/* $Header:   D:/databases/VMdb/2000Series/INC/STATE.H_V   2.89.2.0.1.2   Jan 03 2018 12:50:30   RCHAPA  $ */
#ifndef STATE_H
#define STATE_H
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/* **************************************************************************/ 

/*------------------------ MODULE DESCRIPTION ------------------------------*/

/* Module name:                                                             */

/* Filename:      state.h                                                   */


/*---------------------------- REVISIONS -----------------------------------*/

/* Revision #  Date      Author   Description                               */
/* ==========  ========  ======   ===========                               */
/*    0        4/22/96   BEK      Initial Release                           */
/*    1        4/25/96   LAM      Format file                               */
/*    2        05-01-96  BEKymer  Added calibration states                  */
/*    3        05-03-96  BEKymer  Added upstroke state                      */
/*    4        06-28-96  BEKymer  Added FINALDATASTATE                      */
/*    5        07-24-96  LAM      Added SCSTATES                            */
/*    6        08-02-96  LAM      Added more SCSTATES                       */
/*    7        08-13-96  BEKymer  New states for SonicsOnX                  */
/*    8        09-19-96  BEKymer  New variable - StaggerFlag                */
/*    9        09-21-96  BEKymer  New state TESTMODESTATE                   */
/*   10        10-08-96  BEKymer  Add DoorOpen & ExternalReset              */
/*                                to INBITS                                 */
/*   11        10-10-96  BEKymer  New states for test mode                  */
/*   12        10-16-96  BEKymer  Add ExternalTrigger to INBITS structure   */
/*                                Add StopFlag variable                     */
/*                                Add power supply signals to INBITS        */
/*                                structure (run, seek, stroe and clear)    */
/*   13        10-30-96  LAM      Added more CALTRIGGER                     */
/*   14        10-31-96  BEKymer  Add new state - NEWSTATE                  */
/*   15        11-07-96  BEKymer  Add new state - UPDATEDATASTATE           */
/*   16        12-11-96  BEKymer  Add STATE-CheckHornDown & SSTATEs CheckHD */
/*   17        12-19-96  BEKymer  Change UPPERLIMIT_TIMEOUT to 4000         */
/*   18        01-28-97  LAM      deleted unused variables                  */
/*   19        02-05-97  LAM      added aljumpnorm state                    */
/*   20        02-26-97  PhilJ    added EMERGENCYSTOPRESET                  */
/*   21        03-27-97  PhilJ    added UPDATEALARMSTATE                    */
/*   22        04-10-97  LAM      added WELDTIME2STATE                      */
/*   23        05-05-97  LAM      deleted unused 1msdata                    */
/*   24        05-28-97  LAM      added FINAL1MSDATA                        */
/*   25        05-30-97  LAM      deleted unused define                     */
/*   26.2.41   06-23-97  LAM      deleted missingpart from inbits           */
/*   26.2.42   07-02-97  LAM      added states for no encoder               */
/*   26.2.43   07-07-97  LAM      moved powerup variables to state.c        */
/*   26.2.44   07-17-97  BEKymer  Added PTSTimerFlag, PBExitFlag            */
/*   26.2.45   07-24-97  BEKymer  Added VERIFYDATASTATE                     */
/*   26.2.46   07-30-97  BEKymer  Added STATES StartData & StopData         */
/*                                      and PowerDown1                      */
/*   27.2.47   08-11-97  LAM      added power calibration states            */
/*   27.2.48   08-14-97  LAM      added more power calibration states       */
/*   2.49      08-29-97  LAM      added power calibration trig state        */
/*   2.50      09-04-97  BEKymer  Added new variable 'OKToAdvance'          */
/*   2.51      09-15-97  BEKymer  Move SSTATES & STATE into flash           */
/*                                Add PreReadyTestST for LAM                */
/*   2.52      10-27-97  BEKymer  Added ULSExitFlag                         */
/*   2.53      04-09-98  BEKymer  Changed MAX_AB???_TIME from 30000 to 2000 */
/*   2.54      04-22-98  BJB      Moved TRIGGERLOSTTIME from WELDHOLD.C     */
/*                                Moved PBEXITTIME from READY.C             */
/*                                Deleted def of HornDownFlag, moved it.    */
/*   2.55      04-27-98  LAM      deleted unused upstroke states, added calbpb*/
/*   2.56      05-19-98  BEKymer  Created new state - PROCESSALARMSSTATE    */
/*   2.57      05-20-98  LAM      added spring rate states                  */
/*   2.58      06-10-98  LAM      added extra state for calibration         */
/*   2.59      06-23-98  LAM      deleted unused page states                */
/*   2.61      07-02-98  BJB      TRIGGERLOSTFORCE, TRIGGERLOSTDISTANCE     */
/*                                moved here from weldhold.c                */
/*   2.62      11-20-98  BJB      Corrected spelling of WELDSTATES          */
/*   2.63      04-20-99  OFI      Changed for DIAB                          */
/*   2.64      05-28-99  OFI    Add new defines HIGH_PRESSURE, LOW_PRESSURE,*/
/*                                PRESSURE_TOLLERANCE for SE277 Alarm       */
/*   2.65      06-07-99  OFI      Changed values of defines added previously*/
/*   2.65.1.1  06-24-99  JZ       deleted HoldState, HDReadySt              */
/*   2.65.1.2  07-08-99  JZ       added PRESSURE_TOLLERANCE_SE277 for SE277 */
/*   2.68      09-07-99  LAM      deleted unused cal states                 */
/*   2.69      11-04-99  LAM      deleted all TABS                          */
/*   2.70      12-16-99  LAM      deleted unused reference to profiling     */
/*   2.71      12-17-99  LAM      merged with 2.69.2.1                      */
/*   2.72      07-21-00  BEKymer  Added AbTimeDelayFlag & DUPSOkFlag        */
/*   2.73      08-29-00  JLH      Added DepotLevel state flag.              */
/*   2.74      09-05-00  LAM      Added powerupseek state for dups.         */
/*   2.75      04-10-01  BEKymer  Added STATE's for 1 cycle start condition */
/*                                Added SingleStart to INBITS structure     */
/*   2.76      04-20-01  LAM      Added PresetCode to INBITS structure      */
/*   2.77      04-20-01  BEKymer  Added SonicsOn3HHST, SonicsOn4HHST        */
/*   2.78      04-23-01  LAM      Changed declaration of PresetCode to      */
/*                                work with the menu structures             */
/*   2.79      04-24-01  BEKymer  Added FakeHoldHHST                        */
/*   2.80      05-11-01  BEKymer  Change PBEXITTIME from 2000 to 6000 ms    */
/*   2.81      06-27-01  BEKymer  Create NEGTRIGGERLOSTDISTANCE             */
/*   2.82      05-28-02  BEkymer  Add variables for ClearMem                */
/*   2.83      09-16-03  BEKymer  Add energy brake flag and states          */
/*   2.84      02-18-04  VSharma  Added SonicDisable, MemReset, SVInterLock */
/*                                & ExtTrgDelay to struct INBITS.           */
/*   2.85      03-05-04  VSharma  Added DisplayLockFlag in struct INBITS.   */
/*                                Changed PresetCode from SINT32 to UINT16  */
/*   2.86      03-12-04  VSharma  Add variables PresetX & BitBucket to the  */
/*                                 struct INBITS.                           */
/*   2.87      04-06-04  VSharma  Added SVInterlock & ExtTrgDelay state.    */
/*   2.88      05-03-04  VSharma  Added SyncIn in struct INBITS.            */
/*   2.89      05-17-04  VSharma  Changed PresetCode to SINT32.             */
/*   2.89.2.0  05-27-05  BEKymer  Add extern's for PLC Control stuff        */
/*   2.89.2.0.1.1	   10-18-17   RChapa  Added State and SubState for Refresh DUPS
 * 								  Parameters DUPSPBSTATE, WaitforDUPSSS, 
 * 								  WaitForDUPS                               */
