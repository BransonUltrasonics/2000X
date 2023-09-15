/* $Header:   D:/SWLab/VMdb/2000Series/App/MENUDBUG.C_V   1.124   08 Jun 2010 14:11:56   NHahmed  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Menu debug                                                  */
/*                                                                          */
/* Filename:    Menudbug.c                                                  */
/*                                                                          */
/* Function Name: Menus for debuggging and performance testing              */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */   
/*                Date:   08-26-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date      Author       Description                           */
/*  =========  ========  ===========  ===========                           */
/*     0       07-26-96  BEKymer      Original write of menu's              */
/*     1       08-01-96  BEKymer      Changed CurrentPressure to SINT32     */
/*   1.3       04-27-98  LAM          Changed EP to AEF                     */
/*   1.5       04-29-98  BJB          Deleted old debug code                */
/*   1.6       04-30-98  BJB          Added Branson Menu code & data        */
/*   1.7       05-05-98  LAM          Added trigger debug menu items        */
/*   1.8       05-14-98  LAM          save part contact variables to bbram  */
/*   1.9       05.18.98  JBerman      Changed in SetActLife: Menu1 -> Menu5;*/
/*                                    Due to Future Rel.                    */
/*   1.10      05.26.98  BJB          Calls SetMaxMinValues() after user    */
/*                                     changes PSFreq.                      */
/*   1.11      06-01-98  LAM          made part contact variables AED | AEF */
/*   1.12      06-29-98  BJB          Added 800W choice to Branson Menu.    */
/*   1.13      07-16-98  LAM          removed part contact min, will use    */
/*                                    minlimit.trigger instead              */
/*   1.14      08-05-98  LAM          commented out partcontact may need for*/
/*                                    aef                                   */
/*   1.15      09-01-98  LAM          added update calibration default entry*/
/*   1.16      09-08-98  BJB          Added menu item to print messasge log */
/*   1.17      10-13-98  LAM          update calibration saves default date */
/*   1.18      10-29-98  BJB          Saves act serial # in act Novram      */
/*   1.19      12-01-98  BJB          To prepare for 15/30KHz changes,      */
/*                                     renumbered StrBranFreq and           */
/*                                     StrBranWatts strings.                */
/*   1.20      12-07-98  BJB          Added support for 15/30KHz.           */
/*   1.21      03-12-99  BEKymer      Added menus for ramps for f0          */
/*   1.22      05-12-99  JZ           Added menus for R/T Comp, R/T Ramp,   */
/*                                    Return Ramp                           */
/*   1.23      05-13-99  JZ           Changed endlist2 to endlistDebug      */ 
/*   1.24      06-03-99  JZ           disabled SetActLife in Branson menu   */
/*   1.25      06-16-99  JZ           introduced RATE_SLOWEST to RATE_FASTEST*/
/*                                    created protoypes for local function  */
/*                                    GetRTRamp and GetReturnRamp           */
/*   1.26      08-11-99  JZ           added GetStartRamp, Start Ramps       */
/*   1.27      08-23-99  JZ           added Part Contact, Min Trigger, Gain Factor */
/*   1.28      08-23-99  LAM          need to recalculate springrate default*/
/*                                    when the Gain Factor changes */
/*   1.29      08-25-99  JZ           fixed part contact force              */
/*   1.30      09-01-99  JZ           added ConfigureFromBUCMenu            */
/*                                    moved MinTrigForce to CurrentSetup    */
/*   1.30      09-07-99  JZ           modified ConfigureFromBUCMenu         */
/*   1.31      09-09-99  LAM          update default calibrated stroke and  */
/*                                    pressure                              */
/*   1.32      09-10-99  LAM          updated factory defaults with do cold */
/*                                    start                                 */
/*   1.33      09-16-99  LAM          update default cal springrateslope    */
/*   1.34      09-23-99  BEKymer      Added S/W serial # to BUC menu        */
/*   1.35      09-23-99  BEKymer      Remove save of S/W # to Act ser num   */
/*   1.36      10-14-99  BEKymer      Added call TestWriteToNvram() and     */
/*                                    TestReadFromNvram() in ConfigureFrom  */
/*                                    BUCMenu.                              */
/*   1.37      10-26-99  JZ           Modified UpdateCalibDefaults()        */
/*   1.38      10-26-99  JZ           Added SetIdleSpeed to Branson menu    */
/*   1.39      10-28-99  JZ           rewrote with switch statement GetRTRamp,*/
/*                                    GetReturnRamp, GetStartRamp           */
/*   1.40      10-29-99  BEKymer      Fixed ConfigureFromBUCMenu() so cyl.  */
/*                                    size and stroke is written for new    */
/*                                    novrams.                              */
/*                                    Added return value to ConfigureFrom.. */
/*                                    Removed TABS!  Cleanup up spacing.    */
/*   1.41      11-04-99  JZ           converted BUC defaults to type const  */
/*   1.42      12-08-99  JZ           modified Branson menu for AED act.    */     
/*                                    fixed AE case in ConfigureFromBUCMenu */
/*                                    fixed beeping when configure AE act.  */
/*   1.42.6.1  02-08-00  JZ           removed DVS, added Mask1, Cond1, Mask2, Cond2 */
/*   1.42.6.2  02-23-00  OFI          removed 'User experience level' from menu strucutures*/ 
/*   1.43      04-05-00  JZ           merged Lang to trunk                  */
/*   1.44      04-20-00  SCM          This revision not tested or compiled. */
/*   1.45      05-26-00  SCM          Checked in for testing by Laura, John.*/
/*   1.46      09-06-00  SCM          Added the pointer function to execute */
/*                                    for structure PrintDupsSetup.         */
/*   1.47      06-28-00  BEKymer      Changed all MODEL to LEVEL            */
/*   1.48      06-29-00  BEKymer      Remove all traces of software serial# */
/*   1.49      07-18-00  SCM          Made the DUPS related menu changes    */
/*                                    for the BUC menu                      */
/*   1.50      07-19-00  SCM          Fixed the strings related to the DUPS */
/*                                    Parameter sets.                       */
/*   1.51      07-19-00  SCM          Added the function pointer DUPS_DownloadParamSet*/
/*                                    to the DIGITAL P/S menu               */
/*   1.52      07-20-00  SCM          Added the function pointer DUPS_DownloadHornScan*/
/*   1.53      07-22-00  SCM          Removed the func. Pointer DUPS_DownloadHornScan*/ 
/*   1.54      07-26-00  SCM          Added the function UpdateDupsPresetStatus()  */
/*   1.55      07-26-00  SCM          Made all the DUPS parameters in the BUC menu read-only */
/*   1.56      07-26-00  LAM          merged TEST level change              */
/*   1.57      07-27-00  SCM          Modification of function UpdateDupsPresetStatus() */
/*   1.58      07-28-00  SCM          Fixed an error in function UpdateDupsPresetStatus() */
/*   1.59      08/02/00  SRP          &DUPS_ParamSetName replaced by DUPS_PsNamePTR at all places.*/
/*   1.60      08/08/00  SCM          Added functions SetDupsPreset2Index() thro' SetDupsPreset20Index() */
/*   1.61      08/08/00  JLH          Left justified 5 menu titles.         */
/*   1.62      08/11/00  SCM          Modified function UpdateDupsPresetStatus()  */
/*   1.63      08/11/00  SCM          Modified  PresetClear() function in UpdateDupsPresetStatus() */
/*                                    to accept COPS preset no.             */
/*   1.64      08/12/00  SCM          Modified function UpdateDupsPresetStatus()  */
/*   1.65      08/14/00  AT           Removed Preset 20 from menus          */
/*   1.66      08/15/00  SCM          Commented out PrintLog (Ver9 requirement)
/*   1.67      08/16/00   RBH         Corrections to Save/Recall presets and Parameter Sets 
/*   1.68      08/24/00  LAM          Set ps ser # to 12 characters          */
/*   1.69      08/25/00  AT           Changed DipSetting menu item from CHOICE to TEXT */
/*   1.70      08/28/00  AT           Changed DipFlag strings (1 - hardware, 0 - software)
/*   1.71      08/28/00  JLH          Eliminate "Actuator Settings>" from main debug menu for all actuators */
/*                                     and levels except level_f, actuator AEF */
/*   1.72      08/29/00  JLH          Changed various HornScan variable formats from COUNTER to FORCE to prevent. */
/*                                     overrunning display fields. */
/*   1.73      08/29/00  JLH          Added Depot level stuff to checksum processing. */ 
/*   1.74      09/01/00  LAM          made  "Actuator Settings>"  available for level_d AED */
/*   1.75      09/01/00  SCM          Removed DUPS_DownloadParamSet() in MakeDipText() */
/*   1.76      09/06/00  LAM          fixed #3353 & #3354                           */ 
/*   1.77      10/03/00  JLH          Fixed #3603 - "DUPS values in BUC are wrong". */
/*   1.78      10-04-00  BEKymer      Make configuration skip steps when            */
/*                                    0 is entered for a parameter                  */
/*   1.79      10-18-00  BEKymer      In ConfigureFromBUCMenu if any act.           */
/*                                    parameter changed, then do the test           */
/*                                    write and update all of them.  This           */
/*                                    is a fix for a code review issue.             */
/*   1.80      10-18-00  SCM          Fixed issue with Amplitude & Current being    */
/*                                    incorrect in BUC menu. Issue no:3643          */
/*   1.81      10-19-00  JLH          Fixed PrintDupsSetup menu to call DUPSPresetFunc */
/*                                     Issue no:3638                                   */
/*   1.82      10-31-00  LAM          Save calhomeoffset when updating defaults    */
/*                                    (Issue 3661)                                 */
/*   1.83      11-06-00  BEKymer      Fix small bug in ConfigureFromBUCMenu(),     */
/*                                     BBRPtr->Actuator was not being set when AE  */
/*                                     was selected.                               */
/*   1.84      11-17-00  AT           UpdateDupsPresetStatus - fixed array indexing */
/*   1.85      01-16-01  BEKymer      Added argument to TEXT and SUBMENU structure calls  */
/*   1.84.1.0  04-30-01  LAM          Updated checksum to add 4000 watts           */
/*   1.84.1.1  05-11-01  LAM          docoldstartplus whenever the checksum is changed*/
/*   1.84.1.2. 08-21-01  BEKymer      Changed MaxLimitIdleSpeed to 100 % (Bill S.) */
/*   1.84.1.3  04-03-02  BEKymer      In SaveActSerialNumber() write to BBR as well*/
/*   1.84.1.2.1.1  04-25-02  BEKymer  Added 6000 W in ConfigureFromBUCMenu()       */
/*   1.86      10-09-01  LAM          merged 8.specials and preset cleanup         */
/*   1.87      08-04-03  BEKymer      Merged 1.86 and 1.84.1.2.1.1 to create 1.87  */
/*                                     for 9.00A build                             */
/*                                    -Change FactoryDefaults XXCANTCHANGEXX to    */
/*                                      BUCMENU for 8.3S                           */
/*   1.84.1.2.1.2  08-18-03  JOY      Added 'QVGABransonMenu'.                     */
/*   1.84.1.2.1.3  10-16-03  JOY      MiddleSeg. erased by QVGA ROM image          */
/*   1.88      09-03-03  BEKymer      Add Energy Braking submenu                   */
/*   1.89      12-04-03  BEKymer      Merged 1.84.1.2.1.3 & 1.88 to create 1.89    */
/*                                     for build Ver9.00b                          */
/*   1.90      12-09-03  BEKymer      Add drawscrn.h to include list               */
/*                                    Added arguments where needed                 */
/*   1.91      02-20-04  VSharma      Added EnergyBrakingSettings & AmpDecaySettings*/
/*                                    to QVGABransonMenu.                          */
/*   1.92      03-29-04  BEKymer      Make sure actuator serial # is terminated to */
/*                                     allow the full 10 characters stored in the  */
/*                                     NOVRAM.                                     */
/*   1.93      04-26-04  VSharma      Changed param id of alarm variables to ALARMMASKID.*/
/*   1.94      06-04-04  VSharma      Modified struct PrintDupsSetup for Mask1.    */
/*   1.95      07-13-04  BEKymer      Changed 2500W to 200W for Ahmnet special     */
/*   1.96      08-03-04  JOY          Updated variable 'CurrentSetup.CylinDiameter'*/
/*                                     when cyl. Dia changed by checksum           */
/*   1.97      09-09-04  BEKymer      Change EnergyBrakeTimeMax to 1000                                                                       */
/*   1.98      04-08-05  LAM          Added Sbeam change                           */
/*   1.99      07-25-05  Bwadia       Checksum item in Branson Menu Added for VGA. */
/*                                    VGA exit and Save button added               */
/*   1.100     08-28-05  Aare         Changed min limits of DUPS parameters to     */
/*                                     DUPS_MinPreset, call DUPS_QueuedDownloadPS  */
/*                                     when any parameter is changed.              */
/*   1.101     09-11-05  Aare         Merged 10f and 10h                           */
/*   1.102     09-16-05  Bwadia       Reset Scan Values button added in VGA        */
/*   1.103     10-11-05  Bwadia       Checksum item implemented as per new         */
/*                                    requirement for PS wattage in Branson Menu   */
/*   1.104     10-24-05  Bwadia       PMC timeout variable added to Branson Menu   */
/*   1.105     01-03-06  Bwadia       Seek Phase loop CF added, DIP setting text   */
/*                                    item removed. Modified for tracker 3961, 3965*/
/*   1.106     01-12-06  Bwadia       SW dip setting button removed. Also Hornscan */ 
/*                                    information variables made editable. Modified*/
/*                                    for tracker issue 3966                       */
/*   1.107     02-22-06  Bwadia       Seek ramp time and freq step variable added  */
/*                                    Modified for tracker issue 4077              */
/*   1.108     03-02-06  Bwadia       Trigger force menu implemented               */
/*   1.109     03-07-06  Bwadia       Min trigger force variable included in       */
/*                                    Trigger force menu instead of part contact   */
/*   1.110     03-20-06  Bwadia       VGA reset scan value Param ID modified       */
/*   1.111     04-13-06  Bwadia       Added PresetStatusMenuFlag to be used in     */
/*                                    displaying DUPS preset status TITLE          */
/*   1.112     22-12-06  NHAhmed      Added Min. Trigger and Part Contact to       */
/*                                    Actuator Settings.                           */
/*   1.113     07-06-07  NHAhmed      Put in check for 0 watt case for CurrentSetup.PSWatt*/
/*   1.114     10-22-07  NHAhmed      Changes done for LangTest phase 0            */
/*   1.190     01-11-08  NHAhmed      Function UpdateCallibDefaults was replicated */
/*                                    to a none argument type, keeping all functionality same.*/
/*                                    Added new functions for Dups.                 */
/*   1.191     04-14-08  NHAhmed      Renamed a function and Modified some functions*/
/*   1.192     08-01-08  NHAhmed      Added a new function UpdateDUPSPresetStatus().*/
/*   1.193     09-02-08  NHAhmed      CleanUp for multi-language support.           */
/*   1.194     09-09-08  NHAhmed      CleanUp for multi-language support.           */
/*   1.195     10-20-08  NHAhmed      Replaced stroke length LENGTH_7 by LENGTH_2.  */
/*   1.121     09-10-09  BEkymer      Add new define MICRO where needed             */
/*   1.122     09-22-09  YGupta       Modified CheckSum routine for MICRO Actuator. */
/*   1.123     10-02-09  BEKymer      Force US encoder for MICRO Actuator.          */
/*   1.124     06-08-10  PDwivedi     Modify VGAConfigureFromBUCMenu to configure standard MICRO.      */


