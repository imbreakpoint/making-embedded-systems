/* Includes ------------------------------------------------------------------*/
#include "gyroscope.h"

#include "stm32f429i_discovery_gyroscope.h"

/* Global Definitions --------------------------------------------------------*/


/* Local Definitions ---------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Interface to external driver
  * @param  data pointer to date that will be read
  * @retval None
*/
static void gyroGetXYZ(GYRO_DATA* data);

/**
  * @brief  Number of samples to collect for calibration
*/
#define GYRO_NUM_CAL_SAMPLES (1000)

/**
  * @brief  Number of coordinates in gyro array
*/
#define GYRO_NUM_COORDINATES (3)

/**
  * @brief  Boot up sensor time in milliseconds
*/
#define GYRO_BOOT_DELAY_MS (250)

/**
  * @brief  Time in milliseconds between 2 cal samples
*/
#define GYRO_CAL_DELAY_MS (10)

/**
  * @brief  X coordinate in array
*/
#define GYRO_COOR_X (0)

/**
  * @brief  Y coordinate in array
*/
#define GYRO_COOR_Y (1)

/**
  * @brief  Z coordinate in array
*/
#define GYRO_COOR_Z (2)

/**
  * @brief  Gyroscope status
*/
typedef enum
{
	GYRO_STATUS_INIT,
	GYRO_STATUS_CAL_IN_PROGRESS,
	GYRO_STATUS_CAL_DONE,

	GYRO_STATUS_UNKNOWN
} GYRO_STATUS;

/**
  * @brief  Gyroscope noise floor
*/
static GYRO_DATA gyroNoise = { 0 };

/**
  * @brief  Gyroscope current status
*/
static GYRO_STATUS gyroStatus = GYRO_STATUS_UNKNOWN;

/* Local Functions -----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Interface to external driver
*/
static void gyroGetXYZ(GYRO_DATA* data)
{
	float xyz[GYRO_NUM_COORDINATES] = {0};
	BSP_GYRO_GetXYZ(xyz);
	data->x = xyz[GYRO_COOR_X];
	data->y = xyz[GYRO_COOR_Y];
	data->z = xyz[GYRO_COOR_Z];
}

/* Interrupt Handles ---------------------------------------------------------*/
/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  Initializes gyroscope
*/
void GYROinit(void)
{
	gyroStatus = GYRO_STATUS_INIT;
	BSP_GYRO_Init();
	HAL_Delay(GYRO_BOOT_DELAY_MS);
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Calibrates the gyroscope
*/
void GYROcalibrate(void)
{
	gyroStatus = GYRO_STATUS_CAL_IN_PROGRESS;

	GYRO_DATA calBuffer[1] = { 0 };
	GYRO_DATA sum = { 0 };

	for (uint16_t i = 0; i < GYRO_NUM_CAL_SAMPLES; i++)
	{
		gyroGetXYZ(&calBuffer[0]);

		sum.x += calBuffer[0].x;
		sum.y += calBuffer[0].y;
		sum.z += calBuffer[0].z;

		HAL_Delay(GYRO_CAL_DELAY_MS);
	}

	gyroNoise.x = sum.x / GYRO_NUM_CAL_SAMPLES;
	gyroNoise.y = sum.y / GYRO_NUM_CAL_SAMPLES;
	gyroNoise.z = sum.z / GYRO_NUM_CAL_SAMPLES;

	gyroStatus = GYRO_STATUS_CAL_DONE;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  Reads the current coordinates
*/
bool GYROread(GYRO_DATA* data)
{
	bool status = false;
	if (gyroStatus == GYRO_STATUS_CAL_DONE)
	{
		gyroGetXYZ(data);
		data->x -= gyroNoise.x;
		data->y -= gyroNoise.y;
		data->z -= gyroNoise.z;
		status = true;
	}

	return status;
}
