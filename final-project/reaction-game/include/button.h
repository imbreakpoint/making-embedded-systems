#ifndef _BUTTON_H_
#define _BUTTON_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/* Global Types --------------------------------------------------------------*/
/**
  * @brief  Button physical pin map structure
*/
typedef UTILS_USER_IO BTN;

/* Global Defines ------------------------------------------------------------*/
/**
  * @brief  User botton
*/
const BTN BTN_USER;

/* Global Macros -------------------------------------------------------------*/

/* Global Functions ----------------------------------------------------------*/
/**
  * @brief  Initializes specified button on board
  * @param  btn which button to init
  * @retval None
*/
void BTNinit(BTN btn);

/**
  * @brief  Returns if the button is pressed
  * @param  None
  * @retval true if button was pressed
*/
bool BTNisBtnPressed(void);

/**
  * @brief  Processes the button event
  * @param  none
  * @retval None
*/
void BTNprocessBtnEvt(void);

#endif
