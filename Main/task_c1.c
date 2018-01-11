typedef enum {
	nenTASK_IDLE=0,
	nenTASK_STATUS_UPDATE,
	nenTASK_POLLING,
	nenMAX_TASK_NUM
}tenTaskStateId;

typedef void (*tpfvTask)(void); // pointer to function (of void argument) returning void 

typedef struct{

    tpfvTask pfvTask;
    BYTE u8Priority;
    BYTE u8TaskState;
    
} tstTaskList;

 tstTaskList stTask[6];

static BYTE u8SYS__TaskInit()
{
    BYTE u8Cnt = 0;
    
    while(u8Cnt<=sizeof(stTask))
    {
      stTask[u8Cnt].u8TaskState = nenTASK_IDLE;
        
    }
    
    stTask[0].pfvTask = SYS__vLcdKeyPadTask;
    stTask[0].u8Priority = 0;
    
    stTask[1].pfvTask = StackTask;
    stTask[1].u8Priority = 1;

    stTask[2].pfvTask = SYS__vStatusTask;
    stTask[2].u8Priority = 2;

    stTask[3].pfvTask = StackApplications;
    stTask[3].u8Priority = 3;

    stTask[4].pfvTask = SYS__vLcdBlinkTask;
    stTask[4].u8Priority = 4;  

    stTask[5].pfvTask = Clear_WebPassword;
    stTask[5].u8Priority = 5;      
    
}

static BYTE u8SYS__TaskQueue()
{
    

    
    
}