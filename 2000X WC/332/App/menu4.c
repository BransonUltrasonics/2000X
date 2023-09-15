/* $Header:   D:/databases/VMdb/2000Series/App/MENU4.C_V   1.195   08 Mar 2011 02:57:44   PDwivedi  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                           */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

/*---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   
   Filename: menu4.c
   

   Function Names:   
                     
                     
 

-------------------------------- REVISIONS -----------------------------------

   Revision #  Date      Author  Description
   ==========  ========  ======  ===========
   0                             Initial Version                     
   1.00        08-15-96  PaulG   Original write of code
   1.01        08-15-96  PaulG   Disabled PresetDataFunc
                                 until psos sprintf function
                                 and stdprn problem resolves
   1.02        08-20-96  PaulG   Converted PrintSample and PrintAlarm from
                                  TOGGLE to CHOICE.
                                  Also added local variable
                                  GlobalSample and GlobalAlarm to store
                                  return values for above structs.
   1.03        09-10-96  PaulG   Added q_send to send printer msg.     
   1.04        09-11-96  PaulG   Activated Graph printing functions.
   1.05        10-10-96  PhilJ   Changed menus to type const.
   1.06        10-19-96  PaulG   Added new function PrnMgrONOFFFunc
                                 and PrnMgrAbortFunc.
   1.07        10-21-96  PaulG   Changed security level from Branson
                                 MAINTAINENCE on Submenus and OPERATOR
                                 on all others.
   1.08        11-01-96  PaulG   Added GoBackFlag to enable printer functions. 
   1.09        11-13-96  PaulG   Added PrinterDisplay functionality to PrintONOFF.
   1.10        11-15-96  PaulG   Added SetPrinterFlags to initialize.
   1.11        11-20-96  PaulG   Added GlobalSampleFlag and GlobalAlarmFlag.   
   1.12        11-22-96  PaulG   Modified TestPrintONOFFunc.
   1.13        12-10-96  PaulG   Added PrintAnyway flag.
   1.14        12-12-96  PhilJ   Changed UPDATEDISP to UPDATEDISPLAY.
   1.15        12-12-96  PaulG   Updated PrnMgrAbortFunc.
   1.16        12-19-96  PaulG   Updated PrintOnAlarm for Frequency and velocity.
   1.17        01-06-97  PaulG   Updated q_send to CkQSend.
   1.18        01-09-97  PaulG   Added flag to check for CONTINUOUSMODE.    
   1.19        01-28-97  PaulG   Modified text from Weld History Graph to Last 50 welds.    
   1.20        01-31-97  PaulG   Modified PrinterEpson.    
   1.21        02-21-97  PaulG   Added "Busy" message if printer ic active.    
   1.22        04-11-97  PhilJ   Added PrintTimeModeScaling and PrinterScaling
                                 to PrinterMenu..    
   1.23        04-16-97  PhilJ   Added XAutoScaling and PrinterScaling menus.
   1.24        04-18-97  PaulG   Added "ERROR" string for printer status.
   1.25        04-25-97  PhilJ   Corrected bug selecting Printer.
   1.26        05-02-97  PhilJ   Changed delay times to 2 seconds.
   1.27        05-05-97  PhilJ   Added CheckPrinterFull to WeldHistoryFunc
                                 and WeldSummaryFunc. Moved AutoScaling
                                 and PrinterScaling menus under Print Item.
   1.28        05-13-97  PhilJ   Restructured Print menu per DCS#1672.
   1.29        05-15-97  LAM     fixed global printing                       
   1.30        05-22-97  PaulG   Added OkiData ML  printer.                       
   1.31        05-30-97  PaulG   Removed CheckPrintFull var.                       
   1.32        05-30-97  PaulG   Replaced GlobalSampleFlag and GlobalAlarmFlag
                                 with GlobalPrinting.                       
   2.00        06-06-97  LAM     cleanup
   2.1.49      06-11-97  LAM     removed velocity graph
   2.1.50      06-18-97  PaulG   Restructure Print Menu
   2.1.51      06-19-97  PaulG   Restructure Global Printing.
   2.1.52      06-20-97  PhilJ   Changed PAGELENGTH param Id to PAGESIZE.
                                 Changed SETUPSTUFF to FORMFEED.
   2.1.53      06-20-97  PaulG   Changed Printing preset string.
   2.1.54      06-27-97  PaulG   Changed Print menu.
   2.1.56      07-01-97  LAM     added uilines extern,deleted bargraph
   2.1.57      07-03-97  PaulG   Modified Weld Data message.
   2.1.58      07-17-97  PaulG   Changed function name to FormFeedPage.
   2.1.59      07-21-97  PaulG   Remove function SetPrinterFlags
   2.1.60      07-23-97  JBerman StrM8_1111[20] -> StrM8_1111[LINESIZE+1] 
   2.1.61      07-30-97  PaulG   When Abort occurs pause 2 seconds.
   2.1.63      08-11-97  PhilJ   Chgd Security Level of all menus to OPERATOR.
   2.1.64      08-23-97  PaulG   Removed HP LaserJet AND HP InkJet from menu.
   2.1.65      08-29-97  PaulG   Modified Abort function.
   2.1.66      09-02-97  PaulG   Modified Abort function.
   2.1.67      09.04.97  JBerman Replaced ADVANCED with NORMAL
   2.1.68      09-04-97  PaulG   Removed AbortPrintingFlag.
   2.1.69      09-09-97  PaulG   Cleanup data.
   2.1.70      09-16-97  PaulG   Modified Print Menu.
   2.1.71      09-17-97  PaulG   Modify when Print Offline gets displayed.
   2.1.72      09-18-97  PaulG   Modify PrintOnSample functions.
   2.1.73      09-29-97  PaulG   Added PrinterDisplay to menus.
   2.1.74      09-30-97  PaulG   Execute ExecuteEmulateMode()  when printer mode is changed.
   2.1.75      10-03-97  PaulG   Modified PrintingGraphFlag.
   2.1.75      10.03.97  JBerman Expended RADIOMENU  to 12 items
   2.1.76      10-07-97  PaulG   Added Abort Printing to menu in level 1
   2.1.77      10-16-97  PaulG   Added WeldCounter to reset during abort printing.
   2.1.78      10-17-97  PaulG   Modified LEFT30 to LEFT10
   2.1.79      10-24-97  PaulG   Added function PoweredOffCheckFunc().
   2.1.80      10-28-97  PaulG   Modified function CheckPrintingStatus(),
                                 alse added PrintAnyway flag.
   2.1.83      11-06-97  BJB     Includes display.h, led.h, getmsg.h
                                 Created function AbortPrinting() to produce
                                 Abort Printing screen, doesn't do this with
                                 SUBMENU.
                                 ContinueAbortFunc() resets flags even if printer
                                 is offline or powered off.
                                 AbortCurPrint[] changed from SUBMENU to TEXT.
   2.1.84      11-10-97  PaulG   Modified function CalMaxWeldsPerPage(), added code
                                 to resent page size to printer.
   2.1.85      11-10-97  BJB     Clears keypad buffer in AbortPrinting() after
                                 displaying menu instead of before.  Also added
                                 delay before clearing buffer.
   2.1.86      11-11-97  PaulG   Added a sec to delay on conflict message for weldsPerPage.
   2.1.87      11-11-97  LAM     chged checkprintstatus                                     
   2.1.88      11-11-97  PaulG   Added PrintingGraphFlag to Continue().
   2.1.89      11-17-97  LAM     deleted unused checkprintstatus                                     
   2.1.90      11-17-97  PaulG   Removed AbortPrinting flag from ContinueAbortFunc().   
   2.1.91      11-18-97  PaulG   Added AbortPrintingFlag in ContinueAbortFunc();
   2.1.92      11-19-97  LAM     removed printfinalresults
   2.1.93      11-20-97  PaulG   Removed PrinterEnabled flag.
   2.1.94      11-30-97  Greitmay????????????????????????????
   2.1.95      11-30-97  PaulG   Modify Abort printing function.
   2.1.96      12-01-97  BJB     Makes GetMsgFlag FALSE during AbortPrinting()
                                 screen.
   2.1.97      12-2-97   KGD     Added GetPrinterInfo to fix DCS1083.; fix for dcs1010
   2.1.98      12-4-97   BJB     Converted PrinterSelectionMenu items to RADIO.
   2.1.99      12-05-97  PaulG   Check is Points are collected, if not display message.
   2.1.100     12-10-97  PaulG   Added DontPrintGraph to check if cycle was aborted.
   2.1.101     12-11-97  PaulG   Modify string for message printed out on screen.
   2.1.102     12-12-97  PaulG   Changed DontPrintGraph to extern.
   2.1.103         ?
   2.1.104     12-22-97  KGD     Fix for DCS 1091.
   2.1.105     12-29-97  BJB     Replaced missing bottom half of file! (used 1.103)
   2.1.106     12-29-97  BJB     Changed call to ShowMenuItems() to call
                                  ShowScreenMenuItems(), preparing for new term code.
   1.107       01-05-98  BJB     Added support for remote terminal.
   1.108       01-12-98  BJB     Modified AbortPrinting() to respond to ESTOP msgs.
   1.109       01-20-98  PaulG   Removed 14" PageSize.
                                 Combined Offline and powered off function into one func.
   1.110       01-22-98  BJB     Deleted unnecessary externs to StrYes[]/StrNo[]
   1.111       01-27-98  PaulG   Increased delay time from 2 sec to 4.sec for Page Conflict mess.
                                 Added code to resend code to the printer when printer mode is changed.
   1.112       02-04-98  PaulG   Added code to print graphs based on ControlLevel.
                                 Added code to form feed if WeldsPerPage is changed.
   1.113       02-10-98  PaulG   Reset variable UILines so new header will print for 1 line data.
   1.114       02-18-98  PaulG   Reset Equipment variable when abort is pressed.
   1.116       03-13-98  PaulG   Initialize these variables to 0 (ForGraphValue, VGraphValue,  
                                 DGraphValue, FGraphValue, AGraphValue, PGraphValue,                
                                 WSummaryValue, WHistoryValue, SPresetValue.)
   1.117       03-16-98  BJB     Disables printer interrupt when aborting printing.
   1.118       03-20-98  PaulG   Clean up modules, removing unnessary comments
   1.119       03-24-98  PaulG   Added TotalPts to WELD_OBJECT structure.
   1.120       04-05-98  BJB     Calls WaitMessage() instead of tm_wkafter().
   1.121       04-06-98  PaulG   Changed XScale from MODEL_4 to MODEL_5.
   1.122       04-21-98  PaulG   Changed Distance, velocity, force from DONTCARE to AED.
   1.123       04-22-98  BJB     Calls simpler version of ShowMenuItems().
   1.124       04-28-98  BJB     Deleted unused Vptr[] array, unused ID in RADIOMENU items.
   1.125       05-14-98  PaulG   Changed all occurances of AED or EP and replace with AEF | AED.
                                 Added Force Graph.
   1.126       05-21-98  PaulG   Added Abs menu.
   1.127       05-22-98  PaulG   Remove extra force graph from menu.
   1.128       06-01-98  PaulG   If coldstart was done you will get message if you try to print History.
   1.129       06-05-98  PaulG   Changed DontPrintGraph from UINT16 TO BOOLEAN.
   1.130       06-11-98  PaulG   Added error beeper when Printer is offline and printing is attempted.
   1.131       06-12-98  BJB     Modified AbortPrinting() to use ProcessControlMessage().
   1.132       06-24-98  BJB     Changed NORMAL to BASIC.
   1.133       07-07-98  PaulG   Transferred PrintMessage text array to pr_text file.
                                 When the system is powered up history will print regardless of
                                 whether or not a cycle was done.
   1.134       08-07-98  PaulG   Added DontPrintGraph to WELD_OBJECT struct.
   1.135       08-19-98  BJB     Modified AbortPrinting() for new screen, terminal modules.
   1.136       08-27-98  PaulG   Rearrange graph printout to print first and display message last.
   1.137       09-04-98  PaulG   General cheanup of code.
   1.138       10-27-98  PaulG   Changed Freq. and Weld History from LEVEL_d to LEVEL_ea.
   1.139       11-02-98  PaulG   Changed text strings StrM8_2[], StrM8_2A[]
   1.140       11-16-98  PaulG   Added check for Absolute on sample and alarm.
   1.141       04-23-99  OFi     Changed for Diab
   1.142       05-26-99  LAM     commented out absolute graph for a future release
   1.142.4.1   09-23-99  JLH     Updated ContinueAbortFunc to set top of page for printer in IBM Pro mode.
   1.144       09-23-99  LAM     deleted unused function
   1.144       09-23-99  LAM     fixed function prototype warnings
   1.146       11-05-99  JLH     Deleted InitPrinterOnceOnPowerup = TRUE from GetPrinterChoice.  This was
                                  the cause of the "form feed problem" when printing 1-line data.  Also
                                  converted tabs to equivalent spaces.
   1.147       12-06-99  JLH     Corrected FreqGraphFunc to allow print now function for control levels 
                                  >= 3.   
   1.147.6.1   02-07-00  JZ      removed DVS, added Mask1, Cond1, Mask2, Cond2
   1.147.6.2   02-23-00  OFI     removed 'User experience level' from menu strucutures
   1.147.6.3   03-06-00  JLH     Merged 1.148 into Lang branch.
   1.148       02-23-00  JZ      merged version 7.f4CHp to trunk
   1.149       03-21-00  JLH     Removed IBM proprinter.  Changed printer menu text to Epson(ESC/P)
                                  and HP(PCL).
   1.150       03-24-00  JLH     Removed code to set PrinterType variable.  This will be done in 
                                  InitPrinterType.
   1.151       04-07-00  JZ      merged Lang to trunk
   1.152       04-11-00  JZ      corrected ReferToManual structure                                       
   1.154       05-26-00  JLH     Removed LaserJet and InkJet printer types.  Added OKI520 and HPPCL printer types.
   1.155       05-30-00  JLH     Fixed bugs in 1.154.
   1.156       06-02-00  SCM     Changed the definition of StrM8_1111 variable which
                                 fixed the printer menu error that John encountered.
   1.157       06-09-00  LAM     replaced blank strings with StrBlankLine
   1.158       06-14-00  SCM     Replaced array index-20 with 'define' LINESIZE.
   1.159       06-21-00  DJL     Made a few global name changes from GlobalPrinting to GlobalPrintingFlag.
                                 Changed MODEL to LEVEL and erased model# 6 and 7
   1.160       07-10-00  BEKymer fixed macro errors from the LEVEL to the numbers. 
   1.161       07-13-00  BEK/DJL fixed some macro errors from level back to numbers.                                  
   1.161       07-13-00  JLH     PrintMessage multilanguage updates.
   1.162       07-13-00  BEKymer Fixed pointer problem with PrintMessage
   1.163       07-18-00  SCM     Temporary fix for the PrintMess[] problem.
   1.164       07-18-00  SCM     Removed the temporary fix associated with the Printmess[]
                                 and provided a permanent fix.
   1.165       08-09-00  JLH     Added HornScanFunc to print horn scan graph.
   1.166       08-10-00  JLH     Updated HornScanFunc to display Printing Horn Scan Graph on front panel.
   1.167       08-14-00  SRP     Scanstatus is checked before sending HORNSCAN msg to print.
   1.168       08-17-00  LAM     use correct "continue" string
   1.169       08-18-00  AT      GetPrinterInfo updates all language messages
   1.170       09-06-00  AT      GetPrinterInfo updates messages also when language changes
   1.171       09-12-00  SCM     Fixed the printing of the weld history problem after a cold start.
   1.172       09-27-00  SCM     Fixed the printing of the weld data problem after a cold start.
                                 - Tracker issue 3572.
   1.173       10-19-00  JLH     Added DUPSPresetFunc to properly initiate the DupsPresetReport.
                                  - Tracker issue 3638.  
   1.173.2.0   09-04-03  JOY     Added Printing messages to the QVGA.
                                 Added 'QVGAPrintingMenu'.
   1.173.2.1   10-16-03  JOY     MiddleSeg. is erased by QVGA ROM image.
   1.176       12-03-03  BEKymer Merged 1.175 & 1.173.2.1 to create 1.176 for
                                  Ver9.00b build
   1.177       12-09-03  BEKymer Add in missing brace from merge
                                 Add arguments where needed for SUBMNEU & TEXT
                                  function calls
   1.178       05-17-04  VSharma Removed extern of unused strings.
   1.179       06-04-04  VSharma Added global SampleValue & AlarmFlag struct for each graph.
                                 Modified CheckPrintingStatus() for ExternalPreset selection.
   1.180       07-07-04  JOY     CycleCount check is removed from the WeldHistory print.
   1.181       07-25-05  Bwadia  GetPrinter Info modified to support Asian Language.
                                 VGA exit and save button added.
   1.182       09-10-05  Bwadia  VGA print related menus added for Ver10.0h
   1.183       10-11-05  Bwadia  USB parameter menus added                               
   1.184       10-24-05  Bwadia  USB strings for 'Send on sample' and 'Send on Alarm' changed
   1.185       12-07-05  Bwadia  Page size and printer menu items removed from VGA. Modified
                                 for tracker issue 4023
   1.186       12-20-05  Bwadia  Sequence printing related menu items and code added
                                 Modified for Tracker issue 3976
   1.187       1-06-06   LAM     Merged BBRaun Special
   1.188       01-12-06  Bwadia  Added Print now VGAButton for Main Menu
   1.189	      02-08-06  Bwadia  Added USB global On/Off toggle item
   1.190       10-22-07  NHAhmed Changes done for LangTest phase 0
   1.191       01-11-08  NHAhmed GetPrinterInfo was replicated to a none argument type, 
                                 keeping all functionality same.
   1.192       04-14-08  NHAhmed Removed function GetPrinterInfo1().
   1.193       09-02-08  NHAhmed CleanUp for multi-language support.    
   1.194       09-04-08  YGupta  CleanUp for LangTest Project.   
   1.195       03-08-11  PDwivedi Added USBFullCheckFunc function.                                     
----------------------------------- DESCRIPTION ----------------------------------------
   
   This program allows you to print preset and system information to
   the printer. It enables the Print Menu option form the Main Menu.

--------------------------------- INCLUDE FILES -----------------------------*/

