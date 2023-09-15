
/* $Header:   D:/databases/VMdb/2000Series/App/CONT.C_V   1.18   12 Nov 2010 12:39:02   bkymer  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Continuous Mode                                             */
/*                                                                          */
/* Filename:    Cont.c                                                      */
/*                                                                          */
/* Function Name: SelectContWeldSequence                                    */
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
/*     3       09-12-96   BEKymer    Don't reset state machine index        */
/*     4       12-17-96   BEKymer    Remove afterburst as an option         */
/*     5       12-31-96   BEKymer    Add possible state for post weld seek  */
/*     6       03-27-97   LAM        chged seq to send final data last      */
/*     7.1.11  07-07-97   LAM        deleted psos_tbl.h                     */
/*    1.12     08-26-97   LAM        deleted start datacollection           */
/*    1.13     09-08-97   BEKymer    Check number of states against size of */
/*                                   WeldSequence array                     */
/*    1.14     12/16/99   LAM        removed unused error handling code     */
/*   1.15      06-26-00   DJL        made global name changes from Preset.SeekFun to Preset.SeekFunFlag */
/*   1.18      11-12-10   BEKymer    Put 1.15 on the tip                    */
/*                                                                          */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/
/*                                                                          */
/*   Continuous mode will have two 'modes' of operation.  Pressing one or   */
/*   two palm buttons will determine which mode is used.                    */
/*                                                                          */
/*   Mode 1 - Pressing only ONE palm button, or pressing two palm buttons   */
/*            but exceeding the stagger time in between.                    */
/*                                                                          */
/*            If the second palm button is pressed after the stagger time,  */
/*            the sonics will remain on, the SV will NOT be activated, but  */
/*            an alarm will occur indicating stagger time error.            */
/*                                                                          */
/*            There will be NO SV drive output.  Sonics will remain on      */
/*            until the palm buttons are both released.                     */
/*                                                                          */
/*                                                                          */
/*   Mode 2 - Pressing TWO palm buttons within the stagger time (200 ms).   */
/*                                                                          */
/*            There will be an SV drive output when the 2nd palm button     */
/*            is pressed.  Sonics will start as soon as the 1st palm button */
/*            is pressed.  Both palm buttons must be maintained to keep the */
/*            SV drive on.  As soon as one is released the SV drive is      */
/*            removed.  The sonics will remain on as long as at least one   */
/*            palm button is pressed.                                       */
/*                                                                          */
/*            If "Pre Weld Seek" is enabled the SV drive output will not    */
/*            occur until 550 ms after the stagger time time was met. This  */
/*            is the seek time (+50 ms for tolerance).                      */
/*                                                                          */
/*            The force will be adjustable on the fly without pressing the  */
/*            palm buttons to start a new cycle.                            */
/*                                                                          */
/*                                                                          */
/*   Notes for both modes:                                                  */
/*   ---------------------                                                  */
/*                                                                          */
/*   "Pre Weld Seek", if enabled, will do a 500 ms seek as soon as one palm */
/*   button has been pressed.                                               */
/*                                                                          */
/*   In both modes there will be NO HOLD time, and no amplitude or force    */
/*   stepping.  The power will be checked to make sure the continuous power */
/*   rating is not exceeded.                                                */
/*                                                                          */
/*   In the event of an overload the sonics will be shut off as well as the */
/*   SV drive removed.  The palm buttons will have to be released and then  */
/*   pressed again to start another cycle.                                  */
/*                                                                          */
/*   The amplitude will be adjustable on the fly without pressing the palm  */
/*   buttons to start a new cycle.                                          */
/*                                                                          */
/*-------------------------  End of Description  ---------------------------*/



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


/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

extern STATE    *WeldSequence[NMBR_OF_STATES];/* Current weld cycle definition */
extern SETUPS_Ver800   RunningPreset;
//extern VARIABLE HoldTimeCont;



/*-------------------------- Function Prototypes ---------------------------*/


#include "weldhold.h"



/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/



/*-------------------------------- CODE ------------------------------------*/





void SelectContWeldSequence(void)
/***************************************************************************/
/*                                                                         */
/* This Time Mode Weld sequence will be based on model number and options  */
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
   WeldSequence[i++] = &OnePBState;/*  /  forcing a different sequence, all */
//   WeldSequence[i++] = &WaitUls;   /* /   hell will break loose.            */
   WeldSequence[i++] = &NopList;   /* Nop to replace WaitUls                */

/*------  Here we turn on some sonics  ------*/

   WeldSequence[i++] = &SonicsOn1A;


/*------  Determine if an after burst state is needed (not in 1pb mode) ------*/

//   if ((RunningPreset.AbFlag & BIT0) == BIT0) {   /* Afterburst is enabled */
//      WeldSequence[i++] = &ABDelayST;
//      WeldSequence[i++] = &ABTimeST;
//   }


/*------  Now time to check for post weld seek  ------*/

   if ((RunningPreset.SeekFunFlag & BIT0) == BIT0) {  /* Seek is enabled       */
      WeldSequence[i++] = &SeekState;
   }   

   WeldSequence[i++] = &WaitUlsUp;   /* \   All weld sequences must end with*/
   WeldSequence[i++] = &FinalDataST; /*  \  these 5 states, in this order.  */
   WeldSequence[i++] = &PreReady;    /*   >                                 */
   WeldSequence[i++] = &NopList;     /*  /                                  */
   WeldSequence[i++] = &EndOfList;   /* /                                   */


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