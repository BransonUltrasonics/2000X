/* $Header:   D:/databases/VMdb/2000Series/App/VPRESET4.C_V   1.35.1.0.1.0   Oct 18 2017 13:09:10   RCHAPA  $ */
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

   Module name:   VERIFY_PRESET_MODEL4  

   Filename:      vpreset4.c     

   Function Name: VerifyPresetModel4
  
        Written by:    Barry E. Kymer
      Date:          07-07-97
      Language:      "C"

 ---------------------------------- REVISIONS -----------------------------

    Revision  Date      Author     Description
    ========  ========  =========  ===========
      1.0     07-07-97  BEKymer    Sort of removed from weld_obj.c
   1.1     07-14-97  BEKymer    Adding setup checks for release 2
   1.2     07-28-97  BEKymer    Remove unused variable - ModelMask
                                Use CurentSetup.ControlLevel
   1.3     07-31-97  BEKymer    Look at control level when checking for stepping
                                Check PAbsDistSLimit for SE23
   1.4     08-12-97  BEKymer    Added additional check alarms SE19, SE18
   1.5     08-27-97  BEKymer    Check if plus power suspect limit is on
                                for SE17 and plus power reject limit is on
                                for SE16.
   1.6     09-12-97  BEKymer    Make RunningPreset extern
   1.7     09-19-97  BEKymer    Check ControlLimitFlag wherever ColCutoffFlag
                                is checked
   1.8     10-02-97  BEKymer    Check EnergyCompFlag & ControlLimitsFlag for
                                alarm SE38.
   1.9     10-07-97  BEKymer    Check PeakPwrCutoffFlag for all SE40 alarms
   1.10    12-09-97  BEKymer    Check weld mode for the following alarms:
                                SE16-19, SE22-SE23

-----------04-15-98--BEKymer----Start of code for release 2.5-----------------

   1.11    04-15-98  BEKymer    Added alarms SE99, SE100, SE101, SE102
                                Moved all amplitude related alarms to vpreset3
                                Added alarms SE271, SE272, SE273, SE274
                                SE275, SE276, SE277
   1.12    04-20-98  BEKymer    Move max force alarms from vpreset5.c
                                Add Control limits check and absolute check
                                to SE277.
                                Check MissingPartFlag for all missing part
                                alarms.
                                Check for force stepping on models below (but
                                not equal to) MODEL5.
   1.13    05-01-98  BEKymer    Remove test for ControlLimitsFlag on SE168
                                and SE169
   1.14    05-27-98  BEKymer    Add SE120-Missing Part Max/Min cross
   1.15    06-29-98  BEKymer    Check menu structure to decide if the weldmode
                                is correct for alarms: SE68, SE69
   1.16    07-10-98  BEKymer    Check MAbsDistRLimit.mode for SE56
                                Check PAbsDistRLimit.mode for SE57
   1.17    07-15-98  BEKymer    Remove left over SE151, change -S Trg D vs
                                missing part max from SE153 to SE151
                                Check absolute dist in Abs mode against max 
                                stroke len.
                                Check trig force against max force
   1.18    07-21-98  BEKymer    Check SUSPECT value for SE151
                                Check PLUS value for SE155
                                Check PLUS and SUSPECT for SE164
                                Check SUSPECT for SE152
   1.19    08-11-98  BEKymer    Check ABSCutoff.mode against WeldMode for
                                SE167
                                Check menu structures for SE22-SE23 instead
                                of checking for not Collapse mode.
                                Remove extra 'break' in GRDDETECTMODE case
                                for alarm SE41
                                Check menu structures for SE141, SE143, SE145,
                                SE138, SE140, SE142, SE144, SE166
                                Check TrsDistPLR (not MLR) for SE161
                                Add SE40 to Absolute mode
                                Added a bunch of checks for distances compared
                                to stroke length and forces compared to 
                                cylinder diameter.
   1.20    09-03-98  BEKymer    Remove alarm SE146.
   1.21    10-07-98  BEKymer    Check MissingPart for alarm SE120
                                For alarm SE165 use TrsDistPLS not MLR
   1.22    05-27-99  OFI        Took out MaximumForce from function and declared it globaly.
   1.23.1.1 07-12-99 JZ         added ErrorCode for alarm SE268
   1.25     08-04-99 JZ         added ErrorCodeFlag
   1.26     08-06-99 JZ         added RecordErrorCode
   1.27     08-31-99 JZ         added condition for removing the tenths from the trigger force in USCS only
   1.28     11-04-99 JZ         removed tabs
   1.29     11-05-99 JZ         aligned the code
   1.30     02-09-00 OFI        Deleted alarms:SE22,23,68,69
   1.31     07-5-00  DJL        Made changes from MODEL to LEVEL, changed AmpTrigDistValue to AmpTrigColValue.
   1.32     07-12-00 BEKymer    Changed AmpTrigDistValue to AmpTrigColValue
   1.33     08-06-04 BEKymer    Removed alarm SE169.  It checks for a condition
                                 that is actually valid.
   1.34     09-02-08 NHAhmed    CleanUp for multi-language support.
   1.35     09-10-09 BEkymer    Add new define MICRO where needed
   1.36     10-19-12 JWang		Add some alarms for abosulte mode.
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
#include "actnvram.h"
#include "util.h"



