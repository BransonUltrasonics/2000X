/* $Header:   D:/SWLab/VMdb/2000Series/App/MENU2.C_V   2.171   09 Sep 2008 20:39:58   nhahmed  $ */
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
/****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------
                        
   Module name:

   Filename: menu2.c

   Function name:                      


 --------------------------------- REVISIONS --------------------------------

   Revision #  Date      Author   Description
   ==========  ========  ======   ===========
      0                           Initial Version
      1.00     04/29/96   PJ      Modified for PSOS version
      2.00     05/02/96   PJ      Changed param ID in
                                  TriggerDelayChoiceTime menu
      3.00     05/03/96   PJ      Corrected PARAM ID in all menus
      4.00     05/14/96   PJ      Prototypes in Menu2a.h
      5.00     05/29/96   PJ      Corrected error in TriggerDelayTime menu
      5.01     06/26/96   PJ      Deleted Trigger Delay Submenu.
                                  Trigger Delay to type Variable.
      5.02     07/02/96   PJ      Changed Force Step & Amplitude
                                  Step ON/OFF to STEP/FIXED
      5.03     07/19/96   PJ      Was Menu2a Now Menu2.  Now includes
                                  Menu2b and Menu2c.
      5.04     07/19/96   PJ      Added PeakPowerMenu when
                                  PkPowerMode is enabled.
      6.00     07-20-96   BEKymer General name cleanup. Removing 'Time' from
                                  the end of VARIABLE names
      6.10     07/26/96   PJ      Added and enabled all WeldMode Menus.
      6.20     08/01/96   PJ      Added/Changed menus per Spec Rev 1.C.
      6.30     08/07/96   PJ      Corrected Force & Amplitude Step menus
                                  EnabledFlag.
      6.40     08/14/96   PJ      Enable TimeOut Menu in Grd Detect mode
      6.50     08/21/96   PJ      Deleted duplicate WeldForce and
                                  Amplitude menus.
      6.60     08/23/96   PJ      Enabled WeldForce & Amplitude menus in
                                  Continuous mode.
      6.70     09/04/96   PJ      Corrected bugs in Force and Amplitude Step
      6.80     09/11/96   PJ      Moved TimeoutEnergy menu under Control Limits.
                                  Changed to MaxTimeout.
      6.90     09-18-96   BEKymer In VARIABLE ABSCutoff use ABSCutoffDist for
                                  MinLimit and MaxLimit
      7.00     09-20-96   PhilJ   Corrected bug in Rapid Traverse menu
                                  StepAtDist.
      7.10     09/25/96   PJ      Put back Min/Max Limits in StepatDist menu.
      7.20     10/09/96   PhilJ   Changed Menus to type const. 
      8.00     10/13/96   LAM     fixed force step text        
      8.10     10/19/96   PhilJ   fixed SuspectLimits & RejectLimits.
      8.20     10/22/96   PhilJ   Changed External Pretrigger to On/Off.
      8.30     10/24/96   PhilJ   Corrected menus that display only in
                                  ADVANCE mode.
      9.00     10/24/96   LAM     Changed internalcontrol flags to extern
      9.10     10/27/96   LAM     deleted downspeed2 menus                
      9.20     10/29/96   PhilJ   Changed Display enable flag to
                                  PretrigAmplitude menu.
      9.30     11/08/96   PhilJ   Changed WeldForce1 user from ADVANCED
                                  to NORMAL.
      9.40     11/12/96   PhilJ   Deleted function from Suspect and Reject
                                  menus.
      9.50     11/27/96   PhilJ   AfterBurst cannot be turned off. Energy
                                  Comp available in Time Mode only.
                                  Added PreWeldSeek Menu for Continuous Mode.
      9.60     12/13/96   PhilJ   Enabled Frequency Offset value menu in
                                  Continuous Mode.
      9.70     12/23/96   PhilJ   Set AutoPretrig menu actuator type to AE.
      9.80     12/31/96   PhilJ   Changed Pretrigger submenus to Radio type.
      9.90     01/17/97   PhilJ   Changed TriggerDelay, DownSpeed,
                                  and AmpStepatForce to EP actuator only.
     10.00     01/28/97   LAM     removed unused externals
     10.10     01/31/97   PhilJ   Added CycleAbortschoice menu & MissingParts
     10.20     02/13/97   PhilJ   Corrected MissingPartMaximum string.
     10.30     02/18/97   PhilJ   Changed AutoPretrig actuator type to AE.
     10.40     04/10/97   PhilJ   Deleted CollapseCutoff until rel.2.
     10.50     04/21/97   PhilJ   Fixed bug in all Pretrigger functions.
     10.60     04-28-97   PhilJ   Chngd AmpControlInternal & FreqControlInternal
                                  from UINT8 to UINT16.
     10.70     04-30-97   PhilJ   Corrected StepatAmp functions.
     11.2.44   05-09-97   BEKymer Changed AMPSTEPMASK from 7C to 0xfffE
     11.2.45   06-11-97   LAM     deleted reset required,energy comp                
     12.2.46   06-12-97   LAM     replaced missingpartlimit
     13.2.47   06-16-97   Joe.B   Enable "Missing Part".
     13.2.48   07/01/97   LAM     moved actuator clr from sysconfig,enabled tec
     13.2.49   07/01/97   LAM     enabled collapse cutoff,reset required,switched limits
     13.2.50   07/03/97   LAM     added missingpart to ground detect                    
     13.2.51   07/09/97   PhilJ   added ScrubTimeFlag to VARIABLE ScrubTimeGndDet
     2.52      07/17/97   PhilJ   Chngd Suspect & Reject strings per ORS 1.08
     2.53      07/24/97   JBerman Changed CycleAbort:    NORMAL->ADVANCED
                                          ControlLimits: NORMAL->ADVANCED
                                          Amplitude1:    ADVANCED->ADVANCED
                                          AmpStepExt:    NORMAL->ADVANCED
                                          MissingPart:   ADVANCED->NORMAL
                                          RessetRequiredRLimit: ADVANC->NORMAL
                                          PreWeldSeekChise: ADVANCED->NORMAL

                          PhilJ   AutoPreTrig Menu: Changed encoder enable
                                                    to FALSE  
     2.54      07/28/97   PhilJ   Added functions SetSetupFlag & ClearSetupFlag
     2.55      07.28.97   JBerman MENU: MissingPartMax <-> MissingPartMin
                                        MaxEnergyComp  <-> MinEnergyComp
     2.56      07-31-97   BEKymer Fix LEVEL on CollapseCutoff & CollapseColl
     2.57      08-01-97   PhilJ   Deleted title menus depending on weld mode.
                                  Added titleWeldSetup menu.
     2.58      08-15-97   PhilJ   Chngd ActClearOutput Encoder FALSE to TRUE.
                                  MissingPart to Encoder required.
 
     2.59      08-23-97   NWu     Chngd MTimeR, PTimeR display string
     2.60      09-09-97   BEKymer Add paren's where many bit are or'ed
     2.61      09-24-97   BJB     Enabled PretrigAmplitude without encoder
                                  Changed "encoder is check" comments for
                                  consistency
     2.62      09-29-97   BJB     Created separate Cycle Aborts choice for
                                  ground detect mode (see comment in code)
     2.63      10-07-97   BJB     Moved amp step functions from level_t to level_f
     2.64      10-13-97   BJB     Made ID of AmpStepExt, AutoPretrig,
                                  PretrigDist, and PretrigExt equal to
                                  XXCANTCHANGEXX so "Off" doesn't show up as an
                                  option on the menu.  Also eliminates
                                  redundant call to UpdateCurrentPreset().
     2.65      11-6-97    BJB     Took distance settings off menus for control
                                   levels 1 and 2.
                                  Added text line to show Freq Offset>Ext if
                                   freq offset external, added this to weld
                                   setup menu.
     2.66      01-19-98   BJB     Doesn't allow user to disable MaxTimeout.
     2.67      01-22-98   BJB     Uses StrOn/StrOff instead of StrYes/StrNo
     2.68      01-23-98   LAM     chged triggerdelay & downspeed to level_f, made
                                  EP settings level_f
     2.69      01-23-98   BJB     Swapped position of Cycle Aborts and Control
                                   Limits as per spec.
     2.70      03-10-98   LAM     made triggerforce to AEd & LEVEL_d
     2.71      04-06-98   BEKymer Remove PKPOWERMODE from ControlLimitsChoice
                                  Move MaxTimeout to above ControlLimits menu
     2.72      05-21-98   LAM     deleted EP define, auto pretrigger is for any actuator
                                  swapped level_ea = a and level_d = d
     2.73      05-28-98   BJB     Added function FreqOffsetChangeSign().
                                  Made FreqOffset a normal VARIABLE that can be
                                   selected and edited.
                                  Modified Freq Offset menu to get rid of
                                   Increase/Decrease, add Change Sign.
     2.74      06-01-98   BJB     Moved Act Clr Output menu choice to before
                                   Cycle Aborts.
     2.75      06-15-98   BJB     Created two versions of ControlLimitsChoice
                                   so it can be removed for peak power mode on
                                   AE but not on AED/AEF.
     2.76      06-24-98   BEKymer Add ground detect mode to the following:
                                   PTrigDistRLimit   DCS # 2685
                                   PTrigDistSLimit   DCS # 2685
                                   MTrigDistRLimit   DCS # 2685
                                   MTrigDistSLimit   DCS # 2685
                                   PMaxForceRLimit
                                   PMaxForceSLimit
                                   MMaxForceRLimit
                                   MMaxForceSLimit
     2.77      07-31-98   BJB      Includes kpresmsg.h, getmsg.h
     2.78      08-03-98   BEKymer  Change peak power, peak power cutoff, and
                                   all suspect and reject limits so tenths
                                   can be entered (PERCENT to PERCENTX10)
     2.79      08-11-98   BEKymer  Change Step @ Pwr so tenths can be entered
     2.80      05-12-99   JZ       Added Weld Force, Hold Force, Downspeed, Rapid Travers,
                                   Set Pressure, Force Ramps menus
     2.81      05-13-99   OFI      Changed WeldForce1 to WeldForceSetupMenu, made StepAtRTDist
     2.82      05-21-99   JZ       corrected Force Stepping 
     2.83      06-01-99   JZ       disabled amplitude step at force
     2.84      06-16-99   JZ       introduced RATE_SLOWEST to RATE_FASTEST range
     2.85.1.1  07-12-99   JZ       created function HandlePresChange for EQ20 alarm
     2.86      08-04-99   JZ       added ErrorCodeFlag
     2.87      08-04-99   JZ       fixed DCS#3068
     2.88      08-06-99   JZ       added RecordErrorCode
     2.89      08-16-99   JZ       added SelectWeldSetupMenu2, ForceStepDisableFlag,
                                   SelectWeldSetupMenu2, ForceStepEnableFlag
     2.90      08-23-99   JZ       chngd TriggerForce to MinTrigForce
     2.91      08-31-99   JZ       removed SetPressureToggle from the WeldModeSelectMenu
     2.92      10-01-99   JZ       removed HandlePresChange()
     2.93      10-27-99   JZ       removed Str60psi, and Str80psi, "alarms.h"
     2.94      10-28-99   JZ       rewrote with switch statement GetWeldFRateIndex, GetStepFRateIndex,
                                   GetHoldFRateIndex
     2.94.6.1  02-07-00   JZ       removed DVS, added Mask1, Cond1, Mask2, Cond2
     2.94.6.2  02-23-00   OFI      removed 'User experience level' from menu strucutures
     2.95      11-04-99   JZ       renamed WeldForceSetupMenu_info to WeldForceSetupMenuInfo, and                              
                                   WeldForceA_info to WeldForceAInfo
     2.96      02-09-00   OFI      Made "+" and "-" Rject and Suspect limits available in Collapse Mode
               04-05-00   JZ       merged Lang to trunk
     2.97      04-14-00   SCM      Added AmpStepatAbs and ForceStepatAbs to the Amplitude
                                   Step and Force Step Submenu. 
    2.98       04-19-00   SCM      Converted tabs to spaces.
    2.99       05-26-00   SCM      Checked in for testing by Laura, John.
    2.100      06-02-00   SCM      Changed _RADIO menus corresponding to _RADIOLARGEMENU 
                                   structure to _RADIOLARGE.
    2.101      06-12-00   LAM      added DEPOT masks
    2.102      06-15-00   SCM      Changed the 'RadioMask' value for the Custom Presets 1 thro' 20.
    2.103      06-26-00   DJL      Made global name changes from MaxForceMLR to WeldForceMLR
                                   from MaxForceMLS to WeldforceMLS; MaxForcePLS to WeldForcePLS
                                    RejResetRequired to RejResetRequiredFlag
                                   and  from Preset.SeekFun to Preset.SeekFunFlag.  
                                   Changed MODEL to LEVEL,changed AmpTrigDistValue to AmpTrigColValue
                                    and also ForceTrigDistValue to ForceTrigAmpValue.    
    2.104      07-14-00   BEKymer  Added WELDSTATUS enum to DupsWeldStatus structure
    2.105      07-22-00   SCM      Modified the RADIOLARGE menus in SelPresetSubMenu in accordance with
                                   the new RADIOLARGE structure definition.
    2.107      08/02/00   SRP      & is removed infront of DUPS_ParamSetName[] at all places
    2.108      08/11/00   SCM      Changed the function called in the DUPS parameter structures
                                   from DUPS_DownloadParamSet() to DUPS_DownloadCurrPS().
    2.109      08/14/00   SCM      Added constant string StrM6_21 for the menu SelectDupsPreset.
    2.110      08/14/00   SCM      Fixed some minor problems regarding string definitions.
    2.111      08/15/00   SCM      Added function UpdateWS_Config().
    2.112      08/16/00   AT       Left-aligned some menu titles (#3430)
    2.113      08/16/00   RBH      Corrections to Save/Recall presets and Parameter Sets 
    2.114      08/19/00   RBH      Corrected indicies in DUPS Preset Displays
    2.115      08/23/00   SRP      Corrected indicies in DUPS Preset Displays after testing.
   2.116      08-25-00   BEKymer  Use CurrentPreset.DUPSPreset in RADIOLARGE menu structures
   2.117      08-29-00   AT       Changed seek ramp time var to weld ramp time
    2.118      08-31-00   LAM      deleted unused externs
    2.119      09-06-00   LAM      added RequestDUPSSetup function
    2.120      09-20-00   AT       added ChangeCurrentParamSet() to CustomPreset1..19 RADIOLARGE menus
    2.121      09-25-00   BEKymer  Changed PretrigDist menu structure from
                                    XXCANTCHANGEXX to PRETRIGDIST to compensate
                                    for change 2.207 made in menu.c.  This change
                                    (in menuc.c) prevented pretrig@D from being
                                    selected.                                   
    2.122      10-04-00   AT       Changed DUPS_DownloadCurrPS to DUPS_QueuedDownloadPS
                                   removed RequestDUPSSetup function
    2.123      10-05-00   AT       modified ChangeCurrentParamSet to queue uploads
    2.124      10-05-00   BEKymer  Modified ChangeCurrentParamSet to queue communications
                                    to DUPS except when in preready state,
                                    for a partial fix for issue #3592
    2.125      10-09-00   AT       Modified ChangeCurrentParamSet to use DUPS_QueuedUploadPS
    2.125.1.0  08-29-01   BEKymer  Feasibility test of 8.3S special
                                    - Weld setup menu displayed as read only (this version
                                      only modified suspect limits).                                    
    2.125.1.1  09-24-01   BEKymer  Final version, restoring original weld setup menu
    2.125.1.2  09-25-01   BEKymer  Fixed XXCANTCHANGEXX in AutoTretrig
                                   Removed unused PretrigExt
    2.125.2.0  09-06-03   JOY      Menu items in Force/Amp step menu's arranged as per ORS
                                   -Tracker issue #3743. 
    2.125.2.1  10-03-03   JOY      Added 'QVGAFreqOffsetSubmenu'.
    2.125.2.2  10-08-03   JOY      Added 'QVGAFreqOffsetExt' submenu .
    2.125.2.3  11-02-03   LAM      fixed tracker issue 3796, pretrigger .
    2.125.2.4  11-03-03   LAM      needed to correct above in fun selectDistpretrig also .
    2.126      01-09-01   BEKymer  Added argument to TEXT and SUBMENU structures as
                                   required by the menu system
                                   required by the menu system
    2.127      10-08-01   LAM      merged preset cleanup with 8.Specials                                  
    2.128      09-16-03   BEKymer  Add Write-in fields, external trigger delay
                                    and energy braking entries
    2.129      10-16-03   BEKymer  Changed length of StrWriteIn1 and StrWriteIn2 so
                                    a proper terminator can be inserted.                                   
    2.130      12-03-03   BEKymer  Merged 2.129 & 2.125.2.5 to create 2.130 for
                                    Ver9.00b build
    2.131      12-09-03   BEKymer  In 'const RADIO FastestStepFR' add lost
                                    control level line.
    2.132      01-21-04   BEKymer  Changed WELDTIME TO SCRUBTIME in                                   
                                    const VARIABLE ScrubTimeGndDet
    2.133      02-02-04   VSharma  Added and Called func ChangeDUPSSubParamList() when DUPS
                                   parameters SeekTime or WeldRampTime is changed.
    2.134      02-20-04   VSharma  Added 'QVGAWriteInMenu' and two ALPHA type struct for 
                                   WriteInField1 &WriteInField2.
    2.135      05-17-04   VSharma  Removed extern of unused strings.
    2.136      07-29-04   JOY      Modified func SelectAmpTriggerExt() & SelectForceTriggerExt().
    2.137      08-26-04   JOY      Removed instances of 'Frequency Offset' menu item in the 'WeldSetup' menu.
    2.138      08-27-04   BEKymer  Added Energy Brake submenu to set brake time
    2.139      09-01-04   JOY      Modified ALPHA QVGAWriteIn1 & QVGAWriteIn2.
    2.140      07-25-05   Bwadia   StrWritein1 and StrWritein2 Asian language support added.
                                   VGA exit and Save buttons added.
    2.141      08-23-05   Aare     Fixed menus to edit pretrigger delay.
                                    Bug: Radio menu radioPretriggerMode shows
                                    'Off' regardless of actual pretrigger mode.
    2.142      09-10-05   Aare     Added SBL to reject limits.
    2.143      09-12-05   Aare     Corrected order of min/max limits for -SBL freq.
    2.144      09-12-05   Aare     Reworked the backwards polarity of flags for pretrigger.
    2.145      10-10-05   Aare     Call UpdateCurrentPreset(PRETRIGDIST, NULL, NULL) after modifying pretrigger.
    2.146      10-24-05   Bwadia   PMC submenu button added to Reject limits menu
    2.147      11-02-05   Aare     Cleaned up AutoTrigFlag logic, removed
                                    leftover code from earlier implementation
                                    of pretrigger.
    2.148      11-03-05   LAM    Made SBL Dups only for any actuator
    2.149      11-22-05   Bwadia SBL menus modified
    2.150      01-03-06   Bwadia SetSBLMenuFlags() added. SBL +- Rejkect menus modified
                                 Modified for tracker issue 3980
    2.151     01-09-06  Bwadia   Modified for tracker issue 4042. VGAPMCOn and VGAPMCOff
                                 submenu items removed from reject limits menu and 
                                 one PMC choice item put in the weld setup menu
    2.152     01-12-06  Bwadia   Modified for tracker issue 4042. PresetsChoice Submenu 
                                 added in weldsetup for VFD  
    2.153     02-14-06  Bwadia   PMC choice button seen for all modes 
    2.154     02-22-06  Bwadia   Weld setup menu for VFD restored to previous implementation.
                                 Toggle button implemented for memory reset. Modified 
                                 for tracker issue 4077 and 4078
    2.155     12-22-06  NHAhmed  Uncommented the +R Time.
    2.156     01-31-07  NHAhmed  Changes related to Changed Structure variables of CHOICE and TOGGLE.
    2.157     03-12-07  NHAHmed  Changes for Force/Amp Step, PMC Alarms and Amplitude for scrub time.
    2.158     03-12-07  NHAHmed  Changed the string for Amplitude for scrub time.
    2.159     03-27-07  NHAHmed  Added VGAVisualQualityScreen menu to WeldModeSelectMenu.
    2.160     03-29-07  YGupta   Rename FlagAmplitudeStep and FlagAmplitudeFixed to AmplitudeStepEnableFlag 
                                 and AmplitudeFixedEnableFlag.
    2.161     04-24-07  NHAhmed  Changes related to Force and Amplitude Step/Fixed.
    2.162     04-27-07  YGupta   Made changes related to Force and Amplitude Step/Fixed.
    2.163     05-04-07  NHAhmed  Modified VARIABLE VQSPeakPowerMax (Tracker #4110).
    2.164     05-23-07  NHAhmed  Modified Quality Limit related Strings.
    2.165     05-28-07  NHAhmed  Modified Quality Limit String.
    2.164     07-04-07  NHAhmed  Modified code for Dups settings.
    2.165     01-11-08  NHAhmed  New functions SetWeldFRateIndex, SetHoldFRateIndex and 
                                 SetStepFRateIndex were added. And some functions were
                                 replicated to a none argument type, keeping all functionality same.
    2.166     04-14-08  NHAhmed  Renamed some functions.
    2.167     09-02-08  NHAhmed  CleanUp for multi-language support.    
    2.168     09-04-08  YGupta   CleanUp for LangTest Project.
    2.169     09-09-08  NHAhmed  CleanUp for multi-language support.    


 ------------------------------- DESCRIPTION ---------------------------------

       This file will deal with the sub menus for AllModes.
*/

