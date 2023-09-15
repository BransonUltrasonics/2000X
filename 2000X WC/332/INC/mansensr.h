/* $Header:   K:\APPS\PVCS Pro\332new\INC\MANSENSR.H_V   2.21   Feb 08 2000 10:30:18   lmarkure  $ */
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
/*************************                         **************************/

/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      mansensr.h


        Written by: Laura Markure  
          Date: 3/14/96  
          Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
       0           4/21/96       LAM         Initial
       1           5/20/96       LAM         Clean UP
       2           07-18-96      BEKymer     Prototypes for SelectForceControl
                                             and SelectVelocityControl
       3           07-31-96      LAM         added selectpvpcontrol 
       4           08-31-96      LAM         added average power    
       5           10-14-96      LAM         added startingvelocity 
       6           03-02-97      LAM         added freqoffset       
       7.2.10      08-17-97      LAM         deleted averagepower, getpower
       2.11        03/15/99      LAM         added Stage variable to SetVel and 
                                             SetForce prototypes
       2.11.1.1    06-23-99      JZ          added SetPV, deleted SetForce, SetVelocity
                                             enum STAGE Stage
       2.11.1.2    07-01-99      JZ          added defines for ramps 
       2.12        08-03-99      LAM         deleted unused prototypes
       2.14        08-06-99      JZ          added InitializePV(), typecasted PV_IDLE_VALUE
       2.15        08-16-99      LAM         added shut down define
       2.17        08-26-99      JZ          chngd PV_IDLE_VALUE to 20
       2.18        10-08-99      BEKymer     Add defines for cylinder dependent step limits
       2.19        10-12-99      BEKymer     Added NO_LIMIT define
       2.20        10-26-99      JZ          removed PV_IDLE_VALUE and cleaned typecasting
       2.21        02-08-00      LAM         added case for setting pv d/a to zero
 ------------------------------- DESCRIPTION -----------------------------------


 

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"

/*****     *****     General purpose variables     *****     *****/
 
#define SHIFT_SLOWEST    6  /* divide by 64     these values are the number of times */
#define SHIFT_SLOW       5  /* divide by 32     the value is shifted     */
#define SHIFT_NORMAL     4  /* divide by 16 */
#define SHIFT_FAST       3  /* divide by 8 */
#define SHIFT_FASTEST    2  /* divide by 4 */
#define SHUT_DOWN_VALUE  0  
                         
/* this structure is used to define the possible stages of the weld cycle */
#ifndef ALREADY_DEFINED
#define ALREADY_DEFINED
enum STAGE {
   RT_TO_DWNSPD = 1,      /* rapid traverse to downspeed using RunningPreset.RTRamp            */
   TRG_TO_FORCE_A,        /* from part contact to weld force A using RunningPreset.WeldFR      */
   FORCE_A_TO_FORCE_B,    /* from weld force A to weld force B using Runningpreset.StepFR      */
   FORCE_B_TO_HOLD,       /* from Force B to hold force using RunningPreset.HoldFR             */
   HOLD_TO_HOME,          /* from hold force to home idle value using RunningPreset.ReturnRamp */
   HOME_TO_RT,            /* from home idle to rapid traverse using RunningPreset.RTRamp       */
   HOME_TO_DWNSPD,        /* from home idle to downspeed using RunningPreset.RTRamp            */
   ZERO_PSI,              /* used when psi is below the minimum allowed                        */
   FORCE_CALIBRATION };   /* calibration velocity                                              */

typedef struct R1 {
   UINT16  CurrentValue;     /* In D/A counts (0-65535)    */
   UINT16  TargetValue;      /* In D/A counts (0-65535)    */
   UINT16  ShiftValue;       /* Shift right 0-6 places     */
   UINT16  CurrentStepLimit; /* In D/A counts (0-65535)    */
   UINT16  CylinderStepLimit;/* In D/A counts (0-65535)    */
} RAMP;
#endif

void ManageSensors(void);
void SetCurrentAmp(SINT32 Amplitude);          /* weldhold, profile  */                            
void SetCurrentFreqOffset(SINT32 FreqOffset);  /* frequency offset  */                            
void SetPV(UINT16 InitVel, enum STAGE Stage);    
void InitializePV(void);


#define MAX_VELOCITY_PTS   101
#define MAX_FREQ_PTS       1001
#define MAX_AMP_PTS        101

#define STEPLIMIT_1_5in       4396
#define STEPLIMIT_2_0in       2157
#define STEPLIMIT_2_5in       1266
#define STEPLIMIT_3_0in       879
#define STEPLIMIT_3_25in      742
            
#define NO_LIMIT              65535

