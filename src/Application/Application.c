/**
 *  @file Application.c
 *
 *  @brief Application Layer Function Definitions
 *         This file defines the functions for Application-State Operations, 
 *         Network Setup and Validation.
 *         Function definitions for Application Layer Command-Interface are 
 *         included within this file.
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

#ifdef INCLUDE_FLASH_STORAGE
  #ifndef __IAR_SYSTEMS_ICC__
    #pragma DATA_SECTION ( MyFlashStorage , ".infoD" );
    FlashStorage MyFlashStorage;                                         //!< Flash storage of the whole structure containing NodeIDs, RSCP, AppState
  #else
    __no_init FlashStorage MyFlashStorage @ __BSP_FLASH1_BASE_ADDRESS;   //!< Flash storage of the whole structure containing NodeIDs, RSCP, AppState
  #endif  //__IAR_SYSTEMS_ICC__
#endif  //INCLUDE_FLASH_STORAGE
  
volatile __ApplicationState ApplicationState = HUB;

/*! The pairingMask is used as a mask to all AddNodeIDToNetwork() calls. A zero 
  mask will not allow any nodes to be added to the network (paired) and 
  a 0xFFFFFFFF mask will allow any node to be added (provided there is room left 
  in the array holding the node ID's).
  Since the protocol ALWAYS will attempt to add an unknown node to the network, 
  the pairingMask is the only means for controlling pairing.
*/
unsigned long pairingMask;
NodeInfo Nodes[MAX_NODES] = {0};                                                //!< Structure to store the information of the node itself, and the nodes its paired with.

/*! If the payload frame is bigger than what will fit in the radio frame 
  then PAYLOAD_SIZE_VALIDATION will evaluate to -1 and a compiler error will 
  be generated on the below allocation. If the payload size will fit then 
  PAYLOAD_SIZE_VALIDATION will evaluate to 1, and no compile errors will
  be generated. This 'quirky' construction is necessary because the pre-processor 
  does not know the sizes of things and we want to generate a compile error 
  to avoid overwriting other data areas (without costly run time checks).
*/
PayloadFrame Payloads[2*PAYLOAD_SIZE_VALIDATION];                               // Allows us to buffer payloads or prepare seperate payloads, should we so desire

/**
 * @fn uint8_t WirelessOperation(unsigned int * pBuffer)
 *
 * @brief This function listens for incoming frames, qualifies the data as 
 *        being from a network member, and if so copies data to Nodes[].InData[]
 *        and returns the node IDindex that it came from
 *
 * @return an unsigned int, IDindex; >0 is valid, =0 is invalid/no data
 */
uint8_t WirelessOperation(unsigned int * pBuffer)
{
  s_AppRadio * pRadio = &appRadio[RadioLocal.currentRadio];

  // ----------- Check for the PushButton input ------------
  if (pushButtonAction)
  {
    switch (pushButtonAction)
    {
      unsigned char i;

      case FLASH_FACTORY_DEFAULT :
        for(i=0;i<MAX_NODES;i++){                                               // Remove all the nodes from paired nodes list, so that when the GUI reads the nodes list, 
          RemoveNodeFromNetwork(i);                                             // it sees the network change and updates according to it.
        }
        ChangeConfiguration(&pRadio, 0, 0, 0, 0, 0);
        // If GUI sees an application state change, it reads the nodes list and updates the network change itself. 
        // This works if the application state is sensor and is changed to hub. But if the application state is
        // already hub, the GUI does not see any state change and it does not update the network change itself. 
        // So this condition is placed to make sure that the network gets updated. (for GUI).
        if (ApplicationState == HUB)                                            
        {
          #if defined(__COMMAND_INTERFACE)
            NetworkChanged();                                                   // Report to GUI that the netowrk has been changed.
            PhysicalChanged();                                                  // Report to GUI that the RSCP settings have been changed.
          #endif
        }
        SetApplicationState(HUB);
        break;

      case ENABLE_PAIRING_HUB_TO_SENSOR :                                       // Change application state to sensor and place it in pairing mode immediately.
        SetApplicationState(SENSOR);
		// NOTE: Fall through to pair the devices.
      case ENABLE_PAIRING :
        SetPairingMask(0xFFFFFFFF);
        SoftwareTimerSetInterval(__BSP_SWTIMER[0], 1000);                       // Set 10 second timeout
        SoftwareTimerEnable(__BSP_SWTIMER[0]);
        break;

      case NEXT_APPLICATION_STATE :
        for (i=1;i<MAX_NODES;i++) {
          RemoveNodeFromNetwork(i);                                             // Remove all the nodes from paired nodes list
        }
        if (ApplicationState == HUB) SetApplicationState(SENSOR);
        else if(ApplicationState == SENSOR) SetApplicationState(HUB);
		// NOTE: Fall through to display state change with LEDs.
      case GET_APPLICATION_STATE :
        if (ApplicationState == HUB) BlinkLED(__BSP_LEDRED1, 2, 20);
        else if(ApplicationState == SENSOR) BlinkLED(__BSP_LEDRED1, 3, 20);
        break;

      default :
        break;
    }
    
    pushButtonAction = 0;
  }

  if (swTimerAction == DISABLE_PAIRING)
  {
    SoftwareTimerDisable(__BSP_SWTIMER[0]);
    swTimerAction = 0;
    if (GetPairingMask())
    {
      SetPairingMask(0x00000000);
    }
  }


  if(ApplicationState == HUB)
  {
    return HubWirelessOperation(pRadio, pBuffer);
  }
  else if(ApplicationState == SENSOR)
  {
    return SensorWirelessOperation(pRadio, pBuffer);
  }
  return 0;
}

