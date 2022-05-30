#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "stm32f4xx_hal.h"
#include "stdbool.h"

typedef struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
} BTN;

const BTN BTN_USER;

void BTNinit(BTN btn);
bool BTNisBtnPressed();
void BTNprocessBtnEvt();

#endif