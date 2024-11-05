#include "adc.h"
#

void adc_init() {
	RCC->CFGR = RCC_CFGR_ADCPRE_DIV6;
}

void adc_enable(int x) {
	// TODO regarder les modes, demander pour CONT et DISCNUM
	(void) x;
	if (x == 1) {
		ADC1->CR1 &= ~(ADC_CR1_DISCNUM);
		RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	}
	else {
		ADC2->CR1 &= ~(ADC_CR1_DISCNUM);
		RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	}
}

int adc_get_value(int x) {
	(void) x;
	// send trigger
	// wait for EOC flag
	// fetch and return value
	return 0;
}
