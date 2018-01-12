/*****************************************************************************
  Function:
	BOOL HTTPExe_get_deviceinfo(void)
	
  Internal:
  	See documentation in the TCP/IP Stack API or HTTP2.h for details.
  ***************************************************************************/
#include "define.h" 
#include "HTTPApp.h"
//#include "BUCClient.h"
//#include "RCUHLAccess.h"
#include "singcom.h"
#include "global.h"
#include <string.h>
#include "oled_c1.h"
#include "i2c_c1.h"
#include "DeviceApi.h"
#include "Util.h"
 
char oldp[10];
char newp[10];
char rep[10];

BYTE I2CSlaveAddress = CONVERTER_ADDRESS;
unsigned char RdI2CBuffer[I2CBUFFLENGTH];
BYTE WebpageWriteI2CFlag = FALSE;



static BOOL HTTPGet__boInfoConfig(void);
static BOOL HTTPGet__boNetworkConfig(void);
static BOOL HTTPGet__boDeviceConfig(void);

static BOOL HTTPGet__boSetOnOff(BYTE* pu8Switch, BYTE* pcData);

/* Frequency A */
static BYTE HTTPGet__u8SetUpCvtRFFreq(void);

 /* Frequency B */
static BYTE HTTPGet__u8SetDownCvtRFFreq(void);

 /* Attenuation A */
static BYTE HTTPGet__u8SetUpCvtAttn(void);

/* Attenuation B */
static BYTE HTTPGet__u8SetDownCvtAttn(void);

/* outputpowera */
static BYTE HTTPGet__u8SetUpCvtPower(void);
    
/* outputpowerb */
static BYTE HTTPGet__u8SetDownCvtPower(void);

/* ALCa */
static BYTE HTTPGet__u8SetUpCvtALC(void);

/* ALCb */
static BYTE HTTPGet__u8SetDownCvtALC(void);

/* Mutea */
static BYTE HTTPGet__u8SetUpCvtMute(void);
 
/* Muteb */
static BYTE HTTPGet__u8SetDownCvtMute(void); 

/* 18Vctrl */
static BYTE HTTPGet__u8SetVOL18VDC(void);

/* 24Vctrl  */
static BYTE HTTPGet__u8SetVOL24VDC(void);




static BOOL HTTPGet__boInfoConfig(void)
{
    BYTE *ptr; 
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"ID");
    if(ptr)
    {
    }
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"serial");
    if(ptr)
    {
      if(*(ptr+2)=='2')
      {
      }
      else if (*(ptr+2)=='4')
      {
      }
    }    
    
}



static BOOL HTTPGet__boNetworkConfig(void)
{
    BYTE *ptr; 
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"DIP");
    if(ptr)
    {
          if(StringToIPAddress(ptr, &AppConfig.MyIPAddr))
          {
             SaveSetting();
             SaveAppConfig();
          }
    }

    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"gateway");
    if(ptr)
    {
          if(StringToIPAddress(ptr, &AppConfig.MyGateway))
          {
             SaveSetting();
             SaveAppConfig();
          }
    }

    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"subnet");
    if(ptr)
    {
          if(StringToIPAddress(ptr, &AppConfig.MyMask))
          {
             SaveSetting();
             SaveAppConfig();
          }
    }    

}



static BOOL HTTPGet__boSetOnOff(BYTE* pu8Switch, BYTE* pcData)
{
      if((*(pcData)=='O')&&(*(pcData+1)=='N')) /*ON */
      {
        *pu8Switch = 1;
        return 1; 
      }
      else if((*(pcData)=='O')&&(*(pcData+1)=='F')&&(*(pcData+2)=='F')) /*OFF */
      {
        *pu8Switch = 0;
        return 1; 
      }
      else
      {
        return 0; /* error */
          
      }
    
}


/* frequency are with variable length 950.000 - 2150.000
consider using strchr to find '.' location */
/* convert string xxxx.xxx MHz to kHz value */

