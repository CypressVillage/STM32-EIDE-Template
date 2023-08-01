#include "stm32f10x.h"
#include "TB6612.h"
#include "GPIO_DEF.h"

void Motor_IO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // 使能端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // 使能端口时钟

    GPIO_InitStructure.GPIO_Pin   = PIN_AIN1;         // 端口配置
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50M
    GPIO_Init(GPIO_AIN1, &GPIO_InitStructure);        // 根据设定参数初始化GPIO

    GPIO_InitStructure.GPIO_Pin   = PIN_AIN2;         // 端口配置
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50M
    GPIO_Init(GPIO_AIN2, &GPIO_InitStructure);        // 根据设定参数初始化GPIO

    GPIO_InitStructure.GPIO_Pin   = PIN_BIN1;         // 端口配置
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50M
    GPIO_Init(GPIO_BIN1, &GPIO_InitStructure);        // 根据设定参数初始化GPIO

    GPIO_InitStructure.GPIO_Pin   = PIN_BIN2;         // 端口配置
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP; // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50M
    GPIO_Init(GPIO_BIN2, &GPIO_InitStructure);        // 根据设定参数初始化GPIO

    GPIO_ResetBits(GPIO_AIN1, PIN_AIN1); // io输出0，防止电机乱转
    GPIO_ResetBits(GPIO_AIN2, PIN_AIN2); // io输出0，防止电机乱转
    GPIO_ResetBits(GPIO_BIN1, PIN_BIN1); // io输出0，防止电机乱转
    GPIO_ResetBits(GPIO_BIN2, PIN_BIN2); // io输出0，防止电机乱转
}

void Motor_PWM_Init(u16 arr, u16 psc) // 初始化时arr=10-1，psc=7200-1，则占空比区间为0-7200
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);  // 使能定时器8
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // 使能GPIO外设时钟

    GPIO_InitStructure.GPIO_Pin   = PIN_PWMA;         // 端口配置
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50M
    GPIO_Init(GPIO_PWMA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin   = PIN_PWMB;         // 端口配置
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;  // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 50M
    GPIO_Init(GPIO_PWMB, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period        = arr;                // 设置在下一个更新事件装入活动的自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler     = psc;                // 设置用来作为TIMx时钟频率除数的预分频值  不分频
    TIM_TimeBaseStructure.TIM_ClockDivision = 1;                  // 设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode   = TIM_CounterMode_Up; // TIM向上计数模式
    TIM_TimeBaseInit(TIM_TB6612, &TIM_TimeBaseStructure);         // 根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;        // 选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; // 比较输出使能
    TIM_OCInitStructure.TIM_Pulse        = 0;                      // 设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;    // 输出极性:TIM输出比较极性高
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC1Init(TIM_TB6612, &TIM_OCInitStructure);          // 根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC1PreloadConfig(TIM_TB6612, TIM_OCPreload_Enable); // CH1预装载使能

    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1;        // 选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; // 比较输出使能
    TIM_OCInitStructure.TIM_Pulse        = 0;                      // 设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High;    // 输出极性:TIM输出比较极性高
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC2Init(TIM_TB6612, &TIM_OCInitStructure);          // 根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC2PreloadConfig(TIM_TB6612, TIM_OCPreload_Enable); // CH2预装载使能

    TIM_ARRPreloadConfig(TIM_TB6612, ENABLE); // 使能TIMx在ARR上的预装载寄存器

    TIM_Cmd(TIM_TB6612, ENABLE); // 使能TIM8

    TIM_CtrlPWMOutputs(TIM_TB6612, ENABLE); // 高级定时器输出必须使能这句
}

void TB6612_Init(void)
{
    Motor_IO_Init();
    Motor_PWM_Init(899, 0);
}

/**************************************************************************
函数功能：电机驱动
入口参数：两个电机的pwm值
返回  值：无
注    意：700<pwm<7200
**************************************************************************/
void TB6612_Motor_Run(float pwmA, float pwmB)
{
    if (pwmA > 0) {
        GPIO_SetBits(GPIO_AIN1, PIN_AIN1);   // io输出1，电机正转
        GPIO_ResetBits(GPIO_AIN2, PIN_AIN2); // io输出0，电机正转
        TIM_SetCompare1(TIM_TB6612, pwmA);   // 设置pwm值
    } else if (pwmA < 0) {
        GPIO_ResetBits(GPIO_AIN1, PIN_AIN1); // io输出0，电机反转
        GPIO_SetBits(GPIO_AIN2, PIN_AIN2);   // io输出1，电机反转
        TIM_SetCompare1(TIM_TB6612, -pwmA);  // 设置pwm值
    } else {
        GPIO_ResetBits(GPIO_AIN1, PIN_AIN1); // io输出0，防止电机乱转
        GPIO_ResetBits(GPIO_AIN2, PIN_AIN2); // io输出0，防止电机乱转
        TIM_SetCompare1(TIM_TB6612, 0);      // 设置pwm值
    }

    if (pwmB > 0) {
        GPIO_SetBits(GPIO_BIN1, PIN_BIN1);   // io输出1，电机正转
        GPIO_ResetBits(GPIO_BIN2, PIN_BIN2); // io输出0，电机正转
        TIM_SetCompare2(TIM_TB6612, pwmB);   // 设置pwm值
    } else if (pwmB < 0) {
        GPIO_ResetBits(GPIO_BIN1, PIN_BIN1); // io输出0，电机反转
        GPIO_SetBits(GPIO_BIN2, PIN_BIN2);   // io输出1，电机反转
        TIM_SetCompare2(TIM_TB6612, -pwmB);  // 设置pwm值
    } else {
        GPIO_ResetBits(GPIO_BIN1, PIN_BIN1); // io输出0，防止电机乱转
        GPIO_ResetBits(GPIO_BIN2, PIN_BIN2); // io输出0，防止电机乱转
        TIM_SetCompare2(TIM_TB6612, 0);      // 设置pwm值
    }
}
