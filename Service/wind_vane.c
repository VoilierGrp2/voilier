#include "stm32f10x.h"
#include "wind_vane.h"
#include "timer.h"

TIM_TypeDef * selected_timer;

void wind_vane_init(TIM_TypeDef * timer) {
	selected_timer = timer;
	timer_enable(timer);
	timer_iencoder_enable(timer, encoder_mode_1, rising_polarity, 720);
}

float wind_vane_get_angle() {
	int angle_int = timer_iencoder_get(selected_timer);
	return (float) angle_int / 720 * 2 * PI;
}

void wind_vane_set_zero() {
	timer_iencoder_set_zero(selected_timer);
}
