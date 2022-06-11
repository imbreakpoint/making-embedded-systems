/* Includes ------------------------------------------------------------------*/
#include <math.h>

#include "stm32f429i_discovery_lcd.h"

#include "button.h"
#include "display.h"
#include "game.h"
#include "gyroscope.h"
#include "led.h"
#include "moving_average_filter.h"
#include "temperature.h"
#include "timer.h"
// #define DBG_GAME
#ifdef DBG_GAME
#include <stdio.h>
#endif

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
  * @brief  Reaction timeout
*/
#define GAME_RXN_TIMEOUT_SECS (5)

/**
  * @brief  Reaction timeout
*/
#define GAME_IDLE_TIME_MSECS (1000)

/**
  * @brief  Gyro tolerance
*/
#define GAME_Y_TOL (2.0)

/**
  * @brief  Game direction
*/
typedef enum
{
    GAME_DIR_CW,	/*!< Direction CW */
    GAME_DIR_ACW,	/*!< Direction ACW */

    GAME_DIR_NONE	/*!< Default direction - no action */
} GAME_DIR;

/**
  * @brief  Game data
*/
typedef struct
{
    GAME_STATE state;		/*!< Game state */
    uint32_t score;			/*!< Score */
    uint32_t secsRemaining;	/*!< Time left to take action */
} GAME_INFO;

/**
  * @brief  Game Screens
*/
static DISP_SCREEN dispScrRunning =
{ 
    {DISP_MSG_RUNNING, DISP_MSG_NONE},
    LCD_COLOR_LIGHTGRAY
};

static DISP_SCREEN dispScrCW =
{
    {DISP_MSG_ROT_CW, DISP_MSG_CW_DIR, DISP_MSG_NONE},
    LCD_COLOR_GREEN
};

static DISP_SCREEN dispScrACW =
{ 
    {DISP_MSG_ROT_ACW, DISP_MSG_ACW_DIR, DISP_MSG_NONE},
    LCD_COLOR_RED
};

static DISP_SCREEN dispScrOver =
{ 
    {DISP_MSG_GAME_OVER, DISP_MSG_NONE},
    LCD_COLOR_WHITE
};

/**
  * @brief  Game state
*/
static GAME_INFO gameInfo = { GAME_STATE_NONE, 0, 0 };

/**
  * @brief  Picks the roatation direction
  * @param  None
  * @retval GAME_STATE game state direction
*/
static GAME_STATE gameChooseRotation(void);

/**
  * @brief  Runs the gyroscope loop to read the latest direction
  * @param  None
  * @retval GAME_DIR latest direction
*/
static GAME_DIR gameReadDirection(void);

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

#ifdef DBG_GAME
        char str[20];
        sprintf(str, "temperature =%.4f", temp);	
        BSP_LCD_DisplayStringAtLine(1, (uint8_t*)str);
#endif

    return directionState;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Runs the gyroscope loop to read the latest direction
*/
static GAME_DIR gameReadDirection(void)
{
    GAME_DIR direction = GAME_DIR_NONE;
    static GYRO_DATA previousResult = { 0 };

    // read new value
    GYRO_DATA newSample = {0};
    const bool status = GYROread(&newSample);
    // Run it through the filter
    if (status)
    {
        MAFsmooth(newSample);
    }

    // read the latest result
    const GYRO_DATA result = MAFgetResult();

#ifdef DBG_GAME
    if ((fabs(result.x - previousResult.x) > 0.3) || 
    (fabs(result.y - previousResult.y) > 0.3) || 
    (fabs(result.z - previousResult.z) > 0.3))
    {
        char str[20];
        sprintf(str, "x=%.4f   ", result.x);	
        BSP_LCD_DisplayStringAtLine(10, (uint8_t*)str);
        sprintf(str, "y=%.4f   ", result.y);
        BSP_LCD_DisplayStringAtLine(11, (uint8_t*)str);
        sprintf(str, "z=%.4f   ", result.z);
        BSP_LCD_DisplayStringAtLine(12, (uint8_t*)str);
    }
#endif

    if (fabs(result.y - previousResult.y) > GAME_Y_TOL)
    {
        if (result.y < 0.0)
        {
#ifdef DBG_GAME
            BSP_LCD_ClearStringLine(15);
            BSP_LCD_DisplayStringAtLine(15, (uint8_t*)"LEFT");
#endif
            direction = GAME_DIR_ACW;
        }
        else
        {
#ifdef DBG_GAME			
            BSP_LCD_ClearStringLine(15);
            BSP_LCD_DisplayStringAtLine(15, (uint8_t*)"RIGHT");
#endif			
            direction = GAME_DIR_CW;
        }
    
        MAFinit();
        previousResult.x = 0.0;
        previousResult.y = 0.0;
        previousResult.z = 0.0;
    }
    else
    {
        previousResult = result;   
    }

    return direction;
}

