#ifndef _KEY_H
#define _KEY_H

#include "stm32f10x.h"

#define READ_LEFT   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4);
#define READ_MIDDLE GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_3);
#define READ_RIGHT  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5);
#define READ_KEY4   1;   //GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2);


void KEY_Init(void);
void KEY_Scan(void);
void KEY_Process(void);


#endif

