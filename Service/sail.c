#include "sail.h"
#include "timer.h"

#define MIN_RATIO 0.05
#define MAX_RATIO 1.0

TIM_TypeDef * sail_timer;
char sail_channel;

void sail_init(TIM_TypeDef * timer, uint8_t channel) {
	timer_init(timer);
	timer_conf(timer, 320, 4500);
	timer_enable_pwm(timer, channel);
	
	sail_timer = timer;
	sail_channel = channel;
	
	timer_start(timer);
}

void sail_set_angle(uint16_t sail_angle) {
	float final_ratio = (float) sail_angle / 360;
	final_ratio = final_ratio *(MAX_RATIO - MIN_RATIO) + MIN_RATIO;
	timer_pwm_set_ccr(sail_timer, sail_channel, final_ratio);
}