/*----------------------------- DESCRIPTION--------------------------------*/

/* This temp menu file will allow testing parameters to be set              */


/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/



/*------------------------------ INCLUDES ----------------------------------*/

#include <prepc.h>
#include <string.h>
#include "param.h"
#include "preset.h"
#include "menu.h"
#include "menu3.h"
#include "menu6.h"
#include "snsrcalb.h"
#include "state.h"
#include "statedrv.h"
#include "rtclock.h"
#include "psnvram.h"
#include "actnvram.h"
#include "keypad.h"
#include "getmsg.h"
#include "menu7a.h"
#include "command.h"
#include "rtclock.h"
#include "graphs.h"
#include "battram.h"
#include "alarms.h"
#include "beep.h"
#include "dups_api.h"
#include "dups.h"
#include "drawscrn.h"

/*----------------------------- LOCAL DEFINES ------------------------------*/

/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

const SINT32 MinLimitMin = 0;
const SINT32 MaxLimitMax = 999999999;
const SINT32 AlarmPtrMin = 0;
const SINT32 AlarmPtrMax = 0x0fffffff;
const SINT32 EnergyBrakeTimeMin = 10;
const SINT32 EnergyBrakeTimeMax = 1000;
const SINT32 EnergyBrakePercentMin = 5;
const SINT32 EnergyBrakePercentMax = 100;
 SINT32 BUCFactoryDefaults = 0;
