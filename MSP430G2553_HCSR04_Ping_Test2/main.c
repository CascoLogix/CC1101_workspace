/******************************************************************************/
//	main.c
//  
//	 Created on:
//	     Author:
//
//   Build Date: 2015-04-07
//   IDE: CCS Version 6.1.0
//   Compiler: TI v4.4.4
/******************************************************************************/



/******************************************************************************/
//	Includes
/******************************************************************************/
//Put includes here
#include <msp430.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <ping.h>
/******************************************************************************/
//	End Includes


/******************************************************************************/
//	Defines
/******************************************************************************/
//Put defines here
#define FALSE						(0)
#define TRUE						(!FALSE)


#define LED1_PORT_OUT 				(P1OUT)
#define LED1_PORT_DIR 				(P1DIR)
#define LED1_PIN 					(BIT0)
#define LED1_TOGGLE					(LED1_PORT_OUT ^= LED1_PIN)
#define LED1_ON						(LED1_PORT_OUT |= LED1_PIN)
#define LED1_OFF					(LED1_PORT_OUT &= ~LED1_PIN)


#define SMCLK_PRESCALER				(1)
#define SMCLK_FREQUENCY				(_FCPU / SMCLK_PRESCALER)					// _FCPU in MHz


#define TICK_PERIOD					(10)		// In milliseconds
#define TICKS_PER_SECOND			(1000 / TICK_PERIOD)
#define TIMERA0_PRESCALER			(8)
#define TIMERA0_FREQUENCY			(SMCLK_FREQUENCY / TIMERA0_PRESCALER)
#define TICK_PERIOD_COUNT			(TIMERA0_FREQUENCY * TICK_PERIOD / 1000)
#define TIMERA0_SIZE				(16)		// In bits
#define TIMERA0_RESOLUTION			(65536)		// Should be 2 ^ TIMERA0_SIZE
#if (TICK_PERIOD_COUNT > TIMERA0_RESOLUTION)
#error "Timer register size is insufficient for desired compare register value."
#endif
/******************************************************************************/
//	End Defines


/******************************************************************************/
//	Global Constant Declarations
/******************************************************************************/
//Put Global Constant Declarations here
/******************************************************************************/
//	End Global Constant Declarations


/******************************************************************************/
//	Global Variable Declarations
/******************************************************************************/
//Put Global Variable Declarations here
volatile uint16_t tickCount = 0;
/******************************************************************************/
//	End Global Variable Declarations


/******************************************************************************/
//	Function Prototypes
/******************************************************************************/
//Put function prototypes here
void setupWDT (void);
void setupClocks (void);
void setupLEDs (void);
void setupUART (const uint32_t * baudRate);
void serialPrintInt (uint32_t integer);
void serialPrint (const char * string);
void USCI_getBaudRateSettings (const uint32_t * baudRate, uint16_t * N_val, uint8_t * BRS_val);
void setupTimerA0 (void);
void setupTimerA0CCR0Tick (void);
void startTimerA0CCR0Tick (void);
uint8_t getBase2Exponent (uint32_t number);
/******************************************************************************/
//	End Function Prototypes


/******************************************************************************/
//	Main Definition
/******************************************************************************/
//Put main function here
/**
 * This is the main function
 */
int main(void)
{
	setupWDT();
	setupClocks();
	setupLEDs();
	ping_init();
	const uint32_t var = 9600;
	setupUART(&var);
	setupTimerA0();
	setupTimerA0CCR0Tick();
	startTimerA0CCR0Tick();

	_EINT();

	for(;;)
	{
		serialPrintInt(ping_triggerPing());
		serialPrint("\r\n");
		LPM0;									// Enter LPM0
	}
}
/******************************************************************************/
//	End Main Definition


/******************************************************************************/
//	Function Definitions
/******************************************************************************/
//Put function definitions here
/**
 * \brief Initializes the watchdog timer.
 *
 * This is a simple function that initializes the watchdog timer.  This function
 * should be customized per application needs.
 *
 * @param none
 */
void setupWDT (void)
{
	WDTCTL = WDTPW + WDTHOLD;					// Stop WDT
}


/**
 * \brief Sets up the system clocks.
 *
 * This function sets up the system clocks.  This function should be customized
 * per application needs.
 *
 * @param none
 */
