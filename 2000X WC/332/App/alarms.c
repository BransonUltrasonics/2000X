/* $Header:   D:/SWLab/VMdb/2000Series/App/ALARMS.C_V   1.64.1.0   02 Sep 2008 21:05:22   nhahmed  $ */
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
                              
/*--------------------------- MODULE DESCRIPTION ---------------------------*/

/*   Module name:                                                           */
/*                                                                          */
/*   Filename: genalarm.c                                                   */
/*                                                                          */
/*   Function name:                                                         */
/*------------------------------- REVISIONS --------------------------------*/
                                                                            
/* Revision  Date       Author   Description                                */
/* ========  ========   ======   ===========                                */
/*  1.0      10-08-96   PhilJ    Initial Version                            */
/*  1.1      10-16-96   PhilJ    Deleted AlarmScreenMenu called             */
/*                               from the Main Menu and                     */
/*                               AlarmListMenu.                             */
/*  1.2      10-24-96   PhilJ    Added two Psos General Alarms.             */
/*  1.3      10-25-96   PhilJ    Added General Alarms 65 thru 80.           */
/*  1.4      11-13-96   PhilJ    Alarm counters cleared at start            */
/*                               CountAlarms.                               */
/*  1.5      11-14-96   PhilJ    Added GeneralAlarm #81 & 82.               */
/*  1.6      11-16-96   BEKymer  Speed up alarm checking                    */
/*  1.7      11/21/96   PhilJ    Added General Alarm #46.                   */
/*  1.8      11/26/96   PhilJ    GeneralAlarmCount now adds to              */
/*                               CurrentSetup.GenAlarmCount.                */
/*  1.9      12/02/96   PhilJ    Removed test code from CountAlarms.        */
/*  2.0      01-23-97   PhilJ    Updated alarms per BETA Rel.1              */
/*  2.1      01-23-97   PhilJ    Corrected disabling of Systemfault         */
/*                               alarms.                                    */
/*  2.2      01-23-97   PhilJ    Changed TotalAlarmCount &                  */
/*                               AlarmBuffer to globals.                    */
/*  2.21     01-24-97   LAM      deleted alarmbuffer use runbuffer2         */
/*  2.30     01-29-97   PhilJ    Changed name from Genalarm.c to            */
/*                               alarms.c. Added 43 alarms for rel.1        */
/*  2.31     02-28-97   PhilJ    Added Overload and GeneralAlarm            */
/*                               counter for System Info screen.            */
/*  2.32     03-24-97   PhilJ    Weld_Data alarms masked out in             */
/*                               count alarms.                              */
/*  2.33     04-08-97   PhilJ    Moved PkPowerCutoff and AbsCutoff          */
/*                               to menuwarn.c.                             */
/*  2.34     04-08-97   PhilJ    Moved GeneralAlarmCounter to ready.c.      */
/*  2.35     04-21-97   PhilJ    Moved OverloadCounter to Ready.c           */
/*                               RecordAlarms.                              */
/*  2.36     04-23-97   PhilJ    Deleted PTSFailed menu.                    */
/*                               Added ULSHomeFailed menu.                  */
/*  2.37     05-07-97   PhilJ    Added PkPowerCutoff and AbsCutoff          */
/*                               alarms in warnings.                        */
/*  2.38     05-08-97   PhilJ    Added updating GeneralAlarmCounter         */
/*                               back to CountAlarms.                       */
/*  2.39     05-08-97   PhilJ    Added functions CheckForAlarms and         */
/*                               CheckForWarnings.                          */
/*  2.40     05-29-97   LAM      added W8                                   */
/*  3.1.12   06-20-97   LAM      added new alarm structure                  */
/*  3.1.13   07-21-97   BEKymer  Changed alarm masks for new groups         */
/*  3.1.14   07-24-97   BEKymer  Continue adding alarm group menus          */
/*  3.1.15   07-30-97   BEKymer  Include SetupAlarmCountin TotalAalarmCount */
/*                               Fix bits in EQ9, EQ10 & EQ11               */
/*                               Add singular vs plural alarm message       */
/*  3.1.16   08-07-97   BEKymer  Allow each alarm group to display proper   */
/*                               message                                    */
/*  3.1.17   08-11-97   BEKymer  Fix bug in AbsDistLimit (2-(M)inus instead */
/*                               of minus and (P)lus)                       */
/*  3.1.18   08-12-97   BEKymer  Add additional info sub menu for EQ4, EQ1  */
/*  1.19     09-02-97   BEKymer  Add additional info for overload alarms    */
/*  1.20     09-08-97   LAM      deleted unused .h files,gettotalalarmcount */
/*  1.21     09-22-97   BEKymer  Add additional info sub menu for EQ21      */
/*                               Duplicate alarm structure in alsetup.c     */
/*  1.22     10-03-97   BEKymer  Check WeldData.RejectBitResult for non     */
/*                               limit reject alarms                        */
/*                               Re-order alarms so in reverse order of     */
/*                               CountAlarms()                              */
//  1.23     10.30.97   JBerman  Distiguished between Reject an Suspect menus                                      
/*  1.24     11-12-97   BEKymer  Added additional info for W5               */
/*  1.25     11-18-97   LAM      chged welddata to finalresults             */
/*  1.26     12-12-97   BEKymer  Make sure Reject alarms counted only once  */
/*  1.27     02-03-98   BEKymer  Add alarms CM14, CM15, NC12                */
/*  1.28     02-17-98   BEKymer  Added alarms CM16-CM20                     */
/*  1.29     03-10-98   BEKymer  Added additional information for NC1 alarm */
/*                               In CountAlarms make sure all reject alarms */
/*                               are counted (but only once).               */
/*  1.30     04-28-98   BEKymer  Add additional information for W9          */
/*                               Count calibrate alarms in CountAlarms()    */
/*                               Uncomment W1                               */
/*  1.31     05-05-98   BEKymer  Call the calibration menu directly from the*/
/*                               additional information select key for alarm*/
/*                               CA1.                                       */
/*  1.32     05-08-98   LAM      Call the calibration menu one level up     */
/*  1.33     05-20-98   BEKymer  Moved Energy Not Reached alarm from PR15   */
/*                               to CM21  DCS # 2494                        */
/*  1.34     06-12-98   BEKymer  Jump to next level of calibrate for W8     */
/*                               Change security to MAINTAINENCE for CA1    */
/*  1.35     06-17-98   BEKymer  Move CA1 alarm to EQ20 to simplify calib.  */
/*  1.36     06-24-98   BEKymer  Change EQ20 menu to MAINTAINENCE           */
/*  1.37     08-17-98   LAM      made EQ20 &W8 jump directly to start switch*/
/*                               screen during calibration                  */
/*  1.38     10-06-98   BEKymer  Make alarm W9 display actual WELD collapse */
/*                               instead of total collapse.  Also remove    */
/*                               'Actual = End of Hold" message             */
/*  1.39     10-87-98   LAM      added scfinalcleanup when returning from a */
/*                               recalibrate alarm                          */
/*  1.40     11-02-98   LAM      made sure calibration sequence will be     */
/*                               removed                                    */
/*  1.41     11-23-98   BEKymer  Add CM22 (at the last minute, again)       */
/*  1.42     05-19-99   OFI      put external menus CM5NoforceStepInfo,     */
/*                                CM7NoForceStepInfo, CM10NoForcestepInfo   */                                                      
/*  1.42.1.1 07-06-99   JZ       enabled alarms CM5, 7, 10, 13, 23          */
/*                               added add. info for EQ25                   */
/*  1.43.6.1 02-07-00   JZ       replaced DVS entry with Mask1, Cond1, Mask2, Cond2 */
/*  1.43.6.2 02-22-00   OFI      deleted 'User experience level' from menu strucutures*/
/*  1.44     04-05-00   JZ       merged to trunk Lang                       */
/*  1.45     05-26-00   SCM      Checked in for testing by Laura, John.     */
/*                                                                          */
/*  1.46     06-14-00   SCM     Removed tabs and used 'define' LINESIZE.    */
/*  1.47     06-28-00   BEKymer Changed all MODEL to LEVEL                  */
/*                              Added alarms mask from BBR                  */
/*  1.48     07-18-00   JLH     Modified OLSeekOverload alarm menu to point */
/*                               to OverloadMenuSeek submenu.               */
/*  1.49     08-14-00   LAM     changed name of OLSeekOverload alarm menu   */
/*  1.50     08-21-00   AT      changed Count___Alarms for all languages    */
/*  1.51     09-14-00   LAM     only update 2nd line when an alarm is found */
/*  1.52     01-08-01   BEKymer Add argument for TEXT structure function    */
/*  1.53     04-06-04   VSharma Added NC13,NC14,NC15,OL10 & W11 alarm.      */
/*                              Modified CM17 as MemoryReset alarms.        */
/*  1.54     04-19-04   VSharma Modified EQ19 alarm.                        */
/*  1.55     05-03-04   VSharma Removed menu ptr of EQ19 alarm.             */
/*  1.56     05-17-04   VSharma Added Ver9.00 alarms to alarm menu.         */
/*  1.57     05-21-04   VSharma Added CM17 alarm struct for DUPS.           */
/*  1.58     07-07-04   BEKymer In GetAlarmMask, also update AlarmPtrRam    */
/*                               structure                                  */
/*  1.59     06-10-05   Aare    Commented out unused alarms.                */
/*  1.60     07-25-05   Bwadia  Asian Language support for alarm strings    */
/*  1.61     11-22-05   Bwadia  SBL alarm menus enabled                     */
/*  1.62     12-20-05   Bwadia  USB not present alarm related menus added   */
/*                              Modified for Tracker issue 4029             */
/*  1.63     02-22-06   Bwadia  Modified for tracker issue 4078. Added      */
/*                              additional info for +/- R freq limit alarm  */
/*  1.64     03-12-07   NHAhmed Additional info for PMC Alarms.             */
/*  1.65     09-02-08   NHAhmed CleanUp for multi-language support.         */
/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with Alarms and their submenus                           */


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"
#include "menu.h"
#include "string.h"
#include "weld_obj.h"
#include "genalarm.h"
#include "fmtstrs.h"
#include "battram.h"
#include "alarms.h"
#include "alsetup.h"
#include "sc.h"
#include "menu7a.h"


