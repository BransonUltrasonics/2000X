/* $Header:   L:/pvcs/1000/psos332/archives/inc/COMSHORT.H_v   2.2   01 Aug 1996 14:48:36   BKYMER  $ */
#ifndef COMM_STR_SHORT_MSG_H
#define COMM_STR_SHORT_MSG_H
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

   Module name: n/a

   Filename:    comm_str_short_msg.h

            Written by:  
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 
 ------------------------------- DESCRIPTION -----------------------------------

   For comm port string messages that are less than 10 characters in length,
   this message format will be used.


 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "commnmsg.h"
#include "cibinfo.h"
#include "comdrctn.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/

#define COMM_STR_SHORT_LENGTH 10
#define SERIAL_STR_SHORT_LENGTH 12

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef struct
   {
   COMMON_MSG_FIELD_TYPE     common;
   CIB_INTERFACE_TYPE_TYPE   comm_port;
   COMM_DIRECTION_TYPE       direction;
   SINT8                     string[COMM_STR_SHORT_LENGTH];
   } COMM_STR_SHORT_MSG;

typedef struct 
   { 
   COMMON_MSG_FIELD_TYPE  common;
   SINT8                  string[SERIAL_STR_SHORT_LENGTH];
   } SERIAL_STR_SHORT_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* COMM_STR_SHORT_MSG_H */
