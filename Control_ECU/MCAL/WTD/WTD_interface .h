/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 3 Jan. 2022                                          *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef WTD_INTERFACE_H
#define WTD_INTERFACE_H

#define     WDT_16_3_ms         0
#define     WDT_32_5_ms         1
#define     WDT_1_5             6

void        MWTD_voidEnable()                  ;
void        MWTD_voidSleep(u8 Copy_u8TimerOut) ;
void        MWTD_voidDisable()                 ;

#endif