/* $Header:   L:/pvcs/1000/psos332/archives/inc/ERR_MSG.H_v   2.1   01 Aug 1996 14:49:42   BKYMER  $ */
#ifndef MANAGE_ERRORS_MSG_H
#define MANAGE_ERRORS_MSG_H
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

   Module name:  n/a

   Filename:  err_msg.h


            Written by: Mark Lazarewicz 
                  Date: 2/6/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            02/06/96      Mark L      Initial version

 ------------------------------- DESCRIPTION -----------------------------------

   This message is sent to the ALRM (Alarm Manager) queue whenever an error or alarm is 
   detected.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "commnmsg.h"        /* type used in all message queue types  */
#include "managerr.h"	       /* contains the definitions of the elements in the msg: MANAGE_ERRORS_MSG */
/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef struct
   {                   
   COMMON_MSG_FIELD_TYPE  common;	/* 4 bytes */
   ERROR_KIND_TYPE	  error_kind;	/* 1 byte */
   ERROR_CODE_TYPE	  error_code;	/* 2 byte */
   ERROR_CALLER_TYPE	  error_caller;	/* 2 bytes or UINT16 */
   ERROR_REQUEST_TYPE	  error_request; /* 1 byte */
   UINT16		  line_number;
   UINT16		  spare_1;
   UINT16		  spare_2;
   } MANAGE_ERRORS_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* MANAGE_ERRORS_MSG_H */
