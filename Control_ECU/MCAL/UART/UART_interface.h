/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 2 Jan. 2022                                          *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

void MUSART_voidInit(void) ;
void MUSART_voidTransmitDataSync ( u8 Copy_u8Data );
void MUSART_voidReceiveDataSync(u8 *Copy_pu8ReceivedData);
void MUSART_voidSendNumber( u32 Copy_u32Number);
void MUSART_voidSendString(u8 *Pointer_u8String);
#endif
