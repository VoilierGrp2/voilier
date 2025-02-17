#include "sail.h"
#include "timer.h"

#define SAIL_TIMER_ARR 320
#define SAIL_TIMER_PSC 4500

#define MIN_RATIO 0.05
#define MAX_RATIO 0.0995

#define MIN_ANGLE STRAIGHT_SAIL
#define MAX_ANGLE BLOCKING_SAIL

TIM_TypeDef * sail_timer;
uint8_t sail_channel;

void sail_init(TIM_TypeDef * timer, uint8_t channel) {
	timer_init(timer);
	timer_conf(timer, SAIL_TIMER_ARR, SAIL_TIMER_PSC);
	timer_enable_pwm(timer, channel);
	timer_pwm_set_ccr(timer, channel, MIN_RATIO);
	
	sail_timer = timer;
	sail_channel = channel;
	
	timer_start(timer);
}

float angle_to_pwm(int angle) {
    if (angle > MAX_ANGLE) {
        return MAX_RATIO;
    }

    if (angle < MIN_ANGLE) {
			return MIN_RATIO;
		}
		
    float pwm_percentage = MIN_RATIO + ((float)(angle - MIN_ANGLE) / (MAX_ANGLE - MIN_ANGLE)) * (MAX_RATIO - MIN_RATIO);

    return pwm_percentage;
}

void sail_set_angle(uint16_t sail_angle) {
	float pwm_ratio = angle_to_pwm(sail_angle);
	timer_pwm_set_ccr(sail_timer, sail_channel, pwm_ratio);
}