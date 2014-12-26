//------------------------------------------------------------------------------
//  Description:  This file contains functions that allow the MSP430 device to
//  access the SPI interface of the CC1100/CC2500.  There are multiple
//  instances of each function; the one to be compiled is selected by the
//  system variable RF_SER_INTF, defined in "Pinouts.h".
//
//------------------------------------------------------------------------------

#include "CC1101.h"
#include "Pinouts.h"
#include "Registers.h"

#include <msp430.h>

//------------------------------------------------------------------------------
//  void CC1101::SPISetup(void)
//
//  DESCRIPTION:
//  Configures the assigned interface to function as a SPI port and
//  initializes it.
//------------------------------------------------------------------------------
//  void CC1101::SPIWriteReg(char addr, char value)
//
//  DESCRIPTION:
//  Writes "value" to a single configuration register at address "addr".
//------------------------------------------------------------------------------
//  void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
//
//  DESCRIPTION:
//  Writes values to multiple configuration registers, the first register being
//  at address "addr".  First data byte is at "buffer", and both addr and
//  buffer are incremented sequentially (within the CCxxxx and MSP430,
//  respectively) until "count" writes have been performed.
//------------------------------------------------------------------------------
//  char CC1101::SPIReadReg(char addr)
//
//  DESCRIPTION:
//  Reads a single configuration register at address "addr" and returns the
//  value read.
//------------------------------------------------------------------------------
//  void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
//
//  DESCRIPTION:
//  Reads multiple configuration registers, the first register being at address
//  "addr".  Values read are deposited sequentially starting at address
//  "buffer", until "count" registers have been read.
//------------------------------------------------------------------------------
//  char CC1101::SPIReadStatus(char addr)
//
//  DESCRIPTION:
//  Special read function for reading status registers.  Reads status register
//  at register "addr" and returns the value read.
//------------------------------------------------------------------------------
//  void CC1101::SPIStrobe(char strobe)
//
//  DESCRIPTION:
//  Special write function for writing to command strobe registers.  Writes
//  to the strobe at address "addr".
//------------------------------------------------------------------------------


// Delay function. # of CPU cycles delayed is similar to "cycles". Specifically,
// it's ((cycles-15) % 6) + 15.  Not exact, but gives a sense of the real-time
// delay.  Also, if MCLK ~1MHz, "cycles" is similar to # of useconds delayed.
void CC1101::Wait(unsigned int cycles)
{
  while(cycles>15)                          // 15 cycles consumed by overhead
    cycles = cycles - 6;                    // 6 cycles consumed each iteration
}

//******************************************************************************
// If USART0 is used
//******************************************************************************
#if RF_SER_INTF == SER_INTF_USART0

void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  ME1 |= USPIE0;                            // Enable USART0 SPI mode
  UCTL0 = SWRST;                            // Disable USART state machine
  UCTL0 |= CHAR + SYNC + MM;                // 8-bit SPI Master **SWRST**
  UTCTL0 |= CKPH + SSEL1 + SSEL0 + STC;     // SMCLK, 3-pin mode
  UBR00 = 0x02;                             // UCLK/2
  UBR10 = 0x00;                             // 0
  UMCTL0 = 0x00;                            // No modulation
  SPI_USART0_PxSEL |= SPI_USART0_SIMO
				  | SPI_USART0_SOMI
				  | SPI_USART0_UCLK;
                                            // SPI option select
  SPI_USART0_PxDIR |= SPI_USART0_SIMO + SPI_USART0_UCLK;
                                            // SPI TX out direction
  UCTL0 &= ~SWRST;                          // Initialize USART state machine
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG1&UTXIFG0));                  // Wait for TX to finish
  U0TXBUF = addr;                           // Send address
  while (!(IFG1&UTXIFG0));                  // Wait for TX to finish
  U0TXBUF = value;                          // Send value
  while(!(UTCTL0&TXEPT));                   // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG1 & UTXIFG0));                // Wait for TX to finish
  U0TXBUF = addr | WRITE_BURST;   // Send address
  for (i = 0; i < count; i++)
  {
    while (!(IFG1 & UTXIFG0));              // Wait for TX to finish
    U0TXBUF = buffer[i];                    // Send data
  }
  while(!(UTCTL0 & TXEPT));
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG1 & UTXIFG0));                // Wait for TX to finish
  U0TXBUF = (addr | READ_SINGLE); // Send address
  while (!(IFG1 & UTXIFG0));                // Wait for TX to finish
  U0TXBUF = 0;                              // Dummy write so we can read data
  while(!(UTCTL0 & TXEPT));                 // Wait for TX complete
  x = U0RXBUF;                              // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG1 & UTXIFG0));                // Wait for TXBUF ready
  U0TXBUF = (addr | READ_BURST);  // Send address
  while(!(UTCTL0 & TXEPT));                 // Wait for TX complete
  U0TXBUF = 0;                              // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  IFG1 &= ~URXIFG0;                         // Clear flag
  while (!(IFG1&URXIFG0));                  // Wait for end of 1st data byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    U0TXBUF = 0;                            // Initiate next data RX, meanwhile
    buffer[i] = U0RXBUF;                    // Store data from last data RX
    while (!(IFG1&URXIFG0));                // Wait for end of data RX
  }
  buffer[count-1] = U0RXBUF;                // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// For status/strobe addresses, the BURST bit selects between status registers
