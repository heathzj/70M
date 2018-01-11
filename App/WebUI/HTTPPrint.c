#include "define.h"
#include"HTTPApp.h"
#include "singcom.h"
#include "oled_c1.h"
/****************************************************************************
  Section:
	Dynamic Variable Callback Functions
  ***************************************************************************/

/*****************************************************************************
  Function:
	void HTTPPrint_varname(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/

#if defined(STACK_USE_HTTP2_SERVER)

BYTE global_char_temp[15];

extern char FirmwareVersion[4];
extern unsigned char RdI2CBuffer[I2CBUFFLENGTH];
extern unsigned char I2CReceiveBuffer[9];


/*******************Converter Information***********************/



void HTTPPrint_DeviceModel(void)
{
	TCPPutString(sktHTTP, MNString);	

}

void HTTPPrint_DeviceSerial(void)
{
	TCPPutString(sktHTTP, SNString);

}

void HTTPPrint_dhcp_status(void)
{
	if(AppConfig.Flags.bIsDHCPEnabled)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"Enabled");
	else if(!AppConfig.Flags.bIsDHCPEnabled)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"Disabled");
	return;
}

/* Device IP */
void HTTPPrintIP(IP_ADDR ip)
{
	BYTE i;
	memset(global_char_temp, 0, sizeof(global_char_temp));	
	for(i = 0; i < 4u; i++)
	{
		if(i)
		TCPPut(sktHTTP, '.');
		uitoa(ip.v[i], global_char_temp);
		TCPPutString(sktHTTP, global_char_temp);
	}
}

void HTTPPrint_MIP(void)
{
	HTTPPrintIP(Manager_IP);
	return;
}

void HTTPPrint_static_ip(void)
{
	if(AppConfig.Flags.bIsDHCPEnabled)
		HTTPPrintIP(MyStaticIPAddr);
	else
		HTTPPrintIP(AppConfig.MyIPAddr);
	return;
}

void HTTPPrint_config_ip(void)
{
	HTTPPrintIP(AppConfig.MyIPAddr);
	return;
}
void HTTPPrint_config_subnet(void)
{
	HTTPPrintIP(AppConfig.MyMask);
	return;
}
void HTTPPrint_config_gw(void)
{
	HTTPPrintIP(AppConfig.MyGateway);
	return;
}
/* Device Firmware Version */
void HTTPPrint_Devicefwver(void)
{
	memset(global_char_temp, 0, sizeof(global_char_temp));
	//global_char_temp[0] = FirmwareVersion[0];
	//global_char_temp[1] = FirmwareVersion[1];
	//global_char_temp[2] = FirmwareVersion[2];
	global_char_temp[0] = '1';
	global_char_temp[1] = '0';
	global_char_temp[2] = '0';	
	global_char_temp[3] = '\0';
	TCPPutString(sktHTTP, global_char_temp);
}
/****************END OF Converter Information*******************/

void GetPower(BYTE u8Outputpower)
{
	char c8Outputpower;

	c8Outputpower = (u8Outputpower); /* Base of -30 dB */

	if(0==c8Outputpower)
		{
			global_char_temp[0] = '0';
		}
	else
		{
			global_char_temp[0] = '-';
			global_char_temp[1] = c8Outputpower<10?c8Outputpower%10+'0' : c8Outputpower/10 + '0';
			global_char_temp[2] = c8Outputpower<10? 0 : c8Outputpower%10+'0' ;
		}


}

/* Zj , can be re-used */
void GetWORDString(WORD value) 
{
	if (value < 10)
	{
		global_char_temp[0] = '0';
		global_char_temp[1] = '.';
		global_char_temp[2] = '0' + (value % 10);
	}
	else if (value < 100)
	{
		global_char_temp[0] = '0' + (value / 10);
		global_char_temp[1] = '.';
		global_char_temp[2] = '0' + (value % 10);
	}
	else if (value < 1000)
	{
		global_char_temp[0] = '0' + (value / 100);
		global_char_temp[1] = '0' + ((value / 10) % 10);
		global_char_temp[2] = '.';
		global_char_temp[3] = '0' + (value % 10);
	}
}


