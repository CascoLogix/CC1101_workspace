/**
 *  @file RadioOperation.c
 *
 *  @brief Radio Operation function Definitions
 *         This file defines the functions for Initializing and Configuring the
 *         radio, Frame-Transmit and Frame-Receive.
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
#include "RadioOperation.h"

/**
 * @brief Application Radio Definition Structure
 */
s_AppRadio appRadio[] = {
  #if defined(__RADIO_A1101R04) && defined(__RADIO_CERTIFICATION_FCC)
    {
      &__BSP_RADIO1_CONNECTION,
      (AppRadioConfiguration *)&A1101R09ConfigurationFCC[0],
      (AppRadioChannelList *)&A1101R09ChannelListFCC[0],
      (AppRadioPowerList *)&A1101R09PowerListFCC[0],
      (AppRadioArraySizes *)&A1101R09ArraySizesFCC,
      #ifdef RADIO_FULL_TEXT_DESCRIPTIONS
        "A1101R09A, FCC"
      #endif
    },
  #endif  // __RADIO_A1101R04 ETSI

  #if defined(__RADIO_A1101R04) && defined(__RADIO_CERTIFICATION_ETSI)
    {
      &__BSP_RADIO1_CONNECTION,
      (AppRadioConfiguration *)&A1101R04ConfigurationETSI[0],
      (AppRadioChannelList *)&A1101R04ChannelListETSI[0],
      (AppRadioPowerList *)&A1101R04PowerListETSI[0],
      (AppRadioArraySizes *)&A1101R04ArraySizesETSI,
      #ifdef RADIO_FULL_TEXT_DESCRIPTIONS
        "A1101R09A, ETSI"
      #endif
    },
  #endif  // __RADIO_A1101R04 FCC

  #if defined(__RADIO_A1101R08) && defined(__RADIO_CERTIFICATION_ETSI)
    {
      &__BSP_RADIO1_CONNECTION,
      (AppRadioConfiguration *)&A1101R08ConfigurationETSI[0],
      (AppRadioChannelList *)&A1101R08ChannelListETSI[0],
      (AppRadioPowerList *)&A1101R08PowerListETSI[0],
      (AppRadioArraySizes *)&A1101R08ArraySizesETSI,
      #ifdef RADIO_FULL_TEXT_DESCRIPTIONS
        "A110LR09A, ETSI"
      #endif
    },
  #endif  // __RADIO_A1101R08 ETSI

  #if defined(__RADIO_A1101R09) && defined(__RADIO_CERTIFICATION_FCC)
    {
      &__BSP_RADIO1_CONNECTION,
      (AppRadioConfiguration *)&A1101R09ConfigurationFCC[0],
      (AppRadioChannelList *)&A1101R09ChannelListFCC[0],
      (AppRadioPowerList *)&A1101R09PowerListFCC[0],
      (AppRadioArraySizes *)&A1101R09ArraySizesFCC,
      #ifdef RADIO_FULL_TEXT_DESCRIPTIONS
        "A1101R09A, FCC"
      #endif
    },
  #endif  // __RADIO_A1101R09 FCC

  #if defined(__RADIO_A110LR09) && defined(__RADIO_CERTIFICATION_ETSI)
    {
      &__BSP_RADIO1_CONNECTION,
      (AppRadioConfiguration *)&A110LR09ConfigurationETSI[0],
      (AppRadioChannelList *)&A110LR09ChannelListETSI[0],
      (AppRadioPowerList *)&A110LR09PowerListETSI[0],
      (AppRadioArraySizes *)&A110LR09ArraySizesETSI,
      #ifdef RADIO_FULL_TEXT_DESCRIPTIONS
        "A110LR09A, ETSI"
      #endif
    },
  #endif  // __RADIO_A110LR09
  #if defined(__RADIO_A110LR09) && defined(__RADIO_CERTIFICATION_FCC)
    {
      &__BSP_RADIO1_CONNECTION,
      (AppRadioConfiguration *)&A110LR09ConfigurationFCC[0],
      (AppRadioChannelList *)&A110LR09ChannelListFCC[0],
      (AppRadioPowerList *)&A110LR09PowerListFCC[0],
      (AppRadioArraySizes *)&A110LR09ArraySizesFCC,
      #ifdef RADIO_FULL_TEXT_DESCRIPTIONS
        "A110LR09A, FCC"
      #endif
    },
  #endif  // __RADIO_A110LR09

  #if defined(__RADIO_A2500R24) && defined(__RADIO_CERTIFICATION_ETSI)
    {
      &__BSP_RADIO1_CONNECTION,
      (AppRadioConfiguration *)&A2500R24ConfigurationETSI[0],
      (AppRadioChannelList *)&A2500R24ChannelListETSI[0],
      (AppRadioPowerList *)&A2500R24PowerListETSI[0],
      (AppRadioArraySizes *)&A2500R24ArraySizesETSI,
      #ifdef RADIO_FULL_TEXT_DESCRIPTIONS
        "A2500R24A, ETSI"
      #endif
    },
  #endif  // __RADIO_A2500R24 ETSI
  #if defined(__RADIO_A2500R24) && defined(__RADIO_CERTIFICATION_FCC)
    {
      &__BSP_RADIO1_CONNECTION,
      (AppRadioConfiguration *)&A2500R24ConfigurationFCC[0],
      (AppRadioChannelList *)&A2500R24ChannelListFCC[0],
      (AppRadioPowerList *)&A2500R24PowerListFCC[0],
      (AppRadioArraySizes *)&A2500R24ArraySizesFCC,
      #ifdef RADIO_FULL_TEXT_DESCRIPTIONS
        "A2500R24A, FCC"
      #endif
    },
  #endif  // __RADIO_A2500R24 FCC
};

