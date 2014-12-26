/*****************************************************************************/
//	gpio.c
//  
//	 Created on: Mar 24, 2010
//	     Author: Clint Stevenson
//
/*****************************************************************************/


/*****************************************************************************/
//	Includes
/*****************************************************************************/
#include <GPIO.h>
/*****************************************************************************/
//	End Includes


/*****************************************************************************/
//	Defines
/*****************************************************************************/
#if defined (__MSP430G2553)
#define GPIO_PORT1_SELECT_2_ADDRESS_OFFSET								0x21
#define GPIO_PORT2_SELECT_2_ADDRESS_OFFSET								0x1A
#define GPIO_PORT3_SELECT_2_ADDRESS_OFFSET								0x2B
#define GPIO_PORT3_RESISTOR_ENABLE_ADDRESS								0x10

#define GPIO_PORT1_BASE_ADDRESS											0x20
#define GPIO_PORT2_BASE_ADDRESS											0x28
#define GPIO_PORT3_BASE_ADDRESS											0x18

#elif defined (__MSP430F2112)
#define GPIO_PORT1_SELECT_2_ADDRESS_OFFSET								0x21
#define GPIO_PORT2_SELECT_2_ADDRESS_OFFSET								0x1A
#define GPIO_PORT3_SELECT_2_ADDRESS_OFFSET								0x2B
#define GPIO_PORT3_RESISTOR_ENABLE_ADDRESS								0x10

#define GPIO_PORT1_BASE_ADDRESS											0x20
#define GPIO_PORT2_BASE_ADDRESS											0x28
#define GPIO_PORT3_BASE_ADDRESS											0x18

#elif defined (__MSP430F2618__)
#define GPIO_PORT1_SELECT_2_ADDRESS_OFFSET								0x21
#define GPIO_PORT2_SELECT_2_ADDRESS_OFFSET								0x21
#define GPIO_PORT3_SELECT_2_ADDRESS_OFFSET								0x21
#define GPIO_PORT3_RESISTOR_ENABLE_ADDRESS								0x10

#define GPIO_PORT1_BASE_ADDRESS											0x20
#define GPIO_PORT2_BASE_ADDRESS											0x28
#define GPIO_PORT3_BASE_ADDRESS											0x18
#define GPIO_PORT4_BASE_ADDRESS											0x1C
#define GPIO_PORT5_BASE_ADDRESS											0x30
#define GPIO_PORT6_BASE_ADDRESS											0x34
#define GPIO_PORT7_BASE_ADDRESS											0x38
#define GPIO_PORT8_BASE_ADDRESS											0x39
#define GPIO_PORTA_BASE_ADDRESS											0x38

#elif defined (__MSP430F5438A__) || \
	  defined (__MSP430F5438__)
#define GPIO_PORT1_SELECT_2_ADDRESS_OFFSET								((&P1SEL) - (&P1IN))
#define GPIO_PORT2_SELECT_2_ADDRESS_OFFSET								((&P2SEL) - (&P2IN))
#define GPIO_PORT3_SELECT_2_ADDRESS_OFFSET								((&P3SEL) - (&P3IN))
#define GPIO_PORT3_RESISTOR_ENABLE_ADDRESS								(&P3REN)

#define GPIO_PORT1_BASE_ADDRESS											(&P1IN)
#define GPIO_PORT2_BASE_ADDRESS											(&P2IN)
#define GPIO_PORT3_BASE_ADDRESS											(&P3IN)
#define GPIO_PORT4_BASE_ADDRESS											(&P4IN)
#define GPIO_PORT5_BASE_ADDRESS											(&P5IN)
#define GPIO_PORT6_BASE_ADDRESS											(&P6IN)
#define GPIO_PORT7_BASE_ADDRESS											(&P7IN)
#define GPIO_PORT8_BASE_ADDRESS											(&P8IN)
#define GPIO_PORT9_BASE_ADDRESS											(&P9IN)
#define GPIO_PORT10_BASE_ADDRESS										(&P10IN)
#define GPIO_PORT11_BASE_ADDRESS										(&P11IN)
#define GPIO_PORT12_BASE_ADDRESS										(&P12IN)
#define GPIO_PORTJ_BASE_ADDRESS											(&PJIN)
#endif
/*****************************************************************************/
//	End Defines


