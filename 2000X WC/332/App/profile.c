/* $Header:   K:\APPS\PVCS Pro\332new\App\PROFILE.C_V   2.7   Oct 11 1999 11:19:20   jzimny  $ */
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
/* Module name: Weldhold                                                    */
/*                                                                          */
/* Filename:    Weldhold.c                                                  */
/*                                                                          */
/* Function Name: State machine code                                        */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   03-15-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date        Author       Description                         */
/*  =========  =========   ===========  ===========                         */
/*     0       03-20-96    BEKymer      Add pSOS to state code              */
/*     1       04-28-96    LAM          delete weldmngr.h added weld.h      */
/*     2       05-13-96    BEKymer      Add proper function prototyping     */
/*     2.3     09-12-97    BEKymer      Code added to check for divide by 0 */
/*     2.4     03-15-99    LAM          fixed setforce prototype            */
/*     2.4.1.1 06-24-99    JZ           changed SetForce to SetPV           */
/*     2.6     09-27-99    BEKymer      Remove call to SETPV(HOLD_TO_HOME)  */
/*     2.7     10-11-99    JZ           removed typecasting at AmpRange and */
/*                                      ForceRange                          */
/*                                                                          */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/

/* This module contains those functions that will deal with amplitude and  */
/* force profiling.                                                        */


/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/




/*------------------------------ INCLUDES ----------------------------------*/

#include "portable.h"
#include "menu.h"
#include "profile.h"
#include "preset.h"



/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

#include "profile.h"
#include "timer.h"
#include "encoder.h"
#include "mansensr.h"



/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

extern SINT8  StrProfile1[MESSAGESIZE];     /* Profile Wait        */
extern SINT8  StrProfile2[MESSAGESIZE];     /* Interpolate         */
extern SINT8  StrProfile3[MESSAGESIZE];     /* Profile Trigger     */

SINT16 AmpProfileIndex, ForceProfileIndex, StartAmp, StartForce;
SINT16 AmpProfileStartFlag, ForceProfileStartFlag;
SINT16 InitialAmp, InitialForce;

extern SETUPS RunningPreset;


/*-----  Force and Pressure  -----*/

SINT32  ForceTimeRange, ForceRange, StartForceTime;


SINT32  AmpTimeRange, AmpRange, StartAmpTime;

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/


/*-------------------------------- CODE ------------------------------------*/


void ResetProfile(enum PROFILE Profile)
/***************************************************************************/
/*                                                                         */
/*  This function resets the proper profile indices to zero.  It should be */
/*  called at the start of each weld cycle if profiling is enabled.        */
/*                                                                         */
/***************************************************************************/
{
   if ((Profile == AMPLITUDEPROFILE) || (Profile == ALLPROFILES)) {
      AmpProfileIndex = 0;
      AmpTimeRange = 0;
      AmpRange = 0;
      StartAmpTime = 0;
      AmpProfileStartFlag = FALSE;
      InitialAmp = RunningPreset.AmpProfile.Y_axis[0];
   }

   if ((Profile == FORCEPROFILE) || (Profile == ALLPROFILES)) {
      ForceProfileIndex = 0;
      ForceTimeRange = 0;
      ForceRange = 0;
      StartForceTime = 0;
      ForceProfileStartFlag = FALSE;
      InitialForce = RunningPreset.ForceProfile.Y_axis[0];
   }
}



