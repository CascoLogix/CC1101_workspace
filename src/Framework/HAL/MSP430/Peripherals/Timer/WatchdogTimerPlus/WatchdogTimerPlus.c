/**
 *  \file   WatchdogTimerPlus.c
 *
 *  \brief  Watchdog Timer+ peripheral physical driver implementation.
 */
#include "WatchdogTimerPlus.h"

#if defined(__MCU_MSP430_WATCHDOGTIMERPLUS)

/**
 *  \details  This is the default event handler for a Watchdog Timer+ event. It
 *            does not perform anything useful. The user must attach an event to
 *            the WatchdogTimerEvent handle to override this default event
 *            handler.
 */
unsigned char WatchdogTimerDefaultEventHandler(const void * params)
{
  return 0;
}

unsigned char (*WatchdogTimerEvent)(const void *) = WatchdogTimerDefaultEventHandler;  //!< Watchdog Timer+ interrupt handle.

#pragma vector=WDT_VECTOR
__interrupt void WatchdogTimerInterruptServiceRoutine()
{
  // Call the WDT+ ISR extension to handle this event.
  // TODO: Determine parameters that need to be passed to the event handler.
  InterruptServiceRoutineExtension(WatchdogTimerEvent, WatchdogTimerDefaultEventHandler, NULL);
}

/**
 *  \details  This is the default event handler for a Non-maskable Interrupt 
 *            (NMI) event. It does not perform anything useful. The user must 
 *            attach an event to the NonMaskableInterruptEvent handle to override 
 *            this default event handler.
 */
unsigned char NonMaskableInterruptDefaultEventHandler(const void * params)
{
  return 0;
}

unsigned char (*NonMaskableInterruptEvent)(const void *) = NonMaskableInterruptDefaultEventHandler; //!< Non-maskable interrupt handle

/**
 *  \details
 */
#pragma vector=NMI_VECTOR
__interrupt void NonMaskableInterruptServiceRoutine()
{
  // Call the NMI ISR extension to handle this event.
  // TODO: Determine parameters that need to be passed to the event handler.
  InterruptServiceRoutineExtension(NonMaskableInterruptEvent, NonMaskableInterruptDefaultEventHandler, NULL);
}

#endif  // WATCHDOG_TIMER_PLUS MODULE
