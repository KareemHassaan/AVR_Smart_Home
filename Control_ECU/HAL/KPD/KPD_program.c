/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 15 Dec. 2021                                         *
 *  Layer  : HAL                                                  *
 *  Version: v1.1                                                 *
 * ***************************************************************/

/******** Library inclusions **********/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#define F_CPU   8000000UL

/********** Lower Layer inclusion ************/

#include "../../MCAL/DIO/DIO_interface.h"
#include <util/delay.h>

/********** Self Layer Inclusions ************/


/********** Self Files Inclusions ************/
#include "KPD_interface.h"
#include "KPD_private.h"
#include "KPD_config.h"
#include  "../LCD/LCD_interface.h"

void HKPD_voidInit()
{
	/*Setting the Row Direction to Input*/
	MDIO_voidSetPinDirection(KPD_PORT,KPD_ROW0_PIN,INPUT) ;
	MDIO_voidSetPinDirection(KPD_PORT,KPD_ROW1_PIN,INPUT) ;
	MDIO_voidSetPinDirection(KPD_PORT,KPD_ROW2_PIN,INPUT) ;
	MDIO_voidSetPinDirection(KPD_PORT,KPD_ROW3_PIN,INPUT) ;
	/*Setting the Row State to Pull UP*/
	MDIO_voidSetPinValue(KPD_PORT,KPD_ROW0_PIN,PULL_UP)   ;
	MDIO_voidSetPinValue(KPD_PORT,KPD_ROW1_PIN,PULL_UP)   ;
	MDIO_voidSetPinValue(KPD_PORT,KPD_ROW2_PIN,PULL_UP)   ;
	MDIO_voidSetPinValue(KPD_PORT,KPD_ROW3_PIN,PULL_UP)   ;
	/*Setting the column Direction to output*/
	MDIO_voidSetPinDirection(KPD_PORT,KPD_COL0_PIN,OUTPUT) ;
	MDIO_voidSetPinDirection(KPD_PORT,KPD_COL1_PIN,OUTPUT) ;
	MDIO_voidSetPinDirection(KPD_PORT,KPD_COL2_PIN,OUTPUT) ;
	MDIO_voidSetPinDirection(KPD_PORT,KPD_COL3_PIN,OUTPUT) ;
	/*Setting the column value to high(deactivated)*/
	MDIO_voidSetPinValue(KPD_PORT,KPD_COL0_PIN,HIGH)   ;
	MDIO_voidSetPinValue(KPD_PORT,KPD_COL1_PIN,HIGH)   ;
	MDIO_voidSetPinValue(KPD_PORT,KPD_COL2_PIN,HIGH)   ;
	MDIO_voidSetPinValue(KPD_PORT,KPD_COL3_PIN,HIGH)   ;

}

u8 HKPD_u8GetPressedKey(void)
{
	u8 Local_u8PressedKey=0xff ;
	u8 Local_u8ColArry[4] = {KPD_COL0_PIN,KPD_COL1_PIN,KPD_COL2_PIN,KPD_COL3_PIN};
	u8 Local_u8RowArry[4] = {KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};
	u8 Local_u8PinState=0 ;
	u8 Local_u8ColIterator ;
	u8 Local_u8RowIterator ;
	u8 Local_u8MatrixArry[4][4] = KPD_ARRAY_VAL ;
	for(Local_u8ColIterator=0 ; Local_u8ColIterator < 4 ; Local_u8ColIterator++ )
	{
		MDIO_voidSetPinValue(KPD_PORT,Local_u8ColArry[Local_u8ColIterator],LOW) ;
			for(Local_u8RowIterator=0 ; Local_u8RowIterator<4 ;Local_u8RowIterator++)
			{
				Local_u8PinState =MDIO_u8GetPinValue(KPD_PORT,Local_u8RowArry[Local_u8RowIterator]) ;
				if(Local_u8PinState == 0 )
				{	while(Local_u8PinState == 0)
					{
						Local_u8PinState  =MDIO_u8GetPinValue(KPD_PORT,Local_u8RowArry[Local_u8RowIterator]);
						Local_u8PressedKey = Local_u8MatrixArry[Local_u8ColIterator][Local_u8RowIterator] ;

					}
					_delay_ms(5);
					if(Local_u8PressedKey==' ')
					{
						HLCD_voidGoToXY(0,0);
						HLCD_voidClearAll() ;
					}
					else
					return Local_u8PressedKey ;
				}

			}
		MDIO_voidSetPinValue(KPD_PORT,Local_u8ColArry[Local_u8ColIterator],HIGH) ;
	}
	
	return Local_u8PressedKey ;

}
