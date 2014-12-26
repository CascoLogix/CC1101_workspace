/**
 *  \file   CommonDefinitions.h
 */
#ifndef __HAL_COMMON_DEFINITIONS_H
#define __HAL_COMMON_DEFINITIONS_H

//#define NDEBUG

#include "intrinsics.h"

#ifndef __IAR_SYSTEMS_ICC__
#define __low_power_mode_off_on_exit()		_low_power_mode_off_on_exit()
#ifdef USE_INLINE
#error "__HAL_ERROR: No inline support for selected compiler."
#endif
#endif

#if !defined(NDEBUG)
  #include "assert.h"
#endif

#define NULL                                (void *)0

enum PORT
{
  NO_PORT,                                  //!< No port (default)
  PORT1,                                    //!< Port 1
  PORT2,                                    //!< Port 2
  PORT3,                                    //!< Port 3
  PORT4,                                    //!< Port 4
  PORT5,                                    //!< Port 5
  PORT6,                                    //!< Port 6
  PORT7,                                    //!< Port 7
  PORT8,                                    //!< Port 8
  PORT9,                                    //!< Port 9
  PORT10,                                   //!< Port 10
  PORTJ                                     //!< Port J
};

enum PIN
{
  NO_PIN  = 0,                              //!< No pin (default)
  PIN0    = 0x01,
  PIN1    = 0x02,
  PIN2    = 0x04,
  PIN3    = 0x08,
  PIN4    = 0x10,
  PIN5    = 0x20,
  PIN6    = 0x40,
  PIN7    = 0x80
};

enum DIRECTION
{
  NO_DIRECTION,                             //!< No direction (default)
  INPUT,
  OUTPUT
};

typedef const struct Connection
{
  enum PORT port;
  enum PIN pin;
  enum DIRECTION direction;
} Connection;

enum POLARITY
{
  ACTIVE_LOW      = 0,
  ACTIVE_HIGH     = 1
};

#if defined(__MSP430G2553__)
  #define __MCU_MSP430_SERIES
  #define __MCU_MSP430_G2553
  #include "../MSP430/Config.h"
#endif

#if defined(__MSP430F2274__)
  #define __MCU_MSP430_SERIES
  #define __MCU_MSP430_F2274
  #include "../MSP430/Config.h"
#endif

#if defined(__MSP430F5438A__)
  #define __MCU_MSP430_SERIES
  #define __MCU_MSP430_F5438A
  #include "../MSP430/Config.h"
#endif

#if defined(__CC430F6137__)
  #define __MCU_MSP430_SERIES
  #define __MCU_MSP430_F6137
  #include "../MSP430/Config.h"
#endif

#if defined(__MSP430F5510__)
  #define __MCU_MSP430_SERIES
  #define __MCU_MSP430_F5510
  #include "../MSP430/Config.h"
#endif

#if defined(__CC1110F32__)
  #define __MCU_CC8051_SERIES
  #define __MCU_CC8051_CC1110F32
  #include "../8051/Config.h"
#endif

#endif  // __HAL_COMMON_DEFINITIONS_H
