/* $Header:   D:/SWLab/VMdb/2000Series/App/SC.C_V   1.117   22 Sep 2009 11:53:52   ygupta  $ */
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
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION -----------------------------


 Module name: sc

 Filename:    Sc      .c

 Function Name: SC

          Written by:   Laura Markure
                Date:   06-20-96
            Language:   "C"

------------------------------ REVISIONS -------------------------------------

  Rev #     Date     Author  Description
  =====     ======== ======= ===========
   0        03-15-96 LMarkur initial release
   1        08-05-96 LMarkur fixed PVP calibration
   2        08-09-96 LAM     added UpdateSpringRateTable
   3        08-12-96 LAM     added deflectionTable
   4        08-22-96 LAM     added min/max force calculation
   5        08-28-96 LAM     chged min force calculation
   6        09-30-96 BEKymer Change MINFORCEOFFSET from 10 to 20
   7        10-03-96 LAM     Changed calibration procedure
   8        10-14-96 LAM     added ramp downspeed start
   9        10-15-96 LAM     added forcetable offset
  10        10-31-96 LAM     added cyclinder size
  11        11-25-96 LAM     corrected table by 10%
  12        12-04-96 LAM     enabled spring rate
  13        12-04-96 BEKymer New function SCRestart
  14        12-06-96 LAM     added deflection,added larger offset to
                             force table
  15        12-09-96 LAM     max force point = 15%PSI
  15.01     12-12-96 LAM     added averaging of springratetable,
                             added springrateoffset
  15.00     12-19-96 LAM     added check for strokelen
  16.00     12-21-96 LAM     chged what is saved to the preset
  17.00     12-27-96 LAM     updated springrate offset
  18.00     01-17-97 PhilJ   Corrected possible divide by 0 in
                             GetMaxForce & GetMinForce
  19.00     04-18-97 PhilJ   Chngd StuffKey to SendFakeKeyPress
   1.53     09.09.97 JBerman Added WeldSequence index test
   1.54     04.23.98 LAM     chged get max & min force to calculate
                             max & min force
   1.55     05.01.98 LAM     clear alarms when exiting calibration
                             added request calibration
   1.56     05.13.98 LAM     chged to nvr structure
   1.57     05.14.98 LAM     do not put in sequence yet, not implemented
   1.58     05.14.98 LAM     First pass of spring rate calibration,
                             start switch only still need to add
                             calibration complete message
   1.59     06.05.98 LAM     second pass of spring rate calibration,
                             ver 5.0g, check mainkeyflag before sending
                             main key
   1.60     06.12.98 LAM     added manual mode spring rate calibration
   1.61     06.19.98 LAM     deleted preready st in manual mode
   1.62     06.23.98 LAM     redid state machine menusync state
                             version tested by Pete
   1.63     07.01.98 LAM     set advance menu flag, deleted checkpreready
   1.64     07-01-98 LAM     added startcalpb to eliminate jumping to
                             the run screen
   1.65     07-02-98 LAM     added initmanualscmenus to allow sequence
                             to continue
   1.66     07-07-98 LAM     clean up code
   1.67     07-15-98 LAM     made sure can not press start switches
                             until on correct screen, do not clear
                             alarms until calibration complete
   1.68     07-23-98 LAM     need to set ready even on an abort
   1.69     07-30-98 LAM     update hornweight at home after calibration
   1.70     07-30-98 BJB     Deleted act_nvr definition, uses
                             actnvram.h
   1.71     07-31-98 BJB     Includes kpresmsg.h, getmsg.h
   1.72     08-03-98 LAM     added stagger time test
   1.73     08-18-98 LAM     change partcontact to distance method
   1.74     08-21-98 LAM     fixed hornweight changes with short
                             lengths, do not send messages to weldmanger
   1.75     08-24-98 LAM     chged pressure to homepressure
   1.76     09-28-98 LAM     deleted alarmsreset
   1.77     10-30-98 LAM     disabled keys that are not allowed in calibration
   1.78     11-06-98 LAM     abort calibration if start switches are let go at
                             ULS
   1.79     03-15-99 LAM     fixed SetForce prototype

   1.79.1.1 06-24-99 JZ      deleted SetForce, SetVelocity, SelectVelocityControl,
                             SelectForceControl, added SetPV
   1.79.2.2 07-12-99 JRJ     Added condition CurrentSetup.Actuator == AED and change parameter
                             for SetPV to HOLD_TO_HOME in functions SCInit and  ManualSCInit.
                             Added initialization for PartContactFlag and new SCRTAlreadySetFlag to
                             function SCInit.
                             Added if statement for AEF actuator in functions WaitForSpringRate,
                             InitSpringRate, UpdateMessage.
                             Added if statement for AEF actuator in functions SCFinalCleanup,
                             SelectManualSCSequence, and SelectSCSequence.
  1.79.2.3  07-12-99 JRJ     Added DisplayNextScreen() call in function UpdateMessage.
  1.79.2.4  07-20-99 JLH     Updates during calibration debugging; debugging not complete.
  1.79.2.5  07-22-99 LAM     fixed updatemessage, changes LoadCellatHome to SpringRateTable[0]
  1.79.2.6  07-29-99 LAM     set manual overide downspeed to 20%, fixed velocityestimator calling
  1.82      07-30-99 LAM     cannot clear calibration alarms until weld sequence is restored. Moved
                             call from updatemessage to SCFinalCleanup
  1.83      08-06-99 JZ      typecasted define MANUALDOWNSPD, first arg. of SetPV typecasted to UINT16
  1.84      08-24-99 LAM     fixed ManualMode recal alarm 
  1.85      08-27-99 LAM     cleanup unused code  
  1.86      09-20-99 LAM     deleted rapid traverse  
  1.87      09-20-99 LAM     added horn weight offset              
  1.88      09-22-99 LAM     need to increase down speed if too slow              
  1.89      09-27-99 BEK     Remove call to SetPV(HOLD_TO_HOME)
  1.90      10-12-99 LAM     initialized all down speed variables
  1.91      10-20-99 LAM     fixed select 3 key to be active when necessary
  1.92      10-26-99 LAM     added updatedownspeed in wait for trigger 
  1.93      10-26-99 JZ      changed PV_IDLE_VALUE to CurrentSetup.IdleSpeed
  1.94      10-27-99 JZ      typecasted IdleSpeed in SetPV() calls
  1.95      11-05-99 LAM     removed TABS, deleted unused LastHomeReading
  1.96      11-17-99 LAM     fixed clearing the encoder during manual override
  1.96.2.1  12-08-99 LAM     removed unused createspringrate and initspringrate
  1.97      12-16-99 LAM     merged to tip
  1.98      12-20-99 JZ      fixed backward compatibilty                                     
  1.99      02-08-00 LAM     turn off SV when "Done" Screen is displayed.
  1.100     04-18-00 JLH     Removed unused function SCRestart.  Added update of
                              SpringRateTable if error code = 10xx ( AED Upgrade
                              error).
  1.101     04-20-00 JLH     Do not pass calibration if AED Upgrade failed.
  1.102     05-09-00 JLH     Use ERRORCODE1000_EQ20 to test for AED Upgrade error.
  1.103     05-09-00 JLH     Changed ErrorCode declaration to extern enum ERRORCODE_ARG.
  1.104     05-12-00 LAM     Need to clear ErrorCode once the offset is removed.
  1.105     07-07-00 BEK/DJL fixed SETUPS
  1.106     11-01-00 LAM     Only SetReady when Calibration passes(Issue 3662)
  1.106.2.0 04-02-02 LAM     removed AEDUpgraded flag, calibration always updates the springrate table.
  1.106.2.1 04-08-02 LAM     update CurrentSetup.SpringRateTable during init.
  1.106.2.2 05-06-02 LAM     updated error code test to only change loadcell table
  1.106.2.3 05-07-02 LAM     fixed screen not updating on an aborted calibration
  1.106.2.4 05-07-02 LAM     fixed screen flipping before done key is pressed
  1.106.2.5 05-17-02 LAM     modify error code testing.
  1.108     08-05-03 BEKymer Merged 1.106.2.5 and 1.107 to create 1.108 for 9.00A build
                              - Added new function with an argument to call in place of SCFinalCleanup
                               so it can be called from either TEXT or SUBMENU structures.
  1.106.2.6 07-21-03 JOY     QVGA Act. Calibration flag 'QVGACalAllowed' is reset
                              at the end of Calib procedure, in 'SCFinalCleanup()'. 
  1.109     12-05-03 BEKymer Merged 1.106.2.6 & 1.108 to create 1.109 for Ver9.00b
                             build
  1.110     04-11-05 LAM     Added Sbeam
  1.111     04-27-05 LAM     removed deflection routines
  1.112     01-10-06 LAM     modified zeroing the encoder                                                                                    
  1.113     04-14-08 NHAhmed Added two functions SCInit_new() and MannualSCInit_new(). 
  1.114     08-01-08 NHAhmed Renamed Some Functions.
  1.115     09-09-08 NHAhmed CleanUp for multi-language support.
  1.116     09-10-09 BEkymer Add new define MICRO where needed
  1.117     09-22-09 YGupta  Modified for Tracker BUG00472. 
  
                             
                             
