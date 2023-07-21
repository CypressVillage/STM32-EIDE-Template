#include "GPIO_DEF.h"
#include "stm32f10x.h"

#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "OLED_Pic.h"
#include "Key.h"
#include "Serial.h"
#include "I2C.h"
// #include "ADS1115.h"
// #include "u8g2.h"
// #include "lelib.h" // 自定义lua函数库
#include "math.h"
#include "arm_math.h"
#include "stm32_dsp.h"

/****************************************************************************************/
/* 将userscropts.lua中的内容加载进"incbin_luascript_start"字符串 */
// #define STR2(x) #x
// #define STR(x) STR2(x)

// #if defined ( __GNUC__ )
//     // this aligns start address to 16 and terminates byte array with explict 0
//     // which is not really needed, feel free to change it to whatever you want/need
//     #define INCBIN(name, file) \
//         __asm(".section .rodata\n" \
//                 ".global incbin_" STR(name) "_start\n" \
//                 "incbin_" STR(name) "_start:\n" \
//                 ".incbin \"" file "\"\n" \
//                 ".byte 0\n" \
//         ); \
//         extern const char incbin_ ## name ## _start[];

//     INCBIN(luascript, "./userscripts.lua");
// #elif defined ( __CC_ARM )
//     static char* incbin_luascript_start = "\
//         while true do \
//         led_on()\
//         delayms(200)\
//         led_off()\
//         delayms(200)\
//         end\
//     ";
// #endif
/****************************************************************************************/

#define NPT 256

uint32_t adc_buf[NPT] = {0};
long lBufInArray[NPT];
long lBufOutArray[NPT / 2];
long lBufMagArray[NPT / 2];

int main(void)
{
    /* 使用内置时钟，proteus仿真需要 */
    // RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

    /* 初始化硬件 */
    LED_Init();
    OLED_Init();
    Serial_Init();
    I2C_GPIOInit();
    // ADS1115_Init();

    // u8g2_t u8g2;
    // u8g2Init(&u8g2);

    /* 开启Lua虚拟机并执行自定义lua代码 */
    // lua_State *L;
    // L = luaL_newstate();
    // luaopen_base(L);
    // luaL_setfuncs(L, elib, 0);
    // luaL_dostring(L, incbin_luascript_start);

    while (1) {
        // 填充数组
        for (int i = 0; i < NPT; i++)
            // 这里因为单片机的ADC只能测正的电压 所以需要前级加直流偏执
            // 加入直流偏执后，需要在软件上减去2048即一半，达到负半周期测量的目的（需要根据具体情况来进行配置）
            lBufInArray[i] = ((signed short)(adc_buf[i] - 2048)) << 16;

        cr4_fft_256_stm32(lBufOutArray, lBufInArray, NPT);
    }

}
