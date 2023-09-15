/* $Header:   D:/databases/VMdb/2000Series/App/PRESET.C_V   1.204   04 Sep 2014 10:08:44   hasanchez  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                           */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Preset                                                      */
/*                                                                          */
/* Filename:    Preset.c                                                    */
/*                                                                          */
/* Function Name: Save/Recall Presets                                       */
/*                                                                          */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date        Author       Description                         */
/*  =========  =========   ===========  ===========                         */
/*     0       08-02-96    PhilJ        Original write of code              */
/*     1.00    09-04-96    PhilJ        Set PresetUpdateComplete Flag after */
/*                                      a Write Preset                      */
/*     2.00    10-02-96    Lam          send message directly over to for read*/
/*                                      nvm                                 */
/*     3.00    10-04-96    Lam          replaced q_send                     */
/*     3.10    12-16-96    PhilJ        Added Update PresetUpdateComplete   */
/*                                      in Preset0                          */
/*     4.00    01-28-97    Lam          deleted initpreset,made queues glob.*/
/*     4.10    12-16-96    PhilJ        Qsend in ReadPreset now calls       */
/*                                      Sysmangr instead of Nvmanger        */
/*     1.61    07-07-97    BEKymer      Moved SetMaxMinValues, DoColdStart, */
/*                                      SetMaxMinValues, & MaxDefaultForce  */
/*                                      from now defunct module Weld_obj.c  */
/*     1.8     07-11-97    PhilJ        Added SetRemote to ColdStart. Added */
/*                                      to default ScrubTimeFlag, HmenuIndex*/
/*                                      and CurrentSetup.Remote             */
/*     1.9     07-11-97    PhilJ        Deleted PageSize default            */
/*     1.10    07-15-97    PhilJ        Deleted all Printer & Serial Port   */
/*     1.11    07-16-97    PaulG        Added ClearHistoryInBbram() func.   */
/*     1.12    07-18-97    PhilJ        Added new SW vers: str in ColdStart */
/*     1.13    07-21-97    PaulG        Removed ClearHistoryInBbram() func. */
/*     1.14    07-28-97    PhilJ        ColdStart clears FinalResults and   */
/*                                      WeldData.                           */
/*     2.1.15  07-28-97    LAM          deleted currentsetup.swversion added*/
/*                                      powerdefault table                  */
/*     2.1.16  07-31-97    PhilJ        Added Serial Init to ColdStart      */
/*     2.1.17  08-01-97    PhilJ        After ColdStart go to WeldSetup menu*/
/*     2.1.18  08.15.97    JBerman      Adding BootSf()                     */
//     2.1.19  08.15.97    JBerman      Added #include "features.h"
//     2.1.20  09.09.97    JBerman      Added default into case statements
//     2.1.21  09-15-97    PaulG        Changed default value from 999 to 99999
//     1.22    09-19-97    LAM          deleted update preset                  
/*     1.23    09-23-97    BEKymer      In DoColdStart() only clear alarms  */
/*                                      if ClearAlarm() says it's ok        */
/*                                      Clear setup alarms in DoColdStart() */
/*     1.24    10-03-97    BEKymer      In DoColdStart call CheckBattramD...*/
/*                                      In ReadPreset call CheckBattramD... */
/*                                      Update PwrOutTable with LAM's #'s   */
/*     1.25    10-16-97    BEKymer      Create ColdStartInProcess flag, turn*/
/*                                      off Reset led in cold start         */
/*     1.26    10-29-97    PaulG        Changed GlobalPrinting to TRUE also */
/*                                      also add WeldCounter                */
/*     1.27    11-94-97    BJB          DoColdStart() uses SetupKey, not    */
/*                                       MENUINDEX0 + Sel2, to get to Setup */
/*                                       screen.                            */
/*     1.28    11-05-97    PaulG        Added WeldCounter and added ClearHistoryInBram().*/
/*     1.29    11-14-97    BEKymer      More cleanup in DoColdStart()       */
/*     1.30    11-18-97    LAM          replaced finalresults with weldingresults*/
/*     1.31    12-10-97    PaulG        Reset TotalPts when a colstart is done */
/*     1.32    12-11-97    BEKymer      Fix double equal in DoColdStart     */
/*     1.33    12-31-97    BJB          Rearranged serial port code in      */
/*                                       DoColdStart().                     */
/*                                      Added comment terminators to satisfy*/
/*                                       compiler.                          */
/*     1.34    01-13-98    PaulG        Added default value for WeldPerPage */
/*     1.35    01-19-98    BJB          Doesn't initialize MaxTimeoutFlag,  */
/*                                       this flag no longer exists.        */
/*                                      Default value of EnergyPL is set    */
/*                                       based on PSWatt, not always set 10.*/
/*     1.36    01-27-98    PaulG        Added PrinterBufferReadyFlag        */
/*     1.37    01-28-98    BJB          Saves CurrentPreset before cold strt*/
/*     1.38    02-02-98    BEKymer      In DoColdStart, clear AlarmDetected */
/*                                      Flag if no failure of: alarms.      */
/*     1.39    02.04.98    JBerman      Deafault 9600 bdr on ColdStart      */
/*     1.40    02.04.98    BJB          Inits CurrentSetup.RemoteData to    */
/*                                       FALSE on cold start.               */
/*     1.41    02.19.97    JBerman      CurrentSetup.Features->CurrentPreset.Features*/
/*     1.42    03.09.98    BJB          Doesn't turn off remote term at cold*/
/*                                       start.                             */
/*                                      No serial port config changes on    */
/*                                       cold start anymore.                */
/*                                      Prevents unnecessary Main Menu      */
/*                                       display before Weld Setup on cold  */
/*                                       start.                             */
/*                                      Sets FreqOffset min/max based on    */
/*                                       CurrentSetup.PSFreq.               */
/*     1.43    03.24.98    LAM          fixed setminmax force values        */
/*     1.44    03.24.98    PaulG        Removed TotalPts from  file         */    
/*     1.45    03.28.98    LAM          removed clearing of weld&final results*/    
/*                                      during cold start                   */
/*     1.46    04-24-98    BEKymer      Add call to GetStrokeLength to set  */
/*                                      up max stroke length                */
/*                                      Remove DefaultMaxForce (req, LAM)   */
/*     1.47    04-30-98    BEKymer      After loading a preset create W8    */
/*                                      alarm if AEF/AED and MODEL4+.       */
/*     1.48    05.05.98    LAM          removed unused abscoldist           */    
/*     1.49    05.14.98    LAM          added partcontact variables to coldstart */    
/*     1.50    05.18.98    PaulG        Added AbsDistanceSFlag and AbsDistanceAFlag*/
/*     1.51    05.21.98    BJB          Converted default FORCE settings to */
/*                                       tenths of pounds.                  */
/*                                                                          */
/*     1.52    05-22-98    BEKymer      Changed default values for min col. */
/*                                      Changed default for ActClrDis to .1"*/
/*     1.53    05-26-98    BJB          Change MinLimit.FreqOffset to 0, it */
/*                                       will now represent min abs. value. */
/*     1.54    05-28-98    BEKymer      Change custom stroke length to 99999*/
/*     1.55    06-18-98    BJB          Center digital pot as part of cold  */
/*                                       start.                             */
/*     1.56    06-19-98    BJB          Redraws terminal data after cold    */
/*                                       start.                             */
/*     1.57    06-25-98    BJB          Doesn't set CurrentSetup.User, no   */
/*                                      longer exists.                      */
/*     1.58    06-29-98    PaulG        Reset last saved preset  Date to    */
/*                                      the current preset date.            */
/*     1.59    06-29-98    BJB          Changed min value for collapse dist */
/*                                      from .0005 to .0004, in 8 places.  */
/*     1.60    06-30-98    BJB          Cold start turns control limits off */
/*     1.61    07-02-98    PaulG        When a cold start is done reset date to current time */
/*     1.62    07-15-98    BEKymer      Move max stroke length case into    */
/*                                      util as GetMaxStrokelength()        */
/*                                      Clear AlarmsReset flag in cold start*/
/*     1.63    07.21.98    LAM          made partcontact default = off      */    
/*     1.64    07.30.98    LAM          use sumofforce for nomovement       */    
/*     1.65    07-30-98    BEKymer      Only set AlarmsReset if there are   */
/*                                      no more alarms remaining after a    */
/*                                      cold start.                         */
/*     1.66    07-30-98    BJB          Clears EquipmentFailureAlarm on     */
/*                                      cold start if ClearAlarm() returns  */
/*                                      TRUE, this makes sure alarms like   */
/*                                      "Actuator Type" get cleared.        */
/*     1.67    07-30-98    BJB          Added def for FinalResults.         */
/*     1.68    07-31-98    BJB          Includes kpresmsg.h, getmsg.h       */
/*     1.69    08-03-98    BEKymer      Change power max to 1000 (100.0)    */
/*                                      and power min to 10 (1.0)           */
/*                                      Change power defaults to 100 (10.0%)*/
/*                                      Eliminate as many numbers as        */
/*                                      possible and replace with defines.  */
/*     1.70    08-14-98    BEKymer      In DoColdStart swap CountAlarms()   */
/*                                      and ClearSetupAlarms().  There was  */
/*                                      no point in checking TotalAlarmCount*/
/*                                      because ClearSetupAlarms() set it   */
/*                                      to 0!                               */
/*     1.71    08-24-98    LAM          rescaled power to 1% accuracy       */
/*     1.72    08-24-98    LAM          rescaled power to 0.1% accuracy     */
/*     1.73    08-25-98    PaulG        Added new limit values to XScaleTime*/
/*     1.74    08-31-98    BEKymer      Set PeakPwrCutoff to POWER_MIN in   */
/*                                      SetDefaultValues().                 */
/*     1.75    09-03-98    BJB          Calls new AlarmOff() function to    */
/*                                      turn off reset LED.                 */
/*     1.76    09-29-98    BEKymer      In DoColdStart() no longer call     */
/*                                      ClearAlarm(), just clear ALL alarms */
/*     1.77    11-09-98    BEKymer      Update all frequency values to      */
/*                                      handle 15Khz and 30khz supplies.    */
/*     1.78    11-19-98    BJB          Updates max force settings only if  */
/*                                       AED or AEF actuator (won't set 0   */
/*                                       if AE).                            */
/*     1.79    03-17-99    LAM          fixed hold force max                */
/*     1.80    05-11-99    LAM          added ramps                         */
/*     1.81    05-12-99    JZ           added Min & Max Limit for SetRTComp */
/*                                      WeldFR, StepFR, HoldFR              */
/*     1.82    05-21-99    JZ           Changed limits 1000 to 1250 and ABS_MIN */
/*                                      DownSpeed                           */
/*     1.83    05-26-99    JZ           modified the MaxForce               */
/*     1.84    05-28-99    JZ           removed AEF in DoColdStart          */
/*     1.85    06-01-99    JZ           changed CurrentPreset.WeldForce=200 */
/*     1.86    06-16-99    JZ           change BIT2 to RATE_NORMAL          */
/*     1.86.1.1 07-14-99   JZ           added ScrubTimeFlag                 */
/*     1.88    08-11-99    JZ           chngd DownSpdStart to 20            */
/*     1.89    08-16-99    JZ           chgnd Force2Flag to fffa            */
/*     1.90    08-23-99    JZ           added part contact                  */
/*     1.91    08-26-99    JZ           set min trigger cold start to BUC selection*/
/*     1.92    08-26-99    JZ           chngd FORCE_MIN TO CurrentPreset.MinTrigForce*/
/*     1.93    09-03-99    JZ           removed MinTrigForce min and max limits */
/*                                      changed MinTrigForce to be in CurrentSetup */
/*                                      and added 10 (1lbs) to it           */
/*     1.94    10-01-99    JZ           cleaned ReadPreset()                */
/*     1.95    10-04-99    JZ           removed proto for MaxDefaultForce() */
/*     1.96    10-25-99    JZ           made FIVE_LBS define for MinTriggerForce */     
/*                                      removed GetDateAndTime()            */
/*     1.97    11-04-99    JZ           removed RTInitVel                   */
/*     1.98    12-16-99    LAM          removed unused error handling code  */
/*     1.98.6.1 02-07-00   JZ           removed DVS assignment              */
/*     1.98.6.1 02-23-00   OFI          deleted #include "features.h";
                                        removed CurrentPreset.Features = TRUE
                                        deleted call to BootSF();           */
/*     1.99      04-06-00  JZ           merged Lang to trunk                */
/*     1.100     05-12-00  JLH          Changed DoColdStart so alarms are not */
/*                                       cleared for Wrong Actuator failure.  */
/*     1.101     05-15-00  JLH          Corrected DoColdStart to retain     */
/*                                       Wrong Actuator failure and beep and*/
/*                                       blink alarm LED after cold start.  */ 
/*     1.102     05-26-00   SCM      Checked in for testing by Laura, John. */                                                                         
/*     1.103     06-01-00  JLH       Zeroed print on sample rotation counters */
/*                                    in SetDefaultValues function.           */ 
/*     1.104     06-14-00  JLH       Form feed during cold start if not at top of page. */
/*     1.105     06-21-00  DJL       Made a few global name changes from DigitalFilter to DigitalFilterFlag*/
/*     1.105    06-21-00   DJL       Made a global name change from GeneralAlarmL to GeneralAlarmLFlag */
/*     1.105     06-21-00  DJL       Made global name changes from GlobalPrinting to GlobalPrintingFlag*/
/*     1.105     06-26-00  DJL       Made global name changes from Preset.MaxForce to Preset.WeldForce 
                                    from RejResetRequired to RejResetRequiredFlag  &  SeekFun to SeekFunFlag
                                    changed AmpTrigDistValue to AmpTrigColValue*?
/*    1.105      06-29-00 DJL       changed MODEL to LEVEL                      */  
/*    1.105      06-30-00 DJL       created functions: SaveCompressedPreset and RecallCompressedPreset*/
/*    1.106      07-06-00 BEKymer   created functions: Convert600to800 and Convert702to800.       */
/*    1.107      07-12-00 BEKymer   Fixed bugs in Compression routines
/*    1.108      07-13-00 BEKymer   Call CompressedPreset() in SetDefaultValues()  */
/*                                   instead of BattramAccess()                    */
/*                                  Save and then restore CurrentPreset in         */
/*                                   SetMaxMinValues()                             */
/*                                  Added SetPressure to compressed preset         */
/*    1.109      07-14-00 BEKymer   Added SEEKFUNFLAG to compressed preset         */
/*                                  Added ABSGRAPHSFLAG to compressed preset       */
/*                                  Removed Amp2Flag & Force2Flag from bit save    */
/*                                  Added TimingOnTrg                              */
/*                                  Added SuspectLimits, RejectLimits to comp.     */
/*    1.110      07-14-00 BEKymer   Fix bug in SHIFT2_PEAKPWRCUTOFFFLAG functions  */
/*    1.111      07-14-00 BEKymer   Added TestAmp to Compress/Decompress functions */
/*                                  Added SusResetRequired                         */
/*                                  Fixed bug in peak power cutoff flag            */
/*    1.112      07-21-00 BEKymer   Fixed logic when dealing with CompressPreset-> */
/*                                   Verified.                                     */
/*    1.113      08-01-00 BEKymer   Clear ErrorCodeFlag in ReadPreset()            */
/*    1.114      08-02-00 JLH       Modified DoColdStart to clear ready after wrong*/
/*                                   actuator alarm is repeated.                   */
/*    1.115      08-02-00 JLH       Retyped 1.114 comment -- it would not compile. */
/*    1.116      08-04-00 JLH       Updated Convert600to800 and Convert702to800 functions. */
/*    1.117      08-09-00 JLH       Added include digout.h for its ClearReady prototype.   */
/*    1.118      08-11-00 JLH       Fixed DoColdStart so equipment failure alarms survive the cold start. */
/*    1.119      08-11-00 RBH       Added DUPS Parameter Set to DoColdStart */
/*    1.120      08-11-00 RBH       Corrected DUPS_Wait4CurrPS reference */
/*    1.121      08-16-00 JLH       Deleted code to test for invalid preset from RecallCompressedPreset,
                                     moved it to VerifyPreset. */ 
/*    1.122      08-18-00 SRP       DUps Download and Upload shifted after checking Digpotkey in coldstart.
/*    1.123      08-18-00 LAM       Set trigger force to 10lbs on cold start(Issue 3276).
/*    1.124      08-18-00 SRP       DUPS_Info.WeldStatusFlag = TRUE in cold start flag.
/*    1.125      08-22-00 JLH       Commented out Verified logic.  Associated invalid preset detection will be deferred
                                     to Ver9. */
/*    1.126      08-23-00 BEKymer   Included string.h for memcpy prototype         */
/*                                  Call MoveToCurrentPreset instead of memcpy in  */
/*                                   convert routines                              */
/*    1.127      08-25-00 BEKymer   Initialize CurrentPreset.DUPSPreset in cldstrt */
/*    1.128      08-26-00 JLH       Commented out software version check in RecallCompressedPreset.  It caused */
/*                                   Invalid Preset error code 7 with change in software version number.       */
/*    1.129      08-28-00 BEKymer   Set Weld & Hold Force to 15 lbs in coldstart   */
/*                                  Initialize CurrentSetup.WeldStatusFlag in      */
/*                                   SetDefaultValues                              */
/*    1.130      09/01/00  SRP      Seek time and seek flag value hard coded after cold start */
/*    1.131      09/06/00  LAM      external amp control hard coded after cold start */
/*                                  Issue #3559                             */
/*    1.132      09/12/00  SCM      Force DUPS parameter Memory = On in WeldSetup menu after a coldstart */
/*    1.133      10/04/00  AT       Changed DUPS_DownloadCurrPS to DUPS_QueuedDownloadPS */
/*    1.134      10/16/00  AT       line 1133 - force weld ramp time to 80 at cold start (#3622) */
/*    1.135      10-18-00  BEKymer  Modified SaveCompressedPreset to accept */
/*                                   2nd arg, the address of which structure*/
/*                                   to save (Current, Min, Max, etc) to    */
/*                                   fix issue # 3387                       */
/*    1.136      11/16/00  AT       DoColdStart - set Mem store and Seek flags in SWDipSetting */
/*    1.137      11-17-00  BEKymer  Use temp variables when adding bits in  */
/*                                   SaveCompressedPreset to reduce the     */
/*                                   risk of losing data if reentrency      */
/*                                   occurs at power down.  Issue # 3678.   */
/*    1.138      11/17/00  AT       DoColdStart - clear seek flag only once */
/*    1.139      01-26-01  BEKymer  Remove Convert 6.00 to 8.00 and Convert */
/*                                   7.02 to 8.00 functions                 */
/*    1.141      04-30-03  BEKymer  Move 1.140 to tip for 8.10 build        */
/*    1.138.1.0.1.1  06/30/03  bwadia   Added Cold Start Complete message for   */
/*                                      QVGA display in 'DoColdStart()'         */
/*    1.142      07-25-03  LAM        merged 8.10 with TS01                 */
/*    1.143      10-23-03  JOY      Added extra sleep in DoColdStart().     */
/*    1.144      10-30-03  JOY      Above DoColdStart() Delay is limited to QVGA*/
/*    1.145      11-02-03  JOY      fixed force stepping ext in docoldstart*/
/*    1.146      12-04-03  BEKymer  Merged 1.145 & 1.141.1.1 to create      */
/*                                   1.146 for Ver9.00b build               */
/*    1.147       12-09-03  BEKymer  Added missing external and loop counter */
/*    1.148      01-19-04  VSharma  PresetID, WriteIn1, WriteIn2 ended with */
/*                                  NULL char in RecallCompressedPreset()   */
/*    1.149      02-02-04  VSharma  Added default values for CurrentPreset.HwCnfg
                                    & CurrentPreset.Verified flag.          */
