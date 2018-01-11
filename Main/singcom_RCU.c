#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "HardwareProfile.h"
#include "define.h"
#include <usart.h>
#include "p18f97j60.h"
#include "adc.h"
#include "delays.h"
#include "singcom.h"

unsigned char SW1_STAT;
unsigned char SW2_STAT;
unsigned char SWA_STAT;
unsigned char SWB_STAT;
unsigned char RL_STAT;
unsigned char AM_STAT;
unsigned char R_STAT;
unsigned char LNBA_STAT;
unsigned char LNBB_STAT;
unsigned char LNBC_STAT;
unsigned char PSU_STAT;

unsigned char SW1_STAT_Old=5;
unsigned char SW2_STAT_Old=5;
unsigned char SWA_STAT_Old=5;
unsigned char SWB_STAT_Old=5;
unsigned char RL_STAT_Old=5;
unsigned char AM_STAT_Old=5;
unsigned char R_STAT_Old=5;
unsigned char LNBA_STAT_Old=5;
unsigned char LNBB_STAT_Old=5;
unsigned char LNBC_STAT_Old=5;
unsigned char PSU_STAT_Old=5;

unsigned char SW1_SET=1;
unsigned char SW2_SET=2;
unsigned char SWA_SET=2;
unsigned char SWB_SET=1;
unsigned char RL_SET=0;
unsigned char AM_SET=0;
unsigned char R_SET=0;

unsigned char SW1_err=0;
unsigned char SW2_err=0;
unsigned char SWA_err=0;
unsigned char SWB_err=0;
unsigned char LNBA_err=0;
unsigned char LNBB_err=0;
unsigned char LNBC_err=0;

unsigned char SET_R_LCD=1;
unsigned char SET_AM_LCD=1;
unsigned char SET_SW1_LCD=1;
unsigned char SET_SW2_LCD=1;
unsigned char SET_SWA_LCD=1;
unsigned char SET_SWB_LCD=1;
unsigned char SET_LNBA_LCD=1;
unsigned char SET_LNBB_LCD=1;
unsigned char SET_LNBC_LCD=1;
unsigned char SET_PSU_LCD=1;

unsigned rom char Str_R_STAT1[]="main.R.val=1";
unsigned rom char Str_R_STAT0[]="main.R.val=0";
unsigned rom char Str_AM_STAT1[]="main.AM.val=1";
unsigned rom char Str_AM_STAT0[]="main.AM.val=0";

unsigned rom char Str_SW1_STAT1_1[]="main.SW1.picc0=1";
unsigned rom char Str_SW1_STAT1_2[]="main.SW1.picc1=3";
unsigned rom char Str_SW1_STAT1_3[]="main.SW1.val=1";
unsigned rom char Str_SW1_Refresh[]="ref main.SW1";

unsigned rom char Str_SW1_STAT2_1[]="main.SW1.picc0=1";
unsigned rom char Str_SW1_STAT2_2[]="main.SW1.picc1=3";
unsigned rom char Str_SW1_STAT2_3[]="main.SW1.val=0";

unsigned rom char Str_SW1_STAT3_1[]="main.SW1.picc0=2";
unsigned rom char Str_SW1_STAT3_2[]="main.SW1.picc1=2";
unsigned rom char Str_SW1_STAT3_3[]="main.SW1.val=0";

unsigned rom char Str_SW2_STAT1_1[]="main.SW2.picc0=1";
unsigned rom char Str_SW2_STAT1_2[]="main.SW2.picc1=3";
unsigned rom char Str_SW2_STAT1_3[]="main.SW2.val=0";
unsigned rom char Str_SW2_Refresh[]="ref main.SW2";

unsigned rom char Str_SW2_STAT2_1[]="main.SW2.picc0=1";
unsigned rom char Str_SW2_STAT2_2[]="main.SW2.picc1=3";
unsigned rom char Str_SW2_STAT2_3[]="main.SW2.val=1";

unsigned rom char Str_SW2_STAT3_1[]="main.SW2.picc0=2";
unsigned rom char Str_SW2_STAT3_2[]="main.SW2.picc1=2";
unsigned rom char Str_SW2_STAT3_3[]="main.SW2.val=0";

unsigned rom char Str_SWA_STAT1_1[]="main.SWA.picc0=1";
unsigned rom char Str_SWA_STAT1_2[]="main.SWA.picc1=3";
unsigned rom char Str_SWA_STAT1_3[]="main.SWA.val=0";
unsigned rom char Str_SWA_Refresh[]="ref main.SWA";

