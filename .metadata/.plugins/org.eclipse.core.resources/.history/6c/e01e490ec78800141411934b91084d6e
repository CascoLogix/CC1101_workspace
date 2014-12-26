

#include <msp430.h>
#include <stdint.h>
#include <Timer0_A3.h>
#include <Timer1_A3.h>
#include <GPIO.h>


#define S2_PIN		3
#define S2_BIT		BIT3
#define LED2_PIN	6
#define LED2_BIT	BIT6

#define BUZZER_PORT	PORT2
#define BUZZER_BIT	BIT0


void LED2_One_Shot (void);
void TA0CCR1_ISR_Handler (void);


/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    gpio_port1_init();
    Timer0_init();
    Timer1_init();

	GPIO_PORT1.out = S2_BIT;					// Set S2 pin out register for pullup
	GPIO_PORT1.direction = ~S2_BIT;				// Set LED pin to output mode
	GPIO_PORT1.resistor_enable = S2_BIT;		// Enable S2 pin pullup
	GPIO_PORT1.select = LED2_BIT;				// Select TA0.1
	GPIO_PORT1.select_2 = 0;
	GPIO_PORT1.interrupt_edge_select = S2_BIT;	// Set for falling edge
	GPIO_PORT1.interrupt_flag = 0;				// Clear interrupt flags
	GPIO_PORT1.interrupt_enable = S2_BIT;		// Enable interrupt

	GPIO_PORT2.direction = BUZZER_BIT;			// Set buzzer pin to output mode
	GPIO_PORT2.select = BUZZER_BIT;				// Select TA1.0
	GPIO_PORT2.select_2 = 0;

	GPIO_PORT1_registerCallback(S2_PIN, &LED2_One_Shot);		// Should blink the LED when the button is pressed.
	Timer0_A1_registerCallback (1, &TA0CCR1_ISR_Handler);

    _EINT();
    LPM0;

	return 0;
}


void LED2_One_Shot (void)
{
	GPIO_PORT1.interrupt_enable &= ~S2_BIT;		// Disable interrupt
	Timer0_armOneShot(25000, 1);				// Should cause a 200mS blink

	// TODO:
	// - replace with a function call to Timer1_A3 library
	TA1CCR0 = 300;								// Set compare 0 register to set frequency
}


void TA0CCR1_ISR_Handler (void)
{
	GPIO_PORT1.interrupt_enable |= S2_BIT;		// Enable P1.3 pin interrupt
	TA0CCTL1 &= ~CCIE;							// Disable TA0CCR1 interrupt

	// TODO:
	// - replace with a function call to Timer1_A3 library
	TA1CCR0 = 0;								// Set compare 0 register to turn off tone
}