#define RADIO_COUNT		(sizeof(appRadio) / sizeof(s_AppRadio));
uint8_t const radio_Count = sizeof(appRadio)/sizeof(s_AppRadio);                //!< Number of radios supported in the s_AppRadio structure.

FlagStruct Flags;                                                               //!< RX/TX Payload/Config/ACK Message Flags
ConfigStruct ConfigSettings[] = {0};                                    //!< Initialize Configuration Settings Information
RadioStruct RadioLocal = {0};

/**
 * @fn void InitRadio(s_AppRadio * pRadio)
 *
 * @brief This function initializes the radio to its default config, channel and
 *        power. It resets the radio upon power up.
 *
 * @param pRadio an s_AppRadio structure pointer
 */
void InitRadio(s_AppRadio * pRadio)
{
  RadioPowerOnReset(pCurrentFrameworkRadio(pRadio));                            // Reset the Radio

  #ifdef INCLUDE_FLASH_STORAGE
    unsigned char tempVar[3];

    tempVar[0] = MyFlashStorage.myRSCP.setting;
    tempVar[1] = MyFlashStorage.myRSCP.channel;
    tempVar[2] = MyFlashStorage.myRSCP.power;

    if (!ChangeConfiguration(&pRadio, 0, RadioLocal.currentRadio,tempVar[0],tempVar[1],tempVar[2]))
    {
      ChangeConfiguration(&pRadio, 0, RadioLocal.currentRadio,0,0,0);
    }
  #else
    ChangeConfiguration(&pRadio, 0, RadioLocal.currentRadio,0,0,0);
  #endif

}

/**
 * @fn unsigned char RXPacketProcessing(uint8_t * pBuffer)
 *
 * @brief This function processes the received packet to manipulate the flags
 *        necessary for config change cycle, payload acknowledgement
 *
 * @param pBuffer an integer pointer
 */
unsigned char RXPacketProcessing(uint8_t * pBuffer)
{
  Flags.RxConfigMessageType = (pBuffer[NEW_CONFIG_INDEX] & 0x80) ? RECEIVED_CONFIG_REQUEST :
                              (pBuffer[NEW_CONFIG_INDEX] & 0x40) ? RECEIVED_CONFIG_ACK :
                              (pBuffer[NEW_CONFIG_INDEX] & 0x20) ? RECEIVED_CONFIG_PING :
                                                                   RECEIVED_NO_CONFIG_CHANGE;
  Flags.RxACKMessageType     = (pBuffer[NEW_POWER_COMMAND] & 0x80) ? RECEIVED_ACK : RECEIVED_NO_ACK;
  Flags.RxPayloadMessageType = (pBuffer[NEW_POWER_COMMAND] & 0x40) ? RECEIVED_PAYLOAD : RECEIVED_NO_PAYLOAD;
  Flags.TxACKMessageType     = (pBuffer[NEW_POWER_COMMAND] & 0x40) ? SEND_ACK : SEND_NO_ACK;

  return Flags.RxPayloadMessageType;
}

/**
 * @fn uint8_t FrameSend(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t count, uint16_t timeout, uint8_t timeoutAction)
 *
 * @brief This function takes care of steps required in sending the packet. It flushes the RX-TX FIFOs and creates the
 *        data packet to be sent. Once the packet it transmitted, it loads the timer for the timeout value so that the
 *        radio is placed in low power state if frame timeout occures.
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param pBuffer an integer pointer
 * @param count an integer
 * @param timeout an integer
 * @param timeoutAction an integer
 *
 * @return an integer
 */
