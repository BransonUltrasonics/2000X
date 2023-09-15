/* $Header:   D:/databases/VMdb/2000Series/App/MENU7.C_V   1.143.1.7.1.0   13 Feb 2014 15:49:46   hasanchez  $ */
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
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu7.c

   Function name:

    
 --------------------------------- REVISIONS --------------------------------

   Revision #      Date         Author      Description
   ==========     ========      ======      ===========
      0                                     Initial Version
                                            Strings in menutext.c
      1.00        06/20/96       PJ         Moved Counters Menu to Menu6
                                            (Systems Info).
      2.00        07/02/96       PhilJ      Changed Custem Act Logic menu
                                            from TOGGLE to CHOICE type.
      2.01        07/19/96       PhilJ      Deleted MESSAGESIZE from StrOff
                                            and StrOn to reduce ROM size.
      2.10        08/01/96       PhilJ      Added/Changed menus per Spec Rev
                                            1.C
      2.20        08/07/96       PhilJ      Changed PassWord to PassWordFlag
      2.30        08/21/96       PhilJ      Enabled Password menu.
      2.40        09/25/96       PhilJ      Moved CurrentUser to CurrentSetup.
      2.50        10/09/96       PhilJ      Changed Menus to type const. 
      3.00        10/19/96       LAM        made timestruct global       
      3.10        10/22/96       PhilJ      Enabled Time and Date. 
      3.20        10/27/96       PhilJ      Changed AdvCounters menu from type
                                            VARIABLE to type TOGGLE.
      3.30        10/29/96       PhilJ      Deleted AmpControlExternal and
                                            FreqControlExternal.
      3.40        11/13/96       PhilJ      Removed FeatureChoice menu
      3.50        12/13/96       PhilJ      Clear cycle count in ResetWeldCounter
      3.51        12/20/96       PaulG      Added UILines to reset counter.
      3.52        01/22/97       PhilJ      Disabled SequencingChoice Menu.
      4.00        01/28/97       LAM        deleted unused variables       
      4.10        01/28/97       LAM        deleted missing part out       
      5.00        02/07/97       LAM        moved actclr to preset             
      5.10        02/24/97       PhilJ      Modified GetDateAndTime for new
                                            Timekeeper Ram.
      5.20        04/03/97       PhilJ      Corrected error in ResetWeldCounter,
                                            deleted UpdateCurrentPreset.
      5.30        04-28-97       PhilJ      Chngd AmpControlInternal & Freq
                                            ControlInternal from UINT8 to UINT16.
      6.1.31      06/11/97       LAM        removed lang, custom act, digfilter,
                                            adjust while run
      6.20        06-16-97       PhilJ      Changed UpdateCurrentSetup to
                                             UpdateCurrentPreset.
                                            Added FeatureChoice menu
      7.1.33      06-18-97       PhilJ      Changed CurrentSetup.WeldTimes and Test
                                            Times to Time & Test Multiplier.
      7.1.33      06-18-97       PhilJ      Chngd CurrentSetup.LangA,B,C to enum
                                            & Baudrates to enum.
      7.1.34      06-30-97       PhilJ      Chngd BeeperTrigger from ADVANCED
                                            to NORMAL.
      7.1.36      07/01/97       LAM        moved actuator  clr to weld setup

      8.1.37      07/07/97       J.B.       Added StartScreenChoice. 
      8.1.38      07-08-97       PhilJ      Modified SetAmpControl function.
      8.1.39      07.13.97       JBERMAN    Advanced/Normal -> SetCurrentuser
                                            Adding #include "alarm.h"
      8.1.43      07/18/97       PhilJ      Added ActSettings menu.
      
      8.1.44      07/25/97       JBerman    BeeperError: chng ADVANCED->NORMAL
                                            Beeper Alarm:chng ADVANCED->NORMAL
                                            Update SetCurrentUser function.
      8.1.45      08/11/97       PhilJ      Chngd TimeDate menus to MODEL1
      8.1.46      08/13/97       PhilJ      Added Beepers and Bargraph menus.
      8.1.46      08.22.97       JBerman    Added to the func SetCurrentUser()
                                            "if (GetSF()) CurrentSetup.User = NORMAL;"
      8.1.47      08.26.97       JBerman    Eliminated Advanced Counters Feature
      8.1.48      09.08.97       KevinD     fixed DCS #1045
      1.49        09/10/97       LAM        added dtoutput.h
      1.51        09.18.97       JBerman    Added conditions into the function:
                                            SetCurrentUser.
      1.52        09.30.97       LAM        deleted setting adv feature alarm   
      1.53        10.03.97       JBerman    Expended RADIOMENU from 10 -> 12 items
      1.54        10-10-97       PaulG      Added WeldCounter to reset during abort printing.
      1.55        11-05-97       PaulG      Modified WeldCounter to reset during abort printing.
      1.56        11-4-97        BJB        Doesn't send fake "NOKEY" before displaying menus.
                                            Added new variable FreqControlExternal,
                                             set it up in SetFreqControl() along
                                             with FreqControlInternal.
      1.57        11-11-97       BJB        Doesn't force Main Menu in
                                             SetCurrentUser() unless user exited
                                             FeatureOptionsMenu via GoBack.
      1.58        11-18-97       LAM        replaced finalresults with weldingresults
      1.59        12-10-97       BJB        Modified menu item PasswordChoice to
                                             change WorkingPasswordFlag instead of
                                             CurrentSetup.PassWordFlag directly.
      1.60        12-29-97       BJB        Deleted uses of DTEnabled.
      1.61        12-31-97       BJB        Modified DisableRemoteTerminal() for
                                            new terminal code.
      1.62        01-22-98       BJB        Uses StrOn/StrOff instead of StrYes/StrNo
      1.63        02.19.98       JBerman    CurrentSetup.Features->CurrentPreSet.Features
      1.64        03.05.98       JBerman    Modified SetCurrentUser's function 
      1.65        03.10.98       JBerman    Changed MODEL1  TO MODEL2 in FeatureChoise menu
      1.66        04-15-98       BEKymer    Undo FeatureChoice menu from MODEL2 back to MODEL1
      1.67        04-28-98       BJB        Deleted unused Vptr[] array, unused ID in
                                            RADIOMENU items.
      1.68        06-01-98       BJB        Added function to update top line of Run
                                            Screen when Units changed.
      1.69        06.04.98       JBerman    In FeatureChoice, changed
                                            to MODEL1.
      1.70        06-12-98       BJB        When user changes Units, calls function that
                                             causes terminal to update header text above data.
      1.71        06-15-98       BJB        Updated SetCurrentUser() to deal with "Features"
                                             appearing on Advanced Features menu.
      1.72        06-22-98       BJB        Won't display Digital Filter in NORMAL/BASIC mode.
      1.73        06-24-98       BJB        Changed NORMAL to BASIC, ADVANCED to ALL.
      1.74        06-25-98       BJB        Modified process of changing Features setting so
                                             that user can power-off on Non-Basic popup and
                                             "All" features will be enabled.  Required creating
                                             new variable CopyFeaturesSetting for user to edit,
                                             moving CopyFeatureChoice here from MENU0.C,
                                             changing SetCurrentUser().
      1.75        06-25-98       BJB        Added function HandleFeaturesAlarm().
      1.76        06-26-98       BJB        Deleted HandleFeaturesAlarm(); instead created
                                             new menu item allowing direct editing of
                                             CurrentPreset.Features.
      1.77        08-03-98       PaulG       When reset preset counter is selected if printing is
                                             is activated then printer will be reset.                                                      
      1.78        08-04-98       PaulG       When the preset counter reset if printing is active
                                             form feed to top of next page will automatically occur.
      1.79        08.05.98       JBerman     DigitalFilter: Changed All to BASIC. 
      1.80        08-18-98       PaulG       Remove assignment to FinalResults.CycleCount....
      1.81        08-19-98       BJB        Changed some terminal function calls to their
                                             new names.
                                            Uses new EnableRemoteTerminal() to turn terminal on.
      1.82        10-25-99       JZ         Modified UpdatePresetDateandTime() and removed GetDateAndTime()
      1.82.6.1    02-07-00       JZ         removed DVS, added Mask1, Cond1, Mask2, Cond2
      1.82.6.2    02-23-00       OFI        removed #include "features.h" ; removed CopyFeaturesSetting(); removed
                                            SetCurrentUser(); removed SetCurrentUser(); removed TOGGLE structures:
                                            FeatureChoice, CopyFeatureChoice, RealFeatureChoice. fixed security level in some places;
                                            removed 'user experience level' from menu structures.
      1.82.6.3    02-29-00       JLH        Updated GetLanguageIndex function and LanguageChoice radio menu to add
                                             Spanish and Italian languages.
      1.82.6.4    03-17-00       JLH        Modied LanguageChoice radiomenu to call GetLangArrayIndex after language selection.

      1.83        02-23-00       JZ         merged 7.f4CHp to trunk
      1.84        04-05-00       JZ         merged Lang to trunk
      1.85        04-20-00       SCM        This revision not tested or compiled.
      1.86        05-26-00       SCM        Checked in for testing by Laura, John.
      1.87        06-12-00       LAM        added DUPS mask.
      1.88        06-13-00       JLH        Init Print on Sample counters when Preset counter is cleared in ResetWeldCounter.
      1.89        06-14-00       SCM        Added function UpdateLanguage().
      1.90        06-15-00       SCM        Changed the condition check in the "if" statement of UpdateLanguage() function.
      1.91        06-16-00       LAM        Language starts at a Level "t".                                                
      1.92        07-05-00       BEK/DJL    Added extra cooling variable to structure
      1.93        07-11-00       LAM        added updateterm to update language(DCS3321)
      1.94        07-14-00       BEKymer    Added EXTRACOOLING ID to ExtraCoolingOpt
      1.95        07-22-00       SCM        Updated a few parameters in the structure SetPsChoice.
      1.96        07-22-00       SCM        Updated structure SetPschoice() ,made MASk1=Cond1=0 
      1.97        07-25-00       SCM        Changed the Mask1 values for the structures SetPSFreq and
                                            SetPSWatts.
      1.98        07/27/00       SRP        SETPSTYPE added in  SetPsChoice.                                            
      1.99        09/06/00       JLH        Do form feed when language changes if not already at
                                            top of page.   
      1.100       11-14-00       LAM        removed duplicated text strings
      1.100.1.0   04-06-01       DJL        Added new string for the External Presets                       
      1.100.1.1   04-09-01       LAM        Added External Presets & handheld structure to the 
                                            system configuration menu
      1.100.1.2   04-09-01       LAM        removed duplicated text strings,m7_58,m7_61,m7_64
      1.100.1.3   04-10-01       BEKymer    Add call to SelectWeldSequence when handheld selected
      1.100.1.4   04-24-01       LAM        changed external preset structure to not DUPS, &      
                                            Handheld to AE only.
      1.100.1.5   04-25-01       LAM        fixed handheld structure to only display when it is
                                            an AE.
      1.100.1.6   04-30-01       LAM        changed 4400 Watt to 4000
      1.100.1.7   04-30-01       LAM        changed comments from 4400 Watt to 4000
      1.100.1.8   08-03-01       BEKymer    Remove DisableRemoteTerminal()
                                             Replace SerialPortChoice menu with RS232Selection menu
      1.100.1.9   08-21-01       BEKymer    Detab
      1.101       01-09-01       BEKymer    Added argument to TEXT and SUBMENU function calls and
      1.102       10-08-01       LAM        merged preset cleanup with 8.Specials
      1.103       10-12-01       LAM        removed unused posswitchmenu
      1.100.1.10  10-29-01       BEKymer    Fix bug in EnableSE46 (used wrong structure member)
      1.104       08-04-03       BEKymer    Merged 1.103 and 1.100.1.11 to create 1.104 for 9.00A build
                                            - Added 6000 watts
                                            - Removed 2500 watts
      1.105       09-16-03       BEKymer    Added User I/O menus, custom, switch logic to actuator settings                                      
      1.100.1.11.1.0 09-10-03    JOY        Added 'QVGASystemOptionsMenu'.
      1.100.1.11.1.1 10-16-03    JOY        MiddleSeg. is erased by ROM image.
      1.106       12-04-03       BEKymer    Merged (manually) 1.105 & 1.100.1.11.1.1 to 
                                             create 1.106 for build Ver9.00b
      1.107       12-09-03       BEKymer    Add SINT8 * TrimFillChar(SINT8 Str_temp[]);
                                             function prototype
                                            Remove Pres Correction option from
                                            User output list
      1.108       02-06-04      VSharma     Updated TOGGLE ExtPresets.
      1.109       02-20-04      VSharma     Modify struct related to User I/O & custom Actuator.
                                            Added 'QVGAUserIOMenu, in QVGASystemOptionsMenu.
                                            Moved enum INPUT_PINS to inports.h.
                                            Moved enum OUTPUT_PINS to outports.h.
                                            Added DEPOPasswordChoice.
      1.110       03-09-04      VSharma     Changed naming Convention for UserI/O variables.
      1.111       03-12-04      VSharma     Added GetInputPtr().
                                            Modified MoveInputSelection().
      1.113       04-06-04      VSharma     Modified MoveOutputSelection(). 
      1.114       04-19-04      VSharma     Modified struct of UserIOMenu.
                                            Added QVGAActIOMenu. 
      1.115       05-03-04      VSharma     Added input 'SyncIn' and output 'SyncOut'.
                                            Changed J3_2In to J3_1In.
                                            Changed 'ExtCycleAbort' to 'ExtTrigger'. 
      1.116       05-11-04      VSharma     Commented out TOGGLE 'Trg Sw'. 
      1.117       05-12-04      VSharma     Removed 'Trg Sw' from Custom menu.
      1.118       05-17-04      VSharma     Removed extern of unused strings.
      1.119       06-04-04      VSharma     Added DealWithExtPresetChange() & CheckForCustomAct().
      1.120       06-23-04      JOY         Modified ResetWeldCounter() & QVGAResetWeldCounter() 
                                            To take care ExtPresets also.
      1.121       06-24-04      BEKymer     Merged 1.118.1.0 with 1.120 to create
                                             1.21 for Ver9.00l build
      1.122       07-05-04      JOY         Added CheckDispLockConfigured().
      1.123       07-13-04      BEKymer     Create alternate structures to swap
                                             the text for J3-36 & J3-8 when new
                                             vs old system controller is installed
      1.124       07-27-04      JOY         Added _RADIO Freq60KHZ.
                                            Added 'Disabled' item in the output options.
      1.125       08-18-04      JOY         Added VARIABLE SVDelay.
      1.126       08-24-04      JOY         Added SUBMENU 'Factory Default'.
      1.127       10-04-04      BEKymer     Created UpdateAllUserOutputs() so
                                             output pin has proper value when 
                                             assigned or at power up.
      1.128       11-15-04      BEKymer     Change TOGGLE ExtPresets from Control
                                             level ea to level t
      1.129       07-25-05      Bwadia      Language Radiomenu modified to support Asian
                                            Languages.
                                            VGA exit and Save button added                                                                                   
      1.130       08-19-05      Bwadia      Topline only updated if system is in ready state
                                            when language is changed
      1.131       09-10-05      Bwadia      Cylinder length and stroke length print strings
                                            updated on language change   
      1.132       09-11-05      Aare        Merged 10f and 10h
      1.133       10-11-05      Bwadia      PS wattage Variable structure added instead of
                                            Radio item selection
      1.134       10-24-05      Bwadia      PS wattage radiomenu and radio items removed
                                            ALso removed GetPSWatts() and PutPSWatts()
      1.135       12-07-05      Bwadia      Tracker issue 3998 for displaying Metric decimal
                                            toggle button. Also this item is displayed when 
                                            Metric units are ON.
      1.136       12-20-05      Bwadia      Sequence printing related variable initialization
                                            Modified for Tracker issue 3976 
      1.128.1.1   12-07-05      BEKymer     Add PLC Control menu entry in Touch Screen
                                             system configuration menu                                  
      1.137       01-11-06      Bwadia      Merged BBraun_Final to Ver10_MH04
      1.138       01-20-06      Bwadia      MetricChoice TOGGLE item shown for AED|AEF Actuator
                                            Modified for tracker issue 4057      
      1.139       02-22-06      Bwadia      Modified for tracker issue 4087. Start screen toggle
                                            implemented differently for VGA and VFD                                               
      1.140       12-22-06      NHAhmed     Removed Decimal choice from System Config.
      1.141       01-31-07      NHAhmed     Changes related to Changed Structure variables of CHOICE and TOGGLE.
      1.142       04-24-07      NHAhmed     Removed DisplayStateMessage() from UpdateLanguage().
      2.143       06-52-07      NMAhmed     Moved WindowsSetup button to System Configuration Menu.
      2.144       10-22-07      NHAhmed     Changes done for LangTest phase 0
      2.145       01-11-08      NHAhmed     Some functions are replicated to a none argument type, 
                                            keeping all functionality same.
      2.146       04-14-08      NHAhmed     Renamed some functions.
      2.147       09-02-08      NHAhmed     CleanUp for multi-language support.    
      2.148       09-04-08      YGupta      CleanUp for LangTest Project.    
      2.149       09-09-08      NHAhmed     CleanUp for multi-language support.    
      2.150       09-12-08      NHAhmed     Removed unused functions; modified functions GetOutput() and 
                                            SetOutputSelection() and added function SetOutPinAccordtoBoard().
      2.151       10-01-08      NHAhmed     Merged Ver10.40 Changes.
      
      2.152		  02/13/14      HASanchez   The Default output signal overloard alarm was updated to low 

 ------------------------------- DESCRIPTION ---------------------------------
