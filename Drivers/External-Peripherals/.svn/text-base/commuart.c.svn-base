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
#include "task.h"
#include "commuart.h"
#include <delays.h>
#include "Global.h"


/*----------------------
    GLOBAL FUNCTIONS
----------------------*/


/*-----------------------------------------------------------------------------
FUNCTION NAME: WriteDualUartConf()

DESCRIPTION: 
	This function configures the internal registers of DUAL UART
	
INPUT PARAMETERS: 
    BYTE - Register address that is to be configured
    BYTE - Value to be used to configure teh register address

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/

