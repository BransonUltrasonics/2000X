/* $Header:   L:/pvcs/1000/psos332/archives/inc/INBOUND.H_v   2.2   01 Aug 1996 14:51:36   BKYMER  $ */
#ifndef COMM_INBOUND_MSG_ROUTER_H
#define COMM_INBOUND_MSG_ROUTER_H
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

   Module name: Comm_Inbound_Msg_Router

   Filename: inbound.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0             03/06/96      Mark L      Initial you know the routine

 ------------------------------- DESCRIPTION -----------------------------------

 This header contains all the information needed by comm_inbound_msg_router.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "return.h"       /* use generic return status for this routine */
#include "ipscdmsg.h"     /* for IPS_MESSAGE_TYPE */
#include "root.h"         /* for SYS_STARTUP_STATUS_TYPE */
/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef RETURN_STATUS_TYPE COMM_INBOUND_MSG_ROUTER_STATUS_TYPE;
#endif /* COMM_INBOUND_MSG_ROUTER_H */

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

COMM_INBOUND_MSG_ROUTER_STATUS_TYPE CommInboundMsgRouter(
   IPS_MESSAGE_TYPE  *ips_message_ptr
   );

SYS_STARTUP_STATUS_TYPE CommInboundMsgRouterInit(
   void
   );

