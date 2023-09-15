/* $Header:   D:/databases/VMdb/2000Series/App/SPIDD.C_V   2.232   13 Sep 2012 09:27:48   gbutron  $ */
/****************************************************************************/ 
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96,97, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*************************                         **************************/
/*
 ------------------------- MODULE DESCRIPTION -------------------------------

 Name: spidd.c

     Functions:                                                                                                                              
       1. InitPSNovram
       2. InitPVP                                                         
       3. InitBarGraph                                                    
       4. InitACTNovram                                                   
     
  The Digital Pot will be on Channel 12. The bit stream is 8 bits.      
 It will set the center freq.

 ---------------------------- REVISIONS ------------------------------------

 Rev#      Date       Author   Description
 =====     ========   =======  =============================================
 0         12/4/95      LAM      Initial
 1         4/18/96      LAM      Added Table lookup
 2         5/02/96      LAM      Moved LEd table
 3         05-03-96     WFT      Played with UpdateCalibratedTable
 4         05-12-96     LAM      Clean UP
 5         05-14-96     LAM      fixed digpot
 6         06-10-96     BEKymer  Create temp array to see PVP values sent out
 7         06-14-96     BEKymer  Put back short LoadCellTable
 8         06-15-96     BEKymer  Fix calculation in UpdateCalibratedTable
 9         06-16-96     LAM      removed limit checking on digpot        
 10        06-24-96     BEKymer  Add define to select Interpolate for Force
 11        06-28-96     LAM      chged resolution on power to .1% fixed
                                 freqoffset
 12        06/30/96     LAM      Added spring rate Table lookup
 13        07/08/96     LAM      Added springrateTable and forcetbl to preset
 14        07/10/96     LAM      will not trigger in first 0.25 in            
 15        07-18-96     BEkymer  Switch to Force control when 10lbs is reached
 16        07-22-96     LAM      added frequency bar graph,added loadcell offset                    
 17        07-29-96     BEKymer  Add rounding to UpdateCalibratedTable
                                 Create CalibrateTableLock variable to prevent
                                 ReadACTADC from running while table is updated
 18        08-29-96     BEKymer  fixed power table                    
 19        10-01-96     LAM      fixed frequency bar graph
 20        10-08-96     LAM      added test for door open                 21    10-10-96 LAM      added pressure sensor test
 22        10-14-96     LAM      added check not to exceed maxMA to PVP
 23        10-16-96     LAM      fixed force table,added recal act.
 24        11-10-96     LAM      check for divide by zero          
 25        11-21-96     LAM      fixed part contact                
 26        11-25-96     LAM      fixed updating ep tables          
 27        12-17-96     PhilJ    Deleted variable CurrentLine. Hardcoded
                                 UpdateLine to line 3.  Deleted functions
                                 InitPSNovram and InitActNovram.
 27.10     12-17-96     LAM      check for negative amplitue
 28.00     12-23-96     LAM      use springrate not table,fixed ext amp & freq   
 29.00     01-11-97     LAM      deleted getcurrentactuator,fixed false triggering              
 30.00     01-21-97     LAM      deleted unused code                                            
 31.00     02-14-97     LAM      deleted updatefreqgraph                         
 32.00     02-27-97     LAM      fixed external freq & amp                       
 32.01     02-28-97     LAM      fixed digpot                                    
 33.00     03-12-97     LAM      fixed frequency & memory                        
 34.00     04-01-97     LAM      fixed center frequency  bargraph
 35.00     04-04-97     LAM      fixed center frequency  bargraph
 35.01     04-08-97     LAM      must psreset before center frequency  bargraph
 36.00     04-08-97     LAM      fixed 100 steps                               
 37.00     04-14-97     LAM      fixed bargraph ends                           
 37.01     04-16-97     LAM      redid fbargraph scaling                        
 38.00     04-17-97     LAM      deleted filtering on frequency
 39.00     04-28-97     LAM      process psadc every ms         
 39.10     04-28-97     PhilJ    Chngd AmpControlInternal & FreqControlInternal
                                 from UINT8 to UINT16.
 40.00     05-08-97     LAM      added flag not to update display when center freq
 41.00     05-09-97     LAM      chged bargraph size to 50hz                       
 42.00     05-23-97     LAM      added switch for 20khz to 40khz                   
 2.99      06-23-97     LAM      added check for no encoder               
 2.100     06-27-97     PhilJ    Disabled check for no encoder               
 2.101     06-30-97     PhilJ    Enabled check for no encoder
 2.102     07-07-97     LAM      read 10vref at powerup      
 2.103     07-23-97     LAM      replaced move.w with ori.w  
 2.104     07-28-97     LAM      added power table to currentsetup
 2.105     08-01-97     LAM      added test for 20 or 40 khz
 2.106     08-08-97     LAM      modified readpsad           
 2.107     08-14-97     LAM      added enabledigpot          
 2.108     08-19-97     LAM      fixed extfreq               
 2.109     08.19.97     JBerman  Added DigFilter for: Amp, Frqq, & Power
 2.110     08.26.97     LAM      only update bargraph when sonics on    
                                 added set digpot at power up
 2.111     08.29.97     LAM      chged DigFilter to running preset       
 2.112     09.05.97     LAM      fixed ampouttable                       
 2.114     09.11.97     JBerman  Changed #define MAX_TABLE_PTS 11 instead 10+1
 2.115     09.11.97     LAM      sped up centering frequency and startup freq
 2.116     10.02.97     LAM      only update freq bargraphs when sonics on      
 2.117     10.06.97     LAM      fixed digpot range from -50 to +50
 2.118     10.20.97     LAM      added dooropen check when ULS active
 2.119     10.22.97     LAM      needed to reset inp.trigger
 2.120     10.28.97     LAM      chged update diagscreen      
 2.121     10.28.97     JBerman  Improved digital filters
 2.122     10.28.97     JBerman  Improved Amp graph
 2.123     10.28.97     JBerman  Improved Freq Graph FrqSum to UINT32
 2.124     10.31.97     LAM      fixed store after postweldseek
 2.125     11.11.97     JBerman  Digital Filter improvements 
 2.126     11.19.97     JBerman  AmpOutTable redefin.
 2.127     11.19.97     JBerman  Multiply all original numbers in the 
                                 AmpOutTable by 8. Devide CurrrentAmpIn
                                 by 8 using bit shift X >> 3. 
 2.128     12.05.97     LAM      fixed freq bargraph scales     
 2.129     12.10.97     LAM      fixed digpot, fixed to no encoder(ver 4.29)
                                 eleminated frequency check in initbargraph
 2.130     12.12.97     LAM      chged setdigpot to go to the closer end of the range
 2.132     12.13.97     LAM      made amplitude to .1%                                
 2.133     01-22-98     BJB      Changed block chr 0xbe to '|' so block appears
                                 right on screen and terminal.
 2.134     01-27-98     BJB      Modified UpdateDiagScreen() to use Latch variables.
                                 Changed special chr 0x7e to 0x7F
 2.135     02.24.98     LAM      deleted commented out code                           
 2.136     03.20.98     LAM      chged ampcontrol, added RELEASE2 define                                     
 2.137     04.23.98     LAM      removed RELEASE2 define, started on trigger routine
                                 deleted unused checkforencoder
 2.138     04.27.98     LAM      deleted inp.trigger = false in readactadc            
 2.139     05.01.98     LAM      modified trigger algorithm reduced no movement to       
                                 less then 0.0010
 2.140     05.08.98     LAM      added using spring rate table                           
 2.141     05.14.98     LAM      chged pressure table to NVR structure
 2.142     05.14.98     LAM      added partcontact variables            
 2.143     05.18.98     LAM      rescaled spring rate table to 0.1024 in increment
 2.144     05.19.98     BJB      Changed constants compared to CurrentForce in
                                 ReadACTADC() to use tenths of pounds.
                                 Added Offset parameter to UpdateCalibratedTable()
                                 so pressure & force can use different offsets.
 2.145     06.01.98     LAM      rescaled spring rate table to 0.2024 in increment
 2.146     06.01.98     LAM      fixed digpot to 100
 2.147     06.04.98     BJB      Added CurrentDigPotPosition variable to keep track
                                 of dig pot position for debugging.
                                 Changed order of operations in WritePVP() to more
                                 accurately position digital pot.
                                 Does NOT clear CurrentSetup.DigPot when pot is
                                 centered, this was not necessary, caused data loss.
                                 Modified expressions involving CurrentSetup.DigPot
                                 for new format of this variable.
                                 Deleted unused functions DecPot(), UpPot().
 2.148     06-06-98     BEKymer  Change AmpControlFlags to PowerSupplyControlFlags
 2.149     06.12.98     LAM      moved loadcell offset back here to keep table linear
                                 check for negative pressure numbers, changed part contact
                                 no movement
 2.150     06.19.98     LAM      removed springrate offset test in part contact,
                                 do not let force display as negative
 2.151     06.25.98     LAM      check for values over 10volts on reference      
 2.152     07.01.98     LAM      added zeroing out home values of loadcell       
 2.153     06.30.98     BJB      Sets Inp.DoorOpen on AE if at uls & Inp.Trigger.
                                 (imported, with mods, from v2.137).
                                 Fixed nested comments to satisfy compiler.
 2.154     07.01.98     LAM      chged processing of homereading                 
 2.155     07.02.98     LAM      reset currentforce to zero at ULS               
 2.156     07.06.98     JBerman  Modified CurrentSetup.Actuator w. Encoder
 2.157     07.07.98     LAM      removed homereadings of loadcell, chged actuator
                                 test in readactadc
 2.158     07.15.98     LAM      fixed spi setup for PVP signal                    
 2.159     07.16.98     LAM      use minlimit.trigger instead of partcontact min   
 2.160     07.21.98     LAM      made sure distance1 was set when partcontact is off   
 2.161     07.24.98     LAM      added checknomovement routine                                                                                                                                                                      
 2.162     07.30.98     LAM      cleanup checknomovement routine,added horn weight
                                 change
 2.163     07.30.98     BJB      Deleted act_nvr definition, uses actnvram.h
                                 InitBarGraph() modified so it only changes config,
                                 doesn't write TxdData[] or start transfer.  Need
                                 to do this on power-up only, now done in root().
 2.164     07.31.98     LAM      average horn weight change over time
 2.165     07.31.98     BJB      Includes kpresmsg.h, getmsg.h instead of selctkey.h
 2.166     08.03.98     LAM      increase no movement to 0.75 inverted clock to actuator
                                 A/D.
 2.167     08.03.98     LAM      increase no movement to 0.875
 2.168     08.05.98     LAM      deleted partcontact summing will use no movement
                                 must see a horn weight change for 400ms before alarming
 2.169     08.24.98     LAM      added homepressure, read current pressure every 4ms
 2.170     08.27.98     BJB      Added test for horn down sequence in trigger code
 2.171     08.27.98     LAM      added test if pressure signal is negative          
 2.172     09-22-98     BEKymer  Put original rel 2.0 code back in for DoorOpen
 2.173     10.02.98     LAM      horn weight change must be preset for 5 secs, and
                                 DoorOpenDelay to 2 seconds
 2.174     11.04.98     LAM      update home pressure every 4 seconds               
 2.175     11.06.98     LAM      chged no movement check to over 2 points instead of 5
 2.176     12.07.98     BJB      Modified range of CurrentSetup.DigPot for 15/30KHz
                                 support
 2.177     03/15/99     LAM      added when an aef switch to weld force when part
                                 partcontact is made
 2.179     05/04/99     LAM      moved globals to fix for DIAB
 2.180     05-14-99     JZ       changed PowerSupplyControlFlags to PSActControlFlags
 2.181     05-26-99     LAM      changed SCLK for PSADC to SPBR=3(4.08Mhz) when we are
                                 a system clock of 25Mhz.
 2.182     06-04-99     JHenry   Added WorkingForceSet variable for menuhorn.c 
 2.183     06-10-99     JHenry   Deleted WorkingForceSet as required by Horndown code review.
                                 (WorkingForceSet was moved to menuhorn.c.)
 2.183.2.4 07-16-99     JLH      Updates during calibration debugging.
 2.183.2.5 07-22-99     LAM      Replaced CurrentSetup.LoadCellAtHome with CurrentSetup.SpringRateTable[0]
 2.183.2.6 07-29-99     LAM      Fixed timing on the 7890's, temporarily set part contact force to 20lbs
 2.183.2.7 07-29-99     LAM      Added compiler define to select between median filter and 4 point filter,
                                 set part contact velocity to 0.1 inch per sec. 
 2.183.2.8 07-30-99              temporarily set part contact force to 15lbs
 2.186     08-03-99     JZ       added ERRORCODE for EQ20 alarm
 2.187     08-05-99     LAM      fixed PSDAC queue to read all channels, do not generate recal
                                 alarms unless we are in the weld sequence
 2.188     08-06-99     JZ       added RecordErrorCode   
 2.189     08-11-99     LAM      put psadc queue back to 8  
 2.190     08-11-99     LAM      updated Distance1 to be set at partcontact not trigger 
 2.191     08-13-99     LAM      fixed QSPI timing for 24.462 Mhz clock 
 2.192     08-23-99     LAM      read all queues in readpsadc and readactadc first and start queue before 
                                 processing data.  
 2.193     08-23-99     LAM      use BUC menu partcontact variables
 2.194     08-24-99     LAM      fix partcontactmade function only called after 0.125 after ULS
 2.195     08-26-99     LAM      update ADForce all the time  
 2.196     09-03-99     LAM      use index of 1 minimum for spring rate offset
 2.197     09-07-99     OFI      Add test for EncoderPos is less than 60000
 2.198     09-14-99     LAM      once part contact is made do not reset
 2.199     09-20-99     LAM      filter to raw force ad counts
 2.200     10-11-99     LAM      filter more before part contact, replaced averagepressure with home
                                 pressure
 2.201     11-04-99     LAM      removed all TABS
 2.202     12-20-99     JZ       made backward compability with AED
 2.203     05-15-00     JLH      Fixed CheckEPSignals function to bypass actuator checking if Wrong Actuator
                                 error is active.
 2.204     05-26-00     SCM      Checked in for testing by Laura, John.   
 2.205     06-21-00     DJL      Made a few global changes from DigitalFilter to DigitalFilterFlag.      
                                 ******commented out lines   1425 - 1432 don't forget to reactivate**********
 2.206     07-13-00     BEK      Fixed commented out lines in PartContactMade()
 2.207     08-14-00     LAM      removed 2.203 change, fixed in ready.c instead
 2.208     08-15-00     AT       removed extern TestBuffer1[]
 2.209     10-31-00     BEK      Initialize HomePressure so very 1st reading can start at current
                                 value instead of 0, because starting at 0 takes way too long
                                 to reach 60 or 80 psi with the filter.  This is for issue #3633.
 2.210     10-31-00     BEK      Fix compiler error
 2.211     11-02-00     LAM      Do not generate a recal alarm unless the control level is a d or
                                 above (Issues 3658 & 3662).
 2.212     11-07-00     LAM      fixed actual frequency readings (Issue 3593)                        
 2.213     12-13-00     LAM      modified timing based on 24_117Mhz.                       
 2.213.5.0 04-02-02     LAM      subtract off 1000 count offset from loadcell table                       
 2.213.5.1 04-10-02     LAM      replaced 1000 vs. LC_OFFSET
 2.213.5.2 05-17-02     LAM      replaced LC_OFFSET with global LoadCellOffset
 2.215     12-19-03     BEK      Moved 2.213.5.2 to tip as 2.215 for Ver9.00c build
 2.216     04-06-04     VSharma  Enable AmpDecay output if amplitude falls 
                                 below the defined value in BUCMenu.
 2.217     05-11-04     VSharma  Moved AmpDecay output code to "mansensr.c".
 2.218     05-18-04     LAM      Created CheckforHornChange, this is called at power up and after an EStop
 2.219     05-20-04     LAM      Created AlarmHornWeight variable for Debug 
 2.220     07-12-04     LAM      Changed actuator ad clk to a variable  
 2.221     07-27-04     JOY      Updated ReadPSADC() for FREQ60KHZ.
 2.222     08-27-04     LAM      Changed actuator da clk to a use same variable as ad clk
 2.223     12-30-04     LAM      temporarily disabled DOOROPEN(SBEAM build)
 2.224     04-11-05     LAM      Added SBeam / Loadcell defines
 2.225     04-15-05     LAM      Do not read negative force at home yet
 2.226     04-27-05     LAM      deleted unused slopeint
 2.227     08-25-06     LAM      deleted unused smoothing algorithm, added offset for sbeam
 2.228     08-30-06     LAM      added code back to check if negative loadcellindex set to 0
 2.229     01-31-07     NHAhmed  Changes related to Changed Structure variables of CHOICE and TOGGLE.
 2.230     11-19-07     LAM      Merged 9.07 changes
 2.231     09-10-09     BEkymer  Add new define MICRO where needed
 2.232     09-13-12     GButron  Make the software works with 16/8bits PSNovram. 
                                 #define WELD_FILTER changed from 1 to 3 for doing the filtering 
                                 on force and fixing the Actuator's oscillation readings.
     
/*---------------------------- INCLUDE FILES -------------------------------*/
       
