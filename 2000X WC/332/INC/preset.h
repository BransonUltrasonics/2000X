/* $Header:   D:/databases/VMdb/2000Series/INC/PRESET.H_V   2.144.2.1.1.0   16 Jul 2013 12:40:02   hasanchez  $ */
#ifndef PRESET_H
#define PRESET_H
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
-------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Presets

   Filename:  preset.h


            Written by: Laura Markure, Barry Kymer 
                  Date: 12/31/95 
              Language:  "C"

------------------------------ REVISIONS ------------------------------------

   Revision #     Date        Author      Description
   ==========     ========    ======      ===========
       0          04/25/96    LAM         Initial
       1.00       06/10/96    PJ          Deleted TestDwnspd1,2,& 3 in 
                                          CONFIGSETUP structure.
       1.01       07/02/96    PJ          Added UpperLimitFlag and TriggerSwFlag
                                          to CONFIGSETUP structure.
       2.00       07/09/96    LAM         added springrate table and loadcelltbl
       3.00       07/30/96    PJ          Added ControlLimitsFlag, ABSCutoffDist
                                          ABSCutoffFlag, EnergyCompFlag to SETUPS.
       4.00       07/31/96    LAM         added pressure table and forcetable
       5.00       07/31/96    PJ          Added variables to CurrentSetup
                                          for new menus per Spec Rev 1.C
       5.10       08/07/96    PJ          Moved Spare1 & Spare2 to beginning
                                          of Setups structure to fixed unknown
                                          bug passing variables to battram.c.
       5.20       08/09/96    PJ          Added Active_Preset to CONFIGSETUP.
       5.30       08/12/96    LAM         Added deflection table to preset   
       5.40       08/26/96    PJ          CURRENT_SETUP now defined as zero.
                                          Changed SW, PS, and Actuator serial
                                          numbers to SINT8.
       5.50       09/11/96    PJ          Added MaxTimeoutFlag to CurrentPreset.
       5.60       09/11/96    LAM         Moved pressure to currentsetup
       5.70       09/25/96    PJ          Added Encoder, DVS, SecurityLevel
                                          to CurrentSetup.
       5.80       10/08/96    LAM         moved springrate table, increase force table  
       6.00       10/14/96    LAM         added calibration offset to setup             
       6.10       10/19/96    PJ          Added ActClrFlag to CurrentSetup and
                                          SuspectLimits & RejectLimits to Preset.
       7.00       10/29/96    LAM         added loadcell offset
       8.00       11/02/96    LAM         added horndown parameters
       8.10       11/05/96    LAM         added PVPoffset
       8.20       11/22/96    PHILJ       Changed CurrentSetup.PSFreq to unsigned
       8.30       11/27/96    PHILJ       Added PreSeek to CurrentPreset.
       9.00       12/11/96    LAM         Added springrateoffset         
       9.10       12/20/96    PHILJ       Added WeldHistoryPtr to CurrentSetup.
       9.20       12/21/96    LAM         rearranged calibration data    
       9.30       12/26/96    LAM         rearranged calibration data one more time    
      10.00       01/28/97    LAM         added prototypes,added missing part                             
      11.00       01/29/97    PhilJ       added CycleAbortFlag
      12.00       01/31/97    PhilJ       added MissingPartFlags & variables.
      13.00       02/07/97    LAM         moved actclr to preset             
      14.00       03/17/97    BEKymer     Added Remote to CONFIGSETUP        
      15.00       04/11/97    PhilJ       Added AutoScaleFlag and XScaleTime to
                                          CurrentPreset.
      15.01       05/13/97    PhilJ       Added PageLength to CurrentSetup.
      15.02       05/22/97    PaulG       Added OkiData ML printer.
      16.00       06/03/97    LAM         removed globalprinting flags
      *** Warning any changes to the preset or setup will effect the IRS1.01 ***
      17.2.40     06/10/97    LAM         removed weldmodeflags, missingpartlimit
      17.2.41     06/17/97    PhilJ       realigned CurrentSetup.
      17.2.42     06/17/97    PaulG       Changes PageLength to PageSize( SINT32 to UINT16).
      17.2.43     06/18/97    PhilJ       Deleted all WeldTimes and TestTimes in
                                          CurrentSetup replaced with TimeMultiplier
                                          and TestMultiplier.
      17.2.44     06/19/97    PhilJ       Chngd Baudrates & Languages to enums.
      17.2.45     06/23/97    PaulG       Chngd Printer types.
      17.2.46     06/24/97    PhilJ       Chngd PSWatt & PSFreq to UINT16.
      17.2.47     07-07-97    BEKymer     Moved function protypes from weld_obj.h
      17.2.48     07-09-97    PhilJ       Added ScrubTimeFlag to CurrentPreset
                                          Added Host to CurrentSetup.
                                          Moved HmenuIndex to CurrentSetup.
      17.2.49     07-10-97    BEKymer     Moved prototype for UpdatePreset
                                          from Weld_obj.h
      17.2.50     07-15-97    PhilJ       Deleted ProductNum from CurrentPreset
      2.51        07-17-97    PhilJ       Chngd CurrentSetup.CylinDiameter &
                                          CurrentPreset.StrokeLen to UINT16.
      18.2.52     07-28-97    LAM         deleted swversion added powertable      
      18.2.53     07-30-97    LAM         ren max_table_pts to max_cal_pts        
      18.2.54     08-04-97    PhilJ       Added DigPotFlag to CurrentSetup        
      2.55        09-12-97    BEKymer     Change PSLifeTime from UINT32 to
                                          SINT32 to eliminate warning in MENU6.c
      2.56        09-15-97    PaulG       Change LinesPerPage to WeldsPerPage.
      2.57        10.07.97    JBerman     Added: #define PageS11 1
                                                 #define PageS14 2
                                                 #define PageSA4 4
      2.58        10.15.97    kderby      Added: RemoteData
      2.59        10-29-97    BEKymer     Swapped TRUE/FALSE on AmpControl comment
      2.60        11-24-97    LAM         deleted unused currentsetup elements
      2.61        01-19-98    BJB         Replaced MaxTimeoutFlag with Spare6.
      2.62        02.19.98    JBerman     Moved Features from Setup to Preset
       2.62        03.10.98    JBerman     Added StrokeLen into CONFIGSETUP
       2.63        04.03.98    JBerman     Due to duplication in profile.h
                                          I'm modifying PROFILE to PROF                
       2.65        04.23.98    LAM         made  StrokeLen UINT32          
       2.66        05.06.98    LAM         added Springratetable to currentsetup,
                                          temporarily added SumOfForce and PartContactForce          
       2.67        05.13.98    LAM         deleted calibration vars from currentsetup
                                          will use NVR structure
      2.68        05-18-98    PaulG       Added Variables for Abs Distance Graph.
      2.69        05-22-98    BJB         Terminated comments to satisfy compiler.
      2.70        06-02-98    BJB         Added comment on range of DigPot
      2.71        06-05-98    BEKymer     Corrected logic comment for FreqControl
      2.72        06-25-98    BJB         Got rid of CurrentSetup.User, don't need it.
      2.73        07-16-98    BEKymer     Add AlarmSuppressFlag as argument to
                                          ReadPreset to prevent alarm W8 when
                                          clearing a preset.
      2.74        03-12-99    BEKymer     Added ramp stuff to preset, created a
                                          SETUPS_Ver600 so in the future presets
                                          can be saved in software upgrade.

      2.75        04-20-99    OFI         Changed for DIAB
      2.76        05-06-99    JZ          Added SetPressure, WeldFR, StepFR, HoldFR to SETUPS
      2.77        05-10-99    LAM         added packed for DIAB
      2.78        05-12-99    JZ          Added RTRamp, ReturnRamp, SetRTComp to SETUPS
      2.79        05-18-99    LAM         Fixed structure to be same size as Microtec
      2.79.1.1    06-28-99    JZ          changed VelocityTable to SINT32 type, 
      2.79.1.2    07-29-99    LAM         renamed unused loadcelloffset to calsyspressure 
      2.81        08-11-99    JZ          added StartRamp
      2.82        08-23-99    JZ          added VelocityPC, ForcePC, MinTrigForce, GainFactor
                                          moved FORCE_MIN
      2.83        09-03-99    JZ          added MinTrigForce
      2.84        09-08-99    LAM         removed calibrated sys pressure and stroke length
                                          from the preset                                    
      2.85        10-26-99    JZ          added IdleSpeed
      2.86        11-05-99    JZ          removed RTInitVel
      2.87        12-16-99    LAM         removed unused references to profiling
      2.87.6.1    02-07-00    JZ          remoced DVS and DualPress
      2.88        04-07-00    JZ          merged Lang to trunk
      2.89        04-18-00    JLH         Added HornWeightOffset to CONFIGSETUP/CurrentSetup.
      2.90        05-26-00    JLH         Printer name changes - deleted LaserJet and InkJet, and added OKI520 
                                           and HPPCL. 
      2.91        06-09-00    JLH         Replaced an unused location with the flag SendWeldData.
      2.92        06-20-00    BEK         Created new definitions for preset and setup, while retaining
                                          the older ones for the conversion process.
                                          Add prototypes for RecallCompressedPreset() and
                                          SaveCompressedPreset()
      2.93        07-13-00    BEK         Added SETPRESSUREFLAG define
      2.94        07-14-00    BEKymer     Added SHIFT2_SEEKFUNFLAG define
                                          Added SHIFT2_POWERGRAPHSFLAG define
                                          Remove Amp2Flag & Force2Flag from bit save
                                          Added TimingOnTrg                          
                                          Added SuspectLimits, RejectLimits to comp. 
      2.96        08-22-00    JLH         Added Verified to SETUPS_Ver800 structure (for Ver9).
      2.97        10-18-00    BEKymer     Added 2nd arg to SaveCompressedPreset prototype
                                           to fix issue # 3387
      2.98        04-06-01    DJL         Added UINT16 ExtPreset and UINT16 Handheld;                                           
      2.99        05-24-01    BEKymer     Moved ExtPreset and Handheld to end of structure
                                           (see note where moved to)
      2.100       08-03-01    BEKymer     Change names of members of CurrentSetup for use with
                                           special 8.2S (ASCII output)                                           
      2.101       09-11-01    BEKymer     Add 2 write-in fields to preset for 8.3S
      2.102       10-11-01    LAM         Removed conversion preset structures
      2.103       04-30-03    BEKymer     Add Velocityreporting to end of BUCMENU_800
      2.103.1.0   09-01-03    JOY         Added Weld Param: options in CONFIGSETUP struct.
      2.103.1.1   10-14-03    JOY         Added flag 'QVGAImgSaved' in CONFIGSETUP struct.
      2.104       09-09-03    BEKymer     Added EnergyBraking and ExtTrgDelay to preset structure
      2.105       12-08-03    BEKymer     Merged 2.103.1.1 & 2.104 to create 2.105
                                           for Ver9.00b build
      2.106       12-17-03    BEKymer     Allow compiler to check size of PRESET_COMPRESSED
      2.107       01-19-04    VSharma     Added 'SwDip','SeekTime','WeldRampTime'&'HwCnfg' to 
                                          PRESET_COMPRESSED struct and 'HwCnfg' added in SETUPS_Ver800.
      2.109       01-20-04    BEKymer     Added note 'APPEARS NOT TO BE USED
                                           ANYMORE BEK 01-20-04' for MinTrigForce
                                           in preset anbd compress preset    
      2.110       01-30-04    JOY         Added DUPS_WorkingPreset to the CONFIGSETUP struct.
      2.111       02-18-04    VSharma     Added 'UserIn5', 'UserIn6' & 'UserOut3' to the 
                                          CONFIGSETUP struct.
                                          Changed ExtSwLogicCustom to ExtTriggerLogic.
      2.112       03-05-04    VSharma     Changed naming convention for 'UserInX' & 'UserOutX'.
      2.113       03-12-04    VSharma     Added J3_32Ptr,J3_33Ptr,J3_19Ptr,J3_17Ptr,J3_31Ptr &
                                           J3_2Ptr in CONFIGSETUP struct.
      2.115       04-06-04    VSharma     Added define TOTAL_PRESETS.
      2.116       05-03-04    VSharma     Changed J3_2In to J3_1In and J3_2Ptr to J3_1Ptr.
      2.117       05-11-04    VSharma     Changed define TOTAL_PRESETS.
      2.118       06-02-04    VSharma     Added Sample and Alarm flag for external preset selection
                                          in  CONFIGSETUP struct. 
      2.117.1.0   06-18-04    BEKymer     Added WelderAddrFlag & WelderAddrValue
                                           to system configuration
      2.119       06-23-04    JOY         Removed 'ExtPresetWeldCount' from CONFIGSETUP struct,
                                          the 4 byte space left as it is to avoid pointer conflict.
      2.120       06-25-04    BEKymer     Merged 2.117.1.0 & 2.119 to create
                                           2.120 for Ver9.00l build
      2.121       06-25-04    BEKymer     Add prototypes for default functions                                     
      2.122       07-13-04    LAM         Add Sclk7890Act and ClockPhase to CONFIGSETUP                                       
      2.123       07-14-04    BEKymer     Added SystemControllerFlag to CONFIGSETUP
      2.124       08-18-04    JOY         Added SVDelay to CONFIGSETUP.
      2.125       08-27-04    BEKymer     Added Energy Brake time to preset
      2.126       07-25-05    Bwadia      Auto Refresh added to current setup 
      2.127       08-23-05    Aare        Added pretrigger delay flags and values.        
      2.128       08-25-05    Aare        Added metric 3 flag.
      2.129       08-26-05    Aare        Added encoder reset ULS/SS flag.
      2.131       10-11-05    Bwadia      USB related parameters added in Current setup
      2.132       10-24-05    BWadia      PMC related parameters added to PRESET_COMPRESSED
                                          and SETUPS_Ver800 structures
      2.133       10-26-05    Bwadia      Sequencing related parameters added to CONFIGSETUP 
      2.134       11-22-05    Bwadia      SBL +/- frequency flags added and stored in UINT16
                                          variable
      2.135       12-07-05    Bwadia      PMCDATAPOINTS made 402 bytes as max power value
                                          for power graph also needs to be stored. Modified
                                          for tracker issue 4028
      2.136       12-20-05    Bwadia      Sequence printing related items added to CONFIGSETUP,
                                          PRESET_COMPRESSED and SETUPS_Ver800 structures
                                          Modified for Tracker issue 3976  
      2.137       01-06-06    LAM         Merged BBRaun Special 
      2.138       01-09-06    LAM         Added Encoder type flag to system configuration                                   
      2.139       02-07-06    Bwadia      Added enable/disable flag for OFF button on PMC
                                          limits. Modified for tracker issue 4065
      2.140       02-08-06    Bwadia      Added USB global On/Off flag
      2.141       01-31-07    NHAhmed     Changes related to Changed Structure variables of 
                                          CHOICE and TOGGLE.
      2.142       03-12-07    NHAhmed     Added new variable AmpScrubTime.
      2.143       03-27-07    NHAhmed     Added VQS related variables in PRESET_COMPRESSED and 
                                          SETUPS_Ver800 structures.
      2.144       05-23-07    NHAhmed     Added new variable (NoOfCycles) in Current Setup 
      2.144.2.0   12-03-07    BEKymer     Add RecalCode300 to BBR structure
      2.144.2.1   10-02-09    BEKymer     Add MicroHomeForce to BBR structure
      2.114.2.1   06-26-13    HasanchezZ  add Preset_running to the vector enum{}	
 

 --------------------------- INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "menu.h"


