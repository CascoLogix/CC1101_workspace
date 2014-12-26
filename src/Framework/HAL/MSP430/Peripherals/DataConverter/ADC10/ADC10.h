/**
 *  \file   ADC10.h
 */
#ifndef __MCU_MSP430_ADC10_H
#define __MCU_MSP430_ADC10_H

#include "../../../Config.h"

#if defined(__MCU_MSP430_ADC10)

#define ADC10_NO_EVENT                      0x00
#define ADC10_A0_EVENT                      0x00
#define ADC10_A1_EVENT                      0x01
#define ADC10_A2_EVENT                      0x02
#define ADC10_A3_EVENT                      0x03
#define ADC10_A4_EVENT                      0x04
#define ADC10_A5_EVENT                      0x05
#define ADC10_A6_EVENT                      0x06
#define ADC10_A7_EVENT                      0x07
#define ADC10_TEMPERATURE_SENSOR_EVENT      0x0A
#define ADC10_VOLTAGE_SOURCE_EVENT          0x0B

// Channels
#define A0                                  INCH_0
#define A1                                  INCH_1
#define A2                                  INCH_2
#define A3                                  INCH_3
#define A4                                  INCH_4
#define A5                                  INCH_5
#define A6                                  INCH_6
#define A7                                  INCH_7
#define TEMPERATURE_SENSOR                  INCH_10

/**
 *  @fn   __hal_ADC10Configure
 */
#define __hal_ADC10Configure(srefx, adc10shtx, adc10sr, refout, refburst, ref2_5v,              \
                              inchx, shsx, adc10df, issh, adc10divx, adc10sselx)                \
{                                                                                               \
  ADC10CTL0 &= ~ENC;                                                                            \
  ADC10CTL0 = (ADC10CTL0 & ~SREF_7 & ~ADC10SHT_3 & ~ADC10SR & ~REFOUT & ~REFBURST & ~REF2_5V) | \
                srefx | adc10shtx | adc10sr | refout | refburst | ref2_5v;                      \
  ADC10CTL1 = (ADC10CTL1 & ~INCH_15 & ~SHS_3 & ~ADC10DF & ~ISSH & ~ADC10DIV_7 & ~ADC10SSEL_3) | \
                inchx | shsx | adc10df | issh | adc10divx | adc10sselx;                         \
}

/**
 *  @fn   __hal_ADC10On
 */
#define __hal_ADC10On()                     \
{                                           \
  ADC10CTL0 &= ~ENC;                        \
  ADC10CTL0 |= ADC10ON;                     \
}

/**
 *  @fn   __hal_ADC10Off
 */
#define __hal_ADC10Off()                    \
{                                           \
  ADC10CTL0 &= ~ENC;                        \
  ADC10CTL0 &= ~ADC10;                      \
}

/**
 *  @fn   __hal_ADC10RefOn  
 */
#define __hal_ADC10RefOn()                  \
{                                           \
  ADC10CTL0 &= ~ENC;                        \
  ADC10CTL0 |= REFON;                       \
}

/**
 *  @fn   __hal_ADC10RefOff  
 */
#define __hal_ADC10RefOff()                 \
{                                           \
  ADC10CTL0 &= ~ENC;                        \
  ADC10CTL0 &= ~REFON;                      \
}

/**
 *  @fn   __hal_ADC10EnableInterrupt
 */
#define __hal_ADC10EnableInterrupt()        ADC10CTL0 |= ADC10IE

/**
 *  @fn   __hal_ADC10DisableInterrupt
 */
#define __hal_ADC10DisableInterrupt()       ADC10CTL0 &= ~ADC10IE

/**
 *  @fn   __hal_ADC10GetConversionValue
 */
#define __hal_ADC10GetConversionValue()     ADC10MEM

/**
 *  @fn   __hal_ADC10EnableConversion  
 */
#define __hal_ADC10EnableConversion()       ADC10CTL0 |= ENC

/**
 *  @fn   __hal_ADC10StartSingleConversion
 */
 #ifdef USE_INLINE
#pragma inline
void __hal_ADC10StartSingleConversion(unsigned int channel)
{
  // Configure analog enable pins if channel is analog.
  ADC10AE0 = (channel & 0xFF);
  #ifdef ADC10AE1
  ADC10AE1 = (channel & 0xFF00);
  #endif
  ADC10CTL0 |= ENC + ADC10SC;           //!< Enable and start conversion
}
#else
void __hal_ADC10StartSingleConversion(unsigned int channel);
#endif

/**
 *  \fn   ADC10InterruptServiceRoutine
 */
__interrupt void __hal_ADC10InterruptServiceRoutine();
extern unsigned char (*ADC10Event)(const void *);

#endif  // ADC10 MODULE

#endif  // __MCU_MSP430_ADC10_H
