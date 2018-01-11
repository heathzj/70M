/*********************************************************************
 *
 *  Application to Demo SNMP Server
 *  Support for SNMP module in Microchip TCP/IP Stack
 *	 - Implements the SNMP application
 *
 *********************************************************************
 * FileName:        CustomSNMPApp.c
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
 * Amit Shirbhate 		09/24/08  SNMPv2c Support added.	
 ********************************************************************/

#define __CUSTOMSNMPAPP_C

#include "TCPIPConfig.h"

#if defined(STACK_USE_SNMP_SERVER)

#include "TCPIP Stack/TCPIP.h"
#include "Global.h"
#include "TCPIP Stack/StackTsk.h"
#include "define.h"
#include "SNMPLL.h"
#include "SNMPMibRegistry.h"
#include "singcom.h"

BOOL snmp_get_type = FALSE;


/****************************************************************************
  Section:
	Global Variables
  ***************************************************************************/
BYTE gSendTrapFlag=FALSE;//global flag to send Trap
BYTE gOIDCorrespondingSnmpMibID=SINGCOM;
BYTE gGenericTrapNotification=ENTERPRISE_SPECIFIC;
BYTE gSpecificTrapNotification=VENDOR_TRAP_DEFAULT; // Vendor specific trap code
//DWORD_VAL Manager_IP;

unsigned char counta;
/*Initialize trap table with no entries.*/
TRAP_INFO trapInfo = { TRAP_TABLE_SIZE };

extern systeminfo_t systeminfo1;
extern systeminfo_t2 systeminfo2;


static DWORD SNMPGetTimeStamp(void);


/****************************************************************************
  ===========================================================================
  Section:
	SNMP Routines
  ===========================================================================
  ***************************************************************************/



#if !defined(SNMP_TRAP_DISABLED)


Trap_t  snmp_trap[MAX_TRAPS]={1}; //Allocate the size to the max number of traps available
BYTE trap_en = 0x00;


/****************************************************************************
  Function:
 	 BOOL SendNotification(BYTE receiverIndex, SNMP_ID var, SNMP_VAL val)
 
  Summary:			
	Prepare, validate remote node which will receive trap and send trap pdu.
 	  	  
  Description:		
    This routine prepares the trap notification pdu, sends ARP and get
	remote device MAC address to which notification to sent, sends
	the notification. 
	
  PreCondition:
	SNMPTrapDemo() is called.
 	
  parameters:
     receiverIndex - The index to array where remote ip address is stored.  
     var		   - SNMP var ID that is to be used in notification
	 val           - Value of var. Only value of BYTE, WORD or DWORD can be sent.
	 
  Return Values:          
 	 TRUE	-	If notification send is successful.
 	 FALSE	-	If send notification failed.
 	 
  Remarks:
     None.
 *************************************************************************/
static BOOL SendNotification(BYTE receiverIndex, SNMP_ID var, SNMP_VAL val,BYTE specific)
{
    static enum { SM_PREPARE, SM_NOTIFY_WAIT } smState = SM_PREPARE;
    IP_ADDR IPAddress;

    // Convert local to network order.
   // IPAddress.v[0] = trapInfo.table[receiverIndex].IPAddress.v[3];
   // IPAddress.v[1] = trapInfo.table[receiverIndex].IPAddress.v[2];
  //  IPAddress.v[2] = trapInfo.table[receiverIndex].IPAddress.v[1];
   // IPAddress.v[3] = trapInfo.table[receiverIndex].IPAddress.v[0];

    IPAddress.v[0] = Manager_IP.v[0];
    IPAddress.v[1] = Manager_IP.v[1];
    IPAddress.v[2] = Manager_IP.v[2];
    IPAddress.v[3] = Manager_IP.v[3];

	strcpypgm2ram(trapInfo.table[receiverIndex].community,"public");
	trapInfo.table[receiverIndex].communityLen = 6;
	
    switch(smState)
    {
	    case SM_PREPARE:
	        SNMPNotifyPrepare(&IPAddress,
	                          trapInfo.table[receiverIndex].community,
	                          trapInfo.table[receiverIndex].communityLen,
	                          SINGCOM,            	   // Agent ID Var
	                          gSpecificTrapNotification,   // Specifc Trap notification code
	                          SNMPGetTimeStamp());
	        smState = SM_NOTIFY_WAIT;
	
	        break;
	
	    case SM_NOTIFY_WAIT:
	        if ( SNMPIsNotifyReady(&IPAddress) )
	        {
	            smState = SM_PREPARE;
	            SNMPNotify(var, val, 0,specific);
	            return TRUE;
	        }
    }
    return FALSE;
}