/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/                                                              


#define PRESETLEN           12
#define MAX_CAL_PTS         10+1
#define SPRING_RATE_TABLE   64
#define FORCE_MIN           100      /*    100 =    10.0 lb */
#define NMBRPOINTS          20       /* Maximum number points in profile      */
#define WRITEINLEN          12       /* (10 characters, 1 term, 1 to keep word aligned) */

#define CURRENT_SETUP       0

#define PageS11             1  
#define PageS14             2
#define PageSA4             4

#define MAX_PRESETS         16     /* For Version 8.00, the limit is 16 */
#define PASS_SIZE           7      /* Size of password including null */
#define TOTAL_PRESETS       MAX_PRESETS+1  /* For the size of PresetEnableFlag. */
#define PMCDATAPOINTS       402
#define MAX_SEQUENCE_NOS    30 
#define ALL_PRESETS 36

typedef enum {
    PRESET_0  = 0u,
    PRESET_1,
    PRESET_2,
    PRESET_3,
    PRESET_4,
    PRESET_5,
    PRESET_6,
    PRESET_7,
    PRESET_8,
    PRESET_9,
    PRESET_10,
    PRESET_11,
    PRESET_12,
    PRESET_13,
    PRESET_14,
    PRESET_15,
    PRESET_16,
    PRESET_17,
    PRESET_18,
    PRESET_19,
    PRESET_20,
    PRESET_21,
    PRESET_22,
    PRESET_23,
    PRESET_24,
    PRESET_25,
    PRESET_26,
    PRESET_27,
    PRESET_28,
    PRESET_29,
    PRESET_30,
    PRESET_31,
    PRESET_32,
    PRESET_MIN,
    PRESET_MAX,
    PRESET_COLDSTART, 
    PRESET_RUNNING} PRESET_NUMBER_TYPE;

