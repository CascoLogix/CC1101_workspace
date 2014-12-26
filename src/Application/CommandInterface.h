/**
 *  @file CommandInterface.h
 *
 *  @brief Command-Interface Function Declarations
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

#ifndef __CmdIF_DEFINED
#define __CmdIF_DEFINED

#include "Application.h"

#define __COMMAND_INTERFACE
#define __CmdIF_NAME "CmdIF"                                                    //!< Module Display Name
#define __CmdIF_VERSION   1                                                     //!< Module Version
#define __CmdIF_REVISION  1                                                     //!< Module Revision
//#define __CmdIF_DESCRIPTION "Command Interface"                                 //!< Module Description
#define __CmdIF_DESCRIPTION ""                                                  //!< Module Description


/*!  CmdIF_TestMode
    \brief If defined then module test code will be included
 If CmdIF_TestMode is defined then a set of functions and data will be included
 in the compilation. These functions and the data runs a specific pre-determined
 test, with a defined predictable output, thus allowing to compare current 
 response to previous known good ones. CmdIFCommand_ModuleTest() is the main 
 module test function and will need to be called from somewhere to commense 
 the test.
*/
//#define __CmdIF_TESTMODE

/*! \def XML_INPUT_SUPPORT
    \brief If defined then the command input will accept XML input
 Note however that the parameters still has to be in the expected order and
 be hexadecimal. The XML descriptions will simply be stripped away
*/
#define XML_INPUT_SUPPORT

#ifdef __CmdIF_TESTMODE
  #define MaxRawCommandLength (20)                                              //!< Need at least 20 to run the test
#else
  #define MaxRawCommandLength (16)                                              //!< This is enough for normal operation
#endif
#if MaxRawCommandLength < 7
  #error "Cannot implement mandatory commands with (MaxRawCommandLength<7) in CmdIF"
#endif

//#define __DEBUG_COMMANDS
#ifdef __DEBUG_COMMANDS
  extern RadioStruct RadioLocal;
  extern ConfigStruct ConfigSettings[];
#endif
  
//#define __INCLUDE_ELABORATE_HELP

extern NodeInfo Nodes[MAX_NODES];

/**
 * @brief Command Definition
 */
typedef const struct CommandDefinition {
  char *Command;
  unsigned char (*CmdFunction)(void);
  #ifdef __INCLUDE_ELABORATE_HELP
    char *HelpTxt;
  #endif
} CommandDefinition;

/**
 * @brief Enumerations for the data types of the response numbers.
 */
typedef enum ResponseNumberFormats {
  HexadecimalByte      = 0x41,
  HexadecimalWord      = 0x42,
  Hexadecimal24bit     = 0x43,
  HexadecimalLong      = 0x44,
  BinaryByte           = 0x21,
  BinaryWord           = 0x21,
  Binary24bit          = 0x21,
  BinaryLong           = 0x21,
  SignedDecimalByte    = 0x91, 
  SignedDecimalWord    = 0x92, 
  SignedDecimal24bit   = 0x93, 
  SignedDecimalLong    = 0x94, 
  UnsignedDecimalByte  = 0x11, 
  UnsignedDecimalWord  = 0x12, 
  UnsignedDecimal24bit = 0x13, 
  UnsignedDecimalLong  = 0x14
} ResponseNumberFormats;

///**
// * @brief Enumerations for the type of data sent through the payload.
// */
//typedef enum DataTypes {
//  DigitalInput  = 0x11,
//  DigitalOutput = 0x12,
//  AnalogInput   = 0x21,
//  AnalogOutput  = 0x22,
//} DataTypes;

#define DATA_OUTPUT_MASK 0x02
#define DATA_INPUT_MASK  0x01
#define DATA_DIGITAL_MASK 0x10

