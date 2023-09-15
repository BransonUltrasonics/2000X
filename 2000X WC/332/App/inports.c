/* $Header:   D:/databases/VMdb/2000Series/App/INPORTS.C_V   2.87   12 Nov 2010 13:16:36   bkymer  $ */
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
 ---------------------------- MODULE DESCRIPTION -------------------------------

 ------------------------------- REVISIONS ------------------------------------

   Revision #  Date      Author       Description
   ==========  ========  ======       ===========
     0         12/22/95  M Lazarewicz Initial lowlevel driver
     1         3/28/96   LAM          Changed GetInputs
     2         8/05/96   LAM          added 2c changes 
     3         08-14-96  BEKymer      Moved ground detect to external lls input
     4         9/18/96   LAM          set general alarm on an overload
     5         09-19-96  BEKymer      Don't reset external abort flag (now
                                      done in EPreReady in Ready.c)
     6         10-11-96  BEKymer      Attempt to debounce inputs
                                      Look at external reset & display lock
     7         10-18-96  BEKymer      Look at power supply signals (run, seek,
                                      store and clear)
     8         11-14-96  BEKymer      No longer turn on cooling value when
                                      not at upper limit switch
     9         01/16/97   LAM         added ae trigger switch           
    10         01-20-97   LAM         add trigger switch active          
    11         01-30-97   LAM         added dooropen test
    12         02-04-97   LAM         chged dooropen test
    12.01      02-06-97   LAM         added psidle after overload
    13.0       02-14-97   LAM         moved psidle after overload
    14.0       02-15-97   LAM         added debounce(10ms) once 2pb    
    15.0       04-04-97   LAM         moved safety switch to ready.c   
    15.1       04-04-97  BEKymer      Don't allow palmbuttons to be pressed if
                                      PrinterBufferReadyFlag is not TRUE.  If
                                      they were already pressed that is okay.
                                      Change DEBOUNCE_TIME from 1 to 5
                                      Change DIGITAL_IN_RATE from 1 to 2
                                      Change PB_DEBOUNCE_TIME from 10 to 0
    16.0       04-15-97  BEKymer      More tweaking if PrinterBufferReadyFlag=FALSE
    16.1       04-29-97  BEKymer      Add PrinterOK flag when checking for PB's
    17.0       05-07-97  LAM          Add Psosready flag and timer             
    18.2.27    05-08-97  BEKymer      Make external reset send a KEY_PRESSED msg
    18.2.28    05-09-97  BEKymer      Dont set ResetReceived for external reset
    18.2.29    05-09-97  BEKymer      Cleanup InitMonitorInputPorts
    18.2.30    05-13-97  LAM          deleted psos count down timer
    19.00      05-14-97  LAM          need psos count down timer, decrease time to 200 
    20.00      05-15-97  LAM          added readyok flag                               
    21.00      06-02-97  LAM          added printernotready flag                               
    22.00      06-09-97  LAM          increased psosdelay from 200 to 220                      
    23.2.36    06-24-97  LAM          deleted missingpart input                                
    23.2.37    07-01-97  LAM          made isr for store signal                                
    20.2.38    07-16-97  BEKymer      Added ThermalOLFlag
    23.2.39    07-28-97  LAM          turn on memstore output                                  
    23.2.40    08-07-97  BEKymer      Use ThermalOLFlag as threshold counter
    24.2.41    08-11-97  LAM          deleted digital rate call monitor inputs every other ms
    25.2.42    08-20-97  LAM          fixed polarity of inp.poweron                           
    2.43       08-29-97  BEKymer      Remove ready output when printer buffer full
    2.44       08-31-97  LAM          clear clear & store when entering ready 
    2.45       09-11-97  PaulG        Unit Test and cleanup data.
    2.46       10-09-97  BEKymer      Change DEBOUNCE_TIME from 5 to 7
    2.47       10-17-97  LAM          Change DEBOUNCE_TIME back to 5, moved dooropen to
                                      spidd
    2.48       10-23-97  PaulG        Removed PrinterNotReady.
    2.49       11-13-97  BEKymer      Changed OLRESETTHRESHOLD to 25
    2.50       11-19-97  BEKymer      Start reset process when O/L detected
    2.51       01-27-98  BJB          GetInputData() turns Inp.PSClear off if signal is off.
    2.52       01-28-98  BJB          Added extra protection for power-down signal
    2.53       02-03-98  BJB          Rewrote debounce routine to do bitwise debounce
                                      Doesn't debounce power supply signals
    2.54       04-17-98  LAM          added debounce to the overload input               
    2.55       07.06.98  JBerman      Added: AETrigger = FALSE;
    2.56       05-10-98  LAM          deleted == on line 313 InputPort->BothPB == TRUE               
    2.57       09-05-00  BEKymer      Changed OLRESETTHRESHOLD from 25 to 200 (100 ms)
    2.58       09-28-00  LAM          Changed OLRESETTHRESHOLD from 200 to 2000 (1 s)
                                      this needs to be increased in order for the 
                                      DUPS info to be received before the OL is cleared
                                      Issue(3553)
    2.59       10-03-00  LAM          Need to save OL during hornscan Issue(3597)
    2.60       10-09-00  AT           EStop fix - added ESopState and changed GetInputData
    2.61       10-09-00  AT           Turn Reset LED on if there were no alarms and EStop was pressed
    2.62       10-15-00  AT           Turn Reset LED on if someone turned it off somewhere else
                                      Turn Reset LED on only when EStop is released if there were no alarms
    2.63       04-11-01  BEKymer      Deal with new entry in INBITS structure (SingleStart)
                                      Force Trigger, DoorOpen, uls and AETrigger to FALSE when
                                       HandHeld is turned on.
    2.64       04-24-01  LAM          Deal with new entry in INBITS structure (PresetCode), do not
                                      enter ready when External Presets = On & there is something
                                      being added to the print buffer
    2.65       04-30-01  BEKymer      Allow either OnePB or ExternalTrigger to set SingleStart
                                       to allow for possible future use.
    2.66       05-03-01  BEKymer      Set AETrigger equal to SingleStart (allows
                                       CheckForTriggerLost to work)
    2.67       10-10-02  BEKymer      Make LastInputP0, P1 and P2 not static so
                                       diagnostics can access them.                                                                          
    2.68       07-11-03  JOY          Graph Data Drawing Check has been done before
                                      Processing inputs, in 'GetInputData()'.
    2.69       02-20-04  VSharma      Added ProcessUserCnfgInput(), IsConfigured() & GetActiveInputState().
                                      Modify GetInputData() for uls, ExtTrigger, GndDet and Trigger input.
    2.70       03-09-04  VSharma      Changed naming Convention for UserI/O variables.
    2.71       03-12-04  VSharma      Modified GetInputData().
                                      Removed ProcessUserCnfgInput(),IsConfigured() & GetActiveInputState().
    2.73       04-06-04  VSharma      Modified GetInputData() for MemReset & SVInterlock input.
    2.74       04-23-04  VSharma      Send MemoryReset signal for DUPS also.
    2.75       05-03-04  VSharma      Removed J3_2In as a UserConfigurable pin.Make it fixed for ECycleAbort.
                                      Added J3_1In as a new User configurable input pin.
                                      Make 'ExternalTrigger' as a user configurable input.
                                      Code for new input 'SyncIn' and output 'SyncOut' is added.
    2.76       05-11-05  VSharma      Changed GetInputData() for memory reset.
    2.77       05-18-04  VSharma      Added ProcessMemoryReset().
                                      Changed GetInputData() for memory reset.
    2.78       05-21-04  VSharma      Added check to process MemoryReset only in ready 
                                      or pre-ready state.
    2.79       07-05-04  JOY          Modified GetInputData() code.
    2.80       07-08-04  JOY          DisplayLock is modified in GetInputData().
    2.81       07-12-04  BEKymer      Invert Sync out outputs
    2.82       08-06-04  JOY          Memory reset signal ignored while processing previous one.
    2.83       01-09-06  LAM          Hold PS in reset when in ESTop
    2.87       11-12-10  BEKymer      Move 2.83 to tip


 ------------------------------- DESCRIPTION -----------------------------------

    This routine monitors the input ports P0_IN and P1_IN and P2_IN.
    If a change is detected a message is sent to the ????
    manager which will act upon the change.  Currently 10 ms of debouncing
    is performed. This routine is called from the tick ISR.
    

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include <psos.h>                   /* defines used as interface to psos    */
#include "digout.h"
#include "inputs.h"                 /* typedefs for welder input ports      */
#include "memap.h"                  /* function prototypes                  */                                                                                                 
#include "inports.h"                /* function prototypes                  */                                                                                                 
#include "preset.h"                 /* function prototypes                  */                                                                                                 
#include "kpresmsg.h"               /* Needed for FP_KEY_PRESSED_MSG        */
#include "ready.h"
#include "alarms.h"
#include "led.h"
#include "outports.h"
#include "dups_api.h"
#include "dups.h"

 
/*------------------------------ EXTERNAL DATA -----------------------------*/

