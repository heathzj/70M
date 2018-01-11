/*
 * Copyright (C) 2012  ST Electronics (Satcom & Sensor Systems) Pte Ltd 
 *
 * Agilis Driver Manager
 * 
 * Manage Agilis drivers
 *
 */

#include "HardwareProfile.h"
#include "define.h"
#include "Global.h"
#include "AgilisDriverManager.h"


// table of devices
UINT8 gu8DevNum = 0;
AgilisDriverDescriptor_t  *gaDeviceTable[AGILISDRIVERMANAGER_MAX_NUM_DEVICES];

// Initialize the Agilis Driver Manager
//
void AgilisDriverManagerInit(void)
{
   // clear device table
   gu8DevNum = 0;
   memset(gaDeviceTable, 0, sizeof(gaDeviceTable));
   
   //gpAgilisDriverManagerSelf = AgilisDriverManagerDescriptor;
   // initialize mutex
   //pthread_mutex_init(&mutex, NULL);

   //return &AgilisDriverManagerDescriptor;
}



// open a device which has registered the driver in driver table
//

AgilisDriverDescriptor_t* AgilisDriverManagerOpen(rom char *pDevName)
{
   AgilisDriverDescriptor_t *pDevTable = NULL;
   UINT8 i;

   // set mutex
   //pthread_mutex_lock(&mutex);

   // check if agilis driver manager ownself
   //if (memcmp(AgilisDriverManagerDescriptor.DevName, pDevName, strlen(AgilisDriverManagerDescriptor.name)) == 0) {
   //   pDevTable = (AgilisDriverDescriptor_t *) &AgilisDriverManagerDescriptor;
   //} else {
      // check the device table
      for (i = 0; i < gu8DevNum; i++) {
         if (memcmppgm((rom void*)gaDeviceTable[i]->pDevName, (rom void*)pDevName, strlenpgm(gaDeviceTable[i]->pDevName)) == 0) {

            // send device open request
            pDevTable = gaDeviceTable[i];
            if (pDevTable->Open) {
               //pthread_mutex_unlock(&mutex);
               pDevTable = pDevTable->Open(pDevName);
               return pDevTable;
            }
            break;
         }
      }
   //}

   // release mutex
   //pthread_mutex_unlock(&mutex);

   return pDevTable;
}


// registers a driver table with the Agilis Driver Manager
//
void AgilisDriverManagerRegister(AgilisDriverDescriptor_t *pDevTable)
{
   // set mutex
   //pthread_mutex_lock(&mutex);

   // update the gaDeviceTable
   gaDeviceTable[gu8DevNum] = (AgilisDriverDescriptor_t *) pDevTable;
   gu8DevNum++;


   // release mutex
   //pthread_mutex_unlock(&mutex);

   // after registration, inform all other devices of arrival
   /*
   if (fInform) {
      AgilisDriverManagerIoctl_t ioctl = { DEV_IOCTL_ARRIVAL, 0 };
      ioctl.param = (DWORD) devd;
      AgilisDriverManagerSelfIoctl(&ioctl, sizeof(ioctl));
   }
   */
}



// yt: currently do not need driver manager self instance
//     as used for iterating ioctl to all devices only
/*
AgilisDriverDescriptor_t *gpAgilisDriverManagerSelf = NULL;

// device manager descriptor self table

AgilisDriverDescriptor_t AgilisDriverManagerDescriptor = {
   "devm", AgilisDriverManagerSelfOpen, AgilisDriverManagerSelfIoctl, NULL, NULL, AgilisDriverManagerSelfClose
};

// Ioctl to all drivers registered in the driver table
// yt: current do not require to ioctl to all drivers at the same time
WORD AgilisDriverManagerSelfIoctl(void *pData, WORD size)
{
   AgilisDriverManagerIoctl_t *pIoctl = pData;
   int i;

   // set mutex
   //pthread_mutex_lock(&mutex);

   if (((pIoctl->dev_op == DEV_IOCTL_ATTACH)  && (pIoctl->param == 0)) ||
       ((pIoctl->dev_op == DEV_IOCTL_SUSPEND) && (pIoctl->param))      ||
      ) {
      // broadcast IOCTL in reverse order (highest-level devices first)
      for (i = gu8DevNum - 1; i >= 0; i--)
         if (gaDeviceTable[i]->Ioctl) gaDeviceTable[i]->Ioctl(data, size);
   } else {
      // broadcast IOCTL in forward order (lowest-level devices first)
      for (i = 0; i < gu8DevNum; i++)
         if (gaDeviceTable[i]->Ioctl) gaDeviceTable[i]->Ioctl(data, size);
   }

   // release mutex
   //pthread_mutex_unlock(&mutex);

   return size;
}

// Open the Agilis driver manager itself
AgilisDriverDescriptor_t* AgilisDriverManagerSelfOpen(CHAR8 *pDevName)
{
   // send device open request to device manager
   if (gpAgilisDriverManagerSelf)
      return gpAgilisDriverManagerSelf->Open(pDevName);
   else
      return NULL;
}

// Close the Agilis driver manager itself
//
UINT16 AgilisDriverManagerSelfClose(void)
{
   return 1;
}

*/
