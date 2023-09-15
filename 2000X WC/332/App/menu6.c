/* $Header:   D:/SWLab/VMdb/2000Series/App/MENU6.C_V   2.97   22 Sep 2009 12:04:20   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
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

   Filename: menu6.c

   Function name:


 --------------------------------- REVISIONS --------------------------------

   Revision #      Date         Author      Description
   ==========     ========      ======      ===========
      0                                     Initial Version
      1.00        04/29/96       PJ         Modified for PSOS version
      2.00        05/14/96       PJ         Deleted in menu6.h
                                            Strings in menutext.c
      3.00        06/20/96       PJ         Added Counter Menu per UI
                                            Improvements. Removed from menu7.
      3.01        06/21/96       PJ         Corrected bug displaying Preset
                                            Counter Menu.
      3.10        08/01/96       PJ         Move Preset Counter menu to menu7
                                            Per Spec rev 1.C.
      3.20        08/14/96       PJ         Modified per Spec Rev 1.D.
      3.30        08/22/96       PJ         Modified string length to fit the
                                            the 20 character display line.
      3.40        10/09/96       PhilJ      Changed Menus to type const. 
      3.50        11/01/96       PhilJ      Added function to get System Info.
      3.60        11/26/96       PhilJ      No Change made.
      3.70        12/23/96       PhilJ      Changed function name from Load
                                            ActuatorType to DisplayActuatorType.
      3.80        12/23/96       LAM        moved strokelen to preset
      3.90        03/03/97       PhilJ      Added function GetSerialNumbers.
      4.00        05/21/97       LAM        chged pswatt case               
      5.00        05/24/97       LAM        added 800 pswatt case               
      5.10        06/16/97       PhilJ      Removed commented out code               
      5.2.17      07/03/97       PhilJ      Added new PowerSupply info                
      5.2.18      07/07/97       PhilJ      Chngd EP menus to LEVEL_f. Modified
                                            LoadActuatorType.
      5.2.19      07/11/97       PhilJ      Fixed bug in LoadActuator string
      5.2.20      07/11/97       PhilJ      Fixed string in LoadActuator
      5.2.21      07/11/97       PhilJ      Null terminated SystemInfoBuffers
      5.2.23      08/11/97       PhilJ      Chgd CyclStroke & Diameter menus
                                            to AE and LEVEL_t 
      5.2.24      08.27.97       JBerman    Replaced VARIABLR -> TEXT:
                                            CylinderStroke & CylinderDiameter 
      2.25        09.23.97       LAM        deleted call to actnovram 
      2.26        10.07.97       LAM        deleted unused strings
      2.27        04.30.98       BJB        Modified ActuatorSerialNumber so
                                            it will display on AED or AEF.
      2.28        05.05.98       JBerman    Rewrote LoadCellActuatorType
      2.29        05.18.98       LAM        swapped model3 = a and model 4 = d
                                            Added calibration menu item
      2.30        06.04.98       JBerman    In LoadActuatorType, I matched 
                                            the Actuator Type.
      2.31        06.05.98       LAM        made calibration strings variables  
      2.32        06.10.98       LAM        moved pass fail strings to menutext
      2.33        06.18.98       LAM        made calibrate date TEXT it was SUBMENU
      2.34        06.24.98       BJB        Changed NORMAL to BASIC.
      2.35        06.26.98       JBerman    CommentedOut LoadActuatorType, 
                                            The String will be updated in UTIL.c/Powerup
      2.36        07.30.98       BJB        Deleted act_nvr definition, uses actnvram.h
      2.37        07.30.98       BJB        Put back LoadActuatorType() function.
      2.38        09.01.98       LAM        added default string to calibration data
      2.39        09.03.98       BJB        On sys info screen, uses MENUTEXT.C strings.
      2.41        10.13.98       LAM        if factory then use factory date, else
                                            use pass/fail date
      2.42        12.03.98       LAM        updated 15/30 kHz frequency settings   
      2.43        12.07.98       BJB        Changed 5000W references to 5500W
                                            Uses switch/case for frequency tests
      2.44        05.26.99       LAM        commented out act lifetime counter. This is
                                            a future release.                                      
      2.45        08-31-99       JZ         added SetPressureToggle to SystemTypeMenu
      2.46        09-07-99       JZ         Changed system pressure text
      2.47        10-26-99       JZ         Modified GetCalData()
      2.46.6.1    02-07-00       JZ         removed DVS, added Mask1, Cond1, Mask2, Cond2
      2.46.6.2    02-23-00       OFI        removed 'User experience level' from menu strucutures
      2.47        04-05-00       JZ         merged Lang to trunk  
      2.48        04-18-00       SCM        Added new structures (Ver8 definition) to the System
                                            Information menu.
      2.49        04-19-00       SCM        Converted tabs to spaces.
      2.50        04-19-00       SCM        Removed the definition of TOBEDEFINED.  
      2.51        04-19-00       SCM        Converted tabs to spaces.  
      2.52        05-26-00       SCM        Checked in for testing by Laura, John.
      2.53        06-02-00       SCM        Added GetDUPSInfo() function. 
      2.54        06-09-00       SCM        Added string SysInfoBuffer8[] for P/S option.
      2.55        06-12-00       LAM        Added DUPS mask
      2.56        06-14-00       SCM        Replaced the array index[20] with 'define' LINESIZE.
      2.57        06-28-00     BEKymer/DJL  Changed all MODEL to LEVEL  also added case statements for 
                                            LEVEL_a and LEVEL_TEST; delete swserialnumber.
      2.58        07-14-00       BEKymer    Added string StrM6_7F for level ea
      2.59        07-22-00       SCM        Changed the structure parameters with ref to Psanalog,Psdigital and
                                            Psversion.
      2.60        07/22/00       SCM        Fixed the error associated with the non-inclusion of dups_api.h
      2.61        07/26/00       SCM        Changed the elements of PresetNamesMenu to RADIOLARGE of 
                                            of weld setup menu.
      2.62        07/27/00       SCM        Redefinition of StrM6_23.
      2.63        08/08/00       LAM        Redefinition of StrM6_23 to put pointers in ram.
      2.64        08/21/00       AT         Tried to fix Metric/USCS units for calibration date, didn't work out      
      2.65        08/21/00       AT         one more attempt
      2.66        08/22/00       AT         Went back to 2.63 and hard-coded formatting into GetCalData()
      2.67        08-25-00       BEKymer    Removed CustomPreset20 from  MENU PresetNamesMenu
      2.68        09-14-00       LAM        fixed ps library string (#3571)
      2.69        10-16-00       SCM        Fixed the problem with the P/S Version number not being displayed.
                                            Issue no: 3632
      2.70        01-09-01       BEKymer    Added arguments to TEXT and SUBMENU structures
      2.69.1.0    04-30-01       LAM        changed 4400 watt to 4000 
      2.69.1.1    04-25-02       BEKymer    Add 6000 W to GetPowerSupplyInfo()
      2.69.1.2    07-13-03       JOY        Added 'QVGASystemTypeMenu'.
      2.69.1.3    07-29-03       JOY        Added 'QVGAPspresetsMenu'.
      2.69.1.4    10-03-03       JOY        Calib state, Date & Run put in the
                                            -same line in system info. Screen. 
      2.71        10-08-01       LAM        merged 4000 w with preset cleanup
      2.72        08-01-03       BEKymer    Merged 2.71 and 2.69.1.1 to create 2.72 for V9.00A build
      2.73        12-04-03       BEKymer    Merged 2.72 & 2.69.1.4 to create 2.73
                                             for Ver9.00b build
      2.74        05-17-04       VSharma    Removed extern of unused strings.
      2.75        06-04-04       VSharma    Modified LoadActuatorType() for custom actuator.
      2.76        07-13-04       BEKymer    Change 2200W to 200W for Ahmet special
      2.77        07-27-04       JOY        Added FREQ60KHZ in GetPowerSupplyInfo().
      2.79        07-25-05       Bwadia     Asian Language support for System Info screen
      2.80        08-19-05       Bwadia     IsHWConfigured function used to check for
                                            VGA hardware presence
      2.81        10-24-05       Bwadia     GetPowerSupplyInfo() changed for new PS wattage
                                            implementation and SBC version TEXT item added
      2.82        01-23-06       Bwadia     Modified for tracker issue 4061. Modified GetCalData()
      2.83        02-22-06       Bwadia     SBC version string recieved from Excel sheet                                            
      2.84        12-26-06       NHAhmed    Updated GetSBCVersion(), so that to get SBC S/W form SBC
                                            with SEND_MENU_PTRS command.
      2.85        02-07-07       NHAhmed    Changed display format of date for Asian languages(yyyy/mm/dd).
      2.86        02-07-07       NHAhmed    Check-in after code review.
      2.87        04-16-07       NHAhmed    Added menu for IP Address.
      2.88        05-04-07       NHAhmed    Added Previous buuton in System Info and removed Exit Button(Tracker #4115).
      2.89        05-30-07       NHAhmed    Updated IP Address String.
      2.90        10-22-07       NHAhmed    Changes done for LangTest phase 0
      2.91        04-14-08       NHAhmed    Modified function GetCalData(). 
      2.92        08-26-08       NHAhmed    Added a function GetCalStatus(). 
      2.93        09-02-08       NHAhmed    CleanUp for multi-language support.    
      2.94        09-04-08       YGupta     CleanUp for LangTest Project.
      2.95        09-09-08       NHAhmed    CleanUp for multi-language support.    
      2.96        09-12-08       NHAhmed    Modified function GetPowerSupplyInfo(). 
		2.97        09-22-09       YGupta     Added support for MICRO.
------------------------------- DESCRIPTION ---------------------------------
*/
 
 /* This file will deal with System Info options.  This is an output only   */
 /* set of data to indicate information such as version number, type of     */
 /* actuator, cylinder size, power supply wattage, etc.                     */

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "menu.h"
#include "error.h"                             
#include "display.h"
#include "fmtstrs.h"
#include "preset.h"
#include "param.h"
#include "string.h"
#include "kpresmsg.h"             /* key pressed message definition   */
#include "actnvram.h"
#include "rtclock.h"
#include "dups_api.h"
#include "dups.h"
#include "command.h"

