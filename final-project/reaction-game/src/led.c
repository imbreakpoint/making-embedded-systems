/* Includes ------------------------------------------------------------------*/
#include "led.h"

/* Global Definitions --------------------------------------------------------*/
/**
  * @brief  red led physical pins
*/
const LED LED_RED   = {GPIOG, GPIO_PIN_14};

/**
  * @brief  green led physical pins
*/
const LED LED_GREEN = {GPIOG, GPIO_PIN_13};

/* Local Definitions ---------------------------------------------------------*/
/* Local Functions -----------------------------------------------------------*/
/* Interrupt Handles ---------------------------------------------------------*/
/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes specified LED on board
*/
void LEDinit(LED led)
{
    __HAL_RCC_GPIOG_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = led.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(led.port, &GPIO_InitStruct);
}
