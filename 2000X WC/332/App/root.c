/* $Header:   D:/databases/VMdb/2000Series/App/ROOT.C_V   2.81.1.4   16 Jul 2013 11:39:32   hasanchez  $ */
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

/*
------------------------- MODULE DESCRIPTION -------------------------------
                                          
   Module name:   Root
                                        
   Filename:      root.c

   Function name: root

            Written by: Mark Lazarewicz 
                  Date: 1/10/96
              Language:  "C"                              


----------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author            Description
   ==========   ========   ======            ===========
        0       1/10/96    Mark Lazarewicz   initial base level root
        1       4/10/96    PJ                Deleted blanking vf    
        2       4/29/96    LAM               put <> around psos.h    
        3       05-01-96   BEKymer           Moved StartStateMachine() from library.c
        4       05-15-96   BEKymer           Added #include "state.h"
                                             Commented out unused variables
        5       07-03-96   LAM               cleanup 
        6       10-19-96   BEKymer           Added copyright message at power up
        7       01-10-97   LAM               disabled wdtask
        8       01-21-97   LAM               chged year to 1997
        9       01-30-97   LAM               moved start welder
       10       05-21-97   LAM               made strings extern 
       11.2.14  06-17-97   LAM               deleted panelmsg
       2.15     07-03-97   PhilJ             Added PSNovram and Power Supply
       2.16     07-08-97   PhilJ             Modified Power Supply Info calls.
       11.2.17  07-08-97   LAM               replaced weldtask.h with initweld.h
       12.2.18  07-29-97   LAM               deleted writefp.h
       2.20     12-31-97   BJB               Added code to set up serial port
       2.21     01-05-98   BJB               Inits remote term variables even
                                             if remote term not in use.
       2.22     01-16-98   BJB               Removed serial port init code, haven't
                                             initialized CurrentSetup yet!
       2.23     02-05-98   BJB               Initial sign-on banner goes only to
                                             front panel, because terminal init may
                                             be going on at same time.
       2.24     05-01-98   BJB               Calls RunConstructors() to init any
                                             C++ code that may be present.
       2.25     05.06.98   JBerman           Calling to ActPowerUp 
       2.26     06.10.98   JBerman           Comment out  GetActuatorInfo(PwrOnStr2);
                                             Moved it to sysmangr.c J.B
       2.27     07.10.98   BJB               Deleted commented-out call to
                                              GetActuatorInfo().
       2.28     07-30-98   BJB               Moved in system initialization code
                                              from LIBRARY.C, SYSMANGR.C, other
                                              places.
                                             Suspends before starting state machine,
                                              this now done by FPSC.
       2.29     08-03-98   BJB               If Act Novram exists but is corrupted,
                                              sets up as AED actuator, not AE. Also
                                              records "Recalibrate" alarm.
       2.30     08-19-98   BJB               Calls init routines for new screen,
                                              terminal modules.
                                             Moved code to turn terminal on to
                                              earlier location so term ALARM msg
                                              will be turned on if there are
                                              startup alarms.
       2.31     12-07-98   LAM               added 15/30 kHz changes    
       2.32     03-17-99   LAM               enabled AEF define    
       2.33     05/04/99   LAM               changed define for new psos
       2.34     05-14-99   JZ                changed WeldForceMax to WeldForceEnd    
       2.35     05-19-99   OFI               Unhardcoded AEF Actuator selection
       2.37     05-27-99   JZ                deleted NVR.Force[] element 0 through 4 
       2.38     05-27-99   LAM               deleted Hard coding of velocity table
       2.39     05-28-99   JZ                fixed ActRecover() no parameter passed
      2.39.2.1  07-19-99   JLH    Commented out erroneous NVR.LoadCell initializing;
                                   added calls to SetDefPressure, SetDefLoadCell,
                                   SetDefForce, and NvrCopyDeftoNon.
      2.39.2.2  07-20-99   LAM     Removed test code
      2.41      08-06-99   JZ      added call to InitializePV()
      2.42      09-06-99   OFI     Fixed center frequency for 15 and 30 Khz(to fix DCS issue # 3173
      2.43      10-01-99   JZ      deleted InitCopy() 
      2.44      10-01-99   JZ      deleted RunConstructors()
      2.45      10-01-99   JZ      deleted initcopy.h
      2.46      12-17-99   LAM     deleted unused error handling code
      2.47      01-21-00   JZ      fixed startup alarms for AE act. and merged to trunk
      2.48      04-19-00   JLH     Added test for AED Upgrade error and set ErrorCode accordingly.
      2.49      05-09-00   JLH     Added NO_OFFSET define for testing for AED offset.
      2.50      05-26-00   SCM     Checked in for testing by Laura, John
      2.51      06-21-00   AS      Added pSOS task for DUPS manager
      2.52      06-30-00   SRP     checkedout for testing
      2.53      07-13-00   LAM     merged preset changes with dups changes
      2.50.1.0  06-29-00   BEKymer Modified BattramAccess arguments
      2.50.1.1  07-21-00   JLH     Changed center frequencies to the defines in psnvram.h.
      2.53      07-26-00   LAM     merged all labels
      2.54      08-01-00   LAM     fixed updating top line on run screen
      2.55      08-07-00   LAM     moved DUPS q_send after power up sequence
      2.56      08-15-00   AT      Initialize test line buffers on VFD
      2.57      08-16-00   LAM     Update swconfiguration with ws info
      2.58      08-16-00   LAM     Update swconfiguration with ws info after preset is
                                   loaded
      2.60      09-26-00   JLH     Changed CheckForActChange() to ActuatorChanged = CheckForActChange().  This was done with
                                    the intent of satisfying tracker issue #3573.  It was used for the printer, instead.
      2.61/2    11-02-00   LAM     If there is a wrong actuator alarm, donot check for recal
                                   alarm (Issues 3658 & 3662)
      2.63      11-07-00   LAM     cleanup code for  actual frequency readings (Issue 3593)                               
      2.64      08-07-01   BEKymer Add code to support ASCII outputs, Remove unused ScmFail message
      2.65      08-21-01   BEKymer Detab  
      2.66      04-02-02   LAM     modified upgrade alarm to check for PSVersion and loadcell offset
      2.67      05-06-02   LAM     modified upgrade alarm to only check loadcell table not default.
      2.68      05-06-02   LAM     modified upgrade alarm to only check when an AED is attached.
      2.69      03-05-04   LAM     modified startup code to check if the bbram is initialized
      2.70      05-25-04   VSharma Modified to initialize User I/O input pointers.
      2.71      06-04-04   VSharma Modified to call CheckForVersionChange().
      2.72      06-23-04   JOY     CurrentSetup Variables are initialized after BattRam Initialization.
      2.73      07-13-04   BEKymer Set proper HWbits for system controller so
                                    J3-36 & J3-8 are assigned correctly.
      2.74      07-14-04   LAM     Configure Actuator AD clock if undefined
      2.75      07-23-04   LAM     Fixed test to check if need to Configure Actuator AD clock 
      2.76      08-23-04   LAM     Configure Actuator AD clock to slow speed when not initialized.
      2.77      04-08-05   LAM     Add loadcelloffset when there is an SBeam.
      2.78      08-19-05   Bwadia  LangIndex initialized before 'FormatRunScreenTopLine'
                                   function is called
      2.79      10-24-05   Bwadia  PMC average graph data initialized at power up
      2.80      01-03-06   Bwadia  PSFreq in currentsetup set before BBRAM initialization
                                   takes place as InitSBL() uses the same.
                                   Modified for tracker issue 3980 
      2.81      08-25-06   LAM     Modified loadcell offset for SBEAM                          
      2.82      09-04-08   YGupta  CleanUp for LangTest Project.
      2.83      09-09-08   NHAhmed CleanUp for multi-language support.
      2.81.1.2  09-10-09   BEkymer Add new define MICRO where needed
      2.81.1.3  09-22-09   YGupta  Removed Syntax error coming from Previous Checkin.
      2.81.1.4  06-26-13   HSanchezZ Updated an if before load the preset0 to check if we was updating the presets.
      
                                          
---------------------------- DESCRIPTION -----------------------------------

   This is the "root" of the Branson 332 Welder board software.

----------------------------- PSEUDO CODE -----------------------------------


--------------------------- INCLUDE FILES ----------------------------------
*/
 
                 
#include <psos.h>                /* pSOS+ operating system information        */
#include <prepc.h>
#include "bsp.h"
#include <bspfuncs.h>

