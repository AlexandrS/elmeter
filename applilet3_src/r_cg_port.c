/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only 
* intended for use with Renesas products. No other uses are authorized. This 
* software is owned by Renesas Electronics Corporation and is protected under 
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING 
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT 
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE 
* AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR 
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE 
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software 
* and to discontinue the availability of this software.  By using this software, 
* you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_port.c
* Version      : Applilet3 for RL78/G12 V1.02.01 [11 Oct 2011]
* Device(s)    : R5F102AA
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for PORT module.
* Creation Date: 4/16/2013
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_PORT_Create
* Description  : This function initializes the Port I/O.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_PORT_Create(void)
{
    P0 = _01_Pn0_OUTPUT_1 | _02_Pn1_OUTPUT_1;
    P1 = _20_Pn5_OUTPUT_1;
    P2 = _04_Pn2_OUTPUT_1 | _08_Pn3_OUTPUT_1;
    P3 = _02_Pn1_OUTPUT_1;
    P14 = _80_Pn7_OUTPUT_1;
    PMC0 = _00_PMCn0_DI_ON | _00_PMCn1_DI_ON | _FC_PMC0_DEFAULT;
    PMC12 = _00_PMCn0_DI_ON | _FE_PMC12_DEFAULT;
    PMC14 = _00_PMCn7_DI_ON | _7F_PMC14_DEFAULT;
    ADPC = _01_ADPC_DI_ON;
    PM0 = _00_PMn0_MODE_OUTPUT | _00_PMn1_MODE_OUTPUT | _FC_PM0_DEFAULT;
    PM1 = _01_PMn0_NOT_USE | _02_PMn1_NOT_USE | _04_PMn2_NOT_USE | _08_PMn3_NOT_USE | _10_PMn4_NOT_USE |
          _00_PMn5_MODE_OUTPUT | _40_PMn6_NOT_USE | _80_PMn7_NOT_USE;
    PM2 = _01_PMn0_MODE_INPUT | _02_PMn1_MODE_INPUT | _00_PMn2_MODE_OUTPUT | _00_PMn3_MODE_OUTPUT | _F0_PM2_DEFAULT;
    PM3 = _01_PMn0_MODE_INPUT | _00_PMn1_MODE_OUTPUT | _FC_PM3_DEFAULT;
    PM5 = _01_PMn0_MODE_INPUT | _02_PMn1_MODE_INPUT | _FC_PM5_DEFAULT;
    PM12 = _01_PMn0_MODE_INPUT | _FE_PM12_DEFAULT;
    PM14 = _00_PMn7_MODE_OUTPUT | _7F_PM14_DEFAULT;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
