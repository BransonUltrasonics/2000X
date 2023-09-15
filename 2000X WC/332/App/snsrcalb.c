/* $Header:   D:/SWLab/VMdb/2000Series/App/SNSRCALB.C_V   2.169.1.3   28 Jul 2010 19:30:14   NHahmed  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                           */
/*************************                         **************************/

/*--------------------------- MODULE DESCRIPTION -----------------------------
                                                                          
 Module name: Sensor Calibration                                          
                                                                          
 Filename:    Snsrcalb.c                                                   
                                                                          
 Function Name: Calibration code                                          
                                                                          
          Written by:   Bill Truchsess                                    
                Date:   04-15-96                                          
            Language:   "C"                                               
                                                                          
------------------------------ REVISIONS -------------------------------------
                                                                          
 Rev # Date     Author  Description                              
 ===== ======== ======= ===========                              
 0     05-03-96 WFT     Initial write of code                    
 1     05-05-96 LAM     deleted displaymenu prototype            
 2     05-13-96 BEKymer Add proper function prototyping          
 3     06-06-96 BEKymer Remove unused code                       
 4     06-11-96 BEKymer Add DistanceVerifyInit function          
 5     06-15-96 BEKymer Subtract out springs in force reading    
 6     06-25-96 BEKymer Move where spring rate is subtracted     
 7     07-08-96 LAM     delete springrate chged loadcelltable    
 8     07-20-96 BEKymer Removed weld.h                           
 9     07-30-96 LAM     Added save preset                        
 10    07-30-96 LAM     changed force and pressure tbls to preset
                        chged min/max force settings             
 11    09-18-96 LAM     added velocity equation                  
 12    10-10-96 LAM     fixed downspeed equation                 
 13    10-14-96 LAM     added pressure pts to menu enter         
 14    10-31-96 LAM     fixed metric conversion                  
 15    11-08-96 LAM     fixed verify dist pass/fail,added error  
                        to updatecalibrated table, moved calib   
                        sequences from states.c                  
 16    11-21-96 LAM     corrected springrate loadcell calibration
 17    11-25-96 LAM     added springrate calculation             
 18    12-03-96 LAM     chged downspd on verify distance         
 19    12-09-96 BEKymer Added menusync to SelectDistanceCal...   
 20    12-09-96 LAM     cleanup code                             
 20.01 12-11-96 LAM     average springrate table                 
 21    12-19-96 LAM     average calibrated values                
 22    12-21-96 LAM     chged what is saved to the preset        
 23    12-30-96 LAM     chged trigger force for calibration      
 24    01-08-97 LAM     fixed false triggering                   
 25    01-17-97 PhilJ   Fixed divide by 0 in GetCountsPerLb      
 26    04-18-97 PhilJ   Chngd StuffKey to SendFakeKeyPress       
 27    06-13-97 PhilJ   Chngd UpdateCurrentSetup to UpdateCurrentPreset              
 2.62  04-23-98 LAM     started implementing sensor calibration for Rel2.5.  
 2.63  04-24-98 LAM     verify loadcell table  = +/- 6 lbs       
 2.64  04-30-98 LAM     added calibration mask                   
 2.65  05-04-98 LAM     added requestsensorcal, temp table arrays
                        added default springrate table           
 2.66  05-14-98 LAM     added pass condition to pressure verify  
 2.69  05-15-98 LAM     fixed pass fail condition                
 2.70  05-18-98 LAM     restart state machine after calibration  
                        rescaled springrate index to 0.1024      
 2.71  05-21-98 LAM     adjusted springrate table                
 2.72  05-22-98 BJB     changed FORCE_RANGE to tenths of pounds. 
                        passes new Offset argument to            
                         UpdateCalibratedTable() when building   
                         pressure & force tables.                
 2.73  06-01-98 LAM     chged springrate table to 0.2048, added  
                        pass/fail condition, first pass at adjusting
                        loadcell table                           
 2.74  06-05-98 LAM     corrected springrate, first pass of +/-1 
                        lb, ver 5.0g, fixed beep at end          
 2.75  06-10-98 LAM     temporary put back for rel 5.0h          
 2.76  06-12-98 LAM     added fail condition to calibration when 
                        no keys are pressed                      
 2.77  06-19-98 LAM     added text screen when calibration passes
 2.78  06-19-98 LAM     redid statemachince with new menusync    
 2.79  06-25-98 LAM     deleted verify step for load celll       
 2.80  07-01-98 LAM     added spring rate averaging, added check 
                        lost palm buttons and lost pressure      
 2.81  07-01-98 LAM     chged spring rate averaging              
 2.82  07-02-98 LAM     do not update the spring rate table when 
                        stroke length is less than 0.500 in      
 2.83  07-07-98 LAM     chged spring rate table, chged part contact algorithm
 2.84  07-15-98 LAM     change value of timer if pass or fail calration
 2.85  07-17-98 LAM     change spring rate table averaging               
 2.86  07-23-98 LAM     added verify point but do not bring horn       
 2.87  07-30-98 LAM     removed verify point, update springrate  
                        when stroke is < .6, save horn weight at home 
 2.88  07-30-98 BJB     Deleted act_nvr definition, uses actnvram.h        
 2.89  07-31-98 LAM     clear recal actuator alarm when complete 
 2.90  08-03-98 LAM     added verify screen                      
 2.91  08-11-98 LAM     fixed updatespringrate to detect horn    
                        weight changes when the stroke < 0.6145  
                        change partcontact to distance method    
 2.92  08-19-98 BJB     Changed UpdateVFLine() calls to          
                        UpdateLine().                            
 2.93  08-21-98 LAM     moved calls to weldmngr to menutask      
                        added function to check if calibration is allowed
 2.94  08-24-98 LAM     chged currentpressure to homepressure    
 2.95  09-01-98 LAM     updated calibration data                 
 2.96  09-08-98 LAM     donot remove calibration screen when popup is displayed
 2.97  09-10-98 LAM     chged calibration popup screen to 1 second             
 2.99  10-09-98 LAM     deleted unneeded calibration states                      
 2.100 11-06-98 LAM     abort calibration if start switches are let go at
                         ULS
 2.101 11-10-98 LAM     fixed pressure failed value when greater then 99PSI or KPA,
                        added another menu sync state for extra submenu.
 2.102 11-18-98 LAM     chged springratedistance to 3 from 5 to travel further down
                        before exiting calibration for slow down speeds
 2.103 03-15-99 LAM     fixed SetForce prototype
 2.104 05-27-99 JZ      fixed BuildVelocityTable
 2.105 06-10-99 CMC     CalForceMenuXX changes for AEF
                          changes made only to InitCalTimer()
 2.106 06-16-99 JZ      rewrote Velocity60PSI[] and Velocity80PSI[] with defines
2.107.1.2 07-01-99 JZ   made code for SetPV, deleted SelectVelocityControl,
                        SetVelocity, changed Velocity60PSI and Velocity80PSI to SINT32 type
                        plus merge with calibration branch 2.107.2.1 plus commented some
                        code to be able to compile
2.107.2.3 07-02-99 LAM  merged 2.107.2.2 with 2.107.1.2
2.107.2.4 07-08-99 JLH  More Cal Sensors task updates.
2.107.2.5 07-10-99 JLH  More Cal Sensors task updates.
2.107.2.6 07-12-99 JLH  Correct Build Pressure Table subroutine.
2.107.2.7 07-12-99 JLH  Fix LinearReg to return slope, intercept, and variance. Added
                        DisplayNextScreen function.
2.107.2.8 07-14-99 JLH  Various updates made by Laura, some of which are test-only.  Do
                         difference with 2.107.2.7 to determine changes.
2.107.2.9 07-16-99 JLH  Updates made during calibration debugging; debugging not complete.
2.107.2.10 07-20-99 JLH Updates made during calibration debugging; debugging not complete.
2.107.2.11 07-20-99 LAM added variance to triggerforce,added new function to set velocity
                        table to 60PSI, correct table is loaded when calibration is exited.
                        need to update the NVR.Force before saving it to novram. Set
                        downspeed to 25%.
2.107.2.12 07-22-99 LAM fixed LastIndex going negative in UpdateSpringRate
2.107.2.13 07-23-99 JLH Updated for operator collection of 3 load cell readings.                        
2.107.2.14 07-27-99 JLH Fixed bug in CollectForceData       
2.107.2.15 07-28-99 LAM fixed 3rd point of loadcell fixed first point of loadcell table to use
                        y-intercept, made first point = 20lbs.                                            
2.107.2.16 07-29-99 LAM save calibration system pressure, modify build velocity to
                        correct the velocity and force tables based on cylinder and
                        system pressure, average pressure during calibration, added
                        2 in cylinder velocity tables
2.110      07-30-99 LAM made user force entries = 0 on entry, added call to velocity estimator.
2.111      07-30-99 LAM fixed the DONE screen from stopping
2.112      08-06-99 LAM changed 2in. cyl from 44500,19000 to 42615,13000, changed
                        3in. cyl 63500,27000 to 61615,21000, made forcetabledelta global
                        it will be used by SetPV
2.113      08-06-99 JZ  removed some defines from snsrcalb.c, first arg of SetPV typcasted to UINT16
2.114      08-11-99 LAM fixed ForceTableDelta to SINT16 
2.115      08-16-99 LAM use intercept for the spring rate table
2.116      08-23-99 LAM fixed springratetable, save calibration distance when doing
                        sensor calibration
2.117      08-25-99 LAM fixed springratetable slope when switching to extrapolation
2.118      08-25-99 LAM changed IDLE from 1 to 80
2.119      09-07-99 LAM update pressure in ready not buildvelocitytable, change running
                        preset to current preset for rapid traverse in cal actuator
2.120      09-07-99 LAM deleted unused code
2.121      09-08-99 LAM changed calibrated system pressure and stroke to NVR structure
2.122      09-09-99 LAM updated buildvelocitytable for 2in and 3in cylinder
2.123      09-10-99 LAM updated buildvelocitytable for 2in and the restrictor
2.124      09-14-99 LAM fixed default springrate to include The Force increase when leaving
                        home to 0.2048 in.
2.125      09-20-99 LAM sav springrateslope to NVR, changed velocity tables, cal actuator and
                        cal sensors both come down slow
2.126      09-20-99 LAM added horn weight offset                        
2.127      09-22-99 LAM need to increase down speed if too slow              
2.128      09-22-99 LAM changed hornweight offset calculation              
2.129      09-27-99 BEK Removed all calls to SetPV(HOLD_TO_HOME)
2.130      09-30-99 LAM need to add two calls to SetPV(HOLD_TO_HOME) back. 
2.131      10-26-99 JZ  modified BuildForceTable() and CalibFinalCleanup()
2.132      10-29-99 LAM temporarily made delay between PV steps a variable
2.133      11-03-99 JLH Various changes requested in calibration code review.
2.134      11-04-99 JLH Replace tabs with equivalent spaces.  Add comments for temporary use
                         of CurrentPreset.TimePLS to time PV force changes. 
2.135      11-05-99 LAM changed delay between updates to 15 seconds                                           
2.136      11-05-99 LAM removed 5.0 and replaced with define 
2.137      11-15-99 LAM made sure downspeed would not exceed 100%, need 25 lbs 
                        part contact before switching to done. 
2.138      11-17-99 LAM 25lbs correction                                                                 
2.139      11-18-99 LAM need minimum number of points for springrate update 
2.140      12-06-99 LAM moved calibration test from mansensr.c 
2.141      12-20-99 JZ  made backward compatibility with AED                                                               
2.142      02-08-00 LAM turned SV off when done screen appears, fixed invalid
                        date when pressure sensor fails calibration  
2.143      04-13-00 JZ  changed CheckSpringRate and UpdateSpringRate for 15kHz
2.144      04-18-00 JLH Replaced HornWeightOffset with CurrentSetup.HornWeightOffset.
2.145      04-19-00 JLH Added AEDUpgraded global and modified UpdateSpringRate.
2.146      05-09-00 JLH Added 4-element LeavingHomeForce array, indexed by CurrentSetup.PSFreq.
                        Changed AED Upgrade error tests to use ERRORCODE1000_EQ20.
2.147      05-09-00 JLH Changed ErrorCode declaration to extern enum ERRORCODE_ARG.
2.148      05-26-00 SCM      Checked in for testing by Laura, John.
2.149      07-07-00 BEKymer/DJL    fixed SETUP
2.150      08-30-00 LAM Corrected spring rate calculations for heavy horns
                        (Issue 3304)
2.151      09-20-00 LAM made clearing alarms consistent with cal actuator
2.152      10-30-00 LAM UpdateSpringRate to update the SpringRate table correctly
                        (Issue 3661)
2.153      10-31-00 LAM Update Default HornOffset after configuration(Issue 3661)
2.154      11-01-00 LAM Only SetReady when Calibration passes(Issue 3662)
2.155      11-13-00 BEK Remove LeavingHomeForce array and made it only a single value.
                         The PSFreq index used was referencing 1 element beyond the 
                         end of the array.  40Khz was enum 4, array was element 0 to 3.
                         This fixes issues #3675 and #3679.  
2.156      01-16-01 BEK Add arguments as needed to functions called from the menu structure
2.155.2.0  04-02-02 LAM removed AEDUpgraded flag, calibration always updates the springrate table.
2.155.2.1  04-10-02 LAM replaced 1000 vs. LC_OFFSET
2.155.2.2  05-06-02 LAM modifed error codes.
2.155.2.3  05-17-02 LAM modifed error code test again. Only build table with
                        100 offset when the actuator is an AED
2.155.2.4  07-21-03 JOY QVGA Sensor Calibration flag 'QVGASnsrCalibAllowed' is reset
                        at the end of Calib procedure, in 'CalibFinalCleanup()'.
2.155.2.5  10-23-03 JOY TheMainMenu replaced with QVGATheMainMenu.
2.157      08-05-03 BEK Merged 2.156 and 2.155.2.3 to create 2.157 for 9.00A build
                        -Add arguments as needed to functions called from the menu structure
2.158      12-05-03 BEK Merged 2.155.2.6 & 2.157 to create 2.158 for Ver9.00b build
2.159      05-07-04 LAM merged with 8.22
2.160      07-27-04 JOY Updated UpdateSpringRate() with FREQ60KHZ.
                        Modified #define PSI_RANGE to 40.
2.161      12-30-04 LAM Modified for SBEAM build
2.162      04-11-05 LAM Added SBeam / Loadcell defines
2.163      04-15-05 LAM corrected spring rate slope
2.164      04-26-05 LAM deleted verify distance
2.165      07-25-05 Bwadia Asian Language support for sensor calibration 
2.166      08-19-05 Bwadia IsHWConfigured function used to check for
                    VGA  hardware presence
2.167      01-10-06 LAM  modified zeroing the encoder            
2.168      08-26-06 LAM  modified springrate for sbeam         
2.169      08-30-06 LAM  sensor calibration now starts with the default tables 
2.170      10-22-07 NHAhmed   Changes done for LangTest phase 0                                                                                       
2.171      04-14-08 NHAhmed   Replicated some functions as no-argument type functions
                              and also modified a function.                   
2.172      08-01-08 NHAhmed   Renamed some functions. 
2.173      09-02-08 NHAhmed   CleanUp for multi-language support. 
2.174      09-04-08 YGupta    CleanUp for LangTest Project. 
2.175      09-09-08 NHAhmed   CleanUp for multi-language support. 
2.176      09-10-09 LAM       Added Micro Act springrate offset 
2.177      09-22-09 YGupta    Added Support for MICRO Actuator and code cleanup.
2.178      10-02-09 BEKymer   Adjust LEAVINGHOME FROCE based on hidden codes
2.179      07-28-10 PDwivedi  Added new SPRINGRATEMICRO for new and old Micro and 
                              removed use of MICRODefSpringRate to build the default spring table.
*/
                                   
