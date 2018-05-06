#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"
#include "adc.h"
#include "key.h"
#include "timer.h"
#include "mouse.h"
#include "mpu6050.h"  
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "ano_tech.h"
#include "spi.h"
#include "nrf24l01.h" 

	
 int main(void)
 { 
   
//	float pitch,roll,yaw; 		//欧拉角
//	short aacx,aacy,aacz;		//加速度传感器原始数据
//	short gyrox,gyroy,gyroz;	//陀螺仪原始数据	    
	uint8_t temp_buffer[32];
  extern uint8_t KEY_State[4];
	extern __IO uint16_t ADCConvertedValue;
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  TIM4_Config(1999,71);  //2ms中断
	delay_init();	    	   //延时函数初始化	  
	uart_init(115200);	 	 //蓝牙模块TF-01 波特率为115200
	LED_Init();		  			 //初始化与LED连接的硬件接口
  KEY_Init();	 
  NRF24L01_Init();    	 //初始化NRF24L01
	MPU_Init();					   //初始化MPU6050 
	ADC1_Init();
	
	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{
		
		printf("NRF24L01初始化失败！\n");
	}	
	
  NRF24L01_TX_Mode();
	
 	while(1)
	{   
	
		  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		
      //printf("%f\n",Read_ADC());
		
		   printf("%f\n",ADCConvertedValue*3.30/0xfff);
		
			//mpu_dmp_get_data(&pitch,&roll,&yaw);
		  
		  //MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
			//MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
	   // mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//用自定义帧发送加速度和陀螺仪原始数据
			//usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,(int)(roll*100),(int)(pitch*100),(int)(yaw*10));
  
    
			
		  
//      sprintf(tmp_buf,"%.2f  %.2f  %.2f",pitch,roll,yaw);
//			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
//  		{
//				printf("%ld 发送成功！\n",num);
//			}
//		  else
//			{
//				printf("%ld 发送失败！\n",num);
//				err_num++;
//			}
        Mouse_FormatFill(temp_buffer);
				NRF24L01_TxPacket(temp_buffer);
			  
			//printf("%ld:  %f  %f  %f\n",num,pitch,roll,yaw);
			//printf("%d,%d,%d,%d\n",KEY_State[0],KEY_State[1],KEY_State[2],KEY_State[3]);	
		
	}

} 	

