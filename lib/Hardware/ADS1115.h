#ifndef ADS1115_H
#define ADS1115_H
#include "I2C.h"
/*******************************************************************************
ADDR--GND
SLAVE ADDRESS 0X90
*******************************************************************************/  

/*****************Pointer Register*************/
#define REG_Conversion 0x00
#define REG_config		 0x01
#define REG_L_thresh 	 0x02
#define REG_H_thresh 	 0x03

/*****************Conversion Register**********/
//存放着16位结果

/*****************Config Register**********/
#define OS 		1 		//Operational status or single-shot conversion start
#define MUX 	0x04 	//[2:0]Input multiplexer configuration
#define PGA 	0x01	//Programmable gain amplifier configuration
#define MODE  0x00	//Device operating mode

 

#define DR				0x04//Data rate
#define	COMP_MODE	0 	// Comparator mode
#define COMP_POL 	0		//Comparator polarity
#define COMP_LAT	0 	//Latching comparator
#define COMP_QUE	0x3	//Comparator queue and disable

#define config_MSB (OS << 7)|(MUX << 4)|(PGA << 1)|(MODE)//0xC2
#define config_LSB (DR << 5)|(COMP_MODE << 4)|(COMP_POL << 3)|(COMP_LAT << 2)|(COMP_QUE)

/*****************Lo_thresh Register**********/
#define Lo_thresh	0x8000	// Low threshold value
#define Hi_thresh 0x7FFF	// High threshold value

void ADS1115_Write(u8 Reg , u8 reg_MSB , u8 reg_LSB);
float ADS1115_ReadAD(void);
void ADS115_config(void);
#endif
