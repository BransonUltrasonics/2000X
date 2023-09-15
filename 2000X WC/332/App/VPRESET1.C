/* $Header:   D:/SWLab/VMdb/2000Series/App/VPRESET1.C_V   1.69   08 Jun 2010 14:11:58   NHahmed  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 2009           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

/*--------------------------- MODULE DESCRIPTION ---------------------------

   Module name:   VERIFY_PRESET_MODEL1  

   Filename:      vpreset1.c     

   Function Name: VerifyPresetModel1
  
        Written by:    Barry E. Kymer
      Date:          07-07-97
      Language:      "C"

 ---------------------------------- REVISIONS -----------------------------

    Revision  Date      Author     Description
    ========  ========  =========  ===========
      1.0     07-07-97  BEKymer    Sort of removed from weld_obj.c
      1.2     07-23-97  BEKymer    Changed logic on some CheckForDistance checks
   1.4     07-31-97  BEKymer    Rewrite check for weld modes vs model
   1.5     08-04-97  BEKymer    Rewrite check for weld modes vs model - again
   1.6     09.10.97  JBerman    Added default into case statements
   1.7     09.10.97  JBerman    Got Compiler Warning. Changed the following line:
                                StartWeldMsg.setup_data_ptr =  SetupDataPtr; // It was &SetupDataPtr; 
   1.8     09-12-97  LAM        made runningpreset to extern
   1.9     10-22-97  BEKymer    Create VerifyPresetInProcess flag
   1.10    10-24-97  BEKymer    At the end of VerifyPreset make sure Alarm
                                DetectedFlag is still set TRUE if in fact
                                there is still a setup alarm.
                                Also, count setup alarms if any existed.
   1.11    10-30-97  BEKymer    Call BootSF to update features register
   1.12    11-20-97  PaulG      Added GetPtsIncrement() to verify preset section. 
   1.13    11-20-97  PaulG      Added GetPtsIncrement() Prototype.
   1.14    12-02-97  BEKymer    Moved POWERMULTIPLIER & POWERROUNDOFF and call
                                to SelectWeldSequence from weldmngr.c
   1.15    12-04-97  BEKymer    Move BBR into VerifyPreset().
   1.16    12-13-97  LAM        multiply amp control values by 10    
   1.17    01-20-98  PaulG      Added Printer Offline to setup alarms.
   1.18    02-06-98  BEKymer    Remove POWERROUNDOFF from power values.
   1.19    02.19.98  JBerman    CurrentSetup.Features->CurrentPreset.Features
                                DCS 2402
   1.20    02-20-98  BEKymer    Multiply Suspect/Reject limits by 10 to
                                accommodate for tenths.
   1.21    03-03-98  BEKymer    Remove '==' in PresetHasBeenOKed = TRUE in
                                if (PresetFailed == TRUE)
   1.22    04-06-98  BEKymer    Create new function CheckForStepping()
   1.23    05-04-98  BEKymer    CheckForStepping() on MODEL2 (was only doing
                                MODEL1).
   1.24    05-14-98  BEKymer    Remove all references to ModelMask.  It appears
                                that this variable is no longer needed.
   1.25    08-11-98  BEKymer    No longer multiply power readings by 10, they
                                are now entered in tenths.
   1.26    09-16-98  BEKymer    Fix AmpTrigPowerValue and ForceTrigPowrValue
                                They were still multiplied by 10 (I missed
                                them in ver 1.25 08-11-98).
   1.27    10-14-98  BEKymer    Removed some old commented code.  Add check
                                for valid actuator in MODEL1, MODEL2 and
                                MODEL3 (otherwise generate EQ14 alarm).
   1.28    04-26-99  OFI        Changed for diab
   1.29    05-11-99  LAM        typecasted ~BITS to eliminate warnings with DIAB
   1.30    05-26-99  LAM        Added call to checkbattramDefaults to update the
                                bbram with the correct defaults.
   1.32.1.1 07-12-99 JZ         added ErrorCode to alarm to SE268
   1.34     08-04-99 JZ         added ErrorCodeFlag
   1.35     08-06-99 JZ         added RecordErrorCode
   1.36     10-21-99 OFI        deleted SE46because this conditions checked in SE193
   1.37     11-04-99 OFI        Changd 0x7d to defines and include menu.h and deleted tabs
   1.38     11-06-99 OFI        Fixed alignment
   1.38.6.2 01-04-00 OFI        removed #include "features.h";removed call to BootSF();
                                deleted conditions for alarm SE258.
   1.39     04-06-00 JZ         merged Lang to trunk
   1.40     06-28-00  BEKymer   Changed all MODEL to LEVEL also added switch statement for 
                                 LEVEL_a and LEVEL_TEST
   1.41     07-13-00  BEK/DJL   fixed some encoder issues.                                 
   1.42     08-16-00  JLH       Added code to detect invalid preset to VerifyPreset function.  Moved this code from
                                 RecallCompressedPreset. 
   1.43     08-18-00  JLH       Added code to VerifyPreset function to check for conflict of AE
                                 actuator and welding mode and generate Invalid Preset alarm if
                                 they are in conflict.  
   1.44     08-22-00  JLH       Commented out Verified logic.  Associated invalid preset detection will be deferred
                                 to Ver9.
   1.45     09-06-00  BEKymer   Enhanced logic to check for stepping.  All control levels need to
                                 check because level 'f' with an AE or AED is still not valid
                                 for force stepping.
   1.46     09-07-00  BEKymer   Return ERRORCODE2 or 3 in CheckForStepping if all is not ok
   1.47     09-14-00  BEKymer   Check for valid DUPS/COPS association (SE268 errorcode 9)
                                 Fix bug in return value of CheckForStepping()
   1.48     10-04-00  AT        line 236 - added else { DUPS_DownloadCurrPS() ... }
   1.49     10-05-00  BEKymer   Removed underscores from DUPSChangePending
   1.50     10-10-00  BEKymer   Check DUPSChangePending flag before downloading
                                 to the DUPS
   1.51     11-15-00  BEKymer   Make LEVEL_TEST function the same as LEVEL_f
   1.52     11-17-00  BEKymer   Only put values into Retval (VerifyPreset() ) when a
                                 setup alarm occurs.  This prevents previous alarms
                                 being wiped out in future tests.
   1.53     01-19-04  VSharma   Stored verify result in 'CurrentPreset.Verified' flag.
   1.54     02-02-04  VSharma   Added GetCurrentHwCnfg() & save its return value into battram
                                with the verified flag.
   1.55     04-06-04  VSharma   Added CheckForMultipleInput(), IsConfigured(), IsOutConfigured(),
                                 and CheckUserIOAlarm().
                                Recorded UserIO related Setup alarms in VerifyPreset().
   1.56     05-03-04  VSharma   Record SE295 in CheckUserIOAlarm().
   1.57     05-11-04  VSharma   Modified CheckForMultipleInput().
   1.58     05-17-04  VSharma   Modified condition for SE292 alarm.
   1.59     06-22-04  JOY       'Retval' is equated to proper Error code, when CheckUserIOAlarm() 
                                 is called in VerifyPreset().
   1.60     07-14-04  BEKymer   Changed all 2200w references to 200w.
   1.61     07-28-04  JOY       Added 60KHZ frequency in GetCurrentHwCnfg().
                                Recorded alarm SE296 in VerifyPreset().
   1.62     10-11-05  Bwadia    GetCurrentHwCnfg changed to accomodate PS wattage new
                                implementation
   1.63     03-30-07 YGupta     Moved VQS related setup alarms from vpreset5.c to VerifyPreset as
                                VerifyPresetModel5 function will call only for ControlLevel f.
   1.64     08-26-08 NHAhmed    Modified function CheckForMultipleInput() to correct Input Pin Conflict Alarm
   1.65     09-02-08 NHAhmed    CleanUp for multi-language support.
   1.66     10-20-08 NHAhmed    Replaced stroke length LENGTH_7 by LENGTH_2.
   1.67     09-10-09 BEkymer    Add new define MICRO where needed
	1.68     09-22-09 YGupta     Replaced AOS with MICRO Actuator type.
	1.69     06-08-10 PDwivedi   Modify GetCurrentHwCnfg function for standard MICRO.
   
 ----------------------------- DESCRIPTION -------------------------------*/




