#ifndef __BATTERY_H__
#define __BATTERY_H__
#include "stm32f10x.h"

void battery_init(ADC_TypeDef * adc, int channel, GPIO_TypeDef * gpio, int pin);

int battery_get_percentage();

#endif