extern UINT16 ExternalCycleAbortGoneFlag;
extern UINT16 ResetReceivedFlag;
extern UINT16 PsosReadyFlag;
extern UINT16 ThermalOLFlag;
extern BOOLEAN ECycleHistFlag;
extern UINT32 FpkpQid;
extern UINT16 TotalAlarmCount;
extern BOOLEAN IsThereDataPrinting;
extern BOOLEAN IsGraphDrawing;
extern BOOLEAN DispLockConfigured;
extern BOOLEAN IsRecalledPreset;

extern CONFIGSETUP CurrentSetup;


UINT16 PrinterBufferReadyFlag = TRUE;
UINT16 ExternalResetHistory;
UINT16 MemoryResetHistory = TRUE;

BOOLEAN HornScanOL = FALSE;
UINT8 AETrigger;
UINT16 MemoryResetFlag = FALSE;
UINT16 DUPS_WaitTimer = FALSE;
/*------------------------------ LOCAL DEFINES -----------------------------*/

#define SYS_STARTUP_PASS   0
#define SYS_STARTUP_FAIL   1
#define LEVEL2C            1
#define DEBOUNCE_TIME      5    /* Actual debounce time is DEBOUNCE_TIME    */ 
#define DIGITAL_IN_RATE    2    /* times DIGITAL_IN_RATE.                   */
#define PDOWN_DEBOUNCE   100
#define PB_DEBOUNCE_TIME   0    /* Additional time for palm button debounce */
#define PSOS_TIME        220
#define OLRESETTHRESHOLD 2000   /* Wait time before OL is considered thermal*/
                                /* This time includes the debounce time     */
                                /* This number is twice as big as desired because */
                                /* both PSReset() & GetInputData() increment the  */
                                /* counter (ThermalOLFlag) every ms.              */


   /* The following definitions specify bits that are NOT debounced */

