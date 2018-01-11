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
#include "task.h"
#include "list.h"
#include "Global.h"

/*----------------------
    GLOBAL VARIABLES
----------------------*/
//#pragma udata grp13
TaskItem task_list[MAX_TASK_NUM];  
#pragma udata // Return to default code section
TaskItem queue_head, *queue_index;

unsigned char semaphore;
unsigned int timer_counter = 0;

/*-----------------------------------------------------------------------------
FUNCTION NAME: InitTask()

DESCRIPTION: 
    This function initializes the task queue 
    
INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void InitTask(void)
{        
    unsigned char i;
    semaphore = 0;

	memset(task_list, 0, sizeof(task_list));
	memset(&queue_head, 0, sizeof(queue_head));
	
    for (i = 0; i < MAX_TASK_NUM; i++)   
    {
        task_list[i].id = i;
        task_list[i].priority = 3;     // set all task's priorities 3
        task_list[i].state_bit = 0;
        task_list[i].delay_task_run = FALSE;
    }        
    
//  ListInitialize(&queue_head); 
	queue_head.next = NULL;
    queue_index = &queue_head;
	
//  ListInsert(queue_index,&task_list[TASK_IDLE]);    
    task_list[TASK_IDLE].next = queue_head.next;
    queue_head.next = &(task_list[TASK_IDLE]);
	
    task_list[TASK_IDLE].priority = 0;     //priority 0 only for idle task
    task_list[TASK_IDLE].state_bit |= STAT_BIT_RDY; 
    queue_head.id = 1;       // queue_head.id as task numbers counter in queue     
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: TaskQueue()

DESCRIPTION: 
    This function queues insert a new task in the list and sets the required 
    attributes
    
INPUT PARAMETERS: 
    BYTE      - Indicate the task ID
    TaskItem* - Pointer of the new task to be inserted into the list
    TaskItem* - Pointer to the head of the task list
    WORD      - Indicate the event to be checked on wakeup
    WORD      - Indicate the flag that need to be set when running

RETURN:
    INT       - Return status of success or failure of the function

NOTES:

-----------------------------------------------------------------------------*/
unsigned char TaskQueue(unsigned char task_id, unsigned char task_sema)       // Task ready
{
	unsigned char TaskQueueCounter = 0;

	// task id error, reset
	if (task_id >= MAX_TASK_NUM)
	{
//		ResetSystem();
		return 0;	  
	}
	
    semaphore |= SEMA_TASKQ;       // set semaphore to protect task queue
    queue_index = &queue_head;
    while (1)
    {
        if (queue_index->next->id == task_id)
        {
            semaphore &= ~SEMA_TASKQ;             
            return 0;           //already in task queue    
        }
        
        if ((task_list[task_id].priority > queue_index->next->priority)
           || (queue_index->next == NULL)) 
        {
//            ListInsert(queue_index, &task_list[task_id]);
			task_list[task_id].next = queue_index->next;
			queue_index->next = &(task_list[task_id]);
            task_list[task_id].state_bit |= STAT_BIT_RDY;                          
            semaphore |= task_sema;   //Set task_sema mainly for resources occupied
            queue_head.id++;
            semaphore &= ~SEMA_TASKQ;                     
            return 1;    
        }         
        queue_index = queue_index->next;
        // queue counter can't over max task number
        // if error that means queue pointer wrong
        if (TaskQueueCounter >= MAX_TASK_NUM)
        {
        	break; // yt: should not come here
//        	ResetSystem();
        }
        TaskQueueCounter++;
    }    
    semaphore &= ~SEMA_TASKQ;              
    return 0;     
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: TaskDelay()

DESCRIPTION: 
    This function insert delay to a task in the list and sets the required 
    attributes
    
INPUT PARAMETERS: 
    BYTE      - Indicate the task ID
    TaskItem* - Pointer of the task that needs to be delayed
    WORD      - Delay tiem required
    WORD      - Indicate the event to be checked on wakeup
    WORD      - Indicate the flag that need to be set when running

RETURN:
    INT       - Return status of success or failure of the function

NOTES:

-----------------------------------------------------------------------------*/
unsigned char TaskDelay(unsigned char task_id, unsigned int time, unsigned char task_sema)
{     
    if (!(task_list[task_id].state_bit&STAT_BIT_DLY)) //Only one delay allowed
    {
        task_list[task_id].state_bit |= STAT_BIT_DLY;                          
        task_list[task_id].delay_time = timer_counter + time;
        task_list[task_id].task_sema = task_sema; 
        return 1;
    } 
     
    return 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: TaskKill()

DESCRIPTION: 
    This function kills/remove a task in the list and sets the required 
    attributes
    
INPUT PARAMETERS: 
    BYTE      - Indicate the task ID
    TaskItem* - Pointer of the task to be removed from the list
    TaskItem* - Pointer to the head of the task list
    WORD      - Indicate the flag that need to be set when running

RETURN:
    INT       - Return status of success or failure of the function

NOTES:

-----------------------------------------------------------------------------*/
unsigned char TaskKill(unsigned char task_id, unsigned char task_sema)    //Remove tasks from task queue 
{
	unsigned char TaskQueueCounter = 0;
	
    semaphore |= SEMA_TASKQ;
    queue_index = &queue_head;
    while (queue_index->next != NULL)
    {
        if (queue_index->next->id == task_id)
        {             
//            ListDelete(queue_index);
			queue_index->next = queue_index->next->next;
            task_list[task_id].state_bit &= ~STAT_BIT_RDY;             
            semaphore &= ~task_sema;
            queue_head.id--;
            semaphore &= ~SEMA_TASKQ;         
            return 1;
        }
        queue_index = queue_index->next;
        // queue counter can't over max task number
        // if error that means queue pointer wrong
        if (TaskQueueCounter > MAX_TASK_NUM)
        {
        	break; // yt: should not come here
//        	ResetSystem();
        }
        TaskQueueCounter++;
    }
    semaphore &= ~SEMA_TASKQ;
    return 0;          
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: DelayKill()

DESCRIPTION: 
    This function kills/remove/reset the delay bit for the task.
    
INPUT PARAMETERS: 
    BYTE      - Indicate the task ID
    TaskItem* - Pointer of the task to where state bit need to be reset

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void DelayKill(unsigned char task_id)             //disable delayed task
{
    task_list[task_id].state_bit &= ~STAT_BIT_DLY;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: WaitKill()

DESCRIPTION: 
    This function kills/remove/reset the wait bit for the task.
    
INPUT PARAMETERS: 
    BYTE      - Indicate the task ID
    TaskItem* - Pointer of the task to where state bit need to be reset

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void WaitKill(unsigned char task_id)             //disable waiting task
{
    task_list[task_id].state_bit &= ~STAT_BIT_WAIT;
}