///**
// * @brief Structure for the data being sent through the payload.
// */
//typedef const struct DataDefinition {
//  DataTypes DataType;                                                           //!< Direction
//  char *Label;                                                                  //!< Label
//  char *Min;                                                                    //!< Minimum Value
//  char *Max;                                                                    //!< Maximum Value
//  char *Unit;                                                                   //!< Unit
//  unsigned char DataChannel;                                                    //!< Data Channel Number
//  unsigned int Mask;                                                            //!< Mask
//  unsigned int (*HWMapFunc)(uint8_t direction, unsigned int Value);             //!< Storage Location
//} DataDefinition;

//! \brief Private functions
/**
 * @details Private function called from ProcessRawCommand (typically called 
 *          from the application) to handle built in commands like read/write
 */
char BuiltInCmdProcessing(void);                                                 
                                                                               
/**
 * @details Write out a hex nibble
 */
char HexNibble(char num); 

/**
 * @details Write out a number in specified format.
 */
void ResponseResult(unsigned char res);

// Local function prototyping:
/**
 * @details Provide version, revision and description for each major module.
 */
unsigned char AppInformation(void);

/**
 * @details List all the commands available through the Command Interface.
 */
unsigned char CommandListing(void);

/**
 * @details Control the spontaneous outputs and the output format.
 */
unsigned char ResponseCtrl(void);

// Prototype functions 
/**
 * @details Collect the command from UART
 */
signed char CmdIFCollect(signed char InData);     

/**
 * @details Output the information string to the response stream
 */
unsigned char DebugNote(char *Desc);

/**
 * @details Output the Response String
 */
void CmdIFResponse(char* string, unsigned char length);

/**
 * @details Error in command.
 */
void CommandError(char *desc);

/**
 * @details Header for the Response file
 */
void ResponseFileHeader(void);

/**
 * @details Meant to superseede HexByte, HexWord, HexLong, SignedChar, UnsignedChar
 */
void ResponseNumber(signed long Universal, unsigned char Format, char *Destination); 

#ifdef __CmdIF_TESTMODE
/**
 * @details Test Module for Command Interface
 */
unsigned char CmdIFCommand_ModuleTest(void); 

/**
 * @details Test only functions that uses the above functions to allow verification of their function
 */
void TestCmdResponse(void);                      

/**
 * @details Emulate an application main to both service the UART commands and to stream "RSSI"
 */
void SampleApp(void);                             
#endif

/**
 * @details Process Command
 */
unsigned char CmdIFProcess(unsigned char * ID, unsigned int * pBuffer) ;

/**
 * @details Provide delayed result
 */
void ProvideDelayedResult(unsigned char result);

/**
 * @details Get String length
 */
unsigned char StrLen(char *Str);

/**
 * @details Compare strings
 */
unsigned char StrCmp(char *Src, char *Dst);

/**
 * @details Get Parameter Byte
 */
unsigned char GetParmByte(char *ParmLabel, unsigned char *ReturnDataPtr);

/**
 * @details Get Parameter Word
 */
unsigned char GetParmWord(char *ParmLabel, unsigned int *ReturnDataPtr);

/**
 * @details Get Parameter Long
 */
unsigned char GetParmLong(char *ParmLabel, unsigned long *ReturnDataPtr);

/**
 * @details List all commands available through the command interface
 */
unsigned char CommandListing(void);

/**
 * @details Read from memory
 */
unsigned char MemoryRead(void);

/**
 * @details Write to memory
 */
unsigned char MemoryWrite(void);

/**
 * @details Get Parameter Value
 */
unsigned char GetParmValue(char *ParmLabel, unsigned long *ReturnDataPtr, unsigned char ParmSize);

/**
 * @details Begin the tag
 */
void TagBegin(char *label, unsigned char attributes);

/**
 * @details End the tag
 */
void TagEnd(char * label, unsigned char elementLess);

/**
 * @details Write out element attribute of 8 bit unsigned integer
 */
void ElemAttrUint8(char *label, unsigned char data);

/**
 * @details Write out element attribute of 16 bit unsigned integer
 */
void ElemAttrUint16(char *label, unsigned int data);

/**
 * @details Write out element attribute of 16 bit signed integer
 */
void ElemAttrSint16(char *label, signed int data);

