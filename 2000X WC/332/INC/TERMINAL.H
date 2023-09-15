/* $Header:   L:/pvcs/1000/psos332/archives/app/TERMINAL.H_v   1.6   28 Aug 1998 13:06:30   bbarrows  $ */
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

   Filename: terminal.h


 --------------------------------- REVISIONS --------------------------------

 Rev # Date     Author Description
 ===== ======== ====== ===========
 1.0   12/29/97  BJB   Original Version
 1.1   01/05/97  BJB   Added prototype for TermInputBufferCleared().
 1.2   01/12/98  BJB   Added prototype for TermSyncMenus().
 1.3   01/26/98  BJB   Added prototype for GetTermScreenWindowPos().
 1.4   06/12/98  BJB   Added prototype for TermUpdateDataHeader().
 1.5   08/19/98  BJB   Contains prototypes for significantly revised new
                        TERMINAL.C 1.19.
 1.6   08/21/98  BJB   Added prototype for TermConvertLineToItem().

*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "weld_obj.h"

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/


/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

   
/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void TermInit(void);
void TermEnable(void);
void TermDisable(void);
void TermClearScreen(void);
void TermClearMenuText(void);

void TermSetCurrentItems( UINT16 Line1, UINT16 SelectKey1, UINT16 SingleSelect,
  UINT16 MenuItems );

void TermGetCurrentItems( UINT16 *Line1,UINT16 *SelectKey1,UINT16 *SingleSelect );
UINT16 TermConvertLineToItem( UINT16 Line );
void TermSetMenuText( SINT8 MenuText[], UINT16 Item );
BOOLEAN TermCheckMenuText( UINT16 Item );
void TermShowMenu( UINT16 StartItem, UINT16 EndItem );
UINT16 TermGetSelectedItem( UINT16 SelIndex );
UINT16 TermGetScreenSize(void);
void TermSetSelectedItem( UINT16 Item );
void TermMoveCursor(UINT16 LineNumb, UINT16 LinePos, UINT16 Cursor);
void TermWriteLine( SINT8 string[], UINT16 LineNumber );
BOOLEAN TermScrollUpPage(void);
BOOLEAN TermScrollDownPage( UINT16 MenuItems );
BOOLEAN TermScrollUpLine(void);
BOOLEAN TermScrollDownLine( UINT16 MenuItems );
void TermAlarmOn(void);
void TermAlarmOff(void);
void TermMessagesNotProcessed(void);
BOOLEAN TermIsEnabled(void);
void TermFillInSpecialChrs(SINT8 *string);
void TermUpdateDataHeader(void);
BOOLEAN InDataMode(void);
BOOLEAN IsTermDataAvailable(void);
void TermMsInt(void);
void TermShowAlarm(void);
void TermDataModeToggle( UINT16 MenuItems );
void TermOutputDataLine(void);
void TerminalInput( UINT8 InChr );
void ShowTermMenuItems( MENU itemlist[], UINT16 StartLine, UINT16 MenuLines );
void TermSaveWeldData(WELD_DATA *GetFinalResults);