*/
 
/* This file will deal with System Options, such as language, beepers,     */
/* units, printer setup, etc.                                              */

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include <psos.h>
#include "time.h"
#include "menu.h"
#include "menu0.h"
#include "display.h"
#include "error.h"
#include "preset.h"
#include "param.h"
#include "psnvram.h"
#include "kpresmsg.h"             /* key pressed message definition   */
#include "selctkey.h"
#include "menupass.h"
#include "weld_obj.h"
#include "rtclock.h"
#include "menu7a.h"
#include "ready.h"
#include "alarms.h"
#include "keypad.h"
#include "getmsg.h"
#include "serial.h"
#include "graphs.h"
#include "menu4.h"
#include "statedrv.h"
#include "rdyweld1.h"
#include "qvgamenu.h"
#include "drawscrn.h"
#include "inports.h"
#include "outports.h"
#include "beep.h"
#include "digout.h"
#include "battram.h"

#include "command.h"
/* ----------------------------- EXTERNAL DATA ------------------------------ */

extern ALARM_MASKS AlarmPtrRam;
extern CONFIGSETUP CurrentSetup;
extern WELD_DATA FinalResults,WeldingResults;
extern UINT32  UILines;
extern UINT16  RadioIndex;
extern UINT16  WorkingPasswordFlag;