/*------------------------------ WELD OBJECT DATA --------------------------*/



extern SETUPS_Ver800 RunningPreset;


extern CONFIGSETUP CurrentSetup;

SINT32 MaximumForce;



UINT32 VerifyPresetModel4(void)
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
   UINT32 TempRetVal = FALSE;
   UINT16 SuspectFlag = FALSE;
   UINT16 RejectFlag = FALSE;
   SINT32 Stroke;
  
   RetVal = VerifyPresetModel3();
   if (CurrentSetup.Units == FALSE){             /*     this removes the tenths from the force */
      RunningPreset.TriggerForce /= 10;         /*     in USCS only */
      RunningPreset.TriggerForce *= 10;
   }      
   Stroke = GetMaxStrokeLength();
   TempRetVal = CheckForValidDistances(Stroke);
   if (TempRetVal == FALSE) {
      RecordErrorCode( ERRORCODE5_SE268 );
      RetVal = SE268;
      RecordSetupAlarm(RetVal);
   }

   MaximumForce = GetMaxForce();
   TempRetVal = CheckForValidForces(MaximumForce);
   if (TempRetVal == FALSE) {
      RecordErrorCode( ERRORCODE6_SE268 );
      RetVal = SE268;
      RecordSetupAlarm(RetVal);
   }


/*--------------------------------------------------------------------------*/
/*----    Here check for things which are mode specific                 ----*/
/*--------------------------------------------------------------------------*/

/*----   Make sure step values are less then control values   ----*/

   switch (RunningPreset.WeldMode) {
      default:
      case TIMEMODE:
/*---    Cross check amplitude step on collapse with collapse cutoff   ---*/
//AmpStepAtDist must be renamed    to AmpStepAtCol
//AmpTrigDistValue must be renamed    AmpTrigColValue

         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtDist.BitMask*/BIT5) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.ColCutoffFlag == FALSE) &&  /*FALSE=On*/
            (RunningPreset.AmpTrigColValue >= RunningPreset.ColCutoffDist) )
         {
            RetVal = SE41;
            RecordSetupAlarm(RetVal);
         }
         break;

      case ENERGYMODE:
/*---    Cross check amplitude step on collapse with collapse cutoff   ---*/
//AmpStepAtDist must be renamed    to AmpStepAtCol
//AmpTrigDistValue must be renamed    AmpTrigColValue

         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtDist.BitMask*/BIT5) == 0) &&
            (RunningPreset.ColCutoffFlag == FALSE) &&  /*FALSE=On*/
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.AmpTrigColValue >= RunningPreset.ColCutoffDist) )
         {
            RetVal = SE41;
            RecordSetupAlarm(RetVal);
         }
         break;

      case PKPOWERMODE:
/*---    Cross check amplitude step on collapse with collapse cutoff   ---*/
//AmpStepAtDist must be renamed    to AmpStepAtCol
//AmpTrigDistValue must be renamed    AmpTrigColValue

         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtDist.BitMask*/BIT5) == 0) &&
            (RunningPreset.ColCutoffFlag == FALSE) &&  /*FALSE=On*/
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.AmpTrigColValue >= RunningPreset.ColCutoffDist) )
         {
            RetVal = SE41;
            RecordSetupAlarm(RetVal);
         }
         break;

      case ABSOLUTEMODE:
/*----   Check absolute distance against maximum stroke length    ----*/
 
         if ( ( (CurrentSetup.Actuator == AEF) ||
                (CurrentSetup.Actuator == AED) ||
                (CurrentSetup.Actuator == MICRO) ) &&
            (RunningPreset.AbsDist > Stroke) )
         {
            RecordErrorCode( ERRORCODE5_SE268 );
            RetVal = SE268;
            RecordSetupAlarm(RetVal);
         }
  

/*----   Check pretrigger distance with absolute distance    ----*/

         if ( (RunningPreset.PreTrigDistFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.PreTrigFlag == TRUE) &&      /*TRUE =On*/
            ( (CurrentSetup.Actuator == AEF) ||
              (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == MICRO) ) &&
            (RunningPreset.PreTrigDist >= RunningPreset.AbsDist) )
         {
            RetVal = SE137;
            RecordSetupAlarm(RetVal);
         }
   
