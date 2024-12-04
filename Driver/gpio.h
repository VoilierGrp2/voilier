#ifndef __GPIO_H__
#define __GPIO_H__
#include "stm32f10x.h"

#define In_FLoating  ((uint8_t) 0x4) //0100
#define In_PullDown  ((uint8_t) 0x8) //1000
#define In_PullUp    ((uint8_t) 0x9) //1000 (fake code)
#define In_Analog    ((uint8_t) 0x0) //0000
#define Out_Ppull    ((uint8_t) 0x2) //0010
#define Out_OD       ((uint8_t) 0x6) //0110
#define AltOut_Ppull ((uint8_t) 0xa) //1010
#define AltOut_OD    ((uint8_t) 0xe) //1110

/**
 * @brief 'constructeur', initialise le gpio en lui donnant l'horloge
 * @param GPIO_TypeDef * gpio : gpio � initialiser
 */
void gpio_init(GPIO_TypeDef* gpio);

/**
 * @brief configure le pin d'un gpio avec un mode
 * @param GPIO_TypeDef * gpio : le gpio � configurer
 * @param uint8_t pin : le pin � configurer
 * @param uint8_t mode : le mode d'entr�e/sortie du pin
 * @pre gpio doit �tre initialis� avec la fonction @ref gpio_init()
 */
void gpio_conf(GPIO_TypeDef* gpio, uint8_t pin, uint8_t mode);

/**
 * @brief r�cup�re la valeur du gpio � un certain pin
 * @param GPIO_TypeDef * gpio : gpio � lire
 * @param uint8_t pin : pin sur laquelle on souhaite lire l'information
 * @return un entier avec le bit correspondant au pin d�finit � la valeur lu par la fonction
 */
uint16_t gpio_read(GPIO_TypeDef* gpio, uint8_t pin);

/**
 * @brief met � 1 la pin sur un gpio
 * @param GPIO_TypeDef * gpio : gpio � �crire
 * @param uint8_t pin : pin sur laquelle �crire
 */
void gpio_set(GPIO_TypeDef* gpio, uint8_t pin);

/**
 * @brief met � 0 la pin sur un gpio
 * @param GPIO_TypeDef * gpio : gpio � �crire
 * @param uint8_t pin : pin sur laquelle �crire
 */
void gpio_reset(GPIO_TypeDef* gpio, uint8_t pin);

/**
 * @brief change la valeur courante d'un pin d'un gpio � son inverse
 * @param GPIO_TypeDef * gpio : gpio � �crire
 * @param uint8_t pin : pin sur laquelle �crire
 */
void gpio_toggle(GPIO_TypeDef* gpio, uint8_t pin);

/********************
*   INTERRUPTIONS   *
********************/

/**
 * @brief active l'infrastructure d'interruption pour les gpio
 */
void gpio_enable_interruptions();

/**
 * @brief enregistre une interruption sur un pin
 * @param GPIO_TypeDef * gpio : gpio sur lequel enregistrer l'interruption
 * @param uint8_t pin : pin sur lequel enregistrer l'interruption
 * @param uint8_t priority : priorit� avec laquelle enregistrer l'interruption (cf NVIC priorities)
 * @param void (*handler)() : fonction � appeler lors d'une interruption
 * @pre activer le support des interruptions avec @ref gpio_enable_interruptions()
 * @pre activer le gpio en entr�e avec @ref gpio_conf()
 */
void gpio_register_interruption(GPIO_TypeDef* gpio, uint8_t pin, uint8_t priority, void (*handler)());

#endif