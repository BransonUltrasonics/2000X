/* $Header:   D:/SWLab/VMdb/2000Series/App/SELCTKEY.C_V   2.199   09 Sep 2008 20:40:06   nhahmed  $ */
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

   Filename: selctkey.c
                                        
   Function name:

*/

/*
 --------------------------------- REVISIONS --------------------------------

   Revision #      Date          Author      Description
   ==========     ========       ======      ===========
      0                                      Initial Version
      1.00        04/29/96       PJ          Moved from menu.c to its own
                                             module.
      2.00        05/08/96       LAM         undeleted beep
      3.00        05/10/96       PJ          MainKeyFlag,HornDownFlag,
                                             TestSonicsFlag,PrintFlag externals.
      4.00        05/15/96       PJ          Corrected warnings
      5.00        05/29/96       PJ          Corrected errors when displaying
                                             text
      6.00        06/05/96       PJ          Added Max Digit test and corrected
                                             Display errors.
      7.00        06/07/96       PJ          Added test for Max Decimal entries
                                             and Inc/Dec/Digit check.
      8.00        06/13/96       PJ          Added code to adjust digital pot
                                             when displaying Diagnostic F Actual.
      9.00        06/20/96       PJ          Added functions UpdateCurrentPreset
                                             and SendFakeKeyPress. Corrected
                                             errors sending preset values to
                                             sysmanger.
      9.01        07/01/96       PJ          Corrected the way Flag data is
                                             sent to the system manager.
      9.02        07/02/96       PhilJ       Corrected bug updating CurrentPreset
                                             with CHOICE type value.
      9.03        07/12/96       PhilJ       Corrected bugs in VARIABLE type
                                             when displaying and editing value
                                             and when decimal is pressed.
     10.00        07-20-96       BEKymer     Moved call to func() to very end
                                             in VARIABLE menu type.                                            
     10.01        07-22-96       BEKymer     Make HornDownFlag a BOOLEAN (so
                                             it can be used in states.c)
     10.10        08/01/96       PhilJ       Corrected Max number of digits
                                             in Energy Mode.
     10.20        08/19/96       PhilJ       Added/Changed code in Alpha menus
                                             to handle Password type menus.
     10.30        08/19/96       PMG         Enabled the Front Panel "Print"           
                                             key. Press Print and menu pops up.
                                             Also changed PrintKeyChoice to   
                                             PrintingMenu which was already
                                             defined in MENU4.C
     10.40        08/22/96       PhilJ       Moved Increment & DecrementFreq-
                                             Offset from menu2 to SelctKey.
     10.50        08/26/96       PhilJ       Deleted code from VARIABLE type
                                             FREQOFFSET.
     10.60        09/04/96       PhilJ       Type TIMEDATE added to enum Format
     10.70        09/11/96       PhilJ       Added scrolling menus for the Run
                                             Screen.
     10.80        09/17/96       PhilJ       Left/Right keys for scrolling menus
                                             now handled in Hsubmenu.

     10.90        09/18/96       LAM         added initflag to sendfakekey
     11.00        09/19/96       PhilJ       Corrected incrementing of ENERGY
                                             value.
     11.10        09/20/96       PhilJ       Corrected decrementing of ENERGY
                                             value above 1000. 
     11.20        09/20/96       PhilJ       If Min/Max error Select3Key emulates
                                             GoBackKey.
     11.30        09/24/96       PhilJ       VARIABLE FREQOFFSET displayed in
                                             menu.c.
     11.40        09/25/96       PhilJ       Modified Hsubmenu to correct
                                             updating of scrolling buffer.
     11.50        09/27/96       PhilJ       Moved Left/Right key controls for
                                             scrolling menus to menu.c.
     11.60        09/30/96       PhilJ       Put back the functions UpPot() and
                                             DecPot(). Accidently deleted.
     11.70        10/09/96       PhilJ       Added DisplayLockFlag check to
                                             type CHOICE.
     11.80        10/16/96       PhilJ       Added Alarm Submenu check to type
                                             TEXT.
     11.90        10/18/96       PhilJ       Enabled Security Checking.
     12.00        10/19/96       PhilJ       Modified UpdateCurrentPreset.
                                             Added English to Metric conversion
     12.00        10/21/96       PhilJ       TOGGLE Now calls UpdateCurrentPreset.
     12.10        10/22/96       PhilJ       Corrected the Setting of Time and
                                             Date. UpdateCurrentPreset now will
                                             also update CurrentPreset Time/Date.
     12.20        10/24/96       PhilJ       Send NOKEY to display AlarmsMenu.
                                             Up/Down LEDs are turned off when
                                             SelectKeys are pressed.
     12.30        10/25/96       PhilJ       Clear AlarmDetectedFlag in TEXT type
     12.40        10/27/96       PhilJ       FreqActualFlag is set if VARIABLE 
                                             type equals BARGRAPH. 
     12.50        10/29/96       LAM         replaced q_send with CkQSend
     12.60        10/30/96       PhilJ       Beeps if bad keys are sent.
                                             Corrected decimal value if bad key
                                             sent.
     12.70        11/01/96       PhilJ       DisplayLock check moved to SUBMENU.
     13.00        11/01/96       LAM         added pressure format       
     14.00        11/12/96       LAM         chged pressure format to xxx.x      
     14.10        11/15/96       PhilJ       Corrected bug displaying Min/Max
                                             errors in FORCE and PRESSURE.
     14.20        11/18/96       LAM         deleted horndown sequence   
     14.30        11-21-96       BEKymer     Cleanup main & goback keys
     15.00        11-27-96       LAM         corrected metric pressure
     15.10        12-11-96       PhilJ       Changed UPDATEDISP to UPDATEDISPLAY
     15.20        12-16-96       PhilJ       In struct type CHOICE added test 
                                             to delete change if MainKey pressed
                                             Corrected Display Lock function.
     15.30        12-31-96       PhilJ       Corrected ClearKey Function in
                                             Struct type ALPHA. Deleted error
                                             beep if UPDATEDISPLAY character
                                             received in VARIABLE type.
     15.40        01-07-97       PhilJ       Corrected bug in aborting Password
                                             menu.
     15.50        01-15-97       PhilJ       Corrected bug depressing select key
                                             in HornDown Menu.
     15.60        01/24/97       LAM         deleted alarmdetectedflag   
     15.70        01-29-97       PhilJ       Corrected selectkey toggle of
                                             Min/Max limits.
     15.80        01-31-97       PhilJ       Changed HorndownFlag & TestSonicsFlag
                                             to HDMenuEnabled & TestMenuEnabled.
     15.90        02-03-97       PhilJ       Corrected Metric Min/Max Limits.
     16.00        02-05-97       PhilJ       Corrected Metric distance readout.
     16.10        02-13-97       PhilJ       Corrected Range error bug, and bug
                                             in TOGGLE type implementation.
     16.20        02-13-97       PhilJ       Corrected bug in WELDTIMES & TESTTIMES
     16.21        02-13-97       PaulG       Added flag to check for update to parameter.
     16.22        02-18-97       PhilJ       Corrected the displaying of distance.
     16.23        02-20-97       PhilJ       Corrected the displaying of millimeters
                                             when pressing +/- Keys.
     16.24        02-21-97       LAM         chged velocity format to xx.xx       
     16.25        02-26-97       PhilJ       SelectKeyCount set to 3 if Variable off.       
     16.26        02-28-97       LAM         fixed freq bargraphs                           
     16.27        03-05-97       PhilJ       Added error beep to Reset Keys.                           
     16.28        03-07-97       PhilJ       Adjusted for distance rounding error
                                             in metric for minimum value.                           
     16.29        03-12-97       PhilJ       Added global AlarmMenuFlag.  Corrected
                                             operation of Up/Down keys per spec.
                                             Disabled Min/Max test on Year variable.
     16.30        03-19-97       PhilJ       Enabled UP/Down Key scrolling of menu.
     16.40        04-04-97       PhilJ       Fixed bug in incorrect parameter value
                                             entered after OffKey selected.
     16.50        04-08-97       PhilJ       Fixed SelectKey bug and F Actual
                                             left/right LED display.
     16.51        04-08-97       LAM         made testpower format as watts              
     16.60        04-10-97       PhilJ       Implemented RADIO type menus.
     17.00        04-15-97       LAM         fixed watts off by factor of 10
     17.10        04-16-97       PhilJ       Added PrinterScaling checks.
     17.20        04-17-97       PhilJ       Added ErrorBeep on Range error.
     17.20        04-18-97       PhilJ       Changed InitFlag to UINT8.
     18.00        04-28-97       LAM         goback will beep when adjusting digpot
     18.10        04-30-97       PhilJ       Added test for Ampstep VARIABLE TYPE.
     19.00        05-07-97       LAM         made sysmqueueid & fpscqid global         
     19.10        05-29-97       PhilJ       fixed bug in Increment/DecrementFreqoffset.
     20.00        06-03-97       LAM         added currentsetupchged flag               
     20.10        06-16-97       PhilJ       New message in UpdateCurrentPreset.
     20.2.99      06-18-97       PhilJ       Deleted WELDTIMES and TESTTIMES check in
                                             CHOICE menus. Added UpdateCurrentPreset()
                                             in RADIO type menus.
     20.3.00      06-19-97       PhilJ       Added missing break in type CHOICE.
     2.1.01       07-03-97       PhilJ       Added enable & disable uart in type
                                             SERIALPORT CHOICE menu.
     2.1.02       07-07-97       PhilJ       Display LEDs in ALPHA type menus.
     2.1.04       07-17-97       PhilJ       Added check in VARIABLE type if
                                             AmpControl is External.
     2.1.05       07.18.97       JBerman     Added: case _ADVFEATURE
                                                  : UpdateSf() -> case Enter Key
     2.1.06       07-23-97       PhilJ       Added SetupKey to all NextKey switch
                                             statements
     2.1.07       07-24-97       PhilJ      Corrected bug in RADIO menus
                                            displaying off on blank line
     2.1.08       07-29-97       BEKymer    Added test in _TEXT for SetupAlarmDetectedFlag
     2.1.09       07-31-97       PhilJ      In case ALPHA, modified MainKey &
                                            GoBackKey for Password Id.
     2.1.10       07-31-97       PhilJ      Fixed Pretrig@Dist to act like Radio
                                            button.
     2.1.11       08-13-97       PhilJ      Corrected bug in CHOICE if SERIALPORT
                                            menu is enabled.
     2.1.12       08-21-97       PhilJ      Added check if Amp Step @ Ext Sig
                                            in type CHOICE.
     2.113        08-21-97       LAM        replaced rightleftledoff with rightleftledon
                                            deleted freqactualflag
     2.114        09-03-97       LAM        redeclared radiomenucounter                 
     2.115        09-11-97       LAM        unit test version,deleted offkey                           
     2.116        09-16-97       PaulG      Modified menu screen display to display 5 digits.
     2.117        09-18-97       LAM        see line 2057(LM note )                                    
     2.118        09-26-97       BJB        Deleted ChoiceSubMenuFlag, which was
                                            never tested.
     2.119        10-10-97       BJB        Fixed bug that could cause random character
                                            (whatever is in RAM) to be output to display.
                                            Also extended EditLine[] to allow for
                                            terminator.
     2.120        10-13-97       BJB        Changes to VARIABLE entry code: Always tests
                                            menu8->disable before writing to DisableFlag,
                                            clears (to activate) enable bit if decimal
                                            point key pressed and enable bit exists,
                                            modified code for if (ChangeFlag == TRUE) and
                                            merged with if (SelectKeyCount > 0), since we
                                            want to do the same thing in both cases.
                                            Changes to CHOICE entry code: Won't allow
                                            "Off" selection if ID is XXCANTCHANGEXX
                                            instead of special case AMPTRIGEXTFLAG, tests
                                            all 3 select keys.
     2.121        10-16-97       BJB        No ref of PasswordEnableFlag, AssignNameComplete.
                                            Added flag AlphaEntryDone.
                                            Deleted flag EnterPasswordFlag.
                                            Rewrote password checking code in SUBMENU case.
                                            Rewrote ALPHA entry code.
                                            Beeps when ClearKey pressed and no chrs to
                                             back up over in ALPHA entry routine.
     2.122        10-21-97       BJB        Removed password checking code, this is
                                             now in MENU.C.
                                            Doesn't include "security.h"
     2.123        10-28-97       BJB        Got rid of flag HDMenuEnabled and code that
                                             ran when this flag was TRUE.
                                            No response to HornDownKey in CHOICE,
                                             VARIABLE, TOGGLE, ADVFEATURE.
     2.124        11-4-97        BJB        Doesn't use MainKeyFlag, PrintFlag,
                                             TestMenuEnabled.
                                            Deleted FreqOffsetFlag.
                                            Doesn't send fake "NOKEY" before displaying
                                             menus.
                                            Doesn't allow menu jumping keys during item
                                             entry.
                                            Consolidated redundant SelectKey processing code.
                                            Removed unnecessary display of CHOICE argument
                                             after EnterKey pressed.
                                            Moved final MoveCursor() call to those sections
                                             that need it.
                                            Beeps if ALARM selected with no submenu and no
                                             function to run.
     2.125        11-08-97                  Got rid of unused InitSelectKey().
                                            Made FpsQueue local to SendFakeKeyPress().
     2.126        11-10-97       LAM        added cleardiagflag to choice
     2.127        11-10-97       BJB        Modified ADVFEATURE code to modify & test only
                                             BIT0.
     2.128        11-11-97       BJB        Added ResetKey response code to CHOICE,
                                             ALPHA, VARIABLE, RADIO, TOGGLE, ADVFEATURE.
                                            For TOGGLE and ADVFEATURE, doesn't run
                                             function unless item changed.
     2.129        11-11-97       BJB        Modified CHOICE entry code so that it
                                             edits temporary value instead of the real
                                             thing.  Copies over on EnterKey.
     2.130        11-20-97       BJB        Item entry code will display RESET COMPLETE
                                             message if reset key pressed.  This moved from
                                             WeldManager().
     2.131        12-02-97       BJB        Modified VARIABLE entry code so that enable/
                                             disable flag isn't changed until EnterKey.
     2.132        12-03-97       BJB        Modified TOGGLE, ADVFEATURE entry code so that
                                            temporary value edited instead of real one.
                                            Modified VARIABLE entry code for FREQUENCY
                                            items so 5 digit entry allowed, number posted
                                            on display properly.
                                            Modified VARIABLE entry code so IncKey, DecKey,
                                            and EnterKey can't be used after ClearKey.

     2.133        12-05-97       BEKymer    New flag - OkToDisplayAlarms
     2.134        12-10-97       BJB        No longer needs special case code for
                                             PASSWORD items.
                                            NOKEY during VARIABLE entry doesn't cause
                                             beep, done to prevent beeping on MinMax error
                                             screen during Test Mode.
                                            Added code to prevent immediate call to
                                             UpdateCurrentPreset() when PASSWORD item
                                             changed.
                                            Don't need SavedPasswordFlag.
     2.135        12-29-97       BJB        Calls WriteDisplay() instead of UpdateVFBuf().
                                            SendFakeKeyPress() calls q_send() directly,
                                             returns pSOS error code.
     2.136        12-31-97       BJB        Deleted special case code in CHOICE entry that
                                             checked for serial port choice.
                                            Added support for term select key, term data
                                             output, and term alarm output to CHOICE, ALPHA,
                                             VARIABLE, RADIO, TOGGLE, and ADVFEATURE code.
                                            Modified ALPHA entry to support terminal.
     2.137        01-12-98       BJB        Modified entry routines to respond to ESTOP
                                             messages.
     2.138        01-26-98       BJB        Modified RADIO code to work with terminal
                                             when more than 3 radio selections.
     2.139        01-29-98       BJB        Modified calls to FormatValue() in
                                             DisplayLastValue() to eliminate leading 00s.
                                            Used FormatSignedInt() to format FREQOFFSET
                                             items.
     2.140        03-10-98       BJB        Uses different max/min, increments on
                                             FreqOffset for 20KHz, 40KHz.
     2.141        03-13-98       BEKymer    Always display Setup alarm menu in
                                            DealWithSelectKey
     2.142        04-05-98       BJB        Prevents erroneous extra processing when
                                             Inc/Dec, Up/Down keys received and not acted
                                             on.
     2.143        04-27-98       LAM        fixed force metric entries
     2.144        04-30-98       BJB        Added code in DisplayLastValue() to display
                                             items of type COUNTER.
                                            Added code to support display/entry of COUNTER
                                             items in VARIABLE entry code.
                                            Moved ALPHA entry code to its own function.
                                            ALPHA entry code modified as follows: Edits in
                                            temporary buffer, copies to final location
                                            only if valid entry; returns value that was
                                            previously assigned to AlphaEntryDone; calls
                                            UpdateCurrentPreset() when item entered; calls
                                            item function only on valid entry.
     2.145        05-15-98       BJB        Rewrote all code related to VARIABLE entry.
     2.146        05-26-98       BJB        Uses new format of FormatNum() and related
                                             functions.
     2.147        05-28-98       BJB        Added support to VARIABLE entry code for items
                                             which always have a sign displayed.
                                            Deleted functions IncrementFreqOffset(),
                                             DecrementFreqOffset(), no longer needed.
     2.148        06-03-98       BJB        Added special-case call to DigitalPotEntry()
                                             when user tries to select this item,
                                             function makes sure system is in READY.
                                            Added special case to call
                                             DigitalTuneEntryScreen() instead of standard
                                             submenu when Digital Tune CHOICE is turned On.
                                            Doesn't turn off DiagFlag in CHOICE code, this
                                             now done by DisplayMenu().
     2.149        06-12-98       BJB        Modified DealWithSelectKey() to use
                                             ProcessControlMessage().
     2.150        06-16-98       BJB        Beeps if user selects DATE item (such as
                                             CalibrationDate) without associated submenu.
     2.151        06-25-98       BJB        Won't update preset if ALLEMPTY passed to
                                             UpdateCurrentPreset().
     2.152        06-25-98       BJB        Added code to set up CopyFeaturesSetting before
                                             displaying alarm menu on which it appears.
     2.153        06-26-98       BJB        Removed changes in 2.152; back to 2.151.
     2.154        06-29-98       PaulG      Removed function UpdatePresetDateandTime() when
                                            current preset is being updated.
     2.155        08-19-98       BJB        Moved SendFakeKeyPress() to GETMSG.C.
                                            Modified RADIO entry code for new screen,
                                             terminal modules.
                                            Modified cursor movement calls in AlphaEntry()
                                             for new screen, terminal modules.
     2.156        08-19-98       LAM        need to modify ALARM case to call a
                                            function before calibration is allowed
     2.157        09-02-98       BJB        Saves & restores up/down LED state in
                                             DealWithSelectKey() and AlphaEntry().
                                            Moved some code that reacts to ResetKey
                                             into DisplayResetMsg().
     2.158        09-04-98       BJB        Checks for ENERGY item out of range at start
                                             of VARIABLE entry, corrects problems if
                                             variable was just turned on from "Off".
     2.159        09-23-98       BJB        Clears screen after DisplayMinMaxError().
     2.160        11-11-98       LAM        needed to add a check if in calibration and the
                                            goback or main key is pressed when the entry
                                            was a VARIABLE type.
     2.161        12-07-98       BJB        AlphaEntry() routine supports full alphabet
                                             from terminal.
                                            Made some variable entry subroutines global so
                                             they can be accessed from new menu code.
     2.162        10-26-99       JZ         substituted SetDateAndTime() with RtcWrite()
     2.163        12-16-99       LAM        removed unused error handling code
     2.163.6.1    02-23-00       OFI        removed #include "features.h"; removed case _ADVFEATURE
                                            removed calls to UpdateSF();
     2.164        04-06-00       JZ         merged Lang to trunk  
     2.165        05-26-00       SCM        Checked in for testing by Laura, John.  
     2.166        06-02-00       SCM        Added the code for the _RADIOLARGE menu
                                            in DealWithSelectKey() function.                                       
     2.167        06-14-00       SCM        Changed the condition check in  function AlphaEntry().
     2.168        06-15-00       SCM        Fixed a minor problem which was crashing the system, relating 
                                            to the RADIOLARGE menu.
    2.169         07-07-00   BEKymer/DJL    fixed SETUP
    2.170         07-22-00       SCM        Made changes in case RADIOLARGE in function DealWithSelectKey()
    2.171         07-26-00       SCM        Made further changes in case RADIO to account for the 
                                            function UpdateDupsPresetStatus() .
    2.172         08-21-00       AT         Modified DealWithSelectKey for RADIO menus (function assumed 3 chars for on/off)
    2.173         08-24-00       AT         Modified DealWithSelectKey for RADIOLARGE menus (function assumed 3 chars for on/off)
    2.174         08-25-00       LAM        fixed RADIOLARGE menu to point to menu16
    2.175         09-06-00       AT         DealWithSelectKey updated for terminal and radio items
    2.176         09-06-00       AT         DealWithSelectKey - corrected NULL pointer access for menu8
    2.177         09-22-00       BEKymer    Remove convert to uppercase in AlphaEntry()
    2.178         10-04-00       AT         line 574 - added Id > DUPS_PARAM_OFFSET
    2.179         10-09-00       AT         line 1180 - call menu8->func only on enter key while in Setup menu
    2.180         10-18-00       SCM        Defined externs at a different location. 
    2.181         01-08-01       BEKymer    Add argument to TEXT and SUBMENU function calls
                                             Fix bug in case _HHMM & _DATE so menu is only called
                                             if there really is one.  Make both cases function the same.
    2.180.3.1     06-10-03       bwadia     "VarInfo" struct defenition is moved to
                                            "Selctkey.h"(for global access).  

    2.180.1.0     09-17-01       BEKymer    Modify CHOICE menus so XXCANTCHANGEXX won't allow changes
    2.182         10-11-01       LAM        merged 8.Specials with preset cleanup.
    2.183         08-04-03       BEKymer    Merged 2.182 and 2.180 creating 2.183 for 9.00A build
    2.184         10-20-03       BEKymer    Add test in TOGGLE for XXCANTCHANGEXX    
    2.185         12-05-03       BEKymer    Merged 2.180.3.1 & 2.184 to create 2.185
                                             for Ver9.00b build
    2.186         02-02-04       VSharma    Make 'CurrentPreset.Verified' FALSE if any preset data
                                             is changed.
    2.187         02-19-04       VSharma    Modify RADIOLARGE menus so XXCANTCHANGEXX won't allow changes.
    2.188         03-09-04       VSharma    Modified'DisplayLockFlag' as a member of struct INBITS.
    2.189         09-21-04       JOY        OFF value is removed from Amplitude step, Forcestep, pretrig menu variables.
    2.190         02-10-05       BEKymer    In AlphaEntry() turn on left LED whenever 
                                             right key is pressed.  After all, if we
                                             just moved right, must be able to come
                                             back left.  A bug since the beginning
                                             of time.  Fixed in version 9.03b.                                                 
    2.191         06-10-05       Aare       Moved StrAlpha1 and StrAlpha2 here because they are not in menutext.c anymore.
    2.192         22-12-06       NHAhmed    Made changes for DISTANCE3 format.
    2.193         10-01-06       NHAhmed    Made changes for DISTANCE3 format.
    2.194         10-22-07       NHAhmed    Changes done for LangTest phase 0
    2.195         01-11-08       NHAhmed    Added a new function UpdateCurrentPreset1 for multi-language support which is 
                                            the modified form of function UpdateCurrentPreset.
    2.196         04-14-08       NHAhmed    Renamed function UpdateCurrentPreset1() as UpdateCurrentPresetAndSetup().
    2.197         09-02-08       NHAhmed    CleanUp for multi-language support.
    2.198         09-04-08       YGupta     CleanUp for LangTest Project.
    2.199         09-09-08       NHAhmed    CleanUp for multi-language support.

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
#include "fpdatmsg.h"
#include "fpkptype.h"
#include "menu.h"
#include "preset.h"
#include "ticks.h"
#include "error.h"
#include "keypad.h"
#include "beep.h"
#include "ck_qsend.h"           /* contains function interface           */
#include "genrlmsg.h"           /* generic message type               */
#include "selctkey.h"
/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/

