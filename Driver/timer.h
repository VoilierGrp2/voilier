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

// Codeur incrémental
#define encoder_mode_1 TIM_SMCR_SMS_0
#define encoder_mode_2 TIM_SMCR_SMS_1
#define encoder_mode_3 TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0

#define rising_polarity 0
#define falling_polarity TIM_CCER_CC1P

// Polarity and encoder mode specified above
void timer_iencoder_enable(
	TIM_TypeDef * timer,
  int encoder_mode,
	int polarity,
	int n_incr
);
void timer_iencoder_set_zero(TIM_TypeDef * timer);
// Renvoie un nombre entre 0 et n_incr
int timer_iencoder_get(TIM_TypeDef * timer);

#endif