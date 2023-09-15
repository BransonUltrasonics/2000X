/* $Header:   L:/pvcs/1000/psos332/archives/inc/WELDTASK.H_v   2.1   01 Aug 1996 14:48:14   BKYMER  $ */
#ifndef START_WELDER_H 
#define START_WELDER_H
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
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name: Start_Welder

   Filename:    WELDER.h


            Written by:Mark Lazarewicz  
                  Date: 1/24/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
       0            1/24/96      Mark L       Initial Release
  
 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "run_task.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/

 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/     

CREATE_AND_START_TASK_STATUS_TYPE  StartWelder(void);  

#endif /* end of #ifndef START_WELDER_H */  
