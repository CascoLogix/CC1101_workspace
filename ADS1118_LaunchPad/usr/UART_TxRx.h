/********************************************************************
*
* This file supports assembler and C development for
* MSP430G2553 devices.
*
* UART_TxRx.h
*
* define the functions for uart tranciever
* uart_txc: transmit a char to UART port
* uart_txstr: tansmit a string to UART port
* Texas Instruments, Version 1.0
*
* Rev. 1.0, Setup
*
********************************************************************/


#ifndef __UART_TxRx
#define __UART_TxRx

#define h2a(d) ((d>9)?(d+'A'-10):(d+'0'))
#define LITTLEENDIAN 1

void uart_txc(char c);
void uart_txstr(char *c);
/* "hex2asc" Converts a 32-bit integer n into an ASCII string.

digs is the maximum number of digits to display.  Conversion is controlled
by mode, as follows:

- mode = 0: Leading zeroes are not printed.  The string may be
  less than digs digits long.
- mode = 1: Spaces are printed in place of leading zeroes.  The
  string will be digs digits long.
- mode = 2: Leading zeroes are printed.  The string will be digs
  digits long.

If the number is zero, at least one zero is printed in all modes.

This routine works by converting n to an 8-byte BCD number and calling
hex2asc.  No division by 10 is performed.
*/

int hex2asc(void *n, int digs, int mode, char *s);


#endif
