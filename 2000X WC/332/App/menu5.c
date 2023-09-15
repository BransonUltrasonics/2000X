/* $Header:   D:/SWLab/VMdb/2000Series/App/MENU5.C_V   2.133.2.5   09 Sep 2008 20:39:58   nhahmed  $ */
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

   Filename: menu5.c

   This file will deal with the Calibrate and Diagnostic functions. 

                                   
 --------------------------------- REVISIONS --------------------------------

 Revision#   Date     Author   Description
 =========   ======== =======  =============================================
   0                           Initial Version
   1.00      04/29/96  PJ      Modified for PSOS version
   2.00      05/10/96  PJ      Uncommented DebuggingFlag
   3.00      05/14/96  PJ      Deleted menu5.h
                               Strings in menutext.c
   4.00      06/13/96  PJ      Enabled FActualDiag and
                               FMemoryDiag Menus
   5.00      06/28/96  LAM     added menu5.h for prototypes
   5.01      07/16/96  PJ      Deleted MESSAGESIZE from
                               strOff,StrOn, and StrBlank.
   6.00      07/28/96  LAM     added initsccalibration
   7.00      08-02-96  BEKymer Moved Force from Menucalb.c to here
   8.00      09-16-96  BEKymer Added stuff for Dry Cycle support
   9.00      09/24/96  LAM     deleted chg weldsequence from clearcaldist.
  10.00      10/03/96  LAM     chged calibration screens.
  11.00      10/10/96  PhilJ   changed menus to type const.
  12.00      10/27/96  PhilJ   Deleted function SetFreqActualFlag.
  13.00      11/03/96  LAM     deleted unused strings     
  13.10      12/13/96  PhilJ   Disabled Run Dry Cycle submenu.     
  13.20      12/17/96  PhilJ   Changed FMemoryDiag menu to read only.
  13.30      01/17/97  PhilJ   ReEnabled Run Dry Cycle submenu.     
  13.40      01/27/97  PhilJ   Disabled Run Dry Cycle submenu AGAIN.     
  14.00      04/21/97  LAM     added max bargraph = 12
  15.00      05/08/97  LAM     added center frequency to menu
  15.2.33    06/11/97  LAM     removed cal standards from menu
  16.2.34    07/24/97  LAM     added cal standards from menu
  16.2.35    07/24/97  LAM     added cal power only on model4,
  16.2.36    08/04/97  PhilJ   added DigitalTune menus
  17.2.37    08/14/97  LAM     fixed centerpot lockup 
  2.38       08/21/97  LAM     do not update digout when selcting factual
  2.39       09/02/97  LAM     selected factual will now beep            
  2.40       09.04.97  JBerman All ADVANCED changed to NORMAL
  2.41       09.09.97  LAM     unit version cleanup           
  2.42       10.06.97  LAM     chged digpot screens
  2.43       10.13.97  LAM     made submenu for center frequency, fixed
                               digpot warning message
  2.44       10.27.97  LAM     moved diagflag from menu0, disable when chging digpot
  2.45       10.28.97  LAM     clear diagflag when doing a cold start
  2.46       11.03.97  LAM     made centerfreq a warning only         
  2.47       11.05.97  LAM     added please wait to centerfreq
  2.48       11.11.97  LAM     fixed digpot off does not apply digpot
  2.49       11.13.97  LAM     cannot hit palmbuttons when centering freq or
                               changing digpot
  2.50       11.17.97  LAM     fixed toggling digpot off and on
  2.51       11.20.97  LAM     added digpot mask                
  2.52       12.02.97  LAM     fixed bitmask for digpot
  2.53       12.10.97  LAM     moved digpotflag          
  2.54       12.23.97  LAM     temporarily remove cal standards     
  2.55       12.23.97  LAM     put back cal standards     
  2.56       01.23.97  LAM     temporarily remove cal standards
  2.57       01.22.98  BJB     Added some ClrVFLines() calls in SetCenterFreq()
  2.58       01.27.98  LAM     removed center frequency
  2.59       01.27.98  BJB     SetDiagFlag() clears signal latch variables used
                                to create diagnostic screen.
  2.60       01.28.97  LAM     made cal standards model5,chged EP to AEF & AED
  2.61       03.09.98  BJB     Changed security level of submenuDiagnostics,
                                now available from Main Menu.
                               Removed Diagnostics from Calibration menu.
  2.62       04.28.98  LAM     added cal actuator menus
  2.63       05.22.98  LAM     made cal actuator menus aed | aef
  2.64       06.03.98  LAM     moved where scfinalcleanup is called when aborting
                               calibration
  2.65       06.03.98  BJB     Rewrote code for Digital Pot entry screen,
                                changed appearance of screen to allow direct
                                frequency entry with a note to press Test.
                               Deleted ClearDiagFlag() call from
                                EnableColdStart(), DisplayMenu() should do this.
  2.66       06.12.98  LAM     added manual spring rate calibration mode          
  2.67       06-16-98  BEKymer Change security to MAINTAINENCE for SUBMENU
                               submenuCalACtuator
  2.68       06-18-98  BJB     Modified EnableColdStart() so it will do cold
                                start only when system isn't welding.
                               Must fake ReadyFlag to TRUE after state
                                machine stopped.
  2.69       06-25-98  LAM     added array for calibration                     
  2.70       07-01-98  LAM     chged calibration str                     
  2.71       07-02-98  LAM     added initmanualscmenus
  2.72       07-21-98  LAM     donot put sequence in until submenu is selected
  2.73       08-19-98  BJB     Modified DigPotOffConfirm(),
                                DigitalTuneEntryScreen() for new screen, terminal
                                modules.
  2.74       08-28-98  BJB     After change to SetCurrentItems(), must clear
                                screen explicitly in DigPotOffConfirm().
  2.75       09-02-98  BJB     Changes to digital tune screens to implement
                                spec rev 2.6.
  2.76       09-28-98  BJB     Clears Inp.PSStore on entry to Diagnostics screen
                                so no "blip" left over from last cycle.
  2.77       10-01-98  PaulG   Added a check for the status of the printer buffer
                                in the function EnableColdStart().
  2.78       10-21-98  LAM     made calibration screens basic feature             
  2.79       11-02-98  LAM     changed cal standards to cal full system
  2.80       11-13-98  BJB     Added 15, 30 KHz cases to DigPotStore(),
                                DigitalPotEntry().
                               Modified DigitalPotEntry(), DigPotStore() to use
                                new range for CurrentSetup.DigPot (+-3000).
  2.81       04-26-99  OFI     Changed for Diab  
  2.82       04/30/99  LAM     fixed compiler error 
  2.83       06-10-99  CMC     Added Menu3AEF (twice) plus calls to each
  2.84       06-16-99  LAM     added jump to start switch screen, fixed inline asm
  2.84.2.1   07-10-99  JHenry  Changed TEXT structure textSeeManualSection1 to be
                                AED-specific
  2.84.2.2   07-20-99  JLH     Updates made during calibration debugging; debugging not
                                complete.
  2.84.2.3   07-20-99  LAM      fixed DIAB assembler call, added SCInit & ManualSCInit to 
                                the AEF menus.
  2.86       08-03-99  JZ       added ErrorCodeInfo to Cal Actuator Screen
  2.87       12-20-99  JZ       fixed backward compatibility
  2.87.6.1   02-07-00  JZ       removed DVS, added Mask1, Cond1, Mask2, Cond2
  2.87.6.2   02-23-00  OFI      removed 'User experience level' from menu strucutures and fixed
                                BASIC to PALMBUTTONS because this place used different enum.
  2.87.6.3   04-06-00  SCM      Added menu structures for Diagnostics menu.Work still in
                                progress.
  2.88       04-07-00  JZ       merged Lang to trunk     
  2.89       04-14-00  SCM      Changed the Freq variables in the Horn Scan menu 
                                to type FREQUENCY.
  2.90       04-19-00  SCM      Converted tabs to spaces.
  2.91       05-26-00  SCM      Checked in for testing by Laura, John.
  2.92       06-09-00  LAM      replaced dcycleblank with strblankline
  2.93       06-12-00  LAM      added DUPS mask
  2.94       06-14-00  SCM      Replaced array index-20 with 'define' LINESIZE.
  2.95       06-15-00  SCM      Changed the Mask2 and Cond2 definition in submenuDiagnostics
                                structure. 
  2.96       06-28-00 BEKymer  Changed all MODEL to LEVEL
  2.97       08-02-00  SRP     DUPS_StartHornScan added in StartScan struct.
  2.98       08-04-00  SRP     &HornScanInfo.ResonanceFreqs[n] added in Variable Freqn.
  2.99       08-09-00  JLH     Changed PrintScanGraph menu to point to HornScanFunc (in menu4.c).
  2.100      08-16-00  AT       Cold start and horn scan menu titles left-aligned.
  2.101      08-16-00  LAM      temporarily removed DEPOT flags.
  2.102      08-28-00  LAM      renabled DEPOT flags.
  2.103      09-29-00  LAM      added function DisableCalActKey inorder to keep the menus
                                from advancing before trigger Issue(3594)
  2.104      10-04-00  LAM      added functions requesthornscan and enablewelding 
                                inorder allow horn scan when not welding Issue(3597)
  2.105      10-05-00  LAM      changed where calling enablewelding 
  2.106      10-05-00  LAM      changed when calling requesthornscan 
  2.107      04-03-02  BEKymer  Added code for debug entry in menu
  2.108      04-04-02  BEKymer  Fix bugs in DebugReadMemory
  2.106.2.2  04-08-02  BEKymer  Added PSVersion to debug quick list
  2.106.2.3  04-09-02  BEKymer  Added Pressure table to debug quick list
  2.106.2.4  04-17-02  BEKymer  Added menu for size choice for debug output
                                 Restricted base to hex and decimal
  2.106.2.5  05-06-02  BEKymer  Add default loadcell table to debug quick list                             
  2.106.2.6  05-09-02  BEKymer  Add FailFlag to debug quick list                             
  2.106.2.7  05-09-02  BEKymer  Add FailTraceFlag instead of FailFlag to debug quick list                             
  2.106.2.7.1 01-14-03 DJL      Added IoTestData function in order to change DigPotValue
  2.109      04-11-03  BEKymer  Move 2.106.2.7.1.0 to tip as version 2.109 for 8.10 build
  2.110      05-09-03  BEKymer  Add P/S Failure code to debug quick list
  2.106.2.7.2.1 07-03-03 JOY    Static Variables 'DigPotValue','OrigDigPotFlag','OrigDigPotValue'
                                made Global, these variables accessed in 'QVGADiagnostics.c' file.
                                Function 'DigitalFreqEntry()' made global.
  2.106.2.7.2.2 07-21-03  JOY   'CalMenus[]' populated with QVGA Calib menus for  
                                 calibration synchronization, in 'InitSCMenus()' & 'InitManuelSCMenus()'.  
  2.111      07-25-03  LAM      merged TS01 with 8.10   
  2.112      07-29-03  JOY      Function 'DigitalFreqEntry()' made global.
  2.113      10-21-03  JOY      Added 'QVGAsubmenuDiagnostics'.
  2.114      11-12-03  BEKymer  Add P/S Failure code to debug quick list
                                Add argument to menu structures where needed
  2.115      12-03-03  BEKymer  Merged 2.114 & 2.110.1.1 to create 2.115 for
                                 build9.00b
  2.116      12-09-03  BEKymer  Add argument to const SUBMENU QVGAsubmenuDiagnostics                               
  2.117      12-11-03  BEKymer  Change XXCANTCHANGEXX to DEBUGGER in Debug structure
  2.118      02-12-04  BEKYmer  Add Testing and Specials menu to Diagnostic menu
                                 proper secret code is entered.
  2.119      03-18-04  SCM      Fixed Debug variable lockup.
  2.120      04-06-04  VSharma  Changed Resonance Frequency structures(FreqX).
                                Added UpdateResonanceStr().                               
  2.121      05-17-04  VSharma  Moved function prototype to 'menu5.h'.                               
  2.122      05-20-04  BEKymer  Add AlarmHornWeight to debug quicklist
  2.123      07-08-04  BEKymer  Remove calls to start/stop state
                                 machine for DoColdStart because
                                 DoColdStart does it now.
  2.124      07-27-04  JOY      Added FREQ60KHZ in DigitalPotEntry() & DigPotStore().
  2.125      08-24-04  JOY      Data type of variable 'QVGALatchPSStore' changed to UINT8.
  2.126      04-27-05  LAM      removed verify distance and dry cycle
  2.127      07-25-05  Bwadia   Added support for Horn Scan Frequencies in Asian Language
                                Asian LAnguage Support for VGA debug Secret menu 
  2.128      08-19-05  Bwadia   IsHWConfigured function used to check for VGA
                                hardware presence
  2.129      01-03-06  Bwadia   Diagnostics enabled for VGA. Modified for tracker issue 3972
  2.130      01-12-06  Bwadia   Added VGAExit button 
  2.131      08-27-06  LAM      added force table to debug table
  2.132      22-12-06  NHAhmed  Added pop up before entering the Sensor Cal Screen.
  2.133      01-31-07  NHAhmed  Changes related to Changed Structure variables of CHOICE and TOGGLE.
  2.134      10-22-07  NHAhmed  Changes done for LangTest phase 0
  2.135      04-14-08  NHAhmed  Replicated functions QVGASetDiagFlag(),DisableCalActKey() and 
                                UpdateFrequencyResonanceStr().
  2.136      08-26-08  NHAhmed  Added a function ChangeBaseAndWordLength() and modified function 
                                DebugReadMemory(). 
  2.137      09-02-08  NHAhmed  CleanUp for multi-language support.    
  2.138      09-04-08  YGupta   CleanUp for LangTest Project.
  2.139      09-09-08  NHAhmed  CleanUp for multi-language support.    