/*------------------------------ GLOBAL DATA -------------------------------*/
/*                     (scope is global to ALL files)                       */

UINT8 AlarmDetectedFlag = FALSE, SetupAlarmDetectedFlag = FALSE;
ALARM_MASKS *AlarmPtrBBR;
ALARM_MASKS AlarmPtrRam;


/*----------------------------- EXTERNAL DATA ------------------------------*/

extern UINT8 RunScreenFlag;
extern SINT16 MenuCounter;

extern WELD_DATA FinalResults;

extern SETUPS_Ver800 RunningPreset;
extern CONFIGSETUP CurrentSetup;

extern UINT16         LangIndex;


void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);

/*-------------------------- LOCAL TYPE VARIABLES --------------------------*/

UINT16 TotalAlarmCount;

static UINT16  NoCycleAlarmCount;
static UINT16  OverloadAlarmCount;
static UINT16  EquipmentFailureAlarmCount;
static UINT16  CycleModifiedAlarmCount;
static UINT16  SuspectAlarmCount;
static UINT16  RejectAlarmCount;
static UINT16  CalibrateAlarmCount;
static UINT16  WarningCount;

MENUEND endlistGA = { TRUE };


/*--------------------------------- CODE -----------------------------------*/

void ClearTotalAlarmCount(void)
{
   TotalAlarmCount = 0;
}



