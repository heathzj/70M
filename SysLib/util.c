#include "Global.h"
#include "define.h"
#if defined(__18F97J60) || defined(_18F97J60)
#include "p18f97j60.h"
#include "TCPIP Stack/TCPIP.h"
#endif
#include "delays.h"
#include "DriverManager.h"
#include "DualUART.h"
#include "Util.h"

#if defined(__18F97J60) || defined(_18F97J60)
unsigned char L;
unsigned char tempvalue;
MPFS_HANDLE hMPFS1;
DWORD dwLastIP = 0;
#endif



WORD Util_u16ByteSwap(WORD u16Word)
{
	WORD u16NewWord;
	WORD u16NewWordLow;
	
	u16NewWord = u16Word;
	u16NewWordLow = u16Word;

	u16NewWordLow = (u16NewWordLow>>8) & 0x00ff;
	u16NewWord = (u16NewWord << 8)& 0xff00;
	u16NewWord =  u16NewWord | u16NewWordLow;


	return u16NewWord;

}

DWORD Util_u16DWORDSwap(DWORD u32Word)
{
	DWORD u32NewWordHigh;
	DWORD u32NewWordUp;
	DWORD u32NewWordMid;	
	DWORD u32NewWordLow;
	
	u32NewWordHigh = u32Word;
	u32NewWordLow = u32Word;
	u32NewWordUp = u32Word;
	u32NewWordMid = u32Word;	

	u32NewWordLow = (u32NewWordLow>>24) & 0x000000ff;
	u32NewWordMid = (u32NewWordMid>>8) & 0x0000ff00;

	u32NewWordUp = (u32NewWordUp<<8) & 0x00ff0000;
	u32NewWordHigh = (u32NewWordHigh<<24) & 0xff000000;	
	
	return (u32NewWordHigh | u32NewWordUp | u32NewWordMid | u32NewWordLow);


}



//String to unsigned long 
SHORT Util_u8String2int16(char* Data)
{
	//char temp[16];
	BYTE u8StrLen;
	BYTE u8Pos = 0;
	SHORT i16Ret = 0;
	SHORT i16Sign;

	if (*Data == '-')
	{
		i16Sign = -1;
		u8Pos = 1;

	}
	else if(*Data == '+')
	{
		i16Sign = 1;
		u8Pos = 1;

	}
	else if((*Data >= 0x30) && (*Data <= 0x39))
	{
		i16Sign = 1;
		u8Pos = 0;

	}


    while((*(Data+u8Pos) >= 0x30)  && (*(Data+u8Pos) <= 0x39) ) /* 0~9 */
    {
        i16Ret = i16Ret*10 + (*(Data+u8Pos) - '0');
        u8Pos++;
    }
	
	return (i16Ret * i16Sign);
}


//String to unsigned long
DWORD Util_u8String2DWORD(char* Data)
{
	//char temp[16];
	BYTE u8StrLen;
	BYTE u8Pos = 0;
	DWORD u32Ret = 0;


    while((*(Data+u8Pos) >= 0x30)  && (*(Data+u8Pos) <= 0x39) ) /* 0~9 */
    {
        u32Ret = u32Ret*10 + (*(Data+u8Pos) - '0');
        u8Pos++;
    }
	
	return u32Ret;
}


//limted to 1 digit fraction value eg 5.3.
BYTE Util_u8Float2String(float fvalue, char* Data)
{
	//char temp[16];
	BYTE u8StrLen;

	sprintf(Data,"%d.%d", (int)fvalue, (int)(fvalue*10.0) % 10) ;

	u8StrLen = strlen(Data);
	
	return u8StrLen;
}


//limted to 1 digit fraction value eg 5.3.
float Util_u8String2Float(char* Data)
{
	//char temp[16];
	BYTE u8StrLen;
	char* pcDotPos;
	BYTE u8Pos = 0;
	float fValue = 0;
	float fSign;

	if(*Data == '-') 
	{
		fSign = -1;
		u8Pos = 1;
	}

	else if (*Data == '+')
	{
		fSign = 1;
		u8Pos = 1;
	}	
	else
	{
		fSign = 1;
		u8Pos = 0;
	}

	//char *strchr (auto const char *s, auto unsigned char c);
	pcDotPos = strchr(Data, '.');
	if(pcDotPos == 0)
	{
	   while((*(Data+u8Pos) >= 0x30)  && (*(Data+u8Pos) <= 0x39) ) /* 0~9 */
     	{
			fValue = fValue*10 + (*(Data+u8Pos) - '0');
			u8Pos++;
		}
	}
	else
	{
	
		while( *(Data+u8Pos)!= '.')
		{
			fValue = fValue*10 + (*(Data+u8Pos) - '0');
			u8Pos++;
		}

		fValue = fValue + (*(Data+u8Pos+1) - '0') /10.0;

	}

	
	return fValue * fSign;
}