/*    1.150      02-12-04  BEKymer  Add RecallColdStartPreset() call in     */
/*                                   DoColdStart()                          */
/*    1.151      02-20-04  VSharma  Added default values for UserIO & Custom*/
/*                                   menu variables.                        */
/*    1.152      03-09-04  VSharma  Changed naming Convention for UserI/O   */
/*                                   menu variables.                        */
/*    1.153      03-12-04  VSharma  Added default values for J3_32Ptr,J3_33Ptr,*/
/*                                   J3_19Ptr,J3_17Ptr,J3_31Ptr & J3_2Ptr.  */
/*    1.154      04-23-04  VSharma  Changed default value of J3_22 to ExtBeeper */
/*    1.155      05-03-04  VSharma  Modified J3_2In to J3_1In.              */
/*    1.155.1.0  06-10-04  BEKymer  Added default for Welder Address        */
/*    1.156      06-04-04  VSharma  Added default values for CurrentSetup   */
/*                                   SampleValue & AlarmFlag for each graph.*/
/*                                  Removed ClearWeldHistory code from ColdStart. */
/*    1.157      06-22-04  JOY      Corrected header of DoColdStart() &     */
/*                                  CreateColdStart().                      */
/*                                  Removed initialization of CurrentSetup.ExtPresetWeldCount*/
/*                                  from SetDefaultValues()                 */
/*                                  CurrentPreset.ExtTrgDelay, CurrentPreset.EnergyBraking*/
/*                                  Initialized to 0 in SetDefaultValues(). */
/*    1.158      06-24-04  BEKymer  Merged 1.155.1.0 & 1.157 to create      */
/*                                   1.158 for Ver9.00l                     */
/*    1.158.1.0  06-29-04  JOY      Initialized Write In Fields in SetDefaultValues().*/
/*    1.159      06-29-04  BEKymer  Breakout default sections of code into  */
/*                                   functions so they can be called from   */
/*                                   elsewhere.                             */
/*    1.160      07-08-04  BEKymer  Start/stop state machine in DoColdStart */
/*    1.161      07-08-04  JOY      Active preset set to 0 in DoColdStart   */
/*    1.162      07-27-04  JOY      Added Min/Max Limit for FREQ60KHZ       */
/*    1.163      08-02-04  BEKymer  Default user outputs to disabled        */
/*    1.164      08-03-04  JOY      Touch screen display removed from CreateColdStart() */
/*    1.165      08-18-04  JOY      Added default value to CurrentSetup.SVDelay */
/*    1.166      08-25-04  JOY      Initialized Ext. Start delay in SetUserIOFactoryDefault() */
/*    1.167      08-27-04  BEKymer  Add min/max values for energy braking   */
/*    1.168      09-07-04  BEKymer  Add EBTime to Save & Recall Compressed  */
/*                                   Preset                                 */
/*    1.169      09-10-04  BEKymer  Change the way the COLD START preset is */
/*                                   saved in CreateColdStart().            */
/*    1.170      10-04-04  BEKymer  In function SetUserIOToFactoryDefault() */
/*                                   call RefreshoutputStatus() so outputs  */
/*                                   are set to 24 volts when disabled by   */
/*                                   defaulting to factory setting          */
/*    1.171      10-04-04  BEKymer  Call UserCfgOutputOn instead for above  */
/*                                   fix.                                   */
/*    1.172      07-25-05  Bwadia   QVGA code clean up                      */
/*    1.173      08-23-05  Aare     Pretrigger delay - works with save/recall preset */
/*    1.174      09-10-05  Aare     Save SBL information in compressed presets. */
/*    1.175      09-12-05  Aare     Reworked the backwards polarity of flags for pretrigger. */
/*    1.176      10-11-05  Bwadia   USB default parameters set              */
/*    1.177      10-24-05  Bwadia   PMC related parameters save and recall  */
/*                                  added. Also Added default values        */ 
/*                                  AfterBurst Delay min time changed to 50 ms*/
/*    1.178      11-22-05  Bwadia   Pretrigger delay, PMC and SBL related   */
/*                                  changes and initialization */
/*    1.179      12-07-05  Bwadia   Cold start value for energy braking time*/
/*                                  changed to .020s. Modified for tracker  */
/*                                  issue 4019                              */
/*    1.180      12-20-05  Bwadia   Sequence printing related changes and initialization */
/*                                  Modified for Tracker issue 3976         */
/*    1.181      01-03-06  Bwadia   InitSBL called from SetDefaultValues()  */
/*                                  Modified for tracker 3980               */
/*    1.182      01-06-06  LAM      Merged BBRaun Special                   */
/*    1.183      01-20-06  Bwadia   Global printing flags when cold start   */
/*                                  on VGA systems not changed. Modified for*/
/*                                  tracker issue 4055                      */
/*    1.184      02-08-06  Bwadia   Default Global USB flag set to False    */
/*    1.185      02-22-06  Bwadia   Memory reset flag initialized when      */
/*                                  creating cold start preset. Modified for*/
/*                                  tracker issue 4077                      */
/*   1.186       03-07-06  LAM      Added setprintingtofactorydefault in    */
/*                                  DoColdStart                             */
/*   1.187       03-12-07  NHAhmed  Changes for Force/Amp Step and Amplitude*/
/*                                  for Scrub time.                         */
/*   1.188       03-27-07  NHAhmed  Added VQS Variables in Min/Max Limit,Save
/*                                  & CompressedPreset. 
/*   1.189       03-29-07  YGupta   Rename FlagAmplitudeStep and FlagAmplitudeFixed
                                    to AmplitudeStepEnableFlag and AmplitudeFixedEnableFlag.
/*   1.190       04-05-07  NHAhmed  Check-in for AmpScrubTime               */
/*   1.191       04-24-07  NHAhmed  Changes related to Force and Amplitude  */
/*                                  Step/Fixed.                             */
/*   1.192       04-27-07  Ygupta   Made changes related to Force and Amplitude  */
/*                                  Step/Fixed.                             */
/*   1.193       05-23-07  NHAhmed  Changed the Max value for VQS total cycle time*/
/*   1.194       10-22-07  NHAhmed  Changes done for LangTest phase 0       */
/*   1.195       01-11-08  NHAhmed  Some functions are replicated and updated,*/
/*                                  keeping all functionality same.           */
/*   1.196       04-14-08  NHAhmed  Renamed Some functions and also some   */
/*                                  modification has been done.            */
/*   1.197       09-04-08  YGupta   CleanUp for LangTest Project.          */
/*   1.198       09-09-08  NHAhmed  CleanUp for multi-language support.    */
/*   1.199       09-10-09  BEkymer  Add new define MICRO where needed      */
/*   1.200       06-08-10  PDwivedi Modify SetMaxMinValues for standard MICRO.*/ 
/*   1.202       08-07-12  JWang    Modify SetMaxMinValues for Branson Special*/
/*                                  Function which can make the MinValue, MaxValue*/
/*                                  updated.                               */
/*   1.203       06-24-13 HSanchezZ updated to the proper functionality of the previous changes*/
/*   1.204       09-03-14 HSanchezZ Change the extension of the PresetId to */
/*									to show on the VGA screen               */				 

/*----------------------------- DESCRIPTION --------------------------------*/

/* This module contains all the code to deal with preset 0 - 10 (the current*/
/* preset).  All references to the preset will be done through this module. */
/* This includes the following functions:                                   */
/*                                                                          */
/*   WritePreset-take current preset and save it into BBRAM                 */
/*   ReadPreset-read the preset from BBRAM into the current preset          */



/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define POWER_MIN       10      /*     10 =     1.0 %  */
#define POWER_MAX     1000      /*   1000 =   100.0 %  */
#define ENERGY_MIN      10      /*     10 =     1.0 j  */
#define ENERGY_MAX  990000      /* 990000 =  99,000 j  */
#define TIME_MIN        10      /*     10 =   0.010 s  */
#define TIME_MAX     30000      /*  30000 =  30.000 s  */
#define PRETRG_MAX   10000      /*  10000 =  10.000 s  */
#define EB_TIME_MAX   1000      /*   1000 =   1.000 s  */
#define COL_MIN          4      /*      4 =  0.0004 in */
#define COL_MAX      10000      /*  10000 =  1.0000 in */
#define ABS_MIN       1250      /*   1250 =  0.1250 in */
#define AMP_MIN         10      /*     10 =      10 %  */
#define AMP_MAX        100      /*    100 =     100 %  */
#define TEST_AMP        50      /*     50 =      50 %  */
#define COUNTER_MAX  99999      /*  99999 =   99999    */
#define SHIFT_MIN        0      /* Shift algorithm for f0 test code - min shift */
#define SHIFT_MAX        6      /* Shift algorithm for f0 test code - max shift */
#define FIVE_LBS        50      /* 5 pounds force      */
#define TEN_LBS        100      /* 10 pounds force     */
#define FIFTEEN_LBS    150      /* 15 pounds force     */
#define EB_DEF_TIME     20      /*     20 =   0.020 s  */
#define MAX_CYCLETIME 65000     /* 65000  =  65 s      */

/*------------------------------ INCLUDES ----------------------------------*/

#include <psos.h>
#include "opcodes.h"                  /* intertask opcodes definitions      */
#include "myptrmsg.h"                 /* generic message pointer type       */
#include "nvm_msg.h"
#include "fpdatmsg.h"
#include "util.h"
#include "preset.h"
#include "ck_qsend.h"                 /* contains function interface        */
#include "battram.h"
#include "menu.h"
#include "menu4.h"
#include "menu3.h"
#include "menu7a.h"
#include "menu7.h"
#include "menu1.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "selctkey.h"
#include "ready.h"
#include "serial.h"
#include "rxcharcv.h"
#include "weld_obj.h"
#include "alsetup.h"
#include "led.h"
#include "actnvram.h"
#include "alarms.h"
#include "spidd.h"
#include "beep.h"
#include "digout.h"
#include "dups_api.h"
#include "string.h"
#include "dups.h"
#include "DrawScrn.h"
#include "inports.h"
#include "outports.h"
#include "statedrv.h"
#include "command.h"

/*------------------------------ LOCAL DEFINES -----------------------------*/
#define EXT_START_TIMEOUT 5000

/*------------------------- FUNCTION PROTOTYPING ---------------------------*/
void RecallColdstartPreset(UINT32 MenuExtra);
BOOLEAN* GetInputPtr(UINT16 InputBit);
void InitSBL(void);
void SetupPretriggerFlags(void);

void SetupAmplitudeStepFlag(void);
void SetupForceStepFlag(void);
/*----------------------- LOCAL TYPE DECLARATIONS --------------------------*/

 NVM_ACCESS_MSG                  NvmAccessMsg;


/*----------------------------- GLOBAL DATA --------------------------------*/
/*                      (scope is global to ALL files)                      */

SETUPS_Ver800 RunningPreset;
PRESET_COMPRESSED  *CompressPresset;


UINT16 ColdStartInProcess;
UINT16 ForceStepEnable,AmpStepEnable;

/* ---------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                          (scope is global to THIS file)                  */

static UINT32 PsosReturnStatus;


/*------------------------------ EXTERNAL DATA -----------------------------*/ 


extern WELD_DATA   WeldingResults, FinalResults;                                        
extern CONFIGSETUP CurrentSetup;

extern UINT8   ColdStartFlag;
extern UINT8   AlarmDetectedFlag;
extern UINT8   MainKeyFlag;
extern UINT8   ActivePreset;
extern UINT16  ColdStartDone;
extern const UINT16  CurrentVersion;
extern enum ERRORCODE_ARG ErrorCode;
extern UINT16  SetupAlarmFlag;
extern UINT16  PresetHasBeenOKed;
extern SINT16  BlankMenuCounter;
extern UINT8   PowerUpColdStart;
extern SETUPS_Ver800   CurrentPreset;
extern SETUPS_Ver800   MinLimit;
extern SETUPS_Ver800   MaxLimit;
extern SINT32  WeldCounter;
extern UINT16  PrinterBufferReadyFlag;
extern UINT16  PresetNeedsToBeUpdated;
extern UINT16  TotalAlarmCount;
extern void    LastDatePresetWasSaved(void);
extern BOOLEAN DigPotKey;
extern BOOLEAN QVGAHwAvail;
extern UINT32 NvmmQid;
extern UINT32 SysmQueueId;
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

// set these variables appropriately when recalling presets
// these flags have positive logic, no matter how the flags are
// stored in presets
extern UINT16 FlagPretriggerOff;
extern UINT16 FlagPretriggerAuto;
extern UINT16 FlagPretriggerDist;
extern UINT16 FlagPretriggerTime;
extern UINT16 FlagPretriggerAmpl; // this flag is for pretrigger amplitude
extern UNION_BOOL_UINT16 AmplitudeStepEnableFlag;
extern UNION_BOOL_UINT16 AmplitudeStepMicronsEnableFlag;
extern UINT16 AmplitudeFixedEnableFlag;

extern UINT16 ForceFixedEnableFlag;
extern UNION_BOOL_UINT16 ForceStepEnableFlag;

PRESET_COMPRESSED* PresetAddress[37] = { (PRESET_COMPRESSED*) PRESET_0_START, 
                                         (PRESET_COMPRESSED*) PRESET_1_START, 
                                         (PRESET_COMPRESSED*) PRESET_2_START, 
                                         (PRESET_COMPRESSED*) PRESET_3_START, 
                                         (PRESET_COMPRESSED*) PRESET_4_START, 
                                         (PRESET_COMPRESSED*) PRESET_5_START, 
                                         (PRESET_COMPRESSED*) PRESET_6_START, 
                                         (PRESET_COMPRESSED*) PRESET_7_START, 
                                         (PRESET_COMPRESSED*) PRESET_8_START, 
                                         (PRESET_COMPRESSED*) PRESET_9_START, 
                                         (PRESET_COMPRESSED*) PRESET_10_START,
                                         (PRESET_COMPRESSED*) PRESET_11_START,
                                         (PRESET_COMPRESSED*) PRESET_12_START,
                                         (PRESET_COMPRESSED*) PRESET_13_START,
                                         (PRESET_COMPRESSED*) PRESET_14_START,
                                         (PRESET_COMPRESSED*) PRESET_15_START,
                                         (PRESET_COMPRESSED*) PRESET_16_START,
                                         (PRESET_COMPRESSED*) PRESET_17_START,
                                         (PRESET_COMPRESSED*) PRESET_18_START,
                                         (PRESET_COMPRESSED*) PRESET_19_START,
                                         (PRESET_COMPRESSED*) PRESET_20_START,
                                         (PRESET_COMPRESSED*) PRESET_21_START,
                                         (PRESET_COMPRESSED*) PRESET_22_START,
                                         (PRESET_COMPRESSED*) PRESET_23_START,
                                         (PRESET_COMPRESSED*) PRESET_24_START,
                                         (PRESET_COMPRESSED*) PRESET_25_START,
                                         (PRESET_COMPRESSED*) PRESET_26_START,
                                         (PRESET_COMPRESSED*) PRESET_27_START,
                                         (PRESET_COMPRESSED*) PRESET_28_START,
                                         (PRESET_COMPRESSED*) PRESET_29_START,
                                         (PRESET_COMPRESSED*) PRESET_30_START,
                                         (PRESET_COMPRESSED*) PRESET_31_START,
                                         (PRESET_COMPRESSED*) PRESET_32_START,
                                         (PRESET_COMPRESSED*) PRESET_MIN_START,
                                         (PRESET_COMPRESSED*) PRESET_MAX_START,
                                         (PRESET_COMPRESSED*) PRESET_CLDSTRT_START,
					 (PRESET_COMPRESSED*) PRESET_RUNNING}; /* hs added because we need to save values if the machine is turned off during the edition of Max or Min preset*/

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/


/*-------------------------------- CODE ------------------------------------*/


void WritePreset(UINT16 PresetNumber)
/***************************************************************************/
/*                                                                         */
/*  This function will pass the current preset to the system manger to     */
/*  save in the battery backup RAM                                         */
/*                                                                         */
/***************************************************************************/
{

   NvmAccessMsg.common.source_task =  FPSC_SOURCE_TASK;
   NvmAccessMsg.common.opcode =  OP_BATTRAM_WRITE_PRESET;

   if (PresetNumber <= MAX_PRESETS) {
      CurrentPreset.PresetUpdateComplete = TRUE;
      NvmAccessMsg.offset = PresetNumber;
   }

   /* Have message queue data point to new buffer */

   CkQSend (SysmQueueId,&NvmAccessMsg,FRONT_PANEL_STATE_COORDINATOR
                ,__LINE__,MILLS_TO_TICKS(100));      /* 100 ms        */

}



void ReadPreset(UINT16 PresetNumber, UINT16 AlarmSuppressFlag)
/***************************************************************************/
/*                                                                         */
/*  This function will call the nvmmanager to read the specified preset    */
/*  and copy it to the Current Preset                                      */
/*                                                                         */
/*  The AlarmSuppressFlag if TRUE will prevent the W9 (Cal suggested)      */
/*  alarm from being created (as is the case when a preset is cleared). If */
/*  FALSE, the alarm will be created.                                      */
/*                                                                         */
/*                                                                         */
/***************************************************************************/
{
   NvmAccessMsg.common.source_task =  FPSC_SOURCE_TASK;
   NvmAccessMsg.common.opcode =  OP_BATTRAM_READ_PRESET;
   NvmAccessMsg.common.pointer_flag = DATA_PTR_NO_DEALLOC;

   if (PresetNumber <= MAX_PRESETS) {
      NvmAccessMsg.offset = PresetNumber;
   }

   CheckBattramDefaults();             /* See if BBR is initialized & working */

   CkQSend (SysmQueueId,&NvmAccessMsg,FRONT_PANEL_STATE_COORDINATOR
                ,__LINE__,MILLS_TO_TICKS(50));      /* 50 ms        */

   if ( (CurrentSetup.ControlLevel >= LEVEL_d) &&
        (AlarmSuppressFlag == FALSE) &&
        ((CurrentSetup.Actuator == AEF) ||
         (CurrentSetup.Actuator == AED) ||
         (CurrentSetup.Actuator == MICRO) ) ) {
      ErrorCodeFlag = FALSE;             /* Turn off error codes for this alarm */
      RecordAlarm(W8);   /* Actuator recalibration is suggested */
   }
}


