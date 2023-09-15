/* $Header:   L:/pvcs/1000/psos332/archives/inc/CMD_LINE.H_v   2.1   01 Aug 1996 14:47:50   BKYMER  $ */
#ifndef COMMAND_LINE_HANDLER_H
#define COMMAND_LINE_HANDLER_H
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

   Module name: 

   Filename:    command_line.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========



 ------------------------------- DESCRIPTION -----------------------------------

 This header contains  the interface needed by command_line_handler.c

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "portable.h"             /* normal file-includes                 */
#include "cibinfo.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/


/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/
void command_line_handler(
   SINT8                               *string_ptr,                /* Pointer to received string  */
   UINT32                              shell_qid,                  /* Shell Queue ID              */
   UINT32                              protocol_mngr_qid,          /* Protocol Manager QID        */
   CIB_INTERFACE_TYPE_TYPE             comm_port);                 /* CIB port designation        */

#endif
