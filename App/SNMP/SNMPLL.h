#include "Global.h"
#include "AppUtil.h"
#include "TCPIP Stack/SNMP.h"
#include "mib.h"
//#include "BUCHLAccess.h"


BOOL snmp_getSYS_Params(SNMP_ID var, BYTE *ref, SNMP_VAL* val);
BOOL snmpll_setSYS_Params(SNMP_ID, BYTE, BYTE);

BYTE snmp_get_trap_resp(BYTE, BYTE*, SNMP_VAL*);


/***************************************DevInfo***********************************/
BYTE snmpll_getMANAGERIP(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_setMANAGERIP(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getDEVICEIP(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_setDEVICEIP(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getDEVICEID(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_setDEVICEID(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getMODELNO(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getSERIALNO(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getRCU_SNMP_FIRMWAREVERSION(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getOPERATION(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_setOPERATION(BYTE, BYTE*, SNMP_VAL*);


/***************************************STATUS************************************/
BYTE snmpll_getINPUT_POWERLEVEL(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getOUTPUT_POWERLEVEL(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getTEMPERATURE(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getTONE(BYTE, BYTE*, SNMP_VAL*);

/***************************************ALARMS************************************/
BYTE snmpll_getALARM_STATUS(BYTE, BYTE*, SNMP_VAL*);

/************************************OPERATION************************************/
BYTE snmpll_getRF_OUTPUT(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_setRF_OUTPUT(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getRF_OUTPUT_STARTUP(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_setRF_OUTPUT_STARTUP(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getUSRATTN(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_setUSRATTN(BYTE, BYTE*, SNMP_VAL*);
BYTE snmpll_getSWLO(BYTE var, BYTE *ref, SNMP_VAL *val);
BYTE snmpll_setSWLO(BYTE var, BYTE *ref, SNMP_VAL *val);
BYTE snmpll_getBANDSELECT(BYTE var, BYTE *ref, SNMP_VAL *val);
BYTE snmpll_setBANDSELECT(BYTE var, BYTE *ref, SNMP_VAL *val);


extern BYTE myRef;
extern IP_ADDR Manager_IP;
extern TRAP_INFO trapInfo;