/*   2.89.2.0.1.2	   01-03-18   RChapa  Removed State and SubState for Refresh DUPS
 * 								  Parameters DUPSPBSTATE, WaitforDUPSSS, 
 * 								  WaitForDUPS                               */ 
/*                                                                          */
/*                                                                          */
/*------------------------------ DESCRIPTION -------------------------------*/


 

/*----------------------------- INCLUDE FILES ------------------------------*/


/*-------------------------------- DEFINES ---------------------------------*/


#define NMBR_OF_STATES    50
#define FAILED1           -1
#define FAILED2           -2


#define TRIGGER_TIMEOUT           10000   /* Max time between ULS & trigger */
#define TRIGGERLOSTTIME           150     /* Time (ms) before trigger is considered lost */
#define NEGTRIGGERLOSTDISTANCE    2000    /* .2" of upward travel after trigger */
#define TRIGGERLOSTDISTANCE       2500    /* 1/4" of travel after trigger with less than */
#define TRIGGERLOSTFORCE          350     /* 35 lbs of force                             */
#define UPPERLIMIT_TIMEOUT        4000    /* Max time between PB's & ULS    */
#define PALMBUTTON_STAGGER_TIME   200     /* Max time between the two PB's  */
#define PBEXITTIME                6000    /* Time before pb's must be rlsd  */
#define MAX_WELD_TIME             30000   /* Absolute max weld time         */
#define MAX_HOLD_TIME             30000   /* Absolute max hold time         */
#define MAX_ABDELAY_TIME          2000    /* Absolute max AB delay time     */
#define MAX_AB_TIME               2000    /* Absolute max AB time           */


