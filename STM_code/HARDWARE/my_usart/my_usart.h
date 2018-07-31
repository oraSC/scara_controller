#ifndef _my_usart_h
#define _my_usart_h

#include "stm32f10x.h"

void my_usart2_init(u32 boud);
void usart2_send_string(u8 *string);
void usart2_send_num(u32 num);
u8 usart2_wait_receive(void);







#endif


