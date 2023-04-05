#include "ads1115.h"
#include "Delay.h"

void ADS1115_Write(u8 Reg , u8 reg_MSB , u8 reg_LSB)
{	
	I2C_Start();
	I2C_SendByte(0x90+0);//0x90地址+0写位
	while(I2C_WaitAck());
	I2C_SendByte(Reg);
	while(I2C_WaitAck());
	I2C_SendByte(reg_MSB);
	while(I2C_WaitAck());
	I2C_SendByte(reg_LSB);
	while(I2C_WaitAck());
	I2C_Stop();
}
float ADS1115_ReadAD()
{
	float ret;
	
	uint16_t data;
	I2C_Start();
	I2C_SendByte(0x90+0);//0x90地址+0写位
	while(I2C_WaitAck());
	I2C_SendByte(REG_Conversion);
	while(I2C_WaitAck());
	I2C_Stop();
	Delay_us(5);
	I2C_Start();
	I2C_SendByte(0x90+1);//0x90地址+1读位
	while(I2C_WaitAck());
	data = I2C_ReadByte(1);
	data = (data <<	8)&0xff00;//前8位
	data+=	I2C_ReadByte(1);//后8位
	I2C_Stop();
	//数值计算取决于PGA配置
	if(data>0x8000)
		ret=((float)(0xffff-data)/32768.0)*4.096;
	else
		ret=((float)data/32768.0)*4.096;
	
	return ret;
	
}

void ADS115_config()
{

	ADS1115_Write(REG_config, config_MSB ,config_LSB);
}
