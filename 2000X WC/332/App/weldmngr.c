/* $Header:   D:/databases/VMdb/2000Series/App/WELDMNGR.C_V   2.336.1.0.1.2.1.2   Jan 03 2018 09:33:10   RCHAPA  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 2009           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/*   Module name:                                                           */
/*                                                                           */
/*   Filename:                                                              */
/*                                                                          */
/*   Function Name: WeldManager                                             */
/*                                                                          */
/*            Written by:   Mark Lazarewicz                                 */
/*                  Date:   02/11/96                                        */
/*              Language:   "C"                                             */
/*                                                                          */
/*---------------------------------- REVISIONS -----------------------------*/
/*                                                                          */
/*  Revision#  Date      Author      Description                            */
/*  =========  ========  ==========  ===========                            */
/*     0       02/11/96  Mark L      Initial Shell                          */
/*     1       04/11/96  Mark L      Spring Cleanup                         */                                         
/*     2       04/18/96  Mark L      Add data for weld calcs                */
/*     3       04/27/96  Mark L      Weld data calculations                 */
/*     4       04/29/96  Mark L      send psuedo key kludge                 */
/*     5       06-03-96  BEKymer     Add MENUSYNCSTATE case                 */
/*                                   Uncommented TRIGGEREDSTATE             */
/*     6       06/05/96  Lam         fixed some of end of weld results      */
/*     7       06/10/96  Lam         fixed more end of weld results         */
/*     8       06/26/96  Lam         fixed more end of weld results         */
/*     9       06/26/96  Lam         fixed updating running preset          */
/*    10       07-09-96  BEKymer     Added TRIGGERDELAYSTATE                */
/*                                       Changed msg from WELD to WELDING   */
/*                                       Changed msg from HOLD to HOLDING   */
/*    11       07/23/96  Lam         fixed weld results                     */
/*    12       08-09-96  BEKymer     New ready messages for new weld modes  */
/*    13       09-12-96  BEKymer     Removed static from mSObject array     */
/*                                   Send final data to print manager       */
/*    14       09-18-96  BEKymer     Removed call to UpdatePreset in PBState*/
/*    15       08/06/96  MAL         Support weld data upload               */
/*    16       09/19/96  LAM         modified code                          */
/*    17       09/24/96  LAM         modified trigger state                 */                                                                          
/*    18       10-02-96  BEKymer     Display state message in OP_HERE_IS_PR */
/*    19       10-03-96  BEKymer     Remove while(1) pSos error loops       */
/*                                   Make last line in TRIGGEREDSTATE       */
/*                                   and else                               */
/*    20       10/07/96  LAM         send fakekey = selectkey               */                                                                          
/*    21       10-07-96  BEKymer     Set flag when reset received in OP_    */
/*                                   RESET_KEY_PRESSED                      */
/*    22       10-09-96  BEKymer     New state message for PreReady         */
/*                                   Use Object data instead of weld data   */
/*    23       10/23/96  PaulG       Removed extra qsend for FinalResults   */
/*    24       10-23-96  BEKymer     Sens 1ms only when needed              */
/*    25       10-24-96  BEKymer     put date and time into FinalResults    */
/*    26       10-24-96  LAM         commented out printed graphs           */
/*    27       10-24-96  LAM         commented pbstate                      */
/*    28       10-25-96  BEKymer     Clear AlarmsDetectedFlag in RESET case */
/*    29       10-25-96  LAM         deleted estop messages                 */
/*    30       10-29-96  LAM         replaced q_send with CkQSend           */
/*    31       11-02-96  BEKymer     Handle bad preset in PBSTATE           */
/*                                   Deal with Test key better              */
/*                                   Send MainKey to exit horndown          */
/*    32       11-05-96  BEKymer     Remove dry cycle messages at end of job*/
/*    33       11-06-96  LAM         shorten resend time                    */
/*    34       11-07-96  BEKymer     New case UPDATEDATASTATE               */
/*    35       11-08-96  PaulG       Activate 1ms data                      */
/*    36       11-14-96  BEKymer     In test mode, reset key now removes    */
/*                                   test menu and simulates Go Go Back key */
/*    37       11-16-96  LAM         deleted timeretcheck                   */
/*    38       11-18-96  LAM         chged horndown keypressed              */
/*    39       11-21-96  BEKymer     Handle GoBack and Main key if in horn  */
/*                                   down or test mode, else pass it on     */
/*    40       11-22-96  BEKymer     If main key pressed always clear Test  */
/*                                   SonicsFlag & HornDownFlag              */
/*    41       12-05-96  BEKymer     Send MainKey when in HD & GoBack press */
/*    42       12-06-96  PhilJ       If Reset key pressed clear AlarmFlag.  */
/*    43       12-09-96  BEKymer     If Reset key pressed clear reset led.  */
/*                                   When exiting horndown only set flag &  */
/*                                   not do an SVOff                        */
/*    44       12-16-96  BEKymer     CheckProcessLimits in WAITFORULSCLEAR  */
/*                                   instead of UPSTROKE state              */
/*    45       12-30-96  BEKymer     If in Horndown when Reset is received  */
/*                                   then still clear alarm and Reset Led   */
/*    46       01-03-97  LAM         commented out systemok check in statechg*/
/*    47       01-07-97  PhilJ       If HornDownMenu enabled GoBackKey is   */
/*                                   instead of MainKey.                    */
/*    48       01-31-97  PhilJ       Deleted sending GoBackKey if TestKey   */
/*                                   is hit twice                           */
/*    49       02-04-97  LAM         deleted updatedisp msg                 */
/*    49.01    02-06-97  LAM         added push and pop after preset verify */
/*    50.      02-07-97  LAM         added clearing of updateflags every rec*/
/*                                   only updatetopline when on runscreen   */
/*    51       02-14-97  LAM         chged test key                         */
/*    52       02-14-97  PaulG       removed AbortKey.                      */
/*    53       02-18-97  LAM         change which state limits are checked  */
/*    54       02-19-97  PhilJ       Added metric values to TopLine Data    */
/*    55       02-21-97  LAM         chged test mode                        */
/*    56       02-26-97  PhilJ       Added EMERGENCYSTOPRESET state         */
/*    57       02-27-97  PhilJ       Corrected bug in EMERGENCYSTOPRESET    */
/*    57.01    02-27-97  LAM         fixed test key                         */
/*    57.10    03-05-97  PhilJ       Modified code to OP_RESET_KEY_PRESSED  */
/*    57.20    03-05-97  PhilJ       chged GetDateandTime in FINALDATASTATE */
/*    58.00    03-05-97  LAM         chged updatetopline & endofsonics      */
/*    58.10    03-05-97  PhilJ       Corrected MenuCounter in PBSTATE       */
/*    58.20    03-06-97  PhilJ       Deleted ErrorBeep if ResetKey in Ready */
/*    58.30    03-13-97  PhilJ       Recoded OP_RESET_KEY_PRESSED           */
/*    58.40    03-17-97  PhilJ       Modified code for OP_TEST_KEY_PRESSED  */
/*                                   and OP_RESET_KEY_PRESSED.              */
/*    58.50    03-19-97  PhilJ       Added incrementing of WeldCounter to   */
/*                                   FINALDATASTATE                         */
/*    59.00    03-25-97  LAM         fixed hardware failure alarms          */
/*    59.01    03-27-97  LAM         made copy of finalresults              */
/*    60.00    03-28-97  PhilJ       Changed UPDATASTATE to UPDATEALARMSTATE*/
/*    60.01    03-31-97  PhilJ       Added WeldMode to FinalResults in      */
/*                                   FINALDATASTATE                         */
/*    60.02    04-01-97  PhilJ       Deleted weld_samples check in          */
/*                                   UPSTROKESTATE                          */
/*    60.03    04-02-97  LAM         chged msg sent to serialport           */
/*    60.04    04-02-97  PhilJ       Corrected bug if alarm detected in     */
/*                                   HornDown mode and GoBackKey is pressed */
/*    60.05    04-04-97  LAM         fixed testmode with alarms             */
/*    61.00    04-07-97  LAM         changed which 1msdata are sent         */
/*    61.01    04-08-97  PhilJ       Update FinalResults WeldCount in Preset*/
/*    61.02    04-10-97  PaulG       Removed GetGlobaltime function.        */
/*    61.03    04-10-97  PhilJ       Removed SelectWeldMode from            */
/*                                   OP_HERE_IS_PRESET.                     */
/*    62.00    04-11-97  LAM         added weldtim2state                    */
/*    62.10    04-15-97  PhilJ       Corrected exiting HornDown with alarm  */
/*    62.20    04-17-97  PhilJ       Fixed exiting TestMode when MainKey hit*/
/*    62.30    04-18-97  PhilJ       ErrorBeep if ResetKey pressed with no  */
/*                                   alarm.                                 */
/*    63.00    04-21-97  LAM         added seconds to finaldata             */
/*    64.00    04-28-97  LAM         chged qid for hostcommands             */
/*    64.01    04-29-97  LAM         fixed powering up with estop           */
/*    64.02    04-29-97  BEKymer     Test ???_NORESET for all alarms        */
/*    65.00    05-02-97  BEKymer     Added Verifying Preset message         */
/*    65.01    05-02-97  LAM         sent end of weld code over             */
/*    66.2.123 05-06-97  BEKymer     Rearrange code in OP_RESET_KEY_PRESSED */
/*    66.2.125 05-07-97  BEKymer     CheckIfResetRequired in GOBACK_KEY_PR..*/
/*    67.00    05-07-97  LAM         added extern finalresults              */
/*    68.2.128 05-09-97  BEKymer     Removed CheckAlarmFlag in TEST_KEY_PR..*/
/*    69.00    05-09-97  PhilJ       Alarms cleared if RESET_KEY pressed.   */
/*    70.00    05-09-97  LAM         added flag to stop welder when cycling */
/*                                   fast, reset alarms in horndown mode    */
/*    71.00    05-12-97  LAM         fixed print on sample                  */
/*    71.2.132 05-12-97  BEKymer     Allow Main key to remove horndown seq  */
/*                                   and check alarms & set ready if approp.*/
/*                                   In OP_RESET_KEY_PRESSED re-check preset*/
/*    72.00    05-14-97  LAM         added printer ready set                */
/*    72.2.134 05-14-97  BEKymer     Clear ready as soon as horndown entered*/
/*    73.00    05-15-97  LAM         only send printdata when printer on    */
/*    74.00    05-27-97  LAM         only get new x-axis on preset change   */
/*    74.2.138 05-27-97  BEKymer     In MAIN_KEY release SV if horndown TRUE*/
/*    74.2.139 05-28-97  LAM         chged what is send for 1ms data        */
/*    75.00    05-29-97  LAM         chged what is send for 1ms data last state */
/*    76.2.141 05-29-97  BEKymer     SetReady when horndown is exited with  */
/*                                   Main key                               */
/*    76.2.142 05-30-97  LAM         chged what is send for 1ms data again  */
/*    76.2.143 05-30-97  BEKymer     Dont allow alarm reset if ClearAlarm   */
/*                                   returns FALSE                          */
/*    76.2.144 06-02-97  LAM         chged psosready to printer ready       */
/*    76.2.145 06-03-97  BEKymer     In TEST_KEY check TestModeAllowed flag */
/*    76.2.146 06-04-97  BEKymer     In RESET_KEY set TestModeAllowed flag  */
/*    76.2.147 06-06-97  LAM         added time and date to updatealarms    */
/*    76.2.148 06-20-97  LAM         added new alarm structure              */
/*    77.2.149 07.01.97  J.B.        Modifying alarm codes                  */
/*    77.2.150 07-02-97  LAM         deleted getcurrentmodel#,chged powerup */
/*                                   preset received                        */
/*    77.2.152 07-09-97  BEKymer     Handle new alarm codes (remove for now)*/
/*    77.2.153 07-16-97  BEKymer     Change structure member to OverloadAl..*/
/*                                   in OP_TEST_KEY_PRESSED                 */
/*    77.2.154 07-22-97  PhilJ       added opcode OP_SETUP_KEY_PRESSED      */
/*    77.2.155 07-23-97  BEKymer     Modify TEST_KEY so new alarms can be   */
/*                                   reset                                  */
/*    77.2.156 07-28-97  PhilJ       Added test on SetupFlag to OP_SETUP_KEY*/
/*                                   _PRESSED                               */
/*    77.2.157 07-28-97  PhilJ       ErrorBeep if HornDownKey pressed twice */
/*    77.2.158 07-29-97  BEKymer     Delete ClearSetupAlarm function        */
/*    77.2.159 07-30-97  BEKymer     Check setup alarm count in RESET_KEY   */
/*    78.2.160 08-08-97  LAM         deleted powerdownsequence call         */
/*    79.2.161 08-08-97  LAM         added power calib sequence call        */
/*                                   deleted send 1ms data calls            */
/*    79.2.162 08-13-97  BEKymer     Clean up code for RESET_KEY            */
/*    79.2.164 08-15-97  LAM         added weldamp to powercalibration      */
/*    79.2.165 08-17-97  LAM         added powercal success/fail flag       */
/*    79.2.166 08-21-97  LAM         added check not to update to running   */
/*                                   preset during a weld                   */
/*    2.167    08-25-97  LAM         when in powercal beep for other keys   */
/*    2.168    08-26-97  LAM         moved init1mspts & chg hornkeys        */
/*    2.169    08-27-97  PaulG       Added function CheckPrintingStatus()   */
/*    2.170    08-27-97  KevinD      changed WeldDataDisplayEnabled flag to */                                                                      
/*                                   DTEnabled flag                         */
/*    2.172    08-27-97  BEKymer     Clear FinalResults.Warnings when reset */
/*                                   key is pressed.                        */
/*    2.174    08-29-97  BEKymer     RESET_KEY now clears FinalResults.Equ..*/
/*    2.175    08-29-97  LAM         added printernotreadyflag              */
/*    2.176    09-04-97  LAM         multiply runningpresetpower by 10      */
/*    2.177    09-09-97  LAM         unit test, moved text to menutext      */
/*    2.178    09-17-97  LAM         fixed top line of run when chging preset*/
/*                                   added check when pressing test in pwrcalb*/
/*    2.179    09-19-97  LAM         deleted psosbuffer added runkeyop code*/
/*    2.180    09-23-97  LAM         chged horndown and testkey case       */
/*    2.181    09-26-97  BEKymer     Remove ClearSetupAlarms from UpdateRPr.*/
/*    2.182    09-29-97  BEKymer     In READYSTATE case check ClearAlarm()  */
/*    2.183    10-01-97  BEKymer     In OP_RESET_KEY_PRESSED check Alarm-   */
/*                                   DetectedFlag before DisplayResetMsg()  */
/*                                   Remove all PSReset() except those in   */
/*                                   OP_RESET_KEY_PRESSED                   */
/*    2.184    10-07-97  BEKymer     Modify all power settings after each   */
/*                                   call to VerifyPreset()                 */
/*    2.185    10.13.97  JBerman     Removed PSIdle, solves DCS1807, from   */
/*                                   OP_RESET_KEY_PRESSED CASE.             */
/*    2.186    10-13-97  BJB         Makes sure GoBack key gets passed to   */
/*                                   menu when it's used to exit test mode  */
/*    2.187    10-16-97  BEKymer     Remove VerifyPreset check in OP_HERE_  */
/*                                   IS_PRESET (checked only in PBSTATE)    */
/*    2.188    10-21-97  PaulG       Removed CheckPrintingStatus() and      */
/*                                   replaced it with PoweredOffCheckFunc() */
/*    2.189    10-24-97  BEKymer     Use SetupAlarmFlag instead of GetSetup.*/
/*                                   Check ClearAlarm early when OP_RESET...*/
/*    2.190    10-28-97  BJB         Doesn't need HDMenuEnabled flag.       */
/*                                   Got rid of operation OP_HORNDOWN_KEY...*/
/*                                   Added new operations OP_START_HORNDOWN,*/
/*                                    OP_STOP_HORNDOWN.                     */
/*                                   Deleted special Horn Down code from    */
/*                                    MainKey, RunKey, GoBackKey, SetupKey  */
/*                                    processing.                           */
/*    2.191    10-29-97  LAM         updated topline string on powerup      */
/*    2.192    10-30-97  BEKymer     Add POWERROUNDOFF value to every power */
/*                                   value                                  */
/*                                   Beep if test pressed and there's an O/L*/
/*    2.193    11-4-97   BJB         Got rid of unused variables            */
/*                                    WelderInReadyState and                */
/*                                    OldWelderInReady state.               */
/*                                   Fixed some comment lines to avoid      */
/*                                    compiler "informationals".            */
/*                                   Took code to stop test mode from       */
/*                                    MainKey, GoBackKey, SetupKey, moved   */
/*                                    to new operation OP_STOP_TEST.        */
/*                                   RunKey now allowed in test mode.       */
/*                                   Deleted OP_SETUP_KEY_PRESSED.          */
/*    2.194    11-10-97  LAM         added stop at end of cycle to printerqsend*/
/*    2.195    11-10-97  BEKymer     In OP_RESET_KEY_PRESSED remove all     */
/*                                   references to setup alarms.  This will */
/*                                   allow setup alarms to be reset even if */
/*                                   they still exist (Ok'ed by Kevin & Bob)*/
/*    2.196    11-11-97  LAM         moved printer memcopy here added new printflag*/
/*    2.197    11-12-97  LAM         moved symanger memcopy here added new flag*/
/*    2.198    11-13-97  BJB         Won't call DisplayResetMsg() if in Test*/
/*                                    Mode.                                 */
/*    2.199    11-14-97  LAM         chged finaldatastate for print qsend   */
/*    2.200    11-14-97  LAM         fixed zero time                        */
/*    2.201    11-18-97  BEKymer     In OP_RESET_KEY.. CheckAlarmFlag() also*/
/*    2.202    11-18-97  LAM         replaced finalresults with weldingresults*/
/*    2.203    11-18-97  LAM         deleted extra memcpy                   */
/*    2.204    11-20-97  PaulG       Removed GetPtsIncrement() from PB state*/
/*    2.205    11-21-97  LAM         replaced memcpy with function          */
/*    2.206    11-21-97  BJB         Doesn't write to display when ResetKey */
/*                                   is pressed, just passes message to menu*/
/*                                   task.                                  */
/*    2.207    12-02-97  BEKymer     Move POWERMULTIPLIER & POWERROUNDOFF   */
/*                                   and Call to SelectWeldSequence to      */
/*                                   vpreset1.                              */
/*    2.208    12-08-97  LAM         made sure test screen would not appear */
/*                                   in power calibration                   */
/*    2.209    12-10-97  PaulG       Added new flag DontPrintGraph          */
/*    2.210    12-11-97  LAM         if in power calibration beep when test */
/*                                   key not available                      */
/*    2.211    12-12-97  PaulG       Moved DontPrintGraph                   */
/*    2.212    12-18-97  BEKymer     Uncomment SendFakeKeypress(UPDATEDDI..)*/
/*                                   in PBSTATE                             */
/*    2.213    12-22-97  LAM         beep test key when not allowed in calib*/
/*    2.214    12-29-97  BJB         Deleted use of DTEnabled.              */
/*                                   Doesn't include DTOutput.h             */
/*    2.215    01-05-98  BJB         Passes final weld results to remote    */
/*                                    terminal code.                        */
/*                                   Terminated comment to satisfy compiler */
/*    2.216    01-16-98  BJB         Doesn't update whole screen in READY   */
/*                                   state, just top line                   */
/*    2.217    01-20-98  PaulG       Added printer offline check to PB state*/
/*    2.218    01-29-98  LAM         do not copy to preset counter into the */
/*                                   finalresults counter at power up       */
/*    2.219    01-30-98  BJB         Increments lifetime counter at         */
/*                                   FINALDATASTATE, moved from PSRun().   */
/*                                   At FINALDATASTATE, increments cycle    */
/*                                   regardless of state of AbortFlag.     */
/*    2.220    02-02-98  LAM         copy current preset counter at power up*/
/*    2.221    02-04-98  BEKymer     Move 'AtTime' values from WELD_DATA to  */
/*                                   WELD_OBJECT structure                   */
/*    2.222    02.10.98  JBerman     In OP_TEST_KEY_PRESSED, I added        */
//                                   CoolValOn(). In Addition I removed   
//                                   CoolValOn from PSTest().
/*    2.223    03-03-98  BEKymer     Clear PresetHasBeenOked in UpdateRPrese*/
/*    2.224    03-09-98  BEKymer     In OP_RESET_KEY_PRESSED don't allow    */
/*                                   test mode if TestSonicsFlag still TRUE */
/*    2.225    03-16-98  BEKymer     ClearSetupAlarms() when reset key hit  */
/*    2.226    03-16-98  BEKymer     Reset printer 5 second offline timer   */
/*    2.227    03-19-98  BEKymer     Copy AmpControl into FinalResults in   */
/*                                   CopyWeldResultsToFR()                  */
/*    2.228    03-20-98  BEKymer     AmpContol->AmpControlFlags in CopyWeld */
/*                                   ResultsToFR                            */
/*    2.229    04-07-98  PaulG       Removed DontPrintGraph from file       */
/*    2.230    04-17-98  LAM         if printing do not display retracting  */
/*                                   send either select 1 or 3 depending on */
/*                                   calibration passed or failed           */
/*    2.231    05-04-98  LAM         donot clear calibratealarms, added call*/
/*                                   to calibration when in ready           */
/*    2.233    05-14-98  LAM         do not allow calibration during welding*/
/*    2.234    05-14-98  LAM         added trig force temporarily           */
/*    2.235    05-19-98  BEKymer     Move CheckProcessLimits from WAITFOR   */
/*                                   ULSMADESTATE to new state PROCESSALARM */
/*                                   STATE to fix DCS # 2426.               */
/*    2.236    06-01-98  LAM         allow calibration when alarm is set    */
/*    2.237    06-01-98  BJB         Won't overwrite top line of run screen */
/*                                   if parameter changed during weld.      */
/*    2.238    06-03-98  BEKymer     Changed AmpControlFlags to             */
/*                                   PowerSupplyControlFlags                */
/*    2.239    06-16-98  BJB         Removed potentially destructive calls  */
/*                                   to DisplayCurrentPreset(); menu will   */
/*                                   do this automatically.                 */
/*    2.240    06-18-98  LAM         allow calibration when recalibrate actuator */
/*                                   or dooropen alarm                      */
/*    2.241    06-22-98  BEKymer     Change structure member ActualForceMax */
/*                                   to WeldForceMax                        */
/*    2.242    06-24-98  LAM         changed copyweldtofinals with a memcpy */
/*    2.243    06-30-98  LAM         added error message for calibration    */
/*    2.244    07-01-98  JBerman     added act. nvram check after EStop     */
/*    2.245    07-01-98  LAM         added abort calibration popup          */
/*    2.246    07-10-98  BJB         No parameter to GetActuatorInfo()      */
/*    2.247    07-17-98  BJB         Commented out code that sends SPC data */
/*                                    to host, data were being interpreted  */
/*                                    as host commands by COMMAND.C.        */
/*    2.248    07-20-98  BEKymer     After a reset key is processed send a  */
/*                                   message to sys mangr to recount alarms */
/*                                   Also clear FinalResults when reset key */
/*    2.249    07-22-98  LAM         donot put in calibrate act sequence    */
/*                                   just clear ready so goback will work   */
/*    2.250    07-23-98  BEKymer     Put in Joe's change for EMERGENCYSTOP..*/
/*    2.251    07-29-98  BEKymer     Create 2 new functions - ClearWelding- */
/*                                   ResultsAlarms and ClearFinalResults-   */
/*                                   Alarms.  Call them from RESET_KEY and  */
/*                                   PBSTATE.                               */
/*    2.252    07-30-98  BJB         Deleted act_nvr definition, uses       */
/*                                   actnvram.h.                            */
/*                                   Moved code to set up StrTopLine to     */
/*                                   new function FormatRunScreenTopLine(). */
/*                                   Moved to root() code that copies       */
/*                                   preset at startup.                     */
/*                                   Rewrote code to read actuator type     */
/*                                   after ESTOP.                           */
/*                                   Moved to root() code to init WmgrQid.  */
/*    2.253    08-03-98  BJB         If Act Novram exists but is corrupted, */
/*                                   sets up as AED actuator, not AE. Also  */
/*                                   records "Recalibrate" alarm.           */
/*    2.254    08-03-98  LAM         changed trigger state when in calibration*/
/*    2.255    08-07-98  BEKymer     Changed top line of display for peak   */
/*                                   power mode to display power in tenths  */
/*    2.256    08-18-98  BJB         Replaced UpdateVFLine() calls with     */
/*                                   UpdateLine().  THESE NEED TO BE        */
/*                                   REMOVED TO MENU TASK EVENTUALLY.       */
/*                                   Uses SendFakeKeyPress() to send keys   */
/*                                   to menu task instead of direct queue   */
/*                                   write.                                 */
/*    2.257    08-19-98  BJB         Changed call RemoteTermInUse() to new  */
/*                                   name, TermIsEnabled().                 */
/*    2.258    08-21-98  LAM         moved calls from calibration to menu   */
/*                                   task                                   */
/*    2.259    09-03-98  BJB         Uses new AlarmOff() to turn off reset  */
/*                                   LED.                                   */
/*    2.260    10-01-98  LAM         deleted 1 second delay before processing*/
/*                                   estop message                          */
/*    2.261    10-12-98  BJB         Uses FormatVariable() to format        */
/*                                    distance values for top line of run   */
/*                                    screen, now output matches setup.     */
/*    2.262    10-13-98  BEKymer     Moved CycleCount++ and copy of Welding */
/*                                   results to Final from FINALDATASTATE   */
/*                                   to SendFData in Ready.c                */
/*    2.263    10-14-98  LAM         fixed opcode for weld data out         */
/*    2.264    10-16-98  LAM         send weld data out if serial on and    */
/*                                   terminal is off                        */
/*    2.265    05-28-99  JZ          fixed ActRecover() no parameter passed */
/*                                   deleted HornDown                       */
/*    2.266    10-14-98  LAM         deleted HornDown Case                  */
/*    2.267    10-26-99  JZ          modified WeldManager()                 */
/*    2.268    12-16-99  LAM         removed unused errorhandling code      */
/*    2.269    03-08-00  JZ          added AEF and AED check in e preset    */
/*    2.270    04-20-00  JLH         Added test for AED Upgrade error to    */
/*                                    emergency stop case.                  */
/*    2.271    05-26-00   SCM      Checked in for testing by Laura, John.   */
/*    2.272    06-09-00   JLH      Send weld data to command.c for serial   */
/*                                  port output only if CurrentSetup.       */
/*                                  SendWeldData is true.                   */   
/*    2.273    06-09-00   LAM      removed unused references to drycycle strings */ 
/*    2.274    07-07-00   BEKymer/DJL  fixed SETUP                          */
/*    2.275    07-14-00   BEKymer   In EMERGENCYSTOP case add:              */
/*                                     SVOff()                              */
/*                                     PSIdle()                             */
/*                                     CoolValOff()                         */
/*    2.276    08-01-00   LAM       fix run screen top line                 */ 
/*    2.277    08-15-00   JLH       Various changes to fix reset button issues */
/*    2.278    08-16-00   LAM       Reset button needs to set DUPSOKFlag to TRUE */
/*                                  and the WeldStatus to TIMEOUT           */
/*    2.279    08-24-00   JLH       Changed FormatRunScreenTopLine to say undefined mode for collapse and absolute
                                     mode if acctuator is AE. (change did not seem to work)              */
