/*
 * Copyright (C) 2012  SINGCOM Pte Ltd 
 *
 * RCU Low Level Access Header
 *
 */

#ifndef _RCULLACCESS_H_
#define _RCULLACCESS_H_

#include "define.h"

//Hardware pin mapping
//#define PS1_DET	4 // 0
//#define	PS2_DET 5 // 1
//#define OCXO1_DET 1
//#define	OCXO2_DET 2 //1

#define OCXO1_DET 	0
#define	OCXO2_DET 	1

#ifdef RCU_OUTDOOR
#define PS1_DET		3
#define	PS2_DET 	4
#else
#define PS1_DET		0
#define	PS2_DET 	7
#endif

#define STATE_REF1_OK	(1<<0)
#define STATE_REF2_OK	(1<<1) //0x02
#define STATE_PS1_OK	(1<<2) //0x04
#define STATE_PS2_OK	(1<<3) //0x08

#define ALARM_THRESHOLD 0x80

typedef struct RCULLDCB_s{
	BYTE PATH_ALARM_1_Value;  //CPLD Reading 1 to generate path alarm
	BYTE PATH_ALARM_2_Value;  //CPLD Reading 2 to generate path alarm
	BYTE PATH_ALARM_3_Value;  //CPLD Reading 3 to generate path alarm
	BYTE PATH_ALARM_4_Value;  //CPLD Reading 4 to generate path alarm

	BYTE RCU_Tx_Alarm[3];     //path A alarm
	BYTE RCU_Rx_Alarm[3];	  //path B alarm
	BYTE Switch_Status[2];		//online /offline status		
	BYTE RCU_Tx_Alarm_Enable[3];
	BYTE RCU_Rx_Alarm_Enable[3];	
	BYTE current_mode[2]; 		//Swiching mode
	BYTE current_position[2];	//Switch position
	//BYTE UnitPosition;			//unit position
	BYTE AlarmState;			//Other alarms besides path
	BYTE OCXO1_Hex;
	BYTE OCXO2_Hex;
	BYTE PS1_Hex;
	BYTE PS2_Hex;	



}RCULLDCB_t;



// CPLD I/OPin, 0~5 is FormC pin, 6~13 is J26-1/3/5/7/9/11/13/15
// 14~20 is J27-1/3/5/7/9/11/13, 21 is J27-15 more current pin

#define  PORT_LED_GREEN         15
#define  PORT_LED_RED           14
#define  TX_STATUS1           	16
#define  PORT_LED_GREEN1        17
#define  PORT_LED_RED1          18
#define  PORT_SSPA_ON_OFF1      22
#define  PORT_SSPA_ON_OFF2      23


//extra I/OPins for LNB RCU
#define	TONEA_EN	7
#define	TONEB_EN	9

#define	LNB_ALRMA	6
#define	LNB_ALRMB	8

#define I2C_ADDRA	12
#define I2C_ADDRB	10

#define RX_REF_SW	19


// Used to Chip Selelct enable or disable 
#define CS_ENABLE       0
#define CS_DISABLE      1

#define CS_CPLD					PORTDbits.RD0  		//RD0
#define CS_FLASH				PORTDbits.RD1  		//RD1
#define CS_ADC1					PORTDbits.RD2  		//RD2
#define CS_ADC0					PORTDbits.RD3  		//RD3

// used to work with modes of CPLD 
#define SWITCH_MODE				PORTHbits.RH0  		//RH0, CPLDUCBUS0
#define SET_SWITCH1_POS			PORTHbits.RH1  		//RH1, CPLDUCBUS1
#define SET_SWITCH2_POS			PORTHbits.RH2  		//RH2, CPLDUCBUS2
#define READ_SWITCH1_POS		PORTHbits.RH3  		//RH3, CPLDUCBUS3
#define READ_SWITCH2_POS		PORTHbits.RH4  		//RH4, CPLDUCBUS4
#define PATH_ALARM_1			PORTHbits.RH5  		//RH5, CPLDUCBUS5
#define PATH_ALARM_2			PORTHbits.RH6  		//RH6, CPLDUCBUS6
#define PATH_ALARM_3			PORTHbits.RH7  		//RH7, CPLDUCBUS7
#define PATH_ALARM_4			PORTFbits.RF2  		//RF2, CPLDUCBUS8
#define CPLDUCBUS9				PORTFbits.RF3  		//RF3
#define CPLDUCBUS10				PORTFbits.RF4  		//RF4
#define CPLDUCBUS11				PORTFbits.RF5  		//RF5
#define CPLDUCBUS12				PORTFbits.RF6  		//RF6
#define CPLDUCBUS13				PORTFbits.RF7  		//RF7

#define FAN_ALARM				PORTDbits.RD7
#define FAN_CLEAR				PORTGbits.RG5


#define  RESERVE_BYTE           0xFF


#define Online		1
#define Standby		0

// Used to enable or disable 
#define Alarm_Enable       1
#define Alarm_Disable      0

#define ON         			1
#define OFF           		0


// yt: todo, shift below from protocolprocess.h to somewhere else

