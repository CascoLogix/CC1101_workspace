/**
 *  \file   WatchdogTimerPlus.h
 *
 *  \brief  Watchdog Timer+ peripheral physical driver definitions.
 */
#ifndef __MCU_MSP430_WATCHDOGTIMERPLUS_H
#define __MCU_MSP430_WATCHDOGTIMERPLUS_H

#include "../../../Config.h"

#if defined(__MCU_MSP430_WATCHDOGTIMERPLUS)

#define WDT_NO_EVENT        0
#define WDT_OVERFLOW_EVENT  1

#define NMI_NO_EVENT        0

/**
 *  @fn     __hal_WatchdogConfigure
 *
 *  @brief  The WDT+ defaults to watchdog mode. Minimal configuration is
 *          necessary.
 */
#define __hal_WatchdogConfigure(nmiEdge, nmiSelect)     \
{                                                       \
  WDTCTL = WDTPW | nmiEdge | nmiSelect;                 \
}

/**
 *  @fn   __hal_WatchdogTimerConfigure
 */
#define __hal_WatchdogTimerConfigure(clockSource, interval) \
{                                                           \
  WDTCTL = WDTPW | WDTTMSEL | clockSource | interval;       \
}

// NMIIE Bit Get/Set
inline unsigned char GetNMIIEBit()  {return (IE1 & NMIIE) >> 4;}
#define SetNMIIEBit(bit)            IE1 = (IE1 & 0xEF) | ((bit << 4) & BIT4)
  
// NMIIFG Bit Get/Set
inline unsigned char GetNMIIFGBit() {return (IFG1 & NMIIFG) >> 4;}
#define SetNMIIFGBit(bit)           IFG1 = (IE1 & 0xEF) | ((bit << 4) & BIT4)

// WDTIE Bit Get/Set
inline unsigned char GetWDTIEBit()  {return (IE1 & WDTIE) >> 0;}
#define SetWDTIEBit(bit)            IE1 = (IE1 & 0xFE) | ((bit << 0) & BIT0)

// WDTIFG Bit Get/Set
inline unsigned char GetWDTIFGBit() {return (IFG1 & WDTIFG) >> 0;}
#define SetWDTIFGBit(bit)           IFG1 = (IE1 & 0xFE) | ((bit << 0) & BIT0)

/**
 *  \fn WatchdogTimerInterruptServiceRoutine
 */
__interrupt void WatchdogTimerInterruptServiceRoutine();
extern unsigned char (*WatchdogTimerEvent)(const void *);

/**
 *  \fn NonMaskableInterruptServiceRoutine
 */
__interrupt void NonMaskableInterruptServiceRoutine();
extern unsigned char (*NonMaskableInterruptEvent)(const void *);

#endif  // WATCHDOG_TIMER_PLUS MODULE

#endif  // __MCU_MSP430_WATCHDOGTIMERPLUS_H
