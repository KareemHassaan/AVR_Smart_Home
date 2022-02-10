/********************************************************************************/
/*   !Author      :         Mostafa Mohamed Anwar                               */
/*   !Date        :         03 JAN, 2022                                        */
/*   !LAYER       :         MCAL                                                */
/*   !Version     :         v1.0                                                */
/********************************************************************************/

#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H


void MSPI_voidMasterInit(void);
void MSPI_voidSlaveInit(void);
void MSPI_uint8AsyncTranceiveData(uint8 Copy_uint8Data);
void MSPI_voidSetCallBack(void (*Copy_pvNotificationFunction)(void));



#endif
