#include "define.h"
#include "Global.h"
#include <string.h>

#include "DeviceApi.h"
#include "i2c_c1.h"
#include "Util.h"


#include "oled_c1.h"
#include "oled_c2.h"


unsigned char LCDBufferPosition[2];
char LOStatusString1[9] = {"LOCKED  "}; 
char LOStatusString2[9] = {"UNLOCKED"}; 

/*JuZh 950.000MHz to 2150.000MHz */
char RFFreqString1[12] = {"12750.000MHz"}; /* must update to 3 digits decimal */
char RFFreqString2[12] = {"12750.000MHz"}; /* must update to 3 digits decimal */
char AttenString1[8] = {"00.0 dB"}; 
char AttenString2[8] = {"00.0 dB"}; 

char IPString[16] = {"192.168.001.001"}; 
char MNString[18] = {"SCMDC62001SN10-RM"}; 
char SNString[9] = {"12345678"}; 

char s18VDC[4] = {"OFF"};
char s24VDC[4] = {"OFF"};
char sLNBREF[4] = {"OFF"};
char sBUCREF[4] = {"OFF"};


char sUCPower[10] = {"-30.0 dBm"};
char sDCPower[10] = {"-30.0 dBm"};
char sUPC_StPwr[10] = {"-00.0 dBm"};
char sDNC_StPwr[10] = {"-00.0 dBm"};

char sALCa[4]= {"OFF"};
char sALCb[4] = {"OFF"};
char sMutea[9] = {"DISABLED"};
char sMuteb[9] = {"DISABLED"};


unsigned char LastMenu = MENU0;
unsigned char CurrentMenu = MENU0;

/* LCD_u8UpdateDisplayContent is called if RefreshFlag is set to TRUE, it is set to TRUE if there is sys value update 
   or if there is Menu page change.
   RefreshFlag is set to false after LCD_u8UpdateDisplayContent and PrintLCD
*/
unsigned char KeyPressedFlag = FALSE, PressedKey = NULL;

BYTE RefreshFlag = FALSE; //Page change, update whole Menu
BYTE EditUpdateFlag = FALSE;//Edit position char update only
BYTE ValueUpdateFlag = FALSE; //Content Value Update only

unsigned char EditMode = FALSE, EditPosition = 0, FirstPressKey = TRUE;

tstI2CMessage  stI2CUpCvtMsg;
tstI2CMessage  stI2CDownCvtMsg;
tstI2CMessageVOL  stI2CVOLMsg;

tstI2CMsg  stI2CUCMsg;
tstI2CMsg  stI2CDCMsg;
tstI2CMsgVOL  stI2CREFMsg;
tstI2CMsg stI2CLOMsg;

BYTE u8ExtLO = 0;
BYTE u8LoBand = 0;
WORD u16LoFreq = 0;


char readflag = 0x00;


#pragma udata gpr8
char LCDPrintBuffer[2][nLCDLEN];

#pragma udata grp10
char LCDBlinkBuffer[2][nLCDLEN];


typedef struct menustructure
{
	unsigned char editable;
} menustructure_t;
#define MaxMenuNum 		28
menustructure_t ConvertMenu[MaxMenuNum];

		

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


const rom tstMenuDisplay stMenuDisplay[30]=
{
	{&Main_vPrintUpConverter,NULL,NULL,NULL,				MENU2,MENU3,	MENU0,MENU4,0,14}, //zj changed 0 -3, blink len 7 to 14
		
	{&Main_vPrintDownConverter,NULL,NULL,NULL,				MENU2,MENU0,	MENU1,MENU11,8,7},//skip
	
	{&Main_vPrintVolCtrl,NULL,NULL,NULL,					MENU3,MENU0,	MENU2,MENU2,15,10},//zj changed	to be fixed page
	
	{&Main_vPrintDeviceInfo,NULL,NULL,NULL,					MENU0,MENU2,	MENU3,MENU27,26,13},//zj changed 0 -3
	

	{&UpCvt_vPrintFreq, &UpCvt_vSetFreq,&LCDSub_vLeftMoveCursorFreq,&LCDSub_vRightMoveCursorFreq,		MENU5,MENU10,	MENU0,MENU4,3,9},
	
	{&UpCvt_vPrintPower, &UpCvt_vSetPower,&LCDSub_vLeftMoveCursorPower,&LCDSub_vRightMoveCursorPower,	MENU6,MENU4,	MENU0,MENU5,3,7},

	{&UpCvt_vPrintStPwr, &UpCvt_vSetStPwr,&LCDSub_vLeftMoveCursorPower,&LCDSub_vRightMoveCursorPower,	MENU7,MENU5,	MENU0,MENU6,3,9},	

	{&UpCvt_vPrintLo, NULL,NULL,NULL,																	MENU8,MENU6,	MENU0,MENU7,3,11},
	
	{&UpCvt_vPrintAttn, &UpCvt_vSetAttn,&LCDSub_vLeftMoveCursorAttn,&LCDSub_vRightMoveCursorAttn,		MENU9,MENU7,	MENU0,MENU8,3,6 },
	
	{&UpCvt_vPrintALC, &UpCvt_vSetALC,NULL,NULL,														MENU10,MENU8,	MENU0,MENU9,3,5},
	
	{&UpCvt_vPrintMute, &UpCvt_vSetMute,NULL,NULL,														MENU4,MENU9,	MENU0,MENU10,3,9},
	
	
	
	{&DownCvt_vPrintFreq, &DownCvt_vSetFreq,&LCDSub_vLeftMoveCursorFreq,&LCDSub_vRightMoveCursorFreq,	MENU12,MENU17,	MENU1,MENU11,3,9},
	
	{&DownCvt_vPrintPower, &DownCvt_vSetPower,&LCDSub_vLeftMoveCursorPower,&LCDSub_vRightMoveCursorPower,MENU13,MENU11,	MENU1,MENU12,3,7},
	
	{&DownCvt_vPrintStPwr, &DownCvt_vSetStPwr,&LCDSub_vLeftMoveCursorPower,&LCDSub_vRightMoveCursorPower,MENU14,MENU12,	MENU0,MENU13,3,9},	

	{&DownCvt_vPrintLo, NULL,NULL,NULL,																	MENU15,MENU13,	MENU1,MENU14,3,11},
	
	{&DownCvt_vPrintAttn, &DownCvt_vSetAttn,&LCDSub_vLeftMoveCursorAttn,&LCDSub_vRightMoveCursorAttn,	MENU16,MENU14,	MENU1,MENU15,3,6},
	
	{&DownCvt_vPrintALC, &DownCvt_vSetALC,NULL,NULL,													MENU17,MENU15,	MENU1,MENU16,3,5},
	
	{&DownCvt_vPrintMute, &DownCvt_vSetMute,NULL,NULL,													MENU11,MENU16,	MENU1,MENU17,3,9},
	
	
	
	{&VOLCTRL_vPrint18V, &VOLCTRL_vSet18V,NULL,NULL,			MENU19,MENU26,	MENU2,MENU18,5,8},
	
	{&VOLCTRL_vPrint24V, &VOLCTRL_vSet24V,NULL,NULL,			MENU20,MENU18,	MENU2,MENU19,5,8},
		
	{&VOLCTRL_vPrintLNBREF, &VOLCTRL_vSetLNBREF,NULL,NULL,		MENU21,MENU19,	MENU2,MENU20,5,9},
	
	{&VOLCTRL_vPrintBUCREF, &VOLCTRL_vSetBUCREF,NULL,NULL,		MENU22,MENU20,	MENU2,MENU21,5,9},


	{&VOLCTRL_vPrintEXTREF, NULL,NULL,NULL,						MENU23,MENU21,	MENU2,MENU22,5,9},

	{&VOLCTRL_vPrintBUCI, NULL,NULL,NULL,						MENU24,MENU22,	MENU2,MENU23,5,13},

	{&VOLCTRL_vPrintLNBI, NULL,NULL,NULL,						MENU25,MENU23,	MENU2,MENU24,5,13},
	
	{&VOLCTRL_vPrintBUCAlm, &VOLCTRL_vClearBUCAlm,NULL,NULL, 	MENU26,MENU24,	MENU2,MENU25,5,17},

	{&VOLCTRL_vPrintLNBAlm, &VOLCTRL_vClearLNBAlm,NULL,NULL, 	MENU18,MENU25,	MENU2,MENU26,5,17},
	
	
	{&Main_vPrintIP,&Main_vSetIP,&LCDSub_vLeftMoveCursorIP,&LCDSub_vRightMoveCursorIP,	MENU28,MENU29,	MENU3,MENU27,5,4},
	
	{&Main_vPrintModelNo,NULL,NULL,NULL,												MENU29,MENU27,	MENU3,MENU28,10,15},
	
	{&Main_vPrintSerialNo,NULL,NULL,NULL,												MENU27,MENU28,	MENU3,MENU29,26,14}

};



