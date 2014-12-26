/**
 *  @file     F6137.h
 */
#ifndef __MCU_MSP430_F6137_H
#define __MCU_MSP430_F6137_H

#include "cc430f6137.h"

enum PERIPHERAL
{
  NO_PERIPHERAL                             = 0x00,
  USCIA0                                    = 0x02,
  USCIB0                                    = 0x03
};

// Communication
#define __MCU_MSP430_USCI
#define __MCU_MSP430_USCIA0
#define __MCU_MSP430_USCIB0
#define USCIAB0TX_EVENT                     &USCIAB0TXEvent
#define USCIAB0RX_EVENT                     &USCIAB0RXEvent
#include "../Peripherals/Communication/USCI/USCI.h"

// GPIO
#define __MCU_MSP430_DIGITALIO
#define __MCU_MSP430_DIGITALIO_PORT1
#define PORT1_EVENT                         &DigitalIOPort1Event
#define __MCU_MSP430_DIGITALIO_PORT2
#define PORT2_EVENT                         &DigitalIOPort2Event
#define __MCU_MSP430_DIGITALIO_PORT3
#define __MCU_MSP430_DIGITALIO_PORT4
#include "../Peripherals/GPIO/DigitalIO/DigitalIO.h"

#endif  // __MCU_MSP430_F6137_H