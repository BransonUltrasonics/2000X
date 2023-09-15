/* $Header:   D:/SWLab/VMdb/2000Series/INC/SNSRCALB.H_V   2.39   22 Sep 2009 12:10:26   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/

/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Sensor Calibration                                          */
/*                                                                          */
/* Filename:    Snsrcalb.c                                                  */
/*                                                                          */
/* Function Name: Calibration code                                          */
/*                                                                          */
/*          Written by:   Bill Truchsess                                    */
/*                Date:   04-15-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date        Author       Description                         */
/*  =========  =========   ===========  ===========                         */
/*     0       05-03-96    WFT          Initial write of code               */
/*     1       05-05-96    LAM          deleted displaymenu prototype       */
/*     2       05-13-96    BEKymer      Add proper function prototyping     */
/*     3       06-11-96    BEKymer      Add DistanceVerifyInit function     */
/*     4       06-25-96    BEKymer      Add AdjustSpringRate function       */
/*     5       07-08-96    LAM          deleted springrate functions        */
/*     6       07-23-96    BEKymer      New function-CalTestReady           */
/*     7       07-30-96    LAM          added savecalibration               */
/*     8       08-22-96    LAM          edditted prototypes                 */
/*     9       09-12-96    LAM          added buildvelocitytable            */
/*    10       10-10-96    LAM          deleted prototype                   */
/*    11       10-30-96    LAM          added checkPSI                      */
/*    12       11-25-96    LAM          added updatespringrate              */
/*    13       12-27-96    LAM          added getcountsperlb                */
/*    14       04-23-98    LAM          added verifytable prototypes        */
/*    15       05-04-98    LAM          added requestsencal prototype       */
/*                                      added getdefspringratetable         */
/*   2.18      05-11-98    LAM          added enum for calibration          */
/*                                      added initialize spring rate        */
/*   2.19      06-01-98    LAM          made springrate size 40  .2048in    */
/*   2.20      06-10-98    LAM          added adjusttable prototype         */
/*   2.21      08-11-98    LAM          added CalibrationAllowed prototype  */
/*   2.23      08-21-98    LAM          added ShowCalibratedAbort prototype */
/*   2.24      10-28-98    LAM          chged enum from calibration to      */
/*                                      calstatus                           */
/*   2.24.2.2  07-12-99    JLH          added DisplayNextScreen prototype   */
/*   2.24.2.3  07-20-99    LAM          added LoadCalVelocityTable prototype*/
/*   2.24.2.4  07-23-99    JLH          added ReadA2DLC2 prototype          */
/*   2.24.2.5  07-29-99    LAM          added SaveCalPressure prototype     */
/*   2.27      08-06-99    JZ           moved some defines from snsrcalb.c  */
/*   2.28      08-23-99    LAM          removed unused prototype            */
/*   2.29      08-23-99    LAM          renamed initializespringrate        */
/*   2.30      09-03-99    LAM          removed unused velocity defines     */
/*   2.31      09-07-99    LAM          removed unused prototypes           */
/*   2.32      09-09-99    LAM          changed default velocity entries    */
/*   2.33      09-20-99    LAM          changed default velocity entries again*/
/*   2.34      09-22-99    LAM          added updatedownspeed prototype     */
/*   2.35      11-03-99    JLH          added MAX_VECTOR_SIZE, PVSTART,     */
/*                                       PVADJUST1, and PVADJUST2 #defines  */
/*   2.36      11-04-99    JLH          Replace tabs with equivalent spaces.*/
/*   2.36.1.0  04-03-02    LAM          Added UpdateNVRSpringRate prototype */
/*   2.36.1.1  04-10-02    LAM          added LC_OFFSET                     */
/*   2.36.1.2  05-17-02    LAM          added global variable loadcelloffset*/
/*   2.38      08-05-03    BEKymer      Merged 2.37 and 2.36.1.2 to create  */
/*                                       2.38 for 9.00A build               */
/*                                      -Add argument to functions as now   */
/*                                       required by menu structure         */
/*	  2.39      09-22-09    YGupta        Removed unused function definations.*/
/*                                                                          */
/*                                                                          */
/*------------------------- Defines ----------------------------------------*/

enum CALSTATUS {  
   CAL_PASSED = 1,                 /*                                       */
   CAL_FAILED,                     /*                                       */
   CAL_ABORTED,
   CAL_NOT_ALLOWED };              /*                                       */

#define SPRING_RATE_SIZE       40
#define MAX_VECTOR_SIZE        31   /* accomodates 6-inch stroke */
#define PVSTART       (45220-3500)  /* 7.74% above minimum; see InitForce2 function */
#define PVADJUST1      5544         /* 12.26% adjustment; see InitForce3 function */
#define PVADJUST2      4522         /* 10% adjustment; see CollectForceData function */

#define LOW_60PSI    48000     //   16 bit D/A inputs from 0 to 65535 Verified
                               //   using #5 AEF actuator
#define HIGH_60PSI   -16333    //   Velocity table has a 65535 offset added to it   
#define LC_OFFSET      1000         /* Offset in version 6.XX and 8.06 and above */   

#define MAX_MENUS 15


/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

void BuildPressureTable(void);
void VerifyPressureTable(void);
void BuildPVPTable(void);
void BuildVelocityTable(void);
void CalibFinalCleanup(void);
void UpdateSpringRate(void);
void CalibrationInit(void);
void ShowCalibrationAbort(void);
void GetDefSpringRateTable(void);
void DistanceVerifyInit(UINT32);
void BuildDefaultSpringRate(void);
void InitForce1(void);
void InitForce2(void);
void InitForce3(void);
void CheckSpringRate(void);
void TestTimer(void);
void ExitCalWait(void);
void InitCalWait(void);
void InitCalTimer(void);
void Reading1(void);
void Reading2(void);
void ReadA2D2(UINT32);
void ReadLoadCell(void);
void CollectForceData(void);
void CalExitPB(void);
UINT16 CalibrationAllowed(void);
void DisplayNextScreen(void);
void UpdateDownSpeed(void);
void UpdateNVRSpringRate(void);


#ifdef SNSRCALB                  /******************************************/
#define Snsrtype                 /* This cute little trick will allow all  */
#else                            /* uninitialized variables to be defined  */
#define Snsrtype  extern         /* in one file.  In Main.c GLOBAL should  */
#endif                           /* be defined.                            */
                                 /******************************************/

/*-------------  Global variables  --------------------------*/
Snsrtype UINT16 LoadCellOffset;
