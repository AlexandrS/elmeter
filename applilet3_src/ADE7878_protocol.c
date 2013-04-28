/*******************************************************************************
  -this file contains functions that implement the communication protocol
    between the ADC and R5F102A
*******************************************************************************/

/*******************************************************************************
  -PM_select commands a new PSMx mode to ADE78xx, then sends back 'R',0x7E
  -P0.6 manages PM0
  -P0.7 manages PM1

*******************************************************************************/

#include "ADE7878_protocol.h"
#include "r_cg_port.h"
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"

uint8_t com_status;						/* Communication state */
								/* 0 : Idle (Tx/Rx is normal end.) */
								/* 1 : Communicating, */
								/* 2 : Tx/Rx is abnormal end. */
void PM_select(uint8_t pManMode) {

  switch (pManMode) {
    case 0:
      //order PSM0: PM0 - P22(P2.2)=1, PM1 - P23(P2.3)=0
      P2 = _04_Pn2_OUTPUT_1 | _00_Pn3_OUTPUT_0;
      break;
    case 1:
      //order PSM1: PM0 - P22(P2.2)=0, PM1 - P23(P2.3)=0
      P2 = _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0;
      break;
    case 2:
      //order PSM2: PM0 - P22(P2.2)=0, PM1 - P23(P2.3)=1
      P2 = _00_Pn2_OUTPUT_0 | _08_Pn3_OUTPUT_1;
      break;
    case 3:
      //order PSM3: PM0 - P22(P2.2)=1, PM1 - P23(P2.3)=1
      P2 = _04_Pn2_OUTPUT_1 | _08_Pn3_OUTPUT_1;
  }
  return;
}

uint8_t Read_ADE78xx_I2C(uint8_t SL_Addr, uint8_t *pRegAdress, uint8_t *pRegData, uint8_t nrAdressBytes, uint8_t nrDataBytes) {
  
  if(STCEN0!=1)					/* Case of bus non-liberating. */
    {
      R_IICA0_StopCondition();		        /* Generate stop condition. */
		
      /* Detection waiting of stop condition. */
      while(!SPD0)
	{
          NOP();
	}
     }
  /*Send address of read register of ADE7878*/
  Transmit_Data_I2C(SL_Addr, pRegAdress, nrAdressBytes, 1);
  /*Receive data from ADE7878*/
  Transmit_Data_I2C(SL_Addr, pRegData, nrDataBytes, 0);  
  
  return 0;
}

uint8_t Write_ADE78xx_I2C(uint8_t SL_Addr, uint8_t *pRegAdress, uint8_t *pRegData, uint8_t nrAdressBytes, uint8_t nrDataBytes) {

  int i=0;
  
  uint8_t i2cMessage[LENGHT_MESSAGE];
  
  if(STCEN0!=1)					/* Case of bus non-liberating. */
    {
      R_IICA0_StopCondition();		        /* Generate stop condition. */
		
      /* Detection waiting of stop condition. */
      while(!SPD0)
	{
          NOP();
	}
     }
  
  for (i=0;i<nrAdressBytes+nrDataBytes;i++) {
    if (i<nrAdressBytes) {
      i2cMessage[i] = pRegAdress[i];
    }
    else {
      i2cMessage[i] = pRegData[i-nrAdressBytes];
    }
  }
  
  /*Send address of read register of ADE7878*/
  Transmit_Data_I2C(SL_Addr, i2cMessage, nrAdressBytes+nrDataBytes, 1);  
  
  return 0;
}

void Transmit_Data_I2C(uint8_t addressSlave, uint8_t *pData, uint8_t Nr_Bytes, uint8_t direction) {
  
  uint8_t loop_counter;				/* Loop counter */
  MD_STATUS iic_status;				/* IIC status */
          
  /************************************/
  /* Prepare Communication            */
  /************************************/
 
  restart_counter = RESTART_COUNT;	                /* Setting of retry counter. */
  IICAIF0 = 0;					        /* Clear IICA interrupt request. */
  com_status = 1;					/* Setting communication flag. */

  /* It repeats until one communication is completed. */
  while( com_status )
    {
      /* Direction : transmission. */
      if (direction) {
        /* Send data. */
        iic_status = R_IICA0_Master_Send(
          addressSlave,		/* Slave address. */
          pData,		/* Transfer buffer pointer. */
          Nr_Bytes,		/* Buffer size. */
          20);			/* Wait for start condition. */
      }
      else {
        /* Receive data. */
        iic_status = R_IICA0_Master_Receive(
          addressSlave,		/* Slave address. */
          pData,		/* Transfer buffer pointer. */
          Nr_Bytes,		/* Buffer size. */
          20);			/* Wait for start condition. */
      }
      
      while( com_status == 1 )	/* Communicating. */
          {
            HALT();			/* HALT mode until Tx completed. */
          }
        
      if( com_status == 2 )		/* Incomplete communication. */
	{
          R_IICA0_StopCondition();	/* Generate stop condition. */
          /* Detection waiting of stop condition. */
          while(!SPD0)
            {
              NOP();
            }
          if(restart_counter)		/* Retry is incomplete. */
            {
              restart_counter -= 1;	/* Count retry times. */
              com_status = 1;		/* Continue communication. */

              /* Wait about 10us and restart. */
              for( loop_counter = 0; loop_counter < 35; loop_counter++ )
                {
                  NOP();
		}
            }
          else				/* Retry is complete. */
            {
              com_status = 0;		/* Communication is end. */
            }
	}
    }  
}
