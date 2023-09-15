/* $Header:   L:/pvcs/1000/psos332/archives/app/menupass.h_v   1.3   17 Oct 1997 10:02:24   bbarrows  $ */
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

   Filename: menu2.h

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #     Date            Author     Description
   ==========     ========        ======     ===========
      0                                      Initial Version
      1.10        07/31/97        PJ         Added prototype TryAgain
      1.2         08/06/97         ?
      1.3         10/16/97        BJB        Deleted defs of SendSelect1Key(),
                                              StartOverFunction(), TryAgain().

*/

/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void ClearPasswordFlag(void);
void SetPasswordFlag(void);
void AssignPasswordName(void);
