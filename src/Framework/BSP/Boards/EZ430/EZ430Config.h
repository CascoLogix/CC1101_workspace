/**
 *  @file   EZ430Config.h
 */
#ifndef __BSP_EZ430_CONFIG_H
#define __BSP_EZ430_CONFIG_H

#include "HAL/HAL.h"

/**
 *  @brief  Supported calibrated clock speeds: 1, 8, 12, and 16 MHz.
 *          These calibrated values are taken from configuration flash and are 
 *          factory set.
 *
 *  @note   The clock speeds are approximate as they are derived from an internal
 *          digitally controlled oscillator.
 */
#define __BSP_CONFIG_CLOCK_HZ               CLOCK_8MHZ

/**
 *  @brief  Custom clock configuration is available. Providing a custom configuration
 *          overrides the above selection. To configure the clock system, see
 *          device data sheet and user guide on how to setup the Basic Clock
 *          Module+ (BCS).
 */
//#define __BSP_CONFIG_CUSTOM_CLOCK_HZ          0
//#define __BSP_CONFIG_CUSTOM_DCOCTL            0
//#define __BSP_CONFIG_CUSTOM_DCO_RANGE         0

/**
 *  @brief  Clock sources.
 */
#define __BSP_CONFIG_CLOCK_MCLK_SOURCE      SELM_0
#define __BSP_CONFIG_CLOCK_SMCLK_SOURCE     0
#define __BSP_CONFIG_CLOCK_DCO_RESISTOR     0

/**
 *  @brief  Clock dividers.
 */
#define __BSP_CONFIG_CLOCK_MCLK_DIVIDER     DIVM_0
#define __BSP_CONFIG_CLOCK_SMCLK_DIVIDER    DIVS_0
#define __BSP_CONFIG_CLOCK_ACLK_DIVIDER     DIVA_0

/**
 *  @brief  Oscillator configuration. XT2 is a high frequency oscillator. It is
 *          only available on some devices. Please see the datasheet associated
 *          with your processor. The LFXT1 oscillator has two modes of
 *          operation: high frequency and low frequency.
 */
#define __BSP_CONFIG_CLOCK_XT2_ENABLE       0
#define __BSP_CONFIG_CLOCK_XT2_RANGE        0
#define __BSP_CONFIG_CLOCK_LFXT1_MODE       0
#define __BSP_CONFIG_CLOCK_LFXT1_SELECT     LFXT1S_2
#define __BSP_CONFIG_CLOCK_LFXT1_RANGE      0
#define __BSP_CONFIG_CLOCK_LFXT1_CAP_SELECT XCAP_0

/**
 *  @brief  Watchdog control.
 */
#define __BSP_CONFIG_WATCHDOG_NMI_EDGE      0
#define __BSP_CONFIG_WATCHDOG_NMI_SELECT    0

/**
 *  @brief  Flash.
 */
#define __BSP_CONFIG_FLASH_SWAP_STORAGE                 0         //!< Swap storage type: (0) Flash, (1) RAM
#define __BSP_CONFIG_FLASH_SWAP_STORAGE_BASE_ADDRESS    0x1080

/**
 *  @section  LED
 */
#define __BSP_CONFIG_LED2_PWM               0

/**
 *  @section  SoftwareTimer
 */
#define __BSP_CONFIG_SWTIMER1_ENABLE         1             //!< Enable software timer capability
#define __BSP_CONFIG_SWTIMER1_SOURCE         __BSP_TIMER2  //!< Hardware timer source
#define __BSP_CONFIG_SWTIMER1_SOURCE_DIV     120           //!< Hardware timer source divider (CCR0 value)
#define __BSP_CONFIG_SWTIMER1_COUNT          1             //!< Number of software timers

/**
 *  @section  PushButtonTimer
 */
#define __BSP_CONFIG_PUSHBUTTON_CLICK_TIMEOUT           50
#define __BSP_CONFIG_PUSHBUTTON_MINIMUM_CLICK_TIME      2

/**
 *  @brief  Timer 1 control.
 */
