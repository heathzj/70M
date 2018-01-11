/************************************************************/
/* This file is to handle the SYSDESC Parameter Function    */
/************************************************************/

#include "SNMPLL.h"
extern BYTE myRef;

#if defined(STACK_USE_SNMP_SERVER)

    DWORD_VAL dwvHigh ,dwvLow;
	DWORD dw;
    DWORD dw10msTicks;

/* The Set System Parameters */

BOOL snmpll_setSYS_Params(SNMP_ID var, BYTE ref, BYTE val)
{	
	if((var == SYS_DESCR1)
	 &&(ref != SNMP_END_OF_VAR)
	 &&(ref < 30)
	   )
		{
			systeminfo1.SYSDESCR1[ref] = val;
			systeminfo1.SYSDESCR1[ref+1] = 0;   
		}
	
	else if((var == SYS_CONTACT1)
		  &&(ref != SNMP_END_OF_VAR)
		  &&(ref < 30)
			)
        {
             systeminfo1.SYSCONTACT1[ref] = val;
             systeminfo1.SYSCONTACT1[ref+1] = 0; 
        }

	else if((var == SYS_NAME1)
		  &&(ref != SNMP_END_OF_VAR)
		  &&(ref < 30)
			)
        {
             systeminfo2.SYSNAME1[ref] = val;
             systeminfo2.SYSNAME1[ref+1] = 0;            
        }

	else if((var == SYS_LOCATION1)
		  &&(ref != SNMP_END_OF_VAR)
		  &&(ref < 30)
			)
		{	
             systeminfo2.SYSLOCATION1[ref] = val;
             systeminfo2.SYSLOCATION1[ref+1] = 0;            
        }
	
	if ( ref < 30) 
    {
        SaveSetting();
        return TRUE;
    }
}




/* The Get System Parameters */

BOOL snmp_getSYS_Params(SNMP_ID var, BYTE *ref, SNMP_VAL* val)
{

    if(var == SYS_UP_TIME)
	{
        do
	   	{
		   	dwvHigh.Val = TickGetDiv64K();
		   	dwvLow.Val = TickGet();
		} while(dwvHigh.w[0] != dwvLow.w[1]);
	    dwvHigh.Val = dwvHigh.w[1];
	    
		// Find total contribution from lower DWORD
	    dw = dwvLow.Val/(DWORD)TICK_SECOND;
	    dw10msTicks = dw*100ul;
	    dw = (dwvLow.Val - dw*(DWORD)TICK_SECOND)*100ul;		// Find fractional seconds and convert to 10ms ticks
	    dw10msTicks += (dw+((DWORD)TICK_SECOND/2ul))/(DWORD)TICK_SECOND;

		// Itteratively add in the contribution from upper WORD
		while(dwvHigh.Val >= 0x1000ul)
		{
			dw10msTicks += (0x100000000000ull*100ull+(TICK_SECOND/2ull))/TICK_SECOND;
			dwvHigh.Val -= 0x1000;
		}	
		while(dwvHigh.Val >= 0x100ul)
		{
			dw10msTicks += (0x010000000000ull*100ull+(TICK_SECOND/2ull))/TICK_SECOND;
			dwvHigh.Val -= 0x100;
		}	
		while(dwvHigh.Val >= 0x10ul)
		{
			dw10msTicks += (0x001000000000ull*100ull+(TICK_SECOND/2ull))/TICK_SECOND;
			dwvHigh.Val -= 0x10;
		}	
		while(dwvHigh.Val)
		{
			dw10msTicks += (0x000100000000ull*100ull+(TICK_SECOND/2ull))/TICK_SECOND;
			dwvHigh.Val--;
		}
	    
        val->dword = dw10msTicks;
        return TRUE;
	}


	else if (var == SYS_CONTACT1)
    {
        myRef = *ref;

        if ( systeminfo1.SYSCONTACT1[0] == 0u )
            myRef = SNMP_END_OF_VAR;
        else
        {
            val->byte = systeminfo1.SYSCONTACT1[myRef++];
            if ( systeminfo1.SYSCONTACT1[myRef] == 0u )
                myRef = SNMP_END_OF_VAR;
        }

        *ref = myRef;

        return TRUE;
    }


else if (var == SYS_NAME1)
    {
         myRef = *ref;
	        if ( systeminfo2.SYSNAME1[0] == 0u )
            myRef = SNMP_END_OF_VAR;
        else
        {
            val->byte = systeminfo2.SYSNAME1[myRef++];
            if ( systeminfo2.SYSNAME1[myRef] == 0u )
                myRef = SNMP_END_OF_VAR;
        }

        *ref = myRef;

        return TRUE;
    }


else if (var == SYS_LOCATION1)
  {
	    myRef = *ref;
        if ( systeminfo2.SYSLOCATION1[0] == 0u )
            myRef = SNMP_END_OF_VAR;
        else
        {
            val->byte = systeminfo2.SYSLOCATION1[myRef++];
            if ( systeminfo2.SYSLOCATION1[myRef] == 0u )
                myRef = SNMP_END_OF_VAR;
        }

        *ref = myRef;
		return TRUE;
  }
	  else if(var == SYS_DESCR1)
    {
        myRef = *ref;
        if ( systeminfo1.SYSDESCR1[0] == 0u )
            myRef = SNMP_END_OF_VAR;
        else
        {
            val->byte = systeminfo1.SYSDESCR1[myRef++];
            if ( systeminfo1.SYSDESCR1[myRef] == 0u )
                myRef = SNMP_END_OF_VAR;
        }
        *ref = myRef;
        return TRUE;
    }
  
else 
	return FALSE;
}




#endif
