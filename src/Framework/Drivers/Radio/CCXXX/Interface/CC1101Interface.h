/**
 *  @file CC1101Interface.h
 *
 *  @brief CC1101 radio interface prototype definitions.
 *
 *  @see RadioInterface.h
 *
 *  @version  1.0
 *
 *  @remarks  Rev. 1.0, Initial setup
 */
#ifndef __RADIO_CC1101INTERFACE_H
#define __RADIO_CC1101INTERFACE_H

///**
// *  @fn   CC1101Configure
// */
//#define CC1101Configure(radioId)            __BSP_RADIO_CONFIGURE(radioId)
//
///**
// *  @fn CC1101Write
// */
//#pragma inline
//void CC1101Write(Radio * radio, unsigned char address, unsigned char * pBuffer, unsigned char count)
//{
//  unsigned char command;
//
//  // Check if this is a Strobe command.
//  if (address > 0x2F && address < 0x3E)
//  {
//    // If so, there is no data associated with this command - clear data count.
//    count = 0; 
//  }
//
//  // Format command (R/W, Burst/Single, Address[5:0]).
//  if (count < 2)
//  {
//    // Single write.
//    command = address & 0x3F;
//  }
//  else
//  {
//    // Burst write.
//    command = (address & 0x3F) | CCXXX_WRITE_BURST;
//  }
//
//  // Perform an external SPI write to the radio.
//  SPIBurstWrite(__BSP_SPI1, command, pBuffer, count);
////  __hal_SPIBurstWrite(radio->pRadioConnection->peripheral, radio->pRadioConnection->pSPI, command, pBuffer, count);
//}
//
///**
// *  @fn CC1101Read
// */
//#pragma inline
//unsigned char CC1101Read(Radio * radio, unsigned char addr, unsigned char * pBuffer, unsigned char count)
//{
//  unsigned char command;
//
//  // Format command (R/W, Burst/Single, Address[5:0]).
//  if (count < 2 && (addr <= 0x2F || addr > 0x3E))
//  {
//    // Single read.
//    command = addr | CCXXX_READ_SINGLE;
//  }
//  else
//  {
//    // Burst read.
//    command = addr | CCXXX_READ_BURST;
//  }
//
//  // Perform an external SPI read from the radio.
//  __hal_SPIBurstRead(radio->pRadioConnection->peripheral, radio->pRadioConnection->pSPI, command, pBuffer, count);
//
//  return 0;
//}
//
///**
// *  @fn CC1101UpdateSettings
// */
//#pragma inline
//void CC1101UpdateSettings(Radio * pRadio, RadioSettings * pRadioSettings, RadioChannel * pRadioChannel, RadioPower * pRadioPower)
//{
//  #if defined(__RADIO_CCXXX_CC1101)
//  if (pRadio->model == CC1101)
//  {
//    // Write radio settings.
//    CC1101Write(pRadio, CCXXX_REG_IOCFG2, (unsigned char *)pRadioSettings, sizeof(pRadioSettings->cc1101));
//      
//    // Write radio channel.
//    CC1101Write(pRadio, CCXXX_REG_CHANNR, (unsigned char *)pRadioChannel, sizeof(pRadioChannel->cc1101));
//
//    // Write radio PA table.
//    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->cc1101));
//  }
//  #endif
//  #if defined(__RADIO_CCXXX_CC110L)
//  if (pRadio->model == CC110L)
//  {
//    // Write radio settings.
//    CC1101Write(pRadio, CCXXX_REG_IOCFG2, (unsigned char *)pRadioSettings, sizeof(pRadioSettings->cc110L));
//      
//    // Write radio channel.
//    CC1101Write(pRadio, CCXXX_REG_FREQ2, (unsigned char *)pRadioChannel, sizeof(pRadioChannel->cc110L));
//
//    // Write radio PA table.
//    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->cc110L));
//  }
//  #endif
//  #if defined(__RADIO_CCXXX_CC2500)
//  if (pRadio->model == CC2500)
//  {
//    // Write radio settings.
//    CC1101Write(pRadio, CCXXX_REG_IOCFG2, (unsigned char *)pRadio->pRadioSettings, sizeof(pRadio->pRadioSettings->cc2500));
//      
//    // Write radio channel.
//    CC1101Write(pRadio, CCXXX_REG_CHANNR, (unsigned char *)pRadio->pRadioChannel, sizeof(pRadio->pRadioChannel->cc2500));
//
//    // Write radio PA table.
//    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadio->pRadioPower, sizeof(pRadio->pRadioPower->cc2500));
//  }
//  #endif
//}
//
///**
// *  @fn     CC1101PowerOnReset
// *
// *  @brief  Resets radio upon power up sequence.
// */
//#pragma inline
//unsigned char CC1101PowerOnReset(Radio * pRadio)
//{
//  // Enable SPI chip select.
//  __hal_SPIEnableChipSelect(&pRadio->pRadioConnection->pSPI->csn);
//  
//  // Timeout period for operation.
//  for(unsigned int i = 0; i < 60000; i++)
//  {
//    // Look for MISO pin to go low.
//    if (!(__BSP_SPI_MISO_PORT(pRadio->index) & __BSP_SPI_MISO_PIN(pRadio->index)))
//    {
//      // Reset the chip.
//      CC1101Write(pRadio, CCXXX_STRB_SRES, NULL, 1);
//      // Disable SPI chip select.
//      __hal_SPIDisableChipSelect(&pRadio->pRadioConnection->pSPI->csn);
//      // Operation has succeeded.
//      return 1; 
//    }
//  }
//  
//  // Disable SPI chip select.
//  __hal_SPIDisableChipSelect(&pRadio->pRadioConnection->pSPI->csn);
//  
//  // Operation has failed.
//  return 0;
//}
//
///**
// *  @fn   CC1101WakeUp
// */
//#pragma inline
//void CC1101WakeUp(Radio * pRadio, RadioSettings * pRadioSettings, RadioPower * pRadioPower)
//{
//  // Perform a NOP write to radio.
//  // This will turn on voltage regulator and crystal oscillator and will put the radio into IDLE. 
//  CC1101Write(pRadio, CCXXX_STRB_SNOP, NULL, 1);
//  
//  // NOTE: Not sure whether to wait before writing the configuration registers.
//  for (unsigned int wakeUpDelay = 0; wakeUpDelay < 5000; wakeUpDelay++)
//  {
//    __no_operation();
//  }
//  
//  // Last valid calibration results are maintained so that calibration is still valid after waking
//  // up from SLEEP. TX/RX FIFOs are flushed. If IOCFGx.GDOx_CFG setting is less that 0x20 and 
//  // IOCFGx.GDOx_INV is 0(1), GDO0 and GDO2 pines are hardwired to 0(1), and GDO1 is hardwired to 
//  // 1(0), until CSn goes low.
//  // Need to rewrite the following registers:
//  // AGCTEST, TEST2, TEST1, TEST0, PATABLE(contents of PATABLE are lost except the first byte(index 0))
//  #if defined(__RADIO_CCXXX_CC1101)
//  if (pRadio->model == CC1101)
//  {
//    // Write radio settings.
//    CC1101Write(pRadio, CCXXX_REG_AGCTEST, (unsigned char *)(&(pRadioSettings->cc1101.iocfg2) + CCXXX_REG_AGCTEST), 1);
//    CC1101Write(pRadio, CCXXX_REG_TEST2, (unsigned char *)(&(pRadioSettings->cc1101.iocfg2) + CCXXX_REG_TEST2), 1);
//    CC1101Write(pRadio, CCXXX_REG_TEST1, (unsigned char *)(&(pRadioSettings->cc1101.iocfg2) + CCXXX_REG_TEST1), 1);
//    CC1101Write(pRadio, CCXXX_REG_TEST0, (unsigned char *)(&(pRadioSettings->cc1101.iocfg2) + CCXXX_REG_TEST0), 1);
//      
//    // Write radio PA table.
//    CC1101Write(radio, CCXXX_REG_PATABLE, (unsigned char *)radio->pRadioPower, sizeof(radio->pRadioPower->cc1101));
//  }
//  #endif
//  #if defined(__RADIO_CCXXX_CC110L)
//  if (pRadio->model == CC110L)
//  {
//    // Write radio settings.
//    CC1101Write(pRadio, CCXXX_REG_AGCTEST, (unsigned char *)(&(pRadioSettings->cc110L.iocfg2) + CCXXX_REG_AGCTEST), 1);
//    CC1101Write(pRadio, CCXXX_REG_TEST2, (unsigned char *)(&(pRadioSettings->cc110L.iocfg2) + CCXXX_REG_TEST2), 1);
//    CC1101Write(pRadio, CCXXX_REG_TEST1, (unsigned char *)(&(pRadioSettings->cc110L.iocfg2) + CCXXX_REG_TEST1), 1);
//    CC1101Write(pRadio, CCXXX_REG_TEST0, (unsigned char *)(&(pRadioSettings->cc110L.iocfg2) + CCXXX_REG_TEST0), 1);
//      
//    // Write radio PA table.
//    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->cc110L));
//  }
//  #endif
//  #if defined(__RADIO_CCXXX_CC2500)  
//  if (pRadio->model == CC2500)
//  {
//    // Write radio settings.
//    CC1101Write(pRadio, CCXXX_REG_AGCTEST, (unsigned char *)(&(pRadioSettings->cc2500.iocfg2) + CCXXX_REG_AGCTEST), 1);
//    CC1101Write(pRadio, CCXXX_REG_TEST2, (unsigned char *)(&(pRadioSettings->cc2500.iocfg2) + CCXXX_REG_TEST2), 1);
//    CC1101Write(pRadio, CCXXX_REG_TEST1, (unsigned char *)(&(pRadioSettings->cc2500.iocfg2) + CCXXX_REG_TEST1), 1);
//    CC1101Write(pRadio, CCXXX_REG_TEST0, (unsigned char *)(&(pRadioSettings->cc2500.iocfg2) + CCXXX_REG_TEST0), 1);
//      
//    // Write radio PA table.
//    CC1101Write(pRadio, CCXXX_REG_PATABLE, (unsigned char *)pRadioPower, sizeof(pRadioPower->cc2500));
//  }
//  #endif
//}
//
///**
// *  @fn CC1101Sleep
// */
//#pragma inline
//void CC1101Sleep(Radio * pRadio)
//{
//  // Strobe SPWD register for SLEEP operation.
//  CC1101Write(pRadio, CCXXX_STRB_SPWD, NULL, 0);
//}
//
///**
// *  @fn   CC1101EnableGDO0Interrupt
// */
//#pragma inline
//void CC1101EnableGDO0Interrupt(unsigned char radioId)
//{
//  #if defined(__BSP_RADIO_ENABLE_GDO0_INTERRUPT)
//  __BSP_RADIO_ENABLE_GDO0_INTERRUPT(radioId);
//  #endif
//}
//
///**
// *  @fn   CC1101DisableGDO0Interrupt
// */
//#pragma inline
//void CC1101DisableGDO0Interrupt(unsigned char radioId)
//{
//  #if defined(__BSP_RADIO_DISABLE_GDO0_INTERRUPT)
//  __BSP_RADIO_DISABLE_GDO0_INTERRUPT(radioId);
//  #endif
//}
//
///**
// *  @fn   CC1101GDO0EdgeSelect
// */
//#if defined(__BSP_RADIO_GDO0_INTERRUPT_EDGE)
//#define CC1101GDO0EdgeSelect(radioId, edge)       \
//{                                                 \
//  __BSP_RADIO_GDO0_INTERRUPT_EDGE(radioId, edge); \
//}
//#endif
//
///**
// *  @fn   CC1101EnableGDO2Interrupt
// */
//#pragma inline
//void CC1101EnableGDO2Interrupt(unsigned char radioId)
//{
//  #if defined(__BSP_RADIO_ENABLE_GDO2_INTERRUPT)
//  __BSP_RADIO_ENABLE_GDO2_INTERRUPT(radioId);
//  #endif
//}
//
///**
// *  @fn   CC1101DisableGDO2Interrupt
// */
//#pragma inline
//void CC1101DisableGDO2Interrupt(unsigned char radioId)
//{
//  #if defined(__BSP_RADIO_DISABLE_GDO2_INTERRUPT)
//  __BSP_RADIO_DISABLE_GDO2_INTERRUPT(radioId);
//  #endif
//}
//
///**
// *  @fn   CC1101GDO2EdgeSelect
// */
//#if defined(__BSP_RADIO_GDO2_INTERRUPT_EDGE)
//#define CC1101GDO2EdgeSelect(radioId, edge)       \
//{                                                 \
//  __BSP_RADIO_GDO0_INTERRUPT_EDGE(radioId, edge); \
//}
//#endif

