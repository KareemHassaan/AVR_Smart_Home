/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 14 Dec. 2021                                         *
 *  Layer  : HAL                                                  *
 *  Version: v1.0                                                 *
 * ***************************************************************/

#ifndef KPD_CONFIG_H
#define KPD_CONFIG_H

#define KPD_PORT        PORTC
/*Conifg. of row pins*/
#define KPD_ROW0_PIN    PIN0
#define KPD_ROW1_PIN    PIN1
#define KPD_ROW2_PIN    PIN2
#define KPD_ROW3_PIN    PIN3
/*Conifg. of col pins*/
#define KPD_COL0_PIN    PIN4
#define KPD_COL1_PIN    PIN5
#define KPD_COL2_PIN    PIN6
#define KPD_COL3_PIN    PIN7

#define KPD_ARRAY_VAL {{'7','4','1',' '},{'8','5','2','0'},{'9','6','3','='},{'/','X','-','+'}}



#endif
