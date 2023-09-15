/* $Header:   D:/SWLab/VMdb/2000Series/App/MENU1.C_V   2.133.2.4   10 Sep 2009 15:59:32   bkymer  $ */
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
/*************************                         **************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:                                                 
   Filename: menu1.c               

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #      Date          Author      Description
   ==========     ========      ======       ===========
      0                                      Initial Version
      1.00        04/29/96       PJ          Modified for PSOS version
      2.00        05/10/96       PJ          Uncommented DebuggingFlag
      3.00        05/14/96       PJ          Prototypes in menu2.h
                                             Strings in menutext.c
      3.01        07/01/96       PJ          TriggerDelayChoiceTime changed to
                                             TriggerDelayTime of type VARIABLE.
      3.02        07/19/96       PJ          Changed HoldTime to HoldTime1
      3.10        08/21/96       PJ          Deleted duplicate WeldForce and
                                             Amplitude menus.
      3.20        09/04/96       PJ          Changed Run Screen menu per Spec
                                             Rev 1.D
      3.30        09/04/96       PJ          Changed RunResultsChoice menu 
                                             back to type SubMenu.
      3.40        09/11/96       PJ          Added scrolling menus 
      3.50        09/16/96       PJ          Changed WeldData array to extern
                                             Finalresults array.
      3.60        09/19/96       PJ          Initialized ScrollBuffer to Null
                                             when entering Run screen.
      3.70        09/19/96       PJ          Added Time for Pizza msg.
                                             Deleted GoBackToWeldAdjustSetup,
                                             SetBlankDisplayCounter, and
                                             SetBlankDisplayCounter functions.
      3.80        09-24-96       BEKymer     Use FinalResults.CycleCount instead
                                             of CurrentPreset.WeldCount
      3.80        09/25/96       PJ          Added scrolling menu to correct
                                             updating of scrolling buffer.
      3.90        09/27/96       PJ          Global FinalResults data changed
                                             to WeldData local copy.
      4.00        10/04/96       PJ          Deleted AdjustWeldSetupFlag. No
                                             longer required. Added testing of
                                             MainKeyFlag to UpdateParam().
      4.10        10/09/96       PhilJ       Changed Menus to type const. 
      4.20        10/19/96       PhilJ       Added English to Metric conversion
                                             to FormatScrollinBuffer.
      4.30        10/27/96       PhilJ       Modification to FormatScrolling
                                             Buffer to display negative data
                                             in collapse mode.
      4.40        11/08/96       PhilJ       Deleted UpdateParam from
                                             SetParamChoice menu.
      4.50        11/13/96       PhilJ       Corrected bug displaying energy and
                                             Distance in FormatScrollingBuffer.
      4.60        11/26/96       PhilJ       ScrollingBuffer will display N/A
                                             in CONTINUOUSMODE if applicable. 
      4.70        12/09/96       PhilJ       Deleted call to RemoveNull in
                                             FormatScrollingBuffer.
      4.80        12/31/96       PhilJ       Added HmenuIndex check for invalid
                                             number in Battery backup.
      4.90        01/06/97       LAM         redefined beep prototype
      5.00        01/02197       PhilJ       In FormatScrollingBuffer added
                                             actuator check for Force.
      5.01        01/24/97       LAM         do not update runbuffer2 when
      6.00        01-28-97       LAM         deleted unused vars
      6.01        01/31/97       PhilJ       Set security level of
                                             SetParamChoice menu to OPERATOR.
      6.02        02/20/97       PhilJ       Changed RunBuffer1 to Upper Case
                                             = FALSE.
      6.03        02-21-97       LAM         chged velocity format to xx.xx       
      6.04        02/26/97       PhilJ       Changed RTIME offset from 8 to 9
      7.00        04/05/97       LAM         Changed ampstart & ampend, vel = .1
                                             changed current preset to running preset
      7.10        04/08/97       PhilJ       Changed displaying of RVELOCITY and
                                             fixed = sign in one line data strings.
      7.20        04/08/97       PhilJ       Changed RunningPreset back to Current.
      7.30        04/25/97       PhilJ       Added menus WeldResultsItem and
                                             RunSeekItem to scrolling menu .
      7.40        04-28-97       PhilJ       Chngd AmpControlInternal & Freq
                                             ControlInternal from UINT8 to UINT16.
      7.50        05-01-97       PhilJ       Corrected bug in displaying Collapse
                                             distance in metric.
      7.60        05-07-97       PhilJ       Added Roundoff factor to Velocity.
      7.70        05-12-97       PhilJ       Deleted Runseek from scrolling menu.
      7.80        06-13-97       PhilJ       Corrected warning in floating point.
      8.2.46      06-17-97       PhilJ       Corrected metric velocity calculation
      8.2.47      07-03-97       PhilJ       Added Check in FormatScrollingBuffer
                                             RAMPEND.
      8.2.48      07-08-97       PhilJ       Added AmpCntrlExternal menu.
      8.2.49      07-09-97       PhilJ       Changed HmenuIndex to CurrentSetup
      8.2.50      07-17-97       PhilJ       Added SetOneLineDataBit function for
                                             Scrolling menu enables.
      8.2.51      07-23-97       PhilJ       Chngd Amplitude menu from LEVEL_d
                                             to LEVEL_t
      8.2.52      07-28-97       PhilJ       Added function ClearWeldData()
      8.2.54      08-06-97       BEKymer     In case RCOLDIST set PositiveValue
                                             before checking it for non zero
      8.2.55      08-21-97       PhilJ       Deleted SetParamChoice menu.
      2.56        08-23-97       LAM         Deleted triggerattime       
      2.57        09-15-97       LAM         made freq change negative
      2.58                        ?
      2.59        09-26-97       BJB         Deleted ScrollIndex, now menu.c writes
                                             directly to CurrentSetup.HmenuIndex
      2.60        09-28-97       LAM         added formatfreqchg                
      2.61        10-03-97       BJB         Fixed metric conversion of velocity
                                             Modify US velocity display to show
                                             two decimal places
      2.62        10-07-97       LAM         fixed preset10 asterisk            
      2.63        10-22-97       LAM         fixed +/- freq change
      2.64        11-06-97       BJB         Fixed display of time on weld
                                              results line so it's shown as 0.000
                                              if time is negative (not 0.00/).

      2.65        11-15-97       LAM         added menu1.h to fixed linker warning
      2.66        11-18-97       LAM         chged welddata to finalresults     
      2.67        12-01-97       BEKymer     Add AdjustWeldSetupMenuFlag
      2.68        12.01.97       JBerman     In "VARIABLE Amplitude" modified
                                             from ADVANCED to NORMAL
      2.69        12.04.97       BJB         Added function ExitWeldSetupMenu() to
                                              turn off AdjustWeldSetupMenuFlag.
      2.70        01.29.98       BJB         Replaced calls to FormatFreqChg() with
                                              call to FormatSignedInt().
      2.71        02-04-98       BEKymer     Move 'AtTime' values from WELD_DATA
                                             to WELD_OBJECT structure
      2.72        02-06-98       BJB         Changed PeakPower display code to show
                                              decimal place.
      2.73        03-10-98       BJB         Displays blank line for preset name at
                                              control level 1.
      2.74        03-18-98       BJB         Changed text of "Amplitude" lines on
                                              Weld Results to say "Set Amp".
                                             Fixed amplitude display code in
                                              FormatScrollingBuffer() so it says
                                              "Ext" if amp external, doesn't say
                                              "A" if no amp step, and also displays
                                              reuested values, not actual.
      2.75        03-19-98       BJB         Back to displaying amp from
                                              FinalResults, which now has requested
                                              values.
                                             Checks for ext amp in FinalResults.
                                             Checks for amp stepping, continuous
                                              mode in RunningPreset.
      2.76        03-20-98       BJB         Looks at new flag in FinalResults to
                                              see if stepping is on, instead of
                                              RunningPreset.
      2.77        03-30-98       LAM         chged EP to either AED or AEF
      2.78        04-24-98       BJB         Modified number of digits displayed
                                              for RVELOCITY.
      2.79        05-22-98       BJB         FormatScrollingBuffer() now works
                                              with FORCE values in tenths of
                                              pounds.
      2.80        05-22-98       BJB         Fixed number of digits in metric
                                              display of mm on results line.
      2.81        05-26-98       BJB         Modified FormatScrollingBuffer() to
                                              use FormatVariable() like other
                                              menu code.
      2.82        05.27.98       JBerman     In AmplitudeStep:
                                             changed from LEVEL_d to 3
      2.83        06-03-98       BEKymer     Changed AmpControlFlags to
                                             PowerSupplyControlFlags
      2.84        06-17-98       BJB         Modified DisplayCurrentPreset() to
                                              write to passed string instead of
                                              RunBuffer2[].
                                             GetCurrentWeldData() doesn't need
                                              to call DisplayCurrentPreset(),
                                              done automatically in menu display.
      2.85        06-19-98       BJB         Gets weld results for screen from
                                              history buffer instead of
                                              FinalResults, guarantees printer &
                                              display will match, esp. after
                                              cold start.
      2.86        06-22-98       BJB         Text change: Force Max-->Weld Force
      2.87        06-22-98       BEKymer     Renamed member ActualForceMax to
                                             WeldForceMax
      2.88        06-24-98       BJB         Added System Pressure item to weld
                                              results line.
                                             Moved = sign on Weld Force to
                                              leave a space after units.
      2.89        06-24-98       BJB         Changed NORMAL to BASIC.
                                             Changed ADVANCED to ALL.
      2.90        07-31-98       BJB         Includes kpresmsg.h, getmsg.h
      2.91        08-03-98       BEKymer     Change format for RVELOCITY to 
                                             display 3 digits
      2.92        08-10-98       BEKymer     Rename ActualCollapse to Actual
                                             TotalCollapse and add ActualWeld
                                             Collapse
      2.93        09-04-98       BJB         Added weld collapse item to weld  
                                              results line.
      2.94        11-04-98       LAM         chged sys press to act press
      2.95        11-10-98       BJB         Overwrites = sign to show - number
                                              for total collapse.
      2.96        12-07-98       BEKymer     Use ActualForceEnd instead of Weld
                                             ForceMax on the run screen
                                             Change LEVEL_d to LEVEL_ea on some 
                                             amp end condition
      2.97        05-14-99       JZ          Changed WeldForceMax to SetForceB
                                             ActualForceStart to SetForceA
                                             ActualForceEnd to WeldForceEnd
                                             RFORCEEND to RFORCEB, RFORCESTART to
                                             RFORCEA, RFORCEMAX to RFORCE
                                             Added Force Stepping
                                             
      2.98        05-19-99       OFI         Changed Weldforce to WeldForceAdjMenu
      2.99        05-21-99       JZ          changed Amplitude Step and Force Step order
                                             in the WeldAdjustMenu
      2.100       06-16-99       JZ          eliminated commented code
      2.101       08-16-99       JZ          added ForceStepDisableFlag, SelectWeldSetupMenu2                                
                                             ForceStepEnableFlag
      2.102       09-03-99       JZ          fixed WeldForceAdjMenu 
      2.103       10-01-99       JZ          changed SetRunScreenFlag() and ExitWeldSetupMenu() to static
      2.104       11-03-99       JZ          added comments to SelectWeldSetupMenu2()
      2.105       11-04-99       JZ          converted tabs to spaces
      2.105.6.1   02-07-99       JZ          removed DVS and added Mask1, Cond1, Mask2, Cond2
      2.105.6.2   02-23-00       OFI         removed 'User experience level' from menu strucutures
      2.106       04-05-00       JZ          merged Lang to trunk
      2.107       04-14-00       SCM         Added structure defns for Cycle Time and Weld Abs.Changed
                                             the string name to "Total Abs(in)".
      2.108       04-18-00       SCM         Inserted the "=" sign in the text string for Weld Abs, Total Abs
                                             and Cycle Time. 
      2.109       04-19-00       SCM         Converted all tabs to spaces.
      2.110       05-26-00       SCM         Checked in for testing by Laura, John.
      2.111       06-02-00       SCM         Changed the definition of WeldDataStrPtr[].
      2.112       06-09-00       SCM         Removed CycleTime option since it is now
                                             a Ver9 definition.
      2.113       06-14-00       SCM         Removed the test for LEVEL_t in DisplayCurrentPreset()
                                             and commented out RCYCLETIME case in FormatScrollingBuffer()
                                             since it is part of Version 9 now.
      2.114       06-27-00       SCM         Modified the "cases"  RWABSDIST and RTABSDIST in the 
                                             function FormatScrollingBuffer(). Also modified the "cases" 
                                             in SetOneLineDataBit().All changes involved changes in variable
                                             names.
      2.115       06-28-00       SCM         Initialized ActualWeldAbs to zero in 
                                             ClearWeldData() function.
      2.116       06-28-00       BEKymer     Changed MODEL to LEVEL  and Fixed SETUPS
      2.117       08-03-00       JLH         Changed velocity, weld collapse, and total collapse
                                              HVARIABLES to eliminate their display for ae ea
                                              welders. 
      2.118       08-11-00       JLH         Allow asterisk on level t - tracker issue 3325.  Changed ClearWeldData so it
                                              does not clear non-resetable equipment alarms.
      2.119       08-23-00       LAM         Allow freq min & max on level t - tracker issue 3359.
      2.119.1.0   04-24-03       BEKymer     Make VelocityItemaef and VelocityItemaed
                                             In const HVARIABLE VelocityItemaef add VEL so velocity
                                              reporting can be turned off
      2.119.3.1   06-10-03       Bwadia      The struct variable "BitFlags" made global(runresults.c also
                                             accessing this variable).   
      2.119.3.2   07-31-03       LAM         merged 8.10 with TS01
      2.119.3.3   10-03-03       JOY         'Velocity Weld Param' only displayed in AED.
      2.119.3.4   10-14-03       JOY         Added Velocity weld param in aef. Tracker issue #3781.
      2.121       08-01-03       BEKymer     Merged 2.120 and 2.119.2.0 to create 2.121 for version 9
                                             - Added argument to TEXT and SUBMENU structures as required
                                               by the menu system
                                             - Make VelocityItemaef and VelocityItemaed  
                                             - In const HVARIABLE VelocityItemaef add VEL so velocity  
                                                reporting can be turned off                                              
      2.122       12-02-03       BEKymer     Merged 1.121 & 2.119.3.4 to create 2.122
                                              for Ver9.00b build
      2.123       02-20-04       VSharma     Added PresetNumItem in RunScreenMenu.
                                             Modify FormatScrollingBuffer(), SetOneLineDataBit() &
                                             ClearWeldData() for PRESETNUM change.
      2.124       04-06-04       VSharma     Changed extern of WeldDataStrPtr.                                        
      2.125       05-07-04       LAM         merged 8.22                                        
      2.126       06-15-04       BEKymer     Added RVELOCITY_AED & RVELOCITY_AEF
                                              cases where appropiate.  This 
                                              separates aef from aed, so removing
                                              velocity reporting from aef actuators
                                              has no effect on aed actuators.
      2.127       07-25-05       Bwadia       RunBuffer1, RunBuffer2 and ScrBufName
                                              buffer changed to support Asian Language.
                                              RunBuffer1 and RunBuffer2 are written only for
                                              current language at all the places in the code.
      2.128       08-19-05       Bwadia       RunBuffer1 has different strings for  
                                              different languages 
      2.129       09-11-05       Aare         Merged 10f and 10h 
      2.130       11-02-05       Aare         Use right variable for total cycle time.
      2.131       01-31-07       NHAhmed      Changes related to Changed Structure variables of CHOICE and TOGGLE.
      2.132       04-24-07       NHAhmed      Changes related to Force and Amplitude Step/Fixed.
      2.133       04-27-07       YGupta       Made Changes related to Force and Amplitude Step/Fixed.
      2.134       04-14-08       NHAhmed      Added a new menu RunScreenParamMenu[].
      2.135       09-02-08       NHAhmed      CleanUp for multi-language support.
      2.136       09-04-08       YGupta       CleanUp for LangTest Project.
      2.137       10-13-08       NHAhmed      Modified the CtrlLevel for menu PeakPowerItems.
      2.133.2.4   09-10-09       BEkymer      Add new define MICRO where needed
      
      

 ------------------------------- DESCRIPTION ---------------------------------
*/
 
      /* This file will deal with the Run Screen and all its glory. */

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "string.h"
#include "menu.h"
#include "preset.h"
#include "param.h"
#include "error.h"
#include "keypad.h"
#include "selctkey.h"
#include "fmtstrs.h"
#include "weld_obj.h"
#include "display.h"
#include "beep.h"
#include "graphs.h"
#include "menu3.h"
#include "menu1.h"
#include "kpresmsg.h"
#include "getmsg.h"
#include "alarms.h"
#include "menu7a.h"

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

