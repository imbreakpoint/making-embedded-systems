/* Includes ------------------------------------------------------------------*/
#include "button.h"
#include "led.h"

/* Global Definitions --------------------------------------------------------*/
/**
  * @brief  user button physical pins
*/
const BTN BTN_USER = {GPIOA, GPIO_PIN_0};

/* Local Definitions ---------------------------------------------------------*/
/**
  * @brief  flag to indicate if button press event registered
*/
static volatile bool btnPressedEvt = false;

/* Local Functions -----------------------------------------------------------*/

/* Interrupt Handles ---------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  IRQ Handler
*/
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Interrupt handler callback
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    // TODO disable interrupt?
    if (BTN_USER.pin == GPIO_Pin)
    {
        btnPressedEvt = true;
    }
}

/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes specified button on board
*/
void BTNinit(void)
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

/*----------------------------------------------------------------------------*/
/**
  * @brief  Returns if the button is pressed
*/
bool BTNisBtnPressed(void)
{
    return btnPressedEvt;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Processes the button event
*/
void BTNprocessBtnEvt(void)
{
    btnPressedEvt = false;
}
