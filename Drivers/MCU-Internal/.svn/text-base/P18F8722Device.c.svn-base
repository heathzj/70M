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
#if defined(__18F8722) || defined(_18F8722)

#include <p18f8722.h>
#include <timers.h>
#include	<usart.h>
#include "Uart.h"
#include "task.h"
#include "define.h"
#include "AgilisDualUART.h"
#include "RCULLAccess.h"

void IOInit(void)
{
	ADCON1 = 0x0F; // disable internal ADC set PORTA as digital IO 
    CMCON = 0x07; // comparator setting... make RF3-RF6 as digital 
    MEMCONbits.EBDIS = 1; // enable port J, disable external memory
	
	PORTA = 0x00;// clear port A
	LATA = 0x00;// clear port A
	TRISA = 0x00;// port A set to output

	PORTB = 0x00;// clear port B
	LATB = 0x00;// clear port B
	TRISB = 0xC3;// port RB2/3/4/5 set as output, rest as input

	PORTC = 0x00;// clear port C
	LATC = 0x00;// clear port C
	TRISC = 0x80;// port RC7 set as input, rest as output

	PORTD = 0x00;// clear port D
	LATD = 0x00;// clear port D
	TRISD = 0x20;// port RD5 set as input, rest as output

	// port E is data bus
	PORTE = 0x00;// clear port E
	LATE = 0x00;// clear port E
	TRISE = 0x00;// port E set as output
	
	PORTF = 0x00;// clear port F
	LATF = 0x00;// clear port F
	TRISF = 0xFC;// port RF0/RF1 set as output, rest as input

	PORTG = 0x00;// clear port G
	LATG = 0x00;// clear port G
	TRISG = 0x04;// port RG2 set as input, rest as output

	PORTH = 0x00;// clear port H
	LATH = 0x00;// clear port H
	TRISH = 0xF8;// port RH0/RH1/RH2 set as output, rest as input

	// port E is data bus
	PORTJ = 0x00;// clear port J
	LATJ = 0x00;// clear port J
	TRISJ = 0x00;// port J set as output
	//CS_CAN = CS_DISABLE;
	CS_CPLD = CS_DISABLE;
	CS_FLASH = CS_DISABLE;
	CS_ADC1 = CS_DISABLE;
	CS_ADC0 = CS_DISABLE;
	//CS_DAC = CS_DISABLE;
}

void Timer0Init(void)
{
	T0CONbits.TMR0ON = 0;// turn off T0

	TMR0L = TMROL_VALUE; //500ms interval

	T0CONbits.T0PS2 = 0;// prescaler assignment
	T0CONbits.T0PS1 = 1;
	T0CONbits.T0PS0 = 0;
	
	T0CONbits.PSA = 0;// prescaler enabled
	T0CONbits.T0CS = 0;// internal clock
	T0CONbits.T08BIT = 1;// 8 bits timer
	T0CONbits.TMR0ON = 1;// turn on T0

    // Timer0 used for detecting timeouts 
    OpenTimer0(TIMER_INT_ON 
            & T0_8BIT 
            & T0_SOURCE_INT 
            & T0_PS_1_32);  // 32: HS-PLL; 8:HS  

    INTCON2bits.TMR0IP = 0; // Timer0 low priority

#if 0 // temporary turn off timer interrupt
	T0CONbits.TMR0ON = 0;// turn on T0
#endif
}

void UARTInit(void)
{
	//baud rate 9600, Clock is 10MHz: (OSCFREQ/(16*BAUDRA1)) - 1 = 64;
	Open1USART(USART_TX_INT_ON & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW, 64); 
	Open2USART(USART_TX_INT_ON & USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW, 64); 
}

void EINTInit(void)
{
	INTCON2bits.INTEDG0 = 1; // falling edge
	INTCON2bits.INTEDG1 = 1; // falling edge
	// INT0 always high priority 
    INTCON3bits.INT1IP = 1;	// make it high priority 
	INTCON3bits.INT1E = 1;
	INTCONbits.INT0IE = 1;

}

void IRQInit(void)
{
	RCONbits.IPEN = 1;// prioritize IRQ
	INTCON = 0x00;
	EINTInit();
#if 1 // temporary turn off timer interrupt
	INTCONbits.TMR0IE = 0;// disable TMR0 IRQ
#else
	INTCONbits.TMR0IE = 1;// enable TMR0 IRQ
#endif
	INTCON2bits.TMR0IP = 0;// TMR0 low priority

	PIE1bits.RCIE = 1;// enable Rx interrupt
	IPR1bits.RCIP = 0;// UART rx low priority
	PIE1bits.TXIE = 0;// disable Tx interrupt
	IPR1bits.TXIP = 0;// UART tx low priority
	//PIR1bits.TXIF = 0;
	
	PIE3bits.RC2IE = 1;//enable Rx2 interrupt
	IPR3bits.RC2IP = 0;//UART Rx2 high priority
	PIE3bits.TX2IE = 0;//disable Tx2 interrupt
	IPR3bits.TX2IP = 0;//

	UART0_TX_INT_ENABLE = 0;
	UART1_TX_INT_ENABLE = 0;

#if 1
	INTCON3bits.INT3IE = 0;
	INTCON3bits.INT2IE = 0;
	PIE2 = 0;
#endif
}


