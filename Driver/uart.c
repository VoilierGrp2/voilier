#include "stm32f10x.h"

void uart_init(USART_TypeDef * USART){
	switch ((int)USART) {
		case (int)USART1:
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			break;
		case (int)USART2:
			RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
			break;
		case (int)USART3:
			RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
			break;
	}
	USART->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void uart_config(USART_TypeDef * USART, int baud_rate){
	int clock_frequency;
	switch ((int)USART) {
		case (int)USART1:
			clock_frequency = 72000000;
			break;
		case (int)USART2:
		case (int)USART3:
			clock_frequency = 36000000;
			break;
	}
	unsigned short usart_div = clock_frequency / baud_rate;
	USART->BRR = usart_div;
}

void uart_send(USART_TypeDef * USART, char * data, int length){
	int i;
	for (i = 0; i < length; i++){
		while (!(USART->SR & USART_SR_TXE)) {
			// Wait for register to go to 1
		}
		USART->DR = data[i];
	}
}

void uart_enable_interrupt(USART_TypeDef * USART) {
	USART->CR1 |= USART_CR1_RXNEIE;
}

void (*USART1_it_function)(char);
void (*USART2_it_function)(char);
void (*USART3_it_function)(char);

void USART1_IRQHandler() {
	// Read to DR clears RXNE, no need to reset flag manually?
	char data = USART1->DR & 0xFF;
	USART1_it_function(data);
}

void USART2_IRQHandler() {
	char data = USART2->DR & 0xFF;
	USART2_it_function(data);
}

void USART3_IRQHandler() {
	char data = USART3->DR & 0xFF;
	USART3_it_function(data);
}

void uart_config_interrupt(USART_TypeDef * USART, void (*handler)(char), int priority) {
	int vector;
	switch ((int)USART) {
		case (int)USART1:
			USART1_it_function = handler;
			vector = 37;
			break;
		case (int)USART2:
			USART2_it_function = handler;
			vector = 38;
			break;
		case (int)USART3:
			USART3_it_function = handler;
			vector = 39;
			break;
	}
	NVIC_EnableIRQ(vector);
	NVIC_SetPriority(vector, priority);
}
