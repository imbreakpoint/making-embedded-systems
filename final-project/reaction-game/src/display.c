/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

#include "fonts.h"
#include "stm32f429i_discovery_lcd.h"

#include "display.h"

/* Global Definitions --------------------------------------------------------*/
/* Local Definitions ---------------------------------------------------------*/

/**
    * @brief  Maximum message length in bytes
*/
#define MAX_MSG_BYTES (20)

/**
    * @brief  Display score
*/
#define DISP_GAME_SCORE (10)

/**
    * @brief  Display time left
*/
#define DISP_GAME_TIME_LEFT (250)

/**
    * @brief  Game instructions line 1
*/
#define DISP_GAME_INSTRUCT_LN1 (80)

/**
    * @brief  Game insteructions line 2
*/
#define DISP_GAME_INSTRUCT_LN2 (140)

/**
    * @brief  Message information
*/
typedef struct
{
    uint16_t x;                		/*!< x to display message on */
    uint16_t y;                		/*!< y to display message on */
    Text_AlignModeTypdef align;		/*!< alignment */
    uint32_t txtColor;				/*!< Text color */
    sFONT* pFont;					/*!< font */
    char msg[MAX_MSG_BYTES];    	/*!< Message string to show */

} DISP_MSG_INFO;

/**
    * @brief  Message table
*/
static const DISP_MSG_INFO dispMsgTable[] =
{
    {0, DISP_GAME_INSTRUCT_LN2, CENTER_MODE, LCD_COLOR_BLACK, 	&Font16, "Starting.."			},
    {0, DISP_GAME_INSTRUCT_LN2, CENTER_MODE, LCD_COLOR_BLACK, 	&Font16, "Push to Start Game"	},
    {0, DISP_GAME_INSTRUCT_LN2, CENTER_MODE, LCD_COLOR_BLACK, 	&Font20, "Running..."			},
    {0, DISP_GAME_INSTRUCT_LN1, CENTER_MODE, LCD_COLOR_DARKRED,	&Font20, "Game Over!"			},
    {0, DISP_GAME_TIME_LEFT, 	LEFT_MODE,   LCD_COLOR_BLACK, 	&Font16, "Seconds left:%ld"		},
    {0, DISP_GAME_INSTRUCT_LN2, CENTER_MODE, LCD_COLOR_BLACK, 	&Font20, "CLOCKWISE"			},
    {0, DISP_GAME_INSTRUCT_LN2, CENTER_MODE, LCD_COLOR_BLACK, 	&Font20, "ANTI-CLOCKWISE"		},
    {0, DISP_GAME_SCORE, 		RIGHT_MODE,  LCD_COLOR_BLACK, 	&Font20, "SCORE:%ld"		    },
    {0, DISP_GAME_SCORE, 		CENTER_MODE, LCD_COLOR_BLACK, 	&Font20, "FINAL SCORE:%ld"		},
    {0, DISP_GAME_INSTRUCT_LN1, CENTER_MODE, LCD_COLOR_BLACK, 	&Font20, "-->-->-->"			},
    {0, DISP_GAME_INSTRUCT_LN1, CENTER_MODE, LCD_COLOR_BLACK, 	&Font20, "<--<--<--"			},

    {0, 0,						CENTER_MODE, LCD_COLOR_BLACK,    &Font16, ""					}
};

/* Interrupt Handles ---------------------------------------------------------*/
/* Global Functions ----------------------------------------------------------*/

/* Global Functions ----------------------------------------------------------*/
/*----------------------------------------------------------------------------*/
/**
    * @brief  Initializes the display on disco board
*/
void DISPinit(void)
{
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER, LCD_FRAME_BUFFER);
    BSP_LCD_SelectLayer(LCD_BACKGROUND_LAYER);
    BSP_LCD_DisplayOn();
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    BSP_LCD_SetFont(&Font16);

    // TOOD remove this debug stuff
    BSP_LCD_DisplayStringAtLine(5, (uint8_t*)"Time is an illusion!");
}

/*----------------------------------------------------------------------------*/
/**
   * @brief  Displays a message on screen
*/
void DISPshowMsg(const DISP_MSG msgID)
{
    BSP_LCD_SetFont(dispMsgTable[msgID].pFont);
    BSP_LCD_SetTextColor(dispMsgTable[msgID].txtColor);
    BSP_LCD_DisplayStringAt(dispMsgTable[msgID].x, dispMsgTable[msgID].y, (uint8_t*)dispMsgTable[msgID].msg, dispMsgTable[msgID].align);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Displays a message on screen
*/
void DISPupdateScreen(DISP_SCREEN *pScreen)
{
    BSP_LCD_Clear(pScreen->backColor);
    BSP_LCD_SetBackColor(pScreen->backColor);
    DISP_MSG *listMsgId = pScreen->msgIDs;
    while (DISP_MSG_NONE != *listMsgId)
    {
        BSP_LCD_SetFont(dispMsgTable[*listMsgId].pFont);
        BSP_LCD_SetTextColor(dispMsgTable[*listMsgId].txtColor);
        BSP_LCD_DisplayStringAt(dispMsgTable[*listMsgId].x, dispMsgTable[*listMsgId].y, (uint8_t*)dispMsgTable[*listMsgId].msg, dispMsgTable[*listMsgId].align);
        listMsgId++;
    }
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Updates a 32-bit number, dynamic display
*/
void DISPupdate32(const DISP_MSG msgID, const uint32_t num32)
{
    char msg[MAX_MSG_BYTES];
    sprintf(msg, dispMsgTable[msgID].msg, num32);
    BSP_LCD_SetFont(dispMsgTable[msgID].pFont);
    BSP_LCD_SetTextColor(dispMsgTable[msgID].txtColor);
    BSP_LCD_DisplayStringAt(dispMsgTable[msgID].x, dispMsgTable[msgID].y, (uint8_t*)msg, dispMsgTable[msgID].align);
}
