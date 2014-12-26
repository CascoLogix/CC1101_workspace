/**
 *  @file CC1101.h
 *
 *  @brief CC1101 model register definitions.
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup
 */
#ifndef __DRIVERS_RADIO_CCXXX_CC1101_H
#define __DRIVERS_RADIO_CCXXX_CC1101_H

/**
 *  CC1101RFSettings
 *
 *  @brief
 */
typedef struct CC1101RFSettings
{
  unsigned char iocfg2;                 // GDO2 output pin configuration.
  unsigned char iocfg1;                 // GDO1 output pin configuration.
  unsigned char iocfg0;                 // GDO0 output pin configuration.
  unsigned char fifothr;                // RXFIFO and TXFIFO thresholds.
  unsigned char sync1;                  // Sync word, high byte
  unsigned char sync0;                  // Sync word, low byte
  unsigned char pktlen;                 // Packet length.  
  unsigned char pktctrl1;               // Packet automation control.
  unsigned char pktctrl0;               // Packet automation control.
  unsigned char addr;                   // Device address.
  unsigned char channr;                 // Channel number.
  unsigned char fsctrl1;                // Frequency synthesizer control.
  unsigned char fsctrl0;                // Frequency synthesizer control.
  unsigned char freq2;                  // Frequency control word, high byte.
  unsigned char freq1;                  // Frequency control word, middle byte.
  unsigned char freq0;                  // Frequency control word, low byte.
  unsigned char mdmcfg4;                // Modem configuration.
  unsigned char mdmcfg3;                // Modem configuration.
  unsigned char mdmcfg2;                // Modem configuration.
  unsigned char mdmcfg1;                // Modem configuration.
  unsigned char mdmcfg0;                // Modem configuration.
  unsigned char deviatn;                // Modem deviation setting (when FSK modulation is enabled).
  unsigned char mcsm2;                  // Main Radio Control State Machine configuration.
  unsigned char mcsm1;                  // Main Radio Control State Machine configuration.
  unsigned char mcsm0;                  // Main Radio Control State Machine configuration.
  unsigned char foccfg;                 // Frequency Offset Compensation Configuration.
  unsigned char bscfg;                  // Bit synchronization Configuration.
  unsigned char agcctrl2;               // AGC control.
  unsigned char agcctrl1;               // AGC control.
  unsigned char agcctrl0;               // AGC control.
  unsigned char worevt1;                // High byte Event 0 timeout
  unsigned char worevt0;                // Low byte Event 0 timeout
  unsigned char worctrl;                // Wake On Radio control
  unsigned char frend1;                 // Front end RX configuration.
  unsigned char frend0;                 // Front end RX configuration.
  unsigned char fscal3;                 // Frequency synthesizer calibration.
  unsigned char fscal2;                 // Frequency synthesizer calibration.
  unsigned char fscal1;                 // Frequency synthesizer calibration.
  unsigned char fscal0;                 // Frequency synthesizer calibration.
  unsigned char rcctrl1;                // RC oscillator configuration
  unsigned char rcctrl0;                // RC oscillator configuration  
  unsigned char fstest;                 // Frequency synthesizer calibration control
  unsigned char ptest;                  // Production test
  unsigned char agctest;                // AGC test
  unsigned char test2;                  // Various test settings.
  unsigned char test1;                  // Various test settings.
  unsigned char test0;                  // Various test settings.
} CC1101RFSettings;

/**
 *  CC1101RFChannel
 *
 *  @brief Represents a CC1101 channel.
 */
typedef struct CC1101RFChannel
{
  unsigned char channr;                 // Channel number.
} CC1101RFChannel;

/**
 *  CC1101RFCalibration
 *
 *  @brief Represents calibration data registers.
 */
typedef struct CC1101RFCalibration
{
  unsigned char fscal3;                 // Frequency synthesizer calibration.
  unsigned char fscal2;                 // Frequency synthesizer calibration.
  unsigned char fscal1;                 // Frequency synthesizer calibration.
  unsigned char fscal0;                 // Frequency synthesizer calibration.
} CC1101RFCalibration;


/**
 *  CC1101RFPower
 *
 *  @brief Represents a CC1101 power table.
 */
typedef struct CC1101RFPowerSettings
{
  unsigned char patable[8];             // Output power table.
} CC1101RFPowerSettings;

#endif  // __DRIVERS_RADIO_CCXXX_CC1101_H
