#ifndef _COMM_H
#define _COMM_H
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
#include    "define.h"

/*------------
    MACROS 
------------*/

/* define control pin */
// SIO0, M&C1 RS485 to PC/ASRC
// SIO1, M&C2 RS485 to PC/ASRC
// SIO2
// SIO3, , connect J5 to J2, communicate with BUC
#define SIO0          0
#define SIO1          1
#define SIO2          2
#define SIO3          3

#define START_PROMPT_NEW    0x5A
#define ACK_OK				'P'

#define RCU_TYPE_ID			'R'
#define PC_TYPE_ID			'A'

#define POS_SRC_ID_NEW      1
#define POS_DES_ID_NEW      3
#define POS_CMD_NEW         5
#define POS_ACK_NEW         9
#define POS_DATA_LEN_NEW    8
#define POS_DATA_NEW        9

#define START_PROMPT   0x47
#define END_PROMPT     0x0D
#define BUFFER_LEN     78

/* define positions of frame */
#define POS_START       0
#define POS_SRC_ID      1
#define POS_DES_ID      4
#define POS_CMD         7
#define POS_DATA_LEN    9
#define POS_DATA        10   

#define MaxBUCCmd		5

#define BAUD_9600		0
#define BAUD_115200		1

typedef struct CommandBuffer
{
	unsigned char CmdByte0;
	unsigned char CmdByte1;
	unsigned char CmdLength;
	unsigned char CmdData[30];
} BUCCMDBuffer;

/*---------------------------------
    GLOBAL FUNCTIONS PROTOTYPES
---------------------------------*/      
void PollingDevice(void);

void Rx0Process(void);
void SendMessage(unsigned char sio, 
				 char *src_id1,
                 char *des_id1, 
                 const rom char *cmd, 
                 unsigned char length, 
                 unsigned char *data);
void SendRCUMessage(unsigned char sio, 
				 char *src_id1,
                 char *des_id1, 
                 const rom char *cmd, 
				 unsigned char ack, 
                 unsigned char length, 
                 unsigned char *data);
void Rx1Process(void);
void SendBUCMessage(char *src_id1,
                  char *des_id1, 
                  const rom char *cmd, 
                  unsigned char length, 
                  unsigned char *data);
void Rx2Process(void);
void Rx3Process(void);
void SendUART(unsigned char SIO, unsigned char length, unsigned char *data);
void PrintUART(unsigned char SIO, unsigned char length, unsigned char *data);

void Comm0Mode232(void);
void Comm0Mode485Tx(void);
void Comm0Mode485Rx(void);
void Comm0Mode422(void);
void Comm1Mode422(void);
void Comm1Mode232(void);
void Comm1Mode485Tx(void);
void Comm1Mode485Rx(void);
void Comm2Mode232(void);
void Comm2Mode485Tx(void);
void Comm2Mode485Rx(void);
void Comm3Mode232(void);
void Comm3Mode485Tx(void);
void Comm3Mode485Rx(void);
unsigned char ASC2toHEX(unsigned char *asc);
void HEXto2ASC(unsigned char hex, unsigned char *asc);

void DelayMS(unsigned int ms);
void CheckReceiveData(void);
void CheckSCI0ReceiveData(void);
void CheckSCI1ReceiveData(void);
void CheckSCI2ReceiveData(void);
void CheckSCI3ReceiveData(void);
unsigned char GetChecksum(void *, unsigned char);
void SetBUCCommandData(void);
void SetDualUartBaudRate(unsigned char baudrate);

#endif