unsigned rom char Str_SWA_STAT2_1[]="main.SWA.picc0=1";
unsigned rom char Str_SWA_STAT2_2[]="main.SWA.picc1=3";
unsigned rom char Str_SWA_STAT2_3[]="main.SWA.val=1";

unsigned rom char Str_SWA_STAT3_1[]="main.SWA.picc0=2";
unsigned rom char Str_SWA_STAT3_2[]="main.SWA.picc1=2";
unsigned rom char Str_SWA_STAT3_3[]="main.SWA.val=0";

unsigned rom char Str_SWB_STAT1_1[]="main.SWB.picc0=1";
unsigned rom char Str_SWB_STAT1_2[]="main.SWB.picc1=3";
unsigned rom char Str_SWB_STAT1_3[]="main.SWB.val=1";
unsigned rom char Str_SWB_Refresh[]="ref main.SWB";

unsigned rom char Str_SWB_STAT2_1[]="main.SWB.picc0=1";
unsigned rom char Str_SWB_STAT2_2[]="main.SWB.picc1=3";
unsigned rom char Str_SWB_STAT2_3[]="main.SWB.val=0";

unsigned rom char Str_SWB_STAT3_1[]="main.SWB.picc0=2";
unsigned rom char Str_SWB_STAT3_2[]="main.SWB.picc1=2";
unsigned rom char Str_SWB_STAT3_3[]="main.SWB.val=0";

unsigned rom char Str_LNBA_STAT0[]="main.LNBA.picc=1";
unsigned rom char Str_LNBA_STAT1[]="main.LNBA.picc=2";
unsigned rom char Str_LNBA_Refresh[]="ref main.LNBA";

unsigned rom char Str_LNBB_STAT0[]="main.LNBB.picc=1";
unsigned rom char Str_LNBB_STAT1[]="main.LNBB.picc=2";
unsigned rom char Str_LNBB_Refresh[]="ref main.LNBB";

unsigned rom char Str_LNBC_STAT0[]="main.LNBC.picc=1";
unsigned rom char Str_LNBC_STAT1[]="main.LNBC.picc=2";
unsigned rom char Str_LNBC_Refresh[]="ref main.LNBC";

unsigned rom char Str_PSU_STAT0_1[]="main.P1_alm.val=0";
unsigned rom char Str_PSU_STAT0_2[]="main.P2_alm.val=0";
unsigned rom char Str_PSU_STAT1[]="main.P1_alm.val=1";
unsigned rom char Str_PSU_STAT2[]="main.P2_alm.val=1";


void init_singcom_RCU(void)
{
	ADCON1=0b00001010;


//ADCON2=;
//ADCON0=;
//Connector JC3
	TRISFbits.TRISF0=0;			//OCXO_ONOFF LATFbits.LATF0
	TRISCbits.TRISC0=1;			//IF_SW2_IND_A PORTCbits.RC0
	TRISCbits.TRISC1=1;			//IF_SW2_IND_B PORTCbits.RC1
	TRISFbits.TRISF3=1;			//IF_SW3_IND_A PORTFbits.RF3
	TRISFbits.TRISF4=1;			//IF_SW3_IND_B PORTFbits.RF4
	TRISFbits.TRISF5=1;			//RF_SW1_IND_A1 PORTFbits.RF5
	TRISFbits.TRISF6=1;			//RF_SW1_IND_A2 PORTFbits.RF6
	TRISHbits.TRISH4=1;			//RF_SW1_IND_B1 PORTHbits.RH4
	TRISHbits.TRISH5=1;			//RF_SW1_IND_B2 PORTHbits.RH5
	TRISHbits.TRISH6=1;			//RF_SW2_IND_A1 PORTHbits.RH6
	TRISHbits.TRISH7=1;			//RF_SW2_IND_A2 PORTHbits.RH7
//Connector JC1
	TRISJbits.TRISJ5=0;			//RF_SW1_A LATJbits.LATJ5
	TRISJbits.TRISJ0=0;			//RF_SW1_B LATJbits.LATJ0
	TRISJbits.TRISJ4=0;			//RF_SW2_A LATJbits.LATJ4
	TRISJbits.TRISJ1=0;			//RF_SW2_B LATJbits.LATJ1
	TRISBbits.TRISB3=0;			//IF_SW1_A LATBbits.LATB3
	TRISBbits.TRISB2=0;			//IF_SW1_B LATBbits.LATB2
	TRISBbits.TRISB1=0;			//IF_SW2_A LATBbits.LATB1
	TRISEbits.TRISE0=0;			//IF_SW2_B LATEbits.LATE0
	TRISEbits.TRISE1=1;			//RF_SW2_IND_B1 PORTEbits.RE1//
	TRISBbits.TRISB4=1;			//RF_SW2_IND_B2 PORTBbits.RB4//
	TRISBbits.TRISB5=1;			//IF_SW1_IND_A PORTBbits.RB5//
	TRISFbits.TRISF1=1;			//IF_SW1_IND_B PORTFbits.RF1//

//Connector JC2
	TRISHbits.TRISH0=0;			//ALM_A LATHbits.LATH0
	TRISEbits.TRISE2=0;			//ALM_B LATEbits.LATE2
	TRISEbits.TRISE3=0;			//ALM_C LATEbits.LATE3
	TRISEbits.TRISE4=0;			//ALM_PSU LATEbits.LATE4
	TRISEbits.TRISE5=0;			//IF_SW_A LATEbits.LATE5
	TRISEbits.TRISE6=0;			//RF_SW_1 LATEbits.LATE6
	TRISEbits.TRISE7=0;			//IF_SW_B LATEbits.LATE7
	TRISDbits.TRISD0=0;			//RF_SW_2 LATDbits.LATD0

	RF_SW1_A=0;
	RF_SW1_B=0;
	RF_SW2_A=0;
	RF_SW2_B=0;
	IF_SW1_A=0;
	IF_SW1_B=0;
	IF_SW2_A=0;
	IF_SW2_B=0;


}

