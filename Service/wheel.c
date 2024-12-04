#include "wheel.h"
#include "timer.h"
#include "gpio.h"

#define TIM_ARR 200
#define TIM_PSC 10000

TIM_TypeDef * wheel_timer;
uint8_t wheel_pwm_channel;
GPIO_TypeDef * wheel_gpio;
uint8_t wheel_gpio_pin;

void wheel_init(TIM_TypeDef * timer, uint8_t channel, GPIO_TypeDef * gpio, uint8_t pin) {
	timer_init(timer);
	timer_conf(timer, TIM_ARR, TIM_PSC);
	timer_enable_pwm(timer, channel);
	timer_pwm_set_ccr(timer, channel, 0.0f);
	
	gpio_init(gpio);
	gpio_conf(gpio, pin, Out_Ppull);
	
	wheel_timer = timer;
	wheel_pwm_channel = channel;
	wheel_gpio = gpio;
	wheel_gpio_pin = pin;
	
	timer_start(timer);
}

void wheel_control(int8_t control) {
	if (control < 0) {
		gpio_set(wheel_gpio, wheel_gpio_pin);
	} else {
		gpio_reset(wheel_gpio, wheel_gpio_pin);
	}
	timer_pwm_set_ccr(wheel_timer, wheel_pwm_channel, control / 100.0f);
}
