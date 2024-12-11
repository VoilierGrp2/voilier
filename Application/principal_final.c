#include "stm32f10x.h"
#include "gpio.h"
#include "wind_vane.h"
#include "roll_measurer.h"
#include "sail.h"
#include "remote.h"
#include "wheel.h"

// sail control
// PHA -> PA8 (TIM1_CH1), PHB -> PA9 (TIM1_CH2), (peut changer en fonction du sens)
#define WIND_VANE_TIMER TIM1
// IDX -> PC7 (peut changer en fonction du sens)
#define WIND_VANE_GPIO GPIOC
#define WIND_VANE_GPIO_PIN 7
// TODO
#define ROLL_MEASURER_SPI SPI1
// Servo PWM -> PB0 (TIM3_CH3)
#define SAIL_TIMER TIM3
#define SAIL_TIMER_CHANNEL 3
#define SAIL_PWM_OUTPUT_GPIO GPIOB
#define SAIL_PWM_OUTPUT_PIN 0
// utilities
#define REMOTE_USART USART1
// Plateau PWM -> PA1 (TIM2_CH2)
#define WHEEL_TIMER TIM2
#define WHEEL_TIMER_CHANNEL 2
#define WHEEL_PWM_OUTPUT_GPIO GPIOA
#define WHEEL_PWM_OUTPUT_PIN 1
// Plateau Dir. -> PB7
#define WHEEL_GPIO GPIOB
#define WHEEL_GPIO_PIN 7

#define MAX_ROLL 45

void handle_remote_input(signed char input) {
	wheel_control(input);
}

int main ( void )
{
	// init wind vane service
	wind_vane_init(WIND_VANE_TIMER, WIND_VANE_GPIO, WIND_VANE_GPIO_PIN);
	// init roll measurer service
	roll_measurer_init(ROLL_MEASURER_SPI);
	// init sail service
	gpio_init(SAIL_PWM_OUTPUT_GPIO);
	gpio_conf(SAIL_PWM_OUTPUT_GPIO, SAIL_PWM_OUTPUT_PIN, AltOut_Ppull);
	sail_init(SAIL_TIMER, SAIL_TIMER_CHANNEL);
	
	// init battery service
	// init real time clock service
	// init remote service
	remote_init(REMOTE_USART);
	// init wheel service
	gpio_init(WHEEL_PWM_OUTPUT_GPIO);
	gpio_conf(WHEEL_PWM_OUTPUT_GPIO, WHEEL_PWM_OUTPUT_PIN, AltOut_Ppull);
	wheel_init(WHEEL_TIMER, WHEEL_TIMER_CHANNEL, WHEEL_GPIO, WHEEL_GPIO_PIN);
	
	// wheel control
	remote_set_input_handler(handle_remote_input);
	
	while (1)
	{
		// auto sail
		uint16_t roll = roll_measurer_get_angle();
		if (roll > MAX_ROLL) {
			sail_set_angle(BLOCKING_SAIL);
		} else {
			uint16_t wind_vane_angle = wind_vane_get_angle();
			sail_set_angle(wind_vane_angle);
		}
		// clock timestampt
		// battery notification
	}
}
