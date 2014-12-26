/*****************************************************************************/
//	USCI.h
//  
//	 Created on:
//	     Author:
//
/*****************************************************************************/


// TODO:
// - Remove all other modules other than USCI
// - Make a separate code module for each USCI module (i.e. USCI, USCI_Ax,
//     USCI_Bx
// - Expose public function prototypes


#ifndef USCI_H_
#define USCI_H_


/*****************************************************************************/
//	Includes
/*****************************************************************************/
#include <msp430.h>
#include <stdint.h>
#include <GPIO.h>		// Dependent on GPIO for setting port settings for USCI
#include <USCI_config.h>
//#include <cassert>
/*****************************************************************************/
//	End Includes


/*****************************************************************************/
//	Defines
/*****************************************************************************/
// The following mode defines are used by the application to select which mode
//	to initialize the USCI.
#define USCI_A0_CLK_SRC_UC0CLK		0
#define USCI_A0_CLK_SRC_ACLK		1
#define USCI_A0_CLK_SRC_SMCLK		2
/*****************************************************************************/
//	End Defines


/*****************************************************************************/
//	Public Constant Declarations (extern)
/*****************************************************************************/
//Put public variable declarations here
/*****************************************************************************/
//	End Public Constant Declarations


/*****************************************************************************/
//	Public Variable Declarations (extern)
/*****************************************************************************/
//Put public variable declarations here
/*****************************************************************************/
//	End Public Variable Declarations


/*****************************************************************************/
//	Public Typedef Declarations (extern)
/*****************************************************************************/
/*****************************************************************************/
//	Struct Overlay Declarations for Peripheral Register Access
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*	USCI Struct Type Defines for Struct Overlays							 */
/*                                                                           */
/*****************************************************************************/
typedef struct {

} USCI_Ax_UART_config_t;

#if defined (__MSP430_HAS_USCI_A0__) || \
	defined (__MSP430_HAS_USCI_A1__) || \
	defined (__MSP430_HAS_USCI_A2__) || \
	defined (__MSP430_HAS_USCI_A3__) || \
	defined (__MSP430_HAS_USCI_B0__) || \
	defined (__MSP430_HAS_USCI_B1__) || \
	defined (__MSP430_HAS_USCI_B2__) || \
	defined (__MSP430_HAS_USCI_B3__) || \
	defined (__MSP430_HAS_USCI_AB0__) || \
	defined (__MSP430_HAS_USCI_AB1__) || \
	defined (__MSP430_HAS_USCI_AB2__) || \
	defined (__MSP430_HAS_USCI_AB3__)
// (refer to MSP430x5xx Family User's Guide)
typedef struct {
	uint8_t control_1;
	uint8_t control_0;
	const uint8_t _DNU1[4];
	uint8_t baud_rate_control_0;
	uint8_t baud_rate_control_1;
	uint8_t modulation_control;
	const uint8_t _DNU2;
	uint8_t status_register;
	const uint8_t _DNU3;
	uint8_t receive_buffer;
	const uint8_t _DNU4;
	uint8_t transmit_buffer;
	const uint8_t _DNU5;
	uint8_t auto_baud_control;
	const uint8_t _DNU6;
	uint8_t IrDA_transmit_control;
	uint8_t IrDA_receive_control;
	const uint8_t _DNU7[8];
	uint8_t interrupt_enable;
	uint8_t interrupt_flag;
	uint8_t interrupt_vector;
} USCI_control_t;

#elif defined (__MSP430_HAS_USCI__)
// (refer to MSP430x2xx Family User's Guide)
typedef struct {
	uint8_t auto_baud_control;
	uint8_t IrDA_transmit_control;
	uint8_t IrDA_receive_control;
	uint8_t control_0;
	uint8_t control_1;
	uint8_t baud_rate_control_0;
	uint8_t baud_rate_control_1;
	uint8_t modulation_control;
	uint8_t status_register;
	uint8_t receive_buffer;
	uint8_t transmit_buffer;
} USCI_UART_control_t;

typedef struct {
	uint8_t control_0;
	uint8_t control_1;
	uint8_t bit_rate_control_0;
	uint8_t bit_rate_control_1;
	uint8_t modulation_control;		// Note: not used in USCI_B module
	uint8_t status_register;
	uint8_t receive_buffer;
	uint8_t transmit_buffer;
} USCI_SPI_control_t;

typedef struct {
	uint8_t control_0;
	uint8_t control_1;
	uint8_t baud_rate_control_0;
	uint8_t baud_rate_control_1;
	uint8_t interrupt_enable;
	uint8_t status_register;
	uint8_t receive_buffer;
	uint8_t transmit_buffer;
	uint8_t const unused[168];
	uint16_t own_address;
	uint16_t slave_address;
} USCI_I2C_control_t;