#define NO_DEBOUNCE_0      0x0F
#define NO_DEBOUNCE_1         0
#define NO_DEBOUNCE_2         0

#define MEMCLEAR_TIMEOUT     15
#define DUPS_WAIT_TIMEOUT    500
#define STATE_NONE            0
#define START_MEMRST          1
#define DOWNLOAD_DUPS         2
#define DUPS_WAIT_MEMCLR      3
#define ALG_WAIT_MEMCLR       4

/*------------------------- LOCAL TYPE DECLARATIONS ------------------------*/
void ProcessMemoryReset(void);
/*------------------------------ GLOBAL DATA -------------------------------*/
/*                      (scope is global to ALL files)                      */


/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/
/*                      (scope is global to THIS file)                      */

INPUT_PORT_P0_UNION_TYPE       LastInputP0;    
INPUT_PORT_P1_UNION_TYPE       LastInputP1;      
INPUT_PORT_P2_UNION_TYPE       LastInputP2;      


static UINT8  Port0[DEBOUNCE_TIME];
static UINT8  Port1[DEBOUNCE_TIME];
static UINT8  Port2[DEBOUNCE_TIME];

static UINT16 DebounceIndex = 0;
static UINT16 InputCounter = 0;
static UINT16 PBDebounceCounter = PB_DEBOUNCE_TIME;
static UINT16 PowerDownFudgeCounter = 0;  /* Extra dbounce for pdown signal */

static UINT32 PsosReturnValue;       /* holds status from PSOS calls   */
static BOOLEAN BothPBDebounceFlag = FALSE;

BOOLEAN  PrinterOK;
BOOLEAN  ReadyOK;
static UINT16 PsosReadyCounter = PSOS_TIME;
extern INBITS Inp; 
ESTOP_STATE EStopState;
extern BOOLEAN SVInterlockActive;
extern enum WELDSTATES WeldState;
UINT16 MemoryResetState = STATE_NONE;
/*---------------------------------- CODE ----------------------------------*/