#ifdef STATES                     /******************************************/
#define Statetype                 /* This cute little trick will allow all  */
#else                             /* uninitialized variables to be defined  */
#define Statetype  extern         /* in one file.  In Main.c GLOBAL should  */
#endif                            /* be defined.                            */
                                  /******************************************/
#define HIGH_PRESSURE             800
#define LOW_PRESSURE              600
#define PRESSURE_TOLLERANCE       30
#define PRESSURE_TOLLERANCE_SE277 30

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  This first section of variables are those that must be updated from     */
/*  within the 1 ms interrupt handler.                                      */
/*                                                                          */
/*--------------------------------------------------------------------------*/

Statetype BOOLEAN CycleAbort, DistFlag;
extern    BOOLEAN ContinueFlag;

/*-------------  End of 1 ms interrupt variables  --------------------------*/


Statetype BOOLEAN  FailFlag, AbortFlag, SystemOK, TimerFlag;
Statetype BOOLEAN  StepTimeFlag, ABTimeFlag, ABTimeDelayFlag, SonicsAbort;
Statetype BOOLEAN  WTimeFlag, PTSTimerFlag, DUPSOkFlag, DepotLevel;
Statetype BOOLEAN  HTimeFlag, PDownDelay, TriggerDelayFlag;
Statetype BOOLEAN  StaggerFlag, AlarmsReset, TestTimerFlag;
Statetype BOOLEAN  StopFlag, ActClrFlag, StartTestFlag;
Statetype BOOLEAN  PBExitFlag, ULSExitFlag;
Statetype BOOLEAN  OKToAdvance, ExitClearMemFlag, EnergyBrakeFlag;


Statetype SINT16   InitTime, TimeOff;
Statetype SINT16   TrsEnd, TrsTime, UlsTime;
Statetype SINT16   MaxWTime, MaxHTime;
Statetype SINT16   MaxDTime, MaxABTime;
Statetype SINT16   Stagger;



enum WELDSTATES {                 /* Available weld states                 */
   NOP,                           /*                                       */
   POWERUPSEEKSTATE,              /* added for dups                        */
   PREREADYSTATE,                 /*                                       */
   READYSTATE,                    /*                                       */
   PBSTATE,                       /*                                       */
   DOWNSTROKESTATE,               /*                                       */
   WAITFORULSCLEARSTATE,          /*                                       */
   WAITFORPTSSTATE,               /* Pre-trigger state                     */
   WAITFORTRSSTATE1,              /*                                       */
   WAITFORTRSSTATE2,              /*                                       */
   WAITFORTRSSTATE3,              /* Horn down                             */
   TRIGGEREDSTATE,                /*                                       */
   TRIGGERDELAYSTATE,             /* A delay after trigger & before sonics */
   WELDTIMESTATE,                 /*                                       */
   WELDTIME2STATE,                /*                                       */
   ENDOFSONICS,                   /*                                       */
   HOLDTIMESTATE,                 /*                                       */
   PROCESSALARMSSTATE,            /* Check all process alarms              */
   AFTERBURSTDELAYSTATE,          /*                                       */
   AFTERBURSTTIMESTATE,           /*                                       */
   TESTMODESTATE,                 /*                                       */
   UPSTROKESTATE,                 /*                                       */
   WAITFORULSMADESTATE,           /*                                       */
   POWERDOWNSTATE,                /*                                       */
   DATAPACKETFULL,                /*                                       */
   NEWSTATE,                      /* A new state has been entered          */
   EMERGENCYSTOP,
   WAITFORCONTINUE,               /*                                       */
   CALTIMERSTATE1,                /*                                       */
   CALTIMERSTATE2,                /*                                       */
   MENUSYNCSTATE,
   READA2D1STATE,
   READA2D2STATE,
   READA2D3STATE,
   CALREADYSTATE,
   FINAL1MSSTATE,                 /* All final data will be sent here      */
   FINALDATASTATE,                /* All final data will be sent here      */
   UPDATEDATASTATE,               /* All updated data will be sent here    */
   SEEKSTATE,                     /*                                       */
   UPDATESTATE,                   /* Parameter update, new RunningPreset   */
   UPDATEALARMSTATE,
   RAMPSONICSSTATE,               /* State to ramp sonics up or down       */
   EMERGENCYSTOPRESET,            /* added 2/25/97                         */
   VERIFYDATASTATE,               /* Setup alarm data will be sent here    */
   CLEARMEMORYSTATE,              /* Clear P/S frequency memory            */
   WAITFORSVINPUTSTATE,           /* wait for SVInterlock input upto 30sec.*/
   EXTTRIGDELAYSTATE,             /* Delay after the trigger state.        */
   EXTEND_WELDSTATES = 65535u     /* Force values to be 16 bit             */
   };