/*
------------------------------ INCLUDE FILES --------------------------------
*/

#include <psos.h>
#include <prepc.h>
#include "portable.h"
#include "menu.h"
#include "preset.h"
#include "param.h"
#include "limits.h"
#include "keypad.h"
#include "selctkey.h"
#include "beep.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "ready.h"
#include "menu1.h"
#include "menu2.h"
#include "menu3.h"
#include "dups_api.h"
#include "state.h"
#include "ticks.h"
#include "dups.h"
#include "command.h"
/*
 ----------------------------- EXTERNAL FUNCTIONS ----------------------------
*/

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern SINT32 ActualValuePMC1;
extern SINT32 ActualValuePMC2;
extern UNION_BOOL_UINT16 FreqControlInternal;
extern UINT16 FreqControlExternal;
extern UNION_BOOL_UINT16 AmpControlInternal;
extern UINT16 RadioIndex;
extern BOOLEAN IsRecalledPreset;
extern BOOLEAN VerifyPresetRequired;

extern SETUPS_Ver800 CurrentPreset;    /* from SETUP to SETUPS_Ver800 */
extern SETUPS_Ver800 MaxLimit;         /* from SETUP to SETUPS_Ver800 */

extern SETUPS_Ver800 MinLimit;         /* from SETUP to SETUPS_Ver800 */

