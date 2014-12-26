/**
 *  @file Application.h
 *
 *  @brief Application Layer Function Declarations
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

#ifndef __APP_APPLICATION_H
#define __APP_APPLICATION_H

#include "BSP\Board.h"
#include "Definitions.h"
#include "Protocol.h"

#define __APPLICATION_NAME "Application"                                        //!< Module Display Name
#define __APPLICATION_VERSION   1                                               //!< Module Version
#define __APPLICATION_REVISION  0                                               //!< Module Revision
#define __APPLICATION_DESCRIPTION ""                                            //!< Module Description

#define DEFAULT_SENSOR_ID    0x5A5A5A5A                                         //!< Default sensor ID, if not generated using random number generator.
#define DEFAULT_HUB_ID       0x12345678                                         //!< Default hub ID, if not generated using random number generator.
#define DEFAULT_PAIRING_MASK 0x00000000                                         //!< Startup defult pairing behavior, 0x00000000 requires manual intervention and 0xFFFFFFFF will automatically allow any
#if defined(__IAR_SYSTEMS_ICC__)
#define MAX_NODES 5
#else
#define MAX_NODES 3                                                             //!< Note that Node index 0 is always the local node, thus the max number of external nodes are MAX_NODES-1
#endif

#define NODE_ACK_TEMP_FRAME ((sizeof(Payloads)/sizeof(PayloadFrame))-1)         //!< Use the last(does not mean previous, it means the highest index!) payload for node acks
#define INCOMING_FRAME      0                                                   //!< Frame received by sensor/hub
#define SENSOR_SEND_FRAME   0                                                   //!< Frame sent by sensor

#define PAYLOAD_SIZE_VALIDATION ((sizeof(PayloadFrame) < MAX_PAYLOAD_LENGTH) ? 1 : -1) //!< Payload size less than or equal to maximum payload length specified.
//#define INCLUDE_FRAMECOUNTER_STATUS                                           // Dont delete yet. variables FrameCounter and LastFrameCounter not currently used thought.
#define INCLUDE_RSSI_STATUS                                                     //!< To include RSSI status
#define INCLUDE_FLASH_STORAGE                                                   //!< To include flash storage
#define CONFIG_TIMEOUT Nodes[0].CurrentCycleTime                                //!< Timeout for Config Change Cycle

/**
 * @brief Application state enumerations
 */
typedef enum __ApplicationState {
  SENSOR = 0,
  HUB = 1
} __ApplicationState;                                                           //!< Current state of the application.

/**
 *  @brief Flash memory location definitions.
 */
#ifdef INCLUDE_FLASH_STORAGE

/**
 * @brief For the flash storage of Node IDs : my own and of the devices I am 
 *        paired with
 */
typedef struct NodeIDs {
  volatile unsigned long myNodeID;
  unsigned long myPairedNodeID[MAX_NODES-1];
}NodeIDs;

/**
 * @brief For the flash storage of the Radio, Settings, Channel and Power we 
 *          so far have been using
 */
typedef struct RadioSettingChannelPower {
  unsigned char radio;
  unsigned char setting;
  unsigned char channel;
  unsigned char power;
} RadioSettingChannelPower;

/**
 * @brief Pointers to all the stuctures for Flash storage
 */
typedef volatile struct FlashStorage{
  NodeIDs myNodeIDs;
  RadioSettingChannelPower myRSCP;
  __ApplicationState myAppState;
}FlashStorage;

//#ifndef __IAR_SYSTEMS_ICC__
////  #pragma LOCATION(MyFlashStorage, __BSP_FLASH1_BASE_ADDRESS);	
////  #pragma NOINIT(MyFlashStorage);
//  #pragma DATA_SECTION ( MyFlashStorage , ".infoD" );
//  volatile FlashStorage MyFlashStorage;                                         //!< Flash storage of the whole structure containing NodeIDs, RSCP, AppState
//#else
//  __no_init volatile FlashStorage MyFlashStorage @ __BSP_FLASH1_BASE_ADDRESS;   //!< Flash storage of the whole structure containing NodeIDs, RSCP, AppState
//#endif  //__IAR_SYSTEMS_ICC__

  extern FlashStorage MyFlashStorage;                                  //!< Flash storage of the whole structure containing NodeIDs, RSCP, AppState

#endif  //INCLUDE_FLASH_STORAGE

/**
 * @brief Payload Flags
 */
typedef struct PayloadFlags {
  unsigned char PairingSolicitation : 1;
  unsigned char MsgCounter : 7;
} PayloadFlags;

#define DATA_CHANNELS 3                                                         //!< Data channels for Payload Frame
#define IO_DATA_CHANNELS 4                                                      //!< Total Analog/Digital data channels

/**
 * @brief Enumerations for the type of data sent through the payload.
 */
typedef enum DataTypes {
  DigitalInput  = 0x11,
  DigitalOutput = 0x12,
  AnalogInput   = 0x21,
  AnalogOutput  = 0x22
} DataTypes;

/**
 * @brief Structure for the data being sent through the payload.
 */
