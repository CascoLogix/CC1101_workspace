/**
 *  \file   Config.h
 *
 *  \brief  MSP430 Hardware Abstraction Layer (HAL) configuration.
 */
#ifndef __HAL_MSP430_CONFIG_H
#define __HAL_MSP430_CONFIG_H

#include "../Common/CommonDefinitions.h"

#include "../Common/DataManagement/CircularBuffer/CircularBuffer.h"
#include "../Common/EventHandling/EventHandling.h"
#include "../Common/RandomNumberGenerator/RandomNumberGenerator.h"

#if defined(__MCU_MSP430_G2553)
  #include "Model/G2553.h"
#endif

#if defined(__MCU_MSP430_F2274)
  #include "Model/F2274.h"
#endif

#if defined(__MCU_MSP430_F5438A)
  #include "Model/F5438A.h"
#endif

#if defined(__MCU_MSP430_F5510)
  #include "Model/F5510.h"
#endif

#if defined(__MCU_MSP430_F6137)
  #include "Model/F6137.h"
#endif

#endif  // __HAL_MSP430_CONFIG_H
