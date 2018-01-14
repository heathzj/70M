#include "define.h"
#include "Global.h"

#include "oled_c1.h"
#include "string.h"
#include "Util.h"


extern WORD u16LoFreq;
extern WORD u8LoBand;


void UpCvt_vPrintFreq(void)
{
	strncpy(LCDPrintBuffer[1], RFFreqString1,sizeof(RFFreqString1));	
}


void UpCvt_vPrintPower(void)
{

	strncpy(LCDPrintBuffer[1], sUCPower,sizeof(sUCPower));

}

void UpCvt_vPrintStPwr(void)
{
	strncpy(LCDPrintBuffer[1], sUPC_StPwr,sizeof(sUPC_StPwr));

}


void UpCvt_vPrintLo(void)
{

	if (stConverter.stUp.u8AlarmStatus == 1)
	{
		strncpy(LCDPrintBuffer[1], LOStatusString1,sizeof(LOStatusString1));
	}
	else
	{
		strncpy(LCDPrintBuffer[1], LOStatusString2,sizeof(LOStatusString2));
	}

}

void UpCvt_vPrintAttn(void)
{

	strncpy(LCDPrintBuffer[1], AttenString1,sizeof(AttenString1));

}

void UpCvt_vPrintALC(void)
{

	strncpy(LCDPrintBuffer[1], sALCa,sizeof(sALCa));
}



void UpCvt_vPrintMute(void)
{	

	if(stConverter.stUp.u8Mute==1)
		strncpypgm2ram(sMutea,"ENABLED ",8);
	else
		strncpypgm2ram(sMutea,"DISABLED",8);
 
	strncpy(LCDPrintBuffer[1], sMutea,sizeof(sMutea));	  
}

void UpCvt_vSendI2C()
{
	stI2CUCMsg.u16GainCompenVale = 0xFFFF; /* Don't write tables */
	SetI2C(MODULE0);

}

void UpCvt_vSendLoI2C()
{
	//stI2CUCMsg.u16GainCompenVale = 0xFFFF; /* Don't write tables */
	memset((BYTE*)(&stI2CLOMsg+1),0xff,sizeof(tstI2CMsg)-1);

	switch(u8LoBand)
	{
		case 0:
			stI2CLOMsg.u8CtrlStatus &= ~0x08;
			stI2CLOMsg.u8CtrlStatus &= ~0x10;

		break;


		case 1:
			stI2CLOMsg.u8CtrlStatus &= ~0x08;
			stI2CLOMsg.u8CtrlStatus |= 0x10;


		break;

		case 2:
			stI2CLOMsg.u8CtrlStatus |= 0x08;
			stI2CLOMsg.u8CtrlStatus &= ~0x10;

		break;

		case 3:
			stI2CLOMsg.u8CtrlStatus |= 0x08;
			stI2CLOMsg.u8CtrlStatus |= 0x10;

		break;



	}
	SetI2C(MODULE3);

}


void UpCvt_vSetFreq(void)
{

    DWORD tempDWORD = 0;
    DWORD tempDWORD2 = 0;
    float fFreq = 0;
                                                                                             
    // update LCD value to Freq/Atten/IP, TBD, update wrt power, ALC, Mute
    if (CurrentMenu == nFREQ_MENU_A) // UC1 Freq
    {        
        fFreq =  Util_u8String2NFloat((char*)&LCDPrintBuffer[1][0]);
        tempDWORD = (DWORD)(fFreq * 1000.0f);// should deduct 950 000? 950M ~ 2150M

		if((tempDWORD>=12750000)&&(tempDWORD<13250000))
		{
			u16LoFreq = 11750;
			u8LoBand = 0;
		}
		else if((tempDWORD>=13250000)&&(tempDWORD<13750000))
		{
			u16LoFreq = 12250;
			u8LoBand = 1;
		}

		else if((tempDWORD>=13750000)&&(tempDWORD<14250000))
		{
			u16LoFreq = 12750;
			u8LoBand = 2;
		}


		else if((tempDWORD>=14250000)&&(tempDWORD<14500000))
		{
			u16LoFreq = 13250;
			u8LoBand = 3;
		}

        tempDWORD2 = u16LoFreq;
        
        tempDWORD2 *= 1000.0f;
        
		tempDWORD = tempDWORD - tempDWORD2;//fs - lo*1000
        
        if ((tempDWORD != stConverter.stUp.u32OutputFreq) && (tempDWORD <= MAXRFFREQ) && (tempDWORD >= MINRFFREQ))
        {
            //stConverter.stUp.u32OutputFreq = tempDWORD;
            stI2CUCMsg.unRfFreq.u32Freq = Util_u16DWORDSwap(tempDWORD);
            strncpy(RFFreqString1 ,LCDPrintBuffer[1], sizeof(RFFreqString1) );
            UpCvt_vSendI2C();
			
        }
		UpCvt_vSendLoI2C();
    }

}


