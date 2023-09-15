/* $Header:   L:/pvcs/1000/psos332/archives/inc/TICKLDOG.H_v   2.1   01 Aug 1996 14:52:00   BKYMER  $ */
#ifndef WD_TICKLE_H
#define WD_TICKLE_H
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

   Module name: Watchdog

   Filename:  wd_tickle.h


            Written by: Mark Lazarewicz
                  Date: 1/21/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

   Contains function prototype information for watchdog task and
   initialization routine.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/
                  
void wd_tickle(
   void
   );

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* WD_TICKLE_H */