#include <psos.h>
#include "string.h"
#include "menu.h"
#include "graphs.h"
#include "menu4.h"
#include "weld_obj.h"
#include "beep.h"                                 
#include "keypad.h"
#include "selctkey.h"
#include "state.h"
#include "statedrv.h"
#include "preset.h"
#include "param.h"
#include "names.h"                            /* application object definitions     */
#include "opcodes.h"                          /* intertask opcodes definitions      */
#include "myptrmsg.h"                         /* generic message pointer type       */
#include "genrlmsg.h"                         /* generic message type               */
#include "limits.h"                          
#include "ck_qsend.h"
#include "weldhold.h"

#include "alarms.h"
#include "ready.h"
#include "led.h"
#include "display.h"
#include "selctkey.h"
#include "getmsg.h"
#include "dups_api.h"
#include "menu7a.h"
#include "drawscrn.h"
#include "weld_msg.h"


/*--------------------------- GLOBAL TYPE DECLARATIONS ----------------------*/
                            
void ChangeWeldCountToOne(void);
BOOLEAN PrintMsgDisplayed = FALSE;/*To refresh the screen if Msg is displayed*/
UINT16         PrintingGraphFlag = TRUE;  /*-- TRUE: Graph data currently printing --*/
UINT32         PrintQid = 0;        
SINT8          LastPrinterState = 0;
WELD_DATA_MSG  PrintMsgOut;
SINT32         ForGraphValue = 0;
SINT32         VGraphValue   = 0;
SINT32         DGraphValue   = 0;
SINT32         FGraphValue   = 0;
SINT32         AGraphValue   = 0;
SINT32         PGraphValue   = 0;
SINT32         WSummaryValue = 0;
SINT32         WHistoryValue = 0;
SINT32         SPresetValue  = 0;
SINT32         AbsGraphValue = 0;
SINT32         SequenceValue = 0;
UINT16         PrintIsOffline;    /*-- TRUE: Printer is offline --*/
UINT32         ExtSampleCount= 0;
BOOLEAN        VGAPrinterStatus = FALSE; 
BOOLEAN        VGAUSBFullStatus = FALSE; 

