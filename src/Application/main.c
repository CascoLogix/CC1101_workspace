/**
 *  @file main.c
 *
 *  @brief Application main
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

#include "Application.h"
#include "Callback.h"

unsigned int userBuffer[4] = {0};                                               //!< Data buffer defined by user.

/**
 * @fn void main()
 *
 * @brief main 
 */
void main()
{
  InitSystem();                                                                 // Initialize peripherals, application and protocol.

  while(1)
  {
    // ---------- Get data from hardware-----------
    if (pushButtonAction == ACTIVATE_ALARM) {                                   // Check if Pushbutton pressed and toggle RedLED accordingly.
      pushButtonAction = 0;
      LEDToggle(__BSP_LEDRED1);
    }
    userBuffer[2] = LEDState(__BSP_LEDRED1);                                    // Get RedLED state(from hardware) and store it to user buffer.


    // ----------- Get the data from the GUI
    #ifdef __COMMAND_INTERFACE
    unsigned char id = 0xFF;                                                    // This is only to get the data from the GUI corresponding to the nodeID.
      if(CmdIFProcess(&id, &userBuffer[0])){                                    // Run the command interface to get the data(if any) from GUI.
        if(id != 0xFF){
          MapControlsToHW(id, &userBuffer[0]);                                  // Map the received data to the node's respective structure and to its own hardware(if needed).
          if(userBuffer[1] & 0x0001){                                           // Check if a command is received to set my own green LED.
            LEDOn(__BSP_LEDGREEN1);
          }
          else{
            LEDOff(__BSP_LEDGREEN1);
          }
        }
      }
    #endif


    // ---------- Get data from hardware-----------
    if (ADCConversionDone){                                                    // Check for new analog data (local temperature).
      ADCConversionDone = 0;                                                   // Clear flag.
      userBuffer[0] = ADCGetConversionValue(__BSP_ADC1);                       // Get temperature data from ADC(hardware) and store it to user buffer.
      #ifdef __COMMAND_INTERFACE
        MapSensorsFromHW(0, &userBuffer[0]);                                   // Get local only hardware data to send it to the paired module.
        ReportData(0);                                                         // Report Local only hardware states to GUI(temperature and RedLED)
      #endif
    
      // ---------- Send data to radio (SENSOR)-----------
      if(ApplicationState == SENSOR){                                          // We only want to send data from a sensor node when an ADC conversion is complete.
        WirelessOperation(&userBuffer[0]);
        if(userBuffer[1] & 0x0001){                                            // Check if a command is received to set my own green LED.
          LEDOn(__BSP_LEDGREEN1);
        }
        else{
          LEDOff(__BSP_LEDGREEN1);
        }
      }
    }

    // ---------- Get data from radio (HUB)-----------
    if(ApplicationState == HUB){                                               // Check for data received from a sensor node every pass through the loop.
      WirelessOperation(&userBuffer[0]);
      if(userBuffer[1] & 0x0001){                                              // Check if a command is received to set my own green LED.
        LEDOn(__BSP_LEDGREEN1);
      }
      else{
        LEDOff(__BSP_LEDGREEN1);
      }
    }
      

    // ------------ Go to sleep if there is nothing else to do -------------
    __BSP_LOW_POWER_MODE(LOW_POWER_MODE);                                      // Nothing else to do.  Sleep until next interrupt arrives.
  }
}
