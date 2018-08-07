#include "delay.h"
#include "lcd.h"
#include "sys.h"
#include "usart.h"
#include "motor.h"
#include "my_usart.h"
#include "LED.h"
#include "potentiometer.h"


u16 fre[401] ;
u16 allcounter_x = 0 ;


int main()
{

	  
//	u16 ang;
//	u16 i = 0 ;
//***********函数初始化**************//
	/***lcd调试才开启***/
	delay_init(); 
	uart_init(9600) ;
	LCD_Init();
	LED_init() ;
/*** USART2 初始化 ***/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	my_usart2_init(9600) ;
	s_modelline(fre , SPEEDUP_len , MIN_speed , MAX_speed , 6) ;	
	
/*** 电机驱动（PWM）初始化频率 ***/
	motor_init(100 , 72 ) ;
	motor_set_hz(MIN_speed) ;
/*** 电位计 初始化 **/
	potentiometer_init();
	
  while(1) 
	{ 
		
		allcounter_x = usart2_wait_receive_data();
		motor_work ;
//		do
//		{   
//		usart2_send_num(1234) ;
//		 usart2_wait_receive();
			LED1_ON ;
//		 }while(receive_data[i++] != 'Y') ;

//	  LCD_ShowString(0 , 0 , 200 , 16 , 16 , "1234" );
//		LCD_ShowString(0 , 20 , 200 , 16 , 16 , receive_data );
//		delay_ms(1000);
//		ang = get_ang(5) ;
//	  usart2_send_num(ang) ;
//		delay_ms(1000);
		
	}
			 
		 
   	


	 


	



}



