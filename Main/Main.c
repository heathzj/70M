/*********************************************************************

 *********************************************************************
 * FileName:        MainDemo.c
 * Dependencies:    TCPIP.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 ********************************************************************/

#define THIS_IS_STACK_APPLICATION


#if defined(__18F97J60) || defined(_18F97J60)
// Include all headers for any enabled TCPIP Stack functions
#include "TCPIP Stack/TCPIP.h"
#endif

// Include functions specific to this stack application
#include "singcom.h"   //*******************************************************************************
#include "Main.h"
#include "define.h"
#include "delays.h"
#include "Global.h"
#include "timers.h"
#include "list.h"
#include "DualUART.h"

#include "Uart.h"

#include <i2c.h>
#include "i2c_c1.h"
#include "oled_c1.h"
#include "Util.h"

#define nMINUTE 60


//*******************************************************************************************************
extern char Uart0PCCmdBuf[32];
extern BYTE Uart1ReadLCDCmd;
extern BYTE Uart0ReadPCCmd;
extern BYTE Uart0PCCmdBufCount;
//**********************************************************************************************************




#if 0
const char CompanyString1[40] = {"                  SINGCOM               "};
const char CompanyString2[40] = {"               DOWN CONVERTER           "};
const char menutextstring1[] = {"[CVT. 1] "};
const char menutextstring2[] = {"[CVT. 2] "};
const char menutextstring3[] = {"[DEVICE INFO] "};
const char menutextstring4[] = {"LO "};
const char menutextstring5[] = {"RF "};
const char menutextstring6[] = {"LO "};
const char menutextstring7[] = {"Atten. "};
const char menutextstring8[] = {"IF "};
#endif
char FirmwareVersion[4] = {"100"};




tstUpDownConverter stConverter;



extern unsigned char LastMenu;
extern unsigned char CurrentMenu;




unsigned char SecondCounter = 0, MinuteCounter = 0;




// Declare AppConfig structure and some other supporting stack variables
unsigned char HardwareWDT = 1;

//#define UART_TEST // uart testing

IP_ADDR		MyStaticIPAddr;
unsigned char ostart,oend,ctemp;

#pragma udata grp5
APP_CONFIG AppConfig;

#pragma udata
unsigned char Read2[2][4];

#pragma udata gpr8
systeminfo_t systeminfo1;

#pragma udata grp10
systeminfo_t2 systeminfo2;


static TICK webPass_tmr = 0, lcd_timer = 0, keypad_tmr = 0,tiDisplay_tmr=0;

static void DRI__vEnableGlobalInt();
static void DRI__vHitWatchDog(void) ; 
static void DRI__vEnableGlobalInt();
static void DRI__vConfigSPI();

static void SYS__vStatusTask();
static void SYS__vLcdDisplayTask(void);
static void SYS__vLcdKeyPadTask(void);
static BYTE SYS__u8InitData(void);

static void HTTP_vClearWebPassword();

void main(void);


//#pragma code // Return to default code section

//#define ClearWatchDog()  { _asm CLRWDT _endasm }


/* Called in Main function */
static void DRI__vHitWatchDog(void)  
{ 
	// clear MCU watchdog 
	//ClearWatchDog();
_asm 
	CLRWDT 
_endasm

	// clear hardware watch dog, toggle RA3
//	if (HardwareWDT == 1)
	{
//		WDI_FLAG = 0;
//		HardwareWDT = 0;
	}
//	else
	{
//		WDI_FLAG = 1;
//		HardwareWDT = 1;
	}
}

//********************* FUNCTIONS ************************



/* only used in pic18f8722 */
#if 0 
static void DRI__vINT_OFF(void)
{
//	INTCONbits.GIEL = 0;
//	INTCONbits.GIEH = 0;		
//	INTCONbits.GIE = 0;
}

static void DRI__vINT_ON(void)
{
//	INTCONbits.GIEL = 1;
//	INTCONbits.GIEH = 1;		
//	INTCONbits.GIE = 1;
}
#endif


/* Enable Global interrupts */
static void DRI__vEnableGlobalInt()
{
	INTCONbits.GIEL=1;
	INTCONbits.GIEH = 1;		
	INTCONbits.GIE = 1;		//Enable global interrupts
	INTCONbits.PEIE = 1;	//Enable peripheral interrupts

}

/* Configure SPI bits and registers */
static void DRI__vConfigSPI()
{
	SCL_TRIS = 0;
	SDA_TRIS = 0;

	SSP2CON1bits.SSPEN = 0;
	SSP2STATbits.SMP = 1;
	SSP2CON1 &= 0xF0;
	SSP2CON1 |= 0x08;


}

