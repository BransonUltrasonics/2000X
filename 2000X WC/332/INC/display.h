/* $Header:   K:\APPS\PVCS Pro\332new\INC\DISPLAY.H_V   2.8   Oct 01 1999 11:12:28   jzimny  $ */
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

   Filename: display.h

   Function name:

 --------------------------------- REVISIONS --------------------------------

   Revision #  Date      Author   Description
   ==========  ========  ======   ===========
   0                              Initial Version                   
   1.00        04/18/97  PhilJ    Deleted StuffKey Prototype.
   2.2.5       06/24/97  LAM      Deleted initdisplaymenu.
   2.6         08/28/98  BJB      Deleted DealWithScrollLeds().
   2.7         12/07/98  BJB      Fixed prototype for UpdateScrollLEDs().
   2.8         10-01-99  JZ       Changed InsertProperUnits() to type void

*/

/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void ClearSync(void);
void SetSync(void);
void SetSync(void);
void DisplayResetMsg(void);
void RemoveNull(SINT8 string[]);
void UpdateScrollLEDs(SINT8 MaxIndex);
void InsertProperUnits(SINT8 text[], enum FORMAT UnitFlag);
void DisplayMenu(MENU list[]);