/* Interrupt Handles ---------------------------------------------------------*/
/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes the game state machine and does any other required setups
*/
void GAMEinit(void)
{
    BTNprocessBtnEvt();

    TMRstop();

    LEDoff(LED_CW);
    LEDoff(LED_ACW);

    gameInfo.score = 0;
    gameInfo.state = GAME_STATE_WAITING_START;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Moves the game forward - runs through our state machine to run next state
*/
void GAMErun(void)
{	
    switch (gameInfo.state)
    {
    case GAME_STATE_WAITING_START:
        DISPshowMsg(DISP_MSG_PRESS_BTN);
        if (BTNisBtnPressed())
        {
            gameInfo.state = GAME_STATE_SELECT_DIRECTION;
            BTNprocessBtnEvt();
        }
        break;
    case GAME_STATE_SELECT_DIRECTION:
        // run algo
        LEDoff(LED_CW);
        LEDoff(LED_ACW);
        gameInfo.state = gameChooseRotation();
        DISPupdateScreen(&dispScrRunning);
        HAL_Delay(GAME_IDLE_TIME_MSECS);
        break;
    case GAME_STATE_SETUP_CW:
        LEDon(LED_CW);
        DISPupdateScreen(&dispScrCW);
        gameInfo.state = GAME_STATE_WAITING_CW;
        // TODO Use some algo to make this time dynamic
        TMRstart(GAME_RXN_TIMEOUT_SECS);
        DISPupdate32(DISP_MSG_SCORE, gameInfo.score);
        break;
    case GAME_STATE_SETUP_ACW:
        LEDon(LED_ACW);
        DISPupdateScreen(&dispScrACW);
        gameInfo.state = GAME_STATE_WAITING_ACW;
        // TODO Use some algo to make this time dynamic
        TMRstart(GAME_RXN_TIMEOUT_SECS);
        DISPupdate32(DISP_MSG_SCORE, gameInfo.score);
        break;
    case GAME_STATE_WAITING_CW:
    {
#ifdef DBG_GAME
        char str[20];
        sprintf(str, "secs left=%ld", TMRsecsUntilTimeout());	
        BSP_LCD_DisplayStringAtLine(2, (uint8_t*)str);
#endif
        const GAME_DIR direction = gameReadDirection();
        const uint32_t secs = TMRsecsUntilTimeout();
        if (gameInfo.secsRemaining != secs)
        {
            DISPupdate32(DISP_MSG_TIME_LEFT, secs);
            gameInfo.secsRemaining = secs;
        }

        if (TMRisRxnLEDTimedOut() || (GAME_DIR_ACW == direction))
        {
            gameInfo.state = GAME_STATE_OVER; 
        }
        else if (GAME_DIR_CW == direction)
        {
            gameInfo.state = GAME_STATE_SELECT_DIRECTION;
            TMRstop();
            gameInfo.score++;
            DISPupdate32(DISP_MSG_SCORE, gameInfo.score);
        }
    }
        break;
    case GAME_STATE_WAITING_ACW:
    {
#ifdef DBG_GAME		
        char str[20];
        sprintf(str, "count=%ld   ", TMRsecsUntilTimeout());	
        BSP_LCD_DisplayStringAtLine(2, (uint8_t*)str);
#endif		
        const GAME_DIR direction = gameReadDirection();
        const uint32_t secs = TMRsecsUntilTimeout();
        if (gameInfo.secsRemaining != secs)
        {
            DISPupdate32(DISP_MSG_TIME_LEFT, secs);
            gameInfo.secsRemaining = secs;
        }

        if (TMRisRxnLEDTimedOut() || (GAME_DIR_CW == direction))
        {
            gameInfo.state = GAME_STATE_OVER; 
        }
        else if (GAME_DIR_ACW == direction)
        {
            gameInfo.state = GAME_STATE_SELECT_DIRECTION;
            TMRstop();
            gameInfo.score++;
            DISPupdate32(DISP_MSG_SCORE, gameInfo.score);
        }
    }
        break;
    case GAME_STATE_OVER:
        DISPupdateScreen(&dispScrOver);
        DISPupdate32(DISP_MSG_LAST_SCORE, gameInfo.score);
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
void GAMEsetState(const GAME_STATE state)
{
    gameInfo.state = state;
}
