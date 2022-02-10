/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 3 Jan. 2022                                          *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "WTD_interface .h"
#include "WTD_config.h"
#include "WTD_private.h"

void MWTD_voidEnable()
{
    /*Set The WDE bit to Enable*/
    SET_BIT(WDTCR,WDTCR_WDE) ;

}

void MWTD_voidSleep(u8 Copy_u8TimerOut)
{
    if(Copy_u8TimerOut <= 7)
    {
        WDTCR &= WDTCR_PREMASK   ;
        WDTCR |= Copy_u8TimerOut ;
    }
}

void MWTD_voidDisable()
{
    /* 1-Write 1 to WDE & WDTOE in same operation */
    WDTCR = (1<<WDTCR_WDE) | (1<<WDTCR_WDTOE) ;
    /* 2- within the next four cycles write 0 to WDE */
    WDTCR = 0x00 ;

}