/*----   Check absolute distance with missing part min distance    ----*/

         if ( (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
            (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
            (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
            ( (CurrentSetup.Actuator == AEF) ||
              (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == MICRO) ) &&
            (RunningPreset.MissingPartMin >= RunningPreset.AbsDist) )
         {
            RetVal = SE168;
            RecordSetupAlarm(RetVal);
         }

/*----   Check absolute distance with missing part max distance    ----*/
//  Removed during mh testing for version 9
//         if ( (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
//            (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
//            (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
//            ((CurrentSetup.Actuator == AEF) || (CurrentSetup.Actuator == AED)) &&
//            (RunningPreset.MissingPartMax >= RunningPreset.AbsDist) )
//         {
//            RetVal = SE169;
//            RecordSetupAlarm(RetVal);
//         }

/*----   Cross check amplitude stepping with abs distance  ----*/
//AmpStepAtDist must be renamed    to AmpStepAtAbs
//AmpTrigDistValue must be renamed    AmpTrigAbsValue

//             if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
//                    ((RunningPreset.Amp2Flag & AmpStepAtDist.BitMask) == 0) &&
//                     (RunningPreset.AmpTrigDistValue >= RunningPreset.AbsDist) ) {
//                   RetVal = SE47;
//                   RecordSetupAlarm(RetVal);
//             }

/*---    Cross check amplitude step on collapse with collapse cutoff   ---*/
//AmpStepAtDist must be renamed    to AmpStepAtCol
//AmpTrigDistValue must be renamed    AmpTrigColValue

         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtDist.BitMask*/BIT5) == 0) &&
            (RunningPreset.ColCutoffFlag == FALSE) &&  /*FALSE=On*/
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.AmpTrigColValue >= RunningPreset.ColCutoffDist) )
         {
            RetVal = SE41;
            RecordSetupAlarm(RetVal);
         }

/*---    Cross check amplitude step on power with peak power cutoff   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff) )
         {
            RetVal = SE40;
            RecordSetupAlarm(RetVal);
         }
         break;

      case GRDDETECTMODE:
/*---    Cross check amplitude step on power with peak power cutoff   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff) )
         {
            RetVal = SE40;
            RecordSetupAlarm(RetVal);
         }

/*---    Cross check amplitude step on collapse with collapse cutoff   ---*/
//AmpStepAtDist must be renamed    to AmpStepAtCol
//AmpTrigDistValue must be renamed    AmpTrigColValue

         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtDist.BitMask*/BIT5) == 0) &&
            (RunningPreset.ColCutoffFlag == FALSE) &&  /*FALSE=On*/
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.AmpTrigColValue >= RunningPreset.ColCutoffDist) )
         {
            RetVal = SE41;
            RecordSetupAlarm(RetVal);
         }
         break;

      case COLLAPSEMODE:
/*----   Cross check amplitude stepping with collapse distance  ----*/
//AmpStepAtDist must be renamed    to AmpStepAtCol
//AmpTrigDistValue must be renamed    AmpTrigColValue

         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtDist.BitMask*/BIT5) == 0) &&
            (RunningPreset.AmpTrigColValue >= RunningPreset.ColDist) )
         {
            RetVal = SE42;
            RecordSetupAlarm(RetVal);
         }

/*---    Cross check amplitude step on power with peak power cutoff   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff) )
         {
            RetVal = SE40;
            RecordSetupAlarm(RetVal);
         }
         break;

      case CONTINUOUSMODE:
/*---    Cross check amplitude step on power with peak power cutoff   ---*/
         if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
            ((RunningPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) == 0) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
            (RunningPreset.AmpTrigPowerValue >= RunningPreset.PeakPwrCutoff) )
         {
            RetVal = SE40;
            RecordSetupAlarm(RetVal);
         }
         break;
   }
   
/*--------------------------------------------------------------------------*/
/*---  Here check for things which are not mode specific or not related  ---*/
/*---  to either suspect or reject limits.                               ---*/
/*--------------------------------------------------------------------------*/

