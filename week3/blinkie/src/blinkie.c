#include "blinkie.h"
#include "led.h"
#include "timer.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    // toggle on every interrupt
    if (TMRisBlinkHandle(htim))
    {
        LEDtoggle(LED_GREEN);
    }
}

void BLINKIEcontrol(void)
{
	TMRstartBlinkTimer();
}
