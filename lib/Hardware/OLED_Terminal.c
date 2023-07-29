#include "OLED_Terminal.h"
#include "OLED.h"
// #include "Picture.h"
#include "delay.h"

uint8_t col = 1;
uint8_t row = 1;

void Terminal_Clear( void ){
    col = 1;
    row = 1;
    OLED_Clear();
}

void Terminal_NewLine( void ){
    col = 1;
	if( row == 4 ) row = 1;
	else row++;
}

void Terminal_ShowChar( char chr ){
    OLED_ShowChar( row, col++, chr );
	if( col == 16 ){
        col = 1;
        if( row != 4 ) row ++;
        else row = 1;
    }
}

void Terminal_ShowString( char *str ){
    uint8_t i = 0;
    while( str[i] != '\0' ){
        OLED_ShowChar( row, col++, str[i] );
        if( col == 16 ){
            col = 1;
            if( row != 4 ) row ++;
            else row = 1;
        }
        i++;
    }
}

void Terminal_ShowChineseString( int *str ){
    uint8_t i = 0;
    while( str[i] != '\0' ){
        OLED_ShowChinese( row, col, str[i] );
		col += 2;
        if( col == 16 || col == 15 ){
            col = 1;
            if( row != 4 ) row ++;
            else row = 1;
        }
        i++;
    }
}

// void Terminal_ShowLogo( void ){
// 	OLED_ShowPic(Logo, 59, 64);
// 	OLED_ShowString(2, 41, "Wireless");
// 	OLED_ShowString(3, 41, "Charger");
// }

// void Terminal_ShowCharging( void ){
// 	OLED_ShowString(2, 41, "Charging");
// 	OLED_ShowPic(charging_1, 57, 64);
// 	Delay_ms(1000);
// 	OLED_ShowPic(charging_2, 57, 64);
// 	Delay_ms(1000);
// 	OLED_ShowPic(charging_3, 57, 64);
// 	Delay_ms(1000);
// 	OLED_ShowPic(charging_4, 57, 64);
// 	Delay_ms(1000);
// }

// void Terminal_ShowCharged( void ){
// 	OLED_ShowString(2, 41, "Charged");
// 	OLED_ShowPic(charging_4, 57, 64);
// }