----------------------------- DESCRIPTION --------------------------------*/




/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define MAX_TABLE_PTS 11    
#define MANUALDOWNSPD 20   /* downspeed = 20% */
/*------------------------------ INCLUDES ----------------------------------*/

#include "preset.h"
#include "keypad.h"
#include "param.h"
#include "wldstate.h"
#include "weld.h"
#include "digout.h"
#include "ready.h"
#include "beep.h"
#include "genrlmsg.h"
#include "ck_qsend.h"
#include "alarms.h"
#include "interpol.h"
#include "mansensr.h"
#include "menucalb.h"
#include "display.h"
#include "sc.h"
#include "snsrcalb.h"
#include "spidd.h"
#include "states.h"
#include "state.h"
#include "statedrv.h"
#include "selctkey.h"
#include "sysmangr.h"
#include "util.h"
#include "weld_obj.h"
#include "menu5.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "fpk_task.h"
#include "actnvram.h"
#include "encoder.h"
#include "string.h"


/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/
/*                       (scope is global to ALL files)                     */


BOOLEAN SpringRateComplete = TRUE,DeflectionComplete;
UINT16 Y1Distance,Y2Distance;
SINT32 Vel1Pt,Vel2Pt;
DFLOAT Atop;
UINT16 Mode;
UINT16 PVPCountDown,VelCount;
UINT32 Velocity,Deflection;
UINT32 CalbAve[20];
BOOLEAN CalActErrorFlag =FALSE;

