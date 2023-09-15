/* $Header:   L:/pvcs/1000/psos332/archives/inc/USRPWORD.H_v   2.2   01 Aug 1996 14:47:58   BKYMER  $ */
#ifndef USER_PASSWORD_TYPE_H
#define USER_PASSWORD_TYPE_H

/*
 ---------------------------- INCLUDE DESCRIPTION --------------------------

   Module name: N/A

   Filename:    user_password_type.h 


 -------------------------------- REVISIONS ---------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
         1          07/04/96      LAM         cleanup warnings
 ------------------------------- DESCRIPTION --------------------------------

 This header contains the definition of the USER_PASSWORD parameter

 ------------------------------ INCLUDE FILES -------------------------------
*/

/*
 --------------------------------- DEFINES ----------------------------------
*/
#define USER_PASSWORD_LEN       5


/*
 ---------------------------- TYPE DECLARATIONS -----------------------------
*/

typedef UINT8 USER_PASSWORD_TYPE[ USER_PASSWORD_LEN ];

/*
 --------------------------- FUNCTION PROTOTYPES --------------------------
*/


#endif /* USER_PASSWORD_TYPE_H */
