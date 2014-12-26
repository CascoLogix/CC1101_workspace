/**
 *  @fn   SoftwareTimer.h
 */
#ifndef __DRIVER_SOFTWARETIMER_H
#define __DRIVER_SOFTWARETIMER_H

#include "SoftwareTimerStruct.h"

#include "../../BSP/BoardDrivers.h"

void SoftwareTimerConfigure();

unsigned char SoftwareTimerDefaultEventHandler(const void * params);

/**
 *  @fn     SoftwareTimerEventHandler
 *
 *  @brief  Handles checking for timer overflow and incrementing the count. 
 *
 *  @note   Must be called from inside a Timer event handler.
 */
unsigned char SoftwareTimerEventHandler(SoftwareTimer * swTimer);

/**
 *  @fn     SoftwareTimerEnable
 */
void SoftwareTimerEnable(SoftwareTimer * swTimer);

/**
 *  @fn     SoftwareTimerDisable
 */
void SoftwareTimerDisable(SoftwareTimer * swTimer);

/**
 *  @fn     SoftwareTimerSetInterval
 */
void SoftwareTimerSetInterval(SoftwareTimer * swTimer, unsigned int interval);

/**
 *  @fn     SoftwareTimerGetInterval
 */
unsigned int SoftwareTimerGetInterval(SoftwareTimer * swTimer);

/**
 *  @fn     SoftwareTimerSetCount
 */
void SoftwareTimerSetCount(SoftwareTimer * swTimer, unsigned int count);

/**
 *  @fn     SoftwareTimerGetCount
 */
unsigned int SoftwareTimerGetCount(SoftwareTimer * swTimer);

/**
 *  @fn     DelayTimerEventHandler
 */
unsigned char DelayTimerEventHandler(DelayTimer * swTimer);

/**
 *  @fn     Delay
 */
void Delay(unsigned int delayTicks);

#endif  // __DRIVER_SOFTWARETIMER_H
