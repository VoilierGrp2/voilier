#ifndef __WHEEL_H__
#define __WHEEL_H__
#include "stm32f10x.h"

/**
 * @brief 'constructor', initialise le service wheel
 * @param TIM_TypeDef * timer : timer à utiliser comme pwm pour le controle de la roue
 * @param GPIO_TypeDef * gpio : gpio à utiliser comme sortie pour le bit de direction
 */
void wheel_init(TIM_TypeDef * timer, uint8_t channel, GPIO_TypeDef * gpio, uint8_t pin);

/**
 * @brief controle la roue pour aller dans un certaine direction à un certain endroit
 * @param int8_t control : entier de controle, le signe controle le sens
 *   et la valeur représente le pourcentage d'intensité (entre 0% et 100%)
 */
void wheel_control(int8_t control);

#endif