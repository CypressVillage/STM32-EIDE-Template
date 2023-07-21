#include "MODULE_DEF.h"

void module_init(void)
{
#ifdef PROTEUS
    /* 使用内置时钟，proteus仿真需要 */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
#endif

#ifdef LED
    LED_Init();
#endif

#ifdef OLED
    OLED_Init();
#endif

#ifdef KEY
    Key_Init();
#endif

#ifdef SERIAL
    Serial_Init();
#endif

#ifdef I2C
    I2C_GPIOInit();
#endif

#ifdef ADC
    AD_Init();
#endif

#ifdef PWM
    PWM_Init();
#endif

#ifdef ADS1115
    ADS1115_Init();
#endif

#ifdef U8G2
    u8g2_t u8g2;
    u8g2Init(&u8g2);
#endif

#ifdef LUA
    /* 开启Lua虚拟机并执行自定义lua代码 */
    lua_State *L;
    L = luaL_newstate();
    luaopen_base(L);
    luaL_setfuncs(L, elib, 0);
    luaL_dostring(L, incbin_luascript_start);
#endif
}