// and command strobes.
char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG1 & UTXIFG0));                // Wait for TX to finish
  U0TXBUF = (addr | READ_BURST);  // Send address
  while (!(IFG1 & UTXIFG0));                // Wait for TX to finish
  U0TXBUF = 0;                              // Dummy write so we can read data
  while(!(UTCTL0 & TXEPT));                 // Wait for TX complete
  status = U0RXBUF;                         // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG1 & UTXIFG0));                // Wait for TX to finish
  U0TXBUF = strobe;                         // Send strobe
  // Strobe addr is now being TX'ed
  IFG1 &= ~URXIFG0;                         // Clear flag
  while(!(UTCTL0 & TXEPT));                 // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG1 & UTXIFG0));                // Wait for TX to finish
  U0TXBUF = SRES;                 // Send strobe
  // Strobe addr is now being TX'ed
  while(!(UTCTL0 & TXEPT));                 // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// END USART0
//******************************************************************************
// If USART1 is used
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_USART1

void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  ME2 |= USPIE1;                            // Enable USART1 SPI mode
  UCTL1 = SWRST;                            // Disable USART state machine
  UCTL1 |= CHAR + SYNC + MM;                // 8-bit SPI Master **SWRST**
  UTCTL1 |= CKPH + SSEL1 + SSEL0 + STC;     // SMCLK, 3-pin mode
  UBR01 = 0x02;                             // UCLK/2
  UBR11 = 0x00;                             // 0
  UMCTL1 = 0x00;                            // No modulation
  SPI_USART1_PxSEL |= SPI_USART1_SIMO
                   | SPI_USART1_SOMI
                   | SPI_USART1_UCLK;
                                            // SPI option select
  SPI_USART1_PxDIR |= SPI_USART1_SIMO + SPI_USART1_UCLK;
                                            // SPI TXD out direction
  UCTL1 &= ~SWRST;                          // Initialize USART state machine
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2&UTXIFG1));                  // Wait for TX to finish
  U1TXBUF = addr;                           // Send address
  while (!(IFG2&UTXIFG1));                  // Wait for TX to finish
  U1TXBUF = value;                          // Load data for TX after addr
  while(!(UTCTL1&TXEPT));                   // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2&UTXIFG1));                  // Wait for TX to finish
  U1TXBUF = addr | WRITE_BURST;   // Send address
  for (i = 0; i < count; i++)
  {
    while (!(IFG2&UTXIFG1));                // Wait for TX to finish
    U1TXBUF = buffer[i];                    // Send data
  }
  while(!(UTCTL1&TXEPT));                   // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2&UTXIFG1));                  // Wait for TX to finish
  U1TXBUF = (addr | READ_SINGLE); // Send address
  while (!(IFG2&UTXIFG1));                  // Wait for TX to finish
  U1TXBUF = 0;                              // Load dummy byte for TX after addr
  while(!(UTCTL1&TXEPT));                   // Wait for TX complete
  x = U1RXBUF;                              // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2&UTXIFG1));                  // Wait for TXBUF ready
  U1TXBUF = (addr | READ_BURST);  // Send address
  while(!(UTCTL1&TXEPT));                   // Wait for TX complete
  U1TXBUF = 0;                              // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  IFG2 &= ~URXIFG1;                         // Clear flag
  while (!(IFG2&URXIFG1));                  // Wait for end of 1st data byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    U1TXBUF = 0;                            // Initiate next data RX, meanwhile
    buffer[i] = U1RXBUF;                    // Store data from last data RX
    while (!(IFG2&URXIFG1));                // Wait for end of data RX
  }
  buffer[count-1] = U1RXBUF;                // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2&UTXIFG1));                  // Wait for TX to finish
  U1TXBUF = (addr | READ_BURST);  // Send address
  while (!(IFG2&UTXIFG1));                  // Wait for TX to finish
  U1TXBUF = 0;                              // Dummy write so we can read data
  while(!(UTCTL1&TXEPT));                   // Wait for TX complete
  status = U1RXBUF;                         // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2&UTXIFG1));                  // Wait for TX to finish
  U1TXBUF = strobe;                         // Send strobe
  // Strobe addr is now being TX'ed
  while(!(UTCTL1&TXEPT));                   // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2 & UTXIFG1));                // Wait for TX to finish
  U1TXBUF = SRES;                 // Send strobe
  // Strobe addr is now being TX'ed
  while(!(UTCTL1&TXEPT));                   // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// END SER_INTF_USART1
//******************************************************************************
// If USCIA0 is used
//   |-- If 5xx
//         |-- Use 5xx Init
//   |-- Else
//         |-- Use 2xx, 4xx Init
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_USCIA0

//******************************************************************************
// Support for 5xx USCI_A0
//******************************************************************************
#ifdef TI_5xx
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCA0CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCA0CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 0x02;                           // UCLK/2
  UCA0BR1 = 0;
  UCA0MCTL = 0;
  SPI_USCIA0_PxSEL |= SPI_USCIA0_SIMO
                         | SPI_USCIA0_SOMI
                         | SPI_USCIA0_UCLK;
                                            // SPI option select
  SPI_USCIA0_PxDIR |= SPI_USCIA0_SIMO | SPI_USCIA0_UCLK;
                                            // SPI TXD out direction
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA0TXBUF = addr;                         // Send address
  while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA0TXBUF = value;                        // Send data
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA0TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
    UCA0TXBUF = buffer[i];                  // Send data
  }
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA0TXBUF = (addr | READ_SINGLE);// Send address
  while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA0TXBUF = 0;                            // Dummy write so we can read data
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  x = UCA0RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA0TXBUF = (addr | READ_BURST);// Send address
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  UCA0TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  UCA0IFG &= ~UCRXIFG;                      // Clear flag
  while (!(UCA0IFG&UCRXIFG));               // Wait for end of addr byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCA0TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCA0RXBUF;                  // Store data from last data RX
    while (!(UCA0IFG&UCRXIFG));             // Wait for RX to finish
  }
  buffer[count-1] = UCA0RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA0TXBUF = (addr | READ_BURST);// Send address
  while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA0TXBUF = 0;                            // Dummy write so we can read data
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  status = UCA0RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA0TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA0TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// End of support for 5xx USCI_A0