extern SETUPS_Ver800  CurrentPreset;
extern SETUPS_Ver800  RunningPreset;
extern RTC RTCMenu;
extern INBITS Inp; 
extern UINT16 GlobalCommandID;
extern UINT16 ForceFixedEnableFlag;              
extern UINT32 NackError, ErrorResponseMinLimit, ErrorResponseMaxLimit;
extern UNION_BOOL_UINT16 AmplitudeStepEnableFlag;
extern UNION_BOOL_UINT16 AmplitudeStepMicronsEnableFlag;
extern UINT16 AmplitudeFixedEnableFlag;

/*--------------------------- EXTERNAL FUNCTIONS ----------------------------*/

BOOLEAN* GetInputPtr(UINT16 InputBit);
void FormatRunScreenTopLine(void);

/*------------------------------ GLOBAL DATA --------------------------------*/
/*                     (scope is global to ALL files)                        */


UNION_BOOL_UINT16 AmpControlInternal;
UINT16 AmpCntrlExt;
UINT16 AmpCntrlInt;
UNION_BOOL_UINT16 FreqControlInternal;
UINT16 FreqControlExternal;
UINT16 FreqControlInt,EnableStepForce;
UINT16 LanguageChanged;
BOOLEAN VerifyPresetRequired = FALSE;
BOOLEAN DispLockConfigured;
UINT16 HHInactive1 =FALSE;

