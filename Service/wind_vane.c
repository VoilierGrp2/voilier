#include "stm32f10x.h"
#include "wind_vane.h"
#include "timer.h"
#include "gpio.h"

TIM_TypeDef * selected_timer;

void wind_vane_set_zero() {
	timer_iencoder_set_zero(selected_timer);
}

void wind_vane_init(TIM_TypeDef * timer, GPIO_TypeDef * gpio, char pin) {
	selected_timer = timer;
	timer_enable(timer);
	timer_iencoder_enable(timer, encoder_mode_1, rising_polarity, 720);
	
	// Add interrupt stuff to set zero
	gpio_enable(gpio);
	gpio_conf(gpio, pin, In_PullUp);
	gpio_enable_interruptions();
	gpio_conf_interruption(gpio, pin, 1, wind_vane_set_zero);
}

int wind_vane_get_angle() {
	return timer_iencoder_get(selected_timer) / 2;
}
