#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "stm32f10x.h"
#include "GPIO_DEF.h"

#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"

/* c-lua functions */
static int lua_delay(lua_State *L) {
    int n = luaL_checkinteger(L, 1);
    Delay_ms(n);
    return 0;
}

static int lua_led_on(lua_State *L) {
    GPIO_SetBits(GPIO_LED, PIN_LED_1);
	return 0;
}

static int lua_led_off(lua_State *L) {
    GPIO_ResetBits(GPIO_LED, PIN_LED_1);
    return 0;
}


static const struct luaL_Reg elib[]=
{
    {"delayms", lua_delay},
    {"led_on", lua_led_on},
    {"led_off", lua_led_off},
    {NULL,NULL}
};