/*
	Week 3-Blinky

	Uses timer to control blinking of LED.
	On timer expiry interrupt, toggle LED.
*/
#include "stm32f4xx_hal.h"

#include "blinkie.h"
#include "button.h"
#include "led.h"
#include "timer.h"

static void GPIOinit(void);

int main(void)
{
	// configs
	HAL_Init();
  
  	GPIOinit();
	TMRinit();

	BLINKIEstart();

	// main application code
	while (1)
	{
		BLINKIEcontrol();
	}
}

static void GPIOinit(void)
{
	// i/o port setup
    LEDinit(LED_RED);
    LEDinit(LED_GREEN);

	BTNinit(BTN_USER);
}

void SysTick_Handler(void)
{
	HAL_IncTick();
  	HAL_SYSTICK_IRQHandler();
}