enum ACTIONS  {
   NORM,                      /* Normal state, move on to next value        */
   FAIL,                      /* Set FailFlag for later checking            */
   ABORT,                     /* Set AbortFlag for later checking           */
   JUMP,                      /* This state is complete, go to next state   */
   ALJUMPNORM,                /* This state is complete, go to next state,with alarms  */
   POP,                       /* Return to PUSHed state previously saved    */
   PUSH,                      /* Save current state index for possible POP  */
   END,                       /* This is the end of the sub state list      */
   ALJUMP,                    /* Alarm condition, abort this sub state      */
   ALNORM  };                 /* Alarm condition, but continue sub state    */

typedef const struct substates {
   BOOLEAN *ValuePtr;         /* Pointer to value to be used for evaluation */
   enum    ACTIONS True;      /* What to do if value evaluates to TRUE      */
   enum    ACTIONS False;     /* What to do if value evaluates to FALSE     */
   UINT32  Alarm;             /* Alarm code if there was an alarm condition */
   SINT16  Trace;             /* Code for trace buffer                      */
   } SSTATES;

typedef const struct states {
   SSTATES *ptr;              /* Pointer to sub state structure             */
   SINT16  *STimer;           /* Pointer to timer value for this state      */
   void    (*PassPtr)(void) ; /* Pointer to function to call every pass     */
   void    (*EntryPtr)(void); /* Pointer to function to call on entry       */
   void    (*NextPtr)(void);  /* Pointer to function to call on normal exit */
   void    (*AlarmPtr)(void); /* Pointer to function to call on alarm exit  */
   enum WELDSTATES state;     /* State currently in                         */
   } STATE;



typedef struct portdata {
   BOOLEAN uls;             /* Upper limit switch                           */
   BOOLEAN trs;             /* Trigger switch if AE, Force trigger if EP    */
   BOOLEAN OnePB;           /* Either palm button, but not both             */
   BOOLEAN BothPB;          /* Both palm buttons                            */
   BOOLEAN SingleStart;     /* 1 PB, trigger switch or ext sig(8.1S = OnePB)*/
   BOOLEAN PwrOn;           /* The power is on and okay                     */
   BOOLEAN PwrOff;          /* A power off has been requested by the user   */
   BOOLEAN OL;              /* Power supply overload                        */
   BOOLEAN Estop;           /* Emergency stop                               */
   BOOLEAN lls;             /* Lower limit switch                           */
   BOOLEAN GndDet;          /* Ground detect                                */
   BOOLEAN ECycleAbort;     /* External cycle abort input                   */  
   BOOLEAN Trigger;         /* Logical trigger AE or EP                     */  
   BOOLEAN DoorOpen;        /* Carriage door TRUE:open dont allow welding   */
   BOOLEAN ExternalReset;   /* External reset                               */
   BOOLEAN ExternalTrigger; /* External Force or amplitude step trigger     */
   BOOLEAN PSRun;           /* Power supply run signal                      */
   BOOLEAN PSSeek;          /* Power supply seek signal                     */
   BOOLEAN PSStore;         /* Power supply store signal                    */
   BOOLEAN PSClear;         /* Power supply clear signal                    */
   SINT32  PresetCode;      /* External Selection of Preset                 */
   BOOLEAN SonicDisable;    /* Sonics Disable signal                        */
   BOOLEAN MemReset;        /* Menmory Reset signal                         */
   BOOLEAN SVInterLock;     /* SV Interlock Input signal                    */
   BOOLEAN ExtTrgDelay;     /* External trigger delay signal                */
   BOOLEAN DisplayLockFlag; /* Display Lock Signal                          */
   BOOLEAN Preset1;	     	/* For J3-32's contribution to the preset code  */
   BOOLEAN Preset2;		    /* For J3-33's contribution to the preset code  */
   BOOLEAN Preset4;	       	/* For J3-19's contribution to the preset code  */
   BOOLEAN Preset8;	      	/* For J3-17's contribution to the preset code  */
   BOOLEAN Preset16;     	/* For J3-31's contribution to the preset code  */
   BOOLEAN BitBucket;		/* For when an input is disabled.               */
   BOOLEAN SyncIn;   		/* Sync In input signal.                        */
   }  INBITS;


