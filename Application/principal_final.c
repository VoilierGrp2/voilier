#include "stm32f10x.h"
#include "wind_vane.h"
#include "roll_measurer.h"
#include "sail.h"
#include "remote.h"
#include "wheel.h"

// sail control
#define WIND_VANE_TIMER TIM1
#define WIND_VANE_GPIO GPIOA
#define WIND_VANE_GPIO_PIN 4
#define ROLL_MEASURER_SPI SPI1
#define SAIL_TIMER TIM2
#define SAIL_TIMER_CHANNEL 1
// utilities
#define REMOTE_USART USART1
#define WHEEL_TIMER TIM3
#define WHEEL_TIMER_CHANNEL 1
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
	sail_init(SAIL_TIMER, SAIL_TIMER_CHANNEL);
	
	// init battery service
	// init real time clock service
	// init remote service
	remote_init(REMOTE_USART);
	// init wheel service
	wheel_init(WHEEL_TIMER, WHEEL_TIMER_CHANNEL, WHEEL_GPIO, WHEEL_GPIO_PIN);
	
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
		// wheel remote control
		remote_set_input_handler(handle_remote_input);
		// clock timestampt
		// battery notification
	}
}
