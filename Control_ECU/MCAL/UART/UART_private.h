/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 2 Jan. 2022                                          *
 *  Layer  : MCAL                                                 *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#ifndef UART_PRIVATE_H
#define UART_PRIVATE_H


#define         UCSRA       *(volatile u8*)(0x2B)  //UART Control & status register A
#define         USCRA_RXC   7                      //Receieve Complete Flag
#define         USCRA_TXC   6                      //Transmit Complete Flag
#define         USCRA_UDRE  5                      //Data Register Empty Flag
#define         USCRA_FE    4                      //Frame Error Flag
#define         USCRA_DORC  3                      //Data OverRun Flag
#define         USCRA_PE    2                      //Parity Error Flag
#define         USCRA_U2x   1                      //Double the USART Transmission speed
#define         USCRA_MPCM  0                      //Multi-processor communication mode


#define         UCSRB       *(volatile u8*)(0x2A)   //UART Control & status register B
#define         USCRB_RXCIE  7                      //RX complete interrupt Enable
#define         USCRB_TXCIE  6                      //TX complete interuupt enable
#define         USCRB_UDRIE  5                      //Data Register Empty interrupt
#define         USCRB_RXEN   4                      //Receiver Enable
#define         USCRB_TXEN   3                      //Transmitter Enable
#define         USCRB_UCSZ2  2                      //Character Size bit 2
#define         USCRB_RXB8   1                      //Receive Data  Bit 8
#define         USCRB_TXB8   0                      //Transmit Data bit 8

 
#define         UCSRC       *(volatile u8*)(0x40)  //UART Control & status register C
#define         UCSRC_URSEL  7                     //Register Select
#define         UCSRC_UMSEL  6                     //Mode Select asy/syn
#define         UCSRC_UPM1   5                     //Parity Mode Bit 1
#define         UCSRC_UPM0   4                     //Parity Mode Bit 0
#define         UCSRC_USBS   3                     //Stop Bit Select
#define         UCSRC_UCSZ1  2                     //Character Size Bit 1
#define         UCSRC_UCSZ0  1                     //Character Size Bit 0
#define         UCSRC_UCPOL  0                     //Clock Polarity

#define         UBRRH       *(volatile u8*)(0x40)
#define         UBRRH_URSEL  7

#define         UBRRL       *(volatile u8*)(0x29) //BaudRate left

#define         UDR         *(volatile u8*)(0x2C) //Data Regiser


#endif