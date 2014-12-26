/**
 *  @file Callback.c
 *
 *  @brief Function Definitions for ISR Extensions, brought upto Application Layer.
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

#include "Callback.h"

volatile unsigned char ADCConversionDone = 0;                                            //!< Flag to indicate that ADC conversion is done.
volatile unsigned char pushButtonAction = 0;                                             //!< Specify push button action based on the press type.
volatile unsigned char swTimerAction = 0;                                                //!< Specify software timer action.

LEDStateControl greenLEDStateControl = {0,0,0,0};                               //!< Initialize green LED state controls.                          
LEDStateControl redLEDStateControl = {0,0,0,0};                                 //!< Initialize red LED state controls.   

/**
 * @fn void LEDControl(unsigned char led, LEDStateControl * s_LEDStateControl)
 *
 * @brief This function controls the LED outputs.
 *        While the button is pressed or software timer 0 is running, blink the 
 *        LED at the rate specified. Otherwise restore the state from before the
 *        button press. blinkPeriod specifies the blink period in 10ms increments 
 *        while onTime specifies the amount of time (10ms increments) the LED is
 *        on during that period. For example, setting blinkPeriod to 100 and onTime 
 *        to 10 will result in a 1000ms period with the LED on for 100ms 
 *        (i.e. on for 100ms, off for 900ms)
 *
 * @param led an unsigned char
 * @param pLEDStateControl a LEDStateControl structure pointer
 */
void LEDControl(unsigned char led, LEDStateControl * pLEDStateControl)
{
  if (pLEDStateControl->blinkPeriod)
  {
    if (((pushButtonTimer.clickHold == PUSHBUTTON_HOLD) ? pushButtonTimer.count : SoftwareTimerGetCount(__BSP_SWTIMER[0])) % pLEDStateControl->blinkPeriod < pLEDStateControl->onTime)
    {
      LEDOn(led);
    }
    else
    {
      LEDOff(led);
    }
  }
  else if (pLEDStateControl->restorePrevious)
  {
    pLEDStateControl->restorePrevious = 0;
    if (pLEDStateControl->previousState)
    {
      LEDOn(led);
    }
    else
    {
      LEDOff(led);
    }
  }
}

/**
 * @fn unsigned char ADCEventHandler(const void * params)
 *
 * @brief This function is an extension of Data Converter ISR. It sets a flag 
 *        that indicates the application that Sensor ADC data is available.
 * 
 * @param params a constant void pointer
 *
 * @return an unsigned character
 */
unsigned char ADCEventHandler(const void * params)
{
  // Get event parameters.
  EventParameters * p = (EventParameters *) params;

  if(p->event == __BSP_ADC1_CHAN9_EVENT)
  {
    ADCConversionDone = 1;                                                      // Set sensor ADC data available flag for application.
  }
  
  return EVENT_WAKE_UP;
}

/**
 * @fn unsigned char PortEventHandler(const void * params)
 *
 * @brief This function is an extension of GPIO Port ISR.
 * 
 * @param params a constant void pointer
 *
 * @return an unsigned character
 */
unsigned char PortEventHandler(const void * params)
{
  // Get event parameters.
  EventParameters * p = (EventParameters *) params;

  if (p->event & __BSP_PUSHBUTTON1_EVENT)
  {
    PushButtonEventHandler(__BSP_PUSHBUTTON1, __BSP_CONFIG_PUSHBUTTON_MINIMUM_CLICK_TIME);
  }
  
  if (p->event & __BSP_RADIO1_GDO0_EVENT)
  {
    volatile unsigned char tempVar  = 0;
  
    if(__BSP_RADIO1_GDO0_EVENT & __BSP_RADIO1_GDO0_EDGE_SELECT)                 // End of Packet
    {
      if(pCurrentFrameworkRadio(&appRadio[RadioLocal.currentRadio])->radioState == RADIO_TRANSMIT){
        RadioLocal.FrameState = FRAME_SENT;                                     // Update frame state
        //GDO0 asserted slightly before RF transmission ends, so add a little delay
        for(tempVar=0;tempVar<200;tempVar++){
          __no_operation();
        }
      }
      else if(pCurrentFrameworkRadio(&appRadio[RadioLocal.currentRadio])->radioState == RADIO_RECEIVE){
        RadioLocal.FrameState = FRAME_RECEIVED;                                 // Update frame state
        TimerCCRDisableInterrupt(__BSP_TIMER1, __BSP_TIMER1_CCR1);
      }
      pCurrentFrameworkRadio(&appRadio[RadioLocal.currentRadio])->radioState = RADIO_CALIBRATED;
    }
    else                                                                        // SyncWord sent/received
    {
      RadioSetInterruptEdge(pCurrentFrameworkRadio(&appRadio[RadioLocal.currentRadio]), __BSP_RADIO1_INTERRUPT1, 1);
      
      RadioLocal.FrameState = WAITING_FOR_EOP;                                  // Update frame state
  
      StartTimeoutTimer(EOP_TIMEOUT);                                           // Load timer with timeout value.  The radio should be placed in a low-power state if frame timeout occurs.
    }
  }

  return EVENT_WAKE_UP;
}

