/*********************************************************************
 *
 *  Application to Demo HTTP2 Server
 *  Support for HTTP2 module in Microchip TCP/IP Stack
 *	 -Implements the application 
 *	 -Reference: RFC 1002
 *
 *********************************************************************
 * FileName:        CustomHTTPApp.c
 * Dependencies:    TCP/IP stack
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date    Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Elliott Wood     	6/18/07	Original
 ********************************************************************/
#define __CUSTOMHTTPAPP_C

#include "TCPIPConfig.h"

#if defined(STACK_USE_HTTP2_SERVER)

#include "HTTPApp.h"

webpassword_t webpassinfo;

/****************************************************************************
  Section:
	Function Prototypes and Memory Globalizers
  ***************************************************************************/


// RAM allocated for DDNS parameters
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
	static BYTE DDNSData[100];
#endif

// Sticky status message variable.
// This is used to indicated whether or not the previous POST operation was 
// successful.  The application uses these to store status messages when a 
// POST operation redirects.  This lets the application provide status messages
// after a redirect, when connection instance data has already been lost.
BOOL lastSuccess = FALSE;

// Stick status message variable.  See lastSuccess for details.
BOOL lastFailure = FALSE;

/****************************************************************************
  Section:
	Authorization Handlers
  ***************************************************************************/
  
/*****************************************************************************
  Function:
	BYTE HTTPNeedsAuth(BYTE* cFile)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPNeedsAuth(BYTE* cFile)
{
	// If the filename begins with the folder "protect", then require auth
	
   if(memcmppgm2ram(cFile, (ROM void*)"protect", 7) == 0)
		return 0x00;		// Authentication will be needed later

	// If the filename begins with the folder "snmp", then require auth
	if(memcmppgm2ram(cFile, (ROM void*)"snmp", 4) == 0)
		return 0x00;		// Authentication will be needed later

	#if defined(HTTP_MPFS_UPLOAD_REQUIRES_AUTH)
	if(memcmppgm2ram(cFile, (ROM void*)"mpfsupload", 10) == 0)
		return 0x00;
	#endif

	// You can match additional strings here to password protect other files.
	// You could switch this and exclude files from authentication.
	// You could also always return 0x00 to require auth for all files.
	// You can return different values (0x00 to 0x79) to track "realms" for below.

	return 0x80;			// No authentication required
   //return 0x00;
}
#endif

/*****************************************************************************
  Function:
	BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)
BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
{
	if(strcmppgm2ram((char *)cUser,(ROM char *)"admin") == 0
	//	&& strcmppgm2ram((char *)cPass, (ROM char *)"admin") == 0)
       && strcmp((char *)cPass, (char *)webpassinfo.webpassword) == 0)
		return 0x80;		// We accept this combination
	
	// You can add additional user/pass combos here.
	// If you return specific "realm" values above, you can base this 
	//   decision on what specific file or folder is being accessed.
	// You could return different values (0x80 to 0xff) to indicate 
	//   various users or groups, and base future processing decisions
	//   in HTTPExecuteGet/Post or HTTPPrint callbacks on this value.
	
	return 0x00;			// Provided user/pass is invalid
}
#endif

/****************************************************************************
  Section:
	GET Form Handlers
  ***************************************************************************/
  
/*****************************************************************************
  Function:
	HTTP_IO_RESULT HTTPExecuteGet(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
//    char oldp[10];
//	char newp[10];
//	char rep[10]; 
	//BYTE attn[7]={0,0,0,0,0,0,0};
HTTP_IO_RESULT HTTPExecuteGet(void)
{
   return HTTPExe_get_deviceinfo();
}


/****************************************************************************
  Section:
	POST Form Handlers
  ***************************************************************************/
#if defined(HTTP_USE_POST)

/*****************************************************************************
  Function:
	HTTP_IO_RESULT HTTPExecutePost(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
HTTP_IO_RESULT HTTPExecutePost(void)
{
	// Resolve which function to use and pass along
	BYTE filename[20];
	
	// Load the file name
	// Make sure BYTE filename[] above is large enough for your longest name
	MPFSGetFilename(curHTTP.file, filename, sizeof(filename));
	
#if defined(USE_LCD)
	if(!memcmppgm2ram(filename, "forms.htm", 9))
		return HTTPPostLCD();
	if(!memcmppgm2ram(filename, "buc.htm", 7))
		return HTTPPostLCD2();
#endif

#if defined(STACK_USE_HTTP_MD5_DEMO)
	if(!memcmppgm2ram(filename, "upload.htm", 10))
		return HTTPPostMD5();
#endif

#if defined(STACK_USE_HTTP_APP_RECONFIG)
	if(!memcmppgm2ram(filename, "protect/config.htm", 18))
		return HTTPPostConfig();
	#if defined(STACK_USE_SNMP_SERVER)
	 if(!memcmppgm2ram(filename, "snmp/snmpconfig.htm", 19))
                   return HTTPPostSNMPCommunity();
	#endif
#endif

#if defined(STACK_USE_SMTP_CLIENT)
	if(!strcmppgm2ram((char*)filename, (ROM char*)"email/index.htm"))
		return HTTPPostEmail();
#endif
	
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
	if(!strcmppgm2ram((char*)filename, "dyndns/index.htm"))
		return HTTPPostDDNSConfig();
#endif




if(!memcmppgm2ram(filename, "protect/lut.htm", 15))
		return HTTPPostlut();

	return HTTP_IO_DONE;
}

/*****************************************************************************
  Function:
	static HTTP_IO_RESULT HTTPPostLCD(void)

  Summary:
	Processes the LCD form on forms.htm

  Description:
	Locates the 'lcd' parameter and uses it to update the text displayed
	on the board's LCD display.
	
	This function has four states.  The first reads a name from the data
	string returned as part of the POST request.  If a name cannot
	be found, it returns, asking for more data.  Otherwise, if the name 
	is expected, it reads the associated value and writes it to the LCD.  
	If the name is not expected, the value is discarded and the next name 
	parameter is read.
	
	In the case where the expected string is never found, this function 
	will eventually return HTTP_IO_NEED_DATA when no data is left.  In that
	case, the HTTP2 server will automatically trap the error and issue an
	Internal Server Error to the browser.

  Precondition:
	None

  Parameters:
	None

  Return Values:
  	HTTP_IO_DONE - the parameter has been found and saved
  	HTTP_IO_WAITING - the function is pausing to continue later
  	HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
  ***************************************************************************/


