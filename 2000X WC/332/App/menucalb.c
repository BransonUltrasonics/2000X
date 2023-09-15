/* $Header:   D:/SWLab/VMdb/2000Series/App/MENUCALB.C_V   2.96.1.4   22 Sep 2009 12:03:30   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Menucalb                                                    */
/*                                                                          */
/* Filename:    Menucalb.c                                                  */
/*                                                                          */
/* Function Name: Menus for calibration                                     */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   04-20-96                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date       Author       Description                          */
/*  =========  ========   ===========  ===========                          */
/*     0       04-40-96   BEKymer      Original write of menu's             */
/*     1       05-03-96   BEKymer      Move 'Please Wait' msg down          */
/*     2       06-06-96   BEKymer      Remove all ContinueFlag refs         */
/*     3       06-11-96   BEKymer      Put back BuildForceTable in menu 10  */
/*                                     Call DistanceVerifyInit before       */
/*                                       VerifyDistance menu is displayed   */
/*     4       06-25-96   BEKymer      Add in call for AdjustSpringRate1    */
/*     5       07-08-96   LAM          deleted call for AdjustSpringRate1   */
/*     6       07-30-96   BEKymer      Remove page 12 of calibration        */
/*                                     Change text in MX_9B from 70 to 50   */
/*     7       08-01-96   BEKymer      Change text in MX_9A from 20 to 10   */
/*                                     New page 5 menu for load cell        */
/*     8       08-02-96   BEKymer      Moved Force menus to Menu5.c         */
/*     9       08-08-96   LAM          fixed calibration screens            */
/*    10       10-18-96   LAM          updated loadcell and pressure values */
/*                                     when enter is pressed                */
/*    11       01-01-96   LAM          deleted extra screens                */
/*    12       01-28-97   LAM          deleted unused vars                  */
/*    13       02-11-97   PhilJ        Change subVerifyDistance actuator    */
/*                                     to DONTCARE                          */
/*    14       05-06-97   LAM          made menus constants                 */
/*    15.2.25  07-25-97   LAM          added power calibration              */
/*    15.2.26  07-31-97   LAM          redid power calibration              */
/*                                     added qsend to weldmngr.c            */
/*    15.2.27  08-15-97   LAM          added please wait screen             */
/*    15.2.28  08-21-97   LAM          redid calibration screen             */
/*    15.2.30  08-27-97   LAM          deleted powertstflag                 */
/*    15.2.32  09.04.97   JBerman      Replaced ADVANCED with NORMAL        */
/*    2.33     09.11.97   LAM          unit test version, made lc cal AED   */
/*    2.34     12.12.97   LAM          moved where powercleanup is called   */
/*    2.35     12.22.97   LAM          temporarily remove power calibration */
/*    2.36     12.23.97   LAM          temporarily remove cal standards     */
/*    2.37     12.23.97   LAM          put back cal standards               */
/*    2.38     01.19.97   LAM          temporarily remove cal standards     */
/*    2.39     01.28.97   LAM          made cal standards model5            */
/*    2.40     03.30.98   LAM          made force calibration AED,Model 4   */
/*                                     updated screens per ORS2.01          */
/*    2.41     04.23.98   LAM          added reset calibration tables       */
/*    2.42     05.01.98   LAM          added calibration cleanup when exiting */
/*                                     calibration with the main or goback key */
/*    2.43     05.04.98   LAM          get defaults from the nvram          */
/*    2.44     05.14.98   LAM          donot allow calibration when welding */
/*    2.45     05.22.98   BJB          Converted LoadCellReadingMax to      */
/*                                      tenths of pounds.                   */
/*                                     Changed format of PowerReading1,2,3  */
/*                                      to INTEGER from FORCE, these aren't */
/*                                      really force readings.              */
/*    2.46     06.01.98   LAM          added failed string, chged AED to    */
/*                                     AED | AEF                            */
/*    2.47     06.11.98   LAM          added disable key function to eliminate */
/*                                     calibration all the time             */
/*    2.48     06.19.98   LAM          added text screen after calibration  */    
/*                                     chged verify text to operation psi   */ 
/*    2.49     06.23.98   LAM          added new menusync  array            */    
/*    2.50     06.25.98   LAM          deleted verify loadcell screens      */    
/*    2.51     07.01.98   LAM          chged screens again                  */    
/*    2.52     07.02.98   LAM          added disable key so cannot advance  */    
/*                                     on start switch screen with pressing */
/*                                     the start switches                   */
/*    2.53     07.23.98   LAM          added verify screen to sensor calib  */    
/*    2.54     07.30.98   LAM          removed verify screen to sensor calib*/    
/*    2.55     07-31-98   BJB          Includes kpresmsg.h, getmsg.h        */
/*    2.56     08-03-98   LAM          changed verify screen                */
/*    2.57     08-26-98   LAM          changed first loadcell point based on*/
/*                                     cylinder size                        */
/*    2.58     09-01-98   LAM          added updating calibration data after*/
/*                                     resetting calibration tables         */
/*    2.60     10-28-98   LAM          added delay to clear out key buffer  */
/*    2.61     11-02-98   LAM          changed cal standards to cal full system */
/*    2.62     11-11-98   LAM          added extra 5PSI submenu             */
/*    2.63     06-10-99   CMC          CalForceMenuXX changes for AEF       */
/*    2.64     06-10-99   CMC          ch SetPressureToggle to SetPSIToggle */
/*    2.65     06-16-99   LAM          fixed screens per Calibration PART2 spec */
/*    2.66     06-16-99   LAM          fixed redeclaration of variables     */
/*    2.67     06-17-99   LAM          eliminated unused references         */
/*    2.68     06-17-99   LAM          Disabled DisableKey in subContinue9a */
/*    2.68.2.1 07-08-99   JHenry       Various updates for AEF actuator     */
/*    2.68.2.2 07-10-99   JLH          More updates for AEF actuator        */
/*    2.68.2.3 07-15-99   JLH          Various updates by Laura, some may be*/
/*                                      for testing only. Do difference with*/
/*                                      2.68.2.2 to get changes             */  
/*    2.68.2.4 07-16-99   JLH          Updates made during calibration debugging; */
/*                                      debugging not complete.             */
/*    2.68.2.5 07-20-99   JLH          Updates made during calibration debugging; */
/*                                      debugging not complete.             */ 
/*    2.68.2.6 07-20-99   LAM          changed buildvelocitytable to loadcal
                                       velocitytable, moved buildforcetable
                                       to continue instead of enter
      2.68.2.7 07-23-99   JLH          Made updates for 3 load cell readings
      2.68.2.8 07-29-99   LAM          Added function to CalForceMenu5B to save
                                       the calibrated system pressure  
      2.71     08-05-99   LAM          disabled key in CalForceMenu7B
      2.72     09-09-99   JLH          Eliminated last 2 calibration menus.
      2.73     09-09-99   JZ           removed  SetPressureToggle
      2.74     09-09-99   LAM          added force to reset sensor calibration
      2.75     09-20-99   LAM          added slope to reset sensor calibration,
                                       cleanup unused menus
      2.76     10-26-99   JZ           modified ResetSensorCalb()
      2.77     11-03-99   JLH          changed ForceGaugeReadingMin and
                                         ForceGaugeReadingMax to const
      2.78     11-04-99   JLH          Replace tabs with equivalent spaces. 
      2.79     11-06-99   LAM          added consts deleted unused menus    */