const rom char acLCDTitle[30][nLCDLEN]={
   //1234567890123456789012345678901234567890//
   //0123456789012345678901234567890123456789//     
    "[UP CONVERTER] [MAINCTRL] [DEVICE INFO] ",
    "[UP CONVERTER] [MAINCTRL] [DEVICE INFO] ",
    "[UP CONVERTER] [MAINCTRL] [DEVICE INFO] ",
    "[UP CONVERTER] [MAINCTRL] [DEVICE INFO] ",
    
    "UC [RF FREQ] [POWER] [SET PWR] [LO STATU",
    "UC [POWER] [SET PWR] [LO STATUS] [ATTN] ",
    "UC [SET PWR] [LO STATUS] [ATTN] [ALC] [R",
    "UC [LO STATUS] [ATTN] [ALC] [RF ENBL] [R",	  
    "UC [ATTN] [ALC] [RF ENBL] [RF FREQ] [POW",
    "UC [ALC] [RF ENBL] [RF FREQ] [POWER] [SE",
    "UC [RF ENBL] [RF FREQ] [POWER] [SET PWR]",

    
    "DC [RF FREQ] [POWER] [SET PWR] [LO STATU",
    "DC [POWER] [SET PWR] [LO STATUS] [ATTN] ",
    "DC [SET PWR] [LO STATUS] [ATTN] [ALC] [R",
    "DC [LO STATUS] [ATTN] [ALC] [RF ENBL] [R",    
    "DC [ATTN] [ALC] [RF ENBL] [RF FREQ] [POW",
    "DC [ALC] [RF ENBL] [RF FREQ] [POWER] [SE",
    "DC [RF ENBL] [RF FREQ] [POWER] [SET PWR]",
    
    "CTRL [LNB DC] [BUC DC] [LNB REF] [BUC RE",
    "CTRL [BUC DC] [LNB REF] [BUC REF]   REF ",
    "CTRL [LNB REF] [BUC REF] [  REF  ] [BUC ",
    "CTRL [BUC REF] [  REF  ] [BUC CURRENT] [",
    
    "CTRL [  REF  ] [BUC CURRENT] [LNB CURREN", 
    "CTRL [BUC CURRENT] [LNB CURRENT] [BUC OV", 
    "CTRL [LNB CURRENT] [BUC OVERCURRENT] [LN", 
    "CTRL [BUC OVERCURRENT] [LNB OVERCURRENT]", 
    "CTRL [LNB OVERCURRENT] [LNB DC] [BUC DC]",    
    
    "INFO [IP] [MODULE NUMBER] [SERIAL NUMBER",
    "INFO [IP] [MODULE NUMBER] [SERIAL NUMBER",
    "INFO [IP] [MODULE NUMBER] [SERIAL NUMBER"
}; /* Page 0-3 same title */

const rom char acLCDBlinkTitle[23][nLCDLEN]={
"        [DNCVT] [DC VOL] [DEVICE INFO]  ",
"[UPCVT]         [DC VOL] [DEVICE INFO]  ",
"[UPCVT] [DNCVT]          [DEVICE INFO]  ",
"[UPCVT] [DNCVT] [DC VOL]                ",

"UC            [POWER] [LO STATUS] [ATTN]",
"UC          [LO STATUS] [ATTN] [ALC] [MU",
"UC              [ATTN] [ALC] [MUTE] [RF ",
"UC         [ALC] [MUTE] [RF FREQ] [POWER",
"UC        [MUTE] [RF FREQ] [POWER] [LO S",
"UC         [RF FREQ] [POWER] [LO STATUS]",

"DC           [POWER] [LO STATUS] [ATTN]",
"DC         [LO STATUS] [ATTN] [ALC] [MU",
"DC             [ATTN] [ALC] [MUTE] [RF ",
"DC        [ALC] [MUTE] [RF FREQ] [POWER",
"DC       [MUTE] [RF FREQ] [POWER] [LO S",
"DC        [RF FREQ] [POWER] [LO STATUS]",

"VOL          [BUC DC][LNB REF] [BUC REF]",
"VOL [LNB DC]         [LNB REF] [BUC REF]",
"VOL [LNB DC] [BUC DC]          [BUC REF]",
"VOL [LNB DC] [BUC DC][LNB REF]          ",

"INFO      [MODULE NUMBER] [SERIAL NUMBER",
"INFO [IP]                 [SERIAL NUMBER",
"INFO [IP] [MODULE NUMBER]               "
}; /* Page 0-3 same title */


static BYTE SYS__u8UpdateUpConverter();
static BYTE SYS__u8UpdateDownConverter();
static BYTE SYS__u8UpdateVOL();



void DisplayCompanyMenu(void)
{

	strcpypgm2ram (LCDPrintBuffer[0], "                  SINGCOM               ");
	strcpypgm2ram (LCDPrintBuffer[1], "             FREQUENCY CONVERTER        ");

	PrintCompanyLCD();
}



