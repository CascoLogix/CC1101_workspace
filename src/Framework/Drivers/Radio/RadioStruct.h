#ifndef __DRIVERS_RADIO_STRUCT_H
#define __DRIVERS_RADIO_STRUCT_H

//#define __RADIO_CCXXX_CC1101
//#define __RADIO_CCXXX_CC110L
//#define __RADIO_CCXXX_CC2500

#if defined(__RADIO_CCXXX_SERIES)
  #include "CCXXX/CCXXXConfig.h"

  // Include correct Radio header files.
  #ifdef __RADIO_CCXXX_CC1101
    #include "CCXXX/Model/CC1101.h"
  #endif
  #ifdef __RADIO_CCXXX_CC110L
    #include "CCXXX/Model/CC110L.h"
  #endif
  #ifdef __RADIO_CCXXX_CC2500
    #include "CCXXX/Model/CC2500.h"
  #endif
#endif

//#include "HAL/HAL.h"

/**
 *  Radio Connection
 *
 *  @brief Represents how a radio is connected to the microcontroller.
 */
typedef const struct RadioConnection
{
  enum PERIPHERAL peripheral;               // Peripheral defined in MCU model
  SPIConnection * pConnection;              // SPI connection definition
} RadioConnection;

/**
 *  Radio Settings
 *
 *  @brief Represents all registers for a specific radio.
 */
typedef const struct RadioSettings
{
  union                    			// Radio configuration register settings
  {
    #ifdef __RADIO_CCXXX_CC1101
      CC1101RFSettings cc1101;      // CC1101 configuration registers definition
    #endif
    #ifdef __RADIO_CCXXX_CC110L
      CC110LRFSettings cc110L;      // CC110L configuration registers definition
    #endif
    #ifdef __RADIO_CCXXX_CC2500
      CC2500RFSettings cc2500;      // CC2500 configuration registers definition
    #endif
  } settings;
} RadioSettings;

/**
 *  Radio Calibration
 *
 *  @brief Represents the registers used for calibration.
 */
typedef struct RadioCalibration
{
  union
  {
    #ifdef __RADIO_CCXXX_CC1101
      CC1101RFCalibration cc1101;   // CC1101 calibration data definition
    #endif
    #ifdef __RADIO_CCXXX_CC110L
      CC110LRFCalibration cc110L;   // CC110L calibration data definition
    #endif
    #ifdef __RADIO_CCXXX_CC2500
      CC2500RFCalibration cc2500;   // CC2500 calibration data definition
    #endif
  } calibration;
} RadioCalibration;

/**
 *  Radio Power
 *
 *  @brief Represents the registers for the PA table.
 */
typedef const struct RadioPower
{
  union
  {
    #ifdef __RADIO_CCXXX_CC1101
      CC1101RFPowerSettings cc1101;   // CC1101 power table definition
    #endif
    #ifdef __RADIO_CCXXX_CC110L
      CC110LRFPowerSettings cc110L;   // CC110L power table definition
    #endif
    #ifdef __RADIO_CCXXX_CC2500
      CC2500RFPowerSettings cc2500;   // CC2500 power table definition
    #endif
  } power;
} RadioPower;

/**
 *  RF Channel
 *
 *  @brief Represents the registers used for channels.
 */
typedef const struct RadioChannel
{
  union
  {
    #ifdef __RADIO_CCXXX_CC1101
      CC1101RFChannel cc1101;       // CC1101 channel definition
    #endif
    #ifdef __RADIO_CCXXX_CC110L
      CC110LRFChannel cc110L;       // CC110L channel definition
    #endif
    #ifdef __RADIO_CCXXX_CC2500
      CC2500RFChannel cc2500;       // CC2500 channel definition
    #endif
  } channel;
} RadioChannel;

/**
 *  Radio
 *
 *  @brief Represents the current state information for a specific radio.
 */
typedef struct Radio
{
  unsigned char index;
  enum RADIO_MODEL                                
  {
    CC1101,                                 // Radio is a CC1101
    CC110L,                                 // Radio is a CC110L
    CC2500                                  // Radio is a CC2500
  } model;                                  // Radio model
  volatile enum RADIO_STATE
  {
    RADIO_OFF         = 0,                  // Radio is turned off
    RADIO_ON          = BIT0,               // Radio is turned on
    RADIO_SLEEP       = BIT1,               // Radio is sleeping
    RADIO_CONFIGURED  = BIT2,               // Radio is configured
    RADIO_CALIBRATED  = BIT3,               // Radio is calibrated
    RADIO_RECEIVE     = BIT4,               // Radio is receiving
    RADIO_TRANSMIT    = BIT5                // Radio is transmitting
  } radioState;                             // Radio state
  RadioConnection * pRadioConnection;       // Radio connection definitions
} Radio;

#endif
