/* $Header:   D:/databases/VMdb/2000Series/App/TIME.C_V   1.40.2.0.1.4   Jan 03 2018 12:22:24   RCHAPA  $ */
/* ***********************************************************************  */ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/* ************************                         *********************** */
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Time Mode                                                   */
/*                                                                          */
/* Filename:    Time.c                                                      */
/*                                                                          */
/* Function Name: SelectTimeWeldSequence                                    */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   06-18-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date       Author     Description                            */
/*  =========  ========   =========  ===========                            */
/*     0       06-18-96   BEKymer    Removed Weld Sequence from Statedrv.c  */
/*     1       06-28-96   BEKymer    Add FINALDATASTATE to weld sequence    */
/*     2       07-09-96   BEKymer    Add state for trigger delay            */
/*                                      Re-enable test for hold state       */
/*     3       07-24-96   BEKymer    Change test condition for trigger      */
/*                                      delay test (0:not disabled)         */
/*     4       08-08-96   BEKymer    Add post weld seek state               */
/*     5       09-12-96   BEKymer    Don't reset state machine index        */
/*     6       10-31-96   BEKymer    Add code for FinalData state after     */
/*                                   WaitForULS (but comment out for now)   */
/*     7       12-10-96   BEKymer    Add WaitUlsUp state before PreReady    */
/*     8       02-18-97   LAM        chged sequence to send final data      */
/*     9       03-27-97   LAM        chged seq to send final data last      */
/*    10       04-07-97   LAM        deleted upstroke state                 */
/*    11.1.15  07-02-97   LAM        added states without an encoder        */
/*                                   deleted getcurrentmodel#               */
/*    12.1.16  07-07-97   LAM        deleted psos_tbl.h                     */
/*    12.1.17  07-30-97   BEKymer    Added StartData & StopData states      */
/*    1.18     08-26-97   LAM        deleted start datacollection           */
/*    1.19     09-12-97   LAM        Check number of states against size of */
/*                                   WeldSequence array                     */
/*    1.20     11-13-97   LAM        moved stop data state                  */
/*    1.21     12-01-97   LAM        fixed stop data state                  */
/*    1.22     02-02-98   BEKymer    Do data collection for level_e or better*/
/*    1.23     03-23-98   BEKymer    Add 1 ms to MaxWTime to fix DCS#2514   */
/*    1.24     05-19-98   BEKymer    Add new state to check process alarms  */
/*    1.25     06-26-98   BEKymer    Allow for different trigger states     */
/*                                   depending if pretrigger is on or not.  */
/*                                   This means O/L will not be checked in  */
/*                                   trigger unless pretrigger is on.       */
/*    1.26     09-08-99   BEKymer    Modified sequence so R/T and pretrigger*/
/*                                   are in order by distance.              */
/*    1.27     09-10-99   BEKymer    Modify sequence again so R/T and       */
/*                                   pretrigger are in order.               */
/*    1.28     09-10-99   BEKymer    Modified no R/T & Pretrigger seq.      */
/*    1.29     12-16-99   LAM        removed unused reference to profiling  */
/*    1.30     06-26-00   DJL        made global name changes from Preset.SeekFun to Preset.SeekFunFlag */
/*                                   changed MODEL to LEVEL                 */
/*    1.31     07-12-00   BEKymer    Fixed header line at top of file       */
/*    1.32     07-13-00   BEK/DJL    FIXED A FEW ENCODER ISSUES             */
/*    1.33     04-10-01   BEKymer    Added handheld sequence                */
/*    1.34     04-23-01   BEKymer    Added FakeHoldHHST                     */
/*    1.35     05-14-01   BEKymer    Add 2nd PB state when HH and presets on*/
/*    1.36     05-28-02   BEKymer    Added clear memory state at end of     */
/*                                    weld to aid in sequencing.  This      */
/*                                    change was done months ago but never  */
/*                                    used or saved.  Wanted to save before */
/*                                    change is lost.                       */
/*    1.37     09-11-03   BEKymer    Add energy braking state, remove Mem   */
/*                                    ClearST                               */
/*    1.38     04-06-04   VSharma    Added SVInterlock & ExtTrgDelay state. */
/*    1.39     04-27-04   VSharma    If SVInterlock input & output are not  */
/*                                   configured, don't include 'WaitSVST'.  */
/*    1.40     08-04-04   JOY        States StartData & StopData added in   */
/*                                    LEVEL_t also, Ver9.0 MH1 issue #3858  */
/*    1.40.2.0 05-16-05   BEKymer    Check for PLC Control when creating    */
/*                                    handheld sequence.                    */
/*    1.41     09-02-08   NHAhmed    CleanUp for multi-language support.    */
/*    1.42     10-01-08   NHAhmed    Merged Ver10.40 changes.
 1.40.2.0.1.2  09-10-09   BEkymer    Add new define MICRO where needed		
 1.40.2.0.1.4  01-03-18	  RChapa	 Removed call for DUPS State for 
									 DUPS updated parameters.
 
  ----------------------------- DESCRIPTION --------------------------------*/



