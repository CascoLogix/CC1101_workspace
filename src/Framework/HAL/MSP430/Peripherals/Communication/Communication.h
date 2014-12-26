/**
 *  @file   Communication.h
 */
#ifndef __HAL_MSP430_COMMUNICATION_H
#define __HAL_MSP430_COMMUNICATION_H

#include "../../Config.h"

/**
 *  @typedef
 */
typedef const struct hUARTConnection
{
  Connection txd;                           //!< Transmit data connection
  Connection rxd;                           //!< Receive data connection
} hUARTConnection;

/**
 *  @typedef
 */
typedef const struct SPIChipSelect
{
  Connection connection;
  enum POLARITY polarity;
} SPIChipSelect;

/**
 *  @typedef
 */
typedef const struct SPIConnection
{
  SPIChipSelect csn;                        //!< Chip select connection
  //Connection mosi;                          //!< Master-out/slave-in connection
  //Connection miso;                          //!< Master-in/slave-out connection
  //Connection sclk;                          //!< Slave clock connection
} SPIConnection;

// NOTE: THIS SECTION NEEDS CLEANUP!!!!
//#define ROUND(X) ((X) >= 0 ? (long)((X) + 0.5) : (long)((X) - 0.5))
#define CEIL(VARIABLE)  ( (VARIABLE - (int)VARIABLE)==0 ? (int)VARIABLE : (int)VARIABLE+1 )
#define ROUND(x)        ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

// Low-frequency baud rate mode setting
#define CalculateLowFrequencyUARTBaudrateDivFactor(clockRate, baud)   ((clockRate * 1.0) / (baud * 1.0))
#define CalculateLowFrequencyUARTBaudrate(clockRate, baud)            (unsigned int)CalculateLowFrequencyUARTBaudrateDivFactor(clockRate, baud)
#define CalculateLowFrequencyUARTModulation(clockRate, baud)          (ROUND((CalculateLowFrequencyUARTBaudrateDivFactor(clockRate, baud) - (unsigned int)CalculateLowFrequencyUARTBaudrateDivFactor(clockRate, baud)) * 8) << 1)

// Oversampling baud rate mode setting
#define CalculateOversamplingUARTBaudrateDivFactor(clockRate, baud)   (((clockRate * 1.0) / (baud * 1.0)) / 16)
#define CalculateOversamplingUARTBaudrate(clockRate, baud)            (unsigned int)CalculateOversamplingUARTBaudrateDivFactor(clockRate, baud)
#define CalculateOversamplingUARTModulation(clockRate, baud)          (ROUND(((CalculateLowFrequencyUARTBaudrateDivFactor(clockRate, baud) / 16) - (unsigned int)(CalculateLowFrequencyUARTBaudrateDivFactor(clockRate, baud) / 16)) * 16) << 4)

#define CalculateUARTBaudrate(clockRate, baud)                        ((CalculateLowFrequencyUARTBaudrateDivFactor(clockRate, baud)) < 16) ? CalculateLowFrequencyUARTBaudrate(clockRate, baud) : CalculateOversamplingUARTBaudrate(clockRate, baud)
#define CalculateUARTModulation(clockRate, baud)                      ((CalculateLowFrequencyUARTBaudrateDivFactor(clockRate, baud)) < 16) ? (CalculateLowFrequencyUARTModulation(clockRate, baud)) : (UCOS16 | (CalculateOversamplingUARTModulation(clockRate, baud)))

/**
 *  @fn   __hal_UARTConfigure
 */
#define __hal_UARTConfigure(peripheral, clockRate, clockSource, baud, data, parity, stop) \
{                                                                                   \
  if (peripheral == USCIA0)                                                         \
  {                                                                                 \
    UCA0CTL1 |= UCSWRST;                                                            \
    if (parity == UART_PARITY_EVEN)                                                 \
      UCA0CTL0 |= UCPEN | UCPAR;                                                    \
    else if (parity == UART_PARITY_ODD)                                             \
      UCA0CTL0 |= UCPEN;                                                            \
    else                                                                            \
      UCA0CTL0 &= ~UCPEN;                                                           \
    if (data == UART_DATA_7BITS)                                                    \
      UCA0CTL0 |= UC7BIT;                                                           \
    else                                                                            \
      UCA0CTL0 &= ~UC7BIT;                                                          \
    if (stop == UART_STOP_2BITS)                                                    \
      UCA0CTL0 |= UCSPB;                                                            \
    else                                                                            \
      UCA0CTL0 &= ~UCSPB;                                                           \
    UCA0BR1 = CalculateUARTBaudrate(clockRate, baud) >> 8;                          \
    UCA0BR0 = CalculateUARTBaudrate(clockRate, baud) & 0xFF;                        \
    UCA0MCTL = CalculateUARTModulation(clockRate, baud);                            \
    UCA0CTL1 |= clockSource;                                                        \
    UCA0CTL1 &= ~UCSWRST;                                                           \
    IE2 |= UCA0RXIE;                                                                \
    IE2 &= ~UCA0TXIE;                                                               \
  }                                                                                 \
}                                                                                   \

/**
 *  @fn   __hal_UARTTransmitByte
 */
