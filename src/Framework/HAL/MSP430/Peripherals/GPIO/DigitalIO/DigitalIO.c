/**
 *  \file   DigitalIO.c
 */
#include "DigitalIO.h"

#if defined(__MCU_MSP430_DIGITALIO)

/**
 *  @details
 */
void SetDigitalIOOutputPort(enum PORT port, unsigned char pin)
{
  #if defined(__MCU_MSP430_DIGITALIO)
    #if defined(__MCU_MSP430_DIGITALIO_PORT1)
      if (port == PORT1)
      {
        P1OUT |= pin;
      }
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT2)
      if (port == PORT2)
      {
        P2OUT |= pin;
      }
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT3)
      if (port == PORT3)
      {
        P3OUT |= pin;
      }
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT4)
      if (port == PORT4)
      {
        P4OUT |= pin;
      }
    #endif
  #endif
}

/**
 *  @details
 */
void ClearDigitalIOOutputPort(unsigned char port, unsigned char pin)
{
  #if defined(__MCU_MSP430_DIGITALIO)
    #if defined(__MCU_MSP430_DIGITALIO_PORT1)
      if (port == PORT1)
      {
        P1OUT &= ~pin;
      }
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT2)
      if (port == PORT2)
      {
        P2OUT &= ~pin;
      }
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT3)
      if (port == PORT3)
      {
        P3OUT &= ~pin;
      }
    #endif
    #if defined(__MCU_MSP430_DIGITALIO_PORT4)
      if (port == PORT4)
      {
        P4OUT &= ~pin;
      }
    #endif
  #endif
}

#if defined(__MCU_MSP430_DIGITALIO_PORT1)

/**
 *  \details  This is the default event handler for a Digital I/O Port1 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the DigitalIOPort1Event handle to override this default event 
 *            handler.
 */
unsigned char DigitalIOPort1DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*DigitalIOPort1Event)(const void *) = DigitalIOPort1DefaultEventHandler; //!< Port 1 interrupt handle.

#pragma vector=PORT1_VECTOR
__interrupt void DigitalIOPort1InterruptServiceRoutine()
{
  EventParameters p = {(PORT1_NO_EVENT)};

  unsigned char event = P1IFG;
  event &= P1IE;
  P1IFG &= ~event;
  
  // Set the event source parameter.
  p.event = event;

//  // Check if BIT0 is set and interrupt is enabled.
//  if (event & BIT0)
//  {
//    p.event |= PORT1_0_EVENT;
//  }
//  
//  // Check if BIT1 is set and interrupt is enabled.
//  if (event & BIT1)
//  {
//    p.event |= PORT1_1_EVENT;
//  }
//  
//  // Check if BIT2 is set and interrupt is enabled.  
//  if (event & BIT2)
//  {
//    p.event |= PORT1_2_EVENT;
//  }
//  
//  // Check if BIT3 is set and interrupt is enabled.  
//  if (event & BIT3)
//  {
//    p.event |= PORT1_3_EVENT;
//  }
//  
//  // Check if BIT4 is set and interrupt is enabled.  
//  if (event & BIT4)
//  {
//    p.event |= PORT1_4_EVENT;
//  }
//  
//  // Check if BIT5 is set and interrupt is enabled.  
//  if (event & BIT5)
//  {
//    p.event |= PORT1_5_EVENT;
//  }
//  
//  // Check if BIT6 is set and interrupt is enabled.  
//  if (event & BIT6)
//  {
//    p.event |= PORT1_6_EVENT;
//  }
//  
//  // Check if BIT7 is set and interrupt is enabled.  
//  if (event & BIT7)
//  {
//    p.event |= PORT1_7_EVENT;
//  }

  // Call the Digital IO Port1 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(DigitalIOPort1Event, DigitalIOPort1DefaultEventHandler, &p);
  
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}    

#endif  // DIGITAL I/O PORT 1

#if defined(__MCU_MSP430_DIGITALIO_PORT2)

/**
 *  \details  This is the default event handler for a Digital I/O Port2 event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the DigitalIOPort2Event handle to override this default event 
 *            handler.
 */
unsigned char DigitalIOPort2DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*DigitalIOPort2Event)(const void *) = DigitalIOPort2DefaultEventHandler; //!< Port 2 interrupt handle.

#pragma vector=PORT2_VECTOR
__interrupt void DigitalIOPort2InterruptServiceRoutine()
{
  EventParameters p = {(PORT2_NO_EVENT)};
  
  unsigned char event = P2IFG;
  event &= P2IE;
  P2IFG &= ~event;

  // Set the event source parameter.
  p.event = event;

//  // Check if BIT0 is set and interrupt is enabled.
//  if (event & BIT0)
//  {
//    p.event |= PORT2_0_EVENT;
//  }
//  
//  // Check if BIT1 is set and interrupt is enabled.
//  if (event & BIT1)
//  {
//    p.event |= PORT2_1_EVENT;
//  }
//  
//  // Check if BIT2 is set and interrupt is enabled.  
//  if (event & BIT2)
//  {
//    p.event |= PORT2_2_EVENT;
//  }
//  
//  // Check if BIT3 is set and interrupt is enabled.  
//  if (event & BIT3)
//  {
//    p.event |= PORT2_3_EVENT;
//  }
//  
//  // Check if BIT4 is set and interrupt is enabled.  
//  if (event & BIT4)
//  {
//    p.event |= PORT2_4_EVENT;
//  }
//  
//  // Check if BIT5 is set and interrupt is enabled.  
//  if (event & BIT5)
//  {
//    p.event |= PORT2_5_EVENT;
//  }
//  
//  // Check if BIT6 is set and interrupt is enabled.  
//  if (event & BIT6)
//  {
//    p.event |= PORT2_6_EVENT;
//  }
//  
//  // Check if BIT7 is set and interrupt is enabled.  
//  if (event & BIT7)
//  {
//    p.event |= PORT2_7_EVENT;
//  }
  
  // Call the Digital IO Port2 ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(DigitalIOPort2Event, DigitalIOPort2DefaultEventHandler, &p);
  
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}

#endif  // DIGITAL I/O PORT 2

#endif  // DIGITAL I/O MODULE