/* Update System status from sub modules */
/* Consider to change this task to be receive interrupt triggered with update values to reduce process time*/
static void SYS__vStatusTask()
{
    
    /* Status update from Module MCUs and blick LCD */
   
    /* SecondCounter actually update every 1/3 second = 330ms*/
    if ((TickGet() - lcd_timer) >= (TICK_SECOND / 2))
    {
        /* Update status */
        UpdateStatus(); /* A time consuming task */
        lcd_timer = TickGet();
       
    }    
       
}


/* For blinking display Only*/

static void SYS__vLcdBlinkTask(void) 
{
	if ((TickGet() - tiDisplay_tmr) >= (TICK_SECOND /3 ))
		{
			
			
			tiDisplay_tmr = TickGet();
			SecondCounter++;
	
			/* Blinking effect: dislay text alternatively for odd and even seconds*/
			/* TBD can be improved here to only update blinking part , keep others static */
			// if (((SecondCounter % 4) == 1)||((SecondCounter % 4) == 2)) /* Blink 0.33s */
			// {
				// PrintLCD();
			// }
			// else
			// {
				// PrintBlinkLCD();
			// }
                /* Refresh LCD screen */
            if (ValueUpdateFlag == TRUE) /* if there is data update from I2C, whole page content has to be updated */
            {
                ValueUpdateFlag = FALSE;

                PrintNewValue();
            }
            else /* if no data update, just toggle the blink of value/'  ', or update the edit cursor position */
            {
                PrintBlinkMenuText(); 
            }
      

            

			if(SecondCounter >= nMINUTE) /* Reset from 0 */
				SecondCounter = 0;
				
			
		}	 
		


}

#if 1

/* For key processing and Menu Update*/
static void SYS__vLcdKeyPadTask(void)
{
    
    /* 1. Key press handling */
        /* KeyPressedFlag = true & PressedKey is set in ISR.c -> LowISR */
    if ((KeyPressedFlag == TRUE) && (PressedKey != NULL))
    {

#if 0
        /* There is not the very first time of key pressing */
        if (FirstPressKey == FALSE)
        {
            /* The previous handling and t2 happened  1/10 second = 100 ms before, must re-check */
            if ((TickGet() - keypad_tmr) >= (TICK_SECOND / 10))
            {
                KeyProcessing();
            }
        }
        /* This is the first time of keypress after start up, t2 is 0 in beginning */
        else
#endif	
        {
            KeyProcessing();
        }
        
        keypad_tmr = TickGet();
		
 //       FirstPressKey = FALSE; /* This is not the 1st key press */
        KeyPressedFlag = FALSE; /* Clear KeyPressedFlag from LowISR */
    }

        
         
    /* 2. Menu page update */ 
    /* Current Menu from KeyProcessing diffs from previous menu recorded,refresh is required */
    if (CurrentMenu != LastMenu)
    {
        RefreshFlag = TRUE;
        LastMenu = CurrentMenu;
    }
    
    /* Menu changed, Refresh whole LCD screen */
    if (RefreshFlag == TRUE)
    {
        RefreshFlag = FALSE;
        LCD_u8UpdateDisplayContent();
        PrintLCDWholePage();
    }
    
     /* Got New data set from keypad, Refresh only Data */
    else if(ValueUpdateFlag == TRUE)
    {
        ValueUpdateFlag = FALSE;
        PrintNewValue();
        
    }
    
      /* Up down ky pressed, Refresh only Edit position */
    else if(EditUpdateFlag == TRUE) /*Update only the Edit cursor position */
    {
        EditUpdateFlag = FALSE;
        PrintEditPosition();
    }          

        
          
}
#endif

#if 0
static void SYS__vLcdKeyPadTask(void)
{
    
    /* 1. Key press handling */
        /* KeyPressedFlag = true & PressedKey is set in ISR.c -> LowISR */
    if ((KeyPressedFlag == TRUE) && (PressedKey != NULL))
    {
       
        KeyProcessing();
       		
        FirstPressKey = FALSE; /* This is not the 1st key press */
        KeyPressedFlag = FALSE; /* Clear KeyPressedFlag from LowISR */
    }

        
        
    /* 2. Menu page update */ 
    /* Current Menu from KeyProcessing diffs from previous menu recorded,refresh is required */
    if (CurrentMenu != LastMenu)
    {
        RefreshFlag = TRUE;
        LastMenu = CurrentMenu;
    }
    
    /* Refresh LCD screen */
    if (RefreshFlag == TRUE)
    {
        RefreshFlag = FALSE;
        LCD_u8UpdateDisplayContent();
        PrintLCDWholePage();
    }
    
    if(ValueUpdateFlag == TRUE)
    {
        ValueUpdateFlag = FALSE;
        PrintNewValue();
        
    }
    
    if(EditUpdateFlag == TRUE) /*Update only the Edit cursor position */
    {
        EditUpdateFlag = FALSE;
        PrintEditPosition();
    }        
          
}
#endif


