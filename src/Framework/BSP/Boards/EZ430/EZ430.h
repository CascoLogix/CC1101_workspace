/**
 *  @file   EZ430.h
 */
#ifndef __BSP_EZ430_H
#define __BSP_EZ430_H

// Get configuration.
#include "EZ430Config.h"

// Define intrinsic function definitions based on chosen compiler.
#if defined(__IAR_SYSTEMS_ICC__)
#define __BSP_LOW_LEVEL_INIT()              __intrinsic int __low_level_init()
#define __BSP_DISABLE_INTERRUPT()           __disable_interrupt()
#define __BSP_ENABLE_INTERRUPT()            __enable_interrupt()
#define __BSP_LOW_POWER_MODE(mode)          \
{                                           \
  if (mode == 0)                            \
    __low_power_mode_0();                   \
}
#else
#define __BSP_LOW_LEVEL_INIT()		    int _system_pre_init()
#define __BSP_DISABLE_INTERRUPT()	    _disable_interrupts()
#define __BSP_ENABLE_INTERRUPT()	    _enable_interrupts()
#define __BSP_LOW_POWER_MODE(mode)	    \
{					    \
  if (mode == 0)			    \
  	_low_power_mode_0();		    \
}
#endif

/**
 *  @section  Microcontroller
 *
 *  @brief    The TI MSP430 EZ430 board has a 40-pin QFN package. The clock
 *            system of these microcontrollers is the Basic Clock Module+.
 */
#define __BSP_MCU_SOCKET                    40
#define __BSP_CLOCK_SYSTEM                  BASIC_CLOCK_MODULE_PLUS

/**
 *  @section  Flash
 *
 *  @brief
 */
#define __BSP_FLASH1                        0
#define __BSP_FLASH1_SEGMENT_SIZE           64
#define __BSP_FLASH1_BASE_ADDRESS           0x1000

/**
 *  @section  GPIO
 *
 *  @brief    This board supports interrupts on PORT1 and PORT2. The following
 *            defines how these interrupt service routines can be interracted 
 *            with.
 *          
 *  @details  Each port can have eight potential events based on pin interrupt
 *            enables. To attach an event handler to a port interrupt event,
 *            use one of the provided event handles below.
 */
#define __BSP_PORT1                         0
#define __BSP_PORT1_NO_EVENT                PORT1_NO_EVENT
#define __BSP_PORT1_0_EVENT                 PORT1_0_EVENT
#define __BSP_PORT1_1_EVENT                 PORT1_1_EVENT
#define __BSP_PORT1_2_EVENT                 PORT1_2_EVENT
#define __BSP_PORT1_3_EVENT                 PORT1_3_EVENT
#define __BSP_PORT1_4_EVENT                 PORT1_4_EVENT
#define __BSP_PORT1_5_EVENT                 PORT1_5_EVENT
#define __BSP_PORT1_6_EVENT                 PORT1_6_EVENT
#define __BSP_PORT1_7_EVENT                 PORT1_7_EVENT
#define __BSP_PORT1_EVENT_HANDLE            PORT1_EVENT
#define __BSP_PORT2                         1
#define __BSP_PORT2_NO_EVENT                PORT2_NO_EVENT
#define __BSP_PORT2_0_EVENT                 PORT2_0_EVENT
#define __BSP_PORT2_1_EVENT                 PORT2_1_EVENT
#define __BSP_PORT2_2_EVENT                 PORT2_2_EVENT
#define __BSP_PORT2_3_EVENT                 PORT2_3_EVENT
#define __BSP_PORT2_4_EVENT                 PORT2_4_EVENT
#define __BSP_PORT2_5_EVENT                 PORT2_5_EVENT
#define __BSP_PORT2_6_EVENT                 PORT2_6_EVENT
#define __BSP_PORT2_7_EVENT                 PORT2_7_EVENT
#define __BSP_PORT2_EVENT_HANDLE            PORT2_EVENT

