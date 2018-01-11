/***********************************************************/
/*									                       */
/* For getting & Setting Device Operation on both BUCs     */
/*											               */
/***********************************************************/
#include "SNMPLL.h"
#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "SNMP.h"
#include "singcom.h"

#if defined(STACK_USE_SNMP_SERVER)


extern char AttenString1[]; 
extern char AttenString2[]; 



/*      This for ge"tting startup rfOperation of SSPA		   */
BYTE snmpll_getOPERATION(BYTE var, BYTE *ref, SNMP_VAL *val)
{
	switch(var)
	{

		case DC_AATTENUATION:
	        myRef = *ref;
	
	        if ( AttenString1[0] == 0u )
	            myRef = SNMP_END_OF_VAR;
	        else
	        {
	            val->byte = AttenString1[myRef++];
	            if ( AttenString1[myRef] == 0u )
	                myRef = SNMP_END_OF_VAR;
	        }

	        *ref = myRef;
			break;

		case DC_BATTENUATION:
	        myRef = *ref;
	
	        if ( AttenString2[0] == 0u )
	            myRef = SNMP_END_OF_VAR;
	        else
	        {
	            val->byte = AttenString2[myRef++];
	            if ( AttenString2[myRef] == 0u )
	                myRef = SNMP_END_OF_VAR;
	        }

	        *ref = myRef;
			break;
	}

	return TRUE;
}

/*      This for setting rfOperation of SSPA  		   */
BYTE snmpll_setOPERATION(BYTE var, BYTE *ref, SNMP_VAL *val)
{
	BYTE tempRef, tempVal;

    tempRef = *ref;
	tempVal = *(BYTE *)val;
	switch(var)
	{


		case DC_AATTENUATION:
			if((tempRef != SNMP_END_OF_VAR) && (tempRef < 30))
		    {
		    	AttenString1[tempRef] = tempVal;
		        AttenString1[tempRef+1] = 0; 
				// if ((tempRef == 0) && ((tempVal >= '0') && (tempVal <= '9')))
					// ConverterAAtten = tempVal - '0';
				// else if ((tempVal >= '0') && (tempVal <= '9'))
					// ConverterAAtten = (ConverterAAtten * 10) + (DWORD)(tempVal - '0'); 
		    }
			break;

		case DC_BATTENUATION:
			if((tempRef != SNMP_END_OF_VAR) && (tempRef < 30))
		    {
		    	AttenString2[tempRef] = tempVal;
		        AttenString2[tempRef+1] = 0; 
				// if ((tempRef == 0) && ((tempVal >= '0') && ((tempVal <= '9'))))
					// ConverterBAtten = tempVal - '0';
				// else if ((tempVal >= '0') && (tempVal <= '9'))
					// ConverterBAtten = (ConverterBAtten * 10) + (DWORD)(tempVal - '0'); 
		    }
			break;

		default:
			return FALSE;
	}

   return TRUE;
}

#endif
