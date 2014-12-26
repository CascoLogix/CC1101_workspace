/**
 *  @file   LED.h
 */
#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H

#include "../../BSP/BoardDrivers.h"

/**
 *  @fn   LEDConfigure
 */
#define LEDConfigure(led)                   __BSP_LED_CONFIGURE(led)

/**
 *  @fn   LEDOn
 */
#define LEDOn(led)                          __BSP_LED_ON(led)

/**
 *  @fn   LEDOff
 */
#define LEDOff(led)                         __BSP_LED_OFF(led)

/**
 *  @fn   LEDToggle
 */
#define LEDToggle(led)                      __BSP_LED_TOGGLE(led)

/**
 *  @fn   LEDState
 */
#define LEDState(led)                       __BSP_LED_STATE(led)

#endif  // __DRIVIER_LED_H