/*    2.80.6.1 02-07-00   JZ           removed DVS, added Mask1, Cond1, Mask2, Cond2 */     
/*    2.81.6.2 02-23-00   OFI          removed 'User experience level' from menu strucutures, fixed user security level*/                                                                     
/*    2.80     12-17-99   JZ           fixed compatibility to AED act.      */
/*    2.81     03-31-00   JZ           changed CalForceMenu13Fail, textCalibrationNot, SubContinueFail13 */      
/*                                     deleted subContFail13AEF             */
/*    2.82     04-05-00   JZ           merged Lang to trunk                 */
/*    2.83     05-26-00   SCM          Checked in for testing by Laura, John.*/
/*    2.84     06-14-00   SCM          Replaced array index-20 with 'define' LINESIZE.*/
/*    2.85     06-28-00   BEKymer      Changed all MODEL to LEVEL                      */
/*    2.86     08-14-00   LAM          Fixed calibration saved screen                 */
/*    2.87     10-31-00   LAM          Fixed reset sensr cal. Issue(3661)             */
/*    2.87.1.0  05-06-02  LAM          Added error code test to reset sensr cal.      */
/*    2.87.1.1  05-08-02  LAM          Added record alarm to reset sensr cal.      */
/*    2.87.1.2  05-17-02  LAM          only record alarm to reset sensr cal with an AED */
/*    2.87.1.3  07-21-03  JOY          QVGA menu Sync checking is added in 'WaitForMenu()'*/
/*                                     'CalMenus[]' populated with QVGA Calib menus for  */
/*                                     calibration synchronization.                     */
/*    2.88     01-16-01   BEKymer      Added argument to TEXT and SUBMENU structure calls  */
/*    2.89     08-04-03   BEKymer      Merged 2.88 and 2.87.1.2 to create 2.89 for 9.00A build  */
/*    2.90     12-04-03   BEKymer      Merged 2.89 & 2.87.1.3 to create 2.90 for       */
/*                                     Ver9.00b build                                  */
/*    2.91     04-11-05   LAM          Added SBeam                                     */                                                                                
/*    2.92     04-11-05   LAM          corrected formatting issue                      */                                                                                
/*    2.93     04-26-05   LAM          deleted unused pwrcalb                          */ 
/*    2.94     07-25-05   Bwadia       Asian Language support for Calib menu           */                                                                                
/*    2.95     08-19-05   Bwadia       IsHWConfigured function used to check for       */
/*                                     VGA hardware presence                           */  
/*    2.96     12-22-06   NHAhmed      Added pop up before entering the Sensor Cal Screen.*/
/*    2.97     04-14-08   NHAhmed      Modified functions WaitForMenu().               */
/*    2.98     09-02-08   NHAhmed      CleanUp for multi-language support.             */      
/*    2.99     09-09-08   NHAhmed      CleanUp for multi-language support.             */      
/*    2.100    10-01-08   NHAhmed      Modifed function InitCalMenus().                */      
/* 2.96.1.3.1  09-22-09   YGupta       Added support for MICRO Actuator and Tracker BUG00472.*/
/*----------------------------- DESCRIPTION --------------------------------*/

