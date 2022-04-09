#ifndef _TIMER_H_
#define _TIMER_H_

#include "stdbool.h"
#include "stm32f4xx_hal.h"

void TMRinit(void);
void TMRstartBlinkTimer(void);
void TMRstopBlinkTimer(void);
bool TMRisBlinkHandle(TIM_HandleTypeDef* htim);
#endif