/**
 * @fn uint8_t HubWirelessOperation(s_AppRadio * pRadio, unsigned int * pBuffer)
 *
 * @brief This function listens for incoming frames, qualifies the data as 
 *        being from a network member, and if so copies data to Nodes[].InData[]
 *        and returns the node IDindex that it came from
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param pBuffer an unsigned integer pointer
 *
 * @return an unsigned int, IDindex; >0 is valid, =0 is invalid/no data
 */
uint8_t HubWirelessOperation(s_AppRadio * pRadio, unsigned int * pBuffer)
{
  uint8_t IDindex;
  uint8_t ByteCount;

  Payloads[NODE_ACK_TEMP_FRAME].Data[0] = (pBuffer[0] & 0xFFF0) | (pBuffer[2] & 0x0001);   // my own AnalogInput | DigitalInput
  Payloads[NODE_ACK_TEMP_FRAME].Data[1] = (pBuffer[3] & 0xFFF0) | (pBuffer[1] & 0x0001);   // my own AnalogOutput | DigitalOutput

  if (Listen(pRadio, (uint8_t *)&Payloads[0], &ByteCount)) {                    // Listen for a packet from remote (sensor/actuator)
    //We should perhaps check here if we got a full payload?
    IDindex = NetworkValidation(&Payloads[INCOMING_FRAME]);                     // Data from the radio is available, check if its from a member, if so copy the data and return the node index it came from.
    if (IDindex){
      //If there is a need, do something with the data here. Populate the user's buffer with the data

      if(Payloads[INCOMING_FRAME].Data[2] & 0x0004){                            // If there is new data(for PWM) from the remote module's GUI
        Nodes[0].Data[3] = Payloads[INCOMING_FRAME].Data[2] & 0xFFF0;           // Mask of the bit for new data, because it is not needed any more.
      }                                                                         // Else use old data
      pBuffer[3] = Nodes[0].Data[3];                                            

      if(Payloads[INCOMING_FRAME].Data[2] & 0x0002){                            // If there is new data(for green LED) from the remote module's GUI
        Nodes[0].Data[1] = Payloads[INCOMING_FRAME].Data[2] & 0x0001;           // Mask of the bit for new data, because it is not needed any more.
      }                                                                         // Else use old data
      pBuffer[1] = Nodes[0].Data[1];                                          
      Payloads[NODE_ACK_TEMP_FRAME].Data[2] = 0x0000;                           // Clear the field as the same buffer is used for outgoing frames to all the paired modules.      

      return IDindex;                                                           // Allow main() to be notified of the newly arrived data, which is now in Nodes[].InData[]
    }
  }
  return 0;                                                                     // There is no data or it was not from a network member
}

/**
 * @fn uint8_t SensorWirelessOperation(s_AppRadio * pRadio, unsigned int * pBuffer)
 *
 * @brief This function initiates a data exchange, qualifies any received data as 
 *        being from a network member, and if so copies data to Nodes[].InData[]
 *        and returns the node IDindex that it came from
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param pBuffer an unsigned integer pointer
 *
 * @return an unsigned int, IDindex; >0 is valid, =0 is invalid/no data
 */
uint8_t SensorWirelessOperation(s_AppRadio * pRadio, unsigned int * pBuffer)
{
  uint8_t IDindex;
  uint8_t ByteCount = sizeof(PayloadFrame);
  //If there is a need to do additional stuff prior to send, do it here!
  
  if (DataExchange(pRadio, (uint8_t *)(SensorPayload(pBuffer)), &ByteCount)) {  // Prepare the sensor/actuator payload and initiate data exchange
    //We should perhaps check here if we got a full payload?
    IDindex = NetworkValidation(&Payloads[0]);                                  // Data from the radio is available, check if its from a member, if so copy the data and return the node index it came from.
    if (IDindex){
      //If there is a need, do something with the data here. Populate the user's buffer with the data
      
      if(Payloads[INCOMING_FRAME].Data[2] & 0x0004){                            // If there is new data(for PWM) from the remote module's GUI
        Nodes[0].Data[3] = Payloads[INCOMING_FRAME].Data[2] & 0xFFF0;           // Mask of the bit for new data, because it is not needed any more.
      }                                                                         // Else use old data
      pBuffer[3] = Nodes[0].Data[3];                                            

      if(Payloads[INCOMING_FRAME].Data[2] & 0x0002){                            // If there is new data(for green LED) from the remote module's GUI
        Nodes[0].Data[1] = Payloads[INCOMING_FRAME].Data[2] & 0x0001;           // Mask of the bit for new data, because it is not needed any more.
      }                                                                         // Else use old data
      pBuffer[1] = Nodes[0].Data[1];                                          
      Payloads[INCOMING_FRAME].Data[2] = 0x0000;                                // Clear the field as the same buffer is used for the incoming frame.
      
      if(Nodes[0].CurrentCycleTime != Payloads[0].CycleTime){
        SetCycleTime(pRadio, 0, Payloads[0].CycleTime);
      }
      return IDindex;                                                           // Allow main() to be notified of the newly arrived data, which is now in Nodes[].InData[]
    }
  }
  return 0;                                                                     // There is no data or it was not from a network member
}

