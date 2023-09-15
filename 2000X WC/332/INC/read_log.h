/* $Header:   L:/pvcs/1000/psos332/archives/inc/READ_LOG.H_v   2.1   01 Aug 1996 14:50:54   BKYMER  $ */

#ifndef READ_LOG_MSG_H
#define READ_LOG_MSG_H
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

   Filename:  read_log_msg.h


            Written by: Mark Lazarewicz 
                  Date: 2/5/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
 ------------------------------- DESCRIPTION -----------------------------------

   This message is sent to the DIAG (Diagnostics Manager) queue to read the logs.
   This message includes the following ips_command_ids: READ_SWARE_LOG,

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

typedef UINT8 NUMBER_OF_ENTRIES_TYPE;

typedef struct
   {                   
   COMMON_MSG_FIELD_TYPE  common;	                /* 4 bytes */
   UINT32	                cib_partition_id;       /* 4 bytes */
   UINT32	                *cib_info;              /* 4 byte  */
   UINT16	                ips_command_id;         /* 2 bytes */
   NUMBER_OF_ENTRIES_TYPE number_of_entries;      /* 1 byte  */
   UINT8		                spare_1;                /* 1 byte  */
   } READ_LOG_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* READ_LOG_MSG_H */