void UpCvt_vSetAttn(void)
{

	WORD tempWORD = 0; 

  	 if ((stConverter.stUp.u8ALC != STATUS_OFF))
	 return;

    tempWORD = LCDPrintBuffer[1][0] - '0';
    tempWORD = ((WORD)(tempWORD * 10)) + ((WORD)LCDPrintBuffer[1][1] - '0');
    tempWORD = ((WORD)(tempWORD * 10)) + ((DWORD)LCDPrintBuffer[1][3] - '0');
    
    /* tempWORD is atten * 10 */
    if ((tempWORD != stConverter.stUp.u16Atten) && (tempWORD <= MAXATTEN)&&(tempWORD >= MINATTEN))
    {
        //stConverter.stUp.u16Atten = tempWORD;
        stI2CUCMsg.unAtten.u16Atten= Util_u16ByteSwap(tempWORD);
        memcpy(AttenString1 ,LCDPrintBuffer[1], sizeof(AttenString1) );

        UpCvt_vSendI2C();
    }
}

void UpCvt_vSetPower(void)
{
/*Disabled and moved to 	UpCvt_vSetStPwr */		
    
}


void UpCvt_vSetStPwr(void)
{
	BYTE u8TempByte =0;
	float fTemp;
	SHORT i16Temp;
	WORD u16Temp;
	
	
	
	if ((stConverter.stUp.u8ALC != STATUS_ON))
		return;
	
	
	fTemp = Util_u8String2Float(LCDPrintBuffer[1]);
	
	u16Temp = (WORD)(fTemp *10 + 500);
	
	
	if ((u16Temp!= stConverter.stUp.u16SetPwr) && (u16Temp <= MAXPOWER) && (u16Temp >= MINPOWER))
	{
		stConverter.stUp.u16SetPwr = u16Temp;
		stConverter.stUp.fSetPwr= fTemp;
		//shared 16bits of att and wtpwr
		stI2CUCMsg.unAtten.u16Atten = Util_u16ByteSwap(u16Temp);
	
		memcpy(sUPC_StPwr,LCDPrintBuffer[1], sizeof(sUPC_StPwr) );
	
		
		UpCvt_vSendI2C();
	}  
	


}


void UpCvt_vSetALC(void)
{
    BYTE u8TempByte =0;

    u8TempByte = LCD__u8GetOnOff();

	strncpy(sALCa,LCDPrintBuffer[1], sizeof(sALCa) );

	if(u8TempByte==0)
	{
		stConverter.stUp.u8ALC = OFF;
		stI2CUCMsg.u8CtrlStatus &= nAGC_OFF;//0xFD,swapped back
	}
	else if(u8TempByte==1)
	{
		stConverter.stUp.u8ALC = ON;
		stI2CUCMsg.u8CtrlStatus |= nAGC_ON;//0x02, swapped back	
	}	

	UpCvt_vSendI2C();
	
    
}

void UpCvt_vSetMute()
{
    BYTE u8TempByte =0;


	if(!memcmppgm2ram(LCDPrintBuffer[1],"ENABLED",7))
		u8TempByte = 1;
	else if (!memcmppgm2ram(LCDPrintBuffer[1],"DISABLED",8))
		u8TempByte = 0;

    if(u8TempByte==0) 
    {
    	stConverter.stUp.u8Mute = 0;
        strncpy(sMutea,LCDPrintBuffer[1], sizeof(sMutea) );	
		stI2CUCMsg.u8CtrlStatus &= nRX_DISABLE  ;

        UpCvt_vSendI2C();

		Main_vLEDTX(u8TempByte);
    }
	 else if(u8TempByte==1) 
    {
    	stConverter.stUp.u8Mute = 1;
        strncpy(sMutea,LCDPrintBuffer[1], sizeof(sMutea) );	
		stI2CUCMsg.u8CtrlStatus |= nRX_ENABLE;

        UpCvt_vSendI2C();

		Main_vLEDTX(u8TempByte);
    }
	
    
}