static BYTE HTTPGet__u8SetUpCvtRFFreq(void)
{
    BYTE *ptr;
    BYTE* pcDotPosition;
    BYTE* pcTemp;
    DWORD tempDWORD = 0;
	BYTE u8DigitNum = 0;	

    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"converterarffreq"); /* should also count '=' 17 */
    
    if(ptr)
    { 

		//void *memchr (auto const void *s, auto unsigned char c, auto size_t n);
	
        pcDotPosition = memchr (ptr, '.', 8); /* find the dot xxx.000*/

		if(pcDotPosition == NULL)
			return FALSE;
		else
			u8DigitNum = pcDotPosition - ptr;
        
        pcTemp = ptr; //first byte

		tempDWORD = (DWORD)(*pcTemp -'0'); 
		pcTemp++;
        while(pcTemp <=  (pcDotPosition+3)) /* assume 3 bytes of fixed decimal points */
        {
            if(pcTemp != pcDotPosition) /* skip the '.' */
            {
                tempDWORD *= (DWORD)10;
                tempDWORD += (DWORD)(*pcTemp - '0');   
               
            }
			 pcTemp++;
        }
	

		tempDWORD = nLO_FREQ - tempDWORD;


        if ((tempDWORD != stConverter.stUp.u32OutputFreq) && (tempDWORD <= MAXRFFREQ) && (tempDWORD >= MINRFFREQ))
        {
        
			//stConverter.stUp.u32OutputFreq = tempDWORD;
			stI2CUCMsg.unRfFreq.u32Freq = Util_u16DWORDSwap(tempDWORD);

			
            if(u8DigitNum==3)
            {
                RFFreqString1[0] = '0';
                strncpy(RFFreqString1+1, ptr, 7 );
                
            }
                    
            else if(u8DigitNum==4)
            {
                strncpy(RFFreqString1, ptr, 8 );
                
            }
            
			UpCvt_vSendI2C();

		}
    }   
    
    
}


static BYTE HTTPGet__u8SetDownCvtRFFreq(void)
{
    BYTE *ptr;
    BYTE* pcDotPosition;
    BYTE* pcTemp;
    DWORD tempDWORD = 0;
	BYTE u8DigitNum = 0;	

    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"converterbrffreq"); /* should also count '=' 17 */
    
    if(ptr)
    {   

		//void *memchr (auto const void *s, auto unsigned char c, auto size_t n);
		
		pcDotPosition = memchr (ptr, '.', 8); /* find the dot xxx.000*/
		
		if(pcDotPosition == NULL)
			return FALSE;
		else
			u8DigitNum = pcDotPosition - ptr;
		
		pcTemp = ptr; //first byte
		
		tempDWORD = (DWORD)(*pcTemp -'0'); 
		pcTemp++;
		while(pcTemp <=  (pcDotPosition+3)) /* assume 3 bytes of fixed decimal points */
		{
			if(pcTemp != pcDotPosition) /* skip the '.' */
			{
				tempDWORD *= (DWORD)10;
				tempDWORD += (DWORD)(*pcTemp - '0');   
			   
			}
			 pcTemp++;
		}
		



        if ((tempDWORD != stConverter.stDown.u32InputFreq) && (tempDWORD <= MAXRFFREQ) && (tempDWORD >= MINRFFREQ))
        {
        
			//stConverter.stDown.u32InputFreq = tempDWORD;
       
			stI2CDCMsg.unRfFreq.u32Freq = Util_u16DWORDSwap(tempDWORD);
			
            if(u8DigitNum==3)
            {
                RFFreqString2[0] = '0';
                memcpy(RFFreqString2+1, ptr, 7 );   
            }
                    
            else if(u8DigitNum==4)
            {
                memcpy(RFFreqString2, ptr, 8 );
            }
            
			DownCvt_vSendI2C();

		}
    }     
}


/* Attenuation are with variable length 
consider using strchr to find '.' location */
static BYTE HTTPGet__u8SetUpCvtAttn(void)
{
    BYTE *ptr;
    
    BYTE* pcDotPosition;
    BYTE* pcTemp;
    WORD tempWORD = 0; 
	BYTE u8DigitNum = 0;

    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"converteraatten");
    if((ptr) && (stConverter.stUp.u8ALC == STATUS_OFF))
    {  
		//void *memchr (auto const void *s, auto unsigned char c, auto size_t n);
		
		pcDotPosition = memchr (ptr, '.', 8); /* find the dot xxx.000*/
		
		if(pcDotPosition == NULL)
			return FALSE;
		else
			u8DigitNum = pcDotPosition - ptr;
		
		pcTemp = ptr; //first byte
		
		tempWORD = (DWORD)(*pcTemp -'0'); 
		pcTemp++;
		while(pcTemp <=  (pcDotPosition+1)) /* assume 1 bytes of fixed decimal points */
		{
			if(pcTemp != pcDotPosition) /* skip the '.' */
			{
				tempWORD *= (DWORD)10;
				tempWORD += (DWORD)(*pcTemp - '0');   
			   
			}
			 pcTemp++;
		}
		


        
        if ((tempWORD != stConverter.stUp.u16Atten) && (tempWORD <= MAXATTEN) && (tempWORD >= MINATTEN))
        {
            //stConverter.stUp.u16Atten = tempWORD;
            
			stI2CUCMsg.unAtten.u16Atten = Util_u16ByteSwap(tempWORD);
            
            if(u8DigitNum==1)
            {
                AttenString1[0] = '0';
                memcpy(AttenString1+1, ptr, 3 );   
            }
                    
            else if(u8DigitNum==2)
            {
                memcpy(AttenString1, ptr, 4 );
            }
            
			UpCvt_vSendI2C();
        }

    }  
    
}

