#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/* Includes ------------------------------------------------------------------*/

#include "fonts.h"
#include "stm32f429i_discovery_lcd.h"

#include "utils.h"

/* Global Types --------------------------------------------------------------*/

/* Global Defines ------------------------------------------------------------*/

/* Global Macros -------------------------------------------------------------*/

/* Global Functions ----------------------------------------------------------*/
/**
  * @brief  Initializes the display on disco board
  * @param  None
  * @retval None
*/
void DISPinit(void);

#endif