uint8_t FrameSend(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t count, uint16_t timeout, uint8_t timeoutAction)
{
  RadioDisableInterrupt(pCurrentFrameworkRadio(pRadio), __BSP_RADIO1_INTERRUPT1);
  
  RadioIdle(pCurrentFrameworkRadio(pRadio));                                    // Strobe Idle
  RadioFlushTXBuffer(pCurrentFrameworkRadio(pRadio));                           // Strobe flush TX FIFO
  RadioFlushRXBuffer(pCurrentFrameworkRadio(pRadio));                           // Strobe flush RX FIFO

  CreateDataPacket(pRadio, pBuffer, count, RadioLocal.TxFrameStruct.frameHeader, &RadioLocal.frameLength);          // Create the data packet to be sent
  pCurrentFrameworkRadio(pRadio)->radioState = RADIO_TRANSMIT;                                                      // Update radio state
  RadioLocal.FrameState = WAITING_FOR_SYNCWORD;                                                                     // Update frame state
  RadioWriteTXBuffer(pCurrentFrameworkRadio(pRadio), RadioLocal.TxFrameStruct.frameHeader, RadioLocal.frameLength); // Load Radio TX FIFO
  RadioSetInterruptEdge(pCurrentFrameworkRadio(pRadio), __BSP_RADIO1_INTERRUPT1, 1);
  RadioEnableInterrupt(pCurrentFrameworkRadio(pRadio), __BSP_RADIO1_INTERRUPT1);
  RadioTransmit(pCurrentFrameworkRadio(pRadio));                                                                    // Transmit the packet

  StartTimeoutTimer(timeout);                                                                                       // Load timer with timeout value.  The radio should be placed in a low-power state if frame timeout occurs.

  while(pCurrentFrameworkRadio(pRadio)->radioState == RADIO_TRANSMIT){          // Wait until transmit is complete.  
    if(RadioLocal.frameTimeout){                                                // This blocks all other application code (except ISR stuff) from running.
      RadioLocal.frameTimeout = 0;
      RadioLocal.FrameState = FRAME_IDLE;                                       // Update frame state
      CycleTimeoutAction(pRadio, timeoutAction);                                // If frame timeout occured, perform the timeout action
      return 0;
    }
    __BSP_LOW_POWER_MODE(LOW_POWER_MODE);                                       // Else stay in low power mode until the packet is being transmitted
  }

  TimerCCRDisableInterrupt(__BSP_TIMER1, __BSP_TIMER1_CCR1);

  pCurrentFrameworkRadio(pRadio)->radioState = RADIO_CALIBRATED;                // Restore radio state      
  
  Flags.TxPayloadMessageType = SEND_NO_PAYLOAD;                                 // Clear all TX flags
  Flags.TxACKMessageType = SEND_NO_ACK;

  return 1;
}

/**
 * @fn uint8_t FrameListen(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t * pCount, uint16_t timeout, uint8_t timeoutAction)
 *
 * @brief This function listens to receive a frame. It places the radio in receive mode and loads the timer with timeout
 *        value so that the radio is placed in low power state if nothing is received. If the packet is received, it 
 *        grabs the data from radio.
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param pBuffer an integer pointer
 * @param pCount an integer pointer
 * @param timeout an integer
 * @param timeoutAction an integer
 *
 * @return GetFrame a function
 */
uint8_t FrameListen(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t * pCount, uint16_t timeout, uint8_t timeoutAction)
{
  Flags.RxConfigMessageType = RECEIVED_NO_CONFIG_CHANGE;                        // Clear all RX flags
  Flags.RxPayloadMessageType = RECEIVED_NO_PAYLOAD;
  Flags.RxACKMessageType = RECEIVED_NO_ACK;
    
  ReceiveOn(pRadio);                                                            // Place radio into receive mode to look for ACK or config change order.

  StartTimeoutTimer(timeout);                                                   // Load timer with timeout value.  The radio should be placed in a low-power state if nothing received.

  while(pCurrentFrameworkRadio(pRadio)->radioState == RADIO_RECEIVE){           // Wait for an ACK or timeout event.  
    if(RadioLocal.frameTimeout){                                                // This blocks all other application code (except ISR stuff) from running.
      RadioLocal.frameTimeout = 0;
      RadioLocal.FrameState = FRAME_IDLE;                                       // Update frame state
      CycleTimeoutAction(pRadio, timeoutAction);                                // If frame timeout occured, perform the timeout action
      return 0;
    }
    __BSP_LOW_POWER_MODE(LOW_POWER_MODE);
  }
  
  TimerCCRDisableInterrupt(__BSP_TIMER1, __BSP_TIMER1_CCR1);

  return GetFrame(pRadio, pBuffer, pCount);                                     // Check to see if we received a packet.  If so, grab the data from the radio.
}

