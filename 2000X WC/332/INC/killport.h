/* $Header:   L:/pvcs/1000/psos332/archives/inc/KILLPORT.H_v   2.1   01 Aug 1996 14:52:42   BKYMER  $ */
#ifndef PORT_DISCONNECT_MSG_H
#define PORT_DISCONNECT_MSG_H
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

   Module name:  n/a

   Filename:     port_disconnect_msg.h


            Written by:  
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
  ------------------------------- DESCRIPTION -----------------------------------

 Used by a protocol to disconnect from a port.


 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "commnmsg.h"
#include "cibinfo.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef packed enum
   {
   PORT_DISCONNECT_REASON_BUSY     = 0,
   PORT_DISCONNECT_REASON_FINISHED = 1,
   PORT_DISCONNECT_REASON_SIZER    = 255u
   } PORT_DISCONNECT_REASON_TYPE;


typedef struct
   {
   COMMON_MSG_FIELD_TYPE             common;
   PORT_DISCONNECT_REASON_TYPE       reason;
   CIB_INTERFACE_TYPE_TYPE           comm_port;
   UINT8                             spare[10];
   } PORT_DISCONNECT_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* PORT_DISCONNECT_MSG_H */