#include "sc.h"
#include "display.h"
#include "fmtstrs.h"
#include "kpresmsg.h"
#include "menu1.h"
#include "menu5.h"
#include "menu3.h"
#include "menu7.h"
#include "menu7a.h"
#include "led.h"
#include "util.h"
#include "getmsg.h"
#include "state.h"
#include "statedrv.h"
#include "snsrcalb.h"
#include "digout.h"
#include "spidd.h"
#include "menupass.h"
#include "genalarm.h"
#include "sysmangr.h"
#include "serial.h"
#include "rtclock.h"

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                     
/*
 ------------------------------- EXTERNAL DATA --------------------------------- 
*/ 
extern UINT8 InitFlag;
extern UINT8 GoBackFlag;
extern UINT8 RunScreenFlag;
extern UINT8 AlarmDetectedFlag, SetupAlarmDetectedFlag;

extern SETUPS_Ver800 CurrentPreset;
extern SETUPS_Ver800 MinLimit, MaxLimit;

extern CONFIGSETUP CurrentSetup;
extern UINT32 SysmQueueId;

extern enum   WELD_SEQUENCE_TYPE CurrentSequence;
extern UINT16  CalibrationPassed;
extern INBITS Inp;


/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

UINT16   CurrentSetupChgedFlag = FALSE;


