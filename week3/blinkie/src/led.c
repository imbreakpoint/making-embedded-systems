#include "led.h"

// physical pin maps
LED LED_RED   = {GPIOG, GPIO_PIN_14};
LED LED_GREEN = {GPIOG, GPIO_PIN_13};

void LEDinit(LED led)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.Pin = led.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(led.port, &GPIO_InitStruct);
}

void LEDtoggle(LED led)
{
	HAL_GPIO_TogglePin(led.port, led.pin);
}
