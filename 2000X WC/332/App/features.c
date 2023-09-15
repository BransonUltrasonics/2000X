/* $Header:   K:\APPS\PVCS Pro\332new\App\FEATURES.C_V   1.19   Apr 05 2000 15:11:04   jzimny  $ */
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
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: features.c

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #  Date      Author   Description
   ==========  ========  ======   ===========
      0                           Initial Version
      1.01     07.17.97  JBerman  Creating this file
      1.20     07.18.97  JBerman  Comment future Releasse in UpdateSf().
      1.31     07.25.97  JBerman  TriggerDelayF  TrgDelBit->CrlAmpBit
      1.05     08.15.97  JBerman  Update BootSf()
      1.06     08.25.97  JBerman  Comment Out Advanced Counters
      1.07     09.08.97  LAM      unit test routine,chged some model numbers
      1.08     10.13.97  JBerman  Added ... & BIT0 -> UpdateSf
      1.9      10-31-97  BEKymer  Changed all menus from ADVANCED to NORMAL
                                  so they can be displayed after verify preset
                                  alarm caused by recalling an ADVANCED preset
                                  with features set to NORMAL.
      1.10     04-05-98  BJB      Calls SetAmpControl(), SetFreqControl() when
                                   amp & freq offset sources changed from adv
                                   features menu (bug fix).
      1.11     06-15-98  BJB      Added Digital Filter to adv features menu.
                                  Added "Features" to adv features menu.
      1.12     06-24-98  BJB      Changed NORMAL to BASIC.
      1.13     06-25-98  BJB      Moved CopyFeatureChoice to MENU7.C.
      1.14     06-26-98  BJB      Created second copy of Features menu for use
                                   by alarm.
      1.15     08.05.98  JBerman  Removed Digital Filter from All/Basic features
      1.16     10.26.98  LAM      made ampstep model = 3 from 4                  
      1.16.1.1 07-08-99  JZ       enabled Force2Flag check in BootSF
      1.18     08-25-99  JZ       added call to SelectWeldSetupMenu2
      1.18.6.1 02-07-99  JZ       removed DVS, added Mask1, Cond1, Mask2, Cond2
      1.19     04-05-00  JZ       merged Lang to trunk
      
------------------------------- DESCRIPTION ---------------------------------
*/                  

/*
This file will deal with Features: Normal Advanced menus


*/

//----------------------------- INCLUDE FILES --------------------------------


#include "portable.h"
#include "menu.h"
#include "preset.h"
#include "param.h"
#include "menu7.h"
#include "features.h"
#include "menu1.h"


//------------------------------ EXTERNAL DATA -------------------------------
                 

MENUEND endlist10 = { TRUE };



extern const SINT8 StrM2_46[];
extern const SINT8 StrM2_17[];
extern const SINT8 StrM7_4[];
extern const SINT8 StrM7_4A[];
extern const SINT8 StrM7_4B[];
extern const SINT8 StrM7_20[];
extern const SINT8 StrM7_28[];
extern const SINT8 StrM2_43[];
extern const SINT8 StrM7_23[];
extern const SINT8 StrM7_22[];
extern const SINT8 StrM7_24[];
extern const SINT8 StrM2_29[];
extern const SINT8 StrM7_26[];
extern const SINT8 StrM7_33[];
extern const SINT8 StrM2_74[];
extern const SINT8 StrM2_78[];
extern const SINT8 StrM2_42[];
extern const SINT8 StrM2_14[];
extern const SINT8 StrM7_22A[];
extern const SINT8 StrM7_22B[];
extern const SINT8 StrM0A_4[];     // "Adv Feat on".

extern const SINT8 StrOn[];
extern const SINT8 StrOff[];
extern const SINT8 StrGood[];
extern const SINT8 StrAll[];
extern const SINT8 StrFixed[];
extern const SINT8 StrStep[];

extern SETUPS CurrentPreset;
extern CONFIGSETUP CurrentSetup;
static UINT32 SF;  // Staus Fetures Register.

extern TOGGLE CopyFeatureChoice;
extern TOGGLE RealFeatureChoice;

//**********************************************************************

