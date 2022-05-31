#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#include "stm32f4xx_hal.h"

void TEMPinit(void);
HAL_StatusTypeDef TEMPread(float* temperature);

#endif
