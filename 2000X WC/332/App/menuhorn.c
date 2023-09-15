/* $Header:   D:/SWLab/VMdb/2000Series/App/MENUHORN.C_V   2.97   11 Nov 2009 20:04:44   pdwivedi  $ */
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
/*************************                         **************************/


/*--------------------------- MODULE DESCRIPTION -----------------------------

   Module name:

   Filename: menuhorn.c

   Function name:

                                   
 --------------------------------- REVISIONS ---------------------------------

 Revision # Date     Author  Description
 ========== ======== ======= ======================================================
 0                           Initial Version
 1.00       04/29/96 PJ      Modified for PSOS version
 2.00       05/14/96 PJ      Deleted menuhorn.h
                             Strings in menutext.c
 3.00       07-20-96 BEKymer Removed weld.h
 4.00       10-02-96 BEKymer chged palmbutton
 5.00       10/09/96 PhilJ   Changed Menus to type const. 
 5.10       10/27/96 PhilJ   Added System Pressure menu. 
 6.00       11/01/96 LAM     Added Pressure Type         
 6.10       12/02/96 PhilJ   Removed Press Start Switches and
                             Until Beep from Pressure menu.
 6.20       01/21/97 PhilJ   Changed actuator type from DONTCARE
                             to EP in HDForceSet2 & HDForceAct.
 2.11       07/23/97 PhilJ   Added menu if no encoder present
 2.12       08/01/97 PhilJ   Added Velocity menu.
 2.13       09.04.97 JBerman Replaced ADVANCED with NORMAL
 2.15       10/28/97 BJB     Includes <psos.h>, <prepc.h>, many other new header
                              files.
                             Created new function DoHornDown().
 2.16       11-4-97  BJB     Function DoHornDown() modified to return indication of
                              whether or not HD mode actually run.
 2.17       11-18-97 LAM     chged welddata to finalresults 
 2.18       01-05-98 BJB     Processes term data output, term alarm output messages.
                             Calls SetTermScreenWindowPos() for benefit of remote
                              terminal.
 2.19       01-12-98 BJB     Responds to ESTOP messages.
 2.20       04-22-98 BJB     Added def of HornDownFlag, was in STATE.H.
 2.21       04-24-98 BJB     Rewrote the whole thing.
 2.22       04-27-98 BJB     Continually updates display of SysPressure on AED
                              start screen.
                             Sets OldDistance, used to compute velocity, to ULS
                              clear position, which yields better results.
                             Only clears screen on exit if HD mode entered
                              (prevents screen blink if HD pressed & not ready).
                             For consistency, made HDPressure a "const".
 2.23       06-11-98 BJB     ULS clear waiting for PBs changed to cause manual mode
                              on AED.
                             Previous pressure test for manual mode deleted.
 2.24       06-17-98 BJB     Don't need call to DisplayCurrentPreset() when alarms
                              cleared, menu does this.
 2.25       06-18-98 BJB     Clears READY line when entering HD mode.
                             Reformatted some comments to conform to new standards.
 2.26       07-02-98 BJB     Added safety trigger check.
 2.27       07-21-98 BJB     Stops timer 2 when leaving HDWaitReady().
 2.28       08-05-98 BJB     Starts collecting velocity data at SVOn().
                             Records EQ3 alarm on AE if trigger before ULS clear.
 2.29       08-19-98 BJB     Modified to use new screen, terminal modules.
 2.30       08-28-98 BJB     Changed to progress toward object-oriented menus.
                             Added entry of trigger force, manual mode spec
                              changes.
 2.31       09-02-98 BJB     Uses new AlarmOff() function to turn ALARM LED, msg
                              off.
                             Clears alarms at PBs even if ONE_PB never received.
 2.32       10-28-98 BJB     Prevents ULS alarms on rapid ULS_ON to ULS_OFF
                              transitions in manual mode.
 2.33       10-30-98 BJB     If trigger lost in manual mode, doesn't wait for
                              Ready, just waits for trigger again.
                             Doesn't process Horn Down key in manual mode.
 2.34       11-02-98 BJB     Same changes as 2.33 but for AE instead of AED.
 2.35       12-07-98 BJB     Masks off new MESSAGE_NEW bit before using messages.
 2.36       04-26-99 OFI     Changed for Diab
 2.37       04/30/99 LAM     fixed compiler error
 2.37       05/10/99 LAM     eliminated DIAB warnings 
 2.38       06-04-99 JHenry  Included menus for AEF actuator, began other changes
 2.39       06-10-99 JHenry  Various updates to conform to code review action items.
 2.40       06-17-99 cmc     chg StrMH_18 to StrM2_41
 2.41       06-17-99 LAM     fixed asm commands for DIAB
 2.41.3.1   06-22-99 CMC     Initial horn down executable code and menus
 2.41.3.2   06-25-99 CMC     More horn down executable code and menus
 2.41.3.3   06-25-99 CMC     Correct one line regarding NewMessage
 2.41.3.4   06-25-99 CMC     A few more corrections
 2.41.3.5   06-25-99 CMC     Add prototype HDWaitReadyAEFOpenMenu
 2.41.3.6   06-28-99 CMC     Chg this module to match 6/25 SDS
 2.41.3.7   06-30-99 CMC     create stub copy of SetPV(*)
 2.41.3.8   07-06-99 CMC     change close menu w/in HornDownStartAEF
 2.41.3.9   07-08-99 CMC     remove date (22jun) comments.Fix KeepHornDown logic.
                             Comment-out EQ20 references.Fix asm code.Added blank
                             headers to functions missing headers(fill in later).
                             Move RunningPreset.TriggerForce = MinLimit.TriggerForce
                             from DoHornDown to HDWaitReadyAEFOpenMenu
 2.41.3.10  07-12-99 CMC     Add TestSequence[]
 2.41.3.11. 07-12-99 LAM     fixed control character in HDSetup definition
 2.41.3.12  07-20-99 cmc     Change MenuInfo HornDownWaitPartAEFMan = { HDUpperLSMenu 
                             to MenuInfo HornDownWaitPartAEFMan = { HDResultMenu 
                             Rmv KeepHornDown==TRUE from Trig Lost logic in ISR
                             Rmv KeepHornDown==TRUE from Trig Logic in GetHornDown
                             Restore RecordAlarm(EQ20)(RecalibrateActuator) 3 places 
                             Mv WorkingForceSet fromHDWaitReadyAEFOpenMenu 
                             to DoHornDown
 2.41.3.13  07-22-99 cmc     Mv WorkingForceSet, RTTransitionDist, RapidTraverseState,
                             and CurrentSetup.HornDownSpd to start of DoHornDown
                             Fill function prototypes for all "AEF" functions
 2.41.3.14  07-27-99 cmc     Fill function prototypes for seven more functions
                             Change HornDownWaitPartAEFMan = { HDResultMenu,
                             to HornDownWaitPartAEFMan = { HDUpperLSMenu,
                             Change HornDownWaitTrigAEFMan = { HDUpperLSMenu,
                             to HornDownWaitTrigAEFMan = { HDResultMenu,
                             Change HornDownWaitPartAEDMan = { HDResultMenu,
                             to HornDownWaitPartAEDMan = { HDUpperLSMenu,
                             Rename HDAEFCloseMenu HDStartAEFCloseMenu (to be consistent)
 2.41.3.15  07-29-99 JRJ     Changed HDWaitReadyAEFOpenMenu so conforms to design spec.
                             Changed if statement in HDAEFCloseMenu function to conform
                             to part 2 spec.
 2.44       08-03-99 JZ      added ERRORCODE for EQ20 alarm
 2.45       08-06-99 JZ      added RecordErrorCode, first arg. of SetPV typecasted to UINT16
 2.46       08-11-99 LAM     fixed Force for horn clamp = OFF to 999.9 lbs, do not update
                             PV Control Signal until exit pbs. 
 2.47       08-24-99 LAM     Added updatedistance before switching the horn down force
 2.48       08-25-99 LAM     use HDPosition instead of EncoderPos for rapid traverse  
 2.49       09-01-99 JLH     Incorporated horndown setup functions into main  horndown menu.
 2.50       09-02-99 LAM     default clamp to ON and rapid traverse to off.
 2.51       09-07-99 LAM     update user selected operating pressure when exiting.
 2.52       09-07-99 OFI     Commented out Action = NEXT_MENU inHDStartTimer.
 2.53       09-07-99 JZ      added  SystemPres80PSI and SystemPres60PSI flags
 2.54       09-07-99 OFI     Commented out all instances of alarm EQ23
 2.55       09-08-99 LAM     Update set minmaxvalue when exitting horn down
 2.56       09-20-99 LAM     Added safety check at part contact. Update minmaxvalues
                             when updating pressure changes, wait 5 seconds in ready
                             before updating pressure
 2.57       09-27-99 BEK     Removed calls to SetPV(HOLD_TO_HOME), SVOff() will do it
 2.58       10-11-99 LAM     changed averagepressure to home pressure
 2.59       10-11-99 LAM     fixed warnings  
 2.60       10-20-99 LAM     initialize trigger force to minimum(Horn Down Clamp=ON)
                             deleted HDStartAEFCloseMenu use HDCloseMenu instead
 2.61       10-28-99 LAM     updated per code review  
 2.62       11-15-99 LAM     fixed horn down downspeed at idle
 2.63       11-17-99 LAM     use .25 sec define from ready.h 
 2.64       12-04-99 LAM     added clearpressurearray when entering ready                     
 2.64.2.1   12-09-99 JZ      deleted HDTrigForce, changed in HDStartMenu entry to HDTriggerToggle
                             modified HDTriggerToggle to LEVEL_d and AED|AEF act. type
                             made horndown clamp off working
 2.65       12-20-99 JZ      fixed backward compatibility  
 2.66.6.1   02-08-99 JZ      removed DVS, added Mask1, Cond1, Mask2, Cond2 
 2.66.6.2   02-23-00 OFI     removed 'User experience level' from menu strucutures  
 2.67       04-06-00 JZ      merged Lang to trunk    
 2.68       05-26-00 SCM     Checked in for testing by Laura, John.             
 2.69       06-13-00 BEK     Removed AlarmsReset as a condition in case UPPER_LIMIT_OFF
                             and case TIMER_EXPIRED.  This fix allows entry into
                             horndown even if there is an alarm.  This is the same quick
                             fix that was added to ver 7.02 at the last minute.
 2.70       06-28-00 BEKymer Changed all MODEL to LEVEL
 2.71       08-18-00 LAM     deleted unused extern
 2.72       01-10-01 BEKymer Added argument to TEXT function call
 2.71.1.0   06-19-01 LAM     added test for trigger lost with an ae actuator.
 2.71.2.1   06-20-01 BEK     Added test for lifting off the part in HornDownISR
 2.71.2.2   06-20-01 BEK     Make upward distance .2" instead of .25" and change alarm
                              to trigger lost instead of recal. 
 2.71.2.3   08-04-03 JOY     Added HornDown for QVGA, 'QVGADoHornDown()'.
 2.71.2.4   08-27-03 JOY     Alarm when Horn is not clamped, has been solved.
 2.71.2.5   09-04-03 JOY     Button width of 'QVGAHDStartMenu1' is increased.
                             Bottom status screen text is centered.
 2.71.2.5   09-18-03 JOY     Added the 'Exit' Button which brings the horn Up.
 2.71.2.6   09-26-03 JOY     HornDown Screen is exited properly when alarm button is 
                             -pressed from keypad screen. 
 2.71.2.9   09-30-03 JOY     Bottom text is centered.
 2.71.2.10  10-16-03 JOY     MiddleSeg. Erased by QVGA ROM image.
 2.71.2.11  10-23-03 JOY     Replaced 'TheMainMenu' by 'QVGATheMainMenu'.
 2.71.2.12  10-24-03 JOY     Exit button is replaced by Retract.
 2.71.2.13  12-03-03 JOY     System pres: not displayed in AE Act.
 2.74       12-04-03 BEKymer Merged 2.73 & 2.71.2.13 to create 2.74 for
                              Ver9.00b build
 2.75       12-05-03 BEKymer Merged 2.73 & 2.71.2.14 to create 2.75 for
                              Ver9.00b build 
 2.76       03-12-04 VSharma Changed 'Inp.ECycleAbort' to ECycleHistFlag.
 2.77       05-17-04 VSharma Removed extern of unused strings.
 2.78       09-14-04 JOY     Updated CurrentPreset.Verified flag in UpdateOperatingPressure().
 2.79       09-15-04 JOY     HornDown is not done in HandHeld mode, just beeps.
 2.80       12-30-04 LAM     Temporarily disabled DOOROPEN(SBEAM build)
 2.81       07-25-05 Bwadia  VGA horn down support added  
 2.82       08-19-05 Bwadia  VGAHDPressStart VGATEXT object coordinates changed
 2.83       01-03-06 Bwadia  Param IDs added to VGABOTTOMHALF object.
                             Modified for tracker issue 3972
 2.84       01-10-06 LAM     modified zeroing the encoder
 2.85       08-10-06 LAM     Velocity is only shown on an AEF when reporting is enabled
 2.86       12-22-06 NHAhmed Changes made to dissable welding while changing the variables 
                             in Horn Down menu.
 2.87       01-31-07 NHAhmed Changes related to Changed Structure variables of CHOICE and TOGGLE.
 2.88       04-16-07 NHAhmed Added Warning in Horn Down Result Menu.
 2.89       05-04-07 NHAhmed Resized Retract Button and Warning in Horn Down(Tracker #4108).
 2.90       10-22-07 NHAhmed Changes done for LangTest phase 0
 2.91       04-14-08 NHAhmed Replicted Function VGADoHorndown() and Modified some functions.
 2.92       08-26-08 NHAhmed Modified a function DoHornDownFunc(). 
 2.93       09-04-08 YGupta  CleanUp for LangTest Project.
 2.94       09-09-08 NHAhmed CleanUp for multi-language support.
 2.95       09-10-09 BEkymer Add new define MICRO where needed
 2.96       09-22-09 YGupta  Modified code so that HD will exit only for Reset Required Alarms 
										and for Tracker REQ00475. 
 2.97       11-11-09 Pdwivedi Add new function ResetHDAlarms for Horn Down.

 

----------------------------------------------------------------------------*/

