#include "Global.h"
#include "define.h"
#include "devbt.h"

#if BluetoothDefine

int Config_Bluetooth(void)
{
	unsigned long main_cnt = 0;
	int main_part = 0;
	unsigned char byte_temp[39], temp_baud = BAUD_115200, byte_tmp, datatemp[3];

	datatemp[0] = '\n';
	datatemp[1] = '\r';
	datatemp[2] = 0;

	// wait bluetooth module stable
	DelayMS(500);
	// 1. Set baud rate: default baud rate of SPBT2532C2.AT module is 115200, then we set MCU baud rate also to 115200. 
	SetDualUartBaudRate(BAUD_115200);
	// 2. Check communication with Bluetooth module. 
	// Input command through MCU: AT+AB GetBDAddress
	// If get response like AT-AB BD_ADDR = [BD address], then communication is ok; if no response, then	set MCU baud rate to 9600 and try again.
	PrintUART(SIO2, 2, datatemp);
	DelayMS(1);
	memcpypgm2ram((void*)byte_temp, (ROM void *)"AT+AB GetBDAddress\n\r", 20);
	PrintUART(SIO2, 20, byte_temp);
	while (main_part == 0)
	{
		byte_tmp = ReadDataFromUart(DUAL_UART_B);
		// response should be "BD_ADDR = xxxxxxxx\n\r"
		if ((byte_tmp == 'B') || (byte_tmp == 'D') || (byte_tmp == '_') || (byte_tmp == 'A'))
		{
            main_part = 1;
		}
		Nop();
		Nop();
		main_cnt++;
		// 3 seconds
		if ((main_cnt >= 100000) && (temp_baud == BAUD_115200))
		{
			temp_baud = BAUD_9600;
			SetDualUartBaudRate(BAUD_9600);
			DelayMS(1);
			PrintUART(SIO2, 2, datatemp);
			DelayMS(1);
			memcpypgm2ram((void*)byte_temp, (ROM void *)"AT+AB GetBDAddress\n\r", 20);
			PrintUART(SIO2, 20, byte_temp);
			main_cnt = 0;
		}
		// 3 seconds
		if ((main_cnt >= 100000) && (temp_baud == BAUD_9600))
		{
			main_part = 1;
			return FALSE;
		}
	}  
	if (temp_baud != BAUD_9600)
	{
		// 5. Change MCU baud rate to 9600.
		SetDualUartBaudRate(BAUD_9600);
		// 3. If communication is ok, set bluetooth module default baud rate to 9600.
		// Input command through MCU: AT+AB ChangeDefaultBaud 9600
		// Response should be AT-AB Baudrate Changed
		PrintUART(SIO2, 2, datatemp);
		DelayMS(1);
		memcpypgm2ram((void*)byte_temp, (ROM void *)"AT+AB ChangeDefaultBaud 9600\n\r", 30);
		PrintUART(SIO2, 30, byte_temp);
		DelayMS(1);
		// 4. Change bluetooth module baud rate to 9600. 
		// Input command through MCU: AT+AB ChangeBaud 9600
		// Response should be AT-AB Baudrate Changed
		PrintUART(SIO2, 2, datatemp);
		DelayMS(1);
		memcpypgm2ram((void*)byte_temp, (ROM void *)"AT+AB ChangeBaud 9600\n\r", 23);
		PrintUART(SIO2, 23, byte_temp);
		DelayMS(1);
	}
	// 6. set blue tooth module PIN
	// Input command through MCU: AT+AB SetOrigPin [PIN], default PIN is Agilis, case sensitive
	// There is no response for this command.
	PrintUART(SIO2, 2, datatemp);
	DelayMS(1);
	memcpypgm2ram((void*)byte_temp, (ROM void *)"AT+AB Config PIN=0000\n\r", 23);
	PrintUART(SIO2, 23, byte_temp);
	DelayMS(1);
	PrintUART(SIO2, 2, datatemp);
	DelayMS(1);
	memcpypgm2ram((void*)byte_temp, (ROM void *)"AT+AB DefaultLocalName Agilis\n\r", 31);
	PrintUART(SIO2, 31, byte_temp);
	DelayMS(1);
	Enable_BlueTooth = TRUE;

	InitialiseDualUart();

	return TRUE;
}

#endif

