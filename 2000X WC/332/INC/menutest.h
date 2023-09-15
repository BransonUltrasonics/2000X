/* $Header:   K:/APPS/PVCS Pro/332new/INC/MENUTEST.H_V   2.4   Aug 16 2000 08:00:40   atali  $ */
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
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menuhorn.h

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #     Date            Author     Description
   ==========     ========        ======     ===========
      0                                      Initial Version
      2.3         11/04/97        BJB        Added Branson header.
                                             Added prototype of DoTestMode().
      2.4         08-15-00        AT         Moved UpdateDiagScreen to menutest.[ch]
*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include "portable.h"

/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

BOOLEAN DoTestMode( UINT8 *ExitKey, BOOLEAN *DidTest );
void UpdateTestAmp(void);
void UpdateDiagScreen(void);
void InitTestBuffers(void);
