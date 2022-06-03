#ifndef _GAME_H_
#define _GAME_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/* Global Types --------------------------------------------------------------*/
/**
  * @brief  Game state enumeration
*/
typedef enum
{
	GSTATE_WAITING_START,		/*!< Initial state */
	GSTATE_SELECT_DIRECTION,	/*!< Pick direction based on some algo */
	GSTATE_SETUP_CW,			/*!< Setup for clockwise */
	GSTATE_SETUP_ACW,			/*!< Setup for anti-clockwise */
	GSTATE_WAITING_CW,			/*!< Wait for clockwise command */
	GSTATE_WAITING_ACW,			/*!< Wait for anti-clockwise command */
	GSTATE_OVER,				/*!< Done state */

    GSTATE_NONE					/*!< Default state - no action */
} GSTATE;

/* Global Macros -------------------------------------------------------------*/

/* Global Functions ----------------------------------------------------------*/
/**
  * @brief  Initializes the game state machine and does any other required setups
  * @param  None
  * @retval None
*/
void GAMEinit(void);

/**
  * @brief  Moves the game forward - runs through our state machine to run next state
  * @param  None
  * @retval None
*/
void GAMErun(void);

/**
  * @brief  Sets the game to a specified state
  * @param  state what GSTATE to set the game to
  * @retval None
*/
void GAMEsetState(GSTATE state);

#endif