void SetMaxMinValues(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will update the min and max preset values in battram       */
/*                                                                           */
/*****************************************************************************/
{
   SINT32  MaxStrokeLength;

   BBR_STATUS_TYPE   BattramCompletionStatus;
   SINT32   MaxEnergy;
   UINT32   MaxForce = 0;

   MaxForce = GetMaxForce();
   MaxEnergy = CurrentSetup.PSWatt * 300;
   if (MaxEnergy > ENERGY_MAX)
      MaxEnergy = ENERGY_MAX;             /* Max value even for 4000 Watt   */
   MaxStrokeLength = GetMaxStrokeLength();

   if(strcmp(MinLimit.PresetID, "MINIMUM") != 0){
      MinLimit.WeldTime = TIME_MIN;          /*                                */
      MinLimit.WeldEnergy = ENERGY_MIN;      /* 50 = 5.0 J                     */
      MinLimit.EnergyPL = ENERGY_MIN;        /* energy plus limit              */
      MinLimit.EnergyML = ENERGY_MIN;        /* energy minus limit             */
      MinLimit.ScrubTime = 1;                /* Grd det mode, scrub time       */
      MinLimit.AmpScrubTime = AMP_MIN;       /* Amp for Ground Detect Mode     */
      MinLimit.PeakPwr = POWER_MIN;          /*                                */
      MinLimit.PeakPwrCutoff = POWER_MIN;    /*                                */
      MinLimit.ColDist = COL_MIN;            /* 4 = 0.0004"                    */
      MinLimit.AbsDist = ABS_MIN;            /* 1250 = 0.1250"                 */
      MinLimit.ABSCutoffDist = ABS_MIN;      /* 1250 = 0.1250"                 */
      MinLimit.ColCutoffDist = COL_MIN;      /* 4 = 0.0004"                    */
      MinLimit.HoldTime = TIME_MIN;          /*                                */
      MinLimit.HoldForce = CurrentSetup.MinTrigForce + FIVE_LBS; /*  10 lbs    */
      MinLimit.AbDelay = 50;                 /*Tracker 3948. Min can be 50ms   */
      MinLimit.AbTime = 100;                 /*                                */
      MinLimit.AbAmp = AMP_MIN;              /*                                */
      MinLimit.MaxTimeout = 50;              /*                                */
      MinLimit.TriggerDelay = TIME_MIN;      /*                                */
      MinLimit.FreqOffset = 0;               /* Limit specifies min abs. value */
      MinLimit.EnergyPLS = ENERGY_MIN;       /*                                */
      MinLimit.EnergyMLS = ENERGY_MIN;       /*                                */
      MinLimit.EnergyPLR = ENERGY_MIN;       /*                                */
      MinLimit.EnergyMLR = ENERGY_MIN;       /*                                */
      MinLimit.TimePLS = TIME_MIN;           /*                                */
      MinLimit.TimeMLS = TIME_MIN;           /*                                */
      MinLimit.TimePLR = TIME_MIN;           /*                                */
      MinLimit.TimeMLR = TIME_MIN;           /*                                */
      MinLimit.PowerPLS = POWER_MIN;         /*                                */
      MinLimit.PowerMLS = POWER_MIN;         /*                                */
      MinLimit.PowerPLR = POWER_MIN;         /*                                */
      MinLimit.PowerMLR = POWER_MIN;         /*                                */
      MinLimit.ColPLS = COL_MIN;             /* 4 = 0.0004"                    */
      MinLimit.ColMLS = COL_MIN;             /* 4 = 0.0004"                    */
      MinLimit.ColPLR = COL_MIN;             /* 4 = 0.0004"                    */
      MinLimit.ColMLR = COL_MIN;             /* 4 = 0.0004"                    */
      MinLimit.AbsPLS = ABS_MIN;             /*                                */
      MinLimit.AbsMLS = ABS_MIN;             /*                                */
      MinLimit.AbsPLR = ABS_MIN;             /*                                */
      MinLimit.AbsMLR = ABS_MIN;             /*                                */
      MinLimit.TrsDistPLS = ABS_MIN;         /*                                */
      MinLimit.TrsDistMLS = ABS_MIN;         /*                                */
      MinLimit.TrsDistPLR = ABS_MIN;         /*                                */
      MinLimit.TrsDistMLR = ABS_MIN;         /*                                */
      MinLimit.WeldForcePLS = CurrentSetup.MinTrigForce + FIVE_LBS;      /*                                */
      MinLimit.WeldForceMLS = CurrentSetup.MinTrigForce + FIVE_LBS;      /*                                */
      MinLimit.WeldForcePLR = CurrentSetup.MinTrigForce + FIVE_LBS;      /*                                */
      MinLimit.WeldForceMLR = CurrentSetup.MinTrigForce + FIVE_LBS;      /*                                */
      MinLimit.EnergyMinVQS = ENERGY_MIN;
      MinLimit.PeakPowerMinVQS =POWER_MIN;
      MinLimit.TotalAbsMinVQS = ABS_MIN;
      MinLimit.TotalColMinVQS = COL_MIN;
      MinLimit.TotalCycleTimeMinVQS = TIME_MIN;
      MinLimit.WeldColMinVQS = COL_MIN;
      MinLimit.WeldForceMinVQS = FORCE_MIN;
      MinLimit.WeldTimeMinVQS = TIME_MIN;
      MinLimit.EnergyMaxVQS = ENERGY_MIN;
      MinLimit.PeakPowerMaxVQS =POWER_MIN;
      MinLimit.TotalAbsMaxVQS = ABS_MIN;
      MinLimit.TotalColMaxVQS = COL_MIN;
      MinLimit.TotalCycleTimeMaxVQS = TIME_MIN;
      MinLimit.WeldColMaxVQS = COL_MIN;
      MinLimit.WeldForceMaxVQS = FORCE_MIN;
      MinLimit.WeldTimeMaxVQS = TIME_MIN;
      MinLimit.AmpAMicron = 1;
      MinLimit.AmpBMicron = 1;


      switch (CurrentSetup.PSFreq) {
         default:
         case FREQ20KHZ:
            MinLimit.FreqPLS = -FREQ20_OFF;  /*                                */
            MinLimit.FreqMLS = -FREQ20_OFF;  /*                                */
            MinLimit.FreqPLR = -FREQ20_OFF;  /*                                */
            MinLimit.FreqMLR = -FREQ20_OFF;  /*                                */
            MinLimit.TriggerForce= CurrentSetup.MinTrigForce; /*               */
            break;

         case FREQ40KHZ:
            MinLimit.FreqPLS = -FREQ40_OFF;  /*                                */
            MinLimit.FreqMLS = -FREQ40_OFF;  /*                                */
            MinLimit.FreqPLR = -FREQ40_OFF;  /*                                */
            MinLimit.FreqMLR = -FREQ40_OFF;  /*                                */
            MinLimit.TriggerForce= CurrentSetup.MinTrigForce;  /*             */
            break;

         case FREQ15KHZ:
            MinLimit.FreqPLS = -FREQ15_OFF;  /*                                */
            MinLimit.FreqMLS = -FREQ15_OFF;  /*                                */
            MinLimit.FreqPLR = -FREQ15_OFF;  /*                                */
            MinLimit.FreqMLR = -FREQ15_OFF;  /*                                */
            MinLimit.TriggerForce= CurrentSetup.MinTrigForce; /*              */
            break;

         case FREQ30KHZ:
            MinLimit.FreqPLS = -FREQ30_OFF;  /*                                */
            MinLimit.FreqMLS = -FREQ30_OFF;  /*                                */
            MinLimit.FreqPLR = -FREQ30_OFF;  /*                                */
            MinLimit.FreqMLR = -FREQ30_OFF;  /*                                */
            MinLimit.TriggerForce= CurrentSetup.MinTrigForce;  /*              */
            break;
         
         case FREQ60KHZ:
            MinLimit.FreqPLS = -FREQ60_OFF;  /*                                */
            MinLimit.FreqMLS = -FREQ60_OFF;  /*                                */
            MinLimit.FreqPLR = -FREQ60_OFF;  /*                                */
            MinLimit.FreqMLR = -FREQ60_OFF;  /*                                */
            MinLimit.TriggerForce= CurrentSetup.MinTrigForce;  /*              */
            break;
      }


      MinLimit.Amp1 = AMP_MIN;               /*                                */
      MinLimit.AmpTrigTimeValue=TIME_MIN;    /*                                */
      MinLimit.AmpTrigEnerValue=ENERGY_MIN;  /* 10 = 1.0 J                     */
      MinLimit.AmpTrigPowerValue=POWER_MIN;  /*                                */
      MinLimit.AmpTrigColValue = COL_MIN;    /* 4 = 0.0004"                    */
      MinLimit.AmpTrigForceValue = CurrentSetup.MinTrigForce + FIVE_LBS;/*     */
      MinLimit.Amp2 = AMP_MIN;               /*                                */
      MinLimit.WeldForce = CurrentSetup.MinTrigForce + FIVE_LBS; /*            */
      MinLimit.ForceTrigTimeValue=TIME_MIN;  /* 10 = 1.0 J                     */
      MinLimit.ForceTrigEnerValue=ENERGY_MIN;/*                                */
      MinLimit.ForceTrigPowerValue=POWER_MIN;/*                                */
      MinLimit.ForceTrigColValue = COL_MIN;  /* 4 = 0.0004"                    */
      MinLimit.ForceTrigAmpValue = AMP_MIN;  /*                                */
      MinLimit.Force2 = CurrentSetup.MinTrigForce + FIVE_LBS; /*               */
      MinLimit.PreTrigDist = ABS_MIN;        /* 1250 = 0.1250"                 */
      MinLimit.PreTrigDelay = TIME_MIN;      /* 0.010 seconds                  */
      MinLimit.PreTrigAmp = AMP_MIN;         /*                                */
      MinLimit.DownSpdStart = 1;             /* Initial downspeed value        */
      MinLimit.ActClrDistance = ABS_MIN;
      MinLimit.MissingPartMin = ABS_MIN;     /* 1250 = 0.1250"                 */
      MinLimit.MissingPartMax = ABS_MIN;     /* 1250 = 0.1250"                 */
      MinLimit.RTDist = 1000;                /*                                */
      MinLimit.WeldHistoryValue = 1;         /*                                */
      MinLimit.WeldSummaryValue = 1;         /*                                */
      MinLimit.VelocityGraphValue = 1;       /*                                */
      MinLimit.PowerGraphValue = 1;          /*                                */
      MinLimit.ColDistanceGraphValue = 1;    /*                                */
      MinLimit.AbsDistanceGraphValue = 1;    /*                                */
      MinLimit.ForceGraphValue = 1;          /*                                */
      MinLimit.FrequencyGraphValue = 1;      /*                                */
      MinLimit.AmplitudeGraphValue = 1;      /*                                */
      MinLimit.SetupPresetValue = 1;         /*                                */
      MinLimit.SeqPresetValue = 1;           /*                                */
      MinLimit.WeldCount = 0;                /*                                */
      MinLimit.TestAmp = AMP_MIN;            /*                                */
      MinLimit.Year = 0;                     /*                                */
      MinLimit.Month = 1;                    /*                                */
      MinLimit.Day = 1;                      /*                                */
      MinLimit.Hour = 0;                     /*                                */
      MinLimit.Minute = 0;                   /*                                */
      MinLimit.XScaleTime = XSCALEMINVALUE;  /* min value of x-axis scale      */

      MinLimit.SetRTComp = 1;                /* Min value of R/T Comp in %     */
      MinLimit.EBTime = TIME_MIN;            /* Min value for energy braking   */
      MinLimit.PMCLowLimit = 1;              /* Min % value for PMC Low Limit  */
      MinLimit.PMCHighLimit = 1;             /* Min % value for PMC High Limit */
      MinLimit.PMCTimeout = 1;               /* Min PMC Timeout                */

      MinLimit.WeldMode = TIMEMODE;            /* Set weld mode                 */
      MinLimit.ScrubTimeFlag = 1;              /* Turn scrub time OFF           */
      MinLimit.ControlLimitsFlag = 0;          /* CHOICE structure, so 1 = on   */
      MinLimit.PeakPwrCutoffFlag = 1;          /* Off                           */
      MinLimit.ABSCutoffFlag = 1;              /* VARIABLE structure, so 1= off */
      MinLimit.ColCutoffFlag = 1;              /* 1 = off                       */
      MinLimit.HoldTimeFlag = 0;               /* VARIABLE structure, so 0=On   */
      MinLimit.AbFlag = 0;                     /* CHOICE structure, so 0 = off  */
      MinLimit.TriggerDelayFlag = 1;           /* VARIABLE structure, so 1= Off */
      MinLimit.FreqOffsetFlag = 0;             /* CHOICE structure, so 0=Off    */
      MinLimit.SuspectLimitsFlag = 0;          /* CHOICE structure, so 0=Off    */
      MinLimit.RejectLimitsFlag = 0;           /* CHOICE structure, so 0=Off    */
      MinLimit.SuspectLimits=0x7ffe;           /* VARIABLE 1 = off              */
      MinLimit.RejectLimits=0x7ffe;            /* VARIABLE 1 = off              */
      MinLimit.SeekFunFlag = 0;                /*                               */
      MinLimit.Amp2Flag = 0xfffa;              /* CHOICE structure, so 0=Off    */
      MinLimit.AmpTrigExtFlag = 0;             /*                               */
      MinLimit.ForceTrigExtFlag = 0;           /*                               */
      MinLimit.Force2Flag = 0xfffa;            /* CHOICE structure, so 0=Off    */
      MinLimit.AutoTrigFlag = TRUE;            /* Acts like Radio Button        */
      MinLimit.PreTrigFlag =0;                 /* CHOICE structure, so 0=Off    */
      MinLimit.RTFlag = 0;                     /* CHOICE structure, so 0=Off    */
      MinLimit.PreTrigSwitch = 0;              /* CHOICE structure, so 0=Off    */
      MinLimit.EnergyCompFlag = 0;             /* CHOICE structure, so 0=Off    */
      MinLimit.SuspectLimitsFlag = 0;          /* CHOICE structure, so 0=Off    */
      MinLimit.RejectLimitsFlag = 0;           /* CHOICE structure, so 0=Off    */
      MinLimit.CycleAbortFlag = 0;             /* CHOICE structure, so 0=Off    */
      MinLimit.GndDetectFlag = 0;              /* CHOICE structure, so 0=Off    */
      MinLimit.SusResetRequired = 0;           /* CHOICE structure, so 0=Off    */
      MinLimit.RejResetRequiredFlag = 0;       /* CHOICE structure, so 0=Off    */
      MinLimit.PresetUpdateComplete = TRUE;
      MinLimit.ActClrFlag = 0;                 /* Choice structure so 0=off    */
      MinLimit.MissingPartFlag = 0;
      MinLimit.MissingMinFlag = 1;             /* Pointer to disable/enable flag    */
      MinLimit.MissingMaxFlag = 1;             /* Pointer to disable/enable flag    */
      strcpy(MinLimit.PresetID, "DEFAULT");
      SaveCompressedPreset( (PRESET_COMPRESSED *) PRESET_MIN_START, &MinLimit);
   }
   else
   {
      memcpy(&RunningPreset,&CurrentPreset,sizeof(SETUPS_Ver800));           /* It copy CurrentPreset to runningPreset to save these values*/ 
      RecallCompressedPreset( (PRESET_COMPRESSED *) PRESET_MIN_START);	     /*  loading the Preset_min_start on current preset*/		
      memcpy(&MinLimit,&CurrentPreset,sizeof(SETUPS_Ver800)); 		     /*moving the values of Preset_min_start to minlimit */	
      memcpy(&CurrentPreset,&RunningPreset,sizeof(SETUPS_Ver800));  	     /*Recovering the currentpreset*/	
   }	


     /*----  Now do the Max limits  ----*/
   if(strcmp(MaxLimit.PresetID,"MAXIMUM") != 0){
      MaxLimit.WeldTime = TIME_MAX;            /*                              */
      MaxLimit.WeldEnergy = MaxEnergy;         /* 10 = 1.0 J                   */
      MaxLimit.EnergyPL = MaxEnergy;           /* TEC mode energy plus limit   */
      MaxLimit.EnergyML = MaxEnergy;           /* TEC mode energy minus limit  */
      MaxLimit.ScrubTime = 500;                /* Ground detect, scrub tim     */
      MaxLimit.AmpScrubTime = AMP_MAX;         /* Ground Detect Amplitude      */
      MaxLimit.PeakPwr = POWER_MAX;            /*                              */
      MaxLimit.PeakPwrCutoff = POWER_MAX;      /*                              */
      MaxLimit.ColDist = COL_MAX;              /* 1 = 0.0001"                  */
      MaxLimit.AbsDist = MaxStrokeLength;      /* 40000 = 4.0"                 */
      MaxLimit.ABSCutoffDist = MaxStrokeLength;/* 40000 = 4.0"                 */
      MaxLimit.ColCutoffDist = COL_MAX;        /* 1000 = 0.1"                  */
      MaxLimit.HoldTime = TIME_MAX;            /*                              */
      MaxLimit.AbDelay = 2000;                 /*                              */
      MaxLimit.AbTime = 2000;                  /*                              */
      MaxLimit.AbAmp = AMP_MAX;                /*                              */
      MaxLimit.MaxTimeout = TIME_MAX;          /*                              */
      MaxLimit.TriggerDelay = TIME_MAX;        /*                              */
      MaxLimit.EnergyPLS = MaxEnergy;          /*                              */
      MaxLimit.EnergyMLS = MaxEnergy;          /*                              */
      MaxLimit.EnergyPLR = MaxEnergy;          /*                              */
      MaxLimit.EnergyMLR = MaxEnergy;          /*                              */
      MaxLimit.TimePLS = TIME_MAX;             /*                              */
      MaxLimit.TimeMLS = TIME_MAX;             /*                              */
      MaxLimit.TimePLR = TIME_MAX;             /*                              */
      MaxLimit.TimeMLR = TIME_MAX;             /*                              */
      MaxLimit.PowerPLS = POWER_MAX;           /*                              */
      MaxLimit.PowerMLS = POWER_MAX;           /*                              */
      MaxLimit.PowerPLR = POWER_MAX;           /*                              */
      MaxLimit.PowerMLR = POWER_MAX;           /*                              */
      MaxLimit.ColPLS = COL_MAX;               /*                              */
      MaxLimit.ColMLS = COL_MAX;               /*                              */
      MaxLimit.ColPLR = COL_MAX;               /*                              */
      MaxLimit.ColMLR = COL_MAX;               /*                              */
      MaxLimit.AbsPLS = MaxStrokeLength;       /*                              */
      MaxLimit.AbsMLS = MaxStrokeLength;       /*                              */
      MaxLimit.AbsPLR = MaxStrokeLength;       /*                              */
      MaxLimit.AbsMLR = MaxStrokeLength;       /*                              */
      MaxLimit.TrsDistPLS = MaxStrokeLength;   /*                              */
      MaxLimit.TrsDistMLS = MaxStrokeLength;   /*                              */
      MaxLimit.TrsDistPLR = MaxStrokeLength;   /*                              */
      MaxLimit.TrsDistMLR = MaxStrokeLength;   /*                              */
      MaxLimit.EnergyMaxVQS = ENERGY_MAX;
      MaxLimit.PeakPowerMaxVQS =POWER_MAX;
      MaxLimit.TotalAbsMaxVQS = MaxStrokeLength;
      MaxLimit.TotalColMaxVQS = COL_MAX;
      MaxLimit.TotalCycleTimeMaxVQS = MAX_CYCLETIME;
      MaxLimit.WeldColMaxVQS = COL_MAX;
      MaxLimit.WeldForceMaxVQS = MaxForce;
      MaxLimit.WeldTimeMaxVQS = TIME_MAX;
      MaxLimit.EnergyMinVQS = ENERGY_MAX;
      MaxLimit.PeakPowerMinVQS =POWER_MAX;
      MaxLimit.TotalAbsMinVQS = MaxStrokeLength;
      MaxLimit.TotalColMinVQS = COL_MAX;
      MaxLimit.TotalCycleTimeMinVQS = MAX_CYCLETIME;
      MaxLimit.WeldColMinVQS = COL_MAX;
      MaxLimit.WeldForceMinVQS = MaxForce;
      MaxLimit.WeldTimeMinVQS = TIME_MAX;
      MaxLimit.AmpAMicron = 200;
      MaxLimit.AmpBMicron = 200;


      switch (CurrentSetup.PSFreq) {
         default:
         case FREQ20KHZ:
            MaxLimit.FreqPLS = +FREQ20_OFF;    /*                              */
            MaxLimit.FreqMLS = +FREQ20_OFF;    /*                              */
            MaxLimit.FreqPLR = +FREQ20_OFF;    /*                              */
            MaxLimit.FreqMLR = +FREQ20_OFF;    /*                              */
            MaxLimit.FreqOffset = +FREQ20_OFF; /*                              */
            break;

         case FREQ40KHZ:
            MaxLimit.FreqPLS = +FREQ40_OFF;    /*                              */
            MaxLimit.FreqMLS = +FREQ40_OFF;    /*                              */
            MaxLimit.FreqPLR = +FREQ40_OFF;    /*                              */
            MaxLimit.FreqMLR = +FREQ40_OFF;    /*                              */
            MaxLimit.FreqOffset = +FREQ40_OFF; /*                              */
            break;

         case FREQ15KHZ:
            MaxLimit.FreqPLS = +FREQ15_OFF;    /*                              */
            MaxLimit.FreqMLS = +FREQ15_OFF;    /*                              */
            MaxLimit.FreqPLR = +FREQ15_OFF;    /*                              */
            MaxLimit.FreqMLR = +FREQ15_OFF;    /*                              */
            MaxLimit.FreqOffset = +FREQ15_OFF; /*                              */
            break;

         case FREQ30KHZ:
            MaxLimit.FreqPLS = +FREQ30_OFF;    /*                              */
            MaxLimit.FreqMLS = +FREQ30_OFF;    /*                              */
            MaxLimit.FreqPLR = +FREQ30_OFF;    /*                              */
            MaxLimit.FreqMLR = +FREQ30_OFF;    /*                              */
            MaxLimit.FreqOffset = +FREQ30_OFF; /*                              */
            break;
      
         case FREQ60KHZ:
            MaxLimit.FreqPLS = +FREQ60_OFF;    /*                              */
            MaxLimit.FreqMLS = +FREQ60_OFF;    /*                              */
            MaxLimit.FreqPLR = +FREQ60_OFF;    /*                              */
            MaxLimit.FreqMLR = +FREQ60_OFF;    /*                              */
            MaxLimit.FreqOffset = +FREQ60_OFF; /*                              */
            break;
      }

      MaxLimit.Amp1 = AMP_MAX;                 /*                              */
      MaxLimit.AmpTrigTimeValue = TIME_MAX;    /*                              */
      MaxLimit.AmpTrigEnerValue = MaxEnergy;   /*                              */
      MaxLimit.AmpTrigPowerValue = POWER_MAX;  /*                              */
      MaxLimit.AmpTrigColValue = COL_MAX;      /*                              */
      MaxLimit.Amp2 = AMP_MAX;                 /*                              */
      MaxLimit.ForceTrigTimeValue= TIME_MAX;   /*                              */
      MaxLimit.ForceTrigEnerValue= MaxEnergy;  /*                              */
      MaxLimit.ForceTrigPowerValue = POWER_MAX;/*                              */
      MaxLimit.ForceTrigColValue =COL_MAX;     /*                              */
      MaxLimit.ForceTrigAmpValue = AMP_MAX;    /*                              */
      MaxLimit.PreTrigDist = MaxStrokeLength;  /*                              */
      MaxLimit.PreTrigDelay = PRETRG_MAX;      /* 10 seconds for now           */
      MaxLimit.PreTrigAmp = AMP_MAX;           /*                              */
      MaxLimit.DownSpdStart = 100;             /* Initial downspeed value      */
      MaxLimit.RTDist = MaxStrokeLength;       /*                              */
      MaxLimit.ActClrDistance= MaxStrokeLength;/*                              */
      MaxLimit.MissingPartMin= MaxStrokeLength;/* 40000 = 4.0"                 */
      MaxLimit.MissingPartMax= MaxStrokeLength;/* 40000 = 4.0"                 */
      MaxLimit.WeldHistoryValue = COUNTER_MAX;     /*                          */
      MaxLimit.WeldSummaryValue = COUNTER_MAX;     /*                          */
      MaxLimit.VelocityGraphValue = COUNTER_MAX;   /*                          */
      MaxLimit.PowerGraphValue = COUNTER_MAX;      /*                          */
      MaxLimit.ColDistanceGraphValue = COUNTER_MAX;/*                          */
      MaxLimit.AbsDistanceGraphValue = COUNTER_MAX;/*                          */
      MaxLimit.ForceGraphValue = COUNTER_MAX;      /*                          */
      MaxLimit.FrequencyGraphValue = COUNTER_MAX;  /*                          */
      MaxLimit.AmplitudeGraphValue = COUNTER_MAX;  /*                          */
      MaxLimit.SetupPresetValue = COUNTER_MAX;     /*                          */
      MaxLimit.SeqPresetValue = COUNTER_MAX;       /*                          */
      MaxLimit.WeldCount = 999999999;          /*                              */
      MaxLimit.TestAmp = AMP_MAX;              /*                              */
      MaxLimit.Year = 99;                      /*                              */
      MaxLimit.Month = 12;                     /*                              */
      MaxLimit.Day = 31;                       /*                              */
      MaxLimit.Hour = 23;                      /*                              */
      MaxLimit.Minute = 59;                    /*                              */
      MaxLimit.XScaleTime = XSCALEMAXVALUE;    /*  max x-axis scale value      */

      if ( (CurrentSetup.Actuator == AED) ||
           (CurrentSetup.Actuator == AEF) ||
           (CurrentSetup.Actuator == MICRO) )
      {
         MaxForce = GetMaxForce();
         MaxLimit.HoldForce = MaxForce;        /*                              */
         if(CurrentSetup.Actuator == MICRO)
            MaxLimit.TriggerForce = MICRO_MAXFORCE_40MM;/*Restrict the max trigger force to 135 lbs.*/
         else
            MaxLimit.TriggerForce = MaxForce;  /*                              */
         MaxLimit.WeldForcePLS = MaxForce;     /*                              */
         MaxLimit.WeldForceMLS = MaxForce;     /*                              */
         MaxLimit.WeldForcePLR = MaxForce;     /*                              */
         MaxLimit.WeldForceMLR = MaxForce;     /*                              */
         MaxLimit.AmpTrigForceValue = MaxForce;/*                              */
         MaxLimit.WeldForce = MaxForce;        /*                              */
         MaxLimit.Force2 = MaxForce;           /*                              */
      }
   
      MaxLimit.SetRTComp = 100;                /* Max value of R/T Comp in %   */
      MaxLimit.EBTime = EB_TIME_MAX;           /* Max value for energy braking */
      MaxLimit.PMCLowLimit = 100;              /* Max % value for PMC Low Limit  */
      MaxLimit.PMCHighLimit = 100;             /* Max % value for PMC High Limit */
      MaxLimit.PMCTimeout = 400;               /* Max PMC Timeout                */

      MaxLimit.WeldMode = TIMEMODE;
      MaxLimit.ScrubTimeFlag = 1;
      MaxLimit.ControlLimitsFlag = 0;
      MaxLimit.PeakPwrCutoffFlag = 1;
      MaxLimit.ABSCutoffFlag = 1;
      MaxLimit.ColCutoffFlag = 1;
      MaxLimit.HoldTimeFlag = 0;
      MaxLimit.AbFlag = 0;
      MaxLimit.TriggerDelayFlag = 1;
      MaxLimit.FreqOffsetFlag = 0;
      MaxLimit.SuspectLimitsFlag = 0;
      MaxLimit.RejectLimitsFlag = 0;
      MaxLimit.SuspectLimits=0x7ffe;
      MaxLimit.RejectLimits=0x7ffe;
      MaxLimit.SeekFunFlag = 0;
      MaxLimit.Amp2Flag = 0xfffa;
      MaxLimit.AmpTrigExtFlag = 0;
      MaxLimit.ForceTrigExtFlag = 0;
      MaxLimit.Force2Flag = 0xfffa;
      MaxLimit.AutoTrigFlag = TRUE;
      MaxLimit.PreTrigFlag =0;
      MaxLimit.RTFlag = 0;
      MaxLimit.PreTrigSwitch = 0;
      MaxLimit.EnergyCompFlag = 0;
      MaxLimit.SuspectLimitsFlag = 0;
      MaxLimit.RejectLimitsFlag = 0;
      MaxLimit.CycleAbortFlag = 0;
      MaxLimit.GndDetectFlag = 0;
      MaxLimit.SusResetRequired = 0;
      MaxLimit.RejResetRequiredFlag = 0;
      MaxLimit.PresetUpdateComplete = TRUE;
      MaxLimit.ActClrFlag = 0;
      MaxLimit.MissingPartFlag = 0;
      MaxLimit.MissingMinFlag = 1;
      MaxLimit.MissingMaxFlag = 1;
      strcpy(MaxLimit.PresetID, "DEFAULT");
      SaveCompressedPreset( (PRESET_COMPRESSED *) PRESET_MAX_START, &MaxLimit);
   }
   else 
   {
      memcpy(&RunningPreset,&CurrentPreset,sizeof(SETUPS_Ver800));           /* It copy CurrentPreset to runningPreset to save these values*/ 
      RecallCompressedPreset( (PRESET_COMPRESSED *) PRESET_MAX_START);       /*  loading the Preset_min_start on current preset*/	
      memcpy(&MaxLimit,&CurrentPreset,sizeof(SETUPS_Ver800));                /*moving the values of Preset_min_start to minlimit */
      memcpy(&CurrentPreset,&RunningPreset,sizeof(SETUPS_Ver800));           /*Recovering the currentpreset*/

   }

/****    Make sure MINIMUM & MAXIMUM preset are capable of running    ****/
/****    and reflect cold start values where choices occur            ****/

}



void SetDefaultValues(void)
/*****************************************************************************/
/*                                                                           */
/*  This function will update the current preset with default values when    */
/*  a cold start is executed                                                 */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 x;
   BBR_STATUS_TYPE   BattramCompletionStatus;
   SINT32   MaxEnergy;
   SINT32  MaxStrokeLength;
   UINT32   MaxForce = 0;

   MaxForce = GetMaxForce();
   MaxEnergy = CurrentSetup.PSWatt * 300;
   MaxStrokeLength = GetMaxStrokeLength();
   
   RecallCompressedPreset( (PRESET_COMPRESSED *) PRESET_CLDSTRT_START);	   

   if(strcmp(CurrentPreset.PresetID, "EdiColdStart") != 0)  /*  if the value was edited */
   {
   CurrentPreset.WeldMode = TIMEMODE;      /*                               */
   CurrentPreset.WeldTime = 10;            /*                               */
   CurrentPreset.WeldEnergy = ENERGY_MIN;  /* 50 = 5.0 J                    */
   CurrentPreset.EnergyPL = MaxEnergy;     /* TEC mode energy plus limit    */
   CurrentPreset.EnergyML = ENERGY_MIN;    /* TEC mode energy minus limit   */
   CurrentPreset.ScrubTime = 1;            /* Ground detect mode, scrub time*/
   CurrentPreset.ScrubTimeFlag = 1;        /* Turn scrub time OFF           */
   CurrentPreset.PeakPwr = 100;            /*                               */
   CurrentPreset.ControlLimitsFlag = 0;    /* CHOICE structure, so 1 = on   */
   CurrentPreset.PeakPwrCutoffFlag = 1;    /* Off                           */           
   CurrentPreset.PeakPwrCutoff = POWER_MIN;/*                               */
   CurrentPreset.ColDist = 4;              /* 4 = 0.0004"                   */
   CurrentPreset.AbsDist = ABS_MIN;        /*                               */
   CurrentPreset.ABSCutoffFlag = 1;        /* VARIABLE structure, so 1= off */
   CurrentPreset.ABSCutoffDist = ABS_MIN;  /*                               */
   CurrentPreset.ColCutoffFlag = 1;        /* 1 = off                       */
   CurrentPreset.ColCutoffDist = 4;        /* 1000 = 0.1"                   */
   CurrentPreset.HoldTimeFlag = 0;         /* VARIABLE structure, so 0=On   */
   CurrentPreset.HoldTime = 10;            /*                               */
   CurrentPreset.HoldForce = FIFTEEN_LBS;  /*  15 lbs                       */
   CurrentPreset.AbFlag = 0;               /* CHOICE structure, so 0 = off  */
   CurrentPreset.AbDelay = 100;            /*                               */
   CurrentPreset.AbTime = 100;             /*                               */
   CurrentPreset.AbAmp = 100;              /*                               */
   CurrentPreset.PresetID[0] = 0;          /*                               */
   CurrentPreset.MaxTimeout = 6000;        /*                               */
   CurrentPreset.TriggerForce = TEN_LBS;   /* Issue 3276                    */
   CurrentPreset.TriggerDelayFlag = 1;     /* VARIABLE structure, so 1= Off */ 
   CurrentPreset.TriggerDelay = 10;        /*                               */
   CurrentPreset.FreqOffset = 0;           /*                               */
   CurrentPreset.FreqOffsetFlag = 0;       /* CHOICE structure, so 0=Off    */
   CurrentPreset.SuspectLimitsFlag = 0;    /* CHOICE structure, so 0=Off    */
   CurrentPreset.RejectLimitsFlag = 0;     /* CHOICE structure, so 0=Off    */
   CurrentPreset.SuspectLimits=0x7ffe;     /* VARIABLE 1 = off              */
   CurrentPreset.RejectLimits=0x7ffe;      /* VARIABLE 1 = off              */
   CurrentPreset.EnergyPLS = ENERGY_MIN;   /*                               */
   CurrentPreset.EnergyMLS = ENERGY_MIN;   /*                               */
   CurrentPreset.EnergyPLR = ENERGY_MIN;   /*                               */
   CurrentPreset.EnergyMLR = ENERGY_MIN;   /*                               */
   CurrentPreset.TimePLS = 10;             /*                               */               
   CurrentPreset.TimeMLS = 10;             /*                               */
   CurrentPreset.TimePLR = 10;             /*                               */               
   CurrentPreset.TimeMLR = 10;             /*                               */
   CurrentPreset.PowerPLS = POWER_MIN;     /*                               */                       
   CurrentPreset.PowerMLS = POWER_MIN;     /*                               */                       
   CurrentPreset.PowerPLR = POWER_MIN;     /*                               */                       
   CurrentPreset.PowerMLR = POWER_MIN;     /*                               */                       
   CurrentPreset.ColPLS = 4;               /*                               */               
   CurrentPreset.ColMLS = 4;               /*                               */               
   CurrentPreset.ColPLR = 4;               /*                               */               
   CurrentPreset.ColMLR = 4;               /*                               */               
   CurrentPreset.AbsPLS = ABS_MIN;         /*                               */               
   CurrentPreset.AbsMLS = ABS_MIN;         /*                               */               
   CurrentPreset.AbsPLR = ABS_MIN;         /*                               */               
   CurrentPreset.AbsMLR = ABS_MIN;         /*                               */               
   CurrentPreset.TrsDistPLS = ABS_MIN;     /*                               */                       
   CurrentPreset.TrsDistMLS = ABS_MIN;     /*                               */                       
   CurrentPreset.TrsDistPLR = ABS_MIN;     /*                               */                       
   CurrentPreset.TrsDistMLR = ABS_MIN;     /*                               */                       
   CurrentPreset.WeldForcePLS = CurrentSetup.MinTrigForce + FIVE_LBS; /*                               */               
   CurrentPreset.WeldForceMLS = CurrentSetup.MinTrigForce + FIVE_LBS; /*                               */               
   CurrentPreset.WeldForcePLR = CurrentSetup.MinTrigForce + FIVE_LBS; /*                               */               
   CurrentPreset.WeldForceMLR = CurrentSetup.MinTrigForce + FIVE_LBS; /*                               */               
   CurrentPreset.SeekFunFlag = 0;              /*                               */
   CurrentPreset.XScaleTime = 2000;        /*                               */

   CurrentPreset.FreqPLS = 0;              /*                               */       
   CurrentPreset.FreqMLS = 0;              /*                               */       
   CurrentPreset.FreqPLR = 0;              /*                               */       
   CurrentPreset.FreqMLR = 0;              /*                               */       
   CurrentPreset.Amp2Flag = 0xfffa;        /* CHOICE structure, so 0=Off    */
   CurrentPreset.Amp1 = 100;               /*                               */
   CurrentPreset.AmpScrubTime = 100;       /* Ground detect mode, Amplitude */
   CurrentPreset.AmpTrigTimeValue=TIME_MIN;/*                               */
   CurrentPreset.AmpTrigEnerValue=ENERGY_MIN;/* 50 = 5.0 J                  */
   CurrentPreset.AmpTrigPowerValue=POWER_MIN;/*                             */
   CurrentPreset.AmpTrigColValue = 4;      /* 4  = 0.0004"                  */
   CurrentPreset.AmpTrigForceValue = CurrentSetup.MinTrigForce + FIVE_LBS; /*                               */
   CurrentPreset.AmpTrigExtFlag = 0;       /*                               */
   CurrentPreset.Amp2 = 100;               /*                               */
   CurrentPreset.WeldForce = FIFTEEN_LBS;  /*  DCS #3298                    */
   CurrentPreset.ForceTrigTimeValue=TIME_MIN;/* 10 = 1.0 J                  */
   CurrentPreset.ForceTrigEnerValue=ENERGY_MIN;/* 50 = 5.0 J                */
   CurrentPreset.ForceTrigPowerValue=POWER_MIN;/*                           */
   CurrentPreset.ForceTrigColValue = 4;    /* 4  = 0.0004"                  */
   CurrentPreset.ForceTrigAmpValue = 10;   /*                               */
   CurrentPreset.ForceTrigExtFlag = 0;       /*                               */
   CurrentPreset.Force2Flag = 0xfffa;      /* CHOICE structure, so 0=Off    */
   CurrentPreset.Force2 = CurrentSetup.MinTrigForce + FIVE_LBS; /* 10 lbs   */
   CurrentPreset.AutoTrigFlag = TRUE;      /* Acts like Radio Button        */
   CurrentPreset.PreTrigDistFlag = TRUE;   /* True = off Radio Button       */
   CurrentPreset.PreTrigDist = ABS_MIN;    /* 1250 = 0.1250"                */
   CurrentPreset.PreTrigAmp = 100;         /*                               */
   CurrentPreset.PreTrigFlag =0;           /* CHOICE structure, so 0=Off    */
   CurrentPreset.PreTrigDelayFlag = TRUE;  /* Pretrigger as time mode off   */
   CurrentPreset.PreTrigDelay = TIME_MIN;  /* Pretrigger time delay         */
   CurrentPreset.ExtTrgDelay = 0;          /*Ext Delay disabled, By default */
   CurrentPreset.EnergyBraking = 0;        /*Energy Braking is disabled     */
   CurrentPreset.WeldFR = RATE_NORMAL;     /*  normal                       */
   CurrentPreset.StepFR = RATE_NORMAL;     /*  normal                       */
   CurrentPreset.HoldFR = RATE_NORMAL;     /*  normal                       */
   CurrentPreset.DownSpdStart = 20;        /* Initial downspeed value       */
   CurrentPreset.RTFlag = 0;               /* CHOICE structure, so 0=Off    */
   CurrentPreset.RTDist = 1000;            /*                               */
   CurrentPreset.RTPosSW = 0;              /*                               */
   CurrentPreset.WeldHistoryValue = 1;     /*                               */
   CurrentPreset.WeldSummaryValue = 1;     /*                               */
   CurrentPreset.VelocityGraphValue = 1;   /*                               */                       
   CurrentPreset.PowerGraphValue = 1;      /*                               */                       
   CurrentPreset.ColDistanceGraphValue = 1;/*                               */                       
   CurrentPreset.AbsDistanceGraphValue = 1;/*                               */                       
   CurrentPreset.ForceGraphValue = 1;      /*                               */                       
   CurrentPreset.FrequencyGraphValue = 1;  /*                               */                       
   CurrentPreset.AmplitudeGraphValue = 1;  /*                               */                       
   CurrentPreset.SetupPresetValue = 1;     /*                               */                       
   CurrentPreset.SeqPresetValue = 1;       /*                               */                       
   CurrentPreset.WeldCount = 0;            /*                               */
   CurrentPreset.TestAmp = TEST_AMP;       /*                               */

   CurrentPreset.PreTrigSwitch = 0;        /* CHOICE structure, so 0=Off    */
   CurrentPreset.EnergyCompFlag = 0;       /* CHOICE structure, so 0=Off    */
   CurrentPreset.SuspectLimitsFlag = 0;    /* CHOICE structure, so 0=Off    */
   CurrentPreset.RejectLimitsFlag = 0;     /* CHOICE structure, so 0=Off    */
   CurrentPreset.CycleAbortFlag = 0;       /* CHOICE structure, so 0=Off    */
   CurrentPreset.GndDetectFlag = 0;        /* CHOICE structure, so 0=Off    */
   CurrentPreset.SusResetRequired = 0;     /* CHOICE structure, so 0=Off    */
   CurrentPreset.RejResetRequiredFlag = 0;     /* CHOICE structure, so 0=Off    */

   CurrentPreset.Verified            = FALSE;
   CurrentPreset.PresetUpdateComplete = TRUE;

   CurrentPreset.HwCnfg = 0;
   //Initialize Write In Fields
   for (x = 0; x < WRITEINLEN-2; x++) {           /* Clear write in fields */
      CurrentPreset.WriteIn1[x] = ' ';
      CurrentPreset.WriteIn2[x] = ' ';
   }
   CurrentPreset.WriteIn2[WRITEINLEN-2] = 0;
   CurrentPreset.WriteIn2[WRITEINLEN-1] = 0;
   CurrentPreset.WriteIn1[WRITEINLEN-2] = 0;
   CurrentPreset.WriteIn1[WRITEINLEN-1] = 0;
   CurrentPreset.EBTime = EB_DEF_TIME;         /* Def value for energy braking   */

   CurrentSetup.ActivePreset = 0;
   CurrentSetup.AdvanceCounters = 1;   /* 1 = all  */
   CurrentSetup.AmpControl = 1;        /* 1 = internal  */
   CurrentSetup.FreqControl = 1;       /* 1 = internal  */
   CurrentSetup.Sequence1Flag = 0;
   CurrentSetup.Sequence2Flag = 0;
   CurrentSetup.Sequence3Flag = 0;
   CurrentSetup.PartContactFlag = 0;
   CurrentSetup.DigPotFlag = FALSE;
   CurrentSetup.DigPot = 0;

   CurrentSetup.WeldsPerPage = 50;
   PrinterBufferReadyFlag = TRUE;            

   CurrentSetup.SecurityLevel = BRANSON;
   CurrentSetup.PwrOutTable[0] = 0;    /* need to remove when calibration working */
   CurrentSetup.PwrOutTable[1] = 167;
   CurrentSetup.PwrOutTable[2] = 333;
   CurrentSetup.PwrOutTable[3] = 500;
   CurrentSetup.PwrOutTable[4] = 667;
   CurrentSetup.PwrOutTable[5] = 833;
   CurrentSetup.PwrOutTable[6] = 1000;
   CurrentSetup.PwrOutTable[7] = 1167;
   CurrentSetup.PwrOutTable[8] = 1333;
   CurrentSetup.PwrOutTable[9] = 1500;
   CurrentSetup.PwrOutTable[10] = 1500;
   
   CurrentPreset.GeneralAlarmLFlag = FALSE;
   CurrentPreset.DigitalFilterFlag = TRUE;
   CurrentPreset.ActClrDistance = ABS_MIN;
   CurrentPreset.ActClrFlag = 0;         /* Choice structure so 0=off    */
   CurrentPreset.MissingPartFlag = 0;
   CurrentPreset.MissingMinFlag = 1; /* Pointer to disable/enable flag    */
   CurrentPreset.MissingMaxFlag = 1; /* Pointer to disable/enable flag    */
   CurrentPreset.MissingPartMin = ABS_MIN; /* 1250 = 0.1250"              */
   CurrentPreset.MissingPartMax = ABS_MIN; /* 1250 = 0.1250"              */
   CurrentPreset.PMCLowLimit = 5;           /* Def % value for PMC Low Limit  */
   CurrentPreset.PMCHighLimit = 5;          /* Def % value for PMC High Limit */
   CurrentPreset.PMCTimeout = 5;            /* Default PMC Timeout                */
   CurrentPreset.PMCCycleCount = 0;
   CurrentPreset.PMCEnabled = FALSE;        /* Power match Curve Disabled*/
   CurrentPreset.PMCPlusBandFlag = TRUE;
   CurrentPreset.PMCMinusBandFlag = TRUE;
   // Initialize PMC data points
   for (x = 0; x < PMCDATAPOINTS; x++) {         
      CurrentPreset.PMCData[x] = 0xFF;
   }
   CurrentSetup.SequenceFlag = FALSE;
   CurrentSetup.TestMultiplier = TESTTIMEx1;   
   CurrentSetup.TimeMultiplier = WELDTIMEx1;
   CurrentSetup.HornDownSpd = 15;
   CurrentSetup.HornDownForce = 500;
   CurrentSetup.AdjustWhileRun = 0;         /* Choice structure so 0=off  */
   CurrentSetup.BeeperAlarm = TRUE;      
   CurrentSetup.BeeperTrigger = TRUE;
   CurrentSetup.BeeperRelease = FALSE;
   CurrentSetup.BeeperError = TRUE;      
   CurrentSetup.CustomAct = FALSE;         /* Choice structure so 0=off  */
   CurrentSetup.SVDelay   = EXT_START_TIMEOUT;
   CurrentSetup.PLCControlMenuFlag = FALSE; /* Remove entry from menu */
   CurrentSetup.PLCControlFlag = FALSE;     /* Now make sure its off  */

   /*VQS LIMITS starts here*/
   CurrentPreset.EnergyMinVQS = ENERGY_MIN;
   CurrentPreset.PeakPowerMinVQS =POWER_MIN;
   CurrentPreset.TotalAbsMinVQS = ABS_MIN;
   CurrentPreset.TotalColMinVQS = COL_MIN;
   CurrentPreset.TotalCycleTimeMinVQS = TIME_MIN;
   CurrentPreset.WeldColMinVQS = COL_MIN;
   CurrentPreset.WeldForceMinVQS = FORCE_MIN;
   CurrentPreset.WeldTimeMinVQS = TIME_MIN;
   CurrentPreset.WeldTimeMaxVQS = TIME_MAX;
   CurrentPreset.EnergyMaxVQS = ENERGY_MAX;
   CurrentPreset.PeakPowerMaxVQS =POWER_MAX;
   CurrentPreset.TotalAbsMaxVQS = MaxStrokeLength;
   CurrentPreset.TotalColMaxVQS = COL_MAX;
   CurrentPreset.TotalCycleTimeMaxVQS = TIME_MAX;
   CurrentPreset.WeldColMaxVQS = COL_MAX;
   CurrentPreset.VQSLimit = 0xffff;
   CurrentPreset.WeldForceMaxVQS = MaxForce;
   CurrentPreset.AmpAMicron = 20;
   CurrentPreset.AmpBMicron = 20;
   }

/**  **  Set user definable I/O back to factory default  **  **/

   SetUserIOToFactoryDefault();   
   
/**  **  Set actuator switches back to factory default  **  **/

   SetActuatorSwitchesToFactoryDefault();

   CurrentPreset.WeldStatusFlag = TRUE;
   CurrentSetup.ExtPresets = FALSE;
   DealWithExtPresetChange();

/**  **  Set printing back to factory defaults  **  **/

   SetPrintingToFactoryDefault();

/**  **  Set USB parameters back to factory defaults  **  **/
   SetUSBToFactoryDefault();
   
/** SBL initialization**/
   InitSBL();

   CurrentSetup.WelderAddrFlag = 1;         /* VARIABLE structure, so 1=Off   */
   CurrentSetup.WelderAddrValue = 100;      /* Default = ID of 100            */

   CurrentSetup.AmpMicronsFlag = FALSE;
   CurrentSetup.AmpMicronsValue = 20;
   CurrentSetup.PeakPowerWattsFlag = FALSE;

   CurrentSetup.HmenuIndex = 0;   
   ColdStartDone = TRUE;

   /*-- Get Date of last saved preset --*/
   LastDatePresetWasSaved();

   /*-- Reset graph data --*/
   //TotalPts = 0;
   WeldCounter = CurrentSetup.WeldsPerPage;

  // SaveCompressedPreset( (PRESET_COMPRESSED *) PRESET_CLDSTRT_START, &CurrentPreset);
   //BattramCompletionStatus = BattramAccess(BBR_WRITE, CONFIG_SECTION, (UINT8 *)&CurrentSetup, BBR800_CONFIG_START, sizeof(CurrentSetup) );
}

