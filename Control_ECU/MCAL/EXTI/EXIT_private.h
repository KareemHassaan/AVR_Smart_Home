/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 22 Dec. 2021                                         *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef EXIT_PRIVATE_H
#define EXIT_PRIVATE_H


#define		MCUCR			*((volatile u8 *)0x55)	// MUC Control Register
#define		MCUCR_ISC00		0						// Interrupt 0 Signal Control Bit 0
#define		MCUCR_ISC01		1						// Interrupt 0 Signal Control Bit 1
#define		MCUCR_ISC10		2						// Interrupt 1 Signal Control Bit 0
#define		MCUCR_ISC11		3						// Interrupt 1 Signal Control Bit 1


#define		MCUCSR 			*((volatile u8 *)0x54)	// MCU Control and Status Register
#define		MCUCSR_ISC2		6						// Interrupt 2 Signal Control


#define		GICR 			*((volatile u8 *)0x5B)	// Interrupt Control Register
#define		GICR_INT2		5						// Interrupt 2 Enable
#define		GICR_INT0		6						// Interrupt 0 Enable
#define		GICR_INT1		7						// Interrupt 1 Enable


#define		GIFR			*((volatile u8 *)0x5A)	// Interrupt Flag Register
#define		GIFR_INTF2		5						// Interrupt 2 Flag
#define		GIFR_INTF0		6						// Interrupt 0 Flag
#define		GIFR_INTF1		7						// Interrupt 1 Flag




#define 	FALLING_EDGE	0
#define 	RISING_EDGE		1
#define		ON_CHANGE		2
#define		LOW_LEVEL		3


#endif
