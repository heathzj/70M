/****************************************************************/
/*												                */
/* This is for getting Device Status & Alarm  for both BUCs		*/
/*												                */	
/****************************************************************/

#include "SNMPLL.h"
#include "singcom.h"

#if defined(STACK_USE_SNMP_SERVER)

extern BYTE myRef;

/********************************************************************/
/*												                    */
/* This is for getting Device Status & Alarm  for both all the iBUC */
/*												                    */	
/********************************************************************/


/********************************************************************/
/**************************ALARMS************************************/
/********************************************************************/

BYTE snmpll_getALARM_STATUS(BYTE mib_index, BYTE* ref, SNMP_VAL* val)
{
  BYTE num = 2;          /* Indicating No Alarm initially */
 	switch(mib_index)
 	{
		case DC_ALOLOCK:
			//num =(ConverterAStatus == 0)?1:0;
        	break;
		case DC_BLOLOCK:
			//num =(ConverterBStatus == 0)?1:0;
        	break;
		default:
			return FALSE;
 	}
	
     val->byte = num;
	 return TRUE;
}

#endif

