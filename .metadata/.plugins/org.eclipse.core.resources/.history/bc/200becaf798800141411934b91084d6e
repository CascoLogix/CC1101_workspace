/*****************************************************************************/
//	Timer1_A3.c
//  
//	 Created on: Dec 15, 2014
//	     Author: Clint Stevenson
//
/*****************************************************************************/


/*****************************************************************************/
//	Includes
/*****************************************************************************/
#include <Timer1_A3.h>
#include <callback.h>
/*****************************************************************************/
//	End Includes


/*****************************************************************************/
//	Defines
/*****************************************************************************/
//Put defines here
/*****************************************************************************/
//	End Defines


/*****************************************************************************/
//	Constant Declarations
/*****************************************************************************/
//Put Constant Declarations here
/*****************************************************************************/
//	End Constant Declarations


/*****************************************************************************/
//	Variable Declarations
/*****************************************************************************/
//Put Variable Declarations here
functionPointer_t timer1_A1_callback[8];
functionPointer_t timer1_A0_callback;
/*****************************************************************************/
//	End Variable Declarations


/*****************************************************************************/
//	Function Prototypes
/*****************************************************************************/
//Put function prototypes here
/*****************************************************************************/
//	End Function Prototypes


/*****************************************************************************/
//	Function Definitions
/*****************************************************************************/
//Put function definitions here
void Timer1_init (void)
{
	TA1CTL = TASSEL_2;			// Clk = SMCLK; Clear timer
	TA1CTL |= MC_1;				// Start timer in "UP" mode
	TA1CCR0 = 0;				// Set compare 0 register to set frequency
	TA1CCTL0 = OUTMOD_4;		// Set compare mode to toggle on every match
}


void Timer1_armOneShot (uint16_t timerTicks, uint8_t outputVal)
{
	if (1 == outputVal)                 // If output pulse value should be hi
	{
		TA1CCTL0 = (OUTMOD_3 | OUT);    // Set mode to 'set/reset'; set OUT hi
	}

	else if (0 == outputVal)            // If output pulse value should be lo
	{
		TA1CCTL0 = OUTMOD_7;            // Set mode to 'reset/set'; set OUT lo
	}

	TA1CCR0 = TAR + timerTicks;         // Set compare register to current
}                                       //   timerA count + number of ticks


void Timer1_A1_registerCallback (uint8_t index, functionPointer_t fPtr)
{
	if(timer1_A1_callback[index] != 0)
	{
		timer1_A1_callback[index] = fPtr;
	}
}


void Timer1_A0_registerCallback (functionPointer_t fPtr)
{
	if(timer1_A0_callback != 0)
	{
		timer1_A0_callback = fPtr;
	}
}


#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1_A1_ISR (void)
{
	volatile uint16_t idx = TA1IV >> 1;	// Divide by two

	if(timer1_A1_callback[idx] != 0)
	{
		timer1_A1_callback[idx]();	// TA1IV will only ever be even
	}
}


#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR (void)
{
	if(timer1_A0_callback != 0)
	{
		timer1_A0_callback();
	}
}
/*****************************************************************************/
//	End Function Definitions