/*----------------------------- INCLUDE FILES ------------------------------*/

#include <psos.h>
#include "actnvram.h"
#include "string.h"
#include "portable.h"
#include "menu.h"
#include "menu1.h"
#include "param.h"
#include "preset.h"
#include "weld_obj.h"
#include "genrlmsg.h"
#include "ck_qsend.h"
#include "digout.h"
#include "beep.h"
#include "led.h"
#include "opcodes.h"
#include "display.h"
#include "keypad.h"
#include "fpk_task.h"
#include "getmsg.h"
#include "fmtstrs.h"
#include "state.h"
#include "statedrv.h"
#include "alarms.h"
#include "alsetup.h"
#include "ready.h"
#include "selctkey.h"
#include "menuhorn.h"
#include "util.h"
#include "mansensr.h" /* SetPV */
#include "encoder.h"
/* For QVGA support */
#include "inports.h"
#include "qvga_task.h"
#include "qvgamenu.h"
#include "touchmsg_qvga.h"
#include "DrawScrn.h"
#include "command.h"

void InitVelocityData(void);   /* These prototypes aren't in any .H files */
void CollectVelocityData(SINT32 NewDistance);
SINT32 CalculateVelocity(void);

void QVGAShowEstopMessageOn(void);
void QVGAShowEstopMessageOff(void);
void DrawAlarmButton(void);
BOOLEAN ProcessAlarmButton(TOUCH_HANDLER_MSG *TouchScrnPos);
extern UINT16 DisplayNextMenu;
extern BOOLEAN StateMachineDisabled;
/*------------------------------- LOCAL DEFINES ----------------------------*/

#define NEXT_MSG       0   /* No additional action, just get next message */
#define EXIT_HD        1   /* Causes exit from HD mode */
#define NEXT_MENU      2   /* Within HD mode, displays next screen */
#define DISPLAY_UPDATE 3
#define SCROLL_MENU    4
#define RESTART_HD     5

#define PREREADY_MSG_WAIT_TIME   50    /* Max time to wait for an event in */
                                       /* PREREADY before checking         */
                                       /* conditions again.                */

#define HD_UPDATE_RATE        250       /* Ms between screen updates */

#define MAX_TRIGGER_LOST_TIME 60000    /* Don't tell user when trigger lost */
                                       /* if more time than this. */

#define NUM_TIMERS   4      /* Only 16 timers max allowed in message format */

   /* Define event ID codes.  These guarantee that a TIMERx_EXPIRED message */
   /* was really caused by what we think it was.  Without IDs, some */
   /* function could set up a timer which expires just as the function */
   /* decides to exit for another reason.  A TIMER_EXPIRED message will go */
   /* in the queue, to be read out by the next function, which may think */
   /* the messsage means something else.  IDs allow function to identify */
   /* its own events so this won't happen. */

#define TRIGGER_LOST_EVENT 1
#define HD_DISPLAY_UPDATE  2
#define PBS_STUCK_EVENT    3
#define NO_UL_EVENT        4
#define PB_SPLIT_EVENT     5
#define NO_UL_CLEAR_EVENT  6
#define HD_CHECK_READY     7

   /* The following #defines specify in more detail what caused a change */
   /* from one HD screen to another. This information is passed to the */
   /* CloseMenu() routine for each screen. */

#define HD_RESTART   0     /* Something happened, want to restart HD mode */
#define HD_MANUAL    1     /* ULS clear before PBs, go to manual mode */
#define HD_ADVANCE   2     /* Conditions for advance to next screen met */
#define HD_RESULT    3     /* Skip ahead to result screen */

#define SYS_PRESS_ITEM  1         /* Item # of system pressure on start menus   */
#define FORCENOTREACHED 9999      /* This is used to keep horn down clamp = OFF */
                                  /* repeatadly checking system pressure        */
#define MAX_DOWN_SPEED 100                                  


#define PSOS_TIMEOUT 0x01


/*--------------------------- LOCAL TYPE DECLARATIONS -----------------------*/

struct HornDownState
{
   UINT16   OnePB       : 1;
   UINT16   BothPB      : 1;
   UINT16   Estop       : 1;
   UINT16   OnPart      : 1;
   UINT16   Trigger     : 1;
   UINT16   DoorOpen    : 1;
   UINT16   uls         : 1;
   UINT16   ECycleAbort : 1;
   UINT16   PwrOff      : 1;
   UINT16   Unused      : 7;
};

struct MenuInfo;

union MResults
{
   struct
   {
      UINT32 ExitKey;
   } ExitHD;
   struct
   {
      UINT32 CloseParam;
      struct MenuInfo *NextMenu;
   } NextMenu;
   struct
   {
      UINT32 Devices;
   } ScrollMenu;
   struct
   {
      UINT16 StartItem;
      UINT16 EndItem;
   } DisplayUpdate;
};