/* This file will deal with the Calibrate and Verify menus.                 */


/*----------------------------- PSEUDO CODE --------------------------------*/


#define MENUDELAY 50

/*---------------------------- LOCAL_EQUATES -------------------------------*/



/*------------------------------ INCLUDES ----------------------------------*/

#include "psos.h"
#include "menu.h"
#include "menucalb.h"
#include "actnvram.h"
#include "menu5.h"
#include "menu7a.h"
#include "param.h"
#include "ticks.h"
#include "snsrcalb.h"
#include "rtclock.h"
#include "string.h"
#include "fpk_task.h"
#include "preset.h"
#include "selctkey.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "ready.h"
#include "alarms.h"
#include "qvgamenu.h"
#include "statedrv.h"

/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/



/***   ***   Variables needed   ***   ***/
extern BOOLEAN QVGASnsrCalibAllowed;
extern  BOOLEAN VerifyDistancePass, VerifyDistanceFail;
SINT32  UserPressure[3];

UINT8 CalMenus[MAX_MENUS];
UINT16 MenuPointer = 0;

const SINT32  ForceGaugeReadingMin = 0;     /* Lowest acceptable force reading    */
const SINT32  ForceGaugeReadingMax = 999;   /* Highest acceptable force reading   */
const SINT32  LoadCellReadingMin = 0;       /* Lowest acceptable loadcell reading */
const SINT32  LoadCellReadingMax = 72000;   /* Highest acceptable reading         */
const SINT32  PowerReadingMin = 1;          /* Lowest acceptable force reading    */
const SINT32  PowerReadingMax = 3500;       /* Highest acceptable force reading   */
UINT8 MenuNxtPointer = 0;

/*-------------------------- Function Prototypes ---------------------------*/

void ResetSensorCalb(void);

/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern QVGA_MENU_INFO MenuLevelInfo[];
extern BOOLEAN QVGACalAllowed;
extern SINT32 ForceV[];

