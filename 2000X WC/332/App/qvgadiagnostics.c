/* $Header:   D:/SWLab/VMdb/2000Series/App/qvgadiagnostics.c_v   1.34   09 Sep 2008 20:40:04   nhahmed  $ */
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
/****************************************************************************/
/*
---------------------------- MODULE DESCRIPTION -------------------------------

     Module name:

        Filename: QVGADiagnostics.c

      Written by: JOY MD 
            Date: 04/17/2003 
        Language: "C"

--------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========       ======      ===========
      1.0          06/17/03       JOY        Initial Version
      1.2          06/29/03       JOY        Added Horn Scan.
      1.3          07/25/03       SCM        Checked in for Laura's build.
      1.5          08/27/03       JOY        In case of Estop return FALSE in
                                             - 'ChangeDigitalTune()'. 
      1.6          09/22/03       JOY        Button Stuck Problem is solved.
      1.7          10/16/03       JOY        MiddleSeg. is erased by QVGA ROM image.
      1.8          10/20/03       LAM        made act cold start for d aed|aef.
      1.9          10/23/03       JOY        Added Touch Release Beep. 
      1.11         11/24/03       JOY        Horn Scan graph print/display enabled
                                             at power up.
      1.12         12-09-03       BEKymer    Add argument member to SUBMENU and
                                              TEXT structures as needed
      1.13         02-25-04       VSharma    Added QVGABransonFuncMenu & modified 
                                              QVGADiagnosticMenu1.
      1.14         03-03-04       VSharma    Added QVGATestingMenu & QVGASpecialsMenu.
      1.15         04-12-04       VSharma    Modified EnableHSStart().
      1.16         05-17-04       VSharma    Moved function prototypes to 'menu5.h'.
      1.17         07-08-04       BEKymer    Remove calls to start/stop state
                                              machine for DoColdStart because
                                              DoColdStart does it now.
      1.18         07-27-04       JOY        Added FREQ60KHZ to the UpdateDigitalFreq().
      1.19         08-24-04       JOY        Data type of variable 'QVGALatchPSStore' changed to UINT8.
      1.20         07-25-05       Bwadia     QVGA code clean up, Diagnostics and 
                                             Horn scan implementation for SBC for Ver10.0e
      1.21         08-19-05       Bwadia     IsHWConfigured function used to check for
                                             VGA hardware presence 
      1.22         09-10-05       Bwadia     Horn scan Menu changed. VGAtext objects
                                             for frequency removed and added in 
                                             Horn scan graph object
      1.23         10-11-05       Bwadia     QVGA print scan graph removed from the
                                             Horn scan menu 
      1.24         12-20-05       Bwadia     Dummy check in
      1.25         01-03-06       Bwadia     VGABOTTOMHALF object param IDs added.
                                             Modified for tracker 3972    
      1.26         03-02-06       Bwadia     Refresh rate for hornscan BottomHalfmenu is 1 sec  
      1.27         04-24-06       Bwadia     Removed two menu items from Horn scan bottom
                                             half menu. They are done locally at SBC side 
      1.28         12-22-06       NHAhmed    Added Pop up before Sensor Cal Screen.
      1.29         04-16-07       NHAhmed    Added Menu for Horn Scan Backup.
      1.30         05-28-07       NHAhmed    Added LimitChanged = TRUE at cold start.
      1.31         04-14-08       NHAhmed    Replicated some functions as no-argument type.
      1.32         09-02-08       NHAhmed    CleanUp for multi-language support.
      1.33         09-04-08       YGupta     CleanUp for LangTest Project.
      1.34         09-09-08       NHAhmed    CleanUp for multi-language support.
*/

/*
 ------------------------------- DESCRIPTION ---------------------------------
*/


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include <string.h>
#include "beep.h"
#include "menu.h"
#include "menu5.h"
#include "qvgamenu.h"
#include "DrawScrn.h"
#include "dups_api.h"
#include "digout.h"
#include "statedrv.h"
#include "spidd.h"
#include "preset.h"
#include "param.h"
#include "util.h"
#include "selctkey.h"
#include "state.h"
#include "ticks.h"
#include "snsrcalb.h"
#include "inports.h"
#include "command.h"
/*------------------------------- LOCAL DEFINES ----------------------------*/

