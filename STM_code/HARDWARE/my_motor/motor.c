#include "motor.h"


void motor_init( u16 period , u16 prescaler )
{

  GPIO_InitTypeDef GPIO_InitStructure_PA1 ;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInit_TIM2 ;
	TIM_OCInitTypeDef TIM_OCInit_TIM2_CH2 ;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);
	
	GPIO_InitStructure_PA1.GPIO_Pin = GPIO_Pin_1 ;
	GPIO_InitStructure_PA1.GPIO_Mode = GPIO_Mode_AF_PP ;
	GPIO_InitStructure_PA1.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA , &GPIO_InitStructure_PA1) ;
	
	TIM_TimeBaseInit_TIM2.TIM_ClockDivision = 0 ;
	TIM_TimeBaseInit_TIM2.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInit_TIM2.TIM_Period = period ;
	TIM_TimeBaseInit_TIM2.TIM_Prescaler = prescaler ;
	TIM_TimeBaseInit(TIM2 , &TIM_TimeBaseInit_TIM2) ; 
	
	TIM_OCInit_TIM2_CH2.TIM_OCMode = TIM_OCMode_PWM2 ;
	TIM_OCInit_TIM2_CH2.TIM_OCPolarity = TIM_OCPolarity_High ;
	TIM_OCInit_TIM2_CH2.TIM_OutputState = TIM_OutputState_Enable ;
	TIM_OC2Init(TIM2 , &TIM_OCInit_TIM2_CH2) ;
	
	TIM_OC2PreloadConfig(TIM2 , TIM_OCPreload_Enable) ;
	TIM_Cmd(TIM2 , ENABLE) ;
	
}

void motor_set_hz( u16 hz)
{
  u16 prescaler ;
	u16 half_hz ;
	prescaler = TIM_GetPrescaler(TIM2) ;
  hz = 72000000/prescaler/hz ;
	half_hz = hz/2 ;
  TIM2->ARR = hz ;
  TIM2->CCR2 = half_hz ;
	
}







