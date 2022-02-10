/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 22 Dec. 2021                                         *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "GIE_interface.h"
#include "GIE_private.h"
#include "GIE_config.h"


void MGIE_voidInit()
{
    #if GIE == ENABLE
        SET_BIT(SREG,GIE_BIT) ;
    #else
        CLEAR_BIT(SREG,GIE_BIT) ;
    #endif
}


void MGIE_voidEnable()
{
    SET_BIT(SREG,GIE_BIT) ;
}


void MGIE_voidDisable()
{
    CLEAR_BIT(SREG,GIE_BIT) ;
}