/*------------------------------- GLOBAL DATA ------------------------------*/
BOOLEAN QVGAHornScanOLD = FALSE;    // Horn Scan Overload 
BOOLEAN QVGAAbortHornScan = FALSE;  // Abort the Horn Scan.
BOOLEAN VGADigitalChoiceWaitFlag = FALSE;
BOOLEAN VGADigitalChoiceTestFlag = FALSE;
BOOLEAN VGAColdStartFlag = FALSE;
BOOLEAN VGAColdStartErrorFlag = FALSE;
BOOLEAN VGAActStartFlag = FALSE;
BOOLEAN VGAActStartErrorFlag = FALSE;
UINT16 BransonFunctionFlag = FALSE;
UINT8 AbortScanButtonState;
UINT8 PrevHornState = 0;
UINT16 ShowHSAbort = FALSE;
MENUEND endlistDiag = { TRUE };
BOOLEAN VGARunSelected, VGAClearSelected, VGASeekSelected, VGAStoreSelected;

BOOLEAN  ForceDigitalTuneTest = FALSE; /* TRUE if user must press Test to exit */
SINT32   SaveDigPotValue;   /* Used to determine if user changed value */

/*--------------------------- EXTERN FUNCTION PROTOTYPES --------------------*/

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/
void UpdateFrequencyResonance(void);
void PressTestMsgScrn(void);
static void QVGAWaitDigPotPosition(void);
void GetRunSelection(void);
void GetClearSelection(void);
void GetSeekSelection(void);
void GetStoreSelection(void);
UINT16 LangStrLen(SINT8 * str); 
BOOLEAN LangCheckNull(SINT8 * Line);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void UpdateCurrentPresetAndSetup(void);


/*---------------------------- EXTERNAL DATA -------------------------------*/

extern BOOLEAN NextMenuFlag;
extern BOOLEAN HSStartFlag;
extern UINT8  LimitChanged;
extern BOOLEAN LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;
extern UINT8 QVGALatchPSStore;
extern QVGA_MENU_INFO MenuLevelInfo[];
extern BUTTON_STATE TouchedButtonState;
extern BOOLEAN DigPotKey;
extern BOOLEAN HSNotStarted;
extern BOOLEAN IsGraphDrawing;
extern CONFIGSETUP CurrentSetup;
extern UINT16 OrigDigPotFlag;        /* Initial DigPot On/Off state */
extern SINT32 OrigDigPotValue;       /* Initial DigPot value before editing */
extern SINT32 DigPotValue;           /* This is what user edits */
extern SINT32 MinDigPotValue;        /* Min value allowed in editing */
extern SINT32 MaxDigPotValue;        /* Max value allowed in editing */
extern UINT16  LangIndex;            /*Language Index*/
extern UINT16  TestingMenuFlag;
extern UINT16  SpecialMenuFlag;
extern UINT16 ResonanceFreqEnable[];
extern UINT16 DiagFlag;

extern CONFIRM_SCREEN_TYPE ConfirmType;
extern BOOLEAN IsThereDataPrinting;
extern enum WELDSTATES WeldState;
extern const SINT8 StrQVGABlankLine[];

extern BOOLEAN UserIOAlarmMenu;
extern BOOLEAN StateMachineDisabled;
void  ExitMenuAndEnableWeld (void);
extern UINT32 NackError, ErrorResponseMinLimit, ErrorResponseMaxLimit;

/*
 ---------------------------------- CODE -------------------------------------
*/

