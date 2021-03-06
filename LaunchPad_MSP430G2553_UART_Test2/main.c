

#include <main.h>

char string[] = "Hello";


/*
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    USCI_A0_init_UART(9600, USCI_A0_CLK_SRC_SMCLK);

    char * ptr = string;

    while(*ptr != 0)
    {
    	while(!(IFG2 & UCA0TXIFG));
        USCI_A0_UART_write_TX_buffer(*ptr++);
    }

    LPM0;

	return 0;
}