// TODO:
// - Need to add another struct, as USCI_B module does not have the first three
//    registers as shown above.
#endif


#if defined (__MSP430_HAS_USCI_AB0__) || \
		defined (__MSP430_HAS_USCI_AB1__) || \
		defined (__MSP430_HAS_USCI_AB2__) || \
		defined (__MSP430_HAS_USCI_AB3__) || \
		defined (__MSP430_HAS_USCI_A0__) || \
		defined (__MSP430_HAS_USCI_A1__) || \
		defined (__MSP430_HAS_USCI_A2__) || \
		defined (__MSP430_HAS_USCI_A3__) || \
		defined (__MSP430_HAS_USCI_B0__) || \
		defined (__MSP430_HAS_USCI_B1__) || \
		defined (__MSP430_HAS_USCI_B2__) || \
		defined (__MSP430_HAS_USCI_B3__)
typedef struct {
	uint8_t enable_1;
	uint8_t enable_2;
	uint8_t flag_1;
	uint8_t flag_2;
} USCI_interrupt_t;

#elif defined (__MSP430_HAS_USCI__)
typedef struct {
	uint8_t enable_1;
	uint8_t enable_2;
	uint8_t flag_1;
	uint8_t flag_2;
	uint8_t Ax_Bx_interrupt_enable;
	uint8_t Ax_Bx_interrupt_flag;
} USCI_interrupt_t;
#endif
/*****************************************************************************/
/*                                                                           */
/*	END: USCI Struct Type Defines for Struct Overlays						 */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
//	Constant Struct Overlay Declarations
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*	USCI Struct Overlay Declaration 										 */
/*                                                                           */
/*****************************************************************************/
#if defined (__MSP430_HAS_USCI__)
// Peripheral Control
// Declare pointer to struct overlay for the USCI_A0 peripheral
#if defined (__USING_USCI_A0_UART_MODE__)
extern USCI_UART_control_t volatile * const p_USCI_A0_UART_CONTROL;
#define USCI_A0_UART_CONTROL		(*p_USCI_A0_UART_CONTROL)
#endif /* defined (__USING_USCI_A0_UART_MODE__) */

#if defined (__USING_USCI_A0_IRDA_MODE__)
#error "USCI_A0 IrDA mode not defined yet"
#endif /* defined (__USING_USCI_A0_IRDA_MODE__) */

#if defined (__USING_USCI_A0_LIN_MODE__)
#error "USCI_A0 LIN mode not defined yet"
#endif /* defined (__USING_USCI_A0_LIN_MODE__) */

#if defined (__USING_USCI_A0_SPI_MODE__)
extern USCI_SPI_control_t volatile * const p_USCI_A0_SPI_CONTROL;
#define USCI_A0_SPI_CONTROL		(*p_USCI_A0_SPI_CONTROL)
#endif /* defined (__USING_USCI_A0_SPI_MODE__) */

// Declare pointer to struct overlay for the USCI_B0 peripheral
#if defined (__USING_USCI_B0_SPI_MODE__)
extern USCI_SPI_control_t volatile * const p_USCI_B0_SPI_CONTROL;
#define USCI_B0_SPI_CONTROL		(*p_USCI_B0_SPI_CONTROL)
#endif /* defined (__USING_USCI_B0_SPI_MODE__) */

#if defined (__USING_USCI_B0_I2C_MODE__)
extern USCI_I2C_control_t volatile * const p_USCI_B0_I2C_CONTROL;
#define USCI_B0_I2C_CONTROL		(*p_USCI_B0_I2C_CONTROL)
#endif /* defined (__USING_USCI_B0_I2C_MODE__) */