extern SINT32 ActualSBLMinFreq;
extern SINT32 ActualSBLMaxFreq;
extern enum  WELDSTATES WeldState;

extern CONFIGSETUP CurrentSetup;
extern UINT32 NackError, ErrorResponseMinLimit, ErrorResponseMaxLimit;

void LangStrCpy(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);


/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

UINT8 SetupFlag = FALSE;
static UINT16 QVGAFreqOffsetSignFlag;

UINT16 FlagPretriggerOff;
UINT16 FlagPretriggerAuto;
UINT16 FlagPretriggerTime;
UINT16 FlagPretriggerDist;
UINT16 FlagPretriggerAmpl;
UINT16 pretriggerMode;
UINT16 AmplitudeMode;
UINT16 ForceMode;

UNION_BOOL_UINT16 AmplitudeStepEnableFlag;
UNION_BOOL_UINT16 AmplitudeStepMicronsEnableFlag;
UINT16 AmplitudeFixedEnableFlag;

UNION_BOOL_UINT16 ForceStepEnableFlag;
UINT16 ForceFixedEnableFlag;

UINT8  LimitChanged = FALSE;

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/

#define AMPSTEPMASK 0xFFFE   /* Changed from 7C to FFFE V11.2.44 BEK 05-09-97 */
#define FORCESTEPMASK 0xFFFE

