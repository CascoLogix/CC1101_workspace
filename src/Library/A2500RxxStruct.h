/**
 *  @file A2500RxxStruct.h
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

#ifndef __LIB_A2500SETTINGSSTRUCT_H
#define __LIB_A2500SETTINGSSTRUCT_H

#include "Drivers/Radio/CCXXX/Model/CC2500.h"



/**
 * @brief Cycle Timeout Flags
 */
typedef const struct A2500R24CycleTimeout{
  unsigned int cycleTime;                                                       //!< Cycle time for config timeout
  unsigned int syncTimeout;                                                     //!< Sync word timeout
  unsigned int EOPTimeout;                                                      //!< End of Packet timeout
}A2500R24CycleTimeout;

/**
 * @brief A2500R24 Radio Power Settings
 */
typedef const struct A2500R24PowerList
{
  CC2500RFPowerSettings radioPower;                                             //!< Radio power definitions
  char *powerDescription;
} A2500R24PowerList;

/**
 * @brief A2500R24 Radio Channels
 */
typedef const struct A2500R24ChannelList
{
  CC2500RFChannel radioChannel;                                                 //!< Radio channel definitions
  char *channelDescription;
} A2500R24ChannelList;

/**
 * @brief A2500R24 RF Channels
 */
typedef const struct A2500R24Channel
{
  unsigned char radioChannelIndex;                                              //!< Radio channel index
  unsigned char radioPowerIndex;                                                //!< Radio power index
} A2500R24Channel;

/**
 * @brief A2500R24 RF Register Settings
 */
typedef const struct A2500R24RegisterSettings
{
  CC2500RFSettings registerSettings;                                            //!< Radio register settings
  A2500R24CycleTimeout configCycleTimeout;
  char *baseSettingsDescription;
} A2500R24RegisterSettings;

/**
 * @brief A2500R24 Radio Configuration Settings
 */
typedef const struct A2500R24Configuration
{
  A2500R24RegisterSettings * pRegisterSettings;                                 //!< Radio register settings
  A2500R24Channel * pConfigurationChannel;                                      //!< Radio channels assigned to configuration
  unsigned char configurationChannelCount;                                      //!< Number of channels assigned to configuration
  char *baseConfigurationDescription;
} A2500R24Configuration;

/**
 * @brief Array Sizes
 *
 * @brief Represents the array sizes of the radio settings.
 */
typedef const struct A2500R24ArraySizes 
{
  unsigned char radioConfigurationCount;                                        //!< Number of configurations assigned to radio
  unsigned char radioChannelListCount;                                          //!< Number of channel settings assigned to radio
  unsigned char radioPowerListCount;                                            //!< Number of power settings assigned to radio
  unsigned char radioRegisterSettingsSize;                                      //!< Size of configuration settings structure
  unsigned char radioChannelSize;                                               //!< Size of channel array
  unsigned char radioPowerSize;                                                 //!< Size of power array
} A2500R24ArraySizes;


#endif  // __LIB_A2500SETTINGSSTRUCT_H
