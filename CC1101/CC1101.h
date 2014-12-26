/*
	CC1101.h - CC1101 module library


	This library is designed to be used with the CC1101/CC1100 module on the MSP430.
	It is designed to be portable across all MSP430 devices. To change the class for
	your specific MSP430, edit the #defines in Pinouts.h
	For details on the CC1101, please refer to the datasheet.

	Created By: Lucas Cox
	Do anything you would like with this code.
*/
#ifndef CC1101_h_
#define CC1101_h_

class CC1101
{
	private:
		void SPISetup(void);
		void PowerupReset(void);
		void SPIWriteReg(char addr, char value);
		void SPIWriteBurstReg(char addr, char *buffer, char count);
		char SPIReadReg(char addr);
		void SPIReadBurstReg(char addr, char *buffer, char count);
		char SPIReadStatus(char addr);
		void SPIStrobe(char strobe);
		void Wait(unsigned int cycles);
		void WriteSettings(void);


	public:
		void Init(void);
		void SendPacket(char *txBuffer, char size);
		char ReceivePacket(char *rxBuffer, char *length);
		char PollReceiveFlag(void);
		void SetReceive(void);
		void SetIdle(void);
		void SetSleep(void);
		short GetRSSI(void);

};

extern CC1101 cc1101;


#endif