struct MenuInfo
{
   UINT16   FullMenuID;              /* Points to all items on menu */
   void     (*OpenMenu)( struct MenuInfo *Menu);
   UINT16   (*ProcessMessage)( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
   UINT16   (*ChrReceivedHandler)( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
   UINT16   (*SelectKeyHandler)( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
   UINT16   (*ControlMessageHandler)( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
   UINT16   (*SpecialMessageHandler)( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
   void     (*CloseMenu)( UINT32 CloseParam );
};

struct HornDownTimer
{
   UINT32 Count;        /* Duration to time for */
   UINT16 Id;           /* Distinguishing ID to send with timeout msg */
};

UINT16 HDRTAlreadySetFlag; /* the real RTAlreadySetFlag is in ready.c */
BOOLEAN QVGAHornDown = FALSE;
BOOLEAN QVGAHDAlarm = FALSE;
BOOLEAN QVGAExitHDMenu = FALSE;
BOOLEAN VGAHornVarEntry = FALSE;
UINT16 HDMenuID=0;
/*------------------------------ EXTERNAL DATA -----------------------------*/

extern BUCMENU_800 BUCMenuRAM;
extern UINT16 PartContactFlag;       
extern INBITS Inp;
extern UINT16 ExternalCycleAbortGoneFlag;
extern UINT16 AlarmCounter;
extern UINT16 StopSamplingFlag;
extern BOOLEAN ECycleHistFlag;
extern UINT8  AlarmDetectedFlag;
extern UINT8  AETrigger;
extern enum  WELDSTATES WeldState;
extern BOOLEAN VGA_ReadyFlag;
extern BOOLEAN ReadyFlag;


extern SETUPS_Ver800 MaxLimit;
extern SETUPS_Ver800 MinLimit;
extern SETUPS_Ver800 RunningPreset, CurrentPreset;
extern CONFIGSETUP CurrentSetup;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;

extern SINT16 MenuCounter;
extern SINT32 CurrentPressure;
extern SINT32 EncoderPos;
extern SINT32 ActualHoldTime;
extern SINT32 CurrentForce;            /* Actual horndown force */  
extern SINT32 Distance1;               /* Distance 1-3 used to determine part contact*/
extern SINT32 HomePressure;

extern UINT32 WmgrQid;
extern UINT16 SystemPressureCheck;      
extern UINT16 PresetNeedsToBeUpdated;

extern ESTOP_STATE EStopState;
extern UINT32 ReadOnlyTimer;
extern UINT8 MessageUseFlags[NUM_MSG_USE_FLAGS];
extern REDRAW_SEG  RedrawSeg;         // Indicate which part of Screen has to be- 
                                      // Refreshed.
extern QVGA_MENU_INFO MenuLevelInfo[];
extern BUTTON_STATE TouchedButtonState;
extern UINT32 QvgaQid;                 /* QVGA queue ID */
extern BOOLEAN VGAEstopOn;
extern BOOLEAN VGAEstopOff;
extern BOOLEAN VGAEstopReset; 
extern BOOLEAN UserIOAlarmMenu;
extern BOOLEAN StateMachineDisabled;
void  ExitMenuAndEnableWeld (void);
extern UINT32 NackError, ErrorResponseMinLimit, ErrorResponseMaxLimit;


/*------------------------------- GLOBAL DATA ------------------------------*/
/*                       (scope is global to ALL files)                     */

BOOLEAN HornDownFlag = FALSE;     /* When TRUE disables state machine */
UINT16 SystemPres60PSI;
UINT16 SystemPres80PSI;
UINT16 VGAAction;
struct MenuInfo VGAHDMenu;
union  MResults VGAMessageResults;


/*----- TEMPORARY FUNCTION PROTOTYPES -----*/

UINT16 Downspeed;

/*-------------------------- LOCAL FUNCTION PROTOTYPES ---------------------*/

void CheckForRapidTraverse(void);
static void HDProcessEstop(void);
static void UpdateOperatingPressure(void);
static void GetHornDownState( struct HornDownState *CurrentState );
static HDStartTimer( UINT8 Timer, UINT32 Count, UINT16 Id );

void StdOpenMenu( struct MenuInfo *Menu);
UINT16 StdProcessMessage( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 StdChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDAESelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDAEDSelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDAEFSelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 NoSelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 StdControlMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 StdSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

void StdCloseMenu( UINT32 CloseParam );
void HDCloseMenu( UINT32 CloseParam );

void HDWaitReadyAEOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitReadyAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitPBsAEOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitPBsAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitPBsAECloseMenu( UINT32 CloseParam );
void HDWaitULSAEOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitULSAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitULSAECloseMenu( UINT32 CloseParam );
UINT16 HDWaitTrigAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitTrigAECloseMenu( UINT32 CloseParam );
UINT16 HDResultAEChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

void HDResultCloseMenu( UINT32 CloseParam );
UINT16 HDWaitTrigAEManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDResultAEManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitReadyAEDOpenMenu( struct MenuInfo *Menu);
void HDWaitReadyAEFOpenMenu( struct MenuInfo *Menu);

UINT16 HDWaitReadyAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDWaitReadyAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitPBsAEDAEFOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitPBsAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitPBsAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

void HDWaitULSAEDAEFOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitULSAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitULSAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
void HDWaitULSAEDAEFCloseMenu( UINT32 CloseParam );
void HDWaitPartAEDAEFOpenMenu( struct MenuInfo *Menu);
UINT16 HDWaitPartAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitPartAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

void HDWaitPartAEDCloseMenu( UINT32 CloseParam );
void HDWaitPartAEFCloseMenu( UINT32 CloseParam );

void HDWaitTrigAEDAEFOpenMenu( struct MenuInfo *Menu);

UINT16 HDWaitTrigAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitTrigAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

void HDWaitTrigAEDAEFCloseMenu( UINT32 CloseParam );
void HDResultAEDAEFOpenMenu( struct MenuInfo *Menu);
void HDWaitPartAEDAEFManOpenMenu( struct MenuInfo *Menu);

UINT16 HDResultAEDChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDResultAEFChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDResultAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDResultAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDResultAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDWaitPartAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitPartAEFManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDWaitTrigAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitTrigAEFManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDResultAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );
UINT16 HDResultAEFManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults );

UINT16 HDWaitReady( UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitPBs( UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitULS( UINT32 Message, union MResults *MessageResults );
UINT16 HDWaitPart( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual );
UINT16 HDWaitTrigger( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual );
UINT16 HDShowResult( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual );
void HDSplitMessage( UINT32 *Message, UINT16 *Timer, UINT16 *Id );
void ProcessHDButtonPress1(void); 
void ProcessHDButtonPress2(void); 
void ProcessHDButtonPress3(void); 
void ProcessRvtsMenuTaskMsg(UINT32 RvtsMessage);
void VGAProcessHornDownMsg (void);

/*--------------------------- PRIVATE GLOBAL DATA --------------------------*/
/*                      (scope is global to THIS file)                      */

STR HDBottomHalfBufName[QVGA_LINESIZE];

STR *Str_HDBottomHalf[] =   { HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName,
                              HDBottomHalfBufName };

static BOOLEAN QVGAGnrlAlarmStateBeforeEstop;
static BOOLEAN QVGAEstopFlag = FALSE;
static struct HornDownTimer HornDownEventTimer[NUM_TIMERS];
static struct HornDownState LastHDState; /* Compares to this, sends msgs */
UINT16 HDShowPressure;            /* Controls display of sys pressure */
UINT16 HDShowVelocity;            /* Controls display of velocity item */
UINT16 HDShowForce;               /* Controls display of force item */
static BOOLEAN HDCollectVelData,HDReadyState = TRUE;
SINT32 HornDownVelocity;
SINT32 HDPosition;             /* Same as EncoderPos but never < 0 */
static SINT32 SaveTriggerForce;       /* Save trig force for welding here */
SINT32 WorkingForceSet;        /* Temporary target pressure         */   

SINT32 RTTransitionDist;       /* Rapid Traverse Transition distance */

UNION_BOOL_UINT16 KeepHornDown;           /* TRUE to keep horn down after PB release */
UINT16 RapidTraverseState;            /* TRUE for rapid traverse */

static MENUEND endlistH = { TRUE };
static GENERIC_MSG WeldMsgOut;




const struct MenuInfo HornDownStartAE = {  REFRESH_MENU_AE, 
                                           HDWaitReadyAEOpenMenu, 
                                            StdProcessMessage,
                                           StdChrReceivedHandler,
                                           HDAESelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitReadyAESpecialMessageHandler,
                                           HDCloseMenu
                                         };


const struct MenuInfo HornDownWaitPBsAE = { REFRESH_MENU_AE,  
                                           HDWaitPBsAEOpenMenu, 
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           HDAESelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPBsAESpecialMessageHandler,
                                           HDWaitPBsAECloseMenu
                                         };

const struct MenuInfo HornDownWaitULSAE = { REFRESH_MENU_AE, 
                                           HDWaitULSAEOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitULSAESpecialMessageHandler,
                                           HDWaitULSAECloseMenu
                                         };

const struct MenuInfo HornDownWaitTrigAE = { REFRESH_MENU_AE,
                                           StdOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitTrigAESpecialMessageHandler,
                                           HDWaitTrigAECloseMenu
                                         };

const struct MenuInfo HornDownResultAE = { RESULT_MENU_AE, 
                                           StdOpenMenu,
                                           StdProcessMessage,
                                           HDResultAEChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDResultAESpecialMessageHandler,
                                           HDResultCloseMenu
                                         };

const struct MenuInfo HornDownWaitTrigAEMan = { RESULT_MENU_AE, 
                                           StdOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitTrigAEManSpecialMessageHandler,
                                           HDWaitTrigAECloseMenu
                                         };

const struct MenuInfo HornDownResultAEMan = { RESULT_MENU_AE, 
                                           StdOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDResultAEManSpecialMessageHandler,
                                           HDResultCloseMenu
                                         };

const struct MenuInfo HornDownStartAED = { REFRESH_MENU_AED, 
                                           HDWaitReadyAEDOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           HDAEDSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitReadyAEDSpecialMessageHandler,
                                           HDCloseMenu
                                         };

const struct MenuInfo HornDownWaitPBsAED = { REFRESH_MENU_AED, 
                                           HDWaitPBsAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           HDAEDSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPBsAEDSpecialMessageHandler,
                                           HDCloseMenu
                                         };


const struct MenuInfo HornDownWaitPBsAEF = { REFRESH_MENU_AEF1,
                                           HDWaitPBsAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           HDAEFSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPBsAEFSpecialMessageHandler,
                                           HDCloseMenu
                                         };

const struct MenuInfo HornDownWaitULSAED = { REFRESH_MENU_AED, 
                                           HDWaitULSAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitULSAEDSpecialMessageHandler,
                                           HDWaitULSAEDAEFCloseMenu
                                         };

const struct MenuInfo HornDownWaitULSAEF = { REFRESH_MENU_AEF1, 
                                           HDWaitULSAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitULSAEFSpecialMessageHandler,
                                           HDWaitULSAEDAEFCloseMenu
                                         };

const struct MenuInfo HornDownWaitPartAED = { RESULT_MENU,
                                           HDWaitPartAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPartAEDSpecialMessageHandler,
                                           HDWaitPartAEDCloseMenu
                                         };

const struct MenuInfo HornDownWaitPartAEF = { REFRESH_MENU_AEF2, 
                                           HDWaitPartAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPartAEFSpecialMessageHandler,
                                           HDWaitPartAEFCloseMenu
                                         };

const struct MenuInfo HornDownWaitTrigAED = { RESULT_MENU, 
                                           HDWaitTrigAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitTrigAEDSpecialMessageHandler,
                                           HDWaitTrigAEDAEFCloseMenu
                                         };

const struct MenuInfo HornDownWaitTrigAEF = { RESULT_MENU, 
                                           HDWaitTrigAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitTrigAEFSpecialMessageHandler,
                                           HDWaitTrigAEDAEFCloseMenu
                                         };

const struct MenuInfo HornDownResultAED = { RESULT_MENU,
                                           HDResultAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           HDResultAEDChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDResultAEDSpecialMessageHandler,
                                           HDResultCloseMenu
                                         };

const struct MenuInfo HornDownResultAEF = { RESULT_MENU, 
                                           HDResultAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           HDResultAEFChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDResultAEFSpecialMessageHandler,
                                           HDResultCloseMenu
                                         };

const struct MenuInfo HornDownWaitPartAEDMan = { REFRESH_MENU_AEF2,
                                           HDWaitPartAEDAEFManOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPartAEDManSpecialMessageHandler,
                                           HDWaitPartAEDCloseMenu
                                         };

const struct MenuInfo HornDownWaitPartAEFMan = { REFRESH_MENU_AEF2,
                                           HDWaitPartAEDAEFManOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitPartAEFManSpecialMessageHandler,
                                           HDWaitPartAEFCloseMenu
                                         };

const struct MenuInfo HornDownWaitTrigAEDMan =  { RESULT_MENU,
                                           HDWaitTrigAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitTrigAEDManSpecialMessageHandler,
                                           HDWaitTrigAEDAEFCloseMenu
                                         };

const struct MenuInfo HornDownWaitTrigAEFMan = { RESULT_MENU ,
                                           HDWaitTrigAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitTrigAEFManSpecialMessageHandler,
                                           HDWaitTrigAEDAEFCloseMenu
                                         };


const struct MenuInfo HornDownResultAEDMan =   { RESULT_MENU,
                                           HDResultAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDResultAEDManSpecialMessageHandler,
                                           HDResultCloseMenu
                                         };

const struct MenuInfo HornDownResultAEFMan =   { RESULT_MENU,
                                           HDResultAEDAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           NoSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDResultAEFManSpecialMessageHandler,
                                           HDResultCloseMenu
                                         };

const struct MenuInfo HornDownStartAEF = { REFRESH_MENU_AEF1,
                                           HDWaitReadyAEFOpenMenu,
                                           StdProcessMessage,
                                           StdChrReceivedHandler,
                                           HDAEFSelectKeyHandler,
                                           StdControlMessageHandler,
                                           HDWaitReadyAEFSpecialMessageHandler,
                                           HDCloseMenu
                                         };

/*--------------------------------- CODE -----------------------------------*/


static void HDProcessEstop(void)
/****************************************************************************/
/*                                                                          */
/* Deals with ESTOP press.  Message "Emergency Stop" blinks on the screen   */
/* while the code waits for the ESTOP_RELEASED message.  All other messages */
/* are discareded except for POWER_OFF, which exits.  Note that if we ever  */
/* allow ESTOP to return to HD mode, we have to return something to exit on */
/* power-off!                                                               */
/*                                                                          */
/* This function also sets general alarm output and increments counter.     */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN Quit;
   BOOLEAN GeneralAlarmStateBeforeEstop;
   UINT32 NewKey;
   UINT32 TimeUntilBlink;

   GeneralAlarmStateBeforeEstop = CheckGeneralAlarmFlag();

   CurrentSetup.GenAlarmCount++;
   SetGeneralAlarm();
   SVOff();
   Quit = FALSE;

   do
   {
      ShowEstopMessageOn();
      TimeUntilBlink = MS_TO_TICKS( 200*4 );
      do
      {
         TimeUntilBlink = WaitMessage( TimeUntilBlink );
         if (TimeUntilBlink)     /* Pause interrupted by incoming message */
         {
            NewKey = RcvMsg(0) & ~MESSAGE_NEW;

            if ((NewKey == ESTOP_RELEASED) || (NewKey == POWER_OFF))
               Quit = TRUE;
         }

      } while (TimeUntilBlink && !Quit);

      ShowEstopMessageOff();

      if (!Quit)
      {
         TimeUntilBlink = MS_TO_TICKS( 200*4 );
         do
         {
            TimeUntilBlink = WaitMessage( TimeUntilBlink );
            if (TimeUntilBlink)
            {
               NewKey = RcvMsg(0) & ~MESSAGE_NEW;

               if ((NewKey == ESTOP_RELEASED) || (NewKey == POWER_OFF))
                  Quit = TRUE;
            }

         } while (TimeUntilBlink && !Quit);
      }

   } while (!Quit);

   if (!GeneralAlarmStateBeforeEstop)
      ClearGeneralAlarm();
}

void HornDownISR(void)
/****************************************************************************/
/*                                                                          */
/* This function provides 1ms interrupt support for Horn Down Mode.         */
/* includes checking for important events (ESTOP, palmbuttons, cycle abort, */
/* Tests for important events are performed and messages are sent to the    */
/* main Horn Down code in the menu task when something happens.             */
/*                                                                          */
/* Events which currently cause message output:                             */
/*                                                                          */
/*   Change in PB state                                                     */
/*   Change in ESTOP state                                                  */
/*   Timeout of event timer                                                 */
/*   Change in state of external cycle abort                                */
/*   Change in trigger state                                                */
/*   Change in DoorOpen state                                               */
/*   Change in ULS state                                                    */
/*                                                                          */
/****************************************************************************/
{
   struct HornDownState CurrentHDState;
   UINT32 Timer;
   UINT16 *Last, *Current;             /* Need this to compare structs */

   if (EncoderPos < 60000)      /* Don't display - encoder positions */
      HDPosition = EncoderPos;
   else
      HDPosition = 0;

   /* The next if () block is necessary because GetInputData() won't turn */
   /* off ECycleAbort bit.  Don't know why this is, but if it's ever */
   /* fixed this code can be removed. */

   if (ExternalCycleAbortGoneFlag)
   {
      ECycleHistFlag = FALSE;
      ExternalCycleAbortGoneFlag = FALSE;
   }

   /* Important safety check: If horn moves more than TRIGGERLOSTDISTANCE   */
   /* and still hasn't built up 35 lbs force, clear Trigger, turn off valve */
   /* so horn must come up (even if other code is not working right), send  */
   /* message to menu task telling it to quit result screen. */

   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == MICRO) ) {
      /* test at part contact */
      if ( (CurrentForce < TRIGGERLOSTFORCE) && (PartContactFlag == TRUE) &&
           (EncoderPos > (Distance1 + (SINT32) TRIGGERLOSTDISTANCE)) ) 
      {
         SVOff();
         PartContactFlag = FALSE;
         Inp.Trigger = FALSE;
         SendMsg( BAD_TRIGGER );
      }   
      /* Test for lifting off the part */
      if (EncoderPos < (Distance1 - (SINT32) NEGTRIGGERLOSTDISTANCE) )
      {
         SVOff();
         PartContactFlag = FALSE;
         Inp.Trigger = FALSE;
         SendMsg( TRIGGER_OFF );
      }   

   }

   /* The only routine to call GetHornDownState() is this one. */
   /* Within HornDownISR(), CurrentHDState is an automatic variable. */

   GetHornDownState( &CurrentHDState );   /* Get current system state */

   Last = (UINT16*)&LastHDState;
   Current = (UINT16*)&CurrentHDState;

   if (*Current != *Last)                 /* Something changed, send msg */
   {
      if ((CurrentHDState.OnePB != LastHDState.OnePB) ||
       (CurrentHDState.BothPB != LastHDState.BothPB))
      {
         if (!CurrentHDState.OnePB && !CurrentHDState.BothPB)
            SendMsg( NO_PB_PRESSED );
         else if (CurrentHDState.OnePB && !CurrentHDState.BothPB)
            SendMsg( ONE_PB_PRESSED );
         else if (CurrentHDState.BothPB)
            SendMsg( BOTH_PB_PRESSED );
      }
      if (CurrentHDState.Estop != LastHDState.Estop)
      {
         if (CurrentHDState.Estop)
            SendMsg( ESTOP_PRESSED );
         else
            SendMsg( ESTOP_RELEASED );
      }
      if (CurrentHDState.OnPart != LastHDState.OnPart)
      {
         if (CurrentHDState.OnPart)
            SendMsg( PART_CONTACT );
      }
      if (CurrentHDState.Trigger != LastHDState.Trigger)
      {
         if (CurrentHDState.Trigger)
            SendMsg( TRIGGER_ON );
         else
            SendMsg( TRIGGER_OFF );
      }
	  
      if (CurrentHDState.DoorOpen != LastHDState.DoorOpen)
      {
         if (CurrentHDState.DoorOpen)
            SendMsg( DOOR_OPEN );
         else
            SendMsg( DOOR_CLOSED );
      }
      if (CurrentHDState.uls != LastHDState.uls)
      {
         if (CurrentHDState.uls)
            SendMsg( UPPER_LIMIT_ON );
         else
            SendMsg( UPPER_LIMIT_OFF );
      }
      if (CurrentHDState.ECycleAbort != LastHDState.ECycleAbort)
      {
         if (CurrentHDState.ECycleAbort)
            SendMsg( ECYCLE_ABORT_ON );
         else
            SendMsg( ECYCLE_ABORT_OFF );
      }
      if (CurrentHDState.PwrOff != LastHDState.PwrOff)
      {
         if (CurrentHDState.PwrOff)
            SendMsg( POWER_OFF );
      }
      LastHDState = CurrentHDState;
   }
   /* Check timers and send timeout messages if necessary */

   for (Timer = 0; Timer < NUM_TIMERS; Timer++)
   {
      if (HornDownEventTimer[Timer].Count)   /* If nonzero, timer is active */
      {
         if (!(--(HornDownEventTimer[Timer].Count)))
            SendMsg( TIMER_EXPIRED + (Timer << TIMER_NUM_BITPOS) +
             (HornDownEventTimer[Timer].Id << TIMER_ID_BITPOS));
      }
   }
   if(HDReadyState == TRUE)
   {
      /* need the aef and check every 1/4 second at ready */
      if ((CurrentSetup.Actuator == AEF) && ((SystemPressureCheck--) <= 0 ))
      {
         SystemPressureCheck = PRESSURE_CHECK_TIME1;
         UpdatePressureOffset();
         UpdateOperatingPressure();
      }   
   }
   if (HDCollectVelData)         /* Collect velocity data if desired */
   {
      CollectVelocityData( HDPosition );
      CheckForRapidTraverse(); 
   }      
}

void CheckForRapidTraverse(void)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   if((RapidTraverseState & BIT0) == BIT0)
   {
      if((HDPosition >= RTTransitionDist) && (PartContactFlag == FALSE)
            && (HDRTAlreadySetFlag == FALSE))
      {
      SetPV((UINT16)CurrentSetup.HornDownSpd,RT_TO_DWNSPD);
      HDRTAlreadySetFlag = TRUE;
      }
   }
}

static void GetHornDownState( struct HornDownState *CurrentState )
/****************************************************************************/
/*                                                                          */
/* Fulfills logic required to separate door and trigger. On AED or AEF,     */
/* uses ULS to aid in decision. Also fills in the HornDownState struct      */
/* with info from current inputs.                                           */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN TrigState;


   CurrentState->OnePB = Inp.OnePB;
   CurrentState->BothPB = Inp.BothPB;
   CurrentState->Estop = Inp.Estop;

   /* Trigger & door open functions are on the same bit on AE actuator.  */
   /* The value of AETrigger reflects the state of this bit.  If at upper */
   /* limit, AETrigger is assumed to indicate the door status; if not at */
   /* upper limit, it's assumed to indicate the trigger status. */

   if (CurrentSetup.Actuator == AE)
   {
      if (!AETrigger)          /* If bit is off, can't have trigger or door */
      {
         CurrentState->Trigger = FALSE;
         CurrentState->DoorOpen = FALSE;
      }
      else
      {
         if (Inp.uls)                       /* If at U.L., it's the door */
         {
            CurrentState->Trigger = FALSE;
// sbeam level 1 build            CurrentState->DoorOpen = TRUE;
            CurrentState->DoorOpen = FALSE;

         }
         else                               /* If not at U.L., it's trigger */
         {
            CurrentState->Trigger = TRUE;
            CurrentState->DoorOpen = FALSE;
         }
      }
   }
   else     /* For non-AE actuators */ 
   {
      TrigState = Inp.Trigger;   /* Initially use same as Inp.Trigger */
      
      if (Inp.uls)      /* If at upper limit, can't have trigger */
      {
         Inp.Trigger = FALSE;
         TrigState = FALSE;
      }
      else
      {                       /* must have no ULS to read CurrentForce */

         /* Check for trigger lost.  Will clear trigger in HD state info */
         /* if force falls below MinLimit, but won't clear Inp.Trigger. */
         /* This allows force back over MinLimit to turn trigger back on. */
         /*  Code receiving TRIGGER_OFF messages will deal with brief */
         /* losses of trigger. */

         if (Inp.Trigger)
         {
				if (CurrentForce < MinLimit.TriggerForce)
					TrigState = FALSE;
         }
      }
      CurrentState->Trigger = TrigState;
      CurrentState->DoorOpen = Inp.DoorOpen;
   }

   if (HDCollectVelData)      /* Test flag that will indicate whether */
   {                          /* or not horn is on the part */
      if (PartContactFlag)
         CurrentState->OnPart = TRUE;
      else
         CurrentState->OnPart = FALSE;
   }
   else
      CurrentState->OnPart = FALSE;

   CurrentState->uls = Inp.uls;
   CurrentState->ECycleAbort = ECycleHistFlag;
   CurrentState->PwrOff = Inp.PwrOff;
   CurrentState->Unused = 0;        /* Same state always returns same code */
}

static HDStartTimer( UINT8 Timer, UINT32 Count, UINT16 Id )
/****************************************************************************/
/*                                                                          */
/* Starts a timer to time an event.  The HornDownISR() will decrement any   */
/* nonzero timer, and will send an event message if the timer expires.  An  */
/* ID code, supplied here, is also sent with the event message, so that if  */
/* an event message was sent but not read by the function that set up the   */
/* timer, a later function that reads the message will know to discard it.  */
/*                                                                          */
/* Parameters:                                                              */
/*                                                                          */
/*    Timer - Which timer to use                                            */
/*    Count - Time before message send, in ms                               */
/*    Id    - ID code.  May be anything as long as it's unique              */
/*                                                                          */
/****************************************************************************/
{
   UINT16 old_mode;

   /* Must disable interrupts here while new value & id are being assigned */
   /* to the timer, otherwise, if timer expires with half of data written */
   /* (either just Id or with just new Count), ID for wrong event will be */
   /* sent.  It's probably safe to leave ints on and write new value first, */
   /* since it's unlikely that it will count all the way down before next */
   /* line of code gets to run, but we're being ultra-conservative here. */

   asm(" move.w sr,d0\n ori.w #$700,sr \n move.w d0,_old_mode" );

   HornDownEventTimer[Timer].Count = Count;
   HornDownEventTimer[Timer].Id = Id;

   asm( " move.w _old_mode,d0\n move.w d0,sr" );
}

void StdOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to open a menu. Given a menu object, it figures out */
/* which of the menu items that could potentially appear on this menu need  */
/* to be displayed now, and saves a count of how many items this is in the  */
/* menu object. Also, the current position on the output devices is set up  */
/* as specified in the object data.                                         */
/* returned, and previous menu should be displayed.                         */
/*                                                                          */
/* Inputs:                                                                  */
/*                                                                          */
/*    Menu - Pointer to menu object                                         */
/*                                                                          */
/****************************************************************************/
{


}


UINT16 StdProcessMessage( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to process a message. All that it does is access    */
/* the message type and pass the message to the appropriate handler.        */
/*                                                                          */
/* Inputs:                                                                  */
/*                                                                          */
/*    Menu - Pointer to menu object                                         */
/*    Message - Message to process                                          */
/*    MessageResults - Pointer to structure containing additional           */
/*                     instructions for the caller. What this contains      */
/*                     depends on this function's return value.             */
/*                                                                          */
/* Output:                                                                  */
/*                                                                          */
/*    Action code - Tells the caller what to do.  Will be one of:           */
/*                                                                          */
/*       NEXT_MSG - Just get the next message & process it                  */
/*                                                                          */
/*       EXIT_HD  - Special for HD mode, exits to old menu, menu to go to   */
/*                  (MainKey, RunKey, etc) specified in MessageResults.     */
/*                                                                          */
/*       NEXT_MENU - Changes to another menu object. MessageResults         */
/*                   contains pointer to next menu, also a parameter to     */
/*                   pass to Close routine for the current menu.            */
/*                                                                          */
/*       DISPLAY_UPDATE - Regenerate & redraw menu items specified in       */
/*                        MessageResults.                                   */
/*                                                                          */
/*       SCROLL_MENU - Redraw screen on devices indicated by MessageResults.*/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 MessageType;

   MessageType = (Message & MESSAGE_TYPE_FIELD) >> MESSAGE_TYPE_BITPOS;

   switch( MessageType )
   {
      case CHR_RECEIVED_MSG:
         Action = Menu->ChrReceivedHandler( Menu, Message, MessageResults );
         break;

      case SELECT_MSG:
         Action = Menu->SelectKeyHandler( Menu, Message, MessageResults );
         break;

      case CONTROL_MSG:
         Action = Menu->ControlMessageHandler( Menu, Message, MessageResults );
         break;

      case SPECIAL_MSG:
         Action = Menu->SpecialMessageHandler( Menu, Message, MessageResults );
         break;

      default:
         Action = NEXT_MSG;
         break;

   }
   return( Action );
}

UINT16 StdChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to process an input keystroke message. Provides     */
/* default processing for menu keys, GoBack, terminal data mode toggle,     */
/* arrow keys. Inputs & outputs same as StdProcessMessage().                */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 StartLine, TermStartLine;

