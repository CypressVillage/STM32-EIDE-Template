#include "stm32f10x.h"                  // Device header
#include "GPIO_DEF.h"
#include "Delay.h"

void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_GPIO_KEY, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = PIN_KEY_1 | PIN_KEY_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (GPIO_ReadInputDataBit(GPIOB, PIN_KEY_1) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, PIN_KEY_1) == 0);
		Delay_ms(20);
		KeyNum = 1;
	}
	if (GPIO_ReadInputDataBit(GPIOB, PIN_KEY_2) == 0)
	{
		Delay_ms(20);
		while (GPIO_ReadInputDataBit(GPIOB, PIN_KEY_2) == 0);
		Delay_ms(20);
		KeyNum = 2;
	}
	
	return KeyNum;
}
