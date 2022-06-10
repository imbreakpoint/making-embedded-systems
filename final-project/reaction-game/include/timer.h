#ifndef _TIMER_H_
#define _TIMER_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/* Global Types --------------------------------------------------------------*/

/* Global Defines ------------------------------------------------------------*/
/* Global Macros -------------------------------------------------------------*/

/* Global Functions ----------------------------------------------------------*/
/**
  * @brief  Initializes timer handle
  * @param  None
  * @retval None
*/
void TMRinit(void);

/**
  * @brief  Starts the timer
  * @param  timeout in seconds
  * @retval None
*/
void TMRstart(uint32_t timeout);

/**
  * @brief  Stops the timer
  * @param  None
  * @retval None
*/
void TMRstop(void);

/**
  * @brief  Initializes specified LED on board
  * @param  None
  * @retval true if the reaction led timer has expired
*/
bool TMRisRxnLEDTimedOut(void);

/*----------------------------------------------------------------------------*/
/**
  * @brief  Get seconds left until timer expires
  * @param  None
  * @retval seconds remaining
*/
uint32_t TMRsecsUntilTimeout(void);

#endif
