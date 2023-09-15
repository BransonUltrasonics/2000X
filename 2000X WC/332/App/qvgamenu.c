/* $Header:   D:/SWLab/VMdb/2000Series/App/qvgamenu.c_v   1.73.1.14   25 Sep 2009 15:06:20   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 2009           */
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

        Filename: qvgamenu.c

      Written by: JOY MD 
            Date: 04/17/2003 
        Language: "C"

--------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========       ======      ===========
      1.0          04/17/03       SCM        Initial Version
      1.8          06/17/03       JOY        Added 'TEST_SCREEN'to the Screen types &
                                             Test Screen Processing added.
                                             Diagnostic Screen Processing added.
                                             Horn Scan Screen Processing added.
      1.9          07/15/03       JOY        STATUS_SCREEN is added.
                                             'Exit'Button in Radio Screen is replaced
                                             by 'Save' Button.                                             
      1.10         07/29/03       JOY        Added PresetNames submenu to the 'System Info'
                                             menu. this sub menu is poped up when 'next'button
                                             is pressed. 
      1.11         08/07/03       JOY        Added 'HORNDOWN_SCREEN'.
                                             Added 'ResetKey' Processing.
      1.12         08/25/03       JOY        Alarms/Estop processed in all Screens.
      1.13         09/06/03       JOY        Added System configuration and Print menus.
      1.14         09/16/03       JOY        Added 'Exit' Button in pop-up Screens.
                                             Button Stuck problem is solved.
      1.15         09/25/03       JOY        Added 'Exit' button in 'Act Settings' menu.
      1.16         09/27/03       JOY        Added 'RADIOLARGE_SCREEN'.
      1.17         09/30/03       JOY        system hang array overrun is solved.
      1.18         10/03/03       JOY        Added 'QVGAFreqOffsetSubmenu'.
      1.19         10/06/03       JOY        Preset Name is updated when Recalling 
                                             -External Preset.
      1.20         10/09/03       JOY        Added 'CALIBRATION_ABORTED' message.
      1.21         10/16/03       JOY        Bottom Button width is reduced by 2 pixels.
      1.22         10/23/03       JOY        Added Button Release Beep.
      1.23         10/29/03       JOY        Added 'CONFIRM_REPLACE_COLUMN' confirm screen.
      1.24         11/05/03       JOY        Touching 'Exit' button on additional info.
                                             -Alarm menu return to Prev. alarm screen
                                             -Tracker issue #3787. 
      1.25         11/26/03       JOY        ESTOP Message display is moved from VFD func
                                             -to Touch screen queue. 
      1.26         12/05/03       JOY        State Machines are stopped in the HornDown
                                             Alarm menus.
      1.27         12-09-03       BEKymer    Add argument to calls within SUBMENU's
      1.28         02-20-04       VSharma    Added UserIO, Custom, ViewSetup, QVGABransonDefaultMenu &
                                              QVGABransonFuncMenu.
                                             Modify CHOICE, TOGGLE & RADIOLARGE so XXCANTCHANGEXX won't
                                              allow changes.
                                             Modified ProcessConfirmScrn().
                                             Added POPUP_EXIT_BUTTON in ALARM_MENU_SCREEN.
      1.29         03-03-04       VSharma    Added QVGATestingMenu & QVGASpecialsMenu.
      1.30         03-29-04       LAM        merged with 8.21                                                   
      1.31         04-06-04       VSharma    Modified RefreshStatus().
                                             Added code to exit from the UserIOMenu on reset,
                                             when entered from alarm menu.  
      1.32         04-19-04       VSharma    Changed ExitUserIOMenu() to ExitMenuAndEnableWeld().
      1.33         05-03-04       VSharma    Added Next, Back button in RADIO_SCREEN. 
      1.34         05-17-04       VSharma    Removed extern declaration of unused strings. 
      1.35         06-17-04       VSharma    Refreshed complete screen when language is changed
                                             (case RADIO_SCREEN: in QVGADisplayMenu() ).
      1.36         06-29-04       BEKymer    For case CONFIRM_RESTORE_DEFAULTS
                                              call OkayToDefault instead of
                                              QVGARestoreDefaultsOK ();
      1.37         07-21-04       JOY        Graph Button just beeps if control level is Level_t.
      1.38         07-22-04       JOY        Removed Beep while changing weldMode, Ver9.0 MH issue #3814.
      1.39         07-23-04       JOY        Test Screen LED display is correctd MH issue #3863.
                                             Modified Radio item saving in case of multiple Radio screen
                                             MH issue #3874.
      1.40         07-28-04       JOY        Added Exit Button to the RADIO_SCREEN.
                                             Added Prev Button on Middle menu screens.
      1.41         08-25-04       JOY        Changed number of buttons displayed on MENU_SCREEN.
      1.42         08-27-04       JOY        Menu Items are equaly spaced.
      1.43         08-31-04       JOY        Main menu & printing menus are displayed with 5 rows.
      1.44         09-01-04       JOY        Modified ProcessMenuItem() _ALPHA type.
      1.45         09-02-04       JOY        Touch action disabled 'Refer to Manuel' item in PrinterSelectionMenu.
      1.46         09-09-04       JOY        Corrected Amp Step screen display.
      1.47         09-10-04       JOY        Corrected samepage logic in UpdateVariableValue().
      1.48         09-16-04       JOY        Units also displayed along with Cylinder diameter,
                                              Menu selection.
      1.49         05-23-05       Bwadia     Moved VGA menu related code from command.c
      1.50         07-25-05       Bwadia     Checked in for Ver 10.0e
      1.51         08-12-05       Bwadia     Added export weld data byte in polling response  
      1.52         08-19-05       Bwadia     Dummy check in. No change done 
      1.53         09-10-05       Bwadia     Print support for Ver10.0h 
      1.54         09-16-05       Bwadia     Added function 'StrCpyTwoToOneByte' 
      1.55         10-11-05       Bwadia     USB related sample and alarm parameters
                                             sent in 1027 host command
      1.56         10-24-05       Bwadia     PMC feature related functions added
      1.57         11-22-05       Bwadia     VGA HW present flag set and state
                                             machines started in reply to 1000 command
      1.58         12-07-05       Bwadia     Global Weld command counter sent instead
                                             of external preset counter. Modified for 
                                             Tracker issue 4026, 4030
      1.59         12-20-05       Bwadia     Sequence printing related print parameters added
                                             Modified for tracker issue 3976
      1.60         01-03-05       Bwadia     DiagFlag set to FALSE when exiting Diagnostics
                                             screen. Modified for tracker issue 3972
      1.61         01-11-06       Bwadia     ProcessPMCEnable() removed. Modified for
                                             tracker issue 4042
      1.62          01-12-06      Bwadia     Alarms string were not showing all text.
                                             Modified BuildMenus() for the same.  
      1.63         02-07-06       Bwadia     Modified VGAPrintGraphInfo() for gauge pressure
                                             when graph is printed. Modified for tracker issue 4066  
      1.64         02-08-06       Bwadia     Added USB global flag in VGAPrintParameters()
      1.65         03-31-06       Bwadia     Alpha item function executed in SetAlpha()
                                             Title string for radio screen related to DUPS preset
                                             selection made two bytes     
      1.66         04-13-06       Bwadia     PresetStatusMenuFlag used instead of menu pointer
                                             comparison for displaying TITLE for DUPS
                                             preset status 
      1.67         04-18-06       Bwadia     VGA flag initialized when FT59 is issued
                                             and the system is started in polling command    
      1.68         04-24-06       Bwadia     Horn scan statuses now sent in polling command
      1.69         12-22-06       NHAhmed    Made changes for DISTANCE3 format.
      1.70         01-03-06       NHAhmed    Changes made for Display Lock.
      1.71         01-23-06       NHAhmed    Added PresetStatusMenuFlag = FALSE, in ProcessSubMenuItem(),
                                             ProcessVGAButton() and ProcessBottomMenu() to display the title
                                             string correctly when exiting from DupsPresetMenu[].
      1.72         03-12-07       NHAhmed    Changes for Force/Amp Step, and Add to Average.
      1.73         05-04-07       NHAhmed    Modified SendPollingData to Send Printer Status(Tracker #4109).
      1.74         10-22-07       NHAhmed    Changes done for LangTest phase 0
      1.75         04-14-08       NHAhmed    Replicated functions with some modifications.
      1.76         06-06-08       NHAhmed    Added new function ProcessAlarmItems(). Modified function
                                             VGASendPollingData().
      1.77         08-01-08       NHAhmed    Renamed functions ProcessBottomMenu1() and VGAMoveToNextCalibMenu1()
                                             as BottomMenuProcess() and MoveToNextCalibMenu() respectively.
      1.78         08-26-08       NHAhmed    Modified functions VGASendPollingData() and MoveToNextCalibMenu().
      1.79         09-02-08       NHAhmed    CleanUp for multi-language support.
      1.80         09-04-08       YGupta     CleanUp for LangTest Project.
      1.81         09-09-08       NHAhmed    CleanUp for multi-language support.
      1.82         09-12-08       NHAhmed    Updated function SendMenuPtrs().
      1.83         10-01-08       NHAhmed    Merged Ver10.40 changes.
      1.84         10-06-08       NHAhmed    Updated function SendMenuPtrs().
      1.85         11-07-08       NHAhmed    Modified function VGASendPollingData() for control level or actuator 
                                             change check.
      1.73.1.12    09-10-09       BEkymer    Add new define MICRO where needed
		1.73.1.13    09-22-09       YGupta     Modified code for Horn down to exit only in case of Reset required alarms.
		1.73.1.14    09-25-09       YGupta     Added MICRO for Weld data info.
      
*/
     
/*
 -------------------------------- DESCRIPTION --------------------------------
*/


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include <psos.h>
#include <string.h>
//#include "getmsg.h"
#include "qvgamenu.h"
#include "drawscrn.h"
#include "dups_api.h"
#include "digout.h"
#include "menu.h"
#include "menu5.h"
#include "display.h"
//#include "ascii.h"
#include "opcodes.h"
#include "statedrv.h"
#include "selctkey.h"
#include "beep.h"
#include "param.h"
#include "touchmsg_qvga.h"
#include "qvga_task.h"
#include "qvga_uart.h"
#include "ticks.h"
#include "state.h"
#include "sc.h"
#include "snsrcalb.h"
#include "ipsatype.h"
#include "command.h"
#include "rtclock.h"
#include "util.h"
#include "graphs.h"
#include "prsetprn.h"
#include "preset.h"
#include "inports.h"
#include "alarms.h"
/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
#define  PSOS_TIMEOUT  0x01          /*Psos q_receive Time out Error*/
#define EXIT_HD        1   /* Causes exit from HD mode */
#define WELDCOLUMN_COUNT_3 3
#define WELDCOLUMN_COUNT_5 5
#define WELDCOLUMN_COUNT_6 6
#define WELDCOLUMN_COUNT_7 7
#define WELDCOLUMN_COUNT_8 8
#define WELDCOLUMN_COUNT_12 12
#define WELDCOLUMN_COUNT_13 13
#define WELDCOLUMN_COUNT_14 14
#define WELDCOLUMN_COUNT_15 15
#define WELDCOLUMN_COUNT_16 16
#define RTRIGFORCE 24
#define EQRECALIB_BIT 340
#define WARNINGALARM8_BIT 520

#define CM_NOT_REQ_RESET_EXCLUDE_CM1 (CM_NOT_REQ_RESET & 0xFFFFFFFD)
/*
 ------------------------------- GLOBAL DATA ---------------------------------
*/
/*                       (scope is global to ALL files)                     */

SCREEN_TYPE CurrentScrnType;         // Holds Currently Displayed Screen Type
REDRAW_SEG  RedrawSeg;               // Indicate which part of Screen has to be- 
                                     // Refreshed.
SCREEN_ALIGN DisplayAlign;           // How menu items are aligned in the particular 
                                     // Screen. LEFT_RIGHT_ALIGN, MIDDLE_ALIGN.
QVGA_MENU_INFO MenuLevelInfo[20];    // Holds particular Menu information.
//MENUITEM_PROPERTY MenuItemProp[20];  // Display information of Menu items.
BUTTON_STATE TouchedButtonState;     // Store currently touched Button co-ordinates.
BOOLEAN IsGraphDataAvail = FALSE;    // Is new Graph Data is available to display.

BOOLEAN LastWeld = FALSE;            // IS there any weld staus needs to be refreshed.
                                     // in RUN_RESULT_SCREEN. 
//BOOLEAN RefreshData = FALSE;         // IS there any weld states needs to be refreshed.
                                     // in RUN_RESULT_SCREEN.
BOOLEAN QVGAEstopDisplay = FALSE;
UINT16 DisplayNextMenu = TRUE;       // If FALSE Don't display Next Menu just beep only.
MENU * VGACalibPointer;
                                  
BOOLEAN NextMenuFlag = FALSE;
BOOLEAN  CSCompleteFlag = FALSE;
BOOLEAN ChkSumCompleteFlag = FALSE;
BOOLEAN StartCalibFlag=FALSE;
UINT16 ActType =0;


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern ESTOP_STATE EStopState;
extern UINT16 GlobalCommandID;
extern BOOLEAN CalActErrorFlag;
extern UINT8 CheckPrinterStatus;
extern SINT32 StoreCycleCount;
extern BOOLEAN LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;
extern BOOLEAN ForceDigitalTuneTest;
extern BOOLEAN QVGAPresetSaveAborted;
extern BOOLEAN HSNotStarted;
extern BOOLEAN StartwithRunMenu;
extern BOOLEAN QVGACalAllowed;
extern BOOLEAN QVGASnsrCalibAllowed;
extern BOOLEAN QVGAExitHDMenu;
extern BOOLEAN QVGAHDAlarm;
//extern BOOLEAN QVGARunScreenFlag;
//extern BOOLEAN IsAlarmActive;          /* Alarm Button is Displayed */
extern BOOLEAN PrintMsgDisplayed;      /* Print Messege Displayed */
extern BOOLEAN StateMachineDisabled;
extern BOOLEAN UserIOAlarmMenu;
extern BOOLEAN VGATestKeyPressed;
extern BOOLEAN VGAEstopOn;
extern BOOLEAN VGAEstopOff;
extern BOOLEAN VGAEstopReset;
extern BOOLEAN VGACalibKey;
extern BOOLEAN VGACalAborted;
extern BOOLEAN VGADebugDataFlag;
extern BOOLEAN DigPotKey;
extern BOOLEAN VGADigitalChoiceTestFlag;
extern BOOLEAN VGADigitalChoiceWaitFlag;
extern BOOLEAN VGAColdStartFlag;
extern BOOLEAN VGAColdStartErrorFlag;
extern BOOLEAN VGAActStartFlag;
extern BOOLEAN VGAActStartErrorFlag;
extern BOOLEAN  ForceDigitalTuneTest; /* TRUE if user must press Test to exit */
extern BOOLEAN VGARestoreColdStartFlag; 
extern BOOLEAN VGARestoreErrorFlag; 
extern BOOLEAN VGAOverwritePresetFlag;
extern BOOLEAN VGAOverwriteErrorFlag;
extern BOOLEAN VGACreateStartFlag;
extern BOOLEAN VGACreateStartErrorFlag;
extern BOOLEAN QVGAHornDown;
extern BOOLEAN VGAChecksum;
extern BOOLEAN VGAWeldStartData;
extern BOOLEAN QVGAHornScanOLD;
extern BOOLEAN VGA_ReadyFlag;
extern BOOLEAN ReadyFlag;
extern INBITS Inp;
extern UINT8 PrevHornState;
extern UINT8 AlarmDetectedFlag;
extern UINT16  LangIndex;              /*Language Index*/
extern UINT16  CalibrationPassed;
extern UINT16  AbortPrintingFlag;
extern UINT16 DiagFlag;
extern UINT16 EstopHistoryFlag;
extern UINT16 VGAAction;
extern UINT16 ShowHSAbort;
extern UINT32 QvgaQid;                 /*QVGA queue ID*/
extern SINT32 SaveDigPotValue;   /* Used to determine if user changed value */
extern SINT32 DigPotValue;           /* This is what user edits */
extern SINT32  ExtSampleCount;
extern enum WELDSTATES WeldState;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern CONFIGSETUP CurrentSetup;
extern SETUPS_Ver800 CurrentPreset;
extern UINT16 TotalCycle;
extern BOOLEAN AllParamColumnFlag;
extern BOOLEAN VGAWelderStateChange;
extern BOOLEAN PresetStatusMenuFlag;
extern UINT16 TotalAlarmCount;
extern UINT16 DisplayRefreshButton;
extern UINT32 PollingCommandCounter;

extern Fifo txqvgafifo;
/*VGA Host COmmand related variables*/
extern UINT8 VGAAckBuf[];
extern UINT32 NackError;
extern UINT32 ErrorResponseMinLimit;
extern UINT32 ErrorResponseMaxLimit;
extern UINT16   RadioIndex;
extern BUCMENU_800 BUCMenuRAM;
extern BOOLEAN         WindowSetupFlag;
extern BOOLEAN CurrentPresetParameterChanged;
extern BOOLEAN SystemParameterChgdFlag;

extern VGA_ScreenMicronCalFlag;

/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

enum LEVEL AccessLevel = OPERATOR;

/*
 --------------------------- EXTERNAL FUNCTION PROTOTYPES -----------------------
*/
void UpdateTestLine(void);
void QVGAExitTestSequence(void);

void QVGADigitalPotChoiceDone(void);
BOOLEAN IsCalibGoingOn(void);

SINT16 SPrintf(SINT8* pc_buf, const SINT8* pc_format,...);

/* Alarms*/
BOOLEAN ProcessAlarmButton(TOUCH_HANDLER_MSG *TouchScrnPos);
void DrawAlarmButton(void);
BOOLEAN ExitAlarmScrn(void);
void QVGAAlarmReset(UINT8 QVGAestop);

/*Emergency stop functions*/
void QVGARestoreDefaultsOK(void);
//void QVGAOverwriteAllPreset (void);
void  ExitMenuAndEnableWeld (void);

UINT32 SendFakeKeyPress(KEY_CODE_TYPE Key);
/*VGA Host Command Function prototype*/
UINT16 SendMenuPtrs(UINT8 * to);
UINT16 CreateACK(UINT8 * AckBuf, UINT16 Function, UINT8 * response, UINT16 len);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
void InitWeldParamOption(void);
UINT16 VGASendGraphData(UINT8 * * Response, EDIT_PARAM_TYPE ParamID);
UINT16 ProcessVGAButton (UINT32 * address);
UINT16 DrawVGAHSGraph(UINT8 * * Response, EDIT_PARAM_TYPE ParamID);
void VGAProcessHornDownMsg (void);
UINT16 CreateSameBufferACK(UINT8 * AckBuf, UINT16 Function, UINT16 len);
void ClearPMCData(void);
void VGARequestActCal(void);

void VGARequestMicronCalDisabled(void);

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -----------------------
*/
void QVGAAlarmReset(UINT8 QVGAestop);
UINT16 LangStrLen(SINT8 * str); 
BOOLEAN LangCheckNull(SINT8 * Line);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);
extern SETUPS_Ver800 CurrentPreset,RunningPreset;
extern WELD_DATA       FinalResults;