/*----------------------------------------------------------------------------------------------*/
/*  This typedef defines the structure used to hold the running preset and the current preset.  */
/*  Whenever a change is made to this structure, a corresponding change needs to be made to the */
/*  CompressedSetups structure and to the code in functions Convert600to800() and Convert702to  */
/*  800().  The functions CompressPreset() and UncompressPreset() need to be updated as well.   */
/*----------------------------------------------------------------------------------------------*/
typedef __packed__(2,1) struct  Ver800Setups {   /***  THIS COPY IS TO RETAIN THE DEFINITION FOR VER 8.00    ***/
   SINT32  AbAmp;
   SINT32  AbDelay;
   UINT16  AbFlag;
   SINT32  AbTime;
   SINT32  ABSCutoffDist;
   UINT16  ABSCutoffFlag;
   SINT32  AbsDist;
   BOOLEAN AbsDistanceGraphAFlag;
   UINT16  AbsDistanceGraphSFlag;
   SINT32  AbsDistanceGraphValue;
   SINT32  AbsMLR; 
   SINT32  AbsMLS;    
   SINT32  AbsPLR;
   SINT32  AbsPLS;
   SINT32  ActClrDistance;
   UINT16  ActClrFlag;
   BOOLEAN  AmplitudeGraphAFlag;
   UINT16  AmplitudeGraphSFlag;
   SINT32  AmplitudeGraphValue;
   SINT32  Amp1; 
   SINT32  AmpTrigAbsValue;
   SINT32  AmpTrigColValue;
   UINT16  AmpTrigExtFlag;
   SINT32  AmpTrigTimeValue;
   SINT32  AmpTrigEnerValue;
   SINT32  AmpTrigPowerValue;
   SINT32  AmpTrigForceValue;
   UINT16  Amp2Flag;
   SINT32  Amp2;
   SINT32  AmpScrubTime;
   UINT16  AutoScaleFlag;        
   UINT16  AutoTrigFlag;
   UINT16  ColCutoffFlag;
   SINT32  ColCutoffDist;
   SINT32  ColDist;
   BOOLEAN  ColDistanceGraphAFlag;        
   UINT16  ColDistanceGraphSFlag;               
   SINT32  ColDistanceGraphValue;
   SINT32  ColMLR;
   SINT32  ColMLS;
   SINT32  ColPLR;
   SINT32  ColPLS;
   UINT16  ControlLimitsFlag;
   UINT16  CycleAbortFlag;
   SINT32  Day;
   UINT16  DigitalFilterFlag;       /* Global name change */
   SINT32  DownSpdStart;
   UINT16  DUPSPreset;
   SINT32  EBTime;                  /* V9 new variable - VARIABLE */
   UINT16  EnergyBraking;           /* V9 new variable - CHOICE */
   UINT16  EnergyCompFlag;
   SINT32  EnergyMaxVQS;
   SINT32  EnergyMinVQS;
   SINT32  EnergyML;
   SINT32  EnergyMLR;
   SINT32  EnergyMLS;
   SINT32  EnergyPL; 
   SINT32  EnergyPLR;
   SINT32  EnergyPLS;
   UINT16  ExtTrgDelay;             /* External trigger delay - added in V9  CHOICE */
   SINT32  FreqMLR;
   SINT32  FreqMLS;
   SINT32  FreqPLR;
   SINT32  FreqPLS;
   SINT32  FreqOffset;
   UINT16  FreqOffsetFlag;
   BOOLEAN  FrequencyGraphAFlag;
   UINT16  FrequencyGraphSFlag;
   SINT32  FrequencyGraphValue;
   SINT32  Force2;
   UINT16  Force2Flag;
   BOOLEAN  ForceGraphAFlag;                     
   UINT16  ForceGraphSFlag;
   SINT32  ForceGraphValue;
   SINT32  ForceTrigAbsValue;
   SINT32  ForceTrigAmpValue;
   SINT32  ForceTrigColValue;
   UINT16  ForceTrigExtFlag;
   SINT32  ForceTrigEnerValue;
   SINT32  ForceTrigPowerValue;
   SINT32  ForceTrigTimeValue;
   SINT16  GaugePressure;
   UINT16  GeneralAlarmLFlag;       /* Global Name Change */        
   UINT16  GlobalPrintingFlag;      /* Global Name Change */
   UINT16  GndDetectFlag;
   SINT32  HoldForce;
   UINT16  HoldFR;
   SINT32  HoldTime;
   UINT16  HoldTimeFlag;
   SINT32  Hour;
   SINT32  MaxTimeout;
   SINT32  MinTrigForce;            /* APPEARS NOT TO BE USED ANYMORE BEK 01-20-04 */
   SINT32  Minute;
   UINT16  MissingPartFlag;
   UINT16  MissingMinFlag;
   UINT16  MissingMaxFlag; 
   SINT32  MissingPartMin;
   SINT32  MissingPartMax;
   SINT32  Month;
   SINT32  PeakPwr;
   SINT32  PeakPwrCutoff;
   UINT16  PeakPwrCutoffFlag;
   SINT32  PeakPowerMaxVQS;
   SINT32  PeakPowerMinVQS;
   SINT8   PresetID[PRESETLEN];
   BOOLEAN PowerGraphAFlag;                    
   UINT16  PowerGraphSFlag;                     
   SINT32  PowerGraphValue;  
   SINT32  PowerMLR;
   SINT32  PowerMLS;
   SINT32  PowerPLR;  
   SINT32  PowerPLS;
   UINT16  PreSeek;
   UINT16  PresetUpdateComplete;
   SINT32  PreTrigAmp;
   SINT32  PreTrigDelay;
   UINT16  PreTrigDelayFlag;
   SINT32  PreTrigDist;
   UINT16  PreTrigDistFlag;
   UINT16  PreTrigFlag;
   UINT16  PreTrigSwitch;
   UINT16  RejectLimits; 
   UINT16  RejectLimitsFlag;
   UINT16  RejResetRequiredFlag;        /* Global Name Change */
   UINT16  ReturnRamp;
   SINT32  RTDist;
   UINT16  RTFlag; 
   UINT16  RTPosSW;
   UINT16  RTRamp;
   SINT32  ScrubTime;
   UINT16  ScrubTimeFlag;
   UINT16  SeekFunFlag;         /* Global Name Change */
   UINT16  SetPressure;
   SINT32  SetRTComp;
   BOOLEAN  SetupPresetAFlag;
   UINT16  SetupPresetSFlag;
   SINT32  SetupPresetValue;
   UINT16  StartRamp;
   UINT16  StepFR;
   UINT16  SuspectLimits;
   UINT16  SuspectLimitsFlag;
   UINT16  SusResetRequired;
   SINT32  TestAmp;
   SINT32  TimeMLR;
   SINT32  TimeMLS;
   SINT32  TimePLR;
   SINT32  TimePLS;
   UINT16  TimingOnTrgFlag;     /* TRUE: Trig   FALSE:Pretrigger */
   SINT32  TotalAbsMaxVQS;
   SINT32  TotalAbsMinVQS;
   SINT32  TotalColMaxVQS;
   SINT32  TotalColMinVQS;
   SINT32  TotalCycleTimeMaxVQS;
   SINT32  TotalCycleTimeMinVQS;
   SINT32  TriggerForce;
   SINT32  TriggerDelay;        /* used for timed trigger delay - not implemented as yet */
   UINT16  TriggerDelayFlag;
   SINT32  TrsDistMLR;
   SINT32  TrsDistMLS;
   SINT32  TrsDistPLR;  
   SINT32  TrsDistPLS;
   BOOLEAN VelocityGraphAFlag;
   UINT16  VelocityGraphSFlag; 
   SINT32  VelocityGraphValue;
   UINT16  Verified;
   SINT32  WeldColMaxVQS;
   SINT32  WeldColMinVQS;
   SINT32  WeldCount;
   SINT32  WeldEnergy;
   SINT32  WeldForce;
   SINT32  WeldForceMaxVQS;
   SINT32  WeldForceMinVQS;
   SINT32  WeldForceMLR;        /* Global Name Change Max->Weld */
   SINT32  WeldForceMLS;        /* Global Name Change Max->Weld */
   SINT32  WeldForcePLR;        /* Global Name Change Max->Weld */  
   SINT32  WeldForcePLS;        /* Global Name Change Max->Weld */ 
   UINT16  WeldFR;
   BOOLEAN WeldHistoryAFlag;
   UINT16  WeldHistorySFlag;
   SINT32  WeldHistoryValue;
   UINT16  WeldMode;
   BOOLEAN WeldStatusFlag;
   BOOLEAN WeldSummaryAFlag;
   UINT16  WeldSummarySFlag;
   SINT32  WeldSummaryValue;
   SINT32  WeldTime;
   SINT32  WeldTimeMaxVQS;
   SINT32  WeldTimeMinVQS;   
   SINT8   WriteIn1[WRITEINLEN];
   SINT8   WriteIn2[WRITEINLEN];
   SINT32  XScaleTime;
   SINT32  Year;
   UINT32  HwCnfg;
   SINT32  SBLMinFreqLim;          /* Minimum frequency limit. Value is calculated every time when SBL is enabled or horn scan is run. */
   SINT32  SBLMaxFreqLim;          /* Maximum frequency limit, same as above applies. */
   SINT32  SBLMinFreq;             /* Initially copied from SBLMinFreqLim. Operator can change within limits. */
   SINT32  SBLMaxFreq;             /* Same as SBLMinFreq */
   UINT16  SBLFreqFlags;           /* SBL + and - enable flags. */
   UINT16  SBLEnableMin;           /* SBL enable/disable flag per preset, min freq. */
   UINT16  SBLEnableMax;           /* SBL enable/disable flag per preset, max freq. */
   SINT32  PMCHighLimit;
   SINT32  PMCLowLimit;
   SINT32  PMCTimeout;
   UINT8   PMCData[PMCDATAPOINTS];
   UINT16  PMCCycleCount;
   UINT16  PMCEnabled; 
   BOOLEAN  SeqPresetAFlag;
   UINT16  SeqPresetSFlag;
   SINT32  SeqPresetValue;
   UINT16  PMCPlusBandFlag;
   UINT16  PMCMinusBandFlag;
   UINT16  VQSLimit;
   SINT32  AmpAMicron;
   SINT32  AmpBMicron;
 } SETUPS_Ver800;