/*-----------------------------------------------------------------------------
FUNCTION NAME: SPIInit()

DESCRIPTION: 
    This function initialises SPI

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void SPIInit(void)
//here is the SPI setup
{

//	PORTCbits.RC7 = 0;       // Define CS as Output
	TRISCbits.TRISC3 = 0;       // Define SCK as Output
	PORTCbits.RC4 = 1;       // Define MISO as Input
	TRISCbits.TRISC5 = 0;       // Define MOSI as Output
//	SSPSTAT = 0xC0;         //SPI Bus mode 0,0
//	SSPCON1 = 0x21;         //Enable SSP, Fosc/64, Fosc = 8MHz
//	SSPCON1bits.SSPEN = 1;
//	SSPCON1bits.CKP = 0;
//	SSP1STATbits.CKE = 1;
//	SSP1STATbits.SMP = 1;
	SSP1STAT = 0x40;        
	SSP1CON1 = 0x21;       

	TRISDbits.TRISD6 = 0;		// Define SCK as Output
	TRISDbits.TRISD5 = 1;		// Define MISO as Input
	TRISDbits.TRISD4 = 0;		// Define MOSI as Output
	SSP2STAT = 0x40; 
	SSP2CON1 = 0x21;       

	// Synchronous Serial Port Enable bit
	SSP2CON1bits.SSPEN = 1;

	// Clock Polarity Select bit, 1 = Idle state for clock is a high level
	// 0 = Idle state for clock is a low level
	SSP2CON1bits.CKP = 0;

	// SPI Clock Select bit, 1 = Transmit occurs on transition from active to Idle clock state
	// 0 = Transmit occurs on transition from Idle to active clock state
	SSP2STATbits.CKE = 1;
	
	// Sample bit, 1 = Input data sampled at end of data output time, 
	// 0 = Input data sampled at middle of data output time
	SSP2STATbits.SMP = 0; 
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: DisableSPI()

DESCRIPTION: 
    This function disable SPI, define this function for avoid noise

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void DisableSPI(void)
{
	SSPSTAT = 0x40;        
	SSPCON1 = 0x21;       
	SSPCON1 &= ~0x20;
	SSP2STAT = 0x40;        
	SSP2CON1 = 0x21;       
	SSP2CON1 &= ~0x20;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: ReadWriteSPI1()

DESCRIPTION: 
    This function read/write data to SPI1

INPUT PARAMETERS: 
    write data

RETURN:
    read data

NOTES:

-----------------------------------------------------------------------------*/
unsigned char ReadWriteSPI1( unsigned char WriteData )
{
	unsigned char temp_data;
	unsigned int i = 0;

	SSP1BUF = WriteData;               // write data to SPI1
	while( SSPSTATbits.BF == 0 )
	{
		i++;
		if (i >= 60000)
			break;
	}// wait until 'BF' bit is set
	temp_data = SSP1BUF;               // read data from SPI1
	return temp_data;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: ReadWriteSPI2()

DESCRIPTION: 
    This function read/write data to SPI2

INPUT PARAMETERS: 
    write data

RETURN:
    read data

NOTES:

-----------------------------------------------------------------------------*/
unsigned char ReadWriteSPI2( unsigned char WriteData )
{
	unsigned char temp_data;
	unsigned int i = 0;

	SSP2BUF = WriteData;               // write data to SPI1
	while( SSP2STATbits.BF == 0 )
	{
		i++;
		if (i >= 60000)
			break;
	}// wait until 'BF' bit is set
	temp_data = SSP2BUF;               // read data from SPI1
	return temp_data;
}


/*-----------------------------------------------------------------------------
FUNCTION NAME: P18F8722Init()

DESCRIPTION: 
    This function initialises timer, I/O ports, interrupts and their priority

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void P18F8722Init(void)
{
	//disable global interrupts.
    INT_OFF();  

	IOInit();
	Timer0Init();
	UARTInit();
	SPIInit();
	IRQInit();
    InitialiseDualUart();

	//enable global interrupts.
	INT_ON();  
}

#endif //#if defined(__18F8722) || defined(_18F8722)

