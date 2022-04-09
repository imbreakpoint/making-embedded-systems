#include "timer.h"


// used to blink led
static TIM_HandleTypeDef blinkTimer; 

// timer 1
void TIM1_UP_TIM10_IRQHandler()
{
    HAL_TIM_IRQHandler(&blinkTimer);
}

void TMRinit(void)
{
	blinkTimer.Instance = TIM1;
	__TIM1_CLK_ENABLE();
	blinkTimer.Init.Prescaler = 8000;
	blinkTimer.Init.CounterMode = TIM_COUNTERMODE_UP;
	blinkTimer.Init.Period = 500;
	blinkTimer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	blinkTimer.Init.RepetitionCounter = 0;
	HAL_TIM_Base_Init(&blinkTimer);

  	HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);    
}

void TMRstartBlinkTimer(void)
{
    HAL_TIM_Base_Start_IT(&blinkTimer);
}

void TMRstopBlinkTimer(void)
{
    HAL_TIM_Base_Stop_IT(&blinkTimer);
}

bool TMRisBlinkHandle(TIM_HandleTypeDef* htim)
{
    return (&blinkTimer == htim);
}
