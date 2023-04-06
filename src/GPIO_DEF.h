
#ifndef __GPIO_DEF_H
#define __GPIO_DEF_H


#define RCC_GPIO_LED        RCC_APB2Periph_GPIOA
#define RCC_GPIO_PWM        RCC_APB2Periph_GPIOA
#define RCC_GPIO_OLED       RCC_APB2Periph_GPIOB
#define RCC_GPIO_KEY        RCC_APB2Periph_GPIOB
#define RCC_GPIO_SERIAL     RCC_APB2Periph_GPIOA

#define RCC_USART_SERIAL    RCC_APB2Periph_USART1


#define GPIO_LED            GPIOA
#define PIN_LED_1           GPIO_Pin_8
#define PIN_LED_2           GPIO_Pin_9

#define GPIO_OLED           GPIOB
#define PIN_OLED_SCL        GPIO_Pin_8
#define PIN_OLED_SDA        GPIO_Pin_9

#define GPIO_KEY            GPIOB
#define PIN_KEY_1           GPIO_Pin_1
#define PIN_KEY_2           GPIO_Pin_11

#define GPIO_PWM            GPIOA
#define PIN_PWM             GPIO_Pin_1

#define GPIO_SERIAL         GPIOA
#define PIN_SERIAL_TX       GPIO_Pin_9
#define PIN_SERIAL_RX       GPIO_Pin_10
#define USART_SERIAL        USART1

#define GPIO_ADS1115        GPIOB
#define PIN_ADS1115_SCL     GPIO_Pin_10
#define PIN_ADS1115_SDA     GPIO_Pin_11


#endif /* __GPIO_DEF_H */