static BYTE HTTPGet__u8SetDownCvtAttn(void)
{
    BYTE *ptr;
    
    BYTE* pcDotPosition;
    BYTE* pcTemp;
    WORD tempWORD = 0; 
	BYTE u8DigitNum = 0;

    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"converterbatten");
   if((ptr) && (stConverter.stDown.u8ALC == STATUS_OFF))
    {  
		//void *memchr (auto const void *s, auto unsigned char c, auto size_t n);
		
		pcDotPosition = memchr (ptr, '.', 8); /* find the dot xxx.000*/
		
		if(pcDotPosition == NULL)
			return FALSE;
		else
			u8DigitNum = pcDotPosition - ptr;
		
		pcTemp = ptr; //first byte
		
		tempWORD = (DWORD)(*pcTemp -'0'); 
		pcTemp++;
		while(pcTemp <=  (pcDotPosition+1)) /* assume 1 bytes of fixed decimal points */
		{
			if(pcTemp != pcDotPosition) /* skip the '.' */
			{
				tempWORD *= (DWORD)10;
				tempWORD += (DWORD)(*pcTemp - '0');   
			   
			}
			 pcTemp++;
		}
		

	
        
        if ((tempWORD != stConverter.stDown.u16Atten) && (tempWORD <= MAXATTEN) && (tempWORD >= MINATTEN))
        {
            //stConverter.stDown.u16Atten = tempWORD;
			stI2CDCMsg.unAtten.u16Atten = Util_u16ByteSwap(tempWORD);
            
            if(u8DigitNum==1)
            {
                AttenString2[0] = '0';
                memcpy(AttenString2+1, ptr, 3);   
            }
                    
            else if(u8DigitNum==2)
            {
                memcpy(AttenString2, ptr, 4 );
            }
            
			DownCvt_vSendI2C();
        }

    }  
    
}

static BYTE HTTPGet__u8SetUpCvtPower(void)
{
    BYTE *ptr;
    BYTE tempBYTE = 0;    
    BYTE u8DigitNum = 0;

			
	 SHORT i16Temp;
	 WORD u16Temp;

    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"outputpowera");
     if((ptr) && (stConverter.stUp.u8ALC == STATUS_ON)) //only if AGC is on
    {
 
	 i16Temp = Util_u8String2int16(ptr);
	 
	 u16Temp = (i16Temp *10 + 500);

        if((stConverter.stUp.i16OutputPower!= u16Temp)&&(u16Temp >= MINPOWER)&&(u16Temp <= MAXPOWER))
        {
            stConverter.stUp.i16OutputPower = u16Temp;
			stConverter.stUp.i16OutputPower = i16Temp;

			//shared 2byte of atten and wr pwr
            stI2CUCMsg.unAtten.u16Atten = Util_u16ByteSwap(u16Temp); //output_power dBm X10+500

			if ((stConverter.stUp.i16OutputPower<0) &&(stConverter.stUp.i16OutputPower>-1))
			{
				sprintf(sUCPower,"-%02d dBm",stConverter.stUp.i16OutputPower);  
			}
			else
			{
				sprintf(sUCPower,"%+03d dBm",stConverter.stUp.i16OutputPower);
			}
            UpCvt_vSendI2C();              
        }    	
    }   
    
}

