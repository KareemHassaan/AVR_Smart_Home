/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 22 Dec. 2021                                         *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef EXIT_INTERFACE_H
#define EXIT_INTERFACE_H

#define		  INT0			  0
#define		  INT1			  1
#define		  INT2			  2

#define       ENABLE          1
#define       DISABLE         0





void MEXTI_voidInit() ;
s8 MEXTI_voidInturrupt(u8 Copy_u8InterruptValue,u8 Copy_u8State) ;



#endif
