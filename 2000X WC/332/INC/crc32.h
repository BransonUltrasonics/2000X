/* $Header:   L:/pvcs/1000/psos332/archives/inc/CRC32.H_v   2.1   01 Aug 1996 14:48:40   BKYMER  $ */
#ifndef CRC32_GENERATOR_H
#define CRC32_GENERATOR_H
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

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Crc32_Generator

   Filename: crc32_generator.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 

  ------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by crc32_generator.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include  "portable.h"           /*   general hardware defines...   */

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 * This value is used when starting a CRC calculation.
 * The crc_initial_value can be used to continue a previous CRC calculation
 */
#define CRC32_INITIAL_VALUE   0


#define CRC32_TABLE_SIZE    256

/* the following macro can be used to calculate crc on a byte at a time. 
 * provide the crc table is initialized first.
 */
#define CRC32(data, crc) (crc32_table[(crc^data) & 0xff] ^ ((crc >> 8) & 0x0ffffff))

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef UINT32 CRC32_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

CRC32_TYPE crc32_generator( UINT8 data, CRC32_TYPE crc);

void crc32_table_generator(CRC32_TYPE crc32_table[]);


#endif /* CRC32_GENERATOR_H */
