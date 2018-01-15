#ifndef OLED_C1_H
#define OLED_C1_H

#include "define.h"
#include "TCPIP Stack/TCPIP.h"

#define I2C_nLOLOCK 0x01u
#define I2C_nALC	0x02u
#define I2C_nMUTE	0x04u
#define nLCDLEN 40

#define nBYTE_COMPARE 0


typedef struct {
const char* pcTitle;
char cTitleIndex;
char* pcContent;
}tstLCDMenu;

extern char FirmwareVersion[4]; 

extern char LOStatusString1[9];
extern char LOStatusString2[9]; 

extern char RFFreqString1[13];
extern char RFFreqString2[13]; 
extern char AttenString1[8];
extern char AttenString2[8];

extern char IPString[16];
extern char MNString[18];
extern char SNString[9];

extern char s18VDC[4];
extern char s24VDC[4];

extern char sLNBREF[4];
extern char sBUCREF[4];


extern char sUCPower[10];
extern char sDCPower[10];
extern char sUPC_StPwr[10];
extern char sDNC_StPwr[10];


extern char sALCa[4];
extern char sALCb[4];
extern char sMutea[9];
extern char sMuteb[9];

extern unsigned char EditMode;
extern unsigned char EditPosition;
extern unsigned char FirstPressKey;
extern char LCDPrintBuffer[2][40];
extern char LCDBlinkBuffer[2][40];


extern const rom char acLCDTitle[30][nLCDLEN];
extern const rom char acLCDBlinkTitle[23][nLCDLEN];

typedef struct{
	void (*pvfPrintMenu)(void);
	void (*pvfSetValue)(void);
	void (*pvfMoveCursorLeft)(void);
	void (*pvfMoveCursorRight)(void);

	BYTE u8RightMenu;
	BYTE u8LeftMenu;
	BYTE u8UpMenu;
	BYTE u8DownMenu; 
    
    BYTE u8BlinkPos; /* Start position for blinking text */
    BYTE u8BlinkLen; /* Length for blinking text */
}tstMenuDisplay;


typedef union
{
    unsigned long u32Freq;
    unsigned char u8Freq[4];
}tunFreq;

typedef union
{
    unsigned short int u16Atten;
    unsigned char u8Atten[2];
}tunAtten;


typedef struct
{
	unsigned char u8Updateflag;   //BYTE 0
	unsigned char u8CtrlStatus;   //BYTE 1 0x1(bit0) = Lock status, 0x2(bit1) = ALC, 0x4(bit2) = Mute
	tunFreq       unRfFreq;     //BYTE 2-5 consider union here
    tunAtten      unAtten;      //BYTE 6-7 consider union here
    unsigned char u8WtPower;    //BYTE 8 Write outputpower to modules 
    unsigned char u8RdPower;    //BYTE 9 Read outputpower from modules

}tstI2CMessage;

/********************************************************************************************************************
byte 0: 
			bit0: write flag 1 by master, cleared by software
			bit1: AGC_OFFON off=1, on=0, write by master
  			bit2: lock status
			bit3: Rx_enbl, enable=1, disable=0;
byte 1,2,3,4: 4 bytes for RF frequency in kHz
byte 5,6: when AGC_OFFON=1(off),2bytes for user setable attenuation dB X 10, 0-250
			when AGC_OFFON=0(on), output power setting in dBm X10 +500,
			when it was written as 0xFFFF, nothing will be changed.
byte 7,8: output power detect, output_power dBm X10+500
byte 9: value=0-12	Gain compensation table address, 
							0=950MHz, 1=1050MHz, 2=1150MHz, 3=1250MHz, 4=1350MHz, 5=1450MHz, 
							6=1550MHz, 7=1650MHz, 8=1750MHz, 9=1850MHz, 10=1950MHz, 11=2050MHz, 
							12=2150MHz
			value=13-25	Power compensation table address,
							13=950MHz, 14=1050MHz, 15=1150MHz, 16=1250MHz, 17=1350MHz, 18=1450MHz, 
							19=1550MHz, 20=1650MHz, 21=1750MHz, 22=1850MHz, 23=1950MHz, 24=2050MHz, 
							25=2150MHz
			value=26-56	 output power detection table address, from -15dBm to +15dBm
							26=-15dBm, 27=-14dBm, 28=-13dBm, 29=-12dBm, 30=-11dBm, 31=-10dBm, 32=-9dBm, 
							33=-8dBm, 34=-7dBm, 35=-6dBm, 36=-5dBm, 37=-4dBm, 38=-3dBm, 39=-2dBm,
			 				40=-1dBm, 41=0dBm, 42=1dBm, 43=2dBm, 44=3dBm, 45=4dBm,46=5dBm, 47=6dBm, 
							48=7dBm, 49=8dBm, 50=9dBm, 51=10dBm, 52=11dBm, 53=12dBm, 54=13dBm, 55=14dBm, 
							56=15dBm, 
byte 10,11: 	Gain compensation dB X 10, range 0-65, 
				Power compensation dB X10, range 0-65
				Output power detection table
				if this is written as 0xfff by master,
				slave will read the compensation table and put into I2C_Array. 
**********************************************************************************************************************/
#define nI2C_WRITE 0x01
#define nI2C_READ 0xfe


#define nAGC_OFF		0xFD//0x02 //u8CtrlStatus|nAGC_OFF set off //swapped back
#define nAGC_ON			0x02//0xFD //u8CtrlStatus&nAGC_ON set on //swapped back
#define nLOCK			0x04
#define nUNLOCK 		0xFB
#define nRX_ENABLE 		0x08 //= mute on/off
#define nRX_DISABLE 	0xF7

