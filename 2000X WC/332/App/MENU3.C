/* $Header:   D:/databases/VMdb/2000Series/App/MENU3.C_V   1.126.1.8   Jan 03 2018 09:57:30   RCHAPA  $ */
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

   Filename: menu3.c

   Function name:                  

 --------------------------------- REVISIONS --------------------------------

   Revision #  Date      Author   Description
   ==========  ========  =======  ===========
   0                              Initial Version
   1.00        05/11/96  PJ       Modified for PSOS version
   1.10        08/14/96  PJ       Modified per Spec Rev 1.D
   1.20        08/22/96  PJ       Modification made to Blank display
                                  when scrooling back thru display.
   1.30        09/12/96  PJ       Removed extern SINT8 RunBuffer1
   1.40        09/13/96  PJ       Corrected bug when Save/Recall
                                  Presets was not on line 4.
   1.50        09/20/96  PJ       Warning given if Use Same Name is
                                  overwriting a preset.
   1.60        10/02/96  LAM      deleted writing preset 0
   1.70        10/04/96  PJ       Removed the sending of 4 fake keys
                                  on a Preset Recall.
   1.80        10/09/96  PhilJ    Changed Menus to type const. 
   1.90        10/24/96  PhilJ    Deleted unnecessary code. 
   2.00        10/25/96  LAM      added extern to MENUS                                       
   2.10        11/27/96  PhilJ    * will be displayed if prset is
                                  edited from the Run screen . 
   2.20        12/13/96  PhilJ    Update CycleCount on a Preset recall.
   2.30        12/16/96  PhilJ    Write Preset0 to Battery Backup
                                  in SaveAutoNamedPreset.
   2.30        12/16/96  PhilJ    Write Preset0 to Battery Backup
   2.40        12/23/96  PhilJ    In ClearPreset, if preset is active
                                  CurrentPreset is also cleared.
   2.50        12/31/96  PhilJ    Added function ValidPresetCharacter.
   2.60        12/31/96  PhilJ    Corrected bug when clearing Presets.
   2.70        01/07/97  PhilJ    Corrected bug in Recall Presets.
   2.80        01/15/97  PhilJ    Corrected bugs when Saving Presets.
   2.90        01/22/97  PhilJ    Modified SameNamePreset to test if
                                  preset was AutoNamed.
   3.00        01/23/97  PhilJ    ReadOnlyFlag set to prevent
                                  Running Preset update.
   4.00        01-29-97  LAM      chged getpresetnames
   4.01        01-30-97  LAM      moved update mode,ampcontrol to weldmngr
   4.02        02-03-97  PhilJ    Correct bugs in Preset DCS issues
   4.03        02-04-97  PhilJ    Corrected SavePreset DCS issues.
   4.04        02-12-97  PhilJ    Correct switch argument in
                                  DisplayActivePreset.
   4.05        02-14-97  PhilJ    Modified SameNamePreset.
   4.06        02-28-97  PhilJ    Deleted SameNamePreset from menu.
   4.07        03-18-97  PhilJ    Save Preset0 to Battram after
                                  naming Preset.
   4.08        03-18-97  PhilJ    Added PresetUpdateComplete check
                                  to RecallPresets.
   4.09        04/24/97  PhilJ    Corrected bug Saving Preset cycle
                                  count.
   4.10        06/16/97  PhilJ    Changed UpdateCurrentSetup to
                                  UpdateCurrentPreset.
   5.1.32      07/03/97  LAM      rewrote getpresetnames
   5.1.33      07/11/97  PhilJ    Corrected menu MODEL numbers
   6.1.36      07/23/97  JBerman  Changed all strcat with strncat
                                  Added also Str17Spc
   6.1.37      07/24/97  PhilJ    Updated menu MODEL nums per SRS
   7.1.38      08/08/97  LAM      Added string  StrM3_9a
   7.1.39      08/26/97  PaulG    Added ClearHistoryInBbram().
   7.1.40      08/28/97  LAM      fixed saving preset 2 & 3    
   7.1.41      09.11.97  JBerman  Added default into switch statements
   1.42        09.24.97  BJB      Changed LEVEL_ea to LEVEL_e in
                                  Recall3, bug fix
   1.43        10.02.97  LAM      chged to sendfakerunkey when recalling preset
   1.44        10.07.97  LAM      added namelen define
   1.45        10-16-97  BJB      Deleted flag AssignNameComplete
                                  Copies blank line to PresetName in
                                   DisplayActivePreset() if ActivePreset is
                                   not 1..10
                                  Formats last line of name entry key via
                                   explicit call before AssignNameMenu called,
                                   doesn't do this using function in menu item
                                  Fixed invalid Select2Key send before display
                                   of AssignNameMenu
                                  Checks AlphaEntryDone instead of
                                   AssignNameComplete to see if name entered.
                                   Lets ALPHA entry code in SELCTKEY.C
                                   initialize this variable.
                                  Does not allow null preset names.
                                  Added new elements to items AssignName1..3
   1.46        11-4-97   BJB      Doesn't send fake "NOKEY" before displaying
                                   menus.
   1.47        11-08-97  BJB      Uses StrAlpha1[], StrAlpha2[] instead of
                                   StrM3_5[], StrM3_6[].
   1.48        11-18-97  LAM      chged welddata to finalresults     
   1.49        12-10-97  PaulG    Reset TotalPts when recall is done
   1.50        01-21-98  BJB      At end of GetPresetNames(), copies
                                   from battery RAM directly to
                                   CurrentPreset.
                                  Changed preset name length to 10.
   1.51        02-09-98  PaulG    Reset WeldDataOffset when a cold start is initiated.
   1.52        03-24-98  PaulG    Removed TotalPts don't need to reset at when History is cleared.
   1.53        03-28-98  LAM      need to clear data groups when clearing bbram history.
   1.54        03-28-98  BEKymer  In ClearHistoryInBbram() set 
                                  PrinterTotalCount to 0.
   1.55        04-03-98  PaulG    In ClearHistoryInBbram() call ClearDataStorage().
   1.56        04-28-98  BJB      Replaced AssignNameMenu[] with AssignNameItem, uses
                                   AlphaEntry() function to enter name.
   1.57        06-19-98  BJB      Updates terminal display when preset recalled.
   1.58        06-19-98  BJB      Added #include "terminal.h" missing from last version.
   1.59        06-24-98  BJB      Changed NORMAL to BASIC.
   1.60        06-26-98  BJB      Modified preset recall to prevent recall during cycle.
                                  Consolidated duplicate code in RecallPreset().
   1.61        06-29-98  PaulG    Added Function LastDatePresetWasSaved() to capture date.
   1.62        07.15.98  JBerman  DCS 2789, expanded  presets 6 to 10:
                                  Recall, Save, Clear from level 3.
   1.63        07-16-98  BEKymer  Added argument to all calls to
                                  ReadPreset to indicate if alarm
                                  W8 should be suppressed (TRUE)
                                  or not (FALSE)
   1.64        07-30-98  BJB      Doesn't read preset at end of GetPresetNames().
   1.65        07-31-98  BJB      Includes kpresmsg.h, getmsg.h
   1.66        08-18-98  PaulG    Remove assignment to FinalResults.CycleCount.
   1.67        09-17-98  BEKymer  Fix auto name of PP mode preset
   1.68        10-13-98  PaulG    Added a check for the status of the printer buffer
                                  in the function RecallPreset().
   1.69        10-28-98  LAM      fixed ccrider error
   1.70        10-30-98  BJB      Preset names can include metric units
   1.71        12-16-99  LAM      removed unused error handling code
   1.71.6.1    02-07-00  JZ       removed DVS, added Mask1, Cond1, Mask2, Cond2
   1.71.6.2    02-23-00  OFI      removed 'User experience level' from menu strucutures and fixed
                                  BASIC to PALMBUTTONS because this place used different enum.
   1.72        04-05-00  JZ       merged Lang to trunk
   1.73        04-14-00  SCM      Added preset structures 11 through 16
   1.74        04-18-00  SCM      Fixed definition errors in presets 11-16.
   1.75        04-19-00  SCM      converted tabs to spaces.
   1.76        05-26-00  SCM      Checked in for testing by Laura, John.
   1.77        06-02-00  SCM      Removed tabs, fixed minor problems.
   1.78        06-05-00  LAM      set functions for presets 11-16 to preset10 
                                  functions for first release. There is only one
                                  preset name for all foreign languages.
   1.79        06-14-00  SCM      Removed the VerifyPresetMenu since it is
                                  now part of Version-9 Update.
   1.80        06-16-00  LAM      do not allow lower case letters from the terminal   
   1.81        06-28-00  BEKymer  Changed all MODEL to LEVEL
   1.82        07-14-00  BEKymer  Save, Recall and Clear preset 13-16 Contol_d only
   1.83        07-28-00  SCM      Added the functions CheckForDups() and PresetClear().
   1.84        08-08-00  SCM      Added temporary DUPS structure and functionality for 
                                  Save/recall presets.
   1.85        08-11-00  SCM      Modified functions RecallPreset(),PresetClear(),SaveAutoNamedPreset()
                                  and AssignNameFunction().
   1.86        08-12-00  SCM      Minor bug fixes.
   1.85.1      08/16/00  RBH      Corrections to Save/Recall presets and Parameter
                                  Sets.  Backedup a version and started over.
   1.85.1.1    08/18/00  AT       ClearPresetN() doesn't allow to clear current preset (#3399)
   1.85.1.2    08/28/00  AT       ClearPreset() sets ActivePreset to 0 if clearing current preset (#3519)
   1.85.1.3    08-31-00  BEKymer  Fix # 3525 - Preset cleared even if cancel selected
   1.88        08-31-00  LAM      moved branch to trunk, did not merge it
   1.89        09-06-00  LAM      set PresetNeedsToBeUpdated=TRUE after saving a preset inorder
                                  to update the runningpreset.id( # 3537)
   1.90        09-06-00  LAM      do not allow saving of presets while welding and there is a DUPS
   1.91        09-08-00  LAM      removed unused temporary structure for DUPS parameters
   1.92        09-14-00  BEKymer  In RecallPreset restart the state machine even if an
                                   Invalid Preset alarm occurs (errorcode 9)
   1.93        09-22-00  BEKymer  In AssignNameItem structure use StrM3_0F
                                   instead of StrM3_0B  Issue #3589
   1.94        09-27-00  BEKymer  In AssignNameFunction() and SaveAutoNamePreset()
                                   clear the display after the popup warning about
                                   no DUPS (issue # 3599)
   1.95        10-04-00  AT       Changed DUPS_DownloadCurrPS to DUPS_QueuedDownloadPS
   1.96        10-06-00  BEKymer  In SaveAutoNamedPreset and AssignNameFunction reset
                                   state machine and call ClearAbort() (to clear
                                   ReadyAlreadySet flag ) before restarting
   1.97        10-09-00  AT       Line 2307 - use Queued download/upload to recall presets
   1.98        10-18-00  BEKymer  Added 2nd arg to SaveCompressedPreset call
                                   Fix for issue # 3387
   1.99        01-11-01  BEKymer  Added argument to TEXT and SUBMENU structure calls
                                   Completely cleaned up handling of saving, recalling,
                                   clearing of presets. Combined menu structures for
                                   displaying names of presets.
   1.98.1.0    04-24-01  LAM      Converted PresetEnableFlags to UINT16
                                  added function for recalling ext presets,
                                  modified getpresetnames to set PresetEnableFlags False
                                  when not allowed at a given control level.
   1.98.1.1    04-25-01  LAM      fixed not being able to print graphs with External Presets
   1.98.1.2    04-30-01  LAM      fixed graph data during handheld and beeping when Externally
                                  selecting Presets
   1.98.1.3    07-02-01  LAM      fixed saving the current preset when externally recalling
                                  presets.                                       
   1.98.1.4    08-16-01  BEKymer  Change from LINESIZE to MESSAGESIZE for preset name arrays
                                   This fixes a bug that didn't show up until the new compiler
                                   was used.
   1.100       10-09-01  LAM      merged preset cleanup with 8.specials                                    
   1.101       08-01-03  BEKymer  Merge 1.100 with 1.98.1.5 to create 1.101 for V9.00A build
                                  -Save ActivePreset in BBR as soon as its changed when external 
                                    presets are called.                                          
   1.102       08-05-03  BEKymer  Rename Numout to Numout1 because its arguments are slightly
                                   different than the version in util. This version is used mostly
                                   for the creating preset names within menu3.
   1.103       12-03-03  BEKymer  Merge 1.102 & 1.98.1.7 to create 1.103 for
                                   build Ver9.00b
   1.104       12-09-03  BEKymer  Add QVGASaveAutoNamedPreset & QVGASaveManuelNamedPreset
                                   function prototypes missed during merge.
                                  Add arguments for SUBMENU structure function calls
   1.105       02-02-04  VSharma  Recall DUPS Preset in case of RecallExtPreset() and Save three
                                  DUPS parameters in battram while saving the preset 
                                  using SaveDUPSParameters().
   1.106       02-13-04  VSharma  Changed function header of RecallExtPreset().
   1.107       02-20-04  VSharma  Added RecallAndVerifyPreset() and PresetVerifyManually().
                                  Added SUBMENU 'QVGASameNameAsOld' & 'QVGASameNameAsNew' in
                                  QVGANameMenu.
   1.108       03-03-04  VSharma  Clear alarms before verification in 'RecallAndVerifyPreset()'.
   1.110       04-06-04  VSharma  Added TOTAL_PRESETS, WAIT_2SEC & WAIT_4SEC.
                                  Modified RecallExtPreset().
   1.111       05-13-04  VSharma  Added Check for not to recall preset if PresetCode is greater 
                                  than MAX_PRESET in RecallExtPreset().
   1.112       05-17-04  VSharma  Removed extern of unused strings.
                                  Modified SaveAutoNamedPreset() & AssignNameFunction() function. 
   1.113       05-18-04  VSharma  Modified RecallExtPreset().
   1.114       06-04-04  VSharma  Removed ClearHistoryInBbram() from RecallPreset(),RecallExtPreset() &
                                  RecallAndVerifyPreset().
   1.115       08-03-04  JOY      The flag 'IsRecalledPreset' made FALSE in SaveAutoNamedPreset().
   1.116       08-04-04  JOY      No change.
   1.117       08-19-04  JOY      Corrected AppendPresetNumber() function.
   1.118       08-27-04  JOY      Removed jumping in to the Run screen while external preset recall.
   1.119       09-14-04  JOY      Set flag 'ResetRecall_UpdateFlag' in RecallPreset().
   1.120       07-25-05  Bwadia   Asian Language support for preset strings. 
                                  SaveAutoNamedPreset modified to account for Asian Languages.
   1.121       10-28-05  Bwadia   VFD sequencing menu and functions added                                                                             
   1.122       02-22-06  Bwadia   RefreshDUPSParam() modified for memory reset flag
                                  Modified ofr tracker issue 4077                                            
   1.123       03-27-07  BEkymer  Don't save old preset when recalling a new one.
                                  The weld count will now be updated during
                                  OP_FINAL_WELD_DATA.
   1.124       04-16-07  NHAhmed  Added LimitChanged to RecallAndVerifyPreset() and RecallExtPreset().
   1.125       04-18-07  NHAhmed  Password protection of Preset Sequencing.
   1.126       04-24-07  NHAhmed  Removed DisplayStateMessage() from RecallExtPreset().
   1.126.1.0   10-22-07  NHAhmed  Changes done for LangTest phase 0
   1.126.1.1   01-14-07  NHAhmed  Updated AutoNamePreset() for Multi Language.
   1.126.1.2   09-02-08  NHAhmed  CleanUp for multi-language support.    
   1.126.1.3   09-04-08  YGupta   CleanUp for LangTest Project.
   1.127.1.3   09-04-08  ygupta     Removed include statemsg.h
   1.128.1.3   09-09-08  NHAhmed   CleanUp for LangTest Project.
   1.126.1.8   1/3/2018	 RChapa	  Removed DUPSWaitFlag and DUPSMsTmr used for DUPS parameters Update (DEF01409 - Ramp time issue)		
								 				
------------------------------- DESCRIPTION ---------------------------------
*/

         /* This file will deal with presets, both loading and saving. */

/* --------------------------- INCLUDE FILES --------------------------------  */

#include <prepc.h>
#include "portable.h"
#include "menu.h"
#include "graphs.h"
#include "preset.h"
#include "keypad.h"
#include "beep.h"
#include "selctkey.h"
#include "weld_obj.h"
#include "ck_qsend.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "fmtstrs.h"
#include "display.h"
#include "battram.h"
#include "util.h"
#include "menu3.h"
#include "statedrv.h"
#include "dups_api.h"
#include "alarms.h"
#include "ready.h"
#include "weldmngr.h"
#include "digout.h"
#include "dups.h"
#include "alsetup.h"
#include "weld_msg.h"

/* ----------------------------- EXTERNAL DATA ------------------------------ */


extern BOOLEAN IsGraphDrawing;
extern BOOLEAN UpdateFlag; 
extern UINT16 AlarmCounter;
extern UINT8 AlarmDetectedFlag;
extern BOOLEAN QVGAHwAvail;
extern UINT32 QvgaQid;   // Queue ID for QVGA queue.
extern UINT32 SysmQueueId;
extern UINT16 TotalAlarmCount;
extern UINT16  PresetNeedsToBeUpdated;
extern UINT8  RunScreenFlag;
extern SINT16 MenuCounter;
extern UINT16 AdjustWeldSetupMenuFlag;

extern UINT8 UpdateRunningPreset;
extern UINT8 ExitMenuCounter;
extern void LastDatePresetWasSaved(void);
extern SETUPS_Ver800 CurrentPreset;
extern CONFIGSETUP CurrentSetup;
extern WELD_DATA FinalResults;
extern UINT32 SysmQueueId;                             
extern UINT16 WeldDataOffset;
extern UINT16   PrinterTotalCount;
extern UINT8  LimitChanged;

extern enum WELDSTATES WeldState;
extern BOOLEAN IsThereDataPrinting;
extern PRESET_COMPRESSED* PresetAddress[];

void SaveDUPSParameters(UINT16 ActivePreset);
void RefreshDUPSParam (PRESET_COMPRESSED* CompPreset);
void UpdateDUPSRAMParamSet(void);
void PresetVerifyManually (UINT32 PresetNum);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);
void GetSequenceName(UINT32 dummy);
void RearrangeSeqList(UINT16 PresetNos);

/* ------------------------------- LOCAL DEFINES ------------------------------- */

#define NAMELEN (PRESETLEN - 1)      
#define MAX_LEVEL_t    1      
#define MAX_LEVEL_e    5      
#define MAX_LEVEL_ea  12      
#define MAX_LEVEL_d   16      
#define MAX_LEVEL_f   16      

#define WAIT_2SEC     2000
#define WAIT_4SEC     4000

void Numout1(UINT32 Value, UINT16 Base, STR LC, UINT8 Width, STR *StrAdr);


/* ---------------------------- LOCAL TYPE DECLARATIONS ------------------------ */

const STR  Digits[] = "0123456789ABCDEF";      /* Used by Numout */

UINT16  OldSameNameAvailable;              /* TRUE: writing to existing preset */
UINT16  NewSameNameAvailable;              /* FALSE: writing to clear preset   */
UINT8 SeqActionType;

/* ----------------------------- GLOBAL DATA --------------------------------- */
/*                      (scope is global to ALL files)                         */




SINT8 AssignNamePresetBuffer[MESSAGESIZE];
WELD_DATA_MSG   WeldHistoryMsg;

UINT16  PresetEnableFlags[TOTAL_PRESETS];    /* TRUE: Preset is valid   FALSE: Preset is not valid */
BOOLEAN IsRecalledPreset = FALSE;
BOOLEAN ResetRecall_UpdateFlag = FALSE;
BOOLEAN ConfirmPresetFlag = FALSE;

/*---------------------------- PRIVATE GLOBAL DATA ----------------------------*/
/*                        (scope is global to THIS file)                       */

static BOOLEAN ValidControlLevel(UINT16 PresetNumber);

UINT32 PresetFunction;
SINT32 InfoMonth, InfoDay, InfoYear;
SINT32 InfoHour, InfoMinute;
SINT32 InfoCount;

STR PresetBufEngName[QVGA_LINESIZE];
STR Preset1EngName[QVGA_LINESIZE];
STR Preset2EngName[QVGA_LINESIZE];
STR Preset3EngName[QVGA_LINESIZE];
STR Preset4EngName[QVGA_LINESIZE];
STR Preset5EngName[QVGA_LINESIZE];
STR Preset6EngName[QVGA_LINESIZE];
STR Preset7EngName[QVGA_LINESIZE];
STR Preset8EngName[QVGA_LINESIZE];
STR Preset9EngName[QVGA_LINESIZE];
STR Preset10EngName[QVGA_LINESIZE];
STR Preset11EngName[QVGA_LINESIZE];
STR Preset12EngName[QVGA_LINESIZE];
STR Preset13EngName[QVGA_LINESIZE];     
STR Preset14EngName[QVGA_LINESIZE];
STR Preset15EngName[QVGA_LINESIZE];
STR Preset16EngName[QVGA_LINESIZE];
STR NewSameName[QVGA_LINESIZE];
STR OldSameName[QVGA_LINESIZE];

STR *PresetBuffer[] =   { PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName,
                          PresetBufEngName };
                           
/** This structure needs to grow when more than 16 presets are used **/

const STR *PresetPtrs[] = {  Preset1EngName,     /* 0 index is not really used */
                             Preset1EngName,
                             Preset2EngName,
                             Preset3EngName,
                             Preset4EngName,
                             Preset5EngName,
                             Preset6EngName,
                             Preset7EngName,
                             Preset8EngName,
                             Preset9EngName,
                             Preset10EngName,
                             Preset11EngName,
                             Preset12EngName,
                             Preset13EngName,
                             Preset14EngName,
                             Preset15EngName,
                             Preset16EngName  };

STR SequenceName1[LINESIZE];
STR SequenceName2[LINESIZE];
STR SequenceName3[LINESIZE];
STR SequenceName4[LINESIZE];
STR SequenceName5[LINESIZE];
STR SequenceName6[LINESIZE];
STR SequenceName7[LINESIZE];
STR SequenceName8[LINESIZE];
STR SequenceName9[LINESIZE];
STR SequenceName10[LINESIZE];
STR SequenceName11[LINESIZE];
STR SequenceName12[LINESIZE];
STR SequenceName13[LINESIZE];
STR SequenceName14[LINESIZE];
STR SequenceName15[LINESIZE];
STR SequenceName16[LINESIZE];
STR SequenceName17[LINESIZE];
STR SequenceName18[LINESIZE];
STR SequenceName19[LINESIZE];
STR SequenceName20[LINESIZE];
STR SequenceName21[LINESIZE];
STR SequenceName22[LINESIZE];
STR SequenceName23[LINESIZE];
STR SequenceName24[LINESIZE];
STR SequenceName25[LINESIZE];
STR SequenceName26[LINESIZE];
STR SequenceName27[LINESIZE];
STR SequenceName28[LINESIZE];
STR SequenceName29[LINESIZE];
STR SequenceName30[LINESIZE];
UINT8 SequencePresetSelected;

const STR *SequencePtrs[] = {  SequenceName1,     /* 0 index is not really used */
                               SequenceName1,
                               SequenceName2,
                               SequenceName3,
                               SequenceName4,
                               SequenceName5,
                               SequenceName6,
                               SequenceName7,
                               SequenceName8,
                               SequenceName9,
                               SequenceName10,
                               SequenceName11,
                               SequenceName12,
                               SequenceName13,
                               SequenceName14,
                               SequenceName15,
                               SequenceName16,
                               SequenceName17,
                               SequenceName18,
                               SequenceName19,
                               SequenceName20,
                               SequenceName21,
                               SequenceName22,
                               SequenceName23,
                               SequenceName24,
                               SequenceName25,
                               SequenceName26,
                               SequenceName27,
                               SequenceName28,
                               SequenceName29,
                               SequenceName30 };



UINT8 ConfirmResponse;
UINT8 ActivePreset;
UINT16 SerialMessageQueue(UINT8 *buf, UINT16 cnt );
/* Minimum Control Level required to recall a preset. */
UINT16 PresetControlLevel[TOTAL_PRESETS] = { LEVEL_t,  /* Minimum Control Level for preset 0 */
                                             LEVEL_t,  /* Minimum Control Level for preset 1 */ 
                                             LEVEL_t,  /* Minimum Control Level for preset 2 */
                                             LEVEL_ea, /* Minimum Control Level for preset 3 */
                                             LEVEL_ea, /* Minimum Control Level for preset 4 */
                                             LEVEL_ea, /* Minimum Control Level for preset 5 */
                                             LEVEL_ea, /* Minimum Control Level for preset 6 */
                                             LEVEL_ea, /* Minimum Control Level for preset 7 */
                                             LEVEL_ea, /* Minimum Control Level for preset 8 */
                                             LEVEL_ea, /* Minimum Control Level for preset 9 */
                                             LEVEL_ea, /* Minimum Control Level for preset 10 */
                                             LEVEL_ea, /* Minimum Control Level for preset 11 */
                                             LEVEL_ea, /* Minimum Control Level for preset 12 */
                                             LEVEL_d,  /* Minimum Control Level for preset 13 */
                                             LEVEL_d,  /* Minimum Control Level for preset 14 */
                                             LEVEL_d,  /* Minimum Control Level for preset 15 */
                                             LEVEL_d  };/* Minimum Control Level for preset 16 */


/* --------------------------------- CODE ---------------------------------- */



UINT8 ValidPresetCharacter(SINT8 Character)
{
   UINT8 ValidChar = FALSE;     /* Assume Invalid Character */

   if(Character >= '0' && Character <= '9')
      ValidChar = TRUE;
   else if(Character >= 'A' && Character <= 'Z')
           ValidChar = TRUE;
   else if(Character >= 'a' && Character <= 'z')
           ValidChar = TRUE;
   else
   {
      switch(Character)
      {
         case 0:
         case '.':
         case '/':
         case '#':
         case ' ':
         case '=':
         case '%':
            ValidChar = TRUE;
            break;
         default:
            break;
      }
   }
   return(ValidChar);
}

static BOOLEAN ValidControlLevel(UINT16 PresetNumber)
/***************************************************************************/
/*                                                                         */
/*  This function determines if a preset number is valid for the Control   */
/*  Level of the system                                                    */
/*                                                                         */
/*  Input: CurrentSetup.ControlLevel - used to determine status of Preset  */
/*         EnableFlags                                                     */
/*                                                                         */
/***************************************************************************/
{
   BOOLEAN ValidNumber = TRUE;     /* Assume Valid Number */

   switch(CurrentSetup.ControlLevel)
   {
      case LEVEL_t:
         if(PresetNumber > MAX_LEVEL_t) 
            ValidNumber = FALSE;
         break;
      case LEVEL_e:
         if(PresetNumber > MAX_LEVEL_e) 
            ValidNumber = FALSE;
         break;
      case LEVEL_ea:
         if(PresetNumber > MAX_LEVEL_ea) 
            ValidNumber = FALSE;
         break;
      case LEVEL_d:
         if(PresetNumber > MAX_LEVEL_d) 
            ValidNumber = FALSE;
         break;
      case LEVEL_f:
         if(PresetNumber > MAX_LEVEL_f) 
            ValidNumber = FALSE;
         break;
      default:
         ValidNumber = FALSE;
         break;
   }
   return(ValidNumber);
}



void Numout1(UINT32 Value, UINT16 Base, STR LC, UINT8 Width, STR *StrAdr)
/*****************************************************************************/
/*   Numout1 converts a number from binary to an ascii string suitable for   */
/*   printing or display.                                                    */
/*      Value:   The number whose ascii representation is desired            */
/*      Base:    What base to display in (2-16)                              */
/*      LC:      Leading character (usually space, zero or NULL)             */
/*      Width:   The number of character positions to convert                */
/*      StrAdr:  Address of the buffer where to put the ascii string         */
/*                                                                           */
/*   If the 'Value' is too large to be represented in 'Width' characters of  */
/*   the chosen 'Base', then only the least significant digits will be put   */
/*   into the string.   A null will be added at the end of the converted     */
/*   string.                                                                 */
/*****************************************************************************/
{
   UINT16   I;

   for (I = 1; I <= Width; I++) {
      StrAdr[Width-I] = Digits[Value % Base];
      Value /= Base;
   }
   StrAdr[Width] = NULL;
   I = 0;
   while ((StrAdr[I] == '0') && (I < (Width-1)) ) { 
      StrAdr[I] = LC;
      I++;
   }
}





void GetPresetNames(void)
/*****************************************************************************/
/*  This function will get te names of all the valid presets and put them    */
/*  into the string array PresetPtrs.  Invalid names will be set to NULL.    */
/*  The preset number will be added to the start of the string by the func-  */
/*  tion Numout1().  This function does not read in each preset so the       */
/*  current preset is not lost.  This function should be called whenever the */
/*  list of names needs to be updated such as saving or clearing a preset.   */
/*****************************************************************************/
{
   UINT16            i,x;
   UINT16            ValidPreset;
   STR               LocalPresetNames[LINESIZE];
   PRESET_COMPRESSED *PresetPtr;

   for (x=1; x<=MAX_PRESETS; x++) {
      PresetPtr = PresetAddress[x];
      if (PresetPtr->PresetID[0] != NULL) 
      {
         ValidPreset = TRUE;                     /* Assume Valid Name */
         for (i = 0; i < NAMELEN && ValidPreset; i++) {
            if (PresetPtr->PresetID[i] != 0) {
               if (!ValidPresetCharacter(PresetPtr->PresetID[i])) {
                  if(!ValidControlLevel(x))
                  { 
                     ValidPreset =  FALSE;
                     PresetPtr->PresetID[0] = NULL; /* Invalid Name, Clear Name */
                  }
               }
            }
            else
               ValidPreset = FALSE; /* Terminate Loop, Preset Valid */
         }                                                                 
      }
      if (PresetPtr->PresetID[0] != NULL)       /* Preset name is okay */
      {
         PresetEnableFlags[x] = TRUE;
         Numout1(x, 10, '0', 2, LocalPresetNames);
         strcat(LocalPresetNames, " ");
         strcat(LocalPresetNames, PresetPtr->PresetID);
      }
      else
      {
         Numout1(x, 10, '0', 2, LocalPresetNames);
         PresetEnableFlags[x] = FALSE;
      }
      LocalPresetNames[NAMELEN+3] = NULL;        /* Make sure string is terminated */
                                                 /* +3 is for number & space       */
      strcpy(PresetPtrs[x], LocalPresetNames);
   }
}



void ActivatePreset(UINT32 PresetNum)
/*****************************************************************************/
/*  This function will set ActivePreset equal to the passed argument.  This  */
/*  global is used for saving a preset.  It will also fill two strings with  */
/*  preset names.  NewSameName will be filled with the name of the preset    */
/*  that was just made active.  OldSameName will be filled with the preset   */
/*  that is current.  Both of these can be displayed when saving presets.    */
/*  Besides auto naming and assigning a name, these two names can be chosen, */
/*  allowing a preset to be saved using an existing name.  If the names are  */
/*  the same only one will be displayed.                                     */
/*****************************************************************************/
{
   ActivePreset = PresetNum;
   if (PresetEnableFlags[PresetNum] == TRUE)
   {
      strcpy(NewSameName, "\"");                        /* Start with a quote                       */
      strcat(NewSameName, &PresetPtrs[ActivePreset][3]);/* Put into SameName in case that is picked */
      strcat(NewSameName, "\"");                        /* End with a quote                         */
      NewSameNameAvailable = TRUE;                      /* Allow name to be displayed               */
   }
   else
   {
      NewSameName[0] = NULL;                            /* Remove all signs of old string           */
      NewSameNameAvailable = FALSE;                     /* Prevent display of name                  */
   }   
   if (CurrentPreset.PresetID[0] != NULL)
   {
      strcpy(OldSameName, "\"");                        /* Start with a quote                       */
      strcat(OldSameName, CurrentPreset.PresetID);      /* Put into SameName in case that is picked */
      strcat(OldSameName, "\"");                        /* End with a quote                         */
      if (strcmp(NewSameName, OldSameName))             /* If both strings are different            */
         OldSameNameAvailable = TRUE;                   /* then we need both                        */
      else
         OldSameNameAvailable = FALSE;                  /* Otherwise eliminate one                  */
   }
   else OldSameNameAvailable = FALSE;                   /* Prevent display of name                  */
}




void AutoNamePreset(void)
{
   UINT16 StringSize, NumSize;
   SINT32 Value;
   SINT8 TempString[PRESETLEN];
   SINT8 *CPtr;
   enum FORMAT format;

   Value = 0;     /* Use this to tell if # needs to be displayed */

   switch (CurrentPreset.WeldMode)
   {
      case TIMEMODE:
         strcpy(CurrentPreset.PresetID, "Tm=");
         format = TIME;
         Value = CurrentPreset.WeldTime;
         break;

      case ENERGYMODE:
         strcpy(CurrentPreset.PresetID, "En=");
         Value = CurrentPreset.WeldEnergy;

         if (Value >= 10000)
            format = ENERGYDIV10;
         else
            format = ENERGY;
         break;
   
      case PKPOWERMODE:
         strcpy(CurrentPreset.PresetID, "PP=");
         format = PERCENTX10;
         Value = CurrentPreset.PeakPwr;
         break;
   
      case COLLAPSEMODE:
         strcpy(CurrentPreset.PresetID, "Cl=");
         format = DISTANCE;
         Value = CurrentPreset.ColDist;
         break;

      case ABSOLUTEMODE:
         strcpy(CurrentPreset.PresetID, "Ab=");
         format = DISTANCE;
         Value = CurrentPreset.AbsDist;
         break;

      case GRDDETECTMODE:
         strcpy(CurrentPreset.PresetID, "GD=");
         format = TIME;
         Value = CurrentPreset.ScrubTime;
         break;

      case CONTINUOUSMODE:
         strcpy(CurrentPreset.PresetID, "Continuous");
         break;

      default:
         strcpy(CurrentPreset.PresetID, "Bad Mode");
         break;
   }

   if (Value)
   {
      StringSize = strlen(CurrentPreset.PresetID);
      NumSize = PRESETLEN - StringSize - 3; /* 3 = 2 units chrs + 0 end */

      FormatVariables( Value, format, TempString, NumSize, CurrentSetup.Units );

      TempString[NumSize++] = '&';    /* Add units & terminator */
      TempString[NumSize++] = '&';
      TempString[NumSize++] = 0;
      InsertProperUnits( TempString, format );
      
      CPtr = TempString;
      while (*CPtr == ' ')
         CPtr++;

      strcat( CurrentPreset.PresetID, CPtr );
   }
   StringSize = strlen(CurrentPreset.PresetID); /* Pad with spaces */
   CPtr = &CurrentPreset.PresetID[StringSize];
   while (StringSize++ < PRESETLEN-1)
      *CPtr++ = ' ';

   *CPtr = 0;     /* Supply final terminator */
}



void UseSameNamePreset(UINT32 Cond)
/*****************************************************************************/
/*                                                                           */
/*  Cond = NAME_NEW:     Use NewSameName (Name of preset your writing to)    */
/*  Cond = NAME_CURRENT: Use OldSameName (Name of preset current running)    */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 Length;

   switch (Cond) {
      case NAME_NEW:                   /* Use name of preset that exists where you are writing */
         Length = strlen(NewSameName);
         strcpy(CurrentPreset.PresetID, &NewSameName[1]);  /* Start at 1 to remove front quote */
         CurrentPreset.PresetID[Length-2] = NULL;          /* Remove back quote                */
         break;

      default:
      case NAME_CURRENT:               /* Use name that exists in the current preset           */
         Length = strlen(OldSameName);
         strcpy(CurrentPreset.PresetID, &OldSameName[1]);  /* Start at 1 to remove front quote */
         CurrentPreset.PresetID[Length-2] = NULL;          /* Remove back quote                */
         break;
   }
}



UINT8 IsPresetEnabled(UINT8 PresetNumber)
{
   UINT8 PresetFlag = FALSE;
 
   if (PresetNumber <= MAX_PRESETS) {
      if (PresetEnableFlags[PresetNumber] == TRUE) {
         PresetFlag = TRUE;
      } 
   }
   return(PresetFlag);
}

void RecallPreset( UINT32 PresetNum )
{
   UINT16 DUPS_paramsetno = DUPS_SUCCESS;

   if (PresetEnableFlags[PresetNum])
   {
      if ( ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
           &&(IsThereDataPrinting == FALSE))
      {  // Ok to recall preset since no weld in progress
         StopStateMachine();
   
         if (CurrentPreset.PresetUpdateComplete == TRUE)
            WritePreset(CurrentSetup.ActivePreset);   /* Save Current Preset   */
         
           // Now if the user makes any changes and doesn't want to save the changes, he can do a recall preset 
           // which will discard the changes he made and will restore the original values. 
   
           // If there is a DUPS then    
           // Find the associated DUPS param set number and do an upload Parameter set.
         if (CheckForDups())
         {
             if ( (DUPS_paramsetno = DUPS_FindDUPS4COP(PresetNum)) == DUPS_PARAMSETUNDEF)
             {  //  no associated Parameter set means invalid preset
                RecordSetupAlarm(SE268);
                RecordErrorCode( ERRORCODE9_SE268 );
                ResetStateMachine();       /* We must restart the state machine even if an error */
                StartStateMachine();
             }  // fatal error, invalid preset since there is no associated DUPS Parameter Set
             else  // get the associated DUPS Parameter Set
             {
                //DUPS_QueuedUploadPS(DUPS_paramsetno);
                //DUPS_QueuedDownloadPS();
                DUPS_SelectParamSetNum(DUPS_paramsetno);
                RefreshDUPSParam ((PRESET_COMPRESSED *) PresetAddress[PresetNum]);
             }  // end of else -- get the associated DUPS Parameter Set
         }  // end of if (CheckDups())
   
         if (DUPS_paramsetno != DUPS_PARAMSETUNDEF)
         {  // if there was an associated Parameter set or if this is an analog power supply
            CurrentSetup.ActivePreset = PresetNum;        
            UpdateRunningPreset = TRUE;
            ReadPreset(CurrentSetup.ActivePreset, FALSE);
            WritePreset(0);                           /* Update Running Preset */
            UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
            ResetRecall_UpdateFlag = TRUE;
            ResetStateMachine();
            StartStateMachine();
            SendFakeKeyPress(RunKey);
         }  // if there was an associated Parameter set or if this is an analog power supply
      } // end of -- Ok to recall preset since no weld in progress
      else  // can't recall preset right now because weld in progress
      {
      } // else can't recall preset right now because weld in progress
   }
      else Beep(ERRORBEEP);
}  // end of RecallPreset( UINT16 PresetNum )



BOOLEAN RecallExtPreset(UINT16 PresetCode)
/***************************************************************************/
/*                                                                         */
/*  This function is called from the Weld Manager when a preset is         */
/*  externally selected. This function is for the Analog/Digital Power     */
/*  Supply. Return FALSE if preset not recalled.                           */
/*                                                                         */
/*  Caveat: There can be no pSOS calls from this function because it is    */
/*          already called from the highest priority task.                 */
/*                                                                         */
/***************************************************************************/
{
   BOOLEAN PresetRecalled = TRUE;
   CONFIGSETUP *BBRPtr;
   UINT16 DUPS_paramsetno = DUPS_SUCCESS;

   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   /* check if preset is available.*/
   if (PresetEnableFlags[PresetCode] &&  (PresetCode <= MAX_PRESETS) &&
       (QVGAHwAvail || CurrentSetup.ControlLevel >= PresetControlLevel[PresetCode]))  
   {
      StopStateMachine(); /*Stop the state machine.*/
      if (CheckForDups())
      {
          if( (DUPS_paramsetno = DUPS_FindDUPS4COP(PresetCode)) == DUPS_PARAMSETUNDEF)
          {  //  no associated Parameter set means invalid preset
             RecordSetupAlarm(SE268);
             RecordErrorCode( ERRORCODE9_SE268 );
             PresetRecalled = FALSE;
          }  // fatal error, invalid preset since there is no associated DUPS Parameter Set
          else  // get the associated DUPS Parameter Set
          {
             DUPS_SelectParamSetNum(DUPS_paramsetno);
             RefreshDUPSParam ((PRESET_COMPRESSED *) PresetAddress[PresetCode]);            
          }  // end of else -- get the associated DUPS Parameter Set
      }  // end of if (CheckDups())
      
      
      
      if (DUPS_paramsetno != DUPS_PARAMSETUNDEF)
      {
      
         CurrentSetup.ActivePreset = PresetCode;  
         BBRPtr->ActivePreset = PresetCode;          /* Save in BBR in case power lost illegally */
         RecallCompressedPreset(PresetAddress[PresetCode]); /* Read the PresetCode from BBram */
         CurrentPreset.PresetID[PRESETLEN] = 0;
         FormatRunScreenTopLine();
         /* If not ready do not update the running preset check the UpdateDispFlag
          on the next palm button pressed */
         LimitChanged = FALSE;
         SaveCompressedPreset( (PRESET_COMPRESSED *) PRESET_0_START, &CurrentPreset);
      
        /* if ( (RunScreenFlag == FALSE) || ((RunScreenFlag == TRUE) && (MenuCounter > 1) &&
            (AdjustWeldSetupMenuFlag == TRUE)))
            SendFakeKeyPress(RunKey);
         else */
         SendFakeKeyPress(UPDATEDISPLAY); /* Updates preset name and # on line 2 */
         ResetRecall_UpdateFlag = TRUE;
         ConfirmPresetFlag = TRUE;
      }
      StartStateMachine(); /*Restart the state machine.*/
   }
   else  /* generate the external preset alarm */
   {
      RecordSetupAlarm(SE46); /* "Preset Not Available" alarm */    
      PresetRecalled = FALSE;
   }
   return(PresetRecalled);
}

void ClearHistoryInBbram(void)
/**---------------------------------------------**
 ** This function Clears Weld History Data from **
 ** BBRAM when a Preset is recalled.            **
 **---------------------------------------------**/  
{
   UINT8 *HistBattramPtr; /* points to Weld History data location in BBRAM */
   UINT16 ByteCount;

   HistBattramPtr = (UINT8 *) BBR800_HISTORY_START;

   for(ByteCount = 0; ByteCount < BBR800_HISTORY_SIZE; ByteCount++){
      *HistBattramPtr++ = 0;
   }
   
   CurrentSetup.WeldHistoryPtr = (BBR800_HISTORY_START);

   WeldDataOffset = 0;           /*-- Reset the counter to 1 line data record --*/
   PrinterTotalCount = 0;        /*-- Reset graph data --*/
   ClearDataStorage();           /*-- Reset graph data --*/
}



void PresetClear(UINT16 presetNumber)
/*****************************************************************************/
/*  This function will clear a preset.  In reality it will simply set the    */
/*  preset name string to a NULL.  If the preset number being cleared is the */
/*  same as the one currently in use, then the name of the current preset in */
/*  zero is also set to NULL.                                                */
/*****************************************************************************/
{
   PRESET_COMPRESSED *PresetPtr;

   PresetPtr = PresetAddress[presetNumber];
   DUPS_ClearDUPSParamSet(presetNumber);
   PresetPtr->PresetID[0] = NULL;                          /* Make name NULL */
   if (CurrentSetup.ActivePreset == presetNumber)
   {
      CurrentSetup.ActivePreset = 0;
      strcpy(CurrentPreset.PresetID, "");                     /* Clear preset name       */
      SaveCompressedPreset(PresetAddress[0], &CurrentPreset); /* Save Preset0            */
      CurrentPreset.PresetUpdateComplete = FALSE;
   }
}                                                



/**   Check for presence of DUPS  **/

UINT16 CheckForDups(void)
{
  return (DUPS_Info.DUPSFlag);
}

void SaveDUPSParameters(UINT16 ActivePreset)
/***************************************************************************/
/*Description                                                              */
/*   Update the three DUPS parameters to the compressed preset when saving */
/*   the preset into the battram.                                          */
/***************************************************************************/
{
   PRESET_COMPRESSED* CompPreset;
   
   CompPreset = PresetAddress[ActivePreset];
   CompPreset->SwDip = DUPS_CurrentParamSet.SWDipSetting;
   CompPreset->SeekTime = DUPS_CurrentParamSet.SeekTime;
   CompPreset->WeldRampTime = DUPS_CurrentParamSet.WeldRampTime;
}

void RefreshDUPSParam (PRESET_COMPRESSED* CompPreset)
/*****************************************************************************/
/*                                                                           */
/* This function refresh the DUPS current parameter set from the Compress    */
/* preset values.                                                            */
/*                                                                           */
/*****************************************************************************/
{
   DUPS_CurrentParamSet.SWDipSetting = CompPreset->SwDip;
   DUPS_CurrentParamSet.SeekTime = CompPreset->SeekTime;
   DUPS_CurrentParamSet.WeldRampTime = CompPreset->WeldRampTime;
   
   if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPSTOREMEMATWLDEND) /* Check for bit4 if set flag = True*/
      DUPS_Info. DUPSMemFlag = TRUE;
   else                                /*Update status in DUPS Info*/
      DUPS_Info. DUPSMemFlag = FALSE;

   if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPAUTOSEEK)/* Check for bit6 if set flag = True*/
      DUPS_Info. DUPSSeekFlag = TRUE;
   else              
      DUPS_Info. DUPSSeekFlag = FALSE;  

   if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPCLEARMEMATRST) /* Check for bit3 if set flag = True*/
      DUPS_Info. DUPSMemRstFlag = TRUE;
   else                                /*Update status in DUPS Info*/
      DUPS_Info. DUPSMemRstFlag = FALSE;

}

