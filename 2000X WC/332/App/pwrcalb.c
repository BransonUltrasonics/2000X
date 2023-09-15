/* $Header:   K:/APPS/PVCS Pro/332new/App/PWRCALB.C_V   1.23   29 Mar 2001 14:33:24   BKymer  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Power Calibration                                           */
/*                                                                          */
/*                                                                          */
/* Function Name: Power Calibration code                                    */
/*                                                                          */
/*          Written by:   Laura Markure                                     */
/*                Date:   07-28-97                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision  Date      Author     Description                              */
/*  ========  ========  =========  ===========                              */
/*     0      07-28-97  LAM        Initial release                          */
/*    1.1.1   07-31-97  LAM        added more functions                     */
/*    1.1.2   08-15-97  LAM        added more functions                     */
/*    1.4     08-22-97  LAM        released version                         */
/*    1.5     08-25-97  LAM        added saving of digital filtering        */
/*    1.6     08-27-97  LAM        added setting of trigger                 */
/*    1.7     08-28-97  LAM        added powercal trigger state             */   
/*    1.8     08-29-97  LAM        added timeout                            */   
/*    1.10    09-18-97  LAM        added check for hold testkey pressed     */   
/*    1.11    09-23-97  LAM        added call to keypad mask                */   
/*    1.12    09-24-97  LAM        made timeout 30 seconds                  */   
/*    1.13    10-14-97  LAM        added timeout screen                     */   
/*    1.14    10-15-97  LAM        made sure weld sequence was restored when*/   
/*                                 exitting                                 */
/*    1.15    12-11-97  LAM        test not allowed until exitting calibration*/   
/*    1.16    12-17-97  LAM        made sure not in metric mode             */   
/*    1.17    12-18-97  LAM        fixed timeout in 250w screen             */   
/*    1.18    07-31-98  BJB        Includes kpresmsg.h, getmsg.h            */
/*    1.19    10-28-98  LAM        fixed ccrider warning                    */
/*    1.20    05-26-00  SCM        Checked in for testing by Laura, John.   */
/*    1.20    06-21-00  DJL        Made a few global changes from DigitalFilter to DigitalFilterFlag */
/*    1.21    07-13-00  BEK/DJL    fixed tabs                               */
/*    1.23    01-16-01  BEKymer    Add argument to menu functions as needed */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/

/*  This module includes the support functions for the power calibration.   */


/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

//#define INCLUDE_UNIT_TEST


/*------------------------------ INCLUDES ----------------------------------*/

#include <psos.h>
#include "pwrcalb.h"
#include "preset.h"
#include "ready.h"
#include "interpol.h"
#include "wldstate.h"
#include "statedrv.h"
#include "state.h"
#include "spidd.h"
#include "digout.h"
#include "keypad.h"
#include "selctkey.h"
#include "sysmangr.h"
#include "slopeint.h"
#include "param.h"
#include "vf.h"
#include "opcodes.h"
#include "ck_qsend.h"                     /* contains function interface      */
#include "genrlmsg.h"
#include "display.h"
#include "fpk_task.h"
#include "kpresmsg.h"
#include "getmsg.h"

static GENERIC_MSG WeldMsgOut;

/*-------------------------- GLOBAL DATA ---------------------------*/

BOOLEAN SonicsOffFlag = FALSE;
BOOLEAN TestDelayFlag = TRUE,PowerOkFlag = FALSE;
static UINT16 TestDelayTimer = 0;
static UINT32 A2DPowerReading1;
static UINT32 A2DPowerReading2;
extern UINT16 CalibrationPassed;
#define TESTACTIVETIME 30000
#define MAXTOLERANCE 30
UINT16  OldUnits,OldDigFilter, PowerAbortFlag;
UINT16 j;

/*-------------------------- EXTERN DATA ---------------------------*/

extern STATE  *WeldSequence[NMBR_OF_STATES];      /* Current weld cycle definition */
extern enum   WELD_SEQUENCE_TYPE CurrentSequence;
extern CONFIGSETUP CurrentSetup;
extern SETUPS_Ver800  RunningPreset;
BOOLEAN PwrTestFlag = FALSE;
extern UINT32 WmgrQid;
extern UINT32 CalbAve[];
extern SINT32 PowerSetting1;
extern SINT32 PowerSetting2;
extern UINT16 TempSpringRateTable[];
extern UINT16 FilterPower[];  /* A2D reading */

