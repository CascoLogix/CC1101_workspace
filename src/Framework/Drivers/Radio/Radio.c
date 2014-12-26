/**
 *  @file   Radio.c
 */
#include "../../BSP/BoardDrivers.h"

#if defined(__RADIO_CCXXX_SERIES)

#include "Radio.h"

/**
 *  @fn   RadioBufferWriteRegister
 */
void RadioBufferWriteRegister(Radio * pRadio, unsigned char addr, unsigned char * pBuffer, unsigned char count)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    CC1101Write(pRadio, addr, pBuffer, count); 
  }
  #endif
}

/**
 *  @fn   RadioWriteRegister
 */
void RadioWriteRegister(Radio * pRadio, unsigned char addr, unsigned char value)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    CC1101Write(pRadio, addr, &value, 1);
  }
  #endif
}

/**
 *  @fn   RadioBufferReadRegister
 */
void RadioBufferReadRegister(Radio * pRadio, unsigned char addr, unsigned char * pBuffer, unsigned char count)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    CC1101Read(pRadio, addr, pBuffer, count); 
  }
  #endif
}

/**
 *  @fn   RadioReadRegister
 */
unsigned char RadioReadRegister(Radio * pRadio, unsigned char addr)
{
  unsigned char tempBuffer = 0x00;   // Temporary variable of size 1 to emulate a buffer.
  
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    CC1101Read(pRadio, addr, &tempBuffer, 1);
    return tempBuffer; 
  }
  #endif
  
  return 0;
}

/**
 *  @fn   RadioPowerOnReset
 */
unsigned char RadioPowerOnReset(Radio * pRadio)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    return CC1101PowerOnReset(pRadio); 
  }
  #endif
  
  return 0;
}

/**
 *  @fn   RadioWakeUp
 */
void RadioWakeUp(Radio * pRadio, RadioSettings * pRadioSettings, RadioPower * pRadioPower)
{
  // Set the radio state to configured.
  pRadio->radioState = RADIO_CONFIGURED;
  
  // Wake up the from a low power state.
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    CC1101WakeUp(pRadio, pRadioSettings, pRadioPower); 
  }
  #endif
}

/**
 *  @fn   RadioSleep
 */
void RadioSleep(Radio * pRadio)
{
  pRadio->radioState = RADIO_SLEEP;
  
  // Put the radio to a low power operation state.
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    CC1101Sleep(pRadio); 
  }
  #endif
}

/**
 *  @fn   RadioConfigure
 */
void RadioConfigure(Radio * pRadio)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    CC1101Configure(pRadio->index);
  }
  #endif
}

/**
 *  @fn   RadioUpdateSettings
 */
void RadioUpdateSettings(Radio * pRadio, RadioSettings * pRadioSettings, RadioChannel * pRadioChannel, RadioPower * pRadioPower)
{
  // Configure radio settings, channel, and power.
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    CC1101UpdateSettings(pRadio, pRadioSettings, pRadioChannel, pRadioPower);
  }
  #endif
  
  pRadio->radioState = RADIO_CONFIGURED;
}

/**
 *  @fn   RadioChangeSettings
 */
void RadioChangeSettings(Radio * pRadio, RadioSettings * pRadioSettings)
{
  // TODO: Define implementation for changing settings only. 
}

/**
 *  @fn   RadioChangeChannel
 */
void RadioChangeChannel(Radio * pRadio, RadioChannel * pRadioChannel)
{
  #if defined(__RADIO_CCXXX_CC1101)
  if (pRadio->model == CC1101)
  {
    // Write channel register.
    CC1101Write(pRadio, CCXXX_REG_CHANNR, (unsigned char *)&pRadioChannel->channel.cc1101.channr, 1);
  }
  #endif
  
  #if defined(__RADIO_CCXXX_CC2500)
  if (pRadio->model == CC2500)
  {    
    // Write channel register.
    CC1101Write(pRadio, CCXXX_REG_CHANNR, (unsigned char *)&pRadioChannel->channel.cc2500.channr, 1);
  }
  #endif
  
  #if defined(__RADIO_CCXXX_CC110L)
  if (pRadio->model == CC110L)
  {
    // Write frequency registers to change CC110L channel.
    CC1101Write(pRadio, CCXXX_REG_FREQ2, (unsigned char *)&pRadioChannel->channel.cc110L.freq2, 1);
    CC1101Write(pRadio, CCXXX_REG_FREQ1, (unsigned char *)&pRadioChannel->channel.cc110L.freq1, 1);
    CC1101Write(pRadio, CCXXX_REG_FREQ0, (unsigned char *)&pRadioChannel->channel.cc110L.freq0, 1);
  }
  #endif
}