/*    2.280    09-06-00   BEKymer   When reset key is pressed transfer      */
/*                                   TotalAlarmCount into AlarmCounter      */
/*    2.281    09-20-00   LAM       Rewrote the reset key function          */
/*    2.282    09-26-00   JLH     Changed CheckForActChange() to ActuatorChanged = CheckForActChange().  This was done with
                                    the intent of satisfying tracker issue #3573.  It was used for the printer, instead. */
/*                                                                          */
/*    2.283    10-04-00   AT      added DUPS_DownloadQueuedPS() to PREREADYSTATE */
/*                                changed PKPOWERMODE length from 13 to 15  */
/*    2.284    10-05-00   AT      added queued upload/download to PREREADYSTATE */
/*    2.285    10-05-00   BEKymer Removed underscores from DUPSCHANGEPending*/
/*    2.286    10-09-00   AT      Changed line 895 to use DUPSUploadPSPending */
/*    2.287    10-19-00   LAM     send a gobackkey when estop is release and */
/*                                dupsokflag is false                       */
/*    2.288    11-01-00   BEKymer Removed code in OP_RESET_KEY_PRESSED case.*/
/*                                 As coded it wouldn't work if any other   */
/*                                 EQ alarms.  Also the upper 4 bits which  */
/*                                 define an alarm group are not set in     */
/*                                 the FinalResults.Equi... structure.      */
/*                                 Also removed unused ClearedHardwareAlarm */
/*                                 extern and did some lining up.           */
/*    2.289    11-02-00   LAM     Added test not to generate the recal alarm*/
/*                                for control levels less then d (Issues 3662 & 3658)*/
/*    2.290    11-06-00   BEKymer Require reset after estop removed.  Reset led  */
/*                                 blinks after estop removed.  Now, while estop */
/*                                 active, navigation can occur and values can be*/
/*                                 changed.  In future, consider masking all keys*/
/*                                 but reset after estop removed, until reset    */
/*                                 is pressed. Issue # 3659                      */
/*    2.291    11-09-00   AT      Switched back to version 2.289                 */
/*    2.292    04-19-01   LAM     added recallextpreset function call       */
/*    2.293    05-04-01   LAM     need to call sendsetupdata when Preset Not Available*/
/*    2.294    05-08-01   LAM     need to set PresetHasBeenOKed in OP_PBSTATE */
/*                                to TRUE which allows the state machine to advance*/
/*    2.295    08-20-01   BEKymer Added code to output ASCII in FinalDataSTATE */
/*    2.296    08-21-01   BEKymer Detab                                     */
/*    2.296.1.0  04-04-02   LAM     changed errorcode1000 condition         */
/*    2.296.1.2  05-06-02   LAM     check the loadcell table not the default*/
/*    2.296.1.3  05-17-02   LAM   remove aef from errorcode 1100 test       */
/*    2.296.1.3.1.0  03-20-03  SCM  Added code to send weld data message to QVGA handler*/
/*    2.296.1.3.1.3  06-10-03  bWadia  Weld state Messages are send to the QVGA queue   */
/*    2.296.1.3.1.4  06-16-03  bwadia  TestKey Message is send to the QVGA queue */
/*    2.296.1.3.1.5  07-19-03  JOY     'QVGACALIB_KEY' is send to the QVGA queue to bring */
/*                                     next Calibration stage menu.             */
/*    2.296.1.3.1.6  08-14-03  JOY     'Reset' Key is send to the QVGA queue.   */
/*                                     Added QVGA H/W before sending message to the QVGA queue */
/*    2.296.1.3.1.7  08-26-03  JOY     ESTOP pressed/Released Messages are send to the QVGA queue */
/*    2.296.1.3.1.8  10-01-03  JOY     Alarms are removed with PB Press */
/*    2.296.1.3.1.9  10-06-03  JOY     'OP_RECALL_EXT_PRESET' is send to the QVGA queue */
/*    2.296.1.3.1.11 11-26-03  JOY     'ESTOPMSGOFF' is replaced by 'ESTOPMSGRESET' just name is changed*/
/*    2.296.1.3.1.12 12-03-03  JOY     Reset LED is turned off while reseting the resetable equipment Alarms*/
/*                                     alarm display is refreshed in VFD/touch Screen  */
/*    2.296.1.3.1.13 12-05-03  JOY     Test is not activated in HD Alarm menu */
/*    2.298    12-05-03   BEKymer  Move 2.296.1.3.1.13 to tip as 2.298 for    */
/*                                  Ver9.00b build                            */
/*    2.299    12-27-03   VSharma     Update the ResetFailed and KeyProcessed    */
/*                                     variables to used in RSCH task.           */
/*    2.300    01-19-04   VSharma  Added Min/Max Check in PB State            */
/*    2.301    02-02-04   VSharma  Removed Min/Max Check from PB state and added Verify
                                   related changes.                           */