UINT8 RunScreenFlag = FALSE;

UINT16 AdjustWeldSetupMenuFlag=0; /* TRUE:Adjust Weld Setup selected from Run Screen */
                                  /* FALSE:when Main Menu, Go Back, Run or Setup key pressed */


/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/

BIT_FLAGS BitFlags;


/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/
static void SetRunScreenFlag(void);
static void ExitWeldSetupMenu(void);


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern UINT16 AmplitudeFixedEnableFlag;
extern UNION_BOOL_UINT16 AmplitudeStepEnableFlag;
extern UNION_BOOL_UINT16 AmplitudeStepMicronsEnableFlag;
extern UINT16 ForceFixedEnableFlag;
extern UNION_BOOL_UINT16 ForceStepEnableFlag;

extern SINT8 ScrollBuffer[SCROLLBUFFERSIZE];

extern UINT8 MainKeyFlag;
extern SINT16 BlankMenuCounter;
extern UINT16 AmpCntrlExt;

extern SETUPS_Ver800 CurrentPreset;
extern SETUPS_Ver800 RunningPreset;                   
extern SETUPS_Ver800 MinLimit;
extern SETUPS_Ver800 MaxLimit;

extern CONFIGSETUP CurrentSetup;

extern WELD_DATA FinalResults;
extern WELD_OBJECT *MsDataPtr;

