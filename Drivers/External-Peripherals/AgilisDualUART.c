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
#include "HardwareProfile.h"
#include "delays.h"
#include "define.h"
#include "Global.h"
#include "AgilisDualUART.h"




/*----------------------
    GLOBAL VARIABLES
----------------------*/



#define INTERRUPT 0x05

extern void InitialiseDualUart(void);


/*----------------------
    GLOBAL FUNCTIONS
----------------------*/
/*-----------------------------------------------------------------------------
FUNCTION NAME: ResetDualUart()

DESCRIPTION: 
	This function resets the DUAL UART 
	
INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void ResetDualUart(void)
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
void WriteDualUartConf(BYTE reg_addr, BYTE val, BYTE which_sspa)
{
	// write A/B both side
    UART_A0 = reg_addr & 0x01;
    UART_A1 = ((reg_addr & 0x2) == 0) ? 0 : 1;
    UART_A2 = ((reg_addr & 0x4) == 0) ? 0 : 1;

    UART_DATA_DIRECTION = OUTPUT;

    DUAL_UARTA_ENABLE_IO = 0;
    DUAL_UARTB_ENABLE_IO = 0;	

    DUAL_UARTA2_ENABLE_IO = 0;
    DUAL_UARTB2_ENABLE_IO = 0;	

	if((which_sspa == 1)||(which_sspa == 2))
	{
	    DUAL_UARTA2_ENABLE = CS_DISABLE;
	    DUAL_UARTB2_ENABLE = CS_DISABLE;	
		
	    DUAL_UARTA_ENABLE = CS_ENABLE;
	    DUAL_UARTB_ENABLE = CS_DISABLE;	
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


	if((which_sspa == 3)||(which_sspa == 4))
	{
	
	   DUAL_UARTA_ENABLE = CS_DISABLE;
	   DUAL_UARTB_ENABLE = CS_DISABLE;    
	   
	   DUAL_UARTA2_ENABLE = CS_ENABLE;
	   DUAL_UARTB2_ENABLE = CS_DISABLE; 
	   LATJ |= 0x40; // UART_IOWR = 1;
	   LATJ |= 0x80; // UART_IORD = 1;
	   
	   UART_DATA = val;
	   
	   LATJ &= ~0x40; // UART_IOWR = 0;
	   
	   LATJ |= 0x40; // UART_IOWR = 1;
	   DUAL_UARTA2_ENABLE = CS_DISABLE;
	   DUAL_UARTB2_ENABLE = CS_ENABLE;
	   LATJ |= 0x40; // UART_IOWR = 1;
	   LATJ |= 0x80; // UART_IORD = 1;
	   
	   UART_DATA = val;
	   
	   LATJ &= ~0x40; // UART_IOWR = 0;
	   
	   LATJ |= 0x40; // UART_IOWR = 1;
	   DUAL_UARTB2_ENABLE = CS_DISABLE;
	   DUAL_UARTA2_ENABLE = CS_DISABLE;
	
	}
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
#if defined(__18F97J60) || defined(_18F97J60)
    
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
        DUAL_UARTA2_ENABLE = CS_DISABLE;
        DUAL_UARTB2_ENABLE = CS_DISABLE;		
    }
    else if(which_sspa == DUAL_UART_B)
    {
        DUAL_UARTA_ENABLE = CS_DISABLE;
        DUAL_UARTB_ENABLE = CS_ENABLE;
        DUAL_UARTA2_ENABLE = CS_DISABLE;
        DUAL_UARTB2_ENABLE = CS_DISABLE;			
    }
    else if(which_sspa == DUAL_UART_A2)
    {
        DUAL_UARTA_ENABLE = CS_DISABLE;
        DUAL_UARTB_ENABLE = CS_DISABLE;
        DUAL_UARTA2_ENABLE = CS_ENABLE;
        DUAL_UARTB2_ENABLE = CS_DISABLE;
    }
    else if(which_sspa == DUAL_UART_B2)
    {
        DUAL_UARTA_ENABLE = CS_DISABLE;
        DUAL_UARTB_ENABLE = CS_DISABLE;    
        DUAL_UARTA2_ENABLE = CS_DISABLE;
        DUAL_UARTB2_ENABLE = CS_ENABLE;
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
#else
	UART_IOWR = 1;
	UART_IORD = 1;
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

	UART_IOWR = 1;

	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	UART_IORD = 0;
	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	
	val = UART_DATA;
	
	UART_IORD = 1;
	UART_DATA_DIRECTION = OUTPUT;
    DUAL_UARTB_ENABLE = CS_DISABLE;
    DUAL_UARTA_ENABLE = CS_DISABLE;
#endif

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
	DUAL_UARTA2_ENABLE_IO = 0;
	DUAL_UARTB2_ENABLE_IO = 0;
	
    UART_A0 = 0;
    UART_A1 = 0;
    UART_A2 = 0;

    UART_DATA_DIRECTION = INPUT;
    if(which_sspa == DUAL_UART_A)
    {
        DUAL_UARTA_ENABLE = CS_ENABLE;
        DUAL_UARTB_ENABLE = CS_DISABLE;
        DUAL_UARTA2_ENABLE = CS_DISABLE;
        DUAL_UARTB2_ENABLE = CS_DISABLE;		
    }
    else if(which_sspa == DUAL_UART_B)
    {
        DUAL_UARTA_ENABLE = CS_DISABLE;
        DUAL_UARTB_ENABLE = CS_ENABLE;
        DUAL_UARTA2_ENABLE = CS_DISABLE;
        DUAL_UARTB2_ENABLE = CS_DISABLE;			
    }
    else if(which_sspa == DUAL_UART_A2)
    {
        DUAL_UARTA_ENABLE = CS_DISABLE;
        DUAL_UARTB_ENABLE = CS_DISABLE;
        DUAL_UARTA2_ENABLE = CS_ENABLE;
        DUAL_UARTB2_ENABLE = CS_DISABLE;
    }
    else if(which_sspa == DUAL_UART_B2)
    {
        DUAL_UARTA_ENABLE = CS_DISABLE;
        DUAL_UARTB_ENABLE = CS_DISABLE;    
        DUAL_UARTA2_ENABLE = CS_DISABLE;
        DUAL_UARTB2_ENABLE = CS_ENABLE;
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
	DUAL_UARTA2_ENABLE = CS_DISABLE;
	DUAL_UARTB2_ENABLE = CS_DISABLE;
	
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

#if defined(__18F97J60) || defined(_18F97J60)
	if(current_sspa == DUAL_UART_A)
	{
		DUAL_UARTA_ENABLE = CS_ENABLE;
		DUAL_UARTB_ENABLE = CS_DISABLE;
		DUAL_UARTA2_ENABLE = CS_DISABLE;
		DUAL_UARTB2_ENABLE = CS_DISABLE;		
	}
	else if(current_sspa == DUAL_UART_B)
	{
		DUAL_UARTA_ENABLE = CS_DISABLE;
		DUAL_UARTB_ENABLE = CS_ENABLE;
		DUAL_UARTA2_ENABLE = CS_DISABLE;
		DUAL_UARTB2_ENABLE = CS_DISABLE;		
	}
	else if(current_sspa == DUAL_UART_A2)
	{
		DUAL_UARTA_ENABLE = CS_DISABLE;
		DUAL_UARTB_ENABLE = CS_DISABLE;	
		DUAL_UARTA2_ENABLE = CS_ENABLE;
		DUAL_UARTB2_ENABLE = CS_DISABLE;

	}
	else if(current_sspa == DUAL_UART_B2)
	{
		DUAL_UARTA_ENABLE = CS_DISABLE;
		DUAL_UARTB_ENABLE = CS_DISABLE;	
		DUAL_UARTA2_ENABLE = CS_DISABLE;
		DUAL_UARTB2_ENABLE = CS_ENABLE;
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

	Delay10TCY(); // yt	Delay10TCY(); // yt	Delay10TCY(); // yt	Delay10TCY(); // yt	Delay10TCY(); // yt	Delay10TCY(); // yt	Delay10TCY(); // yt	Delay10TCY(); // yt	Delay10TCY(); // yt
	DUAL_UARTA_ENABLE = CS_DISABLE;
	DUAL_UARTB_ENABLE = CS_DISABLE;
	DUAL_UARTA2_ENABLE = CS_DISABLE;
	DUAL_UARTB2_ENABLE = CS_DISABLE;	
#else
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
	UART_IORD = 1;
	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	UART_IOWR = 0;
	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	UART_IOWR = 1;
	// add delay for enough time for update register
    Nop(); Nop(); Nop();
	
	DUAL_UARTA_ENABLE = CS_DISABLE;
	DUAL_UARTB_ENABLE = CS_DISABLE;
#endif

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
#if defined(__18F97J60) || defined(_18F97J60)
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
#else
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
    UART_IORD = 1;
    UART_IOWR = 0;
	
    UART_IOWR = 1;

    DUAL_UARTA_ENABLE = CS_DISABLE;
    DUAL_UARTB_ENABLE = CS_DISABLE;
#endif
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
    
    ResetDualUart();    
	WriteDualUartConf(DUAL_UART_LCR, 0x03,1);
	WriteDualUartConf(DUAL_UART_LCR, 0x03,3);

	// Follow TL16C752B datasheet initialize sequence
	
	// 1. Set baud rate to VALUE1, VALUE2
	// Read LCR (03), save in temp
    temp1 = ReadDualUartConf(DUAL_UART_LCR, DUAL_UART_A);

	Delay10TCYx( 5 );
	// Set LCR (03) to 80
	WriteDualUartConf(DUAL_UART_LCR, 0x83,1);
	WriteDualUartConf(DUAL_UART_LCR, 0x83,3);
	
	Delay10TCYx( 5 );
	// Set DLL (00) to VALUE1
	WriteDualUartConf(DUAL_UART_DLL, 0x0C,1);
	WriteDualUartConf(DUAL_UART_DLL, 0x0C,3);

	Delay10TCYx( 5 );
	// Set DLM (01) to VALUE2
    WriteDualUartConf(DUAL_UART_DLM, 0,1);
    WriteDualUartConf(DUAL_UART_DLM, 0,3);

	Delay10TCYx( 5 );
	// Set LCR (03) to temp
	WriteDualUartConf(DUAL_UART_LCR, temp1,1);
	WriteDualUartConf(DUAL_UART_LCR, temp1,3);

	// 2. Set xmt and rcv FIFO thresholds to VALUE
	// Read LCR (03), save in temp1
    temp1 = ReadDualUartConf(DUAL_UART_LCR, DUAL_UART_A);

	Delay10TCYx( 5 );
	// Set LCR (03) to BF
	WriteDualUartConf(DUAL_UART_LCR, 0xBF,1);
	WriteDualUartConf(DUAL_UART_LCR, 0xBF,3);

	// Read EFR (02), save in temp2
	Delay10TCYx( 5 );
	temp2 = ReadDualUartConf(DUAL_UART_EFR, DUAL_UART_A);

	// Set EFR (02) to 10 + temp2
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_EFR, temp2 + 0x10,1);
	WriteDualUartConf(DUAL_UART_EFR, temp2 + 0x10,3);

	// Set LCR (03) to 00
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_LCR, 0,1);
	WriteDualUartConf(DUAL_UART_LCR, 0,3);
	
	// Read MCR (04), save in temp3
	Delay10TCYx( 5 );
	temp3 = ReadDualUartConf(DUAL_UART_MCR, DUAL_UART_A);

	// Set MCR (04) to 40 + temp3
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_MCR, temp3 + 0x40,1);
	WriteDualUartConf(DUAL_UART_MCR, temp3 + 0x40,3);

	// Set TLR (07) to VALUE
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_TLR, 0x44,1);
	WriteDualUartConf(DUAL_UART_TLR, 0x44,3);

	// Set MCR (04) to temp3
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_MCR, temp3,1);
	WriteDualUartConf(DUAL_UART_MCR, temp3,3);

	// Set LCR (03) to BF
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_LCR, 0xBF,1);
	WriteDualUartConf(DUAL_UART_LCR, 0xBF,3);

	// Set EFR (02) to temp2
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_EFR, temp2,1);
	WriteDualUartConf(DUAL_UART_EFR, temp2,3);

	Delay10TCYx( 5 );
	// Set LCR (03) to temp1
	WriteDualUartConf(DUAL_UART_LCR, temp1,1);
	WriteDualUartConf(DUAL_UART_LCR, temp1,3);

	// Enable transmit/receive FIFO
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_FCR, 0x01,1);
	WriteDualUartConf(DUAL_UART_FCR, 0x01,3);

	//INT A and B pins are enabled 
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_MCR, 0x08,1);
	WriteDualUartConf(DUAL_UART_MCR, 0x08,3);

	// Enable the RHR interrupt 
	Delay10TCYx( 5 );
	WriteDualUartConf(DUAL_UART_IER, INTERRUPT,1);

	WriteDualUartConf(DUAL_UART_IER, INTERRUPT,3);
}



void SetDualUartInterrupt(BYTE u8Reg, BYTE u8Data, BYTE which_sspa)
{
	WriteDualUartConf(u8Reg, u8Data, which_sspa);
	Delay10TCYx( 5 );
	//DelayMS(1);

}

