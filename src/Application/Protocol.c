/**
 *  @file Protocol.c
 *
 *  @brief Protocol Layer Function Definitions
 *         This file defines the functions for operation of each application 
 *         state in the protocol, i.e. sensor and hub. Function definitions for 
 *         Protocol Layer Command-Interface are included within this file.
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

#include "Protocol.h"
#include "Application.h"

ConfigTimeoutStruct ConfigTimeout = {0};                                        //!< Initialize Config Timeout flag and count

/**
 * @fn void InitProtocol(void)
 *
 * @brief This function initializes the radio for the protocol
 */
void InitProtocol(void)
{
  #ifdef INCLUDE_FLASH_STORAGE
    if(MyFlashStorage.myRSCP.radio < radio_Count){
      RadioLocal.currentRadio = MyFlashStorage.myRSCP.radio;
    }
  #endif

  InitRadio(&appRadio[RadioLocal.currentRadio]);                                // Initialize radio to default config, channel and power 
  SetCycleTime(&appRadio[RadioLocal.currentRadio], 0, 1000);                    // Default cycle to 1 second
}

/**
 * @fn uint8_t DataExchange(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t *count)
 *
 * @brief This function performs the initiates a data exchange.
 *        In the beginning it checks if the radio is in sleep mode due to last
 *        timeout, if it is, it wakes up the radio. It sends a frame with the 
 *        payload data, waits to get the ACK and data, and if a config change was 
 *        requested in the ack it will support completion with an ack back.
 *        If a config change request is to be sent, it initiates and completes
 *        the config change cycle.
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param pBuffer an integer pointer
 * @param count an integer pointer, provides the number of bytes to be sent and
 *        sets the max number that can be recieved and returns the actual 
 *        payload length delivered.
 *
 * @return an integer
 */
uint8_t DataExchange(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t *count)
{
  if(pCurrentFrameworkRadio(pRadio)->radioState == RADIO_SLEEP){                // If radio is in sleep due to last timeout action      
    RadioWakeUp(pCurrentFrameworkRadio(pRadio),
                &pCurrentRadioConfigurationStruct(pRadio)->pRegisterSettings->registerSettings,
                &pRadio[RadioLocal.currentRadio].pRadioPowerList[CurrentPower()].radioPower); // Wake up the radio (SYNC_TIMEOUT_ACTION = SLEEP)
    pCurrentFrameworkRadio(pRadio)->radioState = RADIO_CALIBRATED;              // Restore the radio state
  }
  
  Flags.TxPayloadMessageType = SEND_PAYLOAD;
  Flags.TxACKMessageType = SEND_NO_ACK;
  if(Flags.TxConfigMessageType != SEND_CONFIG_REQUEST){
    if(FrameSend(pRadio, pBuffer, *count, EOP_TIMEOUT, EOP_TIMEOUT_ACTION)){    // Send sensor data to the hub
      if(FrameListen(pRadio, pBuffer, count, SYNC_TIMEOUT, SYNC_TIMEOUT_ACTION)){// Wait for ACK and data from hub
        Query_Current_Status(pRadio, (PayloadFrame *)&pBuffer[0]);              // Check if status update should be given
        if(Flags.RxConfigMessageType == RECEIVED_CONFIG_REQUEST){               // Perform config cycle only if config change request is received
          RXTXCycle(pRadio, pBuffer, count);
        }
        if(Flags.RxPayloadMessageType == RECEIVED_PAYLOAD){
//          RadioSleep(pCurrentFrameworkRadio(pRadio));                           // Put radio to sleep
//          pCurrentFrameworkRadio(pRadio)->radioState = RADIO_SLEEP;             // Update radio state
          return 1;
        }
      }
    }
  }
  else{
    return RXTXCycle(pRadio, pBuffer, count);                                   // If config request to be sent, perform the config change sequence
  }
  return 0;
}