#include "opcodes.h"             /* opcode typedef for the welder board         */

/* library initialization routines prototypes */
#include "rtclock.h"
#include "root.h"               
#include "library.h"
#include "objects.h"
#include "ticks.h"
#include "tickldog.h"   
#define ALLOCATE                     /* allocate storage for pointers here    */
#include "memap.h"
#include "inports.h"
#include "outports.h"
#include "min_mode.h"
#include "run_task.h"
#include "initweld.h"
#include "battram.h"
#include "state.h"
#include "statedrv.h"
#include "util.h"
#include "psnvram.h"
#include "menu.h"
#include "actnvram.h"
#include "weldmngr.h"
#include "weld_obj.h"
#include "qsm.h"
#include "tpu.h"
#include "comm_crc.h"
#include "alarms.h"
#include "menu3.h"
#include "ready.h"
#include "graphs.h"
#include "digout.h"
#include "serial.h"
#include "snsrcalb.h"
#include "sysmangr.h"
#include "rxcharcv.h"
#include "wc_isr.h"
#include "menu7a.h"
#include "menu2.h"
#include "mansensr.h"
#include "menutest.h"
#include "menu7.h"
#include "version_change.h"
#include "preset.h"
#include "command.h"

//#define INCLUDE_UNIT_TEST