extern const STR *const StrM5A_1[];  /* POWER CAL   */
extern const STR *const StrM5A_6[];  /* Calibration */
extern const STR *const StrM5A_9[];  /* Timed Out   */
extern const STR *const StrME_10[];  /* Press Go Back */
extern UINT16 LangIndex;

/*-------------------------------- CODE ------------------------------------*/


void RequestCalPower(UINT32 MenuExtra){

   WeldMsgOut.common.opcode = OP_CALIB_POWER;
   CkQSend (WmgrQid,&WeldMsgOut,FRONT_PANEL_KEY_PAD_TASK,__LINE__,        
                    MILLS_TO_TICKS(20));

}
void PowerCalInit(void)
{
   UINT16 i;

   for(i=0; i < MAX_CAL_PTS; i++){
      TempSpringRateTable[i] = (UINT16) CurrentSetup.PwrOutTable[i];
    }
   PwrTestFlag = FALSE;
   CalibrationPassed = FALSE;
   SonicsOffFlag = FALSE;
   TestDelayFlag = TRUE;
   TestDelayTimer = 0;
   PowerSetting1 = 0;
   PowerSetting2 = 0;
   PowerOkFlag = FALSE;
   OldDigFilter = RunningPreset.DigitalFilterFlag;
/* disable metric */
   OldUnits = CurrentSetup.Units;
   CurrentSetup.Units = FALSE;
   RunningPreset.DigitalFilterFlag = FALSE;
   PowerAbortFlag = FALSE;
}

void ClearPwrFlg(void){
// Start sonics off timer
   TestDelayFlag = TRUE;
   TestDelayTimer = 0;
}



void SelectPowerCalSequence(void)
/***************************************************************************/
/*                                                                         */
/* This is the Sensor Calibration state sequence.                          */
/*                                                                         */
/***************************************************************************/
{
   UINT16 i = 0;

   ResetStateMachine();                /* Turn off the state machine first */

   WeldSequence[i++] = &CalTopOfList;  /* enter the sequence of states */

   /* CalPowerMenu  wait for next menu to be displayed */
                                       /*----------------------*/
                                       /* CAL POWER            */
                                       /* Select Test Key      */
                                       /*                      */
                                       /*----------------------*/

   WeldSequence[i++] = &PwrPage1Wait;  /* Wait for Page to exit*/

   /* CalPowerMenu1 wait for next menu to be displayed */
   WeldSequence[i++] = &CollectPwr1;   /*----------------------*/
                                       /* CAL POWER            */
                                       /* Load to approx.      */
                                       /* 100 watts            */
                                       /*             Calibrate*/
                                       /*----------------------*/

   /* CalPowerMenu2 wait for next menu to be displayed */
                                       /*----------------------*/
   WeldSequence[i++] = &MenuSyncST;    /* CAL POWER            */
                                       /* Enter watt meter     */
                                       /* value        =xxxx   */
                                       /*             Continue */
                                       /*----------------------*/

   /* CalPowerMenu3 wait for next menu to be displayed */
                                       /*----------------------*/
                                       /* CAL POWER            */
                                       /* Select Test Key      */
                                       /*                      */
                                       /*----------------------*/

   WeldSequence[i++] = &PwrPage2Wait;  /* Wait for Page to exit*/

   /* CalPowerMenu4 wait for next menu to be displayed */
   WeldSequence[i++] = &CollectPwr2;   /*----------------------*/
                                       /* CAL POWER            */
                                       /* Load to approx.      */
                                       /* 400 watts            */
                                       /*             Calibrate*/
                                       /*----------------------*/


   /* CalPowerMenu5 wait for next menu to be displayed */
                                       /*----------------------*/
                                       /* CAL POWER            */
                                       /* Enter watt meter     */
                                       /* value         =xxxx  */
                                       /*            Continue  */
   WeldSequence[i++] = &MenuSyncST;    /*----------------------*/

   /* CalPowerMenu6 wait for next menu to be displayed */
                                       /*----------------------*/
                                       /* CAL POWER            */
                                       /* Select Test Key      */
                                       /*                      */
                                       /*----------------------*/

   WeldSequence[i++] = &PwrPage3Wait;  /* Wait for Page to exit*/
   /* CalPowerMenu7 wait for next menu to be displayed */
   WeldSequence[i++] = &CollectPwr3;   /*----------------------*/
                                       /* CAL POWER            */
                                       /* Load to approx.      */
                                       /* 250 watts            */
                                       /*             Calibrate*/
                                       /*----------------------*/

   /* CalPowerMenu8 wait for timeout here */
                                       /*----------------------*/
                                       /* CAL POWER            */
                                       /* Enter watt meter     */
                                       /* Value          =xxxx */
                                       /*            Continue  */
   WeldSequence[i++] = &MenuSyncST;    /*----------------------*/


   /* CalPowerMenu9 wait for next menu to be displayed */

   WeldSequence[i++] = &VerifyPower;   /*----------------------*/
   WeldSequence[i++] = &PwrTriggerST;     /* CAL POWER            */
                                       /*     Please Wait      */
                                       /*                      */
                                       /*----------------------*/

                                       /*----------------------*/  /*----------------------*/
                                       /* CAL POWER            */  /* CAL POWER            */
                                       /* Calibration Failed   */  /* Calibration          */
                                       /* See Manual Section   */  /* Successful           */
                                       /* 7.3             Done */  /*                Done  */
   WeldSequence[i++] = &MenuSyncST;    /*----------------------*/  /*----------------------*/
   WeldSequence[i++] = &MenuSyncST;    /*----------------------*/  /*----------------------*/

   /* End of Calibration sequence */
   WeldSequence[i]   = &CalEndOfList;
   CurrentSequence = POWERCAL;

   PowerCalInit();
   StopDataCollection();                /* Stop the weld data collection */
   ClearAbort();
   ClearAlarmFlag();                    /* Clear all alarms from last cycle */
   UpdateKeyMask(POWERCALMODEMASK);
   StartStateMachine();                 /* Start the state machine here     */
}