#define __BSP_CONFIG_TIMER1_CLOCK_SOURCE                TASSEL_1
#define __BSP_CONFIG_TIMER1_CLOCK_DIVIDER               ID_0
#define __BSP_CONFIG_TIMER1_INTERRUPT_ENABLE            0

/**
 *  @brief  Timer 1 CCR control.
 */
// Capture/compare register 0
#define __BSP_CONFIG_TIMER1_CCR0_CAPTURE_MODE           0
#define __BSP_CONFIG_TIMER1_CCR0_CAPTURE_INPUT_SELECT   0
#define __BSP_CONFIG_TIMER1_CCR0_SYNC_CAPTURE_SOURCE    0
#define __BSP_CONFIG_TIMER1_CCR0_SYNC_CAPTURE_INPUT     0
#define __BSP_CONFIG_TIMER1_CCR0_CAPTURE_ENABLE         0
#define __BSP_CONFIG_TIMER1_CCR0_OUTPUT_MODE            OUTMOD_4
#define __BSP_CONFIG_TIMER1_CCR0_OUTPUT                 0
#define __BSP_CONFIG_TIMER1_CCR0_INTERRUPT_ENABLE       0
#define __BSP_CONFIG_TIMER1_CCR0_INPUT                  0
// Capture/compare register 1
#define __BSP_CONFIG_TIMER1_CCR1_CAPTURE_MODE           0
#define __BSP_CONFIG_TIMER1_CCR1_CAPTURE_INPUT_SELECT   0
#define __BSP_CONFIG_TIMER1_CCR1_SYNC_CAPTURE_SOURCE    0
#define __BSP_CONFIG_TIMER1_CCR1_SYNC_CAPTURE_INPUT     0
#define __BSP_CONFIG_TIMER1_CCR1_CAPTURE_ENABLE         0
#define __BSP_CONFIG_TIMER1_CCR1_OUTPUT_MODE            0
#define __BSP_CONFIG_TIMER1_CCR1_OUTPUT                 0
#define __BSP_CONFIG_TIMER1_CCR1_INTERRUPT_ENABLE       0
#define __BSP_CONFIG_TIMER1_CCR1_INPUT                  0
// Capture/compare register 2
#define __BSP_CONFIG_TIMER1_CCR2_CAPTURE_MODE           0
#define __BSP_CONFIG_TIMER1_CCR2_CAPTURE_INPUT_SELECT   0
#define __BSP_CONFIG_TIMER1_CCR2_SYNC_CAPTURE_SOURCE    0
#define __BSP_CONFIG_TIMER1_CCR2_SYNC_CAPTURE_INPUT     0
#define __BSP_CONFIG_TIMER1_CCR2_CAPTURE_ENABLE         0
#define __BSP_CONFIG_TIMER1_CCR2_OUTPUT_MODE            0
#define __BSP_CONFIG_TIMER1_CCR2_OUTPUT                 0
#define __BSP_CONFIG_TIMER1_CCR2_INTERRUPT_ENABLE       0
#define __BSP_CONFIG_TIMER1_CCR2_INPUT                  0

/**
 *  @brief  Timer 2 control.
 */
#define __BSP_CONFIG_TIMER2_CLOCK_SOURCE                TASSEL_1
#define __BSP_CONFIG_TIMER2_CLOCK_DIVIDER               ID_0
#define __BSP_CONFIG_TIMER2_INTERRUPT_ENABLE            0

/**
 *  @brief  Timer 2 CCR control.
 */