#include "mansensr.h"
#include "332.h"
#include "led.h"
#include "digout.h"
#include "preset.h"
#include "qsm.h"
#include "fmtstrs.h"
#include "spidd.h"
#include "alarms.h"
#include "sc.h"
#include "ready.h"
#include "state.h"
#include "statedrv.h"
#include "snsrcalb.h"
#include "ticks.h"
#include "weld.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "interpol.h"
#include "weld_obj.h"
#include "actnvram.h"
#include "battram.h"
#include <m68332.h>


/*---------------------------- LOCAL_EQUATES -------------------------------*/


//#define INCLUDE_UNIT_TEST
#define NOISEREADING 0xff

#define MAX_TABLE_PTS 11
/* frequency bar graph defines */
#define DIGPOTCOUNT 100
#define DIGPOTDELAY 4                                                      /* 20ms delay */
#define CENTERBAR 6
#define LESSTHENBAR 0
#define GREATERTHENBAR 12
#define RIGHTBRACKETBAR 11
#define LEFTBRACKETBAR 1
#define FREQDIVBY  2                                                       /* 20kHZ Power Supply */
#define FilterIndex8 8
#define DOOROPENDELAY 500                                                  /* 2 second delay */
#define LOADCELLDELAY 63
#define REFOKAY 1000
#define PART_CONTACT_FILTER 2
#define WELD_FILTER 3                                                      /* Changed from 1 to 3 for doing the filtering on force and fixing the Actuator's oscillation readings */