/**
 * @fn unsigned char NetworkValidation(PayloadFrame *AppFrame) 
 *
 * @brief This function performs network validation by checking the pairing with 
 *        the node. If the node is not paired with, it adds it to the network. 
 *        Else it checks if the node is already in the network. If command interface 
 *        is included, it makes a call to a function to output the data and RSSI from the node.
 *
 * @param AppFrame a PayloadFrame structure pointer
 *
 * @return an unsigned char
 */
unsigned char NetworkValidation(PayloadFrame * AppFrame) 
{
  unsigned char i; 
  if (AppFrame->Flags.PairingSolicitation) {                                    // If node not paired with, add it to the network
    i = AddNodeToNetwork(AppFrame->NodeID);
  } else {
    i = NodeIsInMyNet(AppFrame->NodeID);                                        // Else node is already in the net
  }
  if (i) {
      Nodes[i].Data[0] = AppFrame->Data[0] & 0xFFF0;                            // Temperature of the remote unit.
      Nodes[i].Data[2] = AppFrame->Data[0] & 0x000F;                            // State of red LED of the remote unit.
      Nodes[i].Data[3] = AppFrame->Data[1] & 0xFFF0;                            // PWM of the remote unit.
      Nodes[i].Data[1] = AppFrame->Data[1] & 0x000F;                            // State of green LED of the remote unit.
    
    #ifdef __COMMAND_INTERFACE
      ReportStatus(i);                                                          // Tell GUI all about the RSSI values
      ReportData(i);                                                            // Tell the GUI all about the newly arrived data                                         
    #endif
    return i;
  }
  return 0;
 
}

/**
 * @fn PayloadFrame *NodeAckPayload(unsigned long NodeID)
 *
 * @brief This function checks if the node is in the net and then stores the 
 *        payload or ACK data to be sent, into the Payloads structure. This 
 *        function is used by hub.
 *
 * @param NodeID an unsigned long
 *
 * @return a PayloadFrame structure pointer
 */
PayloadFrame * NodeAckPayload(unsigned long NodeID)                            
{
  unsigned char i=NodeIsInMyNet(NodeID);
  if (i) {                                                                      // If the node is a member, we will fill in stored data for it.
    Payloads[NODE_ACK_TEMP_FRAME].NodeID = Nodes[0].ID;                         // Tell sensor who we are

    if(Payloads[INCOMING_FRAME].Data[1] & 0x0002){                              // If the remote module has a new data from GUI, for his green LED.
      Payloads[NODE_ACK_TEMP_FRAME].Data[2] = Payloads[INCOMING_FRAME].Data[1] & 0x0001; // Get the new data for the green LED and mask it off.
    }                                                                           // no need to send back the bit for new data.
    if(Nodes[i].Data[1] & 0x0002){                                              // If I have the new data from the GUI, for remote module's green LED.
      Payloads[NODE_ACK_TEMP_FRAME].Data[2] = Nodes[i].Data[1] & 0x0003;        // Need to send the bit for new data, because it is coming from my GUI.
    }
    
    if(Payloads[INCOMING_FRAME].Data[1] & 0x0004){                              // If the remote module has a new data from GUI, for his PWM.
      Payloads[NODE_ACK_TEMP_FRAME].Data[2] |= Payloads[INCOMING_FRAME].Data[1] & 0xFFF0; // Get the new data for the PWM and mask it off.
    }                                                                           // no need to send back the bit for new data.
    else if(Nodes[i].Data[3] & 0x0004){                                         // If I have the new data from the GUI, for remote module's PWM.
      Payloads[NODE_ACK_TEMP_FRAME].Data[2] |= Nodes[i].Data[3] & 0xFFF4;       // Need to send the bit for new data, because it is coming from my GUI.
    }
    
    Payloads[NODE_ACK_TEMP_FRAME].Flags.PairingSolicitation = Payloads[INCOMING_FRAME].Flags.PairingSolicitation; // Payloads[0] is the receive frame
    Payloads[NODE_ACK_TEMP_FRAME].CycleTime = Nodes[0].CurrentCycleTime;
    return &Payloads[NODE_ACK_TEMP_FRAME];
  } else {                                                                      // If he's not a member dont tell him anything!
    return 0;
  }
}