/**
 *  @section  Timer
 *
 *  @brief    Supported microcontrollers for the EZ430 will contain a timer.
 *            The number of timers will vary. See your microcontroller's specific
 *            data sheet to determine what is available to you.
 *
 *  @details  Depending on the microcontroller's package size (14 or 20 pin),
 *            you may have one or two timers available for your use.
 *
 *            Each timer has a certain number of capture/compare registers that
 *            are interrupt capable. The possible events and event handles are
 *            provided below for your application development.
 */
#define __BSP_TIMER1                        0
#define __BSP_TIMER1_CCR0                   0
#define __BSP_TIMER1_CCR0_EVENT_HANDLE      TA_CCR0_EVENT
#define __BSP_TIMER1_CCR0_EVENT             TIMERA_CCR0_EVENT
#define __BSP_TIMER1_CCR1                   1
#define __BSP_TIMER1_CCR1_EVENT_HANDLE      TA_CCR1_EVENT
#define __BSP_TIMER1_CCR1_EVENT             TIMERA_CCR1_EVENT
#define __BSP_TIMER1_CCR2                   2
#define __BSP_TIMER1_CCR2_EVENT_HANDLE      TA_CCR1_EVENT
#define __BSP_TIMER1_CCR2_EVENT             TIMERA_CCR2_EVENT

#define __BSP_TIMER2                        1
#define __BSP_TIMER2_CCR0                   0
#if (__BSP_CONFIG_SWTIMER1_ENABLE)
  #define __BSP_TIMER2_CCR0_EVENT_HANDLE    &SWTimerEvent
#else
  #define __BSP_TIMER2_CCR0_EVENT_HANDLE    TB_CCR0_EVENT
#endif
#define __BSP_TIMER2_CCR0_EVENT             TIMERB_CCR0_EVENT
#define __BSP_TIMER2_CCR1                   1
#define __BSP_TIMER2_CCR1_EVENT_HANDLE      TB_CCR1_EVENT
#define __BSP_TIMER2_CCR1_EVENT             TIMERB_CCR1_EVENT
#define __BSP_TIMER2_CCR2                   2
#define __BSP_TIMER2_CCR2_EVENT_HANDLE      TB_CCR1_EVENT
#define __BSP_TIMER2_CCR2_EVENT             TIMERB_CCR2_EVENT

/**
 *  @section  SoftwareTimer
 *
 *  @brief
 *
 *  @details
 */
#define __BSP_SWTIMER_COUNT                 __BSP_CONFIG_SWTIMER1_COUNT
#define __BSP_SWTIMER_SOURCE                ((__BSP_CONFIG_SWTIMER1_SOURCE == __BSP_TIMER1) ? TA_CCR0_EVENT : TB_CCR0_EVENT)
#define __BSP_SWTIMER                       &swTimer
#define __BSP_DELAYTIMER                    &delayTimer

/**
 *  @section  ADC
 *
 *  @brief    The Analog-to-Digital converter has 8 analog channels available
 *            along with an internal temperature sensor and microcontroller
 *            voltage source (Vcc - Vss).
 *
 *  @details  Each channel can trigger an ADC interrupt. The interrupt service
 *            routine handles all of the possible channels, so there is only one
 *            event handle and a single possible event: "Conversion Event". The
 *            application will need to know which channel is configured to
 *            determine the cause for the interrupt. 
 *            
 *            In most cases, the ISR will just grab the conversion result from 
 *            memory and store it in a variable global to the place it is needed 
 *            in the application.
 *
 *  @note     The current implementation of the ADC ISR has no knowledge of what 
 *            channel was converted. Since the application can reconfigure at
 *            run-time, it is up to the application developer to take special
 *            note of this.
 */
#define __BSP_ADC1                          0
#define __BSP_ADC1_EVENT_HANDLE             ADC10_EVENT
#define __BSP_ADC1_CONVERSION_EVENT         ADC10_CONVERSION_EVENT

