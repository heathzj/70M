#ifndef _DEFINE_H
#define _DEFINE_H

#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "HardwareProfile.h"
#include "p18f97j60.h"

#define nLO_FREQ 5250u

#define STATUS_OFF 0
#define STATUS_ON 1



#define LED_LO				PORTFbits.RF5
#define LED_Tx_Mute			PORTHbits.RH4
#define LED_Rx_Mute			PORTHbits.RH5
#define LED_Power

#define LED_LO_TRIS			TRISFbits.TRISF5
#define LED_Tx_Mute_TRIS	TRISHbits.TRISH4
#define LED_Rx_Mute_TRIS	TRISHbits.TRISH5
#define LED_Power_TRIS





#define MINRFFREQ		(950000ul) // 7680 MHz
#define MAXRFFREQ		(1250000ul) // 7305 MHz
#define MAXATTEN		(300u)	// 30dB
#define MINATTEN		(0u)
#define MAXPOWER		(660u)	// 5dB*10 + 500
#define MINPOWER		(200u)	// -30dB * 10 + 500


#define MODULE0			0
#define MODULE1			1
#define MODULE2			2

#define MODULE0_ADDRESS		0x36//0x28
#define MODULE1_ADDRESS		0x28//0x36
#define MODULE2_ADDRESS		0x32  /* To be confirmed */

#define I2C_UPCVT_ADDR		MODULE1_ADDRESS
#define I2C_DownCVT_ADDR	MODULE0_ADDRESS
#define I2C_REF_ADDR		MODULE2_ADDRESS
#define I2C_LO_ADDR			0x66
#define CONVERTER_ADDRESS	0x46
#define I2CBUFFLENGTH	30



#define MAX_TRAPS			2

	// Level 0 Menu 0/1/2/3: UC1/DC2/DCVOL/INFO
	// UC1	   Menu 4/5/6/7/8/9: Output Freq(Editable)/Output Power(E)/LO Status/Atten(E)/ALC(E)/Mute(E)
	// DC2	   Menu 10/11/12/13/14/15: Input Freq(Editable)/Output Power(E)/LO Status/Atten(E)/ALC(E)/Mute(E)
	// DCVOL   Menu 16/17: 18V DC(E) / 24V DC(E)
	// INFO Menu 18/19/20: IP(Editable)/MN/SN

#define MENU0		0 // UC1 MENU
#define MENU1		1 // DC2 MENU
#define MENU2		2 // VOL CTRL
#define MENU3		3 // DEVICE INFO MENU

#define MENU4		4 // UC1 RF FREQ MENU
#define MENU5		5 // UC1 OUTPUT POWER MENU
#define MENU6		6 // UC1 Write POWER MENU
#define MENU7		7 // UC1 LO STATUS
#define MENU8		8 // UC1 ATTEN MENU
#define MENU9		9 // UC1 ALC MENU
#define MENU10		10 // UC1 MUTE MENU

#define MENU11		11 // DC2 RF FREQ MENU MENU
#define MENU12		12 // DC2 INPUT POWER MENU
#define MENU13		13 // DC2 Write POWER MENU
#define MENU14		14 // DC2 IF FREQ MENU
#define MENU15		15 // DC2 ATTEN MENU
#define MENU16		16 // DC2 ALC MENU
#define MENU17		17 // DC2 MUTE MENU

#define MENU18		18 //  18V DC
#define MENU19		19 //  24V DC
#define MENU20		20 //  LNB REF
#define MENU21		21 //  BUC REF


#define MENU22		22 //  EXT REF
#define MENU23		23 //  BUC I
#define MENU24		24 // LNB I
#define MENU25		25 //  BUC Over I 
#define MENU26		26 //  LNB Over I


#define MENU27		27 //  IP
#define MENU28		28 //  MN
#define MENU29		29 //  SN



