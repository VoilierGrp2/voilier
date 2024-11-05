#ifndef __ADC_H__
#define __ADC_H__
#include "adc.h"
#include "stm32f10x.h"

// prépare le prescaler
void adc_init();

// clock l'adc x
void adc_enable(int x);

// trigger puis donne la valeur de l'adc x
int adc_get_value(int x);

#endif