extern UINT8 AlarmDetectedFlag;

extern UINT16 LangIndex;

MENUEND endlist1 = { TRUE };

/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/



/*
 ---------------------------------- CODE -------------------------------------
*/

           
void SetOneLineDataBit(UINT16 OneLineIndex, UINT8 ActiveFlag)
{

   switch(OneLineIndex)
   {
      case WELDRESULTS:
         if(!ActiveFlag)
            BitFlags.WRbit = TRUE;
         else
            BitFlags.WRbit = FALSE;
         break;

      case RCYCLECOUNT:
         if(!ActiveFlag)
            BitFlags.Cyclebit = TRUE;
         else
            BitFlags.Cyclebit = FALSE;
         break;

      case RPRESETNUM:
         if(!ActiveFlag)
            BitFlags.PresetNum = TRUE;
         else
            BitFlags.PresetNum = FALSE;
         break;

      case RTIME:
         if(!ActiveFlag)
            BitFlags.Timebit = TRUE;
         else
            BitFlags.Timebit = FALSE;
         break;

      case RPKPWR:
         if(!ActiveFlag)
            BitFlags.PkPwrbit = TRUE;
         else
            BitFlags.PkPwrbit = FALSE;
         break;

      case RENERGY:
         if(!ActiveFlag)
            BitFlags.Energybit = TRUE;
         else
            BitFlags.Energybit = FALSE;
         break;

      case RVELOCITY_AED:
         if(!ActiveFlag)
            BitFlags.VelocityAedbit = TRUE;
         else
            BitFlags.VelocityAedbit = FALSE;
         break;

      case RVELOCITY_AEF:
         if(!ActiveFlag)
            BitFlags.VelocityAefbit = TRUE;
         else
            BitFlags.VelocityAefbit = FALSE;
         break;

      case RWABSDIST:
         if(!ActiveFlag)
            BitFlags.WeldAbsbit = TRUE;
         else
            BitFlags.WeldAbsbit = FALSE;
         break;

      case RTABSDIST:
         if(!ActiveFlag)
            BitFlags.Absbit = TRUE;
         else
            BitFlags.Absbit = FALSE;
         break;

      case RWCOLDIST:
         if(!ActiveFlag)
            BitFlags.WeldCollbit = TRUE;
         else
            BitFlags.WeldCollbit = FALSE;
         break;

      case RTCOLDIST:
         if(!ActiveFlag)
            BitFlags.TtlCollbit = TRUE;
         else
            BitFlags.TtlCollbit = FALSE;
         break;

      case RAMPSTART:
         if(!ActiveFlag)
            BitFlags.AmpAbit = TRUE;
         else
            BitFlags.AmpAbit = FALSE;
         break;

      case RAMPEND:
         if(!ActiveFlag)
            BitFlags.AmpBbit = TRUE;
         else
            BitFlags.AmpBbit = FALSE;
         break;

      case RFORCEA:
         if(!ActiveFlag)
            BitFlags.SetFAbit = TRUE;
         else
            BitFlags.SetFAbit = FALSE;
         break;

      case RFORCEB:
         if(!ActiveFlag)
            BitFlags.SetFBbit = TRUE;
         else
            BitFlags.SetFBbit = FALSE;
         break;

      case RFORCE:
         if(!ActiveFlag)
            BitFlags.SetFEndbit = TRUE;
         else
            BitFlags.SetFEndbit = FALSE;
         break;

      case RSYSPRESS:
         if(!ActiveFlag)
            BitFlags.Pressbit = TRUE;
         else
            BitFlags.Pressbit = FALSE;
         break;

      case RFREQMIN:
         if(!ActiveFlag)
            BitFlags.FreqMinbit = TRUE;
         else
            BitFlags.FreqMinbit = FALSE;
         break;

      case RFREQMAX:
         if(!ActiveFlag)
            BitFlags.FreqMaxbit = TRUE;
         else
            BitFlags.FreqMaxbit = FALSE;
         break;

      case RFREQSTART:
         if(!ActiveFlag)
            BitFlags.FreqStartbit = TRUE;
         else
            BitFlags.FreqStartbit = FALSE;
         break;

      case RFREQEND:
         if(!ActiveFlag)
            BitFlags.FreqEndbit = TRUE;
         else
            BitFlags.FreqEndbit = FALSE;
         break;

      case RFREQCHG:
         if(!ActiveFlag)
            BitFlags.FreqChgbit = TRUE;
         else
            BitFlags.FreqChgbit = FALSE;
         break;

      case RCYCLETIME:
         if(!ActiveFlag)
            BitFlags.CycleTimebit = TRUE;
         else
            BitFlags.CycleTimebit = FALSE;
         break;

      default:
         break;
   }
}


