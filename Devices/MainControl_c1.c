#include "define.h"
#include "Global.h"

#include "oled_c1.h"
#include "string.h"
#include "Util.h"


void Main_vPrintUpConverter(void)
{
	
	strcpypgm2ram(LCDPrintBuffer[1], "RF ");
	strncat(LCDPrintBuffer[1], RFFreqString1,sizeof(RFFreqString1));
	strcatpgm2ram(LCDPrintBuffer[1], " PWR ");
	strncat(LCDPrintBuffer[1], sUCPower,sizeof(sUCPower));
	strcatpgm2ram(LCDPrintBuffer[1], " LO ");
	if (stConverter.stUp.u8Lock == 1)
	{
		strncat(LCDPrintBuffer[1], LOStatusString1,sizeof(LOStatusString1));
	}
	else
	{
		strcatpgm2ram(LCDPrintBuffer[1], "UNLOCK");
	}

    
}

void Main_vPrintDownConverter(void)
{


	strcpypgm2ram(LCDPrintBuffer[1], "RF ");
	strncat(LCDPrintBuffer[1], RFFreqString2,sizeof(RFFreqString2));
	strcatpgm2ram(LCDPrintBuffer[1], " PWER ");
	strncat(LCDPrintBuffer[1], sDCPower,sizeof(sDCPower));
	strcatpgm2ram(LCDPrintBuffer[1], " LO ");
	if (stConverter.stDown.u8Lock == 1)
	{
		strncat(LCDPrintBuffer[1], LOStatusString1,sizeof(LOStatusString1));
	}
	else
	{
		strcatpgm2ram(LCDPrintBuffer[1], "UNLOCK");
	}


}

	
void Main_vPrintVolCtrl(void)
{

	
	// strcpypgm2ram(LCDPrintBuffer[1], "LNBDC: ");
	// strncat(LCDPrintBuffer[1], s18VDC,sizeof(s18VDC));
	// strcatpgm2ram(LCDPrintBuffer[1], " BUCDC: ");
	// strncat(LCDPrintBuffer[1], s24VDC,sizeof(s24VDC));

	// strcatpgm2ram(LCDPrintBuffer[1], " REF: ");
    
    /* ZJ: Only remains REF type */

    strcpypgm2ram(LCDPrintBuffer[1], " REF: ");
    
	if(stConverter.stDC.u8EXTREF  == 1)//ext
		strcatpgm2ram(LCDPrintBuffer[1], "External");
	else
		strcatpgm2ram(LCDPrintBuffer[1], "Internal");
   
}
	

void Main_vPrintDeviceInfo(void)
{

	strcpypgm2ram(LCDPrintBuffer[1], "IP ");
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
	strcat(LCDPrintBuffer[1], IPString);
	strcatpgm2ram(LCDPrintBuffer[1], " MN ");
	strncat(LCDPrintBuffer[1], MNString,sizeof(MNString));
//			strcatpgm2ram(LCDPrintBuffer[1], " SN ");
//			strcat(LCDPrintBuffer[1], SNString); // too long


   
}



void Main_vPrintIP(void)
{
	//memset((char*)&LCDPrintBuffer[1],' ',40);
	strncpy(LCDPrintBuffer[1], IPString,sizeof(IPString));
	
}


void Main_vPrintModelNo(void)
{
	//memset((char*)LCDPrintBuffer[1],' ',40);
	strncpy(LCDPrintBuffer[1], MNString,sizeof(MNString));
	
}

void Main_vPrintSerialNo(void)
{
	//memset((char*)LCDPrintBuffer[1],' ',40);
	strncpy(LCDPrintBuffer[1], SNString,sizeof(SNString));
	
}


void Main_vSetIP()
{
    unsigned char tempbuffer[16];

        memcpy(tempbuffer, LCDPrintBuffer[1], 15);
        tempbuffer[15] = '\0';
        if(StringToIPAddress(tempbuffer, &AppConfig.MyIPAddr))
        {
            SaveSetting();
            SaveAppConfig();
        }

}

void Main_vLEDLO(BYTE Setting)
{
	LED_LO = Setting?0:1; //0 = on, 1 = 0ff
}


void Main_vLEDTX(BYTE Setting)
{
	LED_Tx_Mute = Setting?0:1; //0 = on, 1 = 0ff
}

void Main_vLEDRX(BYTE Setting)
{
	LED_Rx_Mute = Setting?0:1; //0 = on, 1 = 0ff
}


//Set LED IO direction to output
void Main_vLEDInit(void)
{
	LED_LO_TRIS = 0;
	LED_Tx_Mute_TRIS = 0;
	LED_Rx_Mute_TRIS = 0;
}