   switch( Message )
   {
      case MAIN_KEY:
      case RUN_KEY:
      case SETUP_KEY:
      case PRINT_KEY:
         Action = EXIT_HD;
         MessageResults->ExitHD.ExitKey = Message;
         break;

      case GOBACK_KEY:
         Action = EXIT_HD;
         MessageResults->ExitHD.ExitKey = 0;
         break;

      case PG_UP_KEY:
      case PG_DOWN_KEY:
      case UP_KEY:
      case DOWN_KEY:
         StartLine = 1;
         TermStartLine = 1;

         switch( Message )
         {
            case PG_UP_KEY:
               break;

            case PG_DOWN_KEY:
               break;

            case UP_KEY:
               break;

            case DOWN_KEY:
               break;

            default:       /* This should never happen */
               break;
         }

         MessageResults->ScrollMenu.Devices = 0;

         /* A bit of glue here between old code and new code.  By looking */
         /* at first line to update based on scroll (StartLine), can tell */
         /* whether or not screen needs to be updated.  This number will */
         /* always be 1 if the screen scrolled, meaning "update from the */
         /* top line of the screen".  It will be a number greater than */
         /* the last screen line if the device doesn't need to scroll. */

         if (StartLine == 1)
            MessageResults->ScrollMenu.Devices |= VF_DEVICE_BIT;

         if (TermStartLine == 1)
            MessageResults->ScrollMenu.Devices |= TERM_DEVICE_BIT;

         if (MessageResults->ScrollMenu.Devices)
            Action = SCROLL_MENU;   /* If any device needs to scroll, */
         else                       /* return SCROLL_MENU, otherwise */
            Action = NEXT_MSG;      /* do nothing, get another message. */
         break;

      case DATA_KEY:
         Action = SCROLL_MENU;  /* Will redraw screen without re-generating */
         MessageResults->ScrollMenu.Devices = VF_DEVICE_BIT | TERM_DEVICE_BIT;
         break;                 /* menu items. */

      default:
         Action = NEXT_MSG;
         Beep(ERRORBEEP);
   }
   return( Action );
}


