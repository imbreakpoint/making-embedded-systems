/*
	Week 5-CLI

*/
#include "stm32f4xx_hal.h"

#include "blinkie.h"
#include "button.h"
#include "led.h"
#include "timer.h"
#include "uart.h"

#include "console.h"

int main(void)
{
	// configs
	HAL_Init();

	// i/o port setup
    LEDinit(LED_RED);
    LEDinit(LED_GREEN);

	UARTinit();

  	UARTreceiveByte();

	ConsoleInit();

	while (1)
	{
		ConsoleProcess();
	}
}

void SysTick_Handler(void)
{
	HAL_IncTick();
  	HAL_SYSTICK_IRQHandler();
}