#else
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCA0CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCA0CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 0x02;                           // UCLK/2
  UCA0BR1 = 0;
  UCA0MCTL = 0;
  SPI_USCIA0_PxSEL |= SPI_USCIA0_SIMO
                         | SPI_USCIA0_SOMI
                         | SPI_USCIA0_UCLK;
  SPI_USCIA0_PxSEL2 |= SPI_USCIA0_SIMO
          	  	  	  	 | SPI_USCIA0_SOMI
          	  	  	  	 | SPI_USCIA0_UCLK;


                                            // SPI option select
  SPI_USCIA0_PxDIR |= SPI_USCIA0_SIMO | SPI_USCIA0_UCLK;
                                            // SPI TXD out direction
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while(SPI_USCIA0_SOMI & SPI_USCIA0_PxIN);
  while (!(IFG2&UCA0TXIFG));                // Wait for TXBUF ready
  UCA0TXBUF = addr;                         // Send address
  while (!(IFG2&UCA0TXIFG));                // Wait for TXBUF ready
  UCA0TXBUF = value;                        // Send data
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while(SPI_USCIA0_SOMI & SPI_USCIA0_PxIN);
  while (!(IFG2&UCA0TXIFG));                // Wait for TXBUF ready
  UCA0TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(IFG2&UCA0TXIFG));              // Wait for TXBUF ready
    UCA0TXBUF = buffer[i];                  // Send data
  }
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while(SPI_USCIA0_SOMI & SPI_USCIA0_PxIN);
  while (!(IFG2&UCA0TXIFG));                // Wait for TX to finish
  UCA0TXBUF = (addr | READ_SINGLE);// Send address
  while (!(IFG2&UCA0TXIFG));                // Wait for TX to finish
  UCA0TXBUF = 0;                            // Dummy write so we can read data
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  x = UCA0RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while(SPI_USCIA0_SOMI & SPI_USCIA0_PxIN);		//wait for SO to go low
  while (!(IFG2&UCA0TXIFG));                // Wait for TX to finish
  UCA0TXBUF = (addr | READ_BURST);// Send address
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  UCA0TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  IFG2 &= ~UCA0RXIFG;                       // Clear flag
  while (!(IFG2&UCA0RXIFG));                // Wait for end of addr byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCA0TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCA0RXBUF;                  // Store data from last data RX
    while (!(IFG2&UCA0RXIFG));              // Wait for RX to finish
  }
  buffer[count-1] = UCA0RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while(SPI_USCIA0_SOMI & SPI_USCIA0_PxIN);
  while (!(IFG2&UCA0TXIFG));                // Wait for TX to finish
  UCA0TXBUF = (addr | READ_BURST);// Send address
  while (!(IFG2&UCA0TXIFG));                // Wait for TX to finish
  UCA0TXBUF = 0;                            // Dummy write so we can read data
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  status = UCA0RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while(SPI_USCIA0_SOMI & SPI_USCIA0_PxIN);
  while (!(IFG2&UCA0TXIFG));                // Wait for TX to finish
  UCA0TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while(SPI_USCIA0_SOMI & SPI_USCIA0_PxIN);
  while (!(IFG2&UCA0TXIFG));                // Wait for TXBUF ready
  UCA0TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA0STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

#endif
// END SER_INTF_USCIA0

//******************************************************************************
// If USCIA1 is used
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_USCIA1

//******************************************************************************
// Support for 5xx USCI_A1
//******************************************************************************
#ifdef TI_5xx
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCA1CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCA1CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCA1CTL1 |= UCSSEL_2;                     // SMCLK
  UCA1BR0 = 0x02;                           // UCLK/2
  UCA1BR1 = 0;
  UCA1MCTL = 0;
  SPI_USCIA1_PxSEL |= SPI_USCIA1_SIMO
                         | SPI_USCIA1_SOMI;
  SPI_USCIA1_PxSEL_UCLK |= SPI_USCIA1_UCLK;
                                            // SPI option select
  SPI_USCIA1_PxDIR |= SPI_USCIA1_SIMO;
  SPI_USCIA1_PxDIR_UCLK |=  SPI_USCIA1_UCLK;
                                            // SPI TXD out direction
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA1TXBUF = addr;                         // Send address
  while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA1TXBUF = value;                        // Send data
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA1TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
    UCA1TXBUF = buffer[i];                  // Send data
  }
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA1TXBUF = (addr | READ_SINGLE);// Send address
  while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA1TXBUF = 0;                            // Dummy write so we can read data
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  x = UCA1RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA1TXBUF = (addr | READ_BURST);// Send address
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  UCA1TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  UCA1IFG &= ~UCRXIFG;                      // Clear flag
  while (!(UCA1IFG&UCRXIFG));               // Wait for end of addr byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCA1TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCA1RXBUF;                  // Store data from last data RX
    while (!(UCA1IFG&UCRXIFG));             // Wait for RX to finish
  }
  buffer[count-1] = UCA1RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA1TXBUF = (addr | READ_BURST);// Send address
  while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA1TXBUF = 0;                            // Dummy write so we can read data
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  status = UCA1RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA1TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA1TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// End of support for 5xx USCI_A1