#include "../../../../BSP/BoardDrivers.h"

#if defined(__RADIO_CCXXX_CC1101) || defined(__RADIO_CCXXX_CC110L) || defined(__RADIO_CCXXX_CC2500)

#include "../CCXXXConfig.h"
#include "../Framework/Drivers/Radio/RadioStruct.h"

/**
 *  @fn   CC1101Configure
 */
#define CC1101Configure(radioId)            __BSP_RADIO_CONFIGURE(radioId)

/**
 *  @fn CC1101Write
 */
void CC1101Write(Radio * radio, unsigned char address, unsigned char * pBuffer, unsigned char count);

/**
 *  @fn CC1101Read
 */
unsigned char CC1101Read(Radio * radio, unsigned char addr, unsigned char * pBuffer, unsigned char count);

/**
 *  @fn CC1101UpdateSettings
 */
void CC1101UpdateSettings(Radio * pRadio, RadioSettings * pRadioSettings, RadioChannel * pRadioChannel, RadioPower * pRadioPower);

/**
 *  @fn     CC1101PowerOnReset
 *
 *  @brief  Resets radio upon power up sequence.
 */
unsigned char CC1101PowerOnReset(Radio * pRadio);

/**
 *  @fn   CC1101WakeUp
 */
void CC1101WakeUp(Radio * pRadio, RadioSettings * pRadioSettings, RadioPower * pRadioPower);

