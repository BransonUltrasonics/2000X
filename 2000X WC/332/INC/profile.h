
/* $Header:   K:\APPS\PVCS Pro\332new\INC\PROFILE.H_V   2.7   May 18 1999 11:26:48   lmarkure  $ */
#ifndef PROFILE_H
#define PROFILE_H
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
/***************************************************************************/
/*
------------------------------ REVISIONS ------------------------------------

/* Rev #  Date       Author   Description
/* =====  ========   ======   ===========

/* 2.3    04.03.98   JBerman  Due to duplications, with enum PROFILE        */
/*                            , changed typedef struct P1 to be PROF        */
/* 2.4    03-12-99   BEKymer  Changed NMBRPOINTS from 20 to 15 to allow     */
/*							  adding stuff to the preset and keep things    */
/*							  lined up                                      */
/*                            For the future, add col & abs to TRIGGER      */
/*                                                                          */
/* 2.5    04-20-99   OFI      Changed for DIAB                              */                                           
/* 2.6    05-10-99   LAM      added packed for DIAB	                        */
/* 2.7	  05-18-99   LAM      Fixed structure to be same size as Microtec   */



#define NMBRPOINTS   15          /* Maximum number points in profile      */


__packed__ enum TRIGGER {
   TIMETRIG,                      /* Time, started at force trigger        */
   COLLAPSETRIG,                  /* Distance from ULS                     */
   ABSOLUTETRIG,                  /* Distance from trigger                 */
   ENERGYTRIG,                    /* Energy accumulated from sonics on     */
   POWERTRIG,                     /* Peak power, valid only after sonics on*/
   EXTERNALTRIG,                  /* External, valid only after sonics on  */
   EXTEND_TRIGGER = 65535u        /* Force to 16 bit values                */
   };


__packed__ enum PROFILE {
   AMPLITUDEPROFILE,
   FORCEPROFILE,
   ALLPROFILES,
   EXTEND_PROFILE = 65535u        /* Force to 16 bit values                */
   };


/***************************************************************************/
/*                                                                         */
/*  The following typedef members are defined as:                          */
/*                                                                         */
/*      Points - the number of points actually used in the profile.  This  */
/*               number must be equal to or less then NMBRPOINTS and at    */
/*               least two if profiling is enabled.                        */
/*                                                                         */
/*      Trigger - This is an enum of type TRIGGER which defines what event */
/*               will start the trigger.  In all cases except EXTERNALTRIG */
/*               a value is needed.  This value is in member Value index 0.*/
/*                                                                         */
/*      Units -  This indicates what the member Value represents (Time,    */
/*               distance, energy, or power).                              */
/*                                                                         */
/*      X_axis-  This is the value used to decide if the next step of the  */
/*               profile should be sent out.  The units of the value are   */
/*               defined in member X_axis.                                 */
/*                                                                         */
/*      Y_axis   This is the value sent out for either amplitude or force. */
/*                                                                         */
/***************************************************************************/

typedef __packed__(2,1) struct P1 {
   SINT16 Points;                 /* Number of points in this profile      */
   enum   TRIGGER Trigger;        /* What event starts the profile         */
   enum   TRIGGER Units;          /* What unit is on x scale               */
   SINT32 X_axis[NMBRPOINTS];     /* Each step value, [0] = initial value  */
   SINT16 Y_axis[NMBRPOINTS];     /* Next step trigger [0]=initial         */
   } PROF;


/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

void   ResetProfile(enum PROFILE Profile);
void   CheckProfile(enum PROFILE Profile);
SINT16 SetupInterpolateAmp(SINT32 Time0, SINT32 Time1, SINT16 Amp0, SINT16 Amp1);
SINT16 InterpolateAmp(SINT32 Time);
SINT16 SetupInterpolateForce(SINT32 Time0, SINT32 Time1, SINT16 Force0, SINT16 Force1);
SINT16 InterpolateForce(SINT32 Time);




#endif
