/**
 *  @file   AIRBoosterPack.h
 */
#ifndef __BSP_AIRBOOSTERPACK_H
#define __BSP_AIRBOOSTERPACK_H

// Get driver(s) and configuration.
#include "AIRBoosterPackDrivers.h"
#include "AIRBoosterPackConfig.h"

// Get HAL drivers.
#include "../../../HAL/HAL.h"

#define __BSP_DISABLE_INTERRUPT()           __disable_interrupt()
#define __BSP_ENABLE_INTERRUPT()            __enable_interrupt()
#define __BSP_LOW_POWER_MODE(mode)          \
{                                           \
  if (mode == 0)                            \
    __low_power_mode_0();                   \
}

/**
 *  Microcontroller
 */
#define __BSP_MCU_SOCKET                    20
#define __BSP_CLOCK_SYSTEM                  BASIC_CLOCK_MODULE_PLUS

/**
 *  Exported clock configuration.
 */
#if (defined(__BSP_CONFIG_CUSTOM_CLOCK_HZ)      || \
    defined(__BSP_CONFIG_CUSTOM_MSP430_DCOCTL)  || \
    defined(__BSP_CONFIG_CUSTOM_MSP430_BCSCTL1))
  #define __BSP_CLOCK_HZ                    __BSP_CONFIG_CUSTOM_CLOCK_HZ
  #define __BSP_CONFIG_DCOCTL               __BSP_CONFIG_CUSTOM_DCOCTL
  #define __BSP_CONFIG_DCO_RANGE            __BSP_CONFIG_CUSTOM_DCO_RANGE
#else
  #if (__BSP_CONFIG_CLOCK_HZ == CLOCK_1MHZ)
    #define __BSP_CLOCK_HZ                  CLOCK_1MHZ
    #define __BSP_CONFIG_DCOCTL             CALDCO_1MHZ //!< Factory calibrated value from flash
    #define __BSP_CONFIG_DCO_RANGE          CALBC1_1MHZ //!< Factory calibrated value from flash
  #elif (__BSP_CONFIG_CLOCK_HZ == CLOCK_8MHZ)
    #define __BSP_CLOCK_HZ                  CLOCK_8MHZ
    #define __BSP_CONFIG_DCOCTL             CALDCO_8MHZ //!< Factory calibrated value from flash
    #define __BSP_CONFIG_DCO_RANGE          CALBC1_8MHZ //!< Factory calibrated value from flash
  #elif (__BSP_CONFIG_CLOCK_HZ == CLOCK_12MHZ)
    #define __BSP_CLOCK_HZ                  CLOCK_12MHZ
    #define __BSP_CONFIG_DCOCTL             CALDCO_12MHZ //!< Factory calibrated value from flash
    #define __BSP_CONFIG_DCO_RANGE          CALBC1_12MHZ //!< Factory calibrated value from flash
  #elif (__BSP_CONFIG_CLOCK_HZ == CLOCK_16MHZ)
    #define __BSP_CLOCK_HZ                  CLOCK_16MHZ
    #define __BSP_CONFIG_DCOCTL             CALDCO_16MHZ //!< Factory calibrated value from flash
    #define __BSP_CONFIG_DCO_RANGE          CALBC1_16MHZ //!< Factory calibrated value from flash
  #else
    #error "__BSP_ERROR: Clock frequency is not supported. See LaunchPadConfig.h."
  #endif
#endif


#endif  // __BSP_AIRBOOSTERPACK_H