/* $Header:   D:/SWLab/VMdb/2000Series/INC/MENU7.H_V   1.12   Oct 24 2005 14:48:16   bwadia  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1997                 */
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

   Filename: menu7.h


 --------------------------------- REVISIONS --------------------------------

 Rev # Date     Author Description
 ===== ======== ====== ===========
 1.3   06/25/98  BJB   Added prototype for InitCopyFeatures().
                       Added file header with revision history.
 1.4   06/25/98  BJB   Added prototype for HandleFeaturesAlarm().
 1.5   06/26/98  BJB   Removed prototype for HandleFeatuersAlarm().
 1.6   10-25-99  JZ    Removed GetDateAndTime()
 1.7   04-20-00  SCM   This revision not tested or compiled.
 1.8   06-14-00  SCM   Added the function prototype for UpdateLanguage().
 1.9   06-02-04  VSharma  Added the function prototype for DealWithExtPresetChange().
 1.10  07-29-04  JOY   Dummy Checkout.
 1.11  10-04-04  BEkymer  Add prototype for UpdateAllUserOutputs
 1.12  10-24-05  Bwadia   Removed GetPSWatts() and PutPSWatts() prototype
 
*/

/*
 --------------------------- FUNCTION PROTOTYPES -----------------------------
*/

void UpdateAllUserOutputs(void);
void UpdatePresetDateandTime(void);
void SetCurrentUser(void);
void SetAmpControl(void);
void SetFreqControl(void);
void InitCopyFeaturesSetting(void);
void GetPSFreq(void);
void PutPSFreq(void);
void UpdateLanguage(void);
void DealWithExtPresetChange(void);
