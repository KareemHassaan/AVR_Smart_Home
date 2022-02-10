/**********************************************************************************
 *        Author : Ahmed Gamal
 *        Date	 : 2/1/2022
 *        Project: AVR Graduation (SmartHome) Internal controller
 *        Version: 2.0
 **********************************************************************************/

/************************************ List Of Pins Used ****************************
*1- For SPI Communication
*   MOSI   -> PB5   (INPUT )        (SHOULD I SET IT IN DIRECTION ? )
*   MISO   -> PB6	(OUTPUT)
*   SCK    -> PB7	(INPUT )
*   SS     -> PB4	(INPUT )
*   ------------------------------------------------------------------------
*2- For Timers
*	TIM0   -> PB3	(OUTPUT)
*	TIM1   -> PD5	(NOT CONNECTED for setbusy wait)
*	TIM2   -> PD7	(OUTPUT)
*	------------------------------------------------------------------------
*3- For ADC Readings
*	ADC0   -> PA0	(INPUT)
*	ADC1   -> PA1	(INPUT)
*	------------------------------------------------------------------------
*4- For LCD Connection
*	Data   -> PC	(NOO NEED TO SET IN DIRECTIONS)
*	EN     -> PB0
*	RW	   -> PB1
*	RS	   -> PB2
*	------------------------------------------------------------------------
*5- STEPPER Motor
*	BLUE  ->  PD0	(NOO NEED TO SET IN DIRECTIONS)
*	PINK  ->  PD1
*	Yellow->  PD2
*	Orange->  PD3
*	------------------------------------------------------------------------
*6- DIO Pins
*	PIR	  ->  PA2	(INPUT )
*	LED   ->  PA3	(OUTPUT)
***********************************************************************************/
#include "../LIB/STD_TYPES.h"
#include <util/delay.h>

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/TIM/TIM_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/GIE/GIE_interface.h"

#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/STEPPER/STEPPER_interace.h"

#include "MAIN_private.h"
#define		SPDR 		*((volatile u8 *)0x2F)
/* Function to sum up all the drivers needed to be initiated */
void App_DriversInit(void)   ;
void App_PinsDirection(void) ;

extern u8 MSPI_u8ReceivedData    ;