UINT16 HDAESelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* SelectKeyHandler routine for horn down mode, AE actuator. After the      */
/* selected item is edited, system goes back to WaitReady state and waits   */
/* for READY again before advancing.                                        */
/*                                                                          */
/****************************************************************************/
{
   MessageResults->NextMenu.CloseParam = HD_RESTART;
   MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   return( NEXT_MENU );
}
UINT16 HDAEDSelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* SelectKeyHandler routine for horn down mode, AED actuator. Same as AE    */
/* version except that menu for WaitReady is different.                     */
/*                                                                          */
/****************************************************************************/
{
   MessageResults->NextMenu.CloseParam = HD_RESTART;
   MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
   return( NEXT_MENU );
}

UINT16 HDAEFSelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* SelectKeyHandler routine for horn down mode, AEF actuator. Same as AED    */
/* version except that menu for WaitReady is different.                     */
/*                                                                          */
/****************************************************************************/
{
   MessageResults->NextMenu.CloseParam = HD_RESTART;
   MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;
   return( NEXT_MENU );
}


UINT16 NoSelectKeyHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* SelectKeyHandler routine for horn down mode when there are no items on   */
/* the screen that can be edited. Just beeps and tells caller to process    */
/* the next message.                                                        */
/*                                                                          */
/****************************************************************************/
{
   Beep( ERRORBEEP );

   return( NEXT_MSG );
}

UINT16 StdControlMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to process a control message. Provides default      */
/* processing for messages which blink the terminal ALARM message, handle   */
/* ESTOPs and power-off. Inputs & outputs same as StdProcessMessage().      */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   switch( Message )
   {
      case TERM_DATA_OUTPUT:
         Action = NEXT_MSG;
         break;

      case UPDATE_TERM_ALARM:
         Action = NEXT_MSG;
         break;

      case ESTOP_MSG_ON:
         ShowEstopMessageOn();
         Action = NEXT_MSG;
         break;

      case ESTOP_MSG_OFF:
         ShowEstopMessageOff();
         Action = NEXT_MSG;
         break;

      case ESTOP_PRESSED:
         if(QVGAHornDown)
         {
            Action = EXIT_HD;
         }
         else
         {
            HDProcessEstop();  /* Blink message until ESTOP goes away */
            Action = EXIT_HD;  /* Will cause exit from HD mode */
            MessageResults->ExitHD.ExitKey = 0;
         }
         break;
      
      case ESTOP_RELEASED:
         if(QVGAHornDown && QVGAEstopFlag)
         {
            if (!QVGAGnrlAlarmStateBeforeEstop)
               ClearGeneralAlarm();
            Action = EXIT_HD;
            MessageResults->ExitHD.ExitKey = 0;
         }            
         break;
          
      case POWER_OFF:
         Action = EXIT_HD;       /* Leave HD, let regular code handle this */
         MessageResults->ExitHD.ExitKey = 0;
         break;

      default:
         Action = NEXT_MSG;
         break;

   }
   return( Action );
}

UINT16 StdSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to process a "special" message. By definition, this */
/* type of message is menu-specific, so there isn't anything we can do here */
/* except throw out the message and tell the caller to get the next one.    */
/* This routine should only be used in menus that don't expect any special  */
/* messages.                                                                */
/*                                                                          */
/****************************************************************************/
{
   return( NEXT_MSG );
}

void StdCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/* "Base class" routine to close a menu. At the moment, this does nothing.  */
/*   *AND* nobody calls it.                                                 */
/*                                                                          */
/****************************************************************************/
{
}

void HDCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/* CloseMenu() routine for horn down mode, shared by all horn down menus.   */
/* It is called as each "state" is ended, before the next state is started, */
/* to make sure any timers used by the previous state are cleared. Let the  */
/* following state allocate timers as it desires.                           */
/*                                                                          */
/****************************************************************************/
{

   HornDownEventTimer[0].Count = 0;
   HornDownEventTimer[1].Count = 0;
   HornDownEventTimer[2].Count = 0;
   HornDownEventTimer[3].Count = 0;
}


/****************************************************************************/
/*                                                                          */
/*                         HORN DOWN MENU FUNCTIONS                         */
/*                         ========================                         */
/*                                                                          */
/* The following group of functions implement the horn down menus. They     */
/* call the base menu class functions when necessary and add their own      */
/* procssing on top. There are presently six lines of execution: AE auto    */
/* AE manual, AED automatic, AED manual, AEF manual, and AEF automatic.     */
/* Sometimes functions can be used in more than one line. The syntax for    */
/* function names is as follows:                                            */
/*                                                                          */
/*    HD(stage name)(actuator)[Man](function)                               */
/*                                                                          */
/* The (stage name) is either WaitReady, WaitPBs, WaitULS, WaitPart,        */
/* WaitTrigger, or ShowResult. (actuator) is AE or AED or AEF. The [Man] is */
/* included for functions specific to manual mode, and (function) is the    */
/* name of the menu member function, either OpenMenu, CloseMenu, or         */
/* SpecialMessageHandler.                                                   */
/*                                                                          */
/* Example: Using this syntax, the name of the function that handles        */
/* special messages on an AED actuator while waiting for trigger in         */
/* automatic mode is HDWaitTriggerAEDSpecialMessageHandler().               */
/*                                                                          */
/* Some parts of the name may be eliminated if a function can be used in    */
/* multiple menus. For example, the function to close the result menu is    */
/* HDResultCloseMenu(), and it is used for AE, AED, automatic, and manual.  */
/*                                                                          */
/****************************************************************************/

void HDWaitReadyAEOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDShowPressure = FALSE;

   StdOpenMenu( Menu);

   if (LastHDState.OnePB || LastHDState.BothPB) /* If PBs in, time release */
      HDStartTimer( 0, PBEXITTIME, PBS_STUCK_EVENT );

   if (!LastHDState.uls)             /* If not at upper limit, time return */
      HDStartTimer( 1, UPPERLIMIT_TIMEOUT, NO_UL_EVENT );

   /* Use timer 3 to periodically check for READY */

   HDStartTimer( 3, PREREADY_MSG_WAIT_TIME, HD_CHECK_READY );

}

UINT16 HDWaitReadyAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitReady( Message, MessageResults );

   if (Action == NEXT_MENU)
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitPBsAE;

   return( Action );
}

void HDWaitPBsAEOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   StdOpenMenu( Menu);

   TrigSwActv();     /* Do this before PBs or horn won't come down */
}

UINT16 HDWaitPBsAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPBs( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_MANUAL:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEMan;
            break;

         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitULSAE;
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
            break;
      }
   }
   return( Action );
}

void HDWaitPBsAECloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDCloseMenu( CloseParam );

   if (CloseParam != HD_ADVANCE)
      TrigSwInactv();
}

void HDWaitULSAEOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   StdOpenMenu( Menu);

   HDStartTimer( 0, UPPERLIMIT_TIMEOUT, NO_UL_CLEAR_EVENT );

   EnableSVOn();     /* Turn on SV to bring down horn */
   SVOn();

   LastHDState.ECycleAbort = 0;  /* Force message if abort is on */
}

UINT16 HDWaitULSAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitULS( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAE;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   }
   return( Action );
}

void HDWaitULSAECloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDCloseMenu( CloseParam );

   if (CloseParam != HD_ADVANCE)
   {
      SVOff();              /* Didn't work, bring horn back up */
      TrigSwInactv();
   }
}

UINT16 HDWaitTrigAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitTrigger( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAE;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   }
   return( Action );
}

void HDWaitTrigAECloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   if (CloseParam != HD_ADVANCE)
      SVOff();              /* Didn't work, bring horn back up */

   TrigSwInactv();
}

UINT16 HDResultAEChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   if (Message == HORNDOWN_KEY)
   {
      Action = NEXT_MENU;
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
      MessageResults->NextMenu.CloseParam = 0;
   }
   else
      Action = StdChrReceivedHandler( Menu, Message, MessageResults );

   return( Action );
}

UINT16 HDResultAESpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDShowResult( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)   /* This should never happen */
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;

   return( Action );
}

void HDResultCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDCloseMenu( CloseParam );
   SVOff();
}

UINT16 HDWaitTrigAEManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitTrigger( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAEMan;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   }
   return( Action );
}

UINT16 HDResultAEManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDShowResult( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)   /* Happens if trigger lost, just trig again */
   {
      Inp.Trigger = FALSE;
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEMan;
   }
   return( Action );
}


void HDWaitReadyAEDOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDShowPressure = TRUE;

   StdOpenMenu( Menu);

   if (LastHDState.OnePB || LastHDState.BothPB) /* If PBs in, time release */
      HDStartTimer( 0, PBEXITTIME, PBS_STUCK_EVENT );

   
   if (!LastHDState.uls)             /* If not at upper limit, time return */
      HDStartTimer( 1, UPPERLIMIT_TIMEOUT, NO_UL_EVENT );

   /* Use timer 2 to update system pressure on the screen */

   HDStartTimer( 2, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );

   /* Use timer 3 to periodically check for READY */

   HDStartTimer( 3, PREREADY_MSG_WAIT_TIME, HD_CHECK_READY );
     /* In order to use part contact algorithm, the RunningPreset.TriggerForce must
      be changed when in Horn Down and changed back on exit from Horn Down 
      (ref. ReadACTADC) */
   if(KeepHornDown.bool == TRUE)
      RunningPreset.TriggerForce = MinLimit.TriggerForce;
   else
      RunningPreset.TriggerForce = FORCENOTREACHED;  /* set trigger force to a value */
                                                     /* that cannot be reached       */
   PartContactFlag = FALSE;
}


void HDWaitReadyAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/* AEF has special requirements to check before progressing to              */
/* "wait-for-palm-buttons state. (HDWaitPBsAEF)                             */
/****************************************************************************/
{
 
   HDWaitReadyAEDOpenMenu( Menu);
   HDRTAlreadySetFlag = FALSE;
   SystemPressureCheck = PRESSURE_CHECK_TIME1; /* setup .25 second timer */
   HDReadyState = TRUE; 
   ClearPressureArray();
}



UINT16 HDWaitReadyAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitReady( Message, MessageResults );

   if (Action == NEXT_MENU)
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitPBsAED;

   return( Action );
}

UINT16 HDWaitReadyAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* When ready condition is met, a message will be received which instructs  */
/* code to progress to the next "state" which is HornDownWaitPBsAEF.        */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitReady( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *) &HornDownWaitPBsAEF;
      ZeroEncoder();
   }
   else
   {
      Action = NEXT_MSG; 
   }
   return( Action );
}


void HDWaitPBsAEDAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   StdOpenMenu( Menu);
   HDStartTimer( 1, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );
}

UINT16 HDWaitPBsAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPBs( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_MANUAL:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitPartAEDMan;
            break;

         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitULSAED;
            ZeroEncoder();
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
            break;
      }
   }
   return( Action );
}

UINT16 HDWaitPBsAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* Message handler for AEF when the present state is "wait for PBs". The    */
/* possible messages at this point include wait-part, wait-to-clear-ULS,    */
/* and restart. Each of these three will be handled.                        */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPBs( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_MANUAL:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitPartAEFMan;
            HDReadyState = FALSE; 
            break;

         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitULSAEF;
            HDReadyState = FALSE; 
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;
            break;
      }
   }
   return( Action );
}

void HDWaitULSAEDAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/* OpenMenu is the first function called for each state. It is called one   */
/* time at state entry. This version is used by both AED and AEF. This is   */
/* the place for code which will be executed once at entry to state.        */
/****************************************************************************/
{
   StdOpenMenu( Menu);

   HDStartTimer( 0, UPPERLIMIT_TIMEOUT, NO_UL_CLEAR_EVENT );

   HDStartTimer( 1, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );

   EnableSVOn();     /* Turn on SV to bring down horn */
   SVOn();

   InitVelocityData();  /* Prepare for velocity data collection */
   HDCollectVelData = TRUE;   /* Start doing it */
   LastHDState.ECycleAbort = 0;  /* Force message if abort is on */
}

UINT16 HDWaitULSAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitULS( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitPartAED;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
   }
   return( Action );
}