/*------------------------------- LOCAL DEFINES ----------------------------*/
#define CENTURY         2000

/*
 ------------------------------ GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/
STR SysBuf1Name[QVGA_LINESIZE];
SINT8 SBCVersionLabel[SBC_SW_VERSION_LENTGH+1];
STR ps_ver[8];
STR PSFreqTxt[8];

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/


extern SETUPS_Ver800     CurrentPreset;
extern CONFIGSETUP       CurrentSetup;

extern UINT16 RadioIndex;
extern UINT8 DateArr[3];
                           
extern UINT16 SystemPres60PSI;
extern UINT16 SystemPres80PSI;
extern SINT32 WelderAddrMinValue;
extern SINT32 WelderAddrMaxValue;
void GetCalData(void);
UINT16 LangStrLen(SINT8 * str); 
BOOLEAN LangCheckNull(SINT8 * Line);
void LangStrCpy(SINT8 * to, SINT8 * from);
void LangStrCat(SINT8 * to, SINT8 * from);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void StrCatTwoBytes(SINT8 * to, SINT8 * from);
void FormatIntToAscii(SINT8 Str[], UINT8 length, UINT16 val);
SINT8 * TrimLeadingBlanks(SINT8 Str_temp[]);
void GetDate(void);
/*
 ------------------------------- LOCAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

/*
 ---------------------------------- CODE -------------------------------------
*/



