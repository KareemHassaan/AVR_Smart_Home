/***********************************************************************/
/*  !Author     :       Ahmed Emad                			           */
/*  !Date       :       24 JAN, 2022                                    */
/*  !LAYER      :       HAL                                           */
/*  !Version    :       v1.0                                           */
/***********************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../../MCAL/DIO/DIO_interface.h"

#include "STEPPER_interace.h"
#include "STEPPER_private.h"
#include "STEPPER_config.h"

#ifndef 	F_CPU
#define 	F_CPU 	8000000UL
#endif
#include <util/delay.h>

void HSTEPPER_voidRotate(u8 Copy_u8Direction, u16 Copy_u16Angle)
{
	u16 Local_u16Steps  = 0;

	u16 Local_u16Iterations = 0;

	u16 Local_u16LoopCounter = 0;

	Local_u16Steps = (Copy_u16Angle * STEPS_NUMBER)/ 360UL;

	Local_u16Iterations = Local_u16Steps / 4;

	switch(Copy_u8Direction)
	{	
		case CLK_WISE:
			HSTEPPER_VoidStopMotor();

			for(Local_u16LoopCounter = 0; Local_u16LoopCounter < Local_u16Iterations; Local_u16LoopCounter++)
			{
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN0, LOW);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN1, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN2, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN3, HIGH);
				_delay_ms(10);

				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN0, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN1, LOW);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN2, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN3, HIGH);
				_delay_ms(10);

				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN0, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN1, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN2, LOW);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN3, HIGH);
				_delay_ms(10);

				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN0, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN1, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN2, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN3, LOW);
				_delay_ms(10);
			}
		break;

		case COUNTER_CLK_WISE:
			HSTEPPER_VoidStopMotor();

			for(Local_u16LoopCounter = 0; Local_u16LoopCounter < Local_u16Iterations; Local_u16LoopCounter++)
			{
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN0, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN1, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN2, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN3, LOW);
				_delay_ms(10);

				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN0, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN1, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN2, LOW);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN3, HIGH);
				_delay_ms(10);

				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN0, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN1, LOW);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN2, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN3, HIGH);
				_delay_ms(10);

				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN0, LOW);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN1, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN2, HIGH);
				MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN3, HIGH);
				_delay_ms(10);
			}
		break;
	}
}

void HSTEPPER_VoidStopMotor()
{
	/*Deactivate All coils to stop the motor*/
	MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN0, HIGH);
	MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN1, HIGH);
	MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN2, HIGH);
	MDIO_voidSetPinValue(STEPPER_PORT, STEPPER_PIN3, HIGH);
}
