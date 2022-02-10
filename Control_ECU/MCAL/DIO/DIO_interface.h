 /* HEADER GUARD FILE */
#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/****** PORTS DEFINATION ****/
#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
/****** PIN DEFINATION ****/
#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7
/****** Direction DEFINATION ****/
#define INPUT	0
#define OUTPUT	1
/****** OUTPUT DEFINATION ****/
#define LOW 0 
#define HIGH 1
/****** INPUT DEFINATION ****/
#define NO_PULL_UP 0 
#define PULL_UP 1




/* SETTING PORTS FUNCTIONS PROTOTYPES */
void MDIO_voidSetPinDirection(u8 Copy_u8PortName , u8 Copy_u8PinNumber , u8 Copy_u8PinDirection ) ;
void MDIO_voidSetPinValue(u8 Copy_u8PortName , u8 Copy_u8PinNumber , u8 Copy_u8PinValue );
void MDIO_voidSetPort(u8 Copy_u8PortName , u8 Copy_u8PinDirection) ;
void MDIO_voidSetSpecificPortOutPut(u8 Copy_u8PortName , u8 Copy_u8Value) ;
/* READING FROM INPUT FUNCTIONS PROTOTYPES */
u8 MDIO_u8GetPinValue(u8 Copy_u8PortName , u8 Copy_u8PinNumber ) ;
u8 MDIO_u8GetPortValue(u8 Copy_u8PortName ) ;




#endif