/*----------------------------------------------------------------------------------------------*/
/*  This typedef defines the structure used to hold the compressed form of the preset.  This is */
/*  structure used to save a preset.  Its size must never change.  If it does then the proper   */
/*  conversion functions must be written (see Convert600to800, etc).                            */
/*  Whenever a change is made to this structure, a corresponding change needs to be made to the */
/*  CompressedSetups structure and to the code in functions Convert600to800() and Convert702to  */
/*  800().  The functions CompressPreset() and UncompressPreset() need to be updated as well.   */
/*----------------------------------------------------------------------------------------------*/

#define SIZE_OF_COMPRESSED_PRESET  454

typedef __packed__(2,1) struct  CompressedSetups {

   UINT16  AbAmp;                      /* Was SINT32 */
   UINT16  AbDelay;                    /* Was SINT32 */
   SINT32  ABSCutoffDist;
   SINT32  AbsDist;
   SINT32  AbsDistanceGraphValue; 
   SINT32  AbsMLR;
   SINT32  AbsMLS;
   SINT32  AbsPLR;
   SINT32  AbsPLS;
   UINT16  AbTime;                     /* Was SINT32 */
   SINT32  ActClrDistance;
   UINT16  Amp1;                       /* Was SINT32 */
   UINT16  Amp2;                       /* Was SINT32 */
   UINT16  AmpScrubTime;               /* Was SINT32 ....Amplitude for Ground Detect Mode*/ 
   UINT16  Amp2Flag;                   /* Multiple bits used here, dont compress */
   SINT32  AmpTrigAbsValue;
   SINT16  AmpTrigColValue;            /* Collapse can be 16 bits, was SINT32 */
   SINT32  AmpTrigEnerValue;
   UINT16  AmpTrigForceValue;          /* Was SINT32 */
   UINT16  AmpTrigPowerValue;          /* Was SINT32 */
   UINT16  AmpTrigTimeValue;           /* Was SINT32 */    
   SINT32  AmplitudeGraphValue;
   SINT16  ColCutoffDist;              /* Collapse can be 16 bits, was SINT32 */
   SINT16  ColDist;                    /* Collapse can be 16 bits, was SINT32 */
   SINT32  ColDistanceGraphValue;   
   SINT16  ColMLR;                     /* Collapse can be 16 bits, was SINT32 */
   SINT16  ColMLS;                     /* Collapse can be 16 bits, was SINT32 */
   SINT16  ColPLR;                     /* Collapse can be 16 bits, was SINT32 */
   SINT16  ColPLS;                     /* Collapse can be 16 bits, was SINT32 */
   UINT16  Day;                        /* Was SINT32 */
   UINT16  DownSpdStart;               /* Was SINT32 */
   UINT16  DUPSPreset;
   SINT32  EnergyML;
   SINT32  EnergyPL;
   SINT32  EnergyMLR;
   SINT32  EnergyMLS;
   SINT32  EnergyPLR;
   SINT32  EnergyPLS;
   SINT32  EnergyMaxVQS;
   SINT32  EnergyMinVQS;
   UINT16  Force2;                     /* Was SINT32 */
   UINT16  Force2Flag;                 /* Multiple bits used here, dont compress */ 
   SINT32  ForceGraphValue; 
   SINT32  ForceTrigAbsValue;
   UINT16  ForceTrigAmpValue;          /* Was SINT32 */
   SINT16  ForceTrigColValue;          /* Collapse can be 16 bits, was SINT32 */
   SINT32  ForceTrigEnerValue;
   UINT16  ForceTrigPowerValue;        /* Was SINT32 */
   UINT16  ForceTrigTimeValue;         /* Was SINT32 */
   SINT16  FreqOffset;                 /* Was SINT32 */
   UINT16  FreqMLR;                    /* Was SINT32 */
   UINT16  FreqMLS;                    /* Was SINT32 */
   UINT16  FreqPLR;                    /* Was SINT32 */  
   UINT16  FreqPLS;                    /* Was SINT32 */                   
   SINT32  FrequencyGraphValue;
   UINT16  GaugePressure;
   UINT16  HoldTime;                   /* Was SINT32 */
   UINT16  HoldForce;                  /* Was SINT32 */
   UINT16  HoldFR;
   UINT16  Hour;                       /* Was SINT32 */ 
   UINT16  MaxTimeout;                 /* Was SINT32 */
   UINT16  MinTrigForce;               /* Was SINT32 APPEARS NOT TO BE USED ANYMORE BEK 01-20-04 */
   UINT16  Minute;                     /* Was SINT32 */
   SINT32  MissingPartMin;
   SINT32  MissingPartMax;
   UINT16  Month;                      /* Was SINT32 */
   UINT16  PeakPwr;                    /* Was SINT32 */
   UINT16  PeakPwrCutoff;              /* Was SINT32 */
   SINT32  PowerGraphValue;     
   UINT16  PowerMLR;                   /* Was SINT32 */
   UINT16  PowerMLS;                   /* Was SINT32 */
   UINT16  PowerPLR;                   /* Was SINT32 */ 
   UINT16  PowerPLS;                   /* Was SINT32 */
   SINT8   PresetID[PRESETLEN];
   UINT16  PresetUpdateComplete;
   UINT16  PreTrigAmp;                 /* Was SINT32 */                       
   UINT32  PreTrigDelay;
   SINT32  PreTrigDist;
   UINT16  PeakPowerMaxVQS;
   UINT16  PeakPowerMinVQS;
   UINT16  RejectLimits;               /* Multiple bits used, dont compress */
   UINT16  ReturnRamp;  
   SINT32  RTDist;
   UINT16  RTRamp;  
   UINT16  ScrubTime;                  /* Was SINT32 */
   UINT16  SetRTComp;                  /* Was SINT32 */
   SINT32  SetupPresetValue; 
   UINT16  StartRamp;
   UINT16  StepFR;
   UINT16  SBLMinFreqLim;          /* Minimum frequency limit. Value is calculated every time when SBL is enabled or horn scan is run. */
   UINT16  SBLMaxFreqLim;          /* Maximum frequency limit, same as above applies. */
   UINT16  SBLMinFreq;             /* Initially copied from SBLMinFreqLim. Operator can change within limits. */
   UINT16  SBLMaxFreq;             /* Same as SBLMinFreq */
   UINT16  SBLFreqFlags;           /* Parallel resonance frequency. Value is set when horn scan is complete. */
   SINT32  Spare32_2;
   SINT32  Spare32_1;
   UINT16  SuspectLimits;              /* Multiple bits used, dont compress */
   UINT16  TestAmp;                    /* Was SINT32 */
   UINT16  TimeMLR;                    /* Was SINT32 */
   UINT16  TimeMLS;                    /* Was SINT32 */
   UINT16  TimePLR;                    /* Was SINT32 */ 
   UINT16  TimePLS;                    /* Was SINT32 */
   UINT16  TriggerDelay;               /* Was SINT32 */
   UINT16  TriggerForce;               /* Was SINT32 */
   SINT32  TrsDistMLR;
   SINT32  TrsDistMLS;
   SINT32  TrsDistPLR; 
   SINT32  TrsDistPLS;
   SINT32  VelocityGraphValue; 
   UINT16  Verified;                   /* 0 = not verified, Low byte = control level, Hi byte = actuator */
   UINT16  Version;
   SINT32  WeldCount;
   SINT32  WeldEnergy;
   UINT16  WeldForce;                  /* Was SINT32 */
   UINT16  WeldForceMLR;               /* Was SINT32 */ 
   UINT16  WeldForceMLS;               /* Was SINT32 */
   UINT16  WeldForcePLR;               /* Was SINT32 */ 
   UINT16  WeldForcePLS;               /* Was SINT32 */ 
   UINT16  WeldFR;
   SINT32  WeldHistoryValue;
   UINT16  WeldMode;
   BOOLEAN WeldStatusFlag;
   SINT32  WeldSummaryValue;
   UINT16  WeldTime;                   /* Was SINT32 */   
   UINT32  Word1;                      /* Flags - Group 1 */
   UINT32  Word2;                      /* Flags - Group 2 */
   UINT32  Word3;                      /* Flags - Group 3 */
   UINT32  Word4;                      /* Flags - Group 4 */
   UINT16  XScaleTime;                 /* Was SINT32 */
   UINT16  Year;                       /* Was SINT32 */
   SINT8   ZWriteIn1[WRITEINLEN];      /* Write in field 1 for 8.3S */
   SINT8   ZWriteIn2[WRITEINLEN];      /* Write in field 2 for 8.3S */
   UINT32  SwDip;                      /* DUPS Param Added in Ver 9.0 */
   UINT32  SeekTime;                   /* DUPS Param Added in Ver 9.0 */
   UINT16  TotalCycleTimeMaxVQS;
   UINT16  TotalCycleTimeMinVQS;
   SINT32  TotalAbsMaxVQS;
   SINT32  TotalAbsMinVQS;
   UINT16  TotalColMaxVQS;
   UINT16  TotalColMinVQS;
   UINT16  VQSLimit;
   UINT32  WeldRampTime;               /* DUPS Param Added in Ver 9.0 */
   UINT16  WeldColMaxVQS;
   UINT16  WeldColMinVQS;
   UINT16  WeldForceMaxVQS;
   UINT16  WeldForceMinVQS;
   UINT16  WeldTimeMaxVQS;
   UINT16  WeldTimeMinVQS;
   UINT32  HwCnfg;                     /* H/W config Added in Ver 9.0 */
   UINT16  EBTime;                     /* Energy Brake time added in Ver 9.0 */
   UINT16  PMCCycleCount;
   UINT16  PMCHighLimit;
   UINT16  PMCLowLimit;
   UINT16  PMCTimeout;
   SINT32  SeqPresetValue;
   //UINT8   ZZSpare[6];			  /* Fill entire allocated space, entire structure must remain at 454 bytes */
   /****ADDED AMP MICRONS*****/
   //UINT16  AmpAjustmentMicron;		/* Amplitude adjustment microns for the levels of percentage */
   UINT16  AmpAMicron;
   UINT16  AmpBMicron;
   UINT16  AmpMicronEnabledFlag;
 } PRESET_COMPRESSED;

