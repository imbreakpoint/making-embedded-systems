#ifndef _UART_H_
#define _UART_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/* Global Types --------------------------------------------------------------*/
/* Global Defines ------------------------------------------------------------*/
/* Global Macros -------------------------------------------------------------*/

/* Global Functions ----------------------------------------------------------*/

/**
  * @brief  Initializes USART
  * @param  None
  * @retval None
*/
void UARTinit(void);

/**
  * @brief  receives byte
  * @param  None
  * @retval None
*/
void UARTreceiveByte(void);

/**
  * @brief  Checks if new byte in buffer
  * @param  None
  * @retval true if usart is read to be read
*/
bool UARTisReady(void);

/**
  * @brief  Reads one byte of data
  * @param  None
  * @retval A byte of data that was read
*/
uint8_t UARTgetByte(void);

/**
  * @brief  Sends one byte of date
  * @param  byte - pointer to byte to send across
  * @retval None
*/
void UARTsendByte(uint8_t* byte);

#endif
