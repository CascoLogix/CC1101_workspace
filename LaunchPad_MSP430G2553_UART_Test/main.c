/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/Grace.h>

int * pVar;

void (*pFunction) (void);
void subroutine (void);


/*
 *  ======== main ========
 */
int main(void)
{
    Grace_init();                   // Activate Grace-generated configuration
    
    pFunction = &subroutine;
    pFunction();

    return (0);
}


void subroutine (void)
{
	while(1)
	{
		_NOP();
	}
}
