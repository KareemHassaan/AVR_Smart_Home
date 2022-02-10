/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 5 Jan. 2022                                          *
 *  Layer  : HAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

void HEEPROM_voidWriteData( u16 Copy_u16Location , u8 Copy_u8Data )  ;
void HEEPROM_voidReadData (u16 Copy_u16Location , u8 *Copy_pu8ReceivedData ) ;


#endif