extern BOOLEAN AdvanceMenuFlag;
extern CONFIGSETUP CurrentSetup;
void LangStrCpy(SINT8 * to, SINT8 * from);
/*-------------------------------- CODE ------------------------------------*/



void InitCalMenus(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when the calibration is allowed. This initializes*/
/* the menu array and sets up the string for the first loadcell point       */
/*                                                                          */
/* Inputs :  StrMX_9G - Set to 15PSI                                        */
/*           StrMX_9H - Set to 25PSI                                        */
/*           CurrentSetup.CylinDiameter                                     */
/*                                                                          */
/* Outputs : FirstPointStr - displayed when the pressure calibration passes */
/*           CalMenus - array of the calibration menus                      */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 i= 0;
   MenuNxtPointer = 0;
   if((CurrentSetup.Actuator == AED)||
	   (CurrentSetup.Actuator == MICRO))
   {
      if(QVGASnsrCalibAllowed)
      {
         CalMenus[i++] = 1;//(MENU *) QVGACalForceMenu2;
         CalMenus[i++] = 2;//(MENU *) QVGACalForceMenu3;
         CalMenus[i++] = 3;//(MENU *) QVGACalForceMenu4;
         CalMenus[i++] = 4;//(MENU *) QVGACalForceMenu5;
         CalMenus[i++] = 5;//(MENU *) QVGACalForceMenu5A;
         CalMenus[i++] = 6;//(MENU *) QVGACalForceMenu6Suc;
         CalMenus[i++] = 7;//(MENU *) QVGACalForceMenu7A;
         CalMenus[i++] = 8;//(MENU *) QVGACalForceMenu7B;
         CalMenus[i++] = 9;//(MENU *) QVGACalForceMenu8;
         CalMenus[i++] = 10;//(MENU *) QVGACalForceMenu9a;
         CalMenus[i]   = 11;//(MENU *) QVGACalForceMenu12;
      }
      else
      {
         CalMenus[i++] = 1;//(MENU *) CalForceMenu2;
         CalMenus[i++] = 2;//(MENU *) CalForceMenu3;
         CalMenus[i++] = 3;//(MENU *) CalForceMenu4;
         CalMenus[i++] = 4;//(MENU *) CalForceMenu5;
         CalMenus[i++] = 5;//(MENU *) CalForceMenu5A;
         CalMenus[i++] = 6;//(MENU *) CalForceMenu6Suc;
         CalMenus[i++] = 7;//(MENU *) CalForceMenu7A;
         CalMenus[i++] = 8;//(MENU *) CalForceMenu7B;
         CalMenus[i++] = 9;//(MENU *) CalForceMenu8;
         CalMenus[i++] = 10;//(MENU *) CalForceMenu9a;
         CalMenus[i] = 11;//(MENU *) CalForceMenu12;
      }
   }
   else
   {
      if(QVGASnsrCalibAllowed)
      {
         CalMenus[i++] = 1;//(MENU *) QVGACalForceMenu2;
         CalMenus[i++] = 2;//(MENU *) QVGACalForceMenu3;
         CalMenus[i++] = 3;//(MENU *) QVGACalForceMenu4;
         CalMenus[i++] = 4;//(MENU *) QVGACalForceMenu5;
         CalMenus[i++] = 5;//(MENU *) QVGACalForceMenu5A;
         CalMenus[i++] = 6;//(MENU *) QVGACalForceMenu5B;
         CalMenus[i++] = 7;//(MENU *) QVGACalForceMenu6Suc;
         CalMenus[i++] = 8;//(MENU *) QVGACalForceMenu7B;
         CalMenus[i++] = 9;//(MENU *) QVGACalForceMenu8;
         CalMenus[i++] = 10;//(MENU *) QVGACalForceMenu9AEF;
         //CalMenus[i++] = 11;//(MENU *) QVGACalForceMenu10AEF;
         //CalMenus[i++] = 12;//(MENU *) QVGACalForceMenu11AEF; 
         CalMenus[i] = 11;//(MENU *) QVGACalForceMenu12;
      }
      else
      {
         CalMenus[i++] = 1;//(MENU *) CalForceMenu2;
         CalMenus[i++] = 2;//(MENU *) CalForceMenu3;
         CalMenus[i++] = 3;//(MENU *) CalForceMenu4;
         CalMenus[i++] = 4;//(MENU *) CalForceMenu5;
         CalMenus[i++] = 5;//(MENU *) CalForceMenu5A;
         CalMenus[i++] = 6;//MENU *) CalForceMenu5B;
         CalMenus[i++] = 7;//(MENU *) CalForceMenu6Suc;
         CalMenus[i++] = 8;//(MENU *) CalForceMenu7B;
         CalMenus[i++] = 9;//(MENU *) CalForceMenu8;
         CalMenus[i++] = 10;//(MENU *) CalForceMenu9AEF;
         //CalMenus[i++] = 11;//(MENU *) CalForceMenu10AEF;
         //CalMenus[i++] = 12;//(MENU *) CalForceMenu11AEF; 
         CalMenus[i] = 11;//(MENU *) CalForceMenu12;
      }
   }
   MenuPointer = 0;
}



