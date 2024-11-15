// = girouette en francais
#ifndef __WIND_VANE_H__
#define __WIND_VANE_H__
#include "stm32f10x.h"

#define PI 3.14159265358979323846

void wind_vane_init(TIM_TypeDef * timer);

// Returns an angle (in rads) between 0 and 2pi
float wind_vane_get_angle();

// should be called every time iencoder Z causes GPIO interrupt
void wind_vane_set_zero();

#endif