#include "CC1101Interface.h"

#if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)

/**
 *  @fn CC1101Write
 */
void CC1101Write(Radio * pRadio, unsigned char address, unsigned char * pBuffer, unsigned char count)
{
  unsigned char command;

  // Check if this is a Strobe command.
  if (address > 0x2F && address < 0x3E)
  {
    // If so, there is no data associated with this command - clear data count.
    count = 0; 
  }

  // Format command (R/W, Burst/Single, Address[5:0]).
  if (count < 2)
  {
    // Single write.
    command = address & 0x3F;
  }
  else
  {
    // Burst write.
    command = (address & 0x3F) | CCXXX_WRITE_BURST;
  }

  // Perform an external SPI write to the radio.
  __BSP_SPI_BURST_WRITE(__BSP_RADIO_GET_SPI_ID(pRadio->index), command, pBuffer, count);
//  __hal_SPIBurstWrite(radio->pRadioConnection->peripheral, radio->pRadioConnection->pSPI, command, pBuffer, count);
}

/**
 *  @fn CC1101Read
 */
unsigned char CC1101Read(Radio * pRadio, unsigned char addr, unsigned char * pBuffer, unsigned char count)
{
  unsigned char command;

  // Format command (R/W, Burst/Single, Address[5:0]).
  if (count < 2 && (addr <= 0x2F || addr > 0x3E))
  {
    // Single read.
    command = addr | CCXXX_READ_SINGLE;
  }
  else
  {
    // Burst read.
    command = addr | CCXXX_READ_BURST;
  }

  // Perform an external SPI read from the radio.
  __BSP_SPI_BURST_READ(__BSP_RADIO_GET_SPI_ID(pRadio->index), command, pBuffer, count);
//  __hal_SPIBurstRead(radio->pRadioConnection->peripheral, radio->pRadioConnection->pSPI, command, pBuffer, count);

  return 0;
}

/**
 *  @fn CC1101UpdateSettings
 */
void CC1101UpdateSettings(Radio * pRadio, RadioSettings * pRadioSettings, RadioChannel * pRadioChannel, RadioPower * pRadioPower)
{
  #if defined(__RADIO_CCXXX_CC1101)
  if (pRadio->model == CC1101)
  {
    // Write radio settings.
    CC1101Write(pRadio, CCXXX_REG_IOCFG2, (unsigned char *)pRadioSettings, sizeof(pRadioSettings->settings.cc1101));
      
    // Write radio channel.
    CC1101Write(pRadio, CCXXX_REG_CHANNR, (unsigned char *)pRadioChannel, sizeof(pRadioChannel->channel.cc1101));

    // Write radio PA table.
    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->power.cc1101));
  }
  #endif
  #if defined(__RADIO_CCXXX_CC110L)
  if (pRadio->model == CC110L)
  {
    // Write radio settings.
    CC1101Write(pRadio, CCXXX_REG_IOCFG2, (unsigned char *)pRadioSettings, sizeof(pRadioSettings->settings.cc110L));
      
    // Write radio channel.
    CC1101Write(pRadio, CCXXX_REG_FREQ2, (unsigned char *)pRadioChannel, sizeof(pRadioChannel->channel.cc110L));

    // Write radio PA table.
    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->power.cc110L));
  }
  #endif
  #if defined(__RADIO_CCXXX_CC2500)
  if (pRadio->model == CC2500)
  {
    // Write radio settings.
    CC1101Write(pRadio, CCXXX_REG_IOCFG2, (unsigned char *)pRadioSettings, sizeof(pRadioSettings->settings.cc2500));
      
    // Write radio channel.
    CC1101Write(pRadio, CCXXX_REG_CHANNR, (unsigned char *)pRadioChannel, sizeof(pRadioChannel->channel.cc2500));

    // Write radio PA table.
    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->power.cc2500));
  }
  #endif
}

/**
 *  @fn     CC1101PowerOnReset
 *
 *  @brief  Resets radio upon power up sequence.
 */
unsigned char CC1101PowerOnReset(Radio * pRadio)
{
  unsigned int i;
  
  // Enable SPI chip select.
  __hal_SPIEnableChipSelect(&pRadio->pRadioConnection->pConnection->csn);
  
  // Timeout period for operation.
  for(i = 0; i < 60000; i++)
  {
    // Look for MISO pin to go low.
    if (!(__BSP_SPI_MISO_PORT(pRadio->index) & __BSP_SPI_MISO_PIN(pRadio->index)))
    {
      // Reset the chip.
      CC1101Write(pRadio, CCXXX_STRB_SRES, NULL, 1);
      // Disable SPI chip select.
      __hal_SPIDisableChipSelect(&pRadio->pRadioConnection->pConnection->csn);
      // Operation has succeeded.
      return 1; 
    }
  }
  
  // Disable SPI chip select.
  __hal_SPIDisableChipSelect(&pRadio->pRadioConnection->pConnection->csn);
  
  // Operation has failed.
  return 0;
}

/**
 *  @fn   CC1101WakeUp
 */
