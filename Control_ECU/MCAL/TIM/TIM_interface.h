/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 28 Dec. 2021                                         *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef TIM_INTERFACE_H
#define TIM_INTERFACE_H


void MTIMERS_voidTimer0Init()	 ;
void MTIMERS_voidTimer1Init()    ;
void MTIMERS_voidTimer2Init()	 ;


void MTIMERS_voidTimer0SetPreloadValue(u8 Copy_u8PreloadValue) ;
void MTIMERS_voidTimer2SetPreloadValue(u8 Copy_u8PreloadValue) ;

void MTIMERS_voidTimer0SetCompareMatchValue(u8 Copy_u8CompareMatchValue)   ;
void MTIMERS_voidTimer1SetCompareMatchValue(u16 Copy_u16CompareMatchValue) ;
void MTIMERS_voidTimer2SetCompareMatchValue(u8 Copy_u8CompareMatchValue)   ;

void MTIMERS_voidTimer1SetTopValue(u16 Copy_u16TopValue);

void MTIMERS_voidSetBusyWait(u32 Copy_u32MicroSeconds) ;





#endif