void  MonitorInputPorts(void)
{
   UINT8  ANDResult0, ANDResult1, ANDResult2;
   UINT8  ORResult0, ORResult1, ORResult2;
   UINT8  SameMask0, SameMask1, SameMask2;
   UINT8  CurrentPort0, CurrentPort1, CurrentPort2;
   UINT16 LocalIndex;


/**  Get the current value of the input ports **/

//   if (++InputCounter >= DIGITAL_IN_RATE) {
//      InputCounter = 0;

      CurrentPort0 = Port0[DebounceIndex] = InputPort0Ptr->value;   /* Actually read the hardware */
      CurrentPort1 = Port1[DebounceIndex] = InputPort1Ptr->value;   /* ports right here.          */
      CurrentPort2 = Port2[DebounceIndex] = InputPort2Ptr->value;
      if (++DebounceIndex >= DEBOUNCE_TIME) DebounceIndex = 0;

      /* Bitwise debounce algorithm: AND last DEBOUNCE_TIME bytes together */
      /* from each port to create ANDResultx.  OR last DEBOUNCE_TIME bytes */
      /* to create ORResultx.  If a bit is the same in all samples, it will */
      /* be either 1 in ANDResult (all samples were 1) or 0 in ORResult */
      /* all samples were 0).  Complement the ORResult, now a 1-bit in */
      /* either mask corresponds to a bit that is the same in all samples. */
      /* OR together ANDResult and ~ORResult, we have a mask of all bits */
      /* that are the same in all samples. */

      /* Having done all that, now just use this mask to strip bits out of */
      /* LastInputPx.value and substitute the new bits from the port. */

      ANDResult0 = ORResult0 = Port0[0];
      ANDResult1 = ORResult1 = Port1[0];
      ANDResult2 = ORResult2 = Port2[0];

      for (LocalIndex = 1; LocalIndex < DEBOUNCE_TIME; LocalIndex++)
      {
         ANDResult0 &= Port0[LocalIndex];
         ANDResult1 &= Port1[LocalIndex];
         ANDResult2 &= Port2[LocalIndex];
         ORResult0 |= Port0[LocalIndex];
         ORResult1 |= Port1[LocalIndex];
         ORResult2 |= Port2[LocalIndex];
      }

      SameMask0 = ANDResult0 | (~ORResult0) | NO_DEBOUNCE_0;
      SameMask1 = ANDResult1 | (~ORResult1) | NO_DEBOUNCE_1;
      SameMask2 = ANDResult2 | (~ORResult2) | NO_DEBOUNCE_2;

      LastInputP0.value = (LastInputP0.value & (~SameMask0)) | (CurrentPort0 & SameMask0);
      LastInputP1.value = (LastInputP1.value & (~SameMask1)) | (CurrentPort1 & SameMask1);
      LastInputP2.value = (LastInputP2.value & (~SameMask2)) | (CurrentPort2 & SameMask2);

//   }
}



/*--------------------------- MODULE DESCRIPTION ---------------------------

               Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
     0             12/22/95      Mark L      Initial

 ------------------------------- DESCRIPTION -----------------------------------
 init routine for this function
 ------------------------------- PSEUDO CODE -----------------------------------
 initialize statics
 ---------------------------------- CODE ---------------------------------------
*/

UINT8 InitMonitorInputPorts(void)
{                    
   UINT8  SysStartupStatus;

/*---  Now begin the code...  ---*/   

   SysStartupStatus = SYS_STARTUP_PASS;              /* Always pass startup */
         

/*---  Zeros will force a read the first time through  ---*/

   LastInputP0.value      =  0;
   LastInputP1.value      =  0;
   LastInputP2.value      =  0;

   return(SysStartupStatus);
}



