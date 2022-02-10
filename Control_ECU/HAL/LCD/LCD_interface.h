#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H



/*Initialize LCD Put configurations ports and pins for output in config file*/
void HLCD_voidInit() ;

/*Sending Data in ASCII to print Function*/
void HLCD_voidSendData(u8 Copy_u8CData) ;
/*Sending Integer to print Function*/
void HLCD_voidSendNumber( u16 Copy_u16Number) ;
/*Sending String to Print Function*/
void HLCD_voidSendString(u8 *Pointer_u8String) ;

/*Cursor Go to (x,y)*/
void HLCD_voidGoToXY(u8 Copy_u8XPosition , u8 Copy_u8YPosition) ;


void HLCD_voidSendCustomePattern(u8 *Pointer_u8Pattern , u8 Copy_u8PatternNum , u8 Copy_u8XPosition , u8 Copy_u8YPosition );

void HLCD_voidClearAll() ;

#endif
