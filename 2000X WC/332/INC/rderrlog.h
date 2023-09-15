/* $Header:   L:/pvcs/1000/psos332/archives/inc/RDERRLOG.H_v   2.1   01 Aug 1996 14:50:52   BKYMER  $ */
#ifndef READ_ERROR_LOG_RESPONSE_MSG_H
#define READ_ERROR_LOG_RESPONSE_MSG_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: read_error_log_response_msg  

   Filename:  rderrlog.h


            Written by: Mark Lazarewicz
                  Date: 03/10/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            03/10/96      Mark L      Initial

 ------------------------------- DESCRIPTION -----------------------------------

   This message is a response to a read error log and is sent to the RSCH 
   (Remote Serial Command Handler) queue.
   

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"        /* type used in all message queue types  */
#include "alarmsdb.h"        /* contains the definitions for alarm_database_return_data*/
#include "ipsatype.h"
#include "ipscdmsg.h"        /* contains the definition of IPS_MESSAGE_TYPE */
#include "err_data.h"
/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

 


typedef struct
   {                   
   COMMON_MSG_FIELD_TYPE             common;              /* 4 bytes */
   IPS_MESSAGE_TYPE	                 *cib_info;           /* 4 bytes */
   ERROR_LOG_DATABASE_TYPE           *error_log_info_ptr; /* 4 bytes */
   ERROR_LOG_BYTE_COUNT_TYPE         byte_count;          /* 2 bytes:number of bytes in response */
   IPS_ACTION_ID_TYPE                ips_command_id;      /* 2 bytes */
   } READ_ERROR_LOG_RESPONSE_MSG;




  
/*
----------------------------FUNCTION PROTOTYPES ---------------------------------
*/

/*
----------------------------EXTERNAL PROTOTYPES ---------------------------------
*/

#endif /* READ_ALL_ALARMS_RESPONSE_MSG */
