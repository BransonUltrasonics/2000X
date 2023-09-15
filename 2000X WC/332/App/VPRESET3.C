/* $Header:   D:/SWLab/VMdb/2000Series/App/VPRESET3.C_V   1.18   02 Sep 2008 21:05:50   nhahmed  $ */
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
/****************************************************************************/

/*--------------------------- MODULE DESCRIPTION ---------------------------

   Module name:   VERIFY_PRESET_MODEL3  

   Filename:      vpreset3.c     

   Function Name: VerifyPresetModel3
  
      Written by:    Barry E. Kymer
      Date:          07-07-97
      Language:      "C"             

 ---------------------------------- REVISIONS -----------------------------

 Revision  Date      Author     Description
 ========  ========  =========  ===========
   1.0     07-07-97  BEKymer    Sort of removed from weld_obj.c
   1.1     07-14-97  BEKymer    Add in setup alarms for control level 3
   1.2     07-28-97  BEKymer    Remove unused variable - ModelMask
                                Use CurentSetup.ControlLevel
   1.3     07-31-97  BEKymer    For alarms SE68 & SE69 check collapse cutoff flag
   1.4     08-01-97  BEKymer    Look at control level when checking for stepping
                                Check ABSCutoffFlag for SE138
                                Check MColDistRLimit for SE22
                                Fix bugs in SE86, SE87, SE88, SE89, SE90, SE91
                                SE97, SE98, SE107, SE108, SE109, SE110
   1.6     08-25-97  BEKymer    Check PreTrigFlag wherever pretrigger distance
                                is used SE109 to SE120.
                                Add weldmode check to all tests
   1.7     09-12-97  LAM        unit test version, moved runningpreset to extern
   1.8     09-22-97  BEKymer    Added check for CycleAbortFlag wherever
                                MissingPart Min or Max flag is checked
   1.9     09-30-97  BEKymer    Changed <= to >= for SE56
   1.10    09-30-97  PaulG      Removed typo.

-----------04-15-98--BEKymer----Start of code for release 2.5-----------------

   1.11    04-15-98  BEKymer    Added alarm SE139
                                Added check on actuator for all distance
                                related alarms
                                Moved all distance related alarms to vpreset4
   1.12    05-13-98  BEKymer    Add alarm SE43 to fix DCS # 2493.
   1.13    08-12-98  BEKymer    Remove check for ENERGY_MODE for alarms
                                SE18, SE19.  Check each menu
                                structure for proper weld modes.
   1.16    11-04-99  BEKymer    Removed TABS! and realign.
   1.17    06-28-00  BEKymer    Changed all MODEL to LEVEL
   1.18    09-02-08  NHAhmed    CleanUp for multi-language support.
 



*/
/* ----------------------------- DESCRIPTION -------------------------------*/




/* ------------------------------ INCLUDE FILES ----------------------------*/

#include <psos.h>                /* for access to pSOS routines          */
#include <prepc.h>
#include "error.h"
#include "preset.h"
#include "param.h"
#include "limits.h"
#include "ready.h"
#include "alarms.h"
#include "vpreset1.h"
#include "vpreset2.h"
#include "vpreset3.h"
#include "vpreset4.h"
#include "vpreset5.h"


/*------------------------------ WELD OBJECT DATA --------------------------*/



extern SETUPS_Ver800 RunningPreset;


extern CONFIGSETUP CurrentSetup;


UINT32 VerifyPresetModel3(void)
/***************************************************************************/
/*                                                                         */
/*  This function will verify the preset against itself and the system     */
/*  configuration.  It will check the following things:                    */
/*                                                                         */
/*    1) Make sure the required forces and downspeeds are achievable based */
/*       on the current regulator pressure.                                */
/*    2) Check all upper and lower limits for min/max cross.               */
/*    3) If any distance mode is required, make sure the linear encoder    */
/*       is available.                                                     */
/*    4) Check EP/AE requirements against actual actuator installed.       */
/*    5) After the preset is verified a state sequence will be generated   */
/*       to run the selected weld cycle.                                   */
/*                                                                         */
/*                                                                         */
/*                                                                         */
/*  The value returned will be FALSE if the preset is okay and can be run. */
/*  An error code will be returned if any problems are found.  The         */
/*  problems will be logged in PresetProblems array.  See Problems enum    */
/*  for list.                                                              */
/*                                                                         */
/***************************************************************************/
{
   UINT32 RetVal = FALSE;
   UINT16 SuspectFlag = FALSE;
   UINT16 RejectFlag = FALSE;


   RetVal = VerifyPresetModel2();

/*--------------------------------------------------------------------------*/
/*----    Here check for things which are mode specific                 ----*/
/*--------------------------------------------------------------------------*/

   switch (RunningPreset.WeldMode) {
      case TIMEMODE:
/*----   Cross check amplitude stepping with weld time  ----*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtTime.BitMask*/BIT2) == 0) &&
            (RunningPreset.AmpTrigTimeValue >= RunningPreset.WeldTime) ) {
               RetVal = SE15;
               RecordSetupAlarm(RetVal);
         }
               
/*----   Cross check amplitude step on energy with energy compensation  ----*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtEner.BitMask*/BIT3) == 0) &&
            (RunningPreset.EnergyCompFlag == TRUE) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.AmpTrigEnerValue >= RunningPreset.EnergyPL) ) {
               RetVal = SE38;
               RecordSetupAlarm(RetVal);
         }

