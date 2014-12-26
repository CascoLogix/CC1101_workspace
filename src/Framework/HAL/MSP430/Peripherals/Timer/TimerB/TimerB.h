/**
 *  \file   TimerB.h
 */
#ifndef __MCU_MSP430_TIMERB_H
#define __MCU_MSP430_TIMERB_H

#include "../../../Config.h"

#if defined(__MCU_MSP430_TIMERB)

#define STOP_MODE             MC_0
#define UP_MODE               MC_1
#define CONTINUOUS_MODE       MC_2
#define UP_DOWN_MODE          MC_3

#define TIMERB_NO_EVENT       0
#define TIMERB_CCR0_EVENT     0x01
#define TIMERB_CCR1_EVENT     0x02
#define TIMERB_CCR2_EVENT     0x04

#if defined(__MCU_MSP430_TIMERB3)

/**
 *  @fn   __hal_TimerB3EnableInterrupt
 */
#define __hal_TimerB3EnableInterrupt()      TBCTL |= TBIE

/**
 *  @fn   __hal_TimerB3DisableInterrupt
 */
#define __hal_TimerB3DisableInterrupt()     TBCTL &= ~TBIE

/**
 *  @fn   __hal_TimerB3CCR0EnableInterrupt
 */
#define __hal_TimerB3CCR0EnableInterrupt()  TBCCTL0 |= CCIE

/**
 *  @fn   __hal_TimerB3CCR0DisableInterrupt
 */
#define __hal_TimerB3CCR0DisableInterrupt() TBCCTL0 &= ~CCIE

/**
 *  @fn   __hal_TimerB3CCR0ClearInterrupt
 */
#define __hal_TimerB3CCR0ClearInterrupt()   TBCCTL0 &= ~CCIFG

/**
 *  @fn   __hal_TimerB3CCR1EnableInterrupt
 */
#define __hal_TimerB3CCR1EnableInterrupt()  TBCCTL1 |= CCIE

/**
 *  @fn   __hal_TimerB3CCR1DisableInterrupt
 */
#define __hal_TimerB3CCR1DisableInterrupt() TBCCTL1 &= ~CCIE

/**
 *  @fn   __hal_TimerB3CCR1ClearInterrupt
 */
#define __hal_TimerB3CCR1ClearInterrupt()   TBCCTL1 &= ~CCIFG

/**
 *  @fn   __hal_TimerB3CCR2EnableInterrupt
 */
#define __hal_TimerB3CCR2EnableInterrupt()  TBCCTL2 |= CCIE

/**
 *  @fn   __hal_TimerB3CCR2DisableInterrupt
 */
#define __hal_TimerB3CCR2DisableInterrupt() TBCCTL2 &= ~CCIE

/**
 *  @fn   __hal_TimerB3CCR2ClearInterrupt
 */
#define __hal_TimerB3CCR2ClearInterrupt()   TBCCTL2 &= ~CCIFG

/**
 *  @fn   __hal_TimerB3Configure
 */

#define __hal_TimerB3Configure(clockSource, inputDivider, interruptEnable)  \
{                                                                           \
  TBCTL = MC_0 | TBCLR | clockSource | inputDivider | interruptEnable;      \
}

#define __hal_TimerB3CaptureCompareConfigure(ccrId,                                                                                     \
                                      captureMode, captureInputSelect, syncCaptureSource, syncCaptureInput, captureEnable,              \
                                      outputMode, output,                                                                               \
                                      ccie, cci)                                                                                        \
{                                                                                                                                       \
  if (ccrId == 0)                                                                                                                       \
  {                                                                                                                                     \
    TBCCTL0 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output; \
  }                                                                                                                                     \
  else if (ccrId == 1)                                                                                                                  \
  {                                                                                                                                     \
    TBCCTL1 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output; \
  }                                                                                                                                     \
  else if (ccrId == 2)                                                                                                                  \
  {                                                                                                                                     \
    TBCCTL2 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output; \
  }                                                                                                                                     \
}

