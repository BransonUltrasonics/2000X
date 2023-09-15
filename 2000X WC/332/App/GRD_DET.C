/* $Header:   D:/databases/VMdb/2000Series/App/GRD_DET.C_V   1.35   Jan 03 2018 11:22:46   RCHAPA  $ */
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
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Ground Detect Mode                                          */
/*                                                                          */
/* Filename:    Grd_det.c                                                   */
/*                                                                          */
/* Function Name: SelectGroundDetectWeldSequence                            */
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
/*     4       08-13-96   BEKymer    Add state SonicsOn3D                   */
/*     5       09-12-96   BEKymer    Add post weld seek state               */
/*     6       09-12-96   BEKymer    Don't reset state machine index        */
/*     7       12-10-96   BEKymer    Add WaitUlsUp state before PreReady    */
/*     8       03-27-97   LAM        chged seq to send final data last      */
/*     9       04-07-97   LAM        deleted upstroke state                 */
/*    10.1.09  07-02-97   LAM        added states without an encoder        */
/*                                   deleted getcurrentmodel#               */
/*    10.1.10  07-07-97   LAM        deleted psos_tbl.h                     */
/*    10.1.11  07-30-97   BEKymer    Added StartData & StopData states      */
/*    1.12     08-26-97   LAM        deleted start datacollection           */
/*    1.13     09-08-97   BEKymer    Check number of states against size of */
/*                                   WeldSequence array                     */
/*    1.14     11-13-97   LAM        moved stop data state                  */
/*    1.15     12-01-97   LAM        fixed stop data state                  */
/*    1.16     02-02-98   BEKymer    Do data collection for LEVEL_e or better*/
/*    1.17     07-10-98   BEKymer    Add check limit state after hold       */
/*    1.18     09-08-99   BEKymer    Modified sequence so R/T and pretrigger*/
/*                                   are in order by distance.              */
/*    1.19     09-10-99   BEKymer    Modify sequence again so R/T and       */
/*                                   pretrigger are in order.               */
/*    1.20     09-10-99   BEKymer    Modified no R/T & Pretrigger seq.      */
/*    1.21     12-16-99   LAM        removed unused reference to profiling  */
/*    1.22     12-17-99   JZ         fixed gnd_det encoder fail alarm for AE*/
/*                                  merged to trunk                        */
/*   1.23      06-26-00   DJL        made global name changes from Preset.SeekFun to Preset.SeekFunFlag */
/*                                   Changed MODEL to LEVEL                 */
/*   1.24      07-11-00   DJL        added actuator=aed in if statement.    */
/*   1.25      07-13-00   BEKymer/DJL added actuator=ead in more if statements*/
/*   1.26      05-02-01   BEKymer    Added SelectGroundDetectWeldSequenceHH */
/*                                    to support handheld and single start  */
/*                                    weld cycles                           */
/*   1.27      05-28-02   BEKymer    Added clear memory state at end of     */
/*                                    weld to aid in sequencing.  This      */
/*                                    change was done months ago but never  */
/*                                    used or saved.  Wanted to save before */
/*                                    change is lost.                       */
/*   1.28      09-12-03   BEKymer    Add energy braking state, remove Mem   */
/*                                    ClearST                               */
/*    1.29     04-06-04   VSharma    Added SVInterlock & ExtTrgDelay state. */
/*    1.30     04-27-04   VSharma    If SVInterlock input & output are not  */
/*                                   configured, don't include 'WaitSVST'.  */
/*    1.31     08-04-04   JOY        States StartData & StopData added in   */
/*                                    LEVEL_t also, Ver9.0 MH1 issue #3858  */   
/*    1.32     09-02-08  NHAhmed    CleanUp for multi-language support.     */
/*    1.33     09-10-09  BEkymer    Add new define MICRO where needed       */
/*    1.35	   01-03-18	 RChapa		Removed call to DUPS State for DUPS     */
/*									parameters update                       */
/*----------------------------- DESCRIPTION --------------------------------*/



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
#include "weldhold.h"
#include "inports.h"
#include "outports.h"


/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

extern STATE    *WeldSequence[NMBR_OF_STATES];/* Current weld cycle definition */
extern SETUPS_Ver800   RunningPreset;
extern CONFIGSETUP CurrentSetup;



/*-------------------------- Function Prototypes ---------------------------*/





