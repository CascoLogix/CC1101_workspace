/*
 * 		- name: main.c
 *		- write data: 19 Nov. 2012
 *		- modification data: 31 Nov. 2012
 *		- author: Wayne Xu (a0219294)
 *		- version: v1.2
 *
 * ***description
 *
 * 1. Program uses GRACE configuration for Device Configuration;
 * 		- SMCLK, DCO at 1MHz
 * 		- ACLK, external oscillator 32.768kHz
 * 		- USCIA0 as UART, 9600, 8 bits Data, No parity, 1 Stop (Hardware Mode)
 * 		- USCIB0 as 3 line SPI, Master Mode, 100kHz SCLK
 * 		- P2.0 as output, is used as CS for ADS1118 ADC device
 * 		- P2.3 as output,is used as RST of LCD
 * 		- P2.4 as output,is used as RS of LCD
 * 		- P2.5 ,is used as CS of LCD
 * 		- P2.1, P2.2 as input: SW1, SW2.
 * 		- P1.0 as output, is used as switch of buzzer
 * 2. this project is used to measure the temperature by type-K thermocouple.
 * 		- far-end temperature is measured by thermocouple, local temperature is measured by the internal sensor of ADS1118
 * 		- ADC mode: inputs are AIN0/AIN1, FS=+/-0.256, SS, DR=128sps, PULLUP on DOUT
 * 		- temperature mode: DR=128sps, PULLUP on DOUT
 * 		- Reference Tables are used to transform ADC code to temperature.
 *
 */

/*
 * ======== Standard MSP430 includes ========
 */
#include <msp430.h>

/*
 * ======== Grace related includes ========
 */
#include <ti/mcu/msp430/csl/CSL.h>
#include "UART_TxRx.h"
#include "ADS1118.h"
#include "LCD_driver.h"

void System_Initial();	//Initialize system
void set_Thrtemp();		//set threshold temperature
void set_Time();
void half_second();
void time_display();
void ADC_display();
void delay(void);		//delay function

#define BUZZ_ON 	P1OUT &= ~BIT0;	//set P1.0 low
#define BUZZ_OFF 	P1OUT |= BIT0;	//set P1.0 high


/*
 * ======== global variable ========
 */
/* flag is used to transmit parameter between interrupt service function and main function.
 * the flag will be changed by ISR in InterruptVectors_init.c     ...\grace\InterruptVectors_init.c
 *
 * Bit0, Launchpad S2 is pushed
 * Bit1, SW1 on BoosterPack is pushed
 * Bit2, SW2 on BoosterPack is pushed
 * Bit3, 1 second timer interrupt
 * Bit4, timer for ADC interrupts
 * Bit5, ADC input flag, 0 is internal temperature sensor, 1 is AIN0-AIN1
 * Bit6, make an inversion every half a second
 * Bit7, half a second interrupt
 * Bit8, for Fahrenheit display
 * Bit9, ADC channel flag, 0 for channel 0, 1 for channel 1.
 */
volatile unsigned int  flag;		//global flag.
volatile unsigned char Thr_state;	// state for threshold temperature setting state machine.
volatile unsigned char time_state;	// state for time setting state machine.


unsigned long time = 0;	// current time, a Continuous number seconds
unsigned int set_time;	// temporary for setting time
unsigned int Thr_temp;	// Threshold temperature
unsigned int set_temp;	// temporary for setting Threshold temperature
unsigned int num=0;	// temporary for setting Threshold temperature
		 int Act_temp;	// Actual temperature

/*
 *  ======== main ========
 */
