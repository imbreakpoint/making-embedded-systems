/* Includes ------------------------------------------------------------------*/
#include "uart.h"

/* Global Definitions --------------------------------------------------------*/
/* Local Definitions ---------------------------------------------------------*/
/**
  * @brief  USART Handle
*/
static UART_HandleTypeDef uartHandleUSART1;

/**
  * @brief  Sets to true if new byte id
*/
static volatile bool uartIsReceived = false; 

/**
  * @brief  Store received byte
*/
static uint8_t uartRxByte;

/**
  * @brief  USART Baud rate
*/
#define BAUD_RATE (115200)

/* Local Functions -----------------------------------------------------------*/

/* Interrupt Handles ---------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  IRQ for USART
*/
void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&uartHandleUSART1);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Callback for receive USART interrupt
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        HAL_UART_Receive_IT(&uartHandleUSART1, &uartRxByte, 1);

        uartIsReceived = true;
    }
}

/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes USART
*/
void UARTinit(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    GPIO_InitTypeDef  GPIO_InitStruct;
 
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
  
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    uartHandleUSART1.Instance = USART1;
    uartHandleUSART1.Init.BaudRate = BAUD_RATE;
    uartHandleUSART1.Init.WordLength = UART_WORDLENGTH_8B;
    uartHandleUSART1.Init.StopBits = UART_STOPBITS_1;
    uartHandleUSART1.Init.Parity = UART_PARITY_NONE;
    uartHandleUSART1.Init.Mode = UART_MODE_TX_RX;
    uartHandleUSART1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    uartHandleUSART1.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_UART_Init(&uartHandleUSART1);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  receives byte
*/
void UARTreceiveByte(void)
{
    HAL_UART_Receive_IT(&uartHandleUSART1, &uartRxByte, 1);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Checks if new byte in buffer
*/
bool UARTisReady(void)
{
    return uartIsReceived;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Reads one byte of data
*/
uint8_t UARTgetByte(void)
{
    uartIsReceived = false;
    return uartRxByte;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Sends one byte of date
*/
void UARTsendByte(uint8_t* byte)
{
    HAL_UART_Transmit(&uartHandleUSART1, byte, 1, 10);    
}
