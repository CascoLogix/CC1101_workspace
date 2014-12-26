/**
 *  @file   LaunchPadDrivers.h
 */
#ifndef __BSP_LAUNCHPAD_DRIVERS_H
#define __BSP_LAUNCHPAD_DRIVERS_H

// Get HAL drivers.
#include "../../../HAL/HAL.h"

// Get LaunchPad definitions.
#include "LaunchPad.h"

// Get driver interfaces.
#include "../../../Drivers/Watchdog/Watchdog.h"
#include "../../../Drivers/Flash/Flash.h"
#include "../../../Drivers/Timer/SoftwareTimer.h"
#include "../../../Drivers/Timer/SoftwareTimerStruct.h"
#include "../../../Drivers/Timer/Timer.h"
#include "../../../Drivers/ADC/ADC.h"
#include "../../../Drivers/LED/LED.h"
#include "../../../Drivers/UART/UART.h"
#include "../../../Drivers/PushButton/PushButton.h"
#include "../../../Drivers/Random/Random.h"
extern SoftwareTimer swTimer[];
extern PushButtonTimer pushButtonTimer;
extern DelayTimer delayTimer;
extern unsigned char (*SWTimerEvent)(const void *);
extern unsigned char (*PushButtonEvent)(const void *);

////////////////////////////////////////////////////////////////////////////////
//  CLOCK
////////////////////////////////////////////////////////////////////////////////

#define BoardClockSystemInit()              __BSP_CLOCK_SYSTEM_CONFIGURE()
#define __BSP_CLOCK_SYSTEM_CONFIGURE()      __hal_BasicClockModulePlusConfigure(__BSP_CONFIG_CLOCK_HZ,              \
                                                                                __BSP_CONFIG_DCOCTL,                \
                                                                                __BSP_CONFIG_DCO_RANGE,             \
                                                                                __BSP_CONFIG_CLOCK_DCO_RESISTOR,    \
                                                                                __BSP_CONFIG_CLOCK_MCLK_SOURCE,     \
                                                                                __BSP_CONFIG_CLOCK_SMCLK_SOURCE,    \
                                                                                __BSP_CONFIG_CLOCK_MCLK_DIVIDER,    \
                                                                                __BSP_CONFIG_CLOCK_SMCLK_DIVIDER,   \
                                                                                __BSP_CONFIG_CLOCK_ACLK_DIVIDER,    \
                                                                                __BSP_CONFIG_CLOCK_XT2_ENABLE,      \
                                                                                __BSP_CONFIG_CLOCK_XT2_RANGE,       \
                                                                                __BSP_CONFIG_CLOCK_LFXT1_MODE,      \
                                                                                __BSP_CONFIG_CLOCK_LFXT1_SELECT,    \
                                                                                __BSP_CONFIG_CLOCK_LFXT1_RANGE,     \
                                                                                __BSP_CONFIG_CLOCK_LFXT1_CAP_SELECT)

////////////////////////////////////////////////////////////////////////////////
//  WATCHDOG
////////////////////////////////////////////////////////////////////////////////

#define __BSP_WATCHDOG_CONFIGURE()                            \
{                                                             \
  __hal_WatchdogConfigure(__BSP_CONFIG_WATCHDOG_NMI_EDGE,     \
                          __BSP_CONFIG_WATCHDOG_NMI_SELECT);  \
}

#define __BSP_WATCHDOG_HOLD()                                 \
{                                                             \
  WDTCTL = WDTPW | WDTHOLD;                                   \
}

#define __BSP_WATCHDOG_RESET()                                \
{                                                             \
  WDTCTL = WDTPW | WDTCNTCL;                                  \
}

////////////////////////////////////////////////////////////////////////////////
//  FLASH
////////////////////////////////////////////////////////////////////////////////

#define __BSP_FLASH_ERASE(segmentAddress)   __hal_FlashModuleErase(segmentAddress)

#define __BSP_FLASH_WRITE_BYTE(address, data) __hal_FlashModuleWriteByte(address, data)

#define __BSP_FLASH_WRITE_BUFFER(address, buffer, count)															\
{																													\
  if (__BSP_CONFIG_FLASH_SWAP_STORAGE == 0)																			\
  {																													\
    volatile unsigned char * baseAddr = (volatile unsigned char *)__BSP_FLASH1_BASE_ADDRESS;                        \
    volatile unsigned char * flashSwapAddr = (volatile unsigned char *)__BSP_CONFIG_FLASH_SWAP_STORAGE_BASE_ADDRESS;\
    __hal_FlashModuleWriteBuffer(baseAddr,																			\
                                 flashSwapAddr,																		\
                                 address,																			\
                                 buffer,																			\
                                 count);																			\
  }																													\
  else																												\
  {																													\
    volatile unsigned char * baseAddr = (volatile unsigned char *)__BSP_FLASH1_BASE_ADDRESS;						\
    __hal_FlashModuleRAMWriteBuffer(baseAddr,																		\
                                     address,																		\
                                     buffer,																		\
                                     count);																		\
  }																													\
}