/*****************************************************************************/
//	Constant Declarations
/*****************************************************************************/
#if defined (__MSP430_HAS_PORT1_R__)
port1_t volatile * const p_PORT1 =
		(port1_t*) GPIO_PORT1_BASE_ADDRESS;
//#define GPIO_PORT1		(*p_PORT1)
#endif

#if defined (__MSP430_HAS_PORT2_R__)
port2_t volatile * const p_PORT2 =
		(port2_t*) GPIO_PORT2_BASE_ADDRESS;
//#define GPIO_PORT2		(*p_PORT2)
#endif

#if defined (__MSP430_HAS_PORT3_R__)
port3_t volatile * const p_PORT3 =
		(port3_t*) GPIO_PORT3_BASE_ADDRESS;
//#define GPIO_PORT3		(*p_PORT3)
#endif

#if defined (__MSP430_HAS_PORT4_R__)
port4_t volatile * const p_PORT4 =
		(port4_t*) GPIO_PORT4_BASE_ADDRESS;
//#define GPIO_PORT4		(*p_PORT4)
#endif

#if defined (__MSP430_HAS_PORT5_R__)
port5_t volatile * const p_PORT5 =
		(port5_t*) GPIO_PORT5_BASE_ADDRESS;
//#define GPIO_PORT5		(*p_PORT5)
#endif

#if defined (__MSP430_HAS_PORT6_R__)
port6_t volatile * const p_PORT6 =
		(port6_t*) GPIO_PORT6_BASE_ADDRESS;
//#define GPIO_PORT6		(*p_PORT6)
#endif

#if defined (__MSP430_HAS_PORT7_R__)
port7_t volatile * const p_PORT7 =
		(port7_t*) GPIO_PORT7_BASE_ADDRESS;
//#define GPIO_PORT7		(*p_PORT7)
#endif

#if defined (__MSP430_HAS_PORT8_R__)
port8_t volatile * const p_PORT8 =
		(port8_t*) GPIO_PORT8_BASE_ADDRESS;
//#define GPIO_PORT8		(*p_PORT8)
#endif

#if defined (__MSP430_HAS_PORT9_R__)
port9_t volatile * const p_PORT9 =
		(port9_t*) GPIO_PORT9_BASE_ADDRESS;
//#define GPIO_PORT9		(*p_PORT9)
#endif

#if defined (__MSP430_HAS_PORT10_R__)
port10_t volatile * const p_PORT10 =
		(port10_t*) GPIO_PORT10_BASE_ADDRESS;
//#define GPIO_PORT10		(*p_PORT10)
#endif

#if defined (__MSP430_HAS_PORT11_R__)
port11_t volatile * const p_PORT11 =
		(port11_t*) GPIO_PORT11_BASE_ADDRESS;
//#define GPIO_PORT11		(*p_PORT11)
#endif

#if defined (__MSP430_HAS_PORT12_R__)
port12_t volatile * const p_PORT12 =
		(port12_t*) GPIO_PORT12_BASE_ADDRESS;
//#define GPIO_PORT12		(*p_PORT12)
#endif

#if defined (__MSP430_HAS_PORTJ_R__)
portJ_t volatile * const p_PORTJ =
		(portJ_t*) GPIO_PORTJ_BASE_ADDRESS;
//#define GPIO_PORTJ		(*p_PORTJ)
#endif
/*****************************************************************************/
//	End Constant Declarations


/*****************************************************************************/
//	Variable Declarations
/*****************************************************************************/
//Put Variable Declarations here
static functionPointer_t GPIO_PORT1_callback[8];
static functionPointer_t GPIO_PORT2_callback[8];
/*****************************************************************************/
//	End Variable Declarations


