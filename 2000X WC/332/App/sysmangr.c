/* $Header:   D:/SWLab/VMdb/2000Series/App/SYSMANGR.C_V   2.181   05 Sep 2008 11:39:20   nhahmed  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                        **************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name: SYSTEM_MANAGER

   Filename:  sysmangr.c


            Written By:  Mark Lazarewicz 
                  Date:  1/23/96
              Language:  Microtec "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========      ======       ===========
      0           01/23/96      Mark L       Initial Version
      1           04/01/96      Mark L       Load Defualt Preset/Handle err msgs
      2           04/10/96      Mark L       Add HERE_IS_PRESET WHERE_IS_PRESET
      3           04/18/96      Mark L       Get Min and Max Presets
      4           05/02/96      Phil J       Updated OP_CHANGE_PRESET_DATA
                                             Switch statement.
      5           05/03/96      Phil J       Added new Parameters to OP_
                                             CHANGE_PRESET_DATA Switch statement.
      6           06/06/96      LAM          Added code to update running
                                             when a change occurs                
      7.0         06/20/96      Phil J       Added opcode OP_CHANGE_CURRENT_SETUP.
                                             Added parameters to CurrentPreset
                                             and CurrentSetup.
      7.01        06/20/96      Phil J       Disabled code to send CurrentSetup
                                             to NVManger.
      8           06/26/96      LAM          Chged allocation of buffers 
      8.01        07/01/96      Phil J       Added code to update CurrentPreset
                                             Flags to OP_CHANGE_PRESET_DATA.
      8.02        07/02/96      Phil J       Added UpperLimit and TrigerSw
                                             params CurrentSetup for Custom
                                             Act Logic Submenus.
      9.00        07/08/96      LAM          delete rtdwnspd,runningdata                               
      10.00       07/30/96      LAM          added forcetable                               
      11.00       08/01/96      PJ           Added variables to CurrentSetup
                                             per Spec Rev 1.C.
      12.00       08/07/96      PJ           Changed PassWord to PassWordFlag
      12.10       08/14/96      PJ           Modified OP_GOOD_PRESET to update
                                             Running Preset on Preset Recall.
      12.20       08/21/96      PJ           Corrected various CHANGE_PRESET_DATA
      12.30       08/22/96      LAM          deleted possw                        
      12.40       08/22/96      PJ           Added Opcodes for Read/Write
                                             CurrentSetup.
      12.50       09/04/96      PJ           Modification to AMPTRIGEXTFLAG id.
      12.60       09/06/96      PJ           Added SAVEPRESETZERO Id to
                                             OP_CHANGE_PRESET_DATA.
      12.70       09/11/96      PJ           Added PARAM_id SAVEPRESETZERO to
                                             OP_CHANGE_PRESET_DATA.
      12.80       09/22/96      LAM          added recall preset change                                       
      12.90       09/24/96      PJ           Added PARAM_id SAVECURRENTSET to
                                             OP_CHANGE_CURRENT_SETUP.
      13.00       09/27/96      PJ           Changed opcode OP_HERE_IS_WELD_DATA
                                             to OP_FINAL_WELD_DATA. Added
                                             circular buffer for Weld Results.
      13.10       09/30/96      PJ           Corrected Data_pointer in OP_FIANL_
                                             WELD_DATA.
      13.20       10/07/96      LAM          added global data to weld_data                                   
      13.30       10-07-96      BEKymer      Commented lines 488,489
      13.40       10/11/96      PJ           Added Alarms Check in FINAL_WELD_
                                             DATA.
      13.50       10/16/96      PJ           Changed function name CountandDisplay
                                             Alarms to CountAlarms.
      14.00       10/18/96      LAM          made function to update currentsetup                             
      14.10       10/20/96      LAM          cleanup file                             
      14.20       10/24/96      PhilJ        Alarms now get processed on any
                                             screen not just Run screen.                             
      15.00       10-28-96      LAM          converted q_send to ckqsend
      16.00       11-19-96      BEKymer      Force a null into preset string in OP_GOOD_PRESET
      16.10       12/11/96      PhilJ        Added WeldCount update In OP_FINAL_WELD_DATA        
      16.20       12/13/96      PhilJ        Update WeldData.CycleCount in
                                             OP_GOOD_PRESET.
      16.30       12/18/96      PhilJ        Enable Battery Backup of FinalWeldData.
      16.40       12/23/96      PhilJ        GetActuatorType added to OP_GOOD_
                                             CURRENT_SETUP.
      16.50       12/27/96      LAM          added initbargraph after getactuatortype
      16.60       01/02/96      PhilJ        Changed WeldDataOffset calculations.
      17.00       01/09/97      LAM          deleted displayerrormsg
      17.01       01/17/97      PaulG        Modified the way final data being copied
                                             to BATTRAM.
      17.02       01/20/97      LAM          added trsenable
      17.03       01/23/97      PhilJ        Abort alarm check added to Final Data
                                             to prevent storing data in BattRam.
      17.04       01/23/97      PhilJ        Modified OP_FINAL_WELD_DATA to allocate
                                             pointer only with good data.
      17.05       01/23/97      PhilJ        Corrected bug in FINAL_DATA check.
      17.06       01/24/97      LAM          chged alarmdetected flag, added getpresetnames          
      17.07       01/30/97      PhilJ        Added check in OP_GOOD_PRESET to control
                                             inhibit Update of RunningPreset.
      18.00       02/04/97      LAM          added updatedisplay after final data state
      18.01       02/10/97      PaulG        Restoring WeldHistoryPtr to WeldDataOffset on power up.
      18.02       02/14/97      PhilJ        Added PowerUpFlag.
      18.03       03/05/97      PhilJ        Added RunScreen test prior to
                                             sending UPDATEDISPLAY key.
      19.00       03/27/97      PhilJ        Modified code OP_FINAL_WELD_DATA
                                             Added OP_READ_ALARM_DATA opcode
      19.10       04/01/97      PhilJ        Modified OP_FINAL_WELD_DATA.
      19.20       04/09/97      PhilJ        Modified OP_READ_ALARM_DATA.
      19.30       04/10/97      PhilJ        Corrected bug in OP_READ_ALARM_DATA.
      19.40       04/18/97      PhilJ        Chngd PowerUpFlag to ReadPresetsFlag.
      19.50       04/23/97      PhilJ        Fixed code in OP_READ_ALARM_DATA.
      19.60       05/08/97      PhilJ        Added global ReadAlarmsOnly flag.
      19.70       05/13/97      PhilJ        Added GenAlarmCounter and OverLoadcounter
                                             to OP_FINAL_WELD_DATA.
      19.80       06/16/97      PhilJ        Removed Nvmanager calling Battery Backup
                                             directly from sysmangr. Added Backup
                                             CurrentSetupChange. Deleted UpdateCurrentSetup.
      19.2.74     06/17/97      PaulG        Replaced PageLength with PageSize.        
      19.2.75     06/18/97      PhilJ        Replaced WeldTimes & TestTimes with
                                             TimeMultiplier and TestMultiplier.
      19.2.76     06/19/97      PhilJ        Replaced BaudRates & Language with enum.
      19.2.77     06/20/97      PhilJ        Added param Id FORMFEED to Backup func
      19.2.78     06/23/97      PhilJ        Redefined BaudRates in menu7a.h.
      19.2.79     06/23/97      PaulG        Modified Printer types.
      19.2.80     07/03/97      PhilJ        On initialization, Currentsetup gets updated
                                             from PSNovram.
      20.2.81     07.07.97      J.B.         Adding Start Screen case
      20.2.82     07/07/97      LAM          moved getpresetnames to init
      20.2.83     07/07/97      LAM          fixed powerup currentsetup  
      20.2.84     07/07/97      LAM          updated last weld data at powerup
      20.2.85     07/11/97      PhilJ        Added HMENUINDEX and HOSTCOMPUTER
                                             to BatteryBackup.
      20.2.85     07.17.97      JBerman      Adding BootSf
      20.2.87     07.20.97      LAM          fixed sizeof currentsetup
      20.2.89     08/04/97      PhilJ        Added DIGITALFREQ & DIGITALTUNE to
                                             BackupCurrentSetup.
      2.90        08.27.97      LAM          only set remote if serialport enabled
      2.91        08/27/97      PaulG        Added case OP_CLEAR_WELDHISTORY_BBRAM.
      2.92        08.29.97      JBerman      Added : GetStrokeLenIndex(); // Init Cylinder/Srtoke Buffers for printout.
                                             GetCylinderIndex();
      2.93        09.11.97      JBerman      Added default into the switch statement 
      2.94        09-15-97      PaulG        Changed LinesPerPage to WeldsPerPage.
      2.95        09-17-97      LAM          need to update finalresults in case an
                                             at power up.
      2.96        09-19-97      LAM          eliminated preset buffer               
      2.97        09.23.97      LAM          deleted call to actnovram 
      2.98        09-24-97      LAM          moved updated historyptr from battram
      2.99        09-25-97      LAM          moved initbargraph to psnvram & actnvram
      2.100       09-26-97      LAM          made sure weldhistorypointer cannot get to big
      2.101       09-28-97      LAM          corrected weldhistorypointer wrap around       
      2.102       10-02-97      LAM          fixed power up
      2.103       10-06-97      LAM          update printed final results at power up
      2.104       10-06-97      PaulG        Corrected weldhistorypointer wrap around       
      2.105       10-07-97      LAM          chked wrap aroung of finalresults & clear alarms
      2.106       10-13-97      LAM          update actuator type at power up                 
      2.107       10-13-97      LAM          moved welddata memcpy to weldmngr, added start statemachine
                                             donot count alarms in final data state
      2.108       11-18-97      LAM          replaced finalresults with weldingresults
      2.109       11-18-97      LAM          deleted welddata
      2.110       11-24-97      LAM          deleted unused currentsetup elements
      2.111       11-26-97      LAM          deleted !currentsetup.serialenabled
      2.112       12-02-97      PaulG        Added function CheckHistoryPtrBound().
      2.113       12-05-97      LAM          deleted !currentsetup.serialenabled again
      2.115       12.10.97      JBerman      Added for correct timing:
                                             if (GetPowerSupplyFrequency() == 39950){
                                             FreqDivBy = 4;           // 40kHZ Power Supply
                                             CenterFreq = 39950;      // 40kHZ Power Supply
                                             }
                                             Added #include "util.h"
      2.116       12.31.97      BJB          Simplified serial port config code
      2.117       01.16.98      BJB          Moved serial port init code from ROOT.C
      2.118       01.22.98      BJB          Doesn't increment overload counter at end of
                                             cycle, this now done in RecordAlarm().
      2.119       01-28-98      LAM          save weldhistory pointer every cycle
      2.120       01-30-98      BJB          Doesn't increment CurrentSetup.GenAlarmCount,
                                             this moved to RecordAlarm(), RecordSetupAlarm().
      2.121       02-04-98      BJB          Now that terminal may start in data mode,
                                             moved first RemoteTermOn() call to after
                                             reading of CurrentPreset.
      2.122       02.19.98      JBerman      CurrentSetup.Features->CurrentPreset.Features
                                             DCS 2402
                                             In Addition added:
                                             BootSf();  // DCS 2402
                                             if (CurrentPreset.Features == TRUE)   // Advanced
                                                CurrentSetup.User = ADVANCED;
                                             else
                                                CurrentSetup.User = NORMAL;
      2.123       02.23.98      LAM          removed features from updatecurrentsetup      
      2.124       02.27.98      PaulG        Added new function ClearDataStorage().
      2.125       04.17.98      LAM          added calibration tables here until nvram
                                             working
      2.126       04.24.98      LAM          moved calibration tables to ResetSensorCalb
      2.127       04.24.98      JBerman      Call ActPowerUp on PowerUp
      2.128       05.01.98      JBerman      Added CheckNvrValid();
      2.129       05.01.98      BJB          Added code to write ACTLIFETIMECOUNTER to BBRAM.
                                             Commented out 2.128 change until we're ready.
      2.130       05.01.98      JBerman      Added CheckNvrValid();
      2.131       05.08.98      LAM          moved checkNvrValid after clearing alarms
      2.132       05.14.98      LAM          only call checkNvrValid when not an AE         
      2.133       05.15.98      JBerman      Removed the Def from:
                                             GetStrokeLength() & GetCylSize()
      2.134       05.27.98      JBerman      Added a condition for
                                             Actuator vs. LEVEL_d 
      2.135       05.27.98      JBerman      Fixed the above issue.
      2.136       05.27.98      JBerman      Keep working on the above issue.
      2.137       05.29.98      JBerman      Comment out RecordAlarm(EQ24)
      2.138       06.04.98      JBerman      Enabled EQ24, Actuator Type
      2.139       06.04.98      LAM          deleted getting a buffer when saving
                                             the current setup, this was causing a
                                             psos error.
      2.140       06.05.98      JBerman      Improved  Alarm(EQ24).
      2.141       06.05.98      JBerman      Removed TempActType.
      2.142       06.10.98      LAM          moved sv test after currentsetup.actuator
                                             has been updated.
      2.143       06.10.98      JBerman      Removed from root.c to sysmangr.c
                                             GetActuatorInfo(PwrOnStr2); DCS-2616.
      2.144       06.12.98      LAM          clear calibrate alarms on power up
      2.145       06-22-98      BEKymer      Change structure member ActualForceMax
                                             to WeldForceMax
      2.146       06.24.98      JBerman      Added: CheckValidForRecovery();
      2.147       06-25-98      BJB          Deleted code that writes to
                                             CurrentSetup.User, this no longer exists.
      2.148       07.02.98      JBerman      Changed CurrentSetup.Actuator to   
                                             CurrentSetup.Encoder.
      2.149       07.10.98      BJB          Adds actuator type to PwrOnStr2[] just
                                             ONCE on power-up, not every time
                                             GetActuatorInfo() called.
      2.150       07.30.98      BJB          Moved code to init SysmQueueId to
                                             root().
                                             Moved all code to read BBRAM items on
                                             startup to root().
      2.151       07.31.98      BJB          Includes kpresmsg.h, getmsg.h
      2.152       08-18-98      PaulG        Remove assignment to FinalResults.CycleCount.
      2.153       10-02-98      LAM          added test code to catch weldtime = 0   
      2.154       11-25-98      LAM          added actualforceend to be displayed for CM22
      2.155       12-07-98      BJB          Added LastWeldResultsUpdated for use by
                                             new menu code.
      2.156       04-26-99      OFI          Changed for Diab
      2.157       05-14-99      JZ           changed ActualForceEnd to WeldForceEnd, WeldForceMax
                                             to WeldForceEnd
      2.157.2.1   07-20-99      LAM          added SetForceNVR to case OP_NVM_WRITE_PARAMETERS
      2.159       09-08-99      LAM          added Set calibrated pressure and stroke to case
                                             OP_NVM_WRITE_PARAMETERS
      2.160       09-16-99      LAM          added homeoffset and springrate to case
                                             OP_NVM_WRITE_PARAMETERS
      2.161       12/16/99      LAM          removed unused error handling code
      2.161.1.0   02-23-00      OFI          removed #include "features.h";removed call to BootSF();
      2.162       04-06-00      JZ           merged Lang to trunk
      2.163       04-19-00      JLH          Added case OP_NVM_WRITE_UPGRADE for AED Upgrade.
      2.164       05-09-00      JLH          Added #define COUNTS_PER_INCH for 1024.0*10000.0.  Added 
                                              SetDefLoadCell() to OP_NVM_WRITE_UPGRADE.                                                         
      2,165       05-26-00      JLH          Changed printer type designations to OKI520, EPSONCOMP, and HPPCL.
      2.166       06-09-00      JLH          Added SENDWELDDATA and STROKELEN parameters to BackupCurrentSetupChange.
      2.167       06-28-00      BEKymer      Changed MODEL to LEVEL in  the revision
                                             Call RecallCompressedPreset() when recalling a preset
      2.168       07-13-00      BEKymer      Removed extra calls to return pSOS buffers
                                             In BackupCurrentSetupChange() always save entire 
                                               CurrentSetup as well as BUC menu stuff
      2.169       07-14-00      BEKymer      Changed define in OP_FINAL_WELD_DATA to WELD_DATA_SIZE_800
      2.170       10-18-00      BEKymer      Added 2nd arg to SaveCompressedPreset call
                                              to fix issue # 3387
      2.171       11-07-00      LAM          cleanup code for  actual frequency readings (Issue 3593)  
      2.173       04-03-02      BEKymer      Save WeldCount in BBR every cycle
      2.174       04-04-02      LAM          Update PSVersion to novram after calibration
      2.175       04-24-02      BEKymer      Save WeldCount after its updated!
      2.176       05-06-02      LAM          Do not save the default load cell table
      2.177       08-14-03      JOY          'UPDATELINE2'message is send to the QVGA queue
                                             to update alarms.
      2.178       08-27-03      JOY          Alarm message(UPDATELINE2) is send in all kind ofScreen.
      2.179       03-27-07      BEKymer      Save preset during OP_FINAL_WELD_DATA to save
                                              updated preset count.
      2.180       01-11-08   	NHAhmed      Changes done for multi-language support.
					     Removed arguments of function BackupCurrentSetupChange().
      2.181       09-05-08   	NHAhmed      Removed terminal.h from include file list.                                   
                                        
 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------- PSEUDO CODE -----------------------------------
                                                    

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include <psos.h>                             /* psos OS definitions                */
#include "string.h"
#include "names.h"                            /* application object definitions     */
#include "opcodes.h"                          /* intertask opcodes definitions      */
#include "myptrmsg.h"                         /* generic message pointer type       */
#include "genrlmsg.h"                         /* generic message type               */
#include "preset.h"
#include "param.h"
#include "wldstate.h"
#include "statedrv.h"
#include "prsetmsg.h"
#include "nvm_msg.h"
#include "weld_obj.h"
#include "battram.h"
#include "keypad.h"
#include "digout.h"
#include "menu3.h"
#include "fpdatmsg.h"                         /* edit data from fpkp                */
#include "obj_tabl.h"
#include "sysmangr.h"                          
#include "selctkey.h"                          
#include "limits.h"                          
#include "weld_msg.h"
#include "genalarm.h"
#include "ckptgbuf.h"
#include "spidd.h"
#include "snsrcalb.h"
#include "ck_qsend.h"           /* contains function interface           */
#include "actnvram.h"
#include "menu7a.h"
#include "serial.h"
#include "rxcharcv.h"
#include "psnvram.h"
#include "fpsmangr.h"
#include "alsetup.h"
#include "util.h"
#include "graphs.h"
#include "ready.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "command.h"

