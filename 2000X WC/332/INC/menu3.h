/* $Header:   K:/APPS/PVCS Pro/332new/INC/MENU3.H_V   1.15   Sep 16 2003 09:36:56   BKymer  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*   Copyright (c) Branson Ultrasonics Corporation, 1995,97                 */
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

   Filename: menu3.h

   Function name:           


 --------------------------------- REVISIONS --------------------------------

   Revision #     Date            Author     Description
   ==========     ========        ======     ===========
      0                                      Initial Version
      1.0         01/28/97        LAM        chged getpresetnames prototype
      1.1         02/04/97        Philj      added IsPresetEnabled prototype
      1.2         02/14/97        Philj      added missing prototypes.
      2.1.7       07/07/97        LAM        chged getpresetname prototype
      2.1.8       07/15/97        PaulG      Added  function prototype ClearHistoryInBbram().
      1.9         04-14-00        SCM        Added function prototypes for presets 11 through
                                             16 for ActivatePreset,ClearPreset and RecallPreset 
      2.0         07-28-00        SCM        Added function prototypes PresetClear() and CheckForDups(). 
      1.11        08-08-00        SCM        Added temporary structure for DUPS parameters
      1.12        09-08-00        LAM        removed unused temporary structure for DUPS parameters
      1.13        01-08-01        BEKymer    Removed prototypes for all the recall, clear and
                                             save individual preset functions.
                                             Removed prototypes for GetParameter & TestParameter
      1.12.1.0    04-19-01        LAM        added function prototype for ext presets
      1.14        10-11-01        LAM        merged 8.Specials and preset cleanup
      1.15        08-05-03        BEKymer    Merged 1.14 and 1.12.1.0 to creat 1.15 for 9.00A build
                                              

*/
 
/* ----------------------------- FUNCTION PROTOTYPES ------------------------- */

UINT8  ValidPresetCharacter(SINT8 Character);
void   GetPresetNames(void);
void   ActivatePreset(UINT32);
void   DisplayActivePreset(void);
void   AppendPresetNumber(void);
SINT32 GetParameter(UINT16 WeldModeType);
UINT8  TestParameter(UINT16 WeldType, SINT32 ParamVal);
void   SaveSameNamePreset(void);
void   AutoNamePreset(void);
UINT8  IsPresetEnabled(UINT8 PresetNumber);
void   SaveAutoNamedPreset(UINT32);
void   AssignNameFunction(void);
void   ClearPresets(UINT32);
void   RecallPreset(UINT32);

BOOLEAN RecallExtPreset(UINT16 PresetCode);
void   SetConfirmOK(UINT32);
void   SetConfirmCancel(UINT32);
void   ClearHistoryInBbram(void);
void   PresetClear(UINT16 presetNumber);
UINT16 CheckForDups(void);
