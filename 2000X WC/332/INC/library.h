/* $Header:   L:/pvcs/1000/psos332/archives/inc/LIBRARY.H_v   2.1   01 Aug 1996 14:49:10   BKYMER  $ */
#ifndef INIT_LIBRARY_ROUTINES_H
#define INIT_LIBRARY_ROUTINES_H
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

   Module name: Init_Library_Routines

   Filename:  library.h


            Written by: Mark Lazarewicz 
                  Date: 1/15/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========


 ------------------------------- DESCRIPTION -----------------------------------

   This header defines the function prototype for library initializer.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "root.h"              /* contains defines for startup initialization */

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

SYS_STARTUP_STATUS_TYPE InitLibraryRoutines(
   void
   );

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* INIT_LIBRARY_ROUTINES_H */