/**
 * @fn PayloadFrame * SensorPayload(unsigned int * pBuffer)
 *
 * @brief This fucntion creates a payload frame to be sent by sensor.
 *
 * @param pBuffer an unsigned integer pointer
 *
 * @return a PayloadFrame structure pointer
 */
PayloadFrame * SensorPayload(unsigned int * pBuffer) 
{
  //unsigned char i=NodeIsInMyNet(NodeID);
  // The sensor is unique in that it always must be able to send out a pairing message, this will make it also send analog data etc.
  // If thats not desired then dont set i=1 and use the if below to make appropriate actions
  if (1) {                                                                   
    Payloads[SENSOR_SEND_FRAME].NodeID = Nodes[0].ID;                           // Tell sensor who we are
    
    if(Payloads[INCOMING_FRAME].Data[1] & 0x0002){                              // If the remote module has a new data from GUI, for his green LED.
      Payloads[SENSOR_SEND_FRAME].Data[2] = Payloads[INCOMING_FRAME].Data[1] & 0x0001; // Get the new data for the green LED and mask it off.
    }                                                                           // No need to send back the bit for new data.
    if(Nodes[1].Data[1] & 0x0002){                                              // If I have the new data from the GUI, for remote module's green LED.
      Payloads[SENSOR_SEND_FRAME].Data[2] = Nodes[1].Data[1] & 0x0003;          // Need to send the bit for new data, because it is coming from my GUI.
    }
    
    if(Payloads[INCOMING_FRAME].Data[1] & 0x0004){                              // If the remote module has a new data from GUI, for his PWM.
      Payloads[SENSOR_SEND_FRAME].Data[2] |= Payloads[INCOMING_FRAME].Data[1] & 0xFFF0; // Get the new data for the PWM and mask it off.
    }                                                                           // No need to send back the bit for new data.
    else if(Nodes[1].Data[3] & 0x0004){                                         // If I have the new data from the GUI, for remote module's PWM.
      Payloads[SENSOR_SEND_FRAME].Data[2] |= Nodes[1].Data[3] & 0xFFF4;         // Need to send the bit for new data, because it is coming from my GUI.
    }
  
    Payloads[SENSOR_SEND_FRAME].Data[0] = (pBuffer[0] & 0xFFF0) | pBuffer[2] ;  // my own AnalogInput | DigitalInput 
    Payloads[SENSOR_SEND_FRAME].Data[1] = pBuffer[1] | (pBuffer[3] & 0xFFF0);   // my own DigitalOutput | AnalogOutput
   
    if (GetPairingMask()) {
      Payloads[SENSOR_SEND_FRAME].Flags.PairingSolicitation = 1;
    } else {
      Payloads[SENSOR_SEND_FRAME].Flags.PairingSolicitation = 0;
    }
    Payloads[SENSOR_SEND_FRAME].CycleTime = Nodes[0].CurrentCycleTime;
    return &Payloads[SENSOR_SEND_FRAME];
  } else {                                                                      // If he's not a member dont tell him anything!
    return 0;
  }
}

/**
 * @fn uint8_t SetApplicationState(__ApplicationState state) 
 *
 * @brief This function sets the application state of the node. If flash storage
 *        is included, it writes the state to flash.
 *
 * @param state an __ApplicationState enumeration
 *
 * @return an unsigned int
 */
uint8_t SetApplicationState(__ApplicationState state) 
{
  #ifdef INCLUDE_FLASH_STORAGE
    FlashWriteBuffer((unsigned char *)&MyFlashStorage.myAppState, (unsigned char *)&state, sizeof(state)); // Write the new application state to flash.
  #endif
  ApplicationState = state;                                                     // Change application state.
  #ifdef __COMMAND_INTERFACE
    ApplicationChanged();                                                       // Report to GUI that the application state has been changed.
  #endif
  return 1;
}

/**
 * @fn unsigned char SetMyNodeID(unsigned long NodeID)
 *
 * @brief This function sets the node ID of the node itself. If flash storage is
 *        included, it writes its own ID to flash. If command interface is included,
 *        it makes a call to a function to inform the GUI that a network change has 
 *        taken place.
 *
 *        Providing NodeID with a value of zero or 0xFFFFFFFF will cause ID to be
 *        read from flash if flash storage is included.  If the ID in flash is
 *        equal to zero or 0xFFFFFFFF, or if flash storage is not included, a new
 *        random ID will be created.
 *
 * @param NodeID an unsigned long
 *
 * @return an unsigned char
 */
