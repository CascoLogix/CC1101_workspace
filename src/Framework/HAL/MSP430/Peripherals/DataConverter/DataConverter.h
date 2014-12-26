/**
 *  \file   DataConverter.h
 */
#ifndef __HAL_MSP430_DATACONVERTER_H
#define __HAL_MSP430_DATACONVERTER_H

#include "../../Config.h"

//enum ADCChannel
//{
//  A0                  = INCH_0,
//  A1                  = INCH_1,
//  A2                  = INCH_2,
//  A3                  = INCH_3,
//  A4                  = INCH_4,
//  A5                  = INCH_5,
//  A6                  = INCH_6,
//  A7                  = INCH_7,
//  TEMPERATURE_SENSOR  = INCH_10
//};


/**
 *  \fn   __hal_ADCGetSingleConversionValue
 */
//#pragma inline
//unsigned int __hal_ADCGetSingleConversionValue(enum PERIPHERAL peripheral)
//{
//  #if defined(__MCU_MSP430_ADC10)
//  if (ADC10)
//  {
//    return ADC10MEM;                        // Fetch conversion result
//  }
//  #endif
//}

/**
 *  \fn   __hal_ADCSingleConversion
 */
//#pragma inline
//void __hal_ADCSingleConversion(enum PERIPHERAL peripheral, unsigned int channel)
//{
//  #if defined(__MCU_MSP430_ADC10)
////  unsigned char refVoltage = (ADC10CTL0 & REF2_5V);   //<! Previous reference voltage before reconfiguration
//  if (peripheral == ADC10)
//  {
//    ADC10CTL0 &= ~ENC;                      // Disable ADC for configuration
//
//    // Configure channel that conversion is to take place on.
//    switch(channel)
//    {
//    case A0:
//    case A1:
//    case A2:
//    case A3:
//    case A4:
//    case A5:
//    case A6:
//    case A7:
//      break;
//    case TEMPERATURE_SENSOR:
//      // Use the 1.5v reference because the temperature sensor does not exceed
//      // 1.4v over the commercial range of temperature. Resolution would be lost
//      // if the 2.5v reference were used instead.
//      
//      // Set channel to temperate sensor
//      ADC10CTL1 = TEMPERATURE_SENSOR | ADC10DIV_3 | (~CONSEQ_3);
//      break;
//    default:
//      break;
//    }
//    
//    ADC10CTL0 |= ENC + ADC10SC;           //!< Enable and start conversion
//  }
//  #endif
//}

#endif  // __HAL_MSP430_DATACONVERTER_H