void GetInputData(INBITS *InputPort){
 
   FP_KEY_PRESSED_MSG FpkpQueue;
   
   /* Change Input status according to logic level selected in Custom menu. */
   if (LastInputP1.port.uls_signal == CurrentSetup.ULSLogicCustom)
   {
      InputPort->uls = TRUE;
//      SV3Off();                        /* Removed for DCS # 683 */
   }
   else{
      InputPort->uls = FALSE;
//      SV3On();                         /* Removed for DCS # 683 */
   }

/* once two palmbuttons pressed they must be lost for PB_DEBOUNCE_TIME */
/* Need to wait for printing to be complete when External Presets = On */
   if ((PrinterBufferReadyFlag == TRUE) &&    /* Proceed normally if printer ready */
       (PsosReadyFlag == TRUE) && (IsThereDataPrinting == FALSE) &&
       (IsGraphDrawing == FALSE)  || (CurrentSetup.ExtPresets == FALSE))
   {   
      PrinterOK = TRUE;
      ReadyOK = TRUE;
      if ((!LastInputP1.port.pb2_signal) 
         && (!LastInputP1.port.pb1_signal)) {
         InputPort->OnePB = TRUE;
         InputPort->BothPB = TRUE;
         BothPBDebounceFlag = TRUE;
         PBDebounceCounter = 0;     /* reset counter */
      }
      else if ( (!LastInputP1.port.pb1_signal)
         || (!LastInputP1.port.pb2_signal )) {
         InputPort->OnePB = TRUE;
         InputPort->BothPB = FALSE;
         PBDebounceCounter++;     /* start counter */
      }
      else {
         InputPort->OnePB = FALSE;
         InputPort->BothPB = FALSE;
         PBDebounceCounter++;     /* start counter */
      }
   
      if((InputPort->BothPB == FALSE) && (BothPBDebounceFlag == TRUE) &&
           (PBDebounceCounter <= PB_DEBOUNCE_TIME)){
         InputPort->OnePB = TRUE;
         InputPort->BothPB = TRUE;
      }
      else{ 
         BothPBDebounceFlag = FALSE;
        }
   }
   else {
/*--------------------------------------------------------------------------*/
/* Printer not ready, only allow PB's to go away, but not be pressed again  */
/*--------------------------------------------------------------------------*/

      if(PrinterBufferReadyFlag == TRUE)
         PrinterOK = TRUE;
      else {
         PrinterOK = FALSE;
         ClearReady();               /* Remove Welder Ready signal          */
      }
      ReadyOK = FALSE;
      if(PsosReadyFlag == FALSE){
         if(--PsosReadyCounter <= 0){
            PsosReadyCounter = PSOS_TIME;
            PsosReadyFlag = TRUE;
         }
      }
      if ((!LastInputP1.port.pb2_signal) 
         && (!LastInputP1.port.pb1_signal) && (InputPort->BothPB == TRUE)) {
      }
      else if ( (!LastInputP1.port.pb1_signal)
         || (!LastInputP1.port.pb2_signal) && (InputPort->OnePB == TRUE)) {
         InputPort->BothPB = FALSE;
      }
      else {
         InputPort->OnePB = FALSE;
         InputPort->BothPB = FALSE;
      }
   }

   if (CurrentSetup.Actuator == AE) {
      if (LastInputP1.port.trig_sw_signal)
      {
         InputPort->Trigger = TRUE;
         AETrigger = TRUE;
         TrigSwInactv();
      }
      else{
         InputPort->DoorOpen = FALSE;
         AETrigger = FALSE;
      }
   }                            
   else{
      AETrigger = FALSE;
   }

   if(LastInputP0.port.power_on_signal)
      InputPort->PwrOn = TRUE;
   else
      InputPort->PwrOn = FALSE;

   if(LastInputP0.port.power_off_signal)
   {                    /* Power down must read ON a long time before react */
      PowerDownFudgeCounter++;
      if (PowerDownFudgeCounter == ((PDOWN_DEBOUNCE/DIGITAL_IN_RATE) - DEBOUNCE_TIME))
         InputPort->PwrOff = TRUE;
   }         
   else                 /* As soon as it goes off, reset counter to zero */
   {
      PowerDownFudgeCounter = 0;
      InputPort->PwrOff = FALSE;
   }

   if(!LastInputP0.port.mem_clear_signal)
      InputPort->PSClear = TRUE;
   else
      InputPort->PSClear = FALSE;

   if(!LastInputP0.port.seek_signal)
      InputPort->PSSeek = TRUE;
   else
      InputPort->PSSeek = FALSE;

   if(!LastInputP0.port.run_signal)
      InputPort->PSRun = TRUE;
   else
      InputPort->PSRun = FALSE;

   if(LastInputP0.port.overload_input_signal) {
      InputPort->OL = FALSE;
      ThermalOLFlag = FALSE;
   }
   else {
      PSReset();                             /* Start reset process         */
      if (ThermalOLFlag != 0) {
         ThermalOLFlag++;                    /* Start counting, P/S is slow */
         if (ThermalOLFlag >= OLRESETTHRESHOLD) {    /* If non zero then    */
            RecordAlarm(EQ7);                        /* reset was attempted */
            ThermalOLFlag = FALSE;
         }
      }
      InputPort->OL = TRUE;
      HornScanOL = TRUE;                     /* Set incase we are in a horn scan */
      
   }

   // if button pressed - set our flag as well
   if (LastInputP1.port.e_stop_signal){
      EStopState = ESTOPBTN_PRESSED;
	  EStopReset();
   }

   // if button is released and our flag was set - set flag to released
   // so internally it will still be active

   if ((!LastInputP1.port.e_stop_signal) && (EStopState == ESTOPBTN_PRESSED))
      EStopState = ESTOPBTN_RELEASED;

   // someone turned Reset LED off somewhere else?
   if ((EStopState == ESTOPBTN_RELEASED) && (ResetLedRequiredState == FALSE))
      UpdateLED(RESETLED, ON);

   // set EStop to TRUE if our flag is pressed or released
   InputPort->Estop = (EStopState != ESTOPBTN_RESET);

   /* Change Input status according to logic level selected in Custom menu. */
   if (LastInputP1.port.ext_ls_signal == CurrentSetup.GndDetLogicCustom)
   {
      InputPort->GndDet = FALSE;
   }
   else{
      InputPort->GndDet = TRUE;
   }

   if (LastInputP2.port.external_reset_signal) {
      InputPort->ExternalReset = FALSE;
      ExternalResetHistory = FALSE;
   }
   else {
      InputPort->ExternalReset = TRUE;
//      if ((ResetReceivedFlag == FALSE) && (ExternalResetHistory == FALSE)) {
      if (ExternalResetHistory == FALSE) {
         ExternalResetHistory = TRUE;
//         ResetReceivedFlag = TRUE;
         FpkpQueue.key = ResetKey;   
         FpkpQueue.common.opcode = OP_FRONT_PANEL_KEYPRESS;
         PsosReturnValue = q_send(FpkpQid, &FpkpQueue);
      }
   }

   /* Change Input status according to logic level selected in UserI/O menu. */
   if (LastInputP2.port.ext_cycleabort_signal)
   {
      InputPort->ECycleAbort = FALSE;
   }
   else {
      InputPort->ECycleAbort = TRUE;
   }
   /* Assign current value in actual flag for ECycleAbort.  */
   if (InputPort->ECycleAbort == TRUE) ECycleHistFlag = TRUE;
   if (InputPort->ECycleAbort == FALSE) ExternalCycleAbortGoneFlag = TRUE;

   /* Initialize all Configurable inputs. */
   InputPort->ExtTrgDelay = FALSE; /* In case this input is not configured currently.*/
   InputPort->DisplayLockFlag = FALSE;/* In case this input is not configured currently.*/
   InputPort->ExternalTrigger = FALSE;/* In case this input is not configured currently.*/
   InputPort->SonicDisable = FALSE; /* In case this input is not configured currently.*/
   InputPort->MemReset = FALSE; /* In case this input is not configured currently.*/
   InputPort->SVInterLock = FALSE; /* In case this input is not configured currently.*/
   InputPort->SyncIn = FALSE; /* In case this input is not configured currently.*/
   InputPort->Preset1 = 0;		/* In case J3_32 port assigned to PresetCode */
   InputPort->Preset2 = 0;		/* In case J3_33 port assigned to PresetCode */
   InputPort->Preset4 = 0;		/* In case J3_19 port assigned to PresetCode */
   InputPort->Preset8 = 0;		/* In case J3_17 port assigned to PresetCode */
   InputPort->Preset16 = 0;     /* In case J3_31 port assigned to PresetCode */

   if(CurrentSetup.UserInLogic)
   {
      /******* Read J3-32  ******/
      if(LastInputP2.port.J3_32_signal) 
         *CurrentSetup.J3_32Ptr = TRUE;
         
      /******* Read J3-33  ******/
      if(LastInputP2.port.J3_33_signal)
         *CurrentSetup.J3_33Ptr = TRUE;
      
      /******* Read J3-19  ******/
      if(LastInputP2.port.J3_19_signal)
         *CurrentSetup.J3_19Ptr = TRUE;
         
      /******* Read J3-17  ******/
      if(LastInputP0.port.J3_17_signal)
         *CurrentSetup.J3_17Ptr = TRUE;
      
      /******* Read J3-31  ******/
      if(LastInputP2.port.J3_31_signal)
         *CurrentSetup.J3_31Ptr = TRUE;
         
      /******* Read J3-1  ******/
      if(LastInputP2.port.J3_1_signal)
         *CurrentSetup.J3_1Ptr = TRUE;
         
      if (DispLockConfigured) {
         if  (InputPort->DisplayLockFlag) InputPort->DisplayLockFlag = FALSE;
         else InputPort->DisplayLockFlag = TRUE;
      }
      else InputPort->DisplayLockFlag = FALSE;       
   }
   else
   {
      /******* Read J3-32  ******/
      if(!LastInputP2.port.J3_32_signal) 
         *CurrentSetup.J3_32Ptr = TRUE;
         
      /******* Read J3-33  ******/
      if(!LastInputP2.port.J3_33_signal)
         *CurrentSetup.J3_33Ptr = TRUE;
      
      /******* Read J3-19  ******/
      if(!LastInputP2.port.J3_19_signal)
         *CurrentSetup.J3_19Ptr = TRUE;
         
      /******* Read J3-17  ******/
      if(!LastInputP0.port.J3_17_signal)
         *CurrentSetup.J3_17Ptr = TRUE;
      
      /******* Read J3-31  ******/
      if(!LastInputP2.port.J3_31_signal)
         *CurrentSetup.J3_31Ptr = TRUE;
         
      /******* Read J3-1  ******/
      if(!LastInputP2.port.J3_1_signal)
         *CurrentSetup.J3_1Ptr = TRUE;      
   }
    

/*---------------------------------------------------------------------------*/
/* Here deal with single start inputs.  Look at the system configuration     */
/* variable ????????.  Until V9.0 just set it equal to (OnePB OR Ext trig)   */
/*    BIT0:  set SingleStart = OnePB                                         */
/*    BIT1:  set SingleStart = Trigger                                       */
/*    BIT2:  set SingleStart = ExternalTrigger                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/

   InputPort->SingleStart = (InputPort->OnePB || InputPort->ExternalTrigger);


   if (CurrentSetup.HandHeld == TRUE) {
      InputPort->Trigger = FALSE;
      InputPort->DoorOpen = FALSE;
      InputPort->uls = TRUE;
      AETrigger = InputPort->SingleStart;  /* This allow CheckForTriggeLost to work */
   }

   /* Read each input and  assign the proper value in the PresetCode variable.*/
   Inp.PresetCode = 0;	/* Start with all zeros */
   if (InputPort->Preset1)  InputPort->PresetCode |= BIT0;	
   if (InputPort->Preset2)  InputPort->PresetCode |= BIT1;	
   if (InputPort->Preset4)  InputPort->PresetCode |= BIT2;	
   if (InputPort->Preset8)  InputPort->PresetCode |= BIT3;	
   if (InputPort->Preset16) InputPort->PresetCode |= BIT4;	
    
    
   /* This input is edge triggered. Send the Reset signal to the power supply
      on the falling edge of this input.*/
   if (InputPort->MemReset) {
      MemoryResetHistory = FALSE;
   }
   else if (MemoryResetHistory == FALSE) {
      MemoryResetHistory = TRUE;
      if(((WeldState == PREREADYSTATE) || (WeldState == READYSTATE)) &&
         (MemoryResetState == STATE_NONE))
         MemoryResetState = START_MEMRST;
   }
   if(MemoryResetState != STATE_NONE)
      ProcessMemoryReset();
  
   if (!InputPort->SyncIn && InputPort->Trigger)
      UserCfgOutputOff (OUTPUT_SYNC_OUT);  /* Make output high if Inp.SyncIn is true and */
   else                                    /* actuator is triggered.                     */
      UserCfgOutputOn (OUTPUT_SYNC_OUT);  

   /* if SVInterlock feature is not available Make Inp.SVInterlock = TRUE 
      between 'WaitSV state to Hold state . */
   if(SVInterlockActive == FALSE)
      InputPort->SVInterLock = TRUE;

}



