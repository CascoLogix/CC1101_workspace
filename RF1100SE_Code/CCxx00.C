#include "config.h"
#include "comm.h"


#define WAIT Delay_us(10)

#define MAXLEN 61

uchar Lqi;
uchar bCrcOk,Rssi,RfChkT,bRfChk;
uchar RfRunNo;
				  

uchar  bRcvOk,bSendOk,IconRX,IconTX;
void ShowSendTime(void);
unsigned int RfT;
uchar SerData[62] = {0x0c,1,2,3,4,5,6,7,8,9};
uchar RFData[62]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//���ջ���
int Sync0,Sync1;

extern unsigned char reset_rf;
extern unsigned char b_rf_check;


//ʹ��Ƶ�β�ͬʱ�����ò�ͬ�����߲���
//����һ����������ģ��Ĳ�����


typedef struct S_RF_SETTINGS{
    BYTE FSCTRL1;   // Frequency synthesizer control.
    BYTE FSCTRL0;   // Frequency synthesizer control.
    BYTE FREQ2;     // Frequency control word, high byte.
    BYTE FREQ1;     // Frequency control word, middle byte.
    BYTE FREQ0;     // Frequency control word, low byte.
    BYTE MDMCFG4;   // Modem configuration.
    BYTE MDMCFG3;   // Modem configuration.
    BYTE MDMCFG2;   // Modem configuration.
    BYTE MDMCFG1;   // Modem configuration.
    BYTE MDMCFG0;   // Modem configuration.
    BYTE CHANNR;    // Channel number.
    BYTE DEVIATN;   // Modem deviation setting (when FSK modulation is enabled).
    BYTE FREND1;    // Front end RX configuration.
    BYTE FREND0;    // Front end RX configuration.
    BYTE MCSM0;     // Main Radio Control State Machine configuration.
    BYTE FOCCFG;    // Frequency Offset Compensation Configuration.
    BYTE BSCFG;     // Bit synchronization Configuration.
    BYTE AGCCTRL2;  // AGC control.
	BYTE AGCCTRL1;  // AGC control.
    BYTE AGCCTRL0;  // AGC control.
    BYTE FSCAL3;    // Frequency synthesizer calibration.
    BYTE FSCAL2;    // Frequency synthesizer calibration.
	BYTE FSCAL1;    // Frequency synthesizer calibration.
    BYTE FSCAL0;    // Frequency synthesizer calibration.
    BYTE FSTEST;    // Frequency synthesizer calibration control
    BYTE TEST2;     // Various test settings.
    BYTE TEST1;     // Various test settings.
    BYTE TEST0;     // Various test settings.
    BYTE IOCFG2;    // GDO2 output pin configuration
    BYTE IOCFG0;    // GDO0 output pin configuration
    BYTE PKTCTRL1;  // Packet automation control.
    BYTE PKTCTRL0;  // Packet automation control.
    BYTE ADDR;      // Device address.
    BYTE PKTLEN;    // Packet length.
}RF_SETTINGS ;

