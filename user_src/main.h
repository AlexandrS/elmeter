/*******************************************************************************

  -this file contains declarations used in main.c

*******************************************************************************/
#ifndef __main_H_
#define __main_H_

#define DATA_LENGTH (0x10U)
#define NR_REG_ADDRESS (0x02U)
#define NR_REG_DATA (0x04U)

uint8_t controlMode;
uint8_t pmMode;
static uint8_t registerAdress[DATA_LENGTH];
static uint8_t registerData[DATA_LENGTH];
uint8_t slAddress = 0x70;
uint8_t numRegAddress = 0x02;
uint8_t numRegData = 0x04;

#endif //__main_H