/**
 *  \file   TimerA.h
 */
#ifndef __MCU_MSP430_TIMERA_H
#define __MCU_MSP430_TIMERA_H

#include "../../../Config.h"

#if defined(__MCU_MSP430_TIMERA)

#define STOP_MODE             MC_0
#define UP_MODE               MC_1
#define CONTINUOUS_MODE       MC_2
#define UP_DOWN_MODE          MC_3

#define TIMERA_NO_EVENT       0
#define TIMERA_CCR0_EVENT     0x01
#define TIMERA_CCR1_EVENT     0x02
#define TIMERA_CCR2_EVENT     0x04

#if defined(__MCU_MSP430_TIMERA3)

/**
 *  @fn   __hal_TimerA3EnableInterrupt
 */
#define __hal_TimerA3EnableInterrupt()      TACTL |= TAIE

/**
 *  @fn   __hal_TimerA3DisableInterrupt
 */
#define __hal_TimerA3DisableInterrupt()     TACTL &= ~TAIE

/**
 *  @fn   __hal_TimerA3CCR0EnableInterrupt
 */
#define __hal_TimerA3CCR0EnableInterrupt()  TACCTL0 |= CCIE

/**
 *  @fn   __hal_TimerA3CCR0DisableInterrupt
 */
#define __hal_TimerA3CCR0DisableInterrupt() TACCTL0 &= ~CCIE

/**
 *  @fn   __hal_TimerA3CCR0ClearInterrupt
 */
#define __hal_TimerA3CCR0ClearInterrupt()   TACCTL0 &= ~CCIFG

/**
 *  @fn   __hal_TimerA3CCR1EnableInterrupt
 */
#define __hal_TimerA3CCR1EnableInterrupt()  TACCTL1 |= CCIE

/**
 *  @fn   __hal_TimerA3CCR1DisableInterrupt
 */
#define __hal_TimerA3CCR1DisableInterrupt() TACCTL1 &= ~CCIE

/**
 *  @fn   __hal_TimerA3CCR1ClearInterrupt
 */
#define __hal_TimerA3CCR1ClearInterrupt()   TACCTL1 &= ~CCIFG

/**
 *  @fn   __hal_TimerA3CCR2EnableInterrupt
 */
#define __hal_TimerA3CCR2EnableInterrupt()  TACCTL2 |= CCIE

/**
 *  @fn   __hal_TimerA3CCR2DisableInterrupt
 */
#define __hal_TimerA3CCR2DisableInterrupt() TACCTL2 &= ~CCIE

/**
 *  @fn   __hal_TimerA3CCR2ClearInterrupt
 */
#define __hal_TimerA3CCR2ClearInterrupt()   TACCTL2 &= ~CCIFG

/**
 *  @fn   __hal_TimerA3Configure
 */
#define __hal_TimerA3Configure(clockSource, inputDivider, interruptEnable)  \
{                                                                           \
  TACTL = MC_0 | TACLR | clockSource | inputDivider | interruptEnable;      \
}

#define __hal_TimerA3CaptureCompareConfigure(ccrId,                                                                                     \
                                      captureMode, captureInputSelect, syncCaptureSource, syncCaptureInput, captureEnable,              \
                                      outputMode, output,                                                                               \
                                      ccie, cci)                                                                                        \
{                                                                                                                                       \
  if (ccrId == 0)                                                                                                                       \
  {                                                                                                                                     \
    TACCTL0 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output; \
  }                                                                                                                                     \
  else if (ccrId == 1)                                                                                                                  \
  {                                                                                                                                     \
    TACCTL1 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output; \
  }                                                                                                                                     \
  else if (ccrId == 2)                                                                                                                  \
  {                                                                                                                                     \
    TACCTL2 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output; \
  }                                                                                                                                     \
}

#define __hal_TimerA3Enable(mode) \
{                                 \
  TACTL |= mode;                  \
}

#define __hal_TimerA3Clear()      \
{                                 \
  TACTL |= TACLR;                 \
}