static HTTP_IO_RESULT HTTPPostlut(void)
{
	BYTE* cDest;
	
	#define SM_POST_LUT_READ_NAME		(0u)
	#define SM_POST_LUT_READ_VALUE		(1u)
	
	switch(curHTTP.smPost)
	{
		// Find the name
		case SM_POST_LUT_READ_NAME:
		
			// Read a name
			if(HTTPReadPostName(curHTTP.data, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
				return HTTP_IO_NEED_DATA;

			curHTTP.smPost = SM_POST_LUT_READ_VALUE;
			// No break...continue reading value
		
		// Found the value, so store the LCD and return
		case SM_POST_LUT_READ_VALUE:
				
			// If value is expected, read it to data buffer,
			// otherwise ignore it (by reading to NULL)	
		         if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"lcd"))
				cDest = curHTTP.data;
			else
				cDest = NULL;
			
			// Read a value string
			if(HTTPReadPostValue(cDest, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
				return HTTP_IO_NEED_DATA;
			
			// If this was an unexpected value, look for a new name
			if(!cDest)
			{
				curHTTP.smPost = SM_POST_LUT_READ_NAME;
				break;
			}
			/**
			// Copy up to 32 characters to the LCD
			if(strlen((char*)cDest) < 32u)
			{
				memset(LCDText, ' ', 32);
				strcpy((char*)LCDText, (char*)cDest);
			}
			else
			{
				memcpy(LCDText, (void *)cDest, 32);
			}
			LCDUpdate();
			**/
			// This is the only expected value, so callback is done
			strcpypgm2ram((char*)curHTTP.data, (ROM void*)"/buc.htm");
			curHTTP.httpStatus = HTTP_REDIRECT;
			return HTTP_IO_DONE;
	}
	
	// Default assumes that we're returning for state machine convenience.
	// Function will be called again later.
	return HTTP_IO_WAITING;
}



/*****************************************************************************
  Function:
	static HTTP_IO_RESULT HTTPPostConfig(void)

  Summary:
	Processes the configuration form on config/index.htm

  Description:
	Accepts configuration parameters from the form, saves them to a
	temporary location in RAM, then eventually saves the data to EEPROM or
	external Flash.
	
	When complete, this function redirects to config/reboot.htm, which will
	display information on reconnecting to the board.

	This function creates a shadow copy of the AppConfig structure in 
	RAM and then overwrites incoming data there as it arrives.  For each 
	name/value pair, the name is first read to curHTTP.data[0:5].  Next, the 
	value is read to newAppConfig.  Once all data has been read, the new
	AppConfig is saved back to EEPROM and the browser is redirected to 
	reboot.htm.  That file includes an AJAX call to reboot.cgi, which 
	performs the actual reboot of the machine.
	
	If an IP address cannot be parsed, too much data is POSTed, or any other 
	parsing error occurs, the browser reloads config.htm and displays an error 
	message at the top.

  Precondition:
	None

  Parameters:
	None

  Return Values:
  	HTTP_IO_DONE - all parameters have been processed
  	HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
  ***************************************************************************/
#if defined(STACK_USE_HTTP_APP_RECONFIG)
static HTTP_IO_RESULT HTTPPostConfig(void)
{
	APP_CONFIG newAppConfig;
	BYTE *ptr;
	BYTE i;

	// Check to see if the browser is attempting to submit more data than we 
	// can parse at once.  This function needs to receive all updated 
	// parameters and validate them all before committing them to memory so that
	// orphaned configuration parameters do not get written (for example, if a 
	// static IP address is given, but the subnet mask fails parsing, we 
	// should not use the static IP address).  Everything needs to be processed 
	// in a single transaction.  If this is impossible, fail and notify the user.
	// As a web devloper, if you add parameters to AppConfig and run into this 
	// problem, you could fix this by to splitting your update web page into two 
	// seperate web pages (causing two transactional writes).  Alternatively, 
	// you could fix it by storing a static shadow copy of AppConfig someplace 
	// in memory and using it instead of newAppConfig.  Lastly, you could 
	// increase the TCP RX FIFO size for the HTTP server.  This will allow more 
	// data to be POSTed by the web browser before hitting this limit.
	if(curHTTP.byteCount > TCPIsGetReady(sktHTTP) + TCPGetRxFIFOFree(sktHTTP))
		goto ConfigFailure;
	
	// Ensure that all data is waiting to be parsed.  If not, keep waiting for 
	// all of it to arrive.
	if(TCPIsGetReady(sktHTTP) < curHTTP.byteCount)
		return HTTP_IO_NEED_DATA;
	
	
	// Use current config in non-volatile memory as defaults
	#if defined(EEPROM_CS_TRIS)
		XEEReadArray(0x0001, (BYTE*)&newAppConfig, sizeof(AppConfig));
	#elif defined(SPIFLASH_CS_TRIS)
		SPIFlashReadArray(0x0001, (BYTE*)&newAppConfig, sizeof(AppConfig));
	#endif
	
	// Start out assuming that DHCP is disabled.  This is necessary since the 
	// browser doesn't submit this field if it is unchecked (meaning zero).  
	// However, if it is checked, this will be overridden since it will be 
	// submitted.
	newAppConfig.Flags.bIsDHCPEnabled = 0;
	AppConfig.Flags.bIsDHCPEnabled = 0;


	// Read all browser POST data
	while(curHTTP.byteCount)
	{
		// Read a form field name
		if(HTTPReadPostName(curHTTP.data, 6) != HTTP_READ_OK)
			goto ConfigFailure;
			
		// Read a form field value
		if(HTTPReadPostValue(curHTTP.data + 6, sizeof(curHTTP.data)-6-2) != HTTP_READ_OK)
			goto ConfigFailure;
			
		// Parse the value that was read
		if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"ip"))
		{// Read new static IP Address
			if(!StringToIPAddress(curHTTP.data+6, &newAppConfig.MyIPAddr))
				goto ConfigFailure;
				
			newAppConfig.DefaultIPAddr.Val = newAppConfig.MyIPAddr.Val;
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"gw"))
		{// Read new gateway address
			if(!StringToIPAddress(curHTTP.data+6, &newAppConfig.MyGateway))
				goto ConfigFailure;
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"sub"))
		{// Read new static subnet
			if(!StringToIPAddress(curHTTP.data+6, &newAppConfig.MyMask))
				goto ConfigFailure;

			newAppConfig.DefaultMask.Val = newAppConfig.MyMask.Val;
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"dns1"))
		{// Read new primary DNS server
			if(!StringToIPAddress(curHTTP.data+6, &newAppConfig.PrimaryDNSServer))
				goto ConfigFailure;
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"dns2"))
		{// Read new secondary DNS server
			if(!StringToIPAddress(curHTTP.data+6, &newAppConfig.SecondaryDNSServer))
				goto ConfigFailure;
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"mac"))
		{
			// Read new MAC address
			WORD_VAL w;
			BYTE i;

			ptr = curHTTP.data+6;

			for(i = 0; i < 12u; i++)
			{// Read the MAC address
				
				// Skip non-hex bytes
				while( *ptr != 0x00u && !(*ptr >= '0' && *ptr <= '9') && !(*ptr >= 'A' && *ptr <= 'F') && !(*ptr >= 'a' && *ptr <= 'f') )
					ptr++;

				// MAC string is over, so zeroize the rest
				if(*ptr == 0x00u)
				{
					for(; i < 12u; i++)
						curHTTP.data[i] = '0';
					break;
				}
				
				// Save the MAC byte
				curHTTP.data[i] = *ptr++;
			}
			
			// Read MAC Address, one byte at a time
			for(i = 0; i < 6u; i++)
			{				
				w.v[1] = curHTTP.data[i*2];
				w.v[0] = curHTTP.data[i*2+1];
				newAppConfig.MyMACAddr.v[i] = hexatob(w);
			}
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"host"))
		{// Read new hostname
			FormatNetBIOSName(&curHTTP.data[6]);
			memcpy((void*)newAppConfig.NetBIOSName, (void*)curHTTP.data+6, 16);
		}
		else if(!strcmppgm2ram((char*)curHTTP.data, (ROM char*)"dhcp"))
		{// Read new DHCP Enabled flag
			if(curHTTP.data[6] == '1')
			{
				newAppConfig.Flags.bIsDHCPEnabled = 1;
				AppConfig.Flags.bIsDHCPEnabled = 1;//zj
			}

		}
	}


	// All parsing complete!  Save new settings and force a reboot			
	#if defined(EEPROM_CS_TRIS)
		XEEBeginWrite(0x0000);
		XEEWrite(0x60);
		XEEWriteArray((BYTE*)&newAppConfig, sizeof(AppConfig));
	#elif defined(SPIFLASH_CS_TRIS)
		SPIFlashBeginWrite(0x0000);
		SPIFlashWrite(0x60);
		SPIFlashWriteArray((BYTE*)&newAppConfig, sizeof(AppConfig));
	#endif
	
	// Set the board to reboot and display reconnecting information
	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"/protect/reboot.htm?");
	memcpy((void*)(curHTTP.data+20), (void*)newAppConfig.NetBIOSName, 16);
	curHTTP.data[20+16] = 0x00;	// Force null termination
	for(i = 20; i < 20u+16u; i++)
	{
		if(curHTTP.data[i] == ' ')
			curHTTP.data[i] = 0x00;
	}		
	curHTTP.httpStatus = HTTP_REDIRECT;	
	
	return HTTP_IO_DONE;


