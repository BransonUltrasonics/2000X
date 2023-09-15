/* $Header:   D:/SWLab/VMdb/2000Series/App/STATEDRV.C_V   2.181   17 Nov 2009 15:16:24   ygupta  $ */
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
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Statedrv                                                    */
/*                                                                          */
/* Filename:    Statedrv.c                                                  */
/*                                                                          */
/* Function Name: StateMachine                                              */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   03-15-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date      Author     Description                             */
/*  =========  ========  =========  ===========                             */
/*     0       03-15-96  BEKymer    Add pSOS to state machine               */
/*     1       05-01-96  BEKymer    Added calibration states                */
/*     2       05-03-96  BEKymer    Functions to start/stop data            */
/*     3       05-13-96  BEKymer    Proper function prototyping             */
/*     4       06-06-96  BEKymer    Create enum WELD_SEQUENCE_TYPE          */
/*     5       06-18-96  BEKymer    Remove weld sequence, put in Time.c     */
/*     6       06-28-96  BEKymer    Save Power in public variable each ms   */
/*     7       07-02-96  BEKymer    Handle aborts by setting AbortFlag &    */
/*                                    jumping to next state                 */
/*     8       07-15-96  BEKymer    New variable 'DisplayablePower' which   */
/*                                    does not have tenths of percent power */
/*     9       07-18-96  BEKymer    Modify HornDown state sequence          */
/*    10       07-19-96  BEKymer    Prevent Entry code execution when Abort */
/*                                    Flag is set                           */
/*    11       07-30-96  BEKymer    Remove page where "Does Loadcell=70.."  */
/*    12       08-01-96  BEKymer    New state added for load cell calibrate */
/*    13       08-05-96  LAM        chged endflag to a boolean              */
/*    14       08-07-96  BEkymer    Don't clear CurrentIndex in StopStateMa.*/
/*    15       09-16-96  BEKymer    Moved call to GetPowerSupplyWattage     */
/*    16       09-18-96  LAM        added setalarmflag to estopand abort    */
/*    17       09-19-96  BEKymer    Turn off SV in all abort situations     */
/*                                  Remove all TRACE conditional defines    */
/*    18       09-21-96  BEKymer    Reset CurrentIndex in abort cases       */
/*    19       09-30-96  BEKymer    Set EndFlag=TRUE in ABORT case          */
/*    20       10-03-96  BEKymer    Remove while(1) pSos error loops        */
/*    21       10-10-96  BEKymer    Make special Ready state for test mode  */
/*    22       10-14-96  LAM        turn off keypad during estop            */
/*    23       10-15-96  BEKymer    Test alarm code before calling RecordA..*/
/*                                  Changes to InitWeldSequence             */
/*    24       10-30-96  BEKymer    Add argument to SendData                */
/*    25       10-30-96  LAM        Add different trigger state for calib.  */
/*    26       10-31-96  BEKymer    Change logic test in SendData           */
/*    27       11-13-96  LAM        moved calibration sequences to snsrcalb */
/*    28       11-13-96  PaulG      Modified WELD_OBJECT                    */
/*    29       11-14-96  BEKymer    Remove General Alarm after E-stop       */
/*    30       11-15-96  LAM        moved horndown holdstate                */
/*    31       12-04-96  BEKymer    Created new actions POP and PUSH        */
/*    32       12-11-96  BEKymer    Added new states to horn down           */
/*    33       12-30-96  BEKymer    ClearGeneralAlarm when E-stop removed   */
/*    34       01-07-97  PhilJ      Deleted sending MainKey in              */
/*                                  SelectWeldSequence.                     */
/*    35       01-10-97  PhilJ      UINT32 CurrentFreqIn to SINT32          */
/*    36       01-27-97  LAM        clear weldon when estop found           */
/*    37       02-04-97  LAM        added aljumpnorm state                  */
/*    37.01    02-06-97  LAM        added popindex,fixed updating screen    */
/*                                  after estop                             */
/*    37.02    02-26-97  PhilJ      Modified EmergencyStop code             */
/*    37.03    02-27-97  PaulG      Modified Distance value.                */
/*    37.04    03-05-97  PaulG      Modified Distance value.                */
/*    37.05    03-05-97  LAM        datapacketfull data                     */
/*    37.06    03-06-97  PhilJ      Modified END state code                 */
/*    38.00    03-17-97  LAM        modified what is done every ms          */
/*    39.00    03-20-97  PaulG      modified PacketCount in switch..        */
/*    40.00    04-01-97  LAM        added check for estop at powerup        */
/*    41.00    04-07-97  LAM        added check not updating packetcounter  */
/*    41.01    04-08-97  BEKymer    InitTimers after estop removed          */
/*    42.00    04-09-97  LAM        accumulate energy every ms              */
/*                                  redid what is sent for different states */
/*                                  in senddata                             */
/*    43.00    04-21-97  LAM        only accumulate energy(1ms) during the weld, */
/*                                  added 0 samples with less than 5 packets*/
/*    43.01    04-28-97  PhilJ      Clear screen called on Estop received   */
/*    43.02    04-28-97  LAM        fixed peakpower                         */
/*    43.03    04-29-97  LAM        fixed powering up with estop            */
/*    44.00    04-29-97  LAM        fixed powering down with estop, fixed   */
/*                                  end of weld data                        */
/*    45.00    05-28-97  LAM        chged data going to 1msdata             */
/*    46.00    05-29-97  LAM        chged last data going to 1msdata to     */
/*                                  wait ulsmadestate                       */
/*    46.2.78  05-29-97  BEKymer    Add recovery code to ABORT case         */
/*                                  If in horndown still, don't update new  */
/*                                  weld sequence                           */
/*                                  StartStateMachine after recovery code   */
/*    46.2.79  05-29-97  LAM        added 2 more data groups made maxsize=50*/
/*    47.2.80  06-02-97  BEKymer    Change ABORT recovery code              */
/*    47.2.81  06-02-97  LAM        fixed power graph data                  */
/*    48.00    06-04-97  LAM/J.B    donot stop keypad clock during estop    */
/*    48.01    06-06-97  LAM        chged data going to 1msdata again       */
/*    49.2.84  07-03-97  LAM        deleted systemok flag,deleted getpowerwatt */
/*    49.2.85  07-07-97  LAM        deleted psos_tbl.h                      */
/*    50.2.86  07-28-97  LAM        fixed powerup with estop                */
/*    50.2.87  08-12-97  PaulG      Added collection of the 400 points.     */
/*    51.2.88  08-12-97  LAM        added powerdown sequence,added clear ready*/
/*                                  to estop,deleted getinputs              */
/*    52.2.89  08-17-97  LAM        replaced getpower,powerthisms           */
/*    2.90     08-22-97  LAM        added test code for powercal            */
/*    2.91     08-22-97  PaulG      Added statement to  ChangeDataStorage() */
/*    2.92     08-26-97  LAM        donot check for horndown in weldsequence*/
/*                                  donot clear 1ms arrays only count = 0   */
/*    2.93     08-28-97  BEKymer    Reset power supply when installing test */
/*                                  sequence.                               */
/*    2.94     08-29-97  LAM        added 100ms to xscale                   */
/*    2.95     09-04-97  PaulG      Added PostHoldtimeState() function.     */
/*    2.96     09-05-97  PaulG      Added check to ChangeDataStorage()      */
/*                                  to see if printer buffer is almost empty*/
/*    2.97     09.08.97  JBerman    Changed Init: IncrementPts, TotalPts, CopyPts*/
/*    2.98     09-11-97  PaulG      Cleanup data                            */
/*    2.99     09-15-97  LAM        added testprereadystate                 */
/*    2.100    09-23-97  LAM        added keypadmask call                   */
/*    2.101    09-23-97  PaulG      Added OFFLINE check at Palm Botton      */
/*    2.102    09-24-97  LAM        donot chg to powerdown seq when in powerup*/
/*    2.103    10-03-97  PaulG      Modified CheckPrintFull from LEFT10 TO LEFT01 */
/*    2.104    10-16-97  PaulG      Modified CheckPrintFull from LEFT01 TO LEFT10 */
/*    2.105    10-24-97  PaulG      Modified CheckDataStroage function      */
/*    2.106    10-27-97  LAM        added recordalarm to fail condition     */
/*    2.107    10-28-97  PaulG      Added PresetNeedsToBeUpdated flag to    */
/*                                  check if we need to recordalarm(EQ20)   */                                                                          
/*    2.108    11-05-97  PaulG      Modified Init1msPts() function          */
/*    2.106    10-27-97  LAM        added recordalarm to fail condition     */
/*    2.108    11-11-97  LAM        added printcycleflag when chg printcondition*/
/*    2.109    11-12-97  PaulG      Added ColdStartDone flag to determine if*/
/*                                  we should send an alarm (EQ20).         */
/*    2.110    11-14-97  PaulG      Commented out RecordAlarm(EQ20)         */
/*    2.111    11-14-97  LAM        added stop data collection after 100ms  */    
/*                                  hold                                    */
/*    2.112    11-14-97  LAM        added RecordAlarm(EQ20) back            */
/*    2.113    11-17-97  Paul       Modified PreTrigState                   */
/*    2.114    11-18-97  LAM        chged offline / online                  */
/*    2.115    11-18-97  LAM        removed finalresults                    */
/*    2.116    11-20-97  LAM        chged ckqsend to q_send                 */
/*    2.117    12-02-97  LAM        split up test for collecting data       */
/*    2.118    12-02-97  BEKymer    New function - CheckStateMachine()      */
/*    2.119    12-03-97  BEKymer    Remove SVOff() from SelectWeldSequence()*/
/*    2.120    12-04-97  PaulG      Changed TotalPts from UINT16 to UINT32  */
/*                                  also added new variable to store (UINT32)NewInc */
/*    2.121    12-05-97  PaulG      Check for divide by zero.               */
/*    2.122    12-05-97  PaulG      Convert all variable assignment to TotalPts to UINT32. */
/*    2.123    12-09-97  PaulG      Added counter to collection structure   */
/*    2.124    01-23-98  PaulG      Added extended time due to Energy Comp. */
/*    2.125    01-27-98  BJB        Added globals LatchPSRun, LatchPSSeek,  */
/*                                  LatchPSClear, LatchPSStore to latch     */
/*                                  PS signals until they're displayed.     */
/*                                  SelectTestSequence() resets these       */
/*                                  variables.                              */
/*    2.126    01-27-98  BEKymer    Restore state of General Alarm output   */
/*                                  after E-stop is removed                 */
/*    2.127    01-28-98  LAM        dleted resetstatemachine in restart     */
/*    2.128    02-09-98  BJB        Increments general alarm counter when   */
/*                                  ESTOP is pressed.                       */
/*    2.129    03-26-98  PaulG      Added TotalPts to WELD_OBJECT structure.*/
/*    2.130    03-27-98  PaulG      Added CopyPts and IncrementPts to       */
/*                                  WELD_OBJECT structure.                  */
/*    2.131    03-28-98  BEKYmer    Add PrinterIncCounts & PrinterCopyPts   */
/*    2.132    03-31-98  PaulG      Added BufferWrapFlag to WELD_OBJECT.    */
/*    2.132    04-06-98  PaulG      Added NewInc to WELD_OBJECT.            */
/*    2.133    04-07-98  PaulG      Cleared BufferWrapFlag in ClearStorageData() */
/*    2.134    04-22-98  BJB        Includes "menuhorn.h"                        */
/*    2.135    05.06.98  JBerman    In case that someone change an actuator      */
/*                                  without turning the system off, Added:       */
/*                                  ActPowerUp, CheckNvrValid                    */                                                       
/*    2.136    05.07.98 JBerman     Refer 2.135: Comment Out those 2 Func. Call  */                                                                    
/*                                  to Weldmangr.c; caused a LockUp              */                             
/*    2.137    06.05.98 PaulG       Set Dist after hold to 0.                    */
/*    2.138    06.12.98 PaulG       Create variable to store points collected    */
/*                                  up till hold time                            */
/*    2.139    06.18.98 BJB         Clears READY line when state machine stopped.*/
/*                                  Removed nested comment to satisfy compiler.  */
/*                                  Doesn't allow ESTOP while adjusting digpot   */
/*    2.140    07.30.98 BJB         Deleted commented-out lines that call        */
/*                                  actuator functions that shouldn't be here    */
/*    2.141    08-06-98 PAulG       Added PointsUpTillHold and EndOfSonicCt to WELD_OBJ Struct.  */
/*    2.142    08-11-98 PAulG       Added DontPrintGraph to WELD_OBJ Struct.     */
/*    2.143    08-18-98 PAulG       When a recall preset is done MsPointer is not reset to DataGroup1. */
/*    2.144    08-27-98 PAulG       Recalling a  preset while printing will not reset MsPointer */
/*    2.145    08-28-98 PAulG       MsPointer pointer was used before initialized  */
/*    2.146    09-09-98 PAulG       Modified code to grab data count entering HOLDTIME state */
/*    2.147    09-23-98 PAulG       Modified code to allow graph printing if WELDTIMESTATE was reached */
/*    2.148    09-28-98 BJB         Clears Inp.PSStore when starting Test Mode   */
/*                                   so no "blip" left over from last cycle.     */
/*    2.149    10-13-98 PAulG       Modified code to allow graph printing up to end of HOLDTIME */
/*    2.150    11-06-98 BEKymer     In ALJUMP case SendData to indicate a        */
/*                                  state change.                                */
/*    2.151    11-17-98 PAulG       Modified code to allow graph printing up to end of HOLDTIME */
/*    2.152    11-19-98 BJB         Clears AbortFlag before running power-down   */
/*                                  sequence, allows power-down after ESTOP.    */
/*    2.153    11-20-98 PaulG       Check is in Hold state and Weld state collectively  */
/*    2.154    11-20-98 PaulG       Check is in Hold state and Weld state collectively  */
/*    2.155    05-28-99 LAM         Deleted old horn down sequence               */
/*    2.157    12-16-99 LAM         removed unused error handling code           */
/*    2.158    07-07-00 BEKymer/DJL fixed SETUP                             */
/*    2.159    08-30-00 JLH         Turn off cooling valve in ABORT sequence     */
/*    2.160    08-30-00 JLH         Added comment to CoolValOff function call.   */
/*    2.161    11-06-00 BEKymer     Require reset after estop removed.  Reset led  */
/*                                   blinks after estop removed.  Now, while estop */
/*                                   active, navigation can occur and values can be*/
/*                                   changed.  In future, consider masking all keys*/
/*                                   but reset after estop removed, until reset    */
/*                                   is pressed.                                   */
/*    2.162    11-07-00 BEKymer     During estop disable all keys except reset,  */
/*                                   restore all keys when reset pressed after   */
/*                                   estop removed.                              */
/*    2.163    11-09-00 AT          Switched back to 2.160 version (8L12)        */
/*    2.164    04-09-01 BEKymer     Added check for handheld before calling for  */
/*                                   "SelectWeldSequence"                        */
/*    2.165    04-20-01 BEKymer     Added Energy, peak power and ground detect   */
/*                                   mode when using a handheld device           */
/*    2.166    04-25-02 LAM         Update alarm counters in BBR as they occur   */
/*    2.167    05-09-02 BEKymer     Add FailTrace variable for Debug Quick List  */
/*    2.168    05-09-02 BEKymer     Add LastFailTrace variable for Debug Quick   */
/*                                    List                                       */
/*    2.169    02-14-03 BEKymer     Check for actuator clear in state machine    */
/* 2.168.1.1   07-10-03 JOY         The PS Store flag QVGALatchPSStore cleared in*/
/*                                  'SelectTestSequence()'.                      */
/* 2.170       07-25-03  LAM        merged 8.10 with TS01                                                                           */
/* 2.171       04-06-04  VSharma    Disable SVInterlock output if weld cycle is  */
/*                                   aborted.                                    */
/*                                  Collect graph data in PreTrigState() for the */
/*                                   EXTTRIGDELAYSTATE.                          */
/* 2.172       05-11-05  VSharma    Called SVOutOff() when EmergencyStop pressed.*/
/* 2.173       05-17-04  VSharma    Removed SVOutOff() as SVOutOff is merged to  */
/*                                   SVOff().                                    */
/* 2.174       08-24-04 JOY         Data type of variable 'QVGALatchPSStore'     */
/*                                   changed to UINT8.                           */
/* 2.175       09-09-04 BEKymer     Add energy braking time to GetPtsIncrement   */
/* 2.176       09-16-04 BEKymer     Choose smaller of BUC menu brake time or     */
/*                                   RunningPreset.EBTime when calculating       */
/*                                   GetPtsIncrement().                          */
/* 2.176.1.0   09-24-07 BEKymer     Add function SetIndex (Ver 9.07) bug fix     */
/* 2.178       11-30-07 BEKymer     Add function SetIndex bug fix              */
/*                                   Move to tip as 2.178                      */
/* 2.179       09-02-08 NHAhmed     CleanUp for multi-language support.        */
/* 2.180       09-04-08 YGupta      CleanUp for LangTest Project.              */
/* 2.181			11-17-09 YGupta      Modified StartStateMachine to check if     */
/*												E-Stop is pressed.									 */
/*                                                                             */
/*----------------------------- DESCRIPTION -----------------------------------*/


