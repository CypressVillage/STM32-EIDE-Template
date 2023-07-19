#ifndef __DELAY_H
#define __DELAY_H

void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);

#define delay_us Delay_us
#define delay_ms Delay_ms
#define delay_s Delay_s

#endif