/* For QVGA Support */
#include "qvgamenu.h"

/*                                                                                  
 ------------------------------- EXTERNAL DATA --------------------------------- 
*/ 

extern SCREEN_TYPE CurrentScrnType; // Currently Displayed QVGA Screen Type
extern BOOLEAN QVGAHwAvail;
extern UINT8  RunScreenFlag;
extern UINT8  AlarmDetectedFlag, SetupAlarmDetectedFlag;
extern UINT8  *BattramHistoryPtr;
extern UINT8  ReadOnlyFlag;
extern SINT16 MenuCounter;
extern SINT32 AddrBattram;
extern UINT32 QvgaQid;
extern UINT32 WmgrQid;
extern UINT16 PrinterRestartFlag;

extern WELD_DATA WeldingResults;
extern WELD_DATA FinalResults;
extern PSNOVRAMDATA PSNvRamData;

extern FLOAT SpringRateSlope;
extern UINT32 PresetAddress[];

/*
 ------------------------------- LOCAL DEFINES ---------------------------------
*/                           
#define COUNTS_PER_INCH 1024.0*10000.0            /* 10000 counts per inch multiplied by a scaling factor */

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/                            
typedef union
   {
   GENERIC_MSG                     generic_msg;
   NVM_ACCESS_MSG                  NvmAccessMsg;
   PRESET_TABLE_MSG                PresetTablePtrMsg;
   WELD_DATA_MSG                   WeldMsg;
   EDIT_PARAM_MSG_QUEUE_TYPE       EditParamMsg;
   } SYSM_MSG_QUEUE_TYPE;

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

