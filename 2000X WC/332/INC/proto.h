/*****     *****     Function Prototypes     *****     *****/



/**  **  **  1ms.c  **  **  **/

void  Init1ms(void);  


/**  **  **  alarm.c  **  **  **/

void  InitAlarm(void);       
void  ProcessAlarmIn(void);  
void  ProcessAlarmOut(void); 
void  LockPowerOn(void);
void  PowerDownSystem(void);
void  DisplayAlarm(void);
void  SetGeneralAlarm(void);
void  SetAuxAlarms(void);
void  ClearGeneralAlarm(void);
void  ClearAuxAlarms(void);
void  SetReady(void);
void  ClearReady(void);
void  ClearSAS(void);
void  SetSAS(void);
void  ClearSVStatus(void);
void  SetSVStatus(void);


/**  **  **  actuator.c  **  **  **/

void  InitActuator(void);   
void  ProcessActIn(void);   
void  ProcessActOut(void);
void  EnableSVOn(void);
void  SVOn(void);
void  SVOff(void);
void  PSIdle(void);
void  PSReset(void);
void  PSRun(void);
void  PSTest(void);


/**  **  **  Beep.c  **  **  **/

void  Beep(short nmbr, enum BEEPS type);
void  StopBeeper(enum BEEPS type);
void  ProcessBeeper(void);
  
 
/**  **  **  Coldstrt.c  **  **  **/

void  DoColdStart(void);
void  CancelColdStart(void);


/**  **  **  Error.c  **  **  **/

void  DisplayError(enum ERRORCODES ErrorCode);
void  LogError(enum ERRORCODES ErrorCode);


/**  **  **  Estop.c  **  **  **/

short ProcessEstop(void);


/**  **  **  Horndown.c  **  **  **/

void  EnterHDown(void);
void  ExitHDown(void);


/**  **  **  Init.c  **  **  **/

void  Init332(void);  
void  InitTPU(void);  


/**  **  **  Initcpu.c  **  **  **/

void  InitCpu(void);


/**  **  **  Input.c  **  **  **/

void  ReadInputs(void);


/**  **  **  keyb.c  **  **  **/

void  InitKeyB(void);   
void  PutKey(short NewKey);


/**  **  **  led.c  **  **  **/

void  UpdateBarGraph(short PowerPercent); 
void  UpdateLED(unsigned char Led,unsigned char OffOn); 


/**  **  **  Main.c  **  **  **/

void  main(void);


/**  **  **  Menu.c  **  **  **/

void  DecPot(void);
void  DisplayMenu(MENU [], short Timeout, short UpdateTime);
void  UpPot(void);

/**  **  **  Output.c  **  **  **/

void  PowerOff(void);
void  WriteOutputs(void);
void  PowerDownSequence(void);
void  CheckPD(void);
void  PowerUp(void);
void  ProcessPowerDown(void);


/**  **  **  Printkey.c  **  **  **/

void  WeldStatusSummaryCode(void);
void  CancelPrintingCode(void);
void  LabGraphsCode(void);
void  SetupPresetCode(void);
void  WeldHistoryCode(void);
void  PowerGraphCode(void);
void  AmplitudeGraphCode(void);
void  FrequencyGraphCode(void);
void  DistanceGraphCode(void);
void  VelocityGraphCode(void);
void  ForceGraphCode(void);


/**  **  **  qsm.c  **  **  **/

void  InitQsm(void); 


/**  **  **  Ready.c  **  **  **/

void  EnterReady(void);
void  TestReady(void);
void  ExitReady(void);
void  StartPB(void);
void  ExitPB(void);
void  EntryTrs1(void);
void  EntryTrs2(void);
void  ExitTrs1(void);
void  ExitTrs2(void);
void  AlarmUls(void);
void  AlarmTrs1(void);
void  Restart(void);
void  Nothing(void);
void  TestTrs1(void);
void  TestTrs2(void);
void  TestUls(void);
void  EPreReady(void);
void  Enter1(void);
void  Enter2(void);
void  Enter3(void);
void  Enter4(void);
void  Exit1(void);
void  Exit2(void);
void  Exit3(void);
void  Exit4(void);


/**  **  **  Sim.c  **  **  **/

void  InitSim(void);  


/**  **  **  Statedrv.c  **  **  **/

void  InitWeldSequencer(void);
void  StateMachine(void);
void  EntryCode(void);
void  NormalCode(void);
void  AlarmCode(void);
void  RecordAlarm(short code);
void  StartStateMachine(void);
void  StopStateMachine(void);
void  SelectWeldSequence(void);
void  SelectHDSequence(void);
      

/**  **  **  Timer.c  **  **  **/

void  InitTimer(void);
short StartTimer(short Time, short *Flag, short Use);
short UpdateTimers(void);
void  StopTimer(short Id);
void  ValidateLinkedList(void);


/**  **  **  Util.c  **  **  **/

void  strupr(char string[], short length);
void  strctr(char string1[], char string2[], short size);
void  strnset(char string[], char text, short size);
void  strsub(char string[], char old, char new);
enum  PARAM GetParamChanged(void);
void  PutParamChanged(enum PARAM NewID);
void  ResetWeldCounter(void);


/**  **  **  vf.c  **  **  **/

void  ClrVFLines(short LineNums); 
void  InitVF(void);  
void  MoveCursor(short LineNum,short LinePos,short Cursor);
void  UpdateLine(char string[],short Linenum); 
void  UpdateVFBuf(char string[],short length); 
void  WriteToVF(void);                      


/**  **  **  Weldhold.c  **  **  **/

void  SelectWeldSequence(void);
void  StartSonic1(void);
void  CheckSonics1(void);
void  StartSonic2(void);
void  CheckSonics2(void);
void  StopSonic1(void);
void  StopSonic2(void);
void  StartHold(void);
void  StopHold(void);



