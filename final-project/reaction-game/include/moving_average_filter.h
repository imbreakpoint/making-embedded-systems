#ifndef _MOVING_AVERAGE_FILTER_H_
#define _MOVING_AVERAGE_FILTER_H_

/* Includes ------------------------------------------------------------------*/
#include "gyroscope.h"
#include "moving_average_filter.h"
#include "utils.h"

/* Global Types --------------------------------------------------------------*/
/* Global Defines ------------------------------------------------------------*/
/* Global Macros -------------------------------------------------------------*/

/* Global Functions ----------------------------------------------------------*/
/**
    * @brief  Initializes moving average filter
    * @param  None
    * @retval None
*/
void MAFinit(void);

/**
    * @brief  Calculates the new average using the latest sample
    * @param  sample new reading
    * @retval None
*/
void MAFsmooth(const GYRO_DATA sample);

/**
    * @brief  Returns the current average value
    * @param  None
    * @retval GYRO_DATA resultant average
*/
GYRO_DATA MAFgetResult(void);

#endif
