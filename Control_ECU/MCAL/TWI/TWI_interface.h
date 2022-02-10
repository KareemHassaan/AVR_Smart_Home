/*************************************************************************/
/* !Layer    :         MCAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         4 JAN, 2021                                       */
/* !Version  :         v1.0                                              */
/*************************************************************************/
#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

typedef enum
{
	NoError,
	StartConditionError,
	RepeatedStartConditionError,
	SlaveAddressWithWriteError,
	SlaveAddressWithReadError,
	MasterWriteByteError,
	MasterReadByteError,

}TWI_ErrorStatus_t;


void 				MTWI_voidMasterInit(u8 Copy_u8SlaveAddress);
void 				MTWI_voidSlaveInit(u8 Copy_u8SlaveAddress);
TWI_ErrorStatus_t 	MTWI_ErrorStatusSendStartCondition(void);
TWI_ErrorStatus_t 	MTWI_ErrorStatusSendRepeatedStartCondition(void);
TWI_ErrorStatus_t 	MTWI_ErrorStatusSendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);
TWI_ErrorStatus_t 	MTWI_ErrorStatusSendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);
TWI_ErrorStatus_t MTWI_ErrorStatusMasterWriteDataByte(u8 Copy_u8Data);
TWI_ErrorStatus_t MTWI_ErrorStatusMasterReadDataByte(u8 * Copy_pu8ReceivedData) ;
void MTWI_voidSendStopCondition(void) ;



#endif
