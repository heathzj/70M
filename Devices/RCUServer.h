#ifndef _RCUSERVER_H_
#define _RCUSERVER_H_

#include "define.h"


#define RCU_SERVER_UART_PORT_FOR_CLIENT_1 "uart0" // uart port connected to client 1 (PC/ASRC)
#define RCU_SERVER_UART_PORT_FOR_CLIENT_2 "uart1" // uart port connected to client 2 (PC/ASRC)
#define RCU_SERVER_UART_PORT_FOR_SERVER_1 "uart2" // uart port connected to server 1 (BUC-1)
#define RCU_SERVER_UART_PORT_FOR_SERVER_2 "uart3" // uart port connected to server 2 (BUC-2)

#define RCU_SERVER_BUC_UART_PORT_0	0
#define RCU_SERVER_BUC_UART_PORT_1	1


void RCUServerInit(rom char *UartForPCClient, 
				   rom char *UartForLCDClient);




#endif // _RCUSERVER_H_