void UpdateDUPSRAMParamSet(void)
/***************************************************************************/
/*Description                                                              */
/* if preset is Recalled, DUPS_CurrentParamSet may not have latest         */
/* Param list, while recalling we just updating 3 setupscreen params in    */
/* DUPS_CurrentParamSet. To get Actuall Working param set, we must upload  */
/* the paramlist from DUPS.                                                */
/***************************************************************************/
{
   if(IsRecalledPreset)
   {
      DUPS_CurrPSStatus = DUPS_PENDING;
      DUPS_UploadParamSet(CurrentSetup.DUPS_WorkingPreset);
      DUPS_Wait4CurrPS();
   }
}

BOOLEAN RecallAndVerifyPreset (UINT32 PresetNum)
/****************************************************************************/
/*Description:                                                              */
/*   This function Verify the selected preset from the menu structure.      */
/*   This will first recall the selcted preset if the selected preset is not*/
/*   same as the ActivePreset and then verify the preset.                   */
/*   Returns FALSE if the preset is not enabled.                            */ 
/****************************************************************************/
{
   UINT16 DUPS_paramsetno = DUPS_SUCCESS;
   BOOLEAN PresetVerified = FALSE;
   FP_KEY_PRESSED_MSG       FPKeyMsg;
   WELD_DATA_MSG            WeldDataMsg;
   
   if (PresetEnableFlags[PresetNum])
   {
       StopStateMachine();
       SerialMessageQueue( (UINT8*)"11", 2 );
       if(PresetNum != CurrentSetup.ActivePreset)
       {
           if (CurrentPreset.PresetUpdateComplete == TRUE)
              WritePreset(CurrentSetup.ActivePreset);   /* Save Current Preset   */
         
           if (CheckForDups())
           {
              SerialMessageQueue( (UINT8*)"22", 2 ); 
              if ( (DUPS_paramsetno = DUPS_FindDUPS4COP(PresetNum)) == DUPS_PARAMSETUNDEF)
               {  //  no associated Parameter set means invalid preset
                  RecordSetupAlarm(SE268);
                  RecordErrorCode( ERRORCODE9_SE268 );
                  ResetStateMachine();       /* We must restart the state machine even if an error */
                  StartStateMachine();
               }  // fatal error, invalid preset since there is no associated DUPS Parameter Set
               else  // get the associated DUPS Parameter Set
               {
                  DUPS_SelectParamSetNum(DUPS_paramsetno);
                  RefreshDUPSParam ((PRESET_COMPRESSED *) PresetAddress[PresetNum]);
               }  // end of else -- get the associated DUPS Parameter Set
           }  // end of if (CheckDups())
   
           if (DUPS_paramsetno != DUPS_PARAMSETUNDEF)
           {  // if there was an associated Parameter set or if this is an analog power supply
              SerialMessageQueue( (UINT8*)"33", 2 );
              CurrentSetup.ActivePreset = PresetNum;        
              ReadPreset(CurrentSetup.ActivePreset, TRUE);
              WritePreset(0);
              UpdateCurrentPreset(ACTIVEPRESET, 0, 0);
   
           }
           LimitChanged = FALSE;
       }
        if(DUPS_paramsetno != DUPS_PARAMSETUNDEF)
        {
            SerialMessageQueue( (UINT8*)"44", 2 ); 
            UpdateRPreset();/*Update the RunningPreset*/
            if(AlarmDetectedFlag == TRUE)
            {
               ClearSetupAlarms();
               /*Clear all the alarms before verification.*/  
               ClearGeneralAlarm();
               ClearWeldingResultsAlarms();
               ClearFinalResultsAlarms();
               ClearAlarm(FinalResults.EquipmentFailureAlarms);
               /* If all the alarms are cleared. */
               if ((FinalResults.EquipmentFailureAlarms == 0) &&
                (FinalResults.CalibrateAlarms == 0) )
               {
                  AlarmOff();     /* Turn off Reset led               */
                  AlarmDetectedFlag = FALSE;
               }
            }
            CountAlarms();
            /* Carry this count into RecordAlarm       */
            AlarmCounter = TotalAlarmCount; 
            VerifyPreset();  
            CountAlarms();
            if(TotalAlarmCount != 0)
               AlarmDetectedFlag = TRUE;
            else  AlarmOff();
            if(RunScreenFlag && MenuCounter == 1)
               SendFakeKeyPress(UPDATELINE2);              
            /* If QVGA H/W is available send Message to the QVGA queue*/
            if(QVGAHwAvail)
            {
               FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
               FPKeyMsg.key = UPDATELINE2;                        
               CkQSend (QvgaQid, &FPKeyMsg, SYS_MANAGER,
                           __LINE__, MILLS_TO_TICKS(20));   /* 20 ms        */
            }
            UpdateFlag = FALSE;
            PresetVerified = TRUE;
        }
        ResetStateMachine ();
        StartStateMachine ();
   }
   else Beep(ERRORBEEP);
   
   return(PresetVerified);
} 

