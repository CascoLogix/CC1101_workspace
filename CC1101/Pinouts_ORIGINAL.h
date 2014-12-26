/*
 * Pinouts.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Lucas
 */

#ifndef PINOUTS_H_
#define PINOUTS_H_

#include <msp430.h>
//----------------------------------------------------------------------------
// Select which port will be used for interface to CCxxxx
//----------------------------------------------------------------------------
//#define RF_SER_INTF       SER_INTF_BITBANG  // Interface to CCxxxx
//#define RF_SER_INTF		SER_INTF_USCIA0
#define RF_SER_INTF       SER_INTF_USCIB0  // Interface to CCxxxx



#if defined (__MSP430G2553__)

#define __PxSEL2__					  //Some MSP430s do not incorporate PxSEL2s

// SPI port definitions               // Adjust the values for the chosen
#define SPI_USCIA0_PxSEL  P1SEL       // interfaces, according to the pin
#define SPI_USCIA0_PxSEL2	P1SEL2
#define SPI_USCIA0_PxDIR  P1DIR       // assignments indicated in the
#define SPI_USCIA0_PxIN   P1IN        // chosen MSP430 device datasheet.
#define SPI_USCIA0_SIMO   BIT2
#define SPI_USCIA0_SOMI   BIT1
#define SPI_USCIA0_UCLK   BIT4

// SPI port definitions               // Adjust the values for the chosen
#define SPI_USCIB0_PxSEL  P1SEL       // interfaces, according to the pin
#define SPI_USCIB0_PxSEL2	P1SEL2
#define SPI_USCIB0_PxDIR  P1DIR       // assignments indicated in the
#define SPI_USCIB0_PxIN   P1IN        // chosen MSP430 device datasheet.
#define SPI_USCIB0_SIMO   BIT7
#define SPI_USCIB0_SOMI   BIT6
#define SPI_USCIB0_UCLK   BIT5


//LED port definitions
#define LED_PxOUT         P1OUT
#define LED_PxDIR         P1DIR
#define LED1              BIT0
#define LED2              BIT6

//Switch port definitions
#define SW_PxIN           P1IN
#define SW_PxIE           P1IE
#define SW_PxIES          P1IES
#define SW_PxIFG          P1IFG
#define SW_PxREN          P1REN
#define SW_PxOUT          P1OUT
//#define SW1			  RESET		//We don't want to use the reset button as a trigger...wouldn't be very useful
#define SW2               BIT3

//GDO0 Definitions
#define GDO0_PxOUT        P1OUT
#define GDO0_PxIN         P1IN
#define GDO0_PxDIR        P1DIR
#define GDO0_PxIE         P1IE
#define GDO0_PxIES        P1IES
#define GDO0_PxIFG        P1IFG
#define GDO0_PxREN        P1REN
#define GDO0_PIN          BIT4

//GDO0 Definitions
#define GDO1_PxOUT        P1OUT
#define GDO1_PxIN         P1IN
#define GDO1_PxDIR        P1DIR
#define GDO1_PIN          BIT7

//GDO1 Definitions
#define GDO2_PxOUT        P2OUT
#define GDO2_PxIN         P2IN
#define GDO2_PxDIR        P2DIR
#define GDO2_PIN          BIT0

//GDO2 Definitions
#define CSn_PxOUT         P2OUT
#define CSn_PxDIR         P2DIR
#define CSn_PIN           BIT1

#endif /* __MSP430G2553__ */


//******************************************************************************
//  These constants are used to identify the chosen SPI and UART interfaces.
//******************************************************************************
#define SER_INTF_NULL    0
#define SER_INTF_USART0  1
#define SER_INTF_USART1  2
#define SER_INTF_USCIA0  3
#define SER_INTF_USCIA1  4
#define SER_INTF_USCIA2  5
#define SER_INTF_USCIA3  6
#define SER_INTF_USCIB0  7
#define SER_INTF_USCIB1  8
#define SER_INTF_USCIB2  9
#define SER_INTF_USCIB3  10
#define SER_INTF_USI     11
#define SER_INTF_BITBANG 12


#endif /* PINOUTS_H_ */
