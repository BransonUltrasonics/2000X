/* $Header:   D:/SWLab/VMdb/2000Series/App/VPRESET5.C_V   1.29   10 Sep 2009 15:59:38   bkymer  $ */
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

   Module name:   VERIFY_PRESET_MODEL5  

   Filename:      vpreset5.c     

   Function Name: VerifyPresetModel5
  
        Written by:    Barry E. Kymer
      Date:          07-07-97
      Language:      "C"

 ---------------------------------- REVISIONS -----------------------------

    Revision  Date      Author     Description
    ========  ========  =========  ===========
      1.0     07/07/97  BEKymer    Sort of removed from weld_obj.c
   1.2     07-28-97  BEKymer    Remove unused variable - ModelMask
                                Use CurentSetup.ControlLevel
   1.4     09-12-97  LAM        made runningpreset to extern

-----------04-15-98--BEKymer----Start of code for release 2.5-----------------

   1.5     04-20-98  BEKymer    Move max force alarms into vpreset4.c
   1.6     03-17-99  LAM        divided trigger force for f0 only

   1.7     06-04-99  OFI        Wrote code for setup alarms for "F" product

   1.9     06--8-99  JZ         Added call to SetMAxMinValues(),
                                BuildVelocityTable() and BuildForceTable()
   1.10    06-10-99  OFI        It will fix bugs               
   1.11    06-11-99  OFI        Added SE230, fixed SE111 and 262.
   1.12    06-17-99  OFI        Fixed SE230 changed >= to <=.
   1.12.1.1 07-08-99 JZ         fixed SE277  -->  PRESSURE_TOLLERANCE_SE277
                                fixed SE202, 203, fixed SE209 per DCS #3075
   1.14     08-04-99 JZ         removed extern ErrorCode
   1.15     08-20-99 JZ         fixed DCS issue #3104
   1.16     09-03-99 JZ         taken out BuildVelocityTable()
   1.17     11-02-99 OFI        changed tabs to spaces per coding standarts and fixed alarm SE247
   1.18     11-05-99 OFI        fixed alarm SE247
   1.19     11-06-99 OFI        fixed alignment        
   1.20     03-09-00 JZ         fixed SE277 alarm to be for control 5 only   
   1.21     06-26-00 DJL        Made a few global name changes from Preset.MaxForce to Preset.WeldForce
                                changed MODEL to LEVEL
   1.22     08-22-00 JLH        Added code to give invalid preset for trigger force, +/-suspect limit, and +/-reject limit
                                 that are out of bounds.   
   1.23     08-31-00 BEKymer    In places where checking for ERRORCODE6_SE268 make
                                 sure proper suspect or reject limit is in fact
                                 turned on.  Also make sure reject or suspect limit
                                 globally is turned on.  Changed from using
                                 CurrentPreset to RunningPreset in same checks.
   1.24     11-14-00 BEKymer    Make tests for LEVEL_f >= to take into account LEVEL_TEST
   1.25     01-18-07 NHAhmed    Changes for Setup Alarm SE298.
   1.26     03-20-07 NHAhmed    Changes for Setup Alarm SE112, SE113,SE114,
                                SE115, SE122, SE229,SE232,SE236,SE258 
   1.27     03-30-07 YGupta     Moved VQS related setup alarms to vpreset1.c as VerifyPresetModel5 
                                function will call only for ControlLevel f.
   1.28     09-02-08 NHAhmed    CleanUp for multi-language support.
   1.29     09-10-09 BEkymer    Add new define MICRO where needed

 ----------------------------- DESCRIPTION -------------------------------*/




/* ------------------------------ INCLUDE FILES ----------------------------*/

#include <psos.h>                /* for access to pSOS routines          */
#include <prepc.h>
#include "state.h"
#include "error.h"
#include "preset.h"
#include "param.h"
#include "limits.h"
#include "ready.h"
#include "alarms.h"
#include "sc.h"
#include "vpreset1.h"
#include "vpreset2.h"
#include "vpreset3.h"
#include "vpreset4.h"
#include "vpreset5.h"
#include "actnvram.h"
#include "snsrcalb.h"
#include "menu1.h"
#include "weld_obj.h"