SINT32         MaxWeldsPerPage = MAXPAGECONT;
SINT32         MinWeldsPerPage = MINPAGESIZE;

/*-------------------------------EXTERNAL DATA-------------------------------*/

extern SINT32  WeldCounter;                /*--  Counts the weld cycles           --*/
extern SINT16  MenuCounter;
extern UINT32  UILines;                    /*-- Line counter, every CR increments --*/
extern SINT8   CheckPrinter;
extern SETUPS_Ver800  CurrentPreset;   /*changed SETUPS to SETUPS_Ver800*/
extern UINT16  RadioIndex;
extern UINT16  GraphReadyFlag;
extern UINT16  AbortPrintingFlag;
extern UINT16  PrinterBufferReadyFlag;
extern SETUPS_Ver800  MinLimit, MaxLimit;   /*changed SETUPS to SETUPS_Ver800*/
extern UINT8 MenuLevel;    


extern UINT16 LangIndex;
STR    **PrintMessage;


extern CONFIGSETUP CurrentSetup;                            
extern SETUPS_Ver800      RunningPreset;   /*changed SETUPS to SETUPS_Ver800*/

extern SINT8       buffer[];                 /*--  Holds string to be printed    --*/
extern UINT16      PrintAnyway;
extern UINT16      InitPrinterOnceOnPowerup;
extern UINT16      PrinterType;
extern WELD_DATA   WeldingResults;
extern WELD_OBJECT *MsPointer;
extern UINT16      PrintCPIMode;
extern UINT16      ColdStartDone;   /*--  FALSE: cold start not done             --*/ 
extern BOOLEAN VGAUSBFullFlag;

