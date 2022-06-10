/* Includes ------------------------------------------------------------------*/
#include "temperature.h"

/* Global Definitions --------------------------------------------------------*/
/* Local Definitions ---------------------------------------------------------*/

/**
  * @brief  ADC Handle
*/
static ADC_HandleTypeDef tempAdcHandle;

/**
  * @brief  ADC Channel Handle
*/
static ADC_ChannelConfTypeDef tempAdcChannel;

/* Local Functions -----------------------------------------------------------*/
/* Interrupt Handles ---------------------------------------------------------*/
/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes temperature sensor / ADC
*/
void TEMPinit(void)
{
	tempAdcHandle.Instance = ADC1;

	HAL_ADC_DeInit(&tempAdcHandle);

	if (HAL_ADC_STATE_RESET == HAL_ADC_GetState(&tempAdcHandle))
	{
		__HAL_RCC_ADC1_CLK_ENABLE();
  
		tempAdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
		tempAdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
		tempAdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		tempAdcHandle.Init.ScanConvMode = DISABLE;
		tempAdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
		tempAdcHandle.Init.ContinuousConvMode = ENABLE;
		tempAdcHandle.Init.NbrOfConversion = 1;
		tempAdcHandle.Init.DiscontinuousConvMode = DISABLE;
		tempAdcHandle.Init.NbrOfDiscConversion = 1;
		tempAdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
		tempAdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
		tempAdcHandle.Init.DMAContinuousRequests = DISABLE;

		HAL_ADC_Init(&tempAdcHandle);

		tempAdcChannel.Channel = ADC_CHANNEL_TEMPSENSOR;
		tempAdcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
		tempAdcChannel.Rank = 1;
		tempAdcChannel.Offset = 0;

		HAL_ADC_ConfigChannel(&tempAdcHandle, &tempAdcChannel);
	}
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Reads the value of temperature sensor
*/
HAL_StatusTypeDef TEMPread(float* temperature)
{
	if (HAL_OK != HAL_ADC_Start(&tempAdcHandle))
	{
		return HAL_ERROR;
	}

	if (HAL_OK != HAL_ADC_PollForConversion(&tempAdcHandle, HAL_MAX_DELAY))
	{
		return HAL_ERROR;
	}

	if (HAL_ADC_STATE_REG_EOC != (HAL_ADC_GetState(&tempAdcHandle) & HAL_ADC_STATE_REG_EOC))
	{
		return HAL_ERROR;
	}

	volatile uint16_t counts = HAL_ADC_GetValue(&tempAdcHandle);

    static const float VREF_MV = 3000.0;
    static const float ADC_MAX_COUNTS = 0xFFF;
    static const float VREF_25C = 0.76;
    static const float AVG_SLOPE_25C = 0.0025;
    static const float OFFSET_25C = 25.0;
    const float adcMV = (float)(counts * VREF_MV) / ADC_MAX_COUNTS;
    const float adcV = adcMV / 1000.0;
    
    *temperature = ((adcV - VREF_25C) / AVG_SLOPE_25C) + OFFSET_25C;

	return HAL_OK;
}
