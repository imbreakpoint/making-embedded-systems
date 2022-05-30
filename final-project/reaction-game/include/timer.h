#ifndef _TIMER_H_
#define _TIMER_H_

#include "stdbool.h"
#include "stm32f4xx_hal.h"

extern TIM_HandleTypeDef tmrRxnLEDHandle;

void TMRinit(TIM_HandleTypeDef* htimer);
void TMRstart(TIM_HandleTypeDef* htimer);
void TMRstop(TIM_HandleTypeDef* htimer);
bool TMRisRxnLEDHandle(TIM_HandleTypeDef* htimer);
bool TMRisRxnLEDTimedOut();

#endif