/*-------------------------------STATIC DATA----------------------------------*/



/**----------------------------LOCAL FUNCTIONS-----------------------------**/

/**---------------------------------- CODE --------------------------------**/


UINT16 IntCheckPrintStatus(void)
/**--------------------------------------------------**
 ** This function checks if GlobalPrint is ON, for   **
 ** internal preset selection and if On it checks to **
 ** see if there is  at least one item to print.     **
 ** If so, it returns TRUE, else  it returns FALSE.  **
 ** TRUE  : Ok to print.                             **
 ** FALSE : Printing not allowed.                    **
 **--------------------------------------------------**/
{
  UINT16 CheckPrintFlag = FALSE;

  if(RunningPreset.GlobalPrintingFlag == TRUE){ 

     /*-- Check Print Samples, if at least one is ON PrintOk is TRUE --*/

     if(((RunningPreset.SetupPresetSFlag     & BIT0) == FALSE)  ||
        ((RunningPreset.WeldHistorySFlag     & BIT0) == FALSE)  ||
        ((RunningPreset.WeldSummarySFlag     & BIT0) == FALSE)  ||    
        ((RunningPreset.PowerGraphSFlag      & BIT0) == FALSE)  ||    
        ((RunningPreset.AmplitudeGraphSFlag  & BIT0) == FALSE)  || 
        ((RunningPreset.FrequencyGraphSFlag  & BIT0) == FALSE)  || 
        ((RunningPreset.ColDistanceGraphSFlag & BIT0) == FALSE) || 
        ((RunningPreset.AbsDistanceGraphSFlag & BIT0) == FALSE) || 
        ((RunningPreset.VelocityGraphSFlag   & BIT0) == FALSE)  || 
        ((RunningPreset.ForceGraphSFlag      & BIT0) == FALSE)){
        CheckPrintFlag = TRUE;
     }
     
     /*-- Check Print Alarms, if at least one is ON PrintOk is TRUE --*/
     
     else
     if((RunningPreset.SetupPresetAFlag      == TRUE) ||
        (RunningPreset.WeldHistoryAFlag      == TRUE) ||
        (RunningPreset.WeldSummaryAFlag      == TRUE) ||
        (RunningPreset.PowerGraphAFlag       == TRUE) ||
        (RunningPreset.AmplitudeGraphAFlag   == TRUE) ||
        (RunningPreset.FrequencyGraphAFlag   == TRUE) ||
        (RunningPreset.ColDistanceGraphAFlag == TRUE) ||
        (RunningPreset.AbsDistanceGraphAFlag == TRUE) ||
        (RunningPreset.VelocityGraphAFlag    == TRUE) ||
        (RunningPreset.ForceGraphAFlag       == TRUE)) {
        CheckPrintFlag = TRUE;
     }
     else
        CheckPrintFlag = FALSE;

  }
  else
    CheckPrintFlag = FALSE;


  return(CheckPrintFlag);
}