UINT8 IfAlarmEnabled(UINT32 AlarmCopy, UINT32 BitMask)
{
   UINT8 AlarmEnabled = FALSE;

   if(AlarmCopy & BitMask)
      AlarmEnabled = TRUE;

   return(AlarmEnabled);   
}


/* --  No Cycle Alarms  --*/

void CountNoCycleAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopyNoCycleAlarm;
   int Lang;

   FinalResults.NoCycleAlarms &= AlarmPtrBBR->NoCycle;
   CopyNoCycleAlarm = FinalResults.NoCycleAlarms;
   if (CopyNoCycleAlarm != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if( CopyNoCycleAlarm & AlarmMask)
            NoCycleAlarmCount++;
         AlarmMask <<= 1;
         }
      }
}


/* --  Overload Alarms  --*/

void CountOverloadAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopyOverloadAlarm;
   int Lang;

   FinalResults.OverloadAlarms &= AlarmPtrBBR->Overload;
   CopyOverloadAlarm = FinalResults.OverloadAlarms;
   if (CopyOverloadAlarm != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if( CopyOverloadAlarm & AlarmMask)
            OverloadAlarmCount++;
         AlarmMask <<= 1;
         }
      }
}


/* --  Equipment Failure Alarms  --*/

void CountEquipmentFailureAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopyEquipmentFailureAlarm;
   int Lang;

   FinalResults.EquipmentFailureAlarms &= AlarmPtrBBR->EquipmentFailure;
   CopyEquipmentFailureAlarm = FinalResults.EquipmentFailureAlarms;
   if (CopyEquipmentFailureAlarm != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if(CopyEquipmentFailureAlarm & AlarmMask)
            EquipmentFailureAlarmCount++;
         AlarmMask <<= 1;
         }
      }
}