////////////////////////////////////////////////////////////////////////////////
//  SOFTWARE TIMER
////////////////////////////////////////////////////////////////////////////////

#define __BSP_SWTIMER_CONFIGURE()                            \
{                                                            \
  AttachEvent(__BSP_SWTIMER_SOURCE, UpdateSoftwareTimers);   \
}

////////////////////////////////////////////////////////////////////////////////
//  TIMER
////////////////////////////////////////////////////////////////////////////////

#define __BSP_TIMER_CONFIGURE(timerId)                                                    \
{                                                                                         \
  if (timerId == __BSP_TIMER1)                                                            \
  {                                                                                       \
    __hal_Timer0A3Configure(__BSP_CONFIG_TIMER1_CLOCK_SOURCE,                             \
                            __BSP_CONFIG_TIMER1_CLOCK_DIVIDER,                            \
                            __BSP_CONFIG_TIMER1_INTERRUPT_ENABLE);                        \
    __hal_Timer0A3CaptureCompareConfigure(__BSP_TIMER1_CCR0,                              \
                                          __BSP_CONFIG_TIMER1_CCR0_CAPTURE_MODE,          \
                                          __BSP_CONFIG_TIMER1_CCR0_CAPTURE_INPUT_SELECT,  \
                                          __BSP_CONFIG_TIMER1_CCR0_SYNC_CAPTURE_SOURCE,   \
                                          __BSP_CONFIG_TIMER1_CCR0_SYNC_CAPTURE_INPUT,    \
                                          __BSP_CONFIG_TIMER1_CCR0_CAPTURE_ENABLE,        \
                                          __BSP_CONFIG_TIMER1_CCR0_OUTPUT_MODE,           \
                                          __BSP_CONFIG_TIMER1_CCR0_OUTPUT,                \
                                          __BSP_CONFIG_TIMER1_CCR0_INTERRUPT_ENABLE,      \
                                          __BSP_CONFIG_TIMER1_CCR0_INPUT);                \
    __hal_Timer0A3CaptureCompareConfigure(__BSP_TIMER1_CCR1,                              \
                                          __BSP_CONFIG_TIMER1_CCR1_CAPTURE_MODE,          \
                                          __BSP_CONFIG_TIMER1_CCR1_CAPTURE_INPUT_SELECT,  \
                                          __BSP_CONFIG_TIMER1_CCR1_SYNC_CAPTURE_SOURCE,   \
                                          __BSP_CONFIG_TIMER1_CCR1_SYNC_CAPTURE_INPUT,    \
                                          __BSP_CONFIG_TIMER1_CCR1_CAPTURE_ENABLE,        \
                                          __BSP_CONFIG_TIMER1_CCR1_OUTPUT_MODE,           \
                                          __BSP_CONFIG_TIMER1_CCR1_OUTPUT,                \
                                          __BSP_CONFIG_TIMER1_CCR1_INTERRUPT_ENABLE,      \
                                          __BSP_CONFIG_TIMER1_CCR1_INPUT);                \
    __hal_Timer0A3CaptureCompareConfigure(__BSP_TIMER1_CCR2,                              \
                                          __BSP_CONFIG_TIMER1_CCR2_CAPTURE_MODE,          \
                                          __BSP_CONFIG_TIMER1_CCR2_CAPTURE_INPUT_SELECT,  \
                                          __BSP_CONFIG_TIMER1_CCR2_SYNC_CAPTURE_SOURCE,   \
                                          __BSP_CONFIG_TIMER1_CCR2_SYNC_CAPTURE_INPUT,    \
                                          __BSP_CONFIG_TIMER1_CCR2_CAPTURE_ENABLE,        \
                                          __BSP_CONFIG_TIMER1_CCR2_OUTPUT_MODE,           \
                                          __BSP_CONFIG_TIMER1_CCR2_OUTPUT,                \
                                          __BSP_CONFIG_TIMER1_CCR2_INTERRUPT_ENABLE,      \
                                          __BSP_CONFIG_TIMER1_CCR2_INPUT);                \
  }                                                                                       \
  else if (timerId == __BSP_TIMER2)                                                       \
  {                                                                                       \
    __hal_Timer1A3Configure(__BSP_CONFIG_TIMER2_CLOCK_SOURCE,                             \
                            __BSP_CONFIG_TIMER2_CLOCK_DIVIDER,                            \
                            __BSP_CONFIG_TIMER2_INTERRUPT_ENABLE);                        \
    __hal_Timer1A3CaptureCompareConfigure(__BSP_TIMER2_CCR0,                              \
                                          __BSP_CONFIG_TIMER2_CCR0_CAPTURE_MODE,          \
                                          __BSP_CONFIG_TIMER2_CCR0_CAPTURE_INPUT_SELECT,  \
                                          __BSP_CONFIG_TIMER2_CCR0_SYNC_CAPTURE_SOURCE,   \
                                          __BSP_CONFIG_TIMER2_CCR0_SYNC_CAPTURE_INPUT,    \
                                          __BSP_CONFIG_TIMER2_CCR0_CAPTURE_ENABLE,        \
                                          __BSP_CONFIG_TIMER2_CCR0_OUTPUT_MODE,           \
                                          __BSP_CONFIG_TIMER2_CCR0_OUTPUT,                \
                                          __BSP_CONFIG_TIMER2_CCR0_INTERRUPT_ENABLE,      \
                                          __BSP_CONFIG_TIMER2_CCR0_INPUT);                \
    __hal_Timer1A3CaptureCompareConfigure(__BSP_TIMER2_CCR1,                              \
                                          __BSP_CONFIG_TIMER2_CCR1_CAPTURE_MODE,          \
                                          __BSP_CONFIG_TIMER2_CCR1_CAPTURE_INPUT_SELECT,  \
                                          __BSP_CONFIG_TIMER2_CCR1_SYNC_CAPTURE_SOURCE,   \
                                          __BSP_CONFIG_TIMER2_CCR1_SYNC_CAPTURE_INPUT,    \
                                          __BSP_CONFIG_TIMER2_CCR1_CAPTURE_ENABLE,        \
                                          __BSP_CONFIG_TIMER2_CCR1_OUTPUT_MODE,           \
                                          __BSP_CONFIG_TIMER2_CCR1_OUTPUT,                \
                                          __BSP_CONFIG_TIMER2_CCR1_INTERRUPT_ENABLE,      \
                                          __BSP_CONFIG_TIMER2_CCR1_INPUT);                \
    __hal_Timer1A3CaptureCompareConfigure(__BSP_TIMER2_CCR2,                              \
                                          __BSP_CONFIG_TIMER2_CCR2_CAPTURE_MODE,          \
                                          __BSP_CONFIG_TIMER2_CCR2_CAPTURE_INPUT_SELECT,  \
                                          __BSP_CONFIG_TIMER2_CCR2_SYNC_CAPTURE_SOURCE,   \
                                          __BSP_CONFIG_TIMER2_CCR2_SYNC_CAPTURE_INPUT,    \
                                          __BSP_CONFIG_TIMER2_CCR2_CAPTURE_ENABLE,        \
                                          __BSP_CONFIG_TIMER2_CCR2_OUTPUT_MODE,           \
                                          __BSP_CONFIG_TIMER2_CCR2_OUTPUT,                \
                                          __BSP_CONFIG_TIMER2_CCR2_INTERRUPT_ENABLE,      \
                                          __BSP_CONFIG_TIMER2_CCR2_INPUT);                \
  }                                                                                       \
}

