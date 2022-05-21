// Console IO is a wrapper between the actual in and output and the console code
// In an embedded system, this might interface to a UART driver.

#include "consoleIo.h"
#include <stdio.h>

#include "uart.h"

eConsoleError ConsoleIoInit(void)
{
	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoReceive(uint8_t *buffer, const uint32_t bufferLength, uint32_t *readLength)
{
	uint32_t i = 0;
	uint8_t ch;

	while (UARTisReady())
	{
		ch = UARTgetByte();
		buffer[i] = (uint8_t) ch;
		i++;
		UARTsendByte(&ch);
	}
	*readLength = i;

	return CONSOLE_SUCCESS;
}

eConsoleError ConsoleIoSendString(const char *buffer)
{
	while ('\0' != *buffer)
	{
		UARTsendByte((uint8_t*)buffer);
		buffer++;
	}

	return CONSOLE_SUCCESS;
}