/*----------------------------------------------------------------------------*/



/*----------------------------- DESCRIPTION --------------------------------*/


/*  This module includes the support functions for the sensor calibration.  */
/*  The calibration can be aborted, pass, or failed.                        */



/*---------------------------- LOCAL_EQUATES -------------------------------*/

//#define INCLUDE_UNIT_TEST
#define MAX_TABLE_PTS          (10+1)
#define MAXCALIBRATIONERROR    20
#define NOVRAMFAILED           (EQ10&(~EQG1))   /* BIT10 of equipment failure */
#define SPRINGRATEINDEX        0x800   /* 0.2048 in */
#define CALIBRATION_TIMER      3000    /* 3 secs */
#define COUNTS_PER_INCH        10000
#define MAXDISTANCEERROR       400
#define CALBAVESIZE            16
#define LC_DELAY               15000   /* 15 secs */
#define INIT_PV_DELAY          2000    /* 2 secs */
#define PSI_RANGE              40      /* +/- 4PSI */
#define FORCE_RANGE            30      /* +/- 3 lbs */
#define FORCE_ACCURACY_RANGE   10      /* +/- 1 lbs */
#define SPRINGRATE_RANGE       3       /* 3 A/D counts/ 0.2048in */
#define KPA_CONVERT            6.69    /* convert PSI */
#define NEWTON_CONVERT         4.448
#define MINIMUM_FORCE          10
#define ROUNDING_CORRECTION    10
#define OFF_THE_PART           100     /* 0.0100 in. off the part */
#define SPRINGRATE_TIMEOUT     9000    /* 9 seconds assume part contact */
#define PSI_CORRECTION         100     /* correct for table offset */
#define MIN_AD_LOADCELL        0       // was 500     /* minimum value before spring rate calculated */
#define MAX_AD_LOADCELL        3000    /* maximum value */
#define MINIMUM_NUMBER         2       /* need at least 3 points to generate a springrate */
#define SPRING_RATE_AVERAGE    3       /* average last 4 points to extend springrate table*/
#define MIN_STROKE_LEN         6145
#define ONE_SECOND             1000
#define DOWNSPEEDTIMEOUT       250
#define DEF_HORNWEIGHTLC       350 /* typical hornweight value loadcell*/
#define DEF_HORNWEIGHTSB       160 /* typical hornweight value sbeam*/
#define MINDOWNSPEED           3
#define MAXDOWNSPEED           99
#define LEAVINGHOMEFORCE       12
#define LEAVINGHOMEFORCE15KHZ  36
//#define LEAVINGHOMEFORCEMICRO  03
#define ONE_POSITION           2048
#define ONE_INCH               10000
#define FORCE_ON_THE_PART      250  /* 25lbs */
/*  equations used to calculate the Velocity table entries 
              LOW_60PSI + ((HIGH_60PSI - LOW_60PSI)*1)/256 = 45219
              LOW_60PSI + ((HIGH_60PSI - LOW_60PSI)*100)/256 = 15728
    to calculate entries for 80PSI use 59637 and 30146 in the above equation
*/

