/*****************************************************************************/
//	Timer0_A3.c
//  
//	 Created on: Dec 15, 2014
//	     Author: Clint Stevenson
//
/*****************************************************************************/


/*****************************************************************************/
//	Includes
/*****************************************************************************/
#include <Timer0_A3.h>
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
functionPointer_t timer0_A1_callback[8];
functionPointer_t timer0_A0_callback;
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
void Timer0_init (void)
{
	// Don't use TACLR bit, as it basically resets the entire timer peripheral
	TA0CTL = TASSEL_2 | ID_3;	// Clk = SMCLK/8
	TA0CCR1 = 0;				// Clear compare register
	TA0CTL |= MC_2;				// Start timer in "Continuous" mode
}


void Timer0_armOneShot (uint16_t timerTicks, uint8_t outputVal)
{
	// Don't use TACLR bit, as it basically resets the entire timer peripheral
	TA0CCR1 = timerTicks;				// Set compare register
	TAR = 0;

	if (1 == outputVal)					// If output pulse value should be hi
	{
		TA0CCTL1 = OUT;
		TA0CCTL1 |= OUTMOD_5 | CCIE;
	}

	else if (0 == outputVal)			// If output pulse value should be lo
	{
		TA0CCTL1 &= OUTMOD_1;			// Set mode to 'Set'
		TA0CCTL1 &= ~OUT;				// Set OUT lo
	}
}


void Timer0_A1_registerCallback (uint8_t index, functionPointer_t fPtr)
{
	timer0_A1_callback[index] = fPtr;
}


void Timer0_A0_registerCallback (functionPointer_t fPtr)
{
	timer0_A0_callback = fPtr;
}


#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR (void)
{
	volatile uint16_t idx = TA0IV >> 1;	// Divide by two

	if(timer0_A1_callback[idx] != 0)
	{
		timer0_A1_callback[idx]();	// TA0IV will only ever be even
	}
}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR (void)
{
	if(timer0_A0_callback != 0)
	{
		timer0_A0_callback();
	}
}
/*****************************************************************************/
//	End Function Definitions
