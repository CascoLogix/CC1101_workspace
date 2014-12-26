/**
 *  @file   Flash.h
 */
#ifndef __DRIVER_FLASH_H
#define __DRIVER_FLASH_H

#include "../../BSP/BoardDrivers.h"

/**
 *  @fn     FlashErase
 *
 *  @brief  Erase a segment in flash memory.
 */
#define FlashErase(segmentAddress)          __BSP_FLASH_ERASE(segmentAddress)

/**
 *  @fn     FlashWriteByte
 *
 *  @brief  Writes a single byte to a flash segment. 
 *
 *  @note   An entire segment will be erased when using this operation. To retain 
 *          the segment data, use FlashWriteBuffer.
 */
#define FlashWriteByte(address, data)     __BSP_FLASH_WRITE_BYTE(address, data)

/**
 *  @fn     FlashWriteBuffer
 *
 *  @brief  Writes a buffer of bytes to a flash segment. Retains all data stored
 *          in flash segment that isn't being written to.
 */
#define FlashWriteBuffer(address, buffer, count)    \
{                                                   \
  __BSP_FLASH_WRITE_BUFFER(address, buffer, count); \
}

#endif  // __DRIVER_FLASH_H