static void SetRunScreenFlag(void)
{
   RunScreenFlag = TRUE;
}

void ClearRunScreenFlag(void)
{
   RunScreenFlag = FALSE;
}


void GetCurrentWeldData(UINT32 MenuExtra)
{
   strcpy(ScrollBuffer, NULL);         /* Initial 1st position in buffer */

   SetRunScreenFlag();

   if(CurrentSetup.HmenuIndex >= RMAXPARAMETERS)
      CurrentSetup.HmenuIndex = 0;
}


void SelectWeldSetupMenu(UINT32 MenuExtra)
{
   AdjustWeldSetupMenuFlag = TRUE;

   if((CurrentPreset.Force2Flag & BIT0) == TRUE)
   {
      ForceStepEnableFlag.bool = TRUE;
      ForceStepEnableFlag.uint16.Hi = TRUE;
      ForceFixedEnableFlag = FALSE;
   }
   else
   {
      ForceStepEnableFlag.bool = FALSE;
      ForceStepEnableFlag.uint16.Hi = FALSE;
      ForceFixedEnableFlag = TRUE;
   }
   if(CurrentSetup.AmpControl == TRUE)
    {
      if((CurrentPreset.Amp2Flag & BIT0) == TRUE)
      {
          AmplitudeFixedEnableFlag = FALSE;
          AmplitudeStepEnableFlag.bool = TRUE;
          AmplitudeStepEnableFlag.uint16.Hi = TRUE;
          AmplitudeStepMicronsEnableFlag.uint16.Hi = TRUE;
          AmplitudeStepMicronsEnableFlag.uint16.Low = TRUE;
      }
      else
      {
    	  AmplitudeFixedEnableFlag = TRUE;
          AmplitudeStepEnableFlag.bool = FALSE;
          AmplitudeStepEnableFlag.uint16.Hi = FALSE;
          AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
          AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE;
      }
      if(CurrentSetup.AmpMicronsFlag==TRUE)AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE; else AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
    }
   else
    {
      AmplitudeFixedEnableFlag = FALSE;
      AmplitudeStepEnableFlag.bool = FALSE;
      AmplitudeStepEnableFlag.uint16.Hi = FALSE;
      AmplitudeStepMicronsEnableFlag.uint16.Hi = FALSE;
      AmplitudeStepMicronsEnableFlag.uint16.Low = FALSE;
    }
}