/*****************************************************************************/
/*                                                                           */
/*  The following chunk of stuff allows the compiler to check the size of    */
/*  the compressed preset to ensure it remains at 454 bytes.  Don't ask me   */
/*  how it works.  I stole it from the Diab compiler manual and modified it  */
/*  until it worked.  It's static so it's not multiply defined.  I know it   */
/*  will be created once for every 'C' file, but according to the manual it  */
/*  won't generate any code if all is okay.                                  */
/*                                                                           */
/*  The argument for the __ERROR__ call (2) is supposed to create an error   */
/*  and stop the compile.  It doesn't and I don't know why.  It will only    */
/*  create a warning, so pay attention.                                      */
/*                                                                           */
/*****************************************************************************/

extern void __ERROR__(char *, ...);

#define CHECK_PRESET(test) if (!(test)) __ERROR__("COMPRESSED PRESET NOT 454 BYTES..", 2)

static void CheckPresetSize(void)
{
   CHECK_PRESET(sizeof(PRESET_COMPRESSED) == SIZE_OF_COMPRESSED_PRESET);
}

/************************  End of chunk of stuff  ****************************/

typedef __packed__(2,1) struct {
   UINT16  ActivePreset;           /*                                             */
   SINT32  ActLifetime;            /*                                             */
   SINT8   ActSerialNumber[13];
   UINT16  Actuator;               /*                                             */
   UINT16  AdjustWhileRun;         /* TRUE:allow adjusting while welding          */  
   UINT16  AdvanceCounters;        /* TRUE:all cycles   FALSE:good cycles only    */
   BOOLEAN  AmpControl;             /* TRUE:internal control FALSE:external control*/
   UINT16  BeeperAlarm;            /* TRUE:beep on any process alarms             */
   UINT16  BeeperError;            /* TRUE:beep on data entry errors              */
   UINT16  BeeperRelease;          /* TRUE:beep ok to release start, H/H only     */
   UINT16  BeeperTrigger;          /* TRUE:beep when trigger occurs               */
   UINT16  BaudRate;               /* this is active baudrate                     */
   UINT16  BBRInitialized;         /* When BBR is initialized: set to 0x5555      */
   UINT16  CustomAct;              /* TRUE:custom is turned on                    */
   UINT16  ControlLevel;           /* LEVEL_t, LEVEL_e, LEVEL_a, LEVEL_ea, LEVEL_d, LEVEL_f & LEVEL_TEST    */
   UINT16  CycleStart;             /* BIT1:2Start  BIT2:1Start  BIT3:TrgSw  BIT4:ExtSig */ 
   UINT16  CylinDiameter;
   SINT32  DigPot;                 /* Dig Pot position * 20, -999 to 1000         */
   UINT16  DigPotFlag;             /*                                             */
   BOOLEAN  ExtraCooling;           /* TRUE:Extra cooling on                       */
// UINT16  ExtPresets;             /* TRUE:External Presets is On                 */
   UINT16  ExtTriggerLogic;        /* TRUE:ExternalTrigger is active high         */
   BOOLEAN  FreqControl;            /* TRUE:internal control FALSE:external control*/
   SINT32  GenAlarmCount;          /*                                             */
   SINT32  GainFactor;
   BOOLEAN  GndDetLogicCustom;      /* TRUE:High 24V   FALSE:Low 0V                */
// UINT16  HandHeld;               /* TRUE: Handheld is On                        */
   UINT16  HmenuIndex;             /* Current selection on current HSUBMENU       */
   SINT32  HornDownSpd;            /*    */
   SINT32  HornDownForce;          /*    */
   SINT16  HornWeightOffset;
   BOOLEAN  USEncoder;              /* TRUE = US, FALSE = METRIC                   */
   SINT32  IdleSpeed;  
   UINT16  Language;               /*                                             */
   UINT32  LoadCellAtHome;
   SINT32  MinTrigForce;
   SINT32  Overload;               /*                                             */
   UINT16  PageSize;               /* Size of page being used                     */
   SINT32  PartContactForce;  
   UINT16  PartContactFlag;

   /* Next 2 variables (PasswordFlag 7 PasswordID) must stay in sequential order (because of sysmangr)*/
   UINT16  PassWordFlag;           /* TRUE:passwords are required                 */
   SINT8   PassWordID[PASS_SIZE];  /* Alpha/Numeric string of approved password   */

   /* Next 4 variables (Printer...) must stay in sequential order (because of sysmangr) */
   UINT16  PrinterEpson;           /* TRUE if Epson compatible printer selected   */
   UINT16  PrinterOKI520;          /* TRUE if OKIDATA 520 printer selected        */
   UINT16  PrinterHPPCL;           /* TRUE if HP PCL printer has been selected    */
   UINT16  PrinterUnused;          /* reserved for another printer type           */

      /* Next 2 variables (PSFreq & PSWatt)  must stay in sequential order (because of sysmangr) */
   UINT16  PSFreq;
   SINT32  PSWatt;

   SINT32  PSLifetime;             /*                                             */
   SINT8   PSSerialNumber[13];
   BOOLEAN PSType;                 /* TRUE: DUPS, FALSE: Analog                   */ 
   SINT16  PwrOutTable[MAX_CAL_PTS];
   UINT16  Spare2;                 /*                                             */
   UINT16  RemoteData;             /* TRUE:Remote terminal data mode is enabled   */
   UINT16  ScrollDisplay;          /* TRUE:scroll by one  FALSE:scroll by three   */
   UINT16  SecurityLevel;          /* OPERATOR, SETUP, MAINTAINENCE, BRANSON      */
   UINT16  Spare3;        
   UINT16  SequenceFlag;           /*                                             */
   UINT16  Sequence1Flag;          /*                                             */
   UINT16  Sequence2Flag;          /*                                             */
   UINT16  Sequence3Flag;          /*                                             */
   UINT16  SerialPort;             /* TRUE:serial port on and setup               */
   UINT16  SpringRateTable[SPRING_RATE_TABLE];
   BOOLEAN  StartScreen;
   UINT16  StrokeLen;              /*                                             */
   UINT16  SystemEquipment;        /* TRUE: turn on system equipment              */ 
   UINT16  TestMultiplier;         /* TRUE:indicates power bargraph max = 100%    */
   UINT16  TimeMultiplier;         /* TRUE:indicates power bargraph max = 100%    */
   UINT16  TriggerSwLogic;         /* TRUE:High 24V   FALSE:Low 0V                */
   BOOLEAN  Units;                  /* Currently selected units SI:TRUE USCS:FALSE */
   BOOLEAN  ULSLogicCustom;         /* TRUE:High 24V   FALSE:Low 0V                */
   UINT16  J3_32In;                /* Input J3_32                                 */
   UINT16  J3_33In;                /* Input J3_33                                 */
   UINT16  J3_19In;                /* Input J3_19                                 */
   UINT16  J3_17In;                /* Input J3_17                                 */
   UINT16  UserInLogic;            /* TRUE:High 24V   FALSE:Low 0V                */
   UINT16  J3_36Out;               /* Output J3_36                                */
   UINT16  J3_8Out;                /* Output J3_8                                 */
   SINT32  VelocityTable[2];       /*                                             */
   SINT32  WeldHistoryPtr;         /* Last Battram Pointer Address                */
   SINT32  WeldsPerPage;           /* Lines printed before form feed              */
/**********************************************************************************/
/* The following entries are added at the end to ensure that all other variables  */
/* remain in the same place in BBR.  This prevents the need for a reconfiguration */
/* when upgrading from ver 8.xx, 8.xS.  This is still carried over for ver 9.0    */
/**********************************************************************************/
   BOOLEAN  ExtPresets;             /* TRUE:External Presets is On                 */
   BOOLEAN  HandHeld;               /* TRUE: Handheld is On                        */
/**********************************************************************************/
   UINT16  WeldParamOption[5];     /* Weld Result Parameter options */
   UINT16  QVGAImgSaved;           /* Flag indicate QVGA backgnd image is stored  */
   UINT16  DUPS_WorkingPreset;     /* DUPS Working Preset Number */
   UINT16  J3_31In;                /* Input J3_31                                 */
   UINT16  J3_1In;                 /* Input J3_01                                 */
   UINT16  J3_22Out;               /* Output J3_22                                */
   BOOLEAN *J3_32Ptr;              /* Pointer to selected item on J3_32           */
   BOOLEAN *J3_33Ptr;              /* Pointer to selected item on J3_33           */
   BOOLEAN *J3_19Ptr;              /* Pointer to selected item on J3_19           */
   BOOLEAN *J3_17Ptr;              /* Pointer to selected item on J3_17           */
   BOOLEAN *J3_31Ptr;              /* Pointer to selected item on J3_31           */
   BOOLEAN *J3_1Ptr;               /* Pointer to selected item on J3_2            */
   UINT32  Dummy1;                 /* Just a place holder can be used in future   */
   UINT16  ExtGlobalPrintFlag;     /* Global Print when ExtPresets enabled.       */
   UINT16  SPExtSampleFlag;        /* Setup Preset PrintOnSample Flag.            */
   UINT16  WHExtSampleFlag;        /* WeldHistory PrintOnSample Flag.             */
   UINT16  WSExtSampleFlag;        /* Weld Summary PrintOnSample Flag.            */
   UINT16  PGExtSampleFlag;        /* Power Graph PrintOnSample Flag.             */
   UINT16  AGExtSampleFlag;        /* Amplitude Graph PrintOnSample Flag.         */
   UINT16  FreqGExtSampleFlag;     /* Frequency Graph PrintOnSample Flag.         */
   UINT16  CDGExtSampleFlag;       /* CollapseDistance Graph PrintOnSample Flag.  */
   UINT16  VGExtSampleFlag;        /* Velocity Graph PrintOnSample Flag.          */
   UINT16  FGExtSampleFlag;        /* Force Graph PrintOnSample Flag.             */
   UINT16  SeqExtSampleFlag;       /* Sequencing PrintOnSample Flag.              */
   BOOLEAN  SPExtAlarmFlag;         /* Setup Preset PrintOnAlarm flag.             */
   BOOLEAN  WHExtAlarmFlag;         /* WeldHistory PrintOnAlarm flag.              */
   BOOLEAN  WSExtAlarmFlag;         /* Weld Summary PrintOnAlarm flag.             */
   BOOLEAN  PGExtAlarmFlag;         /* Power Graph PrintOnAlarm flag.              */
   BOOLEAN  AGExtAlarmFlag;         /* Amplitude Graph PrintOnAlarm flag.          */
   BOOLEAN  FreqGExtAlarmFlag;      /* Frequency Graph PrintOnAlarm flag.          */
   BOOLEAN  CDGExtAlarmFlag;        /* Collapse Distance Graph PrintOnAlarm flag.  */
   BOOLEAN  VGExtAlarmFlag;         /* Velocity Graph PrintOnAlarm flag.           */
   BOOLEAN  FGExtAlarmFlag;         /* Force Graph PrintOnAlarm flag.              */
   BOOLEAN  SeqExtAlarmFlag;        /* Sequencing PrintOnAlarm flag.               */
   SINT32  SPExtSampleValue;       /* Setup Preset PrintOnSample value.           */
   SINT32  WHExtSampleValue;       /* WeldHistory PrintOnSample value.            */
   SINT32  WSExtSampleValue;       /* Weld Summary PrintOnSample value.           */
   SINT32  PGExtSampleValue;       /* Power Graph PrintOnSample value.            */
   SINT32  AGExtSampleValue;       /* Amplitude Graph PrintOnSample value.        */
   SINT32  FreqGExtSampleValue;    /* Frequency Graph PrintOnSample value.        */
   SINT32  CDGExtSampleValue;      /* Collapse Distance Graph PrintOnSample value.*/
   SINT32  VGExtSampleValue;       /* Velocity Graph PrintOnSample value.         */
   SINT32  FGExtSampleValue;       /* Force Graph PrintOnSample value.            */
   SINT32  SeqExtSampleValue;      /* Sequencing PrintOnSample value.             */
   UINT16  WelderAddrFlag;         /* Welder ID On/Off                            */
   SINT32  WelderAddrValue;        /* Welder ID value                             */
   UINT8   Sclk7890Act;            /* Clock speed for actuator a/d                */
   UINT8   ClockPhase;             /* Phase needs to be inverter at high speed    */
   UINT8   SystemControllerFlag;   /* FALSE:old 101-242-379  TRUE:new 101-242594  */
   SINT32  SVDelay;                /* Sv interlock Delay                          */
   BOOLEAN  AutoRefresh;            /* Auto Refresh of graph on VGA*/
   BOOLEAN  Metric3Flag;            /* TRUE if metric distance must have 3 decimals*/
   UINT16  DistanceULS;            /* True to reset encoder on ULS, false on start switches */
   UINT16  SBLEnable;              /* Global SBL enable/disable flag.            */
   BOOLEAN  USBGlobalFlag;          /* Global USB On/Off flag                     */
   UINT16  USBWDSampleFlag;        /* Weld Summary SendOnSample Flag.            */
   UINT16  USBPGSampleFlag;        /* Power Graph SendOnSample Flag.             */
   UINT16  USBAGSampleFlag;        /* Amplitude Graph SendOnSample Flag.         */
   UINT16  USBFreqGSampleFlag;     /* Frequency Graph SendOnSample Flag.         */
   UINT16  USBCDGSampleFlag;       /* CollapseDistance Graph SendOnSample Flag.  */
   UINT16  USBVGSampleFlag;        /* Velocity Graph SendOnSample Flag.          */
   UINT16  USBFGSampleFlag;        /* Force Graph SendOnSample Flag.             */
   BOOLEAN  USBWDAlarmFlag;         /* Weld Summary SendOnAlarm flag.             */
   BOOLEAN  USBPGAlarmFlag;         /* Power Graph SendOnAlarm flag.              */
   BOOLEAN  USBAGAlarmFlag;         /* Amplitude Graph SendOnAlarm flag.          */
   BOOLEAN  USBFreqGAlarmFlag;      /* Frequency Graph SendOnAlarm flag.          */
   BOOLEAN  USBCDGAlarmFlag;        /* Collapse Distance Graph SendOnAlarm flag.  */
   BOOLEAN  USBVGAlarmFlag;         /* Velocity Graph SendOnAlarm flag.           */
   BOOLEAN  USBFGAlarmFlag;         /* Force Graph SendOnAlarm flag.              */
   SINT32  USBWDSampleValue;       /* Weld Summary SendOnSample value.           */
   SINT32  USBPGSampleValue;       /* Power Graph SendOnSample value.            */
   SINT32  USBAGSampleValue;       /* Amplitude Graph SendOnSample value.        */
   SINT32  USBFreqGSampleValue;    /* Frequency Graph SendOnSample value.        */
   SINT32  USBCDGSampleValue;      /* Collapse Distance Graph SendOnSample value.*/
   SINT32  USBVGSampleValue;       /* Velocity Graph SendOnSample value.         */
   SINT32  USBFGSampleValue;       /* Force Graph SendOnSample value.            */
   BOOLEAN SequenceEnable;         /* Sequencing preset enable/disable           */
   UINT8   SequenceCount;          /* Total sequencing items                     */
   UINT8   SequenceList[MAX_SEQUENCE_NOS]; /* Sequence List                      */
   UINT16  SequenceNos;            /* Current Sequence number                    */ 
   UINT16  VGAHWPresent;           /* True if VGA hardware detected once         */
   BOOLEAN PLCControlFlag;         /* TRUE:PLC Control feature is on             */
   BOOLEAN PLCControlMenuFlag;     /* TRUE:PLC Control menu option is displayed  */
   SINT32  NoOfCycles;
   UINT16  AmpMicronsFlag;         /* AmpMicrons ID On/Off                            */
   SINT32  AmpMicronsValue;        /* AmpMicrons ID value                             */
   UINT16  PeakPowerWattsFlag;         /* AmpMicrons ID On/Off                            */
} CONFIGSETUP;
                


