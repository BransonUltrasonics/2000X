/* $Header:   L:/pvcs/1000/psos332/archives/inc/CLEARMSG.H_v   2.1   01 Aug 1996 14:47:44   BKYMER  $ */


#ifndef CLEAR_LOG_MSG_H
#define CLEAR_LOG_MSG_H
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

   Filename:  clearmsg.h

            Written by: Mark Lazarewicz
                  Date: 02/08/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 

 ------------------------------- DESCRIPTION -----------------------------------

   This message is sent to the DIAG (Diagnostics Manager) queue to read the logs.
   This message includes the following ips_command_ids: CLEAR_SWARE_LOG,
   CLEAR_ERROR_LOG, CLEAR_EVENT_LOG.
 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"        /* type used in all message queue types  */
#include "managerr.h"	     /* contains the definitions for msg: MANAGE_ERRORS_MSG */

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef struct
   {                   
   COMMON_MSG_FIELD_TYPE  common;	          /* 4 bytes */
   UINT32	          cib_partition_id;       /* 4 bytes */
   UINT32	          *cib_info;              /* 4 bytes */
   UINT16	          ips_command_id;         /* 2 bytes */
   UINT16	          spare_1;                /* 2 bytes */
   }CLEAR_LOG_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* CLEAR_LOG_MSG_H */
