/* $Header:   L:/pvcs/1000/psos332/archives/app/comm_crc.c_v   2.4   08 Sep 1997 11:33:42   lmarkure  $ */
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
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  Comm_Crc_Generator

   Filename:  comm_crc.c

   Function name:  comm_crc_generator


  -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author          Description
   ==========      ========      ======          ===========
      0             1/31/96      Mark Lazarewicz Initial Version
      1             6/18/96      LAM             Clean Up        
      2.3           9/08/97      LAM             Clean Up        

 ------------------------------- DESCRIPTION -----------------------------------
 
   This module will calculate the CRC of the given data using CCITT CRC-16. The
   crc_table needs to be previously initialized in order for this routine to
   work correctly.

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"     /* normal file-includes                  */
#include "comm_crc.h"      /* contains function interface           */

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/
                                   
#define CRC_TABLE_SIZE 256

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/

static COMM_CRC_TYPE crc_table[CRC_TABLE_SIZE];

/*
 ------------------------------- GLOBAL DATA -----------------------------------
                        (scope is global to ALL files)
*/

/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
                        (scope is global to THIS file)
*/
                              
/*
 ---------------------------------- CODE ---------------------------------------
*/

COMM_CRC_TYPE CommCrcGenerator(
   UINT8         crc_data_pointer[],
   COMM_CRC_TYPE  crc_initial_value,
   UINT16         crc_byte_count
   ) 
   {
   COMM_CRC_TYPE crc_result;
   UINT16 byte_index;

   /* Initially set CRC to requested initial value */
   crc_result = crc_initial_value;

   /*
    * For each byte as indicated by crc_data_pointer and crc_byte count
    * make a table reference for that byte by exclusive-oring the current byte
    * at crc_data_pointer with the low byte of the running CRC (crc_result)
    * and exclusive-oring that with the high byte of the running CRC.
    */
   for (byte_index = 0; byte_index < crc_byte_count; byte_index++)
      {
      crc_result = (crc_result >> 8)
                   ^ crc_table[crc_data_pointer[byte_index]
                              ^ (crc_result & 0xff)];
      }

   return (crc_result);  /* new CRC */
   }


/*   This routine initializes the tables for CCITT CRC-16 calculations. */

void CommCrcGeneratorInit(void){

   UINT16        table_index;
   UINT8         working_variable;

   for ( table_index = 0; table_index < CRC_TABLE_SIZE; table_index++ ){
      working_variable = table_index ^ (table_index << 4);
      crc_table[table_index] = ( (working_variable << 8)
                               ^ (working_variable << 3)
                               ^ (working_variable >> 4) );
   }

}

/* For Unit testing of this routine */
#ifdef INCLUDE_UNIT_TEST
#include "comm_crc.ut"
#endif