#define ONESECOND 4
#define FIVE_LB 15
#define HORN_CHANGED 20                                                    /* 5 sec */
#if SYSTEM_CLOCK ==_21MHZ                                                  /* 1ms Tick */
   #define SCLK_7890PS  2                                                  /* system clock/3 * SPBR = 4.08 for 24.642Mhz and 5.425 for 20.9Mhz*/
   #define DELAY_AFTER_TRANSFER  7                                         /* 32*DTL/system clock = 11.50us */
#elif SYSTEM_CLOCK ==_24_642MHZ
   #define DELAY_AFTER_TRANSFER  16                                        /* 32*DTL/system clock =  20.7us*/
   #define SCLK_7890PS  3                                                  /* system clock/3 * SPBR = 4.08 for 24.642Mhz and 5.425 for 20.9Mhz*/
   #define SCLK_DA_ACT   5                                                 /* SCK = 2.46 Mhz at 24.6Mhz clock */
   #define SCLK_DIGPOT   84                                                /* SCK = 145khz */
   #define SCLK_BARG     8                                                 /* SCK =  1.5Mhz */
   #define SCLK_AD_PS    3                                                 /* SCK = 4.107Mhz at 24.462 Mhz*/
#elif SYSTEM_CLOCK ==_24_117MHZ
   #define DELAY_AFTER_TRANSFER  16                                        /* 32*DTL/system clock = 21.2us */
   #define SCLK_7890PS   3                                                 /* system clock/3 * SPBR = 4.02 for 24.117*/
   #define SCLK_DA_ACT   5                                                 /* SCK = 2.41 Mhz at 24.117Mhz clock */
   #define SCLK_DIGPOT   84                                                /* SCK = 144khz */
   #define SCLK_BARG     8                                                 /* SCK =  1.5Mhz*/
   #define SCLK_AD_PS    3                                                 /* SCK = 4.02Mhz at 24.117 Mhz*/
#endif

#define POWERUP_PRESSURE      -100                                         /* Value to determine first reading   */
#define FREQ_TABLE_PTS     9                                               /* used for the A/D frequency readings */
#define MAXVOLT 2047
#define AD_NEG_OFFSET 3796                                                 /* Needed for negative force values  */
#define AD_OFFSET 300                                                      /* Needed to compensate for negative force values  */

/*---------------------------------- GLOBAL DATA ---------------------------*/
/*                          (scope is global to ALL files)                  */

SINT16 AmpOutTable[MAX_TABLE_PTS] =
         {0,125,249,374,498,623,747,872,997,1121,1121};

                                                                           // Digital filter 3point throw away the high and low values

UINT16 NovramFlag;
UINT16 FilterAmp[3];
UINT16 FilterPower[3];
UINT16 FilterFreq[3];
UINT16 FilterMem[3];
UINT16 FilterForce[3];
UINT16 FilterPressure[3];

UINT16 FilterAmpPtr = 0;
UINT16 FilterPowerPtr = 0;
UINT16 FilterFreqPtr = 0;
UINT16 FilterMemPtr = 0;
UINT16 FilterForcePtr = 0;
UINT16 FilterPressurePtr = 0;

UINT16 IncrementPot = 0 ;
UINT16 IncrementSpe = 0;
UINT16 TenVoltRef = 0;

                                                                           /* Temporary variables for gathering data for Ralph */
UINT16 TestForceData1Ptr = 0;
UINT16 TestForceData2Ptr = 0;
UINT16 TestPressureDataPtr = 0;
UINT16 TestPowerDataPtr = 0;
UINT16 TestAmplitudeDataPtr = 0;
UINT16 TestFrequencyDataPtr = 0;

#if INCLUDE_UNIT_TEST
UINT16 TestForceData1[1024];
UINT16 TestForceData2[1024];
UINT16 TestPressureData[1024];
UINT16 TestPowerData[1024];
UINT16 TestAmplitudeData[1024];
UINT16 TestFrequencyData[1024];
#endif

UINT16 TriggerMet = FALSE;
UINT16 EnableDigPotFlag = FALSE;
UINT16 CenterPotFlag = FALSE;
SINT16 UpdateTableCountDown;

BOOLEAN DigPotFlag = FALSE;
BOOLEAN DigPotKey = FALSE;
BOOLEAN FirstTime;
SINT16 LoadCellIndex;
UINT16 ADForce;
UINT16 ADPressure;
SINT16 AlarmHornWeight = 0;                                                /* Created on an ErrorCode 300, used in the Debug menu */
UINT16 CurrentDigPotPosition = 0;                                          /* Used to keep track of DigPot */
SINT32 Distance1;                                                          /* Distance 1-3 used to determine part contact*/
UINT16 PartContactFlag;
SINT16 LoadCellCountDown = LOADCELLDELAY;

                                                                           /* Inputs to the 332  */
UINT32 CurrentPowerIn;                                                     /* Value being read by 7890   */
UINT32 CurrentAmpIn;                                                       /* Value being read by 7890   */
UINT32 CurrentMemIn;                                                       /* Value being read by 7890   */
SINT32 CurrentFreqIn;                                                      /* Value being read by 7890   */
SINT32 CurrentPressure;                                                    /* Current pressure           */
SINT32 HomePressure = POWERUP_PRESSURE;                                    /* Home pressure              */
SINT32 CurrentForce;                                                       /* Current pressure           */
SINT16 ExtFreqOffset;                                                      /* external frequency offset  */
UINT16 ExtAmp;                                                             /* external amplitude control */

/* ---------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                          (scope is global to THIS file)                  */


static BOOLEAN PowerUPBGraph;
static BOOLEAN DigPotPinHigh = FALSE;     /* position */
static UINT16 AmpSample=0;      
static UINT16 PowerSample=0;     
static UINT16 FreqSample=0;      
static UINT16 Shift_Amount = PART_CONTACT_FILTER;
static UINT16 NegFreq20kTable[FREQ_TABLE_PTS] =
         {20450, 20388, 20325, 20262, 20200, 20138, 20075, 20012, 19950};
static UINT16 NegFreq15kTable[FREQ_TABLE_PTS] =
         {15375, 15328, 15281, 15234, 15188, 15141, 15093, 15047, 15000};
static UINT16 NegFreq40kTable[FREQ_TABLE_PTS] =
         {40900, 40775, 40650, 40525, 40400, 40275, 40150, 40025, 39900};