void StoreInt(void){
   asm(" andi.w #$7fff,$fffe0a");    /* disable interrupts on the channel */
   asm(" move.w $fffe20,d0");
   asm(" andi.w #$7fff,$fffe20");    /* clear interrupt request bit */
   Inp.PSStore = TRUE;
   asm(" ori.w #$40,$fffe18");       /* drive memstore output high  */
   asm(" ori.w #$8000,$fffe0a");     /* Enable interrupts on the channel */
}

void ProcessMemoryReset(void)
/****************************************************************************/
/*Description:                                                              */
/*  This function sends the memory reset signal to the power supply and     */
/*  waits for the memory clear signal. In case of DUPS it first set the BIT3*/
/*  of SwDipSettings and download to the DUPS. After got the clear signal   */
/*  or record the alarm the BIT3 is cleared and again download to the DUPS. */
/****************************************************************************/
{
   switch(MemoryResetState)
   {
      case START_MEMRST:
         MemoryResetFlag = FALSE;
         DUPS_WaitTimer = FALSE;
         if(DUPS_Info.DUPSFlag)
         {
            if(IsRecalledPreset)
            {
               DUPS_CurrPSStatus = DUPS_PENDING;
               DUPS_UploadParamSet(CurrentSetup.DUPS_WorkingPreset);
            }
            else 
               DUPS_CurrPSStatus = DUPS_SUCCESS;
            MemoryResetState = DOWNLOAD_DUPS;
         }
         else //Analog Power supply
         {
            MemoryReset(); /* Send the memory reset signal. */
            MemoryResetState = ALG_WAIT_MEMCLR;
         }
               
      break;
            
      case DOWNLOAD_DUPS:
      //Wait until parameters are uploaded.
         if (DUPS_CurrPSStatus == DUPS_SUCCESS)
         {
            DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPCLEARMEMATRST;
            DUPS_CurrPSStatus = DUPS_PENDING;
            DUPS_DownloadParamSet(CurrentSetup.DUPS_WorkingPreset);
            MemoryReset(); /* Send Memory reset for DUPS. */
            MemoryResetState = DUPS_WAIT_MEMCLR;
            DUPS_WaitTimer = FALSE;
         }
         else if(DUPS_WaitTimer++ > DUPS_WAIT_TIMEOUT)
            MemoryResetState = STATE_NONE;
         
      break;
            
      case DUPS_WAIT_MEMCLR:
         if (DUPS_CurrPSStatus == DUPS_SUCCESS)/*Wait for the memory clear signal. */
         {
            if(MemoryResetFlag < MEMCLEAR_TIMEOUT && Inp.PSClear)  /* If non zero then    */
               MemoryResetFlag = FALSE;    /* got the memory clear signal. */
            else if(MemoryResetFlag++ >= MEMCLEAR_TIMEOUT)
            {
                RecordAlarm(CM17);/*Record MemReset alarm*/
                MemoryResetFlag = FALSE;
            }
            if (MemoryResetFlag == FALSE)
            {
                DUPS_CurrentParamSet.SWDipSetting &= ~(DUPS_SWDIPCLEARMEMATRST);
                DUPS_CurrPSStatus = DUPS_PENDING;
                DUPS_DownloadParamSet(CurrentSetup.DUPS_WorkingPreset);
                MemoryResetState = STATE_NONE;
            }
            DUPS_WaitTimer = FALSE;
         }
         else if(DUPS_WaitTimer++ > DUPS_WAIT_TIMEOUT)
            MemoryResetState = STATE_NONE;

      break;
            
      case ALG_WAIT_MEMCLR:
         if(MemoryResetFlag < MEMCLEAR_TIMEOUT && Inp.PSClear)  /* If non zero then    */
         {
            MemoryResetFlag = FALSE;/* Got the memory clear signal.*/
            MemoryResetState = STATE_NONE;
         }
         else if(MemoryResetFlag++ >= MEMCLEAR_TIMEOUT)
         {
            RecordAlarm(CM17);/*Record MemReset alarm*/
            MemoryResetFlag = FALSE;
            MemoryResetState = STATE_NONE;
         }
      break;
            
      default:
      break;
   }
}
