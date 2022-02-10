/*************************************************************************/
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         4 JAN, 2021                                       */
/* !Version  :         v1.0                                              */
/*************************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_config.h"

void MTWI_voidMasterInit(u8 Copy_u8SlaveAddress)
{
	/*Enable Acknowledge*/
	SET_BIT(TWCR, TWCR_TWEA);

	/*Set SCL Frequency = 100KHz, CPU Clk = 8MHz, TWPS = 0*/
	TWBR = 32;
	/*Clear The Prescaler Bit (TWPS0, TWPS1)*/
	CLEAR_BIT(TWSR, TWSR_TWPS0);
	CLEAR_BIT(TWSR, TWSR_TWPS1);
	/*Check if the master node will be addressed or not*/
	if(Copy_u8SlaveAddress == 0)
	{
		/*Do Nothing*/
	}
	else
	{
		TWAR = Copy_u8SlaveAddress << 1;
	}
	/*Enable TWI*/
	SET_BIT(TWCR, TWCR_TWEN);
}

void MTWI_voidSlaveInit(u8 Copy_u8SlaveAddress)
{
	/*Enable Acknowledge*/
	SET_BIT(TWCR, TWCR_TWEA);

	/*Set The Slave Address*/
	TWAR = Copy_u8SlaveAddress << 1;
	
	/*Enable TWI*/
	SET_BIT(TWCR, TWCR_TWEN);
}

TWI_ErrorStatus_t MTWI_ErrorStatusSendStartCondition(void)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;
	/*Set The Start Condition Bit*/
	SET_BIT(TWCR, TWCR_TWSTA);
	/*Clear The Flag*/
	SET_BIT(TWCR, TWCR_TWINT);
	/*Polling (Busy Wait) until the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0);
	/*Check if the Start Condition is Transmitted*/
	if((TWSR & STATUS_CODE_MASK) != START_ACK)
	{
		Local_ErrorStatus = StartConditionError;
	}
	return Local_ErrorStatus;
}

TWI_ErrorStatus_t MTWI_ErrorStatusSendRepeatedStartCondition(void)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;
	/*Set The Start Condition Bit*/
	SET_BIT(TWCR, TWCR_TWSTA);
	/*Clear The Flag*/
	SET_BIT(TWCR, TWCR_TWINT);
	/*Polling (Busy Wait) until the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0);
	/*Check if the Start Condition is Transmitted*/
	if((TWSR & STATUS_CODE_MASK) != REP_START_ACK)
	{
		Local_ErrorStatus = RepeatedStartConditionError;
	}
	return Local_ErrorStatus;
}

TWI_ErrorStatus_t MTWI_ErrorStatusSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;
	/*Load The Slave Address To The TWDR Register*/
	TWDR = Copy_u8SlaveAddress << 1;
	/*Clear The Bit 0 For The Write Request*/
	CLEAR_BIT(TWDR, TWDR_TWD0);
	/*Clear The Start Condition Bit*/
	CLEAR_BIT(TWCR, TWCR_TWSTA);
	/*Clear The Flag*/
	SET_BIT(TWCR, TWCR_TWINT);
	/*Polling (Busy Wait) until the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0);
	/*Check if the Start Condition is Transmitted*/
	if((TWSR & STATUS_CODE_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_ErrorStatus = SlaveAddressWithWriteError;
	}
	return Local_ErrorStatus;
}



TWI_ErrorStatus_t MTWI_ErrorStatusSendSlaveAddressWithRead(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;
	/*Load The Slave Address To The TWDR Register*/
	TWDR = Copy_u8SlaveAddress << 1;
	/*Set The Bit 0 For The Read Request*/
	SET_BIT(TWDR, TWDR_TWD0);
	/*Clear The Start Condition Bit*/
	CLEAR_BIT(TWCR, TWCR_TWSTA);
	/*Clear The Flag*/
	SET_BIT(TWCR, TWCR_TWINT);
	/*Polling (Busy Wait) until the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0);
	/*Check if the Start Condition is Transmitted*/
	if((TWSR & STATUS_CODE_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_ErrorStatus = SlaveAddressWithReadError;
	}
	return Local_ErrorStatus;
}

TWI_ErrorStatus_t MTWI_ErrorStatusMasterWriteDataByte(u8 Copy_u8Data)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;
	/*Load The Data Into The TWDR Register*/
	TWDR = Copy_u8Data;
	/*Clear The Flag*/
	SET_BIT(TWCR, TWCR_TWINT);
	/*Polling (Busy Wait) until the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0);
	/*Check if the Start Condition is Transmitted*/
	if((TWSR & STATUS_CODE_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_ErrorStatus = MasterWriteByteError;
	}
	return Local_ErrorStatus;
}

TWI_ErrorStatus_t MTWI_ErrorStatusMasterReadDataByte(u8 * Copy_pu8ReceivedData)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;
	/*Clear The Flag, To Make The Slave Send Its Data*/
	SET_BIT(TWCR, TWCR_TWINT);
	/*Polling (Busy Wait) until the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0);
	/*Check if the Start Condition is Transmitted*/
	if((TWSR & STATUS_CODE_MASK) != MSTR_RD_BYTE_WITH_ACK)
	{
		Local_ErrorStatus = MasterReadByteError;
	}
	else
	{
		/*Get The Received Data*/
		*Copy_pu8ReceivedData = TWDR;
	}
	return Local_ErrorStatus;
}


void MTWI_voidSendStopCondition(void)
{
	/*Set The STOP CONDITION Bit*/
	SET_BIT(TWCR, TWCR_TWSTO);
	/*Clear The Flag, To Make The Slave Send Its Data*/
	SET_BIT(TWCR, TWCR_TWINT);
}
