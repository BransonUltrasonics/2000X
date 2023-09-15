/* $Header:   D:/SWLab/VMdb/2000Series/App/MENU0.C_V   2.76.1.3.1.5   09 Sep 2008 20:39:58   nhahmed  $ */
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

   Filename: menu0.c   

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #      Date         Author       Description
   ==========     ========      ======       ===========
      0                                      Initial Version
      1.00        04/29/96       PJ          Modified for PSOS version
      2.00        05/14/96       PJ          Deleted menu1.h
                                             Strings in menutext.c
      3.00        06/20/96       PJ          Enabled Systems Configuration
                                             Menu.
      3.01        07/16/96       PJ          Changed WeldModeSetup Menu to
                                             WeldModeSelectMenu.
      3.02        07/16/96       LAM         added functions to submenu
                                             extry and exit                                                      
      3.03        07/16/96       PJ          Changed submenu address and added
                                             function to submenu WeldSetupChoice
      3.10        08/14/96       PJ          Enabled Preset Menu
      3.11        08/15/96       PMG         Enabled Printing Menu   
      3.12        08/22/96       PJ          Changed name of function from
                                             ClearWeldModeSelectFlag to
                                             ClearDisplayBlankFlag
      3.13        09/04/96       PJ          RunScreenChoice function now
                                             GetCurrentWeldData was
                                             DisplayCurrentPreset.
      3.14        09/18/96       PJ          Added function ClearRunScreenFlag to
                                             RunScreenChoice menu.
      3.15        09/19/96       PJ          Deleted ClearDisplayBlankFlag
                                             function.
      3.16        10/09/96       PhilJ       Changed Menus to type const. 
      3.17        10/10/96       PaulG       Added PrintingDisplay function to
                                             PrintingMenu.
      3.18        10/11/96       PhilJ       Added AlarmScreenMenu for debugging.
      3.19        10/15/96       PhilJ       Removed AlarmScreenMenu.
      3.20        10-16-96       BEKymer     Remove Branson choice from menu
      3.21        10/29/96       PhilJ       Temporary change to Security levels.
      3.22        10/30/96       PhilJ       Removed temporary changes.
      3.30        11/01/96       PhilJ       Added GetSystemInfo function to
                                             SystemTypeChoice menu.
      3.40        01/07/97       PhilJ       Changed function name from
                                             GetActuatorType to LoadactuatorType.
      4.00        01-28-97       LAM         deleted unused vars
      4.10        03/03/97       PhilJ       Added GetSerialNumber function to
                                             to GetSystemInfo.
      2.27        07/10/97       PhilJ       Changed PresetChoice to LEVEL_e.
      2.28        07.23.97       JBerman     Removed "20" from StrM8_1111[20]
      2.29        07.24.97       PhilJ       Chngd Model in PresetsChoice from
                                             LEVEL_e to LEVEL_t
      2.30        07.28.97       PhilJ       Added functions to execute to
                                             WeldSetupChoice menu.
      2.31        08/18/97       PhilJ       Chngd PrintChoice secrity level to
                                             OPERATOR.
      2.32        09.04.97       JBerman     Replaced ADVANCED with NORMAL
      2.33        10.15.97       LAM         added set & clear diagflag    
      2.34        10/21/97       BJB         Upgraded print menu to MAINTAINENCE
                                              level
      2.35        10.27.97       LAM         moved set & clear diagflag to menu5
      2.36        11-4-97        BJB         Fixed definitions of external menus.
      2.37        12-10-97       BJB         Initializes WorkingPasswordFlag in
                                              SetupOptions so it shows up right
                                              on the display.
      2.38        12-11-97       KGD         Fixed DCS 1091.
      2.39        03-03-98       BJB         Put Diagnostics screen directly off
                                              Main Menu, removed from calibration
                                              menu.
                                             Moved Calibration menu choice to end
                                              of Main Menu.
                                             Updated MODEL of PresetsChoice to
                                              LEVEL_e.
      2.40        04.17.98       LAM         made calibration menu encoder flag = TRUE
      2.41        05.22.98       LAM         made calibration menu aed | aef
      2.42        06.24.98       BJB         Changed NORMAL to BASIC.
      2.43        06.25.98       BJB         SystemOptionsChoice changed so that
                                              InitCopyFeaturesSetting() called before
                                              menu displayed, necessary to set up
                                              CopyFeaturesSetting, displayed on
                                              "Features" line.     
      2.44        06.26.98       JBerman     CommentOut: LoadActuatorType,
                                              it will be determind in UTUL.c
      2.45        06.26.98       BJB         Moved call to InitCopyFeaturesSetting()
                                              to SetupOptions() so it is called
                                              BEFORE sys config menu.
      2.46        07.30.98       BJB         Calls LoadActuatorType() again from
                                              GetSystemInfo().
      2.47        10-01-99       JZ          change GetSystemInfo() and SetupOptions() to static
      2.48        10-26-99       JZ          modified SetupOptions()
      2.48.6.1    02-07-99       JZ          removed DVS and added Mask1, Cond1, Mask2, Cond2
      2.48.6.2    02-23-00       OFI         removed 'User experiencelevel' from menu structs and deleted unused
                                             InitCopyFeaturesSetting().
      2.49        04-05-00       JZ          merged Lang to trunk
      2.50        05-26-00       SCM         Checked in for testing by Laura, John.
      2.51        06-02-00       SCM         Added GetDUPSInfo() function.
      2.52        06-09-00       SCM         Changed the model on SUBMENU PresetsChoice
                                             to LEVEL_t.
      2.53        06-12-00       LAM         added DEPOT masks                                       
      2.54        06-14-00       SCM         Added the two DEPOT menu structures.
      2.55        06-15-00       SCM         Changed Mask2 and Cond2 values for the RunScreen structure.
      2.56        06-28-00       BEKyme/DJL  Changed all MODEL to LEVEL and fixed SETUPS
      2.57        08-16-00       LAM         disabled depo option
      2.58        08-28-00       LAM         reenabled depo option
      2.58.1.0    09-06-01       BEKymer     Add View Setup entry to main menu
      2.59        01-08-01       BEKymer     Added argument to function call for TEXT and
                                              SUBMENU structures.
      2.60        10-08-01       LAM         merged preset cleanup with the view setup menu
      2.61        09-16-03       BEKymer     Added View Setup menu
      2.62        12-02-03       BEkymer     Merged 2.61 & 2.58.3.3 to create
                                              2.62 for Ver9.00b build
      2.63        12-10-03       BEKymer     Add in missed 'const MENU QVGATheMainMenu'
      2.64        02-25-04       VSharma     Changed 'QVGATheMainMenu'.
                                             Added QVGABransonDefaultMenu.
      2.65        05-17-04       VSharma     Removed extern of unused strings.                                        
      2.66        07-07-04       BEKymer     Added code for factory default menus.
      2.67        08-24-04       JOY         Moved defines to the menu0.h file.
      2.68        07-25-05       Bwadia      Maded changes to support Factory default menu 
                                             for VGA 
      2.69        08-19-05       Bwadia      IsHWConfigured function used to check for 
                                             VGA Hardware present
      2.70        10-11-05       Bwadia      USB parameter default values function call
                                             added when GLOBAL default selection is done.
                                             Weld History menu added
      2.71        10-24-05       Bwadia      SBC version string function call when 
                                             entering system information screen
      2.72        10-28-05       Bwadia      Sequening submenu added to main menu                                        
      2.73        01-05-06       LAM/BEKymer Merged BBRaun Special Add "Print Now" to main menu
      2.74        01-12-06       Bwadia      VGA WIndows setup button added. Main menu
                                             rearranged. Modified for tracker issue 4042                    
	  2.75        03-22-06       Bwadia      VGA View Current Setup is a VGABUTTON
	  2.76        03-24-06       Bwadia      Modified View current setup button to 
	                                         GRAPH type 
      2.76.1.1    04-03-07       LAM         Removed ">" from Weld History, password
                                             protect windows setup                                       
      2.76.1.2    04-12-07       NHAhmed     Added View Quality Screen to Main Menu.
      2.76.1.3    05-23-07       NHAhmed     Added a dummy Submenu pointer to the Window Setup Structure.
      2.76.1.4    06-52-07       NMAhmed     Moved WindowsSetup button to System Configuration Menu.
      2.77        10-22-07       NHAhmed     Changes done for LangTest phase 0
      2.78        01-11-08       NHAhmed     Some functions are replicated to a none argument type, 
                                             keeping all functionality same.
      2.79        04-14-08       NHAhmed     Renamed some functions.
      2.80        09-02-08       NHAhmed     CleanUp for multi-language support. 
      2.81        09-04-08       YGupta      CleanUp for LangTest Project.
      2.82        09-09-08       NHAhmed     CleanUp for multi-language support. 
 ------------------------------- DESCRIPTION ---------------------------------
