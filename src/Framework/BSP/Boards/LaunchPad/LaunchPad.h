/**
 *  @file   LaunchPad.h
 */
#ifndef __BSP_LAUNCHPAD_H
#define __BSP_LAUNCHPAD_H

// Get configuration.
#include "LaunchPadConfig.h"

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
 *  @brief    The TI MSP430 LaunchPad board has a 20-pin PDIP socket and supports
 *            microcontrollers of 14 and 20-pin packages. The clock system of
 *            these microcontrollers is the Basic Clock Module+.
 */
#define __BSP_MCU_SOCKET                    20
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
 *  @brief    Supported microcontrollers for the LaunchPad will contain a timer.
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
#define __BSP_TIMER1_CCR0_EVENT_HANDLE      TA0_CCR0_EVENT
#define __BSP_TIMER1_CCR0_EVENT             TIMERA_CCR0_EVENT
#define __BSP_TIMER1_CCR1                   1
#define __BSP_TIMER1_CCR1_EVENT_HANDLE      TA0_CCR1_EVENT
#define __BSP_TIMER1_CCR1_EVENT             TIMERA_CCR1_EVENT
#define __BSP_TIMER1_CCR2                   2
#define __BSP_TIMER1_CCR2_EVENT_HANDLE      TA0_CCR1_EVENT
#define __BSP_TIMER1_CCR2_EVENT             TIMERA_CCR2_EVENT

#define __BSP_TIMER2                        1
#define __BSP_TIMER2_CCR0                   0
#if (__BSP_CONFIG_SWTIMER1_ENABLE)
  #define __BSP_TIMER2_CCR0_EVENT_HANDLE    &SWTimerEvent
#else
  #define __BSP_TIMER2_CCR0_EVENT_HANDLE    TA1_CCR0_EVENT
#endif
#define __BSP_TIMER2_CCR0_EVENT             TIMERA_CCR0_EVENT
#define __BSP_TIMER2_CCR1                   1
#define __BSP_TIMER2_CCR1_EVENT_HANDLE      TA1_CCR1_EVENT
#define __BSP_TIMER2_CCR1_EVENT             TIMERA_CCR1_EVENT
#define __BSP_TIMER2_CCR2                   2
#define __BSP_TIMER2_CCR2_EVENT_HANDLE      TA1_CCR1_EVENT
#define __BSP_TIMER2_CCR2_EVENT             TIMERA_CCR2_EVENT

/**
 *  @section  SoftwareTimer
 *
 *  @brief
 *
 *  @details
 */
#define __BSP_SWTIMER_COUNT                 __BSP_CONFIG_SWTIMER1_COUNT
#define __BSP_SWTIMER_SOURCE                ((__BSP_CONFIG_SWTIMER1_SOURCE == __BSP_TIMER1) ? TA0_CCR0_EVENT : TA1_CCR0_EVENT)
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
#define __BSP_LED1_ENABLE2                  P1SEL2
#define __BSP_LED2                          1
#define __BSP_LED2_PORT                     P1OUT
#define __BSP_LED2_PIN                      BIT6
#define __BSP_LED2_DIRECTION                P1DIR
#define __BSP_LED2_ENABLE                   P1SEL
#define __BSP_LED2_ENABLE2                  P1SEL2
// LED aliases
#define __BSP_LEDRED1                       __BSP_LED1
#define __BSP_LEDGREEN1                     __BSP_LED2

/**
 *  Push button
 */
#define __BSP_PUSHBUTTON                    1

#define __BSP_PUSHBUTTON1                   0
#define __BSP_PUSHBUTTON1_PORT              P1IN
#define __BSP_PUSHBUTTON1_PIN               BIT3
#define __BSP_PUSHBUTTON1_EVENT_HANDLE      &PushButtonEvent
#define __BSP_PUSHBUTTON1_EVENT             __BSP_PORT1_3_EVENT
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
#define __BSP_UART1_DIRECTION               P1DIR
#define __BSP_UART1_ENABLE                  P1SEL
#define __BSP_UART1_ENABLE2                 P1SEL2
#define __BSP_UART1_TX_PIN                  PIN1
#define __BSP_UART1_RX_PIN                  PIN2
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
    #error "__BSP_ERROR: Clock frequency is not supported. See LaunchPadConfig.h."
  #endif
#endif

unsigned char UpdateSoftwareTimers(const void * params);

#endif  // __BSP_LAUNCHPAD_H
