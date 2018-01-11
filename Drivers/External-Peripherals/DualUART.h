#ifndef _COMM_H
#define _COMM_H
/*-----------------------------------------------------------------------------
*
* Copyright (c) 2006-2009, SINGCOM Pte Ltd
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

/*------------
    MACROS 
------------*/


#define BAUD_9600		0
#define BAUD_115200		1

#define DUAL_UART_RHR_INT	(1<<0)
#define DUAL_UART_THR_INT	(1<<1)
#define DUAL_UART_LSR_INT	(1<<2)

/*---------------------------------
    GLOBAL FUNCTIONS PROTOTYPES
---------------------------------*/      

void Comm0Mode232(void);
void Comm0Mode485Tx(void);
void Comm0Mode485Rx(void);
void Comm0Mode422(void);
void Comm1Mode422Tx(void);
void Comm1Mode422Rx(void);
void Comm1Mode232(void);
void Comm1Mode485Tx(void);
void Comm1Mode485Rx(void);
void Comm2Mode232(void);
void Comm2Mode485Tx(void);
void Comm2Mode485Rx(void);
void Comm3Mode232(void);
void Comm3Mode485Tx(void);
void Comm3Mode485Rx(void);
void Comm4Mode232(void);
void Comm4Mode485Tx(void);
void Comm4Mode485Rx(void);
void Comm5Mode232(void);
void Comm5Mode485Tx(void);
void Comm5Mode485Rx(void);

void DelayMS(unsigned int ms);
void SetDualUartBaudRate(unsigned char baudrate);
void InitialiseDualUart(void);
void InitialiseDualUart2(void);
BYTE ReadDataFromUartISR(BYTE which_sspa);
void SendDataToUart(BYTE byte, BYTE current_sspa);
BYTE ReadDualUartConf(BYTE reg_addr, BYTE which_sspa);
void WriteDualUartConf(BYTE reg_addr, BYTE val,BYTE which_sspa);
BOOL IsDualUartTxDone(BYTE numDualUart);
void SetDualUartInterrupt(BYTE u8Reg, BYTE u8Data, BYTE which_uart);

#endif
