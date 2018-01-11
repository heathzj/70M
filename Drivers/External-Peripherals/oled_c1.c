#include "define.h"
#include "i2c_c1.h"


#include "oled_c1.h"





rom unsigned char CGRAM[2][8] = {{0x04,0x0E,0x15,0x04,0x04,0x04,0x04,0x04}, {0x04,0x15,0x0E,0x04,0x04,0x04,0x04,0x04}};

void OLED_vSetKepad(void)
{
	UPKEY_TRIS = 1;
	DOWNKEY_TRIS = 1;
	LEFTKEY_TRIS = 1;
	RIGHTKEY_TRIS = 1;
	ENTERKEY_TRIS = 1;
	CANCELKEY_TRIS = 1;

	CONVERTERA_STATUS_TRIS = 1;
	CONVERTERB_STATUS_TRIS = 1;

}

void OLED_vSetIO(void)
{
	OLED_RS_TRIS = 0;
	OLED_RW_TRIS = 0;
	OLED_EN_TRIS = 0;
	OLED_DB7_TRIS = 0;
	OLED_DB6_TRIS = 0;
	OLED_DB5_TRIS = 0;
	OLED_DB4_TRIS = 0;
	OLED_DB3_TRIS = 0;
	OLED_DB2_TRIS = 0;
	OLED_DB1_TRIS = 0;
	OLED_DB0_TRIS = 0;

}

void OLED_vEnableInterrupt(void)
{
	PIE1bits.TMR2IE = 0;  // disable Timer2 interrupt
	PIR1bits.TMR2IF = 0;
	IPR1bits.TMR2IP = 0; // set Timer2 interrupt to low interrupt




	INTCON3bits.INT1IE = 1; // enable key interrupt
	INTCON3bits.INT1IP = 0; // set key interrupt to low interrupt
	INTCON2bits.INTEDG1 = 1; // 1 = Interrupt on rising edge
	//	INTCON2bits.INTEDG1 = 0; // 0 = Interrupt on falling edge
	TRISBbits.TRISB1 = 1; // RB1 input, INT1
	ADCON0bits.ADON = 0;
	ADCON1 |= 0x0F; // set all IO pin to digital

}

void CheckBusy()
{
	unsigned char temp;

	OLED_BUS_W = 0xff;
	OLED_RS = 0;
	OLED_RW = 1;
	OLED_BUS_TRIS = 0xFF;
	do
	{
		OLED_EN = 1;
		Nop(); /* zj */
		temp = OLED_DB7_R;
		OLED_EN = 0;
	}while(temp);
	OLED_BUS_TRIS = 0;
}

void WriteIns(char instruction)
{
	CheckBusy();
	OLED_RS = 0;
	OLED_RW = 0;
	OLED_EN = 1;
	Nop(); /* zj */
	OLED_BUS_W = instruction;
	OLED_EN = 0;
}
void WriteData(char data1)
{
	CheckBusy();
	OLED_RS = 1;
	OLED_RW = 0;
	Nop(); /* zj */
	OLED_EN = 1;
	Nop(); /* zj */
	OLED_BUS_W = data1;
	OLED_EN = 0;
	
	Nop(); /* zj */
}
unsigned char ReadData(void)
{
	unsigned char temp;

	OLED_BUS_TRIS = 0xFF;
	OLED_RS = 1;
	OLED_RW = 1;
	OLED_EN = 1;
	Nop(); /* zj */
	temp = OLED_BUS_R;
	OLED_EN = 0;
	OLED_BUS_TRIS = 0;
	CheckBusy();

	return temp;
}

void WriteString(unsigned char count,unsigned char * MSG)
{
	unsigned char i;
	for(i = 0; i < count; i++)
	{
		if ((MSG[i] >= ' ') && (MSG[i] <= 'z'))
		{
			WriteData(MSG[i]);
		}
	}
}
void LCDWriteString(unsigned char * MSG)
{
	unsigned char temp;
	
	temp = *MSG;
	while (temp)
	{
		if ((temp >= ' ') && (temp <= 'z'))
		{
			WriteData(temp);
		}
		MSG++;
		temp = *MSG;	
	}
}

