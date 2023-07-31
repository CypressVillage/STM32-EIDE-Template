#ifndef __WT1_IMU_H__
#define __WT1_IMU_H__

#include <string.h>
#include <stdio.h>
#include "wit_c_sdk.h"

#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80

#define Usart1Init(x)	Serial_Init(x)
#define Uart1Send(x,y)	Serial_SendArray(x,y)

extern char s_cDataUpdate;
extern char s_cCmd;
extern uint32_t c_uiBaud[10];


void CmdProcess(void);
void AutoScanSensor(void);
void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
void Delayms(uint16_t ucMs);

void WT1_IMU_Init(void);

#endif