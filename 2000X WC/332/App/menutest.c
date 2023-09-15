/* $Header:   D:/SWLab/VMdb/2000Series/App/MENUTEST.C_V   2.47.1.2   04 Sep 2008 20:16:30   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*---------------------------- MODULE DESCRIPTION --------------------------*/

/* Module name: menutest.c                                                  */

/* Filename:                                                                */

/* Function name:                                                           */

                                
/*-------------------------------- REVISIONS -------------------------------

   Revision # Date     Author   Description                    
   ========== ======== =======  ===========                    
   0          11-??-95 BEK      Initial Version                
   1.00       05/14/96 PJ       Prototypes in menutest.h
                                 Strings in menutext.c
   2.50       10/09/96 PhilJ    Changed Menus to type const. 
   2.60       10/27/96 PhilJ    Swapped order of menus FActual &
                                 FMemory with RunSeek & StoreClear. 
   2.70       11-04-96 BEKymer  Uncomment variables in Factual & Fmemory
   2.80       11-14-96 BEKymer  Made Test amplitude savable
   2.90       12-17-96 PhilJ    Changed F Memory menu to read only
   3.00       01-10-97 PhilJ    UINT32 CurrentFreqIn to SINT32
   4.00       02-06-97 LAM      reordered menu                 
   5.00       02-14-97 LAM      defined testbuffer             
   6.00       03-07-97 LAM      correct testpower              
   7.00       04-08-97 LAM      made testpower format as watts              
   2.16       06-11-97 LAM      chged run seek line                         
   2.17       07-01-97 LAM      chged run seek line for release 2                         
   2.18       07-17-97 PhilJ    chged special asci character in
                                 TestBuffer1 from @ to ~.
   2.19       09-11-97 LAM      unit test version,chged power to model2                                         
   2.20       10-27-97 LAM      made testamp a normal feature                                                   
   2.21       11-4-97  BJB      Numerous new "includes".
                                 Added function DoTestMode().
   2.22       11-14-97 kgd      DCS # 1000
   2.23       11-20-97 BJB      Added (no) response to ResetKey.
   2.23       11-21-97 kgd      DCS #1000 improvement
   2.24       11-21-97 LAM      fixed transmission problem with Kevin
   2.25       12-2-97  kgd      DCS #1000 improvement
   2.26          ?
   2.27       12-29-97 BJB      Deleted Ascent terminal support code.
   2.28       12-29-97 BJB      Structure changes to prepare for new terminal code:
                                ScrollSize removed, fixed at 1.
                                BuildMenu() returns # of lines, not # of pages, so
                                 replaced Pages variable with MenuLines, etc.
                                CurrentLine variable named StartLine.
                                Calls ShowScreenMenuItems() to produce menu, not
                                 ShowMenuItems().
                                CurrentPage variable not needed, uses TopLineIndex.
   2.29       01-05-98 BJB      Added support for remote terminal.
   2.30       01-12-98 BJB      Responds to ESTOP messages.
   2.31       01-27-98 BJB      Added code to format PS signal line of test screen.
                                Changed special chr 0x7e to 0x7F
   2.32       04-21-98 BJB      Calls simpler version of ShowMenuItems().
   2.33       06-12-98 BJB      Modified DoTestMode() to use
                                 ProcessControlMessage().
   2.34       08-19-98 BJB      Modified to use new screen, terminal modules.
   2.35       12-16-99 LAM      removed unused error handling code
   2.35.6.1   02-08-00 JZ       removed DVS, added Mask1, Cond1, Mask2, Cond2
   2.35.6.2   02-23-00 OFI      removed 'User experience level' from menu strucutures
   2.36       04-06-00 JZ       merged Lang to trunk
   2.37       05-26-00 SCM      Checked in for testing by Laura, John.
   2.38       06-28-00 BEKymer  Changed all MODEL to LEVEL
   2.39       08-15-00 At       Moved UpdateDiagScreen to this module, fixed diagnostics
   2.40       01-10-01 BEKymer  Added argument to TEXT function call
              03-28-01 BEKymer  Reordered test menu
   2.41       10-15-03 BEKymer  Modify UpdateDiagScreen() so it only sends a display 
                                update when something on the diagnostic screen actually
   2.39.1.1   06-16-03 JOY      Added new function 'QVGAExitTestSequence()', which
                                Exit the system from the TESTMODE.
                                Added 'QVGATestKeyMenu1' && 'QVGATestKeyMenu2'.
   2.39.1.2   08-14-03 JOY      #Tracker issue 3767 is solved, just ignore the
                                the 'TestKey', if we are already in Test Screen
                                in 'DoTestMode()'.  
   2.39.1.3   09-23-03 JOY      Moved Language String to the 'menutext.c'.
   2.39.1.4   10-12-03 JOY      Refresh time of Diag screen increased to 500ms.
   2.39.1.5   11-03-03 JOY      Refresh time of Diag screen reverted to 250ms.
   2.39.1.6   11-06-03 LAM      removed diagflag, it is not set when there is a touchscreen.
   2.39.1.8   11-14-03 LAM      added diagflag back, there was a build problem.
                                changes.
   2.42       12-04-03 BEKymer  Merged 2.39.1.8 & 2.41 to create 2.42 for
                                 Ver9.00b build
   2.43       12-09-03 BEKymer  Added missing external:
                                 extern const STR *const  QVGATestBuffer1[];
   2.44       08-24-04 JOY      Data type of variable 'QVGALatchPSStore' changed to UINT8.
   2.45       07-25-05 Bwadia   Test screen support for VGA in Ver10.0e                                  
   2.46       08-19-05 Bwadia   IsHWConfigured function used to check for VGA hardware 
                                presence 
   2.47       01-03-06 Bwadia   Diagnostics update freq on VGA changed to 500msec.
                                UpdateTestLine() Called only when VFD is present
                                Modified for tracker issue 3972
   2.48       10-22-07 NHAhmed  Changes done for LangTest phase 0
   2.49       09-02-08 NHAhmed  CleanUp for multi-language support.
   2.50       09-04-08 YGupta   CleanUp for LangTest Project.

*/