/*------------------------------ EXTERNAL DATA -----------------------------*/
extern INBITS Inp;
extern UINT16 StaggerWatchDogTimer;
extern UINT16 OkToDisplayAlarms;          /* TRUE:cycle is complete, display ok */
extern SINT32 HomePressure;
extern BOOLEAN PlsWaitTimerFlag;               /* Please Wait Timer Flag */
extern UINT16 NoPressureFlag;
extern UINT16 CalibrationPassed;


extern STATE  *WeldSequence[NMBR_OF_STATES];      /* Current weld cycle definition */
extern UpperLimitTimer;
extern BOOLEAN UlsTimeout;
extern UINT16 TimerLoopCounter;
extern UINT16 SpringRateTimeout;
extern BOOLEAN AdvanceMenuFlag;
extern UINT32 WmgrQid;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern SETUPS_Ver800 CurrentPreset,RunningPreset;
extern CONFIGSETUP CurrentSetup;
extern SINT32 EncoderPos;
extern enum ERRORCODE_ARG ErrorCode;
extern UINT16 ADForce;
extern UINT16 TempSpringRateTable[];
extern BOOLEAN AdvanceMenuFlag;
extern SINT16 CalTimer;
extern UINT8  MainKeyFlag;
extern UINT16 PartContactFlag;
extern UINT32 CurrentVelocity;
extern UINT16 DownSpeedIncrement;
extern UINT16 CheckDownSpeed; 
extern UINT32 SysmQueueId;