// Capture/compare register 0
#define __BSP_CONFIG_TIMER2_CCR0_CAPTURE_MODE           0
#define __BSP_CONFIG_TIMER2_CCR0_CAPTURE_INPUT_SELECT   0
#define __BSP_CONFIG_TIMER2_CCR0_SYNC_CAPTURE_SOURCE    0
#define __BSP_CONFIG_TIMER2_CCR0_SYNC_CAPTURE_INPUT     0
#define __BSP_CONFIG_TIMER2_CCR0_CAPTURE_ENABLE         0
#define __BSP_CONFIG_TIMER2_CCR0_OUTPUT_MODE            0
#define __BSP_CONFIG_TIMER2_CCR0_OUTPUT                 0
#define __BSP_CONFIG_TIMER2_CCR0_INTERRUPT_ENABLE       CCIE
#define __BSP_CONFIG_TIMER2_CCR0_INPUT                  0
// Capture/compare register 1
#define __BSP_CONFIG_TIMER2_CCR1_CAPTURE_MODE           0
#define __BSP_CONFIG_TIMER2_CCR1_CAPTURE_INPUT_SELECT   0
#define __BSP_CONFIG_TIMER2_CCR1_SYNC_CAPTURE_SOURCE    0
#define __BSP_CONFIG_TIMER2_CCR1_SYNC_CAPTURE_INPUT     0
#define __BSP_CONFIG_TIMER2_CCR1_CAPTURE_ENABLE         0
#define __BSP_CONFIG_TIMER2_CCR1_OUTPUT_MODE            0
#define __BSP_CONFIG_TIMER2_CCR1_OUTPUT                 0
#define __BSP_CONFIG_TIMER2_CCR1_INTERRUPT_ENABLE       0
#define __BSP_CONFIG_TIMER2_CCR1_INPUT                  0
// Capture/compare register 2
#define __BSP_CONFIG_TIMER2_CCR2_CAPTURE_MODE           0
#define __BSP_CONFIG_TIMER2_CCR2_CAPTURE_INPUT_SELECT   0
#define __BSP_CONFIG_TIMER2_CCR2_SYNC_CAPTURE_SOURCE    0
#define __BSP_CONFIG_TIMER2_CCR2_SYNC_CAPTURE_INPUT     0
#define __BSP_CONFIG_TIMER2_CCR2_CAPTURE_ENABLE         0
#define __BSP_CONFIG_TIMER2_CCR2_OUTPUT_MODE            0
#define __BSP_CONFIG_TIMER2_CCR2_OUTPUT                 0
#define __BSP_CONFIG_TIMER2_CCR2_INTERRUPT_ENABLE       0
#define __BSP_CONFIG_TIMER2_CCR2_INPUT                  0

/**
 *  @brief  ADC1 clock source
 */
#define __BSP_CONFIG_ADC1_CLOCK_SOURCE      ADC10SSEL_1

