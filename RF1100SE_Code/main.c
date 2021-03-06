#include <msp430.h> 

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	return 0;
}







#include "config.h"
#include "comm.h"
#include "macros.h"

const FreqID=8 ;//定义工作频点为8频点 频点范围0--32
void Delay_us(int t)
{
  while(t--)
  {
    NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
  }
}
void Delay_ms(int t)
{
  int i;
  for (i=0;i<t;i++)
  Delay_us(1000);
}
//====================================================================
//定义单片机脚，不能是空脚就不管SSD
//====================================================================
void PortInit(void)
{
	DDRA  = 0x7F;//01111111
	PORTA = 0x20;//00100000

	DDRB  = 0xB0;//10110000//Miso  改为输入 否则无线模块打不开，
	PORTB = 0x1F;//00011111

	DDRC  = 0xC3;//11000011
	PORTC = 0x80;//10000000

	DDRD  = 0xFA;//11111010
	PORTD = 0x43;//01000011

}
void xieyi_panduan (void)
{
     SerData[10]++; //接收次数加1
	 SerData[12]=CC_RssiCh(Rssi);  //学生机灵敏度
	 RFData[12]=SerData[12];
	 CC_SendPacket(SerData+1,(SerData[0]+1));//发送数据包 ***//因为增加了学生机器RSSI
}

void main(void)
{
	PortInit();
	while(1);

}
//******************************************************************************
//无线接收中断
// 把接收到的数据放入RFData buffer中，并解析
// archived
#pragma interrupt_handler	INT0_handler:2
void INT0_handler(void)
{
	BYTE dd;
	int i=0;
	CLI();
	dd=CC_RdStatus(0x35);   //读状态寄存器
	if (dd==17) CC_ClrRx(); //清除接收缓冲区和接收错误相关标志
	if (dd==22) CC_ClrTx(); //清除发送缓冲区和发送错误相关标志
	dd=CC_RdStatus(0x3B)&0x7f;//CCxxx0_RXBYTES 读数据长度
	if (dd==0)//V1.1 ?-ê?if (bSendOk==0) 长度 0
	{
		CC_Chan(FreqID); // new added ??????????????????
		CC_RxOn();//	进入接收状态
	}
	else  //长度不为0
	{
		CC_RdPacket(); //读数据包
		CC_Chan(FreqID); // new added ??????????????????
		CC_RxOn();
		if ((bRcvOk==1)&&(SerData[0]<62))
		{
			//复制数据,用于在主程序里显示和修改,SerData 用来在RF中断里判断
			memcpy(RFData,SerData,SerData[0]);
			xieyi_panduan();//解析协议
            bRcvOk=0;
		}
	}
    SEI(); //re-enable interrupts
}
//****************************************************************
// 退出休眠模式，执行下一句语句
// archived
#pragma interrupt_handler	INT2_handler:4
void INT2_handler(void)  //进入中断服务程序之后中断标志自动清零。
{
	//bWakeUp=1;  //开机中断标志位
}
