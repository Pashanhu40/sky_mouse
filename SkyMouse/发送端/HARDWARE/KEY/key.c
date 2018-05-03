/*******************************************************************************
* File Name      : key.c
* Author         : Mr.Wang
* Version        : V1.0
* Date           : 2018/4/15
* Brief          : 按键驱动
*******************************************************************************/
#include "key.h"

uint8_t KEY_State[4];     //按键是否被摁下标志位
uint8_t KEY_Backup[4];


/*******************************************************************************
* Function Name  : KEY_Init
* Description    : 
* Input          : none
* Output         : none
* Return         : none
*******************************************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
}

/*******************************************************************************
* Function Name  : KEY_Scan
* Description    : 按键扫描，参考《手把手教你学51》例程
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void KEY_Scan(void)  
{
	 static uint8_t left_key   = 0xFF;
	 static uint8_t middle_key = 0xFF;
	 static uint8_t right_key  = 0xFF;
   static uint8_t key_buff4  = 0xFF;
	
	 left_key   = (left_key  << 1)   | READ_LEFT;
	 middle_key = (middle_key << 1)  | READ_MIDDLE;
	 right_key  = (right_key  << 1)  | READ_RIGHT;
	 key_buff4  = (key_buff4  << 1)  | READ_KEY4;	
//鼠标左键
	 if(left_key == 0x00)
	 {
			KEY_State[0] = 1;
	 }
	 else if(left_key == 0xFF)
	 {
			KEY_State[0] = 0;
	 } 
//鼠标中键
	 if(middle_key == 0x00)
	 {
			KEY_State[1] = 1;
	 }
	 else if(middle_key == 0xFF)
	 {
			KEY_State[1] = 0;
	 } 
//鼠标右键
	 if(right_key == 0x00)
	 {
			KEY_State[2] = 1;
	 }
	 else if(right_key == 0xFF)
	 {
			KEY_State[2] = 0;
	 } 
//KEY4
	 if(key_buff4 == 0x00)
	 {
			KEY_State[3] = 1;
	 }
	 else if(key_buff4 == 0xFF)
	 {
			KEY_State[3] = 0;
	 } 	 
	 
}

void KEY_Process(void)
{
//	static uint8_t counter0;
//	static uint8_t counter1;
//	static uint8_t counter2;
//	static uint8_t counter3;
	
	
//KEY1	
	if(KEY_State[0] != KEY_Backup[0])
	{
		if(KEY_Backup[0] == 0)
		{
			
    }
		KEY_Backup[0] = KEY_State[0];
  }
	
//KEY2
	if(KEY_State[1] != KEY_Backup[1])
	{
		if(KEY_Backup[1] == 0)
		{

    }
		KEY_Backup[1] = KEY_State[1];
  }
	
//KEY3	
	if(KEY_State[2] != KEY_Backup[2])
	{
		if(KEY_Backup[2] == 0)
		{
			

		}
		KEY_Backup[2] = KEY_State[2];
	}

	//KEY4
  if(KEY_State[3] != KEY_Backup[3])
	{
		if(KEY_Backup[3] == 0)
		{
		  	
			
    }
		KEY_Backup[3] = KEY_State[3];
  }
}



	