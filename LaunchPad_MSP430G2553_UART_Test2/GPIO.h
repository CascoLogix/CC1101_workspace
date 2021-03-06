/*****************************************************************************/
//	gpio.h
//  
//	 Created on: Mar 24, 2010
//	     Author: Clint Stevenson
//
/*****************************************************************************/


#ifndef GPIO_H
#define GPIO_H


/*****************************************************************************/
//	Includes
/*****************************************************************************/
#include <msp430.h>
#include <stdint.h>
/*****************************************************************************/
//	End Includes


/*****************************************************************************/
//	Defines
/*****************************************************************************/
/*****************************************************************************/
//	End Defines


/*****************************************************************************/
//	Public Typedef Declarations (extern)
/*****************************************************************************/
#if !defined (__MSP430_HAS_PORTA_R__) && \
	(defined (__MSP430_HAS_PORT1_R__) || defined (__MSP430_HAS_PORT2_R__))
typedef struct {
	uint8_t in;
	//const uint8_t DNU1;	// MSP430G2553 uses 8-bit registers
	uint8_t out;
	//const uint8_t DNU2;	// MSP430G2553 uses 8-bit registers
	uint8_t direction;
	//const uint8_t DNU3;	// MSP430G2553 uses 8-bit registers
	uint8_t interrupt_flag;
	//const uint8_t DNU4;	// MSP430G2553 uses 8-bit registers
	uint8_t interrupt_edge_select;
	//const uint8_t DNU5;	// MSP430G2553 uses 8-bit registers
	uint8_t interrupt_enable;
	//const uint8_t DNU6;	// MSP430G2553 uses 8-bit registers
	uint8_t select;
	//const uint8_t DNU7;	// MSP430G2553 uses 8-bit registers
	uint8_t resistor_enable;
	const uint8_t DNU8[25];
	uint8_t select_2;			// Non-contiguous address
} port_type_int_t, port1_t, port2_t;


#elif defined (__MSP430_HAS_PORTA_R__)
typedef struct {
	uint8_t in;
	const uint8_t DNU1;
	uint8_t out;
	const uint8_t DNU2;
	uint8_t direction;
	const uint8_t DNU3;
	uint8_t resistor_enable;
	const uint8_t DNU4;
	uint8_t drive_strength;
	const uint8_t DNU5;
	uint8_t select;
	const uint8_t DNU6[13];
	uint8_t interrupt_edge_select;
	const uint8_t DNU7;
	uint8_t interrupt_enable;
	const uint8_t DNU8;
	uint8_t interrupt_flag;
} port_type_int_t, port1_t, port2_t;
#endif

#if defined (__MSP430_HAS_PORT3_R__) ||defined (__MSP430_HAS_PORT4_R__) || \
	defined (__MSP430_HAS_PORT5_R__) ||defined (__MSP430_HAS_PORT6_R__) || \
	defined (__MSP430_HAS_PORT7_R__) ||defined (__MSP430_HAS_PORT8_R__) || \
	defined (__MSP430_HAS_PORT9_R__) ||defined (__MSP430_HAS_PORT10_R__) || \
	defined (__MSP430_HAS_PORT11_R__) ||defined (__MSP430_HAS_PORT12_R__)
typedef struct {
	uint8_t in;
	const uint8_t DNU1;
	uint8_t out;
	const uint8_t DNU2;
	uint8_t direction;
	const uint8_t DNU3;
	uint8_t resistor_enable;
	const uint8_t DNU4;
	uint8_t drive_strength;
	const uint8_t DNU5;
	uint8_t select;
} port_type_std_t, port3_t, port4_t, port5_t, port6_t, port7_t, port8_t,
	port9_t, port10_t, port11_t, port12_t;
#endif


#if defined (__MSP430_HAS_PORTJ_R__)
typedef struct {
	uint8_t in;
	const uint8_t DNU1;
	uint8_t out;
	const uint8_t DNU2;
	uint8_t direction;
	const uint8_t DNU3;
	uint8_t resistor_enable;
	const uint8_t DNU4;
	uint8_t drive_strength;
} port_type_JTAG_t, portJ_t;
#endif
/*****************************************************************************/
//	End Public Typedef Declarations


