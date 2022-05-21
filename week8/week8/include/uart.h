#ifndef _UART_H_
#define _UART_H_

#include <stdbool.h>

#include "stm32f4xx_hal.h"

void UARTinit();
void UARTreceiveByte();

bool UARTisReady();
uint8_t UARTgetByte();
void UARTsendByte(uint8_t* byte);

#endif