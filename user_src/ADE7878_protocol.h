

#ifndef __ADE7878_protocol_H
#define __ADE7878_protocol_H

#include "r_cg_macrodriver.h"


#define RESTART_COUNT (0x03U)


//static const uint8_t tx_data[DATA_LENGTH];	                /* Transmission data( 16 byte ) */
//static uint8_t rx_data[DATA_LENGTH];
// static uint8_t com_direction;
static uint8_t restart_counter;			                /* Restart counter */

void PM_select(uint8_t pManMode);

//void Data_write(uint8_t size_message);

//void Data_read(uint8_t size_message);

uint8_t Read_ADE78xx_I2C(uint8_t SL_Addr, uint8_t *pRegAdress, uint8_t *pRegData, uint8_t nrAdressBytes, uint8_t nrDataBytes);
void Transmit_Data_I2C(uint8_t addressSlave, uint8_t *pData, uint8_t Nr_Bytes, uint8_t direction);

#endif
