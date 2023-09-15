/* $Header:   D:/SWLab/VMdb/2000Series/INC/MENU2.H_V   2.11   04 Sep 2008 20:17:34   ygupta  $ */
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

   Filename: menu2.h

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #     Date            Author     Description
   ==========     ========        ======     ===========
      0                                      Initial Version
      2.60        07/28/97        PJ         Added SetSetupFlag and
                                             ClearSetupFlag prototypes
      2.61        08/15/00        SCM        Added function prototypes.
      2.71        01-08-01        BEKymer    Added argument to SetSetupFlag prototype
      2.7.1.0     09-24-01        BEKymer    Added function prototypes
      2.72        10-11-01        LAM        merged 8.Specials with preset 
      2.10        12-08-03        BEKymer    Above (2.72) changes put back and 
                                              called 2.10.  ABove change was
                                              really 2.9.
	  2.11        09-04-08		  ygupta     Cleanup for Multilanguage project.
                                              
*/

/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

void SetSetupFlag(UINT32);
void ClearSetupFlag(void);
void SelectAmpTriggerTime(void);
void SelectAmpTriggerEnergy(void);
void SelectAmpTriggerPower(void);
void SelectAmpTriggerDist(void);
void SelectAmpTriggerForce(void);
void SelectAmpTriggerExt(void);
void SelectForceTriggerTime(void);
void SelectForceTriggerEnergy(void);
void SelectForceTriggerPower(void);
void SelectForceTriggerDist(void);
void SelectForceTriggerAmp(void);
void SelectForceTriggerExt(void);
void UpdateWS_Config(void);
void GetWeldFRateIndex(void);
void GetStepFRateIndex(void);
void GetHoldFRateIndex(void);


