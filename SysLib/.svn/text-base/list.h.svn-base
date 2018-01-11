#ifndef _LIST_H
#define _LIST_H
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
#ifndef NULL
#define NULL 0
#endif

/*-----------
    ENUMS
-----------*/
typedef struct LstItem
{
   struct LstItem *next;
   unsigned char id;
   unsigned char priority;   
   unsigned char state_bit;	 	// Task state bits: ready, delayed, waiting
   unsigned char delay_task_run; 	 	// For heavy burden tasks			
   unsigned int	 delay_time;	// Time for delay
   unsigned char  task_sema;		// affected semaphore (resources) while the task is ready
       
} TaskItem;

/*---------------------------------
    GLOBAL FUNCTIONS PROTOTYPES
---------------------------------*/
void ListInitialize(TaskItem *ptr_head);

void ListInsert(TaskItem *ptr_index, TaskItem *ptr_new_item);

void ListDelete(TaskItem *ptr_index);


#endif