void setupClocks (void)
{
#if (_FCPU == 1000000)
	BCSCTL1 = CALBC1_1MHZ;						// Set DCO @ 1MHz
	DCOCTL = CALDCO_1MHZ;
#elif (_FCPU == 2000000)
	BCSCTL1 = CALBC1_2MHZ;						// Set DCO @ 2MHz
	DCOCTL = CALDCO_2MHZ;
#elif (_FCPU == 4000000)
	BCSCTL1 = CALBC1_4MHZ;						// Set DCO @ 4MHz
	DCOCTL = CALDCO_4MHZ;
#elif (_FCPU == 8000000)
	BCSCTL1 = CALBC1_8MHZ;						// Set DCO @ 8MHz
	DCOCTL = CALDCO_8MHZ;
#elif (_FCPU == 16000000)
	BCSCTL1 = CALBC1_16MHZ;						// Set DCO @ 16MHz
	DCOCTL = CALDCO_16MHZ;
#endif // (_FCPU == 1000000)

#if (SMCLK_PRESCALER == 1)
	BCSCTL2 = DIVS_0;							// Set SMCLK = DCO / 1
#elif (SMCLK_PRESCALER == 2)
	BCSCTL2 = DIVS_1;							// Set SMCLK = DCO / 2
#elif (SMCLK_PRESCALER == 4)
	BCSCTL2 = DIVS_2;							// Set SMCLK = DCO / 4
#elif (SMCLK_PRESCALER == 8)
	BCSCTL2 = DIVS_3;							// Set SMCLK = DCO / 8
#endif

}


/**
 * \brief Sets up the IO registers for driving the LED's.
 *
 * This is a simple function that sets up the IO registers for driving the
 * LED's.
 *
 * @param none
 */
void setupLEDs (void)
{
	LED1_PORT_OUT = 0;							// Setup port output register
	LED1_PORT_DIR = LED1_PIN;					// Setup direction register
}


/**
 * \brief Sets up the UART module.
 *
 * This function sets up the UART module for operation.  You must pass it an
 * argument to specify the baud rate (units are bits/sec).
 *
 * @param [in] baudRate [type] U32
 */
void setupUART (const uint32_t * baudRate)
{
	P1SEL = BIT1 + BIT2;						// P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2;						// P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2;						// SMCLK

	// Runtime settings:
	uint16_t pScaler;
	uint8_t modCtl;
	USCI_getBaudRateSettings(baudRate, &pScaler, &modCtl);
	UCA0BR0 = 0x00FF & pScaler;					// 8MHz 9600
	UCA0BR1 = (0xFF00 & pScaler) >> 8;			// 8MHz 9600
	UCA0MCTL |= modCtl << 1;					// Modulation UCBRSx = 2

	UCA0CTL1 &= ~UCSWRST;						// **Initialize USCI state machine**
	IE2 |= UCA0RXIE;							// Enable USCI_A0 RX interrupt
}


/**
 * \brief This is the serialPrint function.
 *
 * The serialPrint function prints a null-terminated string to the UART port.
 * The string must be null-terminated!
 *
 * @param [in] str The pointer to the string to pass to the function
 */
void serialPrint (const char * str)
{
    static char pp = FALSE;
    while (pp);
    pp = TRUE;

    int i;
    for (i=0; str[i] != '\0'; ++i)
    {
        while (!(IFG2 & UCA0TXIFG));
        UCA0TXBUF = str[i];
    }

    pp = FALSE;
}


/**
 * \brief This is the serialPrintInt function.
 *
 * The serialPrintInt function prints the ASCII formatted integer to the UART
 * port.  Currently only 16-bit unsigned integers are supported.
 *
 * @param [in] integer The integer to print to the UART port.
 */
void serialPrintInt (uint32_t integer)
{
    char buf[16];
    ltoa(integer, buf);
    serialPrint(buf);
}


/**
 * \brief This is the USCI_getBaudRateSettings function.
 *
 * The  USCI_getBaudRateSettings takes in a pointer to a desired baud rate value
 * and pointers to two result variables to be used for setting baud rate prescaler
 * register settings.
 *
 * @param [in] baudRate The desired baud rate.
 *
 * @param [in/out] N_val The baud rate primary scaling value.
 *
 * @param [in/out] BRS_val The baud rate secondary scaling value.
 */
void USCI_getBaudRateSettings (const uint32_t * baudRate, uint16_t * N_val, uint8_t * BRS_val)
{
	/*
	 * Formula from datasheet:
	 * N = f_BRCLK / BaudRate
	 * UCBR[15:0] = INT(N)
	 * UCBRS[3:1] = Round((N - INT(N)) * 8)
	 */

	const uint8_t prescalerLookup[] = {1, 2, 4, 8};

#if defined(__MSP430_HAS_BC2__)
	(*N_val) = (_FCPU / prescalerLookup[((BCSCTL2 & DIVS_3) >> 1)]) / (*baudRate);	// Get integer portion of buad rate prescaler
#endif // defined(__MSP430_HAS_BC2__)

	uint32_t temp;
	temp = (_FCPU / prescalerLookup[((BCSCTL2 & DIVS_3) >> 1)]) % (*baudRate) * 8;	// Get remainder portion of baud rate prescaler for modulation control value calculation
	(*BRS_val) = temp / (*baudRate);						// Divide by baud rate per datasheet formula; this is the integer portion of the modulation control value
	temp = temp % *baudRate;								// Get remainder to determine if the modulation control value should be rounded up

	if(temp > ((*baudRate) / 2))							// 'Ceiling' function to round up if there is any remainder
	{
		(*BRS_val)++;
	}
}