void SelectWeldSetupMenu2(void)
/****************************************************************************/ 
/*   This function will ensure that either WeldForce or ForceA will be      */
/*   displayed                                                              */
/****************************************************************************/ 
{
   if((CurrentPreset.Force2Flag & BIT0) == BIT0)
   {
      ForceStepEnableFlag.bool = TRUE;
      ForceStepEnableFlag.uint16.Hi = TRUE;
      ForceFixedEnableFlag = FALSE;
   }
   else
   {
      ForceStepEnableFlag.bool = FALSE;
      ForceStepEnableFlag.uint16.Hi = FALSE;
      ForceFixedEnableFlag = TRUE;
   }
}

static void ExitWeldSetupMenu(void)
{
   AdjustWeldSetupMenuFlag = FALSE;
}

void UpdateParam(void)
{
   if(!MainKeyFlag)
   {
      SendFakeKeyPress(GoBackKey);
      SendFakeKeyPress(Select2Key);
      BlankMenuCounter = 2;
   }
}


void SoundBeeper(UINT32 MenuExtra)
{
   Beep(ERRORBEEP);
}


void ClearWeldData(void)
{
   FinalResults.ActualFreqEnd = 0;
   FinalResults.ActualFreqStart = 0;
   FinalResults.FrequencyChange = 0;
   FinalResults.FrequencyMin = 0;
   FinalResults.FrequencyMax = 0;
   FinalResults.TotalEnergy = 0;
   FinalResults.ActualWeldAbs = 0;
   FinalResults.ActualTotalAbs = 0;
   FinalResults.ActualTriggerDistance = 0;
   FinalResults.ActualWeldCollapse = 0;
   FinalResults.ActualTotalCollapse = 0;
   FinalResults.ActualVelocity = 0;
   FinalResults.WeldForceEnd = 0;
   FinalResults.ActualAmplitudeStart = 0;
   FinalResults.ActualAmplitudeEnd = 0;
   FinalResults.PeakPower = 0;
   FinalResults.ActualWeldTime = 0;
   FinalResults.RejectBitResult = 0;
   FinalResults.SuspectBitResult = 0;
   FinalResults.NoCycleAlarms = 0;
   FinalResults.OverloadAlarms = 0;
   FinalResults.EquipmentFailureAlarms &= EQ_NO_RESET;
   FinalResults.CycleModifiedAlarms = 0;
   FinalResults.CalibrateAlarms = 0;
   FinalResults.Warnings = 0;
   FinalResults.PresetNum = 0;
   FinalResults.PresetName[0] = NUL;
   FinalResults.CycleTimeResult = 0;

   MsDataPtr->AmpStepAtTime = 0;
   MsDataPtr->ForceStepAtTime = 0;
   MsDataPtr->HoldEndAtTime = 0;
   MsDataPtr->SeekEndAtTime = 0;
}