#ifdef INCLUDE_UNIT_TEST
                    /* call unit test driver */
 extern unit_test();
#endif

extern void PsosTickInit(void);
extern BOOLEAN* GetInputPtr(UINT16 InputBit);
/*
--------------------------- EXTERNAL DATA ----------------------------------
*/


extern WELD_DATA WeldingResults;
extern WELD_DATA FinalResults;
extern SETUPS_Ver800 CurrentPreset;
extern SETUPS_Ver800 MinLimit;
extern SETUPS_Ver800 MaxLimit;
extern SETUPS_Ver800 RunningPreset;
extern CONFIGSETUP CurrentSetup;
extern PSNOVRAMDATA PSNvRamData;
extern UINT16 PresetNeedsToBeUpdated;
extern UINT16 PowerUpPresetReceived;
extern UINT8  *BattramHistoryPtr;
extern SINT32 AddrBattram;
extern UINT16 WeldDataOffset;
extern SINT32 ActualPeakPower;
extern SINT32 ActualForceMax;
extern UINT16 OneMilTimer;
extern UINT8 UpdateRunningPreset;
extern UINT32 WmgrQid;
extern UINT32 SysmQueueId;
extern UINT32 FpscQid;
extern UINT32 DupsQid; 
extern BOOLEAN ActuatorChanged;
extern UINT32  PresetAddress[];

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/


#define HALF_A_SECOND            500
#define FOUR_SECONDS             4000
#define MESSAGE_DELAY            (FOUR_SECONDS)

#define TEMP_FPDM_PRIORITY       254
#define TEMP_ROOT_PRIORITY       253
#define MODE_MASK                0x700
#define NEW_INTERRUPT_MODE       0x400

/* indicates to suspend this task */
#define THIS_TASK                0

#define MAX_STARTUP_ALARMS       10   /* Sets size of StartupAlarms[] array */

#define LASTWELD 49
/*
------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/

/*
----------------------------- GLOBAL DATA -----------------------------------
                        (scope is global to ALL files)
*/


/*
------------------------- PRIVATE GLOBAL DATA ------------------------------
                        (scope is global to THIS file)
*/
                                 

/*                           
-------------------------- EXTERNAL FUNCTIONS -------------------------------
*/
/*
------------------------ LOCAL FUNCTION PROTOTYPES -------------------------
*/


/*
------------------------------- CODE ---------------------------------------
*/

