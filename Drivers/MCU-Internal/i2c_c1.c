#include "define.h"
#include "Delay.h"
#include "oled_c1.h"

#include "i2c_c1.h"

unsigned char I2CReceiveBuffer[16];

extern tstI2CMessage  stI2CUpCvtMsg;
//*************************************************************************
//                          I2C_Send
//
// Inputs:
//         char Address  - Address to write data to
//         char *Data    - Pointer to buffer
//         char Num      - Number of bytes to send
//*************************************************************************
char I2C_Send(char Address,char *Data,char Num)
{
 i2cstart();

 //-- Send Address
 i2csendbyte(Address & 0xFE);   //-- Lowest bit = 0 => WRITE
 if(!i2cgetack())
 {
  i2cstop();
  return(0);
 }

 while(Num--)
 {
  i2csendbyte(*Data);
  if(!i2cgetack())
  {
   i2cstop();
   return(0);
  }
  Data++;
 }
 i2cstop();
 return(1);
}
//************** END OF I2C_Send

//*************************************************************************
//            char I2C_Read(char Address,char *data, char Num)
//*************************************************************************
char I2C_Read(char Address,char *Data, char Num)
{
 i2cstart();

 //-- Send Address
 i2csendbyte(Address | 0x01);   //-- Lowest bit = 1 => READ

 if(!i2cgetack())
 {
  i2cstop();
  return(0);
 }

 while(Num--)
 {
  *Data=i2cgetbyte();
  Data++;

  if(Num > 0)
  {
   i2csendack();
  }
 }
 i2csendnack();
 i2cstop();
 return(1);

}

//*************************************************************************
//                        i2csendbyte
//*************************************************************************
char i2csendbyte(char Byte)
{
 char count;
 SDA=I2CLOW;
 SCL=I2CLOW;

 i2cdelay(I2CCLOCKLOW);         //-- Minimum Clock Low Time

 for(count=8;count>0;count--)   //-- Send 8 bits of data
 {
  if( (Byte & 0x80)== 0)        //-- Get the Bit
  {
   SDA=I2CLOW;                  //-- Ensure Port pin is low
   SDA_TRIS=I2CLOW;             //-- Lower pin if bit = 0
  }
  else
  {
   SDA_TRIS=I2CHIGH;            //-- Release pin if bit = 1
  }
  Byte=Byte<<1;                 //-- Shift next bit into position
  i2cclock();                   //-- Pulse the clock
 }
 SDA_TRIS=I2CHIGH;              //-- Release data pin for ACK
 return(1);
}
//************** END OF i2csendbyte

//*************************************************************************
//                      char i2cgetbyte(void)
//
//  Reads in a byte from the I2C Port
//*************************************************************************
char i2cgetbyte(void)
{
 char count,Byte=0;
 SDA=I2CLOW;
 SCL=I2CLOW;

 i2cdelay(I2CCLOCKLOW);         //-- Minimum Clock Low Time

 for(count=8;count>0;count--)   //-- Read 8 bits of data
 {
  Byte=Byte <<1;
  SDA_TRIS=I2CHIGH;            //-- Release pin so data can be recieved
  if(i2creadbit())
  {
   Byte +=1;
  }
 }
 return(Byte);
}


//*************************************************************************
//                           i2cstart
//*************************************************************************
void i2cstart(void)
{
 //-- Ensure pins are in high impedance mode --
 SDA_TRIS=I2CHIGH;
 SCL_TRIS=I2CHIGH;
 SCL=I2CLOW;
 SDA=I2CLOW;
 i2cdelay(I2CSTARTDELAY);

 //-- Generate the start condition
 SDA_TRIS=I2CLOW;
 SDA=I2CLOW;
 i2cdelay(I2CSTARTDELAY);
 SCL_TRIS=I2CLOW;
 i2cdelay(I2CCLOCKLOW);         //-- Minimum Clock Low Time

}
//************** END OF i2cstart

//*************************************************************************
//                           i2cstop
//*************************************************************************
void i2cstop(void)
{
  //-- Generate Stop Condition --
/*
 SDA_TRIS=I2CLOW;
 SCL_TRIS=I2CHIGH;
 i2cdelay(I2CSTOPDELAY);
 SDA_TRIS=I2CHIGH;
*/
 SCL=I2CLOW;
 i2cdelay(I2CSTOPDELAY);
 SDA=I2CLOW;
 SDA_TRIS=I2CLOW;
 i2cdelay(I2CSTOPDELAY);
 SCL=I2CHIGH;
 i2cdelay(I2CSTOPDELAY);
 SDA=I2CHIGH;

}
//************** END OF i2cstop

//*************************************************************************
//                          i2cclock
//*************************************************************************
void i2cclock(void)
{
 i2cdelay(I2CDATASETTLE);       //-- Minimum Clock Low Time
 SCL_TRIS=I2CHIGH;              //-- Release clock
 i2cdelay(I2CCLOCKHIGH);        //-- Minimum Clock High Time
 SCL_TRIS=I2CLOW;               //-- Lower the clock
 i2cdelay(I2CCLOCKLOW);         //-- Minimum Clock Low Time
}
//************** END OF i2cclock