#define nFREQ_MENU_A		MENU4	 	// UC1 RF FREQ MENU
#define nPOWER_MENU_A 		MENU5	 	// UC1 OUTPUT POWER MENU
#define nSTPWR_MENU_A		MENU6		 // DC2 write POWER MENU
#define nLOSTATUS_MENU_A 	MENU7		 // UC1 LO STATUS
#define nATTN_MENU_A		MENU8		 // UC1 ATTEN MENU
#define nALC_MENU_A			MENU9		 // UC1 ALC MENU
#define nMUTE_MENU_A		MENU10		 // UC1 MUTE MENU

#define nFREQ_MENU_B 		MENU11		// DC2 RF FREQ MENU MENU
#define nPOWER_MENU_B 		MENU12		 // DC2 INPUT POWER MENU
#define nSTPWR_MENU_B 		MENU13		 // DC2 write POWER MENU
#define nLOSTATUS_MENU_B 	MENU14		 // DC2 IF FREQ MENU
#define nATTN_MENU_B		MENU15		 // DC2 ATTEN MENU
#define nALC_MENU_B			MENU16		 // DC2 ALC MENU
#define nMUTE_MENU_B		MENU17		 // DC2 MUTE MENU

#define nDC18V_MENU			MENU18		 //  18V DC
#define nDC24V_MENU			MENU19		 //  24V DC
#define nLNBREF_MENU		MENU20		 //  18V DC
#define nBUCREF_MENU		MENU21		 //  24V DC

#define nEXTREF_MENU		MENU22		 //  18V DC
#define nBUCI_MENU			MENU23		 //  24V DC
#define nLNBI_MENU			MENU24		 //  18V DC
#define nBUCOVERI_MENU		MENU25		 //  24V DC
#define nLNBOVERI_MENU		MENU26		 //  24V DC





#define UPKEY			1
#define DOWNKEY			2
#define LEFTKEY			3
#define RIGHTKEY		4
#define ENTERKEY		5
#define CANCELKEY		6

#define UPKEY_STATUS     	PORTCbits.RC1
#define UPKEY_TRIS       	TRISCbits.TRISC1
#define DOWNKEY_STATUS   	PORTFbits.RF6
#define DOWNKEY_TRIS       	TRISFbits.TRISF6
#define LEFTKEY_STATUS      PORTFbits.RF3
#define LEFTKEY_TRIS       	TRISFbits.TRISF3
#define RIGHTKEY_STATUS     PORTFbits.RF4
#define RIGHTKEY_TRIS       TRISFbits.TRISF4
#define ENTERKEY_STATUS     PORTHbits.RH7
#define ENTERKEY_TRIS       TRISHbits.TRISH7
#define CANCELKEY_STATUS    PORTHbits.RH6
#define CANCELKEY_TRIS      TRISHbits.TRISH6

#define CONVERTERA_STATUS            PORTFbits.RF5
#define CONVERTERA_STATUS_TRIS       TRISFbits.TRISF5
#define CONVERTERB_STATUS            PORTHbits.RH4
#define CONVERTERB_STATUS_TRIS       TRISHbits.TRISH4

#define SCL            PORTDbits.RD6   //-- The SCL output pin
#define SCL_TRIS       TRISDbits.TRISD6  //-- The SCL Direction Register Bit
#define SDA            PORTDbits.RD5   //-- The SDA output pin
#define SDA_TRIS       TRISDbits.TRISD5  //-- The SDA Direction Register Bit

#define I2CLOW  0         //-- Puts pin into output/low mode
#define I2CHIGH 1         //-- Puts pin into Input/high mode

#define I2CSTARTDELAY 50
#define I2CSTOPDELAY  50
#define I2CDATASETTLE 20
#define I2CCLOCKHIGH  100
#define I2CHALFCLOCK  50
#define I2CCLOCKLOW   100
#define I2CACKWAITMIN 50

#define LINE0		0x80
#define LINE1		0xC0