/*------------------------------ WELD OBJECT DATA --------------------------*/



extern SETUPS_Ver800 RunningPreset,CurrentPreset,MaxLimit,MinLimit;
extern WELD_DATA FinalResults;


extern CONFIGSETUP CurrentSetup;

extern SINT32 MaximumForce;
extern SINT32 HomePressure;           /* Home pressure                  */





UINT32 VerifyPresetModel5(void)
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
                  


   RetVal = VerifyPresetModel4();

   MaximumForce = GetMaxForce();



/*----   Make sure trigger value is less then weld force  -----*/

   if ((CurrentSetup.Actuator == AEF)&&
      (RunningPreset.TriggerForce >= RunningPreset.WeldForce)) {
      RetVal = SE73;
      RecordSetupAlarm(RetVal);
   }
/* Force Step Conflicts with Collapse Cutoff */  
    
   if ((CurrentSetup.Actuator == AEF)&&
      ((/*CollapseCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtCol.BitMask*/BIT5) == 0) &&
      (RunningPreset.ControlLimitsFlag == TRUE)  &&   /*TRUE =On*/
      (RunningPreset.ColCutoffFlag == FALSE) &&  /*FALSE=On*/
      (RunningPreset.ColCutoffDist <= RunningPreset.ForceTrigColValue)){
      RetVal = SE111;
      RecordSetupAlarm(RetVal);
   }  


 /* Rapid Traverse conflicts with -Reject Absolute Distance Limit   */
 
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((/*MAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.RejectLimits & /*MAbsDistRLimit.BitMask*/MABSDISTBIT) == 0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.AbsMLR) ) {
      RetVal = SE177;
      RecordSetupAlarm(RetVal);
   }  
       
 /* RT Conflicts with -Suspect Absolute Distance Limit */
 
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.SuspectLimits &/* MAbsDistSLimit.BitMask*/MABSDISTBIT) == 0) &&
      ((/*MAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.AbsMLS) ) {
      RetVal = SE179;
      RecordSetupAlarm(RetVal);
   }                          
 /* RT Conflicts with + Reject Absolute Distance limit */
 
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.RejectLimits & /*PAbsDistRLimit.BitMask*/PABSDISTBIT) == 0) &&
      ((/*PAbsDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.AbsPLR) ) {
      RetVal = SE181;
      RecordSetupAlarm(RetVal);
    }
  
  /* RT Conflicts with +Suspect Absolute Distance Limit */  
  
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.SuspectLimits & /*PAbsDistSLimit.BitMask*/PABSDISTBIT) == 0) &&
      ((/*PAbsDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.AbsPLS) ) {
      RetVal = SE183;
      RecordSetupAlarm(RetVal);
   }
  
  /* RT Conflicts with +Reject Trigger Distance Limit */  
  
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.RejectLimits &/*PTrigDistRLimit.BitMask*/PTRIGDISTBIT) == 0) &&
      ((/*PTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.TrsDistPLR) ) {
      RetVal = SE184;
      RecordSetupAlarm(RetVal);
   }
                             
  /*  RT Conflicts with +Suspect Trigger Distance Limit */  
  
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.SuspectLimits & /*PTrigDistSLimit.BitMask*/PTRIGDISTBIT) == 0) &&
      ((/*PTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.TrsDistPLS) ) {
      RetVal = SE185;
      RecordSetupAlarm(RetVal);
   }

  /* RT Conflicts with -Reject Trigger Distance Limit */  
  
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.RejectLimits & /*MTrigDistRLimit.BitMask*/MTRIGDISTBIT) == 0) &&
      ((/*MTrigDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.TrsDistMLR) ) {
      RetVal = SE186;
      RecordSetupAlarm(RetVal);
   }
 
 /* RT Conflicts with -Suspect Trigger Distance Limit */  
  
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      ((RunningPreset.SuspectLimits & /*MTrigDistSLimit.BitMask*/MTRIGDISTBIT) == 0) &&
      ((/*MTrigDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.RTDist >= RunningPreset.TrsDistMLS) ) {
      RetVal = SE187;
      RecordSetupAlarm(RetVal);
   }

/* RT Conflicts with Absolute Cutoff Distance Limit */  
  
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) &&
      (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
      ((RunningPreset.ABSCutoffFlag & /*ABSCutoff.BitMask*/BIT0) == 0)&&
      ((/*ABSCutoff.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      (RunningPreset.RTDist >= RunningPreset.ABSCutoffDist ) ) {
      RetVal = SE193;
      RecordSetupAlarm(RetVal);
   } 

/* RT Conflicts with Absolute Distance Setting */  
  
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RTFlag & BIT0) == BIT0) && 
      ((/*AbsoluteAbs.mode*/ABSOLUTEMODE & RunningPreset.WeldMode) == RunningPreset.WeldMode)&&
      (RunningPreset.RTDist >= RunningPreset.AbsDist ) ) {
      RetVal = SE194;
      RecordSetupAlarm(RetVal);
   } 
 
/* Weld Force conflicts with +Reject Weld Force Limit */

   if ((CurrentSetup.Actuator == AEF)&&
      ((/*PMaxForceRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & BIT0) != BIT0) &&
      (RunningPreset.WeldForce >= RunningPreset.WeldForcePLR)){
      RetVal = SE200;
      RecordSetupAlarm(RetVal);
   } 

/* Weld Force conflicts with +Suspect Weld Force Limit */

   if ((CurrentSetup.Actuator == AEF)&&
      ((/*PMaxForceSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & BIT0) != BIT0) && 
      (RunningPreset.WeldForce >= RunningPreset.WeldForcePLS)){
      RetVal = SE201;
      RecordSetupAlarm(RetVal);
   } 

/* Weld Force conflicts with -Reject Weld Force Limit */

   if ((CurrentSetup.Actuator == AEF)&&
      ((/*MMaxForceRLimit.mode */(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE)& RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.RejectLimits & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & BIT0) != BIT0) &&
      (RunningPreset.WeldForce <= RunningPreset.WeldForceMLR)){
      RetVal = SE202;
      RecordSetupAlarm(RetVal);
   } 

  /* Weld Force conflicts with -Suspect Weld Force Limit */

   if ((CurrentSetup.Actuator == AEF)&&
      ((/*MMaxForceSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.SuspectLimits & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & BIT0) != BIT0) &&
      (RunningPreset.WeldForce <= RunningPreset.WeldForceMLS)){
      RetVal = SE203;
      RecordSetupAlarm(RetVal);
   } 
      
/* Force B conflicts with +Reject Weld Force Limit */

   if ((CurrentSetup.Actuator == AEF)&&
      ((/*PMaxForceRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.Force2 >= RunningPreset.WeldForcePLR)){
      RetVal = SE204;
      RecordSetupAlarm(RetVal);
   } 

/* ForceB conflicts with +Suspect Weld Force Limit */

   if ((CurrentSetup.Actuator == AEF)&&
      ((/*PMaxForceSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/PFORCEBIT) == 0) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.Force2>= RunningPreset.WeldForcePLS)){
      RetVal = SE205;
      RecordSetupAlarm(RetVal);
   } 
/* ForceB conflicts with -Reject Weld Force Limit */

   if ((CurrentSetup.Actuator == AEF)&&
      ((/*MMaxForceRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.RejectLimits & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.Force2 <= RunningPreset.WeldForceMLR)){
      RetVal = SE206;
      RecordSetupAlarm(RetVal);
   } 
 /* ForceB conflicts with -Suspect Weld Force Limit */

   if ((CurrentSetup.Actuator == AEF)&&
      ((/*MMaxForceSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE | GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.SuspectLimits & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.Force2 <= RunningPreset.WeldForceMLS)){
      RetVal = SE207;
      RecordSetupAlarm(RetVal);
   } 
 /* Force Step Conflicts with +Reject Peak Power Limit */  
    
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RejectLimits & /*PPkPowerRLimit.BitMask*/PPKPOWERBIT) == 0) &&
      ((/*PPkPowerRLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtPower.BitMask*/BIT4) == 0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.PowerPLR <= RunningPreset.ForceTrigPowerValue)){
      RetVal = SE208;
      RecordSetupAlarm(RetVal);
   } 
      
 /* Force Step Conflicts with +Suspect Peak Power Limit */  
    
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.SuspectLimits & /*PPkPowerSLimit.BitMask*/PPKPOWERBIT) == 0) &&
      ((/*PPkPowerSLimit.mode*/(TIMEMODE | ENERGYMODE | COLLAPSEMODE | ABSOLUTEMODE | CONTINUOUSMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtPower.BitMask*/BIT4) == 0) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.PowerPLS <= RunningPreset.ForceTrigPowerValue)){
      RetVal = SE209;
      RecordSetupAlarm(RetVal);
   } 
      
 /* Force Step Conflicts with +Reject Energy Limit */  
    
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.RejectLimits & /*PEnergyRTime.BitMask*/PENERGYBIT) == 0) &&
      ((/*PEnergyRTime.mode*/(ENERGYMODE | TIMEMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtEner.BitMask*/BIT3) == 0) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.EnergyPLR <= RunningPreset.ForceTrigEnerValue)){
      RetVal = SE214;
      RecordSetupAlarm(RetVal);
   }                                                               
 
  /* Force Step Conflicts with +Suspect Energy Limit */ 
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.SuspectLimits & /*PEnergySTime.BitMask*/PENERGYBIT) == 0) &&
      ((/*PEnergySTime.mode*/(ENERGYMODE | TIMEMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtEner.BitMask*/BIT3) == 0) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.EnergyPLS <= RunningPreset.ForceTrigEnerValue)){
      RetVal = SE217;
      RecordSetupAlarm(RetVal);
   }
        
        
/* Force Step Conflicts with -Reject Collapse Distance Limit */  
    
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtCol.BitMask*/BIT5) == 0) &&
      ((RunningPreset.RejectLimits & /*MColDistRLimit.BitMask*/MCOLDISTBIT) == 0) &&
      ((/*MColDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.ColMLR >= RunningPreset.ForceTrigColValue)){
      RetVal = SE219;
      RecordSetupAlarm(RetVal);
   }                          
 
 /* Force Step Conflicts with -Suspect Collapse Distance Limit */  
    
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtCol.BitMask*/BIT5) == 0) &&
      ((RunningPreset.SuspectLimits & /*MColDistSLimit.BitMask*/MCOLDISTBIT) == 0) &&
      ((/*MColDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.ColMLS >= RunningPreset.ForceTrigColValue)){
      RetVal = SE227;
      RecordSetupAlarm(RetVal);
   }                           




/* Force Step Conflicts with +Reject Collapse Distance Limit */  
    
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtCol.BitMask*/BIT5) == 0) &&
      ((RunningPreset.RejectLimits & /*PColDistRLimit.BitMask*/PCOLDISTBIT) == 0) &&
      ((/*PColDistRLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.ColPLR <= RunningPreset.ForceTrigColValue)){
      RetVal = SE230;
      RecordSetupAlarm(RetVal);
   }                          



 
  /* Force Step Conflicts with +Suspect Collapse Distance Limit */  
    
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtCol.BitMask*/BIT5) == 0) &&
      ((RunningPreset.SuspectLimits & /*PColDistSLimit.BitMask*/PCOLDISTBIT) == 0) &&
      ((/*PColDistSLimit.mode*/(TIMEMODE | ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) &&
      ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&
      (RunningPreset.ColPLS <= RunningPreset.ForceTrigColValue)){
      RetVal = SE233;
      RecordSetupAlarm(RetVal);
   }                     
  
  
  /* Force Step Conflicts with Peak Power Cutoff */  
    
   if ((CurrentSetup.Actuator == AEF)&&
      (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
      (RunningPreset.PeakPwrCutoffFlag == FALSE) && /*FALSE=On*/
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtPower.BitMask*/BIT4) == 0) &&
      (RunningPreset.WeldMode != PKPOWERMODE) &&
      (RunningPreset.PeakPwrCutoff <= RunningPreset.ForceTrigPowerValue)){
      RetVal = SE239;
      RecordSetupAlarm(RetVal);
   } 
  
  
  /* Force Step Conflicts with Peak Power Settings */  
    
   if ((CurrentSetup.Actuator == AEF)&&
      (RunningPreset.WeldMode == PKPOWERMODE) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtPower.BitMask*/BIT4) == 0) &&
      (RunningPreset.PeakPwr <= RunningPreset.ForceTrigPowerValue)){
      RetVal = SE240;
      RecordSetupAlarm(RetVal);
   } 

   /* Force Step Conflicts with Energy Settings */ 
   if ((CurrentSetup.Actuator == AEF)&&
      (RunningPreset.WeldMode == ENERGYMODE) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtEner.BitMask*/BIT3) == 0) &&
      (RunningPreset.WeldEnergy <= RunningPreset.ForceTrigEnerValue)){
      RetVal = SE241;
      RecordSetupAlarm(RetVal);
   }
        
        
   /* Force Step Conflicts with Energy Compensation */ 
  
   if ((CurrentSetup.Actuator == AEF)&&
      (RunningPreset.WeldMode == TIMEMODE) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtEner.BitMask*/BIT3) == 0) &&
      (RunningPreset.EnergyCompFlag == TRUE) &&
      (RunningPreset.ControlLimitsFlag == TRUE) &&  /*TRUE =On*/
      (RunningPreset.EnergyPL <= RunningPreset.ForceTrigEnerValue)){
      RetVal = SE242;
      RecordSetupAlarm(RetVal);
   }


  /* Force Step Conflicts with Weld Time */  

   if ((CurrentSetup.Actuator == AEF)&&
      (RunningPreset.WeldMode == TIMEMODE) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtTime.BitMask*/BIT2) == 0) &&
      (RunningPreset.WeldTime <= RunningPreset.ForceTrigTimeValue)){
      RetVal = SE243;
      RecordSetupAlarm(RetVal);
   }

  /* WeldForce A Cannot Be Reached Because Set Pressure is 60PSi/41kPa  */
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      (RunningPreset.WeldForce > MaximumForce)){
      RetVal = SE245;
      RecordSetupAlarm(RetVal);
   }

  /* WeldForce B Cannot Be Reached Because Set Pressure is 60PSi/41kPa  */
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      (RunningPreset.Force2 > MaximumForce)){
      RetVal = SE246;
      RecordSetupAlarm(RetVal);
   }
   
  /* HoldForce Cannot Be Reached Because Set Pressure is 60PSi/41kPa  */
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.HoldTimeFlag & BIT0) == FALSE)&&
      (RunningPreset.HoldForce > MaximumForce)){
      RetVal = SE247;
      RecordSetupAlarm(RetVal);
   }
  

   
  /* Force Step Conflicts with Maximum Weld Time */  

   if ((CurrentSetup.Actuator == AEF)&&
      (RunningPreset.WeldMode != TIMEMODE) &&
      ((RunningPreset.Force2Flag & BIT0) == BIT0) &&
      ((RunningPreset.Force2Flag & /*ForceStepAtTime.BitMask*/BIT2) == 0) &&
      (RunningPreset.MaxTimeout <= RunningPreset.ForceTrigTimeValue)){
      RetVal = SE260;
      RecordSetupAlarm(RetVal);
   }
   
  /*  WeldForce Cannot Be Reached Because Set Pressure is 60PSi/41kPa  */
 
   if ((CurrentSetup.Actuator == AEF)&&
      ((RunningPreset.Force2Flag & BIT0) != BIT0)&&
      (RunningPreset.WeldForce > MaximumForce)){
      RetVal = SE262;
      RecordSetupAlarm(RetVal);
   }
     
  /* Check for incorrect trigger force */

   if ( ( (CurrentSetup.Actuator == AEF) ||
          (CurrentSetup.Actuator == AED) ||
          (CurrentSetup.Actuator == MICRO) ) &&
        (RunningPreset.TriggerForce < CurrentSetup.MinTrigForce || RunningPreset.TriggerForce > MaxLimit.TriggerForce) )
   {
      RetVal = SE298;
      RecordSetupAlarm(RetVal);
   }   

  /* Check for incorrect +suspect limit force */
   
   if ( (CurrentSetup.Actuator == AEF) && 
        ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&                   /* Added to fix issue # 3528 */
        ((RunningPreset.SuspectLimits & /*PMaxForceSLimit.BitMask*/MFORCEBIT) == 0) &&       /* Added to fix issue # 3528 */
        (RunningPreset.WeldForcePLS < MinLimit.WeldForcePLS || RunningPreset.WeldForcePLS > MaxLimit.WeldForcePLS) )
   {
      RecordErrorCode( ERRORCODE6_SE268 );
      RetVal = SE268;
      RecordSetupAlarm(RetVal);
   }   

  /* Check for incorrect -suspect limit force */
   
   if ( (CurrentSetup.Actuator == AEF) &&
        ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) &&                   /* Added to fix issue # 3528 */
        ((RunningPreset.SuspectLimits & /*MMaxForceSLimit.BitMask*/MFORCEBIT) == 0) &&       /* Added to fix issue # 3528 */
        (RunningPreset.WeldForceMLS < MinLimit.WeldForceMLS || RunningPreset.WeldForceMLS > MaxLimit.WeldForceMLS) )
   {
      RecordErrorCode( ERRORCODE6_SE268 );
      RetVal = SE268;
      RecordSetupAlarm(RetVal);
   }   

  /* Check for incorrect +reject limit force */
   
   if ( (CurrentSetup.Actuator == AEF) &&
        ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&                   /* Added to fix issue # 3528 */
        ((RunningPreset.RejectLimits & /*PMaxForceRLimit.BitMask*/PFORCEBIT) == 0) &&       /* Added to fix issue # 3528 */
        (RunningPreset.WeldForcePLR < MinLimit.WeldForcePLR || RunningPreset.WeldForcePLR > MaxLimit.WeldForcePLR) )
   {
      RecordErrorCode( ERRORCODE6_SE268 );
      RetVal = SE268;
      RecordSetupAlarm(RetVal);
   }   

  /* Check for incorrect -reject limit force */
   
   if ( (CurrentSetup.Actuator == AEF) &&
        ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) &&                   /* Added to fix issue # 3528 */
        ((RunningPreset.RejectLimits & /*MMaxForceRLimit.BitMask*/MFORCEBIT) == 0) &&       /* Added to fix issue # 3528 */
        (RunningPreset.WeldForceMLR < MinLimit.WeldForceMLR || RunningPreset.WeldForceMLR > MaxLimit.WeldForceMLR) )
   {
      RecordErrorCode( ERRORCODE6_SE268 );
      RetVal = SE268;
      RecordSetupAlarm(RetVal);
   }   

  /* System Pressure Incorrect */
  
   if ((CurrentSetup.Actuator == AEF) && (CurrentSetup.ControlLevel >= LEVEL_f)){
      switch (RunningPreset.SetPressure){
         case TRUE:       // 80 PSI
            if( ((HIGH_PRESSURE - PRESSURE_TOLLERANCE_SE277) > HomePressure) ||
              ( (HIGH_PRESSURE + PRESSURE_TOLLERANCE_SE277)  < HomePressure)){
               RetVal = SE277;
               RecordSetupAlarm(RetVal);
            }
            break;
         case FALSE:       // 60 PSI
            if( ((LOW_PRESSURE - PRESSURE_TOLLERANCE_SE277) > HomePressure) ||
              ( ( LOW_PRESSURE + PRESSURE_TOLLERANCE_SE277)  < HomePressure)){
               RetVal = SE277;
               RecordSetupAlarm(RetVal);
            }
            break;
      }
   }                    
      
   
   
/*--------------------------------------------------------------------------*/
/*----    Here check for things which are mode specific                 ----*/
/*-------------------------------------------------------------------------- */

/*   switch (RunningPreset.WeldMode) {    
      case TIMEMODE:
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
            break;  */
   
   SetMaxMinValues();
   return(RetVal);
   }
   

  