const RSPARAMETER WeldResultsItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    WELDRESULTS };                /* Identifier for run parameter          */
 
const RSPARAMETER CycleCounters = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RCYCLECOUNT };                /* Identifier for run parameter          */
 
const RSPARAMETER WeldTimeItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RTIME };                      /* Identifier for run parameter          */

const RSPARAMETER PeakPowerItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RPKPWR };                     /* Identifier for run parameter          */

const RSPARAMETER EnergyItems = {
    LEVEL_e,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RENERGY };                    /* Identifier for run parameter          */

const RSPARAMETER VelocityItem_aed = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (AED | MICRO),                /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RVELOCITY_AED };              /* Identifier for run parameter          */

const RSPARAMETER VelocityItem_aef = {
    LEVEL_f,                      /* Lowest model to be displayed on       */
    (AEF),                        /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    VEL,                          /* what conditions are required   Mask2  */
    VEL,                          /* to display this menu           Cond2  */
    RVELOCITY_AEF };              /* Identifier for run parameter          */

const RSPARAMETER WeldAbsDistItems = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (AED|AEF|MICRO),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RWABSDIST };                  /* Identifier for run parameter          */

const RSPARAMETER AbsDistItems = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (AED|AEF|MICRO),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RTABSDIST };                  /* Identifier for run parameter          */