/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

//#define TIME_UT                       /* For use as an aid in unit test   */




/*------------------------------ INCLUDES ----------------------------------*/

#include "names.h"
#include <psos.h>
#include "error.h"
#include "obj_tabl.h"
#include "menu.h"
#include "preset.h"
#include "wldstate.h"
#include "statedrv.h"
#include "state.h"
#include "weldhold.h"
#include "inports.h"
#include "outports.h" 



/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

extern STATE    *WeldSequence[NMBR_OF_STATES];/* Current weld cycle definition */
extern SETUPS_Ver800   RunningPreset;
extern CONFIGSETUP CurrentSetup;
extern UINT16   PresetNeedsToBeUpdated;

/*-------------------------- Function Prototypes ---------------------------*/

           
/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/



/*-------------------------------- CODE ------------------------------------*/

           
void SelectTimeWeldSequence(void)

/***************************************************************************/
/*                                                                         */
/* This Time Mode Weld sequence will be based on level and options  */
/* selected from the menus.                                                */
/*                                                                         */
/***************************************************************************/
{
   UINT16  SaveStateMachineFlag;
   UINT16  i = 0;


   SaveStateMachineFlag = SetStateMachineFlag(FALSE);
   WeldSequence[i++] = &TopOfList; /* \   All weld sequences must start with*/
   WeldSequence[i++] = &PreReady;  /*  \  these 5 states, in this order.    */
   WeldSequence[i++] = &ReadySt;   /*   > Otherwise, when preset is verified*/
   WeldSequence[i++] = &PBState;   /*  /  forcing a different sequence, all */
                                   /* /   hell will break loose.            */
   
   if(IsConfigured(INPUT_SV_INTERLOCK) && IsOutConfigured(OUTPUT_SV_INTERLOCK))
      WeldSequence[i++] = &WaitSVST;  /* Wait for SVInterlock signal in this state. */
   
   WeldSequence[i++] = &WaitUls;   
   
   WeldSequence[i++] = &StartData;
   
/*------  At this point update Run Screen so alarm message goes  ------*/
/*------  away and last cycle weld results are set to 0   ------*/



/*--------------------------------------------------------------------------*/
/*  Determine if downspeed 2 or pretrigger is enabled.  If both are enabled */
/*  then decide which will occur first and list that one first in the list. */
/*  If only one on, then there is no problem.                               */
/*--------------------------------------------------------------------------*/

   if ((RunningPreset.PreTrigFlag & BIT0) == BIT0) {                   /* If Pretrigger is on                       */
      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) )  {                       /* and we have an encoder (AED, AEF or MICRO)*/
         if  ((RunningPreset.RTFlag & BIT0) == BIT0) {                 /* If Rapid Traverse is on                   */
            if (RunningPreset.PreTrigDistFlag == FALSE) {              /* Pretrigger on distance ( FALSE=On )       */
               if (RunningPreset.RTDist > RunningPreset.PreTrigDist) { /* Pretrigger occurs before rapid traverse   */
                  WeldSequence[i++] = &PreTrsDST;
                  WeldSequence[i++] = &WaitTrs1DSTPT;
                  WeldSequence[i++] = &WaitTrs2DSTPT;
               }
               else {                                                  /* Rapid traverse occurs before pretrigger   */   
                  WeldSequence[i++] = &WaitTrs1DSTPT;
                  WeldSequence[i++] = &PreTrsDST;
                  WeldSequence[i++] = &WaitTrs2DSTPT;
               }
            }   
            else {                                                     /* Auto pretrigger, then rapid traverse      */      
               WeldSequence[i++] = &PreTrsDST;
               WeldSequence[i++] = &WaitTrs1DSTPT;
               WeldSequence[i++] = &WaitTrs2DSTPT;
            }
         }   
         else {                                                        /* No rapid traverse, pretrigger on          */      
            WeldSequence[i++] = &PreTrsDST;
            WeldSequence[i++] = &WaitTrs1DSTPT;
            WeldSequence[i++] = &WaitTrs2DSTPT;
         }
      }      
      else {                                                           /* No encoder, so pretrigger is auto, no R/T */
         WeldSequence[i++] = &PreTrsST;
         WeldSequence[i++] = &WaitTrs1STPT;
         WeldSequence[i++] = &WaitTrs2STPT;
      }
   }
   else {
      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) )  {   /* Trigger seq if PTS off    */
         WeldSequence[i++] = &WaitTrs1DST;
         WeldSequence[i++] = &WaitTrs2DST;
      }
      else{
         WeldSequence[i++] = &WaitTrs1ST;
         WeldSequence[i++] = &WaitTrs2ST;
      }
   }

   WeldSequence[i++] = &TriggerST;              /* Cause the beeper to beep */

   /* If ExtTrgDelay is selected in WeldSetup */
   if(RunningPreset.ExtTrgDelay == TRUE)
      WeldSequence[i++] = &ExtTrigDelayST;
      
