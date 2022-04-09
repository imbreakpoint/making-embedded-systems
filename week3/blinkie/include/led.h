#ifndef _LED_H_
#define _LED_H_

#include "stm32f4xx_hal.h"

typedef struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
} LED;

LED LED_RED;
LED LED_GREEN;

void LEDinit(LED led);
void LEDtoggle(LED led);

#endif