signed char __hal_UARTTransmitByte(enum PERIPHERAL peripheral, unsigned char value);
//#pragma inline
//signed char __hal_UARTTransmitByte(enum PERIPHERAL peripheral, unsigned char value)
//{
//  unsigned char isFull = -1;
//  // If USCI is defined, include the following code.
//  #if defined(__MCU_MSP430_USCI)
//  // Check if we are using the USCIA0 peripheral.
//  if (peripheral == USCIA0)
//  {
//    // Write value to transmit circular buffer.
//    isFull = CircularBufferWrite(&USCIA0Buffer.tx, value);
//    
//    // If the a byte was copied successfully, initiate a transmission sequence.
//    if (!isFull)
//    {
//      // Increment USCIA0 TX buffer count.
//      USCIA0Buffer.count++;
//
//      if (!CircularBufferIsEmpty(&USCIA0Buffer.tx))
//      {
//        if(USCIA0Buffer.state != IN_PROGRESS)
//        {
//          // Set state.
//          USCIA0Buffer.state = IN_PROGRESS;
//          
//          // Set USCIA0 TX interrupt enable to start transmission sequence.
//          IE2 |= UCA0TXIE;
//        }
//      }
//    }
//  }
//  #endif
//  
//  return isFull;
//}

/**
 *  @fn   __hal_UARTReceiveByte
 */
signed char __hal_UARTReceiveByte(enum PERIPHERAL peripheral, unsigned char * readValue);
//#pragma inline
//signed char __hal_UARTReceiveByte(enum PERIPHERAL peripheral, unsigned char * readValue)
//{
//  // If USCI is defined, include the following code.
//  #if defined(__MCU_MSP430_USCI)
//  // Check if we are using the USCIA0 peripheral.
//  if (peripheral == USCIA0)
//  {
//    // Read value from receive circular buffer.
//    return CircularBufferRead(&USCIA0Buffer.rx, readValue);
//  }
//  #endif
//  
//  // NOTE: This return statement should never be reached. If it is, return that 
//  // the read was unsuccessful as an unknown event has occurred.
//  return 0;
//}

/**
 *  @fn   __hal_UARTBusy
 */
signed char __hal_UARTBusy(enum PERIPHERAL peripheral);

/**
 *  @fn   SPIConfigure
 */
#define __hal_SPIConfigure(peripheral, mode, clockPhase, clockPolarity, clockSource, clockDivider)  \
{                                                                                                   \
  if (peripheral == USCIA0)                                                                         \
  {                                                                                                 \
    UCA0CTL1 |= UCSWRST;                                                                            \
    UCA0CTL0 |= (mode | clockPhase | clockPolarity | UCMSB | UCMST | UCSYNC);                       \
    UCA0CTL1 |= clockSource;                                                                        \
    UCA0BR1 = (clockDivider >> 8);                                                                  \
    UCA0BR0 = (clockDivider && 0xFF);                                                               \
    UCA0CTL1 &= ~UCSWRST;                                                                           \
    __hal_SPIDisableUSCIA0Interrupts();                                                             \
  }                                                                                                 \
  else if (peripheral == USCIB0)                                                                    \
  {                                                                                                 \
    UCB0CTL1 |= UCSWRST;                                                                            \
    UCB0CTL0 |= (mode | clockPhase | clockPolarity | UCMSB | UCMST | UCSYNC);                       \
    UCB0CTL1 |= clockSource;                                                                        \
    UCB0BR1 = (clockDivider >> 8);                                                                  \
    UCB0BR0 = (clockDivider && 0xFF);                                                               \
    UCB0CTL1 &= ~UCSWRST;                                                                           \
    __hal_SPIDisableUSCIB0Interrupts();                                                             \
  }                                                                                                 \
}                                                                                                   \

#if defined(UCB0TXIE)
#define __hal_SPIDisableUSCIA0Interrupts()    {IE2 &= ~UCA0TXIE; IE2 &= ~UCA0RXIE;}
#elif defined(UCB0IE)
#define __hal_SPIDisableUSCIA0Interrupts()    {UCA0IE &= ~UCTXIE; UCA0IE &= ~UCRXIE;}
#endif

#if defined(UCB0TXIE)
#define __hal_SPIDisableUSCIB0Interrupts()    {IE2 &= ~UCB0TXIE; IE2 &= ~UCB0RXIE;}
#elif defined(UCB0IE)
#define __hal_SPIDisableUSCIB0Interrupts()    {UCB0IE &= ~UCTXIE; UCB0IE &= ~UCRXIE;}
#endif

/**
 *  @fn   __hal_SPIEnableChipSelect
 */
#ifdef USE_INLINE
#pragma inline
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
#else
void __hal_SPIEnableChipSelect(SPIChipSelect * csn);
#endif

/**
 *  @fn   __hal_SPIDisableChipSelect
 */
#ifdef USE_INLINE
#pragma inline
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
#else
void __hal_SPIDisableChipSelect(SPIChipSelect * csn);
#endif

/**
 *  @fn   __hal_SPISingleWrite
 */
void __hal_SPISingleWrite(enum PERIPHERAL peripheral, SPIConnection * spi, unsigned char address, unsigned char data);

/**
 *  @fn   __hal_SPIBurstWrite
 */
void __hal_SPIBurstWrite(enum PERIPHERAL peripheral, SPIConnection * spi, unsigned char address, unsigned char * pBuffer, unsigned char count);

/**
 *  @fn   __hal_SPISingleRead
 */
unsigned char __hal_SPISingleRead(enum PERIPHERAL peripheral, SPIConnection * spi, unsigned char address);

/**
 *  @fn   __hal_SPIBurstRead
 */
void __hal_SPIBurstRead(enum PERIPHERAL peripheral, SPIConnection * spi, unsigned char address, unsigned char * pBuffer, unsigned char count);


#endif  // __HAL_MSP430_COMMUNICATION_H
