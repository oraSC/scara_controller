#include "my_usart.h"
#include "delay.h"
#include "LED.h"
#include "MATH.h"
#include "lcd.h"

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
//u8 usart2_wait_receive(void)
//{   u8 rec ;
//	  /** 等待读寄存器非空 **/
//	  //************************
//	  //* 1.开启中断，使用while(USART_GetITStatus(USART2, USART_IT_RXNE)  == RESET) 没用
//	  //* 2.开启中断，会使如下语句一直等待
//	  while( !(USART2->SR & USART2_SR_RXNE) ) ;

//	  rec = USART2->DR ;
//		return rec ;
//}


void USART2_IRQHandler(void)
	{     LED1_ON ;
        if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 
					{
                 USART_ClearITPendingBit(USART2, USART_IT_RXNE);
                 LED2_ON ;
                 }
         
        
}



