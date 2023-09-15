/* $Header:   K:\APPS\PVCS Pro\332\INC\MEMAP.H_V   2.5   Apr 19 1999 16:10:06   ofingere  $ */
#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
*---------------------------- INCLUDE DESCRIPTION ------------------------------
*
*                                                                        *
*-------------------------------- REVISIONS -----------------------------------
*
*   Rev #      Date      Author             Description
*   =====    ========    ======             ===========
*    0       12/23/95    Mark Lazarewicz    Initial
*    2.4     08.12.97    JBerman            Correcting the comments of the 
*                                           8255 definitions
*    2.5  	 04/19/99	 OFI				Changed for DIAB
*------------------------------------------------------------------------------*/

/*-------------------------------- OVERVIEW ------------------------------------
*
*-------------------------------- INCLUDES ------------------------------------
*
*   NONE
*
*------------------------------- DEFINITIONS ----------------------------------
*/

#include "portable.h"
#include "inputs.h"
#include "332.h"




#define SPI_DATA_REGISTER                0x00FF9000
#define SPI_CONTROL_REGISTER             0x00FF9080

/* 8255 Parrallel ports */

/* Actuators      */
#define CONTROL_INPUT_PORT_0             0x00150000  /* Port A U79 */
#define CONTROL_INPUT_PORT_1             0x00150002  /* Port C U79 */

/* Alarms */
#define CONTROL_INPUT_PORT_2             0x00160001  /* Port B U67 */

#define CONTROL_OUTPUT_PORT_0            0x00160000  /* Port A U67 */
#define CONTROL_OUTPUT_PORT_1            0x00150001  /* Port B U79 */
#define CONTROL_OUTPUT_PORT_2            0x00160002  /* Port C U67 */
#define CONTROL_OUTPUT_PORT_3            0x00FF9680

#define Actuator_Control_Port            0x00150003
#define Alarm_Control_Port               0x00160003

#define ACTUATOR_8255_CONTROL_WORD       0x99
#define ALARM_8255_CONTROL_WORD          0x82




                                 
 /*
  * The following defines or references the welders input ports.
  * The address for this port is defined in the file memap.h
  */
                                                                                       
#if defined(ALLOCATE)
      UINT8  *Input8255CntrolPtr1             = (UINT8 *) Actuator_Control_Port; 
      UINT8  *Input8255CntrolPtr2             = (UINT8 *) Alarm_Control_Port; 
      /* This is the global definition */
      INPUT_PORT_P0_UNION_TYPE *InputPort0Ptr = (INPUT_PORT_P0_UNION_TYPE *)CONTROL_INPUT_PORT_0;
      INPUT_PORT_P1_UNION_TYPE *InputPort1Ptr = (INPUT_PORT_P1_UNION_TYPE *)CONTROL_INPUT_PORT_1;
      UINT8  *InputPort2Ptr                   = (UINT8 *)CONTROL_INPUT_PORT_2;
       struct MMap *SimMap                    = (struct MMap *) (0xFFFA00);

#else                                 
      /* This is the global reference */
      extern INPUT_PORT_P0_UNION_TYPE *InputPort0Ptr;
      extern INPUT_PORT_P1_UNION_TYPE *InputPort1Ptr;
      extern INPUT_PORT_P2_UNION_TYPE *InputPort2Ptr;
      extern UINT8  *Input8255CntrolPtr1;
      extern UINT8  *Input8255CntrolPtr2;
      extern struct MMap *SimMap;  
#endif




#define DRAM_START                       0x100000
#define DRAM_SIZE                        0x03FFFF
#define DRAM_END                         0x13FFFF

/* Flash defines */

/* Location of flash banks */
#define FLASH_BASE_ADDRESS               0x000000
//#define FLASH_DORMANT_BASE               0x100000
#define FLASH_SIZE                       0x07FFFF
#define FLASH_TOP_ADDRESS                (FLASH_BASE_ADDRESS + FLASH_SIZE)

/* Used by boot_flash_verify.c to set up which flash bank is active */
#define CHIP_SELECT_1_BASE_A_ACT         0xf00000
#define CHIP_SELECT_1_BASE_B_ACT         0x200000
#define CHIP_SELECT_0_SIZE_A_ACT         0x0600
#define CHIP_SELECT_0_SIZE_B_ACT         0x0700


#endif
