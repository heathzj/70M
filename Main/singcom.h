#ifndef __SINGCOM_H
#define __SINGCOM_H

#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "HardwareProfile.h"
#include "p18f97j60.h"

#define PC_CMD_SET_IFSWA_1 ((rom char*)"SET IFSWA 1\r")
#define PC_CMD_SET_IFSWA_2 ((rom char*)"SET IFSWA 2\r")
#define PC_CMD_SET_IFSWB_1 ((rom char*)"SET IFSWB 1\r")
#define PC_CMD_SET_IFSWB_2 ((rom char*)"SET IFSWB 2\r")
#define PC_CMD_SET_RFSW1_1 ((rom char*)"SET RFSW1 1\r")
#define PC_CMD_SET_RFSW1_2 ((rom char*)"SET RFSW1 2\r")
#define PC_CMD_SET_RFSW2_1 ((rom char*)"SET RFSW2 1\r")
#define PC_CMD_SET_RFSW2_2 ((rom char*)"SET RFSW2 2\r")
#define PC_CMD_SET_AUTO ((rom char*)"SET AUTO\r")
#define PC_CMD_SET_MANUAL ((rom char*)"SET MANUAL\r")
#define PC_CMD_SET_REF_ON ((rom char*)"SET REF ON\r")
#define PC_CMD_SET_REF_OFF ((rom char*)"SET REF OFF\r")


// .....

#define PC_CMD_GET_STATUS  ((rom char*)"GET STATUS\r")

// Connector JC3
//#define LNB_A_DET
//#define LNB_B_DET
//#define LNB_C_DET
//#define PSU1_STAT
//#define PSU2_STAT
#define OCXO_ONOFF LATFbits.LATF0
#define IF_SW2_IND_A PORTCbits.RC0
#define IF_SW2_IND_B PORTCbits.RC1
#define IF_SW3_IND_A PORTFbits.RF3
#define IF_SW3_IND_B PORTFbits.RF4
#define RF_SW1_IND_A1 PORTFbits.RF5
#define RF_SW1_IND_A2 PORTFbits.RF6
#define RF_SW1_IND_B1 PORTHbits.RH4
#define RF_SW1_IND_B2 PORTHbits.RH5
#define RF_SW2_IND_A1 PORTHbits.RH6
#define RF_SW2_IND_A2 PORTHbits.RH7

//Connector JC1
#define RF_SW1_A LATJbits.LATJ5
#define RF_SW1_B LATJbits.LATJ0
#define RF_SW2_A LATJbits.LATJ4
#define RF_SW2_B LATJbits.LATJ1
#define IF_SW1_A LATBbits.LATB3
#define IF_SW1_B LATBbits.LATB2
#define IF_SW2_A LATBbits.LATB1
#define IF_SW2_B LATEbits.LATE0
#define RF_SW2_IND_B1 PORTEbits.RE1//
#define RF_SW2_IND_B2 PORTBbits.RB4//
#define IF_SW1_IND_A PORTBbits.RB5//
#define IF_SW1_IND_B PORTFbits.RF1//

//Connector JC2
#define ALM_A LATHbits.LATH0
#define ALM_B LATEbits.LATE2
#define ALM_C LATEbits.LATE3
#define ALM_PSU LATEbits.LATE4
#define RF_SW_1 LATEbits.LATE5
#define IF_SW_A LATEbits.LATE6
#define RF_SW_2 LATEbits.LATE7
#define IF_SW_B LATDbits.LATD0


extern unsigned char SW1_STAT;
extern unsigned char SW2_STAT;
extern unsigned char SWA_STAT;
extern unsigned char SWB_STAT;
extern unsigned char RL_STAT;
extern unsigned char AM_STAT;
extern unsigned char R_STAT;
extern unsigned char LNBA_STAT;
extern unsigned char LNBB_STAT;
extern unsigned char LNBC_STAT;
extern unsigned char PSU_STAT;
        
extern unsigned char SW1_STAT_Old;
extern unsigned char SW2_STAT_Old;
extern unsigned char SWA_STAT_Old;
extern unsigned char SWB_STAT_Old;
extern unsigned char RL_STAT_Old;
extern unsigned char AM_STAT_Old;
extern unsigned char R_STAT_Old;
extern unsigned char LNBA_STAT_Old;
extern unsigned char LNBB_STAT_Old;
extern unsigned char LNBC_STAT_Old;
extern unsigned char PSU_STAT_Old;
        
extern unsigned char SW1_SET;
extern unsigned char SW2_SET;
extern unsigned char SWA_SET;
extern unsigned char SWB_SET;
extern unsigned char RL_SET;
extern unsigned char AM_SET;
extern unsigned char R_SET;
        
