/**
 *  @file   BasicClockModulePlus.h
 */
#ifndef __MCU_MSP430_BASICCLOCKMODULEPLUS_H
#define __MCU_MSP430_BASICCLOCKMODULEPLUS_H

#include "../../../Config.h"

#if defined(__MCU_MSP430_BASICCLOCKMODULEPLUS)

/**
 *  @fn   __hal_BasicClockModulePlusConfigure
 */
#define __hal_BasicClockModulePlusConfigure(clockRate, clockDCO, clockRange, clockResistor, \
                                            mclkSource, smclkSource,                        \
                                            mclkDiv, smclkDiv, aclkDiv,                     \
                                            xt2Enable, xt2Range,                            \
                                            lfxt1Mode, lfxt1Select, lfxt1Range, lfxt1Cap)   \
{                                                                                           \
  DCOCTL = clockDCO;                                                                        \
  BCSCTL1 = clockRange | xt2Enable | lfxt1Mode | aclkDiv;                                   \
  BCSCTL2 = clockResistor | mclkSource | smclkSource | mclkDiv | smclkDiv;                  \
  BCSCTL3 = xt2Range | lfxt1Select | lfxt1Range | lfxt1Cap;                                 \
}

// OFIE Bit Get/Set
#define GetOFIEBit()                    ((IE1 & OFIE) / OFIE)
#define SetOFIEBit(bit)			IE1 = (IE1 & ~OFIE) | ((bit & BIT0) * OFIE)

/**
 *  @fn GetOFIFGBit();
 */
#define GetOFIFGBit()                   ((IFG1 & OFIFG) / OFIFG)
#define SetOFIFGBit(bit)		IFG1 = (IFG1 & ~OFIFG) | ((bit & BIT0) * OFIFG)

#endif  // BASIC_CLOCK_MODULE_PLUS MODULE

#endif  // __MCU_MSP430_BASICCLOCKMODULEPLUS_H
