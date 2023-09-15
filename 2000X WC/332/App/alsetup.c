/* $Header:   D:/SWLab/VMdb/2000Series/App/ALSETUP.C_V   1.52.1.1   04 Sep 2008 20:16:18   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                           */
/*                                                                          */
/*************************                         **************************/
                                     
/*--------------------------- MODULE DESCRIPTION ---------------------------*/

/*   Module name:   SETUP_ALARMS                                            */
/*                                                                          */
/*   Filename:      genalarm.c                                              */
/*                                                                          */
/*   Function name:                                                         */


/*------------------------------- REVISIONS --------------------------------*/
                                                                            
/* Revision  Date       Author   Description                                */
/* ========  ========   ======   ===========                                */
/*  1.0      07-22-97   BEKymer  Initial Version                            */
/*  1.1      07-29-97   BEKymer  Remove extra test on group3 alarms         */
/*  1.2      07-30-97   BEKymer  New function - GetSetupAlarmCount          */
/*  1.3      08-05-97   BEKymer  In GetSetupAlarmCount actually go and      */
/*                               count the alarms in the setup registers    */
/*  1.4      09-03-97   BEKymer  Uncomment SE258 (AdvFeaturesinUse)         */
/*  1.5      09-23-97   BEKymer  Duplicate alarms from alarm.c              */
/*                               Clear SetupAlarmCount in ClearSetupAlarms()*/
/*  1.6      09-26-97   BEKymer  Added SetupAlarmFlag                       */
/*  1.7      10-03-97   BEKymer  Re-order alarms in MENU SetupAlarmsMenu so */
/*                               in reverse order on CountAlarms()          */
/*  1.8      11-22-97   BEKymer  In GetSetupAlarmCount check VerifyPreset.. */
/*                               flag (see note in GetSetupAlarmCount).     */
/*  1.9      11-14-97   BEKymer  Don't clear AlarmDetectedFlag in Clear     */
/*                               SetupAlarms().                             */
/*  1.10     01-20-98   PaulG    Added string for printer offline in StrSE_270 */
/*  1.11     01-26-98   BEKymer  Remove sub menu from SE270 (no addl info)  */
/*  1.12     02-03-98   BEKymer  Add alarms CM14, CM15, NC12                */
/*  1.13     02-11-98   BEKymer  Put sub menu back in for SE270             */
/*  1.14     02-17-98   BEKymer  Add alarms CM15-CM20                       */
/*  1.15     04-02-98   BEKymer  Use AlarmsDesStr to display title line     */
/*                               when setup alarms occur.                   */
/*                                                                          */
/*-----------04-14-98---BEKymer--Start of release 2.5 coding changes--------*/
/*                                                                          */
/*  1.16     04-14-98   BEKymer  Uncommented 2.5 alarms                     */
/*  1.17     04-29-98   BEKymer  Uncommented W1 alarm                       */
/*  1.18     05-20-98   BEKymer  Moved Energy Not Reached alarm from PR15   */
/*                               to CM21  DCS # 2494                        */
/*  1.19     05-27-98   BEKymer  Added SE120-Missing part Max/Min Crossed   */
/*  1.20     06-17-98   BEKymer  Moved Ca1 to EQ20 to simplify calibration  */
/*  1.21     06-24-98   BJB      Changed NORMAL to BASIC.                   */
/*  1.22     06-25-98   BJB      Calls HandleFeaturesAlarm() when dealing   */
/*                               with alarm "Non Basic Feat. Used"          */
/*  1.23     06-26-98   BJB      Removed change in 1.22; Instead, uses      */
/*                               different Features menu with item that     */
/*                               allows direct edit of CrntPrset.Features.  */
/*                               This works better if user tries to run     */
/*                               cycle right on alarm addnl info screen.    */
/*                                                                          */
/*  1.24     05-25-99   OFI      Add new alarms for Force Product           */
/*  1.25     06-11-99   OFI      Put SE262                                  */
/*  1.26     06-14-99   OFI      Fixed absolute mode problem for Ver7.f0    */
/*  1.27.1.1 07-06-99   JZ       enabled CM5NoForceStep, 7, 10, 13, 23      */
/*                               EQ25text enabled                           */
/*  1.29     10-25-99   OFI      Deleted SE46 from group two                */
/*  1.30     02-09-00   OFI      Deleted SE22,23,68,69                      */
/*  1.31     04-05-00   JZ       removed DVS and added Mask1, Cond1, Mask2, Cond2 */
/*                               removed 'User experience level from menu   */
/*                               structs, commented out AlarmSE258          */
/*                               merged Lang to trunk                       */
/*  1.32     05-26-00   SCM      Checked in for testing by Laura, John.     */
/*  1.33     06-14-00   SCM      Removed tabs and checked in for Ver8 build */
/*  1.34     06-28-00   BEKymer  Changed all MODEL to LEVEL                 */
/*  1.35     04-24-01   LAM      Changed SE46 alarm to Preset Not Available */
/*  1.36     08-12-03   JOY      Added function 'IsAlarmMptr()', which detects*/
/*                               Alarm submenus which doesn't have any item */
/*  1.37     12-05-03   JOY      Added Missed Blankmenus to the IsAlarmMptr()*/
/*  1.38     04-06-04   VSharma  Added SE289,SE290,SE291,SE292,SE293,SE294, */
/*                               NC13,NC14,NC15,OL10,CM17 & W11 alarms      */
/*                               in 'SetupAlarmsMenu'.                      */
/*  1.39     04-19-04   VSharma  Changed 'SetupAlarmsMenu' for EQ19 alarm.  */
/*  1.40     05-03-04   VSharma  Added SE295 alarm.                         */
/*  1.41     05-21-04   VSharma  Modified 'SetupAlarmsMenu' for CM17.       */
/*  1.42     07-29-04   JOY      Added Alarm SE296                          */
/*  1.43     06-10-05   Aare     Commented out unused alarms.               */
/*  1.44     07-25-05   Bwadia   Asian Language support and VGA exit button added*/
/*  1.45     10-24-05   Bwadia   +R PMC and -R PMC alarm items enabled      */
/*  1.46     10-28-05   Bwadia   Sequencing alarm added in setup menu       */
/*  1.47     11-22-05   Bwadia   SBL alarm menus enabled                    */
/*  1.48     12-20-05   Bwadia   USB alarm menu enabled                     */
/*  1.49     01-18-07   NHAhmed  Changes for Setup Alarm SE298.             */
/*  1.50     03-27-07   NHAhmed  Changes for Setup Alarm SE112, SE113,SE114,*/
/*                               SE115, SE122, SE229,SE232,SE236,SE258      */
/*  1.51     05-23-07   NHAhmed  Changes for Setup Alarm SE297.             */
/*  1.52     06-06-08   NHAhmed  Added a new function SendAlarmBits().      */
/*  1.53     09-02-08   NHAhmed  CleanUp for multi-language support.        */
/*  1.54     09-04-08   YGupta   CleanUp for LangTest Project.               */
/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with Setup Alarms and their submenus                     */


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"
#include <prepc.h>
#include "menu.h"
#include "weld_obj.h"
#include "error.h"
#include "genalarm.h"
#include "keypad.h"
#include "display.h"
#include "fmtstrs.h"
#include "selctkey.h"
#include "alarms.h"
#include "alsetup.h"


