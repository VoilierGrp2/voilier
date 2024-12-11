// = girouette en francais
#ifndef __WIND_VANE_H__
#define __WIND_VANE_H__
#include "stm32f10x.h"

/**
 * @brief 'constructor', initialise le service wind_vane
 * @param TIM_TypeDef * timer : timer allou� au service wind_vane
 * @param GPIO_TypeDef * gpio : gpio allou� au service wind_vane
 * @param uint8_t pin : pin du gpio a utiliser par le service
 */
void wind_vane_init(TIM_TypeDef * timer, GPIO_TypeDef * gpio, uint8_t pin);

// Returns an angle (in degrees) between 0 and 360
/**
 * @brief r�cup�re l'angle de la girouette
 * @pre le service wind_vane doit avoir �t� initialis� avec @ref wind_vane_init()
 * @return entier codant l'angle de la girouette en degr�s
 */
uint16_t wind_vane_get_angle();

#endif