typedef __packed__(2,1) struct {
   SINT32  EnergyBrakingAmp;
   SINT32  EnergyBrakingTime;
   UINT16  ExtSwLogicBUC;
   SINT32  ForcePC;
   UINT16  GndDetLogicBUC;
   UINT16  ULSLogicBUC;
   SINT32  VelocityPC;
   UINT16  VelocityReporting;  /* Toggle via main menu secret codes */
   SINT32  AmpDecayPercent; 
   UINT16  RecalCode300;       /* Enable/disable recal error code 300 */
   UINT16  MicroHomeForce;     /* FALSE = 3  TRUE = 4   Leaving home force */
} BUCMENU_800;


/* These defines are used for preset compression.  */

#define SHIFT1_ABFLAG                    0
#define SHIFT1_ABSCUTOFFFLAG             1
#define SHIFT1_ABSDISTANCEGRAPHAFLAG     2
#define SHIFT1_ABSDISTANCEGRAPHSFLAG     3
#define SHIFT1_ACTCLRFLAG                4
#define SHIFT1_AMPLITUDEGRAPHAFLAG       5
#define SHIFT1_AMPLITUDEGRAPHSFLAG       6
#define SHIFT1_AMPTRIGEXTFLAG            7
#define SHIFT1_AUTOSCALEFLAG             8
#define SHIFT1_AUTOTRIGFLAG              9
#define SHIFT1_COLCUTOFFFLAG             10
#define SHIFT1_COLDISTANCEGRAPHAFLAG     11
#define SHIFT1_COLDISTANCEGRAPHSFLAG     12
#define SHIFT1_CONTROLLIMITSFLAG         13
#define SHIFT1_CYCLEABORTFLAG            14
#define SHIFT1_DIGITALFILTERFLAG         15
#define SHIFT1_ENERGYCOMPFLAG            16
#define SHIFT1_FREQOFFSETFLAG            17
#define SHIFT1_FREQUENCYGRAPHAFLAG       18
#define SHIFT1_FREQUENCYGRAPHSFLAG       19
#define SHIFT1_FORCEGRAPHAFLAG           20
#define SHIFT1_FORCEGRAPHSFLAG           21
#define SHIFT1_FORCETRIGEXTFLAG          22
#define SHIFT1_GENERALALARMLFLAG         23
#define SHIFT1_GLOBALPRINTINGFLAG        24
#define SHIFT1_GNDDETECTFLAG             25
#define SHIFT1_HOLDTIMEFLAG              26
#define SHIFT1_MISSINGPARTFLAG           27
#define SHIFT1_MISSINGMINFLAG            28
#define SHIFT1_MISSINGMAXFLAG            29
#define SHIFT1_PMCENABLED                30  

                                         
#define SHIFT2_PEAKPWRCUTOFFFLAG         0
#define SHIFT2_POWERGRAPHAFLAG           1
#define SHIFT2_POWERGRAPHSFLAG           2
#define SHIFT2_PRETRIGDISTFLAG           3
#define SHIFT2_PRETRIGFLAG               4
#define SHIFT2_REJECTLIMITSFLAG          5
#define SHIFT2_REJRESETREQUIREDFLAG      6
#define SHIFT2_RTFLAG                    7
#define SHIFT2_SCRUBTIMEFLAG             8
#define SHIFT2_SEEKFUNFLAG               9
#define SHIFT2_SETPRESSUREFLAG           10
#define SHIFT2_SETUPPRESETAFLAG          11
#define SHIFT2_SETUPPRESETSFLAG          12
#define SHIFT2_SUSPECTLIMITSFLAG         13
#define SHIFT2_SUSRESETREQUIREDFLAG      14
#define SHIFT2_TIMINGONTRGFLAG           15
#define SHIFT2_TRIGGERDELAYFLAG          16
#define SHIFT2_VELOCITYGRAPHAFLAG        17
#define SHIFT2_VELOCITYGRAPHSFLAG        18
#define SHIFT2_WELDHISTORYAFLAG          19
#define SHIFT2_WELDHISTORYSFLAG          20
#define SHIFT2_WELDSTATUSFLAG            21
#define SHIFT2_WELDSUMMARYAFLAG          22
#define SHIFT2_WELDSUMMARYSFLAG          23
#define SHIFT2_ENERGYBRAKINGFLAG         24
#define SHIFT2_EXTTRGDELAYFLAG           25
#define SHIFT2_PRETRIGDELAYFLAG          26
#define SHIFT2_SEQUENCINGAFLAG           27
#define SHIFT2_SEQUENCINGSFLAG           28
#define SHIFT2_PMCPLUSBANDFLAG           29
#define SHIFT2_PMCMINUSBANDFLAG          30


