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
   
//	float pitch,roll,yaw; 		//ŷ����
//	short aacx,aacy,aacz;		//���ٶȴ�����ԭʼ����
//	short gyrox,gyroy,gyroz;	//������ԭʼ����	    
	uint8_t temp_buffer[32];
  extern uint8_t KEY_State[4];
	extern __IO uint16_t ADCConvertedValue;
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  TIM4_Config(1999,71);  //2ms�ж�
	delay_init();	    	   //��ʱ������ʼ��	  
	uart_init(115200);	 	 //����ģ��TF-01 ������Ϊ115200
	LED_Init();		  			 //��ʼ����LED���ӵ�Ӳ���ӿ�
  KEY_Init();	 
  NRF24L01_Init();    	 //��ʼ��NRF24L01
	MPU_Init();					   //��ʼ��MPU6050 
	ADC1_Init();
	
	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
	{
		
		printf("NRF24L01��ʼ��ʧ�ܣ�\n");
	}	
	
  NRF24L01_TX_Mode();
	
 	while(1)
	{   
	
		  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		
      //printf("%f\n",Read_ADC());
		
		   printf("%f\n",ADCConvertedValue*3.30/0xfff);
		
			//mpu_dmp_get_data(&pitch,&roll,&yaw);
		  
		  //MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
			//MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
	   // mpu6050_send_data(aacx,aacy,aacz,gyrox,gyroy,gyroz);//���Զ���֡���ͼ��ٶȺ�������ԭʼ����
			//usart1_report_imu(aacx,aacy,aacz,gyrox,gyroy,gyroz,(int)(roll*100),(int)(pitch*100),(int)(yaw*10));
  
    
			
		  
//      sprintf(tmp_buf,"%.2f  %.2f  %.2f",pitch,roll,yaw);
//			if(NRF24L01_TxPacket(tmp_buf)==TX_OK)
//  		{
//				printf("%ld ���ͳɹ���\n",num);
//			}
//		  else
//			{
//				printf("%ld ����ʧ�ܣ�\n",num);
//				err_num++;
//			}
        Mouse_FormatFill(temp_buffer);
				NRF24L01_TxPacket(temp_buffer);
			  
			//printf("%ld:  %f  %f  %f\n",num,pitch,roll,yaw);
			//printf("%d,%d,%d,%d\n",KEY_State[0],KEY_State[1],KEY_State[2],KEY_State[3]);	
		
	}

} 	