/*
 ---------------------------------- CODE -------------------------------------
*/


void ProcessAlarmItems (UINT16 AlarmPosition)
/****************************************************************************/
/*Description:-                                                             */
/* This function processes the Alarm item.                                  */
/*Input Parameters:-                                                        */
/* ID: This is basically Bit position of alarm sent by SBC.                 */
/*Output:-                                                                  */
/*If condition fulfilled than NACKERROR with additional two parameters      */
/****************************************************************************/
{
       /* need to check if calibration is allowed before */
       /* updating the screen. ALARM type does not allow */
       /* a function to be run before menu is displayed  */

       if ((AlarmPosition == EQRECALIB_BIT/*&EQRecalibrateActuator*/) ||
           (AlarmPosition == WARNINGALARM8_BIT/*&WA8text*/))
       {
          VGARequestActCal();
       }
}

void BottomMenuProcess (void)
/****************************************************************************/
/*Description:-                                                             */
/* This function processes Bottom button press                              */
/*Input Parameters:-                                                        */
/* GlobalCommandID:  CommandID of the  Menu                                           */
/*Output:-                                                                  */
/* Bootom menu entry                                                        */
/* or NACKERROR with additional two parameters                              */
/****************************************************************************/
{

   PresetStatusMenuFlag = FALSE;
   if (GlobalCommandID == RUN_MENU) //VGARunMenu
   {
      if ((GetCurrentSequenceType() == POWERCAL)||
          (CurrentSequence == SC) || 
          (CurrentSequence == CALIBRATION))
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
         ErrorResponseMaxLimit = 0;
      }
      else
         AccessLevel = OPERATOR;
   }     
   else if (GlobalCommandID == MAIN_MENU) //QVGATheMainMenu
   {
      if (GetCurrentSequenceType() == POWERCAL)
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
         ErrorResponseMaxLimit = 0;
      }
      else
         AccessLevel = OPERATOR;
   }     
   else if (GlobalCommandID == WELDMODE_MENU) //WeldModeSelectMenu
   {
      if ((CurrentSequence == SC)||
          (CurrentSequence == CALIBRATION) )
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
         ErrorResponseMaxLimit = 0;
      }
      if(Inp.DisplayLockFlag)
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_MAIN_MENU;
         ErrorResponseMaxLimit = 0;
      }
      else if((CurrentSetup.PassWordFlag & BIT0) && (AccessLevel < MAINTAINENCE)) 
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = SHOW_PASSWORD_SCREEN;
         ErrorResponseMaxLimit = 0;
      }
   }     
   else if (GlobalCommandID == GRAPH_MENU) //GraphMenu
   {
      if ((CurrentSequence == SC) || 
          (CurrentSequence == CALIBRATION))
      {
         NackError = WELDER_PROCESS_ERROR;
         ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
         ErrorResponseMaxLimit = 0;
      }
      else
      {
         AccessLevel = OPERATOR;
         DisplayRefreshButton = ~CurrentSetup.AutoRefresh;
      }   
   }     
         
   if ((GlobalCommandID == MAIN_MENU) ||
        (GlobalCommandID == WELDMODE_MENU) ||
        (GlobalCommandID == GRAPH_MENU)||
        (GlobalCommandID == RUN_MENU))
   {     
      DiagFlag = FALSE;    //Disable diagnostics
      if(QVGACalAllowed)
         SCFinalCleanup();
      else if(QVGASnsrCalibAllowed)
         CalibFinalCleanup();   
             /*If we are in TEST sequence Exit from there*/
      if(CurrentSequence == TESTMODE)
      {
         QVGAExitTestSequence();
         SendFakeKeyPress(GoBackKey);
      }
      if(!DUPSOkFlag)
         EnableWelding();
      /* Reset the state machine and keymask when exit from UserIOMenu. */ 
      if(StateMachineDisabled)
         ExitMenuAndEnableWeld();            
      if (QVGAHornDown)   
      {
         VGAAction = EXIT_HD;
         VGAProcessHornDownMsg();
      }   
   }
   VGARequestMicronCalDisabled();
}

