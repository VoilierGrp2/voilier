#ifndef __ADC_H__
#define __ADC_H__
#include "stm32f10x.h"

// prépare le prescaler
void adc_init(ADC_TypeDef * adc);

// trigger puis donne la valeur de l'adc x
int adc_get_value(ADC_TypeDef * adc);

#endif