/* The following variable will be replaced by a legit variable later on */

SINT32 WelderAddrMinValue = 1;
SINT32 WelderAddrMaxValue = 9999;

SINT32 AmpMicronsMinValue = 1;
SINT32 AmpMicronsMaxValue = 200;

const SINT32 MinSVDelay  = 0;
const SINT32 MaxSVDelay  = 10000;
const SINT32 MinPSWatt = 100;
const SINT32 MaxPSWatt = 9999;

/*--------------------------- PRIVATE GLOBAL DATA ---------------------------*/
/*                     (scope is global to THIS file)                        */
   

enum INPUT_PINS ActiveInput;                      /* Contains enum of currently changing I/O */
enum OUTPUT_PINS ActiveOutput;                    /* Contains enum of currently changing I/O */
UINT16 GlobalInputs, GlobalOutputs;               /* Contains bit assignment for current I/O */
UINT16 OutputPin;
/*---------------------------------- CODE ----------------------------------*/


void GetInput(void)
/****************************************************************************/
/* Retrieve original selection for selected input based on CommandID        */
/* so menu can display the proper selection.                                */
/****************************************************************************/
{
     switch (GlobalCommandID) {
      case J3_32IN:
         GlobalInputs = CurrentSetup.J3_32In;
         break;
         
      case J3_33IN:
         GlobalInputs = CurrentSetup.J3_33In;
         break;
         
      case J3_19IN:
         GlobalInputs = CurrentSetup.J3_19In;
         break;
         
      case J3_17IN:
         GlobalInputs = CurrentSetup.J3_17In;
         break;
         
      case J3_31IN:
         GlobalInputs = CurrentSetup.J3_31In;
         break;
      
      case J3_1IN :
         GlobalInputs = CurrentSetup.J3_1In;
         break;
   }

    switch (GlobalInputs) {
      case INPUT_DISABLED:
         RadioIndex = 0;
         break;
         
      case INPUT_PRESET1:
         RadioIndex = 1;
         break;
         
      case INPUT_PRESET2:
         RadioIndex = 2;
         break;
         
      case INPUT_PRESET3:
         RadioIndex = 3;
         break;
         
      case INPUT_PRESET4:
         RadioIndex = 4;
         break;
      
      case INPUT_PRESET5 :
         RadioIndex = 5;
         break;

      case INPUT_EXT_TRIGDELAY:
         RadioIndex = 6;
         break;
         
      case INPUT_DISP_LOCK:
         RadioIndex = 7;
         break;
         
      case INPUT_EXT_TRIGGER:
         RadioIndex = 8;
         break;
         
      case INPUT_SONICS_DISABLE:
         RadioIndex = 9;
         break;
         
      case INPUT_MEM_RESET:
         RadioIndex = 10;
         break;
      
      case INPUT_SV_INTERLOCK :
         RadioIndex = 11;
         break;

      case INPUT_SYNC_IN:
         RadioIndex = 12;
         break;
    }
     
}

