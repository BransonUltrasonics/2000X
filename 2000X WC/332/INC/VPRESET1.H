/* $Header:   K:/APPS/PVCS Pro/332new/INC/VPRESET1.H_V   1.4   Sep 18 2000 10:04:48   bkymer  $ */
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

/*   Module name: VPRESET_MODEL1                                            */

/*   Filename:    vpreset1.h                                                */

/*------------------------------- REVISIONS --------------------------------*/
/*                                                                          */
/*  Revision#  Date      Author       Description                           */
/*  =========  ========  ===========  ===========                           */
/*     1.00    07/09/97  BEKymer      New module, add function prototype    */
/*     1.3     04-06-98  BEKymer      Add prototype for CheckForStepping()  */
/*     1.4     09-15-00  BEKymer      Change return value in CheckForStepp..*/
/*                                                                          */
/*                                                                          */
/*                                                                          */


/*------------------------------ DESCRIPTION -------------------------------*/



/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"            /* fundamental data object types       */


UINT32 VerifyPreset(void);
UINT32 VerifyPresetModel1(void);
UINT16 CheckForDistanceParameters(void);
void   SendSetupData(void);
UINT32 CheckForStepping(void);

