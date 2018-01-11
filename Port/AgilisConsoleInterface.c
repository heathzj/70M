/*********************************************************************
 *
 *  UART Configuration Menu
 *    - UART configuration
 *    - XMODEM uploads of MPFS classic image
 *
 *********************************************************************
 * FileName:        UARTConfig.c
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
 * Author               Date      Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * E. Wood     			4/26/08	  Moved from MainDemo.c
 ********************************************************************/
#define __UARTCONFIG_C

#include "TCPIPConfig.h"
#include "Global.h"
#include "define.h"

#if defined(STACK_USE_UART)

#include "TCPIP Stack/TCPIP.h"
#include "Main.h"


#if (defined(MPFS_USE_EEPROM) || defined(MPFS_USE_SPI_FLASH)) && defined(STACK_USE_MPFS)
	static BOOL DownloadMPFS(void);
#endif

#define MAX_USER_RESPONSE_LEN   (20u)

#if 0

unsigned char SerialModePin=0,SerialModePin2=1;

void DoUARTConfig(void)
{
    BYTE response[MAX_USER_RESPONSE_LEN];
    IP_ADDR tempIPValue;
    IP_ADDR *destIPValue;
	WORD_VAL wvTemp;
    BOOL bQuit = FALSE;
    char l;

	while(!bQuit)
	{
	// Display the menu
	
        CONFIGT();
	    putrsUART("\r\n\r\n\rAgilis TCP/IP Config Application ("VERSION", " __DATE__ ")\r\n\r\n");
	    putrsUART("\t1: Change serial number:\t\t");
		wvTemp.v[1] = AppConfig.MyMACAddr.v[4];
		wvTemp.v[0] = AppConfig.MyMACAddr.v[5];
		uitoa(wvTemp.Val, response);
		putsUART(response);
		putrsUART("\r\n\t2: Change host name:\t\t\t");
		putsUART(AppConfig.NetBIOSName);
	    putrsUART("\r\n\t3: Change static IP address:\t\t");
	    DisplayIPValue(AppConfig.MyIPAddr);
	    putrsUART("\r\n\t4: Change static gateway address:\t");
	    DisplayIPValue(AppConfig.MyGateway);
	    putrsUART("\r\n\t5: Change static subnet mask:\t\t");
	    DisplayIPValue(AppConfig.MyMask);
		putrsUART("\r\n\t6: Change static primary DNS server:\t");
	    DisplayIPValue(AppConfig.PrimaryDNSServer);
		putrsUART("\r\n\t7: Change static secondary DNS server:\t");
	    DisplayIPValue(AppConfig.SecondaryDNSServer);
	    putrsUART("\r\n\t8: ");
		putrsUART((ROM BYTE*)(AppConfig.Flags.bIsDHCPEnabled ? "Dis" : "En"));
		putrsUART("able DHCP & IP Gleaning:\t\tDHCP is currently ");
		putrsUART((ROM BYTE*)(AppConfig.Flags.bIsDHCPEnabled ? "enabled" : "disabled"));
	    //putrsUART("\r\n\t9: Download MPFS image.");
        putrsUART("\r\n\t9: Change Web UI Password(1~8 Bytes):	");
        putsUART( webpassinfo.webpassword);
        //putrsUART("\r\n\tA: Disable SNMP Serial Poll:\t\tSNMP Poll is currently ");
        //putrsUART((ROM BYTE*)((polling_en == 1)? "enabled" : "disabled"));
        putrsUART("\r\n\tB: Select M&C Serial Mode:     \t\tSerial Mode(0=RS232 1=RS485):");
        uitoa(SerialModePin, response);
		putsUART(response);
        putrsUART("\r\n\tC: Select SNMP Serial Mode:     \tSerial Mode(0=RS232 1=RS485):");
        uitoa(SerialModePin2, response);
		putsUART(response);
	    putrsUART("\r\n\t0: Save & Quit.");
	    putrsUART("\r\nEnter a menu choice: ");
//		DelayMS(300);
	    CONFIGR();
	
		// Wait for the user to press a key
	    while(!DataRdyUART());
	    CONFIGT();
		putrsUART((ROM char*)"\r\n");
	
		// Execute the user selection
        CONFIGR();
	    switch(ReadUART())
	    {
		    case '1':
                CONFIGT();
				putrsUART("New setting: ");
                CONFIGR();
				if(ReadStringUART(response, sizeof(response)))
				{
					wvTemp.Val = atoi((char*)response);
			        AppConfig.MyMACAddr.v[4] = wvTemp.v[1];
		    	    AppConfig.MyMACAddr.v[5] = wvTemp.v[0];
				}
		        break;
		
			case '2':
                CONFIGT();
				putrsUART("New setting: ");
                CONFIGR();
		        ReadStringUART(response, sizeof(response) > sizeof(AppConfig.NetBIOSName) ? sizeof(AppConfig.NetBIOSName) : sizeof(response));
				if(response[0] != '\0')
				{
					memcpy(AppConfig.NetBIOSName, (void*)response, sizeof(AppConfig.NetBIOSName));
			        FormatNetBIOSName(AppConfig.NetBIOSName);
				}
				break;
		
		    case '3':
		        destIPValue = &AppConfig.MyIPAddr;
		        goto ReadIPConfig;
		
		    case '4':
		        destIPValue = &AppConfig.MyGateway;
		        goto ReadIPConfig;
		
		    case '5':
		        destIPValue = &AppConfig.MyMask;
		        goto ReadIPConfig;
		
		    case '6':
		        destIPValue = &AppConfig.PrimaryDNSServer;
		        goto ReadIPConfig;
	
			case '7':
		        destIPValue = &AppConfig.SecondaryDNSServer;
		        goto ReadIPConfig;
		
ReadIPConfig:
                CONFIGT();
				putrsUART("New setting: ");
		        CONFIGR();
                ReadStringUART(response, sizeof(response));
		
		        if(StringToIPAddress(response, &tempIPValue))
		            destIPValue->Val = tempIPValue.Val;
				else
                    CONFIGT();
		            putrsUART("Invalid input.\r\n");

		        break;
		
		
		    case '8':
		        AppConfig.Flags.bIsDHCPEnabled = !AppConfig.Flags.bIsDHCPEnabled;
		        break;
		
		    case '9':
                /**
				#if defined(MPFS_USE_EEPROM) && defined(STACK_USE_MPFS)
		        	DownloadMPFS();
				#endif
                **/
                CONFIGT();
				putrsUART("New setting: ");
		        CONFIGR();
                ReadStringUART(response, sizeof(response));

                for(l=0;l<11;l++)
                {
                  if(response[l]==0)
                    break;
                }


                if(l>8)
                {
                    CONFIGT();
                    Delay10TCYx( 10 );
                  	putrsUART("\r\nSet fail,Password too long.\r\n");
                    Delay10TCYx( 20 );
                    CONFIGR();
                    
                }
                else if(l<1)
                {
                   CONFIGT();
                    Delay10TCYx( 10 );
                  	putrsUART("\r\nSet fail,Password too short.\r\n");
                    Delay10TCYx( 20 );
                    CONFIGR();
                }
                else
                {
                  strcpy( webpassinfo.webpassword,response);
                  SaveSetting();
                } 
		        break;
		
		    case '0':
			    bQuit = TRUE;
				#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
		        	SaveAppConfig();
                    CONFIGT();
					putrsUART("Settings saved.\r\n");
				#else
                    CONFIGT();
					putrsUART("External EEPROM/Flash not present -- settings will be lost at reset.\r\n");
				#endif
		        break;
           case 'A':
           case 'a':
                CONFIGT();
                putrsUART("SNMP Polling Enable/Disabled.\r\n");

                break;
           case 'B':
           case 'b':
                CONFIGT();
                putrsUART("New setting: ");
                CONFIGR();
				if(ReadStringUART(response, sizeof(response)))
				{
				
                	//SerialModePin = atoi((char*)response);
                    Read2[2][0]= atoi((char*)response);
                    SaveSetting();
			        
				}
                break;
          case 'C':
          case 'c':
                CONFIGT();
                putrsUART("New setting: ");
                CONFIGR();
				if(ReadStringUART(response, sizeof(response)))
				{
				
                	//SerialModePin = atoi((char*)response);
                    Read2[3][0]= atoi((char*)response);
                    SaveSetting();
			        
				}
                break;
		}
	}
}
#endif
#endif //#if defined(STACK_USE_UART)