void SetInputSelection(void)
/****************************************************************************/
/* This function takes the current selection in GlobalInputs according to   */
/* RadioIndex and moves it to the proper Input register based on funcID.    */
/****************************************************************************/
{
   switch (RadioIndex) {
      case 0:
         GlobalInputs = INPUT_DISABLED;
         break;
         
      case 1:
         GlobalInputs = INPUT_PRESET1;
         break;
         
      case 2:
         GlobalInputs = INPUT_PRESET2;
         break;
         
      case 3:
         GlobalInputs = INPUT_PRESET3;
         break;
         
      case 4:
         GlobalInputs = INPUT_PRESET4;
         break;
      
      case 5 :
         GlobalInputs = INPUT_PRESET5;
         break;

      case 6:
         GlobalInputs = INPUT_EXT_TRIGDELAY;
         break;
         
      case 7:
         GlobalInputs = INPUT_DISP_LOCK;
         break;
         
      case 8:
         GlobalInputs = INPUT_EXT_TRIGGER;
         break;
         
      case 9:
         GlobalInputs = INPUT_SONICS_DISABLE;
         break;
         
      case 10:
         GlobalInputs = INPUT_MEM_RESET;
         break;
      
      case 11 :
         GlobalInputs = INPUT_SV_INTERLOCK;
         break;

      case 12:
         GlobalInputs = INPUT_SYNC_IN;
         break;
    }

   switch (GlobalCommandID) {
      case J3_32IN:      
         CurrentSetup.J3_32In = GlobalInputs;
         CurrentSetup.J3_32Ptr = GetInputPtr(GlobalInputs); 
         break;
         
      case J3_33IN:      
         CurrentSetup.J3_33In = GlobalInputs;
         CurrentSetup.J3_33Ptr = GetInputPtr(GlobalInputs);
         break;
         
      case J3_19IN:      
         CurrentSetup.J3_19In = GlobalInputs;
         CurrentSetup.J3_19Ptr = GetInputPtr(GlobalInputs);
         break;
         
      case J3_17IN:      
         CurrentSetup.J3_17In = GlobalInputs;
         CurrentSetup.J3_17Ptr = GetInputPtr(GlobalInputs);
         break;
         
      case J3_31IN:      
         CurrentSetup.J3_31In = GlobalInputs;
         CurrentSetup.J3_31Ptr = GetInputPtr(GlobalInputs);
         break;
         
      case J3_1IN: 
         CurrentSetup.J3_1In = GlobalInputs;
         CurrentSetup.J3_1Ptr = GetInputPtr(GlobalInputs);
         break;
   }
   VerifyPresetRequired = TRUE;   
}

void UpdateAllUserOutputs(void)
/****************************************************************************/
/*  This function will cycle through all user defind functions and adjust   */
/*  the output pin that is assigned to that function. This should be called */
/*  at power up and any time a pin is assigned to a different function or   */
/*  disabled.                                                               */
/****************************************************************************/
{
   UserCfgOutputOn  (OUTPUT_DISABLED     );
   UserCfgOutputOn  (OUTPUT_CFMPRESET    );
   UserCfgOutputOn  (OUTPUT_AMPDECAY     );
   UserCfgOutputOff (OUTPUT_EXT_BEEPER   );
   UserCfgOutputOn  (OUTPUT_CYCLE_OK     );
   UserCfgOutputOn  (OUTPUT_NO_CYCLEALARM);
   UserCfgOutputOff (OUTPUT_OLDALARM     );
   UserCfgOutputOn  (OUTPUT_MDFY_ALARM   );
   UserCfgOutputOn  (OUTPUT_NOTE         );
   UserCfgOutputOn  (OUTPUT_MISSING_PART );
   UserCfgOutputOff (OUTPUT_SV_INTERLOCK );
   UserCfgOutputOn  (OUTPUT_SYNC_OUT     );
}

