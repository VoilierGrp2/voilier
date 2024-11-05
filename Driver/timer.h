#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f10x.h"

void timer_enable(TIM_TypeDef * timer);
void timer_init(TIM_TypeDef * timer, unsigned short arr, unsigned short psc);

#define timer_start(Timer) (Timer->CR1 |= TIM_CR1_CEN)
#define timer_stop (Timer) (Timer->CR1 &= ~(TIM_CR1_CEN))

// IT
void timer_active_it(TIM_TypeDef * timer, char prio, void (*it_function)());

// PWM
void timer_pwm_enable(TIM_TypeDef * timer, char channel);
void timer_pwm_set_ccr(TIM_TypeDef * timer, char channel, float rapport);

#endif