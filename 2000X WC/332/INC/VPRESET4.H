/* $Header:   L:/pvcs/1000/psos332/archives/app/vpreset4.h_v   1.1   17 Aug 1998 15:09:20   BKYMER  $ */
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

/*   Module name: VPRESET_MODEL4                                            */

/*   Filename:    vpreset4.h                                                */

/*------------------------------- REVISIONS --------------------------------*/
/*                                                                          */
/*  Revision#  Date      Author       Description                           */
/*  =========  ========  ===========  ===========                           */
/*     1.00    07/09/97  BEKymer      New module, add function prototype    */
/*     1.1     08-13-98  BEKymer      Add prototypes for CheckForValidDist..*/
/*                                    and CheckForValidForces               */
/*                                                                          */
/*                                                                          */
/*                                                                          */


/*------------------------------ DESCRIPTION -------------------------------*/



/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"            /* fundamental data object types       */


UINT32 VerifyPresetModel4(void);
BOOLEAN CheckForValidDistances(SINT32 MaxStroke);
BOOLEAN CheckForValidForces(UINT32 MaximumForce);



