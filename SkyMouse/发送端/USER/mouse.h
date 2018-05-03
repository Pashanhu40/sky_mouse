/*******************************************************************************
* File Name      : mouse.h
* Author         : Mr.Wang
* Version        : V1.0
* Date           : 2018/4/15
* Brief          : 
*******************************************************************************/
#ifndef _MOUSE_H
#define _MOUSE_H

#include "stm32f10x.h"

void Mouse_FormatFill(uint8_t* temp_buffer);
void Mouse_DataProcessing(short *ax,short *ay,short *az);


#endif



