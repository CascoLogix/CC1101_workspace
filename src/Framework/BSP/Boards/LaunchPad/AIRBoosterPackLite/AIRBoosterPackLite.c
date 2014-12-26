/**
 *  @file   AIRBoosterPackLite.c
 */
#if defined(__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE)
#include "AIRBoosterPackLite.h"
#include "AIRBoosterPackLiteConfig.h"
#include "AIRBoosterPackLiteDrivers.h"

/**
 *  @brief  Radio SPI connection definition.
 */
SPIConnection spiBus1 = {
  {
    {
      __BSP_CONFIG_SPI1_CSN_PORT,
      __BSP_CONFIG_SPI1_CSN_PIN,
      __BSP_CONFIG_SPI1_CSN_DIRECTION
    },
    __BSP_CONFIG_SPI1_CSN_POLARITY
  }
  //!< MOSI connection
  //!< MISO connection
  //!< SCLK connection
};

RadioConnection radio1Connection = {
  __BSP_RADIO1_PERIPHERAL,
  __BSP_SPI1_CONNECTION
};

Radio radio1 = {
  __BSP_RADIO1,
  #if defined(__RADIO_CCXXX_CC1101)
    CC1101,
  #elif defined(__RADIO_CCXXX_CC110L)
    CC110L,
  #elif defined(__RADIO_CCXXX_CC2500)
    CC2500,
  #endif
  RADIO_ON,
  &radio1Connection
  //!< Radio settings
  //!< Radio channel
  //!< Radio power
};

#endif  // __BSP_LAUNCHPAD_AIRBOOSTERPACKLITE
