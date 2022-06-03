/*
	Final Project

*/
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

#include "button.h"
#include "display.h"
#include "game.h"
#include "led.h"
#include "system.h"
#include "temperature.h"
#include "timer.h"
#include "uart.h"

#include "console.h"

int main(void)
{
	// configs
	HAL_Init();

	SYSTEMclkInit();

	// i/o port inits
    LEDinit(LED_RED);
    LEDinit(LED_GREEN);

	BTNinit(BTN_USER);

	// peripheral inits
	TMRinit(&tmrRxnLEDHandle);

	UARTinit();

	// TODO is this required?
  	UARTreceiveByte();

	TEMPinit();

	DISPinit();

	// Applications and library inits
	ConsoleInit();
	
	GAMEinit();

	while (1)
	{
		// run, run, run, forever..
		ConsoleProcess();
		GAMErun();
	}
}

void SysTick_Handler(void)
{
	HAL_IncTick();
  	HAL_SYSTICK_IRQHandler();
}

// TODO fault handler