void QVGADigitalPotChoiceDone(void)
/****************************************************************************/
/*Description:                                                              */
/* This function is called after the user has selected On or Off for        */
/* Digital Tune.                                                            */
/* This function needs to take action only if current setting is Off.       */
/* If it was originally Off, just restart state machine.  If it was         */
/* originally On, user will be forced to press the Test key.                */
/****************************************************************************/
{
   UINT32  FreqAtCenter;

   FreqAtCenter = GetPowerSupplyFrequency();

   if (!(CurrentSetup.DigPotFlag & BIT0))  /* If now Off ... */
   {
      /* If was originally On and digpot position changed, make */
      /* user push Test key */

      if (OrigDigPotFlag && (FreqAtCenter != OrigDigPotValue))
      {
         CenterDigPot();
         VGADigitalChoiceWaitFlag = TRUE;   /* Wait for pot to center */
         
         VGADigitalChoiceTestFlag = TRUE;         
      }
      else     /* No change, just allow welding & go */
      {
         ResetStateMachine();
         StartStateMachine();
      }
   }
   else
   {
      ResetStateMachine();   /* Covers On + GoBack case and anything */
      StartStateMachine();   /* else we haven't thought of. */
   }
}


void UpdateDigitalFreq(void)
/***************************************************************************/
/*Description:                                                             */
/* Update the variable'DigPotValue'(Digital tune start Freq:) so that      */
/* actual freq: value is displayed when entering in to the DIAG_SCREEN.    */
/***************************************************************************/
{
   UINT32 FreqAtCenter;
   SINT32 CurrentDigPotPos;
   
   OrigDigPotFlag = CurrentSetup.DigPotFlag & BIT0;

   if (OrigDigPotFlag)                        /* If not in use now, orig */
      CurrentDigPotPos = CurrentSetup.DigPot; /* position is "centered" */
   else
      CurrentDigPotPos = 0;
   FreqAtCenter = GetPowerSupplyFrequency();

   switch (CurrentSetup.PSFreq)
   {
      case FREQ20KHZ:
         DigPotValue = CurrentDigPotPos/6 + FreqAtCenter;
         MinDigPotValue = FreqAtCenter - 499;
         MaxDigPotValue = FreqAtCenter + 500;
         break;
      case FREQ15KHZ:
         DigPotValue = CurrentDigPotPos/8 + FreqAtCenter;
         MinDigPotValue = FreqAtCenter - 374;
         MaxDigPotValue = FreqAtCenter + 375;
         break;
      case FREQ30KHZ:
         DigPotValue = CurrentDigPotPos/4 + FreqAtCenter;
         MinDigPotValue = FreqAtCenter - 749;
         MaxDigPotValue = FreqAtCenter + 750;
         break;
      case FREQ60KHZ:
         DigPotValue = CurrentDigPotPos/2 + FreqAtCenter;
         MinDigPotValue = FreqAtCenter - 1499;
         MaxDigPotValue = FreqAtCenter + 1500;
         break;   
      case FREQ40KHZ:
      default:
         DigPotValue = CurrentDigPotPos/3 + FreqAtCenter;
         MinDigPotValue = FreqAtCenter - 999;
         MaxDigPotValue = FreqAtCenter + 1000;
         break;
   }
}

void EnableHornScanStart(void)
/***************************************************************************/
/*Description:                                                             */
/* Set 'HSNotStarted' flag before entering in to the HORN SCAN SCREEN      */
/* Set Horn scan status to DUPS_NOSCAN.                                    */
/***************************************************************************/
{
   if (UserIOAlarmMenu || StateMachineDisabled)
      ExitMenuAndEnableWeld();
   if(WeldState != READYSTATE)  
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
   DiagFlag = FALSE;
   HSStartFlag = FALSE;
   HSNotStarted = TRUE;
   if(HornScanInfo. ScanStatus == DUPS_SCANINPROG)
      HornScanInfo. ScanStatus = DUPS_NOSCAN;
   PrevHornState = SCAN_NONE;
   UpdateFrequencyResonance();
}

void DisableDiagnostics(void)
{
   DiagFlag = FALSE;
}

void GetRunSelection(void)
/***************************************************************************/
/*Description:                                                             */
/* Gets Run Selection for VGACHECK object                                  */
/***************************************************************************/
{
   VGARunSelected = LatchPSRun;
   LatchPSRun = FALSE;
}

