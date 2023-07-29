#include "GPIO_DEF.h"
#include "MODULE_DEF.h"

int main(void)
{
    module_init();

    u8 buf[50] = {0};
    u8 pbuf = 0;
    u8 data = 0;

    while (1) {
        if (Serial_GetRxFlag()){
            data = Serial_GetRxData();
            if (data == '\n') {
                buf[pbuf] = '\0';
                Serial_SendString(buf);
                Terminal_Clear();
                Terminal_ShowString(buf);
                pbuf = 0;
            } else {
                buf[pbuf++] = data;
            }
        }
    }
}
