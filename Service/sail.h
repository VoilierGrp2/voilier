#ifndef __SAIL_H__
#define __SAIL_H__
#include "stm32f10x.h"

#define STRAIGHT_SAIL (uint16_t) 0
#define BLOCKING_SAIL (uint16_t) 90

void sail_init(TIM_TypeDef * timer, char channel);

// angle is between 0 and 1 where 0 is straight sail and 1 is blocking sail
void sail_set_angle(uint16_t sail_angle);

#endif