const RSPARAMETER WeldColDistItems = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (AED|AEF|MICRO),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RWCOLDIST };                  /* Identifier for run parameter          */

const RSPARAMETER TtlColDistItems = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (AED|AEF|MICRO),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RTCOLDIST };                  /* Identifier for run parameter          */

const RSPARAMETER AmpStartItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RAMPSTART };                  /* Identifier for run parameter          */

const RSPARAMETER AmpEndItems = {
    LEVEL_ea,                     /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RAMPEND };                    /* Identifier for run parameter          */


const RSPARAMETER Force_A = {
    LEVEL_f,                      /* Lowest model to be displayed on       */
    AEF,                          /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFORCEA };                    /* Identifier for run parameter          */

const RSPARAMETER Force_B = {
    LEVEL_f,                      /* Lowest model to be displayed on       */
    AEF,                          /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFORCEB };                    /* Identifier for run parameter          */

const RSPARAMETER Force_End = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (AED|AEF|MICRO),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFORCE };                     /* Identifier for run parameter          */

const RSPARAMETER WeldPressureItems = {
    LEVEL_d,                      /* Lowest model to be displayed on       */
    (AED|AEF|MICRO),              /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RSYSPRESS };                  /* Identifier for run parameter          */

const RSPARAMETER FreqMinItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFREQMIN };                   /* Identifier for run parameter          */

