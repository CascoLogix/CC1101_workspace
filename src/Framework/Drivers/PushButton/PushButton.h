/**
 *  @file   PushButton.h
 */
#ifndef __DRIVER_PUSHBUTTON_H
#define __DRIVER_PUSHBUTTON_H

#include "../../BSP/BoardDrivers.h"
#include "../Timer/SoftwareTimerStruct.h"

#define PUSHBUTTON_RELEASE                  0
#define PUSHBUTTON_PRESS                    1
#define PUSHBUTTON_CLICK                    0
#define PUSHBUTTON_HOLD                     1

#define PushButtonConfigure(buttonId)       __BSP_PUSHBUTTON_CONFIGURE(buttonId)  

/**
 *  @fn       PushButtonEventHandler
 *
 *  @brief    Controls push and release triggers.
 *
 *  @note     Must be called from within the corresponding button port event 
 *            handler.
 *
 *  @return   The state of the pushbutton. The possible options are listed below:
 *                1   ->  Press down
 *                0   ->  Release
 */
void PushButtonEventHandler(unsigned char pushButtonId, unsigned char minPressTime);

/**
 *  @fn     PushButtonTimerEventHandler
 */
unsigned int PushButtonTimerEventHandler(PushButtonTimer * swTimer, unsigned int timeout);

/**
 *  @fn     PushButtonTimerEnable
 */
void PushButtonTimerEnable(PushButtonTimer * swTimer);

/**
 *  @fn     PushButtonTimerDisable
 */
void PushButtonTimerDisable(PushButtonTimer * swTimer);

/**
 *  @fn     PushButtonSetTimerCount
 */
void PushButtonSetTimerCount(PushButtonTimer * swTimer, unsigned int count);

/**
 *  @fn     PushButtonGetClickCount 
 */
unsigned char PushButtonGetClickCount(PushButtonTimer * swTimer);

/**
 *  @fn     PushButtonSetClickCount
 */
void PushButtonSetClickCount(PushButtonTimer * swTimer, unsigned char clickCount);

#endif  // __DRIVER_PUSHBUTTON_H
