/* $Header:   L:/pvcs/1000/psos332/archives/inc/UAR_MSG.H_v   2.1   01 Aug 1996 14:52:24   BKYMER  $ */
#ifndef UAR_MSG_H
#define UAR_MSG_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name:  n/a

   Filename:  uar_msg.h


            Written by: 
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
  ------------------------------- DESCRIPTION -----------------------------------

   

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"        /* type used in all message queue types  */

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

 


typedef struct
   {                   
   COMMON_MSG_FIELD_TYPE   common;          /* 4 bytes */
   UINT32                  partition_id;    /* 4 bytes- UAR buffer */
   UINT32                  *uar_ptr;         /* 4 bytes - UAR msg */
   UINT32                  spare_1; 
   } UAR_MSG;
  
/*
----------------------------FUNCTION PROTOTYPES ---------------------------------
*/

/*
----------------------------EXTERNAL PROTOTYPES ---------------------------------
*/

#endif /* UAR_MSG_H */