//limted to N digit fraction value eg 1234.567.
float Util_u8String2NFloat(char* Data)
{
	BYTE u8StrLen;
	char* pcDotPos;
	BYTE u8Pos = 0;
    
    BYTE u8FracPos = 0;
	float fValue = 0;
    float fModulo = 10.0;

	/* char *strchr (auto const char *s, auto unsigned char c); return: A pointer to the first occurrence of character in str.*/
    /*Find dot position */
	pcDotPos = strchr(Data, '.');
    
   
	if(pcDotPos == 0)  /*No dot, integer */
	{
		while( *(Data+u8Pos)!= 0)
		{
			fValue = fValue*10 + (*(Data+u8Pos) - '0');
			u8Pos++;
		}
	}
   
	else  /*dot found, Float type data */
	{
        /* Integer part */
		while( *(Data+u8Pos)!= '.')
		{
			fValue = fValue*10 + (*(Data+u8Pos) - '0');
			u8Pos++;
		}

        
        u8FracPos = u8Pos + 1; /* start from x.1
        /* Fractional part */
        while((*(Data+u8FracPos) >= 0x30)  && (*(Data+u8FracPos) <= 0x39) ) /* 0~9 */
        {
            fValue = fValue + (*(Data+u8FracPos) - '0') /fModulo;
            u8FracPos++;
            fModulo *= 10;
        }

	}

	
	return fValue;
}


unsigned char ASC2toHEX(unsigned char *asc)
{
	unsigned char hex, hex2;

	hex = asc[0] - '0';
	hex = hex<10?hex:hex-7;
	hex = hex<16?hex:hex-22;
	hex <<= 4;
	hex2 = asc[1] - '0';
	hex2 = hex2<10?hex2:hex2-7;
	hex2 = hex2<16?hex2:hex2-22;
	hex += hex2;	
	return hex;	
}