/**
 *  @fn   RadioChangePower
 */
void RadioChangePower(Radio * pRadio, RadioPower * pRadioPower)
{
  #if defined(__RADIO_CCXXX_CC1101)
  if (pRadio->model == CC1101)
  {
    // Update CC1101 power settings register.
    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->power.cc1101.patable));
  }
  #endif
      
  #if defined(__RADIO_CCXXX_CC2500)
  if (pRadio->model == CC2500)
  {
    // Update CC2500 power settings register.
    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->power.cc2500.patable));
  }
  #endif
    
  #if defined(__RADIO_CCXXX_CC110L)
  if (pRadio->model != CC110L)
  {
    // Update CC110L power settings register.
    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->power.cc110L.patable));
  }
  #endif
}

/**
 *  @fn   RadioIdle
 */
void RadioIdle(Radio * pRadio)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    RadioWriteRegister(pRadio, CCXXX_STRB_SIDLE, 0);
  }
  #endif
}

/**
 *  @fn   RadioTransmit
 */
void RadioTransmit(Radio * pRadio)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    RadioWriteRegister(pRadio, CCXXX_STRB_STX, 0);
  }
  #endif
}

/**
 *  @fn   RadioReceive
 */
void RadioReceive(Radio * pRadio)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    RadioWriteRegister(pRadio, CCXXX_STRB_SRX, 0);
  }
  #endif
}

/**
 *  @fn   RadioWriteTXBuffer
 */
void RadioWriteTXBuffer(Radio * pRadio, unsigned char * pBuffer, unsigned char count)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    CC1101Write(pRadio, CCXXX_REG_TXFIFO, pBuffer, count);
  }
  #endif
}

/**
 *  @fn   RadioReadRXBuffer
 */
void RadioReadRXBuffer(Radio * pRadio, unsigned char * pBuffer, unsigned char count)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    CC1101Read(pRadio, CCXXX_REG_RXFIFO, pBuffer, count);
  }
  #endif
}

/**
 *  @fn     RadioFlushTXBuffer
 *
 *  @brief  Empty any data in the transmit (TX) buffer. This buffer may either
 *          be done in hardware (if available), or in software.
 */
void RadioFlushTXBuffer(Radio * pRadio)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    RadioWriteRegister(pRadio, CCXXX_STRB_SFTX, 0);
  }
  #endif
}

/**
 *  @fn     RadioFlushRXBuffer
 *
 *  @brief  Empty any data in the receive (RX) buffer. This buffer may either
 *          be done in hardware (if available), or in software.
 */
void RadioFlushRXBuffer(Radio * pRadio)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    RadioWriteRegister(pRadio, CCXXX_STRB_SFRX, 0);
  }
  #endif
}

/**
 *  @fn     RadioEnableInterrupt
 */
void RadioEnableInterrupt(Radio * pRadio, unsigned char interruptId)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    // GDO0
    if (interruptId == 0)
    {
      CC1101EnableGDO0Interrupt(pRadio->index);
    }
    // GDO2
    else if (interruptId == 2)
    {
      CC1101EnableGDO2Interrupt(pRadio->index);
    }
  }
  #endif
}

/**
 *  @fn     RadioDisableInterrupt
 */
void RadioDisableInterrupt(Radio * pRadio, unsigned char interruptId)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    // GDO0
    if (interruptId == 0)
    {
      CC1101DisableGDO0Interrupt(pRadio->index);
    }
    // GDO2
    else if (interruptId == 2)
    {
      CC1101DisableGDO2Interrupt(pRadio->index);
    }
  }
  #endif
}

/**
 *  @fn     RadioSetInterruptEdge
 */
void RadioSetInterruptEdge(Radio * pRadio, unsigned char interruptId, unsigned char edge)
{
  #if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)
  if ((pRadio->model == CC1101) || (pRadio->model == CC110L) || (pRadio->model == CC2500))
  {
    // GDO0
    if (interruptId == 0)
    {
      CC1101GDO0EdgeSelect(pRadio->index, edge);
    }
    // GDO2
    else if (interruptId == 2)
    {
      CC1101GDO2EdgeSelect(pRadio->index, edge);
    }
  }
  #endif
}

#endif
