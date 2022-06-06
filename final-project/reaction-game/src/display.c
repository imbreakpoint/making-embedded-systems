/* Includes ------------------------------------------------------------------*/
#include "display.h"

/* Global Definitions --------------------------------------------------------*/
/* Local Definitions ---------------------------------------------------------*/

/**
  * @brief  Maximum message length in bytes
*/
#define MAX_MSG_BYTES (20)

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
    {5, "Press button to begin."},
    {4, "Running..."},
    {2, "Game Over!"},
    {7, "Seconds left:"},

    {0, ""}
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
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    // TODO change this at line number
    BSP_LCD_DisplayStringAtLine(dispMsgTable[msgID].ln, (uint8_t*)dispMsgTable[msgID].msg);
}
