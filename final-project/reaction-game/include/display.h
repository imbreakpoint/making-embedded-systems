#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/* Includes ------------------------------------------------------------------*/

#include "utils.h"

/* Global Types --------------------------------------------------------------*/

/**
  * @brief  Maximum display messages
*/
#define MAX_DISP_MSGS (5)

/* Global Defines ------------------------------------------------------------*/
/**
  * @brief  Message enumeration
*/
typedef enum
{
    DISP_MSG_INIT,                      /*!< Message waiting for initializing */
    DISP_MSG_PRESS_BTN,                 /*!< Message waiting for button press */
    DISP_MSG_RUNNING,                   /*!< Message runnig */
    DISP_MSG_GAME_OVER,                 /*!< Message game over */
    DISP_MSG_TIME_LEFT,                 /*!< Time remaining */
    DISP_MSG_ROT_CW,                    /*!< Rotate CW msg */
    DISP_MSG_ROT_ACW,                   /*!< Rotate ACW msg */
    DISP_MSG_SCORE,                     /*!< Score string */
    DISP_MSG_LAST_SCORE,                /*!< Score string */
    DISP_MSG_CW_DIR,                	/*!< CW direction */
    DISP_MSG_ACW_DIR,                	/*!< ACW direction */

    DISP_MSG_NONE					    /*!< Default message - no action */
} DISP_MSG;

/**
  * @brief  Display screens
*/
typedef struct
{
    DISP_MSG msgIDs[MAX_DISP_MSGS]; /*!< Array of messages for this screen */
    uint32_t backColor;             /*!< Background color */
} DISP_SCREEN;

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
void DISPshowMsg(const DISP_MSG msgID);

/**
  * @brief  Displays a message on screen by clearing the pervious one
  * @param  screen screen to show
  * @retval None
*/
void DISPupdateScreen(DISP_SCREEN *pScreen);

/**
  * @brief  Displays a message on screen
  * @param  msgID msg to show
  * @param  num32 parameter for this msg string
  * @retval None
*/
void DISPupdate32(const DISP_MSG msgID, const uint32_t num32);

#endif
