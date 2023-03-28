#include "stm32f10x.h"                  // Device header
#include "GPIO_DEF.h"

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_GPIO_LED, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = PIN_LED_1 | PIN_LED_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIO_LED, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIO_LED, PIN_LED_1 | PIN_LED_2);
}

void LED1_ON(void)
{
	GPIO_ResetBits(GPIO_LED, PIN_LED_1);
}

void LED1_OFF(void)
{
	GPIO_SetBits(GPIO_LED, PIN_LED_1);
}

void LED1_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIO_LED, PIN_LED_1) == 0)
	{
		GPIO_SetBits(GPIO_LED, PIN_LED_1);
	}
	else
	{
		GPIO_ResetBits(GPIO_LED, PIN_LED_1);
	}
}

void LED2_ON(void)
{
	GPIO_ResetBits(GPIO_LED, PIN_LED_2);
}

void LED2_OFF(void)
{
	GPIO_SetBits(GPIO_LED, PIN_LED_2);
}

void LED2_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIO_LED, PIN_LED_2) == 0)
	{
		GPIO_SetBits(GPIO_LED, PIN_LED_2);
	}
	else
	{
		GPIO_ResetBits(GPIO_LED, PIN_LED_2);
	}
}
