/* $Header:   D:/SWLab/VMdb/2000Series/App/runresults.c_v   1.53   22 Sep 2009 11:54:56   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 2009           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
/*
---------------------------- MODULE DESCRIPTION -------------------------------

     Module name:

        Filename: runresults.c

      Written by: JOY 
            Date: 04/28/2003 
        Language: "C"

--------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========       ======      ===========
      1.0          04/28/03       JOY        Initial Version
      1.5          06/23/03       JOY        Moved Language strings to "menutext.c".  
      1.6          07/31/03       LAM        split velocityitem into velocityitemaed & velocityitemaef  
      1.7          08/10/03       JOY        Added 'QVGABUCSubmenu' to the 'RunMenu'.
                                             Added Alarm button processing.
      1.8          08/26/03       JOY        Added function'QVGA AlarmReset()'.
      1.9          09/05/03       JOY        Weld status Green box size is Increased
                                             -#Tracker Issue 3733.
                                             Screen Setup Calib points are changed.
      1.10         09/19/03       JOY        'Setup Screen' Texts are made same as ORS.
      1.11         09/25/03       JOY        Weld Result line turned red, in case of
                                             -Suspect/Reject Limit alarms.
      1.12         09/27/03       JOY        Added 'Done' button in Setup Screen.
      1.13         10/03/03       JOY        Ready state is cleared in setup screen
                                             - to disable 'TestKey'.
      1.15         10/10/03       JOY        Added 'VelocityItemaef' to the RunMenu.
      1.16         10/16/03       JOY        Changed Calibration text.
      1.17         10/16/03       LAM        Renamed str_calibdone to strm3_9.
      1.18         10/23/03       JOY        Added Button Release Beep.
                                             TheMainMenu replaced with QVGATheMainMenu.
      1.19         10/29/03       JOY        Contrast Buttons are centered to the screen.
      1.20         11/07/03       LAM        made eraseparam rectangle 3 pixels less
      1.22         12-09-03       BEKymer    Add arguments to functions called
                                              from SUBMENU's and TEXT structure.
      1.23         02-20-04       VSharma    Added PresetNumItem in RunMenu.
                                             Modified GetUnit_Value() for RPRESETNUM.
                                             Modified QVGAAlarmReset().
      1.24         03-28-04       LAM        merged 8.21 version                                         
      1.25         04-06-04       VSharma    Exit from AlarmUserIOMenu,when ResetKey
                                              pressed.
      1.26         04-19-04       VSharma    Changed ExitUserIOMenu() to ExitMenuAndEnableWeld().
      1.27         05-07-04       LAM        merged 8.22 version
      1.28         05-17-04       VSharma    Removed extern of unused strings. 
      1.29         06-18-04       BEKymer    Changed RVELOCITY to RVELOCITY_AED
                                              and RVELOCITY_AEF
      1.30         08-20-04       JOY        Submenu HornDown not displayed in DEPO mode.
      1.31         05-04-05       LAM        Remove contrast control
      1.32         07-25-05       Bwadia     QVGA clean up and VGA support for run screen
                                             for Ver10.0e
      1.33         08-10-05       Bwadia     GetUnit_value function modified to take care of 
                                             hangup at power up when weld data is present
      1.34         09-10-05       Bwadia     Weld data for all parameters sent for print
                                             feature in VGAWeldParams function. 
      1.35         09-11-05       Aare       Merged 10f and 10h
      1.36         09-16-05       Bwadia     VGAWeldPArams function changed so that
                                             weld parameters are sent as single byte
                                             for asian languages also
      1.37         10-11-05       Bwadia     Total cycle time added to list of weld param
                                             columns      
      1.38         11-02-05       Aare       Corrected total cycle time column to read
                                             correct variable.
      1.39         12-07-05       Bwadia     Global counter sent in VGA run screen object.
                                             Preset name also sent along with Weld state
                                             change command. Modified for tracker issue 
                                             4026 and 4030
      1.40         01-03-06       Bwadia     DiagFlag set to FALSE when Alarm button pressed.
                                             Modified for tracker issue 3972
      1.41         01-12-06       Bwadia     Column setup button added on run screen
                                             Modified for tracker issue 4042    

     1.42         01-20-06       Bwadia     VGANextButton shows up only if DUPS present
                                            Modified for tracker issue 4060 
     1.43         04-05-07       NHAhmed    Modified the WeldStateText to remove the green box 
                                            from the weld result scrren.
     1.44         05-04-07       NHAhmed    Added Previous button in System Info (Tracker #4115).
     1.45         05-23-07       NHAhmed    Added Print Button on the Run Screen.
     1.46         06-01-07       YGupta     Modified Print Button on the Run Screen to come up for all models.
     1.47         04-14-08       NHAhmed    Replicated functions with some modifications. Added a function
                                            CountActiveParameters().
     1.48         08-01-08       NHAhmed    Modifed function GetUnit_Values().
     1.49         09-02-08       NHAhmed    CleanUp for multi-language support.
     1.50         09-04-08       YGupta     CleanUp for LangTest Project.
     1.51         09-09-08       NHAhmed    CleanUp for multi-language support.
     1.52         09-10-09       BEkymer    Add new define MICRO where needed
	  1.53         09-22-09       YGupta     Modified so that HD will not exit in case of ALARM Menu.
     
     
*/
/*
 ------------------------------- DESCRIPTION ---------------------------------
*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "string.h"
#include "menu.h"
#include "menu1.h"
#include "menu3.h"
#include "menu5.h"
#include "preset.h"
#include "prsetprn.h"
#include "display.h"
#include "dups_api.h"
#include "weld_obj.h"
#include "battram.h"
#include "graphs.h"
#include "sc.h"
#include "DRAWSCRN.h"
#include "QVGAMENU.h"
#include "screenmsg_touch.h"
#include "portable.h"
#include "ticks.h"
#include "genalarm.h"
#include "digout.h"
#include "statedrv.h"
#include "command.h"
#include "param.h" 
#include "menu7a.h"
#include "serial.h"

#define MAX_RUN_RESULT_PARAM     5
#define UNIT   0
#define VALUE  1
#define MAX_RUNSCREEN_CYCLES 7
#define EXIT_HD 1
#define TRIGFORCEPARAM 24
/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                         (scope is global to THIS file)
*/
static WELD_DATA LastRunResults;
/*
 --------------------------- EXTERNAL FUNCTION PROTOTYPES -------------------------
*/
void GetCurrentPresetNames(void);
void GetParamName(UINT32 index);
void SetRunScreenParam(void);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
void VGAAlarmReset (UINT32 dummy);
void CalibFinalCleanup(void);
void QVGAExitTestSequence(void);
void ExitMenuAndEnableWeld(void);
void CheckforCalib(void);
void VGAProcessHornDownMsg (void);
UINT16 LangStrLen(SINT8 * str); 
BOOLEAN LangCheckNull(SINT8 * Line);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);
void StrCpyTwoToOneByte(SINT8 * to, SINT8 * from);
SINT8 * Trim_FillChar(SINT8 Str_temp[]);

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern UINT32 SWConfiguration;
extern UINT32 HWConfiguration;
extern SINT32 SecurityLevel;
extern BOOLEAN StartwithRunMenu;
extern BOOLEAN QVGAHDAlarm;
extern BOOLEAN ReadyFlag;
extern BOOLEAN QVGAHornDown;
extern BIT_FLAGS BitFlags;
extern CONFIGSETUP CurrentSetup; 
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern BOOLEAN QVGACalAllowed;
extern BOOLEAN QVGASnsrCalibAllowed;
extern BOOLEAN QVGAAbortHornScan;
extern BOOLEAN StateMachineDisabled;
extern BOOLEAN QVGAHDAlarm;
extern BOOLEAN VGAHistoryData;
extern UINT8 PrevHornState;

