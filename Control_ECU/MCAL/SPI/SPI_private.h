/***********************************************************************/
/*  !Author     :       Abdullah M. Abdullah                           */
/*  !Date       :       3 JAN, 2022                                    */
/*  !LAYER      :       MCAL                                           */
/*  !Version    :       v1.0                                           */
/***********************************************************************/
#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H


#define		SPCR		*((volatile u8 *)0x2D)		// SPI Control Register
#define		SPCR_SPR0	0							// SPI Prescaler Bit 0
#define		SPCR_SPR1	1							// SPI Prescaler Bit 1
#define		SPCR_CPHA	2							// SPI Clock Phase
#define		SPCR_CPOL	3							// SPI Clock Polarity
#define		SPCR_MSTR	4							// SPI Master Bit
#define		SPCR_DORD	5							// SPI Data Order
#define 	SPCR_SPE	6							// SPI Enable Bit
#define 	SPCR_SPIE	7							// SPI Interrupt Enable Bit


#define		SPSR		*((volatile u8 *)0x2E)		// SPI Status Register
#define		SPSR_SPI2X	0							// SPI Prescaler Bit 2
#define		SPSR_WCOL	6							// SPI Write Collision Flag
#define		SPSR_SPIF	7							// SPI Interrupt Flag


#define		SPDR 		*((volatile u8 *)0x2F)		// SPI Data Register


#endif