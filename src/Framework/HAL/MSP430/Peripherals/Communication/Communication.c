/**
 *  @file   Communication.c
 */
#include "Communication.h"

/**
 *  @details  
 */
signed char __hal_UARTTransmitByte(enum PERIPHERAL peripheral, unsigned char value)
{
  signed char isFull = -1;
  // If USCI is defined, include the following code.
  #if defined(__MCU_MSP430_USCI)
  // Check if we are using the USCIA0 peripheral.
  if (peripheral == USCIA0)
  {
    // Write value to transmit circular buffer.
    isFull = CircularBufferWrite(&USCIA0Buffer.tx, value);
    
    // If the a byte was copied successfully, initiate a transmission sequence.
    if (!isFull)
    {
      // Increment USCIA0 TX buffer count.
      USCIA0Buffer.count++;

      if (!CircularBufferIsEmpty(&USCIA0Buffer.tx))
      {
        if(USCIA0Buffer.state != IN_PROGRESS)
        {
          // Set state.
          USCIA0Buffer.state = IN_PROGRESS;
          
          // Set USCIA0 TX interrupt enable to start transmission sequence.
          #if defined(UCA0TXIE)
          IE2 |= UCA0TXIE;
          #elif defined(UCA0IE)
          UCA0IE |= UCTXIE;
          #endif
        }
      }
    }
  }
  #endif
  
  return isFull;
}

/**
 *  @details
 */
signed char __hal_UARTReceiveByte(enum PERIPHERAL peripheral, unsigned char * readValue)
{
  // If USCI is defined, include the following code.
  #if defined(__MCU_MSP430_USCI)
  // Check if we are using the USCIA0 peripheral.
  if (peripheral == USCIA0)
  {
    // Read value from receive circular buffer.
    return CircularBufferRead(&USCIA0Buffer.rx, readValue);
  }
  #endif
  
  // NOTE: This return statement should never be reached. If it is, return that 
  // the read was unsuccessful as an unknown event has occurred.
  return 0;
}

/**
 *	@details
 */
signed char __hal_UARTBusy(enum PERIPHERAL peripheral)
{
  #if defined(__MCU_MSP430_USCI)
  if (peripheral == USCIA0)
  {
    // Check if the UART hardware is configured for UART.
    if (!(UCA0CTL0 && UCSYNC))
    {
      // We only care about the TX buffer being busy. The RX buffer will need to
      // be handled by the application when data comes in. TX is triggered by the
      // application and may wish to wait until the operation completes. This
      // would allow for a blocking implementation.
      return !CircularBufferIsEmpty(&USCIA0Buffer.tx);
    }
  }
  #endif
  
  // Incorrect peripheral provided or none supported.
  return -1;
}

#ifndef USE_INLINE

void __hal_SPIEnableChipSelect(SPIChipSelect * csn)
{
  // Verify the polarity of the csn pin.
  if (csn->polarity == ACTIVE_LOW)
  {
    // Chip select is active high, set it to enable.
    ClearDigitalIOOutputPort(csn->connection.port, csn->connection.pin);
  }
  else  // ACTIVE_HIGH
  {
    // Chip select is active low, clear it to enable.
    SetDigitalIOOutputPort(csn->connection.port, csn->connection.pin);
  }
}

void __hal_SPIDisableChipSelect(SPIChipSelect * csn)
{
  // Verify the polarity of the csn pin.
  if (csn->polarity == ACTIVE_LOW)
  {
    // Chip select is active high, clear it to disable.
    SetDigitalIOOutputPort(csn->connection.port, csn->connection.pin);
  }
  else  // ACTIVE_HIGH
  {
    // Chip select is active low, set it to disable.
    ClearDigitalIOOutputPort(csn->connection.port, csn->connection.pin);
  }
}

#endif

/**
 *  \details  SPI write will look to see which peripherals are defined and then
 *            check the peripheral passed in to perform the correct operation.
 *            The SPI operation is ALWAYS BLOCKING.
 */
void __hal_SPISingleWrite(enum PERIPHERAL peripheral, SPIConnection * spi, unsigned char address, unsigned char data)
{
  unsigned char buffer[] = {0};
  
  buffer[0] = data;
  
  __hal_SPIBurstWrite(peripheral, spi, address, buffer, sizeof(buffer));
}

/**
 *  \details  SPI write with buffer capabilities takes in a user buffer and count
 *            to iterate through the data to be passed across the serial lines.
 *            It selects the appropriate implementation based on the peripheral
 *            that is performing the SPI operation. The function performs a
 *            rudimentary check to see if the peripheral is capable of SPI based
 *            on the implementations defined below. This implementation of SPI is
 *            ALWAYS BLOCKING.
 */
