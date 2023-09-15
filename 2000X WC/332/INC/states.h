/* $Header:   K:\APPS\PVCS Pro\332new\INC\STATES.H_V   2.11   Oct 11 1999 10:14:02   lmarkure  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 

/*------------------------ MODULE DESCRIPTION ------------------------------*/

/* Module name:                                                             */

/* Filename:      states.h                                                   */


/*---------------------------- REVISIONS -----------------------------------*/

/* Revision #  Date      Author   Description                               */
/* ==========  ========  ======   ===========                               */
/*    0        4/22/96   BEK      Initial Release                           */
/*    1.2.6    7/07/97   LAM      deleted failpowerup prototype             */
/*    1.2.8    08-07-97  BEKymer  Added PowerOffLock prototype              */
/*    2.9      03-23-98  LAM      deleted checkmotion prototype             */
/*    2.9.1.1  06-24-99  JZ       deleted EnterHDown, ExitHDown             */
/*    2.11     10-11-99  LAM      deleted ExitHDAlarm prototype             */
/*    																		*/
/*                                                                          */
/*-------------------------- Function Prototypes ---------------------------*/

void  CheckPD(void);
void  PowerOff(void);
void  PowerOffLock(void);
void  EnterPDown(void);
void  PowerUp(void);
void  PowerOnOK(void);
void  PowerUp(void);
void  TestPO1(void);
void  TestPO2(void);
void  TestPO3(void);
void  TestPO4(void);
void  TestPO5(void);
void  DispAct(void);
void  DispPS(void);
void  DispCtrl(void);
void  DispStack(void);
void  NewState(void);
void  NeverStart(void);
void  Copyright(void);
void  CheckMenuSync(void);