/* Converting KHz value to MHz string in format xxxx.xxx MHz*/
void GetDWORDString(DWORD value)
{
	if (value < 10)
	{
		global_char_temp[0] = '0';
		global_char_temp[1] = '.';
		global_char_temp[2] = '0';
		global_char_temp[3] = '0';
		global_char_temp[4] = '0' + (value % 10);
	}
	else if (value < 100)
	{
		global_char_temp[0] = '0';
		global_char_temp[1] = '.';
		global_char_temp[2] = '0';
		global_char_temp[3] = '0' + (value / 10);
		global_char_temp[4] = '0' + (value % 10);
	}
	else if (value < 1000)
	{
		global_char_temp[0] = '0';
		global_char_temp[1] = '.';
		global_char_temp[2] = '0' + (value / 100);
		global_char_temp[3] = '0' + ((value / 10) % 10);
		global_char_temp[4] = '0' + (value % 10);
	}
	else if (value < 10000)
	{
		global_char_temp[0] = '0' + (value / 1000);
		global_char_temp[1] = '.';
		global_char_temp[2] = '0' + ((value / 100) % 10);
		global_char_temp[3] = '0' + ((value / 10) % 10);
		global_char_temp[4] = '0' + (value % 10);
	}
	else if (value < 100000)
	{
		global_char_temp[0] = '0' + (value / 10000);
		global_char_temp[1] = '0' + ((value / 1000) % 10);
		global_char_temp[2] = '.';
		global_char_temp[3] = '0' + ((value / 100) % 10);
		global_char_temp[4] = '0' + ((value / 10) % 10);
		global_char_temp[5] = '0' + (value % 10);
	}
	else if (value < 1000000)
	{
		global_char_temp[0] = '0' + (value / 100000);
		global_char_temp[1] = '0' + ((value / 10000) % 10);
		global_char_temp[2] = '0' + ((value / 1000) % 10);
		global_char_temp[3] = '.';
		global_char_temp[4] = '0' + ((value / 100) % 10);
		global_char_temp[5] = '0' + ((value / 10) % 10);
		global_char_temp[6] = '0' + (value % 10);
	}
	else if (value < 10000000)
	{
		global_char_temp[0] = '0' + (value / 1000000);
		global_char_temp[1] = '0' + ((value / 100000) % 10);
		global_char_temp[2] = '0' + ((value / 10000) % 10);
		global_char_temp[3] = '0' + ((value / 1000) % 10);
		global_char_temp[4] = '.';
		global_char_temp[5] = '0' + ((value / 100) % 10);
		global_char_temp[6] = '0' + ((value / 10) % 10);
		global_char_temp[7] = '0' + (value % 10);
	}
	else
	{
		global_char_temp[0] = '0' + (value / 10000000);
		global_char_temp[1] = '0' + ((value / 1000000) % 10);
		global_char_temp[2] = '0' + ((value / 100000) % 10);
		global_char_temp[3] = '0' + ((value / 10000) % 10);
		global_char_temp[4] = '0' + ((value / 1000) % 10);
		global_char_temp[5] = '.';
		global_char_temp[6] = '0' + ((value / 100) % 10);
		global_char_temp[7] = '0' + ((value / 10) % 10);
		global_char_temp[8] = '0' + (value % 10);
	}
}

/**********************Status Page*************************/

  /* WORD TCPPutArray(TCP_SOCKET hTCP, BYTE* data, WORD len);   */

void HTTPPrint_converterarffreq(void)
{
	//memset(global_char_temp, 0, sizeof(global_char_temp));
	//GetDWORDString(stConverter.stUp.u32OutputFreq);
	//TCPPutString(sktHTTP, global_char_temp);
    
    //RFFreqString1[11] = {"0950.000MHz"}; 
    if('0' == RFFreqString1[0]) /* skip 0 to print on web */
        TCPPutArray(sktHTTP,RFFreqString1+1,7);
    else
        TCPPutArray(sktHTTP,RFFreqString1,8);
}



void HTTPPrint_converterbrffreq(void)
{
	// memset(global_char_temp, 0, sizeof(global_char_temp));
	// GetDWORDString(stConverter.stDown.u32InputFreq);
	// TCPPutString(sktHTTP, global_char_temp);
    
    if('0' == RFFreqString2[0]) /* skip 0 to print on web */
        TCPPutArray(sktHTTP,RFFreqString2+1,7);
    else
        TCPPutArray(sktHTTP,RFFreqString2,8);
}