/*    2.302    02-20-04   VSharma  Update PresetNum & PresetName in FINALDATASTATE.*/
/*    2.303    04-06-04   VSharma  Display the Main Menu after EStop reset if */
/*                                 UserIOMenu is displayed.                   */
/*                                 Execute the VerifyPreset() if any input or */
/*                                  output is reconfigured.                   */
/*    2.304    04-19-04   VSharma  Display 'Interlock Delay' message in case  */
/*                                  of SVInterlock state.                     */ 
/*    2.305    04-23-04   VSharma  Don't display 'Iterlock Delay' if SVInterlock */
/*                                  input and output are not configured.      */
/*    2.306    05-11-04   VSharma  Modified case WAITFORSVINPUTSTATE.         */
/*    2.307    05-17-04   VSharma  Added CheckVerifyPresetRequired().         */
/*    2.308    05-18-04   LAM      check for horn weight change when returning*/
/*    2.309    06-04-04   VSharma  Append asterisk (*) in WeldData PresetName */
/*                                 if last weld is done with the changed data.*/
/*    2.308.1.0 6-10-04   BEKymer  Add Welder ID to ASCII output strings      */
/*    2.310    06-25-04   BEKymer  Merged 2.308.1.0 & 2.309 to create 2.310   */
/*                                  for Ver9.00l build                        */
/*    2.311    11-28-05   BEKymer  Added fix for when recalling verified      */
/*                                  presets.  Added in version 9.04.          */
/*    2.311.1.012-05-05   BEKymer  Restart state machine after SelectWeld     */
/*                                  Sequence in CheckVerifyPresetRequired().  */
/*    2.313    07-25-05   Bwadia   Asian Language support for FormatRunScreen-*/
/*                                 Topline function. Sent messages to RVTS Queue*/
/*    2.314    07-28-05   Bwadia   Weld start host command message sent to RVTS */                                     
/*    2.315    08-19-05   Bwadia   IsHWConfigured function used to check for    */
/*                                 VGA hardware presence                        */
/*    2.310.1.5 09-10-2005 Bwadia  Printing data is not sent to Print Task if  */ 
/*                                 VGA present                                 */
/*    2.310.1.6 10-28-05   Bwadia   Sequencing feature added on PB press       */ 
/*    2.310.1.7 11-02-05  Aare     Store current value of total cycle time into*/
/*                                  weld results in FINALDATASTATE state.      */
/*    2.310.1.8 11-02-05  Aare     Store total cycle time into right place.    */
/*    2.310.1.9 11-22-05  Bwadia   Weld start data command sent only if VGA    */
/*                                 not present.                                */
/*    2.310.1.10 12-07-05 Bwadia   PMC comparison done only when final data is */
/*                                 sent. Tracker issue 4028                    */
/*    2.313    01-06-06   LAM      Merged BBRaun and Ver10                     */
/*    2.314    02-07-06   Bwadia   VGA USB offline and printer offline alarm   */
/*                                 added in PBSTATE. Modified for tracker 4055 */                                     
/*    2.315    02-02-06   BEKymer  Add fake RunKey to PBSTATE when recalling  */
/*                                  external presets  (Ver 9.04 fix)          */
/*    2.316    02-14-06   Bwadia   PMC alarm not detected if limits are OFF   */
/*    2.317    05-31-06   YGupta   CurrentSetup.VGAHWPresent and IsHWConfigured */
/*                                 function used to StartStateMachine after EStopReset.*/ 
/*    2.318    12-22-06   NHAhmed  Added fix for Ver9.04.                     */
/*    2.319    01-23-07   NHAhmed  Made changes in FormatRunScreenTopLine()   */
/*                                 function too display correctly the textbox */
/*                                 item on the run screen in Asian Languages. */
/*    2.320    04-24-07   NHAhmed  Removed all UpdateTopLineFlag and          */
/*                                 DisplayStateMessage() from State Change    */
/*    2.321    05-04-07   NHAhmed  Update printer Status on reset press (Tracker #4109)      */
/*    2.322    05-23-07   NHAhmed  Changes related to Setup Alarm SE297.      */
/*    2.323    07-17-07   NHAhmed  Changes related to support ASIAN languages on ASCII format*/
/*    2.324    10-22-07   NHAhmed  Changes done for LangTest phase 0          */
/*    2.325    11-30-07   BEKymer  Call SetIndex in CheckVerifyPresetRequired */
/*                                  a bug fix in version 9.07                 */
/*    2.326    04-14-08   NHAhmed  Added a copy statement in function FormatRunScreenTopLine()*/
/*    2.327    09-02-08   NHAhmed  CleanUp for multi-language support.        */
/*    2.328    09-04-08   YGupta   CleanUp for LangTest Project.              */
/*    2.329    09-09-08   NHAhmed  CleanUp for multi-language support.        */
/*    2.330    09-10-09   BEkymer  Add new define MICRO where needed          */
/*    2.331    10-23-09   BEKymer  Allow weld results on RS-232 even for      */
/*                                  VGA systems                               */
/*    2.332    11-02-09   YGupta   Comment out ReadWeldDataResponseMsg for RvtsQid for RS232.                                                                          */
/*    2.333    11-11-09   Pdwivedi Modify Reset key for Horn Down Screen      */
/*    2.334    10-14-10   Pdwivedi Added changes for MH Testing Issues        */
/*    2.335    02-28-11   PDwivedi Added changes for USB Memory Full Alarm.   */
/*    2.336    03-03-11   PDwivedi Added changes for USB Memory Full Alarm(Recalibrate Alarm problem).   */
/*	  2.336.1.0.1.2 02-19-14  Hsanchez the function SendFakeKeyPress(RunKey)      */
/*                                 was removed tu avoid the extra beed when   */
/*                                 using external beeps                       */ 
/*    2.336.1.0.1.2.1.2	 1/3/2018 RChapa Removed Case DUPSState and Validation for Ramp Time at Case PBState */
	