// Interrupt Control
extern USCI_interrupt_t volatile * const p_USCI_INTERRUPT;
#define USCI_INTERRUPT	(*p_USCI_INTERRUPT)
#endif /* (defined (__MSP430_HAS_USCI__) */
/*****************************************************************************/
/*                                                                           */
/*	END: USCI Struct Overlay Declaration									 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
//	END: Struct Overlay Declarations for Peripheral Register Access


/*****************************************************************************/
//	Macro Definitions
/*****************************************************************************/
#if defined (__USCI_ENABLE_MACROS__)
// USCI_A0 UART register manipulation macros
#define USCI_A0_UART_enable_TX_interrupt() 		(USCI_INTERRUPT.enable_2 |= USCI_TX_IE_BIT)
#define USCI_A0_UART_disable_TX_interrupt() 	(USCI_INTERRUPT.enable_2 &= ~USCI_TX_IE_BIT)
#define USCI_A0_UART_enable_RX_interrupt() 		(USCI_INTERRUPT.enable_2 |= USCI_RX_IE_BIT)
#define USCI_A0_UART_disable_RX_interrupt() 	(USCI_INTERRUPT.enable_2 &= ~USCI_RX_IE_BIT)
#define USCI_A0_UART_clear_TX_interrupt_flag() 	(USCI_INTERRUPT.flag_2 &= ~USCI_TX_INTERRUPT_FLAG)
#define USCI_A0_UART_write_TX_buffer(a) 		(USCI_A0_UART_CONTROL.transmit_buffer = a)
#define USCI_A0_UART_clear_RX_interrupt_flag() 	(USCI_INTERRUPT.flag_2 &= ~USCI_RX_INTERRUPT_FLAG)
#define USCI_A0_UART_read_RX_buffer() 			(USCI_A0_UART_CONTROL.receive_buffer)
#define USCI_A0_UART_read_busy_flag() 			(USCI_A0_UART_CONTROL.status_register & USCI_BUSY_FLAG)

// USCI_B0 SPI register manipulation macros
#define USCI_B0_SPI_phase_change_then_latch() 	(USCI_B0_SPI_CONTROL.control_0 |= UCCKPH)
#define USCI_B0_SPI_phase_latch_then_change() 	(USCI_B0_SPI_CONTROL.control_0 &= ~UCCKPL)
#define USCI_B0_SPI_polarity_idle_low() 		(USCI_B0_SPI_CONTROL.control_0 |= UCCKPL)
#define USCI_B0_SPI_polarity_idle_high() 		(USCI_B0_SPI_CONTROL.control_0 &= ~UCCKPL)
#define USCI_B0_SPI_bit_order_MSB()				(USCI_B0_SPI_CONTROL.control_0 |= UCMSB)
#define USCI_B0_SPI_bit_order_LSB()				(USCI_B0_SPI_CONTROL.control_0 &= ~UCMSB)
#define USCI_B0_SPI_set_slave()                 (USCI_B0_SPI_CONTROL.control_0 |= UCMST)
#define USCI_B0_SPI_set_master()                (USCI_B0_SPI_CONTROL.control_0 &= ~UCMST)
#define USCI_B0_SPI_set_mode(a)					(USCI_B0_SPI_CONTROL.control_0 &= ~(UCMODE1 | UCMODE0); USCI_B0_SPI_CONTROL.control_0 |= (a & (UCMODE1 | UCMODE0))
#define USCI_B0_SPI_set_clock_src(a)			(USCI_B0_SPI_CONTROL.control_1 &= ~(UCSSEL1 | UCSSEL0); USCI_B0_SPI_CONTROL.control_1 |= (a & (UCSSEL1 | UCSSEL0))
#define USCI_B0_SPI_get_busy_status()			(USCI_B0_SPI_CONTROL.status_register & UCBUSY)
#define USCI_B0_SPI_get_framing_error_flag()	(USCI_B0_SPI_CONTROL.status_register & UCFE)
#define USCI_B0_SPI_get_overrun_error_flag()	(USCI_B0_SPI_CONTROL.status_register & UCOE)
#define USCI_B0_SPI_read_RX_buffer()			(USCI_B0_SPI_CONTROL.receive_buffer)
#define USCI_B0_SPI_write_TX_buffer(a)			(USCI_B0_SPI_CONTROL.transmit_buffer = a)
#define USCI_B0_SPI_get_RX_int_en()				(USCI_INTERRUPT.Ax_Bx_interrupt_enable & UCB0RXIE)
#define USCI_B0_SPI_set_RX_int_en()				(USCI_INTERRUPT.Ax_Bx_interrupt_enable |= UCB0RXIE)
#define USCI_B0_SPI_clr_RX_int_en()				(USCI_INTERRUPT.Ax_Bx_interrupt_enable &= ~UCB0RXIE)
#define USCI_B0_SPI_get_TX_int_en()             (USCI_INTERRUPT.Ax_Bx_interrupt_enable & UCB0TXIE)
#define USCI_B0_SPI_set_TX_int_en()             (USCI_INTERRUPT.Ax_Bx_interrupt_enable |= UCB0TXIE)
#define USCI_B0_SPI_clr_TX_int_en()             (USCI_INTERRUPT.Ax_Bx_interrupt_enable &= ~UCB0TXIE)
#define USCI_B0_SPI_get_RX_int_flag()           (USCI_INTERRUPT.Ax_Bx_interrupt_enable & UCB0RXIFG)
#define USCI_B0_SPI_set_RX_int_flag()           (USCI_INTERRUPT.Ax_Bx_interrupt_enable |= UCB0RXIFG)
#define USCI_B0_SPI_clr_RX_int_flag()           (USCI_INTERRUPT.Ax_Bx_interrupt_enable &= ~UCB0RXIFG)
#define USCI_B0_SPI_get_TX_int_flag()           (USCI_INTERRUPT.Ax_Bx_interrupt_enable & UCB0TXIFG)
#define USCI_B0_SPI_set_TX_int_flag()           (USCI_INTERRUPT.Ax_Bx_interrupt_enable |= UCB0TXIFG)
#define USCI_B0_SPI_clr_TX_int_flag()           (USCI_INTERRUPT.Ax_Bx_interrupt_enable &= ~UCB0TXIFG)
#endif /* defined (__USCI_ENABLE_MACROS__) */
/*****************************************************************************/
//	END: Macro Definitions