void HTTPPrint_converteraatten(void)
{
	// memset(global_char_temp, 0, sizeof(global_char_temp));
	// GetWORDString(stConverter.stUp.u16Atten);
	// TCPPutString(sktHTTP, global_char_temp);
    //char AttenString1[7] = {"00.0 dB"}; 
    
    if('0' == AttenString1[0]) /* skip 0 to print on web */
        TCPPutArray(sktHTTP,AttenString1+1,3);
    else
        TCPPutArray(sktHTTP,AttenString1,4);
}

void HTTPPrint_converterbatten(void)
{
	// memset(global_char_temp, 0, sizeof(global_char_temp));
	// GetWORDString(stConverter.stDown.u16Atten);
	// TCPPutString(sktHTTP, global_char_temp);
    
    if('0' == AttenString2[0]) /* skip 0 to print on web */
        TCPPutArray(sktHTTP,AttenString2+1,3);
    else
        TCPPutArray(sktHTTP,AttenString2,4);
}


void HTTPPrint_swmode(void)
{
}




void HTTPPrint_converteralo(void){
	if(stConverter.stUp.u8Lock == 1)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"LOCK");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"UNLCOK");
	return;


}

void HTTPPrint_outputpowera(void){

	memset(global_char_temp, 0, sizeof(global_char_temp));
	//GetPower(stConverter.stUp.u8OutputPower);
	//TCPPutString(sktHTTP, global_char_temp);
	  TCPPutArray(sktHTTP,sUCPower,5);

}

void HTTPPrint_setpowera(void){

	memset(global_char_temp, 0, sizeof(global_char_temp));
	//GetPower(stConverter.stUp.u8OutputPower);
	//TCPPutString(sktHTTP, global_char_temp);
	  TCPPutArray(sktHTTP,sUPC_StPwr,5);

}


void HTTPPrint_ALCa(void){

	if(stConverter.stUp.u8ALC == 1)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"ON");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"OFF");
	return;

}
void HTTPPrint_Mutea(void){
	if(stConverter.stUp.u8Mute== 1)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"ENABLED ");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"DISABLED");
	return;


}
void HTTPPrint_converterblo(void){
	if(stConverter.stDown.u8Lock == 1)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"LOCK");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"UNLOCK");
	return;

}
void HTTPPrint_outputpowerb(void){
	memset(global_char_temp, 0, sizeof(global_char_temp));
	//GetPower(stConverter.stDown.u8OutputPower);

	//TCPPutString(sktHTTP, global_char_temp);
	TCPPutArray(sktHTTP,sDCPower,5);

}

void HTTPPrint_setpowerb(void){
	memset(global_char_temp, 0, sizeof(global_char_temp));
	//GetPower(stConverter.stDown.u8OutputPower);

	//TCPPutString(sktHTTP, global_char_temp);
	TCPPutArray(sktHTTP,sDNC_StPwr,5);

}


void HTTPPrint_ALCb(void){
	if(stConverter.stDown.u8ALC == 1)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"ON");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"OFF");
	return;

}
void HTTPPrint_Muteb(void){
	if(stConverter.stDown.u8Mute== 1)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"ENABLED ");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"DISABLED");
	return;


}
void HTTPPrint_24Vctrl(void){
	if(stConverter.stDC.u8BUC_DC_ONOFF== 1)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"ON");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"OFF");
	return;

}
void HTTPPrint_18Vctrl(void){
	if(stConverter.stDC.u8LNB_DC_ONOFF== 1)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"ON");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"OFF");
	return;

}


/******************END OF Status Page**********************/



/**********************Config Page*************************/



void HTTPPrint_config_dhcpchecked(void)
{
	if(AppConfig.Flags.bIsDHCPEnabled)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"checked");
	else if(!AppConfig.Flags.bIsDHCPEnabled)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"unchecked");
	return;
}




