/**
 *  @file Radio.h
 *
 *  @brief Chipcon (CCXXX) radio public interface prototype definitions. Requires 
 *  RadioInterface.h to function.
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup
 */
#ifndef __DRIVERS_RADIO_H
#define __DRIVERS_RADIO_H

#include "RadioStruct.h"

#if defined(__RADIO_CCXXX_SERIES)
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
    #include "CCXXX/Interface/CC1101Interface.h"
  #endif
#endif

/**
 *  @fn   RadioBufferWriteRegister
 */
void RadioBufferWriteRegister(Radio * pRadio, unsigned char addr, unsigned char * pBuffer, unsigned char count);

/**
 *  @fn   RadioWriteRegister
 */
void RadioWriteRegister(Radio * pRadio, unsigned char addr, unsigned char value);

/**
 *  @fn   RadioBufferReadRegister
 */
void RadioBufferReadRegister(Radio * pRadio, unsigned char addr, unsigned char * pBuffer, unsigned char count);

/**
 *  @fn   RadioReadRegister
 */
unsigned char RadioReadRegister(Radio * pRadio, unsigned char addr);

/**
 *  @fn   RadioPowerOnReset
 */
unsigned char RadioPowerOnReset(Radio * pRadio);

/**
 *  @fn   RadioWakeUp
 */
void RadioWakeUp(Radio * pRadio, RadioSettings * pRadioSettings, RadioPower * pRadioPower);

/**
 *  @fn   RadioSleep
 */
void RadioSleep(Radio * pRadio);

/**
 *  @fn   RadioConfigure
 */
void RadioConfigure(Radio * pRadio);

/**
 *  @fn   RadioUpdateSettings
 */
void RadioUpdateSettings(Radio * pRadio, RadioSettings * pRadioSettings, RadioChannel * pRadioChannel, RadioPower * pRadioPower);

/**
 *  @fn   RadioChangeSettings
 */
void RadioChangeSettings(Radio * pRadio, RadioSettings * pRadioSettings);

/**
 *  @fn   RadioChangeChannel
 */
void RadioChangeChannel(Radio * pRadio, RadioChannel * pRadioChannel);

/**
 *  @fn   RadioChangePower
 */
void RadioChangePower(Radio * pRadio, RadioPower * pRadioPower);

/**
 *  @fn   RadioIdle
 */
void RadioIdle(Radio * pRadio);

/**
 *  @fn   RadioTransmit
 */
void RadioTransmit(Radio * pRadio);

/**
 *  @fn   RadioReceive
 */
void RadioReceive(Radio * pRadio);

/**
 *  @fn   RadioWriteTXBuffer
 */
void RadioWriteTXBuffer(Radio * pRadio, unsigned char * pBuffer, unsigned char count);

/**
 *  @fn   RadioReadRXBuffer
 */
void RadioReadRXBuffer(Radio * pRadio, unsigned char * pBuffer, unsigned char count);

/**
 *  @fn     RadioFlushTXBuffer
 *
 *  @brief  Empty any data in the transmit (TX) buffer. This buffer may either
 *          be done in hardware (if available), or in software.
 */
void RadioFlushTXBuffer(Radio * pRadio);

/**
 *  @fn     RadioFlushRXBuffer
 *
 *  @brief  Empty any data in the receive (RX) buffer. This buffer may either
 *          be done in hardware (if available), or in software.
 */
void RadioFlushRXBuffer(Radio * pRadio);

/**
 *  @fn     RadioEnableInterrupt
 */
void RadioEnableInterrupt(Radio * pRadio, unsigned char interruptId);

/**
 *  @fn     RadioDisableInterrupt
 */
void RadioDisableInterrupt(Radio * pRadio, unsigned char interruptId);

/**
 *  @fn     RadioSetInterruptEdge
 */
void RadioSetInterruptEdge(Radio * pRadio, unsigned char interruptId, unsigned char edge);

#endif  // __DRIVERS_RADIO_H