/*----   Check pretrigger distance with absolute cutoff distance    ----*/

   if ( (RunningPreset.PreTrigDistFlag == FALSE) &&   /*FALSE=On*/
      (RunningPreset.PreTrigFlag == TRUE) &&        /*TRUE =On*/
      (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
      (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
      ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ( (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) ) &&
      (RunningPreset.PreTrigDist >= RunningPreset.ABSCutoffDist) )
   {
      RetVal = SE136;
      RecordSetupAlarm(RetVal);
   }
   
/*----   Check absolute distance cutoff with missing part min distance    ----*/

   if ( (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
      (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
      (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
      ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ( (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) ) &&
      (RunningPreset.MissingPartMin >= RunningPreset.ABSCutoffDist) )
   {
      RetVal = SE166;
      RecordSetupAlarm(RetVal);
   }

/*----  Check missing part max distance with missing part min distance  ----*/

   if ( (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
      (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
      ( (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) ) &&
      (RunningPreset.MissingPartMin >= RunningPreset.MissingPartMax) )
   {
      RetVal = SE120;
      RecordSetupAlarm(RetVal);
   }

/*----   Check absolute distance cutoff with missing part max distance    ----*/

   if ( (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
      (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
      (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
      (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
      ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ( (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) ) &&
      (RunningPreset.MissingPartMax >= RunningPreset.ABSCutoffDist) )
   {
      RetVal = SE167;
      RecordSetupAlarm(RetVal);
   }
   


/*--------------------------------------------------------------------------*/
/*--  Here are tests which are only valid when Suspect Limits are enabled --*/
/*--------------------------------------------------------------------------*/

   if (((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
        (RunningPreset.WeldMode != CONTINUOUSMODE)) {

      SuspectFlag = TRUE;


/*- Check minus suspect trigger distance with minus suspect absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*MAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ( (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLS >= RunningPreset.AbsMLS) )
      {
         RetVal = SE54;
         RecordSetupAlarm(RetVal);
      }

/*- Check plus suspect trigger distance with plus suspect absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ( (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistPLS >= RunningPreset.AbsPLS) )
      {
         RetVal = SE55;
         RecordSetupAlarm(RetVal);
      }

/*- Check minus suspect trigger distance with plus suspect absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
          ( (CurrentSetup.Actuator == AEF) ||
            (CurrentSetup.Actuator == AED) ||
            (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLS >= RunningPreset.AbsPLS) )
      {
         RetVal = SE271;
         RecordSetupAlarm(RetVal);
      }

/*- Check minus suspect trigger distance with absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*AbsoluteAbs.mode*/ABSOLUTEMODE & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLS >= RunningPreset.AbsDist) )
      {
         RetVal = SE275;
         RecordSetupAlarm(RetVal);
      }

/*-- Check absolute distance cutoff with minus suspect trigger distance limit --*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&   /*TRUE =On*/
         (RunningPreset.ABSCutoffFlag == FALSE) &&      /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.ABSCutoffDist <= RunningPreset.TrsDistMLS) )
      {
         RetVal = SE141;
         RecordSetupAlarm(RetVal);
      }

/*-- Check absolute distance cutoff with plus suspect absolute distance limit --*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ABSCutoffDist <= RunningPreset.AbsPLS) )
      {
         RetVal = SE144;
         RecordSetupAlarm(RetVal);
      }

/*-- Check absolute distance cutoff with plus suspect trigger distance limit --*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.ABSCutoffDist <= RunningPreset.TrsDistPLS) )
      {
         RetVal = SE145;
         RecordSetupAlarm(RetVal);
      }


/*---  Check absolute distance cutoff with minus suspect absolute distance limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*MAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
         ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.AbsMLS >= RunningPreset.ABSCutoffDist) )
      {
         RetVal = SE140;
         RecordSetupAlarm(RetVal);
      }

/*----   Check minus suspect absolute limit with pretrigger distance    ----*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*MAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PreTrigFlag == TRUE) &&        /*TRUE =On*/
         (RunningPreset.PreTrigDistFlag == FALSE) &&   /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.PreTrigDist >= RunningPreset.AbsMLS) )
      {
         RetVal = SE129;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check plus suspect absolute limit with pretrigger distance    ----*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PreTrigFlag == TRUE) &&        /*TRUE =On*/
         (RunningPreset.PreTrigDistFlag == FALSE) &&   /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.PreTrigDist >= RunningPreset.AbsPLS) )
      {
         RetVal = SE131;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check plus suspect trigger limit with pretrigger distance    ----*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PreTrigFlag == TRUE) &&        /*TRUE =On*/
         (RunningPreset.PreTrigDistFlag == FALSE) &&   /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.PreTrigDist >= RunningPreset.TrsDistPLS) )
      {
         RetVal = SE133;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check minus suspect trigger limit with pretrigger distance    ----*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PreTrigFlag == TRUE) &&        /*TRUE =On*/
         (RunningPreset.PreTrigDistFlag == FALSE) &&   /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.PreTrigDist >= RunningPreset.TrsDistMLS) )
      {
         RetVal = SE135;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check minus Suspect absolute limit with missing part min distance    ----*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*MAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMin >= RunningPreset.AbsMLS) )
      {
         RetVal = SE150;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check minus Suspect trigger limit with missing part min distance    ----*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMin >= RunningPreset.TrsDistMLS) )
      {
         RetVal = SE152;
         RecordSetupAlarm(RetVal);
      }