// Channel 1 (A0)
#define __BSP_CONFIG_ADC1_CHAN1_REFERENCE_SELECT    0
#define __BSP_CONFIG_ADC1_CHAN1_SAMPLEHOLD_TIME     0
#define __BSP_CONFIG_ADC1_CHAN1_SAMPLE_RATE         0
#define __BSP_CONFIG_ADC1_CHAN1_REFERENCE_OUT       0
#define __BSP_CONFIG_ADC1_CHAN1_REFERENCE_BURST     0
#define __BSP_CONFIG_ADC1_CHAN1_REFERENCE_VOLTAGE   0
#define __BSP_CONFIG_ADC1_CHAN1_DATA_FORMAT         0
#define __BSP_CONFIG_ADC1_CHAN1_CLOCK_DIVIDER       0
// Channel 2 (A1)
#define __BSP_CONFIG_ADC1_CHAN2_REFERENCE_SELECT    0
#define __BSP_CONFIG_ADC1_CHAN2_SAMPLEHOLD_TIME     0
#define __BSP_CONFIG_ADC1_CHAN2_SAMPLE_RATE         0
#define __BSP_CONFIG_ADC1_CHAN2_REFERENCE_OUT       0
#define __BSP_CONFIG_ADC1_CHAN2_REFERENCE_BURST     0
#define __BSP_CONFIG_ADC1_CHAN2_REFERENCE_VOLTAGE   0
#define __BSP_CONFIG_ADC1_CHAN2_DATA_FORMAT         0
#define __BSP_CONFIG_ADC1_CHAN2_CLOCK_DIVIDER       0
// Channel 3 (A2)
#define __BSP_CONFIG_ADC1_CHAN3_REFERENCE_SELECT    0
#define __BSP_CONFIG_ADC1_CHAN3_SAMPLEHOLD_TIME     0
#define __BSP_CONFIG_ADC1_CHAN3_SAMPLE_RATE         0
#define __BSP_CONFIG_ADC1_CHAN3_REFERENCE_OUT       0
#define __BSP_CONFIG_ADC1_CHAN3_REFERENCE_BURST     0
#define __BSP_CONFIG_ADC1_CHAN3_REFERENCE_VOLTAGE   0
#define __BSP_CONFIG_ADC1_CHAN3_DATA_FORMAT         0
#define __BSP_CONFIG_ADC1_CHAN3_CLOCK_DIVIDER       0
// Channel 4 (A3)
#define __BSP_CONFIG_ADC1_CHAN4_REFERENCE_SELECT    0
#define __BSP_CONFIG_ADC1_CHAN4_SAMPLEHOLD_TIME     0
#define __BSP_CONFIG_ADC1_CHAN4_SAMPLE_RATE         0
#define __BSP_CONFIG_ADC1_CHAN4_REFERENCE_OUT       0
#define __BSP_CONFIG_ADC1_CHAN4_REFERENCE_BURST     0
#define __BSP_CONFIG_ADC1_CHAN4_REFERENCE_VOLTAGE   0
#define __BSP_CONFIG_ADC1_CHAN4_DATA_FORMAT         0
#define __BSP_CONFIG_ADC1_CHAN4_CLOCK_DIVIDER       0
// Channel 5 (A4)
#define __BSP_CONFIG_ADC1_CHAN5_REFERENCE_SELECT    0
#define __BSP_CONFIG_ADC1_CHAN5_SAMPLEHOLD_TIME     0
#define __BSP_CONFIG_ADC1_CHAN5_SAMPLE_RATE         0
#define __BSP_CONFIG_ADC1_CHAN5_REFERENCE_OUT       0
#define __BSP_CONFIG_ADC1_CHAN5_REFERENCE_BURST     0
#define __BSP_CONFIG_ADC1_CHAN5_REFERENCE_VOLTAGE   0
#define __BSP_CONFIG_ADC1_CHAN5_DATA_FORMAT         0
#define __BSP_CONFIG_ADC1_CHAN5_CLOCK_DIVIDER       0
// Channel 6 (A5)
#define __BSP_CONFIG_ADC1_CHAN6_REFERENCE_SELECT    0
#define __BSP_CONFIG_ADC1_CHAN6_SAMPLEHOLD_TIME     0
#define __BSP_CONFIG_ADC1_CHAN6_SAMPLE_RATE         0
#define __BSP_CONFIG_ADC1_CHAN6_REFERENCE_OUT       0
#define __BSP_CONFIG_ADC1_CHAN6_REFERENCE_BURST     0
#define __BSP_CONFIG_ADC1_CHAN6_REFERENCE_VOLTAGE   0
#define __BSP_CONFIG_ADC1_CHAN6_DATA_FORMAT         0
#define __BSP_CONFIG_ADC1_CHAN6_CLOCK_DIVIDER       0
// Channel 7 (A6)
#define __BSP_CONFIG_ADC1_CHAN7_REFERENCE_SELECT    0
#define __BSP_CONFIG_ADC1_CHAN7_SAMPLEHOLD_TIME     0
#define __BSP_CONFIG_ADC1_CHAN7_SAMPLE_RATE         0
#define __BSP_CONFIG_ADC1_CHAN7_REFERENCE_OUT       0
#define __BSP_CONFIG_ADC1_CHAN7_REFERENCE_BURST     0
#define __BSP_CONFIG_ADC1_CHAN7_REFERENCE_VOLTAGE   0
#define __BSP_CONFIG_ADC1_CHAN7_DATA_FORMAT         0
#define __BSP_CONFIG_ADC1_CHAN7_CLOCK_DIVIDER       0
// Channel 8 (A7)
#define __BSP_CONFIG_ADC1_CHAN8_REFERENCE_SELECT    0
#define __BSP_CONFIG_ADC1_CHAN8_SAMPLEHOLD_TIME     0
#define __BSP_CONFIG_ADC1_CHAN8_SAMPLE_RATE         0
#define __BSP_CONFIG_ADC1_CHAN8_REFERENCE_OUT       0
#define __BSP_CONFIG_ADC1_CHAN8_REFERENCE_BURST     0
#define __BSP_CONFIG_ADC1_CHAN8_REFERENCE_VOLTAGE   0
#define __BSP_CONFIG_ADC1_CHAN8_DATA_FORMAT         0
#define __BSP_CONFIG_ADC1_CHAN8_CLOCK_DIVIDER       0
// Channel 9 (Temperature Sensor)
#define __BSP_CONFIG_ADC1_CHAN9_REFERENCE_SELECT    SREF_1
#define __BSP_CONFIG_ADC1_CHAN9_SAMPLEHOLD_TIME     ADC10SHT_3
#define __BSP_CONFIG_ADC1_CHAN9_SAMPLE_RATE         ADC10SR
#define __BSP_CONFIG_ADC1_CHAN9_REFERENCE_OUT       0
#define __BSP_CONFIG_ADC1_CHAN9_REFERENCE_BURST     REFBURST
#define __BSP_CONFIG_ADC1_CHAN9_REFERENCE_VOLTAGE   0
#define __BSP_CONFIG_ADC1_CHAN9_DATA_FORMAT         ADC10DF | SHS_2
#define __BSP_CONFIG_ADC1_CHAN9_CLOCK_DIVIDER       0
// Channel 10 ((Vcc - Vss) / 2)
#define __BSP_CONFIG_ADC1_CHAN10_REFERENCE_SELECT   0
#define __BSP_CONFIG_ADC1_CHAN10_SAMPLEHOLD_TIME    0
#define __BSP_CONFIG_ADC1_CHAN10_SAMPLE_RATE        0
#define __BSP_CONFIG_ADC1_CHAN10_REFERENCE_OUT      0
#define __BSP_CONFIG_ADC1_CHAN10_REFERENCE_BURST    0
#define __BSP_CONFIG_ADC1_CHAN10_REFERENCE_VOLTAGE  0
#define __BSP_CONFIG_ADC1_CHAN10_DATA_FORMAT        0
#define __BSP_CONFIG_ADC1_CHAN10_CLOCK_DIVIDER      0

