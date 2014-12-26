/**
 *  @file AIRBoosterPackLiteConfig.h
 */
#ifndef __BSP_AIRBOOSTERPACKLITECONFIG_H
#define __BSP_AIRBOOSTERPACKLITECONFIG_H

/**
 *  @brief  Radio configuration.
 */
#define __BSP_CONFIG_RADIO1_GDO0_ENABLE     1
#define __BSP_CONFIG_RADIO1_GDO2_ENABLE     0

/**
 *  @brief  Radio SPI1 enable.
 */
#define __BSP_CONFIG_SPI1_ENABLE            1

/**
 *  @brief
 */
#define __BSP_CONFIG_SPI1_MODE              UCMODE_0
#define __BSP_CONFIG_SPI1_CLOCK_PHASE       UCCKPH
#define __BSP_CONFIG_SPI1_CLOCK_POLARITY    0
#define __BSP_CONFIG_SPI1_CLOCK_SOURCE      UCSSEL_2
#define __BSP_CONFIG_SPI1_CLOCK_DIVIDER     1

/**
 *  @brief
 */
#define __BSP_CONFIG_SPI1_CSN_PORT          PORT2
#define __BSP_CONFIG_SPI1_CSN_PIN           PIN7
#define __BSP_CONFIG_SPI1_CSN_DIRECTION     OUTPUT
#define __BSP_CONFIG_SPI1_CSN_POLARITY      ACTIVE_LOW

/**
 *  @brief
 */
#define __BSP_CONFIG_SPI1_DATA_DELAY        0   //!< In clock cycles

#endif  // __BSP_AIRBOOSTERPACKLITECONFIG_H
