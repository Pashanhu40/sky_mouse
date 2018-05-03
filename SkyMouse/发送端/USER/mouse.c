/*******************************************************************************
* File Name      : mouse.c
* Author         : Mr.Wang
* Version        : V1.0
* Date           : 2018/4/15
* Brief          : 多媒体鼠标数据处理函数
*******************************************************************************/
#include "mouse.h"
#include "mpu6050.h"

extern uint8_t KEY_State[4];

/*******************************************************************************
* Function Name  : Mouse_FormatFill
* Description    : 
* Input          : uint8_t* temp_buffer
* Output         : 
* Return         : 
*******************************************************************************/
void Mouse_FormatFill(uint8_t* temp_buffer)
{
	short gyrox,gyroy,gyroz;
	short Mouse_X,Mouse_Y,Mouse_Z;
	
	//获取角速度数据
	MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);
	//处理鼠标位移数据
  Mouse_DataProcessing(&gyrox,&gyroy,&gyroz);
	
	Mouse_X = gyrox&0xFF;
  Mouse_Y = gyroy&0xFF;
	Mouse_Z = gyroz&0xFF;
	
	if(gyrox&0x8000)
	{
		Mouse_X = Mouse_X|0x80;
	}
	if(gyroy&0x8000)
	{
		Mouse_Y = Mouse_Y|0x80;
	}
	if(gyroz&0x8000)
	{
		Mouse_Z = Mouse_Z|0x80;
	}
	//鼠标X,Y轴的变化量
  temp_buffer[1] = Mouse_Y;
	temp_buffer[2] = Mouse_X;
	//滚轮暂时为0
	temp_buffer[3] = 0;
	
	//获取鼠标按键数据
	if(KEY_State[0] == 1)
	{
		//左键按下
		temp_buffer[0] = 0X01;		
	}
	else if(KEY_State[1] == 0)
	{
		//中键按下
		temp_buffer[0] = 0X04;
	}
	else if(KEY_State[2] == 1)
	{
		//右键按下
		temp_buffer[0] = 0X02;
	}
	else
	{
		temp_buffer[0] =0;
	}
	
}
/*******************************************************************************
* Function Name  : Mouse_DataProcessing
* Description    : 鼠标位移数据处理
* Input          : short *ax,short *ay,short *az
* Output         : 
* Return         : 
*******************************************************************************/
void Mouse_DataProcessing(short *ax,short *ay,short *az)
{
		float tempx,tempy,tempz,tempx1,tempy1,tempz1;
		tempx = *ax/1000-1;
		tempy = *ay/1000-1;
		tempz = *az/1000-1;
		tempx1 = *ax%1000/100;
		tempy1 = *ay%1000/100;
		tempz1 = *az%1000/100;
	
		if(tempz==-1 || tempz==-2)
		{*az = 0;}
		else if(tempz>-1)
		{*az = tempz*13+tempz1*2;}
		else
		{*az = (tempz+2)*13+tempz*2;}
		
		if(tempx==-1 ||tempx == -2)
		{*ax=0;}
		else if(tempx>-1)
		{*ax = tempx*13+tempx1*2;}
		else
		{*ax = (tempx+2)*13+tempx1*2;}
		
		if(tempy==-1 ||tempy == -2) 
		{*ay = 0;}
		else if(tempy>-1)
		{*ay = tempy*13+tempy1*2;}
		else
		{*ay = (tempy+2)*13+tempy1*2;}
}





