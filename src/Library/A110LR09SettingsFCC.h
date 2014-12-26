/**
 *  @file A110LR09SettingsFCC.h
 *
 *  @brief Configuration, Channel and Power settings for A110LR09 FCC
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

#ifndef __LIB_A110LR09SETTINGSFCC_H
#define __LIB_A110LR09SETTINGSFCC_H

#include "A110LRxxStruct.h"


#define A110LR09ChannelDefine(freq2, freq1,freq0,description) {freq2, freq1, freq0}, description
#define A110LR09PowerDefine(powerSetting, description) {powerSetting}, description
#define A110LR09PowerDefineAllSame(powerSetting, description) {powerSetting, powerSetting}, description

extern A110LR09RegisterSettings A110LR09RegisterSettingsFCC[];
extern A110LR09PowerList A110LR09PowerListFCC[];
extern A110LR09ChannelList A110LR09ChannelListFCC[];
extern A110LR09Channel A110LR09ConfigurationChannelsFCC[];
extern A110LR09Configuration A110LR09ConfigurationFCC[];
extern A110LR09ArraySizes A110LR09ArraySizesFCC;

#endif  // __LIB_A110LR09SETTINGSFCC_H