/**
 * @fn unsigned char UARTRXEventHandler(const void * params)
 *
 * @brief This function is an extension of UART Receive ISR.
 * 
 * @param params a constant void pointer
 *
 * @return an unsigned character
 */
unsigned char UARTRXEventHandler(const void * params)
{
  unsigned char readValue = 0;

  // Get event parameters.
  EventParameters * p = (EventParameters *) params;

  // Check event type.
  if (p->event == __BSP_UART1_RX_EVENT)
  {
    UARTReceiveByte(__BSP_UART1, &readValue);
    CmdIFCollect(readValue);                                                    // Collect the received command character by character.
  }
  
  return EVENT_WAKE_UP;
}

/**
 * @fn unsigned char Timer1CCREventHandler(const void * params)
 *
 * @brief This function is an extension of Timer1 ISR.
 * 
 * @param params a constant void pointer
 *
 * @return an unsigned character
 */
unsigned char Timer1CCREventHandler(const void * params)
{
  // Get event parameters.
  EventParameters * p = (EventParameters *) params;
  
  // Check event type.
  if (p->event == __BSP_TIMER1_CCR0_EVENT)
  {
    // moved the code here for config timeout, and it does not work!
    if(ConfigTimeout.configTimeoutCount)
    {
      ConfigTimeout.configTimeoutCount--;
      if(!ConfigTimeout.configTimeoutCount)
      {
        ConfigTimeout.configTimeout = 1;
      }
    }
  }
  else if(p->event & __BSP_TIMER1_CCR1_EVENT)
  {
    TimerCCRDisableInterrupt(__BSP_TIMER1, __BSP_TIMER1_CCR1);
    RadioLocal.frameTimeout = 1;
  }
  else if(p->event & __BSP_TIMER1_CCR2_EVENT)
  {
  }
  
  return EVENT_WAKE_UP;
}

/**
 * @fn unsigned char Timer2CCREventHandler(const void * params)
 *
 * @brief This function is an extension of Timer2 ISR.
 * 
 * @param params a constant void pointer
 *
 * @return an unsigned character
 */
unsigned char Timer2CCREventHandler(const void * params)
{
  // Get event parameters.
  EventParameters * p = (EventParameters *) params;
  static unsigned char previousClickHoldState = 0;

  // Check event type.
  if (p->event == __BSP_TIMER2_CCR0_EVENT)
  {
    // Scan for a change in long button press status.  The code inside this IF statement
    // should only execute once following a long button press and once again following release.
    if (previousClickHoldState != pushButtonTimer.clickHold)
    {
      // The button was just pressed ...
      if (pushButtonTimer.clickHold == PUSHBUTTON_HOLD)
      {
        // Store the previous LED states so that we can change the LEDs while the button is held
        greenLEDStateControl.previousState = LEDState(__BSP_LEDGREEN1);
        redLEDStateControl.previousState = LEDState(__BSP_LEDRED1);
      }
      // The button was just released ...
      else
      {
        // Set flags to indicate the LEDs should be returned to their states prior to the button press
        greenLEDStateControl.restorePrevious = 1;
        redLEDStateControl.restorePrevious = 1;
      }
    }

    // Update the LED outputs
    LEDControl(__BSP_LEDGREEN1, &greenLEDStateControl);
    LEDControl(__BSP_LEDRED1, &redLEDStateControl);

    // Blink the LEDs with different patterns while the button is held
    if (pushButtonTimer.clickHold == PUSHBUTTON_HOLD)
    {
      // holdCount does not include first timeout period which is added after button is released.
      if (pushButtonTimer.holdCount > FLASH_FACTORY_DEFAULT_TIME + __BSP_CONFIG_PUSHBUTTON_CLICK_TIMEOUT)
      {
        greenLEDStateControl.blinkPeriod  = FLASH_FACTORY_DEFAULT_GREEN_LED_BLINK_RATE;
        greenLEDStateControl.onTime       = FLASH_FACTORY_DEFAULT_GREEN_LED_ON_TIME;
        redLEDStateControl.blinkPeriod    = FLASH_FACTORY_DEFAULT_RED_LED_BLINK_RATE;
        redLEDStateControl.onTime         = FLASH_FACTORY_DEFAULT_RED_LED_ON_TIME;
      }
      else if (pushButtonTimer.holdCount > ENABLE_PAIRING_HUB_TO_SENSOR_TIME + __BSP_CONFIG_PUSHBUTTON_CLICK_TIMEOUT)
      {
        greenLEDStateControl.blinkPeriod  = ENABLE_PAIRING_HUB_TO_SENSOR_GREEN_LED_BLINK_RATE;
        greenLEDStateControl.onTime       = ENABLE_PAIRING_HUB_TO_SENSOR_GREEN_LED_ON_TIME;
        redLEDStateControl.blinkPeriod    = ENABLE_PAIRING_HUB_TO_SENSOR_RED_LED_BLINK_RATE;
        redLEDStateControl.onTime         = ENABLE_PAIRING_HUB_TO_SENSOR_RED_LED_ON_TIME;
      }
      else if (pushButtonTimer.holdCount > ENABLE_PAIRING_TIME - __BSP_CONFIG_PUSHBUTTON_CLICK_TIMEOUT)
      {
        greenLEDStateControl.blinkPeriod  = ENABLE_PAIRING_GREEN_LED_BLINK_RATE;
        greenLEDStateControl.onTime       = ENABLE_PAIRING_GREEN_LED_ON_TIME;
        redLEDStateControl.blinkPeriod    = ENABLE_PAIRING_RED_LED_BLINK_RATE;
        redLEDStateControl.onTime         = ENABLE_PAIRING_RED_LED_ON_TIME;
      }
    }
    // Maintain the blink settings while the software timer keeps the node in pairing mode
    else
    {
      if ((pushButtonAction == FLASH_FACTORY_DEFAULT) || (__BSP_SWTIMER[0].enable == 0))
      {
        greenLEDStateControl.blinkPeriod  = 0;
        redLEDStateControl.blinkPeriod    = 0;
      }
      else if (pushButtonAction == ENABLE_PAIRING_HUB_TO_SENSOR)
      {
        greenLEDStateControl.blinkPeriod  = ENABLE_PAIRING_HUB_TO_SENSOR_GREEN_LED_BLINK_RATE;
        greenLEDStateControl.onTime       = ENABLE_PAIRING_HUB_TO_SENSOR_GREEN_LED_ON_TIME;
        redLEDStateControl.blinkPeriod    = ENABLE_PAIRING_HUB_TO_SENSOR_RED_LED_BLINK_RATE;
        redLEDStateControl.onTime         = ENABLE_PAIRING_HUB_TO_SENSOR_RED_LED_ON_TIME;
      }
      else if (pushButtonAction == ENABLE_PAIRING)
      {
        greenLEDStateControl.blinkPeriod  = ENABLE_PAIRING_GREEN_LED_BLINK_RATE;
        greenLEDStateControl.onTime       = ENABLE_PAIRING_GREEN_LED_ON_TIME;
        redLEDStateControl.blinkPeriod    = ENABLE_PAIRING_RED_LED_BLINK_RATE;
        redLEDStateControl.onTime         = ENABLE_PAIRING_RED_LED_ON_TIME;
      }
    }

    previousClickHoldState = pushButtonTimer.clickHold;
  }
  else if(p->event & __BSP_TIMER2_CCR1_EVENT)
  {
  }
  else if(p->event & __BSP_TIMER2_CCR2_EVENT)
  {
  }

  return EVENT_NO_ACTION;
}

