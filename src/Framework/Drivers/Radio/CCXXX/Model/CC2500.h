/**
 *  @file CC2500.h
 *
 *  @brief CC2500 model register definitions.
 *
 *  @author   BB
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup [BB]
 */
#ifndef __RADIO_CCXXX_CC2500_H
#define __RADIO_CCXXX_CC2500_H

// NOTE: The CC2500 radio is a CC1101 that is able to communicate at 2.4GHz.
#include "CC1101.h"

/**
 *  CC1101RFSettings
 *
 *  @brief Represents a CC2500 configuration.
 */
typedef CC1101RFSettings CC2500RFSettings;

/**
 *  CC1101RFChannel
 *
 *  @brief Represents a CC2500 channel.
 */
typedef CC1101RFChannel CC2500RFChannel;

/**
 *  CC1101RFCalibration
 *
 *  @brief Represents CC2500 calibration data registers.
 */
typedef CC1101RFCalibration CC2500RFCalibration;

/**
 *  CC1101RFPower
 *
 *  @brief Represents a CC2500 power table.
 */
typedef CC1101RFPowerSettings CC2500RFPowerSettings;

#endif  // __RADIO_CCXXX_CC1101_H