/*convert HEX to 2 ASC CODE*/
void HEXto2ASC(unsigned char hex, unsigned char *asc)
{	
	asc[0] = hex>>4;
	asc[0] = asc[0]<10?asc[0]+'0':asc[0]+'0'+7;
	asc[1] = hex&0x0F;
	asc[1] = asc[1]<10?asc[1]+'0':asc[1]+'0'+7;	
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: GetChecksum()

DESCRIPTION: 
    Calculates the checksum of the buffer

INPUT PARAMETERS: 
    None

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
/*
BYTE GetChecksum(void *p_buff, BYTE n)
{
    BYTE i,*ptr_byte;
    BYTE chksum;
       
    chksum = 0;
    ptr_byte = (BYTE*) p_buff;
    for(i=0;i<n;i++)
    {
        chksum += ptr_byte[i];
    }
    return chksum;
}
*/


/*-----------------------------------------------------------------------------
FUNCTION NAME: DelayMS()

DESCRIPTION: 
    This routine ntroduces NOP to delay

INPUT PARAMETERS:
    unsigned int - time in ms 

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void DelayMS(unsigned int ms)
{
    unsigned int i;
    
    for (i = 1; i <= ms; i++)
    {
        Delay1KTCYx(FREQ_TCY);      
    }
}

//calc_CRC - INTERNAL FUNCTION
//Purpose:	To calculate an 8-bit CRC based on a polynomial and the series
//				of data bytes
//Note: 		Polynomial used x^8 + x^5 + x^4 + 1 = 10001100
//Inputs:	A pointer to an array of the data bytes and an int saying how many
//				bytes there are in the data array
//Outputs:	An int8 which is the calculated CRC
/*
BYTE calc_CRC(WORD addr, WORD bytes)
{
	BYTE shift_register = 0, datab, bits;
	WORD i;

	for (i = 0; i < bytes; ++i)
	{
#if defined(__18F97J60) || defined(_18F97J60)
		XEEReadArray(addr + i, (BYTE *)&datab, 1);
#else

#endif
		shift_register += datab;

	}
	return shift_register;
} //calc_CRC
*/

int Hex2Int(char data)
{
  int byte1;
  if((data<=0x39)&&(data>=0x30))
  {
   byte1=data-0x30;
  }
  else if((data<=0x46)&&(data>=0x41))
  {
   byte1=data-0x41+10;
  }
  return byte1;
}

int Int2Hex(int data)
{
  char byte1;
  if((data<=9)&&(data>=0))
  {
   byte1=data+0x30;
  }
  else if((data<=15)&&(data>=10))
  {
   byte1= data -10 + 0x41;
  }
  return byte1;

}




unsigned float atof5(unsigned char* arraydata)//with 0.5 stepsize
{
 unsigned int int_data=0;
 unsigned char cnt=0,cnt2=0,point5=0;


while(*(arraydata+cnt)!=0x0)
{
  if((*(arraydata+cnt)=='.')&&((*(arraydata+cnt+1)=='5')))
  {
   point5=1;
   break;
  }
  else if((*(arraydata+cnt)=='.')&&((*(arraydata+cnt+1)=='0')))
  {
   point5=0;
   break;
  }
  else
  {
  	cnt++;
  }
}
while(cnt!=0)
{
  int_data = int_data*10 + *(arraydata+cnt2)-0x30;
  cnt --;
  cnt2++;

}
return (int_data + point5*0.5f);
}

unsigned float atof1(unsigned char* arraydata)//with 0.5 stepsize
{
 unsigned int int_data=0;
 unsigned char cnt=0,cnt2=0,point5=0;
 float pointvalue=0;

while((*(arraydata+cnt)!=0x0)&&(*(arraydata+cnt)!=0x0D))
{
  if((*(arraydata+cnt)=='.'))
  {
   pointvalue=*(arraydata+cnt+1)-0x30;
   pointvalue = pointvalue/10.0f;
   break;
  }

  else
  {
  	cnt++;
  }
}
while(cnt!=0)
{
  int_data = int_data*10 + *(arraydata+cnt2)-0x30;
  cnt --;
  cnt2++;

}
return (int_data + pointvalue);
}


#if defined(__18F97J60) || defined(_18F97J60)

#if 0
void CONFIG232(void)      
{
    MODE0 = 0;
    RXEN0 = 1;
    DXEN0 = 0;    

}


void CONFIG422(void)      
{
    MODE0 = 1;
    RXEN0 = 1;
    DXEN0 = 1;    

}


void CONFIG485Tx(void)    
{
    MODE0 = 1;
    RXEN0 = 0;
    DXEN0 = 1;    

}

void CONFIG485Rx(void)    
{
    MODE0 = 1;
    RXEN0 = 1;
    DXEN0 = 0;    

}

void CONFIG2322(void)      
{
	RXEN1=1;
	DXEN1=0;
	MODE1=0;
}

void CONFIG485Tx2(void)    
{
	RXEN1=0;
	DXEN1=1;
	MODE1=1;
}

void CONFIG485Rx2(void)    
{
	RXEN1=1;
	DXEN1=0;
	MODE1=1;
}
void CONFIGT(void)
{
 if(SerialModePin==RS232)
   CONFIG232();
 else if (SerialModePin==RS485)
   CONFIG485Tx();  
}
void CONFIGR(void)
{
 if(SerialModePin==RS232)
   CONFIG232();
 else if (SerialModePin==RS485)
   CONFIG485Rx();  
}
void CONFIGT2(void)
{
 if(SerialModePin2==RS232)
   CONFIG2322();
 else if (SerialModePin2==RS485)
   CONFIG485Tx2();  
}
void CONFIGR2(void)
{
 if(SerialModePin2==RS232)
   CONFIG2322();
 else if (SerialModePin2==RS485)
   CONFIG485Rx2();  
}
#endif


#if defined(STACK_USE_SNMP_SERVER)
int Load_config(void)
{
hMPFS1=MPFSOpenROM((ROM BYTE*)"parameter.htm");

	if(!hMPFS1 || hMPFS1 == 0xFF)
		return 0;

memset(&systeminfo1, 0, sizeof(systeminfo1));
memset(&systeminfo2, 0, sizeof(systeminfo2));

L=0;
while(systeminfo1.SYSDESCR1[L-1]!=0xD && (L < sizeof(systeminfo1.SYSDESCR1)))
{
 MPFSGet(hMPFS1,systeminfo1.SYSDESCR1+L);
 L++;
} 
systeminfo1.SYSDESCR1[L-1]=0;

MPFSGet(hMPFS1,&tempvalue);



L=0;
while(systeminfo1.SYSCONTACT1[L-1]!=0xD && (L < sizeof(systeminfo1.SYSCONTACT1)))
{
 MPFSGet(hMPFS1,systeminfo1.SYSCONTACT1+L);
 L++;
} 
systeminfo1.SYSCONTACT1[L-1]=0;

MPFSGet(hMPFS1,&tempvalue);



L=0;
while(systeminfo2.SYSNAME1[L-1]!=0xD && (L < sizeof(systeminfo2.SYSNAME1)))
{
 MPFSGet(hMPFS1,systeminfo2.SYSNAME1+L);
 L++;
} 
systeminfo2.SYSNAME1[L-1]=0;

MPFSGet(hMPFS1,&tempvalue);



L=0;
while(systeminfo2.SYSLOCATION1[L-1]!=0xD && (L < sizeof(systeminfo2.SYSLOCATION1)))
{
 MPFSGet(hMPFS1,systeminfo2.SYSLOCATION1+L);
 L++;
} 
systeminfo2.SYSLOCATION1[L-1]=0;

MPFSClose(hMPFS1);


	XEEBeginWrite(0x00F2);
	XEEWriteArray((BYTE*)&systeminfo1, 64);
	XEEBeginWrite(0x0133);
	XEEWriteArray((BYTE*)&systeminfo2, 64);

}


#if 0

int Load_config(void)
{
	hMPFS1=MPFSOpenROM((ROM BYTE*)"parameter.htm");

	//MPFSGetArray(hMPFS1,systeminfo1.SYSDESCR1,30);

	if(!hMPFS1)
		return 0;

	memset(&systeminfo1, 0, sizeof(systeminfo1));
	memset(&systeminfo2, 0, sizeof(systeminfo2));

L=0;

MPFSGetArray(hMPFS1,systeminfo1.SYSDESCR1,30);

MPFSGetArray(hMPFS1,systeminfo1.SYSCONTACT1,30);

MPFSGetArray(hMPFS1,systeminfo1.SYSCONTACT1,30);

MPFSGetArray(hMPFS1,systeminfo2.SYSNAME1,30);

MPFSGetArray(hMPFS1,systeminfo2.SYSLOCATION1,30);

/*
while((systeminfo1.SYSDESCR1[L]!=0xD)  && (L < sizeof(systeminfo1.SYSDESCR1)))
{
 MPFSGet(hMPFS1,systeminfo1.SYSDESCR1+L);
 L++;
} 
systeminfo1.SYSDESCR1[L]=0;


MPFSGet(hMPFS1,&tempvalue);

/*
L=1;
while(systeminfo1.SYSCONTACT1[L-1]!=0xD && (L < sizeof(systeminfo1.SYSCONTACT1)))
{
 MPFSGet(hMPFS1,systeminfo1.SYSCONTACT1+L-1);
 L++;
} 
systeminfo1.SYSCONTACT1[L-1]=0;


MPFSGet(hMPFS1,&tempvalue);



L=1;
while((systeminfo2.SYSNAME1[L-1]!=0xD) && (L < sizeof(systeminfo2.SYSNAME1)))
{
 MPFSGet(hMPFS1,systeminfo2.SYSNAME1+L-1);
 L++;
} 
systeminfo2.SYSNAME1[L-1]=0;

MPFSGet(hMPFS1,&tempvalue);



L=1;
while((systeminfo2.SYSLOCATION1[L-1]!=0xD) && (L < sizeof(systeminfo2.SYSLOCATION1)))
{
 MPFSGet(hMPFS1,systeminfo2.SYSLOCATION1+L-1);
 L++;
} 
systeminfo2.SYSLOCATION1[L-1]=0;


//MPFSGet(hMPFS1,&tempvalue);
//MPFSGet(hMPFS1,&modelflag);
//MPFSGet(hMPFS1,&Read2[4][1]);
//MPFSGet(hMPFS1,&Read2[4][2]);
*/


	MPFSClose(hMPFS1);
	XEEBeginWrite(0x00F2);
	XEEWriteArray((BYTE*)&systeminfo1, 64);
	XEEBeginWrite(0x0133);
	XEEWriteArray((BYTE*)&systeminfo2, 64);

}
#endif



#endif


void SaveAppConfig(void)
{
	// Ensure adequate space has been reserved in non-volatile storage to 
	// store the entire AppConfig structure.  If you get stuck in this while(1) 
	// trap, it means you have a design time misconfiguration in TCPIPConfig.h.
	// You must increase MPFS_RESERVE_BLOCK to allocate more space.
	#if defined(STACK_USE_MPFS) || defined(STACK_USE_MPFS2)
		if(sizeof(AppConfig) > MPFS_RESERVE_BLOCK)
			while(1);
	#endif

	#if defined(EEPROM_CS_TRIS)
	    XEEBeginWrite(0x0000);
	    XEEWrite(0x60);
	    XEEWriteArray((BYTE*)&AppConfig, sizeof(AppConfig));
    #else
	    SPIFlashBeginWrite(0x0000);
	    SPIFlashWrite(0x60);
	    SPIFlashWriteArray((BYTE*)&AppConfig, sizeof(AppConfig));
    #endif
}
void SaveSetting(void)
{
	XEEBeginWrite(0x00F2);
	XEEWriteArray((BYTE*)&MNString, sizeof(MNString));
	
	XEEBeginWrite(0x0133);
	XEEWriteArray((BYTE*)&SNString, sizeof(SNString));

 
#if defined(STACK_USE_SNMP_SERVER)
        XEEBeginWrite(0x00F2);
	    XEEWriteArray((BYTE*)&systeminfo1, 64);

        XEEBeginWrite(0x0133);
        XEEWriteArray((BYTE*)&systeminfo2, 64);
#endif

        XEEBeginWrite(0x0174);
        XEEWriteArray((BYTE*)Read2, sizeof(Read2));

        XEEBeginWrite(0x191);
        XEEWriteArray((BYTE*)webpassinfo.webpassword, sizeof(webpassinfo.webpassword));

}


// Writes an IP address to the LCD display and the UART1 as available
void DisplayIPValue(IP_ADDR IPVal)
{
//	printf("%u.%u.%u.%u", IPVal.v[0], IPVal.v[1], IPVal.v[2], IPVal.v[3]);
    BYTE IPDigit[4];
	BYTE i;


	for(i = 0; i < sizeof(IP_ADDR); i++)
	{
	    uitoa((WORD)IPVal.v[i], IPDigit);

		#if defined(STACK_USE_UART)
            
			putsUART(IPDigit);
            
		#endif


			if(i == sizeof(IP_ADDR)-1)
				break;
		

		#if defined(STACK_USE_UART)
			while(BusyUART());
            
			WriteUART('.');
            
		#endif
	}
}




#if 0

// Writes an IP address to the LCD display and the UART2 as available
void DisplayIPValue2(IP_ADDR IPVal)
{
//	printf("%u.%u.%u.%u", IPVal.v[0], IPVal.v[1], IPVal.v[2], IPVal.v[3]);
    BYTE IPDigit[4];
	BYTE i;

	for(i = 0; i < sizeof(IP_ADDR); i++)
	{
	    uitoa((WORD)IPVal.v[i], IPDigit);

		#if defined(STACK_USE_UART)
            
			putsUART2(IPDigit);
            
		#endif

		
			if(i == sizeof(IP_ADDR)-1)
				break;
		

		#if defined(STACK_USE_UART)
			while(BusyUART2());
            
			WriteUART2('.');
            
		#endif
	}

}

 int UpdataIP()
{
 		if(dwLastIP != AppConfig.MyIPAddr.Val)   
		{
			dwLastIP = AppConfig.MyIPAddr.Val;
			CONFIGT2();
		    putrsUART2((ROM char*)"\r\nNew IP Address: ");
			DisplayIPValue2(AppConfig.MyIPAddr);
        	putrsUART2((ROM char*)"\r\n");
            CONFIGR2();

			#if defined(STACK_USE_ANNOUNCE)
           
				AnnounceIP();
           
			#endif
           
		}
}


int Config_IP()
{
     unsigned long main_cnt=0;
     int main_part=0;
	 Comm0Mode485Tx();
     putrsUART("Press ESC Key to config IP :\r\n ");
	 DelayMS(1);
     while(main_part==0)
     {
	   Comm0Mode485Rx();
       switch(ReadUART())
	  {
		    case 0x1B:
            DoUARTConfig();
            main_part=1;
            break;

      }
      Nop();
      Nop();
      main_cnt++;
      // 3 seconds
      if (main_cnt>=1000000)
      {
       main_part=1;
	   Comm0Mode485Tx();
       putrsUART("Entering Main Program...\r\n ");
       DelayMS(1);
	   Comm0Mode485Rx();
      }
     }  

}

#endif
#endif

