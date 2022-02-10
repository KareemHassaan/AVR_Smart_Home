/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 28 Dec. 2021                                         *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef TIM_CONFIG_H
#define TIM_CONFIG_H

/*Options (Enable  Disable)*/
#define			TIMER0						ENABLE
#define			TIMER2						ENABLE

/*********  TIMER 0 CONFig.  *************/
/*Options Timer0 (NORMAL   PHASECORRECT		CTC		FASTPWM)*/
#define			MODE						FASTPWM
/*Options for interrupt Timer0 (ENABLE DISABLE)*/
#define			OVERFLOW_INTERRUPT			DISABLE
/*Options ( 0	8		64		256		1024 ) */
#define			PRESCALER					8
/*Options (STCC (Set Top Clear Compare)		CTSC( Clear Top Set Compare ) )*/
#define			COMPARE_OUTPUT				CTSC

/*********  TIMER 2 CONFig.  *************/
#define			MODE2			FASTPWM
#define			COMPARE_OUTPUT	CTSC
#define			PRESCALER2		8





#endif
