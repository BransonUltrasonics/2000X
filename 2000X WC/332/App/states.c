/* $Header:   D:/databases/VMdb/2000Series/App/STATES.C_V   2.267.1.8   Jan 03 2018 08:53:12   RCHAPA  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996,97, 2009  */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module Name: States                                                      */
/*                                                                          */
/* Filename:    States.c                                                    */
/*                                                                          */
/* Function name: Weld Sequence State Machine                               */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   03-15-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date       Author    Description                             */
/*  =========  =========  ========  ===========                             */
/*     0       03-19-96   BEKymer   Add pSOS to state machine               */
/*     1       05-01-96   BEKymer   Added calibration states                */
/*     2       05-03-96   BEKymer   Added ClearContinueFlag to              */
/*                                    CalWaitCont Entry Code                */
/*     3       06-06-96   BEKymer   Remove all references to ContinueFlag   */
/*                                    Fill in CurrentSequence               */
/*     4       06-10-96   BEKymer   New variable PleaseWaitTimerFlag        */
/*     5       06-15-96   BEKymer   Change ALNORM in Ready state to NORM    */
/*                                    for Inp.Trigger                       */
/*     6       06-26-96   LAM       added TestUls in pass code              */
/*     7       06-27-96   BEKymer   Add states for energy sonics on         */
/*     8       06-28-96   BEKymer   New states for final data results       */
/*     9       07-08-96   BEKymer   Check for overload in Weld1 state       */
/*    10       07-09-96   BEKymer   Add STATE & SSTATE for trigger delay    */
/*    11       07-23-96   BEKymer   Fix TrigDelay SSTATE-TriggerDelayFlag   */
/*    12       08-13-96   BEKymer   New states for SonicsOnX (weld modes    */
/*                                  other then TIME)                        */
/*    13       09-11-96   BEKymer   Make state member for STATE FinalDataST */
/*                                  a NOP instead of FINALDATASTATE so only */
/*                                  one FinalResults message is sent.       */
/*    14       09-18-96   BEKymer   Make overload an ALJUMP in all welds    */
/*    15       10-07-96   LAM       added horn down realtime updates        */
/*    16       10-08-96   BEKymer   Test DoorOpen in ready state            */
/*    17       10-09-96   BEKymer   Added code in EnterHDown function       */
/*    18       10-10-96   BEKymer   Change Inp.BothPB from ALJUMP to ABORT  */
/*                                  New states for test mode                */
/*    19       10-11-96   LAM       deleted initforce call from menus       */
/*                                  changed inp.bothpb in cal to jump       */
/*    20       10-14-96   LAM       added flag to ready when maxMA to PVP   */
/*                                  exceeded.                               */
/*    21       10-18-96   BEKymer   Add power up/down states, change        */
/*                                  UpStroke state                          */
/*    22       10-22-96   BEKymer   Change divisor in TestPO4               */
/*                                  Remove test for StopFlag in ready state */
/*    23       10-30-96   BEKymer   Change trigger lost alarm to SF20       */
/*    24       10-30-96   LAM       added checkpsi                          */
/*    25       11-01-96   BEKymer   GetCurrentModel in actuator power on    */
/*    26       11-02-96   BEKymer   Change condition to leave ReadyTest     */
/*    27       11-05-96   BEKymer   Redefine the power up sequence checking */
/*    28       11-06-96   LAM       added bothpalmbutton test to calibration*/
/*    29       11-06-96   BEKymer   Remove PowerOnPowerOk from power on test*/
/*    30       11-08-96   BEKymer   Change error in HDHold from G39 to G44  */
/*    31       11-13-96   LAM       chged bothpalmbutton state in calibration*/
/*                                  added horndownforce                     */
/*    32       11-14-96   BEKymer   Make all external cycle aborts G33 alarm*/
/*    33       11-15-96   LAM       chged trigger states in calibration     */
/*    34       11-20-96   BEKymer   Change exit code for upstroke state     */
/*                                  Abort when TRS occurs while waiting PTS */
/*    35       11-21-96   BEKymer   Remove 1 Beep from Triggered state      */
/*    36       11-21-96   LAM       added inp.bothpalmbuttons,added realtime*/
/*                                  horndown psi                            */
/*    37       12-03-96   BEKymer   Added StopFlag in palm button state     */
/*                                  Created new actions POP and PUSH        */
/*    38       12-17-96   BEKymer   In CheckMenuSync update display 4/sec   */
/*    39       12-19-96   BEKymer   Dont update(above) when called from     */
/*                                  DealWithSelectKey                       */
/*    40       12-19-96   LAM       deleted check palmbutttons in SCWaitTRS */
/*    41       12-30-96   BEKymer   In horndown, if PB's lost,POP & no alarm*/
/*    42       01-07-97   LAM       made system default to freqinternal     */
/*    43       01-07-97   PhilJ     In ExitHDown deleted sending MainKey    */
/*    44       01-08-97   LAM       fixed calibration first force           */
/*    45       01-10-97   PhilJ     UINT32 CurrentFreqIn to SINT32          */
/*    46       01-11-97   LAM       deleted getcurrentactuator              */
/*    47       01-21-97   LAM       chged alarms for 1st release            */
/*                                  added read preset to end of powerup     */
/*    48       02-03-97   LAM       chged waituls2                          */
/*    49       02-05-97   PaulG     Added PrePowerDown                      */    
/*    49.01    02-06-97   LAM       fixed test overload                     */    
/*    50.      02-18-97   LAM       fixed hornreturn alarm                  */    
/*    50.01    02-21-97   LAM       send data on second step                */    
/*    50.02    02-21-97   LAM       fixed 2 alarms on uls timeout           */    
/*    51.00    03-06-97   LAM       fixed dooropen at powerup               */    
/*    52.00    03-07-97   LAM       removed cold start at power up          */    
/*    53.00    04-01-97   LAM       set ampcontrol to internal at powerup   */    
/*    54.00    04-07-97   LAM       chged horn return to abort              */    
/*    54.01    04-07-97   LAM       chged topoflist,endoflist,and noplist to*/
/*                                  NOP                                     */    
/*    55.00    04-09-97   LAM       added testulsup to waitulsup            */    
/*    55.01    04-10-97   LAM       added WELDTIME2STATE                    */    
/*    55.10    04-11-97   PhilJ     added ExitHDAlarm in HoldState          */    
/*    55.20    04-11-97   LAM       chged fakehold state from nop to holdstate*/    
/*    56.00    04-14-97   LAM       added powerdownaborted flag             */    
/*    56.01    04-16-97   BEKymer   New function (EnterUls) called in WaitUl*/    
/*    56.02    04-23-97   PhilJ     In SSTATEs WaitUls1 changed SF3 to SF4  */    
/*    57.00    04-27-97   LAM       display powerup uls and door fail alarms*/    
/*    57.01    04-28-97   PhilJ     Chngd Internal Amp & FreqControl to UINT16*/    
/*    57.02    04-29-97   BEKymer   Check PrinterOK flag in SSTATES Ready   */
/*                                  and SSTATES CheckReady                  */    
/*    58.00    05-01-97   BEKymer   Test UlsTimeout in WaitUls1             */    
/*             05-01-97   BEKymer   Add extra arg to UpdateBar.. for blink  */
/*    58.01    05-05-97   LAM       added alstopseek                        */
/*    58.02    05-06-97   PhilJ     added SF17 to SSTATES HDHold TriggerLost*/    
/*    58.2.108 05-06-07   BEKymer   Added SonicsAbort to Weld1 & Weld1A     */    
/*    59.2.109 05-09-97   LAM       added entertestready                    */
/*    59.2.110 05-14-97   BEKymer   Added TrigSwActv to HDUpdate()          */    
/*    60.00    05-15-97   LAM       added readyok flag                      */                               
/*    61.00    05-28-97   LAM       added final1msstate                     */                               
/*    62.00    05-30-97   LAM       deleted w3 for printok                  */                               
/*    63.00    06-02-97   LAM       deleted w8 for readyok                  */                               
/*    63.2.115 06-03-97   BEKymer   In SSTATES TestMode ALJUMP on dooropen  */    
/*    63.2.116 07.01.97   J.B.      Change alarm codes                      */  
/*    63.2.118 07.01.97   LAM       added NC8 missingpartabort              */    
/*                                  added encoder states                    */    
/*                                  deleted getcurrentmodel#                */
/*    63.2.119 07.07.97   LAM       updated powerup sequence                */    
/*    63.2.120 07.08.97   LAM       replaced SF17 with EQ23,deleted goback  */    
/*                                  key during powerup,replaced G26 with NC4*/    
/*    63.2.121 07-16-97   LAM       updated record alarms                   */    
/*    63.2.122 07-16-96   BEKymer   Replaced some NC4's with EQ3's          */    
/*                                  Added some overload alarms              */    
/*                                  Added PTSTimerFlag to PreTrigger SSTATES*/    
/*    63.2.123 07-18-97   LAM       added verifypsnvram,OL3,EQ15,EQ22       */    
/*    63.2.124 07-29-97   LAM       deleted estop test in checkready        */    
/*    63.2.125 07-30-97   BEKymer   Added new PowerDown1 state, StartData   */    
/*                                  and EndData states                      */    
/*    63.2.126 08-06-97   BEKymer   In SeekWait change alarm from OL3 to OL8*/    
/*                                  and test for CycleAbort                 */    
/*                                  Add test for CycleAbort in RampSonics   */    
/*    64.2.127 08-08-97   LAM       added seek test                         */    
/*    65.2.128 08-11-97   BEKymer   in ABTime changed OL8 to ALJUMPNORM     */    
/*    65.2.129 08-15-97   LAM       added power calibration states          */    
/*    65.2.130 08-20-97   LAM       fixed power calibration states          */    
/*    65.2.131 08-22-97   LAM       fixed power calibration states          */    
/*    65.2.134 08-25-97   BEKymer   Fix DCS # 1899, dont Trigger Beep unless*/    
/*                                  there really is a trigger               */    
/*    65.2.135 08-26-97   LAM       added aljump for powercal, eliminate seek*/   
/*                                  at powerup when dooropen, deleted checkmotion*/    
/*                                  in horndown,removed OL8 fromrampsonics  */    
/*    65.2.136 08-28-97   LAM       added powercal trigger state            */   
/*    2.137    08-28-97   BEKymer   In CheckReady[] change ALJUMP to FAIL   */    
/*                                  for PBExitFlag                          */    
/*                                  In Ready[] change ALJUMP to ABORT for   */    
/*                                  Inp.uls                                 */    
/*    2.138    08-29-97   LAM       added menusync clear to power cal       */   
/*    2.139    08-29-97   LAM       added seek test                         */    
/*    2.140    09-02-97   LAM       added setdigpot removed seek test       */    
/*    2.141    09-02-97   BEKymer   Added check for overload in WaitTrs1,   */    
/*                                  WaitTrs2, and WaitTrs4                  */    
/*                                  Remove overload check from SeekWait     */    
/*                                  Add test for external cycle abort in    */    
/*                                  WaitUls1                                */    
/*    2.142    09-04-97   BEKymer   Use OKToAdvance in PalmButtons          */    
/*    2.143    09-09-97   BEKymer   Remove BlinkCondition argument from call*/    
/*                                  to UpdateBarGraph                       */    
/*    2.144    09-15-97   LAM       added prereadytestst                    */    
/*    2.145    09-18-97   BEKymer   Added palm button check to TestPO3      */    
/*    2.146    10-03-97   LAM       deleted missing stack alarm             */    
//    2.147    10.13.97   JBerman   1)  Removed a duplicate variable:
//                                      extern BOOLEAN TriggerLostFlag; 
//                                                          2)  Replaced:  2x PSIdle -> RampSonicsST
/*    2.148    10-15-97   LAM       deleted exituls1-this was causing dooropen*/
/*                                  alarm on the upstroke will catch the real alarm */  
/*    2.149    10-22-97   LAM       fixed dooropen in horn down             */  
/*    2.150    10-27-97   LAM       chged pbexit to fail condition          */  
/*    2.151    10-27-97   BEKymer   Remove EQ2 from CheckReady SSTATES      */    
/*                                  Add AlterHold SSTATES, change FakeHold  */    
/*    2.152    11-05-97   BEKymer   In WaitUls1[] check Inp.DoorOpen instead*/    
/*                                  of Inp.Trigger for alarm EQ3            */    
/*                                  Changed ABORT to ALJUMP in HDHold for   */    
/*                                  Inp.ECycleAbort for BJB.                */    
/*    2.153    11-10-97   BJB       Initializes FreqControlExternal as well */
/*                                  as FreqControlInternal in PowerUp().    */
/*    2.154    11-13-97   BEKymer   In Hold[] & AlterHold[] use ALNORM in   */    
/*                                  place of ALJUMPNORM for Inp.OL test     */    
/*    2.155    11-18-97   BEKymer   After a power up seek overload attempt  */    
/*                                  to reset the power supply, so by the    */    
/*                                  time CheckAlarm() is called the overload*/    
/*                                  will have gone away.                    */    
/*    2.156    11-18-97   BEKymer   In PalmButtons[] make CycleAbort=ABORT  */    
/*    2.157    11-20-97   LAM       In Pretrigger made OL a CycleAbort      */    
/*    2.158    12-01-97   LAM       fixed power up with digpot off          */    
/*    2.159    12-05-97   BEKymer   Eliminate call to AlStopSeek, use       */    
/*                                  StopSeek instead (it did the same thing)*/  
/*    2.160    12-11-97   LAM       removed seek test code fix to 5%        */    
/*    2.161    01-26-98   BEKymer   Skip TestPO4 (power supply test at      */    
/*                                  power up) if E-stop is active           */    
/*                                  Check Trigger and door open in palm     */    
/*                                  button state                            */    
/*    2.162    02-02-98   LAM       added check to not clear reset led at   */    
/*                                  power up if an alarm occurred           */    
/*                                                                          */    
/*    2.163    02-03-98   BEKymer   Call ExitUlsUp in WaitUlsUp state       */    
/*    2.164    02-03-98   BEKymer   Change NC5 alarm to CM14                */    
/*    2.165    02-05-98   LAM       Check stopflag in preready and ready    */
/*                                  instead of PB                           */    
/*    2.166    02-06-98   BEKymer   Use ALJUMPNORM to exit Weld1 if Cycle-  */    
/*                                  Abort or SonicsAbort set.  This will    */    
/*                                  turn off sonics this state instead of   */    
/*                                  1 ms later in the next state.           */    
/*    2.167    03-20-98   LAM       set  weldingresults.ampcontrol          */
/*    2.168    03-23-98   LAM       deleted unused function -checkmotion    */
/*    2.169    03-28-98   BEKymer   Changed functions call within the Final */    
/*                                  DataST to delay switching MsDataPtr &   */    
/*                                  MsPointer                               */    
/*    2.170    04-23-98   BJB       Includes menuhorn.h                     */
/*    2.171    04-23-98   LAM       added calbpb state, added readloadcell  */
/*                                  in checkmenusync state                  */    
/*    2.172    04-27-98   LAM       deleted unused upstroke states          */
/*    2.173    04-29-98   BJB       Deleted DebugDelayST and DebugTrigST    */
/*    2.174    04-30-98   BEKymer   Uncomment calls to OL3 in power up      */    
/*    2.175    05-01-98   LAM       chged testuls to nothing in calibration */
/*                                  deleted OL3 in testpo1                  */    
/*    2.176    05-15-98   BEKymer   Added retrigger function to power up    */    
/*                                  seek for 500 ms.                        */    
/*                                  Added new SSTATES Limits[] and new      */    
/*                                  STATE CheckLimitsST                     */    
/*    2.177    05-20-98   LAM       added spring rate states                */
/*    2.178    05-20-98   BEKymer   Added code to determine length of power */    
/*                                  up seek to figure out dip switch setting*/    
/*    2.179    05-20-98   BEKymer   Change SEEK_OFF_TIME to 30 so seek      */    
/*                                  re-trigger occurs every 50 ms.          */    
/*    2.180    05-22-98   BJB       Changed constant in TestPO3() to use    */
/*                                  tenths of pounds.                       */    
/*    2.181    05-29-98   BEKymer   In TestPO4() set PowerSupplyOk=TRUE if  */    
/*                                  Seek from power supply is detected.     */    
/*    2.182    05-29-98   LAM       fixed == PoweredUp declaration          */    
/*    2.183    06-04-98   BJB       Got rid of globals UpdateDigPot and     */    
/*                                  TempPot, don't need these anymore.      */
/*    2.184    06-04-98   BEKymer   Change AmpControlFlag to PowerSupply    */
/*                                  ControlFlag                             */
/*                                  In PowerUp() set freq to internal       */    
/*    2.185    06-08-98   LAM       moved changing 10vref to extfreq to fix */    
/*                                  ultrasonic PS alarm, added new calibration*/
/*                                  states.                                 */    
/*    2.186    06-12-98   LAM       chged waittrs4 state for manual mode    */    
/*    2.187    06-23-98   LAM       chged menusync to wait for correct menu,*/    
/*                                  deleted unused page states              */    
//    2.188    06.25.98   JBerman   Added  a line 182, to catch EQ10
/*    2.189    06-26-98   BEKymer   Change unknown                          */    
/*    2.190    07-01-98   LAM       added startcalpb to eliminate jumping to*/    
/*                                  the run screen                          */    
/*    2.191    07-15-98   LAM       chged state for calibration complete    */    
/*                                  to update message only when completed   */    
/*    2.192    07-24-98   BEKymer   Remove useless NC1 alarm in WaitUls1    */    
/*                                  Timerflag  END END state                */    
/*    2.193    07-30-98   BJB       TestPO1() doesn't need to check         */    
/*                                   PowerUpPresetReceived, preset will now */
/*                                   always be loaded at this point.        */
/*    2.194    07-30-98   BEKymer   In Ready state if AlarmsReset is FALSE  */    
/*                                  then ABORT instead of FAIL.  This fixes */    
/*                                  the problem when Recal Act alarm occurs */    
/*                                  while in the ready state.               */    
/*    2.195    08-03-98   BEKymer   added stagger test to calibration       */    
/*    2.196    03-15-99   LAM       fixed setforce prototype                */
/*    2.197    05-14-99   JZ        changed PowerSupplyControlFlags to      */
/*                                  PSActControlFlags                       */
/*    2.198    05-27-99   JZ        removed EP test generating EQ5 alarm    */                                             
/*    2.198.1.1  06-23-99 JZ        deleted EnterHDown, ExitHDown, HDEnterReady */
/*                                  STATE HoldState, CheckHornDown, HDReadySt */
/*    2.198.1.2  07-07-99 JHenry   Changed CalWaitTime2 state to call       */
/*                                  CollectForceData                        */ 
/*    2.200      08-06-99 JZ        changed JustPowerUpFlag to BOOLEAN      */
/*    2.201    09-07-99   LAM       deleted unused cal states & variables   */
/*    2.202    09-09-99   JZ        modified TestPO3                        */ 
/*    2.203    09-20-99   LAM       deleted unused function in calreadystate*/
/*    2.204    09-22-99   LAM       added updatedownspeed to  cal waituls   */
/*                                  states                                  */
/*    2.205    09-27-99   BEKymer   Change ALJUMP to ABORT when error code  */
/*                                  is EQ3                                  */
/*    2.206    10-11-99   LAM       use homepressure instead of averagepressure*/
/*    2.207    10-22-99   LAM       move updating pressure at power up from */
/*                                  testpreready to testpo3                 */
/*    2.208    10-25-99   LAM       if pressure has changed the preset must */
/*                                  be verified before the next cycle and   */
/*                                  an asterisk needs to be added.          */
/*    2.208.2.1 11-18-99  JZ        modified TestPO3() for product backward */
/*                                  compatibility                           */
/*    2.208.2.2 12-08-99  LAM       removed unused sctriggerst, SCWaitTrs[] */
/*    2.209     12-16-99  LAM       removed unused references to profiling  */
/*    2.210     02-10-00  JZ        modified TestPO3()                      */
/*    2.211     05-26-00   SCM      Checked in for testing by Laura, John.  */
/*    2.212     06-28-00  BEKymer   Changed all MODEL to LEVEL              */
/*    2.213     07-18-00  JLH       Added ActualSeekTime and ActualPeakPower*/ 
/*    2.214     07-21-00  BEKymer   Renamed AbTimeFlag to AbTimeDelayFlag   */
/*    2.215     08-04-00  SRP       DUPSOkFlag = FALSE added in TestPO4()   */ 
/*    2.216     08-08-00  LAM       DUPSOkFlag =FALSE moved to TestPO5() wait*/ 
/*                                  in this state until the DUPS is initialized*/
/*    2.217     08-15-00  LAM       fixed power up to not exit on an overload*/ 
/*                                  until the DUPS answers                  */
/*    2.218     08-29-00  JLH       Added DepotLevel test to CheckReady substate. */
/*    2.219     09-05-00  LAM       Added powerupseek state for dups        */
/*    2.220     09-11-00  LAM       will check for ol if equipment failure  */
/*                                  bit is set and there is a DUPS(#3553)   */
/*    2.221     09-18-00  LAM       added stopahold to catch dups overload info  */
/*    2.222     09-25-00  LAM       added seekstate to poweron6 removed call*/
/*                                  to get dups data                        */
/*    2.223     09-27-00  LAM       DUPSOkFlag =FALSE moved to TestPO1() wait*/ 
/*                                  in this state until the DUPS is initialized*/
/*                                  do not record alarm from state table check */
/*                                  powerol flag in last power up state     */
/*                                  (Issue 3553)                            */
/*    2.224     10-03-00  LAM       Increased testpo2 to allow pressure     */
/*                                  averaging to complete (Issue 3602)      */
/*    2.225     10-04-00  AT        added DUPS_ChangePending to CheckReady  */
/*    2.226     10-05-00  BEKymer   In TestPO4 only increment ActualSeekTime*/
/*                                   until an overload occurs.  Sort of part*/
/*                                   of issue #3604. (COPS=0.999 always)    */
/*    2.227     10-05-00  BEKymer   Added DUPSChangePending to Ready SSTATES*/
/*                                   for a partial fix for issue #3592      */
/*    2.228     10-06-00  BEKymer   Change location of FailFlag test in     */
/*                                   CheckReady SSTATES.  Made the test for */
/*                                   DUPSChangePending in Ready an ABORT    */
/*    2.229     11-14-00  BEKymer   Make tests for LEVEL_f >= s\to take into*/
/*                                   account LEVEL_TEST                     */
/*    2.230     04-12-01  BEKymer   Create states for 'HH' handheld start   */
/*    2.231     04-24-01  BEKymer   Add states to support energy mode w/HH  */
/*    2.232     05-02-01  BEKymer   Use TestPreReadyHH in PreReadyHHST      */
/*    2.233     05-04-01  BEKymer   Use Nothing() instead of StopSonic1()   */
/*    2.234     05-08-01  BEKymer   Use TriggerLost instead of SingleStart  */
/*                                   in Weld1HH and Weld2H.  This fixes 0 ms*/
/*                                   report for additional information when */
/*                                   trigger lost in time mode              */
/*    2.235     05-09-01  BEKymer   Use new function AlStopHH in HH states  */
/*    2.236     05-23-01  BEKymer   Change error code for HoldHH trig lost  */
/*                                    fixes issues # 3689, # 3690, 3693     */
/*    2.237     05-25-01  BEKymer   Added test for external cycle abort in  */
/*                                   PBHH to fix issue # 3701               */
/*    2.237.1.1 02-13-03  BEKymer   Fix test functions for afterburst, was  */
/*                                   calling HH in normal actuator and      */
/*                                   normal when using HH                   */
/*    2.239     04-10-03  BEKymer   Move to tip as 2.239                    */
/*    2.240     04-11-03  BEKymer   Add DiagStopFlag so diagnostics can     */
/*                                   pull system from ready                 */
/*    2.241     05-13-03  BEKymer   Modify P/S power up test to eliminate   */
/*                                   false alarms because of frequency or   */
/*                                   amplitude changes.                     */
/*    2.242     09-11-03  BEKymer   Add energy braking states and substates */
/*                                                                          */
/*    2.241.1.0 09-18-03  JOY       Added Powerup Screen2 Check status.     */
/*    2.243     12-05-03  BEKymer   Merged 2.241.1.0 & 2.242 to create 2.243*/
/*                                   for Ver9.00b build                     */
/*    2.244     03-12-04  VSharma   Changed 'Inp.ECycleAbort' to ECycleHistFlag.*/
/*    2.245     04-06-04  VSharma   Added 'WaitSVST' & 'ExtTrigDelayST'.    */
/*                                  Added check for 'Inp.SVInterlock' signal*/
/*                                   from SVInterlock to Hold state.        */
/*    2.246     04-27-04  VSharma   Modified 'WaitSVState'.                 */
/*    2.247     05-03-04  VSharma   Added 'CalWaitUls1'& 'CalTrigger'.      */
/*    2.248     05-06-04  VSharma   Added ECycleHistFlag in 'ExtTrigDelay'. */
/*    2.249     05-07-04  LAM       merged with 8.22                        */
/*    2.250     05-18-04  LAM       check for horn weight change in         */
/*                                  checking actuator state                 */
/*    2.251     09-14-04  JOY       Updated CurrentPreset.Verified flag in TestPO3() */
/*    2.252     10-04-04  BEKymer   Add initialization for user outputs in  */
/*                                   power up sequence                      */
/*    2.253     10-04-04  BEKymer   Call common function UpdateAllUserOutput*/
/*                                   for power up initialization            */
/*    2.254     04-26-05  LAM       deleted unused pwrcalb                  */
/*    2.255     07-25-05  Bwadia    QVGA clean up done in Ver10.0e          */
/*    2.256     08-24-05  Aare      Added trigger before pretrigger flag to Trigger state. */
/*    2.257     09-12-05  Aare      Removed diagnostics code.               */
/*    2.258     10-17-05  Aare      Pretrigger delay works, trigger never happens. */
/*    2.259     10-20-05  Aare      Assigned unique hex trace values for all pretrigger delay state conditions. */
/*    2.260     11-02-05  Aare      Rolled back to 2.255                    */
/*    2.261     11-02-05  Aare      Set power up sequence timers to about 15 seconds each */
/*    2.262     11-22-05  Bwadia    Start State machines only if VGA started*/
/*                                  (After VGA is detected once)            */
/*                                  Restored power up sequence timers to    */
/*                                  original values                         */
/*    2.263     01-06-06  LAM       Merged BBRaun Special                   */
/*    2.264     02-6-06   BEKymer   Call StopAllSonic in JUMP state for     */
/*                                   WeldOffHHST (9.04A)                    */
/*    2.265     02-27-06  LAM       Made VFBusy an output line when there is*/
/*                                  a VGA                                   */
/*    2.266     03-24-06  Bwadia    Scrolling LEDs turned off after initial */
/*                                  sequence only for VFD                   */
/*    2.267     01-31-07  NHAhmed   Changes related to Changed Structure 
/*                                  variables of CHOICE and TOGGLE.         */
/*    2.268     10-22-07  NHAhmed   Changes done for LangTest phase 0       */
/*    2.269     09-04-08  YGupta    CleanUp for LangTest Project.           */
/*    2.267.1.2 09-10-09  BEkymer   Add new define MICRO where needed       */
/*    2.267.1.3 09-30-09  BEkymer   Init MicroHomeForce variable from BBR   */
/*    2.267.1.4 10-23-09  BEkymer   Add check for SBC ready in pre-ready    */
/*                                   state                                  */
/*    2.267.1.5 07-28-10  PDwivedi  Modified PowerOnOK function to set      */
/*                                  default value of MicroHomeForce.        */
/*    2.267.1.8 12/27/2017 RChapa	DUPS State and Substate Removed         */
/*                                  this state and substate was created for 
 * 									Ramp Time Change.                       */
