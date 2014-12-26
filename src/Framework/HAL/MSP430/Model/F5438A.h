/**
 *  @file   F5438A.h
 */
#ifndef __MCU_MSP430_F5438A_H
#define __MCU_MSP430_F5438A_H

#include "msp430f5438A.h"

/**
 *  @brief  Processor calibrated clock frequencies.
 */
#define CLOCK_1MHZ                          1000000
#define CLOCK_8MHZ                          8000000
#define CLOCK_12MHZ                         12000000
#define CLOCK_16MHZ                         16000000

/**
 *  @brief   MSP430F5438 supported peripherals.
 */
enum PERIPHERAL
{
  NO_PERIPHERAL               = 0x00,
  UNIFIED_CLOCK_SYSTEM        = 0x01,
  USCIA0                      = 0x02,
  USCIB0                      = 0x04,
  USCIA1                      = 0x08,
  USCIB1                      = 0x10
};

// Architecture
#define __MCU_MSP430_UNIFIEDCLOCKSYSTEM
//TODO: Include unified clock system interface.

// Communication
#define __MCU_MSP430_USCI
#define __MCU_MSP430_USCIA0
#define __MCU_MSP430_USCIB0
#define USCIA0_EVENT                        &USCIA0Event
#define USCIB0_EVENT                        &USCIB0Event
#include "../Peripherals/Communication/USCI/USCI.h"

// TODO: Add all 4 USCI modules.
//#define __MCU_MSP430_USCIA1
//#define __MCU_MSP430_USCIB1

// GPIO
#define __MCU_MSP430_DIGITALIO
#define __MCU_MSP430_DIGITALIO_PORT1
#define PORT1_EVENT                         &DigitalIOPort1Event
#define __MCU_MSP430_DIGITALIO_PORT2
#define PORT2_EVENT                         &DigitalIOPort2Event
#define __MCU_MSP430_DIGITALIO_PORT3
#define __MCU_MSP430_DIGITALIO_PORT4
#define __MCU_MSP430_DIGITALIO_PORT5
#define __MCU_MSP430_DIGITALIO_PORT6
#define __MCU_MSP430_DIGITALIO_PORT7
#define __MCU_MSP430_DIGITALIO_PORT8
#define __MCU_MSP430_DIGITALIO_PORT9
#define __MCU_MSP430_DIGITALIO_PORT10
#define __MCU_MSP430_DIGITALIO_PORTJ
#include "../Peripherals/GPIO/DigitalIO/DigitalIO.h"

// Timers
#define __MCU_MSP430_WATCHDOGTIMERPLUS_A
#define WDT_EVENT                           &WatchdogTimerEvent
#include "../Peripherals/Timer/WatchdogTimerPlus/WatchdogTimerPlus.h"
#define NMI_EVENT                           &NonMaskableInterruptEvent

#endif  // __MCU_MSP430_F5438A_H
