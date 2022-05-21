#ifndef _LED_H_
#define _LED_H_

#include "stm32f4xx_hal.h"

typedef struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
} LED;

const LED LED_RED;
const LED LED_GREEN;

#define LEDtoggle(led) (HAL_GPIO_TogglePin(led.port, led.pin))
#define LEDon(led) (HAL_GPIO_WritePin(led.port, led.pin, GPIO_PIN_SET))
#define LEDoff(led) (HAL_GPIO_WritePin(led.port, led.pin, GPIO_PIN_RESET))

void LEDinit(LED led);

#endif