/* $Header:   D:/databases/VMdb/2000Series/App/WELDHOLD.C_V   2.250.1.0   26 Oct 2013 12:56:24   gbutron  $ */
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
/* Module name: Weldhold                                                    */
/*                                                                          */
/* Filename:    Weldhold.c                                                  */
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
/*  =========  ========  =========  ===========                             */
/*     0       03-20-96  BEKymer    Add pSOS to state code                  */
/*     1       04-28-96  LAM        deleted checkprocesslimits              */
/*     2       05-10-96  LAM        cleaned up variables                    */
/*     3       05-13-96  BEKymer    Add proper function prototyping         */
/*     4       06-14-96  LAM        chged cycletime to cycletimer           */
/*     5       06-26-96  LAM        deleted energy chgs                     */
/*     6       07-09-96  BEKymer    Add trigger delay function              */
/*     7       07-15-96  BEKymer    Remove tenths of percent in power       */
/*     8       07-24-96  BEKymer    Set amplitude in afterburst             */
/*                                  In TriggerDelay go to WeldForce instead */
/*                                  of TriggerForce.                        */
/*     9       08-08-96  BEKymer    Add in post weld seek, ramp AB off      */
/*                                  Change trigger lost force to 5 lbs.     */
/*    10       08-13-96  BEKymer    New functions for SonicsOnX for weld    */
/*                                  modes beyond TIME.                      */
/*    11       08-22-96  BEKymer    Fill in ActualTriggerDistance in Final  */
/*                                  Results structure                       */
/*    12       09-11-96  BEKymer    Add code to check for max timeout in    */
/*                                  CheckControlLimits function             */
/*    13       09-18-96  PhilJ      Changed TimeoutEnergy to MaxTimeout     */
/*    14       09-18-96  BEKymer    Changed AbsDist variable to ABSCutoff   */
/*                                  Dist in CheckControlLimits (TEC mode)   */
/*    15       09-21-96  BEKymer    Subtract 1 from actual weld time        */
/*    16       10-01-96  BEKymer    All cutoff conditions to generate alarm */
/*    17       10-08-96  BEKymer    Check control limits in StartSonics2 to */
/*                                  fix DCS #634.                           */
/*                                  Sonic1, if control limits off dont add  */
/*                                  50% to weld time DCS #631               */
/*                                  Fix DCS # 630                           */
/*    18       10-09-96  BEKymer    Set weld force in SonicsOn state        */
/*    19       10-11-96  BEKymer    In StartSonic3 fix DCS #640             */
/*    20       10-15-96  BEKymer    Change alarm defines in CheckControlL...*/
/*                                  Add force and amp step triggers         */
/*    21       10-29-96  BEKymer    Add 35 lb & 1/4" test to TriggerLost    */
/*    22       10-31-96  BEKymer    Rename ActualTriggerDistance to Actual  */
/*                                  TrigPos to so not the same as FinalRes..*/
/*    23       11-05-96  BEKymer    Switch to weld force after trigger delay*/
/*    24       11-12-96  BEKymer    Avoid overflow in energy calc           */
/*    25       11-14-96  BEKymer    Add delay to start of seek              */
/*                                  Add scrub time for 2nd amp step         */
/*    26       11-15-96  LAM        added check for movementstopflag        */
/*    27       11-20-96  BEKymer    Add alarm for Time extended in TEC      */
/*    28       12-13-96  BEKymer    CheckControlLimits in CheckHold         */
/*                                  CheckForForceStepping in all weld modes */
/*    29       01-06-97  LAM        redefined beep prototype                */
/*    30       01-10-97  PhilJ      UINT32 CurrentFreqIn to SINT32          */
/*    31       01-12-97  LAM        added EP check on safetycheck           */
/*    32       01-21-97  LAM        added encoder fail msg,trs lost AE      */
/*    33       01-24-97  LAM        added encoder fail msg,on return stroke */
/*    34       02-06-97  LAM        fixed seek delay                        */
/*    35       02-11-97  LAM        fixed weldon signal                     */
/*    36       02-18-97  LAM        added horn return flag                  */
/*    37       02-22-97  LAM        deleted trigger beep, done in states.c  */
/*                                  added cycle abort checks                */
/*    38       03-02-97  LAM        added freq offset,fixed ext step        */
/*    39       03-04-97  LAM        fixed amp step shorter time             */
/*    40       03-07-97  LAM        fixed amp start value                   */
/*    41       03-17-97  LAM        modified what is done every ms          */
/*    42       03-19-97  LAM        fixed peak power                        */
/*    43       03-28-97  LAM        chged default to 6 seconds              */
/*    43.01    04-02-97  LAM        fixed amp step in other modes           */
/*    43.02    04-03-97  LAM        chged amp start and end                 */
/*    43.03    04/06/97  LAM        added test actclr check                 */
/*    48.04    04-07-97  BEKymer    Changed PeakPowerCutoff to W5 from G40  */
/*                                  Changed AbsoluteCutoff to W6 from G45 if*/
/*                                  sonics already started.                 */
/*                                  Check Max Timeout only if in WELDTIMESTATE*/
/*    49.00    04-10-97  BEKymer    Add define for HORNRETURNTIMEOUT        */
/*                                  Change RampOff() so if AbTime < ABRAMP  */
/*                                  the ramp is faster (AbTime)             */
/*    50.00    04-11-97  BEKymer    Change HORNRETURNTIMEOUT to UPPERLIMIT_ */
/*                                  TIMEOUT                                 */
/*    51.00    04-14-97  LAM        fixed amp step after T.O,amp2time       */
/*    51.01    04-16-97  BEKymer    Fix bug in AB ramp, changed ramp time   */
/*                                  to 10 ms by Kevin's Request             */
/*    52.00    04-21-97  LAM        added collectenergyflag                 */
/*    53.00    04-24-97  LAM        fixed maxtimeout during step 2          */
/*    54.00    04-28-97  LAM        fixed peakpower                         */
/*    54.01    04-29-97  BEKymer    Changed Time Extended Alarm to W7       */
/*    55.00    05-01-97  BEKymer    Add extra arg to UpdateBar.. for blink  */
/*    55.01    05-05-97  LAM        fixed seek overloads                    */
/*    55.2.79  05-08-97  BEKymer    Allow RecordAlarm to set SonicsAbort    */
/*                                  and CycleAbort flags                    */
/*    56.2.80  05-23-97  BEKymer    Change G33 comment to cycle abort       */
/*    56.2.81  05-28-97  LAM        fixed ampB reporting 0                  */
/*    56.2.82  06-05-97  BEKymer    New function AlStopTest                 */
/*    56.2.83  06-06-97  LAM        fixed peakpower in energymode           */
/*    56.2.84  06-18-97  PhilJ      Changed CurrentSetup.WeldTimes and Test */
/*                                  Times to Time & Test Multiplier.        */
/*    56.2.86  07-01-97  LAM        added checkencoder when encoder present */
/*                                  chged step at absolute to collapse      */
/*                                  added collapse cutoff,SF11 - OL3,SF1-CA1*/
/*                                  G33 - NC7,SF2 - EQ1,G38 - CM2, G39 - CM3*/
/*    56.2.87  07-02-97  LAM        added no encoder functions,deleted get  */
/*                                  currentmodel#                           */
/*    56.2.88  07-03-97  PhilJ      Replaced GetPowerSupplyWattage with     */
/*                                  CurrentSetup.PSWatts                    */
/*    56.2.89  07-09-97  BEKymer    Change alarm codes to new format        */
/*    56.2.90  07-11-97  BEKymer    Finish alarm code update                */
/*    57.2.90  07.17.97  JBERMAN    Missing Part Min                        */
/*    57.2.92  07-17-97  BEkymer    Added alarm NC10                        */
/*    58.2.93  07.28.97  JBerman    CheckControlLimits: Added RecordAlarm(W7)*/
/*                                       chgd:  .WeldEnergy <-> .EnergyML   */
/*    58.2.94  07-29-97  BEKymer    Remove unused AlarmDetectedFlag         */
/*    58.2.95  08-04-97  BEKymer    Check .ControlLimitsFlag in function    */
/*                                  CheckEnergyComp                         */
/*                                  Check for Abs Before Trg (NC9)          */
/*                                  Check ECycleAbort in CheckSeek          */
/*                                  Change StopSeek alarm from OL3 to OL8   */
/*    58.2.96  08-08-97  BEKymer    Fudge the time before TEC alarm created */
/*                                  Remove Ext Cycle Abort from CheckCon-   */
/*                                  trolLimits, remove call to CheckControl-*/
/*                                  Limits from CheckHold                   */
/*    59.2.97  08-12-97  BEKymer    Add check for EQ1 in CheckControlLimitsD*/
//    59.2.99  09.15.97  JBerman    Eliminated "AccessControlOutputPorts."                                                                   
//    59.3.00  09.18.97  JBerman    Forced 30sec max weld time limmit in TEC Mode.                                                                        
/*    60.2.103 08-17-97  LAM        replaced getpower                       */
//    2.104    08-23-97  LAM        Deleted triggerattime       
//    2.105    08-25-97  LAM        chged cycletimer to sonictimer
//    2.106    08.26.97  JBerman    Added CurrentPreset.ScrubTimerFlag into
//                                  Gnd Det Mode
//    2.107    08.27.97  LAM        Added 1ms to adjust for delay in power supply
//                                  delayed setsas by 1ms
/*    2.108    09-02-97  BEKymer    Added ActualAfterburstTime for alrm info*/
/*    2.109    09-03-97  BEKymer    Clear OL's after afterburst and seek    */
/*                                  Change SeekTime to ActualSeekTime for   */
/*                                  alarm addtional information             */
/*                                  Check for overload in CheckSeek()       */
/*                                  Fix the value put into FinalResults.    */
/*                                  SeekEndAtTime (add in ActualSeekTime)   */
/*    2.110    09-09-97  BEKymer    Remove BinkCondition argument on calls  */
/*                                  to UpdateBarGraph                       */
/*    2.111    09-11-97  PaulG      Unit test and data cleanup              */ 
/*    2.112    09-13-97  LAM        let freq chg go negative                */ 
/*    2.113    09-22-97  BEKymer    Check ControlLimitsFlag & WeldMode when */
/*                                  dealing with energy compensation        */
/*                                  Check for Absolute mode when dealing    */
/*                                  with absolute distance cutoff           */
/*    2.114    09-24-97  LAM        freq chg go negative when end < start   */
/*    2.115    09-29-97  BEKymer    Check CycleAbort in TEC mode            */
/*    2.116    10-02-97  LAM        made sure min/max and end/start freq ok */
/*    2.117    10-06-97  BEKymer    Check weldmode for alarms W5 & W9       */
/*                                  Round off FinalResults.PeakPower        */
/*    2.118    10-07-97  BEKymer    Check FinalResults.ActualWeldTime in    */
/*                                  CheckEnergyComp()                       */
/*    2.119    10-08-97  LAM        fixed seek time off by .001ms           */
//    2.120    10-08-97  LAM        donot add hold time to seek time, when off
//    2.121    10.13.97  JBerman    Added PSIdle in StopABTme; solves DCS 1968
/*    2.122    10-16-97  LAM        apply frequency offset at sonics on     */
//    2.123    10.24.97  JBerman    Removed comment: PSIdle in StopSeek    
//    2.124    10.24.97  JBerman    In CheckControlLimits I reduced 3 from
//                                  EnergyInJoules. DCS# 2148.              
/*    2.125    10-28-97  BEKymer    New function StartAHold                 */
/*    2.126    10-29-97  LAM        fixed more .001 round off errors        */
/*    2.127    10-29-97  BEKymer    For amp checking make sure amp=internal */
/*    2.128    11-03-97  LAM        fixed freq max = 0                      */
/*    2.129    11-06-97  LAM        fixed freqoffset value only used when enabled*/
/*    2.130    11-13-97  BEKymer    In StopSeek(), do either PSReset or     */
/*                                  PSIdle, but not both.                   */
/*    2.131    11-18-97  BEKymer    Turn off cooling valve when post weld   */
/*                                  seek overloads.                         */
/*    2.132    11-18-97  LAM        replaced finalresults with weldingresults*/
/*    2.133    12.01.97  JBerman    Replaced in StopABTme CoolValOff-PSIdle                                                                      */
/*    2.134    12-03-97  BEKymer    Use ActualHoldTime instead of requested */
/*                                  hold time in StopHold().                */
/*    2.135    12-05-97  BEKymer    Eliminate AlStopSeek()                  */
/*    2.136    12-11-97  BEKymer    Change calculation for Seek end time    */
/*    2.137    12-13-97  LAM        divided ampsettings to 1%               */
/*    2.138    01-20-98  BJB        Removed code that tests MaxTimeoutFlag, */
/*                                  always acts like feature is enabled.    */
/*    2.139    01-26-98  BEKymer    In CheckEnergyComp check for W7 even if */
/*                                  PR15 didn't happen (DCS # 2357)         */
/*    2.140    01-27-98  LAM        set weldtime, step at time, holdtime,   */
/*                                  and maxtimeout to set value when no alarms */
/*                                  occurred                                */
/*    2.141    01-29-98  LAM        set end of seektime to requested        */
/*    2.142    02-03-98  BEKymer    Break Ext cycle abort into 2 alarms.    */
/*                                  Break Grd Det cutoff into 2 alarms.     */
/*    2.143    02-04-98  BEKymer    Move 'AtTime' values from WELD_DATA to  */
/*                                  WELD_OBJECT structure                   */
/*    2.144    02-05-98  BEKymer    Send FinalResults.PeakPower in tenths   */
//    2.145    02.12.98  JBerman    1) Set CoolValOn & CoolValOff @ the right  
//                                     place                                 
//                                  2) Created a +/- 4% window filter, In                           
//                                     StopSonic2, to compensate inaccurate
//                                     hardware errors                                    
//    2.146    02.13.97  JBerman    Added CoolValOn in StartSonic3, to enable                                 
//                                  the cooling valve in: Energy, Peak Power 
//                                  & Groumd Detect Mode.
//    2.147    02.16.97  JBerman    Modified AmpWindow to +/- 2%
/*    2.148    02-16-98  BEKymer    In CheckSeek use CM15 instead of NC7    */
/*                                  for external cycle abort alarm          */
/*    2.149    02-18-98  BEKymer    Put in alarm calls when amplitude not   */
/*                                  within tolerance (CM16-CM20).           */
/*                                  Remove casting on ActualAmp..Start/End  */
/*                                  Change peak power cuttoff to occur when */
/*                                  less than or EQUAL                      */
/*    2.150    03-09-98  LAM        turn off sonics immediately when entering */
/*                                  stopsonic2 or alstopsonics, clear energycollectflag */
/*                                  in alstopsonics, chged stoptimer test in*/
/*                                  stopsonic2 or alstopsonics              */
/*    2.151    03-10-98  LAM        do not set cycleabort in alstopsonics   */
/*    2.152    03-17-98  BEKymer    For amp alarms make sure control is int.*/
/*                                  Limit Information Exchanged (LIE)       */
/*                                  -     -           -                     */
/*                                  about weld, hold, seek and step @ times */
/*                                  to fix (!?) DCS # 2346.                 */
/*                                  Remove the 5 amplitude alarms           */
/*                                  Limit Information Exchanged (LIE)       */
/*                                  -     -           -                     */
/*                                  about Amp A and Amp B                   */
/*    2.153    03-20-98  BEKymer    Use AmpControlFlags to determine if we  */
/*                                  should set final results to requested   */
/*                                  or zero (control = internal/external)   */
/*    2.154    03-20-98  BEKymer    Same change as 2.153 except for AlStopS.*/
/*    2.155    03-23-98  BEKymer    Remove compiler waring in AlStopSonics()*/
/*    2.156    03-24-98  BEKymer    CheckEnergyComp before LIE'ing about    */
/*                                  the weld time.                          */
/*    2.157    04-02-98  BEKymer    Add AB delay in Post 'weld seek at time'*/
/*                                  Adjust actual AB time for ABRAMPDOWNTIME*/
/*    2.158    04-06-98  BEKymer    Remove test for ControlLimits wherever  */
/*                                  max timeout is used.                    */
/*    2.159    04-17-98  LAM        check for cycleabort before turning on  */
/*                                  sonics during afterburst                */
/*    2.160    04-23-98  LAM        removed largest value check in check for*/
/*                                  safety                                  */
/*    2.161    04-27-98  BJB        Moved TRIGGERLOSTTIME def to STATE.H    */
/*    2.162    05-01-98  LAM        added recal actuator alarm to triggerlost*/
/*    2.163    05-14-98  LAM        temporarily added trigforce to weld_obj */
/*    2.164    05-15-98  LAM        set PVP control back to velocity at the */
/*                                  end of hold                             */
/*    2.165    05-19-98  LAM        look for ground detect cutoff in ground */
/*                                  mode before trigger(DCS 2544)           */
/*    2.166    05-19-98  BEKymer    Remove NC10 alarm in step on collapse   */
/*                                  to fix DCS # 2045.                      */
/*                                  Change stepping reference from absolute */
/*                                  to collapse.                            */
/*                                  Changed MAXSEEKTIME back to 500ms       */
/*    2.167    05-20-98  BEKymer    Changed alarm PR15 to CM21  DCS # 2494  */
/*    2.168    05-29-98  LAM        look for ground detect cutoff in ground */
/*                                  mode even when cycle aborts are off     */
/*    2.169    06-03-98  BEKymer    Check for missing part one last time    */
/*                                  before turning on sonics. If missing    */
/*                                  DON'T turn on sonics.                   */
/*                                  Change AmpControlFlag to PowerSupply    */
/*                                  ControlFlag                             */
/*    2.170    06-17-98  LAM        chged TRIGGERLOSTDEFINE to 350(tenths of*/
/*                                  lb) added partcontact distance to check */
/*                                  for safety function                     */
/*    2.170    06-17-98  LAM        chged TRIGGERLOSTDEFINE to 350(tenths of*/
/*    2.171    06-18-98  LAM        made CA1 alarm consist from checkforsafety */
/*                                  and checkfortriggerlost, chged CA1 to EQ20 */
/*    2.172    06-22-98  BEKymer    Change structure member ActualForceMax  */
/*                                  to WeldForceMax                         */
/*                                  Collect max force in hold vs weld       */
/*    2.173    06-23-98  LAM        added check for cycle abort in check for*/
/*                                  safety to eliminate getting the recal alarm*/
/*    2.174    07-02-98  BJB        TRIGGERLOSTFORCE, TRIGGERLOSTDISTANCE   */
/*                                  moved to STATE.H                        */
/*    2.175    07-15-98  BEKymer    In CheckControlLimitsD move check for   */
/*                                  NC9 (ABSOLUTEMODE) outside of the test  */
/*                                  for ControlLimitsFlag                   */
/*    2.176    07-17-98  BEKymer    Add check for missing part in other     */
/*                                  modes besides time (StartSonic3).       */
/*    2.177    07-20-98  BEKymer    Dont add ABRAMPDOWNTIME to ActualAfter- */
/*                                  burstTime if there's an O/L because it  */
/*                                  makes the time 10 ms too large.         */
/*    2.178    08-10-98  BEKymer    Rename ActualCollapse to ActualTotal    */
/*                                  Collapse and add ACtualWeldCollapse     */
/*    2.179    08-14-98  BEKymer    Check for peak power while in TestABTme */
/*                                  so in case of O/L power data is avail   */
/*    2.180    09-02-98  BEKymer    Add argument to CHeckControlLimitsD to  */
/*                                  indicate if the encoder should still be */
/*                                  checked for working.                    */
/*    2.181    09-29-98  LAM        commented out actual trigger force      */
/*    2.182    10-01-98  BEKymer    Before updating new max force, make sure*/
/*                                  it's been there for 10 ms.              */
/*    2.183    10-13-98  BEKymer    In DisplayTestPower and DisplayWeldPower*/
/*                                  do the multiply before the divide so    */
/*                                  accuracy is maintained in 2X and 3X mode*/
/*    2.184    10-21-98  BEKymer    When sonics are turned off make sure the*/
/*                                  WeldForceMax is not 0. If it is, then   */
/*                                  average the current force with the New  */
/*                                  MaxForce(the initial value of force).   */
/*    2.185    10-29-98  BEKymer    In CheckControlLimitsD if the encoder   */
/*                                  value is large or negative create an    */
/*                                  encoder failed alarm.                   */
/*    2.186    11-06-98  BEKymer    Create variable ActualTriggerForce so   */
/*                                  it can be displayed if the define       */
/*                                  TRIGGER_FORCE_TEST is enabled in ready.c*/
/*    2.187    11-23-98  BEKymer    Add alarm CM22 (at the last minute)     */
/*    2.188    11-25-98  LAM        only check CM22 when an AED or AEF      */
/*    2.188    11-25-98  LAM        only check CM22 when an AED or AEF      */
/*    2.189    11-25-98  LAM        also check current force at the end of  */
/*                                  weld for CM22, used actualforceend variable */
/*    2.190    12-01-98  BEKymer    Make Total collapse and weld collapse   */
/*                                  equal if hold time is off               */
/*    2.191    12-04-98  BEKymer    Implement a quick fix so the reported   */
/*                                  collapse and weld force are more        */
/*                                  accurate                                */
/*    2.192    12-08-98  BEKymer    Initialize AccurateCollapse to 0 when   */
/*                                  StartSonic1 is called.                  */
/*    2.193    12-09-98  BEKymer    Initialize AccurateCollapse to 0 when   */
/*                                  StartSonic3 is called (I missed it).    */
/*    2.194    12-15-98  BEKymer    Set the WeldForceMax variable equal to  */
/*                                  ActualWeldForce so the S/R limits will  */
/*                                  actually work on the end force instead  */
/*                                  of the "max" force (with 9ms debounce). */
/*    2.195    03-15-99  LAM        added extra argument to set velocity and*/
/*                                  set force functions,added AEF_ACTUATOR  */
/*                                  define                                  */
/*    2.196    05-11-99  LAM        fixed warning on BITS for DIAB          */
/*    2.197    05-14-99  JZ         changed WeldForceMax to WeldForceEnd,   */
/*                                  ActualForceStart to SetForceA,          */
/*                                  PowerSupplyControlFlags to              */
/*                                  PSActControlFlags, ActualForceEnd to    */
/*                                  WeldForceEnd                            */
/*    2.197.1.2 07-12-99 JZ         enabled ActualFreqStart in StartSonic1  */
/*                                  added ErrorCode to EQ20                 */
/*    2.200     08-04-99 JZ         added ErrorCodeFlag                     */
/*    2.201     08-06-99 JZ         added RecordErrorCode                   */
/*                                  first arg. of SetPV typecasted to UINT16*/
/*    2.202     08-25-99 JZ         modified CM22 alarm so it doesn't occur */
/*                                  under all conditions                    */
/*    2.203     09-09-99 BEKymer    Cleared ForceStepReachedFlag in Start   */
/*                                  Sonic3 so 'No Force Step' alarm works   */
/*                                  in weld modes other than time           */
/*    2.204     09-09-99 BEKymer    Use PartContactFlag in CheckForSafety   */
/*    2.205     09-13-99 JZ         created PartContactHistoryFlag          */
/*                                  and ERRORCODE800_EQ20 and ERRORCODE900_EQ20 */
/*    2.206     09-13-99 BEKymer    Removed PartContactHistoryFlag          */
/*    2.207     09-14-99 LAM        Removed unused MovementStopFlag         */
/*    2.208     09-15-99 BEKymer    Modified reported force step time so it */
/*                                  is derived the same as amp stepping     */
/*    2.208.4.1 09-23-99 JLH        Enabled force step tic mark on graphs.  */
/*    2.211     10-14-99 JLH        correct 1ms error in AB delay           */
/*    2.212     10-25-99 BEKymer    Fix DCS # 3226 (force step tic mark)    */
/*                                  Remove some commented out code          */
/*    2.213     11-02-99 JZ         removed tabs                            */
/*    2.214     11-04-99 OFI        Changed 0x7d to defines                 */
/*    2.215     12-16-99 LAM        removed all unused references to profiling */
/*    2.216     06-27-00 SCM        Added variable AccurateAbsolute and added */
/*                                  conditional statements in the functions   */
/*                                  CheckControlLimitsD(), CheckSonics3A,     */
/*                                  CheckSonics3B() and CheckSonics5()        */
/*    2.217     06-28-00 SCM        Initialized AccurateAbsolute to zero      */
/*                                  in StartSonic1() and StartSonic3()        */
/*    2.218     06-28-00 BEKymer    changed MODEL to LEVEL                    */
/*    2.219     07-18-00 BEKymer    Added test for -0.25" collapse in function*/
/*                                   CheckForTriggerLost().  This is a carry  */
/*                                   over from 7.02.                          */
/*                                  Added functions to deal with DUPS data    */
/*                                   collection,                              */
/*                                  void StartDUPSDataCollection(void)        */
/*                                  BOOLEAN IsDUPSDataCollectionComplete(void)*/
/*    2.220     08-01-00 BEKymer    In TestABDly set or clear DUPSOkFlag      */
/*                                  In CheckSeek set or clear DUPSOkFlag      */
/*    2.221     08-09-00 BEKymer    Add pretrigger state to StartDUPSData...  */
/*                                  Modify StartDUPSData... so test works     */
/*                                  Modify IsDUPSDataColl.. to return TRUE if */
/*                                   there is no DUPS                         */
/*    2.222     08-09-00 BEKymer    Removed call to StartDUPSDataCollection() */
/*                                   in CheckSeek() because its done in       */
/*                                   StopSeek().                              */
/*    2.223     08-15-00 LAM        Need to update the overload flags         */
/*    2.224     09-05-00 LAM        added the powerup seek state              */
/*    2.225     09-18-00 LAM        added stopahold to catch dups overload info */                                                                          
/*    2.226     09-27-00 LAM        moved call to StartDUPSDataCollection     */
/*                                  to record alarm                           */                                                                          
/*    2.227     09-28-00 LAM        corrected logic in IsDUPSDataCollection   */
/*                                  Issue(3567)                               */
/*    2.228     09-28-00 LAM        initialize OLPending to NOT_PENDING       */
/*    2.229     04-11-01 BEKymer    Moved MAXWELDTIME, POWERDIV to ready.h    */
/*    2.230     04-20-01 BEKymer    Moved DEFAULT_MAXTIMEOUT to weldhold.h    */
/*    2.231     05-04-01 BEKymer    Added test in CheckForTriggerLost to make */
/*                                   sure trigger lost time will equal final  */
/*                                   reported weld time.                      */
/*                                                                            */
/*    2.232     02-14-03 BEKymer    Remove calls to TestActClr because its    */
/*                                   now done in the state machine            */
/*    2.233     09-08-03 BEKymer    Add StopAllSonic(), StartBrake() and      */
/*                                   CheckBrake()                             */
/*    2.234     03-12-04 VSharma    Changed 'Inp.ECycleAbort' to ECycleHistFlag.*/
/*    2.235     04-06-04 VSharma    Update power,frequency & time when        */
/*                                  EnergyBrakeOverload occured.              */
/*                                  Disable SVInterlock output in Hold state. */
/*    2.236     05-11-04 VSharma    Modified CheckBrake() for EBOverload alarm.*/
/*    2.237     05-17-04 VSharma    Removed SVOutOff() as SVOutOff is merged  */
/*                                   to SVOff().                              */
/*    2.238     08-27-04 BEKymer    Modified energy braking to use preset     */
/*                                   variable instead of BUC menu value.      */
/*    2.239     09-09-04 BEKymer    Add energy braking time to ActualWeldTime */
/*                                   at the end of each cycle                 */
/*    2.240     02-03-06 BKymer     Use actual weld set time, when PLCControl */
/*                                   is in effect                             */
/*    2.241     02-22-06 Bwadia     VerifySBL() added in CheckFrequencyLimits()*/
/*    2.242     03-12-07 NHAhmed    Changes for Amplitude for Scrub time      */
/*    2.243     05-23-07 NHAhmed    Changes Related to the G point(tick) on   */
/*                                  the Graph while in Ground Detect Menu.    */
/*    2.244                         Revision accidentially skipped            */
/*    2.245     07-10-07 LAM        removed pbreleaseon from startsonics3     */
/*    2.246     11-19-07 LAM        Merged 9.07 changes                       */
/*    2.247     09-02-08 NHAhmed    CleanUp for multi-language support.       */
/*    2.248     09-10-09 BEkymer    Add new define MICRO where needed         */
/*    2.249     09-22-09 YGupta     Added Support for MICRO Actuator.         */
/*    2.250     10-07-09 YGupta     Modified to support MaxTimeout for all	  */
/*	    							modes other then time.					  */
/*    2.250.1.0 10-26-13 GBG        Offset signal was removed from StartSonic1(),          */
/*                                  StartSonic3(), StopAllsonic() and                      */
/*                                  AlStopSonics() functions.                              */
/*                                                                                         */
/*                                                                                         */
                                                                           
