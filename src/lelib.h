#ifndef __LUA_LIB_H
#define __LUA_LIB_H

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

#include "stm32f10x.h"
#include "GPIO_DEF.h"

#include "Delay.h"
#include "LED.h"
#include "OLED.h"
#include "Key.h"
#include "Serial.h"
#include "I2C.h"
#include "ADS1115.h"

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

static int lua_breakpoint(lua_State *L) {
    Serial_Printf("breakpoint");
    return 0;
}

static int lua_Serialprint(lua_State *L) {
    int n = lua_gettop(L);  /* number of arguments */
    int i;
    for (i = 1; i <= n; i++) {  /* for each argument */
        size_t l;
        const char *s = luaL_tolstring(L, i, &l);  /* convert it to string */
        if (i > 1)  /* not the first element? */
            Serial_Printf("\t");  /* add a tab before it */
        Serial_Printf(s);  /* print it */
        lua_pop(L, 1);  /* pop result */
    }
    Serial_Printf("");
    return 0;
}

static const struct luaL_Reg elib[]=
{
    {"delayms", lua_delay},
    {"led_on", lua_led_on},
    {"led_off", lua_led_off},
    {"breakpoint", lua_breakpoint},
    {"sprint", lua_Serialprint},
    {NULL,NULL}
};

#endif /* __LUA_LIB_H */