*/

      /* This file will deal with the Main Menu, top level only. */


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "menu.h"
#include "menu0.h"
#include "menu1.h"
#include "menu2.h"
#include "menu4.h"
#include "menu6.h"
#include "menu7.h"
#include "error.h"
#include "keypad.h"
#include "selctkey.h"
#include "state.h"
#include "statedrv.h"
#include "preset.h"
#include "weld_obj.h"
#include "rtclock.h"
#include "getmsg.h"
#include "qvgamenu.h"
#include "qvga_task.h"
#include "command.h"

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern SETUPS_Ver800 CurrentPreset;
extern CONFIGSETUP CurrentSetup;


extern UINT16 WorkingPasswordFlag;

extern CONFIRM_SCREEN_TYPE ConfirmType;

extern BOOLEAN QVGAHwAvail;
extern UINT16 GlobalCommandID;

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/
/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/
RTC RTCMenu;

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

MENUEND endlist0 = { TRUE };
static UINT32 DefaultSelection;
static UINT16 EnableUserIOCaution;
static UINT16 EnableActuatorCaution;
static UINT16 EnableBBRCaution;
static UINT16 EnablePrintingCaution;
static UINT16 EnableTouchScreenCaution;
static UINT16 EnableGlobalCaution;


/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/

void GetDebugValues(void);
void GetCalData(void);
void GetSBCVersion(void);
/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