extern UINT16 VGAAction;
extern UINT16 DiagFlag;
extern UINT32 PollingCommandCounter;

extern BUCMENU_800   BUCMenuRAM;
extern MENU RunScreenParamMenu[];

extern SETUPS_Ver800    RunningPreset;
extern SETUPS_Ver800 CurrentPreset;
extern UINT8 AlarmDetectedFlag;

extern STR StrWeldStateLine[QVGA_LINESIZE];

/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

MENUEND RunMenuEnd = { TRUE };

const SINT8 tokenChars[] = "()=";
UINT16 TotalCycle;
BOOLEAN AllParamColumnFlag;
UINT16 CalibInProgress = FALSE;
SINT32 MaxNoOfCycles = 50;
SINT32 MinNoOfCycles = 1;
UINT8 RunParameter[25];

/*----------------------------------Menu Structures---------------------------
*/ 

STR CurrentPresetName[QVGA_LINESIZE];
STR PresetNameBuffer[QVGA_LINESIZE];


void GetCurrentPresetNames(void)
/****************************************************************************/
/*Description:-                                                             */
/* Generate Current Preset name from the Preset ID, this Preset name is     */
/* displayed in the WELD_RESULT_SCREEN                                      */
/****************************************************************************/
{
   UINT8 ValidPreset = TRUE;
   UINT16 i;

   if(CurrentPreset.PresetID[0] != 0)
   {
      for(i = 0; i < PRESETLEN && ValidPreset; i++)
      {
         if(CurrentPreset.PresetID[i] != 0)
         {
            if(!ValidPresetCharacter(CurrentPreset.PresetID[i]))
            {
               ValidPreset =  FALSE;
               CurrentPreset.PresetID[0] = NULL; /* Invalid Name, Clear Name */
               CurrentPreset.PresetID[1] = NULL; 
            }
         }
         else
            ValidPreset = FALSE; /* Terminate Loop, Preset Valid */
      }
   }
   
    strcpy(PresetNameBuffer, CurrentPreset.PresetID);
    if(CurrentPreset.PresetUpdateComplete == FALSE)
       strcat(PresetNameBuffer, "*");
    strcpy(CurrentPresetName,PresetNameBuffer);
}

