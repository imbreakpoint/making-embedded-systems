/* Includes ------------------------------------------------------------------*/
#include "button.h"
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
static GSTATE gameState = GSTATE_NONE;

/**
  * @brief  Picks the roatation direction
  * @param  None
  * @retval GSTATE game state direction
*/
static GSTATE gameChooseRotation(void);

/* Local Functions -----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Picks the roatation direction
*/
static GSTATE gameChooseRotation(void)
{
	GSTATE directionState = GSTATE_SETUP_CW;
	// TODO enhance this direction select logic - do something w/ raw values?
	static float prevTemp = 0.0;
	float temp = 0.0;
	TEMPread(&temp);
	if (temp > prevTemp)
	{
		directionState = GSTATE_SETUP_ACW;
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
    gameState = GSTATE_WAITING_START;
	// Message - press button to start
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Moves the game forward - runs through our state machine to run next state
*/
void GAMErun(void)
{
	switch (gameState)
	{
	case GSTATE_WAITING_START:
		if (BTNisBtnPressed())
		{
			gameState = GSTATE_SELECT_DIRECTION;
			BTNprocessBtnEvt();
		}
		break;
	case GSTATE_SELECT_DIRECTION:
		// run algo
		gameState = gameChooseRotation();
		// Screnn erase message and show running?
		break;
	case GSTATE_SETUP_CW:
		TMRstart(&tmrRxnLEDHandle);
		LEDon(LED_CW);
		gameState = GSTATE_WAITING_CW;
		// keep track of gyro co-ordinates to compare later
		break;
	case GSTATE_SETUP_ACW:
		TMRstart(&tmrRxnLEDHandle);
		LEDon(LED_ACW);
		gameState = GSTATE_WAITING_ACW;
		break;
	case GSTATE_WAITING_CW:
	case GSTATE_WAITING_ACW:
		// TODO show seconds remaining
		if (TMRisRxnLEDTimedOut())
		{
			gameState = GSTATE_OVER; 
		}
		else
		{
			// check if gyro co-ordinates are correct before doing this
			gameState = GSTATE_SELECT_DIRECTION;
		}
		break;
	case GSTATE_OVER:
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
void GAMEsetState(GSTATE state)
{
    gameState = state;
}