#define __hal_TimerB3Enable(mode) \
{                                 \
  TBCTL |= mode;                  \
}

#define __hal_TimerB3Clear()      \
{                                 \
  TBCTL |= TBCLR;                 \
}

#define __hal_TimerB3SetCCR(ccrId, value)  \
{                                          \
  if (ccrId == 0)                          \
  {                                        \
    TBCCR0 = value;                        \
  }                                        \
  else if (ccrId == 1)                     \
  {                                        \
    TBCCR1 = value;                        \
  }                                        \
  else if (ccrId == 2)                     \
  {                                        \
    TBCCR2 = value;                        \
  }                                        \
}

#define __hal_TimerB3SetInterrupt()       TBCTL |= TBIE;
#define __hal_TimerB3ClearInterrupt()     TBCTL &= ~TBIE;

#define __hal_TimerB3SetCCRInterrupt(ccrId)   \
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TBCCR0 |= CCIE;                           \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TBCCR1 |= CCIE;                           \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TBCCR2 |= CCIE;                           \
  }                                           \
}

#define __hal_TimerB3ClearCCRInterrupt(ccrId) \
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TBCCR0 &= ~CCIE;                          \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TBCCR1 &= ~CCIE;                          \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TBCCR2 &= ~CCIE;                          \
  }                                           \
}

/**
 *  \fn TimerB3CCR0InterruptServiceRoutine
 */
__interrupt void TimerB3CCR0InterruptServiceRoutine();
extern unsigned char (*TimerB3CCR0Event)(const void *);

/**
 *  \fn TimerB3CCR1InterruptServiceRoutine
 */
__interrupt void TimerB3CCR1InterruptServiceRoutine();
extern unsigned char (*TimerB3CCR1Event)(const void *);

#endif  // TIMERB3 MODULE

#if defined(__MCU_MSP430_TIMER0B3)

/**
 *  @fn   __hal_Timer0B3EnableInterrupt
 */
#define __hal_Timer0B3EnableInterrupt()      TB0CTL |= TBIE

/**
 *  @fn   __hal_Timer0B3DisableInterrupt
 */
#define __hal_Timer0B3DisableInterrupt()     TB0CTL &= ~TBIE

/**
 *  @fn   __hal_Timer0B3CCR0EnableInterrupt
 */
#define __hal_Timer0B3CCR0EnableInterrupt()  TB0CCTL0 |= CCIE

/**
 *  @fn   __hal_Timer0B3CCR0DisableInterrupt
 */
#define __hal_Timer0B3CCR0DisableInterrupt() TB0CCTL0 &= ~CCIE

/**
 *  @fn   __hal_Timer0B3CCR0ClearInterrupt
 */
#define __hal_Timer0B3CCR0ClearInterrupt()   TB0CCTL0 &= ~CCIFG

/**
 *  @fn   __hal_Timer0B3CCR1EnableInterrupt
 */
#define __hal_Timer0B3CCR1EnableInterrupt()  TB0CCTL1 |= CCIE

/**
 *  @fn   __hal_Timer0B3CCR1DisableInterrupt
 */
#define __hal_Timer0B3CCR1DisableInterrupt() TB0CCTL1 &= ~CCIE

/**
 *  @fn   __hal_Timer0B3CCR1ClearInterrupt
 */
#define __hal_Timer0B3CCR1ClearInterrupt()   TB0CCTL1 &= ~CCIFG

/**
 *  @fn   __hal_Timer0B3CCR2EnableInterrupt
 */
#define __hal_Timer0B3CCR2EnableInterrupt()  TB0CCTL2 |= CCIE

/**
 *  @fn   __hal_Timer0B3CCR2DisableInterrupt
 */
#define __hal_Timer0B3CCR2DisableInterrupt() TB0CCTL2 &= ~CCIE

/**
 *  @fn   __hal_Timer0B3CCR2ClearInterrupt
 */
