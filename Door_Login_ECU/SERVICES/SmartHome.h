/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					AAMK Team							09 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: Smart Home                                                        							                      *
* ! File Name	: SmartHome.h                                 	                    							                      *
* ! Description : This file has all definitions needed						       							                          *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: Service                  						                                         							  *
**************************************************************************************************************************************/
#ifndef SMARTHOME_H
#define SMARTHOME_H

#define USERS_NUM				10
#define TRIALS_NUM				3

#define	SYSTEM_ON				'9'
#define	SYSTEM_OFF				'8'

#define	PASSWORD_VALID			1
#define	PASSWORD_INVALID		0

#define	ID_VALID				1
#define	ID_INVALID				0

#define	LIGHT_CONTROL			'1'
#define	A_C_CONTROL				'2'
#define	CURTAIN_CONTROL			'3'
#define	BACK					'4'

#define	COMPONENT_OPEN			'1'
#define	COMPONENT_CLOSE			'2'

/****************************************************** SPI Send Values **************************************************************/

#define SPI_LIGHT_ON			 0
#define SPI_LIGHT_OFF			 1
#define SPI_A_C_ON 				 2
#define SPI_A_C_OFF 			 3
#define SPI_CURTAIN_OPEN 		 4
#define SPI_CURTAIN_CLOSE		 5
#define SPI_SYSTEM_OFF			 8
#define SPI_SYSTEM_ON			 9


/******************************************************** Users IDs ******************************************************************/

#define USER_ID_1				'A'
#define USER_ID_2				'B'
#define USER_ID_3				'C'
#define USER_ID_4				'D'
#define USER_ID_5				'E'
#define USER_ID_6				'F'
#define USER_ID_7				'G'
#define USER_ID_8				'H'
#define USER_ID_9				'I'
#define USER_ID_10				'J'

/***************************************************** Users Passwords **************************************************************/

#define USER_PASSWORD_1			'1'
#define USER_PASSWORD_2     	'2'
#define USER_PASSWORD_3     	'3'
#define USER_PASSWORD_4     	'4'
#define USER_PASSWORD_5     	'5'
#define USER_PASSWORD_6     	'6'
#define USER_PASSWORD_7     	'7'
#define USER_PASSWORD_8     	'8'
#define USER_PASSWORD_9     	'9'
#define USER_PASSWORD_10    	'0'

/*************************************** Array of Structure of IDs & Passwords Values ***********************************************/

#define PASSWORD_ARRAY_INIT    {{USER_ID_1,USER_PASSWORD_1},\
								{USER_ID_2,USER_PASSWORD_2},\
								{USER_ID_3,USER_PASSWORD_3},\
								{USER_ID_4,USER_PASSWORD_4},\
								{USER_ID_5,USER_PASSWORD_5},\
								{USER_ID_6,USER_PASSWORD_6},\
								{USER_ID_7,USER_PASSWORD_7},\
								{USER_ID_8,USER_PASSWORD_8},\
								{USER_ID_9,USER_PASSWORD_9},\
								{USER_ID_10,USER_PASSWORD_10}}
								
/****************************************** Structure To Store User ID & Password ***************************************************/

typedef struct
{
	uint8 	ID;
	uint8	Password;
	
}Global_StructUsersPasswords;

//************************************************************************************************************************************/
/***************************************************** Function Definitions **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: ASmart_VoidInit																			                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function to Init All Perepheral needad													                      *
**************************************************************************************************************************************/
void ASmart_VoidInit();
/**************************************************************************************************************************************
* Function Name		: ASmart_VoidE2promPasswordStore															                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: 													                     										  *
**************************************************************************************************************************************/
uint8 ASmart_uint8PasswordCheck();
/**************************************************************************************************************************************
* Function Name		: ASmart_VoidE2promPasswordStore															                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: 													                     										  *
**************************************************************************************************************************************/
void ASmart_uint8Alarm();


#endif /*SMARTHOME_H*/
