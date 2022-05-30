#ifndef _GAME_H_
#define _GAME_H_

#include "stm32f4xx_hal.h"

typedef enum
{
	GSTATE_WAITING_START,
	GSTATE_SELECT_DIRECTION,
	GSTATE_SETUP_CW,
	GSTATE_SETUP_ACW,
	GSTATE_WAITING_CW,
	GSTATE_WAITING_ACW,
	GSTATE_OVER,

    GSTATE_NONE
} GSTATE;

void GAMEinit();
void GAMErun();
void GAMEsetState(GSTATE state);

#endif