void SetOutPinAccordtoBoard(void)
/****************************************************************************/
/* This function sets output pin according to new or old controller         */
/* board.                                                                   */
/****************************************************************************/
{
   if (CurrentSetup.SystemControllerFlag == TRUE)
   {
      if(GlobalCommandID == J3_36OUT)
         OutputPin = J3PIN8;
      else if (GlobalCommandID == J3_8OUT)
         OutputPin = J3PIN36;
      else
         OutputPin = J3PIN22;
   }
   else
   {
      if(GlobalCommandID == J3_8OUT)
         OutputPin = J3PIN8;
      else if (GlobalCommandID == J3_36OUT)
         OutputPin = J3PIN36;
      else
         OutputPin = J3PIN22;
   }
}

void GetOutput(void)
/****************************************************************************/
/* Retrieve original selection for selected output based on CommandID       */
/* so menu can display the proper selection.                                */
/****************************************************************************/
{
   SetOutPinAccordtoBoard();   
   switch (OutputPin) {
      case J3PIN36:
         GlobalOutputs = CurrentSetup.J3_36Out;
         break;
         
      case J3PIN8:
         GlobalOutputs = CurrentSetup.J3_8Out;
         break;
         
      case J3PIN22:
         GlobalOutputs = CurrentSetup.J3_22Out;
         break;
   }

   switch (GlobalOutputs) {
      case OUTPUT_DISABLED:
         RadioIndex = 0;
         break;
         
      case OUTPUT_CFMPRESET:
         RadioIndex = 1;
         break;
         
      case OUTPUT_AMPDECAY:
         RadioIndex = 2;
         break;
         
      case OUTPUT_EXT_BEEPER:
         RadioIndex = 3;
         break;
         
      case OUTPUT_CYCLE_OK:
         RadioIndex = 4;
         break;
      
      case OUTPUT_NO_CYCLEALARM :
         RadioIndex = 5;
         break;

      case OUTPUT_OLDALARM:
         RadioIndex = 6;
         break;
         
      case OUTPUT_MDFY_ALARM:
         RadioIndex = 7;
         break;
         
      case OUTPUT_NOTE:
         RadioIndex = 8;
         break;
         
      case OUTPUT_MISSING_PART:
         RadioIndex = 9;
         break;
         
      case OUTPUT_SV_INTERLOCK:
         RadioIndex = 10;
         break;
      
      case OUTPUT_SYNC_OUT :
         RadioIndex = 11;
         break;
      }
}


void SetOutputSelection(void)
/***************************************************************************/
/* This function takes the current selection in GlobalOutputs according to */
/* RadioIndex and moves it to the proper Output register based on funcID.  */
/***************************************************************************/
{
   switch (RadioIndex) {
      case 0:
         GlobalOutputs = OUTPUT_DISABLED;
         break;
         
      case 1:
         GlobalOutputs = OUTPUT_CFMPRESET;
         break;
         
      case 2:
         GlobalOutputs = OUTPUT_AMPDECAY;
         break;
         
      case 3:
         GlobalOutputs = OUTPUT_EXT_BEEPER;
         break;
         
      case 4:
         GlobalOutputs = OUTPUT_CYCLE_OK;
         break;
      
      case 5 :
         GlobalOutputs = OUTPUT_NO_CYCLEALARM;
         break;

      case 6:
         GlobalOutputs = OUTPUT_OLDALARM;
         break;
         
      case 7:
         GlobalOutputs = OUTPUT_MDFY_ALARM;
         break;
         
      case 8:
         GlobalOutputs = OUTPUT_NOTE;
         break;
         
      case 9:
         GlobalOutputs = OUTPUT_MISSING_PART;
         break;
         
      case 10:
         GlobalOutputs = OUTPUT_SV_INTERLOCK;
         break;
      
      case 11 :
         GlobalOutputs = OUTPUT_SYNC_OUT;
         break;
      }
   SetOutPinAccordtoBoard();
   switch (OutputPin) {
      case J3PIN36:
         CurrentSetup.J3_36Out = GlobalOutputs;      
         break;
         
      case J3PIN8:      
         CurrentSetup.J3_8Out = GlobalOutputs;      
         break;
         
      case J3PIN22:      
         CurrentSetup.J3_22Out = GlobalOutputs;      
         break;
   }
   UpdateAllUserOutputs();
   VerifyPresetRequired = TRUE;  
}

void GetPSFreq(void)
{
   switch (CurrentSetup.PSFreq)
   {
      case FREQ15KHZ:
         RadioIndex = 0;
         break;
      case FREQ20KHZ:
         RadioIndex = 1;
         break;
      case FREQ30KHZ:
         RadioIndex = 2;
         break;
      case FREQ40KHZ:
         RadioIndex = 3;
         break;
      case FREQ60KHZ:
         RadioIndex = 4;
         break;   
      default:
         RadioIndex = 1;
         break;
   }
}

void SetPSFrequency(void)
{
   switch( RadioIndex )
   {
      case 0:
         CurrentSetup.PSFreq = FREQ15KHZ;
         break;
      case 1:
         CurrentSetup.PSFreq = FREQ20KHZ;
         break;
      case 2:
         CurrentSetup.PSFreq = FREQ30KHZ;
         break;
      case 3:
         CurrentSetup.PSFreq = FREQ40KHZ;
         break;
      case 4:
         CurrentSetup.PSFreq = FREQ60KHZ;
         break;
      default:
         CurrentSetup.PSFreq = FREQ20KHZ;
         break;
   }
   StorePSFrequency();
   SetMaxMinValues();           /* Update Min/Max based on new setting */
}

