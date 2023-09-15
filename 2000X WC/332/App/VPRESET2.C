/* $Header:   D:/databases/VMdb/2000Series/App/VPRESET2.C_V   1.25.1.0   Oct 18 2017 13:05:46   RCHAPA  $ */
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

   Module name:   VERIFY_PRESET_MODEL2  

   Filename:      vpreset2.c     

   Function Name: VerifyPresetModel2
  
        Written by:    Barry E. Kymer
      Date:          07-07-97
      Language:      "C"             

 ---------------------------------- REVISIONS -----------------------------

    Revision  Date      Author     Description
    ========  ========  =========  ===========
   1.0     07/07/97  BEKymer    Sort of removed from weld_obj.c
   1.1     07-14-97  BEKymer    Add in setup alarms for control level 2
   1.2     07-28-97  BEKymer    Remove unused variable - ModelMask
                                Use CurentSetup.ControlLevel
   1.3     07-31-97  BEKymer    Remove check for model vs control level
   1.4     08-01-97  BEKymer    Check PeakPwrCutoffFlag for SE59, SE65, SE66
                                and SE67
   1.5     08-25-97  BEKymer    Check Control limits flag for SE119
                                Fix .BitMask variable for many alarms
   1.6     08-29-97  BEKymer    Change 'less' to 'greater' on alarm SE172, SE173
   1.7     09-11-97  PaulG      Unit test and data cleanup
   1.8     09-12-97  LAM        made runningpreset to extern
   1.9     09-19-97  BEKymer    Add ControlLimitFlag check to all alarms which
                                check for EnergyCompFlag or PeakPwrCutoffFlag
   1.10    12-09-97  BEKymer    Added weld mode check for the following alarms:
                                SE74-SE85

-----------04-15-98--BEKymer----Start of code for release 2.5-----------------

   1.11    04-17-98  BEKymer    Added alarms: SE268
   1.12    06-29-98  BEKymer    Check menu structure to decide if the weldmode
                                is correct for alarms: SE3, SE4, SE5, SE6, 
                                SE11, SE12, SE78, SE80, SE81, SE84, SE85,
                                SE59, SE65, SE66, SE67
   1.13    07-17-98  BEKymer    Change amp step check to less then LEVEL_ea
                                instead of less then or equal to LEVEL_ea
                                Remove commented code
   1.14    08-12-98  BEKymer    Remove test for GROUND_DETECT mode in SE44
                                and SE45
   1.15.1.1 07-12-99 JZ         added ErrorCode to alarm SE268
   1.17     08-04-99 JZ         added ErrorCodeFlag
   1.18     08-06-99 JZ         added RecordErrorCode
   1.19     11-04-99 JZ         removed tabs
   1.20     11-05-99 JZ         aligned the code
   1.21     06-28-00 BEKymer    Changed all MODEL to LEVEL
   1.22     09-02-08 NHAhmed    CleanUp for multi-language support.
   1.24     10-18-12 JWANG      Added changes for absolute limits.

 ----------------------------- DESCRIPTION -------------------------------*/




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

UINT32 VerifyPresetModel2(void)
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
   UINT32 RetVal      = FALSE;
   UINT16 SuspectFlag = FALSE;
   UINT16 RejectFlag  = FALSE;

   RetVal = VerifyPresetModel1();