/*----------------------------- DESCRIPTION --------------------------------*/  
                                                                              

                                                                            
/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define ONE_SECOND         1000 /* 1 second in ms                           */
#define AMPCHANGE             2 /* Min change in percent for seek           */
#define FREQCHANGE           10 /* Min change in hertz for freq during seek */
#define SEEK_ON_TIME         20 /* Power up seek on time                    */
#define SEEK_OFF_TIME        30 /* Power up seek off time                   */
#define SEEK_RETRIGGER_TIME  (SEEK_ON_TIME + SEEK_OFF_TIME)
#define SEEK_TIME          1000 /* Amount of time to retrigger seek         */
#define LONG_SEEK_TIME      250 /* Min amount to be considered long         */ 
#define SHORT_SEEK_TIME      50 /* Min amount to be considered short        */ 
#define SAFETY_SEEK_TIME   2000 /* Make sure we dont get stuck              */
#define ACTUATOR_TIME      2000 /* 2 seconds needed for pressure averaging  */

/*------------------------------ INCLUDES ----------------------------------*/

#define  STATES
#include "portable.h"
#include "state.h"
#include "keyPad.h"
#include "selctkey.h"
#include "mansensr.h"
#include "preset.h"
#include "states.h"
#include "332.h"
#include "qsm.h"
#include "digout.h"
#include "led.h"
#include "beep.h"
#include "weld_obj.h"
#include "weld.h"
#include "genalarm.h"
#include "getmsg.h"
#include "powrdwn.h"
#include "weldhold.h"
#include "spidd.h"
#include "menuhorn.h"
#include "menucalb.h"
#include "util.h"
#include "dups_api.h"
#include "rdyweld1.h"
#include "spidd.h"
#include "outports.h"
#include "menu7.h"

