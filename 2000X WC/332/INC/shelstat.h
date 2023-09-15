/* $Header:   L:/pvcs/1000/psos332/archives/inc/SHELSTAT.H_v   2.1   01 Aug 1996 14:49:00   BKYMER  $ */
#ifndef SHELL_STATUS_TYPE_H
#define SHELL_STATUS_TYPE_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Nucleus Shell

   Filename:    shell_status_type.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========


 ------------------------------- DESCRIPTION -----------------------------------

 This header contains the legal status values that may be returned
 by Nucleus Shell functions. Not all functions will be capable of
 returning all values.

 ------------------------------ INCLUDE FILES ----------------------------------
*/



/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
typedef packed enum
   {
   REMAIN_IN_STATE         = 0,
   SHELL_UAR_RECEIVED      = 1,
   SHELL_PROTOCOL_SELECTED = 2,
   SHELL_PASSWORD_VERIFIED = 3,
   SESSION_TERMINATE       = 4,
   SHELL_RETURN_TO_IDLE    = 5,
   SHELL_STATUS_SIZER      = 255u
   } SHELL_STATUS_TYPE;


/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/


#endif