/* ----------------------------- DESCRIPTION -------------------------------*/


/*------------------------------ PSEUDO CODE -------------------------------*/


/*----------------------------- LOCAL_EQUATES ------------------------------*/
 
#define TESTKEYREPEATTIME  400 /* Slightly more then actual repeat time  */
#define TAB                0x09
#define COMMA              ','
#define SPACE              ' '
#define CRLF               "\r\n"

                                      
/*------------------------------ INCLUDE FILES -----------------------------*/

#include <psos.h>                /* psos defines and prototypes, etc,.  */
#include "string.h"
#include "actnvram.h"
#include "names.h"               /* psos object defines                 */
#include "opcodes.h"             /* incoming message opcodes            */
#include "preset.h"
#include "prsetmsg.h"
#include "psnvram.h"
#include "menu1.h"
#include "ipsatype.h"
#include "menu.h"
#include "weldmngr.h"            /* Weld event definitions              */
#include "wldstate.h"
#include "genrlmsg.h"            /* generic message type                */
#include "graphs.h"              /* generic message type                */
#include "weld_msg.h"
#include "keypad.h"
#include "beep.h"
#include "fpkp_msg.h"
#include "fmtstrs.h"
#include "state.h"
#include "statedrv.h"
#include "selctkey.h"
#include "snsrcalb.h"
#include "alarms.h"
#include "ready.h"
#include "digout.h"
#include "led.h"
#include "getmsg.h"
#include "display.h"
#include "rtclock.h"
#include "alsetup.h"
#include "mansensr.h"
#include "util.h"
#include "dups_api.h"
#include "vpreset1.h"
#include "menu7a.h"
#include "actnvram.h"
#include "menu3.h"
#include "serial.h"
#include "inports.h"
#include "outports.h"
#include "spidd.h"
/*QVGA Message*/
#include "qvgamenu.h"
#include "genalarm.h"
#include "command.h"

/* expected incoming messages */
#include "obj_tabl.h"

/* defines for READ_SWARE_LOG_ENTRIES  */
#include "ipscdmsg.h"

#include "ck_qsend.h" 

/* printer related function */
#include "menu4.h"


/*------------------------- LOCAL_TYPE_DECLARATIONS ------------------------*/
#define DIST_STR_SIZE     7


/* this union is comprised of the expected messages that will be sent */
/*  to this task */

typedef union
{
   GENERIC_MSG                     GenericMsg;
   PRESET_TABLE_MSG                PresetTablePtrMsg;
   HOST_COMMAND_MSG                host_cmd;
   WELD_STATE_MSG                  WeldMsg;
} WMGR_MSG_QUEUE_TYPE;




/*------------------------- LOCAL FUNCTIONS --------------------------------*/
void UpdateRPreset(void);
BOOLEAN CheckVerifyPresetRequired (void);

#define ASCIILENGTH 132
/*------------------------- EXTERNAL FUNCTIONS -----------------------------*/
void ResetHDAlarms(void);
BOOLEAN IsCalibGoingOn(void);
UINT32 GetCurrentHwCnfg (void);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void CheckPMCWithPwrGraph(void);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
SINT8 * Trim_FillChar(SINT8 Str_temp[]);
/*--------------------------- PRIVATE GLOBAL DATA --------------------------*/

STR StrWeldStateLine[QVGA_LINESIZE];
static UINT32 LastCycleTimer;
UINT8  RS232DataLine[ASCIILENGTH];
UINT16 Index;
UINT8 CheckPrinterStatus = FALSE;