/*----------------------------- DESCRIPTION ----------------------------------*/

/* This module contains the code for the weld state, hold state.              */


/*----------------------------- PSEUDO CODE --------------------------------*/


/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define ABRAMPDOWNTIME        10              /* Time from Allan Roberts - 20 ms   08-08-96  */
                                              /* Changed to 10 ms by Kevin Klein   04-16-97  */
#define AMPSTEPTRIGGERTIME     2              /* If amp trigger occurs before this time-alarm*/
#define ENCODERFAILTIME       25              /* Time a minimum distance must be reached in  */
#define ENCODERDETECTDISTANCE 50              /* Minimum distance within ENCODERFAILTIME     */
#define FORCE_DEBOUNCE_TIME    9              /* Time (ms) a new force exists before being   */
                                              /* considered a new max force (should be less  */
                                              /* than minimum weld time so a value is always */
                                              /* displayed)                                  */


#define ALTERNATEHOLDTIME     10              /* Time to catch overloads if hold disabled    */

#define AMPWINDOW 2                           // I'm going to open a window +/- 2% relative
                                              // to Amp1 and Amp2
                                    
/*------------------------------ INCLUDES ----------------------------------*/

#include "names.h"
#include "portable.h"
#include "error.h"
#include "state.h"
#include "menu.h"
#include "preset.h"
#include "weld_obj.h"
#include "alarms.h"
#include "weldhold.h"
#include "timer.h"
#include "statedrv.h"
#include "digout.h"
#include "outports.h"
#include "led.h"
#include "mansensr.h"
#include "util.h"
#include "ready.h"
#include "menu7a.h"
#include "dups_api.h"



/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

static SINT16   SonicStepTimer;
static SINT16   SonicTimer, HoldTimer, ScrubTimer;
static SINT16   WeldForceTimer;
static SINT16   SeekDelay;
static UINT16   DelayStartFlag = TRUE;

static BOOLEAN  WeldForceFlag, ScrubTimerFlag;

enum OL_PENDING{
      NOT_PENDING,
      WELD_OL,
      SEEK_OL,
      AB_OL};