extern BOOLEAN QVGACalAllowed;
extern UINT8 MenuNxtPointer;
extern UINT8 CalMenus[MAX_MENUS];
/*----------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                       (scope is global to THIS file)                     */
static ScreenDisplayed = FALSE;   /* make sure updatemessage only calls display
                                  /* message once */
static GENERIC_MSG WeldMsgOut;

/*-------------------------------- CODE ------------------------------------*/

void SCInitialize(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when calibration is allowed.                     */
/*                                                                          */
/* Outputs : ScreenDisplayed                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{
	MenuNxtPointer = 0;
	memset(&CalMenus,0,(sizeof(CalMenus)));
   SelectSCSequence();         /* Initialize State Sequence for Calibration */
   if ( (CurrentSetup.Actuator != AED) && (CurrentSetup.Actuator != MICRO) )
      UpdateKeyMask(DISABLESEL3);
   AdvanceMenuFlag = FALSE;
   Mode = STARTSWITCHES;
   SpringRateComplete = FALSE;
   PlsWaitTimerFlag = TRUE;                   /* Advance State machine Flag */
   CalibrationPassed = CAL_ABORTED;           /* Assume calibration will be aborted */

/* the next variables for the aef actuator only */
   PVPCountDown = 1500;                       /* countdown timer */
   AdvanceMenuFlag = FALSE;
   VelCount = 0;                              /* countup timer */
   Velocity = 0;
   TimerLoopCounter = 2000;
   NoPressureFlag = TRUE;
   PartContactFlag = FALSE;
   ScreenDisplayed = FALSE;
   DownSpeedIncrement = 0;
   CheckDownSpeed = 0; 

   /* if error code = Version6 upgrade error must save the spring rate default to the novram */
   if ( (NVR.ActId == NVR_AED) || (NVR.ActId == NVR_MICRO) ) {
      if((AtLeastVersion806() == FALSE) &&  ((ErrorCode == ERRORCODE1100_EQ20) || (ErrorCode == ERRORCODE1200_EQ20))){
         BuildDefaultSpringRate();
         UpdateNVRSpringRate();
      }   
   }
   GetDefSpringRateTable();              /* Copy current SpringRateTable to temp table */
   SpringRateTimeout = 0;
   CurrentSetup.SpringRateTable[0] = ADForce; /* save the loadcell reading */
   CurrentSetup.HornWeightOffset = (SINT16)(ADForce - NVR.CalHomeOffset) * 432/1000;
   CurrentVelocity = 0;
   Vel1Pt = 0;
   Vel2Pt = 0;
   DeflectionComplete = FALSE;
   CalActErrorFlag =TRUE;
}