unsigned char SetMyNodeID(unsigned long NodeID) 
{
  if ((NodeID != 0) && (NodeID != 0xFFFFFFFF)) {
    Nodes[0].ID = NodeID;
    #ifdef INCLUDE_FLASH_STORAGE
      WriteMyFlashedID(NodeID);                                                 // Store NodeID in Flash so it starts up this way.
    #endif
    #ifdef __COMMAND_INTERFACE
      NetworkChanged();
    #endif
    return 1;                                                                   // Return 1 only when Nodes[0].ID set to NodeID arg
  }
  else {
    #ifdef INCLUDE_FLASH_STORAGE
      NodeID = ReadMyFlashedID();
      if ((NodeID == 0) || (NodeID == 0xFFFFFFFF)) {
        WriteMyFlashedID(Nodes[0].ID);                                          // Store NodeID in Flash so it starts up this way.
      }
      else {
        Nodes[0].ID = NodeID;
      }
    #endif
    #ifdef __COMMAND_INTERFACE
      NetworkChanged();
    #endif
  }
  return 0;
}

/**
 * @fn inline void SetPairingMask(unsigned long mask)
 *
 * @brief This function sets the pairing mask for the node. If command interface 
 *        is included, it makes a call to a function to inform the GUI that a 
 *        network change has taken place.
 *
 * @param mask an unsigned long
 */
//inline void SetPairingMask(unsigned long mask) 
void SetPairingMask(unsigned long mask) 
{
  pairingMask = mask;
  #ifdef __COMMAND_INTERFACE
    NetworkChanged();                                                           // Report to GUI that the network has been changed.
  #endif
}

/**
 * @fn inline unsigned long GetPairingMask(void)
 *
 * @brief This function returns the pairing mask of the node.
 *
 * @return an unsigned long
 */
//inline unsigned long GetPairingMask(void) 
unsigned long GetPairingMask(void) 
{
  return pairingMask;
}

/**
 * @fn unsigned char EnablePairing(unsigned char maxNodes)
 * 
 * @brief This function implements the pairing mechanism
 *
 * @param maxNodes an unsigned char
 *
 * @return an unsigned char
 */
unsigned char EnablePairing(unsigned char maxNodes)
{
  SetPairingMask(0xFFFFFFFF);
  return 1;
}

/**
 * @fn unsigned char NodeIsInMyNet(unsigned long NodeID) 
 *
 * @brief The node ID array is defined to have this node as index 0. it is also 
 *        defined that a node ID of 0 is an invalid ID. When searching to see if
 *        a NodeID is in the network list this function will return the index 
 *        number to the ID if it was found and 0 (index to this node) if it was 
 *        not found.
 *
 * @param NodeID an unsigned long
 *
 * @return an unsigned char
 */
unsigned char NodeIsInMyNet(unsigned long NodeID) 
{
  unsigned char i;
  for (i=1;i<MAX_NODES;i++) {
    if (NodeID) {                                                               // We do not accept requests for ID==0
      if (NodeID == Nodes[i].ID) return i;
    }
  }
  return 0;
}

/**
 * @fn unsigned char AddNodeToNetwork(unsigned long NodeID)
 *
 * @brief This function adds a paired node to the network. It checks if the node 
 *        is already in the network. If not, it checks if the ID has the content 
 *        within the mask, if yes, then it finds a spot for the node. If command  
 *        interface is included, it makes a call to a function to inform the GUI  
 *        that a network change has taken place.
 *
 * @param NodeID an unsigned long
 *
 * @return an unsigned char
 */
unsigned char AddNodeToNetwork(unsigned long NodeID) 
{
  unsigned char i = NodeIsInMyNet(NodeID);

  if (i != 0) {
    return i;                                                                   // We don't want to add it more than once
  } else {
    // ID cannot have content outside the mask but must have content within the mask
    if ((!(NodeID & ~pairingMask)) && (NodeID & pairingMask)) {                 // Node is qualified for membership or knows someone high up......
      for (i=1;i<((ApplicationState == HUB) ? MAX_NODES:2);i++) {               // Only the Hub is allowed more than one node
        if (Nodes[i].ID == 0) {                                                 // we found a spot for it
          Nodes[i].ID = NodeID;
          #ifdef INCLUDE_FLASH_STORAGE
            WriteMyFlashedPairedID(i, NodeID);
          #endif
          if (ApplicationState == SENSOR) {
            SetPairingMask(0);                                                  // The sensor is paired up, so close for any further pairing
          } else {                                                              // Avoid double network changed notifications
            #ifdef __COMMAND_INTERFACE
              NetworkChanged();
            #endif
          }
          return i;
        }
      }
    }
  }
  return 0;
}

/**
 * @fn unsigned char RemoveNodeFromNetwork(unsigned char NodeIndex)
 *
 * @brief This function removes the node from the network. It checks if the node
 *        index is valid, if so, it clears all the data so the the spot can be 
 *        taken by the new node. If command interface is included, it makes a call
 *        to a function to inform the GUI that a network change has taken place.
 *
 * @param NodeIndex an unsigned char
 *
 * @return an unsigned char
 */