#define OK			0
#define MAJORALARM	1
#define MINORALARM	2

#define NULLTYPE	0
#define STRINGTYPE	1
#define NUMBERTYPE	2

#define OLED_RS			LATJbits.LATJ0
#define OLED_RS_TRIS		TRISJbits.TRISJ0
#define OLED_RW			LATJbits.LATJ4
#define OLED_RW_TRIS		TRISJbits.TRISJ4
#define OLED_EN			LATJbits.LATJ5
#define OLED_EN_TRIS		TRISJbits.TRISJ5
#define OLED_BUS_W		LATE
#define OLED_BUS_R		PORTE
#define OLED_BUS_TRIS	TRISE
#define OLED_DB0_W		LATEbits.LATE0
#define OLED_DB0_R		PORTEbits.RE0
#define OLED_DB0_TRIS	TRISEbits.TRISE0
#define OLED_DB1_W		LATEbits.LATE1
#define OLED_DB1_R		PORTEbits.RE1
#define OLED_DB1_TRIS	TRISEbits.TRISE1
#define OLED_DB2_W		LATEbits.LATE2
#define OLED_DB2_R		PORTEbits.RE2
#define OLED_DB2_TRIS	TRISEbits.TRISE2
#define OLED_DB3_W		LATEbits.LATE3
#define OLED_DB3_R		PORTEbits.RE3
#define OLED_DB3_TRIS	TRISEbits.TRISE3
#define OLED_DB4_W		LATEbits.LATE4
#define OLED_DB4_R		PORTEbits.RE4
#define OLED_DB4_TRIS	TRISEbits.TRISE4
#define OLED_DB5_W		LATEbits.LATE5
#define OLED_DB5_R		PORTEbits.RE5
#define OLED_DB5_TRIS	TRISEbits.TRISE5
#define OLED_DB6_W		LATEbits.LATE6
#define OLED_DB6_R		PORTEbits.RE6
#define OLED_DB6_TRIS	TRISEbits.TRISE6
#define OLED_DB7_W		LATEbits.LATE7
#define OLED_DB7_R		PORTEbits.RE7
#define OLED_DB7_TRIS	TRISEbits.TRISE7

#define INTON()    INTCON |= 0xC0  /* enable high and low interrupts, enable TMR0 interrupts */
#define INTOFF()   INTCON &= ~0xC0 

#define RCU
#define RCU_OUTDOOR
#define RCU2_1
#define RCU_FIRMWARE_VERSION  "105"
#define BUC_MAX_SIZE    3 // 2 BUC

#define SUPPORT_UART1
enum {
	BUC_SWLO_0 = 0, // QF + "00"
	BUC_SWLO_1,		// QF + "01"
	BUC_SWLO_NUM
};

enum {
	FMBUC_A=0,
	FMBUC_B
};

//#define SerialModePin		PORTHbits.RH3
#define RS232_485		          PORTHbits.RH3
#define RS422				2
#define RS485				1
#define RS232				0

#define CBAND               0
#define KUBAND              1
#define XBAND               2
#define	UNKNOWNBUC			10





#define FREQ_TCY      8            //Frequency of instruction cycle: 32Mhz/4
#define  MAX_POWER_POINT        30

#define MaxDataLength	55

#define MAX_NUM 25
#define MAX_NUM2 17
#define MAX_NUM3 10

#define MaxPollingCount		2
#define MaxPollingCount1	3

#define PollingPartNumber		0
#define PollingSerialNumber		1
#define PollingVersionNumber	2

#define Enable					1
#define Disable					0
#define MajorAlarm				1
#define MinorAlarm				0
#define AlarmOK					1
#define Alarm					0
#define On					1
#define Off					0

#define NotApplicable		0xFF

//Gobal Variables
#define MAX_COUNTTIME   40
#define MAX_DATA_LEN   50

#define ENABLE 1
#define DISBALE 0

#define ASSERT 1

