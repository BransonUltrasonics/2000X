/* $Header:   L:/pvcs/1000/psos332/archives/inc/CRC16GEN.H_v   2.1   01 Aug 1996 14:48:40   BKYMER  $ */
#ifndef CRC16_GENERATOR_H
#define CRC16_GENERATOR_H
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

   Module name: Crc16_Generator

   Filename: crc16_generator.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 

------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by crc16_generator.c

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

typedef UINT16 CRC16_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

CRC16_TYPE crc16_generator( UINT8 data, CRC16_TYPE crc);


#endif /* COMM_CRC_GENERATOR_H */
