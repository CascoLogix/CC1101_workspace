/**
 *  @file   ADC.h
 */
#ifndef __DRIVERS_ADC_H
#define __DRIVERS_ADC_H

#include "../../BSP/BoardDrivers.h"

/**
 *  @fn     ADCOn
 *
 *  @brief  Turns the ADC hardware on for operation. This feature may not be
 *          available from all ADC peripherals.
 */
#define ADCOn(adcId)                        __BSP_ADC_ON(adcId)

/**
 *  @fn     ADCOff
 *
 *  @brief  Turns the ADC hardware off for power saving. This feature may not
 *          be available from all ADC peripherals.
 */
#define ADCOff(adcId)                       __BSP_ADC_OFF(adcId)

/**
 *  @fn     ADCReferenceOn
 *
 *  @brief  Turns the reference generator on. When the generator is enabled, a
 *          settling time must be observed before the ADC produces accurate 
 *          readings. This feature may not be available from all ADC peripherals.
 */
#define ADCReferenceOn(adcId)               __BSP_ADC_REF_ON(adcId)

/**
 *  @fn   ADCReferenceOff
 *
 *  @brief  Turns the reference generator off. This feature may not be available
 *          from all ADC peripherals.
 */
#define ADCReferenceOff(adcId)              __BSP_ADC_REF_OFF(adcId)

/**
 *  @fn     ADCEnableInterrupt
 *
 *  @brief  Enable ADC hardware interrupts.
 */
#define ADCEnableInterrupt(adcId)           __BSP_ADC_ENABLE_INTERRUPT(adcId)

/**
 *  @fn     ADCDisableInterrupt
 *
 *  @brief  Disable ADC hardware interrupts.
 */
#define ADCDisableInterrupt(adcId)          __BSP_ADC_DISABLE_INTERRUPT(adcId)

/**
 *  @fn     ADCChannelConfigure
 *
 *  @brief  Configures a specific channel for ADC operation. Peripheral registers
 *          are reconfigured for flexibility of options per channel. Be sure to
 *          call this function each time if other channels are also being used
 *          with different register settings. 
 *
 *  @note   If all channels use the same settings, or you're only using one 
 *          channel, a single call of this function should be sufficient.
 */
#define ADCChannelConfigure(adcId, channelId) __BSP_ADC_CHANNEL_CONFIGURE(adcId, channelId)

/**
 *  @fn   ADCGetConversionValue
 */
#define ADCGetConversionValue(adcId)        __BSP_ADC_GET_CONVERSION_VALUE(adcId)

/**
 *  @fn   ADCSingleConversion
 */
#define ADCSingleConversion(adcId, channel) __BSP_ADC_SINGLE_CONVERSION(adcId, channel)

/**
 *  @fn   ADCEnableConversion
 */
#define ADCEnableConversion(adcId) __BSP_ADC_ENABLE_CONVERSION(adcId)

#endif  // __DRIVERS_ADC_H
