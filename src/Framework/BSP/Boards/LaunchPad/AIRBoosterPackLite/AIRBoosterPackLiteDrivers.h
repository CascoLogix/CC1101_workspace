/**
 *  @file   AIRBoosterStackLiteDrivers.h
 */
#ifndef __BSP_AIRBOOSTERSTACKLITE_DRIVERS_H
#define __BSP_AIRBOOSTERSTACKLITE_DRIVERS_H

// Get HAL drivers.
#include "../../../../HAL/HAL.h"

// Get AIR BoosterPack Lite definitions.
#include "AIRBoosterPackLite.h"

// Get driver interfaces.
#include "../../../../Drivers/SPI/SPI.h"
#include "../../../../Drivers/Radio/Radio.h"
#include "../../../../Drivers/Radio/RadioStruct.h"
extern SPIConnection spiBus1;
extern Radio radio1;


/**
 *  @brief  Configure port and peripheral for SPI (non-interrupt driven master)
 *          operation.
 */
#define __BSP_SPI_CONFIGURATION(spiId)                                                    \
{                                                                                         \
  if (spiId == __BSP_SPI1)                                                                \
  {                                                                                       \
    __BSP_SPI1_SELECT |= __BSP_SPI1_SCLK_PIN | __BSP_SPI1_MOSI_PIN | __BSP_SPI1_MISO_PIN; \
    __BSP_SPI1_SELECT2 |= __BSP_SPI1_SCLK_PIN | __BSP_SPI1_MOSI_PIN | __BSP_SPI1_MISO_PIN;\
    if (__BSP_CONFIG_SPI1_CSN_PORT == PORT1)                                              \
    {                                                                                     \
      P1SEL &= ~__BSP_CONFIG_SPI1_CSN_PIN;                                                \
      P1SEL2 &= ~__BSP_CONFIG_SPI1_CSN_PIN;                                               \
      P1DIR |= __BSP_CONFIG_SPI1_CSN_PIN;                                                 \
    }                                                                                     \
    else if (__BSP_CONFIG_SPI1_CSN_PORT == PORT2)                                         \
    {                                                                                     \
      P2SEL &= ~__BSP_CONFIG_SPI1_CSN_PIN;                                                \
      P2SEL2 &= ~__BSP_CONFIG_SPI1_CSN_PIN;                                               \
      P2DIR |= __BSP_CONFIG_SPI1_CSN_PIN;                                                 \
    }                                                                                     \
  }                                                                                       \
  __hal_SPIConfigure( __BSP_SPI1_PERIPHERAL,                                              \
                      __BSP_CONFIG_SPI1_MODE,                                             \
                      __BSP_CONFIG_SPI1_CLOCK_PHASE,                                      \
                      __BSP_CONFIG_SPI1_CLOCK_POLARITY,                                   \
                      __BSP_CONFIG_SPI1_CLOCK_SOURCE,                                     \
                      __BSP_CONFIG_SPI1_CLOCK_DIVIDER);                                   \
}

/**
 *  @brief
 */
#define __BSP_SPI_SINGLE_WRITE(spiId, address, data)                      \
{                                                                         \
  if (spiId == __BSP_SPI1)                                                \
  {                                                                       \
    __BSP_SPI1_SELECT   |= __BSP_SPI1_MISO_PIN;                           \
    __BSP_SPI1_SELECT2  |= __BSP_SPI1_MISO_PIN;                           \
  }                                                                       \
  __hal_SPISingleWrite(__BSP_SPI_GET_PERIPHERAL(spiId),                   \
                        __BSP_SPI_CONNECTION(spiId),                      \
                        address,                                          \
                        data);                                            \
  if (spiId == __BSP_SPI1)                                                \
  {                                                                       \
    __BSP_SPI1_SELECT   &= ~__BSP_SPI1_MISO_PIN;                          \
    __BSP_SPI1_SELECT2  &= ~__BSP_SPI1_MISO_PIN;                          \
    __BSP_SPI1_SELECT   |=  __BSP_SPI1_MISO_PIN * __BSP_CONFIG_LED2_PWM;  \
  }                                                                       \
}

/**
 *  @brief
 */
#define __BSP_SPI_BURST_WRITE(spiId, address, buffer, count)              \
{                                                                         \
  if (spiId == __BSP_SPI1)                                                \
  {                                                                       \
    __BSP_SPI1_SELECT   |= __BSP_SPI1_MISO_PIN;                           \
    __BSP_SPI1_SELECT2  |= __BSP_SPI1_MISO_PIN;                           \
  }                                                                       \
  __hal_SPIBurstWrite(__BSP_SPI_GET_PERIPHERAL(spiId),                    \
                      __BSP_SPI_CONNECTION(spiId),                        \
                      address,                                            \
                      buffer,                                             \
                      count);                                             \
  if (spiId == __BSP_SPI1)                                                \
  {                                                                       \
    __BSP_SPI1_SELECT   &= ~__BSP_SPI1_MISO_PIN;                          \
    __BSP_SPI1_SELECT2  &= ~__BSP_SPI1_MISO_PIN;                          \
    __BSP_SPI1_SELECT   |=  __BSP_SPI1_MISO_PIN * __BSP_CONFIG_LED2_PWM;  \
  }                                                                       \
}

/**
 *  @brief
 */
