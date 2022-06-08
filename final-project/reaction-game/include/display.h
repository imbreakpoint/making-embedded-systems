#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/* Includes ------------------------------------------------------------------*/

#include "utils.h"

/* Global Types --------------------------------------------------------------*/

/* Global Defines ------------------------------------------------------------*/
/**
  * @brief  Message enumeration
*/
typedef enum
{
    DISP_MSG_PRESS_BTN,                 /*!< Message waiting for button press */
    DISP_MSG_RUNNING,                   /*!< Message runnig */
    DISP_MSG_GAME_OVER,                 /*!< Message game over */
    DISP_MSG_TIME_LEFT,                 /*!< Time remaining */
    DISP_MSG_ROT_CW,                    /*!< Rotate CW msg */
    DISP_MSG_ROT_ACW,                   /*!< Rotate ACW msg */

    DISP_MSG_NONE					    /*!< Default message - no action */
} DISP_MSG;

/* Global Macros -------------------------------------------------------------*/

/* Global Functions ----------------------------------------------------------*/
/**
  * @brief  Initializes the display on disco board
  * @param  None
  * @retval None
*/
void DISPinit(void);

/**
  * @brief  Displays a message on screen
  * @param  msg message string to show
  * @retval None
*/
void DISPshowMsg(DISP_MSG msgID);

#endif
