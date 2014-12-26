/**
 *  @file Callback.h
 *
 *  @brief Event Handler Callback Functions
 *
 *  @version  1.0
 *
 *  @attention IMPORTANT: Your use of this Software is limited to those specific 
 *             rights granted under the terms of a software license agreement 
 *             between the user who downloaded the software, his/her employer 
 *             (which must be your employer) and Anaren (the "License"). You may
 *             not use this Software unless you agree to abide by the terms of 
 *             the License. The License limits your use, and you acknowledge,
 *             that the Software may not be modified, copied or distributed unless
 *             in connection with an authentic Anaren product. Other than for the 
 *             foregoing purpose, you may not use, reproduce, copy, prepare 
 *             derivative works of, modify, distribute, reverse engineer, decompile,
 *             perform, display or sell this Software and/or its documentation 
 *             for any purpose. 
 *             YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION
 *             ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS 
 *             OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY  WARRANTY OF 
 *             MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR 
 *             PURPOSE. IN NO EVENT SHALL ANAREN OR ITS LICENSORS BE LIABLE OR
 *             OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 *             BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR 
 *             INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY 
 *             INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, 
 *             LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS,
 *             TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT
 *             NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS. 
 */

#ifndef __APP_CALLBACK_H
#define __APP_CALLBACK_H

#include "CommandInterface.h"

#define ACTIVATE_ALARM                BIT0                                      //!< Push button action = activate alarm
#define ENABLE_PAIRING                BIT1                                      //!< Push button action = enable pairing mode                                 
#define ENABLE_PAIRING_HUB_TO_SENSOR  BIT2                                      //!< Push button action = change application state from hub to sensor and enable pairing mode
#define FLASH_FACTORY_DEFAULT         BIT3                                      //!< Push button action = restore default setings
#define DISABLE_PAIRING               BIT4                                      //!< Push button action = disable pairing mode
#define NEXT_APPLICATION_STATE        BIT5                                      //!< Push button action = go to next application state
#define GET_APPLICATION_STATE         BIT6                                      //!< Push button action = get current application state

#define ENABLE_PAIRING_TIME                200                                  //!< 2 seconds
#define ENABLE_PAIRING_HUB_TO_SENSOR_TIME  500                                  //!< 5 seconds
#define FLASH_FACTORY_DEFAULT_TIME         1500                                 //!< 15 seconds

//#define ENABLE_PAIRING_GREEN_LED_BLINK_RATE                 50
//#define ENABLE_PAIRING_GREEN_LED_ON_TIME                    5
//#define ENABLE_PAIRING_RED_LED_BLINK_RATE                   1
//#define ENABLE_PAIRING_RED_LED_ON_TIME                      0
//
//#define ENABLE_PAIRING_HUB_TO_SENSOR_GREEN_LED_BLINK_RATE   10
//#define ENABLE_PAIRING_HUB_TO_SENSOR_GREEN_LED_ON_TIME      5
//#define ENABLE_PAIRING_HUB_TO_SENSOR_RED_LED_BLINK_RATE     1
//#define ENABLE_PAIRING_HUB_TO_SENSOR_RED_LED_ON_TIME        0
//
//#define FLASH_FACTORY_DEFAULT_GREEN_LED_BLINK_RATE          1
//#define FLASH_FACTORY_DEFAULT_GREEN_LED_ON_TIME             0
//#define FLASH_FACTORY_DEFAULT_RED_LED_BLINK_RATE            100
//#define FLASH_FACTORY_DEFAULT_RED_LED_ON_TIME               50

#define ENABLE_PAIRING_GREEN_LED_BLINK_RATE                 1
#define ENABLE_PAIRING_GREEN_LED_ON_TIME                    0
#define ENABLE_PAIRING_RED_LED_BLINK_RATE                   50
#define ENABLE_PAIRING_RED_LED_ON_TIME                      5

#define ENABLE_PAIRING_HUB_TO_SENSOR_GREEN_LED_BLINK_RATE   1
#define ENABLE_PAIRING_HUB_TO_SENSOR_GREEN_LED_ON_TIME      0
#define ENABLE_PAIRING_HUB_TO_SENSOR_RED_LED_BLINK_RATE     10
#define ENABLE_PAIRING_HUB_TO_SENSOR_RED_LED_ON_TIME        5

#define FLASH_FACTORY_DEFAULT_GREEN_LED_BLINK_RATE          1
#define FLASH_FACTORY_DEFAULT_GREEN_LED_ON_TIME             0
#define FLASH_FACTORY_DEFAULT_RED_LED_BLINK_RATE            100
#define FLASH_FACTORY_DEFAULT_RED_LED_ON_TIME               50

/**
 * @brief LED state controls
 */
typedef volatile struct LEDStateControl
{
  unsigned char blinkPeriod;                                                    //!< Blink period
  unsigned char onTime;                                                         //!< On time
  unsigned char restorePrevious;                                                //!< To restore previous state of operation
  unsigned char previousState;                                                  //!< previous state of operation
} LEDStateControl;

extern volatile unsigned char pushButtonAction;                                 //!< Specify push button action based on the press type.
extern volatile unsigned char swTimerAction;                                    //!< Specify software timer action.
extern volatile unsigned char ADCConversionDone;                                //!< Flag to indicate that ADC conversion is done.
extern RadioStruct RadioLocal;                                                  //!< Structure for Operation of Radio Functions
extern ConfigTimeoutStruct ConfigTimeout;                                       //!< Config Timeout flag and count

/**
 * @details ADC Event Handler
 */
unsigned char ADCEventHandler(const void * params);

/**
 * @details GPIO Port Event Handler
 */
unsigned char PortEventHandler(const void * params);

/**
 * @details UART Receive Event Handler
 */
unsigned char UARTRXEventHandler(const void * params);

/**
 * @details Timer1 CCR Event Handler
 */
unsigned char Timer1CCREventHandler(const void * params);

/**
 * @details Timer2 CCR Event Handler
 */
unsigned char Timer2CCREventHandler(const void * params);

/**
 * @details Push Button1 Event Handler
 */
unsigned char PushButton1EventHandler(const void * params);

/**
 * @details Software Timer0 Event Handler
 */
unsigned char SWTimer0EventHandler(const void * params);

/**
 * @details Software Timer1 Event Handler
 */
unsigned char SWTimer1EventHandler(const void * params);

/**
 * @details Set the blink rate for LED
 */
void SetLEDBlinkRate(unsigned char led, unsigned int onCount, unsigned int offCount);

#endif  // __APP_CALLBACK_H
