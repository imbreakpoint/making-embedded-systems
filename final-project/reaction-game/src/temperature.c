#include "temperature.h"

static ADC_HandleTypeDef AdcHandle;
static ADC_ChannelConfTypeDef AdcChannel;

void TEMPinit(void)
{
	AdcHandle.Instance = ADC1;

	HAL_ADC_DeInit(&AdcHandle);

	if (HAL_ADC_STATE_RESET == HAL_ADC_GetState(&AdcHandle))
	{
		__HAL_RCC_ADC1_CLK_ENABLE();
    
		AdcHandle.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV2;
		AdcHandle.Init.Resolution = ADC_RESOLUTION_12B;
		AdcHandle.Init.DataAlign = ADC_DATAALIGN_RIGHT;
		AdcHandle.Init.ScanConvMode = DISABLE;
		AdcHandle.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
		AdcHandle.Init.ContinuousConvMode = ENABLE;
		AdcHandle.Init.NbrOfConversion = 1;
		AdcHandle.Init.DiscontinuousConvMode = DISABLE;
		AdcHandle.Init.NbrOfDiscConversion = 1;
		AdcHandle.Init.ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
		AdcHandle.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
		AdcHandle.Init.DMAContinuousRequests = DISABLE;

		HAL_ADC_Init(&AdcHandle);

		AdcChannel.Channel = ADC_CHANNEL_TEMPSENSOR;
		AdcChannel.SamplingTime = ADC_SAMPLETIME_480CYCLES;
		AdcChannel.Rank = 1;
		AdcChannel.Offset = 0;

		HAL_ADC_ConfigChannel(&AdcHandle, &AdcChannel);
	}
}

__attribute__((optimize(0)))
HAL_StatusTypeDef TEMPread(float* temperature)
{
	if (HAL_OK != HAL_ADC_Start(&AdcHandle))
	{
		return HAL_ERROR;
	}

	if (HAL_OK != HAL_ADC_PollForConversion(&AdcHandle, HAL_MAX_DELAY))
	{
		return HAL_ERROR;
	}

	if (HAL_ADC_STATE_REG_EOC != (HAL_ADC_GetState(&AdcHandle) & HAL_ADC_STATE_REG_EOC))
	{
		return HAL_ERROR;
	}

	volatile uint16_t counts = HAL_ADC_GetValue(&AdcHandle);

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
