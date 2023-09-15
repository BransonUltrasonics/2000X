/* $Header:   D:/databases/VMdb/2000Series/App/rdyweld1.c_v   1.15.1.0   26 Oct 2013 11:39:08   gbutron  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 

/* ---------------------------- MODULE DESCRIPTION ---------------------------

This module contains the ready, weld, hold and afterburst functions for single
start cycle conditions like handheld where they are different from normal two
start switch start.  This start condition can be one palm button, trigger
switch or external input.  The input conditioning is handled somewhere else.
Inp.SingleStart will have which ever start condition is defined.   These files
replace similiarly named files (without the 'HH') in either ready.c or 
weldhold.c.

 Name: Rdyweld1.c

 -------------------------------- REVISIONS ----------------------------------

 Rev #     Date     Author    Description
 =====     ======== =======   ===========                              
 1.0       3/29/01  DJL       Initial   
 1.1       04-11-01 BEKymer   Add some real code for handheld
 1.2       05-02-01 BEKymer   Debugging changes, cleanup in CheckSonicsHH, etc.
 1.3       05-03-01 BEKymer   Added check for trigger lost in CheckSonics1HH
 1.4       05-08-01 LAM       Need to wait for PresetHasBeenOKed in the PBState
 1.5       05-08-01 BEKymer   Fudged the max time out timer to eliminate 16 ms difference
 1.6       05-09-01 BEKymer   Added new function (AlStopHH) so correct timer is stopped
 1.7       08-27-03 BEKymer   Update SWConfiguration in DealWithHandHeldChange()
 1.8       02-20-04 VSharma   Modified HHBeep().
 1.9       03-12-04 VSharma   Changed 'Inp.ECycleAbort' to ECycleHistFlag.
 1.11      04-06-04 VSharma   Modified HHBeep().
 1.12      09-14-04 JOY       Updated CurrentPreset.Verified flag in DealWithHandheldChange().
 1.13      10-05-07 BEKymer   Calculate Energy units in StartNonTimeHH
 1.14      09-02-08 NHahmed   CleanUp for multi-language support.
 1.15      03-08-11 PDwivedi  Added changes for USB Full alarm.   
 1.15.1.0  10-26-13 GButron   StartSonic1HH() function was divided into two.
                              StartNonTimeHH() function was divided into two.
                              StartSonic1HH_1msec_Later() and StartNonTimeHH_1msec_Later() were added.
                              Because of this, Offset and Sonic signals are applied in Different states.
                              Offset was removed from StopAllSonicHH() and AlStopHH()
                          

----------------------------------------------------------------------------*/
                                                                                                                                                                                                                                                            
  

/*---------------------------- LOCAL_EQUATES -------------------------------*/


/*------------------------------ INCLUDES ----------------------------------*/

#include <psos.h>                /* psos defines and prototypes, etc,.  */
#include "state.h"
#include "preset.h"
#include "beep.h"
#include "weld_obj.h"
#include "alarms.h"
#include "weldhold.h"
#include "menu4.h"
#include "alsetup.h"
#include "graphs.h"
#include "ready.h"
#include "digout.h"
#include "mansensr.h"
#include "timer.h"
#include "rdyweld1.h"

/*----------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                       (scope is global to THIS file)                     */

static UINT16  HHDelayStartFlag = TRUE;
static SINT16  HHSonicTimer;
static SINT16  HHSonicStepTimer;
static SINT16  HHSeekDelay;
static BOOLEAN HHScrubTimerFlag;
static SINT16  HHScrubTimer;


BOOLEAN Flag_Start_Sonic1HH = FALSE;   
BOOLEAN Flag_Start_NonTimeHH = FALSE; 
UINT16 Two_Msec = 0;

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/



/*------------------------------ EXTERNAL DATA -----------------------------*/