#else
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCA1CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCA1CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCA1CTL1 |= UCSSEL_2;                     // SMCLK
  UCA1BR0 = 0x02;                           // UCLK/2
  UCA1BR1 = 0;
  UCA1MCTL = 0;
  SPI_USCIA1_PxSEL |= SPI_USCIA1_SIMO
                         | SPI_USCIA1_SOMI
                         | SPI_USCIA1_UCLK;
                                            // SPI option select
  SPI_USCIA1_PxDIR |= SPI_USCIA1_SIMO | SPI_USCIA1_UCLK;
                                            // SPI TXD out direction
  UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCA1TXIFG));              // Wait for TXBUF ready
  UCA1TXBUF = addr;                         // Send address
  while (!(UC1IFG&UCA1TXIFG));              // Wait for TXBUF ready
  UCA1TXBUF = value;                        // Send data
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCA1TXIFG));              // Wait for TXBUF ready
  UCA1TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(UC1IFG&UCA1TXIFG));            // Wait for TXBUF ready
    UCA1TXBUF = buffer[i];                  // Send data
  }
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCA1TXIFG));              // Wait for TXBUF ready
  UCA1TXBUF = (addr | READ_SINGLE);// Send address
  while (!(UC1IFG&UCA1TXIFG));              // Wait for TX to finish
  UCA1TXBUF = 0;                            // Dummy write so we can read data
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  x = UCA1RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCA1TXIFG));              // Wait for TXBUF ready
  UCA1TXBUF = (addr | READ_BURST);// Send address
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  UCA1TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  UC1IFG &= ~UCA1RXIFG;                     // Clear flag
  while (!(UC1IFG&UCA1RXIFG));              // Wait for end of 1st data byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCA1TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCA1RXBUF;                  // Store data from last data RX
    while (!(UC1IFG&UCA1RXIFG));            // Wait for RX to finish
  }
  buffer[count-1] = UCA1RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCA1TXIFG));              // Wait for TXBUF ready
  UCA1TXBUF = (addr | READ_BURST);// Send address
  while (!(UC1IFG&UCA1TXIFG));              // Wait for TXBUF ready
  UCA1TXBUF = 0;                            // Dummy write so we can read data
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  status = UCA1RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCA1TXIFG));              // Wait for TXBUF ready
  UCA1TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCA1TXIFG));              // Wait for TXBUF ready
  UCA1TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

#endif
// End of USCIA1

//******************************************************************************
// If USCIA2 is used
//   |-- If 5xx
//         |-- Use 5xx Init
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_USCIA2