int main()
{
	App_DriversInit()   ;
	App_PinsDirection() ;


/****** Local Variables ********/
	volatile u16 LDR_DigitalValue  ;
	volatile u16 LM35_DigitalValue ;
	u8  Mapped_LDR		  ;
	u8  Mapped_LM35		  ;
	u8  Room_Lights = OFF ;
	u8  PIR_Reading = 0   ;
	u8  MAX_CompareValue = 255;


/*****Initial Setting System to be off ****/
	MSPI_u8ReceivedData = 12  ;

	while(1)
	{

		//Saving Sensors Readings
		LDR_DigitalValue = MADC_u16StartConversionSync(ADC_CHANNEL0) ;
		PIR_Reading      = MDIO_u8GetPinValue(PORTA,PIN2)            ;

		//Mapping Reading to PWM Values
		Mapped_LDR =MAP(0,1023,0,255,LDR_DigitalValue)  ;

		//Checking If Room light is on/off or there is no one in room or not
		if(Room_Lights==ON && PIR_Reading == 1)
		{
			MTIMERS_voidTimer0SetCompareMatchValue(MAX_CompareValue - Mapped_LDR) ;
		}
		else if(Room_Lights == OFF || PIR_Reading == 0 )
		{
			MTIMERS_voidTimer0SetCompareMatchValue(MAX_CompareValue)	;
		}

		switch(SPDR)
		{
			case TURN_LIGHT_ON:
				MDIO_voidSetPinValue(PORTA,PIN3,HIGH) ;	// Reception Light
				Room_Lights = ON 					  ; // Room Light
				HLCD_voidClearAll() ;
				HLCD_voidSendString("Home Lights ON") ;
				MSPI_u8ReceivedData = DEFAULT_STATE ;
				break ;
			case TURN_LIGHT_OFF:
				MDIO_voidSetPinValue(PORTA,PIN3,LOW)  ;  // Reception Light
				Room_Lights = OFF					  ;  // Room Light
				HLCD_voidClearAll() ;
				HLCD_voidSendString("Home Lights OFF") ;
				MSPI_u8ReceivedData = DEFAULT_STATE ;
				break ;
			case TURN_AC_ON :
				LM35_DigitalValue= MADC_u16StartConversionSync(ADC_CHANNEL1) ;
				Mapped_LM35=MAP(0,1023,0,255,LM35_DigitalValue)         ;
				MTIMERS_voidTimer2SetCompareMatchValue(MAX_CompareValue - Mapped_LM35) ; //(NEED ADJUSTING)
				HLCD_voidClearAll() ;
				HLCD_voidSendString("Auto Temperature Detected AC ON ") ;
				MSPI_u8ReceivedData = DEFAULT_STATE ;
				break ;
			case TURN_AC_OFF:
				LM35_DigitalValue= MADC_u16StartConversionSync(ADC_CHANNEL1) ;
				Mapped_LM35=MAP(0,1023,0,255,LM35_DigitalValue)         ;
				MTIMERS_voidTimer2SetCompareMatchValue(MAX_CompareValue) ; //(NEED ADJUSTING)
				HLCD_voidSendString("AC OFF.... ") ;
				HLCD_voidClearAll() ;
				MSPI_u8ReceivedData = DEFAULT_STATE ;
				break ;
			case CURTAINS_ON :
				HSTEPPER_voidRotate(COUNTER_CLK_WISE, 360); // Open Curtains  (NEED ADJUSTING)
				HLCD_voidClearAll() ;
				HLCD_voidSendString("Curtains Open...") ;
				MSPI_u8ReceivedData = DEFAULT_STATE ;
				break;
			case CURTAINS_OFF :
				HSTEPPER_voidRotate(COUNTER_CLK_WISE, 360); // Close Curtains (NEED ADJUSTING)
				HLCD_voidClearAll() ;
				HLCD_voidSendString("Curtains Close...") ;
				MSPI_u8ReceivedData = DEFAULT_STATE ;
				break;
			case SYSTEM_OFF  :
				HLCD_voidSendString("System Is OFF") ;
				while(MSPI_u8ReceivedData != SYSTEM_ON) ; // Polling Until System is on
				HLCD_voidSendString("System Is ON , Welcome") ;
				_delay_ms(2000) ;
				HLCD_voidClearAll() ;
				break ;
			case DEFAULT_STATE:
				//do nothing
				break ;
			default:
				HLCD_voidSendString("System ERROR..... data = ") ;
				HLCD_voidSendNumber (MSPI_u8ReceivedData) ;
				_delay_ms(2000) ;
				HLCD_voidClearAll() ;
				break ;
		}
	}
}

void App_DriversInit()
{
	/* Initiate ADC For Reading LDR Value & LM35 Value */
	MADC_voidInit()					;
	/* Initiate Timers Needed Timer 0 -> PWM   , Timer 1 -> SetBusyWait , Timer 2 -> DC Motor */
	MTIMERS_voidTimer0Init()		;
	MTIMERS_voidTimer1Init()		;
	MTIMERS_voidTimer2Init()		;
	/* Initiate SPI communication to communicate with the Master controller */
	MSPI_voidSlaveInit() 			;
	/* Initiate LCD Connections */
	HLCD_voidInit()      			;
}

void App_PinsDirection()
{
	//PORTA
	MDIO_voidSetPinDirection(PORTA,PIN0,INPUT)  ; // For ADC channel 0 (LDR   Reading)
	MDIO_voidSetPinDirection(PORTA,PIN1,INPUT)  ; // For ADC channel 1 (LM-35 Reading)
	MDIO_voidSetPinDirection(PORTA,PIN2,INPUT)  ; // For PIR Signal
	MDIO_voidSetPinDirection(PORTA,PIN3,OUTPUT) ; // For Reception LED

	//PORTB (Pin 0,1,2 For LCD )  (Pin 4,5,6,7 For SPI)
	MDIO_voidSetPinDirection(PORTB,PIN3,OUTPUT) ; // For Timer 0 ( Room LED )
	MDIO_voidSetPinDirection(PORTB,PIN4,INPUT)  ;
	MDIO_voidSetPinDirection(PORTB,PIN5,OUTPUT) ;
	MDIO_voidSetPinDirection(PORTB,PIN6,INPUT)  ;
	MDIO_voidSetPinDirection(PORTB,PIN7,INPUT)  ;

	//PORTC (All For LCD Data)

	//PORTD (Pins 1,2,3,4 For Stepper)
	MDIO_voidSetPinDirection(PORTD,PIN7,OUTPUT) ; // For Timer 2 (DC Motor Air Condition)
}
