/* $Header:   K:/APPS/PVCS Pro/332new/App/MENUPRAL.C_V   1.3   May 26 2000 15:44:24   shishir  $ */

/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                           */
/*                                                                          */
/*************************                         **************************/

/*--------------------------- MODULE DESCRIPTION ---------------------------*/


/*   Module name:       PROCESS_REJECT_ALARM_TEXT                           */
/*                                                                          */
/*   Filename:          menupral.c                                          */
/*                                                                          */
/*   Function name:                                                         */


/*------------------------------- REVISIONS --------------------------------*/
/*                                                                            */
/*   Revision #    Date          Author      Description                    */
/*   ==========    ========      ======      ===========                    */
/*      1.0        10-08-96      PhilJ       Initial Version                */
/*      1.1        01-23-97      PhilJ       Updated alarms per BETA Rel.1  */
//      1.1        10.30.97      JBerman     Dedicate variables to be Reject
//                                           by adding R in the end of the 
//                                           LimitMenu.
//      1.2        11-18-97      LAM         chged welddata to finalresults
//      1.3        05-26-00      SCM         Checked in for testing by Laura, John.
//
/*------------------------------- DESCRIPTION ------------------------------*/


/* This file deals with the Reject Limit Alarms and their submenus          */


/*------------------------------ INCLUDE FILES -----------------------------*/

#include "portable.h"
#include "menu.h"
#include "weld_obj.h"
#include "genalarm.h"


/*------------------------------ EXTERNAL DATA -----------------------------*/

extern WELD_DATA FinalResults;

extern const STR *const StrRejAlarm[];        /* "REJ ALARMS" */
extern const STR *const StrMinusEnergyR[];     /* "Energy -R Limit" */
extern const STR *const StrPlusEnergyR[];      /* "Energy +R Limit" */
extern const STR *const StrMinusPkPowerR[];    /* "Pk Power -R Limit" */
extern const STR *const StrPlusPkPowerR[];     /* "Pk Power +R Limit" */
extern const STR *const StrMinusCollapseR[];   /* "Col Dist -R Limit" */
extern const STR *const StrPlusCollapseR[];    /* "Col Dist +R Limit" */
extern const STR *const StrMinusAbsR[];        /* "Abs Dist -R Limit" */
extern const STR *const StrPlusAbsR[];         /* "Abs Dist +R Limit" */
extern const STR *const StrMinusTriggerR[];    /* "Trig Dist -R Limit" */
extern const STR *const StrPlusTriggerR[];     /* "Trig Dist +R Limit" */
extern const STR *const StrMinusMaxForceR[];   /* "Max Force -R Limit" */
extern const STR *const StrPlusMaxForceR[];    /* "Max Force +R Limit" */
extern const STR *const StrMinusTimeR[];       /* "Time +R Limit" */
extern const STR *const StrPlusTimeR[];        /* "Time -R Limit" */

extern const STR *const StrPR_1 [];    /* -R Energy Limit    */
extern const STR *const StrPR_2 [];    /* +R Energy Limit    */
extern const STR *const StrPR_3 [];    /* -R Pk Power Limit  */
extern const STR *const StrPR_4 [];    /* +R Pk Power Limit  */
extern const STR *const StrPR_5 [];    /* -R Col Dist Limit  */
extern const STR *const StrPR_6 [];    /* +R Col Dist Limit  */
extern const STR *const StrPR_7 [];    /* -R Abs Dist Limit  */
extern const STR *const StrPR_8 [];    /* +R Abs Dist Limit  */
extern const STR *const StrPR_9 [];    /* -R Trig Dist Limit */
extern const STR *const StrPR_10[];    /* +R Trig Dist Limit */
extern const STR *const StrPR_11[];    /* -R Max Force Limit */
extern const STR *const StrPR_12[];    /* +R Max Force Limit */
extern const STR *const StrPR_13[];    /* -R Time Limit      */
extern const STR *const StrPR_14[];    /* +R Time Limit      */
extern const STR *const StrPR_15[];    /* Energy Not Reached */
extern const STR *const StrPR_16[];    /*                    */
extern const STR *const StrPR_17[];    /*                    */
extern const STR *const StrPR_18[];    /* LL Not Reached     */