static enum OL_PENDING OlPending = NOT_PENDING;

static SINT32   RampStartValue, RampStopValue, RampDiff;
static SINT32   RampTime, RampRunningTime;
static SINT32   EnergyBrakeTimer;
static SINT32   AmpRampTime, AmpRampTime10, AmpRampTime25, AmpRampTime50, AmpRampTime95;

static void UpdateOLType(SINT32 OverloadReason);

BOOLEAN         SeekEndFlag, RampUpDirection, RampEndFlag;
BOOLEAN         GroundDetectFlag;

SINT16 TriggerLostTimerFlag, TriggerLostTimerID;
SINT16 TriggerDelayTimer;

UINT16 EncoderFailTimer;
UINT16 ActualABDelay;
UINT16 MaxForceDebounce;
UINT16 NewMaxForce;

SINT32 TriggerLostTime;/* Time (after 150ms) when trigger was declared lost */
SINT32 TriggerLostForce;/* Force when trigger was declared lost             */
SINT32 ActualAfterburstTime;
SINT32 ActualHoldTime;
SINT32 ActualSeekTime;
SINT32 ABOverloadPower;
SINT32 AccurateCollapse;
SINT32 AccurateAbsolute;
SINT32 AmpRamp;
SINT32 NextRampValue;
SINT32 EBOverloadTimer;
SINT32 EBOverloadPower;
SINT32 EBOverloadFreq;  

BOOLEAN TriggerLostHistoryFlag, TriggerLostFlag;
BOOLEAN AmpStepReachedFlag = FALSE, ForceStepReachedFlag = FALSE, HornReturnFlag = TRUE;
SINT32 CurrentPower;                   /* weldhold, ready  */
UINT8 CollectEnergyFlag = FALSE;
SINT32  ActualTriggerForce;

void VerifySBL(void); 
extern UINT8 PortRegisterB; // U79   j.b

extern UINT16 AlarmCounter;
extern WELD_OBJECT *MsDataPtr;
extern SINT32 Distance1;               /* Distance 1-3 used to determine part contact*/


extern SINT32   EncoderPos;
extern SINT32   AccumulatedEnergy, EnergyInJoules, EnergyCalc;
extern SINT32   CurrentForce;
extern UINT16   CycleTimer;
extern UINT16   TestKeyRepeat;
extern UINT16   TestModeAllowed;
extern UINT16   ThermalOLFlag;
extern SINT32   CurrentFreqIn;        /* Value being read by 7890          */
extern UINT32   CurrentPowerIn;         /* Value being read by 7890          */
extern UINT32   CurrentAmpIn;
extern SINT32   EnergyNeeded;
extern UINT16   Update5ms;
extern SETUPS_Ver800   RunningPreset;
extern SETUPS_Ver800   MaxLimit;
extern SETUPS_Ver800   MinLimit;
extern CONFIGSETUP CurrentSetup;
extern UINT8    AETrigger;
extern INBITS   Inp;
extern WELD_DATA WeldingResults;
extern UINT16   HornReturnCount;
extern UINT16   PartContactFlag;       
extern BOOLEAN  CycleAbort;
extern SINT16   PeakPower;
extern enum WELDSTATES WeldState;
extern BUCMENU_800 BUCMenuRAM;
extern BOOLEAN ECycleHistFlag;
extern BOOLEAN MissingPartFlag;

/* DUPS related stuff */

DUPS_WELDSTATUS WeldOLStatus;
DUPS_WELDSTATUS SeekOLStatus;
DUPS_WELDSTATUS ABOLStatus;



//- ---------------------------  MY WINDOW -------------------------------

SINT32 *A_Setup=&RunningPreset.Amp1;            
SINT32 *B_Setup=&RunningPreset.Amp2;                  
SINT32 *LastA=&WeldingResults.ActualAmplitudeStart; 
SINT32 *LastB=&WeldingResults.ActualAmplitudeEnd; 

//-------------------------------- CODE ----------------------------------


void DisplayTestPower(SINT16 Power) 
{
   SINT16 LedPower;

   if (CurrentSetup.TestMultiplier == TESTTIMEx1) {
      LedPower = Power;
   }
   else if (CurrentSetup.TestMultiplier == TESTTIMEx2) {
      LedPower = Power * 2;
   }
   else if (CurrentSetup.TestMultiplier == TESTTIMEx3) {
      LedPower = Power * 3;
   }
   LedPower /= POWERDIV;
   UpdateBarGraph(LedPower);
}



void DisplayWeldPower(SINT16 Power) 
{
   SINT16 LedPower;

   if (CurrentSetup.TimeMultiplier == WELDTIMEx1) {
      LedPower = Power;
   }
   else if (CurrentSetup.TimeMultiplier == WELDTIMEx2) {
      LedPower = Power * 2;
   }
   else if (CurrentSetup.TimeMultiplier == WELDTIMEx3) {
      LedPower = Power * 3;
   }
   LedPower /= POWERDIV;
   UpdateBarGraph(LedPower);
}



BOOLEAN CheckForTriggerLost(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check to see if trigger has been lost.  It will take */
/*  the passed value (Force-the current required force) and compare it with */
/*  the current actual force.  If the required force is less then the       */
/*  actual force for more then 150ms a Trigger Lost error has occured.  A   */
/*  TRUE will be returned if trigger has been lost, a FALSE will be         */
/*  returned if all is okay.                                                */
/*                                                                          */
/*  If trigger was lost and then restored within the 150ms all is okay and  */
/*  the 150ms timer is reset.                                               */
/*                                                                          */
/*  Also, this function will check for MAX force.                           */
/*                                                                          */
/*  NOTE: As agreed to by B. Kymer, C. Linley, N. Galer, B.Jalbert, N. Wu,  */
/*        and L. Markure, trigger will not be considered lost until the     */
/*        actual force is at or below the part contact force, which is      */
/*        currently defined the same as the minimum trigger force.          */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN  RetVal = FALSE;          /* Return value, assume okay for now   */
   SINT32   TRSLostTime;

   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == MICRO) ) {
      if (CurrentForce < MinLimit.TriggerForce) {
         if (TriggerLostHistoryFlag == FALSE) { /* Was trigger already lost    */
            StartUpTimer(TRIGGERLOSTTIMER);
            TriggerLostHistoryFlag = TRUE;
         }
         else {
            TRSLostTime = GetUpTimer(TRIGGERLOSTTIMER);
            if (TRSLostTime > (SINT32) TRIGGERLOSTTIME) {/* See if time to great  */
               RetVal = TRUE;           /* FALSE means trigger lost error NOW! */
               if (TriggerLostTime == 0) {   /* Test to ensure only updated once */
                  TriggerLostTime = GetUpTimer(SONICSTIMER);/* Get cycle time right now    */
               }
               TriggerLostForce = CurrentForce;          /* Get force as of right now   */
            }
         }
      }
      else {                            /* Trigger Ok now, but was it ok before*/
         if (TriggerLostHistoryFlag == TRUE) {
            ResetUpTimer(TRIGGERLOSTTIMER);
            TriggerLostHistoryFlag = FALSE;
         }
      }

/*---  Check for safety condition [less then 35 lbs with 1/4" travel]  ---*/

      if ( (CurrentForce < TRIGGERLOSTFORCE) && 
           (EncoderPos > (WeldingResults.ActualTriggerDistance + (SINT32) TRIGGERLOSTDISTANCE)) ) {
           SVOff();                                  /* Immediately turn off SV  */
           RecordErrorCode( ERRORCODE200_EQ20 );
           RecordAlarm(EQ20);                        /* Record alarm             */
           AbortFlag = TRUE;                         /* Abort state sequence     */
      }

/*---  Check for safety condition [lifting off the part 1/4"]  ---*/

      if (WeldingResults.ActualTriggerDistance > (SINT32) TRIGGERLOSTDISTANCE) {
         if (EncoderPos < (WeldingResults.ActualTriggerDistance - (SINT32) TRIGGERLOSTDISTANCE) ) {
              SVOff();                                  /* Immediately turn off SV  */
              RecordErrorCode( ERRORCODE400_EQ20 );
              RecordAlarm(EQ20);                        /* Record alarm             */
              AbortFlag = TRUE;                         /* Abort state sequence     */
         }
      }

/*-----  Check to see if a new maximum force has been reached  -----*/

      if (WeldState == HOLDTIMESTATE) {
         if (CurrentForce > WeldingResults.HoldForceMax) {
            if (MaxForceDebounce == 0) {
               MaxForceDebounce = 1;
               NewMaxForce = (UINT16)CurrentForce;
            }
            else if (MaxForceDebounce >= FORCE_DEBOUNCE_TIME) { /* We have a new max force now */
               WeldingResults.HoldForceMax = NewMaxForce;
               MaxForceDebounce = 0;
            }
            else {
               MaxForceDebounce++;
            }
         }
         else {
            MaxForceDebounce = 0;
         }
      }
      else {
         if (CurrentForce > WeldingResults.WeldForceEnd) {
            if (MaxForceDebounce == 0) {
               MaxForceDebounce = 1;
               NewMaxForce = (UINT16)CurrentForce;
            }
            else if (MaxForceDebounce >= FORCE_DEBOUNCE_TIME) { /* We have a new max force now */
               WeldingResults.WeldForceEnd = NewMaxForce;
               MaxForceDebounce = 0;
            }
            else {
               MaxForceDebounce++;
            }
         }
         else {
            MaxForceDebounce = 0;
         }
      }
   }
   else{  /* AE trigger lost  */
      if (AETrigger == FALSE) {
         if (TriggerLostHistoryFlag == FALSE) { /* Was trigger already lost    */
            StartUpTimer(TRIGGERLOSTTIMER);
            TriggerLostHistoryFlag = TRUE;
         }
         else {
            TRSLostTime = GetUpTimer(TRIGGERLOSTTIMER);
            if (TRSLostTime > (SINT32) TRIGGERLOSTTIME) {/* See if time to great  */
               RetVal = TRUE;              /* FALSE means trigger lost error NOW! */
               if (TriggerLostTime == 0) {    /* Test to ensure only updated once */
                  TriggerLostTime = GetUpTimer(SONICSTIMER);/* Get cycle time right now    */
               }
               TriggerLostForce = 0;    /* 0lbs for AE   */
            }
         }
      }
      else {                            /* Trigger Ok now, but was it ok before*/
         if (TriggerLostHistoryFlag == TRUE) {
            ResetUpTimer(TRIGGERLOSTTIMER);
            TriggerLostHistoryFlag = FALSE;
         }
      }
    }
   return(RetVal);
}



void CheckForSafety(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check to see if horn has traveled 1/4" after part    */
/*  contact and still have not built up at least 35 lbs of force.  If this  */
/*  occurs, the cycle will be aborted and an alarm will be generated.  This */
/*  function will be called while waiting for trigger.  Once trigger has    */
/*  been reached then CheckForTriggerLost will be called.                   */
/*  returned if all is okay.                                                */
/*                                                                          */
/*  Note:  The variable Distance1 is set in spidd.c when part contact is    */
/*         determined.                                                      */
/*                                                                          */
/****************************************************************************/
{
   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == MICRO) ) {
      if ( (CurrentForce < TRIGGERLOSTFORCE) &&
           (CycleAbort == FALSE) &&
           (PartContactFlag == TRUE) &&
           (EncoderPos > (Distance1 + (SINT32) TRIGGERLOSTDISTANCE)) ) {
           SVOff();                                  /* Immediately turn off SV  */
           RecordErrorCode( ERRORCODE900_EQ20 );
           RecordAlarm(EQ20);                        /* Record alarm             */
           AbortFlag = TRUE;                         /* Abort state sequence     */
      }
   }
}


void EnterTrigDly(void)
/****************************************************************************/
/*                                                                          */
/* This function will do the delay after trigger is reached.  It will first */
/* try to set the force to the trigger force to keep the force constant on  */
/* the part.                                                                */
/*                                                                          */
/****************************************************************************/
{
   SetPV((UINT16)RunningPreset.WeldForce, TRG_TO_FORCE_A);   
   TriggerDelayTimer = StartTimer(RunningPreset.TriggerDelay,
                                  &TriggerDelayFlag, 40);
}



void ExitTrigDly(void)
/****************************************************************************/
/*                                                                          */
/* This function will deal with the force after the trigger delay has timed */
/* out.  It will set the force to the weld force value.                     */
/*                                                                          */
/****************************************************************************/
{
   SetPV((UINT16)RunningPreset.WeldForce, TRG_TO_FORCE_A);
}



void CheckControlLimitsD(UINT16 EncoderCheck)
/****************************************************************************/
/*                                                                          */
/* This function will check the control limits.  If they are globally off   */
/* then only the max timeout will be checked.  If they are globally on,     */
/* then each one will be checked to see if it is on.  If it is on, then the */
/* values will be checked to determine if the cycle should be aborted.  In  */
/* any case the max timeout will be checked.  If max timeout is disabled,   */
/* unless is not allowed in the current weld mode, a default value will be  */
/* used.  If enabled then the user defined value will be used.              */
/* The passed argument 'EncoderCheck' will be used to determine if the      */
/* encoder should be checked for movement.  If it should be checked (TRUE)  */
/* and the value is less than ENCODERDETECTDISTANCE then alarm EQ1 will be  */
/* recorded.                                                                */
/*                                                                          */
/*  moved out of states. The final data was not being updated correctly     */
/*  and the next cycles weld time was shorter.                              */
/*--------------------------------------------------------------------------*/
{

   CheckControlLimits();                  /* Call non distance checks first */

/*-----  Check Encoder to be sure its still working correctly  -----*/

   if (EncoderCheck == TRUE) {
      if (EncoderPos < ENCODERDETECTDISTANCE) {
         EncoderFailTimer++;
         if (EncoderFailTimer >= ENCODERFAILTIME) {
            RecordAlarm(EQ1);
         }
      }
   }

/*-- Check for Absolute Distance before trigger (Absolute Mode only)  --*/
/*-  If the EncoderPos value is larger than MaxLimit.AbsDist (could    -*/
/*-  also be negative, which isn't allowed here either) then the       -*/
/*-  encoder is not working correctly, so make alarm Encoder Failed    -*/


   if (RunningPreset.WeldMode == ABSOLUTEMODE) {
      if ( (EncoderPos >= RunningPreset.AbsDist) &&
           (WeldingResults.ActualTriggerDistance == 0) ) { 
           if (EncoderPos > MaxLimit.AbsDist) {
              RecordAlarm(EQ1);           /* If not triggered yet */
           }
           else {
              RecordAlarm(NC9);           /* If not triggered yet */
           }
      }
   }
   else {
      if (RunningPreset.ControlLimitsFlag == TRUE) { /* Control limits on ? */


/*----  Next check for Absolute Distance Cutoff (All mode but Absolute) ----*/

         if ((RunningPreset.ABSCutoffFlag & /*BSCutoff.BitMask*/BIT0) == 0) {
            if (EncoderPos >= RunningPreset.ABSCutoffDist) {
               if (WeldingResults.ActualTriggerDistance != 0) { 
                  AccurateAbsolute = EncoderPos;
                  RecordAlarm(W6);            /* If already triggered */
               }
               else {
                  RecordAlarm(NC9);           /* If not triggered yet */
               }
            }
         }   
      }
   }


/*-----  First see if Control limits are even enabled  -----*/

   if (RunningPreset.ControlLimitsFlag == TRUE) {


/*-----  Next check for Collapse Distance Cutoff  -----*/

      if ( ((RunningPreset.ColCutoffFlag & /*ABSCutoff.BitMask*/BIT0) == 0) &&
            (RunningPreset.WeldMode != COLLAPSEMODE) ) {
         if (WeldingResults.ActualTriggerDistance != 0){ /* If already triggered */
            if ((EncoderPos - WeldingResults.ActualTriggerDistance) >= RunningPreset.ColCutoffDist) {
               RecordAlarm(W9);
               AccurateCollapse = EncoderPos - WeldingResults.ActualTriggerDistance;
            }
         }
      }   
   }
}