/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

//#define STATEDRV_UT                     


#define MAX_STATE_PASSES  25            /* Prevent infinite hang up */



/*------------------------------ INCLUDES ----------------------------------*/

#include "names.h"
#include <psos.h>
#include "error.h"
#include "menu.h"
#include "preset.h"
#include "wldstate.h"
#include "statedrv.h"
#include "alarms.h"
#include "keypad.h"
#include "selctkey.h"
#include "ticks.h"
#include "ready.h"
#include "weldhold.h"
#include "timer.h"
#include "snsrcalb.h"
#include "inports.h"
#include "mansensr.h"
#include "timemode.h"
#include "energy.h"
#include "peakpwr.h"
#include "collapse.h"
#include "absolute.h"
#include "grd_det.h"
#include "cont.h"
#include "util.h"
#include "digout.h"
#include "graphs.h"
#include "fpk_task.h"
#include "menu4.h"
#include "menuhorn.h"
#include "actnvram.h"
#include "battram.h"

/*------------------------- LOCAL_TYPE_DECLARATIONS ------------------------*/

#define PTSAFTERHOLD 99 /* points after hold collected */

/*-------------------------EXTERNAL DATA------------------------------------*/

extern UINT16      ColdStartDone;
extern UINT16      CycleTimer;
extern UINT16      OkToDisplayAlarms;
extern UINT32      WmgrQid;
extern SINT32      EncoderPos;
extern SINT32      CurrentForce;
extern UINT32      CurrentAmpIn;
extern SINT32      CurrentFreqIn;
extern CONFIGSETUP CurrentSetup;
extern UINT8       CollectEnergyFlag;
extern UINT32      CurrentPowerIn;         /*-- Value being read by 7890         --*/
extern WELD_OBJECT *MsPointer;
extern INBITS      Inp;
extern SETUPS_Ver800      RunningPreset;
extern BOOLEAN     LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;
extern UINT16      PrinterTotalCount;
extern DFLOAT      PrinterIncPoints;
extern UINT16      PrinterCopyPts;
extern DFLOAT      PrinterNewInc;