/* Flag to be used in HTTP Password Page */
static void HTTP_vClearWebPassword()
{
    
    //schedule task to clear set password result
    if (TickGet() - webPass_tmr >= TICK_SECOND*3)
    {
        webPass_tmr = TickGet();
        webpassinfo.count++;  
        if (webpassinfo.count == 2) 
        { 	   
            webpassinfo.setpass = others; 
            webpassinfo.count = 0;
        }
    }

    
}

static BYTE SYS__u8InitData(void)
{
	stConverter.stUp.u8AlarmStatus = 0;
	stConverter.stDown.u8AlarmStatus = 0;

	stConverter.stUp.u8Lock = 0;
	stConverter.stDown.u8Lock = 0;

	stConverter.stUp.u16Atten= 0;
	stConverter.stDown.u16Atten= 0;	

	stConverter.stUp.u8OutputPower= 30;
	stConverter.stDown.u8OutputPower= 30;

	stConverter.stUp.i16OutputPower= -30;
	stConverter.stDown.i16OutputPower= -30;	

	stConverter.stUp.u32OutputFreq= 950000;
	stConverter.stDown.u32InputFreq= 950000;

	stConverter.stUp.u8ALC = FALSE;
	stConverter.stDown.u8ALC = FALSE;

	stConverter.stUp.u8Mute= FALSE;
	stConverter.stDown.u8Mute= FALSE;


	stConverter.stDC.u8LNB_DC_ONOFF= FALSE;
	stConverter.stDC.u8BUC_DC_ONOFF= FALSE;

	stConverter.stDC.u8LNB_REF_ONOFF= FALSE;
	stConverter.stDC.u8BUC_REF_ONOFF= FALSE;

	stI2CUCMsg.u8CtrlStatus= 0;
	stI2CUCMsg.unRfFreq.u32Freq = 950000;
	stI2CUCMsg.unAtten.u16Atten = 0;
	stI2CUCMsg.u16RdPower = 30;
	stI2CUCMsg.u8CtrlStatus = 0x00 | nLOCK; /* Lo Lock, ALC and Mute off */

	stI2CDCMsg.u8CtrlStatus= 0;
	stI2CDCMsg.unRfFreq.u32Freq = 950000;
	stI2CDCMsg.unAtten.u16Atten = 0;
	stI2CDCMsg.u16RdPower = 30;	
	stI2CDCMsg.u8CtrlStatus = 0x00 | nLOCK; /* Lo Lock, ALC and Mute off */


	stI2CREFMsg.u8Status= 0;
	stI2CREFMsg.u16BUCCurrent = 0;
	stI2CREFMsg.u16LNBCurrent = 0;
	stI2CREFMsg.u16BUCCurrentLimit = 0;
	stI2CREFMsg.u16LNBCurrentLimit = 0;


	
	stConverter.stDC.u8EXTREF = 0;
	stConverter.stDC.u8BUC_DC_ONOFF = 0;
	stConverter.stDC.u8LNB_DC_ONOFF = 0;
	stConverter.stDC.u8BUC_REF_ONOFF= 0;
	stConverter.stDC.u8LNB_REF_ONOFF= 0;

	stConverter.stDC.u8BUC_DC_OVERCurrent = 0;

	stConverter.stDC.u8LNB_DC_OVERCurrent = 0;

	stConverter.stDC.u16BUCCurrent = 0;

	stConverter.stDC.u16LNBCurrent = 0;	

	stConverter.stDC.u16BUCCurrentLimit= 0;

	stConverter.stDC.u16LNBCurrentLimit= 0;		

		
}