unsigned char RemoveNodeFromNetwork(unsigned char NodeIndex) 
{
  unsigned char i;
  if ((NodeIndex) && (NodeIndex < MAX_NODES)) {
    Nodes[NodeIndex].ID = 0;                                                    // What node? I've never heard of him.....
    for (i=0;i<DATA_CHANNELS;i++) {
      Nodes[NodeIndex].Data[i] = 0;                                             // Clear also the data area so a new node taking this spot would not inherit this nodes data
    }
    Nodes[NodeIndex].CurrentCycleTime = 0;
    #if defined INCLUDE_FRAMECOUNTER_STATUS
      Nodes[NodeIndex].FrameCounter=0;
    #endif
    #ifdef INCLUDE_FLASH_STORAGE
      WriteMyFlashedPairedID(NodeIndex, 0);                                     // Romove the node from the stored nodes list in flash
    #endif
    return 1;
  }
  return 0;
}

#ifdef INCLUDE_FLASH_STORAGE
/**
 * @fn void InitFlashStorage(void)
 *
 * @brief Initialize flash storage
 */
void InitFlashStorage(void)
{
  #ifdef INCLUDE_FLASH_STORAGE
    unsigned char i;
    unsigned long tempNodeID;
    
    for (i=1;i<MAX_NODES;i++){
      tempNodeID = ReadMyFlashedPairedID(i);
      if(tempNodeID == 0xFFFFFFFF)
        WriteMyFlashedPairedID(i,Nodes[i].ID);                                  // Writes zeroes to the location of paired IDs in flash
      else{
        Nodes[i].ID = tempNodeID;
      }
    }
  #endif
}

/**
 * @fn void WriteMyFlashedID(unsigned long ID) 
 *
 * @brief This function writes the node's own ID into flash
 *
 * @param ID an unsigned long
 */
void WriteMyFlashedID(unsigned long ID) 
{
  FlashWriteBuffer((unsigned char *)&MyFlashStorage.myNodeIDs.myNodeID, (unsigned char *)&ID, sizeof(ID)); //Write my node ID to flash.
}

/**
 * @fn void WriteMyFlashedPairedID(unsigned char index, unsigned long ID) 
 *
 * @brief This function writes the ID of the paired node into flash.
 *
 * @param index an unsigned char
 * @param ID an unsigned long
 */
void WriteMyFlashedPairedID(unsigned char index, unsigned long ID) 
{
  FlashWriteBuffer((unsigned char *)&MyFlashStorage.myNodeIDs.myPairedNodeID[index-1], (unsigned char *)&ID, sizeof(ID)); // Write the ID of the paired node to Flash
}

/**
 * @fn void WriteMyFlashedRSCP(unsigned char radio, unsigned char setting, unsigned char channel, unsigned char power)
 *
 * @brief This function writes the node's indices for current radio, config, 
 *        channel and power, into flash
 *
 * @param radio an unsigned char
 * @param setting an unsigned char
 * @param channel an unsigned char
 * @param power an unsigned char
 */
void WriteMyFlashedRSCP(unsigned char radio, unsigned char setting, unsigned char channel, unsigned char power) 
{
  unsigned long rscp = 0;
  rscp = power;
  rscp = (rscp << 8) | channel;
  rscp = (rscp << 8) | setting;
  rscp = (rscp << 8) | radio;
  FlashWriteBuffer(&MyFlashStorage.myRSCP.radio, (unsigned char*)&rscp, sizeof(rscp)); // Write my owm RSCP settings to flash.                              
}

/**
 * @fn unsigned long ReadMyFlashedID(void)
 *
 * @brief This function reads the node's ID from flash.
 *
 * @return an unsigned long
 */
unsigned long ReadMyFlashedID(void) 
{
  return MyFlashStorage.myNodeIDs.myNodeID;                                     // Read my ID from Flash
}

/**
 * @fn unsigned long ReadMyFlashedPairedID(unsigned char index)
 *
 * @brief This function reads the ID of the paired node from the flash.
 *
 * @param index an unsigned char
 *
 * @return an unsigned long
 */
unsigned long ReadMyFlashedPairedID(unsigned char index) 
{
  return MyFlashStorage.myNodeIDs.myPairedNodeID[index-1];                      // Read the ID of paired node, from Flash
}

#endif  //INCLUDE_FLASH_STORAGE

/**
 * @fn unsigned long CreateRandomAddress(void)
 *
 * @brief This function creates a random address for the node ID. 
 *
 * @return an unsigned long
 */
unsigned long CreateRandomAddress(void)
{
  unsigned int  tempRandom1,tempRandom2;
  unsigned long randomNum = 0;

  while ((randomNum == 0x00000000) || (randomNum == 0xFFFFFFFF))
  {
    tempRandom1 = GenerateRandomNumber();
    tempRandom2 = GenerateRandomNumber();
    randomNum = ((long)tempRandom1 << 16) | tempRandom2;                        // Create a 32 bit random number using 2 16-bit random numbers.
  }
  return randomNum;
}
  
/**
 * @fn void InitSystem(void)
 *
 * @brief This function initializes the microcontroller peripherals needed, the 
 *        application and the protocol.
 */
