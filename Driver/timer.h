#ifndef __TIMER_H__
#define __TIMER_H__

#include "stm32f10x.h"

/**
 * @brief 'constructeur', initialise le timer donné en paramètre en lui donnant l'horloge
 * @param TIM_TypeDef * timer : timer à initialiser
 */
void timer_init(TIM_TypeDef * timer);

/**
 * @brief configure le timer en définissant les champs arr et psc
 * @param TIM_TypeDef * timer : timer à configurer
 * @param uint16_t arr : auto-reload register value
 * @param uint16_t psc : pre scaler value
 * @pre initialiser timer avec @ref timer_init()
 */
void timer_conf(TIM_TypeDef * timer, uint16_t arr, uint16_t psc);

/**
 * @brief lance le timer (commence à compter uniquement après l'appel à cette macro)
 * @param TIM_TypeDef * timer : timer à lancer
 * @pre initialiser timer avec @ref timer_init()
 */
#define timer_start(Timer) (Timer->CR1 |= TIM_CR1_CEN)

/**
 * @brief arrête le timer (inverse de start), arrêté le timer conserve son compteur courant
 * @brief TIM_TypeDef * timer : timer à arrêter
 * @pre initialiser timer avec @ref timer_init()
 */
#define timer_stop (Timer) (Timer->CR1 &= ~(TIM_CR1_CEN))

/********************
*   INTERRUPTIONS   *
********************/

/**
 * @brief enregistre une interruption qui sera appelée au moment d'un reload de l'arr
 * @param TIM_TypeDef * timer : timer sur lequel enregistrer l'interruption
 * @param uint8_t prio : priorité de l'interruption (cf NVIC priorities)
 * @param void (*handler)() : procédure à appeler
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
 * @brief modifie le capture compare register, cela change à partir de quel moment marquer un front descendant pour la pwm
 * @param TIM_TypeDef * timer : timer sur lequel opérer
 * @param uint8_t channel : canal où est configuré la pwm
 * @param float ratio : rapport définissant le pourcentage de temps où le signal est en état max
 * @pre le canal doit avoir été configuré en pwm par la fonction @ref timer_enable_pwm()
 */
void timer_pwm_set_ccr(TIM_TypeDef * timer, uint8_t channel, float ratio);

/************************
*   INCREMENTAL CODER   *
************************/

/** @brief mode pour le codeur incrémental qui compte sur le signal A et traite la direction avec le signal B */
#define COUNT_A TIM_SMCR_SMS_0
/** @brief mode pour le codeur incrémental qui compte sur le signal B et traite la direction avec le signal A */
#define COUNT_B TIM_SMCR_SMS_1
/** @brief mode pour le codeur incrémental qui compte et traite la dircection sur les deux broches (A et B) en utilisant une logique */
#define COUNT_BOTH TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0

/** @brief polarité pour le codeur incrémental qui traite les front montants */
#define RISING_POLARITY 0
/** @brief polarité pour le codeur incrémental qui traite les front descendants */
#define FALLING_POLARITY TIM_CCER_CC1P

/**
 * @brief active et configure le support d'un codeur incrémental
 * @param TIM_TypeDef * timer : timer sur lequel le support se fera
 * @param uint16_t encoder_mode : mode de configuration du codeur incrémental (cf define)
 * @param uint16_t polarity : polarité du codeur incrémental (cf define)
 */
void timer_enable_iencoder(TIM_TypeDef * timer, uint16_t encoder_mode, uint16_t polarity);

/**
 * @brief réinitialise à zéro le codeur incrémental
 * @param TIM_TypeDef * timer : timer à réinitialiser
 * @pre activer et configurer le timer avant avec la fonction @ref timer_enable_iencoder()
 */
void timer_iencoder_set_zero(TIM_TypeDef * timer);

/**
 * @brief récupère la valeur courante du codeur incrémental
 * @param TIM_TypeDef * timer : timer supportant un codeur incrémental
 * @pre activer et configurer le timer avant avec la fonction @ref timer_enable_iencoder()
 * @return la valeur courante du codeur incrémental
 */
uint16_t timer_iencoder_get(TIM_TypeDef * timer);

#endif