#define __BSP_TIMER_ENABLE_INTERRUPT(timerId) \
{                                             \
  if (timerId == __BSP_TIMER1)                \
  {                                           \
    __hal_Timer0A3EnableInterrupt();          \
  }                                           \
  else if (timerId == __BSP_TIMER2)           \
  {                                           \
    __hal_Timer1A3EnableInterrupt();          \
  }                                           \
}

#define __BSP_TIMER_DISABLE_INTERRUPT(timerId)  \
{                                               \
  if (timerId == __BSP_TIMER1)                  \
  {                                             \
    __hal_Timer0A3DisableInterrupt();           \
  }                                             \
  else if (timerId == __BSP_TIMER2)             \
  {                                             \
    __hal_Timer1A3DisableInterrupt();           \
  }                                             \
}

#define __BSP_TIMER_ENABLE(timerId, mode)       \
{                                               \
  if (timerId == __BSP_TIMER1)                  \
  {                                             \
    __hal_Timer0A3Enable(mode);                 \
  }                                             \
  else if (timerId == __BSP_TIMER2)             \
  {                                             \
    __hal_Timer1A3Enable(mode);                 \
  }                                             \
}
  
#define __BSP_TIMER_SET_COUNT(timerId, value)   \
{                                               \
  if (timerId == __BSP_TIMER1)                  \
    TA0R = value;                               \
  else if (timerId == __BSP_TIMER2)             \
    TA1R = value;                               \
}

#define __BSP_TIMER_GET_COUNT(timerId)      ((timerId == __BSP_TIMER1) ? TA0R : TA1R)  