RF_SETTINGS rfSettings7680 = {
    0x0B,   // FSCTRL1   Frequency synthesizer control.
    0x00,   // FSCTRL0   Frequency synthesizer control.
    0x5C,   // FREQ2     Frequency control word, high byte.
    0x4E,   // FREQ1     Frequency control word, middle byte.
    0xDE,   // FREQ0     Frequency control word, low byte.
    0x7B,   // MDMCFG4   Modem configuration.
    0x83,   // MDMCFG3   Modem configuration.
    0x93,   // MDMCFG2   Modem configuration.
    0x23,   // MDMCFG1   Modem configuration.
    0xA4,   // MDMCFG0   Modem configuration.
    0x00,   // CHANNR    Channel number.
    0x44,   // DEVIATN   Modem deviation setting (when FSK modulation is enabled).
    0x56,   // FREND1    Front end RX configuration.
    0x10,   // FREND0    Front end RX configuration.
    0x18,   // MCSM0     Main Radio Control State Machine configuration.
    0x16,   // FOCCFG    Frequency Offset Compensation Configuration.
    0x6C,   // BSCFG     Bit synchronization Configuration.
    0x43,   // AGCCTRL2  AGC control.
    0x40,   // AGCCTRL1  AGC control.
    0x91,   // AGCCTRL0  AGC control.
    0xA9,   // FSCAL3    Frequency synthesizer calibration.
    0x0A,   // FSCAL2    Frequency synthesizer calibration.
    0x00,   // FSCAL1    Frequency synthesizer calibration.
    0x11,   // FSCAL0    Frequency synthesizer calibration.
    0x59,   // FSTEST    Frequency synthesizer calibration.
    0x88,   // TEST2     Various test settings.
    0x31,   // TEST1     Various test settings.
    0x0B,   // TEST0     Various test settings.
    0x29,   // IOCFG2    GDO2 output pin configuration.
    0x06,   // IOCFG0D   GDO0 output pin configuration. Refer to SmartRF?Studio User Manual for detailed pseudo register explanation.
    0x04,   // PKTCTRL1  Packet automation control.
    0x05,   // PKTCTRL0  Packet automation control.
    0x00,   // ADDR      Device address.
    0xFF    // PKTLEN    Packet length.
};

