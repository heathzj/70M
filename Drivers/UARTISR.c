#if defined(__18F97J60) || defined(_18F97J60)
#include "TCPIP Stack/TCPIP.h"
#endif
#include "UARTISR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include functions specific to this stack application
#include "Main.h"
#include "define.h"
#include "Global.h"
#include "timers.h"
#include "list.h"
#include "AgilisDualUART.h"
#include <usart.h>
#include "UART.h"
#include "Hardwareprofile.h"

tAgilisCircBuf agilisUART0RxCircBuf;
tAgilisCircBuf agilisUART1RxCircBuf;

volatile BYTE Uart2THREmpty = 1,Uart3THREmpty = 1,Uart4THREmpty = 1,Uart5THREmpty = 1;

void uart0init(uartDBC_t* pUart,BYTE mode)
{
#if defined(__18F97J60) || defined(_18F97J60)
    Open1USART(USART_TX_INT_ON & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW, 1); 

	SPBRGH1 = 0;
	SPBRG1 = 40;
	BAUDCON1bits.BRG16 = 0;
	TXSTA1bits.BRGH = 0;
	PIR1=PIR1&(~0x30);//*TX1IF,RC1IF
	//PIE1=PIE1|0x20;//*RC1IE
	IPR1bits.RC1IP=0;
	RCSTA1bits.CREN=1;

	RCONbits.IPEN=1;	// yt: should enable IPEN before GIE
	INTCONbits.GIEL=1;
	INTCONbits.GIEH = 1;		
	INTCONbits.GIE = 1;		//Enable global interrupts
	INTCONbits.PEIE = 1;	//Enable peripheral interrupts
#else
	// PIC18F8722
	// initialized in P18F8722Init()...
#endif

	/*
	pUart->UARTFIFODataErrorCount = 0;
	pUart->UARTFramingErrorCount = 0;
	pUart->UARTParityErrorCount = 0;
	pUart->UARTOverrunErrorCount = 0;
	*/

	//pUart->devname = 0;
	pUart->mode = mode;
	if(mode == RS232)
		Comm0Mode232();

	else if(mode == RS485)
		Comm0Mode485Rx();

	//else if(mode == RS422)	
	//	Comm0Mode422();
		

	//pUart->uartfifoinit = InitFifo0;
	pUart->uartisr = UARTISR0;
	pUart->uartread = UARTBufferTask;
	pUart->uartwrite =  UART0write;
	//pUart->uartwriterom = UART0writerom;
	pUart->receiveflag = 0;

	InitFifo0();

	// configure UART0 receive interrupt
	UART0_RX_INT_PRIORITY = INT_PRIORITY_LOW;
	// enable UART0 receive interrupt
	UART0_RX_INT_ENABLE = TRUE;
}

void uart1init(uartDBC_t* pUart,BYTE mode)
{
#if defined(__18F97J60) || defined(_18F97J60)
	Open2USART(USART_TX_INT_ON & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW, 1); 

	SPBRGH2 = 0;
	SPBRG2 = 40;

	BAUDCON2bits.BRG16 = 0;
	TXSTA2bits.BRGH = 0;

	//PIE3bits.RC2IE = 1;
	//IPR3bits.RC2IP = 0;//*high priority interrupt

	RCONbits.IPEN=1;	// yt: should enable IPEN before GIE
	INTCONbits.GIEL=1;
	INTCONbits.GIEH = 1;		
	INTCONbits.GIE = 1;		//Enable global interrupts
	INTCONbits.PEIE = 1;	//Enable peripheral interrupts
#else
	// PIC18F8722
	// initialized in P18F8722Init()...
#endif
	/*
	pUart->UARTFIFODataErrorCount = 0;
	pUart->UARTFramingErrorCount = 0;
	pUart->UARTParityErrorCount = 0;
	pUart->UARTOverrunErrorCount = 0;
	*/
	//pUart->devname = 1;
	pUart->mode = mode;
	if(mode == RS232)
		Comm1Mode232();

	else if(mode == RS485)
		Comm1Mode485Rx();

	//else if(mode == RS422)	
	//	Comm1Mode422Rx();	

	//pUart->uartfifoinit = InitFifo1;
	pUart->uartisr = UARTISR1;
	pUart->uartread = UARTBufferTask;
	pUart->uartwrite =  UART1write;
	//pUart->uartwriterom = UART0writerom;	
	pUart->receiveflag = 0;

	InitFifo1();

	UART1_RX_INT_PRIORITY = INT_PRIORITY_LOW;
	UART1_RX_INT_ENABLE = TRUE;
}


