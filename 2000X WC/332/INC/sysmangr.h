/* $Header:   D:/SWLab/VMdb/2000Series/INC/SYSMANGR.H_V   2.6   Jan 11 2008 19:27:20   nhahmed  $ */
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

   Module name:  

   Filename:      sysmangr.h


            Written by: Mark Lazarewicz  
                  Date: 1/24/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0           01/23/96       Mark L      Initial Version
      1.2.4       06/17/97       PhilJ       Deleted UpdateCurrentSetup prototype
      1.2.5       12/02/97       PaulG       Added prototype CheckHistoryPtrBound().
      1.3         01/11/08       NHAhmed     Changed BackupCurrentSetupChange() prototype.

 ------------------------------- DESCRIPTION -----------------------------------


 Intertask message with front panel display information

 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "param.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           


/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void SystemManager(void);
void BackupCurrentSetupChange(void);
void CheckHistoryPtrBound(void);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

