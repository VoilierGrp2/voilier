#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f10x.h"

/**
 * @brief 'constructeur', initialise le timer donn� en param�tre en lui donnant l'horloge
 * @param TIM_TypeDef * timer : timer � initialiser
 */
void timer_init(TIM_TypeDef * timer);

/**
 * @brief configure le timer en d�finissant les champs arr et psc
 * @param TIM_TypeDef * timer : timer � configurer
 * @param uint16_t arr : auto-reload register value
 * @param uint16_t psc : pre scaler value
 * @pre initialiser timer avec @ref timer_init()
 */
void timer_conf(TIM_TypeDef * timer, uint16_t arr, uint16_t psc);

/**
 * @brief lance le timer (commence � compter uniquement apr�s l'appel � cette macro)
 * @param TIM_TypeDef * timer : timer � lancer
 * @pre initialiser timer avec @ref timer_init()
 */
#define timer_start(Timer) (Timer->CR1 |= TIM_CR1_CEN)

/**
 * @brief arr�te le timer (inverse de start), arr�t� le timer conserve son compteur courant
 * @brief TIM_TypeDef * timer : timer � arr�ter
 * @pre initialiser timer avec @ref timer_init()
 */
#define timer_stop (Timer) (Timer->CR1 &= ~(TIM_CR1_CEN))

/********************
*   INTERRUPTIONS   *
********************/

/**
 * @brief enregistre une interruption qui sera appel�e au moment d'un reload de l'arr
 * @param TIM_TypeDef * timer : timer sur lequel enregistrer l'interruption
 * @param uint8_t prio : priorit� de l'interruption (cf NVIC priorities)
 * @param void (*handler)() : proc�dure � appeler
 * @pre initialiser timer avec @ref timer_init()
 */
void timer_register_interruption(TIM_TypeDef * timer, uint8_t prio, void (*handler)());

/**********
*   PWM   *
**********/

/**
 * @brief active la pwm sur un certain canal
 * @param TIM_TypeDef * timer : timer qui sera configurer pour une pwm
 * @param uint8_t channel : canal sur lequel la pwm sortira
 * @pre initialiser timer avec @ref timer_init()
 * @note voir la datasheet pour savoir quel canal de quel timer correspond quel pin sur la carte
 */
void timer_enable_pwm(TIM_TypeDef * timer, uint8_t channel);

/**
 * @brief modifie le capture compare register, cela change � partir de quel moment marquer un front descendant pour la pwm
 * @param TIM_TypeDef * timer : timer sur lequel op�rer
 * @param uint8_t channel : canal o� est configur� la pwm
 * @param float ratio : rapport d�finissant le pourcentage de temps o� le signal est en �tat max
 * @pre le canal doit avoir �t� configur� en pwm par la fonction @ref timer_enable_pwm()
 */
void timer_pwm_set_ccr(TIM_TypeDef * timer, uint8_t channel, float ratio);

/************************
*   INCREMENTAL CODER   *
************************/

/** @brief mode pour le codeur incr�mental qui compte sur le signal A et traite la direction avec le signal B */
#define COUNT_A TIM_SMCR_SMS_0
/** @brief mode pour le codeur incr�mental qui compte sur le signal B et traite la direction avec le signal A */
#define COUNT_B TIM_SMCR_SMS_1
/** @brief mode pour le codeur incr�mental qui compte et traite la dircection sur les deux broches (A et B) en utilisant une logique */
#define COUNT_BOTH TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0

/** @brief polarit� pour le codeur incr�mental qui traite les front montants */
#define RISING_POLARITY 0
/** @brief polarit� pour le codeur incr�mental qui traite les front descendants */
#define FALLING_POLARITY TIM_CCER_CC1P

/**
 * @brief active et configure le support d'un codeur incr�mental
 * @param TIM_TypeDef * timer : timer sur lequel le support se fera
 * @param uint16_t encoder_mode : mode de configuration du codeur incr�mental (cf define)
 * @param uint16_t polarity : polarit� du codeur incr�mental (cf define)
 */
void timer_enable_iencoder(TIM_TypeDef * timer, uint16_t encoder_mode, uint16_t polarity);

/**
 * @brief r�initialise � z�ro le codeur incr�mental
 * @param TIM_TypeDef * timer : timer � r�initialiser
 * @pre activer et configurer le timer avant avec la fonction @ref timer_enable_iencoder()
 */
void timer_iencoder_set_zero(TIM_TypeDef * timer);

/**
 * @brief r�cup�re la valeur courante du codeur incr�mental
 * @param TIM_TypeDef * timer : timer supportant un codeur incr�mental
 * @pre activer et configurer le timer avant avec la fonction @ref timer_enable_iencoder()
 * @return la valeur courante du codeur incr�mental
 */
uint16_t timer_iencoder_get(TIM_TypeDef * timer);

#endif