/**
 * @fn uint8_t GetFrame(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t * pCount)
 *
 * @brief This function grabs the data from radio and puts it into local buffer.
 *        It checks if a frame is received, and if so, it checks for a valid length.
 *        If the length is valid, it reads the data and status bytes from radio. 
 *        If length is not valid, it flushes the receive FIFO. At last, it checks
 *        for CRC okay and if so, it reads the payload data from the frame and 
 *        provides status update if its the time to report.
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param pBuffer an integer pointer
 * @param pCount an integer pointer
 *
 * @return an integer
 */
uint8_t GetFrame(s_AppRadio * pRadio, uint8_t * pBuffer, uint8_t * pCount)
{
  if(RadioLocal.FrameState == FRAME_RECEIVED){
    RadioLocal.FrameState = FRAME_IDLE;

    // This status register is safe to read since it will not be updated after
    // the packet has been received (See the CC1100 and 2500 Errata Note)
    if (RadioReadRegister(pCurrentFrameworkRadio(pRadio), CCXXX_STAT_RXBYTES) & BYTES_IN_RXFIFO){
      RadioLocal.RxFrameStruct.frameHeader[LENGTH] = RadioReadRegister(pCurrentFrameworkRadio(pRadio), CCXXX_REG_RXFIFO);// Read length byte
      if(RadioLocal.RxFrameStruct.frameHeader[LENGTH] < MAX_FRAME_LENGTH){      // Read the packet if length is valid
        RadioReadRXBuffer(pCurrentFrameworkRadio(pRadio), RadioLocal.RxFrameStruct.frameHeader + 1, RadioLocal.RxFrameStruct.frameHeader[LENGTH]++);
        RadioReadRXBuffer(pCurrentFrameworkRadio(pRadio), RadioLocal.linkStatus, 2);
      }
      else{
        // Make sure that the radio is in IDLE state before flushing the FIFO
        // (Unless RXOFF_MODE has been changed, the radio should be in IDLE state at this point)
        RadioIdle(pCurrentFrameworkRadio(pRadio));                              // Strobe Idle
        RadioFlushRXBuffer(pCurrentFrameworkRadio(pRadio));                     // Strobe flush RX FIFO
        // if valid packet is not received (there are no bytes in RXFIFO), there should not be any check for CRC okay,
        // else it will just return the previous value in the RadioLocal.linkStatus buffer
        return 0;  // so return
      }
    }

    if((RadioLocal.linkStatus[LQI] & 0x80) && (RadioReadRegister(pCurrentFrameworkRadio(pRadio), CCXXX_STAT_LQI) & 0x80)){// CRC OK?
      *pCount = RadioLocal.RxFrameStruct.frameHeader[LENGTH] - HEADER_LENGTH;   // Set the payload length
      if(*pCount <= sizeof(PayloadFrame)){
        if((void*)pCount != NULL){
          uint8_t i = 0;
          for(;i<(sizeof(((PayloadFrame *)pBuffer)->NodeID) + sizeof(((PayloadFrame *)pBuffer)->Flags));i++){
            pBuffer[i] = RadioLocal.RxFrameStruct.framePayload[i];
          }
          if(((PayloadFrame *)pBuffer)->Flags.PairingSolicitation || NodeIsInMyNet(((PayloadFrame *)pBuffer)->NodeID)){
            if(RXPacketProcessing(RadioLocal.RxFrameStruct.frameHeader)){       // Process the received packet to set necessary flags 
              for(;i<*pCount;i++){
                pBuffer[i] = RadioLocal.RxFrameStruct.framePayload[i];          // Store payload into local buffer
              }
            }
            return 1;
          }
        }
      }
    }
  }
  return 0;
}

