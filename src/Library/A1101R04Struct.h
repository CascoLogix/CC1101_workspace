/**
 *  @file A1101RxxStruct.h
 *
 *  @brief A1101 Radio Settings Structure Declarations
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

#ifndef __LIB_A1101SETTINGSSTRUCT_H
#define __LIB_A1101SETTINGSSTRUCT_H

#include "Drivers/Radio/CCXXX/Model/CC1101.h"


/**
 *  Radio Settings
 *
 *  @brief Represents all registers for a specific radio.
 */
typedef const struct A1101R04RadioSettings
{
  union
  {
    CC1101RFSettings cc1101;      // CC1101 configuration registers definition
  } settings;
} A1101R04RadioSettings;

/**
 *  RF Channel
 *
 *  @brief Represents the registers used for channels.
 */
typedef const struct A1101R04RadioChannel
{
  union
  {
    CC1101RFChannel cc1101;       // CC110L channel definition
  } channel;
} A1101R04RadioChannel;

/**
 *  Radio Power
 *
 *  @brief Represents the registers for the PA table.
 */
typedef const struct A1101R04RadioPower
{
  union
  {
    CC1101RFPowerSettings cc1101;   // CC1101 power table definition
  } power;
} A1101R04RadioPower;

/**
 * @brief Cycle Timeout Flags
 */
typedef const struct A1101R04CycleTimeout{
  unsigned int cycleTime;                                                       //!< Cycle time for config timeout
  unsigned int syncTimeout;                                                     //!< Sync word timeout
  unsigned int EOPTimeout;                                                      //!< End of Packet timeout
}A1101R04CycleTimeout;

/**
 * @brief A1101R04 Radio Power Settings
 */
typedef const struct A1101R04PowerList
{
  A1101R04RadioPower radioPower;                                                //!< Radio power definitions
  char *powerDescription;
} A1101R04PowerList;

/**
 * @brief A1101R04 Radio Channels
 */
typedef const struct A1101R04ChannelList
{
  A1101R04RadioChannel radioChannel;                                            //!< Radio channel definitions
  char *channelDescription;
} A1101R04ChannelList;

/**
 * @brief A1101R04 RF Channels
 */
typedef const struct A1101R04Channel
{
  unsigned char radioChannelIndex;                                              //!< Radio channel index
  unsigned char radioPowerIndex;                                                //!< Radio power index
} A1101R04Channel;

/**
 * @brief A1101R04 RF Register Settings
 */
typedef const struct A1101R04RegisterSettings
{
  A1101R04RadioSettings registerSettings;                                       //!< Radio register settings
  A1101R04CycleTimeout configCycleTimeout;
  char *baseSettingsDescription;
} A1101R04RegisterSettings;

/**
 * @brief A1101R04 Radio Configuration Settings
 */
typedef const struct A1101R04Configuration
{
  A1101R04RegisterSettings * pRegisterSettings;                                 //!< Radio register settings
  A1101R04Channel * pConfigurationChannel;                                      //!< Radio channels assigned to configuration
  unsigned char configurationChannelCount;                                      //!< Number of channels assigned to configuration
  char *baseConfigurationDescription;
} A1101R04Configuration;

/**
 * @brief Array Sizes
 *
 * @brief Represents the array sizes of the radio settings.
 */
typedef const struct A1101R04ArraySizes
{
  unsigned char radioConfigurationCount;                                        //!< Number of configurations assigned to radio
  unsigned char radioChannelListCount;                                          //!< Number of channel settings assigned to radio
  unsigned char radioPowerListCount;                                            //!< Number of power settings assigned to radio
  unsigned char radioRegisterSettingsSize;                                      //!< Size of configuration settings structure
  unsigned char radioChannelSize;                                               //!< Size of channel array
  unsigned char radioPowerSize;                                                 //!< Size of power array
} A1101R04ArraySizes;


#endif  // __LIB_A1101SETTINGSSTRUCT_H