UINT16 ExtCheckPrintStatus(void)
/**--------------------------------------------------**
 ** This function checks if GlobalPrint is ON, for   **
 ** External preset selection and if On it checks to **
 ** see if there is  at least one item to print.     **
 ** If so, it returns TRUE, else  it returns FALSE.  **
 ** TRUE  : Ok to print.                             **
 ** FALSE : Printing not allowed.                    **
 **--------------------------------------------------**/
{
  UINT16 CheckPrintFlag = FALSE;

  if(CurrentSetup.ExtGlobalPrintFlag == TRUE )
  {
          /*-- Check Print Samples, if at least one is ON PrintOk is TRUE --*/

     if(((CurrentSetup.SPExtSampleFlag     & BIT0) == FALSE)  ||
        ((CurrentSetup.WHExtSampleFlag     & BIT0) == FALSE)  ||
        ((CurrentSetup.WSExtSampleFlag     & BIT0) == FALSE)  ||    
        ((CurrentSetup.PGExtSampleFlag     & BIT0) == FALSE)  ||    
        ((CurrentSetup.AGExtSampleFlag     & BIT0) == FALSE)  || 
        ((CurrentSetup.FreqGExtSampleFlag  & BIT0) == FALSE)  || 
        ((CurrentSetup.CDGExtSampleFlag    & BIT0) == FALSE)  || 
        ((CurrentSetup.VGExtSampleFlag     & BIT0) == FALSE)  || 
        ((CurrentSetup.FGExtSampleFlag     & BIT0) == FALSE)){
        CheckPrintFlag = TRUE;
     }
     
     /*-- Check Print Alarms, if at least one is ON PrintOk is TRUE --*/
     
     else
     if((CurrentSetup.SPExtAlarmFlag      == TRUE) ||
        (CurrentSetup.WHExtAlarmFlag      == TRUE) ||
        (CurrentSetup.WSExtAlarmFlag      == TRUE) ||
        (CurrentSetup.PGExtAlarmFlag      == TRUE) ||
        (CurrentSetup.AGExtAlarmFlag      == TRUE) ||
        (CurrentSetup.FreqGExtAlarmFlag   == TRUE) ||
        (CurrentSetup.CDGExtAlarmFlag     == TRUE) ||
        (CurrentSetup.VGExtAlarmFlag      == TRUE) ||
        (CurrentSetup.FGExtAlarmFlag      == TRUE)) {
        CheckPrintFlag = TRUE;
     }
     else
        CheckPrintFlag = FALSE;

  }
  
  else
    CheckPrintFlag = FALSE;


  return(CheckPrintFlag);
}


