/***********************************************************************/
/*  !Author     :       Ahmed Gamal			                           */
/*  !Date       :       3 JAN, 2022                                    */
/*  !LAYER      :       MCAL                                           */
/*  !Version    :       v1.0                                           */
/***********************************************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"
/*
	MSB First
	Leading = Rising
	Setup @ Leading
	Prescaler = 16
*/
static void (*Global_pvCallBack)(void) = NULL;
u8 MSPI_u8ReceivedData = 0;

void MSPI_voidMasterInit(void)
{
	/*Set The Node To Be Master*/
	SET_BIT(SPCR, SPCR_MSTR);
	/*Set MSB First*/
	CLEAR_BIT(SPCR, SPCR_DORD);
	/*Set Clock Polarity , Leading = Rising Edge*/
	CLEAR_BIT(SPCR, SPCR_CPOL);
	/*Set The Clock Phase, Setup (Write) At Leading Edge*/
	SET_BIT(SPCR, SPCR_CPHA);
	/*Set Prescaler To Be = 16*/
	SET_BIT(SPCR, SPCR_SPR0);
	CLEAR_BIT(SPCR, SPCR_SPR1);
	CLEAR_BIT(SPSR, SPSR_SPI2X);
	/*Enable SPI*/
	SET_BIT(SPCR, SPCR_SPE);
}

void MSPI_voidSlaveInit(void)
{
	/*Set The Node To Be Slave*/
	CLEAR_BIT(SPCR, SPCR_MSTR);
	/*Set MSB First*/
	CLEAR_BIT(SPCR, SPCR_DORD);
	/*Set Clock Polarity , Leading = Rising Edge*/
	CLEAR_BIT(SPCR, SPCR_CPOL);
	/*Set The Clock Phase, Setup (Write) At Leading Edge*/
	SET_BIT(SPCR, SPCR_CPHA);
	/*Enable SPI*/
	SET_BIT(SPCR, SPCR_SPE);
	SET_BIT(SPCR, SPCR_SPIE);
}


void MSPI_voidTranceiveDataAsync(u8 Copy_u8Data)
{
	/*Set Data In The Data Register SPDR*/
	SPDR = Copy_u8Data;
	/*Enable Interrupt*/
	SET_BIT(SPCR, SPCR_SPIE);
}


void CallBackFunction(void *(Copy_Function(void)))
{
	Global_pvCallBack = Copy_Function ;
}

//ISR For Transfer Complete
void __vector_12 (void) __attribute__((signal));
void __vector_12 (void)
{
	//Get The Received Data
	MSPI_u8ReceivedData = SPDR;
	if(Global_pvCallBack != NULL)
	{
		Global_pvCallBack();
	}
	//Disable Interrupt
	CLEAR_BIT(SPCR, SPCR_SPIE);
}