/*****************************************************************************/
//	Function Prototypes
/*****************************************************************************/
void gpio_all_ports_init (void);
#if defined (__MSP430_HAS_PORT1_R__)
void gpio_port1_init (void);
#endif
#if defined (__MSP430_HAS_PORT2_R__)
void gpio_port2_init (void);
#endif
#if defined (__MSP430_HAS_PORT3_R__)
void gpio_port3_init (void);
#endif
#if defined (__MSP430_HAS_PORT4_R__)
void gpio_port4_init (void);
#endif
#if defined (__MSP430_HAS_PORT5_R__)
void gpio_port5_init (void);
#endif
#if defined (__MSP430_HAS_PORT6_R__)
void gpio_port6_init (void);
#endif
#if defined (__MSP430_HAS_PORT7_R__)
void gpio_port7_init (void);
#endif
#if defined (__MSP430_HAS_PORT8_R__)
void gpio_port8_init (void);
#endif
#if defined (__MSP430_HAS_PORT9_R__)
void gpio_port9_init (void);
#endif
#if defined (__MSP430_HAS_PORT10_R__)
void gpio_port10_init (void);
#endif
#if defined (__MSP430_HAS_PORT11_R__)
void gpio_port11_init (void);
#endif
#if defined (__MSP430_HAS_PORT12_R__)
void gpio_port12_init (void);
#endif
#if defined (__MSP430_HAS_PORTJ_R__)
void gpio_portJ_init (void);
#endif
/*****************************************************************************/
//	End Function Prototypes


/*****************************************************************************/
//	Function Definitions
/*****************************************************************************/
void gpio_all_ports_init (void)
{
#if defined (__MSP430_HAS_PORT1_R__)
	gpio_port1_init();
#endif
#if defined (__MSP430_HAS_PORT2_R__)
	gpio_port2_init();
#endif
#if defined (__MSP430_HAS_PORT3_R__)
	gpio_port3_init();
#endif
#if defined (__MSP430_HAS_PORT4_R__)
	gpio_port4_init();
#endif
#if defined (__MSP430_HAS_PORT5_R__)
	gpio_port5_init();
#endif
#if defined (__MSP430_HAS_PORT6_R__)
	gpio_port6_init();
#endif
#if defined (__MSP430_HAS_PORT7_R__)
	gpio_port7_init();
#endif
#if defined (__MSP430_HAS_PORT8_R__)
	gpio_port8_init();
#endif
#if defined (__MSP430_HAS_PORT9_R__)
	gpio_port9_init();
#endif
#if defined (__MSP430_HAS_PORT10_R__)
	gpio_port10_init();
#endif
#if defined (__MSP430_HAS_PORT11_R__)
	gpio_port11_init();
#endif
#if defined (__MSP430_HAS_PORT12_R__)
	gpio_port12_init();
#endif
/*
#if defined (__MSP430_HAS_PORTJ_R__)
	gpio_portJ_init();
#endif
*/
}


#if defined (__MSP430_HAS_PORT1_R__)
void gpio_port1_init (void)
{
	GPIO_PORT1.out = 0;
	GPIO_PORT1.direction = 0;
	GPIO_PORT1.resistor_enable = 0;
	//GPIO_PORT1.drive_strength = 0;
	GPIO_PORT1.select = 0;
	GPIO_PORT1.interrupt_edge_select = 0;
	GPIO_PORT1.interrupt_flag = 0;
	GPIO_PORT1.interrupt_enable = 0;
}
#endif


#if defined (__MSP430_HAS_PORT2_R__)
void gpio_port2_init (void)
{
	GPIO_PORT2.out = 0;
	GPIO_PORT2.direction = 0;
	GPIO_PORT2.resistor_enable = 0;
	//GPIO_PORT2.drive_strength = 0;
	GPIO_PORT2.select = 0;
	GPIO_PORT2.interrupt_edge_select = 0;
	GPIO_PORT2.interrupt_enable = 0;
}
#endif


