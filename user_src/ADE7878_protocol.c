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

void PM_select(uint8_t pManMode) {

  switch (pManMode) {
    case 0:
      //order PSM0: P22(P2.2)=0, P23(P2.3)=1
      P2 = _00_Pn2_OUTPUT_0 | _08_Pn3_OUTPUT_1;
      break;
    case 1:
      //order PSM1: P22(P2.2)=0, P23(P2.3)=0
      P2 = _00_Pn2_OUTPUT_0 | _00_Pn3_OUTPUT_0;
      break;
    case 2:
      //order PSM2: P22(P2.2)=1, P23(P2.3)=0
      P2 = _04_Pn2_OUTPUT_1 | _00_Pn3_OUTPUT_0;
      break;
    case 3:
      //order PSM3: P22(P2.2)=1, P23(P2.3)=1
      P2 = _04_Pn2_OUTPUT_1 | _08_Pn3_OUTPUT_1;
  }
  return;
}