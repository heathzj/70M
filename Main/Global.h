#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "define.h"

/***ZJ ***/

typedef struct{
	unsigned long u32OutputFreq; /* 950 ~ 2150 MHz, 1kHz step,950 as bas */
	unsigned short int u16Atten; /* 0.0~30.0 dB, 0.1 dB step */	
	
	unsigned char u8OutputPower; /* -30~0 dB, 1 dB step, we record positive value here, add '-' later */
	SHORT i16OutputPower; /* -30~5 dB, 1 dB step, we record signed value * 10 here*/
	WORD u16OutputPower; //raw word data
	float fOutputPower;	
	SHORT i16SetPwr; /* -30~5 dB, 1 dB step, we record signed value * 10 here*/
	WORD u16SetPwr;//raw word data	
	float fSetPwr;

	
	unsigned char u8Lock;
	unsigned char u8AlarmStatus;	
	unsigned char u8ALC;
	unsigned char u8Mute;

} tstUpConverter;

typedef struct{
	unsigned long u32InputFreq;	/* 950 ~ 2150 MHz, 1kHz step,950 as base */
	unsigned short int u16Atten;	/* 0.0~30.0 dB, 0.1 dB step */	
	
	unsigned char u8OutputPower; /* -30~0 dB, 1 dB step ,  we record positive value here, add '-' later */
	SHORT i16OutputPower; /* -30~5 dB, 1 dB step, we record signed value * 10 here*/
	WORD u16OutputPower;//raw word data
	float fOutputPower;
	SHORT i16SetPwr; /* -30~5 dB, 1 dB step, we record signed value * 10 here*/
	WORD u16SetPwr;//raw word data
	float fSetPwr;

	unsigned char u8Lock;
	unsigned char u8AlarmStatus;
	unsigned char u8ALC;
	unsigned char u8Mute;	


} tstDownConverter;

typedef struct{
	unsigned char u818VDC;
	unsigned char u824VDC;
	
	BYTE u8BUC_REF_ONOFF;
	BYTE u8LNB_REF_ONOFF;

	BYTE u8BUC_DC_ONOFF;
	BYTE u8LNB_DC_ONOFF;

	BYTE u8BUC_DC_OVERCurrent;
	BYTE u8LNB_DC_OVERCurrent;

	BYTE u8EXTREF;
	
	BYTE u8Led; //bit 0-3 = LED 1 -4
	WORD u16BUCCurrent;
	WORD u16LNBCurrent;
	WORD u16BUCCurrentLimit;
	WORD u16LNBCurrentLimit;

} tstDCController;




typedef struct{
	tstUpConverter stUp;
	tstDownConverter stDown;
	tstDCController stDC;
} tstUpDownConverter;


extern tstUpDownConverter stConverter;












extern unsigned char Read2[2][4];

//pavan
extern IP_ADDR Manager_IP;
extern DWORD dwLastIP;
extern APP_CONFIG AppConfig;
extern IP_ADDR	MyStaticIPAddr;

extern char RCU_ID[3],BankData[4];

extern BYTE global_char_temp[15];

extern char MNString[18]; 
extern char SNString[9]; 



//Function Prototypes

void LowISR(void);
void HighISR(void);


void AD_GET(void);
void AD_init(void);
void Read_ADC(unsigned int,unsigned int, unsigned int);
unsigned int ADC_Value(unsigned int);

BYTE GetOneCHADC0(BYTE);
BYTE GetOneCHADC1(BYTE);

void SPIInit(void);
void SerialIOInit(void);

void SetCPLDGPIO(unsigned char IOPin, unsigned char value);


void EEPROMWrite(unsigned char * address1, unsigned char * datapte1, unsigned char length);
void EEPROMRead(unsigned char * address1, unsigned char * datapte1, unsigned char length);



unsigned char ASC2toHEX(unsigned char *asc);
void HEXto2ASC(unsigned char hex, unsigned char *asc);
void DelayMS(unsigned int ms);
BYTE GetChecksum(void *p_buff, BYTE n);
BYTE calc_CRC(WORD, WORD);

int Check_checksum(char*);
int Check_checksum2(char*);
int Hex2Int(char);
int Int2Hex(int);


void putsUSART2( char *data);
void putsUSART( char *data);

void CONFIG232(void);   
void CONFIG422(void); 
void CONFIG485Tx(void);    
void CONFIG485Rx(void);   
void CONFIG2322(void);   
void CONFIG485Tx2(void);  
void CONFIG485Rx2(void);   
void CONFIGT(void);  
void CONFIGR(void);   
void CONFIGT2(void);  
void CONFIGR2(void); 