extern unsigned char SW1_err;
extern unsigned char SW2_err;
extern unsigned char SWA_err;
extern unsigned char SWB_err;
extern unsigned char LNBA_err;
extern unsigned char LNBB_err;
extern unsigned char LNBC_err;
        
extern unsigned char SET_R_LCD;
extern unsigned char SET_AM_LCD;
extern unsigned char SET_SW1_LCD;
extern unsigned char SET_SW2_LCD;
extern unsigned char SET_SWA_LCD;
extern unsigned char SET_SWB_LCD;
extern unsigned char SET_LNBA_LCD;
extern unsigned char SET_LNBB_LCD;
extern unsigned char SET_LNBC_LCD;
extern unsigned char SET_PSU_LCD;
        
extern unsigned rom char Str_R_STAT1[];
extern unsigned rom char Str_R_STAT0[];
extern unsigned rom char Str_AM_STAT1[];
extern unsigned rom char Str_AM_STAT0[];
        
extern unsigned rom char Str_SW1_STAT1_1[];
extern unsigned rom char Str_SW1_STAT1_2[];
extern unsigned rom char Str_SW1_STAT1_3[];
extern unsigned rom char Str_SW1_Refresh[];

extern unsigned rom char Str_SW1_STAT2_1[];
extern unsigned rom char Str_SW1_STAT2_2[];
extern unsigned rom char Str_SW1_STAT2_3[];

extern unsigned rom char Str_SW1_STAT3_1[];
extern unsigned rom char Str_SW1_STAT3_2[];
extern unsigned rom char Str_SW1_STAT3_3[];

extern unsigned rom char Str_SW2_STAT1_1[];
extern unsigned rom char Str_SW2_STAT1_2[];
extern unsigned rom char Str_SW2_STAT1_3[];
extern unsigned rom char Str_SW2_Refresh[];

extern unsigned rom char Str_SW2_STAT2_1[];
extern unsigned rom char Str_SW2_STAT2_2[];
extern unsigned rom char Str_SW2_STAT2_3[];

extern unsigned rom char Str_SW2_STAT3_1[];
extern unsigned rom char Str_SW2_STAT3_2[];
extern unsigned rom char Str_SW2_STAT3_3[];
                                          
extern unsigned rom char Str_SWA_STAT1_1[];
extern unsigned rom char Str_SWA_STAT1_2[];
extern unsigned rom char Str_SWA_STAT1_3[];
extern unsigned rom char Str_SWA_Refresh[];

extern unsigned rom char Str_SWA_STAT2_1[];
extern unsigned rom char Str_SWA_STAT2_2[];
extern unsigned rom char Str_SWA_STAT2_3[];

extern unsigned rom char Str_SWA_STAT3_1[];
extern unsigned rom char Str_SWA_STAT3_2[];
extern unsigned rom char Str_SWA_STAT3_3[];

extern unsigned rom char Str_SWB_STAT1_1[];
extern unsigned rom char Str_SWB_STAT1_2[];
extern unsigned rom char Str_SWB_STAT1_3[];
extern unsigned rom char Str_SWB_Refresh[];

extern unsigned rom char Str_SWB_STAT2_1[];
extern unsigned rom char Str_SWB_STAT2_2[];
extern unsigned rom char Str_SWB_STAT2_3[];

extern unsigned rom char Str_SWB_STAT3_1[];
extern unsigned rom char Str_SWB_STAT3_2[];
extern unsigned rom char Str_SWB_STAT3_3[];
        
extern unsigned rom char Str_LNBA_STAT0[];
extern unsigned rom char Str_LNBA_STAT1[];
extern unsigned rom char Str_LNBA_Refresh[];
        
extern unsigned rom char Str_LNBB_STAT0[];
extern unsigned rom char Str_LNBB_STAT1[];
extern unsigned rom char Str_LNBB_Refresh[];
        
extern unsigned rom char Str_LNBC_STAT0[];
extern unsigned rom char Str_LNBC_STAT1[];
extern unsigned rom char Str_LNBC_Refresh[];
        
extern unsigned rom char Str_PSU_STAT0_1[];
extern unsigned rom char Str_PSU_STAT0_2[];
extern unsigned rom char Str_PSU_STAT1[];
extern unsigned rom char Str_PSU_STAT2[];

void init_singcom_RCU(void);
void Check_SW_Status(void);
void Check_LNAPSU_Status(void);
void Check_Other_Status(void);
void Send_SW(void);
void Send_CTL(void);
void Send_LED(void);
void Send_LCD(void);
void Send_LCD2(void);
void Get_LCD(void);
void delay_RF_SW(void);
void delay_IF_SW(void);
void Send_Status_To_PC(void);

#endif