void CheckPower(UINT32 MenuExtra){
   
   UINT16 k;
   
   for(k = 0;k < 20; k++)
      A2DPowerReading2 += CalbAve[k];
   A2DPowerReading2 = A2DPowerReading2/20;  /* min fixed */
   A2DPowerReading2 = GetInterpolatedSINT16(CurrentSetup.PwrOutTable,(UINT16)A2DPowerReading2);
// Power is in 0.1%
   PowerSetting2 = (PowerSetting2 * 1000) / CurrentSetup.PSWatt;
   if((CalibrationPassed == TRUE) && (TestDelayFlag == TRUE)) {
      if(PowerSetting2 > A2DPowerReading2){
         if((PowerSetting2 - A2DPowerReading2) >= MAXTOLERANCE)
            PowerOkFlag = FALSE;
         else
            PowerOkFlag = TRUE;
      }
      else{
         if((A2DPowerReading2 - PowerSetting2) >= MAXTOLERANCE)
            PowerOkFlag = FALSE;
         else
            PowerOkFlag = TRUE;
      }
   }
   else
      PowerOkFlag = FALSE;
// advance state machine
   TestDelayFlag = FALSE;
};


void PowerCleanupArg(UINT32 MenuExtra)
/*****************************************************************************/
/*  This function simply calls PowerCleanup without passing as argument.  It */
/*  is needed because sometimes PowerCleanup is called from the menu system  */
/*  with an argument and sometimes without an argument.                      */
/*****************************************************************************/
{
   PowerCleanup();
}


void PowerCleanup(void){

   UINT16 i;
   
   TurnOffSonics(0);
   if(PowerOkFlag == TRUE){
      BackupCurrentSetupChange(SAVECURRENTSETUP);
   }
   else{
      for(i=0; i < MAX_CAL_PTS; i++){
         CurrentSetup.PwrOutTable[i] = TempSpringRateTable[i];
         }
     }
   RunningPreset.DigitalFilterFlag = OldDigFilter;
   CurrentSetup.Units = OldUnits;
   SelectWeldSequence();               /* Restore proper weld sequence      */
   StartStateMachine();                /* Start the state machine here     */
   SetReady();
/* Force Main Menu key */
   SendFakeKeyPress(MainKey);
};

