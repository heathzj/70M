/*
 * Copyright (C) 2012  SINGCOM Pte Ltd 
 *
 * Driver Manager Header
 *
 */

#ifndef _DEV_H_
#define _DEV_H_

#include "GenericTypeDefs.h"

#define DRIVERMANAGER_MAX_NUM_DEVICES    4

// device driver descriptor
typedef struct _DriverDescriptor_t {
   rom char *pDevName;
   struct _DriverDescriptor_t *(*Open) (rom char *pDevName);
   //WORD (*Ioctl)(void *pData, UINT16 u16Size);
   WORD (*Read) (void *pData, UINT16 u16Size);
   WORD (*Write)(void *pData, UINT16 u16Size);
   //WORD (*ErrorReport)(void *pData, UINT16 u16Size);
   //WORD (*Close)(void);
} DriverDescriptor_t;



void 						DriverManagerInit(void);
void     					DriverManagerRegister (DriverDescriptor_t *pDevTable);
DriverDescriptor_t  *DriverManagerOpen     (rom char *name);
UINT16	 					DriverManagerClose    (void);


#endif /* _DEV_H_ */
