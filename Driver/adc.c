#include "adc.h"
#

void adc_init(ADC_TypeDef * adc) {
	(void) adc;
	RCC->CFGR = RCC_CFGR_ADCPRE_DIV6;
	// TODO regarder les modes, demander pour CONT et DISCNUM
	if (adc == ADC1) {
		ADC1->CR1 &= ~(ADC_CR1_DISCNUM);
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}
	else {
		ADC2->CR1 &= ~(ADC_CR1_DISCNUM);
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	}
}

int adc_get_value(ADC_TypeDef * adc) {
	(void) adc;
	// send trigger
	// wait for EOC flag
	// fetch and return value
	return 0;
}
