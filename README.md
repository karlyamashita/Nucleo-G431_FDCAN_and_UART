# Nucleo-G431_FDCAN_UART


If you're receiving FDCAN messages and wanting to transmit the data over UART, you may find that the CAN data maybe received before you can finish transmitting the UART message. This is where a ring buffer to hold the UART messages comes in handy. The code shows how to create a message structure with ring buffer pointer.

This code also demonstrates how to make use of HAL status to be sure data was transmitted and increment the ring buffer pointer. If HAL_BUSY then the FW will try to send the UART message again.

