#include "timer.h"


static volatile bool tmrRxnLEDEvt = false;
static volatile bool tmrIsRxnTmrExpired = false;

TIM_HandleTypeDef tmrRxnLEDHandle;

// timer 1
void TIM1_UP_TIM10_IRQHandler()
{
    HAL_TIM_IRQHandler(&tmrRxnLEDHandle);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    //
    if (TMRisRxnLEDHandle(htim))
    {
        tmrIsRxnTmrExpired = true;
    }
}

void TMRinit(TIM_HandleTypeDef* htimer)
{
	// PS = 8000, Period = 500, gives about, 16e6 / ((8000-1) * (500-1)) = 1Hz
	htimer->Instance = TIM1;
	__TIM1_CLK_ENABLE();
	htimer->Init.Prescaler = 8000;
	htimer->Init.CounterMode = TIM_COUNTERMODE_UP;
	htimer->Init.Period = 2000;
	htimer->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htimer->Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(htimer);

  	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);    
}

void TMRstart(TIM_HandleTypeDef* htimer)
{
    HAL_TIM_Base_Start_IT(htimer);
}

void TMRstop(TIM_HandleTypeDef* htimer)
{
    HAL_TIM_Base_Stop_IT(htimer);
}

bool TMRisRxnLEDHandle(TIM_HandleTypeDef* htimer)
{
    return (&tmrRxnLEDHandle == htimer);
}

bool TMRisRxnLEDTimedOut()
{
	return tmrIsRxnTmrExpired;
}
