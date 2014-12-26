/**
 *  @file   FlashModule.h
 *
 *  @brief  
 */
#ifndef __MCU_MSP430_FLASHMODULE_H
#define __MCU_MSP430_FLASHMODULE_H

#include "../../../Config.h"

#ifdef __MCU_MSP430_FLASHMODULE

/**
 *  @fn     FlashModuleUnlock
 *
 *  @brief  Enables read/write capabilities with the Flash module. If the flash 
 *          is not unlocked before an operation on it is performed, a reset will 
 *          occur.
 */
#define __hal_FlashModuleUnlock()                 FCTL3 = FWKEY;

/**
 *  @fn     FlashModuleLock
 *
 *  @brief  Disables read/write capabilities with the Flash module.
 */
#define __hal_FlashModuleLock()                   FCTL3 = FWKEY | LOCK;

/**
 *  @fn     FlashWriteByte
 *
 *  @brief  Write a single byte to an address in flash.
 */
#define __hal_FlashModuleWriteByte(address, value)  \
{                                             \
  FCTL1 = FWKEY | WRT;                        \
  *address = value;                           \
}

/**
 *  @fn   FlashErase
 */
#define __hal_FlashModuleErase(address)     \
{                                           \
  FCTL1 = FWKEY | ERASE;                    \
  *address = 0;                             \
}

/**
 *  @fn   FlashModuleWriteBuffer
 */
#ifdef USE_INLINE
#pragma inline
void __hal_FlashModuleWriteBuffer(volatile unsigned int pBaseAddress, volatile unsigned int pStorage, volatile unsigned char * pAddress, unsigned char * pBuffer, unsigned char count)
{
  unsigned char segmentIndex;
  unsigned char bufferIndex = (pAddress - pBaseAddress) % 64;
  unsigned char i;
  
  // Unlock flash module for read/write capabilities.
  __hal_FlashModuleUnlock();
  
  // Erase the swap storage flash segment.
  __hal_FlashModuleErase(pStorage);
  
  // Store all buffer values into segment 2 for swap storage.
  for (segmentIndex = 0; segmentIndex < 64; segmentIndex++)
  {
    __hal_FlashModuleWriteByte((pStorage+segmentIndex), *(pAddress - bufferIndex + segmentIndex));
  }
  
  // Check if flash should be erased. If flash contains a value that prohibits
  // writing the new value, such as writing 0 to a 1, we need to erase the entire 
  // segment.
  for (i = 0; i < count; i++)
  {
    if ((*(pAddress - bufferIndex + i) & pBuffer[i]) != pBuffer[i])
    {
      // If the check has failed, erase the segment.
       __hal_FlashModuleErase(pAddress);
       break;
    }
  }

  // Clear buffer index variable.
  i = 0;
  
  // Perform the swap and write buffer data to the segment.
  for (segmentIndex = 0; segmentIndex < 64; segmentIndex++)
  {
    // Write buffer data to segment 1.
    if (segmentIndex >= bufferIndex && segmentIndex < bufferIndex + count)
    {
      __hal_FlashModuleWriteByte((pAddress - bufferIndex + segmentIndex), pBuffer[i]);
      
      if (i < count)
      {
        i++;
      }
    }
    else
    {
      // Write segment 2 data that was already stored in flash before operation.
      __hal_FlashModuleWriteByte((pAddress - bufferIndex + segmentIndex), pStorage[segmentIndex]);
    }
  }
  
  // Lock flash when done for cleanup.
  __hal_FlashModuleLock();
}
#else
void __hal_FlashModuleWriteBuffer(volatile unsigned char * pBaseAddress, volatile unsigned char * pStorage, volatile unsigned char * pAddress, unsigned char * pBuffer, unsigned char count);
#endif

#ifdef USE_INLINE
#pragma inline
void __hal_FlashModuleRAMWriteBuffer(volatile unsigned char * pBaseAddress, volatile unsigned char * pAddress, unsigned char * pBuffer, unsigned char count)
{
  unsigned char segmentIndex;
  unsigned char flag = 0; 
  unsigned char bufferIndex = ((unsigned int)pAddress - (unsigned int)pBaseAddress) % 64;  // Get the index of the address within the flash segment
  unsigned char flashedData[64];
  unsigned char i;
  
  // Unlock flash module for read/write capabilities.
  __hal_FlashModuleUnlock();
  
  for (segmentIndex = 0; segmentIndex < 64; segmentIndex++)
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
  
  for (segmentIndex = 0; segmentIndex < 64; segmentIndex++)
  {
    __hal_FlashModuleWriteByte((pAddress - bufferIndex + segmentIndex), flashedData[segmentIndex]); // Write the entire buffer back into flash
  }
  
  // Lock flash when done for cleanup.
  __hal_FlashModuleLock();
}
#else
void __hal_FlashModuleRAMWriteBuffer(volatile unsigned char * pBaseAddress, volatile unsigned char * pAddress, unsigned char * pBuffer, unsigned char count);
#endif

#endif

#endif  // __MCU_MSP430_FLASHMODULE_H