static BYTE HTTPGet__u8SetUpCvtSetPower(void)
{
    BYTE *ptr;
    BYTE tempBYTE = 0;    
    BYTE u8DigitNum = 0;
	float fTemp;

			
	 SHORT i16Temp;
	 WORD u16Temp;

	 int i16Frac;

    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"setpowera");
     if((ptr) && (stConverter.stUp.u8ALC == STATUS_ON)) //only if AGC is on
    {
 
	 fTemp = Util_u8String2Float(ptr);
	 
	 u16Temp = (WORD)(fTemp *10 + 500);

        if((stConverter.stUp.u16SetPwr!= u16Temp)&&(u16Temp >= MINPOWER)&&(u16Temp <= MAXPOWER))
        {
            //stConverter.stUp.u16SetPwr = u16Temp;
			stConverter.stUp.fSetPwr= fTemp;

			//shared 2byte of atten and wr pwr
            stI2CUCMsg.unAtten.u16Atten = Util_u16ByteSwap(u16Temp); //output_power dBm X10+500

			i16Frac = (int)(stConverter.stUp.fSetPwr*10) %10;
			if(i16Frac < 0)
			  i16Frac *= -1;
			if (((int)stConverter.stUp.fSetPwr,i16Frac<0)&&((int)stConverter.stUp.fSetPwr,i16Frac>-1))
			{
				sprintf(sUPC_StPwr,"-%02d.%1d dBm",(int)stConverter.stUp.fSetPwr,i16Frac );	
			}
			else
			{
				sprintf(sUPC_StPwr,"%+03d.%1d dBm",(int)stConverter.stUp.fSetPwr,i16Frac );
			}	
            UpCvt_vSendI2C();              
        }    	
    }   
    
}



static BYTE HTTPGet__u8SetDownCvtPower(void)
{
    BYTE *ptr;
    BYTE tempBYTE = 0;    
    BYTE u8DigitNum = 0;
	
		   
	SHORT i16Temp;
	WORD u16Temp;

    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"outputpowerb");
    if((ptr) && (stConverter.stDown.u8ALC == STATUS_ON))
    {
		
		i16Temp = Util_u8String2int16(ptr);
		
		u16Temp = (i16Temp *10 + 500);

    

        if((stConverter.stDown.u16OutputPower!= u16Temp)&&(u16Temp >= MINPOWER)&&(u16Temp <= MAXPOWER))
        {
          stConverter.stDown.u16OutputPower = u16Temp;
		  stConverter.stDown.i16OutputPower = i16Temp;

		  //shared 2byte of atten and wr pwr
          stI2CDCMsg.unAtten.u16Atten = Util_u16ByteSwap(u16Temp);
          if ((stConverter.stDown.i16OutputPower<0)&&(stConverter.stDown.i16OutputPower>-1))
			{
		  		sprintf(sUCPower,"-%02d dBm",stConverter.stDown.i16OutputPower);         
   			}
			else
			{    
		  		sprintf(sUCPower,"%+03d dBm",stConverter.stDown.i16OutputPower);  
			}  	
          DownCvt_vSendI2C();              
        }    	
    }   
    
}


static BYTE HTTPGet__u8SetDownCvtSetPower(void)
{
    BYTE *ptr;
    BYTE tempBYTE = 0;    
    BYTE u8DigitNum = 0;
	float fTemp;
		   
	SHORT i16Temp;
	WORD u16Temp;
	int i16Frac;

    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"setpowerb");
    if((ptr) && (stConverter.stDown.u8ALC == STATUS_ON))
    {
		
		fTemp = Util_u8String2Float(ptr);
		
		u16Temp = (WORD)(fTemp *10 + 500);

    

        if((stConverter.stDown.u16SetPwr!= u16Temp)&&(u16Temp >= MINPOWER)&&(u16Temp <= MAXPOWER))
        {
          //stConverter.stDown.u16SetPwr = u16Temp;
		  stConverter.stDown.fSetPwr = fTemp;

		  //shared 2byte of atten and wr pwr
          stI2CDCMsg.unAtten.u16Atten = Util_u16ByteSwap(u16Temp);

		  i16Frac = (int)(stConverter.stDown.fSetPwr*10) %10;
		  if(i16Frac < 0)
		  	i16Frac *= -1;

		 if  (((int)stConverter.stDown.fSetPwr, i16Frac<0)&&((int)stConverter.stDown.fSetPwr, i16Frac>-1))
			{
		  		sprintf(sDNC_StPwr,"-%02d.%1d dBm",(int)stConverter.stDown.fSetPwr, i16Frac);	  
   			}     
		else
			{
		  		sprintf(sDNC_StPwr,"%+03d.%1d dBm",(int)stConverter.stDown.fSetPwr, i16Frac);	  
   			} 	
          DownCvt_vSendI2C();              
        }    	
    }   
    
}


