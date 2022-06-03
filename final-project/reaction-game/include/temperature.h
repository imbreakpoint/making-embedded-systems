#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/* Global Types --------------------------------------------------------------*/
/* Global Defines ------------------------------------------------------------*/
/* Global Macros -------------------------------------------------------------*/

/* Global Functions ----------------------------------------------------------*/
/**
  * @brief  Initializes temperature sensor / ADC
  * @param  None
  * @retval None
*/
void TEMPinit(void);

/**
  * @brief  Reads the value of temperature sensor
  * @param  temperature present temperature in 'C
  * @retval HAL error code
*/
HAL_StatusTypeDef TEMPread(float* temperature);

#endif
