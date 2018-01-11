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
#include "comm.h"
#include "task.h"
#include "define.h"
#include "commuart.h"
#include "Global.h"
//#include "old/Protocolprocess.h"

/*----------------------
    GLOBAL VARIABLES
----------------------*/

BYTE Comm0TxFlag = FALSE, Comm0TxCounter = 0;
BYTE Comm1TxFlag = FALSE, Comm1TxCounter = 0;
BYTE Comm2TxFlag = FALSE, Comm2TxCounter = 0;
BYTE Comm3TxFlag = FALSE, Comm3TxCounter = 0;
WORD Comm0RxCounter = 0, Comm1RxCounter = 0, Comm2RxCounter = 0;

BYTE rx_counter0 = 0, tx_counter0 = 0;  // number of bytes in the rx_buffer/ tx_buffer
BYTE rx_counter1 = 0, tx_counter1 = 0; 
BYTE rx_counter2 = 0, tx_counter2 = 0; 
BYTE rx_counter3 = 0, tx_counter3 = 0; 
BYTE *data_field0;
BYTE data_field_length0;
WORD command0;
BYTE *data_field1;
BYTE data_field_length1;
WORD command1;
BYTE *data_field2;
BYTE data_field_length2;
WORD command2;
BYTE *data_field3;
BYTE data_field_length3;
WORD command3;
const rom char BroadcastID[3] = {'0', '0', '0'};
const rom char BroadcastIDNew = '0';
/*

char RCU_ID[3], SIO0_ID[3], SIO1_ID[3], SIO2_ID[3], SIO3_ID[3];
extern char SSPA_ID[3], BUC_ID[3];
extern char src_id[3], des_id[3];
char src_id_New[3], des_id_New[3];
char src_id0_New[3], des_id0_New[3];
char src_id1_New[3], des_id1_New[3];
char src_id2_New[3], des_id2_New[3];
char src_id3_New[3], des_id3_New[3];
char src_id2[3], des_id2[3];

BYTE BUCCommFlag = FALSE, PollingTcik = 0, BUCCommCounter = 0, BUC_Atten = 0;
BYTE SetBUCAttenFlag = FALSE, SendBUCAttenCmdFlag = FALSE;
BYTE SetBUCOnFlag = FALSE, SendBUCOnCmdFlag = FALSE;
BYTE SetBUCOffFlag = FALSE, SendBUCOffCmdFlag = FALSE;
BYTE ResendCounter = 0;
char RCU_ID1;
*/
/*----------------------
    EXTERN VARIABLES
----------------------*/
/*
extern WORD semaphore;
extern BYTE data_counter, sspa_state, sspa_temp1_hex;
extern BYTE data_buffer0[BUFFER_LEN], data_buffer1[BUFFER_LEN], data_buffer2[BUFFER_LEN], data_buffer3[BUFFER_LEN];
extern BYTE data_counter0, data_counter1, data_counter2, data_counter3;
extern BYTE Run_Polling_Once;
*/
extern void InitialiseDualUart(void);