const SINT32 AmpDecayPercentMin = 0;
const SINT32 AmpDecayPercentMax = 20;


BUCMENU_800   BUCMenuRAM;
extern ALARM_MASKS AlarmPtrRam;
extern ALARM_MASKS *AlarmPtrBBR;

UINT16 DUPS_LockTemp[DUPS_NUMPARAMSET];
UINT16 ChecksumRet;
BOOLEAN VGAChecksum = FALSE;
BOOLEAN PresetStatusMenuFlag = FALSE;

/*-------------------------- Function Prototypes ---------------------------*/

void GetRTRamp(void);
void GetReturnRamp(void);
void GetStartRamp(void);
void CopyToBBR(void);
void SetDupsPreset2Index(void);
void SetDupsPreset3Index(void);
void SetDupsPreset4Index(void);
void SetDupsPreset5Index(void);
void SetDupsPreset6Index(void);
void SetDupsPreset7Index(void);
void SetDupsPreset8Index(void);
void SetDupsPreset9Index(void);
void SetDupsPreset10Index(void);
void SetDupsPreset11Index(void);
void SetDupsPreset12Index(void);
void SetDupsPreset13Index(void);
void SetDupsPreset14Index(void);
void SetDupsPreset15Index(void);
void SetDupsPreset16Index(void);
void SetDupsPreset17Index(void);
void SetDupsPreset18Index(void);
void SetDupsPreset19Index(void);
void SetDupsPreset20Index(void);
void DUPSPresetFunc(UINT32);