/*------  Determine if trigger delay is needed  ------*/

   if ((RunningPreset.TriggerDelayFlag & /*TriggerDelay.BitMask*/BIT0) == 0) {/* Is it disabled?*/
      WeldSequence[i++] = &TrigDelayST;
   }   


/*------  Here we turn on some sonics  ------*/

   if ( (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) )  {  
     WeldSequence[i++] = &SonicsOn1DST;
   }
   else{
      WeldSequence[i++] = &SonicsOn1ST;
   }
/*------  Determine if stepping is needed  ------*/

    if ( (CurrentSetup.Actuator == AEF) ||
         (CurrentSetup.Actuator == AED) ||
         (CurrentSetup.Actuator == MICRO) )  {
       WeldSequence[i++] = &SonicsOn2DST;  /* Amplitude step is off  */
   }
   else{
      WeldSequence[i++] = &SonicsOn2ST;   /* Amplitude step is off  */
   }
   if (RunningPreset.EnergyBraking == TRUE)
      WeldSequence[i++] = &EnerBrakeST;      /* Energy braking needed */
      
   WeldSequence[i++] = &WeldOffST;           /* End of sonics, key to do end of weld stuff */


/*------  Determine if a hold state is needed  ------*/

   if ((RunningPreset.HoldTimeFlag & /*HoldTime1.BitMask*/ BIT0) == /*HoldTime1.BitMask*/ BIT0) 
      WeldSequence[i++] = &FakeHold;
   else{
    if ( (CurrentSetup.Actuator == AEF) ||
         (CurrentSetup.Actuator == AED) ||
         (CurrentSetup.Actuator == MICRO) )  {
        WeldSequence[i++] = &HoldTimeDST;
      }
      else{
         WeldSequence[i++] = &HoldTimeST;
      }
   }


/*------  Always squirt in a state to check process alarms  ------*/

   WeldSequence[i++] = &CheckLimitsST;


/*------  Determine if an after burst state is needed  ------*/

   if ((RunningPreset.AbFlag & BIT0) == BIT0) {   /* Afterburst is enabled */
      WeldSequence[i++] = &ABDelayST;
      WeldSequence[i++] = &ABTimeST;
      WeldSequence[i++] = &RampSonicsST;
   }


/*------  Now time to check for post weld seek  ------*/

   if ((RunningPreset.SeekFunFlag & BIT0) == BIT0) {  /* Seek is enabled       */
      WeldSequence[i++] = &SeekState;
   }   


/*------  Finally get back to the ready state  ------*/

   WeldSequence[i++] = &WaitUlsUp;     /* \   All weld sequences must end with*/
   /* Stop data collection  */         /*  \  */   
   WeldSequence[i++] = &StopData;      /*   \ */   
   // WeldSequence[i++] = &ClearMemST; /*    \*/
   WeldSequence[i++] = &FinalDataST;   /*    /*/
   WeldSequence[i++] = &PreReady;      /*   / */
   WeldSequence[i++] = &NopList;       /*  /  */
   WeldSequence[i++] = &EndOfList;     /* /   */

/*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i >= NMBR_OF_STATES) {
      while(TRUE);        /* NUMBER OF WELD STATES EXCEEDS ARRAY SIZE      */
   }                      /* Programmer error, increase NMBR_OF_STATES     */

   SetCurrentSequenceType(WELD);

   SetStateMachineFlag(SaveStateMachineFlag);

   TrsTime = TRIGGER_TIMEOUT;
   UlsTime = UPPERLIMIT_TIMEOUT;
   Stagger = PALMBUTTON_STAGGER_TIME;
   MaxWTime = MAX_WELD_TIME + 1;       /* Kludge fix for DCS # 2514    */
   MaxHTime = MAX_HOLD_TIME;
   MaxDTime = MAX_ABDELAY_TIME;
   MaxABTime = MAX_AB_TIME;
   TimeOff = 0;
}


