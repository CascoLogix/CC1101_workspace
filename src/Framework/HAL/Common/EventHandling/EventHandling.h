/**
 *  @file   EventHandling.h
 */
#ifndef __HAL_COMMON_EVENTHANDLING_H
#define __HAL_COMMON_EVENTHANDLING_H

#include "../CommonDefinitions.h"

typedef struct EventParameters
{
  unsigned char event;
} EventParameters;

/**
 *  @brief  Possible responses from an event handler to an ISR after an event has
 *          been processed. This allows application code to perform a subset of
 *          actions that an ISR may perform such as waking up.
 */
#define EVENT_NO_ACTION                     0x00
#define EVENT_WAKE_UP                       0x01

/**
 *  @fn     AttachEvent
 *
 *  @brief  
 */
void AttachEvent(unsigned char (**Event)(const void *), unsigned char (*pHandler)(const void *));

/**
 *  @fn     DetachEvent
 *
 *  @brief  
 */
void DetachEvent(unsigned char (**Event)(const void *));

/**
 *  @fn     InterruptServiceRoutineExtension
 *
 *  @brief  
 */
unsigned char InterruptServiceRoutineExtension(unsigned char (*EventHandler)(const void *), unsigned char (*DefaultEventHandler)(const void *), const void * eventParameters);

#endif  // __HAL_COMMON_EVENTHANDLING_H
