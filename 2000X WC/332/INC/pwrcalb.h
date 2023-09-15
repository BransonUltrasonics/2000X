/* $Header:   K:/APPS/PVCS Pro/332new/INC/PWRCALB.H_V   1.6   29 Mar 2001 14:55:32   BKymer  $ */
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

/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Power Calibration                                           */
/*                                                                          */
/*                                                                          */
/*          Written by:   Laura Markure                                     */
/*                Date:   07-28-97                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date        Author       Description                         */
/*  =========  =========   ===========  ===========                         */
/*     0       07-28-97    LAM          Initial release                     */
/*    1.1.1    07-31-97    LAM          added more prototypes               */
/*    1.1.3    08-15-97    LAM          added more prototypes               */
/*    1.1.4    08-27-97    LAM          added powercalabort                 */
/*    1.6      01-16-01    BEKymer      Add argument to RequestCalPower as  */
/*                                       now required by menu structure     */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

void SelectPowerCalSequence(void);
void PowerCalInit(void);
void CheckPower(UINT32);
void PowerCleanupArg(UINT32);
void PowerCleanup(void);
void TurnOffSonics(UINT32);
void RequestCalPower(UINT32);
void ClearPwrFlg(void);
void ReadingPower(void);
void RecordPower1(UINT32);
void RecordPower2(UINT32);
void BuildPowerTable(UINT32);
UINT16 UpdatePowerTable(SINT16 TableVals[], UINT16 Y1, UINT16 Y2,
	  UINT16 X1, UINT16 X2);
void InitPwr(void);
void PowerCalAbort(void);
