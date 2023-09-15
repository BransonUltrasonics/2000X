/* $Header:   D:/SWLab/VMdb/2000Series/App/LIMITS.C_V   1.27   10 Sep 2009 15:59:32   bkymer  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

/*--------------------------- MODULE DESCRIPTION ---------------------------

   Module name: PROCESS_LIMITS  

   Filename:    limits.c     

   Function Name: 
  
   Written by:   Barry E. Kymer
         Date:         04/18/96
         Language:     "C"

 ---------------------------------- REVISIONS -----------------------------

    Revision    Date      Author      Description
    ========    ========  =========   ===========
    1.0      04/18/96  Mark L      Initial Shell
    1.3      07-07-97  BEKymer     CheckProcessLimits removed from weld_obj.c
    1.4      07-11-97  BEKymer     Include ready.h for RecordAlarm prototpye
    1.5      07-28-97  BEKymer     Remove unused variable - ModelMask
    1.6      09.09.97  JBerman     Added default into the case statement 
    1.7      09.12.97  LAM         made running preset extern            
    1.8      10-29-97  BEKymer     Check amp control = internal before alarming
    1.9      11-18-97  LAM         replaced finalresults with weldingresults
    1.10     04-27-98  BEKymer     Test CurrentActuator for AEF or AED instead
                                   of EP.
    1.11     06-22-98  BEKymer     Change structure member ActualForceMax
                                   to WeldForceMax 
    1.12     07-10-98  BEKymer     Remove unused case for TECMODE
    1.13     08-10-98  BEKymer     Rename ActualCollapse to ActualTotalCollapse
    1.14     05-11-99  LAM         typecasted ~BITS to eliminate warnings with DIAB
    1.15     05-14-99  JZ          changed WeldForceMax to WeldForceEnd
    1.15.1.1 06-29-99  JZ          added Force Stepping alarms
    1.17     11-02-99  JZ          fixed tabs
    1.18     11-04-99  OFI         Changd 0x7d to defines and include menu.h
    1.19     06-24-00  SCM         Changed the variable name TotalAbs to ActualTotalAbs.
    1.20     06-28-00 BEKymer/DJL  Changed all MODEL to LEVEL
                                   Changed all MODEL_MASK to CTRL_LEVEL_MASK 
                                   fixed SETUPS, and changed MaxForce to Weld Force
    1.21     11-14-00  BEKymer     Modify cases so LEVEL_TEST and LEVEL_f are the same
                                    also made LEVEL_a and LEVEL_ea the same
    1.22     09-10-05  Aare        Added SBL to CheckProcessLimits().
    1.23     10-24-05  Bwadia      + R and -R PMC band alarms added to CheckProcessLimits().
    1.24     11-22-05  Bwadia      SBL alarm logging decision modified 
    1.25     12-07-05  Bwadia      PMC comparison removed from CheckProcessLimits()
                                   function and moved to final data state. Tracker issue
                                   4028. SBL alarms are checked only if DUPS is present
	   1.26     01-12-06  Bwadia      SBL alarms not detected if global reject limits flag is off
	                                  Modified for tracker issue 3980  
    1.27     09-10-09  BEkymer     Add new define MICRO where needed
    
    

 ----------------------------- DESCRIPTION -------------------------------*/




/* ------------------------------ INCLUDE FILES ----------------------------*/

#include <psos.h>                /* for access to pSOS routines          */
#include "preset.h"
#include "param.h"
#include "wldstate.h"
#include "state.h"
#include "limits.h"
#include "alarms.h"
#include "ready.h"
#include "menu.h"



/*------------------------------ WELD OBJECT DATA --------------------------*/



extern SETUPS_Ver800 RunningPreset;

extern BOOLEAN     AmpStepReachedFlag;
extern BOOLEAN     ForceStepReachedFlag;
extern WELD_DATA   WeldingResults;
extern CONFIGSETUP CurrentSetup;
extern SETUPS_Ver800 CurrentPreset;

extern BOOLEAN SBLMinLimitReached;
extern BOOLEAN SBLMaxLimitReached;
UINT16 CheckForDups(void);


