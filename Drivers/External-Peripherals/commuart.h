#ifndef _UART_H
#define _UART_H

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
#include "define.h"
/*-------------------------
	FUNCTION PROTOTYPES 
-------------------------*/
void InitialiseDualUart(void);
unsigned char ReadDualUartConf(unsigned char, unsigned char);
void WriteDualUartConf(unsigned char, unsigned char);
void ConfigureUartChannel(unsigned char, unsigned char, unsigned char);
void SendDataToUart(unsigned char , unsigned char );
unsigned char ReadDataFromUart(unsigned char);
unsigned char  ReadDataFromUartISR(unsigned char  which_sspa);

#endif  /*  end of #ifndef _UART_H */