/*--------------------------- GLOBAL DATA ----------------------------------*/
extern UINT8  RunScreenFlag;
extern UINT8  AETrigger;
extern UINT16 SetupAlarmFlag;
extern UINT16 PrintEveryCycleFlag;
extern UINT16 PrinterCheckTimer;   /* Keep track of how often to check printer */
extern UINT16 AlarmCounter;
extern INBITS Inp;
extern DUPS_WELDSTATUS WeldOLStatus;
extern DUPS_WELDSTATUS SeekOLStatus;
extern DUPS_WELDSTATUS ABOLStatus;
extern SETUPS_Ver800 CurrentPreset,RunningPreset;
extern CONFIGSETUP CurrentSetup;
extern UINT32 SysmQueueId;
extern SINT16 MenuCounter;
extern enum WELDSTATES WeldState;
extern UINT16 TestTimerCounter;
extern UINT8 AlarmDetectedFlag;
extern WELD_DATA WeldingResults;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern UINT16   ResetReceivedFlag;
extern UINT16   TestModeAllowed;
extern BOOLEAN  TestSonicsFlag, HornDownFlag, SonicsOnFlag;
extern BOOLEAN PwrTestFlag;
extern UINT16   CalibrationPassed;
extern UINT32 PrintQid;
extern UINT32 RschQid;   
extern UINT32 SystemTimer;
extern PSNOVRAMDATA PSNvRamData;
extern BOOLEAN PowerOkFlag;
extern UINT16  ReadyAlreadySet;
extern BOOLEAN TestDelayFlag;
extern UINT16  InitPrinterOnceOnPowerup;
extern UINT16  TotalAlarmCount;

extern WELD_OBJECT *MsDataPtr;
extern UINT16 PresetHasBeenOKed;
extern BOOLEAN   IsThereAGraphPrinting;
extern BOOLEAN ActuatorChanged;
extern UINT32 QvgaQid;   // Queue ID for QVGA queue.
extern UINT32 RvtsQid;
extern BOOLEAN QVGAHwAvail;
extern BOOLEAN QVGARunScreenFlag;
extern BOOLEAN QVGAHDAlarm;
extern UINT16 AbortPrintingFlag;
extern BOOLEAN ResetFailed;
extern BOOLEAN ResetAlarmProcessed;
extern BOOLEAN ResetRecall_UpdateFlag;
extern BOOLEAN VerifyPresetRequired;
extern BOOLEAN WeldingStopInsideMenu;
extern BOOLEAN UserIOAlarmMenu;
extern BOOLEAN SVInterlockActive;
extern BOOLEAN VGAWeldStartData;
extern BOOLEAN PMCPlusBandFlag;
extern BOOLEAN PMCMinusBandFlag;
extern BOOLEAN VGAUSBOfflineFlag;
extern BOOLEAN VGAPrinterOfflineFlag;
extern BOOLEAN VGAUSBFullFlag;
extern SETUP_DATA_ALARMS SetupData;
extern UINT32 TotalCycleTime;
extern BOOLEAN WindowSetupFlag;

extern BOOLEAN VGA_ScreenMicronCalFlag;

UINT8 weld_data_flag = 0;
BOOLEAN UpdateFlag = TRUE;
WELD_DATA FinalResults;
UINT16 PresetNeedsToBeUpdated = FALSE;
UINT16 TestKeyRepeat;
UINT16 PowerUpPresetReceived = FALSE;
WMGR_MSG_QUEUE_TYPE WmgrMsg;
UINT32 WmgrQid;
UINT32 PsosStatus;
UINT16 PrinterRestartFlag = FALSE;

static UINT16 BeepFlag;


/*---------------------------------- CODE ----------------------------------*/

