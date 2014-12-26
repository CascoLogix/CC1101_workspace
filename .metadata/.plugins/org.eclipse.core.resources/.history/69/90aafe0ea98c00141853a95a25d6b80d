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

/*
 * - P1.0: LED1 (red)
 * - P1.1: UC0ARXD (input)
 * - P1.2: UCA0TXD (output)
 * - P1.3: SW2 (pushbutton)
 * - P1.4: Use this as pulse input?  Use as gated power to ultrasonic sensor?
 * - P1.5: UCB0CLK (SPI/CLK)
 * - P1.6: UCB0SOMI (SPI/GDO1/MISO)
 * - P1.7: UCB0SIMO (SPI/MOSI)
 * - P2.0: TA1.0 (buzzer)
 * - P2.1: Use this as pulse input?  Use as gated power to ultrasonic sensor?
 * - P2.2: (SPI/CSn)
 * - P2.3: (GDO0)
 * - P2.4: (GDO2)
 * - P2.5: Use this as pulse input?  Use as gated power to ultrasonic sensor?
 * - P2.6: 32.768kHz Crystal
 * - P2.7: 32.768kHz Crystal
*/

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
#define GDO0_PxOUT        P2OUT			// Original setting was Port 1
#define GDO0_PxIN         P2IN			// Original setting was Port 1
#define GDO0_PxDIR        P2DIR			// Original setting was Port 1
#define GDO0_PxIE         P2IE			// Original setting was Port 1
#define GDO0_PxIES        P2IES			// Original setting was Port 1
#define GDO0_PxIFG        P2IFG			// Original setting was Port 1
#define GDO0_PxREN        P2REN			// Original setting was Port 1
#define GDO0_PIN          BIT3			// Original setting was BIT4

//GDO1 Definitions
/*
#define GDO1_PxOUT        P1OUT
#define GDO1_PxIN         P1IN
#define GDO1_PxDIR        P1DIR
#define GDO1_PIN          BIT6
*/

//GDO2 Definitions
#define GDO2_PxOUT        P2OUT
#define GDO2_PxIN         P2IN
#define GDO2_PxDIR        P2DIR
#define GDO2_PIN          BIT4

//CSn Definitions
#define CSn_PxOUT         P2OUT
#define CSn_PxDIR         P2DIR
#define CSn_PIN           BIT2			// Original setting was BIT1

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
