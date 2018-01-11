/*
 * Copyright (C) 2012  SINGCOM Pte Ltd 
 *
 * UART Driver Header
 *
 */

#ifndef _UART_H_
#define _UART_H_

#include "DriverManager.h"


// UART configuration ioctl
typedef struct {
   UINT32    u32Value;                  // param for different uart config
} UartConfig_t;


// UART error report structure
typedef struct {
	UINT32	u32ParityErrorCnt;
   	UINT32  u32RxFrameErrorCnt;
   	UINT32  u32RxOverrunErrorCnt;
   	UINT32  u32TxOverrunErrorCnt;
} UartErrorReport_t;

typedef enum {
	UartStatus_Ok,
	UartStatus_Fail
}UartStatus_t;

enum {
	UART_CONFIG_MODE_RS232,
	UART_CONFIG_MODE_RS422,
	UART_CONFIG_MODE_RS485
};

enum {
	UART_CONFIG_BAUDRATE_9600,
	UART_CONFIG_BAUDRATE_38400,
	UART_CONFIG_BAUDRATE_115200
};

// UART configuration opcodes
enum {
   UART_CONFIG_SET_BAUDRATE,  // configure baud rate
   UART_CONFIG_SET_MODE      // configure RS232/422/485 mode
};


// UART 0 port
void Uart0Init(UINT8 comMode);
DriverDescriptor_t *Uart0Open(rom char *name);
UINT16 Uart0Ioctl(void *pData, UINT16 u16Size);
UINT16 Uart0Read(void *pData, UINT16 u16Size);
UINT16 Uart0Write(void *pData, UINT16 u16Size);
UINT16 Uart0Close(void);

// UART 1 port
void Uart1Init(UINT8 comMode);
DriverDescriptor_t *Uart1Open(rom char *name);
UINT16 Uart1Ioctl(void *pData, UINT16 u16Size);
UINT16 Uart1Read(void *pData, UINT16 u16Size);
UINT16 Uart1Write(void *pData, UINT16 u16Size);
UINT16 Uart1Close(void);

// UART 2 port
void Uart2Init(UINT8 comMode);
DriverDescriptor_t *Uart2Open(rom char *name);
UINT16 Uart2Ioctl(void *pData, UINT16 u16Size);
UINT16 Uart2Read(void *pData, UINT16 u16Size);
UINT16 Uart2Write(void *pData, UINT16 u16Size);
UINT16 Uart2Close(void);

// UART 3 port
void Uart3Init(UINT8 comMode);
DriverDescriptor_t *Uart3Open(rom char *name);
UINT16 Uart3Ioctl(void *pData, UINT16 u16Size);
UINT16 Uart3Read(void *pData, UINT16 u16Size);
UINT16 Uart3Write(void *pData, UINT16 u16Size);
UINT16 Uart3Close(void);

// UART 4 port
void Uart4Init(UINT8 comMode);
DriverDescriptor_t *Uart4Open(rom char *name);
UINT16 Uart4Ioctl(void *pData, UINT16 u16Size);
UINT16 Uart4Read(void *pData, UINT16 u16Size);
UINT16 Uart4Write(void *pData, UINT16 u16Size);
UINT16 Uart4Close(void);

// UART 5 port
void Uart5Init(UINT8 comMode);
DriverDescriptor_t *Uart5Open(rom char *name);
UINT16 Uart5Ioctl(void *pData, UINT16 u16Size);
UINT16 Uart5Read(void *pData, UINT16 u16Size);
UINT16 Uart5Write(void *pData, UINT16 u16Size);
UINT16 Uart5Close(void);

void UartTestWrite(rom char* pUartName, rom char *pData);
void UartTestRead(rom char* pUartName);


#endif // _UART_H_