/**
 * @fn uint8_t ChangeConfiguration(s_AppRadio ** pRadio, uint8_t remote, uint8_t radioIndex, uint8_t configIndex, uint8_t channelIndex, uint8_t powerIndex)
 *
 * @brief This function takes necessary steps to change local or remote configuration 
 *        based on the user's requirement. It checks if all config, channel and 
 *        power indices fed to it are within the range, if they are, it checks 
 *        if its a remote or local config change. For remote, it sets a flag to 
 *        initiate the config change request and loads config timeout value. For
 *        local, it updates the indices for config, channel and power and loads 
 *        new settings into the radio. At last, it sets the cycle time to the 
 *        default cycle time.
 *
 * @param pRadio an s_AppRadio structure double pointer
 * @param remote an integer
 * @param radioIndex an integer
 * @param configIndex an integer
 * @param channelIndex an integer
 * @param powerIndex an integer
 *
 * @return an integer
 */
uint8_t ChangeConfiguration(s_AppRadio ** pRadio, uint8_t remote, uint8_t radioIndex, uint8_t configIndex, uint8_t channelIndex, uint8_t powerIndex)
{
  // If all indices within range
  if(radioIndex   < radio_Count &&
     configIndex  < pCurrentRadioArraySizesStruct(&appRadio[radioIndex])->radioConfigurationCount &&
     channelIndex < pCurrentRadioArraySizesStruct(&appRadio[radioIndex])->radioChannelListCount &&
     powerIndex   < pCurrentRadioArraySizesStruct(&appRadio[radioIndex])->radioPowerListCount){

    if(remote){
      RadioLocal.TxFrameStruct.frameHeader[NEW_RADIO_INDEX]   = radioIndex;     // Using this field to send radio index for now.(do not want to make changes to header length yet)              
      RadioLocal.TxFrameStruct.frameHeader[NEW_CONFIG_INDEX]  = configIndex;    // Config index
      RadioLocal.TxFrameStruct.frameHeader[NEW_CHANNEL_INDEX] = channelIndex;   // Channel index
      RadioLocal.TxFrameStruct.frameHeader[NEW_POWER_COMMAND] = powerIndex;     // Power index

      Flags.TxConfigMessageType = SEND_CONFIG_REQUEST;
    }
    else{
      // Update radio index
      RadioLocal.oldRadio = RadioLocal.currentRadio;
      RadioLocal.currentRadio = radioIndex;

      *pRadio = &appRadio[RadioLocal.currentRadio];

      // Update config index and load new register settings into radio
      pCurrentConfigSettingsStruct()->oldRFICConfig = CurrentBaseConfig();
      pCurrentConfigSettingsStruct()->currentRFICConfig = configIndex;

      // Update channel index and load new value into radio
      pCurrentConfigSettingsStruct()->oldRFChannelNum = CurrentChannel();
      pCurrentConfigSettingsStruct()->currentRFChannelNum = channelIndex;

      // Update power index and load new value into radio
      pCurrentConfigSettingsStruct()->oldRFPower = CurrentPower();
      pCurrentConfigSettingsStruct()->currentRFPower = powerIndex < pCurrentRadioConfigurationStruct(*pRadio)->pConfigurationChannel[CurrentChannel()].radioPowerIndex ?
                                                                    pCurrentRadioConfigurationStruct(*pRadio)->pConfigurationChannel[CurrentChannel()].radioPowerIndex : powerIndex;

      #ifdef INCLUDE_FLASH_STORAGE
        WriteMyFlashedRSCP(RadioLocal.currentRadio,
                           pCurrentConfigSettingsStruct()->currentRFICConfig,
                           pCurrentConfigSettingsStruct()->currentRFChannelNum,
                           pCurrentConfigSettingsStruct()->currentRFPower);     // If flash storage is enabled, save new settings
      #endif

      // Wakeup the current radio
      if(pCurrentFrameworkRadio(*pRadio)->radioState == RADIO_SLEEP){           // If radio is in sleep due to last timeout action      
        RadioWakeUp(pCurrentFrameworkRadio(*pRadio),
                    &pCurrentRadioConfigurationStruct(*pRadio)->pRegisterSettings->registerSettings,
                    &(*pRadio)->pRadioPowerList[CurrentPower()].radioPower);    // Wake up the radio (SYNC_TIMEOUT_ACTION = SLEEP)
        pCurrentFrameworkRadio(*pRadio)->radioState = RADIO_CALIBRATED;         // Restore the radio state
      }
      else{
        RadioIdle(pCurrentFrameworkRadio(*pRadio));                             // Place selected radio in IDLE
      }

      // Load new settings into radio registers
      RadioUpdateSettings(pCurrentFrameworkRadio(*pRadio),
                         &pCurrentRadioConfigurationStruct(*pRadio)->pRegisterSettings->registerSettings,
                         &(*pRadio)->pRadioChannelList[pCurrentRadioConfigurationStruct(*pRadio)->pConfigurationChannel[CurrentChannel()].radioChannelIndex].radioChannel,
                         &(*pRadio)->pRadioPowerList[CurrentPower()].radioPower);

      if((Flags.TxConfigMessageType == SEND_CONFIG_PING) &&
         (Flags.RxConfigMessageType != RECEIVED_CONFIG_ACK)){
      }
    }
    return 1;
  }
  return 0;
}

