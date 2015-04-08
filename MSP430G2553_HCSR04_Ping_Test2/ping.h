/******************************************************************************/
//	ping.h
//  
//	 Created on: Apr 7, 2015
//	     Author: Clint Stevenson
//
/******************************************************************************/


#ifndef PING_H_
#define PING_H_


/******************************************************************************/
//	Includes
/******************************************************************************/
//Put conditional includes here
#include <msp430.h>
//#include <timer_interface.h>
#include <stdint.h>
/******************************************************************************/
//	End Includes


/******************************************************************************/
//	Defines
/******************************************************************************/
//Put defines here
#define PING_PORT_OUT 				(P2OUT)
#define PING_PORT_DIR 				(P2DIR)
#define PING_ECHO_SEL				(P2SEL)
#define PING_TRIG_PIN 				(BIT1)
#define PING_ECHO_PIN 				(BIT0)
/******************************************************************************/
//	End Defines


/******************************************************************************/
//	Public Constant Declarations (extern)
/******************************************************************************/
//Put public variable declarations here
/******************************************************************************/
//	End Public Constant Declarations


/******************************************************************************/
//	Public Variable Declarations (extern)
/******************************************************************************/
//Put public variable declarations here
/******************************************************************************/
//	End Public Variable Declarations


/******************************************************************************/
//	Public Typedef Declarations (extern)
/******************************************************************************/
//Put public typedef declarations here
/******************************************************************************/
//	End Public Typedef Declarations


/******************************************************************************/
//	Public Function Prototypes
/******************************************************************************/
//Put public function prototypes here
void ping_init (void);
uint32_t ping_triggerPing (void);
uint32_t ping_markEchoStart (void);
uint32_t ping_markEchoStop (void);
uint32_t ping_getResult (void);
void ping_Overflow (void);
/******************************************************************************/
//	End Public Function Prototypes


#endif /* PING_H_ */
