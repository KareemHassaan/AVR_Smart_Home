/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					AAMK Team							09 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: Smart Home                                                        							                      *
* ! File Name	: SmartHome.c                                                       							                      *
* ! Description : This file has the implementation of Basic of Smart Home functions Controlled By HC-05 Blutooth Module         	  *
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
/************************************************** Self Layer Inclusions ************************************************************/

/************************************************** Self Files Inclusions ************************************************************/
#include"..\SERVICES\SmartHome.h"  

/***************************************************** Global Variables **************************************************************/
Global_StructUsersPasswords GLobal_ArrIDPasswords[USERS_NUM] = PASSWORD_ARRAY_INIT; //Global Array for IDs and Passwords of the users

/*************************************************************************************************************************************/
/***************************************************** Functions Definition **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: ASmart_VoidInit																			                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Initialize All Perepheral and Pins needad										                      *
**************************************************************************************************************************************/
void ASmart_VoidInit()
{
	/*Initiate TX and RX Of USART Output Pins Pin0 -> RX, Pin1 -> TX*/
	 MDIO_voidSetPinDirection(PORTD,PIN0,INPUT);
	 MDIO_voidSetPinDirection(PORTD,PIN1,OUTPUT);
	/*Initiate The Alarm Pins (Buzzer), Pin0 -> Switch OFF, Pin1 -> Buzzer Vcc*/
	 MDIO_voidSetPinDirection(PORTA,PIN0,INPUT);
	 MDIO_voidSetPinValue(PORTA,PIN0,HIGH);
	 MDIO_voidSetPinDirection(PORTA,PIN1,OUTPUT);
	/*Initiate The Indicators LEDs Pins Pin2 -> Green LED, Pin3 -> Green LED*/
	 MDIO_voidSetPinDirection(PORTA,PIN2,OUTPUT);
	 MDIO_voidSetPinDirection(PORTA,PIN3,OUTPUT);
	 MDIO_voidSetPinValue(PORTA,PIN3,HIGH);

	/*Initiate Function Call of The USART*/
	 MUSART_VoidInit();
	/*Initiate Function Call of TIMER0*/
	 MTIMERS_VoidTimer0Init();
	/*Master Initiate Function Call of The SPI*/ 
	 MSPI_voidMasterInit();
}