/*****************************************************************************/
//	Public Constant Declarations (extern)
/*****************************************************************************/
#if defined (__MSP430_HAS_PORT1_R__)
extern port1_t volatile * const p_PORT1;
#define GPIO_PORT1		(*p_PORT1)
#endif

#if defined (__MSP430_HAS_PORT2_R__)
extern port2_t volatile * const p_PORT2;
#define GPIO_PORT2		(*p_PORT2)
#endif

#if defined (__MSP430_HAS_PORT3_R__)
extern port3_t volatile * const p_PORT3;
#define GPIO_PORT3		(*p_PORT3)
#endif

#if defined (__MSP430_HAS_PORT4_R__)
extern port4_t volatile * const p_PORT4;
#define GPIO_PORT4		(*p_PORT4)
#endif

#if defined (__MSP430_HAS_PORT5_R__)
extern port5_t volatile * const p_PORT5;
#define GPIO_PORT5		(*p_PORT5)
#endif

#if defined (__MSP430_HAS_PORT6_R__)
extern port6_t volatile * const p_PORT6;
#define GPIO_PORT6		(*p_PORT6)
#endif

#if defined (__MSP430_HAS_PORT7_R__)
extern port7_t volatile * const p_PORT7;
#define GPIO_PORT7		(*p_PORT7)
#endif

#if defined (__MSP430_HAS_PORT8_R__)
extern port8_t volatile * const p_PORT8;
#define GPIO_PORT8		(*p_PORT8)
#endif

#if defined (__MSP430_HAS_PORT9_R__)
extern port9_t volatile * const p_PORT9;
#define GPIO_PORT9		(*p_PORT9)
#endif

#if defined (__MSP430_HAS_PORT10_R__)
extern port10_t volatile * const p_PORT10;
#define GPIO_PORT10		(*p_PORT10)
#endif

#if defined (__MSP430_HAS_PORT11_R__)
extern port11_t volatile * const p_PORT11;
#define GPIO_PORT11		(*p_PORT11)
#endif

#if defined (__MSP430_HAS_PORT12_R__)
extern port12_t volatile * const p_PORT12;
#define GPIO_PORT12		(*p_PORT12)
#endif

#if defined (__MSP430_HAS_PORTJ_R__)
extern portJ_t volatile * const p_PORTJ;
#define GPIO_PORTJ		(*p_PORTJ)
#endif
/*****************************************************************************/
//	End Public Constant Declarations


/*****************************************************************************/
//	Public Variable Declarations (extern)
/*****************************************************************************/

/*****************************************************************************/
//	End Public Variable Declarations


/*****************************************************************************/
//	Public Function Prototypes (extern)
/*****************************************************************************/
extern void gpio_all_ports_init (void);
#if defined (__MSP430_HAS_PORT1_R__)
extern void gpio_port1_init (void);
#endif
#if defined (__MSP430_HAS_PORT2_R__)
extern void gpio_port2_init (void);
#endif
#if defined (__MSP430_HAS_PORT3_R__)
extern void gpio_port3_init (void);
#endif
#if defined (__MSP430_HAS_PORT4_R__)
extern void gpio_port4_init (void);
#endif
#if defined (__MSP430_HAS_PORT5_R__)
extern void gpio_port5_init (void);
#endif
#if defined (__MSP430_HAS_PORT6_R__)
extern void gpio_port6_init (void);
#endif
#if defined (__MSP430_HAS_PORT7_R__)
extern void gpio_port7_init (void);
#endif
#if defined (__MSP430_HAS_PORT8_R__)
extern void gpio_port8_init (void);
#endif
#if defined (__MSP430_HAS_PORT9_R__)
extern void gpio_port9_init (void);
#endif
#if defined (__MSP430_HAS_PORT10_R__)
extern void gpio_port10_init (void);
#endif
#if defined (__MSP430_HAS_PORT11_R__)
extern void gpio_port11_init (void);
#endif
#if defined (__MSP430_HAS_PORT12_R__)
extern void gpio_port12_init (void);
#endif
#if defined (__MSP430_HAS_PORTJ_R__)
extern void gpio_portJ_init (void);
#endif
/*****************************************************************************/
//	End Public Function Prototypes