extern UINT16 PrinterTotalCount;
extern UINT16 PBExitTimer;
extern UINT16 ExternalCycleAbortGoneFlag;
extern UINT16 PrinterCopyPts;
extern UINT16 PrinterCheckTimer;
extern UINT16 OkToDisplayAlarms;      /* TRUE:cycle is complete, display ok */
extern UINT16 JustPoweredUpTimer;
extern UINT16 Update5ms;
extern SINT16 PeakPower;
extern UINT16 ActualABDelay;
extern UINT16 PresetNeedsToBeUpdated;
extern UINT16 PresetHasBeenOKed;
extern SINT32 CurrentFreqIn;          /* Value being read by 7890          */
extern UINT32 CurrentPowerIn;         /* Value being read by 7890          */
extern UINT32 CurrentAmpIn;
extern SINT32 *A_Setup;
extern SINT32 *B_Setup;
extern SINT32 *LastA;
extern SINT32 *LastB;
extern SINT32 AccumulatedEnergy, EnergyCalc;
extern SINT32 ActualAfterburstTime;
extern SINT32 ABOverloadPower;
extern SINT32 ActualSeekTime;
extern SINT32 EnergyNeeded;
extern SINT32 TriggerLostTime;

extern DFLOAT PrinterIncPoints;
extern DFLOAT PrinterNewInc;
extern BOOLEAN ECycleHistFlag;
extern BOOLEAN JustPoweredUpFlag;
extern BOOLEAN PoweredUp;
extern BOOLEAN AmpStepReachedFlag;
extern BOOLEAN TriggerLostFlag;
extern BOOLEAN ReadyFlag;
extern BOOLEAN SeekEndFlag;
extern BOOLEAN GroundDetectFlag;

extern WELD_OBJECT *MsDataPtr;
extern SETUPS_Ver800  RunningPreset;
extern CONFIGSETUP CurrentSetup;
extern enum ERRORCODE_ARG ErrorCode;
extern INBITS Inp;
extern WELD_DATA WeldingResults;
extern UINT8 CollectEnergyFlag;
/*-------------------------------- CODE ------------------------------------*/