void Check_SW_Status(void)
{
//check SWA status
	if ((IF_SW1_IND_A==0) &&(IF_SW1_IND_B==1)) //IF SW1 switch to LNBA
	{
		SWA_STAT=1;           // IF switch 1=part of SWA, pos 1
		if (SWA_SET==2) 
		{
			if (SWA_err>=3)
			{
				SWA_STAT=3;
			}
			else 
			{
				SWA_err++;
			}
		}
		else SWA_err=0;
	}
	else if ((IF_SW1_IND_A==1) &&(IF_SW1_IND_B==0)
		 && (IF_SW3_IND_A==0) &&(IF_SW3_IND_B==1))
	{
		SWA_STAT=2;
		if (SWA_SET==1) 
		{
			if (SWA_err>=3)
			{
				SWA_STAT=3;
			}
			else 
			{
				SWA_err++;
			}
		}
		else SWA_err=0;
	}
	else
	{
		if (SWA_err>=3)
		{
			SWA_STAT=3;
		}
		else 
		{
			SWA_err++;
		}
	}

//check SWB status
	if ((IF_SW2_IND_A==1) && (IF_SW2_IND_B==0))
	{
		SWB_STAT=2;     
		if (SWB_SET==1) 
		{
			if (SWB_err>=3)
			{
				SWB_STAT=3;
			}
			else 
			{
				SWB_err++;
			}			
		} 
		else SWB_err=0;      
	}
	else if ((IF_SW2_IND_A==0) &&(IF_SW2_IND_B==1)
		 && (IF_SW3_IND_A==1) &&(IF_SW3_IND_B==0))
	{
		SWB_STAT=1;
		if (SWB_SET==2) 
		{
			if (SWB_err>=3)
			{
				SWB_STAT=3;
			}
			else 
			{
				SWB_err++;
			}
		}
		else SWB_err=0;
	}
	else
	{
		if (SWB_err>=3)
		{
			SWB_STAT=3;
		}
		else 
		{
			SWB_err++;
		}
	}

//check SW1 status
	if ((RF_SW1_IND_A1==0) && (RF_SW1_IND_B1==0)
		&&	(RF_SW1_IND_A2==1) && (RF_SW1_IND_B2==1))
	{
		SW1_STAT=1;
		if (SW1_SET==2) 
		{
			if (SW1_err>=3)
			{
				SW1_STAT=3;
			}
			else 
			{
				SW1_err++;
			}
		}
		else SW1_err=0;
	}
	else if ((RF_SW1_IND_A1==1) && (RF_SW1_IND_B1==1)
		&&	(RF_SW1_IND_A2==0) && (RF_SW1_IND_B2==0))
	{
		SW1_STAT=2;
		if (SW1_SET==1) 
		{
			if (SW1_err>=3)
			{
				SW1_STAT=3;
			}
			else 
			{
				SW1_err++;
			}
		}
		else SW1_err=0;
	}
	else
	{
		if (SW1_err>=3)
		{
			SW1_STAT=3;
		}
		else 
		{
			SW1_err++;
		}
	}

//check SW2 status
	if ((RF_SW2_IND_A1==0) && (RF_SW2_IND_B1==0)
		&&	(RF_SW2_IND_A2==1) && (RF_SW2_IND_B2==1))
	{
		SW2_STAT=1;
		if (SW2_SET==2) 
		{
			if (SW2_err>=3)
			{
				SW2_STAT=3;
			}
			else 
			{
				SW2_err++;
			}
		}
		else SW2_err=0;
	}
	else if ((RF_SW2_IND_A1==1) && (RF_SW2_IND_B1==1)
		&&	(RF_SW2_IND_A2==0) && (RF_SW2_IND_B2==0))
	{
		SW2_STAT=2;
		if (SW2_SET==1) 
		{
			if (SW2_err>=3)
			{
				SW2_STAT=3;
			}
			else 
			{
				SW2_err++;
			}
		}
		else SW2_err=0;
	}
	else
	{
		if (SW2_err>=3)
		{
			SW2_STAT=3;
		}
		else 
		{
			SW2_err++;
		}
	}


//if switch status changed, send LCD
	if (SW1_STAT_Old!=SW1_STAT)
	{
		SET_SW1_LCD=1;
		SW1_STAT_Old=SW1_STAT;
	}
	if (SW2_STAT_Old!=SW2_STAT)
	{
		SET_SW2_LCD=1;
		SW2_STAT_Old=SW2_STAT;
	}
	if (SWA_STAT_Old!=SWA_STAT)
	{
		SET_SWA_LCD=1;
		SWA_STAT_Old=SWA_STAT;
	}
	if (SWB_STAT_Old!=SWB_STAT)
	{
		SET_SWB_LCD=1;
		SWB_STAT_Old=SWB_STAT;
	}

}