/**
 * @fn uint8_t Listen(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t * pCount)
 *
 * @brief This function performs the operation of Application State - Hub. It checks
 *        to see if a frame is received, if so, it reads the data from radio. If
 *        payload is received, it processes the packet and sends ACK and data back,
 *        and places radio in receive mode to listen for the ACK. It initiates or 
 *        responds to config change and completes the cycle. At the end it checks 
 *        if frane timeout is occured, if so, it checks if the radio is in receive 
 *        mode. If its not, then it places radio back to receive mode to listen for
 *        the next frame.
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param pBuffer an integer pointer
 * @param pCount an integer pointer
 *
 * @return an integer
 */
uint8_t Listen(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t * pCount)
{
  uint8_t tempVar = 0;
  PayloadFrame *ackPayload;
  unsigned char ackCount;
  
  if(RadioLocal.FrameState == FRAME_RECEIVED){                                  // Check to see if a frame has been received.
    GetFrame(pRadio, pBuffer, pCount);                                          // Read data from radio.
    Query_Current_Status(pRadio, (PayloadFrame *)&pBuffer[0]);                  // Check if status update should be given

    if((Flags.RxPayloadMessageType == RECEIVED_PAYLOAD) && (Flags.RxACKMessageType == RECEIVED_NO_ACK)){
      ackPayload = NodeAckPayload(((PayloadFrame *)pBuffer)->NodeID);           // Inform application if payload data was received.
      Flags.TxPayloadMessageType = SEND_PAYLOAD;
      if (ackPayload){                                                          // If payload received from sensor, send ACK and data back to sensor
        ackCount = sizeof(PayloadFrame);
        RXTXCycle(pRadio, (uint8_t *)ackPayload, &ackCount);
      }
      tempVar = 1;
    }
    else if((Flags.RxPayloadMessageType == RECEIVED_NO_PAYLOAD) && (Flags.RxACKMessageType == RECEIVED_NO_ACK)){
      RXTXCycle(pRadio, pBuffer, pCount);
    }
    ReceiveOn(pRadio);                                                          // Place radio back into receive mode.
    return tempVar;
  }
  else if(Flags.TxConfigMessageType == SEND_CONFIG_REQUEST){                  
    if(ConfigTimeout.configTimeout){                                               
      ConfigTimeout.configTimeout = 0;
      Flags.TxConfigMessageType = SEND_NO_CONFIG_CHANGE;                        // If Config timeout occured, abort current config change cycle
      ProvideDelayedResult(0);                                                  // Tell the GUI that we failed
    }
  }

  if((RadioLocal.FrameState != WAITING_FOR_EOP) || RadioLocal.frameTimeout){    // If frame timeout occured, check if radio is in Receive
    RadioLocal.frameTimeout = 0;
    uint8_t temp = ReadMARCSTATE(pRadio);
    if(!(temp == 13 || temp == 14 || temp == 15)){
      ReceiveOn(pRadio);                                                        // If not, place it back in receive to wait for next packet from sensor
    }
  }
  return 0;
}


/**
 * @fn uint8_t RXTXCycle(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t * pCount)
 *
 * @brief This function performs the config change cycle. It is divided into two parts
 *        based on the Initiator and Receiver operation.
 *        
 *        Initiator Operation: It sends a config change request and waits for its ACK.
 *        If an CONFIG_ACK is received, It switches to the new configuration itself,
 *        and sends a config ping. If it receives an ACK for the ping, it returns, 
 *        else it reverts back to old config and sends a config ping. If it receives
 *        an ACK for the ping, it returns. Else it goes to new config and concludes 
 *        that the other module changed to new config and missed the first ping 
 *        for some reason. 
 *        
 *        Receiver Operation: It receives a config change request and sends an ACK for 
 *        that. Then it switches to new config and listens for the config ping. If it
 *        receives config ping, it sends the ACK back and returns. Else it reverts to 
 *        old config and listens for a another config ping. It it receives one, it 
 *        sends an ACK back and returns. Else it goes to new config and concludes 
 *        that it missed the first config ping for some reason.
 *
 *        If none of these conditions are true, it checks if a payload is received and
 *        ACK is to be sent, if yes, it sends the ACK and returns.
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param pBuffer an integer pointer
 * @param pCount an integer pointer
 *
 * @return an integer
 */