#ifndef STATES

extern  SSTATES Initial[];
extern  SSTATES Ready[];
extern  SSTATES ReadyTest[];
extern  SSTATES CheckReady[];
extern  SSTATES PalmButtons[];
extern  SSTATES PalmButton[];
extern  SSTATES CalbPBs[];
extern  SSTATES WaitUls1[];
extern  SSTATES WaitUls2[];
extern  SSTATES WaitSVInput[];
extern  SSTATES ExtTrigDelay[];
extern  SSTATES PreTrigger[];
extern  SSTATES WaitTrs1[];
extern  SSTATES WaitTrs2[];
extern  SSTATES WaitTrs1PT[];
extern  SSTATES WaitTrs2PT[];
extern  SSTATES TrigDelay[];
extern  SSTATES Weld1[];
extern  SSTATES Weld1A[];
extern  SSTATES Weld2[];
extern  SSTATES EnerBrake[];
extern  SSTATES SonicsOff[];
extern  SSTATES Hold[];
extern  SSTATES AlterHold[];
extern  SSTATES Limits[];
extern  SSTATES Nop[];
extern  SSTATES PowerDown[];
extern  SSTATES PowerDown1[];
extern  SSTATES WaitTime[];
extern  SSTATES AdjustDone[];
extern  SSTATES MenuSync[];
extern  SSTATES FinalData[];
extern  SSTATES DebugState[];
extern  SSTATES Power1[];
extern  SSTATES Power2[];
extern  SSTATES Power3[];
extern  SSTATES PwrPage1[];
extern  SSTATES PwrPage2[];
extern  SSTATES Trigger[];
extern  SSTATES PwrTrigger[];
extern  SSTATES SeekWait[];
extern  SSTATES ParamUpdate[];
extern  SSTATES Initial[];
extern  SSTATES PChkAct;
extern  SSTATES PChkPwrSup;
extern  SSTATES PChkCntrls;
extern  SSTATES PChkStack;
extern  SSTATES ClearMem;

/* SSTATES added for 1 cycle start */

extern  SSTATES ReadyHH;
extern  SSTATES CheckReadyHH;
extern  SSTATES PalmButtonsHH;
extern  SSTATES WeldHH;
extern  SSTATES SonicsOffHH;
extern  SSTATES TriggerHH[];
extern  SSTATES ABDelayHH;
extern  SSTATES ABTimeHH;
extern  SSTATES SeekHH;
extern  SSTATES SeekWaitHH[];
extern  SSTATES CalWaitUls1;
extern  SSTATES CalTrigger;