void __hal_SPIBurstWrite(enum PERIPHERAL peripheral, SPIConnection * spi, unsigned char address, unsigned char * pBuffer, unsigned char count)
{
  /**
   *  USCI Implementation
   *
   *  This portion of the function defines the SPI write implementation for
   *  MSP430 USCI peripherals. This includes USCIAx and USCIBx.
   */
  #if defined(__MCU_MSP430_USCI)
  
  unsigned char i;                          // Buffer loop counter

  #if defined(__MCU_MSP430_USCIA0)
  // Check if we are using the USCIA0 peripheral.
  if (peripheral == USCIA0)
  {
    // Check if USCIA0 is in SPI operation.
    if (UCA0CTL0 & UCSYNC)
    {
      // Enable chip select.
      __hal_SPIEnableChipSelect(&spi->csn);
      
        UCA0TXBUF = address;
        #if defined(UCA0TXIFG)
        while (!(IFG2 & UCA0TXIFG));
        #elif defined(UCA0IFG)
        while (!(UCA0IFG & UCTXIFG));
        #endif
      
      // Perform SPI write.
      for (i = 0; i < count; i++)
      {
        UCA0TXBUF = pBuffer[i];
        // NOTE: If the processor is running faster than the SPI clock, you must
        // use the following instruction for safe operation. Otherwise, you risk
        // overwriting data in the transmit shift register.
        #if defined(UCA0TXIFG)
        while (!(IFG2 & UCA0TXIFG));
        #elif defined(UCA0IFG)
        while (!(UCA0IFG & UCTXIFG));
        #endif
      }
       
      // Halt program execution until TX complete.
      while(UCA0STAT & UCBUSY);
      
      // Disable chip select.
      __hal_SPIDisableChipSelect(&spi->csn);
    }
  }
  #endif  // USCIA0 Module

  #if defined(__MCU_MSP430_USCIB0)
  // Check if we are using the USCIB0 peripheral.
  if (peripheral == USCIB0)
  {
    // Check if USCIB0 is in SPI operation.
    if (UCB0CTL0 & UCSYNC)
    {
      // Enable chip select.
      __hal_SPIEnableChipSelect(&spi->csn);
      
      UCB0TXBUF = address;
      #if defined(UCB0TXIFG)
      while (!(IFG2 & UCB0TXIFG));
      #elif defined(UCB0IFG)
      while (!(UCB0IFG & UCTXIFG));
      #endif

      // Perform SPI write.
      // NOTE: The following for loop will be replaced with an assembly variant.
      for (i = 0; i < count; i++)
      {
        UCB0TXBUF = pBuffer[i];
        // NOTE: If the processor is running faster than the SPI clock, you must
        // use the following instruction for safe operation. Otherwise, you risk
        // overwriting data in the transmit shift register.
        #if defined(UCB0TXIFG)
        while (!(IFG2 & UCB0TXIFG));
        #elif defined(UCB0IFG)
        while (!(UCB0IFG & UCTXIFG));
        #endif
      }
      
      // Halt program execution until TX complete.
      while(UCB0STAT & UCBUSY);
      
      // Enable chip select.
      __hal_SPIDisableChipSelect(&spi->csn);
    }
  }
  #endif  // USCIB0 Module
  
  #endif  // USCI Module
}

/**
 *  \details
 */
unsigned char __hal_SPISingleRead(enum PERIPHERAL peripheral, SPIConnection * spi, unsigned char address)
{
  unsigned char buffer[] = {0xFF};
  
  __hal_SPIBurstRead(peripheral, spi, address, buffer, sizeof(buffer));

  return buffer[1];
}

/**
 *  \details
 */
void __hal_SPIBurstRead(enum PERIPHERAL peripheral, SPIConnection * spi, unsigned char address, unsigned char * pBuffer, unsigned char count)
{
  // If USCI is defined, include the following code.
  #if defined(__MCU_MSP430_USCI)
  unsigned char i;                          // Buffer loop counter

  // Check if we are using the USCIA0 peripheral.
  if (peripheral == USCIA0)
  {
    // Check if USCIA0 is in SPI operation.
    if (UCA0CTL0 & UCSYNC)
    {
      // Enable chip select.
      __hal_SPIEnableChipSelect(&spi->csn);
      
      UCA0TXBUF = address;
      #if defined(UCA0TXIFG)
      while (!(IFG2 & UCA0TXIFG));
      #elif defined(UCA0IFG)
      while (!(UCA0IFG & UCTXIFG));
      #endif
      
      // Perform SPI write loop to get valid data.
      for (i = 0; i < count; i++)
      {
        UCA0TXBUF = pBuffer[i];
        // NOTE: If the processor is running faster than the SPI clock, you must
        // use the following instruction for safe operation. Otherwise, you risk
        // overwriting data in the transmit shift register.
        #if defined(UCA0TXIFG)
        while (!(IFG2 & UCA0TXIFG));
        #elif defined(UCA0IFG)
        while (!(UCA0IFG & UCTXIFG));
        #endif

        // Read the value returned after the dummy write.
        pBuffer[i] = UCA0RXBUF;
      }
      
      // Halt program execution until TX complete.
      while(UCA0STAT & UCBUSY);             // Wait for TX to complete

      // Disable chip select.
      __hal_SPIDisableChipSelect(&spi->csn);
    }
  }
  // Check if we are using the USCIB0 peripheral.
  if (peripheral == USCIB0)
  {
    // Check if USCIB0 is in SPI operation.
    if (UCB0CTL0 & UCSYNC)
    {
      // Enable chip select.
      __hal_SPIEnableChipSelect(&spi->csn);
      
      UCB0TXBUF = address;
      #if defined(UCB0TXIFG)
      while (!(IFG2 & UCB0TXIFG));
      #elif defined(UCB0IFG)
      while (!(UCB0IFG & UCTXIFG));
      #endif
      
      // Perform SPI write.
      for (i = 0; i < count; i++)
      {
        UCB0TXBUF = pBuffer[i];
        // NOTE: If the processor is running faster than the SPI clock, you must
        // use the following instruction for safe operation. Otherwise, you risk
        // overwriting data in the transmit shift register.
        #if defined(UCB0TXIFG)
        while (!(IFG2 & UCB0TXIFG));
        #elif defined(UCB0IFG)
        while (!(UCB0IFG & UCTXIFG));
        #endif
        
        // Read the value returned after the dummy write.
        pBuffer[i] = UCB0RXBUF;
      }
      
      // Halt program execution until TX complete.
      while(UCB0STAT & UCBUSY);             // Wait for TX to complete

      // Enable chip select.
      __hal_SPIDisableChipSelect(&spi->csn);
    }
  }
  #endif
}
