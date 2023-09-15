/* $Header:   L:/pvcs/1000/psos332/archives/inc/COMMLONG.H_v   2.2   01 Aug 1996 14:48:24   BKYMER  $ */
#ifndef COMM_STR_LONG_MSG_H
#define COMM_STR_LONG_MSG_H
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

   Module name: comm_str_long_msg

   Filename:    commlong.h


            Written by: Mark Lazarewicz 
                  Date: 02/08/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 

 ------------------------------- DESCRIPTION -----------------------------------

   For comm port string messages that are 10 characters or greater in length,
   this message format will be used.  It, like other "data pointer"-type
   messages, contains a partition-ID, a byte count, and a pointer to the
   string of data.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "commnmsg.h"
#include "cibinfo.h"
#include "comdrctn.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef struct
   {
   COMMON_MSG_FIELD_TYPE     common;
   CIB_INTERFACE_TYPE_TYPE   comm_port;
   COMM_DIRECTION_TYPE       direction;
   SINT8                     *string_ptr;
   UINT32                    partition_id;
   UINT16                    byte_count;
   } COMM_STR_LONG_MSG;


typedef struct
   {
   COMMON_MSG_FIELD_TYPE  common;
   UINT32                 partition_id;
   UINT16                 spare;
   UINT16                 byte_count;
   void                  *string;
   } SERIAL_STR_LONG_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* COMM_STR_LONG_MSG_H */











