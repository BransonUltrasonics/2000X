/* $Header:   K:/APPS/PVCS Pro/332new/App/MENUPSAL.C_V   1.4   May 26 2000 15:45:22   shishir  $ */
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

/*--------------------------- MODULE DESCRIPTION ---------------------------*/

/*   Module name:     PROCESS_SUSPECT_ALARM_TEXT                            */
/*                                                                          */
/*   Filename:        menupsal.c                                            */
/*                                                                          */
/*   Function name:                                                         */
//
//
/*------------------------------- REVISIONS --------------------------------*/
/*                                                                          */
/*   Revision #      Date          Author      Description                  */
/*   ==========     ========       ======      ===========                  */
/*      1.0         07-11-97       BEKymer     Initial Version              */
/*      1.1         09-11-97       PaulG       Cleanup data                 */
//      1.2         10.30.97       JBerman     Dedicate variables to be Suspect
//                                             by adding S in the end of the 
//                                             LimitMenu.
//      1.3         11-18-97       LAM         chged welddata to finalresults
//      1.4         05-26-00       SCM         Checked in for testing by Laura, John.                                                              
//
//
/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with the Process Suspect Limit Alarms and their submenus */


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"
#include "menu.h"
#include "weld_obj.h"
#include "genalarm.h"


/*----------------------------- EXTERNAL DATA ------------------------------*/

extern WELD_DATA FinalResults;

extern const STR *const StrSuspAlarm[];        /* "SUSP ALARMS" */
extern const STR *const StrPS_1 [];            /* -S Energy Limit    */
extern const STR *const StrPS_2 [];            /* +S Energy Limit    */
extern const STR *const StrPS_3 [];            /* -S Pk Power Limit  */
extern const STR *const StrPS_4 [];            /* +S Pk Power Limit  */
extern const STR *const StrPS_5 [];            /* -S Col Dist Limit  */
extern const STR *const StrPS_6 [];            /* +S Col Dist Limit  */
extern const STR *const StrPS_7 [];            /* -S Abs Dist Limit  */
extern const STR *const StrPS_8 [];            /* +S Abs Dist Limit  */
extern const STR *const StrPS_9 [];            /* -S Trig Dist Limit */
extern const STR *const StrPS_10[];            /* +S Trig Dist Limit */
extern const STR *const StrPS_11[];            /* -S Max Force Limit */
extern const STR *const StrPS_12[];            /* +S Max Force Limit */
extern const STR *const StrPS_13[];            /* -S Time Limit      */
extern const STR *const StrPS_14[];            /* +S Time Limit      */

extern MENU MPeakEnergyLimitMenuS;
extern MENU PPeakEnergyLimitMenuS;
extern MENU MPeakPwrLimitMenuS;
extern MENU PPeakPwrLimitMenuS;
extern MENU MColDistLimitMenuS;
extern MENU PColDistLimitMenuS;
extern MENU MAbsDistLimitMenuS;
extern MENU PAbsDistLimitMenuS;
extern MENU MTrigDistLimitMenuS;
extern MENU PTrigDistLimitMenuS;
extern MENU MForceLimitMenuS;
extern MENU PForceLimitMenuS;
extern MENU PTimeLimitMenuS;
extern MENU MTimeLimitMenuS;


/*
 ---------------------------- LOCAL TYPE VARIABLES -------------------------
*/

MENUEND endlistSP = { TRUE };

/*
 ---------------------------------- CODE -------------------------------------
*/


const TITLE titleSuspectLimits = {
    StrSuspAlarm,                 /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    FALSE,                        /* TRUE if should look at next pointer   */
    NULL,                         /* Pointer to where enable flag is       */
    FALSE,                        /* TRUE if should center justify field   */
    TRUE,                         /* TRUE if page information should show  */
    TRUE   };                     /* TRUE if text should be uppercased     */

const ALARM EnergyMinusSLimit = {
    StrPS_1,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT1,                         /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &MPeakEnergyLimitMenuS,        /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM EnergyPlusSLimit = {
    StrPS_2,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT2,                         /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &PPeakEnergyLimitMenuS,        /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM PkPowerMinusSLimit = {
    StrPS_3,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT3,                         /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &MPeakPwrLimitMenuS,           /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM PkPowerPlusSLimit = {
    StrPS_4,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT4,                         /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &PPeakPwrLimitMenuS,           /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM CollDistMinusSLimit = {
    StrPS_5,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT5,                         /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &MColDistLimitMenuS,           /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM CollDistPlusSLimit = {
    StrPS_6,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT6,                         /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &PColDistLimitMenuS,           /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM AbsDistMinusSLimit = {
    StrPS_7,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT7,                         /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &MAbsDistLimitMenuS,           /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM AbsDistPlusSLimit = {
    StrPS_8,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT8,                         /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &PAbsDistLimitMenuS,           /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM TrigDistMinusSLimit = {
    StrPS_9,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT9,                         /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &MTrigDistLimitMenuS,          /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM TrigDistPlusSLimit = {
    StrPS_10,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT10,                        /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &PTrigDistLimitMenuS,          /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM MaxForceMinusSLimit = {
    StrPS_11,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT11,                        /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &MForceLimitMenuS,             /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM MaxForcePlusSLimit = {
    StrPS_12,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT12,                        /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &PForceLimitMenuS,             /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM TimeMinusSLimit = {
    StrPS_13,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT13,                        /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &MTimeLimitMenuS,              /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM TimePlusSLimit = {
    StrPS_14,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT14,                        /* Bit Mask used for this menu enable    */
    &FinalResults.SuspectBitResult,   /* Pointer to where enable flag is       */
    &PTimeLimitMenuS,              /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */


const MENU SuspectLimitMenu[] = {{&titleSuspectLimits,         _TITLE    },
                                 {&EnergyMinusSLimit,          _ALARM    },
                                 {&EnergyPlusSLimit,           _ALARM    },
                                 {&PkPowerMinusSLimit,         _ALARM    },
                                 {&PkPowerPlusSLimit,          _ALARM    },
                                 {&CollDistMinusSLimit,        _ALARM    },
                                 {&CollDistPlusSLimit,         _ALARM    },
                                 {&AbsDistMinusSLimit,         _ALARM    },
                                 {&AbsDistPlusSLimit,          _ALARM    },
                                 {&TrigDistMinusSLimit,        _ALARM    },
                                 {&TrigDistPlusSLimit,         _ALARM    },
                                 {&MaxForceMinusSLimit,        _ALARM    },
                                 {&MaxForcePlusSLimit,         _ALARM    },
                                 {&TimeMinusSLimit,            _ALARM    },
                                 {&TimePlusSLimit,             _ALARM    },
                                 {&endlistSP,                  ENDLIST}  };

