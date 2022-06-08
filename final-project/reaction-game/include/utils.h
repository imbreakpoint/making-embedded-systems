#ifndef _UTILS_INCLUDES_H_
#define _UTILS_INCLUDES_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stdbool.h"

/* Global Types --------------------------------------------------------------*/
/**
  * @brief  physical pin map structure
*/
typedef struct
{
    GPIO_TypeDef* port;     /*!< GPIO port name */
    uint16_t pin;           /*!< GPIO port pin */
} UTILS_USER_IO;

#endif