void CheckProcessLimits(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check ALL process limits. When all are checked,      */
/*  those which are not valid for the current weld mode and those not       */
/*  enabled,  will then be masked out of the Alarm value                    */
/*  (SuspectLimitAlarm and RejectLimitAlarm).                               */
/*                                                                          */
/****************************************************************************/
{
UINT32   SuspectLimitAlarm = 0;              /* Clear out last cycle data   */
UINT32   RejectLimitAlarm = 0 ;              /* Clear out last cycle data   */
UINT16   LocalModelMask;


   switch (CurrentSetup.ControlLevel) {
      case LEVEL_t:
         LocalModelMask = CTRL_LEVEL_tMASK;
         break;

      case LEVEL_e:
         LocalModelMask = CTRL_LEVEL_eMASK;
         break;

      case LEVEL_ea:
      case LEVEL_a:
         LocalModelMask = CTRL_LEVEL_eaMASK;
         break;

      case LEVEL_d:
         LocalModelMask = CTRL_LEVEL_dMASK;
         break;

      case LEVEL_f:
      case LEVEL_TEST:
         LocalModelMask = CTRL_LEVEL_fMASK;
         break;

      case LEVEL_DEPOT:
      default:
         LocalModelMask = CTRL_LEVEL_tMASK;
         break;
   }




   switch (RunningPreset.WeldMode) {
      case TIMEMODE:
         LocalModelMask &= TIMEMODEMASK;
         break;

      case ENERGYMODE:
         LocalModelMask &= ENERGYMODEMASK;
         break;

      case PKPOWERMODE:
         LocalModelMask &= PKPOWERMODEMASK;
         break;

      case COLLAPSEMODE:
         LocalModelMask &= COLLMODEMASK;
         break;

      case ABSOLUTEMODE:
         LocalModelMask &= ABSMODEMASK;
         break;

      case GRDDETECTMODE:
         LocalModelMask &= GNDDETMODEMASK;
         break;

      case CONTINUOUSMODE:
         LocalModelMask &= CONTMODEMASK;
         break;

      default:
         LocalModelMask &= TIMEMODEMASK;
         break;
   }

   if ((RunningPreset.SuspectLimitsFlag & BIT0) == BIT0) {

/**  **  First we deal with Energy (alarms PS1 & PS2)  **  **/

      if (RunningPreset.EnergyMLS > WeldingResults.TotalEnergy) SuspectLimitAlarm |= MENERGYBIT;
      if (RunningPreset.EnergyPLS < WeldingResults.TotalEnergy) SuspectLimitAlarm |= PENERGYBIT;


/**  **  Next we deal with Peak Power  (alarms PS3 & PS4)  **  **/

      if (RunningPreset.PowerMLS > WeldingResults.PeakPower) SuspectLimitAlarm |= MPKPOWERBIT;
      if (RunningPreset.PowerPLS < WeldingResults.PeakPower) SuspectLimitAlarm |= PPKPOWERBIT;
         

/**  **  Next we deal with Collapse Distance  (alarms PS5 & PS6)  **  **/

      if (RunningPreset.ColMLS > WeldingResults.ActualTotalCollapse) SuspectLimitAlarm |= MCOLDISTBIT;
      if (RunningPreset.ColPLS < WeldingResults.ActualTotalCollapse) SuspectLimitAlarm |= PCOLDISTBIT;


/**  **  Next we deal with Absolute Distance  (alarms PS7 & PS8)  **  **/

      if (RunningPreset.AbsMLS > WeldingResults.ActualTotalAbs) SuspectLimitAlarm |= MABSDISTBIT;
      if (RunningPreset.AbsPLS < WeldingResults.ActualTotalAbs) SuspectLimitAlarm |= PABSDISTBIT;


/**  **  Next we deal with Trigger Distance  (alarms PS9 & PS1)  **  **/

      if (RunningPreset.TrsDistMLS > WeldingResults.ActualTriggerDistance) SuspectLimitAlarm |= MTRIGDISTBIT;
         if (RunningPreset.TrsDistPLS < WeldingResults.ActualTriggerDistance) SuspectLimitAlarm |= PTRIGDISTBIT;


/**  **  Next we deal with Maximum Force  (alarms PS11 & PS12)  **  **/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (RunningPreset.WeldForceMLS > WeldingResults.WeldForceEnd) SuspectLimitAlarm |= MFORCEBIT;
            if (RunningPreset.WeldForcePLS < WeldingResults.WeldForceEnd) SuspectLimitAlarm |= PFORCEBIT;
      }

/**  **  Finally we deal with Time  (alarms PS13 & PS14)  **  **/

      if (RunningPreset.TimeMLS > WeldingResults.ActualWeldTime) SuspectLimitAlarm |= MTIMEBIT;
         if (RunningPreset.TimePLS < WeldingResults.ActualWeldTime) SuspectLimitAlarm |= PTIMEBIT;


/***  Now remove those which are not allowed in current mode & model  ***/

      SuspectLimitAlarm &= ((~RunningPreset.SuspectLimits) & LocalModelMask);
   }
   if (SuspectLimitAlarm != 0) {
      SuspectLimitAlarm |= PSG1;
      RecordAlarm(SuspectLimitAlarm);
   }

   
   if ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0) {

/**  **  First we deal with Energy (alarms PR1 & PR2)  **  **/

      if (RunningPreset.EnergyMLR > WeldingResults.TotalEnergy) RejectLimitAlarm |= MENERGYBIT;
      if (RunningPreset.EnergyPLR < WeldingResults.TotalEnergy) RejectLimitAlarm |= PENERGYBIT;


/**  **  Next we deal with Peak Power  (alarms PR3 & PR4)  **  **/

      if (RunningPreset.PowerMLR > WeldingResults.PeakPower) RejectLimitAlarm |= MPKPOWERBIT;
      if (RunningPreset.PowerPLR < WeldingResults.PeakPower) RejectLimitAlarm |= PPKPOWERBIT;


/**  **  Next we deal with Collapse Distance  (alarms PR5 & PR6)  **  **/

      if (RunningPreset.ColMLR > WeldingResults.ActualTotalCollapse) RejectLimitAlarm |= MCOLDISTBIT;
      if (RunningPreset.ColPLR < WeldingResults.ActualTotalCollapse) RejectLimitAlarm |= PCOLDISTBIT;


/**  **  Next we deal with Absolute Distance  (alarms PR7 & PR8)  **  **/

      if (RunningPreset.AbsMLR > WeldingResults.ActualTotalAbs) RejectLimitAlarm |= MABSDISTBIT;
      if (RunningPreset.AbsPLR < WeldingResults.ActualTotalAbs) RejectLimitAlarm |= PABSDISTBIT;


/**  **  Next we deal with Trigger Distance  (alarms PR9 & PR1)  **  **/

      if (RunningPreset.TrsDistMLR > WeldingResults.ActualTriggerDistance) RejectLimitAlarm |= MTRIGDISTBIT;
      if (RunningPreset.TrsDistPLR < WeldingResults.ActualTriggerDistance) RejectLimitAlarm |= PTRIGDISTBIT;


/**  **  Next we deal with Maximum Force  (alarms PR11 & PR12)  **  **/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (RunningPreset.WeldForceMLR > WeldingResults.WeldForceEnd) RejectLimitAlarm |= MFORCEBIT;
         if (RunningPreset.WeldForcePLR < WeldingResults.WeldForceEnd) RejectLimitAlarm |= PFORCEBIT;
      }