void SelectTimeWeldSequenceHH(void)
/***************************************************************************/
/*                                                                         */
/* This Time Mode Weld sequence is used for 1 input cycle start options    */
/* such as handheld and will be based on control level and options         */
/* selected from the menus.                                                */
/*                                                                         */
/***************************************************************************/
{
   UINT16  SaveStateMachineFlag;
   UINT16  i = 0;

   SaveStateMachineFlag = SetStateMachineFlag(FALSE);
   WeldSequence[i++] = &TopOfList;   
   WeldSequence[i++] = &PreReadyHHST;
   WeldSequence[i++] = &ReadyHHST; 
   WeldSequence[i++] = &PBStateHHST; 
   if (CurrentSetup.ExtPresets == TRUE) {
      WeldSequence[i++] = &PBStateHHST;   /* Need an extra state when both HH and external presets are selected */
   }   
   WeldSequence[i++] = &StartData;

/*------  Sonics State ------*/

   if (CurrentSetup.PLCControlFlag == FALSE) { /* STANDARD CONTROL            */
      WeldSequence[i++] = &SonicsOnHHST;       /* Here we turn on some sonics */
      WeldSequence[i++] = &SonicsOn2HHST;      /* Amplitude step is off       */
      if (RunningPreset.EnergyBraking == TRUE)
         WeldSequence[i++] = &EnerBrakeHHST;   /* Energy braking needed       */
   }
   else {                                      /* PLC CONTROL                 */
      WeldSequence[i++] = &PLCOnHHST;          /* Here we turn on some sonics */
      WeldSequence[i++] = &PLCOn2HHST;         /* Amplitude step is off       */
      if (RunningPreset.EnergyBraking == TRUE)
         WeldSequence[i++] = &PLCBrakeHHST;    /* Energy braking needed       */
   }
      
   WeldSequence[i++] = &WeldOffHHST;  /* End of sonics, key to do end of weld stuff */

/*------  Determine if a hold state is needed  ------*/

   if (CurrentSetup.PLCControlFlag == FALSE) { /* STANDARD CONTROL            */
      if ((RunningPreset.HoldTimeFlag & /*HoldTime1.BitMask*/ BIT0) == /*HoldTime1.BitMask*/ BIT0) 
         WeldSequence[i++] = &FakeHoldHHST;    /* No hold needed */
      else
         WeldSequence[i++] = &HoldTimeHHST;    /* Hold on        */
   }   
   else {                                      /* PLC CONTROL                 */
      if ((RunningPreset.HoldTimeFlag & /*HoldTime1.BitMask*/ BIT0) == /*HoldTime1.BitMask*/ BIT0) 
         WeldSequence[i++] = &FakeHold;        /* No hold needed */
      else   
         WeldSequence[i++] = &PLCTimeHHST;     /* Hold on        */
   }
   
/*------  Always squirt in a state to check process alarms  ------*/

   WeldSequence[i++] = &CheckLimitsST;

/*------  Determine if an after burst state is needed  ------*/

   if ((RunningPreset.AbFlag & BIT0) == BIT0) {   /* Afterburst is enabled */
      WeldSequence[i++] = &ABDelayHHST;
      WeldSequence[i++] = &ABTimeHHST;
      WeldSequence[i++] = &RampSonicsST;
   }

/*------  Now time to check for post weld seek  ------*/

   if ((RunningPreset.SeekFunFlag & BIT0) == BIT0) {  /* Seek is enabled       */
      WeldSequence[i++] = &SeekStateHH;
   }   

   WeldSequence[i++] = &TriggerHHST;              /* Cause the beeper to beep */

/*------  Finally get back to the ready state  ------*/

   WeldSequence[i++] = &StopData;
   // WeldSequence[i++] = &ClearMemST;
   WeldSequence[i++] = &FinalDataST; 
   WeldSequence[i++] = &PreReadyHHST;    
   WeldSequence[i++] = &NopList;     
   WeldSequence[i++] = &EndOfList;   

/*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i >= NMBR_OF_STATES) {
      while(TRUE);        /* NUMBER OF WELD STATES EXCEEDS ARRAY SIZE      */
   }                      /* Programmer error, increase NMBR_OF_STATES     */

   SetCurrentSequenceType(WELD);

   SetStateMachineFlag(SaveStateMachineFlag);

   TrsTime = TRIGGER_TIMEOUT;
   UlsTime = UPPERLIMIT_TIMEOUT;
   Stagger = PALMBUTTON_STAGGER_TIME;
   MaxWTime = MAX_WELD_TIME + 1;       /* Kludge fix for DCS # 2514    */
   MaxHTime = MAX_HOLD_TIME;
   MaxDTime = MAX_ABDELAY_TIME;
   MaxABTime = MAX_AB_TIME;
   TimeOff = 0;
}