UINT16 HDWaitULSAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* After the palm buttons are pressed, the next physical action to expect   */
/* would be for the upper limit switch to change to false. The ISR will     */
/* send a message every .001 second, and when the USL clears (FALSE), this  */
/* routine will advance the state to "wait-for-part-contact".               */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitULS( Message, MessageResults );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
      {
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitPartAEF;
      }  
      else
      {   
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;
      }   
   }
   return( Action );
}


void HDWaitULSAEDAEFCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/* Called when ULS is cleared                                               */
/*                                                                          */
/* Inputs : RapidTraverseState                                              */
/*          CurrentPreset.SetRTComp                                         */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{
   if(RapidTraverseState == TRUE)
   {
      Downspeed = CurrentSetup.HornDownSpd + CurrentPreset.SetRTComp;
      if( Downspeed > MAX_DOWN_SPEED)
      {
         Downspeed = MAX_DOWN_SPEED;
      }   
      SetPV((UINT16)Downspeed,HOME_TO_RT);
   }
   else
      SetPV((UINT16)CurrentSetup.HornDownSpd,HOME_TO_DWNSPD);
   
   HDCloseMenu( CloseParam );

   if (CloseParam != HD_ADVANCE)
   {
      SVOff();              /* Didn't work, bring horn back up */
      HDCollectVelData = FALSE;
   }
}

void HDWaitPartAEDAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDShowPressure = FALSE;
   HDShowVelocity = FALSE;
   HDShowForce = TRUE;

   StdOpenMenu( Menu);

   HDStartTimer( 0, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );

   LastHDState.OnPart = FALSE;   /* Force message if on part */
}

UINT16 HDWaitPartAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPart( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAED;
            break;

         case HD_RESULT:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAED;
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
            break;
      }
   }
   return( Action );
}


UINT16 HDWaitPartAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* When actuator is AEF and state is waiting for part contact, and a message*/
/* is received,(some message is received every .001 second), and the message*/
/* type is "special_message", then this routine calls HDWaitPart to see if  */
/* part-contact has been made. When that part-contact has been made, action */
/* will be set to advance the state to "wait-for-trigger". If HDWaitPart    */
/* does not return part-contact-true, then this routine will take no action.*/
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPart( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEF;
            break;

         case HD_RESULT:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAEF;
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;
            break;
      }
   }
   return( Action );
}


void HDWaitPartAEDCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDCloseMenu( CloseParam );

   HDCollectVelData = FALSE;  /* Stop collecting vel data once hit part */

   if (CloseParam == HD_RESTART)
      SVOff();              /* Didn't work, bring horn back up */
   else
      HornDownVelocity = CalculateVelocity(); /* Advancing, compute vel */
}

void HDWaitPartAEFCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/* CloseMenu functions are the last functions called when a state change is */
/* taken. A CloseMenu function handles any remaining clean up work. For the */
/* AEF actuator, it is the time to set the proportional valve for the force */
/****************************************************************************/
{
   HDWaitPartAEDCloseMenu( CloseParam );

   if (CloseParam != HD_RESTART)
   {
      UpdateDistanceOffset();
      SetPV((UINT16)WorkingForceSet, TRG_TO_FORCE_A);
   }   
}

void HDWaitTrigAEDAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDShowPressure = TRUE;
   if ( (BUCMenuRAM.VelocityReporting == TRUE) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) )
      HDShowVelocity = TRUE;
   HDShowForce = TRUE;

   StdOpenMenu( Menu);

   HDStartTimer( 0, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );
}

UINT16 HDWaitTrigAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitTrigger( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAED;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
   }
   return( Action );
}

UINT16 HDWaitTrigAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* When a message is received, and the state is wait-for-trigger, and the   */
/* actuator is AEF, and the message type is SPECIAL_MESSAGE, then this      */
/* routine will be called. This routine will then call HDWaitTrigger which  */
/* will determine if trigger is true or if some other conditions have been  */
/* met. If trigger is true, HDWaitTrigger will return Action==NEXT_MENU and */
/* CloseParam==HD_ADVANCE. This routine then advances tells the next routine*/
/* what the next state will be (HornDownResultAEF).                         */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitTrigger( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
      {
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAEF;
        
      }
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;
   }
   return( Action );
}

void HDWaitTrigAEDAEFCloseMenu( UINT32 CloseParam )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDCloseMenu( CloseParam );

   if (CloseParam != HD_ADVANCE)
      SVOff();              /* Didn't work, bring horn back up */

}

void HDResultAEDAEFOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDShowPressure = TRUE;
   if ( (BUCMenuRAM.VelocityReporting == TRUE) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) )
      HDShowVelocity = TRUE;
   HDShowForce = TRUE;

   StdOpenMenu( Menu);

   HDStartTimer( 1, HD_UPDATE_RATE, HD_DISPLAY_UPDATE );
}

UINT16 HDResultAEDChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   if (Message == HORNDOWN_KEY)
   {
      Action = NEXT_MENU;
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
      MessageResults->NextMenu.CloseParam = 0;
   }
   else
      Action = StdChrReceivedHandler( Menu, Message, MessageResults );

   return( Action );
}

UINT16 HDResultAEFChrReceivedHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* If the actuator is AEF, and the state is (show) results, and a front     */
/* panel character is pressed, this routine will handle that key press.  If */
/* that key is horndown, then the horn down start state will be entered.    */
/* If it is any other key, then StdCharReceivedHandler will be called.      */
/****************************************************************************/
{
   UINT16 Action;

   if (Message == HORNDOWN_KEY)
   {
      Action = NEXT_MENU;
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;
      MessageResults->NextMenu.CloseParam = 0;
   }
   else
      Action = StdChrReceivedHandler( Menu, Message, MessageResults );

   return( Action );
}


UINT16 HDResultAEDSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDShowResult( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)   /* This should never happen */
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;

   return( Action );
}

UINT16 HDResultAEFSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* When actuator==AEF and state==results (results is the last of six AEF    */
/* states), and message-type==SPECIAL_MESSAGE, then this routine will be    */
/* called. This routine will then call HDShowResult to determine the Action.*/
/* If Action==NEXT_MENU, then state will be advanced (to start state).      */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDShowResult( Menu, Message, MessageResults, FALSE );

   if (Action == NEXT_MENU)   /* This should never happen */
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;

   return( Action );
}

void HDWaitPartAEDAEFManOpenMenu( struct MenuInfo *Menu)
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   HDWaitPartAEDAEFOpenMenu( Menu);
   InitVelocityData();  /* Prepare for velocity data collection */
   HDCollectVelData = TRUE;   /* Start doing it */
}

UINT16 HDWaitPartAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPart( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEDMan;
            break;

         case HD_RESULT:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAEDMan;
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
            break;
      }
   }
   return( Action );
}

UINT16 HDWaitPartAEFManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* if actuator=AEF and the operator has tripped the over-ride air valve and */
/* the upper limit switch has been cleared and the horn is approaching part */
/* contact,then this routine will handle the message. Eventually the message*/
/* will be "part-contact = true", and this routine will advance the state   */
/* from "wait-for-part-contact" to "wait-for-trigger".                      */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitPart( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)
   {
      switch (MessageResults->NextMenu.CloseParam)
      {
         case HD_ADVANCE:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEFMan;
            break;

         case HD_RESULT:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAEFMan;
            break;

         case HD_RESTART:
         default:
            MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;
            break;
      }
   }
   return( Action );
}

UINT16 HDWaitTrigAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitTrigger( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAEDMan;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
   }
   return( Action );
}

UINT16 HDWaitTrigAEFManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* if actuator=AEF and the operator has tripped the manual over-ride air    */
/* valve and part contact has been made, the next anticipated condition is  */
/* force contact build up until trigger condition is true. This routine 1st */
/* calls HDWaitTrigger, which monitors the trigger input condition and rtns */
/* Action==NEXT_MENU when true. This routine then advances the state from   */
/* wait-for-trigger to show-results.                                        */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDWaitTrigger( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)
   {
      if (MessageResults->NextMenu.CloseParam == HD_ADVANCE)
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownResultAEFMan;
      else
         MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;
   }
   return( Action );
}

UINT16 HDResultAEDManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;

   Action = HDShowResult( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)   /* Happens if trigger lost, just trig again */
   {
      Inp.Trigger = FALSE;
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEDMan;
   }
   return( Action );
}

