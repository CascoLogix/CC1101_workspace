/**
 *  \file   TimerA.c
 */
#include "TimerA.h"

#if defined(__MCU_MSP430_TIMERA)

#if defined(__MCU_MSP430_TIMERA3)

/**
 *  \details  This is the default event handler for a Timer_A3 CCR0 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the TimerA3CCR0Event handle to override this default event 
 *            handler.
 */
unsigned char TimerA3CCR0DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*TimerA3CCR0Event)(const void *) = TimerA3CCR0DefaultEventHandler;   //!< Timer0_A3 CCR0 interrupt handle.

#pragma vector=TIMERA0_VECTOR
__interrupt void TimerA3CCR0InterruptServiceRoutine()
{
  EventParameters p = {TIMERA_CCR0_EVENT};
  
  // Clear CCR0 flag.
  TACCTL0 &= ~CCIFG;
  
  // Call the Timer0_A3 CCR0 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(TimerA3CCR0Event, TimerA3CCR0DefaultEventHandler, &p);
    
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

/**
 *  \details  This is the default event handler for a Timer_A3 CCR1 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the TimerA3CCR1Event handle to override this default event 
 *            handler.
 */
unsigned char TimerA3CCR1DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*TimerA3CCR1Event)(const void *) = TimerA3CCR1DefaultEventHandler;   //!< Timer_A3 CCR1 interrupt handle.

#pragma vector=TIMERA1_VECTOR
__interrupt void TimerA3CCR1InterruptServiceRoutine()
{
  EventParameters p = {TIMERA_NO_EVENT};

  // Set the event source parameter.
  switch (__even_in_range(TAIV, 14))
  {
    case 0: break;
    case 2:
      p.event = TIMERA_CCR1_EVENT;          // CCR1 interrupt pending
      break;
    case 4:
      p.event = TIMERA_CCR2_EVENT;          // CCR2 interrupt pending
      break;
    case 6: break;
    case 8: break;
    case 10: break;
    case 12: break;
    case 14: break;
    default:
      p.event = TIMERA_NO_EVENT;            // No interrupt pending
      break;
  }
  
  // Call the Timer0_A3 CCR0 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(TimerA3CCR1Event, TimerA3CCR1DefaultEventHandler, &p);
    
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}
#endif  // TIMER_A3 MODULE

#if defined(__MCU_MSP430_TIMER0A3)

/**
 *  \details  This is the default event handler for a Timer0_A3 CCR0 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the Timer0A3CCR0Event handle to override this default event 
 *            handler.
 */
unsigned char Timer0A3CCR0DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*Timer0A3CCR0Event)(const void *) = Timer0A3CCR0DefaultEventHandler;   //!< Timer0_A3 CCR0 interrupt handle.

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0A3CCR0InterruptServiceRoutine()
{
  EventParameters p = {TIMERA_CCR0_EVENT};
  
  // Clear CCR0 flag.
  TA0CCTL0 &= ~CCIFG;
  
  // Call the Timer0_A3 CCR0 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(Timer0A3CCR0Event, Timer0A3CCR0DefaultEventHandler, &p);
    
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

/**
 *  \details  This is the default event handler for a Timer0_A3 CCR1 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the Timer0A3CCR1Event handle to override this default event 
 *            handler.
 */
unsigned char Timer0A3CCR1DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*Timer0A3CCR1Event)(const void *) = Timer0A3CCR1DefaultEventHandler;   //!< Timer0_A3 CCR1 interrupt handle.

#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0A3CCR1InterruptServiceRoutine()
{
  EventParameters p = {TIMERA_NO_EVENT};

  // Set the event source parameter.
  switch (__even_in_range(TA0IV, 14))
  {
    case 0: break;
    case 2:
      p.event = TIMERA_CCR1_EVENT;          // CCR1 interrupt pending
      break;
    case 4:
      p.event = TIMERA_CCR2_EVENT;          // CCR2 interrupt pending
      break;
    case 6: break;
    case 8: break;
    case 10: break;
    case 12: break;
    case 14: break;
    default:
      p.event = TIMERA_NO_EVENT;            // No interrupt pending
      break;
  }
  
  // Call the Timer0_A3 CCR0 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(Timer0A3CCR1Event, Timer0A3CCR1DefaultEventHandler, &p);
    
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

#endif  // TIMER0_A3 SUB MODULE

#if defined(__MCU_MSP430_TIMER1A3)

/**
 *  \details  This is the default event handler for a Timer1_A3 CCR0 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the Timer1A3CCR0Event handle to override this default event 
 *            handler.
 */
unsigned char Timer1A3CCR0DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*Timer1A3CCR0Event)(const void *) = Timer1A3CCR0DefaultEventHandler;   //!< Timer1_A3 CCR0 interrupt handle.

/**
 *  \details
 */
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1A3CCR0InterruptServiceRoutine()
{
  EventParameters p = {TIMERA_CCR0_EVENT};
  
  // Clear CCR0 flag.
  TA1CCTL0 &= ~CCIFG;
  
  // Call the Timer0_A3 CCR0 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(Timer1A3CCR0Event, Timer1A3CCR0DefaultEventHandler, &p);
    
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

/**
 *  \details  This is the default event handler for a Timer1_A3 CCR1-4 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the Timer1A3CCR1Event handle to override this default event 
 *            handler.
 */
unsigned char Timer1A3CCR1DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*Timer1A3CCR1Event)(const void *) = Timer1A3CCR1DefaultEventHandler;   //!< Timer1_A3 CCR1-4 interrupt handle.

/**
 *  \details
 */
#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1A3CCR1InterruptServiceRoutine()
{
  EventParameters p = {TIMERA_NO_EVENT};
  
  // Set the event source parameter.
  switch (__even_in_range(TA1IV, 0x0E))
  {
    case 0: break;
    case 2:
      p.event = TIMERA_CCR1_EVENT;          // CCR1 interrupt pending
      break;
    case 4:
      p.event = TIMERA_CCR2_EVENT;          // CCR2 interrupt pending
      break;
    case 6: break;
    case 8: break;
    case 10: break;
    case 12: break;
    case 14: break;
    default:
      p.event = TIMERA_NO_EVENT;            // No interrupt pending
      break;
  }
  
  // Call the Timer1_A3 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(Timer1A3CCR1Event, Timer1A3CCR1DefaultEventHandler, &p);
  
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

#endif  // TIMER1_A3 SUB MODULE

#endif  // TIMER_A MODULE
