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
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 	//����ģ��HC-05 ������Ϊ115200
	LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ� 
	NRF24L01_Init();    	//��ʼ��NRF24L01
	
  USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(300);
  USB_Port_Set(1);	//USB�ٴ�����
	//USB����
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();
	
	while(NRF24L01_Check())	//���NRF24L01�Ƿ���λ.	
	{
		printf("NRF24L01��ʼ��ʧ�ܣ�\n");
		delay_ms(1000);
	}								   
  NRF24L01_RX_Mode();
	
 	while(1)
	{
			LED1=!LED1;//LED��˸
		  
			if(NRF24L01_RxPacket(tmp_buf))
			{
				printf("%ld û�н��յ��κ����ݣ�\n",num);
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