void GetUnit_Values(SINT8 StrUnit_Value[], UINT16 Param, UINT8 Flag)
/****************************************************************************/
/*Description:-                                                             */
/* Populates Weld Parameter Value and Unit in the input string variable     */
/*Input Parameters:-                                                        */
/* Param  : Weld Parameter                                                  */
/* Flag   : Indicates whether Unit/Value of the weld parameter needs to be  */
/*          populated in the input String variable (StrUnit_Value)          */
/****************************************************************************/
{
   SINT32 TempWeldTime;   
   
   switch ( Param )
   {
      case RCYCLECOUNT:
         if (Flag == VALUE)
         {
             if(BitFlags.Cyclebit)
             {
                if(CurrentPreset.WeldMode != CONTINUOUSMODE)
                   FormatVariables( LastRunResults.CycleCount, COUNTER,
                                    StrUnit_Value, LINESIZE, CurrentSetup.Units );
                else
                   strcpy(StrUnit_Value, NUL);            
             }
             else
                strcpy(StrUnit_Value, NUL);
         } 
         break;
         
      case RPRESETNUM:
         if (Flag == VALUE)
         {
             if(BitFlags.PresetNum)
             {
                FormatVariables( LastRunResults.PresetNum, COUNTER,
                       StrUnit_Value, LINESIZE, CurrentSetup.Units );
             }
          
             else
               strcpy(StrUnit_Value, NUL); 
         }
         break;
         
      case RTIME:
            if(BitFlags.Timebit)
            {
               if(CurrentPreset.WeldMode != CONTINUOUSMODE)
               {
                  TempWeldTime = LastRunResults.ActualWeldTime;

                  if (TempWeldTime < 0)  /* Just in case weld time less than 0 */
                     TempWeldTime = 0;   

                  FormatVariables( TempWeldTime, TIME, StrUnit_Value, LINESIZE,
                        CurrentSetup.Units );
                }
                else
                   strcpy(StrUnit_Value, NUL);
            }
            else
               strcpy(StrUnit_Value, NUL);
         break;
         
         case RPKPWR:
               if(BitFlags.PkPwrbit)
               {
            	  if(CurrentSetup.PeakPowerWattsFlag == TRUE)
            	  {
            		  FormatVariables( LastRunResults.PeakPower, WATTS, StrUnit_Value, LINESIZE, CurrentSetup.Units );
            	  }
            	  else
            	  {
            		  FormatVariables( LastRunResults.PeakPower, PERCENTX10, StrUnit_Value, LINESIZE, CurrentSetup.Units );
            	  }
               }
               else
                 strcpy(StrUnit_Value, NUL);
            break;
            
         case RENERGY:
                if(BitFlags.Energybit)
                {
                   if(CurrentPreset.WeldMode != CONTINUOUSMODE)
                   {
                      if(LastRunResults.TotalEnergy < 10000)
                         FormatVariables( LastRunResults.TotalEnergy, ENERGY,
                            StrUnit_Value, LINESIZE, CurrentSetup.Units );
                      else
                         FormatVariables( LastRunResults.TotalEnergy, ENERGYDIV10,
                                   StrUnit_Value, LINESIZE, CurrentSetup.Units );
                    }
                    else
                       strcpy(StrUnit_Value, NUL);            
                 }
                 else
                    strcpy(StrUnit_Value, NUL);
            break;
             
         case RVELOCITY_AED:
         case RVELOCITY_AEF:
               if(((CurrentSetup.Actuator == AEF) && (BUCMenuRAM.VelocityReporting == TRUE))
                   || (CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == MICRO) ) 
               {
                  if(CurrentPreset.WeldMode != CONTINUOUSMODE)                  
                     FormatVariables( LastRunResults.ActualVelocity, VELOCITY,
                                       StrUnit_Value, LINESIZE, CurrentSetup.Units );
                  else
                     strcpy(StrUnit_Value, NUL);                     
               }
               else
                  strcpy(StrUnit_Value, NUL);
            break;
             
         case RWABSDIST:
               if(BitFlags.WeldAbsbit)               
                  FormatVariables( LastRunResults.ActualWeldAbs, DISTANCE,
                                    StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, NUL);
            break; 
            
         case RTABSDIST:
               if(BitFlags.Absbit)              
                  FormatVariables( LastRunResults.ActualTotalAbs, DISTANCE,
                                     StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, NUL);
            break;
             
         case RWCOLDIST:
               if(BitFlags.WeldCollbit)
               {
                  if(CurrentPreset.WeldMode != CONTINUOUSMODE)            
                     FormatVariables( LastRunResults.ActualWeldCollapse, DISTANCE, 
                                      StrUnit_Value, LINESIZE, CurrentSetup.Units );
                  else
                     strcpy(StrUnit_Value, NUL);         
               }
               else
                  strcpy(StrUnit_Value, NUL);
            break; 
            
         case RTCOLDIST:
               if(BitFlags.TtlCollbit)
               {
                  if(CurrentPreset.WeldMode != CONTINUOUSMODE)                 
                    FormatVariables( LastRunResults.ActualTotalCollapse, DISTANCE,
                                     StrUnit_Value, LINESIZE, CurrentSetup.Units );
                  else
                     strcpy(StrUnit_Value, NUL);                   
               }
               else
                  strcpy(StrUnit_Value, NUL);
            break; 
            
         case RAMPSTART:
               if(BitFlags.AmpAbit)
               {
                  if(!(LastRunResults.PSActControlFlags & BIT0))/* If external amplitude, use */
                  {                                         /* canned string. */
                     strcpy(StrUnit_Value, NUL);                    
                  }
                  else
                  {
                     if((CurrentSetup.ControlLevel < LEVEL_ea) || (!(LastRunResults.PSActControlFlags & BIT1)))
                     {
                        strcpy(StrUnit_Value, NUL);        /* Don't say "Amp A" if stepping */                        
                     }
                     if(RunningPreset.WeldMode != CONTINUOUSMODE)
                     {
                         if(CurrentSetup.AmpMicronsFlag==TRUE)
                         {
                        	 FormatVariables( LastRunResults.ActualAmplitudeStart,PERCENT,StrUnit_Value, LINESIZE, CurrentSetup.Units );
                         }
                         else
                         {
                        	 FormatVariables( LastRunResults.ActualAmplitudeStart,MICRONS,StrUnit_Value, LINESIZE, CurrentSetup.Units );
                         }
                     }
                     else
                        strcpy(StrUnit_Value, NUL);
               
                  }
               }
               else
                  strcpy(StrUnit_Value, NUL);
            break; 
            
         case RAMPEND:
               if(BitFlags.AmpBbit)
               {
                  if((RunningPreset.WeldMode != CONTINUOUSMODE) && ((LastRunResults.PSActControlFlags & (BIT1 | BIT0)) == (BIT1 | BIT0)))
                  {
                      if(CurrentSetup.AmpMicronsFlag==TRUE)
                      {
                    	  FormatVariables( LastRunResults.ActualAmplitudeEnd,PERCENT, StrUnit_Value, LINESIZE, CurrentSetup.Units );
                      }
                      else
                      {
                    	  FormatVariables( LastRunResults.ActualAmplitudeEnd,MICRONS, StrUnit_Value, LINESIZE, CurrentSetup.Units );
                      }
                  }
                  else
                    strcpy(StrUnit_Value, NUL);            
               }
               else
                  strcpy(StrUnit_Value, NUL);
            break; 
            
         case RFORCEA:
               if(BitFlags.SetFAbit)
               {
                  if((LastRunResults.PSActControlFlags & BIT4)!=BIT4)
                  {
                     strcpy(StrUnit_Value, NUL);     /* Don't say "Set Force A" if Force stepping */
                     
                  }
                  
                  else if((RunningPreset.WeldMode != CONTINUOUSMODE) &&
                           (CurrentSetup.Actuator == AEF))
                     FormatVariables( LastRunResults.SetForceA, FORCE,
                         StrUnit_Value, LINESIZE, CurrentSetup.Units );
                  else
                     strcpy(StrUnit_Value, NUL);       
            
               }                                                  
               else
                  strcpy(StrUnit_Value, NUL);
            break; 
            
         case RFORCEB:
                if(BitFlags.SetFBbit)
                {
                   if((RunningPreset.WeldMode != CONTINUOUSMODE) &&
                     ((LastRunResults.PSActControlFlags & BIT4) == BIT4) && (CurrentSetup.Actuator == AEF)){
                     FormatVariables( LastRunResults.SetForceB, FORCE,
                       StrUnit_Value, LINESIZE, CurrentSetup.Units );
                   }
                   else
                      strcpy(StrUnit_Value, NUL);
                }
                else
                   strcpy(StrUnit_Value, NUL);
            break; 
            
         case RFORCE:
               if(BitFlags.SetFEndbit)
               {
                  if ( (RunningPreset.WeldMode != CONTINUOUSMODE) && 
                       ( (CurrentSetup.Actuator == AED) ||
                         (CurrentSetup.Actuator == MICRO) ||
                         (CurrentSetup.Actuator == AEF) ) )
                  {
                     FormatVariables( LastRunResults.WeldForceEnd,
                               FORCE, StrUnit_Value, LINESIZE, CurrentSetup.Units );
                  }
                  else
                     strcpy(StrUnit_Value, NUL);
               }
               else
                  strcpy(StrUnit_Value, NUL);
            break;
            
         case RSYSPRESS:
               if(BitFlags.Pressbit)              
                  FormatVariables( LastRunResults.WeldPressure, PRESSURE,
                                    StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, NUL);
            break; 
            
         case RFREQMIN:
               if(BitFlags.FreqMinbit)               
                  FormatVariables( LastRunResults.FrequencyMin, FREQUENCY,
                                    StrUnit_Value, LINESIZE, CurrentSetup.Units );            
               else
                   strcpy(StrUnit_Value, NUL);
            break; 
            
         case RFREQMAX:
               if(BitFlags.FreqMaxbit)         
                   FormatVariables( LastRunResults.FrequencyMax, FREQUENCY,
                                     StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, NUL);
           break; 
           
         case RFREQSTART:
               if(BitFlags.FreqStartbit)        
                  FormatVariables( LastRunResults.ActualFreqStart, FREQUENCY,
                                       StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, NUL);
           break;
           
         case RFREQEND:
                if(BitFlags.FreqEndbit)               
                   FormatVariables( LastRunResults.ActualFreqEnd, FREQUENCY,
                   StrUnit_Value, LINESIZE, CurrentSetup.Units );            
                else
                   strcpy(StrUnit_Value, NUL);
           break;
           
         case RFREQCHG:
               if(BitFlags.FreqChgbit)
                  FormatVariables( LastRunResults.FrequencyChange, FREQOFFSET,
                  StrUnit_Value, LINESIZE, CurrentSetup.Units );
               else
                  strcpy(StrUnit_Value, NUL);
           break; 
           
      case RCYCLETIME:
            TempWeldTime = LastRunResults.CycleTimeResult;
            if (TempWeldTime < 0)  /* Just in case weld time less than 0 */
               TempWeldTime = 0;   

            FormatVariables( TempWeldTime, TIME, StrUnit_Value, LINESIZE,
                  CurrentSetup.Units );
         break;
         
         default:
           break; 
             
      }  
} 

