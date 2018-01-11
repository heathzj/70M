#include "Global.h"
#include "define.h"
#if defined(__18F97J60) || defined(_18F97J60)
#include "p18f97j60.h"
#include "TCPIP Stack/TCPIP.h"
#endif
#include "DualUART.h"
#include "UARTISR.h"

//
// PIC18 Interrupt Service Routines
// 
// NOTE: Several PICs, including the PIC18F4620 revision A3 have a RETFIE FAST/MOVFF bug
// The interruptlow keyword is used to work around the bug when using C18
extern unsigned char KeyPressedFlag, PressedKey;

unsigned char Timer2Counter = 0;


#pragma interruptlow LowISR
void LowISR(void)
{
	unsigned char byte_tmp, i;

	if(UART0_RX_INT_FLAG)
	{
		UART0_RX_INT_ENABLE = FALSE;

		byte_tmp = RCREG;

		UART0_RX_INT_FLAG = 0; // yt added to clear interrupt flag
		UART0_RX_INT_ENABLE = TRUE;
	}
	
	if(UART1_RX_INT_FLAG)
	{
		UART1_RX_INT_ENABLE = FALSE;

		byte_tmp = RCREG2;

		UART1_RX_INT_FLAG = 0; // yt added to clear interrupt flag
		UART1_RX_INT_ENABLE = TRUE;
	}
	
	if (PIR1bits.TMR2IF)
	{
		PIR1bits.TMR2IF = 0;
		Timer2Counter++;
		TMR2 = 0;
		if (Timer2Counter >= 3)
		{
			Timer2Counter = 0;
			PIR1bits.TMR2IF = 0;
			INTCON3bits.INT1IE = 1; // enable key interrupt
			PIE1bits.TMR2IE = 0;  // disable Timer2 interrupt, stop timer2
			T2CON = 0x00;
			KeyPressedFlag = TRUE;
			if (UPKEY_STATUS == 1)
			{
				PressedKey = UPKEY;
			}
			else if (DOWNKEY_STATUS == 1)
			{
				PressedKey = DOWNKEY;
			}
			else if (LEFTKEY_STATUS == 1)
			{
				PressedKey = LEFTKEY;
			}
			else if (RIGHTKEY_STATUS == 1)
			{
				PressedKey = RIGHTKEY;
			}
			else if (ENTERKEY_STATUS == 1)
			{
				PressedKey = ENTERKEY;
			}
			else if (CANCELKEY_STATUS == 1)
			{
				PressedKey = CANCELKEY;
			}
			else
			{
				KeyPressedFlag = FALSE;
			}
		}
	}
	if (INTCON3bits.INT1IF)
	{
		PIE1bits.TMR2IE = 1;  // enable Timer2 interrupt, start timer2
		T2CON = 0xFF;
		INTCON3bits.INT1IF = 0;
		INTCON3bits.INT1IE = 0; // disable key interrupt
	}

	TickUpdate();

}
	

#pragma interrupt HighISR
void HighISR(void)
{
	unsigned char val_isr = 0;
	unsigned char byte_tmp;

#if defined(__18F97J60) || defined(_18F97J60)
	UART2ISR();         
#endif

}


#ifdef USE_SERIAL_BOOTLOADER
#pragma code lowVector=0x218
#else
#pragma code lowVector=0x18
#endif

void LowVector(void){_asm goto LowISR _endasm}

#ifdef USE_SERIAL_BOOTLOADER
#pragma code highVector=0x208
#else
#pragma code highVector=0x8
#endif
void HighVector(void){_asm goto HighISR _endasm}