#define ON     1
#define OFF    0

#define IN     1
#define OUT    0

#define  RESERVE_BYTE           0xFF

// Used to Chip Selelct enable or disable 
#define CS_ENABLE       0
#define CS_DISABLE      1

// Used to set some of pins states 
#define HIGH         1
#define LOW          0



#define MEM_ADDR    0x1FC01
#define MEM_ADDR2   0x1FD00
#define MEM_ADDR3   0x1FE00
#define MEM_STEP    0x00040


//Special Characters
#define START_PROMT  'G'
#define START_PROMT2 'Z'
#define START_PROMT3 0x02
#define END_PROMT    0x0D
#define END_PROMT2   0x0A
#define END_PROMT3   0x03
#define ACK3   		 0x06
#define NACK3   	 0x15


//SPI
#define SPI_MASTER_MODE 0x20
#define SPI_SLAVE_MODE  0x25

#define INTERUPT       1
#define POLL           0

#define SPI1_SDO        0x20 //RC5
#define SPI1_SDI        0x10 //RC4
#define SPI1_CLK        0x08 //RC3

#define SPI2_SDO        0x10 //RD4
#define SPI2_SDI        0x20 //RD5
#define SPI2_CLK        0x40 //RD6

//COM Interface  Related I/O
#if defined(__18F97J60) || defined(_18F97J60)
// PIC18F97J60

#define DXEN0					PORTGbits.RG6  		//RG6
#define MODE0					PORTGbits.RG5  		//RG5
#define RXEN0					PORTBbits.RB0  		//RB0

#define RXEN1					PORTGbits.RG0  		//RG0
#define MODE1					PORTBbits.RB4  		//RB4
#define DXEN1					PORTBbits.RB5  		//RB5

// #define  MODE2  SetCPLDGPIO(12, 0); 
// #define	RXEN2  SetCPLDGPIO(10, 1);
// #define	DXEN2  SetCPLDGPIO(13, 0);

#define DXEN3					PORTCbits.RC2  		//RC2
#define RXEN3					PORTGbits.RG7  		//RG7
#define MODE3					PORTGbits.RG3  		//RG3

#define WDI_FLAG				PORTAbits.RA3  		//RA3, hardware watch dog

#else

// PIC18F8722

#define UART0_INT				PIR1bits.RCIF
#define UART1_INT               PIR3bits.RC2IF
#define UART2_INT				INTCONbits.INT0IF
#define UART3_INT               INTCON3bits.INT1IF

#define RXEN0					LATAbits.LATA4		//PORTAbits.RA4  		//RA4
#define DXEN0					LATCbits.LATC0 		//PORTCbits.RC0  		//RC0
#define MODE0					LATCbits.LATC1		//PORTCbits.RC1  		//RC1

#define RXEN1					LATGbits.LATG0		//PORTGbits.RG0  		//RG0
#define MODE1					LATGbits.LATG3		//PORTGbits.RG3  		//RG3
#define DXEN1					LATGbits.LATG4		//PORTGbits.RG4  		//RG4

#define MODE2					LATAbits.LATA0		// PORTAbits.RA0  		//RA0
#define RXEN2					LATAbits.LATA1		// PORTAbits.RA1  		//RA1
#define DXEN2					LATAbits.LATA5		// PORTAbits.RA5  		//RA5

#define DXEN3					LATBbits.LATB2		//PORTBbits.RB2  		//RB2
#define MODE3					LATBbits.LATB3		//PORTBbits.RB3  		//RB3
#define RXEN3					LATBbits.LATB4		//PORTBbits.RB4  		//RB4

#define WDI_FLAG				LATBbits.LATB5		//PORTBbits.RB5  		//RB5, hardware watch dog

#endif

#define UART0_RX_INT_ENABLE		PIE1bits.RCIE
#define UART0_RX_INT_FLAG		PIR1bits.RCIF
#define	UART0_RX_INT_PRIORITY   IPR1bits.RC1IP

