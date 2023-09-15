/* $Header:   D:/databases/VMdb/2000Series/INC/READY.H_V   2.40.1.2   Jan 03 2018 12:58:50   RCHAPA  $ */
/* ************************************************************************ */ 
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996,97        */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/* ************************************************************************ */ 

/*------------------------ MODULE DESCRIPTION ------------------------------*/

/* Module name:                                                             */

/* Filename:      ready.h                                                   */


/*---------------------------- REVISIONS -----------------------------------*/

/* Revision #  Date      Author   Description                               */
/* ==========  ========  ======   ===========                               */
/*    0        04/22/96   BEK      Initial Release                          */
/*    1        01-26-97   LAM      deleted displayalarm prototype           */
/*    2        01-30-97   LAM      added clearalarm prototype               */
/*    3        03-27-97   PhilJ    Renamed UpdateData to UpdateAlarm        */
/*    4        04-07-97   LAM      added testactclr                         */
/*    5        04-09-97   LAM      added testulsup                          */
/*    6        04-16-97   BEKymer  Added prototype for TestUls()            */
/*    7        05-09-97   LAM      Added prototype for EnterTestReady       */
/*    8.2.23   07-02-97   LAM      Added prototype for no encoder           */
/*    9.2.24   07-10-97   BEKymer  Added prototype for RecordSetupAlarm     */
/*    9.2.25   08-01-97   BEKymer  Add prototpye for ExitULS1               */
/*    9.2.26   08-08-97   BEKymer  Changed Filename description above       */
/*                                 Add new prototype                        */
/*    2.27     09-12-97   LAM      Added prototype for testtestpreready     */
/*    2.28     11.12.97   JBerman  Added a prototype: PwrTestFilter         */
/*    2.29     01-28-98   BEKymer  Added prototype for EnterUlsUp()         */
/*    2.30     02-02-98   BEKymer  Added prototype for EnterFData()         */
/*                                 Added prototype for ExitUlsUp()          */
/*    2.31     05-04-98   BEKymer  Added prototype for ClearCalibrationAlarm*/
/*    2.32     06-03-98   BEKymer  Change prototype names for missing part  */
/*    2.33     08-14-98   BEKymer  Added prototype for TestForOverload      */
/*    2.34     08-06-99   JZ       Added prototype for RecordErrorCode      */
/*    2.35     11-19-99   BEKymer  Moved PRESSURE defines from ready.c      */
/*    2.36     04-11-01   BEKymer  Moved POWERUPREADYDELAY,PRINTERCHECKTIME */
/*                                  from ready.c                            */
/*                                 Moved MAXWELDTIME, POWERDIV              */
/*                                  from weldhold.c                         */
/*    2.37     05-28-02   BEKymer  Add prototypes for EnterClearMem and     */
/*                                  PassClearMem.                           */
/*    2.38     04-06-04   VSharma  Added prototype for EnterExtTrigDly(),   */
/*                                 TestExtTrigDly(),EnterSV(),TestSVInput().*/
/*    2.39     04-27-04   VSharma  Added prototype of ExitSVState().        */
/*    2.40     10-17-05   Aare     Added prototypes for pretrigger delay state functions. */
/*    2.40.1.1	   10-18-17   RChapa   Added 3 new functions for DUPS State     */
/*    2.40.1.2	   01-03-18   RChapa   Removed 3 new functions for DUPS State   */
/*                                                                          */
/*------------------------- FUNCTION PROTOTYPING ---------------------------*/



#define PRESSURE_CHECK_TIME1       250    /* how long to wait in ready before */
                                          /* checking system pressure    */
#define PRESSURE_CHECK_TIME2       250    /* how long to wait in ready before */
                                          /* repeatadly checking system pressure    */
#define IDLE_TO_DOWNSPEED_DISTANCE 750    /* Distance before switch from idle to downspeed value */
#define POWERUPREADYDELAY         2500    /* Wait this time after power up before   */
                                          /* Ready can go active                    */
#define PRINTERCHECKTIME          5000    /* In Not ready check printer this often  */
#define MAXWELDTIME              30000    /* Max. selectable weld on time           */
#define POWERDIV                    10
                             

void   SetAlarmFlag(void);
UINT16 ClearAlarm(UINT32 code);
void   ClearAlarmFlag(void);
void   ClearAbort(void);
UINT16 CheckAlarmFlag(void);
void   EnterReady(void);
void   EnterTestReady(void);
void   TestReady(void);
void   TestReadyTest(void);
void   TestActClr(void);
void   ExitReady(void);
void   ExitReadyTest(void);
void   StartPB(void);
void   TestPB(void);
void   ExitPB(void);
void   TriggerBeep(void);
void   AlarmExitPB(void);
void   EntryTrs1(void);
void   EntryTrs2(void);
void   ExitULS(void);
void   ExitULS1(void);
void   ExitTrs1F(void);
void   ExitTrs1D(void);
void   ExitTrs1(void);
void   ExitTrs2(void);
void   ExitUlsUp(void);
void   AlarmUls(void);
void   AlarmTrs1(void);
void   EPreReady(void);
void   TestPreReady(void);
void   EnterPTS(void);
void   TestPTS(void);
void   StartPTS(void);
void   TestForOverload(void);
void   TestTrs1F(void);
void   TestTrs1D(void);
void   TestTrs1(void);
void   TestTrs2D(void);
void   TestTrs2(void);
void   EnterUls(void);
void   TestUls(void);
void   EnterUlsUp(void);
void   TestUlsUp(void);
void   TestTest(void);
void   TestTestPreReady(void);
void   EnterTest(void);
void   ExitTest(void);
void   RecordAlarm(UINT32 code);
void   RecordSetupAlarm(UINT32 AlarmCode);
void   EnterFData(void);
void   SendFData(void);
void   UpdateAlarm(void);
UINT16 CheckIfResetRequired(void);
void   ClearCalibrationAlarms(void);
void   EnterUpstroke(void);
void   ExitUpstroke(void);
void   TestUpstroke(void);
void   ClearFinalResults(void);

BOOLEAN CheckForMissingPartMin(void);
BOOLEAN CheckForMissingPartMax(void);
void RecordErrorCode(enum ERRORCODE_ARG ErrorCodeArg);

UINT32 PwrTestFilter(UINT32);  
void EnterClearMem(void);
void PassClearMem(void);

void EnterExtTrigDly(void);
void TestExtTrigDly(void);
void EnterSV(void);
void TestSVInput(void);
void ExitSVState(void);

// state functions for pretrigger delay
void TestPreTrigDelay1(void);
void EnterPreTrigDelay1(void);
void ExitPreTrigDelay1(void);
void AlarmPreTrigDelay1(void);
void TestPreTrigDelay2(void);
void EnterPreTrigDelay2(void);
void ExitPreTrigDelay2(void);
void AlarmPreTrigDelay2(void);


