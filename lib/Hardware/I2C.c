#include "i2c.h"
#include "Delay.h"
#include "GPIO_DEF.h"

void I2C_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitStructure.GPIO_Pin   = PIN_ADS1115_SCL | PIN_ADS1115_SDA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_ADS1115, &GPIO_InitStructure);
    GPIO_ResetBits(GPIO_ADS1115, PIN_ADS1115_SCL | PIN_ADS1115_SDA);
}
// 配置SDA信号线为输入模式
void SDA_Input_Mode(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = PIN_ADS1115_SDA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;
    GPIO_Init(GPIO_ADS1115, &GPIO_InitStructure);
}

// 配置SDA信号线为输出模式
void SDA_Output_Mode(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = PIN_ADS1115_SDA;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO_ADS1115, &GPIO_InitStructure);
}

/**
 * 函数功能: CPU发起I2C总线启动信号
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
void I2C_Start(void)
{
    /* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
    SDA_Output_Mode();
    I2C_SDA_HIGH();
    I2C_SCL_HIGH();
    Delay_us(4);
    I2C_SDA_LOW();
    Delay_us(4);
    I2C_SCL_LOW();
    Delay_us(4);
}

/**
 * 函数功能: CPU发起I2C总线停止信号
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
void I2C_Stop(void)
{
    /* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
    SDA_Output_Mode();
    I2C_SDA_LOW();
    I2C_SCL_HIGH();
    Delay_us(4);
    I2C_SDA_HIGH();
}
/**
 * 函数功能: CPU向I2C总线设备发送8bit数据
 * 输入参数: Byte ： 等待发送的字节
 * 返 回 值: 无
 * 说    明：无
 */
void I2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    SDA_Output_Mode();
    /* 先发送字节的高位bit7 */
    for (i = 0; i < 8; i++) {
        if (Byte & 0x80) {
            I2C_SDA_HIGH();
        } else {
            I2C_SDA_LOW();
        }
        Delay_us(4);
        I2C_SCL_HIGH();
        Delay_us(4);
        I2C_SCL_LOW();
        if (i == 7) {
            I2C_SDA_HIGH(); // 释放总线
        }
        Byte <<= 1; /* 左移一个bit */
        Delay_us(4);
    }
}

/**
 * 函数功能: CPU从I2C总线设备读取8bit数据
 * 输入参数: 无
 * 返 回 值: 读到的数据
 * 说    明：无
 */
uint8_t I2C_ReadByte(uint8_t ack)
{
    uint8_t i;
    uint8_t value;
    SDA_Input_Mode();
    /* 读到第1个bit为数据的bit7 */
    value = 0;
    for (i = 0; i < 8; i++) {
        value <<= 1;
        I2C_SCL_HIGH();
        Delay_us(4);
        if (I2C_SDA_READ()) {
            value++;
        }
        I2C_SCL_LOW();
        Delay_us(4);
    }
    if (ack == 0)
        I2C_NAck();
    else
        I2C_Ack();
    return value;
}

/**
 * 函数功能: CPU产生一个时钟，并读取器件的ACK应答信号
 * 输入参数: 无
 * 返 回 值: 返回0表示正确应答，1表示无器件响应
 * 说    明：无
 */
uint8_t I2C_WaitAck(void)
{
    uint8_t re;
    SDA_Output_Mode();
    I2C_SDA_HIGH(); /* CPU释放SDA总线 */
    Delay_us(4);
    I2C_SCL_HIGH(); /* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
    Delay_us(4);
    SDA_Input_Mode();
    if (I2C_SDA_READ()) /* CPU读取SDA口线状态 */
    {
        re = 1;
    } else {
        re = 0;
    }
    I2C_SCL_LOW();
    Delay_us(4);
    return re;
}

/**
 * 函数功能: CPU产生一个ACK信号
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
void I2C_Ack(void)
{
    SDA_Output_Mode();
    I2C_SDA_LOW(); /* CPU驱动SDA = 0 */
    Delay_us(4);
    I2C_SCL_HIGH(); /* CPU产生1个时钟 */
    Delay_us(4);
    I2C_SCL_LOW();
    Delay_us(4);
    I2C_SDA_HIGH(); /* CPU释放SDA总线 */
}

/**
 * 函数功能: CPU产生1个NACK信号
 * 输入参数: 无
 * 返 回 值: 无
 * 说    明：无
 */
void I2C_NAck(void)
{
    SDA_Output_Mode();
    I2C_SDA_HIGH(); /* CPU驱动SDA = 1 */
    Delay_us(4);
    I2C_SCL_HIGH(); /* CPU产生1个时钟 */
    Delay_us(4);
    I2C_SCL_LOW();
    Delay_us(4);
}

uint8_t Read_Reg1(uint8_t dev_add, uint8_t RegIndex)
{
    unsigned char receive = 0;

    I2C_Start();
    I2C_SendByte(dev_add);
    I2C_WaitAck();
    I2C_SendByte(RegIndex);
    I2C_WaitAck();

    I2C_Start();
    I2C_SendByte(dev_add + 1);
    I2C_WaitAck();
    receive = I2C_ReadByte(0);
    I2C_Stop();
    return receive;
}

void IIC_Write_Reg(uint8_t dev_add, uint8_t RegIndex, uint8_t data)
{
    I2C_Start();
    I2C_SendByte(dev_add);
    I2C_WaitAck();
    I2C_SendByte(RegIndex);
    I2C_WaitAck();
    I2C_SendByte(data);
    I2C_WaitAck();
    I2C_Stop();
}
