/* $Header:   K:/APPS/PVCS Pro/332new/App/MENUPO.C_V   1.4   May 26 2000 15:43:36   shishir  $ */
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
/*
/*
/*---------------------------- MODULE DESCRIPTION --------------------------*/

/* Module name: menupo.c                                                    */

/* Filename:                                                                */

/* Function name:  Menu Power On                                            */


/*-------------------------------- REVISIONS -------------------------------*/
/*                                                                          */
/* Revision #  Date      Author   Description                               */
/* ==========  ========  ======   ===========                               */
/*    0        10-19-96  BEKymer  Initial Version                           */
/*    1.3      07-03-97  PhilJ    Deleted text2000w_EP menu, Replaced Rom   */
/*                                type text strings with Ram type           */
/*    1.4      05-26-00   SCM      Checked in for testing by Laura, John.   */
/*                                                                          */
/*------------------------------- DESCRIPTION ------------------------------*/
 
/* This file will deal with the power screen.                               */


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"
#include "menu.h"
#include "param.h"
#include "preset.h"


/*------------------------------ EXTERNAL DATA -----------------------------*/

extern SETUPS CurrentPreset;
extern SETUPS MaxLimit;
extern SETUPS MinLimit;

extern SINT8 *PwrOnStr1[];
extern SINT8 *PwrOnStr2[];
extern SINT8 *PwrOnStr3[];

extern const STR *const StrPO_3[];  /* Checking Controls */

/*--------------------------- PRIVATE GLOBAL DATA --------------------------*/
/*                       (scope is global to THIS file)                     */


static MENUEND endlistPO = { TRUE };


/*---------------------------------- CODE ----------------------------------*/

const TITLE titleBranson = {
    PwrOnStr1,                    /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    NORMAL,                       /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    FALSE,                        /* TRUE if should look at next pointer   */
    NULL,                         /* Pointer to where enable flag is       */
    FALSE,                        /* TRUE if should center justify field   */
    FALSE,                        /* TRUE if page information should show  */
    FALSE  };                     /* TRUE if text should be uppercased     */

//const TEXT text2000W_EP = {
//    StrPO_7,                      /* String to be displayed                */
//    MODEL1,                       /* Lowest model to be displayed on       */
//    EP,                           /* What actuator is required             */
//    BEGINNER,                     /* What is user experience level         */
//    ALLMODES,                     /* Which welding mode to display line    */
//    OPERATOR,                     /* What is security level of operator    */
//    FALSE,                        /* The DVS option is needed              */
//    FALSE,                        /* TRUE if should look at next pointer   */
//    NULL,                         /* Pointer to where enable flag is       */
//    FALSE,                        /* TRUE:Right justify  FALSE:Left justify*/
//    NULL      };                  /* Pointer function to execute           */
    
const TEXT text2000W_AE = {
    PwrOnStr2,                    /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BEGINNER,                     /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    FALSE,                        /* TRUE if should look at next pointer   */
    NULL,                         /* Pointer to where enable flag is       */
    FALSE,                        /* TRUE:Right justify  FALSE:Left justify*/
    NULL      };                  /* Pointer function to execute           */
    
const TEXT textControlVersion = {
    PwrOnStr3,                    /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BEGINNER,                     /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    FALSE,                        /* TRUE if should look at next pointer   */
    NULL,                         /* Pointer to where enable flag is       */
    FALSE,                        /* TRUE:Right justify  FALSE:Left justify*/
    NULL      };                  /* Pointer function to execute           */
    
const TEXT textChecking = {
    StrPO_3,                      /* String to be displayed                */
    MODEL1,                       /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    BEGINNER,                     /* What is user experience level         */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    FALSE,                        /* The DVS option is needed              */
    FALSE,                        /* TRUE if should look at next pointer   */
    NULL,                         /* Pointer to where enable flag is       */
    FALSE,                        /* TRUE:Right justify  FALSE:Left justify*/
    NULL      };                  /* Pointer function to execute           */
    



const MENU PowerOnMenu[] =     { {&titleBranson,              _TITLE    },
//                                 {&text2000W_EP,              _TEXT     },
                                 {&text2000W_AE,              _TEXT     },
                                 {&textControlVersion,        _TEXT     },
                                 {&textChecking,              _TEXT     },
                                 {&endlistPO,                 ENDLIST}  };
