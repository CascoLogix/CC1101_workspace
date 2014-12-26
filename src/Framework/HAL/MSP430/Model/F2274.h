/**
 *  @file   F2274.h
 *
 *  @brief  MSP430F2274 model definition.
 */
#ifndef __MCU_MSP430_F2274_H
#define __MCU_MSP430_F2274_H

//#include "msp430x22x4.h"
#include "msp430f2274.h"

/**
 *  @brief  Processor calibrated clock frequencies.
 */
#define CLOCK_1MHZ                          1000000
#define CLOCK_8MHZ                          8000000
#define CLOCK_12MHZ                         12000000
#define CLOCK_16MHZ                         16000000

/**
 *  @brief MSP430F2274 supported peripherals.
 */
enum PERIPHERAL
{
  NO_PERIPHERAL                             = 0x00,
  BASIC_CLOCK_MODULE_PLUS                   = 0x01,
  USCIA0                                    = 0x02,
  USCIB0                                    = 0x04,
  ADC10                                     = 0x08
};

// Architecture
#define __MCU_MSP430_BASICCLOCKMODULEPLUS
#include "../Peripherals/Architecture/BasicClockModulePlus/BasicClockModulePlus.h"
#define __MCU_MSP430_FLASHMODULE
#include "../Peripherals/Architecture/FlashModule/FlashModule.h"

// Communication
#define __MCU_MSP430_USCI
#define __MCU_MSP430_USCIA0
#define __MCU_MSP430_USCIB0
#define USCIAB0TX_EVENT                     &USCIAB0TXEvent
#define USCIAB0RX_EVENT                     &USCIAB0RXEvent
#include "../Peripherals/Communication/USCI/USCI.h"

// Data Converters
#define __MCU_MSP430_ADC10
#define ADC10_EVENT                         &ADC10Event
#include "../Peripherals/DataConverter/ADC10/ADC10.h"

// GPIO
#define __MCU_MSP430_DIGITALIO
#define __MCU_MSP430_DIGITALIO_PORT1
#define PORT1_EVENT                         &DigitalIOPort1Event
#define __MCU_MSP430_DIGITALIO_PORT2
#define PORT2_EVENT                         &DigitalIOPort2Event
#define __MCU_MSP430_DIGITALIO_PORT3
#define __MCU_MSP430_DIGITALIO_PORT4
#include "../Peripherals/GPIO/DigitalIO/DigitalIO.h"

// Timers
#define __MCU_MSP430_TIMERA
#define __MCU_MSP430_TIMERA3
#define TA_CCR0_EVENT                         &TimerA3CCR0Event
#define TA_CCR1_EVENT                         &TimerA3CCR1Event
#include "../Peripherals/Timer/TimerA/TimerA.h"
#define __MCU_MSP430_TIMERB
#define __MCU_MSP430_TIMERB3
#define TB_CCR0_EVENT                         &TimerB3CCR0Event
#define TB_CCR1_EVENT                         &TimerB3CCR1Event
#include "../Peripherals/Timer/TimerB/TimerB.h"
#define __MCU_MSP430_WATCHDOGTIMERPLUS
#define WDT_EVENT                           &WatchdogTimerEvent
#include "../Peripherals/Timer/WatchdogTimerPlus/WatchdogTimerPlus.h"
#define NMI_EVENT                           &NonMaskableInterruptEvent

#endif  // __MCU_MSP430_F2274_H