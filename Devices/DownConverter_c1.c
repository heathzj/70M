#include "define.h"
#include "Global.h"

#include "oled_c1.h"
#include "string.h"
#include "Util.h"


void DownCvt_vPrintFreq(void)
{
	strncpy(LCDPrintBuffer[1], RFFreqString2,sizeof(RFFreqString2));	
}


void DownCvt_vPrintPower(void)
{

	strncpy(LCDPrintBuffer[1], sDCPower,sizeof(sDCPower));

}


void DownCvt_vPrintStPwr(void)
{
	strncpy(LCDPrintBuffer[1], sDNC_StPwr,sizeof(sDNC_StPwr));
}

void DownCvt_vPrintLo(void)
{

	if (stConverter.stDown.u8AlarmStatus == 1)
	{
		strncpy(LCDPrintBuffer[1], LOStatusString1,sizeof(LOStatusString1));
	}
	else
	{
		strncpy(LCDPrintBuffer[1], LOStatusString2,sizeof(LOStatusString2));
	}

}

void DownCvt_vPrintAttn(void)
{

	strncpy(LCDPrintBuffer[1], AttenString2,sizeof(AttenString2));

}

void DownCvt_vPrintALC(void)
{
	strncpy(LCDPrintBuffer[1], sALCb,sizeof(sALCb));

}



void DownCvt_vPrintMute(void)
{	
	if(stConverter.stDown.u8Mute==1)
		strncpypgm2ram(sMuteb,"ENABLED ",8);
	else
		strncpypgm2ram(sMuteb,"DISABLED",8);

	strncpy(LCDPrintBuffer[1], sMuteb,sizeof(sMuteb));	  
}



void DownCvt_vSendI2C()
{
	stI2CDCMsg.u16GainCompenVale = 0xFFFF; /* Don't write tables */
	SetI2C(MODULE1);

}

   
 

void DownCvt_vSetFreq(void)
 {
    DWORD tempDWORD = 0;
    float fFreq = 0;
    
    fFreq = Util_u8String2NFloat((char*)&LCDPrintBuffer[1][0]);
    tempDWORD = (DWORD)(fFreq * 1000.0f);// should deduct 950 000? 950M ~ 2150M
	 
	 if ((tempDWORD != stConverter.stDown.u32InputFreq) && (tempDWORD <= MAXRFFREQ) && (tempDWORD >= MINRFFREQ))
	 {
		// stConverter.stDown.u32InputFreq = tempDWORD;
		 stI2CDCMsg.unRfFreq.u32Freq = Util_u16DWORDSwap(tempDWORD);
		 strncpy(RFFreqString2 ,LCDPrintBuffer[1], sizeof(RFFreqString2) );
         
		 DownCvt_vSendI2C();
	 }
 }

 void DownCvt_vSetAttn(void)
 {
  WORD tempWORD = 0; 

  	 if ((stConverter.stDown.u8ALC != STATUS_OFF))
		 return;
  
	 tempWORD = LCDPrintBuffer[1][0] - '0';
	 tempWORD = ((WORD)(tempWORD * 10)) + ((WORD)LCDPrintBuffer[1][1] - '0');
	 tempWORD = ((WORD)(tempWORD * 10)) + ((DWORD)LCDPrintBuffer[1][3] - '0');
     
      /* tempWORD is atten * 10 */
	 if ((tempWORD != stConverter.stDown.u16Atten) && (tempWORD <= MAXATTEN) && (tempWORD >= MINATTEN))
	 {
		 //stConverter.stDown.u16Atten = tempWORD;
		 stI2CDCMsg.unAtten.u16Atten= Util_u16ByteSwap(tempWORD);
		 memcpy(AttenString2 ,LCDPrintBuffer[1], sizeof(AttenString2) );
	
		 DownCvt_vSendI2C();
	 }
 }

 void DownCvt_vSetPower(void)
 {
/*Disabled and moved to 	DownCvt_vSetStPwr */		
  					 
 }

 void DownCvt_vSetStPwr(void)
{
	 BYTE u8TempByte =0;
	 float fTemp;
	 SHORT i16Temp;
	 WORD u16Temp;
	 

	 
	 if ((stConverter.stDown.u8ALC != STATUS_ON))
		 return;

	 
	 fTemp = Util_u8String2Float(LCDPrintBuffer[1]);
	 
	 u16Temp = (WORD)(fTemp *10 + 500);


	 if ((u16Temp!= stConverter.stDown.u16SetPwr) && (u16Temp <= MAXPOWER) && (u16Temp >= MINPOWER))
	 {
		 stConverter.stDown.u16SetPwr = u16Temp;
		 stConverter.stDown.fSetPwr= fTemp;
		 //shared 16bits of att and wtpwr
		 stI2CDCMsg.unAtten.u16Atten = Util_u16ByteSwap(u16Temp);

		 memcpy(sDNC_StPwr,LCDPrintBuffer[1], sizeof(sDNC_StPwr) );

		 
		 DownCvt_vSendI2C();
	 }	



}

 void DownCvt_vSetALC(void)
 {
	 BYTE u8TempByte =0;
	 
	 u8TempByte = LCD__u8GetOnOff();
	 
	 strncpy(sALCb,LCDPrintBuffer[1], sizeof(sALCb) );
	 
	 if(u8TempByte==0)
	 {
		 stConverter.stDown.u8ALC = OFF;
		 stI2CDCMsg.u8CtrlStatus |= nAGC_OFF;//0x02
	 }
	 else if(u8TempByte==1)
	 {
		 stConverter.stDown.u8ALC = ON;
		 stI2CDCMsg.u8CtrlStatus &= nAGC_ON;//0xFD	 
	 }	 
	 
	 DownCvt_vSendI2C();
	 

 }

 void DownCvt_vSetMute(void)
 {

    BYTE u8TempByte =0;


	if(!memcmppgm2ram(LCDPrintBuffer[1],"ENABLED",7))
		u8TempByte = 1;
	else if (!memcmppgm2ram(LCDPrintBuffer[1],"DISABLED",8))
		u8TempByte = 0;

    if(u8TempByte==0) 
    {
    	stConverter.stDown.u8Mute = 0;
        strncpy(sMuteb,LCDPrintBuffer[1], sizeof(sMuteb) );	
		stI2CDCMsg.u8CtrlStatus  &= nRX_DISABLE;

        DownCvt_vSendI2C();

		//Main_vLEDRX(u8TempByte);  //zj disable for Lband
    }
	 else if(u8TempByte==1) 
    {
    	stConverter.stDown.u8Mute = 1;
        strncpy(sMuteb,LCDPrintBuffer[1], sizeof(sMuteb) );	
		stI2CDCMsg.u8CtrlStatus |= nRX_ENABLE;

        DownCvt_vSendI2C();

		//Main_vLEDRX(u8TempByte);  //zj disable for Lband
    }	 

}