/**
 * @fn unsigned char PushButton1EventHandler(const void * params)
 *
 * @brief This function is an extension of ISR for Push Button event.
 * 
 * @param params a constant void pointer
 *
 * @return an unsigned character
 */
unsigned char PushButton1EventHandler(const void * params)
{
  if (pushButtonTimer.clickHold == PUSHBUTTON_CLICK)
  {
    switch (pushButtonTimer.clickCount)
    {
      case 1:                                                                   //!< Single click
        pushButtonAction = ACTIVATE_ALARM;
        break;
      case 2:                                                                   //!< Double click
        pushButtonAction = GET_APPLICATION_STATE;
        break;
      case 3:                                                                   //!< Triple click
        pushButtonAction = NEXT_APPLICATION_STATE;
        break;
      default: break;
    }
  }
  else
  {
    if (pushButtonTimer.holdCount > FLASH_FACTORY_DEFAULT_TIME)
    {
      pushButtonAction = FLASH_FACTORY_DEFAULT;
    }
    else if (pushButtonTimer.holdCount > ENABLE_PAIRING_HUB_TO_SENSOR_TIME)
    {
      pushButtonAction = ENABLE_PAIRING_HUB_TO_SENSOR;
    }
    else if (pushButtonTimer.holdCount > ENABLE_PAIRING_TIME)
    {
      pushButtonAction = ENABLE_PAIRING;
    }
  }

  return EVENT_WAKE_UP;
}

/**
 * @fn unsigned char SWTimer0EventHandler(const void * params)
 *
 * @brief Software Timer0 Event Handler.
 * 
 * @param params a constant void pointer
 *
 * @return an unsigned character
 */
unsigned char SWTimer0EventHandler(const void * params)
{
  swTimerAction = DISABLE_PAIRING;
  greenLEDStateControl.blinkPeriod  = 0;
  redLEDStateControl.blinkPeriod    = 0;
  
  return EVENT_NO_ACTION;
}

///**
// * @fn unsigned char SWTimer1EventHandler(const void * params)
// *
// * @brief Software Timer1 Event Handler.
// * 
// * @param params a constant void pointer
// *
// * @return an unsigned character
// */
//unsigned char SWTimer1EventHandler(const void * params)
//{
//  return EVENT_WAKE_UP;
//}