#define FREQ15_OFF     300      /* 15 khz offset (80% of max swing) */
#define FREQ20_OFF     400      /* 20 khz offset (80% of max swing) */
#define FREQ30_OFF     600      /* 30 khz offset (80% of max swing) */
#define FREQ40_OFF     800      /* 40 khz offset (80% of max swing) */
#define FREQ60_OFF    1200      /* 60 khz offset (80% of max swing) */

/*-------------------------- FUNCTION PROTOTYPES ---------------------------*/
/*                                                                          */
/*  These prototypes must be after SETUPS so UpdatePreset will complile.    */
/*                                                             BEK 07-10-97 */
/*                                                                          */


void WritePreset(UINT16 PresetNumber);
void ReadPreset(UINT16 PresetNumber, UINT16 AlarmSuppressFlag);
void SetMaxMinValues(void);
void DoColdStart(void);
void SetDefaultValues(void);
void SaveCompressedPreset(PRESET_COMPRESSED* CompressPreset, SETUPS_Ver800 *SourcePtr);
void RecallCompressedPreset(PRESET_COMPRESSED* CompressPreset);
void SetUserIOToFactoryDefault(void);
void SetActuatorSwitchesToFactoryDefault(void);
void SetPrintingToFactoryDefault(void);
void SetUSBToFactoryDefault(void);


#endif