void HTTPPrint_ALCaSelected(WORD state){
	if((state)&&(stConverter.stUp.u8ALC == 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}
	else if((!state)&&(stConverter.stUp.u8ALC != 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}

}
void HTTPPrint_MuteaSelected(WORD state){
	if((state)&&(stConverter.stUp.u8Mute== 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}
	else if((!state)&&(stConverter.stUp.u8Mute != 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}

}
void HTTPPrint_ALCbSelected(WORD state){
	if((state)&&(stConverter.stDown.u8ALC == 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}
	else if((!state)&&(stConverter.stDown.u8ALC != 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}

}
void HTTPPrint_MutebSelected(WORD state){
	if((state)&&(stConverter.stDown.u8Mute== 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}
	else if((!state)&&(stConverter.stDown.u8Mute != 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}

}
void HTTPPrint_DC18VSelected(WORD state){
	if((state)&&(stConverter.stDC.u8LNB_DC_ONOFF== 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}
	else if((!state)&&(stConverter.stDC.u8LNB_DC_ONOFF!= 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}


}
void HTTPPrint_DC24VSelected(WORD state){
	if((state)&&(stConverter.stDC.u8BUC_DC_ONOFF== 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}
	else if((!state)&&(stConverter.stDC.u8BUC_DC_ONOFF!= 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}

}


void HTTPPrint_LNBREFSelected(WORD state){
	if((state)&&(stConverter.stDC.u8LNB_REF_ONOFF== 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}
	else if((!state)&&(stConverter.stDC.u8LNB_REF_ONOFF!= 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}

}

void HTTPPrint_BUCREFSelected(WORD state){
	if((state)&&(stConverter.stDC.u8BUC_REF_ONOFF== 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}
	else if((!state)&&(stConverter.stDC.u8BUC_REF_ONOFF!= 1))
	{
		TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");
	}


}




void HTTPPrint_BUCREF()
	{
	if(stConverter.stDC.u8BUC_REF_ONOFF== 1)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"ON");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"OFF");
	return;

	
	}

void HTTPPrint_LNBREF()
	{
	if(stConverter.stDC.u8LNB_REF_ONOFF== 1)
		TCPPutROMString(sktHTTP, (ROM BYTE*)"ON");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"OFF");
	return;	
	}

void HTTPPrint_EXTREF()
	{
	if(stConverter.stDC.u8EXTREF == 1)  // 1=external reference 0=internal reference
		TCPPutROMString(sktHTTP, (ROM BYTE*)"External");
	else
		TCPPutROMString(sktHTTP, (ROM BYTE*)"Internal");
	return;	
	}


void HTTPPrint_BUCCurrent()
{
	char ac8Temp[6];

	sprintf(ac8Temp,"%d", stConverter.stDC.u16BUCCurrent);

	TCPPutString(sktHTTP, ac8Temp);

}

void HTTPPrint_LNBCurrent()
{
	char ac8Temp[6];

	sprintf(ac8Temp,"%d", stConverter.stDC.u16LNBCurrent);

	TCPPutString(sktHTTP, ac8Temp);

}



void HTTPPrint_rdi2cdata(void)
{
  BYTE Out[35] = {0};
  BYTE i = 0;
  for (i = 0; i < 16; i++)
  {
	  Out[(2 * i)]=Int2Hex(RdI2CBuffer[i]/16);
	  Out[(2 * i) + 1]=Int2Hex(RdI2CBuffer[i]%16);
  }
  TCPPutString(sktHTTP, Out);
}

void HTTPPrint_wri2cdata(void)
{
  BYTE Out[35] = {0};
  BYTE i = 0;
  for (i = 0; i < 16; i++)
  {
	  Out[(2 * i)]=Int2Hex(I2CReceiveBuffer[i]/16);
	  Out[(2 * i) + 1]=Int2Hex(I2CReceiveBuffer[i]%16);
  }
  TCPPutString(sktHTTP, Out);
}




/*******************END OF Config Page*************************/

void HTTPPrint_setpasscolor(void)
{
//    BYTE Temp[8] = {0};
memset(global_char_temp	, 0, sizeof(global_char_temp));

    if(webpassinfo.setpasscolor==passred)
		strcpypgm2ram(global_char_temp,"red");
    else if(webpassinfo.setpasscolor==passgreen)
		strcpypgm2ram(global_char_temp,"green");
		
    TCPPutString(sktHTTP, global_char_temp);
}


void HTTPPrint_setpass(void)
{
    BYTE Temp[30] = {0};
	
    switch (webpassinfo.setpass)
	{
     case successful:
		strcpypgm2ram(Temp,"Set Successful.");
     break;
	
     case invalid_charactor:
		strcpypgm2ram(Temp,"Invalid character contained.");
     break;

     case too_long:
		strcpypgm2ram(Temp,"Password too long.");
     break;

     case old_password_wrong:
		strcpypgm2ram(Temp,"Old password wrong.");
     break;

     case repeat_password_different:
		strcpypgm2ram(Temp,"Repeat password is different.");
     break;

	 default:
		strcpypgm2ram(Temp,"   \t");
     break;

	}
	
    TCPPutString(sktHTTP, Temp);
}



/******************* Alarms *************************/
void HTTPPrint_converteraalarm(void)
{
	memset(global_char_temp	, 0, sizeof(global_char_temp));
	global_char_temp[0] = '0' + stConverter.stUp.u8AlarmStatus; //0=alm(00ff00 r), 1= ok(FF0000 g)
    TCPPutString(sktHTTP, global_char_temp);
}

void HTTPPrint_converterbalarm(void)
{
	memset(global_char_temp	, 0, sizeof(global_char_temp));
	global_char_temp[0] = '0' + stConverter.stDown.u8AlarmStatus;//0=alm(00ff00 r), 1= ok(FF0000 g)

    TCPPutString(sktHTTP, global_char_temp);
}

void HTTPPrint_BUCIAlm(void)
{
	memset(global_char_temp	, 0, sizeof(global_char_temp));
	if(stConverter.stDC.u8BUC_DC_OVERCurrent == 1) //over current 1=over current, 0=normal. 
		global_char_temp[0] = '0' ;//0=alm(00ff00 r), 1= ok(FF0000 g)
	else	
		global_char_temp[0] = '1' ;//0=alm(00ff00 r), 1= ok(FF0000 g)

    TCPPutString(sktHTTP, global_char_temp);
}

void HTTPPrint_LNBIAlm(void)
{
	memset(global_char_temp	, 0, sizeof(global_char_temp));
	if(stConverter.stDC.u8LNB_DC_OVERCurrent == 1) //over current 1=over current, 0=normal. 
		global_char_temp[0] = '0' ;//0=alm(00ff00 r), 1= ok(FF0000 g)
	else	
		global_char_temp[0] = '1' ;//0=alm(00ff00 r), 1= ok(FF0000 g)
    TCPPutString(sktHTTP, global_char_temp);
}

void HTTPPrint_ClearBUCIAlm(WORD u16data)
{
	TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");

}
void HTTPPrint_ClearLNBIAlm(WORD u16data)
{
	TCPPutROMString(sktHTTP, (ROM BYTE*)"selected");

}


void HTTPPrint_led(WORD num)
{
   BYTE Value[5] = {0};

	switch(num)
	{
		case 0:
            num = 3; //N.A
			break;
		case 1:
		//	num = BUCinfo[0].alarm.fan;
           num = 3; //N/A
			break;
		case 2:
  //       if(BUCinfo[0].info.BUC_model==KUBAND)
	//		num = (BUCinfo[0].alarm.templvl_sspa == 0)?0:1;
	//	 else
	//		num = (BUCinfo[0].alarm.templvl==0)?0:1;
        	break;
		case 3:
      //   if(BUCinfo[0].info.BUC_model==KUBAND)
		//	num = BUCinfo[0].alarm.rfon_sspa;
		// else
		//	num = BUCinfo[0].alarm.rfon;
			break;
		case 4:
    //   	 if(BUCinfo[0].info.BUC_model==KUBAND)
	//		num = (BUCinfo[0].alarm.rflow_sspa==0)?2:1;
    //     else
	//		num = (BUCinfo[0].alarm.rflow==0)?2:1;
		   break;
		case 5:
    //       if(BUCinfo[0].info.BUC_model==CBAND)  
    //        num = BUCinfo[0].alarm.refclk;
    //       else
    //        num =3;//N/A
			break;
		case 6:
			//num = BUCinfo[0].alarm.fetbias;
            num =3;//N/A
			break;
		case 7:
     //     if((BUCinfo[0].info.BUC_model==KUBAND)||(BUCinfo[0].info.BUC_model==CBAND))
	//		num = BUCinfo[0].alarm.Lo;
     //     else
     //       num = 3;
			break;

		default:
			num = 0;
	}

	//if(BUCinfo[0].info.firmwareVersion[1] == '?')
	//	num = 3;

    uitoa(num, (BYTE*)Value);

   	TCPPutString(sktHTTP, Value);
	return;
}

void HTTPPrint_ned(WORD num)
{
   BYTE Value[5] = {0};
	switch(num)
	{
		case 0:
			//num = LED0_IO;
            num = 3; //N.A
			break;
		case 1:
		//	num = BUCinfo[0].alarm.fan;
           num = 3; //N/A
			break;
		case 2:
    //     if(BUCinfo[1].info.BUC_model==KUBAND)
//			num = (BUCinfo[1].alarm.templvl_sspa == 0)?0:1;
	//	 else
//			num = (BUCinfo[1].alarm.templvl == 0)?0:1;
        	break;
		case 3:
   //       if(BUCinfo[1].info.BUC_model==KUBAND)
	//		num = BUCinfo[1].alarm.rfon_sspa;
      //    else
		//	num = BUCinfo[1].alarm.rfon;
			break;
		case 4:
  //         if(BUCinfo[1].info.BUC_model==KUBAND)
	//		  num = (BUCinfo[1].alarm.rflow_sspa == 0)?2:1;
      //     else
//			  num = (BUCinfo[1].alarm.rflow == 0)?2:1;
		   break;
		case 5:
  //         if(BUCinfo[1].info.BUC_model==CBAND)  
     //       num = BUCinfo[1].alarm.refclk;
    //       else
            num =3;//N/A
			break;
		case 6:
			//num = BUCinfo[0].alarm.fetbias;
            num =3;//N/A
			break;
		case 7:
          //if((BUCinfo[1].info.BUC_model==KUBAND)||(BUCinfo[1].info.BUC_model==CBAND))
	//		num = BUCinfo[1].alarm.Lo;
      //    else
        //    num = 3;
			break;

		default:
			num = 0;
	}

	//if(BUCinfo[1].info.firmwareVersion[1] == '?')
	//	num = 3;

    uitoa(num, (BYTE*)Value);
    TCPPutString(sktHTTP, Value);
	return;
}


/******************* END Alarms *************************/
/*------------------------------------------------------*/
/******************* END Alarms *************************/


void HTTPPrint_maf(void)
{
  BYTE Out[4] = {0};
  Out[0]=Int2Hex(AppConfig.MyMACAddr.v[4]/16);
  Out[1]=Int2Hex(AppConfig.MyMACAddr.v[4]%16);
  //uitoa(mac5,(BYTE*)(Out));
  TCPPutString(sktHTTP, Out);
}


void HTTPPrint_mas(void)
{
  BYTE Out[4] = {0};
  Out[0]=Int2Hex(AppConfig.MyMACAddr.v[5]/16);
  Out[1]=Int2Hex(AppConfig.MyMACAddr.v[5]%16);
  //uitoa(mac6,(BYTE*)(Out));
  TCPPutString(sktHTTP, Out);
}



void HTTPPrint_config_mac(void)
{
	BYTE i;
	
	if(TCPIsPutReady(sktHTTP) < 18u)
	{//need 17 bytes to write a MAC
		curHTTP.callbackPos = 0x01;
		return;
	}	
	
	// Write each byte
	for(i = 0; i < 6u; i++)
	{
		if(i)
			TCPPut(sktHTTP, ':');
		TCPPut(sktHTTP, btohexa_high(AppConfig.MyMACAddr.v[i]));
		TCPPut(sktHTTP, btohexa_low(AppConfig.MyMACAddr.v[i]));
	}
	
	// Indicate that we're done
	curHTTP.callbackPos = 0x00;
	return;
}




// SNMP Read communities configuration page
void HTTPPrint_read_comm(WORD num)
{
	#if defined(STACK_USE_SNMP_SERVER)
	// Ensure no one tries to read illegal memory addresses by specifying 
	// illegal num values.
	if(num >= SNMP_MAX_COMMUNITY_SUPPORT)
		return;
		
	// Send proper string
	TCPPutString(sktHTTP, AppConfig.readCommunity[num]);
	#endif
}

// SNMP Write communities configuration page
void HTTPPrint_write_comm(WORD num)
{
	#if defined(STACK_USE_SNMP_SERVER)
	// Ensure no one tries to read illegal memory addresses by specifying 
	// illegal num values.
	if(num >= SNMP_MAX_COMMUNITY_SUPPORT)
		return;
		
	// Send proper string
	TCPPutString(sktHTTP, AppConfig.writeCommunity[num]);
	#endif
}

#endif
