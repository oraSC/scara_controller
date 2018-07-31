#include "my_usart.h"
#include "delay.h"

void my_usart2_init(u32 boud)
{
	GPIO_InitTypeDef GPIO_InitStructure_PA2 ;
	GPIO_InitTypeDef GPIO_InitStructure_PA3 ;
	USART_InitTypeDef USART_InitStructure_USART2 ;
	NVIC_InitTypeDef NVIC_InitStructure_USART2 ;
	
/*** 使能USART2、GPIOA时钟 ***/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 , ENABLE) ;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE) ;
	
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
	NVIC_InitStructure_USART2.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure_USART2.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure_USART2.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure_USART2);	//根据指定的参数初始化VIC寄存器
  
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
  USART_Cmd(USART2 , ENABLE) ;
  

}

void USART2_IRQHandler(void)                	//串口1中断服务程序
{
 u8 rec ;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		rec = USART2->DR ;
		delay_ms(1000);
		USART_SendData(USART2 , rec);
		
	
	
	}
	



	
} 



