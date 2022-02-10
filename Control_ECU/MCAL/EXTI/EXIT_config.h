/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 22 Dec. 2021                                         *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef EXIT_CONFIG_H
#define EXIT_CONFIG_H

/*
        Options   ENABLE / DISABLE
*/

/*
	Options:
				ENABLE 			DISABLE
*/
#define		EXTI_INT0_ENABLE			ENABLE
#define		EXTI_INT1_ENABLE			DISABLE


/*
	Options:
				FALLING_EDGE	RISING_EDGE		ON_CHANGE	LOW_LEVEL
*/
#define		EXTI_INT0_SENSE_SIGNAL		FALLING_EDGE
#define		EXTI_INT1_SENSE_SIGNAL		LOW_LEVEL

#endif