uint8_t RXTXCycle(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t * pCount)
{
  uint8_t tempVar = 0;
  
  // Config Change Receiver: Check to see if we received a config change request.  If so, send a config change ACK then change config.
  if(Flags.RxConfigMessageType == RECEIVED_CONFIG_REQUEST){
    Flags.TxConfigMessageType = SEND_CONFIG_ACK;
    FrameSend(pRadio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);       // Send ACK for config change request and change to the new config
    ChangeConfiguration(&pRadio, 0, RadioLocal.RxFrameStruct.frameHeader[NEW_RADIO_INDEX], (RadioLocal.RxFrameStruct.frameHeader[NEW_CONFIG_INDEX] & 0x1F), 
                        RadioLocal.RxFrameStruct.frameHeader[NEW_CHANNEL_INDEX], (RadioLocal.RxFrameStruct.frameHeader[NEW_POWER_COMMAND] & 0x3F));
    if(FrameListen(pRadio, pBuffer, pCount, CONFIG_TIMEOUT, CONFIG_TIMEOUT_ACTION)){// Check if config ping received
      if(Flags.RxConfigMessageType == RECEIVED_CONFIG_PING){
        Flags.TxConfigMessageType = SEND_CONFIG_ACK;
        FrameSend(pRadio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);   // Send config ACK
        Flags.TxConfigMessageType = SEND_NO_CONFIG_CHANGE;
        #if defined(__COMMAND_INTERFACE)
          PhysicalChanged();                                                    // Tell GUI the settings have been changed
        #endif
        return tempVar;
      }
    }
    else{                                                                       // If config ping not received
      // Configuration change sequence failed, revert back to previous settings 
      ChangeConfiguration(&pRadio, 0, RadioLocal.oldRadio, pCurrentConfigSettingsStruct()->oldRFICConfig, pCurrentConfigSettingsStruct()->oldRFChannelNum, pCurrentConfigSettingsStruct()->oldRFPower);
      if(FrameListen(pRadio, pBuffer, pCount, CONFIG_TIMEOUT, CONFIG_TIMEOUT_ACTION)){  // Check if config ping received
        if(Flags.RxConfigMessageType == RECEIVED_CONFIG_PING){
          Flags.TxConfigMessageType = SEND_CONFIG_ACK;
          FrameSend(pRadio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);  // Send config ACK
        }
      }
    }
  }

  // Config Change Initiator:
  else if(Flags.TxConfigMessageType == SEND_CONFIG_REQUEST){
    if(FrameSend(pRadio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION)){    // Send config change request
      if(FrameListen(pRadio, pBuffer, pCount, SYNC_TIMEOUT, CONFIG_TIMEOUT_ACTION)){
        if(Flags.RxPayloadMessageType == RECEIVED_PAYLOAD){
          tempVar = 1;
        }
        if(Flags.RxConfigMessageType == RECEIVED_CONFIG_ACK){                 // Check to see if we received a config change request ACK.  If so, change to new config.
          ChangeConfiguration(&pRadio, 0, RadioLocal.TxFrameStruct.frameHeader[NEW_RADIO_INDEX], (RadioLocal.TxFrameStruct.frameHeader[NEW_CONFIG_INDEX] & 0x1F), 
                              RadioLocal.TxFrameStruct.frameHeader[NEW_CHANNEL_INDEX], (RadioLocal.TxFrameStruct.frameHeader[NEW_POWER_COMMAND] & 0x3F));
          if(SendConfigPingSequence(pRadio, pBuffer, pCount)){
            #if defined(__COMMAND_INTERFACE)
              ProvideDelayedResult(1);                                          // Tell the GUI that we passed
            #endif
            return tempVar;
          }
          // Configuration change sequence failed, revert back to previous settings
          ChangeConfiguration(&pRadio, 0, RadioLocal.oldRadio, pCurrentConfigSettingsStruct()->oldRFICConfig, pCurrentConfigSettingsStruct()->oldRFChannelNum, pCurrentConfigSettingsStruct()->oldRFPower);
          if(SendConfigPingSequence(pRadio, pBuffer, pCount)){
            #if defined(__COMMAND_INTERFACE)
              ProvideDelayedResult(0);                                          // Tell the GUI that we failed
            #endif
            return tempVar;
          }
          // The old settings didn't work either, so let's stay with the new settings
          ChangeConfiguration(&pRadio, 0, RadioLocal.oldRadio, pCurrentConfigSettingsStruct()->oldRFICConfig, pCurrentConfigSettingsStruct()->oldRFChannelNum, pCurrentConfigSettingsStruct()->oldRFPower);
        }
      }
    }
    #if defined(__COMMAND_INTERFACE)
      ProvideDelayedResult(0);                                                  // Tell the GUI that we failed
    #endif
    Flags.TxConfigMessageType = SEND_NO_CONFIG_CHANGE;                          // Abort current config change cycle
  }

  else if(Flags.RxConfigMessageType == RECEIVED_CONFIG_PING){                   // Received packet is a config change ping, so send a config change ACK
      Flags.TxConfigMessageType = SEND_CONFIG_ACK;
      FrameSend(pRadio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);
      return tempVar;
    }

  else if(Flags.RxPayloadMessageType == RECEIVED_PAYLOAD){                      // Received packet has payload data, so send an ACK
    if((pBuffer == NULL) || (pCount == NULL)){
      FrameSend(pRadio, NULL, 0, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);              // If no payload is to be sent
    }
    else{
      FrameSend(pRadio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION);     // If payload is to be sent
    }
  }
  return tempVar;
}