#if defined (__MSP430_HAS_PORT3_R__)
void gpio_port3_init (void)
{
	GPIO_PORT3.out = 0;
	GPIO_PORT3.direction = 0;
	GPIO_PORT3.select = 0;
	GPIO_PORT3.resistor_enable = 0;
	GPIO_PORT3.drive_strength = 0;
}
#endif


#if defined (__MSP430_HAS_PORT4_R__)
void gpio_port4_init (void)
{
	GPIO_PORT4.out = 0;
	GPIO_PORT4.direction = 0;
	GPIO_PORT4.select = 0;
	GPIO_PORT4.resistor_enable = 0;
	GPIO_PORT4.drive_strength = 0;
}
#endif


#if defined (__MSP430_HAS_PORT5_R__)
void gpio_port5_init (void)
{
	GPIO_PORT5.out = 0;
	GPIO_PORT5.direction = 0;
	GPIO_PORT5.select = 0;
	GPIO_PORT5.resistor_enable = 0;
	GPIO_PORT5.drive_strength = 0;
}
#endif


#if defined (__MSP430_HAS_PORT6_R__)
void gpio_port6_init (void)
{
	GPIO_PORT6.out = 0;
	GPIO_PORT6.direction = 0;
	GPIO_PORT6.select = 0;
	GPIO_PORT6.resistor_enable = 0;
	GPIO_PORT6.drive_strength = 0;
}
#endif


#if defined (__MSP430_HAS_PORT7_R__)
void gpio_port7_init (void)
{
	GPIO_PORT7.out = 0;
	GPIO_PORT7.direction = 0;
	GPIO_PORT7.select = 0;
	GPIO_PORT7.resistor_enable = 0;
	GPIO_PORT7.drive_strength = 0;
}
#endif


#if defined (__MSP430_HAS_PORT8_R__)
void gpio_port8_init (void)
{
	GPIO_PORT8.out = 0;
	GPIO_PORT8.direction = 0;
	GPIO_PORT8.select = 0;
	GPIO_PORT8.resistor_enable = 0;
	GPIO_PORT8.drive_strength = 0;
}
#endif


#if defined (__MSP430_HAS_PORT9_R__)
void gpio_port9_init (void)
{
	GPIO_PORT9.out = 0;
	GPIO_PORT9.direction = 0;
	GPIO_PORT9.select = 0;
	GPIO_PORT9.resistor_enable = 0;
	GPIO_PORT9.drive_strength = 0;
}
#endif


#if defined (__MSP430_HAS_PORT10_R__)
void gpio_port10_init (void)
{
	GPIO_PORT10.out = 0;
	GPIO_PORT10.direction = 0;
	GPIO_PORT10.select = 0;
	GPIO_PORT10.resistor_enable = 0;
	GPIO_PORT10.drive_strength = 0;
}
#endif


#if defined (__MSP430_HAS_PORT11_R__)
void gpio_port11_init (void)
{
	GPIO_PORT11.out = 0;
	GPIO_PORT11.direction = 0;
	GPIO_PORT11.select = 0;
	GPIO_PORT11.resistor_enable = 0;
	GPIO_PORT11.drive_strength = 0;
}
#endif


#if defined (__MSP430_HAS_PORT12_R__)
void gpio_port12_init (void)
{
	GPIO_PORT12.out = 0;
	GPIO_PORT12.direction = 0;
	GPIO_PORT12.select = 0;
	GPIO_PORT12.resistor_enable = 0;
	GPIO_PORT12.drive_strength = 0;
}
#endif


#if defined (__MSP430_HAS_PORTJ_R__)
void gpio_portJ_init (void)
{
	GPIO_PORTJ.out = 0;
	GPIO_PORTJ.direction = 0;
	GPIO_PORTJ.drive_strength = 0;
	GPIO_PORTJ.resistor_enable = 0;
}
#endif


void GPIO_PORT1_registerCallback (uint8_t portPinNum, functionPointer_t fPtr)
{
	GPIO_PORT1_callback[portPinNum] = fPtr;
}