UINT16 CheckPrintingStatus(void)
/**--------------------------------------------------**
 ** This function checks if GlobalPrint is ON, if it **
 ** is then it checks to see if there is  at least   **
 ** one item to print. If so, it returns TRUE, else  **
 ** it returns FALSE.                                **
 ** TRUE  : Ok to print.                             **
 ** FALSE : Printing not allowed.                    **
 **--------------------------------------------------**/
{
  UINT16 CheckPrintOk = FALSE;

  /*-- Global print is "SUSPENDED" or "ON".   --*/

  if(CurrentSetup.ExtPresets == FALSE)
     CheckPrintOk = IntCheckPrintStatus();
  else
     CheckPrintOk = ExtCheckPrintStatus();
  
  return(CheckPrintOk);
}

UINT16 USBFullCheckFunc(void)
{
   if(VGAUSBFullStatus)
      VGAUSBFullFlag = TRUE;
   else
      VGAUSBFullFlag = FALSE;

   return(VGAUSBFullFlag);

}

UINT16 OfflineCheckFunc(void)
/**-------------------------------------------------**
 ** This function checks if the printer is offline  **
 ** or powered off.                                 **
 ** Return: TRUE  if printer is offline/Powered off **
 ** Return: FALSE if printer is busy, online, or    **
 ** powered off                                     **
 **-------------------------------------------------**/
{
  /*-- Check printer status --*/
  if (IsHWConfigured(VGA))
  {
     if(VGAPrinterStatus)
        PrintIsOffline = FALSE;
     else
        PrintIsOffline = TRUE;   
  }
  else
  {
     switch(CheckPrinter & MASKPRINT)
     {

       case PRINTBUSY:       /*-- printer Busy   -    00001101 --*/         
            PrintIsOffline = FALSE;
            break;

       case PRINTONLINE:     /*-- printer online  -   00000101 = 0x05 --*/
            PrintIsOffline = FALSE;
            break;

       case POWEROFF:        /*-- printer offline 0x0f --*/

       case OUTOFPAPER:        /*-- printer offline 0x0f --*/

       default:

            PrintIsOffline = TRUE;
            break;
     }
  }

  return(PrintIsOffline);
}