void Check_LNAPSU_Status(void)
//ADC_CH0:LNBA, ADC_CH1:LNBB, ADC_CH2:LNBC
{
	unsigned short LNBA_I, LNBB_I,LNBC_I,PSU1_V,PSU2_V;
	unsigned char temp;
	TRISAbits.TRISA0=1;
	TRISAbits.TRISA1=1;
	TRISAbits.TRISA2=1;
	TRISAbits.TRISA3=1;
	TRISAbits.TRISA5=1;
	OpenADC(ADC_FOSC_64 & ADC_RIGHT_JUST & ADC_20_TAD, ADC_CH0
	 & ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS ,10);
	Delay10TCYx(5);
	ConvertADC();
	while(BusyADC());
	LNBA_I=ReadADC();

	SetChanADC(ADC_CH1);
	Delay10TCYx(5);
	ConvertADC();
	while(BusyADC());
	LNBB_I=ReadADC();

	SetChanADC(ADC_CH2);
	Delay10TCYx(5);
	ConvertADC();
	while(BusyADC());
	LNBC_I=ReadADC();

	SetChanADC(ADC_CH3);
	Delay10TCYx(5);
	ConvertADC();
	while(BusyADC());
	PSU1_V=ReadADC();

	SetChanADC(ADC_CH4);
	Delay10TCYx(5);
	ConvertADC();
	while(BusyADC());
	PSU2_V=ReadADC();
	
//	CloseADC();
		
	if (LNBA_I>=677 & LNBA_I<=1016)
	{
		temp=0;
		LNBA_err=0;
	}
	else
	{
		LNBA_err++;
		if (LNBA_err>=10)
		{
			LNBA_err=10;
			temp=1;
		}
	}
	if (temp!=LNBA_STAT)
	{
		SET_LNBA_LCD=1;
	}
	LNBA_STAT=temp;

	if (LNBB_I>=677 & LNBB_I<=1016)
	{
		temp=0;
		LNBB_err=0;
	}
	else
	{
		LNBB_err++;
		if (LNBB_err>=10)
		{
			LNBB_err=10;
			temp=1;
		}
	}
	if (temp!=LNBB_STAT)
	{
		SET_LNBB_LCD=1;
	}
	LNBB_STAT=temp;

	if (LNBC_I>=677 & LNBC_I<=1016)
	{
		temp=0;
		LNBC_err=0;
	}
	else
	{
		LNBC_err++;
		if (LNBC_err>=10)
		{
			LNBC_err=10;
			temp=1;
		}
	}
	if (temp!=LNBC_STAT)
	{
		SET_LNBC_LCD=1;
	}
	LNBC_STAT=temp;

	if (PSU1_V>=400 & PSU2_V>=400) //reading 603
	{
		temp=0;
	}
	else if (PSU1_V<400)
	{
		temp=1;
	}
	else temp=2;
	if (temp!=PSU_STAT)
	{
		SET_PSU_LCD=1;
	}
	PSU_STAT=temp;
}

