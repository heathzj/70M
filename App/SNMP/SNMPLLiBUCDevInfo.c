/***********************************************************/
/*									                       */
/*        For getting Device Information on RCU  		   */
/*											               */
/***********************************************************/

#include "SNMPLL.h"
#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "SNMP.h"

extern char FirmwareVersion[4];

extern BYTE global_char_temp[15];
BYTE myRef;
IP_ADDR TEMP_IP;
 
#if defined(STACK_USE_SNMP_SERVER)
DWORD AppUtil_dword_swap(DWORD val)
{
	 return(DWORD)(((val<<24ul)&0xff000000)
			      |((val<<8ul)&0x00ff0000)
				  |((val>>8ul)&0x0000ff00)
				  |((val>>24ul)&0x000000ff));
}



/*      This for getting Manager IP              	   */
BYTE snmpll_getMANAGERIP(BYTE var, BYTE* ref, SNMP_VAL* val)
{
	myRef = *ref;
	if ( Manager_IP.Val == 0u )
    {
		myRef = SNMP_END_OF_VAR;
    }
	else
    {
       	val->dword = AppUtil_dword_swap(Manager_IP.Val);
        myRef = SNMP_END_OF_VAR;
    }  
    *ref = myRef;
    return TRUE;	
}	


/*      This for setting Manager IP              	   */
BYTE snmpll_setMANAGERIP(BYTE var, BYTE* ref, SNMP_VAL* val)
{
    myRef = *ref;
	TEMP_IP.Val = val->dword;
		
        Manager_IP.v[0] = TEMP_IP.v[3];
        Manager_IP.v[1] = TEMP_IP.v[2];
        Manager_IP.v[2] = TEMP_IP.v[1];
        Manager_IP.v[3] = TEMP_IP.v[0];

        Read2[0][0] = Manager_IP.v[0];
        Read2[0][1] = Manager_IP.v[1];
        Read2[0][2] = Manager_IP.v[2];
        Read2[0][3] = Manager_IP.v[3];
				
		SaveSetting();
        return TRUE;
}



/*      This for getting SSPA Device IP              	   */
BYTE snmpll_getDEVICEIP(BYTE var, BYTE* ref, SNMP_VAL* val)	
{	
      myRef = *ref;
	if ( AppConfig.MyIPAddr.Val == 0u )
	{	
		myRef = SNMP_END_OF_VAR;
	}
    else
    {
       	val->dword = AppUtil_dword_swap(AppConfig.MyIPAddr.Val);
        myRef = SNMP_END_OF_VAR;
    }  
	 *ref = myRef;
	 return TRUE;
}


/*      This for setting SSPA Device IP              	   */
BYTE snmpll_setDEVICEIP(BYTE var, BYTE* ref, SNMP_VAL* val)	
{
	
      if ( AppConfig.MyIPAddr.Val == 0u )
            myRef = SNMP_END_OF_VAR;
       else
      {
			AppConfig.MyIPAddr.Val = AppUtil_dword_swap(val->dword);
            myRef = SNMP_END_OF_VAR;
       }  

        *ref = myRef;
		SaveAppConfig();
		SaveSetting();
        return TRUE;
}



/*      This for getting RCU,PM1, PM2 and BUC Firmware Version               */
BYTE snmpll_getRCU_SNMP_FIRMWAREVERSION(BYTE var, BYTE *ref, SNMP_VAL *val)
{
  myRef = *ref;

  if(FirmwareVersion[0] == 0u)
     myRef  = SNMP_END_OF_VAR;
	 
  else
  {
   switch(var)
	{
	  case DC_FIRMWAREVERSION:
		val->byte = FirmwareVersion[myRef++];
		break;
	}

	if(FirmwareVersion[myRef] == 0)
	   myRef  = SNMP_END_OF_VAR;
  }
  *ref = myRef;
  return TRUE;
}


/*      This for getting Manager IP              	   */
BYTE snmp_get_trap_resp(BYTE var, BYTE* ref, SNMP_VAL* val)
{
  BYTE index = 0;
  myRef = *ref;
  
 switch(var)
  {
 	case DC_ALOLOCK_TRAP:
		if ( index < trapInfo.Size )
        	{
           	 	val->byte = index;
           		return TRUE;
        	}
		break;
	case DC_BLOLOCK_TRAP:
		 if ( index < trapInfo.Size )
         {
            if ( trapInfo.table[index].communityLen == 0u )
                *ref = SNMP_END_OF_VAR;
            else
            {
                val->byte = trapInfo.table[index].community[myRef];

                myRef++;

                if ( myRef == trapInfo.table[index].communityLen )
                    *ref = SNMP_END_OF_VAR;
                else
                    *ref = myRef;
            }
            return TRUE;
         }
		break;
  } 

}

#endif