/**
 * @fn void CreateDataPacket(s_AppRadio * pRadio, uint8_t * pBufferIn, uint8_t countIn, uint8_t * pBufferOut, uint8_t * countOut)
 *
 * @brief This function loads the buffer to send the data out in the packet. It  
 *        sets the bit fields based on config change cycle flags, payload and 
 *        acknowledgement flags. It reads the RSSI, LQI and frequency offset 
 *        values from radio and places in the packet to give status update to the 
 *        remote module. At the end, it puts the payload data available from the 
 *        application, into the packet.
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param pBufferIn an integer pointer
 * @param countIn an integer
 * @param pBufferOut an integer pointer
 * @param countOut an integer
 */
void CreateDataPacket(s_AppRadio * pRadio, uint8_t * pBufferIn, uint8_t countIn, uint8_t * pBufferOut, uint8_t * countOut)
{
  *countOut = HEADER_LENGTH + countIn;

  pBufferOut[LENGTH] = *countOut - 1;				
  pBufferOut[DESTINATION_ADDR] = 0x00;                                          // Destination address;
  pBufferOut[SOURCE_ID] = 0x00;                                                 // Source node ID;

  pBufferOut[NEW_CONFIG_INDEX] &= 0x1F;                                         // Configuration;
  
  if(Flags.TxConfigMessageType == SEND_CONFIG_REQUEST){                         // 0x80 = Config Change Request,
     pBufferOut[NEW_CONFIG_INDEX] |= 0x80;
  }
  else if(Flags.TxConfigMessageType == SEND_CONFIG_ACK){                        // 0x40 = Config Change ACK,
     pBufferOut[NEW_CONFIG_INDEX] |= 0x40;
  }
  else if(Flags.TxConfigMessageType == SEND_CONFIG_PING){                       // 0x20 = Config change ping,
     pBufferOut[NEW_CONFIG_INDEX] |= 0x20;
  }

  pBufferOut[NEW_POWER_COMMAND] &= 0x3F;                                        // Power and Command;
  
  if(Flags.TxACKMessageType == SEND_ACK){                                     
    pBufferOut[NEW_POWER_COMMAND] |= 0x80;                                      // 0x80 = ACK for received data,  
  }
  if(countIn){
    pBufferOut[NEW_POWER_COMMAND] |= 0x40;                                      // 0x40 = Payload is a data,                                        
  }
  
  pBufferOut[RSSI_RECEIVER] = RadioLocal.linkStatus[RSSI];                      // RSSI @ receiver
  pBufferOut[LQI_RECEIVER] = RadioLocal.linkStatus[LQI];	                // LQI @ receiver
  pBufferOut[FREQ_OFFSET_RECEIVER] = RadioReadRegister(pCurrentFrameworkRadio(pRadio), CCXXX_STAT_FREQEST); // Frequency offset @ receiver

  pBufferOut[CURRENT_POWER_INDEX] = pCurrentConfigSettingsStruct()->currentRFPower; // Power @ receiver

  if(Flags.TxPayloadMessageType == SEND_PAYLOAD){
    uint8_t i;
    for(i=0;i<countIn;i++){
      pBufferOut[HEADER_LENGTH+i] = *(pBufferIn + i);                           // Payload
    }
  }
}

/**
 * @fn void CycleTimeoutAction(s_AppRadio * pRadio, uint8_t action)
 *
 * @brief This function performs the cycle timeout action based on the action provided
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param action an integer
 */
void CycleTimeoutAction(s_AppRadio * pRadio, uint8_t action)
{
  switch (action)
  {
    case SET_RADIO_IDLE :
      RadioIdle(pCurrentFrameworkRadio(pRadio));                                // Strobe Idle
      pCurrentFrameworkRadio(pRadio)->radioState = RADIO_CALIBRATED;            // Update radio state
      break;
    case SET_RADIO_SLEEP :
//      RadioSleep(pCurrentFrameworkRadio(pRadio));                               // Put radio to sleep
//      pCurrentFrameworkRadio(pRadio)->radioState = RADIO_SLEEP;                 // Update radio state
      break;
    default:
      break;
  }
}

