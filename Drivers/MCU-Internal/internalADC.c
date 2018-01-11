#include "Global.h"
#if defined(__18F97J60) || defined(_18F97J60)
#include "p18f97j60.h"
#endif
#include "timers.h"
#include "delays.h"
#include "define.h"
#include "devadc.h"
#include <math.h>
#include <adc.h>
#include "Hardwareprofile.h"


#pragma udata grp17
ADCInfo_t ADCInfo1;

unsigned int ADC_result;

void AD_init(void)
{

	ADCON1 = 0x00;//AVDD, AVSS, Temporarily set all channels to analog
	ADCON0 = 0x80|(AN4<<2);//default CH4 input 0100
	ADCON2 = 0b00111110;// Left Justified, 8 TAD, Fosc/64
	ADCON0bits.ADON = 1;
	
	TRISF = TRISF|0b01111110;//RF2-Rf6 input
	TRISF = TRISF&0b01111110;//RF0, RF1, Rf7 set to output
	PORTF = PORTF&0b10000011;//clear once
	
	TRISH = TRISH|0b11000000;//RH6, RH7 input
	TRISH = TRISH&0b11000000;//RH0- RH5 set to output 
	PORTH = PORTH&0b00111111;
}
/* // yt: unused
void AD_GET(void)
{
	ADCON0bits.ADON = 1;
	Delay10TCY();
	Delay10TCY();
	Delay10TCY();
	Delay10TCY();	Delay10TCY();
	Delay10TCY();	Delay10TCY();
	Delay10TCY();	Delay10TCY();
	Delay10TCY();
	ADCON0bits.GO = 1;
	while(ADCON0bits.GO)
	{
		Nop();
	//waiting for ad convertion to stop
	}

}
*/
void Read_ADC(unsigned int AN,unsigned int AD_Result_1, unsigned int AD_Result_2)
{

	ADCON0 = (ADCON0&0x11000011)|(AN<<2);//default CH5 input 0101

//	ADCON0bits.ADCAL = 1;

	ADCON0bits.ADON = 1;
	Delay10TCY();
	Delay10TCY();
	Delay10TCY();
	Delay10TCY();	Delay10TCY();
	Delay10TCY();	Delay10TCY();
	Delay10TCY();	Delay10TCY();
	Delay10TCY();

	ADCON0bits.GO = 1;
	while(ADCON0bits.GO)
	{
		Nop();
	//waiting for ad convertion to stop
	}
	ADCInfo1.AD_Result_L = ADRESL;
	ADCInfo1.AD_Result_H = ADRESH;
	ADCON0&=0x00000001;

//	return AD_Result_1,AD_Result_2;

}

unsigned int ADC_Value(unsigned int AN)
{
	unsigned int value,Lbyte=0,Hbyte=0;
	Delay10TCY();
	Read_ADC(AN,ADCInfo1.AD_Result_L,ADCInfo1.AD_Result_H);
	Hbyte=ADCInfo1.AD_Result_H;
	Lbyte=ADCInfo1.AD_Result_L;
	//value = (Hbyte << 8) | Lbyte;
	value = 0x0000|(Lbyte)|(Hbyte<<8);

	Nop();
	Nop();
	Nop();
	return value;
}


BYTE GetOneADC(BYTE	ChannelNum)
{

	unsigned int  temp_data;
	OpenADC(ADC_FOSC_RC	& ADC_RIGHT_JUST & ADC_12_TAD,
			ADC_INT_OFF & ADC_VREFPLUS_VDD & ADC_VREFMINUS_VSS, 8 );
 	
// 	SetChanADC(ChannelNum); 
//	ADCON0 = 0b00000000|(ChannelNum<<2);
//	Delay10TCYx(1); // Dalay for 10TCY
//	ConvertADC();
//	while (BusyADC());
	temp_data = ADC_Value(ChannelNum);

//	temp_data = ReadADC();
	CloseADC();
	   
//	temp_data >>= 2;  //10 bits --> 8 bits 
	return (BYTE)(temp_data);
}



