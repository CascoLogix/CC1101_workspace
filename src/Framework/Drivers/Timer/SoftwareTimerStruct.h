/**
 *  @file   SoftwareTimerStruct.h
 */
#ifndef __DRIVER_SOFTWARETIMER_STRUCT_H
#define __DRIVER_SOFTWARETIMER_STRUCT_H

typedef struct SoftwareTimer
{
  volatile unsigned char enable;                     //!< Enable timer operation
  volatile unsigned int count;                       //!< Current count value
  volatile unsigned int interval;                    //!< Overflow count
  unsigned char (*event)(const void *);     //!< Event handle
} SoftwareTimer;

typedef struct DelayTimer
{
  volatile unsigned char enable;                     //!< Enable timer operation
  volatile unsigned int count;                       //!< Current count value
  volatile unsigned int interval;                    //!< Overflow count
  volatile unsigned char done;                       //!< Overflow flag
} DelayTimer;

typedef struct PushButtonTimer
{
  volatile unsigned char enable;                     //!< Enable timer operation
  volatile unsigned int count;                       //!< Current timer count value
  volatile unsigned char buttonState;                //!< Current state of the button (press or release)
  volatile unsigned char clickHold;                  //!< Single click or click & hold
  volatile unsigned char clickCount;                 //!< Single click count
  volatile unsigned int holdCount;                   //!< Time button held
} PushButtonTimer;

#endif  // __DRIVER_SOFTWARETIMER_STRUCT_H