#define CAL_DOWNSPEED         10     /* calibrate sensors at 10% downspeed */
#define PSIALLOWED             3      /* 3PSI */
#define PSI2DAC               (65535.0/90.0)
#define RATIOMETRICITY 1.25   /* per load cell spec sheet */
#define LCSENSITIVITY 0.020   /* volts per psi per load cell spec sheet */
#define VOLTSPERBIT 0.004883  /* 10 volts divided by 2048 */
#define PI 3.141593
#define SPRINGRATE      5.6  /* 5.6 lbs per inch */
#define SPRINGRATEMICRO 6.5  /* 6.5 lbs per inch */
#define CALIBRATION_IDLE_VALUE 80
#define LBSPERCNT 0.432
#define GREATERTHENNOISE 2
/*------------------------------ INCLUDES ----------------------------------*/

#define SNSRCALB 
#include <psos.h>
#include <stdlib.h>
#include "names.h" 
#include "alarms.h" 
#include "interpol.h"
#include "wldstate.h"
#include "preset.h"
#include "beep.h"
#include "string.h"
#include "rtclock.h"
#include "ready.h"
#include "keypad.h"
#include "digout.h"
#include "getmsg.h"
#include "selctkey.h"
#include "spidd.h"
#include "actnvram.h"
#include "fpk_task.h"
#include "param.h"
#include "mansensr.h"
#include "menucalb.h"
#include "genrlmsg.h"
#include "statedrv.h"
#include "ck_qsend.h"
#include "util.h"
#include "snsrcalb.h"
#include "sysmangr.h"
#include "sc.h"
#include "state.h"
#include "weld_obj.h"
#include "332.h"
#include "qsm.h"
#include "menu.h"
#include "menu7a.h"
#include "encoder.h"
#include "qvgamenu.h"
#include "DrawScrn.h"


/*------------------------------ GLOBAL DATA -------------------------------*/
/*                       (scope is global to ALL files)                     */

SINT16 CalTimer;
UINT16 TimerLoopCounter;
UINT16 CalibrationPassed;
UINT16 SpringRateTimeout;
UINT16 UpdateCalbAve = 5;
UINT16 CalbAveIndex = 0;
UINT16 MicroHomeForce;
BOOLEAN CalTimerFlag;
extern SINT16 ForceTableDelta;

BOOLEAN PlsWaitTimerFlag;                   /* Please Wait Timer Flag */
BOOLEAN AdvanceMenuFlag = FALSE;
SINT32 DistanceV[MAX_VECTOR_SIZE];
SINT32 ForceV[MAX_VECTOR_SIZE];
SINT32 ForceVcnts[MAX_VECTOR_SIZE];
SINT32 AdCntsLC[MAX_VECTOR_SIZE];
SINT32 PVDacCnts[MAX_VECTOR_SIZE];
SINT16 PVPCountsLb;
SINT16 LCCountsLb;
SINT16 TempPressureTable[MAX_CAL_PTS] ;
SINT32 TempForceTable[MAX_CAL_PTS] ;
SINT16 TempLoadCellTable[MAX_CAL_PTS] ;
UINT16 TempSpringRateTable[SPRING_RATE_SIZE] ;
UINT16 NoPressureFlag = TRUE;
UINT16 RawPVPValue;
SINT32 AdCntsPSI[3];
FLOAT  SpringRateSlope;
UINT16 CheckDownSpeed = 0; 
UINT16 DownSpeedIncrement = 0;

const SINT32 Velocity60PSI3in[] = {LOW_60PSI, HIGH_60PSI};
const SINT32 Velocity60PSI2in[] = {49250, -16333}; /* values for restrictor verified on AEF # 6*/

const UINT16 MICRODefSpringRate[]={312,323,331,340,348,357,365,374,382,390,
								   398,406,414,422,430,438,446,454,462,470,
								   478,486,494,502,510,518,526,534,542,550,
								   558,566,574,582,590,598,606,614,622,630}; 


/*----------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                       (scope is global to THIS file)                     */


static SINT16 TemporaryCalSysPressure;
static GENERIC_MSG WeldMsgOut;
static UINT16 PVControlSignal;
static UINT16 CollectForceDataDelay;
static UINT16 CollectForceDataIndex;
static SINT32 TempTriggerForce;
static WELD_STATE_MSG calbmsg;
extern UINT32 CalbAve[];
static UINT16 AvePressure[CALBAVESIZE];
static UINT32 TemporaryCalStrokeLen;

/* structure used by LinearReg function */
static struct Regression {
       FLOAT  slope;
       FLOAT  intercept;
       FLOAT  variance;
       } ;

extern UINT32 QvgaQid;
extern UINT32 RvtsQid;
extern UINT32 CurrentVelocity;
extern UINT16 PartContactFlag;
extern SINT32 HomePressure;
extern UINT8  MainKeyFlag;
extern UINT16 HomeReading;
extern SETUPS_Ver800 RunningPreset;
extern CONFIGSETUP CurrentSetup;
extern UINT32  WmgrQid;
extern BOOLEAN SpringRateComplete;
extern UINT16  ADForce,ADPressure;
extern SINT16 LoadCellIndex;
extern UINT32 SysmQueueId;
extern enum ERRORCODE_ARG ErrorCode;
extern UINT16 Mode;
extern enum WELDSTATES WeldState;
extern RAMP  RampPV;

extern INBITS Inp;

extern UINT16 AlarmFlag;
extern WELD_DATA WeldingResults;
extern SETUPS_Ver800 MinLimit;

extern SINT32  UserPressure[3];
extern SINT32  EncoderPos;
extern SINT32  CurrentForce;
extern STATE  *WeldSequence[NMBR_OF_STATES];      /* Current weld cycle definition */
extern enum   WELD_SEQUENCE_TYPE CurrentSequence;
extern UINT32 CalbAve[];
extern UINT16 CalibrationPassed;
extern BOOLEAN QVGASnsrCalibAllowed;
extern BOOLEAN QVGACalAllowed;
extern BOOLEAN QVGAHwAvail;
extern QVGA_MENU_INFO MenuLevelInfo[];

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/

void CheckForNoPressure(void);
struct Regression LinearReg(SINT32* x, SINT32* y, UINT16 n);
UINT16 LangStrLen(SINT8 * str); 
BOOLEAN LangCheckNull(SINT8 * Line);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);
SINT16 SPrintf(SINT8* pc_buf, const SINT8* pc_format,...);

/*-------------------------------- CODE ------------------------------------*/

void CalibrationInit(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called if calibration is allowed. This initializes the  */
/* calibrate sensor variables. All outputs are set to there initial         */
/* conditions                                                               */
/*                                                                          */
/* Inputs :  StrMX_26                                                       */
/*           NVR.PressureTable                                              */
/*           NVR.LoadCell                                                   */
/*           NVR.Force                                                      */
/*                                                                          */
/* Outputs : PassFailStr - displayed when pressure sensor calibration fails */
/*           AdvanceMenuFlag - used to keep the menu task in sink with the  */
/*                             calibration state machince                   */
/*           SpringRateComplete - Flag set when part contact is made        */
/*           PlsWaitTimerFlag - used to advance the state machine           */
/*           ForceV[1] - second entered loadcell reading             */
/*           UserPressure[0] - first entered pressure sensor reading        */
/*           UserPressure[1] - second entered pressure sensor reading       */
/*           LCADcnts[1] - second A/D reading from the loadcell     */
/*           NoPressureFlag - used to abort calibration when there is no    */
/*                            pressure                                      */
/*           TimerLoopCounter - used to wait for first loadcell point to    */
/*                              settled out                                 */
/*           SpringRateTimeout - Timeout used if part contact not made      */
/*           TempPressureTable - save last pressure table incase calibration*/
/*                               is aborted                                 */
/*           TempLoadCellTable - save last loadcell table incase calibration*/
/*                               is aborted                                 */
/*           TempForceTable - save last force table in case calibration is  */
/*                               aborted                                    */
/*           CalibrationPassed - assume calibration will be aborted         */
/*                                                                          */
/****************************************************************************/ 
{

   UINT16 Index;

   UserPressure[0] = 0;     /* Set illegal for later verification        */
   UserPressure[1] = 0;     /* Set illegal for later verification        */
   UserPressure[2] = 0;
   CheckDownSpeed = 0;
   DownSpeedIncrement = 0;
   ForceTableDelta = 0;
   CurrentVelocity = 0;
   NoPressureFlag = TRUE; 
   TimerLoopCounter = INIT_PV_DELAY;
   PartContactFlag = FALSE;
   AdvanceMenuFlag = FALSE;
   SpringRateComplete = FALSE; 
   PlsWaitTimerFlag = TRUE;    /* Please Wait Timer Flag */
   SpringRateTimeout = 0;
   CalibrationPassed = CAL_ABORTED;   /* assume calibration will be aborted */
   SetPV(CALIBRATION_IDLE_VALUE,HOLD_TO_HOME);
   InitCalMenus();
   SelectSensorCalSequence();  /* Initialize State Sequence for Calibration */

   /* Save current tables in case of failure */
   GetDefSpringRateTable();   /* save current springrate table */

   for(Index = 0; Index < MAX_TABLE_PTS; Index++)
      TempPressureTable[Index] = NVR.Pressure[Index];
   for(Index = 0; Index < MAX_TABLE_PTS; Index++)
      TempLoadCellTable[Index] = NVR.LoadCell[Index];
   for(Index = 0; Index < FORCE_TABLE_SIZE; Index++)
      TempForceTable[Index] = NVR.Force[Index];

   GetDefPressure();  /* Update pressure, loadcell, and pvp tables with defaults */
   GetDefLoadCell();
   GetDefForce();

   TempTriggerForce = RunningPreset.TriggerForce;
   RunningPreset.TriggerForce = MinLimit.TriggerForce;
}



void GetDefSpringRateTable(void)
/****************************************************************************/ 
/*                                                                          */
/* Save springrate table in case calibration is aborted. Called when the    */
/* calibration sequence is initialized                                      */
/*                                                                          */
/* Inputs : CurrentSetup.SpringRateTable                                    */
/*                                                                          */
/* Outputs : TempSpringRateTable                                            */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Index;

   for(Index = 0; Index < SPRING_RATE_SIZE; Index++){
      TempSpringRateTable[Index] = CurrentSetup.SpringRateTable[Index];
   }
}



