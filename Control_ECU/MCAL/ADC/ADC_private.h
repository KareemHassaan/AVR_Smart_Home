/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 26 Dec. 2021                                         *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

/********************************************************************************************************/
#define  ADMUX				*((volatile u8*)0x27)  //ADC MUX register
#define  ADMUX_MUX0		    0					   //MUX 0 bit
#define  ADMUX_MUX1		    1					   //MUX 1 bit
#define  ADMUX_MUX2		    2					   //MUX 2 bit
#define  ADMUX_MUX3		    3					   //MUX 3 bit
#define  ADMUX_MUX4		    4					   //MUX 4 bit
#define  ADMUX_ADLAR		5					   //ADC Left Adjust bit
#define  ADMUX_REFS0		6					   //ADC Reference selection bit 0
#define  ADMUX_REFS1		7					   //ADC Reference selection bit 1
/********************************************************************************************************/
#define  ADCSRA				*((volatile u8*)0x26)
#define  ADCSRA_ADPS0   	0             		//ADC Prescaler selection BIT0
#define  ADCSRA_ADPS1   	1			  		//ADC Prescaler selection BIT0
#define  ADCSRA_ADPS2   	2			  		//ADC Prescaler selection BIT0
#define  ADCSRA_ADIE		3			  		//ADC interrupt enable
#define  ADCSRA_ADIF		4			  		//ADC interrupt Flag
#define  ADCSRA_ADATE   	5			  		//ADC Auto Trigger Flag
#define  ADCSRA_ADSC		6			  		//start conversation
#define  ADCSRA_ADEN		7			  		//ADC Enable BIT ****
/********************************************************************************************************/
#define	 ADCL				*((volatile u8*)0x24)  //ADC Low  Data
#define	 ADCH				*((volatile u8*)0x25)  //ADC High Data
#define	 ADC				*((volatile u16*)0x24) //ADC Data
/********************************************************************************************************/
#define			ENABLE				1
#define			DISABLE				0

#define			AREF				0
#define			AVCC				1
#define			INT_256VOLT			2

#define 		PRESCALER_MASK		0b11111000
#define			ADMUX_MASK			0b11100000

#define			DIV_BY_2			0b001
#define			DIV_BY_8			0b010
#define			DIV_BY_16			0b100
#define			DIV_BY_32			0b101
#define			DIV_BY_64			0b110
#define			DIV_BY_128			0b111

#define         ADC0                0b000
#define         ADC1                0b001    
#define         ADC2                0b010
#define         ADC3                0b011
#define         ADC4                0b100    
#define         ADC5                0b101
#define         ADC6                0b110
#define         ADC7                0b111



#endif
