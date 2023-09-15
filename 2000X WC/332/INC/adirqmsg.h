/* $Header:   L:/pvcs/1000/psos332/archives/inc/ADIRQMSG.H_v   2.1   01 Aug 1996 14:52:20   BKYMER  $ */
#ifndef ASCII_DIAG_REQ_SESSION_MSG_H
#define ASCII_DIAG_REQ_SESSION_MSG_H
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

   Filename:     adirqmsg.h


            Written by: Mark Lazarewicz 
                  Date: 03/22/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            03/23/96      Mark L      Initial
 
 ------------------------------- DESCRIPTION -----------------------------------

 Used to request an ASCII Diagnostic session


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

typedef struct
   {
   COMMON_MSG_FIELD_TYPE             common;
   UINT32                            resp_qid;         /* QID to send responses to  */
   CIB_INTERFACE_TYPE_TYPE           comm_port;        /* Comm port designator      */
   UINT8                             spare[7];         /* Not used                  */
   } ASCII_DIAG_REQ_SESSION_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* ASCII_DIAG_REQ_SESSION_MSG_H */