static UINT16 NegFreq30kTable[FREQ_TABLE_PTS] =
         {30750, 30656, 30562, 30469, 30375, 30281, 30188, 30094, 30000};
static UINT16 NegFreq60kTable[FREQ_TABLE_PTS] =
         {61500, 61312, 61125, 60937, 60750, 60562, 60375, 60187, 60000};
static UINT16 PosFreq20kTable[FREQ_TABLE_PTS] =
          {19950, 19888, 19825, 19762, 19700, 19638, 19575, 19512, 19450};
static UINT16 PosFreq15kTable[FREQ_TABLE_PTS] =
          {15000, 14953, 14906, 14859, 14812, 14766, 14719, 14672, 14625};
static UINT16 PosFreq40kTable[FREQ_TABLE_PTS] =
          {39900, 39775, 39650, 39525, 39400, 39275, 39150, 39025, 38900};
static UINT16 PosFreq30kTable[FREQ_TABLE_PTS] =
          {30000, 29906, 29812, 29719, 29625, 29531, 29438, 29344, 29250};
static UINT16 PosFreq60kTable[FREQ_TABLE_PTS] =
          {60000, 59812, 59625, 59437, 59250, 59062, 58875, 58687, 58500};
 

// ------------------ Data For the Digital Filters --------------------

static UINT16 BufferAmp[FilterIndex8]=  {0};                               // Amp Buffer init. to 0.
static UINT16 BufferPower[FilterIndex8]={0};                               // Power Buffer init. to 0.
static UINT16 BufferFreq[FilterIndex8]= {0};                               // Freq Buffer init. to 0. 
static UINT16 ForceEstimateBuffer[4] = {0,0,0,0};

static UINT16 *aptr = &BufferAmp[0];
static UINT16 *pptr = &BufferPower[0];
static UINT16 *fptr = &BufferFreq[0];

static UINT32 AmpSum=0;
static UINT32 FrqSum=0;
static UINT32 PwrSum=0;

// ------------------- End of Digital Filter Data ---------------------



/*------------------------- EXTERNAL DATA ----------------------------------*/

extern CONFIGSETUP CurrentSetup;
extern BUCMENU_800 BUCMenuRAM;
extern SINT32 EncoderPos;
extern SINT32 FActualBargraph,FMemoryBargraph;
extern enum   WELD_SEQUENCE_TYPE CurrentSequence;
extern BOOLEAN LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;
extern WELD_DATA WeldingResults;


extern enum WELDSTATES WeldState;
extern INBITS Inp;
extern SETUPS_Ver800  RunningPreset;
extern UNION_BOOL_UINT16 AmpControlInternal;
extern BOOLEAN PoweredUp;
extern UINT32 CurrentVelocity;
extern UINT16 LangIndex;
extern UINT16   ResetReceivedFlag;
extern UINT16 OldNovramInstalledFlag;

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/

static void CheckEPSignals(void);
static UINT16 ForceEstimator(UINT16 NewSample);
static BOOLEAN PartContactMade(void);

static UINT16 GetFilterValue(UINT16 TableValue[]);

//---------------------------------- CODE ----------------------------------


void InitDigitalPot(void){
/****************************************************************************/ 
/*                                                                          */
/* This function configures the QSPI so that the digital pot can be updated */
/*                                                                          */
/* Inputs :  DigPotFlag                                                     */
/*                                                                          */
/* Outputs : IncrementPot                                                   */
/****************************************************************************/ 
 
   if(DigPotFlag == FALSE){
      DigPotFlag = TRUE;
      IncrementPot = 0 ;
      QsmMap->TxdData[12] = 0;
      QsmMap->ContRam[12].Cont = 0;                                        /* return chip select high after*/
                                                                           /* transfer */
      QsmMap->ContRam[12].Bitse = 0;                                       /* 8 bits per transfer */
      QsmMap->ContRam[12].Dt = 1;                                          /* Delay after transfer */
      QsmMap->ContRam[12].Dsck = 1;                                        /* SPCR1 specifies value of delay from*/
                                                                           /* PCS valid to SCK */    
      QsmMap->ContRam[12].Pcs = 6;                                         /* Peripheral Chip Select */
   }
}


void WritePVP(UINT16 PVPValue){
   if(OldNovramInstalledFlag==TRUE){                                       /* G If OLD PSNovram is installed */
                                                                           // Actuator DAC 420 PVP Control
      if(DigPotFlag == FALSE){
        QsmMap->TxdData[12] = PVPValue;
        QsmMap->Spcr0.Cpha = 1;
        QsmMap->Spcr0.Cpol = 1;                                            /* The inactive state value of SCK */
                                                                           /* is high */
        QsmMap->Spcr2.Newqp = 12;                                          /* Start of queue */
        QsmMap->Spcr2.Endqp = 12;                                          /* End of queue */
        QsmMap->Spcr0.Bits = 16;                                           /* Number of bits per transfer */
        QsmMap->Spcr1.Dtl = 1;                                             /* length of delay after transfer */
        QsmMap->Spcr0.Spbr = CurrentSetup.Sclk7890Act;  
        QsmMap->Spcr1.Spe = 1;                                             /* Enable Qspi */
	  }
      else{
         if(DigPotKey == TRUE){
           IncrementSpe++;
            if(IncrementSpe > DIGPOTDELAY){
              DigPotKey = FALSE;
              IncrementPot++;
              IncrementSpe = 0;
              QsmMap->Spcr0.Cpha = 0;                                      /* Data is captured on the leading */
                                                                           /* edge of SCK */
              QsmMap->Spcr0.Cpol = 0;                                      /* The inactive state value of SCK is */
                                                                           /* high */
              QsmMap->Spcr2.Newqp = 12;
              QsmMap->Spcr2.Endqp = 12;
              QsmMap->Spcr1.Dtl = 1;                                       /* length of delay after transfer */
              QsmMap->Spcr0.Spbr = SCLK_DIGPOT;
              QsmMap->Spcr1.Spe = 1;                                       /* Enable Qspi */
            if (DigPotPinHigh && CurrentDigPotPosition > 0)
               CurrentDigPotPosition--;
            else if (!DigPotPinHigh && CurrentDigPotPosition < 99)
               CurrentDigPotPosition++;
               if(EnableDigPotFlag == TRUE){
                 if(CenterPotFlag == TRUE)
                   CenterDigPot();
                 else
                  SetDigPot();
			   }
			}
		 }
	  }

   }
   else{                                                                   /* G If New PSNovram is installed */
     // Actuator DAC 420 PVP Control
      if(DigPotFlag == FALSE && NovramFlag == FALSE){                      /* Will write to the PVP */
        QsmMap->TxdData[12] = PVPValue;
        QsmMap->Spcr0.Cpha = 1;
        QsmMap->Spcr0.Cpol = 1;                                            /* The inactive state value of SCK */
                                                                           /* is high */
        QsmMap->Spcr2.Newqp = 12;                                          /* Start of queue */
        QsmMap->Spcr2.Endqp = 12;                                          /* End of queue */
        QsmMap->Spcr0.Bits = 16;                                           /* Number of bits per transfer */
        QsmMap->Spcr1.Dtl = 1;                                             /* length of delay after transfer */
        QsmMap->Spcr0.Spbr = CurrentSetup.Sclk7890Act;  
        QsmMap->Spcr1.Spe = 1;                                             /* Enable Qspi */
	  }
      else{
         if(DigPotKey == TRUE && NovramFlag == FALSE){ 
           IncrementSpe++;
            if(IncrementSpe > DIGPOTDELAY){
              DigPotKey = FALSE;
              IncrementPot++;
              IncrementSpe = 0;
              QsmMap->Spcr0.Cpha = 0;                                      /* Data is captured on the leading */
                                                                           /* edge of SCK */
              QsmMap->Spcr0.Cpol = 0;                                      /* The inactive state value of SCK is */
                                                                           /* high */
              QsmMap->Spcr2.Newqp = 12;
              QsmMap->Spcr2.Endqp = 12;
              QsmMap->Spcr1.Dtl = 1;                                       /* length of delay after transfer */
              QsmMap->Spcr0.Spbr = SCLK_DIGPOT;
              QsmMap->Spcr1.Spe = 1;                                       /* Enable Qspi */
              if (DigPotPinHigh && CurrentDigPotPosition > 0)
                CurrentDigPotPosition--;
              else if (!DigPotPinHigh && CurrentDigPotPosition < 99)
                CurrentDigPotPosition++;

                 if(EnableDigPotFlag == TRUE){
                   if(CenterPotFlag == TRUE)
                     CenterDigPot();
                   else
                     SetDigPot();
				 }
			}
		 }
	  }

   }  
}  