#define __hal_Timer0B3CCR2ClearInterrupt()   TB0CCTL2 &= ~CCIFG

#define __hal_Timer0B3Configure(clockSource, inputDivider, interruptEnable) \
{                                                                           \
  TB0CTL = MC_0 | TBCLR | clockSource | inputDivider | interruptEnable;     \
}

#define __hal_Timer0B3CaptureCompareConfigure(ccrId,                                                                                      \
                                      captureMode, captureInputSelect, syncCaptureSource, syncCaptureInput,  captureEnable,               \
                                      outputMode, output,                                                                                 \
                                      ccie, cci)                                                                                          \
{                                                                                                                                         \
  if (ccrId == 0)                                                                                                                         \
  {                                                                                                                                       \
    TB0CCTL0 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
  else if (ccrId == 1)                                                                                                                    \
  {                                                                                                                                       \
    TB0CCTL1 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
  else if (ccrId == 2)                                                                                                                    \
  {                                                                                                                                       \
    TB0CCTL2 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
}

#define __hal_Timer0B3Enable(mode)          \
{                                           \
  TB0CTL |= mode;                           \
}

#define __hal_Timer0B3Clear()               \
{                                           \
  TB0CTL |= TBCLR;                          \
}

#define __hal_Timer0B3SetCCR(ccrId, value)  \
{                                           \
  if (ccrId == 0)                           \
  {                                         \
    TB0CCR0 = value;                        \
  }                                         \
  else if (ccrId == 1)                      \
  {                                         \
    TB0CCR1 = value;                        \
  }                                         \
  else if (ccrId == 2)                      \
  {                                         \
    TB0CCR2 = value;                        \
  }                                         \
}

#define __hal_Timer0B3SetInterrupt()        TB0CTL |= TBIE;
#define __hal_Timer0B3ClearInterrupt()      TB0CTL &= ~TBIE;

#define __hal_Timer0B3SetCCRInterrupt(ccrId)  \
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TB0CCR0 |= CCIE;                          \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TB0CCR1 |= CCIE;                          \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TB0CCR2 |= CCIE;                          \
  }                                           \
}

#define __hal_Timer0B3ClearCCRInterrupt(ccrId)\
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TB0CCR0 &= ~CCIE;                         \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TB0CCR1 &= ~CCIE;                         \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TB0CCR2 &= ~CCIE;                         \
  }                                           \
}

/**
 *  \fn Timer0B3CCR0InterruptServiceRoutine
 */
__interrupt void Timer0B3CCR0InterruptServiceRoutine();
extern unsigned char (*Timer0B3CCR0Event)(const void *);

/**
 *  \fn Timer0B3CCR1InterruptServiceRoutine
 */
__interrupt void Timer0B3CCR1InterruptServiceRoutine();
extern unsigned char (*Timer0B3CCR1Event)(const void *);

#endif  // TIMER0_B3 SUB MODULE

#if defined(__MCU_MSP430_TIMER1B3)

/**
 *  @fn   __hal_Timer1B3EnableInterrupt
 */
#define __hal_Timer1B3EnableInterrupt()      TB1CTL |= TBIE

/**
 *  @fn   __hal_Timer1B3DisableInterrupt
 */
#define __hal_Timer1B3DisableInterrupt()     TB1CTL &= ~TBIE

/**
 *  @fn   __hal_Timer1B3CCR0EnableInterrupt
 */
#define __hal_Timer1B3CCR0EnableInterrupt()  TB1CCTL0 |= CCIE

/**
 *  @fn   __hal_Timer1B3CCR0DisableInterrupt
 */
#define __hal_Timer1B3CCR0DisableInterrupt() TB1CCTL0 &= ~CCIE

/**
 *  @fn   __hal_Timer1B3CCR0ClearInterrupt
 */
#define __hal_Timer1B3CCR0ClearInterrupt()   TB1CCTL0 &= ~CCIFG

/**
 *  @fn   __hal_Timer1B3CCR1EnableInterrupt
 */
