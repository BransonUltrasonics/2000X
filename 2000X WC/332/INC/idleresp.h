/* $Header:   L:/pvcs/1000/psos332/archives/inc/IDLERESP.H_v   2.1   01 Aug 1996 14:51:32   BKYMER  $ */
#ifndef SESSION_IDLE_RESP_MSG_H
#define SESSION_IDLE_RESP_MSG_H
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

   Module name: session_idle_resp_msg

   Filename: idleresp.h 


            Written by: Mark Lazarewicz 
                  Date: 03/12/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
        0           03/12/96      Mark L      Initial 

 ------------------------------- DESCRIPTION -----------------------------------

 Defines message sent to indiacte that a session has terminated

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "commnmsg.h"

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
      char                      unused[11];
      } SESSION_IDLE_RESP_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* SESSION_IDLE_RESP_MSG_H */