/*********************************************************************
 * Function:        void InitFifo0(void)
 *
 * PreCondition:    UART FIFO ininitialization
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            This function is supposed to be called in the ISR 
 *					context.
 ********************************************************************/

void InitFifo0(void) {
	

	Uart0.RXBuff = agilisUART0RxCircBuf.ai8AgilisCircBuf;

	AGILIS_UART0_FIFO_RD_PTR = Uart0.RXBuff;
	AGILIS_UART0_FIFO_WR_PTR = Uart0.RXBuff;
	AGILIS_UART0_FIFO_START_PTR = Uart0.RXBuff;
	AGILIS_UART0_FIFO_END_PTR = Uart0.RXBuff + (AGILIS_FIFO_SIZE - 1);
	
}

/*********************************************************************
 * Function:        void InitFifo1(void)
 *
 * PreCondition:    UART FIFO ininitialization
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            This function is supposed to be called in the ISR 
 *					context.
 ********************************************************************/

void InitFifo1() {
	

	Uart1.RXBuff = agilisUART1RxCircBuf.ai8AgilisCircBuf;

	AGILIS_UART1_FIFO_RD_PTR = Uart1.RXBuff;
	AGILIS_UART1_FIFO_WR_PTR = Uart1.RXBuff;
	AGILIS_UART1_FIFO_START_PTR = Uart1.RXBuff;
	AGILIS_UART1_FIFO_END_PTR = Uart1.RXBuff + (AGILIS_FIFO_SIZE - 1);
}


/*********************************************************************
 * Function:        void UARTISR(void)
 *
 * PreCondition:    UART ininitialization
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            This function is supposed to be called in the ISR 
 *					context.
 ********************************************************************/


#if 1
BYTE Uart0ReadPCCmd=0;
char Uart0PCCmdBuf[32]={0};
BYTE Uart0PCCmdBufCount = 0;

void UARTISR0(void)
{
	static BYTE data;
	static BYTE count=0;
	
	if(UART0_RX_INT_FLAG)
	{
		UART0_RX_INT_ENABLE = FALSE;

		data = RCREG;

		// if new command come but main.c did not use old data, throw old data
		if(Uart0ReadPCCmd == 1)
			count = 0;

		Uart0PCCmdBuf[count]=data;	

		if(count < sizeof(Uart0PCCmdBuf))
			count++;	
		else
			count=0;

		if(data == 0x0D){
			Uart0ReadPCCmd=1;
			Uart0PCCmdBufCount = count;
			count=0;
		}

		UART0_RX_INT_FLAG = 0; // yt added to clear interrupt flag
		UART0_RX_INT_ENABLE = TRUE;
	}
}

#else
void UARTISR0(void)
{
	static BYTE i;
	
	if(UART0_RX_INT_FLAG)
	{
		UART0_RX_INT_ENABLE = FALSE;

		i = RCREG;

		if (RCSTA1bits.FERR)
		{
			//Uart0.UARTFramingErrorCount++;
		}
		if (RCSTA1bits.OERR)
		{
			//Uart0.UARTOverrunErrorCount++;
			RCSTA1bits.CREN = 0; // 
			RCSTA1bits.CREN = 1; // 
		}
		if (AGILIS_UART0_FIFO_RD_PTR == AGILIS_UART0_FIFO_WR_PTR_NEXT)
		{
			//Comm0Mode485Tx();
			//putrsUART("Fifo is full\r\n"); //??
			//Comm0Mode485Rx();

			// if fifo is full as data is not taken fast enough
			// ask for data to be received by uart driver now
			Uart0.receiveflag = 1; //ask for clearing buffer
		}
		else 
		{
			*(AGILIS_UART0_FIFO_WR_PTR) = i;

			AGILIS_UART0_FIFO_WR_PTR = AGILIS_UART0_FIFO_WR_PTR_NEXT;


			if(i == END_PROMT) //??
			{
				Uart0.receiveflag  = 1; //ask for clearing buffer

			}
		}
		UART0_RX_INT_FLAG = 0; // yt added to clear interrupt flag
		UART0_RX_INT_ENABLE = TRUE;
	}

}
#endif

/*********************************************************************
 * Function:        void UARTISR2(void)
 *
 * PreCondition:    UART interrupt has occured
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            This function is supposed to be called in the ISR 
 *					context.
 ********************************************************************/


#if 1
BYTE Uart1ReadLCDCmd=0;
void UARTISR1(void)
{
	static BYTE data;
	static BYTE count=0;
	
	if(UART1_RX_INT_FLAG)
	{
		UART1_RX_INT_ENABLE = FALSE;

		data = RCREG2;

		if(data > 30 && data < 50)
			Uart1ReadLCDCmd=data;

		UART1_RX_INT_FLAG = 0; // yt added to clear interrupt flag
		UART1_RX_INT_ENABLE = TRUE;
	}
}

