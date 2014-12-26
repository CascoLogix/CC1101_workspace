/**
 *  \file   ADC10.c
 */
#include "ADC10.h"

#if defined(__MCU_MSP430_ADC10)

#ifndef USE_INLINE

void __hal_ADC10StartSingleConversion(unsigned int channel)
{
  // Configure analog enable pins if channel is analog.
  ADC10AE0 = (channel & 0xFF);
  #ifdef ADC10AE1
  ADC10AE1 = (channel & 0xFF00);
  #endif
  ADC10CTL0 |= ENC + ADC10SC;           //!< Enable and start conversion
}

#endif

/**
 *  \details  This is the default event handler for a ADC10 conversion event. 
 *            It does not perform anything useful. The user must attach an event 
 *            to the ADC10Event handle to override this default event handler.
 */
unsigned char ADC10DefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned char (*ADC10Event)(const void *) = ADC10DefaultEventHandler;//!< ADC10 interrupt handle.

/**
 *  \details
 */
#if defined(ADC10_VECTOR)
#pragma vector=ADC10_VECTOR
__interrupt void __hal_ADC10InterruptServiceRoutine()
{
  // NOTE: The interrupt flag is automatically cleared.
  // Pulse the enable conversion bit. Mainly for interrupt driven ADC operation.
  ADC10CTL0 &= ~ENC;
  ADC10CTL0 |= ENC;
  
  EventParameters p = {ADC10_NO_EVENT};
  
  // Check if the data transfer control is being used.
  if (ADC10DTC1 != 0)
  {
    // TODO: Determine implementation for using the data transfer control. When
    // an interrupt occurs and the DTC is used, a block transfer is completed
    // and the internal transfer counter 'n' = 0.
  }
  else
  {
    // For a normal conversion, the result is loaded into ADC10MEM.
  }

  p.event = (ADC10CTL1 & INCH_15) >> 12;
  
  // Call the USCIAB0 TX ISR extension to handle this event.
  unsigned char response = InterruptServiceRoutineExtension(ADC10Event, ADC10DefaultEventHandler, &p);
  
  // Check the response for a wake up event to occur.
  if (response == EVENT_WAKE_UP)
  {
    // Come out of sleep.
    __low_power_mode_off_on_exit();
  }
}
#endif

#endif  // ADC10