/* --  Cycle Modified Alarms  --*/

void CountCycleModifiedAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopyCycleModifiedAlarms;
   int Lang;

   FinalResults.CycleModifiedAlarms &= AlarmPtrBBR->CycleModified;
   CopyCycleModifiedAlarms = FinalResults.CycleModifiedAlarms;
   if (CopyCycleModifiedAlarms != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if( CopyCycleModifiedAlarms & AlarmMask)
            CycleModifiedAlarmCount++;
         AlarmMask <<= 1;
         }
      }
}


/* --  Warning Alarms  --*/

void CountWarnings(void)
{
   UINT32 AlarmMask;
   UINT32 CopyWarningAlarms;
   int Lang;
   
   FinalResults.Warnings &= AlarmPtrBBR->Warning;
   CopyWarningAlarms = FinalResults.Warnings;
   if (CopyWarningAlarms != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if( CopyWarningAlarms & AlarmMask)
            WarningCount++;
         AlarmMask <<= 1;
         }
      }
}


/* --  Calibrate Alarms  --*/

void CountCalibrateAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopyCalibrateAlarms;
   int Lang;

   FinalResults.CalibrateAlarms &= CALIBRATEMASK;
   CopyCalibrateAlarms = FinalResults.CalibrateAlarms;
   if (CopyCalibrateAlarms != 0)
      {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28)
         {
         if( CopyCalibrateAlarms & AlarmMask)
            CalibrateAlarmCount++;
         AlarmMask <<= 1;
         }
      }
}


void CountSuspectResults(void)
{
   UINT32 SuspectBitResultMask;
   UINT32 CopySuspectBitResult;
   int Lang;

   FinalResults.SuspectBitResult &= AlarmPtrBBR->Suspect;
   CopySuspectBitResult = FinalResults.SuspectBitResult;
   if(CopySuspectBitResult != 0)
      {
      SuspectBitResultMask = BIT1;
      while(SuspectBitResultMask < BIT28)
         {
         if( CopySuspectBitResult & SuspectBitResultMask)
            SuspectAlarmCount++;
         SuspectBitResultMask <<= 1;
         }
      }
}


