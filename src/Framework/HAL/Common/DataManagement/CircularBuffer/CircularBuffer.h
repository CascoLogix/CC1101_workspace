/**
 *  \file   CircularBuffer.h
 *
 *  \brief    A circular buffer. Allows for buffering a stream of data.
 *
 *  \details  This implementation of a circular buffer uses the "Keep One Slot
 *            Open" method to prevent overfilling the buffer. It will not write 
 *            over valid data as it prevents pushing more than available in.
 */
#ifndef __HAL_COMMON_CIRCULARBUFFER_H
#define __HAL_COMMON_CIRCULARBUFFER_H

#include "intrinsics.h"

#if defined(__IAR_SYSTEMS_ICC__)
  #if defined(__MCU_MSP430_SERIES)
  #define ISTATE                            istate_t
  #elif defined(__MCU_CC8051_SERIES)
  #define ISTATE                            __istate_t
  #else
  #define ISTATE                            unsigned short
  #endif
#else
  #define ISTATE			    unsigned short
#endif

/**
 *  \enum   CIRCULAR_BUFFER_OPERATION
 */
enum CIRCULAR_BUFFER_OPERATION
{
  NO_OPERATION    = 0,                      //!< Circular buffer not operating
  IN_PROGRESS     = 1,                      //!< Circular buffer currently performing operation
  DONE            = 2                       //!< Circular buffer operation complete
};

/**
 *  \typedef  CircularBuffer
 */
typedef struct CircularBuffer
{
  unsigned char * pBuffer;                  //!< Pointer to start of buffer
  unsigned char * pBufferEnd;               //!< Pointer to end of buffer
  unsigned char * pWrite;                   //!< Pointer to write position in buffer
  unsigned char * pRead;                    //!< Pointer to read position in buffer
  unsigned char size;                       //!< Size of the buffer
} CircularBuffer;

/**
 *  \fn   CircularBufferIsFull
 */
#ifdef USE_INLINE
#pragma inline
unsigned char CircularBufferIsFull(CircularBuffer * pCircularBuffer)
{
  // Check if incrementing the write pointer by 1 causes a rollover to start.
  if ((pCircularBuffer->pWrite) < (pCircularBuffer->pBufferEnd))
  {
    // If pWrite + 1 and pRead are equal, the buffer is full.
    return ((pCircularBuffer->pWrite + 1) == pCircularBuffer->pRead);
  }
  else
  {
    // If a rollover occurs, we can use pBuffer in place of pWrite for the
    // comparison. If pBuffer and pRead are the same, the buffer is full.
    return (pCircularBuffer->pBuffer == pCircularBuffer->pRead);
  }
}
#else
unsigned char CircularBufferIsFull(CircularBuffer * pCircularBuffer);
#endif

/**
 *  \fn CircularBufferIsEmpty
 */
#ifdef USE_INLINE
#pragma inline
unsigned char CircularBufferIsEmpty(CircularBuffer * pCircularBuffer)
{
  return (pCircularBuffer->pWrite == pCircularBuffer->pRead);
}
#else
unsigned char CircularBufferIsEmpty(CircularBuffer * pCircularBuffer);
#endif

/**
 *  \fn   CircularBufferPointerManipulation
 */
#ifdef USE_INLINE
#pragma inline
void CircularBufferPointerManipulation(CircularBuffer * pCircularBuffer, unsigned char ** ptr)
{
  // Compare the current ptr offset position to the buffer start.
  if (*(ptr) < (pCircularBuffer->pBuffer + (pCircularBuffer->size - 1)))
  {
    // If the pointer address is less than the buffer start address + size of
    // the buffer, increment the pointer.
    *(ptr) = *(ptr) + 1;
  }
  else
  {
    // If the pointer reaches the end, set it back to the beginning.
    *(ptr) = pCircularBuffer->pBuffer;
  }
}
#else
void CircularBufferPointerManipulation(CircularBuffer * pCircularBuffer, unsigned char ** ptr);
#endif

/**
 *  \fn   CircularBufferWrite
 */
#ifdef USE_INLINE
#pragma inline
unsigned char CircularBufferWrite(CircularBuffer * pCircularBuffer, unsigned char value)
{
  ISTATE state = __get_interrupt_state();
  __disable_interrupt();
 
  unsigned char isFull = CircularBufferIsFull(pCircularBuffer);
  
  // Verify that there is free space available to write data.
  if (!isFull)
  {
    // Write value at current write pointer position.
    *(pCircularBuffer->pWrite) = value;
  
    // Manipulate pointers.
    // Compare the current ptr offset position to the buffer start.
    if (pCircularBuffer->pWrite < pCircularBuffer->pBufferEnd)
    {
      // If the pointer address is less than the buffer start address + size of
      // the buffer, increment the pointer.
      pCircularBuffer->pWrite = pCircularBuffer->pWrite + 1;
    }
    else
    {
      // If the pointer reaches the end, set it back to the beginning.
      pCircularBuffer->pWrite = pCircularBuffer->pBuffer;
    }
  }

  __set_interrupt_state(state);
  
  return isFull;
}
#else
unsigned char CircularBufferWrite(CircularBuffer * pCircularBuffer, unsigned char value);
#endif

/**
 *  \fn   CircularBufferRead
 */
#ifdef USE_INLINE
#pragma inline
unsigned char CircularBufferRead(CircularBuffer * pCircularBuffer, unsigned char * readValue)
{    
  ISTATE state = __get_interrupt_state();
  __disable_interrupt();
  
  unsigned char isEmpty = CircularBufferIsEmpty(pCircularBuffer);

  // Verify that there is data to read.
  if (!isEmpty)
  {
    // Read current value at current read pointer position.
    *(readValue) = *(pCircularBuffer->pRead);
  
    // Manipulate pointers.
    // Compare the current ptr offset position to the buffer start.
    if (pCircularBuffer->pRead < pCircularBuffer->pBufferEnd)
    {
      // If the pointer address is less than the buffer start address + size of
      // the buffer, increment the pointer.
      pCircularBuffer->pRead = pCircularBuffer->pRead + 1;
    }
    else
    {
      // If the pointer reaches the end, set it back to the beginning.
      pCircularBuffer->pRead = pCircularBuffer->pBuffer;
    }
  }

  __set_interrupt_state(state);
  
  return isEmpty;
}
#else
unsigned char CircularBufferRead(CircularBuffer * pCircularBuffer, unsigned char * readValue);
#endif

#endif  // __HAL_COMMON_CIRCULARBUFFER_H
