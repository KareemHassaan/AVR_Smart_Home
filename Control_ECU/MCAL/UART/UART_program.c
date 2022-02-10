/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 2 Jan. 2022                                          *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#include "UART_private.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

void MUSART_voidInit(void)
 {

 	 u8 Local_u8UCSRCTemp = 0 ;
    /* Enable Tx And Rx */
    SET_BIT(UCSRB,USCRB_RXEN) ;
    SET_BIT(UCSRB,USCRB_TXEN) ;

    /*Set character size */
    SET_BIT(Local_u8UCSRCTemp,UCSRC_UCSZ0) ;
    SET_BIT(Local_u8UCSRCTemp,UCSRC_UCSZ1) ;
    CLEAR_BIT(UCSRB , USCRB_UCSZ2)         ;

    /* 1 Stop Bit */
    CLEAR_BIT(Local_u8UCSRCTemp,UCSRC_USBS);

    /* Parity Disable */
    CLEAR_BIT(Local_u8UCSRCTemp,UCSRC_UPM0);
    CLEAR_BIT(Local_u8UCSRCTemp,UCSRC_UPM1);

    /*   */
    CLEAR_BIT(UCSRC,UCSRC_UMSEL) ;

    /* Select USCRC Register */
    SET_BIT(Local_u8UCSRCTemp,UCSRC_URSEL) ;
    /* Put data in register */
    UCSRC = Local_u8UCSRCTemp ;

    /* Set baudRate to be 1200 */
    UBRRL = 112 ;
    CLEAR_BIT(UBRRH,UBRRH_URSEL) ;
    UBRRH = 2 					;
}

void MUSART_voidTransmitDataSync ( u8 Copy_u8Data )
{
    /* Check if buffer is empty */
    while( GET_BIT(UCSRA,USCRA_UDRE) == 0 ) ;
    /* Set data to UDR Register */
    UDR = Copy_u8Data ;
    /* Polling on sending flag */
    while ( GET_BIT(UCSRA,USCRA_TXC) == 0) ;
}

void  MUSART_voidReceiveDataSync(u8 *Copy_pu8ReceivedData)
{
    /* Polling till receiving data */
    while ( GET_BIT(UCSRA,USCRA_RXC) == 0) ;
    /* Putting data in pointer */
    *Copy_pu8ReceivedData = UDR ;
}


void MUSART_voidSendNumber( u32 Copy_u32Number)
{
	u16 Local_u16Temp=Copy_u32Number ;
	u8 Local_u8CharArr[6]={} ;
	s8 Local_u8NumOfDigits = -1 ;
	u8 Local_u8ArryCounter = 0 ;
	s8 Local_u8LoopCounter ;
	while(Copy_u32Number != 0)
	{
		Local_u16Temp =Copy_u32Number  ;
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
		Copy_u32Number /= 10 ;
	}
	for(Local_u8LoopCounter=Local_u8NumOfDigits ; Local_u8LoopCounter>=0 ; Local_u8LoopCounter--)
	{
		MUSART_voidTransmitDataSync(Local_u8CharArr[Local_u8LoopCounter]) ;
	}

}

void MUSART_voidSendString(u8 *Pointer_u8String)
{
	u8 Local_u8ArryCounter=0 ;

	while(Pointer_u8String[Local_u8ArryCounter]!='\0')
	{
		MUSART_voidTransmitDataSync(Pointer_u8String[Local_u8ArryCounter]) ;
		Local_u8ArryCounter++ ;
	}
}