/*---------------------------- EXTERNAL DATA -------------------------------*/
extern BOOLEAN NextMenuFlag, ChkSumCompleteFlag;
extern BOOLEAN QVGAHwAvail;
extern UINT16  RadioIndex;

extern UINT16  DUPS_Lock[];
extern DEPOT_FLAGS  *DepotFlag;

extern SETUPS_Ver800  CurrentPreset,MinLimit, MaxLimit;
extern CONFIGSETUP    CurrentSetup;

void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);

const SINT32 MinLimitForcePC = 49;
const SINT32 MinLimitVelocityPC = 1;
const SINT32 MaxLimitVelocityPC = 10;
const SINT32 MinLimitGainFactor = 100;
const SINT32 MaxLimitGainFactor = 3000;
const SINT32 MinLimitMinTrigForce = 50;
const SINT32 MaxLimitMinTrigForce = 500;
const SINT32 MinLimitIdleSpeed = 10;
const SINT32 MaxLimitIdleSpeed = 100;

const SINT32 MinBUCFactoryDefaults = 0;
const SINT32 MaxBUCFactoryDefaults = 999999999;


SINT32 GlobalRetryCounter = 0;

                                    

/*-------------------------------- CODE ------------------------------------*/

void CopyToBBR(void)
{
    AlarmPtrBBR = (ALARM_MASKS *)BBR800_ALARM_START;

    AlarmPtrBBR->SetupGroup1 = AlarmPtrRam.SetupGroup1;
    AlarmPtrBBR->SetupGroup2 = AlarmPtrRam.SetupGroup2;
    AlarmPtrBBR->SetupGroup3 = AlarmPtrRam.SetupGroup3;
    AlarmPtrBBR->SetupGroup4 = AlarmPtrRam.SetupGroup4;
    AlarmPtrBBR->SetupGroup5 = AlarmPtrRam.SetupGroup5;
    AlarmPtrBBR->SetupGroup6 = AlarmPtrRam.SetupGroup6;
    AlarmPtrBBR->SetupGroup7 = AlarmPtrRam.SetupGroup7;
    AlarmPtrBBR->SetupGroup8 = AlarmPtrRam.SetupGroup8;
    AlarmPtrBBR->SetupGroup9 = AlarmPtrRam.SetupGroup9;
    AlarmPtrBBR->SetupGroup10 = AlarmPtrRam.SetupGroup10;
    AlarmPtrBBR->Overload = AlarmPtrRam.Overload;
    AlarmPtrBBR->NoCycle = AlarmPtrRam.NoCycle;
    AlarmPtrBBR->EquipmentFailure = AlarmPtrRam.EquipmentFailure;
    AlarmPtrBBR->CycleModified = AlarmPtrRam.CycleModified;
    AlarmPtrBBR->Reject = AlarmPtrRam.Reject;
    AlarmPtrBBR->Suspect = AlarmPtrRam.Suspect;
    AlarmPtrBBR->Warning = AlarmPtrRam.Warning;
}


void SavePSSerialNum(void)
{
   StorePSSerialNumber();     /* Write to Novram */
   GetSerialNumbers();        /* Update strings for Sys Info menu */
}



void SaveActSerialNum(void)
{
   UINT16 i;
   CONFIGSETUP *BBRPtr;

   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;

/* Note: The CurrentSetup.ActSerialNumber member is larger than MAXSERIALNUM */
/*       allowing a NULL terminator to be added at location MAXSERIALNUM.    */

   CurrentSetup.ActSerialNumber[MAXSERIALNUM] = 0;   /* make sure terminated */

   i = strlen(CurrentSetup.ActSerialNumber);
   while (i < MAXSERIALNUM)
      CurrentSetup.ActSerialNumber[i++] = ' ';

   for (i=0; i<=MAXSERIALNUM; i++) {
      BBRPtr->ActSerialNumber[i] = CurrentSetup.ActSerialNumber[i];
   }
   SetSerNum(CurrentSetup.ActSerialNumber);
   GetSerialNumbers();
}

void UpdateCalibDefault(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when calibration values are saved to the defaults*/
/*                                                                          */
/* Inputs :                                                                 */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 DateArray[3]; // 3 Words Calibration date: 04 13 1967
   RTC RTCCal;

   Beep(CONFIRMBEEP);

   UpdateDefPressure();
   UpdateDefLoadCell();
   UpdateDefForce();
   UpdateDefCalSysPressure();
   UpdateDefCalStrokeLength();
   UpdateDefSpringRateSlope();
   UpdateDefCalHomeOffset();
   RTCCal = RtcReadDateandTime();     /* Get date when calibration complete */
   DateArray[0] = RTCCal.Month;
   DateArray[1] = RTCCal.Day;
   DateArray[2] = RTCCal.Year;
   SetDefCalibDate(DateArray);     
   SetCalibPass((UINT16) CALIBDEFAULT);
   Beep(CONFIRMBEEP);
}


/* *** menus for the R/T Comp, R/T Ramp, Return Ramp  *** */

void GetRTRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Rapid Traverse Rate choice                                           */
/*                                                                          */
/****************************************************************************/
{
   switch(CurrentPreset.RTRamp)
   {
      case RATE_SLOWEST:
         RadioIndex = 0;
         break;
         
      case RATE_SLOW:
         RadioIndex = 1;
         break;
         
      case RATE_NORMAL:
      default:
         RadioIndex = 2;
         break;
         
      case RATE_FAST:
         RadioIndex = 3;
         break;
         
      case RATE_FASTEST:
         RadioIndex = 4;
         break;
   }
}

void SetRTrRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Rapid Traverse Rate choice                                           */
/*                                                                          */
/****************************************************************************/
{
   switch(RadioIndex)
   {
      case 0:
         CurrentPreset.RTRamp = RATE_SLOWEST;
         break;
         
      case 1:
         CurrentPreset.RTRamp = RATE_SLOW;
         break;
         
      case 2:
      default:
         CurrentPreset.RTRamp = RATE_NORMAL;
         break;
         
      case 3:
         CurrentPreset.RTRamp = RATE_FAST;
         break;
         
      case 4:
         CurrentPreset.RTRamp = RATE_FASTEST;
         break;
   }
}

void GetReturnRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Return Rate choice                                                   */
/*                                                                          */
/****************************************************************************/
{
   switch(CurrentPreset.ReturnRamp)
   {
      case RATE_SLOWEST:
         RadioIndex = 0;
         break;
         
      case RATE_SLOW:
         RadioIndex = 1;
         break;
         
      case RATE_NORMAL:
      default:
         RadioIndex = 2;
         break;
         
      case RATE_FAST:
         RadioIndex = 3;
         break;
         
      case RATE_FASTEST:
         RadioIndex = 4;
         break;
   }
}

void SetreturnRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Rapid Traverse Rate choice                                           */
/*                                                                          */
/****************************************************************************/
{
   switch(RadioIndex)
   {
      case 0:
         CurrentPreset.ReturnRamp = RATE_SLOWEST;
         break;
         
      case 1:
         CurrentPreset.ReturnRamp = RATE_SLOW;
         break;
         
      case 2:
      default:
         CurrentPreset.ReturnRamp = RATE_NORMAL;
         break;
         
      case 3:
         CurrentPreset.ReturnRamp = RATE_FAST;
         break;
         
      case 4:
         CurrentPreset.ReturnRamp = RATE_FASTEST;
         break;
   }
}


void GetStartRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Start Rampe Rate choice                                              */
/*                                                                          */
/****************************************************************************/

{
   switch(CurrentPreset.StartRamp)
   {
      case RATE_SLOWEST:
         RadioIndex = 0;
         break;
         
      case RATE_SLOW:
         RadioIndex = 1;
         break;
         
      case RATE_NORMAL:
      default:
         RadioIndex = 2;
         break;
         
      case RATE_FAST:
         RadioIndex = 3;
         break;
         
      case RATE_FASTEST:
         RadioIndex = 4;
         break;
   }
}

