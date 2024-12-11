#ifndef __SAIL_H__
#define __SAIL_H__
#include "stm32f10x.h"

#define STRAIGHT_SAIL (uint16_t) 0
#define BLOCKING_SAIL (uint16_t) 90

/**
 * @brief 'constructor', initialise le service sail
 * @param TIM_TypeDef * timer : timer utilis� par le service
 * @param utin8_t channel : channel du timer utilis� par le service
 */
void sail_init(TIM_TypeDef * timer, uint8_t channel);

// angle is between 0 and 1 where 0 is straight sail and 1 is blocking sail
/**
 * @brief d�finie l'angle du servo moteur
 * @param uint16_t sail_angle : nouvel angle du servo moteur
 * @pre le service sail doit avoir �t� initialis� avec @ref sail_init()
 */
void sail_set_angle(uint16_t sail_angle);

#endif