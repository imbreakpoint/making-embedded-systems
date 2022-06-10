/* Includes ------------------------------------------------------------------*/
#include "circular_buffer.h"
#include "gyroscope.h"

/* Global Definitions --------------------------------------------------------*/
/* Local Definitions ---------------------------------------------------------*/

/**
	* @brief  filter data
*/
typedef struct
{
	GYRO_DATA sum;      /*!< running sum */
	GYRO_DATA average;  /*!< latest average */
} MAF_FILTER;

/**
	* @brief  filter
*/
static MAF_FILTER mafFilter = { 0 };

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes moving average filter
*/
void MAFinit(void)
{
	CBbufferInit();
	mafFilter.sum.x = 0.0;
	mafFilter.sum.y = 0.0;
	mafFilter.sum.z = 0.0;

	mafFilter.average.x = 0.0;
	mafFilter.average.y = 0.0;
	mafFilter.average.z = 0.0;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Calculates the new average using the latest sample
*/
void MAFsmooth(GYRO_DATA sample)
{
	// remove
	CB_BUF_DATA oldSample = { 0 };
	CBremove(&oldSample);

	// update sum
	mafFilter.sum.x = mafFilter.sum.x - oldSample.sample.x + sample.x;
	mafFilter.sum.y = mafFilter.sum.y - oldSample.sample.y + sample.y;  
	mafFilter.sum.z = mafFilter.sum.z - oldSample.sample.z + sample.z;

	mafFilter.average.x = mafFilter.sum.x / CB_BUF_MAX;
	mafFilter.average.y = mafFilter.sum.y / CB_BUF_MAX;
	mafFilter.average.z = mafFilter.sum.z / CB_BUF_MAX;

	// add to buffer
	CB_BUF_DATA newSample = { sample };
	CBinsert(newSample);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Returns the current average value
*/
GYRO_DATA MAFgetResult(void)
{
	return mafFilter.average;
}
