/**
 *  @file   LaunchPad.c
 */
#if defined(__BSP_LAUNCHPAD) || defined(__BSP_LAUNCHPAD_AIRBOOSTERPACKLITE)
#include "LaunchPad.h"
//#include "LaunchPadConfig.h"
#include "LaunchPadDrivers.h"

#include "../../../HAL/HAL.h"

#if (__BSP_CONFIG_SWTIMER1_ENABLE)
#if (__BSP_CONFIG_SWTIMER1_COUNT <= 0)
#error "__BSP_ERROR: Invalid software timer count. Value must be greater than 0."
#endif
// Software timer size includes a delay timer as well. When the software timers
// are enabled this delay timer will be included automatically.
SoftwareTimer swTimer[__BSP_CONFIG_SWTIMER1_COUNT];
PushButtonTimer pushButtonTimer = {0,0,0,0,0,0};
DelayTimer delayTimer = {0,0,0,0};

unsigned char UpdateSoftwareTimers(const void * params)
{
  unsigned char response = EVENT_NO_ACTION;
  unsigned char i;
  unsigned char enabled = 0;
  
  // Increment all enabled software timers and retrieve their response. Build
  // the response to return back to the interrupt service routine.
  for (i = 0; i < __BSP_SWTIMER_COUNT; i++)
  {
    response |= SoftwareTimerEventHandler(&swTimer[i]);
    if (swTimer[i].enable)
    {
      enabled = 1;
    }
  }
  
  response |= PushButtonTimerEventHandler(&pushButtonTimer, __BSP_CONFIG_PUSHBUTTON_CLICK_TIMEOUT);
  if (pushButtonTimer.enable)
  {
    enabled = 1;
  }
  
  // Increment the delay timer if it is enabled.
  response |= DelayTimerEventHandler(&delayTimer);
  if (delayTimer.enable)
  {
    enabled = 1;
  }

  // Go to application timer event handler.
  response |= InterruptServiceRoutineExtension(SWTimerEvent, NULL, params);
  
  if (enabled)
  {
    // TODO: Put timer hardware disable interrupt here.
  }
  
  // Return overall response to the interrupt service routine.
  return response;
}

unsigned char (*SWTimerEvent)(const void *) = NULL;     //!< Software timer event handle
unsigned char (*PushButtonEvent)(const void *) = NULL;  //!< Push button event handle

#endif

#if defined(__MCU_MSP430_USCI)
/**
 *  @brief    UART buffer implementation uses circular buffers for receive and
 *            transmit and operates without an application knowing the details.
 *            
 *            This is a software buffer replacement for a hardware buffer that
 *            does not exist on this platform.
 */
//#include "HAL/MSP430/Peripherals/Communication/USCI/USCI.h"
#if (__BSP_CONFIG_UART1_ENABLE)
#if (__BSP_CONFIG_UART1_TX_BUFFER_SIZE <= 0) || (__BSP_CONFIG_UART1_TX_BUFFER_SIZE <= 0)
#error "__BSP_ERROR: Invalid UART buffer size(s). Values must be greater than 0."
#else
//!< Buffer size is size + 1 because of circular buffer implementation
unsigned char USCIA0TXBuffer[__BSP_UART1_TX_BUFFER_SIZE] = {0x00};
unsigned char USCIA0RXBuffer[__BSP_UART1_RX_BUFFER_SIZE] = {0x00};
USCIBuffer USCIA0Buffer = {
  {                                         // TX circular buffer initial state
    &USCIA0TXBuffer[0],
    &USCIA0TXBuffer[0]+(sizeof(USCIA0TXBuffer)-1),
    &USCIA0TXBuffer[0],
    &USCIA0TXBuffer[0],
    sizeof(USCIA0TXBuffer)
  },
  {                                         // RX circular buffer initial state
    &USCIA0RXBuffer[0],
    &USCIA0RXBuffer[0]+(sizeof(USCIA0RXBuffer)-1),
    &USCIA0RXBuffer[0],
    &USCIA0RXBuffer[0],
    sizeof(USCIA0RXBuffer)
  },
  NO_OPERATION,                  // Operation being performed
  0                              // Operation count
};
#endif
#endif

#endif  // __MCU_MSP430_USCI

#endif  // __BSP_LAUNCHPAD
