/**
 *  @file   SPI.h
 */
#ifndef __DRIVER_SPI_H
#define __DRIVER_SPI_H

#include "../../BSP/BoardDrivers.h"

/**
 *  @fn     SPIConfigure
 *
 *  @brief  Setup SPI hardware.
 */
#define SPIConfigure(spiId)                           __BSP_SPI_CONFIGURATION(spiId)

/**
 *  @fn     SPISingleWrite
 */
#define SPISingleWrite(spiId, address, data)          __BSP_SPI_SINGLE_WRITE(spiId, address, data)

/**
 *  @fn     SPIBurstWrite
 */
#define SPIBurstWrite(spiId, address, buffer, count)  __BSP_SPI_BURST_WRITE(spiId, address, buffer, count)

/**
 *  @fn     SPISingleRead
 */
#define SPISingleRead(spiId, address)                 __BSP_SPI_SINGLE_READ(spiId, address)

/**
 *  @fn     SPIBurstRead
 */
#define SPIBurstRead(spiId, address, buffer, count)   __BSP_SPI_BURST_READ(spiId, address, buffer, count)

#endif  // __DRIVER_SPI_H
