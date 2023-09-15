/* $Header:   L:/pvcs/1000/psos332/archives/inc/CLRALARM.H_v   2.1   01 Aug 1996 14:47:48   BKYMER  $ */
#ifndef CLEAR_ALARMS_MSG_H
#define CLEAR_ALARMS_MSG_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: clear_alarms_msg

   Filename: clralarm.h

             Written by: Mark Lazarewicz
                  Date:  03/30/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            03/30/96      Mark Lazarewicz Initial release 

 ------------------------------- DESCRIPTION -----------------------------------

   This message is sent to the DIAG (Diagnostics Manager) queue to clear alarms.
   This message includes the following ips_command_ids: CLEAR_SINCLE_ACTUAL_ALARMS,
   CLEAR_ALL_ACTUAL_ALARMS, CLEAR_SINGLE_LATCHED_ALARM, CLEAR_ALL_LATCHED_ALARMS.
   Note that the error_code is only checked for clearing single alarms.
 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"        /* type used in all message queue types  */
#include "managerr.h"	       /* contains the definitions for msg: MANAGE_ERRORS_MSG */
#include "ipscdmsg.h"        /* contains the definition of IPS_MESSAGE_TYPE */
#include "ipsatype.h"        /* contains the definition of IPS_ACTION_ID_TYPE */

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef struct
   {                   
   COMMON_MSG_FIELD_TYPE  common;	          /* 4 bytes */
   UINT32	                cib_partition_id; /* 4 bytes */
   IPS_MESSAGE_TYPE	      *cib_info;        /* 4 byte */
   IPS_ACTION_ID_TYPE	    ips_command_id;   /* 2 bytes */
   ERROR_CODE_TYPE	       error_code;       /* 2 byte */
   } CLEAR_ALARMS_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* CLEAR_ALARMS_MSG_H */