void CheckProfile(enum PROFILE Profile)
/***************************************************************************/
/*                                                                         */
/*  This function will check the next trigger point to determine if the    */
/*  force or amplitude value should be changed.  If it determines a change */
/*  is required, the change is done and the indices are set up for the     */
/*  next call.                                                             */
/*                                                                         */
/***************************************************************************/
{
   SINT16 NewAmp, NewForce;
   SINT32  TimeOrDist;

/***************************************************************************/
/***   ***                First deal with Amplitude                ***   ***/
/***************************************************************************/

   if ((Profile == AMPLITUDEPROFILE) || (Profile == ALLPROFILES)) {
      if (AmpProfileStartFlag == FALSE) {
         if (RunningPreset.AmpProfile.Trigger == TIMETRIG) /* Start trigger */
            TimeOrDist = GetCycleTime();
         else
            TimeOrDist = GetCycleDist();
      }
      else {
         if (RunningPreset.AmpProfile.Units == TIMETRIG)  /* Next point trigger */
            TimeOrDist = GetCycleTime();
         else
            TimeOrDist = GetCycleDist();
      }

      if (TimeOrDist >= RunningPreset.AmpProfile.X_axis[AmpProfileIndex]) {
         if (++AmpProfileIndex >= RunningPreset.AmpProfile.Points) {
            AmpProfileIndex = RunningPreset.AmpProfile.Points - 1;
            NewAmp = SetupInterpolateAmp(TimeOrDist, 
                     RunningPreset.MaxTimeout,
                     RunningPreset.AmpProfile.Y_axis[AmpProfileIndex],
                     RunningPreset.AmpProfile.Y_axis[AmpProfileIndex]);
         }
         else {
            NewAmp = SetupInterpolateAmp(TimeOrDist,
                     RunningPreset.AmpProfile.X_axis[AmpProfileIndex],
                     RunningPreset.AmpProfile.Y_axis[AmpProfileIndex - 1],
                     RunningPreset.AmpProfile.Y_axis[AmpProfileIndex]);
         }
//         strcpy(&RunBuffer1, &StrProfile3);        /* Update msg for Run screen   */
      }
      else if (AmpProfileStartFlag == FALSE) {
         NewAmp = InitialAmp;
//         strcpy(&RunBuffer1, &StrProfile1);        /* Update msg for Run screen   */
      }
      else {
         NewAmp = InterpolateAmp(TimeOrDist);
//         strcpy(&RunBuffer1, &StrProfile2);        /* Update msg for Run screen   */
      }
   }
   SetCurrentAmp(NewAmp);


/***************************************************************************/
/***   ***                   Next deal with Force                  ***   ***/
/***************************************************************************/

   if ((Profile == FORCEPROFILE) || (Profile == ALLPROFILES)) {
      if (ForceProfileStartFlag == FALSE) {
         if (RunningPreset.ForceProfile.Trigger == TIMETRIG) /* Start trigger */
            TimeOrDist = GetCycleTime();
         else
            TimeOrDist = GetCycleDist();
      }
      else {
         if (RunningPreset.ForceProfile.Units == TIMETRIG)  /* Next point trigger */
            TimeOrDist = GetCycleTime();
         else
            TimeOrDist = GetCycleDist();
      }

      if (TimeOrDist >= RunningPreset.ForceProfile.X_axis[ForceProfileIndex]) {
         if (++ForceProfileIndex >= RunningPreset.ForceProfile.Points) {
            ForceProfileIndex = RunningPreset.ForceProfile.Points - 1;
            NewForce = SetupInterpolateForce(TimeOrDist,
                 RunningPreset.MaxTimeout,
                 RunningPreset.ForceProfile.Y_axis[ForceProfileIndex],
                 RunningPreset.ForceProfile.Y_axis[ForceProfileIndex]);
         }
         else {
            NewForce = SetupInterpolateForce(TimeOrDist,
                 RunningPreset.ForceProfile.X_axis[ForceProfileIndex],
                 RunningPreset.ForceProfile.Y_axis[ForceProfileIndex - 1],
                 RunningPreset.ForceProfile.Y_axis[ForceProfileIndex]);
         }
      }
      else if (ForceProfileStartFlag == FALSE)
         NewForce = InitialForce;
      else NewForce = InterpolateForce(TimeOrDist);
   }
//   ForceIndex = NewForce;
}



SINT16 SetupInterpolateAmp(SINT32 Time0, SINT32 Time1, SINT16 Amp0, SINT16 Amp1)
/***************************************************************************/
/*                                                                         */
/*  This function is called once for each point in the profile.  It will   */
/*  calculate the amplitude difference between the new point and the next  */
/*  point, and the Time (or distance) difference between the new point and */
/*  the next point.  These values are then used by the InterpolateAmp      */
/*  function every ms. to create the proper ramp.                          */
/*                                                                         */
/***************************************************************************/
{
   AmpProfileStartFlag = TRUE;
   AmpTimeRange = Time1 - Time0;
   AmpRange = (Amp1 - Amp0);
   StartAmp = Amp0;
   StartAmpTime = Time0;
   return(Amp0);
}



SINT16 InterpolateAmp(SINT32 Time)
/***************************************************************************/
/*                                                                         */
/* This function uses the calculations done by the SetupInterpolateAmp     */
/* function.  It is called every ms to create the proper amplitude ramp.   */
/*                                                                         */
/***************************************************************************/
{
   SINT16  Retval = 0;
 
   if (AmpTimeRange != 0) {
      Retval = (StartAmp + (SINT16)(((Time - StartAmpTime) * AmpRange) / AmpTimeRange));
   }
   return(Retval);
}



SINT16 SetupInterpolateForce(SINT32 Time0, SINT32 Time1, SINT16 Force0, SINT16 Force1)
/***************************************************************************/
/*                                                                         */
/*  This function is called once for each point in the profile.  It will   */
/*  calculate the force difference between the new point and the next      */
/*  point, and the Time (or distance) difference between the new point and */
/*  the next point.  These values are then used by the InterpolateForce    */
/*  function every ms. to create the proper ramp.                          */
/*                                                                         */
/***************************************************************************/
{
   ForceProfileStartFlag = TRUE;
   ForceTimeRange = Time1 - Time0;
   ForceRange = (Force1 - Force0);
   StartForce = Force0;
   StartForceTime = Time0;
   return(Force0);
}



SINT16 InterpolateForce(SINT32 Time)
/***************************************************************************/
/*                                                                         */
/* This function uses the calculations done by the SetupInterpolateForce   */
/* function.  It is called every ms to create the proper force ramp.       */
/*                                                                         */
/***************************************************************************/
{
   SINT16  Retval = 0;

   if (ForceTimeRange != 0) {
      Retval = (StartForce + (SINT16)(((Time - StartForceTime) * ForceRange) / ForceTimeRange));
   }
   return(Retval);
}
