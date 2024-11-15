#ifndef __GPIO_H__
#define __GPIO_H__
#include "stm32f10x.h"

#define In_FLoating  0x4 //0100
#define In_PullDown  0x8 //1000
#define In_PullUp    0x9 //1000 (fake code)
#define In_Analog    0x0 //0000
#define Out_Ppull    0x2 //0010
#define Out_OD       0x6 //0110
#define AltOut_Ppull 0xa //1010
#define AltOut_OD    0xe //1110

void gpio_enable(GPIO_TypeDef* gpio);
void gpio_conf(GPIO_TypeDef* gpio, char pin, char conf);
int  gpio_read(GPIO_TypeDef* gpio, char pin);
void gpio_enable_interruptions();
void gpio_conf_interruption(GPIO_TypeDef* gpio, char pin, char prio, void (*callback)());
void gpio_set(GPIO_TypeDef* gpio, char pin);
void gpio_reset(GPIO_TypeDef* gpio, char pin);
void gpio_toggle(GPIO_TypeDef* gpio, char pin);

#endif