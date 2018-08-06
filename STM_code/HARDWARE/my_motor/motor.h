#ifndef _motor_h
#define _motor_h

#include "stm32f10x.h"

#define MAX_speed     7500 
#define MIN_speed     1500 
#define SPEEDUP_len   400

//typedef struct
//{
//  u32 pwn_hz ;
//	u32 last_position ;
//	u32 now_position ;
//	u32 next_position ;
//  
//} motor	;
//½ûÖ¹¼ÆÊýÆ÷
#define motor_stop 		TIM2->CR1 &= ~TIM_CR1_CEN 
#define motor_work    TIM2->CR1 |= TIM_CR1_CEN 

void motor_init(u16 period , u16 prescaler) ;
void motor_set_hz( u16 hz ) ;
u16  motor_get_hz(void) ; 
void s_modelline(u16 *fre , u16 len , u16 fre_min , u16 fre_max , u16 flexible)  ;






#endif