#define __hal_TimerA3SetCCR(ccrId, value)  \
{                                          \
  if (ccrId == 0)                          \
  {                                        \
    TACCR0 = value;                        \
  }                                        \
  else if (ccrId == 1)                     \
  {                                        \
    TACCR1 = value;                        \
  }                                        \
  else if (ccrId == 2)                     \
  {                                        \
    TACCR2 = value;                        \
  }                                        \
}

#define __hal_TimerA3SetInterrupt()       TACTL |= TAIE;
#define __hal_TimerA3ClearInterrupt()     TACTL &= ~TAIE;

#define __hal_TimerA3SetCCRInterrupt(ccrId)   \
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TACCR0 |= CCIE;                           \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TACCR1 |= CCIE;                           \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TACCR2 |= CCIE;                           \
  }                                           \
}

#define __hal_TimerA3ClearCCRInterrupt(ccrId) \
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TACCR0 &= ~CCIE;                          \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TACCR1 &= ~CCIE;                          \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TACCR2 &= ~CCIE;                          \
  }                                           \
}

/**
 *  \fn TimerA3CCR0InterruptServiceRoutine
 */
__interrupt void TimerA3CCR0InterruptServiceRoutine();
extern unsigned char (*TimerA3CCR0Event)(const void *);

/**
 *  \fn TimerA3CCR1InterruptServiceRoutine
 */
__interrupt void TimerA3CCR1InterruptServiceRoutine();
extern unsigned char (*TimerA3CCR1Event)(const void *);

#endif  // TIMER_A3 MODULE

#if defined(__MCU_MSP430_TIMER0A3)

/**
 *  @fn   __hal_Timer0A3EnableInterrupt
 */
#define __hal_Timer0A3EnableInterrupt()      TA0CTL |= TAIE

/**
 *  @fn   __hal_Timer0A3DisableInterrupt
 */
#define __hal_Timer0A3DisableInterrupt()     TA0CTL &= ~TAIE

/**
 *  @fn   __hal_Timer0A3CCR0EnableInterrupt
 */
#define __hal_Timer0A3CCR0EnableInterrupt()  TA0CCTL0 |= CCIE

/**
 *  @fn   __hal_Timer0A3CCR0DisableInterrupt
 */
#define __hal_Timer0A3CCR0DisableInterrupt() TA0CCTL0 &= ~CCIE

/**
 *  @fn   __hal_Timer0A3CCR0ClearInterrupt
 */
#define __hal_Timer0A3CCR0ClearInterrupt()   TA0CCTL0 &= ~CCIFG

/**
 *  @fn   __hal_Timer0A3CCR1EnableInterrupt
 */
#define __hal_Timer0A3CCR1EnableInterrupt()  TA0CCTL1 |= CCIE

/**
 *  @fn   __hal_Timer0A3CCR1DisableInterrupt
 */
#define __hal_Timer0A3CCR1DisableInterrupt() TA0CCTL1 &= ~CCIE

/**
 *  @fn   __hal_Timer0A3CCR1ClearInterrupt
 */
#define __hal_Timer0A3CCR1ClearInterrupt()   TA0CCTL1 &= ~CCIFG

/**
 *  @fn   __hal_Timer0A3CCR2EnableInterrupt
 */
#define __hal_Timer0A3CCR2EnableInterrupt()  TA0CCTL2 |= CCIE

/**
 *  @fn   __hal_Timer0A3CCR2DisableInterrupt
 */
#define __hal_Timer0A3CCR2DisableInterrupt() TA0CCTL2 &= ~CCIE

/**
 *  @fn   __hal_Timer0A3CCR2ClearInterrupt
 */
#define __hal_Timer0A3CCR2ClearInterrupt()   TA0CCTL2 &= ~CCIFG

#define __hal_Timer0A3Configure(clockSource, inputDivider, interruptEnable) \
{                                                                           \
  TA0CTL = MC_0 | TACLR | clockSource | inputDivider | interruptEnable;     \
}