extern BOOLEAN     DigPotKey;
extern UINT8       QVGALatchPSStore;  
extern UINT16      PresetCheck; 
extern BUCMENU_800 BUCMenuRAM;

/*-------------------------- PRIVATE GLOBAL DATA -----------------------------*/

/* Data collection variables */

UINT16      NewDurCt, NewPostCt;               /* global counters                                 */
UINT16      StopPts;                           /* Don't exceeded the points limit                 */
UINT16      DataGetValue = 0;
UINT16      CopyEndPts;               /* number of records to copy before TRIGGEREDSTATE */
UINT16      PreTrigCt, DurTrigCt;     /* counters                                        */
UINT16      PostHoldCt, PostEndCt;    /* counters                                        */
UINT16      DataCount;
UINT16      SonicsCt = 0;    /* Data count at end of Sonics */

UINT16		CheckPrintFull = 0;
UINT16      Update5ms = 0;
static      SINT16   SafetyTimerId = 0;         /* Id of watchdog timer assigned    */
static      SINT16   CurrentIndex, PushedIndex; /* Index to current state pointer*/
static      SINT16   LastTrace;
static      BOOLEAN  StopAtEndOfCycleFlag;
static      BOOLEAN  GeneralAlarmStateBeforeEstop;
static      UINT16   StateMachineFlag;

SINT16      FailTrace;
SINT16      LastFailTrace;
SINT32      EnergyNeeded;
SINT32      EnergyCalc;
SINT32      AccumulatedEnergy, EnergyInJoules;
static      STATE    *CurrentPtr;               /* Current state pointer         */
STATE       *WeldSequence[NMBR_OF_STATES];      /* Current weld cycle definition */
static      SSTATES  *SSptr;                    /* Current sub state pointer     */
enum        WELDSTATES WeldState;
WELD_OBJECT DataGroup0;
WELD_OBJECT DataGroup1;
WELD_OBJECT *MsDataPtr;
UINT16      ToggleFlag = 0;   /* 0:DataGroup0  1:DataGroup1 */

static      WELD_STATE_MSG msg;
static      BOOLEAN DataSendFlag = FALSE;
enum        WELD_SEQUENCE_TYPE CurrentSequence = NONEDEFINED;
static      UINT16 PowerDownMsgSent;
UINT16      EstopHistoryFlag = FALSE;
UINT16      PrintEveryCycleFlag = FALSE;
UINT32      ConvNewInc;

#ifdef STATEDRV_UT
void   DefaultPreset(void);
#endif

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/



/*-------------------------------- CODE ------------------------------------*/


void SendData(enum WELDSTATES State)
{
/* mask off states are do nothing in the weld manager */
   if((State != NOP) && (State != ENDOFSONICS) &&
      (State != WAITFORULSCLEARSTATE)){
      msg.common.opcode = OP_WELDER_STATE_CHANGE;
      msg.common.source_task = WC_ISR_TASK;
      msg.state = State;
      msg.weld_samples = MsDataPtr->count;
      msg.weld_object_ptr = MsDataPtr;

      q_send(WmgrQid,&msg);
   }
}



void StopAtEndOfCycle(void)
/****************************************************************************/
/*                                                                          */
/*  This function will set a bit which can be tested at the end of a weld   */
/*  cycle.  If this bit is set, then the state machine should be stopped.   */
/*                                                                          */
/****************************************************************************/
{
   StopAtEndOfCycleFlag = TRUE;  /* Stop at end of current cycle            */
   StopFlag = TRUE;              /* If not cycling, then stop now           */
}


void StartDataCollection(void)
/****************************************************************************/
/*                                                                          */
/*  This function will set a bit which will be tested in the function to    */
/*  send the 1ms data to the weld manager.                                  */
/*                                                                          */
/****************************************************************************/
{
   DataSendFlag = TRUE;
}


void StopDataCollection(void)
/****************************************************************************/
/*                                                                          */
/*  This function will clear a bit which will be tested in the function to  */
/*  send the 1ms data to the weld manager.                                  */
/*                                                                          */
/****************************************************************************/
{
   DataSendFlag = FALSE;
}



