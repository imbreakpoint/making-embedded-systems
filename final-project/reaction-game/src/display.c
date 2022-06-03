/* Includes ------------------------------------------------------------------*/
#include "display.h"

/* Global Definitions --------------------------------------------------------*/
/* Local Definitions ---------------------------------------------------------*/
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