static BYTE HTTPGet__u8SetUpCvtALC(void)
{
    BYTE *ptr;
    BYTE u8TempByte = 0; 
    
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"ALCa");
    if(ptr)
    {
        if(*(ptr+1)=='N')
        {
               memcpypgm2ram(sALCa,"ON ",sizeof(sALCa));
			   stConverter.stUp.u8ALC= 1;
			   

        }
        else if ((*(ptr+1)=='F') && (*(ptr+2)=='F'))
        {
                memcpypgm2ram(sALCa,"OFF",sizeof(sALCa));
				stConverter.stUp.u8ALC =0;
        }

		u8TempByte = (stI2CUCMsg.u8CtrlStatus & nAGC_ON)?1:0;

        if(stConverter.stUp.u8ALC != u8TempByte)
        {
            stI2CUCMsg.u8CtrlStatus = (stConverter.stUp.u8ALC ==1) ? (stI2CUCMsg.u8CtrlStatus | nAGC_ON):(stI2CUCMsg.u8CtrlStatus & nAGC_OFF);

            UpCvt_vSendI2C();            
        } 

    }     
    
}

static BYTE HTTPGet__u8SetDownCvtALC(void)
{
    BYTE *ptr;
    BYTE u8TempByte = 0;   
    
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"ALCb");
    if(ptr)
    {
        if(*(ptr+1)=='N')
        {
               memcpypgm2ram(sALCb,"ON ",sizeof(sALCb));
			   stConverter.stDown.u8ALC = 1;
			   

        }
        else if ((*(ptr+1)=='F') && (*(ptr+2)=='F'))
        {
                memcpypgm2ram(sALCb,"OFF",sizeof(sALCb));
				stConverter.stDown.u8ALC =0;
        }

		u8TempByte = (stI2CDCMsg.u8CtrlStatus & nAGC_OFF)?0:1;

        if(stConverter.stDown.u8ALC != u8TempByte)
        {
            
			stI2CDCMsg.u8CtrlStatus = (stConverter.stDown.u8ALC ==1) ? (stI2CDCMsg.u8CtrlStatus & nAGC_ON):(stI2CUCMsg.u8CtrlStatus | nAGC_OFF);
            

            DownCvt_vSendI2C();            
        }  

    }     
    
}

static BYTE HTTPGet__u8SetUpCvtMute(void)
{
    BYTE *ptr;
    BYTE u8TempByte = 0;  
    
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Mutea");
    if(ptr)
    {
        if( (*(ptr)=='E') && (*(ptr+1)=='n'))
        {
               memcpypgm2ram(sMutea,"ENABLED ",sizeof(sMutea));
			   stConverter.stUp.u8Mute = 1;
			   Main_vLEDTX(ON);
			   

        }
        else if ((*(ptr+1)=='i') && (*(ptr+2)=='s'))
        {
                memcpypgm2ram(sMutea,"DISABLED",sizeof(sMutea));
				stConverter.stUp.u8Mute =0;
				Main_vLEDTX(OFF);
        }

		u8TempByte = (stI2CUCMsg.u8CtrlStatus & nRX_ENABLE)?1:0;

        if(stConverter.stUp.u8Mute != u8TempByte)
        {
            stI2CUCMsg.u8CtrlStatus = (stConverter.stUp.u8Mute==1)?(stI2CUCMsg.u8CtrlStatus|nRX_ENABLE):(stI2CUCMsg.u8CtrlStatus & nRX_DISABLE);

            UpCvt_vSendI2C();            
        }        
    }    
    
}

static BYTE HTTPGet__u8SetDownCvtMute(void)
{
    BYTE *ptr;
    BYTE u8TempByte = 0;  
    
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"Muteb");
    if(ptr)
    {
        if( (*(ptr)=='E') && (*(ptr+1)=='n'))
        {
               memcpypgm2ram(sMuteb,"ENABLED ",sizeof(sMuteb));
			   stConverter.stDown.u8Mute = 1;
			   //Main_vLEDRX(ON); //zj disable for L-band

        }
        else if ((*(ptr+1)=='i') && (*(ptr+2)=='s'))
        {
                memcpypgm2ram(sMuteb,"DISABLED",sizeof(sMuteb));
				stConverter.stDown.u8Mute =0;
				//Main_vLEDRX(OFF); //zj disable for L-band
        }

		u8TempByte = (stI2CDCMsg.u8CtrlStatus & nRX_ENABLE)?1:0;

        if(stConverter.stDown.u8Mute != u8TempByte)
        {
           
		   stI2CDCMsg.u8CtrlStatus = (stConverter.stDown.u8Mute==1)?(stI2CDCMsg.u8CtrlStatus|nRX_ENABLE):(stI2CUCMsg.u8CtrlStatus & nRX_DISABLE);
           
           DownCvt_vSendI2C();            
        }  
    }    
    
}