/* This variable needs to be defined later on. For now this is used by default */
SINT32 TOBEDEFINED = 7;

/* This FUNCTION needs to be defined later on. For now this is used by default */
void TOBEDEFINEDFN(void);
void ChangeDUPSSubParamList(void);
void SetupPretriggerFlags(void);

void SetupAmplitudeStepFlag(void);
void SetupForceStepFlag(void);
void SetupAmpModeStepFlag(void);
void SetupForceFixedOrStepFlag(void);

void TOBEDEFINEDFN()
{
}

/*
 ---------------------------------- CODE -------------------------------------
*/

void SetAmplitudeMode(void)
{
   if (AmplitudeMode == RADIO_0)
      CurrentPreset.Amp2Flag |= BIT0;
   if (AmplitudeMode == RADIO_1)
      CurrentPreset.Amp2Flag &= 0xFFFE;
   SetupAmplitudeStepFlag();
   UpdateCurrentPreset(AMPLITUDESTEPFLAG, NULL, NULL);
}

void SetAmplitudeModes(void)
{
   switch(RadioIndex){
   case 0:
      AmplitudeMode = RADIO_0;
      break;
   case 1:
      AmplitudeMode = RADIO_1;
      break;
   }

   if (AmplitudeMode == RADIO_0)
      CurrentPreset.Amp2Flag |= BIT0;
   if (AmplitudeMode == RADIO_1)
      CurrentPreset.Amp2Flag &= 0xFFFE;
   SetupAmpModeStepFlag();
}