#define __BSP_ADC_GET_CHANNEL(channelId)    ((channelId == 1) ? __BSP_ADC1_CHAN1 :  \
                                            (channelId == 2) ? __BSP_ADC1_CHAN2 :   \
                                            (channelId == 3) ? __BSP_ADC1_CHAN1 :   \
                                            (channelId == 4) ? __BSP_ADC1_CHAN2 :   \
                                            (channelId == 5) ? __BSP_ADC1_CHAN1 :   \
                                            (channelId == 6) ? __BSP_ADC1_CHAN2 :   \
                                            (channelId == 7) ? __BSP_ADC1_CHAN1 :   \
                                            (channelId == 8) ? __BSP_ADC1_CHAN2 :   \
                                            (channelId == 9) ? __BSP_ADC1_CHAN1 :   \
                                            (channelId == 10) ? __BSP_ADC1_CHAN2 : )

#define __BSP_ADC1_CHAN1_EVENT              ADC10_A0_EVENT
#define __BSP_ADC1_CHAN2_EVENT              ADC10_A1_EVENT
#define __BSP_ADC1_CHAN3_EVENT              ADC10_A2_EVENT
#define __BSP_ADC1_CHAN4_EVENT              ADC10_A3_EVENT
#define __BSP_ADC1_CHAN5_EVENT              ADC10_A4_EVENT
#define __BSP_ADC1_CHAN6_EVENT              ADC10_A5_EVENT
#define __BSP_ADC1_CHAN7_EVENT              ADC10_A6_EVENT
#define __BSP_ADC1_CHAN8_EVENT              ADC10_A7_EVENT
#define __BSP_ADC1_CHAN9_EVENT              ADC10_TEMPERATURE_SENSOR_EVENT
#define __BSP_ADC1_CHAN10_EVENT             ADC10_VOLTAGE_SOURCE_EVENT

#define __BSP_ADC1_CHAN1                    INCH_0    //!< A0
#define __BSP_ADC1_CHAN2                    INCH_1    //!< A1
#define __BSP_ADC1_CHAN3                    INCH_2    //!< A2
#define __BSP_ADC1_CHAN4                    INCH_3    //!< A3
#define __BSP_ADC1_CHAN5                    INCH_4    //!< A4
#define __BSP_ADC1_CHAN6                    INCH_5    //!< A5
#define __BSP_ADC1_CHAN7                    INCH_6    //!< A6
#define __BSP_ADC1_CHAN8                    INCH_7    //!< A7
#define __BSP_ADC1_CHAN9                    INCH_10   //!< Temperature sensor
#define __BSP_ADC1_CHAN10                   INCH_11   //!< (Vcc - Vss) / 2

/**
 *  LED
 */
#define __BSP_LED1                          0
#define __BSP_LED1_PORT                     P1OUT
#define __BSP_LED1_PIN                      BIT0
#define __BSP_LED1_DIRECTION                P1DIR
#define __BSP_LED1_ENABLE                   P1SEL
// #define __BSP_LED1_ENABLE2                  P1SEL2
#define __BSP_LED2                          1
#define __BSP_LED2_PORT                     P1OUT
#define __BSP_LED2_PIN                      BIT1
#define __BSP_LED2_DIRECTION                P1DIR
#define __BSP_LED2_ENABLE                   P1SEL
// #define __BSP_LED2_ENABLE2                  P1SEL2
// LED aliases
#define __BSP_LEDRED1                       __BSP_LED1
#define __BSP_LEDGREEN1                     __BSP_LED2

/**
 *  Push button
 */
#define __BSP_PUSHBUTTON                    1

#define __BSP_PUSHBUTTON1                   0
#define __BSP_PUSHBUTTON1_PORT              P1IN
#define __BSP_PUSHBUTTON1_PIN               BIT2
#define __BSP_PUSHBUTTON1_EVENT_HANDLE      &PushButtonEvent
#define __BSP_PUSHBUTTON1_EVENT             __BSP_PORT1_2_EVENT
#define __BSP_PUSHBUTTONTIMER               &pushButtonTimer

