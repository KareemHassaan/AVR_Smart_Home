#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "HB_interface.h"
#include "HB_private.h"
#include "HB_config.h"


void HBRIDGE_voidInit(void)
{
	MDIO_voidSetPinDirection(HB_PORT, HB_PIN0, OUTPUT);
	MDIO_voidSetPinDirection(HB_PORT, HB_PIN1, OUTPUT);
}

void HBRIDGE_voidCW(void)
{
	MDIO_voidSetPinValue(HB_PORT, HB_PIN1, LOW);
	MDIO_voidSetPinValue(HB_PORT, HB_PIN0, HIGH);
}

void HBRIDGE_voidCCW(void)
{
	MDIO_voidSetPinValue(HB_PORT, HB_PIN0, LOW);
	MDIO_voidSetPinValue(HB_PORT, HB_PIN1, HIGH);
}

void HBRIDGE_voidOFF(void)
{
	MDIO_voidSetPinValue(HB_PORT, HB_PIN0, LOW);
	MDIO_voidSetPinValue(HB_PORT, HB_PIN1, LOW);
}