UINT16 HDResultAEFManSpecialMessageHandler( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* If actuator=AEF and the operator has tripped the manual over-ride air    */
/* valve and part contact has been made, and trigger condition has been met,*/
/* and the results have been displayed, then the next state change will be  */
/* back to start.                                                           */ 
/****************************************************************************/
{
   UINT16 Action;

   Action = HDShowResult( Menu, Message, MessageResults, TRUE );

   if (Action == NEXT_MENU)   /* Happens if trigger lost, just trig again */
   {
      Inp.Trigger = FALSE;
      MessageResults->NextMenu.NextMenu = (struct MenuInfo *)&HornDownWaitTrigAEFMan;
   }
   return( Action );
}


UINT16 HDWaitReady( UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/*                                                                          */
/* Routine to implement WaitReady stage of HD operation. Waits for upper    */
/* limit, door closed, no PBs before trying HD sequence again. If a PB is   */
/* pressed or horn not at upper limit on entry, this is okay, as long as    */
/* these conditions are met within appropriate time limits.  However, once  */
/* PBs are released or upper limit is on, pressing a PB or leaving upper    */
/* limit will cause an immediate alarm.                                     */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;

   HDSplitMessage( &Message, &Timer, &Id );

   switch( Message )
   {
      case ONE_PB_PRESSED:
      case BOTH_PB_PRESSED:                 /* Unless timing already, */
         if (!HornDownEventTimer[0].Count)  /* this should alarm now. */
            RecordAlarm( EQ17 );
         break;
               
      case NO_PB_PRESSED:
         HornDownEventTimer[0].Count = 0;    /* Stop timing PBs */
         break;

      case TIMER_EXPIRED:
         switch( Timer )
         {
            case 0:
               if (Id == PBS_STUCK_EVENT)
                 RecordAlarm( EQ17 ); /* Exit unless horn should stay down */
               break;

            case 1:
               if (Id == NO_UL_EVENT)
               {
                  RecordAlarm( EQ2 );    /* No upper limit */
               }
               break;

            case 2:
               if (Id == HD_DISPLAY_UPDATE)
               {
                  Action = DISPLAY_UPDATE;
                  HornDownEventTimer[2].Count = HD_UPDATE_RATE; /* repeat */
               }
               break;

            case 3:
               if (Id == HD_CHECK_READY)
               {
                  
                  /* This timer is used to force regular tests for the    */
                  /* READY condition. When READY is achieved, we want to  */
                  /* move on to the next menu. In order to be READY, all  */
                  /* the conditions tested here must be correct, and also */
                  /* there must be no pending messages (because a pending */
                  /* message might indicate that one of these conditions  */
                  /* isn't what we think it is). */

                  if (!CheckIfResetRequired())  /* Try to clear alarms */
                     AlarmsReset = TRUE;                                    
                                   
                  if (!LastHDState.OnePB && !LastHDState.BothPB &&
                   LastHDState.uls && !LastHDState.DoorOpen &&
                   !LastHDState.Trigger && 
                   (!KeyAvailable(TRUE) || QVGAHornDown))
                  {
                     Action = NEXT_MENU;
                     MessageResults->NextMenu.CloseParam = HD_ADVANCE;
                  }
                  else                        /* If not ready, try again later */
                     HornDownEventTimer[3].Count = PREREADY_MSG_WAIT_TIME;
               }
               break;

            default:
               break;
         }
         break;

      case DOOR_OPEN:
         RecordAlarm( EQ4 );
         break;

      case UPPER_LIMIT_ON:
         HornDownEventTimer[1].Count = 0;   /* Stop timing ULS */
         break;

      case UPPER_LIMIT_OFF:               /* Unless timing already, */
         
         if (!HornDownEventTimer[1].Count)/* alarm now (test of */
         {                                /* timer value is overkill) */

            /* Some klunky code: It is possible to get a ULS_OFF without */
            /* yet having found the system to be ready. For example, may */
            /* have just seen ULS_ON, causing state change to WaitForReady. */
            /* Before timer that checks for ready expires, ULS may change */
            /* to OFF. This should not cause an alarm unless there is some */
            /* other problem. So here we will check to see if system is */
            /* otherwise ready, and if so, will advance to the next state */
            /* and force the ULS_OFF message to come up again. */

            if (!CheckIfResetRequired())
               AlarmsReset = TRUE;

            if (!LastHDState.OnePB && !LastHDState.BothPB &&
             !LastHDState.DoorOpen && !LastHDState.Trigger)
            {
               Action = NEXT_MENU;
               MessageResults->NextMenu.CloseParam = HD_ADVANCE;
               LastHDState.uls = TRUE;    /* If still FALSE, will cause */
            }                             /* message to be sent again. */
            else
            {
               RecordAlarm( EQ2 );  /* Another reason for not ready, alarm */
            }
         }
         break;

      default:
         break;

   }
   return( Action );
}

void ResetHDAlarms(void)
{
   if(AlarmDetectedFlag == TRUE)
   {
      AlarmDetectedFlag = FALSE;
      AlarmOff();
      CycleAbort = FALSE;
      ClearAlarmFlag();       /* Clear Alarm flag                 */
      ClearGeneralAlarm();         /* Remove GeneralAlarm,suspect,&reject signals*/
      AlarmCounter = 0;     /* Also need to do this, was in StartPB() */
      WeldState = PBSTATE;  /* ClearAlarm() code will test this */
      ClearSetupAlarms();   /* Clear out previous alarms */
      ClearFinalResults();
   }
   else
      Beep(ERRORBEEP);
   
}

UINT16 HDWaitPBs( UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* This routine handles other possible external stimuli while waiting for   */
/* palm buttons.                                                            */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;
   MessageResults->NextMenu.CloseParam = HD_RESTART;   /* Most popular param */

   HDSplitMessage( &Message, &Timer, &Id );

   switch( Message )
   {
      case ONE_PB_PRESSED:  /* One PB pressed, wait for other one */
      case BOTH_PB_PRESSED:

         /* If this is the first sight of PBs in here, then try to clear */
         /* those alarms that should be cleared at the start of a cycle. */

         if (!HornDownEventTimer[0].Count)
         {
            /* The following code was imported from WeldManager().  Seems */
            /* appropriate NOT to get WeldManager() involved, because we */
            /* aren't welding. */

            if(AlarmDetectedFlag == TRUE)
            {
               AlarmDetectedFlag = FALSE;
               AlarmOff();
               CycleAbort = FALSE;
               ClearAlarmFlag();       /* Clear Alarm flag                 */
               ClearGeneralAlarm();         /* Remove GeneralAlarm,suspect,&reject signals*/
            }
            AlarmCounter = 0;     /* Also need to do this, was in StartPB() */
            WeldState = PBSTATE;  /* ClearAlarm() code will test this */
            ClearSetupAlarms();   /* Clear out previous alarms */
            ClearFinalResults();
         }

         if (Message == ONE_PB_PRESSED)
            HDStartTimer( 0, PALMBUTTON_STAGGER_TIME, PB_SPLIT_EVENT );
         else
         {
            Action = NEXT_MENU;   /* Got what we want, get out now */
            MessageResults->NextMenu.CloseParam = HD_ADVANCE;
         }
         break;

      case NO_PB_PRESSED:                 /* Must have had it & lost it */
         RecordAlarm( EQ12 );
         Action = NEXT_MENU;
         break;

      case TIMER_EXPIRED:
         switch( Timer )
         {
            case 0:
               if (Id == PB_SPLIT_EVENT)
               {
                  RecordAlarm( EQ12 );    /* Didn't get second PB */
                  Action = NEXT_MENU;     /* Start switch time alarm */
               }
               break;

            case 1:
               if (Id == HD_DISPLAY_UPDATE)
               {
                  Action = DISPLAY_UPDATE;
                  HornDownEventTimer[1].Count = HD_UPDATE_RATE; /* repeat */
               }
               break;

            default:
               break;
         }
         break;

      case DOOR_OPEN:
      case TRIGGER_ON:
         RecordAlarm( EQ4 );
         Action = NEXT_MENU;
         break;

      case UPPER_LIMIT_OFF:
         Action = NEXT_MENU;
         MessageResults->NextMenu.CloseParam = HD_MANUAL;  /* Go manual mode */
         break;

      default:
         break;
   }
   return( Action );
}

UINT16 HDWaitULS( UINT32 Message, union MResults *MessageResults )
/****************************************************************************/
/* This routine handles other possible external stimuli while waiting for   */
/* the upper limit switch to be cleared.                                    */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;
   MessageResults->NextMenu.CloseParam = HD_RESTART;   /* Most popular param */

   HDSplitMessage( &Message, &Timer, &Id );

   switch(Message)
   {
      case NO_PB_PRESSED:    /* Don't have both PBs anymore */
      case ONE_PB_PRESSED:
         Action = NEXT_MENU;
         break;

      case UPPER_LIMIT_ON:    /* Must have left & come back */
         RecordAlarm( EQ3 );
         Action = NEXT_MENU;
         break;

      case UPPER_LIMIT_OFF:
         Action = NEXT_MENU;      /* What we want, get out */
         MessageResults->NextMenu.CloseParam = HD_ADVANCE;
         break;

      case TIMER_EXPIRED:
         switch (Timer)
         {
            case 0:
               if (Id == NO_UL_CLEAR_EVENT)  /* Didn't leave upper limit */
               {
                  RecordAlarm( NC1 );
                  Action = NEXT_MENU;
               }
               break;

            case 1:
               if (Id == HD_DISPLAY_UPDATE)
               {
                  Action = DISPLAY_UPDATE;
                  HornDownEventTimer[1].Count = HD_UPDATE_RATE; /* repeat */
               }
               break;

            default:
               break;
         }
         break;

      case ECYCLE_ABORT_ON:
         RecordAlarm( NC7 );
         Action = NEXT_MENU;
         break;

      case DOOR_OPEN:
         RecordAlarm( EQ4 );

         if (CurrentSetup.Actuator == AE)/* On AE, could be we hit     */
            RecordAlarm( EQ3 );          /* trigger without ULS clear, */
                                         /* so send alarm for this.    */
         Action = NEXT_MENU;
         break;

      default:
         break;
   }
   return( Action );
}

UINT16 HDWaitPart( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual )
/****************************************************************************/
/* This routine handles other possible external stimuli while waiting for   */
/* the part contact.                                                        */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;
   MessageResults->NextMenu.CloseParam = HD_RESTART;   /* Most popular param */

   HDSplitMessage( &Message, &Timer, &Id );

   switch(Message)
   {
      case NO_PB_PRESSED:    /* Don't have both PBs anymore */
      case ONE_PB_PRESSED:
         if (!Manual)
         {
            Action = NEXT_MENU;
         }
         break;

      case UPPER_LIMIT_ON:    /* Must have left & come back */
         if (!Manual)
            RecordAlarm( EQ3 );
         Action = NEXT_MENU;
         break;

      case ECYCLE_ABORT_ON:
         if (!Manual)
         {
            RecordAlarm( NC7 );
            Action = NEXT_MENU;
         }
         break;

      case DOOR_OPEN:         /* Really shouldn't happen past UL */
         RecordAlarm( EQ4 );
         Action = NEXT_MENU;
         break;

      case PART_CONTACT:      /* This is good, get out */
         Action = NEXT_MENU;
         MessageResults->NextMenu.CloseParam = HD_ADVANCE;
         break;

      case TRIGGER_ON:        /* Should do PART_CONTACT first, but if not, */
         Beep(TRIGGERBEEP);   /* just skip ahead to show results */
         Action = NEXT_MENU;
         MessageResults->NextMenu.CloseParam = HD_RESULT;
         break;

      case TIMER_EXPIRED:
         if (!Timer && Id == HD_DISPLAY_UPDATE)
         {
            Action = DISPLAY_UPDATE;
            HornDownEventTimer[0].Count = HD_UPDATE_RATE; /* repeat */
         }
         break;

      case BAD_TRIGGER:             /* Should really see TRIGGER_ON msg */
         if (!Manual)               /* first and get this on result */
         {                          /* screen, but test here just in case */
            RecordErrorCode( ERRORCODE700_EQ20 );
            RecordAlarm(EQ20);
			QVGAHDAlarm = TRUE;
            Action = EXIT_HD;
            MessageResults->ExitHD.ExitKey = 0;
         }
         break;

      default:
         break;
   }
   return( Action );
}

UINT16 HDWaitTrigger( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual )
/****************************************************************************/
/* This routine handles other possible external stimuli while waiting for   */
/* trigger condition.                                                       */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;
   MessageResults->NextMenu.CloseParam = HD_RESTART;   /* Most popular param */

   HDSplitMessage( &Message, &Timer, &Id );

   switch(Message)
   {
      case NO_PB_PRESSED:    /* Don't have both PBs anymore */
      case ONE_PB_PRESSED:
         if (!Manual)
         {
            Action = NEXT_MENU;
         }
         break;

      case UPPER_LIMIT_ON:    /* Must have left & come back */
         if (!Manual)
            RecordAlarm( EQ3 );
         Action = NEXT_MENU;
         break;

      case ECYCLE_ABORT_ON:
         if (!Manual)
         {
            RecordAlarm( NC7 );
            Action = NEXT_MENU;
         }
         break;

      case DOOR_OPEN:         /* Really shouldn't happen past UL */
         RecordAlarm( EQ4 );
         Action = NEXT_MENU;
         break;

      case TRIGGER_ON:
         Beep(TRIGGERBEEP);
         Action = NEXT_MENU;
         MessageResults->NextMenu.CloseParam = HD_ADVANCE;
         break;

      case TIMER_EXPIRED:
         if (!Timer && Id == HD_DISPLAY_UPDATE)
         {
            Action = DISPLAY_UPDATE;
            HornDownEventTimer[0].Count = HD_UPDATE_RATE; /* repeat */
         }
         break;

      case BAD_TRIGGER:             /* Should really see TRIGGER_ON msg */
         if (!Manual)               /* first and get this on result */
         {                          /* screen, but test here just in case */
            RecordErrorCode( ERRORCODE700_EQ20 );
            RecordAlarm(EQ20); 
			QVGAHDAlarm = TRUE;
            Action = EXIT_HD;
            MessageResults->ExitHD.ExitKey = 0;
         }
         break;

      default:
         break;
   }
   return( Action );
}

UINT16 HDShowResult( struct MenuInfo *Menu, UINT32 Message, union MResults *MessageResults, BOOLEAN Manual )
/****************************************************************************/
/* This routine handles other possible external stimuli while waiting for   */
/* the correct time to display final results.                               */
/****************************************************************************/
{
   UINT16 Action;
   UINT16 Timer, Id;

   Action = NEXT_MSG;
   MessageResults->NextMenu.CloseParam = HD_RESTART;   /* Most popular param */

   HDSplitMessage( &Message, &Timer, &Id );

   switch(Message)
   {
      case ECYCLE_ABORT_ON:
         if (!Manual)
         {
            RecordAlarm( CM15 );
			QVGAHDAlarm = TRUE;
            Action = EXIT_HD;
            MessageResults->ExitHD.ExitKey = 0;
         }
         break;

      
      case TRIGGER_OFF:                /* Lost trigger, time how long */
        if ((((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AEF) || (CurrentSetup.Actuator == MICRO))
               && (KeepHornDown.bool == TRUE)) || (CurrentSetup.Actuator == AE))
         {
            HDStartTimer( 0, TRIGGERLOSTTIME, TRIGGER_LOST_EVENT);
           /*   Action = NEXT_MENU; */
         }
         break;
      

      case TRIGGER_ON:
         HornDownEventTimer[0].Count = 0;   /* Trigger back, stop timing */
         break;

      case TIMER_EXPIRED:
         switch (Timer)
         {
            case 0:        /* Lost trigger too long, alarm */
               if (Id == TRIGGER_LOST_EVENT)
               {
                  if (!Manual)
                  {
						ActualHoldTime = MAX_TRIGGER_LOST_TIME - HornDownEventTimer[2].Count;
						RecordAlarm( CM1 );
						Action = RESTART_HD;
						MessageResults->ExitHD.ExitKey = 0;
                  }
                  else
                     Action = NEXT_MENU;
               }
               break;

            case 1:
               if (Id == HD_DISPLAY_UPDATE)
               {
                  Action = DISPLAY_UPDATE;
                  HornDownEventTimer[1].Count = HD_UPDATE_RATE; /* repeat */
               }
            default:
               break;
         }
         break;

      case BAD_TRIGGER:
         if (!Manual)
         {
            RecordErrorCode( ERRORCODE700_EQ20 );
            RecordAlarm(EQ20); /* case. */
			QVGAHDAlarm = TRUE;
            Action = EXIT_HD;
            MessageResults->ExitHD.ExitKey = 0;
         }
         break;

      default:
         break;

   }
   return( Action );
}