#define __BSP_TIMER_SET_CCR(timerId, ccrId, value)  \
{                                                   \
  if (timerId == __BSP_TIMER1)                      \
  {                                                 \
    __hal_Timer0A3SetCCR(ccrId, value);             \
  }                                                 \
  else if (timerId == __BSP_TIMER2)                 \
  {                                                 \
    __hal_Timer1A3SetCCR(ccrId, value);             \
  }                                                 \
}

#define __BSP_TIMER_CCR_ENABLE_INTERRUPT(timerId, ccrId)\
{                                                       \
  if (timerId == __BSP_TIMER1)                          \
  {                                                     \
    if (ccrId == 0)                                     \
    {                                                   \
      __hal_Timer0A3CCR0EnableInterrupt();              \
    }                                                   \
    else if (ccrId == 1)                                \
    {                                                   \
      __hal_Timer0A3CCR1EnableInterrupt();              \
    }                                                   \
    else if (ccrId == 2)                                \
    {                                                   \
      __hal_Timer0A3CCR2EnableInterrupt();              \
    }                                                   \
  }                                                     \
  else if (timerId == __BSP_TIMER2)                     \
  {                                                     \
    if (ccrId == 0)                                     \
    {                                                   \
      __hal_Timer1A3CCR0EnableInterrupt();              \
    }                                                   \
    else if (ccrId == 1)                                \
    {                                                   \
      __hal_Timer1A3CCR1EnableInterrupt();              \
    }                                                   \
    else if (ccrId == 2)                                \
    {                                                   \
      __hal_Timer1A3CCR2EnableInterrupt();              \
    }                                                   \
  }                                                     \
}

#define __BSP_TIMER_CCR_DISABLE_INTERRUPT(timerId, ccrId) \
{                                                         \
  if (timerId == __BSP_TIMER1)                            \
  {                                                       \
    if (ccrId == 0)                                       \
    {                                                     \
      __hal_Timer0A3CCR0DisableInterrupt();               \
    }                                                     \
    else if (ccrId == 1)                                  \
    {                                                     \
      __hal_Timer0A3CCR1DisableInterrupt();               \
    }                                                     \
    else if (ccrId == 2)                                  \
    {                                                     \
      __hal_Timer0A3CCR2DisableInterrupt();               \
    }                                                     \
  }                                                       \
  else if (timerId == __BSP_TIMER2)                       \
  {                                                       \
    if (ccrId == 0)                                       \
    {                                                     \
      __hal_Timer1A3CCR0DisableInterrupt();               \
    }                                                     \
    else if (ccrId == 1)                                  \
    {                                                     \
      __hal_Timer1A3CCR1DisableInterrupt();               \
    }                                                     \
    else if (ccrId == 2)                                  \
    {                                                     \
      __hal_Timer1A3CCR2DisableInterrupt();               \
    }                                                     \
  }                                                       \
}

#define __BSP_TIMER_CCR_CLEAR_INTERRUPT(timerId, ccrId) \
{                                                       \
  if (timerId == __BSP_TIMER1)                          \
  {                                                     \
    if (ccrId == 0)                                     \
    {                                                   \
      __hal_Timer0A3CCR0ClearInterrupt();               \
    }                                                   \
    else if (ccrId == 1)                                \
    {                                                   \
      __hal_Timer0A3CCR1ClearInterrupt();               \
    }                                                   \
    else if (ccrId == 2)                                \
    {                                                   \
      __hal_Timer0A3CCR2ClearInterrupt();               \
    }                                                   \
  }                                                     \
  else if (timerId == __BSP_TIMER2)                     \
  {                                                     \
    if (ccrId == 0)                                     \
    {                                                   \
      __hal_Timer1A3CCR0ClearInterrupt();               \
    }                                                   \
    else if (ccrId == 1)                                \
    {                                                   \
      __hal_Timer1A3CCR1ClearInterrupt();               \
    }                                                   \
    else if (ccrId == 2)                                \
    {                                                   \
      __hal_Timer1A3CCR2ClearInterrupt();               \
    }                                                   \
  }                                                     \
}

#define __BSP_TIMER_GET_CCR(timerId, ccrId) ((timerId == __BSP_TIMER1) ? ((ccrId == 0) ? TA0CCR0 : (ccrId == 1) ? TA0CCR1 : (ccrId == 2) ? TA0CCR2 : 0) : ((ccrId == 0) ? TA1CCR0 : (ccrId == 1) ? TA1CCR1 : (ccrId == 2) ? TA1CCR2 : 0))

////////////////////////////////////////////////////////////////////////////////
//  ADC
////////////////////////////////////////////////////////////////////////////////