void CheckControlLimits(void)
/****************************************************************************/
/*                                                                          */
/* This function will check the control limits.  If they are globally off   */
/* then only the max timeout will be checked.  If they are globally on,     */
/* then each one will be checked to see if it is on.  If it is on, then the */
/* values will be checked to determine if the cycle should be aborted.  In  */
/* any case the max timeout will be checked.  If max timeout is disabled,   */
/* unless is not allowed in the current weld mode, a default value will be  */
/* used.  If enabled then the user defined value will be used.              */
/*                                                                          */
/*  moved out of states. The final data was not being updated correctly     */
/*  and the next cycles weld time was shorter.                              */
/*--------------------------------------------------------------------------*/
{
   SINT32  TempTimeValue;

   TempTimeValue = GetUpTimer(SONICSTIMER);

/*-----  Now see if Control limits are even enabled  -----*/

   if (RunningPreset.ControlLimitsFlag == TRUE) {


/*-----  Now check for Peak Power Cutoff  -----*/

      if ((RunningPreset.PeakPwrCutoffFlag & /*PeakPowerCutoff.BitMask*/BIT0) == 0) {
         if ( (RunningPreset.PeakPwrCutoff <= PeakPower) &&
              (RunningPreset.WeldMode != PKPOWERMODE) ) {
            RecordAlarm(W5);
         }
      }


/*-----  Next deal with TEC mode (Energy compensation)                 -----*/

      if ( (RunningPreset.EnergyCompFlag == TRUE)     &&
           (RunningPreset.ControlLimitsFlag == TRUE)  &&   /*TRUE =On*/
           (CurrentSetup.ControlLevel >= LEVEL_e)      &&
           (CycleAbort == FALSE)                      &&
           (RunningPreset.WeldMode == TIMEMODE) ) {
         if (EnergyInJoules-3 >= RunningPreset.EnergyML) {
            if ((TempTimeValue - 1) > RunningPreset.WeldTime) {
               RecordAlarm(W7);
            }
            else if (TempTimeValue == RunningPreset.WeldTime) {
               SonicsAbort = TRUE;               /* Stop sonics             */
            }
         }
         if (EnergyInJoules-3 >= RunningPreset.EnergyPL) {
            RecordAlarm(W2);
         }
      }
   }

/*-----  For safety, now check on max timeout (Control Limits on/off)  -----*/

   if ((WeldState == WELDTIMESTATE) || (WeldState == WELDTIME2STATE)){
      if ((/*MaxTimeout.mode*/(ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE |GRDDETECTMODE) & RunningPreset.WeldMode) == RunningPreset.WeldMode) {
         if (TempTimeValue >= RunningPreset.MaxTimeout) { 
            RecordAlarm(CM3);
         }
      }
   }
   
/***   ***   Now some test code to determine the starting ramp   ***   ***/

   AmpRampTime++;
   if ( ((CurrentAmpIn/10) >= 95) && (AmpRampTime95 == 0) ) AmpRampTime95 = AmpRampTime;
   if ( ((CurrentAmpIn/10) >= 50) && (AmpRampTime50 == 0) ) AmpRampTime50 = AmpRampTime;
   if ( ((CurrentAmpIn/10) >= 25) && (AmpRampTime25 == 0) ) AmpRampTime25 = AmpRampTime;
   if ( ((CurrentAmpIn/10) >= 10) && (AmpRampTime10 == 0) ) AmpRampTime10 = AmpRampTime;
}



void CheckCycleAborts(void)
/****************************************************************************/
/*                                                                          */
/* This function will check the cycle aborts.  If they are globally on      */
/* then each one will be checked to see if it is on.  If it is on, then the */
/* values will be checked to determine if the cycle should be aborted.      */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*  moved out of states. The final data was not being updated correctly     */
/*  and the next cycles weld time was shorter.                              */
/*--------------------------------------------------------------------------*/
{

/*-----  First check for External Cycle Abort   -----*/

   if (ECycleHistFlag == TRUE) {
      if (GetUpTimer(SONICSTIMER) >= 1) {
         RecordAlarm(CM15);           /* After trigger  */
      }
      else {
         RecordAlarm(NC7);            /* Before trigger */
      }
   }

/*-----  Next see if Cycle Aborts are even enabled  -----*/

   if (RunningPreset.CycleAbortFlag == TRUE) {


/*-----  Next check for Ground Detect Cutoff  -----*/

/*--------------------------------------------------------------------------*/
/*  Think about a timer when ground detect is active.  If ground detect     */
/*  goes away before the timer expires, then ignore the ground detect input.*/
/*  This will help ensure we stop sonics only when really needed and not    */
/*  when there is a small hole in the material.  (See Bill Surprenant)      */
/*  Must check ground detect input before trigger in ground detect mode     */
/*--------------------------------------------------------------------------*/
      if ((RunningPreset.GndDetectFlag == TRUE) &&
              (RunningPreset.WeldMode != GRDDETECTMODE)){
         if (Inp.GndDet == TRUE) {
            if (GetUpTimer(SONICSTIMER) >= 1) {
               RecordAlarm(CM2);           /* After trigger  */
            }
            else {
               RecordAlarm(NC12);          /* Before trigger */
            }
         }
      }
   }
/* need to check for ground detect before trigger in ground detect mode */
   if((RunningPreset.WeldMode == GRDDETECTMODE) &&
      (Inp.GndDet == TRUE)) {
      if (GetUpTimer(SONICSTIMER) < 1) {
         RecordAlarm(NC12);          /* Before trigger */
      }
   }
}



void  CheckEnergyComp(void)
{
/*-----  First see if Control limits are even enabled  -----*/

   if ( (RunningPreset.ControlLimitsFlag == TRUE) &&
        (RunningPreset.EnergyCompFlag == TRUE)    &&
        (CurrentSetup.ControlLevel >= LEVEL_e)     &&
        (RunningPreset.WeldMode == TIMEMODE)      &&
        (CycleAbort == FALSE) ) {
           if (WeldingResults.TotalEnergy < RunningPreset.EnergyML) {
              RecordAlarm(CM21);
           }
           if ((WeldingResults.ActualWeldTime - 1) > RunningPreset.WeldTime) {
              RecordAlarm(W7);
           }
   }
}

         

void CheckForForceStepping(void)
/***************************************************************************/
/*                                                                         */
/*   This function will check the various force triggers and see if it is  */
/*   time to switch to the second force.  If it is time, then the switch   */
/*   will be done.                                                         */
/*                                                                         */
/*   It will then check the various amplitude triggers and see if it is    */
/*   time to switch to the second amplitude.  If it is time, then the      */
/*   switch will be done.                                                  */
/*                                                                         */
/***************************************************************************/
{
   if ( ((RunningPreset.Force2Flag & BIT0) == BIT0) && (ForceStepReachedFlag == FALSE) ) {
      switch (RunningPreset.Force2Flag) {
         case ((UINT16)~BIT2):                    /* Stepping enabled on time          */
            if ((WeldForceTimer != FALSE) && (WeldForceFlag == FALSE)) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = RunningPreset.ForceTrigTimeValue;
               WeldForceTimer = 0;      /* Turn off flag to prevent further checking*/
            }
            break;

         case ((UINT16)~BIT3):                    /* Stepping enabled on energy        */
            if (RunningPreset.ForceTrigEnerValue <= EnergyInJoules) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }   
            break;

         case ((UINT16)~BIT4):                    /* Stepping enabled on peak power    */
            if (RunningPreset.ForceTrigPowerValue <= PeakPower) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;

         case ((UINT16)~BIT5):                    /* Stepping enabled on collapse dist */
            if (RunningPreset.ForceTrigColValue <= (EncoderPos -WeldingResults.ActualTriggerDistance)) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;

         case ((UINT16)~BIT6):                    /* Stepping enabled on amplitude     */
            if (RunningPreset.Amp1 > RunningPreset.Amp2) {
               if (RunningPreset.ForceTrigAmpValue >= CurrentAmpIn) { /* Negative slope */
                  SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
                  ForceStepReachedFlag = TRUE;
                  MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
               }
            }
            else {
               if (RunningPreset.ForceTrigAmpValue <= CurrentAmpIn) { /* Positive slope */
                  SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
                  ForceStepReachedFlag = TRUE;
                  MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
               }
            }
            break;

         case ((UINT16)~BIT7):                    /* Stepping enabled on absolute dist */
            if (RunningPreset.ForceTrigAbsValue <= (EncoderPos -WeldingResults.ActualTriggerDistance)) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;

         case FORCE_STEP_AT_EXTERNAL:                     /* Stepping enabled on external in   */
            if (Inp.ExternalTrigger == TRUE) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;

         default:
            break;
      }
   }
   if ( ((RunningPreset.Amp2Flag & BIT0) == BIT0) &&  /* If stepping on and */
         (CurrentSetup.AmpControl == TRUE)        &&  /* amp is internal &  */
         (AmpStepReachedFlag == FALSE) ) {            /* not stepped yet    */

/* save ampA(amplitudestart) to final results before switching to ampB  */
/* must subtract 1 from time(power supply delays sonics for 1ms */
      switch (RunningPreset.Amp2Flag) {
         case ((UINT16)~BIT2):                 /* Stepping enabled on time          */
            if (GetUpTimer(SONICSTIMER) >= RunningPreset.AmpTrigTimeValue) {
               if (GetUpTimer(SONICSTIMER) < AMPSTEPTRIGGERTIME) {
                  RecordAlarm(NC10);
               }
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = RunningPreset.AmpTrigTimeValue;
            }
            break;
   
         case ((UINT16)~BIT3):                 /* Stepping enabled on energy        */
            if (RunningPreset.AmpTrigEnerValue <= EnergyInJoules) {
               if (GetUpTimer(SONICSTIMER) < AMPSTEPTRIGGERTIME) {
                  RecordAlarm(NC10);
               }
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) -1);
            }
            break;
   
         case ((UINT16)~BIT4):                 /* Stepping enabled on peak power    */
            if (RunningPreset.AmpTrigPowerValue <= PeakPower) {
               if (GetUpTimer(SONICSTIMER) < AMPSTEPTRIGGERTIME) {
                  RecordAlarm(NC10);
               }
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;
   
         case ((UINT16)~BIT5):                 /* Stepping enabled on collapse dist */
            if (RunningPreset.AmpTrigColValue <= (EncoderPos - WeldingResults.ActualTriggerDistance)) {

/*- This check removed to fix DCS # 2045.  By definition of collapse, the -*/
/*- step condition could not occur before trigger because there can be no -*/
/*- collapse before trigger.                                               */

//               if (GetUpTimer(SONICSTIMER) < AMPSTEPTRIGGERTIME) {
//                  RecordAlarm(NC10);
//               }

               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;
   
         case ((UINT16)~BIT6):                 /* Stepping enabled on force         */
            if (RunningPreset.WeldForce > RunningPreset.Force2) {
               if (RunningPreset.AmpTrigForceValue >= CurrentForce) { /* Negative slope */
                  AmpStepReachedFlag = TRUE;
                  if (GetUpTimer(SONICSTIMER) < AMPSTEPTRIGGERTIME) {
                     RecordAlarm(NC10);
                  }
                  WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
                  SetCurrentAmp(RunningPreset.Amp2);
                  MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
               }
               if (RunningPreset.AmpTrigForceValue <= CurrentForce) { /* Positive slope */
                  AmpStepReachedFlag = TRUE;
                  if (GetUpTimer(SONICSTIMER) < AMPSTEPTRIGGERTIME) {
                     RecordAlarm(NC10);
                  }
                  WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
                  SetCurrentAmp(RunningPreset.Amp2);
                  MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
               }
            }
            break;
   
         case AMP_STEP_AT_EXTERNAL:                  /* Stepping enabled on external in   */
            if (Inp.ExternalTrigger == TRUE) {
               if (GetUpTimer(SONICSTIMER) < AMPSTEPTRIGGERTIME) {
                  RecordAlarm(NC10);
               }
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;

         default:
            break;
      }
   }
}



void StartSonic1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with turning on the sonics for     */
/*  the first weld pressure.  Two conditions can exist: 1) Amplitude step  */
/*  is enabled or 2) Amplitude step is disabled.                           */
/*                                                                         */
/*  Amplitude step enabled:  SonicStepTimer=timer id for time of step one  */
/*                           SonicTimer=timer id for total sonics on time  */
/*                                                                         */
/*  Amplitude step disabled: SonicStepTimer=timer id total sonics on time  */
/*                           SonicTimer=timer id for total sonics on time  */
/*                                                                         */
/***************************************************************************/
{
   UINT16  FirstTimeValue;

/*--   Before doing anything, make 1 final check for missing part  --*/

   WeldingResults.ActualTriggerDistance = EncoderPos;      /* Save position for coll calc */
   AccurateCollapse = 0;
   AccurateAbsolute = 0;
   MissingPartFlag = CheckForMissingPartMin();
   if (MissingPartFlag == TRUE) {       /* If TRUE, alarm and abort cycle  */
      RecordAlarm(NC8);
   }
   else {                               /* If FALSE, then proceed normally */
      CollectEnergyFlag = TRUE;
      DelayStartFlag = TRUE;
      CoolValOn();   

/*----- Deal with the new cycle trigger stuff -----*/
/* Enable frequency offset */
      
/*      if(RunningPreset.FreqOffsetFlag == TRUE)                */              
/*         SetCurrentFreqOffset(RunningPreset.FreqOffset);      */  

   /* check for encoder failed (but only if cycle not aborted) */
      if (CycleAbort == FALSE) {
         if (( (CurrentSetup.Actuator == AED) ||
              (CurrentSetup.Actuator == AEF) ||
              (CurrentSetup.Actuator == MICRO) ) && (EncoderPos < ENCODERDETECTDISTANCE))
            RecordAlarm(EQ1);
      }

      StartUpTimer(SONICSTIMER);
      WeldingResults.ActualFreqStart = CurrentFreqIn; /* Get starting frequency  */
      CheckFrequencyLimits();

      PeakPower = 0;                           /* Reset last peak power */

      SetCurrentAmp(RunningPreset.Amp1);       /* Initial amplitude           */
      PSRun();                                 /* Start sonics                */
      AmpRampTime = 0;
      AmpRampTime10 = 0;
      AmpRampTime25 = 0;
      AmpRampTime50 = 0;
      AmpRampTime95 = 0;
      
/**  ** This timer is the total length of time Sonics are on  **  **/

      FirstTimeValue = RunningPreset.WeldTime; /* Control limits off so no Energy Comp */

/*---- Deal with amplitude stepping (Consider Energy Comp)  ----*/

      if (RunningPreset.ControlLimitsFlag == TRUE) {
         if (RunningPreset.EnergyCompFlag == TRUE) {
            FirstTimeValue = ((RunningPreset.WeldTime) + ((RunningPreset.WeldTime ) >> 1)); /* Assume Step is off, Energy Comp is ON */
            if (FirstTimeValue >= MAXWELDTIME + 1) FirstTimeValue=MAXWELDTIME; 
         }
         else {
            FirstTimeValue = RunningPreset.WeldTime;   /* Assume Step is off, Energy Comp is off   */
         }
      }

      SonicTimer = StartTimer(FirstTimeValue, &WTimeFlag, 7);
      if (SonicTimer == FAILED1) {
         LogError(TIMERFAILED1);
         SonicTimer = 0;
      }
      else if (SonicTimer == FAILED2) {
         LogError(TIMERFAILED2);
         SonicTimer = 0;
      }
      AmpStepReachedFlag = FALSE;
      ForceStepReachedFlag = FALSE;

      if ((RunningPreset.Amp2Flag & BIT0) == BIT0) { /* See if amplitude step is on */
         switch (RunningPreset.Amp2Flag) {
            case ((UINT16)~BIT2):                    /* Stepping enabled on time          */
               FirstTimeValue = (RunningPreset.AmpTrigTimeValue);/* Step is on   */
               break;
   
            case ((UINT16)~BIT3):                    /* Stepping enabled on energy        */
               break;
   
            case ((UINT16)~BIT4):                    /* Stepping enabled on peak power    */
               break;
   
            case ((UINT16)~BIT5):                    /* Stepping enabled on collapse dist */
               break;
   
            case ((UINT16)~BIT6):                    /* Stepping enabled on amplitude     */
               break;
   
            case AMP_STEP_AT_EXTERNAL:                       /* Stepping enabled on external in   */
               break;
     
            default:
               break;
         }
      }
   
/**  ** This timer is the start up holdoff time  **  **/

//   HoldOffTimer = StartTimer(50, &HoldOffTimerFlag, 20);


/**  ** This timer is the length of time for Sonic1 state  **  **/

      SonicStepTimer = StartTimer(FirstTimeValue, &StepTimeFlag, 17);
      if (SonicStepTimer == FAILED1) {
         LogError(TIMERFAILED1);
         SonicStepTimer = 0;
      }
      else if (SonicStepTimer == FAILED2) {
         LogError(TIMERFAILED2);
         SonicStepTimer = 0;
      }


/**  ** This timer is the time before the second weld force starts  **  **/

      if ((RunningPreset.Force2Flag & BIT0) == BIT0) {
         WeldForceTimer = StartTimer(RunningPreset.ForceTrigTimeValue, &WeldForceFlag, 19);
         if (WeldForceTimer == FAILED1) {
            LogError(TIMERFAILED1);
            WeldForceTimer = 0;
         }
         else if (WeldForceTimer == FAILED2) {
            LogError(TIMERFAILED2);
            WeldForceTimer = 0;
         }
      }
      else {
         WeldForceTimer = FALSE;
         WeldForceFlag = FALSE;
      }
   }
}

   