/*----   Check minus Suspect trigger limit with missing part max distance    ----*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMax <= RunningPreset.TrsDistMLS) )
      {
         RetVal = SE151;
         RecordSetupAlarm(RetVal);
      }

/*----   Check plus suspect absolute limit with missing part min distance    ----*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMin >= RunningPreset.AbsPLS) )
      {
         RetVal = SE163;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check plus suspect absolute limit with missing part max distance    ----*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMax <= RunningPreset.AbsPLS) )
      {
         RetVal = SE162;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check plus suspect trigger limit with missing part min distance    ----*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMin >= RunningPreset.TrsDistPLS) )
      {
         RetVal = SE165;
         RecordSetupAlarm(RetVal);
      }

/*----   Check plus suspect trigger limit with missing part max distance    ----*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMax <= RunningPreset.TrsDistPLS) )
      {
         RetVal = SE164;
         RecordSetupAlarm(RetVal);
      }


/*--  Check amplitude step at absolute distance with plus suspect limit  --*/
//AmpStepAtDist must be renamed    to AmpStepAtAbs
//AmpTrigDistValue must be renamed    AmpTrigAbsValue

//      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
//          ((RunningPreset.Amp2Flag & AmpStepAtDist.BitMask) == 0) &&
//           (RunningPreset.AmpTrigDistValue >= RunningPreset.AbsPLS) ) {
//         RetVal = SE21;
//         RecordSetupAlarm(RetVal);
//      }


/*----   Check plus suspect max force with minus suspect max force   ----*/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (((RunningPreset.SuspectLimits & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0) &&
            ((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0) &&
            (RunningPreset.WeldForcePLS <= RunningPreset.WeldForceMLS) )
         {
            RetVal = SE14;
            RecordSetupAlarm(RetVal);
         }
      }

/*----   Check trigger force with plus suspect max force   ----*/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0) &&
            (RunningPreset.TriggerForce >= RunningPreset.WeldForcePLS) )
         {
            RetVal = SE251;
            RecordSetupAlarm(RetVal);
         }
      }

   }


/*--------------------------------------------------------------------------*/
/*--  Here are tests which are only valid when Reject Limits are enabled  --*/
/*--------------------------------------------------------------------------*/

   if (((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.WeldMode != CONTINUOUSMODE)) {

      RejectFlag = TRUE;


/*- Check minus reject trigger distance with minus reject absolute distance -*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*MAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLR >= RunningPreset.AbsMLR) )
      {
         RetVal = SE56;
         RecordSetupAlarm(RetVal);
      }
   
/*- Check plus reject trigger distance with plus reject absolute distance -*/

      if (((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE)& RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistPLR >= RunningPreset.AbsPLR) )
      {
         RetVal = SE57;
         RecordSetupAlarm(RetVal);
      }

/*- Check minus reject trigger distance with plus suspect absolute distance -*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLR >= RunningPreset.AbsPLR) )
      {
         RetVal = SE274;
         RecordSetupAlarm(RetVal);
      }

/*- Check minus reject trigger distance with absolute distance -*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*AbsoluteAbs.mode*/ABSOLUTEMODE & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLR >= RunningPreset.AbsDist) )
      {
         RetVal = SE276;
         RecordSetupAlarm(RetVal);
      }