#define __BSP_ADC_ON(adcId)                           \
{                                                     \
  if (adcId == __BSP_ADC1)                            \
  {                                                   \
    __hal_ADC10On();                                  \
  }                                                   \
}

#define __BSP_ADC_OFF(adcId)                          \
{                                                     \
  if (adcId == __BSP_ADC1)                            \
  {                                                   \
    __hal_ADC10Off();                                 \
  }                                                   \
}

#define __BSP_ADC_REF_ON(adcId)                       \
{                                                     \
  if (adcId == __BSP_ADC1)                            \
  {                                                   \
    __hal_ADC10RefOn();                               \
  }                                                   \
}

#define __BSP_ADC_REF_OFF(adcId)                      \
{                                                     \
  if (adcId == __BSP_ADC1)                            \
  {                                                   \
    __hal_ADC10RefOff();                              \
  }                                                   \
}

#define __BSP_ADC_ENABLE_INTERRUPT(adcId)             \
{                                                     \
  if (adcId == __BSP_ADC1)                            \
  {                                                   \
    __hal_ADC10EnableInterrupt();                     \
  }                                                   \
}

#define __BSP_ADC_DISABLE_INTERRUPT(adcId)            \
{                                                     \
  if (adcId == __BSP_ADC1)                            \
  {                                                   \
    __hal_ADC10DisableInterrupt();                    \
  }                                                   \
}