void StateMachine(void)
/****************************************************************************/
/*                                                                          */
/* See notes (state.doc) for overview of how this function works.  The      */
/* while loop will continue until EndFlag is set TRUE.  This can happen by  */
/* one of several ways: 1) the action END was executed, 2) the action JUMP  */
/* was executed, 3) the action ALJUMP was executed or 4) more sub states    */
/* then MAX_STATE_PASSES have been tested in a row (as counted by the       */
/* variable SafetyNet).                                                     */
/*                                                                          */
/* NOTES:Instead of safety net approach consider using hardware (PIT)       */
/*       timer on the 332 (122 us resolution).  It would be retriggered     */
/*       before each call to the state machine.  An interrupt would occur   */
/*       if too much time elapsed before each retriggering.  The interrupt  */
/*       handler would record an error (for later viewing) and then set     */
/*       EndFlag to TRUE (except EndFlag is local!?).                       */
/*                                                                          */
/*       If ALJUMP is the cause of leaving one state and entering the       */
/*       next, the Entry Code for the new state WILL NOT be executed.       */
/*       This means in an abort situation, the next state code will not     */
/*       be run, i.e. hold time will not start if the weld was aborted.     */
/*                                                                          */
/*       If ABORT is the cause of leaving one state and entering the        */
/*       next, the Entry Code for the new state and the exit code for the   */
/*       old state WILL NOT be executed.  This means in an abort situation, */
/*       the next state code will not be run, i.e. hold time will not start */
/*       if the weld was aborted.  Further, no state entry code will be     */
/*       executed until the AbortFlag is reset.  All exit code will con-    */
/*       tinue to be executed.                                              */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN EndFlag = FALSE;
   BOOLEAN TestValue;
   SINT16  Cond;
   SINT16  SafetyNet = 0;
   CONFIGSETUP  *SetupPtr;

   SetupPtr = (CONFIGSETUP *) BBR800_CONFIG_START;


/*----------  The next thing to do is check for Emergency Stop  ----------*/

   /* Don't allow ESTOP while powering up, powering down, or adjusting digital pot */

   if((CurrentSequence != POWERDOWN) && (CurrentSequence != POWERUP) && (!DigPotKey)){
      if (Inp.Estop == TRUE) {
         if (EstopHistoryFlag == FALSE) {/* Did we already deal with Estop?    */
            SendData(EMERGENCYSTOP);
            AbortFlag = TRUE;
            GeneralAlarmStateBeforeEstop = CheckGeneralAlarmFlag();

            /* Inc alarm counter if this is first alarm on cycle */
            /* attempt or if cycle attempt not in progress now. */

            if (!GeneralAlarmStateBeforeEstop || OkToDisplayAlarms){
               CurrentSetup.GenAlarmCount++;
               SetupPtr->GenAlarmCount = CurrentSetup.GenAlarmCount;  /* Update BBR */
            }
            SetAlarmFlag();
            ClearSAS();                        /* Reset Sonics Active signal            */
            ClearReady();
            StopDataCollection();              /* Stop 1ms data while in estop */
            ResetStateMachine();               /* Stop & reset weld cycle      */
            SVOff();                           /* Release SV, send horn home   */
            PSIdle();                          /* Turn off the sonics          */
            EstopHistoryFlag = TRUE;
         }
      }
      else {
         if (EstopHistoryFlag == TRUE) { /* Did we already deal with no ESTOP? */
            SendData(EMERGENCYSTOPRESET);
            EstopHistoryFlag = FALSE;
            InitTimer();
            if (GeneralAlarmStateBeforeEstop == FALSE) {
               ClearGeneralAlarm();
            }
         }
      }
   }
/*----------  Check to see if a power down has been requested  ----------*/

   if (Inp.PwrOff == TRUE) {
      if (EstopHistoryFlag == TRUE) { /* Did we already deal with no ESTOP? */
         PowerDownSystem();
      }
      else if (PowerDownMsgSent == FALSE) {
         PowerDownMsgSent = TRUE;       /* Make sure message sent only once */
         if(CurrentSequence != POWERUP){
            AbortFlag = FALSE; /* If not clear, won't run EPowerDown() */
            SelectPowerDownSequence();
         }
         else{
            PowerDownSystem();
         }
      }
   }

/*----------  This section gets executed every ms  ---------*/

   TestActClr();         /* Check actuator clear so multiple individual */
                         /* states dont have to do it.  This ensures it */
                         /* work even in abort situations.              */ 