extern MENU MPeakEnergyLimitMenuR;
extern MENU PPeakEnergyLimitMenuR;
extern MENU MPeakPwrLimitMenuR;
extern MENU PPeakPwrLimitMenuR;
extern MENU MColDistLimitMenuR;
extern MENU PColDistLimitMenuR;
extern MENU MAbsDistLimitMenuR;
extern MENU PAbsDistLimitMenuR;
extern MENU MTrigDistLimitMenuR;
extern MENU PTrigDistLimitMenuR;
extern MENU MForceLimitMenuR;
extern MENU PForceLimitMenuR;
extern MENU PTimeLimitMenuR;
extern MENU MTimeLimitMenuR;


/*-------------------------- LOCAL TYPE VARIABLES --------------------------*/

MENUEND endlistRJ = { TRUE };


/*---------------------------------- CODE ----------------------------------*/


const TITLE titleRejectLimits = {
    StrRejAlarm,                  /* String to be displayed                */
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

const ALARM EnergyMinusRLimit = {
    StrPR_1,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT1,                         /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &MPeakEnergyLimitMenuR,       /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM EnergyPlusRLimit = {
    StrPR_2,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT2,                         /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &PPeakEnergyLimitMenuR,       /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM PkPowerMinusRLimit = {
    StrPR_3,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT3,                         /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &MPeakPwrLimitMenuR,          /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM PkPowerPlusRLimit = {
    StrPR_4,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT4,                         /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &PPeakPwrLimitMenuR,          /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM CollDistMinusRLimit = {
    StrPR_5,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT5,                         /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &MColDistLimitMenuR,          /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM CollDistPlusRLimit = {
    StrPR_6,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT6,                         /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &PColDistLimitMenuR,          /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM AbsDistMinusRLimit = {
    StrPR_7,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT7,                         /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &MAbsDistLimitMenuR,          /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM AbsDistPlusRLimit = {
    StrPR_8,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT8,                         /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &PAbsDistLimitMenuR,          /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM TrigDistMinusRLimit = {
    StrPR_9,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT9,                         /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &MTrigDistLimitMenuR,         /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM TrigDistPlusRLimit = {
    StrPR_10,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT10,                        /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &PTrigDistLimitMenuR,         /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM MaxForceMinusRLimit = {
    StrPR_11,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    EP,                           /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT11,                        /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &MForceLimitMenuR,            /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM MaxForcePlusRLimit = {
    StrPR_12,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    EP,                           /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT12,                        /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &PForceLimitMenuR,            /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM TimeMinusRLimit = {
    StrPR_13,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT13,                        /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &MTimeLimitMenuR,             /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */

const ALARM TimePlusRLimit = {
    StrPR_14,                     /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    BIT14,                        /* Bit Mask used for this menu enable    */
    &FinalResults.RejectBitResult,    /* Pointer to where enable flag is       */
    &PTimeLimitMenuR,             /* Pointer to sub menus                  */
    NULL   };                     /* Pointer function to execute           */



const MENU RejectLimitMenu[] = { {&titleRejectLimits,          _TITLE    },
                                 {&EnergyMinusRLimit,          _ALARM    },
                                 {&EnergyPlusRLimit,           _ALARM    },
                                 {&PkPowerMinusRLimit,         _ALARM    },
                                 {&PkPowerPlusRLimit,          _ALARM    },
                                 {&CollDistMinusRLimit,        _ALARM    },
                                 {&CollDistPlusRLimit,         _ALARM    },
                                 {&AbsDistMinusRLimit,         _ALARM    },
                                 {&AbsDistPlusRLimit,          _ALARM    },
                                 {&TrigDistMinusRLimit,        _ALARM    },
                                 {&TrigDistPlusRLimit,         _ALARM    },
                                 {&MaxForceMinusRLimit,        _ALARM    },
                                 {&MaxForcePlusRLimit,         _ALARM    },
                                 {&TimeMinusRLimit,            _ALARM    },
                                 {&TimePlusRLimit,             _ALARM    },
                                 {&endlistRJ,                  ENDLIST}  };
