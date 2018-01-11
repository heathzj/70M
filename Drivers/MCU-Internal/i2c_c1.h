#ifndef I2C_C1_H
#define I2C_C1_H


extern unsigned char I2CReceiveBuffer[16];



char I2C_Send(char Address,char *Data,char Num);
char I2C_Read(char Address,char *Data,char Num);
char i2csendbyte(char byte);
char i2cgetbyte(void);
char i2cgetack(void);
void i2csendack(void);
void i2csendnack(void);
void i2cdelay(char delay);
void i2cstart(void);
void i2cstop(void);
void i2cclock(void);
char i2creadbit(void);
void SetI2C(unsigned char module);
	

#endif /* I2C_C1_H */