int main(int argc, char *argv[])
{
	CSL_init();                 // Activate Grace-generated configuration
	delay();					//
    System_Initial();			// initialize system.
   	delay();					// delay and wait the first conversion.
   	_enable_interrupt();		// enable interrupt

   	while(1)
   	{
   		// half a second interrupt.
   		if(flag & BIT7)
   		{
   			half_second();
   		}

   		// read ADC result
   		if(flag & BIT4)			//Read ADC result
   		{
   			ADC_display();
   		}

   		// one second interrupt to display time
   		if (flag & BIT3)
   		{
   			time_display();
   		}

   		if(flag & BIT1)				// if SW1 is pushed, threshold temperature state machine will be changed
   		{
   			flag &= ~ BIT1;			// flag is reset
   			time_state = 0;			//when threshold temperature is setting, setting time is disable.
   			if(Thr_state >= 3)		// if in state 3, change to state 0;
   			{
   				Thr_state = 0;
   				Thr_temp = set_temp;				// assign threshold temperature
   				LCD_display_number(0,3,Thr_temp);	// display threshold temperature
   			}
   			else					//else, Thr_state is changed to next state
   			{
   				Thr_state ++;
   				//time_state = 0;		//when threshold temperature is setting, setting time is disable.
   			}
   		}

   		if((flag & BIT2) && (!Thr_state))			// if SW2 is pushed, and Thr_state = 0, time setting state machine will be changed
   		{
   			flag &= ~ BIT2;							// flag is reset

   			if(!(P1IN & BIT3))
   			{
   				flag ^= BIT9;						// S2 and SW2 are pushed together to change input channel
   				flag ^= BIT8;
   				if(flag & BIT9)
   					LCD_display_char(1,15,'2');
   				else
   					LCD_display_char(1,15,'1');
   			}
   			else
   			{
   				if(time_state >= 4)					// if in state 4, change to state 0;
   				{
   					time_state = 0;
   				 	time = set_time;				// assign actual time
   					set_time = 0;
   					LCD_display_time(0,8,time);		// display setting time
   				}
   				else
   				{
   				time_state ++;
   				}
   			}
   		}

   		if(flag & BIT0)				// P1.3 service, set the Threshold temperature or Time.
   		{
   			flag &= ~ BIT0;			// flag is reset
   			if(Thr_state != 0)
   			{
   				set_Thrtemp();		// set threshold temperature.
   			}
   			else if(time_state != 0)
   			{
   				set_Time();			// set timer.
   			}
   			else
   				flag ^= BIT8;		// display temperature in Fahrenheit
   		}

   		else
   		__no_operation();
   	}
    
    return (0);
}


void delay(void)
{
	unsigned int k;

	for (k = 1000; k > 0; k--)
		__no_operation();
}

void ADC_display()
{
	//char data[5];
	//float sensor;

	static signed int local_data, far_data;
	signed int temp;
	flag &= ~ BIT4;					// flag is reset
	if (!(flag & BIT5))
	{
		local_data = ADS_Read(1);	//read local temperature data,and start a new convertion for far-end temperature sensor.
	}
	else
	{
		far_data = ADS_Read(0);		//read far-end temperature,and start a new convertion for local temperature sensor.
		temp = far_data + local_compensation(local_data);	// transform the local_data to compensation codes of far-end.

		temp = ADC_code2temp(temp);	// transform the far-end thermocouple codes to temperature.

		if(flag & BIT8)				// display temperature in Fahrenheit
		{
			Act_temp = temp * 9 / 5 +320;
			LCD_display_temp(1,5,Act_temp);
			LCD_display_char(1,11,'F');
		}
		else
		{
			Act_temp = temp;
			LCD_display_temp(1,5,Act_temp);
			LCD_display_char(1,11,'C');
		}

	}
		// transmit temperature to PC by UART;
		/*
		hex2asc(&temp, 4, 2, data);
	   	uart_txstr(data); //the temperature is displayed in hexadecimal.
	   	uart_txc('\n');
		*/
}
void time_display()
{
	flag &= ~BIT3;						// flag is reset

	if (time_state == 0)
	{
  		if(time >= 86400 || time <= 0)	// if current is more than 24 hours
  		{
  			time = 0;
  		}
  		else
  		{
  			time--;
  		}



  		LCD_display_time(0,8,time);		// display time on LCD
	}
}

/*
 * function name: half_second()
 * description: it is executed every half a second. it has three functions,
 * the first one is to compare the Actual temperature and threshold temperature, if Actual temperature is higher than threshold
 * temperature, buzzer will work
 * the second one is to flicker the threshold temperature bit which is being set.
 * the third one is to flicker the time bit which is being set.
 */