/*----------  The next thing to do is collect the 1ms data  ----------*/

   if (StateMachineFlag == TRUE) {

      if(CollectEnergyFlag == TRUE){
         AccumulatedEnergy += CurrentPowerIn;
         if (EnergyCalc != 0) 
            EnergyInJoules = (AccumulatedEnergy / EnergyCalc);
      }

      if(Update5ms++ >= 4){
         Update5ms = 0;
      }


   
/**---------------------------------------------------------**
 ** This block of instruction involves accumulating the 400 **
 ** points we need for the printing of the graphs.  It is   **
 ** executed if it's ok to collect data. This decision is   **
 ** based on DataSendFlag being TRUE and the data increment.**
 ** The 400 points are stored at DataGroup0 and then toggled**
 ** to DataGroup1. After the 400 points have been collected **
 ** Graph points are generated if PRINT NOW is pressed or a **
 ** print selection has been made.                          **
 **---------------------------------------------------------**/


      /*-- Convert float to long --*/
      ConvNewInc = (UINT32)MsDataPtr->NewInc;
      
      /*-- Stop collecting data if        --*/
      /*-- there is a collection overflow --*/

      if(ConvNewInc == 0)
         DataSendFlag = FALSE;

      /*-- First time in HOLDTIMESTATE grab the count --*/
      if((CurrentPtr->state == HOLDTIMESTATE) && (SonicsCt == 0)){ 
         MsDataPtr->EndOfSonicCt = DataCount;
         MsDataPtr->PointsUpTillHold = DataCount;
         SonicsCt++;
      }
      
      /*-- Refresh count until end of HOLDTIMESTATE --*/
      if(CurrentPtr->state <= HOLDTIMESTATE){ 
        MsDataPtr->PointsUpTillHold = DataCount;
      }
      

      if(CurrentPtr->state == WELDTIMESTATE){ 
        MsDataPtr->DontPrintGraph = FALSE;       /* TRS not reached as yet  */
      }
   
   

      if(DataSendFlag == TRUE){  
         if((DataGetValue++ % ConvNewInc) == 0){

           MsDataPtr->NewInc += MsDataPtr->IncrementPts;

           switch (CurrentPtr->state)
           {

               case DOWNSTROKESTATE:
                    PreTrigState();
                    break;

               case WAITFORPTSSTATE:
                    PreTrigState();
                    break;

               case WAITFORTRSSTATE1:
                    PreTrigState();
                    break;

               case WAITFORTRSSTATE2:
                    PreTrigState();
                    break;

               case WAITFORTRSSTATE3:
                    PreTrigState();
                    break;

               case EXTTRIGDELAYSTATE:
                    PreTrigState();
                    break;
                    
               case TRIGGERDELAYSTATE:
                    DurTrigWeldHoldState();
                    break;

               case WELDTIMESTATE:
               case WELDTIME2STATE:
                    DurTrigWeldHoldState();
                    break;

               case ENDOFSONICS:
                    DurTrigWeldHoldState();
                    MsDataPtr->EndOfSonicCt = MsDataPtr->count;
                    break;

               case HOLDTIMESTATE:
                    DurTrigWeldHoldState();
                    break;

               case AFTERBURSTDELAYSTATE:
                    PostHoldtimeState();
                    break;

               case AFTERBURSTTIMESTATE:
                    PostHoldtimeState();
                    break;

               case UPSTROKESTATE:
                    PostHoldtimeState();
                    break;

               case WAITFORULSMADESTATE:
                    PostHoldtimeState();
                    break;

               case WAITFORCONTINUE:
                    PostHoldtimeState();
                    break;
              
               case SEEKSTATE:
                    PostHoldtimeState();
                    break;

               case RAMPSONICSSTATE:
                    PostHoldtimeState();
                    break;

                 default:
                    break;
              }
         }

      }
/*----------  Now finally run through the state cycles  ----------*/

      CurrentPtr = WeldSequence[CurrentIndex];
      SSptr = CurrentPtr->ptr;                 /* Get sub state pointer    */
      CurrentPtr->PassPtr();                   /* Execute this pass code   */
      FailFlag = FALSE;
      while (EndFlag == FALSE) {
         TestValue = *(SSptr->ValuePtr);
         if (TestValue == FALSE) {             /* Test the value           */
            Cond = SSptr->False;               /* Was FALSE, use FALSE cmd */
         }
         else {
            Cond = SSptr->True;                /* Was TRUE, use TRUE cmd   */
         }
         switch (Cond) {
   
            case NORM:
               SSptr++;
               if (++SafetyNet > MAX_STATE_PASSES) EndFlag = TRUE;
               break;
   
            case PUSH:
               SSptr++;
               if (++SafetyNet > MAX_STATE_PASSES) EndFlag = TRUE;
               PushedIndex = CurrentIndex;
               break;
   
            case FAIL:
               if (SSptr->Alarm != NONE) RecordAlarm(SSptr->Alarm);
               SSptr++;
               if (++SafetyNet > MAX_STATE_PASSES) EndFlag = TRUE;
               FailFlag = TRUE;
               LastFailTrace = FailTrace; 
               FailTrace = SSptr->Trace; 
               break;
   
            case ABORT:
               if (SSptr->Alarm != NONE) RecordAlarm(SSptr->Alarm);
               SSptr++;
//               AbortFlag = TRUE;

               LastTrace = SSptr->Trace; 
               CurrentIndex++;                         /* Increment index   */
               CurrentPtr = WeldSequence[CurrentIndex];
               if (CurrentPtr->state != NOP)
                  WeldState = CurrentPtr->state;       /* Update state variable  */
               if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
                  StopTimer(SafetyTimerId);            /* Stop last timer*/
               }
               if (*CurrentPtr->STimer != 0) {
                  SafetyTimerId = StartTimer(*CurrentPtr->STimer, &TimerFlag, 1);
                  if (SafetyTimerId == FAILED1)
                     LogError(TIMERFAILED1);
                  else if (SafetyTimerId == FAILED2)
                     LogError(TIMERFAILED2);
               }
               else SafetyTimerId = 0;

/*---- New code added to better handle aborts (09-21-96) ----*/

               SVOff();            /* Bring up horn in all abort situations */
               ClearSAS();         /* Reset Sonics Active signal            */
               PSIdle();           /* Stop sonics                           */
               ResetStateMachineIndex();
               CoolValOff();       /* Turn off cooling valve (08-30-00)     */
               EndFlag = TRUE;

/*---- End of new abort code ----*/

/*---  If we aborted, lets assume something went wrong somewhere, so     ---*/
/*---  lets reset everything and reselect the weld sequence to recover.  ---*/

               TrigSwActv();                  /* safety circuit input       */
               if ( (GetCurrentSequenceType() == WELD) &&
                    (HornDownFlag == FALSE) ) {
                   SelectWeldSequence();      /* Try redoing weld sequence  */
                   StartStateMachine();
               }
               break;
   
            case ALNORM:
               if (SSptr->Alarm != NONE) RecordAlarm(SSptr->Alarm);
               SSptr++;
               if (++SafetyNet > MAX_STATE_PASSES) EndFlag = TRUE;
               break;
   
            case JUMP:
               CurrentPtr->NextPtr();                  /* Execute exit code */
               LastTrace = SSptr->Trace;
               CurrentIndex++;                         /* Increment index   */
               CurrentPtr = WeldSequence[CurrentIndex];
               if (CurrentPtr->state != NOP)
                  WeldState = CurrentPtr->state;       /* Update state variable  */
               if (AbortFlag == FALSE)
                  CurrentPtr->EntryPtr();              /* Execute new entry code */
               if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
                  StopTimer(SafetyTimerId);            /* Stop last timer*/
               }
               if (*CurrentPtr->STimer != 0) {
                  SafetyTimerId = StartTimer(*CurrentPtr->STimer, &TimerFlag, 1);
                  if (SafetyTimerId == FAILED1)
                     LogError(TIMERFAILED1);
                  else if (SafetyTimerId == FAILED2)
                     LogError(TIMERFAILED2);
               }
               else SafetyTimerId = 0;
               EndFlag = TRUE;
               SendData(CurrentPtr->state);
               break;
   
            case ALJUMPNORM:
               if (SSptr->Alarm != NONE) RecordAlarm(SSptr->Alarm);
               CurrentPtr->AlarmPtr();                 /* Execute exit code   */
               CurrentPtr->NextPtr();                  /* Execute exit code */
               LastTrace = SSptr->Trace; 
               CurrentIndex++;                         /* Increment index   */
               CurrentPtr = WeldSequence[CurrentIndex];
               if (CurrentPtr->state != NOP)
                  WeldState = CurrentPtr->state;       /* Update state variable  */
               if (AbortFlag == FALSE)
                  CurrentPtr->EntryPtr();              /* Execute new entry code */
               if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
                  StopTimer(SafetyTimerId);            /* Stop last timer*/
               }
               if (*CurrentPtr->STimer != 0) {
                  SafetyTimerId = StartTimer(*CurrentPtr->STimer, &TimerFlag, 1);
                  if (SafetyTimerId == FAILED1)
                     LogError(TIMERFAILED1);
                  else if (SafetyTimerId == FAILED2)
                     LogError(TIMERFAILED2);
               }
               else SafetyTimerId = 0;
               EndFlag = TRUE;
               SendData(CurrentPtr->state);
               break;

            case POP:
               CurrentPtr->AlarmPtr();                /* Execute alarm code */
               LastTrace = SSptr->Trace; 
               CurrentIndex = PushedIndex;            /* Reset index        */
               CurrentPtr = WeldSequence[CurrentIndex];
               if (CurrentPtr->state != NOP)
                  WeldState = CurrentPtr->state;       /* Update state variable  */
               if (AbortFlag == FALSE)
                  CurrentPtr->EntryPtr();              /* Execute new entry code */
               if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
                  StopTimer(SafetyTimerId);            /* Stop last timer*/
               }
               if (*CurrentPtr->STimer != 0) {
                  SafetyTimerId = StartTimer(*CurrentPtr->STimer, &TimerFlag, 1);
                  if (SafetyTimerId == FAILED1)
                     LogError(TIMERFAILED1);
                  else if (SafetyTimerId == FAILED2)
                     LogError(TIMERFAILED2);
               }
               else SafetyTimerId = 0;
               EndFlag = TRUE;
               break;
   
            case ALJUMP:
               if (SSptr->Alarm != NONE) RecordAlarm(SSptr->Alarm);
               CurrentPtr->AlarmPtr();                 /* Execute exit code   */
               LastTrace = SSptr->Trace; 
               CurrentIndex++;                         /* Increment index     */
               CurrentPtr = WeldSequence[CurrentIndex];
               if (CurrentPtr->state != NOP)
                  WeldState = CurrentPtr->state;       /* Update state variable  */
               if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
                  StopTimer(SafetyTimerId);            /* Stop last timer*/
               }
               if (*CurrentPtr->STimer != 0) {
                  SafetyTimerId = StartTimer(*CurrentPtr->STimer, &TimerFlag, 2);
                  if (SafetyTimerId == FAILED1)
                     LogError(TIMERFAILED1);
                  else if (SafetyTimerId == FAILED2)
                     LogError(TIMERFAILED2);
               }
               else SafetyTimerId = 0;
               EndFlag = TRUE;
               SendData(CurrentPtr->state);
               break;
   
            case END:

               EndFlag = TRUE;
               break;

            default:
               EndFlag = TRUE;
               break;
         }
      }
   }

}