#define __BSP_SPI_SINGLE_READ(spiId, address)                             \
{                                                                         \
  if (spiId == __BSP_SPI1)                                                \
  {                                                                       \
    __BSP_SPI1_SELECT   |= __BSP_SPI1_MISO_PIN;                           \
    __BSP_SPI1_SELECT2  |= __BSP_SPI1_MISO_PIN;                           \
  }                                                                       \
  __hal_SPISingleRead(__BSP_SPI_GET_PERIPHERAL(spiId),                    \
                      __BSP_SPI_CONNECTION(spiId),                        \
                      address);                                           \
  if (spiId == __BSP_SPI1)                                                \
  {                                                                       \
    __BSP_SPI1_SELECT   &= ~__BSP_SPI1_MISO_PIN;                          \
    __BSP_SPI1_SELECT2  &= ~__BSP_SPI1_MISO_PIN;                          \
    __BSP_SPI1_SELECT   |=  __BSP_SPI1_MISO_PIN * __BSP_CONFIG_LED2_PWM;  \
  }                                                                       \
}

/**
 *  @brief
 */
#define __BSP_SPI_BURST_READ(spiId, address, buffer, count)               \
{                                                                         \
  if (spiId == __BSP_SPI1)                                                \
  {                                                                       \
    __BSP_SPI1_SELECT   |= __BSP_SPI1_MISO_PIN;                           \
    __BSP_SPI1_SELECT2  |= __BSP_SPI1_MISO_PIN;                           \
  }                                                                       \
  __hal_SPIBurstRead(__BSP_SPI_GET_PERIPHERAL(spiId),                     \
                      __BSP_SPI_CONNECTION(spiId),                        \
                      address,                                            \
                      buffer,                                             \
                      count);                                             \
  if (spiId == __BSP_SPI1)                                                \
  {                                                                       \
    __BSP_SPI1_SELECT   &= ~__BSP_SPI1_MISO_PIN;                          \
    __BSP_SPI1_SELECT2  &= ~__BSP_SPI1_MISO_PIN;                          \
    __BSP_SPI1_SELECT   |=  __BSP_SPI1_MISO_PIN * __BSP_CONFIG_LED2_PWM;  \
  }                                                                       \
}

/**
 *  @brief  Configure Radio interrupt ports and peripheral for SPI.
 */
#define __BSP_RADIO_CONFIGURE(radioId)                      \
{                                                           \
  if (radioId == __BSP_RADIO1)                              \
  {                                                         \
    __BSP_SPI_CONFIGURATION(__BSP_RADIO1_PERIPHERAL_INDEX); \
    __BSP_RADIO1_GDO0_SELECT  &= ~__BSP_RADIO1_GDO0_PIN;  \
    __BSP_RADIO1_GDO0_SELECT2 &= ~__BSP_RADIO1_GDO0_PIN;  \
    __BSP_RADIO1_GDO2_SELECT  |= __BSP_RADIO1_GDO2_PIN;   \
    __BSP_RADIO1_GDO2_SELECT2 |= __BSP_RADIO1_GDO2_PIN;   \
  }                                                         \
}

/**
 *  @brief  Enables GDO0 on the CC110x radio module.
 */
#define __BSP_RADIO_ENABLE_GDO0_INTERRUPT(radioId)        \
{                                                         \
  if (radioId == __BSP_RADIO1)                            \
  {                                                       \
    __BSP_RADIO1_GDO0_INTERRUPT |= __BSP_RADIO1_GDO0_PIN; \
  }                                                       \
}

/**
 *  @brief  Disables GDO0 on the CC110x radio module.
 */
#define __BSP_RADIO_DISABLE_GDO0_INTERRUPT(radioId)       \
{                                                         \
  if (radioId == __BSP_RADIO1)                            \
  {                                                       \
    __BSP_RADIO1_GDO0_INTERRUPT &= ~__BSP_RADIO1_GDO0_PIN;\
  }                                                       \
}

/**
 *  @brief
 */
#define __BSP_RADIO_GDO0_INTERRUPT_EDGE(radioId, edge)          \
{                                                               \
  if (radioId == __BSP_RADIO1)                                  \
  {                                                             \
    if (edge == 0)                                              \
      __BSP_RADIO1_GDO0_EDGE_SELECT &= ~__BSP_RADIO1_GDO0_PIN;  \
    else                                                        \
      __BSP_RADIO1_GDO0_EDGE_SELECT |= __BSP_RADIO1_GDO0_PIN;   \
    __BSP_RADIO1_GDO0_FLAG &= ~__BSP_RADIO1_GDO0_PIN;           \
  }                                                             \
}

/**
 *  @brief  Enables GDO2 on the CC110x radio module.
 */
#define __BSP_RADIO_ENABLE_GDO2_INTERRUPT(radioId)        \
{                                                         \
  if (radioId == __BSP_RADIO1)                            \
  {                                                       \
    __BSP_RADIO1_GDO2_INTERRUPT |= __BSP_RADIO1_GDO2_PIN; \
  }                                                       \
}

/**
 *  @brief  Disables GDO2 on the CC110x radio module.
 */
#define __BSP_RADIO_DISABLE_GDO2_INTERRUPT(radioId)       \
{                                                         \
  if (radioId == __BSP_RADIO1)                            \
  {                                                       \
    __BSP_RADIO1_GDO2_INTERRUPT &= ~__BSP_RADIO1_GDO2_PIN;\
  }                                                       \
}

/**
 *  @brief
 */
#define __BSP_RADIO_GDO2_INTERRUPT_EDGE(radioId, edge)          \
{                                                               \
  if (radioId == __BSP_RADIO1)                                  \
  {                                                             \
    if (edge == 0)                                              \
      __BSP_RADIO1_GDO2_EDGE_SELECT &= ~__BSP_RADIO1_GDO2_PIN;  \
    else                                                        \
      __BSP_RADIO1_GDO2_EDGE_SELECT |= __BSP_RADIO1_GDO2_PIN;   \
    __BSP_RADIO1_GDO2_FLAG &= ~__BSP_RADIO1_GDO2_PIN;           \
  }                                                             \
}

#endif  // __BSP_AIRBOOSTERSTACKLITE_DRIVERS_H