#define UART1_RX_INT_ENABLE		PIE3bits.RC2IE
#define UART1_RX_INT_FLAG       PIR3bits.RC2IF
#define	UART1_RX_INT_PRIORITY   IPR3bits.RC2IP

#define UART2_INT_ENABLE		INTCONbits.INT0IE
#define UART2_INT_EDGE			INTCON2bits.INTEDG0
#define UART2_INT_FLAG			INTCONbits.INT0IF

#define UART3_INT_ENABLE		INTCON3bits.INT1IE
#define UART3_INT_FLAG          INTCON3bits.INT1IF
#define UART3_INT_PRIORITY		INTCON3bits.INT1IP
#define UART3_INT_EDGE			INTCON2bits.INTEDG1

#define UART4_INT_ENABLE        INTCON3bits.INT3IE
#define UART4_INT_FLAG          INTCON3bits.INT3IF
#define UART4_INT_PRIORITY      INTCON2bits.INT3IP
#define UART4_INT_EDGE			INTCON2bits.INTEDG3

#define UART5_INT_ENABLE		INTCON3bits.INT2IE
#define UART5_INT_FLAG			INTCON3bits.INT2IF
#define UART5_INT_PRIORITY      INTCON3bits.INT2IP //todo!!!
#define UART5_INT_EDGE			INTCON2bits.INTEDG2 //todo!!!

#define INT_RISING_EDGE			1
#define INT_FALLING_EDGE		0
#define INT_PRIORITY_HIGH 		1
#define INT_PRIORITY_LOW 		0


#define DIGI_INT_ENABLE		    INTCON3bits.INT2IE
#define CAN_INT_ENABLE			INTCON3bits.INT3IE
#define UART0_TX_INT_ENABLE		PIE1bits.TXIE
#define UART1_TX_INT_ENABLE		PIE3bits.TX2IE


// Dual UART
#define DUAL_UART_A        1
#define DUAL_UART_B        2

#define DUAL_UART_A2        3
#define DUAL_UART_B2        4

// Used set port data direction 
#define INPUT                   0xff
#define OUTPUT                  0x00

#define UART_A2					PORTJbits.RJ0  		//RJ0, DUAL UART's address bits 
#define UART_A1					PORTJbits.RJ1  		//RJ1, DUAL UART's address bits 
#define UART_A0					PORTJbits.RJ2  		//RJ2, DUAL UART's address bits 
#define UART_RST				PORTJbits.RJ3  		//RJ3, DUAL UART's reset line 
#define DUAL_UARTB_ENABLE		PORTJbits.RJ4  		//RJ4
#define DUAL_UARTA_ENABLE		PORTJbits.RJ5  		//RJ5
#define DUAL_UARTB_ENABLE_IO		TRISJbits.TRISJ4  		//RJ4
#define DUAL_UARTA_ENABLE_IO		TRISJbits.TRISJ5  		//RJ5

#define DUAL_UARTB2_ENABLE		PORTGbits.RG4  		//RJ4
#define DUAL_UARTA2_ENABLE		PORTFbits.RF0  		//RJ5
#define DUAL_UARTB2_ENABLE_IO		TRISGbits.TRISG4  		//RJ4
#define DUAL_UARTA2_ENABLE_IO		TRISFbits.TRISF0  		//RJ5


#define UART_IOWR				PORTJbits.RJ6  		//RJ6, DUAL UART's IOWR and IORD
#define UART_IORD				PORTJbits.RJ7  		//RJ7, DUAL UART's IOWR and IORD

// DUAL UART's data register and data direction register 
#define UART_DATA                                       PORTE
#define UART_DATA_DIRECTION                             TRISE

// Used to Chip Selelct enable or disable 
#define CS_ENABLE       0
#define CS_DISABLE      1


