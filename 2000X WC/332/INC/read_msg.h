/* $Header:   L:/pvcs/1000/psos332/archives/inc/read_msg.h_v   2.3   28 Apr 1997 08:23:12   lmarkure  $ */
#ifndef ASCII_DATA_RESPONSE_MSG_H
#define ASCII_DATA_RESPONSE_MSG_H
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

   Filename:  read_msg.h


            Written by: Mark Lazarewicz
                  Date: 2/6/96 
              Language:  "C"

-------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            02/06/96      Mark L      Initial Version
       1            04/28/97      LAM         cleanup            

------------------------------- DESCRIPTION -----------------------------------
                                        
   

------------------------------ INCLUDE FILES ----------------------------------
*/

#include "ipsatype.h"         /* contains the definition of IPS_MESSAGE_TYPE */
#include "ipscdmsg.h"         /* contains the definition of IPS_MESSAGE_TYPE */
#include "commnmsg.h"         /* type used in all message queue types  */
#include "swaredat.h"


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
   SWARE_LOG_DATABASE_TYPE           *sware_log_info_ptr; /* 4 bytes */
   SWARE_LOG_BYTE_COUNT_TYPE         byte_count;          /* 2 bytes: number of bytes in response */
   UINT16                            ips_command_id;      /* 2 bytes */
   } READ_SWARE_LOG_RESPONSE_MSG;




  
/*
----------------------------FUNCTION PROTOTYPES ---------------------------------
*/

/*
----------------------------EXTERNAL PROTOTYPES ---------------------------------
*/

#endif /* ASCII_DATA_RESPONSE_MSG */
