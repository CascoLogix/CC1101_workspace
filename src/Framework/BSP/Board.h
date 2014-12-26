/**
 *  @file   Board.h
 */
#ifndef __BSP_BOARD_H
#define __BSP_BOARD_H

/**
 *  MSP430 LaunchPad
 *
 *  @brief  The MSP430 LaunchPad is a modular development platform that can have
 *          daughter boards connected for optional features. The LaunchPad is
 *          considered the motherboard.
 */
#if defined(__BSP_LAUNCHPAD)
  #include "Boards/LaunchPad/LaunchPad.h"
#endif  // __BSP_LAUNCHPAD

#if defined(__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE)
  #include "Boards/LaunchPad/LaunchPad.h"
  #include "Boards/LaunchPad/AIRBoosterPackLite/AIRBoosterPackLite.h"
#endif

/**
 *  MSP430 EZ430
 */
#if defined(__BSP_EZ430)
  #include "Boards/EZ430/EZ430.h"
#endif  // __BSP_EZ430

/**
 *  SmartRFCC1110
 */
#if defined(__BSP_SMARTRFCC1110)
  #include "Boards/SmartRFCC1110/SmartRFCC1110.h"
#endif    /*defined(__BSP_SMARTRFCC1110) */

/**
 *  MSP430 EM-CC430F6137-900
 */
#if defined(__BSP_EMCC430F6137900)
  #include "Boards/EMCC430F6137900/EMCC430F6137900.h"
#endif

/**
 *  MSP430 Experimenter's Board MSP430F5438A
 */
#if defined(__BSP_MSPEXP430F5438A)
  #include "Boards/MSPEXP430F5438A/MSPEXP430F5438A.h"
#endif

#if defined(__BSP_ANMSP430F5510)
  #include "Boards/ANMSP430F5510/ANMSP430F5510.h"
#endif

/**
 *  Include board drivers.
 */
#include "BoardDrivers.h"

#endif  // __BSP_BOARD_H
