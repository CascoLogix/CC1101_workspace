/**
 *  \file   HAL.h
 */
#ifndef __HAL_H
#define __HAL_H

#include "Common/CommonDefinitions.h"

#if defined(__MCU_MSP430_SERIES)
  #include "MSP430/Peripherals/Architecture/Architecture.h"
  #include "MSP430/Peripherals/Communication/Communication.h"
  #include "MSP430/Peripherals/DataConverter/DataConverter.h"
  #include "MSP430/Peripherals/GPIO/GPIO.h"
  #include "MSP430/Peripherals/Timer/Timer.h"

#elif defined (__MCU_CC8051_SERIES)
  #include "8051/Peripherals/Communication/Communication.h"
  #include "8051/Peripherals/Architecture/Architecture.h"
  #include "8051/Peripherals/GPIO/GPIO.h"
//  #include "8051/Peripherals/GPIO/GPIO.h"
//  #include "8051/Peripherals/Timers/Timers.h"
#endif

#endif  // __HAL_H
