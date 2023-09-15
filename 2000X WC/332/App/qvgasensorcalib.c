/* $Header:   D:/SWLab/VMdb/2000Series/App/qvgasensorcalib.c_v   1.11   09 Sep 2008 20:40:04   nhahmed  $ */
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

   Module name: Sensor Calibration.

   Filename: qvgasensorcalib.c



                                   
 --------------------------------- REVISIONS --------------------------------

 Revision#   Date     Author   Description
 =========   ======== =======  =============================================
   1.0       07/18/03 JOY      Initial Version
   1.1       07/25/03 JOY      Added data structures for sensor calibration.
   1.2       10/23/03 JOY      TheMainMenu is replaced by QVGATheMainMenu.
   1.3       12-09-03 BEKymer  Add argument members to SUBMENU structures
   1.4       05-04-04 VSharma  Modified DrawCalResetConfirmScrn().
   1.5       07-25-05 Bwadia   VGA reset sensor support added 
   1.6       02-07-06 Bwadia   VGAPOINTER menu item added when entry to calibration screen
                               Done for exiting out of alarm screen 
   1.7       12-22-06 NHAhmed  Added Pop up before Sensor Cal Screen.
   1.8       10-22-07 NHAhmed  Changes done for LangTest phase 0
   1.9       04-14-08 NHAhmed  Replicated a function as no-argument type.
   1.10      09-02-08 NHAhmed  CleanUp for multi-language support.
   1.11      09-08-08 NHAhmed  CleanUp for multi-language support.

*/

/*--------------------------- INCLUDE FILES --------------------------------*/

#include "menu.h"
#include "qvgamenu.h"
#include "sc.h"
#include "snsrcalb.h"
#include "digout.h"
#include "DrawScrn.h"
#include "param.h"
#include "command.h"
/*----------------------------- LOCAL_DEFINES ------------------------------*/

/*---------------------------------- GLOBAL DATA ---------------------------*/
/*                          (scope is global to ALL files)                  */

MENUEND endlistsnsrCalib = { TRUE };
BOOLEAN QVGASnsrCalibAllowed = FALSE;
                                      
/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/
                                      
    
/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/


/*------------------------EXTERNAL FUNCTION PROTOTYPES --------------------*/

void CheckforCalib (void);

/*---------------------------- EXTERNAL DATA -------------------------------*/

extern UINT16 CalibrationPassed;
extern QVGA_MENU_INFO MenuLevelInfo[];
extern CONFIRM_SCREEN_TYPE ConfirmType;
extern REDRAW_SEG  RedrawSeg;            // Indicate which part of Screen has to be- 
                                         // Refreshed.
extern UINT32 NackError, ErrorResponseMinLimit, ErrorResponseMaxLimit;

/****************************************************************************/
/*-------------------------------- CODE ------------------------------------*/
/****************************************************************************/

void VGARequestSensorCal(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called from the menu when the Cal Sensor selection is   */
/* made                                                                     */
/*                                                                          */
/* Output: CalibrationPassed                                                */
/*                                                                          */
/****************************************************************************/ 
{
   QVGASnsrCalibAllowed = FALSE;
   if(CalibrationAllowed() == TRUE)
   {
      QVGASnsrCalibAllowed = TRUE;
      CalibrationInit();   /* Initialize State Sequence for Calibration */
      ClearReady();        /* Remove Welder Ready signal to prevent a cycle*/      
	  CheckforCalib();
   }
   else  
      CalibrationPassed = CAL_NOT_ALLOWED;
   if(QVGASnsrCalibAllowed == FALSE)
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
}