void BuildDefaultSpringRate(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when a checksum is done, an upgrade is done, and */
/* when Actuator cold start is done                                         */
/*                                                                          */
/* Inputs : ADForce                                                         */
/*          CurrentSetup.GainFactor                                         */
/*                                                                          */
/* Outputs : CurrentSetup.SpringRateTable                                   */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Index;
   UINT32 Distance = SPRINGRATEINDEX;
   
   if((CurrentSetup.Actuator == AEF)||
	   (CurrentSetup.Actuator == AED)||
	   (CurrentSetup.Actuator == MICRO)) {                               /* and we have an encoder (AED or AEF)       */
      CurrentSetup.SpringRateTable[0] = ADForce;
    }
   else
      CurrentSetup.SpringRateTable[0] = DEF_HORNWEIGHTSB;
   
   SpringRateSlope = RATIOMETRICITY*(LCSENSITIVITY/PI)*
                             (((float)CurrentSetup.GainFactor/1000.0)/VOLTSPERBIT);

    if(CurrentSetup.Actuator == MICRO)
      SpringRateSlope *= SPRINGRATEMICRO; /* Multiply by nominal MICRO spring rate */
    else
      SpringRateSlope *= SPRINGRATE; /* Multiply by nominal spring rate */

   SpringRateSlope /= 10000.0; /* Adjust for 1/10000 units */

		/* Calculate Default Spring Rate Table. */
	   for(Index = 1; Index < SPRING_RATE_SIZE; Index++){
		  CurrentSetup.SpringRateTable[Index] = (UINT16)(SpringRateSlope*(FLOAT)Distance)
			  + CurrentSetup.SpringRateTable[0];
		  Distance += SPRINGRATEINDEX;
	   }
   
   UpdateCurrentPreset(SAVECURRENTSETUP,0,0);  /* save springrate to BBram */
}



void UpdateNVRSpringRate(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when a checksum is done or an upgrade is done    */
/*                                                                          */
/* Inputs : ADForce                                                         */
/*          CurrentSetup.GainFactor                                         */
/*                                                                          */
/* Outputs : NVR.CalHomeOffset                                              */
/*           NVR.DefCalHomeOffset                                           */
/*                                                                          */
/****************************************************************************/ 
{
   
   NVR.CalHomeOffset = ADForce;
   SetCalHomeOffset();
   NVR.DefCalHomeOffset = ADForce;
   SetDefCalHomeOffset();
   SpringRateSlope = RATIOMETRICITY*(LCSENSITIVITY/PI)*
                             (((float)CurrentSetup.GainFactor/1000.0)/VOLTSPERBIT);
   if(CurrentSetup.Actuator == MICRO){
      SetDefSpringRateSlope((UINT16)(SpringRateSlope * 1024.0 * SPRINGRATEMICRO));
      SetCalSpringRateSlope((UINT16)(SpringRateSlope * 1024.0 * SPRINGRATEMICRO));
   }
   else{
      SetDefSpringRateSlope((UINT16)(SpringRateSlope * 1024.0 * SPRINGRATE));
      SetCalSpringRateSlope((UINT16)(SpringRateSlope * 1024.0 * SPRINGRATE));
   }
}



void BuildPressureTable(void)
/****************************************************************************/ 
/*                                                                          */
/* Called from menu system after entering the third pressure value. It takes*/
/* takes the three pressure values and their corresponding A/D values and   */
/* builds a pressure table.                                                 */
/*                                                                          */
/* Inputs : UserPressure[] - 3 pressure sensor readings                     */
/*          AdCntsPSI[]    - 3 corresponding A/D readings                   */   
/*                                                                          */
/* Outputs: NVR.Pressure - update                                           */
/*          CalibrationPassed                                               */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Index, PressureAverage;
   FLOAT TBLStep;
   /* structure used by LinearReg function */
   struct Regression Reg;

   CalibrationPassed = CAL_PASSED;

      /* Get A/D average for 3rd A/D reading */
   PressureAverage = 0;
   for(Index=0; Index<CALBAVESIZE; Index++)
     PressureAverage += AvePressure[Index];           
   PressureAverage /= CALBAVESIZE;    /* divide by array length */

   AdCntsPSI[2] = (SINT32)PressureAverage;

      /* Get best fit to 3 pressure points */
   Reg = LinearReg(AdCntsPSI, UserPressure, 3);

      /* Build table to be used with processor's interpolation instructions. */
      /* This requires an x-axis table step of 256. */
   TBLStep = 0.0;
   for(Index = 0; Index < MAX_TABLE_PTS; Index++)
   {
      NVR.Pressure[Index] = (SINT16)(TBLStep*Reg.slope+Reg.intercept);
      TBLStep += 256.0;
   }      
      /* Set illegal for later verification */
   UserPressure[0] = UserPressure[1] = 0;
   VerifyPressureTable();
}


STR FailedByValue[QVGA_LINESIZE];

void VerifyPressureTable(void)
/****************************************************************************/ 
/*                                                                          */
/* Pressure table must be within +/- 2 PSI                                  */
/*                                                                          */
/* Inputs : HomePressure                                                    */
/*          UserPressure[2]                                                 */
/*          CurrentSetup.Units                                              */
/*                                                                          */
/* Outputs : CalibrationPassed                                              */
/*           PassFailStr                                                    */
/*           UserPressure[2]                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 ErrorValue, TensPlace;
   UINT8 TempVal;
   SINT8 TempStr[10];

   UpdateKeyMask(CALMODEMASK);
   if(CalibrationPassed != CAL_ABORTED)
   {
      if((HomePressure < (UserPressure[2] - PSI_RANGE)) ||
         (HomePressure > (UserPressure[2] + PSI_RANGE)))
      {
         CalibrationPassed = CAL_FAILED;
         if(HomePressure < UserPressure[2])
         {
            StrCpyTwoBytes(FailedByValue, "-");
            ErrorValue = UserPressure[2] - HomePressure;
         }
         else
         {
            StrCpyTwoBytes(FailedByValue, "+");
            ErrorValue = HomePressure - UserPressure[2];
         }
         if(CurrentSetup.Units == TRUE)      /* convert value to metric */
         {
            ErrorValue = (UINT16)((float)ErrorValue * KPA_CONVERT);
         }
         if(ErrorValue < 100)
         {
            StrCatTwoBytes(FailedByValue, " ");
            TempVal = 0x30 + (ErrorValue/10);
            SPrintf(TempStr, "%d", TempVal);
               StrCatTwoBytes(FailedByValue, TempStr);
         }
         else
         {
            if(ErrorValue > 999) ErrorValue = 999; /* there is only 2 places for the error */
               TensPlace = ErrorValue/100;
            TempVal = 0x30 + (ErrorValue / 100);
            SPrintf(TempStr, "%d", TempVal);
            StrCatTwoBytes(FailedByValue, TempStr);
            TempVal = 0x30 + ((ErrorValue - (TensPlace * 100)) / 10);

            SPrintf(TempStr, "%d", TempVal);
            StrCatTwoBytes(FailedByValue, TempStr);
         }
         if(CurrentSetup.Units == TRUE)      /* convert value to metric */
         {
            StrCatTwoBytes(FailedByValue, "k");
            StrCatTwoBytes(FailedByValue, "p");
            StrCatTwoBytes(FailedByValue, "a");
         }
         else
         {
            StrCatTwoBytes(FailedByValue, "P");
            StrCatTwoBytes(FailedByValue, "S");
            StrCatTwoBytes(FailedByValue, "I");
         }
      }   
      else
      {
		   CalibrationPassed = CAL_PASSED;   /* continue to loadcell calibration */
         CurrentSetup.SpringRateTable[0] = ADForce; /* save the loadcell reading */
         NVR.CalHomeOffset = ADForce;
      }
      UserPressure[2] = 0;    /* Set illegal for later verification        */
      DisplayNextScreen();

   }
   StrCatTwoBytes(FailedByValue, '\0');
}



void BuildVelocityTable(void)
/****************************************************************************/ 
/*                                                                          */
/* This function updates the velocity table with default values. It is      */
/* called from MFG25 and the BUC menu factory default setting               */
/*                                                                          */
/* Inputs : NVR.CylSize                                                     */
/*                                                                          */
/* Outputs : CurrentSetup.VelocityTable                                     */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   if(NVR.CylSize == SIZE3_0)
   {
      CurrentSetup.VelocityTable[0] = Velocity60PSI3in[0];
      CurrentSetup.VelocityTable[1] = Velocity60PSI3in[1];
   }
   else /* use 2in table for all other cylinder sizes for Ver 7 */
   {
      CurrentSetup.VelocityTable[0] = Velocity60PSI2in[0];
      CurrentSetup.VelocityTable[1] = Velocity60PSI2in[1];
   }

}