void ManualSCInitialize(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when manual mode is selected                     */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{

   MenuNxtPointer = 0;
	memset(&CalMenus,0,(sizeof(CalMenus)));
   SelectManualSCSequence();   /* Initialize State Sequence for Calibration */
   if ( (CurrentSetup.Actuator != AED) && (CurrentSetup.Actuator != MICRO) )
      UpdateKeyMask(DISABLESEL3);
   AdvanceMenuFlag = FALSE;
   SpringRateComplete = FALSE;
   PlsWaitTimerFlag = TRUE;                   /* Advance State machine Flag */
   CalibrationPassed = CAL_ABORTED;           /* Assume calibration will be aborted */
   Mode = MANUAL;

/* the next variables for for the aef actuator only */
   PVPCountDown = 1500;                       /* countdown timer */
   VelCount = 0;                              /* countup timer */
   Velocity = 0;
   CurrentVelocity = 0;
   TimerLoopCounter = 2000;
   NoPressureFlag = TRUE;
   PartContactFlag = FALSE;
   ScreenDisplayed = FALSE;

   /* if error code = Version6 upgrade error must save the spring rate default to the novram */
   if ( (NVR.ActId == NVR_AED) || (NVR.ActId == NVR_MICRO) ) {
      if((AtLeastVersion806() == FALSE) &&  ((ErrorCode == ERRORCODE1100_EQ20) || (ErrorCode == ERRORCODE1200_EQ20))){
         BuildDefaultSpringRate();
         UpdateNVRSpringRate();
      }   
   }

   DownSpeedIncrement = 0;
   CheckDownSpeed = 0; 

   SetPV(MANUALDOWNSPD, HOME_TO_DWNSPD);
   GetDefSpringRateTable();
   SpringRateTimeout = 0;
   CurrentSetup.SpringRateTable[0] = ADForce; /* save the loadcell reading */
   CurrentSetup.HornWeightOffset = (SINT16)(ADForce - NVR.CalHomeOffset) * 432/1000;
   ZeroEncoder();
   Vel1Pt = 0;
   Vel2Pt = 0;
   DeflectionComplete = FALSE;
}

void StartCalPB(void){
/****************************************************************************/
/*                                                                          */
/*  This function is called whenever both start switches have been pressed. */
/*                                                                          */
/****************************************************************************/

   OkToDisplayAlarms = FALSE;


/*----- Clean up trigger stuff from last cycle -----*/

   StaggerFlag = FALSE;
   StaggerWatchDogTimer = 0;
   UlsTimeout = FALSE;                  /* Clear Uls Timeout Flag           */
   UpperLimitTimer = 0;                 /* Reset timer to zero              */
   OKToAdvance = FALSE;

}

void TestCalPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed between the time one palm   */
/*  is pressed and before two palm buttons are pressed.  It will be a      */
/*  watchdog on the stagger time.                                          */
/*                                                                         */
/***************************************************************************/
{
   if(Inp.OnePB == TRUE)
   {
      if (++StaggerWatchDogTimer > PALMBUTTON_STAGGER_TIME) {
         StaggerFlag = TRUE;
         CalibrationPassed = CAL_ABORTED;   /* assume calibration will be aborted */
         SendFakeKeyPress(MainKey);
      }
   }
}

void WaitForSpringRate(void){

   if((Inp.BothPB == FALSE) && (Mode == STARTSWITCHES))
   {
      SVOff();                            /* Turn off SV to bring hown up      */
      CalibrationPassed = CAL_FAILED;
      PlsWaitTimerFlag = FALSE;               /* Advances the state machine */
   }
   CurrentVelocity = VelocityEstimator(EncoderPos);
   UpdateDownSpeed();
   if(Inp.uls == FALSE)
   {
      if(SpringRateComplete == FALSE) {
         CheckSpringRate();
      }
      else
      {
         PlsWaitTimerFlag = FALSE;               /* Advances the state machine */
         CalibrationPassed = CAL_PASSED;
      }
   }
   else
   {
      if(Mode == STARTSWITCHES)
         ZeroEncoder();
   }
}                                       /* end of WaitForSpringRate */


void UpdateMessage(void){
   UINT16 Index;

   if (ScreenDisplayed == FALSE)
   {
      /* Save the springratetable, loadcellathome, and clear the alarms for AEF only */
      SVOff();                            /* Turn off SV to bring hown up      */
    /* Test for Version6 AED Upgrade error */
      if ( (NVR.LoadCell[0] < NO_LOADCELL_OFFSET) &&
           ( (NVR.ActId == NVR_AED) ||
             (NVR.ActId == NVR_MICRO) ||
             (NVR.ForceGauge == SBEAM) ) )
      {
         for(Index = 0; Index < MAX_TABLE_PTS; Index++)
         {
            NVR.LoadCell[Index] += LoadCellOffset;
            if(NVR.LoadCell[Index] < 0) NVR.LoadCell[Index] = 0;
         }
         ErrorCode = 0;     /* need to clear incase calibration is run again */
         WeldMsgOut.common.opcode = OP_NVM_WRITE_UPGRADE805;
         CkQSend(SysmQueueId, &WeldMsgOut, WELD_MGR, __LINE__, MILLS_TO_TICKS(20));  /* 20 ms */
      }
      else if(AtLeastVersion806() == FALSE)
      {
         ErrorCode = 0;     /* need to clear incase calibration is run again */
         WeldMsgOut.common.opcode = OP_NVM_WRITE_UPGRADE600;
         CkQSend(SysmQueueId, &WeldMsgOut, WELD_MGR, __LINE__, MILLS_TO_TICKS(20));  /* 20 ms */
      }
      else if ( CalibrationPassed != CAL_PASSED)
      {
         for (Index = 1; Index < SPRING_RATE_SIZE; Index++)
         {
            CurrentSetup.SpringRateTable[Index] = TempSpringRateTable[Index];
         }
      }                        
      DisplayNextScreen();
      ScreenDisplayed = TRUE;  
      UpdateCurrentPreset(SAVECURRENTSETUP,0,0);  /* save springrate to BBram */
   }                           
}                              /* end of UpdateMessage */

void SCFinalCleanup(void) {
/* Called when the actuator calibration is complete or terminated */
   UINT16 Index;

   if(CalibrationPassed != CAL_NOT_ALLOWED)
   {
/* Put state machine back */
      SelectWeldSequence();               /* Restore proper weld sequence      */
      StartStateMachine();                /* Start the state machine here      */
      if (CalibrationPassed == CAL_PASSED){
         SetReady();
         ClearCalibrationAlarms();      
      }
      SVOff();                            /* Turn off SV to bring hown up      */


/* Force Main Menu key */
      if(MainKeyFlag == FALSE && QVGACalAllowed == FALSE)
         SendFakeKeyPress(MainKey);
      CalibrationPassed = CAL_NOT_ALLOWED;
   }
                                       /* end if (CalibrationPassed != CAL_NOT_ALLOWED) */
   QVGACalAllowed = FALSE;                                       
}                                       /* end of SCFinalCleanup */


void SelectSCSequence(void)
/***************************************************************************/
/*                                                                         */
/* This is the SC state sequence.                                          */
/*                                                                         */
/***************************************************************************/{
   UINT16  SaveStateMachineFlag;
   UINT16 i = 0;

   /* Set the current state to TopOfList */
   ResetStateMachine();                /* Turn off the state machine first */
   SaveStateMachineFlag = SetStateMachineFlag(FALSE);
   WeldSequence[i++] = &CalTopOfList;     /* enter the sequence of states */
   /* CalForceMenu1 wait for next menu to be displayed */
                                       /**--------------------**/
                                       /* CAL ACTUATOR         */
                                       /* W/Start Switches     */
                                       /* W/Manual Overide     */
                                       /*                      */
                                       /**--------------------**/
   if ( (CurrentSetup.Actuator==AED) || (CurrentSetup.Actuator==MICRO) )
      WeldSequence[i++] = &MenuSyncST;  /**--------------------**/
                                       /* CAL ACTUATOR         */
                                       /* Set Regulator Tor    */
                                       /* Operating PSI        */
                                       /* ____________Continue */
                                       /**--------------------**/


/* wait for menu to set CalDistanceFlag wait for AEF */
//   WeldSequence[i++] = &MenuSyncST;    /**--------------------**/
                                       /* CAL ACTUATOR         */
                                       /* Cal. Distance        */
                                       /*                  Yes */
                                       /*                   No */
                                       /**--------------------**/

                                       /**--------------------**/
   WeldSequence[i++] = &CalPBState2;   /* CAL ACTUATOR         */
   WeldSequence[i++] = &SCWaitUls;     /* Press Start Switches */
   WeldSequence[i++] = &SCWaitTrsST;   /*                      */
                                       /**--------------------**/


   /* aef ONLY Calculate spring rate  wait for next menu to be displayed */

//   WeldSequence[i++] = &SCDeflection;/**--------------------**/
                                       /* CAL ACTUATOR         */
   WeldSequence[i++] = &SCDone;        /* Calibration Comp.    */
                                       /* Release Start        */
   WeldSequence[i] = &SCEndOfList;   /* Switches             */
                                       /**--------------------**/

/*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i > NMBR_OF_STATES) {
      while(TRUE);        /* NUMBER OF WELD STATES EXCEEDS ARRAY SIZE      */
   }                      /* Programmer error, increase NMBR_OF_STATES     */

   UpdateKeyMask(CALMODEMASK);
   CurrentSequence = SC;
   UlsTime = UPPERLIMIT_TIMEOUT;
   Stagger = PALMBUTTON_STAGGER_TIME;
   SetStateMachineFlag(SaveStateMachineFlag);
   ClearAbort();

   StopDataCollection();             /* Stop the weld data collection */
   StartStateMachine();              /* Start state machine      */

}


