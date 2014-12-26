/**
 *  \file   USCI.c
 */
#include "USCI.h"

#if defined(__MCU_MSP430_USCI)

/**
 *  \details  This is the default event handler for a USCIAB0 Transmit event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the USCIAB0TXEvent handle to override this default event 
 *            handler.
 */
unsigned char USCIAB0TXDefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*USCIAB0TXEvent)(const void *) = USCIAB0TXDefaultEventHandler;//!< USCIAB0 TX interrupt handle.

#if defined(USCIAB0TX_VECTOR)
#pragma vector=USCIAB0TX_VECTOR
__interrupt void __hal_USCIAB0TXInterruptServiceRoutine()
{
  EventParameters p = {USCI_NO_EVENT};  // Event handler parameters
  unsigned char readValue;
  unsigned char isEmpty = 0;
  
  // Isolate source of the interrupt.
  unsigned char event = IFG2;
  event &= IE2;
  
  // Check if the source of the interrupt was USCIA0 or USCIB0.
  if (event & UCA0TXIFG)
  {
    // Check if operation is asynchronous. If so, use a circular buffer to receive
    // data stream. This occurs if the USCI is configured for UART operation.
    if (!(UCA0CTL1 & UCSYNC))
    {
      // Perform.
      if (USCIA0Buffer.count > 0)
      {
        // Read current value from the transmit circular buffer. Load value into the
        // TX buffer register.
        isEmpty = CircularBufferRead(&USCIA0Buffer.tx, &readValue);
        if (!isEmpty)
        {
          UCA0TXBUF = readValue;
          
          // Decrement total count to transmit.
          USCIA0Buffer.count--;

          if (USCIA0Buffer.count <= 0)
          {
            USCIA0Buffer.count = 0;
            IE2 &= ~UCA0TXIE;
            // Set the operation state to done once the last value has been loaded.
            USCIA0Buffer.state = DONE;
          }
        }
        #if !defined(NDEBUG)
        else
        {
          // DEBUG: If data is being lost, turn debug mode on and break here.
          __no_operation(); 
        }
        #endif
      }
      else
      {
        IE2 &= ~UCA0TXIE;
        // Set the operation state to done once the last value has been loaded.
        USCIA0Buffer.state = DONE;
      }
              
      // Store USCIA0 transmit event in parameters.
      p.event = USCIA0_TX_EVENT;
    }
  }
  else if (event & UCB0TXIFG)
  {
    // Clear USCIB0 TX flag.
    IFG2 &= ~UCB0TXIFG;
    
    // Store USCIB0 transmit event in parameters.
    p.event = USCIB0_TX_EVENT;
  }
  
  // Call the USCIAB0 TX ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(USCIAB0TXEvent, USCIAB0TXDefaultEventHandler, &p);
  
  // Check the response for a wake up event to occur.
  if (response & EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}
#endif

/**
 *  \details  This is the default event handler for a USCIAB0 Receive event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the USCIAB0RXEvent handle to override this default event 
 *            handler.
 */
unsigned char USCIAB0RXDefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*USCIAB0RXEvent)(const void *) = USCIAB0RXDefaultEventHandler;  //!< USCIAB0 RX interrupt handle.

#if defined(USCIAB0RX_VECTOR)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void __hal_USCIAB0RXInterruptServiceRoutine()
{
  EventParameters p = {USCI_NO_EVENT};  // Event handler parameters
  unsigned char isFull = 0;
  
  // Isolate source of the interrupt.
  unsigned char event = IFG2;
  event &= IE2;
  
  // Check if the source of the interrupt was USCIA0 or USCIB0.
  if (event & UCA0RXIFG)
  {    
    // Check if operation is asynchronous. If so, use a circular buffer to receive
    // data stream. This occurs if the USCI is configured for UART operation.
    if (!(UCA0CTL1 & UCSYNC))
    {     
      // Write the RX buffer to the circular buffer.
      isFull = CircularBufferWrite(&USCIA0Buffer.rx, UCA0RXBUF);
      #if !defined(NDEBUG)
      if (isFull)
      {
        // DEBUG: If data is being lost, turn debug mode on and break here.
        __no_operation(); 
      }
      #endif
    }
    
    // Store USCIA0 receive event in parameters.
    p.event = USCIA0_RX_EVENT;
  }
  else if (event & UCB0RXIFG)
  {
    // Clear USCIB0 RX flag.
    IFG2 &= ~UCB0RXIFG;
    
    // Store USCIB0 receive event in parameters.
    p.event = USCIB0_RX_EVENT;
  }
  
  // Call the USCIAB0 TX ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(USCIAB0RXEvent, USCIAB0RXDefaultEventHandler, &p);
  
  // Check the response for a wake up event to occur.
  if (response & EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}
#endif

#endif