/* ------------------------------ INCLUDE FILES ----------------------------*/

#include <psos.h>
                /* for access to pSOS routines          */
#include "portable.h"
#include "ck_qsend.h"
#include "error.h"
#include "preset.h"
#include "param.h"
#include "limits.h"
#include "names.h"
#include "alarms.h"
#include "ready.h"
#include "weld_obj.h"
#include "wldstate.h"
#include "vpreset1.h"
#include "vpreset2.h"
#include "vpreset3.h"
#include "vpreset4.h"
#include "vpreset5.h"
#include "alsetup.h"
#include "graphs.h"
#include "statedrv.h"
#include "battram.h"
#include "menu3.h"
#include "menu4.h"
#include "menu.h"
#include "DUPS_api.h"
#include "menu7.h"
#include "menu7a.h"
#include "inports.h"
#include "outports.h"


/*------------------------------ WELD OBJECT DATA --------------------------*/

#define POWERMULTIPLIER        10 /* Multiply to get .1 resolution          */
#define POWERROUNDOFF           5 /* Subtract 1/2 of multiply to round off  */   
#define INPUT_COUNT             7

#define WELDMODES_1  (TIMEMODE | GRDDETECTMODE | CONTINUOUSMODE)
#define WELDMODES_2  (WELDMODES_1 | ENERGYMODE | PKPOWERMODE)
#define WELDMODES_3  (WELDMODES_2 | COLLAPSEMODE | ABSOLUTEMODE)
#define WELDMODES_4  (WELDMODES_3)
#define WELDMODES_5  (WELDMODES_4)
#define WELDMODES_6  (WELDMODES_5)
#define WELDMODES_7  (WELDMODES_6)

static UINT16 ControlLevelMask;
extern SETUPS_Ver800 RunningPreset;
extern SETUP_DATA_ALARMS SetupData;
SETUP_DATA_ALARMS *SetupDataPtr;
static START_WELD_MSG    StartWeldMsg;


extern CONFIGSETUP CurrentSetup;
extern UINT32 SysmQueueId, PrintQid;
extern UINT16 SetupAlarmFlag;
extern UINT8 AlarmDetectedFlag, SetupAlarmDetectedFlag;
extern BOOLEAN UlsTimeout;
extern BOOLEAN SVInterlockActive;

UINT16 PresetHasBeenOKed;
UINT16 VerifyPresetInProcess;

extern CONFIGSETUP CurrentSetup;
extern UINT16  PrintAnyway;
extern UINT16  PrintEveryCycleFlag;
extern UINT16  PrintIsOffline;    

/*------------------------- EXTERNAL FUNCTIONS -----------------------------*/

UINT32 GetCurrentHwCnfg (void);
UINT16 CheckUserIOAlarm (void);

