/* Includes ------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "circular_buffer.h"

/* Local Definitions ---------------------------------------------------------*/

/**
  * @brief  circular buffer data structure to read/write data
*/
typedef struct
{
	CB_BUF_DATA buffer[CB_BUF_MAX];     /*!< data buffer */
	uint16_t head;                      /*!< keeps track of writing to buffer */
	uint16_t tail;                      /*!< keeps track of reading from the buffer */
	uint16_t count;                     /*!< number of elements in buffer */
} CB_CIRC_BUF;


/**
  * @brief  buffer to store the commands received
*/
static CB_CIRC_BUF cbCBuf;

/**
  * @brief  checks if buffer is full or empty depending on the number of elements in the buffer
  * @param  None
  * @retval true if buffer is emptyGAME_STATE game state direction
*/
static bool isEmpty(void);

/* Local Functions -----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  checks if buffer is full or empty depending on the number of elements in the buffer
*/
static bool isEmpty(void)
{	
	return (cbCBuf.count == 0);
}

/* Global Functions ----------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/**
  * @brief  initializes the buffer 
*/
void CBbufferInit(void)
{
	cbCBuf.head = 0;
	cbCBuf.tail = 0 ;
	cbCBuf.count = 0;     
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  writes data to front of queue
*/
CB_BUF_STATUS CBinsert(CB_BUF_DATA data)
{
	CB_BUF_STATUS status = CB_BUF_OK;

	// copy the data to front of the buffer
	memcpy((void *)&cbCBuf.buffer[cbCBuf.head], &data, sizeof(CB_BUF_DATA));

	// check if we are overwriting the tail
	if (!isEmpty() && cbCBuf.head == cbCBuf.tail)
	{
		status = CB_BUF_INSERT_OVERWRITE;
	}

	// increment count if buffer is not full
	if (cbCBuf.count != CB_BUF_MAX)
	{
		cbCBuf.count++;
	}

	// increment head (wrap if necessary)   
	cbCBuf.head = (cbCBuf.head + 1) % CB_BUF_MAX;
	
	return status;
}

/*----------------------------------------------------------------------------*/
/**
  * @brief  reads data from the back of queue
*/
CB_BUF_STATUS CBremove(CB_BUF_DATA *data)
{   
	CB_BUF_STATUS status = CB_BUF_OK;
 
	// return error code to indicate that, buffer is empty and hence read is not possible
	if (isEmpty())
	{
		return CB_BUF_REMOVE_EMPTY;
	}

	// copy data to pointer
	memcpy((void *)data, (void *)&cbCBuf.buffer[cbCBuf.tail], sizeof(CB_BUF_DATA));    

	// decrement the number of elements in buffer counter
	cbCBuf.count--;    

	// increment tail (wrap if necessary)
	cbCBuf.tail = (cbCBuf.tail + 1) % CB_BUF_MAX;   

	return status;
}