#define __hal_Timer0A3CaptureCompareConfigure(ccrId,                                                                                      \
                                      captureMode, captureInputSelect, syncCaptureSource, syncCaptureInput,  captureEnable,               \
                                      outputMode, output,                                                                                 \
                                      ccie, cci)                                                                                          \
{                                                                                                                                         \
  if (ccrId == 0)                                                                                                                         \
  {                                                                                                                                       \
    TA0CCTL0 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
  else if (ccrId == 1)                                                                                                                    \
  {                                                                                                                                       \
    TA0CCTL1 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
  else if (ccrId == 2)                                                                                                                    \
  {                                                                                                                                       \
    TA0CCTL2 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
}

#define __hal_Timer0A3Enable(mode)          \
{                                           \
  TA0CTL |= mode;                           \
}

#define __hal_Timer0A3Clear()               \
{                                           \
  TA0CTL |= TACLR;                          \
}

#define __hal_Timer0A3SetCCR(ccrId, value)  \
{                                           \
  if (ccrId == 0)                           \
  {                                         \
    TA0CCR0 = value;                        \
  }                                         \
  else if (ccrId == 1)                      \
  {                                         \
    TA0CCR1 = value;                        \
  }                                         \
  else if (ccrId == 2)                      \
  {                                         \
    TA0CCR2 = value;                        \
  }                                         \
}

#define __hal_Timer0A3SetInterrupt()        TA0CTL |= TAIE;
#define __hal_Timer0A3ClearInterrupt()      TA0CTL &= ~TAIE;

#define __hal_Timer0A3SetCCRInterrupt(ccrId)  \
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TA0CCR0 |= CCIE;                          \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TA0CCR1 |= CCIE;                          \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TA0CCR2 |= CCIE;                          \
  }                                           \
}

#define __hal_Timer0A3ClearCCRInterrupt(ccrId)\
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TA0CCR0 &= ~CCIE;                         \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TA0CCR1 &= ~CCIE;                         \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TA0CCR2 &= ~CCIE;                         \
  }                                           \
}

/**
 *  \fn Timer0A3CCR0InterruptServiceRoutine
 */
__interrupt void Timer0A3CCR0InterruptServiceRoutine();
extern unsigned char (*Timer0A3CCR0Event)(const void *);

/**
 *  \fn Timer0A3CCR1InterruptServiceRoutine
 */
__interrupt void Timer0A3CCR1InterruptServiceRoutine();
extern unsigned char (*Timer0A3CCR1Event)(const void *);

#endif  // TIMER0_A3 SUB MODULE

#if defined(__MCU_MSP430_TIMER1A3)

/**
 *  @fn   __hal_Timer1A3EnableInterrupt
 */
#define __hal_Timer1A3EnableInterrupt()      TA1CTL |= TAIE

/**
 *  @fn   __hal_Timer1A3DisableInterrupt
 */
#define __hal_Timer1A3DisableInterrupt()     TA1CTL &= ~TAIE

/**
 *  @fn   __hal_Timer1A3CCR0EnableInterrupt
 */
#define __hal_Timer1A3CCR0EnableInterrupt()  TA1CCTL0 |= CCIE

/**
 *  @fn   __hal_Timer1A3CCR0DisableInterrupt
 */
#define __hal_Timer1A3CCR0DisableInterrupt() TA1CCTL0 &= ~CCIE

/**
 *  @fn   __hal_Timer1A3CCR0ClearInterrupt
 */
#define __hal_Timer1A3CCR0ClearInterrupt()   TA1CCTL0 &= ~CCIFG

/**
 *  @fn   __hal_Timer1A3CCR1EnableInterrupt
 */
#define __hal_Timer1A3CCR1EnableInterrupt()  TA1CCTL1 |= CCIE

/**
 *  @fn   __hal_Timer1A3CCR1DisableInterrupt
 */
#define __hal_Timer1A3CCR1DisableInterrupt() TA1CCTL1 &= ~CCIE

/**
 *  @fn   __hal_Timer1A3CCR1ClearInterrupt
 */