/*--------------------------- INCLUDE FILES --------------------------------*/

#include <psos.h>
#include "string.h"
#include "ticks.h"
#include "selctkey.h"
#include "menu5.h"
#include "digout.h"
#include "preset.h"
#include "sc.h"
#include "weld_obj.h"
#include "spidd.h"
#include "statedrv.h"
#include "fpk_task.h"
#include "beep.h"
#include "getmsg.h"
#include "util.h"
#include "led.h"
#include "menu.h"
#include "menutest.h"
#include "dups_api.h"
#include "snsrcalb.h"
#include "actnvram.h"
#include "qvgamenu.h"
#include "command.h"


/*----------------------------- LOCAL_DEFINES ------------------------------*/

#define MAXDIGITALFREQ 50
#define MINDIGITALFREQ -50
#define DIGITALFREQINC 1
#define START_OF_RAM  0x100000       /* Beginning of RAM               */
#define END_OF_RAM    0x13FFFF-16    /* 16 bytes from end of RAM       */
                                     /* because debug reads 16 at once */
                                     

/*---------------------------------- GLOBAL DATA ---------------------------*/
/*                          (scope is global to ALL files)                  */




STR    DebugTitle[QVGA_LINESIZE];
STR    DebugText1[QVGA_LINESIZE];
STR    DebugText2[QVGA_LINESIZE];
STR    DebugText3[QVGA_LINESIZE];
STR    DebugText4[QVGA_LINESIZE];