void GetPowerSupplyInfo(void)
{
   SINT8 temp[LINESIZE];
   SINT8 temp1[LINESIZE];
   STR *str_temp;

   switch (CurrentSetup.PSFreq)
   {
      case FREQ20KHZ:
         strcpy(PSFreqTxt,"20KHz");
         break;
      case FREQ40KHZ:
         strcpy(PSFreqTxt,"40KHz");
         break;
      case FREQ15KHZ:
         strcpy(PSFreqTxt,"15KHz");
         break;
      case FREQ30KHZ:
         strcpy(PSFreqTxt,"30KHz");
         break;
      case FREQ60KHZ:
         strcpy(PSFreqTxt,"60KHz");
         break;
      default:
         strcpy(PSFreqTxt,"Unknown");
         break;
   }

   FormatIntToAscii(temp, LINESIZE, CurrentSetup.PSWatt);
   str_temp = TrimLeadingBlanks(temp);
   strcpy(temp1, str_temp);
   strcat(temp1, "W");
   strcat(SysBuf1Name, temp1);

}

void LoadActuatorType(void)
{

   if(CurrentSetup.CustomAct)
   {
      RadioIndex = 0;
   }
   else
   {
      switch( GetActId() ){
         case BIT1:
            RadioIndex = 1;
         break;
         case BIT2:  
            RadioIndex = 2;
         break;
         case BIT3: 
            RadioIndex = 3;
         break;
         case BIT4:  
            RadioIndex = 4;
         break;
		 case BIT6:
			 RadioIndex = 7;
	     break;
         case BIT7:    
            RadioIndex = 5;
         break;
         case BIT8:       
            RadioIndex = 6;
         break;
         default:     
            RadioIndex = 0;
         break;
   }
   }
}