/**
 * @fn void ReceiveOn(s_AppRadio * pRadio)
 *
 * @brief This function performs steps necessary to put the radio in receive mode.
 *        It flushes the receive FIFO, enables the GDO0 interrupt at rising edge
 *        to check if sync word in received. It then updates radio and frame states
 *        and strobes receive command.
 *
 * @param pRadio an s_AppRadio structure pointer
 */
void ReceiveOn(s_AppRadio * pRadio)
{
  RadioIdle(pCurrentFrameworkRadio(pRadio));                                    // Strobe Idle
  RadioFlushRXBuffer(pCurrentFrameworkRadio(pRadio));                           // Strobe flush RX FIFO

  RadioDisableInterrupt(pCurrentFrameworkRadio(pRadio), __BSP_RADIO1_INTERRUPT1);
  RadioSetInterruptEdge(pCurrentFrameworkRadio(pRadio), __BSP_RADIO1_INTERRUPT1, 0);
  RadioEnableInterrupt(pCurrentFrameworkRadio(pRadio), __BSP_RADIO1_INTERRUPT1);

  pCurrentFrameworkRadio(pRadio)->radioState = RADIO_RECEIVE;                   // Update radio state
  RadioLocal.FrameState = WAITING_FOR_SYNCWORD;                                 // Update frame state
  RadioReceive(pCurrentFrameworkRadio(pRadio));                                 // Strobe RX
}

/**
 * @fn AppRadioArraySizes * pCurrentRadioArraySizesStruct(s_AppRadio * pRadio)
 *
 * @brief This function returns the pointer to array size of the Radio in use.
 *
 * @param pRadio an s_AppRadio structure pointer
 *
 * @return an AppRadioArraySizes structure pointer
 */
AppRadioArraySizes * pCurrentRadioArraySizesStruct(s_AppRadio * pRadio)
{
  return pRadio->pRadioArraySizes;                                              // Pointer to the array size of current radio.
}

/**
 * @fn ConfigStruct * pCurrentConfigSettingsStruct(void)
 *
 * @brief This function returns the current configuration in use for current radio.
 *
 * @return a ConfigStruct structure pointer
 */
ConfigStruct * pCurrentConfigSettingsStruct(void)
{
  return &ConfigSettings[RadioLocal.currentRadio];                              // Current configuration is use for current radio.
}

/**
 * @fn AppRadioConfiguration * pCurrentRadioConfigurationStruct(s_AppRadio * pRadio)
 *
 * @brief This function returns the pointer to the current configuration structure 
 *        in use for current radio.
 *
 * @return an AppRadioConfiguration structure pointer
 */
AppRadioConfiguration * pCurrentRadioConfigurationStruct(s_AppRadio * pRadio)
{
  return &pRadio->pRadioConfiguration[CurrentBaseConfig()];                     // Pointer to the current configuration structure in use for current radio.
}

/**
 * @fn Radio * pCurrentFrameworkRadio(s_AppRadio * pRadio)
 *
 * @brief This function returns the pointer to current framework radio in use.
 *
 * @return a Radio structure pointer
 */
Radio * pCurrentFrameworkRadio(s_AppRadio * pRadio)
{
  return pRadio->frameworkRadio;                                                // Pointer to current Framework Radio in use
}

/**
 * @fn uint8_t CurrentRadio(void)
 *
 * @brief Returns the index of current radio in use
 *
 * @return an integer
 */
uint8_t CurrentRadio(void)
{
  return RadioLocal.currentRadio;                                               // Current Radio in use
}

/**
 * @fn uint8_t CurrentBaseConfig(void)
 *
 * @brief Returns the index of current configuration set
 *
 * @return an integer
 */
uint8_t CurrentBaseConfig(void)
{
  return pCurrentConfigSettingsStruct()->currentRFICConfig;                     // Current Config for CCxxxx
}

/**
 * @fn uint8_t CurrentChannel(void)
 *
 * @brief Returns the index of current channel in use
 *
 * @return an integer
 */
uint8_t CurrentChannel(void)
{
  return pCurrentConfigSettingsStruct()->currentRFChannelNum;                   // Current Channel Number for CCxxxx
}

/**
 * @fn uint8_t CurrentPower(void)
 *
 * @brief Returns the index of current power setting in use
 *
 * @return an integer
 */
uint8_t CurrentPower(void)
{
  return pCurrentConfigSettingsStruct()->currentRFPower;                        // Current Power for CCxxxx
}

/**
 * @fn uint8_t ReadMARCSTATE(s_AppRadio * pRadio)
 *
 * @brief This radio reads the current state of the MARCSTATE status reg for CCxxxx. 
 *        It must be read up to 4 times(see errata).
 *
 * @param pRadio an s_AppRadio structure pointer
 *
 * @return an integer
 */
