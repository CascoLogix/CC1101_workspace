#include "CC1101.h"
#include "Pinouts.h"
#include "Registers.h"



//this function initializes both the cc1101 and the MSP430
void CC1101::Init(void)
{
	SPISetup();			//configure SPI
	Wait(5000);			//wait for CC1101 power-on reset
	PowerupReset();		//Reset CC1101
	WriteSettings();	//Send configuration commands
}

//
void CC1101::SendPacket(char *txBuffer, char size)
{
  SPIWriteBurstReg(TXFIFO, txBuffer, size); // Write TX data
  SPIStrobe(STX);           				// Change state to TX, initiating
                                            // data transfer

  while (!(GDO0_PxIN&GDO0_PIN));
                                            // Wait GDO0 to go hi -> sync TX'ed
  while (GDO0_PxIN&GDO0_PIN);
                                            // Wait GDO0 to clear -> end of pkt
  GDO0_PxIFG &= ~GDO0_PIN;      			// After pkt TX, this flag is set.
                                            // Has to be cleared before existing
  SPIStrobe(SIDLE);
}

char CC1101::ReceivePacket(char *rxBuffer, char *length)
{
  char status[2];
  char pktLen;
  char returnval = 0;
  if ((SPIReadStatus(RXBYTES) & NUM_RXBYTES))
  {
    pktLen = SPIReadReg(RXFIFO); 			// Read length byte

    if (pktLen <= *length)                  // If pktLen size <= rxBuffer
    {
      SPIReadBurstReg(RXFIFO, rxBuffer, pktLen); // Pull data
      *length = pktLen;                     // Return the actual size
      SPIReadBurstReg(RXFIFO, status, 2);
                                            // Read appended status bytes
      returnval = (char)(status[LQI_RX] & CRC_OK);
    }                                       // Return CRC_OK bit
    else
    {
      *length = pktLen;                     // Return read size
      SPIStrobe(SFRX);      				// Flush RXFIFO
    }
  }

      return returnval;							//1 = good, 0 = bad
}

char CC1101::PollReceiveFlag(void)
{
	char returnval = 0;
	if(GDO0_PIN & GDO0_PxIN)
	{
		while(GDO0_PIN & GDO0_PxIN){}
		returnval = 1;
	}
	return returnval;
}

void CC1101::SetReceive(void)
{
	SPIStrobe(SRX);			//put into RX mode
}

void CC1101::SetIdle(void)
{
	SPIStrobe(SIDLE);		//put int IDLE mode
}

void CC1101::SetSleep(void)
{
	SPIStrobe(SXOFF);		//turn off
}




//Description: This function will get the RSSI from the CC1101 and return it.
//The RSSI value read from the RSSI status register is a 2�s complement number and is in
//dBm with � dB resolution. Praise him. (pardon this random Dr. Who reference)
short CC1101::GetRSSI(void)
{
	unsigned char RSSI_dec;			//base ten reading
	short RSSI_dBm;			//dbm value
	const char RSSI_offset = 74;
	const unsigned char NEGATIVE = 128;

	//get RSSI
	RSSI_dec = SPIReadStatus(RSSI);
	//if negative, convert to dBm
	if (RSSI_dec >= NEGATIVE)
	{
		RSSI_dBm = (( RSSI_dec - 256) / 2) - RSSI_offset;
	}
	//If positive, convert to dBm
	else
	{
		RSSI_dBm = (RSSI_dec / 2) - RSSI_offset;
	}
	return RSSI_dBm;
}

void CC1101::WriteSettings(void)
{

	char PA[] =  {0x60};
	const unsigned char PA_LEN = 1;
	/* Sync word qualifier mode = 30/32 sync word bits detected */
	/* CRC autoflush = false */
	/* Channel spacing = 199.951172 */
	/* Data format = Normal mode */
	/* Data rate = 512.573 */
	/* RX filter BW = 58.035714 */
	/* PA ramping = false */
	/* Preamble count = 4 */
	/* Whitening = false */
	/* Address config = No address check */
	/* Carrier frequency = 433.999969 */
	/* Device address = 0 */
	/* TX power = 0 */
	/* Manchester enable = true */
	/* CRC enable = true */
	/* Deviation = 5.157471 */
	/* Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word */
	/* Packet length = 255 */
	/* Modulation format = GFSK */
	/* Base frequency = 433.999969 */
	/* Modulated = true */
	/* Channel number = 0 */
	//-------------------------------------------------------
	//Register Settings for CC1101
	//-Generated by the Awesomely Awesome SmartRF(c) studio
	//-------------------------------------------------------
	SPIWriteReg(IOCFG0  ,0x06);
	SPIWriteReg(FIFOTHR ,0x47);
	SPIWriteReg(PKTCTRL0,0x05);
	SPIWriteReg(FSCTRL1 ,0x06);
	SPIWriteReg(FREQ2   ,0x21);
	SPIWriteReg(FREQ1   ,0x62);
	SPIWriteReg(FREQ0   ,0x76);
	SPIWriteReg(MDMCFG4 ,0xF6);
	SPIWriteReg(MDMCFG3 ,0x83);
	SPIWriteReg(MDMCFG2 ,0x13);
	SPIWriteReg(DEVIATN ,0x15);
	SPIWriteReg(MCSM0   ,0x18);
	SPIWriteReg(FOCCFG  ,0x16);
	SPIWriteReg(WORCTRL ,0xFB);
	SPIWriteReg(FSCAL3  ,0xE9);
	SPIWriteReg(FSCAL2  ,0x2A);
	SPIWriteReg(FSCAL1  ,0x00);
	SPIWriteReg(FSCAL0  ,0x1F);
	SPIWriteReg(TEST2   ,0x81);
	SPIWriteReg(TEST1   ,0x35);
	SPIWriteReg(TEST0   ,0x09);

	SPIWriteBurstReg(PATABLE, PA, PA_LEN);
}

CC1101 cc1101;
