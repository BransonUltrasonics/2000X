/* $Header:   K:/APPS/PVCS Pro/332new/App/MENUCAAL.C_V   1.2   May 26 2000 15:25:32   shishir  $ */

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

/*   Module name:     CALIBRATE_ALARMS_TEXT                                 */
/*                                                                          */
/*   Filename:        menucaal.c                                            */
/*                                                                          */
/*   Function name:                                                         */
/*                                                                          */

/*------------------------------- REVISIONS --------------------------------*/

/*   Revision #   Date       Author      Description                        */
/*   ==========   ========   ======      ===========                        */
/*      1.0       07-11-97   BEKymer     Initial Version                    */
/*      1.1       05-26-00   SCM      Checked in for testing by Laura, John.*/
/*                                                                          */
/*                                                                          */
/*                                                                          */


/*------------------------------ DESCRIPTION -------------------------------*/


/* This file deals with the calibration Alarms and their submenus           */



/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"
#include "menu.h"
#include "weld_obj.h"
#include "genalarm.h"


/*----------------------------- EXTERNAL DATA ------------------------------*/

extern WELD_DATA WeldData;


extern const STR *const StrCA_1[];    /* Recalibrate Actuator  */




/*-------------------------- LOCAL TYPE VARIABLES --------------------------*/



/*-------------------------------- CODE ------------------------------------*/