/**
 *  UART
 */
#define __BSP_UART                          1

#define __BSP_UART_ID(uartId)               __BSP_UART1_PERIPHERAL
#define __BSP_UART_CLOCK_RATE(uartId)       __BSP_CONFIG_UART1_CLOCK_RATE
#define __BSP_UART_CLOCK_SOURCE(uartId)     __BSP_CONFIG_UART1_CLOCK_SOURCE
#define __BSP_UART_BAUD_RATE(uartId)        __BSP_CONFIG_UART1_BAUD_RATE
#define __BSP_UART_DATA_BITS(uartId)        __BSP_CONFIG_UART1_DATA_BITS
#define __BSP_UART_PARITY_BIT(uartId)       __BSP_CONFIG_UART1_PARITY_BIT
#define __BSP_UART_STOP_BITS(uartId)        __BSP_CONFIG_UART1_STOP_BITS

#define __BSP_UART1                         0
#define __BSP_UART1_PERIPHERAL              USCIA0
#define __BSP_UART1_DIRECTION               P3DIR
#define __BSP_UART1_ENABLE                  P3SEL
// #define __BSP_UART1_ENABLE2                 P3SEL2
#define __BSP_UART1_TX_PIN                  PIN4
#define __BSP_UART1_RX_PIN                  PIN5
#define __BSP_UART1_TX_BUFFER_SIZE          (__BSP_CONFIG_UART1_TX_BUFFER_SIZE+1)
#define __BSP_UART1_RX_BUFFER_SIZE          (__BSP_CONFIG_UART1_RX_BUFFER_SIZE+1)
#define __BSP_UART1_TX_EVENT_HANDLE         USCIAB0TX_EVENT
#define __BSP_UART1_TX_EVENT                USCIA0_TX_EVENT
#define __BSP_UART1_RX_EVENT_HANDLE         USCIAB0RX_EVENT
#define __BSP_UART1_RX_EVENT                USCIA0_RX_EVENT

/**
 *  Random Number Generator
 */
#define __BSP_RAND_VLO                      0
#define __BSP_RAND_ADC                      1

/**
 *  Exported clock configuration.
 */
#if (defined(__BSP_CONFIG_CUSTOM_CLOCK_HZ)      || \
    defined(__BSP_CONFIG_CUSTOM_MSP430_DCOCTL)  || \
    defined(__BSP_CONFIG_CUSTOM_MSP430_BCSCTL1))
  #define __BSP_CLOCK_HZ                    __BSP_CONFIG_CUSTOM_CLOCK_HZ
  #define __BSP_CONFIG_DCOCTL               __BSP_CONFIG_CUSTOM_DCOCTL
  #define __BSP_CONFIG_DCO_RANGE            __BSP_CONFIG_CUSTOM_DCO_RANGE