#define __BSP_ADC_CHANNEL_CONFIGURE(adcId, channelId)                   \
{                                                                       \
  if (adcId == __BSP_ADC1)                                              \
  {                                                                     \
    if (channelId == __BSP_ADC1_CHAN1)                                  \
    {                                                                   \
      __hal_ADC10Configure(__BSP_CONFIG_ADC1_CHAN1_REFERENCE_SELECT,    \
                            __BSP_CONFIG_ADC1_CHAN1_SAMPLEHOLD_TIME,    \
                            __BSP_CONFIG_ADC1_CHAN1_SAMPLE_RATE,        \
                            __BSP_CONFIG_ADC1_CHAN1_REFERENCE_OUT,      \
                            __BSP_CONFIG_ADC1_CHAN1_REFERENCE_BURST,    \
                            __BSP_CONFIG_ADC1_CHAN1_REFERENCE_VOLTAGE,  \
                            __BSP_ADC1_CHAN1,                           \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN1_DATA_FORMAT,        \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN1_CLOCK_DIVIDER,      \
                            __BSP_CONFIG_ADC1_CLOCK_SOURCE);            \
    }                                                                   \
    else if (channelId == __BSP_ADC1_CHAN2)                             \
    {                                                                   \
      __hal_ADC10Configure(__BSP_CONFIG_ADC1_CHAN2_REFERENCE_SELECT,    \
                            __BSP_CONFIG_ADC1_CHAN2_SAMPLEHOLD_TIME,    \
                            __BSP_CONFIG_ADC1_CHAN2_SAMPLE_RATE,        \
                            __BSP_CONFIG_ADC1_CHAN2_REFERENCE_OUT,      \
                            __BSP_CONFIG_ADC1_CHAN2_REFERENCE_BURST,    \
                            __BSP_CONFIG_ADC1_CHAN2_REFERENCE_VOLTAGE,  \
                            __BSP_ADC1_CHAN2,                           \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN2_DATA_FORMAT,        \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN2_CLOCK_DIVIDER,      \
                            __BSP_CONFIG_ADC1_CLOCK_SOURCE);            \
    }                                                                   \
    else if (channelId == __BSP_ADC1_CHAN3)                             \
    {                                                                   \
      __hal_ADC10Configure(__BSP_CONFIG_ADC1_CHAN1_REFERENCE_SELECT,    \
                            __BSP_CONFIG_ADC1_CHAN3_SAMPLEHOLD_TIME,    \
                            __BSP_CONFIG_ADC1_CHAN3_SAMPLE_RATE,        \
                            __BSP_CONFIG_ADC1_CHAN3_REFERENCE_OUT,      \
                            __BSP_CONFIG_ADC1_CHAN3_REFERENCE_BURST,    \
                            __BSP_CONFIG_ADC1_CHAN3_REFERENCE_VOLTAGE,  \
                            __BSP_ADC1_CHAN3,                           \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN3_DATA_FORMAT,        \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN3_CLOCK_DIVIDER,      \
                            __BSP_CONFIG_ADC1_CLOCK_SOURCE);            \
    }                                                                   \
    else if (channelId == __BSP_ADC1_CHAN4)                             \
    {                                                                   \
      __hal_ADC10Configure(__BSP_CONFIG_ADC1_CHAN4_REFERENCE_SELECT,    \
                            __BSP_CONFIG_ADC1_CHAN4_SAMPLEHOLD_TIME,    \
                            __BSP_CONFIG_ADC1_CHAN4_SAMPLE_RATE,        \
                            __BSP_CONFIG_ADC1_CHAN4_REFERENCE_OUT,      \
                            __BSP_CONFIG_ADC1_CHAN4_REFERENCE_BURST,    \
                            __BSP_CONFIG_ADC1_CHAN4_REFERENCE_VOLTAGE,  \
                            __BSP_ADC1_CHAN4,                           \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN4_DATA_FORMAT,        \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN4_CLOCK_DIVIDER,      \
                            __BSP_CONFIG_ADC1_CLOCK_SOURCE);            \
    }                                                                   \
    else if (channelId == __BSP_ADC1_CHAN5)                             \
    {                                                                   \
      __hal_ADC10Configure(__BSP_CONFIG_ADC1_CHAN5_REFERENCE_SELECT,    \
                            __BSP_CONFIG_ADC1_CHAN5_SAMPLEHOLD_TIME,    \
                            __BSP_CONFIG_ADC1_CHAN5_SAMPLE_RATE,        \
                            __BSP_CONFIG_ADC1_CHAN5_REFERENCE_OUT,      \
                            __BSP_CONFIG_ADC1_CHAN5_REFERENCE_BURST,    \
                            __BSP_CONFIG_ADC1_CHAN5_REFERENCE_VOLTAGE,  \
                            __BSP_ADC1_CHAN5,                           \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN5_DATA_FORMAT,        \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN5_CLOCK_DIVIDER,      \
                            __BSP_CONFIG_ADC1_CLOCK_SOURCE);            \
    }                                                                   \
    else if (channelId == __BSP_ADC1_CHAN6)                             \
    {                                                                   \
      __hal_ADC10Configure(__BSP_CONFIG_ADC1_CHAN6_REFERENCE_SELECT,    \
                            __BSP_CONFIG_ADC1_CHAN6_SAMPLEHOLD_TIME,    \
                            __BSP_CONFIG_ADC1_CHAN6_SAMPLE_RATE,        \
                            __BSP_CONFIG_ADC1_CHAN6_REFERENCE_OUT,      \
                            __BSP_CONFIG_ADC1_CHAN6_REFERENCE_BURST,    \
                            __BSP_CONFIG_ADC1_CHAN6_REFERENCE_VOLTAGE,  \
                            __BSP_ADC1_CHAN6,                           \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN6_DATA_FORMAT,        \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN6_CLOCK_DIVIDER,      \
                            __BSP_CONFIG_ADC1_CLOCK_SOURCE);            \
    }                                                                   \
    else if (channelId == __BSP_ADC1_CHAN7)                             \
    {                                                                   \
      __hal_ADC10Configure(__BSP_CONFIG_ADC1_CHAN7_REFERENCE_SELECT,    \
                            __BSP_CONFIG_ADC1_CHAN7_SAMPLEHOLD_TIME,    \
                            __BSP_CONFIG_ADC1_CHAN7_SAMPLE_RATE,        \
                            __BSP_CONFIG_ADC1_CHAN7_REFERENCE_OUT,      \
                            __BSP_CONFIG_ADC1_CHAN7_REFERENCE_BURST,    \
                            __BSP_CONFIG_ADC1_CHAN7_REFERENCE_VOLTAGE,  \
                            __BSP_ADC1_CHAN7,                           \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN7_DATA_FORMAT,        \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN7_CLOCK_DIVIDER,      \
                            __BSP_CONFIG_ADC1_CLOCK_SOURCE);            \
    }                                                                   \
    else if (channelId == __BSP_ADC1_CHAN8)                             \
    {                                                                   \
      __hal_ADC10Configure(__BSP_CONFIG_ADC1_CHAN8_REFERENCE_SELECT,    \
                            __BSP_CONFIG_ADC1_CHAN8_SAMPLEHOLD_TIME,    \
                            __BSP_CONFIG_ADC1_CHAN8_SAMPLE_RATE,        \
                            __BSP_CONFIG_ADC1_CHAN8_REFERENCE_OUT,      \
                            __BSP_CONFIG_ADC1_CHAN8_REFERENCE_BURST,    \
                            __BSP_CONFIG_ADC1_CHAN8_REFERENCE_VOLTAGE,  \
                            __BSP_ADC1_CHAN8,                           \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN8_DATA_FORMAT,        \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN8_CLOCK_DIVIDER,      \
                            __BSP_CONFIG_ADC1_CLOCK_SOURCE);            \
    }                                                                   \
    else if (channelId == __BSP_ADC1_CHAN9)                             \
    {                                                                   \
      __hal_ADC10Configure(__BSP_CONFIG_ADC1_CHAN9_REFERENCE_SELECT,    \
                            __BSP_CONFIG_ADC1_CHAN9_SAMPLEHOLD_TIME,    \
                            __BSP_CONFIG_ADC1_CHAN9_SAMPLE_RATE,        \
                            __BSP_CONFIG_ADC1_CHAN9_REFERENCE_OUT,      \
                            __BSP_CONFIG_ADC1_CHAN9_REFERENCE_BURST,    \
                            __BSP_CONFIG_ADC1_CHAN9_REFERENCE_VOLTAGE,  \
                            __BSP_ADC1_CHAN9,                           \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN9_DATA_FORMAT,        \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN9_CLOCK_DIVIDER,      \
                            __BSP_CONFIG_ADC1_CLOCK_SOURCE);            \
    }                                                                   \
    else if (channelId == __BSP_ADC1_CHAN10)                            \
    {                                                                   \
      __hal_ADC10Configure(__BSP_CONFIG_ADC1_CHAN10_REFERENCE_SELECT,   \
                            __BSP_CONFIG_ADC1_CHAN10_SAMPLEHOLD_TIME,   \
                            __BSP_CONFIG_ADC1_CHAN10_SAMPLE_RATE,       \
                            __BSP_CONFIG_ADC1_CHAN10_REFERENCE_OUT,     \
                            __BSP_CONFIG_ADC1_CHAN10_REFERENCE_BURST,   \
                            __BSP_CONFIG_ADC1_CHAN10_REFERENCE_VOLTAGE, \
                            __BSP_ADC1_CHAN10,                          \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN10_DATA_FORMAT,       \
                            0,                                          \
                            __BSP_CONFIG_ADC1_CHAN10_CLOCK_DIVIDER,     \
                            __BSP_CONFIG_ADC1_CLOCK_SOURCE);            \
    }                                                                   \
  }                                                                     \
}

