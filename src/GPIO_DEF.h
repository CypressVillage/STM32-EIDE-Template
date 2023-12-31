
#ifndef __GPIO_DEF_H
#define __GPIO_DEF_H

// LED
#define RCC_GPIO_LED        RCC_APB2Periph_GPIOA
#define GPIO_LED            GPIOA
#define PIN_LED_1           GPIO_Pin_8
#define PIN_LED_2           GPIO_Pin_9
// OLED
#define RCC_GPIO_OLED       RCC_APB2Periph_GPIOB
#define GPIO_OLED           GPIOB
#define PIN_OLED_SCL        GPIO_Pin_8
#define PIN_OLED_SDA        GPIO_Pin_9
// 按键
#define RCC_GPIO_KEY        RCC_APB2Periph_GPIOB
#define GPIO_KEY            GPIOB
#define PIN_KEY_1           GPIO_Pin_1
#define PIN_KEY_2           GPIO_Pin_11
// PWM输出
#define RCC_GPIO_PWM        RCC_APB2Periph_GPIOA
#define GPIO_PWM            GPIOA
#define PIN_PWM             GPIO_Pin_1
// 串口输出
#define RCC_GPIO_SERIAL     RCC_APB2Periph_GPIOA
#define RCC_USART_SERIAL    RCC_APB2Periph_USART1
#define GPIO_SERIAL         GPIOA
#define PIN_SERIAL_TX       GPIO_Pin_9
#define PIN_SERIAL_RX       GPIO_Pin_10
#define USART_SERIAL        USART1
#define SERIAL_BAUDRATE     9600
// ADS1115
#define GPIO_ADS1115        GPIOB
#define PIN_ADS1115_SCL     GPIO_Pin_10
#define PIN_ADS1115_SDA     GPIO_Pin_11
// WT1-IMU陀螺仪
#define RCC_GPIO_WT1        RCC_APB2Periph_GPIOA
#define RCC_USART_WT1       RCC_APB1Periph_USART2
#define GPIO_WT1            GPIOA
#define PIN_WT1_TX          GPIO_Pin_1
#define PIN_WT1_RX          GPIO_Pin_2
#define USART_WT1           USART2

#endif /* __GPIO_DEF_H */