//********************************
//д1���ֽڵ�ʱ��ͬʱ����1���ֽ�
BYTE CC_SpiWr(BYTE Cmd)
{
  uchar i;
#ifndef SPIWR
//��IO����ģ��SPI����
   BYTE Status=0;
   for (i=0;i<8;i++)
   {  //in...
      Status=Status<<1;
      //if (CHKRFIN >0) 
	  //if (SPI_MISO >0)

	  if (RF433_MISO>0)
	      Status|=0x01;
      //out...
     // if (Cmd>0x7f) //��λ�ȳ�
	 if (Cmd & 0x80)
          {RF433_MOSI_UP;}//RFSDOUP;
   	  else
      	 {RF433_MOSI_DN;}//RFSDODN;
   	  //asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop");
	  NOP();
	  RF433_SPCK_UP;//RFSCLUP;
	  //asm("nop"); asm("nop"); asm("nop"); asm("nop");asm("nop");
	  NOP();
	  RF433_SPCK_DN;//RFSCLDN;
	  
	  Cmd=Cmd<<1;
   }	  	  
   return Status;
#else
//ֱ��ʹ��AVR��SPI����
BYTE i=0;
   SPDR=Cmd;
   while (((SPSR&(1<<SPIF))==0)&&(i<100))
   { i++;//!!����SpiWr�жϺ������������ͻ�����������ʵ��i=4
     NOP();NOP();NOP();NOP();
   };
   return SPDR;
#endif   
}
//**********************************************************************************
//�ȴ�оƬSO������ͱ�ʾReady
void CC_Rdy()
{
	BYTE i;
   for (i=0;i<10;i++)
   { 
     //if (CHKRFIN==0) return; 
	 if (RF433_MISO==0) return;
     Delay_us(200);//���������200uS������20nS
   }
}
//************************************************************************************
//д������
BYTE CC_Cmd(BYTE Cmd)
{
	BYTE Status;
    
	RF433_CS_DN;
	CC_Rdy();
	Status=CC_SpiWr(Cmd);
	RF433_CS_UP;
    WAIT;	
	return Status;
}
//*************************************************************************************
//ָ����ַ��д������
BYTE CC_WrReg(BYTE Addr,BYTE Data)
{
	BYTE Status;

    RF433_CS_DN;
	CC_Rdy();
	Status=CC_SpiWr(Addr);
	CC_SpiWr(Data);
	RF433_CS_UP;
	WAIT;
	return Status;
}
//************************************************************************************
//ָ����ַ������д����
BYTE CC_WrRegs(uchar Addr,uchar *Buf,uchar Count)
{
	BYTE Status,i;

    RF433_CS_DN;
	CC_Rdy();
	Status=CC_SpiWr(Addr|0x40);
	for (i=0;i<Count;i++)
	{ CC_SpiWr(Buf[i]);
	}
	RF433_CS_UP;
	WAIT;
	return Status;
}
//*************************************************************************************
//��״̬�Ĵ���
BYTE CC_RdStatus(BYTE Addr)
{
	BYTE Data=0;   
    
	RF433_CS_DN;
	CC_Rdy();
	Data=CC_SpiWr(Addr|0xC0);//
	Data=CC_SpiWr(0);
	RF433_CS_UP;
	WAIT;
	return Data;
}
//*****************************************************************************************
//������
BYTE CC_RdReg(BYTE Addr)
{
	BYTE Data;   
    
	RF433_CS_DN;
	CC_Rdy();
	Data=CC_SpiWr(Addr|0x80);
	Data=CC_SpiWr(0);
	RF433_CS_UP;
	WAIT;
	return Data;
}
//*******************************************************************************************
//������������
BYTE CC_RdRegs(uchar Addr,uchar *Buf,uchar Count)
{
	BYTE Status,i;

    RF433_CS_DN;
	CC_Rdy();
	Status=CC_SpiWr(Addr|0xC0);//******
	for (i=0;i<Count;i++)
	{ 
	 Buf[i]=CC_SpiWr(0); //******
	}
	RF433_CS_UP;
	WAIT;
	return Status;

}
//******************************************************************************************
//��״̬
BYTE CC_GetStatus()
{
  return CC_Cmd(CCxxx0_SNOP);
}
//**********************************************************************************
//оƬ�ϵ縴λ
void CC_RESET()
{
   RF433_CS_UP;
   RF433_CS_DN;
   RF433_CS_UP;
   Delay_us(500);//>40us
   
   CC_Cmd(CCxxx0_SRES);
}
//***********************************************************************************
//����оƬ���Ժ����߲���
void CC_RfConfig(RF_SETTINGS *pRfSettings) 
{    // Write register settings
    CC_WrReg(CCxxx0_FSCTRL1,  pRfSettings->FSCTRL1);
    CC_WrReg(CCxxx0_FSCTRL0,  pRfSettings->FSCTRL0);
    CC_WrReg(CCxxx0_FREQ2,    pRfSettings->FREQ2);
    CC_WrReg(CCxxx0_FREQ1,    pRfSettings->FREQ1);
    CC_WrReg(CCxxx0_FREQ0,    pRfSettings->FREQ0);
    CC_WrReg(CCxxx0_MDMCFG4,  pRfSettings->MDMCFG4);
    CC_WrReg(CCxxx0_MDMCFG3,  pRfSettings->MDMCFG3);
    CC_WrReg(CCxxx0_MDMCFG2,  pRfSettings->MDMCFG2);
    CC_WrReg(CCxxx0_MDMCFG1,  pRfSettings->MDMCFG1);
    CC_WrReg(CCxxx0_MDMCFG0,  pRfSettings->MDMCFG0);
    CC_WrReg(CCxxx0_CHANNR,   pRfSettings->CHANNR);
    CC_WrReg(CCxxx0_DEVIATN,  pRfSettings->DEVIATN);
    CC_WrReg(CCxxx0_FREND1,   pRfSettings->FREND1);
    CC_WrReg(CCxxx0_FREND0,   pRfSettings->FREND0);
    CC_WrReg(CCxxx0_MCSM0 ,   pRfSettings->MCSM0 );
    CC_WrReg(CCxxx0_FOCCFG,   pRfSettings->FOCCFG);
    CC_WrReg(CCxxx0_BSCFG,    pRfSettings->BSCFG);
    CC_WrReg(CCxxx0_AGCCTRL2, pRfSettings->AGCCTRL2);
	CC_WrReg(CCxxx0_AGCCTRL1, pRfSettings->AGCCTRL1);
    CC_WrReg(CCxxx0_AGCCTRL0, pRfSettings->AGCCTRL0);
    CC_WrReg(CCxxx0_FSCAL3,   pRfSettings->FSCAL3);
    CC_WrReg(CCxxx0_FSCAL2,   pRfSettings->FSCAL2);
	CC_WrReg(CCxxx0_FSCAL1,   pRfSettings->FSCAL1);
    CC_WrReg(CCxxx0_FSCAL0,   pRfSettings->FSCAL0);
    CC_WrReg(CCxxx0_FSTEST,   pRfSettings->FSTEST);
    CC_WrReg(CCxxx0_TEST2,    pRfSettings->TEST2);
    CC_WrReg(CCxxx0_TEST1,    pRfSettings->TEST1);
    CC_WrReg(CCxxx0_TEST0,    pRfSettings->TEST0);
    CC_WrReg(CCxxx0_IOCFG2,   pRfSettings->IOCFG2);
    CC_WrReg(CCxxx0_IOCFG0,   pRfSettings->IOCFG0);    
    CC_WrReg(CCxxx0_PKTCTRL1, pRfSettings->PKTCTRL1);
    CC_WrReg(CCxxx0_PKTCTRL0, pRfSettings->PKTCTRL0);
    CC_WrReg(CCxxx0_ADDR,     pRfSettings->ADDR);
    CC_WrReg(CCxxx0_PKTLEN,   pRfSettings->PKTLEN);
}
//****************************************************************************************
//������Ƶ����
void CC_PaTable(BYTE paTable)
{
  CC_WrReg(CCxxx0_PATABLE, paTable);
}
//****************************************************************************************
//����Ƶ��
void CC_Chan(BYTE Chan)
{
  CC_Idle();//Ϊ����
  CC_WrReg(CCxxx0_CHANNR,Chan);
}
//****************************************************************************************
//�򿪻�ر�FECǰ�����
void CC_FEC(BYTE On)
{
	BYTE Reg;
  Reg=CC_RdReg(CCxxx0_MDMCFG1);
  if (On==1) 
     CC_WrReg(CCxxx0_MDMCFG1, Reg | 0x80);
  else
  	 CC_WrReg(CCxxx0_MDMCFG1, Reg & 0x7F);
}
//*****************************************************************************************
//�򿪻�ر�WHITE���ݹ��ܣ�ʹ����01���⣩
void CC_WHITE(BYTE On)
{
	BYTE Reg;
  Reg=CC_RdReg(CCxxx0_PKTCTRL0);
  if (On==1) 
     CC_WrReg(CCxxx0_PKTCTRL0, Reg | 0x40);
  else
  	 CC_WrReg(CCxxx0_PKTCTRL0, Reg & 0xBF);
}