void SetRunScreenParam(void)
/****************************************************************************/
/*Description:-                                                             */
/* Sets Run screen parameters                                               */
/****************************************************************************/
{
   TotalCycle = MAX_RUNSCREEN_CYCLES;
   AllParamColumnFlag = FALSE;
   VGAHistoryData = FALSE;

}

UINT8 GetVGAPresetNameHeader(WELD_DATA *ResultsPtr, SINT8* HeaderLine)
/*--------------------------------------------*
 * Prpare the Preset Header string to display *
 * WeldMode,PresetNum & PresetName.           *
 *--------------------------------------------*/ 
{
   UINT8  VGAWeldMode;

   switch(ResultsPtr->Weldmode)
   {  /* Get the weld mode string.  */
      case TIMEMODE:
         VGAWeldMode = 1;
         break;
         
      case ENERGYMODE:
         VGAWeldMode = 2;
         break;
         
      case PKPOWERMODE:
         VGAWeldMode = 3;
         break;
         
      case COLLAPSEMODE:
         VGAWeldMode = 4;
         break;
         
      case ABSOLUTEMODE:
         VGAWeldMode = 5;
         break;
         
      case GRDDETECTMODE:
         VGAWeldMode = 6;
         break;
         
      case CONTINUOUSMODE:
         VGAWeldMode = 7;
         break;
         
      default:
         VGAWeldMode = 1;
         break;   
   }
   strcpy(HeaderLine, ResultsPtr->PresetName);
   return (VGAWeldMode);
}