//******************************************************************************
// Support for 5xx USCI_A2
//******************************************************************************
#ifdef TI_5xx
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCA2CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCA2CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCA2CTL1 |= UCSSEL_2;                     // SMCLK
  UCA2BR0 = 0x02;                           // UCLK/2
  UCA2BR1 = 0;
  SPI_USCIA2_PxSEL |= SPI_USCIA2_SOMI
                         | SPI_USCIA2_UCLK
                         | SPI_USCIA2_SIMO;
                                            // SPI option select
  SPI_USCIA2_PxDIR |= SPI_USCIA2_UCLK | SPI_USCIA2_SIMO;
                                            // SPI TXD out direction
  UCA2CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA2TXBUF = addr;                         // Send address
  while (!(UCA2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA2TXBUF = value;                        // Send data
  while (UCA2STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA2TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(UCA2IFG&UCTXIFG));             // Wait for TXBUF ready
    UCA2TXBUF = buffer[i];                  // Send data
  }
  while (UCA2STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA2TXBUF = (addr | READ_SINGLE);// Send address
  while (!(UCA2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA2TXBUF = 0;                            // Dummy write so we can read data
  while (UCA2STAT & UCBUSY);                // Wait for TX complete
  x = UCA2RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA2TXBUF = (addr | READ_BURST);// Send address
  while (UCA2STAT & UCBUSY);                // Wait for TX complete
  UCA2TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  UCA2IFG &= ~UCRXIFG;                      // Clear flag
  while (!(UCA2IFG&UCRXIFG));               // Wait for end of addr byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCA2TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCA2RXBUF;                  // Store data from last data RX
    while (!(UCA2IFG&UCRXIFG));             // Wait for RX to finish
  }
  buffer[count-1] = UCA2RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA2TXBUF = (addr | READ_BURST);// Send address
  while (!(UCA2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA2TXBUF = 0;                            // Dummy write so we can read data
  while (UCA2STAT & UCBUSY);                // Wait for TX complete
  status = UCA2RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA2TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA2STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA2TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA2STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// End of support for 5xx USCI_A2
#endif
// End of support for USCI_A2

//******************************************************************************
// If USCIA3 is used
//   |-- If 5xx
//         |-- Use 5xx Init
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_USCIA3

//******************************************************************************
// Support for 5xx USCI_A3
//******************************************************************************
#ifdef TI_5xx
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCA3CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCA3CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCA3CTL1 |= UCSSEL_2;                     // SMCLK
  UCA3BR0 = 0x02;                           // UCLK/2
  UCA3BR1 = 0;
  SPI_USCIA3_PxSEL |= SPI_USCIA3_SOMI
                         | SPI_USCIA3_UCLK
                         | SPI_USCIA3_SIMO;
                                            // SPI option select
  SPI_USCIA3_PxDIR |= SPI_USCIA3_UCLK | SPI_USCIA3_SIMO;
                                            // SPI TXD out direction
  UCA3CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA3TXBUF = addr;                         // Send address
  while (!(UCA3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA3TXBUF = value;                        // Send data
  while (UCA3STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA3TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(UCA3IFG&UCTXIFG));             // Wait for TXBUF ready
    UCA3TXBUF = buffer[i];                  // Send data
  }
  while (UCA3STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA3TXBUF = (addr | READ_SINGLE);// Send address
  while (!(UCA3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA3TXBUF = 0;                            // Dummy write so we can read data
  while (UCA3STAT & UCBUSY);                // Wait for TX complete
  x = UCA3RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA3TXBUF = (addr | READ_BURST);// Send address
  while (UCA3STAT & UCBUSY);                // Wait for TX complete
  UCA3TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  UCA3IFG &= ~UCRXIFG;                      // Clear flag
  while (!(UCA3IFG&UCRXIFG));               // Wait for end of addr byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCA3TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCA3RXBUF;                  // Store data from last data RX
    while (!(UCA3IFG&UCRXIFG));             // Wait for RX to finish
  }
  buffer[count-1] = UCA3RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA3TXBUF = (addr | READ_BURST);// Send address
  while (!(UCA3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA3TXBUF = 0;                            // Dummy write so we can read data
  while (UCA3STAT & UCBUSY);                // Wait for TX complete
  status = UCA3RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA3TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA3STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCA3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCA3TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCA3STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// End of support for 5xx USCI_A3
#endif
// End of support for USCI_A3

//******************************************************************************
// If USCIB0 is used
//   |-- If 5xx
//         |-- Use 5xx Init
//   |-- Else
//         |-- Use 2xx, 4xx Init
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_USCIB0

//******************************************************************************
// Support for 5xx USCI_B0
//******************************************************************************
#ifdef TI_5xx
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCB0CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCB0CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 0x02;                           // UCLK/2
  UCB0BR1 = 0;
  SPI_USCIB0_PxSEL |= SPI_USCIB0_SIMO
                         | SPI_USCIB0_SOMI
                         | SPI_USCIB0_UCLK;
                                            // SPI option select
#if defined (__PxSEL2__)
  SPI_USCIB0_PxSEL2 |= SPI_USCIB0_SIMO
          	  	  	  	 | SPI_USCIB0_SOMI
          	  	  	  	 | SPI_USCIB0_UCLK;
#endif
  SPI_USCIB0_PxDIR |= SPI_USCIB0_SIMO | SPI_USCIB0_UCLK;
                                            // SPI TXD out direction
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB0TXBUF = addr;                         // Send address
  while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB0TXBUF = value;                        // Send data
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB0TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
    UCB0TXBUF = buffer[i];                  // Send data
  }
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB0TXBUF = (addr | READ_SINGLE);// Send address
  while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB0TXBUF = 0;                            // Dummy write so we can read data
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  x = UCB0RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB0TXBUF = (addr | READ_BURST);// Send address
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  UCB0TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  UCB0IFG &= ~UCRXIFG;                      // Clear flag
  while (!(UCB0IFG&UCRXIFG));               // Wait for end of 1st data byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCB0TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCB0RXBUF;                  // Store data from last data RX
    while (!(UCB0IFG&UCRXIFG));              // Wait for RX to finish
  }
  buffer[count-1] = UCB0RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB0TXBUF = (addr | READ_BURST);// Send address
  while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB0TXBUF = 0;                            // Dummy write so we can read data
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  status = UCB0RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB0TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB0IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB0TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

#else
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCB0CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCB0CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 0x02;                           // UCLK/2
  UCB0BR1 = 0;
  SPI_USCIB0_PxSEL |= SPI_USCIB0_SIMO
                         | SPI_USCIB0_SOMI
                         | SPI_USCIB0_UCLK;

#if defined (__PxSEL2__)
  SPI_USCIB0_PxSEL2 |= SPI_USCIB0_SIMO
          	  	  	  	 | SPI_USCIB0_SOMI
          	  	  	  	 | SPI_USCIB0_UCLK;
#endif
                                            // SPI option select
  SPI_USCIB0_PxDIR |= SPI_USCIB0_SIMO | SPI_USCIB0_UCLK;
                                            // SPI TXD out direction
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = addr;                         // Send address
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = value;                        // Send data
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(IFG2&UCB0TXIFG));              // Wait for TXBUF ready
    UCB0TXBUF = buffer[i];                  // Send data
  }
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        			// /CS enable
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = (addr | READ_SINGLE);			// Send address
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = 0;                            // Dummy write so we can read data
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  x = UCB0RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         			// /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        			// /CS enable
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = (addr | READ_BURST);			// Send address
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  UCB0TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  IFG2 &= ~UCB0RXIFG;                       // Clear flag
  while (!(IFG2&UCB0RXIFG));                // Wait for end of 1st data byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCB0TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCB0RXBUF;                  // Store data from last data RX
    while (!(IFG2&UCB0RXIFG));              // Wait for RX to finish
  }
  buffer[count-1] = UCB0RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         			// /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        			// /CS enable
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = (addr | READ_BURST);			// Send address
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = 0;                            // Dummy write so we can read data
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  status = UCB0RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         			// /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        			// /CS enable
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_PxOUT |= CSn_PIN;         			// /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        			// /CS enable
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = SRES;               			// Send strobe
  // Strobe addr is now being TX'ed
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_PxOUT |= CSn_PIN;         			// /CS disable
}

#endif
// End of USCIB0

//******************************************************************************
// If USCIB1 is used
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_USCIB1

//******************************************************************************
// Support for 5xx USCI_B1
//******************************************************************************
#ifdef TI_5xx
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCB1CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCB1CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCB1CTL1 |= UCSSEL_2;                     // SMCLK
  UCB1BR0 = 0x02;                           // UCLK/2
  UCB1BR1 = 0;
  SPI_USCIB1_PxSEL |= SPI_USCIB1_SOMI
                         | SPI_USCIB1_UCLK;
  SPI_USCIB1_PxSEL_SIMO |= SPI_USCIB1_SIMO;
                                            // SPI option select
  SPI_USCIB1_PxDIR |= SPI_USCIB1_UCLK;
  SPI_USCIB1_PxDIR_SIMO |=  SPI_USCIB1_SIMO;
                                            // SPI TXD out direction
  UCB1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB1TXBUF = addr;                         // Send address
  while (!(UCB1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB1TXBUF = value;                        // Send data
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB1TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(UCB1IFG&UCTXIFG));             // Wait for TXBUF ready
    UCB1TXBUF = buffer[i];                  // Send data
  }
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB1TXBUF = (addr | READ_SINGLE);// Send address
  while (!(UCB1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB1TXBUF = 0;                            // Dummy write so we can read data
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  x = UCB1RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB1TXBUF = (addr | READ_BURST);// Send address
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  UCB1TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  UCB1IFG &= ~UCRXIFG;                      // Clear flag
  while (!(UCB1IFG&UCRXIFG));               // Wait for end of addr byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCB1TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCB1RXBUF;                  // Store data from last data RX
    while (!(UCB1IFG&UCRXIFG));             // Wait for RX to finish
  }
  buffer[count-1] = UCB1RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB1TXBUF = (addr | READ_BURST);// Send address
  while (!(UCB1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB1TXBUF = 0;                            // Dummy write so we can read data
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  status = UCB1RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB1TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB1IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB1TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// End of support for 5xx USCI_B1
#else

void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCB1CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCB1CTL0 |= UCMST+UCCKPL+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCB1CTL1 |= UCSSEL_2;                     // SMCLK
  UCB1BR0 = 0x02;                           // UCLK/2
  UCB1BR1 = 0;
  SPI_USCIB1_PxSEL |= SPI_USCIB1_SIMO
                         | SPI_USCIB1_SOMI
                         | SPI_USCIB1_UCLK;
                                            // SPI option select
  SPI_USCIB1_PxDIR |= SPI_USCIB1_SIMO | SPI_USCIB1_UCLK;
                                            // SPI TXD out direction
  UCB1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCB1TXIFG));              // Wait for TXBUF ready
  UCB1TXBUF = addr;                         // Send address
  while (!(UC1IFG&UCB1TXIFG));              // Wait for TXBUF ready
  UCB1TXBUF = value;                        // Send data
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCB1TXIFG));              // Wait for TXBUF ready
  UCB1TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(UC1IFG&UCB1TXIFG));            // Wait for TXBUF ready
    UCB1TXBUF = buffer[i];                  // Send data
  }
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCB1TXIFG));              // Wait for TXBUF ready
  UCB1TXBUF = (addr | READ_SINGLE);// Send address
  while (!(UC1IFG&UCB1TXIFG));              // Wait for TXBUF ready
  UCB1TXBUF = 0;                            // Dummy write so we can read data
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  x = UCB1RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCB1TXIFG));              // Wait for TXBUF ready
  UCB1TXBUF = (addr | READ_BURST);// Send address
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  UCB1TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  UC1IFG &= ~UCB1RXIFG;                     // Clear flag
  while (!(UC1IFG&UCB1RXIFG));              // Wait for end of 1st data byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCB1TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCB1RXBUF;                  // Store data from last data RX
    while (!(UC1IFG&UCB1RXIFG));            // Wait for RX to finish
  }
  buffer[count-1] = UCB1RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCB1TXIFG));              // Wait for TXBUF ready
  UCB1TXBUF = (addr | READ_BURST);// Send address
  while (!(UC1IFG&UCB1TXIFG));              // Wait for TXBUF ready
  UCB1TXBUF = 0;                            // Dummy write so we can read data
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  status = UCB1RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCB1TXIFG));              // Wait for TXBUF ready
  UCB1TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UC1IFG&UCB1TXIFG));              // Wait for TXBUF ready
  UCB1TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB1STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// End of USCIB1
