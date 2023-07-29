#ifndef __OLED_TERMINAL_H
#define __OLED_TERMINAL_H

#include <stdio.h>

// void Terminal_SetMod( uint8_t mod );
void Terminal_Clear( void );
void Terminal_NewLine( void );
void Terminal_ShowChar( char chr );
void Terminal_ShowString( char *str );
void Terminal_ShowChineseString( int *str );

void Terminal_ShowLogo( void );
void Terminal_ShowCharging( void );
void Terminal_ShowCharged( void );

#endif
