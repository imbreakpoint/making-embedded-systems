#include "button.h"
#include "led.h"

const BTN BTN_USER = {GPIOA, GPIO_PIN_0};

void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void BTNinit(BTN btn)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}