UINT16 AddToBuffer(UINT8 * * to, SINT8 byte)
/****************************************************************************/
/*Description:-                                                             */
/* This function writes a byte to the buffer                                */
/*Input Parameters:-                                                        */
/* to:  Address of the buffer                                               */
/* byte: Value to be written                                                */
/*Output:-                                                                  */
/* Length of the byte                                                       */
/****************************************************************************/
{
	UINT8 * ptr = *to;
	*ptr++ = byte;
	*to = ptr;
	return sizeof(byte);
}

UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length)
/****************************************************************************/
/*Description:-                                                             */
/* This function writes specified number of bytes from the start of string  */
/* to the buffer                                                            */                                                   
/*Input Parameters:-                                                        */
/* to:  address of the buffer                                               */  
/* string:                                                                  */
/* length: Length of the bytes to be written                                */                                
/*Output:-                                                                  */
/* Length of the bytes written                                              */
/****************************************************************************/
{
	UINT16 i;
	for (i = 0; i < length; i++)
		AddToBuffer(to, *string++);
	return length;
}

void ClearPMCData(void)
/****************************************************************************/
/*Description:-                                                             */
/* This function clears Power match curve data                              */
/****************************************************************************/
{
   UINT16 i;
   StoreCycleCount = 0;
   CurrentPreset.PMCCycleCount = 0;
   for (i = 0; i < PMCDATAPOINTS; i++){
      CurrentPreset.PMCData[i] = 0xFF;
   }
}

