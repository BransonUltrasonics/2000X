/* $Header:   L:/pvcs/1000/psos332/archives/inc/comasesn.h_v   2.4   30 Mar 1997 19:34:38   lmarkure  $ */
#ifndef COMM_ACTIVE_SESSION_H
#define COMM_ACTIVE_SESSION_H
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

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: comm_active_session

   Filename:    comasesn.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            03/06/96      Mark L      Initial
      2             3/30/97      LAM         welddata test


 ------------------------------- DESCRIPTION -----------------------------------

 This header contains  the interface needed by comm_active_session.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/

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
SHELL_STATUS_TYPE CommActiveSession(
    CIB_PROTOCOL_TYPE_TYPE              current_service,            /* Service or protocol        */
    UINT32                              protocol_mngr_qid,          /* Protocol Manager QID       */
    CIB_INTERFACE_TYPE_TYPE             comm_port,                  /* CIB port designation       */
    UINT32                              shell_qid,                  /* Shell Queue ID             */
    PARAMETER_ID_TYPE                   timer_param_id,             /* Parameter ID for timer     */
    TIMER_NAME_TYPE                     timer_name );               /* Timer designator           */



#endif /* COMM_ACTIVE_SESSION_H */