/**************************************************************************************************************************************
* Function Name		: ASmart_uint8PasswordCheck																	                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Scan the ID and Password From the User and Check its validity. 									  *
**************************************************************************************************************************************/
uint8 ASmart_uint8PasswordCheck()
{
	/*Variable to store the Number of Tries of Entering Password*/
	 uint8  Local_uint8PasswordTrials 	= TRIALS_NUM;
	/*Variable to store the Status of Password Validation*/
	 uint8  Global_uint8PasswordCheck 	= PASSWORD_INVALID;
	 /*Variable to store the Status of ID Validation*/
	 uint8  Global_uint8IDCheck 		= ID_INVALID;
	/*Variable To Scan in It the Entered Password*/
	 uint8  Local_uint8EnteredPassword  = 0;
	/*Variable To Scan in It the Entered ID*/
	 uint8	Local_uint8EnteredID 		= 0;
	/*Loop Counter To searching for the ID is Exist or Not*/
	 uint8  Local_uint8IDLoopCounter 	= 0;
	/*Variable To Store the Position Of Wanted ID*/
	 uint8  Local_uint8WantedID		 	= 0;

	
	/*Printing To The User To Enter His ID*/
	 MUSART_VoidSendString("|***********************************************************| \r\n");
	 MUSART_VoidSendString("|* Please Enter your ID :                                     \r\n");
	 MUSART_VoidSendString("|***********************************************************| \r\n");
	
	/*Scaning From The User His ID Through Bluetooth Module Interfaced by USART*/
	 Local_uint8EnteredID = MUSART_VoidReceive();
	
	
	/*Checking If The Entered ID Is Exist or Not*/
	 for(Local_uint8IDLoopCounter = 0; Local_uint8IDLoopCounter < USERS_NUM; Local_uint8IDLoopCounter++)
	 {

		 if(Local_uint8EnteredID == GLobal_ArrIDPasswords[Local_uint8IDLoopCounter].ID)
		 {
			/*Change The Entered ID Status To Valid*/
			 Global_uint8IDCheck = ID_VALID;
			/*Storing The Position Of The WantedID*/
			 Local_uint8WantedID = Local_uint8IDLoopCounter;
		 }
	 }
	 
	 
	 if(Global_uint8IDCheck == ID_VALID)
	 {
		 while((Local_uint8PasswordTrials != 0) && (Global_uint8PasswordCheck == PASSWORD_INVALID))
		 {
			/*Printing To The User To Enter His Password*/
			 MUSART_VoidSendString("|***********************************************************| \r\n");
			 MUSART_VoidSendString("|* Please Enter your Password :                               \r\n");
			 MUSART_VoidSendString("|***********************************************************| \r\n");
			 
			/*Scaning From The User His Password Through Bluetooth Module Interfaced by USART*/
			 Local_uint8EnteredPassword = MUSART_VoidReceive();

			/*Check If The Entered Password Is Valid Or Not*/
			 if(Local_uint8EnteredPassword ==  GLobal_ArrIDPasswords[Local_uint8WantedID].Password)
			 {
				/*The Password Is Valid and Opening The Door*/
				 MUSART_VoidSendString("=> Welcome, Door Opened\r\n");
				/*Single Alarm Opening Inicator*/
				 ASmart_uint8Alarm();

				/*Busy Wait for 2 Sec*/
				 MTIMERS_voidSetBusyWait(2000);

				/*Automatic Closing The Door*/ 
				 MUSART_VoidSendString("=> Door Closed\r\n");
				/*Double Alarm Closing Inicator*/
				 ASmart_uint8Alarm();
				 ASmart_uint8Alarm();
				/*Change The Entered Password Status To Valid*/
				 Global_uint8PasswordCheck = PASSWORD_VALID;
			 }
			 else
			 {
				/*Printing an Error Message That the Password Is Invalid and Try Again*/
				 MUSART_VoidSendString("=> Sorry the Password Entered is Invalid, Try again. \r\n");
			 }

			/*Decrement The Loop Counter (Number of Tries)*/
			 Local_uint8PasswordTrials--;
		 }

		/*Number Of Tries Ran out*/
		 if((Local_uint8PasswordTrials == 0) && (Global_uint8PasswordCheck == PASSWORD_INVALID))
		 {
			/*Printing Error Message That User Is Not Authorized*/
			 MUSART_VoidSendString("=> Not Authorized Password  \r\n");

			/*Turn Security Alarm ON Till Closed Manually*/
			 while(MDIO_uint8GetPinValue(PORTA,PIN0))
			 {
				 ASmart_uint8Alarm();
			 }
		 }
	 }
	 else
	 {
		/*Printing an Error Message That the ID Is Invalid*/
		 MUSART_VoidSendString("=> Sorry your ID is Invalid \r\n");
	 }

	/*Return The Login Process Status*/
	 return Global_uint8PasswordCheck;
}

/**************************************************************************************************************************************
* Function Name		: ASmart_uint8Alarm																			                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Alarm													                   							  *
**************************************************************************************************************************************/
void ASmart_uint8Alarm()
{
	/*Set the Alarm (Buzzer) And Red LED ON*/
	 MDIO_voidSetPinValue(PORTA,PIN1,HIGH);
	 MDIO_voidSetPinValue(PORTA,PIN3,HIGH);
	/*Busy Wait for 200 ms*/
	 MTIMERS_voidSetBusyWait(200);
	
	/*Set the Alarm (Buzzer) And Red LED OFF*/
	 MDIO_voidSetPinValue(PORTA,PIN1,LOW);
	 MDIO_voidSetPinValue(PORTA,PIN3,LOW);
	/*Busy Wait for 200 ms*/
	 MTIMERS_voidSetBusyWait(200);
}