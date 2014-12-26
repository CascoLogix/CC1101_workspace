/**
 *  @file   Timer.h
 */
#ifndef __DRIVER_TIMER_H
#define __DRIVER_TIMER_H

#include "../../BSP/BoardDrivers.h"

/**
 *  @fn   TimerConfigure
 */
#define TimerConfigure(timerId)             __BSP_TIMER_CONFIGURE(timerId)

/**
 *  @fn   TimerEnableInterrupt
 */
#define TimerEnableInterrupt(timerId)       __BSP_TIMER_ENABLE_INTERRUPT(timerId)

/**
 *  @fn   TimerDisableInterrupt
 */
#define TimerDisableInterrupt(timerId)      __BSP_TIMER_DISABLE_INTERRUPT(timerId)

/**
 *  @fn   TimerEnable
 */
#define TimerEnable(timerId, mode)          __BSP_TIMER_ENABLE(timerId, mode)

/**
 *  @fn   TimerSetCount
 */
#define TimerSetCount(timerId, value)       __BSP_TIMER_SET_COUNT(timerId, value)

/**
 *  @fn   TimerGetCount
 */
#define TimerGetCount(timerId)              __BSP_TIMER_GET_COUNT(timerId)

/**
 *  @fn   TimerSetCCR
 */
#define TimerSetCCR(timerId, ccrId, value)  __BSP_TIMER_SET_CCR(timerId, ccrId, value)

/**
 *  @fn   TimerGetCCR
 */
#define TimerGetCCR(timerId, ccrId)         __BSP_TIMER_GET_CCR(timerId, ccrId)

/**
 *  @fn   TimerCCREnableInterrupt
 */
#define TimerCCREnableInterrupt(timerId, ccrId)   __BSP_TIMER_CCR_ENABLE_INTERRUPT(timerId, ccrId)

/**
 *  @fn   TimerCCRDisableInterrupt
 */
#define TimerCCRDisableInterrupt(timerId, ccrId)  __BSP_TIMER_CCR_DISABLE_INTERRUPT(timerId, ccrId)

/**
 *  @fn   TimerCCRClearInterrupt
 */
#define TimerCCRClearInterrupt(timerId, ccrId)   __BSP_TIMER_CCR_CLEAR_INTERRUPT(timerId, ccrId)

#endif  // __DRIVER_TIMER_H
