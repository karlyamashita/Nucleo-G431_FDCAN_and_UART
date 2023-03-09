/*
 * PollingRoutine.c
 *
 *  Created on: Mar 8, 2023
 *      Author: codek
 */


#include "main.h"
#include "PollingRoutine.h"

extern UART_HandleTypeDef huart2;


// simulated FDCAN data
uint8_t data0[] = {1,2,3,4,5,6,7,8};
uint8_t data1[] = {0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88};
uint8_t data2[] = {0xaa,0xbb,0xcc,0xdd,0xee,0xff,0x10,0x20};


mdb_message_t mdb_message = {0};

int status;


// called before main while loop
void PollingInit(void)
{

	// this is where you are receiving FDCAN messages and adding to a UART tx buffer.

	status = UART_Tx_AddData(&mdb_message, data0, 8);
	if (status != 0)
	{
		Error_Handler(); // May need to increase buffer size if this is called
	}

	// check status for these as well
	UART_Tx_AddData(&mdb_message, data1, 8);
	UART_Tx_AddData(&mdb_message, data2, 8);
}

// called from inside main while loop
void PollingRoutine(void)
{
	transmit_mdb(&mdb_message);
}

int UART_Tx_AddData(mdb_message_t *msg, uint8_t *data, uint32_t size)
{
	if(msg->msgPtr.iCnt_OverFlow) return 1;

	memcpy(&msg->Queue[msg->msgPtr.iIndexIN].data, data, size);
	msg->Queue[msg->msgPtr.iIndexIN].length = size;
	DRV_RingBuffPtr__Input(&msg->msgPtr, BUFFER_SIZE);

	return 0;
}

int transmit_mdb(mdb_message_t *msg)
{
	int status = 0;

	if(msg->msgPtr.iCnt_Handle)
	{

//#define CHECK_HAL_STATUS

#ifdef CHECK_HAL_STATUS
		// checking for HAL_OK before incrementing pointer to next data
		if(HAL_UART_Transmit_IT(&huart2, msg->Queue[msg->msgPtr.iIndexOUT].data, msg->Queue[msg->msgPtr.iIndexOUT].length) == HAL_OK)
		{
			DRV_RingBuffPtr__Output(&msg->msgPtr, BUFFER_SIZE); // only increment pointer to next message when status is HAL_OK
		}
#else
		// not checking for HAL_OK.
		HAL_UART_Transmit_IT(&huart2, &msg->Queue[msg->msgPtr.iIndexOUT].data, msg->Queue[msg->msgPtr.iIndexOUT].length);
		DRV_RingBuffPtr__Output(&msg->msgPtr, BUFFER_SIZE);
#endif
	}

	return status;
}
