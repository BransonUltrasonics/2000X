/* $Header:   L:/pvcs/1000/psos332/archives/inc/OUTBOUND.H_v   2.1   01 Aug 1996 14:51:26   BKYMER  $ */
#ifndef COMM_OUTBOUND_MSG_ROUTER_H
#define COMM_OUTBOUND_MSG_ROUTER_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Comm_Outbound_Msg_Router

   Filename: outbound.h 

 
 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by comm_outbound_msg_router.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

void CommOutboundMsgRouter(
   void
   );

void InitializeComr(
   void
   );

#endif /* COMM_OUTBOUND_MSG_ROUTER_H */