void InitSystem(void)
{
  // Initialize microcontroller peripherals and application.

  // Disable all interrupts while setting up microcontroller.
  __BSP_DISABLE_INTERRUPT();

  // Halt the watchdog.
  WatchdogHold();                                                               // Stop the watchdog timer
 
  Nodes[0].ID = CreateRandomAddress();                                          // Generate a random address.  This must be done
                                                                                // before the clocks and ADC are initialized.
  // Setup board clock system.
  BoardClockSystemInit();                                                       // Intialize the system clocks
  SetOFIEBit(0);                                                                // Disable Osc Fault interrupt
  SetOFIFGBit(0);                                                               // Clear Osc Fault interrupt flag

  FCTL2 = FWKEY | FSSEL_1 | 19;
  SetMyNodeID(0);                                                               // Set node ID. The Flash block requires the clock
                                                                                // to be configured prior to calling this function.
  // Setup timers.
  TimerConfigure(__BSP_TIMER1);                                                 // Initialize Timer1
  AttachEvent(__BSP_TIMER1_CCR0_EVENT_HANDLE, Timer1CCREventHandler);
  AttachEvent(__BSP_TIMER1_CCR1_EVENT_HANDLE, Timer1CCREventHandler);
  TimerConfigure(__BSP_TIMER2);                                                 // Initialize Timer2
  AttachEvent(__BSP_TIMER2_CCR0_EVENT_HANDLE, Timer2CCREventHandler);
  TimerSetCCR(__BSP_TIMER2, __BSP_TIMER2_CCR0, __BSP_CONFIG_SWTIMER1_SOURCE_DIV);

  // Setup software timers.
  SoftwareTimerConfigure();                                                     // Initialize Software Timer
  SoftwareTimerSetInterval(__BSP_SWTIMER[0], 100);
  SoftwareTimerEnable(__BSP_SWTIMER[0]);
  AttachEvent(__BSP_SWTIMER[0].event, SWTimer0EventHandler);
//  AttachEvent(__BSP_SWTIMER[1].event, SWTimer1EventHandler);                                   

  RadioConfigure(&__BSP_RADIO1_CONNECTION);                                     // Initialize the Radio Communication module

  // Setup UART.
  UARTConfigure(__BSP_UART1);                                                   // Initialize the UART Communication module
  AttachEvent(__BSP_UART1_RX_EVENT_HANDLE, UARTRXEventHandler);                 // Attach UART RX event handler

  // Setup LEDs.
  LEDConfigure(__BSP_LEDRED1);                                                  // Initialize the Red LED
  LEDConfigure(__BSP_LEDGREEN1);                                                // Initialize the Green LED

  // Setup push button.
  PushButtonConfigure(__BSP_PUSHBUTTON1);                                       // Initialize push button.
  AttachEvent(__BSP_PUSHBUTTON1_EVENT_HANDLE, PushButton1EventHandler);
  
  AttachEvent(__BSP_PORT1_EVENT_HANDLE, PortEventHandler);
  AttachEvent(__BSP_PORT2_EVENT_HANDLE, PortEventHandler);

  // Setup ADC.
  ADCChannelConfigure(__BSP_ADC1, __BSP_ADC1_CHAN9);                            // Initialize ADC channel.
  ADCReferenceOn(__BSP_ADC1);
  ADCEnableInterrupt(__BSP_ADC1);
  ADCOn(__BSP_ADC1);
  ADCEnableConversion(__BSP_ADC1);
  AttachEvent(__BSP_ADC1_EVENT_HANDLE, ADCEventHandler);
  
  // Setup Application.
  InitApplication(Nodes[0].ID);                                                 // Initialize the Application (application state of the module, supporting protocol)

  // Start timers in "UP" mode.
  TimerEnable(__BSP_TIMER1, UP_MODE);                                           // Start the timer prior to enabling interrupts
  TimerEnable(__BSP_TIMER2, UP_MODE);                                           // Start the timer prior to enabling interrupts

  // Enable interrupts now that microcontroller is ready for normal operation.
  __BSP_ENABLE_INTERRUPT();
}

/**
 * @fn void InitApplication(unsigned long addr)
 *
 * @brief This function initializes the application. It first sets the application
 *        state, then initializes the protocol, and finally sets the pairing mask.
 *
 * @param addr an unsigned long
 */
void InitApplication(unsigned long addr) 
{
  #ifdef INCLUDE_FLASH_STORAGE
  InitFlashStorage();

  // Verify that a valid application state is stored in flash.
  if((MyFlashStorage.myAppState == HUB) || (MyFlashStorage.myAppState == SENSOR)) {
    // Get application state from flash
    ApplicationState = MyFlashStorage.myAppState;
  } else {
    // Set the default application state.
    SetApplicationState(HUB);
  }
  #endif
  InitProtocol();                                                               // Initialize Protocol 
  SetPairingMask(DEFAULT_PAIRING_MASK);                                         // Set pairing mask
}

/**
 * @fn void BlinkLED(unsigned char led, unsigned char count, unsigned char delay)
 *
 * @brief Blink the LED based on specified delay.
 * 
 * @param led an unsigned char
 * @param count an unsigned char
 * @param delay an unsigned char
 */