void DRI_vPrintCGRAM(unsigned char number1)
{
	unsigned char i;
	WriteIns(0x40); //SET CG_RAM ADDRESS 000000
	for(i = 0;i<=24;i++)
	{
		WriteData(CGRAM[number1][i]);
	}
}

void DRI_vLCDClear(void)
{
	WriteIns(0x01); //Clear Display
}

void DRI_vLCDReturnhome(void)
{
	WriteIns(0x02); //Return Home
}
void DRI_vLCDEntryMode(void)
{
	WriteIns(0x06); //Entry Mode Set, address increment & Shift off
}

void DRI_vLCDDisplay(unsigned char displayflag, unsigned char cusorflag, unsigned char blinkflag)
{
	unsigned char temp = 0x08;
	
	if (displayflag == TRUE)
	{
		temp |= 0x04; // display ON
	}
	if (cusorflag == TRUE)
	{
		temp |= 0x02; // cusor ON
	}
	if (blinkflag == TRUE)
	{
		temp |= 0x01; // Blink ON
	}
	WriteIns(temp); //Display ON/OFF control,Display ON,Cursor&Blink OFF
}

void Initial_LCD(void)
{
	CurrentMenu = MENU0;
	LastMenu = CurrentMenu;


	WriteIns(0x38); //function set,8-bit transfer,2-lines display & 5*8 dot characteristic, font 00
	WriteIns(0x38); //function set,8-bit transfer,2-lines display & 5*8 dot characteristic, font 00
	WriteIns(0x38); //function set,8-bit transfer,2-lines display & 5*8 dot characteristic, font 00
	WriteIns(0x38); //function set,8-bit transfer,2-lines display & 5*8 dot characteristic, font 00
	WriteIns(0x0C); //Display ON/OFF control,Display ON,Cursor&Blink OFF
	WriteIns(0x06); //Entry Mode Set, address increment & Shift off
	WriteIns(0x02); //Return Home
	WriteIns(0x01); //Clear Display
}

void PrintCompanyLCD(void)
{
	unsigned char i, temp, temp1;

	for (i = 0; i < 40; i++)
	{
		temp = 0x80 + i;
		WriteIns(temp);
		temp = LCDPrintBuffer[0][i];
		
		if ((temp >= ' ') && (temp <= 'z'))
		{
			WriteData(temp);
		}
	}
	for (i = 0; i < 40; i++)
	{
		temp = 0xC0 + i;
		WriteIns(temp);
		temp = LCDPrintBuffer[1][i];
		
		if ((temp >= ' ') && (temp <= 'z'))
		{
			WriteData(temp);
		}
	}
	if (EditMode == TRUE)
	{
		// void DRI_vLCDDisplay(unsigned char displayflag, unsigned char cusorflag, unsigned char blinkflag)
		WriteIns(0xC0 + EditPosition);
		DRI_vLCDDisplay(TRUE, TRUE, FALSE);
	}
}


void PrintLCDWholePage(void)
{
	unsigned char i, temp, temp1;

	/* First 3 pages have same menu, no need to re-print, but menu 0 is initial , need to print */
	
	//if((LastMenu > 3) || (CurrentMenu > 3) || ((CurrentMenu==0) && (LastMenu==0)))
	{
			WriteIns(0x80);
			Nop();

			for (i = 0; i < 40; i++)
			{
				temp = acLCDTitle[CurrentMenu][i];
				if ((temp >= ' ') && (temp <= 'z'))
				{
					WriteData(temp);
				}
			}
	}

	WriteIns(0xC0);
	Nop();
	for (i = 0; i < 40; i++)
	{
		//temp = 0xC0 + i;
		//WriteIns(temp);
		temp = LCDPrintBuffer[1][i];
		
		if ((temp >= ' ') && (temp <= 'z'))
		{
			WriteData(temp);
		}
	}
	if (EditMode == TRUE)
	{
		// void DRI_vLCDDisplay(unsigned char displayflag, unsigned char cusorflag, unsigned char blinkflag)
		WriteIns(0xC0 + EditPosition);
		DRI_vLCDDisplay(TRUE, TRUE, FALSE);
	}
}


/* JuZh, Consider only print the blink text part if there is no Menu Index change, provieded the blink location and length */