/*---    Cross check amplitude step on power with peak power cutoff   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff) ) {
               RetVal = SE40;
               RecordSetupAlarm(RetVal);
         }
         break;

      case ENERGYMODE:
/*----   Cross check amplitude stepping with energy setting  ----*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtEner.BitMask*/BIT3) == 0) &&
            (RunningPreset.AmpTrigEnerValue >= RunningPreset.WeldEnergy) ) {
               RetVal = SE48;
               RecordSetupAlarm(RetVal);
         }
               
/*---    Cross check amplitude step on power with peak power cutoff   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff) ) {
               RetVal = SE40;
               RecordSetupAlarm(RetVal);
         }
         break;

      case PKPOWERMODE:
/*---    Cross check amplitude step on power with peak power value   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwr) ) {
               RetVal = SE37;
               RecordSetupAlarm(RetVal);
         }
         break;

      case ABSOLUTEMODE:
         if (CurrentSetup.ControlLevel < LEVEL_d) {
            RetVal = SE259;
            RecordSetupAlarm(RetVal);
         }
         break;

      case GRDDETECTMODE:
/*---    Cross check amplitude step on power with peak power cutoff   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            (CurrentSetup.AmpControl == TRUE) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff) ) {
               RetVal = SE40;
               RecordSetupAlarm(RetVal);
         }
         break;

      case COLLAPSEMODE:
         if (CurrentSetup.ControlLevel < LEVEL_d) {
            RetVal = SE259;
            RecordSetupAlarm(RetVal);
         }
         break;

      case CONTINUOUSMODE:
         break;
   }
   

/*--------------------------------------------------------------------------*/
/*---  Here check for things which are not mode specific or not related  ---*/
/*---  to either suspect or reject limits.                               ---*/
/*--------------------------------------------------------------------------*/

/*--  Check amplitude step at time with timeout  --*/

   if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
      (CurrentSetup.AmpControl == TRUE) &&
      (RunningPreset.WeldMode != TIMEMODE) &&
      ((RunningPreset.Amp2Flag & /*AmpStepAtTime.BitMask*/BIT2) == 0) &&
      (RunningPreset.AmpTrigTimeValue >= RunningPreset.MaxTimeout) ) {
         RetVal = SE43;
         RecordSetupAlarm(RetVal);
   }


 
/*--------------------------------------------------------------------------*/
/*--  Here are tests which are only valid when Suspect Limits are enabled --*/
/*--------------------------------------------------------------------------*/

   if (((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
        (RunningPreset.WeldMode != CONTINUOUSMODE)) {

      SuspectFlag = TRUE;

/*--  Check amplitude step at peak power with plus suspect limit  --*/

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
         (CurrentSetup.AmpControl == TRUE) &&
         ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
         ((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
         (RunningPreset.WeldMode != PKPOWERMODE) &&
         (RunningPreset.AmpTrigPowerValue >= RunningPreset.PowerPLS) ) {
             RetVal = SE17;
             RecordSetupAlarm(RetVal);
      }

/*--  Check amplitude step at energy with plus suspect limit  --*/

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
         (CurrentSetup.AmpControl == TRUE) &&
         ((RunningPreset.Amp2Flag & /*AmpStepAtEner.BitMask*/BIT3) == 0) &&
         ((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         ((/*PEnergySTime.mode*/(ENERGYMODE | TIMEMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*AmpStepAtEner.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.AmpTrigEnerValue >= RunningPreset.EnergyPLS) ) {
            RetVal = SE19;
            RecordSetupAlarm(RetVal);
      }

   }



/*--------------------------------------------------------------------------*/
/*--  Here are tests which are only valid when Reject Limits are enabled  --*/
/*--------------------------------------------------------------------------*/

   if (((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
        (RunningPreset.WeldMode != CONTINUOUSMODE)) {

      RejectFlag = TRUE;
 
/*--  Check amplitude step at peak power with plus reject limit  --*/

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
         (CurrentSetup.AmpControl == TRUE) &&
         ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
         ((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
         (RunningPreset.WeldMode != PKPOWERMODE) &&
         (RunningPreset.AmpTrigPowerValue >= RunningPreset.PowerPLR) ) {
            RetVal = SE16;
            RecordSetupAlarm(RetVal);
      }

/*--  Check amplitude step at energy with plus reject limit  --*/

      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
         (CurrentSetup.AmpControl == TRUE) &&
         ((RunningPreset.Amp2Flag & /*AmpStepAtEner.BitMask*/BIT3) == 0) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         ((/*PEnergyRTime.mode*/(ENERGYMODE | TIMEMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*AmpStepAtEner.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.AmpTrigEnerValue >= RunningPreset.EnergyPLR) ) {
            RetVal = SE18;
            RecordSetupAlarm(RetVal);
      }
   }

/*-----------------------------------------------------------------------*/
/*---  Here are tests for when BOTH reject and suspect limits are on  ---*/
/*-----------------------------------------------------------------------*/
      
   if ((SuspectFlag == TRUE) && (RejectFlag == TRUE)) {
      ;
   }


/*--------------------------------------------------------------------------*/
/*----    Finally check for things which are only allowed in            ----*/
/*----    control level 4 or above.                                     ----*/
/*--------------------------------------------------------------------------*/


   return(RetVal);
}

