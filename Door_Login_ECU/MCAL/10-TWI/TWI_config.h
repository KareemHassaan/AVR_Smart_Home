/**************************************************************************************************************************************
* LOG:                                                                   							   								  *
* VERSION					AUTHOR           					DATE 						DESCRIPTION 		   					  *
* 1.0.0 					Kareem Hassaan						04 JAN,2022					- Initial Creation						  *
**************************************************************************************************************************************/
/**************************************************************************************************************************************
* ! Title      	: TWI Driver                                     							                                          *
* ! File Name	: TWI_config.h                                                      							                      *
* ! Description : This file has the Configrations needed		     		        	 						                      *
* ! Compiler  	: GNU AVR cross Compiler                                            							                      *
* ! Target 	  	: Atmega32 Micro-Controller                                         							                      *
* ! Layer 	  	: MCAL                  						                                         							  *
**************************************************************************************************************************************/
#ifndef TWI_CONFIG_H
#define TWI_CONFIG_H

/**************************************************************************************************************************************
* MACRO		: 	To Adjust Master Prescaller																			         		  *
* options	:	PRESCALLER_1		/		PRESCALLER_4		/		PRESCALLER_16		/		PRESCALLER_64		/		      *
**************************************************************************************************************************************/
#define MASTER_PRESCALLER_VALUE				PRESCALLER_1							

/**************************************************************************************************************************************
* MACRO		: 	To Turn ACK on or off 																				         		  *
* options	:	ACK_ENABLE			/		ACK_DISABLE			/			  														  *
**************************************************************************************************************************************/
#define ACKNOWLEDGE_ENABLE_VALUE			ACK_ENABLE	
/**************************************************************************************************************************************
* MACRO		: 	To Adjust CPU Frequency																				         		  *
* options	:																													      *
**************************************************************************************************************************************/
#define CPU_FREQUENCY						8000000.0F
/**************************************************************************************************************************************
* MACRO		: 	To Adjust SCL Frequency																				         		  *
* options	:																													      *
**************************************************************************************************************************************/
#define SCL_FREQUENCY_KHZ					100.0F


#endif /*TWI_CONFIG_H*/  