void VGABuildForceTable(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when the third force value is entered. It is     */
/* called from within the menu task. It takes the three actual force values */
/* and three corresponding A/D values and builds a table.                   */
/*                                                                          */
/* Inputs : NVR.LoadCell                                                    */
/*          ForceV[]                                                        */
/*          AdCntsLC[]                                                      */
/*                                                                          */
/* Outputs : NoPressureFlag                                                 */
/*           CalibrationPassed                                              */
/*           NVR.LoadCell                                                   */
/*           ForceV[]                                                       */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
UINT16 DateArray[3]; // 3 Words Calibration date: 04 13 1967
UINT16 NumberOfLoadCellPoints;
FLOAT  TBLStep;
UINT16 Index;
SINT32 LoadCellAverage;
struct Regression Reg;
RTC RTCCal;

   if(CalibrationPassed != CAL_ABORTED)
   {
      UpdateKeyMask(CALMODEMASK);
      ReadA2D2(0);
      CalibrationPassed = CAL_PASSED;

      if ((CurrentSetup.Actuator==AED)||
		  (CurrentSetup.Actuator == MICRO))
         NumberOfLoadCellPoints = 2;
      else 
         NumberOfLoadCellPoints = 3;
         
      /* Get best fit to 3 force values */
      Reg = LinearReg(AdCntsLC, ForceV, NumberOfLoadCellPoints);

      /* Build table to be used with processor's interpolation instructions. */
      /* This requires an x-axis table step of 256. */
      TBLStep = 0.0;
      for(Index=0; Index<MAX_CAL_PTS; Index++)
         {
            /* added offset to the loadcell table */
            NVR.LoadCell[Index] = (SINT16)(TBLStep*Reg.slope +(SINT16)Reg.intercept) + LoadCellOffset;
            TBLStep += 256.0;
         }

      /* Interpolate force values for collected D-to-A values */
      for(Index=0; Index<MAX_CAL_PTS; Index++)      
         /* do not have offset in when generating the PV table */
         ForceV[Index] = (GetInterpolatedSINT16(NVR.LoadCell, ForceVcnts[Index]) - LoadCellOffset);
      NoPressureFlag = TRUE;
      
      if(CurrentSetup.Actuator == AEF)
         BuildPVPTable();         
      for(Index=0; Index<MAX_VECTOR_SIZE; Index++)
         ForceV[Index] = 0;

      /* need to update the calibrated pressure and stroke length */
      NVR.CalSysPressure = TemporaryCalSysPressure;
      NVR.CalStrokeLen = TemporaryCalStrokeLen;
      /* need to clear the horn weight offset */
      CurrentSetup.HornWeightOffset = 0;
      SVOff();
      UpdateCurrentPreset(SAVECURRENTSETUP, 0, 0);
      WeldMsgOut.common.opcode = OP_NVM_WRITE_PARAMETERS;  /* update to actnvram */
      CkQSend (SysmQueueId,&WeldMsgOut,WELD_MGR,
            __LINE__,MILLS_TO_TICKS(20));      /* 20 ms        */
      RTCCal = RtcReadDateandTime();     /* Get date when calibration complete */
      DateArray[0] = RTCCal.Month;
      DateArray[1] = RTCCal.Day;
      DateArray[2] = RTCCal.Year;
      SetCalibrationDate(DateArray);     
      SetCalibPass((UINT16) CALIBPASSED);
   }  
}

void SaveCalibPressure(void){
/****************************************************************************/ 
/*                                                                          */
/* This function is called from CalForceMenu5B. It will save the averaged   */
/* pressure at home.                                                        */
/*                                                                          */
/* Inputs :                                                                 */
/*                                                                          */
/* Outputs : TemporaryCalSysPressure                                        */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 

   UINT16 PressureAverage,Index;
   
   PressureAverage = 0;
   for(Index=0; Index<CALBAVESIZE; Index++)
      PressureAverage += AvePressure[Index];           
   PressureAverage /= CALBAVESIZE;    /* divide by array length */

   TemporaryCalSysPressure = GetInterpolatedSINT16(NVR.Pressure,PressureAverage);
}


void BuildPVPTable(void)
/**********************************************************************************/
/* Build NVR.Force interpolation table, which gives D-to-A values when indexed by */
/* pounds.                                                                        */
/**********************************************************************************/
{
UINT16 Index;
FLOAT  TBLStep;
struct Regression Reg;
   
   /* Get best fit to 9 data points collected */
   Reg = LinearReg(ForceV,PVDacCnts, 9);

   /* Build table to be used with processor's interpolation instructions. */
   /* This requires an x-axis table step of 256. */
   TBLStep = 0.0;
   for(Index=0; Index< FORCE_TABLE_SIZE; Index++)
   {
      NVR.Force[Index] = (SINT32)(TBLStep*(Reg.slope*10.0)+Reg.intercept);
      TBLStep += 256.0;
   }
}


void CalibFinalCleanup(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when calibration is complete or aborted. It will */
/* either restore the old values on a fail or abort condition. Or it if     */
/* passes update the calibration tables.                                    */
/*                                                                          */
/* Inputs : CalibrationPassed                                               */
/*          TempSpringRateTable                                             */
/*          TempPressureTable                                               */
/*          TempLoadCellTable                                               */
/*          TempForceTable                                                  */
/*          TempTriggerForce                                                */
/*          MainKeyFlag                                                     */
/*                                                                          */
/* Outputs : DateArray                                                      */
/*           CurrentSetup.SpringRateTable                                   */
/*           NVR.Pressure                                                   */
/*           NVR.LoadCell                                                   */
/*           NVR.Force                                                      */
/*           CalibrationPassed                                              */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Index;
   UINT16 DateArray[3]; // 3 Words Calibration date: 04 13 1967
   RTC RTCCal;

   if(CalibrationPassed != CAL_NOT_ALLOWED)
   {
      SVOff();                            /* Turn off SV to bring hown up      */
      RunningPreset.TriggerForce = TempTriggerForce;
      SelectWeldSequence();               /* Restore proper weld sequence*/
      StartStateMachine();
      if(CalibrationPassed == CAL_PASSED)
      {
         ClearCalibrationAlarms();           /* Clear any Calibration alarms      */ 
         SetReady();
      }
      else if(CalibrationPassed == CAL_ABORTED) {    /* restore calibration tables */
         for(Index = 0; Index < SPRING_RATE_SIZE; Index++)
         {
            CurrentSetup.SpringRateTable[Index] = TempSpringRateTable[Index];
         }
         for(Index = 0; Index < MAX_TABLE_PTS; Index++){
            NVR.Pressure[Index] = TempPressureTable[Index];
         }
         for(Index = 0; Index < MAX_TABLE_PTS; Index++){
            NVR.LoadCell[Index] = TempLoadCellTable[Index];
         }
         for(Index = 0; Index < FORCE_TABLE_SIZE; Index++){
            NVR.Force[Index] = TempForceTable[Index];
         }
      }
      else { /* Load defaults when calibration fails */
         RTCCal = RtcReadDateandTime();     /* Get date when calibration complete */
         DateArray[0] = RTCCal.Month;
         DateArray[1] = RTCCal.Day;
         DateArray[2] = RTCCal.Year;

         SetCalibrationDate(DateArray);     
         SetCalibPass((UINT16) CALIBFAILED);
         GetDefPressure();
         GetDefLoadCell();
         GetDefForce();
      }
     
      /*before throwing main key check calibration by VFD */
      if(MainKeyFlag == FALSE && QVGASnsrCalibAllowed == FALSE)
      {
         SendFakeKeyPress(MainKey);
      }
      CalibrationPassed = CAL_NOT_ALLOWED;
   }
   QVGASnsrCalibAllowed = FALSE;
}