void DealWithHandHeldChange(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed when handheld is turned on or off in the*/
/*  menu (menu7.c TOGGLE Handheld).   It will set PresetNeedsToBeUpdated   */
/*  to force a verify and to load the proper state sequence.               */
/*                                                                         */
/***************************************************************************/
{
   PresetNeedsToBeUpdated = TRUE;   /* Force verify and new state sequence */
   PresetHasBeenOKed = FALSE;
   CurrentPreset.Verified = FALSE;
   if (CurrentSetup.HandHeld == TRUE)
      UpdateSWConfiguration(HH, TRUE);  /* Handheld enabled */
   else
      UpdateSWConfiguration(HH, FALSE); /* Handheld disabled */
   
}



void TestPBHH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when one start signal is    */
/*  received.  It will check to see if the preset needs to be verified     */
/*  before the sonics are turned on.                                       */
/*                                                                         */
/***************************************************************************/
{
  
   if (PresetHasBeenOKed == TRUE) {
      if (ReadyFlag == TRUE) ClearReady();   /* Remove Welder Ready signal */
         OKToAdvance = TRUE;
         ClearSetupAlarms();      /* This will clear Printer Offline alarm */
         ClearFinalResults();
   }
}



void ExitPBHH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when a single start is      */
/*  received.                                                              */
/*                                                                         */
/***************************************************************************/
{
   if (PrinterTotalCount == 0) GetPtsIncrement();
   MsDataPtr->TotalPts = PrinterTotalCount;
   MsDataPtr->IncrementPts = PrinterIncPoints;
   MsDataPtr->CopyPts = PrinterCopyPts;
   MsDataPtr->NewInc = PrinterNewInc;

   SetCurrentAmp(RunningPreset.Amp1);   /* Prepare P/S for 1st amplitude   */

/* Here decide if extra cooling is needed  */

   if (CurrentSetup.ExtraCooling == TRUE) CoolValOn();

   OKToAdvance = FALSE;
   ErrorCodeFlag = FALSE;
   ErrorCode = 0;
}



void TestPreReadyHH(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called whenever we are checking to see if we can      */
/*  enter the ready state.  It will clear the ECycleAbort flag if the      */
/*  ExternalCycleAbortGoneFlag is TRUE (which is set in Inports.c).        */
/*                                                                         */
/*  The JustPoweredUpFlag delays the Ready signal until we think the front */
/*  panel has displayed the Run screen.                                    */
/*                                                                         */
/***************************************************************************/
{
   if (Inp.SingleStart == TRUE) {
      PBExitTimer++;                   /* Count time until pb's released   */
      if (PBExitTimer > PBEXITTIME) {
         PBExitFlag = TRUE;            /* Took too long, generate alarm    */
      }
   }
   else
      PBExitFlag = FALSE;             /* clear alarm in case it was set    */

   if (ExternalCycleAbortGoneFlag == TRUE) {
      ECycleHistFlag = FALSE;    /* Clear external cycle abort in case it got set */
   }
   if (JustPoweredUpFlag == TRUE) {
      if (JustPoweredUpTimer >= POWERUPREADYDELAY) {

         if((WeldingResults.EquipmentFailureAlarms & WRONG_ACTUATOR_FAIL) !=
            WRONG_ACTUATOR_FAIL){
               PoweredUp = TRUE;
               JustPoweredUpFlag = FALSE;
               
            }   
      }
      else {
         JustPoweredUpTimer++;
      }
   }
   if ( (++PrinterCheckTimer >= PRINTERCHECKTIME) &&
        (CheckPrintingStatus() == TRUE) ) {
      PrinterCheckTimer = 0;                /* Reset timer */
      if (OfflineCheckFunc() == TRUE) {
         RecordSetupAlarm(SE270);
      }
   }
   if(USBFullCheckFunc() == TRUE)
      RecordAlarm(EQ13);
   if (CheckIfResetRequired() == FALSE) AlarmsReset = TRUE;
   if (IsDUPSDataCollectionComplete() == FALSE) {
      DUPSOkFlag = FALSE;             /* FALSE:waiting for DUPS data */
   }
   else {
      DUPSOkFlag = TRUE;              /* TRUE:not waiting for DUPS data */
   }
   OkToDisplayAlarms=TRUE;    /* At this point allow alarms to be displayed */
}



void StartSonic1HH(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will deal with turning on the sonics for      */
/*  single start cycles.  Two conditions can exist: 1) Amplitude step       */
/*  is enabled or 2) Amplitude step is disabled.                            */
/*                                                                          */
/*  Amplitude step enabled:  HHSonicStepTimer=timer id for time of step one */
/*                           HHSonicTimer=timer id for total sonics on time */
/*                                                                          */
/*  Amplitude step disabled: HHSonicStepTimer=timer id total sonics on time */
/*                           HHSonicTimer=timer id for total sonics on time */
/*                                                                          */
/****************************************************************************/
{

   CollectEnergyFlag = TRUE;
   HHDelayStartFlag = TRUE;
   CoolValOn();   

/*----- Deal with the new cycle trigger stuff -----*/
/* Enable frequency offset */
   if(RunningPreset.FreqOffsetFlag == TRUE){
      SetCurrentFreqOffset(RunningPreset.FreqOffset);
   }

   Flag_Start_Sonic1HH = TRUE; 
   Two_Msec = 0;  
}




/*****************************************************************************/
/*                                                                           */
/*      This is the function that will deal with turning on the Sonics       */
/*                      once the offset was applied                          */
/*                          Hand Held mode only                              */
/*                                                                           */
/*****************************************************************************/

void StartSonic1HH_1msec_Later(void)
{
   UINT16  FirstTimeValue;

   StartUpTimer(SONICSTIMER);
   WeldingResults.ActualFreqStart = CurrentFreqIn;                                       /* Get starting frequency      */
   CheckFrequencyLimits();
   PeakPower = 0;                                                                        /* Reset last peak power       */
   SetCurrentAmp(RunningPreset.Amp1);                                                    /* Initial amplitude           */
   PSRun();                                                                              /* Start sonics                */

/**  ** This timer is the total length of time Sonics are on  **  **/

    FirstTimeValue = RunningPreset.WeldTime; /* Control limits off so no Energy Comp */

/* ---- Deal with amplitude stepping (Consider Energy Comp)  ----*/

   if (RunningPreset.ControlLimitsFlag == TRUE) {
      if (RunningPreset.EnergyCompFlag == TRUE) {
         FirstTimeValue = ((RunningPreset.WeldTime) + ((RunningPreset.WeldTime ) >> 1)); /* Assume Step is off, Energy Comp is ON */
         if (FirstTimeValue >= MAXWELDTIME + 1) FirstTimeValue=MAXWELDTIME; 
      }
      else {
         FirstTimeValue = RunningPreset.WeldTime;                                        /* Assume Step is off, Energy Comp is off */
      }
   }
   HHSonicTimer = StartTimer(FirstTimeValue, &WTimeFlag, 7);
   if (HHSonicTimer == FAILED1) {
      LogError(TIMERFAILED1);
      HHSonicTimer = 0;
   }
   else if (HHSonicTimer == FAILED2) {
      LogError(TIMERFAILED2);
      HHSonicTimer = 0;
   }
   AmpStepReachedFlag = FALSE;
    if ((RunningPreset.Amp2Flag & BIT0) == BIT0) {                                       /* See if amplitude step is on       */
      switch (RunningPreset.Amp2Flag) {
         case ((UINT16)~BIT2):                                                           /* Stepping enabled on time          */
            FirstTimeValue = (RunningPreset.AmpTrigTimeValue);                           /* Step is on                        */
            break;

         case ((UINT16)~BIT3):                                                           /* Stepping enabled on energy        */
         case ((UINT16)~BIT4):                                                           /* Stepping enabled on peak power    */
         case ((UINT16)~BIT5):                                                           /* Stepping enabled on collapse dist */
         case ((UINT16)~BIT6):                                                           /* Stepping enabled on amplitude     */
         case AMP_STEP_AT_EXTERNAL:                                                      /* Stepping enabled on external in   */
         default:
            break;
      }
   }

/**  ** This timer is the length of time for Sonic1 state  **  **/

   HHSonicStepTimer = StartTimer(FirstTimeValue, &StepTimeFlag, 17);
   if (HHSonicStepTimer == FAILED1) {
      LogError(TIMERFAILED1);
      HHSonicStepTimer = 0;
   }
   else if (HHSonicStepTimer == FAILED2) {
      LogError(TIMERFAILED2);
      HHSonicStepTimer = 0;
   }
}




void CheckSonics1HH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to sonic state 2.  This function is used for all weld   */
/*  modes.                                                                 */
/*                                                                         */
/***************************************************************************/
{
   if (HHDelayStartFlag == TRUE){
      HHDelayStartFlag = FALSE;
      SetSAS();
   }
   if (Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimits();
   CheckForForceStepping();      /*---Also check for amplitude stepping----*/
   TriggerLostFlag = CheckForTriggerLost();
}



void StartNonTimeHH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with turning on the sonics for     */
/*  the first weld pressure.  Two conditions can exist: 1) Amplitude step  */
/*  is enabled or 2) Amplitude step is disabled.                           */
/*                                                                         */
/*  Amplitude step enabled:  SonicStepTimer=timer id for time of step one  */
/*                           SonicTimer=timer id for total sonics on time  */
/*                                                                         */
/*  Amplitude step disabled: SonicStepTimer=timer id total sonics on time  */
/*                           SonicTimer=timer id for total sonics on time  */
/*                                                                         */
/*  NOTES: 1) ENERGY MODE, PEAK POWER MODE &  GROUND DETECT ONLY           */
/*         2) 100 ms is added to the maxtimeout timer.  This is to resolve */
/*            a problem encountered when both handheld and external presets*/
/*            are selected.  In interest of time (schedule) time is added  */
/*            to maxtimeout so this timer does not expire.  Max timeout is */
/*            checked in CheckForControlLimits() and the max timeout alarm */
/*            will be generated there.  The problem to be solved was a time*/
/*            difference between the final weld time and the set max time  */
/*            (a difference of roughly 12-18 ms).                          */
/*                                                                         */
/***************************************************************************/
{
   if (RunningPreset.WeldMode == ENERGYMODE) {
      EnergyCalc = (100000 / CurrentSetup.PSWatt);
      if (RunningPreset.WeldEnergy >= 2000) {                            /* Prevent overflow, lose a little accuracy            */
         EnergyNeeded = RunningPreset.WeldEnergy * EnergyCalc;           /* Convert to energy units                             */
      }
      else {                                                             /* Overflow not a problem here, keep accuracy instead  */
         EnergyNeeded = RunningPreset.WeldEnergy * 100000;               /* 1/10's of millejoules                               */
         EnergyNeeded /= CurrentSetup.PSWatt;                            /* Convert to energy units                             */
      }
   }   
   CollectEnergyFlag = TRUE;
   HHDelayStartFlag = TRUE;
   CoolValOn();

/*----- Deal with the new cycle trigger stuff -----*/
/* Enable frequency offset */
   if(RunningPreset.FreqOffsetFlag == TRUE){
      SetCurrentFreqOffset(RunningPreset.FreqOffset);
   }

   Flag_Start_NonTimeHH = TRUE; 
   Two_Msec = 0;  
}



/*****************************************************************************/
/*                                                                           */
/*      This is the function that will deal with turning on the Sonics       */
/*                      once the offset was applied                          */
/*                          Hand Held mode only                              */
/*                                                                           */
/*****************************************************************************/

void StartNonTimeHH_1msec_Later(void)
{
   UINT16  FirstTimeValue;

   GroundDetectFlag = FALSE;
   HHScrubTimerFlag = FALSE;
   StartUpTimer(SONICSTIMER);
   WeldingResults.ActualFreqStart = CurrentFreqIn;                                   /* Get starting frequency       */
   CheckFrequencyLimits();
   PeakPower = 0;                                                                    /* Reset last peak power        */

   SetCurrentAmp(RunningPreset.Amp1);                                                /* Initial amplitude            */
   PSRun();                                                                          /* Start sonics                 */
   
   if ((/*MaxTimeout.mode*/(ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE |GRDDETECTMODE) & RunningPreset.WeldMode) ==   /* If weld mode allows        */
         RunningPreset.WeldMode) {                                                   /* timeout, then and only then  */
      FirstTimeValue = (RunningPreset.MaxTimeout + 100);                             /* use user supplied value      */
   }
   else {
      FirstTimeValue = (DEFAULT_MAXTIMEOUT + 100);
   }
   
/**  ** This timer is the total length of time Sonics are on  **  **/

   HHSonicTimer = StartTimer(FirstTimeValue, &WTimeFlag, 7);
   if (HHSonicTimer == FAILED1) {
      LogError(TIMERFAILED1);
      HHSonicTimer = 0;
   }
   else if (HHSonicTimer == FAILED2) {
      LogError(TIMERFAILED2);
      HHSonicTimer = 0;
   }
   AmpStepReachedFlag = FALSE;
   
   if ((RunningPreset.Amp2Flag & BIT0) == BIT0) {                                    /* See if amplitude step is on       */
      switch (RunningPreset.Amp2Flag) {
         case ((UINT16)~BIT2):                                                       /* Stepping enabled on time          */
            FirstTimeValue = (RunningPreset.AmpTrigTimeValue);                       /* Step is on                        */
            break;
   
         case ((UINT16)~BIT3):                                                       /* Stepping enabled on energy        */
         case ((UINT16)~BIT4):                                                       /* Stepping enabled on peak power    */
         case ((UINT16)~BIT5):                                                       /* Stepping enabled on absolute dist */
         case ((UINT16)~BIT6):                                                       /* Stepping enabled on amplitude     */
         case AMP_STEP_AT_EXTERNAL:                                                  /* Stepping enabled on external in   */
         default:
            break;
     }
   }
   
/**  ** This timer is the length of time for Sonic1 state  **  **/

   HHSonicStepTimer = StartTimer(FirstTimeValue, &StepTimeFlag, 17);
   if (HHSonicStepTimer == FAILED1) {
      LogError(TIMERFAILED1);
      HHSonicStepTimer = 0;
   }
   else if (HHSonicStepTimer == FAILED2) {
      LogError(TIMERFAILED2);
      HHSonicStepTimer = 0;
   }
}




void CheckEnergyHH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state 2 (ENERGY MODE only).               */
/*                                                                         */
/***************************************************************************/
{
   CheckSonics1HH();              /* Monitor all common functions          */
   if (AccumulatedEnergy >= EnergyNeeded) {
      SonicsAbort = TRUE;         /* Stop sonics, energy value reached     */
   }
}



void CheckPPHH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state 2 (PEAK POWER MODE only).           */
/*                                                                         */
/***************************************************************************/
{
   CheckSonics1HH();              /* Monitor all common functions          */
   if (PeakPower >= RunningPreset.PeakPwr) {
      SonicsAbort = TRUE;         /* Stop sonics, peak power value reached */
   }
}



void CheckGdDetHH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to ground detect 2 (after amplitude stepping) (GROUND   */
/*  DETECT mode only).                                                     */
/*                                                                         */
/***************************************************************************/
{
   CheckSonics1HH();              /* Monitor all common functions          */
   if (Inp.GndDet == TRUE) {
      if (GroundDetectFlag == FALSE) {
         GroundDetectFlag = TRUE;
         if ((RunningPreset.ScrubTime     != 0) &&
              (RunningPreset.ScrubTimeFlag == 0)) //Scrub Time(s) isn't Off
         {
            HHScrubTimer = StartTimer(RunningPreset.ScrubTime,
                                    &HHScrubTimerFlag, 60);
         }
      }
      else if (HHScrubTimerFlag == FALSE) {
         SonicsAbort = TRUE;         /* Stop sonics, ground detect is active*/
      }
   }
   else if (GroundDetectFlag == TRUE) { /* Had Grd Detect, but lost it, check anyway */
      if (HHScrubTimerFlag == FALSE) {
         SonicsAbort = TRUE;         /* Stop sonics, ground detect is active*/
      }
   }   
}



void StopSonic2HH(void)
/***************************************************************************/
/*                                                                         */
/*  This replaces the original StopSonic2HH function which has been renamed*/
/*  to StopAllSonicHH().  This function will determine if energy braking   */
/*  is on.  If braking is not on then StopAllSonicHH() is called and       */
/*  everything is as it was.  If energy braking is on then this function   */
/*  exits and does nothing.  The energy braking state (which is then next) */
/*  will call StopAllSonicHH() after the proper amp ramp has outputted.    */
/*                                                                         */
/***************************************************************************/
{
   if (RunningPreset.EnergyBraking == FALSE)  /* Not on, proceed as before */
      StopAllSonicHH();
}



void StopAllSonicHH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with turning off the sonics.       */
/*                                                                         */
/***************************************************************************/
{
   UINT16  FirstTimeValue;

   PSIdle();                                /* Stop sonics                 */
   ClearSAS();                              /* Remove Sonics Active signal */
 
   CollectEnergyFlag = FALSE;
   if(AmpStepReachedFlag == FALSE)
      WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
   else {
      WeldingResults.ActualAmplitudeEnd = ((CurrentAmpIn + 5) / POWERDIV);
      MsDataPtr->PrintBottomFlags &= (~AMPSTEPALARMMASK); /* Amp step reached, so remove alarm flag */
   }

   if ((WeldingResults.PSActControlFlags & BIT0) == BIT0) {  /* If internal amp control only */
      *LastA = *A_Setup;
      *LastB = *B_Setup;
   }
   else {
      *LastA = 0;
      *LastB = 0;
   }

   WeldingResults.PeakPower = (PeakPower);
   /* SetCurrentFreqOffset(0); */    /* clear frequency offset  */                            
   if (WTimeFlag == TRUE) {
      StopTimer(HHSonicTimer);
   }

/*--------------------------------------------------------------------------*/
/* The following approach will be used to determine if the actual weld time */
/* should be reported or if the requested weld time will be used instead.   */
/*                                                                          */
/*     If trigger has been reached, (it must have been reached or we would  */
/*     not be here, right!), (SonicsAbort == TRUE or CycleAbort == TRUE)    */
/*     then use actual time.  If (SonicsAbort == FALSE and CycleAbort       */
/*     == FALSE) then use the requested time.  If energy comp is turned     */
/*     on and time is extended use actual time.  If time is not extended    */
/*     then use the requested time.                                         */
/*                                                                          */
/*     Note: We need to CheckEnergyComp() first because this is what will   */
/*     create the W7 alarm which we want to check in TIMEMODE.  We get the  */
/*     actual time before we call CheckEnergyComp() because it needs the    */
/*     time to decide if time was actually extended.                        */
/*                                                                          */
/*--------------------------------------------------------------------------*/

   if (AccumulatedEnergy > 20000) {
      WeldingResults.TotalEnergy = (AccumulatedEnergy / (100000 / CurrentSetup.PSWatt));
   }
   else {
      WeldingResults.TotalEnergy = (AccumulatedEnergy * CurrentSetup.PSWatt) / 100000;
   }
   WeldingResults.ActualWeldTime = GetUpTimer(SONICSTIMER);
   CheckEnergyComp();

   switch (RunningPreset.WeldMode) {
      case TIMEMODE:               /* TIME mode only           */
         FirstTimeValue = ((RunningPreset.WeldTime) + ((RunningPreset.WeldTime ) >> 1)); /* Energy Comp ON, time extended */
         if (FirstTimeValue >= MAXWELDTIME) {
            FirstTimeValue = MAXWELDTIME;
         }

         if ( (SonicsAbort == TRUE) || (CycleAbort == TRUE) ) {
            WeldingResults.ActualWeldTime = GetUpTimer(SONICSTIMER);
            if ((WeldingResults.ActualWeldTime - 1) == RunningPreset.WeldTime) {
               WeldingResults.ActualWeldTime = RunningPreset.WeldTime;
            }
            if ((WeldingResults.ActualWeldTime + 1) >= FirstTimeValue) {
               WeldingResults.ActualWeldTime = FirstTimeValue;
            }
         }
         else if ( (RunningPreset.ControlLimitsFlag == FALSE) ||
                   (RunningPreset.EnergyCompFlag == FALSE) ) {
            WeldingResults.ActualWeldTime = RunningPreset.WeldTime;
         }
         else if ((WeldingResults.Warnings & W7) == (W7 & ALARMCODEMASK)) {
            WeldingResults.ActualWeldTime = GetUpTimer(SONICSTIMER);
            if ((WeldingResults.ActualWeldTime - 1) >= FirstTimeValue) {
               WeldingResults.ActualWeldTime = FirstTimeValue;
            }
            if ((WeldingResults.ActualWeldTime + 1) >= FirstTimeValue) {
               WeldingResults.ActualWeldTime = FirstTimeValue;
            }
         }
         else {
            WeldingResults.ActualWeldTime = RunningPreset.WeldTime;
         }
         break;

      default:                     /* All other modes but TIME */
         if ((WeldingResults.CycleModifiedAlarms & CM3) == (CM3 & ALARMCODEMASK)) {
            WeldingResults.ActualWeldTime = RunningPreset.MaxTimeout;
         }
         else if (TriggerLostFlag == TRUE) {
            WeldingResults.ActualWeldTime = TriggerLostTime;   /* Sync alrm info with sonics on time */
         }
         else {
            WeldingResults.ActualWeldTime = GetUpTimer(SONICSTIMER);
         }
         break;

   }

   DisplayWeldPower(PeakPower);

   WeldingResults.ActualFreqEnd = CurrentFreqIn;     /* Get final frequency   */
   CheckFrequencyLimits();
   WeldingResults.FrequencyChange = WeldingResults.ActualFreqEnd - WeldingResults.ActualFreqStart;

   if (CurrentSetup.ExtraCooling == FALSE) {
      CoolValOff();
   }
}


void AlStopHH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with turning off the sonics after  */
/*  an alarm has been generated when handheld (or any single input start)  */
/*  is enabled.                                                            */
/*                                                                         */
/***************************************************************************/
{
   PSIdle();                                /* Stop sonics                 */
   ClearSAS();                              /* Remove Sonics Active signal */
   CollectEnergyFlag = FALSE;

   if(AmpStepReachedFlag == TRUE)
      MsDataPtr->PrintBottomFlags &= (~AMPSTEPALARMMASK); /* Amp step reached, so remove alarm flag */

   if ((WeldingResults.PSActControlFlags & BIT0) == BIT0) {  /* If internal amp control only */
      *LastA = *A_Setup;
      *LastB = *B_Setup;
   }
   else {
      *LastA = 0;
      *LastB = 0;
   }

   /* SetCurrentFreqOffset(0); */    /* clear frequency offset  */                            
   if (WTimeFlag == TRUE) StopTimer(HHSonicTimer);
   WeldingResults.ActualWeldTime = (GetUpTimer(SONICSTIMER) - 1);
   if(RunningPreset.Amp2Flag == (UINT16)~BIT2){
      WeldingResults.ActualWeldTime++;
   }

   WeldingResults.PeakPower = (PeakPower);
   if (AccumulatedEnergy > 20000) {
      WeldingResults.TotalEnergy = (AccumulatedEnergy / (100000 / CurrentSetup.PSWatt));
   }
   else {
      WeldingResults.TotalEnergy = (AccumulatedEnergy * CurrentSetup.PSWatt) / 100000;
   }
   DisplayWeldPower(PeakPower);

   WeldingResults.ActualFreqEnd = CurrentFreqIn;     /* Get final frequency   */
   CheckFrequencyLimits();
   WeldingResults.FrequencyChange = WeldingResults.ActualFreqEnd - WeldingResults.ActualFreqStart;
   CheckEnergyComp();
   TriggerLostFlag = FALSE;
   if (Inp.OL == TRUE) PSReset();
}



void TestABDlyHH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the delay for afterburst      */
/*  when using a single start condition.  It will also wait for the DUPS   */
/*  data collection if an overload occured prior to this state.            */
/*                                                                         */
/***************************************************************************/
{
   ActualABDelay++;
   if (IsDUPSDataCollectionComplete() == TRUE) {
      DUPSOkFlag = TRUE;
   }
   else {
      DUPSOkFlag = FALSE;
   }
   if ( (DUPSOkFlag == TRUE) && (ABTimeFlag == FALSE) ) {
      ABTimeDelayFlag = FALSE;
   }
   else ABTimeDelayFlag = TRUE;
}



void TestABTmeHH(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will deal with checking afterburst time.      */
/*                                                                          */
/****************************************************************************/
{
   ActualAfterburstTime++;
   if (CurrentPowerIn > ABOverloadPower) {
      ABOverloadPower = CurrentPowerIn;
   }
}



void StartSeekHH(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the start of seek.            */
/*                                                                         */
/***************************************************************************/
{
   HHSeekDelay = SEEKDELAYTIME;            /* Load up counter with delay   */
   ActualSeekTime = 0;
   SeekEndFlag = FALSE;
}



void CheckSeekHH(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will be called every pass while seeking.      */
/*                                                                          */
/*  Notes: External cycle abort is checked here instead of calling          */
/*         CheckControlLimits because during seek we don't want to risk     */
/*         hitting peak power cutoff, energy compensation, or max timeout   */
/*         while we're seeking.                                             */
/*                                                                          */
/*         Overload is checked here instead of the state table to prevent   */
/*         an afterburst overload showing up also as a seek overload.       */
/*         Doing it here allows the SEEKDELAYTIME to pass before a check is */
/*         done, giving the power supply time to react to the reset from    */
/*         the afterburst overload.                                         */
/*                                                                          */
/****************************************************************************/
{
   if (ECycleHistFlag == TRUE) {          /* Check on external cycle abort */
      RecordAlarm(CM15);
   }
   if (HHSeekDelay-- <= 0) { 
      if (IsDUPSDataCollectionComplete() == TRUE) {
         DUPSOkFlag = TRUE;
         PSSeek();                        /* Start seek */
         MsDataPtr->PrintBottomFlags &= (~SEEKALARMMASK); /* Seek started, so remove alarm flag */
         if (ActualSeekTime++ >= MAXSEEKTIME) {
            ActualSeekTime--;
            SeekEndFlag = TRUE;
         }
         if (Inp.OL == TRUE) {
            RecordAlarm(OL8);
            SeekEndFlag = TRUE;
         }
      }
      else {
         DUPSOkFlag = FALSE;
      }
   }
}



void HHBeep(void)
/***************************************************************************/
/*                                                                         */
/*  This function will unconditionally sound the trigger beeper one time.  */
/*                                                                         */
/***************************************************************************/
{
   Beep(TRIGGERBEEP);
   PBReleaseOn();
}