void BlinkLED(unsigned char led, unsigned char count, unsigned char delay)
{
  unsigned tempVar;

  for (tempVar=0;tempVar<count*2;tempVar++)
  {
    LEDToggle(led);
    Delay(delay);
  }
}

/**
 * @fn void Query_Current_Status(s_AppRadio * pRadio, PayloadFrame *payload)
 *
 * @brief This function checks if its the time to report the status. If yes, 
 *        It populates the status information in its own node structure.
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param payload a PayloadFrame structure pointer
 */
void Query_Current_Status(s_AppRadio * pRadio, PayloadFrame *payload)
{
  unsigned char i;
  i = NodeIsInMyNet(payload->NodeID);                                           // Check if the node is in my net
  if (i) {                                                                      // Load status bytes into my  node structure
    #ifdef INCLUDE_FRAMECOUNTER_STATUS
      Nodes[i].FrameCounter++;
    #endif
      Nodes[0].LastRSSI = RadioReadRegister(pCurrentFrameworkRadio(pRadio), CCXXX_STAT_RSSI);
      Nodes[i].LastRSSI = RadioLocal.RxFrameStruct.frameHeader[RSSI_RECEIVER];
    #ifdef INCLUDE_LQI_STATUS
      Nodes[i].LastLocalLQI  = RadioReadRegister(pCurrentFrameworkRadio(pRadio), CCXXX_STAT_LQI) & 0x7F;
      Nodes[i].LastRemoteLQI = RadioLocal.RxFrameStruct.frameHeader[LQI_RECEIVER] & 0x7F;
    #endif
    #ifdef INCLUDE_FREQOFF_STATUS
      Nodes[i].LastLocalFoff  = ~(RadioReadRegister(pCurrentFrameworkRadio(pRadio), CCXXX_STAT_FREQEST) - 1);
      Nodes[i].LastRemoteFoff = ~(RadioLocal.RxFrameStruct.frameHeader[FREQ_OFFSET_RECEIVER] - 1);
    #endif
    #ifdef INCLUDE_POWER_STATUS
      Nodes[i].LastLocalPower  = CurrentPower();
      Nodes[i].LastRemotePower = RadioLocal.RxFrameStruct.frameHeader[CURRENT_POWER_INDEX];
    #endif
    #ifdef INCLUDE_CHANNEL_STATUS
      Nodes[i].LastUsedChannel = CurrentChannel();
    #endif
  }
}

/**
 * @fn unsigned char SetCycleTime(s_AppRadio * pRadio, unsigned char ID, unsigned int newCycleTime)
 *
 * @brief This function checks whether the cycle time entered by the user is 
 *        greater than the minimum cycle time corresponding to current config.
 *        If so, it sets the new cycle time. If not, it sets the minimum cycle
 *        time corresponding to the current config.
 *
 * @param pRadio an s_AppRadio structure pointer
 * @param ID an unsigned char
 * @param newCycleTime an unsigned int
 *
 * @return an unsigned char
 */
unsigned char SetCycleTime(s_AppRadio * pRadio, unsigned char ID, unsigned int newCycleTime)
{
  // If the cycle time provided by the user is greater than the minimum cycle time, assign it to current cycle time
  if(newCycleTime >= pCurrentRadioConfigurationStruct(pRadio)->pRegisterSettings->configCycleTimeout.cycleTime){
    Nodes[ID].CurrentCycleTime = newCycleTime;
  }
  else{                                                                         // If not then load the minimum cycle time value
    Nodes[ID].CurrentCycleTime = pCurrentRadioConfigurationStruct(pRadio)->pRegisterSettings->configCycleTimeout.cycleTime;
  }

  // Load the cycle time into CCR
  TimerSetCount(__BSP_TIMER1, 0);
  // New value is presented in milliseconds, so multiply by 12 since timer tick is 12kHz, then divide by 2 since timer toggle output drives ADC (sample rate is half timer cycle)
  TimerSetCCR(__BSP_TIMER1, __BSP_TIMER1_CCR0, Nodes[0].CurrentCycleTime * 6);
  return 1;
}

/**
 * @fn void Alarm(unsigned int * pBuffer)
 *
 * @brief Alarm implementation
 *
 * @param pBuffer an unsigned integer pointer
 */
void Alarm(unsigned int * pBuffer)
{
  unsigned int r = 0;
  unsigned char i;
  for (i=1;i<MAX_NODES;i++) {
    if (Nodes[i].ID) {                                                          // Is it a valid network member
      r |= Nodes[i].Data[2] & 0x8000;                                           // 'OR' all red LED's (alarm)
    }
  }
  Nodes[0].Data[2] = (Nodes[0].Data[2] & (~0x8000)) | r;                        // Update our local copy for a red LED Alarm
  if (r) {                                                                      // Write to the HW the red LED (redundant)
    LEDOn(__BSP_LEDRED1);
  } else {
    LEDOff(__BSP_LEDRED1);
  }
}
