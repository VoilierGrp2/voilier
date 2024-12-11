#include "wheel.h"
#include "timer.h"
#include "gpio.h"

// couple of arr and psc that allow a frequency of 40kHz using the smaller arr possible
//   (we need at least 101 level because we will get a value between 0 and 100 as input)
#define WHEEL_TIMER_ARR 101
#define WHEEL_TIMER_PSC 18

TIM_TypeDef * wheel_timer;
uint8_t wheel_pwm_channel;
GPIO_TypeDef * wheel_gpio;
uint8_t wheel_gpio_pin;

void wheel_init(TIM_TypeDef * timer, uint8_t channel, GPIO_TypeDef * gpio, uint8_t pin) {
	timer_init(timer);
	timer_conf(timer, WHEEL_TIMER_ARR, WHEEL_TIMER_PSC);
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

float current_ratio;

void wheel_control(int8_t control) {
	if (control < 0) {
		gpio_set(wheel_gpio, wheel_gpio_pin);
		control = -control;
	} else {
		gpio_reset(wheel_gpio, wheel_gpio_pin);
	}
	current_ratio = control / 100.0f;
	timer_pwm_set_ccr(wheel_timer, wheel_pwm_channel, control / 100.0f);
}
