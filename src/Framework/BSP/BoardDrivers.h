/**
 *  @file   BoardDrivers.h
 */
#ifndef __BSP_BOARD_DRIVERS_H
#define __BSP_BOARD_DRIVERS_H

#if defined(__BSP_LAUNCHPAD)
  #include "Boards/LaunchPad/LaunchPadDrivers.h"
#endif

#if defined(__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE)
  #include "Boards/LaunchPad/LaunchPadDrivers.h"
  #include "Boards/LaunchPad/AIRBoosterPackLite/AIRBoosterPackLiteDrivers.h"
#endif

#if defined(__BSP_EZ430)
  #include "Boards/EZ430/EZ430Drivers.h"
#endif

#if defined(__BSP_EMCC430F6137900)
  #include "Boards/EMCC430F6137900/EMCC430F6137900Drivers.h"
#endif

#if defined(__BSP_MSPEXP430F5438A)
  #include "Boards/MSPEXP430F5438A/MSPEXP430F5438ADrivers.h"
#endif

#if defined(__BSP_ANMSP430F5510)
  #include "Boards/ANMSP430F5510/ANMSP430F5510Drivers.h"
#endif

#if defined(__BSP_SMARTRFCC1110)
  #include "Boards/SmartRFCC1110/SmartRFCC1110Drivers.h"
#endif

#endif  // __BSP_BOARD_DRIVERS_H