/*----------------------------- INCLUDE FILES ------------------------------*/

#include <string.h>
#include "portable.h"
#include "menu.h"
#include "param.h"
#include "preset.h"
#include "mansensr.h"
#include "keypad.h"
#include "led.h"
#include "beep.h"
#include "genrlmsg.h"
#include "getmsg.h"
#include "state.h"
#include "statedrv.h"
#include "opcodes.h"
#include "ck_qsend.h"
#include "display.h"
#include "selctkey.h"
#include "menutest.h"
#include "menu7a.h"

/*------------------------------ EXTERNAL DATA -----------------------------*/

extern SETUPS_Ver800 CurrentPreset;
extern CONFIGSETUP CurrentSetup;
extern SETUPS_Ver800 MaxLimit;
extern SETUPS_Ver800 MinLimit;

extern UINT16 LangIndex;
extern UINT8  MainKeyFlag;
extern UINT8  ExitMenuCounter;
extern SINT16 BlankMenuCounter;
extern UINT16 DiagFlag;

extern SINT16 MenuCounter;
extern UINT16 RadioMenuCounter;

extern SINT32 FMemoryBargraph;
extern SINT32 FMemoryBargraphMin;
extern SINT32 FMemoryBargraphMax;
extern SINT32 FActualBargraph;
extern SINT32 FActualBargraphMin;
extern SINT32 FActualBargraphMax;
extern SINT32 PowerTest;

extern SINT32 CurrentFreqIn;
extern SINT32 CurrentPower;
extern UINT32 WmgrQid;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern BOOLEAN VGARunSelected, VGAClearSelected, VGASeekSelected;
extern BOOLEAN VGAStoreSelected;
extern BOOLEAN LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;
extern INBITS Inp;

#define DIAGUPDATE 250
#define VGADIAGUPDATE 500

/*--------------------------- PRIVATE GLOBAL DATA --------------------------*/
/*                       (scope is global to THIS file)                     */

UINT8 QVGALatchPSStore = FALSE;
static SINT8 * TestBuffer1[LANGUAGE_MAX];    /* initialized to 0 by startup */

static MENUEND endlistT = { TRUE };
static MENUEND endlistTest1 = { TRUE };
static MENUEND endlistTest2 = { TRUE };

static GENERIC_MSG WeldMsgOut;

static SINT16 DiagCountDown = 20;
static SINT16 DiagCountDown2 = 20;
static SINT32 FMemoryLatch = 0, FActualLatch = 0;

STR TestPowerBufName[QVGA_LINESIZE];

STR *Str_TestPower[] =   { TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName,
                             TestPowerBufName };

STR TestFrequencyBufName[QVGA_LINESIZE];

STR *Str_TestFrequency[] =   { TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName,
                             TestFrequencyBufName };

/*--------------------------- EXTERN FUNCTION PROTOTYPES --------------------*/
void GetRunSelection (void);
void GetClearSelection (void);
void GetStoreSelection (void);
void GetSeekSelection (void);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/

/*---------------------------------- CODE ----------------------------------*/

void UpdateTestAmp(void)
{
   SetCurrentAmp(CurrentPreset.TestAmp);  /* Output new value right now!   */
}   

/****************************************************************************/


static char TestBuffers[9][21];



static void UpdateTestLine(void)
{
   if (LangIndex < ASIAN_LANGUAGE_START)  //If not Asian Language
   {
   TestBuffer1[LangIndex][2] = LatchPSRun ? '|' : 0x7F;
   TestBuffer1[LangIndex][8] = LatchPSSeek ? '|' : 0x7F;
   TestBuffer1[LangIndex][13] = LatchPSClear ? '|' : 0x7F;
   TestBuffer1[LangIndex][19] = LatchPSStore ? '|' : 0x7F;
   if(QVGALatchPSStore) TestBuffer1[LangIndex][19] = '|';
   }
   else
   {
      StrCpyTwoBytes(TestBuffer1[LangIndex], " ");
   }

}



