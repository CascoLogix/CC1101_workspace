/**
 *  @file   FlashModule.c
 */
#include "FlashModule.h"

#if defined(__MCU_MSP430_FLASHMODULE)

#ifndef USE_INLINE

void __hal_FlashModuleWriteBuffer(volatile unsigned char * pBaseAddress, volatile unsigned char * pStorage, volatile unsigned char * pAddress, unsigned char * pBuffer, unsigned char count)
{
  unsigned char segmentIndex;
  unsigned char bufferIndex = ((unsigned int)pAddress - (unsigned int)pBaseAddress) % 64;
  unsigned char i;


  // Unlock flash module for read/write capabilities.
  __hal_FlashModuleUnlock();

  // Erase the swap storage flash segment.
  __hal_FlashModuleErase(pStorage);
  
  // Copy all segment values into swap storage location.
  for (segmentIndex = 0; segmentIndex < 64; segmentIndex++)
  {
    __hal_FlashModuleWriteByte((pStorage+segmentIndex), *(pAddress - bufferIndex + segmentIndex));
  }
  
  // Erase the segment.
   __hal_FlashModuleErase(pAddress);

  // Clear buffer index variable.
  i = 0;

  // Perform the swap and write buffer data to the segment.
  for (segmentIndex = 0; segmentIndex < 64; segmentIndex++)
  {
    // Write buffer data to segment.
    if (segmentIndex >= bufferIndex && segmentIndex < bufferIndex + count)
    {
      __hal_FlashModuleWriteByte((pAddress - bufferIndex + segmentIndex), pBuffer[i++]);
    }
    else
    {
      // Write segment data that was already stored in flash before operation.
      __hal_FlashModuleWriteByte((pAddress - bufferIndex + segmentIndex), pStorage[segmentIndex]);
    }
  }
  
  // Lock flash when done for cleanup.
  __hal_FlashModuleLock();
}

void __hal_FlashModuleRAMWriteBuffer(volatile unsigned char * pBaseAddress, volatile unsigned char * pAddress, unsigned char * pBuffer, unsigned char count)
{
  unsigned char segmentIndex;
  unsigned char flag = 0; 
  unsigned char bufferIndex = ((unsigned int)pAddress - (unsigned int)pBaseAddress) % 64;  // Get the index of the address within the flash segment
  unsigned char flashedData[64];
  unsigned char i;

  // Unlock flash module for read/write capabilities.
  __hal_FlashModuleUnlock();
  
  for (segmentIndex = 0; segmentIndex < sizeof(flashedData); segmentIndex++)
  {
    flashedData[segmentIndex] = *(pAddress - bufferIndex + segmentIndex);    // Store all values in segment into buffer
  }
  
  for (i = 0; i < count; i++)
  {
    flashedData[bufferIndex + i] = pBuffer[i];                                 // Rewrite the buffer location specified by index with the desire value
    if ((*(pAddress - bufferIndex + i) & pBuffer[i]) != pBuffer[i])
    {
       flag = 1;
    }
  }
  
  if (flag == 1)
  {
    __hal_FlashModuleErase(pAddress);                          // Erase the flash segment
  }
  
  for (segmentIndex = 0; segmentIndex < sizeof(flashedData); segmentIndex++)
  {
    __hal_FlashModuleWriteByte((pAddress - bufferIndex + segmentIndex), flashedData[segmentIndex]); // Write the entire buffer back into flash
  }
  
  // Lock flash when done for cleanup.
  __hal_FlashModuleLock();
}

#endif

#endif  // FLASHMODULE
