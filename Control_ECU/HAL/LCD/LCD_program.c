/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 12 Dec. 2021                                         *
 *  Layer  : HAL                                                  *
 *  Version: v1.0                                                 *
 * ***************************************************************/

/******** Library inclusions **********/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#define F_CPU   8000000UL
#include <util/delay.h>

/********** Lower Layer inclusion ************/

#include "../../MCAL/DIO/DIO_interface.h"

/********** Self Layer Inclusions ************/


/********** Self Files Inclusions ************/
#include "../LCD/LCD_interface.h"
#include "../LCD/LCD_private.h"
#include "../LCD/LCD_config.h"

void HLCD_voidInit()
{
        /*send data port to output port */
		MDIO_voidSetPort(LCD_DATA_PORT,OUTPUT) ;
        /* set control pins to output pins */
		MDIO_voidSetPinDirection(LCD_CTRL_PORT , LCD_EN_PIN , OUTPUT) ;
		MDIO_voidSetPinDirection(LCD_CTRL_PORT , LCD_RW_PIN , OUTPUT) ;
		MDIO_voidSetPinDirection(LCD_CTRL_PORT , LCD_RS_PIN , OUTPUT) ;
        /* wait for 30 mili second */
        _delay_ms(40) ;
        u8 Local_u8Set = Function_Set_Command ;
        Local_u8Set |= FontSize  ;
        Local_u8Set |= TwoLines  ;
        /*send function set command */
        HLCD_voidSendCommands(Local_u8Set) ;
        /*send display set command */
        u8 Local_u8Display = Display_Set_Command ;
        if(Blink)
        {
        	SET_BIT(Local_u8Display ,0);
        }
        if(Cursor)
        {
           SET_BIT(Local_u8Display ,1);
        }
        HLCD_voidSendCommands(Local_u8Display ) ;
        /*send clear set command */
        HLCD_voidSendCommands(0b00000001) ;
}

static void HLCD_voidSendCommands(u8 Copy_u8Command)
{
    
    /* Set RS,RW to be low */
    MDIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN ,LOW ) ;
    MDIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN ,LOW ) ;
    
    /* Set command on Data port */
    MDIO_voidSetSpecificPortOutPut(LCD_DATA_PORT , Copy_u8Command ) ;

    /* Set enable pin to high for certain time */
    MDIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN ,HIGH ) ;
    _delay_ms(2) ;
    MDIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN ,LOW ) ;
}

void HLCD_voidSendData(u8 Copy_u8CData)
{
    /* Set RS,RW to be low */
    MDIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RW_PIN ,LOW ) ;
    MDIO_voidSetPinValue(LCD_CTRL_PORT,LCD_RS_PIN ,HIGH) ;

    /* Set Data on Data port */
    MDIO_voidSetSpecificPortOutPut(LCD_DATA_PORT , Copy_u8CData ) ;

    /* Set enable pin to high for certain time */
    MDIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN ,HIGH ) ;
    _delay_ms(2) ;
    MDIO_voidSetPinValue(LCD_CTRL_PORT,LCD_EN_PIN ,LOW ) ;
}


void HLCD_voidSendNumber( u16 Copy_u16Number)
{
	u16 Local_u16Temp=Copy_u16Number ;
	u8 Local_u8CharArr[5]={} ;
	s8 Local_u8NumOfDigits = -1 ;
	u8 Local_u8ArryCounter = 0 ;
	s8 Local_u8LoopCounter ;
	while(Copy_u16Number != 0)
	{
		Local_u16Temp =Copy_u16Number  ;
		Local_u16Temp %= 10 ;

		if(Local_u16Temp==0)
		{
			Local_u8CharArr[Local_u8ArryCounter] = 48 ;
		}
		else
		{
			Local_u8CharArr[Local_u8ArryCounter] = Local_u16Temp+48 ;
		}
		Local_u8NumOfDigits++ ;
		Local_u8ArryCounter++ ;
		Copy_u16Number /= 10 ;
		//HLCD_voidSendData(Local_u8NumOfDigits+48) ;
	}
	for(Local_u8LoopCounter=Local_u8NumOfDigits ; Local_u8LoopCounter>=0 ; Local_u8LoopCounter--)
	{
		HLCD_voidSendData(Local_u8CharArr[Local_u8LoopCounter]) ;
	}

}


void HLCD_voidSendString(u8 *Pointer_u8String)
{
	u8 Local_u8ArryCounter=0 ;
	u8 Local_u8CharCounter=0 ;
	while(Pointer_u8String[Local_u8ArryCounter]!='\0')
	{
		if(Local_u8CharCounter==16)
		{
			HLCD_voidGoToXY(0,1);
		}
		HLCD_voidSendData(Pointer_u8String[Local_u8ArryCounter]) ;
		Local_u8ArryCounter++ ;
		Local_u8CharCounter++ ;
	}
}



void HLCD_voidGoToXY(u8 Copy_u8XPosition , u8 Copy_u8YPosition)
{   u8 Local_u8PositionAddress ;
    /* Getting Address*/
    if(Copy_u8YPosition == 0)
    {
        Local_u8PositionAddress = Copy_u8XPosition ;
    }
    else if(Copy_u8YPosition == 1)
    {
        Local_u8PositionAddress = Copy_u8XPosition + POSITION_FIXED_ADDRES ;
    }
    else
    {
        /*Error*/
    }
    /*Set the 7ths bit to 1 for command*/
    SET_BIT(Local_u8PositionAddress,7);
    /*Send command*/
    HLCD_voidSendCommands(Local_u8PositionAddress) ;
}


void HLCD_voidClearAll()
{
	HLCD_voidSendCommands(0x01) ;
}

void HLCD_voidSendCustomePattern(u8 *Pointer_u8Pattern ,
								 u8 Copy_u8PatternNum ,
								 u8 Copy_u8XPosition ,
								 u8 Copy_u8YPosition )
{
	u8 Local_u8LoopCounter ;
	/*Calculate which byte in CGRAM to start writing*/
	u8 Local_u8AddresByte = 8*Copy_u8PatternNum ;
	SET_BIT(Local_u8AddresByte,6);
	CLEAR_BIT(Local_u8AddresByte,7);

	HLCD_voidSendCommands(Local_u8AddresByte);
	/* kda ay data htegy httsgl fl CGRAM mn awel el addres Local_u8AddresByte  */

	for(Local_u8LoopCounter=0 ; Local_u8LoopCounter<8 ;Local_u8LoopCounter++)
	{
		HLCD_voidSendData(Pointer_u8Pattern[Local_u8LoopCounter]) ;
	}

	HLCD_voidGoToXY(Copy_u8XPosition,Copy_u8YPosition) ;

	HLCD_voidSendData(Copy_u8PatternNum) ;

}





