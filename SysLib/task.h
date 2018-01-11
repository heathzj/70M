#ifndef _TASK_H
#define _TASK_H
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

/*------------
    MACROS 
------------*/
/* define task state bit */
#define STAT_BIT_RDY           0x01
#define STAT_BIT_DLY           0x02
#define STAT_BIT_WAIT          0x04

/* define tasks here...*/
enum {
	TASK_IDLE=0,
	TASK_STATUS_UPDATE,
	TASK_POLLING,
	MAX_TASK_NUM
};

//#define MAX_DELAY_TASK_NUM		MAX_TASK_NUM

/* define semaphores here...*/
#define SEMA_NULL              0
#define SEMA_TASKQ             0x0001  //required in task routines to protect task queue

/* define task delay period ( *1.024ms ) */    
#define PERIOD_RX_TIMEOUT       1 // 1000  // to accormdate the long transmit time needed by AMC200 software
#define PERIOD_TX_TIMEOUT       1 // 500
#define PERIOD_UPDATE_INTERVAL  1 // 300
#define PERIOD_POLLING		  1 // 1000
#define PERIOD_RXMODE_DELAY     1 // 3
#define PERIOD_TCP_Stacks       1 // 10
#define PERIOD_SNMP_Trap     	1 // 10
 
#define TMROL_VALUE             0x00  
/*use 8bits TIMERO, counts 0x00 to 0xFFF.
  prescale 1:16, so 256*4*(1/16Mhz)*16= 1.024 milliseconds */ 

/*---------------------------------
    GLOBAL FUNCTIONS PROTOTYPES
---------------------------------*/ 
void InitTask(void);
unsigned char TaskQueue(unsigned char task_id, unsigned char task_sema);
unsigned char TaskDelay(unsigned char task_id, unsigned int time, unsigned char task_sema);
unsigned char TaskKill(unsigned char task_id, unsigned char task_sema);
void DelayKill(unsigned char task_id);
void WaitKill(unsigned char task_id);


#endif