static BYTE HTTPGet__u8SetVOL18VDC(void)
{
    BYTE *ptr;
    BYTE u8TempByte = 0;  
    
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"18Vctrl");
    if(ptr)
    {
       if(*(ptr+1)=='N')
       	{
            memcpypgm2ram(s18VDC,"ON ",sizeof(s18VDC));
			//stConverter.stDC.u8LNB_DC_ONOFF= 1;
			stI2CREFMsg.u8Status |= nLNB_DC_ON;
			SetI2C(MODULE2);

       	}
        else if ((*(ptr+1)=='F') && (*(ptr+2)=='F'))
        {
            memcpypgm2ram(s18VDC,"OFF",sizeof(s18VDC));
			//stConverter.stDC.u8LNB_DC_ONOFF= 0;
			stI2CREFMsg.u8Status &= nLNB_DC_OFF;
			SetI2C(MODULE2);
        }
		

    }     
    
    
}

static BYTE HTTPGet__u8SetVOL24VDC(void)
{
    
    BYTE *ptr;
    BYTE u8TempByte = 0;  
    
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"24Vctrl");
    if(ptr)
    {
      if(*(ptr+1)=='N')
       	{
            memcpypgm2ram(s24VDC,"ON ",sizeof(s24VDC));

			//stConverter.stDC.u8BUC_DC_ONOFF= 1;
			stI2CREFMsg.u8Status |= nBUC_DC_ON;
			 SetI2C(MODULE2);   

       	}
        else if ((*(ptr+1)=='F') && (*(ptr+2)=='F'))
        {
            memcpypgm2ram(s24VDC,"OFF",sizeof(s24VDC));
			//stConverter.stDC.u8BUC_DC_ONOFF= 0;
			stI2CREFMsg.u8Status &= nBUC_DC_OFF;
			 SetI2C(MODULE2);   
        }
		
  
    }    
    
}

static BYTE HTTPGet__u8SetBUCREF(void)
{
    BYTE *ptr;
    BYTE u8TempByte = 0; 


    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"BUCREF");
    if(ptr)
    {
      if(*(ptr+1)=='N')
       	{
            memcpypgm2ram(sBUCREF,"ON ",sizeof(sBUCREF));

			//stConverter.stDC.u8BUC_REF_ONOFF = 1;
			stI2CREFMsg.u8Status |= nBUC_REF_ON;
			 SetI2C(MODULE2);   

       	}
        else if ((*(ptr+1)=='F') && (*(ptr+2)=='F'))
        {
            memcpypgm2ram(sBUCREF,"OFF",sizeof(sBUCREF));
			//stConverter.stDC.u8BUC_REF_ONOFF= 0;
			stI2CREFMsg.u8Status &= nBUC_REF_OFF;
			 SetI2C(MODULE2);   
        }
		
    }

}


static BYTE HTTPGet__u8SetLNBREF(void)
{
    
    BYTE *ptr;
    BYTE u8TempByte = 0;  
    
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"LNBREF");
    if(ptr)
    {
      if(*(ptr+1)=='N')
       	{
            memcpypgm2ram(sLNBREF,"ON ",sizeof(sLNBREF));

			//stConverter.stDC.u8LNB_REF_ONOFF = 1;
			stI2CREFMsg.u8Status |= nLNB_REF_ON;
			 SetI2C(MODULE2);   

       	}
        else if ((*(ptr+1)=='F') && (*(ptr+2)=='F'))
        {
            memcpypgm2ram(sLNBREF,"OFF",sizeof(sLNBREF));
			//stConverter.stDC.u8LNB_REF_ONOFF= 0;
			stI2CREFMsg.u8Status &= nLNB_REF_OFF;
			 SetI2C(MODULE2);   
        }
		
    }    

	
    
}


static BYTE HTTPGet__u8ClearBUCIAm(void)
{
    
    BYTE *ptr;
    BYTE u8TempByte = 0;  
    
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"ClearBUCIAlm");
    if(ptr)
    {
		 stConverter.stDC.u8BUC_DC_OVERCurrent == 0; // clear alm
		 stI2CREFMsg.u8Status &= (~nBUC_OVER_CURRENT);
		 VOLCTRL_vSendI2C();	
    }    

	  
}

static BYTE HTTPGet__u8ClearLNBIAm(void)
{
    
    BYTE *ptr;
    BYTE u8TempByte = 0;  
    
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"ClearLNBIAlm");
    if(ptr)
    {
		 stConverter.stDC.u8LNB_DC_OVERCurrent == 0; // clear alm
		 stI2CREFMsg.u8Status &= (~nLNB_OVER_CURRENT);
		 VOLCTRL_vSendI2C();	
    }    

	  
}


