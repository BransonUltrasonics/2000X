/* $Header:   L:/pvcs/1000/psos332/archives/inc/PASSWORD.H_v   2.1   01 Aug 1996 14:50:26   BKYMER  $ */
#ifndef COMM_PASSWORD_H
#define COMM_PASSWORD_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Comm Shell

   Filename:    comm_password.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

 This header contains  the interface needed by comm_password.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "vrifypwd.h"                 /* contains function interface          */
#include "parametr.h"               /* interface to parameter manager       */
#include "timrname.h"                 /* Defines timers                       */
#include "cibinfo.h"
#include "shelstat.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/


/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

SHELL_STATUS_TYPE comm_password(
    UINT32                              protocol_mngr_qid,          /* Protocol Manager QID       */
    CIB_INTERFACE_TYPE_TYPE             comm_port,                  /* CIB port designation       */
    UINT32                              shell_qid,                  /* Shell Queue ID             */
    PARAMETER_ID_TYPE                   timer_param_id,             /* Parameter ID for timer     */
    TIMER_NAME_TYPE                     timer_name );               /* Timer designator           */


#endif /* COMM_PASSWORD_H */
