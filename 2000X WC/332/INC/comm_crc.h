/* $Header:   L:/pvcs/1000/psos332/archives/inc/COMM_CRC.H_v   2.1   01 Aug 1996 14:48:28   BKYMER  $ */
#ifndef COMM_CRC_GENERATOR_H
#define COMM_CRC_GENERATOR_H
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
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Comm_Crc_Generator

   Filename: comm_crc.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0             1/26/96      Mark L      Initial Version

 ------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by comm_crc_generator.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include  "portable.h"      /*   general hardware defines...   */

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 * This value is used when starting a CRC calculation.
 * The crc_initial_value can be used to continue a previous CRC calculation
 */
#define CRC_INITIAL_VALUE   0

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef UINT16 COMM_CRC_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

COMM_CRC_TYPE CommCrcGenerator(
   UINT8          crc_data_pointer[],
   COMM_CRC_TYPE  crc_initial_value,
   UINT16         crc_byte_count
   ); 


void CommCrcGeneratorInit(
   void
   );

#endif /* COMM_CRC_GENERATOR_H */