// All internal registers of DUAL UART 
#define DUAL_UART_RHR                                   0
#define DUAL_UART_THR                                   0
#define DUAL_UART_DLL                                   0
#define DUAL_UART_DLM                                   1
#define DUAL_UART_IER                                   1 // interrupt enable register
#define DUAL_UART_ISR                                   2 // interrupt status register
#define DUAL_UART_FCR                                   2 // FIFO control register
#define DUAL_UART_EFR                                   2 // Enhanced Feature Register
#define DUAL_UART_LCR                                   3 // line control register
#define DUAL_UART_MCR                                   4 // modem control register
#define DUAL_UART_LSR                                   5 // line status register
#define DUAL_UART_TLR                                   7 // Trigger level register
#define DUAL_UART_FRR                                   7 // FIFO ready register

// LSR register bits 
#define THR_RCV_DATA_READY                              0x40
#define THR_EMPTY_BIT                                   0x20
#define LSR_RX_RDY                                      0x01

// Internal registers of DUAL UART used for interrupt handling 
#define ISR_LSR_INTRPT                                  6
#define ISR_RX_DATA_RDY_INTRPT                          4
#define ISR_TX_READY_INTRPT                             2

#define TxA_FUNCTIONAL                                  1
#define TxA_FAILED                                      0
#define RxA_FUNCTIONAL                                  1
#define RxA_FAILED                                      0

#define TxB_FUNCTIONAL                                  1
#define TxB_FAILED                                      0
#define RxB_FUNCTIONAL                                  1
#define RxB_FAILED                                      0


#define TX1            PORTCbits.RC6
#define RX1            PORTCbits.RC7
#define TX1_OUT        TRISCbits.TRISC6
#define RX1_IN         TRISCbits.TRISC7











// CPLD I/OPin, 0~5 is FormC pin, 6~13 is J26-1/3/5/7/9/11/13/15
// 14~20 is J27-1/3/5/7/9/11/13, 21 is J27-15 more current pin
#define  PORT_LED_GREEN         15
#define  PORT_LED_RED           14
#define  TX_STATUS1           	16
#define  PORT_LED_GREEN1        17
#define  PORT_LED_RED1          18
#define  PORT_SSPA_ON_OFF1      22
#define  PORT_SSPA_ON_OFF2      23


//extra I/OPins for LNB RCU
#define	TONEA_EN	7
#define	TONEB_EN	9

#define	LNB_ALRMA	6
#define	LNB_ALRMB	8

#define I2C_ADDRA	12
#define I2C_ADDRB	10

#define RX_REF_SW	19


//Internal ADC Channels
#define AN0       0x0
#define AN1       0x1
#define AN2       0x2
#define AN3       0x3
#define AN4       0x4
#define AN5       0x5
#define AN6       0x6
#define AN7       0x7
#define AN8       0x8
#define AN9       0x9
#define AN10      0x10
#define AN11      0x11
#define AN12      0x12
#define AN13      0x13
#define AN14      0x14
#define AN15      0x15

/*
// ADC pin
#define CURRENT1 				0 // AIN0
#define SSPA_TEMP1 				1 // AIN1
#define DC12V_MONITOR1	 		2 // AIN2
#define CURRENT2				3 // AIN3
#define SSPA_TEMP2 				4 // AIN4
#define DC12V_MONITOR2 			5 // AIN5
#define RF_OUTPUT_PWR 			6 // AIN6
#define AGC 					7 // AIN7
#define RF_IN_PWR 				0 // AIN8
#define RF_RFL_PWR 				0 // AIN8
#define BUC_STATUS 				1 // AIN9
*/



// Used to Chip Selelct enable or disable 
#define CS_ENABLE       0
#define CS_DISABLE      1

#define CS_CPLD					PORTDbits.RD0  		//RD0
#define CS_ADC1					PORTDbits.RD2  		//RD2
#define CS_ADC0					PORTDbits.RD3  		//RD3

#endif /* _DEFINE_H */