void half_second()
{
	flag &= ~ BIT7;

	// judge actual temperature is higher than threshold temperature. if higher, buzzer will work
	if((Act_temp >= (10*Thr_temp)) && (flag & BIT6))
	{
	   	BUZZ_ON;
	}
	else if(time >0 && time <= 3)
	{
	   	BUZZ_ON;
	}
	else
	{
		BUZZ_OFF;
	}

	//display threshold temperature setting
	if(Thr_state == 0x01)						//threshold temperature state machine output.
	{
		if (flag & BIT6)
			LCD_display_char(0,4,' ');			//display blank space for half a second
		else
			LCD_display_number(0,3,set_temp);	//display hundred place for half a second
	}
	else if(Thr_state == 0x02)
	{
		if (flag & BIT6)
			LCD_display_char(0,5,' ');			//display blank space for half a second
		else
			LCD_display_number(0,3,set_temp);	//display decade for half a second
	}
	else if(Thr_state == 0x03)
	{
		if (flag & BIT6)
			LCD_display_char(0,6,' ');			//display blank space for half a second
		else
			LCD_display_number(0,3,set_temp); 	//display unit's digit for half a second
	}

	// display time setting
	if(time_state == 0x01)
	{
		if (flag & BIT6)
			LCD_display_char(0,11,' ');			//display blank space for half a second
		else
			LCD_display_time(0,8,set_time);;	//display hundred place for half a second
	}

	else if(time_state == 0x02)
	{
		if (flag & BIT6)
			LCD_display_char(0,12,' ');			//display blank space for half a second
		else
			LCD_display_time(0,8,set_time);;	//display hundred place for half a second
	}
	else if(time_state == 0x03)
	{
		if (flag & BIT6)
			LCD_display_char(0,14,' ');			//display blank space for half a second
		else
			LCD_display_time(0,8,set_time);;	//display hundred place for half a second
	}
	else if(time_state == 0x04)
	{
		if (flag & BIT6)
			LCD_display_char(0,15,' ');			//display blank space for half a second
		else
			LCD_display_time(0,8,set_time);;	//display hundred place for half a second
	}
}


/*
 * function name: set_Time()
 * description: set the time. the temporary is saved in variable set_time.
 */
void set_Time()
{
	if (time_state == 0x01)
	{
		if (set_time/600 >= 6)
		{
			set_time = set_time % 600;
	   	}
	   	else
	   	{
	   		set_time += 600;
	   	}
	}
	else if (time_state  == 0x02)
	{
		if (set_time%600/60 == 9)
	   	{
	   		set_time = set_time-540;
	   	}
	   	else
	   	{
	   		set_time += 60;
	   	}
	}
	else if (time_state  == 0x03)
	{
	   	if (set_time%60/10 == 5)
	   	{
	   		set_time = set_time-50;
	   	}
	   	else
	   	{
	   		set_time += 10;;
	   	}
	}
	else if (time_state  == 0x04)
	{
	   	if (set_time%10 == 9)
	   	{
	   		set_time = set_time-9;
	   	}
	   	else
	   	{
	   		set_time++;
	   	}
	}
	else
	__no_operation();
}



/*
 * function name:set_hrtemp()
 * description: set the threshold temperature. the temporary is saved in variable set_temp.
 */
void set_Thrtemp()
{
	if (Thr_state == 0x01)
	{
		if (set_temp/100 == 9)
		{
			set_temp = set_temp-900;
	   	}
	   	else
	   	{
	   		set_temp += 100;
	   	}
	}
	else if (Thr_state == 0x02)
	{
		if (set_temp%100/10 == 9)
	   	{
	   		set_temp = set_temp-90;
	   	}
	   	else
	   	{
	   		set_temp += 10;
	   	}
	}
	else if (Thr_state == 0x03)
	{
	   	if (set_temp%10 == 9)
	   	{
	   		set_temp = set_temp-9;
	   	}
	   	else
	   	{
	   		set_temp ++;
	   	}
	}
	else
	__no_operation();
}


/*
 * function name:System_Initial()
 * description: Initialize the system. include I/O, LCD and ADS1118.
 */
void System_Initial()
{
	flag  = 0;		//reset flag

	Thr_state = 0;  //threshold temperature setting state machine counter
	time_state = 0;	//time setting state machine counter
	Thr_temp = 100; //configure threshold temperature to 100;
	Act_temp = 250;

	// IO initial
	P1OUT = 0x09;
	P2OUT = 0x3F;

	LCD_init();						// LCD initial
	LCD_clear();					// LCD clear
	LCD_display_string(0,"TH:");	// display "ADS1118"
	LCD_display_time(0,8,time);		// display current time
	LCD_display_string(1,"Temp:        CH1");	// display threshold temp and actual temp;
	LCD_display_char(1,10,0xDF);
	LCD_display_char(1,11,'C');
	LCD_display_number(0,3,Thr_temp);// display threshold temp number

	ADS_Config(0); 					// set ADS1118 to convert local temperature, and start convertion.
}
