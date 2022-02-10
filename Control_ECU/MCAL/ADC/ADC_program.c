/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 26 Dec. 2021                                         *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#include "ADC_private.h"
#include "ADC_config.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/*GLobal pointer to function for ISR */
static void (*Global_pvCallbackFunction)(void ) = NULL;
/* Global variable for ISR to save ADC Data */
u16 Global_u16DigitalValue=10 ;

s16 MAP(s16 Copy_s16InputMin, s16 Copy_s16InputMax, s16 Copy_s16OutputMin, s16 Copy_s16OutputMax, s16 Copy_s16InputValue)
 {
	/*Local variable to Store in it the return value*/
	 s16 Local_s16ReturnX;
	/*Calculating the slope of the Linear graph*/
     s16 Slope = (Copy_s16InputMax-Copy_s16InputMin)/(Copy_s16OutputMax-Copy_s16OutputMin);
	/*Getting the Entered Value in the variable Y*/
     s16 Y = Copy_s16InputValue;
	/*Define a variable to store the opposite value on the line*/
     s16 X = 0;

	/*Calculating the wanted oppisite value on the line*/
     X = ((Y - Copy_s16InputMin)/Slope)+Copy_s16OutputMin;

	/*Check if the Entered value Smaller than the minimum*/
     if(Copy_s16InputValue < Copy_s16InputMin)
     {
		/*Return the MIN value*/
    	 Local_s16ReturnX = Copy_s16OutputMin;
     }
	 /*Check if the Entered value Bigger than the maximum*/
     else if(Copy_s16InputValue > Copy_s16InputMax)
     {
		/*Return the MAX value*/
    	 Local_s16ReturnX = Copy_s16OutputMax;
     }
     else
     {
		/*Return the Calculated value*/
    	 Local_s16ReturnX = X;
     }


    return Local_s16ReturnX;
 }

void MADC_voidInit()
{
		#if ADC_ENABLE == ENABLE
			CLEAR_BIT(ADMUX,ADMUX_ADLAR) ;
			#if     ADC_REF_SELECTION   ==  AREF
				CLEAR_BIT(ADMUX, ADMUX_REFS0);
				CLEAR_BIT(ADMUX, ADMUX_REFS1);
			#elif   ADC_REF_SELECTION   ==  AVCC
				SET_BIT(ADMUX  , ADMUX_REFS0);
				CLEAR_BIT(ADMUX, ADMUX_REFS1);
			#elif   ADC_REF_SELECTION   ==  INT_256VOLT
				SET_BIT(ADMUX, ADMUX_REFS0);
				SET_BIT(ADMUX, ADMUX_REFS1);
			#else
				#error "NO SELECTION"
			#endif
			ADCSRA &= PRESCALER_MASK ;
			ADCSRA |= ADC_PRESCALER_VALUE ;
			SET_BIT(ADCSRA,ADCSRA_ADEN) ;

		#elif  ADC_ENABLE == DISABLE
			CLEAR_BIT(ADCSRA,ADCSRA_ADEN) ;
 		#else
			#error "ADC_ENABLE Config. error"
		#endif
}

u16 MADC_u16StartConversionSync(u8 Copy_u8ChannelNumber)
{
	ADMUX &= ADMUX_MASK ;
	ADMUX |= Copy_u8ChannelNumber;

	/*Start conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC) ;
	/*Polling till the flag is raised*/
	while(GET_BIT(ADCSRA,ADCSRA_ADIF) == 0);
	/*Clear Flag*/
	SET_BIT(ADCSRA,ADCSRA_ADIF);
	return ADC ;
}

void MADC_voidStartConversionAsync(u8 Copy_u8ChannelNumber)
{
	ADMUX &= ADMUX_MASK ;
	ADMUX |= Copy_u8ChannelNumber ;
	/*Start conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC) ;
	/* ADC ENABLE INTURREPT*/
	SET_BIT(ADCSRA,ADCSRA_ADIE );
}


/* ISR And callBack Function to ADC */
void MADC_voidSetCallback(void (*Copy_pvNotificationFunction)(void))
{
	Global_pvCallbackFunction = Copy_pvNotificationFunction ;
}

void __vector_16(void)    __attribute__((signal));
void __vector_16(void)
{
    if(Global_pvCallbackFunction != NULL)
    {
        /*Get Data And Store It In A Global Variable*/
        Global_u16DigitalValue = ADC;
        /*Call The Callback Function*/
        Global_pvCallbackFunction();
        /*Disable The Interrupt*/
        CLEAR_BIT(ADCSRA, ADCSRA_ADIE);
    }
    else
    {
        /*Do Nothing*/
    }
}