/**
 * \brief This is the setupTimerA0 function.
 *
 * The setupTimerA0 function sets up the Timer A0 module
 *
 * @param None
 */
void setupTimerA0 (void)
{
	TA0CTL = TACLR;											// Reset Timer A0 module
#if (TIMERA0_PRESCALER == 1)
	TA0CTL = TASSEL_2 + ID_0;								// SMCLK, CLK/1
#elif (TIMERA0_PRESCALER == 2)
	TA0CTL = TASSEL_2 + ID_1;								// SMCLK, CLK/2
#elif (TIMERA0_PRESCALER == 4)
	TA0CTL = TASSEL_2 + ID_2;								// SMCLK, CLK/4
#elif (TIMERA0_PRESCALER == 8)
	TA0CTL = TASSEL_2 + ID_3;								// SMCLK, CLK/8
#endif // (TIMERA0_PRESCALER == 1)
}


/**
 * \brief This is the setupTimerA0CCR0Tick function.
 *
 * The setupTimerA0CCR0Tick function does this...
 *
 * None
 */
void setupTimerA0CCR0Tick (void)
{
	TA0CCTL0 = 0;											// Clear Timer A0 Capture Control register
	TA0CCR0 = TICK_PERIOD_COUNT;							// Set Timer A0 Capture Compare register for first tick time
}


/**
 * \brief This is the startTimerA0CCR0Tick function.
 *
 * The startTimerA0CCR0Tick function does this...
 *
 * None
 */
void startTimerA0CCR0Tick (void)
{
	TA0CCTL0 = CCIE;										// Enable
	TA0CTL |= MC_2;											// Start timer in Continuous Mode
}


/**
 * \brief This is the getBase2Exponent function.
 *
 * The getBase2Exponent function does this...
 *
 * @param [in] number Description of parameter
 *
 * @returns
 */
uint8_t getBase2Exponent (uint32_t number)
{
	uint8_t exponent = 0;

	while(number >= 2)
	{
		exponent++;
		number >>= 1;
	}

	return exponent;
}
/******************************************************************************/
//	End Function Definitions


/******************************************************************************/
//	Interrupt Service Routines
/******************************************************************************/
//Put Interrupt Service Routines here
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR (void)
{
	_NOP();
}


//  Echo back RXed character, confirm TX buffer is ready first
#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR (void)
{
	char c = UCA0RXBUF;

	while (!(IFG2 & UCA0TXIFG));                	// USCI_A0 TX buffer ready?

	UCA0TXBUF = c;									// Echo char
}


//Timer0_A
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0A0 (void)
{
	TA0CCR0 += TICK_PERIOD_COUNT;					// Add offset for next tick
	tickCount++;
	if(tickCount > TICKS_PER_SECOND)
	{
		tickCount = 0;								// Reset seconds counter
		LED1_TOGGLE;								// Toggle the LED
		LPM0_EXIT;									// Wake and get ping, etc.
	}

	/* Seudo Code
	 * millisTime++
	 * if(millisTime > 999)
	 * {
	 * 		millisTime = 0;
	 * 		secTime++;
	 * 		if(secTime > 59)
	 * 		{
	 * 			secTime = 0;
	 * 			minTime++;
	 * 			if(minTime > 59)
	 * 			{
	 * 				minTime = 0;
	 * 				hourTime++;
	 * 				if(hourTime > 23)
	 * 				{
	 * 					hourTime = 0;
	 * 					dayTime++;
	 * 					if(dayTime > daysInCurrentMonth)
	 * 					{
	 * 						dayTime = 1;
	 * 						monthTime++;
	 * 						if(monthTime > 11)
	 * 						{
	 * 							monthTime = 1;
	 * 							yearTime++;
	 * 						}
	 * 					}
	 * 				}
	 * 			}
	 * 		}
	 * }
	 */

}


//Timer1_A
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1A0 (void)
{
	if(TA1CCTL0 & CCI)								// Start of pulse (rising edge)
	{
		ping_markEchoStart();
	}

	else											// End of pulse (falling edge)
	{
		ping_markEchoStop();
	}
}


#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1A1 (void)
{
	switch(TA1IV)
	{
		case TA1IV_NONE:
			break;

		case TA1IV_TACCR1:
			break;

		case TA1IV_TACCR2:
			break;

		case TA1IV_6:
			break;

		case TA1IV_8:
			break;

		case TA1IV_TAIFG:
			ping_Overflow();
			break;

		default:
			break;
	}
}
/******************************************************************************/
//	End Function Definitions


/**
 * \brief This is the XYZ function.
 *
 * The XYZ function does this...
 *
 * @param [in] parIn Description of parameter
 *
 * @param [out] parOUT Description of parameter
 */

