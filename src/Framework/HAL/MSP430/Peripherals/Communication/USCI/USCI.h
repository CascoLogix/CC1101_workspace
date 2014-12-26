/**
 *  \file   USCI.h
 */
#ifndef __MCU_MSP430_USCI_H
#define __MCU_MSP430_USCI_H

#include "../../../Config.h"

#if defined(__MCU_MSP430_USCI)

#define UART_UCLK                           UCSSEL_0
#define UART_ACLK                           UCSSEL_1
#define UART_SMCLK                          UCSSEL_2

#define UART_BAUD_9600                      9600
#define UART_BAUD_19200                     19200
#define UART_BAUD_38400                     38400
#define UART_BAUD_57600                     57600
#define UART_BAUD_115200                    115200

#define UART_PARITY_NONE                    0
#define UART_PARITY_ODD                     1
#define UART_PARITY_EVEN                    UCPAR

#define UART_DATA_8BITS                     0
#define UART_DATA_7BITS                     UC7BIT

#define UART_STOP_1BIT                      0
#define UART_STOP_2BITS                     UCSPB

#define SPI_CLOCK_PHASE_CHANGE              0
#define SPI_CLOCK_PHASE_CAPTURE             UCCKPH

#define SPI_CLOCK_ACTIVE_LOW                0
#define SPI_CLOCK_ACTIVE_HIGH               UCCKPL

#define SPI_MODE_3WIRE                      UCMODE_0

#define SPI_CLOCK_SOURCE_ACLK               UCSSEL_1
#define SPI_CLOCK_SOURCE_SMCLK              UCSSEL_2

typedef struct USCIBuffer
{
  CircularBuffer tx;
  CircularBuffer rx;
  enum CIRCULAR_BUFFER_OPERATION state;
  unsigned char count;
} USCIBuffer;

#define USCI_SPI_MODE_MASK                  0x06  //!< Mask for UCMODEx bits in UCXxCTL0 register

#define USCI_NO_EVENT     0
#define USCIA0_TX_EVENT   1
#define USCIA0_RX_EVENT   2
#define USCIB0_TX_EVENT   3
#define USCIB0_RX_EVENT   4

//#pragma inline
//unsigned char GetUSCISPIMode(enum PERIPHERAL peripheral)
//{
//  #if defined(__MCU_MSP430_USCIA0)
//  if (peripheral == USCIA0)
//  {
//    if ((UCA0CTL0 & USCI_SPI_MODE_MASK) == SPI_MODE_3WIRE)
//      return SPI_MODE_3WIRE;
//  }
//  #endif
//  #if defined(__MCU_MSP430_USCIB0)
//  if (peripheral == USCIB0)
//  {
//    if ((UCB0CTL0 & USCI_SPI_MODE_MASK) == SPI_MODE_3WIRE)
//      return SPI_MODE_3WIRE;
//  }
//  #endif
//  // Error: We should have returned in one of the above statements.
//  return 0xFF;
//}

#if defined(__MCU_MSP430_USCIA0)

// UART uses an Tx/Rx queue pair.
extern USCIBuffer USCIA0Buffer;

#endif  // USCIA0 SUB MODULE

/**
 *  \fn   USCIAB0TXInterruptServiceRoutine
 */
__interrupt void __hal_USCIAB0TXInterruptServiceRoutine();
extern unsigned char (*USCIAB0TXEvent)(const void *);

/**
 *  \fn   USCIAB0RXInterruptServiceRoutine
 */
__interrupt void __hal_USCIAB0RXInterruptServiceRoutine();
extern unsigned char (*USCIAB0RXEvent)(const void *);

#endif  // USCI MODULE

#endif  // __MCU_MSP430_USCI_H
