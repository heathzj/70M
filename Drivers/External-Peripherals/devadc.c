#include "Global.h"
#include "define.h"
#include <adc.h>
#include "devadc.h"
#include "devspi.h"
#include "RCULLAccess.h"

//BYTE 	temp1,temp2,temp3,temp4;

/*-----------------------------------------------------------------------------
FUNCTION NAME: GetOneCHADC0()

DESCRIPTION: 
    This function reads values from the ADC0 device.

INPUT PARAMETERS: 
    BYTE - Channel number of the ADC0 to be read.

RETURN:
    BYTE - ADC data read form teh channel

NOTES:

-----------------------------------------------------------------------------*/
BYTE GetOneCHADC0(BYTE ChannelNum)
{
    BYTE  datain, temp_data, temp_data1, temp_data2;
    WORD temp;

	// enable ADC0
    CS_ADC0 = CS_ENABLE;
    
    // write CH address to ADC0, start ADC convert, use internal REF
    // DONTC   ZERO   ADD2   ADD1   ADD0   REF   PM1   PM0
    // 0		    0		 					0	 0	   0
    datain = ((ChannelNum & 0x07) << 3) & 0x38;
    datain |= 0x04; // use external REF, it is 2.5V
    temp_data1 = ReadWriteSPI2(datain);
    temp_data2 = ReadWriteSPI2(datain);

//    CS_ADC0 = CS_DISABLE;

     DelayMS(1);

//    CS_ADC0 = CS_ENABLE;
    
    // first time is set channel number to start ADC, second time is start read ADC result
    temp_data1 = ReadWriteSPI2(datain);
    temp_data2 = ReadWriteSPI2(datain);

	// Analog input range is 0~5V, use AD8652 /2 is 0~2.5V
	// AD7888 internal REF is 2.5V, so ADC output range is 0~4095 (12Bits)
	// We use 1 byte to show this value so /16 is 0~255
    temp = (temp_data1 * 256) + temp_data2;
    temp /= 16;
    
    temp_data = (BYTE)temp;

    CS_ADC0 = CS_DISABLE;
    
    return temp_data;
}

WORD GetOneCHADC012Bits(BYTE ChannelNum)
{
    BYTE  datain, temp_data, temp_data1, temp_data2;
    WORD temp;

	// enable ADC0
    CS_ADC0 = CS_ENABLE;
    
    // write CH address to ADC0, start ADC convert, use internal REF
    // DONTC   ZERO   ADD2   ADD1   ADD0   REF   PM1   PM0
    // 0		    0		 					0	 0	   0
    datain = ((ChannelNum & 0x07) << 3) & 0x38;
    datain |= 0x04; // use external REF, it is 2.5V
    temp_data1 = ReadWriteSPI2(datain);
    temp_data2 = ReadWriteSPI2(datain);

//    CS_ADC0 = CS_DISABLE;

    DelayMS(1);

//    CS_ADC0 = CS_ENABLE;
    
    // first time is set channel number to start ADC, second time is start read ADC result
    temp_data1 = ReadWriteSPI2(datain);
    temp_data2 = ReadWriteSPI2(datain);

	// Analog input range is 0~5V, use AD8652 /2 is 0~2.5V
	// AD7888 internal REF is 2.5V, so ADC output range is 0~4095 (12Bits)
	// We use 1 byte to show this value so /16 is 0~255
    temp = (temp_data1 * 256) + temp_data2;
    
    temp_data = (BYTE)temp;

    CS_ADC0 = CS_DISABLE;
    
    return temp;
}

/*-----------------------------------------------------------------------------
FUNCTION NAME: GetOneCHADC1()

DESCRIPTION: 
    This function reads values from the ADC1 device.

INPUT PARAMETERS: 
    BYTE - Channel number of the ADC1 to be read.

RETURN:
    BYTE - ADC data read form teh channel

NOTES:

-----------------------------------------------------------------------------*/
BYTE GetOneCHADC1(BYTE ChannelNum)
{
    BYTE  datain, temp_data, temp_data1, temp_data2;
    WORD temp;

	// enable ADC1
    CS_ADC1 = CS_ENABLE;
    
    // write CH address to ADC0, start ADC convert, use internal REF
    // DONTC   ZERO   ADD2   ADD1   ADD0   REF   PM1   PM0
    // 0		    0		 					0	 0	   0
    datain = ((ChannelNum & 0x07) << 3) & 0x38;
    datain |= 0x04; // use external REF, it is 2.5V
    temp_data1 = ReadWriteSPI2(datain);
    temp_data2 = ReadWriteSPI2(datain);

//    CS_ADC1 = CS_DISABLE;

     DelayMS(1);

//    CS_ADC1 = CS_ENABLE;
    
    // first time is set channel number to start ADC, second time is start read ADC result
    temp_data1 = ReadWriteSPI2(datain);
    temp_data2 = ReadWriteSPI2(datain);

	// Analog input range is 0~5V, use AD8652 /2 is 0~2.5V
	// AD7888 internal REF is 2.5V, so ADC output range is 0~4095 (12Bits)
	// We use 1 byte to show this value so /16 is 0~255
    temp = (temp_data1 * 256) + temp_data2;
    temp /= 16;
    
    temp_data = (BYTE)temp;

    CS_ADC1 = CS_DISABLE;
    
    return temp_data;
}

WORD GetOneCHADC112Bits(BYTE ChannelNum)
{
    BYTE  datain, temp_data, temp_data1, temp_data2;
    WORD temp;

	// enable ADC1
    CS_ADC1 = CS_ENABLE;
    
    // write CH address to ADC0, start ADC convert, use internal REF
    // DONTC   ZERO   ADD2   ADD1   ADD0   REF   PM1   PM0
    // 0		    0		 					0	 0	   0
    datain = ((ChannelNum & 0x07) << 3) & 0x38;
    datain |= 0x04; // use external REF, it is 2.5V
    temp_data1 = ReadWriteSPI2(datain);
    temp_data2 = ReadWriteSPI2(datain);

//    CS_ADC1 = CS_DISABLE;

    DelayMS(1);

//    CS_ADC1 = CS_ENABLE;
    
    // first time is set channel number to start ADC, second time is start read ADC result
    temp_data1 = ReadWriteSPI2(datain);
    temp_data2 = ReadWriteSPI2(datain);

	// Analog input range is 0~5V, use AD8652 /2 is 0~2.5V
	// AD7888 internal REF is 2.5V, so ADC output range is 0~4095 (12Bits)
	// We use 1 byte to show this value so /16 is 0~255
    temp = (temp_data1 * 256) + temp_data2;
//    temp /= 16;
    
//    temp_data = (BYTE)temp;

    CS_ADC1 = CS_DISABLE;
    
    return temp;
}


WORD GetCurrentFromHexValue(BYTE hexvalue)
{
	WORD int_tmp, int_tmp1;
	
	int_tmp1 = (WORD)hexvalue * 20; // mV
	int_tmp = int_tmp1 * 10 / 85; // mA

	return int_tmp;
}

