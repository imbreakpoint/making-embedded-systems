/* Includes ------------------------------------------------------------------*/
#include "button.h"
#include "display.h"
#include "game.h"
#include "led.h"
#include "temperature.h"
#include "timer.h"

/* Global Definitions --------------------------------------------------------*/
/* Local Definitions ---------------------------------------------------------*/

/**
  * @brief  Clockwise Lled
*/
#define LED_CW (LED_GREEN)

/**
  * @brief  Anti-clockwise led
*/
#define LED_ACW (LED_RED)

/**
  * @brief  Game state
*/
static GAME_STATE gameState = GAME_STATE_NONE;

/**
  * @brief  Picks the roatation direction
  * @param  None
  * @retval GAME_STATE game state direction
*/
static GAME_STATE gameChooseRotation(void);

/* Local Functions -----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Picks the roatation direction
*/
static GAME_STATE gameChooseRotation(void)
{
	GAME_STATE directionState = GAME_STATE_SETUP_CW;
	// TODO enhance this direction select logic - do something w/ raw values?
	static float prevTemp = 0.0;
	float temp = 0.0;
	TEMPread(&temp);
	if (temp > prevTemp)
	{
		directionState = GAME_STATE_SETUP_ACW;
	}

	prevTemp = temp;

	return directionState;
}

/* Interrupt Handles ---------------------------------------------------------*/
/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes the game state machine and does any other required setups
*/
void GAMEinit(void)
{
    TMRstop(&tmrRxnLEDHandle);
    LEDoff(LED_CW);
    LEDoff(LED_ACW);
    gameState = GAME_STATE_WAITING_START;

	DISPshowMsg(DISP_MSG_PRESS_BTN);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Moves the game forward - runs through our state machine to run next state
*/
void GAMErun(void)
{
	switch (gameState)
	{
	case GAME_STATE_WAITING_START:
		if (BTNisBtnPressed())
		{
			gameState = GAME_STATE_SELECT_DIRECTION;
			BTNprocessBtnEvt();
		}
		break;
	case GAME_STATE_SELECT_DIRECTION:
		// run algo
		gameState = gameChooseRotation();
		DISPshowMsg(DISP_MSG_RUNNING);
		break;
	case GAME_STATE_SETUP_CW:
		TMRstart(&tmrRxnLEDHandle);
		LEDon(LED_CW);
		gameState = GAME_STATE_WAITING_CW;
		// keep track of gyro co-ordinates to compare later
		break;
	case GAME_STATE_SETUP_ACW:
		TMRstart(&tmrRxnLEDHandle);
		LEDon(LED_ACW);
		gameState = GAME_STATE_WAITING_ACW;
		break;
	case GAME_STATE_WAITING_CW:
	case GAME_STATE_WAITING_ACW:
		// TODO show seconds remaining
		if (TMRisRxnLEDTimedOut())
		{
			gameState = GAME_STATE_OVER; 
		}
		// else
		// {
		// 	// check if gyro co-ordinates are correct before doing this
		// 	gameState = GAME_STATE_SELECT_DIRECTION;
		// }
		break;
	case GAME_STATE_OVER:
		DISPshowMsg(DISP_MSG_GAME_OVER);
		GAMEinit();
		break;
	default:
		break;
	}
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Sets the game to a specified state
*/
void GAMEsetState(GAME_STATE state)
{
    gameState = state;
}
