// = girouette en francais
#ifndef __WIND_VANE_H__
#define __WIND_VANE_H__
#include "stm32f10x.h"

void wind_vane_init(TIM_TypeDef * timer, GPIO_TypeDef * gpio, char pin);

// Returns an angle (in degrees) between 0 and 360
int wind_vane_get_angle();

#endif