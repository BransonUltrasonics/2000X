/* $Header:   L:/pvcs/1000/psos332/archives/inc/MIN_MODE.H_v   2.1   01 Aug 1996 14:51:14   BKYMER  $ */
#ifndef START_MINIMAL_TASK_SET_H
#define START_MINIMAL_TASK_SET_H
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

   Module name: Start_Minimal_Task_Set
   Filename:    min_mode.h

   Function name: 


            Written by: Mark Lazarewicz 
                  Date: 1/16/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"            /* for BOOLEAN TYPE */
#include "root.h"                /* contains defines for startup initialization */

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

SYS_STARTUP_STATUS_TYPE StartMinimalTaskSet(
   void
   );
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif 
