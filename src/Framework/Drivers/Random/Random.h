/**
 *  @file   Random.h
 */
#ifndef __DRIVER_RANDOM_H
#define __DRIVER_RANDOM_H

#include "../../BSP/BoardDrivers.h"


/**
 *  @fn   LEDState
 */
#define GenerateRandomNumber()                       __BSP_RAND()

#endif  // __DRIVER_RANDOM_H