void snmp_trap_task(void)
{
	BOOL temp = FALSE;
	SNMP_VAL alarm_value = 0;
	BYTE num = 0;

	gGenericTrapNotification = ENTERPRISE_SPECIFIC;
	
	if (!trap_en && ((TickGet() - 0) >= (TICK_SECOND * 5)))
	{
		if (trap_en == 0x00)
		{
	   		trap_en = 0x01;
			memset(snmp_trap, 1, sizeof(snmp_trap));
		}
	}

	if(trap_en == 0x01)
	{
		//num =(ConverterAStatus == 0)?1:0;
		if(num != snmp_trap[0].alarm_temp)
		{
			alarm_value.byte = num;

			if(SendNotification(0, DC_ALOLOCK_TRAP, alarm_value, 1))
				snmp_trap[0].alarm_temp = num;
		}

	//	num =(ConverterBStatus == 0)?1:0;
		if(num != snmp_trap[1].alarm_temp)
		{
			alarm_value.byte = num;

			if(SendNotification(0, DC_BLOLOCK_TRAP, alarm_value, 2))
				snmp_trap[1].alarm_temp = num;
		}
	}
}
#endif

/*********************************************************************
  Function:
 	 BYTE SNMPValidateCommunity(BYTE* community)
 
  Summary:			
 	 Validates community name for access control. 
 
  Description:		
     This function validates the community name for the mib access to NMS.
 	 The snmp community name received in the request pdu is validated for
 	 read and write community names. The agent gives an access to the mib
 	 variables only if the community matches with the predefined values.
  	 This routine also sets a gloabal flag to send trap if authentication
 	 failure occurs.
  
  PreCondition:
 	 SNMPInit is already called.
 
  parameters:
     community - Pointer to community string as sent by NMS.
 
  Returns:          
 	 This routine returns the community validation result as 
  	 READ_COMMUNITY or WRITE_COMMUNITY or INVALID_COMMUNITY	
 
  Remarks:
     This is a callback function called by module. User application must 
  	 implement this function and verify that community matches with 
 	 predefined value. This validation occurs for each NMS request.
 ********************************************************************/
BYTE SNMPValidateCommunity(BYTE * community)
{
	BYTE i;
	BYTE *ptr;
	
	/*
	If the community name is encrypted in the request from the Manager,
	agent required to decrypt it to match with the community it is
	configured for. The response from the agent should contain encrypted community 
	name using the same encryption algorithm which Manager used while
	making the request.
	*/ 		

	// Validate that community string is a legal size
	if(strlen((char*)community) <= SNMP_COMMUNITY_MAX_LEN)
	{
		// Search to see if this is a write community.  This is done before 
		// searching read communities so that full read/write access is 
		// granted if a read and write community name happen to be the same.
		for(i = 0; i < SNMP_MAX_COMMUNITY_SUPPORT; i++)
		{
			ptr = AppConfig.writeCommunity[i];
			if(ptr == NULL)
				continue;
			if(*ptr == 0x00u)
				continue;
			if(strncmp((char*)community, (char*)ptr, SNMP_COMMUNITY_MAX_LEN) == 0)
				return WRITE_COMMUNITY;
		}
		
		// Did not find in write communities, search read communities
		for(i = 0; i < SNMP_MAX_COMMUNITY_SUPPORT; i++)
		{
			ptr = AppConfig.readCommunity[i];
			if(ptr == NULL)
				continue;
			if(*ptr == 0x00u)
				continue;
			if(strncmp((char*)community, (char*)ptr, SNMP_COMMUNITY_MAX_LEN) == 0)
				return READ_COMMUNITY;
		}
	}
	
	// Could not find any matching community, set up to send a trap
	gSpecificTrapNotification=VENDOR_TRAP_DEFAULT;
	gGenericTrapNotification=AUTH_FAILURE;
	gSendTrapFlag=TRUE;
	return INVALID_COMMUNITY;
	
}