UINT16 CountActiveParameters(MENU list[])
{
   UINT16 index = 0;
   UINT16 MenuIndex = 0;
   UINT16 HMaxIndex = -1;
   BOOLEAN SkipFlag;
   RSPARAMETER *menu30;

   while (list[index].type != ENDLIST)
   {
      SkipFlag = FALSE;
      menu30 = (RSPARAMETER *)list[index].ptr;

      if (CurrentSetup.ControlLevel < menu30->CtrlLevel)
         SkipFlag = TRUE;
      else if (!(menu30->act & CurrentSetup.Actuator))
         SkipFlag = TRUE;
      else if ((CurrentPreset.WeldMode != (menu30->mode & CurrentPreset.WeldMode)) &&
         (menu30->mode != ALLMODES)) SkipFlag = TRUE;
      else if ((menu30->Mask1!=0)  && ((menu30->Mask1 & menu30->Cond1)!= (HWConfiguration & menu30->Mask1)))
         SkipFlag = TRUE;
      else if ((menu30->Mask2!=0)  && ((menu30->Mask2 & menu30->Cond2)!= (SWConfiguration & menu30->Mask2)))
         SkipFlag = TRUE;
      else if (menu30->level > SecurityLevel) SkipFlag = TRUE;

      SetOneLineDataBit(menu30->Index, SkipFlag);
      if (!SkipFlag)
      {
 
            HMaxIndex++;
      }
      if (SkipFlag == FALSE)
      {
         RunParameter[MenuIndex]= menu30->Index;
         MenuIndex++;
      }
      index++;
   }
   return (HMaxIndex);
}
UINT16 WeldParams(UINT8  * *Response, UINT16 WeldCount, BOOLEAN ParamFlag)
/****************************************************************************/
/*Description:-                                                             */
/* Send VGARunScreen Object Line parameters                                 */
/* WeldCount - Number of weld cycle data to be sent                         */
/* ParamFlag - True if all weld parameters requested                        */
/* Returns length of the Runscreen object                                   */
/****************************************************************************/
{
   UINT8 *HistoryStart;
   UINT8 *NextHistoryPtr;
   UINT8 *SaveHistoryPtr;
   SINT8 Str[QVGA_LINESIZE];
   STR *StrTemp;
   UINT8 Index1 = 0;
   SINT8 Index2;
   UINT16 length = 0;
   UINT8 ParamNos;
   UINT8 i;
   SINT8 StrParam[LINELEN*2];
   UINT16 ScrollItems;

   for(Index2 = 0; (Index2 < QVGA_LINESIZE - 2); Index2++)
      Str[Index2] = FILLCHAR;
   Str[QVGA_LINESIZE-1] = 0;
   Str[QVGA_LINESIZE-2] = 0;        

   ScrollItems = CountActiveParameters(RunScreenParamMenu);
   if (ParamFlag)
   {
      ParamNos = ScrollItems + 1; 
      if ( (CurrentSetup.ControlLevel >= LEVEL_d) && 
           ( (CurrentSetup.Actuator == AED) ||
             (CurrentSetup.Actuator == MICRO) ||
             (CurrentSetup.Actuator == AEF) ) )
         length += AddToBuffer(Response, ParamNos+1 );
      else
         length += AddToBuffer(Response, ParamNos );
      
      for (Index2 = 0; Index2 < ScrollItems+1; Index2++)   
      {
         length += AddToBuffer(Response, (UINT8)(RunParameter[Index2]));
      }
      if ( (CurrentSetup.ControlLevel >= LEVEL_d) && 
           ( (CurrentSetup.Actuator == AED) ||
             (CurrentSetup.Actuator == MICRO) ||
             (CurrentSetup.Actuator == AEF) ) )
         length += AddToBuffer(Response, TRIGFORCEPARAM );
   }
   else
   {
      ParamNos = MAX_RUN_RESULT_PARAM;
      length += AddToBuffer(Response, MAX_RUN_RESULT_PARAM );
      for (Index2 = 0; Index2 < MAX_RUN_RESULT_PARAM; Index2++)
      {
         length += AddToBuffer(Response, CurrentSetup.WeldParamOption[Index2] );
      }
   }
   /*Send global ram weld counter to SBC at the present moment*/
   length += AddToBuffer(Response, (UINT8)((PollingCommandCounter)>>24)); 	  
   length += AddToBuffer(Response, (UINT8)((PollingCommandCounter)>>16));	  
   length += AddToBuffer(Response, (UINT8)((PollingCommandCounter)>>8));	  
   length += AddToBuffer(Response, (UINT8)(PollingCommandCounter));	  


   HistoryStart = (UINT8 *)(BBR800_HISTORY_START);
   NextHistoryPtr = (UINT8*)CurrentSetup.WeldHistoryPtr;
   if (VGAHistoryData)
   {
      NextHistoryPtr = NextHistoryPtr - (WeldCount*(sizeof(WELD_DATA)));
      if (NextHistoryPtr < HistoryStart)
         NextHistoryPtr = NextHistoryPtr + (HISTORYDATA * sizeof(WELD_DATA));
   }   
   SaveHistoryPtr = NextHistoryPtr;

   for (Index2 = 0; Index2 < WeldCount; Index2 ++){
      
      if(NextHistoryPtr != HistoryStart)
         NextHistoryPtr = NextHistoryPtr - (sizeof(WELD_DATA));
      else
         NextHistoryPtr = HistoryStart + (HISTORYDATA-1)* sizeof(WELD_DATA);
         
      memcpy( &LastRunResults, NextHistoryPtr, (sizeof(WELD_DATA))); 
      if (LastRunResults.CycleCount <= 0) break;
      Index1++; 
   }

   length += AddToBuffer(Response, Index1);          
   NextHistoryPtr = SaveHistoryPtr;   

   for (Index2 = 0; Index2 < WeldCount; Index2 ++){
      
      if(NextHistoryPtr != HistoryStart)
         NextHistoryPtr = NextHistoryPtr - (sizeof(WELD_DATA));
      else
         NextHistoryPtr = HistoryStart + (HISTORYDATA-1)* sizeof(WELD_DATA);
         
      memcpy( &LastRunResults, NextHistoryPtr, (sizeof(WELD_DATA))); 

     if (LastRunResults.CycleCount <= 0) break;

     /* All the alarmed Weld cycle are Drawn in red color */
     if(LastRunResults.NoCycleAlarms || LastRunResults.OverloadAlarms ||
        LastRunResults.EquipmentFailureAlarms || LastRunResults.CycleModifiedAlarms ||
        LastRunResults.CalibrateAlarms || (LastRunResults.SuspectBitResult & SUSPECTBITRESULTMASK)||
        (LastRunResults.RejectBitResult & REJECTBITRESULTMASK))
        length += AddToBuffer(Response, COLOR_RED);  //Red Color            
     else
        length += AddToBuffer(Response, COLOR_BLACK);  //Black Color          

     for (Index1 = 0; Index1 < ParamNos; Index1++)
     {
        if (!ParamFlag)
        {
           if(CurrentSetup.WeldParamOption[Index1])
           {
              GetUnit_Values(Str, CurrentSetup.WeldParamOption[Index1], VALUE);
           }
           else 
           { 
              Str[0] = NUL;
              Str[1] = NUL;
           }   
        }
        else
        {
           GetUnit_Values(Str, (UINT16)(RunParameter[Index1]), VALUE);
        }
        
        if (!LangCheckNull(Str))
        {
		   Str[LINESIZE] = 0;
           StrTemp = Trim_FillChar(Str); /*remove the blanks before Value*/
           strcpy(StrParam, StrTemp);
           length += AddToBuffer(Response, strlen(StrParam));            
           length += AddToBufferString(Response, StrParam, strlen(StrParam));
        }   
        else 
        { 
           strcpy(Str, "---");
           length += AddToBuffer(Response, strlen(Str));            
           length += AddToBufferString(Response, Str, strlen(Str));
        }   

     }

     if (ParamFlag)
     {
        if ( (CurrentSetup.ControlLevel >= LEVEL_d) &&
           ( (CurrentSetup.Actuator == AED) ||
             (CurrentSetup.Actuator == MICRO) ||
             (CurrentSetup.Actuator == AEF) ) )
        {
           FormatVariables( LastRunResults.TrigForce, FORCE,
                           Str, LINESIZE, CurrentSetup.Units );  // Trigger Force
           Str[LINESIZE] = 0;
           StrTemp = Trim_FillChar(Str); /*remove the blanks before Value*/
           strcpy(StrParam, StrTemp);
           length += AddToBuffer(Response, strlen(StrParam));            
           length += AddToBufferString(Response, StrParam, strlen(StrParam));
        }    
     }

     i = GetVGAPresetNameHeader(&LastRunResults, StrParam);  //Weld mode and preset number
     length += AddToBuffer(Response, i);  // Weld Mode
     length += AddToBuffer(Response, (UINT8)LastRunResults.PresetNum);  // Preset NUmber
     length += AddToBuffer(Response, strlen(StrParam));            
     length += AddToBufferString(Response, StrParam, strlen(StrParam));

     length += AddToBuffer(Response, (UINT8)LastRunResults.CycleDate.day);  // Cycle Date
     length += AddToBuffer(Response, (UINT8)LastRunResults.CycleDate.month);
     length += AddToBuffer(Response, (UINT8)((LastRunResults.CycleDate.year)%100));

     length += AddToBuffer(Response, (UINT8)LastRunResults.CycleTime.hour); // Cycle Time
     length += AddToBuffer(Response, (UINT8)LastRunResults.CycleTime.minute);
     length += AddToBuffer(Response, (UINT8)LastRunResults.CycleTime.second);

     length += AddToBuffer(Response, (UINT8)((LastRunResults.NoCycleAlarms)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.NoCycleAlarms)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.NoCycleAlarms)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.NoCycleAlarms));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.OverloadAlarms)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.OverloadAlarms)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.OverloadAlarms)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.OverloadAlarms));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.EquipmentFailureAlarms)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.EquipmentFailureAlarms)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.EquipmentFailureAlarms)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.EquipmentFailureAlarms));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.CycleModifiedAlarms)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.CycleModifiedAlarms)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.CycleModifiedAlarms)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.CycleModifiedAlarms));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.CalibrateAlarms)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.CalibrateAlarms)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.CalibrateAlarms)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.CalibrateAlarms));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.Warnings)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.Warnings)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.Warnings)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.Warnings));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.RejectBitResult)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.RejectBitResult)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.RejectBitResult)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.RejectBitResult));	  

     length += AddToBuffer(Response, (UINT8)((LastRunResults.SuspectBitResult)>>24)); 	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.SuspectBitResult)>>16));	  
     length += AddToBuffer(Response, (UINT8)((LastRunResults.SuspectBitResult)>>8));	  
     length += AddToBuffer(Response, (UINT8)(LastRunResults.SuspectBitResult));	  

     length += AddToBuffer(Response, (UINT8)(LastRunResults.PSActControlFlags)); 

   }
     
   return length;
}