void InitalizeMenu(void)
{
	unsigned char i;

	for (i = 0; i < 40; i++)
	{
		//LCDPrintBuffer[0][i] = ' ';
		LCDPrintBuffer[1][i] = ' ';

	}	
	CurrentMenu = MENU0;
	IPString[0] = ((AppConfig.MyIPAddr.v[0] / 100) % 10) + '0';
	IPString[1] = ((AppConfig.MyIPAddr.v[0] / 10) % 10) + '0';
	IPString[2] = ((AppConfig.MyIPAddr.v[0] / 1) % 10) + '0';
	IPString[4] = ((AppConfig.MyIPAddr.v[1] / 100) % 10) + '0';
	IPString[5] = ((AppConfig.MyIPAddr.v[1] / 10) % 10) + '0';
	IPString[6] = ((AppConfig.MyIPAddr.v[1] / 1) % 10) + '0';
	IPString[8] = ((AppConfig.MyIPAddr.v[2] / 100) % 10) + '0';
	IPString[9] = ((AppConfig.MyIPAddr.v[2] / 10) % 10) + '0';
	IPString[10] = ((AppConfig.MyIPAddr.v[2] / 1) % 10) + '0';
	IPString[12] = ((AppConfig.MyIPAddr.v[3] / 100) % 10) + '0';
	IPString[13] = ((AppConfig.MyIPAddr.v[3] / 10) % 10) + '0';
	IPString[14] = ((AppConfig.MyIPAddr.v[3] / 1) % 10) + '0';


	// Level 0 Menu 0/1/2/3: UC1/DC2/DCVOL/INFO
	// UC1	   Menu 4/5/6/7/8/9: Output Freq(Editable)/Output Power(E)/LO Status/Atten(E)/ALC(E)/Mute(E)
	// DC2	   Menu 10/11/12/13/14/15: Input Freq(Editable)/Output Power(E)/LO Status/Atten(E)/ALC(E)/Mute(E)
	// DCVOL   Menu 16/17: 18V DC(E) / 24V DC(E)
	// INFO Menu 18/19/20: IP(Editable)/MN/SN

	// Level 0 

	ConvertMenu[0].editable = FALSE;
	ConvertMenu[1].editable = FALSE;
	ConvertMenu[2].editable = FALSE;
	ConvertMenu[3].editable = FALSE;

	// UC1
	ConvertMenu[4].editable = TRUE;
	ConvertMenu[5].editable = FALSE;
	ConvertMenu[6].editable = TRUE;	
	ConvertMenu[7].editable = FALSE;
	ConvertMenu[8].editable = TRUE;
	ConvertMenu[9].editable = TRUE;
	ConvertMenu[10].editable = TRUE;

	// DC2	
	ConvertMenu[11].editable = TRUE;
	ConvertMenu[12].editable = FALSE;
	ConvertMenu[13].editable = TRUE;	
	ConvertMenu[14].editable = FALSE;
	ConvertMenu[15].editable = TRUE;
	ConvertMenu[16].editable = TRUE;
	ConvertMenu[17].editable = TRUE;

	// DCVOL

	ConvertMenu[18].editable = TRUE;
	ConvertMenu[19].editable = TRUE;
	ConvertMenu[20].editable = TRUE;
	ConvertMenu[21].editable = TRUE;
	ConvertMenu[22].editable = FALSE;
	ConvertMenu[23].editable = FALSE;
	ConvertMenu[24].editable = FALSE;
	ConvertMenu[25].editable = TRUE;
	ConvertMenu[26].editable = TRUE;	

	// INFO 
	ConvertMenu[27].editable = TRUE;
	ConvertMenu[28].editable = FALSE;
	ConvertMenu[29].editable = FALSE;

	
}



BYTE LCD__u8GetOnOff(void)
{
	if('N' == LCDPrintBuffer[1][1])
		return 1;
	else if('F' == LCDPrintBuffer[1][1])
	 	return 0;

}


