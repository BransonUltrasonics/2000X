/* $Header:   L:/pvcs/1000/psos332/archives/inc/PROTOSEL.H_v   2.1   01 Aug 1996 14:50:40   BKYMER  $ */
#ifndef SHELL_PROTOCOL_SELECTION_H
#define SHELL_PROTOCOL_SELECTION_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Nucleus Shell

   Filename:    shell_protocol_selection.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========


 ------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by shell_protocol_selection.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "portable.h"                        /* normal file-includes                 */
#include "timrname.h"                 /* Defines timers                       */
#include "cibinfo.h"
#include "uar_msg.h"                         /* Defines structure of UAR message     */
#include "parametr.h"
#include "shelstat.h"               /* Shell function return values         */



/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/



/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/
SHELL_STATUS_TYPE shell_protocol_selection(
    CIB_PROTOCOL_TYPE_TYPE              *protocol_ptr,
    UINT32                              protocol_mngr_qid,          /* Protocol Manager QID       */
    CIB_INTERFACE_TYPE_TYPE             *session_port_ptr,          /* CIB port designation       */
    UINT32                              shell_qid,                  /* Shell Queue ID             */
    PARAMETER_ID_TYPE                   timer_param_id,             /* Parameter ID for timer     */
    TIMER_NAME_TYPE                     timer_name,                 /* Timer designator           */
    UAR_MSG                             *uar_msg_ptr );             /* Returns UAR message        */


#endif