/* QVGA Header */
#include "DrawScrn.h"



/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/

extern INBITS  Inp;
extern BOOLEAN SubmenuFlag;
extern BOOLEAN UlsTimeout;
extern SINT16  CalTimer;
extern SINT16  NumberOfBeeps;    
extern BOOLEAN TestDelayFlag;
extern UINT16 AlarmCounter;

extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern CONFIGSETUP CurrentSetup;
extern BOOLEAN PlsWaitTimerFlag;                  /* Please Wait Timer Flag */
extern BOOLEAN TriggerLostFlag;
extern BOOLEAN PoweredUp, PrinterOK;
extern BOOLEAN JustPoweredUpFlag;
extern SINT16  DebugDelay;
extern BOOLEAN SpringRateComplete,DeflectionComplete;
extern BOOLEAN SeekEndFlag, RampEndFlag;
extern BOOLEAN DiagStopFlag;
extern BOOLEAN SBCReadyFlag;
extern SETUPS_Ver800  RunningPreset, CurrentPreset;
extern SINT32  CurrentFreqIn;
extern SINT32  CurrentForce;
extern SINT32  ActualSeekTime, ActualPeakPower;
extern UINT16  TenVoltRef,FreqControlExternal;
extern UNION_BOOL_UINT16  FreqControlInternal,AmpControlInternal;
extern BOOLEAN SonicsOffFlag;
extern BOOLEAN MissingPartFlag;
extern BOOLEAN AdvanceMenuFlag;
extern WELD_DATA WeldingResults;
extern UINT16 PresetNeedsToBeUpdated;
extern UINT16 SystemPres60PSI;
extern UINT16 SystemPres80PSI;
extern SINT32    FreqChg;

extern UINT16 LangIndex;
extern UINT32 DupsQid; 
extern BUCMENU_800 BUCMenuRAM;
extern UINT16 MicroHomeForce;
  
UINT16 PowerUpTimer;
UINT16 PowerUpSeekTimer;
UINT16 PowerSupplyOk; 
UINT16 MenuSyncTimer;
UINT16 JustPoweredUpTimer;
UINT16 SeekTime;              /* Actual time for seek vs dip switch setting */
UINT16 PressureCounter = 0;
UINT16 PressureTimer = 0;
UINT16 PressureFlag;
static DUPS_MSGBUF DUPS_MsgBuf;

BOOLEAN  ActDone, PSDone;
BOOLEAN  ControlsDone, StackDone;
static BOOLEAN PowerUpOL = FALSE;
UINT16 PSFailCode = 0x07;    /* BIT0, BIT1 and BIT2 Assume all will fail */


UINT32 PowerUpFreq;

BOOLEAN ParamUpdateFlag;
BOOLEAN PowerDownAborted = FALSE;

extern BOOLEAN HornReturnFlag;
extern BOOLEAN ReadyOK;
extern BOOLEAN ECycleHistFlag;
extern BOOLEAN TrgDelayTimeout;
extern BOOLEAN SVTimeout;
extern UINT16 ExtTriggerDelayTimer;
extern UINT16 SVTimer;

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/

extern BOOLEAN   IsThereAGraphPrinting;


/*-------------------------- Function Prototypes ---------------------------*/

#include "states.h"
#include "ready.h"
#include "weldhold.h"
#include "statedrv.h"
#include "mansensr.h"
#include "snsrcalb.h"
#include "psnvram.h"
#include "sc.h"
#include "display.h"


/*-------------------------------- CODE ------------------------------------*/




/*---------------------------  Data Structures  ----------------------------*/


/*****     *****     Here is an actual test weld cycle     *****     *****/

/*                         Variable           TRUE    FALSE   Alarm   Trace  */
/*                         pointer            Action  Action  Code    Code   */
/*                         ----------         ------- ------- ------- ------ */
SSTATES Initial[]       = {&SystemOK,         JUMP,   ALJUMP, NONE,   100,
                           &TimerFlag,        END,    END,    NONE,   101  };

SSTATES Ready[]         = {&Inp.DoorOpen,     ABORT,  NORM,   EQ4,    201,
                           &StopFlag,         ABORT,  NORM,   NONE,   202,
//                         &Inp.uls,          NORM,   ALJUMP, EQ2,    203,
                           &Inp.uls,          NORM,   ABORT,  EQ2,    203,
                           &AlarmsReset,      NORM,   ABORT,  NONE,   204,
                           &Inp.OnePB,        JUMP,   NORM,   NONE,   205,
                           &Inp.BothPB,       JUMP,   NORM,   NONE,   206,
//                         &ReadyOK,          NORM,   ABORT,  W8,     207,
                           &ReadyOK,          NORM,   ABORT,  NONE,   207,
                           &PrinterOK,        NORM,   ABORT,  NONE,   208,
                           &DUPSChangePending,ABORT,  NORM,   NONE,   209,
                           &DiagStopFlag,     ABORT,  NORM,   NONE,   210,
                           &TimerFlag,        END,    END,    NONE,   211  };

SSTATES ReadyHH[]       = {&StopFlag,         ABORT,  NORM,   NONE, 10000,
                           &AlarmsReset,      NORM,   ABORT,  NONE, 10001,
                           &Inp.SingleStart,  JUMP,   NORM,   NONE, 10002,
                           &ReadyOK,          NORM,   ABORT,  NONE, 10003,
                           &PrinterOK,        NORM,   ABORT,  NONE, 10004,
                           &DUPSChangePending,ABORT,  NORM,   NONE, 10005,
                           &DiagStopFlag,     ABORT,  NORM,   NONE, 10006,
                           &TimerFlag,        END,    END,    NONE, 10007  };

SSTATES ReadyTest[]     = {&Inp.DoorOpen,     ABORT,   NORM,   EQ4,   220,
//                         &Inp.OL,           ALJUMPNORM,NORM, OL1,   221,
                           &StartTestFlag,    JUMP,   NORM,   NONE,   222,
                           &AlarmsReset,      NORM,   FAIL,   NONE,   223,
                           &FailFlag,         FAIL,   NORM,   NONE,   224,
                           &TimerFlag,        END,    END,    NONE,   225  };

SSTATES CheckReady[]    = {&Inp.DoorOpen,     FAIL,   NORM,   EQ4,    300,
                           &StopFlag,         FAIL,   NORM,   NONE,   301,
                           &Inp.OnePB,        FAIL,   NORM,   NONE,   302,
                           &Inp.uls,          NORM,   FAIL,   NONE,   303,
                           &ULSExitFlag,      FAIL,   NORM,   EQ2,    304,
                           &AlarmsReset,      NORM,   FAIL,   NONE,   305,
                           &PoweredUp,        NORM,   FAIL,   NONE,   306,
                           &ReadyOK,          NORM,   FAIL,   NONE,   307,
                           &PrinterOK,        NORM,   FAIL,   NONE,   308,
                           &PBExitFlag,       FAIL,   NORM,   EQ17,   309,
                           &DUPSOkFlag,       NORM,   FAIL,   NONE,   310,
                           &DepotLevel,       FAIL,   NORM,   NONE,   311,
                           &DUPSChangePending,FAIL,   NORM,   NONE,   312,
                           &DiagStopFlag,     FAIL,   NORM,   NONE,   313,
                           &SBCReadyFlag,     NORM,   FAIL,   NONE,   314,
                           &FailFlag,         FAIL,   JUMP,   NONE,   315,
                           &TimerFlag,        END,    END,    NONE,   316 };

