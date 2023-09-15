/* $Header:   D:/SWLab/VMdb/2000Series/App/VFSCRN.C_V   1.6   04 Sep 2008 20:16:40   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1997                 */
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

   Filename: vfscrn.c


 --------------------------------- REVISIONS --------------------------------

 Rev # Date     Author Description
 ===== ======== ====== ======================================================
 1.0   08/14/98  BJB   Original Version
 1.1   08/21/98  BJB   Added VFConvertLineToItem()
                       VFSetCurrentItems() doesn't clear the screen
                       Added code to manage up/down LEDs
 1.2   09/02/98  BJB   Added functions to save & restore up/down LED states.
 1.3   08/16/00  AT    VFWriteLine accepts strings shorter than 20 characters, blank-pads them
 1.4   08/16/00  AT    VFWriteLine now works for 20-char strings without zero terminator 
 1.5   10-22-07  NHAhmed  Changes done for LangTest phase 0
 1.6   09-04-08  Ygupta   CleanUp for LangTest Project.


*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/


/*------------------------------- LOCAL DEFINES ----------------------------*/

/*------------------------------- GLOBAL DATA ------------------------------*/
/*                       (scope is global to ALL files)                     */


/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

/* Define storage for menu text.  Add +1 to # of items to make room for */
/* title, +1 to LINESIZE to make room for terminator. */


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/


/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/


/*
 ---------------------------------- CODE -------------------------------------
*/



