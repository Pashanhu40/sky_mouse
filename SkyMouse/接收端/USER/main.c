#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"        
#include "spi.h"
#include "nrf24l01.h" 
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h" 



 int main(void)
{     
	u8 tmp_buf[32];
  uint16_t ADC_value;
	long num=0;
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 	//蓝牙模块HC-05 波特率为115200
	LED_Init();		  			//初始化与LED连接的硬件接口 
	NRF24L01_Init();    	//初始化NRF24L01
	
  USB_Port_Set(0); 	//USB先断开
	delay_ms(300);
  USB_Port_Set(1);	//USB再次连接
	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();
	
	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{
		printf("NRF24L01初始化失败！\n");
		delay_ms(1000);
	}								   
  NRF24L01_RX_Mode();
	
 	while(1)
	{
			LED1=!LED1;//LED闪烁
		  
			if(NRF24L01_RxPacket(tmp_buf))
			{
				printf("%ld 没有接收到任何数据！\n",num);
				num++;
			}
		  else
			{
				ADC_value = tmp_buf[0] | tmp_buf[1] << 8;
				printf("%ld %d\n",num,ADC_value);
				num++;
			}
      //Joystick_Send(tmp_buf[0],tmp_buf[1],tmp_buf[2],tmp_buf[3]);
//		  	Joystick_Send(1,2,3,4);
	}

} 	

