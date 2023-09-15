/* $Header:   L:/pvcs/1000/psos332/archives/inc/RESETMSG.H_v   2.1   01 Aug 1996 14:50:56   BKYMER  $ */
#ifndef RESET_MSG_H
#define RESET_MSG_H
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

   Module name:  

   Filename:     resetmsg.h


            Written by: Mark Lazarewicz 
                  Date: 2/7/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

   This file defines the RESET message that is sent to the watchdog to force
   a hardware reset.

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
   COMMON_MSG_FIELD_TYPE common;
   UINT32                spare_1;
   UINT32                spare_2;
   UINT32                spare_3;
   } RESET_MSG;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* RESET_MSG_H */