//****************************************************************************************
//������ջ������ͽ��մ�����ر�־
void CC_ClrRx() 
{
    CC_Idle();//!!������Idle״̬
	CC_Cmd(CCxxx0_SFRX);
}	  

//**********************************************************************************************
//������ͻ������ͷ��ʹ�����ر�־
void  CC_ClrTx() 	
{
  CC_Idle();//!!������Idle״̬
  CC_Cmd(CCxxx0_SFTX);
}

//**********************************************************************************
//����ģ���ʼ��
void CC_Init()
{
  CLI();
  CC_RESET();
  CC_RfConfig(&rfSettings7680);

  //CC_RfConfig(&rfSettings1200);
 // CC_WrReg(CCxxx0_SYNC1,0xa4 );//ȱʡֵ��D391
 // CC_WrReg(CCxxx0_SYNC0,0x25 );
  //CC_WrReg(CCxxx0_SYNC1,0x08 );//ȱʡֵ��D391
  //CC_WrReg(CCxxx0_SYNC0,0x00 );
  //CC_WrReg(CCxxx0_SYNC1,Sync0 );
  //CC_WrReg(CCxxx0_SYNC0,Sync1 );

  CC_PaTable(PAMAX);

   CC_WrReg(CCxxx0_MCSM1,0x00 );//0x0fȡ��CCA���շ��ܻص�RX ���ܣ��������Զ�У��Ƶ��
  //CC_WrReg(CCxxx0_MCSM1,0x30 );//��λֵ0x30 ��CCA���շ���IDLE
 // CC_WHITE(1);
 
  CC_FEC(1);
  Delay_ms(20);
  CC_RxOn();
  //GIFR=0xE0;//clr int
  
  //CC_Test();
  SEI();
}



