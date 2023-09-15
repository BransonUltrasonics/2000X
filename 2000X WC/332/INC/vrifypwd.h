/* $Header:   L:/pvcs/1000/psos332/archives/inc/VRIFYPWD.H_v   2.1   01 Aug 1996 14:48:06   BKYMER  $ */
#ifndef VERIFY_PASSWORD_H
#define VERIFY_PASSWORD_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Comm

   Filename:    verify_password.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========


 ------------------------------- DESCRIPTION -----------------------------------

 This header contains the interface needed by verify_password.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef enum
   {
   WAITING_FOR_PASSWORD,
   PASSWORD_VALID,
   PASSWORD_INVALID
   } VERIFY_PASSWORD_STATUS_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

VERIFY_PASSWORD_STATUS_TYPE verify_password(UINT8 * password_ptr );


#endif /* VERIFY_PASSWORD_H */
