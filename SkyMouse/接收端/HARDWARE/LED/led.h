#ifndef __LED_H__
#define __LED_H__
#include "sys.h"

#define LED1 PCout(13)	//LED1对应于GPIOC13

void LED_Init(void);	//LED初始化子函数

#endif
