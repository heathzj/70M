#include "Global.h"
#include "define.h"

/*-----------------------------------------------------------------------------
FUNCTION NAME: SPI2Init()

DESCRIPTION: 
    This function initialises SPI

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void SPIInit(void)
{

#if !(defined(__18F97J60) || defined(_18F97J60))
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
#endif

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

