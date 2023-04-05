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

u16 count=0;
u32 data_1=0;
float ReadAD=0;
extern u8 data_buffer_1[10];
extern char data_buffer_2[400];
extern u8 Rxbuffer_2[400];
// extern u8 Rxcomplete_Flag_2;
// extern u8 Rxcomplete_Flag_1;
char *Databuffer;
char seps[]=",";
char control_buffer[100];
double data_2[100]={0};
double x=0,y=0;
// void data_control_2(void);
// void data_control_1(void);

int main(void)
{
    LED_Init();
    OLED_Init();
    Serial_Init();

    // lua_State *L;
    // L = luaL_newstate();
    // luaopen_base(L);
    // luaL_setfuncs(L, elib, 0);
    // luaL_dostring(L, incbin_luascript_start);

    I2C_GPIOInit();
	ADS115_config();
	Serial_Printf("ADS1115 init success!\n");
	while(1)
	{
		// if(Rxcomplete_Flag_2==1)
		// {//接收到正确数据后，进入数据操作函数
		// 	Rxcomplete_Flag_2=0;
		// 	data_control_2();
		// 	memset(data_buffer_2,0x00,sizeof(data_buffer_2)); //清空数组
		// }	
		// if(Rxcomplete_Flag_1==1)
		// {
		// 	Rxcomplete_Flag_1=0;
		// 	data_control_1();
		// }
        Delay_s(1);
		ReadAD = ADS1115_ReadAD();
        Serial_Printf("ReadAD:%f\n", ReadAD);
	}
}
// void data_control_2(void)
// {
// //以','找出数据
// 	Databuffer=strtok(data_buffer_2,seps);
// 	while(Databuffer!=NULL)
// 	{
// 		strcpy(control_buffer,Databuffer);
// 		data_2[count++]=atof(control_buffer);
// 		Databuffer=strtok(NULL,seps);
			
// 	}
// }	
// void data_control_1(void)
// {
// 	data_1=(data_buffer_1[0]&0xffffffff)<<24;
// 	data_1=data_1|((data_buffer_1[1]&0xffffffff)<<16);
// 	data_1=data_1|((data_buffer_1[2]&0xffffffff)<<8);
// 	data_1=data_1|(data_buffer_1[3]&0xffffffff);
// 	memset(data_buffer_1,0x00,sizeof(data_buffer_1)); //清空数组
// }