#define __hal_Timer1A3CCR1ClearInterrupt()   TA1CCTL1 &= ~CCIFG

/**
 *  @fn   __hal_Timer1A3CCR2EnableInterrupt
 */
#define __hal_Timer1A3CCR2EnableInterrupt()  TA1CCTL2 |= CCIE

/**
 *  @fn   __hal_TimerA3CCR2DisableInterrupt
 */
#define __hal_Timer1A3CCR2DisableInterrupt() TA1CCTL2 &= ~CCIE

/**
 *  @fn   __hal_TimerA3CCR2ClearInterrupt
 */
#define __hal_Timer1A3CCR2ClearInterrupt()   TA1CCTL2 &= ~CCIFG

#define __hal_Timer1A3Configure(clockSource, inputDivider, interruptEnable) \
{                                                                           \
  TA1CTL = MC_0 | TACLR | clockSource | inputDivider | interruptEnable;     \
}

#define __hal_Timer1A3CaptureCompareConfigure(ccrId,                                                                                      \
                                      captureMode, captureInputSelect, syncCaptureSource, syncCaptureInput, captureEnable,                \
                                      outputMode, output,                                                                                 \
                                      ccie, cci)                                                                                          \
{                                                                                                                                         \
  if (ccrId == 0)                                                                                                                         \
  {                                                                                                                                       \
    TA1CCTL0 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
  else if (ccrId == 1)                                                                                                                    \
  {                                                                                                                                       \
    TA1CCTL1 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
  else if (ccrId == 2)                                                                                                                    \
  {                                                                                                                                       \
    TA1CCTL2 = captureMode | captureInputSelect | syncCaptureSource | syncCaptureInput | captureMode | outputMode | ccie | cci | output;  \
  }                                                                                                                                       \
}

#define __hal_Timer1A3Enable(mode)          \
{                                           \
  TA1CTL |= mode;                           \
}

#define __hal_Timer1A3Clear()               \
{                                           \
  TA1CTL |= TACLR;                          \
}

#define __hal_Timer1A3SetCCR(ccrId, value)  \
{                                           \
  if (ccrId == 0)                           \
  {                                         \
    TA1CCR0 = value;                        \
  }                                         \
  else if (ccrId == 1)                      \
  {                                         \
    TA1CCR1 = value;                        \
  }                                         \
  else if (ccrId == 2)                      \
  {                                         \
    TA1CCR2 = value;                        \
  }                                         \
}

#define __hal_Timer0A3SetInterrupt()        TA0CTL |= TAIE;
#define __hal_Timer0A3ClearInterrupt()      TA0CTL &= ~TAIE;

#define __hal_Timer1A3SetCCRInterrupt(ccrId)  \
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TA1CCR0 |= CCIE;                          \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TA1CCR1 |= CCIE;                          \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TA1CCR2 |= CCIE;                          \
  }                                           \
}

#define __hal_Timer1A3ClearCCRInterrupt(ccrId)\
{                                             \
  if (ccrId == 0)                             \
  {                                           \
    TA1CCR0 &= ~CCIE;                         \
  }                                           \
  else if (ccrId == 1)                        \
  {                                           \
    TA1CCR1 &= ~CCIE;                         \
  }                                           \
  else if (ccrId == 2)                        \
  {                                           \
    TA1CCR2 &= ~CCIE;                         \
  }                                           \
}

/**
 *  \fn Timer1A3CCR0InterruptServiceRoutine
 */
__interrupt void Timer1A3InterruptServiceRoutine();
extern unsigned char (*Timer1A3CCR0Event)(const void *);

/**
 *  \fn Timer1A3CCR1to4InterruptServiceRoutine
 */
__interrupt void Timer1A3CCR1InterruptServiceRoutine();
extern unsigned char (*Timer1A3CCR1Event)(const void *);

#endif  // TIMER1_A3 SUB MODULE

#endif  // TIMER_A MODULE

#endif  // __MCU_MSP430_TIMERA_H
