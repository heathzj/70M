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
#include "list.h"
#include <stdlib.h>

/*-----------------------------------------------------------------------------
FUNCTION NAME: ListInitialize()

DESCRIPTION: 
	This function initializes the task list
	
INPUT PARAMETERS: 
    TaskItem* - Pointer to the task list that is to be initialized.

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void ListInitialize(TaskItem *ptr_head)
{    
    ptr_head->next = NULL;        
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: ListInsert()

DESCRIPTION: 
	This function insert new item hehind the index pointer of the list
	
INPUT PARAMETERS: 
    TaskItem* - Pointer to the task list
    TaskItem* - Pointer to the new item to be insert to this list

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void ListInsert(TaskItem *ptr_index, TaskItem *ptr_new_item)
{
    ptr_new_item->next = ptr_index->next;
    ptr_index->next = ptr_new_item;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: ListDelete()

DESCRIPTION: 
	This function delete item hehind the index pointer of the list 
	
INPUT PARAMETERS: 
    TaskItem* - Pointer to the task to be deleted from the list

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void ListDelete(TaskItem *ptr_index)
{
    ptr_index->next = ptr_index->next->next;
}

