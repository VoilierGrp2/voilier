#include "battery.h"
#include "adc.h"
#include "gpio.h"
#include "stm32f10x.h"

ADC_TypeDef * selected_adc;

void battery_init(ADC_TypeDef * adc, int channel, GPIO_TypeDef * gpio, int pin) {
	  selected_adc = adc;
    adc_init(adc);
    adc_conf(adc, 6, channel, SAMPLE_TIME_1_5);
    gpio_enable(gpio);
    gpio_conf(gpio, pin, AltOut_Ppull);
}

int battery_get_percentage() {
    // Full battery: 13.7V
    // Dead battery: 11.5V
    // divider is 1/13
    // adc resolution is 12 bits (4095)
    // ADC min voltage is 0V
    // ADC max voltage is probably around 3.3V

    // Voltage when battery is full: 13.7/13 = 1.0538
    // Voltage when battery is dead is 11.5/13 = 0.8846
    // Max input from adc: 1.0538/3.3*4095 = 1308
    // Min input from adc: 0.8846/3.3*4095 = 1097
    int value = adc_get_value(selected_adc);
    int battery_percentage = (value - 1097) * 100 / (1308 - 1097);
    if (battery_percentage < 0) {
        return 0;
    } else if (battery_percentage > 100) {
        return 100;
    } else {
        return battery_percentage;
    }
}