void GetClearSelection(void)
/***************************************************************************/
/*Description:                                                             */
/* Gets Clear Selection for VGACHECK object                                */
/***************************************************************************/
{
   VGAClearSelected = LatchPSClear;
   LatchPSClear = FALSE;
}

void GetSeekSelection(void)
/***************************************************************************/
/*Description:                                                             */
/* Gets Seek Selection for VGACHECK object                                 */
/***************************************************************************/
{
   VGASeekSelected = LatchPSSeek;
   LatchPSSeek = FALSE;
}

void GetStoreSelection(void)
/***************************************************************************/
/*Description:                                                             */
/* Gets Store Selection for VGACHECK object                                */
/***************************************************************************/
{
   VGAStoreSelected = (LatchPSStore || QVGALatchPSStore );
   LatchPSStore = FALSE;
}

void ProcessHSAbort1 (void)
/***************************************************************************/
/*Description:                                                             */
/* Processes Horn scan by setting the Flag True                            */
/***************************************************************************/
{
   ShowHSAbort = FALSE;
   QVGAAbortHornScan = TRUE;
}

void SetDigtalPot(void)
/***************************************************************************/
/*Description:                                                             */
/* Makes Digital pot setting zero if making Digital tune OFF               */
/***************************************************************************/
{
   if (!ForceDigitalTuneTest)
   {
      CurrentSetup.DigPot = 0;
      UpdateCurrentPresetAndSetup();
   }
}

void VGACheckDigitalTune(void)
/***************************************************************************/
/*Description:                                                             */
/* Performs Digital Tune                                                   */
/* There is no data printing/Drawing is going on...                        */
/***************************************************************************/
{
   if (!CheckStateMachine())
   {
      if (SaveDigPotValue != DigPotValue)
      {
         SetDigPot();      /* CurrentSetup.DigPot updated already */
                               /* on exit from VARIABLE entry. */
         VGADigitalChoiceWaitFlag = TRUE;   /* Wait for pot to center */
         ForceDigitalTuneTest = TRUE;
         VGADigitalChoiceTestFlag = TRUE;         
      }
      else if (!ForceDigitalTuneTest)
      {
         ResetStateMachine();  /* Position is at original value, */
         StartStateMachine();  /* don't need to force Test.      */
      }
   }
}

void ColdStartEnable(void)
/***************************************************************************/
/*Description:                                                             */
/* Do the Cold start if weld state is either ready/pre-ready state and     */
/* There is no data printing/Drawing is going on...                        */
/***************************************************************************/
{
   if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) &&
      (IsThereDataPrinting == FALSE) && (IsGraphDrawing == FALSE))
   {
      VGAColdStartFlag = TRUE;
      LimitChanged = TRUE;
   }
   else
      VGAColdStartErrorFlag = TRUE;
}

void VGADoColdStart(void)
/***************************************************************************/
/*Description:                                                             */
/* Do the Cold start. If VGA is present then Polling command initiates Cold*/
/* start else it will be done here                                         */
/***************************************************************************/
{
   if (IsHWConfigured(VGA))
      VGAColdStartFlag = TRUE;
   else
      DoColdStart();   
}


void VGAActColdStart(void)
/***************************************************************************/
/*Description:                                                             */
/* Do Actuator Cold start.                                                 */
/***************************************************************************/
{
   BuildDefaultSpringRate();    /* welding */     
   ResetStateMachine();
   StartStateMachine();
   NextMenuFlag = TRUE;
}

void EnableActColdStart(void)
/***************************************************************************/
/*Description:                                                             */
/* Do the Actuator Cold start if weld state is either ready/pre-ready state*/
/* And there is no data printing/Drawing is going on...                    */
/***************************************************************************/
{
   if (((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) &&
      (IsThereDataPrinting == FALSE)&& (IsGraphDrawing == FALSE))
   { 
      StopStateMachine();          /* Perform cold start only if not */
      VGAActStartFlag = TRUE;
   }   
   else
      VGAActStartErrorFlag = TRUE;
}

 /*=========================================================================*/
 /*******************************END*****************************************/
 /*=========================================================================*/
 