//*************************************************************************
//                          i2creadbit
//*************************************************************************
char i2creadbit(void)
{
 char Data=0;
 i2cdelay(I2CDATASETTLE);       //-- Minimum Clock Low Time
 SCL_TRIS=I2CHIGH;              //-- Release clock
 i2cdelay(I2CHALFCLOCK);        //-- 1/2 Minimum Clock High Time
 if(SDA !=0 ) 
	Data=1;           //-- READ in the data bit
 i2cdelay(I2CHALFCLOCK);        //-- 1/2 Minimum Clock High Time
 SCL_TRIS=I2CLOW;               //-- Lower the clock
 i2cdelay(I2CCLOCKLOW);         //-- Minimum Clock Low Time
 return(Data);
}
//************** END OF i2cclock


//*************************************************************************
//                           i2cgetack
//*************************************************************************
char i2cgetack(void)
{
 SDA=I2CLOW;
 SCL=I2CLOW;
 SCL_TRIS=I2CLOW;                 //-- Ensure clock is low
 SDA_TRIS=I2CHIGH;                //-- Release the Data pin so slave can ACK
 SCL_TRIS=I2CHIGH;                //-- raise the clock pin
 i2cdelay(I2CHALFCLOCK);          //-- wait for 1/2 the clock pulse
 if(SDA)                          //-- sample the ACK signal
 {
  return(0);                      //-- No ACK so return BAD
 }
 i2cdelay(I2CHALFCLOCK);          //-- Else wait for rest of clock
 SCL_TRIS=I2CLOW;                 //-- Finish the clock pulse
 i2cdelay(I2CCLOCKLOW);           //-- Minimum Clock Low Time
 i2cdelay(I2CCLOCKLOW);           //-- Minimum Clock Low Time
 return(1);
}
//************** END OF i2cgetack


//*************************************************************************
//                   void i2csendack(void)
//*************************************************************************
void i2csendack(void)
{
 //--- Send Ack to slave except for last time ---
 SDA=0;
 SDA_TRIS=I2CLOW;              //-- Send ACK
 i2cdelay(I2CDATASETTLE);      //-- Give it time to settle
 i2cclock();                   //-- Pulse the clock
 SDA_TRIS=I2CHIGH;             //-- Release ACK
 i2cdelay(I2CDATASETTLE);      //-- Gap between next byte
}
//************** END OF i2csendack


//*************************************************************************
//                   void i2csendnack(void)
//*************************************************************************
void i2csendnack(void)
{
 //--- Send NAck to slave except for last time ---
 SDA=1;
 SDA_TRIS=I2CLOW;              //-- Send NACK
 i2cdelay(I2CDATASETTLE);      //-- Give it time to settle
 i2cclock();                   //-- Pulse the clock
 SDA_TRIS=I2CHIGH;             //-- Release ACK
 i2cdelay(I2CDATASETTLE);      //-- Gap between next byte
}
//************** END OF i2csendnack


//*************************************************************************
//                           i2cdelay
//
// This delay is approx us plus the function call delays
// Should be close enough for I2C
//*************************************************************************
void i2cdelay(char delay)
{
	Delay10us(delay);
// DelayMs(delay);  //-- For Debug
}
//************** END OF i2cdelay



// typedef union
// {
    // unsigned long u32Freq;
    // unsigned char u8Freq[4];
// }tunFreq;

// typedef union
// {
    // unsigned short int u16Atten;
    // unsigned char u8Atten[2];
// }tunAtten;

// typedef struct
// {
	// unsigned char Updateflag;   //BYTE 0
	// unsigned char LockStatus;   //BYTE 1
	// tunFreq       unRfFreq;     //BYTE 2-5 consider union here
    // tunAtten      unAtten;      //BYTE 6-7 consider union here

// }tstI2CMessage;

void SetI2C(unsigned char module)
{
	int length;
	BYTE abTemp[30];
	abTemp[0] = 0x00; //insert a null before I2c Send


	if (module == MODULE0)
	{
		length = sizeof(tstI2CMsg);
        
        stI2CUCMsg.u8CtrlStatus |= nI2C_WRITE;

		memcpy(abTemp+1,(char*)&stI2CUCMsg, length );
		
		I2C_Send(I2C_UPCVT_ADDR, (char*)&abTemp, length+1 );
	}
	else if(module == MODULE1)
	{
		length = sizeof(tstI2CMsg);
        
        stI2CDCMsg.u8CtrlStatus |= nI2C_WRITE;
        
		memcpy(abTemp+1,(char*)&stI2CDCMsg, length );
		
		I2C_Send(I2C_DownCVT_ADDR, (char*)&abTemp, length+1 );
	}
	else if(module == MODULE2)
	{
		length = sizeof(tstI2CMsgVOL);
        
        stI2CREFMsg.u8Status |= nI2C_WRITE;
        
		memcpy(abTemp+1,(char*)&stI2CREFMsg, length );
		
		I2C_Send(I2C_REF_ADDR, (char*)&abTemp, length+1 );
	}

	
}

