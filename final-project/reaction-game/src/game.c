#include "button.h"
#include "game.h"
#include "led.h"
#include "temperature.h"
#include "timer.h"

#define LED_CW     	LED_GREEN
#define LED_ACW     LED_RED

static GSTATE gameState = GSTATE_NONE;

static GSTATE gameChooseRotation();

static GSTATE gameChooseRotation()
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

void GAMEinit()
{
    TMRstop(&tmrRxnLEDHandle);
    LEDoff(LED_CW);
    LEDoff(LED_ACW);
    gameState = GSTATE_WAITING_START;
}

void GAMErun()
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

void GAMEsetState(GSTATE state)
{
    gameState = state;
}