SSTATES CheckReadyHH[]  = {&StopFlag,         FAIL,   NORM,   NONE, 10100,
                           &Inp.SingleStart,  FAIL,   NORM,   NONE, 10101,
                           &AlarmsReset,      NORM,   FAIL,   NONE, 10102,
                           &PoweredUp,        NORM,   FAIL,   NONE, 10103,
                           &ReadyOK,          NORM,   FAIL,   NONE, 10104,
                           &PrinterOK,        NORM,   FAIL,   NONE, 10105,
                           &PBExitFlag,       FAIL,   NORM,   EQ17, 10106,
                           &DUPSOkFlag,       NORM,   FAIL,   NONE, 10107,
                           &DepotLevel,       FAIL,   NORM,   NONE, 10108,
                           &DUPSChangePending,FAIL,   NORM,   NONE, 10109,
                           &DiagStopFlag,     FAIL,   NORM,   NONE, 10110,
                           &FailFlag,         FAIL,   JUMP,   NONE, 10111,
                           &TimerFlag,        END,    END,    NONE, 10112 };

SSTATES PalmButtons[]   = {&Inp.OnePB,        NORM,   NORM,   NONE,   400,
//                           &CycleAbort,       JUMP,   NORM,   NONE,   402,
                           &CycleAbort,       ABORT,  NORM,   NONE,   402,
                           &Inp.uls,          NORM,   ABORT,  EQ2,    403,
//                         &Inp.BothPB,       JUMP,   NORM,   NONE,   404,
                           &OKToAdvance,      JUMP,   NORM,   NONE,   404,
                           &StaggerFlag,      ABORT,  NORM,   EQ12,   405,
                           &Inp.Trigger,      ABORT,  NORM,   EQ4,    406,
                           &Inp.DoorOpen,     ABORT,  NORM,   EQ4,    407,
                           &TimerFlag,        END,    END,    NONE,   408  };   /*Test State*/

SSTATES PBHH[]          = {&Inp.SingleStart,  NORM,   ABORT,  CM14, 10200,
                           &ECycleHistFlag,   ABORT,  NORM,   NC7,  10201,
                           &CycleAbort,       ABORT,  NORM,   NONE, 10202,
                           &OKToAdvance,      JUMP,   NORM,   NONE, 10203,
                           &TimerFlag,        END,    END,    NONE, 10204  }; 
                         
// continuous mode
SSTATES PalmButton[]    = {&Inp.OnePB,        JUMP,   ABORT,  EQ23,   440,
                           &Inp.uls,          NORM,   ABORT,  EQ2,    441,
                           &CycleAbort,       ABORT,  NORM,   NONE,   442,
                           &TimerFlag,        END,    END,    NONE,   443  };   /*Test State*/

SSTATES WaitSVInput[]  = {&AbortFlag,          ABORT, NORM,   NONE,  11500,
                          &CycleAbort,         JUMP,  NORM,   NONE,  11501,
                          &Inp.BothPB,         NORM,  ABORT,  EQ23,  11502,
                          &Inp.SVInterLock,    JUMP,  NORM,   NONE,  11503,
                          &Inp.DoorOpen,       ABORT, NORM,   EQ3,   11504,
                          &SVTimeout,          ABORT, NORM,   NC15,  11505,
                          &ECycleHistFlag,     ABORT, NORM,   NC7,   11506,
                          &TimerFlag,          END,   END,    NONE,  11507   }; 

SSTATES CalWaitUls1[]   = {&AbortFlag,        ABORT,  NORM,   NONE,   3600,
                           &CycleAbort,       JUMP,   NORM,   NONE,   3601,
                           &Inp.BothPB,       NORM,   JUMP,   NONE,   3602,
                           &Inp.uls,          NORM,   JUMP,   NONE,   3603,
                           &Inp.DoorOpen,     ABORT,  NORM,   EQ3,    3604,
                           &UlsTimeout,       ABORT,  NORM,   NC1,    3605,
                           &ECycleHistFlag,   ABORT,  NORM,   NC7,    3606,
                           &TimerFlag,        END,    END,    NONE,   3607  };

SSTATES WaitUls1[]      = {&AbortFlag,        ABORT,  NORM,   NONE,   500,
                           &CycleAbort,       JUMP,   NORM,   NONE,   501,
                           &Inp.BothPB,       NORM,   JUMP,   NONE,   502,
                           &Inp.uls,          NORM,   JUMP,   NONE,   503,
                           &Inp.DoorOpen,     ABORT,  NORM,   EQ3,    504,
                           &UlsTimeout,       ABORT,  NORM,   NC1,    505,
                           &ECycleHistFlag,   ABORT,  NORM,   NC7,    506,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   507,
                           &TimerFlag,        END,    END,    NONE,   508  };

SSTATES WaitUls2[]      = {&AbortFlag,        ABORT,  NORM,   NONE,   510,
                           &CycleAbort,       JUMP,   NORM,   NONE,   511,
//                           &Inp.uls,          JUMP,   NORM,   NONE,   512,
                           &HornReturnFlag,   NORM,   ABORT,  EQ9,    514,
                           &OKToAdvance,      JUMP,   NORM,   NONE,   515,
                           &TimerFlag,        END,    END,    NONE,   516 };

SSTATES PreTrigger[]    = {&AbortFlag,        ABORT,  NORM,   NONE,  2100,
                           &CycleAbort,       JUMP,   NORM,   NONE,  2101,
                           &MissingPartFlag,  ABORT,  NORM,   NC8,   2102,
                           &Inp.BothPB,       NORM,   ABORT,  EQ23,  2103,
                           &Inp.Trigger,      ABORT,  NORM,   NC3,   2104,
                           &DistFlag,         JUMP,   NORM,   NONE,  2105,
                           &PTSTimerFlag,     ALJUMP, NORM,   EQ18,  2106,
                           &Inp.OL,           ABORT,  NORM,   OL2,   2107,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,  2108,
                           &TimerFlag,        END,    END,    NONE,  2109  };   /*Test State*/


/*-- Use this if pretrigger is off  --*/

SSTATES ExtTrigDelay[] = {&AbortFlag,          ABORT, NORM,   NONE,   11600,
                          &CycleAbort,         JUMP,  NORM,   NONE,   11601,
                          &Inp.ExtTrgDelay,    NORM,  JUMP,   NONE,   11602,
                          &TriggerLostFlag,    ALJUMP,NORM,   CM14,   11603,
                          &TrgDelayTimeout,    ABORT, NORM,   NC13,   11604,
                          &Inp.SVInterLock,    NORM,  ABORT,  NC14,   11605,
                          &ECycleHistFlag,     ABORT, NORM,   NC7,    11606,
                          &TimerFlag,          END,   END,    NONE,   11607 };

SSTATES WaitTrs1[]      = {&AbortFlag,        ABORT,  NORM,   NONE,   600,
                           &CycleAbort,       JUMP,   NORM,   NONE,   601,
                           &Inp.BothPB,       NORM,   ABORT,  EQ23,   602,
                           &DistFlag,         JUMP,   NORM,   NONE,   603,
//                           &Inp.uls,          ALJUMP, NORM,   EQ3,    604,
                           &Inp.uls,          ABORT,  NORM,   EQ3,    604,
//                         &ForceStepFlag,    NORM,   JUMP,   NONE,   605,
                           &MissingPartFlag,  ABORT,  NORM,   NC8,    606,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   607,
                           &TimerFlag,        END,    ALJUMP, NC4,    608  };   /*Test State*/

/*--  Use this if pretrigger is on  --*/

SSTATES WaitTrs1PT[]    = {&AbortFlag,        ABORT,  NORM,   NONE,   600,
                           &CycleAbort,       JUMP,   NORM,   NONE,   601,
                           &Inp.BothPB,       NORM,   ABORT,  EQ23,   602,
                           &DistFlag,         JUMP,   NORM,   NONE,   603,
//                           &Inp.uls,          ALJUMP, NORM,   EQ3,    604,
                           &Inp.uls,          ABORT,  NORM,   EQ3,    604,
//                         &ForceStepFlag,    NORM,   JUMP,   NONE,   605,
                           &MissingPartFlag,  ABORT,  NORM,   NC8,    606,
                           &Inp.OL,           ABORT,  NORM,   OL2,    607,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   608,
                           &TimerFlag,        END,    ALJUMP, NC4,    609  };   /*Test State*/

/*-- Use this if pretrigger is off  --*/

SSTATES WaitTrs2[]      = {&AbortFlag,        ABORT,  NORM,   NONE,   800,
                           &CycleAbort,       JUMP,   NORM,   NONE,   801,
                           &Inp.BothPB,       NORM,   ABORT,  EQ23,   802,
                           &Inp.Trigger,      JUMP,   NORM,   NONE,   803,
                           &Inp.uls,          ABORT,  NORM,   EQ3,    804,
                           &MissingPartFlag,  ABORT,  NORM,   NC8,    805,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   806,
                           &TimerFlag,        END,    ABORT,  NC4,    807  };

/*--  Use this if pretrigger is on  --*/

SSTATES WaitTrs2PT[]    = {&AbortFlag,        ABORT,  NORM,   NONE,   800,
                           &CycleAbort,       JUMP,   NORM,   NONE,   801,
                           &Inp.BothPB,       NORM,   ABORT,  EQ23,   802,
                           &Inp.Trigger,      JUMP,   NORM,   NONE,   803,
                           &Inp.uls,          ABORT,  NORM,   EQ3,    804,
//                           &Inp.uls,          ALJUMP, NORM,   EQ3,    804,
                           &MissingPartFlag,  ABORT,  NORM,   NC8,    805,
                           &Inp.OL,           ABORT,  NORM,   OL2,    806,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   607,
                           &TimerFlag,        END,    ABORT,  NC4,    808  };

SSTATES WaitTrs4[]      = {&AbortFlag,        ABORT,  NORM,   NONE,   2400,
                           &PlsWaitTimerFlag, NORM,   JUMP,   NONE,   2402,
                           &StaggerFlag,      JUMP,   NORM,   NONE,   2403,
                           &TimerFlag,        END,    END,    NONE,   2404 };

SSTATES TrigDelay[]     = {&AbortFlag,        ABORT,  NORM,   NONE,   2700,
                           &TriggerDelayFlag, NORM,   JUMP,   NONE,   2701,
                           &CycleAbort,       JUMP,   NORM,   NONE,   2702,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,   2703,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   2704,
                           &TimerFlag,        END,    JUMP,   NONE,   2705 };

SSTATES Weld1HH[]       = {&AbortFlag,        ABORT,  NORM,   NONE,  10300,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,   10301,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,  10302,
                           &CycleAbort,       ALJUMPNORM,NORM,NONE,  10303,
                           &StepTimeFlag,     NORM,   JUMP,   NONE,  10304,
                           &SonicsAbort,      ALJUMPNORM,NORM,NONE,  10305,
                           &TimerFlag,        END,    JUMP,   NONE,  10306  };

SSTATES PLC1HH[]        = {&AbortFlag,        ABORT,  NORM,   NONE,  10350,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,   10351,
                           &TriggerLostFlag,  JUMP,   NORM,   NONE,  10352,
                           &CycleAbort,       ALJUMPNORM,NORM,NONE,  10353,
                           &StepTimeFlag,     NORM,   JUMP,   NONE,  10354,
                           &SonicsAbort,      ALJUMPNORM,NORM,NONE,  10355,
                           &TimerFlag,        END,    JUMP,   NONE,  10356  };