extern BOOLEAN NextMenuFlag;

void DoColdStart(void)
/****************************************************************************/
/*                                                                          */
/* Performs a "cold start" by recalling the COLD START preset. It clears    */
/* alarms that can be cleared (those that don't always require a RESET) and */
/* centers the digital pot.                                                 */
/* VERY IMPORTANT: STATE MACHINE MUST BE SUSPENDED WHEN THIS FUNCTION IS    */
/* CALLED.  This is necessary to allow the digital pot position to be       */
/* changed, also prevents unfriendly activities while the cold start is     */
/* going on.                                                                */
/*                                                                          */
/****************************************************************************/
{
   UINT16 x;

   StopStateMachine();            /* Perform cold start only if not welding */
   if(CurrentPreset.PresetUpdateComplete == TRUE)
      WritePreset(CurrentSetup.ActivePreset);   /* Save Current Preset */
   
   /* need to fix to go through psos */

   ColdStartInProcess = TRUE;
   CenterDigPot();
   RecallColdstartPreset(0);
   SetPrintingToFactoryDefault();

   // SetMaxMinValues();      /* This call was after SetDefaultValues.  It was moved because saving */
   // SetDefaultValues();     /* Min/Max values now messes up the currentpreset.                    */

   UpdateCurrentPreset(SAVEPRESETZERO, 0, 0); /* Updates Running Preset */
   UpdateCurrentPreset(SAVECURRENTSETUP, 0, 0);
   
   SetAmpControl();
   SetFreqControl();

   ClearFinalResults();
   ClearWeldData();
   WeldingResults.CycleCount = 0;
   SetupAlarmFlag = FALSE;           /* Clear any leftover setup alarms  */

   /*-----     Clear all setup alarms here   -----*/

   ClearSetupAlarms();
   CountAlarms();
   if(QVGAHwAvail)    /* Add Delay for QVGA */
      tm_wkafter(SECONDS_TO_TICKS(4));
   if (TotalAlarmCount == 0)
   {
      AlarmsReset = TRUE;
      AlarmDetectedFlag = FALSE;
      AlarmOff();
   }

   PresetHasBeenOKed = FALSE;           /* Ensure a check on new start signal*/
   while (DigPotKey);                   /* Wait for pot to center */

   DUPS_Info.WeldStatusFlag = TRUE;     /* Initialize weld status flag*/

   if (DUPS_Info.DUPSFlag)
   {
      DUPS_UploadParamSet (0);   /* Upload factory default Parameter Set */
      DUPS_Wait4CurrPS();
      DUPS_CurrentParamSet.SeekTime = 500;  /* Seek time and seek flag value hard coded*/
      DUPS_CurrentParamSet.WeldRampTime = 80;  /* Seek time and seek flag value hard coded*/
      
      /* During Coldstart, force Memory = On and Timed Seek = Off.*/
      DUPS_Info. DUPSMemFlag =  TRUE;
      DUPS_Info. DUPSSeekFlag = FALSE;
	  DUPS_Info. DUPSMemRstFlag = FALSE;
      
      DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN | DUPS_SWDIPSTOREMEMATWLDEND; /* external amp control */
      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPAUTOSEEK;
      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPCLEARMEMATRST;

      DUPS_QueuedDownloadPS();     /* establish default DUPS Current Parameter Set*/
      CurrentPreset.DUPSPreset = 0;  /* Tell RADIO menu its DUPS Parameter set 0 */
   }

   tm_wkafter( SECONDS_TO_TICKS( 3 ));

   if (!ColdStartFlag)               /* Special test if PowerUpColdStart   */
   {
      MainKeyFlag = TRUE;
      BlankMenuCounter = 1;          /* Prevent Main Menu display */
      SendFakeKeyPress(SetupKey);    /* Display Weld Setup Screen */
   }
   CurrentPreset.PresetUpdateComplete = TRUE;
   CurrentSetup.ActivePreset = 0;
   strcpy(CurrentPreset.PresetID, "Preset0 ");  /* Name it Preset0  */

   for (x = 0; x < WRITEINLEN-2; x++) {                    /* Clear write in fields */
      CurrentPreset.WriteIn1[x] = ' ';
      CurrentPreset.WriteIn2[x] = ' ';
   }
   CurrentPreset.WriteIn2[WRITEINLEN-2] = 0;
   CurrentPreset.WriteIn2[WRITEINLEN-1] = 0;
   CurrentPreset.WriteIn1[WRITEINLEN-2] = 0;
   CurrentPreset.WriteIn1[WRITEINLEN-1] = 0;
    

   /* CheckBattramDefaults();    */       /* See if BBR is initialized & working */
   ColdStartInProcess = FALSE;
   CurrentSetup.BaudRate = BAUD_9600;

   SetupForceStepFlag();
   SetupAmplitudeStepFlag();

   InitSBL();

   ResetStateMachine();
   StartStateMachine();
   NextMenuFlag = TRUE;
}


