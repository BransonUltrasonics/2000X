/* $Header:   D:/SWLab/VMdb/2000Series/App/qvgacalib.c_v   1.6.1.2   09 Sep 2008 20:40:02   nhahmed  $ *//****************************************************************************/ 
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

   Module name: Actuator/Sensor Calibration.

   Filename: QVGACalib.c

   This file will deal with the Calibration functions. 

                                   
 --------------------------------- REVISIONS --------------------------------

 Revision#   Date     Author   Description
 =========   ======== =======  =============================================
   1.0       07/18/03 JOY      Initial Version
   1.1       07/25/03 JOY      Added data structures for calibration.
   1.2       10/23/03 JOY      TheMainMenu replaced by QVGATheMainMenu.
   1.3       12-09-03 BEKymer  Add argument members to SUBMENU structures
   1.4       07-25-05 Bwadia   Added VGA menu for calibration screen    
   1.5       02-07-06 Bwadia   Added CheckforCalib() function when Actuator calibration
                               or full calibration done. Modified for improving speed
                               relating to tracker issue 4066 
   1.6       22-12-06 NHAhmed  Added Pop up before Sensor Cal Screen.
   1.6.1     04-14-08 NHAhmed  Replicated some functions as no-argument type.
   1.6.2     09-02-08 NHAhmed  CleanUp for multi-language support.
   1.6.3     09-09-08 NHAhmed  CleanUp for multi-language support.
  
*/

/*--------------------------- INCLUDE FILES --------------------------------*/

#include "menu.h"
#include "qvgamenu.h"
#include "sc.h"
#include "snsrcalb.h"
#include "digout.h"
#include "param.h"
#include "command.h"
/*----------------------------- LOCAL_DEFINES ------------------------------*/

/*---------------------------------- GLOBAL DATA ---------------------------*/
/*                          (scope is global to ALL files)                  */

BOOLEAN QVGACalAllowed = FALSE;
MENUEND endlistCalib = { TRUE };
                                      
/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/
void QVGACloseCalibration(UINT32);

/*------------------------EXTERNAL FUNCTION PROTOTYPES --------------------*/

void CheckforCalib(void);
/*---------------------------- EXTERNAL DATA -------------------------------*/

extern QVGA_MENU_INFO MenuLevelInfo[];
extern REDRAW_SEG  RedrawSeg;               // Indicate which part of Screen has to be- 
                                            // Refreshed.
extern BOOLEAN PlsWaitTimerFlag;
extern BOOLEAN QVGASnsrCalibAllowed;
extern UINT16  CalibrationPassed;
extern UINT32 NackError, ErrorResponseMinLimit, ErrorResponseMaxLimit;


/*-------------------------------- CODE ------------------------------------*/

void VGARequestActCal(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the menu when the selection is made. Need to*/
/* make sure not ready for calibration                                      */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{
   QVGACalAllowed = FALSE;
   if(CalibrationAllowed() == TRUE)
   {
      ClearReady();        /* Remove Welder Ready signal*/
      QVGACalAllowed = TRUE;
	  CheckforCalib();
   }   
   CalibrationPassed = CAL_NOT_ALLOWED;
   if(QVGACalAllowed == FALSE)
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
}

void VGACloseCalibration(void)
/*************************************************************************/
/*Description:                                                           */
/* clean up the Calibration Procedure & start the state machines.        */
/*                                                                       */
/*************************************************************************/
{
   PlsWaitTimerFlag = FALSE;
   /*Here Calibration is Closed Move to Main Menu*/
   SCFinalCleanup();
}


BOOLEAN IsCalibGoingOn(void)
/*****************************************************************************/
/*Description:                                                               */
/* Returns TRUE if either QVGA Act. or Sensor Calibration is going on        */
/*****************************************************************************/
{
   BOOLEAN CalbFlag = FALSE;
   if(QVGACalAllowed || QVGASnsrCalibAllowed) CalbFlag = TRUE;
      
   return(CalbFlag);
}
