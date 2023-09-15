/* $Header:   D:/SWLab/VMdb/2000Series/App/VF.C_V   2.31   04 Sep 2008 20:16:40   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*     Functions:                                                           */                                                                   
/*       1. InitVF()                                                        */
/*       2. ClrVFLines(LineNums)                                            */
/*       3. WriteToVF()                                                     */
/*       4. UpdateLine(String,LineNum)                                      */
/*       5. MoveCursor(LineNum,LinePos)                                     */
/*                                                                          */
/*                                                                          */
/*                          History of changes                              */
/*                          ------------------                              */
/*                                                                          */
/* Rev      Who      Date        Description of change                      */
/* ---- --- -------- ------------------------------------------------------ */
/*                                                                          */
/* 1.00     Phil J   07/12/96    Increases VFBuffer from 500 to 1000        */
/* 2.00     LAM      08/16/96    deleted interrupt writevf checks busy      */
/* 3.00     LAM      10/11/96    cleanup updatevfbuffer                     */
/* 4.00     PhilJ    12/09/96    Added function IsVFBufferEmpty()           */
/* 4.10     PhilJ    04/02/97    Modified UpdateVFBuf and WriteToVF         */
/* 5.2.12   KD       07/11/97    cleanup warnings                           */
/* 2.14     PhilJ    07/17/97    Chngd special character from 0x40 to 0x7e  */
/* 6.2.15   LAM      07/29/97    chged move.w to ori.w, deleted xmitflags   */
/* 6.2.16   LAM      07/29/97    added xmitflags                            */
/* 6.2.17   LAM      09/10/97    added dtoutput.h                           */
/* 6.2.18   JBerman  09.11.97    Line Alignment                             */
/* 2.19     BJB      11.04.97    Fixed bug that would cause system to hang  */
/*                               if buffer fills up.                        */
/*                               Deleted unnecessary XmitFlags structure.   */
/* 2.20     BJB      12.29.97    Deleted Ascent terminal support code.      */
/* 2.21     BJB      12.29.97    MoveCursor() --> MoveVFCursor()            */
/*                               UpdateLine() --> UpdateVFLine()            */
/*                               Added WriteDisplay(), MoveCursor(),        */
/*                                UpdateLine().                             */
/* 2.22     BJB      12.31.97    Added code to do terminal output to        */
/*                                ClrVFLines(), WriteDisplay(),             */
/*                                MoveCursor(), and UpdateLine().           */
/* 2.23     BJB      08.19.98    Added function ClrVFScreen() to clear only */
/*                                screen. Calls from init routine.          */
/*                               UpdateVFLine() changed to VFWriteLine().   */
/*                                with -1 row #, in VFSCRN.C.               */
/*                               Changed names of display & term function   */
/*                                calls to new names.                       */
/* 2.34     LAM      04/30/99    fixed compiler errors                      */
/* 2.35     JZ       10-11-99    made InitializeFrontPanelDisplay() type void*/
/* 2.25.3   bwadia   10/27/04    Check for VFD busy only if QVGA not present*/
/* 2.28     BEKymer  10-27-04    Move 2.25.3.0 to tip as 2.28 for 9.01 build*/
/* 2.29     Bwadia   02-08-06    Used VGAHWPresent flag instead of QVGAHWAvail*/
/*                               for checking VFD busy                        */
/* 2.30     NHAhmed  10-22-07    Changes done for LangTest phase 0          */
/* 2.31     YGupta   09-04-08    CleanUp for LangTest Project.         */

/****************************************************************************/                                                                          


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


/*
 -------------------------- LOCAL FUNCTIONS--------------------------------
*/


/*
 ------------------------------- LOCAL DATA ------------------------------------
*/

/*
 ------------------------------- CODE ------------------------------------
*/