void GetPrinterChoice(void)
/**------------------------------------------**
 ** This function assigns index values for   **                                        
 ** each printer choice. Panasonic will have **
 ** the same index as EpsonFX                ** 
 **------------------------------------------**/
{
   if(CurrentSetup.PrinterOKI520)
      RadioIndex = 0;    
   else if(CurrentSetup.PrinterEpson) 
      RadioIndex = 1;
   else if(CurrentSetup.PrinterHPPCL)
       RadioIndex = 2;
   else
       RadioIndex = 0;
}

void SetPrinterChoice(void)
/**------------------------------------------**
 ** This function assigns index values for   **                                        
 ** each printer choice. Panasonic will have **
 ** the same index as EpsonFX                ** 
 **------------------------------------------**/
{
   switch(RadioIndex)
   {
   case 0:
      CurrentSetup.PrinterOKI520   = TRUE;
      CurrentSetup.PrinterHPPCL    = FALSE;
      CurrentSetup.PrinterEpson    = FALSE;
      break;
   case 1:
      CurrentSetup.PrinterOKI520   = FALSE;
      CurrentSetup.PrinterHPPCL    = FALSE;
      CurrentSetup.PrinterEpson    = TRUE;
      break;
   case 2:
      CurrentSetup.PrinterOKI520   = FALSE;
      CurrentSetup.PrinterHPPCL    = TRUE;
      CurrentSetup.PrinterEpson    = FALSE;
      break;
   default:
      CurrentSetup.PrinterOKI520   = TRUE;
      CurrentSetup.PrinterHPPCL    = FALSE;
      CurrentSetup.PrinterEpson    = FALSE;
      break;
   
   }
   UpdateCurrentPreset(PRINTERTYPE, 0, 0);
   SetThePrinterType();
}