/*-- Check absolute distance cutoff with plus reject absolute distance limit --*/

      if (((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.ABSCutoffDist <= RunningPreset.AbsPLR) )
      {
         RetVal = SE142;
         RecordSetupAlarm(RetVal);
      }

/*-- Check absolute distance cutoff with plus reject trigger distance limit --*/

      if (((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.ABSCutoffDist <= RunningPreset.TrsDistPLR) )
      {
         RetVal = SE143;
         RecordSetupAlarm(RetVal);
      }


/*---  Check absolute distance cutoff with minus reject absolute distance limit  ---*/

      if (((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*MAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.AbsMLR >= RunningPreset.ABSCutoffDist) )
      {
         RetVal = SE138;
         RecordSetupAlarm(RetVal);
      }

/*---  Check absolute distance cutoff with minus reject trigger limit  ---*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.ABSCutoffDist <= RunningPreset.TrsDistMLR) )
      {
         RetVal = SE139;
         RecordSetupAlarm(RetVal);
      }

/*----   Check minus reject absolute limit with pretrigger distance    ----*/

      if (((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*MAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PreTrigFlag == TRUE) &&        /*TRUE =On*/
         (RunningPreset.PreTrigDistFlag == FALSE) &&   /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.PreTrigDist >= RunningPreset.AbsMLR) )
      {
         RetVal = SE123;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check plus reject absolute limit with pretrigger distance    ----*/

      if (((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PreTrigFlag == TRUE) &&        /*TRUE =On*/
         (RunningPreset.PreTrigDistFlag == FALSE) &&   /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.PreTrigDist >= RunningPreset.AbsPLR) )
      {
         RetVal = SE130;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check plus reject trigger limit with pretrigger distance    ----*/

      if (((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PreTrigFlag == TRUE) &&        /*TRUE =On*/
         (RunningPreset.PreTrigDistFlag == FALSE) &&   /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.PreTrigDist >= RunningPreset.TrsDistPLR) )
      {
         RetVal = SE132;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check minus reject trigger limit with pretrigger distance    ----*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PreTrigFlag == TRUE) &&        /*TRUE =On*/
         (RunningPreset.PreTrigDistFlag == FALSE) &&   /*FALSE=On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.PreTrigDist >= RunningPreset.TrsDistMLR) )
      {
         RetVal = SE134;
         RecordSetupAlarm(RetVal);
      }

/*----   Check minus reject absolute limit with missing part min distance    ----*/

      if (((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*MAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMin >= RunningPreset.AbsMLR) )
      {
         RetVal = SE147;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check minus reject absolute limit with missing part max distance    ----*/

//  This alarm removed on 09-03-98 by agreement with Bob Jalbert and
//  Kevin Klein after reviewing DCS issue # 2837.

//      if (((RunningPreset.RejectLimits & MAbsDistRLimit.BitMask) == 0) &&
//          ((MAbsDistRLimit.mode & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
//           (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
//           (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
//           (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
//          ((CurrentSetup.Actuator == AEF) || (CurrentSetup.Actuator == AED)) &&
//              (RunningPreset.MissingPartMax <= RunningPreset.AbsMLR) ) {
//            RetVal = SE146;
//           RecordSetupAlarm(RetVal);
//      }
   
/*----   Check minus reject trigger limit with missing part min distance    ----*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMin >= RunningPreset.TrsDistMLR) )
      {
         RetVal = SE149;
         RecordSetupAlarm(RetVal);
      }

/*----   Check minus reject trigger limit with missing part max distance    ----*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMax <= RunningPreset.TrsDistMLR) )
      {
         RetVal = SE148;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check plus reject absolute limit with missing part min distance    ----*/

      if (((RunningPreset.RejectLimits &/*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMin >= RunningPreset.AbsPLR) )
      {
         RetVal = SE154;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check plus reject absolute limit with missing part max distance    ----*/

      if (((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMax >= RunningPreset.AbsPLR) )
      {
         RetVal = SE153;
         RecordSetupAlarm(RetVal);
      }
   
/*----   Check plus reject trigger limit with missing part min distance    ----*/

      if (((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMin >= RunningPreset.TrsDistPLR) )
      {
         RetVal = SE161;
         RecordSetupAlarm(RetVal);
      }

/*----   Check plus reject trigger limit with missing part max distance    ----*/

      if (((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
         (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
         (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.MissingPartMax <= RunningPreset.TrsDistPLR) )
      {
         RetVal = SE155;
         RecordSetupAlarm(RetVal);
      }


/*--  Check amplitude step at absolute distance with plus reject limit  --*/
//AmpStepAtDist must be renamed    to AmpStepAtAbs
//AmpTrigDistValue must be renamed    AmpTrigAbsValue

//      if (((RunningPreset.Amp2Flag & BIT0) == BIT0) &&
//          ((RunningPreset.Amp2Flag & AmpStepAtDist.BitMask) == 0) &&
//           (RunningPreset.AmpTrigDistValue >= RunningPreset.AbsPLR) ) {
//         RetVal = SE20;
//         RecordSetupAlarm(RetVal);
//      }


/*----   Check plus reject max force with minus reject max force    ----*/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {

         if (((RunningPreset.RejectLimits & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0) &&
            ((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0) &&
            (RunningPreset.WeldForcePLR <= RunningPreset.WeldForceMLR) )
         {
            RetVal = SE13;
            RecordSetupAlarm(RetVal);
         }
      }

/*----   Check trigger force with plus reject max force   ----*/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0) &&
            (RunningPreset.TriggerForce >= RunningPreset.WeldForcePLR) )
         {
            RetVal = SE257;
            RecordSetupAlarm(RetVal);
         }
      }

   }


/*--------------------------------------------------------------------------*/
/*----  Here are tests for when BOTH reject and suspect limits are on.  ----*/
/*--------------------------------------------------------------------------*/
      
   if ((SuspectFlag == TRUE) && (RejectFlag == TRUE)) {

/*---  Check plus reject absolute limit with minus suspect absolute limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*MAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.AbsPLR <= RunningPreset.AbsMLS) )
      {
         RetVal = SE86;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect absolute limit with minus reject absolute limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*MAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.AbsPLS <= RunningPreset.AbsMLR) )
      {
         RetVal = SE87;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject absolute limit with plus suspect absolute limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.AbsPLR <= RunningPreset.AbsPLS) )
      {
         RetVal = SE88;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject absolute limit with minus suspect absolute limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*MAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*MAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.AbsMLR >= RunningPreset.AbsMLS) )
      {
         RetVal = SE89;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject collapse limit with minus suspect collapse limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MColDistSLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PColDistRLimit.BitMask*/PCOLDISTBIT) == 0) &&
         ((/*MColDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PColDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.ColPLR <= RunningPreset.ColMLS) )
      {
         RetVal = SE90;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect collapse limit with minus reject collapse limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PColDistSLimit.BitMask*/PCOLDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MColDistRLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((/*PColDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*MColDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.ColPLS <= RunningPreset.ColMLR) )
      {
         RetVal = SE91;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject collapse limit with plus suspect collapse limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PColDistSLimit.BitMask*/PCOLDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PColDistRLimit.BitMask*/PCOLDISTBIT) == 0) &&
         ((/*PColDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PColDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.ColPLR <= RunningPreset.ColPLS) )
      {
         RetVal = SE97;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject collapse limit with minus suspect collapse limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MColDistSLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MColDistRLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((/*MColDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*MColDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.ColMLR >= RunningPreset.ColMLS) )
      {
         RetVal = SE98;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject trigger limit with minus suspect trigger limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistPLR <= RunningPreset.TrsDistMLS) )
      {
         RetVal = SE107;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect trigger limit with minus reject trigger limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*PTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistPLS <= RunningPreset.TrsDistMLR) )
      {
         RetVal = SE108;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject trigger limit with plus suspect trigger limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistPLR <= RunningPreset.TrsDistPLS) )
      {
         RetVal = SE109;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject trigger limit with minus suspect trigger limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLR >= RunningPreset.TrsDistMLS) )
      {
         RetVal = SE110;
         RecordSetupAlarm(RetVal);
      }

/*- Check minus suspect trigger distance with plus reject absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLS >= RunningPreset.AbsPLR) )
      {
         RetVal = SE272;
         RecordSetupAlarm(RetVal);
      }

/*- Check minus reject trigger distance with plus suspect absolute distance -*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLR >= RunningPreset.AbsPLS) )
      {
         RetVal = SE273;
         RecordSetupAlarm(RetVal);
      }

/*-- Check plus reject max force limit with minus suspect max force limit --*/

      if (((RunningPreset.SuspectLimits & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0) &&
         ((/*MMaxForceSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PMaxForceRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.WeldForcePLR <= RunningPreset.WeldForceMLS) )
      {
         RetVal = SE99;
         RecordSetupAlarm(RetVal);
      }

/*-- Check plus suspect max force limit with minus reject max force limit --*/

      if (((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0) &&
         ((/*PMaxForceSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*MMaxForceRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.WeldForcePLS <= RunningPreset.WeldForceMLR) )
      {
         RetVal = SE100;
         RecordSetupAlarm(RetVal);
      }

/*-- Check plus reject max force limit with plus suspect max force limit  --*/

      if (((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0) &&
         ((/*PMaxForceSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*PMaxForceRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.WeldForcePLR <= RunningPreset.WeldForcePLS) )
      {
         RetVal = SE101;
         RecordSetupAlarm(RetVal);
      }

/*-- Check minus reject max force limit with minus suspect max force limit -*/

      if (((RunningPreset.SuspectLimits & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0) &&
         ((/*MMaxForceSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ((/*MMaxForceRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.WeldForceMLR >= RunningPreset.WeldForceMLS) )
      {
         RetVal = SE102;
         RecordSetupAlarm(RetVal);
      }
   }

/*--------------------------------------------------------------------------*/
/*----    Finally check for things which are only allowed in            ----*/
/*----    control level 5 or above.                                     ----*/
/*--------------------------------------------------------------------------*/


/*---  Check for force stepping  ---*/

   if (CurrentSetup.ControlLevel < LEVEL_f) {
      if ((RunningPreset.Force2Flag & BIT0) == BIT0) {
         RecordErrorCode( ERRORCODE3_SE268 );
         RetVal = SE268;
         RecordSetupAlarm(RetVal);
      }
   }

   return(RetVal);
}



BOOLEAN CheckForValidDistances(SINT32 MaxStroke)
/*--------------------------------------------------------------------------*/
/*  This function will check all distances against the stroke length which  */
/*  has been selected for this machine as defined by the passed argument.   */
/*  If any problems are found, a FALSE will be returned.  If all is okay    */
/*  then TRUE will be returned.                                             */
/*--------------------------------------------------------------------------*/
{
   BOOLEAN RetVal = TRUE;

/*----------  First check things which are Suspect limits  ----------*/

   if ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) {

/*- Check minus suspect trigger distance -*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLS > MaxStroke) )
      {
         RetVal = FALSE;
      }

/*- Check plus suspect trigger distance -*/

      if (((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistPLS > MaxStroke) )
      {
         RetVal = FALSE;
      }

/*- Check minus suspect absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*AbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.AbsMLS > MaxStroke) )
      {
         RetVal = FALSE;
      }

/*- Check plus suspect absolute distance -*/

      if (((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.AbsPLS > MaxStroke) )
      {
         RetVal = FALSE;
      }

   }

/*----------  Next check things which are Reject limits  ----------*/

   if ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) {

/*- Check minus reject trigger distance -*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistMLR > MaxStroke) )
      {
         RetVal = FALSE;
      }

/*- Check plus reject trigger distance -*/

      if (((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*PTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.TrsDistPLR > MaxStroke) )
      {
         RetVal = FALSE;
      }

/*- Check minus reject absolute distance -*/

      if (((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((/*MAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.AbsMLR > MaxStroke) )
      {
         RetVal = FALSE;
      }

/*- Check plus reject absolute distance -*/

      if (((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
         (RunningPreset.AbsPLR > MaxStroke) )
      {
         RetVal = FALSE;
      }
   }

/*- Check step @ distance  (for release 3.0) -*/



/*- Check actuator clear distance -*/

   if (((RunningPreset.ActClrFlag & BIT0) == BIT0) &&
      ((/*OutputAtPosSw.mode*/ALLMODES & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
      (RunningPreset.ActClrDistance > MaxStroke) )
   {
      RetVal = FALSE;
   }

/*- Check missing part minimum distance -*/

   if ( (RunningPreset.MissingMinFlag == FALSE) &&    /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
      (RunningPreset.MissingPartMin > MaxStroke) )
   {
      RetVal = FALSE;
   }

/*- Check missing part maximum distance -*/

   if ( (RunningPreset.MissingMaxFlag == FALSE) &&    /*FALSE=On*/
      (RunningPreset.MissingPartFlag == TRUE) &&    /*TRUE =On*/
      (RunningPreset.CycleAbortFlag == TRUE) &&     /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
      (RunningPreset.MissingPartMax > MaxStroke) )
   {
      RetVal = FALSE;
   }

/*- Check absolute cutoff distance -*/

   if ( (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
      (RunningPreset.ABSCutoffFlag == FALSE) &&     /*FALSE=On*/
      ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
      (RunningPreset.ABSCutoffDist > MaxStroke) )
   {
      RetVal = FALSE;
   }

/*- Check pre-trigger distance -*/

   if ( (RunningPreset.PreTrigDistFlag == FALSE) && /*FALSE=On*/
      (RunningPreset.PreTrigFlag == TRUE) &&      /*TRUE =On*/
         ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) &&
      (RunningPreset.PreTrigDist > MaxStroke) )
   {
      RetVal = FALSE;
   }

   return(RetVal);
}



BOOLEAN CheckForValidForces(UINT32 MaximumForce)
/*--------------------------------------------------------------------------*/
/*  This function will check all force values against the maximum force     */
/*  which has been selected for this machine as defined by the passed arg.  */
/*  If any problems are found, a FALSE will be returned.  If all is okay    */
/*  then TRUE will be returned.                                             */
/*--------------------------------------------------------------------------*/
{
   BOOLEAN RetVal = TRUE;

/*----------  First check things which are Suspect limits  ----------*/

   if ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) {

/*- Check minus suspect weld force -*/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (((RunningPreset.SuspectLimits & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0) &&
            (RunningPreset.WeldForceMLS > MaximumForce) )
         {
            RetVal = FALSE;
         }
      }

/*- Check plus suspect weld force -*/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0) &&
            (RunningPreset.WeldForcePLS > MaximumForce) )
         {
            RetVal = FALSE;
         }
      }
   }

/*----------  Next check things which are reject limits  ----------*/

   if ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) {

/*- Check minus reject weld force -*/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (((RunningPreset.RejectLimits & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0) &&
            (RunningPreset.WeldForceMLR > MaximumForce) )
         {
            RetVal = FALSE;
         }
      }

/*- Check plus reject weld force -*/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0) &&
            (RunningPreset.WeldForcePLR > MaximumForce) )
         {
            RetVal = FALSE;
         }
      }
   }

/*-  Check trigger force  -*/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
      if (RunningPreset.TriggerForce > MaximumForce )
      {
         RetVal = FALSE;
      }
   }
   return(RetVal);
}
