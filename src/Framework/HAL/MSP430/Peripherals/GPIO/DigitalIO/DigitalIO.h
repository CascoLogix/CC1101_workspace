/**
 *  \file   DigitalIO.h
 */
#ifndef __MCU_MSP430_DIGITALIO_H
#define __MCU_MSP430_DIGITALIO_H

#include "../../../Config.h"

#if defined(__MCU_MSP430_DIGITALIO)

#if defined(__MCU_MSP430_DIGITALIO_PORT1)

#define PORT1_NO_EVENT    0
#define PORT1_0_EVENT     BIT0
#define PORT1_1_EVENT     BIT1
#define PORT1_2_EVENT     BIT2
#define PORT1_3_EVENT     BIT3
#define PORT1_4_EVENT     BIT4
#define PORT1_5_EVENT     BIT5
#define PORT1_6_EVENT     BIT6
#define PORT1_7_EVENT     BIT7

/**
 *  \fn   DigitalIOPort1InterruptServiceRoutine
 */
__interrupt void DigitalIOPort1InterruptServiceRoutine();
extern unsigned char (*DigitalIOPort1Event)(const void *);

#endif  // DIGITAL_IO_PORT1 SUB MODULE

#if defined(__MCU_MSP430_DIGITALIO_PORT2)

#define PORT2_NO_EVENT    0
#define PORT2_0_EVENT     BIT0
#define PORT2_1_EVENT     BIT1
#define PORT2_2_EVENT     BIT2
#define PORT2_3_EVENT     BIT3
#define PORT2_4_EVENT     BIT4
#define PORT2_5_EVENT     BIT5
#define PORT2_6_EVENT     BIT6
#define PORT2_7_EVENT     BIT7

/**
 *  \fn   DigitalIOPort2InterruptServiceRoutine
 */
__interrupt void DigitalIOPort2InterruptServiceRoutine();
extern unsigned char (*DigitalIOPort2Event)(const void *);

#endif  // DIGITAL_IO_PORT2 SUB MODULE

/**
 *  \fn   SetGPIOOutputPort
 */
void SetDigitalIOOutputPort(enum PORT port, unsigned char pin);

/**
 *  \fn   ClearGPIOOutputPort
 */
void ClearDigitalIOOutputPort(unsigned char port, unsigned char pin);


#endif  // DIGITAL_IO MODULE

#endif  // __MCU_MSP430_DIGITALIO_H