//**************************************************************************************
 volatile BYTE i=0;
//����ģ�鹦�ܲ��ԣ�Ӳ��������
void CC_Test()
{
  //!!����ע��volatile�������Ż���i��ֵ����
  i=CC_RdStatus(CCxxx0_VERSION);//0x03
  i=CC_RdReg(CCxxx0_PKTCTRL0);//0x05
  i=CC_RdReg(CCxxx0_PKTLEN);//0xff
  i=CC_GetStatus();
  CC_Idle();
  i=CC_GetStatus();
  CC_RxOn();
}
//**************************************************************************************
//�������ݰ����������е�1�ֽ��ǳ���
void CC_SendPacket(uchar *txBuffer, uchar size) 
{

    //TCNT1=0;	
	//CC_Idle();//����ֱ�Ӵ�RX״̬��TX״̬?���ԣ���Լ1/10����û���л���TX״̬������CCA��ԭ��
    /*i=(CC_GetStatus()>>4);
	if (i>=2)
	{ CC_Idle();
	}*/
	
	CC_ClrTx();//v1.1��֤TxBYTES����ǰ�ֽ�
	
    CC_WrReg(CCxxx0_TXFIFO, size);//len
	CC_WrRegs(CCxxx0_TXFIFO, txBuffer, size);//***
	CC_Cmd(CCxxx0_STX);
	
 //RfT=TCNT1;//���Ժ�ʱ
	bSendOk=0;
	//reset_rf=2;b_rf_check=0;//40ms
}

//*************************************************************************************************
//�������յ����ݣ���LQI,RSSI�����ж�CrcOk
void CC_RdPacket()
{

    uchar iLen;
	 //TCNT1=0;
	 //iLen=CC_RdStatus(CCxxx0_RXBYTES) & 0x7f;//read RxFIFO Nums
	 //FIFO���������ֽڣ���̬�仯
     
	 // Read length byte
     iLen= CC_RdReg(CCxxx0_RXFIFO);//��һ�ֽ���Len ���ݰ�����
     if (iLen==0) goto RXERR; 
	 if (iLen>MAXLEN) goto RXERR;//iLen=MAXLEN;
	 
     // Read data from RX FIFO and store in rxBuffer
	 SerData[0]=iLen;    //���ݰ�����
   
     CC_RdRegs(CCxxx0_RXFIFO, SerData+1, iLen); //������
   
     // Read the 2 appended status bytes (status[0] = RSSI, status[1] = LQI)
     Rssi=CC_RdReg(CCxxx0_RXFIFO); 

     Lqi=CC_RdReg(CCxxx0_RXFIFO);
     
	 if (Lqi>0x80) //80
	 {  
	    bCrcOk=1;// MSB of LQI is the CRC_OK bit ***
	    bRcvOk=TRUE;//IconRX=1;
		//abcd++;
	 }
	// RcvOk=1;
	   else bCrcOk=0;
    	
	 
	 iLen=CC_RdStatus(CCxxx0_RXBYTES) & 0x7f;
	 //RfT=TCNT1;//���Ժ�ʱ
	 if (iLen==0) 
		 return;
	 
RXERR:	 //Ӧ��Ϊ0����Ϊ0�Ͳ��ԣ�Ҫ���RxFiFo
	 CC_ClrRx();
	 //iLen=CC_RdStatus(CCxxx0_RXBYTES) & 0x7f;
	 bRcvOk=0;
	 bCrcOk=0;
	 
}			
//*********************************************************************************************
//���ź�ǿ��RSSIֵת����dBֵ
BYTE CC_RssiCh(BYTE rssi)
{//���ֵ����ֵ�������Ǹ���dBm�����緵��ֵ��55��-55dBm
  if (rssi>=128)
  { 
	  return (128+RSSI0-(rssi>>1));
  }
  else
  { 
	  return (RSSI0-(rssi>>1));
  }
}

//*************************************************************************************
//���ź�ǿ��RSSIֵ
BYTE CC_Rssi()
{
  return CC_RdStatus(CCxxx0_RSSI);
}