/**
 * @fn uint8_t SendConfigPingSequence(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t * pCount)
 *
 * @brief This function performs the config ping sequence. It sends the config 
 *        ping and listens for ACK. This sequence is continued until config timeout 
 *        occurs. If config ACK is received, config change cycle is finished.
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param pBuffer an unsigned integer pointer
 * @param pCount an unsigned integer pointer
 *
 * @return an unsigned int
 */
uint8_t SendConfigPingSequence(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t * pCount)
{
  TAR = 0;
  TimerCCRClearInterrupt(__BSP_TIMER1, __BSP_TIMER1_CCR0);
  TimerCCREnableInterrupt(__BSP_TIMER1, __BSP_TIMER1_CCR0);                     // Enable Timer1 CCR0 interrupt for config timeout.
  
  ConfigTimeout.configTimeoutCount = 1;                                         // Set timer count initial value (timeout declared when counter reaches 0)
  ConfigTimeout.configTimeout = 0;
  while(!ConfigTimeout.configTimeout){
    Flags.TxConfigMessageType = SEND_CONFIG_PING;
    if(FrameSend(pRadio, pBuffer, *pCount, EOP_TIMEOUT, EOP_TIMEOUT_ACTION)){   // Send config ping
      if(FrameListen(pRadio, pBuffer, pCount, SYNC_TIMEOUT, CONFIG_TIMEOUT_ACTION)){// Check if ACK for config ping is received
        if(Flags.RxConfigMessageType == RECEIVED_CONFIG_ACK){
          Flags.TxConfigMessageType = SEND_NO_CONFIG_CHANGE;                    // Clear the flag to indicate that the config cycle is finished
          ConfigTimeout.configTimeoutCount = 0;
          ConfigTimeout.configTimeout = 0;
          return 1;
        }
      }
    }
  }
  
  TimerCCRDisableInterrupt(__BSP_TIMER1, __BSP_TIMER1_CCR0);                    // Disable Timer1 CCR0 interrupt after config timeout.
  ConfigTimeout.configTimeout = 0;
  return 0;
}