ConfigFailure:
	lastFailure = TRUE;
	strcpypgm2ram((char*)curHTTP.data, (ROM char*)"/protect/config.htm");
	curHTTP.httpStatus = HTTP_REDIRECT;		

	return HTTP_IO_DONE;
}

#if defined(STACK_USE_SNMP_SERVER)
static HTTP_IO_RESULT HTTPPostSNMPCommunity(void)
{
	BYTE vCommunityIndex;
	BYTE *dest;

	#define SM_CFG_SNMP_READ_NAME	(0u)
	#define SM_CFG_SNMP_READ_VALUE	(1u)
	
	switch(curHTTP.smPost)
	{
		case SM_CFG_SNMP_READ_NAME:
			// If all parameters have been read, end
			if(curHTTP.byteCount == 0u)
			{
				SaveAppConfig();
				return HTTP_IO_DONE;
			}
		
			// Read a name
			if(HTTPReadPostName(curHTTP.data, sizeof(curHTTP.data)-2) == HTTP_READ_INCOMPLETE)
				return HTTP_IO_NEED_DATA;
				
			// Move to reading a value, but no break
			curHTTP.smPost = SM_CFG_SNMP_READ_VALUE;
			
		case SM_CFG_SNMP_READ_VALUE:
			// Read a value
			if(HTTPReadPostValue(curHTTP.data + 6, sizeof(curHTTP.data)-6-2) == HTTP_READ_INCOMPLETE)
				return HTTP_IO_NEED_DATA;

			// Default action after this is to read the next name, unless there's an error
			curHTTP.smPost = SM_CFG_SNMP_READ_NAME;

			// See if this is a known parameter and legal (must be null 
			// terminator in 4th field name byte, string must no greater than 
			// SNMP_COMMUNITY_MAX_LEN bytes long, and SNMP_MAX_COMMUNITY_SUPPORT 
			// must not be violated.
			vCommunityIndex = curHTTP.data[3] - '0';
			if(vCommunityIndex >= SNMP_MAX_COMMUNITY_SUPPORT)
				break;
			if(curHTTP.data[4] != 0x00u)
				break;
			if(memcmppgm2ram((void*)curHTTP.data, (ROM void*)"rcm", 3) == 0)
				dest = AppConfig.readCommunity[vCommunityIndex];
			else if(memcmppgm2ram((void*)curHTTP.data, (ROM void*)"wcm", 3) == 0)
				dest = AppConfig.writeCommunity[vCommunityIndex];
			else
				break;
			if(strlen((char*)curHTTP.data + 6) > SNMP_COMMUNITY_MAX_LEN)
				break;
			
			// String seems valid, lets copy it to AppConfig
			strcpy((char*)dest, (char*)curHTTP.data+6);
			break;			
	}

	return HTTP_IO_WAITING;		// Assume we're waiting to process more data
}
#endif //#if defined(STACK_USE_SNMP_SERVER)

