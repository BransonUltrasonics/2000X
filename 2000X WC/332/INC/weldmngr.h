/* $Header:   K:/APPS/PVCS Pro/332new/INC/WELDMNGR.H_V   2.5   Aug 01 2000 13:52:24   lmarkure  $ */
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

   Filename:      weldmngr.h


 -------------------------------- REVISIONS ------------------------------------

 Rev # Date     Author Description
 ===== ======== ====== ======================================================
 2.3   07/29/98  BJB   Added prototypes for UpdateRPreset(),
                        FormatRunScreenTopLine().
 2.4   07-29-98  BEK   Added prototypes for ClearWeldingResultsAlarms and
                       ClearFinalResultsAlarms
 2.5   08-01-00  LAM   changed FormatRunScreenTopLine prototype


--------------------------------------------------------------------------------
*/

#ifndef WELD_MNGR_H
#define WELD_MNGR_H
/******************************************/
/* This cute little trick is too cute!    */
/******************************************/

#include "portable.h"
#include "preset.h"
//#include "weld_obj.h"


void WeldManager(void);
void UpdateRPreset(void);
void FormatRunScreenTopLine(void);
void ClearWeldingResultsAlarms(void);
void ClearFinalResultsAlarms(void);


/* The following defines are Events for the Weld Manager */

#define EV_NEW_STATE  0x00000002  /* A new weld state has been started     */
#define EV_TEST       0x00000004  /* Test the ultrasonic power supply      */
#define EV_CALIBRATE  0x00000008  /* Calibrate sequence request            */
#define EV_NEW_PACKET 0x00000010  /* Another block of 1 ms data is ready   */


#define EV_WELD (EV_NEW_STATE | EV_TEST | EV_CALIBRATE | EV_NEW_PACKET)



/*--------------------------- PRIVATE GLOBAL DATA --------------------------*/
/*                       (Scope-all weld related files)                     */

/*-----  Distance and Velocity  -----*/

/*-----  The local copy of the current preset  -----*/



#endif