#pragma vector = PORT1_VECTOR
__interrupt void GPIO_Port1_ISR (void)
{
	volatile uint8_t interruptSource;

	// Only look at enabled interrupt sources
	interruptSource = (GPIO_PORT1.interrupt_flag & GPIO_PORT1.interrupt_enable);

	switch (interruptSource)
	{
		case 0x01:
			GPIO_PORT1.interrupt_flag &= ~BIT0;			// Clear interrupt flag
			GPIO_PORT1_callback[0]();					// Call callback function
			break;

		case 0x02:
			GPIO_PORT1.interrupt_flag &= ~BIT1;			// Clear interrupt flag
			GPIO_PORT1_callback[1]();					// Call callback function
			break;

		case 0x04:
			GPIO_PORT1.interrupt_flag &= ~BIT2;			// Clear interrupt flag
			GPIO_PORT1_callback[2]();					// Call callback function
			break;

		case 0x08:
			GPIO_PORT1.interrupt_flag &= ~BIT3;			// Clear interrupt flag
			GPIO_PORT1_callback[3]();					// Call callback function
			break;

		case 0x10:
			GPIO_PORT1.interrupt_flag &= ~BIT4;			// Clear interrupt flag
			GPIO_PORT1_callback[4]();					// Call callback function
			break;

		case 0x20:
			GPIO_PORT1.interrupt_flag &= ~BIT5;			// Clear interrupt flag
			GPIO_PORT1_callback[5]();					// Call callback function
			break;

		case 0x40:
			GPIO_PORT1.interrupt_flag &= ~BIT6;			// Clear interrupt flag
			GPIO_PORT1_callback[6]();					// Call callback function
			break;

		case 0x80:
			GPIO_PORT1.interrupt_flag &= ~BIT7;			// Clear interrupt flag
			GPIO_PORT1_callback[7]();					// Call callback function
			break;

		default:
			GPIO_PORT1.interrupt_flag = 0;
			break;
	}
}


void GPIO_PORT2_registerCallback (uint8_t portPinNum, functionPointer_t fPtr)
{
	GPIO_PORT2_callback[portPinNum] = fPtr;
}


#pragma vector = PORT2_VECTOR
__interrupt void GPIO_Port2_ISR (void)
{
	switch (GPIO_PORT2.in)
	{
		case 0x01:
			GPIO_PORT2.interrupt_flag &= ~BIT0;			// Clear interrupt flag
			GPIO_PORT2_callback[0]();					// Call callback function
			break;

		case 0x02:
			GPIO_PORT2.interrupt_flag &= ~BIT1;			// Clear interrupt flag
			GPIO_PORT2_callback[1]();					// Call callback function
			break;

		case 0x04:
			GPIO_PORT2.interrupt_flag &= ~BIT2;			// Clear interrupt flag
			GPIO_PORT2_callback[2]();					// Call callback function
			break;

		case 0x08:
			GPIO_PORT2.interrupt_flag &= ~BIT3;			// Clear interrupt flag
			GPIO_PORT2_callback[3]();					// Call callback function
			break;

		case 0x10:
			GPIO_PORT2.interrupt_flag &= ~BIT4;			// Clear interrupt flag
			GPIO_PORT2_callback[4]();					// Call callback function
			break;

		case 0x20:
			GPIO_PORT2.interrupt_flag &= ~BIT5;			// Clear interrupt flag
			GPIO_PORT2_callback[5]();					// Call callback function
			break;

		case 0x40:
			GPIO_PORT2.interrupt_flag &= ~BIT6;			// Clear interrupt flag
			GPIO_PORT2_callback[6]();					// Call callback function
			break;

		case 0x80:
			GPIO_PORT2.interrupt_flag &= ~BIT7;			// Clear interrupt flag
			GPIO_PORT2_callback[7]();					// Call callback function
			break;

		default:
			GPIO_PORT2.interrupt_flag = 0;
			break;
	}
}
/*****************************************************************************/
//	End Function Definitions