void SetPageSize(void)
/**-----------------------------------------**
 ** This function is used by the Radio Menu **
 ** to change the page size selection.      **
 **-----------------------------------------**/
{
   switch(RadioIndex){
   case 0:
      CurrentSetup.PageSize = PAGESIZE11;
      break;
   case 1:
      CurrentSetup.PageSize = PAGESIZEA4;
      break;
   default :
      CurrentSetup.PageSize = PAGESIZE11;
      break;
   }
    
}


void GetPageSize(void)
/**-----------------------------------------**
 ** This function is used by the Radio Menu **
 ** to change the page size selection.      **
 **-----------------------------------------**/
{
   if(CurrentSetup.PageSize & PAGESIZE11)
      RadioIndex = 0;
   else
   if(CurrentSetup.PageSize & PAGESIZEA4)
      RadioIndex = 1;
   else

      RadioIndex = 0;
}


void EnabledPrinterHPPCL(void)
/**-----------------------------------------------------**
 ** HP PCL printer is enabled and all others disabled.  **
 **-----------------------------------------------------**/
{
   if(CurrentSetup.PrinterHPPCL)
   {
      CurrentSetup.PrinterOKI520   = FALSE;
      CurrentSetup.PrinterEpson    = FALSE;
      UpdateCurrentPreset(PRINTERTYPE, 0, 0);
   }
   else if(!CurrentSetup.PrinterEpson &&
           !CurrentSetup.PrinterOKI520)
           CurrentSetup.PrinterHPPCL = TRUE;
   
   SetThePrinterType();
}



void CalMaxWeldsPerPage(void)
/**---------------------------------------------------------**
 ** Calculate the Welds per page limit dynamically via Page **
 ** size.                                                   **
 **---------------------------------------------------------**/
{
}



void SetThePrinterType(void)
/**--------------------------------------**
 ** This function check the printer type **
 **--------------------------------------**/
{
   /*-- If printer type changes send correct code to printer --*/
   InitPrinterOnceOnPowerup = TRUE;
}



void ContinueAbortFunc(UINT32 MenuExtra)
/**------------------------------------------------**
 ** This function stops welder when Printer aborts **
 ** is pressed until user hits "Continue"          **
 **------------------------------------------------**/
{
   /*-- Reset to allow welding to continue --*/
   WaitMessage( SECONDS_TO_TICKS(1));
   AbortPrintingFlag = FALSE;
   PrinterBufferReadyFlag = TRUE;
}



void InitSetupPresetValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    SPresetValue = 0;
}



void InitWeldHistoryValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    WHistoryValue = 0;
}



void InitWeldSummaryValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    WSummaryValue = 0;
}



void InitPowerGraphValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    PGraphValue = 0;
}



void InitAmpGraphValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    AGraphValue = 0;
}



void InitFreqGraphValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    FGraphValue = 0;
}



void InitColDistGraphValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    DGraphValue = 0;
}



void InitAbsDistGraphValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    AbsGraphValue = 0;
}



void InitVelGraphValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    VGraphValue = 0;
}



void InitForceGraphValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    ForGraphValue = 0;
}

void InitSequenceValue(void)
/**------------------------------------------**
 ** This function Initialize Sample variable **
 **------------------------------------------**/
{
    SequenceValue = 0;
}

void ChangeWeldCountToOne(void)
/**------------------------------------------**
 ** This function Initialize the Weldcounter **
 ** to the WeldsPerPage value in the menu.   **
 **------------------------------------------**/
{
  WeldCounter = CurrentSetup.WeldsPerPage;
  
}







