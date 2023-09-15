/* $Header:   D:/databases/VMdb/2000Series/App/READY.C_V   2.359.1.1.1.1.1.5.1.2   Jan 03 2018 10:13:46   RCHAPA  $ */
/* ************************************************************************ */ 
/*                                                                          */
/*                                                                          */
/*   Copyright (c) Branson Ultrasonics Corporation, 1995, 1996,97, 2009     */
/*   This program is the property of Branson Ultrasonics Corporation        */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/* ************************                         *********************** */
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Ready                                                       */
/*                                                                          */
/* Filename:    Ready.c                                                     */
/*                                                                          */
/* Function Name: State machine code                                        */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   03-15-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date      Author     Description                             */
/*  =========  ========= =========  ===========                             */
/*     0       03-20-96  BEKymer    Add pSOS to state code                  */
/*     1       05-13-96  BEKymer    Add proper function prototyping         */
/*     2       06-06-96  BEKymer    Add function TriggerBeep                */
/*     3       06-27-96  LAM        moved peakpower = 0                     */
/*     4       07-08-96  BEKymer    Clear DistFlag in EnterReady            */
/*     5       07-08-96  BEKymer    Make Rapid Traverse work correctly      */
/*     6       07-08-96  BEKymer    Reset power when leaving PB state       */
/*     7       07-15-96  BEKymer    Remove tenths of percent in power       */
/*     8       07-19-96  BEKymer    New function to clear AbortFlag         */
/*     9       07-28-96  LAM        moved init finalresults                 */
/*    10       08-02-96  BEKymer    Remove Time from end of variable names  */
/*    11       09-17-96  LAM        added peak power = 0 to testuls         */
/*    12       09-24-96  BEKymer    Use FinalResults.CycleCount instead     */
/*                                  of RunningPreset.WeldCount              */
/*    13       10-01-96  BEKymer    RecordAlarm now puts results in Final   */
/*                                  Results structure & handles Suspect and */
/*                                  Reject outputs                          */
/*    14       10-03-96  BEKymer    Remove while(1) pSos error loops        */
/*    15       10-07-96  BEKymer    New function CheckIfResetRequired       */
/*    16       10-08-96  BEKymer    Check control limits while waiting for  */
/*                                  trigger. DCS #624.                      */
/*    17       10-09-96  BEKymer    Added SelectForceControl to ExitTrs2    */
/*                                  Set force to trigger value in ExitTrs2  */
/*    18       10-14-96  LAM        added ramp downspeed start              */
/*    19       10-15-96  BEKymer    Add 0 case to RecordAlarms              */
/*    20       10-18-96  BEKymer    Change MAXTESTTIME from 10000 to 2000   */
/*    21       10-24-96  BEKymer    Put back commented code in EUpstroke    */
/*    22       10-26-96  LAM        chged rtflag                            */
/*    23       10-28-96  BEKymer    Output SystemFault signal               */
/*    24       10-31-96  BEKymer    StopDataCollection in TestReady         */
/*    25       11-02-96  BEKymer    Fix Exit/Enter Test code                */
/*    26       11-07-96  BEKymer    Use UPDATEDATASTATE instead of FINAL    */
/*                                  DATASTATE to UpdateDisplay              */
/*    27       11-08-96  BEKymer    In StartPB state reset SONICSTIMER      */
/*    28       11-14-96  BEKymer    Test for uls in act clr function        */
/*    29       11-16-96  BEKymer    New function - ClearFinalResults        */
/*    30       11-18-96  BEKymer    In RecordAlarm dont call UpdateDisp for */
/*                                  alarms already recorded                 */
/*    31       11-20-96  BEKymer    Create ExitUpstroke function            */
/*    32       11-21-96  LAM        added changed q_send,added partcontactflg*/
/*    33       12-09-96  LAM        moved velocity cal. to TestTRS2         */
/*    34       12-11-96  BEKymer    In ExitPB only start data collection if */
/*                                  CurrentSequence is not HORNDOWN         */
/*    35       01-06-97  LAM        redefined beep prototype                */
/*    36       01-10-97  PhilJ      UINT32 CurrentFreqIn to SINT32.         */
/*                                  TestTimerCounter incremented at entry   */
/*                                  of function. Modified TestTest function */
/*    37       01-11-97  LAM        deleted getcurrentactuator,added endweldmsg*/
/*    38       01-21-97  LAM        deleted resend of alarms                */
/*    39       01-21-97  LAM        chged reset alarms                      */
/*    40       02-03-97  LAM        chged systemfault alarms                */
/*    40.01    02-03-97  LAM        clear overload after alarm              */
/*    40.02    02-06-97  LAM        chged test states                       */
/*    41.00    02/07/97  LAM        moved actclr to preset,moved clear peakpower at exitready*/
/*    42.00    02/18/97  LAM        fixed extern reset                     */
/*    43.00    02/25/97  LAM        added cycle abort check,fixed warnings  */
/*    44.00    03/01/97  LAM        fixed actuator return,added freqoffset  */
/*    45.00    03/10/97  LAM        chged velocity calculation              */
/*    46.00    03-17-97  LAM        modified what is done every ms          */
/*    47.00    03-19-97  PhilJ      Corrected bug in TestUpstroke           */
/*    47.01    03/19/97  LAM        chged velocity calculation back         */
/*    47.02    03/19/97  LAM        fixed update5ms                         */
/*    48.00    03/27/97  LAM        deleted update data call                */
/*    48.01    03/27/97  LAM        only call updatedata when in ready state*/
/*    48.02    03/27/97  PhilJ      Renamed UpdateData() to UpdateAlarm     */
/*    48.03    04/03/97  PhilJ      fixed actclr                            */
/*    48.04    04/04/97  LAM        fixed alarms in test mode               */
/*    48.05    04-04-97  BEKymer    Added code to delay the Ready signal at */
/*                                  power up.                               */
/*                                  Sound the beeper for a warning          */
/*    49.00    04/06/97  LAM        deleted upstroke state,added test actclr*/
/*    49.01    04-08-97  BEKymer    In RecordAlarm (case 0) add UpdateDispFl*/
/*    49.02    04-08-97  LAM        fixed test screen                       */
/*    49.03    04-09-97  PhilJ      TotalAlarmCounter incremented in        */
/*                                  RecordAlarm.                            */
/*    50.00    04-09-97  LAM        added testulsup function                */
/*    51.00    04-11-97  BEKymer    Add in new approach for velocity        */
/*    51.01    04_16-97  BEKymer    New function EnterUls                   */
/*    51.02    04-22-97  PhilJ      Added AutoTrigFlag check in TestPTS     */
/*                                  Added OverLoadCounter to RecordAlarms   */
/*    51.03    04-29-97  BEKymer    Allow for removing Ready for warnings   */
/*                                  Change POWERUPREADYDELAY to 2500        */
/*                                  Allow for removing Ready for SystemFault*/
/*                                  Add more checks in CheckIfResetRequired */
/*    52.00    05-01-97  BEKymer    Do Upper Limit Timeout check in TestUls */
/*    52.01    05-05-97  LAM        donot do psidle in preready             */
/*    52.02    05-08-97  PhilJ      Removed incrementing TotalAlarmCounter  */
/*    53.2.96  05-08-97  BEKymer    Allow RecordAlarm to set SonicsAbort    */
/*                                  and CycleAbort flags                    */
/*    54.00    05-09-97  LAM        only update bargraph when sonics on in test*/
/*    54.01    05-09-97  PhilJ      Added OVERLOADMASK test in RecordAlarm  */
/*    55.00    05-12-97  LAM        initialized velocity timers to 1        */
/*    55.2.100 05-12-97  BEKymer    In CheckIfResetRequired look for alarms */
/*                                  which cannot be reset.                  */
/*    56.00    05-13-97  PhilJ      Deleted incrementing of Overload Counter*/
/*    56.2.102 05-13-97  BEKymer    Added clear UpperLimitTimer & UlsTimeout*/
/*                                  to StartPB function in case EnterUls    */
/*                                  code did not execute because of ABORT   */
/*    56.2.103 05-14-97  BEKymer    In TestReady, if no alarms call TrigSwAc*/
/*    57.2.104 05-21-97  BEKymer    Add delay to ready output               */
/*             05-27-97  BEKymer    Add recovery code to TestUls            */
/*    57.2.105 05-29-97  BEKymer    StartStateMachine after recovery code   */
/*                                  Reset P.S. before entering Test mode    */
/*                                  Clean up CheckIfResetRequired()         */
/*    58.2.106 06-03-97  BEKymer    New flag TestModeAllowed                */
/*    58.2.107 06-11-97  LAM        removed test store and clear            */
/*    59.2.108 06-23-97  BEKymer    Allow  for new alarm groups             */
/*                                  Create new function RecordSetupAlarm    */
/*    60.2.109 07-01-97  Jberman    Adding MissedPartMin/Max functions      */
/*    60.2.110 07-01-97  LAM        Adding pbreleaseoff,added testmenu      */
/*    60.2.111 07-01-97  LAM        Added no encoder functions              */
/*    60.2.113 07-10-97  BEKymer    Continue work on new alarms             */
/*    60.2.114 07-17-97  PhilJ      Changed Special Character in TestBuffer1*/
/*                                  from 0x40 to 0x7e                       */
/*    60.2.115 07-17-97  BEKymer    Removed unused variable NotReadyFlag    */
/*    60.2.116 07-21-97  BEkymer    Change logic in TestActClr              */
/*    60.2.117 07-25-97  LAM        added memstoreoutput = 0                */
/*    60.2.118 07-29-97  BEKymer    Remove unused AlarmDetectedFlag         */
/*    60.2.119 07-30-97  BEKymer    Check PB's in TestPreReady before count-*/
/*                                  ing PBExitTimer                         */
/*    60.2.120 08-01-97  BEKymer    Check for EQ4 in ExitULS1               */
/*                                  Clear EnergyinJoules in ExitReady       */
/*                                  Check OL_CYCLE_ABORT in case OLG1       */
/*                                  CheckIfResetRequired fix DCS #1822      */
/*                                  In StartPB, leave alarm screen when PB's*/
/*    61.2.121 08-11-97  LAM        deleted startdatacollection             */
/*    61.2.122 08-12-97  BEKymer    Reset EncoderFailTimer in ExitPB        */
/*    61.2.123 08-12-97  PaulG      Added function to toggle data storage   */
/*    62.2.124 08-17-97  LAM        replaced getpower                       */
/*    2.125    08-23-97  LAM        Deleted triggerattime                   */
/*    2.126    08-26-97  LAM        added init1mspts to enterpb             */
/*    2.127    08-27-97  BEKymer    In ClearAlarm() add checks for Printer  */
/*                                  Buffer full, start switches released &  */
/*                                  power supply overload.                  */
/*                                  Deleted FinalResults.Sonics.. = 0   LAM */
/*    2.128    08-28-97  BEKymer    Fix ClearAlarm (Inp.OL) logic           */
/*                                  Reset ResetReceivedFlag in CheckIfReset.*/
/*    2.129    08-29-97  BEKymer    In ClearAlarm only clear Door switch &  */
/*                                  Thermal O/L  and test O/L if reset key  */
/*                                  was pressed                             */
/*    2.130    08-31-97  LAM        clear clear & store when entering ready */
/*    2.131    09-03-97  LAM        update store & clear in readytest       */
/*    2.132    09-03-97  BEKymer    Change PTSTime from UINT16 to SINT32    */
/*    2.133    09-04-97  BEKymer    Use OKToAdvance in TestPB               */    
/*    2.134    09.11.97  JBerman    Added default into switch statements    */
/*    2.135    09.17.97  LAM        moved freq offset to enteruls,fixed clear & */
/*                                  and store in test                       */
/*    2.136    09-18-97  BEKymer    Clear OKToAdvance in ExitPB             */
/*                                  In ClearFinalResults only clear alarms  */
/*                                  if ClearALarm says its ok               */
/*                                  In ClearAlarm() check printer stuff     */
/*    2.137    09-25-97  BEKymer    Check for setup hardwares in ClearAlarm(*/
/*    2.138    09-25-97  BEKymer    Add #include "alsetup.h"                */
/*    2.139    09-25-97  PaulG      Removed OfflineCheckFunc from ClearAlarm*/
/*    2.140    09-26-97  BEKymer    If Preset need updating dont clear alarm*/
/*    2.141    09-26-97  BEKymer    In CheckIfReset... test EQ_NO_RESET     */
/*                                  In TestTest check ResetReceivedFlag     */
/*                                  In TestPB, add code to deal with Hdown  */
//    2.142    09.31.97  JBerman    Expended conditions in TestActClr function                                                        
/*    2.143    10-03-97  BEKymer    Add check for BBR in ClearAlarm()       */
/*    2.144    10-15-97  PaulG      Modified ChangeDataStorage location     */
/*    2.145    10-16-97  BEKymer    Check ColdStartInProcess flag in Clear  */
/*                                  Alarm()                                 */
/*    2.146    10.16.97  LAM        removed freq offset, only increment alarmcounter*/
/*                                  if it has not been recorded already     */
/*    2.147    10-21-97  BEKymer    Dont remove ready output in ExitReady() */
/*                                  if preset needs verifing, do it instead */
/*                                  in TestPB().                            */
/*                                  In CheckIfResetRequired() don't remove  */
/*                                  General Alarm if setup alarms exist     */
/*                                  Check EQ_REJECT in EQG1 case            */
/*    2.148    10.27.97  LAM        fixed updating leds,chged testpreread   */
/*    2.149    10-28-97  BEKymer    Added ULSExitTimer                      */
/*    2.150    10-31-97  BEKymer    Change the way overloads are handled in */
/*                                  ClearAlarm().                           */
/*    2.151    10.31.97  LAM        moved clearing store to exitready       */
/*    2.152    11-03-97  BEKymer    In StartPB() send RunKey if on run      */
/*                                  screen or any sub menu of it            */
/*    2.153    11-04-97  BJB        Don't send RunKey if on run screen, just*/
/*                                  on submenus. Also don't send if in      */
/*                                  HornDown mode.                          */
/*    2.154    11-06-97  BEKymer    Only clear ULS_FAIL if reset pressed in */
/*                                  ClearAlarm().                           */
/*                                  Call DisplayCurrentPreset in ClearAlarm */
/*                                  Dont' clear OVERLOADS_RESET unless      */
/*                                  ResetReceivedFlag is TRUE               */
/*                                  Remove check for setup alarms in        */
/*                                  ClearAlarm().                           */
/*    2.155    11-10-97  PaulG      Checked if Printer is offline before    */
/*                                  clearing any printer                    */
//    2.156    11.12.97  JBerman    Added PwrTestFilter
/*    2.157    11-12-97  PaulG      Added PoweredOffCheckFunc().            */
/*    2.158    11-14-97  BEKymer    Remove DisplayCurrentPreset() in StartPB*/
/*    2.159    11-18-97  BEKymer    In ClearAlarm() make sure overload is   */
/*                                  gone BEFORE clearing FinalResults.Over..*/
/*                                  Clear ResetReceivedFlag whenever a new  */
/*                                  alarm is recorded.                      */
/*    2.160    11.19.97  LAM        fixed offline online                    */
/*    2.161    11-18-97  LAM        replaced finalresults with weldingresults*/
/*    2.162    11-20-97  PaulG      Added PrintAnyway flag to check if Print */
/*                                  Now was pressed.                         */
/*    2.163    11-20-97  LAM        chged ckqsend to q_send                  */
/*    2.164    12-01-97  LAM        deleted readydelay, cleanup checkifresetreq*/
/*    2.165    12.01.97  JBerman    Inserted CoolValOff into EPreRead                                                                   */
/*    2.166    12-01-97  BEKymer    New Flag AdjustWeldSetupMenuFlag        */
/*    2.167    12-03-97  BEKymer    Set AbortFlag in NCG1 case in RecordAlar*/
/*    2.168    12-04-97  BEKymer    Remove BBR check in ClearAlarm().       */
/*    2.169    12-04-97  LAM        Stop data collection on a cycle abort   */
/*    2.170    12-05-97  LAM        corrected date on file                  */
/*    2.171    12-05-97  BEKymer    New flag - OkToDisplayAlarms            */
/*    2.172    12-05-97  LAM        Stop data collection when enterpreready */
//    2.173    12.08.97  JBerman    Added: 1) DisplayTestPower(PeakTestPower)
/*                                    inside ExitTest, following reset all  */
//                                    associated power values.
//                                  Barry's request: Added OkToDisplayAlarms=TRUE
//                                  into EnterReady
/*    2.174    12-10-97  BEKymer    Another new flag - DontPrintGraph       */
/*    2.175    12-11-97  BEKymer    Fix double equal in RecordAlarm         */
/*    2.176    12-11-97  BEKymer    In RecordAlarm dont allow graphs unless */
/*                                  sonics have started (TRS reached)       */
/*    2.177    12-11-97  BEKymer    In RecordAlarm dont allow graphs unless */
/*                                  sonics have started for 5 ms            */
/*                                  Set ActualSeekTime to 0 when PB's hit   */
/*    2.178    12-12-97  BEKymer    Fix logic on above test                 */
/*    2.179    12.15.97  JBerman    Reset PowerTest in EnterTest instead of */
//                                  ExitTest             
/*    2.180    12-17-97  BEKymer    Allow alarms to be displayed in preready*/
/*    2.181    12-29-97  BJB        Updates test screen only every 1/2 sec  */
/*                                   if remote terminal is being used.      */
/*                                  Terminated comments to satisfy compiler */
/*    2.182    01-20-98  PaulG      Combined Offline and powered off function */
/*    2.183    01-22-98  BJB        RecordAlarm() increments overload count */
/*                                  Changed block chr 0xbe to '|' so block  */
/*                                   appears right on screen and terminal.  */
/*    2.184    01-27-98  BJB        Added globals LatchPSRun, LatchPSSeek,  */
/*                                   LatchPSClear, LatchPSStore.            */
/*    2.185    01.27.98  JBerman    DCS 2265: Don't show PeakTestPower;     */
/*                                  In ExitTest: comment out DisplayTestPower*/
/*                                   TestTest:commentout PeakTestPower test */
/*    2.186    01-27-98  BJB        Test mode functions write input signals */
/*                                   to latch variables, not to display text*/
/*                                   string.                                */
/*    2.187    01-28-98  BEKymer    New function-EnterUlsUp, modified Test  */
/*                                  UlsUp to look for trigger 20 ms after   */
/*                                  upper limit is active                   */
/*    2.188    01-30-98  LAM        moved setting downspeed to exitpb       */
/*    2.189    01-30-98  BJB        Made UpdatedDisplayFlag local to the    */
/*                                   functions that use it.                 */
/*                                  Increments CurrentSetup.GenAlarmCount   */
/*                                   when new alarm received and output set.*/
/*                                   Must count bits because one call can   */
/*                                   record multiple alarms.                */
/*    2.190    01-30-98  BEKymer    Don't allow overloads to be cleared in  */
/*                                  ClearAlarm() unless Gen Alarm Latch is  */
/*                                  not on.                                 */
/*    2.191    02-02-98  LAM        do not clear a wrong actuator alarm     */
/*    2.192    02-02-98  BEKymer    Create EnterFData; send final data only */
/*                                  if weld time greater than zero.         */
/*                                  Clear OKToAdvance in ExitULS, AlarmUls  */
/*                                                                          */
/*    2.193    02-04-98  BEKymer    Move 'AtTime' values from WELD_DATA to  */
/*                                  WELD_OBJECT structure                   */
/*    2.194    02-09-98  BJB        Changed rules on incrementing General   */
/*                                   Alarm Counter, now once per PB press.  */
/*    2.195    03-05-98  BEKymer    Initialize timers in final data state   */
/*    2.196    03-10-98  LAM        moved init pb & uls timers & flags to   */
/*                                  clearabort, commented out triggerdelay  */
/*                                  code                                    */
/*    2.197    03-13-98  LAM        removed clearing overload alarms in clear*/
/*                                  alarms                                  */
/*    2.198    03-13-98  BEKymer    In TestPreReady check for printer off-  */
/*                                  line every 5 seconds                    */
/*    2.199    03-16-98  BEKymer    In TestPreReady call RecordSetupAlarm   */
/*                                  for SE270                               */
/*    2.200    03-16-98  BEKymer    Simplify TestPreReady code for SE270    */
/*    2.201    03-18-98  BEKymer    Don't count setup alarm if UpdatedDisp..*/
/*                                  if TRUE                                 */
/*    2.202    03-19-98  BEKymer    ClearSetupAlarms() in TestPB to clear   */
/*                                  Printer Offline alarm                   */
/*    2.203    03-19-98  BEKymer    In ClearFinalResults() set WeldingRes...*/
/*                                  AmpControl equal to CurrentSetup.AmpCon */
/*    2.204    03-20-98  BEKymer    AmpControl->AmpControlFlags in Clear    */
/*                                  FinalResults()                          */
/*    2.205    03-20-98  BEKymer    Move call to ClearFinalResults from     */
/*                                  StartPB() to TestPB after PresetHasBeen.*/
/*    2.206    03-23-98  BEKymer    In RecordAlarm() check for EQ which     */
/*                                  will not set the CycleAbort flag.       */
/*    2.207    03-23-98  BEKymer    See if anything to print before calling */
/*                                  alarm SE270 in TestPreReady().          */
/*    2.208    03-26-98  PaulG      Modify PrintBottomFlags so all flags    */
/*                                  except MANUALSCALEFLAG.                 */
/*    2.209    03-28-98  BEKymer    In ExitPB() make sure MsDataPtr->TotalPt*/
/*                                  contains the PrinterTotalCount          */
/*    2.210    03-28-98  BEKYmer    Add PrinterIncCounts & PrinterCopyPts   */
/*    2.211    04-01-98  PaulG      Add PrinterNewInc                       */
/*    2.212    04-06-98  BEKymer    Clear ActualABDelay in StartPB() so     */
/*                                  seek end time is calculated correctly.  */
/*                                  Remove all references to DontPrintFlag  */
/*    2.213    04-08-98  LAM        Added oktodisplayalarms to EnterFData   */
/*    2.214    04-17-98  LAM        only delay ready when the actuator=AE   */
/*    2.215    04-21-98  LAM        clear inp.trigger on upstroke when!= AE */
/*    2.216    04-21-98  BJB        Modified CalculateVelocity() to return  */
/*                                   the velocity, not write directly to    */
/*                                   WeldingResults.                        */
/*                                  Moved PBEXITTIME def to STATE.H         */
/*    2.217    04-27-98  LAM        deleted unused upstroke routines, remove*/
/*                                  inp.trigger in exit preready            */
/*    2.218    04-29-98  BEKymer    Added alarm W1 in TestActClr().         */
/*                                  Added alarm CA1 in TestReady()          */
/*    2.219    05-04-98  BEKymer    Set OldDistance to current encoder value*/
/*                                  when upper limit switch is cleared.     */
/*                                  This will increase the accuracy of the  */
/*                                  velocity calculation.                   */
/*                                  Move ActClrOff() from EnterReady() and  */
/*                                  EnterTestReady() to EnterPB().  This    */
/*                                  will keep the Actuator clear output     */
/*                                  active until the PB's are pressed again.*/
/*                                  Clear PressureReadDelay in EnterReady().*/
/*                                  New function - ClearCalibrationAlarms().*/
/*    2.220    05-05-98  BEKymer    In ClearCalibrationAlarms() send a Reset*/
/*                                  key to weldmngr to clear all alarms     */
/*                                  after the calibration is complete.      */
/*    2.221    05-08-98  LAM        change sendkeypress to sendkeytoweldmngr*/
/*    2.222    05-11-98  BEKymer    Add calibration check to ClearAlarm()   */
/*                                  Remove check for pressure in TestReady()*/
/*    2.223    05-22-98  BEKymer    Add EQ_UPDATE_OFTEN in RecordAlarm to   */
/*                                  allow some Equipment Failure alarms to  */
/*                                  to be repeatedly updated on display     */
/*    2.224    05-22-98  BEKymer    Light the 0% led if external seek       */
/*    2.225    05-27-98  BEKymer    Increment PTSTimer while waiting for    */
/*                                  trigger.                                */
/*                                  In ClearCalibration.. if no alarms then */
/*                                  don't globally issue a reset key.       */
/*                                  Create .1"/sec as velocity minimum if   */
/*                                  enough movement is detected.            */
/*    2.226    06-01-98  BEKymer    Remove 'Part contact' algorithym in     */
/*                                  CollectVelocityData.  Now collect until */
/*                                  trigger is really reached.              */
/*    2.227    06-01-98  BJB        Fixed timing for remote terminal, was   */
/*                                   adding only 1/4 sec to test time every */
/*                                   1/2 sec.  Now updates time each ms.    */
/*    2.228    06-03-98  BEKymer    Move all missing part tests into 1 func */
/*                                  Change AmpControlFlag to PowerSupply    */
/*                                  ControlFlag                             */
/*    2.229    06-15-98  BEKymer    Remove call to DisplayCurrentPreset in  */
/*                                  ClearAlarm.  This helps to fix DCS#2654.*/
/*    2.230    06-19-98  BEKymer    Change VELOCITY_MINIMUM to 10           */
/*                                  Adjust ClearCalib.. to handle CA1 moving*/
/*                                  to EQ20.                                */
/*    2.231    06-22-98  PaulG      Stopped collected point on part contact */
/*    2.232    06-22-98  BEKymer    Renamed structure member ActualForceMax */
/*                                  to WeldForceMax                         */
/*    2.233    06-23-98  LAM        updated WeldPressure when exiting ready */
/*    2.234    06-24-98  BEKymer    Add check for calibrate alarm in Clear  */
/*                                  Alarm() function so it won't be reset   */
/*                                  in weldmngr when reset is pressed.      */
/*    2.235    06-25-98  BEKymer    Fix test in ClearAlarm(). Was wrong!    */
/*    2.236    06-30-98  BEKymer    Modified ClearCalibrationAlarms() so    */
/*                                  Reset is called even for Cal Warning    */
/*    2.237    06-30-98  BJB        Added Inp.Trigger = FALSE in a couple   */
/*                                   of places to prevent DoorOpen alarms   */
/*                                   after a cycle.                         */
/*                                  Removed check of Inp.Trigger in         */
/*                                   TestUlsUp().                           */
/*    2.238    06-30-98  BEKymer    Adjust velocity so return value is at   */
/*                                  least the minimum AT ALL TIMES.         */
/*    2.239    07-15-98  BEKymer    For alarm W1 use whichever is larger    */
/*                                  ActualDistance or ActualTriggerDistance */
/*    2.240    07-20-98  BEKymer    Clear PTSTimer when pre-trigger starts  */
/*                                  so @time is from sonics not uls cleared */
/*                                  In ClearAlarm() only check AETrigger if */
/*                                  CurrentSetup.Actuator is AE             */
/*    2.241    07-24-98  BEKymer    Fix word/byte issue in CalculateVeloc...*/
/*    2.242    07-27-98  BEKymer    Collect velocity data every ms for a    */
/*                                  max of 500 points.                      */
/*    2.243    07-29-98  BEKymer    Collect velocity data every 2 ms.       */
/*                                  Change Velocity array to a byte and     */
/*                                  allow 3 cycles of history data and part */
/*                                  contact value.                          */
/*    2.244    07-29-98  BEKymer    In ClearAlarm clear EQ17 in both Final  */
/*                                  and Welding Results structures if reset */
/*                                  as been pressed.                        */
/*    2.245    08-05-98  BEKymer    Added ability to collect velocity data  */
/*                                  before ULS is cleared starting after    */
/*                                  distance has reached VELOCITY_DIST_MIN  */
/*    2.246    08-06-98  PaulG      Saved CurrentPressure to GaugePressure. */
/*    2.247    08-06-98  BEKymer    Added MIN_POINTS and set to 3           */
/*    2.248    08-10-98  BEKymer    Rename ActualCollapse to ActualTotal    */
/*                                  Collapse and add ActualWeldCollapse     */
/*    2.249    08-12-98  BEKymer    CollectVelocityData while in TestPTS()  */
/*                                  Also clear FinalResults when clearing   */
/*                                  calibration alarms                      */
/*    2.250    08-18-98  LAM        temporary Removed renaming of ActualCollapse */
/*                                  to ActualTotal for beta release         */
/*    2.251    08-18-98  LAM        compiler error                          */
/*    2.252    08-18-98  LAM        with actualtotal and actualcollapse back*/
/*    2.253    08-19-98  BJB        Changed call RemoteTermInUse() to new   */
/*                                  name, TermIsEnabled().                  */
/*    2.254    08-24-98  LAM        chged currentpressure to homepressure   */
/*    2.255    09-02-98  BEKymer    Add argument to CheckControlLimitsD to  */
/*                                  ensure encoder is still checked.        */
/*                                  Change VELOCITY_SAMPLE_RATE to 1 and    */
/*                                  MIN_POINTS to 2.                        */
/*    2.256    09-03-98  BJB        Uses new functions AlarmOn() and        */
/*                                  AlarmOff() to control reset LED.        */
/*    2.257    09-08-98  BEKymer    In ExitPB() set amp to pre-trigger value*/
/*                                  if pre-trigger enabled otherwise set to */
/*                                  weld amplitude.  This to address DCS    */
/*                                  issue #2727.                            */
/*                                  Always collect at least 2 points for    */
/*                                  velocity even if 'part contact' reached */
/*    2.258    09-10-98  BEKymer    Fix velocity calculation when part con- */
/*                                  tact is never reached.                  */
/*                                  Fix amplitude when pre-trigger on vs off*/
/*                                  Add code to save home distance vs uls   */
/*    2.259    09-21-98  BEKymer    Fix CollectVelocityData to handle neg.  */
/*                                  distances correctly                     */
/*    2.260    09-23-98  BEKymer    Fix yet another bug in the Collect      */
/*                                  VelocityData routine.  Make sure enough */
/*                                  points are collected so we don't wrap   */
/*                                  around to left over points.             */
/*    2.261    10-01-98  BEKymer    Clear the MaxForceFlag when PB's pressed*/
/*                                  Moved CycleCount++ and copy of Welding  */
/*                                  results to Final from FINALDATASTATE    */
/*                                  to SendFData in Ready.c                 */
/*    2.262    10-15-98  BEKymer    Remove commented code in ClearAlarm.    */
/*                                  In ClearAlarm() keep track if any alarms*/
/*                                  were cleared each call.  If so, then    */
/*                                  send message to system manager to up-   */
/*                                  date run screen line 2.                 */
/*                                  In CollectVelocityData() stop collecting*/
/*                                  data if the minimum trigger value is    */
/*                                  reached before part contact is reached. */
/*                                  This is a fix for DCS # 2965 at the last*/
/*                                  minute (again).                         */
/*    2.263    10-23-98  BEKymer    Fix velocity bug in CalculateVelocity() */
/*                                  Error 2 was not using TotalTimeValue in */
/*                                  RetVelocity calculation                 */
/*    2.264    11-06-98  BEKymer    Create define TRIGGER_FORCE_TEST to     */
/*                                  allow printing of trigger distance and  */
/*                                  trigger force for testing.              */
/*    2.265    11-06-98  BEKymer    Change PARTCONTACTDISTANCE to 15 for    */
/*                                  velocity calculation                    */
/*    2.266    11-12-98  LAM        Removed TRIGGER_FORCE_TEST define       */
/*    2.267    11-20-98  BEKymer    Remove min force as condition in part   */
/*                                  contact for velocity calculation        */
/*    2.268    03-15-99  LAM/BEK    added extra argument to set velocity and*/
/*                                  set force functions,added AEF_ACTUATOR  */
/*                                  define                                  */
/*                                                                          */
/*    2.269    04-23-99  OFI        changed for Diab                        */
/*    2.270    05-07-99  JZ         changed StepAtDist to StepAtCol         */ 
/*    2.271    05-14-99  OFI        changed StepAtCol to StepAtRTDist       */
/*    2.272    05-18-99  JZ         changed WeldForceMax to WeldForceEnd,   */
/*                                  ActualForceStart to SetForceA,          */
/*                                  ActualForceEnd to SetForceB,            */
/*                                  PowerSupplyControlFlags to PSActControlFlags */                                       
/*    2.273    05-19-99  JZ         corrected for step force (BIT4)         */
/*    2.273.1.1 07-01-99 JZ         added SetPV and deleted some code       */
/*    2.273.1.2 07-01-99 JZ         added CurrentVelocity, VelocityEstimator */
/*    2.273.1.3 07-06-99 JZ         added EQ25 alarm code, ErrorCode = 0 in */
/*                                  function ExitPB                         */
/*    2.276     08-03-99 JZ         added check for PartContact before call */
/*                                  CheckForSafety                          */
/*    2.277     08-04-99 JZ         added ErrorCodeFlag                     */
/*    2.278     08-06-99 JZ         changed JustPowerUpFlag to BOOLEAN      */
/*                                  added RecordErrorCode                   */
/*                                  first arg. of SetPV typecasted to UINT16*/
/*    2.279     08-11-99 JZ         chngd to HOME_TO_RT in ExitPB           */
/*    2.280     08-23-99 JZ         added call to system pressure check,    */
/*                                  UpdatePressureOffset, UpdateDistanceOffset*/
/*    2.281     09-07-99 JZ         fixed system pressure calls, used global */
/*                                  PartContactFlag for Velocity calculation */
/*    2.282     09-08-99 BEKymer    Use ActualPointCounter instead of array */
/*                                  index difference for velocity calc.     */
/*    2.283     09-13-99 JZ         added PartContactHistoryFlag to StartPB */
/*    2.284     09-13-99 BEKymer    Removed PartContactHistoryFlag          */
/*    2.285     09-14-99 LAM        Removed unused MovementStopFlag         */
/*    2.286     09-15-99 BEKymer    Check pressure in pre-ready after 5 sec */
/*                                  and every 1/4 sec after that            */
/*    2.287     09-27-99 BEKymer    Remove call to SetPV(HOLD_TO_HOME) from */
/*                                  EnterReady().                           */
/*    2.288     10-08-99 BEKymer    Call UpdatePressureOffset() at power up */
/*    2.289     10-12-99 JZ         removed CountTheBits()                  */
/*    2.290     10-22-99 LAM        move updating pressure at power up from */
/*                                  testpreready to testpo3                 */
/*    2.291     10-25-99 BEKymer    Change velocity counts from 500 to 2000 */
/*    2.292     11-02-99 JZ         Moved CheckForSafety call from TestTrs2 */                                       
/*                                  to TestTrs2D                            */
/*    2.293     11-03-99 JZ         removed extra call to CheckForSafety    */
/*    2.294     11-04-99 JZ         removed unnecessary comments            */
/*    2.295     11-12-99 BEkymer    Added test code to use col cutoff value */
/*                                  to determine when to switch from Idle   */
/*                                  to downspeed control                    */
/*    2.296     11-19-99 BEKymer    Moved PRESSURE defines into ready.h     */
/*                                  Delayed switch from idle to downspeed   */
/*                                  until proper distance is reached.       */
/*    2.297     11-30-99 BEKymer    Added code in ExitUls() to ensure the   */
/*                                  switch from idle PV to downspeed occurs.*/
/*    2.298     12-07-99 LAM        only switch downspeed in exituls when   */
/*                                  welding                                 */ 
/*    2.299     12-16-99 LAM        removed unused references to profiling  */
/*    2.300     03-08-00 JZ         added check for model5 in TestReady     */
/*    2.301     04-20-00 JLH        Changed RecordErrorCode to always record*/
/*                                  AED Upgrade error (10xx).               */
/*    2.302     05-09-00 JLH        Changed AED Upgrade error test to use   */
/*                                   ERRORCODE1000_EQ20.  Changed to test   */
/*                                   ErrorCodeArg for this value.           */  
/*    2.303     05-09-00 JLH        Added extern enum ERRORCODE_ARG         */
/*                                   declaration for ErrorCode.             */
/*    2.304     05-26-00 SCM        Checked in for testing by Laura, John.  */
/*    2.305     06-27-00 SCM        Changed the variable name ActualTotalAbs*/
/*                                  in funcs. TestActClr() and              */
/*                                  ClearFinalResults().                    */
/*    2.306     06-28-00 SCM        Initialized ActualWeldAbs to zero in    */
/*                                  ClearFinalResults() function.           */
/*    2.307     06-28-00 BEKymer    changed MODEL to LEVEL &                */
/*                                  RejResetRequired to RejResetRequiredFlag*/
/*    2.308     07-13-00 BEKymer    Added code in RecordSetupAlarm and      */
/*                                  RecordAlarm to skip alarms which had    */
/*                                  their masks removed from the BUC menu.  */
/*    2.309     07-18-00 JLH        Added FreqChg and TestTime variables.   */
/*                                   Also added ETestPreReady function.     */
/*    2.310     07-21-00 BEKymer    In TestPreReady test for DUPS data by   */
/*                                   calling IsDUPSDataCollectionComplete() */
/*    2.311     08-01-00 BEKymer    In TestPreReady set DUPSOkFlag if not   */
/*                                   waiting for data from DUPS             */
/*    2.312     08-02-00 JLH        In TestPreReady do not progress to      */
/*                                   PoweredUp = TRUE if there is a wrong   */
/*                                   actuator alarm.                        */
/*    2.313     08-09-00 BEKymer    Call StartDUPSDataCollection() if there */
/*                                   is a pretrigger overload or test O/L.  */
/*                                  Remove ETestPreReady function           */
/*    2.314     08-15-00 JLH        Various changes to fix reset button issues */
/*    2.315     08-28-00 JLH        Updated ClearAlarm to use FinalResults instead of WeldingResults */
/*                                   for recalibrate actuator test.         */
/*    2.316     08-31-00 LAM        added clear errorcode to clearcalibration */
/*                                  alarms(Issue 3522)                      */
/*    2.317     09-20-00 LAM        fixed clearcalibration alarms(Issue 3562) */
/*    2.318     09-20-00 BEKymer    In EnterPTS clear DistFlag DCS # 3565   */
/*    2.319     09-25-00 BEKmer     Call StartDUPSData.. from RecordAlarm   */
/*                                   instead of from individual functions   */
/*    2.320     10-06-00 BEKymer    Reset ReadyAlreadySet flag when leaving */
/*                                   Preready state and ClearAbort function */  
/*                                   This was preventing ready from being   */
/*                                   set when abort was caused by           */
/*                                   communication with DUPS.               */
/*    2.321     10-30-00 BEKymer    In TestReady() wait for 3 bad system    */
/*                                   pressure check in a row before creating*/
/*                                   an alarm (Issue #3655 and 3663)        */
/*    2.322     10-31-00 BEKymer    In ClearAlarm() check both FinalResults */
/*                                   & WeldingResults for EQ20.  When alarm */
/*                                   occurs (in cycle, switching actuators) */
/*                                   will determine where bit is set.  This */
/*                                   is issue #3662.                        */
/*   2.323/4   11-02-00 LAM         fixed clearing equipment failure alarms*/
/*                                   in testpreready (Issues 3658 & 3662)   */
/*   2.325     11-14-00 BEKymer     Made test for system pressure take into */
/*                                   account LEVEL_TEST/LEVEL_f             */
/*   2.326     11-14-00 LAM         clear equipmentfailure print alarms in  */
/*                                  ClearAlarm when PrinterBufferReadyFlag = TRUE */
/*   2.327     04-11-01 BEKymer     Move POWERUPREADYDELAY to ready.h       */
/*   2.328     05-08-01 LAM         need to clear PresetHasBeenOKed in ready*/
/*                                  and wait for the weldmngr to set it     */                                                                        
/*   2.329     08-14-01 BEKymer     Set amplitude in EPreReady state.  This */
/*                                   gives HH a better chance to be at the  */
/*                                   right amplitude when sonics come on.   */
/*   2.330     04-08-02 BEKymer     Update cycle counter in BBR at end of   */
/*                                   cycle in case power removed without    */
/*                                   power switch                           */
/*   2.331     04-24-02 BEKymer     Fix address assigned to Setup Pointer   */
/*                                   in BBR (instead of CurrentSetup)       */
/*   2.332     04-25-02 LAM         Update alarm counters in BBR as they    */
/*                                  occur                                   */
/*   2.333     05-06-02 LAM         modified recorderrorcode                */
/*   2.235     02-14-03 BEKymer     No longer call ClrActOff in StartPB     */
/*                                  Remove calls to TestActClr since its    */
/*                                   always done in state machine now       */
/*   2.335     04-10-03 BEKymer     Move back to the tip as 2.335           */
/*   2.336     04-17-03 BEKymer     Condition ExitUlsUp with actuator type  */
/*                                   and if actuator clear is on            */
/*   2.337     07-07-03 BEKymer     In ClearFinalResults() set HoldForceMax */
/*                                   to zero to fix bug in 'Compuweld' data */
/*   2.333.3.1 07-10-03 JOY         Added PS Sotre flag 'QVGALatchPSStore'  */
/*                                  in 'TestPreReady()'&'TestTestPreReady()'*/
/*                                  this flag make sure that PS store status*/
/*                                  is displayed on the QVGA.               */
/*   2.338     07-25-03 LAM         merged 8.10 with TS01                   */
/*   2.339     02-20-04 VSharma     Modified ClearFinalResults() to intialize*/
/*                                   PresetNum & PresetName.                */
/*   2.340     03-12-04 VSharma     Changed 'Inp.ECycleAbort' to ECycleHistFlag.*/
/*   2.341     04-06-04 VSharma     Updated RecordAlarm(),SendFData(), ExitPB() */
/*                                  & SendFData() function for user configurable*/
/*                                  outputs.                                */
/*                                  Added EnterExtTrigDly,TestExtTrigDly,   */
/*                                   EnterSV & TestSVInput.                 */
/*   2.342     04-26-04 VSharma     Modified TriggerBeep().                 */
/*   2.343     04-27-04 VSharma     Modified ExitPB(). Added ExitSVState(). */
/*   2.344     05-11-04 VSharma     Added defines SV_INTERLOCK_TIMEOUT &    */
/*                                  EXT_TRGDELAY_TIMEOUT.                   */
/*   2.345     06-04-04 VSharma     Increment the ExtPresetWeldCounter and  */
/*                                   ExtSampleCount in SendFData().         */
/*   2.346     06-23-04 JOY         Removed CurrentSetup.ExtPresetWeldCount */
/*                                  From the SendFData().                   */
/*   2.347     08-02-04 BEKymer     Mask NC8 with ALARMMASK to strip off    */
/*                                   alarm type in RecordAlarm()            */
/*   2.348     08-18-04 JOY         Replaced SV_INTERLOCK_TIMEOUT with      */
/*                                   CurrentSetup.SVDelay                   */
/*   2.349     08-20-04 JOY         Trigger lost is checked in Ext. Trigger */
/*                                   Delay state.                           */
/*   2.350     08-24-04 JOY         Data type of variable 'QVGALatchPSStore'*/
/*                                   changed to UINT8.                      */
/*   2.351     08-26-04 JOY         Initialized WeldingResults.ActualTriggerDistance */
/*                                   in EnterExtTrigDly().                  */
/*   2.351.3.1 08-23-05 Aare        Total cycle time, incomplete.           */
/*   2.351.3.2 08-24-05 Aare        Implemented pretrigger delay code.      */
/*   2.351.3.3 08-26-05 Aare        Implemented reset encoder on ULS.       */
/*   2.351.3.4 09-10-05 Aare        Initialize SBL limit reached flags at the beginning of cycle. */
/*   2.351.3.5 09-12-05 Aare        Removed diagnostics code.               */
/*   2.351.3.6 09-12-05 Aare        Reworked the backwards polarity of flags for pretrigger. */
/*   2.351.3.8 09-12-05 Aare        Removed pretrigger delay code from weld states.  */
/*   2.351.3.9 10-16-05 Aare        Put pretrigger back in, trigger still doesn't work. */
/*   2.351.3.10 10-20-05 Aare       PretriggerDelay2 state - call velocity function, trigger works now. */
/*   2.352     10-20-05 Aare        Moved Ver10.0j back to tip.                */
/*   2.353     10-28-05 Bwadia      Sequence Nos incremented on cycle complete */
/*   2.354     11-02-05 Aare        Removed all changes for pretrigger         */
/*                                  delay, implemented pretrigger delay        */
/*                                  code in EnterPTS() and TestPTS()           */
/*                                  functions, still doesn't work.             */
/*                                  Branson testing: pretrigger delay works,   */
/*                                  pretrigger auto doesn't. Fixed in menu2.c  */
/*   2.355     11-02-05 Aare        Clear total cycle time in EnterULS().      */
/*   2.356     11-02-05 Aare        Use right variable for total cycle time.   */
/*   2.357     12-07-05 Bwadia      Global RAM weld counter for polling command*/
/*                                  Modified for tracker issue 4026, 4030      */
/*   2.358     01-10-06 LAM         modified zeroing the encoder               */                                                                         
/*   2.359     04-26-06 LAM         removed actuator clr alarm at ULS          */
/*   2.360     09-02-08 NHAhmed     CleanUp for multi-language support.        */
/*   2.361     09-04-08 YGupta      CleanUp for LangTest Project. 
/*   2.359.1.1.0.1 09-10-09 BEkymer Add new define MICRO where needed
/*   2.359.1.1.0.2 03-08-11 PDwivedi Added changes for USB Full alarm.  
/*   2.359.1.1.1.1.1.0 10-16-13     Hasanchez Added to the rutine TestPTS the function CheckCycleAborts()
/*									it to check if during the pretrigger the cycle should abort
/*									(Ground detected) 
/*   2.359.1.1.1.1.1.4 10-29-13     GButron  ExitReady() function changed: Frequency Offset is applied when No acctuator is attached -
                                    f, d, t, a, TEST, DEPOT, ea levels. ExitTrs2() function changed:  Frequency Offset is  
                                    applied when an actuator is attached.
     2.359.1.1.1.1.1.5 02-20-14     HSanchez The function ExitReady was updated to
     								improve the lines QTY and logic on it.
     2.359.1.1.1.1.1.6 08-25-17     Removed RejectFlag from OLG1, NCG1, EQG1, CMG1 and CAG1  
     2.359.1.1.1.1.1.5.1.2	 1/3/2018	Removed TestForDUPS, EnterForDUPS, ExitForDUPS Functions used for DUPS Update parameters 
										DEF01409 - Ramp time issue 
                                   
/*----------------------------- DESCRIPTION -------------------------------------*/