void Check_Other_Status(void)
{
	if (R_SET!=R_STAT)
	{
		R_STAT=R_SET;
		OCXO_ONOFF=1-R_STAT;
		SET_R_LCD=1;		
	}
	if (AM_STAT!=AM_SET)
	{
		AM_STAT=AM_SET;
		SET_AM_LCD=1;
	}
}

void Send_SW(void)
{
// for auto mode
	if (AM_STAT==0)
	{
		if ((LNBA_STAT==0)&&(LNBB_STAT==0))
		{
			SW1_SET=2;
			SW2_SET=1;
			SWA_SET=1;
			SWB_SET=2;
		}
		if (LNBA_STAT==1)
		{
			SW1_SET=1;
			SW2_SET=1;
			SWA_SET=2;
			SWB_SET=2;
		}
		if (LNBB_STAT==1)
		{
			SW1_SET=2;
			SW2_SET=2;
			SWA_SET=1;
			SWB_SET=1;
		}
	}

//set SW1
	if (SW1_STAT!=SW1_SET)
	{
		if (SW1_SET==1)
		{
			RF_SW1_B=0;
			RF_SW1_A=1;
		}
		else if (SW1_SET==2)
		{
			RF_SW1_A=0;
			RF_SW1_B=1;
		}
		SET_SW1_LCD=1;
	}

//set SW2
	if (SW2_STAT!=SW2_SET)
	{
		if (SW2_SET==1)
		{
			RF_SW2_B=0;		
			RF_SW2_A=1;
		}
		else if (SW2_SET==2)
		{
			RF_SW2_A=0;
			RF_SW2_B=1;
		}
		SET_SW2_LCD=1;
	}



	if (SWA_SET==2 & SWB_SET==1)
	{
		SWA_SET=1;
	}

//set SWA

	if (SWA_STAT!=SWA_SET)
	{
		if (SWA_SET==1)
		{	
			IF_SW1_B=0;
			IF_SW1_A=1;
		}
		else if (SWA_SET==2)
		{
			IF_SW1_A=0;
			IF_SW1_B=1;
		}
		SET_SWA_LCD=1;
	}

//set SWB
	if (SWB_STAT!=SWB_SET)
	{
		if (SWB_SET==1)
		{
			IF_SW2_B=0;
			IF_SW2_A=1;
		}
		else if (SWB_SET==2)
		{
			IF_SW2_A=0;
			IF_SW2_B=1;
		}
		SET_SWB_LCD=1;
	}
}


void Send_CTL(void)
{
// if auto/manual status changes need to refresh LCD
	if (AM_SET!=AM_STAT)
	{
		AM_STAT=AM_SET;
		SET_AM_LCD=1;
	}
	if (R_STAT!=R_SET)
	{
		R_STAT=R_SET;
		OCXO_ONOFF=1-R_STAT;
		SET_R_LCD=1;
	}
}

void Send_LED(void)
{
	ALM_A=LNBA_STAT;
	ALM_B=LNBB_STAT;
	ALM_C=LNBC_STAT;
	if (PSU_STAT!=0)
	{
		ALM_PSU=1;
	}
	else ALM_PSU=0;
	if (SW1_STAT==3 | SWA_STAT==3)
	{
		ALM_A=1;
		ALM_C=1;
	}
	if (SW2_STAT==3 | SWB_STAT==3)
	{
		ALM_B=1;
		ALM_C=1;
	}
	if (SW1_STAT==2)
	{
		RF_SW_1=1;
	}
	else RF_SW_1=0;
	if (SW2_STAT==1)
	{
		RF_SW_2=1;
	}
	else RF_SW_2=0;
	if (SWA_STAT==1)
	{
		IF_SW_A=1;
	}
	else IF_SW_A=0;
	if (SWB_STAT==2)
	{
		IF_SW_B=1;
	}
	else IF_SW_B=0;
}

void Send_LCD_Data(rom char *str)
{
}

void Send_Status_To_PC(void)
{
}


void Send_LCD2(void)
{
}


void delay_RF_SW(void)
{
	Delay10KTCYx(255);
}

void delay_IF_SW(void)
{
	Delay10KTCYx(255);
	Delay10KTCYx(255);
}