void CountRejectResults(void)
{
   UINT32 RejectBitResultMask;
   UINT32 CopyRejectBitResult;
   int Lang;

   FinalResults.RejectBitResult &= (AlarmPtrBBR->Reject | REJECTALARMMASK);
   CopyRejectBitResult = FinalResults.RejectBitResult;
   if(CopyRejectBitResult != 0)
      {
      RejectBitResultMask = BIT1;
      while(RejectBitResultMask < BIT28)
         {
         if( CopyRejectBitResult & RejectBitResultMask)
            RejectAlarmCount++;
         RejectBitResultMask <<= 1;
         }
      }
}


void CountAlarms(void)
{
   UINT16 SetupAlarmCount;
   UINT16 RejectAlarmCountFlag = FALSE;
   int Lang;

   AlarmPtrBBR = (ALARM_MASKS *)BBR800_ALARM_START;   /* Setup pointer to BBR structure for masks  */
   TotalAlarmCount = 0;
   NoCycleAlarmCount = 0;
   OverloadAlarmCount = 0;
   EquipmentFailureAlarmCount = 0;
   CycleModifiedAlarmCount = 0;
   CalibrateAlarmCount = 0;
   WarningCount = 0;
   SuspectAlarmCount = 0;
   RejectAlarmCount = 0;

/*---  The reverse order of these checks will set the priority of which  ---*/
/*---  alarm message will appear when the select key is pressed.         ---*/

   if (FinalResults.Warnings & WARNINGMASK)                  /* Lowest priority */
      CountWarnings();

   if (FinalResults.NoCycleAlarms & NOCYCLEMASK)
      CountNoCycleAlarms();

   if (FinalResults.CycleModifiedAlarms & CYCLEMODIFIEDMASK)
      CountCycleModifiedAlarms();
      
   if (RunningPreset.SuspectLimitsFlag & BIT0) {
      if (FinalResults.SuspectBitResult & SUSPECTBITRESULTMASK)
         CountSuspectResults();
   }

   if (RunningPreset.RejectLimitsFlag & BIT0) {
      if(FinalResults.RejectBitResult & REJECTBITRESULTMASK)
         RejectAlarmCountFlag = TRUE;
   }

/*-- Count Alarms in reject group which are not really reject limits  --*/
/*--            (only if not already counted above)                   --*/

   if (FinalResults.RejectBitResult & REJECTALARMMASK) {
      RejectAlarmCountFlag = TRUE;
   }                                                    
   if (RejectAlarmCountFlag == TRUE) CountRejectResults();                             


   if (FinalResults.OverloadAlarms & OVERLOADMASK)
      CountOverloadAlarms();

   if (FinalResults.EquipmentFailureAlarms & EQUIPMENTFAILUREMASK)
      CountEquipmentFailureAlarms();

   if (FinalResults.CalibrateAlarms & CALIBRATEMASK)  /* Highest  */
      CountCalibrateAlarms();

   SetupAlarmCount = GetSetupAlarmCount();
   TotalAlarmCount = NoCycleAlarmCount + OverloadAlarmCount + 
                     EquipmentFailureAlarmCount + CycleModifiedAlarmCount + 
                     SuspectAlarmCount + RejectAlarmCount + 
                     CalibrateAlarmCount + WarningCount + SetupAlarmCount;
 
}

UINT8 CheckForAlarms(void)
{
   UINT8 AlarmDetected = FALSE;

   if((FinalResults.NoCycleAlarms & NOCYCLEMASK) ||
      (FinalResults.OverloadAlarms & OVERLOADMASK) ||
      (FinalResults.EquipmentFailureAlarms & EQUIPMENTFAILUREMASK) ||
      (FinalResults.CycleModifiedAlarms & CYCLEMODIFIEDMASK) ||
      (FinalResults.CalibrateAlarms & CALIBRATEMASK) ||
      (FinalResults.SuspectBitResult & SUSPECTBITRESULTMASK) ||
      (FinalResults.RejectBitResult & REJECTBITRESULTMASK))
         AlarmDetected = TRUE;

   return(AlarmDetected);
}