void InitPVP(void){
/* Actuator DAC 420 PVP Control */
/* need to remove some of registers once isr is running */
/* called when disabling digital pot */

   DigPotFlag = FALSE;
   QsmMap->ContRam[12].Cont = 0;                                           /* return chip select high after */
                                                                           /*   transfer */
   QsmMap->Spcr0.Bits = 16;                                                /* number of bits per transfer */
   QsmMap->ContRam[12].Bitse = 1;                                          /* number of bit set in SPCR0 reg */
   QsmMap->ContRam[12].Dt = 1;                                             /* Delay after transfer */
   QsmMap->ContRam[12].Dsck = 1;                                           /* SPCR1 specifies value of delay from*/
                                                                           /*   PCS valid to SCK */    
   QsmMap->ContRam[12].Pcs = 4;                                            /* Peripheral Chip Select */
   QsmMap->Spcr0.Cpha = 1;
   QsmMap->Spcr0.Cpol = 1;                                                 /* The inactive state value of SCK */
                                                                           /* is high */
   QsmMap->Spcr1.Dtl = 1;                                                  /* length of delay after transfer */
   QsmMap->Spcr0.Spbr = CurrentSetup.Sclk7890Act;          
}
 

void InitBarGraph(void){

   PowerUPBGraph = TRUE;
   QsmMap->ContRam[13].Cont = 1;                                           /* chip select held low */

   QsmMap->ContRam[13].Bitse = 1;                                          /* 8 bits per transfer */
   
   QsmMap->ContRam[13].Dt = 1;                                             /* Delay after transfer */
   QsmMap->ContRam[13].Dsck = 1;                                           // SPCR1 specifies value of delay from
                                                                           /* PCS valid to SCK */    
   QsmMap->ContRam[13].Pcs = 7;                                            /* Peripheral Chip Select */
   QsmMap->ContRam[14].Cont = 1;                                           /* chip select held low */
   QsmMap->ContRam[14].Bitse = 1;                                          /* 8 bits per transfer */
   QsmMap->ContRam[14].Dt = 1;                                             /* Delay after transfer */
   QsmMap->ContRam[14].Dsck = 1;                                           /* SPCR1 specifies value of delay from */
                                                                           /* PCS valid to SCK */    
   QsmMap->ContRam[14].Pcs = 7;                                            /* Peripheral Chip Select */
   QsmMap->ContRam[15].Cont = 0;                                           /* return chip select high after */
                                                                           /* transfer */
   QsmMap->ContRam[15].Bitse = 1;                                          /* 8 bits per transfer */
   QsmMap->ContRam[15].Dt = 1;                                             /* Delay after transfer */
   QsmMap->ContRam[15].Dsck = 1;                                           /* SPCR1 specifies value of delay from */
                                                                           /* PCS valid to SCK */    
   QsmMap->ContRam[15].Pcs = 7;                                            /* Peripheral Chip Select */
   QsmMap->Spcr0.Spbr = SCLK_BARG;

                                                                           // these two signals are inverted in hardware  

   QsmMap->Spcr0.Cpol = 1;
   QsmMap->Spcr0.Cpha = 0;

   QsmMap->Spcr0.Bits = 16;                                                /* Number of bits per transfer */
   QsmMap->Spcr2.Newqp = 13;
   QsmMap->Spcr2.Endqp = 14;
}

void ReadACTADC(void)
{
/* This function is dependent on which actuator is attached. When an AE   */
/* actuator is attached, the door switch is checked when at ULS. If an    */
/* AED is attached, the pressure sensor and loadcell must be read. This   */
/* function will determine when partcontact and trigger conditions are met*/
/* when an AED actuator is attached. See SRS for complete algorithm       */ 

   if ( ( (CurrentSetup.Actuator == AED) ||
          (CurrentSetup.Actuator == AEF) ||
          (CurrentSetup.Actuator == MICRO) )
      && (CurrentSetup.ControlLevel >= LEVEL_d))
   { 
      if((QsmMap->RxdData[11] & 0x800) == 0x800){                          // In case of Neg
         FilterPressure[FilterPressurePtr++] = 0;
      }
      else{
         FilterPressure[FilterPressurePtr++] = (QsmMap->RxdData[11] & 0x07ff);
      }
      if(FilterPressurePtr > 2) FilterPressurePtr = 0;

      ADPressure = GetFilterValue(FilterPressure);

                                                                           /* filter force */
      if((QsmMap->RxdData[10] & 0x800) == 0x800){                          // In case of Neg
         FilterForce[FilterForcePtr++] = (QsmMap->RxdData[10] & 0xfff) - AD_NEG_OFFSET;
      }
      else{
         FilterForce[FilterForcePtr++] = (QsmMap->RxdData[10] & 0x07ff) + AD_OFFSET;
      }
      LoadCellIndex = ADForce + ((GetFilterValue(FilterForce) - ADForce) >> Shift_Amount);
      if(FilterForcePtr > 2) FilterForcePtr = 0;
      ADForce = LoadCellIndex;

    /* Start queue as soon as we get received data */
    /* the delay between transfer are setup from the PS7890 */
    
      QsmMap->Spcr0.Spbr = CurrentSetup.Sclk7890Act;                       /* SCK  */
      QsmMap->Spcr0.Cpha = CurrentSetup.ClockPhase;                        /* need to invert signal when Sclk7890Act = 5*/
      QsmMap->Spcr2.Newqp = 9;                                             /* Start of queue */
      QsmMap->Spcr2.Endqp = 11;                                            /* End of queue */
      CurrentPressure = GetInterpolatedSINT16(NVR.Pressure,ADPressure);

      if (Inp.uls == TRUE)                                                 /* Check if at home and door closed*/
      {
                                                                           /* Gather HOME force data for Ralph */
                                                                           // if(TestForceData1Ptr < 1024)
                                                                           // TestForceData1[TestForceData1Ptr++] = (QsmMap->RxdData[10] & 0x07ff);    
                                                                           /* Gather HOME pressure data for Ralph */
                                                                           // if(TestPressureDataPtr < 1024)
                                                                           // TestPressureData[TestPressureDataPtr++] = (QsmMap->RxdData[11] & 0x07ff);    
         CurrentForce = 0;
         Shift_Amount = PART_CONTACT_FILTER;

                                                                           /* Distance1 is referenced by menuhorn.c and weldhold.c */
         Distance1 = 0;

                                                                           // Version 10 does not check for door open SBEAM Build  
         Inp.DoorOpen = FALSE;                                             /* loadcellindex at home is ~1.1 volt */

         if((CurrentSequence != WELD) ||
            (WeldState == READYSTATE && CurrentSequence == WELD))
            CheckEPSignals();                                              /* update home pressure and horn changes at ULS */
      }
      else                                                                 /* not at home, reset counters for next time*/
      {
         LoadCellCountDown = LOADCELLDELAY; 

         LoadCellIndex -= GetSpringForce();                                /* need to subtract off spring force */
  
         if(LoadCellIndex <= 0) 
         {
            LoadCellIndex = 0;                                             /* keep value positive */
            CurrentForce = 0;
         }
         else
            CurrentForce = (GetInterpolatedSINT16(NVR.LoadCell, LoadCellIndex) - LoadCellOffset); /* Upgrade offset */

         if(CurrentForce < 0)
            CurrentForce = 0;

         if(Inp.Trigger == FALSE)
         {          
            if((EncoderPos >= 1250)&&( EncoderPos < 60000))
            {
               if(PartContactFlag == FALSE) 
               {
                  PartContactFlag = PartContactMade();
               }
               if((PartContactFlag == TRUE) && (Distance1 == 0))
               {
                  Distance1 = EncoderPos;
                  Shift_Amount = WELD_FILTER;
               }
               
               if((PartContactFlag == TRUE) && (CurrentForce >= RunningPreset.TriggerForce))
               {
                  Inp.Trigger = TRUE;
               }
            }   
         }
      } 
   }

   else                                                                    /* an ae actuator    Copied from original rel 2.0 */
   {
      if (Inp.uls == TRUE && Inp.Trigger == TRUE)
      {
         UpdateTableCountDown--;
         Inp.Trigger = FALSE;
         if (UpdateTableCountDown < 0)
         {
            UpdateTableCountDown = DOOROPENDELAY;                          /* divide because only called every 4 ms */  
            Inp.DoorOpen = TRUE;
         }
         else
            Inp.DoorOpen = FALSE;
      }
      else
         Inp.DoorOpen = FALSE;

   }
}