#define __hal_Timer1B3CCR1EnableInterrupt()  TB1CCTL1 |= CCIE

/**
 *  @fn   __hal_Timer1B3CCR1DisableInterrupt
 */
#define __hal_Timer1B3CCR1DisableInterrupt() TB1CCTL1 &= ~CCIE

/**
 *  @fn   __hal_Timer1B3CCR1ClearInterrupt
 */
#define __hal_Timer1B3CCR1ClearInterrupt()   TB1CCTL1 &= ~CCIFG

/**
 *  @fn   __hal_Timer1B3CCR2EnableInterrupt
 */
#define __hal_Timer1B3CCR2EnableInterrupt()  TB1CCTL2 |= CCIE

/**
 *  @fn   __hal_TimerB3CCR2DisableInterrupt
 */
#define __hal_Timer1B3CCR2DisableInterrupt() TB1CCTL2 &= ~CCIE

/**
 *  @fn   __hal_TimerB3CCR2ClearInterrupt
 */
#define __hal_Timer1B3CCR2ClearInterrupt()   TB1CCTL2 &= ~CCIFG

#define __hal_Timer1B3Configure(clockSource, inputDivider, interruptEnable) \
{                                                                           \
  TB1CTL = MC_0 | TBCLR | clockSource | inputDivider | interruptEnable;     \
}

#define __hal_Timer1B3CaptureCompareConfigure(ccrId,                                                                                      \
                                      captureMode, captureInputSelect, syncCaptureSource, syncCaptureInput, captureEnable,                \
                                      outputMode, output,                                                                                 \
                                      ccie, cci)                                                                                          \
{                                                                                                                                         \
  if (ccrId == 0)                                                                                                                         \
  {                                                                                                                                       \
    TB1CCTL0 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
  else if (ccrId == 1)                                                                                                                    \
  {                                                                                                                                       \
    TB1CCTL1 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
  else if (ccrId == 2)                                                                                                                    \
  {                                                                                                                                       \
    TB1CCTL2 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
}

#define __hal_Timer1B3Enable(mode)          \
{                                           \
  TB1CTL |= mode;                           \
}

#define __hal_Timer1B3Clear()               \
{                                           \
  TB1CTL |= TBCLR;                          \
}

#define __hal_Timer1B3SetCCR(ccrId, value)  \
{                                           \
  if (ccrId == 0)                           \
  {                                         \
    TB1CCR0 = value;                        \
  }                                         \
  else if (ccrId == 1)                      \
  {                                         \
    TB1CCR1 = value;                        \
  }                                         \
  else if (ccrId == 2)                      \
  {                                         \
    TB1CCR2 = value;                        \
  }                                         \
}

#define __hal_Timer0B3SetInterrupt()        TB0CTL |= TBIE;
#define __hal_Timer0B3ClearInterrupt()      TB0CTL &= ~TBIE;

#define __hal_Timer1B3SetCCRInterrupt(ccrId)  \
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TB1CCR0 |= CCIE;                          \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TB1CCR1 |= CCIE;                          \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TB1CCR2 |= CCIE;                          \
  }                                           \
}

#define __hal_Timer1B3ClearCCRInterrupt(ccrId)\
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TB1CCR0 &= ~CCIE;                         \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TB1CCR1 &= ~CCIE;                         \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TB1CCR2 &= ~CCIE;                         \
  }                                           \
}

/**
 *  \fn Timer1B3CCR0InterruptServiceRoutine
 */
__interrupt void Timer1B3InterruptServiceRoutine();
extern unsigned char (*Timer1B3CCR0Event)(const void *);

/**
 *  \fn Timer1B3CCR1to4InterruptServiceRoutine
 */
__interrupt void Timer1B3CCR1InterruptServiceRoutine();
extern unsigned char (*Timer1B3CCR1Event)(const void *);

#endif  // TIMER1_B3 SUB MODULE

#endif  // TIMERB MODULE

#endif  // __MCU_MSP430_TIMERB_H