void CreateColdStart(void)
/****************************************************************************/
/*                                                                          */
/* Performs a "cold start".  This involves:                                 */
/* Reseting parameters to default values, clearing alarms that can be       */
/* cleared (those that don't always require a RESET) and centering digital  */
/* pot.                                                                     */
/*                                                                          */
/* VERY IMPORTANT: STATE MACHINE MUST BE SUSPENDED WHEN THIS FUNCTION IS    */
/* CALLED.  This is necessary to allow the digital pot position to be       */
/* changed, also prevents unfriendly activities while the cold start is     */
/* going on.                                                                */
/*                                                                          */
/* WHEN FINISHED THIS FUNCTION WILL SAVE THE COLD START VALUES IN THE       */
/* COLD START PRESET.  THIS PRESET WILL BE RECALLED WHEN A COLD START IS    */
/* NEEDED BY DoColdStart() above.  This allows specials which would define  */
/* a different set of cold start values.                                    */
/*                                                                          */
/****************************************************************************/
{
   UINT16 x;

   if(CurrentPreset.PresetUpdateComplete == TRUE)
      WritePreset(CurrentSetup.ActivePreset);   /* Save Current Preset */
   
   /* need to fix to go through psos */
   ColdStartInProcess = TRUE;
   CenterDigPot();
   strcpy(MinLimit.PresetID, "DEFAULT");  /*     it will allow restore the values as a factory*/
   strcpy(MaxLimit.PresetID, "DEFAULT");  /*     it will allow restore the values as a factory*/	
   
  
   SetMaxMinValues();      /* This call was after SetDefaultValues.  It was moved because saving */

   strcpy(CurrentPreset.PresetID, "COLD START");                                  /*     it will allow restore the values as a factory*/
   SaveCompressedPreset( (PRESET_COMPRESSED *) PRESET_CLDSTRT_START, &CurrentPreset);   
   SetDefaultValues();     /* Min/Max values now messes up the currentpreset.                    */

   UpdateCurrentPreset(SAVEPRESETZERO, 0, 0); /* Updates Running Preset */
   UpdateCurrentPreset(SAVECURRENTSETUP, 0, 0);
   
   SetAmpControl();
   SetFreqControl();

   ClearFinalResults();
   ClearWeldData();
   WeldingResults.CycleCount = 0;
   SetupAlarmFlag = FALSE;           /* Clear any leftover setup alarms  */

   /*-----     Clear all setup alarms here   -----*/
   ClearSetupAlarms();
   CountAlarms();
   if(QVGAHwAvail)    /* Add Delay for QVGA */
      tm_wkafter(SECONDS_TO_TICKS(4));
   if (TotalAlarmCount == 0)
   {
      AlarmsReset = TRUE;
      AlarmDetectedFlag = FALSE;
      AlarmOff();
   }

   PresetHasBeenOKed = FALSE;           /* Ensure a check on new start signal*/
   while (DigPotKey);                   /* Wait for pot to center */

   DUPS_Info.WeldStatusFlag = TRUE;     /* Initialize weld status flag*/

   if (DUPS_Info.DUPSFlag)
   {
      DUPS_UploadParamSet (0);   /* Upload factory default Parameter Set */
      DUPS_Wait4CurrPS();
      DUPS_CurrentParamSet.SeekTime = 500;  /* Seek time and seek flag value hard coded*/
      DUPS_CurrentParamSet.WeldRampTime = 80;  /* Seek time and seek flag value hard coded*/
      
      /* During Coldstart, force Memory = On and Timed Seek = Off.*/
      DUPS_Info. DUPSMemFlag =  TRUE;
      DUPS_Info. DUPSSeekFlag = FALSE;
	  DUPS_Info. DUPSMemRstFlag = FALSE;
      
      DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN | DUPS_SWDIPSTOREMEMATWLDEND; /* external amp control */
      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPAUTOSEEK;
	  DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPCLEARMEMATRST;
      DUPS_QueuedDownloadPS();     /* establish default DUPS Current Parameter Set*/
      CurrentPreset.DUPSPreset = 0;  /* Tell RADIO menu its DUPS Parameter set 0 */
   }

   tm_wkafter( SECONDS_TO_TICKS( 3 ));

   if (!ColdStartFlag)     /* Special test if PowerUpColdStart   */
   {
      MainKeyFlag = TRUE;
      BlankMenuCounter = 1;          /* Prevent Main Menu display */
      SendFakeKeyPress(SetupKey);      /* Display Weld Setup Screen */
   }
   CurrentPreset.PresetUpdateComplete = TRUE;

   strcpy(CurrentPreset.PresetID, "Preset0 ");  /* Name it Preset0  */

   for (x = 0; x < WRITEINLEN-2; x++) {                    /* Clear write in fields */
      CurrentPreset.WriteIn1[x] = ' ';
      CurrentPreset.WriteIn2[x] = ' ';
   }
   CurrentPreset.WriteIn2[WRITEINLEN-2] = 0;
   CurrentPreset.WriteIn2[WRITEINLEN-1] = 0;
   CurrentPreset.WriteIn1[WRITEINLEN-2] = 0;
   CurrentPreset.WriteIn1[WRITEINLEN-1] = 0;    

   /* CheckBattramDefaults();    */       /* See if BBR is initialized & working */
   ColdStartInProcess = FALSE;
   CurrentSetup.BaudRate = BAUD_9600;

   strcpy(CurrentPreset.PresetID, "COLD START");   /* Name it              */
   SaveCompressedPreset( (PRESET_COMPRESSED *) PRESET_CLDSTRT_START, &CurrentPreset);
}



