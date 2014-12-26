/**
 *  @file A110LRxxStruct.h
 *
 *  @brief A110L Radio Settings Structure Declarations
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

#ifndef __LIB_A110LSETTINGSSTRUCT_H
#define __LIB_A110LSETTINGSSTRUCT_H

#include "Drivers/Radio/CCXXX/Model/CC110L.h"


/**
 *  Radio Settings
 *
 *  @brief Represents all registers for a specific radio.
 */
typedef const struct A110LR09RadioSettings
{
  union
  {
    CC110LRFSettings cc110L;      // CC110L configuration registers definition
  } settings;
} A110LR09RadioSettings;

/**
 *  RF Channel
 *
 *  @brief Represents the registers used for channels.
 */
typedef const struct A110LR09RadioChannel
{
  union
  {
    CC110LRFChannel cc110L;       // CC110L channel definition
  } channel;
} A110LR09RadioChannel;

/**
 *  Radio Power
 *
 *  @brief Represents the registers for the PA table.
 */
typedef const struct A110LR09RadioPower
{
  union
  {
    CC110LRFPowerSettings cc110L;   // CC110L power table definition
  } power;
} A110LR09RadioPower;

/**
 * @brief Cycle Timeout Flags
 */
typedef const struct A110LR09CycleTimeout{
  unsigned int cycleTime;                                                       //!< Cycle time for config timeout
  unsigned int syncTimeout;                                                     //!< Sync word timeout
  unsigned int EOPTimeout;                                                      //!< End of Packet timeout
}A110LR09CycleTimeout;

/**
 * @brief A110LR09 Radio Power Settings
 */
typedef const struct A110LR09PowerList
{
  A110LR09RadioPower radioPower;                                             //!< Radio power definitions
  char *powerDescription;
} A110LR09PowerList;

/**
 * @brief A110LR09 Radio Channels
 */
typedef const struct A110LR09ChannelList
{
  A110LR09RadioChannel radioChannel;                                                 //!< Radio channel definitions
  char *channelDescription;
} A110LR09ChannelList;

/**
 * @brief A110LR09 RF Channels
 */
typedef const struct A110LR09Channel
{
  unsigned char radioChannelIndex;                                              //!< Radio channel index
  unsigned char radioPowerIndex;                                                //!< Radio power index
} A110LR09Channel;

/**
 * @brief A110LR09 RF Register Settings
 */
typedef const struct A110LR09RegisterSettings
{
  A110LR09RadioSettings registerSettings;                                            //!< Radio register settings
  A110LR09CycleTimeout configCycleTimeout;
  char *baseSettingsDescription;
} A110LR09RegisterSettings;

/**
 * @brief A110LR09 Radio Configuration Settings
 */
typedef const struct A110LR09Configuration
{
  A110LR09RegisterSettings * pRegisterSettings;                                 //!< Radio register settings
  A110LR09Channel * pConfigurationChannel;                                      //!< Radio channels assigned to configuration
  unsigned char configurationChannelCount;                                      //!< Number of channels assigned to configuration
  char *baseConfigurationDescription;
} A110LR09Configuration;

/**
 * @brief Array Sizes
 *
 * @brief Represents the array sizes of the radio settings.
 */
typedef const struct A110LR09ArraySizes 
{
  unsigned char radioConfigurationCount;                                        //!< Number of configurations assigned to radio
  unsigned char radioChannelListCount;                                          //!< Number of channel settings assigned to radio
  unsigned char radioPowerListCount;                                            //!< Number of power settings assigned to radio
  unsigned char radioRegisterSettingsSize;                                      //!< Size of configuration settings structure
  unsigned char radioChannelSize;                                               //!< Size of channel array
  unsigned char radioPowerSize;                                                 //!< Size of power array
} A110LR09ArraySizes;


#endif  // __LIB_A110LSETTINGSSTRUCT_H