void StartSonic1A(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with turning on the sonics for     */
/*  CONTINUOUS mode.                                                       */
/*                                                                         */
/***************************************************************************/
{
   SetSAS();                                /* Output Sonics Active signal */
   StartUpTimer(SONICSTIMER);
   
   WeldingResults.ActualFreqStart = CurrentFreqIn; /* Get starting frequency  */
   CheckFrequencyLimits();
   PeakPower = 0;                           /* Reset last peak power */
   WeldingResults.ActualWeldTime = 0;      /* Reset last actual weld time */

   SetCurrentAmp(RunningPreset.Amp1);       /* Initial amplitude           */
   PSRun();                                 /* Start sonics                */

/**  ** This timer is the start up holdoff time  **  **/

//   HoldOffTimer = StartTimer(50, &HoldOffTimerFlag, 20);
   WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
}



void CheckSonics1D(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to sonic state 2.                                       */
/*                                                                         */
/***************************************************************************/
{
   if(DelayStartFlag == TRUE){
      DelayStartFlag = FALSE;
      SetSAS();
      ActualTriggerForce = CurrentForce;
   }
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);

   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/

   TriggerLostFlag = CheckForTriggerLost();
}


void CheckSonics1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to sonic state 2.                                       */
/*                                                                         */
/***************************************************************************/
{
   if(DelayStartFlag == TRUE){
      DelayStartFlag = FALSE;
      SetSAS();
      ActualTriggerForce = CurrentForce;
   }
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimits();

   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/

   TriggerLostFlag = CheckForTriggerLost();
}


void CheckSonics1A(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should turn off sonics in CONTINUOUS mode only.                        */
/*                                                                         */
/*  Note:  This function must check for continuous power rating being      */
/*         exceeded.                                                       */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
}




void StartSonic2(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the weld during the second    */
/*  weld pressure.  When this state is reached either of two things        */
/*  happened: Thing1-the first amplitude step has timed out, or Thing2-    */
/*  the total sonics time has expired.  We know the difference by checking */
/*  RunningPreset.Amp2Flag.  If RunningPreset.Amp2Flag BIT0 is TRUE then   */
/*  Thing1 happened.  If it is FALSE then Thing2 happened.                 */
/*                                                                         */
/***************************************************************************/
{

   if ( ((RunningPreset.Amp2Flag & BIT0) == BIT0) &&  /* If stepping on and */
         (CurrentSetup.AmpControl == TRUE)        &&  /* amp is internal &  */
         (AmpStepReachedFlag == FALSE) ) {            /* not stepped yet    */

/* save ampA before switching to ampB */
/* must subtract 1 from time(power supply delays sonics for 1ms */
      switch (RunningPreset.Amp2Flag) {
         case ((UINT16)~BIT2):                 /* Stepping enabled on time          */
//3-25-98   if (GetUpTimer(SONICSTIMER) > RunningPreset.AmpTrigTimeValue) {
            if (GetUpTimer(SONICSTIMER) >= RunningPreset.AmpTrigTimeValue) {
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = RunningPreset.AmpTrigTimeValue;
            }
            break;
   
         case ((UINT16)~BIT3):                 /* Stepping enabled on energy        */
            if (RunningPreset.AmpTrigEnerValue <= EnergyInJoules) {
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;
   
         case ((UINT16)~BIT4):                 /* Stepping enabled on peak power    */
            if (RunningPreset.AmpTrigPowerValue <= PeakPower) {
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;
   
         case ((UINT16)~BIT5):                 /* Stepping enabled on collapse dist */
            if (RunningPreset.AmpTrigColValue <= (EncoderPos -WeldingResults.ActualTriggerDistance)) {
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;
   
         case ((UINT16)~BIT6):                 /* Stepping enabled on force         */
            if (RunningPreset.AmpTrigForceValue <= CurrentForce) {
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;
   
         case ((UINT16)~BIT7):                 /* Stepping enabled on absolute dist */
            if (RunningPreset.AmpTrigAbsValue <= (EncoderPos -WeldingResults.ActualTriggerDistance)) {
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;
   
         case AMP_STEP_AT_EXTERNAL:                  /* Stepping enabled on external in   */
            if (Inp.ExternalTrigger == TRUE) {
               AmpStepReachedFlag = TRUE;
               WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
               SetCurrentAmp(RunningPreset.Amp2);
               MsDataPtr->AmpStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;
   
         default:
            break;
      }
   }

/** This entire  if and switch was added to fix DCS # 3226 on 10-25-99  **/

   if ( ((RunningPreset.Force2Flag & BIT0) == BIT0) && (ForceStepReachedFlag == FALSE) ) {
      switch (RunningPreset.Force2Flag) {
         case ((UINT16)~BIT2):                    /* Stepping enabled on time          */
            if ((WeldForceTimer != FALSE) && (WeldForceFlag == FALSE)) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = RunningPreset.ForceTrigTimeValue;
               WeldForceTimer = 0;      /* Turn off flag to prevent further checking*/
            }
            break;

         case ((UINT16)~BIT3):                    /* Stepping enabled on energy        */
            if (RunningPreset.ForceTrigEnerValue <= EnergyInJoules) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }   
            break;

         case ((UINT16)~BIT4):                    /* Stepping enabled on peak power    */
            if (RunningPreset.ForceTrigPowerValue <= PeakPower) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;

         case ((UINT16)~BIT5):                    /* Stepping enabled on collapse dist */
            if (RunningPreset.ForceTrigColValue <= (EncoderPos -WeldingResults.ActualTriggerDistance)) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;

         case ((UINT16)~BIT6):                    /* Stepping enabled on amplitude     */
            if (RunningPreset.Amp1 > RunningPreset.Amp2) {
               if (RunningPreset.ForceTrigAmpValue >= CurrentAmpIn) { /* Negative slope */
                  SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
                  ForceStepReachedFlag = TRUE;
                  MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
               }
            }
            else {
               if (RunningPreset.ForceTrigAmpValue <= CurrentAmpIn) { /* Positive slope */
                  SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
                  ForceStepReachedFlag = TRUE;
                  MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
               }
            }
            break;

         case ((UINT16)~BIT7):                    /* Stepping enabled on absolute dist */
            if (RunningPreset.ForceTrigAbsValue <= (EncoderPos -WeldingResults.ActualTriggerDistance)) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;

         case FORCE_STEP_AT_EXTERNAL:                     /* Stepping enabled on external in   */
            if (Inp.ExternalTrigger == TRUE) {
               SetPV((UINT16)RunningPreset.Force2, FORCE_A_TO_FORCE_B);
               ForceStepReachedFlag = TRUE;
               MsDataPtr->ForceStepAtTime = (GetUpTimer(SONICSTIMER) - 1);
            }
            break;

         default:
            break;
      }
   }
}



void CheckSonics2D(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state (TIME MODE only).                   */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/

   TriggerLostFlag = CheckForTriggerLost();
}




void CheckSonics2(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state (TIME MODE only).                   */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimits();
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/

   TriggerLostFlag = CheckForTriggerLost();
}



void StartSonic3(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with turning on the sonics for     */
/*  the first weld pressure.  Two conditions can exist: 1) Amplitude step  */
/*  is enabled or 2) Amplitude step is disabled.                           */
/*                                                                         */
/*  Amplitude step enabled:  SonicStepTimer=timer id for time of step one  */
/*                           SonicTimer=timer id for total sonics on time  */
/*                                                                         */
/*  Amplitude step disabled: SonicStepTimer=timer id total sonics on time  */
/*                           SonicTimer=timer id for total sonics on time  */
/*                                                                         */
/*  NOTE: ENERGY MODE, ABSOLUTE MODE, COLLAPSE MODE, PEAK POWER MODE &     */
/*  GROUND DETECT ONLY                                                     */
/*                                                                         */
/***************************************************************************/
{
   UINT16  FirstTimeValue;

/*--   Before doing anything, make 1 final check for missing part  --*/

   WeldingResults.ActualTriggerDistance = EncoderPos;      /* Save position for coll calc */
   AccurateCollapse = 0;
   AccurateAbsolute = 0;
   MissingPartFlag = CheckForMissingPartMin();
   if (MissingPartFlag == TRUE) {       /* If TRUE, alarm and abort cycle  */
      RecordAlarm(NC8);
   }
   else {                               /* If FALSE, then proceed normally */
      if (RunningPreset.WeldMode == ENERGYMODE) {
         EnergyCalc = (100000 / CurrentSetup.PSWatt);
         if (RunningPreset.WeldEnergy >= 2000) { /* Prevent overflow, lose a little accuracy */
            EnergyNeeded = RunningPreset.WeldEnergy * EnergyCalc;  /* Convert to energy units   */
         }
         else {      /* Overflow not a problem here, keep accuracy instead  */
            EnergyNeeded = RunningPreset.WeldEnergy * 100000; /* 1/10's of millejoules */
            EnergyNeeded /= CurrentSetup.PSWatt;    /* Convert to energy units   */
         }
      }   
      CollectEnergyFlag = TRUE;
      DelayStartFlag = TRUE;

/*----- Deal with the new cycle trigger stuff -----*/
/* Enable frequency offset */
/*      if(RunningPreset.FreqOffsetFlag == TRUE)              */
/*         SetCurrentFreqOffset(RunningPreset.FreqOffset);    */ 
   
      CoolValOn();

/* check for encoder failed (but only if cycle not aborted) */

      if (CycleAbort == FALSE) {
         if ( ((CurrentSetup.Actuator == AEF) || (CurrentSetup.Actuator == AEF)) && (EncoderPos < ENCODERDETECTDISTANCE))
            RecordAlarm(EQ1);
      }
      GroundDetectFlag = FALSE;
      ScrubTimerFlag = FALSE;
      StartUpTimer(SONICSTIMER);
      WeldingResults.ActualFreqStart = CurrentFreqIn; /* Get starting frequency  */
      CheckFrequencyLimits();
      PeakPower = 0;                           /* Reset last peak power */

      MissingPartFlag = CheckForMissingPartMin();
   
      SetCurrentAmp(RunningPreset.Amp1);       /* Initial amplitude           */
      PSRun();                                 /* Start sonics                */
      FirstTimeValue = (RunningPreset.MaxTimeout + 1);        /* use user supplied value  */
      
      if ((/*MaxTimeout.mode*/(ENERGYMODE | PKPOWERMODE | COLLAPSEMODE | ABSOLUTEMODE |GRDDETECTMODE) & RunningPreset.WeldMode) ==   /* If weld mode allows        */
            RunningPreset.WeldMode) {                     /* timeout, then and only then*/
         FirstTimeValue = (RunningPreset.MaxTimeout + 1); /* use user supplied value    */
      }
      else {
         FirstTimeValue = (DEFAULT_MAXTIMEOUT + 1);
      }
   
/**  ** This timer is the total length of time Sonics are on  **  **/

      SonicTimer = StartTimer(FirstTimeValue, &WTimeFlag, 7);
      if (SonicTimer == FAILED1) {
         LogError(TIMERFAILED1);
         SonicTimer = 0;
      }
      else if (SonicTimer == FAILED2) {
         LogError(TIMERFAILED2);
         SonicTimer = 0;
      }
      AmpStepReachedFlag = FALSE;
      ForceStepReachedFlag = FALSE;
   
      if ((RunningPreset.Amp2Flag & BIT0) == BIT0) { /* See if amplitude step is on */
         switch (RunningPreset.Amp2Flag) {
            case ((UINT16)~BIT2):              /* Stepping enabled on time          */
               FirstTimeValue = (RunningPreset.AmpTrigTimeValue);/* Step is on   */
               break;
   
            case ((UINT16)~BIT3):              /* Stepping enabled on energy        */
               break;
   
            case ((UINT16)~BIT4):              /* Stepping enabled on peak power    */
               break;
   
            case ((UINT16)~BIT5):              /* Stepping enabled on absolute dist */
               break;
   
            case ((UINT16)~BIT6):              /* Stepping enabled on amplitude     */
               break;
   
            case AMP_STEP_AT_EXTERNAL:                 /* Stepping enabled on external in   */
               break;
       
            default:
               break;
        }
      }
   
/**  ** This timer is the start up holdoff time  **  **/

//   HoldOffTimer = StartTimer(50, &HoldOffTimerFlag, 20);


/**  ** This timer is the length of time for Sonic1 state  **  **/

      SonicStepTimer = StartTimer(FirstTimeValue, &StepTimeFlag, 17);
      if (SonicStepTimer == FAILED1) {
         LogError(TIMERFAILED1);
         SonicStepTimer = 0;
      }
      else if (SonicStepTimer == FAILED2) {
         LogError(TIMERFAILED2);
         SonicStepTimer = 0;
      }


/**  ** This timer is the time before the second weld force starts  **  **/

      if ((RunningPreset.Force2Flag & BIT0) == BIT0) {
         WeldForceTimer = StartTimer(RunningPreset.ForceTrigTimeValue, &WeldForceFlag, 19);
         if (WeldForceTimer == FAILED1) {
            LogError(TIMERFAILED1);
            WeldForceTimer = 0;
         }
         else if (WeldForceTimer == FAILED2) {
            LogError(TIMERFAILED2);
            WeldForceTimer = 0;
         }
      }
      else {
         WeldForceTimer = FALSE;
         WeldForceFlag = FALSE;
      }
   }
}



void CheckSonics3D(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state 2 (ENERGY MODE only).               */
/*                                                                         */
/***************************************************************************/
{
   if(DelayStartFlag == TRUE){
      DelayStartFlag = FALSE;
      SetSAS();
      ActualTriggerForce = CurrentForce;
   }
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (AccumulatedEnergy >= EnergyNeeded) {
      SonicsAbort = TRUE;         /* Stop sonics, energy value reached     */
   }
//   if (GetUpTimer(SONICSTIMER) >= RunningPreset.MaxTimeout) {
//      SonicsAbort = TRUE;         /* Stop sonics, max time value reached    */
//   }   
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics3(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state 2 (ENERGY MODE only).               */
/*                                                                         */
/***************************************************************************/
{
   if(DelayStartFlag == TRUE){
      DelayStartFlag = FALSE;
      SetSAS();
      ActualTriggerForce = CurrentForce;
   }
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimits();
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (AccumulatedEnergy >= EnergyNeeded) {
      SonicsAbort = TRUE;         /* Stop sonics, energy value reached     */
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics3A(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state 2.                                  */
/*                                                                         */
/*  ABSOLUTE MODE ONLY                                                     */
/*                                                                         */
/***************************************************************************/
{
   if(DelayStartFlag == TRUE){
      DelayStartFlag = FALSE;
      SetSAS();
      ActualTriggerForce = CurrentForce;
   }
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (EncoderPos >= RunningPreset.AbsDist) {
      AccurateAbsolute = EncoderPos;
      SonicsAbort = TRUE;         /* Stop sonics, distance value reached    */
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics3B(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state 2.                                  */
/*                                                                         */
/*  COLLAPSE MODE ONLY                                                     */
/*                                                                         */
/***************************************************************************/
{
   if(DelayStartFlag == TRUE){
      DelayStartFlag = FALSE;
      SetSAS();
      ActualTriggerForce = CurrentForce;
   }
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (EncoderPos > WeldingResults.ActualTriggerDistance) {
      if ((EncoderPos - WeldingResults.ActualTriggerDistance) >= RunningPreset.ColDist) {
         SonicsAbort = TRUE;         /* Stop sonics, collapse value reached */
         AccurateCollapse = EncoderPos - WeldingResults.ActualTriggerDistance;
      }
   }
   else {  /* Here, as per conversation with Kevin K., start a 10 ms       */
           /* timer.  If the collapse is still negative, then create some  */
           /* kind of an alarm.  We guess this will only happened once in  */
           /* the life of the product, long after we remember talking      */
           /* about it.       BEKymer   08-12-96 (after Kevin returned     */
           /* from Mid Ohio)                                               */
      ;
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics3CD(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state 2.                                  */
/*                                                                         */
/*  PEAK POWER MODE ONLY                                                   */
/*                                                                         */
/***************************************************************************/
{
   if(DelayStartFlag == TRUE){
      DelayStartFlag = FALSE;
      SetSAS();
      ActualTriggerForce = CurrentForce;
   }
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (PeakPower >= RunningPreset.PeakPwr) {
      SonicsAbort = TRUE;         /* Stop sonics, distance value reached    */
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics3C(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state 2.                                  */
/*                                                                         */
/*  PEAK POWER MODE ONLY                                                   */
/*                                                                         */
/***************************************************************************/
{
   if(DelayStartFlag == TRUE){
      DelayStartFlag = FALSE;
      SetSAS();
      ActualTriggerForce = CurrentForce;
   }
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimits();
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (PeakPower >= RunningPreset.PeakPwr) {
      SonicsAbort = TRUE;         /* Stop sonics, distance value reached    */
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics8D(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state 2.                                  */
/*                                                                         */
/*  GROUND DETECT MODE ONLY                                                */
/*                                                                         */
/***************************************************************************/
{
   if(DelayStartFlag == TRUE){
      DelayStartFlag = FALSE;
      SetSAS();
      ActualTriggerForce = CurrentForce;
   }
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (Inp.GndDet == TRUE) {
      if (GroundDetectFlag == FALSE) {
         GroundDetectFlag = TRUE;
         if ((RunningPreset.ScrubTime     != 0) &&
              (RunningPreset.ScrubTimeFlag == 0)) //Scrub Time(s) isn't Off
         {
            ScrubTimer = StartTimer(RunningPreset.ScrubTime,
                                    &ScrubTimerFlag, 60);
            SetCurrentAmp(RunningPreset.AmpScrubTime);
            MsDataPtr->ScrubStartAtTime = GetUpTimer(SONICSTIMER);
         }
      }
      else if (ScrubTimerFlag == FALSE) {
         SonicsAbort = TRUE;         /* Stop sonics, ground detect is active*/
      }
   }
   else if (GroundDetectFlag == TRUE) { /* Had Grd Detect, but lost it, check anyway */
      if (ScrubTimerFlag == FALSE) {
         SonicsAbort = TRUE;         /* Stop sonics, ground detect is active*/
      }
   }   
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics8(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking to decide when we    */
/*  should move on to stop sonic state 2.                                  */
/*                                                                         */
/*  GROUND DETECT MODE ONLY                                                */
/*                                                                         */
/***************************************************************************/
{
   if(DelayStartFlag == TRUE){
      DelayStartFlag = FALSE;
      SetSAS();
      ActualTriggerForce = CurrentForce;
   }
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimits();
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (Inp.GndDet == TRUE) {
      if (GroundDetectFlag == FALSE) {
         GroundDetectFlag = TRUE;
         if ((RunningPreset.ScrubTime     != 0) &&
              (RunningPreset.ScrubTimeFlag == 0))  //Scrub Time(s) isn't Off
         {
            ScrubTimer = StartTimer(RunningPreset.ScrubTime,
                                    &ScrubTimerFlag, 60);
            SetCurrentAmp(RunningPreset.AmpScrubTime);
            MsDataPtr->ScrubStartAtTime = GetUpTimer(SONICSTIMER);
         }
      }
      else if (ScrubTimerFlag == FALSE) {
         SonicsAbort = TRUE;         /* Stop sonics, ground detect is active*/
      }
   }
   else if (GroundDetectFlag == TRUE) { /* Had Grd Detect, but lost it, check anyway */
      if (ScrubTimerFlag == FALSE) {
         SonicsAbort = TRUE;         /* Stop sonics, ground detect is active*/
      }
   }   
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics4D(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the weld during the second    */
/*  weld pressure.  When this state is reached either of two things        */
/*  happened: Thing1-the first amplitude step has timed out, or Thing2-    */
/*  the total sonics time has expired.  We know the difference by checking */
/*  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then */
/*  Thing1 happened.  If it is FALSE then Thing2 happened.                 */
/*                                                                         */
/*  ENERGY MODE ONLY                                                       */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (AccumulatedEnergy >= EnergyNeeded) {
      SonicsAbort = TRUE;         /* Stop sonics, energy value reached     */
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics4(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the weld during the second    */
/*  weld pressure.  When this state is reached either of two things        */
/*  happened: Thing1-the first amplitude step has timed out, or Thing2-    */
/*  the total sonics time has expired.  We know the difference by checking */
/*  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then */
/*  Thing1 happened.  If it is FALSE then Thing2 happened.                 */
/*                                                                         */
/*  ENERGY MODE ONLY                                                       */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimits();
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (AccumulatedEnergy >= EnergyNeeded) {
      SonicsAbort = TRUE;         /* Stop sonics, energy value reached     */
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics5(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the weld during the second    */
/*  weld pressure.  When this state is reached either of two things        */
/*  happened: Thing1-the first amplitude step has timed out, or Thing2-    */
/*  the total sonics time has expired.  We know the difference by checking */
/*  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then */
/*  Thing1 happened.  If it is FALSE then Thing2 happened.                 */
/*                                                                         */
/*  ABSOLUTE DISTANCE MODE ONLY                                            */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (EncoderPos >= RunningPreset.AbsDist) {
      AccurateAbsolute = EncoderPos;
      SonicsAbort = TRUE;         /* Stop sonics, distance value reached    */
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics6(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the weld during the second    */
/*  weld pressure.  When this state is reached either of two things        */
/*  happened: Thing1-the first amplitude step has timed out, or Thing2-    */
/*  the total sonics time has expired.  We know the difference by checking */
/*  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then */
/*  Thing1 happened.  If it is FALSE then Thing2 happened.                 */
/*                                                                         */
/*  COLLAPSE DISTANCE MODE ONLY                                            */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (EncoderPos > WeldingResults.ActualTriggerDistance) {
      if ((EncoderPos - WeldingResults.ActualTriggerDistance) >= RunningPreset.ColDist) {
         SonicsAbort = TRUE;         /* Stop sonics, collapse value reached */
         AccurateCollapse = EncoderPos - WeldingResults.ActualTriggerDistance;
      }
   }
   else {  /* Here, as per conversation with Kevin K., start a 10 ms       */
           /* timer.  If the collapse is still negative, then create some  */
           /* kind of an alarm.  We guess this will only happened once in  */
           /* the life of the product, long after we remember talking      */
           /* about it.       BEKymer   08-12-96 (after Kevin returned     */
           /* from Mid Ohio)                                               */
      ;
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics7D(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the weld during the second    */
/*  weld pressure.  When this state is reached either of two things        */
/*  happened: Thing1-the first amplitude step has timed out, or Thing2-    */
/*  the total sonics time has expired.  We know the difference by checking */
/*  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then */
/*  Thing1 happened.  If it is FALSE then Thing2 happened.                 */
/*                                                                         */
/*  PEAK POWER MODE ONLY                                                   */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (PeakPower >= RunningPreset.PeakPwr) {
      SonicsAbort = TRUE;         /* Stop sonics, distance value reached    */
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics7(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the weld during the second    */
/*  weld pressure.  When this state is reached either of two things        */
/*  happened: Thing1-the first amplitude step has timed out, or Thing2-    */
/*  the total sonics time has expired.  We know the difference by checking */
/*  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then */
/*  Thing1 happened.  If it is FALSE then Thing2 happened.                 */
/*                                                                         */
/*  PEAK POWER MODE ONLY                                                   */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimits();
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (PeakPower >= RunningPreset.PeakPwr) {
      SonicsAbort = TRUE;         /* Stop sonics, distance value reached    */
   }
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics9D(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the weld during the second    */
/*  weld pressure.  When this state is reached either of two things        */
/*  happened: Thing1-the first amplitude step has timed out, or Thing2-    */
/*  the total sonics time has expired.  We know the difference by checking */
/*  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then */
/*  Thing1 happened.  If it is FALSE then Thing2 happened.                 */
/*                                                                         */
/*  GROUND DETECT MODE ONLY                                                */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimitsD(FALSE);
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (Inp.GndDet == TRUE) {
      if (GroundDetectFlag == FALSE) {
         GroundDetectFlag = TRUE;
         if ((RunningPreset.ScrubTime     != 0) &&
              (RunningPreset.ScrubTimeFlag == 0))  //Scrub Time(s) isn't Off
         {
            ScrubTimer = StartTimer(RunningPreset.ScrubTime,
                                    &ScrubTimerFlag, 60);
            SetCurrentAmp(RunningPreset.AmpScrubTime);
            MsDataPtr->ScrubStartAtTime = GetUpTimer(SONICSTIMER);
         }
      }   
      else if (ScrubTimerFlag == FALSE) {
         SonicsAbort = TRUE;         /* Stop sonics, ground detect is active*/
      }
   }
   else if (GroundDetectFlag == TRUE) { /* Had Grd Detect, but lost it, check anyway */
      if (ScrubTimerFlag == FALSE) {
         SonicsAbort = TRUE;         /* Stop sonics, ground detect is active*/
      }
   }   
   TriggerLostFlag = CheckForTriggerLost();
}



void CheckSonics9(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the weld during the second    */
/*  weld pressure.  When this state is reached either of two things        */
/*  happened: Thing1-the first amplitude step has timed out, or Thing2-    */
/*  the total sonics time has expired.  We know the difference by checking */
/*  RunningPreset.Amp2Flag.  If BIT0 is set in RunningPreset.Amp2Flag then */
/*  Thing1 happened.  If it is FALSE then Thing2 happened.                 */
/*                                                                         */
/*  GROUND DETECT MODE ONLY                                                */
/*                                                                         */
/***************************************************************************/
{
   if(Update5ms >= 3){
      CheckFrequencyLimits();
      DisplayWeldPower(CurrentPowerIn);
      CheckCycleAborts();
   }
   if (CurrentPowerIn > PeakPower) {
      PeakPower = CurrentPowerIn;
      MsDataPtr->PeakPowerAtTime = GetUpTimer(SONICSTIMER);
   }
   CheckControlLimits();
   CheckForForceStepping();     /*----  Deal with Force stepping Here  ----*/
   if (Inp.GndDet == TRUE) {
      if (GroundDetectFlag == FALSE) {
         GroundDetectFlag = TRUE;
         if ((RunningPreset.ScrubTime     != 0) &&
             (RunningPreset.ScrubTimeFlag == 0))  //Scrub Time(s) isn't Off
         {
            ScrubTimer = StartTimer(RunningPreset.ScrubTime,
                                    &ScrubTimerFlag, 60);
            SetCurrentAmp(RunningPreset.AmpScrubTime);
            MsDataPtr->ScrubStartAtTime = GetUpTimer(SONICSTIMER);
         }
      }
      else if (ScrubTimerFlag == FALSE) {
         SonicsAbort = TRUE;         /* Stop sonics, ground detect is active*/
      }
   }
   else if (GroundDetectFlag == TRUE) { /* Had Grd Detect, but lost it, check anyway */
      if (ScrubTimerFlag == FALSE) {
         SonicsAbort = TRUE;         /* Stop sonics, ground detect is active*/
      }
   }   
   TriggerLostFlag = CheckForTriggerLost();
}



void StopSonic1(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with whatever needs dealing with   */
/*  after the first amplitude step.                                        */
/*                                                                         */
/***************************************************************************/
{
}



void StopSonic2(void)
/***************************************************************************/
/*                                                                         */
/*  This replaces the original StopSonic2 function which has been renamed  */
/*  to StopAllSonic().  This function will determine if energy braking     */
/*  is on.  If braking is not on then StopAllSonic() is called and         */
/*  everything is as it was.  If energy braking is on then this function   */
/*  exits and does nothing.  The energy braking state (which is then next) */
/*  will call StopAllSonic() after the proper amp ramp has outputted.      */
/*                                                                         */
/***************************************************************************/
{
   if (RunningPreset.EnergyBraking == FALSE)  /* Not on, proceed as before */
      StopAllSonic();
}



void StopAllSonic(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with turning off the sonics after  */
/*  the second weld pressure. In timemode only.                            */
/*                                                                         */
/*  Total collapse will be updated here in case there is no hold time.  If */
/*  hold time is on, total collapse will be rewritten.                     */
/*                                                                         */
/***************************************************************************/
{
   UINT16  FirstTimeValue, EBTimeValue;

   PSIdle();                                /* Stop sonics                 */
   ClearSAS();                              /* Output Sonics Active signal */
 
   if (AccurateAbsolute == 0) {
      WeldingResults.ActualWeldAbs = EncoderPos;
      WeldingResults.ActualTotalAbs = EncoderPos;
   }
   else {
      WeldingResults.ActualWeldAbs = AccurateAbsolute;
      WeldingResults.ActualTotalAbs = AccurateAbsolute;
   }

   if (AccurateCollapse == 0) {
      WeldingResults.ActualWeldCollapse = EncoderPos - WeldingResults.ActualTriggerDistance; /* Determine collapse    */
      WeldingResults.ActualTotalCollapse = WeldingResults.ActualWeldCollapse;
   }
   else {
      WeldingResults.ActualWeldCollapse = AccurateCollapse;
      WeldingResults.ActualTotalCollapse = AccurateCollapse;
   }
   CollectEnergyFlag = FALSE;
   if(AmpStepReachedFlag == FALSE)
      WeldingResults.ActualAmplitudeStart = ((CurrentAmpIn + 5) / POWERDIV);
   else {
      WeldingResults.ActualAmplitudeEnd = ((CurrentAmpIn + 5) / POWERDIV);
      MsDataPtr->PrintBottomFlags &= (~AMPSTEPALARMMASK); /* Amp step reached, so remove alarm flag */
   }

   if(ForceStepReachedFlag == TRUE)
      MsDataPtr->PrintBottomFlags &= (~FORCESTEPALARMMASK); /* Force step reached, so remove alarm flag */

   if ((WeldingResults.PSActControlFlags & BIT0) == BIT0) {  /* If internal amp control only */
      *LastA = *A_Setup;
      *LastB = *B_Setup;
   }
   else {
      *LastA = 0;
      *LastB = 0;
   }
   
/*--------------------------------------------------------------------------*/

   WeldingResults.PeakPower = (PeakPower);
  /* SetCurrentFreqOffset(0); */    /* clear frequency offset  */                            
   if (WTimeFlag == TRUE) {
      StopTimer(SonicTimer);
   }

/*--------------------------------------------------------------------------*/
/* The following approach will be used to determine if the actual weld time */
/* should be reported or if the requested weld time will be used instead.   */
/*                                                                          */
/*     If trigger has been reached, (it must have been reached or we would  */
/*     not be here, right!), (SonicsAbort == TRUE or CycleAbort == TRUE)    */
/*     then use actual time.  If (SonicsAbort == FALSE and CycleAbort       */
/*     == FALSE) then use the requested time.  If energy comp is turned     */
/*     on and time is extended use actual time.  If time is not extended    */
/*     then use the requested time.   If PLCControl is in effect then use   */
/*     the actual time also.                                                */
/*                                                                          */
/*     Note: We need to CheckEnergyComp() first because this is what will   */
/*     create the W7 alarm which we want to check in TIMEMODE.  We get the  */
/*     actual time before we call CheckEnergyComp() because it needs the    */
/*     time to decide if time was actually extended.                        */
/*                                                                          */
/*--------------------------------------------------------------------------*/

   if (AccumulatedEnergy > 20000) {
      WeldingResults.TotalEnergy = (AccumulatedEnergy / (100000 / CurrentSetup.PSWatt));
   }
   else {
      WeldingResults.TotalEnergy = (AccumulatedEnergy * CurrentSetup.PSWatt) / 100000;
   }
   WeldingResults.ActualWeldTime = GetUpTimer(SONICSTIMER);
   CheckEnergyComp();

   if (RunningPreset.EnergyBraking == 1) EBTimeValue = RunningPreset.EBTime;
   else EBTimeValue = 0;

   switch (RunningPreset.WeldMode) {
      case TIMEMODE:               /* TIME mode only           */
         FirstTimeValue = ((RunningPreset.WeldTime) + ((RunningPreset.WeldTime ) >> 1)); /* Energy Comp ON, time extended */
         if (FirstTimeValue >= MAXWELDTIME) {
            FirstTimeValue = MAXWELDTIME;
         }

         if ( (SonicsAbort == TRUE) || (CycleAbort == TRUE) ||
              (CurrentSetup.PLCControlFlag == TRUE) ) {
            WeldingResults.ActualWeldTime = GetUpTimer(SONICSTIMER);
            if ((WeldingResults.ActualWeldTime - 1) == RunningPreset.WeldTime) {
               WeldingResults.ActualWeldTime = RunningPreset.WeldTime;
            }
            if ((WeldingResults.ActualWeldTime + 1) >= FirstTimeValue) {
               WeldingResults.ActualWeldTime = FirstTimeValue;
            }
         }
         else if ( (RunningPreset.ControlLimitsFlag == FALSE) ||
                   (RunningPreset.EnergyCompFlag == FALSE) ) {
            WeldingResults.ActualWeldTime = RunningPreset.WeldTime + EBTimeValue;
         }
         else if ((WeldingResults.Warnings & W7) == (W7 & ALARMCODEMASK)) {
            WeldingResults.ActualWeldTime = GetUpTimer(SONICSTIMER);
            if ((WeldingResults.ActualWeldTime - 1) >= FirstTimeValue) {
               WeldingResults.ActualWeldTime = FirstTimeValue + EBTimeValue;
            }
            if ((WeldingResults.ActualWeldTime + 1) >= FirstTimeValue) {
               WeldingResults.ActualWeldTime = FirstTimeValue + EBTimeValue;
            }
         }
         else {
            WeldingResults.ActualWeldTime = RunningPreset.WeldTime + EBTimeValue;
         }
         break;

      default:                     /* All other modes but TIME */
         if ((WeldingResults.CycleModifiedAlarms & CM3) == (CM3 & ALARMCODEMASK)) {
            WeldingResults.ActualWeldTime = RunningPreset.MaxTimeout + EBTimeValue;
         }
         else {
            WeldingResults.ActualWeldTime = GetUpTimer(SONICSTIMER) + EBTimeValue;
         }
         break;

   }

   DisplayWeldPower(PeakPower);

   WeldingResults.ActualFreqEnd = CurrentFreqIn;     /* Get final frequency   */
   CheckFrequencyLimits();
   WeldingResults.FrequencyChange = WeldingResults.ActualFreqEnd - WeldingResults.ActualFreqStart;
   WeldingResults.WeldForceEnd = (UINT16) CurrentForce;


/*--  Now make sure there the final max force is greater than trigger  --*/

   if ( (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == AEF) ||
        (CurrentSetup.Actuator == MICRO) ) 
   {

      if (CurrentForce < RunningPreset.TriggerForce) 
      {
         WeldingResults.WeldForceEnd = (UINT16) CurrentForce;
         if ((RunningPreset.Force2Flag & BIT0) == BIT0){ 
            if (RunningPreset.Force2 >= RunningPreset.TriggerForce){ 
               RecordAlarm(CM22);
            }   
         }
         else{
            RecordAlarm(CM22);
         }   
      }   
         
   }

/*-- The next line is a quick fix for Kevin  12-15-98  --*/

/*   WeldingResults.WeldForceEnd = WeldingResults.WeldForceEnd;  */

/*-- End of quick fix  --*/

   if (CurrentSetup.ExtraCooling == FALSE) {
      CoolValOff();
   }
}



void AlStopSonics(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with turning off the sonics after  */
/*  an alarm has been generated.                                           */
/*                                                                         */
/***************************************************************************/
{
   PSIdle();                                /* Stop sonics                 */
   ClearSAS();                              /* Output Sonics Active signal */
   WeldingResults.ActualWeldCollapse = EncoderPos - WeldingResults.ActualTriggerDistance; /* Determine collapse    */
   CollectEnergyFlag = FALSE;

   if(AmpStepReachedFlag == TRUE)
      MsDataPtr->PrintBottomFlags &= (~AMPSTEPALARMMASK); /* Amp step reached, so remove alarm flag */
   if(ForceStepReachedFlag == TRUE)
      MsDataPtr->PrintBottomFlags &= (~FORCESTEPALARMMASK); /* Force step reached, so remove alarm flag */

   if ((WeldingResults.PSActControlFlags & BIT0) == BIT0) {  /* If internal amp control only */
      *LastA = *A_Setup;
      *LastB = *B_Setup;
   }
   else {
      *LastA = 0;
      *LastB = 0;
   }


   /* SetCurrentFreqOffset(0); */    /* clear frequency offset  */                            
// removed test for stoptimer 3/10/98   if ((StopTimer != 0) && (WTimeFlag == TRUE)) {
   if (WTimeFlag == TRUE) {
      StopTimer(SonicTimer);
   }
   WeldingResults.ActualWeldTime = (GetUpTimer(SONICSTIMER) - 1);
   if(RunningPreset.Amp2Flag == (UINT16)~BIT2){
      WeldingResults.ActualWeldTime++;
   }

   WeldingResults.PeakPower = (PeakPower);
   if (AccumulatedEnergy > 20000) {
      WeldingResults.TotalEnergy = (AccumulatedEnergy / (100000 / CurrentSetup.PSWatt));
   }
   else {
      WeldingResults.TotalEnergy = (AccumulatedEnergy * CurrentSetup.PSWatt) / 100000;
   }
   DisplayWeldPower(PeakPower);

   WeldingResults.ActualFreqEnd = CurrentFreqIn;     /* Get final frequency   */
   CheckFrequencyLimits();
   WeldingResults.FrequencyChange = WeldingResults.ActualFreqEnd - WeldingResults.ActualFreqStart;
   CheckEnergyComp();
   TriggerLostFlag = FALSE;

   if(Inp.OL == TRUE) {  /* do not abort overloads */
      PSReset();
   }
      
/*-- The next line is a quick fix for Kevin  12-15-98  --*/

   WeldingResults.WeldForceEnd = (UINT16) CurrentForce;
/*   WeldingResults.WeldForceEnd = WeldingResults.WeldForceEnd;   */

/*-- End of quick fix  --*/

}



void AlStopTest(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will deal with turning off the sonics in      */
/*  test mode after an overload alarm has been generated.                   */
/*                                                                          */
/****************************************************************************/
{
   PSIdle();                                 /* Stop sonics                 */
   StartTestFlag = FALSE;
   DisplayTestPower(PeakPower);
   if (TestKeyRepeat == TRUE)
      TestModeAllowed = FALSE;               /* Disallow more test mode     */
}                                            /* repeat vs pressing again    */



void StartBrake(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the start of energy braking.  */
/*  It will clear the timer and set the amplitude to the first value of    */
/*  calculated ramp using the specified end value in the BUC menu variable */
/*  the actual measured ramp time when sonics were turned on.              */
/*                                                                         */
/*  Exit:   AmpRamp = 10 times ms step value in percent                    */
/*          NextRampValue = Amp value just output                          */
/*                                                                         */
/*  Future Options:                                                        */
/*      To have 3 different ramps choices use:                             */
/*               AmpRampTime10 - for fastest ramp                          */
/*               AmpRampTime25 - for medium ramp (or 2 * AmpRampTime10)    */
/*               AmpRampTime50 - for slowest ramp (or 4 * AmpRampTime10)   */
/*                                                                         */
/***************************************************************************/
{
   SINT32   AmpDrop;

   EnergyBrakeTimer = 0;
   EnergyBrakeFlag = FALSE;
   EBOverloadTimer = 0;
   AmpDrop = (CurrentAmpIn + 5);/* Already multiplied by 10 for more accuracy */
   AmpRamp = AmpDrop / RunningPreset.EBTime;  /* 10 times ramp step value      */
   NextRampValue = (CurrentAmpIn - AmpRamp);
   SetCurrentAmp(NextRampValue/POWERDIV);
}



void CheckBrake(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with handling the timing for the   */
/*  energy braking.  When the time set in the BUC menu variable is         */
/*  reached this state will end.  Also, if the requested amplitude is      */
/*  reached before the time expires the state will end early.  Each pass   */
/*  the amp value will be decreased by AmpRamp percent.  The exit code     */
/*  will call StopAllSonic() which will finally turn off the sonics.       */
/*                                                                         */
/***************************************************************************/
{
   UINT32   TempAmpIn;
   
   if (++EnergyBrakeTimer >= BUCMenuRAM.EnergyBrakingTime) {
//   if (++EnergyBrakeTimer >= RunningPreset.EBTime) {
      EnergyBrakeFlag = TRUE;
   }
   TempAmpIn = ((CurrentAmpIn + 5) / POWERDIV); /* Drop tenths and round to whole percent */
   if (TempAmpIn <= BUCMenuRAM.EnergyBrakingAmp) {
      EnergyBrakeFlag = TRUE;
   }
   if (NextRampValue > AmpRamp) NextRampValue = (NextRampValue - AmpRamp);
   if (NextRampValue < 50) NextRampValue = 50;  /* Request no less than 5% */
   SetCurrentAmp(NextRampValue/POWERDIV);
   EBOverloadTimer++;
   if (Inp.OL == TRUE) {            /* If overload detected save Power & Freq. */
      EBOverloadPower = CurrentPowerIn;
      EBOverloadFreq = CurrentFreqIn;
   }
}



void StartHold(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the hold time.                */
/*                                                                         */
/***************************************************************************/
{
   // AccessControlOutputPorts(CTRL_PORT_1, BIT_2_MASK, OVERLOAD_RESET_SIGNAL_OFF_VAL);

   PortRegisterB = (PortRegisterB & BIT_2_CLR);              // J.B
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;

   SetPV((UINT16)RunningPreset.HoldForce, FORCE_B_TO_HOLD);
   HoldTimer = StartTimer(RunningPreset.HoldTime, &HTimeFlag, 8);
   if (HoldTimer == FAILED1) {
      LogError(TIMERFAILED1);
      HoldTimer = 0;
   }
   else if (HoldTimer == FAILED2) {
      LogError(TIMERFAILED2);
      HoldTimer = 0;
   }
   ActualHoldTime = 0;
   if (CycleAbort == FALSE) {
      MsDataPtr->PrintBottomFlags &= (~HOLDALARMMASK); /* Hold started, so remove alarm flag */
   }
}



void StartAHold(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the ALTERNATE hold state.     */
/*  This state is required when the normal hold state is not used.  This   */
/*  allows checking of overloads when the overload occurs within the last  */
/*  few ms of the weld.                                                    */
/*                                                                         */
/***************************************************************************/
{
   // AccessControlOutputPorts(CTRL_PORT_1, BIT_2_MASK, OVERLOAD_RESET_SIGNAL_OFF_VAL);

   PortRegisterB = (PortRegisterB & BIT_2_CLR);              // J.B
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;

   HoldTimer = StartTimer(ALTERNATEHOLDTIME, &HTimeFlag, 8);
   if (HoldTimer == FAILED1) {
      LogError(TIMERFAILED1);
      HoldTimer = 0;
   }
   else if (HoldTimer == FAILED2) {
      LogError(TIMERFAILED2);
      HoldTimer = 0;
   }
   ActualHoldTime = 0;
   SVOff();
/*---  Because there will be no Stop Hold state, get final numbers here ---*/

   WeldingResults.ActualTotalAbs = EncoderPos;
   MsDataPtr->HoldEndAtTime = WeldingResults.ActualWeldTime;

   SetCurrentFreqOffset(0);                                 


}



void CheckHold(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking the hold to see if   */
/*  trigger has been lost.                                                 */
/*                                                                         */
/***************************************************************************/
{
   TriggerLostFlag = CheckForTriggerLost();
//   CheckControlLimits();
   CheckCycleAborts();
   ActualHoldTime++;
}


void StopAHold(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with an overload occuring in the   */
/*  fake hold state. It is needed inorder to get the DUPS info.            */
/*                                                                         */
/***************************************************************************/
{   
}


 
void StopHold(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the end of the hold time.     */
/*                                                                         */
/***************************************************************************/
{

   WeldingResults.ActualTotalAbs = EncoderPos;
   WeldingResults.ActualTotalCollapse = EncoderPos - WeldingResults.ActualTriggerDistance; /* Determine collapse    */

      

/* when no trigger lost or cycle abort alarms use the requested hold time */

   if ((WeldingResults.CycleModifiedAlarms & (CM1|CM15)) == FALSE) {
      ActualHoldTime = RunningPreset.HoldTime;
   }
   MsDataPtr->HoldEndAtTime = WeldingResults.ActualWeldTime + ActualHoldTime;

   SVOff();                             /* Turn off SV to bring hown up    */
   if ((HoldTimer != 0) && (HTimeFlag == TRUE)) {
      StopTimer(HoldTimer);
   }

   SetCurrentFreqOffset(0);                                 
}


/*-----------------------------------------------------------------------*/
/*----------  Below here is the code to deal with After Burst  ----------*/
/*-----------------------------------------------------------------------*/


void StartABDly(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the start of the delay        */
/*  between hold and after burst.                                          */
/*                                                                         */
/***************************************************************************/
{
   SINT16 TimerReturn;

   TimerReturn = StartTimer((UINT16)RunningPreset.AbDelay, &ABTimeFlag, (UINT16)40);
   if (TimerReturn == FAILED1) {
      LogError(TIMERFAILED1);
   }
   else if (TimerReturn == FAILED2) {
      LogError(TIMERFAILED2);
   }
   ActualABDelay = 0;
   ABTimeDelayFlag = TRUE;
}



void TestABDly(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with checking for hornreturn time  */
/*                                                                         */
/*  This function will wait for the DUPS data collection if and overload   */
/*  occured prior to this state.                                           */
/*                                                                         */
/***************************************************************************/
{
//   TestActClr();
   if (Inp.uls == FALSE){
      HornReturnCount++;
      if(HornReturnCount > UPPERLIMIT_TIMEOUT)
         HornReturnFlag = FALSE;
   }
   ActualABDelay++;
   if (IsDUPSDataCollectionComplete() == TRUE) {
      DUPSOkFlag = TRUE;
   }
   else {
      DUPSOkFlag = FALSE;
   }
   if ( (DUPSOkFlag == TRUE) && (ABTimeFlag == FALSE) ) {
      ABTimeDelayFlag = FALSE;
   }
   else ABTimeDelayFlag = TRUE;
}



void StopABDly(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the end of the delay between  */
/*  hold and after burst.                                                  */
/*                                                                         */
/***************************************************************************/
{
   ActualABDelay++;
}



void ALStopABD(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with an abnormal end to the delay  */
/*  between hold and after burst.                                          */
/*                                                                         */
/***************************************************************************/
{
}



void StartABTme(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the start of the after burst. */
/*                                                                         */
/***************************************************************************/
{
   SINT16 TimerReturn;


   TimerReturn = StartTimer((UINT16)RunningPreset.AbTime - ABRAMPDOWNTIME,
                                &ABTimeFlag, (UINT16)41);
   if (TimerReturn == FAILED1) {
      LogError(TIMERFAILED1);
   }
   else if (TimerReturn == FAILED2) {
      LogError(TIMERFAILED2);
   }
   SetCurrentAmp(RunningPreset.AbAmp);      /* Initial amplitude           */

   if(CycleAbort == FALSE) {      /* do not want to turn on sonics for 1ms */
      PSRun();                    /* Start sonics             */
   }
   ActualAfterburstTime = 0;
}



void TestABTme(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will deal with checking for horn return time, */
/*  while doing the afterburst.                                             */
/*                                                                          */
/****************************************************************************/
{
//   TestActClr();
   if (Inp.uls == FALSE){
      HornReturnCount++;
      if(HornReturnCount > UPPERLIMIT_TIMEOUT)
         HornReturnFlag = FALSE;
   }
   ActualAfterburstTime++;
   if (CurrentPowerIn > ABOverloadPower) {
      ABOverloadPower = CurrentPowerIn;
   }
}



void StopABTme(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the end of the after burst.   */
/*                                                                         */
/***************************************************************************/
{
   RampStartValue = RunningPreset.AbAmp;      /* Ramp start value           */
   RampStopValue = 5;                         /* Go until 5 %               */
   RampTime = ABRAMPDOWNTIME;                 /* How long to ramp down      */
   RampUpDirection = FALSE;                   /* Say "ramp down"            */
   RampRunningTime = 0;                       /* Initial ramp counter       */
   RampDiff = RampStartValue - RampStopValue; /* Change in value            */
   RampEndFlag = FALSE;
   if (Inp.OL == TRUE) {
      if (CurrentSetup.ExtraCooling == FALSE) {
         CoolValOff(); //  Solves 1968; It was PSIdle
      }
      PSReset();
   }
   else {
      ActualAfterburstTime += ABRAMPDOWNTIME; /* Offset by ramp down time   */
   }                                          /* unless an O/L occurred     */
}



void RampOff(void)
{
   SINT32 RampValue;

   if (Inp.uls == FALSE){
      HornReturnCount++;
      if(HornReturnCount > UPPERLIMIT_TIMEOUT)
         HornReturnFlag = FALSE;
   }
   RampRunningTime += 1000;

/*----   Stop if we timed out, before reaching the actual end of ramp   ----*/

   if ((RampRunningTime / 1000) >= RampTime) {
      PSIdle();     // Stop sonics
      RampEndFlag = TRUE;
   }
   else switch (RampUpDirection) {
      case FALSE:                             /* Ramp Down                  */
         RampValue = (((RampRunningTime / RampTime) * RampDiff) + 50) / 1000;
         RampValue = (RampStartValue - RampValue);
         SetCurrentAmp(RampValue);
         if (RampValue <= RampStopValue) {
            PSIdle();                         /* Stop sonics                */
            RampEndFlag = TRUE;
         }
         break;

      case TRUE:                              /* Ramp Up                    */
         RampValue = (((RampRunningTime / RampTime) * RampDiff) + 50) / 1000;
         RampValue = (RampStartValue + RampValue);
         SetCurrentAmp(RampValue);
         if (RampValue >= RampStopValue) {
            PSIdle();                         /* Stop sonics                */
            RampEndFlag = TRUE;
         }
         break;

      default:
         break;
   }
   if (Inp.OL == TRUE) {
      PSReset();
   }
}



void ALStopABT(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the abnormal end of after     */
/*  burst.                                                                 */
/*                                                                         */
/***************************************************************************/
{
   PSIdle();                                /* Stop sonics                 */
   if (Inp.OL == TRUE) {
      PSReset();
   }
}



void StartSeek(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the start of seek.            */
/*                                                                         */
/***************************************************************************/
{
   SeekDelay = SEEKDELAYTIME;               /* Load up counter with delay   */
   ActualSeekTime = 0;
   SeekEndFlag = FALSE;
}



void CheckSeek(void)
/****************************************************************************/
/*                                                                          */
/*  This is the function that will be called every pass while seeking.      */
/*                                                                          */
/*  Notes: External cycle abort is checked here instead of calling          */
/*         CheckControlLimits because during seek we don't want to risk     */
/*         hitting peak power cutoff, energy compensation, or max timeout   */
/*         while we're seeking.                                             */
/*                                                                          */
/*         Overload is checked here instead of the state table to prevent   */
/*         an afterburst overload showing up also as a seek overload.       */
/*         Doing it here allows the SEEKDELAYTIME to pass before a check is */
/*         done, giving the power supply time to react to the reset from    */
/*         the afterburst overload.                                         */
/*                                                                          */
/****************************************************************************/
{
//   TestActClr();
   if (ECycleHistFlag == TRUE) {          /* Check on external cycle abort */
      RecordAlarm(CM15);
   }
   if (Inp.uls == FALSE){
      HornReturnCount++;
      if(HornReturnCount > UPPERLIMIT_TIMEOUT)
         HornReturnFlag = FALSE;
   }
   if (SeekDelay-- <= 0) { 
      if (IsDUPSDataCollectionComplete() == TRUE) {
         DUPSOkFlag = TRUE;
         PSSeek();                        /* Start seek */
         MsDataPtr->PrintBottomFlags &= (~SEEKALARMMASK); /* Seek started, so remove alarm flag */
         if (ActualSeekTime++ >= MAXSEEKTIME) {
            ActualSeekTime--;
            SeekEndFlag = TRUE;
         }
         if (Inp.OL == TRUE) {
            RecordAlarm(OL8);
            SeekEndFlag = TRUE;
         }
      }
      else {
         DUPSOkFlag = FALSE;
      }
   }
}



void StopSeek(void)
/***************************************************************************/
/*                                                                         */
/*  This is the function that will deal with the end of seek.              */
/*                                                                         */
/***************************************************************************/
{
   if (CurrentSetup.ExtraCooling == FALSE) {
      CoolValOff();                           /* Dont forget the cooling valve*/
   }
   if (Inp.OL == TRUE) {                    /* do not abort overloads      */
      RecordAlarm(OL8);
      PSReset();
      MsDataPtr->SeekEndAtTime = WeldingResults.ActualWeldTime +
                                 ActualHoldTime + 
                                 ActualABDelay + ActualAfterburstTime +
                                 SEEKDELAYTIME + ActualSeekTime;
   }
   else {
      PSIdle();                             /* Stop sonics                 */
      MsDataPtr->SeekEndAtTime = WeldingResults.ActualWeldTime +
                                 ActualHoldTime +
                                 ActualABDelay + ActualAfterburstTime +
                                 SEEKDELAYTIME + MAXSEEKTIME;
   }

   ResetUpTimer(TRIGGERLOSTTIMER);
}



void CheckFrequencyLimits(void) 
{
   if (CurrentFreqIn <= WeldingResults.FrequencyMin) 
      WeldingResults.FrequencyMin = CurrentFreqIn;
   if (CurrentFreqIn >= WeldingResults.FrequencyMax)
      WeldingResults.FrequencyMax = CurrentFreqIn;
   VerifySBL();
}



void StartDUPSDataCollection(void)
/****************************************************************************/
/*                                                                          */
/*  This function will initiate the weld data collection from the DUPS.     */
/*  The structure which is used is based on what the current weld state is. */
/*  A check will be done to see if there is communication with DUPS and to  */
/*  see if CurrentPreset.WeldStatusFlag is TRUE, except for TESTMODESTATE.  */
/*  If there is no DUPS available, then the OpStatus of each structure is   */
/*  set to DUPS_SUCCESS.                                                    */
/*                                                                          */
/****************************************************************************/
{

   WeldOLStatus.OpStatus = DUPS_SUCCESS;  /* If no DUPS, then assume */
   SeekOLStatus.OpStatus = DUPS_SUCCESS;  /* everything is okay.     */
   ABOLStatus.OpStatus = DUPS_SUCCESS;    /*                         */

   if (DUPS_Info.DUPSFlag == TRUE) {
      switch (WeldState) {

         case TESTMODESTATE:          /* Test overload */
            WeldOLStatus.OpStatus = DUPS_PENDING;
            DUPS_GetLastWeldStatus(&WeldOLStatus);
            OlPending = WELD_OL;
            break;

         case WAITFORPTSSTATE:        /* Pretrigger overload */
         case WAITFORTRSSTATE1:       /* Pretrigger overload */
         case WAITFORTRSSTATE2:       /* Pretrigger overload */
         case WELDTIMESTATE:          /* Weld overload */
         case POWERUPSEEKSTATE:       /* Power up seek overload */
         default:
            if (RunningPreset.WeldStatusFlag == TRUE)  {
               WeldOLStatus.OpStatus = DUPS_PENDING;
               DUPS_GetLastWeldStatus(&WeldOLStatus);
               OlPending = WELD_OL;
            }
            break;

         case SEEKSTATE:              /* Seek overload */
            if (RunningPreset.WeldStatusFlag == TRUE)  {
               SeekOLStatus.OpStatus = DUPS_PENDING;
               DUPS_GetLastWeldStatus(&SeekOLStatus);
               OlPending = SEEK_OL;
            }
            break;
         case AFTERBURSTTIMESTATE:    /* AB overload */
            if (RunningPreset.WeldStatusFlag == TRUE)  {
               ABOLStatus.OpStatus = DUPS_PENDING;
               DUPS_GetLastWeldStatus(&ABOLStatus);
               OlPending = AB_OL;
            }
            break;
      }
   }
}


BOOLEAN IsDUPSDataCollectionComplete(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check the OpStatus member of each of the DUPS_WELD   */
/*  STATUS structures.  If none of the three are waiting for data then a    */
/*  TRUE will be returned.  If any are waiting then a FALSE will be         */
/*  returned.                                                               */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN  RetVal = TRUE;           /* Assume for now not waiting for data */

   if (DUPS_Info.DUPSFlag == FALSE) 
      RetVal = TRUE;
   else if (WeldOLStatus.OpStatus == DUPS_PENDING)
      RetVal = FALSE;
   else if (SeekOLStatus.OpStatus == DUPS_PENDING)
      RetVal = FALSE;
   else if (ABOLStatus.OpStatus == DUPS_PENDING)
      RetVal = FALSE;
   if(RetVal == TRUE)
      {
      switch(OlPending)
         {
         case(WELD_OL):
            if(WeldOLStatus.OpStatus == DUPS_SUCCESS)
               {
               UpdateOLType(WeldOLStatus.ErrorReason);
			   OlPending = NOT_PENDING;
			   }
            break;
            
         case(AB_OL):
            if(ABOLStatus.OpStatus == DUPS_SUCCESS)
               {
               UpdateOLType(ABOLStatus.ErrorReason);
			   OlPending = NOT_PENDING;
			   }
            break;
            
         case(SEEK_OL):
            if(SeekOLStatus.OpStatus == DUPS_SUCCESS)
               {
               UpdateOLType(SeekOLStatus.ErrorReason);
			   OlPending = NOT_PENDING;
			   }
            break;
         
         default: /* not waiting for any data */
		    OlPending = NOT_PENDING;
            break;
         }    
      }   
   return(RetVal);
}


static void UpdateOLType(SINT32 OverloadReason)
/****************************************************************************/
/*                                                                          */
/*  This function will receives the type of overload that occurred. Then    */
/*  updates the SWConfiguration inorder to show the proper overload title   */
/*  line.                                                                   */
/*                                                                          */
/****************************************************************************/
{
   switch(OverloadReason)
   {
      case DUPS_CURRENTOVERLOAD:         /* Current Overload */
         UpdateSWConfiguration(C_OL,TRUE);
         UpdateSWConfiguration(V_OL,FALSE);
         UpdateSWConfiguration(F_OL,FALSE);
         UpdateSWConfiguration(P_OL,FALSE);
         break;   
      
      case DUPS_VOLTAGEOVERLOAD:         /* Voltage Overload */
         UpdateSWConfiguration(C_OL,FALSE);
         UpdateSWConfiguration(V_OL,TRUE);
         UpdateSWConfiguration(F_OL,FALSE);
         UpdateSWConfiguration(P_OL,FALSE);
         break;   
      
      case DUPS_FREQLIMITSEEKLOW:         /* Freq Overload */
      case DUPS_FREQLIMITSEEKHIGH:
      case DUPS_FREQLIMITWELDLOW:
      case DUPS_FREQLIMITWELDHIGH:
         UpdateSWConfiguration(C_OL,FALSE);
         UpdateSWConfiguration(V_OL,FALSE);
         UpdateSWConfiguration(F_OL,TRUE);
         UpdateSWConfiguration(P_OL,FALSE);
         break;   
      
      case DUPS_PHASELIMIT:         /* Phase Overload */
      default:
         UpdateSWConfiguration(C_OL,FALSE);
         UpdateSWConfiguration(V_OL,FALSE);
         UpdateSWConfiguration(F_OL,FALSE);
         UpdateSWConfiguration(P_OL,TRUE);
         break;   
   }
}

