/***********************************************************************/
/*  !Author     :       Ahmed Gamal                  		           */
/*  !Date       :       3 Jan, 2022                                   */
/*  !LAYER      :       MCAL                                           */
/*  !Version    :       v1.7                                           */
/***********************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIM_interface.h"
#include "TIM_private.h"
#include "TIM_config.h"

void MTIMERS_voidTimer0Init(void)			// PreBuild
{
	/* PreProcessor Timer0 Configurations and enable */
	#if TIMER0 == ENABLE
		#if   MODE == CTC
			CLEAR_BIT(TCCR0, TCCR0_WGM00);
			SET_BIT(TCCR0  , TCCR0_WGM01);
		#elif MODE == NORMAL
			CLEAR_BIT(TCCR0, TCCR0_WGM00);
			CLEAR_BIT(TCCR0, TCCR0_WGM01);
		#elif MODE == PHASECORRECT
			SET_BIT(TCCR0  , TCCR0_WGM00);
			CLEAR_BIT(TCCR0, TCCR0_WGM01);
		#elif MODE == FASTPWM
			SET_BIT(TCCR0  , TCCR0_WGM00);
			SET_BIT(TCCR0  , TCCR0_WGM01);
		#endif
		/*Over Flow Interrupt */
		#if OVERFLOW_INTERRUPT == ENABLE
			SET_BIT(TIMSK, TIMSK_TOIE0);
		#elif OVERFLOW_INTERRUPT == DSIABLE
			CLEAR_BIT(TIMSK, TIMSK_TOIE0);
		#endif
		/*PresScaler Settings*/
		TCCR0 &= TIM_PRESCALER_MASK ;
		#if PRESCALER == 0
		TCCR0 |= 0b1 ;
		#elif PRESCALER == 8
		TCCR0 |= 0b10 ;
		#elif PRESCALER == 64
		TCCR0 |= 0b11 ;
		#elif PRESCALER == 256
		TCCR0 |= 0b100 ;
		#elif PRESCALER == 1024
		TCCR0 |= 0b101 ;
		#endif
		/* Setting of Clear / set flags */
		#if COMPARE_OUTPUT == STCC
		CLEAR_BIT(TCCR0,TCCR0_COM00);
		SET_BIT	 (TCCR0,TCCR0_COM01);
		#elif COMPARE_OUTPUT == CTSC
		SET_BIT(TCCR0,TCCR0_COM00);
		SET_BIT(TCCR0,TCCR0_COM01);
		#endif
	#endif
}

void MTIMERS_voidTimer1Init()    				//postBuild
{
	/* SET MODE 14 => FAST PWM */
	CLEAR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A  ,TCCR1A_WGM11);
	SET_BIT(TCCR1B  ,TCCR1B_WGM12);
	SET_BIT(TCCR1B  ,TCCR1B_WGM13);
	/* SET ( SET ON TOP CLEAR ON COMPARE) mode */
	CLEAR_BIT(TCCR1A , TCCR1A_COM1A0);
	SET_BIT  (TCCR1A , TCCR1A_COM1A1);
	/*               SET PreScaler             */
	CLEAR_BIT(TCCR1B,TCCR1B_CS10) ;
	SET_BIT  (TCCR1B,TCCR1B_CS11) ;
	CLEAR_BIT(TCCR1B,TCCR1B_CS12) ;
}

