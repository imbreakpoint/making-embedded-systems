/* Includes ------------------------------------------------------------------*/
#include "timer.h"
#include "led.h"
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
		if (HAL_TIM_CHANNEL_STATE_RESET != HAL_TIM_GetChannelState(htim, TIM_CHANNEL_ALL))
		{
			tmrIsRxnTmrExpired = true;
		}
    }
}

/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes timer handle
*/
void TMRinit(TIM_HandleTypeDef* hTimer)
{
	hTimer->Instance = TIM1;
	__TIM1_CLK_ENABLE();
	hTimer->Init.Prescaler = 32000;
	hTimer->Init.CounterMode = TIM_COUNTERMODE_UP;
	hTimer->Init.Period = 60000;
	hTimer->Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
	hTimer->Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(hTimer);

  	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);    

	tmrIsRxnTmrExpired = false;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Starts the timer
*/
void TMRstart(TIM_HandleTypeDef* hTimer)
{
    HAL_TIM_Base_Start_IT(hTimer);
	tmrIsRxnTmrExpired = false;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Stops the timer
*/
void TMRstop(TIM_HandleTypeDef* hTimer)
{
    HAL_TIM_Base_Stop_IT(hTimer);
	tmrIsRxnTmrExpired = false;
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
