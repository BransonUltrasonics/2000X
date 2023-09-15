/* $Header:   D:/SWLab/VMdb/2000Series/App/SECURITY.C_V   1.29.1.2   04 Sep 2008 20:16:36   ygupta  $ */
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

   Filename: security.c

   Function name:                


 --------------------------------- REVISIONS --------------------------------

 Rev # Date     Author Description
 ===== ======== ====== ======================================================
 1.00  10/18/96 PhilJ  Initial Version
 1.10  10/19/96 PhilJ  Added Password incorrect message
 1.20  10/21/96 PhilJ  Added global password.
 1.30  07/31/97 PhilJ  Added test if MainKey or GoBackKey is pressed.
 1.40  08/06/97 PhilJ  Added another check if MainKey or GoBackKey is pressed
 1.50  09/11/97 PaulG  Unit test and data cleanup.
 1.6   10-16-97 BJB    No ref of PasswordEnableFlag.
                       No ref of IncorrectPasswordMenu[].
                       Deleted flag PasswordAttempt.
                       Rewrote CheckSecurity().
 1.7   10-21-97 BJB    Includes "beep.h", "security.h"
                       Adds new global "AccessLevel"
                       Added function SecurityChecked()
 1.8   10-29-97 BJB    Added test for invalid type and rational reaction in
                        SecurityChecked().
 1.9   11-4-97  BJB    Doesn't use MainKeyFlag.
                       MainKey can't be used to exit password entry screen.
                       Doesn't send fake "NOKEY" before displaying menus.
 1.10  11-6-97  BJB    Will report that password entry is wrong if user enters
                        nothing.
                       Changed appearance of "Password Incorrect" screen to
                        match new spec.
 1.11  11-11-97 BJB    Added response to ResetKey from WaitKeyPress().
 1.12  01-05-98 BJB    Clears screen after displaying "Password Accepted".
 1.13  04-06-98 BJB    Calls WaitMessage() instead of tm_wkafter().
 1.14  04-30-98 BJB    Item EnterPassword moved from MENUPASS.C.
                       Uses new AlphaEntry() function.
 1.15  09-03-98 BJB    Some code to react to ResetKey removed, will be
                        executed inside DisplayResetMsg().
 1.15.6.1 02-08-00 JZ  removed DVS, added Mask1, Cond1, Mask2, Cond2
 1.15.6.2 02-23-00 JZ  removed 'User experience level' from menu strucutures
 1.16     04-06-00 JZ  merged Lang to trunk
 1.17     05-26-00 SCM  Checked in for testing by Laura, John.
 1.18     06-28-00 BEKymer  Changed all MODEL to LEVEL
 1.19     07-13-00 BEK/DJL  fixed tabs 
 1.20     08-18-00 LAM      use correct "continue" string 
 1.21     09-10-03 JOY      Added 'CheckForAccessDenied()'.
 1.22     09-27-03 JOY      Restricted Maintainance password to six chars.
 1.23     10-16-03 JOY      MiddleSeg. Erased by QVGA ROM image.
 1.24     03-09-04 VSharma  Modified 'DisplayLockFlag' as a member of struct INBITS.
 1.25     03-28-04 LAM      changed ts password from ZA#### to ZA....
 1.26     07-25-05 Bwadia   VGA check access function added for security check
 1.27     11-22-05 Bwadia   ZA.... password entry for VGA added
 1.28     01-06-06 LAM      merged BBRaun special
 1.29     01-20-06 Bwadia   VGACheckAccess() modified for Override password to work.
                            Modified for tracker issue 4056
 1.30     10-22-07 NHAhmed  Changes done for LangTest phase 0
 1.31     09-02-08 NHAhmed  CleanUp for multi-language support.
 1.32     09-04-08 YGupta   CleanUp for LangTest Project.

 ------------------------------- DESCRIPTION ---------------------------------
*/
 
   /* This file will deal with the menus for all password interaction. */

/*                                   
 ------------------------------ INCLUDE FILES --------------------------------
*/


/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/


/*
 --------------------------- EXTERNAL FUNCTION PROTOTYPES -----------------------
*/

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

/*
 ---------------------------------- CODE -------------------------------------
*/





/***************************************************************************/
/*==============================END========================================*/
/***************************************************************************/
