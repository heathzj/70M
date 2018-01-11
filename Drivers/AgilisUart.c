/*
 * Copyright (C) 2012  ST Electronics (Satcom & Sensor Systems) Pte Ltd 
 *
 * Agilis UART Driver
 * 
 *
 */

#include "HardwareProfile.h"
#include "define.h"
#include "Global.h"
#include <usart.h>
#include "AgilisDriverManager.h"
#include "AgilisUart.h"
#include "UARTISR.h"
#include "AgilisProtocol.h"





uartDBC_t Uart0; 
uartDBC_t Uart1; 


// uart port 0  - connect to PC client
AgilisDriverDescriptor_t gUart0Table =
{
   	//(rom char*)"uart0", AgilisUart0Open, AgilisUart0Read, AgilisUart0Write, AgilisUart0ErrorReport, AgilisUart0Close
	(rom char*)"uart0", AgilisUart0Open, AgilisUart0Read, AgilisUart0Write
};

// uart port 1  - connect to ASRC/LCD client
AgilisDriverDescriptor_t gUart1Table =
{
   	//(rom char*)"uart1", AgilisUart1Open, AgilisUart1Ioctl, AgilisUart1Read, AgilisUart1Write, AgilisUart1ErrorReport, AgilisUart1Close
	(rom char*)"uart1", AgilisUart1Open, AgilisUart1Read, AgilisUart1Write
};

void AgilisUart0Init(UINT8 comMode)
{
	memset(&Uart0, 0, sizeof(Uart0));

	uart0init(&Uart0, comMode);

	// register Uart0 table to agilis driver manager
	AgilisDriverManagerRegister(&gUart0Table);
}


AgilisDriverDescriptor_t *AgilisUart0Open(rom char *name)
{
	return((AgilisDriverDescriptor_t *)&gUart0Table);
}


UINT16 AgilisUart0Read(void *pData, UINT16 u16Size)
{
    //pthread_mutex_lock(&mutex);

	if(pData && u16Size){
		if (RCSTA1bits.OERR)
		{
			RCSTA1bits.CREN = 0; // 
			RCSTA1bits.CREN = 1; // 
		}
    	// get receive data from interrupt buffer
		if(Uart0.receiveflag == 1)
		{
			Uart0.receiveflag = 0;
			u16Size = UARTBufferTask(pData, &agilisUART0RxCircBuf);
		}else
		    u16Size = 0;
	}else
		u16Size = 0;

    //pthread_mutex_unlock(&mutex);
    
    return u16Size;
}


UINT16 AgilisUart0Write(void *pData, UINT16 u16Size)
{
    //pthread_mutex_lock(&mutex);

	if(pData && u16Size){
		Uart0.uartwrite((char*)pData);
	}else
		u16Size = 0;
	
    //pthread_mutex_unlock(&mutex);
    
    return u16Size;
}



void AgilisUart1Init(UINT8 comMode)
{
	memset(&Uart1, 0, sizeof(Uart1));

	uart1init(&Uart1, comMode);

	// register Uart1 table to agilis driver manager
	AgilisDriverManagerRegister(&gUart1Table);
}


AgilisDriverDescriptor_t *AgilisUart1Open(rom char *name)
{
	return((AgilisDriverDescriptor_t *)&gUart1Table);
}


UINT16 AgilisUart1Read(void *pData, UINT16 u16Size)
{
    //pthread_mutex_lock(&mutex);

	if(pData && u16Size){
		if(RCSTA2bits.OERR)
		{
			RCSTA2bits.CREN = 0;
			RCSTA2bits.CREN = 1;
		}
    	// get receive data from interrupt buffer
		if(Uart1.receiveflag == 1)
		{
			Uart1.receiveflag = 0;

			u16Size = UARTBufferTask(pData, &agilisUART1RxCircBuf);
		}else
		    u16Size = 0;
	}else
		u16Size = 0;

    //pthread_mutex_unlock(&mutex);
    
    return u16Size;
}


UINT16 AgilisUart1Write(void *pData, UINT16 u16Size)
{
    //pthread_mutex_lock(&mutex);

	if(pData && u16Size){
		Uart1.uartwrite((char*)pData);
	}else
		u16Size = 0;
	
    //pthread_mutex_unlock(&mutex);
    
    return u16Size;
}



#if 0 // debug only

extern UINT8 gAgilisReadBuf[AGILIS_PROTOCOL_UARTBUF_SIZE];
extern UINT8 gAgilisWriteBuf[AGILIS_PROTOCOL_UARTBUF_SIZE];

static void UartPrintPgm(rom char* str)
{
	AgilisDriverDescriptor_t *pUartPort=NULL;
	pUartPort = AgilisDriverManagerOpen("uart0");
	if(pUartPort){
		strcpypgm2ram(gAgilisWriteBuf, str);
		pUartPort->Write(gAgilisWriteBuf, strlenpgm(str));
	}
} 

void AgilisUartTestWrite(rom char* pUartName, rom char *pData)
{
	UINT16 u16ByteSent, u16ByteRead, u16CmdLen;
	AgilisDriverDescriptor_t *pUartPort=NULL;
	pUartPort = AgilisDriverManagerOpen(pUartName);
	
	if(pUartPort){
		strcpypgm2ram(gAgilisWriteBuf, pData);
		strcatpgm2ram(gAgilisWriteBuf, "\r");
		u16CmdLen = strlen(gAgilisWriteBuf);
		u16ByteSent = pUartPort->Write(gAgilisWriteBuf, u16CmdLen );
		DelayMS(5);
	}
	
}