void UpdateSpringRate(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called after triggerring in sensor cal or act. cal.     */
/* The strokelength must be greater then 0.8in to detect a heavy horn.      */
/*                                                                          */
/* Inputs : EncoderPos                                                      */
/*          DistanceV                                                       */
/*          ForceV                                                          */
/*          NVR.PSVersion - contains the last spring rate slope. This is    */
/*            used for Non Version 6 Cal actuator upgrade. It is also used  */
/*            when the calibration stroke length is less than one inch.     */
/*                                                                          */
/* Outputs : CurrentSetup.SpringRateTable                                   */
/*           SpringRateSlope - This is saved to the novram after a          */
/*              successful sensor calibration and during a Version 6 upgrade*/
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 LastIndex, Index, StartIndex,CompensatedIndex;
   UINT32 Distance = 0;
   struct Regression Reg;
   float GainRatio;
   UINT16 HornWeightCorrection = FALSE;
   UINT16 LeavingHomeForce;
   UINT16 ActuatorFreqIndex;
      
   if(CurrentSetup.Actuator == MICRO)
//      LeavingHomeForce = LEAVINGHOMEFORCEMICRO;
      LeavingHomeForce = MicroHomeForce;
   else{
      switch (CurrentSetup.PSFreq) {
         default:
         case FREQ20KHZ:
         case FREQ40KHZ:
         case FREQ30KHZ:
         case FREQ60KHZ:
            LeavingHomeForce = LEAVINGHOMEFORCE;
         break;

         case FREQ15KHZ:
            LeavingHomeForce = LEAVINGHOMEFORCE15KHZ;
         break;
      }
   }   

   /* convert SpringRateSlope to a FLOAT incase the stroke was not long enough or */
   /* a cal actuator is performed to update for a new horn weight                 */
   SpringRateSlope = (float)NVR.SpringRateSlope / 1024.0;
   SpringRateSlope /= 10000.0; /* Adjust for 1/10000 units */

   /* Go back one point from part contact */
   if(TemporaryCalStrokeLen > SPRINGRATEINDEX)
      LastIndex = (TemporaryCalStrokeLen/ SPRINGRATEINDEX) -1;
   else
      LastIndex = 0;

   if(LastIndex <= 3)
      /* There is not enough stroke to check for a heavy horn. */
      HornWeightCorrection = TRUE;
      
   GainRatio = (float)GAIN_FACTOR_DEFAULT / (float)CurrentSetup.GainFactor;

   /* need to correct the distance and force tables when a heavy horn is used for calibration */
   StartIndex = 0;
   for(Index=0; Index < (LastIndex +1); Index++)
   {
      if((ForceV[Index + 1] - ForceV[Index]) > GREATERTHENNOISE)
      {
         StartIndex = Index;
         Index = (LastIndex + 1); /* exit the for loop */
      }
   }         
   LastIndex -= StartIndex;
   CompensatedIndex = StartIndex;
   
   for(Index=0; Index < (LastIndex + 1); Index++)
   {
      ForceV[Index] = ForceV[CompensatedIndex];
      DistanceV[Index] = DistanceV[CompensatedIndex++];
   }     
         
   Reg = LinearReg(DistanceV, ForceV, LastIndex);
 
   
   /* Use defaults if stroke length < 1 inch. */
   if(TemporaryCalStrokeLen > ONE_INCH){
      /* Only update springrate slope during a sensor calibration */ 
      /* or when Cal Actuator is run on a Version 6 Actuator */
      if((CurrentSequence == CALIBRATION) || 
      ((AtLeastVersion806() == FALSE) &&  ((ErrorCode == ERRORCODE1100_EQ20) || (ErrorCode == ERRORCODE1200_EQ20))))
         SpringRateSlope = Reg.slope;
   }
   
   if((LastIndex < 3) || (CurrentSequence == SC))
   {

      /*  Use the default table except for CurrentSetup.SpringRateTable[0]  */
      /*  CurrentSetup.SpringRateTable[0] contains the load cell bias read  */
      /*  at the home position of the actuator. Do not update if hornweight */
      /*  can not be detected.                                              */
   
      for(Index = 1; Index < SPRING_RATE_SIZE; Index++)
      {   
         Distance = Distance + SPRINGRATEINDEX;
         CurrentSetup.SpringRateTable[Index] = CurrentSetup.SpringRateTable[0]
          + LeavingHomeForce + (SpringRateSlope*Distance);
      }   
   }  
   
   if(CurrentSequence == CALIBRATION)
   {
      for(Index = 1; Index < SPRING_RATE_SIZE; Index++)		 
      {
         Distance = Distance + SPRINGRATEINDEX;
            CurrentSetup.SpringRateTable[Index] = CurrentSetup.SpringRateTable[0]
              + (UINT16)(SpringRateSlope *(FLOAT)Distance) + LeavingHomeForce;
         /* need to compensate for heavy horns */
         if(NVR.ForceGauge == LOAD_CELL){ 
            if((ForceV[Index] >= CurrentSetup.SpringRateTable[0] + LeavingHomeForce) || (HornWeightCorrection == TRUE))
            {
              HornWeightCorrection = TRUE;
            }
            else
            {
               CurrentSetup.HornWeightOffset = (SINT16)((float)(ForceV[Index] - NVR.CalHomeOffset)
                     * LBSPERCNT * GainRatio);
               CurrentSetup.HornWeightOffset -= Index;       /* pound increments */
            }
		 }
      }
   }  
   ForceV[0] = 0;       /* Set to zero so they will show up as zero lbs */
   ForceV[1] = 0;       /* on the user menus                            */
   ForceV[2] = 0;  
   
}




void InitForce1(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   InitCalWait();              /* Initialize the Calibration wait timer flag*/
}



void InitForce2(void)
/****************************************************************************/ 
/* Set the PV Control signal to 7.74% above the minimum and stage to        */
/* FORCE_CALIBRATION.  The force range is from 13.8ma to 0 ma which = 45220 */
/* to 0.  Note that the PV control signal works in reverse, so 7.74% "above"*/
/* the minimum is 45220 less 7.74%.  This function is executed on entry to  */
/* the CalWaitTime1 state.                                                  */
/****************************************************************************/
{   
   PVControlSignal = PVSTART;
   if(RampPV.CurrentValue < RampPV.CurrentValue) /* Do not want to decrease force */
      PVControlSignal = RampPV.CurrentValue;     /* during calibration */
   SetPV(PVControlSignal,FORCE_CALIBRATION);
   PlsWaitTimerFlag = TRUE;
}



void InitForce3(void)
/****************************************************************************/ 
/* Set the PV Control signal to 12.26% above the previous value and the     */       
/* stage to FORCE_CALIBRATION.  Start a 2 sec timer for collection of force */
/* data in the CollectForceData subroutine.  This function is executed on   */
/* entry to the CalWaitTime2 state.                                         */
/****************************************************************************/ 
{
   PVControlSignal -= PVADJUST1;
   if(RampPV.CurrentValue < RampPV.CurrentValue) /* Do not want to decrease force */
      PVControlSignal = RampPV.CurrentValue;     /* during calibration */
   SetPV(PVControlSignal,FORCE_CALIBRATION);
   InitCalWait();              /* Initialize the Calibration wait timer flag*/
   /* Initiate variable delay.  This is a patch for testing various delays. */
   CollectForceDataDelay = LC_DELAY;
}



void DisplayNextScreen(void)
/****************************************************************************/
/* This function is called to force the display of the next screen in       */
/* calibration.                                                             */
/****************************************************************************/
{
   calbmsg.common.opcode = OP_WELDER_STATE_CHANGE;
   calbmsg.common.source_task = WC_ISR_TASK;
   calbmsg.state = TRIGGEREDSTATE;
   q_send(WmgrQid,&calbmsg);
}



void CollectForceData(void)
/****************************************************************************/
/* This function is called by the state machine each pass through the       */
/* CalWaitTime2 state.                                                      */
/****************************************************************************/
{
UINT16 Index;
SINT32 LoadCellAverage;

   ReadLoadCell(); /* Get average load cell A-to-D reading */
   /* wait for operator data input */
   if(!CollectForceDataDelay) return;
     
      /* Wait 2 seconds to collect data */
      if(!(--CollectForceDataDelay))
      {
         LoadCellAverage = 0;
         for(Index=0; Index<CALBAVESIZE; Index++)
            LoadCellAverage += CalbAve[Index];           
         LoadCellAverage /= CALBAVESIZE;    /* divide by array length */

         PVDacCnts[CollectForceDataIndex] = PVControlSignal;
         ForceVcnts[CollectForceDataIndex++] = LoadCellAverage;

         PVControlSignal -= PVADJUST2;   /* Increase force by 10% */
         if(RampPV.CurrentValue < RampPV.CurrentValue) /* Do not want to decrease force */
            PVControlSignal = RampPV.CurrentValue;     /* during calibration */
         SetPV(PVControlSignal,FORCE_CALIBRATION);

         if(CollectForceDataIndex == 4 || CollectForceDataIndex == 8)
            /* force screen to advance */
            DisplayNextScreen();
         else
            /* Initiate variable delay.  This is a patch for testing various delays. */
            CollectForceDataDelay = LC_DELAY;
      }
      
}



void CheckSpringRate(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   /* check for no movement */
   UpdateDownSpeed();
   if((PartContactFlag == FALSE) || (CurrentForce < FORCE_ON_THE_PART))
   {
      if(EncoderPos > ONE_POSITION)
      {
         ForceV[(UINT16) (EncoderPos/ SPRINGRATEINDEX) - 1] = ADForce;
         DistanceV[(UINT16) (EncoderPos/ SPRINGRATEINDEX) - 1] = EncoderPos;
      }   
   }   
   else
   {
      TemporaryCalStrokeLen = EncoderPos;
      InitForce1();
      UpdateSpringRate();
      SpringRateComplete = TRUE;
      NoPressureFlag = FALSE; 
      UpdateKeyMask(CALMODEMASK);
   }
}                            



void UpdateDownSpeed(void)
/****************************************************************************/ 
/*                                                                          */
/* check for no movement                                                    */                                             
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   if(CheckDownSpeed++ == DOWNSPEEDTIMEOUT)
   {
      CheckDownSpeed = 0;
      if((SpringRateComplete == FALSE) && (CurrentVelocity < MINDOWNSPEED))
      {
         SetPV((UINT16)(CAL_DOWNSPEED+ DownSpeedIncrement++),HOME_TO_DWNSPD); 
         if(DownSpeedIncrement > MAXDOWNSPEED) DownSpeedIncrement = MAXDOWNSPEED;  
      }
   }   
}