SSTATES Weld1[]         = {&AbortFlag,        ABORT,  NORM,   NONE,   900,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,    901,
//                           &CycleAbort,       JUMP,   NORM,   NONE,   902,
                           &CycleAbort,       ALJUMPNORM,NORM,NONE,   902,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,   903,
                           &StepTimeFlag,     NORM,   JUMP,   NONE,   904,
//                           &SonicsAbort,      JUMP,   NORM,   NONE,   905,
                           &SonicsAbort,      ALJUMPNORM,NORM,NONE,   905,
                           &MissingPartFlag,  ABORT,  NORM,   NC8,    906,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   907,
                           &TimerFlag,        END,    JUMP,   NONE,   908  };

SSTATES Weld1A[]        = {&Inp.OnePB,        NORM,   JUMP,   NONE,   950,
                           &AbortFlag,        ABORT,  NORM,   NONE,   951,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,    952,
                           &CycleAbort,       ABORT,  NORM,   NONE,   953,
                           &SonicsAbort,      JUMP,   NORM,   NONE,   954,
                           &TimerFlag,        END,    END,    NONE,   955  };

SSTATES Weld2[]         = {&AbortFlag,        ABORT,  NORM,   NONE,   1000,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,    1001,
                           &CycleAbort,       JUMP,   NORM,   NONE,   1002,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,   1003,
                           &WTimeFlag,        NORM,   JUMP,   NONE,   1004,
                           &SonicsAbort,      JUMP,   NORM,   NONE,   1005,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   1006,
                           &TimerFlag,        END,    JUMP,   NONE,   1007 };
                                            
SSTATES Weld2HH[]       = {&AbortFlag,        ABORT,  NORM,   NONE,  10800,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,   10801,
                           &CycleAbort,       JUMP,   NORM,   NONE,  10802,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,  10803,
                           &WTimeFlag,        NORM,   JUMP,   NONE,  10804,
                           &SonicsAbort,      JUMP,   NORM,   NONE,  10805,
                           &TimerFlag,        END,    JUMP,   NONE,  10806 };
                                            
SSTATES PLC2HH[]        = {&AbortFlag,        ABORT,  NORM,   NONE,  10850,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,   10851,
                           &CycleAbort,       JUMP,   NORM,   NONE,  10852,
                           &TriggerLostFlag,  JUMP,   NORM,   NONE,  10853,
                           &WTimeFlag,        NORM,   JUMP,   NONE,  10854,
                           &SonicsAbort,      JUMP,   NORM,   NONE,  10855,
                           &TimerFlag,        END,    JUMP,   NONE,  10856 };
                                            
SSTATES Weld3[]         = {&AbortFlag,        ABORT,  NORM,   NONE,   2500,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,    2501,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,   2502,
                           &CycleAbort,       JUMP,   NORM,   NONE,   2503,
                           &StepTimeFlag,     NORM,   JUMP,   NONE,   2504,
                           &MissingPartFlag,  ABORT,  NORM,   NC8,    2505,
                           &SonicsAbort,      JUMP,   NORM,   NONE,   2506,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   2507,
                           &TimerFlag,        END,    JUMP,   NONE,   2508 };

SSTATES Weld3HH[]       = {&AbortFlag,        ABORT,  NORM,   NONE,  11100,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,   11101,
                           &CycleAbort,       JUMP,   NORM,   NONE,  11102,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,  11103,
                           &StepTimeFlag,     NORM,   JUMP,   NONE,  11104,
                           &SonicsAbort,      JUMP,   NORM,   NONE,  11105,
                           &TimerFlag,        END,    JUMP,   NONE,  11106 };

SSTATES Weld4[]         = {&AbortFlag,        ABORT,  NORM,   NONE,   2600,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,    2601,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,   2602,
                           &CycleAbort,       JUMP,   NORM,   NONE,   2603,
                           &WTimeFlag,        NORM,   JUMP,   NONE,   2604,
                           &SonicsAbort,      JUMP,   NORM,   NONE,   2605,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   2606,
                           &TimerFlag,        END,    JUMP,   NONE,   2607 };
                                            
SSTATES Weld4HH[]       = {&AbortFlag,        ABORT,  NORM,   NONE,  11200,
                           &Inp.OL,           ALJUMPNORM,NORM,OL4,   11201,
                           &CycleAbort,       JUMP,   NORM,   NONE,  11202,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,  11203,
                           &WTimeFlag,        NORM,   JUMP,   NONE,  11204,
                           &SonicsAbort,      JUMP,   NORM,   NONE,  11205,
                           &TimerFlag,        END,    JUMP,   NONE,  11206 };
                                            
SSTATES EnerBrake[]     = {&AbortFlag,        ABORT,  NORM,   NONE,   1300,
                           &Inp.OL,           ALJUMPNORM,NORM,OL10,   1301,
                           &CycleAbort,       JUMP,   NORM,   NONE,   1302,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,   1303,
                           &EnergyBrakeFlag,  JUMP,   NORM,   NONE,   1304,
                           &SonicsAbort,      JUMP,   NORM,   NONE,   1305,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   1306,
                           &TimerFlag,        END,    END,    NONE,   1307 };
                           
SSTATES EnerBrakeHH[]   = {&AbortFlag,        ABORT,  NORM,   NONE,   1310,
                           &Inp.OL,           ALJUMPNORM,NORM,OL10,   1311,
                           &CycleAbort,       JUMP,   NORM,   NONE,   1312,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,   1313,
                           &EnergyBrakeFlag,  JUMP,   NORM,   NONE,   1314,
                           &SonicsAbort,      JUMP,   NORM,   NONE,   1315,
                           &TimerFlag,        END,    END,    NONE,   1316 };
                                            
SSTATES PLCBrakeHH[]    = {&AbortFlag,        ABORT,  NORM,   NONE,   1350,
                           &Inp.OL,           ALJUMPNORM,NORM,OL10,   1351,
                           &CycleAbort,       JUMP,   NORM,   NONE,   1352,
                           &TriggerLostFlag,  JUMP,   NORM,   NONE,   1353,
                           &EnergyBrakeFlag,  JUMP,   NORM,   NONE,   1354,
                           &SonicsAbort,      JUMP,   NORM,   NONE,   1355,
                           &TimerFlag,        END,    END,    NONE,   1356 };
                                            
                                                                                        
SSTATES SonicsOff[]     = {&TimerFlag,        JUMP,   JUMP,   NONE,   1750 };


SSTATES Hold[]          = {&AbortFlag,        ABORT,  NORM,   NONE,   1100,
                           &Inp.OL,           ALNORM, NORM,   OL4,    1101,
                           &CycleAbort,       JUMP,   NORM,   NONE,   1102,
                           &ECycleHistFlag,   ABORT,  NORM,   CM15,   1103,
                           &HTimeFlag,        NORM,   JUMP,   NONE,   1104,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM1,    1105,
                           &Inp.SVInterLock,  NORM,   ABORT,  NC14,   1106,
                           &TimerFlag,        END,    JUMP,   NONE,   1107 };

SSTATES PLCHoldHH[]     = {&AbortFlag,        ABORT,  NORM,   NONE,  10750,
                           &Inp.OL,           ALNORM, NORM,   OL4,   10751,
                           &CycleAbort,       JUMP,   NORM,   NONE,  10752,
                           &ECycleHistFlag,   ABORT,  NORM,   CM15,  10753,
                           &HTimeFlag,        NORM,   JUMP,   NONE,  10754,
//                         &Inp.SingleStart,  NORM,   ALJUMP, CM1,   10755,
//                           &TriggerLostFlag,  JUMP,   NORM,   NONE,  10755,
                           &TimerFlag,        END,    JUMP,   NONE,  10756 };

SSTATES HoldHH[]        = {&AbortFlag,        ABORT,  NORM,   NONE,  10700,
                           &Inp.OL,           ALNORM, NORM,   OL4,   10701,
                           &CycleAbort,       JUMP,   NORM,   NONE,  10702,
                           &ECycleHistFlag,   ABORT,  NORM,   CM15,  10703,
                           &HTimeFlag,        NORM,   JUMP,   NONE,  10704,
//                         &Inp.SingleStart,  NORM,   ALJUMP, CM1,   10705,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM1,   10705,
                           &TimerFlag,        END,    JUMP,   NONE,  10706 };

SSTATES AlterHold[]     = {&AbortFlag,        ABORT,  NORM,   NONE,   1110,
                           &Inp.OL,           ALNORM, NORM,   OL4,    1111,
                           &CycleAbort,       JUMP,   NORM,   NONE,   1112,
                           &ECycleHistFlag,   ABORT,  NORM,   CM15,   1113,
                           &HTimeFlag,        NORM,   JUMP,   NONE,   1114,
                           &TimerFlag,        END,    JUMP,   NONE,   1116 };

SSTATES AlterHoldHH[]   = {&AbortFlag,        ABORT,  NORM,   NONE,  10400,
                           &Inp.OL,           ALNORM, NORM,   OL4,   10401,
                           &CycleAbort,       JUMP,   NORM,   NONE,  10402,
                           &ECycleHistFlag,   ABORT,  NORM,   CM15,  10403,
                           &HTimeFlag,        NORM,   JUMP,   NONE,  10404,
//                         &Inp.SingleStart,  NORM,   ALJUMP, NONE,  10405,
                           &TriggerLostFlag,  ALJUMP, NORM,   CM14,  10405,
                           &TimerFlag,        END,    JUMP,   NONE,  10406 };

SSTATES Limits[]        = {&TimerFlag,        JUMP,   JUMP,   NONE,   1201 };

SSTATES ABDelay[]       = {&AbortFlag,        ABORT,  NORM,   NONE,   1500,
                           &CycleAbort,       JUMP,   NORM,   NONE,   1501,
                           &ECycleHistFlag,   ABORT,  NORM,   CM15,   1502,
//                         &ABTimeFlag,       NORM,   JUMP,   NONE,   1503,
                           &ABTimeDelayFlag,  NORM,   JUMP,   NONE,   1503,
                           &HornReturnFlag,   NORM,   ABORT,  EQ9,    1504,
                           &TimerFlag,        END,    JUMP,   NONE,   1505 };

SSTATES ABDelayHH[]     = {&AbortFlag,        ABORT,  NORM,   NONE,  10500,
                           &CycleAbort,       JUMP,   NORM,   NONE,  10501,
                           &ECycleHistFlag,   ABORT,  NORM,   CM15,  10502,
                           &ABTimeDelayFlag,  NORM,   JUMP,   NONE,  10503,
                           &Inp.SingleStart,  NORM,   ALJUMP, NONE,  10504,
                           &TimerFlag,        END,    JUMP,   NONE,  10505 };

SSTATES ABTime[]        = {&AbortFlag,        ABORT,  NORM,   NONE,   1600,
                           &CycleAbort,       JUMP,   NORM,   NONE,   1601,
                           &ECycleHistFlag,   ABORT,  NORM,   CM15,   1602,
                           &ABTimeFlag,       NORM,   JUMP,   NONE,   1603,
                           &HornReturnFlag,   NORM,   ABORT,  EQ9,    1604,
                           &Inp.OL,           ALJUMPNORM,NORM,OL6,    1605,
                           &TimerFlag,        END,    JUMP,   NONE,   1606 };

SSTATES ABTimeHH[]      = {&AbortFlag,        ABORT,  NORM,   NONE,  10600,
                           &CycleAbort,       JUMP,   NORM,   NONE,  10601,
                           &ECycleHistFlag,   ABORT,  NORM,   CM15,  10602,
                           &ABTimeFlag,       NORM,   JUMP,   NONE,  10603,
                           &HornReturnFlag,   NORM,   ABORT,  EQ9,   10604,
                           &Inp.OL,           ALJUMPNORM,NORM,OL6,   10605,
                           &Inp.SingleStart,  NORM,   ALJUMP, NONE,  10606,
                           &TimerFlag,        END,    JUMP,   NONE,  10607 };

SSTATES RampSonics[]    = {&RampEndFlag,      JUMP,   NORM,   NONE,   1900,
                           &CycleAbort,       JUMP,   NORM,   NONE,   1901,
                           &HornReturnFlag,   NORM,   ABORT,  EQ9,    1902,
                           &Inp.OL,           ALJUMPNORM,NORM,NONE,   1903,
                           &TimerFlag,        END,    END,    NONE,   1904 };


SSTATES Nop[]           = {&TimerFlag,        JUMP,   JUMP,   NONE,   1200 };