#define __BSP_ADC_GET_CONVERSION_VALUE(adcId)     __hal_ADC10GetConversionValue()

#define __BSP_ADC_SINGLE_CONVERSION(adcId, channel)                     \
{                                                                       \
  if (adcId == __BSP_ADC1)                                              \
  {                                                                     \
    __BSP_ADC_CHANNEL_CONFIGURE(adcId, channel);                        \
    __hal_ADC10StartSingleConversion(channel);                          \
  }                                                                     \
}

#define __BSP_ADC_ENABLE_CONVERSION(adcId)                              \
{                                                                       \
  if (adcId == __BSP_ADC1)                                              \
  {                                                                     \
    __hal_ADC10EnableConversion();                                      \
  }                                                                     \
}

////////////////////////////////////////////////////////////////////////////////
//  LED
////////////////////////////////////////////////////////////////////////////////

#define __BSP_LED_CONFIGURE(ledId)                                    \
{                                                                     \
  if (ledId == __BSP_LED1)                                            \
  {                                                                   \
    __BSP_LED1_DIRECTION  |= __BSP_LED1_PIN;                          \
    __BSP_LED1_PORT       &= ~__BSP_LED1_PIN;                         \
    __BSP_LED1_ENABLE     &= ~__BSP_LED1_PIN;                         \
    __BSP_LED1_ENABLE2    &= ~__BSP_LED1_PIN;                         \
  }                                                                   \
  else if (ledId == __BSP_LED2)                                       \
  {                                                                   \
    __BSP_LED2_DIRECTION  |= __BSP_LED2_PIN;                          \
    __BSP_LED2_PORT       &= ~__BSP_LED2_PIN;                         \
    __BSP_LED2_ENABLE     &= ~__BSP_LED2_PIN;                         \
    __BSP_LED2_ENABLE2    &= ~__BSP_LED2_PIN;                         \
    __BSP_LED2_ENABLE     |=  __BSP_LED2_PIN * __BSP_CONFIG_LED2_PWM; \
  }                                                                   \
}

/**
 *  @brief  Set an LED pin high to turn on. The polarity of LEDs on the LaunchPad
 *          are ACTIVE HIGH.
 */
#define __BSP_LED_ON(ledId)               \
{                                         \
  if (ledId == __BSP_LED1)                \
    __BSP_LED1_PORT |= __BSP_LED1_PIN;    \
  else if (ledId == __BSP_LED2)           \
    __BSP_LED2_PORT |= __BSP_LED2_PIN;    \
}

/**
 *  @brief
 */
#define __BSP_LED_OFF(ledId)              \
{                                         \
  if (ledId == __BSP_LED1)                \
    __BSP_LED1_PORT &= ~__BSP_LED1_PIN;   \
  else if (ledId == __BSP_LED2)           \
    __BSP_LED2_PORT &= ~__BSP_LED2_PIN;   \
}

