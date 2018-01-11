/*
 * Copyright (C) 2012  SINGCOM Pte Ltd 
 *
 *
 */

#ifndef _DEVICEMANAGER_H_
#define _DEVICEMANAGER_H_

#include "define.h"

//#include "TCPIP Stack/Tick.h"

#define RESPONSE_TIMER			100 	// once every 20 main() cycle
#define POLLING_TIMER			5000	// once every 100 main() cycle
#define SERVER_NOCOMM_COUNT		500 	// no comm after 10 seconds


#define MAX_CLIENT 					2 // PC and LCD
#define MAX_SERVER 					BUC_MAX_SIZE // 3 BUC
#define NUM_SERVER_INSTANCE	1  // 1 server instance to handle all PC/LCD/WiFi clients
#define NUM_CLIENT_INSTANCE	MAX_SERVER  // multiple client instances based on number of servers

// to support LCD client, add #define SUPPORT_UART1
// to support WiFi client, add #define SUPPORT_UART2


#define BUC_STATUS_AS_READY		(1<<0)	// BUC AS status is ready
#define BUC_STATUS_DA_READY		(1<<1)	// BUC DA status is ready
#define BUC_STATUS_PN_READY		(1<<2)	// BUC part number is ready
#define BUC_STATUS_SN_READY		(1<<3) 	// BUC serial number is ready
#define BUC_STATUS_VE_READY		(1<<4)	// BUC firmware version is ready
#define SSPA_STATUS_BV_READY	(1<<5)	// SSPA BV status is ready
#define SSPA_STATUS_RF_READY	(1<<6)	// SSPA RF status is ready
#define SSPA_STATUS_BS_READY	(1<<7)	// SSPA BS status is ready





#endif // _DEVICEMANAGER_H_


