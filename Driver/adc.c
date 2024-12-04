#include "adc.h"
#include "stm32f10x.h"

void adc_init(ADC_TypeDef * adc) {
	switch ((int)adc) {
		case (int)ADC1:
			RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
			break;
		case (int)ADC2:
			RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
			break;
	}
}

void adc_conf(ADC_TypeDef * adc, int prescaler_divisor, int channel_number, char sample_time) {
	// use div 6
	switch (prescaler_divisor) {
		case 2:
			RCC->CFGR |= RCC_CFGR_ADCPRE_DIV2;
			break;
		case 4:
			RCC->CFGR |= RCC_CFGR_ADCPRE_DIV4;
			break;
		case 6:
			RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
			break;
		case 8:
			RCC->CFGR |= RCC_CFGR_ADCPRE_DIV8;
			break;
	}

	// Configure to continous single mode
	adc->CR2 |= ADC_CR2_CONT;
	adc->CR1 &= ~ADC_CR1_SCAN;

	// Configure the sampling time on the given channel
	if (channel_number <= 9) {
		adc->SMPR2 &= ~(0b111<<(channel_number*3));
		adc->SMPR2 |= sample_time << (channel_number*3);
	} else {
		int shift = (channel_number-10)*3;
		adc->SMPR1 &= ~(0b111<<shift);
		adc->SMPR1 |= sample_time << shift;
	}

	// Configure the sequence to only read from channel channel_number on first conversion
	adc->SQR3 |= 0x1F & channel_number;

	// Enable the ADC
	adc->CR2 |= ADC_CR2_ADON;
}

int adc_get_value(ADC_TypeDef * adc) {
	// Send trigger to start conversion
	adc->CR2 |= ADC_CR2_ADON;

	// Wait for the end of the conversion
	// (no need for interrupts at this scale)
	while ((adc->SR & ADC_SR_EOC) == 0);

	// get the value
	uint32_t value = adc->DR;

	// Return the value
	return value;
}
