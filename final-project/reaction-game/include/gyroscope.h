#ifndef _GYROSCOPE_H_
#define _GYROSCOPE_H_

/* Includes ------------------------------------------------------------------*/

#include "utils.h"

/* Global Types --------------------------------------------------------------*/

/**
  * @brief  Gyroscope data store
*/
typedef struct
{
    float x;        /*!< X coordinate */
    float y;        /*!< Y coordinate */
    float z;        /*!< Z coordinate */
} GYRO_DATA;

/* Global Defines ------------------------------------------------------------*/
/* Global Macros -------------------------------------------------------------*/
/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes gyroscope
  * @param  None
  * @retval None
*/
void GYROinit(void);

/**
  * @brief  Calibrates the gyroscope
  * @param  None
  * @retval None
*/
void GYROcalibrate(void);

/**
  * @brief  Reads the current coordinates
  * @param  data pointer to store read data
  * @retval true if read is OK, false otherwise
*/
bool GYROread(GYRO_DATA *pData);

#endif