/* Memory-mapped IO from linker file
00000200   PAIN		  00000220   PBIN    	00000240   PCIN       00000260   PDIN       00000280   PEIN       000002a0   PFIN       00000320   PJIN
00000200   PAIN_L	  00000220   PBIN_L     00000240   PCIN_L     00000260   PDIN_L     00000280   PEIN_L     000002a0   PFIN_L     00000320   PJIN_L
00000201   PAIN_H	  00000221   PBIN_H     00000241   PCIN_H     00000261   PDIN_H     00000281   PEIN_H     000002a1   PFIN_H     00000321   PJIN_H
00000202   PAOUT	  00000222   PBOUT      00000242   PCOUT      00000262   PDOUT      00000282   PEOUT      000002a2   PFOUT      00000322   PJOUT
00000202   PAOUT_L	  00000222   PBOUT_L    00000242   PCOUT_L    00000262   PDOUT_L    00000282   PEOUT_L    000002a2   PFOUT_L    00000322   PJOUT_L
00000203   PAOUT_H	  00000223   PBOUT_H    00000243   PCOUT_H    00000263   PDOUT_H    00000283   PEOUT_H    000002a3   PFOUT_H    00000323   PJOUT_H
00000204   PADIR	  00000224   PBDIR      00000244   PCDIR      00000264   PDDIR      00000284   PEDIR      000002a4   PFDIR      00000324   PJDIR
00000204   PADIR_L	  00000224   PBDIR_L    00000244   PCDIR_L    00000264   PDDIR_L    00000284   PEDIR_L    000002a4   PFDIR_L    00000324   PJDIR_L
00000205   PADIR_H	  00000225   PBDIR_H    00000245   PCDIR_H    00000265   PDDIR_H    00000285   PEDIR_H    000002a5   PFDIR_H    00000325   PJDIR_H
00000206   PAREN	  00000226   PBREN      00000246   PCREN      00000266   PDREN      00000286   PEREN      000002a6   PFREN      00000326   PJREN
00000206   PAREN_L	  00000226   PBREN_L    00000246   PCREN_L    00000266   PDREN_L    00000286   PEREN_L    000002a6   PFREN_L    00000326   PJREN_L
00000207   PAREN_H	  00000227   PBREN_H    00000247   PCREN_H    00000267   PDREN_H    00000287   PEREN_H    000002a7   PFREN_H    00000327   PJREN_H
00000208   PADS		  00000228   PBDS    	00000248   PCDS       00000268   PDDS       00000288   PEDS       000002a8   PFDS       00000328   PJDS
00000208   PADS_L	  00000228   PBDS_L     00000248   PCDS_L     00000268   PDDS_L     00000288   PEDS_L     000002a8   PFDS_L     00000328   PJDS_L
00000209   PADS_H	  00000229   PBDS_H     00000249   PCDS_H     00000269   PDDS_H     00000289   PEDS_H     000002a9   PFDS_H     00000329   PJDS_H
0000020a   PASEL	  0000022a   PBSEL      0000024a   PCSEL      0000026a   PDSEL      0000028a   PESEL      000002aa   PFSEL
0000020a   PASEL_L	  0000022a   PBSEL_L    0000024a   PCSEL_L    0000026a   PDSEL_L    0000028a   PESEL_L    000002aa   PFSEL_L
0000020b   PASEL_H	  0000022b   PBSEL_H    0000024b   PCSEL_H    0000026b   PDSEL_H    0000028b   PESEL_H    000002ab   PFSEL_H
0000020e   P1IV
00000218   PAIES
00000218   PAIES_L
00000219   PAIES_H
0000021a   PAIE
0000021a   PAIE_L
0000021b   PAIE_H
0000021c   PAIFG
0000021c   PAIFG_L
0000021d   PAIFG_H
0000021e   P2IV
*/


#endif /* GPIO_H */