#else
void UARTISR1(void)
{
	// NOTE: All local variables used here should be declared static
	static BYTE i;
	
	// Store a received byte, if pending, if possible
	if(UART1_RX_INT_FLAG)
	{
		UART1_RX_INT_ENABLE = FALSE;

		i = RCREG2;

		if (RCSTA2bits.FERR)
		{
			//Uart1.UARTFramingErrorCount++;
		}
		if (RCSTA2bits.OERR)
		{
			RCSTA2bits.CREN = 0; // 
			RCSTA2bits.CREN = 1; // 
			//Uart1.UARTOverrunErrorCount++;
		}
		if (AGILIS_UART1_FIFO_RD_PTR == AGILIS_UART1_FIFO_WR_PTR_NEXT)
		{
			// if fifo is full as data is not taken fast enough
			// ask for data to be received by uart driver now
			//putrsUART2("Fifo is full\r\n"); //??
			Uart1.receiveflag  = 1;
		}
		else 
		{
			*(AGILIS_UART1_FIFO_WR_PTR) = i;

			AGILIS_UART1_FIFO_WR_PTR = AGILIS_UART1_FIFO_WR_PTR_NEXT;


			if(i == END_PROMT) //??
			{
				Uart1.receiveflag  = 1;

			}
		}
		UART1_RX_INT_FLAG = 0;
		UART1_RX_INT_ENABLE = TRUE;
	}
}
#endif

void UART0write(BYTE* data)
{

	putsUSART(data);
}

void UART1write(BYTE* data)
{
	putsUSART2(data);
}




/*********************************************************************
 * Function:        void UARTBufferTask(BYTE* ,tAgilisCircBuf* )
 *
 * PreCondition:    UART Driver called
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        None
 *
 * Note:            This function is supposed to be called in the ISR 
 *					context.
 ********************************************************************/




int UARTBufferTask(BYTE* data,tAgilisCircBuf* buf)
{

	WORD PutLen, GetLen, w,len;
	BYTE *RXHeadPtrLocal, *RXTailPtrLocal;
	BYTE *TXHeadPtrLocal, *TXTailPtrLocal;


	RXTailPtrLocal = buf->pi8AgilisCircBufRead;
	RXHeadPtrLocal = buf->pi8AgilisCircBufWrite;


	GetLen = RXHeadPtrLocal - RXTailPtrLocal;
	if(RXHeadPtrLocal < RXTailPtrLocal)
		GetLen += sizeof(buf->ai8AgilisCircBuf);
//	if(PutLen > GetLen)		
	
		PutLen = GetLen;

	len = PutLen;
	
	if(PutLen) 						
	{
		
		w = buf->ai8AgilisCircBuf + sizeof(buf->ai8AgilisCircBuf) - RXTailPtrLocal;
		if(PutLen >= w)
		{
	 		//Copy w lenght data here out
			strncpy(data,RXTailPtrLocal,w);
			RXTailPtrLocal = buf->ai8AgilisCircBuf;
			PutLen -= w;
			data+= w;
		}
 		//copy (len - w) length data here out
	   strncpy(data,RXTailPtrLocal,PutLen);
	   RXTailPtrLocal += PutLen;   
	   buf->pi8AgilisCircBufRead = RXTailPtrLocal;
	}

	return len;

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
	UART0_TX_INT_ENABLE = 0;
	UART0_RX_INT_ENABLE = 0;
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
	UART0_RX_INT_ENABLE = 1;
}

/*
void Comm0Mode422(void)
{
    MODE0 = 1;
    RXEN0 = 1;
    DXEN0 = 1;  
	UART0_TX_INT_ENABLE = 0;
	UART0_RX_INT_ENABLE = 1;
}
*/

/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm1Mode422Rx()

DESCRIPTION: 
    This function sets communication mode RS422

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
/*
void Comm1Mode422Rx(void)
{
    MODE1 = 1;
    RXEN1 = 1;
	SetCPLDGPIO(11, 1); // ON_CTRL

    DXEN1 = 0;    
}
*/
/*-----------------------------------------------------------------------------
FUNCTION NAME: Comm1Mode422Tx()

DESCRIPTION: 
    This function sets communication mode RS422

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
/*
void Comm1Mode422Tx(void)
{
    MODE1 = 1;
    RXEN1 = 0;
	SetCPLDGPIO(11, 0); // ON_CTRL

    DXEN1 = 1;    
}
*/
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
	UART1_TX_INT_ENABLE = 0;
	UART1_RX_INT_ENABLE = 0;
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
	UART1_RX_INT_ENABLE = 1;
}



