#include "remote.h"
#include "uart.h"
#include "gpio.h"
#include "stm32f10x.h"

USART_TypeDef * selected_usart;
void (*input_handler)(signed char);

void handler_function(char data) {
  input_handler((signed char) data);
}

void remote_init(USART_TypeDef * USART) {
  selected_usart = USART;
	uart_init(USART);
	uart_config(USART, 9600);
  uart_enable_interrupt(USART);
  uart_config_interrupt(USART, handler_function, 0);
}

void remote_set_input_handler(void (*handler)(signed char)) {
  input_handler = handler;
}

void remote_send_data(char * data, int size) {
  uart_send(selected_usart, data, size);
}