void TestTimer(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{

   UINT16 Index;
   FP_KEY_PRESSED_MSG  FPKeyMsg;
   
   if(Inp.BothPB == FALSE)
   {
      SVOff();                            /* Turn off SV to bring hown up      */

      CalibrationPassed = CAL_ABORTED;
      SendFakeKeyPress(CALIBRATION_ABORTED);
      /* If VGA H/W is available send Message to the VGA queue*/
      if(IsHWConfigured(VGA))
      {
         FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
         FPKeyMsg.key = CALIBRATION_ABORTED;                        
         CkQSend (RvtsQid, &FPKeyMsg, SYS_MANAGER,
                 __LINE__, MILLS_TO_TICKS(20));   /* 20 ms        */
      }     

/* Put state machine back */
      for(Index = 0; Index < SPRING_RATE_SIZE; Index++)
      {
         CurrentSetup.SpringRateTable[Index] = TempSpringRateTable[Index];
      }
      for(Index = 0; Index < MAX_TABLE_PTS; Index++)
      {
         NVR.Pressure[Index] = TempPressureTable[Index];
      }
      for(Index = 0; Index < MAX_TABLE_PTS; Index++)
      {
         NVR.LoadCell[Index] = TempLoadCellTable[Index];
      }
      for(Index = 0; Index < FORCE_TABLE_SIZE; Index++){
         NVR.Force[Index] = TempForceTable[Index];
      }
      PlsWaitTimerFlag = FALSE;   /* Advances the state machine */
   }
    /* check for no movement */
   UpdateDownSpeed();
   CurrentVelocity = VelocityEstimator(EncoderPos);
   if(Inp.uls == FALSE)
   {
      if(SpringRateComplete == FALSE) 
      {
         CheckSpringRate();
      }
      else 
      {
         if(TimerLoopCounter-- <= 0)
         {
            PlsWaitTimerFlag = FALSE;   /* Advances the state machine */
            TriggerBeep();
         }
         if(TimerLoopCounter < 400)
         {
            if(UpdateCalbAve++ > 3)
            {
               UpdateCalbAve = 0;
               CalbAve[CalbAveIndex++] = LoadCellIndex;
               if(CalbAveIndex >= CALBAVESIZE)
                  CalbAveIndex = 0;
            }
         }
      }
   }    
   else
   {
      ZeroEncoder();
   }
}



void ReadLoadCell(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{

   if(NoPressureFlag == FALSE)
      CheckForNoPressure();
   if(UpdateCalbAve++ > 3){
      UpdateCalbAve = 0;
      AvePressure[CalbAveIndex] = ADPressure;
      CalbAve[CalbAveIndex++] = LoadCellIndex;
      if(CalbAveIndex >= CALBAVESIZE)
      {
         CalbAveIndex = 0;
      }
   }
}



void ExitCalWait(void)
/****************************************************************************/
/*                                                                          */
/*  CalTimerFlag is used to sync the menu with the state machine.  When the */
/*  state machine times out, CalTimerFlag is set to TRUE.  This is what the */
/*  menu system is waiting for to proceed with the next menu.               */
/*                                                                          */
/****************************************************************************/
{
   CalTimerFlag = TRUE;        /* Initialize timer flag here                */
}



void InitCalWait(void)
/****************************************************************************/
/*                                                                          */
/*  CalTimerFlag is used to sync the menu with the state machine.  When the */
/*  state machine times out, CalTimerFlag is set to TRUE.  This is what the */
/*  menu system is waiting for to proceed with the next menu.  The CalTimer */
/*  Flag is cleared here.                                                   */
/*                                                                          */
/****************************************************************************/
{
   PlsWaitTimerFlag = TRUE;
   CalTimerFlag = FALSE;       /* Initialize timer flag here                */
}



void InitCalTimer(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/* 02jun99: Separated AED & AEF code - cmc                                  */
/****************************************************************************/ 
{
   if(CalibrationPassed == CAL_PASSED)
   {
      CalTimer = CALIBRATION_TIMER;/* Initialize the calibration timer */
      CalbAveIndex = 0;
      UpdateCalbAve = 5;
      PlsWaitTimerFlag = TRUE;    /* Please Wait Timer Flag */
   }
   PlsWaitTimerFlag = FALSE;      /* Advance statemachine*/
   InitCalWait();
}


void SBCReadA2D3(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 PressureAverage,Index;
   
   PressureAverage = 0;
   for(Index=0; Index<CALBAVESIZE; Index++)
      PressureAverage += AvePressure[Index];           
   PressureAverage /= CALBAVESIZE;   /* divide by array length */

   AdCntsPSI[0] = (SINT32)PressureAverage;

}

void SBCReadA2D4(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 PressureAverage,Index;
   
   PressureAverage = 0;
   for(Index=0; Index<CALBAVESIZE; Index++)
      PressureAverage += AvePressure[Index];           
   PressureAverage /= CALBAVESIZE;       /* divide by array length */

   AdCntsPSI[1] = (SINT32)PressureAverage;
}

void SBCReadA2D1(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
UINT16 Index;
SINT32 LoadCellAverage;

   UpdateKeyMask(CALMODEMASK);
   LoadCellAverage = 0;
   CollectForceDataIndex = 1;
   for(Index=0; Index<CALBAVESIZE; Index++)
      LoadCellAverage += CalbAve[Index];           
   LoadCellAverage /= CALBAVESIZE;    /* divide by array length */

   AdCntsLC[0] = LoadCellAverage;
   ForceVcnts[0] = LoadCellAverage;
   PVDacCnts[0] = PVControlSignal;

   PlsWaitTimerFlag = FALSE;      /* Advance statemachine*/
}

void SBCReadA2DLC2(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
UINT16 Index;
SINT32 LoadCellAverage;

   UpdateKeyMask(CALMODEMASK);
   LoadCellAverage = 0;

   for(Index=0; Index<CALBAVESIZE; Index++)
      LoadCellAverage += CalbAve[Index];           
   LoadCellAverage /= CALBAVESIZE;    /* divide by array length */

   AdCntsLC[1] = LoadCellAverage;
   ForceVcnts[4] = LoadCellAverage;
   PVDacCnts[4] = PVControlSignal;
   CollectForceDataIndex++;
   PlsWaitTimerFlag = FALSE;      /* Advance statemachine*/
   if ((CurrentSetup.Actuator == AED)||
	   (CurrentSetup.Actuator == MICRO))
      VGABuildForceTable();
}


void ReadA2D2(UINT32 MenuExtra)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
UINT16 Index;
SINT32 LoadCellAverage;

   UpdateKeyMask(CALMODEMASK);
   LoadCellAverage = 0;

   for(Index=0; Index<CALBAVESIZE; Index++)
      LoadCellAverage += CalbAve[Index];           
   LoadCellAverage /= CALBAVESIZE;     /* divide by array length */

   AdCntsLC[2] = LoadCellAverage;
   ForceVcnts[8] = LoadCellAverage;
   PVDacCnts[8] = PVControlSignal;
   PlsWaitTimerFlag = FALSE;      /* Advance statemachine*/
}



void CheckForNoPressure(void)
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/* Outputs :                                                                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 Index;
   FP_KEY_PRESSED_MSG  FPKeyMsg;

   if((EncoderPos < (TemporaryCalStrokeLen - OFF_THE_PART)) &&
      (NoPressureFlag == FALSE))
   {
      NoPressureFlag = TRUE; 
      CalibrationPassed = CAL_ABORTED;

      SVOff();                            /* Turn off SV to bring hown up      */
      SendFakeKeyPress(CALIBRATION_ABORTED);
      /* If QVGA H/W is available send Message to the QVGA queue*/
      if(QVGAHwAvail)
      {
         FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
         FPKeyMsg.key = CALIBRATION_ABORTED;                        
         CkQSend (QvgaQid, &FPKeyMsg, SYS_MANAGER,
                 __LINE__, MILLS_TO_TICKS(20));   /* 20 ms        */
      }       

/* Put state machine back */
      for(Index = 0; Index < SPRING_RATE_SIZE; Index++)
      {
         CurrentSetup.SpringRateTable[Index] = TempSpringRateTable[Index];
      }
      for(Index = 0; Index < MAX_TABLE_PTS; Index++){
         NVR.Pressure[Index] = TempPressureTable[Index];
      }
      for(Index = 0; Index < MAX_TABLE_PTS; Index++){
         NVR.LoadCell[Index] = TempLoadCellTable[Index];
      }
      for(Index = 0; Index < FORCE_TABLE_SIZE; Index++){
         NVR.Force[Index] = TempForceTable[Index];
      }
   }
}



void CalExitPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when both palm buttons have */
/*  been pressed in the calibration weld sequence.  
/*                                                                         */
/***************************************************************************/
{
   
   SetPV(CAL_DOWNSPEED,HOME_TO_DWNSPD);   
   EnableSVOn();                        /* Enable SV valve                 */
   SVOn();                              /* Turn on SV to bring down hown   */
   ZeroEncoder();
}



