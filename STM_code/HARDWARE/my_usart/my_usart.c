#include "my_usart.h"
#include "delay.h"
#include "LED.h"
#include "MATH.h"
#include "lcd.h"

u16 receive_len = 0;
u8 receive_data[20];
u8 wait_receive_Y = 0 ;

void my_usart2_init(u32 boud)
{
	GPIO_InitTypeDef GPIO_InitStructure_PA2 ;
	GPIO_InitTypeDef GPIO_InitStructure_PA3 ;
	USART_InitTypeDef USART_InitStructure_USART2 ;
	NVIC_InitTypeDef NVIC_InitStructure_USART2 ;
	
/*** 使能USART2、GPIOA时钟 ***/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE) ;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE) ;
	
	USART_DeInit(USART2);
	
/*** GPIO初始化配置 ***/
	/** USART2_TX ---> PA2 **/
	/** USART2_RX ---> PA3 **/
	GPIO_InitStructure_PA2.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStructure_PA2.GPIO_Mode = GPIO_Mode_AF_PP ;
	GPIO_InitStructure_PA2.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA , &GPIO_InitStructure_PA2) ;
	
	GPIO_InitStructure_PA3.GPIO_Pin = GPIO_Pin_3 ;
	GPIO_InitStructure_PA3.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	GPIO_InitStructure_PA3.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA , &GPIO_InitStructure_PA3) ;

/*** USART2 初始化配置 ***/
  /** 无硬件数据流控制 、接送以及发送模式 、 无奇偶校验 、 八位字节长 **/
	/** USART2 接收中断配置 **/
	/** 开启USART2接受、使能USART2 **/
	USART_InitStructure_USART2.USART_BaudRate = boud ;
	USART_InitStructure_USART2.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	USART_InitStructure_USART2.USART_Mode = USART_Mode_Rx | USART_Mode_Tx ;
	USART_InitStructure_USART2.USART_Parity = USART_Parity_No ;
	USART_InitStructure_USART2.USART_StopBits = USART_StopBits_1 ;
	USART_InitStructure_USART2.USART_WordLength = USART_WordLength_8b ;
	USART_Init(USART2 , &USART_InitStructure_USART2) ;

  NVIC_InitStructure_USART2.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure_USART2.NVIC_IRQChannelPreemptionPriority=0 ;//抢占优先级3
	NVIC_InitStructure_USART2.NVIC_IRQChannelSubPriority = 0;		//子优先级3
	NVIC_InitStructure_USART2.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure_USART2);	//根据指定的参数初始化VIC寄存器

	USART_ITConfig(USART2, USART_IT_RXNE , ENABLE);
//	USART_ITConfig(USART2, USART_IT_TC , ENABLE);     
  USART_Cmd(USART2 , ENABLE) ;

}

void usart2_send_char(u8 _char)
{/** 等待发送完成 **/
	/* USART2_SR_TC 发送完成标志位*/
	while( !(USART2->SR & (1 << USART2_SR_TC) )) ;
	USART2->DR = _char ;
}

void usart2_send_string(u8 *string)
{
	
	while(*string)
	{ /** 等待发送完成 **/
		while( !(USART2->SR & (1 << USART2_SR_TC))) ;
		USART2->DR = *string ;
    string ++ ;
	}
}	
void usart2_send_num(u32 num)
{
   u16 len = 0 ;
	 u16 i;
	 u8  num_string[10]= "" ;
	 u32 numcopy = num ;
	if(num == 0)
	{
		usart2_send_char('0');
	}
	else 
	{
			/** 判断位数 **/
			 while(numcopy)
			 {
					numcopy = numcopy / 10 ;
					len ++ ;
			 }

			 for( i = 0 ; i < len ; i++)
			 {/** 提取各个位 **/
				 num_string[i] = (u32)(num / pow(10 , len - i -1)) % 10 + '0';
			 }
			 usart2_send_string(num_string);
		 }
}

u16 usart2_wait_receive_data(void)
{
    u8 data_x[10];
	  u16 data_x_len = 0 ;
	  u8 data_y[10];
	  u16 data_y_len = 0 ;
	  u16 i = 0;
	  u16 j = 0;
	  u16 distance_x = 0;
	  u16 distance_y = 0;
	
		while(!wait_receive_Y);
    LCD_ShowString(0 , 20 , 200 , 16 , 16 , receive_data );
	  /** 切割receive_data **/
    for( ; receive_data[i] !='X' ; i++)
	  {
		 /** 符号位 **/
		 if( i == 0 )
		    {}
		 else 
		    {
					data_x[data_x_len ++] = receive_data[i];
				}
		}
    
		distance_x = data_string2num(data_x , data_x_len) ;
		LCD_ShowNum(0 , 40 ,  distance_x , 10 , 16  );
    /** 切割receive_data **/
    for( j = i + 1; receive_data[j] !='Y' ; j++)
	  {
		 /** 符号位 **/
		 if( j == i + 1 )
		    {}
		 else 
		    {
					data_y[data_y_len ++] = receive_data[j];
				}
		}
		distance_y = data_string2num(data_y , data_y_len) ;
		LCD_ShowNum(0 , 60 ,  distance_y , 10 , 16  );
		return distance_x ;
}

u16 data_string2num(u8 *_string , u16 len)
{   
	u16 i = 0 ;
	u16 num = 0 ;
    for( ; i < len ; i++)
	   {
		     num += (*_string - '0' )*pow(10 , len - i - 1) ;
			   _string ++ ;
		 }
     return num ;



}



//******************************
//*无法使用
//*****************************
//u8 usart2_wait_receive(void)
//{   u8 rec ;
//	  /** 等待读寄存器非空 **/
//	  //************************
//	  //* 1.开启中断，使用while(USART_GetITStatus(USART2, USART_IT_RXNE)  == RESET) 没用
//	  //* 2.开启中断，会使如下语句一直等待
//	  while( !(USART2->SR & USART2_SR_RXNE) ) ;
//    
//	  rec = USART2->DR ;
//		return rec ;
//}


void USART2_IRQHandler(void)
	{     
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 
		{
			receive_data[receive_len ]  = USART_ReceiveData(USART2) ;
			if(receive_data[receive_len] == 'Y')
				wait_receive_Y   = 1 ;
			else 
				receive_len ++ ;
			
			USART_ClearITPendingBit(USART2 , USART_IT_RXNE);
		}
               
}