UINT32 VerifyPreset(void)
/***************************************************************************/
/*                                                                         */
/*  This function will determine what control level is currently configured*/
/*  and will then call the proper VerifyPresetModel function.              */
/*                                                                         */
/*  The value returned will be FALSE if the preset is okay and can be run. */
/*  An error code will be returned if any problems are found.  The         */
/*  problems will be logged in PresetProblems array.  See Problems enum    */
/*  for list.                                                              */
/*                                                                         */
/***************************************************************************/
{
   UINT32 Retval = FALSE;
   UINT32 TempRetval;
   UINT16 PresetFailed = FALSE;        /* Start off assuming preset is okay */
   UINT16 *BattramIdPtr;  /* points to BATTRAM Init location for read/write */
   UINT16  DefaultSet;
   PRESET_COMPRESSED* CompressPreset;
// UINT16 TempVerified;

   VerifyPresetInProcess = TRUE;
   ClearSetupAlarms();

// TempVerified= (CurrentSetup.ControlLevel | (CurrentSetup.Actuator << 8));
// if (CurrentPreset.Verified ==  0) {
//    PresetHasBeenOKed = FALSE;           /* Is not verified */
// }
// else if (CurrentPreset.Verified != TempVerified) {
//    RecordSetupAlarm(SE268);         /* Was verified, but wrong control level or actuator */
//    RecordErrorCode(ERRORCODE8_SE268);
// }

/* Here check for things which are not actuator or control level dependent */

   if (CheckForDups())
      {
      if (DUPS_FindDUPS4COP(CurrentSetup.ActivePreset) == DUPS_PARAMSETUNDEF)
         {  //  no associated Parameter set means invalid preset
         Retval = SE268;
         RecordSetupAlarm(SE268);
         RecordErrorCode( ERRORCODE9_SE268 );
         }
      else if (DUPSChangePending == TRUE) {
            DUPS_DownloadCurrPS();
            DUPSChangePending = FALSE;
      }
   }

   switch (CurrentSetup.ControlLevel) {
        case LEVEL_a:
         ControlLevelMask = WELDMODES_3;
         TempRetval = VerifyPresetModel3();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode(TempRetval);
            RecordSetupAlarm(Retval);
         }
         if ( (CurrentSetup.Actuator == AEF) ||
              (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == MICRO) ) {
            PresetFailed = TRUE;
            RecordAlarm(EQ14);
         }
         break;

      case LEVEL_TEST:
      case LEVEL_f:
         ControlLevelMask = WELDMODES_5;
         TempRetval = VerifyPresetModel5();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode(TempRetval);
            RecordSetupAlarm(Retval);
         }
         break;

      case LEVEL_d:
         ControlLevelMask = WELDMODES_4;
         TempRetval = VerifyPresetModel4();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode(TempRetval);
            RecordSetupAlarm(Retval);
         }
         break;

      case LEVEL_ea:
         ControlLevelMask = WELDMODES_3;
         TempRetval = VerifyPresetModel3();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode(TempRetval);
            RecordSetupAlarm(Retval);
         }
         if ( (CurrentSetup.Actuator == AEF) ||
              (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == MICRO) ) {
            PresetFailed = TRUE;
            RecordAlarm(EQ14);
         }
         break;

      case LEVEL_e:
         ControlLevelMask = WELDMODES_2;
         TempRetval = VerifyPresetModel2();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode(TempRetval);
            RecordSetupAlarm(Retval);
         }
         if ( (CurrentSetup.Actuator == AEF) ||
              (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == MICRO) ) {
            PresetFailed = TRUE;
            RecordAlarm(EQ14);
         }
         break;

      case LEVEL_t:
         ControlLevelMask = WELDMODES_1;
         TempRetval = VerifyPresetModel1();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         TempRetval = CheckForStepping();
         if (TempRetval != FALSE) {
            Retval = SE268;
            PresetFailed = TRUE;
            RecordErrorCode(TempRetval);
            RecordSetupAlarm(Retval);
         }
         if ( (CurrentSetup.Actuator == AEF) ||
              (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == MICRO) ) {
            PresetFailed = TRUE;
            RecordAlarm(EQ14);
         }
         break;

      default:
         ControlLevelMask = WELDMODES_1;
         TempRetval = VerifyPresetModel1();
         if (TempRetval != 0) {
            Retval = TempRetval;
            PresetFailed = TRUE;
         }
         break;
   }

   switch (RunningPreset.WeldMode) {
      case TIMEMODE:
             break;

      case ENERGYMODE:
             break;

      case PKPOWERMODE:
             break;

      case COLLAPSEMODE:
             break;

      case ABSOLUTEMODE:
             break;

      case GRDDETECTMODE:
             break;

      case CONTINUOUSMODE:
             break;

      default:
             break;

   }

/*---  Make sure selected weld mode is valid for control level  ---*/

   if ((RunningPreset.WeldMode & ControlLevelMask) != RunningPreset.WeldMode) {
         RecordErrorCode( ERRORCODE4_SE268 );
         Retval = SE268;
      RecordSetupAlarm(Retval);
   }



/*--- Check for conflict of AE actuator and welding mode ---*/
   if((CurrentSetup.Actuator == AE) && (RunningPreset.WeldMode == COLLAPSEMODE || RunningPreset.WeldMode == ABSOLUTEMODE))
   {
      RecordErrorCode( ERRORCODE4_SE268 );
      Retval = SE268;
      RecordSetupAlarm(Retval);
   }      


/*--------------------------------------------------------------------------------*/
/*-- At this point check things like Advanced/Normal, Actuators, VQS alarms etc --*/
/*--------------------------------------------------------------------------------*/