void GetRS232Index(void)
/*****************************************************************************/
/*  This function will convert the bit assignment in CurrentSetup.SerialPort */
/*  to an index so the proper selection will be displayed when RADIOMENU is  */
/*  called.                                                                  */
/*****************************************************************************/
{
   switch(CurrentSetup.SerialPort)
   {
      case COMPUWELD:
         RadioIndex = 0;
         break;
         
      case TERMINAL:
         RadioIndex = 1;
         break;

      case ASCIICOMMA:
         RadioIndex = 2;
         break;

      case ASCIITAB:
         RadioIndex = 3;
         break;

      case ASCIISPACE:
         RadioIndex = 4;
         break;
         
      case RS232DISABLED:
         RadioIndex = 5;
         break;
   }
}

void SetAmpControlValue(void)
{
   if (CurrentSetup.AmpControl == FALSE)   /* FALSE if external control */
   {
      AmpControlInternal.bool = FALSE;
      AmpCntrlExt = TRUE;
      VerifyPresetRequired = TRUE;
      AmpCntrlInt = FALSE;
      AmplitudeFixedEnableFlag = FALSE;
      AmplitudeStepEnableFlag.bool = FALSE;
      AmplitudeStepEnableFlag.uint16.Hi = FALSE;
      AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
      AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE;
   }
   else
   {
      if((CurrentPreset.Amp2Flag & BIT0) == TRUE)
      {
         AmplitudeFixedEnableFlag = FALSE;
         AmplitudeStepEnableFlag.bool = TRUE;
         AmplitudeStepEnableFlag.uint16.Hi = TRUE;
         AmplitudeStepMicronsEnableFlag.uint16.Hi = TRUE;
         AmplitudeStepMicronsEnableFlag.uint16.Low = TRUE;
      }
      else
      {
         AmplitudeFixedEnableFlag = TRUE;
         AmplitudeStepEnableFlag.bool = FALSE;
         AmplitudeStepEnableFlag.uint16.Hi = FALSE;
         AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
         AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE;
      }
      AmpControlInternal.bool = TRUE;
      AmpCntrlExt = FALSE;
      AmpCntrlInt = TRUE;
   }

   if(CurrentSetup.AmpMicronsFlag==TRUE)
   {
	  AmpCntrlInt = FALSE;
	  AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE;
   }
   else
   {
	  AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
   }
}

void SetAmpControl(void)
{
   if (CurrentSetup.AmpControl == FALSE)   /* FALSE if external control */
    {
      AmpControlInternal.bool = FALSE;
      AmpCntrlExt = TRUE;
      VerifyPresetRequired = TRUE;
      AmplitudeFixedEnableFlag = FALSE;
      AmplitudeStepEnableFlag.bool = FALSE;
      AmplitudeStepEnableFlag.uint16.Hi = FALSE;
      AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
      AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE;
    }
   else
    {
      if((CurrentPreset.Amp2Flag & BIT0) == TRUE)
      {
         AmplitudeFixedEnableFlag = FALSE;
         AmplitudeStepEnableFlag.bool = TRUE;
         AmplitudeStepEnableFlag.uint16.Hi = TRUE;
         AmplitudeStepMicronsEnableFlag.uint16.Hi = TRUE;
         AmplitudeStepMicronsEnableFlag.uint16.Low = TRUE;
      }
      else
      {
         AmplitudeFixedEnableFlag = TRUE;
         AmplitudeStepEnableFlag.bool = FALSE;
         AmplitudeStepEnableFlag.uint16.Hi = FALSE;
         AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
         AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE;
      }
      AmpControlInternal.bool = TRUE;
      AmpCntrlExt = FALSE;
      if(CurrentSetup.AmpMicronsFlag==TRUE)AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE; else AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
    }
}

void SetFreqControlValue(void)
{
   if (CurrentSetup.FreqControl == FALSE)  /* FALSE if external control */
   {
      FreqControlInternal.bool = FALSE;
      FreqControlExternal = TRUE;  /* Menu needs this to display >Ext line */
      FreqControlInt = FALSE;
   }
   else
   {
      FreqControlInternal.bool = TRUE;
      FreqControlExternal = FALSE;
      FreqControlInt = TRUE;
   }

}
void SetFreqControl(void)
{
   if (CurrentSetup.FreqControl == FALSE)  /* FALSE if external control */
   {
      FreqControlInternal.bool = FALSE;
      FreqControlExternal = TRUE;  /* Menu needs this to display >Ext line */
   }
   else
   {
      FreqControlInternal.bool = TRUE;
      FreqControlExternal = FALSE;
   }
}

void ProduceBeep(void)
{
   if(GlobalCommandID == AMP_CNTL_SET)
      CurrentSetup.AmpControl = FALSE;
   if(GlobalCommandID == FREQ_CNTL_SET)
      CurrentSetup.FreqControl = FALSE;
   
   NackError = WELDER_PROCESS_ERROR;
   ErrorResponseMinLimit = ACCESS_NOT_ALLOWED;
   ErrorResponseMaxLimit = 0;
}




void DealWithExtPresetChange(void)
/****************************************************************************/
/*                                                                          */
/* This function Update the 'SWConfiguration' for external preset selection */
/* on powerup or when the ExtPreset value is changed.                       */
/*                                                                          */
/****************************************************************************/
{
   if (CurrentSetup.ExtPresets)
      UpdateSWConfiguration(EP_E, TRUE);  /* ExtPreset enabled */
   else
      UpdateSWConfiguration(EP_E, FALSE); /* ExtPreset disabled */
   
}


