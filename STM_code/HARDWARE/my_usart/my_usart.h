#ifndef _my_usart_h
#define _my_usart_h

#include "stm32f10x.h"

#define USART2_SR_TC 6
//#define USART2_SR_RXNE 0000000000100000


void my_usart2_init(u32 boud);
void usart2_send_string(u8 *string);
void usart2_send_char(u8 _char);
void usart2_send_num(u32 num);
u16 usart2_wait_receive_data(void);
u16 data_string2num(u8 *_string , u16 len);
//u8 usart2_wait_receive(void);







#endif