/*****************************************************************************/
//	Function Prototypes
/*****************************************************************************/
/*****************************************************************************/
/*                                                                           */
/*	USCI Function Prototypes												 */
/*                                                                           */
/*****************************************************************************/
#if defined (__MSP430_HAS_USCI__)
#if defined (__MSP430G2553__)
#if defined (__USING_USCI_A0_UART_MODE__)
void USCI_A0_init_UART (uint16_t baud_rate, uint8_t clk_source);
#endif /* defined (__USING_USCI_A0_UART_MODE__) */

#if defined (__USING_USCI_A0_SPI_MODE__)
void USCI_A0_init_SPI (uint16_t clock_div, uint8_t clk_source);
#endif /* defined (__USING_USCI_A0_SPI_MODE__) */

#if defined (__USING_USCI_B0_SPI_MODE__)
void USCI_B0_init_SPI (uint16_t clock_div, uint8_t clk_source);
#endif /* defined (__USING_USCI_B0_SPI_MODE__) */

#if defined (__USING_USCI_B0_I2C_MODE__)
void USCI_B0_init_I2C (uint16_t clock_div, uint8_t clk_source,
						uint8_t bus_role, uint16_t address);
#endif /* defined (__USING_USCI_B0_I2C_MODE__) */
#endif // defined (__MSP430G2553__)

#if !defined (__USCI_ENABLE_MACROS__)
void USCI_disable_TX_interrupt (void);
void USCI_enable_TX_interrupt (void);
void USCI_disable_RX_interrupt (void);
void USCI_enable_RX_interrupt (void);
void USCI_clear_TX_interrupt_flag (void);
void USCI_clear_RX_interrupt_flag (void);
void USCI_write_TX_buffer (uint8_t data);
uint8_t USCI_read_RX_buffer (void);
uint8_t USCI_read_busy_flag (void);

void USCI_B0_SPI_phase_change_then_latch (void);
void USCI_B0_SPI_phase_latch_then_change (void);
void USCI_B0_SPI_polarity_idle_low (void);
void USCI_B0_SPI_polarity_idle_high (void);
void USCI_B0_SPI_bit_order_MSB (void);
void USCI_B0_SPI_bit_order_LSB (void);
void USCI_B0_SPI_set_slave (void);
void USCI_B0_SPI_set_master (void);
void USCI_B0_SPI_set_mode (uint8_t mode);
void USCI_B0_SPI_set_clock_src (uint8_t mode);
uint8_t USCI_B0_SPI_get_busy_status (void);
uint8_t USCI_B0_SPI_get_framing_error_flag (void);
uint8_t USCI_B0_SPI_get_overrun_error_flag (void);
uint8_t USCI_B0_SPI_read_RX_buffer (void);
void USCI_B0_SPI_write_TX_buffer (uint8_t data);
uint8_t USCI_B0_SPI_get_RX_int_en (void);
void USCI_B0_SPI_set_RX_int_en (void);
void USCI_B0_SPI_clr_RX_int_en (void);
uint8_t USCI_B0_SPI_get_TX_int_en (void);
void USCI_B0_SPI_set_TX_int_en (void);
void USCI_B0_SPI_clr_TX_int_en (void);
uint8_t USCI_B0_SPI_get_RX_int_flag (void);
void USCI_B0_SPI_set_RX_int_flag (void);
void USCI_B0_SPI_clr_RX_int_flag (void);
uint8_t USCI_B0_SPI_get_TX_int_flag (void);
void USCI_B0_SPI_set_TX_int_flag (void);
void USCI_B0_SPI_clr_TX_int_flag (void);
#endif /* defined (__USCI_ENABLE_MACROS__) */
#endif /* __MSP430_HAS_USCI__ */
/*****************************************************************************/
/*                                                                           */
/*	END: USCI Function Prototypes											 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
//	End Function Prototypes


#endif /* USCI_H_ */