STR  *DebugTitleMsg[] = { DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle,
                          DebugTitle };

STR  *DebugText1Msg[] = { DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1,
                          DebugText1 };

STR  *DebugText2Msg[] = { DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2,
                          DebugText2 };

STR  *DebugText3Msg[] = { DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3,
                          DebugText3 };

STR  *DebugText4Msg[] = { DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4,
                          DebugText4 };



BOOLEAN VGADebugDataFlag = FALSE;
UINT16 DryCycleFlag = FALSE;
UINT16 DiagFlag = FALSE;
UINT16 DebugPasswordFlag = FALSE;
BOOLEAN DebugBase;
BOOLEAN DebugBytes;

SINT32 FMemoryBargraph = 6;
SINT32 FMemoryBargraphMin = 0;
SINT32 FMemoryBargraphMax = 12;
SINT32 FActualBargraph = 6;
SINT32 FActualBargraphMin = 0;
SINT32 FActualBargraphMax = 12;

MENUEND endlist5 = { TRUE };

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

UINT16 OrigDigPotFlag;        /* Initial DigPot On/Off state */
SINT32 OrigDigPotValue;       /* Initial DigPot value before editing */
SINT32 DigPotValue;           /* This is what user edits */
SINT32 MinDigPotValue;        /* Min value allowed in editing */
SINT32 MaxDigPotValue;        /* Max value allowed in editing */
BOOLEAN HSNotStarted = TRUE;
UINT8 FreqType[DUPS_NUMRESONANCES];
UINT16 BinEnable,HexEnable;
UINT32 TempDebugPtr;
/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/

