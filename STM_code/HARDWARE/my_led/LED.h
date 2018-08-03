#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"

#define LED1_OFF GPIO_SetBits(GPIOE,GPIO_Pin_5);    //PA8输出高电平
#define LED1_ON GPIO_ResetBits(GPIOE,GPIO_Pin_5);   //PA8输出低电平
#define LED2_OFF GPIO_SetBits(GPIOE,GPIO_Pin_6);    //PD2输出高电平
#define LED2_ON GPIO_ResetBits(GPIOE,GPIO_Pin_6);   //PD2输出低电平


void LED_init(void);   /* LED 端口初始化 */

#endif /* __LED_H */