void SelectSensorCalSequence(void)
/***************************************************************************/
/*                                                                         */
/* This is the Sensor Calibration state sequence.                          */
/*                                                                         */
/* Caveats : Must make sure to update menusync states when submenues are added*/
/* or deleted.                                                             */
/*                                                                         */
/***************************************************************************/
{
   UINT16 i = 0, SaveStateMachineFlag;

   ResetStateMachine();                /* Turn off the state machine first */
   SaveStateMachineFlag = SetStateMachineFlag(FALSE);

   if((CurrentSetup.Actuator == AED)||(CurrentSetup.Actuator == MICRO))
   {
   WeldSequence[i++] = &CalTopOfList;     /* enter the sequence of states */

   /* CalForceMenu1 wait for next menu to be displayed */
                                       /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Set Regulator For    */
                                       /* Reading of 10 psi    */
                                       /*             Continue */
                                       /*----------------------*/
   WeldSequence[i++] = &MenuSyncST;
   /* CalForceMenu2 wait for next menu to be displayed */
                                       /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Enter Gauge Reading  */
                                       /*                = xxx */
                                       /*             Continue */
                                       /*----------------------*/

   WeldSequence[i++] = &MenuSyncST;    
   /* CalForceMenu3 wait for next menu to be displayed */
                                       /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Set Regulator For    */
                                       /* Reading of 50 psi    */
                                       /*             Continue */
                                       /*----------------------*/

   WeldSequence[i++] = &MenuSyncST;    
   /* CalForceMenu4 wait for next menu to be displayed */
                                       /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Enter Gauge Reading  */
                                       /*                = xxx */
                                       /* ____________Continue */
                                       /*----------------------*/

   WeldSequence[i++] = &MenuSyncST;
   /* CalForceMenu5 wait for next menu to be displayed */

                                       /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Set Regulator to     */
                                       /* 20 PSI(138kPA)       */
                                       /* ____________Continue */
                                       /*----------------------*/
   WeldSequence[i++] = &MenuSyncST;
   /* CalForceMenu5A wait for next menu to be displayed */

                                       /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Enter Gauge Reading  */
                                       /*                = xxx */
                                       /*                      */
                                       /*----------------------*/

   WeldSequence[i++] = &MenuSyncST;
   /* CalForceMenu6Suc wait for next menu to be displayed */
                                       
                                       /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Position Load Cell   */
                                       /*                      */
                                       /*             Continue */
                                       /*----------------------*/

   WeldSequence[i++] = &MenuSyncST;
   /* CalForceMenu7A wait for next menu to be displayed */
                                       
                                       /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Set to 5PSI(35kpa)   */
                                       /*                      */
                                       /*             Continue */
                                       /*----------------------*/
   WeldSequence[i++] = &MenuSyncST;
   /* CalForceMenu7B wait for beep */


                                       /*----------------------*/
   WeldSequence[i++] = &CalPBState2;   /* CAL SENSORS          */
   WeldSequence[i++] = &CalWaitUls;    /* Set 35PSI(107kpa)    */
   WeldSequence[i++] = &CalWaitTrsST;  /* Press Start Switches */
// needed to advance the menu          /* Until Beep is Heard  */
   WeldSequence[i++] = &CalTriggerST;  /*----------------------*/
                                       

   WeldSequence[i++] = &MenuSyncST;
   /* CalForceMenu8 wait for next menu to be displayed */
   /* need 1st force applied here and wait for Enter key flag */
   WeldSequence[i++] = &CalWaitTime1;  /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Enter Load Cell      */
                                       /* Reading        = xxx */
                                       /* ____________Continue */
                                       /*----------------------*/

   WeldSequence[i++] = &MenuSyncST;
   /* CalForceMenu9A wait for timeout here */
   /* need 2nd force applied here and wait for Enter key flag */
   WeldSequence[i++] = &CalWaitTime1;  /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Set Regulator to     */
                                       /* 50PSI(345kpa)        */
                                       /*             Continue */
                                       /*----------------------*/

   WeldSequence[i++] = &MenuSyncST;
   /* CalForceMenu10 wait for next menu to be displayed */
                                       /*----------------------*/
                                       /* CAL SENSORS          */
                                       /* Reenter Load Cell    */
                                       /* Reading        = xxx */
                                       /* ____________Continue */
                                       /*----------------------*/
   WeldSequence[i++] = &CalWaitTime2;
                                       /*----------------------*/  /*----------------------*/
                                       /* CAL SENSORS          */  /* CAL SENSORS          */
                                       /* Calibration Failed   */  /* Calibration          */
                                       /* See Manual Section   */  /* Successful           */
                                       /* X-YY.       Continue */  /* ____________Continue */
                                       /*----------------------*/  /*----------------------*/

   /* End of Calibration sequence */
   WeldSequence[i]   = &CalEndOfList;
   }
   else   /* Put in AEF sequence */
   {
      WeldSequence[i++] = &CalTopOfList;

      /* Wait for CalForceMenu2 to be displayed */
      WeldSequence[i++] = &MenuSyncST;    

      /* Wait for CalForceMenu3 to be displayed */
      WeldSequence[i++] = &MenuSyncST;    

      /* Wait for CalForceMenu4 to be displayed */
      WeldSequence[i++] = &MenuSyncST;

      /* Wait for CalForceMenu5 to be displayed */
      WeldSequence[i++] = &MenuSyncST;

      /* Wait for CalForceMenu5A to be displayed */
      WeldSequence[i++] = &MenuSyncST;

      /* Wait for CalForceMenu5B to be displayed */
      WeldSequence[i++] = &MenuSyncST;

      /* Wait for CalForceMenu6Suc to be displayed */
      WeldSequence[i++] = &MenuSyncST;

      /* Wait for CalForceMenu7B to be displayed */
      WeldSequence[i++] = &MenuSyncST;
      
      /* Wait for palm buttons to be pressed */
      WeldSequence[i++] = &CalPBState2;  

      /* Wait for upper limit switch to be cleared */
      WeldSequence[i++] = &CalWaitUls; 

      /* Wait for part contact */
      WeldSequence[i++] = &CalWaitTrsST;

      /* Generate beep and advance to CalForceMenu8 */      
      WeldSequence[i++] = &CalTriggerST; 

      /* Wait for CalForceMenu8; advance to CalWaitTime1 when this menu is displayed */ 
      WeldSequence[i++] = &MenuSyncST;

      /* Increase PV force by 7.74% and read load cell for correlation with 1st */
      /* operator-entered value, entered through CalForceMenu8 above after the  */
      /* initiation of the CalWaitTime1 state.                                  */
      WeldSequence[i++] = &CalWaitTime1;

      /* Wait for CalForceMenu9AEF to be displayed */
      WeldSequence[i++] = &MenuSyncST;

      /* Increase PV force by 12.26%, and then in 10% increments until force is at */
      /* 50% level.  Read load cell 2 seconds after each increment.  Advance menu  */
      /* to CalForceMenu10AEF when at 50% level and continue to read load cell     */
      /* until operator responds with the 2nd reading of force in pounds.  When the*/
      /* operator responds the menu is advanced to CalForceMenu11AEF and the state */
      /* machine is advanced to the next instance of CalWaitTime2 below.           */
      WeldSequence[i++] = &CalWaitTime2; 
      
      /* Increase PV force be 12.26%, and then in 10% increments until force is at */
      /* 92.26% level.  Read load cell 2 seconds after each increment.  Advance    */
      /* menu to CalForceMenu12 when at 92.26% level and continue to read load cell*/
      /* until operator responds with the 3rd reading of force in pounds.  When the*/
      /* operator responds new tables are computed and the calibration is saved.   */
      WeldSequence[i++] = &CalWaitTime2; 

      /* Wait for CalForceMenu12AEF to be displayed */
      WeldSequence[i++] = &MenuSyncST;
      
      /* End of Calibration sequence */
      WeldSequence[i]   = &CalEndOfList;
   }

   CurrentSequence = CALIBRATION;
   SetStateMachineFlag(SaveStateMachineFlag);

   UpdateKeyMask(CALMODEMASK);
   StopDataCollection();                /* Stop the weld data collection */

   ClearAbort();                        
   StartStateMachine();                 /* Start the state machine here     */
}




UINT16 CalibrationAllowed(void)
{
   UINT16 Allowed = FALSE;

   if(((WeldState == READYSTATE) || (WeldState == PREREADYSTATE))&&
     (CurrentSequence == WELD))
   {
      if((Inp.OnePB == FALSE) &&
        ((WeldingResults.EquipmentFailureAlarms & NOVRAMFAILED) == 0) &&
        (Inp.uls == TRUE) && (Inp.DoorOpen == FALSE))
        Allowed = TRUE;
   }
   return(Allowed);
 
}



void ShowCalibrationAbort(void)
{
   CalibrationPassed = CAL_NOT_ALLOWED;
   SetReady();
   SelectWeldSequence();               /* Restore proper weld sequence      */
   StartStateMachine();
   tm_wkafter( MS_TO_TICKS( 3000));
   if(MainKeyFlag == FALSE)
   {
      SendFakeKeyPress(GoBackKey);
      SendFakeKeyPress(MainKey);
   }
}




struct Regression LinearReg(SINT32* x, SINT32* y, UINT16 n)
/****************************************************************************/
/* LinearReg returns the slope of the best least squares fit.  x is the     */
/* independent variable and y is the dependent variable.  The slope is delta*/
/* y/delta x.                                                               */
/****************************************************************************/
{
FLOAT  Sxy=0.0, Sx2=0.0;
FLOAT  Mx=0.0, My=0.0;
FLOAT  xn, error, error2;
SINT32 *xsav, *ysav;
struct Regression Reg;
UINT16 Index;

   xsav = x;
   ysav = y;
   
   /* compute the sums and the means */
   for(Index=0; Index<n; Index++)
   {
      Sxy = Sxy + (FLOAT)(*x)*(FLOAT)(*y);
      Sx2 = Sx2 + (FLOAT)(*x)*(FLOAT)(*x);
      Mx = Mx + (FLOAT)(*x);
      My = My + (FLOAT)(*y);
      x++;
      y++;
   }
   xn = (FLOAT)n;
   Mx /= xn;
   My /= xn;
   
   /* compute the slope */
   Reg.slope = (Sxy - xn*Mx*My)/(Sx2 - xn*Mx*Mx);

   /* compute the y intercept */
   Reg.intercept = My - Reg.slope*Mx;

   /* Restore pointers to array beginnings */
   x = xsav;
   y = ysav;

   /* compute the variance */
   error2 = 0.0;
   for(Index=0; Index<n; Index++)
   {
      error = *y - (Reg.intercept + Reg.slope*(*x));
      error2 = error2 + error*error;
      x++;
      y++;
   }

   Reg.variance = error2/(FLOAT)(n-2);
   return Reg;
}

/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "G:\332\ut\snsrcalb.ut"
#endif
/* End of include for unit test */