void ReadPSADC(void)
{
                                                                           /* read all the queue recieved data then start next conversion */
   AmpSample = (QsmMap->RxdData[3] & 0xfff);
   PowerSample = (QsmMap->RxdData[4] & 0xfff);
   FilterMem[FilterMemPtr++] = (QsmMap->RxdData[5] & 0x0fff);
   if(FilterMemPtr > 2) FilterMemPtr = 0;                                  /* Freq Out of supply */
   FilterFreq[FilterFreqPtr++] = (QsmMap->RxdData[6] & 0x0fff);
   if(FilterFreqPtr > 2) FilterFreqPtr = 0;                                /* Freq Out of supply */
   ExtAmp = (QsmMap->RxdData[7] & 0xfff);
   ExtFreqOffset = (QsmMap->RxdData[8] & 0xfff);  
                                                                           /* will not check 10vref */
   QsmMap->Spcr2.Newqp = 2;                                                /* Start of queue */
   QsmMap->Spcr2.Endqp = 8;                                                /* End of queue */  // jz temp was 8
   QsmMap->Spcr0.Cpha = 0;                                                 /* Data is captured on the leading */
                                                                           /* edge of SCK */
   QsmMap->Spcr0.Cpol = 1;                                                 /* The inactive state value of SCK is */
                                                                           /* low */
   QsmMap->Spcr0.Bits = 16;                                                /* number of bits per transfer */
   QsmMap->Spcr0.Spbr = SCLK_7890PS;                                       /* SCK  */
   QsmMap->Spcr1.Dtl = DELAY_AFTER_TRANSFER;                               /* length of delay after transfer */
   QsmMap->Spcr1.Spe = 1;                                                  /* Enable Qspi */

   if((WeldingResults.PSActControlFlags & BIT0) == FALSE)                  /* external amp */
   {
/* convert to % */       
      if (ExtAmp <= 0x07ff) 
      {
         ExtAmp =  50 + ExtAmp/40;
         if(ExtAmp >= 100) ExtAmp = 100;
      }
      else if (ExtAmp >= 0x0800) 
      {
         ExtAmp =  (ExtAmp - 2048)/40;
         if(ExtAmp <= 10) ExtAmp = 10;
      }
   }
   if((WeldingResults.PSActControlFlags & BIT2) == FALSE)                  /* external amp */
   {
                                                                           /* convert to Hz extfreqoffset does not vary with 20khz or 40khz supply*/
      if (ExtFreqOffset <= 0x07ff) 
      {
         ExtFreqOffset =  0 - ExtFreqOffset;
         ExtFreqOffset =  ExtFreqOffset >> FREQDIVBY;
      }
      else if (ExtFreqOffset >= 0x0800) 
      {
         ExtFreqOffset = 4096 - ExtFreqOffset;
         ExtFreqOffset =  ExtFreqOffset >> FREQDIVBY;
         if(ExtFreqOffset >= 500) ExtFreqOffset = 500;
      }
   }
                                                                           /* check if value is positive:0 - 0x7ff = 0 - 10v = 0 - 100% for ampitude */
                                                                           /* and power  do 3 point filter */
   if(PoweredUp == FALSE)
   {
      if ((QsmMap->RxdData[8] & 0x0800) >= 0x0800)
      {
         TenVoltRef = REFOKAY;
      }
      else
      {
         TenVoltRef = GetInterpolatedSINT16(AmpOutTable,(QsmMap->RxdData[8] & 0x7ff));
      }
   }
   else
   {
      if(RunningPreset.DigitalFilterFlag == TRUE)                          // Digital Filter is ON:        
      {
                                                                           // AMP CASE -----------------------------------------

         if((AmpSample & 0x800) == 0x800)    // In case of Neg
         {
            AmpSample = 0;
         }                            
         CurrentAmpIn = GetInterpolatedSINT16(AmpOutTable,AmpSample);      // JB
         CurrentAmpIn = DigFilterAmp(CurrentAmpIn);
      
                                                                           // POWER CASE ---------------------------------------
      
         if((PowerSample & 0x800) == 0x800)                                // In case of Neg
         {
            PowerSample = 0;                     
         }     
         CurrentPowerIn = GetInterpolatedSINT16(CurrentSetup.PwrOutTable,PowerSample);
         CurrentPowerIn = DigFilterPower(CurrentPowerIn);
      }
      else                                                                 // Digital Filter is OFF:
      {
                                                                           // AMP CASE -----------------------------------------

         if((AmpSample & 0x800) == 0x800)                                  // In case of Neg
            FilterAmp[FilterAmpPtr++] = 0;
         else
            FilterAmp[FilterAmpPtr++] = AmpSample;
         if(FilterAmpPtr > 2) FilterAmpPtr = 0;
         CurrentAmpIn = GetInterpolatedSINT16(AmpOutTable,GetFilterValue(FilterAmp));


                                                                           // POWER CASE ---------------------------------------

         if((PowerSample & 0x800) == 0x800)
         {
            FilterPower[FilterPowerPtr++] = 0;
         }
         else
         {
            FilterPower[FilterPowerPtr++] = PowerSample;
         }
         if(FilterPowerPtr > 2)
            FilterPowerPtr = 0;
         CurrentPowerIn = GetInterpolatedSINT16(CurrentSetup.PwrOutTable,GetFilterValue(FilterPower));
   
      }

                                                                           /* 20khz power suppy */
                                                                           /* check if value is negative:0 - 0x7ff = 0 - 10v = 0 - -500hz for freqout */
                                                                           /* and memout or positive:0x800 - 0xfff = -10v - 0 = 500hz - 0 */
                                                                           /* 40khz power suppy */
                                                                           /* check if value is negative:0 - 0x7ff = 0 - 10v = 0 - -1000hz for freqout */
                                                                           /* and memout or positive:0x800 - 0xfff = -10v - 0 = 1000hz - 0 */


                                                                           /* 1 block = 20hz */
                                                                           /* -110hz(450) -  +110hz(3643) */

                                                                           /* 1 block = 50hz for 20khz and 100hz for 40khz*/
                                                                           /* -275hz(1127) -  +275hz(2968) */
      CurrentMemIn = GetFilterValue(FilterMem);                            /* only used on the bargraphs */
       
      if ((CurrentMemIn > 3993) && (CurrentMemIn < 102)) {
         FMemoryBargraph = CENTERBAR;
      }
      if (CurrentMemIn <= 0x07ff) {
         CurrentMemIn++;
         if(CurrentMemIn > 1127)
            FMemoryBargraph = LESSTHENBAR;
         else if(CurrentMemIn > 923) {
            FMemoryBargraph = 1;
         }
         else if(CurrentMemIn > 718) {
            FMemoryBargraph = 2;
         }
         else if(CurrentMemIn > 513) {
            FMemoryBargraph = 3;
         }
         else if(CurrentMemIn > 308) {
            FMemoryBargraph = 4;
         }
         else if(CurrentMemIn > 103) {
            FMemoryBargraph = 5;
         }
         else {
            FMemoryBargraph = 6;
         }
      }
      else if (CurrentMemIn >= 0x0800) {
         if(CurrentMemIn < 2968)
            FMemoryBargraph = GREATERTHENBAR;
         else if(CurrentMemIn < 3172)
            FMemoryBargraph = 11;
         else if(CurrentMemIn < 3377)
            FMemoryBargraph = 10;
         else if(CurrentMemIn < 3582)
            FMemoryBargraph = 9;
         else if(CurrentMemIn < 3787)
            FMemoryBargraph = 8;
         else if(CurrentMemIn < 3992)
            FMemoryBargraph = 7;
         else {
            FMemoryBargraph = 6;
         }
      }
      
      CurrentFreqIn = GetFilterValue(FilterFreq);
      
      if ((CurrentFreqIn > 3993) && (CurrentFreqIn < 102)) {
         FActualBargraph = CENTERBAR;
      }
      if (CurrentFreqIn <= 0x07ff) {
         CurrentFreqIn++;
         if(CurrentFreqIn > 1127)
            FActualBargraph = LESSTHENBAR;
          else if(CurrentFreqIn > 923) {
            FActualBargraph = 1;
         }
          else if(CurrentFreqIn > 718) {
            FActualBargraph = 2;
         }
          else if(CurrentFreqIn > 513) {
            FActualBargraph = 3;
         }
          else if(CurrentFreqIn > 308) {
            FActualBargraph = 4;
         }
          else if(CurrentFreqIn > 103) {
            FActualBargraph = 5;
         }
          else {
            FActualBargraph = 6;
         }
      }
      else if (CurrentFreqIn >= 0x0800) {
         if(CurrentFreqIn < 2968)
            FActualBargraph = GREATERTHENBAR;
         else if(CurrentFreqIn < 3172)
            FActualBargraph = 11;
         else if(CurrentFreqIn < 3377)
            FActualBargraph = 10;
         else if(CurrentFreqIn < 3582)
            FActualBargraph = 9;
         else if(CurrentFreqIn < 3787)
            FActualBargraph = 8;
         else if(CurrentFreqIn < 3992)
            FActualBargraph = 7;
          else {
            FActualBargraph = 6;
         }
      }
      if(CurrentFreqIn > MAXVOLT){
         CurrentFreqIn -=  2048; 
         switch (CurrentSetup.PSFreq) {
            default:
            case FREQ20KHZ:    
               CurrentFreqIn = GetInterpolatedUINT16(NegFreq20kTable,CurrentFreqIn);
               break;
            
            case FREQ40KHZ:    
               CurrentFreqIn = GetInterpolatedUINT16(NegFreq40kTable,CurrentFreqIn);
               break;
            
            case FREQ15KHZ:    
               CurrentFreqIn = GetInterpolatedUINT16(NegFreq15kTable,CurrentFreqIn);
               break;
            
            case FREQ30KHZ:    
               CurrentFreqIn = GetInterpolatedUINT16(NegFreq30kTable,CurrentFreqIn);
               break;
            
            case FREQ60KHZ:    
               CurrentFreqIn = GetInterpolatedUINT16(NegFreq60kTable,CurrentFreqIn);
               break;
         }
      }
      else{
         switch (CurrentSetup.PSFreq) {
            default:
            case FREQ20KHZ:    
               CurrentFreqIn = GetInterpolatedUINT16(PosFreq20kTable,CurrentFreqIn);
               break;
            
            case FREQ40KHZ:    
               CurrentFreqIn = GetInterpolatedUINT16(PosFreq40kTable,CurrentFreqIn);
               break;
            
            case FREQ15KHZ:    
               CurrentFreqIn = GetInterpolatedUINT16(PosFreq15kTable,CurrentFreqIn);
               break;
            
            case FREQ30KHZ:    
               CurrentFreqIn = GetInterpolatedUINT16(PosFreq30kTable,CurrentFreqIn);
               break;
               
            case FREQ60KHZ:    
               CurrentFreqIn = GetInterpolatedUINT16(PosFreq60kTable,CurrentFreqIn);
               break;

         }
      } 
      if(RunningPreset.DigitalFilterFlag == TRUE)     
         CurrentFreqIn = DigFilterFreq(CurrentFreqIn);
      
   }      
}     
      
