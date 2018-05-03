#include "led.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"

/********************
  *LED��ʼ���Ӻ���*
********************/
//RCT6mini��PC13ΪLED1
//�ߵ�ƽ LED1��
//�͵�ƽ LED1��
void LED_Init(void)					
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*ʹ��GPIOCʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

	/*��ʼ��GPIOC13,����ٶ�50MHz��ͨ���������*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC,&GPIO_InitStructure);

	/*GPIOC13����ߵ�ƽ,GPIOC13��Ӧ��LED1*/
	GPIO_SetBits(GPIOC,GPIO_Pin_13);

}
