/******************************************************************
 *  AUTHOR : Ahmed Gamal                                          *
 *  Date   : 5 Jan. 2022                                          *
 *  Layer  : HAL                                                  *
 *  Version: v1.0                                                 *
 * ***************************************************************/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/TWI/TWI_interface.h"

#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"
#include <util/delay.h>
/* 
Read Sequance from E^2PROM ( u 16 Location )
    1-Send Start Condition
    2-Send Slave Address + Write signal (send command to EEPROM)
        0b 1010  A2A1 A0 + 0 
        fixed            Write
    3-Send rest of Byte Address
    4-Send Repeated start condition 
    5-Send Slave Address + Read signal 
        0b 1010 A2A1A0 + 1  (READ REQUEST)
    6-Read Data received 
    7-Send Stop condition
*/
void HEEPROM_voidWriteData(u16 Copy_u16Location, u8 Copy_u8Data)
{
	u8 Local_u8AddressPacket = 0;
	if(Copy_u16Location <= 1023)
	{
		Local_u8AddressPacket =	 EEPROM_FIXED_ADDRESS | (A2_CONNECTION << 2) | (u8)(Copy_u16Location >> 8);
		/*2K
			Local_u8AddressPacket =	 EEPROM_FIXED_ADDRESS | (A2_CONNECTION << 2) |
			(A1_CONNECTION << 1) | (A0_CONNECTION);
		*/

		/*Send Start Condition*/
		MTWI_ErrorStatusSendStartCondition();
		/*Send Slave Address With Write Request*/
		MTWI_ErrorStatusSendSlaveAddressWithWrite(Local_u8AddressPacket);
		/*Send The Rest Of Byte Address*/
		MTWI_ErrorStatusMasterWriteDataByte((u8)Copy_u16Location);
		/*Send The Data Byte*/
		MTWI_ErrorStatusMasterWriteDataByte(Copy_u8Data);
		/*Send Stop Condition*/
		MTWI_voidSendStopCondition();
		_delay_ms(10);
	}

}

void HEEPROM_voidReadData(u16 Copy_u16Location, u8 * Copy_pu8ReceivedData)
{
	u8 Local_u8AddressPacket = 0;
	if(Copy_u16Location <= 1023)
	{

		Local_u8AddressPacket =	 EEPROM_FIXED_ADDRESS | (A2_CONNECTION << 2) | (u8)(Copy_u16Location >> 8);
		/*2K
			Local_u8AddressPacket =	 EEPROM_FIXED_ADDRESS | (A2_CONNECTION << 2) |
			(A1_CONNECTION << 1) | (A0_CONNECTION);
		*/

		/*Send Start Condition*/
		MTWI_ErrorStatusSendStartCondition();
		/*Send Slave Address With Write Request*/
		MTWI_ErrorStatusSendSlaveAddressWithWrite(Local_u8AddressPacket);
		/*Send The Rest Of Byte Address*/
		MTWI_ErrorStatusMasterWriteDataByte((u8)Copy_u16Location);
		/*Send Repeated Start Condition*/
		MTWI_ErrorStatusSendRepeatedStartCondition();
		/*Send The Slave Address With Read Request*/
		MTWI_ErrorStatusSendSlaveAddressWithRead(Local_u8AddressPacket);
		/*Get The Data From The Memory*/
		MTWI_ErrorStatusMasterReadDataByte(Copy_pu8ReceivedData);
		/*Send Stop Condition*/
		MTWI_voidSendStopCondition();
	}
}
