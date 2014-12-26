#include "SoftwareTimer.h"

#if __BSP_CONFIG_SWTIMER1_ENABLE == 1

void SoftwareTimerConfigure()
{
  unsigned char i;
  
  __BSP_SWTIMER_CONFIGURE();

  for (i = 0; i < __BSP_SWTIMER_COUNT; i++)
  {
    swTimer[i].enable = 0;
    swTimer[i].count = 0;
    swTimer[i].interval = 0;
    swTimer[i].event = SoftwareTimerDefaultEventHandler;
  }
}

unsigned char SoftwareTimerDefaultEventHandler(const void * params)
{
  // The default SW Timer event handler does nothing useful.
  return 0;
}

unsigned char SoftwareTimerEventHandler(SoftwareTimer * swTimer)
{
  EventParameters p = {0};                  //!< No event parameters are currently passed.
  
  // If the timer is enabled, perform this operation.
  if (swTimer->enable)
  {
    // Increment the counter.
    swTimer->count++;

    if (swTimer->count >= swTimer->interval)
    {
      // Clear the counter.
      swTimer->count = 0;
      
      // An overflow has occurred and the timer has started over.
      return InterruptServiceRoutineExtension(swTimer->event,
                                              SoftwareTimerDefaultEventHandler,
                                              &p);
    }
  }
  
  // No overflow has occurred.
  return EVENT_NO_ACTION;
}

void SoftwareTimerEnable(SoftwareTimer * swTimer)
{
  swTimer->enable = 1;
}

void SoftwareTimerDisable(SoftwareTimer * swTimer)
{
  swTimer->enable = 0;
}

void SoftwareTimerSetInterval(SoftwareTimer * swTimer, unsigned int interval)
{
  swTimer->interval = interval;
}

unsigned int SoftwareTimerGetInterval(SoftwareTimer * swTimer)
{
  return swTimer->interval;
}

void SoftwareTimerSetCount(SoftwareTimer * swTimer, unsigned int count)
{
  swTimer->count = count;
}

unsigned int SoftwareTimerGetCount(SoftwareTimer * swTimer)
{
  return swTimer->count;
}

unsigned char DelayTimerEventHandler(DelayTimer * swTimer)
{
  // If the timer is enabled, perform this operation.
  if (swTimer->enable)
  {
    // Increment the counter.
    swTimer->count++;
    
    if (swTimer->count >= swTimer->interval)
    {
      // Clear the counter.
      swTimer->count = 0;
      swTimer->done = 1;
      
      // An overflow has occurred and the timer has started over.
      return EVENT_WAKE_UP;
    }
  }
  
  // No overflow has occurred.
  return EVENT_NO_ACTION;
}

void Delay(unsigned int delayTicks)
{
  // Set the delay period and enable the timer.
  delayTimer.interval = delayTicks;
  delayTimer.enable = 1;
  
  // Wait until the count has surpassed the desired tick interval.
  while (delayTimer.done != 1)
  {
    // Go to sleep. If another interrupt wakes the processor, we won't exit this
    // loop until the desired delay has been reached.
    __low_power_mode_0();
    __no_operation();
  }
  
  // Manually clear the counter to ensure it starts at 0 everytime. Disable the
  // counter until the next delay call.
  delayTimer.enable = 0;
  delayTimer.done = 0;
}

#endif