UINT16 SendMenuPtrs(UINT8 * to)
/****************************************************************************/
/*Description:-                                                             */
/* This function sends Language, start screen, Unit, Time & Date and Bottom */
/* Menu pointers in response to 1000 command from SBC                       */                                                   
/*Input Parameters:-                                                        */
/* to:  buffer where data is to be written                                  */
/*Returns length of the bytes written to the buffer                         */  
/****************************************************************************/
{
    RTC Welder_Clock;

	UINT16 length,i;		// length of data in output buffer
    UpdateHWConfiguration(QVGA, TRUE);           
    UpdateHWConfiguration(VGA, TRUE); 
    
    CurrentSetup.VGAHWPresent = TRUE;    //VGA HW detected
    //StartStateMachine();                 //Start State machines
    
    InitWeldParamOption();
    length = 0;
    length += AddToBuffer(&to, (UINT8)LangIndex);  //Language
    if (CurrentSetup.StartScreen)
       length += AddToBuffer(&to, 1);  //Run Screen
    else
      length += AddToBuffer(&to, 0);  //Main Screen
    if (CurrentSetup.Units)
       length += AddToBuffer(&to, 1);  //Metric Units
    else
      length += AddToBuffer(&to, 0);  //English Units
    Welder_Clock = RtcReadDateandTime();
   length += AddToBuffer(&to, (UINT8)Welder_Clock.Hour);
   length += AddToBuffer(&to, (UINT8)Welder_Clock.Minute);
   length += AddToBuffer(&to, (UINT8)Welder_Clock.Second);
   length += AddToBuffer(&to, (UINT8)Welder_Clock.Month);
   length += AddToBuffer(&to, (UINT8)Welder_Clock.Day);
   length += AddToBuffer(&to, (UINT8)Welder_Clock.Year);
   for(i=1;i<=16;i++)
	         length += AddToBuffer(&to, 0);  //English Units
   return length;
}

void MoveToNextCalibMenu(void)
/***************************************************************************/
/*Description:                                                             */
/* brings next calibration Screen depends on the calibration status.       */
/***************************************************************************/
{
   if(CalibrationPassed == CAL_PASSED)
      StartCalibFlag=TRUE;
   else
   {
      if(CalActErrorFlag)
      {
         CalActErrorFlag= FALSE;
         SCFinalCleanup();
      }
      StartCalibFlag=FALSE;
   } 
}


UINT16 ExitHDForResetRequiredAlarms(void)
/****************************************************************************/
/*                                                                          */
/* This function will check to see if a reset is required.  If a reset is   */
/* required then a TRUE will be returned, otherwise a FALSE will be         */
/* returned.                                                                */
/*                                                                          */
/****************************************************************************/
{
	UINT16 ResetRequiredFlag = FALSE;          /* Assume reset not required */

	/*---  Here, check alarms which always require reset  ---*/

	if ( ((FinalResults.OverloadAlarms & OL_RESET) != 0) ||
	   ((FinalResults.EquipmentFailureAlarms & EQ_NO_RESET) != 0) ||
	   ((FinalResults.EquipmentFailureAlarms & EQ_RESET) != 0) ||
	   ((FinalResults.CalibrateAlarms & CA_NO_RESET) != 0) ) {
	 ResetRequiredFlag = TRUE;         
	}
	if(ResetRequiredFlag == FALSE)
	{

	/*--  Check alarms which require reset only if Reset Required = On  --*/

		if (RunningPreset.GeneralAlarmLFlag == TRUE) {   /* See if globally required */
			if ( ((FinalResults.NoCycleAlarms & NC_NOT_REQ_RESET) != 0) ||
				((FinalResults.OverloadAlarms & OL_NOT_REQ_RESET) != 0) ||
				((FinalResults.EquipmentFailureAlarms & EQ_NOT_REQ_RESET) != 0) ||
				((FinalResults.CycleModifiedAlarms & CM_NOT_REQ_RESET_EXCLUDE_CM1) != 0) ||
				(FinalResults.RejectBitResult != 0) ||
				(FinalResults.SuspectBitResult != 0) ||
				(FinalResults.CalibrateAlarms != 0)) {
				ResetRequiredFlag = TRUE;
			}
		}
		if((FinalResults.CycleModifiedAlarms & CM15) == (CM15 & ALARMCODEMASK))
			ResetRequiredFlag = TRUE;
	}

  
   return(ResetRequiredFlag);
}


