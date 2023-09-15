/* $Header:   L:/pvcs/1000/psos332/archives/inc/HEX2ASCI.H_v   2.1   01 Aug 1996 14:51:32   BKYMER  $ */
#ifndef CONVERT_HEX_TO_ASCII_H
#define CONVERT_HEX_TO_ASCII_H
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

   Module name:   convert_hex_to_ascii

   Filename:      hex2asci.h


            Written by: Mark Lazarewicz  
                  Date: 03/13/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            03/13/96      Mark L      Initial version

 ------------------------------- DESCRIPTION -----------------------------------

 Function prototype for utility that converts an array of bytes to Hex-ASCII

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "portable.h"            /* normal file-includes                 */



/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void ConvertHexToAscii(
   UINT8                               *string_ptr,                /* Put ASCII conversion here      */
   UINT16                              byte_count,                 /* Number of bytes to convert     */
   UINT8                               *hex_data_ptr );            /* Start of hex data              */


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  