void PrepareAmplitudeRadioMenu(void)
{
   AmplitudeMode = RADIO_0;
   RadioIndex    = 0;
   if ((CurrentPreset.Amp2Flag & BIT0) == BIT0)
   {
      AmplitudeMode = RADIO_0;
      RadioIndex = 0;
   } 
   else
   {
      AmplitudeMode = RADIO_1;
      RadioIndex = 1;
   } 
}

void PrepareForceRadioMenu(void)
{
   ForceMode = RADIO_0;
   RadioIndex    = 0;
   if ((CurrentPreset.Force2Flag & BIT0) == BIT0)
   {
      ForceMode = RADIO_0;
      RadioIndex = 0;
   } 
   else
   {
      ForceMode = RADIO_1;
      RadioIndex = 1;
   } 
}

void SetForceMode(void)
{
   if (ForceMode == RADIO_0)
      CurrentPreset.Force2Flag |= BIT0;
   if (ForceMode == RADIO_1)
      CurrentPreset.Force2Flag &= 0xFFFE;
   SetupForceStepFlag();
   UpdateCurrentPreset(FORCESTEPFLAG, NULL, NULL);
}

void SetForceModes(void)
{
   switch(RadioIndex){
   case 0:
         ForceMode = RADIO_0;
         break;
   case 1:
         ForceMode = RADIO_1;
         break;
   }

   if (ForceMode == RADIO_0)
      CurrentPreset.Force2Flag |= BIT0;
   if (ForceMode == RADIO_1)
      CurrentPreset.Force2Flag &= 0xFFFE;
   SetupForceFixedOrStepFlag();
}

void SetSetupFlag(UINT32 MenuExtra)   /*  IT APPEARS SetupFlag IS NOT USED BEK 09-19-01 */
{
   SetupFlag = TRUE;
}


void ClearSetupFlag(void)
{
   SetupFlag = FALSE;
}