void InitTestBuffers(void)
{
   int i;
   static STR * initvalues[] = {
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F",
                          "R=\x7F  Sk=\x7F  C=\x7F  St=\x7F"  };
   static STR testlinestorage[LANGUAGE_MAX][62];
   for (i = 0; i < LANGUAGE_MAX; i++)
      {
      TestBuffer1[i] = testlinestorage[i];
      strcpy(TestBuffer1[i], initvalues[i]);
      }
}



BOOLEAN DoTestMode( UINT8 *ExitKey, BOOLEAN *DidTest )
/****************************************************************************/
/*                                                                          */
/* This function implements Test Mode.  Returns TRUE if system should       */
/* jump to another menu due to a Run, Main, Print, or Setup keypress.       */
/* The key pressed will be returned in ExitKey.  If Test Mode terminated by */
/* GoBack, FALSE will be returned, and previous menu should be displayed.   */
/*                                                                          */
/* On exit, DidTest will be TRUE unless routine terminated immediately due  */
/* to welder not ready.                                                     */
/*                                                                          */
/****************************************************************************/
{
   UINT8    NewKey;
   UINT8    ExitFlag;

   SINT8    HmenuCounter = -1;

   UINT16   MenuLines;
   UINT16   SelectedItem;

   UINT16   StartLine;
   UINT16   TermStartLine;
   UINT16   SaveLine1[NUM_OUTPUT_DEVICES];
   UINT16   SaveSelectKey1;
   UINT16   SaveSingleSelect;

   MENU     local[MAXSUBMENUS];
   BOOLEAN  LevelChanged;/* Unfortunate kludge, see notes under Select1Key */
   BOOLEAN  RetVal;
   return(RetVal);
}



void QVGAExitTestSequence(void)
/***************************************************************************/
/*Description:                                                             */
/* Exit from the Test sequence.                                            */
/***************************************************************************/
{
  if (CurrentSequence == TESTMODE)    /* Still in test state */
  {
    WeldMsgOut.common.opcode = OP_STOP_TEST;
        CkQSend (WmgrQid,&WeldMsgOut,FRONT_PANEL_STATE_COORDINATOR,
        __LINE__,MILLS_TO_TICKS(50)); 
  }       
}



void UpdateDiagScreen(void){

   BOOLEAN Changed1 = FALSE;
   BOOLEAN Changed2 = FALSE;
   

   if ((Inp.PSRun == TRUE) && (LatchPSRun == FALSE)) {
      LatchPSRun = TRUE;
      Changed1 = TRUE;
   }   
   else if ((Inp.PSRun == FALSE) && (LatchPSRun == TRUE)) {
      if (--DiagCountDown <= 0) {
         LatchPSRun = FALSE;
         Changed2 = TRUE;
      }
   }

   if ((Inp.PSSeek == TRUE) && (LatchPSSeek == FALSE)) {
      LatchPSSeek = TRUE;
      Changed1 = TRUE;
   }
   else if ((Inp.PSSeek == FALSE) && (LatchPSSeek == TRUE)) {
      if (--DiagCountDown <= 0) {
         LatchPSSeek = FALSE;
         Changed2 = TRUE;
      }
   }
   
   if ((Inp.PSClear == TRUE) && (LatchPSClear == FALSE)) {
      LatchPSClear = TRUE;
      Changed1 = TRUE;
   }
   else if ((Inp.PSClear == FALSE) && (LatchPSClear == TRUE)) {
      if (--DiagCountDown <= 0) {
         LatchPSClear = FALSE;
         Changed2 = TRUE;
      }
   }
   
   if ((Inp.PSStore == TRUE) && (LatchPSStore == FALSE)) {
      Inp.PSStore = FALSE;
      LatchPSStore = TRUE;
      Changed1 = TRUE;
   }
   else if ((Inp.PSStore == FALSE) && (LatchPSStore == TRUE)) {
      if (--DiagCountDown <= 0) {
         LatchPSStore = FALSE;
         Changed2 = TRUE;
      }   
   }

/* Now need to check FMemoryBargraph and FActualBargraph for changes */

   if (--DiagCountDown2 <= 0) {
      if(CurrentSetup.VGAHWPresent)
         DiagCountDown2 = VGADIAGUPDATE;
      else
         DiagCountDown2 = DIAGUPDATE;
         
      if (FMemoryBargraph != FMemoryLatch) {
         FMemoryLatch = FMemoryBargraph;
         Changed1 = TRUE;
      }

      if (FActualBargraph != FActualLatch) {
         FActualLatch = FActualBargraph;
         Changed1 = TRUE;
      }
   }
   
   if (Changed1 == TRUE) {
      if(CurrentSetup.VGAHWPresent)
         DiagCountDown = VGADIAGUPDATE;
      else
      {   
         DiagCountDown = DIAGUPDATE;
         UpdateTestLine();
         SendFakeKeyPress(UPDATEDISPLAY);      /* Tell menu system to update */
      }   
   }
   else if (Changed2 == TRUE) {
      if (!CurrentSetup.VGAHWPresent)
      {
         UpdateTestLine();
         SendFakeKeyPress(UPDATEDISPLAY);      /* Tell menu system to update */
      }
   }
}

