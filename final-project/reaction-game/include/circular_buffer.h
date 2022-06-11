#ifndef _CIRCULAR_BUFFER_H
#define	_CIRCULAR_BUFFER_H

/* Includes ------------------------------------------------------------------*/
#include "gyroscope.h"

/* Global Macros -------------------------------------------------------------*/

/**
    * @brief  maximum size of circular buffer
*/
#define CB_BUF_MAX (25)

/* Global Defines ------------------------------------------------------------*/
/**
    * @brief  data structure for data to store in buffer
*/
typedef struct
{ 
    GYRO_DATA sample;   /*!< Sample */
} CB_BUF_DATA;

/**
    * @brief  buffer status error codes 
*/
typedef enum 
{    
    CB_BUF_OK = 0,                 /*!< Buffer ok */
    CB_BUF_INSERT_OVERWRITE = 1,   /*!< Overwrite */
    CB_BUF_REMOVE_EMPTY = 2        /*!< Empty */
} CB_BUF_STATUS;

/* Global Functions ----------------------------------------------------------*/
/**
  * @brief  initializes the buffer 
  * @param  None
  * @retval None
*/
void CBbufferInit(void);

/**
  * @brief  writes data to front of queue
  * @param  data: data to be pushed to the buffer
  * @retval buffer error status 
*/
CB_BUF_STATUS CBinsert(const CB_BUF_DATA data);

/**
  * @brief  reads data from the back of queue
  * @param  pData: pointer to where the read data will be saved
  * @retval buffer error status 
*/
CB_BUF_STATUS CBremove(CB_BUF_DATA *pData);

#endif