/*********************************************************************
  Function:
  	BOOL SNMPIsValidSetLen(SNMP_ID var, BYTE len)

  Summary: 	
	Validates the set variable data length to data type.
	
  Description:
  	This routine is used to validate the dyanmic variable data length
  	to the variable data type. It is used when SET request is processed.
  	This is a callback function called by module. User application
  	must implement this function.
  	
  PreCondition:
  	ProcessSetVar() is called.
 
  Parameters:  
  	var	-	Variable id whose value is to be set
  	len	-	Length value that is to be validated.
 
  Return Values:  
  	TRUE  - if given var can be set to given len
    FALSE - if otherwise.
 
  Remarks:
  	This function will be called for only dynamic variables that are
  	defined as ASCII_STRING and OCTET_STRING (i.e. data length greater
  	than 4 bytes)
 ********************************************************************/
BOOL SNMPIsValidSetLen(SNMP_ID var, BYTE len)
{
    switch(var)
    {
/*
    case TRAP_COMMUNITY:
        if ( len < (BYTE)TRAP_COMMUNITY_MAX_LEN+1 )
            return TRUE;
        break;
*/
    case MANAGERIP:
    case DEVICEIP:
	default:
            return TRUE;
        break;
   case SYS_DESCR1:
   case SYS_CONTACT1:
   case SYS_NAME1:
   case SYS_LOCATION1:
            return TRUE;
        break;

#if defined(USE_LCD)
    case LCD_DISPLAY:
        if ( len < sizeof(LCDText)+1 )
            return TRUE;
        break;
#endif

    }
    return FALSE;
}




/*********************************************************************
  Function:        
  	BOOL SNMPGetExactIndex(SNMP_ID var,SNMP_INDEX index)

  Summary:
  	To search for exact index node in case of a Sequence variable.
	
  Description:    
  	This is a callback function called by SNMP module.
    SNMP user must implement this function in user application and 
    provide appropriate data when called.  This function will only
    be called for OID variable of type sequence.
    
  PreCondition: 
  	None
 
  Parameters:
  	var		-	Variable id as per mib.h (input)
  	index      -	 Index of variable (input)
 
  Return Values:
  	TRUE	-	 If the exact index value exists for given variable at given
                 index.
    FALSE	-	 Otherwise.
 
  Remarks:
	  Only sequence index needs to be handled in this function.
 ********************************************************************/
BOOL SNMPGetExactIndex(SNMP_ID var, SNMP_INDEX index)
{  
    return TRUE;
}

/*********************************************************************
  Function:  
 	BOOL SNMPSetVar(SNMP_ID var, SNMP_INDEX index,
                                   BYTE ref, SNMP_VAL val)
 
  Summary:
  	This routine Set the mib variable with the requested value.
 
  Description:
  	This is a callback function called by module for the snmp
  	SET request.User application must modify this function 
 	for the new variables address.

  Precondition:
 	ProcessVariables() is called.
 	
  Parameters:        
    var	-	Variable id whose value is to be set

    ref -   Variable reference used to transfer multi-byte data
            0 if first byte is set otherwise nonzero value to indicate
            corresponding byte being set.
            
    val -   Up to 4 byte data value.
            If var data type is BYTE, variable
               value is in val->byte
            If var data type is WORD, variable
               value is in val->word
            If var data type is DWORD, variable
               value is in val->dword.
            If var data type is IP_ADDRESS, COUNTER32,
               or GAUGE32, value is in val->dword
            If var data type is OCTET_STRING, ASCII_STRING
               value is in val->byte; multi-byte transfer
               will be performed to transfer remaining
               bytes of data.
 
  Return Values:  
  	TRUE	-	if it is OK to set more byte(s).
    FALSE	-	if otherwise.
 
  Remarks: 
  	This function may get called more than once depending on number 
	of bytes in a specific set request for given variable.
	only dynamic read-write variables needs to be handled.
********************************************************************/
BOOL SNMPSetVar(SNMP_ID var, SNMP_INDEX index, BYTE ref, SNMP_VAL val)
{
  BOOL fReturn = FALSE;
  char i=0;
  switch(var)
  {

	case SYS_DESCR1:
	case SYS_CONTACT1:
	case SYS_NAME1:
	case SYS_LOCATION1:
    {	
		fReturn = snmpll_setSYS_Params(var, ref, val.byte);
		return fReturn;
    }

  } /* End of Switch case */

  SEARCH_INDEX(var,i);
 
  if ((SNMP_cmd_tbl[i].param_id == var) && (SNMP_cmd_tbl[i].fptr_set != NULL))
  {
    fReturn = (*SNMP_cmd_tbl[i].fptr_set) (var, &ref, &val);
  }
 	return fReturn;
}