/* This module contains the code for the ready state, downstroke state and     */
/* the return to ready state.                                                  */
                                 
                                   
/*----------------------------- PSEUDO CODE -----------------------------------*/




/*---------------------------- LOCAL_EQUATES ----------------------------------*/


/*#define READY_UT                   For use as an aid in unit testing         */
//#define VELOCITY_DEBUG
//#define TRIGGER_FORCE_TEST        /* This allows the actual trigger force    */
                                  /* to be displayed as set trigger force &    */
                                  /* trigger distance to be displayed as       */
                                  /* the absolute distance (testing only)      */





#define VELOCITY_OFFSET       500 /* Back off from trigger this distance    */
#define VELOCITY_DISTANCE    1250 /* This is the distance over which we use */
#define VELOCITY_SAMPLE_RATE    1 /* How often (in ms) we sample distance   */
#define VELOCITY_POINTS      2000 /* The maximum number of collected points */
#define VELOCITY_MINIMUM       10 /* If any movement beyond VELOCITY_OFFSET */
                                  /* then this is minimum value 10=.00010"  */
#define MIN_POINTS              2 /* Minimum # of points needed for calc    */
#define VELOCITY_DIST_MIN     125 /* Movement before any readings are used  */
#define PARTCONTACTTIME      5000 /* Min time which part contact is checked */
#define PARTCONTACTDISTANCE     1 /* Distance which part contact is checked */
#define MAX_POS_INC           127 /* Max size for positive increment        */
#define MAX_NEG_INC          -127 /* Max size for negative increment        */

