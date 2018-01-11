/*-----------------------------------------------------------------------------
*
* Copyright (c) 2006-2009, ST Electronics (Satcom & Sensor Systems) Pte Ltd
* All rights reserved.
*
* DESCRIPTION:
* 
* PROJECT NAME: SSPA_RCU M&C Firmware  
*
* AUTHOR: Wu Zhixian
*
* DATE: 15/07/2009 
*
* ABSTRACT: 
*    This firmware is for RCU M&C borad using PIC18F8720 MCU.
*    It acts as a intermedia to realize communications 
*    between a VB written data fusing software running on a PC
*    and the RCU unit connected to M&C borad. 
*
*
*    The firmware receives commands through serial port and 
*    do corresponding actions, such as do auto/manual 
*    switch through CPLD etc.
*
* ---------------------------------------------------------------------------*/
/*---------------------
    REVISION HISTORY
---------------------*/
/*-----------------------------------------------------------------------------
NAME            DATE        BUGID#         
------------    ----------  ----------
DESCRIPTION
---------------------------------------
Wu Zhixian     15/07/2009                
First release version  
------------------------------------------------------------------------------*/
/*--------------
    INCLUDES 
--------------*/
#include "eeprom.h"
#include <p18f8722.h>

/*----------------------
    GLOBAL FUNCTIONS 
----------------------*/
/*-----------------------------------------------------------------------------
FUNCTION NAME: EEpromGet()

DESCRIPTION: 
    This function read one byte of data from EEPROM

INPUT PARAMETERS: 
    WORD - Address to be read

RETURN:
    BYTE - Byte read from the given address

NOTES:

-----------------------------------------------------------------------------*/
BYTE EEpromGet(WORD addr) 
{ /*
    volatile BYTE eepTemp; 
    UWORDbytes temp;
    temp.data=addr;
    EEADRH = temp.high;
    EEADR = temp.low; 
    EECON1bits.EEPGD = 0; 
    EECON1bits.CFGS = 0; 
    EECON1bits.RD = 1; 
    eepTemp = EEDATA; 
    return eepTemp; 
*/

    EEADRH = (unsigned int) (addr>>8);
    EEADR = (unsigned int) addr;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.RD = 1;    
    return EEDATA;

} 

/*-----------------------------------------------------------------------------
FUNCTION NAME: EEpromPut()

DESCRIPTION: 
    This function write one byte of data to EEPROM

INPUT PARAMETERS: 
    WORD - Address to be written
    BYTE - Byte to be written to that address

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void EEpromPut(WORD addr, BYTE data) 
{ 
    /*
    UWORDbytes temp;
    temp.data=addr;         //could use cast instead
    EEADRH = temp.high;
    EEADR = temp.low; 
    EEDATA = data; 
    EECON1bits.EEPGD = 0; 
    EECON1bits.CFGS = 0; 
    EECON1bits.WREN = 1; 

    DISABLE_INTERRUPTS();
    _asm
    MOVLW 0x55
    MOVWF EECON2,0
    MOVLW 0xAA
    MOVWF EECON2,0
    _endasm
    EECON1bits.WR=1;
    while (EECON1bits.WR == 1);
    ENABLE_INTERRUPTS();

    EECON1bits.WREN = 0;
*/
    
    EEADRH = (unsigned int) (addr>>8);
    EEADR = (unsigned int) addr;
    EEDATA = data;
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;
    PIR2bits.EEIF = 0;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 1;
    while (!PIR2bits.EEIF);    
    EECON1bits.WREN = 0;
     
} 

/*-----------------------------------------------------------------------------
FUNCTION NAME: EEpromRead()

DESCRIPTION: 
    This function reads several bytes of data from EEPROM

INPUT PARAMETERS: 
    WORD  - Address to be read
    BYTE* - Pointer to the data that needs to be filled
    WORD  - Total bytes to read

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void EEpromRead(WORD addr, BYTE *data, WORD len)
{
    WORD i;
    BYTE temp;
    for(i=0; i<len; i++)
    {
         
        temp=EEpromGet(addr++);
        data[i]=temp;
    }

}

/*-----------------------------------------------------------------------------
FUNCTION NAME: EEpromWrite()

DESCRIPTION: 
    This function write several bytes of data to EEPROM

INPUT PARAMETERS: 
    WORD - Address to be written
    BYTE - Pointer to the data to be written to that address
    WORD - Total bytes to write

RETURN:
    None

NOTES:

-----------------------------------------------------------------------------*/
void EEpromWrite(WORD addr, BYTE *data, WORD len)
{
    WORD i;
    BYTE temp;
    for(i=0; i<len; i++)
    {
        temp = data[i];
        EEpromPut(addr++,temp);
    }

}