UINT16 VGASendPollingData(UINT8 * to)
/****************************************************************************/
/*Description:- Reply to the polling command                                */
/****************************************************************************/
{
   UINT16 length = 0;		// length of data in output buffer
    UINT32 VGAPollingPointer = 0;
    static UINT16 PreviousAlarmCount = 0;
    if (!IsHWConfigured(VGA))
    {
       UpdateHWConfiguration(QVGA, TRUE);           
       UpdateHWConfiguration(VGA, TRUE); 
       InitWeldParamOption();
    }
  
    length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldCount)>>24)); 	  
    length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldCount)>>16));	  
    length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldCount)>>8));	  
    length += AddToBuffer(&to, (UINT8)(CurrentPreset.WeldCount));	  

    length += AddToBuffer(&to, (UINT8)((PollingCommandCounter)>>24)); 	  
    length += AddToBuffer(&to, (UINT8)((PollingCommandCounter)>>16));	  
    length += AddToBuffer(&to, (UINT8)((PollingCommandCounter)>>8));	  
    length += AddToBuffer(&to, (UINT8)(PollingCommandCounter));	  

    length += AddToBuffer(&to, (UINT8)(CheckPrinterStatus));
    CheckPrinterStatus = FALSE;	  
    length += AddToBuffer(&to, (UINT8)(CurrentSetup.ActivePreset));	  
    length += AddToBuffer(&to, (UINT8)((TotalAlarmCount)>>8));	  
    length += AddToBuffer(&to, (UINT8)(TotalAlarmCount));	  
    length += AddToBuffer(&to, (UINT8)(VGAWeldStartData));
    VGAWeldStartData = FALSE;	  
    
	if (((QVGAHornDown) && (TotalAlarmCount > PreviousAlarmCount ))||(QVGAHDAlarm == TRUE)){
		QVGAHDAlarm = FALSE;
		if(ExitHDForResetRequiredAlarms() == TRUE){
			VGAPollingPointer = VGAPollingPointer | 0x08000000;
		}
	}


	PreviousAlarmCount = TotalAlarmCount;
    if(Inp.DisplayLockFlag)
       VGAPollingPointer = VGAPollingPointer | 0x80000000;
    else
       VGAPollingPointer = VGAPollingPointer | 0x00000000;

    if(SystemParameterChgdFlag)  /*check for control level or actuator change*/
    {
       SystemParameterChgdFlag =FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x40000000;
    }
    else
       VGAPollingPointer = VGAPollingPointer | 0x00000000;

    if (VGATestKeyPressed)
    {
       VGATestKeyPressed = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x09000000;
    }
    else if (VGAEstopOn)
    {
       VGAEstopOn = FALSE;
       if(EStopState == ESTOPBTN_PRESSED)
         VGAPollingPointer = VGAPollingPointer | 0x07000000;
       else
         VGAPollingPointer = VGAPollingPointer | 0x02000000;

    }
    else if (VGAEstopOff)
    {
       VGAEstopOff = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x01000000;
    }
    else if (VGAEstopReset)
    {
       VGAEstopReset = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x08000000;
    }
    else if (VGACalibKey)
    {
       VGACalibKey = FALSE;
       MoveToNextCalibMenu();
       if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) )
          VGAPollingPointer = VGAPollingPointer | 0x00000001;
       else
          VGAPollingPointer = VGAPollingPointer | 0x00000000;

       if(StartCalibFlag)
       {
         VGAPollingPointer = VGAPollingPointer | 0x05000000;
       }
       else
       {
         VGAPollingPointer = VGAPollingPointer | 0x06000000;
       }
    }
    else if (VGACalAborted)
    {
       VGACalAborted = FALSE;
       QVGACalAllowed = FALSE;
       QVGASnsrCalibAllowed = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
      NextMenuFlag=TRUE;
    }
    else if (VGADebugDataFlag)
    {
       VGADebugDataFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
    }
    else if (VGADigitalChoiceWaitFlag)
    {
       VGADigitalChoiceWaitFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
    }
    else if (VGADigitalChoiceTestFlag && DigPotKey)
    {
       VGADigitalChoiceTestFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
    }
    else if(NextMenuFlag)
    {
      NextMenuFlag = FALSE;
      VGAPollingPointer = VGAPollingPointer | 0x03000000;
    }
    else if(ChkSumCompleteFlag)
    {
       ChkSumCompleteFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
    }
    else if(CSCompleteFlag)
    {
       CSCompleteFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
    }
    else if (VGAColdStartFlag)
    {

       VGAColdStartFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
       CSCompleteFlag = TRUE;
    }
    else if (VGAColdStartErrorFlag)
    {
       VGAColdStartErrorFlag = FALSE;
	    NextMenuFlag = TRUE;
       VGAPollingPointer = VGAPollingPointer | 0x04000000;
    }
    else if (VGAActStartFlag)
    {
       VGAActStartFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
       CSCompleteFlag = TRUE;
    }
    else if (VGAActStartErrorFlag)
    {
       VGAActStartErrorFlag = FALSE;
	    NextMenuFlag = TRUE;
       VGAPollingPointer = VGAPollingPointer | 0x04000000;
    }
    else if (VGARestoreColdStartFlag)
    {
       VGARestoreColdStartFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
       CSCompleteFlag = TRUE;
    }
    else if (VGARestoreErrorFlag)
    {
       VGARestoreErrorFlag = FALSE;
	    NextMenuFlag = TRUE;
       VGAPollingPointer = VGAPollingPointer | 0x04000000;
    }
    else if (VGAOverwritePresetFlag)
    {
       VGAOverwritePresetFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
       CSCompleteFlag = TRUE;
    }
    else if (VGAOverwriteErrorFlag)
    {
       VGAOverwriteErrorFlag = FALSE;
	    NextMenuFlag = TRUE;
       VGAPollingPointer = VGAPollingPointer | 0x04000000;
    }
    else if (VGACreateStartFlag)
    {
       VGACreateStartFlag = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
       CSCompleteFlag = TRUE;
    }
    else if (VGACreateStartErrorFlag)
    {
       VGACreateStartErrorFlag = FALSE;
	    NextMenuFlag = TRUE;
       VGAPollingPointer = VGAPollingPointer | 0x04000000;
    }
    else if (VGAChecksum)
    {
       VGAChecksum = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x03000000;
       CSCompleteFlag = TRUE;
    }
    else if(CurrentPresetParameterChanged)
    {
       CurrentPresetParameterChanged = FALSE;
       VGAPollingPointer = VGAPollingPointer | 0x0A000000;
    }
    length += AddToBuffer(&to, (UINT8)((VGAPollingPointer)>>24)); 	  
    length += AddToBuffer(&to, (UINT8)((VGAPollingPointer)>>16));	  
    length += AddToBuffer(&to, (UINT8)((VGAPollingPointer)>>8));	  
    length += AddToBuffer(&to, (UINT8)(VGAPollingPointer));	  
    return length;
}


