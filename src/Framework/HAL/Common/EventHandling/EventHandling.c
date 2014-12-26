/**
 *  \file   EventHandling.c
 */
#include "EventHandling.h"

/**
 *  \details  Attaches an event to a user application event handler. Any
 *            triggered interrupt will then go to the new event handler instead
 *            of the previous, which is most likely the default.
 */
void AttachEvent(unsigned char (**Event)(const void *), unsigned char (*pHandler)(const void *))
{
  *(Event) = pHandler;
}

/**
 *  \details  Detaches an event from the currently attached user application 
 *            handler and points to NULL.
 *
 *  \note     Pointing to NULL is valid because the interrupt service routine
 *            extension will point the event to the default event handler
 *            automatically.
 */
void DetachEvent(unsigned char (**Event)(const void *))
{
  *(Event) = NULL; 
}

/**
 *  \details  This procedure extends an interrupt service routine to allow for
 *            application specific code to be handled while keeping the ISR
 *            generic. 
 *            
 *  \note     It should be noted that this function still resides inside of the 
 *            ISR and any event handler attached should act as if it were the 
 *            ISR.
 */
unsigned char InterruptServiceRoutineExtension(unsigned char (*EventHandler)(const void *), unsigned char (*DefaultEventHandler)(const void *), const void * eventParameters)
{
  // Verify that the handler is pointing to a valid function.
  if (EventHandler == NULL)
  {
    // Change the location of the handler to point to the default. This will
    // prevent undefined behavior.
    EventHandler = DefaultEventHandler;
  }
  
  // Run the event handler with the provided parameters.
  return EventHandler(eventParameters);
}