BOOLEAN DigitalFreqEntry(void);
void UpdateDigitalFreq(void);
void VGACheckDigitalTune(void);
void LangStrCpy(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);

/*---------------------------- EXTERNAL DATA -------------------------------*/
extern UINT32 NackError, ErrorResponseMinLimit, ErrorResponseMaxLimit;
extern SETUPS_Ver800 CurrentPreset;
extern struct act_nvr NVR;
extern CONFIGSETUP CurrentSetup;
extern INBITS Inp;


extern UINT16 TestingMenuFlag;
extern UINT16 SpecialMenuFlag;
extern UINT16 ResonanceFreqEnable[];
extern QVGA_MENU_INFO MenuLevelInfo[];
extern BOOLEAN QVGAHwAvail;
extern REDRAW_SEG RedrawSeg;

extern SINT32  ForceGaugeReading1;
extern UINT16  OneMilTimer;
extern SINT16  MenuCounter;
extern UINT8   MainKeyFlag;
extern SINT16  BlankMenuCounter;
extern BOOLEAN DigPotKey;

extern BOOLEAN LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;
extern BOOLEAN ReadyFlag, PlsWaitTimerFlag;
extern BOOLEAN QVGACalAllowed;

extern enum WELDSTATES WeldState;
extern UINT16 MenuPointer;
extern BOOLEAN IsThereDataPrinting;
extern BOOLEAN PSFailCode;
                         


/* Stuff for the special debug feature */

extern UINT16 ADPressure;
extern UINT16 ADForce;
extern SINT16 FailTrace, AlarmHornWeight;
extern SINT16 LastFailTrace;
extern UINT8  QVGALatchPSStore;

const SINT32 DebugLowValue =  0;            /* Start of quick list */
const SINT32 DebugHighValue = 0x16FFF8-16;  /* End of BBR -16      */

SINT32 DebugPtr;
STR    DebugAddr[]           = "Addr:         ";
STR    Debug00[]             = "00:                 ";
STR    Debug04[]             = "04:                 ";
STR    Debug08[]             = "08:                 ";
STR    Debug0A[]             = "0A:                 ";
STR    Debug10[]             = "10:                 ";
STR    Debug18[]             = "18:                 ";
STR    ActIdText[]           = "Act ID      ";   
STR    SerNumText[]          = "Act S/N     ";   
STR    DefSerNumText[]       = "Def act S/N ";
STR    LoadCellText[]        = "Loadcell Tbl"; 
STR    DefLoadCellText[]     = "Def L/C Tbl "; 
STR    LevelText[]           = "Cntrl Level ";    
STR    ADPressText[]         = "AD Press.   ";    
STR    ADForceText[]         = "AD Force    ";    
STR    SpringRateText[]      = "Springrate  ";    
STR    PSVerText[]           = "Cal: PS ver ";    
STR    PressureText[]        = "Pressure Tbl";    
STR    FailTraceText[]       = "Fail Code   ";    
STR    PSFailText[]          = "PSFail EVRS ";    
STR    LastFailTraceText[]   = "NotReadyCode";    
STR    HWFailText[]          = "Horn Weight ";    
STR    ForceText[]           = "Force Tbl   ";  

typedef struct DebugList {
   void      *MemPtr;       /* Pointer to memory locations          */
   STR       *TextPtr;      /* Pointer to descriptive text          */
   UINT16    Base;          /* Default number base                  */
   UINT16    Size;          /* Default word (TRUE) or long (FALSE)  */
   } DEBUGLIST;
   
#define MAX_LIST_ENTRIES   16   /* Arbitrary limit, can be any practical size */
#define HEX      1
#define DECIMAL  2
#define BINARY   3
#define BASE10  0

DEBUGLIST   QuickList[MAX_LIST_ENTRIES] = {
/* Address                          Text               Base     Size    */
/* -----------------------------    -------------      -------  -----   */
   &NVR.ActId,                      ActIdText,         DECIMAL, TRUE,     /* Quick List Entry 0  */
   &NVR.SerNum,                     SerNumText,        HEX,     TRUE,     /* Quick List Entry 1  */
   &NVR.DefSerNum,                  DefSerNumText,     HEX,     TRUE,     /* Quick List Entry 2  */
   &NVR.LoadCell,                   LoadCellText,      DECIMAL, TRUE,     /* Quick List Entry 3  */
   &CurrentSetup.ControlLevel,      LevelText,         HEX,     TRUE,     /* Quick List Entry 4  */
   &ADPressure,                     ADPressText,       DECIMAL, TRUE,     /* Quick List Entry 5  */
   &ADForce,                        ADForceText,       DECIMAL, TRUE,     /* Quick List Entry 6  */
   &CurrentSetup.SpringRateTable,   SpringRateText,    DECIMAL, TRUE,     /* Quick List Entry 7  */
   &NVR.PSVersion,                  PSVerText,         DECIMAL, TRUE,     /* Quick List Entry 8  */
   &NVR.Pressure,                   PressureText,      DECIMAL, TRUE,     /* Quick List Entry 9  */
   &NVR.DefLoadCell,                DefLoadCellText,   DECIMAL, TRUE,     /* Quick List Entry 10 */
   &LastFailTrace,                  LastFailTraceText, DECIMAL, TRUE,     /* Quick List Entry 11 */
   &FailTrace,                      FailTraceText,     DECIMAL, TRUE,     /* Quick List Entry 12 */
   &PSFailCode,                     PSFailText,        BINARY,  TRUE,     /* Quick List Entry 13 */
   &AlarmHornWeight,                HWFailText,        DECIMAL, TRUE,     /* Quick List Entry 14 */
   &NVR.Force,                      ForceText,         DECIMAL, TRUE  };  /* Quick List Entry 14 */