#endif

//******************************************************************************
// If USCIB2 is used
//   |-- If 5xx
//         |-- Use 5xx Init
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_USCIB2

//******************************************************************************
// Support for 5xx USCI_B2
//******************************************************************************
#ifdef TI_5xx
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCB2CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCB2CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCB2CTL1 |= UCSSEL_2;                     // SMCLK
  UCB2BR0 = 0x02;                           // UCLK/2
  UCB2BR1 = 0;
  SPI_USCIB2_PxSEL |= SPI_USCIB2_SOMI
                         | SPI_USCIB2_UCLK
                         | SPI_USCIB2_SIMO;
                                            // SPI option select
  SPI_USCIB2_PxDIR |= SPI_USCIB2_UCLK | SPI_USCIB2_SIMO;
                                            // SPI TXD out direction
  UCB2CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB2TXBUF = addr;                         // Send address
  while (!(UCB2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB2TXBUF = value;                        // Send data
  while (UCB2STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB2TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(UCB2IFG&UCTXIFG));             // Wait for TXBUF ready
    UCB2TXBUF = buffer[i];                  // Send data
  }
  while (UCB2STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB2TXBUF = (addr | READ_SINGLE);// Send address
  while (!(UCB2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB2TXBUF = 0;                            // Dummy write so we can read data
  while (UCB2STAT & UCBUSY);                // Wait for TX complete
  x = UCB2RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB2TXBUF = (addr | READ_BURST);// Send address
  while (UCB2STAT & UCBUSY);                // Wait for TX complete
  UCB2TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  UCB2IFG &= ~UCRXIFG;                      // Clear flag
  while (!(UCB2IFG&UCRXIFG));               // Wait for end of addr byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCB2TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCB2RXBUF;                  // Store data from last data RX
    while (!(UCB2IFG&UCRXIFG));             // Wait for RX to finish
  }
  buffer[count-1] = UCB2RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB2TXBUF = (addr | READ_BURST);// Send address
  while (!(UCB2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB2TXBUF = 0;                            // Dummy write so we can read data
  while (UCB2STAT & UCBUSY);                // Wait for TX complete
  status = UCB2RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB2TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB2STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB2IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB2TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB2STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// End of support for 5xx USCI_B2
#endif

// End of support for USCI_B2

//******************************************************************************
// If USCIB3 is used
//   |-- If 5xx
//         |-- Use 5xx Init
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_USCIB3

//******************************************************************************
// Support for 5xx USCI_B3
//******************************************************************************
#ifdef TI_5xx
void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  UCB3CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCB3CTL0 |= UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCB3CTL1 |= UCSSEL_2;                     // SMCLK
  UCB3BR0 = 0x02;                           // UCLK/2
  UCB3BR1 = 0;
  SPI_USCIB3_PxSEL |= SPI_USCIB3_SOMI
                         | SPI_USCIB3_UCLK
                         | SPI_USCIB3_SIMO;
                                            // SPI option select
  SPI_USCIB3_PxDIR |= SPI_USCIB3_UCLK | SPI_USCIB3_SIMO;
                                            // SPI TXD out direction
  UCB3CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB3TXBUF = addr;                         // Send address
  while (!(UCB3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB3TXBUF = value;                        // Send data
  while (UCB3STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB3TXBUF = addr | WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(UCB3IFG&UCTXIFG));             // Wait for TXBUF ready
    UCB3TXBUF = buffer[i];                  // Send data
  }
  while (UCB3STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB3TXBUF = (addr | READ_SINGLE);// Send address
  while (!(UCB3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB3TXBUF = 0;                            // Dummy write so we can read data
  while (UCB3STAT & UCBUSY);                // Wait for TX complete
  x = UCB3RXBUF;                            // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB3TXBUF = (addr | READ_BURST);// Send address
  while (UCB3STAT & UCBUSY);                // Wait for TX complete
  UCB3TXBUF = 0;                            // Dummy write to read 1st data byte
  // Addr byte is now being TX'ed, with dummy byte to follow immediately after
  UCB3IFG &= ~UCRXIFG;                      // Clear flag
  while (!(UCB3IFG&UCRXIFG));               // Wait for end of addr byte TX
  // First data byte now in RXBUF
  for (i = 0; i < (count-1); i++)
  {
    UCB3TXBUF = 0;                          //Initiate next data RX, meanwhile..
    buffer[i] = UCB3RXBUF;                  // Store data from last data RX
    while (!(UCB3IFG&UCRXIFG));             // Wait for RX to finish
  }
  buffer[count-1] = UCB3RXBUF;              // Store last RX byte in buffer
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char status;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB3TXBUF = (addr | READ_BURST);// Send address
  while (!(UCB3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB3TXBUF = 0;                            // Dummy write so we can read data
  while (UCB3STAT & UCBUSY);                // Wait for TX complete
  status = UCB3RXBUF;                       // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return status;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB3TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB3STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (!(UCB3IFG&UCTXIFG));               // Wait for TXBUF ready
  UCB3TXBUF = SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB3STAT & UCBUSY);                // Wait for TX complete
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

// End of support for 5xx USCI_B3
#endif
// End of support for USCI_B3

//******************************************************************************
// If USI is used
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_USI


void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  USICTL0 |= USIPE7 +  USIPE6 + USIPE5 + USIMST + USIOE;// Port, SPI master
  USICKCTL = USISSEL_2 + USICKPL;           // SCLK = SMCLK
  USICTL0 &= ~USISWRST;                     // USI released for operation

  USISRL = 0x00;                            // Ensure SDO low instead of high,
  USICNT = 1;                               // to avoid conflict with CCxxxx
}

void CC1101::SPIWriteReg(char addr, char value)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (SPI_USI_PxIN&SPI_USI_SOMI);// Wait for CCxxxx ready
  USISRL = addr;                            // Load address
  USICNT = 8;                               // Send it
  while (!(USICTL1&USIIFG));                // Wait for TX to finish
  USISRL = value;                           // Load value
  USICNT = 8;                               // Send it
  while (!(USICTL1&USIIFG));                // Wait for TX to finish
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (SPI_USI_PxIN&SPI_USI_SOMI);// Wait for CCxxxx ready
  USISRL = addr | WRITE_BURST;    // Load address
  USICNT = 8;                               // Send it
  while (!(USICTL1&USIIFG));                // Wait for TX to finish
  for (i = 0; i < count; i++)
  {
    USISRL = buffer[i];                     // Load data
    USICNT = 8;                             // Send it
    while (!(USICTL1&USIIFG));              // Wait for TX to finish
  }
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (SPI_USI_PxIN&SPI_USI_SOMI);// Wait for CCxxxx ready
  USISRL = addr | READ_SINGLE;    // Load address
  USICNT = 8;                               // Send it
  while (!(USICTL1&USIIFG));                // Wait for TX to finish
  USICNT = 8;                               // Dummy write so we can read data
  while (!(USICTL1&USIIFG));                // Wait for RX to finish
  x = USISRL;                               // Store data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (SPI_USI_PxIN&SPI_USI_SOMI);// Wait for CCxxxx ready
  USISRL = addr | READ_BURST;     // Load address
  USICNT = 8;                               // Send it
  while (!(USICTL1&USIIFG));                // Wait for TX to finish
  for (i = 0; i < count; i++)
  {
    USICNT = 8;                             // Dummy write so we can read data
    while (!(USICTL1&USIIFG));              // Wait for RX to finish
    buffer[i] = USISRL;                     // Store data
  }
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (SPI_USI_PxIN&SPI_USI_SOMI);// Wait for CCxxxx ready
  USISRL = addr | READ_BURST;     // Load address
  USICNT = 8;                               // Send it
  while (!(USICTL1&USIIFG));                // Wait for TX to finish
  USICNT = 8;                               // Dummy write so we can read data
  while (!(USICTL1&USIIFG));                // Wait for RX to finish
  x = USISRL;                               // Store data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (SPI_USI_PxIN&SPI_USI_SOMI);// Wait for CCxxxx ready
  USISRL = strobe;                          // Load strobe
  USICNT = 8;                               // Send it
  while (!(USICTL1&USIIFG));                // Wait for TX to finish
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  // Sec. 27.1 of CC1100 datasheet
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;
  while (SPI_USI_PxIN&SPI_USI_SOMI);
  USISRL = SRES;
  USICNT = 8;
  while (!(USICTL1&USIIFG));
  while (SPI_USI_PxIN&SPI_USI_SOMI);
  CSn_PxOUT |= CSn_PIN;
}

// End of USI

//******************************************************************************
// If Bit Bang is used
//******************************************************************************
#elif RF_SER_INTF == SER_INTF_BITBANG

void SPI_bitbang_out(char);
char SPI_bitbang_in();

void CC1101::SPISetup(void)
{
  CSn_PxOUT |= CSn_PIN;
  CSn_PxDIR |= CSn_PIN;         // /CS disable

  // Config bitbang pins
  SPI_BITBANG_PxOUT |= SPI_BITBANG_SIMO;
  SPI_BITBANG_PxOUT &= ~SPI_BITBANG_UCLK;
  SPI_BITBANG_PxDIR |= SPI_BITBANG_SIMO | SPI_BITBANG_UCLK;
}

// Output eight-bit value using selected bit-bang pins
void SPI_bitbang_out(char value)
{
  char x;

  for(x=8;x>0;x--)
  {
    if(value & 0x80)                                     // If bit is high...
      SPI_BITBANG_PxOUT |= SPI_BITBANG_SIMO; // Set SIMO high...
    else
      SPI_BITBANG_PxOUT &= ~SPI_BITBANG_SIMO;// Set SIMO low...
    value = value << 1;                                  // Rotate bits

    SPI_BITBANG_PxOUT &= ~SPI_BITBANG_UCLK;  // Set clock low
    SPI_BITBANG_PxOUT |= SPI_BITBANG_UCLK;   // Set clock high
  }
  SPI_BITBANG_PxOUT &= ~SPI_BITBANG_UCLK;  // Set clock low
}

// Input eight-bit value using selected bit-bang pins
char SPI_bitbang_in()
{
  char x=0,shift=0;
  int y;

  // Determine how many bit positions SOMI is from least-significant bit
  x = SPI_BITBANG_SOMI;
  while(x>1)
  {
    shift++;
    x = x >> 1;
  };

  x = 0;
  for(y=8;y>0;y--)
  {
    SPI_BITBANG_PxOUT &= ~SPI_BITBANG_UCLK;// Set clock low
    SPI_BITBANG_PxOUT |= SPI_BITBANG_UCLK;// Set clock high

    x = x << 1;                             // Make room for next bit
    x = x | ((SPI_BITBANG_PxIN & SPI_BITBANG_SOMI) >> shift);
  }                                         // Store next bit
  SPI_BITBANG_PxOUT &= ~SPI_BITBANG_UCLK; // Set clock low
  return(x);
}

void CC1101::SPIWriteReg(char addr, char value)
{
    CSn_PxOUT &= ~CSn_PIN;      // /CS enable
    while (SPI_BITBANG_PxIN&SPI_BITBANG_SOMI); // Wait CCxxxx ready
    SPI_bitbang_out(addr);            // Send address
    SPI_bitbang_out(value);           // Send data
    CSn_PxOUT |= CSn_PIN;       // /CS disable
}

void CC1101::SPIWriteBurstReg(char addr, char *buffer, char count)
{
    char i;

    CSn_PxOUT &= ~CSn_PIN;      // /CS enable
    while (SPI_BITBANG_PxIN&SPI_BITBANG_SOMI); // Wait CCxxxx ready
    SPI_bitbang_out(addr | WRITE_BURST);   // Send address
    for (i = 0; i < count; i++)
      SPI_bitbang_out(buffer[i]);     // Send data
    CSn_PxOUT |= CSn_PIN;       // /CS disable
}

char CC1101::SPIReadReg(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  SPI_bitbang_out(addr | READ_SINGLE);//Send address
  x = SPI_bitbang_in();               // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (SPI_BITBANG_PxIN&SPI_BITBANG_SOMI); // Wait CCxxxx ready
  SPI_bitbang_out(addr | READ_BURST);    // Send address
  for (i = 0; i < count; i++)
    buffer[i] = SPI_bitbang_in();     // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

char CC1101::SPIReadStatus(char addr)
{
  char x;

  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (SPI_BITBANG_PxIN & SPI_BITBANG_SOMI); // Wait CCxxxx ready
  SPI_bitbang_out(addr | READ_BURST);      // Send address
  x = SPI_bitbang_in();               // Read data
  CSn_PxOUT |= CSn_PIN;         // /CS disable

  return x;
}

void CC1101::SPIStrobe(char strobe)
{
  CSn_PxOUT &= ~CSn_PIN;        // /CS enable
  while (SPI_BITBANG_PxIN&SPI_BITBANG_SOMI);// Wait for CCxxxx ready
  SPI_bitbang_out(strobe);            // Send strobe
  CSn_PxOUT |= CSn_PIN;         // /CS disable
}

void CC1101::PowerupReset(void)
{
  // Sec. 27.1 of CC1100 datasheet
  CSn_PxOUT |= CSn_PIN;
  Wait(30);
  CSn_PxOUT &= ~CSn_PIN;
  Wait(30);
  CSn_PxOUT |= CSn_PIN;
  Wait(45);

  CSn_PxOUT &= ~CSn_PIN;
  while (SPI_BITBANG_PxIN&SPI_BITBANG_SOMI);
  SPI_bitbang_out(SRES);
  while (SPI_BITBANG_PxIN&SPI_BITBANG_SOMI);
  CSn_PxOUT |= CSn_PIN;
}
#endif