void CC1101WakeUp(Radio * pRadio, RadioSettings * pRadioSettings, RadioPower * pRadioPower)
{
  volatile unsigned int Delay = 0;
  
  // Enable SPI chip select.
  __hal_SPIEnableChipSelect(&pRadio->pRadioConnection->pConnection->csn);

  // Wait until MISO goes low.
  while(__BSP_SPI_MISO_PORT(pRadio->index) & __BSP_SPI_MISO_PIN(pRadio->index)){
    Delay++;
    if(Delay == 0xFFFF)
      break;
  }
  
  // Perform a NOP write to radio.
  // This will turn on voltage regulator and crystal oscillator and will put the radio into IDLE. 
  CC1101Write(pRadio, CCXXX_STRB_SNOP, NULL, 1);
  
//  // NOTE: Not sure whether to wait before writing the configuration registers.
//  for (wakeUpDelay = 0; wakeUpDelay < 5000; wakeUpDelay++)
//  {
//    __no_operation();
//  }
  
  // Last valid calibration results are maintained so that calibration is still valid after waking
  // up from SLEEP. TX/RX FIFOs are flushed. If IOCFGx.GDOx_CFG setting is less that 0x20 and 
  // IOCFGx.GDOx_INV is 0(1), GDO0 and GDO2 pines are hardwired to 0(1), and GDO1 is hardwired to 
  // 1(0), until CSn goes low.
  // Need to rewrite the following registers:
  // AGCTEST, TEST2, TEST1, TEST0, PATABLE(contents of PATABLE are lost except the first byte(index 0))
  #if defined(__RADIO_CCXXX_CC1101)
  if (pRadio->model == CC1101)
  {
    // Write radio settings.
    CC1101Write(pRadio, CCXXX_REG_AGCTEST, (unsigned char *)(&(pRadioSettings->settings.cc1101.iocfg2) + CCXXX_REG_AGCTEST), 1);
    CC1101Write(pRadio, CCXXX_REG_TEST2, (unsigned char *)(&(pRadioSettings->settings.cc1101.iocfg2) + CCXXX_REG_TEST2), 1);
    CC1101Write(pRadio, CCXXX_REG_TEST1, (unsigned char *)(&(pRadioSettings->settings.cc1101.iocfg2) + CCXXX_REG_TEST1), 1);
    CC1101Write(pRadio, CCXXX_REG_TEST0, (unsigned char *)(&(pRadioSettings->settings.cc1101.iocfg2) + CCXXX_REG_TEST0), 1);
      
    // Write radio PA table.
    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->power.cc1101));
  }
  #endif
  #if defined(__RADIO_CCXXX_CC110L)
  if (pRadio->model == CC110L)
  {
    // Write radio settings.
    CC1101Write(pRadio, CCXXX_REG_AGCTEST, (unsigned char *)(&(pRadioSettings->settings.cc110L.iocfg2) + CCXXX_REG_AGCTEST), 1);
    CC1101Write(pRadio, CCXXX_REG_TEST2, (unsigned char *)(&(pRadioSettings->settings.cc110L.iocfg2) + CCXXX_REG_TEST2), 1);
    CC1101Write(pRadio, CCXXX_REG_TEST1, (unsigned char *)(&(pRadioSettings->settings.cc110L.iocfg2) + CCXXX_REG_TEST1), 1);
    CC1101Write(pRadio, CCXXX_REG_TEST0, (unsigned char *)(&(pRadioSettings->settings.cc110L.iocfg2) + CCXXX_REG_TEST0), 1);
      
    // Write radio PA table.
    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->power.cc110L));
  }
  #endif
  #if defined(__RADIO_CCXXX_CC2500)  
  if (pRadio->model == CC2500)
  {
    // Write radio settings.
    CC1101Write(pRadio, CCXXX_REG_AGCTEST, (unsigned char *)(&(pRadioSettings->settings.cc2500.iocfg2) + CCXXX_REG_AGCTEST), 1);
    CC1101Write(pRadio, CCXXX_REG_TEST2, (unsigned char *)(&(pRadioSettings->settings.cc2500.iocfg2) + CCXXX_REG_TEST2), 1);
    CC1101Write(pRadio, CCXXX_REG_TEST1, (unsigned char *)(&(pRadioSettings->settings.cc2500.iocfg2) + CCXXX_REG_TEST1), 1);
    CC1101Write(pRadio, CCXXX_REG_TEST0, (unsigned char *)(&(pRadioSettings->settings.cc2500.iocfg2) + CCXXX_REG_TEST0), 1);
      
    // Write radio PA table.
    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->power.cc2500));
  }
  #endif
}

/**
 *  @fn CC1101Sleep
 */
void CC1101Sleep(Radio * pRadio)
{
  // Strobe SPWD register for SLEEP operation.
  CC1101Write(pRadio, CCXXX_STRB_SPWD, NULL, 0);
}

/**
 *  @fn   CC1101EnableGDO0Interrupt
 */
void CC1101EnableGDO0Interrupt(unsigned char radioId)
{
  #if defined(__BSP_RADIO_ENABLE_GDO0_INTERRUPT)
  __BSP_RADIO_ENABLE_GDO0_INTERRUPT(radioId);
  #endif
}

/**
 *  @fn   CC1101DisableGDO0Interrupt
 */
void CC1101DisableGDO0Interrupt(unsigned char radioId)
{
  #if defined(__BSP_RADIO_DISABLE_GDO0_INTERRUPT)
  __BSP_RADIO_DISABLE_GDO0_INTERRUPT(radioId);
  #endif
}

/**
 *  @fn   CC1101EnableGDO2Interrupt
 */
void CC1101EnableGDO2Interrupt(unsigned char radioId)
{
  #if defined(__BSP_RADIO_ENABLE_GDO2_INTERRUPT)
  __BSP_RADIO_ENABLE_GDO2_INTERRUPT(radioId);
  #endif
}

/**
 *  @fn   CC1101DisableGDO2Interrupt
 */
void CC1101DisableGDO2Interrupt(unsigned char radioId)
{
  #if defined(__BSP_RADIO_DISABLE_GDO2_INTERRUPT)
  __BSP_RADIO_DISABLE_GDO2_INTERRUPT(radioId);
  #endif
}

#endif
