#ifndef _UARTISR_H_
#define _UARTISR_H_


#include "HardwareProfile.h"


#define 	FIFO_SIZE 64




typedef struct uartDCB_s
{
	//BYTE dummy[8];
	//BYTE UARTFIFODataErrorCount;
	//BYTE UARTFramingErrorCount;
	//BYTE UARTParityErrorCount;
	//BYTE UARTOverrunErrorCount;
	//BYTE devname;
	BYTE* RXBuff;

	BYTE mode;
	volatile BYTE receiveflag;

	void (*uartinit)();
	void (*uartisr)();
	int (*uartread)();
	void (*uartwrite)(char*);
	//void (*uartwriterom)(rom char*);
	void (*uartfifoinit)();


} uartDBC_t;


extern uartDBC_t Uart0; 
extern uartDBC_t Uart1; 
extern uartDBC_t Uart2; 
extern uartDBC_t Uart3; 
extern uartDBC_t Uart4; 
extern uartDBC_t Uart5; 

void uart0init(uartDBC_t*,BYTE);
void uart1init(uartDBC_t*,BYTE );
void uart2init(uartDBC_t*,BYTE );
void uart3init(uartDBC_t*,BYTE );
void uart4init(uartDBC_t*,BYTE );
void uart5init(uartDBC_t*,BYTE );

void UART0write(BYTE*);
void UART1write(BYTE* );
void UART2write(BYTE*);
void UART3write(BYTE* );
void UART4write(BYTE* );
void UART5write(BYTE* );

void UARTISR0(void);
void UARTISR1(void);
void UARTISR2(void);
void UARTISR3(void);
void UARTISR4(void);
void UARTISR5(void);
void UART2ISR(void);

void InitFifo0(void);
void InitFifo1(void);
void InitFifo2(void);
void InitFifo3(void);
void InitFifo4(void);
void InitFifo5(void);




#endif // _UARTISR_H_

