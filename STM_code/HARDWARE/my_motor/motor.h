#ifndef _motor_h
#define _motor_h

#include "stm32f10x.h"


typedef struct
{
  u32 pwn_hz ;
	u32 last_position ;
	u32 now_position ;
	u32 next_position ;
  
} motor	;


void motor_init(u16 period , u16 prescaler) ;
void motor_set_hz( u16 hz ) ;







#endif



