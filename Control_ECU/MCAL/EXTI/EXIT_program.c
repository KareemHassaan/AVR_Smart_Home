/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 22 Dec. 2021                                         *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../DIO/DIO_interface.h"
#include "../EXTI/EXIT_config.h"
#include "../EXTI/EXIT_interface.h"
#include "../EXTI/EXIT_private.h"


void (*Global_pvInit0CallBack)() = NULL ;
void (*Global_pvInit1CallBack)() = NULL ;

void MEXTI_voidInit(void)
{
	#if 	EXTI_INT0_ENABLE == ENABLE
		/*Set Sense Signal*/
		#if 	EXTI_INT0_SENSE_SIGNAL	== FALLING_EDGE
			/*Set Sense Signal To Falling Edge*/
			CLEAR_BIT(MCUCR, MCUCR_ISC00);
			SET_BIT(MCUCR, MCUCR_ISC01);
		#elif	EXTI_INT0_SENSE_SIGNAL  == RISING_EDGE
			/*Set Sense Signal To Rising Edge*/
			SET_BIT(MCUCR, MCUCR_ISC00);
			SET_BIT(MCUCR, MCUCR_ISC01);
		#elif	EXTI_INT0_SENSE_SIGNAL  == ON_CHANGE
			/*Set Sense Signal To On Change*/
			SET_BIT(MCUCR, MCUCR_ISC00);
			CLR_BIT(MCUCR, MCUCR_ISC01);
		#elif	EXTI_INT0_SENSE_SIGNAL	== LOW_LEVEL
			/*Set Sense Signal To Low Level*/
			CLR_BIT(MCUCR, MCUCR_ISC00);
			CLR_BIT(MCUCR, MCUCR_ISC01);
		#else
			#error "EXTI_INT0_SENSE_SIGNAL Configuration Error"
		#endif
		/*Enable INT0 Interrupt*/
		SET_BIT(GICR, GICR_INT0);
	#elif	EXTI_INT0_ENABLE == DISABLE
		/*Disable INT0 Interrupt*/
		CLEAR_BIT(GICR, GICR_INT0);
	#else
		#error "EXTI_INT0_ENABLE Configuration Error"
	#endif

	#if 	EXTI_INT1_ENABLE == ENABLE
		/*Set Sense Signal*/
		#if 	EXTI_INT1_SENSE_SIGNAL	== FALLING_EDGE
			/*Set Sense Signal To Falling Edge*/
			CLR_BIT(MCUCR, MCUCR_ISC10);
			SET_BIT(MCUCR, MCUCR_ISC11);
		#elif	EXTI_INT1_SENSE_SIGNAL  == RISING_EDGE
			/*Set Sense Signal To Rising Edge*/
			SET_BIT(MCUCR, MCUCR_ISC10);
			SET_BIT(MCUCR, MCUCR_ISC11);
		#elif	EXTI_INT1_SENSE_SIGNAL  == ON_CHANGE
			/*Set Sense Signal To On Change*/
			SET_BIT(MCUCR, MCUCR_ISC10);
			CLR_BIT(MCUCR, MCUCR_ISC11);
		#elif	EXTI_INT1_SENSE_SIGNAL	== LOW_LEVEL
			/*Set Sense Signal To Low Level*/
			CLR_BIT(MCUCR, MCUCR_ISC10);
			CLR_BIT(MCUCR, MCUCR_ISC11);
		#else
			#error "EXTI_INT1_SENSE_SIGNAL Configuration Error"
		#endif
		/*Enable INT1 Interrupt*/
		SET_BIT(GICR, GICR_INT1);
	#elif	EXTI_INT1_ENABLE == DISABLE
		/*Disable INT1 Interrupt*/
		CLEAR_BIT(GICR, GICR_INT1);
	#else
		#error "EXTI_INT1_ENABLE Configuration Error"
	#endif
}

s8 MEXTI_voidInturrupt(u8 Copy_u8InterruptValue,u8 Copy_u8State)
{
	switch (Copy_u8InterruptValue)
	{
		case INT0 :
			if(Copy_u8State == ENABLE)
			{
				SET_BIT(GICR,GICR_INT0) ;
				return 1;
			}
			else if(Copy_u8State == DISABLE)
			{
				CLEAR_BIT(GICR , GICR_INT0) ;
				return 1;
			}
			break ;
		case INT1 :
			if(Copy_u8State == ENABLE)
			{
				SET_BIT(GICR,GICR_INT1) ;
				return 1;
			}
			else if(Copy_u8State == DISABLE)
			{
				CLEAR_BIT(GICR , GICR_INT1) ;
				return 1;
			}
			break ;
		case INT2 :
			if(Copy_u8State == ENABLE)
			{
				SET_BIT(GICR,GICR_INT2) ;
				return 1;
			}
			else if(Copy_u8State == DISABLE)
			{
				CLEAR_BIT(GICR , GICR_INT2) ;
				return 1;
			}
			break ;
		default:
			return -1 ;
	}
	return 0 ;
}


/**************************** CALLL BACK AND ISR TO INT0 Interrupt ******************/
void MEXTI_voidInt0CallBack(void (*Copy_pvNotificationFunction)(void))
{
	Global_pvInit0CallBack = Copy_pvNotificationFunction ;
}

void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	Global_pvInit0CallBack() ;
}

/**************************** CALLL BACK AND ISR TO INT1 Interrupt ******************/
void MEXTI_voidInt1CallBack(void (*Copy_pvNotificationFunction)(void))
{
	Global_pvInit1CallBack = Copy_pvNotificationFunction ;
}

void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	Global_pvInit1CallBack() ;
}



