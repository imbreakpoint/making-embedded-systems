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
	GAME_STATE_WAITING_START,		/*!< Initial state */
	GAME_STATE_SELECT_DIRECTION,	/*!< Pick direction based on some algo */
	GAME_STATE_SETUP_CW,			/*!< Setup for clockwise */
	GAME_STATE_SETUP_ACW,			/*!< Setup for anti-clockwise */
	GAME_STATE_WAITING_CW,			/*!< Wait for clockwise command */
	GAME_STATE_WAITING_ACW,			/*!< Wait for anti-clockwise command */
	GAME_STATE_OVER,				/*!< Done state */

	GAME_STATE_NONE					/*!< Default state - no action */
} GAME_STATE;

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
  * @param  state what GAME_STATE to set the game to
  * @retval None
*/
void GAMEsetState(GAME_STATE state);

#endif