void UpdateRunTopLine(void)
/****************************************************************************/
/*                                                                          */
/* Issues a call to UpdateCurrentPreset(), which will cause the top line of */
/* the run screen to be updated.  This function is called when Units are    */
/* changed, because this affects what's shown on the run screen.  The Weld  */
/* Manager is responsible for updating this text, so we have to get an      */
/* OP_HERE_IS_PRESET sent to it, even though the preset itself hasn't       */
/* actually changed.                                                        */
/*                                                                          */
/****************************************************************************/
{
   UpdateCurrentPreset(WELDMODE, 0, 0);
}                                      

void QVGAResetWeldCounterOk(void)
/****************************************************************************/
/*Description:                                                              */
/*  Refresh the Weld counter variable in case of pressing Ok button on the  */
/*  Confirm Screen.                                                         */
/****************************************************************************/
{
   extern SINT32 SPresetValue;
   extern SINT32 WHistoryValue;
   extern SINT32 WSummaryValue;
   extern SINT32 PGraphValue;
   extern SINT32 AGraphValue;
   extern SINT32 FGraphValue;
   extern SINT32 DGraphValue;
   extern SINT32 AbsGraphValue;
   extern SINT32 VGraphValue;
   extern SINT32 ForGraphValue;
   extern SINT32 SequenceValue;
   extern SINT32 ExtSampleCount;

   /* Init Print on Sample rotation counters */
   SPresetValue = 0;
   WHistoryValue = 0;
   WSummaryValue = 0;
   PGraphValue = 0;
   AGraphValue = 0;
   FGraphValue = 0;
   DGraphValue = 0;
   AbsGraphValue = 0;
   VGraphValue = 0;
   ForGraphValue = 0;
   SequenceValue = 0;
   ExtSampleCount = 0;

   WeldingResults.CycleCount = 0;
   CurrentPreset.WeldCount = 0;
   

 
}

void SetBeeperCondition (void)
{
   if(CurrentSetup.HandHeld == TRUE)
      HHInactive1 = FALSE;
   else
      HHInactive1 = TRUE;
}

BOOLEAN* GetInputPtr(UINT16 InputBit)
/********************************************************************/
/*  This funtion will return a pointer to the member of INBITS      */
/*  structure, selcted on the input pin.This function will be called*/ 
/*  when the input is defined to the port pin.                      */
/********************************************************************/
{
 	BOOLEAN *RetVal;

    switch (InputBit)
    {
        case INPUT_DISABLED:
           RetVal = &Inp.BitBucket;
           break;
        case INPUT_PRESET1:
        /* If 'Select Preset1' is selcted to J3_32 port pin.*/
           RetVal = &Inp.Preset1;
           break;
        case INPUT_PRESET2:
        /* If 'Select Preset2' is selcted to J3_33 port pin.*/
           RetVal = &Inp.Preset2;
           break;       
        case INPUT_PRESET3:
        /* If 'Select Preset4' is selcted to J3_19 port pin.*/
           RetVal = &Inp.Preset4;
           break;       
        case INPUT_PRESET4:
        /* If 'Select Preset8' is selcted to J3_17 port pin.*/
           RetVal = &Inp.Preset8;
           break;       
        case INPUT_PRESET5:
        /* If 'Select Preset16' is selcted to J3_31 port pin.*/
           RetVal = &Inp.Preset16;
           break;       
        case INPUT_EXT_TRIGDELAY:
        /* Return External Trigger Delay pointer */
           RetVal = &Inp.ExtTrgDelay;
           break; 
        case INPUT_DISP_LOCK:
        /* Return DisplayLock pointer */
           RetVal = &Inp.DisplayLockFlag;
           break;     
        case INPUT_EXT_TRIGGER:
        /* Return External Trigger pointer. */
           RetVal = &Inp.ExternalTrigger;
           break;
        case INPUT_SONICS_DISABLE:
        /* Return SonicDisable pointer*/
           RetVal = &Inp.SonicDisable;
           break;
        case INPUT_MEM_RESET:
        /* Return Menmory Reset pointer. */
           RetVal = &Inp.MemReset;
           break;     
        case INPUT_SV_INTERLOCK:
        /* Return SVInterlock pointer. */
           RetVal = &Inp.SVInterLock;
           break;
        case INPUT_SYNC_IN:
        /* Return SVInterlock pointer. */
           RetVal = &Inp.SyncIn;
           break;  
      }
      DispLockConfigured = IsConfigured(INPUT_DISP_LOCK);
      return (RetVal);
}

void CheckForCustomAct (void)
/****************************************************************************/
/* This function Update the 'CustomAct' when the UpperLimitSwitch or Ground */
/* DetectSwitch default logic level(0V) is inverted to 24V.                 */
/****************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   if((CurrentSetup.ULSLogicCustom) &&  /* Check for ULS & GndDet default logic level.*/
      (CurrentSetup.GndDetLogicCustom))
      CurrentSetup.CustomAct = FALSE;/* Custom actuator is not configured. */
   else
      CurrentSetup.CustomAct = TRUE; /* Custom actuator is configured. */
   BBRPtr->CustomAct = CurrentSetup.CustomAct;
}
                                   
/**************************************************************************/
/*===============================END =====================================*/
/**************************************************************************/


