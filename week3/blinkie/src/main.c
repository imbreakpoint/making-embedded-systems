/*
	Week 3-Blinky

	Uses timer to control blinking of LED.
	On timer expiry interrupt, toggle LED.
*/
#include "stm32f4xx_hal.h"

#include "timer.h"
#include "led.h"
#include "blinkie.h"

static void GPIOinit(void);

int main(void)
{
	// configs
	HAL_Init();
  
  	GPIOinit();
	TMRinit();

	// main application code
	BLINKIEcontrol();
	while (1)
	{
		// Nothing here right now
	}
}

static void GPIOinit(void)
{
	// i/o port setup
    __HAL_RCC_GPIOG_CLK_ENABLE();
    LEDinit(LED_RED);
    LEDinit(LED_GREEN);
}

void SysTick_Handler(void)
{
	HAL_IncTick();
  	HAL_SYSTICK_IRQHandler();
}
