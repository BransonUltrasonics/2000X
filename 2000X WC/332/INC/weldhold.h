/* $Header:   K:/APPS/PVCS Pro/332new/INC/WELDHOLD.H_V   2.26   Sep 16 2003 09:45:58   BKymer  $ */
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

/* Module name:                                                             */

/* Filename:      weldhold.h                                                */


/*---------------------------- REVISIONS -----------------------------------*/

/* Revision #  Date      Author   Description                               */
/* ==========  ========  ======   ===========                               */
/*    0        04/22/96   BEK      Initial Release                          */
/*    1        01-24-97   LAM      added prototype                          */
/*    2        02-18-97   LAM      added prototype for ab                   */
/*    3        02-25-97   LAM      added prototype for cycleaborts          */
/*    4        05-03-97   LAM      added prototype for alstopseek           */
/*    5.2.16   06-05-97   BEKymer  Add function prototype for AlStopTest    */
/*    5.2.17   07-01-97   LAM      deleted checkencoder                     */
/*    5.2.18   07-02-97   LAM      Added prototype for no encoder           */
/*                                 deleted getcurrentmodel# prototype       */
/*    2.19     10-28-97   BEKymer  Add StartAHold prototype                 */
/*    2.20     09-02-98   BEKymer  Add argument to CheckControlLimitsD      */
/*    2.21     12-16-99   LAM      removed unused references to profiling   */
/*    2.22     07-21-00   BEKymer  Add StartDUPSDataCollection and          */
/*                                     IsDUPSDataCollectionComplete         */
/*    2.23     09-18-00   LAM      added stopahold to catch dups overload info */
/*    2.24     04-12-01   BEKymer  Add CheckForForceStepping and            */
/*                                  CheckEnergyComp prototype               */
/*                                 Move MAXSEEKTIME, SEEKDELAYTIME from     */
/*                                  weldhold.c                              */
/*    2.25     04-20-01   BEKymer  Moved DEFAULT_MAXTIMEOUT from weldhold.c */
/*    2.26     09-08-03   BEKymer  Add prototype for FinalStopSonic()       */
/*                                                                          */
/*                                                                          */



#define MAXSEEKTIME          500 /* Time from Allan Roberts - 500 ms  08-08-96  */
                                 /* Back to 500ms (Kevin)  DCS #2540  05-19-98  */
#define SEEKDELAYTIME        300 /* Time before actual seek starts              */
#define DEFAULT_MAXTIMEOUT  6000 /* Max weld time - default                     */


/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

void    DisplayTestPower(SINT16 Power);
void    DisplayWeldPower(SINT16 Power); 
void    CheckFrequencyLimits(void);
BOOLEAN CheckForTriggerLost(void);
void    CheckForSafety(void);
void    CheckControlLimitsD(UINT16 EncoderCheck);
void    CheckControlLimits(void);
void    CheckCycleAborts(void);
void    CheckEnergyComp(void);
void    CheckForForceStepping(void);
void    EnterTrigDly(void);
void    ExitTrigDly(void);
void    StartSonic1(void);
void    CheckSonics1D(void);
void    CheckSonics1(void);
void    StartSonic1A(void);
void    CheckSonics1A(void);
void    StartSonic2(void);
void    CheckSonics2D(void);
void    CheckSonics2(void);
void    StartSonic3(void);
void    CheckSonics3D(void);
void    CheckSonics3(void);
void    CheckSonics3A(void);
void    CheckSonics3B(void);
void    CheckSonics3CD(void);
void    CheckSonics3C(void);
void    CheckSonics4D(void);
void    CheckSonics4(void);
void    CheckSonics5(void);
void    CheckSonics6(void);
void    CheckSonics7D(void);
void    CheckSonics7(void);
void    CheckSonics8D(void);
void    CheckSonics8(void);
void    CheckSonics9D(void);
void    CheckSonics9(void);
void    StopSonic1(void);
void    StopSonic2(void);
void    StopAllSonic(void);
void    AlStopSonics(void);
void    AlStopTest(void);
void    StartBrake(void);
void    CheckBrake(void);
void    AlStopSeek(void);
void    StartHold(void);
void    StartAHold(void);
void    CheckHold(void);
void    StopHold(void);
void    StopAHold(void);
void    StartABDly(void);
void    StopABDly(void);
void    TestABDly(void);
void    ALStopABD(void);
void    StartABTme(void);
void    StopABTme(void);
void    TestABTme(void);
void    RampOff(void);
void    StartSeek(void);
void    CheckSeek(void);
void    StopSeek(void);
void    ALStopABT(void);
void    StartDUPSDataCollection(void);
BOOLEAN IsDUPSDataCollectionComplete(void);

