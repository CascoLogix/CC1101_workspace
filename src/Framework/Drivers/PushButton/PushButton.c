#include "PushButton.h"

#ifdef __BSP_PUSHBUTTON

unsigned char PushButtonGetState(unsigned char pushButtonId)
{
  __BSP_PUSHBUTTON_EVENT_HANDLER(pushButtonId);
  
  return 0xFF;
}

void PushButtonEventHandler(unsigned char pushButtonId, unsigned char minPressTime)
{
  pushButtonTimer.buttonState = PushButtonGetState(pushButtonId);
  if (pushButtonTimer.buttonState == PUSHBUTTON_PRESS)
  {
    // Start timeout timer to determine a push/hold or single click sequence.
    PushButtonTimerEnable(__BSP_PUSHBUTTONTIMER);
  }
  else
  {
    // Switch debounce
    if (pushButtonTimer.count > minPressTime)
    {
      pushButtonTimer.clickCount++;
    }
    pushButtonTimer.count = 0;
  }
}

unsigned char PushButtonDefaultEventHandler(const void * params)
{
  return EVENT_NO_ACTION;
}

unsigned int PushButtonTimerEventHandler(PushButtonTimer * swTimer, unsigned int timeout)
{
  unsigned int action = EVENT_NO_ACTION;

  // If the timer is enabled, perform this operation.
  if (swTimer->enable)
  {
    // Increment the counter.
    swTimer->count++;
    
    if (swTimer->buttonState == PUSHBUTTON_PRESS)
    {
      // Check if the timeout period has expired to determine a hold event.
      if (swTimer->count > timeout)
      {
        // A click & hold event is occurring.
        swTimer->clickHold = PUSHBUTTON_HOLD;
        swTimer->holdCount++;               //!< Hold count does not take into consideration timeout, need to do below
        swTimer->clickCount = 0;
      }
      else
      {
        // Still in the single click time period.
        swTimer->clickHold = PUSHBUTTON_CLICK;
      }
    }
    else
    {
      // Check for end of operation timeout expiration.
      if (swTimer->count > timeout)
      {
        if (swTimer->clickHold == PUSHBUTTON_HOLD)
        {
          swTimer->holdCount += timeout;    //!< Add timeout period to hold count
        }
        action = InterruptServiceRoutineExtension(PushButtonEvent, PushButtonDefaultEventHandler, (const void *)swTimer);
        swTimer->clickCount = 0;
        swTimer->clickHold = 0;
        swTimer->count = 0;
        swTimer->holdCount = 0;
        swTimer->enable = 0;                //!< Disable timer
      }
    }
  }
  
  // No overflow has occurred.
  return action;
}

void PushButtonTimerEnable(PushButtonTimer * swTimer)
{
  swTimer->enable = 1;
}

void PushButtonTimerDisable(PushButtonTimer * swTimer)
{
  swTimer->enable = 0;
}

void PushButtonSetTimerCount(PushButtonTimer * swTimer, unsigned int count)
{
  swTimer->count = count;
}

unsigned char PushButtonGetClickCount(PushButtonTimer * swTimer)
{
  return swTimer->clickCount;
}

void PushButtonSetClickCount(PushButtonTimer * swTimer, unsigned char clickCount)
{
  swTimer->clickCount = clickCount;
}

#endif
