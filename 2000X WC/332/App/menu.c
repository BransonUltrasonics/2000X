/* $Header:   D:/databases/VMdb/2000Series/App/MENU.C_V   2.276.2.1   Nov 29 2017 11:36:10   hasanchez  $ */
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
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu.c

   Function name: void RemoveNull();                            
                  void DealWithScrollLeds();
                  SINT16 InsertProperUnits();
                  void DisplayMenu();

 --------------------------------- REVISIONS --------------------------------

   Revision #      Date       Author      Description
   ==========     ========    ======      ===========
   0                                      Initial Version                     
   1.00           051095      BEK         Original write of code            
   2.00           04/29/96    PJ          Moved Selectkey Function into its 
                                          own module.                     
   3.00           05/01/96    BEK         added statefakeout                
   4.00           05/03/96    BEK         added StuffKey                    
   5.00           05/08/96    PJ          Corrected display distance bug    
                                          Corrected MainMenu from
                                          displaying twice.                 
   7.00           05/10/96    PJ          Corrected MainMenuKey, GoBackKey
   10.00          05/30/96    PJ          Corrected bug displaying Energy value.
   11.00          06/07/96    PJ          Changed TitleLine Page Display to
                                          1 of xx
   12.00          06/11/96    PJ          Changed CurrentUser from local to global
   13.00          06/13/96    PJ          Enabled Diagnostic BARGRAPH menus
   14.00          06/28/96    PJ          if format is BARGRAPH and type is
                                          VARIABLE, function will be executed 
   15.00          07/02/96    PJ          Changed = sign to > sign if submenus
                                          are in the item.   
   15.01          07/19/96    PJ          Added code to go directly to the WeldMode
                                          Menu If Weld Parameters is selected.
   15.02          07-25-96    PJ          Make HornDownFlag a BOOLEAN (so
                                          it can be used in states.c)
   15.10          08/01/96    PJ          Added function call test prior to
                                          displaying RADIOMENU.
   15.20          08/14/96    PJ          Corrected Formatting of Energy str.
   15.30          08/22/96    PJ          Added code to prevent displaying of
                                          menus when scrolling thru displays.
   15.40          08/22/96    PMG         Enabled Print Key Option for Front
                                          Panel.
   15.60          09/04/96    PhilJ       Added Type TIMEDATE to enum Format
                                          to display VARIABLE type.
   15.70          09/11/96    PhilJ       Added Weld Results Scrolling menus
                                          to the Run screen.
   15.80          09/17/96    PhilJ       Left/Right keys for Scrolling menus
                                          now handled in Selctkey.c.
                                          disabled amplitude step at force
   15.90          09/18/96    PhilJ       Added missing update of MenuIndex in
                                          case Select3Key.
   16.00          09/19/96    PhilJ       Cleared HornDownFlag in GoBackKey
   16.10          09/19/96    PhilJ       Changed Display blanking procedure.
   16.20          09/20/96    PhilJ       Corrected updating of HVARIABLE.
   16.30          09/23/96    PhilJ       Corrected updating of HSUBMENU.
   16.40          09/24/96    PhilJ       Disabled Select1Key in FREQ OFFSET
                                          menu.
   16.50          09/25/96    PhilJ       Corrected updating of scrolling
                                          buffer.
   16.60          09/25/96    PhilJ       Added function SendKeyToWeldMngr.
   16.70          10/04/96    PhilJ       Removed the sending of GoBackKeys
                                          on a MainKeyPress.
   16.80          10/10/96    PaulG       Added PrinterDisplay to case PrintKey .
   16.90          10/11/96    PhilJ       Added ALARM type for displaying
                                          Alarms.  Correct updating of LEDs.
   17.00          10/15/96    PhilJ       VF Display line updated with FILLCHAR
                                          when ENDLIST encountered.
   17.10          10/16/96    PhilJ       Moved Display Alarm Check to SelctKey.c.
   18.00          10-17-96    BEKymer     Removed action code from HornDownKey,
                                          TestKey and ResetKey (only deal with menus)
   18.10          10/19/96    PhilJ       Added English to Metric conversion.
   18.20          10/22/96    PhilJ       Corrected Displaying of Time and Date.
                                          Changed Energy unit from lowercase
                                          j to Uppercase.
   18.30          10/24/96    PhilJ       Replaced CurrentUser with
                                          CurrentPreset.User to check Features.
   19.02          10/27/96    LAM         Added equal sign to hour and date
                                          strings.
   19.30          10/29/96    PhilJ       ScrollingBuffer now updates when on
                                          Scrolling Menu screen.
   19.40          10/31/96    PhilJ       Added GoBackFlag and beeps if
                                          bad key sent.
   20.00          11/01/96    LAM         chged productnumber variable
   20.01          11/01/96    LAM         added pressure type,added clearkey,
   21.00          11/06/96    PhilJ       Corrected bug in Run Screen.
   21.10          11/07/96    PhilJ       Added ExitMenuCounter to pop menu
                                          off stack.
   21.20          11/10/96    LAM         replaced q_send
   21.30          11/11/96    PhilJ       Corrected ExitFlag from being set
                                          when HornDownKey is pressed.
   21.40          11/13/96    PhilJ       Corrected displaying of OFF string
                                          in Suspect and Reject alarms.
   21.50          11/13/96    LAM         chged pressure format to xxx.x
   21.60          11/15/96    PhilJ       Corrected bug displaying distance
                                          in Metric.
   21.70          11/18/96    LAM         deleted horndown              
   21.80          11-21-96    BEKyme      Cleanup main & goback key handling
   21.90          11-22-96    LAM         fixed metric distance to 1 less decimal              
   22.00          11-27-96    PhilJ       Removed AlarmDetectedFlag check from
                                          TEXT in display choices.
   22.10          12-02-96    LAM         fixed metric pressure readings              
   23.00          12-09-96    BEKymer     Added OP_FRONT_PANEL_KEYPRESS to 
                                          StateChangeFakeOut
   23.10          12-10-96    PhilJ       In HSUBMENU check if VFBuffer is empty
                                          before line update.
   23.20          12-11-96    PhilJ       Added FakeKeyPress UPDATETOPLINE.
                                          Changed UPDATEDISP to UPDATEDISPLAY
                                          Deleted wait till VFBuffer empty.
   23.30          12-17-96    PhilJ       Fixed return to Main menu from Run
   23.31          01-02-97    PaulG       Added PrinterDisplay function.
   23.40          01-07-97    PhilJ       Corrected returning from HornDownMenu.
   23.50          01-10-97    PhilJ       Corrected LED update from Run screen.
   23.60          01-15-97    PhilJ       Corrected bug depressing select key
                                          in HornDown Menu.
   23.70          01-21-97    PhilJ       Test actuator type when HornDownKey is
                                          pressed to display correct menu.
   23.80          01-23-97    LAM         added run screen alarm check               
   23.90          01-21-97    PhilJ       Corrected menu navigation &
                                          Left/Right LED display.
   24.00          02-03-97    PhilJ       Corrected Left/Right Leds
   25.00          02-05-97    PhilJ       Corrected Metric distance display.
   25.10          02-13-97    PhilJ       Added 3rd decimal to Metric distance.
   25.10          02-13-97    PhilJ       Added 3rd decimal to Metric distance.
   25.20          02-21-97    PhilJ       disabled RunKey if Test menu enabled.
   25.30          02-21-97    LAM         chged velocity format to xx.xx       
   25.40          02-26-97    PhilJ       Added HornDown test in Selct2key.
   25.50          03-05-97    PhilJ       Added ErrorBeep to Reset Key.
   25.60          03-07-97    PhilJ       Corrected display corruption when
                                          scrolling one line data.
   25.60          03-07-97    PhilJ       Corrected display corruption when
   25.70          03-12-97    PhilJ       Added function DisplayResetMsg();
   25.80          04-02-97    PhilJ       Added UPDATELINE4 to switch(NewKey).
   25.90          04-04-97    PhilJ       Call new FormatDateStrs function if
                                          TIMEDATE variable.
   26.00          04-08-97    LAM         made testpower format as watts              
   26.10          04-10-97    PhilJ       Implemented RADIO type menus.
   27.00          04-15-97    LAM         added max bargraph = 12                   
   27.10          04-15-97    LAM         fixed watts off by factor of 10
   27.20          04-16-97    PhilJ       Added PrinterScaling check.
   27.30          04-18-97    PhilJ       Deleted StuffKey function.
   27.40          04-21-97    PhilJ       Fixed updating of scrolling buffer
                                          when UPDATELINE4 is sent.
   27.50          04-23-97    PhilJ       Added UPDATELINE2 to switch(NewKey).
   27.60          04-25-97    PhilJ       Added WeldResults & RunSeek to
                                          scrolling menu.
   28.10          05-07-97    PhilJ       Fixed LED display exiting TestMode.
   28.20          05-27-97    PhilJ       Fixed FreqOffset if MainKey or RunKey
                                          is pressed.  Corrected asterick when
                                          scrolling one line data.
   28.30          05-28-97    PhilJ       Changed clearing of TestMenuEnabled.
   29.2.100       06-23-97    LAM         deleted hardcoding of encoder       
   29.2.101       06/24/97    LAM         Deleted initdisplaymenu
   29.2.112       07-09-97    PhilJ       Moved HmenuIndex to CurrentSetup
   2.113          07-17-97    PhilJ       Added SetOneLineDataBit function to
                                          HVARIABLE type.
   2.114          07.18.97    JBerman     Added case: _ADVFEATURE
   2.115          07-22-97    PhilJ       Added case:SetupKey to switch statement
   2.116          07-23-97    PhilJ       Added HornDownMenu check if no encoder
   2.117          07-23-97    JBerman     Added #include features.h
   2.118          07-24-97    PhilJ       Added global variable RadioMenuCounter
   2.119          07-31-97    BEKymer     Add uppercasing option if  
                                          (CenterFlag=TRUE) & (PageFlag=FALSE)
   2.120          08-20-97    PhilJ       Repositioned "=" sign in type CHOICE
   2.121          08-21-97    LAM         replaced rightleftledoff with rightleftledon
                                          fixed weld data when an alarm occurs
   2.122          08-25-97    LAM         deleted unused variables                    
   2.123          09-03-97    LAM         made radiomenucounter extern                
   2.124          09-09-97    BEKymer     Added checks in InsertProperUnits
                                          to make sure inserting into right place
                                          Replaced 0xbe with SOLIDBLOCK define
   2.125          09-26-97    BJB         Deleted ChoiceSubMenuFlag, which was
                                          never tested.  Deleted ScrollIndex,
                                          writes directly to CurrentSetup.HmenuIndex
                                          Added missing comment end * / on ln #232
   2.126          10-03-97    BJB         Added code to convert VELOCITY items to
                                          metric.
   2.127          10-16-97    BJB         Added function WaitKeyPress()
   2.128          10-21-97    BJB         Includes "security.h"
                                          Deleted bogus "FUNCTION PROTOTYPES" line
                                          Added code to check passwords by calling
                                           SecurityChecked() when select keys,
                                           PrintKey, or SetupKey pressed.
                                          Resets access level at main menu or run
                                           screen when no key present in queue
                                           (waiting for user).
   2.129          10-28-97    BJB         Includes new file menuhorn.h.
                                          Got rid of flag HDMenuEnabled and code that
                                           ran when this flag was TRUE.
                                          Fixed error in RemoveNull().
                                          Initializes ScrollBuffer[] at start of
                                           DisplayMenu().
                                          Modified HornDownKey handling to call new
                                           function DoHornDown().
                                          Cleaned up GoBackKey code.
                                          Doesn't use what's pointed to by "menu8" to
                                           decide whether or not to allow Select1Key,
                                           since menu8 may be uninitialized!
   2.130          11-4-97     BJB         Includes menu2.h, menutest.h
                                          Deleted PrintFlag, BlankMenuFlag,
                                           TestMenuEnabled.
                                          DisplayResetMsg() uses just RunKey, not
                                           MainKey + INDEX0 + Sel1 to get to run
                                           screen.
                                          Pulled functions BuildMenu(),
                                           ShowMenuItems() out of DisplayMenu().
                                          Cleaned up insides of DisplayMenu().
                                          WaitKeyPress() doesn't respond to MainKey.
                                          Beeps if blank line is selected.
   2.131          11-08-97    BJB         Made FpsQueue local to DisplayMenu().
                                          Modified code that checks for chrs to
                                           throw out extra left/right keys, also
                                           uses new function ClearKeypadBuffer().
                                           Added tm_wkafter() call to Left/Right
                                           key processing code.
                                          Modified ADVFEATURE code so it only tests
                                           BIT0.
   2.132          11-11-97    BJB         DisplayResetMsg() sends ResetKey instead
                                           of RunKey so context-dependent response
                                           possible.
                                          Changed response to ResetKey in
                                           DisplayMenu() and WaitKeyPress().
                                          Modified WaitKeyPress() to return key.
   2.133          11-14-97    BJB         Extended size of local[] structure so max
                                           # of alarms doesn't cause crash.
   2.134          11-20-97    BJB         Changed response to ResetKey so code here
                                           in MENU.C posts RESET COMPLETE message.
                                          Modified DisplayResetMsg() so it only
                                           puts up text.  Other stuff now done
                                           directly in WeldManager().
   2.135          12-01-97    BEKymer     New flag AdjustWeldSetupMenuFlag
                                          Change 'J' to upper case in metric units

   2.136          12-2-97     kgd         Changed PrinterDisplay to GetPrinterInfo to fix DCS #1083
   2.137          12-04-97    BJB         Deleted AdjustWeldSetupMenuFlag.

                                          Rule #1: Please do not add any new "flags" to this file.
                                          Rule #2: If you need to add a new flag, read rule #1!
   2.138          12-2-97     kgd         fix for DCS #1013
   2.139          12-29-97    BJB         Deleted uses of DTEnabled.
   2.140          12-29-97    BJB         Structure changes to prepare for new terminal code:
                                           BuildMenu() returns # of lines, not # of pages.
                                           CurrentLine variable in DisplayMenu() named StartLine.
                                           RadioMenuCounter init moved to BuildMenu().
                                           CurrentPage variable not needed, uses TopLineIndex.
                                           Calls ShowScreenMenuItems() to produce menu, not
                                            ShowMenuItems().
                                           Prevents complete redraw when left/right pressed.
                                           Clears screen on exit from DisplayMenu().
                                           ScrollSize removed, fixed at 1.
                                           ShowMenuItems() changed to ShowScreenMenuItems().
                                           ShowScreenMenuItems() gives birth to FormatMenuLine()
                                            and FormatTitle() functions.
                                           ShowScreenMenuItems() calls UpdateVFLine() to
                                            explicitly output to screen.
   2.141          01-05-98    BJB          Added remote terminal support, including new
                                            variables for term menu display, response to new
                                            term messages (term up/down, select, data out,
                                            alarm out), use of up/down key handler functions,
                                            to DisplayMenu() and WaitKeyPress().
                                           Added ShowMenuItems() function to output to screen
                                            and terminal.
                                           Added up/down key handler functions.
                                           Modified FormatMenuLine() so caller can pass
                                            substitution character.
   2.142          01-12-98    BJB          Added ShowEstopMessageOn/Off()
                                           Modified DisplayMenu(), WaitKeyPress() to respond
                                            to ESTOP messages.
                                           Calls TermSyncMenus() after displaying submenus,
                                            in case a submenu called TermDataModeToggle().
   2.143          01-22-98    BJB          Turns off DiagFlag before calling Horn Down or
                                            Test modes.
                                           Does range check on CurrentSetup.HmenuIndex after
                                            every call to BuildMenu, just in case.
                                           Added TermSyncMenus() calls after HornDown, Test
   2.144          01-27-98    BJB          FormatMenuLine() takes argument specifying function
                                            to use to fill special characters into strings.
                                            Calls this instead of strsub().
                                           Created routine FillInScreenChrs().
                                           Changed '^' to '~'
                                           Got rid of unnecessary calls to strsub().
   2.145          01-29-98    BJB          Uses FormatSignedInt() to format FREQOFFSET items.
                                           Uses FormatValue() to format TIMEDATE items.
   2.146          02-06-98    BJB          Added code to display new type PERCENTX10.
   2.147          03-18-98    BJB          Recomputes HmenuCounter when weld results line of
                                            Run Screen is updated.
   2.148          03-20-98    BJB          TIME, DATE code in FormatMenuLine() adds > for
                                            submenu so it doesn't need to be in text strings.
   2.149          03-25-98    BJB          Fix for change in 2.147: Doesn't display scroll LEDs
                                            on UPDATEDISPLAY or UPDATELINE4 unless they should
                                            be on!
   2.150          04-21-98    BJB          Removed unnecessary parameters from ShowMenuItems(),
                                            ShowScreenMenuItems(), FormatMenuLine().
                                           Got rid of unused code for case StateChangeFakeOut.
   2.151          04-24-98    BJB          Modified number of digits displayed for VELOCITY.
   2.152          04-27-98    BJB          Modified BuildMenu() so one menu item can appear
                                            for multiple actuators.
   2.153          04-28-98    LAM          when in calibration goback sends a main key
   2.154          04-30-98    BJB          Added code to allow access to Branson menu when
                                            magic # is typed.
                                           Added test to prevent screen redraw after password
                                            entry for RADIOMENU items.
                                           Doesn't call ALPHA item function from FormatMenuLine().
                                           Added code to FormatMenuLine() to display ALPHA
                                            items on a menu.
                                           Corrected output length of COUNTER items.
   2.155          05-15-98    BJB          Added variable format table to simplify code
                                            that displays numerical items.  Rewrote routines
                                            related to display (InsertProperUnits(),
                                            FormatMenuLine()) to use table.
   2.156          05-19-98    BJB          Redefined FORCE format to store tenths of PSI, use
                                            more precise Newton conversion.
                                           Added new plain-vanilla INTERGER format.
   2.157          05-26-98    BJB          Modified FormatVariable(), FormatNum(), related
                                            functions so Metric/English flag is passed in.
                                            This is useful if printing while Units is changed.
   2.158          05-28-98    BJB          Changed increment of FREQOFFSET from 10 to 1.
                                           Deleted special test that prevented selection
                                            of Frequency Offset item.  Now selection of this
                                            item is permitted (and necessary).
   2.159          06-01-98    BJB          Made weld results scrolling active all the time
                                            on the run screen.
                                           Forced > to appear next to Password choice on
                                            system configuration menu.
   2.160          06-03-98    BJB          Deleted special test that prevented selection
                                            of Digital Pot Start Freq item.  Now selection
                                            of this item is permitted (and necessary).
                                           Turns of DiagFlag when processing Select keys,
                                            restores original state when done.
   2.161          06-11-98    LAM          added test if goback is pressed during calibration
   2.162          06-12-98    BJB          Modified DisplayMenu(), WaitKeyPress() to use
                                            ProcessControlMessage().
   2.163          06-17-98    BJB          Calls DisplayCurrentPreset() from FormatMenuLine();
                                            makes calls from other tasks unnecessary and
                                            so prevents corruption.
                                           Removed some now unneeded calls to
                                            DisplayCurrentPreset().
   2.164          06-22-98    BJB          Added function GetCurrentMenu() to allow other
                                            functions to see what menu is currently on the
                                            screen.
   2.165          06-24-98    BJB          Changed NORMAL to BASIC.
   2.166          06-25-98    BJB          Uses CurrentPreset.Features instead of
                                            CurrentSetup.User to decide which menu items to
                                            display.
   2.167          08-17-98    BJB          Fixed problem when sel key pressed during reset msg.
   2.168          08-19-98    BJB          Modified for new screen, terminal modules.
   2.169          08-28-98    BJB          Deleted DealWithScrollLeds(), LEDs now controlled
                                            by VFSCRN.C.
                                           Screen won't update on HD keypress if system not
                                            ready, just beeps (back to 2.167 behavior).
   2.170          09-02-98    BJB          Added functions AlarmOn() and AlarmOff().
                                           Moved some code that reacts to ResetKey into
                                            DisplayResetMsg().
   2.171          09-08-98    BJB          Blocks out TestKey while Reset Msg is
                                            displayed. If Test allowed, it interferes
                                            with forced jump to Run screen.
   2.172          09-09-98    BJB          Added LONGTIME to format table.
   2.173          09-28-98    BJB          Restores CurrentlyDisplayedMenu when leaving
                                            DisplayMenu().
   2.174          11-10-98    BJB          Fixed FormatNum() so it can't write - sign before
                                            start of string.
   2.175          11-13-98    BJB          Modified display of VARIABLEs to show - sign
                                           Fixed rounding of negative #s in convert
                                            internal/external routines.
   2.176          03-17-99    LAM          chged Branson password to 41
   2.177          05-11-99    JZ           changed BransonPassword to 413245373
   2.178          06-04-99    JZ           added entry into the struct var_format_def2 VarFormatTable   
   2.178.2.0      07-20-99    LAM          removed extra multiply of the FORCEDIV10 type
   2.180          08-20-99    JZ           fixed DCS issue #3103
   2.181          09-02-99    JZ           changed SkipFlag to UINT16
   2.182          09-23-99    BEKymer      Temp change Branson password to 88 for testing
   2.183          10-01-99    JZ           changed InsertProperUnits() to type void
   2.184          10-14-99    BEKymer      Temp change Branson password to 443 for testing   
   2.185          10-26-99    JZ           modified FormatMenuLine()
   2.186          10-26-99    BEKymer      Put back original BUC password
   2.187          12-16-99    LAM          removed unused error handling code
   2.187.6.1      02-07-99    JZ           removed DVS and commented out DVS else if
   2.187.6.2      02-22-00    OFI          removed features.h from list of include files Deleted all ADVFEATURE cases
                                           and all occurances of the use of features in code.
   2.188          04-05-00    JZ           merged to trunk
   2.189          05-26-00    SCM          Checked in for testing by Laura, John.
   2.190          06-02-00    SCM          Added cases for BuildMenu() and FormatMenuLine()
                                           functions.
   2.191          06-09-00    SCM          Added functions UpdateHWConfiguration() and
                                           UpdateSWConfiguration().
   2.192          06-14-00    SCM          Added the tests for the HWConfig and SWConfig in BuildMenu()
                                           and added the RestartMenu case.
   2.193          06-15-00    SCM          Changed the logic for testing the Mask and Cond in BuildMenu() function.
   2.194          06-29-00    BEKymer      Change structure member name from model to CtrlLevel
   2.195          07-22-00    SCM          Made the changes related to RADIOLARGE structure in the 
                                           BuildMenu() and FormatMenuLine() functions.
   2.196          07-26-00    SCM          Made the further changes related to RADIOLARGE structure in the 
                                           BuildMenu() and FormatMenuLine() functions.
   2.197          08/02/00    SRP          Typecast done at (SINT8 *)menu16->Tptr. 
   2.198          08/08/00    LAM          fixed displaying locked parameter set names 
   2.199          08/15/00    SCM          Modified function UpdateSWConfiguration().
   2.200          08/15/00    JLH          Modified date display for US units and metric units - was only mm/dd/yy before,
                                            now gives dd/mm/yy when metric units are selected.
   2.201          08/23/00    AT           Modified UpdateHWConfiguration to be like UpdateSWConfiguration
   2.202          08/23/00    BEKymer      Included string.h for memcpy prototype
   2.203          08/25/00    AT           TEXT menu - Eptr can be used to update item text if EnableFlag is FALSE (Look at MakeDipText for example)
   2.204          08/25/00    SRP          RadioIndex = 0 defined in case RADIOLARGEMENU to solve hangup problem. 
   2.205          08/28/00    LAM          fixed hw & sw configurations
   2.206          08/29/00    AT           Set access level to BRANSON if going to BUC menu 
   2.207          09/22/00    AT           Check XXCANTCHANGEXX before checking for password for VARIABLE menu item
   2.208          09/29/00    AT           Limited 2.207 fix to system info menu only because it would break other inconsistencies
   2.209          10/05/00    LAM          modified estop ISSUE(3597)
   2.210          10/06/00    LAM          set exitflag for gobackkey(3597)
   2.211          10/24/00    AT           DisplayMenu - beep in PresetNamesMenu and on any var with min and max 0 or equal
   2.212          10/25/00    AT           DisplayMenu - Fixed VARIABLE menu select key once more
   2.213          10/25/00    AT           DisplayMenu - if passwords are on and level below MAINTAINENCE - set to MAINTAINENCE if
                                           we are in CalibrateForceMenu1 (#3653)
   2.214          10/25/00    AT           Forgot to include the comment above in the source
                                           (Actually made it but didn't save before checking in)
   2.215          11-06-00    BEKymer      Require reset after estop removed.  Reset led
                                            blinks after estop removed.  Now, while estop
                                            active, navigation can occur and values can be
                                            changed.  In future, consider masking all keys
                                            but reset after estop removed, until reset
                                            is pressed.
   2.216          11-09-00    AT           EStop - modified ShowEstopMessageOn
   2.217          04-03-02    BEKymer      Add secret code to main menu for debugger
   2.218          04-04-02    BEKymer      Change DebugBase from UINT16 to SINT32
   2.216.3.2      04-17-02    BEKymer      Rewrite code to handle special secret passwords
                                            to allow easy adding to table.
   2.216.3.3      04-25-02    BEKymer      Add two new entries in the secret list for configuring
                                            aed and aef actuator cards
   2.216.3.4      05-09-02    BEKymer      Save updates to HmenuIndex in BBR as soon as changed
                                            in case plug is pulled.  This makes sure the run screen
                                            selection is not lost.                                   
   2.216.3.5      05-20-02    BEKymer      Call InitializeBBR instead of FixBattRam from secret code
   2.219          04-15-03    BEKymer      Put 2.216.3.5 back on tip as 2.219 for 8.10 build
                                            Add secret code to enable 332 diagnostics
                                            Allow KEY_0 key for secret codes
   2.220          05-16-03    BEKymer      Save VelocityReporting flag in BBR so it can be
                                            recovered at the next power up.
   2.216.3.7      06-10-03    bwadia       Modified "FormatMenuLine()" function to accomodate _GRAPH type
                                           menu items.
                                           Modified "BuildMenu()" to accomodate _GRAPH menu item type.
                                           Modified "SetHWConfiguration()" code was written erroneously.  
   2.216.3.8      06-11-03    bWadia       File checked in again since few functions got missed. 
   2.216.3.9      06-18-03    bwadia       Added include file 'Qvgamenu.h'.
                                           Added new function 'QVGAFormatMenuLine()'.
                                           existing function limits line size to just 20 Chrs.
                                           Added new function QVGARemoveNull(..). 
   2.221          07-25-03    LAM          merged 8.10 with TS01                                                                                     
   2.222          07-29-03    JOY          In 'QVGAFormatMenuLine()'_RADIOLARGE processing
                                           is modified.
   2.223          08-07-03    JOY          In 'QVGAFormatMenuLine()' under _RADIOMENU, if current
                                           menu is 'WeldResultSetupMenu' 'GetSelectedResultParam()'
                                           is called, which build menuLine for particular item. 
   2.224          08-26-03    JOY          Estop display for QVGA is added in functions 'ShowEstopMessageOn()',
                                           -'ShowEstopMessageOff()'.
   2.225          09-09-03    JOY          Moved 'CODES' struct to menu.h.
                                           Added 'QVGABUCMenu()'.
   2.226          10-03-03    JOY          "=" is not added in case of 'FreqOffsetSignChoice'.
   2.227          10-13-03    JOY          Added 'IsSWConfigured()'.
   2.228          11-26-03    JOY          Moved ESTOP Message display to the qvgamenu.c.
   2.229          12-02-03    BEKymer      Merged 2.228 & 2.220.1.1 to create 2.229
                                            for Ver9.00b build
   2.230          12-10-03    BEKymer      Added 'extern MENU BransonDefaultMenu[];'
   2.231          02-05-04    VSharma      DUPS_CurrParamSet is updated before enter to BUC Menu
                                           in BUCMenu() & QVGABUCMenu().
   2.232          02-12-04    BEkymer      Added two new secret codes - Testing & Special
   2.233          02-20-04    VSharma      Call QVGAFillInSpecialChrs() in QVGAFormatMenuLine()
                                           in case of submenu.
                                           Added BransonFunctionFlag in DebugMenu(),EnableTestingMenu() &
                                           EnableSpecialsMenu().
                                           Added QVGARestoreFactoryDefaults().
   2.234          04-06-04    VSharma      Called BuildMenu in case of UPDATEDISPLAY key if
                                           HornscanMenu is displayed.
   2.235          05-21-04    VSharma      Modified BuildMenu() for ALARM mask1 & mask2 conditions.
   2.236          06-15-04    BEKymer      Changed RVELOCITY to RVELOCITY_AEF
   2.237          07-12-04    LAM          Added 2 actuator a/d speeds
   2.238          07-14-04    BEKymer      Added 2 secret codes to select which
                                            system controller is installed
                                           Moved defines for number of codes to menu.h
   2.239          07-21-04    JOY          Removed '=' from the DATE menu item string in QVGAFormatMenuLine().
   2.240          07-22-04    JOY          CurrentSetup.SystemControllerFlag is saved in to the BBRAM.
   2.241          07-23-04    LAM          A/D variables are saved in to the BBRAM.
   2.242          07-30-04    JOY          Modified FREQOFFSET format.
   2.243          08-24-04    LAM          Added fast actuator a/d speed
   2.244          09-17-04    BEKymer      Move function prototypes to menu.h
                                            where they belong
   2.245          04-05-05    LAM          added loadcell and sbeam hidden codes
   2.246          04-15-05    LAM          reordered hidden codes
   2.247          05-04-05    Aare         made SWConfiguration and HWConfiguration global
   2.248          07-25-05    Bwadia       QVGAFormatMenuLine function modified for new objects
                                           and Asian Language support added.
                                           BuildMenu function supports new objects.
                                           FormatNum, InsertProperUnits modified for 
                                           Asian Languages.
                                           VGARemoveNull function added.
   2.248.1.0      08-25-05    Aare         Added DISTANCE3 format, modified FormatVariable to use it.
   2.248.1.1      08-25-05    Aare         Added functions and hidden codes for encoder reset on ULS/SS.
   2.248.1.2      08-25-05    Aare         Added DUPS Control hidden code and function, copied function from BUC Menu.
   2.248.1.3      09-10-05    Aare         Added SBL and HSC hidden codes.
   2.251          09-11-05    Aare         Merged with 2.250 (10f and 10h)
   2.252          09-20-05    Bwadia       Only one hidden code entry required for DUPS HSC
                                           menu entry
   2.253          10-11-05    Bwadia       PS wattage variable supported in FormatMenuLine
                                           and QVGAFormatMenuLine function
   2.254          11-22-05    Bwadia       HS compare and SBL secret function execution
                                           done under a single function
   2.255          12-20-05    Bwadia       3/2 decimal place implementation corrected
                                           Modified for tracker issue 3977
   2.256          01-10-06    Bwadia       'digitalpsMenu' menu opened when DUPS control
											                                password entered. Modified for tracker 3963
   2.244.2.0      05-17-05    BEKymer      Change BUC menu password
                                           Add secret code to enable PLC Control menu   
   2.244.2.1      12-07-05    BEKymer      Add duplicate entry in secret code structure to
                                            patch bug.  Real issue not understood yet.
   2.257          01-10-06    LAM          Merged BBRaun Special, added metric/uscs encoder
   2.258          01-10-06    LAM          added metric/uscs encoder prototypes
   2.260          03-02-06    Bwadia       Secret code for trigger menu added
   2.260.1.0      12-22-06    NHAhmed      Removed the hidden menus for DUPS HSC, Move Part Contact and
                                           Minimum Trigger, and changed FormatNum() for DISTANCE3 format.
   2.260.1.1      12-26-06    NHAhmed      Updated DisplayMenu() function.
   2.260.1.2      01-10-07    NHAhmed      Made changes for DISTANCE3 format.
   2.260.1.3      01-31-07    NHAhmed      Changes related to Changed Structure variables of CHOICE and TOGGLE.
   2.260.1.4      02-07-07    NHAhmed      Moved function prototypes for Secret Codes from menu.c to menu.h.
   2.260.1.5      02-07-07    NHAhmed      Removed unused #define.
   2.261          10-22-07    NHAhmed      Changes done for LangTest phase 0
   2.262          12-03-07    BEKymer      Add hidden codes to enable / disable
                                            recal error code 300.
                                           Check in as 2.262 on tip  
   2.263          04-14-08    NHAhmed      Replicated function FormatVariable() and FormatNum()
                                           as FormatVariables() and FormatNums()
   2.264          09-02-08    NHAhmed      CleanUp for multi-language support.
   2.265          09-04-08    YGupta       CleanUp for LangTest Project.
   2.266          09-09-08    NHAhmed      CleanUp for multi-language support.
   2.267          09-10-09    BEkymer      Add new define MICRO where needed
   2.268          09-22-09    YGupta       Rearrange SecretCode[] for MICRO.
   2.269          10-02-09    BEkymer      Force MICRO to US encoder
                                           Change MEAVINGHOME code to match keypad
   2.270          10-05-09    BEKymer      Modify hidden code "266344772326" to
                                            force 2" stroke & 40 mm diameter.                                   
                                           Remove duplicate code
                                           Make ConfigureMICROSbeam() work the
                                            same as ConfigureAEDSbeam() and
                                            ConfigureAEFSbeam().
   2.271          10-21-09    BEKymer      Add functions to set control level
                                            from hidden codes.
   2.272          10-23-09    BEKymer      Change BUC menu code
                                           Add code for changing control levels
                                           Add code to save calibration
   2.273          11-03-09    BEKymer      Correct BUC menu code
   2.274          06-08-10    PDwivedi     Added BUC menu code to configure standard MICRO.
   2.275          09-01-10    BEKymer      Added func for FT 61 to set leaving home force
   2.276          03-25-11    PDWivedi     Added Secret menu function for Baxter velocity limit.
   2.276.2.1      11-23-17		HSAN	   Added functions to add compatibility of new encoders.
   
*/                                         

/*
 ------------------------------- DESCRIPTION ---------------------------------
*/


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include <psos.h>
#include <prepc.h>
#include "names.h" 
#include "menu.h"
#include "menu2.h"
#include "menu4.h"
#include "menu5.h"
#include "menu7a.h"
#include "genrlmsg.h"
#include "fpkp_msg.h"
#include "kpresmsg.h"             /* key pressed message definition   */
#include "error.h"
#include "keypad.h"
#include "preset.h"
#include "param.h"
#include "beep.h"
#include "ck_qsend.h"           /* contains function interface           */
#include "fmtstrs.h"
#include "selctkey.h"
#include "menu1.h"
#include "led.h"
#include "util.h"
#include "portable.h"
#include "weld_obj.h"
#include "getmsg.h"
#include "genalarm.h"
#include "menuhorn.h"
#include "menutest.h"
#include "statedrv.h"
#include "display.h"
#include "rtclock.h"
#include "dups_api.h"
#include "string.h"
#include "inports.h"
#include "psnvram.h"
#include "actnvram.h"
#include "qvgamenu.h"
#include "ready.h"
#include "battram.h"


/*------------------------------- LOCAL DEFINES ----------------------------*/

#define SOLIDBLOCK  0xbe    /* Character substuted for '|' on display */
#define CHANGEDISTFORMATVAL 10000  /*Value at which distance format in Metric*/
                                      /*changes from 3 decimal to 2 decimal     */

#define CENTURY         2000
/*------------------------------- GLOBAL DATA ------------------------------*/
/*                       (scope is global to ALL files)                     */

UINT8    MainKeyFlag = FALSE;
UINT8    GoBackFlag = FALSE;
UINT8    PowerUpColdStart = FALSE;

UINT8    ExitMenuCounter = 0;

SINT8    ScrollBuffer[SCROLLBUFFERSIZE];

BOOLEAN  TestSonicsFlag = FALSE;
BOOLEAN  SubmenuFlag;

SINT16   MenuCounter = -1;
SINT16   HornMenuCount;
SINT16   BlankMenuCounter = 0;

SINT32   SecurityLevel = BRANSON;

// VARIABLE TYPE TABLE DEFINITION
//
// This table defines the features of various types of numerical items that
// can appear on a menu.  The source for each item is a SINT32, but there are
// many ways of converting this to text.  A DISTANCE value stored in the
// SINT32 as 54321 should be displayed as 5.4321 if USCS units are selected,
// or should be converted to metric if metric units are selected.  So
// conversion factors and the number of digits left and right of the decimal
// point must be in the table.  Also, there are items for which the entire
// available resolution is not displayed.  A VELOCITY stored as 653 will
// display as 6.5 in/s in USCS units.  The table therefore specifies a
// conversion for USCS (English) as well as Metric.  In the English
// conversion, the value in the SINT32 may be divided by 10, 100, or some
// other power of 10.
//
// Conversions are accomplished by taking the stored SINT32 (n) and finding:
//
//    x = (n * ConvMult + ConvDiv/2) / ConvDiv;
//

struct var_format_def2 VarFormatTable[] =
{
  {{ "%   ", 3, 0,  1, FALSE, 1,  1 }, { "%   ", 3, 0,  1, FALSE,   1,    1 }},
  {{ "lb  ", 4, 0,  1, FALSE, 1, 10 }, { "N   ", 4, 0,  1, FALSE,4448,10000 }},
  {{ "lb  ", 4, 1,  1, FALSE, 1,  1 }, { "N   ", 4, 0,  1, FALSE,4448,10000 }},
  {{ "s   ", 2, 3,  1, FALSE, 1,  1 }, { "s   ", 2, 3,  1, FALSE,   1,    1 }},
  {{ "PSI ", 3, 1,  1, FALSE, 1,  1 }, { "kPa ", 3, 0,  1, FALSE, 689, 1000 }},
  {{ "in  ", 1, 4,  1, FALSE, 1,  1 }, { "mm  ", 3, 2,  1, FALSE, 254, 1000 }},
  /* DISTANCE3, requires special handling for 7-character strings */
  {{ "in  ", 1, 4,  1, FALSE, 1,  1 }, { "mm  ", 2, 3,  1, FALSE, 254, 100  }},
  {{ "Hz  ", 5, 0,  1, FALSE, 1,  1 }, { "Hz  ", 5, 0,  1, FALSE,   1,    1 }},
  {{ "Hz  ", 4, 0,  1,  TRUE, 1,  1 }, { "Hz  ", 4, 0,  1,  TRUE,   1,    1 }},
  {{ "J   ", 3, 1,  1, FALSE, 1,  1 }, { "J   ", 3, 1,  1, FALSE,   1,    1 }},
  {{ "    ", 9, 0,  1, FALSE, 1,  1 }, { "    ", 9, 0,  1, FALSE,   1,    1 }},
  {{ "in/s", 2, 1,  1, FALSE, 1, 10 }, { "mm/s", 4, 0,  1, FALSE, 254, 1000 }},
  {{ "W   ", 4, 0,  1, FALSE, 1,  1 }, { "W   ", 4, 0,  1, FALSE,   1,    1 }},
  {{ "    ", 5, 0,  1, FALSE, 1,  1 }, { "    ", 5, 0,  1, FALSE,   1,    1 }},
  {{ "    ", 2, 0,  1, FALSE, 1,  1 }, { "    ", 2, 0,  1, FALSE,   1,    1 }},
  {{ "%   ", 3, 1,  1, FALSE, 1,  1 }, { "%   ", 3, 1,  1, FALSE,   1,    1 }},
  {{ "J   ", 5, 0,  1, FALSE, 1, 10 }, { "J   ", 5, 0,  1, FALSE,   1,   10 }},
  {{ "    ", 4, 0,  1, FALSE, 1,  1 }, { "    ", 4, 0,  1, FALSE,   1,    1 }},
  {{ "s   ", 8, 3,  1, FALSE, 1,  1 }, { "s   ", 8, 3,  1, FALSE,   1,    1 }},
  {{ "um  ", 3, 0,  1, FALSE, 1,  1 }, { "um  ", 3, 0,  1, FALSE,   1,    1 }},
  {{ "W   ", 4, 0,  1, FALSE, 1,  1 }, { "W   ", 4, 0,  1, FALSE,   1,    1 }}
};

    struct var_format_AmpPower VarFormatTableAmpPower[] =
	{
		  {{ "%   ", 3, 1,  1, FALSE, 1,  1 }, { "W   ", 4, 0,  1, FALSE,  1,    100 }},
		  {{ "%   ", 3, 0,  1, FALSE, 1,  1 }, { "um  ", 3, 0,  1, FALSE, 1,    100 }}
	};
/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

void UpdateDUPSRAMParamSet(void);
void LangStrCpy (SINT8 * to , SINT8 * from);
UINT16 LangStrLen(SINT8 * str);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void DistanceULS(void);
void EnableStringDebug(void);
void DisableStringDebug(void);
void UpdateCalibDefault(void);

#define BUCMENUID       10
#define DEFAULTID      128
#define DUPSMENUID      12
#define TFMENUID       129

/*--------------------------------------------------------------------------*/
/*  The following structure is for special codes that are entered while on  */
/*  main menu.  Each code will call a function. The entires required for    */
/*  each code are:                                                          */
/*                                                                          */
/*      Password - at least 8 digits, must be all numeric, no max limit     */
/*      A pointer - a pointer to keep track of digits entered so far        */
/*      A function -  a function to call when the code has been entered     */
/*      ID - if this code is required to display a menu on VGA.  In this    */
/*           case an SBC code change is probably required.  If not, set     */
/*           this field to NULL.                                            */
/*                                                                          */
/*--------------------------------------------------------------------------*/



CODES SecretCode[NUMBER_OF_CODES] = {
/* Password       Ptr Function            ID        */
/* -------------  --- ------------------  ---       */
 {"19002726866",  0,  BUCMenu,            BUCMENUID }, /* 0  1-900-Branson               */
 {"33284437",     0,  DebugMenu,          NULL      }, /* 1  "DEBUGGER" on phone pad     */
 {"3492288726",   0,  InitializeBBR,      NULL      }, /* 2  "FIXBATTRAM" on phone pad   */
 {"534922868726", 0,  ConfigureAed,       NULL      }, /* 3  5 + "FIXACTNVRAM"           */
 {"634922868726", 0,  ConfigureAef,       NULL      }, /* 4  6 + "FIXACTNVRAM"           */
 {"6060099456",   0,  VelocityOn,         NULL      }, /* 5  Code is built at power up   */
 {"6030399654",   0,  VelocityOff,        NULL      }, /* 6  Code is built at power up   */
 {"789456123",    0,  CreateSecretCodes,  NULL      }, /* 7  Code to enable other codes  */
 {"741236987",    0,  EnableDiagnostics,  NULL      }, /* 8  Circle on keypad            */
 {"3228679",      0,  RestoreDefaults,    DEFAULTID }, /* 9  Factory on keypad           */
 {"741852963",    0,  EnableTestingMenu,  NULL      }, /* 10 Down keypad columns L to R  */
 {"963852741",    0,  EnableSpecialsMenu, NULL      }, /* 11 Down keypad columns R to L  */
 {"2326667569",   0,  SlowActADComm,      NULL      }, /* 12 "ADCommSlow" on phone pad   */
 {"2326663278",   0,  FastActADComm,      NULL      }, /* 13 "ADCommFast" on phone pad   */
 {"756937232666", 0,  SlowerActADComm,    NULL      }, /* 14 "SlowerADComm" on phone pad */
 {"102242379",    0,  SelectOldBoard,     NULL      }, /* 15 EDP#-old system controller  */
 {"102242594",    0,  SelectNewBoard,     NULL      }, /* 16 EDP#-new system controller  */
 {"266344572326", 0,  ConfigAEDSbeam,     NULL      }, /* 17 CONFIG+5+SBEAM for AED      */
 {"266344672326", 0,  ConfigAEFSbeam,     NULL      }, /* 18 CONFIG+6+SBEAM for AEF      */
 {"26634472326",  0,  ConfigSBeam,        NULL      }, /* 19 config actuator to SBEAM    */
 {"2663446232",   0,  ConfigLoadcell,     NULL      }, /* 20 config actuator to Loadcell */
 {"34882623858",  0,  DistanceULS,        NULL      }, /* 21                             */
 {"3488262388",   0,  DistanceSS,         NULL      }, /* 22                             */
 {"38772668765",  0,  DupsControl,        DUPSMENUID}, /* 23                             */
 {"7522668765",   0,  EnablePLCTiming,    NULL      }, /* 24 "PLC Control"               */
 {"3622588",      0,  EnableUSEncoder,    NULL      }, /* 25                             */
 {"3622566",      0,  EnableMetricEncoder,NULL      }, /* 26                             */
 {"3622583",      0,  EnableTF,           TFMENUID  }, /* 27 Enable trigger force menu   */
 {"2633300633",   0,  DisableCode300,     NULL      }, /* 28 "Code300Off" on phone pad   */
 {"263330066",    0,  EnableCode300,      NULL      }, /* 29 "Code300On" on phone pad    */
 {"101",          0,  EnableStringDebug,  NULL      }, /* 30 Enable String no. display   */
 {"102",          0,  DisableStringDebug, NULL      }, /* 31 Disable String no. display  */
 {"266344772326", 0,  ConfigMICROSbeam,   NULL      }, /* 32 CONFIG+7+SBEAM for MICRO    */
 {"87746472833",  0,  SetSpringRate3,     NULL      }, /* 33 use 3 for LEAVINGHOMEFORCEMICRO */
 {"87746472834",  0,  SetSpringRate4,     NULL      }, /* 34 use 4 for LEAVINGHOMEFORCEMICRO */
 {"22542728466",  0,  SaveCalibration,    NULL      }, /* 35 Save calibration values     */
 {"2668539351",   0,  SetContLevelt,      NULL      }, /* 36 Set control level to t      */
 {"2668539353",   0,  SetContLevelea,     NULL      }, /* 37 Set control level to ea     */
 {"2668539354",   0,  SetContLeveld,      NULL      }, /* 38 Set control level to d      */
 {"2668539355",   0,  SetContLevelf,      NULL      }, /* 39 Set control level to f      */
 {"2668539350",   0,  SetContLeveldepot,  NULL      }, /* 40 Set control level to depot  */
 {"2668539359",   0,  SetContLeveltest,   NULL      }, /* 41 Set control level to test   */
 {"101134290",    0,  Config50mmMICRO,    NULL      }, /* 42 Set New Micro Actuator      */
 {"159134348",    0,  ConfigOriginal_MICRO,NULL     }, /* 43 Set New Micro Actuator      */
 {"100143190",    0,  MicroEncoder,	NULL     	    }, /* 44 Set MicroE encoder  Manufacturer: CELERA MOTION 
														Manufacturer Part Number: 195-00710    */
 {"100143175",    0,  OLDEncoder,		NULL     	}, /* 45 Encoder manufacturer GSI	 */
 {"229837",       0,  ConfigMaxMinValues,  NULL     }, /* 46 Set Min max values for BAXTER*/
};


/*-------------------- End of Special Codes section ------------------------*/


MENU *CurrentlyDisplayedMenu = 0;      /* Allows rest of system to peek at */
                                       /* current menu. */

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern UINT8   RunScreenFlag;
extern UINT8   AlarmDetectedFlag, SetupAlarmDetectedFlag;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;

extern UINT16  RadioIndex;
extern UINT16  DiagFlag;
extern UINT16  DebugPasswordFlag;
extern BOOLEAN DebugBase;
extern BOOLEAN DebugBytes;
extern BOOLEAN OnboardDiag;
extern UINT16  TestingMenuFlag;
extern UINT16  SpecialMenuFlag;
extern UINT16  BransonFunctionFlag;
extern UINT16  MicroHomeForce;

extern UINT32  KeyMask;

extern enum LEVEL AccessLevel;



extern SETUPS_Ver800 CurrentPreset;
extern CONFIGSETUP   CurrentSetup;
extern BUCMENU_800   BUCMenuRAM;
extern QVGA_MENU_INFO MenuLevelInfo[];
extern BOOLEAN QVGAEstopDisplay;
extern UINT16 ResultDisplayPos[];
extern DEPOT_FLAGS  *DepotFlag;

//extern INBITS        Inp;

extern UINT32 WmgrQid;
extern RTC RTCMenu;

/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

static UINT32                 PsosReturnValue;
static UINT32                 PsosStatus;
static GENERIC_MSG            WeldMsgOut;
UINT32                 HWConfiguration;
UINT32                 SWConfiguration;

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

/*
 ---------------------------------- CODE -------------------------------------
*/

void DistanceULS(void)
{
   CurrentSetup.DistanceULS = TRUE;
}

void DistanceSS(void)
{
   CurrentSetup.DistanceULS = FALSE;
}

void EnableHSCandSBL(void)
{
   UpdateSWConfiguration(HSC, TRUE);               /* Enable HSC  */
   BransonFunctionFlag = TRUE; 
   UpdateSWConfiguration(SBL_EN, TRUE);
   CurrentSetup.SBLEnable = TRUE;
}

void DisableHSCandSBL(void)
{
   UpdateSWConfiguration(HSC, FALSE);               /* Disable HSC  */
   BransonFunctionFlag = FALSE; 
   UpdateSWConfiguration(SBL_EN, FALSE);
   CurrentSetup.SBLEnable = FALSE;
}

void VelocityOn(void)
{
   BUCMENU_800  *BUCMenuBBR;

   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   SecretCode[5].Ptr = SecretCode[5].Password;
   UpdateSWConfiguration(VEL, TRUE);               /* Set velocity reporting on  */
   BUCMenuRAM.VelocityReporting = TRUE;                                             
   BUCMenuBBR->VelocityReporting = TRUE;                                             
}



void VelocityOff(void)
{
   BUCMENU_800  *BUCMenuBBR;
   UINT16 Index;

   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   SecretCode[6].Ptr = SecretCode[6].Password;
   UpdateSWConfiguration(VEL, FALSE);              /* Set velocity reporting off */
   BUCMenuRAM.VelocityReporting = FALSE;
   BUCMenuBBR->VelocityReporting = FALSE;
   
   /* if Act. Type is AEF & VEL is configured, then RVELOCITY is already
      configured reset it*/
   for(Index = 1; Index < 5; Index++)
   {
      if(CurrentSetup.WeldParamOption[Index] == RVELOCITY_AEF &&
         CurrentSetup.Actuator == AEF)
         CurrentSetup.WeldParamOption[Index] = 0;
   }
   ResultDisplayPos[RVELOCITY_AEF] = BIT0; //NOT_DISPLAY      
   
}



void CreateSecretCodes(void)
/***************************************************************************/
/*                                                                         */
/*  This function will create secret codes using the power supply serial   */
/*  number as part of the code.  This helps to ensure this code will only  */
/*  work on one system.  The base code below is the starting point.  All   */
/*  zeros and nines will be replaced with values from the serial number.   */
/*                                                                         */
/***************************************************************************/
{
   static STR VelocityOnStr[]  = "6060099"; /* Base code, not machine specific */
   static STR VelocityOffStr[] = "6030399"; /* Base code, not machine specific */
   UINT16 TempSum1, TempSum10, x;
   
/*  The first code is to enable velocity reporting - machine specfic */

   SecretCode[5].Ptr = VelocityOnStr;
   SecretCode[5].Password = VelocityOnStr;
   if ((CurrentSetup.PSSerialNumber[7] >= '0') && (CurrentSetup.PSSerialNumber[7] <= '9'))
      VelocityOnStr[1] = CurrentSetup.PSSerialNumber[7];
   else 
      VelocityOnStr[1] = '9';
   if ((CurrentSetup.PSSerialNumber[9] >= '0') && (CurrentSetup.PSSerialNumber[9] <= '9'))
      VelocityOnStr[3] = ('9' - CurrentSetup.PSSerialNumber[9]) + '0';
   else
      VelocityOnStr[3] = '9';
   VelocityOnStr[5] = '0';  /* Temporarily set to zero for checksum */
   VelocityOnStr[6] = '0';  /* Temporarily set to zero for checksum */
   TempSum1 = 0;
   TempSum10 = 0;
   for (x=0; x<(sizeof(VelocityOnStr)-1); x++) {  /* Start checksum calculation */
      TempSum1 += (UINT16)(VelocityOnStr[x] - '0');
      if (TempSum1 > 9) {
         TempSum10++;
         TempSum1 -= 10;
      }
   }
   VelocityOnStr[5] = (TempSum10 + '0');
   VelocityOnStr[6] = (TempSum1 + '0');
   VelocityOnStr[7] = 0;


/*  The second code is to disable velocity reporting - machine specfic*/

   SecretCode[6].Ptr = VelocityOffStr;
   SecretCode[6].Password = VelocityOffStr;
   if ((CurrentSetup.PSSerialNumber[8] >= '0') && (CurrentSetup.PSSerialNumber[8] <= '9'))
      VelocityOffStr[1] = ('9' - CurrentSetup.PSSerialNumber[8]) + '0';
   else   
      VelocityOffStr[1] = '9';
   if ((CurrentSetup.PSSerialNumber[6] >= '0') && (CurrentSetup.PSSerialNumber[6] <= '9'))
      VelocityOffStr[3] = CurrentSetup.PSSerialNumber[6];
   else
      VelocityOffStr[3] = '9';
   VelocityOffStr[5] = '0';  /* Temporarily set to zero for checksum */
   VelocityOffStr[6] = '0';  /* Temporarily set to zero for checksum */
   TempSum1 = 0;
   TempSum10 = 0;
   for (x=0; x<(sizeof(VelocityOffStr)-1); x++) { /* Start checksum calculation */
      TempSum1 += (UINT16)(VelocityOffStr[x] - '0');
      if (TempSum1 > 9) {
         TempSum10++;
         TempSum1 -= 10;
      }
   }
   VelocityOffStr[5] = (TempSum10 + '0');
   VelocityOffStr[6] = (TempSum1 + '0');
   VelocityOffStr[7] = 0;
}



void BUCMenu(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu for the Branson Menu.                                             */
/*                                                                         */
/***************************************************************************/
{
   UINT16   SaveLine1[NUM_OUTPUT_DEVICES];
   UINT16   SaveSelectKey1;
   UINT16   SaveSingleSelect;
   UINT16   MenuLines;              /* Number of choices in menu */

   AccessLevel = BRANSON;
   UpdateDUPSRAMParamSet(); /*Update DUPS_CurrParamSet before enter to BUC Menu */
}



void DupsControl(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu for the DUPS controlMenu.                                         */
/*                                                                         */
/***************************************************************************/
{
   UINT16   SaveLine1[NUM_OUTPUT_DEVICES];
   UINT16   SaveSelectKey1;
   UINT16   SaveSingleSelect;
   UINT16   MenuLines;              /* Number of choices in menu */

   AccessLevel = BRANSON;
   UpdateDUPSRAMParamSet(); /*Update DUPS_CurrParamSet before enter to BUC Menu */
}



void EnableTF(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu for the Enable trigger force                                      */
/*                                                                         */
/***************************************************************************/

{
   AccessLevel = BRANSON;
}



void DisableCode300(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the recal error code 300 to be disabled.      */
/*  This must be changed by a secret code.  The default is to have error   */
/*  code 300 enabled.                                                      */
/*                                                                         */
/***************************************************************************/
{
   BUCMENU_800  *BUCMenuBBR;

   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   SecretCode[28].Ptr = SecretCode[28].Password;
   UpdateSWConfiguration(CAL, FALSE);           /* Turn off error code 300  */
   BUCMenuRAM.RecalCode300 = FALSE;
   BUCMenuBBR->RecalCode300 = FALSE;
}



void EnableCode300(void)
/***************************************************************************/
/*                                                                         */
/*  This function will re-enable recal error code 300.  This is also the   */
/*  default condition.  It will be enabled whenever the system control     */
/*  level is set.                                                          */
/*                                                                         */
/***************************************************************************/
{
   BUCMENU_800  *BUCMenuBBR;

   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   SecretCode[29].Ptr = SecretCode[29].Password;
   UpdateSWConfiguration(CAL, TRUE);            /* Turn on error code 300   */
   BUCMenuRAM.RecalCode300 = TRUE;                                             
   BUCMenuBBR->RecalCode300 = TRUE;                                             
}

void EnableStringDebug(void)
{
}

void DisableStringDebug(void)
{
}

void EnableDiagnostics(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to enable the onboard diagnostics.                                */
/*                                                                         */
/***************************************************************************/
{
   OnboardDiag = TRUE;         /* This turns on the diagnostics via RS-232 */
}



void EnableTestingMenu(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to enable the onboard diagnostics.                                */
/*                                                                         */
/***************************************************************************/
{
   TestingMenuFlag = TRUE;     /* This turns on the diagnostics via RS-232 */
   BransonFunctionFlag = TRUE; /*Display the Specials menu on Diagnostic Screen.*/
}



void EnableSpecialsMenu(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to enable the onboard diagnostics.                                */
/*                                                                         */
/***************************************************************************/
{
   SpecialMenuFlag = TRUE;     /* This turns on the diagnostics via RS-232 */
   BransonFunctionFlag = TRUE;/*Display the Specials menu on Diagnostic Screen.*/
}



void DebugMenu(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu for the debug menu.                                               */
/*                                                                         */
/***************************************************************************/
{
   DebugPasswordFlag = TRUE;    /* This will allow display in DIAG menu    */
   DebugBase = TRUE;            /* Default to number base 16 (hexidecimal) */
   DebugBytes = TRUE;           /* Default to 2 bytes                      */
   BransonFunctionFlag = TRUE; /*Display the Specials menu on Diagnostic Screen.*/
}



void RestoreDefaults(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu for the factory defaults menu.  This will display a list of       */
/*  functions, each will set certain groups of values back to factory      */
/*  defaults.  The groups are:                                             */
/*      User I/O - disable most, assign original ones (cycle abort &       */
/*                 display lock), set active hi/lo back to default         */
/*      Actuator settings - ULS, TRS and ground detect switch states       */
/*      BBR settings - alarm masks, trigger setting, ramps                 */
/*      Printing - print on sample, print on alarm all off                 */
/*      Global - all of the above in one step                              */
/*                                                                         */
/***************************************************************************/
{
   AccessLevel = BRANSON;
}



void FastActADComm(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to speed up the communication speed between the 332 and the       */
/*  actuator a/d(~2.4Mhz)                                                 */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   CurrentSetup.Sclk7890Act = FAST_CLK;  /* Actuator a/d SCK  */
   CurrentSetup.ClockPhase = CLOCK_PHASE;   /* need to invert signal when 
                                             Sclk7890Act is slowed down */
   BBRPtr->Sclk7890Act = FAST_CLK;
   BBRPtr->ClockPhase = CLOCK_PHASE;
}



void SlowActADComm(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to slow down the communication speed between the 332 and the      */
/*  actuator a/d(~1.72Mhz)                                                 */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   CurrentSetup.Sclk7890Act = SLOWSPEED;  /* Actuator a/d SCK  */
   CurrentSetup.ClockPhase = INVERTCLK;   /* need to invert signal when 
                                             Sclk7890Act is slowed down */
   BBRPtr->Sclk7890Act = SLOWSPEED;
   BBRPtr->ClockPhase = INVERTCLK;
}

   

void SlowerActADComm(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when the proper code is entered on the main    */
/*  menu to slow down the communication speed between the 332 and the      */
/*  actuator a/d(~1.51Mhz)                                                 */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   CurrentSetup.Sclk7890Act = SLOWERSPEED;/* Actuator a/d SCK  */
   CurrentSetup.ClockPhase = INVERTCLK;   /* need to invert signal when 
                                             Sclk7890Act is slowed down */
   BBRPtr->Sclk7890Act = SLOWERSPEED;
   BBRPtr->ClockPhase = INVERTCLK;
                                             
}



void SelectOldBoard(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the user I/O J3-36 and J3-8 selections to be  */
/*  swapped.  The new board swapped the pins and the software (again) was  */
/*  adjusted to handle it.  This puts them back on the original pin.       */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   UpdateHWConfiguration(PC379, TRUE);
   UpdateHWConfiguration(PC594, FALSE);
   CurrentSetup.SystemControllerFlag = FALSE;
   BBRPtr->SystemControllerFlag = FALSE;
}



void SelectNewBoard(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the user I/O J3-36 and J3-8 selections to be  */
/*  swapped.  The new board swapped the pins and the software (again) was  */
/*  adjusted to handle it.  This puts them back on the swapped pin.        */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   UpdateHWConfiguration(PC594, TRUE);
   UpdateHWConfiguration(PC379, FALSE);
   CurrentSetup.SystemControllerFlag = TRUE;
   BBRPtr->SystemControllerFlag = TRUE;
}


void EnablePLCTiming(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the menu option "PLC Control" to be displayed */
/*  in the System Configuration menu right after Handheld.  This feature   */
/*  removes the trigger lost in weld and trigger lost in hold alarms,      */
/*  effectively allowing the start signal to control the weld time.  Once  */
/*  the menu is enabled, it can only be turned off by initializing the BBR.*/
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   CurrentSetup.PLCControlMenuFlag = TRUE;
   BBRPtr->PLCControlMenuFlag = TRUE;
}


void EnableUSEncoder(void)
/***************************************************************************/
/*                                                                         */
/*  This function will configure the system with a US Encoder              */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   CurrentSetup.USEncoder = TRUE;
   BBRPtr->USEncoder = TRUE;
}


void EnableMetricEncoder(void)
/***************************************************************************/
/*                                                                         */
/*  This function will configure the system with a Metric Encoder          */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   CurrentSetup.USEncoder = FALSE;
   BBRPtr->USEncoder = FALSE;
}



void ConfigSBeam(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the user to configure the actuator interface  */
/*  board to run the SBEAM                                                 */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
}



void ConfigAEDSbeam(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to an AED  */
/*  with the SBEAM.                                                        */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_AED, LENGTH_4, SIZE3_0);
   EnableMetricEncoder();
}



void ConfigAEFSbeam(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to an AEF  */
/*  with the SBEAM.                                                        */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_AEF, LENGTH_4, SIZE3_0);
   EnableMetricEncoder();
}



void ConfigMICROSbeam(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to a MICRO */
/*  with the SBEAM and US encoder.                                         */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_MICRO, LENGTH_2, SIZE_40);
   EnableUSEncoder();
}

void ConfigOriginal_MICRO(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to a MICRO */
/*  with the SBEAM and US encoder.                                         */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_MICRO, LENGTH_2, SIZE_40);
   EnableUSEncoder();
   SetManufacturer( ENCODER_MICROE );
}


void MicroEncoder(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to a MICRO */
/*  with the encoder EDP 100-143-190   Manufacturer: celera motion MicroE  */
/*                                                                         */
/***************************************************************************/
{

   SetManufacturer( ENCODER_MICROE );
 
}

void OLDEncoder(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to a MICRO */
/*  with the encoder EDP 100-143-175 manufacturer: GSI & amphenol          */
/*                                                                         */
/***************************************************************************/
{

   SetManufacturer( ENCODER_OLD );

}

void Config50mmMICRO(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initializes the actuator interface board to a MICRO */
/*  with 50mm stroke length and US encoder.                                         */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(SBEAM);
   ConfigureActuatorBoard (NVR_MICRO,LENGTH_50, SIZE_40);
   EnableUSEncoder();
}

void SetSpringRate3(void)
/***************************************************************************/
/*                                                                         */
/*  This function will change the leaving home force to 3 and save it in   */
/*  BBR so at power up it can be retrieved.                                */
/*                                                                         */
/***************************************************************************/
{
   BUCMENU_800  *BUCMenuBBR;

   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   SecretCode[33].Ptr = SecretCode[33].Password;
   BUCMenuRAM.MicroHomeForce = FALSE;                                             
   BUCMenuBBR->MicroHomeForce = FALSE;
   MicroHomeForce = LEAVINGHOMEFORCEMICROLO;   
   RecordAlarm(W8);                                             
}



void SetSpringRate4(void)
/***************************************************************************/
/*                                                                         */
/*  This function will change the leaving home force to 4 and save it in   */
/*  BBR so at power up it can be retrieved.                                */
/*                                                                         */
/***************************************************************************/
{
   BUCMENU_800  *BUCMenuBBR;

   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   SecretCode[34].Ptr = SecretCode[34].Password;
   BUCMenuRAM.MicroHomeForce = TRUE;                                             
   BUCMenuBBR->MicroHomeForce = TRUE;                                             
   MicroHomeForce = LEAVINGHOMEFORCEMICROHI;   
   RecordAlarm(W8);                                             
}



void SetSpringRateMicroFT(UINT8 MicroForce)
/***************************************************************************/
/*                                                                         */
/*  This function will change the leaving home force to passed value and   */
/*  save it in BBR so at power up it can be retrieved.                     */
/*                                                                         */
/***************************************************************************/
{
   BUCMENU_800  *BUCMenuBBR;

   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   BUCMenuRAM.MicroHomeForce = TRUE;                                             
   BUCMenuBBR->MicroHomeForce = TRUE;                                             
   MicroHomeForce = MicroForce;   
   RecordAlarm(W8);                                             
}



void SaveCalibration(void)
/***************************************************************************/
/*                                                                         */
/*  This function will save the most recent calibration.                   */
/*                                                                         */
/***************************************************************************/
{
   UpdateCalibDefault();
}



void SetContLevelt(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to t.                         */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   BBRPtr->ControlLevel = LEVEL_t;
   DepotFlag->IsADepot = FALSE;
   CurrentSetup.ControlLevel = BBRPtr->ControlLevel;
   StorePSControlLevel();
}



void SetContLevelea(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to ea.                        */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   BBRPtr->ControlLevel = LEVEL_ea;
   DepotFlag->IsADepot = FALSE;
   CurrentSetup.ControlLevel = BBRPtr->ControlLevel;
   StorePSControlLevel();
}



void SetContLeveld(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to d.                         */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   BBRPtr->ControlLevel = LEVEL_d;
   DepotFlag->IsADepot = FALSE;
   CurrentSetup.ControlLevel = BBRPtr->ControlLevel;
   StorePSControlLevel();
}



void SetContLevelf(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to f.                         */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   BBRPtr->ControlLevel = LEVEL_f;
   DepotFlag->IsADepot = FALSE;
   CurrentSetup.ControlLevel = BBRPtr->ControlLevel;
   StorePSControlLevel();
}



void SetContLeveldepot(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to depot                      */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   BBRPtr->ControlLevel = LEVEL_t;
   DepotFlag->WasADepot = TRUE;
   DepotFlag->IsADepot = TRUE;
   CurrentSetup.ControlLevel = BBRPtr->ControlLevel;
   StorePSControlLevel();
}



void SetContLeveltest(void)
/***************************************************************************/
/*                                                                         */
/*  This function will set the control level to test                       */
/*                                                                         */
/***************************************************************************/
{
   CONFIGSETUP *BBRPtr;
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   BBRPtr->ControlLevel = LEVEL_TEST;
   DepotFlag->IsADepot = FALSE;
   CurrentSetup.ControlLevel = BBRPtr->ControlLevel;
   StorePSControlLevel();
}



void ConfigLoadcell(void)
/***************************************************************************/
/*                                                                         */
/*  This function will allow the user to configure the actuator interface  */
/*  board to run the LoadCell                                              */
/*                                                                         */
/***************************************************************************/
{
   SetForceGauge(LOAD_CELL);
}



void SendKeyToWeldMngr(MSG_OPCODE_TYPE Opcode, BOOLEAN State)
{
   WeldMsgOut.lword1 = State;                                      
   WeldMsgOut.common.opcode = Opcode;
   CkQSend (WmgrQid,&WeldMsgOut,FRONT_PANEL_STATE_COORDINATOR
            ,__LINE__,MILLS_TO_TICKS(50));      /* 50 ms        */
}



void DisplayResetMsg(void)
{
   UINT32 OrigKeyMask;

   OrigKeyMask = KeyMask;      /* Don't allow Test key to sneak between */
   KeyMask &= ~TESTKEYMASK;    /* Reset and RunKey */

   tm_wkafter( SECONDS_TO_TICKS( 1 ));

      ClearKeypadBuffer(TRUE);  /* Drop keys pressed while msg on */
      SendFakeKeyPress(RunKey);
      BlankMenuCounter = 1;     /* Don't redisplay current menu before exit */
   KeyMask = OrigKeyMask;
}

void UpdateHWConfiguration(enum MASK1 HWConfig, BOOLEAN Enabled)
{

     if(Enabled)
        HWConfiguration = HWConfiguration | HWConfig;
     else 
        HWConfiguration = HWConfiguration & (~HWConfig);
        
}       

void UpdateSWConfiguration(enum MASK2 SWConfig, BOOLEAN Enabled)
{

     if(Enabled)
        SWConfiguration = SWConfiguration | SWConfig;
     else 
        SWConfiguration = SWConfiguration & (~SWConfig);
        
}

BOOLEAN IsHWConfigured(UINT16 HWType)
/***************************************************************************/
/*Description:                                                             */
/* Checks particular H/W is configured.                                    */
/*Input Parameters:                                                        */
/* HWType- H/W needs to be detected.                                       */
/***************************************************************************/
{
   BOOLEAN IsAvail = FALSE;
   
   switch(HWType)
   {
      case DUPS:
         if(HWConfiguration & DUPS)
            IsAvail = TRUE;
      break;
      
      case QVGA:
         if(HWConfiguration & QVGA)
            IsAvail = TRUE;
      break;
      
      case VGA:
         if(HWConfiguration & VGA)
            IsAvail = TRUE;
      break;

      default:
         IsAvail = FALSE;
      break;  
   }
   return(IsAvail);
}


BOOLEAN IsSWConfigured(UINT32 SWType)
/***************************************************************************/
/*Description:                                                             */
/* Checks particular S/W is configured.                                    */
/*Input Parameters:                                                        */
/* HWType- S/W needs to be detected.                                       */
/***************************************************************************/
{
   BOOLEAN IsAvail = FALSE;
   switch(SWType)
   {
      case EC:
         if(SWConfiguration & EC)
            IsAvail = TRUE;
      break;
      
      case CUS:
         if(SWConfiguration & CUS)
            IsAvail = TRUE;
      break;
      
      case WS:
         if(SWConfiguration & WS)
            IsAvail = TRUE;
      break;
      
      case DEPO:
         if(SWConfiguration & DEPO)
            IsAvail = TRUE;
      break;
      
      case V_OL:
         if(SWConfiguration & V_OL)
            IsAvail = TRUE;
      break;
      
      case C_OL:
         if(SWConfiguration & C_OL)
            IsAvail = TRUE;
      break;
      
      case F_OL:
         if(SWConfiguration & F_OL)
            IsAvail = TRUE;
      break;
      
      case P_OL:
         if(SWConfiguration & P_OL)
            IsAvail = TRUE;
      break;
      
      case HE:
         if(SWConfiguration & HE)
            IsAvail = TRUE;
      break;
      
      case ALR:
         if(SWConfiguration & ALR)
            IsAvail = TRUE;
      break;
      
      case VEL:
         if(SWConfiguration & VEL)
            IsAvail = TRUE;
      break;
      
      default:
           IsAvail = FALSE;
      break;
      
   }
   return(IsAvail);
}

void InsertProperUnits(SINT8 text[], enum FORMAT UnitFlag)
/***************************************************************************/
/*                                                                         */
/*  This function will remove the '&' in the passed text string and        */
/*  replace it with the proper units based on the passed UnitFlag and the  */
/*  current units selected (SI or US).  If CurrentSetup.Units equals TRUE  */
/*  then SI units are selected.                                            */
/*  Support for Asian Language provided                                    */
/*  The location where the subsitution started will be returned.           */
/*                                                                         */
/***************************************************************************/
{
   SINT8  *UnitText;
   UINT8  ChrCount;
   SINT16 Index;
   struct var_format_def1 *FormatPtr;
   UINT16 * ptr = (UINT16 *)text;

   if (CurrentSetup.Units)
      FormatPtr = &VarFormatTable[UnitFlag].Metric;
   else
      FormatPtr = &VarFormatTable[UnitFlag].English;

   Index = 0;
   
      while (text[Index] && (text[Index] != '&'))
         Index++;

      if (text[Index] == '&')
      {
         UnitText = FormatPtr->Units;

         for (ChrCount=0; (ChrCount < 4) && (text[Index] == '&'); ChrCount++)
            text[Index++] = *UnitText++;

      }
}

void DisplayMenu(MENU list[])
/***************************************************************************/
/*                                                                         */
/*  This function will scan through the structures which define the menus. */
/*  It will decide which entries should appear on the display at this      */
/*  time.  A list will be created which is valid for this pass only.  It   */
/*  is the intent that this function be reentrant and any sub-menu will    */
/*  simply call this function again.                                       */
/*                                                                         */
/*  The first set of switch statements will determine which things will    */
/*  appear in the menu list.  The second set will actually deal with       */
/*  putting the data and text into the buffer to be displayed.             */
/*                                                                         */
/***************************************************************************/
{
   UINT8    NewKey, i;
   UINT8    ExitFlag;

   SINT8    HmenuCounter = -1;

   UINT16   MenuLines;              /* Number of choices in menu */
   UINT16   SelectedItem;           /* Index of item on line 2 of 4 */
   SINT16   ScrollIndexStart;
   SINT16   ScrollIndexEnd;

   UINT16   Index;
   UINT16   StartLine;              /* First line to update next pass */
   UINT16   TermStartLine;          /* First line on terminal to update next pass */
   UINT16   SaveDiagFlag;           /* Temp storage */

   UINT16   SaveLine1[NUM_OUTPUT_DEVICES];
   UINT16   SaveSelectKey1;
   UINT16   SaveSingleSelect;

   UINT16   CheckLine1[NUM_OUTPUT_DEVICES];
   UINT16   CheckSelectKey1;
   UINT16   CheckSingleSelect;

   MENU      local[MAXSUBMENUS+5];  /* Allow space for ENDLISTs at end */
   BOOLEAN   LevelChanged;/* Unfortunate kludge, see notes under Select1Key */
   BOOLEAN   HDReady, DidTest;
   BOOLEAN   KeyPressed;
   UINT8     ExitKey;
   BOOLEAN   JumpMenu;

   MENU      *RestorePrevMenu;  /* Remembers menu displayed before this one */

   CONFIGSETUP *BBRPtr;         /* Allows saving to BBR in case of power interruption */

   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   MenuCounter++;
   RestorePrevMenu = CurrentlyDisplayedMenu;
   CurrentlyDisplayedMenu = list;   /* Allow other tasks to see which menu this is */
   UpdateLED(OFFLED, OFF);          /* .. Turn off the OFF led */

   for (i=0; i < NUMBER_OF_CODES; i++) {     /* Reset all secret code pointers */
      SecretCode[i].Ptr = SecretCode[i].Password;
   }

   /* AT: if we are in CalibrateForceMenu1 and access level is below maintenance
      while we have passwords on - set access level to maintenance so we won't
      ask for password in the middle of calibration. It seems to be the step all
      calibration procedures go through, so every calibration should be covered. */

   StartLine = 1;    /* Line of display to write next */
   TermStartLine = 1;

   SaveLine1[VF_DEVICE] = 1;
   SaveLine1[TERM_DEVICE] = 1;

   SaveSelectKey1 = 1;
   SaveSingleSelect = 1;

   ExitFlag = FALSE;

   while (ExitFlag != TRUE)   /* Main menu loop */
   {                          /* Enter with StartLine set to next screen */
      if(MenuCounter == 0)    /*  line (1-4) to update, usually 1 */
         MainKeyFlag = FALSE;

      if(BlankMenuCounter > 0)  /* If counter nonzero, don't display menu */
         BlankMenuCounter--;
     
      StartLine = 1;      /* Next pass through update whole screen unless */
      TermStartLine = 1;  /* code processing keys doesn't want to do this. */

      /* Code to take some special action depending on what's in key queue: */

      /* Want to reset the access level to OPERATOR only if the system is */
      /* waiting for a keypress at the main menu.  Must not have a keypress */
      /* available because there are times when system passes through the */
      /* main menu on the way to someplace else and these times we do NOT */
      /* want to reset the access level. */

      /* Also want to throw out left/right arrow keypresses unless there */
      /* are no other keys in the buffer.  This prevents wild scrolling of */
      /* weld results due to accumulated keypresses. */

      do
      {
         KeyPressed = KeyAvailable(TRUE);

        NewKey = GetMsg(TRUE);

      } while (KeyPressed && (NewKey == LeftKey || NewKey == RightKey));

      if (NewKey < FIRSTCONTROLMESSAGE)  /* Process keypresses */
      {
         switch(NewKey)
         {

            case TestKey:
               SaveDiagFlag = DiagFlag;    /* Need to disable Diagnostics */
               DiagFlag = FALSE;           /* if going to Test. */


               JumpMenu = DoTestMode( &ExitKey, &DidTest );
               DiagFlag = SaveDiagFlag;

               if (JumpMenu && MenuCounter > 0)
               {                                 /* Force jump to next menu */
                  MainKeyFlag = TRUE;
                  ExitFlag = TRUE;
               }

               if (JumpMenu && (ExitKey != MainKey)) /* If JumpMenu TRUE will */
               {                                     /* go to Main Menu anyway */
                  SendFakeKeyPress( ExitKey );
                  BlankMenuCounter = 1;      /* Block display of Main Menu */
               }

               break;
   
            case ResetKey:
               DisplayResetMsg();   /* Will only get this key on run screen */
               break;

                
            default:
               Beep(ERRORBEEP);
               break;
         } /* End of switch(NewKey) */
      }
      else
      {
         ProcessControlMessage(NewKey);
      }

   } /* End of while ExitFlag != TRUE */

   CurrentlyDisplayedMenu = RestorePrevMenu ;
   MenuCounter--;
}

/****************************************************************************/
/*                                                                          */
/* Converts the given value into an ASCII string showing a variable of the  */
/* given format. The string is written to the supplied String[] right-      */
/* justified and with spaces filling in unused space to the left.           */
/* This function, unlike FormatNumber(), performs conversion to external    */
/* units.                                                                   */
/*                                                                          */
/* Input Parameters:                                                        */
/*                                                                          */
/*    Value - Value to display                                              */
/*    format - Format to display value in (PERCENT, DISTANCE, etc.)         */
/*    String[] - Output string                                              */
/*    MaxLen - Max character space in String[] (not incl. terminator)       */
/*    Metric - TRUE if value should be displayed in metric units            */
/*                                                                          */
/****************************************************************************/
void FormatVariables( SINT32 Value, enum FORMAT format, SINT8 String[],
 UINT8 MaxLen, BOOLEAN Metric )
{
   SINT32 Number;
   
   Number = ConvertInternalExternal( Value, format, Metric );
   if (Metric && (format == DISTANCE) && CurrentSetup.Metric3Flag)
   {
      if (Number < CHANGEDISTFORMATVAL)
      {
         Number = ConvertInternalExternal( Value, DISTANCE3, Metric );
         FormatNums( Number, DISTANCE3, String, MaxLen, Metric );
      }
      else
         FormatNums( Number, format, String, MaxLen, Metric );
   }
   else 
      FormatNums( Number, format, String, MaxLen, Metric );

}

/****************************************************************************/
/*                                                                          */
/* Converts the given number into an ASCII string showing a variable of the */
/* given format. The string is written to the supplied String[] right-      */
/* justified and with spaces filling in unused space to the left.           */
/* Conversion to displayable units is assumed to have been done.            */
/* Support for Asian Language provided where each char is of two bytes      */
/* Input Parameters:                                                        */
/*                                                                          */
/*    Value - Value to display                                              */
/*    format - Format to display value in (PERCENT, DISTANCE, etc.)         */
/*    String[] - Output string                                              */
/*    MaxLen - Max character space in String[] (not incl. terminator)       */
/*    Metric - TRUE if value should be displayed using metric units         */
/*                                                                          */
/****************************************************************************/
void FormatNums( SINT32 Number, enum FORMAT format, SINT8 String[],
 UINT8 MaxLen, BOOLEAN Metric )
{
   UINT8 ChrCount, Digits;
   SINT8 *cptr;
   SINT8 SignChr;
   struct var_format_def1 *FormatPtr;
  
   if (Metric)                         /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;

   if (Number < 0)
   {
      Number = -Number;
      SignChr = '-';
   }
   else
      SignChr = '+';

   cptr = String;
   for (ChrCount=0; ChrCount<MaxLen; ChrCount++)  /* Blank out input string */
      *cptr++ = ' ';

   cptr = &String[ChrCount-1];      /* Point to last chr in string */
   Digits = FormatPtr->RightDigits;

   if (Digits)          /* If necessary, write digits to right of decimal */
   {
      while (ChrCount && Digits)
      {
         *cptr-- = (Number%10) + '0';
         ChrCount--;
         Number /= 10;
         Digits--;
      }
      if (ChrCount)
      {
         *cptr-- = '.';
         ChrCount--;
      }
   }

   if (ChrCount)     /* Write left part if space in string */
   {
      Digits = FormatPtr->LeftDigits; /* Max # of digits to write this step */
      if (Digits > ChrCount)  /* Don't write more than there's space for */
         Digits = ChrCount;
      if (Number)
      {
         while (Digits && Number)
         {
            *cptr-- = (Number%10) + '0';
            ChrCount--;
            Number /= 10;
            Digits--;
         }
      }
      else
      {
         *cptr-- = '0';   /* Always one chr left of decimal point */
         ChrCount--;
      }
   }

   if (ChrCount && (FormatPtr->ShowSign || SignChr == '-'))
   {
      *cptr = SignChr;     /* Add sign */
   }  
}



/****************************************************************************/
/*                                                                          */
/* Converts the value passed in, which is in the specified format, into a   */
/* form that can be displayed.  This may involve scaling by factors of ten  */
/* or unit conversions.  The end result is a SINT32 that can be converted  '*/
/* to ASCII and displayed, with a decimal point placed as determined by the */
/* format.                                                                  */
/*                                                                          */
/****************************************************************************/
SINT32 ConvertInternalExternal( SINT32 Value, enum FORMAT format,
 BOOLEAN Metric )
{
   SINT32 RetVal;
   struct var_format_def1 *FormatPtr;

   if (Metric)                         /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;

   /*if ( format ==MICRONS)
	{

		if(CurrentSetup.AmpMicronsFlag==FALSE)
			FormatPtr =  &VarFormatTableAmpPower[MIC].Percent;
		else
			FormatPtr =  &VarFormatTableAmpPower[MIC].Unit;
		VarFormatTableAmpPower[MIC].Unit.ConvMult= CurrentSetup.AmpMicronsValue;
	}
	if ( format ==POWERWATTS)
	{

		if(CurrentSetup.PeakPowerWattsFlag==FALSE)
			FormatPtr =  &VarFormatTableAmpPower[POWER].Percent;
		else
			FormatPtr =  &VarFormatTableAmpPower[POWER].Unit;
		VarFormatTableAmpPower[POWER].Unit.ConvMult= CurrentSetup.PSWatt;
	}*/
   /* Perform conversion from stored units to displayed units */

   if (Value < 0)
      RetVal = 0 - ((((0-Value)*FormatPtr->ConvMult) + (FormatPtr->ConvDiv/2))/
        FormatPtr->ConvDiv);
   else
      RetVal = ((Value*FormatPtr->ConvMult) + (FormatPtr->ConvDiv/2))/
        FormatPtr->ConvDiv;

   return( RetVal );
}



/****************************************************************************/
/*                                                                          */
/* Converts the value passed in to internal storage units.  Passed number   */
/* is binary form of what was entered or displayed, minus a decimal point.  */
/* Conversion may scale by factors of ten or convert units, but end result '*/
/* is suitable for storage.                                                 */
/*                                                                          */
/****************************************************************************/
SINT32 ConvertExternalInternal( SINT32 Number, enum FORMAT format,
 BOOLEAN Metric )
{
   SINT32 RetVal;
   struct var_format_def1 *FormatPtr;

   if (Metric)                         /* Point to format info */
      FormatPtr = &VarFormatTable[format].Metric;
   else
      FormatPtr = &VarFormatTable[format].English;
   /* Perform conversion from displayed units to stored units */

   if (Number < 0)
      RetVal = 0-((((0-Number) * FormatPtr->ConvDiv) +
    (FormatPtr->ConvMult/2))/(FormatPtr->ConvMult));
   else
      RetVal = ((Number * FormatPtr->ConvDiv) +
    (FormatPtr->ConvMult/2))/(FormatPtr->ConvMult);

   return( RetVal );
}

void ShowEstopMessageOn(void)
{
   Beep(PSOSBEEP);
}



void ShowEstopMessageOff(void)
{
  
}



/****************************************************************************/
/*                                                                          */
/* Returns a pointer to the menu list used to generate the menu currently   */
/* being shown by DisplayMenu().  The pointer returned has the same value   */
/* as was passed to DisplayMenu() to put the menu on the screen.            */
/*                                                                          */
/* Caveats: This function only works when the current screen text was put   */
/*          there by DisplayMenu().  If GetCurrentMenu() is called during   */
/*          Horn Down, Test, or some other mode that does its own display   */
/*          output, GetCurrentMenu() will return a pointer to the last menu */
/*          output by DisplayMenu(), not the one currently on the screen.   */
/*                                                                          */
/****************************************************************************/
MENU *GetCurrentMenu(void)
{
   return( CurrentlyDisplayedMenu );                                            
}




void VFAlarmOn(void)
/****************************************************************************/
/*                                                                          */
/* Initiates blinking of the reset LED to indicate that there is an alarm.  */
/*                                                                          */
/****************************************************************************/
{
   UpdateLED(RESETLED, ON);           /* Turn Reset led on */
}

void VFAlarmOff(void)
/****************************************************************************/
/*                                                                          */
/* Stops blinking of the ALARM message in the upper left corner of the      */
/* screen.                                                                  */
/*                                                                          */
/****************************************************************************/
{
   UpdateLED(RESETLED, OFF);
}




void AlarmOn(void)
{
   VFAlarmOn();
}



void AlarmOff(void)
{
   VFAlarmOff();
}

void ConfigMaxMinValues()
{
   SetMaxMinValues();
}
