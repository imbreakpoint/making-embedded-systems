/*
	Week 5-CLI

*/
#include "stm32f4xx_hal.h"

#include "button.h"
#include "game.h"
#include "led.h"
#include "temperature.h"
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

	BTNinit(BTN_USER);

	TMRinit(&tmrRxnLEDHandle);

	UARTinit();

  	UARTreceiveByte();

	TEMPinit();  

	ConsoleInit();
	GAMEinit();

	while (1)
	{
		ConsoleProcess();
		GAMErun();
	}
}

void SysTick_Handler(void)
{
	HAL_IncTick();
  	HAL_SYSTICK_IRQHandler();
}
