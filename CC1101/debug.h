// Written by Jack Clark

#define BUFFERSIZE      25

#if defined (__MSP430G2231__)

#elif defined (__MSP430G2553__)

#define UARTIFLG2 IFG2
#define UARTIE2   IE2

#define UARTTXIFG UCA0TXIFG
#define UARTRXIFG UCA0RXIFG
#define UARTRXBUF UCA0RXBUF
#define UARTTXBUF UCA0TXBUF

#define UARTPSEL  P1SEL
#define UARTPSEL2 P1SEL2

#define UARTCTL1  UCA0CTL1
#define UARTBR0   UCA0BR0
#define UARTBR1   UCA0BR1
#define UARTMCTL  UCA0MCTL

// 9600 offset divider
#define UARTBRONUM   104

#define UARTSEL     UCSSEL_2
#define UARTUCBRSO  UCBRS0
#define UARTUCSWRST UCSWRST

#define UARTTXIE  UCA0TXIE
#define UARTRXIE  UCA0RXIE

// SetClock / UnSetClock #define
#define UCSCTL4         DCOCTL
#define UCSCTL5         BCSCTL1
#define UCSCTL6         Ctl6 // We don't use this value

// Interrupt 
#define UART_VECTOR USCIAB0RX_VECTOR

#elif defined (__MSP430F5171__)

#define UARTIFLG2 UCA0IFG
#define UARTIE2   UCA0IE
#define UARTTXIE  UCTXIE
#define UARTRXIE  UCRXIE

#define UARTTXIFG UCTXIFG
#define UARTRXIFG UCRXIFG
#define UARTRXBUF UCA0RXBUF
#define UARTTXBUF UCA0TXBUF

#define UARTPSEL  P1SEL
#define UARTPSEL2 P1SEL2

#define UARTCTL1  UCA0CTL1
#define UARTBR0   UCA0BR0
#define UARTBR1   UCA0BR1
#define UARTMCTL  UCA0MCTL

// 9600 offset divider
#define UARTBRONUM   109

#define UARTSEL     UCSSEL_3
#define UARTUCBRSO  UCBRS0
#define UARTUCSWRST UCSWRST

// Interrupt 
#define UART_VECTOR USCI_A0_VECTOR

#else
#error "Failed to match a default include file Please edit debug.h"
#endif

// Make sure to call this function to ensure
// that the UART is configured Unless you already
// configure it yourself
void UARTInit();

void Dprintf(const char * message, ...);

void putc(const char ch);
char getc();

int getline(char * message, int buf_size);

char *itoa(int i, char *a, int r = 10);
static char *i2a(unsigned i, char *a, unsigned r);

