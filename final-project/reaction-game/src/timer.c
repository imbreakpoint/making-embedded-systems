/* Includes ------------------------------------------------------------------*/
#include "timer.h"
#include "led.h"
/* Global Definitions --------------------------------------------------------*/
/**
  * @brief  timer handle for reaction game led
*/
static TIM_HandleTypeDef tmrRxnLEDHandle;

/* Local Definitions ---------------------------------------------------------*/

/**
  * @brief  gets set to 0 if reaction led timer is expired
*/
static uint32_t tmrTickOnIrq = 0;

/* Local Functions -----------------------------------------------------------*/
/* Interrupt Handles ---------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  IRQ handle
*/
void TIM3_IRQHandler(void)
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
	if ((&tmrRxnLEDHandle == htim) && tmrTickOnIrq)
	{
		tmrTickOnIrq--;
	}
}

/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes timer handle
*/
void TMRinit()
{
	__TIM3_CLK_ENABLE();
	HAL_NVIC_SetPriority(TIM3_IRQn, 0, 1);
  	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	tmrRxnLEDHandle.Instance = TIM3;
	tmrRxnLEDHandle.Init.Prescaler = (uint32_t) ((SystemCoreClock /2) / 10000) - 1;
	tmrRxnLEDHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	tmrRxnLEDHandle.Init.Period = 10000 - 1;
	tmrRxnLEDHandle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV2;
	tmrRxnLEDHandle.Init.RepetitionCounter = 0;

	if (HAL_OK != HAL_TIM_Base_Init(&tmrRxnLEDHandle))
	{
		// TODO
	}

	if (HAL_OK != HAL_TIM_Base_Start_IT(&tmrRxnLEDHandle))
	{
		// TODO
	}

	tmrTickOnIrq = 0;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Starts the timer
*/
void TMRstart(uint32_t timeout)
{
	tmrTickOnIrq = timeout;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Stops the timer
*/
void TMRstop(void)
{
	tmrTickOnIrq = 0;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Return true if timed out
*/
bool TMRisRxnLEDTimedOut(void)
{
	return (0 == tmrTickOnIrq);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Get seconds left until timer expires
*/
uint32_t TMRsecsUntilTimeout(void)
{
	return tmrTickOnIrq;
}
