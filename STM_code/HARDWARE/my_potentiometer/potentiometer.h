#ifndef _potentiometer_h
#define _potentiometer_h
#include "sys.h"

void potentiometer_init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
u16 get_ang(u16 time);

#endif 