uint8_t ReadMARCSTATE(s_AppRadio * pRadio)
{
  uint8_t loopCount, localStatus[4];
  // Read the current state of MARCSTATE status reg for CCxxxx.  Must be read up to 4 times (see device errata).
  localStatus[0] = RadioReadRegister(pCurrentFrameworkRadio(pRadio), CCXXX_STAT_MARCSTATE);
  for(loopCount=1;loopCount<4;loopCount++){
    localStatus[loopCount] = RadioReadRegister(pCurrentFrameworkRadio(pRadio), CCXXX_STAT_MARCSTATE);
    if ( localStatus[loopCount] == localStatus[loopCount-1] )
    { 
      return localStatus[loopCount];
    }
  }
  return 0xFF;
}

/**
 * @fn void RadioOperation(void)
 *
 * @brief ISR extension of Communication Module 1 ISR. This functionality is
 *        currently not implemented.
 */
void RadioOperation(void)
{
}

/**
 * @fn signed int RSSI2dBm(unsigned char rssi)  
 *
 * @brief This function shifts the RSSI value to have the decimal point between 
 *        the two bytes in the integer and adds offset to it(see CC110L datasheet).
 *
 * @param rssi an unsigned int
 *
 * @return signed int
 */
signed int RSSI2dBm(unsigned char rssi) 
{
  signed int temp, offset;
  temp = (rssi < 128 || rssi >= 148) ? (signed int)(signed char)rssi : -108;    // Remove -128.5dBm to -138dBm range since they exceed size of data type and are not valid values from radio
  temp <<= 7;                                                                   // RSSI is in 1/2 dB's, move it up to have the decimal point between the two bytes in the int
  offset = -74 * 256;                                                           // hardcoded for now, recommended value from CC110L datasheet
  // This really should be an offset specifically measured for each config setting......
  temp += offset;                                                               //Radio...etc...RSSI_Offset.
  return temp;
}

/**
 * @fn uint8_t RadioFrameTimeoutTimer(s_AppRadio * pRadio, enum RADIO_STATE state, uint16_t timeout, uint8_t timeoutAction)
 *
 * @brief This function checks if the timeout event has been occured and performs
 *        the specified timeout action.
 * 
 * @param pRadio a s_AppRadio structure pointer
 * @param state an RADIO_STATE enum
 * @param timeout an unsigned int
 * @param timeoutAction an unsigned int
 * 
 * @return an unsigned int
 */
uint8_t RadioFrameTimeoutTimer(s_AppRadio * pRadio, enum RADIO_STATE state, uint16_t timeout, uint8_t timeoutAction)
{
  StartTimeoutTimer(timeout);

  while(pCurrentFrameworkRadio(pRadio)->radioState == state){                   // Wait for an ACK or timeout event.  
    if(RadioLocal.frameTimeout){                                                // This blocks all other application code (except ISR stuff) from running.
      RadioLocal.frameTimeout = 0;
      RadioLocal.FrameState = FRAME_IDLE;                                       // Update frame state
      CycleTimeoutAction(pRadio, timeoutAction);                                // If frame timeout occured, perform the timeout action
      return 0;
    }
    __BSP_LOW_POWER_MODE(LOW_POWER_MODE);
  }
  return 1;
}

/**
 * @fn void StartTimeoutTimer(uint16_t timeout)
 *
 * @brief This function loads the timeout value into the timer.
 * 
 * @param timeout an unsigned int
 */
void StartTimeoutTimer(uint16_t timeout)
{
  uint16_t tempVar  = TimerGetCount(__BSP_TIMER1);
  uint16_t tempVar0 = TimerGetCCR(__BSP_TIMER1, __BSP_TIMER1_CCR0);
  uint16_t tempTimeout = (timeout * 12) + tempVar;

  if(tempVar0 > tempTimeout){                                                   // If timeout is less than the time remaining in the cycle
    TimerSetCCR(__BSP_TIMER1, __BSP_TIMER1_CCR1, tempTimeout);                  // Load timeout
  }
  else{
    TimerSetCCR(__BSP_TIMER1, __BSP_TIMER1_CCR1, tempTimeout - tempVar0);       // Load the difference
  }
  RadioLocal.frameTimeout = 0;
  TimerCCRClearInterrupt(__BSP_TIMER1, __BSP_TIMER1_CCR1);
  TimerCCREnableInterrupt(__BSP_TIMER1, __BSP_TIMER1_CCR1);
}