BYTE LCD__u8UpdateToModule(BYTE* pu8Parameter,BYTE* pu8Data ,BYTE u8CompareFlag,BYTE* pu8SendData)
{
	if ((*pu8Data!= *pu8Parameter))
	{
		*pu8Parameter= *pu8Data;

		if(nBYTE_COMPARE == u8CompareFlag)
		{
			*pu8SendData = *pu8Data;

		}
		
		else
		{
			if(STATUS_ON == *pu8Data)
				*pu8SendData |= u8CompareFlag;
			else
				*pu8SendData &= (~u8CompareFlag);
		}
		
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}




/**************New Menu ******************/
// Level 0 Menu 0/1/2/3: UC1/DC2/DCVOL/INFO
// UC1	   Menu 4/5/6/7/8/9: Output Freq(Editable)/Output Power(E)/LO Status/Atten(E)/ALC(E)/Mute(E)
// DC2	   Menu 10/11/12/13/14/15: Input Freq(Editable)/Output Power(E)/LO Status/Atten(E)/ALC(E)/Mute(E)
// DCVOL   Menu 16/17: 18V DC(E) / 24V DC(E)
// INFO Menu 18/19/20: IP(Editable)/MN/SN

BYTE LCD_u8UpdateDisplayContent(void)
{
	unsigned char i;

	memset(LCDPrintBuffer[1],' ', nLCDLEN);
	
	stMenuDisplay[CurrentMenu].pvfPrintMenu();
}


static BYTE LCD__u8ToParentMenu()
{
   CurrentMenu = stMenuDisplay[CurrentMenu].u8UpMenu;       
}

 /* In main menus, Enter 1st child menus */  
static BYTE LCD__u8ToChildMenu()
{
    CurrentMenu = stMenuDisplay[CurrentMenu].u8DownMenu; 
  
}


 BYTE LCD__u8UpkeyEdit()
{
    // update LCD display zj: must consider on off settings too
    if ((LCDPrintBuffer[1][EditPosition] >= '0') && (LCDPrintBuffer[1][EditPosition] < '9'))
    {
        LCDPrintBuffer[1][EditPosition]++;
    }
    else if (LCDPrintBuffer[1][EditPosition] == '9')
    {
        LCDPrintBuffer[1][EditPosition] = '0';
    }
#if 1 

    else if (LCDPrintBuffer[1][EditPosition] == '-')
    {
        LCDPrintBuffer[1][EditPosition] = '+';

    }

    else if (LCDPrintBuffer[1][EditPosition] == '+')
    {
        LCDPrintBuffer[1][EditPosition] = '-';

    }				
#endif
    if(!memcmppgm2ram(LCDPrintBuffer[1],"ON ",3))
    {
        memcpypgm2ram(LCDPrintBuffer[1],"OFF",3);

    }
    else if(!memcmppgm2ram(LCDPrintBuffer[1],"OFF",3)) 
    {
        memcpypgm2ram(LCDPrintBuffer[1],"ON ",3);

    }

    if(!memcmppgm2ram(LCDPrintBuffer[1],"Alarm",5))
    {
        memcpypgm2ram(LCDPrintBuffer[1],"OK   ",5);

    }

    if(!memcmppgm2ram(LCDPrintBuffer[1],"ENABLED ",8))
    {
        memcpypgm2ram(LCDPrintBuffer[1],"DISABLED",8);

    }  
    else if(!memcmppgm2ram(LCDPrintBuffer[1],"DISABLED",8))
    {
        memcpypgm2ram(LCDPrintBuffer[1],"ENABLED ",8);

    }      
 
    EditUpdateFlag = TRUE;
    /* Blink is required here to display the updated value */
    /* No additional Menu Content updated is required  */
    /* RefreshFlag is already set to true, when entering Edit mode */
}

static BYTE LCD__u8UpkeyToParentMenu()
{
    LCD__u8ToParentMenu();
     /* Refresh flag not required to be set here, since there is menu change, SYS__vLcdKeyPadTask will refresh  */   
    
}

static BYTE LCD__u8UpKeyProcess()
{
    if (EditMode == TRUE)
    {
        LCD__u8UpkeyEdit();
    }
    else /* Go into parent menu */
    {
        LCD__u8UpkeyToParentMenu();
    }    
    
    
}

static BYTE LCD__u8DownKeyEdit()
{
    // update LCD display  zj: must consider on off settings too
    if ((LCDPrintBuffer[1][EditPosition] > '0') && (LCDPrintBuffer[1][EditPosition] <= '9'))
    {
        LCDPrintBuffer[1][EditPosition]--;
    }
    else if (LCDPrintBuffer[1][EditPosition] == '0')
    {
        LCDPrintBuffer[1][EditPosition] = '9';
    }
#if 1	
    else if (LCDPrintBuffer[1][EditPosition] == '-')
    {
        LCDPrintBuffer[1][EditPosition] = '+';
    }

    else if (LCDPrintBuffer[1][EditPosition] == '+')
    {
        LCDPrintBuffer[1][EditPosition] = '-';

    }	
#endif
    if(!memcmppgm2ram(LCDPrintBuffer[1],"ON ",3))
    {
        memcpypgm2ram(LCDPrintBuffer[1],"OFF",3);

    }
    else if(!memcmppgm2ram(LCDPrintBuffer[1],"OFF",3)) 
    {
        memcpypgm2ram(LCDPrintBuffer[1],"ON ",3);
    }

    if(!memcmppgm2ram(LCDPrintBuffer[1],"Alarm",5))
    {
        memcpypgm2ram(LCDPrintBuffer[1],"OK   ",5);

    }

    if(!memcmppgm2ram(LCDPrintBuffer[1],"ENABLED ",8))
    {
        memcpypgm2ram(LCDPrintBuffer[1],"DISABLED",8);

    }  
    else if(!memcmppgm2ram(LCDPrintBuffer[1],"DISABLED",8))
    {
        memcpypgm2ram(LCDPrintBuffer[1],"ENABLED ",8);

    }   	
    
    EditUpdateFlag = TRUE;
    
    /* Blink is required here to display the updated value */
    /* No additional Menu Content updated is required  */
    /* RefreshFlag is already set to true, when entering Edit mode */
}

static BYTE LCD__u8DownkeyToChildMenu()
{
    LCD__u8ToChildMenu();    
    /* Refresh flag not required to be set here, since there is menu change, SYS__vLcdKeyPadTask will refresh  */    
}

static BYTE LCD__u8DownKeyProcess()
{
    if (EditMode == TRUE)
    {

        LCD__u8DownKeyEdit();
        
    }
    else /* Go into child menu */
    {
        LCD__u8DownkeyToChildMenu();
    }       
}

void LCDSub_vLeftMoveCursorFreq()
{
	if (EditPosition == 0)
	{
		EditPosition = 7;
	}
	else if (EditPosition == 5) //skip '.'
	{
		EditPosition = 3;
	}
	else
	{
		EditPosition--;
	}


}

void LCDSub_vLeftMoveCursorAttn()
{
	if (EditPosition == 0)
	{
		EditPosition = 3;
	}
	else if (EditPosition == 3)//skip '.'
	{
		EditPosition = 1;
	}					
	else
	{
		EditPosition--;
	}


}


void LCDSub_vLeftMoveCursorPower(void)
{
	if (EditPosition == 0)
	{
		EditPosition = 4;
	}
	else if (EditPosition == 4)
	{
		EditPosition =2;
	}		
	else
	{
		EditPosition--;
	}


}

void LCDSub_vLeftMoveCursorIP(void)
{
	if (EditPosition == 0)
	{
		EditPosition = 14;
	}

	if('.' == LCDPrintBuffer[1][EditPosition-1]) /* Skip '.' */
	{
		EditPosition -= 2;	  
	}
	else
	{
		EditPosition--;
	}


}

static BYTE LCD__u8LeftKeyMoveCursor(void)
{
    // update LCD display
    stMenuDisplay[CurrentMenu].pvfMoveCursorLeft();

	// void DRI_vLCDDisplay(unsigned char displayflag, unsigned char cusorflag, unsigned char blinkflag)
    WriteIns(0xC0 + EditPosition);
    DRI_vLCDDisplay(TRUE, TRUE, FALSE);      
}

static BYTE LCD__u8LeftKeyToLeftMenu(void)
{

        CurrentMenu = stMenuDisplay[CurrentMenu].u8LeftMenu;
   
   
 /* Refresh flag not required to be set here, since there is menu change, SYS__vLcdKeyPadTask will refresh  */       
}


static BYTE LCD__u8LeftKeyProcess(void)
{
    if (EditMode == TRUE) /* Move cursor to left */
    {
        LCD__u8LeftKeyMoveCursor();
    }
    else /* Go to previous menu */
    {
        LCD__u8LeftKeyToLeftMenu();
    }    
     
}

void LCDSub_vRightMoveCursorFreq(void)
{
	if (EditPosition == 7)
	{
		EditPosition = 0;
	}
	else if (EditPosition == 3) //'.'
	{
		EditPosition = 5;
	}
	else
	{
		EditPosition++;
	}


}

void LCDSub_vRightMoveCursorAttn(void)
{
	if (EditPosition == 3)
	{
		EditPosition = 0;
	}
	else if (EditPosition == 1)//skip '.'
	{
		EditPosition = 3;
	}					
	else
	{
		EditPosition = 1;
	}


}


void LCDSub_vRightMoveCursorPower(void)
{
	if (EditPosition == 2)
	{
		EditPosition = 4;
	}	
	else if (EditPosition == 4)
	{
		EditPosition = 0;
	}		
	else
	{
		EditPosition++;
	}


}

void LCDSub_vRightMoveCursorIP(void)
{
	if (EditPosition == 14)
	 {
		 EditPosition = 0;
	 }

	 if('.' == LCDPrintBuffer[1][EditPosition+1]) /* Skip '.' */
	 {
		 EditPosition += 2;    
	 }
	 else
	 {
		 EditPosition++;
	 }


}


static BYTE LCD__u8RightKeyMoveCursor()
{
    // update LCD display
   
	stMenuDisplay[CurrentMenu].pvfMoveCursorRight();

    // void DRI_vLCDDisplay(unsigned char displayflag, unsigned char cusorflag, unsigned char blinkflag)
    WriteIns(0xC0 + EditPosition);
    DRI_vLCDDisplay(TRUE, TRUE, FALSE);    
    
}

static BYTE LCD__u8RightKeyToRightMenu()
{
	CurrentMenu = stMenuDisplay[CurrentMenu].u8RightMenu;   
 /* Refresh flag not required to be set here, since there is menu change, SYS__vLcdKeyPadTask will refresh  */       
}

static BYTE LCD__u8RightKeyProcess()
{
    if (EditMode == TRUE)   /* Move cursor to right */
    {
        LCD__u8RightKeyMoveCursor();
    }
    else    /* Go to next menu */
    {
        LCD__u8RightKeyToRightMenu();
    }      
}

static BYTE LCD__u8EnterKeySetValue()
{ 
    
    // update LCD value to Freq/Atten/IP, TBD, update wrt power, ALC, Mute
	stMenuDisplay[CurrentMenu].pvfSetValue();

    DRI_vLCDDisplay(TRUE, FALSE, FALSE);
    EditMode = FALSE;
    EditPosition = 0;
}


 /* In main menus, Enter 1st child menus */  
static BYTE LCD__u8EnterKeyToChildMenu()
{
    LCD__u8ToChildMenu();
    /* Refresh flag not required to be set here, since there is menu change, SYS__vLcdKeyPadTask will refresh  */   
}

static BYTE LCD__u8EnterKeyToEditMode()
{
    EditMode = TRUE;
    EditPosition = 0;

    WriteIns(0xC0 + EditPosition);
    DRI_vLCDDisplay(TRUE, TRUE, FALSE);    
   //RefreshFlag = TRUE;

}

static BYTE LCD__u8EnterKeyProcess()
{   
    /* 1. In Edit mode Set new values */
    if (EditMode == TRUE) 
    {
        LCD__u8EnterKeySetValue();

		return 0;
    }


    /* 2. Not in Edit Mode */	
#if 0 	
    /* 2.1 In main menus, Enter 1st child menus */    
	/*JuZh: Not required feature */
    if(CurrentMenu <= MENU3)
    {
        LCD__u8EnterKeyToChildMenu();
		return 0;
    }
#endif	
    /* 2.2 In Child menus, go to edit mode */  
    if (ConvertMenu[CurrentMenu].editable == TRUE)
    {
        LCD__u8EnterKeyToEditMode();
		return 0;
    }
   // RefreshFlag = TRUE;       
}

static BYTE LCD__u8CancelKeyExitEditMode()
{				
    EditMode = FALSE;
    EditPosition = 0;
    DRI_vLCDDisplay(TRUE, FALSE, FALSE);        
}

/* Consider merget this function with UpkeyToParentMenu */
static BYTE LCD__u8CancelKeyToParentMenu()
{
    LCD__u8ToParentMenu();
    /* Refresh flag not required to be set here, since there is menu change, SYS__vLcdKeyPadTask will refresh  */   
}

static BYTE LCD__u8CancelKeyProcess()
{

    /* 1. In Edit mode, Cancel Edit Mode */
    if(TRUE == EditMode) 
    {
        LCD__u8CancelKeyExitEditMode();
    }
#if 0 	
    /* 2. Not in editor mode, in child menu,  Exit from child menu, Enter parent menus */
	/* JuZh: Diabled not required feature to save process time */
    else
    {
        LCD__u8CancelKeyToParentMenu();
    }
#endif 	
    
    RefreshFlag = TRUE;       
}


// Level 0 Menu 0/1/2/3: UC1/DC2/DCVOL/INFO
// UC1	   Menu 4/5/6/7/8/9: Output Freq(Editable)/Output Power(E)/LO Status/Atten(E)/ALC(E)/Mute(E)
// DC2	   Menu 10/11/12/13/14/15: Input Freq(Editable)/Output Power(E)/LO Status/Atten(E)/ALC(E)/Mute(E)
// DCVOL   Menu 16/17: 18V DC(E) / 24V DC(E)
// INFO Menu 18/19/20: IP(Editable)/MN/SN



void KeyProcessing(void)
{

	switch (PressedKey)
	{
		case UPKEY:
		{
            LCD__u8UpKeyProcess();
		}
		break;
		case DOWNKEY:
		{
            LCD__u8DownKeyProcess();
		}
		break;
		case LEFTKEY:
		{
            LCD__u8LeftKeyProcess();
		}
		break;
		case RIGHTKEY:
		{
            LCD__u8RightKeyProcess();
		}
		break;
		case ENTERKEY: //zj tbd must update freq 0000.000 attn 00.0, ALC mute, Power
		{
            LCD__u8EnterKeyProcess();
		}
		break;
		case CANCELKEY:
		{
            LCD__u8CancelKeyProcess();
		}
		break;
		default :
		break;
	}

}


//tstI2CMsg  stI2CUCMsg;
//tstI2CMsg  stI2CDCMsg;
//tstI2CMsgVOL  stI2CREFMsg;


static BYTE SYS__u8UpdateUpConverter()
{
 	DWORD tempDWORD = 0;
	WORD tempWORD = 0;
	BYTE u8TempByte = 0; 
	BOOL boReturn = FALSE;
	float fAtten;
	float fSetPwr;
	int i16frac;
    
	stI2CUCMsg.u8CtrlStatus &= nI2C_READ;
	
	I2C_Send(I2C_UPCVT_ADDR, (char*)&readflag, 1); //Notify Want to read I2C message by sending null
	boReturn = I2C_Read(I2C_UPCVT_ADDR, (char*)&stI2CUCMsg, sizeof(tstI2CMsg)); //Read I2C message
	if(!boReturn)
		return FALSE;
    
	if (((stI2CUCMsg.u8CtrlStatus & nLOCK )== 0) && (stConverter.stUp.u8AlarmStatus != 0))
	{

		stConverter.stUp.u8AlarmStatus = 0; //0 = alm
		stConverter.stUp.u8Lock = 0;
        /* If we are not at this menu now, we don't have to refresh now */
		if(((CurrentMenu == nLOSTATUS_MENU_A) || (CurrentMenu == MENU0)) && (TRUE != EditMode) ) /* if edit is on going, don't refresh the new read values */
        {
            ValueUpdateFlag = TRUE;
            stMenuDisplay[CurrentMenu].pvfPrintMenu();
        }


	
		Main_vLEDLO(OFF);
        Main_vLEDRX(OFF); 
           
	}
	else if (((stI2CUCMsg.u8CtrlStatus & nLOCK)!= 0) && (stConverter.stUp.u8AlarmStatus == 0))
	{

	    stConverter.stUp.u8AlarmStatus = 1;
		stConverter.stUp.u8Lock = 1;
        /* If we are not at this menu, we don't have to refresh now */
		if(((CurrentMenu == nLOSTATUS_MENU_A)|| (CurrentMenu == MENU0)) && (TRUE != EditMode) )
        {
			ValueUpdateFlag = TRUE;
            stMenuDisplay[CurrentMenu].pvfPrintMenu();
        }


		/* ZJ don't check down cvt anymore */
	//	if(stConverter.stDown.u8Lock == 1) //check the other cvt
		if(u8ExtLO == 1)
	{
			Main_vLEDLO(ON);
            
            Main_vLEDRX(ON); 
	}
        
	}


	u8TempByte = (stI2CUCMsg.u8CtrlStatus & nAGC_ON)?1:0;
	//if(u8TempByte != stConverter.stUp.u8ALC)
	{
		stConverter.stUp.u8ALC= u8TempByte;



		if(STATUS_OFF == stConverter.stUp.u8ALC)
		{
			strcpypgm2ram(sALCa,"OFF");
		}
		else
		{
			strcpypgm2ram(sALCa,"ON ");
		}

		/* If we are not at this menu now, we don't have to refresh now */
		if((CurrentMenu == nALC_MENU_A)&& (TRUE != EditMode))
		{
            ValueUpdateFlag = TRUE;
            stMenuDisplay[nALC_MENU_A].pvfPrintMenu();
        }
        
	}

	u8TempByte = (stI2CUCMsg.u8CtrlStatus & nRX_ENABLE)?1:0; //0 = disabled, 1 = enabled
	//if(u8TempByte != stConverter.stUp.u8Mute)
	{
		stConverter.stUp.u8Mute= u8TempByte;
		


		if(STATUS_OFF == stConverter.stUp.u8Mute)
		{
			strcpypgm2ram(sMutea,"DISABLED ");
			Main_vLEDTX(OFF);
		}
		else
		{
			strcpypgm2ram(sMutea,"ENABLED ");
			Main_vLEDTX(ON);
		}
       
	   if((CurrentMenu == nMUTE_MENU_A)&& (TRUE != EditMode))
	   {
		   ValueUpdateFlag = TRUE;
		   stMenuDisplay[nMUTE_MENU_A].pvfPrintMenu();
	   }

	}	


    tempDWORD = Util_u16DWORDSwap(stI2CUCMsg.unRfFreq.u32Freq);

    if((tempDWORD != stConverter.stUp.u32OutputFreq)&&(tempDWORD <=MAXRFFREQ)&&(tempDWORD>=MINRFFREQ))
    {
        stConverter.stUp.u32OutputFreq = tempDWORD;
		
		sprintf(RFFreqString1,"%04ld.%03ldMHz",(u16LoFreq + stConverter.stUp.u32OutputFreq/1000),
				((DWORD)u16LoFreq*1000 + stConverter.stUp.u32OutputFreq)%1000);	
    
        if(((CurrentMenu == nFREQ_MENU_A) || (CurrentMenu == MENU0)) && (TRUE != EditMode))
        {
            ValueUpdateFlag = TRUE;
            stMenuDisplay[CurrentMenu].pvfPrintMenu();
        }
    }

    
    tempWORD = Util_u16ByteSwap(stI2CUCMsg.unAtten.u16Atten);

	if (stConverter.stUp.u8ALC == STATUS_OFF) /* ALC OFF, read out Attn*/
	{
	    if ((tempWORD != stConverter.stUp.u16Atten)&&(tempWORD<= MAXATTEN)&&(tempWORD>= MINATTEN))
	    {

	        stConverter.stUp.u16Atten = tempWORD;
	    
			fAtten = (float)stConverter.stUp.u16Atten /10.0f;
			
			sprintf(AttenString1,"%02d.%1d dB",(int)fAtten,(int)(fAtten*10) %10 );	

			if((CurrentMenu == nATTN_MENU_A)&& (TRUE != EditMode))
	        {
	            ValueUpdateFlag = TRUE;
	            stMenuDisplay[nATTN_MENU_A].pvfPrintMenu();
	        }

	    }
	}
	else /* ALC ON, read out Set Power*/
	{
	    if ((tempWORD != stConverter.stUp.u16SetPwr)&&(tempWORD<= MAXPOWER)&&(tempWORD>= MINPOWER))
	    {

	        stConverter.stUp.u16SetPwr = tempWORD;

			fSetPwr = ((float)stConverter.stUp.u16SetPwr -500)/10.0f;

			stConverter.stUp.fSetPwr = fSetPwr;

			i16frac = (int)(fSetPwr*10) %10;
			if(i16frac < 0)
				i16frac *= -1;
			if ((fSetPwr<0)&& (fSetPwr>-1))
			{
				sprintf(sUPC_StPwr,"-%02d.%1d dBm",(int)fSetPwr,i16frac);	
			}
			else
			{
				sprintf(sUPC_StPwr,"%+03d.%1d dBm",(int)fSetPwr,i16frac);
			}	
			if((CurrentMenu == nSTPWR_MENU_A)&& (TRUE != EditMode))
	        {
	            ValueUpdateFlag = TRUE;
	            stMenuDisplay[nSTPWR_MENU_A].pvfPrintMenu();
	        }

	    }


	}

	



	tempWORD = Util_u16ByteSwap(stI2CUCMsg.u16RdPower);
	if(((tempWORD) != stConverter.stUp.u16OutputPower)&&(tempWORD<=MAXPOWER)&&(tempWORD>=MINPOWER))
	{
		stConverter.stUp.u16OutputPower = tempWORD; ;
		stConverter.stUp.fOutputPower= ((float)tempWORD-500) ;
		stConverter.stUp.fOutputPower= stConverter.stUp.fOutputPower / 10.0f;
		fSetPwr = stConverter.stUp.fOutputPower;

		i16frac = (int)(fSetPwr*10) %10;
		if(i16frac < 0)
			i16frac *= -1;

		if ((fSetPwr<0) && (fSetPwr>-1))
		{
			sprintf(sUCPower,"-%02d.%1d dBm",(int)fSetPwr,i16frac);
		}
		else
		{
			sprintf(sUCPower,"%+03d.%1d dBm",(int)fSetPwr,i16frac);
		}	

		if(((CurrentMenu == nPOWER_MENU_A)  || (CurrentMenu == MENU0))&& (TRUE != EditMode))
        {
			ValueUpdateFlag = TRUE;
            stMenuDisplay[CurrentMenu].pvfPrintMenu();
        }
	}

	return TRUE;
          
}

static BYTE SYS__u8UpdateDownConverter()
{
 	DWORD tempDWORD = 0;
	WORD tempWORD = 0;
	BYTE u8TempByte = 0;    
	BOOL boReturn = FALSE;	
	float fAtten;
	float fSetPwr;
	int i16frac;
    
	stI2CDCMsg.u8CtrlStatus &= nI2C_READ;
	
	I2C_Send(I2C_DownCVT_ADDR, (char*)&readflag, 1);
	
	boReturn = I2C_Read(I2C_DownCVT_ADDR, (char*)&stI2CDCMsg, sizeof(tstI2CMsg));

	if(!boReturn)
		return FALSE;
    
    
	if (((stI2CDCMsg.u8CtrlStatus & nLOCK)== 0)  && (stConverter.stDown.u8AlarmStatus != 0))
	{

		stConverter.stDown.u8AlarmStatus = 0;
		stConverter.stDown.u8Lock = 0;

		if(((CurrentMenu == nLOSTATUS_MENU_B)  || (CurrentMenu == MENU1)) && (TRUE != EditMode))
		{
            ValueUpdateFlag = TRUE;
            stMenuDisplay[CurrentMenu].pvfPrintMenu();
        }

//		Main_vLEDLO(OFF);
        
	}
	else if (((stI2CDCMsg.u8CtrlStatus & nLOCK)!= 0) && (stConverter.stDown.u8AlarmStatus == 0))
	{

        
		stConverter.stDown.u8AlarmStatus = 1;
		stConverter.stDown.u8Lock = 1;

		if(((CurrentMenu == nLOSTATUS_MENU_B)  || (CurrentMenu == MENU1))&& (TRUE != EditMode))
        {
			ValueUpdateFlag = TRUE;
             stMenuDisplay[CurrentMenu].pvfPrintMenu();
        }		

//		if(stConverter.stUp.u8Lock == 1)
//			Main_vLEDLO(ON);
       
	}


	u8TempByte = (stI2CDCMsg.u8CtrlStatus & nAGC_OFF)?0:1; 
	//if(u8TempByte != stConverter.stDown.u8ALC)
	{
		stConverter.stDown.u8ALC= u8TempByte;



		if(STATUS_OFF == stConverter.stDown.u8ALC)
		{
			strcpypgm2ram(sALCb,"OFF");
		}
		else
		{
			strcpypgm2ram(sALCb,"ON ");
		}

		if((CurrentMenu == nALC_MENU_B) && (TRUE != EditMode))
        {
			ValueUpdateFlag = TRUE;
            stMenuDisplay[nALC_MENU_B].pvfPrintMenu();
        }
        
	}
	u8TempByte = (stI2CDCMsg.u8CtrlStatus & nRX_ENABLE)?1:0;
	//if(u8TempByte != stConverter.stDown.u8Mute)
	{
		stConverter.stDown.u8Mute= u8TempByte;
		


		if(STATUS_OFF == stConverter.stDown.u8Mute)
		{
			strcpypgm2ram(sMuteb,"DISABLED");
			//Main_vLEDRX(OFF); //zj disable for Lband
		}
		else
		{
			strcpypgm2ram(sMuteb,"ENABLED ");
			//Main_vLEDRX(ON);  //zj disable for Lband
		}

		if ((CurrentMenu == nMUTE_MENU_B) && (TRUE != EditMode))
		{
            ValueUpdateFlag = TRUE;
            stMenuDisplay[nMUTE_MENU_B].pvfPrintMenu();   
        }

	}	

    
    tempDWORD = Util_u16DWORDSwap(stI2CDCMsg.unRfFreq.u32Freq);


    if ((tempDWORD != stConverter.stDown.u32InputFreq)&&(tempDWORD <=MAXRFFREQ)&&(tempDWORD>=MINRFFREQ))
    {

        
        stConverter.stDown.u32InputFreq = tempDWORD;


		sprintf(RFFreqString2,"%04ld.%03ldMHz",stConverter.stDown.u32InputFreq/1000,stConverter.stDown.u32InputFreq%1000 );	
		
        if(((CurrentMenu == nFREQ_MENU_B)  || (CurrentMenu == MENU1)) && (TRUE != EditMode))
        {
            ValueUpdateFlag = TRUE;
             stMenuDisplay[CurrentMenu].pvfPrintMenu();   
        }

          
    }

    
    
    tempWORD = Util_u16ByteSwap(stI2CDCMsg.unAtten.u16Atten);
	if (stConverter.stDown.u8ALC == STATUS_OFF) /* ALC OFF, read out Attn*/
	{

		    if ((tempWORD != stConverter.stDown.u16Atten)&&(tempWORD<= MAXATTEN)&&(tempWORD>= MINATTEN))
		    {

		        stConverter.stDown.u16Atten = tempWORD;

				fAtten = (float)stConverter.stDown.u16Atten /10.0f;
		    
				sprintf(AttenString2,"%02d.%1d dB",(int)fAtten,(int)(fAtten*10) %10 );	
				
		        if((CurrentMenu == nATTN_MENU_B) && (TRUE != EditMode))
		        {
		            ValueUpdateFlag = TRUE;
		            stMenuDisplay[nATTN_MENU_B].pvfPrintMenu(); 
		        }

		                
		    }
	}

	else /* ALC ON, read out Set Power*/
	{
	    if ((tempWORD != stConverter.stDown.u16SetPwr)&&(tempWORD<= MAXPOWER)&&(tempWORD>= MINPOWER))
	    {

	        stConverter.stDown.u16SetPwr = tempWORD;

			fSetPwr = ((float)stConverter.stDown.u16SetPwr -500)/10.0f;

			stConverter.stDown.fSetPwr = fSetPwr;

			i16frac = (int)(fSetPwr*10) %10;

			if(i16frac < 0)
				i16frac *= -1;
			
			if ((fSetPwr<0) && (fSetPwr>-1))
			{
				sprintf(sDNC_StPwr,"-%02d.%1d dBm",(int)fSetPwr,i16frac);	
			}
			else
			{
				sprintf(sDNC_StPwr,"%+03d.%1d dBm",(int)fSetPwr,i16frac);
			}
			if((CurrentMenu == nSTPWR_MENU_B)&& (TRUE != EditMode))
	        {
	            ValueUpdateFlag = TRUE;
	            stMenuDisplay[nSTPWR_MENU_B].pvfPrintMenu();
	        }

	    }

	}
	

	
	
	tempWORD = Util_u16ByteSwap(stI2CDCMsg.u16RdPower);

	if((tempWORD != stConverter.stDown.u16OutputPower)&&(tempWORD<=MAXPOWER)&&(tempWORD>=MINPOWER))
	{
		stConverter.stDown.i16OutputPower = tempWORD;
		stConverter.stDown.fOutputPower = ((float)tempWORD-500);
		stConverter.stDown.fOutputPower = stConverter.stDown.fOutputPower /10.0f;
		fSetPwr = stConverter.stDown.fOutputPower;

		i16frac = (int)(fSetPwr*10) %10;
		
		if(i16frac < 0)
			i16frac *= -1;
		

		if ((fSetPwr<0) && (fSetPwr>-1))
		{
        	sprintf(sDCPower,"-%02d.%1d dBm",(int)fSetPwr,i16frac);
		}
		else
		{
        	sprintf(sDCPower,"%+03d.%1d dBm",(int)fSetPwr,i16frac);
		}
		if(((CurrentMenu == nPOWER_MENU_B) || (CurrentMenu == MENU1))&& (TRUE != EditMode))
        {
			ValueUpdateFlag = TRUE;
            stMenuDisplay[CurrentMenu].pvfPrintMenu();
        }

	}    

	return TRUE;
}

static BYTE SYS__u8UpdateVOL()
{
	BYTE u8TempByte = 0;
	WORD u16TempWord = 0;
	BOOL boReturn = FALSE;	
    
	stI2CREFMsg.u8Status &= nI2C_READ;
	
	I2C_Send(I2C_REF_ADDR, (char*)&readflag, 1);
	boReturn = I2C_Read(I2C_REF_ADDR, (char*)&stI2CREFMsg, sizeof(tstI2CMsgVOL));

	if(!boReturn)
		return FALSE;
    
    
    u8TempByte = stI2CREFMsg.u8Status & nLNB_DC_ON ? 1:0;
    if(stConverter.stDC.u8LNB_DC_ONOFF!= u8TempByte )
    {
        stConverter.stDC.u8LNB_DC_ONOFF= u8TempByte;
		if (STATUS_ON != stConverter.stDC.u8LNB_DC_ONOFF)
		{
			s18VDC[1] ='F';
			s18VDC[2] ='F';
		}
		else
		{
			s18VDC[1] ='N';
			s18VDC[2] =' ';

		}
	    
		if(((CurrentMenu == nDC18V_MENU) || (CurrentMenu == MENU2)) && (TRUE != EditMode))
	    {	ValueUpdateFlag = TRUE;
	        stMenuDisplay[CurrentMenu].pvfPrintMenu(); 
	    }
	         
            
    }

   
    
    u8TempByte = stI2CREFMsg.u8Status & nBUC_DC_ON ? 1:0;
	
    if(stConverter.stDC.u8BUC_DC_ONOFF!= u8TempByte )
    {
        stConverter.stDC.u8BUC_DC_ONOFF= u8TempByte;

		
		if (STATUS_ON != stConverter.stDC.u8BUC_DC_ONOFF)
		{
			s24VDC[1] ='F';
			s24VDC[2] ='F';
		}
		else
		{
			s24VDC[1] ='N';
			s24VDC[2] =' ';
		
		}
		
		 if (((CurrentMenu == nDC24V_MENU) || (CurrentMenu == MENU2)) && (TRUE != EditMode))
		 {
			 ValueUpdateFlag = TRUE;
		 
			 stMenuDisplay[CurrentMenu].pvfPrintMenu();  
		 }
		
    } 



	 u8TempByte = stI2CREFMsg.u8Status & nBUC_REF_ON ? 1:0;
	 
	 if(stConverter.stDC.u8BUC_REF_ONOFF!= u8TempByte )
	 {
		 stConverter.stDC.u8BUC_REF_ONOFF= u8TempByte;
		if (STATUS_ON != stConverter.stDC.u8BUC_REF_ONOFF)
		{
			sBUCREF[1] ='F';
			sBUCREF[2] ='F';
		}
		else
		{
			sBUCREF[1] ='N';
			sBUCREF[2] =' ';
		}


		if ((CurrentMenu == nBUCREF_MENU) && (TRUE != EditMode))
		{
			ValueUpdateFlag = TRUE;

			stMenuDisplay[nBUCREF_MENU].pvfPrintMenu();	
		}

	 } 


	 u8TempByte = stI2CREFMsg.u8Status & nLNB_REF_ON ? 1:0;
	 
	 if(stConverter.stDC.u8LNB_REF_ONOFF!= u8TempByte )
	 {
		 stConverter.stDC.u8LNB_REF_ONOFF= u8TempByte;

		 if (STATUS_ON != stConverter.stDC.u8LNB_REF_ONOFF)
		 {
			 sLNBREF[1] ='F';
			 sLNBREF[2] ='F';
		 }
		 else
		 {
			 sLNBREF[1] ='N';
			 sLNBREF[2] =' ';
		 }	

		 if ((CurrentMenu == nLNBREF_MENU) && (TRUE != EditMode))
		 {
			 ValueUpdateFlag = TRUE;
		 
			 stMenuDisplay[nLNBREF_MENU].pvfPrintMenu();	
		 }	 
	 		 
		 

	 } 


	 u8TempByte = stI2CREFMsg.u8Status & nBUC_OVER_CURRENT ? 1:0;

	 if(stConverter.stDC.u8BUC_DC_OVERCurrent != u8TempByte)
	 {
	 	stConverter.stDC.u8BUC_DC_OVERCurrent = u8TempByte;

		if ((CurrentMenu == nBUCOVERI_MENU) && (TRUE != EditMode))
		{
		ValueUpdateFlag = TRUE;

		stMenuDisplay[CurrentMenu].pvfPrintMenu();  
		}

	 }

	 u8TempByte = stI2CREFMsg.u8Status & nLNB_OVER_CURRENT ? 1:0;
	 
	if(stConverter.stDC.u8LNB_DC_OVERCurrent != u8TempByte)
	{
		stConverter.stDC.u8LNB_DC_OVERCurrent = u8TempByte;
		
		if ((CurrentMenu == nLNBOVERI_MENU) && (TRUE != EditMode))
		{
			ValueUpdateFlag = TRUE;

			stMenuDisplay[CurrentMenu].pvfPrintMenu();  
		}

	}

	u8TempByte = stI2CREFMsg.u8Status & nEXT_REF ? 1:0;
	  
	if(stConverter.stDC.u8EXTREF != u8TempByte )
	{
		stConverter.stDC.u8EXTREF = u8TempByte;


		if (((CurrentMenu == nEXTREF_MENU) || (CurrentMenu == MENU2)) && (TRUE != EditMode))
		{
		ValueUpdateFlag = TRUE;

		stMenuDisplay[CurrentMenu].pvfPrintMenu();  
		}

	}  

	u16TempWord =  Util_u16ByteSwap(stI2CREFMsg.u16BUCCurrent);
	if(u16TempWord != stConverter.stDC.u16BUCCurrent )
	{
		stConverter.stDC.u16BUCCurrent = u16TempWord;

		if ((CurrentMenu == nBUCI_MENU) && (TRUE != EditMode))
		{
			ValueUpdateFlag = TRUE;

			stMenuDisplay[CurrentMenu].pvfPrintMenu();  
		}
	}


	u16TempWord = Util_u16ByteSwap(stI2CREFMsg.u16LNBCurrent);
	if(u16TempWord!= stConverter.stDC.u16LNBCurrent)
	{
		stConverter.stDC.u16LNBCurrent = u16TempWord;
		if ((CurrentMenu == nLNBI_MENU) && (TRUE != EditMode))
		{
			ValueUpdateFlag = TRUE;

			stMenuDisplay[CurrentMenu].pvfPrintMenu();  
		}		

	}

	u16TempWord =  Util_u16ByteSwap(stI2CREFMsg.u16BUCCurrentLimit);
	if(u16TempWord!= stConverter.stDC.u16BUCCurrentLimit)
	{
		stConverter.stDC.u16BUCCurrentLimit=u16TempWord;

	}


	u16TempWord =  Util_u16ByteSwap(stI2CREFMsg.u16LNBCurrentLimit);
	if(u16TempWord!= stConverter.stDC.u16LNBCurrentLimit)
	{
		stConverter.stDC.u16LNBCurrentLimit = u16TempWord;

	}


    return TRUE;
    
}

static BYTE SYS__u8UpdateLO()
{
BYTE u8TempByte = 0;
WORD u16TempWord = 0;
BOOL boReturn = FALSE; 
    
stI2CLOMsg.u8CtrlStatus&= nI2C_READ;
I2C_Send(I2C_LO_ADDR, (char*)&readflag, 1);
boReturn = I2C_Read(I2C_LO_ADDR, (char*)&stI2CLOMsg, sizeof(tstI2CMsg));

if(!boReturn)
return FALSE;

if(stI2CLOMsg.u8CtrlStatus & 0x04)  //bit2 is lo status
    {
        if(u8ExtLO == 0)
        {
            u8ExtLO = 1;
            if(stConverter.stUp.u8Lock == 1)
                Main_vLEDLO(ON);
            	Main_vLEDRX(ON);
        }
        
        
    }
else
    {
         if(u8ExtLO == 1)
        {
            u8ExtLO = 0;
            Main_vLEDLO(OFF);
            Main_vLEDRX(OFF);
        }
        
    }


//read bit 3 and bit 4 for band selection

	if((stI2CLOMsg.u8CtrlStatus & 0x08) && (stI2CLOMsg.u8CtrlStatus & 0x10))
	{
		u8LoBand = 3;
		u16LoFreq = 13250;

	}
	else if((stI2CLOMsg.u8CtrlStatus & 0x08) && !(stI2CLOMsg.u8CtrlStatus & 0x10))
	{
		u8LoBand = 2;
		u16LoFreq = 12750;

	}
	else if(!(stI2CLOMsg.u8CtrlStatus & 0x08) && (stI2CLOMsg.u8CtrlStatus & 0x10))
	{
		u8LoBand = 1;
		u16LoFreq = 12250;

	}
	else if(!(stI2CLOMsg.u8CtrlStatus & 0x08) && !(stI2CLOMsg.u8CtrlStatus & 0x10))
	{
		u8LoBand = 0;
		u16LoFreq = 11750;

	}


}




/* ValueUpdateFlag will force refresh LCD. it must be rechecked whether current page is relavant or else, refresh is not required */
/* Data strings should be re-organized */
/* JuZh: should consider only send to one module per cycle, or else waiting time is too long */
void UpdateStatus(void)
{
	static BYTE u8Index = 0;
	

	if(0 == u8Index)
        /* Module Up Converter*/
    	SYS__u8UpdateUpConverter();
	
	else if(1 == u8Index)	
	{
		/* Module Down Converter*/
		/* Do nothing since L-Band Up converter only */
	//	SYS__u8UpdateDownConverter();

		SYS__u8UpdateLO();
	}
	else if(2 == u8Index)
	    /* Module Dc Control*/
	    SYS__u8UpdateVOL();

	u8Index++;
	
	if(u8Index>=3)
		u8Index = 0;

}