void root(void)
{
   SYS_STARTUP_STATUS_TYPE SysStartupStatus;   /* return status for startup */

                             /* return status from task create and start routines */

   UINT32 PsosStatus;        /* return status from psos calls */
   UINT32 OldMode;
   UINT8  StartupAlarmCount, Index;
   UINT32 StartupAlarms[MAX_STARTUP_ALARMS];  /* Array to store alarm codes */
   UINT32 BattramOffset;
   UINT32 BattramStatus;
   UINT8  *TempPtr;
   UINT16 x;
   
   /* set initial values for initialized static data */
   InitTestBuffers();
   SysStartupStatus = SYS_STARTUP_PASS; 
   
   InitializeOutputPorts();   /* Initialize 8255s and globals used */
   InitMonitorInputPorts();   /* for servicing them. */
   InitializePV();

   InitTPU();                       /* set up interrupt vectors. */
   InitQsm();
   PsosTickInit();

   QsmMap->TxdData[13] = 0x3fff;    /* Part of first-time bargraph init */
   QsmMap->TxdData[14] = 0xff3f;
   QsmMap->Spcr1.Spe = 1;           /* Enable Qspi, transfer initial data */

   t_mode( T_LEVELMASK7, 0, &OldMode );    /* Enable all interrupts */

   OneMilTimer = 0;                 /* Wait for transfer to finish */
   while(OneMilTimer<5){};


   /* Will store alarms in array during startup until system is ready */
   /* to record them. */

   StartupAlarmCount = 0;     /* No startup alarms yet */

   /* ------------------- */
   /* Create PSOS objects */
   /* ------------------- */
   /* create all objects */

   SysStartupStatus = CreatePsosObjects();


   /* Initialize some generally useful software elements */

   CommCrcGeneratorInit();

   if (SysStartupStatus !=  SYS_STARTUP_PASS)
   {
      PsosStatus = t_suspend(THIS_TASK);
   }



   /*--------------------------------------------*/
   /*    Get IDs of important message queues     */
   /*--------------------------------------------*/
   q_ident(WMGR_Q, Q_NODE_0, &WmgrQid);               /* Weld Manager */
   q_ident(SYSM_Q, Q_NODE_0, &SysmQueueId);           /* System Manager */
   q_ident(FPSC_Q, Q_NODE_0, &FpscQid);               /* Menus */
   q_ident(DUPS_Q, Q_NODE_0, &DupsQid);               /* DUPS */


   /* Read & check power supply configuration */

   ReCallPSNovram();
   StartupAlarms[StartupAlarmCount] = VerifyPSNovram();
   if (StartupAlarms[StartupAlarmCount])
      StartupAlarmCount++;

   /* Read & check actuator configuration */

   ActPowerUp();        /* Read actuator data into global NVR structure */

   /* add offset to be used during calibration and in spidd */
   if ( (NVR.ActId == NVR_AED) || (NVR.ActId == NVR_MICRO) ) 
      LoadCellOffset = LC_OFFSET;
   else 
      LoadCellOffset = 0;
   if(NVR.ForceGauge == SBEAM)
      LoadCellOffset = LC_OFFSET;
        
   /* Check for Version 8.04 - 8.05 without the offset. */
   /* This generates ErrorCode 1000. */
   if((NVR.ActId == NVR_AED) && (PSNvRamData.ControlLevel >= LEVEL_d))
   {
      if(NVR.LoadCell[0] < NO_LOADCELL_OFFSET)
      {
         /* generate recalibrate alarm with error code 1100 set */
         RecordErrorCode( ERRORCODE1100_EQ20 );
         StartupAlarms[StartupAlarmCount++] = EQ20;   /* Recalibrate Actuator */
      }
   }
 
   /* Note: If there is no actuaor Novram, then ActPowerUp will write some */
   /* reasonable initial values to NVR.  Therefore, if CheckNvrValid()     */
   /* fails, it must be because it is processing data actually read from   */
   /* Novram, not the "fake" information supplied by ActPowerUp().  It is  */
   /* therefore safe to conclude that we have an AED actuator. */

   if ( ( (NVR.ActId==NVR_AED) ||
          (NVR.ActId==NVR_AEF)||
          (NVR.ActId==NVR_MICRO) ) && (PSNvRamData.ControlLevel >= LEVEL_d))
   {
      if (!CheckNvrValid())
      {
         ActRecover();   /* Put something in there that makes sense */
         StartupAlarms[StartupAlarmCount++] = EQ10;   /* Actuator Novram */
         StartupAlarms[StartupAlarmCount++] = EQ20;   /* Recalibrate Actuator */
      }
   }   
   
   /* If 'SwVersion' is changed update the newly added parameters with default values.*/
   CheckForVersionChange();
   CurrentSetup.PSFreq = PSNvRamData.PSFrequency;   
        
   if (!CheckBattramDefaults())
      StartupAlarms[StartupAlarmCount++] = EQ8;
   
   UpdateRunningPreset = FALSE;

   /************  Read Min Preset Table from BATTRAM to DRAM  **************/
   RecallCompressedPreset( (PRESET_COMPRESSED *) PRESET_MIN_START);   /* Decompress min preset into current preset    */
   memcpy(&MinLimit, &CurrentPreset, sizeof(CurrentPreset) );         /* Now move it into min preset where it belongs */

   /************  Read Max Preset Table from BATTRAM to DRAM  **************/
   RecallCompressedPreset( (PRESET_COMPRESSED *) PRESET_MAX_START);   /* Decompress max preset into current preset    */
   memcpy(&MaxLimit, &CurrentPreset, sizeof(CurrentPreset) );         /* Now move it into max preset where it belongs */

   /***********  Read Current Setup Table from BATTRAM to DRAM  ************/
   BattramStatus = BattramAccess(BBR_READ, CONFIG_SECTION, (UINT8 *)&CurrentSetup, BBR800_CONFIG_START, sizeof(CurrentSetup));
   
   /***** Check if bbbram initialized, if not reinitialize it and generate an alarm *****/
   if(CurrentSetup.BBRInitialized != BBRAM_INIT) {
      InitializeBBR();
      CheckBattramDefaults();
      StartupAlarms[StartupAlarmCount++] = EQ8;
   }
   
   CurrentSetup.ControlLevel = PSNvRamData.ControlLevel;
   CurrentSetup.PSWatt = PSNvRamData.PSWatts;
   CurrentSetup.PSFreq = PSNvRamData.PSFrequency;   
   strcpy(CurrentSetup.PSSerialNumber, PSNvRamData.PSSerialNum);

   /* Intialize User I/O input pointers.*/
   CurrentSetup.J3_32Ptr = GetInputPtr(CurrentSetup.J3_32In);
   CurrentSetup.J3_33Ptr = GetInputPtr(CurrentSetup.J3_33In);
   CurrentSetup.J3_19Ptr = GetInputPtr(CurrentSetup.J3_19In);
   CurrentSetup.J3_17Ptr = GetInputPtr(CurrentSetup.J3_17In);
   CurrentSetup.J3_31Ptr = GetInputPtr(CurrentSetup.J3_31In);
   CurrentSetup.J3_1Ptr = GetInputPtr(CurrentSetup.J3_1In);

   if((CurrentSetup.Sclk7890Act > SLOW_CLK) || (CurrentSetup.Sclk7890Act < FAST_CLK))
   {
      CurrentSetup.Sclk7890Act = SLOWSPEED;   /* Actuator A/D SCK  */
      CurrentSetup.ClockPhase = INVERTCLK;    /* need to invert signal when using slow speed*/
   }


   GetPresetNames();


   /************  Read Preset Table from BATTRAM to DRAM  ******************/
  
   RecallCompressedPreset( (PRESET_COMPRESSED *) PRESET_RUNNING);    /* first we load the ruuning preset */
   if ((CurrentPreset.PresetUpdateComplete == FALSE) && (CurrentPreset.WeldTime != 0) )/* if we have not finished the update of preset then will load thise values and change the status to complete or if the value is empty */
   {
	CurrentPreset.PresetUpdateComplete = TRUE;
   }
   else	
   {
   	RecallCompressedPreset( (PRESET_COMPRESSED *) PRESET_0_START);   /* if the status is finished we will load the values of preset_0_start  */
   }
   



/* Calculate to correct offset for last cycle's Weld data */
   BattramHistoryPtr = (UINT8 *) BBR800_HISTORY_START;
   AddrBattram = (SINT32)BattramHistoryPtr;

   //Make sure WeldHistoryPtr is in bounds
   CheckHistoryPtrBound();
   WeldDataOffset = CurrentSetup.WeldHistoryPtr - AddrBattram;
   if(WeldDataOffset != 0)
      BattramOffset = WeldDataOffset - sizeof(WELD_DATA);
   else
      BattramOffset = (LASTWELD * sizeof(WELD_DATA));
   BattramStatus = BattramAccess(BBR_READ, HISTORY_SECTION, (UINT8 *)&WeldingResults, BattramOffset, sizeof(WELD_DATA) );

   UpdateWS_Config();           /* updates swconfiguration with weld status information */

/**  Make sure system controller flag is set so user I/O is on correct pin  **/

   if (CurrentSetup.SystemControllerFlag == TRUE) {
      UpdateHWConfiguration(PC594, TRUE);
      UpdateHWConfiguration(PC379, FALSE);
   }
   else {
      UpdateHWConfiguration(PC379, TRUE);
      UpdateHWConfiguration(PC594, FALSE);
   }
      

// need to copy all final results at power up
   memcpy(&FinalResults, &WeldingResults, sizeof(WELD_DATA) );

// need to clear alarms from last cycle
   WeldingResults.EquipmentFailureAlarms = 0;
   WeldingResults.RejectBitResult = 0;
   WeldingResults.SuspectBitResult = 0;
   WeldingResults.NoCycleAlarms = 0;
   WeldingResults.OverloadAlarms = 0;
   WeldingResults.CycleModifiedAlarms = 0;
   WeldingResults.CalibrateAlarms = 0;
   WeldingResults.Warnings = 0;

   PresetNeedsToBeUpdated = TRUE;
   FormatRunScreenTopLine();

   /*Populate PMC Average data points*/
   if ((CurrentSetup.ActivePreset >= PRESET_1) && 
       (CurrentSetup.ActivePreset <= PRESET_16))
   {
      TempPtr =  (UINT8 *) PresetAddress[CurrentSetup.ActivePreset+16];
      memcpy((UINT8 *) &CurrentPreset.PMCData, TempPtr, PMCDATAPOINTS);
   }    
   else
   {
      // Initialize PMC data points
      for (x = 0; x < PMCDATAPOINTS; x++) {         
         CurrentPreset.PMCData[x] = 0xFF;
      }
      CurrentPreset.PMCCycleCount = 0;
   }
   UpdateRPreset();
   PowerUpPresetReceived = TRUE;

   /* ** initialize serial port for host or terminal ** */

   SerialSetup(CurrentSetup.BaudRate);  /* Initialize Baud Rate */


   switch (CurrentSetup.SerialPort) {
      case TERMINAL:
         break;
         
      case COMPUWELD:
         SerialIntRxion();    /* Ints should already be on for terminal */
         break;
         
      case ASCIICOMMA:
      case ASCIITAB:
      case ASCIISPACE:
      case RS232DISABLED:
         break;
      default:          /* If none valid, then default to Compuweld */
         CurrentSetup.SerialPort = COMPUWELD;
   }
   InitReceiveBuffer();

   /* Now can record alarms we've been saving up */

   for (Index=0; Index<StartupAlarmCount; Index++)
      RecordAlarm( StartupAlarms[Index] );

   /* Update the 'SWConfiguration' for external preset selection(EP_E). */
   DealWithExtPresetChange();
   
   /*-- Needed to Initalize MsDataPtr and MsPointer pointers --*/
   /*-- to point to DataGroup0 and DataGroup1 respectively   --*/
   /*-- Also initalize graph variables to zeros at power up. --*/
   ClearDataStorage();

   
   ActuatorChanged = CheckForActChange();

   /* Get Actuator type */
   
   if(CurrentSetup.Actuator != AE )
      TrsDisabled();
   else
      TrsEnabled();

   
   if(CurrentSetup.PeakPowerWattsFlag == TRUE)
   {
	   ActualPeakPower = ThreeRuleWattsToPorcentage(FinalResults.PeakPower,CurrentSetup.PSWatt);
   }
   else
   {
	   ActualPeakPower = FinalResults.PeakPower;
   }

   ActualForceMax = FinalResults.WeldForceEnd;

   InitWeldSequencer();

   SysSetVector( V_MSINT, MsInt, NORMAL_WRAPPER);  /* Run full 1ms int code */

   StartWelder();            /* Start some tasks */
   StartMinimalTaskSet();    /* Start other tasks */

   t_suspend(THIS_TASK); 

}