void SaveCompressedPreset(PRESET_COMPRESSED* CompressPreset, SETUPS_Ver800 *SourcePtr)
/*****************************************************************************/
/*                                                                           */
/* This copies the preset out of the structure pointed to by SourcePtr,      */
/* compresses it and places it into battery backed up ram at the address     */
/* specified by the argument CompressPreset.                                 */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 x;
   UINT32 Temp;
   UINT8 *TempPtr;
   BOOLEAN PMCPresetFlag = FALSE;
      
   Temp = 0;
   Temp |= ((SourcePtr->AbFlag & BIT0) << SHIFT1_ABFLAG);
   Temp |= ((SourcePtr->ABSCutoffFlag & BIT0) << SHIFT1_ABSCUTOFFFLAG);
   Temp |= ((SourcePtr->AbsDistanceGraphAFlag & BIT0) << SHIFT1_ABSDISTANCEGRAPHAFLAG);
   Temp |= ((SourcePtr->AbsDistanceGraphSFlag & BIT0) << SHIFT1_ABSDISTANCEGRAPHSFLAG);
   Temp |= ((SourcePtr->ActClrFlag & BIT0) << SHIFT1_ACTCLRFLAG);
   Temp |= ((SourcePtr->AmplitudeGraphAFlag & BIT0) << SHIFT1_AMPLITUDEGRAPHAFLAG);
   Temp |= ((SourcePtr->AmplitudeGraphSFlag & BIT0) << SHIFT1_AMPLITUDEGRAPHSFLAG);
   Temp |= ((SourcePtr->AmpTrigExtFlag & BIT0) << SHIFT1_AMPTRIGEXTFLAG);
   Temp |= ((SourcePtr->AutoScaleFlag & BIT0) << SHIFT1_AUTOSCALEFLAG);
   Temp |= ((SourcePtr->AutoTrigFlag & BIT0) << SHIFT1_AUTOTRIGFLAG);
   Temp |= ((SourcePtr->ColCutoffFlag & BIT0) << SHIFT1_COLCUTOFFFLAG);
   Temp |= ((SourcePtr->ColDistanceGraphAFlag & BIT0) << SHIFT1_COLDISTANCEGRAPHAFLAG);
   Temp |= ((SourcePtr->ColDistanceGraphSFlag & BIT0) << SHIFT1_COLDISTANCEGRAPHSFLAG);
   Temp |= ((SourcePtr->ControlLimitsFlag & BIT0) << SHIFT1_CONTROLLIMITSFLAG);
   Temp |= ((SourcePtr->CycleAbortFlag & BIT0) << SHIFT1_CYCLEABORTFLAG);
   Temp |= ((SourcePtr->DigitalFilterFlag & BIT0) << SHIFT1_DIGITALFILTERFLAG);
   Temp |= ((SourcePtr->EnergyCompFlag & BIT0) << SHIFT1_ENERGYCOMPFLAG);
   Temp |= ((SourcePtr->FreqOffsetFlag & BIT0) << SHIFT1_FREQOFFSETFLAG);
   Temp |= ((SourcePtr->FrequencyGraphAFlag & BIT0) << SHIFT1_FREQUENCYGRAPHAFLAG);
   Temp |= ((SourcePtr->FrequencyGraphSFlag & BIT0) << SHIFT1_FREQUENCYGRAPHSFLAG);
   Temp |= ((SourcePtr->ForceGraphAFlag & BIT0) << SHIFT1_FORCEGRAPHAFLAG);
   Temp |= ((SourcePtr->ForceGraphSFlag & BIT0) << SHIFT1_FORCEGRAPHSFLAG);
   Temp |= ((SourcePtr->ForceTrigExtFlag & BIT0) << SHIFT1_FORCETRIGEXTFLAG);
   Temp |= ((SourcePtr->GeneralAlarmLFlag & BIT0) << SHIFT1_GENERALALARMLFLAG);
   Temp |= ((SourcePtr->GlobalPrintingFlag & BIT0) << SHIFT1_GLOBALPRINTINGFLAG);
   Temp |= ((SourcePtr->GndDetectFlag & BIT0) << SHIFT1_GNDDETECTFLAG);
   Temp |= ((SourcePtr->HoldTimeFlag & BIT0) << SHIFT1_HOLDTIMEFLAG);
   Temp |= ((SourcePtr->MissingPartFlag & BIT0) << SHIFT1_MISSINGPARTFLAG);
   Temp |= ((SourcePtr->MissingMinFlag & BIT0) << SHIFT1_MISSINGMINFLAG);
   Temp |= ((SourcePtr->MissingMaxFlag & BIT0) << SHIFT1_MISSINGMAXFLAG);
   Temp |= ((SourcePtr->PMCEnabled & BIT0) << SHIFT1_PMCENABLED);
   CompressPreset->Word1 = Temp;
   
   Temp = 0;
   Temp |= ((SourcePtr->PeakPwrCutoffFlag & BIT0) << SHIFT2_PEAKPWRCUTOFFFLAG);
   Temp |= ((SourcePtr->PowerGraphAFlag & BIT0) << SHIFT2_POWERGRAPHAFLAG);
   Temp |= ((SourcePtr->PowerGraphSFlag & BIT0) << SHIFT2_POWERGRAPHSFLAG);
   Temp |= ((SourcePtr->PreTrigDistFlag & BIT0) << SHIFT2_PRETRIGDISTFLAG);
   Temp |= ((SourcePtr->PreTrigFlag & BIT0) << SHIFT2_PRETRIGFLAG);
   Temp |= ((SourcePtr->RejectLimitsFlag & BIT0) << SHIFT2_REJECTLIMITSFLAG);
   Temp |= ((SourcePtr->RejResetRequiredFlag & BIT0) << SHIFT2_REJRESETREQUIREDFLAG);
   Temp |= ((SourcePtr->RTFlag & BIT0) << SHIFT2_RTFLAG);
   Temp |= ((SourcePtr->ScrubTimeFlag & BIT0) << SHIFT2_SCRUBTIMEFLAG);
   Temp |= ((SourcePtr->SeekFunFlag & BIT0) << SHIFT2_SEEKFUNFLAG);
   Temp |= ((SourcePtr->SetPressure & BIT0) << SHIFT2_SETPRESSUREFLAG);
   Temp |= ((SourcePtr->SetupPresetAFlag & BIT0) << SHIFT2_SETUPPRESETAFLAG);
   Temp |= ((SourcePtr->SetupPresetSFlag & BIT0) << SHIFT2_SETUPPRESETSFLAG);
   Temp |= ((SourcePtr->SuspectLimitsFlag & BIT0) << SHIFT2_SUSPECTLIMITSFLAG);
   Temp |= ((SourcePtr->SusResetRequired & BIT0) << SHIFT2_SUSRESETREQUIREDFLAG);
   Temp |= ((SourcePtr->TimingOnTrgFlag & BIT0) << SHIFT2_TIMINGONTRGFLAG);
   Temp |= ((SourcePtr->TriggerDelayFlag & BIT0) << SHIFT2_TRIGGERDELAYFLAG);
   Temp |= ((SourcePtr->VelocityGraphAFlag & BIT0) << SHIFT2_VELOCITYGRAPHAFLAG);
   Temp |= ((SourcePtr->VelocityGraphSFlag & BIT0) << SHIFT2_VELOCITYGRAPHSFLAG);
   Temp |= ((SourcePtr->WeldHistoryAFlag & BIT0) << SHIFT2_WELDHISTORYAFLAG);
   Temp |= ((SourcePtr->WeldHistorySFlag & BIT0) << SHIFT2_WELDHISTORYSFLAG);
   Temp |= ((SourcePtr->WeldStatusFlag & BIT0) << SHIFT2_WELDSTATUSFLAG);
   Temp |= ((SourcePtr->WeldSummaryAFlag & BIT0) << SHIFT2_WELDSUMMARYAFLAG);
   Temp |= ((SourcePtr->WeldSummarySFlag & BIT0) << SHIFT2_WELDSUMMARYSFLAG);
   Temp |= ((SourcePtr->EnergyBraking & BIT0) << SHIFT2_ENERGYBRAKINGFLAG);
   Temp |= ((SourcePtr->ExtTrgDelay & BIT0) << SHIFT2_EXTTRGDELAYFLAG);
   Temp |= ((SourcePtr->PreTrigDelayFlag & BIT0) << SHIFT2_PRETRIGDELAYFLAG);
   Temp |= ((SourcePtr->SeqPresetAFlag & BIT0) << SHIFT2_SEQUENCINGAFLAG);
   Temp |= ((SourcePtr->SeqPresetSFlag & BIT0) << SHIFT2_SEQUENCINGSFLAG);
   Temp |= ((SourcePtr->PMCPlusBandFlag & BIT0) << SHIFT2_PMCPLUSBANDFLAG);
   Temp |= ((SourcePtr->PMCMinusBandFlag & BIT0) << SHIFT2_PMCMINUSBANDFLAG);

   CompressPreset->Word2 = Temp;

   CompressPreset->Word3 = 0;
   CompressPreset->Word4 = 0;

   CompressPreset->AbAmp = (UINT16) SourcePtr->AbAmp;
   CompressPreset->AbDelay = (UINT16)SourcePtr->AbDelay;
   CompressPreset->AbTime = (UINT16)SourcePtr->AbTime;
   CompressPreset->Amp1 = (UINT16)SourcePtr->Amp1;
   CompressPreset->Amp2 = (UINT16)SourcePtr->Amp2;
   CompressPreset->AmpScrubTime = (UINT16)SourcePtr->AmpScrubTime;
   CompressPreset->AmpTrigColValue = (UINT16)SourcePtr->AmpTrigColValue;
   CompressPreset->AmpTrigForceValue = (UINT16)SourcePtr->AmpTrigForceValue;
   CompressPreset->AmpTrigPowerValue = (UINT16)SourcePtr->AmpTrigPowerValue;
   CompressPreset->AmpTrigTimeValue = (UINT16)SourcePtr->AmpTrigTimeValue;
   CompressPreset->ColCutoffDist = (UINT16)SourcePtr->ColCutoffDist;
   CompressPreset->ColDist = (UINT16)SourcePtr->ColDist;
   CompressPreset->ColMLR = (UINT16)SourcePtr->ColMLR;
   CompressPreset->ColMLS = (UINT16)SourcePtr->ColMLS;
   CompressPreset->ColPLR = (UINT16)SourcePtr->ColPLR;
   CompressPreset->ColPLS = (UINT16)SourcePtr->ColPLS;
   CompressPreset->Day = (UINT16)SourcePtr->Day;
   CompressPreset->DownSpdStart = (UINT16)SourcePtr->DownSpdStart;
   CompressPreset->EBTime = (UINT16)SourcePtr->EBTime;
   CompressPreset->Force2 = (UINT16)SourcePtr->Force2;
   CompressPreset->ForceTrigAmpValue = (UINT16)SourcePtr->ForceTrigAmpValue;
   CompressPreset->ForceTrigColValue = (UINT16)SourcePtr->ForceTrigColValue;
   CompressPreset->ForceTrigPowerValue = (UINT16)SourcePtr->ForceTrigPowerValue;
   CompressPreset->ForceTrigTimeValue = (UINT16)SourcePtr->ForceTrigTimeValue;
   CompressPreset->FreqOffset = (UINT16)SourcePtr->FreqOffset;
   CompressPreset->FreqMLR = (UINT16)SourcePtr->FreqMLR;
   CompressPreset->FreqMLS = (UINT16)SourcePtr->FreqMLS;
   CompressPreset->FreqPLR = (UINT16)SourcePtr->FreqPLR;
   CompressPreset->FreqPLS = (UINT16) SourcePtr->FreqPLS;
   CompressPreset->HoldTime = (UINT16) SourcePtr->HoldTime;
   CompressPreset->HoldForce = (UINT16)SourcePtr->HoldForce;
   CompressPreset->Hour = (UINT16)SourcePtr->Hour;
   CompressPreset->MaxTimeout = (UINT16)SourcePtr->MaxTimeout;
   CompressPreset->MinTrigForce = (UINT16)SourcePtr->MinTrigForce;
   CompressPreset->Minute = (UINT16)SourcePtr->Minute;
   CompressPreset->Month = (UINT16)SourcePtr->Month;
   CompressPreset->PeakPwr = (UINT16)SourcePtr->PeakPwr;
   CompressPreset->PeakPwrCutoff = (UINT16)SourcePtr->PeakPwrCutoff;
   CompressPreset->PowerMLR = (UINT16)SourcePtr->PowerMLR;
   CompressPreset->PowerMLS = (UINT16)SourcePtr->PowerMLS;
   CompressPreset->PowerPLR = (UINT16)SourcePtr->PowerPLR;
   CompressPreset->PowerPLS = (UINT16)SourcePtr->PowerPLS;
   CompressPreset->PreTrigAmp = (UINT16)SourcePtr->PreTrigAmp;
   CompressPreset->RejectLimits = (UINT16)SourcePtr->RejectLimits;
   CompressPreset->ScrubTime = (UINT16)SourcePtr->ScrubTime;
   CompressPreset->SetRTComp = (UINT16)SourcePtr->SetRTComp;
   CompressPreset->SuspectLimits = (UINT16)SourcePtr->SuspectLimits;
   CompressPreset->TestAmp = (UINT16)SourcePtr->TestAmp;
   CompressPreset->TimeMLR = (UINT16)SourcePtr->TimeMLR;
   CompressPreset->TimeMLS = (UINT16)SourcePtr->TimeMLS;
   CompressPreset->TimePLR = (UINT16)SourcePtr->TimePLR;
   CompressPreset->TimePLS = (UINT16)SourcePtr->TimePLS;
   CompressPreset->TriggerDelay = (UINT16)SourcePtr->TriggerDelay;
   CompressPreset->TriggerForce = (UINT16)SourcePtr->TriggerForce;
   CompressPreset->WeldForce = (UINT16)SourcePtr->WeldForce;
   CompressPreset->WeldForceMLR = (UINT16)SourcePtr->WeldForceMLR;
   CompressPreset->WeldForceMLS = (UINT16)SourcePtr->WeldForceMLS;
   CompressPreset->WeldForcePLR = (UINT16)SourcePtr->WeldForcePLR;
   CompressPreset->WeldForcePLS = (UINT16)SourcePtr->WeldForcePLS;
   CompressPreset->WeldTime = (UINT16)SourcePtr->WeldTime;
   CompressPreset->XScaleTime = (UINT16)SourcePtr->XScaleTime;
   CompressPreset->Year = (UINT16)SourcePtr->Year;
   CompressPreset->ABSCutoffDist = SourcePtr->ABSCutoffDist;
   CompressPreset->AbsDist = SourcePtr->AbsDist;
   CompressPreset->AbsDistanceGraphValue = SourcePtr->AbsDistanceGraphValue; 
   CompressPreset->AbsMLR = SourcePtr->AbsMLR;
   CompressPreset->AbsMLS = SourcePtr->AbsMLS;
   CompressPreset->AbsPLR = SourcePtr->AbsPLR;
   CompressPreset->AbsPLS = SourcePtr->AbsPLS;
   CompressPreset->ActClrDistance = SourcePtr->ActClrDistance;
   CompressPreset->Amp2Flag = SourcePtr->Amp2Flag;                  
   CompressPreset->AmpTrigAbsValue = SourcePtr->AmpTrigAbsValue;
   CompressPreset->AmpTrigEnerValue = SourcePtr->AmpTrigEnerValue;
   CompressPreset->AmplitudeGraphValue = SourcePtr->AmplitudeGraphValue;
   CompressPreset->ColDistanceGraphValue = SourcePtr->ColDistanceGraphValue;   
   CompressPreset->DUPSPreset = SourcePtr->DUPSPreset;
   CompressPreset->EnergyML = SourcePtr->EnergyML;
   CompressPreset->EnergyPL = SourcePtr->EnergyPL;
   CompressPreset->EnergyMLR = SourcePtr->EnergyMLR;
   CompressPreset->EnergyMLS = SourcePtr->EnergyMLS;
   CompressPreset->EnergyPLR = SourcePtr->EnergyPLR;
   CompressPreset->EnergyPLS = SourcePtr->EnergyPLS;
   CompressPreset->Force2Flag = SourcePtr->Force2Flag;                 
   CompressPreset->ForceGraphValue = SourcePtr->ForceGraphValue; 
   CompressPreset->ForceTrigAbsValue = SourcePtr->ForceTrigAbsValue;
   CompressPreset->ForceTrigEnerValue = SourcePtr->ForceTrigEnerValue;
   CompressPreset->FrequencyGraphValue = SourcePtr->FrequencyGraphValue;
   CompressPreset->GaugePressure = SourcePtr->GaugePressure;
   CompressPreset->HoldFR = SourcePtr->HoldFR;
   CompressPreset->MissingPartMin = SourcePtr->MissingPartMin;
   CompressPreset->MissingPartMax = SourcePtr->MissingPartMax;
   CompressPreset->PowerGraphValue = SourcePtr->PowerGraphValue;     
   for (x=0; x<PRESETLEN; x++) {
      CompressPreset->PresetID[x] = SourcePtr->PresetID[x];
   }
   CompressPreset->PresetUpdateComplete = SourcePtr->PresetUpdateComplete;
   CompressPreset->PreTrigDist = SourcePtr->PreTrigDist;
   CompressPreset->PreTrigDelay = SourcePtr->PreTrigDelay;
   CompressPreset->ReturnRamp = SourcePtr->ReturnRamp;  
   CompressPreset->RTDist = SourcePtr->RTDist;
   CompressPreset->RTRamp = SourcePtr->RTRamp;  
   CompressPreset->SetupPresetValue = SourcePtr->SetupPresetValue; 
   CompressPreset->StartRamp = SourcePtr->StartRamp;
   CompressPreset->StepFR = SourcePtr->StepFR;
   CompressPreset->SuspectLimits = SourcePtr->SuspectLimits;              
   CompressPreset->TrsDistMLR = SourcePtr->TrsDistMLR;
   CompressPreset->TrsDistMLS = SourcePtr->TrsDistMLS;
   CompressPreset->TrsDistPLR = SourcePtr->TrsDistPLR; 
   CompressPreset->TrsDistPLS = SourcePtr->TrsDistPLS;
   CompressPreset->VelocityGraphValue = SourcePtr->VelocityGraphValue; 
// if (PresetHasBeenOKed == TRUE) {
//    CompressPreset->Verified = (CurrentSetup.ControlLevel | (CurrentSetup.Actuator << 8));
// }
// else {
//    CompressPreset->Verified = 0;
// }
   CompressPreset->Verified = SourcePtr->Verified;
   CompressPreset->Version = CurrentVersion;
   CompressPreset->WeldCount = SourcePtr->WeldCount;
   CompressPreset->WeldEnergy = SourcePtr->WeldEnergy;
   CompressPreset->WeldFR = SourcePtr->WeldFR;
   CompressPreset->WeldHistoryValue = SourcePtr->WeldHistoryValue;
   CompressPreset->WeldMode = SourcePtr->WeldMode;
   CompressPreset->WeldSummaryValue = SourcePtr->WeldSummaryValue;
   CompressPreset->HwCnfg = SourcePtr->HwCnfg;
   for (x=0; x<WRITEINLEN; x++) {
      CompressPreset->ZWriteIn1[x] = SourcePtr->WriteIn1[x];
      CompressPreset->ZWriteIn2[x] = SourcePtr->WriteIn2[x];
   }
   CompressPreset->SBLMinFreqLim = SourcePtr->SBLMinFreqLim;
   CompressPreset->SBLMaxFreqLim = SourcePtr->SBLMaxFreqLim;
   CompressPreset->SBLMinFreq = SourcePtr->SBLMinFreq;
   CompressPreset->SBLMaxFreq = SourcePtr->SBLMaxFreq;
   CompressPreset->SBLFreqFlags = SourcePtr->SBLFreqFlags;
   CompressPreset->PMCLowLimit = (UINT16)SourcePtr->PMCLowLimit;
   CompressPreset->PMCHighLimit = (UINT16)SourcePtr->PMCHighLimit;
   CompressPreset->PMCTimeout = (UINT16)SourcePtr->PMCTimeout;
   CompressPreset->PMCCycleCount = SourcePtr->PMCCycleCount;
   CompressPreset->EnergyMinVQS = (UINT32)SourcePtr->EnergyMinVQS;
   CompressPreset->PeakPowerMinVQS = (UINT32)SourcePtr->PeakPowerMinVQS;
   CompressPreset->TotalAbsMinVQS = (UINT32)SourcePtr->TotalAbsMinVQS;
   CompressPreset->TotalColMinVQS = (UINT32)SourcePtr->TotalColMinVQS;
   CompressPreset->TotalCycleTimeMinVQS = (UINT32)SourcePtr->TotalCycleTimeMinVQS;
   CompressPreset->WeldColMinVQS = (UINT32)SourcePtr->WeldColMinVQS;
   CompressPreset->WeldForceMinVQS = (UINT32)SourcePtr->WeldForceMinVQS;
   CompressPreset->WeldTimeMinVQS = (UINT32)SourcePtr->WeldTimeMinVQS;

   CompressPreset->EnergyMaxVQS = (UINT32)SourcePtr->EnergyMaxVQS;
   CompressPreset->PeakPowerMaxVQS = (UINT32)SourcePtr->PeakPowerMaxVQS;
   CompressPreset->TotalAbsMaxVQS = (UINT32)SourcePtr->TotalAbsMaxVQS;
   CompressPreset->TotalColMaxVQS = (UINT32)SourcePtr->TotalColMaxVQS;
   CompressPreset->TotalCycleTimeMaxVQS = (UINT32)SourcePtr->TotalCycleTimeMaxVQS;
   CompressPreset->WeldColMaxVQS = (UINT32)SourcePtr->WeldColMaxVQS;
   CompressPreset->WeldForceMaxVQS = (UINT32)SourcePtr->WeldForceMaxVQS;
   CompressPreset->WeldTimeMaxVQS = (UINT32)SourcePtr->WeldTimeMaxVQS;
   CompressPreset->VQSLimit = (UINT16)SourcePtr->VQSLimit;
   CompressPreset->AmpAMicron = (UINT16)SourcePtr->AmpAMicron;
   CompressPreset->AmpBMicron = (UINT16)SourcePtr->AmpBMicron;

   /*Save PMC data into Preset17-32*/
   for(x = 1; x <= MAX_PRESETS; x++ ) {
      if (CompressPreset == (PRESET_COMPRESSED *)PresetAddress[x])
      {
         PMCPresetFlag = TRUE;
         break;
      }
   }
   if (PMCPresetFlag)
   {
      TempPtr = (UINT8 *)PresetAddress[x + MAX_PRESETS];
      memcpy(TempPtr, (UINT8 *) &CurrentPreset.PMCData, PMCDATAPOINTS);   
   }
   
}       