UINT16 VGAPrintParameters(UINT8 * to)
/****************************************************************************/
/*Description:-                                                             */
/* Sends VGA print param to the SBC                                          */
/****************************************************************************/
{
   UINT16 length = 0;

   if(CurrentSetup.ExtPresets == TRUE)  // External preset enabled byte
      length += AddToBuffer(&to, 1);            
   else
      length += AddToBuffer(&to, 0);

   if (CurrentSetup.ExtPresets == TRUE) // Global printing flag
   {
      if(CurrentSetup.ExtGlobalPrintFlag)
         length += AddToBuffer(&to, 1);
      else      
         length += AddToBuffer(&to, 0);
   }
   else
   {
      if(CurrentPreset.GlobalPrintingFlag)
         length += AddToBuffer(&to, 1);
      else      
         length += AddToBuffer(&to, 0);
   }

   if(CurrentSetup.PageSize & PAGESIZEA4)  // page size
      length += AddToBuffer(&to, 1);            
   else
      length += AddToBuffer(&to, 0);
                  
   length += AddToBuffer(&to, (UINT8)CurrentSetup.WeldsPerPage);  // Welds per page
   
   if (CurrentSetup.ExtPresets == TRUE)
   {
      /* Print Setup Sample Value*/
      if((CurrentSetup.SPExtSampleFlag & /*ExtPrintOnSampleSetup.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.SPExtSampleValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.SPExtSampleValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.SPExtSampleValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentSetup.SPExtSampleValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Setup Alarm Flag*/
      if (CurrentSetup.SPExtAlarmFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Summary Sample Value*/
      if((CurrentSetup.WSExtSampleFlag & /*ExtPrintOnSampleSummary.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.WSExtSampleValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.WSExtSampleValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.WSExtSampleValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentSetup.WSExtSampleValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Summary Alarm Flag*/
      if (CurrentSetup.WSExtAlarmFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     
   
      /* Print Weld History Sample Value*/
      if((CurrentSetup.WHExtSampleFlag & /*ExtPrintOnSampleHistory.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.WHExtSampleValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.WHExtSampleValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.WHExtSampleValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentSetup.WHExtSampleValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Weld History Alarm Flag*/
      if (CurrentSetup.WHExtAlarmFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Sequencing Sample Value*/
      if((CurrentSetup.SeqExtSampleFlag & /*ExtPrintOnSampleSeq.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.SeqExtSampleValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.SeqExtSampleValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.SeqExtSampleValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentSetup.SeqExtSampleValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Sequencing Alarm Flag*/
      if (CurrentSetup.SeqExtAlarmFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Power Graph Sample Value*/
      if((CurrentSetup.PGExtSampleFlag & /*ExtPrintOnSamplePower.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.PGExtSampleValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.PGExtSampleValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.PGExtSampleValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentSetup.PGExtSampleValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Power Graph Alarm Flag*/
      if (CurrentSetup.PGExtAlarmFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Col. Distance Graph Sample Value*/
      if((CurrentSetup.CDGExtSampleFlag & /*ExtPrintOnSampleDistance.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.CDGExtSampleValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.CDGExtSampleValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.CDGExtSampleValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentSetup.CDGExtSampleValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Col. Distance Graph Alarm Flag*/
      if (CurrentSetup.CDGExtAlarmFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Velocity Graph Sample Value*/
      if((CurrentSetup.VGExtSampleFlag & /*ExtPrintOnSampleVelocity.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.VGExtSampleValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.VGExtSampleValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.VGExtSampleValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentSetup.VGExtSampleValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Velocity Graph Alarm Flag*/
      if (CurrentSetup.VGExtAlarmFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Force Graph Sample Value*/
      if((CurrentSetup.FGExtSampleFlag & /*ExtPrintOnSampleForce.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.FGExtSampleValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.FGExtSampleValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.FGExtSampleValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentSetup.FGExtSampleValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Force Graph Alarm Flag*/
      if (CurrentSetup.FGExtAlarmFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Amplitude Graph Sample Value*/
      if((CurrentSetup.AGExtSampleFlag & /*ExtPrintOnSampleAmplitude.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.AGExtSampleValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.AGExtSampleValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.AGExtSampleValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentSetup.AGExtSampleValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Amplitude Graph Alarm Flag*/
      if (CurrentSetup.AGExtAlarmFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Freq. Graph Sample Value*/
      if((CurrentSetup.FreqGExtSampleFlag & /*ExtPrintOnSampleFreq.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.FreqGExtSampleValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.FreqGExtSampleValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentSetup.FreqGExtSampleValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentSetup.FreqGExtSampleValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Freq. Graph Alarm Flag*/
      if (CurrentSetup.FreqGExtAlarmFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     
      
   }
   else
   {
      /* Print Setup Sample Value*/
      if((CurrentPreset.SetupPresetSFlag & /*PrintOnSampleSetup.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.SetupPresetValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.SetupPresetValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.SetupPresetValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentPreset.SetupPresetValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Setup Alarm Flag*/
      if (CurrentPreset.SetupPresetAFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Summary Sample Value*/
      if((CurrentPreset.WeldSummarySFlag & /*PrintOnSampleSummary.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldSummaryValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldSummaryValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldSummaryValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentPreset.WeldSummaryValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Summary Alarm Flag*/
      if (CurrentPreset.WeldSummaryAFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     
   
      /* Print Weld History Sample Value*/
      if((CurrentPreset.WeldHistorySFlag & /*PrintOnSampleHistory.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldHistoryValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldHistoryValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.WeldHistoryValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentPreset.WeldHistoryValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Weld History Alarm Flag*/
      if (CurrentPreset.WeldHistoryAFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Sequencing Sample Value*/
      if((CurrentPreset.SeqPresetSFlag & /*PrintOnSampleSeq.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.SeqPresetValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.SeqPresetValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.SeqPresetValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentPreset.SeqPresetValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Sequencing Alarm Flag*/
      if (CurrentPreset.SeqPresetAFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Power Graph Sample Value*/
      if((CurrentPreset.PowerGraphSFlag & /*PrintOnSamplePower.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.PowerGraphValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.PowerGraphValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.PowerGraphValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentPreset.PowerGraphValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Power Graph Alarm Flag*/
      if (CurrentPreset.PowerGraphAFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Col. Distance Graph Sample Value*/
      if((CurrentPreset.ColDistanceGraphSFlag & /*PrintOnSampleDistance.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.ColDistanceGraphValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.ColDistanceGraphValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.ColDistanceGraphValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentPreset.ColDistanceGraphValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Col. Distance Graph Alarm Flag*/
      if (CurrentPreset.ColDistanceGraphAFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Velocity Graph Sample Value*/
      if((CurrentPreset.VelocityGraphSFlag & /*PrintOnSampleVelocity.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.VelocityGraphValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.VelocityGraphValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.VelocityGraphValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentPreset.VelocityGraphValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Velocity Graph Alarm Flag*/
      if (CurrentPreset.VelocityGraphAFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Force Graph Sample Value*/
      if((CurrentPreset.ForceGraphSFlag & /*PrintOnSampleForce.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.ForceGraphValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.ForceGraphValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.ForceGraphValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentPreset.ForceGraphValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Force Graph Alarm Flag*/
      if (CurrentPreset.ForceGraphAFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Amplitude Graph Sample Value*/
      if((CurrentPreset.AmplitudeGraphSFlag & /*PrintOnSampleAmplitude.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.AmplitudeGraphValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.AmplitudeGraphValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.AmplitudeGraphValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentPreset.AmplitudeGraphValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Amplitude Graph Alarm Flag*/
      if (CurrentPreset.AmplitudeGraphAFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

      /* Print Freq. Graph Sample Value*/
      if((CurrentPreset.FrequencyGraphSFlag & /*PrintOnSampleFreq.BitMask*/BIT0) == FALSE)
      {
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.FrequencyGraphValue)>>24)); 	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.FrequencyGraphValue)>>16));	  
         length += AddToBuffer(&to, (UINT8)((CurrentPreset.FrequencyGraphValue)>>8));	  
         length += AddToBuffer(&to, (UINT8)(CurrentPreset.FrequencyGraphValue));	  
      }
      else
      {
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
         length += AddToBuffer(&to, 0);     
      }
      /*Print Freq. Graph Alarm Flag*/
      if (CurrentPreset.FrequencyGraphAFlag == TRUE)
         length += AddToBuffer(&to, 1);
      else
         length += AddToBuffer(&to, 0);     

   }
   /* USB global ON/Off flag */
   if(CurrentSetup.USBGlobalFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);

   /* USB weld data Sample Value*/
   if((CurrentSetup.USBWDSampleFlag & /*USBWeldDataSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBWDSampleValue)>>24)); 	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBWDSampleValue)>>16));	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBWDSampleValue)>>8));	  
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBWDSampleValue));	  
   }
   else
   {
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
   }
   /*USB Weld data Alarm Flag*/
   if (CurrentSetup.USBWDAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);     

   /* USB Power Graph Sample Value*/
   if((CurrentSetup.USBPGSampleFlag & /*USBPowerSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBPGSampleValue)>>24)); 	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBPGSampleValue)>>16));	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBPGSampleValue)>>8));	  
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBPGSampleValue));	  
   }
   else
   {
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
   }
   /*USB Power Graph Alarm Flag*/
   if (CurrentSetup.USBPGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);      

   /* USB Col. Distance Graph Sample Value*/
   if((CurrentSetup.USBCDGSampleFlag & /*USBDistanceSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBCDGSampleValue)>>24)); 	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBCDGSampleValue)>>16));	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBCDGSampleValue)>>8));	  
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBCDGSampleValue));	  
   }
   else
   {
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
   }
   /*USB Col. Distance Graph Alarm Flag*/
   if (CurrentSetup.USBCDGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);      

   /* USB Velocity Graph Sample Value*/
   if((CurrentSetup.USBVGSampleFlag & /*USBVelocitySample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBVGSampleValue)>>24)); 	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBVGSampleValue)>>16));	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBVGSampleValue)>>8));	  
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBVGSampleValue));	  
   }
   else
   {
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
   }
   /*USB Velocity Graph Alarm Flag*/
   if (CurrentSetup.USBVGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);     

   /* USB Force Graph Sample Value*/
   if((CurrentSetup.USBFGSampleFlag & /*USBForceSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFGSampleValue)>>24)); 	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFGSampleValue)>>16));	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFGSampleValue)>>8));	  
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBFGSampleValue));	  
   }
   else
   {
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
   }
   /*USB Force Graph Alarm Flag*/
   if (CurrentSetup.USBFGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);     

   /* USB Amplitude Graph Sample Value*/
   if((CurrentSetup.USBAGSampleFlag & /*USBAmplitudeSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBAGSampleValue)>>24)); 	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBAGSampleValue)>>16));	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBAGSampleValue)>>8));	  
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBAGSampleValue));	  
   }
   else
   {
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
   }
   /*USB Amplitude Graph Alarm Flag*/
   if (CurrentSetup.USBAGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);      

   /* USB Freq. Graph Sample Value*/
   if((CurrentSetup.USBFreqGSampleFlag & /*USBFreqSample.BitMask*/BIT0) == FALSE)
   {
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFreqGSampleValue)>>24)); 	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFreqGSampleValue)>>16));	  
      length += AddToBuffer(&to, (UINT8)((CurrentSetup.USBFreqGSampleValue)>>8));	  
      length += AddToBuffer(&to, (UINT8)(CurrentSetup.USBFreqGSampleValue));	  
   }
   else
   {
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
      length += AddToBuffer(&to, 0);     
   }
   /*USB Freq. Graph Alarm Flag*/
   if (CurrentSetup.USBFreqGAlarmFlag == TRUE)
      length += AddToBuffer(&to, 1);
   else
      length += AddToBuffer(&to, 0);     
   
   return (length);
}

UINT16 VGAPrintGraphInfo(UINT8 * to)
/****************************************************************************/
/*Description:-                                                             */
/* Sends VGA Weld data column ID and Misc Notes section for printing graphs */
/****************************************************************************/
{
   UINT16 length = 0;
   SINT8 PCChar[LINELEN*2];

   if(CurrentSetup.ControlLevel == LEVEL_t)
      length += AddToBuffer(&to, 0);
   else
   if(CurrentSetup.ControlLevel == LEVEL_e)
   {
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_7);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQSTART);
      length += AddToBuffer(&to, RFREQEND);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      
   }
   else /*--  WITH AED --*/ 
   if ( (CurrentSetup.ControlLevel == LEVEL_d) &&
        ( (CurrentSetup.Actuator == AED) ||
          (CurrentSetup.Actuator == AEF) ||   /* Is this wrong? 9-10-09 BEK */
          (CurrentSetup.Actuator == MICRO) ) )
   { 
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_14);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RTABSDIST);
      length += AddToBuffer(&to, RWCOLDIST);
      length += AddToBuffer(&to, RTCOLDIST);
      length += AddToBuffer(&to, RTRIGFORCE);
      length += AddToBuffer(&to, RFORCE);
      length += AddToBuffer(&to, RFREQSTART);
      length += AddToBuffer(&to, RFREQEND);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
      if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) )
         length += AddToBuffer(&to, RVELOCITY_AED);
      else   
         length += AddToBuffer(&to, RVELOCITY_AEF);
   }
   else 
   if(CurrentSetup.ControlLevel == LEVEL_f || CurrentSetup.ControlLevel == LEVEL_TEST)
   {
      if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) )
      {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_14);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RTABSDIST);
         length += AddToBuffer(&to, RWCOLDIST);
         length += AddToBuffer(&to, RTCOLDIST);
         length += AddToBuffer(&to, RTRIGFORCE);
         length += AddToBuffer(&to, RFORCE);
         length += AddToBuffer(&to, RFREQSTART);
         length += AddToBuffer(&to, RFREQEND);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
         length += AddToBuffer(&to, RVELOCITY_AED);
      }
      else if(CurrentSetup.Actuator == AEF)
      {
         if(BUCMenuRAM.VelocityReporting == TRUE)
         {
            length += AddToBuffer(&to, WELDCOLUMN_COUNT_16);
            length += AddToBuffer(&to, RTIME);
            length += AddToBuffer(&to, RPKPWR);
            length += AddToBuffer(&to, RENERGY);
            length += AddToBuffer(&to, RTABSDIST);
            length += AddToBuffer(&to, RWCOLDIST);
            length += AddToBuffer(&to, RTCOLDIST);
            length += AddToBuffer(&to, RTRIGFORCE);
            length += AddToBuffer(&to, RFORCEA);
            length += AddToBuffer(&to, RFORCEB);
            length += AddToBuffer(&to, RFORCE);
            length += AddToBuffer(&to, RFREQSTART);
            length += AddToBuffer(&to, RFREQEND);
            length += AddToBuffer(&to, RFREQCHG);
            length += AddToBuffer(&to, RAMPSTART);
            length += AddToBuffer(&to, RAMPEND);
            length += AddToBuffer(&to, RVELOCITY_AEF);
         }
         else   
         {
            length += AddToBuffer(&to, WELDCOLUMN_COUNT_15);
            length += AddToBuffer(&to, RTIME);
            length += AddToBuffer(&to, RPKPWR);
            length += AddToBuffer(&to, RENERGY);
            length += AddToBuffer(&to, RTABSDIST);
            length += AddToBuffer(&to, RWCOLDIST);
            length += AddToBuffer(&to, RTCOLDIST);
            length += AddToBuffer(&to, RTRIGFORCE);
            length += AddToBuffer(&to, RFORCEA);
            length += AddToBuffer(&to, RFORCEB);
            length += AddToBuffer(&to, RFORCE);
            length += AddToBuffer(&to, RFREQSTART);
            length += AddToBuffer(&to, RFREQEND);
            length += AddToBuffer(&to, RFREQCHG);
            length += AddToBuffer(&to, RAMPSTART);
            length += AddToBuffer(&to, RAMPEND);
         }   
      }
      else if(CurrentSetup.Actuator == AE)
      {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_8);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RFREQSTART);
         length += AddToBuffer(&to, RFREQEND);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
      }
   }
   else /*--  WITHOUT ENCODER --*/ 
   if(CurrentSetup.ControlLevel == LEVEL_ea)
   {
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_8);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQSTART);
      length += AddToBuffer(&to, RFREQEND);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
   }
   else /*--  WITHOUT ENCODER --*/ 
   if ( (CurrentSetup.ControlLevel == LEVEL_d) &&
        ( (CurrentSetup.Actuator != AED) ||
          (CurrentSetup.Actuator != AEF) ||
          (CurrentSetup.Actuator != MICRO) ) )
   { 
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_8);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQSTART);
      length += AddToBuffer(&to, RFREQEND);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
   }
   else
   {
      length += AddToBuffer(&to, 0);
   }
   return(length);
}

UINT16 VGAWeldDataInfo(UINT8 * to)
/****************************************************************************/
/*Description:-                                                             */
/* Prepares VGA Weld Column IDs to be seen on Print summary and history scrn*/
/****************************************************************************/
{
   UINT16 length = 0;
   
   if(CurrentSetup.ControlLevel == LEVEL_t)
   {
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_3);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
   }
   else
   if(CurrentSetup.ControlLevel == LEVEL_e)
   {
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_5);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
   }
   else /*--  WITH ENCODER --*/ 
   if((CurrentSetup.ControlLevel == LEVEL_d)&&
      ((CurrentSetup.Actuator == AED) ||(CurrentSetup.Actuator == MICRO)||
       (CurrentSetup.Actuator == AEF)))
   { 
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_12);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RTABSDIST);
      length += AddToBuffer(&to, RWCOLDIST);
      length += AddToBuffer(&to, RTCOLDIST);
      length += AddToBuffer(&to, RTRIGFORCE);
      length += AddToBuffer(&to, RFORCE);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
      if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) )
         length += AddToBuffer(&to, RVELOCITY_AED);
      else   
         length += AddToBuffer(&to, RVELOCITY_AEF);
   }
   else
   if(CurrentSetup.ControlLevel == LEVEL_f || CurrentSetup.ControlLevel == LEVEL_TEST)
   {
      if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) )
      {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_12);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RTABSDIST);
         length += AddToBuffer(&to, RWCOLDIST);
         length += AddToBuffer(&to, RTCOLDIST);
         length += AddToBuffer(&to, RTRIGFORCE);
         length += AddToBuffer(&to, RFORCE);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
         length += AddToBuffer(&to, RVELOCITY_AED);
      }
      else if(CurrentSetup.Actuator == AEF)
      {
         if (BUCMenuRAM.VelocityReporting == TRUE) {
            length += AddToBuffer(&to, WELDCOLUMN_COUNT_14);
            length += AddToBuffer(&to, RTIME);
            length += AddToBuffer(&to, RPKPWR);
            length += AddToBuffer(&to, RENERGY);
            length += AddToBuffer(&to, RTABSDIST);
            length += AddToBuffer(&to, RWCOLDIST);
            length += AddToBuffer(&to, RTCOLDIST);
            length += AddToBuffer(&to, RTRIGFORCE);
            length += AddToBuffer(&to, RFORCEA);
            length += AddToBuffer(&to, RFORCEB);
            length += AddToBuffer(&to, RFORCE);
            length += AddToBuffer(&to, RFREQCHG);
            length += AddToBuffer(&to, RAMPSTART);
            length += AddToBuffer(&to, RAMPEND);
            length += AddToBuffer(&to, RVELOCITY_AEF);
         }
         else {
            length += AddToBuffer(&to, WELDCOLUMN_COUNT_13);
            length += AddToBuffer(&to, RTIME);
            length += AddToBuffer(&to, RPKPWR);
            length += AddToBuffer(&to, RENERGY);
            length += AddToBuffer(&to, RTABSDIST);
            length += AddToBuffer(&to, RWCOLDIST);
            length += AddToBuffer(&to, RTCOLDIST);
            length += AddToBuffer(&to, RTRIGFORCE);
            length += AddToBuffer(&to, RFORCEA);
            length += AddToBuffer(&to, RFORCEB);
            length += AddToBuffer(&to, RFORCE);
            length += AddToBuffer(&to, RFREQCHG);
            length += AddToBuffer(&to, RAMPSTART);
            length += AddToBuffer(&to, RAMPEND);
         }
      }
      else if(CurrentSetup.Actuator == AE)
      {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_6);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
      }
   }
   else 
   if(CurrentSetup.ControlLevel == LEVEL_ea)
   {
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_6);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
   }
   else /*--  WITHOUT ENCODER --*/ 
   if ( (CurrentSetup.ControlLevel == LEVEL_d) &&
        ( (CurrentSetup.Actuator != AED) ||
          (CurrentSetup.Actuator != AEF) ||
          (CurrentSetup.Actuator != MICRO) ) )
   { 
      length += AddToBuffer(&to, WELDCOLUMN_COUNT_6);
      length += AddToBuffer(&to, RTIME);
      length += AddToBuffer(&to, RPKPWR);
      length += AddToBuffer(&to, RENERGY);
      length += AddToBuffer(&to, RFREQCHG);
      length += AddToBuffer(&to, RAMPSTART);
      length += AddToBuffer(&to, RAMPEND);
   }
   else
   {
      if (BUCMenuRAM.VelocityReporting == TRUE) {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_14);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RTABSDIST);
         length += AddToBuffer(&to, RWCOLDIST);
         length += AddToBuffer(&to, RTCOLDIST);
         length += AddToBuffer(&to, RTRIGFORCE);
         length += AddToBuffer(&to, RFORCEA);
         length += AddToBuffer(&to, RFORCEB);
         length += AddToBuffer(&to, RFORCE);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
         length += AddToBuffer(&to, RVELOCITY_AEF);
      }
      else {
         length += AddToBuffer(&to, WELDCOLUMN_COUNT_13);
         length += AddToBuffer(&to, RTIME);
         length += AddToBuffer(&to, RPKPWR);
         length += AddToBuffer(&to, RENERGY);
         length += AddToBuffer(&to, RTABSDIST);
         length += AddToBuffer(&to, RWCOLDIST);
         length += AddToBuffer(&to, RTCOLDIST);
         length += AddToBuffer(&to, RTRIGFORCE);
         length += AddToBuffer(&to, RFORCEA);
         length += AddToBuffer(&to, RFORCEB);
         length += AddToBuffer(&to, RFORCE);
         length += AddToBuffer(&to, RFREQCHG);
         length += AddToBuffer(&to, RAMPSTART);
         length += AddToBuffer(&to, RAMPEND);
      }
   }


   return(length);
}

void StrCpyTwoToOneByte(SINT8 * to, SINT8 * from)
/****************************************************************************/
/*Description:-                                                             */
/* This function takes asian string and convert them to European string     */
/****************************************************************************/
{
      strcpy(to, from);
}

UINT16 LangStrLen(SINT8 * str)
/****************************************************************************/
/*Description:-                                                             */
/* This function emulates strlen function for Asian Language                */
/****************************************************************************/
{
   UINT16 length = 0;
   length = strlen (str);
   return length;
}

void StrCpyTwoBytes(SINT8 * to, SINT8 * from)
/****************************************************************************/
/*Description:-                                                             */
/* This function converts one byte into byte format for asian language      */
/****************************************************************************/
{
      strcpy(to, from);

}

void StrCatTwoBytes(SINT8 * to, SINT8 * from)
/****************************************************************************/
/*Description:-                                                             */
/* This function adds one byte into byte format for asian language      */
/****************************************************************************/
{
      strcat(to, from);

}

void LangStrCpy(SINT8 * to, SINT8 * from)
/****************************************************************************/
/*Description:-                                                             */
/* This function emulates strcpy function                                   */
/****************************************************************************/
{
      strcpy(to, from);
}

void LangStrCat(SINT8 * to, SINT8 * from)
/****************************************************************************/
/*Description:-                                                             */
/* This function emulates strcat function                                   */
/****************************************************************************/
{
      strcat(to, from);
}

BOOLEAN LangCheckNull(SINT8 * Line)
/****************************************************************************/
/*Description:-                                                             */
/* This function checks for null at the start of a string                   */
/****************************************************************************/
{
   BOOLEAN VGAIsNull = FALSE;
      if (Line[0] == 0)
         VGAIsNull = TRUE;
   
   return (VGAIsNull);
}

/*==========================================================================*/
/*************************************End************************************/
/*==========================================================================*/      
