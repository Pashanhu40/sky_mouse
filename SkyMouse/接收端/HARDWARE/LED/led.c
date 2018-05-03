#include "led.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

/********************
  *LED初始化子函数*
********************/
//RCT6mini中PC13为LED1
//高电平 LED1灭
//低电平 LED1亮
void LED_Init(void)					
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*使能GPIOC时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	/*初始化GPIOC13,输出速度50MHz，通用推挽输出*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	/*GPIOC13输出高电平,GPIOC13对应于LED1*/
	GPIO_SetBits(GPIOC,GPIO_Pin_13);

}
