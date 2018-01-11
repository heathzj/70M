#ifndef __EEPROM_H
#define __EEPROM_H
/*-----------------------------------------------------------------------------
*
* Copyright (c) 2006-2009, ST Electronics (Satcom & Sensor Systems) Pte Ltd
* All rights reserved.
*
* DESCRIPTION:
* 
* PROJECT NAME: SSPA_RCU M&C Firmware  
*
* AUTHOR: Wu Zhixian
*
* DATE: 15/07/2009 
*
* ABSTRACT: 
*    This firmware is for RCU M&C borad using PIC18F8720 MCU.
*    It acts as a intermedia to realize communications 
*    between a VB written data fusing software running on a PC
*    and the RCU unit connected to M&C borad. 
*
*
*    The firmware receives commands through serial port and 
*    do corresponding actions, such as do auto/manual 
*    switch through CPLD etc.
*
* ---------------------------------------------------------------------------*/
/*---------------------
    REVISION HISTORY
---------------------*/
/*-----------------------------------------------------------------------------
NAME            DATE        BUGID#         
------------    ----------  ----------
DESCRIPTION
---------------------------------------
Wu Zhixian     15/07/2009                
First release version  
------------------------------------------------------------------------------*/
/*--------------
    INCLUDES 
--------------*/
#include "define.h"
#include "HardwareProfile.h"

#if defined(EEPROM_CS_TRIS)	
#error "Target must have internal EEPROM!"
#endif

/*------------
    MACROS 
------------*/
#define DISABLE_INTERRUPTS() {while(INTCONbits.GIE) INTCONbits.GIE=0;}  
#define ENABLE_INTERRUPTS() {INTCONbits.GIE=1;}  

#if 0 // yt: already defined in define.h

/* define eeprom address */
#define EEADR_ID           0x00

#define EEADR_Resistor     0x03
#define EEADR_RF1_ROUT     EEADR_Resistor     
#define EEADR_RF1_RSENSE   (EEADR_Resistor + 0x02)    
#define EEADR_RF2_ROUT     (EEADR_Resistor + 0x04)        
#define EEADR_RF2_RSENSE   (EEADR_Resistor + 0x06)            
#define EEADR_FAN_ROUT     (EEADR_Resistor + 0x08)            
#define EEADR_FAN_RSENSE   (EEADR_Resistor + 0x0A)        

#define EEADR_BUC_ID       0x0D

#define EEADR_alarm_limit                    0x10    
#define EEADR_sspa_temp_thd_degree           EEADR_alarm_limit        
#define EEADR_shutdown_temperature_degree    (EEADR_alarm_limit + 0x01)        
#define EEADR_recovery_temperature_degree    (EEADR_alarm_limit + 0x02) 
#define EEADR_rfout_thd_dBm                  (EEADR_alarm_limit + 0x03) 
#define EEADR_rf_current_high_thd_A          (EEADR_alarm_limit + 0x04)   // 2 bytes, by 0.1A
#define EEADR_rf_current_low_thd_A           (EEADR_alarm_limit + 0x06)   // 2 bytes, by 0.1A
#define EEADR_fan_current_high_thd_A         (EEADR_alarm_limit + 0x08)   // 2 bytes, by 0.1A
#define EEADR_fan_current_low_thd_A          (EEADR_alarm_limit + 0x0A)   // 2 bytes, by 0.1A

#define EEADR_alarm_enable         0x1C     
#define EEADR_module_num           0x1D 

#define EEADR_PartNo               0x20 //30 bytes
#define EEADR_SerialNo             0x3E //30 bytes

#define EEADR_fuse_rfout_freqmin   0x5C
#define EEADR_rfout_num            EEADR_fuse_rfout_freqmin
#define EEADR_rfout_offset         (EEADR_fuse_rfout_freqmin + 0x01) 
#define EEADR_rfout_power          (EEADR_fuse_rfout_freqmin + 0x02) //30 bytes

#define EEADR_fuse_rfout_freqmid   0x8E
#define EEADR_rfout_num_freqmid    EEADR_fuse_rfout_freqmid
#define EEADR_rfout_offset_freqmid (EEADR_fuse_rfout_freqmid + 0x01) 
#define EEADR_rfout_power_freqmid  (EEADR_fuse_rfout_freqmid + 0x02) //30 bytes

#define EEADR_fuse_rfout_freqmax   0xC0
#define EEADR_rfout_num_freqmax    EEADR_fuse_rfout_freqmax
#define EEADR_rfout_offset_freqmax (EEADR_fuse_rfout_freqmax + 0x01) 
#define EEADR_rfout_power_freqmax  (EEADR_fuse_rfout_freqmax + 0x02) //30 bytes


#define		EEADR_rf_reflect_recover			0xFE
#define		EEADR_rf_reflect_end				0xFF
#define		EEADR_rf_reflect_start				0x100
#define		EEADR_rf_reflect_num				(EEADR_rf_reflect_start + 0x01) 
#define		EEADR_rf_reflect_power				(EEADR_rf_reflect_start + 0x02) // 90 bytes

#define EEADR_ODU1_ID       0x200
#define EEADR_ODU2_ID       0x203
#define EEADR_ODU3_ID       0x206
#define EEADR_RCU_ID        0x209
#define EEADR_RCU_ALARM     0x210 // 6 bytes
#define EEADR_RCU_Switch1_Mode     0x216 
#define EEADR_RCU_Switch2_Mode     0x217
#define EEADR_RCU_Switch1_Pos      0x218
#define EEADR_RCU_Switch2_Pos      0x219
#define EEADR_RCU_Default_Unit     0x21A
#define EEADR_Rx_RCU_Attenuator0   0x21B
#define EEADR_Rx_RCU_Attenuator1   0x21C

#define EEADR_Rx_A_ALARM_LIMIT1  	   0x21D
#define EEADR_Rx_A_ALARM_LIMIT2  	   0x21E
#define EEADR_Rx_B_ALARM_LIMIT1  	   0x21F
#define EEADR_Rx_B_ALARM_LIMIT2  	   0x220
#define EEADR_Rx_A_ALARM_LIMIT_CENTER  0x221
#define EEADR_Rx_B_ALARM_LIMIT_CENTER  0x222

#define EEADR_Rx_Atten_Enable  	   		0x250

#endif // #if 0

/*---------------------------------
    GLOBAL FUNCTIONS PROTOTYPES
---------------------------------*/ 
BYTE EEpromGet(WORD addr);
void EEpromPut(WORD addr, BYTE data);
void EEpromRead(WORD addr, BYTE *data, WORD len);
void EEpromWrite(WORD addr, BYTE *data, WORD len);

#endif //__EEPROM_H