void PowerCalAbort(void){

   UINT16 i;
   
   TestDelayFlag = TRUE;
   UpdateLine((SINT8 *)StrM5A_1[LangIndex], 1);
   UpdateLine((SINT8 *)StrM5A_6[LangIndex], 2);
   UpdateLine((SINT8 *)StrM5A_9[LangIndex], 3);
   UpdateLine((SINT8 *)StrME_10[LangIndex], 4);
// Wait for go back key
   UpdateKeyMask(POWERABORTMASK);
   TurnOffSonics(0);
   for(i=0; i < MAX_CAL_PTS; i++){
      CurrentSetup.PwrOutTable[i] = TempSpringRateTable[i];
   }
   RunningPreset.DigitalFilterFlag = OldDigFilter;
   CurrentSetup.Units = OldUnits;
}


void TurnOffSonics(UINT32 MenuExtra){

   TestDelayTimer = 0;
   PSIdle();
   SonicsOffFlag = TRUE;
};


void InitPwr(void){
   j = 0;
}

void ReadingPower(void){
 
   if(TestDelayTimer++ > TESTACTIVETIME){
      TestDelayFlag = FALSE;
   }
   if(FilterPower[0] > 0){
      CalbAve[j++] = FilterPower[0];
      if(j >= 20 ){
         j = 0;
      }
   }
}

void RecordPower1(UINT32 MenuExtra){
   UINT16 k;
/* make sure pressure doesn't change during calibration */
   for(k = 0;k < 20; k++)
      A2DPowerReading1 += CalbAve[k];
   A2DPowerReading1 = A2DPowerReading1/20;  /* min fixed */
   SonicsOffFlag = FALSE;
   PwrTestFlag = FALSE;
}

void RecordPower2(UINT32 MenuExtra){
   UINT16 k;
/* make sure pressure doesn't change during calibration */
   for(k = 0;k < 20; k++)
      A2DPowerReading2 += CalbAve[k];
   A2DPowerReading2 = A2DPowerReading2/20;  /* min fixed */
   SonicsOffFlag = FALSE;
}

void BuildPowerTable(UINT32 MenuExtra)
{

   RecordPower2(0);
// Power is in 0.1%
   PowerSetting1 = (PowerSetting1 * 1000) / CurrentSetup.PSWatt;
   PowerSetting2 = (PowerSetting2 * 1000) / CurrentSetup.PSWatt;
   CalibrationPassed = UpdatePowerTable(CurrentSetup.PwrOutTable,
       (UINT16) PowerSetting1,(UINT16) PowerSetting2,A2DPowerReading1,          A2DPowerReading2);
   PowerSetting2 = 0;
   PwrTestFlag = FALSE;
}

UINT16 UpdatePowerTable(SINT16 TableVals[], UINT16 Y1, UINT16 Y2,
      UINT16 X1, UINT16 X2)
/****************************************************************************/
/*                                                                          */
/* Notes: 1 - A value of 0.5 is added to b for rounding off.                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
{
   UINT16 Index,StepSize=0x100;   /* Table entries must be in 100 Hex steps */
   UINT16 TableUpdated = FALSE;
   FLOAT m,b;
   SINT16 RetVal;

   RetVal = SlopeInterceptCalc(Y2, Y1, X2, X1, &m, &b);
   if (RetVal != -1) {    /* divide by zero check */
      TableUpdated = TRUE;
      b += (FLOAT)0.5;
      TableVals[0] = (SINT16) b; /* Offset calculated by 2 point line equation y=mx+b */
      if(TableVals[0] < 1) TableVals[0] = 0;
      for(Index = 1; Index < MAX_CAL_PTS; Index++){
         TableVals[Index] = (SINT16)( (m * (FLOAT)StepSize * (FLOAT)Index) + b);
      }
   }
   return(TableUpdated);
}



/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "G:\332\ut\snsrcalb.ut"
#endif
/* End of include for unit test */