void PushIndex(void)
{
   PushedIndex = CurrentIndex;
}



void PopIndex(void)
{
   CurrentIndex = PushedIndex;
}



void SetIndex(SINT16 Index)
{
   CurrentIndex = Index;
}



void StartStateMachine(void)
{
   if(Inp.Estop == FALSE)
	{
		StateMachineFlag = TRUE;
		StopAtEndOfCycleFlag = FALSE;
		StopFlag = FALSE;
	}
}



void StopStateMachine(void)
{
   StateMachineFlag = FALSE;
   ClearReady();  /* No state machine = not ready! */
}



UINT16 CheckStateMachine(void)
{
   return(StateMachineFlag);
}



void ResetStateMachine(void)
{
   if ((SafetyTimerId > 0) && (TimerFlag == TRUE)) {
      StopTimer(SafetyTimerId);            /* Stop last timer*/
   }
   CurrentPtr = 0;
   CurrentIndex = 0;
   StateMachineFlag = FALSE;
}



UINT16 GetStateMachineFlag(void)
{
   return(StateMachineFlag);
}



UINT16 SetStateMachineFlag(UINT16 Flag)
{
   UINT16 RetVal;

   RetVal = StateMachineFlag;          /* Get old value before we change it */
   StateMachineFlag = Flag;            /* Set to new passed value           */
   return(RetVal);                     /* Return original value             */
}


void ResetStateMachineIndex(void)
{
   CurrentIndex = 0;
}



void SetCurrentSequenceType(enum WELD_SEQUENCE_TYPE Type)
{
   CurrentSequence = Type;
}



enum WELD_SEQUENCE_TYPE GetCurrentSequenceType(void)
{
   return(CurrentSequence);
}



void ResetCycleTimer(void)
/***************************************************************************/
/*                                                                         */
/*  This function will clear the cycle timer.  It should be called from    */
/*  the routine which first becomes aware that the upper limit switch is   */
/*  cleared and the cycle is about to begin.                               */
/*                                                                         */
/*  Whatever routine calls this better be from within the 1 ms interrupt.  */
/*                                                                         */
/***************************************************************************/
{
   CycleTimer = 0;
}



void InitWeldSequencer(void)
/***************************************************************************/
/*                                                                         */
/* This is where all variables relating to the weld sequencer will be      */
/* initialized.  This function must be called at least once after power    */
/* and whenever a 'warm' reset is needed.                                  */
/*                                                                         */
/* pSOS Notes:                                                             */
/*                                                                         */
/*   1 - This function will also get the task ID of the weld manager so    */
/*       the state machine knows where to send the new state events.       */
/*                                                                         */
/***************************************************************************/
{
   UINT16 x;
   UINT16 i = 2;

   TimeOff = 0;                        /* Variable used when no timeout    */
   CurrentIndex = 0;                   /* Start at top of list             */

/* Set all indexes to NOP except first and last */

   for (x = 1; x < NMBR_OF_STATES - 1; x++) {
      WeldSequence[x] = &NopList;
   }
   WeldSequence[0] = &TopOfList;
   WeldSequence[x] = &EndOfList;
   StateMachineFlag = FALSE;
   StopDataCollection();
   CurrentSequence = POWERUP;

/*-----  Insert Power On Sequence Here  -----*/

   WeldSequence[i++] = &PowerOn1;
   WeldSequence[i++] = &PowerOn2;
   WeldSequence[i++] = &PowerOn3;
   WeldSequence[i++] = &PowerOn4;
   WeldSequence[i++] = &PowerOn5;
   WeldSequence[i++] = &PowerOn6;

   CycleTimer = 0;
   MsDataPtr = &DataGroup0;
   ToggleFlag = 0;

   InitTimer();                         /* Initialize state machine timers  */
   DataSendFlag = FALSE;                /* Start the 1ms data collection    */
   PowerDownMsgSent = FALSE;

#ifdef STATEDRV_UT
   DefaultPreset();          /* Define a default preset (just for Bob & Guy) */
#endif

}



void SelectWeldSequence(void)
/***************************************************************************/
/*                                                                         */
/* This function will call the proper function to set up a weld sequence   */
/* based on the selected weld mode.                                        */
/*                                                                         */
/* It will also do such trivial things as set up the PSWattage variable so */
/* energy can be calculated.                                               */
/*                                                                         */
/***************************************************************************/
{
   ResetStateMachine();                /* Turn off the state machine first */
   CurrentIndex = 0;
   EnergyCalc = (100000 / CurrentSetup.PSWatt);
   if (CurrentSetup.HandHeld == FALSE) {
      switch (RunningPreset.WeldMode) {
         case TIMEMODE:
            SelectTimeWeldSequence();
            break;
   
         case ENERGYMODE:
            SelectEnergyWeldSequence();
/* Calculate here "energy units" needed */
            if (RunningPreset.WeldEnergy >= 2000) { /* Prevent overflow, lose a little accuracy */
               EnergyNeeded = RunningPreset.WeldEnergy * EnergyCalc;  /* Convert to energy units   */
            }
            else {      /* Overflow not a problem here, keep accuracy instead  */
               EnergyNeeded = RunningPreset.WeldEnergy * 100000; /* 1/10's of millejoules */
               EnergyNeeded /= CurrentSetup.PSWatt;    /* Convert to energy units   */
            }
            break;
   
         case PKPOWERMODE:
            SelectPeakPowerWeldSequence();
            break;
   
         case COLLAPSEMODE:
            SelectCollapseWeldSequence();
            break;
   
         case ABSOLUTEMODE:
            SelectAbsoluteWeldSequence();
            break;
   
         case GRDDETECTMODE:
            SelectGroundDetectWeldSequence();
            break;
   
         case CONTINUOUSMODE:
            SelectContWeldSequence();
            break;
   
         default:
            RunningPreset.WeldMode = TIMEMODE;
            SelectTimeWeldSequence();
            break;
      }
   }
   else {              /* Handheld is On */
      switch (RunningPreset.WeldMode) {
         case TIMEMODE:
            SelectTimeWeldSequenceHH();
            break;
   
         case ENERGYMODE:
            SelectEnergyWeldSequenceHH();
/* Calculate here "energy units" needed */
            if (RunningPreset.WeldEnergy >= 2000) {    /* Prevent overflow, lose a little accuracy */
               EnergyNeeded = RunningPreset.WeldEnergy * EnergyCalc;  /* Convert to energy units   */
            }
            else {      /* Overflow not a problem here, keep accuracy instead  */
               EnergyNeeded = RunningPreset.WeldEnergy * 100000; /* 1/10's of millejoules */
               EnergyNeeded /= CurrentSetup.PSWatt;    /* Convert to energy units   */
            }
            break;
   
         case PKPOWERMODE:
            SelectPeakPowerWeldSequenceHH();
            break;
   
         case GRDDETECTMODE:
            SelectGroundDetectWeldSequenceHH();
            break;
   
         case COLLAPSEMODE:
//            SelectCollapseWeldSequenceHH();    /* Maybe sometime in the distant future */
            break;

         case ABSOLUTEMODE:
//            SelectAbsoluteWeldSequenceHH();    /* Maybe sometime in the distant future */
            break;

         default:
            RunningPreset.WeldMode = TIMEMODE;
            SelectTimeWeldSequenceHH();
            break;
      }
   }
   StopFlag = FALSE;
   UpdateKeyMask(WELDMODEMASK);
}