/*
 ---------------------------------- CODE -------------------------------------
*/



void SetupOption(void)
{
   RTCMenu = RtcReadDateandTime();
   WorkingPasswordFlag = CurrentSetup.PassWordFlag;
}


void SelectProperDefault(UINT32 Default)
{
   DefaultSelection = Default;
   EnableUserIOCaution = FALSE;
   EnableActuatorCaution = FALSE;
   EnableBBRCaution = FALSE;
   EnablePrintingCaution = FALSE;
   EnableGlobalCaution = FALSE;
   switch (Default) {
      case USERIO:            /* Put all user I/O back to factory default */
         EnableUserIOCaution = TRUE;
         break;
      case ACTUATOR:          /* Restore actuator switches back to default*/
         EnableActuatorCaution = TRUE;
         break;
      case BBR:               /* Initialize alarms, trig force in BBR     */
         EnableBBRCaution = TRUE;
         break;
      case PRINTING:          /* Turn off all print on sample & alarm     */
         EnablePrintingCaution = TRUE;
         break;
      case GLOBAL:            /* Do all of the above                      */
         EnableGlobalCaution = TRUE;
         break;
   }   
   
}   

void OkToDefault(void)
/**************************************************************************/
/*                                                                        */
/*   A return to factory setting has been selected.  The Global variable  */
/*   DefaultSelection contains the define for which selection.            */
/*                                                                        */
/**************************************************************************/
{
   switch (GlobalCommandID)
   {
   case RESTORE_USERIO:     /* Put all user I/O back to factory default */
      SetUserIOToFactoryDefault();
      break;

   case RESTORE_ACTUATOR:   /* Restore actuator switches back to default*/
      SetActuatorSwitchesToFactoryDefault();
      break;

   case RESTORE_BBR:   /* Initialize alarms, trig force in BBR     */
      SetBucMenuToFactoryDefault();
      break;

   case RESTORE_PRINTING:   /* Turn off all print on sample & alarm     */
         SetPrintingToFactoryDefault();
      break;

   case RESTORE_GLOBAL:   /* Do all of the above                      */
      SetUserIOToFactoryDefault();
      SetActuatorSwitchesToFactoryDefault();
      SetBucMenuToFactoryDefault();
      SetPrintingToFactoryDefault();
      SetUSBToFactoryDefault();
      break;
   }
}

void CancelDefaults(UINT32 MenuExtra)
/**************************************************************************/
/*                                                                        */
/*   Setting factory defaults has been canceled.  This means there is     */
/*   really nothing to do.  Just return back to the original menu.        */
/*                                                                        */
/**************************************************************************/
{
   SendFakeKeyPress(GoBackKey);
}

void RestoreDefaultConfirmScrn(UINT32 Default)
/****************************************************************************/
/*Description:                                                              */
/* Draws Restore Defaults Confirmation  Screen.                             */
/****************************************************************************/
{
   
   DefaultSelection = Default;
   
}

//void QVGARestoreDefaultsOK(void)
/**************************************************************************/
/*                                                                        */
/*   A return to factory setting has been selected.  The Global variable  */
/*   DefaultSelection contains the define for which selection.            */
/*                                                                        */
/**************************************************************************/
//{
//   switch (DefaultSelection) {
//      case USERIO:            /* Put all user I/O back to factory default */
//         break;
//      case ACTUATOR:          /* Restore actuator switches back to default*/
//         break;
//      case BBR:               /* Initialize alarms, trig force in BBR     */
//         break;
//      case PRINTING:          /* Turn off all print on sample & alarm     */
//         break;
//      case GLOBAL:            /* Do all of the above                      */
//         break;
//   } 
//}


//static void QVGAGetSystemInfo(void)
//{
//  GetPowerSupplyInfo();
//  LoadActuatorType();
//  GetControlLevel();
//  GetSerialNumbers();
//  GetDUPSInfo();
//  GetCalData();
//}


//static void SetupOptions(void)
//{
//   RTCMenu = RtcReadDateandTime();
//   WorkingPasswordFlag = CurrentSetup.PassWordFlag;
//}


const MENU TheMainMenu[]    = { {&endlist0,                  ENDLIST}  };
