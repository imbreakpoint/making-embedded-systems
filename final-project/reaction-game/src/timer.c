/* Includes ------------------------------------------------------------------*/
#include "timer.h"

/* Global Definitions --------------------------------------------------------*/
/**
  * @brief  timer handle for reaction game led
*/
TIM_HandleTypeDef tmrRxnLEDHandle;

/* Local Definitions ---------------------------------------------------------*/

/**
  * @brief  gets set to true if reaction led timer is expired
*/
static volatile bool tmrIsRxnTmrExpired = false;

/* Local Functions -----------------------------------------------------------*/
/* Interrupt Handles ---------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  IRQ handle
*/
void TIM1_UP_TIM10_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&tmrRxnLEDHandle);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Timer handle callback
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    // TODO disable interrupt?
    if (TMRisRxnLEDHandle(htim))
    {
        tmrIsRxnTmrExpired = true;
    }
}

/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes timer handle
*/
void TMRinit(TIM_HandleTypeDef* hTimer)
{
	// PS = 8000, Period = 500, gives about, 16e6 / ((8000-1) * (500-1)) = 1Hz
	hTimer->Instance = TIM1;
	__TIM1_CLK_ENABLE();
	hTimer->Init.Prescaler = 8000;
	hTimer->Init.CounterMode = TIM_COUNTERMODE_UP;
	hTimer->Init.Period = 2000;
	hTimer->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	hTimer->Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(hTimer);

  	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);    
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Starts the timer
*/
void TMRstart(TIM_HandleTypeDef* hTimer)
{
    HAL_TIM_Base_Start_IT(hTimer);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Stops the timer
*/
void TMRstop(TIM_HandleTypeDef* hTimer)
{
    HAL_TIM_Base_Stop_IT(hTimer);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Check if this is reaction timer handle
*/
bool TMRisRxnLEDHandle(TIM_HandleTypeDef* hTimer)
{
    return (&tmrRxnLEDHandle == hTimer);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes specified LED on board
*/
bool TMRisRxnLEDTimedOut(void)
{
	return tmrIsRxnTmrExpired;
}