//**************************************************************************************
//�����״̬�Ĵ���
BYTE CC_PackStatus()
{
  return CC_RdStatus(CCxxx0_PKTSTATUS);
  //bit0-bit7 GDO0,GDO1,GDO2,SYNC,  CCA,PQT,CS,CRCOK
  //���MCSM1.CCA��0û��ʹ��CCA�Ļ���CCAָʾλ��Ϊ1��
  //���ʹ��CCA��CCA��CSλ���෴
}
//***********************************************************************************
//��CCA�ж��Ƿ����ŵ���ͻ
BYTE CC_CheckCCA()
{
	BYTE i;
  
	i=CC_RdStatus(CCxxx0_PKTSTATUS);
  //bit0-bit7 GDO0,GDO1,GDO2,SYNC,  CCA,PQT,CS,CRCOK
  //���MCSM1.CCA��0û��ʹ��CCA�Ļ���CCAָʾλ��Ϊ1��������ʹ��CCA!!
  //���ʹ��CCA��CCA��CSλ���෴
  //if (CHK(i,6)==0)//ʹ��CSָʾ��Ч����ͬ
//  if CHK(i,4) //ʹ��CCAָʾ
  if ((i & 4) ==4)
    return 1;
  else
    return 0;
}
//***************************************************************************************
//�������оƬ�Ƿ�����
void RfChk()
{
   BYTE i;
   CLI();
   i=(CC_GetStatus()>>4);
   if (i!=1)//0IDLE 1RX 2TX 3FSTXON 4CALI 5SETT 6RX_OVER 7TX_UNDER
   { 
	  CC_Idle();
	  Delay_us(100);
	  CC_Cmd(CCxxx0_SFRX);
	  Delay_us(100);
	  CC_Cmd(CCxxx0_SFTX);
	  Delay_us(100);
	  CC_RxOn();
	}
   bSendOk=1;//!!	
   SEI();
}
//***************************************************************************************
//���Բ�ͬ״̬��ĳЩ�Ĵ�����ֵ��������
void ChkRfState()
{
	volatile BYTE i;

CHKNEXT:
   switch (RfRunNo)
   {
     case 1:
	 	  i=CC_GetStatus();
		  //i=CC_RdReg(CCxxx0_MCSM1);
		  RfRunNo=0;
		  break;
	 case 2:
	 	  i=CC_RdStatus(CCxxx0_RXBYTES) & 0x7f;	  
		  i= CC_RdReg(CCxxx0_RXFIFO);
		  break;
	 case 3:
	 	  i=CC_RdStatus(CCxxx0_TXBYTES) & 0x7f;	  
		  CC_ClrTx();
		  i=CC_RdStatus(CCxxx0_TXBYTES) & 0x7f;
		  CC_RxOn();
		  RfRunNo=0;	  
		  break;
	 case 4:
	 	  i=CC_RdStatus(CCxxx0_RXBYTES) & 0x7f;	  
		  CC_ClrRx();
		  i=CC_RdStatus(CCxxx0_RXBYTES) & 0x7f;
		  CC_RxOn();	  
		  RfRunNo=0;
		  break;	  	  
	 default:
	 	  RfRunNo=0;	 
	 	  break;	 	  
   }
   if (RfRunNo>0) goto CHKNEXT;
}
//******************************************************************************
//�޸�ͬ����
void CC_SyncNew()
{ 
 // CLI();
  CC_WrReg(CCxxx0_SYNC1,Sync0 );//
  CC_WrReg(CCxxx0_SYNC0,Sync1 );
 // SEI();
}

//==============================================================================
void RfOff()
{
  CC_Cmd(0x36);//IDLE ������IDLE���ܽ���SLEEP
  CC_Cmd(0x39);//Rf PwrDown
  
  CLR(GICR,INT0);//!!�ر�int0
  PORTD &= 0xfb;  //!!����ʱ��RFGDO0������͵�ƽ��INT0�Ų�Ҫ��������������ĵ�100uA

}