void main(void)
{
	WORD tempWORD;
	float fAtt = 0;

	
#if 0 //test code
	
	SHORT i8Temp;
	WORD u16Temp;
	SHORT i16Temp = 10;

	char i8Temp2;
	WORD u16Temp2;
	char i8Temp3;
	WORD u16Temp3;
	char acTem[10] = "-30";
	char acTem2[10] = "+13";
	char acTem3[10] = "24";

					//tempWORD = stI2CUCMsg.u16RdPower;
	
					stConverter.stUp.i16OutputPower =-5;
	
	
					sprintf(sUCPower,"%+03d dB",stConverter.stUp.i16OutputPower);

					stConverter.stUp.i16OutputPower =12;
	
	
					sprintf(sUCPower,"%+03d dB",stConverter.stUp.i16OutputPower);


					stConverter.stUp.i16OutputPower =0;
	
					if ((stConverter.stUp.i16OutputPower<0)&&(stConverter.stUp.i16OutputPower>-1))
					{
						sprintf(sUCPower,"-%02d dB",stConverter.stUp.i16OutputPower);
					}
					else
					{
						sprintf(sUCPower,"%+03d dB",stConverter.stUp.i16OutputPower);
					}
					Nop();


					sprintf(AttenString2,"%02d.%1d dB",(int)fAtt, (int)(fAtt*10) %10  );
					Nop();

					fAtt = 2.3;
					sprintf(AttenString2,"%02d.%1d dB",(int)fAtt, (int)(fAtt*10) %10 );
					Nop();

					fAtt = 12.5;
					sprintf(AttenString2,"%02d.%1d dB",(int)fAtt,(int)(fAtt*10) %10 );
					Nop();

stConverter.stUp.u32OutputFreq = 1234567;
	sprintf(RFFreqString1,"%04ld.%03ldMHz",(DWORD)(stConverter.stUp.u32OutputFreq/1000),(DWORD)(stConverter.stUp.u32OutputFreq%1000) );	
     	Nop();

stConverter.stUp.u32OutputFreq = 1234;
	sprintf(RFFreqString1,"%04ld.%03ldMHz",stConverter.stUp.u32OutputFreq/1000,stConverter.stUp.u32OutputFreq%1000 );	
    		Nop();

//sscanf();

	i8Temp = Util_u8String2int8((char*)acTem);

	u16Temp = (	i8Temp *10 + 500);

	i8Temp2 = Util_u8String2int8((char*)acTem2);

	u16Temp2 = (i8Temp2 *10 + 500);

	i8Temp3 = Util_u8String2int8((char*)acTem3);

	u16Temp3 = (i8Temp3 *10 + 500);

	
#endif	

	// Initialize application specific hardware
	InitializeBoard();

	OLED_vSetKepad();  /* Set OLED Keypad  io directions */

	DRI__vConfigSPI(); /* Configure SPI bits and registers */
	
	OLED_vSetIO(); /* Set OLED control  io directions */

	Main_vLEDInit(); /* Set LED bits on main panel */
    
	SYS__u8InitData();
	
	Initial_LCD();
    
	InitalizeMenu();
    
	DisplayCompanyMenu();
	PrintCompanyLCD();

	DelayMs(1000);

	LCD_u8UpdateDisplayContent();
	DelayMs(300);
	PrintLCDWholePage();
    
	//DelayMs(200);

	RCONbits.IPEN=1;	// yt: should enable IPEN before GIE

    TickInit();

	DRI__vEnableGlobalInt();

	Main_vLEDInit();





#if defined(STACK_USE_MPFS) || defined(STACK_USE_MPFS2)
	MPFSInit();
#endif

	// Initialize Stack and application related NV variables into AppConfig.
	InitAppConfig();

	InitData();

    StackInit();

	// init I2C, 
	// set Converter A LO Frequency, Attenuation; 
	// set Converter B LO Frequency, Attenuation;

//	SetDefaultValue();

	OLED_vEnableInterrupt();/* Set OLED key interrupt bits */



	while(1)
    {
        /**
            Task priority:          Time:       Tick Period:                    Trigger:
            
            0 SYS__vLcdKeyPadTask     Long        2nd Check: TICK_SECOND/10       Interrupt(KeyPressedFlag)
            1 StackTask               Long        NULL                            Receiver INT
            2 SYS__vStatusTask        Long        TICK_SECOND/3                   Timer   
            2 StackApplications       Long        NULL                            Receiver INT
            3 SYS__vLcdBlinkTask      Middle      TICK_SECOND                     Timer
            4 HTTP_vClearWebPassword  Short       TICK_SECOND*3                   Timer
        **/

        /* If KeyPressedFlag == TRUE */
        SYS__vLcdKeyPadTask();
		
	


 
		 /* Run ethernet stack task only if PHY is connected */
		 if(MACIsLinked())
		 {
			 /* TCP/IP stack task */
			 StackTask();	
			 
			 /* This tasks invokes each of the core stack application tasks */
			 StackApplications(); 
		 }
        
        /* Run lower priority task only if Keypad is not in use */
       // if( TRUE != KeyPressedFlag )
        {

            SYS__vLcdBlinkTask();
            
            SYS__vStatusTask();

            HTTP_vClearWebPassword();

        }

#if defined(STACK_USE_SNMP_SERVER) && !defined(SNMP_TRAP_DISABLED)
	/*	snmp_trap_task(); */  /* SNMP is not used in this version */
#endif 

		DRI__vHitWatchDog();
    }
}