/*------------------------------ GLOBAL DATA -------------------------------*/
/*                     (scope is global to ALL files)                       */

SETUP_DATA_ALARMS SetupData;
#define ALARMGROUPSNUMBER 17


/*----------------------------- EXTERNAL DATA ------------------------------*/

extern UINT8  RunScreenFlag;
extern SINT16 MenuCounter;
extern UINT16 TotalAlarmCount;
extern UINT16 SetupAlarmFlag;
extern UINT16 VerifyPresetInProcess;

extern SETUPS_Ver800 CurrentPreset;
extern CONFIGSETUP   CurrentSetup;
extern UINT8 AlarmDetectedFlag, SetupAlarmDetectedFlag;

extern WELD_DATA       FinalResults;
void LangStrCpy(SINT8 * to, SINT8 * from);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);




/*-------------------------- LOCAL TYPE VARIABLES --------------------------*/

UINT16 TotalSetupAlarmCount;

static UINT16  SetupAlarmCount;

MENUEND endlistSE = { TRUE };


/*--------------------------------- CODE -----------------------------------*/


/* --  Setup Alarms  --*/

UINT16 GetSetupAlarmCount(void)
/****************************************************************************/
/*                                                                          */
/*  VerifyPresetInProcess is checked here to ensure that the weldmngr (OP_  */
/*  RESET) is not calling VerifyPreset (and therefore calling ClearSetup    */
/*  Alarms) while TestReady State is calling CheckIfResetRequired(), which  */
/*  looks at the SetData.structure which ClearSetupAlarm clears.  This will */
/*  happen every once in a while, while there are still setup alarms but    */
/*  the damn user is still pressing the reset key anyway.                   */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Retval = TRUE;

   if (VerifyPresetInProcess == FALSE) {
      CountSetupAlarms();
      Retval = SetupAlarmCount;
   }
   return(Retval);
}



UINT8 CheckForSetupAlarms(void)
{
   UINT8 AlarmDetected = FALSE;

   if ( (SetupData.SetupErrorAlarms1 &= SETUPGROUP1MASK) ||
        (SetupData.SetupErrorAlarms2 &= SETUPGROUP2MASK) ||
        (SetupData.SetupErrorAlarms3 &= SETUPGROUP3MASK) ||
        (SetupData.SetupErrorAlarms4 &= SETUPGROUP4MASK) ||
        (SetupData.SetupErrorAlarms5 &= SETUPGROUP5MASK) ||
        (SetupData.SetupErrorAlarms6 &= SETUPGROUP6MASK) ||
        (SetupData.SetupErrorAlarms7 &= SETUPGROUP7MASK) ||
        (SetupData.SetupErrorAlarms8 &= SETUPGROUP8MASK) ||
        (SetupData.SetupErrorAlarms9 &= SETUPGROUP9MASK) ||
        (SetupData.SetupErrorAlarms10 &= SETUPGROUP10MASK) )
         AlarmDetected = TRUE;

   return(AlarmDetected);
}