#else
  #if (__BSP_CONFIG_CLOCK_HZ == 0)
    #error "__BSP_ERROR: Clock frequency cannot be 0"
  #elif (__BSP_CONFIG_CLOCK_HZ == CLOCK_1MHZ)
    #define __BSP_CLOCK_HZ                  CLOCK_1MHZ
    #define __BSP_CONFIG_DCOCTL             CALDCO_1MHZ //!< Factory calibrated value from flash
    #define __BSP_CONFIG_DCO_RANGE          CALBC1_1MHZ //!< Factory calibrated value from flash
  #elif (__BSP_CONFIG_CLOCK_HZ == CLOCK_8MHZ)
    #define __BSP_CLOCK_HZ                  CLOCK_8MHZ
    #define __BSP_CONFIG_DCOCTL             CALDCO_8MHZ //!< Factory calibrated value from flash
    #define __BSP_CONFIG_DCO_RANGE          CALBC1_8MHZ //!< Factory calibrated value from flash
  #elif (__BSP_CONFIG_CLOCK_HZ == CLOCK_12MHZ)
    #define __BSP_CLOCK_HZ                  CLOCK_12MHZ
    #define __BSP_CONFIG_DCOCTL             CALDCO_12MHZ //!< Factory calibrated value from flash
    #define __BSP_CONFIG_DCO_RANGE          CALBC1_12MHZ //!< Factory calibrated value from flash
  #elif (__BSP_CONFIG_CLOCK_HZ == CLOCK_16MHZ)
    #define __BSP_CLOCK_HZ                  CLOCK_16MHZ
    #define __BSP_CONFIG_DCOCTL             CALDCO_16MHZ //!< Factory calibrated value from flash
    #define __BSP_CONFIG_DCO_RANGE          CALBC1_16MHZ //!< Factory calibrated value from flash
  #else
    #error "__BSP_ERROR: Clock frequency is not supported. See EZ430Config.h."
  #endif
#endif

unsigned char UpdateSoftwareTimers(const void * params);

/**
 *  SPI connection
 */
#define __BSP_SPI                           1

#define __BSP_SPI1                          0
#define __BSP_SPI1_PERIPHERAL               USCIB0
#define __BSP_SPI1_SELECT                   P3SEL
// #define __BSP_SPI1_SELECT2                  P3SEL2

#define __BSP_SPI_MISO_PORT(spiId)          __BSP_SPI1_MISO_PORT
#define __BSP_SPI_MISO_PIN(spiId)           __BSP_SPI1_MISO_PIN

// NOTE: 4-wire implementation.
//#define __BSP_SPI1_CSN_PORT                 P3OUT
//#define __BSP_SPI1_CSN_PIN                  PIN0
#define __BSP_SPI1_SCLK_PORT                P3OUT
#define __BSP_SPI1_SCLK_PIN                 PIN3
#define __BSP_SPI1_MOSI_PORT                P3OUT
#define __BSP_SPI1_MOSI_PIN                 PIN1
#define __BSP_SPI1_MISO_PORT                P3IN
#define __BSP_SPI1_MISO_PIN                 PIN2
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
#define __BSP_RADIO1_GDO0_INTERRUPT         P2IE
#define __BSP_RADIO1_GDO0_EDGE_SELECT       P2IES
#define __BSP_RADIO1_GDO0_FLAG              P2IFG
#define __BSP_RADIO1_GDO0_PIN               BIT6
#define __BSP_RADIO1_GDO0_EVENT             PORT2_6_EVENT
#define __BSP_RADIO1_GDO2                   1
#define __BSP_RADIO1_GDO2_SELECT            P2SEL
#define __BSP_RADIO1_GDO2_INTERRUPT         P1IE
#define __BSP_RADIO1_GDO2_EDGE_SELECT       P1IES
#define __BSP_RADIO1_GDO2_FLAG              P1IFG
#define __BSP_RADIO1_GDO2_PIN               BIT7
#define __BSP_RADIO1_GDO2_EVENT             PORT2_7_EVENT

// Interrupt aliases
#define __BSP_RADIO1_INTERRUPT1             __BSP_RADIO1_GDO0
#define __BSP_RADIO1_INTERRUPT2             __BSP_RADIO1_GDO2

#define __BSP_RADIO_GET_SPI_ID(radioId)     0
#define __BSP_RADIO_INTERRUPT(radioId, interruptId)     ((interruptId == __BSP_RADIO1_INTERRUPT1) ?         \
                                                          __BSP_RADIO1_INTERRUPT1 : __BSP_RADIO1_INTERRUPT2)\

// NOTE: Not sure where this should reside. Needed to include the radio driver.
//#define __RADIO_A1101R09
//#define __RADIO_CERTIFCIATION_FCC

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

#endif  // __BSP_EZ430_H