/**
 *  @brief
 */
#define __BSP_LED_TOGGLE(ledId)           \
{                                         \
  if (ledId == __BSP_LED1)                \
    __BSP_LED1_PORT ^= __BSP_LED1_PIN;    \
  else if (ledId == __BSP_LED2)           \
    __BSP_LED2_PORT ^= __BSP_LED2_PIN;    \
}

/**
 *  @brief
 */
#define __BSP_LED_STATE(ledId)            ((ledId == __BSP_LED1) ?              \
                                          (__BSP_LED1_PORT & __BSP_LED1_PIN) :  \
                                          (__BSP_LED2_PORT & __BSP_LED2_PIN))

////////////////////////////////////////////////////////////////////////////////
//  PUSHBUTTON
////////////////////////////////////////////////////////////////////////////////

#define __BSP_PUSHBUTTON_CONFIGURE(buttonId)       \
{                                                  \
  P1SEL  &= ~__BSP_PUSHBUTTON1_PIN;                \
  P1SEL2 &= ~__BSP_PUSHBUTTON1_PIN;                \
  P1DIR  &= ~__BSP_PUSHBUTTON1_PIN;                \
  P1OUT  |=  __BSP_PUSHBUTTON1_PIN;                \
  P1IES  |=  __BSP_PUSHBUTTON1_PIN;                \
  P1IE   |=  __BSP_PUSHBUTTON1_PIN;                \
  P1REN  |=  __BSP_PUSHBUTTON1_PIN;                \
  P1IFG  &= ~__BSP_PUSHBUTTON1_PIN;                \
}

#define __BSP_PUSHBUTTON_EVENT_HANDLER(buttonId)  \
{                                                 \
  if (buttonId == __BSP_PUSHBUTTON1)              \
  {                                               \
    if (P1IES & __BSP_PUSHBUTTON1_PIN)            \
    {                                             \
      P1IES &= ~__BSP_PUSHBUTTON1_PIN;            \
      P1IFG &= ~__BSP_PUSHBUTTON1_PIN;            \
      return 1;                                   \
    }                                             \
    else                                          \
    {                                             \
      P1IES |= __BSP_PUSHBUTTON1_PIN;             \
      P1IFG &= ~__BSP_PUSHBUTTON1_PIN;            \
      return 0;                                   \
    }                                             \
  }                                               \
}

////////////////////////////////////////////////////////////////////////////////
//  UART
////////////////////////////////////////////////////////////////////////////////

/**
 *  @brief  Configure port and peripheral for UART operation.
 */
#define __BSP_UART_CONFIGURATION(uartId)                                          \
{                                                                                 \
  __BSP_UART1_DIRECTION |= __BSP_UART1_TX_PIN;                                    \
  __BSP_UART1_ENABLE    |= __BSP_UART1_TX_PIN | __BSP_UART1_RX_PIN;               \
  __BSP_UART1_ENABLE2   |= __BSP_UART1_TX_PIN | __BSP_UART1_RX_PIN;               \
                                                                                  \
  __hal_UARTConfigure(__BSP_UART_ID(uartId),                                      \
                      __BSP_UART_CLOCK_RATE(uartId),                              \
                      __BSP_UART_CLOCK_SOURCE(uartId),                            \
                      __BSP_UART_BAUD_RATE(uartId),                               \
                      __BSP_UART_DATA_BITS(uartId),                               \
                      __BSP_UART_PARITY_BIT(uartId),                              \
                      __BSP_UART_STOP_BITS(uartId));                              \
}

#define __BSP_UART_TRANSMIT_BYTE(uartId, value)   __hal_UARTTransmitByte(uartId, value)
#define __BSP_UART_RECEIVE_BYTE(uartId, value)    __hal_UARTReceiveByte(uartId, value)
#define __BSP_UART_BUSY(uartId)                   __hal_UARTBusy(uartId)

////////////////////////////////////////////////////////////////////////////////
//  RANDOM NUMBER GENERATOR
////////////////////////////////////////////////////////////////////////////////

/**
 *  @brief  Generate Random Number from hardware source
 */
//#define __BSP_RAND(source)  ((source == __BSP_RAND_VLO) ? __hal_GetRandomIntegerFromVLO() : __hal_GetRandomIntegerFromADC())
#if (__BSP_RAND_SOURCE == __BSP_RAND_VLO)
  #define __BSP_RAND()  __hal_GetRandomIntegerFromVLO()
#elif (__BSP_RAND_SOURCE == __BSP_RAND_ADC)
  #define __BSP_RAND()  __hal_GetRandomIntegerFromADC()
#endif


#endif  // __BSP_LAUNCHPAD_DRIVERS_H
