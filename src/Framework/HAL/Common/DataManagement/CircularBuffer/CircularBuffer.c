#include "CircularBuffer.h"

#ifndef USE_INLINE

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

unsigned char CircularBufferIsEmpty(CircularBuffer * pCircularBuffer)
{
  return (pCircularBuffer->pWrite == pCircularBuffer->pRead);
}

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

#endif
