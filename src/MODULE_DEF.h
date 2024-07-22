#ifndef __MODULE_DEF_H
#define __MODULE_DEF_H

/*****************************************/
// #define PROTEUS
#define LED
#define OLED
#define KEYS
#define SERIAL
#define I2C
// #define ADC
#define PWM
// #define MATH
// #define FFT
#define CMSIS_DSP
// #define LUA
// #define U8G2
// #define ADS1115
// #define TB6612
// #define WT1_IMU
/*****************************************/
#include "stm32f10x.h"

#include "Delay.h"
#include "Timer.h"

#ifdef LED
#include "LED.h"
#endif

#ifdef OLED
#include "OLED.h"
#include "OLED_Terminal.h"
#endif

#ifdef KEYS
#include "Key.h"
#endif

#ifdef SERIAL
#include "Serial.h"
#endif

#ifdef I2C
#include "I2C.h"
#endif

#ifdef ADC
#include "AD.h"
#endif

#ifdef PWM
#include "PWM.h"
#endif

#ifdef MATH
#include "math.h"
#include "arm_math.h"
#endif

#ifdef FFT
#include "stm32_dsp.h"
#endif

#ifdef CMSIS_DSP
#include "arm_math.h"
#endif

#ifdef ADS1115
#include "ADS1115.h"
#endif

#ifdef U8G2
#include "I2C.h"
#include "u8g2.h"
#endif

#ifdef LUA
// 调用lua脚本写法(gcc)
// lua_State *L;
// L = luaL_newstate();
// luaopen_base(L);
// luaL_setfuncs(L, elib, 0);
// luaL_dostring(L, incbin_luascript_start);

#include "lelib.h"
/* 将userscropts.lua中的内容加载进"incbin_luascript_start"字符串 */
#define STR2(x) #x
#define STR(x) STR2(x)
#if defined ( __GNUC__ )
    // this aligns start address to 16 and terminates byte array with explict 0
    // which is not really needed, feel free to change it to whatever you want/need
    #define INCBIN(name, file) \
        __asm(".section .rodata\n" \
                ".global incbin_" STR(name) "_start\n" \
                "incbin_" STR(name) "_start:\n" \
                ".incbin \"" file "\"\n" \
                ".byte 0\n" \
        ); \
        extern const char incbin_ ## name ## _start[];

    INCBIN(luascript, "./userscripts.lua");
#elif defined ( __CC_ARM )
    static char* incbin_luascript_start = "\
        while true do \
        led_on()\
        delayms(200)\
        led_off()\
        delayms(200)\
        end\
    ";
#endif
#endif

#ifdef WT1_IMU
#include "WT1-IMU.h"
#endif

#ifdef TB6612
#include "TB6612.h"
#endif

void module_init(void);

#endif /* __MODULE_DEF_H */
