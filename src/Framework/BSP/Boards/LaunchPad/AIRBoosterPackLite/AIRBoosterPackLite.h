/**
 *  @file   AIRBoosterPackLite.h
 */
#ifndef __BSP_AIRBOOSTERPACKLITE_H
#define __BSP_AIRBOOSTERPACKLITE_H

// Get configuration.
#include "AIRBoosterPackLiteConfig.h"

/**
 *  SPI connection
 */
#define __BSP_SPI                           1

#define __BSP_SPI1                          0
#define __BSP_SPI1_PERIPHERAL               USCIB0
#define __BSP_SPI1_SELECT                   P1SEL
#define __BSP_SPI1_SELECT2                  P1SEL2

#define __BSP_SPI_MISO_PORT(spiId)          __BSP_SPI1_MISO_PORT
#define __BSP_SPI_MISO_PIN(spiId)           __BSP_SPI1_MISO_PIN

// NOTE: 4-wire implementation.
//#define __BSP_SPI1_CSN_PORT                 P1OUT
//#define __BSP_SPI1_CSN_PIN                  PIN4
#define __BSP_SPI1_SCLK_PORT                P1OUT
#define __BSP_SPI1_SCLK_PIN                 PIN5
#define __BSP_SPI1_MOSI_PORT                P1OUT
#define __BSP_SPI1_MOSI_PIN                 PIN7
#define __BSP_SPI1_MISO_PORT                P1IN
#define __BSP_SPI1_MISO_PIN                 PIN6
#define __BSP_SPI1_CONNECTION               &spiBus1

#define __BSP_SPI_ID(spiId)                 __BSP_SPI1
#define __BSP_SPI_GET_PERIPHERAL(spiId)     __BSP_SPI1_PERIPHERAL
#define __BSP_SPI_MODE(spiId)               __BSP_CONFIG_SPI1_MODE
#define __BSP_SPI_CLOCK_PHASE(spiId)        __BSP_CONFIG_SPI1_CLOCK_PHASE
#define __BSP_SPI_CLOCK_POLARITY(spiId)     __BSP_CONFIG_SPI1_CLOCK_POLARITY
#define __BSP_SPI_CLOCK_SOURCE(spiId)       __BSP_CONFIG_SPI1_CLOCK_SOURCE
#define __BSP_SPI_CLOCK_DIVIDER(spiId)      __BSP_CONFIG_SPI1_CLOCK_DIVIDER
#define __BSP_SPI_CONNECTION(spiId)         __BSP_SPI1_CONNECTION

/**
 *  Radio
 */
#define __BSP_RADIO                         1

#define __BSP_RADIO1                        0
#define __BSP_RADIO1_CONNECTION             radio1
#define __BSP_RADIO1_PERIPHERAL             __BSP_SPI1_PERIPHERAL
#define __BSP_RADIO1_PERIPHERAL_INDEX       __BSP_SPI1
#define __BSP_RADIO1_GDO0                   0
#define __BSP_RADIO1_GDO0_SELECT            P2SEL
#define __BSP_RADIO1_GDO0_SELECT2           P2SEL2
#define __BSP_RADIO1_GDO0_INTERRUPT         P2IE
#define __BSP_RADIO1_GDO0_EDGE_SELECT       P2IES
#define __BSP_RADIO1_GDO0_FLAG              P2IFG
#define __BSP_RADIO1_GDO0_PIN               BIT6
#define __BSP_RADIO1_GDO0_EVENT             PORT2_6_EVENT
#define __BSP_RADIO1_GDO2                   1
#define __BSP_RADIO1_GDO2_SELECT            P1SEL
#define __BSP_RADIO1_GDO2_SELECT2           P1SEL2
#define __BSP_RADIO1_GDO2_INTERRUPT         P1IE
#define __BSP_RADIO1_GDO2_EDGE_SELECT       P1IES
#define __BSP_RADIO1_GDO2_FLAG              P1IFG
#define __BSP_RADIO1_GDO2_PIN               BIT0
#define __BSP_RADIO1_GDO2_EVENT             PORT1_0_EVENT

// Interrupt aliases
#define __BSP_RADIO1_INTERRUPT1             __BSP_RADIO1_GDO0
#define __BSP_RADIO1_INTERRUPT2             __BSP_RADIO1_GDO2

#define __BSP_RADIO_GET_SPI_ID(radioId)     0
#define __BSP_RADIO_INTERRUPT(radioId, interruptId)     ((interruptId == __BSP_RADIO1_INTERRUPT1) ?         \
                                                          __BSP_RADIO1_INTERRUPT1 : __BSP_RADIO1_INTERRUPT2)\

// NOTE: Not sure where this should reside. Needed to include the radio driver.
//#define __RADIO_CCXXX_SERIES
//#define __RADIO_CCXXX_CC110L

#if defined(__RADIO_A1101R04) || defined(__RADIO_A1101R08) || defined(__RADIO_A1101R09) || defined(__RADIO_A110LR09) || defined(__RADIO_A2500R24)
  #define __RADIO_CCXXX_SERIES
#endif

#if defined(__RADIO_A1101R04) || defined(__RADIO_A1101R08) || defined(__RADIO_A1101R09)
  #define __RADIO_CCXXX_CC1101
#endif

#if defined(__RADIO_A110LR09)
  #define __RADIO_CCXXX_CC110L
#endif

#if defined(__RADIO_A2500R24)
  #define __RADIO_CCXXX_CC2500
#endif

#endif  // __BSP_AIRBOOSTERPACKLITE_H
