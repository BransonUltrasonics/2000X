/* $Header:   D:/databases/VMdb/2000Series/INC/rdyweld1.h_v   1.5   24 Jul 2013 14:32:28   gbutron  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996,97        */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 

/*------------------------ MODULE DESCRIPTION ------------------------------*/

/* Module name:   Ready/Weld/Hold                                           */

/* Filename:      Rdyweld1.h                                                */


/*---------------------------- REVISIONS -----------------------------------*/

/* Rev #  Date      Author   Description                                    */
/* =====  ========  =======  ===========                                    */
/* 1.0    04-11-01  BEKymer  Initial Release                                */
/* 1.1    04-11-01  BEKymer  Added some prototypes and real things          */
/* 1.2    04-20-01  BEKymer  Add prototypes for StartSonic3HH,CheckSonic3HH */
/* 1.3    05-09-01  BEKymer  Add prototype for AlStopHH                     */
/* 1.4    09-16-03  BEKymer  Add prototype for StopAllSonicHH               */
/* 1.5    07-23-13  GButron  Add prototypes for StartSonic1HH_1msec_Later   */
/*                           and StartNonTimeHH_1msec_Later                 */
/*                                                                          */
/*------------------------- FUNCTION PROTOTYPING ---------------------------*/


void DealWithHandHeldChange(void);
void TestPBHH(void);
void ExitPBHH(void);
void TestPreReadyHH(void);
void StartSonic1HH(void);
void CheckSonics1HH(void);
void CheckEnergyHH(void);
void CheckPPHH(void);
void CheckGdDetHH(void);
void StopSonic2HH(void);
void StopAllSonicHH(void);
void AlStopHH(void);
void StartNonTimeHH(void);
void TestABDlyHH(void);
void TestABTmeHH(void);
void StartSeekHH(void);
void CheckSeekHH(void);
void HHBeep(void);
void StartSonic1HH_1msec_Later(void);
void StartNonTimeHH_1msec_Later(void);