/*
 --------------------------- LOCAL TYPE DECLARATIONS -------------------------
*/                            
 /*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

/*
 ---------------------------- EXTERNAL FUNCTIONS -----------------------------
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -----------------------
*/
/*
 ---------------------------------- CODE -------------------------------------
*/

void UpdateCurrentPreset(enum PARAM Id, SINT32 Value1, UINT16 Value2)
{
   EDIT_PARAM_MSG_QUEUE_TYPE           EditParamMsg;

   if (Id != ALLEMPTY)
   {
  
      if ((Id < CURRENT_SETUP_OFFSET) || (Id > DUPS_PARAM_OFFSET))
      {
         CurrentPreset.PresetUpdateComplete = FALSE;
         CurrentPreset.Verified = FALSE;
         EditParamMsg.common.opcode = OP_CHANGE_PRESET_DATA;
      }
      else
      {
         CurrentSetupChgedFlag = TRUE;
         EditParamMsg.common.opcode = OP_CHANGE_CURRENT_SETUP;
      }

      EditParamMsg.param_id = Id;          /* from param.h */
      EditParamMsg.value1 = Value1;       /* SINT32 data  */
      EditParamMsg.value2 = Value2;       /* UINT16 data  */
      CkQSend (SysmQueueId,&EditParamMsg,FRONT_PANEL_STATE_COORDINATOR,
                  __LINE__,MILLS_TO_TICKS(20));         /* 20 ms        */
   }
}

void UpdateCurrentPresetAndSetup(void)
{
   GENERIC_MSG                     genericMsg;

   CurrentPreset.PresetUpdateComplete = FALSE;
   CurrentPreset.Verified = FALSE;
   genericMsg.common.opcode = OP_CHANGE_PRESET_DATA;
   CkQSend (SysmQueueId,&genericMsg,FRONT_PANEL_STATE_COORDINATOR,
                  __LINE__,MILLS_TO_TICKS(20));         /* 20 ms        */
}
