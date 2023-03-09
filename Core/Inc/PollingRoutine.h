/*
 * PollingRoutine.h
 *
 *  Created on: Mar 8, 2023
 *      Author: codek
 */

#ifndef INC_POLLINGROUTINE_H_
#define INC_POLLINGROUTINE_H_

#include "main.h"

#define BUFFER_SIZE 4 // increase if msgPtr.iCnt_OverFlow > 0

typedef struct
{
	struct
	{
		uint32_t length;
		uint8_t data[8];
	}Queue[BUFFER_SIZE];
	RING_BUFF_INFO msgPtr;
}mdb_message_t ;

void PollingInit(void);
void PollingRoutine(void);

int UART_Tx_AddData(mdb_message_t *msg, uint8_t *data, uint32_t size);
int transmit_mdb(mdb_message_t *mdb_message);

#endif /* INC_POLLINGROUTINE_H_ */