/*--------------------------------------------------------------------------*/
/*----    Here check for things which are mode specific                 ----*/
/*--------------------------------------------------------------------------*/

   switch (RunningPreset.WeldMode) {
      case TIMEMODE:

/*--  Check energy compensation minimum with energy compensation maximum  --*/

         if ((RunningPreset.EnergyCompFlag == TRUE) &&
            (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
            (RunningPreset.EnergyPL <= RunningPreset.EnergyML) )
         {
            RetVal = SE119;
            RecordSetupAlarm(RetVal);
         }
         break;

      case ENERGYMODE:
         break;

      case PKPOWERMODE:
         break;

      case ABSOLUTEMODE:
         break;

      case GRDDETECTMODE:
         break;

      case COLLAPSEMODE:
         break;

      case CONTINUOUSMODE:
         break;

      default:
         break;
   }

/*--------------------------------------------------------------------------*/
/*---  Here check for things which are not mode specific or not related  ---*/
/*---  to either suspect or reject limits.                               ---*/
/*--------------------------------------------------------------------------*/


/*--------------------------------------------------------------------------*/
/*--  Here are tests which are only valid when Suspect Limits are enabled --*/
/*--------------------------------------------------------------------------*/

   if (((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.WeldMode != CONTINUOUSMODE))
   {
      SuspectFlag = TRUE;

/*----   Check Suspect Limit    TIME   ----*/

      if (((RunningPreset.SuspectLimits & /*MTimeSEnergy.BitMask*/MTIMEBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PTimeSEnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.WeldMode != TIMEMODE) &&
         (RunningPreset.TimePLS <= RunningPreset.TimeMLS) )
      {
         RetVal = SE1;
         RecordSetupAlarm(RetVal);
      }

/*---   Check maximum timeout with minus suspect time limit   ---*/

      if (((RunningPreset.SuspectLimits & /*MTimeSEnergy.BitMask*/MTIMEBIT) == 0) &&
         (RunningPreset.WeldMode != TIMEMODE) &&
         (RunningPreset.TimeMLS >= RunningPreset.MaxTimeout) )
      {
         RetVal = SE50;
         RecordSetupAlarm(RetVal);
      }

/*---   Check maximum timeout with plus suspect time limit   ---*/

      if (((RunningPreset.SuspectLimits & /*PTimeSEnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.WeldMode != TIMEMODE) &&
         (RunningPreset.TimePLS >= RunningPreset.MaxTimeout) )
      {
         RetVal = SE58;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Suspect Limit   ENERGY  ----*/

      if (((RunningPreset.SuspectLimits &/*MEnergySTime.BitMask*/MENERGYBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         ((/*MEnergySTime.mode*/(ENERGYMODE | TIMEMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.EnergyPLS <= RunningPreset.EnergyMLS) )
      {
         RetVal = SE3;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Suspect Limit   PEAK POWER    ----*/

      if (((RunningPreset.SuspectLimits & /*MPkPowerSLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
         ((/*MPkPowerSLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PowerPLS <= RunningPreset.PowerMLS) )
      {
         RetVal = SE5;
         RecordSetupAlarm(RetVal);
      }

/*----   Check peak power cutoff with minus Suspect power Limit   ----*/

      if (((RunningPreset.SuspectLimits & /*MPkPowerSLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((/*MPkPowerSLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PeakPwrCutoffFlag == FALSE) &&  /*FALSE=On*/
         (RunningPreset.ControlLimitsFlag == TRUE) &&   /*TRUE =On*/
         (RunningPreset.PowerMLS >= RunningPreset.PeakPwrCutoff) )
      {
         RetVal = SE66;
         RecordSetupAlarm(RetVal);
      }

/*----   Check peak power cutoff with plus Suspect power Limit   ----*/

      if (((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
          ((/*PPkPowerSLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
          (RunningPreset.PeakPwrCutoffFlag == FALSE) &&  /*FALSE=On*/
          (RunningPreset.ControlLimitsFlag == TRUE) &&   /*TRUE =On*/
          (RunningPreset.PowerPLS >= RunningPreset.PeakPwrCutoff) )
      {
          RetVal = SE67;
          RecordSetupAlarm(RetVal);
      }

/*----   Check Suspect Limit   COLLAPSE DISTANCE    ----*/

      if (((RunningPreset.SuspectLimits & /*MColDistSLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PColDistSLimit.BitMask*/PCOLDISTBIT) == 0) &&
         ((/*MColDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ColPLS <= RunningPreset.ColMLS) )
      {
         RetVal = SE12;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Suspect Limit   ABSOLUTE DISTANCE    ----*/

      if (((RunningPreset.SuspectLimits & /*MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*MColDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.AbsPLS <= RunningPreset.AbsMLS) )
      {
         RetVal = SE10;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Suspect Limit   TRIGGER DISTANCE    ----*/

      if (((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.TrsDistPLS <= RunningPreset.TrsDistMLS) )
      {
         RetVal = SE45;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect energy limit with energy compensation min value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.WeldMode == TIMEMODE)   &&
         ((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLS <= RunningPreset.EnergyML) )
      {
         RetVal = SE171;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus suspect energy limit with energy compensation min value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.WeldMode == TIMEMODE) &&
         ((RunningPreset.SuspectLimits & /*MEnergySTime.BitMask*/MENERGYBIT) == 0) &&
         (RunningPreset.EnergyMLS <= RunningPreset.EnergyML) )
      {
         RetVal = SE265;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus suspect energy limit with energy compensation max value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.WeldMode == TIMEMODE) &&
         ((RunningPreset.SuspectLimits & /*MEnergySTime.BitMask*/MENERGYBIT) == 0) &&
         (RunningPreset.EnergyMLS >= RunningPreset.EnergyPL) )
      {
         RetVal = SE173;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect energy limit with energy compensation max value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.WeldMode == TIMEMODE) &&
         ((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLS >= RunningPreset.EnergyPL) )
      {
         RetVal = SE267;
         RecordSetupAlarm(RetVal);
      }
   }


/*--------------------------------------------------------------------------*/
/*--  Here are tests which are only valid when Reject Limits are enabled  --*/
/*--------------------------------------------------------------------------*/

   if (((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.WeldMode != CONTINUOUSMODE))
   {
      RejectFlag = TRUE;

/*----   Check Reject Limit    TIME   ----*/

      if (((RunningPreset.RejectLimits & /*MTimeREnergy.BitMask*/MTIMEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PTimeREnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.WeldMode != TIMEMODE) &&
         (RunningPreset.TimePLR <= RunningPreset.TimeMLR) )
      {
         RetVal = SE2;
         RecordSetupAlarm(RetVal);
      }

/*---   Check maximum timeout with plus reject time limit   ---*/

      if (((RunningPreset.RejectLimits & /*PTimeREnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.WeldMode != TIMEMODE) &&
         (RunningPreset.TimePLR >= RunningPreset.MaxTimeout) )
      {
         RetVal = SE49;
         RecordSetupAlarm(RetVal);
      }

/*---   Check maximum timeout with minus reject time limit   ---*/

      if (((RunningPreset.RejectLimits & /*MTimeREnergy.BitMask*/MTIMEBIT) == 0) &&
         (RunningPreset.WeldMode != TIMEMODE) &&
         (RunningPreset.TimeMLR >= RunningPreset.MaxTimeout) )
      {
         RetVal = SE51;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Reject Limit   ENERGY  ----*/

      if (((RunningPreset.RejectLimits & /*MEnergyRTime.BitMask*/MENERGYBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         ((/*MEnergyRTime.mode*/(ENERGYMODE | TIMEMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.EnergyPLR <= RunningPreset.EnergyMLR) )
      {
         RetVal = SE4;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Reject Limit   PEAK POWER    ----*/

      if (((RunningPreset.RejectLimits & /*MPkPowerRLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
         ((/*MPkPowerRLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PowerPLR <= RunningPreset.PowerMLR) )
      {
         RetVal = SE6;
         RecordSetupAlarm(RetVal);
      }

/*---   Check peak power cutoff with minus reject power limit   ---*/

      if (((RunningPreset.RejectLimits & /*MPkPowerRLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((/*MPkPowerRLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PeakPwrCutoffFlag == FALSE) &&  /*FALSE=On*/
         (RunningPreset.ControlLimitsFlag == TRUE) &&   /*TRUE =On*/
         (RunningPreset.PowerMLR >= RunningPreset.PeakPwrCutoff) )
      {
         RetVal = SE59;
         RecordSetupAlarm(RetVal);
      }

/*---   Check peak power cutoff with plus reject power limit   ---*/

      if (((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
         ((/*PPkPowerRLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PeakPwrCutoffFlag == FALSE) &&  /*FALSE=On*/
         (RunningPreset.ControlLimitsFlag == TRUE) &&   /*TRUE =On*/
         (RunningPreset.PowerPLR >= RunningPreset.PeakPwrCutoff) )
      {
         RetVal = SE65;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Reject Limit   COLLAPSE DISTANCE    ----*/

      if (((RunningPreset.RejectLimits & /*MColDistRLimit.BitMask*/MCOLDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PColDistRLimit.BitMask*/PCOLDISTBIT) == 0) &&
         ((/*MColDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.ColPLR <= RunningPreset.ColMLR) )
      {
         RetVal = SE11;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Reject Limit   ABSOLUTE DISTANCE    ----*/

      if (((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
         ((/*MColDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.AbsPLR <= RunningPreset.AbsMLR) )
      {
         RetVal = SE9;
         RecordSetupAlarm(RetVal);
      }

/*----   Check Reject Limit   TRIGGER DISTANCE    ----*/

      if (((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
         ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.TrsDistPLR <= RunningPreset.TrsDistMLR) )
      {
         RetVal = SE44;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject energy limit with energy compensation min value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.WeldMode == TIMEMODE) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLR <= RunningPreset.EnergyML) )
      {
         RetVal = SE170;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject energy limit with energy compensation min value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.WeldMode == TIMEMODE) &&
         ((RunningPreset.RejectLimits & /*MEnergyRTime.BitMask*/MENERGYBIT) == 0) &&
         (RunningPreset.EnergyMLR <= RunningPreset.EnergyML) )
      {
         RetVal = SE264;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject energy limit with energy compensation max value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.WeldMode == TIMEMODE) &&
         ((RunningPreset.RejectLimits & /*MEnergyRTime.BitMask*/MENERGYBIT) == 0) &&
         (RunningPreset.EnergyMLR >= RunningPreset.EnergyPL) )
      {
         RetVal = SE172;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject energy limit with energy compensation max value  ---*/

      if ((RunningPreset.EnergyCompFlag == TRUE) &&
         (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
         (RunningPreset.WeldMode == TIMEMODE) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         (RunningPreset.EnergyPLR >= RunningPreset.EnergyPL) )
      {
         RetVal = SE266;
         RecordSetupAlarm(RetVal);
      }
   }


/*---  Here are tests for when BOTH reject and suspect limits are on  ---*/
      
   if ((SuspectFlag == TRUE) && (RejectFlag == TRUE))
   {

/*---  Check plus reject time limit with minus suspect time limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MTimeSEnergy.BitMask*/MTIMEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PTimeREnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.WeldMode != TIMEMODE) &&
         (RunningPreset.TimePLR <= RunningPreset.TimeMLS) )
      {
         RetVal = SE74;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect time limit with minus reject time limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PTimeSEnergy.BitMask*/PTIMEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MTimeREnergy.BitMask*/MTIMEBIT) == 0) &&
         (RunningPreset.WeldMode != TIMEMODE) &&
         (RunningPreset.TimePLS <= RunningPreset.TimeMLR) )
      {
         RetVal = SE75;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject time limit with plus suspect time limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PTimeSEnergy.BitMask*/PTIMEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PTimeREnergy.BitMask*/PTIMEBIT) == 0) &&
         (RunningPreset.WeldMode != TIMEMODE) &&
         (RunningPreset.TimePLR <= RunningPreset.TimePLS) )
      {
         RetVal = SE76;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject time limit with minus suspect time limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MTimeSEnergy.BitMask*/MTIMEBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MTimeREnergy.BitMask*/MTIMEBIT) == 0) &&
         (RunningPreset.WeldMode != TIMEMODE) &&
         (RunningPreset.TimeMLR >= RunningPreset.TimeMLS) )
      {
         RetVal = SE77;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject energy limit with minus suspect energy limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MEnergySTime.BitMask*/MENERGYBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         ((/*MEnergySTime.mode*/(ENERGYMODE | TIMEMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.EnergyPLR <= RunningPreset.EnergyMLS) )
      {
         RetVal = SE78;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect energy limit with minus reject energy limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MEnergyRTime.BitMask*/MENERGYBIT) == 0) &&
         ((/*MEnergyRTime.mode*/(ENERGYMODE | TIMEMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.EnergyPLS <= RunningPreset.EnergyMLR) )
      {
         RetVal = SE79;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject energy limit with plus suspect energy limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
         ((/*PEnergySTime.mode*/(ENERGYMODE | TIMEMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.EnergyPLR <= RunningPreset.EnergyPLS) )
      {
         RetVal = SE80;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject energy limit with minus suspect energy limit  ---*/

      if (((RunningPreset.SuspectLimits &/*MEnergyRTime.BitMask*/MENERGYBIT) == 0) &&
         ((/*MEnergySTime.mode*/(ENERGYMODE | TIMEMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.EnergyMLR >= RunningPreset.EnergyMLS) )
      {
         RetVal = SE81;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject peak power limit with minus suspect peak power limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MPkPowerSLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
         ((/*MPkPowerSLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PowerPLR <= RunningPreset.PowerMLS) )
      {
         RetVal = SE82;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus suspect peak power limit with minus reject peak power limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MPkPowerRLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((/*PPkPowerSLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PowerPLS <= RunningPreset.PowerMLR) )
      {
         RetVal = SE84;
         RecordSetupAlarm(RetVal);
      }

/*---  Check plus reject peak power limit with plus suspect peak power limit  ---*/

      if (((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
         ((/*PPkPowerSLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PowerPLR <= RunningPreset.PowerPLS) )
      {
         RetVal = SE83;
         RecordSetupAlarm(RetVal);
      }

/*---  Check minus reject peak power limit with minus suspect peak power limit  ---*/

      if (((RunningPreset.SuspectLimits & /*MPkPowerSLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((RunningPreset.RejectLimits & /*MPkPowerRLimit.BitMask*/MPKPOWERBIT) == 0) &&
         ((/*MPkPowerSLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE | GRDDETECTMODE ) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
         (RunningPreset.PowerMLR >= RunningPreset.PowerMLS) )
      {
         RetVal = SE85;
         RecordSetupAlarm(RetVal);
      }
   }

/*--------------------------------------------------------------------------*/
/*----    Finally check for things which are only allowed in            ----*/
/*----    control level 3 or above.                                     ----*/
/*--------------------------------------------------------------------------*/


/*---  Check for amplitude stepping  ---*/

   if (CurrentSetup.ControlLevel < LEVEL_ea)
   {
      if ((RunningPreset.Amp2Flag & BIT0) == BIT0)
      {
         RecordErrorCode( ERRORCODE2_SE268 );
         RetVal = SE268;
         RecordSetupAlarm(RetVal);
      }
   }
   return(RetVal);
}



