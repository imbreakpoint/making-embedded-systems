/*

*/
#include "stm32f4xx_hal.h"

#include "blinkie.h"
#include "button.h"
#include "led.h"
#include "timer.h"
#include "uart.h"

#include "console.h"

#include <stdio.h>
#include <stdlib.h>

uint8_t initializedGlobal = 5;
uint8_t uninitializedGlobal;

int main(void)
{
	// configs
	HAL_Init();

	UARTinit();

	ConsoleInit();
	ConsoleProcess();

	static uint8_t staticInFunction = 2;

	uint8_t variableInFunction = 0;
	
	
	char buffer[80];
	uint8_t* pHeap = (uint8_t*)malloc(1);
	sprintf(buffer, "Heap Pointer:%p\r\n", pHeap);
	ConsoleSendString(buffer);

	volatile uint32_t reg;
    __asm volatile("mov %0, sp" : "=r"(reg));
    sprintf(buffer, "Stack Pointer:%08lX\r\n", (uint32_t)(reg));
	ConsoleSendString(buffer);


	sprintf(buffer, "&initialized global:%p\r\n", (void*)&initializedGlobal);
	ConsoleSendString(buffer);
	
	sprintf(buffer, "&uninitialized global:%p\r\n", (void*)&uninitializedGlobal);
	ConsoleSendString(buffer);

	sprintf(buffer, "&static in function:%p\r\n", (void*)&staticInFunction);
	ConsoleSendString(buffer);
	
	sprintf(buffer, "&variable in function:%p\r\n", (void*)&variableInFunction);
	ConsoleSendString(buffer);
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