void SelectAmpTriggerTime(void)
{
   if((CurrentPreset.Amp2Flag & /*AmpStepAtTime.BitMask*/BIT2) != /*AmpStepAtTime.BitMask*/BIT2)
   {
      CurrentPreset.Amp2Flag = (~(/*AmpStepAtTime.BitMask*/BIT2)) | BIT0;
      CurrentPreset.AmpTrigExtFlag = FALSE;
      UpdateCurrentPreset(AMPTRIGTIMEVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK) &
             CurrentPreset.AmpTrigExtFlag == FALSE) 
                CurrentPreset.Amp2Flag = (~(/*AmpStepAtTime.BitMask*/BIT2)) | BIT0;
}

void SelectAmpTriggerEnergy(void)
{
   if((CurrentPreset.Amp2Flag & /*AmpStepAtEner.BitMask*/BIT3) != /*AmpStepAtEner.BitMask*/BIT3)
   {
      CurrentPreset.Amp2Flag = (~(/*AmpStepAtEner.BitMask*/BIT3)) | BIT0;
      CurrentPreset.AmpTrigExtFlag = FALSE;
      UpdateCurrentPreset(AMPTRIGENERVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK) &
             CurrentPreset.AmpTrigExtFlag == FALSE) 
                CurrentPreset.Amp2Flag = (~(/*AmpStepAtEner.BitMask*/BIT3)) | BIT0;
}


void SelectAmpTriggerPower(void)
{
   if((CurrentPreset.Amp2Flag & /*AmpStepAtPower.BitMask*/BIT4) != /*AmpStepAtPower.BitMask*/BIT4)
   {
      CurrentPreset.Amp2Flag = (~(/*AmpStepAtPower.BitMask*/BIT4)) | BIT0;
      CurrentPreset.AmpTrigExtFlag = FALSE;
      UpdateCurrentPreset(AMPTRIGPOWERVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK) &
             CurrentPreset.AmpTrigExtFlag == FALSE) 
                CurrentPreset.Amp2Flag = (~(/*AmpStepAtPower.BitMask*/BIT4)) | BIT0;
}


void SelectAmpTriggerDist(void)
{
   if((CurrentPreset.Amp2Flag & /*AmpStepAtDist.BitMask*/BIT5) != /*AmpStepAtDist.BitMask*/BIT5)
   {
      CurrentPreset.Amp2Flag = (~(/*AmpStepAtDist.BitMask*/BIT5)) | BIT0;
      CurrentPreset.AmpTrigExtFlag = FALSE;
      UpdateCurrentPreset(AMPTRIGDISTVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK) &
             CurrentPreset.AmpTrigExtFlag == FALSE) 
                CurrentPreset.Amp2Flag = (~(/*AmpStepAtDist.BitMask*/BIT5)) | BIT0;
}


void SelectAmpTriggerForce(void)
{
   if((CurrentPreset.Amp2Flag & /*AmpStepAtForce.BitMask*/BIT6) != /*AmpStepAtForce.BitMask*/BIT6)
   {
      CurrentPreset.Amp2Flag = (~(/*AmpStepAtForce.BitMask*/BIT6)) | BIT0;
      CurrentPreset.AmpTrigExtFlag = FALSE;
      UpdateCurrentPreset(AMPTRIGFORCEVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK) &
             CurrentPreset.AmpTrigExtFlag == FALSE) 
                CurrentPreset.Amp2Flag = (~(/*AmpStepAtForce.BitMask*/BIT6)) | BIT0;
}


void SelectAmpTriggerExt(void)
{
   if(CurrentPreset.AmpTrigExtFlag == FALSE)
   {
      CurrentPreset.AmpTrigExtFlag = TRUE;
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;                                                 
   }
   else if(CurrentPreset.AmpTrigExtFlag)
   {
      /* Disable all bits BIT0 enabled */
      CurrentPreset.Amp2Flag = (BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT0);
      UpdateCurrentPreset(AMPTRIGEXTFLAG, NULL, NULL);
   }
   else if( (CurrentPreset.Amp2Flag & AMPSTEPMASK) == AMPSTEPMASK)
           CurrentPreset.AmpTrigExtFlag = TRUE;
           
   VerifyPresetRequired = TRUE; 
}


void SelectForceTriggerTime(void)
{
   if((CurrentPreset.Force2Flag & /*ForceStepAtTime.BitMask*/BIT2) != /*ForceStepAtTime.BitMask*/BIT2)
   {
      CurrentPreset.Force2Flag = (~(/*ForceStepAtTime.BitMask*/BIT2)) | BIT0;
      CurrentPreset.ForceTrigExtFlag = FALSE;
      UpdateCurrentPreset(FORCETRIGTIMEVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Force2Flag & FORCESTEPMASK) == FORCESTEPMASK) &
             CurrentPreset.ForceTrigExtFlag == FALSE) 
                CurrentPreset.Force2Flag = (~(/*ForceStepAtTime.BitMask*/BIT2)) | BIT0;
}


void SelectForceTriggerEnergy(void)
{
   if((CurrentPreset.Force2Flag & /*ForceStepAtEner.BitMask*/BIT3) != /*ForceStepAtEner.BitMask*/BIT3)
   {
   CurrentPreset.Force2Flag = (~(/*ForceStepAtEner.BitMask*/BIT3)) | BIT0;
   CurrentPreset.ForceTrigExtFlag = FALSE;
   UpdateCurrentPreset(FORCETRIGENERVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Force2Flag & FORCESTEPMASK) == FORCESTEPMASK) &
             CurrentPreset.ForceTrigExtFlag == FALSE) 
                CurrentPreset.Force2Flag = (~(/*ForceStepAtEner.BitMask*/BIT3)) | BIT0;
}


