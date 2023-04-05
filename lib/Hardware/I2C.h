#ifndef _I2C_H_
#define _I2C_H_

#include "stm32f10x.h"
#include "stdio.h"

#define I2C_SCL_HIGH() GPIO_SetBits(I2C_GPIO_PORT, I2C_SCL_PIN)
#define I2C_SCL_LOW()  GPIO_ResetBits(I2C_GPIO_PORT, I2C_SCL_PIN)
#define I2C_SDA_HIGH() GPIO_SetBits(I2C_GPIO_PORT, I2C_SDA_PIN)
#define I2C_SDA_LOW()  GPIO_ResetBits(I2C_GPIO_PORT, I2C_SDA_PIN)
#define I2C_SDA_READ() GPIO_ReadInputDataBit(I2C_GPIO_PORT, I2C_SDA_PIN)

#define I2C_GPIO_PORT  GPIOB
#define I2C_SCL_PIN    GPIO_Pin_10
#define I2C_SDA_PIN    GPIO_Pin_11

void I2C_GPIOInit(void);
void SDA_Input_Mode(void);
void SDA_Output_Mode(void);
void I2C_GPIOInit(void);
void I2C_Start(void);              // 开始信号
void I2C_Stop(void);               // 停止信号
void I2C_Ack(void);                // 应答
uint8_t I2C_WaitAck(void);         // 等待应答
void I2C_NAck(void);               // 无应答
void I2C_SendByte(uint8_t data);   // 发送
uint8_t I2C_ReadByte(uint8_t ack); // 接收
void SDA_OUT(void);                // SDA设置成输出
void SDA_IN(void);                 // SDA设置成输入

uint8_t Read_Reg(uint8_t dev_add, uint8_t RegIndex);
void IIC_Write_Reg(uint8_t dev_add, uint8_t RegIndex, uint8_t data);

#endif