UINT8 UpdateRunningPreset;

SETUPS_Ver800 CurrentPreset;
SETUPS_Ver800 MinLimit, MaxLimit;

CONFIGSETUP CurrentSetup;

extern BUCMENU_800  *BUCMenuBBR;
extern BUCMENU_800  BUCMenuRAM;

UINT16 WeldDataOffset;
UINT8  WarningDetectedFlag;
SINT32 ActualPeakPower;
SINT32 ActualForceMax;
SINT32 WeldForceEnd;
BOOLEAN LastWeldResultsUpdated = FALSE;   // Used by C++ run screen

/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
*/
UINT32                     SysmQueueId;
UINT32                     SysmPtId;
UINT32                     PsosReturnStatus;
UINT8                     *PresetDataPtr;      /* Current destination of rcvd data            */
SYSM_MSG_QUEUE_TYPE        SysmMsgOut;
SYSM_MSG_QUEUE_TYPE        SysmMsgIn;
 
/*
 --------------------------------- CODE ----------------------------------------
*/ 

void SystemManager(void)

{                                              
   FP_KEY_PRESSED_MSG  FPKeyMsg;
   UINT8               ReadPresetsFlag = FALSE;
                                                
   UINT32              BattramOffset;
   BBR_STATUS_TYPE     BBRRetVal;

   void                *BattRamPointer;
   PRESET_COMPRESSED* CompressPreset;

   /* Get partition id of MADD partition */
   PsosReturnStatus = pt_ident (MAD_PARTITION, PT_NODE_0, &SysmPtId);

   while (FOREVER)
   {
                
      PsosReturnStatus = q_receive (SysmQueueId, Q_WAIT ,Q_WAIT_FOREVER, &SysmMsgIn);  

      switch (SysmMsgIn.generic_msg.common.opcode)
      {
         case OP_DISPLAY_MESSAGE :
            break;
 

         case OP_GOOD_CURRENT_SETUP:
            break;


         case OP_BATTRAM_READ_CURRENT_SETUP:
            break;

         case OP_BATTRAM_WRITE_PRESET:
            BattramOffset = PresetAddress[SysmMsgIn.NvmAccessMsg.offset]; 
            SaveCompressedPreset((PRESET_COMPRESSED *) BattramOffset, &CurrentPreset);
            break;

         /* read preset */
         case OP_BATTRAM_READ_PRESET:
          /* Read Preset Table from BATTRAM to DRAM */
            BattramOffset = PresetAddress[SysmMsgIn.NvmAccessMsg.offset]; 

            RecallCompressedPreset((PRESET_COMPRESSED *) BattramOffset);
            CurrentPreset.PresetID[PRESETLEN] = 0;
  
               /* Have message queue data point to new buffer */

               /* 16 Presets are read at Power Up ONLY then PRESET_ZERO is read last */
               if(!ReadPresetsFlag)
               {
                  if(SysmMsgIn.NvmAccessMsg.offset == PRESET_0)
                     ReadPresetsFlag = TRUE;
               }

               if( ((SysmMsgIn.NvmAccessMsg.offset == PRESET_0)
                   || UpdateRunningPreset) && !ReadOnlyFlag)
               {

                  SysmMsgOut.PresetTablePtrMsg.common.opcode =  OP_HERE_IS_PRESET;
                  SysmMsgOut.PresetTablePtrMsg.common.source_task = SYSM_SOURCE_TASK;
                  SysmMsgOut.PresetTablePtrMsg.msg_pointer = PresetDataPtr;
                  SysmMsgOut.PresetTablePtrMsg.byte_count = 0;
                  SysmMsgOut.PresetTablePtrMsg.partition_id = SysmPtId;
                  SysmMsgOut.PresetTablePtrMsg.common.pointer_flag = DATA_PTR_NO_DEALLOC;
                  CkQSend (WmgrQid,&SysmMsgOut,SYS_MANAGER,__LINE__,        
                           MILLS_TO_TICKS(50));
                  UpdateRunningPreset = FALSE;

                  /* Update Cycle Count */
                  // FinalResults.CycleCount = CurrentPreset.WeldCount;
               }
            break;

         case OP_GOOD_MIN_PRESET:
            break;

         case OP_GOOD_MAX_PRESET:
            break;

         case OP_MIN_PRESET_READ_FAIL:
            break;

         case OP_MAX_PRESET_READ_FAIL:
            break;

         case OP_CURRENT_SETUP_READ_FAIL:
            break;

         case OP_PRESET_READ_FAIL:
            break;

         case OP_WHERE_IS_PRESET:     
            break;

         case OP_FINAL_WELD_DATA:
            /* Calculate to correct offset for Weld data */
            BattramHistoryPtr = (UINT8 *) BBR800_HISTORY_START;
            AddrBattram = (SINT32)BattramHistoryPtr;
            
            if(WeldDataOffset == 0)
               WeldDataOffset = CurrentSetup.WeldHistoryPtr - AddrBattram;
            else if (WeldDataOffset >= WELD_DATA_SIZE_800)
               WeldDataOffset = 0;

            BattramOffset = WeldDataOffset;
            WeldDataOffset += sizeof(WELD_DATA);
            
            /* Change to SINT32 (32 bit) Variables for menu pointers */
            if(CurrentSetup.PeakPowerWattsFlag == TRUE)
            {
            	ActualPeakPower = ThreeRuleWattsToPorcentage(FinalResults.PeakPower,CurrentSetup.PSWatt);
            }
            else
            {
            	ActualPeakPower = FinalResults.PeakPower;
            }

            ActualForceMax = FinalResults.WeldForceEnd;
            WeldForceEnd = FinalResults.WeldForceEnd;
            
            /* test code to check weldtime = 0 */
            TESTCODE:
            if(FinalResults.ActualWeldTime == 0)
               asm(" nop ");
               
            /* Update Cycle Count */
            CompressPreset = (PRESET_COMPRESSED*) PRESET_0_START;   /* 1st save in Preset0 */
            CompressPreset->WeldCount = FinalResults.CycleCount;
            CurrentPreset.WeldCount = FinalResults.CycleCount;      /* Now save in current */

/***   Save preset now so updated preset count is not lost (Japan's fix)   ***/

            if (CurrentPreset.PresetUpdateComplete == TRUE)
               SaveCompressedPreset((PRESET_COMPRESSED*)PresetAddress[CurrentSetup.ActivePreset], &CurrentPreset);

/***   End of preset count Fix   ***/

            BattRamPointer = &FinalResults;
            BBRRetVal = BattramAccess( BBR_WRITE, HISTORY_SECTION, BattRamPointer, BattramOffset, sizeof(WELD_DATA) );

            BattRamPointer = &CurrentSetup.WeldHistoryPtr;
            BattramOffset = (UINT32)&CurrentSetup.WeldHistoryPtr;
            BattramOffset = BattramOffset - (UINT32)&CurrentSetup;
            LastWeldResultsUpdated = FALSE;   /* Causes latest result data */
                                              /* to be fetched for display */

            if(RunScreenFlag && MenuCounter == 1)
            {
               if(AlarmDetectedFlag)
                  SendFakeKeyPress(UPDATEDISPLAY);
               else
                  SendFakeKeyPress(UPDATELINE4);
            }
            if(PrinterRestartFlag == FALSE)
               StartStateMachine();
            break;

         case OP_SETUP_ALARM_DATA:

            SetupAlarmDetectedFlag = CheckForSetupAlarms();
            
            if (SetupAlarmDetectedFlag == TRUE) {
               CountSetupAlarms();
            }

            if ((RunScreenFlag) && (MenuCounter == 1)) {
               if (SetupAlarmDetectedFlag == TRUE)
                  SendFakeKeyPress(UPDATEDISPLAY);
               else
                  SendFakeKeyPress(UPDATELINE4);
            }
            break;

         case OP_READ_ALARM_DATA:
            AlarmDetectedFlag = TRUE;
            CountAlarms();
            
            if(RunScreenFlag && MenuCounter == 1)
            {
               SendFakeKeyPress(UPDATELINE2);              
               
            }
            
            /* If QVGA H/W is available send Message to the QVGA queue*/
            if(QVGAHwAvail)
            {
               FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
               FPKeyMsg.key = UPDATELINE2;                        
               CkQSend (QvgaQid, &FPKeyMsg, SYS_MANAGER,
                           __LINE__, MILLS_TO_TICKS(20));   /* 20 ms        */
            }   
            break;

         case OP_PRESET_WRITE_FAIL:
            break; 
           
         case OP_CHANGE_PRESET_DATA:

            SaveCompressedPreset((PRESET_COMPRESSED *) PRESET_0_START, &CurrentPreset);

            SysmMsgOut.NvmAccessMsg.common.source_task = SYSM_SOURCE_TASK;
            SysmMsgOut.PresetTablePtrMsg.common.opcode = OP_HERE_IS_PRESET;
            SysmMsgOut.NvmAccessMsg.offset = PRESET_0;
            SysmMsgOut.NvmAccessMsg.data_pointer = PresetDataPtr;
            SysmMsgOut.NvmAccessMsg.byte_count = 0;
            SysmMsgOut.PresetTablePtrMsg.common.pointer_flag = DATA_PTR_NO_DEALLOC;
            SysmMsgOut.NvmAccessMsg.partition_id = SysmPtId;

            /* send out just-formed message to Weld Manager */
            CkQSend (WmgrQid,&SysmMsgOut,SYS_MANAGER,__LINE__,        
                                MILLS_TO_TICKS(50));  
            //break;

         case OP_CHANGE_CURRENT_SETUP:
            BackupCurrentSetupChange();
            break;

              /*Clear last 50 weld history records  from BBRAM */
         case OP_CLEAR_WELDHISTORY_BBRAM:
            ClearHistoryInBbram();
            break;
         
         case OP_NVM_WRITE_PARAMETERS:             /* update to actnvram    */
            SetLoadCell();                         /* save when calibration */                                         
            SetPressure();                         /* successful            */
            SetForceNVR();
            SetCalStrokeLength();
            SetCalSysPressure();
            SetCalSpringRateSlope((UINT16)(SpringRateSlope * COUNTS_PER_INCH));
            SetCalHomeOffset();
            SetPSVersionNVR();
            break;

         case OP_NVM_WRITE_UPGRADE600:
            SetCalSpringRateSlope((UINT16)(SpringRateSlope * COUNTS_PER_INCH));
            SetCalHomeOffset();
            SetPSVersionNVR();
            break;

         case OP_NVM_WRITE_UPGRADE805:
            SetLoadCell();
            SetPSVersionNVR();
            break;
                
         default:
            break;

      } /* end of switch(SysmMsgIn.generic_msg.common.opcode) */
   }    /* end of while(FOREVER) */
}


void BackupCurrentSetupChange(void)
{
   CONFIGSETUP *BBRPtr;
   UINT16      x;

   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   BUCMenuBBR=(BUCMENU_800*) BBR800_BUCMENU_START;
   memcpy(BBRPtr, &CurrentSetup, sizeof(CurrentSetup) ); /* Save entire setup even if only 1 thing changed */
   memcpy(BUCMenuBBR, &BUCMenuRAM, sizeof(BUCMenuRAM) ); /* Save BUC menu while we're at it */
}




void CheckHistoryPtrBound(void)
/*-----------------------------------------------------------------------------*/
/* This function Checks to make sure bounds are not exceeded by WeldHistoryPtr */
/*-----------------------------------------------------------------------------*/
{
   SINT32 Start, End;

   // Calculate bounds for the weld data.
   Start = BBR800_HISTORY_START;
   End   = Start + (NMBR_OF_WELD_HISTORY * sizeof(WELD_DATA));

   if((CurrentSetup.WeldHistoryPtr < Start) ||
      (CurrentSetup.WeldHistoryPtr > End)){
      CurrentSetup.WeldHistoryPtr = BBR800_HISTORY_START;
   }
}