/*********************************************************************
  Function:        
  	BOOL SNMPGetNextIndex(SNMP_ID var,SNMP_INDEX* index)

  Summary:
  	To search for next index node in case of a Sequence variable.
	
  Description:    
  	This is a callback function called by SNMP module.
    SNMP user must implement this function in user application and 
    provide appropriate data when called.  This function will only
    be called for OID variable of type sequence.
    
  PreCondition: 
  	None
 
  Parameters:
  	var		-	Variable id whose value is to be returned
  	index   -	Next Index of variable that should be transferred
 
  Return Values:
  	TRUE	-	 If a next index value exists for given variable at given
                 index and index parameter contains next valid index.
    FALSE	-	 Otherwise.
 
  Remarks:
	  Only sequence index needs to be handled in this function.
 ********************************************************************/
BOOL SNMPGetNextIndex(SNMP_ID var, SNMP_INDEX* index)
{
    SNMP_INDEX tempIndex;

    tempIndex = *index;

/*
    switch(var)
    {
    case TRAP_RECEIVER_ID:
        // There is no next possible index if table itself is empty.
        if ( trapInfo.Size == 0u )
            return FALSE;

        // INDEX_INVALID means start with first index.
        if ( tempIndex == (BYTE)SNMP_INDEX_INVALID )
        {
            *index = 0;
            return TRUE;
        }
        else if ( tempIndex < (trapInfo.Size-1) )
        {
            *index = tempIndex+1;
            return TRUE;
        }
        break;
    }
    return FALSE;
*/
return TRUE;

}



/*********************************************************************
  Function:
  	BOOL SNMPIdRecrdValidation(PDU_INFO * pduPtr,OID_INFO *var,BYTE * oidValuePtr,BYTE oidLen)
                                   
  Summary:
  	Used to Restrict the access dynamic and non dynamic OID string for A perticular SNMP Version.

  Description:
 	This is a callback function called by SNMP module. SNMP user must 
 	implement this function as per SNMP version. One need to add the new SNMP
 	MIB IDs hereas per SNMP version.
 	e.g - SYS_UP_TIME (250) is common for V1/V2/V3
 	ENGINE_ID - is the part of V3, So put the all the SNMPv3 var ids within 
 	Macro STACK_USE_SNMPV3_SERVER.   
 	
  PreCondition:
  	None
 
  parameters:
  	var		-	Variable rec whose record id need to be validated
  	oidValuePtr - OID Value
  	oidLen - oidValuePtr length
    
  Return Values:
  	TRUE	-	If a Var ID exists .
    	FALSE 	-	Otherwise.
 
  Remarks:
 	None.
 ********************************************************************/
/*
BOOL SNMPIdRecrdValidation(PDU_INFO * pduPtr,OID_INFO *var,BYTE * oidValuePtr,BYTE oidLen)
{	
	int i=0,j=0;
	int len=0;
	BOOL flag=FALSE;
	BYTE size=0;

	if(var == NULL)
		return FALSE;

#if 0
	
  i = var->id;
  j = 0;

  SEARCH_INDEX(i,j);
 
  if ((SNMP_cmd_tbl[j].param_id == var->id))
  {
	return TRUE;
  }
   else
   {
       return FALSE;
   }	
#endif
    return TRUE;
}
*/

