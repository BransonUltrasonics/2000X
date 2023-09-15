/* $Header:   L:/pvcs/1000/psos332/archives/app/alsetup.h_v   1.1   31 Jul 1997 13:19:28   BKYMER  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*   Copyright (c) Branson Ultrasonics Corporation, 1995,96,97              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/*                                                                          */
/*   Module name:   Alarms                                                  */
/*                                                                          */
/*   Filename:      alsetup.h                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*   Revision #  Date      Author   Description                             */
/*   ==========  ========  ======   ===========                             */
/*      1.0      07-29-97  BEKymer  Original Release                        */
/*      1.1      07-30-97  BEKymer  New function prototype-GetSetupAlarmCo..*/
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/




/*---------------------------- INCLUDE FILES -------------------------------*/  



/*------------------------- Function Prototypes ----------------------------*/  

UINT16 GetSetupAlarmCount(void);
UINT8 CheckForSetupAlarms(void);
void  ClearSetupAlarms(void);
void  CountSetupAlarms(void);



/*-------------------------------- DEFINES ---------------------------------*/


