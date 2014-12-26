/**
 *  @file CC110L.h
 *
 *  @brief CC110L model register definitions.
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup
 */
#ifndef __DRIVERS_RADIO_CCXXX_CC110L_H
#define __DRIVERS_RADIO_CCXXX_CC110L_H

/**
 *  CC110LRFSettings
 *
 *  @brief Represents all configuration registers for CC110L excluding the PA Table.
 */
typedef struct CC110LRFSettings
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
  unsigned char reserved1;              // NOTE: Was previously the CC1101 channr register.
  unsigned char fsctrl1;                // Frequency synthesizer control.
  unsigned char fsctrl0;                // Frequency synthesizer control.
  unsigned char freq2;                  // Frequency control word, high byte.
  unsigned char freq1;                  // Frequency control word, middle byte.
  unsigned char freq0;                  // Frequency control word, low byte.
  unsigned char mdmcfg4;                // Modem configuration.
  unsigned char mdmcfg3;                // Modem configuration.
  unsigned char mdmcfg2;                // Modem configuration.
  unsigned char mdmcfg1;                // Modem configuration.
  unsigned char notused1;               // NOTE: Was previously the CC1101 mdmcfg0 register.
  unsigned char deviatn;                // Modem deviation setting (when FSK modulation is enabled).
  unsigned char mcsm2;                  // Main Radio Control State Machine configuration.
  unsigned char mcsm1;                  // Main Radio Control State Machine configuration.
  unsigned char mcsm0;                  // Main Radio Control State Machine configuration.
  unsigned char foccfg;                 // Frequency Offset Compensation Configuration.
  unsigned char bscfg;                  // Bit synchronization Configuration.
  unsigned char agcctrl2;               // AGC control.
  unsigned char agcctrl1;               // AGC control.
  unsigned char agcctrl0;               // AGC control.
  unsigned char notused2;               // NOTE: Was previously the CC1101 worevt1 register.
  unsigned char notused3;               // NOTE: Was previously the CC1101 worevt0 register.
  unsigned char reserved2;              // NOTE: Was previously the CC1101 worctrl1 register.
  unsigned char frend1;                 // Front end RX configuration.
  unsigned char frend0;                 // Front end RX configuration.
  unsigned char fscal3;                 // Frequency synthesizer calibration.
  unsigned char fscal2;                 // Frequency synthesizer calibration.
  unsigned char fscal1;                 // Frequency synthesizer calibration.
  unsigned char fscal0;                 // Frequency synthesizer calibration.
  unsigned char notused4;               // NOTE: Was previously the CC1101 rcctrl1 register.
  unsigned char notused5;               // NOTE: Was previously the CC1101 rcctrl0 register.
  unsigned char reserved3;              // NOTE: Was previously the CC1101 fstest register.
  unsigned char reserved4;              // NOTE: Was previously the CC1101 ptest register.
  unsigned char reserved5;              // NOTE: Was previously the CC1101 agctest register.
  unsigned char test2;                  // Various test settings.
  unsigned char test1;                  // Various test settings.
  unsigned char test0;                  // Various test settings.
} CC110LRFSettings;

/**
 *  CC1101RFChannel
 *
 *  @brief Represents a CC110L channel.
 */
typedef struct CC110LRFChannel
{
  unsigned char freq2;                  // Frequency control word, high byte.
  unsigned char freq1;                  // Frequency control word, middle byte.
  unsigned char freq0;                  // Frequency control word, low byte.
} CC110LRFChannel;

/**
 *  CC110LRFCalibration
 *
 *  @brief Represents calibration data registers.
 */
typedef struct CC110LRFCalibration
{
  unsigned char fscal3;                 // Frequency synthesizer calibration.
  unsigned char fscal2;                 // Frequency synthesizer calibration.
  unsigned char fscal1;                 // Frequency synthesizer calibration.
  unsigned char fscal0;                 // Frequency synthesizer calibration.
} CC110LRFCalibration;


/**
 *  CC110LRFPowerSettings
 *
 *  @brief Represents a CC110L power table.
 */
typedef struct CC110LRFPowerSettings
{
  unsigned char patable[2];             // Output power table.
} CC110LRFPowerSettings;

#endif  // __DRIVERS_RADIO_CCXXX_CC110L_H