void AgilisUartTestRead(rom char* pUartName)
{
	UINT16 u16StrLen;
	AgilisDriverDescriptor_t *pUartPort=NULL;
	pUartPort = AgilisDriverManagerOpen(pUartName);
	
	if(pUartPort){
		memset(gAgilisReadBuf, 0, sizeof(gAgilisReadBuf));
		u16StrLen = pUartPort->Read(gAgilisReadBuf, 50);
		if(u16StrLen){
			strcpypgm2ram(gAgilisWriteBuf, pUartName);
			strcatpgm2ram(gAgilisWriteBuf, " received: ");
			strcat(gAgilisWriteBuf, gAgilisReadBuf);
			u16StrLen = strlen(gAgilisReadBuf);
 			pUartPort->Write(gAgilisWriteBuf, u16StrLen);
		}else{
			//UartPrintPgm("received nothing\r");
		}
	}
}

void AgilisUartTestDumpReadBuf(rom char* pUartName)
{
	UINT16 u16StrLen;
	AgilisDriverDescriptor_t *pUartPort=NULL;
	pUartPort = AgilisDriverManagerOpen(pUartName);
	
	if(pUartPort){
		memset(gAgilisWriteBuf, 0, sizeof(gAgilisWriteBuf));
		strcpypgm2ram(gAgilisWriteBuf, pUartName);
		strcatpgm2ram(gAgilisWriteBuf, ": ");
		strcat(gAgilisWriteBuf, gAgilisReadBuf);
		u16StrLen = strlen(gAgilisReadBuf);
		pUartPort->Write(gAgilisWriteBuf, u16StrLen);
	}
}

void debugPrintf2(rom char *str)
{
 	AgilisUartTestWrite((rom char*)"uart0", str);
}

void debugPrintfRAM(char *str)
{
	UINT16 u16ByteSent, u16ByteRead, u16CmdLen;
	AgilisDriverDescriptor_t *pUartPort=NULL;
	pUartPort = AgilisDriverManagerOpen("uart0");
	
	if(pUartPort){
		strcpy(gAgilisWriteBuf, str);
		strcatpgm2ram(gAgilisWriteBuf, "\r");
		u16CmdLen = strlen(gAgilisWriteBuf);
		u16ByteSent = pUartPort->Write(gAgilisWriteBuf, u16CmdLen );
		DelayMS(5);
	}
}

void debugPrintfByte(rom char *str, BYTE data)
{
	UINT16 u16ByteSent, u16ByteRead, u16CmdLen;
	char dataStr[3];

	AgilisDriverDescriptor_t *pUartPort=NULL;
	pUartPort = AgilisDriverManagerOpen("uart0");
	
	if(pUartPort){
		strcpypgm2ram(gAgilisWriteBuf, str);
		HEXto2ASC(data, dataStr);
		dataStr[2]=0;
		strcat(gAgilisWriteBuf, dataStr);
		strcatpgm2ram(gAgilisWriteBuf, "\r");
		u16CmdLen = strlen(gAgilisWriteBuf);
		u16ByteSent = pUartPort->Write(gAgilisWriteBuf, u16CmdLen );
		DelayMS(2);
	}
}

void debugPrintfWord(rom char *str, WORD data)
{
	UINT16 u16ByteSent, u16ByteRead, u16CmdLen;
	char dataStr[5];

	AgilisDriverDescriptor_t *pUartPort=NULL;
	pUartPort = AgilisDriverManagerOpen("uart0");
	
	if(pUartPort){
		strcpypgm2ram(gAgilisWriteBuf, str);
		HEXto2ASC(data>>8, &dataStr[0]);
		HEXto2ASC(data&0xFF, &dataStr[2]);
		dataStr[4]=0;
		strcat(gAgilisWriteBuf, dataStr);
		strcatpgm2ram(gAgilisWriteBuf, "\r");
		u16CmdLen = strlen(gAgilisWriteBuf);
		u16ByteSent = pUartPort->Write(gAgilisWriteBuf, u16CmdLen );
		DelayMS(2);
	}
}

void debugPrintfDword(rom char *str, DWORD data)
{
	UINT16 u16ByteSent, u16ByteRead, u16CmdLen;
	char dataStr[9];

	AgilisDriverDescriptor_t *pUartPort=NULL;
	pUartPort = AgilisDriverManagerOpen("uart0");
	
	if(pUartPort){
		strcpypgm2ram(gAgilisWriteBuf, str);
		HEXto2ASC((data>>24)&0xFF, &dataStr[0]);
		HEXto2ASC((data>>16)&0xFF, &dataStr[2]);
		HEXto2ASC((data>>8)&0xFF, &dataStr[4]);
		HEXto2ASC(data&0xFF, &dataStr[6]);
		dataStr[8]=0;
		strcat(gAgilisWriteBuf, dataStr);
		strcatpgm2ram(gAgilisWriteBuf, "\r");
		u16CmdLen = strlen(gAgilisWriteBuf);
		u16ByteSent = pUartPort->Write(gAgilisWriteBuf, u16CmdLen );
		DelayMS(2);
	}
}

#endif //#if 1