#if defined(__18F97J60) || defined(_18F97J60)
#define EEADR_START_OFFSET			0x19B//191	
#else
#define EEADR_START_OFFSET			0x0  // PIC18F8722 internal EEPROM
#endif

#define EEADR_PartNo          	      	(EEADR_START_OFFSET + 0x20) //30 bytes
#define EEADR_SerialNo         		    (EEADR_START_OFFSET + 0x3E) //30 bytes

#define EEADR_RCU_ID        			(EEADR_START_OFFSET + 0x209)
#define EEADR_RCU_ALARM     			(EEADR_START_OFFSET + 0x210) // 6 bytes
#define EEADR_RCU_Switch1_Mode     		(EEADR_START_OFFSET + 0x216) 
#define EEADR_RCU_Switch2_Mode     		(EEADR_START_OFFSET + 0x217)
#define EEADR_RCU_Switch1_Pos      		(EEADR_START_OFFSET + 0x218)
#define EEADR_RCU_Switch2_Pos      		(EEADR_START_OFFSET + 0x219)

#define EEADR_Rx_RCU_Attenuator0   		(EEADR_START_OFFSET + 0x21B)
#define EEADR_Rx_RCU_Attenuator1   		(EEADR_START_OFFSET + 0x21C)

#define EEADR_Rx_A_ALARM_LIMIT1 		(EEADR_START_OFFSET + 0x21D)
#define EEADR_Rx_A_ALARM_LIMIT2  		(EEADR_START_OFFSET + 0x21E)
#define EEADR_Rx_B_ALARM_LIMIT1  		(EEADR_START_OFFSET + 0x21F)
#define EEADR_Rx_B_ALARM_LIMIT2  		(EEADR_START_OFFSET + 0x220)
#define EEADR_Rx_A_ALARM_LIMIT_CENTER  	(EEADR_START_OFFSET + 0x221)
#define EEADR_Rx_B_ALARM_LIMIT_CENTER  	(EEADR_START_OFFSET + 0x222)

#define EEADR_COMMODE        			(EEADR_START_OFFSET + 0x243)
#define EEADR_RCU_Enable_Option			(EEADR_START_OFFSET + 0x248)
#define EEADR_Rx_Atten_Enable  	   		(EEADR_START_OFFSET + 0x250)

#define	Extend_IO_0			0
#define	Extend_IO_1			1
#define	Extend_IO_2			2
#define	Extend_IO_3			3
#define	Extend_IO_4			4
#define	Extend_IO_5			5
#define	Extend_IO_6			6
#define	Extend_IO_7			7
#define	Extend_IO_8			8
#define	Extend_IO_9			9
#define	Extend_IO_10		10
#define	Extend_IO_11		11
#define	Extend_IO_12		12
#define	Extend_IO_13		13
#define	Extend_IO_14		14
#define	Extend_IO_15		15
#define	Extend_IO_16		16
#define	Extend_IO_17		17
#define	Extend_IO_18		18
#define	Extend_IO_19		19
#define	Extend_IO_20		20
#define	Extend_IO_21		21
#define	Extend_IO_22		22
#define	Extend_IO_23		23






/*
// used to work with modes of CPLD 
#define SWITCH_MODE				PORTHbits.RH0  		//RH0, CPLDUCBUS0
#define SET_SWITCH1_POS			PORTHbits.RH1  		//RH1, CPLDUCBUS1
#define SET_SWITCH2_POS			PORTHbits.RH2  		//RH2, CPLDUCBUS2
#define READ_SWITCH1_POS		PORTHbits.RH3  		//RH3, CPLDUCBUS3
#define READ_SWITCH2_POS		PORTHbits.RH4  		//RH4, CPLDUCBUS4
#define PATH_ALARM_1			PORTHbits.RH5  		//RH5, CPLDUCBUS5
#define PATH_ALARM_2			PORTHbits.RH6  		//RH6, CPLDUCBUS6
#define PATH_ALARM_3			PORTHbits.RH7  		//RH7, CPLDUCBUS7

#define PATH_ALARM_4			PORTFbits.RF2  		//RF2, CPLDUCBUS8
#define CPLDUCBUS9				PORTFbits.RF3  		//RF3
#define CPLDUCBUS10				PORTFbits.RF4  		//RF4
#define CPLDUCBUS11				PORTFbits.RF5  		//RF5
#define CPLDUCBUS12				PORTFbits.RF6  		//RF6
#define CPLDUCBUS13				PORTFbits.RF7  		//RF7
*/




#define Online		1
#define Standby		0

extern RCULLDCB_t RCU0;

void RCULLInit(void);
void RCULLGetRCUAlarmStatus(void);
void RCULLSetMode(UINT8 u8RCUMode);
void RCULLSetPath(UINT8 u8RCUPath);
void RCULLSelectManualMode(void);
void RCULLSelectAutoMode(void);
void TxAActivate(void);
void TxBActivate(void);
void RxAActivate(void);
void RxBActivate(void);
void RCULLSetComMode(UINT8 comMode);

void RCULLSetDefaultValue(void);

#endif // #ifndef _RCUHLACCESS_H_