SSTATES PowerDown[]     = {&Inp.PwrOff,       NORM,   NORM, NONE,   9900,
                           &PDownDelay,       JUMP,   NORM,   NONE,   9901,
//                           &PowerDownAborted, ALJUMP, NORM,   NONE,   9902,
                           &TimerFlag,        END,    END,    NONE,   9903  };

/*---  This state is meant to never, NEVER, Ever exit ---*/

SSTATES PowerDown1[]    = {&TimerFlag,        END,    END,    NONE,   9904  };




SSTATES SCComp[]        = {&PlsWaitTimerFlag, NORM,   JUMP,   NONE,   3405,
                           &TimerFlag,         END,   END,    NONE,   3406};

SSTATES CalbPBs[]       = {&Inp.OnePB,        NORM,   NORM,   NONE,   3500,
                           &Inp.uls,          NORM,   ABORT,  EQ2,    3501,
                           &StaggerFlag,      JUMP,   NORM,   NONE,   3502,
                           &Inp.BothPB,       JUMP,   NORM,   NONE,   3503,
                           &TimerFlag,        END,    END,    NONE,   3504  };   /*Test State*/
                          
                          
SSTATES SeekWait[]      = {&SeekEndFlag,       JUMP,  NORM,   NONE,   1700,
                           &CycleAbort,        JUMP,  NORM,   NONE,   1701,
                           &HornReturnFlag,    NORM,  ABORT,  EQ9,    1702,
                           &TimerFlag,         END,   END,    NONE,   1703 };

SSTATES SeekWaitHH[]    = {&SeekEndFlag,       JUMP,  NORM,   NONE,  10900,
                           &CycleAbort,        JUMP,  NORM,   NONE,  10901,
                           &Inp.SingleStart,   NORM,  ALJUMP, NONE,  10902,
                           &TimerFlag,         END,   END,    NONE,  10903 };

SSTATES ParamUpdate[]   = {&ParamUpdateFlag,   NORM,  NORM,   NONE,   1800,  
                           &TimerFlag,         END,   END,    NONE,   1801 };
                          

/*                         Variable           TRUE    FALSE   Alarm   Trace */
/*                         pointer            Action  Action  Code    Code  */
/*                         ----------         ------- ------- ------- ------*/

SSTATES WaitTime[]       = {&PlsWaitTimerFlag,NORM,   JUMP,   NONE,   2100,
                            &TimerFlag,       END,    END,    NONE,   2101  };

SSTATES Trigger[]        = {&Inp.Trigger,     NORM,   ALJUMP, NONE,   2200,
                            &Inp.SVInterLock, NORM,   ABORT,  NC14,   2201,
                            &TimerFlag,       JUMP,   JUMP,   NONE,   2202 };

SSTATES CalTrigger[]     = {&Inp.Trigger,     NORM,   ALJUMP, NONE,   3700,
                            &TimerFlag,       JUMP,   JUMP,   NONE,   3701 };

SSTATES TriggerHH[]      = {&Inp.SingleStart, NORM,   ALJUMP, NONE,  11001,
                            &TimerFlag,       JUMP,   JUMP,   NONE,  11002 };


SSTATES MenuSync[]       = {&AdvanceMenuFlag, JUMP,   NORM,   NONE,   2000,
                            &TimerFlag,       END,    END,    NONE,   2002 };

SSTATES FinalData[]      = {&IsThereAGraphPrinting,NORM,JUMP, NONE,   9998,
                            &TimerFlag,       END,    END,    NONE,   9999 };

SSTATES DebugState[]     = {&TimerFlag,       NORM,   JUMP,   NONE,   9000,
                            &TimerFlag,       END,    END,    NONE,   9001 };


SSTATES TestMode[]       = {&TestTimerFlag,   JUMP,   NORM,   NONE,   4000,
                            &Inp.uls,         NORM,   ALJUMP, EQ2,    4001,
                            &Inp.DoorOpen,    ALJUMP, NORM,   EQ4,    4002,
                            &Inp.OL,          ALJUMPNORM,NORM,OL1,    4003,
                            &TimerFlag,       END,    END,    NONE,   4004 };


/*-----  Here are the power up sub states  -----*/

SSTATES PInitial[]      = {&SystemOK,         JUMP,   NORM,   NONE,   150,
//                           &Inp.OL,           ALJUMPNORM,NORM,OL3,    151,
                           &TimerFlag,        END,    END,    NONE,   152  };

SSTATES PChkAct[]       = {&ActDone,          JUMP,   NORM,   NONE,   160,
                           &TimerFlag,        END,    END,    NONE,   162  };

SSTATES PChkPwrSup[]    = {&PSDone,           JUMP,   NORM,   NONE,   170,
                           &TimerFlag,        END,    END,    NONE,   172  };

SSTATES PChkCntrls[]    = {&ControlsDone,     JUMP,   NORM,   NONE,   180,
                           &TimerFlag,        END,    END,    NONE,   183  };

SSTATES PChkStack[]     = {&StackDone,        JUMP,   NORM,   NONE,   190,
                           &TimerFlag,        END,    END,    NONE,   191  };


/*                    Substate    Timeout     Pass Code     Entry Code    JUMP Code     ALJUMP Code   State               */
/*                    Name        pointer                                                                                 */
/*                    ----------  -------     ----------    ----------    -----------   ----------    ------------        */
STATE TopOfList    = {Initial,    &TimeOff,   Nothing,      Nothing,      Restart,      NeverStart,   NOP       };

STATE ReadySt      = {Ready,      &TimeOff,   TestReady,    EnterReady,   ExitReady,    Nothing,      READYSTATE          };
STATE ReadyHHST    = {ReadyHH,    &TimeOff,   TestReady,    EnterReady,   ExitReady,    Nothing,      READYSTATE          };

STATE PBState      = {PalmButtons,&Stagger,   TestPB,       StartPB,      ExitPB,       AlarmExitPB,  PBSTATE             };
STATE PBStateHHST  = {PBHH,       &Stagger,   TestPBHH,     StartPB,      ExitPBHH,     AlarmExitPB,  PBSTATE             };
/*----- SVInterlock  -----*/
STATE WaitSVST     = {WaitSVInput,&MaxWTime,  TestSVInput,   EnterSV,     ExitSVState,  Nothing,      WAITFORSVINPUTSTATE };

// continuous mode
STATE OnePBState   = {PalmButton, &TimeOff,   Nothing,      StartPB,      Nothing,      AlarmExitPB,  PBSTATE             };
STATE WaitUls      = {WaitUls1,   &UlsTime,   TestUls,      EnterUls,     ExitULS,      AlarmUls,     WAITFORULSCLEARSTATE};
STATE WaitUlsUp    = {WaitUls2,   &TimeOff,   TestUlsUp,    EnterUlsUp,   ExitUlsUp,    AlarmUls,     WAITFORULSMADESTATE };

/*--  This first group is used when pretrigger is off  --*/

STATE WaitTrs1DST  = {WaitTrs1,   &TrsTime,   TestTrs1D,    EntryTrs1,    ExitTrs1,     AlarmTrs1,    WAITFORTRSSTATE1    };
STATE WaitTrs1ST   = {WaitTrs1,   &TrsTime,   TestTrs1,     EntryTrs1,    ExitTrs1,     AlarmTrs1,    WAITFORTRSSTATE1    };
STATE WaitTrs2DST  = {WaitTrs2,   &TrsTime,   TestTrs2D,    EntryTrs2,    ExitTrs2,     AlarmTrs1,    WAITFORTRSSTATE2    };
STATE WaitTrs2ST   = {WaitTrs2,   &TrsTime,   TestTrs2,     EntryTrs2,    ExitTrs2,     AlarmTrs1,    WAITFORTRSSTATE2    };

/*--  This second group is used when pretrigger is on  --*/

STATE WaitTrs1DSTPT= {WaitTrs1PT, &TrsTime,   TestTrs1D,    EntryTrs1,    ExitTrs1,     AlarmTrs1,    WAITFORTRSSTATE1    };
STATE WaitTrs1STPT = {WaitTrs1PT, &TrsTime,   TestTrs1,     EntryTrs1,    ExitTrs1,     AlarmTrs1,    WAITFORTRSSTATE1    };
STATE WaitTrs2DSTPT= {WaitTrs2PT, &TrsTime,   TestTrs2D,    EntryTrs2,    ExitTrs2,     AlarmTrs1,    WAITFORTRSSTATE2    };
STATE WaitTrs2STPT = {WaitTrs2PT, &TrsTime,   TestTrs2,     EntryTrs2,    ExitTrs2,     AlarmTrs1,    WAITFORTRSSTATE2    };

STATE UpdateState  = {ParamUpdate,&TimeOff,   Nothing,      Nothing,      Nothing,      Nothing,      UPDATESTATE         }; 

STATE PreTrsDST    = {PreTrigger, &TimeOff,   TestPTS,      EnterPTS,     StartPTS,     Nothing,      WAITFORPTSSTATE     };
STATE PreTrsST     = {PreTrigger, &TimeOff,   TestPTS,      EnterPTS,     StartPTS,     Nothing,      WAITFORPTSSTATE     };
STATE TriggerST    = {Trigger,    &TimeOff,   Nothing,      Nothing,      TriggerBeep,  Nothing,      TRIGGEREDSTATE      };
STATE TriggerHHST  = {TriggerHH,  &TimeOff,   Nothing,      Nothing,      HHBeep,       Nothing,      TRIGGEREDSTATE      };
STATE TrigDelayST  = {TrigDelay,  &MaxWTime,  Nothing,      EnterTrigDly, ExitTrigDly,  Nothing,      TRIGGERDELAYSTATE   };
STATE ExtTrigDelayST={ExtTrigDelay,&MaxWTime, TestExtTrigDly,EnterExtTrigDly, Nothing,   Nothing,      EXTTRIGDELAYSTATE   };


/*                    Substate    Timeout     Pass Code     Entry Code    JUMP Code     ALJUMP Code   State               */
/*                    Name        pointer                                                                                 */
/*                    ----------  -------     ----------    ----------    -----------   ----------    ------------        */

/*----- Time Mode -----*/

STATE SonicsOn1DST = {Weld1,      &MaxWTime,  CheckSonics1D,  StartSonic1,  StopSonic1,   AlStopSonics, WELDTIMESTATE    };
STATE SonicsOn1ST  = {Weld1,      &MaxWTime,  CheckSonics1,   StartSonic1,  StopSonic1,   AlStopSonics, WELDTIMESTATE    };
STATE SonicsOn2DST = {Weld2,      &MaxWTime,  CheckSonics2D,  StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE   };
STATE SonicsOn2ST  = {Weld2,      &MaxWTime,  CheckSonics2,   StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE   };
STATE SonicsOnHHST = {Weld1HH,    &MaxWTime,  CheckSonics1HH, StartSonic1HH,Nothing,      AlStopHH,     WELDTIMESTATE    };
STATE SonicsOn2HHST= {Weld2HH,    &MaxWTime,  CheckSonics1HH, StartSonic2,  StopSonic2HH, AlStopHH,     WELDTIME2STATE   };
STATE PLCOnHHST    = {PLC1HH,     &MaxWTime,  CheckSonics1HH, StartSonic1HH,Nothing,      AlStopHH,     WELDTIMESTATE    };
STATE PLCOn2HHST   = {PLC2HH,     &MaxWTime,  CheckSonics1HH, StartSonic2,  StopSonic2HH, AlStopHH,     WELDTIME2STATE   };


/*----- Energy Mode -----*/