/*-------------------------------- CODE ------------------------------------*/



void CloseCalibration(void)
/*************************************************************************/
/*                                                                       */
/* Note that this routine is *NOT* global.                               */
/*                                                                       */
/*************************************************************************/
{
   PlsWaitTimerFlag = FALSE;
}





static void QVGASetDiagFlag(UINT32 MenuExtra)
{
   DiagFlag = TRUE;
   LatchPSRun = LatchPSSeek = LatchPSClear = LatchPSStore = FALSE;
   Inp.PSStore = FALSE;  /* Clear here, set by ISR */
   QVGALatchPSStore = FALSE;
   UpdateDigitalFreq();
}

void SetDiagFlag(void)
{
   DiagFlag = TRUE;
   LatchPSRun = LatchPSSeek = LatchPSClear = LatchPSStore = FALSE;
   Inp.PSStore = FALSE;  /* Clear here, set by ISR */
   QVGALatchPSStore = FALSE;
   UpdateDigitalFreq();
}



void DisableCalActKey1(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is used to disable the menus to the actuator calibration   */
/* sequence when waiting for an event from the state machine.               */
/*                                                                          */
/****************************************************************************/ 
{
   UpdateKeyMask(DISABLESEL3);
}

void EnableWelding(void)
/****************************************************************************/
/*                                                                          */
/* This function is called from the menu when the Horn Scan submenu is      */
/* removed.                                                                 */
/*                                                                          */
/****************************************************************************/
{
   if(HSNotStarted == FALSE){
      HSNotStarted = TRUE;
      ResetStateMachine();
      StartStateMachine();
      SetReady();
      DUPSOkFlag = TRUE; 
      UpdateKeyMask(WELDMODEMASK); 
   }      
}



void WaitDigPotPosition(void)
/****************************************************************************/
/*                                                                          */
/* Puts up a message that says "Please Wait" and waits for the digital pot  */
/* to reach its final position.                                             */
/*                                                                          */
/****************************************************************************/
{
   while (DigPotKey);
}



BOOLEAN DigitalPotEntry(void)
/****************************************************************************/
/*                                                                          */
/* Tests for READY state before entering Digital Pot adjustment screen.  If */
/* system is READY, turns off state machine to make sure it stays that way, */
/* returns TRUE.  If not ready, returns FALSE. Also sets up the following:  */
/*                                                                          */
/*    OrigDigPotFlag - Zero if Digital Tune was off when selected           */
/*    DigPotValue - Current pot position. This is what user will edit       */
/*    OrigDigPotValue - Pot position when Digital Tune selected             */
/*                                                                          */
/****************************************************************************/
{
   UINT16  old_mode;
   SINT32  CurrentDigPotPos;
   UINT32  FreqAtCenter;
   BOOLEAN DoDigPot;

   /* Must disable interrupts here or system could go to "not ready" */
   /* between test of ready flag and shutdown of state machine. */

   asm (" move.w sr,d0\n ori.w #$700,sr\n move.w d0,_old_mode" );


   if (!GetReadyStatus())
      DoDigPot = FALSE;

   else
   {
      StopStateMachine();
      DoDigPot = TRUE;
      ReadyFlag = TRUE;   /* Kludge: System needs to "think" it is READY */
                          /* (or it won't run Test, etc) although hardware */
                          /* output should say it isn't. */

      OrigDigPotFlag = CurrentSetup.DigPotFlag & BIT0;

      if (OrigDigPotFlag)                        /* If not in use now, orig */
         CurrentDigPotPos = CurrentSetup.DigPot; /* position is "centered" */
      else
         CurrentDigPotPos = 0;

      /* Compute here the current start frequency and min/max range. */
      /* Range of values for CurrentSetup.DigPot is the same for all */
      /* power supplies to make use easier, but this means that here */
      /* we need to check power supply type to determine frequency.  */

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
      OrigDigPotValue = DigPotValue;
   }

   asm( " move.w _old_mode,d0\n move.w d0,sr" );

   return( DoDigPot );
}



UINT8 DigPotPressTest(void)
/****************************************************************************/
/*                                                                          */
/* Implements the screen that forces the user to press Test after changing  */
/* the position of the digital pot.                                         */
/*                                                                          */
/* Return: Key used to exit Test screen (GoBack, Main, Run, etc). If ESTOP  */
/*         caused exit from "Press Test To Confirm" screen, then return     */
/*         value will be zero.                                              */
/*                                                                          */
/****************************************************************************/
{
   UINT8    NewKey;
   UINT8    ExitFlag;

   UINT16   SaveLine1[NUM_OUTPUT_DEVICES];
   UINT16   SaveSelectKey1;
   UINT16   SaveSingleSelect;

   BOOLEAN   DidTest;
   UINT8     ExitKey;
   BOOLEAN   JumpMenu;
   BOOLEAN  EstopHappened;          /* Need this to escape screen on ESTOP */

   EstopHappened = FALSE;

   MenuCounter++;

   SaveLine1[VF_DEVICE] = 1;
   SaveLine1[TERM_DEVICE] = 1;

   SaveSelectKey1 = 1;
   SaveSingleSelect = 1;

   UpdateLED(OFFLED, OFF);

   ExitFlag = FALSE;

   while (ExitFlag != TRUE)
   {
      NewKey = GetMsg(TRUE);

      switch(NewKey)
      {
         case TestKey:
            JumpMenu = DoTestMode( &ExitKey, &DidTest );

            ExitFlag = TRUE;                 /* Always exiting */

            if (!JumpMenu)             /* Fill in key for this case */
               ExitKey = GoBackKey;

            break;

         case ResetKey:
            break;         /* Should never happen */

         case ESTOPMSGON:
            ShowEstopMessageOn();
            EstopHappened = TRUE;
            break;

         case ESTOPMSGOFF:
            ShowEstopMessageOff();
            EstopHappened = TRUE;
            break;

            /* If ESTOP pushed & released, UPDATEDISPLAY will be sent */
            /* here, use this as cue to get out. */

         case UPDATEDISPLAY:
            if (EstopHappened)
            {
               ExitFlag = TRUE;
               ExitKey = 0;
            }
            break;

         default:
            if (NewKey > FIRSTCONTROLMESSAGE)  /* Try to process */
               ProcessControlMessage( NewKey );
            else
               Beep(ERRORBEEP);  /* Inappropriate keypress, beep */
            break;

      }
   }
   MenuCounter--;
   return( ExitKey );
}



void DigitalPotChoiceDone(void)
/****************************************************************************/
/*                                                                          */
/* This function is called after the user has selected On or Off for        */
/* Digital Tune (or may have opted to leave original value via GoBack).  If */
/* user turned Digital Tune On, submenu has already been displayed at this  */
/* point, and it took care of turning the state machine back on.  This      */
/* function needs to take action only if current setting is Off.  If it was */
/* originally Off, just restart state machine.  If it was originally On,    */
/* user will be forced to press the Test key.                               */
/*                                                                          */
/* One exception: May have been On, user selected & hit GoBack.  In this    */
/* case, setting is On but submenu wasn't displayed.  Here just re-enable   */
/* state machine.                                                           */
/*                                                                          */
/****************************************************************************/
{
   UINT8   ExitKey;
   UINT32  FreqAtCenter;

   FreqAtCenter = GetPowerSupplyFrequency();

   if (!(CurrentSetup.DigPotFlag & BIT0))  /* If now Off ... */
   {
      /* If was originally On and digpot position changed, make */
      /* user push Test key */

      if (OrigDigPotFlag && (FreqAtCenter != OrigDigPotValue))
      {
         CenterDigPot();
         WaitDigPotPosition();   /* Wait for pot to center */
         CurrentSetup.DigPot = 0;
         UpdateCurrentPreset( DIGITALFREQ, CurrentSetup.DigPot, TRUE );

         ExitKey = DigPotPressTest();  /* Make 'em press Test */

         if (ExitKey && (ExitKey != GoBackKey))
         {
            MainKeyFlag = TRUE;  /* Causes return to Main Menu */

            if (ExitKey != MainKey)  /* From there, go to right place */
            {
               SendFakeKeyPress( ExitKey );
               BlankMenuCounter = 1;      /* Block display of Main Menu */
            }
         }
      }
      else     /* No change, just allow welding & go */
      {
         ResetStateMachine();
         StartStateMachine();
      }
   }
   else if (!CheckStateMachine())
   {
      ResetStateMachine();   /* Covers On + GoBack case and anything */
      StartStateMachine();   /* else we haven't thought of. */
   }
}



BOOLEAN DigitalFreqEntry(void)
/****************************************************************************/
/*                                                                          */
/* This function is called before the user can select the Start Frequency   */
/* item on the Digital Tune entry screen.  It makes sure system is in READY */
/* before item can be selected, then stops state machine.                   */
/*                                                                          */
/****************************************************************************/
{
   UINT16  old_mode;
   BOOLEAN AllowSelect;

   /* Must disable interrupts here or system could go to "not ready" */
   /* between test of ready flag and shutdown of state machine. */

   asm (" move.w sr,d0\n ori.w #$700,sr\n move.w d0,_old_mode" );

   if (!GetReadyStatus())
      AllowSelect = FALSE;

   else
   {
      if (CheckStateMachine())   /* Will be running if user already */
      {                          /* tested first value, is now about to */
         StopStateMachine();     /* try another one. */
         ReadyFlag = TRUE;    /* Kludge, see comment at similar one above */
      }
      AllowSelect = TRUE;
   }

   asm( " move.w _old_mode,d0\n move.w d0,sr" );

   return( AllowSelect );
}


void DigPotStore(void)
/****************************************************************************/
/*                                                                          */
/* Converts Start Frequency entered by user back into digital pot position  */
/* for storage in the CurrentSetup.  Note that this function runs after     */
/* the call to UpdateCurrentPreset(), so DigitalFrequency had to have       */
/* ID of XXCANTCHANGE so that UpdateCurrentPreset() wouldn't be called and  */
/* passed the wrong value.  Here UpdateCurrentPreset() called directly.     */
/*                                                                          */
/****************************************************************************/
{
   SINT32 FreqAtCenter;

   FreqAtCenter = GetPowerSupplyFrequency();

   switch (CurrentSetup.PSFreq)
   {
      case FREQ20KHZ:
         CurrentSetup.DigPot = (DigPotValue - FreqAtCenter)*6;
         break;
      case FREQ15KHZ:
         CurrentSetup.DigPot = (DigPotValue - FreqAtCenter)*8;
         break;
      case FREQ30KHZ:
         CurrentSetup.DigPot = (DigPotValue - FreqAtCenter)*4;
         break;
      case FREQ60KHZ:
         CurrentSetup.DigPot = (DigPotValue - FreqAtCenter)*2;
         break;   
      case FREQ40KHZ:
      default:
         CurrentSetup.DigPot = (DigPotValue - FreqAtCenter)*3;
         break;
   }

   UpdateCurrentPreset( DIGITALFREQ, CurrentSetup.DigPot, TRUE );
}

void VarDigPotStore(void)
{
   DigPotStore();
   if (IsHWConfigured(VGA))
      VGACheckDigitalTune();
}




void DebugReadMemory(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will be called when a value has been entered in the Debug  */
/*  entry in the DIAG menu.  It will read memory from the location specified */
/*  and format it for display in the submenu which it will call.             */
/*                                                                           */
/*  The formated output for base 16 and 2 bytes will be:                     */
/*      DebugText1:   00:    xxxx     xxxx                                   */
/*      DebugText2:   04:    xxxx     xxxx                                   */
/*      DebugText3:   08:    xxxx     xxxx                                   */
/*      DebugText4:   0C:    xxxx     xxxx                                   */
/*                                                                           */
/*  where:  xx is a 2-digit hex value for each byte                          */
/*                                                                           */
/*****************************************************************************/
{
   UINT32 Value, *Ptr, Mask;
   UINT8  QuickListFlag = FALSE;
   UINT8  i, Offset, Shift, *Tmp;
   UINT8  Base, Width, LC, FirstByte;
   SINT8 TempStr[QVGA_LINESIZE];

   #define LOOP       2       /* Number of values/line         */
   #define SPACING    9       /* Max # of digits/value + space */

   TempDebugPtr = DebugPtr;
/* First validate entered range.  Only allow RAM and BBR-pSOS-RTC */

   if (DebugPtr < MAX_LIST_ENTRIES) {     /* Test for quick list entry */
      strcpy(DebugTitle, QuickList[DebugPtr].TextPtr);
      DebugBase = QuickList[DebugPtr].Base;
      DebugBytes = QuickList[DebugPtr].Size;
      DebugPtr = (SINT32)QuickList[DebugPtr].MemPtr;
      QuickListFlag = TRUE;
   }
   else
   /* Bring Debug pointer to the even address*/
   DebugPtr = DebugPtr - (DebugPtr%2);
   
   if(DebugBase == BINARY ){
      HexEnable = FALSE;
      BinEnable = TRUE;
   }
   else{
      HexEnable = TRUE;
      BinEnable = FALSE;
   }

   if (((DebugPtr >= START_OF_RAM) && (DebugPtr <= END_OF_RAM)) 
        || (DebugPtr >=BBR800_SYSTEM_START)) {

/* Create title line */
      if (QuickListFlag == FALSE) {
         strcpy(DebugTitle, DebugAddr);
         Numout((UINT32)DebugPtr, 16, '0', &DebugTitle[5], 6);  
      }
      
/* Now setup variables for either hex, decimal or binary */
      switch (DebugBase) {
         case HEX:
         default:
            LC = '0';                      /* display leading zeros */
            Base = 16;
            break;

         case DECIMAL:
            LC = ' ';                      /* no leading zeros displayed */
            Base = 10;
            break;
            
         case BINARY:
            LC = '0';                      /* leading zeros displayed */
            Base = 2;
            break;
            
      }  

      strcpy(DebugText1, Debug00);
      Ptr = (UINT32*)DebugPtr;

      switch (DebugBytes) {
         case TRUE:              /* 2 bytes */
         default:
            Mask = 0xffff0000;
            Shift = 16;
            if (DebugBase == HEX) Width = 4;       /* 4 digits/byte for Hex     */
            else if (DebugBase == BINARY) Width=8; /* 8 digits/byte for binary  */
            else Width = 5;                        /* 5 digits/byte for decimal */
            strcpy(DebugText2, Debug04);
            strcpy(DebugText3, Debug08);
            strcpy(DebugText4, Debug0A);
            break;
         
         case FALSE:             /* 4 bytes */
            Mask = 0xffffffff;
            Shift = 0;
            Width = 8;                          /* 8 digits per byte */
            strcpy(DebugText2, Debug08);
            strcpy(DebugText3, Debug10);
            strcpy(DebugText4, Debug18);
            break;
         
      }   
      FirstByte = 11 - Width;       /* Start first output here */
      Offset = FirstByte;           /* Handle line 1 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         Numout((UINT32)Value, Base, LC, &DebugText1[Offset], Width);
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
         Offset += SPACING;
      }
      
      Offset = FirstByte;           /* Handle line 2 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         Numout((UINT32)Value, Base, LC, &DebugText2[Offset], Width);
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
         Offset += SPACING;
      }
   
      Offset = FirstByte;           /* Handle line 3 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         Numout((UINT32)Value, Base, LC, &DebugText3[Offset], Width);
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
         Offset += SPACING;
      }
   
      Offset = FirstByte;           /* Handle line 4 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         Numout((UINT32)Value, Base, LC, &DebugText4[Offset], Width);
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
         Offset += SPACING;
      }
      strcpy(TempStr, DebugTitle);
      StrCpyTwoBytes(DebugTitle, TempStr);
      strcpy(TempStr, DebugText1);
      StrCpyTwoBytes(DebugText1, TempStr);
      strcpy(TempStr, DebugText2);
      StrCpyTwoBytes(DebugText2, TempStr);
      strcpy(TempStr, DebugText3);
      StrCpyTwoBytes(DebugText3, TempStr);
      strcpy(TempStr, DebugText4);
      StrCpyTwoBytes(DebugText4, TempStr);

      if(IsHWConfigured(VGA))
         VGADebugDataFlag = TRUE;
   }
   else {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = REFRESH_MENU;
      ErrorResponseMaxLimit = 0;

   }
}

void ChangeBaseAndWordLength(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will be called when a value of a memory loction has to     */
/*  dispaly in either hex or decimal and also word length either in four     */
/*  bytes or in eight bytes.                                                 */
/*                                                                           */
/*****************************************************************************/
{
   UINT32 Value, *Ptr, Mask;
   UINT8  i, Offset, Shift, *Tmp;
   UINT8  Base, Width, LC, FirstByte;
   SINT8 TempStr[QVGA_LINESIZE];

   if (((DebugPtr >= START_OF_RAM) && (DebugPtr <= END_OF_RAM)) 
        || (DebugPtr >=BBR800_SYSTEM_START)) {
      if(TempDebugPtr >= 0 && TempDebugPtr <= 15){ 
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
         ErrorResponseMaxLimit = 0;
      }
      else{
      /* Now setup variables for either hex, decimal or binary */
      switch (DebugBase) {
         case HEX:
         default:
            LC = '0';                      /* display leading zeros */
            Base = 16;
            break;

         case BASE10:
            LC = ' ';                      /* no leading zeros displayed */
            Base = 10;
            break;
            
         case BINARY:
            LC = '0';                      /* leading zeros displayed */
            Base = 2;
            break;
            
      }  

      strcpy(DebugText1, Debug00);
      Ptr = (UINT32*)DebugPtr;

      switch (DebugBytes) {
         case TRUE:              /* 2 bytes */
         default:
            Mask = 0xffff0000;
            Shift = 16;
            if (DebugBase == HEX) Width = 4;       /* 4 digits/byte for Hex     */
            else if (DebugBase == BINARY) Width=8; /* 8 digits/byte for binary  */
            else Width = 5;                        /* 5 digits/byte for decimal */
            strcpy(DebugText2, Debug04);
            strcpy(DebugText3, Debug08);
            strcpy(DebugText4, Debug0A);
            break;
         
         case FALSE:             /* 4 bytes */
            Mask = 0xffffffff;
            Shift = 0;
            Width = 8;                          /* 8 digits per byte */
            strcpy(DebugText2, Debug08);
            strcpy(DebugText3, Debug10);
            strcpy(DebugText4, Debug18);
            break;
         
      }   
      FirstByte = 11 - Width;       /* Start first output here */
      Offset = FirstByte;           /* Handle line 1 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         Numout((UINT32)Value, Base, LC, &DebugText1[Offset], Width);
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
         Offset += SPACING;
      }
      
      Offset = FirstByte;           /* Handle line 2 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         Numout((UINT32)Value, Base, LC, &DebugText2[Offset], Width);
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
         Offset += SPACING;
      }
   
      Offset = FirstByte;           /* Handle line 3 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         Numout((UINT32)Value, Base, LC, &DebugText3[Offset], Width);
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
         Offset += SPACING;
      }
   
      Offset = FirstByte;           /* Handle line 4 output here */
      for (i=0; i<LOOP; i++) {
         Value = *Ptr;              /* Always read 4 bytes         */
         Value = (Value & Mask);    /* Strip off what not needed   */
         Value = (Value >> Shift);  /* Shift what left for display */
         Numout((UINT32)Value, Base, LC, &DebugText4[Offset], Width);
         if (DebugBytes == TRUE) {
            Tmp = (UINT8 *)Ptr;
            Tmp += 2;
            Ptr = (UINT32 *)Tmp;
         }
         else Ptr++;
         Offset += SPACING;
      }
      strcpy(TempStr, DebugText1);
      StrCpyTwoBytes(DebugText1, TempStr);
      strcpy(TempStr, DebugText2);
      StrCpyTwoBytes(DebugText2, TempStr);
      strcpy(TempStr, DebugText3);
      StrCpyTwoBytes(DebugText3, TempStr);
      strcpy(TempStr, DebugText4);
      StrCpyTwoBytes(DebugText4, TempStr);
     }
   }
}


void IoTestData(UINT8 ExtraData){
   WaitDigPotPosition();
   DigPotValue= (UINT32)ExtraData;
}

void UpdateFrequencyResonance(void)
/*****************************************************************************/
/* This function will update the strings for resonance frequency depends on  */
/* the Series & Parallel type.                                               */
/*****************************************************************************/
{
   UINT16 i;
   for (i=0;i<DUPS_NUMRESONANCES;i++)
   {
      if(HornScanInfo.ResonanceFreqs[i] != 0)
      {
         ResonanceFreqEnable[i] = TRUE;/* Display the frequency variable on the screen. */
         if(HornScanInfo.ResonanceFreqType[i] == FREQ_SERIES )
         /* Display 'Series F(Hz) = XXXXX'*/
            FreqType[i] = 2;
         else if(HornScanInfo.ResonanceFreqType[i] == FREQ_PARALLEL )
         /* Display 'Parallel F(Hz) = XXXXX'*/
            FreqType[i] = 1;
         else if(HornScanInfo.ResonanceFreqType[i] == FREQ_NONE )
            FreqType[i] = 0;
      }
   }
}