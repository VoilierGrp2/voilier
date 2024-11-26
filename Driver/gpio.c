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

void gpio_conf(GPIO_TypeDef* gpio, uint8_t pin, uint8_t conf) {
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

uint16_t gpio_read(GPIO_TypeDef* gpio, uint8_t pin) {
	return gpio->IDR & (1<<pin);
}

void gpio_enable_interruptions() {
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
}

void (*exti0_callback)();
void (*exti1_callback)();
void (*exti2_callback)();
void (*exti3_callback)();
void (*exti4_callback)();
void (*exti9_5_callback)();
void (*exti15_10_callback)();

void gpio_register_interruption(GPIO_TypeDef* gpio, uint8_t pin, uint8_t prio, void (*callback)()) {
	uint8_t n;
	uint8_t offset;
	uint16_t exti_conf_value;
	
	n = pin/4; // 4 sections [0-3], [4-7], [8-11] et [12-15]
	offset = (pin%4) * 4; // valeurs possibles dans les sections ci-dessus: 0, 4, 8; 12
	if (gpio == GPIOA) {
		exti_conf_value = 0b0000;
	} else if (gpio == GPIOB) {
		exti_conf_value = 0b0001;
	} else if (gpio == GPIOC) {
		exti_conf_value = 0b0010;
	} else if (gpio == GPIOD) {
		exti_conf_value = 0b0011;
	} else if (gpio == GPIOE) {
		exti_conf_value = 0b0100;
	} else if (gpio == GPIOF) {
		exti_conf_value = 0b0101;
	} else {
		exti_conf_value = 0b0110;
	}
	AFIO->EXTICR[n] &= ~(AFIO_EXTICR1_EXTI0 << offset);
	AFIO->EXTICR[n] |= exti_conf_value << offset;
	
	// setup EXTI
	EXTI->IMR |= (0b1 << pin); // activation de l'imr (masque qui active, ou non, une ligne)
	EXTI->RTSR |= (0b1 << pin); // sélectionne la détection de front montant
	
	// setup NVIC
	int vector;
	if (pin > 0 && pin < 5) {
		vector = pin + 6;
		switch (pin) {
			case 0:
				exti0_callback = callback;
				break;
			case 1:
				exti1_callback = callback;
				break;
			case 2:
				exti2_callback = callback;
				break;
			case 3:
				exti3_callback = callback;
				break;
			default:
				exti4_callback = callback;
				break;
		}
	} else if (pin < 10) {
		vector = 23;
		exti9_5_callback = callback;
	} else { // EXTI15_10
		vector = 40;
		exti15_10_callback = callback;
	}
	NVIC_EnableIRQ(vector);
	NVIC_SetPriority(vector, prio);
}

void EXTI0_IRQHandler() {
	EXTI->PR |= 0b1; // baisse le flag de PR0
	exti0_callback();
}

void EXTI1_IRQHandler() {
	EXTI->PR |= (0b1 << 1); // baisse le flag de PR1
	exti1_callback();
}

void EXTI2_IRQHandler() {
	EXTI->PR |= (0b1 << 2); // baisse le flag de PR2
	exti2_callback();
}

void EXTI3_IRQHandler() {
	EXTI->PR |= (0b1 << 3); // baisse le flag de PR3
	exti3_callback();
}

void EXTI4_IRQHandler() {
	EXTI->PR |= (0b1 << 4); // baisse le flag de PR4
	exti4_callback();
}

void EXTI9_5_IRQHandler() {
	EXTI->PR |= (0b11111 << 5); // baisse les flags de PR5 à PR9 inclus
	exti9_5_callback();
}

void EXTI15_10_IRQHandler() {
	EXTI->PR |= (0b11111 << 10); // baisse les flags de PR10 à PR15 inclus
	exti15_10_callback();
}

void gpio_set(GPIO_TypeDef* gpio, uint8_t pin) {
	gpio->ODR |= (1<<pin);
}

void gpio_reset(GPIO_TypeDef* gpio, uint8_t pin) {
	gpio->ODR &= ~(1<<pin);
}

void gpio_toggle(GPIO_TypeDef* gpio, uint8_t pin) {
	if (gpio_read(gpio, pin)) {
		gpio_reset(gpio, pin);
	} else {
		gpio_set(gpio, pin);
	}
}