void WritePSDAC(UINT16 FreqValue, UINT16 AmpValue){
// The SPILIST[PSDAC] will have use 2 of the 16 command ram registers.
// Command Register [0] will output Frequency Offset and [1] will output
// Amplitude The Maxim Max532 is used to convert the 24 serial bit
// stream into the 2 channels of analog outputs.
// The voltage swing is from -10v to +10v. The following registers need to be 
// changed before the list can be executed.

   QsmMap->TxdData[0] = FreqValue;

   QsmMap->TxdData[1] = AmpValue;  

     QsmMap->Spcr2.Newqp = 0;                                              /* Frequency Offset */
     QsmMap->Spcr2.Endqp = 1;                                              /* Amplitude In */
     QsmMap->Spcr0.Cpha = 0;                                               /* Data is captured on the leading edge of SCK. */
     QsmMap->Spcr0.Cpol = 0;                                               /* The inactive state value of SCK is low */
     QsmMap->Spcr0.Bits = 12;                                              /* Number of bits per transfer */
     QsmMap->Spcr1.Dtl = 2;                                                /* length of delay after transfer */
     QsmMap->Spcr0.Spbr = SCLK_AD_PS;
}

void WriteBarGraph(void){

                                                                           // need to update only once
   
   if(PowerUPBGraph == TRUE) {
   QsmMap->TxdData[13] = 0x9fff;                                           /* Configure bargraph */
   QsmMap->TxdData[14] = 0xff9f;
   QsmMap->TxdData[15] = 0xffff;

      PowerUPBGraph = FALSE;
      QsmMap->ContRam[13].Cont = 1;                                        /* chip select held low */
   }
   QsmMap->Spcr0.Spbr = SCLK_BARG;

                                                                           // these two signals are inverted in hardware  

   QsmMap->Spcr0.Cpol = 1;
   QsmMap->Spcr0.Cpha = 0;

   QsmMap->Spcr1.Dsckl = 3;                                                /* CHGED??? 6 */
   QsmMap->Spcr1.Dtl = 7;                                                  /* length of delay after transfer */
      
   QsmMap->Spcr0.Bits = 16;                                                /* Number of bits per transfer */
   QsmMap->Spcr2.Newqp = 13;
   QsmMap->Spcr2.Endqp = 15;
   GetLedStatus();
}

static UINT16 GetFilterValue(UINT16 TableValue[]){

   UINT16 FilterValue;

   
                                                                           /* throw away element 0*/
   if((TableValue[0] < TableValue[1]) && (TableValue[0] < TableValue[2])){
                                                                           /* throw away element 1 */
      if(TableValue[1] > TableValue[2]){
         FilterValue = TableValue[2];
      }
                                                                           /* throw away element 2 */
      else{
         FilterValue = TableValue[1];
      }
   }
                                                                           /* throw away element 1*/
   else if((TableValue[1] < TableValue[0]) && (TableValue[1] < TableValue[2])){
                                                                           /* throw away element 1 */
      if(TableValue[0] > TableValue[2]){
         FilterValue = TableValue[2];
      }
                                                                           /* throw away element 2 */
      else{
         FilterValue = TableValue[0];
      }
   }
                                                                           /* throw away element 2*/
   else if((TableValue[2] < TableValue[0]) && (TableValue[2] < TableValue[1])){
                                                                           /* throw away element 0 */
      if(TableValue[0] > TableValue[1]){
         FilterValue = TableValue[1];
      }
                                                                           /* throw away element 1 */
      else{
         FilterValue = TableValue[0];
      }
   }
   else if((TableValue[0] == TableValue[1]) || (TableValue[0] == TableValue[2])){
         FilterValue = TableValue[0];
   }
   else if(TableValue[1] == TableValue[2]){
         FilterValue = TableValue[1];
   }
   else FilterValue = TableValue[0];
   return(FilterValue);
}


UINT16 GetSpringForce(void)
/****************************************************************************/
/*                                                                          */
/* This function subtracts off the spring force from the load cell reading  */
/*                                                                          */
/* Inputs: CurrentSetup.SpringRateTable                                     */
/*         EncoderPos                                                       */
/*                                                                          */
/****************************************************************************/


{
   UINT16 Offset,SpringIndex;

   SpringIndex = (UINT16) EncoderPos>>11;                                  /* Divide by 0x800 */
   if(SpringIndex == 0) SpringIndex = 1;                                   /* this compensates for the snubber */
   Offset = CurrentSetup.SpringRateTable[SpringIndex];
   return(Offset);
}


void CenterDigPot(void){
                                                                           /**  **  Attempt to center the digital pot and force output  **  **/

   InitDigitalPot();
   CenterPotFlag = TRUE;
   EnableDigPotFlag = TRUE;
                                                                           /* Move digital pot to one end     */
   asm(" ori.w #$20,$fffe18");                                             /* drive pin high */
   DigPotPinHigh = TRUE;
   if(IncrementPot < (UINT16) DIGPOTCOUNT){
      DigPotKey = TRUE;
   }
                                                                           /* Move digital pot to middle      */
   else{
      if(IncrementPot < (UINT16)(DIGPOTCOUNT + 50)) {
         asm(" ori.w #$10,$fffe18");                                       /* drive pin low */
         DigPotPinHigh = FALSE;
         DigPotKey = TRUE;
      }
      else{
         DisableDigPot();
         EnableDigPotFlag = FALSE;
         CenterPotFlag = FALSE;
         IncrementPot = 0;
      }
   }
}