/**
 *  @brief  UART0 enable.
 */
#define __BSP_CONFIG_UART1_ENABLE           1     //!< Use UART hardware.

#define __BSP_CONFIG_UART1_CLOCK_RATE       __BSP_CONFIG_CLOCK_HZ
#define __BSP_CONFIG_UART1_CLOCK_SOURCE     UART_SMCLK
#define __BSP_CONFIG_UART1_BAUD_RATE        9600
#define __BSP_CONFIG_UART1_DATA_BITS        8
#define __BSP_CONFIG_UART1_PARITY_BIT       0
#define __BSP_CONFIG_UART1_STOP_BITS        1
#define __BSP_CONFIG_UART1_TX_BUFFER_SIZE   5     //!< Must be greater than 0!
#define __BSP_CONFIG_UART1_RX_BUFFER_SIZE   5     //!< Must be greater than 0!

/**
 *  @brief  Random Number Generator hardware source
 */
#define __BSP_RAND_SOURCE                   __BSP_RAND_VLO

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
#define __BSP_CONFIG_SPI1_CSN_PORT          PORT3
#define __BSP_CONFIG_SPI1_CSN_PIN           PIN0
#define __BSP_CONFIG_SPI1_CSN_DIRECTION     OUTPUT
#define __BSP_CONFIG_SPI1_CSN_POLARITY      ACTIVE_LOW

/**
 *  @brief
 */
#define __BSP_CONFIG_SPI1_DATA_DELAY        0   //!< In clock cycles

#endif  // __BSP_EZ430_CONFIG_H