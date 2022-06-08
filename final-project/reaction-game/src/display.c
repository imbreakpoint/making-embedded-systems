/* Includes ------------------------------------------------------------------*/
#include "display.h"

#include "fonts.h"
#include "stm32f429i_discovery_lcd.h"

/* Global Definitions --------------------------------------------------------*/
/* Local Definitions ---------------------------------------------------------*/

/**
	* @brief  Maximum message length in bytes
*/
#define MAX_MSG_BYTES (20)

/**
	* @brief  Display time left
*/
#define DISP_GAME_TIME_LEFT (2)

/**
	* @brief  Game instructions line 1
*/
#define DISP_GAME_INSTRUCT_LN1 (5)

/**
	* @brief  Game insteructions line 2
*/
#define DISP_GAME_INSTRUCT_LN2 (7)

/**
	* @brief  Display temperature?
*/
#define DISP_TEMP (15)

/**
	* @brief  Message information
*/
typedef struct
{
	uint16_t ln;                /*!< Line number to display message on */
	char msg[MAX_MSG_BYTES];    /*!< Message string to show */
} dispMsgInfo;

/**
	* @brief  Message table
*/
static const dispMsgInfo dispMsgTable[] =
{
	{	DISP_GAME_INSTRUCT_LN2, 	"Push button to begin"	},
	{	DISP_GAME_INSTRUCT_LN2, 	"Running..."			},
	{	DISP_GAME_INSTRUCT_LN1, 	"Game Over!"			},
	{	DISP_GAME_TIME_LEFT, 		"Seconds left:"			},
	{	DISP_GAME_INSTRUCT_LN2, 	"Go Clockwise"			},
	{	DISP_GAME_INSTRUCT_LN2, 	"Go Anti-Clockwise"		},

	{	0, 							""						}
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
	BSP_LCD_DisplayStringAtLine(5, (uint8_t*)"Hope this works!");
}

/**
 	* @brief  Displays a message on screen
*/
void DISPshowMsg(DISP_MSG msgID)
{
	BSP_LCD_ClearStringLine(dispMsgTable[msgID].ln);
	// TODO change this at line numbe
	BSP_LCD_DisplayStringAtLine(dispMsgTable[msgID].ln, (uint8_t*)dispMsgTable[msgID].msg);
}
