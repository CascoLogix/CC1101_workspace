
#define PAMAX 0xFE 
#define RSSI0  72  //Rssi Offset 

#define BYTE unsigned char
#define uchar unsigned char
//清除接收缓冲区和接收错误相关标志
extern void CC_ClrRx(void); 
//清除发送缓冲区和发送错误相关标志
extern void CC_ClrTx(void); 
extern BYTE CC_RdStatus(BYTE Addr);
extern void CC_SendPacket(uchar *txBuffer, uchar size);
extern void CC_Test(void);
extern void CC_Init(void);//初始化无线模块
extern void CC_Chan(BYTE Chan);
extern uchar bRcvOk;
extern uchar bSendOk,IconRX,IconTX;
extern uchar Lqi,bCrcOk,Rssi,RfChkT,bRfChk;
//写命令码
extern BYTE CC_Cmd(BYTE Cmd);
//读出接收的数据，和LQI,RSSI，并判断CrcOk
extern void CC_RdPacket(void);
//把信号强度RSSI值转换成dB值
extern BYTE CC_RssiCh(BYTE rssi);
extern uchar SerData[];
extern uchar RFData[];