/**
 * @details Write out element attribute of 32 bit unsigned integer
 */
void ElemAttrUint32(char *label, unsigned long data);

/**
 * @details Write out element attribute text
 */
void ElemAttrText(char *label, char *text);

/**
 * @details Function to write out the element attributes of all data types
 */
void ElemAttrUniv(char *label, char *text, signed long data, unsigned char format);

/**
 * @details End the attribute
 */
void AttributeEnd(void);

#ifdef __COMMAND_INTERFACE
/**
 * @details  Get all Node IDs
 */
unsigned char CmdIF_GetNodeIDs(void);

/**
 * @details Set given Node ID
 */
unsigned char CmdIF_SetThisNodeID(void);

/**
 * @details Set pairing mask
 */
unsigned char CmdIF_SetPairingMask();

/**
 * @details Remove node from the network
 */
unsigned char CmdIF_RemoveNode(void);

/**
 * @details Get Application States
 */
unsigned char CmdIF_GetAppStates(void);

/**
 * @details Set Application States
 */
unsigned char CmdIF_SetAppState(void);

/**
 * @details Inform GUI that application state has changed
 */
void ApplicationChanged(void);

/**
 * @details Set Cycle Update Rate(total cycle time)
 */
unsigned char CmdIF_SetCycleUpdateRate(void);

/**
 * @details Write out what data is received from Application state.
 */
unsigned char CmdIF_DataDefinitions(void);

/**
 @details Return the index of the node ID, whose data is to be set as per
 *        user's input.
 */
unsigned char CmdIF_SetDataValue(void);

/**
 * @details Store the data value corresponding to the node ID index 
 *          provided by user, into the buffer passed to it.
 */
unsigned char SetDataValue(unsigned char IDindex, unsigned int * pBuffer);

/**
 * @details Report the data on UART
 */
void ReportData(unsigned char IDindex);

/**
 * @details Maps data from a network node storage location (Nodes[].Data[])
 *          into all applicable HW "actuators"
 */
void MapControlsToHW(unsigned char IDindex, unsigned int * pBuffer);

/**
 * @details Maps all applicable HW sensors into the network node storage 
 *          location (Nodes[].Data[]) specified
 */
void MapSensorsFromHW(unsigned char IDindex, unsigned int * pBuffer);
#endif

/**
 * @details Emit current Radio, Config, Channel and Power settings when they are changed
 */
void PhysicalChanged(void);

/**
 * @details Emit the node slots when they are changed
 */
void NetworkChanged(void);

// For Debug
/**
 * @details Set the Channel Index
 */
unsigned char SetCurrentChannel(void);

/**
 * @details Set the Power Index
 */
unsigned char SetCurrentPower(void);

/**
 * @details Set the Configuration Index
 */
unsigned char SetCurrentConfig(void);

/**
 * @details Set the Radio Index
 */
unsigned char SetCurrentRadio(void);

/**
 * @details Reset current Radio
 */
unsigned char ResetCurrentRadio(void);

/**
 * @details Used to report RSSI values. Can be called with IDindex=0, which will 
 *          output the RSSI only for the local node and with IDindex>0, which 
 *          will output the RSSI for both the local and the specified remote 
 *          (must be a valid remote).
 */
void ReportStatus(unsigned char IDindex);

// Local Prototyping for hardware mapping functions
/**
 * @details Return current temperature data
 */
unsigned int HWMap_ChipTemp(uint8_t direction, unsigned int Value);

/**
 * @details Map the Red LED to hardware based on the input.
 */
unsigned int HWMap_RedLED(uint8_t direction, unsigned int Value);

/**
 * @details Map the Green LED to hardware based on the input.
 */
unsigned int HWMap_GreenLED(uint8_t direction, unsigned int Value);

/**
 * @details Map the Red LED to hardware based on the button switch input
 */
unsigned int HWMap_RedLEDandButton(uint8_t direction, unsigned int Value);

/**
 * @details Map the PWM to hardware based on the input.
 */
unsigned int HWMap_PWM(uint8_t direction, unsigned int Value);


#endif