#endif	// #if defined(STACK_USE_HTTP_APP_RECONFIG)

/*****************************************************************************
  Function:
	static HTTP_IO_RESULT HTTPPostMD5(void)

  Summary:
	Processes the file upload form on upload.htm

  Description:
	This function demonstrates the processing of file uploads.  First, the
	function locates the file data, skipping over any headers that arrive.
	Second, it reads the file 64 bytes at a time and hashes that data.  Once
	all data has been received, the function calculates the MD5 sum and
	stores it in curHTTP.data.

	After the headers, the first line from the form will be the MIME 
	separator.  Following that is more headers about the file, which we 
	discard.  After another CRLFCRLF, the file data begins, and we read 
	it 16 bytes at a time and add that to the MD5 calculation.  The reading
	terminates when the separator string is encountered again on its own 
	line.  Notice that the actual file data is trashed in this process, 
	allowing us to accept files of arbitrary size, not limited by RAM.  
	Also notice that the data buffer is used as an arbitrary storage array 
	for the result.  The ~uploadedmd5~ callback reads this data later to 
	send back to the client.
	
  Precondition:
	None

  Parameters:
	None

  Return Values:
	HTTP_IO_DONE - all parameters have been processed
	HTTP_IO_WAITING - the function is pausing to continue later
	HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
  ***************************************************************************/
#if defined(STACK_USE_HTTP_MD5_DEMO)
static HTTP_IO_RESULT HTTPPostMD5(void)
{
	WORD lenA, lenB;
	static HASH_SUM md5;			// Assume only one simultaneous MD5
	
	#define SM_MD5_READ_SEPARATOR	(0u)
	#define SM_MD5_SKIP_TO_DATA		(1u)
	#define SM_MD5_READ_DATA		(2u)
	#define SM_MD5_POST_COMPLETE	(3u)
	
	// Don't care about curHTTP.data at this point, so use that for buffer
	switch(curHTTP.smPost)
	{
		// Just started, so try to find the separator string
		case SM_MD5_READ_SEPARATOR:
			// Reset the MD5 calculation
			MD5Initialize(&md5);
			
			// See if a CRLF is in the buffer
			lenA = TCPFindROMArray(sktHTTP, (ROM BYTE*)"\r\n", 2, 0, FALSE);
			if(lenA == 0xffff)
			{//if not, ask for more data
				return HTTP_IO_NEED_DATA;
			}
		
			// If so, figure out where the last byte of data is
			// Data ends at CRLFseparator--CRLF, so 6+len bytes
			curHTTP.byteCount -= lenA + 6;
			
			// Read past the CRLF
			curHTTP.byteCount -= TCPGetArray(sktHTTP, NULL, lenA+2);
			
			// Save the next state (skip to CRLFCRLF)
			curHTTP.smPost = SM_MD5_SKIP_TO_DATA;
			
			// No break...continue reading the headers if possible
				
		// Skip the headers
		case SM_MD5_SKIP_TO_DATA:
			// Look for the CRLFCRLF
			lenA = TCPFindROMArray(sktHTTP, (ROM BYTE*)"\r\n\r\n", 4, 0, FALSE);
	
			if(lenA != 0xffff)
			{// Found it, so remove all data up to and including
				lenA = TCPGetArray(sktHTTP, NULL, lenA+4);
				curHTTP.byteCount -= lenA;
				curHTTP.smPost = SM_MD5_READ_DATA;
			}
			else
			{// Otherwise, remove as much as possible
				lenA = TCPGetArray(sktHTTP, NULL, TCPIsGetReady(sktHTTP) - 4);
				curHTTP.byteCount -= lenA;
			
				// Return the need more data flag
				return HTTP_IO_NEED_DATA;
			}
			
			// No break if we found the header terminator
			
		// Read and hash file data
		case SM_MD5_READ_DATA:
			// Find out how many bytes are available to be read
			lenA = TCPIsGetReady(sktHTTP);
			if(lenA > curHTTP.byteCount)
				lenA = curHTTP.byteCount;
	
			while(lenA > 0u)
			{// Add up to 64 bytes at a time to the sum
				lenB = TCPGetArray(sktHTTP, curHTTP.data, (lenA < 64u)?lenA:64);
				curHTTP.byteCount -= lenB;
				lenA -= lenB;
				MD5AddData(&md5, curHTTP.data, lenB);
			}
					
			// If we've read all the data
			if(curHTTP.byteCount == 0u)
			{// Calculate and copy result to curHTTP.data for printout
				curHTTP.smPost = SM_MD5_POST_COMPLETE;
				MD5Calculate(&md5, curHTTP.data);
				return HTTP_IO_DONE;
			}
				
			// Ask for more data
			return HTTP_IO_NEED_DATA;
	}
	
	return HTTP_IO_DONE;
}
#endif // #if defined(STACK_USE_HTTP_MD5_DEMO)

