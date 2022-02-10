/********************************************************************************/
/*   !Author      :         Mostafa Mohamed Anwar                               */
/*   !Date        :         03 JAN, 2022                                        */
/*   !LAYER       :         MCAL                                                */
/*   !Version     :         v1.0                                                */
/********************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "SPI_intrface.h"
#include "SPI_private.h"
#include "SPI_config.h"

/* Global Pointer to the functio */
static void (*Global_pvCallBackFunction)(void) = NULL;

/* 
    Master:
            MSB First
            Leading = Rising
            Setup @ Leading
            Prescalar = 16 
*/
void MSPI_voidMasterInit(void)
{
    /* Set the Node to be master */
    SET_BIT(SPCR, SPCR_MSTR);
    /* SET MSB first */
    CLR_BIT(SPCR, SPCR_DORD);
    /* Set the Leading = Rising */
    CLR_BIT(SPCR, SPCR_CPOL);
    /* Set the clock phase setup at leading edge */
    SET_BIT(SPCR, SPCR_CPHA);
    /* Set the prescalar */
    SET_BIT(SPCR, SPCR_SPR0);
    CLR_BIT(SPCR, SPCR_SPR1);
    CLR_BIT(SPSR, SPSR_SPI2X);
    /* Enable SPI */
    SET_BIT(SPCR, SPCR_SPE);
}

void MSPI_voidSlaveInit(void)
{
    /* Set the Node to be SLAVE */
    CLR_BIT(SPCR, SPCR_MSTR);
    /* SET MSB first */
    CLR_BIT(SPCR, SPCR_DORD);
    /* Set the Leading = Rising */
    CLR_BIT(SPCR, SPCR_CPOL);
    /* Set the clock phase setup at leading edge */
    SET_BIT(SPCR, SPCR_CPHA);
    /* Enable SPI */
    SET_BIT(SPCR, SPCR_SPE);
}


void   MSPI_uint8AsyncTranceiveData(uint8 Copy_u8Data)
{
    /* Set Data in the DAta Register SPDR */
    SPDR = Copy_u8Data;
    /* Enable Interrupt */
    SET_BIT(SPCR, SPCR_SPIE);
}



void MSPI_voidSetCallBack(void (*Copy_pvNotificationFunction)(void))
{
    Global_pvCallBackFunction = Copy_pvNotificationFunction;
}
uint8 MSPI_uint8ReceivedData = 0;

/* ISR for Transfer Complete */
void __vector_12(void) __attribute__((signal));
void __vector_12(void)
{
    /* Get the Received Data */
	MSPI_uint8ReceivedData = SPDR;
    if(Global_pvCallBackFunction != NULL)
    {
        Global_pvCallBackFunction();
    }
    CLR_BIT(SPCR, SPCR_SPIE);
}