void ClearSetupAlarms(void)
{
   SetupData.SetupErrorAlarms1 = 0;
   SetupData.SetupErrorAlarms2 = 0;
   SetupData.SetupErrorAlarms3 = 0;
   SetupData.SetupErrorAlarms4 = 0;
   SetupData.SetupErrorAlarms5 = 0;
   SetupData.SetupErrorAlarms6 = 0;
   SetupData.SetupErrorAlarms7 = 0;
   SetupData.SetupErrorAlarms8 = 0;
   SetupData.SetupErrorAlarms9 = 0;
   SetupData.SetupErrorAlarms10 = 0;
   SetupAlarmDetectedFlag = FALSE;
//   AlarmDetectedFlag = FALSE;  /* Shouldn't do it here, I think !! (BEK)  */
//   SetupAlarmCount = 0;        /* Only clear when recounted, not here     */
   TotalAlarmCount = 0;
//   SetupAlarmFlag = FALSE;     /* Only clear when verify preset, not here */
}

UINT16 SendAlarmBits(UINT8 * to)
/************************************************************************/
/*                                                                      */
/* This  function sends generated alarm bit position to SBC.            */
/*                                                                      */
/************************************************************************/
{
   UINT16 length =0;
   
   length += AddToBuffer(&to, (UINT8)(ALARMGROUPSNUMBER));

   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms1)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms1)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms1)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms1));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms2)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms2)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms2)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms2));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms3)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms3)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms3)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms3));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms4)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms4)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms4)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms4));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms5)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms5)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms5)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms5));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms6)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms6)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms6)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms6));	  

   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms7)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms7)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms7)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms7));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms8)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms8)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms8)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms8));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms9)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms9)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms9)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms9));	  
	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms10)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms10)>>16));	  
   length += AddToBuffer(&to, (UINT8)((SetupData.SetupErrorAlarms10)>>8));	  
   length += AddToBuffer(&to, (UINT8)(SetupData.SetupErrorAlarms10));	  

   length += AddToBuffer(&to, (UINT8)((FinalResults.EquipmentFailureAlarms)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.EquipmentFailureAlarms)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.EquipmentFailureAlarms)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.EquipmentFailureAlarms));

   length += AddToBuffer(&to, (UINT8)((FinalResults.OverloadAlarms)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.OverloadAlarms)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.OverloadAlarms)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.OverloadAlarms));	  

   length += AddToBuffer(&to, (UINT8)((FinalResults.RejectBitResult)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.RejectBitResult)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.RejectBitResult)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.RejectBitResult));
	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.SuspectBitResult)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.SuspectBitResult)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.SuspectBitResult)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.SuspectBitResult));

   length += AddToBuffer(&to, (UINT8)((FinalResults.CycleModifiedAlarms)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.CycleModifiedAlarms)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.CycleModifiedAlarms)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.CycleModifiedAlarms));

   length += AddToBuffer(&to, (UINT8)((FinalResults.NoCycleAlarms)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.NoCycleAlarms)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.NoCycleAlarms)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.NoCycleAlarms));

   length += AddToBuffer(&to, (UINT8)((FinalResults.Warnings)>>24)); 	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.Warnings)>>16));	  
   length += AddToBuffer(&to, (UINT8)((FinalResults.Warnings)>>8));	  
   length += AddToBuffer(&to, (UINT8)(FinalResults.Warnings));

   return (length);
}

void CountSetupAlarms(void)
{
   UINT32 AlarmMask;
   UINT32 CopySetupAlarm;

   SetupAlarmCount = 0;
   SetupData.SetupErrorAlarms1 &= SETUPGROUP1MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms1;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms2 &= SETUPGROUP2MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms2;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms3 &= SETUPGROUP3MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms3;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms4 &= SETUPGROUP4MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms4;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms5 &= SETUPGROUP5MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms5;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms6 &= SETUPGROUP6MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms6;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms7 &= SETUPGROUP7MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms7;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms8 &= SETUPGROUP8MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms8;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms9 &= SETUPGROUP9MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms9;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
   SetupData.SetupErrorAlarms10 &= SETUPGROUP10MASK;
   CopySetupAlarm = SetupData.SetupErrorAlarms10;
   if (CopySetupAlarm != FALSE) {
      AlarmMask = BIT1;
      while(AlarmMask < BIT28) {
         if (CopySetupAlarm & AlarmMask)
            SetupAlarmCount++;
         AlarmMask <<= 1;
      }
   }
}

