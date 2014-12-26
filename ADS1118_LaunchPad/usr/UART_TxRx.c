/*
 * 	- UART_TxRx.c
 *  - Created on: Nov 11, 2012
 *	- modification data: 31 Nov. 2012
 *	- author: Wayne Xu (a0219294)
 *	- version: v1.2
 */
#include <msp430g2553.h>
#include <ti/mcu/msp430/csl/CSL.h>



/******************************************************************************
 * function: uart_txc(char c)
 * introduction: transmit a char to UART
 * parameters: char c,
 * return value:
*******************************************************************************/
void uart_txc(char c)
{
	while (!((UC0IFG&UCA0TXIFG)));
	UCA0TXBUF=c;

}

/******************************************************************************
 * function: uart_txstr(char *c)
 * introduction: transmit a string to UART
 * parameters: char *c,
 * return value:
*******************************************************************************/
void uart_txstr(char *c)
{
	while (*c) uart_txc(*(c++));
}


/******************************************************************************
 * function: hex2asc(void *npos, int digs, int mode, char *s)
 * introduction: transform hex value to ascII code
 * parameters:
 * void *npos,
 * int digs,
 * int mode,
 * char *s
 * return value:
*******************************************************************************/
int hex2asc(void *npos, int digs, int mode, char *s)
{
	int i,zero;
	char dig;
	char *spos=s;
	char *n=(char *)npos;

	zero=1;
#if LITTLEENDIAN
	n+=(digs-1)>>1;
#else
	n+=(16-digs)>>1;
#endif
	for (i=digs-1;i>=0;--i) {
		if (i&1) {
			dig=(*(char *)n>>4)&15;
		} else {
			dig=*(char *)n&15;
#if LITTLEENDIAN
			--n;
#else
			++n;
#endif
		}
		if (zero&&dig)
			zero=0;
		if (zero) {
			switch(mode) {
			case 1:
				*spos++=' ';
				break;
			case 2:
				*spos++='0';
				break;
			default:
				break;
			}
		} else
			*spos++=h2a(dig);
	}
	if (zero&&mode==1)
		*(spos-1)='0';
	else if (zero&&mode==0)
		*spos++='0';
	*spos=0;
	return spos-s;
}

