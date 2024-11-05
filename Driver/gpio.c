#include "gpio.h"

void gpio_enable(GPIO_TypeDef* gpio) {
	int offset;
	if (gpio == GPIOA) offset = 2;
	else if (gpio == GPIOB) offset = 3;
	else if (gpio == GPIOC) offset = 4;
	else if (gpio == GPIOD) offset = 5;
	else if (gpio == GPIOE) offset = 6;
	else if (gpio == GPIOF) offset = 7;
	else offset = 8;
	RCC->APB2ENR |= (0x01 << offset);
}

void gpio_init(GPIO_TypeDef* gpio, char pin, char conf) {
	int offset;
	gpio_enable(gpio);
	if (conf == In_PullUp) {
		offset = pin;
		gpio->ODR |= (1 << offset);
		conf = In_PullDown;
	} else if (conf == In_PullDown) {
		offset = pin;
		gpio->ODR &= ~(1 << offset);
	}
	
	if (pin < 8) { //CRL
		offset = pin * 4;
		gpio->CRL &= ~(0xf<<offset);
		gpio->CRL |= (conf<<offset);
	} else { //CRH
		offset = (pin - 8) * 4;
		gpio->CRH &= ~(0xf<<offset);
		gpio->CRH |= (conf<<offset);
	}
}

int gpio_read(GPIO_TypeDef* gpio, char pin) {
	return gpio->IDR & (1<<pin);
}

void gpio_set(GPIO_TypeDef* gpio, char pin) {
	gpio->ODR |= (1<<pin);
}

void gpio_reset(GPIO_TypeDef* gpio, char pin) {
	gpio->ODR &= ~(1<<pin);
}

void gpio_toggle(GPIO_TypeDef* gpio, char pin) {
	if (gpio_read(gpio, pin)) {
		gpio_reset(gpio, pin);
	} else {
		gpio_set(gpio, pin);
	}
}
