#ifndef _TIMER_H_
#define _TIMER_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/* Global Types --------------------------------------------------------------*/
/**
  * @brief  Timer handle
*/
extern TIM_HandleTypeDef tmrRxnLEDHandle;

/* Global Defines ------------------------------------------------------------*/
/* Global Macros -------------------------------------------------------------*/

/* Global Functions ----------------------------------------------------------*/
/**
  * @brief  Initializes timer handle
  * @param  hTimer timer handle
  * @retval None
*/
void TMRinit(TIM_HandleTypeDef* hTimer);

/**
  * @brief  Starts the timer
  * @param  hTimer timer handle
  * @retval None
*/
void TMRstart(TIM_HandleTypeDef* hTimer);

/**
  * @brief  Stops the timer
  * @param  hTimer timer handle
  * @retval None
*/
void TMRstop(TIM_HandleTypeDef* hTimer);

/**
  * @brief  Check if this is reaction timer handle
  * @param  hTimer name of timer handle
  * @retval true if this matches the reaction led handle
*/
bool TMRisRxnLEDHandle(TIM_HandleTypeDef* hTimer);

/**
  * @brief  Initializes specified LED on board
  * @param  None
  * @retval true if the reaction led timer has expired
*/
bool TMRisRxnLEDTimedOut(void);

#endif