void MTIMERS_voidTimer2Init()    				//PreBuild
{
	#if TIMER2 == ENABLE
		/* Setting TIMER2 Mode */
		#if MODE2 ==	NORMAL
			CLEAR_BIT(TCCR2,TCCR2_WGM20) ;
			CLEAR_BIT(TCCR2,TCCR2_WGM21) ;
		#elif MODE2 ==	PHASECORRECT
			SET_BIT(TCCR2,TCCR2_WGM20) ;
			CLEAR_BIT(TCCR2,TCCR2_WGM21) ;
		#elif MODE2 ==	CTC
			CLEAR_BIT(TCCR2,TCCR2_WGM20) ;
			SET_BIT(TCCR2,TCCR2_WGM21) ;
		#elif MODE2 ==	FASTPWM
			SET_BIT(TCCR2,TCCR2_WGM20) ;
			SET_BIT(TCCR2,TCCR2_WGM21) ;
		#endif
		/* Setting Compare Output Mode */
		#if COMPARE_OUTPUT2 == STCC
			SET_BIT(TCCR2,TCCR2_COM21);
			CLEAR_BIT(TCCR2,TCCR20)  ;
		#elif COMPARE_OUTPUT2 == CTSC
			SET_BIT(TCCR2,TCCR2_COM21)  ;
			SET_BIT(TCCR2,TCCR2_COM20)  ;
		#endif
		/* Setting PreScaler */
		#if PRESCALER2 == 0
			CLEAR_BIT(TCCR2,TCCR2_CS20) ;
			CLEAR_BIT(TCCR2,TCCR2_CS21) ;
			SET_BIT(TCCR2,TCCR2_CS22)   ;
		#elif PRESCALER2 == 8
			CLEAR_BIT(TCCR2,TCCR2_CS20) ;
			SET_BIT(TCCR2,TCCR2_CS21)   ;
			CLEAR_BIT(TCCR2,TCCR2_CS22) ;
		#elif PRESCALER2 == 32
			SET_BIT(TCCR2,TCCR2_CS20)   ;
			SET_BIT(TCCR2,TCCR2_CS21) 	;
			CLEAR_BIT(TCCR2,TCCR2_CS22) ;
		#elif PRESCALER2 == 64
			CLEAR_BIT(TCCR2,TCCR2_CS20) ;
			CLEAR_BIT(TCCR2,TCCR2_CS21) ;
			SET_BIT(TCCR2,TCCR2_CS22)   ;
		#elif PRESCALER2 == 128
			SET_BIT(TCCR2,TCCR2_CS20) ;
			CLEAR_BIT(TCCR2,TCCR2_CS21) ;
			SET_BIT(TCCR2,TCCR2_CS22)   ;
		#elif PRESCALER2 == 256
			SET_BIT(TCCR2,TCCR2_CS20)   ;
			SET_BIT(TCCR2,TCCR2_CS21)   ;
			CLEAR_BIT(TCCR2,TCCR2_CS22) ;
		#elif PRESCALER2 == 1024
			SET_BIT(TCCR2,TCCR2_CS20)   ;
			SET_BIT(TCCR2,TCCR2_CS21)   ;
			SET_BIT(TCCR2,TCCR2_CS22)   ;
		#endif
	#endif

}


void MTIMERS_voidTimer0SetPreloadValue(u8 Copy_u8PreloadValue)
{
	/*Set The Preload Value In The Timer0 Register*/
	TCNT0 = Copy_u8PreloadValue;
}

void MTIMERS_voidTimer2SetPreloadValue(u8 Copy_u8PreloadValue)
{
	/*Set The Preload Value In The Timer0 Register*/
	TCNT2 = Copy_u8PreloadValue;
}

void MTIMERS_voidTimer1SetTopValue(u16 Copy_u16TopValue)
{
	ICR1 = Copy_u16TopValue 		;
}


void MTIMERS_voidTimer0SetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
	/*Set The Compare Match Value In The OCR0 Register*/
	OCR0 = Copy_u8CompareMatchValue;
}
void MTIMERS_voidTimer1SetCompareMatchValue(u16 Copy_u16CompareMatchValue)
{
	/*Set compare value in OCR0 Register*/
	OCR1A = Copy_u16CompareMatchValue ;
}

void MTIMERS_voidTimer2SetCompareMatchValue(u8 Copy_u8CompareMatchValue)
{
	/*Set The Compare Match Value In The OCR0 Register*/
	OCR2 = Copy_u8CompareMatchValue;
}


void MTIMERS_voidSetBusyWait(u32 Copy_u32MicroSeconds)
{
	/*
		Prescaler = 8;
		OCR0 = 250
		Compare Match Time = 250 * 8/8MHz = 250 usec
	*/
	/* Make Sure The Prescaler Is = 8
	   Set The OCR0 (Compare Match Value) = 1
	   Make Sure The Flag Is Cleared
	*/
	OCR0 = 250 ;

	SET_BIT(TIFR, TIFR_OCF0);

	u32 Local_u32TickCounter = 0;

	while(Local_u32TickCounter < Copy_u32MicroSeconds*4)
	{
		/*Check if The Flag Is Raised Up Or Not*/
		if(GET_BIT(TIFR, TIFR_OCF0) == 1)
		{
			/*Increment The Counter*/
			Local_u32TickCounter++;
			/*Clear The Flag*/
			SET_BIT(TIFR, TIFR_OCF0);
		}
	}
}