void SelectForceTriggerPower(void)
{
   if((CurrentPreset.Force2Flag & /*ForceStepAtPower.BitMask*/BIT4) != /*ForceStepAtPower.BitMask*/BIT4)
   {
   CurrentPreset.Force2Flag = (~(/*ForceStepAtPower.BitMask*/BIT4)) | BIT0;
   CurrentPreset.ForceTrigExtFlag = FALSE;
   UpdateCurrentPreset(FORCETRIGPOWERVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Force2Flag & FORCESTEPMASK) == FORCESTEPMASK) &
             CurrentPreset.ForceTrigExtFlag == FALSE) 
                CurrentPreset.Force2Flag = (~(/*ForceStepAtPower.BitMask*/BIT4)) | BIT0;
}


void SelectForceTriggerDist(void)
{
   if((CurrentPreset.Force2Flag & /*ForceStepAtCol.BitMask*/BIT5) != /*ForceStepAtCol.BitMask*/BIT5)
   {
   CurrentPreset.Force2Flag = (~(/*ForceStepAtCol.BitMask*/BIT5)) | BIT0;
   CurrentPreset.ForceTrigExtFlag = FALSE;
   UpdateCurrentPreset(FORCETRIGDISTVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Force2Flag & FORCESTEPMASK) == FORCESTEPMASK) &
             CurrentPreset.ForceTrigExtFlag == FALSE) 
                CurrentPreset.Force2Flag = (~(/*ForceStepAtCol.BitMask*/BIT5)) | BIT0;
}


void SelectForceTriggerAmp(void)
{
   if((CurrentPreset.Force2Flag & /*ForceStepAtAmp.BitMask*/BIT6) != /*ForceStepAtAmp.BitMask*/BIT6)
   {
   CurrentPreset.Force2Flag = (~(/*ForceStepAtAmp.BitMask*/BIT6)) | BIT0;
   CurrentPreset.ForceTrigExtFlag = FALSE;
   UpdateCurrentPreset(FORCETRIGAMPVALUE, NULL, NULL);
   }
   else if( ( (CurrentPreset.Force2Flag & FORCESTEPMASK) == FORCESTEPMASK) &
             CurrentPreset.ForceTrigExtFlag == FALSE) 
                CurrentPreset.Force2Flag = (~(/*ForceStepAtAmp.BitMask*/BIT6)) | BIT0;
}


void SelectForceTriggerExt(void)
{
   if(CurrentPreset.ForceTrigExtFlag == FALSE)
   {
      CurrentPreset.ForceTrigExtFlag = TRUE;
      NackError = WELDER_PROCESS_ERROR;
      ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
      ErrorResponseMaxLimit = 0;                                                 
   }
   else if(CurrentPreset.ForceTrigExtFlag)
   {
      /* Disable all bits, BIT0 enabled */
      CurrentPreset.Force2Flag = (BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT0);
      UpdateCurrentPreset(FORCETRIGEXTFLAG, NULL, NULL);
   }
   else if( (CurrentPreset.Force2Flag & FORCESTEPMASK) == FORCESTEPMASK)
           CurrentPreset.ForceTrigExtFlag = TRUE;
   
   VerifyPresetRequired = TRUE;
}


void ChangeFreqOffsetSign(void)
/****************************************************************************/
/*                                                                          */
/* This function is called when the "Change Sign(-,+)" line on the Frequency*/
/* Offset screen is selected.  It flips the sign of the variable containing */
/* the frequency offset, updates the preset, and causes the new value to be */
/* displayed on the screen.                                                 */
/*                                                                          */
/****************************************************************************/
{
   if (CurrentPreset.FreqOffset)
   {
      CurrentPreset.FreqOffset = -CurrentPreset.FreqOffset;
   }
   else
      Beep(ERRORBEEP);  /* If zero, can't change sign */
}



void ChangeDUPSSubParamList(void)
/****************************************************************************/
/*                                                                          */
/*  If any Recall preset is called prior, Update "DUPS_CurrentParamSet" from*/
/*  DUPS before downloading modified parameter set to the DUPS.             */
/*                                                                          */
/****************************************************************************/

{
   SINT32 SavedRampTime;
   SINT32 SavedSeekTime;
   SINT32 SavedDipSW;
    
   if(IsRecalledPreset)
   {
      SavedRampTime = DUPS_CurrentParamSet.WeldRampTime;
      SavedSeekTime = DUPS_CurrentParamSet.SeekTime;
      SavedDipSW    = DUPS_CurrentParamSet.SWDipSetting;
      
      DUPS_CurrPSStatus = DUPS_PENDING;
      DUPS_UploadParamSet(CurrentSetup.DUPS_WorkingPreset);
      DUPS_Wait4CurrPS();
      
      DUPS_CurrentParamSet.WeldRampTime = SavedRampTime;
      DUPS_CurrentParamSet.SeekTime = SavedSeekTime;
      DUPS_CurrentParamSet.SWDipSetting = SavedDipSW;
      if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPSTOREMEMATWLDEND) /* Check for bit4 if set flag = True*/
         DUPS_Info. DUPSMemFlag = TRUE;
      else                                /*Update status in DUPS Info*/
         DUPS_Info. DUPSMemFlag = FALSE;

      if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPAUTOSEEK)/* Check for bit6 if set flag = True*/
         DUPS_Info. DUPSSeekFlag = TRUE;
      else              
         DUPS_Info. DUPSSeekFlag = FALSE;  

      if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPCLEARMEMATRST) /* Check for bit3 if set flag = True*/
         DUPS_Info. DUPSMemRstFlag = TRUE;
      else                                /*Update status in DUPS Info*/
         DUPS_Info. DUPSMemRstFlag = FALSE;
   }
   DUPS_QueuedDownloadPS();
}