void RecallCompressedPreset(PRESET_COMPRESSED* CompressPreset)
/*****************************************************************************/
/*                                                                           */
/* This brings the preset out of the battery backed up ram, uncompresses it  */
/* and puts it into the  current preset.                                     */
/*                                                                           */
/*****************************************************************************/
{
   UINT16 x;
   BOOLEAN PMCPresetFlag = FALSE;
   UINT8 *TempPtr;
   
   CurrentPreset.AbFlag = ((CompressPreset->Word1 >> SHIFT1_ABFLAG) & BIT0);
   CurrentPreset.ABSCutoffFlag = ((CompressPreset->Word1 >> SHIFT1_ABSCUTOFFFLAG) & BIT0);
   CurrentPreset.AbsDistanceGraphAFlag = ((CompressPreset->Word1 >> SHIFT1_ABSDISTANCEGRAPHAFLAG) & BIT0);
   CurrentPreset.AbsDistanceGraphSFlag = ((CompressPreset->Word1 >> SHIFT1_ABSDISTANCEGRAPHSFLAG) & BIT0);
   CurrentPreset.ActClrFlag = ((CompressPreset->Word1 >> SHIFT1_ACTCLRFLAG) & BIT0);
   CurrentPreset.AmplitudeGraphAFlag = ((CompressPreset->Word1 >> SHIFT1_AMPLITUDEGRAPHAFLAG) & BIT0);
   CurrentPreset.AmplitudeGraphSFlag = ((CompressPreset->Word1 >> SHIFT1_AMPLITUDEGRAPHSFLAG) & BIT0);
   CurrentPreset.AmpTrigExtFlag = ((CompressPreset->Word1 >> SHIFT1_AMPTRIGEXTFLAG) & BIT0);
   CurrentPreset.AutoScaleFlag = ((CompressPreset->Word1 >> SHIFT1_AUTOSCALEFLAG) & BIT0);
   CurrentPreset.AutoTrigFlag = ((CompressPreset->Word1 >> SHIFT1_AUTOTRIGFLAG) & BIT0);
   CurrentPreset.ColCutoffFlag = ((CompressPreset->Word1 >> SHIFT1_COLCUTOFFFLAG) & BIT0);
   CurrentPreset.ColDistanceGraphAFlag = ((CompressPreset->Word1 >> SHIFT1_COLDISTANCEGRAPHAFLAG) & BIT0);
   CurrentPreset.ColDistanceGraphSFlag = ((CompressPreset->Word1 >> SHIFT1_COLDISTANCEGRAPHSFLAG) & BIT0);
   CurrentPreset.ControlLimitsFlag = ((CompressPreset->Word1 >> SHIFT1_CONTROLLIMITSFLAG) & BIT0);
   CurrentPreset.CycleAbortFlag = ((CompressPreset->Word1 >> SHIFT1_CYCLEABORTFLAG) & BIT0);
   CurrentPreset.DigitalFilterFlag = ((CompressPreset->Word1 >> SHIFT1_DIGITALFILTERFLAG) & BIT0);
   CurrentPreset.EnergyCompFlag = ((CompressPreset->Word1 >> SHIFT1_ENERGYCOMPFLAG) & BIT0);
   CurrentPreset.FreqOffsetFlag = ((CompressPreset->Word1 >> SHIFT1_FREQOFFSETFLAG) & BIT0);
   CurrentPreset.FrequencyGraphAFlag = ((CompressPreset->Word1 >> SHIFT1_FREQUENCYGRAPHAFLAG) & BIT0);
   CurrentPreset.FrequencyGraphSFlag = ((CompressPreset->Word1 >> SHIFT1_FREQUENCYGRAPHSFLAG) & BIT0);
   CurrentPreset.ForceGraphAFlag = ((CompressPreset->Word1 >> SHIFT1_FORCEGRAPHAFLAG) & BIT0);
   CurrentPreset.ForceGraphSFlag = ((CompressPreset->Word1 >> SHIFT1_FORCEGRAPHSFLAG) & BIT0);
   CurrentPreset.ForceTrigExtFlag = ((CompressPreset->Word1 >> SHIFT1_FORCETRIGEXTFLAG) & BIT0);
   CurrentPreset.GeneralAlarmLFlag = ((CompressPreset->Word1 >> SHIFT1_GENERALALARMLFLAG) & BIT0);
   CurrentPreset.GlobalPrintingFlag = ((CompressPreset->Word1 >> SHIFT1_GLOBALPRINTINGFLAG) & BIT0);
   CurrentPreset.GndDetectFlag = ((CompressPreset->Word1 >> SHIFT1_GNDDETECTFLAG) & BIT0);
   CurrentPreset.HoldTimeFlag = ((CompressPreset->Word1 >> SHIFT1_HOLDTIMEFLAG) & BIT0);
   CurrentPreset.MissingPartFlag = ((CompressPreset->Word1 >> SHIFT1_MISSINGPARTFLAG) & BIT0);
   CurrentPreset.MissingMinFlag = ((CompressPreset->Word1 >> SHIFT1_MISSINGMINFLAG) & BIT0);
   CurrentPreset.MissingMaxFlag = ((CompressPreset->Word1 >> SHIFT1_MISSINGMAXFLAG) & BIT0);
   CurrentPreset.PMCEnabled = ((CompressPreset->Word1 >> SHIFT1_PMCENABLED) & BIT0);

   CurrentPreset.PeakPwrCutoffFlag = ((CompressPreset->Word2 >> SHIFT2_PEAKPWRCUTOFFFLAG) & BIT0);
   CurrentPreset.PowerGraphAFlag = ((CompressPreset->Word2 >> SHIFT2_POWERGRAPHAFLAG) & BIT0);
   CurrentPreset.PowerGraphSFlag = ((CompressPreset->Word2 >> SHIFT2_POWERGRAPHSFLAG) & BIT0);
   CurrentPreset.PreTrigDistFlag = ((CompressPreset->Word2 >> SHIFT2_PRETRIGDISTFLAG) & BIT0);
   CurrentPreset.PreTrigFlag = ((CompressPreset->Word2 >> SHIFT2_PRETRIGFLAG) & BIT0);
   CurrentPreset.RejectLimitsFlag = ((CompressPreset->Word2 >> SHIFT2_REJECTLIMITSFLAG) & BIT0);
   CurrentPreset.RejResetRequiredFlag = ((CompressPreset->Word2 >> SHIFT2_REJRESETREQUIREDFLAG) & BIT0);
   CurrentPreset.RTFlag = ((CompressPreset->Word2 >> SHIFT2_RTFLAG) & BIT0);
   CurrentPreset.ScrubTimeFlag = ((CompressPreset->Word2 >> SHIFT2_SCRUBTIMEFLAG) & BIT0);
   CurrentPreset.SeekFunFlag = ((CompressPreset->Word2 >> SHIFT2_SEEKFUNFLAG) & BIT0);
   CurrentPreset.SetPressure = ((CompressPreset->Word2 >> SHIFT2_SETPRESSUREFLAG) & BIT0);
   CurrentPreset.SetupPresetAFlag = ((CompressPreset->Word2 >> SHIFT2_SETUPPRESETAFLAG) & BIT0);
   CurrentPreset.SetupPresetSFlag = ((CompressPreset->Word2 >> SHIFT2_SETUPPRESETSFLAG) & BIT0);
   CurrentPreset.SuspectLimitsFlag = ((CompressPreset->Word2 >> SHIFT2_SUSPECTLIMITSFLAG) & BIT0);
   CurrentPreset.SusResetRequired = ((CompressPreset->Word2 >> SHIFT2_SUSRESETREQUIREDFLAG) & BIT0);
   CurrentPreset.TimingOnTrgFlag = ((CompressPreset->Word2 >> SHIFT2_TIMINGONTRGFLAG) & BIT0);
   CurrentPreset.TriggerDelayFlag = ((CompressPreset->Word2 >> SHIFT2_TRIGGERDELAYFLAG) & BIT0);
   CurrentPreset.VelocityGraphAFlag = ((CompressPreset->Word2 >> SHIFT2_VELOCITYGRAPHAFLAG) & BIT0);
   CurrentPreset.VelocityGraphSFlag = ((CompressPreset->Word2 >> SHIFT2_VELOCITYGRAPHSFLAG) & BIT0);
   CurrentPreset.WeldHistoryAFlag = ((CompressPreset->Word2 >> SHIFT2_WELDHISTORYAFLAG) & BIT0);
   CurrentPreset.WeldHistorySFlag = ((CompressPreset->Word2 >> SHIFT2_WELDHISTORYSFLAG) & BIT0);
   CurrentPreset.WeldStatusFlag = ((CompressPreset->Word2 >> SHIFT2_WELDSTATUSFLAG) & BIT0);
   CurrentPreset.WeldSummaryAFlag = ((CompressPreset->Word2 >> SHIFT2_WELDSUMMARYAFLAG) & BIT0);
   CurrentPreset.WeldSummarySFlag = ((CompressPreset->Word2 >> SHIFT2_WELDSUMMARYSFLAG) & BIT0);
   CurrentPreset.EnergyBraking = ((CompressPreset->Word2 >> SHIFT2_ENERGYBRAKINGFLAG) & BIT0);
   CurrentPreset.ExtTrgDelay = ((CompressPreset->Word2 >> SHIFT2_EXTTRGDELAYFLAG) & BIT0);
   CurrentPreset.PreTrigDelayFlag = ((CompressPreset->Word2 >> SHIFT2_PRETRIGDELAYFLAG) & BIT0);
   CurrentPreset.SeqPresetAFlag = ((CompressPreset->Word2 >> SHIFT2_SEQUENCINGAFLAG) & BIT0);
   CurrentPreset.SeqPresetSFlag = ((CompressPreset->Word2 >> SHIFT2_SEQUENCINGSFLAG) & BIT0);
   CurrentPreset.PMCPlusBandFlag = ((CompressPreset->Word2 >> SHIFT2_PMCPLUSBANDFLAG) & BIT0);
   CurrentPreset.PMCMinusBandFlag = ((CompressPreset->Word2 >> SHIFT2_PMCMINUSBANDFLAG) & BIT0);


   CurrentPreset.AbAmp = (UINT32) CompressPreset->AbAmp;
   CurrentPreset.AbDelay = (UINT32)CompressPreset->AbDelay;
   CurrentPreset.AbTime = (UINT32) CompressPreset->AbTime;
   CurrentPreset.Amp1 = (UINT32) CompressPreset->Amp1;
   CurrentPreset.Amp2 = (UINT32) CompressPreset->Amp2;
   CurrentPreset.AmpScrubTime = (SINT32) CompressPreset->AmpScrubTime;
   CurrentPreset.AmpTrigColValue = (UINT32)CompressPreset->AmpTrigColValue;
   CurrentPreset.AmpTrigForceValue = (UINT32)CompressPreset->AmpTrigForceValue;
   CurrentPreset.AmpTrigPowerValue = (UINT32) CompressPreset->AmpTrigPowerValue;
   CurrentPreset.AmpTrigTimeValue = (UINT32) CompressPreset->AmpTrigTimeValue;
   CurrentPreset.ColCutoffDist = (UINT32) CompressPreset->ColCutoffDist;
   CurrentPreset.ColDist = (UINT32) CompressPreset->ColDist;
   CurrentPreset.ColMLR = (UINT32) CompressPreset->ColMLR;
   CurrentPreset.ColMLS = (UINT32) CompressPreset->ColMLS;
   CurrentPreset.ColPLR = (UINT32) CompressPreset->ColPLR;
   CurrentPreset.ColPLS = (UINT32) CompressPreset->ColPLS;
   CurrentPreset.Day = (UINT32) CompressPreset->Day;
   CurrentPreset.DownSpdStart = (UINT32) CompressPreset->DownSpdStart;
   CurrentPreset.EBTime = (UINT32) CompressPreset->EBTime;
   CurrentPreset.Force2 = (UINT32) CompressPreset->Force2;
   CurrentPreset.ForceTrigAmpValue = (UINT32) CompressPreset->ForceTrigAmpValue;
   CurrentPreset.ForceTrigColValue = (UINT32) CompressPreset->ForceTrigColValue;
   CurrentPreset.ForceTrigPowerValue = (UINT32) CompressPreset->ForceTrigPowerValue;
   CurrentPreset.ForceTrigTimeValue = (UINT32) CompressPreset->ForceTrigTimeValue ;
   CurrentPreset.FreqOffset = (UINT32) CompressPreset->FreqOffset;
   CurrentPreset.FreqMLR = (UINT32) CompressPreset->FreqMLR;
   CurrentPreset.FreqMLS = (UINT32) CompressPreset->FreqMLS;
   CurrentPreset.FreqPLR = (UINT32) CompressPreset->FreqPLR;
   CurrentPreset.FreqPLS = (UINT32) CompressPreset->FreqPLS ;
   CurrentPreset.HoldTime = (UINT32) CompressPreset->HoldTime;
   CurrentPreset.HoldForce = (UINT32) CompressPreset->HoldForce;
   CurrentPreset.Hour = (UINT32) CompressPreset->Hour;
   CurrentPreset.MaxTimeout = (UINT32) CompressPreset->MaxTimeout;
   CurrentPreset.MinTrigForce = (UINT32) CompressPreset->MinTrigForce;
   CurrentPreset.Minute = (UINT32) CompressPreset->Minute;
   CurrentPreset.Month = (UINT32) CompressPreset->Month;
   CurrentPreset.PeakPwr = (UINT32) CompressPreset->PeakPwr;
   CurrentPreset.PeakPwrCutoff = (UINT32) CompressPreset->PeakPwrCutoff;
   CurrentPreset.PowerMLR = (UINT32) CompressPreset->PowerMLR;
   CurrentPreset.PowerMLS = (UINT32) CompressPreset->PowerMLS;
   CurrentPreset.PowerPLR = (UINT32) CompressPreset->PowerPLR;
   CurrentPreset.PowerPLS = (UINT32) CompressPreset->PowerPLS;
   CurrentPreset.PreTrigAmp = (UINT32) CompressPreset->PreTrigAmp;
   CurrentPreset.RejectLimits = (UINT32) CompressPreset->RejectLimits;
   CurrentPreset.ScrubTime = (UINT32) CompressPreset->ScrubTime;
   CurrentPreset.SetRTComp = (UINT32) CompressPreset->SetRTComp;
   CurrentPreset.SuspectLimits = (UINT32) CompressPreset->SuspectLimits;
   CurrentPreset.TestAmp = (UINT32) CompressPreset->TestAmp;
   CurrentPreset.TimeMLR = (UINT32) CompressPreset->TimeMLR;
   CurrentPreset.TimeMLS = (UINT32) CompressPreset->TimeMLS;
   CurrentPreset.TimePLR = (UINT32) CompressPreset->TimePLR;
   CurrentPreset.TimePLS = (UINT32) CompressPreset->TimePLS;
   CurrentPreset.TriggerDelay = (UINT32) CompressPreset->TriggerDelay;
   CurrentPreset.TriggerForce = (UINT32) CompressPreset->TriggerForce;
   CurrentPreset.WeldForce = (UINT32) CompressPreset->WeldForce;
   CurrentPreset.WeldForceMLR = (UINT32) CompressPreset->WeldForceMLR;
   CurrentPreset.WeldForceMLS = (UINT32) CompressPreset->WeldForceMLS;
   CurrentPreset.WeldForcePLR = (UINT32) CompressPreset->WeldForcePLR;
   CurrentPreset.WeldForcePLS = (UINT32) CompressPreset->WeldForcePLS;
   CurrentPreset.WeldTime = (UINT32) CompressPreset->WeldTime;
   CurrentPreset.XScaleTime = (UINT32)CompressPreset->XScaleTime;
   CurrentPreset.Year = (UINT32) CompressPreset->Year; 
   CurrentPreset.ABSCutoffDist = CompressPreset->ABSCutoffDist;
   CurrentPreset.AbsDist = CompressPreset->AbsDist;
   CurrentPreset.AbsDistanceGraphValue = CompressPreset->AbsDistanceGraphValue; 
   CurrentPreset.AbsMLR = CompressPreset->AbsMLR;
   CurrentPreset.AbsMLS = CompressPreset->AbsMLS;
   CurrentPreset.AbsPLR = CompressPreset->AbsPLR;
   CurrentPreset.AbsPLS = CompressPreset->AbsPLS;
   CurrentPreset.ActClrDistance = CompressPreset->ActClrDistance;
   CurrentPreset.Amp2Flag = CompressPreset->Amp2Flag;                  
   CurrentPreset.AmpTrigAbsValue = CompressPreset->AmpTrigAbsValue;
   CurrentPreset.AmpTrigEnerValue = CompressPreset->AmpTrigEnerValue;
   CurrentPreset.AmplitudeGraphValue = CompressPreset->AmplitudeGraphValue;
   CurrentPreset.ColDistanceGraphValue = CompressPreset->ColDistanceGraphValue;   
   CurrentPreset.DUPSPreset = CompressPreset->DUPSPreset;
   CurrentPreset.EnergyML = CompressPreset->EnergyML;
   CurrentPreset.EnergyPL = CompressPreset->EnergyPL;
   CurrentPreset.EnergyMLR = CompressPreset->EnergyMLR;
   CurrentPreset.EnergyMLS = CompressPreset->EnergyMLS;
   CurrentPreset.EnergyPLR = CompressPreset->EnergyPLR;
   CurrentPreset.EnergyPLS = CompressPreset->EnergyPLS;
   CurrentPreset.Force2Flag = CompressPreset->Force2Flag;                 
   CurrentPreset.ForceGraphValue = CompressPreset->ForceGraphValue; 
   CurrentPreset.ForceTrigAbsValue = CompressPreset->ForceTrigAbsValue;
   CurrentPreset.ForceTrigEnerValue = CompressPreset->ForceTrigEnerValue;
   CurrentPreset.FrequencyGraphValue = CompressPreset->FrequencyGraphValue;
   CurrentPreset.GaugePressure = CompressPreset->GaugePressure;
   CurrentPreset.HoldFR = CompressPreset->HoldFR;
   CurrentPreset.MissingPartMin = CompressPreset->MissingPartMin;
   CurrentPreset.MissingPartMax = CompressPreset->MissingPartMax;
   CurrentPreset.PowerGraphValue = CompressPreset->PowerGraphValue;     
   for (x=0; x<PRESETLEN; x++) {
      CurrentPreset.PresetID[x] = CompressPreset->PresetID[x];
   }
   CurrentPreset.PresetUpdateComplete = CompressPreset->PresetUpdateComplete;
   CurrentPreset.PreTrigDist = CompressPreset->PreTrigDist;
   CurrentPreset.PreTrigDelay = CompressPreset->PreTrigDelay;
   CurrentPreset.ReturnRamp = CompressPreset->ReturnRamp;  
   CurrentPreset.RTDist = CompressPreset->RTDist;
   CurrentPreset.RTRamp = CompressPreset->RTRamp;  
   CurrentPreset.SetupPresetValue = CompressPreset->SetupPresetValue; 
   CurrentPreset.StartRamp = CompressPreset->StartRamp;
   CurrentPreset.StepFR = CompressPreset->StepFR;
   CurrentPreset.SuspectLimits = CompressPreset->SuspectLimits;              
   CurrentPreset.TrsDistMLR = CompressPreset->TrsDistMLR;
   CurrentPreset.TrsDistMLS = CompressPreset->TrsDistMLS;
   CurrentPreset.TrsDistPLR = CompressPreset->TrsDistPLR; 
   CurrentPreset.TrsDistPLS = CompressPreset->TrsDistPLS;
   CurrentPreset.VelocityGraphValue = CompressPreset->VelocityGraphValue; 
   CurrentPreset.Verified = CompressPreset->Verified;
   CurrentPreset.WeldCount = CompressPreset->WeldCount;
   CurrentPreset.WeldEnergy = CompressPreset->WeldEnergy;
   CurrentPreset.WeldFR = CompressPreset->WeldFR;
   CurrentPreset.WeldHistoryValue = CompressPreset->WeldHistoryValue;
   CurrentPreset.WeldMode = CompressPreset->WeldMode;
   CurrentPreset.WeldSummaryValue = CompressPreset->WeldSummaryValue;
   CurrentPreset.HwCnfg = CompressPreset->HwCnfg;
   for (x=0; x<WRITEINLEN; x++) {
      CurrentPreset.WriteIn1[x] = CompressPreset->ZWriteIn1[x];
      CurrentPreset.WriteIn2[x] = CompressPreset->ZWriteIn2[x];
   }

   /* Terminate strings with NULL */
   CurrentPreset.PresetID[PRESETLEN-1]  = 0; /*HSan   Update to show 11 characters on the VGA Screen.*/
  
   CurrentPreset.WriteIn1[WRITEINLEN-2] = 0;
   CurrentPreset.WriteIn2[WRITEINLEN-2] = 0;
//   if (CompressPreset->Version !=  CurrentVersion)  {
//      RecordSetupAlarm(SE268);
//      RecordErrorCode(ERRORCODE7_SE268);
//   }
   CurrentPreset.SBLMinFreqLim = CompressPreset->SBLMinFreqLim;
   CurrentPreset.SBLMaxFreqLim = CompressPreset->SBLMaxFreqLim;
   CurrentPreset.SBLMinFreq = CompressPreset->SBLMinFreq;
   CurrentPreset.SBLMaxFreq = CompressPreset->SBLMaxFreq;
   CurrentPreset.SBLFreqFlags = CompressPreset->SBLFreqFlags;
   CurrentPreset.PMCTimeout = (UINT32)CompressPreset->PMCTimeout;
   CurrentPreset.PMCLowLimit = (UINT32)CompressPreset->PMCLowLimit;
   CurrentPreset.PMCHighLimit = (UINT32)CompressPreset->PMCHighLimit;
   CurrentPreset.PMCCycleCount = CompressPreset->PMCCycleCount;

     CurrentPreset.EnergyMaxVQS = (UINT32)CompressPreset->EnergyMaxVQS ;
     CurrentPreset.PeakPowerMaxVQS = (UINT32)CompressPreset->PeakPowerMaxVQS ;
     CurrentPreset.TotalAbsMaxVQS = (UINT32)CompressPreset->TotalAbsMaxVQS ;
     CurrentPreset.TotalColMaxVQS = (UINT32)CompressPreset->TotalColMaxVQS ;
     CurrentPreset.TotalCycleTimeMaxVQS = (UINT32)CompressPreset->TotalCycleTimeMaxVQS ;
     CurrentPreset.WeldColMaxVQS = (UINT32)CompressPreset->WeldColMaxVQS ;
     CurrentPreset.WeldForceMaxVQS = (UINT32)CompressPreset->WeldForceMaxVQS ;
     CurrentPreset.WeldTimeMaxVQS = (UINT32)CompressPreset->WeldTimeMaxVQS ;

     CurrentPreset.EnergyMinVQS = (UINT32)CompressPreset->EnergyMinVQS ;
     CurrentPreset.PeakPowerMinVQS = (UINT32)CompressPreset->PeakPowerMinVQS ;
     CurrentPreset.TotalAbsMinVQS = (UINT32)CompressPreset->TotalAbsMinVQS ;
     CurrentPreset.TotalColMinVQS = (UINT32)CompressPreset->TotalColMinVQS ;
     CurrentPreset.TotalCycleTimeMinVQS = (UINT32)CompressPreset->TotalCycleTimeMinVQS ;
     CurrentPreset.WeldColMinVQS = (UINT32)CompressPreset->WeldColMinVQS ;
     CurrentPreset.WeldForceMinVQS = (UINT32)CompressPreset->WeldForceMinVQS ;
     CurrentPreset.WeldTimeMinVQS = (UINT32)CompressPreset->WeldTimeMinVQS ;
     CurrentPreset.VQSLimit = (UINT16) CompressPreset->VQSLimit;
     CurrentPreset.AmpAMicron = (UINT32) CompressPreset->AmpAMicron;
     CurrentPreset.AmpBMicron = (UINT32) CompressPreset->AmpBMicron;
   
   
   // for menus - prepare flags for pretrigger stuff
   SetupPretriggerFlags();
   
   SetupAmplitudeStepFlag();
   SetupForceStepFlag();
   /*Populate PMC data into current preset*/
   for(x = 1; x <= MAX_PRESETS; x++ ) {
      if (CompressPreset == (PRESET_COMPRESSED *)PresetAddress[x])
      {
         PMCPresetFlag = TRUE;
         break;
      }
   }
   if (!CompressPreset->PMCCycleCount || !PMCPresetFlag)
   {
      for (x = 0; x < PMCDATAPOINTS; x++) {         
         CurrentPreset.PMCData[x] = 0xFF;
      }
   }
   else
   {
      TempPtr = (UINT8 *)PresetAddress[x + MAX_PRESETS];
      memcpy((UINT8 *) &CurrentPreset.PMCData, TempPtr, PMCDATAPOINTS);   
   }
}

