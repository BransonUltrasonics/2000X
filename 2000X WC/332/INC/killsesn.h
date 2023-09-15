/* $Header:   L:/pvcs/1000/psos332/archives/inc/KILLSESN.H_v   2.1   01 Aug 1996 14:52:44   BKYMER  $ */
#ifndef SESSION_TERMINATE_COMMAND_MSG_H
#define SESSION_TERMINATE_COMMAND_MSG_H
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

   Filename:    session_terminate_command_msg.h 


            Written by:  
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
 
 ------------------------------- DESCRIPTION -----------------------------------

 Defines message sent to force termination of a session

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
      } SESSION_TERMINATE_COMMAND_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* SESSION_TERMINATE_COMMAND_MSG_H */
