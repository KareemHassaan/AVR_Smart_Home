/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 28 Dec. 2021                                         *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef TIM_PRIVATE_H
#define TIM_PRIVATE_H

#define		TCCR0				*((volatile u8*)0x53)
#define		TCCR0_CS00  		0                      //Timer 0 clock selection  bit 0
#define		TCCR0_CS01  		1                      //Timer 0 clock selection  bit 1
#define		TCCR0_CS02  	 	2                      //Timer 0 clock selection  bit 2
#define		TCCR0_WGM01 		3                      //Timer 0 Wave Generation mode  bit 0
#define		TCCR0_COM00 		4                      //Timer 0 Compare out mode  bit 0
#define		TCCR0_COM01 		5                      //Timer 0 Compare output mode bit 1
#define		TCCR0_WGM00 		6                      //Timer 0 Wave Generation mode  bit 2
#define		TCCR0_FOC0 			7                      //Timer 0 Force Output  bit 2

#define 	TCNT0				*((volatile u8*)0x52)  //Timer/Counter 0  register

#define 	TIMSK				*((volatile u8*)0x59)  //Timer/Counter interrupt mask register
#define		TIMSK_TOIE0 		0                      //Timer 0 Over flow interrupt enable
#define		TIMSK_OCIE0 		1                      //Timer 0 Output compare interrupt  bit 1
#define		TIMSK_TOIE1 		2                      //Timer 1 overflow interrupt enable
#define		TIMSK_OCIE1B 		3                      //Timer 1 Channel A output compare interrupt
#define		TIMSK_OCIE1A 		4                      //Timer 1 Channel A output compare interrupt
#define		TIMSK_TICIE1 		5                      //Timer 1 input Capture interrupt enable
#define		TIMSK_TOIE2 		6                      //Timer 2 Overflow interrupt enable
#define		TIMSK_OCIE2 		7                      //Timer 2 Output compare interrupt enable

#define 	TIFR				*((volatile u8 *)0x58) //timer/counter interrupt flag
#define		TIFR_TOV0			0						//timer 0 overflow flag
#define		TIFR_OCF0			1						//timer 0 output compare flag
#define		TIFR_TOV1			2						//timer 1 overflow flag
#define		TIFR_OCF1B			3						//timer 1 Channel B output compare flag
#define		TIFR_OCF1A			4						//timer 1 Channel A output compare flag
#define		TIFR_ICF1			5						//timer 1 input capture flag
#define		TIFR_TOV2			6						//timer 2 overflow flag
#define		TIFR_OCF2			7						//timer 2 output compare flag

#define		OCR0				*((volatile u8 *)0x5C)  //Compare Match register
/**********************  TIMER 1 REGISETERS   *************************/
#define		TCCR1A				*((volatile u8 *)0x4F)  //timer 1 control register A
#define		TCCR1A_WGM10		0						//WaveGeneration mode Bit 0
#define		TCCR1A_WGM11		1						//WaveGeneration mode Bit 1
#define		TCCR1A_COM1A0		6						//Compare output mod Channel A mode Bit 0
#define		TCCR1A_COM1A1		7						//Compare output mod Channel A  mode Bit 0

#define		TCCR1B				*((volatile u8 *)0x4E)  //timer 1 control register B
#define		TCCR1B_CS10			0						//prescaler
#define		TCCR1B_CS11			1						//prescaler
#define		TCCR1B_CS12			2						//prescaler
#define		TCCR1B_WGM12		3						//WaveGeneration mode Bit 2
#define		TCCR1B_WGM13		4						//WaveGeneration mode Bit 3
#define		TCCR1B_ICES1		6						//Input capture unit enable

#define		TCNT1				*((volatile u16*)0x4C) //timer 1 register

#define		OCR1A				*((volatile u16*)0x4A) //Output compare register

#define		ICR1				*((volatile u16*)0x46) //Output input capture unit
/**********************  TIMER 2 REGISETERS   *************************/
#define		TCCR2				*((volatile u8*)0x45)
#define		TCCR2_FOC2			7					//Force Output Compare
#define		TCCR2_WGM21			6					//Wave Generation Mode bit 1
#define		TCCR2_COM21			5					//Compare Match Output Mode	bit 1
#define		TCCR2_COM20			4					//Compare Match Output Mode bit 0
#define		TCCR2_WGM20			3					//Wave Generation Mode bit 0
#define		TCCR2_CS22			2					//Clock Select bit 2
#define		TCCR2_CS21			1					//Clock Select bit 1
#define		TCCR2_CS20			0					//Clock Select bit 1

#define		TCNT2				*((volatile u8*)0x44)  //Timer 2 Register

#define		OCR2				*((volatile u8*)0x43)  //Output Compare Register

/**********************  Magic Numbers Definitions   *************************/
#define			NORMAL					0
#define			PHASECORRECT			1
#define			CTC						2
#define			FASTPWM					3
#define			TIM_PRESCALER_MASK		0b11111000
#define			STCC					1
#define			CTSC					0
#define			TIMER0_CTC				1
#define			TIMER0_OVF				0

#endif