unsigned float atof5(unsigned char* );//with 0.5 stepsize
unsigned float atof1(unsigned char* );//with 0.1 stepsize


#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
 void SaveAppConfig(void);
int Load_config(void);
#endif

void SaveSetting(void);


int UpdataIP();
int Config_IP();
void DisplayIPValue(IP_ADDR);
void DisplayIPValue2(IP_ADDR);


void Default_value(void);
void InitData(void);


// Private helper functions.
// These may or may not be present in all applications.
void InitAppConfig(void);
void InitializeBoard(void);
void HitWatchDog(void);

void SetDefaultValue(void);



//char PreProcessCommandBuffer(char SIO, char RecvLength);
//char PostProcessCommandBuffer(BYTE *cmdBuffer, char *src_id1, char *des_id1, WORD cmd, BYTE length, BYTE *data);
//int SSPA_CMD_Process(void);




int Set_ID(unsigned char);

void debugPrintf(const char *szFormat, ...);
void debugPrintf2(rom char *str);
void debugPrintfByte(rom char *str, BYTE data);
void debugPrintfWord(rom char *str, WORD data);
void debugPrintfDword(rom char *str, DWORD data);

void SNMPAlarmTrap(void);
void SNMPClearTrap(void);
void DoUARTConfig(void);
// Structure type defines



typedef struct systeminfo_s
{
 unsigned char SYSDESCR1[32]; 
 unsigned char SYSCONTACT1[32];
} systeminfo_t;

typedef struct systeminfo_s2
{
 unsigned char SYSNAME1[32];
 unsigned char SYSLOCATION1[32];
} systeminfo_t2;

extern systeminfo_t systeminfo1;
extern systeminfo_t2 systeminfo2;


typedef struct deviceInfo
{
	char deviceID[4];
	char modelNo[16];
	char serialNo[16];
	char firmwareVersion[4];
	char firmwareVersion_sspa[4];
	BYTE BUC_model;
	BYTE max_attn;
} deviceInfo_t;


typedef struct deviceStatus 
{
	unsigned int inpower;
	char inpower_sign;
	unsigned int outpower;
	char outpower_sign;
	int temp;
	char temp_sign;
	int temp_sspa;
	//char temp_sign_sspa;
	unsigned int outpower_sspa;
	char outpower_sign_sspa;
} deviceStatus_t;


typedef struct deviceAlarm 
{
	char Lo;
	char fetbias;
	char refclk;
	char rflow;
	char rfon;
	char templvl;
	char major_sspa;
	char templvl_sspa;
	char rflow_sspa;
	char tempoff_sspa;
	char buc_sspa;
	char reflect_sspa;
	char rfon_sspa;
} deviceAlarm_t;



typedef struct deviceOperation 
{
	char rfOperation;
	float usrSetAttn;
	char swLO;
    char maxattn;
} deviceOperation_t;



typedef struct BUCinfo_s
{
	deviceInfo_t info;
	deviceStatus_t status;
	deviceAlarm_t alarm;
	deviceOperation_t operation;
}BUCinfo_t;

extern BUCinfo_t BUCinfo[BUC_MAX_SIZE];


typedef struct ADCInfo 
{
	unsigned int Channel;
	unsigned int AD_Result_H;
	unsigned int AD_Result_L;
	unsigned int  ADC_value;
} ADCInfo_t;


extern ADCInfo_t ADCInfo1;


typedef enum 
{
	successful=0, //password set succesful
	invalid_charactor, //password contains invalid data
	too_long,//password set is too long
	old_password_wrong,//old password input wrongly
	repeat_password_different,//repeat pasword dose not match
	others	//default
}webpasserror_e;

typedef enum
{
	passred = 0,
	passgreen
}webpasscolor_e;

typedef struct webpassword_s
{
webpasserror_e setpass; //password set result
webpasscolor_e setpasscolor; //color to be displayed to indicate set status
char count;//time counter
char webpassword[10]; //save password
}webpassword_t;

extern webpassword_t webpassinfo;

#if !defined SNMP_TRAP_DISABLED


#define TRAP_MINOR_ALARM		0
#define TRAP_MAJOR_ALARM		1
#define TRAP_NO_ALARM           2

/*
typedef struct 
{
	BYTE	alarm_value;
	BYTE	device_id;
}trap_info;
*/

extern BYTE trap_en;

typedef struct 
{
		BYTE alarm_temp;
}Trap_t;

extern Trap_t  snmp_trap[];

extern void snmp_trap_task(void);

#endif