/**
 *  @fn CC1101Sleep
 */
void CC1101Sleep(Radio * pRadio);

/**
 *  @fn   CC1101EnableGDO0Interrupt
 */
void CC1101EnableGDO0Interrupt(unsigned char radioId);

/**
 *  @fn   CC1101DisableGDO0Interrupt
 */
void CC1101DisableGDO0Interrupt(unsigned char radioId);

/**
 *  @fn   CC1101GDO0EdgeSelect
 */
//#if defined(__BSP_RADIO_GDO0_INTERRUPT_EDGE)
#define CC1101GDO0EdgeSelect(radioId, edge)       \
{                                                 \
  __BSP_RADIO_GDO0_INTERRUPT_EDGE(radioId, edge); \
}
//#endif

/**
 *  @fn   CC1101EnableGDO2Interrupt
 */
void CC1101EnableGDO2Interrupt(unsigned char radioId);

/**
 *  @fn   CC1101DisableGDO2Interrupt
 */
void CC1101DisableGDO2Interrupt(unsigned char radioId);

/**
 *  @fn   CC1101GDO2EdgeSelect
 */
//#if defined(__BSP_RADIO_GDO2_INTERRUPT_EDGE)
#define CC1101GDO2EdgeSelect(radioId, edge)       \
{                                                 \
  __BSP_RADIO_GDO0_INTERRUPT_EDGE(radioId, edge); \
}
//#endif

#endif

#endif  // __RADIO_CC1101INTERFACE_H
