#include "delay.h"
#include "lcd.h"
#include "sys.h"
#include "usart.h"
#include "motor.h"
#include "my_usart.h"
#include "LED.h"
#include "potentiometer.h"

u16 fre[500] ;

int main()
{

//	u16 ang;
//	u16 i = 0 ;
//***********函数初始化**************//
	/***lcd调试才开启***/
	delay_init(); 
//	uart_init(9600) ;
//	LCD_Init();
	LED_init() ;
/*** USART2 初始化 ***/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	my_usart2_init(9600) ;
	s_modelline(fre , 400 , 1500 , 7000 , 6) ;	
	
/*** 电机驱动（PWM）初始化频率 ***/
	motor_init(100 , 72 ) ;
	motor_set_hz(1500) ;
/*** 电位计 初始化 **/
	potentiometer_init();
  while(1) 
	{   
	  //ang = get_ang(10);
		//LCD_ShowxNum(10,10 ,ang,3,16,0) ;
	
	}
			 
		 
   	


	 


	



}



