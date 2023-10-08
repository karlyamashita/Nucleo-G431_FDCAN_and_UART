# Nucleo-G431_FDCAN_and_UART


If you're receiving FDCAN messages and wanting to transmit the data over UART, you may find that the CAN data maybe received before you can finish transmitting the UART message. This is where a ring buffer to hold the UART messages comes in handy. The code shows how to create a message structure with ring buffer pointer.

This code also demonstrates how to make use of HAL status to be sure data was transmitted and increment the ring buffer pointer. If HAL_BUSY then the FW will try to send the UART message again.

For this example I don't have the FDCAN peripheral enabled. But I have 3 arrays with different data that emulates 3 CAN messages that I add to the ring buffer. Then I call transmit_mdb() to transmit all available UART messages. All 3 messages will get sent.

To see how effective it is to check HAL status, there is a "#define CHECK_HAL_STATUS" in the transmit_mdb() function. If you comment that out, then the code will not check for HAL status. This will cause the HAL_UART_Transmit_IT the 1st message but then subsequently return HAL_BUSY on the next two messages because the 1st message is still sending. The last two messages will be lost because the code didn't monitor the HAL status.