UINT8 CheckForWarnings(void)
{
   UINT8 WarningDetected = FALSE;

   if(FinalResults.Warnings & WARNINGMASK)
      WarningDetected = TRUE;
   return(WarningDetected);
}


void GetAlarmMask(void)
/****************************************************************************/
/*                                                                          */
/* This function will copy the alarm defines into BBR where they can be     */
/* modified from the BUC menu.  This function should only be called when    */
/* the system is configured.  Any changes made from the BUC menu will be    */
/* lost when reconfiguring.                                                 */
/*                                                                          */
/****************************************************************************/
{
   AlarmPtrBBR = (ALARM_MASKS *)BBR800_ALARM_START;

   AlarmPtrBBR->SetupGroup1 = SETUPGROUP1MASK;
   AlarmPtrBBR->SetupGroup2 = SETUPGROUP2MASK;
   AlarmPtrBBR->SetupGroup3 = SETUPGROUP3MASK;
   AlarmPtrBBR->SetupGroup4 = SETUPGROUP4MASK;
   AlarmPtrBBR->SetupGroup5 = SETUPGROUP5MASK;
   AlarmPtrBBR->SetupGroup6 = SETUPGROUP6MASK;
   AlarmPtrBBR->SetupGroup7 = SETUPGROUP7MASK;
   AlarmPtrBBR->SetupGroup8 = SETUPGROUP8MASK;
   AlarmPtrBBR->SetupGroup9 = SETUPGROUP9MASK;
   AlarmPtrBBR->SetupGroup10 = SETUPGROUP10MASK;
   AlarmPtrBBR->Overload = OVERLOADMASK;
   AlarmPtrBBR->NoCycle = NOCYCLEMASK;
   AlarmPtrBBR->EquipmentFailure = EQUIPMENTFAILUREMASK;
   AlarmPtrBBR->CycleModified = CYCLEMODIFIEDMASK;
   AlarmPtrBBR->Reject = REJECTBITRESULTMASK;
   AlarmPtrBBR->Suspect = SUSPECTBITRESULTMASK;
   AlarmPtrBBR->Warning = WARNINGMASK;

   AlarmPtrRam.SetupGroup1 = AlarmPtrBBR->SetupGroup1;
   AlarmPtrRam.SetupGroup2 = AlarmPtrBBR->SetupGroup2;
   AlarmPtrRam.SetupGroup3 = AlarmPtrBBR->SetupGroup3;
   AlarmPtrRam.SetupGroup4 = AlarmPtrBBR->SetupGroup4;
   AlarmPtrRam.SetupGroup5 = AlarmPtrBBR->SetupGroup5;
   AlarmPtrRam.SetupGroup6 = AlarmPtrBBR->SetupGroup6;
   AlarmPtrRam.SetupGroup7 = AlarmPtrBBR->SetupGroup7;
   AlarmPtrRam.SetupGroup8 = AlarmPtrBBR->SetupGroup8;
   AlarmPtrRam.SetupGroup9 = AlarmPtrBBR->SetupGroup9;
   AlarmPtrRam.SetupGroup10 = AlarmPtrBBR->SetupGroup10;
   AlarmPtrRam.Overload = AlarmPtrBBR->Overload;
   AlarmPtrRam.NoCycle = AlarmPtrBBR->NoCycle;
   AlarmPtrRam.EquipmentFailure = AlarmPtrBBR->EquipmentFailure;
   AlarmPtrRam.CycleModified = AlarmPtrBBR->CycleModified;
   AlarmPtrRam.Reject = AlarmPtrBBR->Reject;
   AlarmPtrRam.Suspect = AlarmPtrBBR->Suspect;
   AlarmPtrRam.Warning = AlarmPtrBBR->Warning;

}   

                          

