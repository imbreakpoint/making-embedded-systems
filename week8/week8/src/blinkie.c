#include "blinkie.h"
#include "button.h"
#include "led.h"
#include "timer.h"

#define BLINKIE_LED     LED_GREEN

static volatile bool blinkieBtnEvt = false;
static volatile bool blinkieTmrEvt = false;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    // toggle on every interrupt
    if (TMRisBlinkHandle(htim))
    {
        blinkieTmrEvt = true;
    }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (BTN_USER.pin == GPIO_Pin)
    {
        blinkieBtnEvt = true;
    }
}

void BLINKIEstart(void)
{
    LEDon(BLINKIE_LED);
    TMRstartBlinkTimer();
}

void BLINKIEstop(void)
{
    LEDoff(BLINKIE_LED);
    TMRstopBlinkTimer();
}

void BLINKIEcontrol(void)
{
    static bool isBlinkieOn = true;
    if (blinkieBtnEvt)
    {
	isBlinkieOn ? BLINKIEstop() : BLINKIEstart();
        isBlinkieOn = !isBlinkieOn;
        blinkieBtnEvt = false;
    }

    if (blinkieTmrEvt)
    {
        LEDtoggle(BLINKIE_LED);
        blinkieTmrEvt = false;
    }
}
