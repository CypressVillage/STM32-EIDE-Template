#include "GPIO_DEF.h"
#include "lelib.h"

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

int main(void)
{
    LED_Init();
    OLED_Init();

    lua_State *L;
    L = luaL_newstate();
    luaopen_base(L);
    luaL_setfuncs(L, elib, 0);
    luaL_dostring(L, incbin_luascript_start);

    while(1);
}
