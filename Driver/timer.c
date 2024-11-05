#include "timer.h"

void timer_enable(TIM_TypeDef * timer) {
	if (timer == TIM1) RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	else if (timer == TIM2) RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	else if (timer == TIM3) RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	else if (timer == TIM4) RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
}

void timer_init(TIM_TypeDef * timer, unsigned short arr, unsigned short psc) {
	timer->ARR = arr-1;
	timer->PSC = psc-1;
}

void (*tim1_it_function)();
void (*tim2_it_function)();
void (*tim3_it_function)();
void (*tim4_it_function)();

void timer_active_it(TIM_TypeDef * timer, char prio, void (*it_function)()) {
	// activer "port" correspondant sur NVIC
	
	char vector;
	if (timer == TIM1) {
		vector = 25;
		tim1_it_function = it_function;
	}
	else if (timer == TIM2) {
		vector = 28;
		tim2_it_function = it_function;
	}
	else if (timer == TIM3) {
		vector = 29;
		tim3_it_function = it_function;
	}
	else {
		vector = 30;
		tim4_it_function = it_function;
	}
	
	NVIC_EnableIRQ(vector);
	NVIC_SetPriority(vector, prio);

	timer->DIER |= TIM_DIER_UIE;
	
}

void TIM1_UP_IRQHandler() {
	TIM1->SR &= ~(TIM_SR_UIF);
	tim1_it_function();
}

void TIM2_IRQHandler() {
	TIM2->SR &= ~(TIM_SR_UIF);
	tim2_it_function();
}

void TIM3_IRQHandler() {
	TIM3->SR &= ~(TIM_SR_UIF);
	tim3_it_function();
}

void TIM4_IRQHandler() {
	TIM4->SR &= ~(TIM_SR_UIF);
	tim4_it_function();
}

void timer_pwm_enable(TIM_TypeDef * timer, char channel) {
	if (timer == TIM1) {
		timer->BDTR |= TIM_BDTR_MOE;
	}
	if (channel == 1) {
		timer->CCMR1 &= ~(TIM_CCMR1_CC1S);
		timer->CCMR1 &= ~(TIM_CCMR1_OC1M);
		timer->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1;
		timer->CCER |= TIM_CCER_CC1E;
	}
	else if (channel == 2) {
		timer->CCMR1 &= ~(TIM_CCMR1_CC2S);
		timer->CCMR1 &= ~(TIM_CCMR1_OC2M);
		timer->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1;
		timer->CCER |= TIM_CCER_CC2E;
	}
	else if (channel == 3) {
		timer->CCMR2 &= ~(TIM_CCMR2_CC3S);
		timer->CCMR2 &= ~(TIM_CCMR2_OC3M);
		timer->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1;
		timer->CCER |= TIM_CCER_CC3E;
	}
	else {
		timer->CCMR2 &= ~(TIM_CCMR2_CC4S);
		timer->CCMR2 &= ~(TIM_CCMR2_OC4M);
		timer->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
		timer->CCER |= TIM_CCER_CC4E;
	}
}

void timer_pwm_set_ccr(TIM_TypeDef * timer, char channel, float rapport) {
	if (channel == 1) {
		timer->CCR1 = (int) (timer->ARR*rapport);
	}
	else if (channel == 2) {
		timer->CCR2 = (int) (timer->ARR*rapport);
	}
	else if (channel == 3) {
		timer->CCR3 = (int) (timer->ARR*rapport);
	}
	else {
		timer->CCR4 = (int) (timer->ARR*rapport);
	}
}