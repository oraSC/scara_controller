#include "delay.h"
#include "lcd.h"
#include "sys.h"
#include "usart.h"
#include "motor.h"
#include "my_usart.h"

int main()
{
//	u8 a = 'A' ;
//***********函数初始化**************//
	/***lcd调试才开启***/
	delay_init(); 
//	uart_init(9600) ;
//	LCD_Init();
  	
/*** USART2 初始化 ***/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	my_usart2_init(9600) ;
	
/*** 电机驱动（PWM）初始化频率 ***/
	motor_init(100 , 72 ) ;
	motor_set_hz(1000) ;
	my_usart2_init(9600) ;
  
  while(1) 
	{
	  
	
	
	}
			 
		 
   	


	 


	



}



