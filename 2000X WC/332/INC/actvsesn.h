/* $Header:   L:/pvcs/1000/psos332/archives/inc/ACTVSESN.H_v   2.1   01 Aug 1996 14:51:50   BKYMER  $ */
#ifndef SESSION_ACTIVE_RESP_MSG_H
#define SESSION_ACTIVE_RESP_MSG_H
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

   Module name: n/a

   Filename:    actvsesn.h 

   Function:    session_active_resp_msg.h 


            Written by: Mark Lazarewicz 
                  Date: 03/06/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            03/06/96      Mark L      Initial Version


 ------------------------------- DESCRIPTION -----------------------------------

 Defines message sent to indiacte that a session has terminated

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"
#include "cibinfo.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
   
typedef struct
      {     
      COMMON_MSG_FIELD_TYPE     common;       /* 32 -bits */
      CIB_INTERFACE_TYPE_TYPE   comm_port;    /* 8-bits   */
      CIB_PROTOCOL_TYPE_TYPE    protocol;     /* 8-bits   */
      char                      unused[10];
      } SESSION_ACTIVE_RESP_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* SESSION_ACTIVE_RESP_MSG_H */
