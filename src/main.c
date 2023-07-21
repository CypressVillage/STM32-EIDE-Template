#include "GPIO_DEF.h"
#include "MODULE_DEF.h"

#define NPT 256 // 采样点数

uint16_t AD0, AD1, AD2, AD3; // 4个通道的AD值

uint32_t adc_buf[NPT] = {0};
long lBufInArray[NPT];
long lBufOutArray[NPT / 2];
long lBufMagArray[NPT / 2];

int main(void)
{
    module_init();
    while (1) {
        AD0 = AD_GetValue(ADC_Channel_0);
        // 填充数组
        for (int i = 0; i < NPT; i++)
            // 这里因为单片机的ADC只能测正的电压 所以需要前级加直流偏执
            // 加入直流偏执后，需要在软件上减去2048即一半，达到负半周期测量的目的（需要根据具体情况来进行配置）
            lBufInArray[i] = ((signed short)(adc_buf[i] - 2048)) << 16;

        cr4_fft_256_stm32(lBufOutArray, lBufInArray, NPT);
    }
}
