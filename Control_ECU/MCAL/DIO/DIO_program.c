/******** Library inclusions **********/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

/********** Lower Layer Inclustions ************/


/********** Self Layer Inclustions ************/


/********** Self Files Inclustions ************/
#include "DIO_interface.h"
#include "DIO_private.h"
#include "DIO_config.h"



void MDIO_voidSetPinDirection(u8 Copy_u8PortName , u8 Copy_u8PinNumber , u8 Copy_u8PinDirection ) 
{
	if(Copy_u8PinNumber <= 7)
	{
		switch(Copy_u8PortName)
		{
			case PORTA  :
				

				switch(Copy_u8PinDirection)
				{
					case INPUT :
						CLEAR_BIT(DIO_DDRA,Copy_u8PinNumber) ;
						break ;
						
					case OUTPUT :
						SET_BIT(DIO_DDRA,Copy_u8PinNumber) ;
						break ;
					
				}
		
				break ; 
			
			case PORTB  :
				switch(Copy_u8PinDirection)
				{
					case INPUT :
						CLEAR_BIT(DIO_DDRB,Copy_u8PinNumber) ;
						break ;
						
					case OUTPUT :
						SET_BIT(DIO_DDRB,Copy_u8PinNumber) ;
						break ;
					
				}
				
				break ; 
				
			case PORTC :
				switch(Copy_u8PinDirection)
				{
					case INPUT :
						CLEAR_BIT(DIO_DDRC,Copy_u8PinNumber) ;
						break ;
						
					case OUTPUT :
						SET_BIT(DIO_DDRC,Copy_u8PinNumber) ;
						break ;
					
				}
				
				break ;
				
			case PORTD :
				switch(Copy_u8PinDirection)
				{
					case INPUT :
						CLEAR_BIT(DIO_DDRD,Copy_u8PinNumber) ;
						break ;
						
					case OUTPUT :
						SET_BIT(DIO_DDRD,Copy_u8PinNumber) ;
						break ;
					
				}
				
				break ;
			
			
		}
	}
	else
	{
		/*Return error*/
	}
}


void MDIO_voidSetPinValue(u8 Copy_u8PortName , u8 Copy_u8PinNumber , u8 Copy_u8PinValue )
{
	if(Copy_u8PinNumber <= 7)
		{
			switch(Copy_u8PortName)
			{
				case PORTA  :


					switch(Copy_u8PinValue)
					{
						case HIGH :
							SET_BIT(DIO_PORTA,Copy_u8PinNumber) ;
							break ;

						case LOW :
							CLEAR_BIT(DIO_PORTA,Copy_u8PinNumber) ;
							break ;
					}

					break ;

				case PORTB  :
					switch(Copy_u8PinValue)
					{
						case HIGH :
							SET_BIT(DIO_PORTB,Copy_u8PinNumber) ;
							break ;

						case LOW :
							CLEAR_BIT(DIO_PORTB,Copy_u8PinNumber) ;
							break ;
					}

					break ;

				case PORTC :
					switch(Copy_u8PinValue)
					{
						case HIGH :
							SET_BIT(DIO_PORTC,Copy_u8PinNumber) ;
							break ;

						case LOW :
							CLEAR_BIT(DIO_PORTC,Copy_u8PinNumber) ;
							break ;
					}

					break ;

				case PORTD :
					switch(Copy_u8PinValue)
					{
						case HIGH :
							SET_BIT(DIO_PORTD,Copy_u8PinNumber) ;
							break ;

						case LOW :
							CLEAR_BIT(DIO_PORTD,Copy_u8PinNumber) ;
							break ;
					}

					break ;

			}
		}
		else
		{
			/*Return error*/
		}


}

void MDIO_voidSetPort(u8 Copy_u8PortName , u8 Copy_u8PinDirection) 
{
	switch (Copy_u8PortName)
	{
		case PORTA :
			if(Copy_u8PinDirection == INPUT)
				DIO_DDRA = ALL_INPUT ; 
			else 
				DIO_DDRA = ALL_OUTPUT ;
			break ;
		case PORTB :
			if(Copy_u8PinDirection == INPUT)
				DIO_DDRB = ALL_INPUT ; 
			else 
				DIO_DDRB = ALL_OUTPUT ;
			break ;
		case PORTC :
			if(Copy_u8PinDirection == INPUT)
				DIO_DDRC = ALL_INPUT ; 
			else 
				DIO_DDRC = ALL_OUTPUT ;
			break ;	
		case PORTD :
			if(Copy_u8PinDirection == INPUT)
				DIO_DDRD = ALL_INPUT ; 
			else 
				DIO_DDRD = ALL_OUTPUT ;
			break ;
	}
}

/*********************************************************
* Description : Put Certain value inside a certain PORTA  *
* Parameters  : 1-Port name - PORTA		2-Value : ...     * 
*						    - PORTB  					  *
*						    - PORTC  					  *
*						    - PORTD   					  *
**********************************************************/

void MDIO_voidSetSpecificPortOutPut(u8 Copy_u8PortName , u8 Copy_u8Value) 
{
	switch (Copy_u8PortName)
	{
		case PORTA :
			DIO_PORTA =Copy_u8Value ;
			break ;
		case PORTB :
			DIO_PORTB =Copy_u8Value ;
			break ;
		case PORTC :
			DIO_PORTC =Copy_u8Value ;
			break ;
		case PORTD :
			DIO_PORTD =Copy_u8Value ;
			break ;
	}
}
/***************************************************************
* Description : Get Pin value from certain input port	       *
* Parameters  : 1-Port name - PORTA	|| 2-PinNumber :PIN0 /PIN4 * 
*						    - PORTB || 	   		    PIN1 /PIN5 *
*						    - PORTC ||		  	    PIN2 /PIN6 *
*						    - PORTD ||  		    PIN3 /PIN7 *
***************************************************************/
u8 MDIO_u8GetPinValue(u8 Copy_u8PortName , u8 Copy_u8PinNumber )
{
	u8 Local_u8PortValue ;
	if(Copy_u8PinNumber <= 7)
	{
		switch(Copy_u8PortName)
		{
			case PORTA:
				Local_u8PortValue = GET_BIT(DIO_PINA,Copy_u8PinNumber) ;
				break ;
			case PORTB:
				Local_u8PortValue = GET_BIT(DIO_PINB,Copy_u8PinNumber) ;
				break ;
			case PORTC:
				Local_u8PortValue = GET_BIT(DIO_PINC,Copy_u8PinNumber) ;
				break ;
			case PORTD:
				Local_u8PortValue = GET_BIT(DIO_PIND,Copy_u8PinNumber) ;
				break ;
		}
	}
	else
	{
		/*Return error*/
	}
	return Local_u8PortValue ;
}
/***************************************************************
* Description : Get Full Port value 					       *
* Parameters  : 1-Port name - PORTA	 						   *
*						    - PORTB  	  					   *
*						    - PORTC 	  					   *
*						    - PORTD   					       *
* Return : u8							 					   *
***************************************************************/

u8 MDIO_u8GetPortValue(u8 Copy_u8PortName )
{
	u8 Local_u8PortValue ;
		switch(Copy_u8PortName)
		{
			case PORTA:
				Local_u8PortValue = DIO_PINA ;
				break ;
			case PORTB:
				Local_u8PortValue = DIO_PINB ;
				break ;
			case PORTC:
				Local_u8PortValue = DIO_PINC ;
				break ;
			case PORTD:
				Local_u8PortValue = DIO_PIND ;
		 		break ;
		}
	return Local_u8PortValue ;
}