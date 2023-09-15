/* $Header:   L:/pvcs/1000/psos332/archives/inc/TIMR_MSG.H_v   2.1   01 Aug 1996 14:52:10   BKYMER  $ */
#ifndef TIMER_EXPIRED_MSG_H
#define TIMER_EXPIRED_MSG_H 1
       
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name: TIMER_EXPIRED_MSG

   Filename: timr_msg.h 

            Written by: Mark Lazarewicz 
                  Date: 02/03/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author           Description
   ==========      ========      ===========      ==============

 ------------------------------- DESCRIPTION -----------------------------------


*/

/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"
#include "timrname.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

                                                                               

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/    
       
typedef TIMER_NAME_TYPE  TIMER_EXPIRED_STATE_TYPE;  

typedef struct
        {
          COMMON_MSG_FIELD_TYPE    common;
          TIMER_EXPIRED_STATE_TYPE state;
          UINT32                   spare_1;
          UINT32                   spare_2;
        } TIMER_EXPIRED_MSG;

#endif /* TIMER_EXPIRED_MSG_H */
