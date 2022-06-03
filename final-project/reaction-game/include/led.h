#ifndef _LED_H_
#define _LED_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/* Global Types --------------------------------------------------------------*/
/**
  * @brief  LED physical pin map structure
*/
typedef UTILS_USER_IO LED;

/* Global Defines ------------------------------------------------------------*/
/**
  * @brief  RED LED
*/
const LED LED_RED;

/**
  * @brief  GREEN LED
*/
const LED LED_GREEN;

/* Global Macros -------------------------------------------------------------*/

/**
  * @brief  Toggles led state
*/
#define LEDtoggle(led) (HAL_GPIO_TogglePin(led.port, led.pin))

/**
  * @brief  Switches ON led
*/
#define LEDon(led) (HAL_GPIO_WritePin(led.port, led.pin, GPIO_PIN_SET))

/**
  * @brief  Switches OFF led
*/
#define LEDoff(led) (HAL_GPIO_WritePin(led.port, led.pin, GPIO_PIN_RESET))

/* Global Functions ----------------------------------------------------------*/
/**
  * @brief  Initializes specified LED on board
  * @param  led which led to init
  * @retval None
*/
void LEDinit(LED led);

#endif