BOOL HTTPGet__boDeviceConfig(void)
{  

    /* Frequency A */
    HTTPGet__u8SetUpCvtRFFreq();

     /* Frequency B */
    HTTPGet__u8SetDownCvtRFFreq();

     /* Attenuation A */
    HTTPGet__u8SetUpCvtAttn();

    /* Attenuation B */
    HTTPGet__u8SetDownCvtAttn();
    
    /* setpowera */
    HTTPGet__u8SetUpCvtSetPower();
    /* setpowerb */
    HTTPGet__u8SetDownCvtSetPower();
    
    /* ALCa */
    HTTPGet__u8SetUpCvtALC();
    
    /* ALCb */
    HTTPGet__u8SetDownCvtALC();
    
    /* Mutea */
    HTTPGet__u8SetUpCvtMute();
     
    /* Muteb */
    HTTPGet__u8SetDownCvtMute(); 
    
    /* 18Vctrl */
    HTTPGet__u8SetVOL18VDC();
    
    /* 24Vctrl  */
    HTTPGet__u8SetVOL24VDC();

	HTTPGet__u8SetLNBREF();

	HTTPGet__u8SetBUCREF();

	HTTPGet__u8ClearBUCIAm();

	HTTPGet__u8ClearLNBIAm();
	
}