void WaitForMenu(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when calibration sequence is waiting for the menu*/
/* task. When the correct screen is displayed, then the calibration sequence*/
/* can continue.                                                            */
/*                                                                          */
/* Inputs :  CalMenus - array of the calibration menus                      */
/*                                                                          */
/* Outputs : AdvanceMenuFlag - set to TRUE when screen is displayed         */
/*                                                                          */
/****************************************************************************/ 
{
   if((QVGACalAllowed || QVGASnsrCalibAllowed) )
   {
	   if(CurrentSequence == CALIBRATION)
	   {
			if(MenuNxtPointer == CalMenus[MenuPointer]) 
				AdvanceMenuFlag = TRUE;
	   }
	   else
			AdvanceMenuFlag = TRUE;
   }
}



void UpdateCalibrationState(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when calibration sequence is waiting for the menu*/
/* task. When the correct screen is displayed, then the calibration sequence*/
/* can continue.                                                            */
/*                                                                          */
/* Inputs :  CalMenus - array of the calibration menus                      */
/*                                                                          */
/* Outputs : AdvanceMenuFlag - set to TRUE when screen is displayed         */
/*                                                                          */
/****************************************************************************/ 
{
   AdvanceMenuFlag = FALSE;
   MenuPointer++;

}



void ResetSensorCalb(void) {
/****************************************************************************/ 
/*                                                                          */
/* This function copies the default calibration values into the current     */
/* values. It is called from the calibration menu entry. If the default     */
/* table was created from version 8.05, then generate Recal Alarm 1200      */
/*                                                                          */
/****************************************************************************/ 

   UINT16 DateArray[3]; // 3 Words Calibration date: 04 13 1967
   RTC RTCCal;

   RTCCal = RtcReadDateandTime();     /* Get date when calibration complete */
   DateArray[0] = RTCCal.Month;
   DateArray[1] = RTCCal.Day;
   DateArray[2] = RTCCal.Year;
   SetCalibrationDate(DateArray);     
   SetCalibPass((UINT16) CALIBDEFAULT);
   GetDefPressure();        /* Get defaults from the actuator novram */
   GetDefLoadCell();        /* Get defaults from the actuator novram */
   GetDefForce();
   GetDefCalStrokeLen();
   GetDefCalSysPressure();
   GetDefHomeOffset();
   
   SetCalSpringRateSlope(GetDefSpringRateSlope());
   
   SetLoadCell();           /* save them to pressure and loadcell   */                                         
   SetPressure();
   SetForceNVR(); 
   SetCalStrokeLength();
   SetCalSysPressure();
   SetCalHomeOffset();

   tm_wkafter( MS_TO_TICKS( MENUDELAY ));  /* If this isn't here and user hits */
                                           /* key right away, the menu will    */
                                           /* jump to the next screen automatically*/

   if((NVR.LoadCell[0] < NO_LOADCELL_OFFSET) && ((NVR.ActId == NVR_AED) && (NVR.ForceGauge != LOAD_CELL)))
   {
      /* generate recalibrate alarm with error code 1200 set */
      RecordErrorCode( ERRORCODE1200_EQ20 );
      RecordAlarm( EQ20 );   /* Recalibrate Actuator */
   }
   if (!IsHWConfigured(VGA))
   {
      ClearKeypadBuffer(TRUE);
      SendFakeKeyPress(GoBackKey);
   }
}