/*****************************************************************************
  Function:
	static HTTP_IO_RESULT HTTPPostEmail(void)

  Summary:
	Processes the e-mail form on email/index.htm

  Description:
	This function sends an e-mail message using the SMTP client and 
	optionally encrypts the connection to the SMTP server using SSL.  It
	demonstrates the use of the SMTP client, waiting for asynchronous
	processes in an HTTP callback, and how to send e-mail attachments using
	the stack.

	Messages with attachments are sent using multipart/mixed MIME encoding,
	which has three sections.  The first has no headers, and is only to be
	displayed by old clients that cannot interpret the MIME format.  (The 
	overwhelming majority of these clients have been obseleted, but the
	so-called "ignored" section is still used.)  The second has a few 
	headers to indicate that it is the main body of the message in plain-
	text encoding.  The third section has headers indicating an attached 
	file, along with its name and type.  All sections are separated by a
	boundary string, which cannot appear anywhere else in the message.
	
  Precondition:
	None

  Parameters:
	None

  Return Values:
	HTTP_IO_DONE - the message has been sent
	HTTP_IO_WAITING - the function is waiting for the SMTP process to complete
	HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
  ***************************************************************************/
#if defined(STACK_USE_SMTP_CLIENT)
static HTTP_IO_RESULT HTTPPostEmail(void)
{
	static BYTE *ptrData;
	static BYTE *szPort;
	#if defined(STACK_USE_SSL_CLIENT)
	static BYTE *szUseSSL;
	#endif
	WORD len, rem;
	BYTE cName[8];

	#define SM_EMAIL_CLAIM_MODULE				(0u)
	#define SM_EMAIL_READ_PARAM_NAME			(1u)
	#define SM_EMAIL_READ_PARAM_VALUE			(2u)
	#define SM_EMAIL_PUT_IGNORED				(3u)
	#define SM_EMAIL_PUT_BODY					(4u)
	#define SM_EMAIL_PUT_ATTACHMENT_HEADER		(5u)
	#define SM_EMAIL_PUT_ATTACHMENT_DATA_BTNS	(6u)
	#define SM_EMAIL_PUT_ATTACHMENT_DATA_LEDS	(7u)
	#define SM_EMAIL_PUT_ATTACHMENT_DATA_POT	(8u)
	#define SM_EMAIL_PUT_TERMINATOR				(9u)
	#define SM_EMAIL_FINISHING					(10u)
	
	#define EMAIL_SPACE_REMAINING				(HTTP_MAX_DATA_LEN - (ptrData - curHTTP.data))
	
	switch(curHTTP.smPost)
	{
		case SM_EMAIL_CLAIM_MODULE:
			// Try to claim module
			if(SMTPBeginUsage())
			{// Module was claimed, so set up static parameters
				SMTPClient.Subject.szROM = (ROM BYTE*)"Microchip TCP/IP Stack Status Update";
				SMTPClient.ROMPointers.Subject = 1;
				SMTPClient.From.szROM = (ROM BYTE*)"\"SMTP Service\" <mchpboard@picsaregood.com>";
				SMTPClient.ROMPointers.From = 1;
				
				// The following two lines indicate to the receiving client that 
				// this message has an attachment.  The boundary field *must not*
				// be included anywhere in the content of the message.  In real 
				// applications it is typically a long random string.
				SMTPClient.OtherHeaders.szROM = (ROM BYTE*)"MIME-version: 1.0\r\nContent-type: multipart/mixed; boundary=\"frontier\"\r\n";
				SMTPClient.ROMPointers.OtherHeaders = 1;
				
				// Move our state machine forward
				ptrData = curHTTP.data;
				szPort = NULL;
				curHTTP.smPost = SM_EMAIL_READ_PARAM_NAME;
			}
			return HTTP_IO_WAITING;			
			
		case SM_EMAIL_READ_PARAM_NAME:
			// Search for a parameter name in POST data
			if(HTTPReadPostName(cName, sizeof(cName)) == HTTP_READ_INCOMPLETE)
				return HTTP_IO_NEED_DATA;
			
			// Try to match the name value
			if(!strcmppgm2ram((char*)cName, (ROM char*)"server"))
			{// Read the server name
				SMTPClient.Server.szRAM = ptrData;
				curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
			}
			else if(!strcmppgm2ram((char*)cName, (ROM char*)"port"))
			{// Read the server port
				szPort = ptrData;
				curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
			}
			#if defined(STACK_USE_SSL_CLIENT)
			else if(!strcmppgm2ram((char*)cName, (ROM char*)"ssl"))
			{// Read the server port
				szUseSSL = ptrData;
				curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
			}
			#endif
			else if(!strcmppgm2ram((char*)cName, (ROM char*)"user"))
			{// Read the user name
				SMTPClient.Username.szRAM = ptrData;
				curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
			}
			else if(!strcmppgm2ram((char*)cName, (ROM char*)"pass"))
			{// Read the password
				SMTPClient.Password.szRAM = ptrData;
				curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
			}
			else if(!strcmppgm2ram((char*)cName, (ROM char*)"to"))
			{// Read the To string
				SMTPClient.To.szRAM = ptrData;
				curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
			}
			else if(!strcmppgm2ram((char*)cName, (ROM char*)"msg"))
			{// Done with headers, move on to the message
				// Delete paramters that are just null strings (no data from user) or illegal (ex: password without username)
				if(SMTPClient.Server.szRAM)
					if(*SMTPClient.Server.szRAM == 0x00u)
						SMTPClient.Server.szRAM = NULL;
				if(SMTPClient.Username.szRAM)
					if(*SMTPClient.Username.szRAM == 0x00u)
						SMTPClient.Username.szRAM = NULL;
				if(SMTPClient.Password.szRAM)
					if((*SMTPClient.Password.szRAM == 0x00u) || (SMTPClient.Username.szRAM == NULL))
						SMTPClient.Password.szRAM = NULL;
				
				// Decode server port string if it exists
				if(szPort)
					if(*szPort)
						SMTPClient.ServerPort = (WORD)atol((char*)szPort);

				// Determine if SSL should be used
				#if defined(STACK_USE_SSL_CLIENT)
				if(szUseSSL)
					if(*szUseSSL == '1')
						SMTPClient.UseSSL = TRUE;
				#endif
				
				// Start sending the message
				SMTPSendMail();
				curHTTP.smPost = SM_EMAIL_PUT_IGNORED;
				return HTTP_IO_WAITING;
			}
			else
			{// Don't know what we're receiving
				curHTTP.smPost = SM_EMAIL_READ_PARAM_VALUE;
			}
			
			// No break...continue to try reading the value
		
		case SM_EMAIL_READ_PARAM_VALUE:
			// Search for a parameter value in POST data
			if(HTTPReadPostValue(ptrData, EMAIL_SPACE_REMAINING) == HTTP_READ_INCOMPLETE)
				return HTTP_IO_NEED_DATA;
				
			// Move past the data that was just read
			ptrData += strlen((char*)ptrData);
			if(ptrData < curHTTP.data + HTTP_MAX_DATA_LEN - 1)
				ptrData += 1;
			
			// Try reading the next parameter
			curHTTP.smPost = SM_EMAIL_READ_PARAM_NAME;
			return HTTP_IO_WAITING;
			
		case SM_EMAIL_PUT_IGNORED:
			// This section puts a message that is ignored by compatible clients.
			// This text will not display unless the receiving client is obselete 
			// and does not understand the MIME structure.
			// The "--frontier" indicates the start of a section, then any
			// needed MIME headers follow, then two CRLF pairs, and then
			// the actual content (which will be the body text in the next state).
			
			// Check to see if a failure occured
			if(!SMTPIsBusy())
			{
				curHTTP.smPost = SM_EMAIL_FINISHING;
				return HTTP_IO_WAITING;
			}
		
			// See if we're ready to write data
			if(SMTPIsPutReady() < 90u)
				return HTTP_IO_WAITING;
				
			// Write the ignored text				
			SMTPPutROMString((ROM BYTE*)"This is a multi-part message in MIME format.\r\n");
			SMTPPutROMString((ROM BYTE*)"--frontier\r\nContent-type: text/plain\r\n\r\n");
			SMTPFlush();
			
			// Move to the next state
			curHTTP.smPost = SM_EMAIL_PUT_BODY;
			
		case SM_EMAIL_PUT_BODY:
			// Write as much body text as is available from the TCP buffer
			// return HTTP_IO_NEED_DATA or HTTP_IO_WAITING
			// On completion, => PUT_ATTACHMENT_HEADER and continue
			
			// Check to see if a failure occurred
			if(!SMTPIsBusy())
			{
				curHTTP.smPost = SM_EMAIL_FINISHING;
				return HTTP_IO_WAITING;
			}
			
			// Loop as long as data remains to be read
			while(curHTTP.byteCount)
			{
				// See if space is available to write
				len = SMTPIsPutReady();
				if(len == 0u)
					return HTTP_IO_WAITING;
				
				// See if data is ready to be read
				rem = TCPIsGetReady(sktHTTP);
				if(rem == 0u)
					return HTTP_IO_NEED_DATA;
				
				// Only write as much as we can handle
				if(len > rem)
					len = rem;
				if(len > HTTP_MAX_DATA_LEN - 2)
					len = HTTP_MAX_DATA_LEN - 2;
				
				// Read the data from HTTP POST buffer and send it to SMTP
				curHTTP.byteCount -= TCPGetArray(sktHTTP, curHTTP.data, len);
				curHTTP.data[len] = '\0';
				HTTPURLDecode(curHTTP.data);
				SMTPPutString(curHTTP.data);
				SMTPFlush();
			}
			
			// We're done with the POST data, so continue
			curHTTP.smPost = SM_EMAIL_PUT_ATTACHMENT_HEADER;
						
		case SM_EMAIL_PUT_ATTACHMENT_HEADER:
			// This section writes the attachment to the message.
			// This portion generally will not display in the reader, but
			// will be downloadable to the local machine.  Use caution
			// when selecting the content-type and file name, as certain
			// types and extensions are blocked by virus filters.

			// The same structure as the message body is used.
			// Any attachment must not include high-bit ASCII characters or
			// binary data.  If binary data is to be sent, the data should
			// be encoded using Base64 and a MIME header should be added:
			// Content-transfer-encoding: base64
			
			// Check to see if a failure occurred
			if(!SMTPIsBusy())
			{
				curHTTP.smPost = SM_EMAIL_FINISHING;
				return HTTP_IO_WAITING;
			}
			
			// See if we're ready to write data
			if(SMTPIsPutReady() < 100u)
				return HTTP_IO_WAITING;
			
			// Write the attachment header
			SMTPPutROMString((ROM BYTE*)"\r\n--frontier\r\nContent-type: text/csv\r\nContent-Disposition: attachment; filename=\"status.csv\"\r\n\r\n");
			SMTPFlush();
			
			// Move to the next state
			curHTTP.smPost = SM_EMAIL_PUT_ATTACHMENT_DATA_BTNS;
			
		case SM_EMAIL_PUT_ATTACHMENT_DATA_BTNS:
			// The following states output the system status as a CSV file.
			
			// Check to see if a failure occurred
			if(!SMTPIsBusy())
			{
				curHTTP.smPost = SM_EMAIL_FINISHING;
				return HTTP_IO_WAITING;
			}
			
			// See if we're ready to write data
			if(SMTPIsPutReady() < 36u)
				return HTTP_IO_WAITING;
				
			// Write the header and button strings
			SMTPPutROMString((ROM BYTE*)"SYSTEM STATUS\r\n");
			SMTPPutROMString((ROM BYTE*)"Buttons:,");
			SMTPPut(BUTTON0_IO + '0');
			SMTPPut(',');
			SMTPPut(BUTTON1_IO + '0');
			SMTPPut(',');
			SMTPPut(BUTTON2_IO + '0');
			SMTPPut(',');
			SMTPPut(BUTTON3_IO + '0');
			SMTPPut('\r');
			SMTPPut('\n');
			SMTPFlush();
			
			// Move to the next state
			curHTTP.smPost = SM_EMAIL_PUT_ATTACHMENT_DATA_LEDS;

		case SM_EMAIL_PUT_ATTACHMENT_DATA_LEDS:
			// Check to see if a failure occurred
			if(!SMTPIsBusy())
			{
				curHTTP.smPost = SM_EMAIL_FINISHING;
				return HTTP_IO_WAITING;
			}
			
			// See if we're ready to write data
			if(SMTPIsPutReady() < 30u)
				return HTTP_IO_WAITING;
				
			// Write the header and button strings
			SMTPPutROMString((ROM BYTE*)"LEDs:,");
			SMTPPut(LED0_IO + '0');
			SMTPPut(',');
			SMTPPut(LED1_IO + '0');
			SMTPPut(',');
			SMTPPut(LED2_IO + '0');
			SMTPPut(',');
			SMTPPut(LED3_IO + '0');
			SMTPPut(',');
			SMTPPut(LED4_IO + '0');
			SMTPPut(',');
			SMTPPut(LED5_IO + '0');
			SMTPPut(',');
			SMTPPut(LED6_IO + '0');
			SMTPPut(',');
			SMTPPut(LED7_IO + '0');
			SMTPPut('\r');
			SMTPPut('\n');
			SMTPFlush();

			// Move to the next state
			curHTTP.smPost = SM_EMAIL_PUT_ATTACHMENT_DATA_POT;

		case SM_EMAIL_PUT_ATTACHMENT_DATA_POT:
			// Check to see if a failure occurred
			if(!SMTPIsBusy())
			{
				curHTTP.smPost = SM_EMAIL_FINISHING;
				return HTTP_IO_WAITING;
			}
			
			// See if we're ready to write data
			if(SMTPIsPutReady() < 16u)
				return HTTP_IO_WAITING;

			// Do the A/D conversion
			#if defined(__18CXX)
			    // Wait until A/D conversion is done
			    ADCON0bits.GO = 1;
			    while(ADCON0bits.GO);
			    // Convert 10-bit value into ASCII string
			    len = (WORD)ADRES;
			    uitoa(len, (BYTE*)&curHTTP.data[1]);
			#else
				len = (WORD)ADC1BUF0;
			    uitoa(len, (BYTE*)&curHTTP.data[1]);
			#endif

			// Write the header and button strings
			SMTPPutROMString((ROM BYTE*)"Pot:,");
			SMTPPutString(&curHTTP.data[1]);
			SMTPPut('\r');
			SMTPPut('\n');
			SMTPFlush();
			
			// Move to the next state
			curHTTP.smPost = SM_EMAIL_PUT_TERMINATOR;
			
		case SM_EMAIL_PUT_TERMINATOR:
			// This section finishes the message
			// This consists of two dashes, the boundary, and two more dashes
			// on a single line, followed by a CRLF pair to terminate the message.

			// Check to see if a failure occured
			if(!SMTPIsBusy())
			{
				curHTTP.smPost = SM_EMAIL_FINISHING;
				return HTTP_IO_WAITING;
			}
		
			// See if we're ready to write data
			if(SMTPIsPutReady() < 16u)
				return HTTP_IO_WAITING;
				
			// Write the ignored text				
			SMTPPutROMString((ROM BYTE*)"--frontier--\r\n");
			SMTPPutDone();
			SMTPFlush();
			
			// Move to the next state
			curHTTP.smPost = SM_EMAIL_FINISHING;
		
		case SM_EMAIL_FINISHING:
			// Wait for status
			if(!SMTPIsBusy())
			{
				// Release the module and check success
				// Redirect the user based on the result
				if(SMTPEndUsage() == SMTP_SUCCESS)
					lastSuccess = TRUE;
				else
					lastFailure = TRUE;
									
				// Redirect to the page
				strcpypgm2ram((char*)curHTTP.data, (ROM void*)"/email/index.htm");
				curHTTP.httpStatus = HTTP_REDIRECT;
				return HTTP_IO_DONE;
			}
			
			return HTTP_IO_WAITING;
	}
	
	return HTTP_IO_DONE;
}
#endif	// #if defined(STACK_USE_SMTP_CLIENT)

