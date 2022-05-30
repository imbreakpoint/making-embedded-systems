#include "uart.h"

//
static UART_HandleTypeDef sHandleUSART1;

//
#define BAUD_RATE (115200)

static volatile bool isReceived = false; 

static uint8_t byte;

void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&sHandleUSART1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        HAL_UART_Receive_IT(&sHandleUSART1, &byte, 1);

        isReceived = true;
    }
}

void UARTsendByte(uint8_t* byte)
{
    HAL_UART_Transmit(&sHandleUSART1, byte, 1, 10);    
}

bool UARTisReady()
{
    return isReceived;
}

uint8_t UARTgetByte()
{
    isReceived = false;
    return byte;
}

void UARTreceiveByte()
{
    HAL_UART_Receive_IT(&sHandleUSART1, &byte, 1);
}

void UARTinit()
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

    sHandleUSART1.Instance = USART1;
    sHandleUSART1.Init.BaudRate = BAUD_RATE;
    sHandleUSART1.Init.WordLength = UART_WORDLENGTH_8B;
    sHandleUSART1.Init.StopBits = UART_STOPBITS_1;
    sHandleUSART1.Init.Parity = UART_PARITY_NONE;
    sHandleUSART1.Init.Mode = UART_MODE_TX_RX;
    sHandleUSART1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    sHandleUSART1.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_UART_Init(&sHandleUSART1);
}