const ADVFEATURE TriggerDelayF= { // (1)
    StrM2_14,                     /* String to be displayed                */
    MODEL3,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentPreset.TriggerDelayFlag,     /* Pointer to where to put selection     */
    TrgDelBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrOff,                       /* Pointer to first choice string        */
    StrOn,                        /* Pointer to second choice string       */
    TRIGGERDELAYFLAG,             /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */

const ADVFEATURE ForceStepF = {  // (2)
    StrM2_17,                     /* String to be displayed                */
    MODEL3,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentPreset.Force2Flag,    /* Pointer to where to put selection     */
    FrcStpBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrFixed,                     /* Pointer to first choice string        */
    StrStep,                      /* Pointer to second choice string       */
    FORCESTEPFLAG,                /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */

const ADVFEATURE AmplitudeStepF = {  // (3)
    StrM2_29,                     /* String to be displayed                */
    MODEL3,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentPreset.Amp2Flag,      /* Pointer to where to put selection     */
    AmpStpBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrFixed,                     /* Pointer to first choice string        */
    StrStep,                      /* Pointer to second choice string       */
    AMPLITUDESTEPFLAG,            /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */

const ADVFEATURE PostWeldSeekChoiceF = {  // (5)
    StrM2_42,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentPreset.SeekFun,       /* Pointer to where to put selection     */
    PstWldBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrOff,                      /* Pointer to first choice string        */
    StrOn,                       /* Pointer to second choice string       */
    POSTWELDSEEK,                 /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */

const ADVFEATURE FreqOffsetChoiceF = {  // (6)
    StrM2_43,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentPreset.FreqOffsetFlag, /* Pointer to where to put selection     */
    FrqOfsBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrOff,                       /* Pointer to first choice string        */
    StrOn,                        /* Pointer to second choice string       */
    FREQOFFSETFLAG,               /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */

const ADVFEATURE CycleAbortsChoiceF = {  // (7)
    StrM2_78,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentPreset.CycleAbortFlag, /* Pointer to where to put selection     */
    CycAbtBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrOff,                       /* Pointer to first choice string        */
    StrOn,                        /* Pointer to second choice string       */
    CYCLEABORT,                   /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */

const ADVFEATURE ActClearOutputChoiceF = {  // (8)
    StrM7_24,                     /* String to be displayed                */
    MODEL3,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentPreset.ActClrFlag,    /* Pointer to where to put selection     */
    ActClrBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrOff,                       /* Pointer to first choice string        */
    StrOn,                        /* Pointer to second choice string       */
    ACTCLEARPOSSW,                /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */

const ADVFEATURE SuspectLimitsChoiceF = {  // (9)
    StrM2_46,                     /* String to be displayed                */
    MODEL2,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentPreset.SuspectLimitsFlag, /* Pointer to where to put selection     */
    SusLmtBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrOff,                       /* Pointer to first choice string        */
    StrOn,                        /* Pointer to second choice string       */
    SUSPECTLIMITSFLAG,            /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */

const ADVFEATURE AmpControlF = {  // (10)
    StrM7_22,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentSetup.AmpControl,     /* Pointer to where to put selection     */
    AmpCrlBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrM7_22A,                    /* Pointer to first choice string        */
    StrM7_22B,                    /* Pointer to second choice string       */
    AMPCONTROL,                   /* Identifier for this parameter         */
    SetAmpControl };              /* Pointer function to execute           */


const ADVFEATURE FreqControlF = {  // (11)
    StrM7_23,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentSetup.FreqControl,    /* Pointer to where to put selection     */
    FrqCrlBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrM7_22A,                    /* Pointer to first choice string        */
    StrM7_22B,                    /* Pointer to second choice string       */
    FREQCONTROL,                  /* Identifier for this parameter         */
    SetFreqControl };             /* Pointer function to execute           */

const ADVFEATURE AjustWhileRunF = {  // (12)
    StrM7_26,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentSetup.AdjustWhileRun, /* Pointer to where to put selection     */
    AdjWleBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrOff,                       /* Pointer to first choice string        */
    StrOn,                        /* Pointer to second choice string       */
    ADJUSTWHILERUN,               /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */

/*

const ADVFEATURE AdvCountersF = {   // (13)
    StrM7_28,                       // String to be displayed                
    MODEL1,                         // Lowest model to be displayed on       
    DONTCARE,                       // What actuator is required             
    BASIC,                          // What is user experience level         
    ALLMODES,                       // Which welding mode to display line    
    OPERATOR,                       // What is security level of operator    
    FALSE,                          // The linear encoder is needed          
    0,                              // what is important to           Mask1  
    0,                              // display this menu              Cond1  
    0,                              // what conditions are required   Mask2  
    0,                              // to display this menu           Cond2  
    &CurrentSetup.AdvanceCounters,  // Pointer to where to put selection    
    AdvCnrBit,                      // The Corresponding bit; BIT. 
    &SF,                            // The address of Status Features Register
    StrGood,                        // Pointer to first choice string        
    StrAll,                         // Pointer to second choice string       
    ADVANCEDCOUNTERS,               // Identifier for this parameter         
    NULL };                         // Pointer function to execute           

*/
   
const ADVFEATURE ControlLimitsChoiceF = {  // (14)
    StrM2_74,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentPreset.ControlLimitsFlag,  /* Pointer to where to put selection     */
    CrlLmtBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrOff,                       /* Pointer to first choice string        */
    StrOn,                        /* Pointer to second choice string       */
    CONTROLLIMITSFLAG,            /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */

const ADVFEATURE SequencingChoiceF = {  // (15)
    StrM7_33,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    &CurrentSetup.SequenceFlag,   /* Pointer to where to put selection     */
    SeqOnfBit,                    // The Corresponding bit; BIT. 
    &SF,                          // The address of Status Features Register
    StrOff,                       /* Pointer to first choice string        */
    StrOn,                        /* Pointer to second choice string       */
    SEQUENCEFLAG,                 /* Identifier for this parameter         */
    NULL };                       /* Pointer function to execute           */



//**********************************************************************
   
   
    
const TITLE Features = {
    StrM0A_4,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BASIC,                        /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The linear encoder is needed          */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    FALSE,                        /* TRUE if should look at next pointer   */
    NULL,                         /* Pointer to where enable flag is       */
    FALSE,                        /* TRUE if should center justify field   */
    TRUE,                         /* TRUE if page information should show  */
    TRUE   };                     /* TRUE if text should be uppercased     */


    

/* Welcome to Kludge City.  The following two menus need to be identical    */
/* EXCEPT for this: CopyFeatureChoice must be in the first menu, which      */
/* appears when the user tries to change from All features to Basic, and    */
/* RealFeatureChoice must appear on the second menu, which appears when     */
/* the user gets additional information on the alarm "Non Basic Feat. Used" */
/* The latter menu item directly edits CurrentPreset.Features, while in the */
/* former menu, a copy of CurrentPreset.Features is edited.                 */

const MENU FeatureOptionsMenu[] = { {&Features,               _TITLE      },
                                   {&CopyFeatureChoice,       _TOGGLE     },
                                   {&TriggerDelayF,           _ADVFEATURE },
                                   {&ForceStepF,              _ADVFEATURE },
                                   {&AmplitudeStepF,          _ADVFEATURE },
                                   {&PostWeldSeekChoiceF,     _ADVFEATURE },
                                   {&FreqOffsetChoiceF,       _ADVFEATURE },
                                   {&CycleAbortsChoiceF,      _ADVFEATURE },
                                   {&ActClearOutputChoiceF,   _ADVFEATURE },
                                   {&SuspectLimitsChoiceF,    _ADVFEATURE },
                                   {&AmpControlF,             _ADVFEATURE },
                                   {&FreqControlF,            _ADVFEATURE },
                                   {&AjustWhileRunF,          _ADVFEATURE },
                                   {&ControlLimitsChoiceF,    _ADVFEATURE },
                                   {&SequencingChoiceF,       _ADVFEATURE }, 
                                   {&endlist10,               ENDLIST}  };


const MENU FeatureOptionsMenu2[]= { {&Features,               _TITLE      },
                                   {&RealFeatureChoice,       _TOGGLE     },
                                   {&TriggerDelayF,           _ADVFEATURE },
                                   {&ForceStepF,              _ADVFEATURE },
                                   {&AmplitudeStepF,          _ADVFEATURE },
                                   {&PostWeldSeekChoiceF,     _ADVFEATURE },
                                   {&FreqOffsetChoiceF,       _ADVFEATURE },
                                   {&CycleAbortsChoiceF,      _ADVFEATURE },
                                   {&ActClearOutputChoiceF,   _ADVFEATURE },
                                   {&SuspectLimitsChoiceF,    _ADVFEATURE },
                                   {&AmpControlF,             _ADVFEATURE },
                                   {&FreqControlF,            _ADVFEATURE },
                                   {&AjustWhileRunF,          _ADVFEATURE },
                                   {&ControlLimitsChoiceF,    _ADVFEATURE },
                                   {&SequencingChoiceF,       _ADVFEATURE }, 
                                   {&endlist10,               ENDLIST}  };


// Update Status Featurs register. It gives an indication for their status. 


void UpdateSf(enum PARAM id)
{
   SelectWeldSetupMenu2();
   switch (id) {

      case SUSPECTLIMITSFLAG:
         if (CurrentPreset.SuspectLimitsFlag & BIT0)
            SF=SF|SusLmtBit;
         else
            SF=SF&(~SusLmtBit);  // Clear the corresponding bit.
         break; 

      case FORCESTEPFLAG:
         if (CurrentPreset.Force2Flag & BIT0)
            SF=SF|FrcStpBit;
         else
            SF=SF&(~FrcStpBit);  // Clear the corresponding bit.
         break;

      case ADVANCEDCOUNTERS:
         // if (CurrentSetup.AdvanceCounters & BIT0)
         //    SF=SF|AdvCnrBit;
         // else
           
         SF=SF&(~AdvCnrBit);  // Clear the corresponding bit.
         break;

      case FREQOFFSETFLAG:
         if (CurrentPreset.FreqOffsetFlag & BIT0)
            SF=SF|FrqOfsBit;
         else
            SF=SF&(~FrqOfsBit);  // Clear the corresponding bit.
         break;

      case FREQCONTROL:
         if ( !(CurrentSetup.FreqControl & BIT0) )
            SF=SF|FrqCrlBit;
         else
            SF=SF&(~FrqCrlBit);  // Clear the corresponding bit.
         break;

      case AMPCONTROL:
         if ( !(CurrentSetup.AmpControl & BIT0) )
            SF=SF|AmpCrlBit;
         else
            SF=SF&(~AmpCrlBit);  // Clear the corresponding bit.
         break;

      case ACTCLEARPOSSW:
         if (CurrentPreset.ActClrFlag & BIT0)
            SF=SF|ActClrBit;
         else
            SF=SF&(~ActClrBit);  // Clear the corresponding bit.
         break;

      case AMPLITUDESTEPFLAG:
         if (CurrentPreset.Amp2Flag & BIT0)
            SF=SF|AmpStpBit;
         else
            SF=SF&(~AmpStpBit);  // Clear the corresponding bit.
         break;

      case ADJUSTWHILERUN:
         if (CurrentSetup.AdjustWhileRun & BIT0)
            SF=SF|AdjWleBit;
         else
            SF=SF&(~AdjWleBit);  // Clear the corresponding bit.
         break;

      case SEQUENCEFLAG:
         if (CurrentSetup.SequenceFlag & BIT0)
            SF=SF|SeqOnfBit;
         else
            SF=SF&(~SeqOnfBit);  // Clear the corresponding bit.
         break;

      case CONTROLLIMITSFLAG:
         if (CurrentPreset.ControlLimitsFlag & BIT0)
            SF=SF|CrlLmtBit;
         else
            SF=SF&(~CrlLmtBit);  // Clear the corresponding bit.
         break;

      case CYCLEABORT:
         if (CurrentPreset.CycleAbortFlag & BIT0)
            SF=SF|CycAbtBit;
         else
            SF=SF&(~CycAbtBit);  // Clear the corresponding bit.
         break;

      case POSTWELDSEEK:
         if (CurrentPreset.SeekFun & BIT0)
            SF=SF|PstWldBit;
         else
            SF=SF&(~PstWldBit);  // Clear the corresponding bit.
         break;

      case TRIGGERDELAYFLAG:
         if (CurrentPreset.TriggerDelayFlag & BIT0)
            SF=SF|TrgDelBit;
         else
            SF=SF&(~TrgDelBit);  // Clear the corresponding bit.
         break;

 
      default:
            SF=SF;   // For debugging purpesses only.
         break;
   
   }
}





// Update Status Featurs register during boot-up. 
// For Future Release: Remove the corresponding comments J.B.


void BootSf(void)
{
   if ((CurrentPreset.SuspectLimitsFlag & BIT0) == TRUE)
     SF=SF|SusLmtBit;
   else
      SF=SF&(~SusLmtBit);  // Clear the corresponding bit.
   
   
   
   if ((CurrentPreset.Force2Flag & BIT0) == TRUE)  
      SF=SF|FrcStpBit;
   else
      SF=SF&(~FrcStpBit);  // Clear the corresponding bit.
   
   
      
   // if ((CurrentSetup.AdvanceCounters & BIT0) == TRUE)
   //    SF=SF|AdvCnrBit;
   // else
   
   SF=SF&(~AdvCnrBit);  // Clear the corresponding bit.
   

   if ((CurrentPreset.FreqOffsetFlag & BIT0) == TRUE)
      SF=SF|FrqOfsBit;
   else
      SF=SF&(~FrqOfsBit);  // Clear the corresponding bit.
   
   if ((!CurrentSetup.FreqControl & BIT0) == TRUE)
      SF=SF|FrqCrlBit;
   else
      SF=SF&(~FrqCrlBit);  // Clear the corresponding bit.
   
   if ((!CurrentSetup.AmpControl & BIT0) == TRUE)
      SF=SF|AmpCrlBit;
   else
      SF=SF&(~AmpCrlBit);  // Clear the corresponding bit.
       
   if ((CurrentPreset.ActClrFlag & BIT0) == TRUE)
      SF=SF|ActClrBit;
   else
      SF=SF&(~ActClrBit);  // Clear the corresponding bit.
   
   if ((CurrentPreset.Amp2Flag & BIT0) == TRUE)
      SF=SF|AmpStpBit;
   else
      SF=SF&(~AmpStpBit);  // Clear the corresponding bit.
   
   
   // if ((CurrentSetup.AdjustWhileRun & BIT0) == TRUE) !!! FUTURE RELEASE !!!
   //    SF=SF|AdjWleBit;
   // else
   
   
   SF=SF&(~AdjWleBit);  // Clear the corresponding bit.
   
   
   
   // if ((CurrentSetup.SequenceFlag & BIT0) == TRUE)  !!! FUTURE RELEASE !!!
   //    SF=SF|SeqOnfBit;
   // else
     
   SF=SF&(~SeqOnfBit);  // Clear the corresponding bit.
   
   
   if ((CurrentPreset.ControlLimitsFlag & BIT0) == TRUE)
      SF=SF|CrlLmtBit;
   else
      SF=SF&(~CrlLmtBit);  // Clear the corresponding bit.
   
   if ((CurrentPreset.CycleAbortFlag & BIT0) == TRUE)
      SF=SF|CycAbtBit;
   else
      SF=SF&(~CycAbtBit);  // Clear the corresponding bit.
   
   if ((CurrentPreset.SeekFun & BIT0) == TRUE)
      SF=SF|PstWldBit;
   else
      SF=SF&(~PstWldBit);  // Clear the corresponding bit.
   
   
   // if ((CurrentPreset.TriggerDelayFlag & BIT0) == TRUE) !!! FUTURE RELEASE !!!
   //    SF=SF|TrgDelBit;
   // else
      
   SF=SF&(~TrgDelBit);  // Clear the corresponding bit.
}


// SF register is a static protected variable. Any other file can test
// if all the features turned of or not.


BOOLEAN GetSF(void) {
   if (SF==0)       // All features turned off.
      return 1;
   else
     return 0;      // Atleast 1 or more feature is on 
}




UINT8 IfFeatureEnabled(UINT32 AlarmCopy, UINT32 BitMask)
{
   UINT8 AlarmEnabled = FALSE;

   if(AlarmCopy & BitMask)
      AlarmEnabled = TRUE;

   return(AlarmEnabled);   
}