typedef const struct DataDefinition {
  DataTypes DataType;                                                           //!< Direction
  char *Label;                                                                  //!< Label
  char *Min;                                                                    //!< Minimum Value
  char *Max;                                                                    //!< Maximum Value
  char *Unit;                                                                   //!< Unit
  unsigned char DataChannel;                                                    //!< Data Channel Number
  unsigned int Mask;                                                            //!< Mask
//  unsigned int (*HWMapFunc)(uint8_t direction, unsigned int Value);             //!< Storage Location
} DataDefinition;

/**
 * @brief Payload Frame
 */
typedef struct PayloadFrame {                                                   // Right now this must be exactly 10, as its hardcoded in lower levels
  unsigned long NodeID;
  PayloadFlags Flags;
  unsigned int Data[DATA_CHANNELS];
  unsigned int CycleTime;
} PayloadFrame;

/**
 * @brief Node Information
 */
typedef struct NodeInfo {
  unsigned long ID;
  unsigned int CurrentCycleTime;
  unsigned int Data[IO_DATA_CHANNELS];
  unsigned char LastRSSI;
  #ifdef INCLUDE_LQI_STATUS
    unsigned char LastLocalLQI;
    unsigned char LastRemoteLQI;
  #endif
  #ifdef INCLUDE_FREQOFF_STATUS
    unsigned char LastLocalFoff;
    unsigned char LastRemoteFoff;
  #endif
  #ifdef INCLUDE_POWER_STATUS
    unsigned char LastLocalPower;
    unsigned char LastRemotePower;
  #endif
  #ifdef INCLUDE_CHANNEL_STATUS
    unsigned char LastUsedChannel;
  #endif
  #ifdef INCLUDE_FRAMECOUNTER_STATUS
    unsigned char FrameCounter;
    unsigned char LastFrameCounter;
  #endif
} NodeInfo;


/**
 * @details Perform operation based on the application state
 */
uint8_t WirelessOperation(unsigned int * pBuffer);

/**
 * @details Listen for incomming data, network qualification and data presenting
 */
uint8_t HubWirelessOperation(s_AppRadio * pRadio, unsigned int * pBuffer);

/**
 * @details Initiates a data exchange, network qualification and data presenting 
 *          of incomming data
 */
uint8_t SensorWirelessOperation(s_AppRadio * pRadio, unsigned int * pBuffer);

/**
 * @details Write the application state into Flash
 */
uint8_t SetApplicationState(__ApplicationState state);

/**
 * @details void InitFlashStorage(void)
 */
void InitFlashStorage(void);

/**
 * @details Flash pairing mechanism prototypes. Write my ID into Flash
 */
void WriteMyFlashedID(unsigned long ID);

/**
 * @details Write the ID of device paired with me, into Flash
 */
void WriteMyFlashedPairedID(unsigned char index, unsigned long ID);

/**
 * @details Write my Radio, Config, Channel and Power indices into Flash
 */
void WriteMyFlashedRSCP(unsigned char Radio, unsigned char Setting, unsigned char Channel, unsigned char Power);

/**
 * @details Read my ID from Flash
 */
unsigned long ReadMyFlashedID(void);

/**
 * @details Read the ID of the device paired with me, from Flash
 */
unsigned long ReadMyFlashedPairedID(unsigned char index);

/**
 * @details Create random address for pairing
 */
unsigned long CreateRandomAddress(void);

/**
 * @details Initialize Application
 */
void InitApplication(unsigned long addr);

/**
 * @details Initialize all the microcontroller peripherals, application, and protocol
 */
void InitSystem(void);

/**
 * @details Set pairing mask
 */
void SetPairingMask(unsigned long mask);

/**
 * @details Set my node ID
 */
unsigned char SetMyNodeID(unsigned long NodeID);

/**
 * @details Get my pairing mask
 */
unsigned long GetPairingMask(void);

/**
 * @details This fucntion implements the pairing mechanism
 */
unsigned char EnablePairing(unsigned char maxNodes);

/**
 * @details Check if the node is in my net
 */
unsigned char NodeIsInMyNet(unsigned long NodeID);

/**
 * @details Add the node to my network
 */
unsigned char AddNodeToNetwork(unsigned long NodeID);

/**
 * @details Remove the node from my network
 */
unsigned char RemoveNodeFromNetwork(unsigned char NodeID_index);

/**
 * @details Validate my network
 */
unsigned char NetworkValidation(PayloadFrame *AppFrame);

/**
 * @details Create ACK/payload frame
 */
PayloadFrame *NodeAckPayload(unsigned long NodeID);

/**
 * @details Create Sensor payload frame
 */
PayloadFrame * SensorPayload(unsigned int * pBuffer);

/**
 * @details Set the total Cycle Time
 */
unsigned char SetCycleTime(s_AppRadio * pRadio, unsigned char ID, unsigned int newCycleTime);

/**
 * @details Provide Status Update when necessary
 */
void Query_Current_Status(s_AppRadio * pRadio, PayloadFrame *payload);

/**
 * @details Blink the LED based on specified delay.
 */
void BlinkLED(unsigned char led, unsigned char count, unsigned char delay);

/**
 * @details Alarm Implementation
 */
void Alarm(unsigned int * pBuffer);

#include "CommandInterface.h"
extern volatile __ApplicationState ApplicationState;
extern NodeInfo Nodes[];

#endif  // __APP_APPLICATION_H