#define READYDELAYTIME         10 /* Time to delay actual ready output      */
                                  /* An attempt to fix 'Upper Limit Timeout'*/
#define PSRESETDELAY           10 /* Length of time PS reset remains active */
#define PTS_TIMEOUT         10000 /* Time in which pretrigger must start    */
#define TRIGGERBOUNCETIME      20 /* Time after ULS before checking trigger */
#define PASSES_BEFORE_FAILURE   2 /* How many times in ready a bad pressure */
                                  /* is accepted before an alarm is created */
//#define PRESSUREDELAY         500 /* How often in ready to read pressure    */
//#define PRESSUREOFFSET        300 /* Allowed pressure change before recal   */

#define EXT_TRGDELAY_TIMEOUT  30000

#define FilterIndex8 8
#define FilterIndex16 16
/*------------------------------ INCLUDES ----------------------------------*/

#include <psos.h>                /* psos defines and prototypes, etc,.  */
#include <string.h>
#include "names.h"
#include "error.h"
#include "state.h"
#include "menu.h"
#include "preset.h"
#include "beep.h"
#include "wldstate.h"
#include "weld_obj.h"
#include "alarms.h"
#include "statedrv.h"
#include "keypad.h"
#include "selctkey.h"
#include "util.h"
#include "weldhold.h"
#include "display.h"
#include "genalarm.h"
#include "menu4.h"
#include "alsetup.h"
#include "battram.h"
#include "menu1.h"
#include "graphs.h"
#include "menuhorn.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "encoder.h"     // jz added for VelocityEstimater()
#include "dups_api.h"
#include "psnvram.h"

/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

#include "ready.h"
#include "digout.h"
#include "statedrv.h"
#include "mansensr.h"
#include "led.h"
#include "timer.h"
#include "outports.h"
#include "inports.h"
#include "encoder.h"
#include "command.h"


#define MAX_HISTORY   2
SINT16  PartContactDistance[MAX_HISTORY];/*  Keep track of last MAX_HISTORY */
UINT16  C1= 0;                           /*  cycles for debugging           */



/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

static SINT32   VelocityTime;
static SINT32   FrequencyStart;
static SINT32   FirstDistance, TotalDistance;
static UINT16   RTAlreadySetFlag;
UINT16 TestTimerCounter, AlarmFlag;                        
UINT16 TestModeAllowed = TRUE;
UINT16 OkToDisplayAlarms;          /* TRUE:cycle is complete, display ok */
UINT16 SystemPressureCheck;      

SINT8  VelocityData[VELOCITY_POINTS][MAX_HISTORY];

#ifdef VELOCITY_DEBUG
UINT16 VelocityTrigger = 128;  /* For debugging, stop when velocity greater */
#endif

UINT16 NextValueIndex, PointCounter, SampleCount;
UINT16 StopSamplingFlag, StartSamplingFlag;
UINT16 NegVelocityCounter;

UINT16 ReadyDelay, ReadyAlreadySet;
UINT16 PSResetDelay, PBExitTimer, ULSExitTimer;
//UINT16 PressureReadDelay;

UINT16 SetupAlarmFlag;
//UINT16 DontPrintGraph;   /* Disable Print Now whenever cycle is aborted   */
UINT16 PrinterCheckTimer = 0;   /* Keep track of how often to check printer */
UINT16 PrinterTotalCount;
DFLOAT PrinterIncPoints;
DFLOAT PrinterNewInc;
UINT16 PrinterCopyPts;
UINT16 PTSFlag;                 /* TRUE:pre-trigger has started */

SINT32 FreqChg, TestTime;
SINT32 OldDistance;
SINT32 SaveTriggerDistance;
SINT32 PTSTimer;
//SINT32 LastPressureReading = -1;

SINT16 TriggerDelayTimer;
SINT16 PeakPower, PeakTestPower;
SINT32 PowerTest;
SINT32 OverloadFreq;           /* Value stored when pre-trigger O/L occurs */
SINT32 OverloadPower;          /* Value stored when pre-trigger O/L occurs */

UINT16 StaggerWatchDogTimer, ExternalCycleAbortGoneFlag;
UINT16 ResetReceivedFlag, UpperLimitTimer;
BOOLEAN ECycleHistFlag;

BOOLEAN JustPoweredUpFlag = TRUE;
BOOLEAN PoweredUp = FALSE;
BOOLEAN UlsTimeout;
BOOLEAN LatchPSRun, LatchPSSeek, LatchPSClear, LatchPSStore;

BOOLEAN MissingPartFlag = FALSE; //J.B
BOOLEAN TrgDelayTimeout,SVTimeout;
BOOLEAN SVInterlockActive;
UINT16 ExtTriggerDelayTimer,SVTimer;

static UINT32 BuffPwrTst[FilterIndex16]= {0}; //Power Buffer During Test
static UINT32 *ptst = &BuffPwrTst[0];
static UINT32 TestPwrSum=0;

SINT32 DistanceAtULS = IDLE_TO_DOWNSPEED_DISTANCE;  /* Start with a default value  */
SINT32 DistanceAtHome;
extern enum WELDSTATES WeldState;

UINT32  CurrentVelocity;
extern UINT8   RunScreenFlag;
extern enum ERRORCODE_ARG ErrorCode;
extern BOOLEAN DistFlag;
extern BOOLEAN ReadyFlag;
extern BOOLEAN SonicDisabledFlag;
extern SETUPS_Ver800  RunningPreset;
extern SETUPS_Ver800  MinLimit;
extern CONFIGSETUP CurrentSetup;
extern SINT32  EncoderPos;
extern SINT32  CurrentForce;
extern SINT32  AccumulatedEnergy, EnergyInJoules;
extern SINT32  CurrentFreqIn;        /* Value being read by 7890          */
extern SINT16  MenuCounter;
extern UINT16  PowerUpTimer;
extern UINT16  JustPoweredUpTimer;
extern UINT16  CycleTimer;
extern UINT16  EncoderFailTimer;
extern UINT16  PresetNeedsToBeUpdated;
extern UINT16  ActualABDelay;
extern UINT16  MaxForceDebounce;
extern UINT16  NewMaxForce;

