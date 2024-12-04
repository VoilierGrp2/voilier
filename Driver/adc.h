#ifndef __ADC_H__
#define __ADC_H__
#include "stm32f10x.h"

// pr�pare le prescaler
void adc_init(ADC_TypeDef * adc);

#define SAMPLE_TIME_1_5 0
#define SAMPLE_TIME_41_5 4
#define SAMPLE_TIME_239_5 7

// For sample time see above
void adc_conf(ADC_TypeDef * adc, int prescaler_divisor, int channel_number, char sample_time);

// trigger puis donne la valeur de l'adc x
int adc_get_value(ADC_TypeDef * adc);

#endif