/****************************************************************************
  Function:
    HTTP_IO_RESULT HTTPPostDDNSConfig(void)
    
  Summary:
    Parsing and collecting http data received from http form.

  Description:
    This routine will be excuted every time the Dynamic DNS Client
    configuration form is submitted.  The http data is received 
    as a string of the variables seperated by '&' characters in the TCP RX
    buffer.  This data is parsed to read the required configuration values, 
    and those values are populated to the global array (DDNSData) reserved 
    for this purpose.  As the data is read, DDNSPointers is also populated
    so that the dynamic DNS client can execute with the new parameters.
    
  Precondition:
     curHTTP is loaded.

  Parameters:
    None.

  Return Values:
    HTTP_IO_DONE 		-  Finished with procedure
    HTTP_IO_NEED_DATA	-  More data needed to continue, call again later
    HTTP_IO_WAITING 	-  Waiting for asynchronous process to complete, 
    						call again later
  ***************************************************************************/
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
static HTTP_IO_RESULT HTTPPostDDNSConfig(void)
{
	static BYTE *ptrDDNS;

	#define SM_DDNS_START			(0u)
	#define SM_DDNS_READ_NAME		(1u)
	#define SM_DDNS_READ_VALUE		(2u)
	#define SM_DDNS_READ_SERVICE	(3u)
	#define SM_DDNS_DONE			(4u)

	#define DDNS_SPACE_REMAINING				(sizeof(DDNSData) - (ptrDDNS - DDNSData))

	switch(curHTTP.smPost)
	{
		// Sets defaults for the system
		case SM_DDNS_START:
			ptrDDNS = DDNSData;
			DDNSSetService(0);
			DDNSClient.Host.szROM = NULL;
			DDNSClient.Username.szROM = NULL;
			DDNSClient.Password.szROM = NULL;
			DDNSClient.ROMPointers.Host = 0;
			DDNSClient.ROMPointers.Username = 0;
			DDNSClient.ROMPointers.Password = 0;
			curHTTP.smPost++;
			
		// Searches out names and handles them as they arrive
		case SM_DDNS_READ_NAME:
			// If all parameters have been read, end
			if(curHTTP.byteCount == 0u)
			{
				curHTTP.smPost = SM_DDNS_DONE;
				break;
			}
		
			// Read a name
			if(HTTPReadPostName(curHTTP.data, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
				return HTTP_IO_NEED_DATA;
			
			if(!strcmppgm2ram((char *)curHTTP.data, (ROM char*)"service"))
			{
				// Reading the service (numeric)
				curHTTP.smPost = SM_DDNS_READ_SERVICE;
				break;
			}
			else if(!strcmppgm2ram((char *)curHTTP.data, (ROM char*)"user"))
				DDNSClient.Username.szRAM = ptrDDNS;
			else if(!strcmppgm2ram((char *)curHTTP.data, (ROM char*)"pass"))
				DDNSClient.Password.szRAM = ptrDDNS;
			else if(!strcmppgm2ram((char *)curHTTP.data, (ROM char*)"host"))
				DDNSClient.Host.szRAM = ptrDDNS;
			
			// Move to reading the value for user/pass/host
			curHTTP.smPost++;
			
		// Reads in values and assigns them to the DDNS RAM
		case SM_DDNS_READ_VALUE:
			// Read a name
			if(HTTPReadPostValue(ptrDDNS, DDNS_SPACE_REMAINING) == HTTP_READ_INCOMPLETE)
				return HTTP_IO_NEED_DATA;
				
			// Move past the data that was just read
			ptrDDNS += strlen((char*)ptrDDNS);
			if(ptrDDNS < DDNSData + sizeof(DDNSData) - 1)
				ptrDDNS += 1;			
			
			// Return to reading names
			curHTTP.smPost = SM_DDNS_READ_NAME;
			break;
		
		// Reads in a service ID
		case SM_DDNS_READ_SERVICE:
			// Read the integer id
			if(HTTPReadPostValue(curHTTP.data, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
				return HTTP_IO_NEED_DATA;
			
			// Convert to a service ID
			DDNSSetService((BYTE)atol((char*)curHTTP.data));

			// Return to reading names
			curHTTP.smPost = SM_DDNS_READ_NAME;
			break;
			
		// Sets up the DDNS client for an update
		case SM_DDNS_DONE:
			// Since user name and password changed, force an update immediately
			DDNSForceUpdate();
			
			// Redirect to prevent POST errors
			lastSuccess = TRUE;
			strcpypgm2ram((char*)curHTTP.data, (ROM void*)"/dyndns/index.htm");
			curHTTP.httpStatus = HTTP_REDIRECT;
			return HTTP_IO_DONE;				
	}
	
	return HTTP_IO_WAITING;		// Assume we're waiting to process more data
}
#endif	// #if defined(STACK_USE_DYNAMICDNS_CLIENT)

#endif //(use_post)



#endif