/*--------------------------------
    LOCAL FUNCTIONS PROTOTYPES
--------------------------------*/
#if 0
/*---------------------
    LOCAL FUNCTIONS 
---------------------*/
/*-----------------------------------------------------------------------------
FUNCTION NAME: CheckSCI0ReceiveData()

DESCRIPTION: 
	check serial port receive data

INPUT PARAMETERS: 
	None

RETURN:
	None

NOTES:

-----------------------------------------------------------------------------*/
void CheckSCI0ReceiveData(void)
{
	BYTE temp_data = 0, i, len;

	len = data_counter0;

	// why data_buffer is ok but rx_buffer is wrong???????
	for (i = 0; i < len; i++)
	{
		// get receive data form data buffer
		temp_data = data_buffer0[i];

		// if receive data is START_PROMPT or START_PROMPT_NEW when rx_counter is 0
		if (((temp_data == START_PROMPT) || (temp_data == START_PROMPT_NEW)) && (rx_counter0 == 0))
		{
			rx_buffer0[0] = temp_data;
			rx_counter0 = 1;
			TaskDelay(TASK_RX0_TIMEOUT,PERIOD_RX_TIMEOUT,SEMA_NULL,SEMA_NULL);
		}
		else if ((temp_data == END_PROMPT) && (rx_counter0 != 0))
		{					
			TaskQueue(TASK_RX0_PROCESS,SEMA_NULL,SEMA_NULL);
			DelayKill(TASK_RX0_TIMEOUT);
		}
		else if (rx_counter0 != 0)
		{
			rx_buffer0[rx_counter0++] = temp_data;

			if (rx_counter0 >= BUFFER_LEN)
			{
				rx_counter0 = 0;
			}
			
			// if get destination ID then check destination ID
			if (rx_counter0 > POS_CMD)
			{
				if (rx_buffer0[0] == START_PROMPT)
				{	// if destination ID is not SSPA_RCU ID or broadcast ID then count receive message again
					if (!(((rx_buffer0[POS_DES_ID] == SSPA_ID[0]) && (rx_buffer0[POS_DES_ID + 1] == SSPA_ID[1]) && (rx_buffer0[POS_DES_ID + 2] == SSPA_ID[2]))
						|| ((rx_buffer0[POS_DES_ID] == BUC_ID[0]) && (rx_buffer0[POS_DES_ID + 1] == BUC_ID[1]) && (rx_buffer0[POS_DES_ID + 2] == BUC_ID[2]))
						|| ((rx_buffer0[POS_DES_ID] == BroadcastID[0]) && (rx_buffer0[POS_DES_ID + 1] == BroadcastID[1]) && (rx_buffer0[POS_DES_ID + 2] == BroadcastID[2]))))
					{
						rx_counter0 = 0;
					}
				}
				if (rx_buffer0[0] == START_PROMPT_NEW)
				{	// if destination ID is not SSPA_RCU ID or broadcast ID then count receive message again
					if (!(((rx_buffer0[POS_DES_ID_NEW] == RCU_ID[0]) && (rx_buffer0[POS_DES_ID_NEW + 1] == RCU_ID[1]))
						|| ((rx_buffer0[POS_DES_ID_NEW] == BroadcastIDNew)) || ((rx_buffer0[POS_DES_ID_NEW + 1] == BroadcastIDNew))))
					{
						rx_counter0 = 0;
					}
				}
			}
		}
		else
		{
			rx_counter0 = 0;
		}
	}
	data_counter0 = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: CheckSCI1ReceiveData()

DESCRIPTION: 
	check serial port receive data

INPUT PARAMETERS: 
	None

RETURN:
	None

NOTES:

-----------------------------------------------------------------------------*/
void CheckSCI1ReceiveData(void)

{
	BYTE temp_data = 0, i, len;

	len = data_counter1;

	// why data_buffer is ok but rx_buffer is wrong???????
	for (i = 0; i < len; i++)
	{
		// get receive data form data buffer
		temp_data = data_buffer1[i];

		// if receive data is START_PROMPT or START_PROMPT_NEW when rx_counter is 0
		if (((temp_data == START_PROMPT) || (temp_data == START_PROMPT_NEW)) && (rx_counter1 == 0))
		{
			rx_buffer1[0] = temp_data;
			rx_counter1 = 1;
			TaskDelay(TASK_RX1_TIMEOUT,PERIOD_RX_TIMEOUT,SEMA_NULL,SEMA_NULL);
		}
		else if ((temp_data == END_PROMPT) && (rx_counter1 != 0))
		{					
			TaskQueue(TASK_RX1_PROCESS,SEMA_NULL,SEMA_NULL);
			DelayKill(TASK_RX1_TIMEOUT);
		}
		else if (rx_counter1 != 0)
		{
			rx_buffer1[rx_counter1++] = temp_data;

			if (rx_counter1 >= BUFFER_LEN)
			{
				rx_counter1 = 0;
			}
			
			// if get destination ID then check destination ID
			if (rx_counter1 > POS_CMD)
			{
				if (rx_buffer1[0] == START_PROMPT)
				{	// if destination ID is not SSPA_RCU ID or broadcast ID then count receive message again
					if (!(((rx_buffer1[POS_DES_ID] == SSPA_ID[0]) && (rx_buffer1[POS_DES_ID + 1] == SSPA_ID[1]) && (rx_buffer1[POS_DES_ID + 2] == SSPA_ID[2]))
						|| ((rx_buffer1[POS_DES_ID] == BUC_ID[0]) && (rx_buffer1[POS_DES_ID + 1] == BUC_ID[1]) && (rx_buffer1[POS_DES_ID + 2] == BUC_ID[2]))
						|| ((rx_buffer1[POS_DES_ID] == BroadcastID[0]) && (rx_buffer1[POS_DES_ID + 1] == BroadcastID[1]) && (rx_buffer1[POS_DES_ID + 2] == BroadcastID[2]))))
					{
						rx_counter1 = 0;
					}
				}
				if (rx_buffer1[0] == START_PROMPT_NEW)
				{	// if destination ID is not SSPA_RCU ID or broadcast ID then count receive message again
					if (!(((rx_buffer1[POS_DES_ID_NEW] == RCU_ID[0]) && (rx_buffer1[POS_DES_ID_NEW + 1] == RCU_ID[1]))
						|| ((rx_buffer1[POS_DES_ID_NEW] == BroadcastIDNew)) || ((rx_buffer1[POS_DES_ID_NEW + 1] == BroadcastIDNew))))
					{
						rx_counter1 = 0;
					}
				}
			}
		}
		else
		{
			rx_counter1 = 0;
		}
	}
	data_counter1 = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: CheckSCI2ReceiveData()

DESCRIPTION: 
	check serial port receive data

INPUT PARAMETERS: 
	None

RETURN:
	None

NOTES:

-----------------------------------------------------------------------------*/
void CheckSCI2ReceiveData(void)
{
	BYTE temp_data = 0, i, len;

	len = data_counter2;

	// why data_buffer is ok but rx_buffer is wrong???????
	for (i = 0; i < len; i++)
	{
		// get receive data form data buffer
		temp_data = data_buffer2[i];

		// if receive data is START_PROMPT or START_PROMPT_NEW when rx_counter is 0
		if (((temp_data == START_PROMPT) || (temp_data == START_PROMPT_NEW)) && (rx_counter2 == 0))
		{
			rx_buffer2[0] = temp_data;
			rx_counter2 = 1;
			TaskDelay(TASK_RX2_TIMEOUT,PERIOD_RX_TIMEOUT,SEMA_NULL,SEMA_NULL);
		}
		else if ((temp_data == END_PROMPT) && (rx_counter2 != 0))
		{					
			TaskQueue(TASK_RX2_PROCESS,SEMA_NULL,SEMA_NULL);
			DelayKill(TASK_RX2_TIMEOUT);
		}
		else if (rx_counter2 != 0)
		{
			rx_buffer2[rx_counter2++] = temp_data;

			if (rx_counter2 >= BUFFER_LEN)
			{
				rx_counter2 = 0;
			}
			
			// if get destination ID then check destination ID
			if (rx_counter2 > POS_CMD)
			{
				if (rx_buffer2[0] == START_PROMPT)
				{	// if destination ID is not SSPA_RCU ID or broadcast ID then count receive message again
					if (!(((rx_buffer2[POS_DES_ID] == SSPA_ID[0]) && (rx_buffer2[POS_DES_ID + 1] == SSPA_ID[1]) && (rx_buffer2[POS_DES_ID + 2] == SSPA_ID[2]))
						|| ((rx_buffer2[POS_DES_ID] == BUC_ID[0]) && (rx_buffer2[POS_DES_ID + 1] == BUC_ID[1]) && (rx_buffer2[POS_DES_ID + 2] == BUC_ID[2]))
						|| ((rx_buffer2[POS_DES_ID] == BroadcastID[0]) && (rx_buffer2[POS_DES_ID + 1] == BroadcastID[1]) && (rx_buffer2[POS_DES_ID + 2] == BroadcastID[2]))))
					{
						rx_counter2 = 0;
					}
				}
				if (rx_buffer2[0] == START_PROMPT_NEW)
				{	// if destination ID is not SSPA_RCU ID or broadcast ID then count receive message again
					if (!(((rx_buffer2[POS_DES_ID_NEW] == RCU_ID[0]) && (rx_buffer2[POS_DES_ID_NEW + 1] == RCU_ID[1]))
						|| ((rx_buffer2[POS_DES_ID_NEW] == BroadcastIDNew)) || ((rx_buffer2[POS_DES_ID_NEW + 1] == BroadcastIDNew))))
					{
						rx_counter2 = 0;
					}
				}
			}
		}
		else
		{
			rx_counter2 = 0;
		}
	}
	data_counter2 = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: CheckSCI3ReceiveData()

DESCRIPTION: 
	check serial port receive data

INPUT PARAMETERS: 
	None

RETURN:
	None

NOTES:

-----------------------------------------------------------------------------*/
void CheckSCI3ReceiveData(void)
{
	BYTE temp_data = 0, i;

	for (i = 0; i < data_counter3; i++)
	{
		// get receive data form data buffer
		temp_data = data_buffer3[i];

		// if receive data is START_PROMPT or START_PROMPT_NEW when rx_counter is 0
		if ((temp_data == START_PROMPT) && (rx_counter3 == 0))
		{
			rx_buffer3[0] = temp_data;
			rx_counter3 = 1;
			TaskDelay(TASK_RX3_TIMEOUT,PERIOD_RX_TIMEOUT,SEMA_NULL,SEMA_NULL);
		}
		else if ((temp_data == END_PROMPT) && (rx_counter3 > POS_DATA_LEN))
		{					
			TaskQueue(TASK_RX3_PROCESS,SEMA_NULL,SEMA_NULL);
			DelayKill(TASK_RX3_TIMEOUT);
		}
		else if (rx_counter3 != 0)
		{
			rx_buffer3[rx_counter3++] = temp_data;

			if (rx_counter3 >= BUFFER_LEN)
			{
				rx_counter3 = 0;
			}
		}
		else
		{
			rx_counter3 = 0;
		}
	}
	data_counter3 = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: CheckReceiveData()

DESCRIPTION: 
	check serial port receive data

INPUT PARAMETERS: 
	None

RETURN:
	None

NOTES:

-----------------------------------------------------------------------------*/
void CheckReceiveData(void)
{
	if (data_counter0 > 0)
		CheckSCI0ReceiveData();
	if (data_counter1 > 0)
		CheckSCI1ReceiveData();
	if (data_counter2 > 0)
		CheckSCI2ReceiveData();
	if (data_counter3 > 0)
		CheckSCI3ReceiveData();
}
#endif

unsigned char ASC2toHEX(unsigned char *asc)
{
	unsigned char hex, hex2;

	hex = asc[0] - '0';
	hex = hex<10?hex:hex-7;
	hex = hex<16?hex:hex-22;
	hex <<= 4;
	hex2 = asc[1] - '0';
	hex2 = hex2<10?hex2:hex2-7;
	hex2 = hex2<16?hex2:hex2-22;
	hex += hex2;	
	return hex;	
}

/*convert HEX to 2 ASC CODE*/
void HEXto2ASC(unsigned char hex, unsigned char *asc)
{	
	asc[0] = hex>>4;
	asc[0] = asc[0]<10?asc[0]+'0':asc[0]+'0'+7;
	asc[1] = hex&0x0F;
	asc[1] = asc[1]<10?asc[1]+'0':asc[1]+'0'+7;	
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: GetChecksum()

DESCRIPTION: 
    Calculates the checksum of the buffer

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
BYTE GetChecksum(void *p_buff, BYTE n)
{
    BYTE i,*ptr_byte;
    BYTE chksum;
       
    chksum = 0;
    ptr_byte = (BYTE*) p_buff;
    for(i=0;i<n;i++)
    {
        chksum += ptr_byte[i];
    }
    return chksum;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm0Mode232()

DESCRIPTION: 
    This functions sets the communication mode to RS 232

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm0Mode232(void)
{
    MODE0 = 0;
    RXEN0 = 1;
    DXEN0 = 0;    
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm0Mode485Tx()

DESCRIPTION: 
    This functions sets the communication mode to RS485Tx

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm0Mode485Tx(void)
{
    MODE0 = 1;
    RXEN0 = 0;
    DXEN0 = 1;    
	UART0_TX_INT_ENABLE = 1;
	UART0_INT_ENABLE = 0;
	Comm0TxFlag = TRUE;
	Comm0TxCounter = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm0Mode485Rx()

DESCRIPTION: 
    This functions sets the communication mode to RS485Rx

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm0Mode485Rx(void)
{
    MODE0 = 1;
    RXEN0 = 1;
    DXEN0 = 0;    
	UART0_TX_INT_ENABLE = 0;
	UART0_INT_ENABLE = 1;
	Comm0TxFlag = FALSE;
	Comm0TxCounter = 0;
}


void Comm0Mode422(void)
{
    MODE0 = 1;
    RXEN0 = 1;
    DXEN0 = 1;  
	UART0_TX_INT_ENABLE = 0;
	UART0_INT_ENABLE = 1;
	Comm0TxFlag = FALSE;
	Comm0TxCounter = 0;  
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm1Mode422()

DESCRIPTION: 
    This function sets communication mode RS422

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm1Mode422(void)
{
    MODE1 = 1;
    RXEN1 = 1;
    DXEN1 = 1;    
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm1Mode232()

DESCRIPTION: 
    This function sets communication mode RS232

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm1Mode232(void)
{
    MODE1 = 0;
    RXEN1 = 1;
    DXEN1 = 0;    
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm1Mode485Tx()

DESCRIPTION: 
    This function sets communication mode RS48Tx

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm1Mode485Tx(void)
{
    MODE1 = 1;
    RXEN1 = 0;
    DXEN1 = 1;    
	UART1_TX_INT_ENABLE = 1;
	UART1_INT_ENABLE = 0;
	Comm1TxFlag = TRUE;
	Comm1TxCounter = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm1Mode485Rx()

DESCRIPTION: 
    This function sets communication mode RS48Rx

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm1Mode485Rx(void)
{
    MODE1 = 1;
    RXEN1 = 1;
    DXEN1 = 0;    
	UART1_TX_INT_ENABLE = 0;
	UART1_INT_ENABLE = 1;
	Comm1TxFlag = FALSE;
	Comm1TxCounter = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm3Mode232()

DESCRIPTION: 
    This function sets communication mode RS232

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm3Mode232(void)
{
    MODE3 = 0;
    RXEN3 = 1;
    DXEN3 = 0;    
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm3Mode485Tx()

DESCRIPTION: 
    This function sets communication mode RS48Tx

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm3Mode485Tx(void)
{
    MODE3 = 1;
    RXEN3 = 0;
    DXEN3 = 1;    
	Comm3TxFlag = TRUE;
	Comm3TxCounter = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm3Mode485Rx()

DESCRIPTION: 
    This function sets communication mode RS48Rx

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm3Mode485Rx(void)
{
    MODE3 = 1;
    RXEN3 = 1;
    DXEN3 = 0;    
	Comm3TxFlag = FALSE;
	Comm3TxCounter = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm2Mode232()

DESCRIPTION: 
    This function sets communication mode RS232

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm2Mode232(void)
{
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm2Mode485Tx()

DESCRIPTION: 
    This function sets communication mode RS48Tx

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm2Mode485Tx(void)
{
	Comm2TxFlag = TRUE;
	Comm2TxCounter = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm2Mode485Rx()

DESCRIPTION: 
    This function sets communication mode RS48Rx

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Comm2Mode485Rx(void)
{
	Comm2TxFlag = FALSE;
	Comm2TxCounter = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: PrintUART()

DESCRIPTION: 
	This routine sends data to UART0/1/2/3

INPUT PARAMETERS: 
	None

RETURN:
	None

NOTES:

-----------------------------------------------------------------------------*/
void PrintUART(BYTE SIO, BYTE length, BYTE *data)
{
	BYTE i, lsr_sspa_val = 0;
	if (SIO == SIO0)
	{
		if (data != NULL)
		{
			for (i = 0; i < length; i++)
			{
				while (TXSTA1bits.TRMT == 0);
				TXREG1 = data[i];
			}
		}
	}
	else if (SIO == SIO1)
	{
		if (data != NULL)
		{
			for (i = 0; i < length; i++)
			{
				while (TXSTA2bits.TRMT == 0);
				TXREG2 = data[i];
			}
		}
	}
	else if (SIO == SIO2)
	{
		if (data != NULL)
		{
			for (i = 0; i < length; i++)
			{
//				do
//				{
//					lsr_sspa_val = ReadDualUartConf(DUAL_UART_LSR, DUAL_UART_B);
					if (data[i] != 0)
					{
						SendDataToUart(data[i], DUAL_UART_B);
						DelayMS(1);
					}
					else
						break;
//				}while(1);
			}
		}
		DelayMS(1);
	}
	else if (SIO == SIO3)
	{
		if (data != NULL)
		{
			for (i = 0; i < length; i++)
			{
//				do
//				{
//					lsr_sspa_val = ReadDualUartConf(DUAL_UART_LSR, DUAL_UART_A);
					if (data[i] != 0)
					{
						SendDataToUart(data[i], DUAL_UART_A);
//						DelayMS(1);
					}
					else
						break;
//				}while(1);
			}
		}
		DelayMS(1);
	}
}

#if 0
/*----------------------
    GlOBAL FUNCTIONS 
----------------------*/
	/*-----------------------------------------------------------------------------
	FUNCTION NAME: SetBUCCommandData()
	
	DESCRIPTION: 
		This routine get BUC command and answer with buffer, if unknow command, directly forward to BUC
	
	INPUT PARAMETERS: 
		None
	
	RETURN:
		None
	
	NOTES:
	
	-----------------------------------------------------------------------------*/
void SetBUCCommandData(void)
{
	// AS command
	BUCCommand[0].CmdLength = 10;
	BUCCommand[0].CmdData[0] = 'F';
	BUCCommand[0].CmdData[1] = 'F';
	BUCCommand[0].CmdData[2] = 'F';
	BUCCommand[0].CmdData[3] = 'F';
	BUCCommand[0].CmdData[4] = 'F';
	BUCCommand[0].CmdData[5] = 'F';
	BUCCommand[0].CmdData[6] = 'F';
	BUCCommand[0].CmdData[7] = 'F';
	BUCCommand[0].CmdData[8] = 'F';
	BUCCommand[0].CmdData[9] = 'F';
	BUCCommand[0].CmdData[10] = 'F';
	BUCCommand[0].CmdData[11] = 'F';

	// VE command
	BUCCommand[1].CmdLength = 8;
	BUCCommand[1].CmdData[0] = '0';
	BUCCommand[1].CmdData[1] = '0';
	BUCCommand[1].CmdData[2] = '3';
	BUCCommand[1].CmdData[3] = '1';
	BUCCommand[1].CmdData[4] = '3';
	BUCCommand[1].CmdData[5] = '0';
	BUCCommand[1].CmdData[6] = '3';
	BUCCommand[1].CmdData[7] = '0';
	BUCCommand[1].CmdData[8] = '0';
	BUCCommand[1].CmdData[9] = '0';

	// AD command
	BUCCommand[2].CmdLength = 16;
	BUCCommand[2].CmdData[0] = '0';
	BUCCommand[2].CmdData[1] = '0';
	BUCCommand[2].CmdData[2] = '0';
	BUCCommand[2].CmdData[3] = '0';
	BUCCommand[2].CmdData[4] = '0';
	BUCCommand[2].CmdData[5] = '0';
	BUCCommand[2].CmdData[6] = '0';
	BUCCommand[2].CmdData[7] = '0';
	BUCCommand[2].CmdData[8] = '0';
	BUCCommand[2].CmdData[9] = '0';
	BUCCommand[2].CmdData[10] = '0';
	BUCCommand[2].CmdData[11] = '0';
	BUCCommand[2].CmdData[12] = '0';
	BUCCommand[2].CmdData[13] = '0';
	BUCCommand[2].CmdData[14] = '0';
	BUCCommand[2].CmdData[15] = '0';
	BUCCommand[2].CmdData[16] = '0';
	BUCCommand[2].CmdData[17] = '0';

	// DA command
	BUCCommand[3].CmdLength = 8;
	BUCCommand[3].CmdData[0] = '0';
	BUCCommand[3].CmdData[1] = '0';
	BUCCommand[3].CmdData[2] = '0';
	BUCCommand[3].CmdData[3] = '0';
	BUCCommand[3].CmdData[4] = '0';
	BUCCommand[3].CmdData[5] = '0';
	BUCCommand[3].CmdData[6] = '0';
	BUCCommand[3].CmdData[7] = '0';
	BUCCommand[3].CmdData[8] = '0';
	BUCCommand[3].CmdData[9] = '0';

	// MS command
	BUCCommand[4].CmdLength = 24;
	BUCCommand[4].CmdData[0] = 'F';
	BUCCommand[4].CmdData[1] = 'F';
	BUCCommand[4].CmdData[2] = 'F';
	BUCCommand[4].CmdData[3] = 'F';
	BUCCommand[4].CmdData[4] = 'F';
	BUCCommand[4].CmdData[5] = 'F';
	BUCCommand[4].CmdData[6] = 'F';
	BUCCommand[4].CmdData[7] = 'F';
	BUCCommand[4].CmdData[8] = 'F';
	BUCCommand[4].CmdData[9] = 'F';
	BUCCommand[4].CmdData[10] = 'F';
	BUCCommand[4].CmdData[11] = 'F';
	BUCCommand[4].CmdData[12] = 'F';
	BUCCommand[4].CmdData[13] = 'F';
	BUCCommand[4].CmdData[14] = 'F';
	BUCCommand[4].CmdData[15] = 'F';
	BUCCommand[4].CmdData[16] = 'F';
	BUCCommand[4].CmdData[17] = 'F';
	BUCCommand[4].CmdData[18] = 'F';
	BUCCommand[4].CmdData[19] = 'F';
	BUCCommand[4].CmdData[20] = 'F';
	BUCCommand[4].CmdData[21] = 'F';
	BUCCommand[4].CmdData[22] = 'F';
	BUCCommand[4].CmdData[23] = 'F';
	BUCCommand[4].CmdData[24] = 'F';
	BUCCommand[4].CmdData[25] = 'F';
}

	/*-----------------------------------------------------------------------------
	FUNCTION NAME: BUCCommandProcess()
	
	DESCRIPTION: 
		This routine get BUC command and answer with buffer, if unknow command, directly forward to BUC
	
	INPUT PARAMETERS: 
		None
	
	RETURN:
		None
	
	NOTES:
	
	-----------------------------------------------------------------------------*/
void BUCCommandProcess(BYTE sio)
{
	BYTE SourceID[3];
	BYTE temp, tempLength;
	BYTE *tempptr;

	if (sio == SIO1)
	{
		SourceID[0] = rx_buffer1[POS_SRC_ID];
		SourceID[1] = rx_buffer1[POS_SRC_ID + 1];
		SourceID[2] = rx_buffer1[POS_SRC_ID + 2];
		tempptr = rx_buffer1;
		tempLength = rx_counter1;
	}
	else if (sio == SIO0)
	{
		SourceID[0] = rx_buffer0[POS_SRC_ID];
		SourceID[1] = rx_buffer0[POS_SRC_ID + 1];
		SourceID[2] = rx_buffer0[POS_SRC_ID + 2];
		tempptr = rx_buffer0;
		tempLength = rx_counter0;
	}
	else if (sio == SIO2)
	{
		SourceID[0] = rx_buffer2[POS_SRC_ID];
		SourceID[1] = rx_buffer2[POS_SRC_ID + 1];
		SourceID[2] = rx_buffer2[POS_SRC_ID + 2];
		tempptr = rx_buffer2;
		tempLength = rx_counter2;
	}

	// answer BUC command with BUC buffer
	if ((tempptr[POS_CMD] == 'A') && (tempptr[POS_CMD + 1] == 'S'))
	{
		// if BUC alarm, set BUC alarm
		if ((sspa_state & 0x02) != 0x02)
		{
			temp = ASC2toHEX(BUCCommand[0].CmdData + 4);
			temp &= ~0x08;
			HEXto2ASC(temp, (BUCCommand[0].CmdData + 4));
		}
		else
		{
			temp = ASC2toHEX(BUCCommand[0].CmdData + 4);
			temp |= 0x08;
			HEXto2ASC(temp, (BUCCommand[0].CmdData + 4));
		}
		// set BUC temperature
		temp = sspa_temp1_hex;
		HEXto2ASC(temp, (BUCCommand[0].CmdData + 6));

		// set BUC attenuator
		temp = BUC_Atten;
		HEXto2ASC(temp, (BUCCommand[0].CmdData + 8));
		
		SendMessage(sio, BUC_ID, SourceID, "AS", BUCCommand[0].CmdLength, BUCCommand[0].CmdData);
	}
	else if ((tempptr[POS_CMD] == 'V') && (tempptr[POS_CMD + 1] == 'E'))
	{
		SendMessage(sio, BUC_ID, SourceID, "VE", BUCCommand[1].CmdLength, BUCCommand[1].CmdData);
	}
	else if ((tempptr[POS_CMD] == 'A') && (tempptr[POS_CMD + 1] == 'D'))
	{
		// set BUC temperature
		temp = sspa_temp1_hex;
		HEXto2ASC(temp, (BUCCommand[2].CmdData + 0));
		
		SendMessage(sio, BUC_ID, SourceID, "AD", BUCCommand[2].CmdLength, BUCCommand[2].CmdData);
	}
	else if ((tempptr[POS_CMD] == 'D') && (tempptr[POS_CMD + 1] == 'A'))
	{
		// set BUC attenuator
		temp = BUC_Atten;
		HEXto2ASC(temp, (BUCCommand[3].CmdData + 0));
		
		// set BUC temperature
		temp = GetTemperatureDegree(sspa_temp1_hex);
		HEXto2ASC(temp, (BUCCommand[3].CmdData + 2));
		
		SendMessage(sio, BUC_ID, SourceID, "DA", BUCCommand[3].CmdLength, BUCCommand[3].CmdData);
	}
	else if ((tempptr[POS_CMD] == 'M') && (tempptr[POS_CMD + 1] == 'S'))
	{
		SendMessage(sio, BUC_ID, SourceID, "MS", BUCCommand[4].CmdLength, BUCCommand[4].CmdData);
	}
	else if ((tempptr[POS_CMD] == 'A') && (tempptr[POS_CMD + 1] == '1'))
	{
		SetBUCAttenFlag = TRUE;
		Run_Polling_Once = TRUE;
		SendBUCAttenCmdFlag = TRUE;
		PollingTcik = 0;
		BUC_Atten = ASC2toHEX(tempptr + POS_DATA);
		SendUART(SIO3, tempLength, tempptr);
	}
	else if ((tempptr[POS_CMD] == 'S') && (tempptr[POS_CMD + 1] == 'O'))
	{
		SetBUCOnFlag = TRUE;
		Run_Polling_Once = TRUE;
		SendBUCOnCmdFlag = TRUE;
		ResendCounter = 0;
		SendUART(SIO3, tempLength, tempptr);
	}
	else if ((tempptr[POS_CMD] == 'S') && (tempptr[POS_CMD + 1] == 'F'))
	{
		SetBUCOffFlag = TRUE;
		Run_Polling_Once = TRUE;
		SendBUCOffCmdFlag = TRUE;
		ResendCounter = 0;
		SendUART(SIO3, tempLength, tempptr);
	}
	else // if unknow command, directly forward to BUC
	{
		SendUART(SIO3, tempLength, tempptr);
	}
/*
	if (BUCCommFlag == TRUE)
	{
		if (sio == SIO1)
		{
			SourceID[0] = rx_buffer1[POS_SRC_ID];
			SourceID[1] = rx_buffer1[POS_SRC_ID + 1];
			SourceID[2] = rx_buffer1[POS_SRC_ID + 2];
		}
		else
		{
			SourceID[0] = rx_buffer0[POS_SRC_ID];
			SourceID[1] = rx_buffer0[POS_SRC_ID + 1];
			SourceID[2] = rx_buffer0[POS_SRC_ID + 2];
		}
		
		// answer BUC command with BUC buffer
		if ((rx_buffer0[POS_CMD] == 'A') && (rx_buffer0[POS_CMD + 1] == 'S'))
		{
			SendMessage(sio, BUC_ID, SourceID, "AS", BUCCommand[0].CmdLength, BUCCommand[0].CmdData);
		}
		else if ((rx_buffer0[POS_CMD] == 'V') && (rx_buffer0[POS_CMD + 1] == 'E'))
		{
			SendMessage(sio, BUC_ID, SourceID, "VE", BUCCommand[1].CmdLength, BUCCommand[1].CmdData);
		}
		else if ((rx_buffer0[POS_CMD] == 'A') && (rx_buffer0[POS_CMD + 1] == 'D'))
		{
			SendMessage(sio, BUC_ID, SourceID, "AD", BUCCommand[2].CmdLength, BUCCommand[2].CmdData);
		}
		else if ((rx_buffer0[POS_CMD] == 'D') && (rx_buffer0[POS_CMD + 1] == 'A'))
		{
			SendMessage(sio, BUC_ID, SourceID, "DA", BUCCommand[3].CmdLength, BUCCommand[3].CmdData);
		}
		else // if unknow command, directly forward to BUC
		{
			SendUART(SIO2, rx_counter0, rx_buffer0);
		}
	}
	else // if BUC no comm, directly forward to BUC
	{
		SendUART(SIO2, rx_counter0, rx_buffer0);
	}
*/
}
/*-----------------------------------------------------------------------------
FUNCTION NAME: PollingBUC()

DESCRIPTION: 
	This routine sends polling command to other device (SSPA need polling BUC or stand alone RCU need polling other ODU)

INPUT PARAMETERS: 
	None

RETURN:
	None

NOTES:

-----------------------------------------------------------------------------*/
void PollingBUC(void)
{
	BYTE databuff[10];
	
	if (Run_Polling_Once == TRUE)
	{
		// check BUC communication state
		if (BUCCommFlag == TRUE)
		{
			BUCCommCounter++;
			if (BUCCommCounter > MaxBUCCmd)
			{
				BUCCommCounter = 0;
				BUCCommFlag = FALSE;
				InitialiseDualUart();
			}
		}
		if ((SetBUCAttenFlag == TRUE) && (PollingTcik == 0))
		{
			SendBUCMessage(SSPA_ID, BUC_ID, "DA", 0, NULL);
			PollingTcik++;
		}

		if ((SendBUCAttenCmdFlag == TRUE) && (PollingTcik == 1))
		{
			HEXto2ASC(BUC_Atten, databuff);
			SendBUCMessage(SSPA_ID, BUC_ID, "A1", 2, databuff);
			PollingTcik = 0;
			return;
		}
		
		if (SendBUCOnCmdFlag == TRUE)
		{
			SendBUCMessage(SSPA_ID, BUC_ID, "SO", 0, NULL);
			ResendCounter++;
			if (ResendCounter > 5)
			{
				ResendCounter = 0;
				SendBUCOnCmdFlag = FALSE;
			}
			return;
		}
		if (SendBUCOffCmdFlag == TRUE)
		{
			SendBUCMessage(SSPA_ID, BUC_ID, "SF", 0, NULL);
			ResendCounter++;
			if (ResendCounter > 5)
			{
				ResendCounter = 0;
				SendBUCOnCmdFlag = FALSE;
			}
			return;
		}
		// start polling counter, if no answer then set BUCCommFlag = FALSE
		if (PollingTcik == 0)
		{
			SendBUCMessage(SSPA_ID, BUC_ID, "AS", 0, NULL);
		}
		else if (PollingTcik == 1)
		{
			SendBUCMessage(SSPA_ID, BUC_ID, "VE", 0, NULL);
		}
		else if (PollingTcik == 2)
		{
			SendBUCMessage(SSPA_ID, BUC_ID, "AD", 0, NULL);
		}
		else if (PollingTcik == 3)
		{
			SendBUCMessage(SSPA_ID, BUC_ID, "DA", 0, NULL);
		}
		else if (PollingTcik == 4)
		{
			SendBUCMessage(SSPA_ID, BUC_ID, "MS", 0, NULL);
		}
		PollingTcik++;
		if (PollingTcik >= MaxBUCCmd)
		{
			Run_Polling_Once = FALSE;
			PollingTcik = 0;
		}
	}
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: PollingDevice()

DESCRIPTION: 
	This routine sends polling command to other device (SSPA need polling BUC or stand alone RCU need polling other ODU)

INPUT PARAMETERS: 
	None

RETURN:
	None

NOTES:

-----------------------------------------------------------------------------*/
void PollingDevice(void)
{
	PollingBUC();
	
	SendMessage(SIO3, SSPA_ID, BroadcastID, "AS", 0, NULL);
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: SendUART()

DESCRIPTION: 
	This routine sends data to UART0/1/2/3

INPUT PARAMETERS: 
	None

RETURN:
	None

NOTES:

-----------------------------------------------------------------------------*/
void SendUART(BYTE SIO, BYTE length, BYTE *data)
{
	BYTE i;

	// SIO0/1 use interrupt to send data, this can save MCU time
	// SIO2/3 use DUAL Uart FIFO to save send data, this also save MCU time
	// if we want SIO2/3 use interrupt to send data, there is some trouble for dual uart port 
	if (SIO == SIO0)
	{
		if (data != NULL)
		{
			for (i = 0; i < length; i++)
			{
				tx_buffer0[i] = data[i];
			}
			tx_buffer0[i] = END_PROMPT;
			tx_buffer0[i + 1] = END_PROMPT;
		}
		TXREG1 = tx_buffer0[POS_START];    
		tx_counter0 = 1;
		TaskDelay(TASK_TX0_TIMEOUT, PERIOD_TX_TIMEOUT, SEMA_NULL, SEMA_NULL);
		Comm0Mode485Tx();
	}
	else if (SIO == SIO1)
	{
		if (data != NULL)
		{
			for (i = 0; i < length; i++)
			{
				tx_buffer1[i] = data[i];
			}
			tx_buffer1[i] = END_PROMPT;
		}
		TXREG2 = tx_buffer1[POS_START];    
		tx_counter1 = 1;
		TaskDelay(TASK_TX1_TIMEOUT, PERIOD_TX_TIMEOUT, SEMA_NULL, SEMA_NULL);
		Comm1Mode485Tx();
	}
	else if (SIO == SIO2)
	{
		Comm2Mode485Tx();
		if (data != NULL)
		{
			for (i = 0; i < length; i++)
			{
				SendDataToUart(data[i], DUAL_UART_B);
			}
			SendDataToUart(END_PROMPT, DUAL_UART_B);
		}
		DelayMS(1);
		Comm2Mode485Rx();
	}
	else if (SIO == SIO3)
	{
		Comm3Mode485Tx();
		if (data != NULL)
		{
			for (i = 0; i < length; i++)
			{
				SendDataToUart(data[i], DUAL_UART_A);
			}
			SendDataToUart(END_PROMPT, DUAL_UART_A);
		}
		DelayMS(1);
		Comm3Mode485Rx();
	}

}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Rx0Process()

DESCRIPTION: 
    This function is the prinicipal routine that is called from the ISR handler 
    for RS232 RX Interrupt

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Rx0Process(void)
{
    BYTE tmp_byte;
    UWORDbytes temp_udata; /*UWORDbytes: data type defined in define.h */

	// SSPA protocol
    if (rx_buffer0[POS_START] == START_PROMPT)
    {
    	// check sum
		tmp_byte = GetChecksum(&rx_buffer0[POS_SRC_ID], rx_counter0 - 3);
		if (tmp_byte != ASC2toHEX(&rx_buffer0[rx_counter0 - 2]))
		{
			rx_counter0 = 0;
			return;
		}

		// check ID, own ID and broadcast ID need process
		if ((rx_buffer0[POS_DES_ID] == SSPA_ID[0]) && (rx_buffer0[POS_DES_ID + 1] == SSPA_ID[1]) && (rx_buffer0[POS_DES_ID + 2] == SSPA_ID[2]))
		{}
		// SSPA_RCU need forward message to BUC (SIO3)
		else if ((rx_buffer0[POS_DES_ID] == BroadcastID[0]) && (rx_buffer0[POS_DES_ID + 1] == BroadcastID[1]) && (rx_buffer0[POS_DES_ID + 2] == BroadcastID[2]))
		{
			SendUART(SIO3, rx_counter0, rx_buffer0);
		}
		else if ((rx_buffer0[POS_DES_ID] == BUC_ID[0]) && (rx_buffer0[POS_DES_ID + 1] == BUC_ID[1]) && (rx_buffer0[POS_DES_ID + 2] == BUC_ID[2]))
		{
			// if unknow command then forward to BUC directly
			BUCCommandProcess(SIO0);
			SIO0_ID[0] = rx_buffer0[POS_SRC_ID];
			SIO0_ID[1] = rx_buffer0[POS_SRC_ID + 1];
			SIO0_ID[2] = rx_buffer0[POS_SRC_ID + 2];
			rx_counter0 = 0;
			return;
		}
		else 
		{
			SendUART(SIO3, rx_counter0, rx_buffer0);
			rx_counter0 = 0;
			return;
		}		

		// check data length
		if (rx_counter0 == (POS_DATA_LEN + 2))
		{
			data_field_length0 = 0;
		}
		else
		{
			data_field_length0 = rx_buffer0[POS_DATA_LEN] - '0';
			if (data_field_length0 == (rx_counter0 - POS_DATA_LEN - 3)) // check data length, 13 bytes 
			{
				data_field0 = rx_buffer0 + POS_DATA;			
			}
			else
			{	 
				rx_counter0 = 0;
				return;
			}
		}	
		
		SIO0_ID[0] = rx_buffer0[POS_SRC_ID];
		SIO0_ID[1] = rx_buffer0[POS_SRC_ID + 1];
		SIO0_ID[2] = rx_buffer0[POS_SRC_ID + 2];
				 
		des_id[0] = rx_buffer0[POS_SRC_ID];
		des_id[1] = rx_buffer0[POS_SRC_ID + 1];
		des_id[2] = rx_buffer0[POS_SRC_ID + 2];
		
		src_id[0] = SSPA_ID[0];
		src_id[1] = SSPA_ID[1];
		src_id[2] = SSPA_ID[2];	 
		
		temp_udata.high = rx_buffer0[POS_CMD];
		temp_udata.low	= rx_buffer0[POS_CMD + 1];
		command0 = temp_udata.data;	  
		rx_counter0 = 0; 	  
		SSPACommandProcess(SIO0, command0); 			 
		
		Comm0RxCounter = 0;
    }
    // RCU protocol
    else if (rx_buffer0[POS_START] == START_PROMPT_NEW)
    {
    	// check sum
		tmp_byte = GetChecksum(&rx_buffer0[POS_SRC_ID_NEW], rx_counter0 - 3);
		if (tmp_byte != ASC2toHEX(&rx_buffer0[rx_counter0 - 2]))
		{
			rx_counter0 = 0;
			return;
		}

		// check ID, own ID and broadcast ID need process
		if ((rx_buffer0[POS_DES_ID_NEW] == RCU_ID[0]) && (rx_buffer0[POS_DES_ID_NEW + 1] == RCU_TYPE_ID))
		{}
		else if ((rx_buffer0[POS_DES_ID_NEW] == BroadcastIDNew) && (rx_buffer0[POS_DES_ID_NEW + 1]== RCU_TYPE_ID))
		{
		}
		else 
		{
			rx_counter0 = 0;
			return;
		}		
	
		// check data length
		if (rx_counter0 == (POS_DATA_LEN_NEW + 2))
		{
			data_field_length0 = 0;
		}
		else
		{
			data_field_length0 = rx_buffer0[POS_DATA_LEN_NEW] - '0';
			if (data_field_length0 == (rx_counter0 - POS_DATA_LEN_NEW - 3)) // check data length,  13 bytes 
			{
				data_field0 = rx_buffer0 + POS_DATA_NEW;			
			}
			else
			{	 
				rx_counter0 = 0;
				return;
			}
		}	  
			 
		des_id0_New[0] = rx_buffer0[POS_SRC_ID_NEW];
		des_id0_New[1] = rx_buffer0[POS_SRC_ID_NEW + 1];
		
		src_id0_New[0] = RCU_ID[0];
		src_id0_New[1] = RCU_ID[1];
		
		command0New.CmdByte0 = rx_buffer0[POS_CMD_NEW];
		command0New.CmdByte1 = rx_buffer0[POS_CMD_NEW + 1];
		command0New.CmdByte2 = rx_buffer0[POS_CMD_NEW + 2];
		
		rx_counter0 = 0;	   
		RCUCommandProcess(SIO0, command0New, data_field_length0);			  
		
		Comm0RxCounter = 0;
    }
    // wrong command
    else
    {
		rx_counter0 = 0; 	  
    }
        
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Rx1Process()

DESCRIPTION: 
    This function is the prinicipal routine that is called from the ISR handler 
    for RS485 RX Interrupt
	 this is ASRC port, just same as SIO0

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Rx1Process(void)
{
    BYTE tmp_byte;
    UWORDbytes temp_udata; /*UWORDbytes: data type defined in define.h */

	// SSPA protocol
    if (rx_buffer1[POS_START] == START_PROMPT)
    {
    	// check sum
		tmp_byte = GetChecksum(&rx_buffer1[POS_SRC_ID], rx_counter1 - 3);
		if (tmp_byte != ASC2toHEX(&rx_buffer1[rx_counter1 - 2]))
		{
			rx_counter1 = 0;
			return;
		}

		// check ID, own ID and broadcast ID need process
		if ((rx_buffer1[4] == SSPA_ID[0]) && (rx_buffer1[5] == SSPA_ID[1]) && (rx_buffer1[6] == SSPA_ID[2]))
		{}
		// SSPA_RCU need forward message to BUC (SIO3)
		else if ((rx_buffer1[4] == 0x30) && (rx_buffer1[5] == 0x30) && (rx_buffer1[6] == 0x30))
		{
			SendUART(SIO3, rx_counter1, rx_buffer1);
		}
		else if ((rx_buffer1[POS_DES_ID] == BUC_ID[0]) && (rx_buffer1[POS_DES_ID + 1] == BUC_ID[1]) && (rx_buffer1[POS_DES_ID + 2] == BUC_ID[2]))
		{
			// if unknow command then forward to BUC directly
			BUCCommandProcess(SIO1);
			SIO1_ID[0] = rx_buffer1[POS_SRC_ID];
			SIO1_ID[1] = rx_buffer1[POS_SRC_ID + 1];
			SIO1_ID[2] = rx_buffer1[POS_SRC_ID + 2];
			rx_counter1 = 0;
			return;
		}
		else 
		{
			SendUART(SIO3, rx_counter1, rx_buffer1);
			rx_counter1 = 0;
			return;
		}		

		// check data length
		if (rx_counter1 == (POS_DATA_LEN + 2))
		{
			data_field_length1 = 0;
		}
		else
		{
			data_field_length1 = rx_buffer1[POS_DATA_LEN] - '0';
			if (data_field_length1 == (rx_counter1 - POS_DATA_LEN - 3)) // check data length, 13 bytes 
			{
				data_field1 = rx_buffer1 + POS_DATA;			
			}
			else
			{	 
				rx_counter1 = 0;
				return;
			}
		}	  
		
		SIO1_ID[0] = rx_buffer1[POS_SRC_ID];
		SIO1_ID[1] = rx_buffer1[POS_SRC_ID + 1];
		SIO1_ID[2] = rx_buffer1[POS_SRC_ID + 2];
				 
		des_id[0] = rx_buffer1[POS_SRC_ID];
		des_id[1] = rx_buffer1[POS_SRC_ID + 1];
		des_id[2] = rx_buffer1[POS_SRC_ID + 2];
		
		src_id[0] = SSPA_ID[0];
		src_id[1] = SSPA_ID[1];
		src_id[2] = SSPA_ID[2];	 
		
		temp_udata.high = rx_buffer1[POS_CMD];
		temp_udata.low	= rx_buffer1[POS_CMD + 1];
		command1 = temp_udata.data;	  
		rx_counter1 = 0; 	  
		SSPACommandProcess(SIO1, command1); 			 
		
		Comm1RxCounter = 0;
    }
    // RCU protocol
    else if (rx_buffer1[POS_START] == START_PROMPT_NEW)
    {
    	// check sum
		tmp_byte = GetChecksum(&rx_buffer1[POS_SRC_ID_NEW], rx_counter1 - 3);
		if (tmp_byte != ASC2toHEX(&rx_buffer1[rx_counter1 - 2]))
		{
			rx_counter1 = 0;
			return;
		}

		// check ID, own ID and broadcast ID need process
		if ((rx_buffer1[POS_DES_ID_NEW] == RCU_ID[0]) && (rx_buffer1[POS_DES_ID_NEW + 1] == RCU_TYPE_ID))
		{}
		else if ((rx_buffer1[POS_DES_ID_NEW] == BroadcastIDNew) && (rx_buffer1[POS_DES_ID_NEW + 1]== RCU_TYPE_ID))
		{
		}
		else 
		{
			rx_counter1 = 0;
			return;
		}		
	
		// check data length
		if (rx_counter1 == (POS_DATA_LEN_NEW + 2))
		{
			data_field_length1 = 0;
		}
		else
		{
			data_field_length1 = rx_buffer1[POS_DATA_LEN_NEW] - '0';
			if (data_field_length1 == (rx_counter1 - POS_DATA_LEN_NEW - 3)) // check data length,  13 bytes 
			{
				data_field1 = rx_buffer1 + POS_DATA_NEW;			
			}
			else
			{	 
				rx_counter1 = 0;
				return;
			}
		}	  
			 
		des_id1_New[0] = rx_buffer1[POS_SRC_ID_NEW];
		des_id1_New[1] = rx_buffer1[POS_SRC_ID_NEW + 1];
		
		src_id1_New[0] = RCU_ID[0];
		src_id1_New[1] = RCU_ID[1];
		
		command1New.CmdByte0 = rx_buffer1[POS_CMD_NEW];
		command1New.CmdByte1 = rx_buffer1[POS_CMD_NEW + 1];
		command1New.CmdByte2 = rx_buffer1[POS_CMD_NEW + 2];
		
		rx_counter1 = 0;	   
		RCUCommandProcess(SIO1, command1New, data_field_length1);			  
		
		Comm1RxCounter = 0;
    }
    // wrong command
    else
    {
		rx_counter1 = 0; 	  
    }
        
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: Rx2Process()

DESCRIPTION: 
    This function is the prinicipal routine that is called from the ISR handler 
    for RS485 RX Interrupt

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES: This connect to SNMP agent, so not forward SNMP agent polling command to BUC.

-----------------------------------------------------------------------------*/
void Rx2Process(void)
{
    BYTE tmp_byte;
    UWORDbytes temp_udata; /*UWORDbytes: data type defined in define.h */

	// SSPA protocol
    if (rx_buffer2[POS_START] == START_PROMPT)
    {
    	// check sum
		tmp_byte = GetChecksum(&rx_buffer2[POS_SRC_ID], rx_counter2 - 3);
		if (tmp_byte != ASC2toHEX(&rx_buffer2[rx_counter2 - 2]))
		{
			rx_counter2 = 0;
			return;
		}

		// check ID, own ID and broadcast ID need process
		if ((rx_buffer2[4] == SSPA_ID[0]) && (rx_buffer2[5] == SSPA_ID[1]) && (rx_buffer2[6] == SSPA_ID[2]))
		{}
		// SSPA_RCU need forward message to BUC (SIO3)
		else if ((rx_buffer2[4] == 0x30) && (rx_buffer2[5] == 0x30) && (rx_buffer2[6] == 0x30))
		{
//			SendUART(SIO3, rx_counter2, rx_buffer2);
			// test
			// if unknow command then forward to BUC directly
			BUCCommandProcess(SIO2);
			// test
		}
		else if ((rx_buffer2[POS_DES_ID] == BUC_ID[0]) && (rx_buffer2[POS_DES_ID + 1] == BUC_ID[1]) && (rx_buffer2[POS_DES_ID + 2] == BUC_ID[2]))
		{
			// if unknow command then forward to BUC directly
			BUCCommandProcess(SIO2);
			SIO2_ID[0] = rx_buffer2[POS_SRC_ID];
			SIO2_ID[1] = rx_buffer2[POS_SRC_ID + 1];
			SIO2_ID[2] = rx_buffer2[POS_SRC_ID + 2];
			rx_counter2 = 0;
			return;
		}
		else 
		{
			SendUART(SIO3, rx_counter2, rx_buffer2);
			rx_counter2 = 0;
			return;
		}		

		// check data length
		if (rx_counter2 == (POS_DATA_LEN + 2))
		{
			data_field_length2 = 0;
		}
		else
		{
			data_field_length2 = rx_buffer2[POS_DATA_LEN] - '0';
			if (data_field_length2 == (rx_counter2 - POS_DATA_LEN - 3)) // check data length, 13 bytes 
			{
				data_field2 = rx_buffer2 + POS_DATA;			
			}
			else
			{	 
				rx_counter2 = 0;
				return;
			}
		}	  
		
		SIO2_ID[0] = rx_buffer2[POS_SRC_ID];
		SIO2_ID[1] = rx_buffer2[POS_SRC_ID + 1];
		SIO2_ID[2] = rx_buffer2[POS_SRC_ID + 2];
				 
		des_id[0] = rx_buffer2[POS_SRC_ID];
		des_id[1] = rx_buffer2[POS_SRC_ID + 1];
		des_id[2] = rx_buffer2[POS_SRC_ID + 2];
		
		src_id[0] = SSPA_ID[0];
		src_id[1] = SSPA_ID[1];
		src_id[2] = SSPA_ID[2];	 
		
		temp_udata.high = rx_buffer2[POS_CMD];
		temp_udata.low	= rx_buffer2[POS_CMD + 1];
		command2 = temp_udata.data;	  
		rx_counter2 = 0; 	  
		SSPACommandProcess(SIO2, command2); 			 
    }
    // RCU protocol
    else if (rx_buffer2[POS_START] == START_PROMPT_NEW)
    {
    	// check sum
		tmp_byte = GetChecksum(&rx_buffer2[POS_SRC_ID_NEW], rx_counter2 - 3);
		if (tmp_byte != ASC2toHEX(&rx_buffer2[rx_counter2 - 2]))
		{
			rx_counter2 = 0;
			return;
		}

		// check ID, own ID and broadcast ID need process
		if ((rx_buffer2[POS_DES_ID_NEW] == RCU_ID[0]) && (rx_buffer2[POS_DES_ID_NEW + 1] == RCU_TYPE_ID))
		{}
		else if ((rx_buffer2[POS_DES_ID_NEW] == BroadcastIDNew) && (rx_buffer2[POS_DES_ID_NEW + 1]== RCU_TYPE_ID))
		{
		}
		else 
		{
			rx_counter2 = 0;
			return;
		}		
	
		// check data length
		if (rx_counter2 == (POS_DATA_LEN_NEW + 2))
		{
			data_field_length2 = 0;
		}
		else
		{
			data_field_length2 = rx_buffer2[POS_DATA_LEN_NEW] - '0';
			if (data_field_length2 == (rx_counter2 - POS_DATA_LEN_NEW - 3)) // check data length,  13 bytes 
			{
				data_field2 = rx_buffer2 + POS_DATA_NEW;			
			}
			else
			{	 
				rx_counter2 = 0;
				return;
			}
		}	  
			 
		des_id2_New[0] = rx_buffer2[POS_SRC_ID_NEW];
		des_id2_New[1] = rx_buffer2[POS_SRC_ID_NEW + 1];
		
		src_id2_New[0] = RCU_ID[0];
		src_id2_New[1] = RCU_ID[1];
		
		command2New.CmdByte0 = rx_buffer2[POS_CMD_NEW];
		command2New.CmdByte1 = rx_buffer2[POS_CMD_NEW + 1];
		command2New.CmdByte2 = rx_buffer2[POS_CMD_NEW + 2];
		
		rx_counter2 = 0;	   
		RCUCommandProcess(SIO2, command2New, data_field_length2);			  
    }
    // wrong command
    else
    {
		rx_counter2 = 0; 	  
    }
        
}

/*
{
	// forward all BUC message to PC
    SendUART(SIO0, rx_counter2, rx_buffer2);
    rx_counter2 = 0;
}
*/
/*-----------------------------------------------------------------------------
FUNCTION NAME: Rx3Process()

DESCRIPTION: 
    This function is the prinicipal routine that is called from the ISR handler 
    for RS485 RX Interrupt

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void Rx3Process(void)
{
    BYTE tmp_byte, i;
    
	// communicate with BUC
    if (rx_buffer3[POS_START] == START_PROMPT)
    {
    	// check sum
		tmp_byte = GetChecksum(&rx_buffer3[POS_SRC_ID], rx_counter3 - 3);
		if (tmp_byte != ASC2toHEX(&rx_buffer3[rx_counter3 - 2]))
		{
			rx_counter3 = 0;
			return;
		}

		// if destination ID is not SSPA, forward to PC/ASRC
		if (!((rx_buffer3[POS_DES_ID] == SSPA_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SSPA_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SSPA_ID[2])))
		{
			if ((rx_buffer3[POS_DES_ID] == SIO0_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO0_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO0_ID[2]))
				SendUART(SIO0, rx_counter3, rx_buffer3);
			if ((rx_buffer3[POS_DES_ID] == SIO1_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO1_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO1_ID[2]))
				SendUART(SIO1, rx_counter3, rx_buffer3);
			if ((rx_buffer3[POS_DES_ID] == SIO2_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO2_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO2_ID[2]))
				SendUART(SIO2, rx_counter3, rx_buffer3);
			rx_counter3 = 0;
			return;
		}
		
		// check ID, if source ID is BUC ID then save this command buffer
		if ((rx_buffer3[POS_SRC_ID] == BUC_ID[0]) && (rx_buffer3[POS_SRC_ID + 1] == BUC_ID[1]) && (rx_buffer3[POS_SRC_ID + 2] == BUC_ID[2]))
		{
			BUCCommFlag = TRUE;
			BUCCommCounter = 0;

			if ((rx_buffer3[POS_CMD] == 'A') && (rx_buffer3[POS_CMD + 1] == 'S'))
			{
				BUCCommand[0].CmdByte0 = rx_buffer3[POS_CMD];
				BUCCommand[0].CmdByte1 = rx_buffer3[POS_CMD + 1];
				BUCCommand[0].CmdLength = rx_buffer3[POS_DATA_LEN] - '0';
				if (BUCCommand[0].CmdLength < 30)
				{
					for (i = 0; i < BUCCommand[0].CmdLength; i++)
					{
						BUCCommand[0].CmdData[i] = rx_buffer3[POS_DATA + i];
					}
				}
				
				// get BUC attenuator
				BUC_Atten = ASC2toHEX(BUCCommand[0].CmdData + 8);
			}
			else if ((rx_buffer3[POS_CMD] == 'V') && (rx_buffer3[POS_CMD + 1] == 'E'))
			{
				BUCCommand[1].CmdByte0 = rx_buffer3[POS_CMD];
				BUCCommand[1].CmdByte1 = rx_buffer3[POS_CMD + 1];
				BUCCommand[1].CmdLength = rx_buffer3[POS_DATA_LEN] - '0';
				if (BUCCommand[1].CmdLength < 30)
				{
					for (i = 0; i < BUCCommand[1].CmdLength; i++)
					{
						BUCCommand[1].CmdData[i] = rx_buffer3[POS_DATA + i];
					}
				}
			}
			else if ((rx_buffer3[POS_CMD] == 'A') && (rx_buffer3[POS_CMD + 1] == 'D'))
			{
				BUCCommand[2].CmdByte0 = rx_buffer3[POS_CMD];
				BUCCommand[2].CmdByte1 = rx_buffer3[POS_CMD + 1];
				BUCCommand[2].CmdLength = rx_buffer3[POS_DATA_LEN] - '0';
				if (BUCCommand[1].CmdLength < 30)
				{
					for (i = 0; i < BUCCommand[2].CmdLength; i++)
					{
						BUCCommand[2].CmdData[i] = rx_buffer3[POS_DATA + i];
					}
				}
			}
			else if ((rx_buffer3[POS_CMD] == 'D') && (rx_buffer3[POS_CMD + 1] == 'A'))
			{
				if (SetBUCAttenFlag == TRUE)
				{
					if (BUC_Atten == ASC2toHEX(rx_buffer3 + POS_DATA))
					{
						SetBUCAttenFlag = FALSE;
						SendBUCAttenCmdFlag = FALSE;
					}
					else
					{
						SendBUCAttenCmdFlag = TRUE;
					}
				}
				BUCCommand[3].CmdByte0 = rx_buffer3[POS_CMD];
				BUCCommand[3].CmdByte1 = rx_buffer3[POS_CMD + 1];
				BUCCommand[3].CmdLength = rx_buffer3[POS_DATA_LEN] - '0';
				if (BUCCommand[3].CmdLength < 30)
				{
					for (i = 0; i < BUCCommand[3].CmdLength; i++)
					{
						BUCCommand[3].CmdData[i] = rx_buffer3[POS_DATA + i];
					}
				}
			}
			else if ((rx_buffer3[POS_CMD] == 'M') && (rx_buffer3[POS_CMD + 1] == 'S'))
			{
				BUCCommand[4].CmdByte0 = rx_buffer3[POS_CMD];
				BUCCommand[4].CmdByte1 = rx_buffer3[POS_CMD + 1];
				BUCCommand[4].CmdLength = rx_buffer3[POS_DATA_LEN] - '0';
				if (BUCCommand[4].CmdLength < 30)
				{
					for (i = 0; i < BUCCommand[4].CmdLength; i++)
					{
						BUCCommand[4].CmdData[i] = rx_buffer3[POS_DATA + i];
					}
				}
			}
			else if ((rx_buffer3[POS_CMD] == 'S') && (rx_buffer3[POS_CMD + 1] == 'O'))
			{
				if (SetBUCOnFlag == TRUE)
				{
					SetBUCOnFlag = FALSE;
					SendBUCOnCmdFlag = FALSE;
				}
				if ((rx_buffer3[POS_DES_ID] == SIO0_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO0_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO0_ID[2]))
					SendUART(SIO0, rx_counter3, rx_buffer3);
				if ((rx_buffer3[POS_DES_ID] == SIO1_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO1_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO1_ID[2]))
					SendUART(SIO1, rx_counter3, rx_buffer3);
				if ((rx_buffer3[POS_DES_ID] == SIO2_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO2_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO2_ID[2]))
					SendUART(SIO2, rx_counter3, rx_buffer3);
			}
			else if ((rx_buffer3[POS_CMD] == 'S') && (rx_buffer3[POS_CMD + 1] == 'F'))
			{
				if (SetBUCOffFlag == TRUE)
				{
					SetBUCOffFlag = FALSE;
					SendBUCOffCmdFlag = FALSE;
				}
				if ((rx_buffer3[POS_DES_ID] == SIO0_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO0_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO0_ID[2]))
					SendUART(SIO0, rx_counter3, rx_buffer3);
				if ((rx_buffer3[POS_DES_ID] == SIO1_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO1_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO1_ID[2]))
					SendUART(SIO1, rx_counter3, rx_buffer3);
				if ((rx_buffer3[POS_DES_ID] == SIO2_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO2_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO2_ID[2]))
					SendUART(SIO2, rx_counter3, rx_buffer3);
			}
			else // if unknow command directly forward to PC
			{
				if ((rx_buffer3[POS_DES_ID] == SIO0_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO0_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO0_ID[2]))
					SendUART(SIO0, rx_counter3, rx_buffer3);
				if ((rx_buffer3[POS_DES_ID] == SIO1_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO1_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO1_ID[2]))
					SendUART(SIO1, rx_counter3, rx_buffer3);
				if ((rx_buffer3[POS_DES_ID] == SIO2_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO2_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO2_ID[2]))
					SendUART(SIO2, rx_counter3, rx_buffer3);
			}
		}
		else // if unknow command directly forward to PC
		{
			if ((rx_buffer3[POS_DES_ID] == SIO0_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO0_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO0_ID[2]))
				SendUART(SIO0, rx_counter3, rx_buffer3);
			if ((rx_buffer3[POS_DES_ID] == SIO1_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO1_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO1_ID[2]))
				SendUART(SIO1, rx_counter3, rx_buffer3);
			if ((rx_buffer3[POS_DES_ID] == SIO2_ID[0]) && (rx_buffer3[POS_DES_ID + 1] == SIO2_ID[1]) && (rx_buffer3[POS_DES_ID + 2] == SIO2_ID[2]))
				SendUART(SIO2, rx_counter3, rx_buffer3);
			rx_counter2 = 0;
			return;
		}		
    }
    rx_counter3 = 0;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: SendMessage()

DESCRIPTION: 
    This routine sends data to UART1

INPUT PARAMETERS: 
    char - Source ID
    char - Destination ID
    const rom char - pointer to the command
    BYTE - Length of the buffer
    BYTE - Pointer to the buffer

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void SendMessage(BYTE sio, 
				  char *src_id,
                  char *des_id, 
                  const rom char *cmd, 
                  BYTE length, 
                  BYTE *data)
{
    BYTE i, tmp_byte, chksum[2];
    BYTE * temp_prt;

    switch (sio)
    {
    	case SIO3:
    	{
    		temp_prt = tx_buffer3;
    	}
    	break;
    	case SIO2:
    	{
    		temp_prt = tx_buffer2;
    	}
    	break;
    	case SIO1:
    	{
    		temp_prt = tx_buffer1;
    	}
    	break;
    	case SIO0:
    	default:
    	{
    		temp_prt = tx_buffer0;
    	}
    	break;
    }

    temp_prt[POS_START] = START_PROMPT;
    temp_prt[POS_SRC_ID] = src_id[0];
    temp_prt[POS_SRC_ID + 1] = src_id[1];
    temp_prt[POS_SRC_ID + 2] = src_id[2];
    temp_prt[POS_DES_ID] = des_id[0];
    temp_prt[POS_DES_ID + 1] = des_id[1];
    temp_prt[POS_DES_ID + 2] = des_id[2];
    temp_prt[POS_CMD] = (BYTE) cmd[0];
    temp_prt[POS_CMD + 1] = (BYTE) cmd[1];

    DelayMS(2);  // delay 2 ms, incase the message cannot be received by handheld controller

    if (data != NULL)
    {
        temp_prt[POS_DATA_LEN] = 0x30 + length;
        for (i = 0; i < length; i++)
        {
            temp_prt[POS_DATA + i] = data[i];
        }
        tmp_byte = GetChecksum(&temp_prt[POS_SRC_ID], POS_DATA + length - 1);        
        HEXto2ASC(tmp_byte, chksum);
        temp_prt[POS_DATA + length] = chksum[0];
        temp_prt[POS_DATA + length + 1] = chksum[1];
        temp_prt[POS_DATA + length + 2] = END_PROMPT;    
    }
    else
    {
        tmp_byte = GetChecksum(&temp_prt[POS_SRC_ID], POS_CMD + 1);
        HEXto2ASC(tmp_byte, chksum);        
        temp_prt[POS_CMD + 2] = chksum[0];        
        temp_prt[POS_CMD + 3] = chksum[1];
        temp_prt[POS_CMD + 4] = END_PROMPT;
        
    }
    if (sio == SIO0)
    {
		TXREG1 = temp_prt[POS_START];	 
		tx_counter0 = 1;
		TaskDelay(TASK_TX0_TIMEOUT, PERIOD_TX_TIMEOUT, SEMA_NULL, SEMA_NULL);
		Comm0Mode485Tx();
    }
    else if (sio == SIO1)
    {
		TXREG2 = temp_prt[POS_START];	 
		tx_counter1 = 1;
		TaskDelay(TASK_TX1_TIMEOUT, PERIOD_TX_TIMEOUT, SEMA_NULL, SEMA_NULL);
		Comm1Mode485Tx();
    }
    else if (sio == SIO2)
    {
    	if (data == NULL)
			SendUART(SIO2, 12, tx_buffer2);
    	else
			SendUART(SIO2, length + 13, tx_buffer2);
    }
    else if (sio == SIO3)
    {
    	if (data == NULL)
			SendUART(SIO3, 12, tx_buffer3);
		else
			SendUART(SIO3, length + 13, tx_buffer3);
    }
    
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: SendBUCMessage()

DESCRIPTION: 
    This routine sends data to UART1

INPUT PARAMETERS: 
    char - Source ID
    char - Destination ID
    const rom char - pointer to the command
    BYTE - Length of the buffer
    BYTE - Pointer to the buffer

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void SendBUCMessage(char *src_id1,
                  char *des_id1, 
                  const rom char *cmd, 
                  BYTE length, 
                  BYTE *data)
{
    BYTE i, tmp_byte, chksum[2];

    tx_buffer3[POS_START] = START_PROMPT;
    tx_buffer3[POS_SRC_ID] = src_id1[0];
    tx_buffer3[POS_SRC_ID + 1] = src_id1[1];
    tx_buffer3[POS_SRC_ID + 2] = src_id1[2];
    tx_buffer3[POS_DES_ID] = des_id1[0];
    tx_buffer3[POS_DES_ID + 1] = des_id1[1];
    tx_buffer3[POS_DES_ID + 2] = des_id1[2];
    tx_buffer3[POS_CMD] = (BYTE) cmd[0];
    tx_buffer3[POS_CMD + 1] = (BYTE) cmd[1];

    DelayMS(2);  // delay 2 ms, incase the message cannot be received by handheld controller

    if (data != NULL)
    {
        tx_buffer3[POS_DATA_LEN] = 0x30 + length;
        for (i = 0; i < length; i++)
        {
            tx_buffer3[POS_DATA + i] = data[i];
        }
        tmp_byte = GetChecksum(&tx_buffer3[POS_SRC_ID], POS_DATA + length - 1);        
        HEXto2ASC(tmp_byte, chksum);
        tx_buffer3[POS_DATA + length] = chksum[0];
        tx_buffer3[POS_DATA + length + 1] = chksum[1];
        tx_buffer3[POS_DATA + length + 2] = END_PROMPT;    
    }
    else
    {
        tmp_byte = GetChecksum(&tx_buffer3[POS_SRC_ID], POS_CMD + 1);
        HEXto2ASC(tmp_byte, chksum);        
        tx_buffer3[POS_CMD + 2] = chksum[0];        
        tx_buffer3[POS_CMD + 3] = chksum[1];
        tx_buffer3[POS_CMD + 4] = END_PROMPT;
        
    }
    SendUART(SIO3, length + 11, tx_buffer3);
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: SendRCUMessage()

DESCRIPTION: 
    This routine sends data to UART1

INPUT PARAMETERS: 
    char - Source ID
    char - Destination ID
    const rom char - pointer to the command
    BYTE - Ack of the buffer
    BYTE - Length of the buffer
    BYTE - Pointer to the buffer

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void SendRCUMessage(BYTE sio, 
				  char *src_id1,
                  char *des_id1, 
                  const rom char *cmd, 
                  BYTE ack, 
                  BYTE length, 
                  BYTE *data)
{
    BYTE i, tmp_byte, chksum[2];
    BYTE * temp_prt;

    switch (sio)
    {
    	case SIO3:
    	{
    		temp_prt = tx_buffer3;
    	}
    	break;
    	case SIO2:
    	{
    		temp_prt = tx_buffer2;
    	}
    	break;
    	case SIO1:
    	{
    		temp_prt = tx_buffer1;
    	}
    	break;
    	case SIO0:
    	default:
    	{
    		temp_prt = tx_buffer0;
    	}
    	break;
    }

    temp_prt[POS_START] = START_PROMPT_NEW;
    temp_prt[POS_SRC_ID_NEW] = src_id1[0];
    temp_prt[POS_SRC_ID_NEW + 1] = src_id1[1];
    temp_prt[POS_DES_ID_NEW] = des_id1[0];
    temp_prt[POS_DES_ID_NEW + 1] = des_id1[1];
    temp_prt[POS_CMD_NEW] = (BYTE) cmd[0];
    temp_prt[POS_CMD_NEW + 1] = (BYTE) cmd[1];
    temp_prt[POS_CMD_NEW + 2] = (BYTE) cmd[2];
    temp_prt[POS_ACK_NEW] = ack;

    if (data != NULL)
    {
        temp_prt[POS_DATA_LEN_NEW] = 0x30 + length;
        temp_prt[POS_ACK_NEW] = ack; // ACK
        for (i = 0; i < length; i++)
        {
            temp_prt[POS_DATA_NEW + 1 + i] = data[i];
        }
        tmp_byte = GetChecksum(&temp_prt[POS_SRC_ID_NEW], POS_DATA_NEW + length);        
        HEXto2ASC(tmp_byte, chksum);
        temp_prt[POS_DATA_NEW + 1 + length] = chksum[0];
        temp_prt[POS_DATA_NEW + 1 + length + 1] = chksum[1];
        temp_prt[POS_DATA_NEW + 1 + length + 2] = END_PROMPT;    
    }
    else
    {
        temp_prt[POS_DATA_LEN_NEW] = 0x30; // NULL length is 1, ACK
        temp_prt[POS_ACK_NEW] = ack; // ACK
        tmp_byte = GetChecksum(&temp_prt[POS_SRC_ID_NEW], POS_DATA_NEW);
        HEXto2ASC(tmp_byte, chksum);        
        temp_prt[POS_CMD_NEW + 5] = chksum[0];        
        temp_prt[POS_CMD_NEW + 6] = chksum[1];
        temp_prt[POS_CMD_NEW + 7] = END_PROMPT;
        
    }
    
    if (sio == SIO0)
    {
		TXREG1 = temp_prt[POS_START];	 
		tx_counter0 = 1;
		TaskDelay(TASK_TX0_TIMEOUT, PERIOD_TX_TIMEOUT, SEMA_NULL, SEMA_NULL);
		Comm0Mode485Tx();
    }
    else if (sio == SIO1)
    {
		TXREG2 = temp_prt[POS_START];	 
		tx_counter1 = 1;
		TaskDelay(TASK_TX1_TIMEOUT, PERIOD_TX_TIMEOUT, SEMA_NULL, SEMA_NULL);
		Comm1Mode485Tx();
    }
    else if (sio == SIO2)
    {
    	if (data == NULL)
			SendUART(SIO2, 13, tx_buffer2);
    	else
			SendUART(SIO2, length + 13, tx_buffer2);
    }
    else if (sio == SIO3)
    {
    	if (data == NULL)
			SendUART(SIO3, 13, tx_buffer3);
		else
			SendUART(SIO3, length + 13, tx_buffer3);
    }
}
#endif
/*-----------------------------------------------------------------------------
FUNCTION NAME: DelayMS()

DESCRIPTION: 
    This routine ntroduces NOP to delay

INPUT PARAMETERS:
    unsigned int - time in ms 

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void DelayMS(unsigned int ms)
{
    unsigned int i;
    
    for (i = 1; i <= ms; i++)
    {
        Delay1KTCYx(FREQ_TCY);      
    }
}

//calc_CRC - INTERNAL FUNCTION
//Purpose:	To calculate an 8-bit CRC based on a polynomial and the series
//				of data bytes
//Note: 		Polynomial used x^8 + x^5 + x^4 + 1 = 10001100
//Inputs:	A pointer to an array of the data bytes and an int saying how many
//				bytes there are in the data array
//Outputs:	An int8 which is the calculated CRC
BYTE calc_CRC(WORD addr, WORD bytes)
{
	BYTE shift_register = 0, datab, bits;
	WORD i;

	for (i = 0; i < bytes; ++i)
	{
		XEEReadArray(addr + i, (BYTE *)&datab, 1);
		shift_register += datab;
/*
		for (bits = 0; bits < 8; ++bits)
		{
			if ((shift_register ^ datab) == 0)
			{
				shift_register = shift_register >> 1;
				shift_register ^= CRC_POLY;
			}
			else
			{
				shift_register = shift_register >> 1;
			}

			datab = datab >> 1;
		}
*/
	}
	return shift_register;
} //calc_CRC

/*----------------------
    GLOBAL FUNCTIONS
----------------------*/
/*-----------------------------------------------------------------------------
FUNCTION NAME: ResetDualUart1()

DESCRIPTION: 
	This function resets the DUAL UART 
	
INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void ResetDualUart1(void)
{
    UART_RST = LOW;
    Delay10TCYx( 10 );

    UART_RST = HIGH;
    Delay10TCYx( 20 );

    UART_RST = LOW;
    Delay10TCYx( 10 );
}

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
void WriteDualUartConf(BYTE reg_addr, BYTE val)
{
	// write A/B both side
    UART_A0 = reg_addr & 0x01;
    UART_A1 = ((reg_addr & 0x2) == 0) ? 0 : 1;
    UART_A2 = ((reg_addr & 0x4) == 0) ? 0 : 1;

    UART_DATA_DIRECTION = OUTPUT;
    DUAL_UARTA_ENABLE = CS_ENABLE;
	LATJ |= 0x40; // UART_IOWR = 1;
	LATJ |= 0x80; // UART_IORD = 1;
	
	UART_DATA = val;
	
	LATJ &= ~0x40; // UART_IOWR = 0;
	
	LATJ |= 0x40; // UART_IOWR = 1;
    DUAL_UARTA_ENABLE = CS_DISABLE;
    DUAL_UARTB_ENABLE = CS_ENABLE;
	LATJ |= 0x40; // UART_IOWR = 1;
	LATJ |= 0x80; // UART_IORD = 1;
	
	UART_DATA = val;
	
	LATJ &= ~0x40; // UART_IOWR = 0;
	
	LATJ |= 0x40; // UART_IOWR = 1;
    DUAL_UARTB_ENABLE = CS_DISABLE;
    DUAL_UARTA_ENABLE = CS_DISABLE;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: ReadDualUartConf()

DESCRIPTION: 
	This function read the internal registers of the DUAL UART
	(configuration bytes of DUAL UART)
	
INPUT PARAMETERS: 
    BYTE - Register address that is to be configured
    BYTE - Indicate which SSPA is to be read from

RETURN:
    BYTE - The read value from the register

NOTES:

-----------------------------------------------------------------------------*/
BYTE ReadDualUartConf(BYTE reg_addr, BYTE which_sspa)
{
    BYTE val;
    
	LATJ |= 0x40; // UART_IOWR = 1;
	LATJ |= 0x80; // UART_IORD = 1;
    UART_A0 = reg_addr & 0x01;
    UART_A1 = ((reg_addr & 0x2) == 0) ? 0 : 1;
    UART_A2 = ((reg_addr & 0x4) == 0) ? 0 : 1;

    UART_DATA_DIRECTION = INPUT;
	if(which_sspa == DUAL_UART_A)
    {
        DUAL_UARTA_ENABLE = CS_ENABLE;
        DUAL_UARTB_ENABLE = CS_DISABLE;
    }
    else
    {
        DUAL_UARTA_ENABLE = CS_DISABLE;
        DUAL_UARTB_ENABLE = CS_ENABLE;
    }

	LATJ |= 0x40; // UART_IOWR = 1;

	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	LATJ &= ~0x80; // UART_IORD = 0;
	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	
	val = UART_DATA;
	
	LATJ |= 0x80; // UART_IORD = 1;
	UART_DATA_DIRECTION = OUTPUT;
    DUAL_UARTB_ENABLE = CS_DISABLE;
    DUAL_UARTA_ENABLE = CS_DISABLE;
	return val;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: ReadDataFromUart()

DESCRIPTION: 
	This function reads a single byte (recvd byte) from DUAL UART
	
INPUT PARAMETERS: 
    BYTE - Indicate which SPPA is to be read from

RETURN:
    BYTE - Value read from the configuration register

NOTES:

-----------------------------------------------------------------------------*/
BYTE ReadDataFromUart(BYTE which_sspa)
{
    BYTE val;

	LATJ |= 0x40; // UART_IOWR = 1;
	LATJ |= 0x80; // UART_IORD = 1;
    UART_A0 = 0;
    UART_A1 = 0;
    UART_A2 = 0;

    UART_DATA_DIRECTION = INPUT;
    if(which_sspa == DUAL_UART_A)
    {
        DUAL_UARTA_ENABLE = CS_ENABLE;
        DUAL_UARTB_ENABLE = CS_DISABLE;
    }
    else
    {
        DUAL_UARTA_ENABLE = CS_DISABLE;
        DUAL_UARTB_ENABLE = CS_ENABLE;
    }

	LATJ |= 0x40; // UART_IOWR = 1;
	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	LATJ &= ~0x80; // UART_IORD = 0;
	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	
	val = UART_DATA;
	
	LATJ |= 0x80; // UART_IORD = 1;
	
	DUAL_UARTA_ENABLE = CS_DISABLE;
	DUAL_UARTB_ENABLE = CS_DISABLE;
	
	return val;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: ReadDataFromUartISR()

DESCRIPTION: 
	This function reads a single byte (recvd byte) from DUAL UART
	
INPUT PARAMETERS: 
    BYTE - Indicate which SPPA is to be read from

RETURN:
    BYTE - Value read from the configuration register

NOTES:

-----------------------------------------------------------------------------*/
BYTE ReadDataFromUartISR(BYTE which_sspa)
{
    BYTE val;

	LATJ |= 0x40; // UART_IOWR = 1;
	LATJ |= 0x80; // UART_IORD = 1;
    UART_A0 = 0;
    UART_A1 = 0;
    UART_A2 = 0;

    UART_DATA_DIRECTION = INPUT;
    if(which_sspa == DUAL_UART_A)
    {
        DUAL_UARTA_ENABLE = CS_ENABLE;
        DUAL_UARTB_ENABLE = CS_DISABLE;
    }
    else
    {
        DUAL_UARTA_ENABLE = CS_DISABLE;
        DUAL_UARTB_ENABLE = CS_ENABLE;
    }

	LATJ |= 0x40; // UART_IOWR = 1;
	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	LATJ &= ~0x80; // UART_IORD = 0;
	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	
	val = UART_DATA;
	
	LATJ |= 0x80; // UART_IORD = 1;
	
	DUAL_UARTA_ENABLE = CS_DISABLE;
	DUAL_UARTB_ENABLE = CS_DISABLE;
	
	return val;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: SendDataToUart()

DESCRIPTION: 
	This function writes a single byte to DUAL UART, and UART will transmit it.
 
INPUT PARAMETERS: 
    BYTE - Value to be sent/transmitted
    BYTE - Indicate which is the current SSPA

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void SendDataToUart(BYTE byte, BYTE current_sspa)
{
	BYTE stat = 0;

	if(current_sspa == DUAL_UART_A)
	{
		DUAL_UARTA_ENABLE = CS_ENABLE;
		DUAL_UARTB_ENABLE = CS_DISABLE;
	}
	else
	{
		DUAL_UARTA_ENABLE = CS_DISABLE;
		DUAL_UARTB_ENABLE = CS_ENABLE;
	}

	UART_DATA_DIRECTION = OUTPUT;
	
	// select THR 
	UART_A0 = 0;
	UART_A1 = 0;
	UART_A2 = 0;
	
	UART_DATA = byte;
	LATJ |= 0x80; // UART_IORD = 1;
	LATJ &= ~0x40; // UART_IOWR = 0;
	
	LATJ |= 0x40; // UART_IOWR = 1;
	
	DUAL_UARTA_ENABLE = CS_DISABLE;
	DUAL_UARTB_ENABLE = CS_DISABLE;
}


/*-----------------------------------------------------------------------------
FUNCTION NAME: ConfigureUartChannel()

DESCRIPTION: 
	This function writes a single byte to DUAL UART's single selected channel
	
INPUT PARAMETERS: 
    BYTE - Indiacte which SSPA to be configured
    BYTE - COnfiguration register address
    BYTE - Value to be used to configure the register address

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void ConfigureUartChannel(BYTE which_sspa, BYTE reg_addr, BYTE val)
{
    /* DUAL UART internal address is passed as reg_addr, the values of 
     * A0 A1 A2 should be extracted from reg_addr, a small logic which 
     * checks whether which pins should be set and set them accordingly 
     */
	UART_A0 = reg_addr & 0x01;
    UART_A1 = ((reg_addr & 0x02) == 0) ? 0 : 1;
    UART_A2 = ((reg_addr & 0x04) == 0) ? 0 : 1;

    UART_DATA_DIRECTION = OUTPUT;
    if(which_sspa == DUAL_UART_A)
    {
        DUAL_UARTA_ENABLE = CS_ENABLE;
        DUAL_UARTB_ENABLE = CS_DISABLE;
    }
    else
    {
        DUAL_UARTA_ENABLE = CS_DISABLE;
        DUAL_UARTB_ENABLE = CS_ENABLE;
    }

    UART_DATA = val;
	LATJ |= 0x80; // UART_IORD = 1;
	LATJ &= ~0x40; // UART_IOWR = 0;
	
	LATJ |= 0x40; // UART_IOWR = 1;

    DUAL_UARTA_ENABLE = CS_DISABLE;
    DUAL_UARTB_ENABLE = CS_DISABLE;
}

void SetDualUartBaudRate(unsigned char baudrate)
{
    BYTE statA = 0, statB = 0, cnt, temp1, temp2, temp3;
    
    ResetDualUart1();    
	WriteDualUartConf(DUAL_UART_LCR, 0x03);

	// Follow TL16C752B datasheet initialize sequence

	if (baudrate == BAUD_9600)
	{
		// 1. Set baud rate to VALUE1, VALUE2
		// Read LCR (03), save in temp
		temp1 = ReadDualUartConf(DUAL_UART_LCR, DUAL_UART_A);
		
		Delay10TCYx( 5 );
		// Set LCR (03) to 80
		WriteDualUartConf(DUAL_UART_LCR, 0x83);
		
		Delay10TCYx( 5 );
		// Set DLL (00) to VALUE1
		WriteDualUartConf(DUAL_UART_DLL, 0x0C);
		
		Delay10TCYx( 5 );
		// Set DLM (01) to VALUE2
		WriteDualUartConf(DUAL_UART_DLM, 0);
		
		Delay10TCYx( 5 );
		// Set LCR (03) to temp
		WriteDualUartConf(DUAL_UART_LCR, temp1);
	}
	else if ((baudrate == BAUD_115200))
	{
		// 1. Set baud rate to VALUE1, VALUE2
		// Read LCR (03), save in temp
		temp1 = ReadDualUartConf(DUAL_UART_LCR, DUAL_UART_A);
		
		Delay10TCYx( 5 );
		// Set LCR (03) to 80
		WriteDualUartConf(DUAL_UART_LCR, 0x83);
		
		Delay10TCYx( 5 );
		// Set DLL (00) to VALUE1
		WriteDualUartConf(DUAL_UART_DLL, 0x01);
		
		Delay10TCYx( 5 );
		// Set DLM (01) to VALUE2
		WriteDualUartConf(DUAL_UART_DLM, 0);
		
		Delay10TCYx( 5 );
		// Set LCR (03) to temp
		WriteDualUartConf(DUAL_UART_LCR, temp1);
	}
}


/*-----------------------------------------------------------------------------
FUNCTION NAME: InitialiseDualUart()

DESCRIPTION: 
	This function initialises the DUAL UART 
	
INPUT PARAMETERS: 
	None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void InitialiseDualUart(void)
{
    BYTE statA = 0, statB = 0, cnt, temp1, temp2, temp3;
    
    ResetDualUart1();    
	WriteDualUartConf(DUAL_UART_LCR, 0x03);

	// Follow TL16C752B datasheet initialize sequence
	
	// 1. Set baud rate to VALUE1, VALUE2
	// Read LCR (03), save in temp
    temp1 = ReadDualUartConf(DUAL_UART_LCR, DUAL_UART_A);

	Delay10TCYx( 5 );
	// Set LCR (03) to 80
	WriteDualUartConf(DUAL_UART_LCR, 0x83);
	
	Delay10TCYx( 5 );
	// Set DLL (00) to VALUE1
	WriteDualUartConf(DUAL_UART_DLL, 0x0C);

	Delay10TCYx( 5 );
	// Set DLM (01) to VALUE2
    WriteDualUartConf(DUAL_UART_DLM, 0);

	Delay10TCYx( 5 );
	// Set LCR (03) to temp
	WriteDualUartConf(DUAL_UART_LCR, temp1);

	// 2. Set xmt and rcv FIFO thresholds to VALUE
	// Read LCR (03), save in temp1
    temp1 = ReadDualUartConf(DUAL_UART_LCR, DUAL_UART_A);

	Delay10TCYx( 5 );
	// Set LCR (03) to BF
	WriteDualUartConf(DUAL_UART_LCR, 0xBF);

	// Read EFR (02), save in temp2
	Delay10TCYx( 5 );
	temp2 = ReadDualUartConf(DUAL_UART_EFR, DUAL_UART_A);

	// Set EFR (02) to 10 + temp2
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_EFR, temp2 + 0x10);

	// Set LCR (03) to 00
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_LCR, 0);
	
	// Read MCR (04), save in temp3
	Delay10TCYx( 5 );
	temp3 = ReadDualUartConf(DUAL_UART_MCR, DUAL_UART_A);

	// Set MCR (04) to 40 + temp3
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_MCR, temp3 + 0x40);

	// Set TLR (07) to VALUE
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_TLR, 0x44);

	// Set MCR (04) to temp3
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_MCR, temp3);

	// Set LCR (03) to BF
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_LCR, 0xBF);

	// Set EFR (02) to temp2
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_EFR, temp2);

	Delay10TCYx( 5 );
	// Set LCR (03) to temp1
	WriteDualUartConf(DUAL_UART_LCR, temp1);

	// Enable transmit/receive FIFO
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_FCR, 0x01);

	//INT A and B pins are enabled 
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_MCR, 0x08);

	// Enable the RHR interrupt 
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_IER, 0x01);
}