void SetDigPot(void){
                                                                           /* Called at power up & when chging digpot & from write pvp when digpot active */

   InitDigitalPot();
   CenterPotFlag = FALSE;
   EnableDigPotFlag = TRUE;
   if(CurrentSetup.DigPot <= 0){                                           /* Move digital pot to low end */
      asm(" ori.w #$20,$fffe18");                                          /* drive pin high set to decrement*/
      DigPotPinHigh = TRUE;
      if(IncrementPot < (UINT16)DIGPOTCOUNT){
         DigPotKey = TRUE;
      }
      else{                                                                /* Move digital pot to the setting   */
         if(IncrementPot < (UINT16)(DIGPOTCOUNT + (CurrentSetup.DigPot+2999)/60)) {
            asm(" ori.w #$10,$fffe18");                                    /* drive pin low */
            DigPotPinHigh = FALSE;
            DigPotKey = TRUE;
         }
         else{
            DisableDigPot();
            EnableDigPotFlag = FALSE;
            IncrementPot = 0;
         }
      }
   }
   else{                                                                   /* Move digital pot to the high end     */
      asm(" ori.w #$10,$fffe18");                                          /* drive pin low to increment */
      DigPotPinHigh = FALSE;
      if(IncrementPot < (UINT16)DIGPOTCOUNT){
         DigPotKey = TRUE;
      }
                                                                           /* Move digital pot to the setting   */
      else{
         if(IncrementPot < (UINT16)(DIGPOTCOUNT + 99 - (CurrentSetup.DigPot+2999)/60)) {
            asm(" ori.w #$20,$fffe18");                                    /* drive pin high to decrement */
            DigPotPinHigh = TRUE;
            DigPotKey = TRUE;
         }
         else{
            DisableDigPot();
            EnableDigPotFlag = FALSE;
            IncrementPot = 0;
         }
      }
   }
}

void EnableDigPot(void){

   InitDigitalPot();
   CenterPotFlag = TRUE;
   EnableDigPotFlag = TRUE;
   DigPotKey = TRUE;
}

void DisableDigPot(void)
{

   UINT16 i;

   for(i=0; i < 20000; i++);
   InitPVP();

}

static void CheckEPSignals(void)
/*******************************************************************************/
/*                                                                             */
/* When at home check pressure changes.                                        */
/*                                                                             */
/* Inputs: CurrentPressure - read every 4ms                                    */
/*                                                                             */
/* Outputs: HomePressure - Averaged pressure at home                           */
/*                                                                             */
/*******************************************************************************/    
{

                                                                           /* Check for expiration of home position debounce timer. */
   if ((LoadCellCountDown-- < 0) || (ResetReceivedFlag == TRUE) )
   {
      if (HomePressure != POWERUP_PRESSURE) {
         HomePressure = HomePressure + ((CurrentPressure - HomePressure) >> 2);
      }
      else {
         HomePressure = CurrentPressure;                                   /* 1st reading after power up */
      }
      LoadCellCountDown = LOADCELLDELAY;    
   }                 
}
 


UINT32 DigFilterAmp (UINT16 Element){
/**************************************************************************
   The following filter functions take an element and return the average
   of the last indexfilter(8) back; It returnes the average of the last 
   8 points. Using: Sum + New - Last / 8 

***************************************************************************/

   UINT16 temp;                                                            // Last Value
   if(aptr==&BufferAmp[FilterIndex8-1]){
      temp=*aptr;                                                          // Move old to temp
      *aptr=Element;
      aptr=&BufferAmp[0];
   }
   else{                  
      temp=*aptr;                                                          // Move old to temp
      *aptr=Element;                                                       // Insert new into buffer 
      ++aptr;
   }
   AmpSum=AmpSum+Element-temp;        
   return ( AmpSum >> 3);                                                  // Devide by 8;  -->000
}

UINT32 DigFilterPower (UINT16 Element){
UINT16 temp;   // Last Value
   if(pptr==&BufferPower[FilterIndex8-1]){
      temp=*pptr;                                                          // It was the last element
      *pptr=Element;
         pptr=&BufferPower[0];
   }
   else{
      temp=*pptr;                                                          // It was the last element
      *pptr=Element;
      ++pptr;
   }
   PwrSum=PwrSum+Element-temp;     
   return (PwrSum >> 3);                                                   // Devide by 8;  -->000
}

UINT32 DigFilterFreq (UINT16 Element){
UINT16 temp;   // Last Value
   if(fptr==&BufferFreq[FilterIndex8-1]){
      temp=*fptr;                                                          // It was the last element
      *fptr=Element;
      fptr=&BufferFreq[0];
   }
   else{
      temp=*fptr;                                                          // It was the last element
      *fptr=Element;
      ++fptr;
   }
   FrqSum=FrqSum+Element-temp;     
   return (FrqSum >> 3);                                                   // Devide by 8;  -->000
}

UINT16 ForceEstimator(UINT16 NewSample)
/*************************************************************************/
/* This code does force estimating using the filter [1/16,1/8,9/16,1/4]. */
/*************************************************************************/
{
   UINT16 Temp;

   ForceEstimateBuffer[0] = ForceEstimateBuffer[1];
   ForceEstimateBuffer[1] = ForceEstimateBuffer[2];
   ForceEstimateBuffer[2] = ForceEstimateBuffer[3];
   ForceEstimateBuffer[3] = NewSample;

   Temp = (ForceEstimateBuffer[0] + ForceEstimateBuffer[2]) >>2;   
   Temp = Temp + (ForceEstimateBuffer[2]<<1) + ForceEstimateBuffer[3];
   Temp = ( Temp + (ForceEstimateBuffer[1] >>1) ) >>2;
   return (Temp);
}

//--------------------------- END OF FILTERS -------------------------------

BOOLEAN PartContactMade(void)
/************************************************************************/
/* This is the part contact algorithm.  It is called from ReadACTADC(). */
/************************************************************************/
{
   UINT16  ForceSum;
   BOOLEAN TriggerMet;

   TriggerMet = FALSE;
   ForceSum = ForceEstimator(CurrentForce);

   if (CurrentVelocity <= BUCMenuRAM.VelocityPC)                           /* Have we slowed down to part contact? */
   {   
      if(ForceSum > (UINT16)BUCMenuRAM.ForcePC) {                          /* Are we exerting enough pressure on the part yet? */ 
         TriggerMet = TRUE;
      }
   }
   return(TriggerMet);
}   



void CheckForHornChange(void)
/************************************************************************/
/*                                                                      */  
/* This function checks for a horn weight change from the last power    */
/* up or the last EStop. It is called from TestPO3()and from weldmanger.*/
/*                                                                      */
/* Inputs: CurrentSetup.SpringRateTable[0] - Home weight offset         */
/*                                                                      */  
/* Output: Alarm generated if condition met                             */
/*         AlarmHornWeight                                              */
/*                                                                      */  
/************************************************************************/
{
   UINT16 LoadCellDifference;
   BUCMENU_800  *BUCMenuBBR;
   
   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   if (BUCMenuBBR->RecalCode300 == TRUE) {
      if(CurrentSetup.SpringRateTable[0] > LoadCellIndex)
      {
         LoadCellDifference = CurrentSetup.SpringRateTable[0] - LoadCellIndex;
         if(LoadCellDifference > FIVE_LB)                                  /* a 5 lb change detected */
         {
            RecordErrorCode( ERRORCODE300_EQ20 );
            RecordAlarm(EQ20);                                             /* Recal actuator             */
            AlarmHornWeight = LoadCellIndex;                               /* Used in the Debug menu     */
         }
      }
      else
      {
         LoadCellDifference = LoadCellIndex - CurrentSetup.SpringRateTable[0];
         if(LoadCellDifference > FIVE_LB)
         {
            RecordErrorCode( ERRORCODE300_EQ20 );
            RecordAlarm(EQ20);                                             /* Recal actuator             */
            AlarmHornWeight = LoadCellIndex;                               /* Used in the Debug menu     */
         }
      }   
   }
}

/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "..\ut\spidd.ut"
#endif   
/* End of include for unit test */