/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/



/*-------------------------------- CODE ------------------------------------*/





void SelectGroundDetectWeldSequence(void)
/***************************************************************************/
/*                                                                         */
/* This Ground Detect Mode Weld sequence will be based on LEVEL and */
/* options selected from the menus.                                        */
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

/*--------------------------------------------------------------------------*/
/*  Determine if downspeed 2 or pretrigger is enabled.  If both are enabled */
/*  then decide which will occur first and put that one first in the list.  */
/*  If only one on, then there is no problem.                               */
/*--------------------------------------------------------------------------*/

   if ((RunningPreset.PreTrigFlag & BIT0) == BIT0) {                   /* If Pretrigger is on                       */
      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {                        /* and we have an encoder (AED, AEF or MICRO)*/
         if ((RunningPreset.RTFlag & BIT0) == BIT0) {                  /* If Rapid Traverse is on                   */
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
           (CurrentSetup.Actuator == MICRO) ) {                        /* and we have an encoder (AED, AEF or MICRO)*/
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
        (CurrentSetup.Actuator == MICRO) ) {
      WeldSequence[i++] = &SonicsOn8DST;
   }
   else{
      WeldSequence[i++] = &SonicsOn8ST;
   }

/*------  Determine if stepping is needed  ------*/

   if ( (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) ) {
      WeldSequence[i++] = &SonicsOn9DST;  /* Amplitude step is off  */
   }
   else{
      WeldSequence[i++] = &SonicsOn9ST;   /* Amplitude step is off  */
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
           (CurrentSetup.Actuator == MICRO) ) {
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
   WeldSequence[i++] = &WaitUlsUp;     /*  \   All weld sequences must end with*/
   /* Stop data collection */          /*   \    */   
   WeldSequence[i++] = &StopData;       /*   \   */
   // WeldSequence[i++] = &ClearMemST;  /*    \  */
   WeldSequence[i++] = &FinalDataST;    /*    /  */
   WeldSequence[i++] = &PreReady;       /*   /   */
   WeldSequence[i++] = &NopList;        /*  /    */
   WeldSequence[i++] = &EndOfList;      /* /     */


/*---  Check the WeldSequence index and make sure no overflow occurred  ---*/

   if (i >= NMBR_OF_STATES) {
      while(TRUE);        /* NUMBER OF WELD STATES EXCEEDS ARRAY SIZE      */
   }                      /* Programmer error, increase NMBR_OF_STATES     */

   SetCurrentSequenceType(WELD);

   SetStateMachineFlag(SaveStateMachineFlag);

   TrsTime = TRIGGER_TIMEOUT;
   UlsTime = UPPERLIMIT_TIMEOUT;
   Stagger = PALMBUTTON_STAGGER_TIME;
   MaxWTime = MAX_WELD_TIME;
   MaxHTime = MAX_HOLD_TIME;
   MaxDTime = MAX_ABDELAY_TIME;
   MaxABTime = MAX_AB_TIME;
   TimeOff = 0;
}



void SelectGroundDetectWeldSequenceHH(void)
/***************************************************************************/
/*                                                                         */
/* This Ground Detect Mode Weld sequence for handheld will be based on     */
/* LEVEL and options selected from the menus.                              */
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
   WeldSequence[i++] = &StartData;

/*------  Here we turn on some sonics  ------*/

   WeldSequence[i++] = &SonicsOnGD1ST;
   WeldSequence[i++] = &SonicsOnGD2ST;
   if (RunningPreset.EnergyBraking == TRUE)
      WeldSequence[i++] = &EnerBrakeST;      /* Energy braking needed */
      
   WeldSequence[i++] = &WeldOffHHST;  /* End of sonics, key to do end of weld stuff */


/*------  Determine if a hold state is needed  ------*/

   if ((RunningPreset.HoldTimeFlag & /*HoldTime1.BitMask*/ BIT0) == /*HoldTime1.BitMask*/ BIT0) 
      WeldSequence[i++] = &FakeHoldHHST;
   else  
      WeldSequence[i++] = &HoldTimeHHST;


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
   MaxWTime = MAX_WELD_TIME;
   MaxHTime = MAX_HOLD_TIME;
   MaxDTime = MAX_ABDELAY_TIME;
   MaxABTime = MAX_AB_TIME;
   TimeOff = 0;
}
                                               
