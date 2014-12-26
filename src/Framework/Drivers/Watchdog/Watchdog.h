/**
 *  @file   Watchdog.h
 */
#ifndef __DRIVER_WATCHDOG_H
#define __DRIVER_WATCHDOG_H

#include "../../BSP/BoardDrivers.h"

/**
 *  @fn     WatchdogConfigure
 * 
 *  @brief  Configures supported hardware for watchdog operation.
 */
#define WatchdogConfigure()                 __BSP_WATCHDOG_CONFIGURE()

/**
 *  @fn     WatchdogHold
 */
#define WatchdogHold()                      __BSP_WATCHDOG_HOLD()

/**
 *  @fn     WatchdogReset
 */
#define WatchdogReset()                     __BSP_WATCHDOG_RESET()

#endif  // __DRIVER_WATCHDOG_H
