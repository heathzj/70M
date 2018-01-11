/* This file consists of all the command table implementation */

#include"SNMPLL.h"


typedef BYTE (*_CMD_Tbl_fptr_t) (BYTE ,BYTE*, SNMP_VAL*);

typedef struct SNMP_cmd_tbl_block_s
  {
	  char param_id;
	  _CMD_Tbl_fptr_t  fptr_get;
      _CMD_Tbl_fptr_t  fptr_set;
  }SNMP_cmd_tbl_block_t;


#define CMD_TBL_SIZE_MAX  (sizeof(SNMP_cmd_tbl)/sizeof(SNMP_cmd_tbl_block_t))



#define SEARCH_INDEX(var,i)  {while((!(SNMP_cmd_tbl[i].param_id == var)) && (i < CMD_TBL_SIZE_MAX)){i++;}}



#if !defined DEFINE_SNMP_GLOBAL_VAR

#define DEFINE_SNMP_GLOBAL_VAR

#pragma udata gpr8
const SNMP_cmd_tbl_block_t SNMP_cmd_tbl[]=
	{
/***************************************TRAPINFO**********************************/
		{DC_ALOLOCK_TRAP,		  &snmp_get_trap_resp	,	  		  NULL},
//		{TRAP_RECEIVER_ENABLED,   &							,			  NULL},
//		{TRAP_RECEIVER_IP,		  &							,			  NULL},
		{DC_BLOLOCK_TRAP,		  &snmp_get_trap_resp	,	  		  NULL},
/***************************************DevInfo***********************************/
		{MANAGERIP,        		 &snmpll_getMANAGERIP,             &snmpll_setMANAGERIP},
		{DEVICEIP,   	         &snmpll_getDEVICEIP,              &snmpll_setDEVICEIP},
		{DC_FIRMWAREVERSION,     &snmpll_getRCU_SNMP_FIRMWAREVERSION,    NULL},
/************************************OPERATION************************************/
		{DC_AATTENUATION,     		  &snmpll_getOPERATION,      	      &snmpll_setOPERATION},
		{DC_BATTENUATION,     		  &snmpll_getOPERATION,      	      &snmpll_setOPERATION},
		{DC_ALOFREQ,     		  &snmpll_getOPERATION,      	      &snmpll_setOPERATION},
		{DC_BLOFREQ,     		  &snmpll_getOPERATION,      	      &snmpll_setOPERATION},
/***************************************ALARMS************************************/
		{DC_ALOLOCK,        &snmpll_getALARM_STATUS,	      NULL},
		{DC_BLOLOCK,		  &snmpll_getALARM_STATUS,	      NULL},
};

 #else

 extern const SNMP_cmd_tbl_block_t SNMP_cmd_tbl[];
 extern const _CMD_Tbl_fptr_t cmd_tbl_fptr_array[];
 
 #define CMD_TBL_SIZE_MAX  (sizeof(SNMP_cmd_tbl)/sizeof(SNMP_cmd_tbl_block_t))
 extern APP_CONFIG newAppConfig;
 #define SEARCH_INDEX(var,i)  {while((!(SNMP_cmd_tbl[i].param_id == var))){i++;}} 

 #endif

