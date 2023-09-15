/* $Header:   L:/pvcs/1000/psos332/archives/inc/INITCOPY.H_v   2.3   01 May 1998 15:53:12   bbarrows  $ */
#ifndef INITCOPY_H
#define INITCOPY_H
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

   Filename:  initcopy.h


            Written by: Mark Lazarewicz
                  Date: 02/15/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
         0          02/15/96      Mark L      initial version
         2.3        05/01/98      BJB         Added prototypes for C++ support
                                               functions RunConstructors(),
                                               RunDestructors().

 ------------------------------- DESCRIPTION -----------------------------------

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

void InitCopy(void);
void RunConstructors(void);
void RunDestructors(void);

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* INITCOPY_H */
