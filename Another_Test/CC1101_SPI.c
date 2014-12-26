/*****************************************************************************/
//	CC1101_SPI.c
//  
//	 Created on: Dec 22, 2014
//	     Author: Clint Stevenson
//
/*****************************************************************************/


/*****************************************************************************/
//	Includes
/*****************************************************************************/
#include <CC1101_SPI.h>
/*****************************************************************************/
//	End Includes


/*****************************************************************************/
//	Defines
/*****************************************************************************/
//Put defines here
/*****************************************************************************/
//	End Defines


/*****************************************************************************/
//	Constant Declarations
/*****************************************************************************/
//Put Constant Declarations here
/*****************************************************************************/
//	End Constant Declarations


/*****************************************************************************/
//	Variable Declarations
/*****************************************************************************/
//Put Variable Declarations here
/*****************************************************************************/
//	End Variable Declarations


/*****************************************************************************/
//	Function Prototypes
/*****************************************************************************/
//Put function prototypes here
/*****************************************************************************/
//	End Function Prototypes


/*****************************************************************************/
//	Function Definitions
/*****************************************************************************/
//Put function definitions here
/*****************************************************************************/
//	End Function Definitions


/******************************************************************************
    Filename: cc1101_spi.c

    Description: implementation file for a minimum set of neccessary functions
                 to communicate with CC1101 over SPI

*******************************************************************************/


/******************************************************************************
 * INCLUDES
 */
#include "hal_types.h"
#include "hal_spi_rf_trxeb.h"
#include "cc1101_spi.h"


/******************************************************************************
 * @fn          cc1101SpiReadReg
 *
 * @brief       Reads register(s). If len  = 1: one byte is read
 *                                 if len != 1: len bytes are read in burst
 *                                              mode
 * input parameters
 *
 * @param       addr   - address to read
 * @param       *pData - pointer to data array where read data is stored
 * @param       len    - numbers of bytes to read starting from addr
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc1101SpiReadReg(uint8 addr, uint8 *pData, uint8 len)
{
  uint8 rc;
  rc = trx8BitRegAccess((RADIO_BURST_ACCESS|RADIO_READ_ACCESS), addr, pData, len);
  return (rc);
}

/******************************************************************************
 * @fn          cc1101SpiWriteReg
 *
 * @brief       writes register(s). If len  = 1: one byte is written
 *                                  if len != 1: len bytes at *data is written
 *                                               in burst mode.
 * input parameters
 *
 * @param       addr   - register address to write
 * @param       *pData - pointer to data array that is written
 * @param       len    - number of bytes written
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc1101SpiWriteReg(uint8 addr, uint8 *pData, uint8 len)
{
  uint8 rc;
  rc = trx8BitRegAccess((RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS),addr, pData, len);
  return (rc);
}

/******************************************************************************
 * @fn          cc1101SpiWriteTxFifo
 *
 * @brief       Writes provided data to TX FIFO
 *
 * input parameters
 *
 * @param       *pData - pointer to data array that is written to TX FIFO
 * @param       len    - Length of data array to be written
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc1101SpiWriteTxFifo(uint8 *pData, uint8 len)
{
  uint8 rc;
  rc = trx8BitRegAccess((RADIO_BURST_ACCESS|RADIO_WRITE_ACCESS),CC1101_FIFO, pData, len);
  return (rc);
}


/******************************************************************************
 * @fn          cc1101SpiReadRxFifo
 *
 * @brief       Reads RX FIFO values to pData array
 *
 * input parameters
 *
 * @param       *pData - pointer to data array where RX FIFO bytes are saved
 * @param       len    - number of bytes to read from the RX FIFO
 *
 * output parameters
 *
 * @return      rfStatus_t
 */
rfStatus_t cc1101SpiReadRxFifo(uint8 *pData, uint8 len)
{
  uint8 rc;
  rc = trx8BitRegAccess((RADIO_BURST_ACCESS|RADIO_READ_ACCESS),CC1101_FIFO, pData, len);
  return (rc);
}

/******************************************************************************
 * @fn      cc1101GetTxStatus(void)
 *
 * @brief   This function transmits a No Operation Strobe (SNOP) to get the
 *          status of the radio and the number of free bytes in the TX FIFO.
 *
 *          Status byte:
 *
 *          ---------------------------------------------------------------------------
 *          |          |            |                                                 |
 *          | CHIP_RDY | STATE[2:0] | FIFO_BYTES_AVAILABLE (free bytes in the TX FIFO |
 *          |          |            |                                                 |
 *          ---------------------------------------------------------------------------
 *
 *          NOTE:
 *          When reading a status register over the SPI interface while the
 *          register is updated by the radio hardware, there is a small, but
 *          finite, probability that the result is corrupt. This also applies
 *          to the chip status byte. The CC1100 and CC1101 errata notes explain
 *          the problem and propose several work arounds.
 *
 * input parameters
 *
 * @param   none
 *
 * output parameters
 *
 * @return  rfStatus_t
 *
 */
rfStatus_t cc1101GetTxStatus(void)
{
    return(trxSpiCmdStrobe(CC1101_SNOP));
}

/******************************************************************************
 *
 *  @fn       cc1101GetRxStatus(void)
 *
 *  @brief
 *            This function transmits a No Operation Strobe (SNOP) with the
 *            read bit set to get the status of the radio and the number of
 *            available bytes in the RXFIFO.
 *
 *            Status byte:
 *
 *            --------------------------------------------------------------------------------
 *            |          |            |                                                      |
 *            | CHIP_RDY | STATE[2:0] | FIFO_BYTES_AVAILABLE (available bytes in the RX FIFO |
 *            |          |            |                                                      |
 *            --------------------------------------------------------------------------------
 *
 *            NOTE:
 *            When reading a status register over the SPI interface while the
 *            register is updated by the radio hardware, there is a small, but
 *            finite, probability that the result is corrupt. This also applies
 *            to the chip status byte. The CC1100 and CC1101 errata notes explain
 *            the problem and propose several work arounds.
 *
 * input parameters
 *
 * @param     none
 *
 * output parameters
 *
 * @return    rfStatus_t
 *
 */
rfStatus_t cc1101GetRxStatus(void)
{
    return(trxSpiCmdStrobe(CC1101_SNOP | RADIO_READ_ACCESS));
}

/******************************************************************************
  Copyright 2010 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
*******************************************************************************/