extern UINT8   AlarmDetectedFlag;
extern UINT8   AETrigger;
extern UINT32  CurrentPowerIn;         /* Value being read by 7890          */
extern SINT32  ActualAfterburstTime;
extern SINT32  HomePressure;

extern SINT32  TriggerLostTime;/* Time (after 150ms) when trigger was declared lost */
extern SINT32  TriggerLostForce;/* Force when trigger was declared lost             */
extern SINT32  ActualTriggerForce;
extern SINT32  ExtSampleCount;
extern UINT16  PartContactFlag;
extern UINT16  PrinterBufferReadyFlag;
extern UINT16  PrintEveryCycleFlag;

extern BOOLEAN UpdateFlag;

extern BOOLEAN TriggerLostHistoryFlag, TriggerLostFlag;

static END_WELD_MSG end_weld_msg;
extern UINT32 WmgrQid;

WELD_DATA WeldingResults;
extern WELD_DATA FinalResults;
WELD_DATA *WeldingResultsPtr;
extern SETUP_DATA_ALARMS SetupData;
extern enum  WELD_SEQUENCE_TYPE CurrentSequence;

UINT16 ClearedHardwareAlarm = FALSE;
UINT16 AlarmCounter = 0;

extern UINT16 Update5ms;
extern UINT16 PresetHasBeenOKed;
extern UINT16 AdjustWeldSetupMenuFlag;

extern INBITS Inp;
//extern SINT8  *TestBuffer1[[MESSAGESIZE];
#define MAXTESTTIME 700  /* Max time sonics allowed on in test mode */
SINT16 TestCountDown = 250;

extern WELD_OBJECT *MsDataPtr;
extern ALARM_MASKS AlarmPtrRam;


extern PSNOVRAMDATA PSNvRamData;
extern BOOLEAN Actuator_Novram_Exist;


void SendKeyToWeldMngr(MSG_OPCODE_TYPE Opcode, BOOLEAN State);

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/

extern BOOLEAN CycleAbort;
extern BOOLEAN HornReturnFlag;
extern UINT8 QVGALatchPSStore;
UINT16 HornReturnCount = 0;
UINT16 TriggerBounceTimer;

UINT32 TotalCycleTime;
UINT32  PollingCommandCounter = 0;
BOOLEAN TotalCycleTimeAssigned;

SINT32 PretriggerDelayTimer;

BOOLEAN SBLMinLimitReached;
BOOLEAN SBLMaxLimitReached;

extern BIT_FLAGS BitFlags;

/*-------------------------- LOCAL FUNCTION PROTOTYPES ---------------------*/



/*-------------------------------- CODE ------------------------------------*/


#ifdef READY_UT

#include "..\ut\ready.ut"

#endif



void SetAlarmFlag(void)
{
   AlarmFlag = TRUE;
   SetGeneralAlarm();
   Beep(ALARMBEEP);
}   



void ClearAlarmFlag(void)
{
   AlarmFlag = FALSE;
}



UINT16 CheckAlarmFlag(void)
{
   return(AlarmFlag);
}   



void ClearAbort(void)
{
   AbortFlag = FALSE;
   ExternalCycleAbortGoneFlag = FALSE;
   PBExitTimer = 0;                    /* Reset palm button uls timer      */
   PBExitFlag = FALSE;                 /* Clear palm buttom home flag      */
   ULSExitTimer = 0;                   /* Reset upper limit timer          */
   ULSExitFlag = FALSE;                /* Clear upper limit home flag      */
   Inp.Trigger = FALSE;                /* Clear trigger from last cycle    */
   ReadyAlreadySet = FALSE;

}



void InitVelocityData(void)
/***************************************************************************/
/*                                                                         */
/*  This function will clear out the velocity array and all values in      */
/*  preparation for a new cycle.                                           */
/*                                                                         */
/***************************************************************************/
{
   PointCounter = 0;         /* Set number of points in buffer to zero     */
   NextValueIndex = 0;       /* Start putting points into index zero       */
   OldDistance = 0;          /* Make last distance reading zero            */
   SampleCount = 0;          /* Reset sample counter to zero               */
   StopSamplingFlag = FALSE; /* Dont stop sampling yet                     */
   StartSamplingFlag = FALSE;/* But dont start yet either,dist not reached */
   if (C1 >= (MAX_HISTORY - 1)) {
      C1 = 0;
   }
   else C1++;
   PartContactDistance[C1] = 0;
   NegVelocityCounter = 0;
}



void CollectVelocityData(SINT32 NewDistance)
/***************************************************************************/
/*                                                                         */
/*  This function will collect distance data in order to calculate the     */
/*  final velocity.  The velocity will be calculated by backing off from   */
/*  the trigger distance by a distance specified by the define VELOCITY_   */
/*  OFFSET.  It will be calculated over a distance defined by VELOCITY_    */
/*  DISTANCE.  Data will be collected at a rate set by the define VELOCITY_*/
/*  SAMPLE_RATE.  The maximum number of points which will be collected is  */
/*  defined by VELOCITY_POINTS.  VELOCITY_SAMPLE_RATE times VELOCITY_POINTS*/
/*  is the length of time (ms) which velocity will be calculated over.     */
/*  Points will be collected until one of two things happens:  Thing 1 -   */
/*  The distance traveled slowed down to less than PARTCONTACTDISTANCE     */
/*  over PARTCONTACTTIME.  Thing 2 - The current force is equal to or      */
/*  greater than the minimum trigger force.                                */
/*                                                                         */
/*  How this function works:                                               */
/*  ------------------------                                               */
/*                                                                         */
/*  A circular buffer will be used to save the data.  The data will be     */
/*  compressed into a UINT8.  Each data point will represent the difference*/
/*  in distance from this reading to the previous reading.  This means     */
/*  there are some limits: 1) between readings the distance can change no  */
/*  more then 0.0255", 2) the distance cannot go negative.                 */
/*                                                                         */
/*  The following variables will keep track of things:                     */
/*  NextValueIndex       Where in the array the next difference will go    */
/*  PointCounter         Number of points collected in buffer so far       */
/*  OldDistance          The reading from the last sample                  */
/*  SampleCount          How many ms since the last sample                 */
/*                                                                         */
/***************************************************************************/
{
   SINT16  TempDistance;
   UINT16  TempTime, TempIndex;

   if ((NewDistance >= VELOCITY_DIST_MIN) && /* Dont start until min dist reached */
       (NewDistance < 10000) ) {  /* Make sure distance is not negative  */
      StartSamplingFlag = TRUE;
   }
   if ((StopSamplingFlag == FALSE) && (StartSamplingFlag == TRUE) ) {
      SampleCount++;
      if (SampleCount >= VELOCITY_SAMPLE_RATE) {
         SampleCount = 0;
         TempDistance = (NewDistance - OldDistance);
         if (TempDistance > MAX_POS_INC) {
            TempDistance = MAX_POS_INC; /* Cant be bigger then a signed byte */
         }
         else if (TempDistance < MAX_NEG_INC) {
            TempDistance = MAX_NEG_INC;  /* Cant be smaller then a signed byte */
            NegVelocityCounter++;        /* Count # of times negative   */
         }
         VelocityData[NextValueIndex][C1] = (SINT8)(TempDistance);
         TempIndex = NextValueIndex;
         OldDistance += TempDistance;
   
         NextValueIndex++;
         if (NextValueIndex >= VELOCITY_POINTS) NextValueIndex = 0;
         else if (PointCounter < VELOCITY_POINTS) {
            PointCounter++;
         }
         TempTime = PARTCONTACTTIME;   
         TempDistance = 0;

/*--- Here we insure that at least enough points are collected to ---*/
/*--- represent PARTCONTACTTIME.                                  ---*/

         if (PointCounter >= (PARTCONTACTTIME / VELOCITY_SAMPLE_RATE)) {
            while (TempTime > VELOCITY_SAMPLE_RATE) {
               TempDistance += VelocityData[TempIndex][C1];
               TempTime -= VELOCITY_SAMPLE_RATE;
               if (TempIndex != 0) TempIndex--;
               else TempIndex = VELOCITY_POINTS - 1;
            }
            if (NewDistance > VELOCITY_OFFSET) {

/*--  If past upper limit switch and already collected minimum points  --*/

               if ((Inp.uls == FALSE) && (PointCounter >= MIN_POINTS)) {
                  if (PartContactFlag == TRUE) {

/*--------------------------------------------------------------------------*/
/*  This test for minimim trigger force was removed because it was causing  */
/*  the velocity to be inconsistant.  If the minimum trigger was ever       */
/*  reached on the downstroke (even for 1 ms) this would cause the part     */
/*  contact to be determined way before the part was really hit.  This meant*/
/*  the velocity would be calculated at different points in the stroke on   */
/*  different cycles.  This was decided in a meeting between Kevin Klein,   */
/*  Pete Dardis, Bob Baker, Laura Markure, Nick Wu and Barry Kymer on Nov.  */
/*  20, 1998 ( the day Bruce announced his resignation, and the day after   */
/*  Nick announced his).                                                    */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/

//                      (CurrentForce >= MinLimit.TriggerForce) ) {

                     StopSamplingFlag = TRUE;
                     PartContactDistance[C1] = NewDistance;
                  }
               }
            }
         }
      }
   }
   CurrentVelocity = VelocityEstimator(EncoderPos);          
}



SINT32 CalculateVelocity(void)
/***************************************************************************/
/*                                                                         */
/*  This function will do the actual velocity calculation using the data   */
/*  which was collected in CollectVelocityData.  It is assumed that when   */
/*  trigger has occurred the NextValueIndex will be pointing to the last   */
/*  collected piece of data.  From this point we need to go back for a     */
/*  distance of VELOCITY_OFFSET.  Here is our last data point.  From here, */
/*  go back another distance of VELOCITY_DISTANCE and where we find this   */
/*  value represents our total distance and time for velocity.             */
/*                                                                         */
/*  Two types of errors can be generated.  Error 1 means from VELOCITY_    */
/*  DIST_MIN to part contact (or trigger) there is less then VELOCITY_     */
/*  OFFSET distance.  Error 2 means from VELOCITY_DIST_MIN to part contact */
/*  (or trigger) there is less then VELOCITY_DISTANCE plus VELOCITY_OFFSET.*/
/*  Error 1 will result in a velocity of VELOCITY_MINIMUM.  Error 2 will   */
/*  result in a valid velocity for whatever distance the horn did travel.  */
/*                                                                         */
/***************************************************************************/
{
   SINT32  Distance = 0;
   SINT32  RetVelocity;
   UINT16  ExitFlag = FALSE;
   UINT16  Counter = 0;
   UINT16  TotalTimeValue = 1, LastTimeValue = 1;
   UINT16  ErrorFlag = 0;
   UINT16  ActualPointCounter = 0;


/*---  First determine if part contact was ever reached, or just trigger ---*/

   if (StopSamplingFlag == FALSE) {  /* If FALSE we never reached part contact */
      PartContactDistance[C1] = EncoderPos; /* Make current dist part contact  */
   }

/*---  First find out how much data to throw away (VELOCITY_OFFSET)      ---*/

   while (ExitFlag == FALSE) {
      if (NextValueIndex != 0) NextValueIndex--;
      else NextValueIndex = VELOCITY_POINTS - 1;
      Distance += VelocityData[NextValueIndex][C1];
      Counter++;
      if (Distance >= VELOCITY_OFFSET) {   /* We have enough offset now     */
         ExitFlag = TRUE;
      }
      if (Counter > PointCounter) {
         ErrorFlag = 1;                    /* Out of points, cycle must     */
         ExitFlag = TRUE;                  /* have been too short           */
      }
   }
   if (ErrorFlag == 0) {                   /* We have proper offset, so get */
      LastTimeValue = NextValueIndex;      /* final time value              */
/* check for divide by zero */
//      if(LastTimeValue == 0) LastTimeValue = 1;
      Distance = 0;


/*---  Now find where velocity calculation starts (VELOCITY_DISTANCE)    ---*/

      ExitFlag = FALSE;
      while (ExitFlag == FALSE) {
         if (NextValueIndex != 0) NextValueIndex--;
         else NextValueIndex = VELOCITY_POINTS - 1;
         Distance += VelocityData[NextValueIndex][C1];
         Counter++;
         ActualPointCounter++;
         if (Distance >= VELOCITY_DISTANCE) {
            ExitFlag = TRUE;               /* We have enough distance now   */
         }
         if (Counter > PointCounter) {
            ErrorFlag = 2;                 /* Out of points, cycle must     */
            ExitFlag = TRUE;               /* have been too short           */
         }
      }
   }

   Distance *= 10;       /* Multiply by 10 to get tenth's in final velocity */
   switch (ErrorFlag) {
      case 0:                      /* Normal cycle data is okay             */
         if ((ActualPointCounter < MIN_POINTS) || (PartContactDistance[C1] == 0) ) {
            RetVelocity = VELOCITY_MINIMUM;/* Error for now, not enough points */
         }
         else {
//            if (NextValueIndex < LastTimeValue)
//               TotalTimeValue = (LastTimeValue - NextValueIndex);
//            else
//               TotalTimeValue = VELOCITY_POINTS - (NextValueIndex - LastTimeValue);
      
//            RetVelocity = (Distance / (TotalTimeValue * VELOCITY_SAMPLE_RATE));
            RetVelocity = (Distance / (ActualPointCounter * VELOCITY_SAMPLE_RATE));
            if (RetVelocity < VELOCITY_MINIMUM) {
               RetVelocity = VELOCITY_MINIMUM;
            }
         }
         break;

      case 1:                      /* Cycle less then VELOCITY_OFFSET       */
         RetVelocity = VELOCITY_MINIMUM;
         break;

      case 2:                    /* Cycle < VELOCITY_DISTANCE, deal with it */
         if ((ActualPointCounter < MIN_POINTS) || (PartContactDistance[C1] == 0) ) {
            RetVelocity = VELOCITY_MINIMUM;/* Error for now, not enough points */
         }
         else {
//            if (NextValueIndex < LastTimeValue)
//               TotalTimeValue = (LastTimeValue - NextValueIndex);
//            else
//               TotalTimeValue = VELOCITY_POINTS - (NextValueIndex - LastTimeValue);
      
//            RetVelocity = (Distance / (TotalTimeValue * VELOCITY_SAMPLE_RATE));
            RetVelocity = (Distance / (ActualPointCounter * VELOCITY_SAMPLE_RATE));
            if (RetVelocity < VELOCITY_MINIMUM) {
               RetVelocity = VELOCITY_MINIMUM;
            }
         }
         break;

      default:
         break;
   }
#ifdef VELOCITY_DEBUG

   if (RetVelocity > VelocityTrigger) {
      while(1);
   }
#endif

   return( RetVelocity );
}



BOOLEAN CheckForMissingPartMax(void)
/***************************************************************************/
/*                                                                         */
/*  This function will first see if cycle aborts are on, then if missing   */
/*  part is on and finally if the missing part conditions exist.  If it    */
/*  is determined that the part is missing then a TRUE will be returned    */
/*  otherwise a FALSE will be returned.                                    */
/*                                                                         */
/***************************************************************************/
{
   BOOLEAN  Retval = FALSE;

   if ((RunningPreset.MissingMaxFlag == FALSE) &&
          (RunningPreset.MissingPartFlag == TRUE) &&
          (RunningPreset.CycleAbortFlag == TRUE) ) {
      if (EncoderPos > RunningPreset.MissingPartMax) {/* The horn has passed */
         Retval = TRUE;                               /* the allowed distance*/
      }
   }
   return(Retval);
}



BOOLEAN CheckForMissingPartMin(void)
/***************************************************************************/
/*                                                                         */
/*  This function will first see if cycle aborts are on, then if missing   */
/*  part is on and finally if the missing part conditions exist.  If it    */
/*  is determined that the part is missing then a TRUE will be returned    */
/*  otherwise a FALSE will be returned.                                    */
/*                                                                         */
/***************************************************************************/
{
   BOOLEAN  Retval = FALSE;

   if ((RunningPreset.MissingMinFlag == FALSE) &&
          (RunningPreset.MissingPartFlag == TRUE) &&
          (RunningPreset.CycleAbortFlag == TRUE) ) {
      if (WeldingResults.ActualTriggerDistance < RunningPreset.MissingPartMin) {
         Retval = TRUE;
      }
   }
   return(Retval);
}



