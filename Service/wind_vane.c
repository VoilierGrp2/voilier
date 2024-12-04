#include "stm32f10x.h"
#include "wind_vane.h"
#include "timer.h"
#include "gpio.h"

TIM_TypeDef * selected_timer;

void wind_vane_set_zero();

void wind_vane_init(TIM_TypeDef * timer, GPIO_TypeDef * gpio, uint8_t pin) {
	selected_timer = timer;
	timer_init(timer);
	timer_conf(timer, 720, 1);
	timer_enable_iencoder(timer, COUNT_A, RISING_POLARITY);
	
	// Add interrupt stuff to set zero
	gpio_init(gpio);
	gpio_conf(gpio, pin, In_PullUp);
	gpio_enable_interruptions();
	gpio_register_interruption(gpio, pin, 1, wind_vane_set_zero);
	
	timer_start(timer);
}

void wind_vane_set_zero() {
	timer_iencoder_set_zero(selected_timer);
}

uint16_t wind_vane_get_angle() {
	return timer_iencoder_get(selected_timer) / 2;
}
