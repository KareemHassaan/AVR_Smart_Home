/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					AAMK Team							09 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: Smart Home                                                        							                      *
* ! File Name	: SmartHome.c                                                       							                      *
* ! Description : This file has the implementation of Basic of Smart Home functions        							                  *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: Service                  						                                         							  *
**************************************************************************************************************************************/

/**************************************************** Library Inclusions *************************************************************/
#include"../LIB/STD_TYPES.h"
#include"../LIB/BIT_MATH.h"
/************************************************** Lower Layer Inclusions ***********************************************************/
#include"../MCAL/01-DIO/DIO_intrface.h"
#include"../MCAL/05-Timers/TIMERS_intrface.h"
#include"../MCAL/06-USART/USART_intrface.h"
#include"../MCAL/07-SPI/SPI_intrface.h"
#include"../SERVICES/SmartHome.h"
/************************************************** Self Layer Inclusions ************************************************************/

/***************************************************** Global Variables **************************************************************/


/*************************************************************************************************************************************/
/********************************************************* Main Function  ************************************************************/
/*************************************************************************************************************************************/

void main(void)
{
	/*Variable To Store System ON or OFF*/
	uint8 Local_uint8SystemStatus;
	/*Variable To Store System Option Entered By The User*/
	uint8 Local_uint8SystemOptions;
	/*Variable To Store The Status Of The Component Entered By the user To Turn ON or OFF*/
	uint8 Local_uint8Component_ON_OFF;
	/*Variable To Store The Return Value Of Password Check Function*/
	uint8 Local_uint8UserValidation;
	
	/*Function Call to Initialize All Perepheral and Pins needad*/
	 ASmart_VoidInit();
	
	 while(1)
	 {
		/*Printing to The User To Choose Turn ON or Turn OFF The System*/
		 MUSART_VoidSendString("|***********************************************************| \r\n");
		 MUSART_VoidSendString("|* Please Choose System ON Or System OFF  :                   \r\n");
		 MUSART_VoidSendString("|***********************************************************| \r\n");

		/*Scaning From The User The Status Of The System*/
		 Local_uint8SystemStatus = MUSART_VoidReceive();

		/*Checking If The Entered Value Is Turn System ON*/
		 if(SYSTEM_ON == Local_uint8SystemStatus)
		 {
			
			/*Printing That The System Turned ON*/
			 MUSART_VoidSendString("=> System ON \r\n");
			/*Turn OFF The Red LED And ON The Green One*/
			 MDIO_voidSetPinValue(PORTA,PIN2,HIGH);
			 MDIO_voidSetPinValue(PORTA,PIN3,LOW);
			/*Single Alarm Indicator*/
			 ASmart_uint8Alarm();

			/*Calling The ID & Password Check Function*/
			 Local_uint8UserValidation = ASmart_uint8PasswordCheck();

			 
			 if(Local_uint8UserValidation)
			 {
				/*Sending To The Other ECU Through SPI To Turn System ON*/
				 MSPI_uint8AsyncTranceiveData(SPI_SYSTEM_ON);

				 while(SYSTEM_OFF != Local_uint8SystemStatus)
				 {
					/*Printing to The User To Choose Option*/
					 MUSART_VoidSendString("|***********************************************************|\r\n");
					 MUSART_VoidSendString("|* Please choose an option from the below  :                 \r\n");
					 MUSART_VoidSendString("|* 1) To Control the Light System. 			                 \r\n");
					 MUSART_VoidSendString("|* 2) To Control the Air Conditioner. 		                 \r\n");
					 MUSART_VoidSendString("|* 3) To Control the Window curtain. 		                 \r\n");
					 MUSART_VoidSendString("|* 4) To Return Back to System Options. 	                 \r\n");
					 MUSART_VoidSendString("|***********************************************************|\r\n");
					/*Scaning From The Option*/
					 Local_uint8SystemOptions = MUSART_VoidReceive();

					 
					 switch(Local_uint8SystemOptions)
					 {
						case LIGHT_CONTROL :
						
								/*Printing to The User To Choose Turn ON or Turn OFF*/
								 MUSART_VoidSendString("|***********************************************************|\r\n");
								 MUSART_VoidSendString("|* 1) To Open  the Light System.                             \r\n");
								 MUSART_VoidSendString("|* 2) To Close the Light System.                             \r\n");
								 MUSART_VoidSendString("|***********************************************************|\r\n");
								/*Scaning From The User The Status Wanted*/
								 Local_uint8Component_ON_OFF = MUSART_VoidReceive();

								switch(Local_uint8Component_ON_OFF)
								{
									case COMPONENT_OPEN :
									
											/*Sending To The Other ECU Through SPI To Turn ON*/
											MSPI_uint8AsyncTranceiveData(SPI_LIGHT_ON);
											/*Single Alarm Indicator*/
											 ASmart_uint8Alarm();
									break;

									case COMPONENT_CLOSE :
									
											/*Sending To The Other ECU Through SPI To Turn OFF*/
											 MSPI_uint8AsyncTranceiveData(SPI_LIGHT_OFF);
											/*Double Alarm Indicator*/
											 ASmart_uint8Alarm();
											 ASmart_uint8Alarm();
									break;

									default:
									
											/*Printing An Error Message To the User To Enter A valid Option*/
											 MUSART_VoidSendString("Sorry Choose a Valid Option  : \r\n");
									break;
								}
						break;

						case A_C_CONTROL :
								
								/*Printing to The User To Choose Turn ON or Turn OFF*/
								 MUSART_VoidSendString("|***********************************************************|\r\n");
								 MUSART_VoidSendString("|* 1) To Open  the Air Conditioner.                          \r\n");
								 MUSART_VoidSendString("|* 2) To Close the Air Conditioner.                          \r\n");
								 MUSART_VoidSendString("|***********************************************************|\r\n");
								/*Scaning From The User The Status Wanted*/
								 Local_uint8Component_ON_OFF = MUSART_VoidReceive();

								switch(Local_uint8Component_ON_OFF)
								{
									case COMPONENT_OPEN :
											
											/*Sending To The Other ECU Through SPI To Turn ON*/
											 MSPI_uint8AsyncTranceiveData(SPI_A_C_ON);
											/*Single Alarm Indicator*/
											 ASmart_uint8Alarm();
									break;

									case COMPONENT_CLOSE :
									
											/*Sending To The Other ECU Through SPI To Turn OFF*/
											 MSPI_uint8AsyncTranceiveData(SPI_A_C_OFF);
											/*Double Alarm Indicator*/
											 ASmart_uint8Alarm();
											 ASmart_uint8Alarm();
									break;

									default:
									
										/*Printing An Error Message To the User To Enter A valid Option*/
										 MUSART_VoidSendString("=> Sorry Choose a Valid Option  : \r\n");
									break;
								}
						break;

						case CURTAIN_CONTROL :
						
								/*Printing to The User To Choose Turn ON or Turn OFF*/
								 MUSART_VoidSendString("|***********************************************************|\r\n");
								 MUSART_VoidSendString("|* 1) To Open  the Window curtain.                           \r\n");
								 MUSART_VoidSendString("|* 2) To Close the Window curtain.                           \r\n");
								 MUSART_VoidSendString("|***********************************************************|\r\n");
								/*Scaning From The User The Status Wanted*/
								 Local_uint8Component_ON_OFF = MUSART_VoidReceive();

								switch(Local_uint8Component_ON_OFF)
								{
									case COMPONENT_OPEN :
									
											/*Sending To The Other ECU Through SPI To Turn ON*/
											 MSPI_uint8AsyncTranceiveData(SPI_CURTAIN_OPEN);
											/*Single Alarm Indicator*/
											 ASmart_uint8Alarm();
									break;

									case COMPONENT_CLOSE :
									
											/*Sending To The Other ECU Through SPI To Turn OFF*/
											 MSPI_uint8AsyncTranceiveData(SPI_CURTAIN_CLOSE);
											/*Double Alarm Indicator*/
											 ASmart_uint8Alarm();
											 ASmart_uint8Alarm();
									break;

									default:
									
											/*Printing An Error Message To the User To Enter A valid Option*/
											 MUSART_VoidSendString("=> Sorry Choose a Valid Option  : \r\n");
									break;
								}
						break;

						case BACK :
						
								/*Set System Status To Be OFF*/
								 Local_uint8SystemStatus = SYSTEM_OFF;
						break;

						default:
						
								/*Printing An Error Message To the User To Enter A valid Option*/
								 MUSART_VoidSendString("=> Sorry Choose a Valid Option  : \r\n");
						break;
					 }
				 }
			 }
		 }

		/*Checking If The Entered Value Is Turn System OFF*/
		 else if(SYSTEM_OFF == Local_uint8SystemStatus)
		 {
			/*Sending To The Other ECU Through SPI To Turn System OFF*/
			 MSPI_uint8AsyncTranceiveData(SPI_SYSTEM_OFF);
			/*Printing That The System Turned OFF*/ 
			 MUSART_VoidSendString("=> System OFF \r\n");
			 
			/*Double Alarm Indicator*/
			 ASmart_uint8Alarm();
			 ASmart_uint8Alarm();
			/*Turn OFF The Green LED And ON The Red One*/
			 MDIO_voidSetPinValue(PORTA,PIN2,LOW);
			 MDIO_voidSetPinValue(PORTA,PIN3,HIGH);
		 }
		 else
		 {
			/*Printing An Error Message To the User To Enter A valid Option*/
			 MUSART_VoidSendString("=> Sorry Choose a Valid Option  : \r\n");
		 }
	 }
}