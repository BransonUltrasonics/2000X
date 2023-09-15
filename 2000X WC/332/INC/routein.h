/* $Header:   L:/pvcs/1000/psos332/archives/inc/ROUTEIN.H_v   2.1   01 Aug 1996 14:51:00   BKYMER  $ */
#ifndef COMM_INBOUND_MSG_ROUTER_H
#define COMM_INBOUND_MSG_ROUTER_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Comm_Inbound_Msg_Router

   Filename: comm_inbound_msg_router.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by comm_inbound_msg_router.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "return.h"              /* use generic return status for this routine */
#include "ipscmdty.h"            /* for IPS_MESSAGE_TYPE */
#include "root.h"                /* for SYS_STARTUP_STATUS_TYPE */

/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef RETURN_STATUS_TYPE COMM_INBOUND_MSG_ROUTER_STATUS_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

COMM_INBOUND_MSG_ROUTER_STATUS_TYPE comm_inbound_msg_router(
   IPS_MESSAGE_TYPE  *ips_message_ptr
   );

SYS_STARTUP_STATUS_TYPE comm_inbound_msg_router_init(
   void
   );

#endif /* COMM_INBOUND_MSG_ROUTER_H */
