/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 3 Jan. 2022                                          *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef WTD_PRIVATE_H
#define WTD_PRIVATE_H

#define         WDTCR       *(volatile u8*)(0x41)    //Watch Dog timer control register
#define         WDTCR_WDP0  0                        //Watch dog timer prescaler bit 0
#define         WDTCR_WDP1  1                        //Watch dog timer prescaler bit 1
#define         WDTCR_WDP2  2                        //Watch dog timer prescaler bit 2
#define         WDTCR_WDE   3                        //Watch dog enable
#define         WDTCR_WDTOE 4                        //watch dog turn-off enable

#define         WDTCR_PREMASK   0b11111000      

#endif