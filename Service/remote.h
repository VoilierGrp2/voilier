#ifndef __REMOTE_H__
#define __REMOTE_H__
#include "stm32f10x.h"
#include "uart.h"

#define REMOTE_MAX_LEFT -100
#define REMOTE_MAX_RIGHT 100

/**
 * @brief Initializes the remote control module.
 * 
 * This function sets up the USART peripheral for communication with the remote control.
 * It configures the necessary settings for the USART to function correctly.
 * 
 * @param USART Pointer to the USART_TypeDef structure that contains
 *              the configuration information for the specified USART peripheral.
 */
void remote_init(USART_TypeDef * USART);

/**
 * @brief Sets the input handler function.
 * 
 * This function sets the function that will be called when a new input is received from the remote control.
 * 
 * @param handler Pointer to the function that will handle the input.
 */
void remote_set_input_handler(void (*handler)(signed char));

/**
 * @brief Sends data to the remote control.
 * 
 * This function sends data to the remote control using the USART peripheral.
 * 
 * @param data Pointer to the data to be sent.
 * @param size Size of the data to be sent.
 */
void remote_send_data(char * data, int size);

#endif