void WeldManager(void)
{
   /*---------------------------------------------------------------*/   
   /*            Define and Initialize Local Variables              */
   FRONT_PANEL_USER_REQUEST_MSG FpscMsg;
   FP_KEY_PRESSED_MSG           FPKeyMsg;
   WELD_DATA_MSG                WeldDataMsg;
   HOST_COMMAND_MSG             ReadWeldDataResponseMsg;
   UINT16                       UpdateTopLineFlag = FALSE;
   RTC RTCWeld;
   BOOLEAN ExternalPresetAlarm = FALSE; /* Assume the external preset is available */
   UINT16 NextPreset;
   UINT8 SavedLangIndex = 0;
   FpscMsg.common.opcode       = OP_FRONT_PANEL_KEYPRESS;
   FpscMsg.common.pointer_flag = NO_DATA_PTR;
   FpscMsg.common.source_task  = FPKP_SOURCE_TASK;

    /* Form the message, OP_READ_WELD_DATA_RESPONSE with the */
    /* sware_log_return_data_ptr and send to RSCH queue      */   

   ReadWeldDataResponseMsg.byte_count          = sizeof(WELD_DATA);
   ReadWeldDataResponseMsg.common.opcode       = START_WELD_DATA;
   ReadWeldDataResponseMsg.common.pointer_flag = DATA_PTR_NO_DEALLOC;
   ReadWeldDataResponseMsg.common.source_task  = WELD_MGR;
   ReadWeldDataResponseMsg.data_pointer        = &FinalResults;
           
 
   while (TRUE)
   {
      /* Wait for an event of epic proportions to continue */

      /* Check msg queue */ 
      PsosStatus = q_receive(WmgrQid, Q_WAIT, Q_WAIT_FOREVER, &WmgrMsg);
      ExternalPresetAlarm = FALSE; /* Assume the external preset is available */

      UpdateTopLineFlag = FALSE;
      switch (WmgrMsg.GenericMsg.common.opcode) {

         case OP_TEST_KEY_PRESSED:
            if ((SystemTimer - LastCycleTimer) <= TESTKEYREPEATTIME) {
               TestKeyRepeat = TRUE;
               if ((WeldingResults.OverloadAlarms & OL1) == 
                   (OL1 & ALARMCODEMASK) ) {
                  Beep(ERRORBEEP);
                  TouchScrnBeep(10);
                  PSReset();
                  TestModeAllowed = FALSE;    /* An overload, stop further  */
               }                              /* testing as low as repeating*/
            }
            else {
               TestKeyRepeat = FALSE;
               if (AETrigger == FALSE) { 
                  if ((WeldingResults.OverloadAlarms & OL1) == 
                      (OL1 & ALARMCODEMASK) ) {
                     TestModeAllowed = FALSE; /* Test mode ok now, door is shut */
                  }
                  else {
                     TestModeAllowed = TRUE; /* Test mode ok now, door is shut */
                  }
               }
            }
            LastCycleTimer = SystemTimer;
            if ( ((GetReadyStatus() == TRUE) || (TestSonicsFlag == TRUE)) &&
                 (TestModeAllowed == TRUE) ) {
               if (HornDownFlag == TRUE || QVGAHDAlarm) {
                  Beep(ERRORBEEP);
                  TouchScrnBeep(10);
               }
               else if (( !Get_GetMsgFlag() && !QVGAHwAvail) ||
                         AbortPrintingFlag) {
                  Beep(ERRORBEEP);
                  TouchScrnBeep(10);
               }
               else if (TestSonicsFlag == FALSE) {
                  SelectTestSequence();
                  TestSonicsFlag = TRUE;
                  StartTestFlag = TRUE;                    
                  
                  /*If enable block the TEST screen for Micron Calibration*/
                  if(VGA_ScreenMicronCalFlag == FALSE)
                  {
                	  /*If VGA H/W available send TestKey to qvga queue*/
                	  if(IsHWConfigured(VGA))
                	  {
                		  FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                		  FPKeyMsg.key = TestKey;
                		  CkQSend (RvtsQid, &FPKeyMsg, WELD_MGR,__LINE__, MILLS_TO_TICKS(20));
                  	  }
                  }
                  else
                  {
                	  Beep(CONFIRMBEEP);
                  }
                  SendFakeKeyPress(TestKey);

                  ////else
                  //   SendFakeKeyPress(TestKey);    /* Tell menu system ok      */
               }
               else {
                  switch (SonicsOnFlag) {

                     case TRUE:                 /* Sonics still on          */
                        TestTimerCounter = 0;               /* Reset timer                      */
                        break;

                     case FALSE:               /* Sonics gone off already  */
                        StartTestFlag = TRUE;
                        break;
                     default:
                        break;
                  }
               }
            }
            else {
               if (TestKeyRepeat == FALSE) /* Only beep if we cant get into */
                  {
                     Beep(ERRORBEEP);     /* test because of something besides */
                     TouchScrnBeep(10);
                  }
            }                          /* overload.  This prevents multiple */
            break;                     /* beeps when the test key is held   */
                                       /* and there is an overload.         */

         case OP_RESET_KEY_PRESSED:
            if ((WeldState == READYSTATE) || (WeldState == PREREADYSTATE)) {
               if ( (CheckAlarmFlag() == TRUE) || (AlarmDetectedFlag == TRUE) ) {
                  BeepFlag = FALSE;      /* Start off assuming we will reset */
               }
               else BeepFlag = TRUE;
   
   /*---   First clear out alarms which can be reset   ---*/
   
               if(SetupData.SetupErrorAlarms9 & BIT270)
                  CheckPrinterStatus = TRUE;
               ClearSetupAlarms();
               PrinterCheckTimer = 0;/* Reset printer 5 second offline timer */
 
               ClearWeldingResultsAlarms();
               ClearFinalResultsAlarms();

               ResetReceivedFlag = TRUE;
               TrigSwActv();                      /* safety circuit input            */
               TestModeAllowed = TRUE;
   
   /*---  Now see if any non-resetable alarms remain  ---*/
   
               if (ClearAlarm(FinalResults.EquipmentFailureAlarms) != TRUE) {
                  BeepFlag = TRUE;
               }   
   
               if ((FinalResults.EquipmentFailureAlarms == 0) &&
                   (FinalResults.CalibrateAlarms == 0) &&
                   (AlarmDetectedFlag == TRUE) ) {
                  PSIdle();
                  PSReset();
                  AlarmDetectedFlag = FALSE;

/*--------------------------------------------------------------------------*/
/*  The Reset key was pressed while still in test mode.  Let's make it look */
/*  like the test mode has ended (at least look like the test key is no     */
/*  longer pressed and sonics have timed out).  To turn on sonics again the */
/*  test key must be pressed again.  This is to fix DCS # 2446.             */
/*--------------------------------------------------------------------------*/
                  if (TestSonicsFlag == TRUE) {
                     TestModeAllowed = FALSE;
                  }
/*--------------------------------------------------------------------------*/
   
                  ClearAlarmFlag();                 /* Clear Alarm flag */
                  ClearGeneralAlarm();              /* Remove GeneralAlarm,suspect,&reject signals*/
                  if((RunScreenFlag == TRUE) && (MenuCounter == 1))
                     SendFakeKeyPress(UPDATEDISPLAY);
                        
                  /* If QVGA H/W is available send Message to the QVGA queue*/
                  if(QVGAHwAvail)
                  {
                     FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                     FPKeyMsg.key = UPDATELINE2;                        
                     CkQSend (QvgaQid, &FPKeyMsg, WELD_MGR,
                      __LINE__, MILLS_TO_TICKS(20));   /* 20 ms        */
                  }
                  AlarmOff();                       /* Turn off Reset led               */
               }
   
/*--------------------------------------------------------------------------*/
            }
            else
               BeepFlag = TRUE;
            if ((GetCurrentSequenceType() == HORNDOWN) && (HornDownFlag == TRUE))
            {
               ResetHDAlarms();
               BeepFlag = FALSE;
            }
            if (BeepFlag == FALSE)        /* By now, either beep or display   */
            {                             /* the Reset Complete message, we   */
                                          /* must do exactly one of them.     */
               if (RunScreenFlag)
                  SendFakeKeyPress(ResetKey);  /* If on RunScreen or submenu, */
                                               /* react on-screen to reset.   */
               /*If QVGA H/W available send ResetKey to qvga queue*/
               if(QVGAHwAvail)
               {
                  FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                  FPKeyMsg.key = ResetKey;                        
                  CkQSend (QvgaQid, &FPKeyMsg, WELD_MGR,
                           __LINE__, MILLS_TO_TICKS(20));      /* 20 ms       */
               }
               ReadyAlreadySet = FALSE;
               CycleAbort = FALSE;
               AlarmDetectedFlag = FALSE;
               ClearAlarmFlag();        /* Clear Alarm flag                 */
               ClearGeneralAlarm();     /* Remove GeneralAlarm,suspect,&reject signals*/
               AlarmOff();              /* Turn off Reset led               */
            }
            else {
               Beep(ERRORBEEP);

/*----  Here we need to send Updated Alarm Data over to the System Manager  ----*/

               CountAlarms();
               AlarmCounter = TotalAlarmCount;   /* Carry this count into RecordAlarm       */
                                                 /* This allow reset to clear the counter   */
                                                 /* even if a cycle is not run.  DCS # 3544 */
               if (TotalAlarmCount != 0) {  /* Update to latest count if not 0 */
                  WeldDataMsg.common.opcode = OP_READ_ALARM_DATA;
                  CkQSend (SysmQueueId,&WeldDataMsg,WELD_MGR,
                           __LINE__,MILLS_TO_TICKS(10));
                  ResetFailed = TRUE;/*Used in Host command.*/      
               }
            }
			VGAPrinterOfflineFlag = FALSE;
			VGAUSBOfflineFlag = FALSE;
         VGAUSBFullFlag = FALSE;
            ResetAlarmProcessed = TRUE;/*Used in Host command.*/
            break;

   
         case OP_MAIN_KEY_PRESSED:
            SendFakeKeyPress(MainKey);
            break;

         case OP_RUN_KEY_PRESSED:
            SendFakeKeyPress(RunKey);
            break;

         case OP_STOP_TEST:
            PSIdle();                    /* Turn off sonics              */
            TestTimerFlag = TRUE;        /* Advance state machine        */
            SelectWeldSequence();        /* Restore weld sequence        */
            StartStateMachine();         /* Start the state machine here */
            TestSonicsFlag = FALSE;      /* Clear flag to show test done */
            if (CheckIfResetRequired() == FALSE)
               SetReady();               /* Output Welder Ready signal   */
            break;

         case OP_POWERDOWN:         /* Received power switch is set to off  */
            break;

         case OP_CALIB_START:       /* Received when Calib/Diag selected from main menu */
            break;

         case OP_GOBACK_KEY_PRESSED:
            SendFakeKeyPress(GoBackKey);
            break;

         case OP_START_WELD_DATA:
            weld_data_flag =1;
            break;

         case OP_STOP_WELD_DATA:
            weld_data_flag = 0;
            break;

         case OP_HERE_IS_PRESET:
            /* return the buffer allocated by the SysManager task */
            PresetNeedsToBeUpdated = TRUE;
            FormatRunScreenTopLine();
/* If not ready do not update the running preset check the UpdateDispFlag
   on the next palm button pressed */
            break;

         case OP_WELDER_STATE_CHANGE:
            switch (WmgrMsg.WeldMsg.state) {


               case PREREADYSTATE:
                  if (DUPSChangePending == TRUE) 
                     {
                     if (DUPSChange == UPLOAD_PENDING) /* both upload and download pending */
                        {
							DUPS_CurrPSStatus = DUPS_PENDING;
							DUPS_UploadParamSet(DUPSUploadPSPending);
							DUPS_Wait4CurrPS();
                        }
                     DUPS_DownloadCurrPS(); /* download is pending always when we get here */
                     DUPSChangePending = FALSE;
                     }
                  break;

               case READYSTATE:

                  break;
                                 
               case PBSTATE:
                  if((CurrentSetup.ExtPresets == TRUE) && (Inp.PresetCode != 0))
                  {
                     /* External Preset Changed*/
						 if(RecallExtPreset((UINT16)Inp.PresetCode) == TRUE){ /* Preset Not Available Alarm */  
							PresetNeedsToBeUpdated = TRUE; /* need to verify the new preset */
							//SendFakeKeyPress(RunKey);  it send an extra beep. HSanchez
						 }
						 else
							ExternalPresetAlarm = TRUE;
                  }
                  else if(CurrentSetup.SequenceEnable == TRUE &&  //Sequencing enabled
                           CurrentSetup.SequenceCount != 0)
                  {
                     NextPreset = (UINT16)CurrentSetup.SequenceList[CurrentSetup.SequenceNos];
                     if (NextPreset != CurrentSetup.ActivePreset )
                     {
                        if(RecallExtPreset(NextPreset) == TRUE) /* Preset Not Available Alarm */  
                           PresetNeedsToBeUpdated = TRUE; /* need to verify the new preset */
                        else
                           ExternalPresetAlarm = TRUE;
                     }   
                  }         
                  else if(CurrentSetup.SequenceEnable == TRUE &&  //Sequencing enabled
                          CurrentSetup.SequenceCount == 0)
                  {
                     RecordSetupAlarm(SE299);
                     ExternalPresetAlarm = TRUE;
                  }
                  if(CurrentSetup.SequenceEnable == TRUE &&  //Sequencing enabled
                           CurrentSetup.ExtPresets == TRUE)       //External Preset Enable
                  {
                     RecordSetupAlarm(SE297);
                     ExternalPresetAlarm = TRUE;
                  }
				     if (VGAUSBOfflineFlag)   // Check for USB offline
				     {
				        RecordAlarm(EQ27);
					    VGAUSBOfflineFlag = FALSE;
					    ExternalPresetAlarm = TRUE;
				     }
				     if (VGAPrinterOfflineFlag)   // Check for printer offline
				     {
				        if ((CurrentSetup.ExtPresets && CurrentSetup.ExtGlobalPrintFlag)
				             || ((!CurrentSetup.ExtPresets) && CurrentPreset.GlobalPrintingFlag ))
					    {
					 	   RecordSetupAlarm(SE270);
					       VGAPrinterOfflineFlag = FALSE;
					       ExternalPresetAlarm = TRUE;
					    }
					    else
					       VGAPrinterOfflineFlag = FALSE;
				     }
                 if(VGAUSBFullFlag)
                 {
                    RecordAlarm(EQ13); 
                    VGAUSBFullFlag = FALSE;
                    ExternalPresetAlarm = TRUE;
                 }
                  if (ExternalPresetAlarm == TRUE)
                  {
                     SendSetupData();           /* Notify display system of impending doom */
                     PresetHasBeenOKed = FALSE;
                     AlarmDetectedFlag = TRUE;
                     CountSetupAlarms();
                     ResetStateMachine();     /* Start back at ready     */
                     StartStateMachine();     /* Allows alarms every PB  */
                  }
                  else //(ExternalPresetAlarm == FALSE) No alarm so far
                  {
                     if(PresetNeedsToBeUpdated == TRUE)
                     {
                     UpdateRPreset();
                     }
   
                     /*-- When the palm button is pressed check to make sure  the printer    --*/
                     /*-- is not disconnected or offline. Check if item is selected to print --*/
                     /*-- and if so, set UpdateFlag to TRUE so preset gets verified  --*/

                     PrintEveryCycleFlag = CheckPrintingStatus();
   
                     if(PrintEveryCycleFlag){ 
                       if(OfflineCheckFunc()){
                         UpdateFlag = TRUE;
                         /*-- Resend code to printer --*/
                         InitPrinterOnceOnPowerup = TRUE;
                       }
                     }
   
                     if(AlarmDetectedFlag == TRUE){
                        AlarmDetectedFlag = FALSE;
                        AlarmOff();                       /* Turn off Reset led               */
                        ClearGeneralAlarm();              /* Remove GeneralAlarm,suspect,&reject signals*/
                        ClearWeldingResultsAlarms();
                        ClearFinalResultsAlarms();
                        if((RunScreenFlag == TRUE) && (MenuCounter == 1))
                           SendFakeKeyPress(UPDATEDISPLAY);
                        //UpdateTopLineFlag = FALSE;
                        /* If QVGA H/W is available send Message to the QVGA queue*/
                       if(QVGAHwAvail)
                       {
                          FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                          FPKeyMsg.key = UPDATELINE2;                        
                          CkQSend (QvgaQid, &FPKeyMsg, WELD_MGR,
                           __LINE__, MILLS_TO_TICKS(20));   /* 20 ms        */
                       }   
                     }
                     
                   
                     if (CheckVerifyPresetRequired() ) {
                        StopStateMachine();         /* Stop state machine      */
                        if ( VerifyPreset()==FALSE ) { /* CALL VERIFY PRESET      */
                           StartStateMachine();     /* Start state machine     */
                           UpdateFlag = FALSE;      /* Clear flag              */
                           VerifyPresetRequired = FALSE;
                        }
                        else {      /* Preset bad, what do we do now? */
                           ResetStateMachine();     /* Start back at ready     */
                           StartStateMachine();     /* Allows alarms every PB  */
                        }
                        
                     }
                  }   
                  PresetHasBeenOKed = TRUE;  /* Allow the state machine to advance */
                  break;

               case WAITFORSVINPUTSTATE:
                  break;

               case DOWNSTROKESTATE:
               case WAITFORPTSSTATE:
                  break;

               case TRIGGEREDSTATE:
                  if ((CurrentSequence == CALIBRATION) || (CurrentSequence == SC)) {

                     if(IsCalibGoingOn())
                     {
                        FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                        FPKeyMsg.key = QVGACALIB_KEY;                        
                        CkQSend (RvtsQid, &FPKeyMsg, WELD_MGR,
                           __LINE__, MILLS_TO_TICKS(20));      /* 20 ms        */
                     }
                     else
                     {
                        if(CalibrationPassed == CAL_PASSED)
                           SendFakeKeyPress( Select3Key );  /* advance to pass screen */

                        else if(CalibrationPassed == CAL_FAILED)
                          SendFakeKeyPress( Select1Key );  /* advance to fail screen */
                     }   

                  }
                  break;
                  
               case EXTTRIGDELAYSTATE:
                  break;

               case TRIGGERDELAYSTATE:
                  break;

               case WELDTIMESTATE:
                  break;

               case ENDOFSONICS:
                  break;

               case HOLDTIMESTATE:
                  break;

               case PROCESSALARMSSTATE:
                  CheckProcessLimits();
                  break;

               case AFTERBURSTTIMESTATE:
                  break;

               case AFTERBURSTDELAYSTATE:
                  break;

               case NOP:
               case TESTMODESTATE:
                  break;

               case WAITFORULSMADESTATE:
                  break;

               case SEEKSTATE:
                  break;


               case EMERGENCYSTOPRESET:
                  
                  ActPowerUp();     /* Read current actuator settings */

                  /* Check for Version 8.04 - 8.05 without the offset for AEDs only. */
                  /* This generates ErrorCode 1000. */
                  if((NVR.ActId == NVR_AED)  && (PSNvRamData.ControlLevel >= LEVEL_d) && (NVR.ForceGauge == LOAD_CELL))
                  {
                     if(NVR.LoadCell[0] < NO_LOADCELL_OFFSET)
                     {
                        /* generate recalibrate alarm with error code 1100 set */
                        RecordErrorCode( ERRORCODE1100_EQ20 );
                        RecordAlarm( EQ20 );   /* Recalibrate Actuator */
                     }
                  }
 
                  /* Note: If there is no actuaor Novram, then ActPowerUp    */
                  /* will write some reasonable initial values to NVR.       */
                  /* Therefore, if CheckNvrValid() fails, it must be because */
                  /* it is processing data actually read from Novram, not    */
                  /* the "fake" information supplied by ActPowerUp().  It is */
                  /* therefore safe to conclude that we have an AED actuator.*/

                  if (((NVR.ActId==NVR_AED)||(NVR.ActId==NVR_AEF)||(NVR.ActId==NVR_MICRO)) 
                       && (CurrentSetup.ControlLevel >= LEVEL_d)) {
                     if (!CheckNvrValid())
                     {
                        ActRecover(); /* Put something in there that makes sense */
                        RecordAlarm( EQ10 );  /* Actuator Novram */
                        RecordAlarm( EQ20 );  /* Recalibrate Actuator */
                     }

                     CheckForHornChange();    /* Is the horn weight different when returning */
                  }                           /* from EStop                                  */
                  ActuatorChanged = CheckForActChange();

                  if(CurrentSetup.Actuator != AE )
                     TrsDisabled();
                  else
                     TrsEnabled();

                  if ((CurrentSequence == CALIBRATION) || (CurrentSequence == SC))
                  {
                     SendFakeKeyPress(MainKey);   /* Tell menu system all done    */
                  }
                  else if (DUPSOkFlag == FALSE)
                     SendFakeKeyPress(GoBackKey);   /* exit hornscan menu    */
                     
                  SelectWeldSequence();        /* Then get out                 */
                  SVOff();                     /* Bring horn back home         */
                  
				  /* Don't go in ready state if VGA HW Present and not powered up.*/
				  if((!WindowSetupFlag) && ((!CurrentSetup.VGAHWPresent)||((CurrentSetup.VGAHWPresent)&&(IsHWConfigured(VGA)))))  
				     StartStateMachine();

                  if(HornDownFlag) {
                     AbortFlag = TRUE;
                     HornDownFlag = FALSE;
                     SendFakeKeyPress(MainKey);   /* Tell menu system all done    */
                  }
                  else if(TestSonicsFlag) {
                        PSIdle();               /* Turn off sonics          */
                        TestTimerFlag = TRUE;   /* Advance state machine    */
                        TestSonicsFlag = FALSE; /* Clear flag to show done  */
                        SendFakeKeyPress(MainKey);  /* Tell menu system all done    */
                  }
                  /* Send fake key 'MainKey' if User IO Menu is displayed. */
                  else if(WeldingStopInsideMenu)
                     SendFakeKeyPress(MainKey);
                  else if(UserIOAlarmMenu)
                     SendFakeKeyPress(RunKey);
                     
                  else if(Get_GetMsgFlag() == FALSE)
                          SendFakeKeyPress(GoBackKey); /* Tell menu system all done    */
                  else
                     SendFakeKeyPress(UPDATEDISPLAY);  /* Tell menu system all done    */
                  
                  /*If VGA H/W available send ESTOPMSGRESET to qvga queue*/
                  if(IsHWConfigured(VGA))
                  {
                     FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                     FPKeyMsg.key = ESTOPMSGRESET;                        
                     CkQSend (RvtsQid, &FPKeyMsg, WELD_MGR,
                           __LINE__, MILLS_TO_TICKS(20));      /* 20 ms       */
                  }
                  break;   

               case WAITFORCONTINUE:
               case CALTIMERSTATE1:
               case CALTIMERSTATE2:
               case READA2D1STATE:
               case READA2D2STATE:
               case READA2D3STATE:
               case CALREADYSTATE:
                  break;

               case MENUSYNCSTATE:
                  break;

               case UPDATEALARMSTATE:

                  FinalResults.EquipmentFailureAlarms = WeldingResults.EquipmentFailureAlarms;
                  FinalResults.RejectBitResult = WeldingResults.RejectBitResult;
                  FinalResults.SuspectBitResult = WeldingResults.SuspectBitResult;
                  FinalResults.NoCycleAlarms =  WeldingResults.NoCycleAlarms;
                  FinalResults.OverloadAlarms = WeldingResults.OverloadAlarms;
                  FinalResults.CycleModifiedAlarms = WeldingResults.CycleModifiedAlarms;
                  FinalResults.CalibrateAlarms = WeldingResults.CalibrateAlarms;
                  FinalResults.Warnings = WeldingResults.Warnings;

/*----  Here we need to send Updated Alarm Data over to the System Manager  ----*/

                  WeldDataMsg.common.opcode = OP_READ_ALARM_DATA;
                  CkQSend (SysmQueueId,&WeldDataMsg,WELD_MGR,
                      __LINE__,MILLS_TO_TICKS(10));      
                  break;


               case FINALDATASTATE:

/*----  Get date and time so we can time stamp the weld data  ----*/
                  RTCWeld = RtcReadDateandTime();
                  FinalResults.CycleDate.day = RTCWeld.Day;
                  FinalResults.CycleDate.month = RTCWeld.Month;
                  FinalResults.CycleDate.year = RTCWeld.Year;

                  FinalResults.CycleTime.hour = RTCWeld.Hour;
                  FinalResults.CycleTime.minute = RTCWeld.Minute;
                  FinalResults.CycleTime.second = RTCWeld.Second;

/*----  Load Final Data with current WeldMode, PresetNum & Preset Name. ----*/
                  FinalResults.Weldmode = RunningPreset.WeldMode;
                  FinalResults.PresetNum = CurrentSetup.ActivePreset;
                  strcpy(FinalResults.PresetName, RunningPreset.PresetID);
                  if(!RunningPreset.PresetUpdateComplete)
                     strcat(FinalResults.PresetName, "*");

/* Last, but not least, total cycle time... */
                  FinalResults.CycleTimeResult = TotalCycleTime;

/*----  Here we need to send Final Data over to the System Manager  ----*/

                  WeldDataMsg.common.opcode = OP_FINAL_WELD_DATA;
                  CkQSend (SysmQueueId,&WeldDataMsg,WELD_MGR,
                           __LINE__,MILLS_TO_TICKS(20));      /* 20 ms        */
 
/* checks and Record +R PMC band & -R PMC band alarms here*/
                  CheckPMCWithPwrGraph();
                  if (PMCPlusBandFlag && !(RunningPreset.PMCPlusBandFlag))
                     RecordAlarm(PR21);
                  if (PMCMinusBandFlag && !(RunningPreset.PMCMinusBandFlag))
                     RecordAlarm(PR22);   

/*----  Here we need to send Final Data over to the Print Manager  ----*/
                     
                  if (!IsHWConfigured(VGA))
                  {
                     if(PrintEveryCycleFlag == TRUE){
                        PrinterRestartFlag = TRUE;
                        CkQSend (PrintQid,&WeldDataMsg,WELD_MGR,
                             __LINE__,MILLS_TO_TICKS(20));      /* 20 ms        */

                     }
                     else
                        PrinterRestartFlag = FALSE;
                     StopAtEndOfCycle();
                  }      
                  
                                                     
/*----  Now deal with the serial port (Compuweld, terminal or ASCII output)  ----*/
               
                  switch (CurrentSetup.SerialPort) {
                     case TERMINAL:
                        break;

                     case COMPUWELD:       
                        CkQSend(RschQid,&ReadWeldDataResponseMsg,
                           WELD_MGR,__LINE__, MILLS_TO_TICKS(20));
                       // CkQSend(RvtsQid,&ReadWeldDataResponseMsg,
                         //  WELD_MGR,__LINE__, MILLS_TO_TICKS(20));
                        VGAWeldStartData = TRUE;      
                        break;

                     case ASCIICOMMA:
                        if (CurrentSetup.WelderAddrFlag == 0) {   /* See if Welder ID is on */
                           SPrintf((SINT8*)RS232DataLine, "%4u ", CurrentSetup.WelderAddrValue); 
                           SerialMessageQueue( RS232DataLine, strlen((SINT8 *)RS232DataLine) );
                        }   
                        FormatDataLine(RS232DataLine, &FinalResults, CurrentSetup.Units );
                        RemoveExtraSpaces(RS232DataLine);
                        strsub((SINT8 *)RS232DataLine, SPACE, COMMA);
                        SerialMessageQueue( RS232DataLine, strlen((SINT8 *)RS232DataLine) );
                        SerialMessageQueue( (UINT8*)CRLF, 2 );
                        break;

                     case ASCIITAB:
                        if (CurrentSetup.WelderAddrFlag == 0) {   /* See if Welder ID is on */
                           SPrintf((SINT8*)RS232DataLine, "%4u ", CurrentSetup.WelderAddrValue); 
                           SerialMessageQueue( RS232DataLine, strlen((SINT8 *)RS232DataLine) );
                        }   
                        FormatDataLine(RS232DataLine, &FinalResults, CurrentSetup.Units );
                        RemoveExtraSpaces(RS232DataLine);
                        strsub((SINT8 *)RS232DataLine, SPACE, TAB);
                        SerialMessageQueue( RS232DataLine, strlen((SINT8 *)RS232DataLine) );
                        SerialMessageQueue( (UINT8*)CRLF, 2 );

                        break;

                     case ASCIISPACE:

                        if (CurrentSetup.WelderAddrFlag == 0) {   /* See if Welder ID is on */
                           SPrintf((SINT8*)RS232DataLine, "%4u ", CurrentSetup.WelderAddrValue); 
                           SerialMessageQueue( RS232DataLine, strlen((SINT8 *)RS232DataLine) );
                        }   
                        FormatDataLine( RS232DataLine, &FinalResults, CurrentSetup.Units );
                        RemoveExtraSpaces(RS232DataLine);
                        SerialMessageQueue( RS232DataLine, strlen((SINT8 *)RS232DataLine) );
                        SerialMessageQueue( (UINT8*)CRLF, 2 );
                        break;

                     case RS232DISABLED:
                     default:
//                      No code here, nothing to do!
                        break;
                  }
                  break;

               case WAITFORULSCLEARSTATE:
               case WAITFORTRSSTATE1:
               case WAITFORTRSSTATE2:
               case WAITFORTRSSTATE3:
               case WELDTIME2STATE:
               case RAMPSONICSSTATE:
               case POWERDOWNSTATE:
               default:
                  break;
               case EMERGENCYSTOP:
                  SVOff();                     /* Bring horn back home         */
                  PSIdle();                    /* Turn off sonics          */
                  CoolValOff();
                  /*If VGA H/W available send ESTOPMSGON to vga queue*/
                  if(IsHWConfigured(VGA))
                  {
                     FPKeyMsg.common.opcode = OP_FRONT_PANEL_KEYPRESS;
                     FPKeyMsg.key = ESTOPMSGON;                        
                     CkQSend (RvtsQid, &FPKeyMsg, WELD_MGR,
                        __LINE__, MILLS_TO_TICKS(20));      /* 20 ms       */
                  }      
                  break;

            }
            
            /*Send Message to the VGA queue*/
            if((UpdateTopLineFlag == TRUE) && (IsHWConfigured(VGA)))

            { 
               WeldDataMsg.common.opcode = OP_WELDER_STATE_CHANGE;
               CkQSend (RvtsQid,&WeldDataMsg,WELD_MGR,
                           __LINE__,MILLS_TO_TICKS(20));     
            }

            
            if ((UpdateTopLineFlag == TRUE) && (RunScreenFlag == TRUE) &&
                 (MenuCounter == 1)){
               SendFakeKeyPress(UPDATETOPLINE);
            }


            break;
 
         default:
            break;
      } /* end switch (WmgrMsg.GenericMsg.common.opcode) */

   } /* end while */

} /* end of WeldManager task */