/*---------------Weld Time +/- Limits Crossed -----------------*/

   if(((/*VQSWeldTimeMax.act*/DONTCARE & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSWeldTimeMax.CtrlLevel*/LEVEL_t <= CurrentSetup.ControlLevel)&&
      ((/*VQSWeldTimeMin.act*/DONTCARE & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSWeldTimeMin.CtrlLevel*/LEVEL_t <= CurrentSetup.ControlLevel)&&
      ((RunningPreset.VQSLimit & /*VQSWeldTimeMin.BitMask*/MTIMEBIT) == 0) &&
         ((RunningPreset.VQSLimit & /*VQSWeldTimeMax.BitMask*/PTIMEBIT) == 0) &&
         ((/*VQSWeldTimeMax.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*VQSWeldTimeMin.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      (RunningPreset.WeldTimeMaxVQS<=RunningPreset.WeldTimeMinVQS)){
      Retval = SE112;
      RecordSetupAlarm(Retval);
   }

   
/*--------------- Weld Energy +/- Limits Crossed --------------*/

   if(((/*VQSEnergyMax.act*/DONTCARE & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSEnergyMax.CtrlLevel*/LEVEL_ea <= CurrentSetup.ControlLevel)&&
      ((/*VQSEnergyMin.act*/DONTCARE & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSEnergyMin.CtrlLevel*/LEVEL_ea <= CurrentSetup.ControlLevel)&&
      ((RunningPreset.VQSLimit & /*VQSEnergyMin.BitMask*/MENERGYBIT) == 0) &&
         ((RunningPreset.VQSLimit & /*VQSEnergyMax.BitMask*/PENERGYBIT) == 0) &&
         ((/*VQSEnergyMax.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*VQSEnergyMin.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      (RunningPreset.EnergyMaxVQS<=RunningPreset.EnergyMinVQS)){
      Retval = SE113;
      RecordSetupAlarm(Retval);
   }

   
/*--------------- Peak Power +/- Limits Crossed --------------*/

   if(((/*VQSPeakPowerMax.act*/DONTCARE & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSPeakPowerMax.CtrlLevel*/LEVEL_ea <= CurrentSetup.ControlLevel)&&
      ((/*VQSPeakPowerMin.act*/DONTCARE & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSPeakPowerMin.CtrlLevel*/LEVEL_ea <= CurrentSetup.ControlLevel)&&
      ((RunningPreset.VQSLimit & /*VQSPeakPowerMin.BitMask*/MPKPOWERBIT) == 0) &&
         ((RunningPreset.VQSLimit & /*VQSPeakPowerMax.BitMask*/PPKPOWERBIT) == 0) &&
         ((/*VQSPeakPowerMax.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*VQSPeakPowerMin.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      (RunningPreset.PeakPowerMaxVQS<=RunningPreset.PeakPowerMinVQS)){
      Retval = SE114;
      RecordSetupAlarm(Retval);
   }
   
/*--------------- Total Abs +/- Limits Crossed --------------*/

   if(((/*VQSTotalAbsMax.act*/(AED|AOD|AEF|AOF|MICRO) & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSTotalAbsMax.CtrlLevel*/LEVEL_d <= CurrentSetup.ControlLevel)&&
      ((/*VQSTotalAbsMin.act*/(AED|AOD|AEF|AOF|MICRO) & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSTotalAbsMin.CtrlLevel*/LEVEL_d <= CurrentSetup.ControlLevel)&&
      ((RunningPreset.VQSLimit & /*VQSTotalAbsMin.BitMask*/MABSDISTBIT) == 0) &&
         ((RunningPreset.VQSLimit & /*VQSTotalAbsMax.BitMask*/PABSDISTBIT) == 0) &&
         ((/*VQSTotalAbsMax.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*VQSTotalAbsMin.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      (RunningPreset.TotalAbsMaxVQS<=RunningPreset.TotalAbsMinVQS)){
      Retval = SE115;
      RecordSetupAlarm(Retval);
   }

/*--------------- Total Cycle Time +/- Limits Crossed --------------*/

   if(((/*VQSTotalCycleTimeMax.act*/DONTCARE & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSTotalCycleTimeMax.CtrlLevel*/LEVEL_t <= CurrentSetup.ControlLevel)&&
      ((/*VQSTotalCycleTimeMin.act*/DONTCARE & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSTotalCycleTimeMin.CtrlLevel*/LEVEL_t <= CurrentSetup.ControlLevel)&&
      ((RunningPreset.VQSLimit & /*VQSTotalCycleTimeMin.BitMask*/MTOTCYCLETIMEBIT) == 0) &&
         ((RunningPreset.VQSLimit & /*VQSTotalCycleTimeMax.BitMask*/PTOTCYCLETIMEBIT) == 0) &&
         ((/*VQSTotalCycleTimeMax.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*VQSTotalCycleTimeMin.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      (RunningPreset.TotalCycleTimeMaxVQS<=RunningPreset.TotalCycleTimeMinVQS)){
      Retval = SE122;
      RecordSetupAlarm(Retval);
   }
/*--------------- Weld Collapse +/- Limits Crossed --------------*/

   if(((/*VQSWeldColMax.act*/(AED|AOD|AEF|AOF|MICRO) & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSWeldColMax.CtrlLevel*/LEVEL_d <= CurrentSetup.ControlLevel)&&
      ((/*VQSWeldColMin.act*/(AED|AOD|AEF|AOF|MICRO) & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSWeldColMin.CtrlLevel*/LEVEL_d <= CurrentSetup.ControlLevel)&&
      ((RunningPreset.VQSLimit & /*VQSWeldColMin.BitMask*/MWELDCOLLAPSEBIT) == 0) &&
         ((RunningPreset.VQSLimit & /*VQSWeldColMax.BitMask*/PWELDCOLLAPSEBIT) == 0)&&
         ((/*VQSWeldColMax.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*VQSWeldColMin.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      (RunningPreset.WeldColMaxVQS<=RunningPreset.WeldColMinVQS)){
      Retval = SE229;
      RecordSetupAlarm(Retval);
   }
/*--------------- Total Collapse +/- Limits Crossed --------------*/

   if(((/*VQSTotalColMax.act*/(AED|AOD|AEF|AOF|MICRO) & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSTotalColMax.CtrlLevel*/LEVEL_d <= CurrentSetup.ControlLevel)&&
      ((/*VQSTotalColMin.act*/(AED|AOD|AEF|AOF|MICRO) & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      ((/*VQSTotalColMin.CtrlLevel*/LEVEL_d <= CurrentSetup.ControlLevel)&&
      ((RunningPreset.VQSLimit & /*VQSTotalColMin.BitMask*/MCOLDISTBIT) == 0) &&
         ((RunningPreset.VQSLimit & /*VQSTotalColMax.BitMask*/PCOLDISTBIT) == 0)&&
         ((/*VQSTotalColMax.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (/*VQSTotalColMin.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      (RunningPreset.TotalColMaxVQS<=RunningPreset.TotalColMinVQS)){
      Retval = SE232;
      RecordSetupAlarm(Retval);
   }

/*--------------- Weld Force +/- Limits Crossed --------------*/

   if(((/*VQSWeldForceMax.act*/(AED|AOD|AEF|AOF|MICRO) & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSWeldForceMax.CtrlLevel*/LEVEL_d <= CurrentSetup.ControlLevel)&&
      ((/*VQSWeldForceMin.act*/(AED|AOD|AEF|AOF|MICRO) & CurrentSetup.Actuator) == CurrentSetup.Actuator)&&
      (/*VQSWeldForceMin.CtrlLevel*/LEVEL_d <= CurrentSetup.ControlLevel)&&
      ((RunningPreset.VQSLimit & /*VQSWeldForceMin.BitMask*/MFORCEBIT) == 0) &&
         ((RunningPreset.VQSLimit & /*VQSWeldForceMax.BitMask*/PFORCEBIT) == 0)&&
         ((/*VQSWeldForceMax.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*VQSWeldForceMin.mode */(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE)& RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      (RunningPreset.WeldForceMaxVQS<=RunningPreset.WeldForceMinVQS)){
      Retval = SE258;
      RecordSetupAlarm(Retval);
   }



/*--  Further refine this mask by checking for optional encoder  --*/

   if(CurrentSetup.Actuator == AE) {
      if (CheckForDistanceParameters() == TRUE) {
         PresetFailed = TRUE;
         Retval = SE259;
         RecordSetupAlarm(Retval);
      }
   }
   /* Checks for the User Configurable input/output related alarms.*/
   if(TempRetval = CheckUserIOAlarm ())
   {
      Retval = TempRetval;
      PresetFailed = TRUE;
   }
   /*If both the Pretrigger and External trigger delay are 
      selected, record the 'TrgDelayConflct' alarm.*/
   if((RunningPreset.PreTrigFlag == TRUE) && (RunningPreset.ExtTrgDelay == TRUE))
   {
      Retval = SE289;
      RecordSetupAlarm(Retval);
      PresetFailed = TRUE;
   }
   
   if((CurrentSetup.ControlLevel >= LEVEL_ea) && ((RunningPreset.Amp2Flag & BIT0) == BIT0) &&  /* If stepping on and */
      (CurrentSetup.AmpControl == TRUE) && (RunningPreset.Amp2Flag == AMP_STEP_AT_EXTERNAL) &&
      !IsConfigured(INPUT_EXT_TRIGGER))
   {
      Retval = SE296;
      RecordSetupAlarm(Retval);
      PresetFailed = TRUE;
   }
   
   if((CurrentSetup.ControlLevel >= LEVEL_ea) && ((RunningPreset.Force2Flag & BIT0) == BIT0) &&  /* If stepping on and */
      (RunningPreset.Force2Flag == FORCE_STEP_AT_EXTERNAL) &&
      !IsConfigured(INPUT_EXT_TRIGGER))
   {
      Retval = SE296;
      RecordSetupAlarm(Retval);
      PresetFailed = TRUE;
   }


         
   if (PresetFailed == TRUE) {
      SendSetupData();           /* Notify display system of impending doom */
      PresetHasBeenOKed = FALSE;
      AlarmDetectedFlag = TRUE;
      CountSetupAlarms();
      CurrentPreset.Verified = FALSE;
      RunningPreset.Verified = FALSE;
   }
   else {
     /*------------------------------------------------------*
      * Calculate IncrementPts (WeldTime+HoldTime+200)/400.  *
      * or (WeldTime+HoldTime+TriggerDelay+200)/400.         *
      *------------------------------------------------------*/
      GetPtsIncrement();

/*---   Here we need to modify power readings   ---*/

      RunningPreset.ForceTrigAmpValue *= POWERMULTIPLIER;
      RunningPreset.ForceTrigAmpValue -= POWERROUNDOFF;
      PresetHasBeenOKed = TRUE;
      AlarmDetectedFlag = FALSE;
      SetupAlarmFlag = FALSE;
      PushIndex();
      SelectWeldSequence();                      /* Create new weld sequence*/
      PopIndex();
      CurrentPreset.Verified = TRUE;
      RunningPreset.Verified = TRUE;
   }

   CurrentPreset.HwCnfg = GetCurrentHwCnfg();
   RunningPreset.HwCnfg = CurrentPreset.HwCnfg;
   /*Store the verified result in preset 0*/
   CompressPreset = (PRESET_COMPRESSED*) PRESET_0_START;
   CompressPreset->Verified = CurrentPreset.Verified;
   CompressPreset->HwCnfg = CurrentPreset.HwCnfg;
   if(CurrentPreset.PresetUpdateComplete == TRUE)
      WritePreset(CurrentSetup.ActivePreset);  /* Save Current Preset */

/*---   Now check the condition of the battery backed ram (BBR)   ---*/

  // BattramIdPtr =(UINT16 *)BATTRAM_INIT_ADDRESS;
  // DefaultSet = *BattramIdPtr;
  // if (DefaultSet != 0x5555) {
  //    CheckBattramDefaults();
  //    RecordAlarm(EQ8);              /* Let user know BBR was bad          */
  // }
  
   UlsTimeout = 0;               /* Reset ULS timer to start after verify   */
   VerifyPresetInProcess = FALSE;
   return(Retval);
}



UINT32 VerifyPresetModel1(void)
/****************************************************************************/
/*                                                                          */
/*  This function will verify the preset against itself and the system      */
/*  configuration.  It will check the following things:                     */
/*                                                                          */
/*    1) Only those things whic are unique to control model 1.              */
/*    2) After the preset is verified a state sequence will be generated    */
/*       to run the selected weld cycle.                                    */
/*                                                                          */
/*                                                                          */
/*  The value returned will be FALSE if the preset is okay and can be run.  */
/*  An error code will be returned if any problems are found.  The          */
/*  problems will be logged in PresetProblems array.  See Problems enum     */
/*  for list.                                                               */
/*                                                                          */
/****************************************************************************/
{
   UINT32 RetVal = FALSE;

/*--------------------------------------------------------------------------*/
/*----    Here check for things which are mode specific                 ----*/
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/*---  Here check for things which are not mode specific or not related  ---*/
/*---  to either suspect or reject limits.                               ---*/
/*--------------------------------------------------------------------------*/



/*---  Checking if the there is at least one item to print.         ---*/
/*---  If so, check if the printer is offline or disconnected.      ---*/
/*---  If the above is TRUE then clear the Record Alarm with reset. ---*/

   if(PrintEveryCycleFlag){
      if(PrintIsOffline){ 
        RetVal = SE270;
        RecordSetupAlarm(RetVal);
      }
   }




/*--------------------------------------------------------------------------*/
/*----    Finally check for things which are only allowed in            ----*/
/*----    control level 2 or above.                                     ----*/
/*----                                                                  ----*/
/*----    Remember, this function is called by ALL VerifyPreset levels. ----*/
/*----                                                                  ----*/
/*----                                                                  ----*/
/*--------------------------------------------------------------------------*/

   return(RetVal);
}



UINT16 CheckForDistanceParameters(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check all distance parameters and if any distance    */
/*  parameters are turned on a TRUE will be returned, otherwise a FALSE     */
/*  will be reutrned.                                                       */
/*                                                                          */
/****************************************************************************/
{
   UINT16 RetVal = FALSE;              /* Assume no distance stuff is on    */

   switch (RunningPreset.WeldMode) {
      case TIMEMODE:
      case ENERGYMODE:
      case PKPOWERMODE:
      case GRDDETECTMODE:
      case CONTINUOUSMODE:
             break;

      case COLLAPSEMODE:
      case ABSOLUTEMODE:
               RetVal = TRUE;
             break;
   }

/*--  Check for absolute distance cutoff (FALSE means option is on) --*/

   if (RunningPreset.ABSCutoffFlag == FALSE) RetVal = TRUE;


/*--  Check for collapse distance cutoff (FALSE means option is on)--*/

   if (RunningPreset.ColCutoffFlag == FALSE) RetVal = TRUE;


/*--  Check for pre-trigger distance  (FALSE means option is on)--*/

   if (RunningPreset.PreTrigDistFlag == FALSE) RetVal = TRUE;


/*--  Check for missing part distance (FALSE means option is off) --*/

   if (RunningPreset.MissingPartFlag == TRUE) RetVal = TRUE;


/*--  Check for actuator clear distance (FALSE means option is off) --*/

   if (RunningPreset.ActClrFlag == TRUE) RetVal = TRUE;


/*--  Check for rapid traverse distance (FALSE means option is off) --*/

   if (RunningPreset.RTFlag == TRUE) RetVal = TRUE;


/*--  Check for amplitude step on distance  --*/

   switch (RunningPreset.Amp2Flag) {
      case ((UINT16)~BIT2):                    /* Stepping enabled on time          */
         break;                       
                                      
      case ((UINT16)~BIT3):                    /* Stepping enabled on energy        */
         break;                       
                                      
      case ((UINT16)~BIT4):                    /* Stepping enabled on peak power    */
         break;                       
                                      
      case ((UINT16)~BIT5):                    /* Stepping enabled on absolute dist */
         RetVal = TRUE;               
         break;                       
                                      
      case ((UINT16)~BIT6):                    /* Stepping enabled on force         */
         break;                       
                                      
      case AMP_STEP_AT_EXTERNAL:                       /* Stepping enabled on external in   */
         break;

      default:
         break;
   }                                  
                                       

/*--  Check for force step on distance  --*/

   switch (RunningPreset.Force2Flag) {
      case ((UINT16)~BIT2):                    /* Stepping enabled on time          */
         break;                        
                                       
      case ((UINT16)~BIT3):                    /* Stepping enabled on energy        */
         break;                        
                                       
      case ((UINT16)~BIT4):                    /* Stepping enabled on peak power    */
         break;                        
                                       
      case ((UINT16)~BIT5):                    /* Stepping enabled on absolute dist */
         RetVal = TRUE;                
         break;                        
                                       
      case ((UINT16)~BIT6):                    /* Stepping enabled on amplitude     */
         break;                        
                                       
      case FORCE_STEP_AT_EXTERNAL:                       /* Stepping enabled on external in   */
         break;

      default:
         break;

   }                                   
   return(RetVal);
}



UINT32  CheckForStepping(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check for any stepping which might be enabled.  It   */
/*  will then check the control level and actuator type to see if stepping  */
/*  is allowed.  It will return an ERRORCODE if either stepping is turn on  */
/*  but is not allowed and FALSE if stepping is off or is allowed if it is  */
/*  on.                                                                     */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Retval = FALSE;

/**  First deal with amplitude stepping (its easier)  **/

   if ((RunningPreset.Amp2Flag & BIT0) == BIT0) {    /* Amp stepping on ?   */
      switch (CurrentSetup.ControlLevel) {           /* Yes it is           */
         case LEVEL_t:
         case LEVEL_e:
         case LEVEL_DEPOT:
            Retval = ERRORCODE2_SE268;                                 
            break;
         case LEVEL_a:
         case LEVEL_ea:
         case LEVEL_d:
         case LEVEL_f:
         case LEVEL_TEST:
            break;  
      }
   }

/**  Now deal with force stepping (its a pain)  **/

   if ((RunningPreset.Force2Flag & BIT0) == BIT0) {  /* Force stepping on ? */
      switch (CurrentSetup.ControlLevel) {           /* Yes it is           */
         case LEVEL_t:
         case LEVEL_e:
         case LEVEL_DEPOT:
         case LEVEL_a:
         case LEVEL_ea:
         case LEVEL_d:
            Retval = ERRORCODE3_SE268;                                 
            break;
         case LEVEL_f:
         case LEVEL_TEST:
            if ( (CurrentSetup.Actuator == AE) ||
                 (CurrentSetup.Actuator == AED) ||
                 (CurrentSetup.Actuator == MICRO) ) {
               Retval = ERRORCODE3_SE268;                                 
            }
            break;  
      }
   }
   return (Retval);
}



void SendSetupData(void)
/****************************************************************************/
/*                                                                          */
/*   This function will put the results of the verify preset into a struc-  */
/*   ture and then send a pointer to that structure to the system manager.  */
/*                                                                          */
/****************************************************************************/
{
   SetupDataPtr = &SetupData;
   StartWeldMsg.common.opcode = OP_SETUP_ALARM_DATA;
   StartWeldMsg.common.source_task = WC_ISR_TASK;
   
   StartWeldMsg.setup_data_ptr =  SetupDataPtr; // It was &SetupDataPtr; 
   
   StartWeldMsg.weld_samples = 1;
   CkQSend (SysmQueueId, &StartWeldMsg, WELD_MGR,
            __LINE__, MILLS_TO_TICKS(20));      /* 20 ms        */
}

UINT32 GetCurrentHwCnfg (void)
/****************************************************************************/
/*                                                                          */
/*   This function will used to get the value of current hardware config.   */
/*   This returns the value in decimal format depending on the Actuator type*/
/*   Control level, PS freq, PS Watt, Stroke Length and cylinder diameter.  */
/*   If any of these value is changed preset needs to be verified again.    */
/*                                                                          */
/****************************************************************************/
{
   UINT32 TempCnfg = 0;
   SINT32 Temp = 0;
   SINT32 x = 1000000;
   CONFIGSETUP *BBRPtr;


   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;

/**----------  Start of Actuator Type  ----------**/
      switch(BBRPtr->Actuator){        /* actuator type */
         case AE:             /* actuator = AE*/
            Temp = 1;
            break;
         case AO:             /* actuator = AO*/
            Temp = 2;
            break;
         case AED:             /* actuator = AED*/
            Temp = 3;
            break;
         case AOD:             /* actuator = AOD*/
            Temp = 4;
            break;
         case AES:             /* actuator = AES*/
            Temp = 5;
            break;
         case MICRO:             /* actuator = MICRO (Replaced AOS)*/
            Temp = 6;
            break;
         case AEF:             /* actuator = AEF*/
            Temp = 7;
            break;
         case AOF:             /* actuator = AOF*/
            Temp = 8;
            break;
         case HGUN:             /* actuator = HGUN*/
            Temp = 9;
            break;           
      }
   TempCnfg += Temp * x;
   x /= 10;
/**----------  Start of Stroke length  ----------**/

      switch(BBRPtr->StrokeLen){         /* stroke length */
         case CUSTOMLEN:           /* custom */
            Temp = 0;
            break;
         case LENGTH_4:           /* LENGTH_4 */
            Temp = 1;
            break;
         case LENGTH_5:           /* LENGTH_5 */
            Temp = 2;
            break;
         case LENGTH_6:           /* LENGTH_6 */
            Temp = 3;
            break;
         case LENGTH_2:           /* LENGTH_2 */
            Temp = 4;
            break;
        case LENGTH_8:           /* LENGTH_8 */
            Temp = 5;
            break;
         case LENGTH_80:           /* LENGTH_80 */
            Temp = 6;
            break;
         case LENGTH_100:           /* LENGTH_100 */
            Temp = 7;
            break;
         case LENGTH_125:           /* LENGTH_125 */
            Temp = 8;
            break;
         case LENGTH_50:           /* LENGTH_50 */
            Temp = 9;
            break;
        /* case LENGTH_160:           /* LENGTH_160 * /
            Temp = 9;
            break;*/
         
      }
 
   TempCnfg += Temp * x;
   x /= 10;
 
/**----------  Start of Cylinder diameter  ----------**/

      switch(BBRPtr->CylinDiameter){        /* cylinder diameter */
         case SIZE1_5:          /* 1.5" */
            Temp = 0;
            break;
         case SIZE2_0:           /*   2"*/
            Temp = 1;
            break;
         case SIZE2_5:           /* 2.5" */
            Temp = 2;
            break;
         case SIZE3_0:           /*   3" */
            Temp = 3;
            break;
         case SIZE3_25:          /* 3.25" */
            Temp = 4;
            break;
         case SIZE4_0:           /*  4"   */
            Temp = 5;
            break;
         case SIZE_40:           /*  40mm */
            Temp = 6;
            break;
         case SIZE_50:           /*  50mm */
            Temp = 7;
            break;
         case SIZE_63:           /*  63mm */
            Temp = 8;
            break;
         case SIZE_80:           /*  80mm */
            Temp = 9;
            break;
           
      }
   TempCnfg += Temp * x;
   x /= 10;

/**----------  Start of Control level  ----------**/

      switch(BBRPtr->ControlLevel){        /* control level */
         case LEVEL_DEPOT:           /* Depot */
            Temp = 1;
            break;
         case LEVEL_t:           /* LEVEL_t */
            Temp = 2;
            break;
         case LEVEL_e:           /* LEVEL_e */
            Temp = 3;
            break;
         case LEVEL_a:           /* LEVEL_a */
            Temp = 4;
            break;
         case LEVEL_ea:           /* LEVEL_ea */
            Temp = 5;
            break;
         case LEVEL_d:           /* LEVEL_d */
            Temp = 6;
            break;
         case LEVEL_f:           /* LEVEL_f */
            Temp = 7;
            break;
         case LEVEL_TEST:           /* LEVEL_TEST */
            Temp = 8;
            break;
      }

   TempCnfg += Temp * x;
   x /= 10;

/**----------  Start of Frequency  ----------**/

      switch(BBRPtr->PSFreq){        /* frequency */
         case FREQ15KHZ:           /* 15kHz */
            Temp = 1;
            break;
         case FREQ20KHZ:           /* 20kHz */
            Temp = 2;
            break;
         case FREQ30KHZ:           /* 30kHz */
            Temp = 3;
            break;
         case FREQ40KHZ:           /* 40kHz */
            Temp = 4;
            break;
         case FREQ50KHZ:           /* 50kHz */
            Temp = 5;
            break;
         case FREQ60KHZ:           /* 60kHz */
            Temp = 6;
            break;
      }
      
   TempCnfg += Temp * x;
   
/** --------------- Store PS Wattage divided / 100 as last two digits------**/   

   Temp = (BBRPtr->PSWatt) / 100;
   TempCnfg += Temp;
   
   return (TempCnfg);      
      
} 
  
BOOLEAN CheckForMultipleInput(void)
/*****************************************************************************/
/* Description :-                                                            */
/*   This function record the SE294 alarm if same input is configured to     */
/*   multiple pins.                                                          */
/*   Returns TRUE if same input is defined to more than one pin.             */
/*****************************************************************************/
{
   UINT8	x1, x2, Stop = 0, ExitFlag = FALSE;
   UINT16	UserCfgInput[INPUT_COUNT];
   BOOLEAN	RetVal = FALSE;

   /* If INPUT_DISABLED, then no need to check for 'Input Pin Conflict'. */

   if (CurrentSetup.J3_32In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_32In;
   if (CurrentSetup.J3_33In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_33In;
   if (CurrentSetup.J3_19In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_19In;
   if (CurrentSetup.J3_17In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_17In;
   if (CurrentSetup.J3_31In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_31In;
   if (CurrentSetup.J3_1In != INPUT_DISABLED)
      UserCfgInput[++Stop] = CurrentSetup.J3_1In;

   if (Stop > 1) {	/* Only check if Input are not disabled. */
		x1 = 1;
		x2 = 2;
		while (ExitFlag == FALSE) {
		    /* Check if both are equal.*/
			if (UserCfgInput[x1] == UserCfgInput[x2] ) {
				RecordSetupAlarm(SE294);
				RetVal = TRUE;
				ExitFlag = TRUE;
			}
			else if (++x2 > Stop) {
				if (x1 < (Stop - 1)) {
					x1++;
					x2 = x1+1;
				}
				else /* All the inputs are checked.Get out of while loop.*/
				   ExitFlag = TRUE;
			}
		}
   }
   return (RetVal);
}



BOOLEAN IsConfigured (UINT16 SelectedInput)
/*****************************************************************************/
/* Description :-                                                            */
/*   This function returns TRUE if the Selected input is configured to any   */
/*   of the input pin in User I/O menu.                                      */
/*****************************************************************************/
{
   BOOLEAN RetValue;
   /* If input is configured to any of the port pin. */
   if(SelectedInput == CurrentSetup.J3_32In ||
      SelectedInput == CurrentSetup.J3_33In ||
      SelectedInput == CurrentSetup.J3_19In ||
      SelectedInput == CurrentSetup.J3_17In ||
      SelectedInput == CurrentSetup.J3_31In ||
      SelectedInput == CurrentSetup.J3_1In )
      RetValue = TRUE;
   else
      RetValue = FALSE;
   
   return (RetValue);
}

BOOLEAN IsOutConfigured (UINT16 SelectedOutput)
/*****************************************************************************/
/* Description :-                                                            */
/*   This function returns TRUE if the Selected output is configured to any  */
/*   of the output pin in User I/O menu.                                     */
/*****************************************************************************/
{
   BOOLEAN RetValue;
   /* If input is configured to any of the port pin. */
   if(SelectedOutput == CurrentSetup.J3_36Out ||
      SelectedOutput == CurrentSetup.J3_8Out  ||
      SelectedOutput == CurrentSetup.J3_22Out )
      RetValue = TRUE;
   else
      RetValue = FALSE;
   
   return (RetValue);
}

UINT16 CheckUserIOAlarm (void)
/*****************************************************************************/
/* Description :-                                                            */
/*   This function Checks and record the alarms from SE290 to SE294.         */
/*****************************************************************************/
{
   UINT32 RetVal = FALSE;
   
         
   if(RunningPreset.ExtTrgDelay == TRUE && !IsConfigured(INPUT_EXT_TRIGDELAY))
   {/*Record TrgDelayConflict alarm*/
      RetVal = SE290;
      RecordSetupAlarm(RetVal);
   }
   /* Make 'Inp.SVInterlock' TRUE between WaitSVST & Hold state when both the pins are 
      not defined.  */   
   if(!IsConfigured(INPUT_SV_INTERLOCK) && !IsOutConfigured(OUTPUT_SV_INTERLOCK))
      SVInterlockActive = FALSE;
   else if(IsConfigured(INPUT_SV_INTERLOCK) && IsOutConfigured(OUTPUT_SV_INTERLOCK))
      SVInterlockActive = TRUE;
   else /* one of the pin (SVInterlock input and output) is not defined.*/  
   {    /* Record SVInterlockSetup alarm*/
      RetVal = SE291;
      RecordSetupAlarm(RetVal);
   }
      
   /* Record Missing Part Conflict alarm */
   if ( (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) ) {
       if (IsOutConfigured(OUTPUT_MISSING_PART) && ((RunningPreset.CycleAbortFlag == FALSE) ||
          (RunningPreset.MissingPartFlag == FALSE) || ( RunningPreset.MissingMinFlag &&
           RunningPreset.MissingMaxFlag) ))
       {
           RetVal = SE292;
           RecordSetupAlarm(RetVal);
       }
   }  
     
   /* Record Energy Braking Setup alarm .*/
   if(RunningPreset.EnergyBraking == TRUE && CurrentSetup.AmpControl == FALSE)
   {
      RetVal = SE293;
      RecordSetupAlarm(RetVal);
   }
   /* If Same input configured to multiple pins.*/
   if (CheckForMultipleInput())
      RetVal = SE294;

   if((IsConfigured(INPUT_SYNC_IN) ^ IsOutConfigured(OUTPUT_SYNC_OUT)) )
   {    /* Record alarm*/
      RetVal = SE295;
      RecordSetupAlarm(RetVal);
   }
   
   return(RetVal);
}