typedef struct
{
	//bit0: write flag 1 by master, cleared by software		0x01 ~0xFE
	//bit1: AGC_OFFON off=1, on=0, write by master		0x02 ~0xFD
	//bit2: lock status									0x04  ~0xFB
	//bit3: Rx_enbl, enable=1, disable=0; 		 		0x08 ~0xF7

	BYTE u8CtrlStatus;   //BYTE 0 
	tunFreq       unRfFreq;     //BYTE 1-4 4 bytes for RF frequency in kHzs
    tunAtten      unAtten;      //BYTE 5-6 consider union here
    WORD		  u16RdPower;    //BYTE 7-8 output power detect, output_power dBm X10+500
    BYTE		u8GainCompenAddr; //byte 9 Gain compensation table address
	WORD		u16GainCompenVale; //byte 10-11 Gain compensation dB X 10, range 0-65, 

}tstI2CMsg;



#define nBUC_REF_ON	0x02
#define nBUC_REF_OFF 0xFD

#define nLNB_REF_ON	0x04
#define nLNB_REF_OFF 0xFB

#define nBUC_DC_ON	0x08
#define nBUC_DC_OFF 0xF7

#define nLNB_DC_ON	0x10
#define nLNB_DC_OFF 0xEF

#define nBUC_OVER_CURRENT	0x20

#define nLNB_OVER_CURRENT	0x40
#define nEXT_REF	0x80



/********************************************************************************************************************
byte 0: 
			bit0: write flag 1 by master, cleared by software
			bit1: BUC_REF_ONOFF 1=on, 0=off
  			bit2: LNB_REF_ONOFF 1=on, 0=off
			bit3: BUC_DC_ONOFF 1=on, 0=off
			bit4: LNB_DC_ONOFF 1=on, 0=off
			bit5: BUC DC over current 1=over current, 0=normal. 
					When BUC over current, BUC_DC_ONOFF will be set to 0. 
					This bit must be cleared before turn on the BUC DC again.
			bit6: LNB DC over current 1=over current, 0=normal. 
					When LNB over current, LNB_DC_ONOFF will be set to 0. 
					This bit must be cleared before turn on the LNB DC again.
			bit7: external reference detect 1=external reference 0=internal reference
byte 1:
			bit0: LED1
			bit1: LED2
			bit2: LED3
			bit3: LED4
byte 2,3: BUC current in mA, unsigned int
byte 4,5: LNB current in mA, unsigned int
byte 6,7: BUC current limit in mA, unsigned int
byte 8,9: LNB current limit in mA, unsinged int
**********************************************************************************************************************/

typedef struct
{
    BYTE u8Status;	//byte 0
	BYTE u8LEDSetting; //byte 1 bit0-3,= LED1-4
	WORD u16BUCCurrent;   //byte 2-3BUC current in mA, unsigned int
	WORD u16LNBCurrent;   //byte 4-5 LNB current in mA, unsigned int
	WORD u16BUCCurrentLimit;   //BYTE 6-7 BUC current limit in mA, unsigned int
	WORD u16LNBCurrentLimit;   //BYTE 8-9 LNB  current limit in mA, unsigned int	

}tstI2CMsgVOL;



typedef struct
{
    unsigned char u8Updateflag;
	unsigned char u818VDC;   //BYTE 0
	unsigned char u824VDC;   //BYTE 1

}tstI2CMessageVOL;


extern tstI2CMessage  stI2CUpCvtMsg;
extern tstI2CMessage  stI2CDownCvtMsg;
extern tstI2CMessageVOL  stI2CVOLMsg;

extern tstI2CMsg  stI2CUCMsg;
extern tstI2CMsg  stI2CDCMsg;
extern tstI2CMsgVOL  stI2CREFMsg;
extern tstI2CMsg  stI2CLOMsg;



extern char IPString[];
extern unsigned char LastMenu;
extern unsigned char CurrentMenu;
extern APP_CONFIG AppConfig;
extern unsigned char KeyPressedFlag, PressedKey, RefreshFlag;
extern BYTE EditUpdateFlag;//Edit position char update only
extern BYTE ValueUpdateFlag; //Content Value Update only

extern const rom tstMenuDisplay stMenuDisplay[30];



void OLED_vSetKepad(void);

void OLED_vSetIO(void);

void OLED_vEnableInterrupt(void);


void CheckBusy();

void WriteIns(char instruction);

void WriteData(char data1);

unsigned char ReadData(void);

void WriteString(unsigned char count,unsigned char * MSG);

void LCDWriteString(unsigned char * MSG);

void PrintCGRAM(unsigned char number1);

void LCDClear(void);

void LCDReturnhome(void);

void LCDEntryMode(void);


void LCDDisplay(unsigned char displayflag, unsigned char cusorflag, unsigned char blinkflag);

void Initial_LCD(void);

void PrintLCD(void);

void PrintBlinkLCD(void);



void DisplayCompanyMenu(void);


void InitalizeMenu(void);



BYTE LCD__u8GetOnOff(void);

BYTE LCD__u8UpdateToModule(BYTE* pu8Parameter,BYTE* pu8Data ,BYTE u8CompareFlag,BYTE* pu8SendData);



BYTE LCD_u8UpdateDisplayContent(void);
void KeyProcessing(void);
	void UpdateStatus(void);


void Main_vLEDLO(BYTE Setting);

void Main_vLEDTX(BYTE Setting);
void Main_vLEDLO(BYTE Setting);


//Set LED IO direction to output
void Main_vLEDInit(void);


#endif /* OLED_C1_H */