void FormatRunScreenTopLine(void)
/****************************************************************************/
/*                                                                          */
/* Creates the text that should appear on the top line of the run screen.   */
/* StrTopLine must be updated for all the languages                      */
/*                                                                          */
/****************************************************************************/
{
   SINT8 TempStr[LINESIZE+1];
   STR *TempStrTrim;
   SINT8 TempStr1[QVGA_LINESIZE];
      switch (CurrentPreset.WeldMode)
      {
         case TIMEMODE:
            FormatStr2(TempStr, 0, NOCHAR, 2,
                    (CurrentPreset.WeldTime / 1000),
                     '.', 3, (CurrentPreset.WeldTime % 1000) );
            TempStr[LINESIZE] = 0;
            StrCpyTwoBytes(TempStr1, TempStr);
            TempStrTrim = Trim_FillChar(TempStr1); 
            strcpy(StrWeldStateLine, TempStrTrim);

            break;

         case ENERGYMODE:
            if(CurrentPreset.WeldEnergy < 10000)
               FormatStr2(TempStr, 0, NOCHAR, 4,
                         (CurrentPreset.WeldEnergy / 10),
                          '.', 1, (CurrentPreset.WeldEnergy % 10) );
            else
               FormatStr1(TempStr, 0, 5,
               (CurrentPreset.WeldEnergy / 10), NOCHAR);
            TempStr[LINESIZE] = 0;
            StrCpyTwoBytes(TempStr1, TempStr);
            TempStrTrim = Trim_FillChar(TempStr1); 
            strcpy(StrWeldStateLine, TempStrTrim);

            break;

         case PKPOWERMODE:
        	if(CurrentSetup.PeakPowerWattsFlag == TRUE)
        	{
        		FormatVariables( ThreeRulePorcentageToWatts(CurrentPreset.PeakPwr,CurrentSetup.PSWatt), WATTS, TempStr, DIST_STR_SIZE, CurrentSetup.Units );
                TempStr[DIST_STR_SIZE] = 0;
                strcpy(StrWeldStateLine, TempStr);
        	}
        	else
        	{
        		FormatStr2(TempStr, 0, NOCHAR,3, (CurrentPreset.PeakPwr/10),
                           '.', 1, (CurrentPreset.PeakPwr % 10) );
            
        		TempStr[LINESIZE] = 0;
        		StrCpyTwoBytes(TempStr1, TempStr);
        		TempStrTrim = Trim_FillChar(TempStr1);
        		strcpy(StrWeldStateLine, TempStrTrim);
        	}
            break;
       
         case COLLAPSEMODE:
            if ( (CurrentSetup.Actuator == AED) ||
                 (CurrentSetup.Actuator == AEF) ||
                 (CurrentSetup.Actuator == MICRO) )
            {
               FormatVariables( CurrentPreset.ColDist, DISTANCE, TempStr,
               DIST_STR_SIZE, CurrentSetup.Units );
               TempStr[DIST_STR_SIZE] = 0;

               strcpy(StrWeldStateLine, TempStr);
            }
            else
            {
               strcpy(StrWeldStateLine, '\0');
            }
            break;
    
         case ABSOLUTEMODE:
            if ( (CurrentSetup.Actuator == AED) ||
                 (CurrentSetup.Actuator == AEF) ||
                 (CurrentSetup.Actuator == MICRO) )
            {   
               FormatVariables( CurrentPreset.AbsDist, DISTANCE, TempStr,
               DIST_STR_SIZE, CurrentSetup.Units );
               TempStr[DIST_STR_SIZE] = 0;

               strcpy(StrWeldStateLine, TempStr);
            }
            else
            {
               strcpy(StrWeldStateLine, '\0');
            }
            break;
       
         case GRDDETECTMODE:
            strcpy(StrWeldStateLine, '\0');
            break;
       
         case CONTINUOUSMODE:
            strcpy(StrWeldStateLine, '\0');
            break;
         default:             
            strcpy(StrWeldStateLine, '\0');
            break;
      }
}