/*********************************************************************
  Function:
  	BOOL SNMPGetVar(SNMP_ID var, SNMP_INDEX index,BYTE* ref, SNMP_VAL* val)
                                   
  Summary:
  	Used to Get/collect OID variable information.

  Description:
 	This is a callback function called by SNMP module. SNMP user must 
 	implement this function in user application and provide appropriate
 	data when called.
   	
  PreCondition:
  	None
 
  parameters:
  	var		-	Variable id whose value is to be returned
    index   -	Index of variable that should be transferred
    ref     -   Variable reference used to transfer
              	multi-byte data
                It is always SNMP_START_OF_VAR when very
                first byte is requested.
                Otherwise, use this as a reference to
                keep track of multi-byte transfers.
    val     -	Pointer to up to 4 byte buffer.
                If var data type is BYTE, transfer data
                  in val->byte
                If var data type is WORD, transfer data in
                  val->word
                If var data type is DWORD, transfer data in
                  val->dword
                If var data type is IP_ADDRESS, transfer data
                  in val->v[] or val->dword
                If var data type is COUNTER32, TIME_TICKS or
                  GAUGE32, transfer data in val->dword
                If var data type is ASCII_STRING or OCTET_STRING
                  transfer data in val->byte using multi-byte
                  transfer mechanism.
 
  Return Values:
  	TRUE	-	If a value exists for given variable at given index.
    FALSE 	-	Otherwise.
 
  Remarks:
 	None.
 ********************************************************************/
BOOL SNMPGetVar(SNMP_ID var, SNMP_INDEX index, BYTE* ref, SNMP_VAL* val)
{
	BYTE fReturn = FALSE;
	char i = 0;
	char j = 0;
	BYTE myRef = *ref;


if(var == DC_ALOLOCK_TRAP || var == DC_BLOLOCK_TRAP)
{
  SEARCH_INDEX(var,i);
 
       fReturn = (*SNMP_cmd_tbl[i].fptr_get) (var, ref, val);
       return fReturn;
}

  switch(var)
  {
	case SYS_UP_TIME:
	case SYS_DESCR1:
	case SYS_CONTACT1:
	case SYS_NAME1:	
	case SYS_LOCATION1:
	{    	
		fReturn = snmp_getSYS_Params(var, ref, val);
		return fReturn;
	}
  }
 
  SEARCH_INDEX(var,i);
 
       fReturn = (*SNMP_cmd_tbl[i].fptr_get) (var, ref, val);
       return fReturn;
}


static DWORD SNMPGetTimeStamp(void)
{

	DWORD_VAL dwvHigh, dwvLow;
    DWORD dw;
    DWORD timeStamp;
	
	//TimeStamp
	// Get all 48 bits of the internal Tick timer
    do
   	{
	   	dwvHigh.Val = TickGetDiv64K();
	   	dwvLow.Val = TickGet();
	} while(dwvHigh.w[0] != dwvLow.w[1]);
    dwvHigh.Val = dwvHigh.w[1];
    
	// Find total contribution from lower DWORD
    dw = dwvLow.Val/(DWORD)TICK_SECOND;
    timeStamp = dw*100ul;
    dw = (dwvLow.Val - dw*(DWORD)TICK_SECOND)*100ul;		// Find fractional seconds and convert to 10ms ticks
    timeStamp += (dw+((DWORD)TICK_SECOND/2ul))/(DWORD)TICK_SECOND;

	// Itteratively add in the contribution from upper WORD
	while(dwvHigh.Val >= 0x1000ul)
	{
		timeStamp += (0x100000000000ull*100ull+(TICK_SECOND/2ull))/TICK_SECOND;
		dwvHigh.Val -= 0x1000;
	}	
	while(dwvHigh.Val >= 0x100ul)
	{
		timeStamp += (0x010000000000ull*100ull+(TICK_SECOND/2ull))/TICK_SECOND;
		dwvHigh.Val -= 0x100;
	}	
	while(dwvHigh.Val >= 0x10ul)
	{
		timeStamp += (0x001000000000ull*100ull+(TICK_SECOND/2ull))/TICK_SECOND;
		dwvHigh.Val -= 0x10;
	}	
	while(dwvHigh.Val)
	{
		timeStamp += (0x000100000000ull*100ull+(TICK_SECOND/2ull))/TICK_SECOND;
		dwvHigh.Val--;
	}
    
    return timeStamp;
}

#endif	//#if defined(STACK_USE_SNMP_SERVER) 