void SelectTestSequence(void)
/****************************************************************************/
/*                                                                          */
/* This is the Test mode state sequence.                                    */
/*                                                                          */
/****************************************************************************/
{
   UINT16 i = 0;

   PSReset();                          /* Reset the power supply            */
   ResetStateMachine();                /* Turn off the state machine first  */
   StopDataCollection();               /* Stop 1ms data while in test mode  */
   CurrentIndex = 0;
   WeldSequence[i++] = &TopOfList;       
   WeldSequence[i++] = &PreReadyTestSt;
   WeldSequence[i++] = &ReadyTestSt;
   WeldSequence[i++] = &TestST;       
   WeldSequence[i++] = &NopList;
   WeldSequence[i++] = &EndOfList;
   CurrentSequence = TESTMODE;
   UpdateKeyMask(TESTMODEMASK);

   LatchPSRun = LatchPSSeek = LatchPSClear = LatchPSStore = FALSE;
   QVGALatchPSStore = FALSE;
   Inp.PSStore = FALSE;           /* Clear here, set by ISR */
   StartStateMachine();           /* Start the state machine here */
}



void Restart(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will reset the current index to the start of */
/*  the state list.                                                        */
/*                                                                         */
/***************************************************************************/
{
   CurrentIndex = 0;   /* Reset all pointers to the top of the state list. */
}



void Nothing(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be the most used of all functions.  It  */
/*  will be the MANAGER function (i.e. it will do nothing).                */
/*                                                                         */
/*  This would be a good place to put debugging stuff, because it will get */
/*  called at somewhat regular intervals.                                  */
/*                                                                         */
/***************************************************************************/
{
}



void SelectPowerDownSequence(void)
/****************************************************************************/
/*                                                                          */
/* This is the sequence that will be run when the power is about to go down.*/
/*                                                                          */
/****************************************************************************/
{
   UINT16 i = 0;

   ResetStateMachine();                /* Turn off the state machine first  */
   StopDataCollection();               /* Stop 1ms data while in test mode  */
   CurrentIndex = 0;
   WeldSequence[i++] = &TopOfList;       
   WeldSequence[i++] = &PwrDown;
   WeldSequence[i++] = &EndOfList;
   CurrentSequence = POWERDOWN;

   StartStateMachine();                /* Start the state machine here      */
}



/**---------------------------------------------------------------------**
 ** This function calculates the increment of the  1msdata information. **
 ** That is, if weldtime is 1 sec and holdtime is 2 sec and the extra   **
 ** .1 sec before triggerstate and  .1 sec after holdstate accumulates  **
 ** to 2.2 sec (or 2.2 * 1000 = 2200 pts). Only 400 pts is needed to    **
 ** configure graph so to utilize the entire 2200 pts we find the       **
 ** increment so we can discard unneeded data. NOTE: the increment is   **
 ** strictly based on the weldtime and holdtime. As these values vary   **
 ** so does the increment. If TriggerDelayFlag is TRUE, TriggerDelay    **
 ** value is also added to the equation.                                ** 
 ** This function also initialize the mSObject struct to zeroes....     **
 **---------------------------------------------------------------------**/
void GetPtsIncrement(void)
{
   UINT16 AddedTimeValue = 0;

   /*-- reinitialize values to 0 when restart --*/
   MsDataPtr->IncrementPts = 1.0;
   MsDataPtr->TotalPts = 1; // Changed to 1 because 1ms_data.c divides this variable.
   StopPts = 0;
   MsDataPtr->CopyPts = 1;  
   CopyEndPts = 0;

/* See if energy braking is on, if so, then add smaller of BUC menu time */
/* or RunningPreset.EBTime                                               */

   if (CurrentPreset.EnergyBraking == TRUE) {
      if (BUCMenuRAM.EnergyBrakingTime < RunningPreset.EBTime)
         AddedTimeValue = BUCMenuRAM.EnergyBrakingTime;
      else
         AddedTimeValue = RunningPreset.EBTime;
   }

   if (CurrentSetup.HandHeld == TRUE)
      AddedTimeValue += 100;  /* 100 ms after hold only  */
   else
      AddedTimeValue += 200;  /* 100 ms before trigger and 100 ms after hold */
      
    /*-- TIMEMODE and manual scale active --*/
   if((RunningPreset.WeldMode == TIMEMODE) && ((RunningPreset.AutoScaleFlag & BIT0) == FALSE)){
      MsDataPtr->TotalPts = (UINT32)(RunningPreset.XScaleTime + PRETRIGMAXLIM);
     
       /* If manual scale is active therefore,  set flag */
      MsDataPtr->PrintBottomFlags |= MANUALSCALEFLAG;
   }

   /* TIMEMODE and manual scale inactive*/
   else
   if((RunningPreset.WeldMode == TIMEMODE) && ((RunningPreset.AutoScaleFlag & BIT0) == TRUE)){

      /* If manual scale is inactive the clear flag if not already cleared */
      MsDataPtr->PrintBottomFlags &= (~MANUALSCALEFLAG);

      /*-- Check if Time is extended due to Energy Compensation --*/
      /*-- if so, multiply the weldtime by 1.5 --*/
      if((RunningPreset.ControlLimitsFlag ==  TRUE) && (RunningPreset.EnergyCompFlag == TRUE)){

         MsDataPtr->TotalPts = (UINT32)(RunningPreset.WeldTime * 1.5);
         if(MsDataPtr->TotalPts > WELDTIMEMAX)  /*-- WELDTIMEMAX = 30000 --*/
             MsDataPtr->TotalPts = WELDTIMEMAX;
         
         /*-- Add 100ms before trigger and 100ms after hold --*/
         MsDataPtr->TotalPts += AddedTimeValue;
      }
      /*-- If time is NOT extended due to Energy Compensation --*/
      else
         MsDataPtr->TotalPts = (UINT32)(RunningPreset.WeldTime + AddedTimeValue);    /* 200 = 100ms before trigger */
                                                                                     /*       100ms after hold     */    
      /* Check if HoldTime is Off */
      if((RunningPreset.HoldTimeFlag & BIT0) == FALSE){
         MsDataPtr->TotalPts += (UINT32)RunningPreset.HoldTime;
      }
      
      /* Check if Trigger Delay is on */
      if((RunningPreset.TriggerDelayFlag & /*TriggerDelay.BitMask*/BIT0) == FALSE){
         MsDataPtr->TotalPts += (UINT32)RunningPreset.TriggerDelay;
      }
   }
   else{
     MsDataPtr->TotalPts = (UINT32)(RunningPreset.XScaleTime + PRETRIGMAXLIM);  /* ALL OTHER MODES no HH*/
     
     /* If manual scale is active therefore,  set flag */
     MsDataPtr->PrintBottomFlags |= MANUALSCALEFLAG;

   }
     
   if(MsDataPtr->TotalPts < (UINT32)MAX_WELD_SAMPLES)
      MsDataPtr->TotalPts = (UINT32)MAX_WELD_SAMPLES;

   if(MsDataPtr->TotalPts > (UINT32)COMPRESS){
     MsDataPtr->IncrementPts = ((FLOAT)MsDataPtr->TotalPts /(UINT32)COMPRESS);
   }
   else
     MsDataPtr->IncrementPts = 1;

   
   /*-- Number of records to select for last 100ms before TRIGGEREDSTATE --*/
   /*-- and first 100ms after HOLDTIMESTATE  --*/

   MsDataPtr->CopyPts = (UINT16)(PRETRIGMAXLIM / MsDataPtr->IncrementPts);
   
   if (MsDataPtr->CopyPts > PRETRIGMAXLIM) MsDataPtr->CopyPts = PRETRIGMAXLIM;
   else if (MsDataPtr->CopyPts < PRETRIGMINLIM) MsDataPtr->CopyPts = PRETRIGMINLIM;

/* If HandHeld is selected then collect the minimum number of useless pretrig points */

   if (CurrentSetup.HandHeld == TRUE) MsDataPtr->CopyPts = PRETRIGMINLIM;

   StopPts = MAX_WELD_SAMPLES - MsDataPtr->CopyPts;
   MsDataPtr->NewInc = MsDataPtr->IncrementPts;
   ConvNewInc = (UINT32)MsDataPtr->NewInc;
   
   PrintEveryCycleFlag = CheckPrintingStatus();

   
   PrinterTotalCount = MsDataPtr->TotalPts;
   PrinterIncPoints = MsDataPtr->IncrementPts;
   PrinterCopyPts = MsDataPtr->CopyPts;
   PrinterNewInc = MsDataPtr->NewInc;
   ColdStartDone = FALSE;          /*--  Reset to FALSE: cold start not done --*/ 
}
    




/**------------------------------------------------------------**
 ** This function also initializes all the key data collection **
 ** variables at the Palm button state                         **
 **------------------------------------------------------------**/
void Init1msPts(void)
{

   /* TRUE: function is used once during weld cycle */
   /* reinitialize values to 0 when restart */
   
   NewDurCt     = 0;
   NewPostCt    = 0; 
   PreTrigCt    = 0;
   DurTrigCt    = 0;
   PostHoldCt   = 0;
   PostEndCt    = 0; 
   DataCount    = 0;
   DataGetValue = 0;
   MsDataPtr->BufferWrapFlag = FALSE;
   MsDataPtr->NewPreCt = 0;
   MsDataPtr->count = 0;
   MsDataPtr->NewInc = MsDataPtr->IncrementPts;
   ConvNewInc   = (UINT32)MsDataPtr->NewInc;
   SonicsCt     = 0;                    
   MsDataPtr->EndOfSonicCt = 0;
}
 

/**-------------------------------------------------------**
 ** Function will accummulate up to 100ms of data before  **
 ** the TRIGGEREDSTATE and copy each sample to the array  **
 ** structures. If (CopyPts) samples is copied to the     **
 ** buffer is reset to form a circular buffer.If a        **
 ** wraparound occurs BufferWrapFlag will be set to TRUE  **
 ** and NewPreCt will be the number of records stored     **
 ** NewPreCt is the index which keep track of the position**
 ** one spot beyond of the last point written.            **
 **-------------------------------------------------------**/
void PreTrigState(void)
{
      MsDataPtr->Power[MsDataPtr->NewPreCt] = (UINT16)CurrentPowerIn;
      MsDataPtr->Amp[MsDataPtr->NewPreCt]   = (UINT16)CurrentAmpIn;
      MsDataPtr->Freq[MsDataPtr->NewPreCt]  = CurrentFreqIn;
      MsDataPtr->Force[MsDataPtr->NewPreCt] = CurrentForce;
      MsDataPtr->Dist[MsDataPtr->NewPreCt]  = EncoderPos;
      MsDataPtr->NewPreCt++;
        
      if(MsDataPtr->NewPreCt >= MsDataPtr->CopyPts){   
        MsDataPtr->NewPreCt = 0;
        MsDataPtr->BufferWrapFlag = TRUE;
      }
  
      /*-- Always start trigger at CopyPts --*/
      DataCount  = MsDataPtr->CopyPts;
      NewDurCt   = MsDataPtr->CopyPts;
      MsDataPtr->count = DataCount;
      MsDataPtr->DontPrintGraph = TRUE;       /* TRS not reached as yet  */
}



/**-----------------------------------------------------**
 ** This function will accumulate  up to 400 points     **
 ** based on the TRIGGEREDSTATE thru the FINALDATASTATE.**
 **-----------------------------------------------------**/
void DurTrigWeldHoldState(void)
{

  if(NewDurCt < MAX_WELD_SAMPLES){
   
      MsDataPtr->Power[NewDurCt] = (UINT16)CurrentPowerIn;
      MsDataPtr->Amp[NewDurCt]   = (UINT16)CurrentAmpIn;
      MsDataPtr->Freq[NewDurCt]  = CurrentFreqIn;
      MsDataPtr->Force[NewDurCt] = CurrentForce;
      MsDataPtr->Dist[NewDurCt]  = EncoderPos;
      NewDurCt++;
      NewPostCt = NewDurCt;
      DataCount = NewDurCt;
      MsDataPtr->count = DataCount;
  }

}



/**-----------------------------------------------**
 ** This function will accumulate the 100ms data  **
 ** after the HOLDTIMESTATE.                      **
 **-----------------------------------------------**/
void PostHoldtimeState(void)
{

  if(NewPostCt < MAX_WELD_SAMPLES && (PostEndCt <= MsDataPtr->CopyPts )){
  
      MsDataPtr->Power[NewPostCt] = (UINT16)CurrentPowerIn;
      MsDataPtr->Amp[NewPostCt]   = (UINT16)CurrentAmpIn;
      MsDataPtr->Freq[NewPostCt]  = CurrentFreqIn;
      MsDataPtr->Force[NewPostCt] = CurrentForce;
      MsDataPtr->Dist[NewPostCt]  = 0;
      NewPostCt++;
      PostEndCt++;

      DataCount = NewPostCt;
      MsDataPtr->count = DataCount;
  }
  if(PostEndCt > PTSAFTERHOLD)
     StopDataCollection();              /* Stop 1ms data after hold + 100ms */

}





        
/**------------------------------------------------**
 ** This module will toggle betweem DataGroup0 and **
 ** DataGroup1. once FINALDATASTATE is reached.    **
 ** Before toggle occurs Printer pointer(MsPointer)**
 ** is first updated.                              **
 ** IMPORTANT NOTE: If a graph is printing toggle  **
 ** will not be allowed and weld will be shut off  **
 ** until the printer buffer is almost empty.      **
 **------------------------------------------------**/
void ChangeDataStorage(void)
{

   /*Update pointer before change*/
   MsPointer = MsDataPtr;

   switch (ToggleFlag) {


      case 0:
         MsDataPtr = &DataGroup1;      /* Set pointer to group 1            */
         ToggleFlag = 1;
         break;
    
      case 1:
         MsDataPtr = &DataGroup0;      /* Set pointer to group 2            */
         ToggleFlag = 0;
         break;
 
      default:
         MsDataPtr = &DataGroup0;
         ToggleFlag = 0;
         break;
   }
}


/**-----------------------------------------------------------**
 ** This function initializes key member variables from our 2 **
 ** data storage area to  zeros and  points the collection    **
 ** pointer MsDataPtr to DataGroup0. Infact it also points    **
 ** the MsPointer to DataGroup1. However is a recall preset   **
 ** is executed while printing, data will not be cleared out. **
 **-----------------------------------------------------------**/
void ClearDataStorage(void)
{
  
  /*-- If not printing or printing done clear all data storage --*/
  if(CheckPrintFull == 0){
     MsDataPtr = &DataGroup0;
     MsDataPtr->TotalPts = 0;
     MsDataPtr->IncrementPts = 0;
     MsDataPtr->CopyPts = 0;
     MsDataPtr->NewInc = 0;
     MsDataPtr->NewPreCt = 0;
     MsDataPtr->PrintBottomFlags = 0;
     MsDataPtr->BufferWrapFlag = FALSE;                    
     MsDataPtr->count = 0;

     MsPointer = &DataGroup1;
     MsPointer->TotalPts = 0;
     MsPointer->IncrementPts = 0;
     MsPointer->CopyPts= 0;
     MsPointer->NewPreCt= 0;
     MsPointer->NewInc = 0;
     MsPointer->PrintBottomFlags = 0;
     MsPointer->BufferWrapFlag = FALSE;                    
     MsPointer->count = 0;
     MsPointer->DontPrintGraph = TRUE;
  }

    PrinterTotalCount = 0;
    PrinterIncPoints = 0;
    PrinterCopyPts = 0;
    PrinterNewInc = 0;
 
}
