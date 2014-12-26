/**
 *  \file   TimerB.c
 */
#include "TimerB.h"

#if defined(__MCU_MSP430_TIMERB)

#if defined(__MCU_MSP430_TIMERB3)

/**
 *  \details  This is the default event handler for a Timer_B3 CCR0 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the TimerB3CCR0Event handle to override this default event 
 *            handler.
 */
unsigned char TimerB3CCR0DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*TimerB3CCR0Event)(const void *) = TimerB3CCR0DefaultEventHandler;   //!< Timer0_B3 CCR0 interrupt handle.

#pragma vector=TIMERB0_VECTOR
__interrupt void TimerB3CCR0InterruptServiceRoutine()
{
  EventParameters p = {TIMERB_CCR0_EVENT};
  
  // Clear CCR0 flag.
  TBCCTL0 &= ~CCIFG;
  
  // Call the Timer0_B3 CCR0 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(TimerB3CCR0Event, TimerB3CCR0DefaultEventHandler, &p);
    
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

/**
 *  \details  This is the default event handler for a Timer_B3 CCR1 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the TimerB3CCR1Event handle to override this default event 
 *            handler.
 */
unsigned char TimerB3CCR1DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*TimerB3CCR1Event)(const void *) = TimerB3CCR1DefaultEventHandler;   //!< Timer_B3 CCR1 interrupt handle.

#pragma vector=TIMERB1_VECTOR
__interrupt void TimerB3CCR1InterruptServiceRoutine()
{
  EventParameters p = {TIMERB_NO_EVENT};

  // Set the event source parameter.
  switch (__even_in_range(TBIV, 14))
  {
    case 0: break;
    case 2:
      p.event = TIMERB_CCR1_EVENT;          // CCR1 interrupt pending
      break;
    case 4:
      p.event = TIMERB_CCR2_EVENT;          // CCR2 interrupt pending
      break;
    case 6: break;
    case 8: break;
    case 10: break;
    case 12: break;
    case 14: break;
    default:
      p.event = TIMERB_NO_EVENT;            // No interrupt pending
      break;
  }
  
  // Call the Timer0_B3 CCR0 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(TimerB3CCR1Event, TimerB3CCR1DefaultEventHandler, &p);
    
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}
#endif  // TIMER_B3 MODULE

#if defined(__MCU_MSP430_TIMER0B3)

/**
 *  \details  This is the default event handler for a Timer0_B3 CCR0 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the Timer0B3CCR0Event handle to override this default event 
 *            handler.
 */
unsigned char Timer0B3CCR0DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*Timer0B3CCR0Event)(const void *) = Timer0B3CCR0DefaultEventHandler;   //!< Timer0_B3 CCR0 interrupt handle.

#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer0B3CCR0InterruptServiceRoutine()
{
  EventParameters p = {TIMERB_CCR0_EVENT};
  
  // Clear CCR0 flag.
  TB0CCTL0 &= ~CCIFG;
  
  // Call the Timer0_B3 CCR0 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(Timer0B3CCR0Event, Timer0B3CCR0DefaultEventHandler, &p);
    
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

/**
 *  \details  This is the default event handler for a Timer0_B3 CCR1 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the Timer0B3CCR1Event handle to override this default event 
 *            handler.
 */
unsigned char Timer0B3CCR1DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*Timer0B3CCR1Event)(const void *) = Timer0B3CCR1DefaultEventHandler;   //!< Timer0_B3 CCR1 interrupt handle.

#pragma vector=TIMER0_B1_VECTOR
__interrupt void Timer0B3CCR1InterruptServiceRoutine()
{
  EventParameters p = {TIMERB_NO_EVENT};

  // Set the event source parameter.
  switch (__even_in_range(TB0IV, 14))
  {
    case 0: break;
    case 2:
      p.event = TIMERB_CCR1_EVENT;          // CCR1 interrupt pending
      break;
    case 4:
      p.event = TIMERB_CCR2_EVENT;          // CCR2 interrupt pending
      break;
    case 6: break;
    case 8: break;
    case 10: break;
    case 12: break;
    case 14: break;
    default:
      p.event = TIMERB_NO_EVENT;            // No interrupt pending
      break;
  }
  
  // Call the Timer0_B3 CCR0 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(Timer0B3CCR1Event, Timer0B3CCR1DefaultEventHandler, &p);
    
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

#endif  // TIMER0_B3 SUB MODULE

#if defined(__MCU_MSP430_TIMER1B3)

/**
 *  \details  This is the default event handler for a Timer1_B3 CCR0 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the Timer1B3CCR0Event handle to override this default event 
 *            handler.
 */
unsigned char Timer1B3CCR0DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*Timer1B3CCR0Event)(const void *) = Timer1B3CCR0DefaultEventHandler;   //!< Timer1_B3 CCR0 interrupt handle.

/**
 *  \details
 */
#pragma vector=TIMER1_B0_VECTOR
__interrupt void Timer1B3CCR0InterruptServiceRoutine()
{
  EventParameters p = {TIMERB_CCR0_EVENT};
  
  // Clear CCR0 flag.
  TB1CCTL0 &= ~CCIFG;
  
  // Call the Timer0_B3 CCR0 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(Timer1B3CCR0Event, Timer1B3CCR0DefaultEventHandler, &p);
    
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

/**
 *  \details  This is the default event handler for a Timer1_B3 CCR1-4 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the Timer1B3CCR1Event handle to override this default event 
 *            handler.
 */
unsigned char Timer1B3CCR1DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*Timer1B3CCR1Event)(const void *) = Timer1B3CCR1DefaultEventHandler;   //!< Timer1_B3 CCR1-4 interrupt handle.

/**
 *  \details
 */
#pragma vector=TIMER1_B1_VECTOR
__interrupt void Timer1B3CCR1InterruptServiceRoutine()
{
  EventParameters p = {TIMERB_NO_EVENT};
  
  // Set the event source parameter.
  switch (__even_in_range(TB1IV, 0x0E))
  {
    case 0: break;
    case 2:
      p.event = TIMERB_CCR1_EVENT;          // CCR1 interrupt pending
      break;
    case 4:
      p.event = TIMERB_CCR2_EVENT;          // CCR2 interrupt pending
      break;
    case 6: break;
    case 8: break;
    case 10: break;
    case 12: break;
    case 14: break;
    default:
      p.event = TIMERB_NO_EVENT;            // No interrupt pending
      break;
  }
  
  // Call the Timer1_B3 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(Timer1B3CCR1Event, Timer1B3CCR1DefaultEventHandler, &p);
  
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

#endif  // TIMER1_B3 SUB MODULE

#endif  // TIMER_B MODULE