void EnterReady(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just before entering the    */
/*  ready state.  It will do whatever good code should do before the       */
/*  ready state is entered.                                                */
/*                                                                         */
/***************************************************************************/
{
   OkToDisplayAlarms=TRUE;
   SystemPressureCheck = PRESSURE_CHECK_TIME1;
   ClearPressureArray();
   if (Inp.Estop == FALSE)
      CycleAbort = FALSE;
   TrigSwActv();                           /* safety circuit input            */
   PSIdle();
/*   SetReady();   */                      /* Output Welder Ready signal      */
//   ReadyDelay = 0;
   ReadyAlreadySet = FALSE;
   DistFlag = FALSE;                    /* Reset last cycle distance flag  */
   HornReturnFlag = TRUE;
   HornReturnCount = 0;
// ActClrFlag = FALSE;
// ActClrOff();                         /* Remove actuator clear output    */
//   PressureReadDelay = 0;
   PBReleaseOff();
   StopDataCollection();                /* Stop data collection in ready   */
   PowerUpTimer = 0;                    /* Reset just for horndown mode    */
   MissingPartFlag = FALSE;   // Clearing the flag after each cycle
   // MissingPartOff();
   RTAlreadySetFlag = FALSE;
   CoolValOff();                       // Turn Off Cooling Valve  
   ConfirmPresetOff();   //Make Confirm Preset output low
   if (!TotalCycleTimeAssigned)
      {
      FinalResults.TotalCycleTime = TotalCycleTime; 
      TotalCycleTimeAssigned = TRUE;
      }
}



void TestReady(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed every time the ready state  */
/*  is called.  This will make sure we should remain in ready.  System     */
/*  pressure will be checked.  An alarm will be generated if the pressure  */
/*  fails for 3 consecutive 1/4 second readings. Any one or two bad        */
/*  readings will be tossed out.  The logic here is that if the pressure   */
/*  is really bad it will be bad for at least 3/4 second.                  */
/*                                                                         */
/***************************************************************************/
{
   static UINT16 PassCounter = 0;

   if ((SystemPressureCheck--) <= 0 ) {
     SystemPressureCheck = PRESSURE_CHECK_TIME2;
     if ((CurrentSetup.Actuator == AEF) && (CurrentSetup.ControlLevel >= LEVEL_f)){
        UpdatePressureOffset();
        switch (CurrentPreset.SetPressure){
           case TRUE:       /* 80 PSI */
              if( ((HIGH_PRESSURE - PRESSURE_TOLLERANCE) > HomePressure) ||
                 ( (HIGH_PRESSURE + PRESSURE_TOLLERANCE)  < HomePressure)){
                 if (++PassCounter > PASSES_BEFORE_FAILURE) {
                    RecordAlarm(EQ25);
                 }
              }
              else PassCounter = 0;
              break;
           case FALSE:       /* 60 PSI */
              if( ((LOW_PRESSURE - PRESSURE_TOLLERANCE) > HomePressure) ||
                 ( ( LOW_PRESSURE + PRESSURE_TOLLERANCE)  < HomePressure)){
                 if (++PassCounter > PASSES_BEFORE_FAILURE) {
                    RecordAlarm(EQ25);
                 }
              }
              else PassCounter = 0;
              break;
        }
      }        
   }

   if (CheckIfResetRequired() == FALSE) {
      AlarmsReset = TRUE;
      TrigSwActv();                                  /* safety circuit input   */
   }
   if (ReadyAlreadySet == FALSE) {
      ReadyAlreadySet = TRUE;
      SetReady();
   }
   if (Inp.PSSeek == TRUE) {          /* Light the 0% led if external seek */
      UpdateLED(ZEROPERCENTLED,ON);
   }
   else {
      UpdateLED(ZEROPERCENTLED,OFF);
   }
}



void EnterTestReady(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just before entering the    */
/*  ready state.  It will do whatever good code should do before the       */
/*  ready state is entered.                                                */
/*                                                                         */
/***************************************************************************/
{
   if (Inp.Estop == FALSE)
      CycleAbort = FALSE;
   TrigSwActv();                           /* safety circuit input            */
   PSReset();                           /* Clear any overloads left over   */
   PSResetDelay = PSRESETDELAY;         /* Start delay to insure a reset   */
//   PSIdle();
/*   SetReady();     */                 /* Output Welder Ready signal      */
   DistFlag = FALSE;                    /* Reset last cycle distance flag  */
   HornReturnFlag = TRUE;
   HornReturnCount = 0;
// ActClrFlag = FALSE;
// ActClrOff();                         /* Remove actuator clear output    */
   asm(" ori.w #$80,$fffe18");          /* drive memstore output low */
   StopDataCollection();                /* Stop data collection in ready   */
   PowerUpTimer = 0;                    /* Reset just for horndown mode    */
}


void TestTestPreReady(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called whenever we are checking to see if we can      */
/*  enter the test ready state.                                            */
/*                                                                         */
/***************************************************************************/
{
   if (Inp.PSRun == TRUE)
      LatchPSRun = TRUE;

   if (Inp.PSSeek == TRUE)
      LatchPSSeek = TRUE;

   if (Inp.PSClear == TRUE)
      LatchPSClear = TRUE;

   if (Inp.PSStore == TRUE)
   {
      Inp.PSStore = FALSE;
      LatchPSStore = TRUE;
      QVGALatchPSStore = 2;
   }

   if (--TestCountDown <= 0) {
           TestCountDown = 250;
      
      if(QVGALatchPSStore) QVGALatchPSStore--;   

      SendFakeKeyPress(UPDATEDISPLAY);      /* Tell menu system to update   */
   }
   if (CheckIfResetRequired() == FALSE) AlarmsReset = TRUE;
}


void TestReadyTest(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will be executed every time the ready state   */
/*  is called while in the test weld sequence.                              */
/*                                                                          */
/****************************************************************************/
{
   if (CheckIfResetRequired() == FALSE) AlarmsReset = TRUE;

   if (Inp.PSRun == TRUE)
      LatchPSRun = TRUE;

   if (Inp.PSSeek == TRUE)
      LatchPSSeek = TRUE;

   if (Inp.PSClear == TRUE)
      LatchPSClear = TRUE;

   if (Inp.PSStore == TRUE)
   {
      Inp.PSStore = FALSE;
      LatchPSStore = TRUE;
      QVGALatchPSStore = 2;
   }

   if (--TestCountDown <= 0) {
      TestCountDown = 250;
      if(QVGALatchPSStore) QVGALatchPSStore--;
      SendFakeKeyPress(UPDATEDISPLAY);      /* Tell menu system to update   */
   }
}



void ExitReady(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will be executed just before leaving the      */
/*  ready state.  It will do whatever good code should do after the ready   */
/*  state is finished.                                                      */
/*  Output: WeldingResults.WeldPressure                                        */
/****************************************************************************/
{
   ClearAlarmFlag();
   if ((PresetNeedsToBeUpdated == FALSE) && (UpdateFlag == FALSE)) {
      ClearReady();                                                                   /* Remove Welder Ready signal          */
   }
// clear store & clear signals
   Inp.PSClear = FALSE;
   Inp.PSStore = FALSE;
   DistanceAtHome = EncoderPos;
   asm(" ori.w #$80,$fffe18");                                                        /* drive memstore output low           */
   ZeroEncoder();
   SonicsAbort = FALSE;                                                               /* Reset sonics abort flag             */
   AccumulatedEnergy = 0;                                                             /* Clear out last cycle energy         */
   EnergyInJoules = 0;
   PartContactFlag = FALSE;
   PeakPower = 0;
   DisplayWeldPower(PeakPower);                                                       /* Display last peak power reading     */
   ResetReceivedFlag = FALSE;                                                         /* Remove any sign of reset key        */
   if (ExternalCycleAbortGoneFlag == TRUE) {
      ECycleHistFlag = FALSE;
   }
   InitVelocityData();                                                                /* Prepare velocity variables          */
   WeldingResults.WeldPressure = (UINT16) HomePressure;
   CurrentPreset.GaugePressure = (UINT16) HomePressure;
   PresetHasBeenOKed = FALSE;                                                         /* Will not allow the state machine to advance passed the */
                                                                                      /* PB state until the WeldManger completes its part       */
   TotalCycleTime = 0;
   TotalCycleTimeAssigned = FALSE;
   FinalResults.CycleTimeResult = 0;

         
 

   if(RunningPreset.FreqOffsetFlag == TRUE)                                        /*HSan update to improving the size of file and logic of it*/
   {
       		SetCurrentFreqOffset(RunningPreset.FreqOffset);                           /* Enable Frequency offset */ 
   
   }
}



void ExitReadyTest(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will be executed just before leaving the      */
/*  ready state on the way to sonics on in the test mode.                   */
/*                                                                          */
/****************************************************************************/
{
//   ClearFinalResults();
   ClearReady();                     /* Remove Welder Ready signal          */
   SonicsAbort = FALSE;              /* Reset sonics abort flag             */
   AccumulatedEnergy = 0;            /* Clear out last cycle energy         */
   ResetReceivedFlag = FALSE;        /* Remove any sign of reset key        */
}



void StartPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when one palm button has    */
/*  been pressed. It will do whatever good code should do after just one   */
/*  palm button has been pressed.                                          */
/*                                                                         */
/***************************************************************************/
{
   PSReset();                          /* Reset power supply before we go  */
   AlarmCounter = 0;
//   ClearFinalResults();
   OkToDisplayAlarms = FALSE;

   Init1msPts();

   if ( (RunScreenFlag == TRUE) &&
      (MenuCounter > 1) &&
      (CurrentSequence != HORNDOWN) &&
      (AdjustWeldSetupMenuFlag == FALSE) )
   {
      SendFakeKeyPress(RunKey);        /* Return to Run Screen from alarms */
   }

/*----- Clean up trigger stuff from last cycle -----*/

   TriggerLostHistoryFlag = FALSE;
   TriggerLostTime = 0;
   TriggerLostForce = 0;
   PartContactFlag = FALSE;
   MaxForceDebounce = 0;
   NewMaxForce = 0;
   StaggerFlag = FALSE;
   StaggerWatchDogTimer = 0;
   ResetUpTimer(SONICSTIMER);
   UlsTimeout = FALSE;                  /* Clear Uls Timeout Flag           */
   UpperLimitTimer = 0;                 /* Reset timer to zero              */
   OKToAdvance = FALSE;
   ActualAfterburstTime = 0;            /* Clear for seek end time          */
   ActualABDelay = 0;                   /* Clear for seek end time          */
   ActClrFlag = FALSE;
   SonicDisabledFlag = FALSE;
//   ActClrOff();                         /* Remove actuator clear output    */
}



void TestPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed between the time one palm   */
/*  is pressed and before two palm buttons are pressed.  It will be a      */
/*  watchdog on the stagger time.                                          */
/*                                                                         */
/***************************************************************************/
{
   if (++StaggerWatchDogTimer > PALMBUTTON_STAGGER_TIME) {
      StaggerFlag = TRUE;
   }
 
   if (PresetHasBeenOKed == TRUE) {
      if (ReadyFlag == TRUE) ClearReady();   /* Remove Welder Ready signal */
         if (Inp.BothPB == TRUE) {
            OKToAdvance = TRUE;
            ClearSetupAlarms();   /* This will clear Printer Offline alarm */
            ClearFinalResults();
         }
   }

/*---   This code to deal with horn down mode   ---*/

   if ((CurrentSequence == HORNDOWN) && (Inp.BothPB == TRUE)) {
      OKToAdvance = TRUE;
   }
}



void ExitPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when both palm buttons have */
/*  been pressed.  It will do whatever good code should do after both      */
/*  palm buttons have been pressed.                                        */
/*                                                                         */
/***************************************************************************/
{
/*----- Test to see if Rapid Traverse is on -----*/
//UINT16 temp1;

//   if ((StepAtRTDist.BitMask & RunningPreset.RTFlag) == StepAtRTDist.BitMask)
//   {
//      temp1 = RunningPreset.DownSpdStart + RunningPreset.SetRTComp;
//      if (temp1 > 100)
//         temp1 = 100;
//      SetPV(temp1, HOME_TO_RT);       
//   }
//   else
//      SetPV((UINT16)RunningPreset.DownSpdStart, HOME_TO_DWNSPD);    
   if (PrinterTotalCount == 0) GetPtsIncrement();
   MsDataPtr->TotalPts = PrinterTotalCount;
   MsDataPtr->IncrementPts = PrinterIncPoints;
   MsDataPtr->CopyPts = PrinterCopyPts;
   MsDataPtr->NewInc = PrinterNewInc;
   
   if(!IsConfigured(INPUT_SV_INTERLOCK) && 
      !IsOutConfigured(OUTPUT_SV_INTERLOCK))
   {
      SVInterlockActive = FALSE;
      EnableSVOn();                        /* Enable SV valve                 */
      SVOn();                              /* Turn on SV to bring down hown   */
   }      
   else SVInterlockActive = TRUE;
   
   if ((RunningPreset.PreTrigFlag & BIT0) == BIT0) { /* If PTS, set PT amp */
      SetCurrentAmp(RunningPreset.PreTrigAmp);    /* Pretrigger amplitude  */
   }
   else {
      SetCurrentAmp(RunningPreset.Amp1);/* Prepare P/S for 1st amplitude   */
   }

/* Here decide if extra cooling is needed  */

   if (CurrentSetup.ExtraCooling == TRUE) {
      CoolValOn();
   }
   UserCfgOutputOff(OUTPUT_CYCLE_OK);   //Make Cycle Okay output low             
   ConfirmPresetOn();//Make Confirm Preset output high if preset changed.   
   if(Inp.SonicDisable)
      SonicDisabledFlag = TRUE;
/*   AccumulatedEnergy = 0;   */          /* Clear out last cycle energy     */
   EncoderFailTimer = 0;                /* Clear encoder check timer       */
   OKToAdvance = FALSE;
   ErrorCodeFlag = FALSE;
   ErrorCode = 0;
}



void TriggerBeep(void)
/***************************************************************************/
/*                                                                         */
/*  This function will unconditionally sound the trigger beeper one time.  */
/*                                                                         */
/***************************************************************************/
{
   Beep(TRIGGERBEEP);
   SaveTriggerDistance = EncoderPos;
   PBReleaseOn();
}
   


void AlarmExitPB(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when the palm button        */
/*  state must be exited because of some type of an alarm.                 */
/*                                                                         */
/***************************************************************************/
{
   CycleAbort = TRUE;
}



void EntryTrs1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just before waiting for     */
/*  trigger.                                                               */
/*                                                                         */
/***************************************************************************/
{
   StartUpTimer(VELOCITYTIMER);        /* Start timer for velocity calc    */
   FirstDistance = EncoderPos;         /* Save position for velocity calc  */
}



void EntryTrs2(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed after distflag.             */
/*  Needs to be called after TRS this is for alpha A only.                 */
/***************************************************************************/
{
// logic problem with triggerdelayflag
// if((TriggerDelay.BitMask & RunningPreset.TriggerDelayFlag)
//       == TriggerDelay.BitMask){
//      if (RunningPreset.TriggerDelay != 0) {
//         TriggerDelayTimer = StartTimer((SINT32)RunningPreset.TriggerDelay, &TriggerDelayFlag, 18);
//         if ((TriggerDelayTimer == FAILED1) || (TriggerDelayTimer == FAILED2)){
//            LogError(TIMERFAILED1);
//            TriggerDelayTimer = 0;
//            TriggerDelayFlag = TRUE;
//         }
//      }
//   }
//   else
   TriggerDelayFlag = TRUE;
}



void ExitULS(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just after the upper limit  */
/*  switch is cleared indicating the horn has left the home position.      */
/*                                                                         */
/***************************************************************************/
{
   UINT16 temp1;

   StartUpTimer(CYCLETIMER);           /* Start timer for the fun of if    */
   OKToAdvance = FALSE;                /* Clear so Final Data State can use*/
   OldDistance = EncoderPos;           /* Make last distance=current pos   */
   DistanceAtULS = EncoderPos;

/**    This section of code is executed in case the upper limit switch   **/
/**    was reached before the idle to downspeed distance was reached.    **/
   if (CurrentSequence == WELD)  /* If WELD only go to downspeed */
   {
      if ((/*StepAtRTDist.BitMask*/BIT0 & RunningPreset.RTFlag) == /*StepAtRTDist.BitMask*/BIT0)
      {
         temp1 = RunningPreset.DownSpdStart + RunningPreset.SetRTComp;
         if (temp1 > 100)
            temp1 = 100;
         SetPV(temp1, HOME_TO_RT);       
      }
      else
         SetPV((UINT16)RunningPreset.DownSpdStart, HOME_TO_DWNSPD);    
   } 
   if (CurrentSetup.DistanceULS)
      ZeroEncoder();
   SBLMinLimitReached = FALSE;
   SBLMaxLimitReached = FALSE;
}

void ExitULS1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just after the upper limit  */
/*  switch is active on the upstroke, indicating the horn has just returned*/
/*  home.  A test of door open is done here, but we are actually checking  */
/*  for trigger.  Once uls is active door open is used instead of trigger. */
/*                                                                         */
/*    60.2.120 08-01-97  BEKymer    Check for EQ4 in ExitULS1              */
/*                                                                         */
/***************************************************************************/
{
   if (Inp.DoorOpen == TRUE) {         /* Start timer for velocity calc    */
      RecordAlarm(EQ4);
   }
}



void ExitTrs1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed just after the first        */
/*  downspeed (pressure) value.                                            */
/*                                                                         */
/***************************************************************************/
{

}


void ExitTrs2(void)
/*****************************************************************************/
/*                                                                           */
/*  This is the function that will be executed just after the second         */
/*  downspeed (pressure) value.  This function "will set up" the first weld  */
/*  force.                                                                   */
/*      It is logical to conclude that will be executed just Before          */
/*      The first weld force, and consequently, Before the Sonics            */
/*      Is enabled.                                                          */
/*                                                                           */
/*****************************************************************************/
{
   WeldingResults.ActualVelocity = CalculateVelocity();
   
      if(RunningPreset.FreqOffsetFlag == TRUE)                  /* Frequency offset is enabled Just Before the sonics is applied */                            
         SetCurrentFreqOffset(RunningPreset.FreqOffset);        
}


void ExitUlsUp(void)
/***************************************************************************/
/*  This is the function that will be executed when the "wait for upper    */
/*  limit to clear" state has finished.                                    */
/*                                                                         */
/***************************************************************************/
{
   OKToAdvance = FALSE;
         
/*--  Use ActualDistance or ActualTriggerDistance which ever is larger  --*/

   if (RunningPreset.ActClrFlag == TRUE) { /* Actuator Clear function is ON */
      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (WeldingResults.ActualTotalAbs > WeldingResults.ActualTriggerDistance) {
            if (RunningPreset.ActClrDistance > WeldingResults.ActualTotalAbs) { 
               RecordAlarm(W1);
            }
         }
         else {
            if (RunningPreset.ActClrDistance > WeldingResults.ActualTriggerDistance) {
               RecordAlarm(W1);
            }
         }
     }
  }
}




void AlarmUls(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when an alarm has forced    */
/*  the "wait for upper limit to clear" state to abort.                    */
/*                                                                         */
/***************************************************************************/
{
   SVOff();                             /* Turn off SV to bring down hown  */
   CycleAbort = TRUE;
   OKToAdvance = FALSE;
}



void AlarmTrs1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will be executed when an alarm has forced    */
/*  the trigger state to abort.                                            */
/*                                                                         */
/***************************************************************************/
{
   SVOff();                             /* Turn off SV to bring down hown  */
   CycleAbort = TRUE;
}



void TestPreReady(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called whenever we are checking to see if we can      */
/*  enter the ready state.  It will clear the ECycleAbort flag if the      */
/*  ExternalCycleAbortGoneFlag is TRUE (which is set in Inports.c).        */
/*                                                                         */
/*  The JustPoweredUpFlag delays the Ready signal until we think the front */
/*  panel has displayed the Run screen.                                    */
/*                                                                         */
/***************************************************************************/
{
   if ((SystemPressureCheck--) <= 0 ) {
      SystemPressureCheck = PRESSURE_CHECK_TIME2;
      if (CurrentSetup.Actuator == AEF){
         UpdatePressureOffset();
      }
   }      
   if (Inp.OnePB == TRUE) {
      PBExitTimer++;                   /* Count time until pb's released    */
      if (PBExitTimer > PBEXITTIME) {
         PBExitFlag = TRUE;            /* Took too long, generate alarm     */
      }
   }
   else
      PBExitFlag = FALSE;            /* clear alarm incase it was set    */

   if (Inp.uls == FALSE) {           /* If still not home, then wait a bit  */
      ULSExitTimer++;                /* Count until horn is home            */
      if (ULSExitTimer > UPPERLIMIT_TIMEOUT) {
         ULSExitFlag = TRUE;
      }
   }
   else {
      ULSExitFlag = FALSE;
   }

   if (ExternalCycleAbortGoneFlag == TRUE) {
      ECycleHistFlag = FALSE;    /* Clear external cycle abort in case it got set */
   }
//   if (CheckIfResetRequired() == FALSE) AlarmsReset = TRUE;
   if (JustPoweredUpFlag == TRUE) {
      if (JustPoweredUpTimer >= POWERUPREADYDELAY) {

         if((WeldingResults.EquipmentFailureAlarms & WRONG_ACTUATOR_FAIL) !=
            WRONG_ACTUATOR_FAIL){
               PoweredUp = TRUE;
               JustPoweredUpFlag = FALSE;
               
            }   
      }
      else {
         JustPoweredUpTimer++;
      }
   }
   if ( (++PrinterCheckTimer >= PRINTERCHECKTIME) &&
        (CheckPrintingStatus() == TRUE) ) {
      PrinterCheckTimer = 0;                /* Reset timer */
      if (OfflineCheckFunc() == TRUE) {
         RecordSetupAlarm(SE270);
      }
   }
   if(USBFullCheckFunc() == TRUE)
      RecordAlarm(EQ13);
   if (CheckIfResetRequired() == FALSE) AlarmsReset = TRUE;
   if (IsDUPSDataCollectionComplete() == FALSE) {
      DUPSOkFlag = FALSE;             /* FALSE:waiting for DUPS data */
   }
   else {
      DUPSOkFlag = TRUE;              /* TRUE:not waiting for DUPS data */
   }
   OkToDisplayAlarms=TRUE;    /* At this point allow alarms to be displayed */
}



void EPreReady(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called whenever we are ready to enter the ready state.*/
/*  One of the things it will do it check for any alarms generated on this */
/*  weld cycle.                                                            */
/*                                                                         */
/***************************************************************************/
{
   SystemPressureCheck = PRESSURE_CHECK_TIME1;
   ClearPressureArray();
   CoolValOff();                       // Turn Off Cooling Valve  
   SVOff();                            /* Turn off SV to bring down hown   */
   OkToDisplayAlarms = TRUE;           /* Allow alarms to be displayed     */
   PrinterCheckTimer = 0;              /* Reset printer 5 second timer     */
   Inp.Trigger = FALSE;
   ReadyAlreadySet = FALSE;
   SetCurrentAmp(RunningPreset.Amp1);  /* Initial amplitude                */
//   FinalResults.TotalCycleTime = 0;
}



void EnterPTS(void)
/****************************************************************************/
/*                                                                          */
/*  This function will be executed when the pretrigger state is entered.    */
/*  It will clear the timer and timer flag.                                 */
/*                                                                          */
/****************************************************************************/
{
   PTSTimerFlag = FALSE;              /* TRUE means pretigger took too long */
   PTSTimer = 0;                      /* Clear time value                   */
   PTSFlag = FALSE;                   /* Indicate pretrigger has not started yet */
   DistFlag = FALSE;                  /* Clear in case R/T already set it   */
   PretriggerDelayTimer = 0;          /* Clear the timer, will be updated in TestPTS() */
}


void TestPTS(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for pre-trigger. */
/*  It will test the current distance and when the proper distance is      */
/*  reached the DistFlag will be set TRUE.                                 */
/*                                                                         */
/***************************************************************************/
{
   PTSTimer++;                        /* Count how long it's taking         */
   if (PTSTimer > PTS_TIMEOUT) {      /* If too long set flag to abort      */
      PTSTimerFlag = TRUE;
   }
   if(RunningPreset.AutoTrigFlag)
      DistFlag = TRUE;
   else if (!RunningPreset.PreTrigDistFlag) {
      if (EncoderPos >= RunningPreset.PreTrigDist)
         DistFlag = TRUE;
   }
   else if (!RunningPreset.PreTrigDelayFlag) {
      PretriggerDelayTimer++;
      if (PretriggerDelayTimer >= RunningPreset.PreTrigDelay)
         DistFlag = TRUE;
   }
   MissingPartFlag = CheckForMissingPartMax();
   CollectVelocityData(EncoderPos);
   CheckCycleAborts();
}



void StartPTS(void)
/***************************************************************************/
/*                                                                         */
/*  This function will start the sonics when executed.  The WeldOn external*/
/*  signal will not be activated at this time because there is no trigger  */
/*  condition (i.e. force on the part).                                    */
/*                                                                         */
/***************************************************************************/
{
   SetCurrentAmp(RunningPreset.PreTrigAmp);       /* Pretrigger amplitude  */
   PSRun();                                       /* Start sonics          */
   PTSTimer = 0;            /* Clear time value, now used for @Time for O/L*/
   DistFlag = FALSE;        /* Clear flag in case downspeed stepping is on */
   PTSFlag = TRUE;          /* Indicate pre-trigger has in fact started    */
}



void TestForOverload(void)
/***************************************************************************/
/*                                                                         */
/* This function check for overload while pre-trigger is on.  It will keep */
/* track of peak power an record the frequency when an overload occurs.    */
/*                                                                         */
/***************************************************************************/
{
   PTSTimer++;
   if (CurrentPowerIn > OverloadPower) {
      OverloadPower = CurrentPowerIn;
   }
   if (Inp.OL == TRUE) {            /* If overload detected save frequency */
      OverloadFreq = CurrentFreqIn;
   }
}



void TestTrs1D(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for trigger.  It */
/*  will test for such things as second downspeed.                         */
/*                                                                         */
/***************************************************************************/
{
   if (PTSFlag == TRUE) TestForOverload();

   if ((RunningPreset.RTFlag & BIT0) == BIT0) {

      if((EncoderPos  >= RunningPreset.RTDist) && (PartContactFlag == FALSE)
         && (RTAlreadySetFlag == FALSE)){
         SetPV((UINT16)RunningPreset.DownSpdStart, RT_TO_DWNSPD);
         DistFlag = TRUE;
         RTAlreadySetFlag = TRUE;

      }
   }      
   else DistFlag = TRUE;
   if (Inp.Trigger == TRUE) {
      DistFlag=TRUE;
   }
   CheckControlLimitsD(TRUE);
   CheckCycleAborts();
   CollectVelocityData(EncoderPos);

    // Missing Part => Max ="on" AND values are enabled.
   
   MissingPartFlag = CheckForMissingPartMax();
}



void TestTrs1(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for trigger.  It */
/*  will test for such things as second downspeed.                         */
/*                                                                         */
/***************************************************************************/
{
// need to add code when rapid traverse added
   if (Inp.Trigger == TRUE) {
      DistFlag=TRUE;
   }
   if (PTSFlag == TRUE) TestForOverload();

   CheckControlLimits();
   CheckCycleAborts();
}



void TestTrs2D(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for trigger      */
/*  after the second downspeed has gone into effect.  It will wait for     */
/*  only trigger.                                                          */
/*                                                                         */
/***************************************************************************/
{
   if (PTSFlag == TRUE) TestForOverload();

   CheckControlLimitsD(TRUE);
   CheckCycleAborts();
   CollectVelocityData(EncoderPos);
   if (PartContactFlag == TRUE ) {
       CheckForSafety();
       UpdateDistanceOffset();
       SetPV((UINT16)RunningPreset.WeldForce, TRG_TO_FORCE_A);
   }
   // Missing Part => Max ="on"  And value are enabled
   
   MissingPartFlag = CheckForMissingPartMax();
   
}



void TestTrs2(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for trigger      */
/*  after the second downspeed has gone into effect.  It will wait for     */
/*  only trigger.                                                          */
/*                                                                         */
/***************************************************************************/
{
   if (PTSFlag == TRUE) TestForOverload();

   CheckControlLimits();
   CheckCycleAborts();
}



void EnterUls(void)
/****************************************************************************/
/*                                                                          */
/*   This function will be executed when the upstroke is started.  It will  */
/*   check to see if actuator clear output is enabled.  If not enabled,     */
/*   ActClrFlag will be set allowing the state to end.  If actuator clear   */
/*   output is enabled, TestUlsUp will test the distance and when the       */
/*   actuator is high enough the ActClrFlag will be set, again allowing the */
/*   state to end.                                                          */
/*                                                                          */
/****************************************************************************/
{
   UlsTimeout = FALSE;                  /* Clear Uls Timeout Flag           */
   UpperLimitTimer = 0;                 /* Reset timer to zero              */
   PretriggerDelayTimer = 0;
   TotalCycleTime = 0;                  /* reset total cycle time           */
}



void TestUls(void)
{
   UINT16 temp1;
   
   if (Inp.uls == FALSE){
      HornReturnCount++;
      if(HornReturnCount > UPPERLIMIT_TIMEOUT)
         HornReturnFlag = FALSE;
   }
   if (UpperLimitTimer++ > UPPERLIMIT_TIMEOUT) {
      UlsTimeout = TRUE;

/*---  If we timed out lets assume something went wrong somewhere, so    ---*/
/*---  lets reset everything and reselect the weld sequence to recover.  ---*/

      TrigSwActv();                  /* safety circuit input       */
      if ((GetCurrentSequenceType() != HORNDOWN) && (HornDownFlag == FALSE)){
          SelectWeldSequence();      /* Try redoing weld sequence  */
          StartStateMachine();
      }
   }
   CollectVelocityData(EncoderPos);  /* Collect data BEFORE we clear ULS  */



//   if (EncoderPos >= IDLE_TO_DOWNSPEED_DISTANCE) {
//   if (EncoderPos >= (DistanceAtULS - DOWNSPEED_DISTANCE_OFFSET)) {     /* Test for last cycle distance to ULS */
//      WeldingResults.ActualTotalCollapse = (DistanceAtULS - DOWNSPEED_DISTANCE_OFFSET);
//      if ((StepAtRTDist.BitMask & RunningPreset.RTFlag) == StepAtRTDist.BitMask)
//      {
//         temp1 = RunningPreset.DownSpdStart + RunningPreset.SetRTComp;
//         if (temp1 > 100)
//            temp1 = 100;
//         SetPV(temp1, HOME_TO_RT);       
//      }
//      else
//         SetPV((UINT16)RunningPreset.DownSpdStart, HOME_TO_DWNSPD);    
//   }

/*  End of temp test code */
}


void EnterUlsUp(void)
/***************************************************************************/
/*                                                                         */
/*  This function will initialize the variables which will be used in Test */
/*  UlsUp.                                                                 */
/*                                                                         */
/***************************************************************************/
{
   TriggerBounceTimer = 0;
   OKToAdvance = FALSE;
}



void TestUlsUp(void)
/****************************************************************************/
/*                                                                          */
/*  This function will be executed every ms while in the upstroke.  It      */
/*  check to see if actuator clear distance has been reached or if home     */
/*  has been reached.  If either of these cases happen the ActClrFlag       */
/*  will be set allowing the state to end.                                  */
/*  It will wait TRIGGERBOUNCETIME after Inp.uls is TRUE.  If               */
/*  trigger is gone, then the state will exit, otherwise an EQ4 alarm will  */
/*  result.                                                                 */
/*                                                                          */
/****************************************************************************/
{
//   TestActClr();
   if (Inp.uls == FALSE) {
      if (++HornReturnCount > UPPERLIMIT_TIMEOUT) {
         HornReturnFlag = FALSE;
      }
   }
   else{
// make sure AE actuator with trigger switch
      if (CurrentSetup.Actuator == AE) {
         if (++TriggerBounceTimer > TRIGGERBOUNCETIME) {
            Inp.Trigger = FALSE;
            OKToAdvance = TRUE;
         }
      }
      else {
         OKToAdvance = TRUE;
      }
   }
}



void RecordAlarm(UINT32 AlarmCode)
/****************************************************************************/
/*                                                                          */
/*  This function will take the passed AlarmCode and set the proper bit in  */
/*  the FinalResults structure.  If needed it will also output the reject,  */
/*  suspect or system fault signals.  The UpdateAlarm function will be      */
/*  called in case the run screen is being displayed.  This will ensure     */
/*  alarm will get displayed immediately.  If the alarm bit is already set  */
/*  the UpdateDisplay function will NOT be called to prevent pSOS from      */
/*  getting backed up.                                                      */
/*                                                                          */
/****************************************************************************/
{
   UINT32  AlarmType;
   UINT16  RejectFlag = FALSE, SuspectFlag = FALSE;
   UINT16  NotReadyFlag = FALSE, WarningFlag = FALSE;
   UINT16  OverloadFlag = FALSE, NoCycleFlag = FALSE;
   UINT16  MissingPartOut = FALSE, ModifiedFlag = FALSE;
   UINT16  UpdatedDisplayFlag;
   CONFIGSETUP  *SetupPtr;

   SetupPtr = (CONFIGSETUP *) BBR800_CONFIG_START;

   if (AlarmCounter < (MAXSUBMENUS - 1) ) {
      ResetReceivedFlag = FALSE;        /* Remove evidence of reset pressed */
      UpdatedDisplayFlag = FALSE;
      AlarmType = (AlarmCode & ALARMTYPEMASK);   /* Get what type of alarm     */
      AlarmCode = (AlarmCode & ALARMCODEMASK);   /* Strip off type of alarm    */
      switch (AlarmType) {
         case PSG1:                              /* Process Suspect Alarms     */
            if ((AlarmPtrRam.Suspect & AlarmCode) == AlarmCode) {
               if ((WeldingResults.SuspectBitResult & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                     /* Count bits set in AlarmCode and NOT in WeldingResults */

                  WeldingResults.SuspectBitResult |= AlarmCode;
                  SuspectFlag = TRUE;
               }
            }
            else
               UpdatedDisplayFlag = TRUE;
            break;
   
         case PRG1:                              /* Process Reject Alarms      */
            if ((AlarmPtrRam.Reject & AlarmCode) == AlarmCode) {
               if ((WeldingResults.RejectBitResult & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                     /* Count bits set in AlarmCode and NOT in WeldingResults */

                  WeldingResults.RejectBitResult |= AlarmCode;
                  RejectFlag = TRUE;
               }
            }
            else
               UpdatedDisplayFlag = TRUE;
            break;
   
         case OLG1:                              /* Overload Alarms - Group 1  */
            if ((AlarmPtrRam.Overload & AlarmCode) == AlarmCode) {
               if ((WeldingResults.OverloadAlarms & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  StartDUPSDataCollection();       /* All O/L's attempt to get data from DUPS */
                  WeldingResults.OverloadAlarms |= AlarmCode;
                  OverloadFlag = TRUE;
                  if (AlarmCode & OL_INC_COUNTER){  /* Increment counter if necessary */
                     CurrentSetup.Overload++;
                     SetupPtr->Overload = CurrentSetup.Overload;  /* Update BBR */
                  }   
                  if ((OL_CYCLE_ABORT & AlarmCode) != FALSE) CycleAbort = TRUE;
                  SonicsAbort = TRUE;
               }
            }
            else
               UpdatedDisplayFlag = TRUE;
            break;
   
         case NCG1:                              /* No Cycle Alarms - Group 1  */
            if ((AlarmPtrRam.NoCycle & AlarmCode) == AlarmCode) {
               if ((WeldingResults.NoCycleAlarms & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  WeldingResults.NoCycleAlarms |= AlarmCode;
                  NoCycleFlag = TRUE;
                  if(AlarmCode == (NC8 & ALARMCODEMASK) )
                     MissingPartOut = TRUE;
                  CycleAbort = TRUE;
                  AbortFlag = TRUE;
               }
            }
            else
               UpdatedDisplayFlag = TRUE;
            break;
   
         case EQG1:                              /* Equipment Failure Alarms   */
            if ((AlarmPtrRam.EquipmentFailure & AlarmCode) == AlarmCode) {
               if ( ((FinalResults.EquipmentFailureAlarms & AlarmCode) == AlarmCode) && 
                    ((AlarmCode & EQ_UPDATE_OFTEN) == 0) ) {
                  UpdatedDisplayFlag = TRUE;
               }
               else{
                  WeldingResults.EquipmentFailureAlarms |= AlarmCode;
                  if ((EQ_NOT_READY & AlarmCode) != FALSE) NotReadyFlag = TRUE;
                  if ((EQ_NO_CYCLEABORT & AlarmCode) != FALSE) CycleAbort = TRUE;
                  SonicsAbort = TRUE;
               }
            }
            else
               UpdatedDisplayFlag = TRUE;
            break;
   
         case CMG1:                              /* Cycle Modified Alarms      */
            if ((AlarmPtrRam.CycleModified & AlarmCode) == AlarmCode) {
               if ((WeldingResults.CycleModifiedAlarms & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  WeldingResults.CycleModifiedAlarms |= AlarmCode;
                  if ((CM_CYCLE_ABORT & AlarmCode) != FALSE) CycleAbort = TRUE;
                  if ((CM_SONICS_ABORT & AlarmCode) != FALSE) SonicsAbort = TRUE;
                  ModifiedFlag = TRUE;
               }
            }
            else
               UpdatedDisplayFlag = TRUE;
            break;
   
         case WAG1:                              /* Warnings - Group 1         */
            if ((AlarmPtrRam.Warning & AlarmCode) == AlarmCode) {
               if ((WeldingResults.Warnings & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  WeldingResults.Warnings |= AlarmCode;
                  if ((WA_SONICS_ABORT & AlarmCode) != FALSE) SonicsAbort = TRUE;
                  WarningFlag = TRUE;
               }
            }
            else
               UpdatedDisplayFlag = TRUE;
            break;
   
         case CAG1:                              /* Calibration Alarms         */
            if ((AlarmPtrRam.Calibrate & AlarmCode) == AlarmCode) {
               if ((WeldingResults.CalibrateAlarms & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  WeldingResults.CalibrateAlarms |= AlarmCode;
                  NotReadyFlag = TRUE;
               }
            }
            else
               UpdatedDisplayFlag = TRUE;
            break;
   
         case 0:
            UpdatedDisplayFlag = TRUE;
            break;
   
         default:
            break;
   
      }
      if (CycleAbort == TRUE) {
         StopDataCollection();
//         if (WeldingResults.ActualWeldTime <= 5) { /* No graphing unless  */
//            DontPrintGraph = TRUE;                 /* TRS reached         */
//         }
      }
      AlarmsReset = FALSE;                  /* Stop state machine until reset  */
      if (RejectFlag == TRUE) RejectOn();   /* Activate the Reject signal      */
      if (SuspectFlag == TRUE) SuspectOn(); /* Activate the Suspect signal     */
      if (NotReadyFlag == TRUE) {
         ClearReady();                      /* Remove the Ready signal         */
      }
      if (WarningFlag == TRUE) UserCfgOutputOn(OUTPUT_NOTE); /* Activate the Warning output     */
      if (ModifiedFlag == TRUE) UserCfgOutputOn(OUTPUT_MDFY_ALARM);/* Activate the ModifiedAlarm signal */
      if (OverloadFlag == TRUE) UserCfgOutputOn(OUTPUT_OLDALARM);/* Activate the OverloadAlarm signal */
      if (NoCycleFlag == TRUE) UserCfgOutputOn(OUTPUT_NO_CYCLEALARM);/* Activate the NoCycleAlarm signal */
      if (MissingPartOut == TRUE) UserCfgOutputOn(OUTPUT_MISSING_PART);/* Activate the MissingPartAlarm signal */
      
      if (UpdatedDisplayFlag == FALSE) {
         AlarmCounter++;
         AlarmOn();                         /* Turn Reset led on               */
         if (AlarmType != WAG1)             /* Warnings dont SetGeneralAlarm flag*/
         {
            /* General alarm counter will increment if system isn't running */
            /* a cycle (OkToDisplayAlarms) or if PBs have been pressed but */
            /* there have been no alarms recorded so far. */

            if (OkToDisplayAlarms || !CheckGeneralAlarmFlag()){
               CurrentSetup.GenAlarmCount++;
               SetupPtr->GenAlarmCount = CurrentSetup.GenAlarmCount;  /* Update BBR */
            }   

            SetAlarmFlag();      /* Set general alarm output */
         }
         else
            Beep(ALARMBEEP);              /* Warnings sound the beeper         */
         UpdateAlarm();                   /* Send message in case screen=Run   */
      }
   }
}


void RecordSetupAlarm(UINT32 AlarmCode)
/****************************************************************************/
/*                                                                          */
/*  This function will take the passed AlarmCode and set the proper bit in  */
/*  the SetupData structure. It is assumed that the code passed to this     */
/*  function is in fact a setup alarm code.  If it isn't, this function     */
/*  has no way of knowing and it will be decoded as though it is.  So be    */
/*  careful!                                                                */
/*                                                                          */
/****************************************************************************/
{
   UINT16  UpdatedDisplayFlag;
   UINT32  AlarmType;
   CONFIGSETUP  *SetupPtr;
   
   SetupPtr = (CONFIGSETUP *) BBR800_CONFIG_START;

   if (AlarmCounter < (MAXSUBMENUS - 1) ) {
      ResetReceivedFlag = FALSE;        /* Remove evidence of reset pressed */
      SetupAlarmFlag = TRUE;
      UpdatedDisplayFlag = FALSE;
      AlarmType = (AlarmCode & ALARMTYPEMASK);   /* Get what type of alarm     */
      AlarmCode = (AlarmCode & ALARMCODEMASK);   /* Strip off type of alarm    */
      switch (AlarmType) {
         case SEG1:                              /* Setup Alarms - Group 1     */
            if ((AlarmPtrRam.SetupGroup1 & AlarmCode) == AlarmCode) {
               if ((SetupData.SetupErrorAlarms1 & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  SetupData.SetupErrorAlarms1 |= AlarmCode;
               }
            }
            else
                  UpdatedDisplayFlag = TRUE;
            break;
   
         case SEG2:                              /* Setup Alarms - Group 2     */
            if ((AlarmPtrRam.SetupGroup2 & AlarmCode) == AlarmCode) {
               if ((SetupData.SetupErrorAlarms2 & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  SetupData.SetupErrorAlarms2 |= AlarmCode;
               }
            }
            else
                  UpdatedDisplayFlag = TRUE;
            break;
   
         case SEG3:                              /* Setup Alarms - Group 3     */
            if ((AlarmPtrRam.SetupGroup3 & AlarmCode) == AlarmCode) {
               if ((SetupData.SetupErrorAlarms3 & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  SetupData.SetupErrorAlarms3 |= AlarmCode;
               }
            }
            else
                  UpdatedDisplayFlag = TRUE;
            break;
   
         case SEG4:                              /* Setup Alarms - Group 4     */
            if ((AlarmPtrRam.SetupGroup4 & AlarmCode) == AlarmCode) {
               if ((SetupData.SetupErrorAlarms4 & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  SetupData.SetupErrorAlarms4 |= AlarmCode;
               }
            }
            else
                  UpdatedDisplayFlag = TRUE;
            break;
   
         case SEG5:                              /* Setup Alarms - Group 5     */
            if ((AlarmPtrRam.SetupGroup5 & AlarmCode) == AlarmCode) {
               if ((SetupData.SetupErrorAlarms5 & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  SetupData.SetupErrorAlarms5 |= AlarmCode;
               }
            }
            else
                  UpdatedDisplayFlag = TRUE;
            break;
   
         case SEG6:                              /* Setup Alarms - Group 6     */
            if ((AlarmPtrRam.SetupGroup6 & AlarmCode) == AlarmCode) {
               if ((SetupData.SetupErrorAlarms6 & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  SetupData.SetupErrorAlarms6 |= AlarmCode;
               }
            }
            else
                  UpdatedDisplayFlag = TRUE;
            break;
   
         case SEG7:                              /* Setup Alarms - Group 7     */
            if ((AlarmPtrRam.SetupGroup7 & AlarmCode) == AlarmCode) {
               if ((SetupData.SetupErrorAlarms7 & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  SetupData.SetupErrorAlarms7 |= AlarmCode;
               }
            }
            else
                  UpdatedDisplayFlag = TRUE;
            break;
   
         case SEG8:                              /* Setup Alarms - Group 8     */
            if ((AlarmPtrRam.SetupGroup8 & AlarmCode) == AlarmCode) {
               if ((SetupData.SetupErrorAlarms8 & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  SetupData.SetupErrorAlarms8 |= AlarmCode;
               }
            }
            else
                  UpdatedDisplayFlag = TRUE;
            break;
   
         case SEG9:                              /* Setup Alarms - Group 9     */
            if ((AlarmPtrRam.SetupGroup9 & AlarmCode) == AlarmCode) {
               if ((SetupData.SetupErrorAlarms9 & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  SetupData.SetupErrorAlarms9 |= AlarmCode;
               }
            }
            else
                  UpdatedDisplayFlag = TRUE;
            break;
   
         case SEG10:                             /* Setup Alarms - Group 10    */
            if ((AlarmPtrRam.SetupGroup10 & AlarmCode) == AlarmCode) {
               if ((SetupData.SetupErrorAlarms10 & AlarmCode) == AlarmCode) {
                  UpdatedDisplayFlag = TRUE;
               }
               else {
                  SetupData.SetupErrorAlarms10 |= AlarmCode;
               }
            }
            else
                  UpdatedDisplayFlag = TRUE;
            break;
   
         case 0:
            UpdatedDisplayFlag = TRUE;
            break;
   
         default:
            break;
      }
      AlarmsReset = FALSE;                  /* Stop state machine until reset  */
      if (UpdatedDisplayFlag == FALSE) {
         AlarmCounter++;
         AlarmOn();                       /* Turn Reset led on               */
         if (!CheckGeneralAlarmFlag()){    /* Increment only on first alarm */
            CurrentSetup.GenAlarmCount++;
            SetupPtr->GenAlarmCount = CurrentSetup.GenAlarmCount;  /* Update BBR */
         }
         SetAlarmFlag();                 
         UpdateAlarm();                     /* Send message in case screen=Run */
      }
   }
}


UINT16 ClearAlarm(UINT32 AlarmCode) {
/****************************************************************************/
/*                                                                          */
/*  This function will clear hardware resettable alarms.  A TRUE will be    */
/*  returned if the alarm can be cleared (i.e. the hardware condition       */
/*  causing the alarm has been fixed).  A FALSE will be returned if the     */
/*  alarm has not been fixed.                                               */
/*                                                                          */
/*  2.127  08-27-97  BEKymer    Changed assumption on ClearedHardwarealarm  */
/*  2.136  09-18-97  BEKymer    Added palm button check to ClearAlarm       */
/*                                                                          */
/****************************************************************************/

   UINT16  AlarmClearedThisPass = FALSE;


   ClearedHardwareAlarm = TRUE;         /* Assume everything is OK for now  */

/*---   Start checking Door switch (Dont clear unless reset pressed  ---*/

   if ((AlarmCode & DOOR_TRIG_FAIL) == DOOR_TRIG_FAIL) {
      if (CurrentSetup.Actuator == AE) {
         if (AETrigger == FALSE) {
            if (ResetReceivedFlag == TRUE) {
               WeldingResults.EquipmentFailureAlarms &= DOOR_TRIG_FAIL_RESET;
               FinalResults.EquipmentFailureAlarms &= DOOR_TRIG_FAIL_RESET;
            }
            Inp.DoorOpen = FALSE;
            TestModeAllowed = TRUE;      /* Test mode ok now, door is shut  */
         }
         else {
            TestModeAllowed = FALSE;     /* Door open, DONT ALLOW TEST MODE */
            ClearedHardwareAlarm = FALSE;
         }
      }
      else if ( (CurrentSetup.Actuator == AEF) ||
                (CurrentSetup.Actuator == AED) ||
                (CurrentSetup.Actuator == MICRO) ) {
         if (Inp.DoorOpen == FALSE) {
            if (ResetReceivedFlag == TRUE) {
               WeldingResults.EquipmentFailureAlarms &= DOOR_TRIG_FAIL_RESET;
               FinalResults.EquipmentFailureAlarms &= DOOR_TRIG_FAIL_RESET;
            }
            Inp.DoorOpen = FALSE;
            TestModeAllowed = TRUE;      /* Test mode ok now, door is shut  */
         }
         else {
            TestModeAllowed = FALSE;     /* Door open, DONT ALLOW TEST MODE */
            ClearedHardwareAlarm = FALSE;
         }
      }
   }

/*---   Next check for Upper limit (Only clear if reset pressed)  ---*/

   if ((AlarmCode & ULS_FAIL) == ULS_FAIL) {
      if (Inp.uls == TRUE) {
         if (ResetReceivedFlag == TRUE) {
            WeldingResults.EquipmentFailureAlarms &=  ULS_FAIL_RESET;
            FinalResults.EquipmentFailureAlarms &=  ULS_FAIL_RESET;
            AlarmClearedThisPass = TRUE;
         }
      }
      else
         ClearedHardwareAlarm = FALSE;
   }

/*---   Now check for Upper limit return   ---*/

   if ((AlarmCode & ULSRETURN_FAIL) == ULSRETURN_FAIL) {
      if (Inp.uls == TRUE) {
         WeldingResults.EquipmentFailureAlarms &=  ULSRETURN_FAIL_RESET;
         FinalResults.EquipmentFailureAlarms &=  ULSRETURN_FAIL_RESET;
         AlarmClearedThisPass = TRUE;
      }
      else {
         ClearedHardwareAlarm = FALSE;
      }
   }

/*---   Next check for Wrong Actuator  ---*/

   if ((AlarmCode & WRONG_ACTUATOR_FAIL) == WRONG_ACTUATOR_FAIL) {
      ClearedHardwareAlarm = FALSE;
   }


/*---   Now check to see if printer buffer is empty enough      ---*/
/*---   Also check to see if global printing is suspended       ---*/
/*---   if it is there is no reason not to reset.               ---*/

   if(PrinterBufferReadyFlag == TRUE){
      WeldingResults.EquipmentFailureAlarms &= PRINTERBUFFER_RESET;
      FinalResults.EquipmentFailureAlarms &= PRINTERBUFFER_RESET;
   }

   
/*--  Next check for overloads (Dont clear Thermal unless Reset pressed)  --*/

   if (ResetReceivedFlag == TRUE) {
      if (Inp.OL == TRUE) {                /* If overload is still there,   */
         PSReset();                        /* attempt to reset again        */
         ClearedHardwareAlarm = FALSE;
      }
      else {
         WeldingResults.EquipmentFailureAlarms &= THERMALOVERLOADS_RESET;
         WeldingResults.OverloadAlarms &= TESTOVERLOAD_RESET;
         WeldingResults.OverloadAlarms &= (OL_RESET_IS_NEEDED & OL_RESET_NOT_NEEDED);
      }
   }


/*---   Now check for start switches still held   ---*/

   if (WeldState != PBSTATE) {                /* Should be held in PBSTATE */
      if (Inp.OnePB == TRUE) {
         ClearedHardwareAlarm = FALSE;
      }
      else {
         WeldingResults.EquipmentFailureAlarms &= STARTSWITCH_RESET;
         if (ResetReceivedFlag == TRUE) {
            FinalResults.EquipmentFailureAlarms &= STARTSWITCH_RESET;
         }
      }
   }
   else {
      WeldingResults.EquipmentFailureAlarms &= STARTSWITCH_RESET;
      if (ResetReceivedFlag == TRUE) {
         FinalResults.EquipmentFailureAlarms &= STARTSWITCH_RESET;
      }
   }


/*---   Check for Calibrate Actuator alarm (EQ20)  It cant be cleared   ---*/

   if ( ((FinalResults.EquipmentFailureAlarms & EQ20) != FALSE) ||     /* Check both FinalResults and */
        ((WeldingResults.EquipmentFailureAlarms & EQ20) != FALSE) ) {  /* WeldingResults because either */
      ClearedHardwareAlarm = FALSE;                                    /* could be set depending on   */
   }                                                                   /* reason for alarm.           */


/*--- If any alarms were cleared this time, and reset was not pressed  ---*/
/*--- tell system manger so the run screen count can be updated.       ---*/

   if (AlarmClearedThisPass == TRUE && ResetReceivedFlag == FALSE) {
      UpdateAlarm();
   }

   return(ClearedHardwareAlarm);
}




void TestTest(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called every ms while in test mode.  It will turn off */
/*  sonics after the proper time has elapsed, if the reset key has not     */
/*  been pressed.                                                          */
/*                                                                         */
/***************************************************************************/
{
   if (CheckIfResetRequired() == FALSE){
      AlarmsReset = TRUE;
   }
   if (TestModeAllowed == TRUE) {
      if (PSResetDelay > 0) {
         PSResetDelay--;
      }
      else if (ResetReceivedFlag == FALSE) {  /* Dont keep sonics on if reset pressed */
         PSTest();                            /* Start the sonics                */
      }
      PowerTest=PwrTestFilter(CurrentPowerIn);  // Display Filtered Power during Test  

      // Now they don't want to see PeakPower during test DCS-2265
      // if (PowerTest > PeakTestPower) PeakTestPower = PowerTest;

      DisplayTestPower(PowerTest);      // Display test mode power reading

      if (Inp.PSRun == TRUE)
         LatchPSRun = TRUE;

      if (Inp.PSSeek == TRUE)
         LatchPSSeek = TRUE;

      if (Inp.PSClear == TRUE)
         LatchPSClear = TRUE;

      if (Inp.PSStore == TRUE)
      {
         Inp.PSStore = FALSE;
         LatchPSStore = TRUE;
         QVGALatchPSStore = 2;
      }

      TestTime++;
      TestTimerCounter++;
      if (TestTimerCounter >= MAXTESTTIME)
         TestTimerFlag = TRUE;

      if (--TestCountDown <= 0) {
         TestCountDown = 250;
         if(QVGALatchPSStore) QVGALatchPSStore--;
         SendFakeKeyPress(UPDATEDISPLAY);      /* Tell menu system to update   */
      }
   }
}     



void EnterTest(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when test mode is first started.  It will      */
/*  start a timer which will be used to check the length of time sonics    */
/*  are on, in case the reset key is not pressed in time.                  */
/*                                                                         */
/***************************************************************************/
{
   ClearReady();                       /* Remove Welder Ready signal       */
   TestCountDown = 250;
   TestTimerFlag = FALSE;              /* Make sure flag is clear          */
   if (TestModeAllowed == TRUE){
      FrequencyStart = CurrentFreqIn;
      TestTime = 0;
      TestTimerCounter = 0;            /* Reset timer                      */
      PowerTest = 0;                   /* Clear old power value            */
      PeakTestPower = 0;               /* Clear old peak power value       */
      TestPwrSum=0;
   }
   else {
      PSIdle();                        /* Make sure sonics are off         */
      TestTimerCounter = MAXTESTTIME;  /* Reset timer                      */
   }
}



void ExitTest(void)
/***************************************************************************/
/*                                                                         */
/*  This function is called when sonics need to be turned off in test      */
/*  mode.  You can get here because the user pressed the reset key, the    */
/*  power supply overloaded or the test timer has expired.                 */
/*                                                                         */
/***************************************************************************/
{
   UINT16 i;
   // DisplayTestPower(PeakTestPower); DCS 2265
   for(i=0; i<=15; i++){
      BuffPwrTst[i]=0;
   }
   FreqChg = CurrentFreqIn - FrequencyStart;
   PSIdle();
   StartTestFlag = FALSE;
   /* Test for overload and DUPS present */
}



void EnterFData(void)
/****************************************************************************/
/*                                                                          */
/*   This function will initalize the flag so SendFData can deal with       */
/*   actually sending the final data and then leaving quickly.              */
/*                                                                          */
/****************************************************************************/
{
   OkToDisplayAlarms = TRUE;
   OKToAdvance = FALSE;
   InitTimer();                     /* Reset all timers for next weld cycle */
}



void SendFData(void)
/****************************************************************************/
/*                                                                          */
/*   This function will put the final data into a structure and then send   */
/*   a pointer to that structure to the weld manager.                       */
/*                                                                          */
/*   It will also take care of the weld counter.                            */
/*                                                                          */
/*   Final data will only be sent if we reached trigger.  This is decided   */
/*   by looking at the weld time.  If it is greater than 0, we must have    */
/*   triggered, so send the data.                                           */
/*                                                                          */
/****************************************************************************/
{
   CONFIGSETUP  *SetupPtr;

   SetupPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   if (WeldingResults.ActualWeldTime > 0) {  /* If not 0, then we triggered */

/*----  Here deal with incrementing the weld counters  ----*/

      CurrentSetup.PSLifetime++;
      SetupPtr->PSLifetime = CurrentSetup.PSLifetime;  /* Update BBR */
      if (CurrentSetup.AdvanceCounters == TRUE){      /* TRUE: all cycles */
         WeldingResults.CycleCount++;
      }
      else if (CheckGeneralAlarmFlag() == FALSE){
         WeldingResults.CycleCount++;
      }
      
      /* Increment external sample count, if ExtPreset is enabled. */
      if(CurrentSetup.ExtPresets == TRUE)
         ExtSampleCount++;
      
      PollingCommandCounter++;
      if (CurrentSetup.SequenceEnable == TRUE && CurrentSetup.SequenceCount != 0)   
      {
         CurrentSetup.SequenceNos++;
         CurrentSetup.SequenceNos %= CurrentSetup.SequenceCount;
      }
      
#ifdef TRIGGER_FORCE_TEST

      WeldingResults.TrigForce = ActualTriggerForce;
      WeldingResults.ActualWeldCollapse = WeldingResults.ActualTriggerDistance;

#endif

      memcpy(&FinalResults, &WeldingResults, sizeof(WeldingResults) );

      if(CurrentSetup.AmpMicronsFlag == TRUE)
      {
        FinalResults.ActualAmplitudeStart = CurrentPreset.AmpAMicron;
        if ((RunningPreset.Amp2Flag & BIT0) == BIT0)
        {
        	FinalResults.ActualAmplitudeEnd = CurrentPreset.AmpBMicron;
        }
      }

      if(BitFlags.PkPwrbit)
      {
    	  if(CurrentSetup.PeakPowerWattsFlag == TRUE)
    	  {
    		  FinalResults.PeakPower = ThreeRulePorcentageToWatts(FinalResults.PeakPower,CurrentSetup.PSWatt);
    	  }

      }

      WeldingResultsPtr = &WeldingResults;
      end_weld_msg.common.opcode = OP_WELDER_STATE_CHANGE;
      end_weld_msg.common.source_task = WC_ISR_TASK;
      end_weld_msg.state = FINALDATASTATE;
      end_weld_msg.weld_samples = 1;
      end_weld_msg.weld_data_ptr = WeldingResultsPtr;
           
      ChangeDataStorage();                   /* Change data storage address */
      
      q_send(WmgrQid,&end_weld_msg);
      // Activate Cycle Okay signal if no alarm is recorded.
      if(!CheckAlarmFlag())
         UserCfgOutputOn(OUTPUT_CYCLE_OK);
      /*If ultrasonics were disabled by the user input 
         signal during the weld cycle the record 'Sonic Disabled' alarm.*/
      if(SonicDisabledFlag)
         RecordAlarm(W11);
   }
   OKToAdvance = TRUE;
}



void UpdateAlarm(void)
/****************************************************************************/
/*                                                                          */
/*   This function will allow the display to be updated with new data, even */
/*   if final data is not available.  This will allow alarms to be shown    */
/*   on the run screen even if a cycle has not been completed.              */
/*                                                                          */
/****************************************************************************/
{

   end_weld_msg.common.opcode = OP_WELDER_STATE_CHANGE;
   end_weld_msg.common.source_task = WC_ISR_TASK;
   end_weld_msg.state = UPDATEALARMSTATE;
   end_weld_msg.weld_samples = 1;
   end_weld_msg.weld_data_ptr = WeldingResultsPtr;
   
   q_send(WmgrQid,&end_weld_msg);

}



UINT16 CheckIfResetRequired(void)
/****************************************************************************/
/*                                                                          */
/* This function will check to see if a reset is required.  If a reset is   */
/* required then a TRUE will be returned, otherwise a FALSE will be         */
/* returned.                                                                */
/*                                                                          */
/****************************************************************************/
{
   UINT16 ResetRequiredFlag = FALSE;          /* Assume reset not required */
   UINT16 ClearFlag = TRUE;                   /* Assume condition is fixed */

   if (AlarmFlag == TRUE) {

/*---  Here, check alarms which always require reset  ---*/

      if ( ((FinalResults.OverloadAlarms & OL_RESET) != 0) ||
           ((FinalResults.EquipmentFailureAlarms & EQ_NO_RESET) != 0) ||
           ((FinalResults.EquipmentFailureAlarms & EQ_RESET) != 0) ||
           ((FinalResults.CalibrateAlarms & CA_NO_RESET) != 0) ) {
         ResetRequiredFlag = TRUE;
         if (ClearAlarm(FinalResults.EquipmentFailureAlarms) == FALSE) {
            ClearFlag = FALSE;
         }
      }


/*--  Check alarms which require reset only if Reset Required = On  --*/

      if (RunningPreset.GeneralAlarmLFlag == TRUE) {   /* See if globally required */
         if ( ((FinalResults.NoCycleAlarms & NC_NOT_REQ_RESET) != 0) ||
              ((FinalResults.OverloadAlarms & OL_NOT_REQ_RESET) != 0) ||
              ((FinalResults.EquipmentFailureAlarms & EQ_NOT_REQ_RESET) != 0) ||
              ((FinalResults.CycleModifiedAlarms & CM_NOT_REQ_RESET) != 0) ||
               (FinalResults.RejectBitResult != 0) ||
               (FinalResults.SuspectBitResult != 0) ||
               (FinalResults.CalibrateAlarms != 0)) {
            ResetRequiredFlag = TRUE;
         }
      }

/*--   Here check for alarms which cant be reset as well as those which   --*/
/*--   require reset.                                                     --*/

      if (RunningPreset.SusResetRequired == TRUE) {
         if (FinalResults.SuspectBitResult != 0) {
            ResetRequiredFlag = TRUE;
                    }
      }
      if (RunningPreset.RejResetRequiredFlag == TRUE) {
         if (FinalResults.RejectBitResult != 0) {
            ResetRequiredFlag = TRUE;
         }
      }
      if (ResetReceivedFlag == TRUE) {
         if (ClearFlag == TRUE){
            AlarmOff();                 /* Turn off Reset led               */
            ClearGeneralAlarm();        /* Remove GeneralAlarm,suspect,&reject signals*/
            ResetRequiredFlag = FALSE;
            ClearAlarmFlag();
            ResetReceivedFlag = FALSE;  /* Clear signs of reset press   */
         }
         ResetReceivedFlag = FALSE;     /* Clear signs of reset press   */
      }
   }
   return(ResetRequiredFlag);
}



void ClearCalibrationAlarms(void)
/****************************************************************************/
/*                                                                          */
/*  This function will clear all calibration related alarms.  This should   */
/*  be called only after a successful calibration has been done.  If any    */
/*  calibration alarms exist, they will be cleared and the reset key will   */
/*  be pressed.  If any other alarms exist a reset key will be pressed to   */
/*  clear those as well. The Errorcode and Errorcodeflag need to be reset.  */
/*                                                                          */
/****************************************************************************/
{

   ErrorCode = 0;
   ErrorCodeFlag = FALSE;
   if ( ((FinalResults.EquipmentFailureAlarms & EQ4) != 0) || /* If door/trg fail  */
        ((FinalResults.Warnings & W8) != 0) ||                /* or cal warning    */
        ((FinalResults.EquipmentFailureAlarms & EQ20) != 0) ||/* or calib required */
        (AlarmFlag == TRUE) )                                   /* or any other alarm*/
   {
       FinalResults.EquipmentFailureAlarms &= RESET_CALIBRATION_ALARMS;
       FinalResults.Warnings &= RESET_CALIBRATION_WARNINGS;

       WeldingResults.Warnings &= RESET_CALIBRATION_WARNINGS;
       WeldingResults.EquipmentFailureAlarms &= RESET_CALIBRATION_ALARMS;
       if((WeldState != READYSTATE) && (WeldState != PREREADYSTATE))
          WeldState = PREREADYSTATE;
       SendKeyToWeldMngr(OP_RESET_KEY_PRESSED, 0);
   }
}



void TestActClr(void)
/****************************************************************************/
/*                                                                          */
/*   This function will be executed every ms.  It will check to see if the  */
/*   actuator clear distance has been reached if the actuator clear is on   */
/*   or if home has been reached if actuator clear is off.  If either of    */
/*   these cases happen the ActClrFlag will be set allowing the state to    */
/*   end.  However, if ULS is reached (and actuator clear is on) before the */
/*   distance is reached an alarm will be created.                          */
/*                                                                          */
/*    60.2.116 07-21-97  BEkymer    Change logic in TestActClr              */
/*                                                                          */
/****************************************************************************/
{
   SINT32 LocalEncoder = EncoderPos;
   
   if (RunningPreset.ActClrFlag == TRUE) { /* Actuator Clear function is ON */

/*------------  Linear Encoder here  ------------*/

      if ( (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == MICRO) ) {
         if (RunningPreset.ActClrDistance > LocalEncoder) {
            ActClrOn();
         
         }
         else {
            if (Inp.uls == TRUE) {
               ActClrOn();
               ActClrFlag = TRUE;
//               RecordAlarm(EQ21);
            }
            else {
               ActClrOff();
            }
         }
      }
      else { /* Actuator Clear function is on, but its only an ae actuator, so use ULS */
         if (Inp.uls == TRUE)
            ActClrOn();
         else 
            ActClrOff();
      }
   }
   else {                                  /* Actuator Clear function is OFF */
      if (Inp.uls == TRUE)
         ActClrOn();
      else 
         ActClrOff();
   }
}


void ClearFinalResults(void)
{
   WeldingResults.ActualFreqEnd = 0;
   WeldingResults.ActualFreqStart = 0;
   WeldingResults.FrequencyChange = 0;
   WeldingResults.FrequencyMin = 50000;  /* initialize to maximum */
   WeldingResults.FrequencyMax = 0;
   WeldingResults.TotalEnergy = 0;
   WeldingResults.ActualWeldAbs = 0;
   WeldingResults.ActualTotalAbs = 0;
   WeldingResults.ActualTriggerDistance = 0;
   WeldingResults.ActualTotalCollapse = 0;
   WeldingResults.ActualWeldCollapse = 0;
   WeldingResults.ActualVelocity = 0;
   WeldingResults.SetForceB = RunningPreset.Force2;
   WeldingResults.SetForceA = RunningPreset.WeldForce;
   WeldingResults.HoldForceMax = 0;
   WeldingResults.WeldForceEnd = 0;
   WeldingResults.ActualAmplitudeStart = 0;
   WeldingResults.ActualAmplitudeEnd = 0;
   WeldingResults.PeakPower = 0;
   WeldingResults.ActualWeldTime = 0;
   WeldingResults.TrigForce = RunningPreset.TriggerForce;
   WeldingResults.PSActControlFlags = CurrentSetup.AmpControl;
   if ((RunningPreset.Amp2Flag & BIT0) == BIT0) {     /* If stepping on     */
      WeldingResults.PSActControlFlags |= BIT1; /* set BIT1           */
   }
   if ((RunningPreset.Force2Flag & BIT0) == BIT0) {     /* If stepping on     */
      WeldingResults.PSActControlFlags |= BIT4; /* set BIT4           */
   }
   if ((CurrentSetup.FreqControl & BIT0) == BIT0) {   /* If Freq=internal   */
      WeldingResults.PSActControlFlags |= BIT2; /* set BIT2           */
   }
   if (ClearAlarm(WeldingResults.EquipmentFailureAlarms) == TRUE) {
      WeldingResults.EquipmentFailureAlarms = 0;
   }
   WeldingResults.RejectBitResult = 0;
   WeldingResults.SuspectBitResult = 0;
   WeldingResults.NoCycleAlarms = 0;
   WeldingResults.OverloadAlarms = 0;
   WeldingResults.CycleModifiedAlarms = 0;
//   WeldingResults.CalibrateAlarms = 0;
   WeldingResults.Warnings = 0;
   WeldingResults.PresetNum = 0;
   WeldingResults.PresetName[0] = NULL;
   WeldingResults.CycleTimeResult = 0;

   MsDataPtr->AmpStepAtTime = 0;
   MsDataPtr->ForceStepAtTime = 0;
   MsDataPtr->HoldEndAtTime = 0;
   MsDataPtr->SeekEndAtTime = 0;
   MsDataPtr->PrintBottomFlags |= ALLALARMMASK;    /* Assume all will fail */
}




//--------------------------Power Filter During Test----------------------
//
//   This function accepts CurrentPowerIn as an argument, and returnes
//   the average of the last 16 previous elements. 
// 
//------------------------------------------------------------------------

UINT32 PwrTestFilter (UINT32 Element){
UINT32 temp;
   if(ptst==&BuffPwrTst[FilterIndex16-1]){
      temp=*ptst;                     // It was the last element
      *ptst=Element;
      ptst=&BuffPwrTst[0];
   }
   else{
      temp=*ptst;                     // It was the last element
      *ptst=Element;
      ++ptst;
   }
   TestPwrSum=TestPwrSum+Element-temp;// !     
   return (TestPwrSum >> 4);          // Devide by 16;  --> 0000
}

void RecordErrorCode(enum ERRORCODE_ARG ErrorCodeArg)
/****************************************************************************/
/*                                                                          */
/* It will take the passed argument and  put it in the public variable      */
/* ErrorCode and set ErrorCodeFlag to True, unless ErrorCode is non-zero,   */
/* but always if ErrorCodeArg is AED upgrade error, which takes precedence  */
/* over all other errors.                                                   */ 
/*                                                                          */
/****************************************************************************/
{
   if (ErrorCode == 0 || ErrorCodeArg == ERRORCODE1100_EQ20 || ErrorCodeArg == ERRORCODE1200_EQ20)
   {
      ErrorCode = ErrorCodeArg;
      ErrorCodeFlag = TRUE;
   }
}

void EnterExtTrigDly(void)
/****************************************************************************/
/*                                                                          */
/*   This function will initalize the flag so TestExtTrigDly can deal       */
/*   to wait in this state untill the Inp.ExtTrgDelay input becomes low.    */
/*                                                                          */
/****************************************************************************/
{
   ExtTriggerDelayTimer = 0;
   TrgDelayTimeout = FALSE;
   WeldingResults.ActualTriggerDistance = EncoderPos; /* Save position for coll calc */
   
}

void TestExtTrigDly(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for external     */
/*  trigger delay input becomes low.If the input doesn't deactivates in    */
/*  30 seconds this will record the alarm and abort the cycle.             */
/*                                                                         */
/***************************************************************************/
{
   if(ExtTriggerDelayTimer++ >  EXT_TRGDELAY_TIMEOUT)
      TrgDelayTimeout = TRUE;
      
   TriggerLostFlag = CheckForTriggerLost();   
}


void EnterSV(void)
/****************************************************************************/
/*                                                                          */
/*   This function will initalize the flag so TestSVInput can check for the */
/*   Inp.SVInterlock input.                                                 */ 
/*                                                                          */
/****************************************************************************/
{
   SVTimer = 0;
   SVTimeout = FALSE;
   /*Make SVInterlock Output High*/   
   SVOutOn();
}

void TestSVInput(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed every ms while waiting for SVInterlock  */
/*  input becomes active.                                                  */
/*                                                                         */
/***************************************************************************/
{
   if(SVTimer++ >  CurrentSetup.SVDelay)
      SVTimeout = TRUE;
}

void ExitSVState(void)
/***************************************************************************/
/*                                                                         */
/*  This function will be executed when exit from the SVInterlock state.   */
/*  This fuction will cause to move the horn down.                         */
/*                                                                         */
/***************************************************************************/
{
    EnableSVOn();                        /* Enable SV valve                 */
    SVOn();                              /* Turn on SV to bring down hown   */
}
