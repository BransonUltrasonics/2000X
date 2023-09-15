/* $Header:   L:/pvcs/1000/psos332/archives/inc/ASCRNMSG.H_v   2.1   01 Aug 1996 14:52:34   BKYMER  $ */
#ifndef DISPLAY_ASCII_SCREEN_MSG_H
#define DISPLAY_ASCII_SCREEN_MSG_H 1
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

   Module name: display_ascii_screen_msg

   Filename:    ascrnmsg.h

            Written by:  Mark Lazarewicz
                  Date:  03/24/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            03/24/96      Mark L      Initial

 ------------------------------- DESCRIPTION -----------------------------------

   This message contains a string of ASCII characters that is sent from ADIM to the 
   Front panel serial port or the AIPS port.  This message is 10 characters or greater in 
   length.  It, like other "data pointer"-type messages, contains a partition-ID, a 
   byte count, and a pointer to the string of data.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "commnmsg.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/

#define MAX_ASCII_BUFFER_SIZE   1500 /* 1.5 KB ascii buffer size */


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/* Number of bytes to access    */
typedef UINT16  ASCII_DATA_BYTE_COUNT_TYPE;

/* Defines vt100 Ascii screen display */
typedef char EXTERNAL_ASCII_DISPLAY_TYPE[MAX_ASCII_BUFFER_SIZE];

typedef struct
   {
   COMMON_MSG_FIELD_TYPE          common;                      /* 32 bits */
   EXTERNAL_ASCII_DISPLAY_TYPE    *ext_ascii_display_str_ptr;  /* 32 bits */
   ASCII_DATA_BYTE_COUNT_TYPE     byte_count;                  /* 16 bits */
   UINT32                         partition_id;                /* 32 bits */
   UINT16		          spare_1;                     /* 16 bits */
   } DISPLAY_ASCII_SCREEN_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* DISPLAY_ASCII_SCREEN_MSG_H */