BOOL HTTPExe_get_deviceinfo(void)
 {
    BYTE byte_temp,byte_temp2[2];
	BYTE temp_ID[4];
	BYTE *ptr;
	BYTE filename[20];
	DWORD temp = 0;
	char invalid_char=0,end;
    char toolong = 0;
	unsigned char i,k = 0;
	unsigned char count = 0;
	BYTE u8Temp;

	MPFSGetFilename(curHTTP.file, filename, 20);
	
	 if(!memcmppgm2ram(filename, "protect/config.htm", 18))
	{
        
        /* Handle Model and Serial configuration */
        HTTPGet__boInfoConfig();
						
        /* Handle Network configurations */
        HTTPGet__boNetworkConfig();
           
         /* Zj , Handle device related configurations */  
        HTTPGet__boDeviceConfig();

 	  } //END OF config.htm

	else if(!memcmppgm2ram(filename, "snmp/snmpconfig.htm", 19))
	{
        ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"MIP");
           if(ptr)
           {
                  if(StringToIPAddress(ptr, &Manager_IP))
                  {
                     Read2[0][0] = Manager_IP.v[0];
                     Read2[0][1] = Manager_IP.v[1];
                     Read2[0][2] = Manager_IP.v[2];
                     Read2[0][3] = Manager_IP.v[3];
                     SaveSetting();  
                  }
            }

	} //end of snmpconfig.htm

     else if(!memcmppgm2ram(filename, "protect/lut.htm", 15))
	 {
       ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"mac5");
           if(ptr)
           {
              AppConfig.MyMACAddr.v[4] = Hex2Int(*ptr)*16+Hex2Int(*(ptr+1));
              SaveAppConfig();
           }

       ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"mac6");
           if(ptr)
           {
              AppConfig.MyMACAddr.v[5] = Hex2Int(*ptr)*16+Hex2Int(*(ptr+1));
              SaveAppConfig();
           }

   		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"model");
        if(ptr)
        { 
			memcpy(MNString , ptr,sizeof(MNString) );
			SaveSetting();
		
        }

		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"serial");
        if(ptr)
        {
        	memcpy(SNString , ptr,sizeof(SNString) );
			SaveSetting();
        }

		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"wri2cdata");
		if(ptr)
		{
	        I2CSlaveAddress = Hex2Int(*ptr)*16+Hex2Int(*(ptr+1));
			
		  	I2CReceiveBuffer[0] = 0;
			
		  	for (i = 1; i < 15; i++)
		  	{

			`	if(((*(ptr+(i*2)) >= 0x03) && (*(ptr+(i*2))<='F')) && ((*(ptr+1+(i*2)) >= 0x03) && (*(ptr+1+(i*2))<='F')))
		  			I2CReceiveBuffer[i] = Hex2Int(*(ptr+(i*2)))*16+Hex2Int(*(ptr+1+(i*2)));
				else
					break;
	
		  	}
			 DelayMs(10);
		  	I2C_Send(I2CSlaveAddress, I2CReceiveBuffer, i+1);

			WebpageWriteI2CFlag = TRUE;
      }

		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"rdi2cdata");
		if(ptr)
		{
	        I2CSlaveAddress = Hex2Int(*ptr)*16+Hex2Int(*(ptr+1));
			
			RdI2CBuffer[0] = 0;
			RdI2CBuffer[1] = 0;
			RdI2CBuffer[2] = 0;

	
			I2C_Send(I2CSlaveAddress, (char*)&RdI2CBuffer, 1); //Notify Want to read I2C message
			I2C_Read(I2CSlaveAddress, RdI2CBuffer, 16);
		  

      }
/*
       ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"start");
       if(ptr)
       {
          if((*(ptr+1)<=0x39)&&(*(ptr+1)>=0x30))
            ostart = (*ptr-0x30)*10 + *(ptr+1)-0x30;
          else
            ostart = *ptr-0x30;
          Read2[1][1]=ostart;
          SaveSetting();
		  SSPALL_XEEWriteByte(EEADR_rfout_offset, ostart);
		  rfout_offset = ostart;
       }

        ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"end");
       if(ptr)
       {
          if((*(ptr+1)<=0x39)&&(*(ptr+1)>=0x30))
            oend = (*ptr-0x30)*10 + *(ptr+1)-0x30;
          else
            oend = *ptr-0x30;
          Read2[1][2]=oend;
          SaveSetting();
		  SSPALL_XEEWriteByte(EEADR_rfout_num, oend-ostart);
		  rfout_num = oend-ostart;
       }

        ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"ctemp");
       if(ptr)
       {
          if(((*(ptr)<=0x39)&&(*(ptr)>=0x30)) && ((*(ptr+1)<=0x39)&&(*(ptr+1)>=0x30)) )
		  {
			ctemp = (BYTE)atoi((char*)ptr);
			SSPALL_XEEWriteArray(EEADR_shutdown_temperature_degree,(BYTE*)&ctemp, 1);
			sspa_temp_shutdown_thd_degree = ctemp;
		  }
			
       }
*/

	}  // end of "protect/lut.htm"

	else if(!memcmppgm2ram(filename, "password.htm", 12))
	{
		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"oldp");
   			if(ptr)
			{ 
				i=0;
				while(*(ptr+i)!=0)
				{
					oldp[i]=*(ptr+i);
				
					if(
						(oldp[i]<0x30)
					  ||((oldp[i]>0x39)&&(oldp[i]<0x41))
					  ||((oldp[i]>0x5A)&&(oldp[i]<0x61))
					  ||(oldp[i]>0x7A)
                      )
						invalid_char = TRUE;
					if(i>7)
						toolong = TRUE;
					i++;

				}
				oldp[i]=0;
   			}         
		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"newp");
			if(ptr)
			{
				i=0;
				while(*(ptr+i)!=0)
				{
					newp[i]=*(ptr+i);
					if(
						(newp[i]<0x30)
					  ||((newp[i]>0x39)&&(newp[i]<0x41))
					  ||((newp[i]>0x5A)&&(newp[i]<0x61))
					  ||(newp[i]>0x7A)
                      )
						invalid_char = TRUE;
					if(i>7)
						toolong = TRUE;
                    i++;
				}
				newp[i]=0;
   			}  
		ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *)"rep");
			if(ptr)
			{
				i=0;
				while(*(ptr+i)!=0)
				{
					rep[i]=*(ptr+i);
					if(
						(rep[i]<0x30)
					  ||((rep[i]>0x39)&&(rep[i]<0x41))
					  ||((rep[i]>0x5A)&&(rep[i]<0x61))
					  ||(rep[i]>0x7A)
                      )
						invalid_char = TRUE;

					if(i>7)
						toolong = TRUE;

					i++;
				}
				rep[i]=0;
   			}  

		
 		if(invalid_char == TRUE)
		{
			webpassinfo.setpass = invalid_charactor;
			webpassinfo.setpasscolor = passred;
		}

		else if(toolong == TRUE)
		{
			webpassinfo.setpass = too_long;
			webpassinfo.setpasscolor = passred;
		}

		else if(strcmp(oldp,webpassinfo.webpassword))  //0 means equal
		{
			webpassinfo.setpass = old_password_wrong;
			webpassinfo.setpasscolor = passred;
		}

		else if(strcmp(newp,rep))
		{
			webpassinfo.setpass = repeat_password_different;
			webpassinfo.setpasscolor = passred;
		}
    
        else
		{
			webpassinfo.setpass = successful;
			webpassinfo.setpasscolor = passgreen;
			strcpy(webpassinfo.webpassword,newp);
			SaveSetting();
		}

	} // end of "password.htm"

 return HTTP_IO_DONE;
 }
