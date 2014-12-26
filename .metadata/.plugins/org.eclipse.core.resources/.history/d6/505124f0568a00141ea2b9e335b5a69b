#ifndef  __CONFIG_H
#define  __CONFIG_H

#include <iom32v.h>
#include <macros.h>
#include <eeprom.h>
#include <string.h>
#include "cc1101.h"


#define CC1100  //使用2.4G

//位操纵宏
#define SET(a,b) a|=(1<<b) 
#define CLR(a,b) a&=~(1<<b)
#define CPL(a,b) a^=(1<<b)
#define CHK(a,b) (a&(1<<b))

#define SBUF UDR
#define uint unsigned int
#define uchar unsigned char
#define bit char
#define ulong unsigned long


//各端口位定义
//PORTA
#define H0        PA0
#define H1        PA1
#define H2        PA2
#define H3        PA3
#define LPDC      4
#define LPCS      5
#define LPRST     6
#define VBATTERY  7  //电池电压检测


//PORTB
#define K0        PB0
#define K1        PB1
#define K2        PB2
#define K3        PB3
#define RFCS      4
#define MOSI      5
#define MISO      6
#define RFSCL     7

//PORTC
#define LPCK      0
#define LPDI      1
#define TCK       2 
#define TMS       3
#define TDO       4
#define TDI       5
#define LED2      PC7      

//PORTD
#define CHRG       0
#define LED1       PD1
#define GDO0       2
//#define GDO2       3
#define WDIO       4
#define WDO        5
#define WCS        6
#define WSCK       7

#endif
