#include <msp430.h>
#include "debug.h"

#include <stdarg.h>

int Ctl4 = 0;
int Ctl5 = 0;
int Ctl6 = 0;

void SetClock()
{
  Ctl4 = UCSCTL4;
  Ctl5 = UCSCTL5;
  Ctl6 = UCSCTL6;
  
 #if defined (__MSP430G2231__)

 #elif defined (__MSP430G2553__)
  if (CALBC1_1MHZ==0xFF)					// If calibration constant erased
  {
     while(1);                               // do not load, trap CPU!!
  }
  DCOCTL = 0;                               // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
#elif defined (__MSP430F5171__)

  UCSCTL4 |= SELS__DCOCLK;
  UCSCTL5 &= ~DIVS_7;
  UCSCTL6 &= ~SMCLKOFF;
#else
#error "Failed to match a default include file Please edit debug.h"
#endif
}

void UnSetClock()
{
  UCSCTL4 = Ctl4;
  UCSCTL5 = Ctl5;
  UCSCTL6 = Ctl6;
}

void  UARTInit()
{
  SetClock();

  UARTPSEL  |= BIT1 + BIT2;        // P1.1 = RXD, P1.2=TXD
  UARTPSEL2 |= BIT1 + BIT2;
  UARTCTL1  |= UARTSEL;            // SMCLK
  UARTBR0    = UARTBRONUM;                  // 9600 Baud
  UARTBR1    = 0;                    // 9600 Baud
  UARTMCTL   = UARTUCBRSO;          // Modulation UCBRSx = 1
  UARTCTL1  &= ~UARTUCSWRST;     // **Initialize USCI state machine**
  UARTIE2   |= UARTRXIE;            // Enable USCI_A0 RX interrupt
}

void Dprintf(const char * message, ...)
{
 // SetClock();
  
  va_list args;
  va_start(args, message);

  int maxPrint = 128;
  
  while(maxPrint-- && *message != '\0')
  {
    if(*message == '%')
    {
      switch(message[1])
      {
        char num[34];      
      case '%':
        putc('%');
        break;
      case 'b':
      case 'B':
        itoa(va_arg(args, int), num, 2);
        Dprintf(num);
        break;        
      case 'c':
      case 'C':
         putc(va_arg(args, char));        
        break;     
      case 'd':
      case 'D':
      case 'i':
      case 'I':
         itoa(va_arg(args, int), num, 10);
         Dprintf(num);
        break;
      case 's':
      case 'S':
        Dprintf(va_arg(args, char *));
        break;
      case 'u':
      case 'U':
        *i2a(va_arg(args, unsigned), num, 10)=0;
        Dprintf(num);
        break;
      case 'x':
      case 'X':
        itoa(va_arg(args, int), num, 16);
        Dprintf(num);
        break;        
      default:
       break;         
      }
      message += 2;
    }
    
    while (!(UARTIFLG2&UARTTXIFG));
    //__delay_cycles(1000);
    UARTTXBUF = *message;
    message++;
  }
    
  va_end(args);  
  while (!(UARTIFLG2&UARTTXIFG));
 // UnSetClock();
}

  static char *i2a(unsigned i, char *a, unsigned r)
  {
    if (i/r > 0)
      a = i2a(i/r,a,r);
    
    *a = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i%r];
    return a+1;
  }

  char *itoa(int i, char *a, int r)
  {
    if ((r < 2) || (r > 36))
      r = 10;
    
    if (i < 0)
    {
        *a = '-';
        *i2a(-(unsigned)i,a+1,r) = 0;
    }
    else 
    {
      *i2a(i,a,r) = 0;
    }
    
    return a;
  }

void putc(const char ch)
{
   // SetClock();
    while (!(UARTIFLG2&UARTTXIFG)); 
    __delay_cycles(100);
    UARTTXBUF = ch;
    //UnSetClock();
}

char getc()
{
   // SetClock();
   while (!(UARTIFLG2&UARTRXIFG));
  // UnSetClock();
   return UARTRXBUF;
}

int getline(char * message, int buf_size)
{
  //SetClock();
  int index = 0;
  
   while(index < buf_size)
   {
      while (!(UARTIFLG2&UARTRXIFG));
      *message = UARTRXBUF;
      if(*message == '\r')
      {
        *message = '\0';
        break;
      }
      message++;
      index++;
   }
  
   //UnSetClock();
   return index;
}



// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=UART_VECTOR
__interrupt void UART_ISR(void)
{
   while (!(UARTIFLG2&UARTTXIFG));                // USCI_A0 TX buffer ready?
  UARTTXBUF = UARTRXBUF;                    // TX -> RXed character      
      
   /*  
  Dprintf("Please Enter Hello\r\n");
  
  char buffer[BUFFERSIZE];
  
  if(BUFFERSIZE > getline(buffer, BUFFERSIZE))
  {
    Dprintf(buffer);
    Dprintf("\r\n");
  }
  
  
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    UCA0TXBUF = UCA0RXBUF;                  // TX -> RXed character
    // don't quit till character is sent
    while (!(UCA0IFG&UCTXIFG));             // USCI_A0 TX buffer ready?
    break;
  case 4:break;                             // Vector 4 - TXIFG
  default: break;
  }
  */
}


