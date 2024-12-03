#ifndef __UART__
#define __UART__
#include "stm32f10x.h"

void uart_init(USART_TypeDef * USART);

void uart_config(USART_TypeDef * USART, int baud_rate);

void uart_send(USART_TypeDef * USART, char * data, int length);

void uart_enable_interrupt(USART_TypeDef * USART);

void uart_config_interrupt(USART_TypeDef * USART, void (*handler)(char), int priority);

#endif