const RSPARAMETER FreqMaxItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFREQMAX };                   /* Identifier for run parameter          */

const RSPARAMETER FreqStartItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFREQSTART };                 /* Identifier for run parameter          */

const RSPARAMETER FreqEndItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFREQEND };                   /* Identifier for run parameter          */

const RSPARAMETER FreqChgItems = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RFREQCHG };                   /* Identifier for run parameter          */

const RSPARAMETER PresetNumItems = {
    LEVEL_t,                     /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RPRESETNUM };                 /* Identifier for run parameter          */
 
 
const RSPARAMETER CycleTimes = {
    LEVEL_t,                      /* Lowest model to be displayed on       */
    DONTCARE,                     /* What actuator is required             */
    ALLMODES,                     /* Which welding mode to display line    */
    OPERATOR,                     /* What is security level of operator    */
    0,                            /* what is important to           Mask1  */
    0,                            /* display this menu              Cond1  */
    0,                            /* what conditions are required   Mask2  */
    0,                            /* to display this menu           Cond2  */
    RCYCLETIME };                  /* Identifier for run parameter          */



const MENU RunScreenParamMenu[] ={  {&CycleCounters,              _RSPARAMETER },
                                    {&WeldTimeItems,              _RSPARAMETER },
                                    {&PeakPowerItems,             _RSPARAMETER },
                                    {&EnergyItems,                _RSPARAMETER },
                                    {&VelocityItem_aed,           _RSPARAMETER },
                                    {&VelocityItem_aef,           _RSPARAMETER },
                                    {&WeldAbsDistItems,           _RSPARAMETER },
                                    {&AbsDistItems,               _RSPARAMETER },
                                    {&WeldColDistItems,           _RSPARAMETER },
                                    {&TtlColDistItems,            _RSPARAMETER },
                                    {&AmpStartItems,              _RSPARAMETER },
                                    {&AmpEndItems,                _RSPARAMETER },
                                    {&Force_A,                    _RSPARAMETER },
                                    {&Force_B,                    _RSPARAMETER },
                                    {&Force_End,                  _RSPARAMETER },
                                    {&WeldPressureItems,          _RSPARAMETER },
                                    {&FreqMinItems,               _RSPARAMETER },
                                    {&FreqMaxItems,               _RSPARAMETER },
                                    {&FreqStartItems,             _RSPARAMETER },
                                    {&FreqEndItems,               _RSPARAMETER },
                                    {&FreqChgItems,               _RSPARAMETER },
                                    {&PresetNumItems,             _RSPARAMETER },
                                    {&CycleTimes,                 _RSPARAMETER },
                                    {&endlist1,                    ENDLIST}   };