void GetControlLevel(void)
{
   switch(CurrentSetup.ControlLevel)
   {
      case LEVEL_t:
         RadioIndex = 0;
         break;
      case LEVEL_e:
         RadioIndex = 1;
         break;
      case LEVEL_ea:
          RadioIndex = 2;
         break;
      case LEVEL_d:
         RadioIndex = 3;
         break;
      case LEVEL_f:
         RadioIndex = 4;
         break;
      case LEVEL_a:
         RadioIndex = 5;
         break;
      case LEVEL_TEST:
         RadioIndex = 6;
          break;
    
      default:
         RadioIndex = 7;
         break;
   }
}

void GetSerialNumbers(void)
{
   SINT32 pid = DUPS_Info.ProgramId;
   ps_ver[6] = pid % 10 + '0';
   pid = pid/10;

   ps_ver[5] = pid%10 + '0';
   pid = pid/10;

   ps_ver[3] = pid % 10 + '0';
   ps_ver[4] = '.';
   ps_ver[7] = NULL;
   ps_ver[0] = ps_ver[1] = ps_ver[2] =  ' ';
    
}


void GetCalStatus(void)
{
   if(NVR.CalibPass == CALIBPASSED)
      RadioIndex = 1;
   else if(NVR.CalibPass == CALIBFAILED)
      RadioIndex = 2;
   else
      RadioIndex = 3;
}

void GetCalData(void)
/****************************************************************************/ 
/*                                                                          */
/* This function is called when the system information menu is displayed    */
/*                                                                          */
/* Inputs :  NVR.CalibPass - if default display default date else display   */
/*           pass/fail date                                                 */
/*                                                                          */
/* Outputs : CalPassStr - either pass, fail, or factory                     */
/*                                                                          */
/****************************************************************************/ 
{
   SINT16 position;
   RTC RTCCal;
   UINT16 loop;

   if((NVR.CalibPass == CALIBPASSED) || (NVR.CalibPass == CALIBFAILED))
   {
      RTCCal.Day = NVR.CalDate[1]; 
      RTCCal.Month = NVR.CalDate[0]; 
      RTCCal.Year = NVR.CalDate[2];
   }
   else
   {
      RTCCal.Day = NVR.DefCalDate[1]; 
      RTCCal.Month = NVR.DefCalDate[0]; 
      RTCCal.Year = NVR.DefCalDate[2];
   }
 if(CurrentSetup.Units == TRUE) /*Display Time in the DD/MM/YY format.*/
   {

      DateArr[0] = (UINT8)RTCCal.Day;
      DateArr[1] = (UINT8)RTCCal.Month;
      DateArr[2] = (UINT8)RTCCal.Year;
   }
   else                       /*Display Time in MM/DD/YY format*/
   {
      DateArr[0] = (UINT8)RTCCal.Month;
      DateArr[1] = (UINT8)RTCCal.Day;
      DateArr[2] = (UINT8)RTCCal.Year;
   }
}

                               
/*==========================================================================*/
/**********************************END***************************************/
/*==========================================================================*/