void SetupPretriggerFlags(void)
{
// strange, but true: PreTrigFlag   PreTrigDistFlag  PreTrigDelayFlag
// no pretrigger        FALSE             TRUE             TRUE
// auto pretrigger      TRUE              TRUE             TRUE
// distance pretrigger  TRUE              FALSE            TRUE
// time pretrigger      TRUE              TRUE             FALSE

   FlagPretriggerOff = CurrentPreset.PreTrigFlag ? FALSE : TRUE;
   FlagPretriggerAmpl = FlagPretriggerOff ? FALSE : TRUE;
   /* Flag is used for pretrigger amplitude, if enabled and internally controlled */
   FlagPretriggerAmpl = (FlagPretriggerAmpl && CurrentSetup.AmpControl) ? TRUE : FALSE;
   FlagPretriggerAuto = (CurrentPreset.PreTrigFlag && CurrentPreset.PreTrigDistFlag &&
                         CurrentPreset.PreTrigDelayFlag) ? TRUE : FALSE;
   FlagPretriggerTime = CurrentPreset.PreTrigDelayFlag ? FALSE : TRUE;
   FlagPretriggerDist = CurrentPreset.PreTrigDistFlag ? FALSE : TRUE;
}

void SetUserIOToFactoryDefault(void)
/****************************************************************************/
/*                                                                          */
/*  This function will set the user definable I/O back to the factory       */
/*  defaults.                                                               */
/*                                                                          */
/****************************************************************************/
{
   UINT32 BattramStatus;

   CurrentSetup.J3_32In  = INPUT_PRESET1;      // Select preset 1
   CurrentSetup.J3_32Ptr = GetInputPtr(INPUT_PRESET1);
   CurrentSetup.J3_33In  = INPUT_PRESET2;      // Select Preset 2
   CurrentSetup.J3_33Ptr = GetInputPtr(INPUT_PRESET2);
   CurrentSetup.J3_19In  = INPUT_PRESET3;      // Select Preset 3
   CurrentSetup.J3_19Ptr = GetInputPtr(INPUT_PRESET3);
   CurrentSetup.J3_17In  = INPUT_PRESET4;      // Select Preset 4
   CurrentSetup.J3_17Ptr = GetInputPtr(INPUT_PRESET4);
   CurrentSetup.J3_31In  = INPUT_DISP_LOCK;    // Display Lock.
   CurrentSetup.J3_31Ptr = GetInputPtr(INPUT_DISP_LOCK);
   CurrentSetup.J3_1In   = INPUT_EXT_TRIGGER;   // Ext Trigger.
   CurrentSetup.J3_1Ptr  = GetInputPtr(INPUT_EXT_TRIGGER);
   CurrentSetup.J3_36Out = OUTPUT_DISABLED;     //  Disable outputs by default
   CurrentSetup.J3_8Out  = OUTPUT_DISABLED;     //  Disable outputs by default
   CurrentSetup.J3_22Out = OUTPUT_DISABLED;     //  Disable outputs by default
   UserCfgOutputOn(OUTPUT_DISABLED);            /* Write 24 volts to pins */
   CurrentSetup.UserInLogic = FALSE;
   CurrentSetup.SVDelay     = EXT_START_TIMEOUT;//  External Start Delay

/* Store CurrentSetup Parameter Change from DRAM to BATTRAM */
   BattramStatus = BattramAccess(BBR_WRITE, CONFIG_SECTION,(UINT8 *)&CurrentSetup, BBR800_CONFIG_START, sizeof(CurrentSetup));

}


void SetActuatorSwitchesToFactoryDefault(void)
/****************************************************************************/
/*                                                                          */
/*  This function will set the actuator switches back to the factory        */
/*  default value.                                                          */
/*                                                                          */
/****************************************************************************/
{
   CurrentSetup.GndDetLogicCustom = TRUE;            /*Custom Menu Defaults.*/
   CurrentSetup.ULSLogicCustom = TRUE;
}



void SetPrintingToFactoryDefault(void)
/****************************************************************************/
/*                                                                          */
/*  This function will turn off all print on sample and print on alarm      */
/*  functions.  This is the same as cold start, except only printing is     */
/*  affected.                                                               */
/*                                                                          */
/****************************************************************************/
{
/****    ****   Internal presets   ****    ****/

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

   CurrentPreset.SetupPresetSFlag    = TRUE;
   CurrentPreset.WeldHistorySFlag    = TRUE;
   CurrentPreset.WeldSummarySFlag    = TRUE;
   CurrentPreset.PowerGraphSFlag     = TRUE;
   CurrentPreset.AmplitudeGraphSFlag = TRUE;
   CurrentPreset.FrequencyGraphSFlag = TRUE;
   CurrentPreset.ColDistanceGraphSFlag  = TRUE;
   CurrentPreset.AbsDistanceGraphSFlag  = TRUE;
   CurrentPreset.VelocityGraphSFlag  = TRUE;
   CurrentPreset.ForceGraphSFlag     = TRUE;
   CurrentPreset.SeqPresetSFlag      = TRUE;

   CurrentPreset.SetupPresetAFlag    = FALSE;
   CurrentPreset.WeldHistoryAFlag    = FALSE;
   CurrentPreset.WeldSummaryAFlag    = FALSE;
   CurrentPreset.PowerGraphAFlag     = FALSE;
   CurrentPreset.AmplitudeGraphAFlag = FALSE;
   CurrentPreset.FrequencyGraphAFlag = FALSE;
   CurrentPreset.ColDistanceGraphAFlag  = FALSE;
   CurrentPreset.AbsDistanceGraphAFlag  = FALSE;
   CurrentPreset.VelocityGraphAFlag  = FALSE;
   CurrentPreset.ForceGraphAFlag     = FALSE;
   CurrentPreset.SeqPresetAFlag      = FALSE;
   if(CurrentSetup.VGAHWPresent)
      CurrentPreset.GlobalPrintingFlag  = FALSE;
   else
      CurrentPreset.GlobalPrintingFlag  = TRUE;

   CurrentPreset.AutoScaleFlag = TRUE; /* TRUE = AutoScale enabled in TIME MODE */

/****    ****   External presets   ****    ****/

   if(CurrentSetup.VGAHWPresent)
      CurrentSetup.ExtGlobalPrintFlag = FALSE;
   else
      CurrentSetup.ExtGlobalPrintFlag = TRUE;

   CurrentSetup.SPExtSampleFlag    = TRUE; /* SampleFlag */
   CurrentSetup.WHExtSampleFlag    = TRUE;
   CurrentSetup.WSExtSampleFlag    = TRUE;
   CurrentSetup.PGExtSampleFlag    = TRUE;
   CurrentSetup.AGExtSampleFlag    = TRUE;
   CurrentSetup.FreqGExtSampleFlag = TRUE;
   CurrentSetup.CDGExtSampleFlag   = TRUE;
   CurrentSetup.VGExtSampleFlag    = TRUE;
   CurrentSetup.FGExtSampleFlag    = TRUE;
   CurrentSetup.SeqExtSampleFlag   = TRUE;
   CurrentSetup.SPExtAlarmFlag    = FALSE; /* Alarm Flag */
   CurrentSetup.WHExtAlarmFlag    = FALSE;
   CurrentSetup.WSExtAlarmFlag    = FALSE;
   CurrentSetup.PGExtAlarmFlag    = FALSE;
   CurrentSetup.AGExtAlarmFlag    = FALSE;
   CurrentSetup.FreqGExtAlarmFlag = FALSE;
   CurrentSetup.CDGExtAlarmFlag   = FALSE;
   CurrentSetup.VGExtAlarmFlag    = FALSE;
   CurrentSetup.FGExtAlarmFlag    = FALSE;
   CurrentSetup.SeqExtAlarmFlag   = FALSE;
   CurrentSetup.SPExtSampleValue = 1;  /* SampleValue */
   CurrentSetup.WHExtSampleValue = 1;
   CurrentSetup.WSExtSampleValue = 1;
   CurrentSetup.PGExtSampleValue = 1;
   CurrentSetup.AGExtSampleValue = 1;
   CurrentSetup.FreqGExtSampleValue = 1;
   CurrentSetup.CDGExtSampleValue = 1;
   CurrentSetup.VGExtSampleValue = 1;
   CurrentSetup.FGExtSampleValue = 1;
   CurrentSetup.SeqExtSampleValue = 1;
}

void SetUSBToFactoryDefault(void)
/****************************************************************************/
/*                                                                          */
/*  This function will turn off all USB on sample and USB on alarm          */
/*  functions.  This is the same as cold start, except only USB params are  */
/*  affected.                                                               */
/*                                                                          */
/****************************************************************************/
{
   CurrentSetup.USBGlobalFlag      = FALSE;
   CurrentSetup.USBWDSampleFlag    = TRUE;
   CurrentSetup.USBPGSampleFlag    = TRUE;
   CurrentSetup.USBAGSampleFlag    = TRUE;
   CurrentSetup.USBFreqGSampleFlag = TRUE;
   CurrentSetup.USBCDGSampleFlag   = TRUE;
   CurrentSetup.USBVGSampleFlag    = TRUE;
   CurrentSetup.USBFGSampleFlag    = TRUE;
   CurrentSetup.USBWDAlarmFlag    = FALSE;
   CurrentSetup.USBPGAlarmFlag    = FALSE;
   CurrentSetup.USBAGAlarmFlag    = FALSE;
   CurrentSetup.USBFreqGAlarmFlag = FALSE;
   CurrentSetup.USBCDGAlarmFlag   = FALSE;
   CurrentSetup.USBVGAlarmFlag    = FALSE;
   CurrentSetup.USBFGAlarmFlag    = FALSE;
   CurrentSetup.USBWDSampleValue = 1;
   CurrentSetup.USBPGSampleValue = 1;
   CurrentSetup.USBAGSampleValue = 1;
   CurrentSetup.USBFreqGSampleValue = 1;
   CurrentSetup.USBCDGSampleValue = 1;
   CurrentSetup.USBVGSampleValue = 1;
   CurrentSetup.USBFGSampleValue = 1;
}

void SetupAmpModeStepFlag(void)
{
  if((CurrentPreset.Amp2Flag & BIT0) == BIT0){
      AmplitudeStepEnableFlag.bool  = TRUE;
      AmplitudeStepEnableFlag.uint16.Hi = TRUE;
      AmplitudeStepMicronsEnableFlag.uint16.Hi = TRUE;
      AmplitudeStepMicronsEnableFlag.uint16.Low = TRUE;
      AmplitudeFixedEnableFlag = FALSE;
      AmpStepEnable = TRUE;
   }
   else
   {
      AmplitudeStepEnableFlag.bool  = FALSE;
      AmplitudeStepEnableFlag.uint16.Hi = FALSE;
      AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
      AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE;
      AmplitudeFixedEnableFlag = TRUE;
      AmpStepEnable = FALSE;
   }
   if(CurrentSetup.AmpMicronsFlag==TRUE)AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE; else AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
}

void SetupAmplitudeStepFlag(void)
{
  if((CurrentPreset.Amp2Flag & BIT0) == BIT0){
      AmplitudeStepEnableFlag.bool  = TRUE;
      AmplitudeStepEnableFlag.uint16.Hi = TRUE;
      AmplitudeStepMicronsEnableFlag.uint16.Hi = TRUE;
      AmplitudeStepMicronsEnableFlag.uint16.Low = TRUE;
      AmplitudeFixedEnableFlag = FALSE;
   }
   else
   {
      AmplitudeStepEnableFlag.bool  = FALSE;
      AmplitudeStepEnableFlag.uint16.Hi = FALSE;
      AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
      AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE;
      AmplitudeFixedEnableFlag = TRUE;
   }
   if(CurrentSetup.AmpMicronsFlag==TRUE)AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE; else AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
}

void SetupForceFixedOrStepFlag(void)
{
   if((CurrentPreset.Force2Flag & BIT0) == BIT0){
      ForceStepEnableFlag.bool  = TRUE;
      ForceStepEnableFlag.uint16.Hi = TRUE;
      ForceFixedEnableFlag = FALSE;
      ForceStepEnable = TRUE;
   }
   else
   {
      ForceStepEnableFlag.bool  = FALSE;
      ForceStepEnableFlag.uint16.Hi = FALSE;
      ForceFixedEnableFlag = TRUE;
      ForceStepEnable = FALSE;
   }
}


void SetupForceStepFlag(void)
{
   if((CurrentPreset.Force2Flag & BIT0) == BIT0){
      ForceStepEnableFlag.bool  = TRUE;
      ForceStepEnableFlag.uint16.Hi = TRUE;
      ForceFixedEnableFlag = FALSE;
   }
   else
   {
      ForceStepEnableFlag.bool  = FALSE;
      ForceStepEnableFlag.uint16.Hi = FALSE;
      ForceFixedEnableFlag = TRUE;
   }
}