void HDSplitMessage( UINT32 *Message, UINT16 *Timer, UINT16 *Id )
/****************************************************************************/
/*                                                                          */
/* Takes a given message and splits out the data field, which is assumed to */
/* indicate a timer # and a timer ID.  (If the message isn't TIMER_EXPIRED, */
/* nobody is going to look at the Timer and Id anyway).  After the timer    */
/* and Id are copied out, the data field is cleared so that the Message     */
/* variable may be used in a switch/case.                                   */
/*                                                                          */
/****************************************************************************/
{
   *Timer = (*Message & TIMER_NUM_FIELD) >> TIMER_NUM_BITPOS; /* Get timer */
   *Id = (*Message & TIMER_ID_FIELD) >> TIMER_ID_BITPOS;      /* Get ID */

   *Message &= (MESSAGE_TYPE_FIELD | MESSAGE_CODE_FIELD); /* Clear data */
}

static void UpdateOperatingPressure(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when exiting HornDown and at HornDown ready. It  */
/* will save the operator's set pressure reading(60 or 80PSI)               */
/*                                                                          */
/* Inputs :  HomePressure - the averaged pressure when at home              */
/*                                                                          */
/* Outputs : CurrentPreset.SetPressure                                      */
/*           PresetNeedsToBeUpdated - this causes a preset verify           */
/*           CurrentPreset.PresetUpdateComplete - this forces an asterisk   */
/*                                                                          */
/****************************************************************************/ 
{   
   if( ((HIGH_PRESSURE - PRESSURE_TOLLERANCE) < HomePressure) &&
       ((HIGH_PRESSURE + PRESSURE_TOLLERANCE)  > HomePressure))
   {
      if(CurrentPreset.SetPressure == FALSE)         /* 60 PSI */
      {
         CurrentPreset.PresetUpdateComplete = FALSE; /* force asterisk */
         PresetNeedsToBeUpdated = TRUE;              /* need to verify the preset */
         CurrentPreset.Verified = FALSE;
      }
      CurrentPreset.SetPressure = TRUE;              /* 80 PSI */
      SetMaxMinValues();
      SystemPres60PSI = FALSE;
      SystemPres80PSI = TRUE;
   }
   else if( ((LOW_PRESSURE - PRESSURE_TOLLERANCE) < HomePressure) &&
            (( LOW_PRESSURE + PRESSURE_TOLLERANCE)  > HomePressure))
   {
      if(CurrentPreset.SetPressure == TRUE)          /* 80 PSI */
      {
         CurrentPreset.PresetUpdateComplete = FALSE; /* force asterisk */
         PresetNeedsToBeUpdated = TRUE;              /* need to verify the preset */
         CurrentPreset.Verified = FALSE;
      }
      CurrentPreset.SetPressure = FALSE;             /* 60 PSI */
      SetMaxMinValues();
      SystemPres60PSI = TRUE;
      SystemPres80PSI = FALSE;
   }
}

   
void DoHornDownFunc(void)
/****************************************************************************/
/*Description:                                                              */
/* This function performs the Horn Down operation. Horn Down Process is     */
/* Exited when user presses any of the Bottom buttons ( Run, Setup, Main,-  */
/* Graphs ) or in any erroneous condtions (eg: Trigger lost).               */
/****************************************************************************/
{
   
   UINT16  old_mode;
   if ((GetCurrentSequenceType() == HORNDOWN) && (HornDownFlag == TRUE))
      return;
   if (UserIOAlarmMenu || StateMachineDisabled)
      ExitMenuAndEnableWeld();

   QVGAHornDown = FALSE;
   QVGAEstopFlag = FALSE;
   QVGAHDAlarm = FALSE;

   if (!VGAHornVarEntry)
   {
      KeepHornDown.bool = TRUE;  /* set TRUE on each entry to do-horn-down */
      RTTransitionDist = CurrentPreset.RTDist;
      WorkingForceSet = CurrentPreset.WeldForce;
      RapidTraverseState = FALSE;
      CurrentSetup.HornDownSpd = CurrentPreset.DownSpdStart;
   } 
   else
   {
      VGAHornVarEntry = FALSE;  
      StartStateMachine();
      SetReady(); 
   }
      
   /* First, set up LastHDState structure the way we think the system */
   /* should be now.  Any change from this will cause a message to be */
   /* sent. */

   LastHDState.OnePB = LastHDState.BothPB = LastHDState.Estop = FALSE;
   LastHDState.OnPart = LastHDState.Trigger = LastHDState.DoorOpen = FALSE;
   LastHDState.uls = TRUE;
   LastHDState.ECycleAbort = LastHDState.PwrOff = FALSE;
   LastHDState.Unused = 0;       /* Fill in all bits */
   
   /* Now try to take over the state machine.  Can only do this if the */
   /* system is ready.  Disable ints first in case system goes to "Not */
   /* Ready" just after we do the test. */

   asm(" move.w sr,d0\n ori.w #$700,sr \n move.w d0,_old_mode" );
   
   if(GetReadyStatus()/*WeldState == READYSTATE*/ && !HornDownFlag && CurrentSetup.HandHeld == FALSE)
   {
      HornDownEventTimer[0].Count = 0;    /* Make sure timers shut off */
      HornDownEventTimer[1].Count = 0;
      HornDownEventTimer[2].Count = 0;
      HornDownEventTimer[3].Count = 0;
      HDPosition = 0;                     /* Reasonable initial value */
      HDCollectVelData = FALSE;           /* Don't collect vel data yet */
      HDReadyState = TRUE;                /* Horn down starts checking pressure at ready */
      SystemPressureCheck = PRESSURE_CHECK_TIME1; /* setup .25 second timer */
      HornDownFlag = TRUE;                /* Shut down state machine */
      CurrentSequence = HORNDOWN;         /* Some code looks at this */
      UpdateKeyMask(HDMODEMASK);  /* Mask off keys we don't want to allow */
      ClearReady();

      /* Save trigger force even if AE, just won't mean anything */

      SaveTriggerForce = RunningPreset.TriggerForce;
      RunningPreset.TriggerForce = MinLimit.TriggerForce;
      QVGAHornDown = TRUE;
      /* Clear Keypad buffer */
      ClearKeypadBuffer(FALSE);
   }

   asm( " move.w _old_mode,d0\n move.w d0,sr" );   /* Reenable interrupts */

   /* Horn Down can be started */
   if(QVGAHornDown)
   {      
      /* Replaces MenuInfo Menu with QVGA Menus */
      if (CurrentSetup.Actuator == AEF)
         VGAHDMenu = HornDownStartAEF;
      else if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) )
         VGAHDMenu = HornDownStartAED;
      else                             /* Don't know what actuator this is */
         VGAHDMenu = HornDownStartAE;     /* default to simplest */

      VGAHDMenu.OpenMenu( &VGAHDMenu); 
      VGAAction = NEXT_MSG;
   }
   else
   {
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;
   }
}    


void ProcessHDButtonPress1(void)            //For retract button
{
   VGAAction = NEXT_MENU;
   VGAMessageResults.NextMenu.CloseParam = 0;
   if (CurrentSetup.Actuator == AEF)                   
      VGAMessageResults.NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;
   else if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) )
      VGAMessageResults.NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
   else
      VGAMessageResults.NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   VGAProcessHornDownMsg();   
}

void ProcessHDButtonPress2(void)            //For toggle and choice press
{
   VGAAction = NEXT_MENU;
   VGAMessageResults.NextMenu.CloseParam = HD_RESTART;
   if (CurrentSetup.Actuator == AEF)                   
      VGAMessageResults.NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAEF;
   else if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) )
      VGAMessageResults.NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAED;
   else
      VGAMessageResults.NextMenu.NextMenu = (struct MenuInfo *)&HornDownStartAE;
   VGAProcessHornDownMsg();   
}

void ProcessHDButtonPress3(void)            
{
   VGAAction = EXIT_HD;
   VGAHornVarEntry = TRUE;
   VGAProcessHornDownMsg();   
   QVGAHornDown = TRUE;
}

void ProcessRvtsMenuTaskMsg(UINT32 RvtsMessage)
{
   UINT32  Message;
   UINT32  MsgUseId;

   Message = RvtsMessage & ~MESSAGE_NEW;
   /* If this message is one that should only appear in the buffer once, */
   /* clear flag now so it can be put in the buffer again. */

   MsgUseId = (Message & MESSAGE_USE_ID_FIELD) >> MESSAGE_USE_ID_BITPOS;
   if (MsgUseId)
      MessageUseFlags[MsgUseId-1] = 0;  /* MsgUseId=0 when no flag needed */
   
   VGAAction = VGAHDMenu.ProcessMessage( &VGAHDMenu, Message, &VGAMessageResults );  
   VGAProcessHornDownMsg();
}

void RestartHornDown(void)
{
	UINT32 CloseParam = 0;
	VGAHDMenu.CloseMenu( CloseParam );
	UpdateOperatingPressure();
	Inp.Trigger = FALSE;    /* Nobody else will do this, so do it here */
	VGAAction = NEXT_MSG;		 
   QVGAEstopFlag = FALSE;
   QVGAHDAlarm = FALSE;

   /* First, set up LastHDState structure the way we think the system */
   /* should be now.  Any change from this will cause a message to be */
   /* sent. */

   LastHDState.OnePB = LastHDState.BothPB = LastHDState.Estop = FALSE;
   LastHDState.OnPart = LastHDState.Trigger = LastHDState.DoorOpen = FALSE;
   LastHDState.uls = TRUE;
   LastHDState.ECycleAbort = LastHDState.PwrOff = FALSE;
   LastHDState.Unused = 0;       /* Fill in all bits */
   
      HornDownEventTimer[0].Count = 0;    /* Make sure timers shut off */
      HornDownEventTimer[1].Count = 0;
      HornDownEventTimer[2].Count = 0;
      HornDownEventTimer[3].Count = 0;
      HDPosition = 0;                     /* Reasonable initial value */
      HDCollectVelData = FALSE;           /* Don't collect vel data yet */
      HDReadyState = TRUE;                /* Horn down starts checking pressure at ready */
      SystemPressureCheck = PRESSURE_CHECK_TIME1; /* setup .25 second timer */
      HornDownFlag = TRUE;                /* Shut down state machine */
      CurrentSequence = HORNDOWN;         /* Some code looks at this */
      UpdateKeyMask(HDMODEMASK);  /* Mask off keys we don't want to allow */
      ClearReady();

      QVGAHornDown = TRUE;
      /* Replaces MenuInfo Menu with QVGA Menus */
      if (CurrentSetup.Actuator == AEF)
         VGAHDMenu = HornDownStartAEF;
      else if ( (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) )
         VGAHDMenu = HornDownStartAED;
      else                             /* Don't know what actuator this is */
         VGAHDMenu = HornDownStartAE;     /* default to simplest */

      VGAHDMenu.OpenMenu( &VGAHDMenu); 
      VGAAction = NEXT_MSG;
}

void VGAProcessHornDownMsg (void)
/****************************************************************************/
/*Description:                                                              */
/* This function processes Horn down messages.                              */
/****************************************************************************/
{
   UINT32 CloseParam;

   switch (VGAAction)  
   {
      case NEXT_MENU:
      
        CloseParam = VGAMessageResults.NextMenu.CloseParam;

        VGAHDMenu.CloseMenu( CloseParam );
        VGAHDMenu = *VGAMessageResults.NextMenu.NextMenu;
       
        /*Refresh Menus ID */
        HDMenuID =VGAHDMenu.FullMenuID;
           
        VGAHDMenu.OpenMenu( &VGAHDMenu);
        VGAAction = NEXT_MSG;   
      
      break;

      case EXIT_HD:
         CloseParam = 0;
         VGAHDMenu.CloseMenu( CloseParam );
         UpdateOperatingPressure();
         RunningPreset.TriggerForce = SaveTriggerForce;  /* Restore to orig */
         CurrentSequence = WELD; /* Next call should do this anyway */
         SelectWeldSequence();   /* Restart state machine */
         WeldState = NOP;        /* Restore this after tampering */
         //ResetStateMachine();
         StartStateMachine();
         SetReady(); 
         Inp.Trigger = FALSE;    /* Nobody else will do this, so do it here */
         HornDownFlag = FALSE;
         QVGAHornDown = FALSE;
         VGAAction = NEXT_MSG;
      break;
	  case RESTART_HD:
		  RestartHornDown();		 
		  break;
		        
      case NEXT_MSG:
      default:         
      break;
   } 
}

/*=========================================================================*/
/***********************************END*************************************/
/*=========================================================================*/