SINT8 * Trim_FillChar(SINT8 Str_temp[])
/****************************************************************************/
/*Description:-                                                             */
/* Trim the leading spaces in the Input string and returns string pointer   */
/****************************************************************************/
{
   SINT8 *StrPtr= NULL_PTR;
   UINT16 Index;
   UINT16 * ptr = (UINT16 *)Str_temp;
   for(Index=0; Index < LangStrLen(Str_temp); Index++)
   {
      if(Str_temp[Index]!=' ')
      {
         StrPtr = &Str_temp[Index]; 
         break;
      }
   }
   return(StrPtr); 
}

void VGAAlarmReset (UINT32 dummy)
/****************************************************************************/
/*Description:-                                                             */
/* The function wind up the processes running before entering the           */
/* the alarm Screen.                                                        */
/****************************************************************************/
{
      DiagFlag = FALSE; // Disable diagnostics
      /*If we are in TEST sequence Exit from there*/
      if(CurrentSequence == TESTMODE)
      {
         QVGAExitTestSequence();
      }
      /*Wind up Horn Scan*/
      else if(HornScanInfo. ScanStatus == DUPS_SCANINPROG)
      {
          QVGAAbortHornScan = TRUE;
          EnableWelding();
          HornScanInfo. ScanStatus = DUPS_NOSCAN;
          PrevHornState = SCAN_NONE;
      }
                
      /*Wind up Calibration Process */
      if(QVGACalAllowed)
      {
          SCFinalCleanup();
      }
      else if(QVGASnsrCalibAllowed)
      {
          CalibFinalCleanup();
      } 
      else if(StateMachineDisabled)
      {  
         ExitMenuAndEnableWeld();
      } 
      if ((QVGAHornDown) && (dummy == 0))
      {
         VGAAction = EXIT_HD;
         VGAProcessHornDownMsg(); //commented

      }   
       
}

void CheckforCalib(void)
/****************************************************************************/
/*Description:-                                                             */
/* Function checks if calibration is in progress and set/reset              */
/* CalibInProgress flag.                                                    */
/****************************************************************************/
{
   CalibInProgress = FALSE;
   if (QVGACalAllowed || QVGASnsrCalibAllowed)
      CalibInProgress = TRUE;
}

UINT16 SendWeldState(UINT8 * to)
/****************************************************************************/
/*Description:-                                                             */
/* Sends VGA weld state and preset nameto the SBC                           */
/****************************************************************************/
{
   UINT16 length = 0;

   length += AddToBuffer(&to, LangStrLen(StrWeldStateLine));            
   length += AddToBufferString(&to, StrWeldStateLine, 
                                 LangStrLen(StrWeldStateLine));
   length += AddToBuffer(&to, (UINT8)((CurrentSetup.ActivePreset)>>8));	  
   length += AddToBuffer(&to, (UINT8)(CurrentSetup.ActivePreset));	  

   GetCurrentPresetNames();
   length += AddToBuffer(&to, LangStrLen(PresetNameBuffer));            
   length += AddToBufferString(&to, PresetNameBuffer, LangStrLen(PresetNameBuffer));
   return (length);
}

 /*********************************END***************************************/