void UpdateRPreset(void){

   PresetHasBeenOKed = FALSE;
   PresetNeedsToBeUpdated = FALSE;
   memcpy(&RunningPreset, &CurrentPreset, sizeof(RunningPreset) );
   UpdateFlag = TRUE;
   if(PowerUpPresetReceived == TRUE)
      WeldingResults.CycleCount = RunningPreset.WeldCount;
   else{
      RunningPreset.WeldCount = WeldingResults.CycleCount;
      CurrentPreset.WeldCount = WeldingResults.CycleCount;
   }
}

void ClearWeldingResultsAlarms(void)
{
   WeldingResults.NoCycleAlarms = 0;
   WeldingResults.OverloadAlarms = 0;
   WeldingResults.Warnings = 0;
   WeldingResults.EquipmentFailureAlarms &= EQ_NO_RESET;
   WeldingResults.CycleModifiedAlarms = 0;
   WeldingResults.CalibrateAlarms &= CA_NO_RESET;
   WeldingResults.RejectBitResult = 0;
   WeldingResults.SuspectBitResult = 0;
}



void ClearFinalResultsAlarms(void)
{
   FinalResults.NoCycleAlarms = 0;
   FinalResults.OverloadAlarms = 0;
   FinalResults.Warnings = 0;
   FinalResults.EquipmentFailureAlarms &= EQ_NO_RESET;
   FinalResults.CycleModifiedAlarms = 0;
   FinalResults.CalibrateAlarms &= CA_NO_RESET;
   FinalResults.RejectBitResult = 0;
   FinalResults.SuspectBitResult = 0;
}

BOOLEAN CheckVerifyPresetRequired (void)
/****************************************************************************/
/*                                                                          */
/* This function returns TRUE if the preset needs to be verified and return */
/* FALSE if not needs to be verified.The function checks for the HwCnfg     */
/* and UserIO alarm conditions to verify preset again.                      */
/*                                                                          */
/****************************************************************************/
{
    BOOLEAN RetVal = FALSE;
    static UINT16 LastActivePreset = 0;
  
    static UINT16 LastActiveWeldMode = TIMEMODE;  
    /* In case of Recall preset verify preset only if 
        CurrentPreset.verified= FALSE */
    if(ResetRecall_UpdateFlag)
    {
        UpdateFlag = FALSE;
        ResetRecall_UpdateFlag = FALSE;
    }

    if(CurrentPreset.Verified)
    {
       /* Verify again if HwCnfg is changed or any of the UserIOAlarm condition is TRUE */
       if(RunningPreset.HwCnfg != GetCurrentHwCnfg() || (RunningPreset.ExtTrgDelay == TRUE && 
          !IsConfigured(INPUT_EXT_TRIGDELAY)) || (RunningPreset.EnergyBraking == TRUE && 
          CurrentSetup.AmpControl == FALSE))
          CurrentPreset.Verified = FALSE;
       /* Check for MissingPart alarm condition. */   
       else if ( (CurrentSetup.Actuator == AEF) ||
                 (CurrentSetup.Actuator == AED) ||
                 (CurrentSetup.Actuator == MICRO) ) {
          if (IsOutConfigured(OUTPUT_MISSING_PART) && ((RunningPreset.CycleAbortFlag == FALSE) ||
              (RunningPreset.MissingPartFlag == FALSE) || (RunningPreset.MissingMinFlag &&
               RunningPreset.MissingMaxFlag) ))
             CurrentPreset.Verified = FALSE;
         }
    } 

   if (((UpdateFlag) && (CurrentSequence == WELD)) ||
      (CurrentPreset.Verified == FALSE) || VerifyPresetRequired )
      RetVal = TRUE; /* Preset Needs to Verify. */
    
/****    Fix for version 9.04    ****/

   if ((CurrentSetup.ActivePreset != LastActivePreset)||(RunningPreset.WeldMode != LastActiveWeldMode))  {
      LastActivePreset = CurrentSetup.ActivePreset;
      LastActiveWeldMode = RunningPreset.WeldMode;
      SelectWeldSequence();                     /* Create new weld sequence*/
      SetIndex(2);                         /* Bounce index back to ready   */
      StartStateMachine();                 /* Start the state machine here */
   } 
    
   return(RetVal);
}

/* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "weldmngr.ut"
#endif
/* FOR UNIT TEST ONLY */
