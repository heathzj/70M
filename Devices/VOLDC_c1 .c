#include "define.h"
#include "Global.h"

#include "oled_c1.h"
#include "string.h"
#include "Util.h"


void VOLCTRL_vPrint18V(void)
{
	strncpy(LCDPrintBuffer[1], s18VDC,3);

	 
}


void VOLCTRL_vPrint24V(void)
{

	
	strncpy(LCDPrintBuffer[1], s24VDC,3);

}
void VOLCTRL_vPrintLNBREF(void)
{
	strncpy(LCDPrintBuffer[1], sLNBREF,3);

}

void VOLCTRL_vPrintBUCREF(void)
{

	strncpy(LCDPrintBuffer[1], sBUCREF,3);

}

void VOLCTRL_vPrintEXTREF(void)
{

	if(stConverter.stDC.u8EXTREF  == 1)//ext
		strncpypgm2ram(LCDPrintBuffer[1], "External",8);
	else
		strncpypgm2ram(LCDPrintBuffer[1], "Internal",8);


}

void VOLCTRL_vPrintBUCI(void)
{
	char acTemp[20];
	
	sprintf(acTemp,"%d mA",stConverter.stDC.u16BUCCurrent);
	
	strncpy(LCDPrintBuffer[1], acTemp,sizeof(acTemp));


}
void VOLCTRL_vPrintLNBI(void)
{
		char acTemp[20];

		sprintf(acTemp,"%d mA",stConverter.stDC.u16LNBCurrent);
	
		strncpy(LCDPrintBuffer[1], acTemp,sizeof(acTemp));


}

void VOLCTRL_vPrintBUCAlm(void)
{

	if(stConverter.stDC.u8BUC_DC_OVERCurrent == 1)//overcurrent
		strncpypgm2ram(LCDPrintBuffer[1], "Alarm",5);
	else
		strncpypgm2ram(LCDPrintBuffer[1], "OK",2);


}
void VOLCTRL_vPrintLNBAlm(void)
{


	if(stConverter.stDC.u8LNB_DC_OVERCurrent == 1)//overcurrent
		strncpypgm2ram(LCDPrintBuffer[1], "Alarm",5);
	else
		strncpypgm2ram(LCDPrintBuffer[1], "OK",2);


}


void VOLCTRL_vSendI2C()
{
	stI2CREFMsg.u16BUCCurrentLimit = 0xffff;
	
	stI2CREFMsg.u16LNBCurrentLimit = 0xffff;

	SetI2C(MODULE2);

}


void VOLCTRL_vSet18V(void)
{
	BYTE u8TempByte =0;

	  u8TempByte = LCD__u8GetOnOff();
	  if(LCD__u8UpdateToModule(&stConverter.stDC.u8LNB_DC_ONOFF,&u8TempByte,nLNB_DC_ON,&stI2CREFMsg.u8Status))
	  {
		  strncpy(s18VDC,LCDPrintBuffer[1], sizeof(s18VDC) ); 

		  VOLCTRL_vSendI2C();
	  }

  }

 
 void VOLCTRL_vSet24V(void)
 {
 	BYTE u8TempByte =0;
	
 	  u8TempByte = LCD__u8GetOnOff();

	  if(LCD__u8UpdateToModule(&stConverter.stDC.u8BUC_DC_ONOFF,&u8TempByte,nBUC_DC_ON,&stI2CREFMsg.u8Status))
	  {
		  strncpy(s24VDC,LCDPrintBuffer[1], sizeof(s24VDC) ); 


		  VOLCTRL_vSendI2C();
	  }
  }

 void VOLCTRL_vSetLNBREF(void)
{
	 BYTE u8TempByte =0;
	 
	   u8TempByte = LCD__u8GetOnOff();
	 
	   if(LCD__u8UpdateToModule(&stConverter.stDC.u8LNB_REF_ONOFF,&u8TempByte,nLNB_REF_ON,&stI2CREFMsg.u8Status))
	   {
		   strncpy(sLNBREF,LCDPrintBuffer[1], sizeof(sLNBREF) ); 
	 
	 
		    VOLCTRL_vSendI2C();
	   }

}

 void VOLCTRL_vSetBUCREF(void)
{
	 BYTE u8TempByte =0;
	 
	   u8TempByte = LCD__u8GetOnOff();
	 
	   if(LCD__u8UpdateToModule(&stConverter.stDC.u8BUC_REF_ONOFF,&u8TempByte,nBUC_REF_ON,&stI2CREFMsg.u8Status))
	   {
		   strncpy(sBUCREF,LCDPrintBuffer[1], sizeof(sBUCREF) ); 
	 
	 
		   VOLCTRL_vSendI2C();
	   }

}

  void VOLCTRL_vClearBUCAlm(void)
{
	
	if(!memcmppgm2ram(LCDPrintBuffer[1],"OK",2))
	  {
		 stConverter.stDC.u8BUC_DC_OVERCurrent == 0; // clear alm
		 stI2CREFMsg.u8Status &= (~nBUC_OVER_CURRENT);
		VOLCTRL_vSendI2C();
	  }
	
}

  void VOLCTRL_vClearLNBAlm(void)
{
	  if(!memcmppgm2ram(LCDPrintBuffer[1],"OK",2))
		{
		   stConverter.stDC.u8LNB_DC_OVERCurrent == 0; // clear alm
		   stI2CREFMsg.u8Status &= (~nLNB_OVER_CURRENT);
		  VOLCTRL_vSendI2C();
		}

}