STATE SonicsOn3DST = {Weld3,      &MaxWTime,  CheckSonics3D,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn3ST  = {Weld3,      &MaxWTime,  CheckSonics3, StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn4DST = {Weld4,      &MaxWTime,  CheckSonics4D,StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn4ST  = {Weld4,      &MaxWTime,  CheckSonics4, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn3HHST= {Weld3HH,    &MaxWTime,  CheckEnergyHH,StartNonTimeHH, Nothing,    AlStopHH,     WELDTIMESTATE       };
STATE SonicsOn4HHST= {Weld4HH,    &MaxWTime,  CheckEnergyHH,CheckEnergyHH,StopSonic2HH, AlStopHH,     WELDTIME2STATE      };


/*----- Absolute Mode -----*/

STATE SonicsOn3A   = {Weld3,      &MaxWTime,  CheckSonics3A,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn5    = {Weld4,      &MaxWTime,  CheckSonics5, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };


/*----- Collapse Mode -----*/

STATE SonicsOn3B   = {Weld3,      &MaxWTime,  CheckSonics3B,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn6    = {Weld4,      &MaxWTime,  CheckSonics6, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };


/*----- Peak Power Mode -----*/

STATE SonicsOn3CDST= {Weld3,      &MaxWTime,  CheckSonics3CD,StartSonic3, StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn3CST = {Weld3,      &MaxWTime,  CheckSonics3C,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn7DST = {Weld4,      &MaxWTime,  CheckSonics7D,StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn7ST  = {Weld4,      &MaxWTime,  CheckSonics7, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOnPP1ST= {Weld3HH,    &MaxWTime,  CheckPPHH,    StartNonTimeHH, Nothing,    AlStopHH,     WELDTIMESTATE       };
STATE SonicsOnPP2ST= {Weld4HH,    &MaxWTime,  CheckPPHH,    StartSonic2,  StopSonic2HH, AlStopHH,     WELDTIME2STATE      };


/*                    Substate    Timeout     Pass Code     Entry Code    JUMP Code     ALJUMP Code   State               */
/*                    Name        pointer                                                                                 */
/*                    ----------  -------     ----------    ----------    -----------   ----------    ------------        */

/*----- Ground Detect Mode -----*/

STATE SonicsOn8DST = {Weld3,      &MaxWTime,  CheckSonics8D,StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn8ST  = {Weld3,      &MaxWTime,  CheckSonics8, StartSonic3,  StopSonic1,   AlStopSonics, WELDTIMESTATE       };
STATE SonicsOn9DST = {Weld4,      &MaxWTime,  CheckSonics9D,StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOn9ST  = {Weld4,      &MaxWTime,  CheckSonics9, StartSonic2,  StopSonic2,   AlStopSonics, WELDTIME2STATE      };
STATE SonicsOnGD1ST= {Weld3HH,    &MaxWTime,  CheckGdDetHH, StartNonTimeHH, Nothing,    AlStopHH,     WELDTIMESTATE       };
STATE SonicsOnGD2ST= {Weld4HH,    &MaxWTime,  CheckGdDetHH, StartSonic2,  StopSonic2HH, AlStopHH,     WELDTIME2STATE      };


/*----- Continuous Mode -----*/

STATE SonicsOn1A   = {Weld1A,     &TimeOff,   CheckSonics1A,StartSonic1A, StopSonic1,   AlStopSonics, WELDTIMESTATE       };


STATE WeldOffST    = {SonicsOff,  &TimeOff,   Nothing,      Nothing,      Nothing,      Nothing,      ENDOFSONICS         };
STATE WeldOffHHST  = {SonicsOff,  &TimeOff,   Nothing,      Nothing,      StopAllSonic, Nothing,      ENDOFSONICS         };

/*----- Energy Braking -----*/

STATE EnerBrakeST  = {EnerBrake,  &TimeOff,   CheckBrake,   StartBrake,   StopAllSonic, StopAllSonic, WELDTIME2STATE      };
STATE EnerBrakeHHST= {EnerBrakeHH,&TimeOff,   CheckBrake,   StartBrake,   StopAllSonicHH,StopAllSonicHH,WELDTIME2STATE    };
STATE PLCBrakeHHST = {PLCBrakeHH, &TimeOff,   CheckBrake,   StartBrake,   StopAllSonicHH,StopAllSonicHH,WELDTIME2STATE    };


/*----- Hold -----*/

STATE HoldTimeDST  = {Hold,       &MaxHTime,  CheckHold,    StartHold,    StopHold,     StopHold,     HOLDTIMESTATE       };
STATE HoldTimeST   = {Hold,       &MaxHTime,  CheckHold,    StartHold,    StopHold,     StopHold,     HOLDTIMESTATE       };
STATE HoldTimeHHST = {HoldHH,     &MaxHTime,  CheckHold,    StartHold,    StopHold,     StopHold,     HOLDTIMESTATE       };
STATE PLCTimeHHST  = {PLCHoldHH,  &MaxHTime,  CheckHold,    StartHold,    StopHold,     StopHold,     HOLDTIMESTATE       };
STATE FakeHold     = {AlterHold,  &MaxHTime,  Nothing,      StartAHold,   StopAHold,    Nothing,      HOLDTIMESTATE       };
STATE FakeHoldHHST = {AlterHoldHH,&MaxHTime,  Nothing,      StartAHold,   StopAHold,    Nothing,      HOLDTIMESTATE       };

STATE CheckLimitsST= {Limits,     &TimeOff,   Nothing,      Nothing,      Nothing,      Nothing,      PROCESSALARMSSTATE  };

/*----- Afterburst -----*/

STATE ABDelayST    = {ABDelay,    &MaxDTime,  TestABDly,    StartABDly,   StopABDly,    ALStopABD,    AFTERBURSTDELAYSTATE};
STATE ABTimeST     = {ABTime,     &MaxABTime, TestABTme,    StartABTme,   StopABTme,    ALStopABT,    AFTERBURSTTIMESTATE };
STATE RampSonicsST = {RampSonics, &TimeOff,   RampOff,      Nothing,      PSIdle,       PSIdle,       RAMPSONICSSTATE     };
STATE ABDelayHHST  = {ABDelayHH,  &MaxDTime,  TestABDlyHH,  StartABDly,   StopABDly,    ALStopABD,    AFTERBURSTDELAYSTATE};
STATE ABTimeHHST   = {ABTimeHH,   &MaxABTime, TestABTmeHH,  StartABTme,   StopABTme,    ALStopABT,    AFTERBURSTTIMESTATE };

/*                    Substate    Timeout     Pass Code     Entry Code    JUMP Code     ALJUMP Code   State               */
/*                    Name        pointer                                                                                 */
/*                    ----------  -------     ----------    ----------    -----------   ----------    ------------        */

/*----- Seek -----*/

STATE SeekState    = {SeekWait,   &TimeOff,   CheckSeek,    StartSeek,    StopSeek,     StopSeek,     SEEKSTATE           }; 
STATE SeekStateHH  = {SeekWaitHH, &TimeOff,   CheckSeekHH,  StartSeekHH,  StopSeek,     StopSeek,     SEEKSTATE           }; 

STATE PreReady     = {CheckReady, &TimeOff,   TestPreReady, EPreReady,    ClearAbort,   Nothing,      PREREADYSTATE       };
STATE PreReadyHHST = {CheckReadyHH,&TimeOff,  TestPreReadyHH,EPreReady,   ClearAbort,   Nothing,      PREREADYSTATE       };
STATE EndOfList    = {Nop,        &TimeOff,   Nothing,      Restart,      Restart,      Restart,      NOP                 };
STATE NopList      = {Nop,        &TimeOff,   Nothing,      Nothing,      Nothing,      Nothing,      NOP                 };

STATE StartData    = {Nop,        &TimeOff,   Nothing,      StartDataCollection,Nothing,Nothing,      NOP                 };
STATE StopData     = {Nop,        &TimeOff,   Nothing,      StopDataCollection,Nothing, Nothing,      NOP                 };


/*-----  Here are the Power On/Off States  -----*/

STATE PowerOn1     = {PInitial,   &TimeOff,   TestPO1,      PowerUp,      Copyright,    Nothing,      NOP                 };
STATE PowerOn2     = {PChkCntrls, &TimeOff,   TestPO2,      DispCtrl,     Nothing,      Nothing,      NOP                 };
STATE PowerOn3     = {PChkAct,    &TimeOff,   TestPO3,      DispAct,      Nothing,      Nothing,      NOP                 };
STATE PowerOn4     = {PChkPwrSup, &TimeOff,   TestPO4,      DispPS,       Nothing,      Nothing,      NOP                 };
STATE PowerOn5     = {PChkStack,  &TimeOff,   TestPO5,      DispStack,    PowerOnOK,    Nothing,      POWERUPSEEKSTATE    };
STATE PowerOn6     = {Nop,        &TimeOff,   Nothing,      Nothing,      NewState,     Nothing,      POWERUPSEEKSTATE    };



STATE PwrDown      = {PowerDown,  &TimeOff,   CheckPD,      EnterPDown,   PowerOff,     Nothing,      POWERDOWNSTATE      };
STATE PwrDown1     = {PowerDown1, &TimeOff,   Nothing,      PowerOffLock, Nothing,      Nothing,      POWERDOWNSTATE      };



/*-----  Other useful and sometimes used states  -----*/

STATE MenuSyncST   = {MenuSync,   &TimeOff,   CheckMenuSync,Nothing, UpdateCalibrationState,Nothing,      MENUSYNCSTATE       };
/* Can't use FINALDATASTATE because it would cause two FinalResults messages to be sent */
STATE FinalDataST  = {FinalData,  &TimeOff,   Nothing,      EnterFData,   SendFData,    Nothing,      NOP                 };

STATE PreReadyTestSt= {CheckReady,&TimeOff,   TestTestPreReady, EPreReady,    ClearAbort,   Nothing,      PREREADYSTATE       };
STATE ReadyTestSt  = {ReadyTest,  &TimeOff,   TestReadyTest,EnterTestReady,ExitReadyTest,AlStopSonics, READYSTATE         };
STATE TestST       = {TestMode,   &TimeOff,   TestTest,     EnterTest,    ExitTest,     AlStopTest, TESTMODESTATE       };


/*                    Substate    Timeout     Pass Code     Entry Code    JUMP Code     ALJUMP Code   State               */
/*                    Name        pointer                                                                                 */
/*                    ----------  -------     ----------    ----------    -----------   ----------    ------------        */

STATE CalTopOfList = {Initial,    &TimeOff,   Nothing,      Nothing,      Restart,      Restart,      PREREADYSTATE       };

STATE CalReadySt   = {Ready,      &TimeOff,   Nothing,      Nothing,      Nothing,      Nothing,      CALREADYSTATE       };
STATE CalPBState2  = {CalbPBs,    &Stagger,   TestCalPB,    StartCalPB,   CalExitPB,    AlarmExitPB,  NOP         };
STATE CalWaitUls   = {CalWaitUls1,&UlsTime,   UpdateDownSpeed, Nothing,   ExitULS,      AlarmUls,     WAITFORULSCLEARSTATE};
STATE CalTriggerST = {CalTrigger, &TimeOff,   Nothing,      Nothing,      TriggerBeep,  Nothing,      TRIGGEREDSTATE      };
STATE CalWaitTrsST = {WaitTrs4,   &MaxWTime,  TestTimer,    Nothing,      Nothing,      Nothing,      WAITFORTRSSTATE2    };
STATE CalWaitTime1 = {WaitTime,   &CalTimer,  ReadLoadCell, InitForce2,   ExitCalWait,  Restart,      CALTIMERSTATE1      };
STATE CalWaitTime2 = {WaitTime,   &CalTimer,  CollectForceData,InitForce3,ExitCalWait,  Restart,      CALTIMERSTATE2      };
STATE CalEndOfList = {Nop,        &TimeOff,   Nothing,      Restart,      Restart,      Nothing,      PREREADYSTATE       };
                                                                                                                                                      

/*                      Substate    Timeout    Pass Code      Entry Code       JUMP Code     ALJUMP      State       */
/*                      Name        pointer                                                                          */
/*                      ----------  -------    ----------     ----------       ----------    --------    ------------        */
STATE SCPBState       = {PalmButtons,&Stagger, Nothing,       StartCalPB,      ExitPB,       AlarmExitPB,NOP         };
STATE SCWaitUls       = {CalWaitUls1,&UlsTime, UpdateDownSpeed, Nothing,       ExitULS,      AlarmUls,   WAITFORULSCLEARSTATE};
STATE SCWaitTrsST     = {WaitTrs4,   &TimeOff, WaitForSpringRate,Nothing,      InitCalTimer, Nothing,    WAITFORTRSSTATE2    };
                                                                                                                                             
STATE SCDone          = {SCComp,     &TimeOff, UpdateMessage, Nothing,         SCFinalCleanup,  Nothing,    NOP         };
STATE SCEndOfList     = {Nop,        &TimeOff, Nothing,       Restart,         Restart,      Restart,    NOP         };


void  CheckPD(void)
{
   PowerDownAborted = FALSE;
}


void  PowerOff(void)
{
   PowerDownSystem();
}



void PowerOffLock(void)
/****************************************************************************/
/*                                                                          */
/* This function will NEVER RETURN, used for power down only.               */
/*                                                                          */
/****************************************************************************/
{
   while(TRUE);
}



void EnterPDown(void)
{
   PDownDelay = FALSE;                 /* Write to BBR will set to TRUE    */
   PrePowerDown();
}


void  PowerUp(void)
{
   ActDone = FALSE;
   PSDone = FALSE;
   ControlsDone = FALSE;
   StackDone = FALSE;
   PowerUpTimer = 0;
   PowerUpSeekTimer = 0;
   PowerUpOL = FALSE;
   SystemOK = FALSE;       /* TestPO1 will set this to TRUE after 1 second */
   SetCurrentFreqOffset(0);
   FreqControlInternal.bool = TRUE;  /* set to internal frequency */
   FreqControlExternal = FALSE;
   WeldingResults.PSActControlFlags = BIT0;   /* set to internal amplitude */
   WeldingResults.PSActControlFlags |= BIT2;   /* set to internal frequency */
   DUPSOkFlag = FALSE;
   DUPS_MsgBuf.mt = DUPS_MSGINITINTERFACE;
   q_send( DupsQid, &DUPS_MsgBuf);   /* Initialize DUPS interface */
   PSReset();
}

/****************************************************************************/
/*  It must get the current preset and decide what actuator is correct and  */
/*  then see if that actuator is the one actually connected to this power   */
/*  supply.                                                                 */
/****************************************************************************/


void TestPO1(void)
/*-----   Initial conditions for power up    -----*/
{
   if ((PowerUpTimer++ >= 1500) && (DUPSOkFlag == TRUE)){
      PowerUpTimer = 500;
      if((CurrentSetup.DigPotFlag & BIT0) == TRUE)
      {
         SetDigPot();
      }
      else{
         CenterDigPot();
      }
      SystemOK = TRUE;
   }
}

void DispCtrl(void)
{
   PowerUpTimer = 0;
}   

void TestPO2(void)
/*-----   Check controls here   -----*/
{
   if (PowerUpTimer++ >= 1800) {
      if(!CurrentSetup.VGAHWPresent)
         UpdateBarGraph(0);
      UpdateLED(UPLED, OFF);
      UpdateLED(RIGHTLED, OFF);
      UpdateLED(DOWNLED, OFF);
      UpdateLED(LEFTLED, OFF);
      UpdateLED(OFFLED, OFF);
      if(AlarmCounter == 0) 
         UpdateLED(RESETLED, OFF);
      NumberOfBeeps = 0;
      TurnOffBeeper();

/* Before we leave, set up all user definable outputs to correct state */
  
      UpdateAllUserOutputs();
      
      ControlsDone = TRUE;
   }
   else {
      UpdateBarGraph(PowerUpTimer / 17);
      if (PowerUpTimer > 1500) {
         UpdateLED(UPLED, ON);
      }
      else if (PowerUpTimer > 1250) {
         UpdateLED(RIGHTLED, ON);
      }
      else if (PowerUpTimer > 1000) {
         UpdateLED(DOWNLED, ON);
      }
      else if (PowerUpTimer > 751) {
         UpdateLED(LEFTLED, ON);
      }
      else if (PowerUpTimer > 750) {
         Beep(PSOSBEEP);
      }
      else if (PowerUpTimer > 500) {
         UpdateLED(OFFLED, ON);
      }
      else if (PowerUpTimer > 250) {
         UpdateLED(RESETLED, ON);
      }
   }
}


void DispAct(void)
{
   PowerUpTimer = 0;
}   

void TestPO3(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check the actuator. The upper limit switch, carriage */
/*  door.                                                                   */
/*  Note: For now the SV safety circuits will not be tested.                */
/*                                                                          */
/****************************************************************************/
{
   if ( PowerUpTimer++ <= ACTUATOR_TIME) {
      if ((CurrentSetup.Actuator == AEF) && (CurrentSetup.ControlLevel >= LEVEL_f)) {
         if ( PressureTimer++ >= 200 ) {
            PressureTimer = 0;            
            if (CheckPressure( &PressureFlag, HomePressure ) == TRUE) {
               PressureCounter++;
            }
            else {     
               PressureCounter = 0;
            }
         }  
      }      
   }
   if ( PowerUpTimer > ACTUATOR_TIME){
      if ((CurrentSetup.Actuator == AEF) && (CurrentSetup.ControlLevel >= LEVEL_f)) {
         if ( PressureCounter >= 3 ){
            if(CurrentPreset.SetPressure != PressureFlag)  /* Pressure has changed */
            {
               CurrentPreset.SetPressure = PressureFlag;
               CurrentPreset.PresetUpdateComplete = FALSE;    /* force asterisk */
               PresetNeedsToBeUpdated = TRUE;                 /* need to verify the preset */
               CurrentPreset.Verified = FALSE;
            }
            UpdatePressureOffset();
         }
         else { 
            RecordAlarm(EQ25);
         }   
         if ( CurrentPreset.SetPressure == TRUE ){
            SystemPres60PSI = FALSE;
            SystemPres80PSI = TRUE;
         }
         else {
            SystemPres60PSI = TRUE;
            SystemPres80PSI = FALSE;   
         }
      SetMaxMinValues();
      }
/*-----   Start by looking at various signals   -----*/
      
      if (Inp.uls == FALSE) {
         RecordAlarm(EQ2);
         ActClrOff();         /* Not at home, so can't say for sure if actuator */
      }                       /* is clear or not.                               */
      else {
         ActClrOn();          /* We're home so actuator is clear                */
      }   
      if (Inp.DoorOpen == TRUE)
         RecordAlarm(EQ4);
      if (CurrentSetup.Actuator == AE) {
         if (Inp.Trigger == TRUE)
            RecordAlarm(EQ4);
      }
      else
         CheckForHornChange(); /* Is the horn weight different from last power up */
      if (Inp.OnePB == TRUE) {
         RecordAlarm(EQ17);
      }
      ActDone = TRUE;
   }
}

void DispPS(void)
{
   PowerSupplyOk = TRUE;                    /* Assume P/S will be okay      */
   PowerUpFreq = CurrentFreqIn;             /* Read frequency at rest       */
   if (Inp.DoorOpen == FALSE){
      PSSeek();                             /* Start a seek                 */
      SetCurrentAmp(5);                     /* Limit to 5% amplitude        */
   }
   ActualSeekTime = 0;
   ActualPeakPower = 0;
   PowerUpTimer = 0;
   PowerUpSeekTimer = 0;
}   



void TestPO4(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check the power supply at power up.  It will do the  */
/*  following checks:                                                       */
/*                                                                          */
/*     - Do a seek & check for run signal back from power supply            */
/*     - While seeking check for seek signal back from power supply         */
/*     - Look for +10V reference signal from power supply                   */
/*     - This entire function will be skipped if E-stop is activated        */
/*                                                                          */
/*  The variable PSFailCode (available as entry 13 in debug quick list)     */
/*  will contain bits set to '1' to indicate the reason for failure.        */
/*       BIT0 - Seek signal did not respond from power supply module        */
/*       BIT1 - Run signal did not respond from power supply module         */
/*       BIT3 - +10Vreference was below roughly 9.0 volts                   */
/*       BIT4 - E-stop was active at power up.  Not a failure, but does     */
/*              indicate that the power up test was not run.                */
/*                                                                          */
/****************************************************************************/
{

   static BOOLEAN OverloadHistoryFlag = FALSE;
   
   if (Inp.Estop == FALSE) {
      if (PowerUpTimer++ >= ONE_SECOND) {
         if (TenVoltRef >= 900) PSFailCode &= ~BIT2;
         if (PSFailCode != 0) PowerSupplyOk = FALSE;
         if (PowerSupplyOk == FALSE)
            RecordAlarm(EQ15);
         PSIdle();                                /* Stop sonics               */
         PSDone = TRUE;                           /* Advance state machine     */
      }
      else {

/*-- For the 1st 1000ms restart the seek every 50 ms (20ms on / 30ms off) --*/
  
         if (PowerUpTimer <= SEEK_TIME) {
            PowerUpSeekTimer++;
            if (OverloadHistoryFlag == FALSE) {
               ActualSeekTime++;  
               if (Inp.OL == TRUE) OverloadHistoryFlag = TRUE;
            }
            if (PowerUpSeekTimer <= SEEK_ON_TIME) {
               PSSeek();                            /* Seek on   */
               if (Inp.PSSeek == TRUE) PSFailCode &= ~BIT0; 
            }
            else {
               PSIdle();                            /* Seek off  */
               if (PowerUpSeekTimer >= SEEK_RETRIGGER_TIME) {
                  PowerUpSeekTimer = 0;
               }
            }
         }
         else {
            PSSeek();                            /* Make sure 0% Led stays on  */
         }

         if (Inp.PSRun == TRUE) PSFailCode &= ~BIT1; 
      }
      if (CurrentPowerIn > ActualPeakPower) /* update needed for alarm additional information */
          ActualPeakPower = CurrentPowerIn;
      FreqChg = CurrentFreqIn - PowerUpFreq;
   }

/*---   Here's what we do if they powered up with E-stop active   ---*/

   else {
      PSDone = TRUE;             /* Make sure the state machine can advance */
      PowerSupplyOk = TRUE;      /* Now we lie about our results on the P/S */
      PSFailCode = BIT3;
   }
   if (Inp.OL == TRUE)
      PowerUpOL = TRUE;
}



void DispStack(void)
{
   PowerUpTimer = 0;
}   



void TestPO5(void)
/****************************************************************************/
/*                                                                          */
/*  This function will check the stack.                                     */
/*                                                                          */
/****************************************************************************/
{
   QsmMap->TxdData[7] = 0xd000; /* replace ch7 with Ext Freq was 10vref */
   if (PowerUpTimer++ >= ONE_SECOND ){
// do not detect stack missing 
      StackDone = TRUE;
   }
   if(Inp.OL == TRUE)
      PowerUpOL = TRUE;
}



void PowerOnOK(void)
{
   LockPowerOn();
   JustPoweredUpFlag = TRUE;
   JustPoweredUpTimer = 0;
   PoweredUp = FALSE;
   if (PowerUpOL == TRUE)
   {
      RecordAlarm(OL3);
      PSReset();                 /* Attempt to reset power up seek overload */
   }   

/* Do stuff here that has to happen only at power on */

   if ( (BUCMenuRAM.VelocityReporting == TRUE) ||
        (CurrentSetup.Actuator == AED) ||
        (CurrentSetup.Actuator == MICRO) )
      UpdateSWConfiguration(VEL, TRUE);         /* Set velocity reporting on  */                                             
   else
      UpdateSWConfiguration(VEL, FALSE);        /* Set velocity reporting off */

//   if (BUCMenuRAM.MicroHomeForce == FALSE)      /* Set up Micro home leaving force */
      MicroHomeForce = LEAVINGHOMEFORCEMICROLO;  
//   else                
//      MicroHomeForce = LEAVINGHOMEFORCEMICROHI;   
   
}


void NewState(void)
{
   ResetStateMachine();
   SelectWeldSequence();
   if (!CurrentSetup.VGAHWPresent) 
      StartStateMachine();
   else {  /* Convert the VFD Busy Input to and output */
      asm(" move.w #$03,$ffff80");
      asm(" move.w #$40aa,$fffe18");
   }
}



void NeverStart(void)
{
   Restart();
}


void Copyright(void)
/****************************************************************************/
/*                                                                          */
/* This function will be called after the copyright notice has been shown   */
/* for the proper amount of time.                                           */
/*                                                                          */
/****************************************************************************/
{
   PowerUpTimer = 0;
}


void CheckMenuSync(void)
/****************************************************************************/
/*                                                                          */
/*   This function will wait for a new menu to be displayed.  While waiting */
/*   some tests will be run.                                                */
/*                                                                          */
/****************************************************************************/
{
   if ((GetCurrentSequenceType() == SC) ||
        (GetCurrentSequenceType() == CALIBRATION)){
      ReadLoadCell();     /* Read loadcell until user types in value */
      WaitForMenu();
   }
}