void SetstartRamp(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Rapid Traverse Rate choice                                           */
/*                                                                          */
/****************************************************************************/
{
   switch(RadioIndex)
   {
      case 0:
         CurrentPreset.StartRamp = RATE_SLOWEST;
         break;
         
      case 1:
         CurrentPreset.StartRamp = RATE_SLOW;
         break;
         
      case 2:
      default:
         CurrentPreset.StartRamp = RATE_NORMAL;
         break;
         
      case 3:
         CurrentPreset.StartRamp = RATE_FAST;
         break;
         
      case 4:
         CurrentPreset.StartRamp = RATE_FASTEST;
         break;
   }
}

void UpdateDUPSPresetStatus(UINT16 DupsPrstNum,UINT16 DupsStatus)
{
   UINT16 cnt;
   switch(DUPS_LockTemp[DupsPrstNum])
   {
      case DUPS_PARAMSETLOCKED: // Source.

         switch(DupsStatus)
         {
            case DUPS_PARAMSETLOCKED:
            // Locked to Locked. No changes occur.
               break;

            case DUPS_PARAMSETAVAIL:
               PresetClear(DUPS_FindCOP4DUPS(DupsPrstNum));
               break;

            case DUPS_PARAMSETSAVED:
               Beep(ERRORBEEP); // Condition not allowed.Report error beep.
               break;   
    
            default:
               break;
         }
         break;  

      case DUPS_PARAMSETAVAIL:         //source

         switch( DupsStatus ) 
         {
            case DUPS_PARAMSETLOCKED:  // Destination.
               break;
  
            case DUPS_PARAMSETAVAIL:
            // Avail to Avail. No changes occur.
               break;

            case DUPS_PARAMSETSAVED:
               Beep(ERRORBEEP); // Condition not allowed.Report error beep.
               break;
    
            default:
               break;
         }
         break;                      

      case DUPS_PARAMSETSAVED:   // source

         switch( DupsStatus ) 
         {
            case DUPS_PARAMSETLOCKED:  //Destination
               break;
  
            case DUPS_PARAMSETAVAIL:
               PresetClear(DUPS_FindCOP4DUPS(DupsPrstNum));
               break;

            case DUPS_PARAMSETSAVED:
            // Saved to Saved. No changes occur.
               break;
    
            default:
               break;
         }
         break;                      
   
      default:
         break;
   }

   DUPS_RAM2BBRAM();
   for(cnt=0;cnt<DUPS_NUMPARAMSET;cnt++)
   DUPS_LockTemp[cnt] =  DUPS_Lock[cnt];

} //End of function

void SetDupsPreset2Index(void)
{
   switch(DUPS_Lock[1])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;                                                                       
       
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset2(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[1] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[1] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[1] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(1,DUPS_Lock[1]);
}

void SetDupsPreset3Index(void)
{
   switch(DUPS_Lock[2])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
       
   }
  // PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset3(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[2] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[2] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[2] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(2,DUPS_Lock[2]);
}


void SetDupsPreset4Index(void)
{
   switch(DUPS_Lock[3])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
        
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset4(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[3] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[3] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[3] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(3,DUPS_Lock[3]);
}


void SetDupsPreset5Index(void)
{
   switch(DUPS_Lock[4])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
        
   }
  // PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset5(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[4] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[4] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[4] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(4,DUPS_Lock[4]);
}


void SetDupsPreset6Index(void)
{
   switch(DUPS_Lock[5])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
  // PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset6(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[5] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[5] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[5] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(5,DUPS_Lock[5]);
}


void SetDupsPreset7Index(void)
{
   switch(DUPS_Lock[6])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset7(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[6] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[6] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[6] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(6,DUPS_Lock[6]);
}


void SetDupsPreset8Index(void)
{
   switch(DUPS_Lock[7])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset8(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[7] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[7] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[7] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(7,DUPS_Lock[7]);
}


void SetDupsPreset9Index(void)
{
   switch(DUPS_Lock[8])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset9(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[8] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[8] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[8] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(8,DUPS_Lock[8]);
}


void SetDupsPreset10Index(void)
{
   switch(DUPS_Lock[9])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
    //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset10(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[9] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[9] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[9] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(9,DUPS_Lock[9]);
}


void SetDupsPreset11Index(void)
{
   switch(DUPS_Lock[10])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset11(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[10] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[10] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[10] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(10,DUPS_Lock[10]);
}


void SetDupsPreset12Index(void)
{
   switch(DUPS_Lock[11])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset12(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[11] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[11] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[11] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(11,DUPS_Lock[11]);
}


void SetDupsPreset13Index(void)
{
   switch(DUPS_Lock[12])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset13(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[12] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[12] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[12] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(12,DUPS_Lock[12]);
}


void SetDupsPreset14Index(void)
{
   switch(DUPS_Lock[13])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset14(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[13] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[13] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[13] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(13,DUPS_Lock[13]);
}


void SetDupsPreset15Index(void)
{
   switch(DUPS_Lock[14])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset15(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[14] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[14] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[14] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(14,DUPS_Lock[14]);
}


void SetDupsPreset16Index(void)
{
   switch(DUPS_Lock[15])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset16(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[15] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[15] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[15] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(15,DUPS_Lock[15]);
}


void SetDupsPreset17Index(void)
{
   switch(DUPS_Lock[16])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset17(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[16] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[16] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[16] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(16,DUPS_Lock[16]);
}


void SetDupsPreset18Index(void)
{
   switch(DUPS_Lock[17])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset18(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[17] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[17] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[17] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(17,DUPS_Lock[17]);
}


void SetDupsPreset19Index(void)
{
   switch(DUPS_Lock[18])
   {
      case RADIO_0:
         RadioIndex = 0;
         break;

      case RADIO_1:
      default:
         RadioIndex = 1;
         break;

      case RADIO_2:
         RadioIndex = 2;
         break;
   }
   //PresetStatusMenuFlag = TRUE;
}

void SetDupsPreset19(void)
{
   switch(RadioIndex)
   {
      case 0:
         DUPS_Lock[18] = RADIO_0;
         break;

      case 1:
      default:
         DUPS_Lock[18] = RADIO_1;
         break;

      case 2:
         DUPS_Lock[18] = RADIO_2;
         break;                                                                       
       
   }
   UpdateDUPSPresetStatus(18,DUPS_Lock[18]);
}

void VGATestCheckSum(void)
/****************************************************************************/
/* VGA checksum Initiation function for VGA                                 */
/****************************************************************************/
{
   SINT32  temp;
   SINT32  temp1;
   SINT32  checksum;
   SINT32  checksum1 = 0;
   SINT32  x = 1000000;

   temp1 = BUCFactoryDefaults; 
   checksum = (temp1 / 10000000);
   temp1 -= (checksum * 10000000);
   
   while ( x>=1 ){
      temp = temp1 / x;
      checksum1 = checksum1 + temp;
      temp1 -= (temp * x);
      x = x/10;
   }

   BUCFactoryDefaults -= (checksum * 10000000);
   if ((BUCFactoryDefaults != 0)&&(checksum == checksum1))
      VGAChecksum = TRUE;
   else
      BUCFactoryDefaults = 0;
}

void VGAConfigureFromBUCMenu(void)
/****************************************************************************/
/* This function configure system settings based on a entered code          */
/*  XXABCDEF        XX is the checksum for all other digits                 */
/*        * A is the actuator type                                          */
/*          B is the power supply wattage                                   */
/*        * C is the actuator stroke length                                 */
/*        * D is the cylinder diameter                                      */
/*          E is the control level                                          */
/*          F is the power supply frequency                                 */
/*                                                                          */
/*  Note: If any item marked with an asterisk (*) is changed then all items */
/*        marked with an asterisk are updated.                              */
/*                                                                          */
/* The value returned in BUCFactoryDefaults will be xxxxRyyy where:         */
/*     xxxx is the number of times the novram was written to (390 or 391)   */
/*      yyy is the last location which failed the write test                */
/*        R is zero for now, but in the future may contain an indication    */
/*          if the novram has never been written to.                        */
/*                                                                          */
/****************************************************************************/
{
   SINT32  temp;
   UINT16  Data;
   SINT32  checksum;
   CONFIGSETUP *BBRPtr;
   UINT16  ChangeFlag = TRUE;
   BOOLEAN ActuatorChangeFlag = FALSE;
   BOOLEAN TestWriteDone = FALSE;

   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   GlobalRetryCounter = 0;
   checksum = (BUCFactoryDefaults / 10000000);


/**----------  Start of Actuator Type  ----------**/

  BUCFactoryDefaults -= (checksum * 10000000);
  temp = (BUCFactoryDefaults / 1000000);
  switch(temp){        /* actuator type */
     case 0:           /* No change */
        ChangeFlag = FALSE;
        break;
     case 1:           /* AED/AOD */
        Data = NVR_AED;
        BBRPtr->Actuator = AED;
        break;
     case 2:           /* AEF   */
        Data = NVR_AEF;
        BBRPtr->Actuator = AEF;
        break;
     case 3:           /* AED/AOD with Sbeam */
        Data = NVR_AED;
        BBRPtr->Actuator = AED;
        break;
     case 4:           /* AEF with SBeam */
        Data = NVR_AEF;
        BBRPtr->Actuator = AEF;
        break;
     case 5:           /* MICRO with Sbeam */
        Data = NVR_MICRO;
        BBRPtr->Actuator = MICRO;
        EnableUSEncoder();
        break;
     case 6:           /* AE/AO */
     case 7:           /* AE/AO */
     case 8:           /* AE/AO */
     case 9:           /* AE/AO */
        Data = NVR_AE;
        BBRPtr->Actuator = AE;
        break;
  }
  if (ChangeFlag == TRUE) {
     ActuatorChangeFlag = TRUE;
     CurrentSetup.Actuator = BBRPtr->Actuator;
     if ( (BBRPtr->Actuator==AED) ||
          (BBRPtr->Actuator==AEF) ||
          (BBRPtr->Actuator==MICRO) )
     {
        TestWriteToNvram();                            /* Erase everything currently in Novram */
        TestReadFromNvram();
        TestWriteDone = TRUE;
        SetActId(Data);
        if((temp == 1) || (temp==2))
           ConfigLoadcell();
        if((temp == 3) || (temp==4) || (temp==5))
           ConfigSBeam();
     }
  }
  else ChangeFlag = TRUE;


/**----------  Start of Wattage  NO LONGER USED  ----------**/



/**----------  Start of Stroke length  ----------**/

  BUCFactoryDefaults -= (temp * 1000000);
  temp = (BUCFactoryDefaults / 100000);
  if (BBRPtr->Actuator == MICRO) BBRPtr->StrokeLen = LENGTH_50;
  else { 
  switch(temp){         /* stroke length */
     case 0:           /*  No change */
        if (TestWriteDone == TRUE) {
           BBRPtr->StrokeLen = NVR.StrokeLength;
        }
        else {
           ChangeFlag = FALSE;
        }
        break;
     case 1:           /*  4" */
        BBRPtr->StrokeLen = LENGTH_4;
        break;
     case 2:           /*  5" */
        BBRPtr->StrokeLen = LENGTH_5;
        break;
     case 3:           /*  6" */
        BBRPtr->StrokeLen = LENGTH_6;
        break;
     case 4:           /*  7" */
        BBRPtr->StrokeLen = LENGTH_2;
        break;
     case 5:           /*  80mm */
        BBRPtr->StrokeLen = LENGTH_80;
        break;
     case 6:           /* 100mm */
        BBRPtr->StrokeLen = LENGTH_100;
        break;
     case 7:           /* 125mm */
        BBRPtr->StrokeLen = LENGTH_125;
        break;
    /* case 8:           /* 160mm * /
        BBRPtr->StrokeLen = LENGTH_160;
        break;*/
    case 8:           /* 50mm */
        BBRPtr->StrokeLen = LENGTH_50;
        break;
     case 9:           /* custom */
        BBRPtr->StrokeLen = CUSTOMLEN;
        break;
	  }
  }
  if (ChangeFlag == TRUE) {
     ActuatorChangeFlag = TRUE;
     if ( (BBRPtr->Actuator==AED) ||
          (BBRPtr->Actuator==AEF) ||
          (BBRPtr->Actuator==MICRO) )
     {
        if (TestWriteDone == FALSE) {
           TestWriteToNvram();         /* Erase everything currently in Novram */
           TestReadFromNvram();
           TestWriteDone = TRUE;
           SetActId(Data);
        }
        SetStrokeLength(BBRPtr->StrokeLen);  
        SetDefStrokeLength(BBRPtr->StrokeLen);  
     }
     else     /* no novram */
     {
        NVR.StrokeLength=BBRPtr->StrokeLen;
        NVR.DefStrokeLength=BBRPtr->StrokeLen;
     }
  }
  else ChangeFlag = TRUE;


/**----------  Start of Cylinder diameter  ----------**/

  BUCFactoryDefaults -= (temp * 100000);
  temp = (BUCFactoryDefaults / 10000);
  if (BBRPtr->Actuator == MICRO) BBRPtr->CylinDiameter = SIZE_40;
  else {
     switch(temp){        /* cylinder diameter */
        case 0:           /*   No change */
           if (TestWriteDone == TRUE) {
              BBRPtr->CylinDiameter = NVR.CylSize;
           }
           else {
              ChangeFlag = FALSE;
           }
           break;
        case 1:           /* 1.5" */
           BBRPtr->CylinDiameter = SIZE1_5;
           break;
        case 2:           /*   2"*/
           BBRPtr->CylinDiameter = SIZE2_0;
           break;
        case 3:           /* 2.5" */
           BBRPtr->CylinDiameter = SIZE2_5;
           break;
        case 4:           /*   3" */
           BBRPtr->CylinDiameter = SIZE3_0;
           break;
        case 5:           /* 3.25" */
           BBRPtr->CylinDiameter = SIZE3_25;
           break;
        case 6:           /*  40mm */
           BBRPtr->CylinDiameter = SIZE_40;
           break;
        case 7:           /*  50mm */
           BBRPtr->CylinDiameter = SIZE_50;
           break;
        case 8:           /*  63mm */
           BBRPtr->CylinDiameter = SIZE_63;
           break;
        case 9:           /*  80mm */
           BBRPtr->CylinDiameter = SIZE_80;
           break;
     }
  }   
  if (ChangeFlag == TRUE) {
     ActuatorChangeFlag = TRUE;
     if ( (BBRPtr->Actuator==AED) ||
          (BBRPtr->Actuator==AEF) ||
          (BBRPtr->Actuator==MICRO) )
     {
        if (TestWriteDone == FALSE) {
           TestWriteToNvram();         /* Erase everything currently in Novram */
           TestReadFromNvram();
           TestWriteDone = TRUE;
           SetActId(Data);
           SetStrokeLength(BBRPtr->StrokeLen);  
           SetDefStrokeLength(BBRPtr->StrokeLen);  
        }
        SetCylSize(BBRPtr->CylinDiameter);     
        SetDefCylSize(BBRPtr->CylinDiameter);     
     }
     else     /* no novram */
     {
        NVR.CylSize=BBRPtr->CylinDiameter;
        NVR.DefCylSize=BBRPtr->CylinDiameter;
     }
     CurrentSetup.CylinDiameter = BBRPtr->CylinDiameter;      
  }
  else ChangeFlag = TRUE;


/**----------  Start of Control level  ----------**/

  BUCFactoryDefaults -= (temp * 10000);
  temp = (BUCFactoryDefaults / 1000);
  switch(temp){        /* control level */
     case 0:           /* No change */
        ChangeFlag = FALSE;
        break;
     case 1:           /*  t */
        BBRPtr->ControlLevel = LEVEL_t;
        DepotFlag->IsADepot = FALSE;
        break;
     case 2:           /*  e */
        BBRPtr->ControlLevel = LEVEL_e;
        DepotFlag->IsADepot = FALSE;
        break;
     case 3:           /*  ea */
        BBRPtr->ControlLevel = LEVEL_ea;
        DepotFlag->IsADepot = FALSE;
        break;
     case 4:           /*  d */
        BBRPtr->ControlLevel = LEVEL_d;
        DepotFlag->IsADepot = FALSE;
        break;
     case 5:           /*  f */
        BBRPtr->ControlLevel = LEVEL_f;
        DepotFlag->IsADepot = FALSE;
        break;                      
     case 6:           /* Depot (t internal) */
        BBRPtr->ControlLevel = LEVEL_t;
        DepotFlag->WasADepot = TRUE;
        DepotFlag->IsADepot = TRUE;
        break;
     case 7:           /* a */
        BBRPtr->ControlLevel = LEVEL_a;
        DepotFlag->IsADepot = FALSE;
        break;
     case 8:           /* t */
        BBRPtr->ControlLevel = LEVEL_t;
        DepotFlag->IsADepot = FALSE;
        break;
     case 9:           /* test */
        BBRPtr->ControlLevel = LEVEL_TEST;
        DepotFlag->IsADepot = FALSE;
        break;
  }
  if (ChangeFlag == TRUE) {
     CurrentSetup.ControlLevel = BBRPtr->ControlLevel;
     StorePSControlLevel();
     GetControlLevel();
  }
  else ChangeFlag = TRUE;

  // Set Encoder Type in case its a Micro Actuator
  if (ActuatorChangeFlag == TRUE) {
     if ( BBRPtr->Actuator==MICRO)
     {
         SetEncoderType(ENCODER_ENGLISH);//2000X micro std prod
     }
 }
/**----------  Start of Frequency  NO LONGER USED  ----------**/


/**----------  Start of Wattage  ----------**/
      
  temp = BUCFactoryDefaults % 100;
  if(temp)
     BBRPtr->PSWatt = temp * 100;
  CurrentSetup.PSWatt = BBRPtr->PSWatt;
  StorePSWattage();

  GetSerialNumbers();

  if (ActuatorChangeFlag == TRUE) {
     if ( (BBRPtr->Actuator==AED) ||
          (BBRPtr->Actuator==AEF) ||
          (BBRPtr->Actuator==MICRO) )
     {
        SetDefSerNum((UINT8 *)&BBRPtr->ActSerialNumber);
     }
  }
  ChkSumCompleteFlag = TRUE;  
}  



void VGADebugColdStart(void)
/****************************************************************************/
/* VGA coldstart after checksum Initialization                              */
/****************************************************************************/
{
   CONFIGSETUP *BBRPtr;

   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;

/*  Here starts a bunch a things that need to be done whenever configuration takes place */

  ColdStartPlus();

/*  Here we are going to output a bunch of stuff all squeezed into the BUCFactoryDefaults for display */

     if ( (BBRPtr->Actuator==AED) ||
          (BBRPtr->Actuator==AEF) ||
          (BBRPtr->Actuator==MICRO) )
     BUCFactoryDefaults = ChecksumRet + (GlobalRetryCounter * 10000);      /* All is okay */
  else
     BUCFactoryDefaults = 10000000;   
  GetPowerSupplyInfo();
  NextMenuFlag = TRUE;
}



void ResetHornScanValue(void)
/****************************************************************************/
/* Put Default Values for horn scan parameters                              */
/****************************************************************************/
{
   HornScanInfo. MaximumAmplitude =  HS_MinScanInfo. MaximumAmplitude;
   HornScanInfo. MaximumCurrent   =  HS_MinScanInfo. MaximumCurrent;
   switch (CurrentSetup.PSFreq)
   {
      case FREQ15KHZ:
         HornScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MIN15AND30);
         HornScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MaxScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MaxScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MinScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MIN15AND30);
         HS_MinScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MIN15AND30);
         break;
      case FREQ20KHZ:
         HornScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MIN20AND40);
         HornScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MaxScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MaxScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MinScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MIN20AND40);
         HS_MinScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MIN20AND40);
		 break;
      case FREQ30KHZ:
         HornScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MIN15AND30);
         HornScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MaxScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MaxScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MAX15AND30);
         HS_MinScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MIN15AND30);
         HS_MinScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MIN15AND30);
         break;
      case FREQ40KHZ:
      default:
         HornScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MIN20AND40);
         HornScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MaxScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MaxScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MAX20AND40);
         HS_MinScanInfo. StartFreq =  DUPS_FreqD2C(DUPS_MIN20AND40);
         HS_MinScanInfo. StopFreq  =  DUPS_FreqD2C(DUPS_MIN20AND40);
         break;
   }
   HornScanInfo. TimeDelay        =  HS_MinScanInfo. TimeDelay;
//   HornScanInfo. FreqStep         =  DUPS_FreqD2C(HS_MinScanInfo. FreqStep);
   HornScanInfo.FreqStep          = HS_MinScanInfo.FreqStep;
}