/**  **  Finally we deal with Time  (alarms PR13 & PR14)  **  **/

      if (RunningPreset.TimeMLR > WeldingResults.ActualWeldTime) RejectLimitAlarm |= MTIMEBIT;
      if (RunningPreset.TimePLR < WeldingResults.ActualWeldTime) RejectLimitAlarm |= PTIMEBIT;


/***  Now remove those which are not allowed in current mode & model  ***/

      RejectLimitAlarm &= ((~RunningPreset.RejectLimits) & LocalModelMask);
   }
   if (RejectLimitAlarm != 0) {
      RejectLimitAlarm |= PRG1;
      RecordAlarm(RejectLimitAlarm);
   }

/**  **  Finally we deal with amplitude step not occurring  **  **/

   if ( ((RunningPreset.Amp2Flag & BIT0) == BIT0) &&  /* If stepping on and */
         (CurrentSetup.AmpControl == TRUE)        &&  /* amp is internal &  */
         (AmpStepReachedFlag == FALSE) ) {            /* not stepped yet    */
            
      switch (RunningPreset.Amp2Flag) {
          case ((UINT16)~BIT2):                 /* Stepping enabled on time          */
             RecordAlarm(CM4);
             break;
   
          case ((UINT16)~BIT3):                 /* Stepping enabled on energy        */
             RecordAlarm(CM6);
             break;
   
          case ((UINT16)~BIT4):                 /* Stepping enabled on peak power    */
             RecordAlarm(CM11);
             break;
   
          case ((UINT16)~BIT5):                 /* Stepping enabled on collapse dist */
             RecordAlarm(CM8);
             break;
   
          case ((UINT16)~BIT6):                 /* Stepping enabled on force         */
             break;
   
          case AMP_STEP_AT_EXTERNAL:                    /* Stepping enabled on external in   */
             RecordAlarm(CM12);
             break;
      
          default:
             RecordAlarm(CM4);
             break;

      }
   }
   if ( ((RunningPreset.Force2Flag & BIT0) == BIT0) &&  /* If stepping on and */          
         (ForceStepReachedFlag == FALSE) ) {            /* not stepped yet    */
            
      switch (RunningPreset.Force2Flag) {
         case ((UINT16)~BIT2):                 /* Stepping enabled on time          */
            RecordAlarm(CM5);
            break;
   
         case ((UINT16)~BIT3):                 /* Stepping enabled on energy        */
            RecordAlarm(CM7);
            break;
   
         case ((UINT16)~BIT4):                 /* Stepping enabled on peak power    */
            RecordAlarm(CM10);
            break;
   
         case ((UINT16)~BIT5):                 /* Stepping enabled on collapse dist */
            RecordAlarm(CM23);
            break;
   
         case ((UINT16)~BIT6):                 /* Stepping enabled on Amplitude      */
            break;
   
         case FORCE_STEP_AT_EXTERNAL:                    /* Stepping enabled on external in   */
            RecordAlarm(CM13);
            break;
      
         default:
            RecordAlarm(CM5);
            break;

      }
   }
   if (CurrentSetup.SBLEnable && (CheckForDups() == TRUE) &&
        ((RunningPreset.RejectLimitsFlag & BIT0) == BIT0))
   {
      if ((!(CurrentPreset.SBLFreqFlags & BIT0)) && SBLMinLimitReached)
         RecordAlarm(PR19);
      if ((!(CurrentPreset.SBLFreqFlags & BIT1)) && SBLMaxLimitReached)
         RecordAlarm(PR20);
   }
   
} 

