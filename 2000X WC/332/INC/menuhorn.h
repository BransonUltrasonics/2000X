/* $Header:   L:/pvcs/1000/psos332/archives/inc/menuhorn.h_v   2.6   24 Apr 1998 14:54:24   bbarrows  $ */
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
      1           4/29\96         PJ         First release
      2           4/30/96         LAM        Deleted strm6_2
      2.2        10/29/97         BJB        Added definition of new function,
                                              DoHornDown().
                                             Added include of portable.h.
                                             Deleted strings at end.
      2.3        10/30/97         BJB        Added comment end to prevent
                                              compiler "informational".
      2.4        11/04/97         BJB        Updated prototype of DoHornDown().
      2.5        04/22/98         BJB        Added def of HornDownFlag.
      2.6        04/22/98         BJB        Added def of HornDownISR().

*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include "portable.h"

/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

BOOLEAN DoHornDown( UINT8 *ExitKey, BOOLEAN *DidHD );
void HornDownISR(void);

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/


/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/


/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/



/*
 ---------------------------------- CODE -------------------------------------
*/


/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

extern BOOLEAN HornDownFlag;     /* When TRUE disables state machine */
