/*
 * Copyright (C) 2012  SINGCOM Pte Ltd 
 *
 * BUC Client Header
 *
 */

#ifndef _BUCCLIENT_H_
#define _BUCCLIENT_H_

#include "define.h"
#include "DeviceManager.h"

#define BUCCLIENT_SOURCE_ID 		"666"
#define BUCCLIENT_BROADCAST_ID 		"000"


void BUCClientInit(	const rom char *UartForBUCServer1,
					const rom char *UartForBUCServer2,
					const rom char *UartForBUCServer3);
void BUCClientPoll(void *p, UINT8 numServer);
void BUCClientRespond(void *p, UINT8 numServer);
void BUCClientResetServerInfo(BYTE serverNum);
void BUCClientSetBUCAttn(UINT8 serverNum, float fAttn);
void BUCClientSetBUCLO(UINT8 serverNum, UINT8 u8BUCLO);
void BUCClientSetBUCID(UINT8 ID);
void BUCClientSetBUCRFOnOff(UINT8 serverNum, UINT8 onOff);


#endif // _BUCCLIENT_H_