extern  STATE   TopOfList; 
extern  STATE   ReadySt;   
extern  STATE   PreReadyTestSt;   
extern  STATE   ReadyTestSt;   
extern  STATE   PBState;   
extern  STATE   OnePBState;   
extern  STATE   WaitUls;
extern  STATE   WaitUlsUp;
extern  STATE   WaitSVST;
extern  STATE   WaitTrs1DST;
extern  STATE   WaitTrs2DST;
extern  STATE   WaitTrs1ST;
extern  STATE   WaitTrs2ST;
extern  STATE   WaitTrs1DSTPT;
extern  STATE   WaitTrs2DSTPT;
extern  STATE   WaitTrs1STPT;
extern  STATE   WaitTrs2STPT;
extern  STATE   WaitTrsST3;
extern  STATE   UpdateState;
extern  STATE   PreTrsDST;
extern  STATE   PreTrsST;
extern  STATE   TriggerST; 
extern  STATE   CalTriggerST; 
extern  STATE   ExtTrigDelayST;
extern  STATE   TrigDelayST; 
extern  STATE   SonicsOn1ST; 
extern  STATE   SonicsOn1DST; 
extern  STATE   SonicsOn1A; 
extern  STATE   SonicsOn2ST; 
extern  STATE   SonicsOn2DST; 
extern  STATE   SonicsOn3DST; 
extern  STATE   SonicsOn3ST; 
extern  STATE   SonicsOn3A;
extern  STATE   SonicsOn3B;
extern  STATE   SonicsOn3CST;
extern  STATE   SonicsOn3CDST;
extern  STATE   SonicsOn4ST; 
extern  STATE   SonicsOn4DST; 
extern  STATE   SonicsOn5; 
extern  STATE   SonicsOn6; 
extern  STATE   SonicsOn7ST; 
extern  STATE   SonicsOn7DST; 
extern  STATE   SonicsOn8ST; 
extern  STATE   SonicsOn8DST; 
extern  STATE   SonicsOn9ST; 
extern  STATE   SonicsOn9DST; 
extern  STATE   WeldOffST;  
extern  STATE   EnerBrakeST;  
extern  STATE   EnerBrakeHHST;  
extern  STATE   PLCBrakeHHST;  
extern  STATE   HoldTimeST;  
extern  STATE   HoldTimeDST;  
extern  STATE   FakeHold;  
extern  STATE   CheckLimitsST;  
extern  STATE   ABDelayST;
extern  STATE   ABTimeST;
extern  STATE   RampSonicsST;
extern  STATE   SeekState;  
extern  STATE   PreReady;  
extern  STATE   EndOfList; 
extern  STATE   NopList;   
extern  STATE   TestST;   
extern  STATE   StartData;   
extern  STATE   StopData;   
extern  STATE   PowerOn1;   
extern  STATE   PowerOn2;   
extern  STATE   PowerOn3;   
extern  STATE   PowerOn4;   
extern  STATE   PowerOn5;   
extern  STATE   PowerOn6;   
extern  STATE   PwrDown;   
extern  STATE   MenuSyncST;
extern  STATE   CalTopOfList;
extern  STATE   PwrPage1Wait; 
extern  STATE   PwrPage2Wait; 
extern  STATE   PwrPage3Wait; 
extern  STATE   CollectPwr1;  
extern  STATE   CollectPwr2;  
extern  STATE   CollectPwr3;  
extern  STATE   VerifyPwr;  
extern  STATE   VerifyPower;  
extern  STATE   PwrTriggerST;
extern  STATE   CalReadySt;  
extern  STATE   CalPBState2;
extern  STATE   CalWaitUls;  
extern  STATE   CalWaitTrsST;
extern  STATE   CalWaitTime1;  
extern  STATE   CalWaitTime2;  
extern  STATE   CalEndOfList;
extern  STATE   DistanceST1;
extern  STATE   DistanceST2;
extern  STATE   ClearMemST;
extern  STATE   DebugDelayST;
extern  STATE   DebugTrigST;
extern  STATE   FinalDataST;
extern  STATE   SCPBState;
extern  STATE   SCWaitUls;  
extern  STATE   SCDone;
extern  STATE   SCDeflection;
extern  STATE   SCWaitTrsST;
extern  STATE   SCEndOfList;

/* States added for 1 cycle start condition */

extern STATE    PreReadyHHST;
extern STATE    ReadyHHST;
extern STATE    PBStateHHST;
extern STATE    SonicsOnHHST;
extern STATE    PLCOnHHST;
extern STATE    SonicsOn2HHST;
extern STATE    PLCOn2HHST;
extern STATE    SonicsOn3HHST;
extern STATE    SonicsOn4HHST;
extern STATE    SonicsOnGD1ST;
extern STATE    SonicsOnGD2ST;
extern STATE    SonicsOnPP1ST;
extern STATE    SonicsOnPP2ST;
extern STATE    HoldTimeHHST;
extern STATE    PLCTimeHHST;
extern STATE    FakeHoldHHST;
extern STATE    WeldOffHHST;
extern STATE    ABDelayHHST;
extern STATE    ABTimeHHST;
extern STATE    SeekStateHH;  
extern STATE    TriggerHHST; 

#endif
#endif