void PresetVerifyManually (UINT32 PresetNum)
/*****************************************************************************/
/*Description:                                                               */
/*   This function verify the preset in Ready or Pre-Ready state and display */
/*   the respective results for two seconds. Else this will display an error */
/*   message to wait for ready state.                                        */  
/*****************************************************************************/
{
   /* Check for the Ready or Pre-Ready state. */ 
   if ( ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE))
        &&(IsThereDataPrinting == FALSE) && (IsGraphDrawing == FALSE))
   {
       if(RecallAndVerifyPreset(PresetNum))
       /* If the preset is enabled & undergone to verify procedure. */
       {
          if(CurrentPreset.Verified)
          {
             tm_wkafter( MS_TO_TICKS( WAIT_2SEC ));
             SendFakeKeyPress( UPDATEDISPLAY ); 
          }
          else
          {
             tm_wkafter( MS_TO_TICKS( WAIT_2SEC ));
             SendFakeKeyPress( UPDATEDISPLAY );                
          }
       }
   } 
   else 
   {
      tm_wkafter( MS_TO_TICKS( WAIT_4SEC ));
      SendFakeKeyPress( UPDATEDISPLAY ); 
   }  
   
}

void DoSequenceFunction(UINT32 PresetNum)
/*****************************************************************************/
/*Description:                                                               */
/*   This function replace, insert before and insert after items to the      */
/*   sequencing list.                                                        */
/*****************************************************************************/
{
   UINT8 TempSeqList[MAX_SEQUENCE_NOS];
   UINT8 i, j;
      
   switch (SeqActionType) {
      case 1:                      /* Replace the selected sequence preset */
         if(SequencePresetSelected <= CurrentSetup.SequenceCount &&
             PresetEnableFlags[PresetNum] == TRUE )
            CurrentSetup.SequenceList[SequencePresetSelected-1] = (UINT8)PresetNum;
         break;

      case 2:                     /* Insert Before the selected sequence */
         if(CurrentSetup.SequenceCount < MAX_SEQUENCE_NOS &&
             SequencePresetSelected <= (CurrentSetup.SequenceCount+1) &&
             PresetEnableFlags[PresetNum] == TRUE )
         {
            for(i = 0; i < SequencePresetSelected - 1 ; i++ )
               TempSeqList[i] = CurrentSetup.SequenceList[i]; 
            TempSeqList[SequencePresetSelected-1] = (UINT8)PresetNum;
            for(j = i; j < CurrentSetup.SequenceCount; j++)
               TempSeqList[j+1] = CurrentSetup.SequenceList[j];
            CurrentSetup.SequenceCount++; 
            for(i = 0; i < CurrentSetup.SequenceCount; i++)   
               CurrentSetup.SequenceList[i] = TempSeqList[i];
         }   
         break;

      case 3:                    /* Insert after the selected sequence */
         if(CurrentSetup.SequenceCount < MAX_SEQUENCE_NOS &&
             SequencePresetSelected <= CurrentSetup.SequenceCount &&
             PresetEnableFlags[PresetNum] == TRUE )
         {
            for(i = 0; i < SequencePresetSelected ; i++ )
               TempSeqList[i] = CurrentSetup.SequenceList[i]; 
            TempSeqList[SequencePresetSelected] = (UINT8)PresetNum;
            for(j = i; j < CurrentSetup.SequenceCount; j++)
               TempSeqList[j+1] = CurrentSetup.SequenceList[j];
            CurrentSetup.SequenceCount++;    
            for(i = 0; i < CurrentSetup.SequenceCount; i++)   
               CurrentSetup.SequenceList[i] = TempSeqList[i];
         }   
         break;

   }
   GetSequenceName(0);
   SeqActionType = 0;
}   

void GetSequenceName(UINT32 dummy)
/*****************************************************************************/
/*Description:                                                               */
/*   This function populates all the sequencing item strings                 */
/*****************************************************************************/
{
   UINT16 i, j;
   
   for (i = 1; i <= MAX_SEQUENCE_NOS; i++)
   {
      SPrintf(SequencePtrs[i], "%2d", i);
      strcat(SequencePtrs[i], ". ");
      if (i <= CurrentSetup.SequenceCount)
      {
         j = CurrentSetup.SequenceList[i-1];
         strcat(SequencePtrs[i], PresetPtrs[j]);  
         if (i == (CurrentSetup.SequenceNos+1))
            strcat(SequencePtrs[i], "*");                
      }
   }   
}