void VQSLimitsChanged(void)
{     
  LimitChanged = TRUE;
}

/***   ***   Force Step Submenu   ***   ***/
void PreparePretriggerRadioMenu(void)
{
   pretriggerMode = RADIO_1;
   RadioIndex = 1;
   if (CurrentPreset.PreTrigFlag == FALSE)
      {
         pretriggerMode = RADIO_0;
         RadioIndex = 0;
      } 
   if (CurrentPreset.PreTrigDistFlag == FALSE)
      {
         pretriggerMode = RADIO_2;
         RadioIndex = 2;
      }
   if (CurrentPreset.PreTrigDelayFlag == FALSE)
      {
         pretriggerMode = RADIO_3;
         RadioIndex = 3;
      }
}

void SetPretriggerModes(void)
{
   // default values - pretrigger auto, from there we change one bit for
   // any other pretrigger mode
   CurrentPreset.PreTrigFlag = TRUE;
   CurrentPreset.AutoTrigFlag = FALSE;
   CurrentPreset.PreTrigDistFlag = TRUE;
   CurrentPreset.PreTrigDelayFlag = TRUE;
   switch(RadioIndex){
   case 0:
      pretriggerMode = RADIO_0;
      break;
   case 1:
      pretriggerMode = RADIO_1;
      break;
   case 2:
      pretriggerMode = RADIO_2;
      break;
   case 3:
      pretriggerMode = RADIO_3;
      break;
   }
   if (pretriggerMode == RADIO_0)
      CurrentPreset.PreTrigFlag = FALSE;
   if (pretriggerMode == RADIO_1)
      CurrentPreset.AutoTrigFlag = TRUE;
   if (pretriggerMode == RADIO_2)
      CurrentPreset.PreTrigDistFlag = FALSE;
   if (pretriggerMode == RADIO_3)
      CurrentPreset.PreTrigDelayFlag = FALSE;
   SetupPretriggerFlags();
}

void SetPretriggerMode(void)
{
   // default values - pretrigger auto, from there we change one bit for
   // any other pretrigger mode
   CurrentPreset.PreTrigFlag = TRUE;
   CurrentPreset.AutoTrigFlag = FALSE;
   CurrentPreset.PreTrigDistFlag = TRUE;
   CurrentPreset.PreTrigDelayFlag = TRUE;
   
   if (pretriggerMode == RADIO_0)
      CurrentPreset.PreTrigFlag = FALSE;
   if (pretriggerMode == RADIO_1)
      CurrentPreset.AutoTrigFlag = TRUE;
   if (pretriggerMode == RADIO_2)
      CurrentPreset.PreTrigDistFlag = FALSE;
   if (pretriggerMode == RADIO_3)
      CurrentPreset.PreTrigDelayFlag = FALSE;
   SetupPretriggerFlags();
   UpdateCurrentPreset(PRETRIGDIST, NULL, NULL);
}
   
void GetWeldFRateIndex(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Weld Force Rate choice                                               */
/*                                                                          */
/****************************************************************************/
{
   switch(CurrentPreset.WeldFR)
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

void SetWeldFRateIndex(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Weld Force Rate choice                                               */
/*                                                                          */
/****************************************************************************/
{
   switch(RadioIndex)
   {
      case 0:
         CurrentPreset.WeldFR = RATE_SLOWEST;
         break; 
         
      case 1:
         CurrentPreset.WeldFR = RATE_SLOW;
         break;
         
      case 2:
      default:
         CurrentPreset.WeldFR = RATE_NORMAL;
         break;     
         
      case 3:
         CurrentPreset.WeldFR = RATE_FAST;
         break;
         
      case 4:
         CurrentPreset.WeldFR = RATE_FASTEST;
         break;
   }
}   

void SetStepFRateIndex(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Weld Force Rate choice                                               */
/*                                                                          */
/****************************************************************************/
{
   switch(RadioIndex)
   {
      case 0:
         CurrentPreset.StepFR = RATE_SLOWEST;
         break; 
         
      case 1:
         CurrentPreset.StepFR = RATE_SLOW;
         break;
         
      case 2:
      default:
         CurrentPreset.StepFR = RATE_NORMAL;
         break;     
         
      case 3:
         CurrentPreset.StepFR = RATE_FAST;
         break;
         
      case 4:
         CurrentPreset.StepFR = RATE_FASTEST;
         break;
   }
}
void GetStepFRateIndex(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Step Force Rate choice                                               */
/*                                                                          */
/****************************************************************************/
{
   switch(CurrentPreset.StepFR)
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
void SetHoldFRateIndex(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Weld Force Rate choice                                               */
/*                                                                          */
/****************************************************************************/
{
   switch(RadioIndex)
   {
      case 0:
         CurrentPreset.HoldFR = RATE_SLOWEST;
         break; 
         
      case 1:
         CurrentPreset.HoldFR = RATE_SLOW;
         break;
         
      case 2:
      default:
         CurrentPreset.HoldFR = RATE_NORMAL;
         break;     
         
      case 3:
         CurrentPreset.HoldFR = RATE_FAST;
         break;
         
      case 4:
         CurrentPreset.HoldFR = RATE_FASTEST;
         break;
   }
}   
void GetHoldFRateIndex(void)
/****************************************************************************/
/* This function converts bit index to a sequential number                  */
/* for Hold Force Rate choice                                               */
/*                                                                          */
/****************************************************************************/
{
   switch(CurrentPreset.HoldFR)
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
   

void UpdateWS_Config(void)
{
  if(CurrentPreset.WeldStatusFlag)
  UpdateSWConfiguration(WS,TRUE);
  else
  UpdateSWConfiguration(WS,FALSE);
}  