void PrintBlinkMenuText(void)
{
	unsigned char i, temp;
    static BYTE boBlink;
    BYTE u8BlinkPos;
    BYTE u8BlinkLen;

    u8BlinkPos = stMenuDisplay[CurrentMenu].u8BlinkPos;
    u8BlinkLen = stMenuDisplay[CurrentMenu].u8BlinkLen;
    
    boBlink = boBlink?0:1;
    
	WriteIns(0x80 + u8BlinkPos);
	for (i = 0; i < u8BlinkLen; i++)
	{
        temp = boBlink?' ':acLCDTitle[CurrentMenu][i + u8BlinkPos]; /* toggole between space and text */
        
		if ((temp >= ' ') && (temp <= 'z'))
		{
			WriteData(temp);
		}

		
		
	}
    	//DelayMS(1);
    	
	if (EditMode == TRUE)
	{
		// void DRI_vLCDDisplay(unsigned char displayflag, unsigned char cusorflag, unsigned char blinkflag)
		WriteIns(0xC0 + EditPosition);
		DRI_vLCDDisplay(TRUE, TRUE, FALSE);
	}
	DelayMS(1);

}


/* consider only update the value text instead of whole line */
void PrintNewValue(void)
{
	unsigned char i, temp, temp1;


	WriteIns(0xC0);
	for (i = 0; i < 40; i++)
	{

		temp = LCDPrintBuffer[1][i];
		
		if ((temp >= ' ') && (temp <= 'z'))
		{
			WriteData(temp);
		}
	}

	if (EditMode == TRUE)
	{
		// void DRI_vLCDDisplay(unsigned char displayflag, unsigned char cusorflag, unsigned char blinkflag)
		WriteIns(0xC0 + EditPosition);
		DRI_vLCDDisplay(TRUE, TRUE, FALSE);
	}    
    
}


void PrintEditPosition(void)
{
    
    unsigned char i, temp;    
    
    WriteIns(0xC0+EditPosition);

    
    if((LCDPrintBuffer[1][EditPosition] == 'E') || (LCDPrintBuffer[1][EditPosition] == 'D')) //Enabled Disabled
    {
            for (i = 0; i < 9; i++) /* Only re-print the cursor value or print "ON", "OFF", 2 bytes are enough */
            {
                temp = LCDPrintBuffer[1][EditPosition + i];

                if ((temp >= ' ') && (temp <= 'z'))
                {
                    WriteData(temp);
                }
            }     
        
        
    }
    
    

	else if(LCDPrintBuffer[1][EditPosition] != 'O') /* Not editing On/Off , set only 1 number*/
	{
		temp = LCDPrintBuffer[1][EditPosition];

        if ((temp >= ' ') && (temp <= 'z'))
        {
            WriteData(temp);
        }
	}
	
	else /* On/Off, set 2 bytes */
	{
	    for (i = 0; i < 3; i++) /* Only re-print the cursor value or print "ON", "OFF", 2 bytes are enough */
	    {
	        temp = LCDPrintBuffer[1][EditPosition + i];

	        if ((temp >= ' ') && (temp <= 'z'))
	        {
	            WriteData(temp);
	        }
	    }  
	}

	if (EditMode == TRUE)
	{
		// void DRI_vLCDDisplay(unsigned char displayflag, unsigned char cusorflag, unsigned char blinkflag)
		WriteIns(0xC0 + EditPosition);
		DRI_vLCDDisplay(TRUE, TRUE, FALSE);
	}    
           
}



/* Not used any more */
void PrintBlinkLCD(void)
{
	unsigned char i, temp;

	WriteIns(0x80);
	for (i = 0; i < 40; i++)
	{

		temp = acLCDBlinkTitle[CurrentMenu][i];;
		if ((temp >= ' ') && (temp <= 'z'))
		{
			WriteData(temp);
		}
	}
	WriteIns(0xC0);
	for (i = 0; i < 40; i++)
	{
		temp = LCDPrintBuffer[1][i];
		
		if ((temp >= ' ') && (temp <= 'z'))
		{
			WriteData(temp);
		}
	}
	if (EditMode == TRUE)
	{
		// void DRI_vLCDDisplay(unsigned char displayflag, unsigned char cusorflag, unsigned char blinkflag)
		WriteIns(0xC0 + EditPosition);
		DRI_vLCDDisplay(TRUE, TRUE, FALSE);
	}
}




