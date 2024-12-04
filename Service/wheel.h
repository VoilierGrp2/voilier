#ifndef __WHEEL_H__
#define __WHEEL_H__
#include "stm32f10x.h"

/**
 * @brief 'constructor', initialise le service wheel
 * @param TIM_TypeDef * timer : timer to use as pwm for the wheel control
 * @param GPIO_TypeDef * gpio : gpio to use as output for the direction
 * @pre both timer and gpio are enable (clocked)
 * @post laisse à l'utilisateur le soin de lancer le timer
 */
void wheel_init(TIM_TypeDef * timer, uint8_t channel, GPIO_TypeDef * gpio, uint8_t pin);

/**
 * @brief control the wheel to go a certain way at a certain intensity
 * @param int8_t control : entier de controle, le signe controle le sens
 *   et la valeur représente le pourcentage d'intensité (entre 0% et 100%)
 */
void wheel_control(int8_t control);

#endif