void SelectManualSCSequence(void)
/***************************************************************************/
/*                                                                         */
/* This is the Manual SC state sequence.                                   */
/*                                                                         */
/***************************************************************************/
{
   UINT16  SaveStateMachineFlag;
   UINT16 i = 0;

   ResetStateMachine();                /* Turn off the state machine first */
   /* Set the current state to TopOfList */
   SaveStateMachineFlag = SetStateMachineFlag(FALSE);
   WeldSequence[i++] = &CalTopOfList;     /* enter the sequence of states */
   /* CalForceMenu1 wait for next menu to be displayed */
                                       /**--------------------**/
                                       /* CAL ACTUATOR         */
                                       /* Set Regulator Tor    */
                                       /* Operating PSI        */
                                       /* ____________Continue */
                                       /**--------------------**/


/* wait for menu to set CalDistanceFlag wait for AEF */
   if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) )
      WeldSequence[i++] = &MenuSyncST; /**--------------------**/
                                       /* CAL ACTUATOR         */
                                       /* Cal. Distance        */
                                       /*                  Yes */
                                       /*                   No */
                                       /**--------------------**/

                                       /**--------------------**/
                                       /* CAL ACTUATOR         */
   WeldSequence[i++] = &SCWaitUls;     /* Use Manual           */
   WeldSequence[i++] = &SCWaitTrsST;   /* Overide on valve     */
                                       /**--------------------**/


/* aef ONLY Calculate spring rate  wait for next menu to be displayed */

//   WeldSequence[i++] = &SCDeflection;/**--------------------**/
                                       /* CAL ACTUATOR         */
   WeldSequence[i++] = &SCDone;        /* Calibration Comp.    */
                                       /* Release Start        */
   WeldSequence[i++] = &SCEndOfList;   /* Switches             */
                                       /**--------------------**/

/*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i > NMBR_OF_STATES) {
      while(TRUE);        /* NUMBER OF WELD STATES EXCEEDS ARRAY SIZE      */
   }                      /* Programmer error, increase NMBR_OF_STATES     */
   UlsTime = UPPERLIMIT_TIMEOUT;
   Stagger = PALMBUTTON_STAGGER_TIME;

   UpdateKeyMask(CALMODEMASK);
   CurrentSequence = SC;
   SetStateMachineFlag(SaveStateMachineFlag);
   ClearAbort();
   StopDataCollection();             /* Stop the weld data collection */
   StartStateMachine();              /* Start state machine      */

}



