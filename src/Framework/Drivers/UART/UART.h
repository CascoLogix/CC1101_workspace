/**
 *  @file   UART.h
 *
 *  @brief  A generic UART driver interface.
 */
#ifndef __DRIVER_UART_H
#define __DRIVER_UART_H

#include "../../BSP/BoardDrivers.h"

/**
 *  @fn     UARTConfigure
 *
 *  @brief  Setup UART hardware to operate with a selected baud rate, data bits,
 *          parity bit, and stop bits.
 */
#define UARTConfigure(uartId)      \
{                                  \
  __BSP_UART_CONFIGURATION(uartId) \
}

/**
 *  @fn     UARTTransmitByte
 *
 *  @brief  Write a single byte to the internal UART buffer for transmission.
 *
 *  @return Success of the operation.
 */
#define UARTTransmitByte(uartId, value)     __BSP_UART_TRANSMIT_BYTE(__BSP_UART_ID(uartId), value)

/**
 *  @fn     UARTReceiveByte
 *
 *  @brief  Read a single byte from the internal UART buffer.
 *
 *  @return Success of the operation.
 */
#define UARTReceiveByte(uartId, value)      __BSP_UART_RECEIVE_BYTE(__BSP_UART_ID(uartId), value)

/**
 *  @fn     UARTBusy
 *
 *  @brief  Check the current state of the UART.
 *
 *  @return Busy state of the UART.
 */
#define UARTBusy(uartId)                    __BSP_UART_BUSY(__BSP_UART_ID(uartId))

#endif  // __DRIVER_UART_H
