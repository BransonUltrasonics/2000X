/* $Header:   D:/SWLab/VMdb/2000Series/App/UTIL.C_V   2.87   08 Jun 2010 14:11:58   NHahmed  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/* Module name: Util                                                        */
/*                                                                          */
/* Filename:    Util.c                                                      */
/*                                                                          */
/* Function Name: Utility function used just about anywhere                 */
/*                                                                          */
/*          Written by:   Barry E. Kymer                                    */
/*                Date:   06-28-95                                          */
/*            Language:   "C"                                               */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*  Revision#  Date       Author       Description                          */
/*  =========  =========  ===========  ===========                          */
/*     0       03-22-96   BEKymer      Convert to run under pSOS            */
/*     1.0     05-13-96   BEKymer      Add proper function prototyping      */
/*     2.0     06-14-96    PJ          Enabled function ResetWeldCounter    */
/*     3.0     06-20-96    PJ          Moved ResetWeldCounter to Menu6.c    */
/*     4.0     08-13-96   BEKymer      Change PowerSupply Default to 1000 W */
/*     5.0     08-23-96   LAM          deleted string.h                     */
/*     6.0     09-11-96   LAM          deleted warning                      */
/*     7.0     09-23-96   PAULG        Addes functions to InchToMm and      */     
/*                                     PoundToNewton.                       */
/*     8.0     10-30-96   BEKymer      New function GetPowerSupplyFrequency */
/*     9.0     10-31-96   BEKymer      Modify GetPower..Freq & GetP..Wattagle*/
/*    10.0     01-08-96   LAM          chged to 2000w in 3.13               */
/*    11.0     02-03-97   PaulG        chged to 2200w in 3.17               */
/*    12.0     04-25-97   LAM          added myatoi from rssnline.c         */
/*    13.0     05-02-97   PhilJ        added ReadOneMilTimer and DelayTime  */
/*                                     functions.                           */
/*    13.1     05-02-97   PhilJ        Deleted ReadOneMilTimer and DelayTime*/
/*    14.0     05-24-97   LAM          40khz release                        */
/*    15.0     05-28-97   LAM          20khz 2kw release                    */
/*    16.2.18  06-16-97   LAM          20khz 1kw release                    */
/*    16.2.19  06-16-97   LAM          40khz 800w release                   */
/*    16.2.20  06-16-97   LAM          20khz 3kw release                    */
/*    17.2.21  06-17-97   LAM          20khz 2kw release                    */
/*    17.2.23  07-03-97   PhilJ        Added PowerSupply Info fuctions      */
/*    17.2.24  07-08-97   PhilJ        Modified PS Info routines            */
/*    17.2.25  07-08-97   PhilJ        Added space chars to PS Info strings */
/*    2.26     09-24-97   LAM          made call to actuatortype only once  */
/*    2.27     10-13-97   LAM          made temp actuatortype               */
/*    2.28     11-06-97   BJB          Put space after control level letter */
/*                                      on power-up screen, related to      */
/*                                      change to StrPO_5[].                */
/*                                     Modified some comments to prevent    */
/*                                      compiler "informationals".          */
/*    2.29     03-30-98   LAM          added define for release25           */
/*    2.30     04-17-98   LAM          added more tempcode for release25    */
/*    2.31     04.24.98   JBerman      Test for AED actuator, usind Is_AED  */
/*    2.32     05.14.98   LAM          switch model 3 = a and model 4 = d   */                                                           
/*    2.33     05.15.98   Paulg        Modified the PoundToNewton function  */  
/*    2.34     05.22.98   BJB          Modified PoundToNewton() to accept   */
/*                                      tenths of pounds instead of pounds. */
/*    2.35     06.05.98   JBerman      Improved GetActuatorInfo.            */
/*    2.36     06.05.98   JBerman      Removed TempActType.                 */
/*    2.37     06.26.98   JBerman      In GetActuatorInfo: Update Strings   */
/*                                      for System Info.                    */
/*    2.38     07.07.98   JBerman      Added NVR.ActId=AENVR.               */                                             
/*    2.39     07.10.98   BJB          Doesn't strcat() to string inside    */
/*                                      GetActuatorInfo(); more than one    */
/*                                      call would extend string too far,   */
/*                                      cause crash.                        */
/*    2.40     07-17-98   BEKymer      New function GetMaxStrokeLength() to */
/*                                     return length in inches not bits     */
/*    2.41     07-30-98   BJB          Deleted GetActuatorInfo().           */
/*                                     Deleted act_nvr definition, uses     */
/*                                      actnvram.h.                         */
/*    2.42     11-09-98   LAM          added 15/30 khz change               */
/*    2.43     12-07-98   BJB          Added 1500W support                  */
/*                                     Uses switch/case for frequency tests */
/*    2.44     06-04-99   JHenry       Add GetMinStrokeLength for menuhorn.c*/
/*    2.45     06-10-99   JHenry       Deleted GetMinStrokeLength as        */
/*                                      required by Horndown code review    */
/*    2.46     08-23-99   JZ           added UpdatePressureOffset,          */
/*                                     UpdateDistanceOffset                 */
/*    2.47     08-24-99   JZ           corrected UpdateDistanceOffset       */
/*    2.48     09-03-99   LAM          added UpdatePressureOffset           */
/*    2.49     09-09-99   LAM          changed calibrated sys pressure and  */
/*                                     stroke to the NVR structure          */
/*    2.50     09-09-99   OFI          changed center f for 15 and 30kHz    */
/*                                                                DCS 3173  */
/*    2.51     09-09-99   JZ           added CheckPressure                  */
/*                                     modified UpdatePressureOffset        */
/*    2.52     09-09-99   JZ           modified UpdatePressureOffset        */
/*    2.53     10-11-99   LAM          replaced averagepressure with home   */
/*                                     pressure                             */
/*    2.54     10-26-99   BEKymer      Changed UpdateDistanceOffset() so    */
/*                                     correction is more accurate.         */
/*    2.55     11-19-99   BEKymer      Added code so update pressure is only*/
/*                                     done once system is stable           */
/*    2.56     11-30-99   BEKymer      Refined pressure update function and */
/*                                     added ClearPressureArray().          */
/*    2.57     02-08-00   LAM          set pv d/a to 0 when pressure falls  */
/*                                     below 30psi.Use currentpressure      */
/*                                     instead of homepressure to check when*/
/*                                     not ready                            */
/*    2.58     04-13-00   JZ           changed UpdateDistanceOffset         */
/*    2.59     05-09-00   JLH          Changed UpdateDistanceOffset again   */
/*    2.60     05-26-00   SCM         Checked in for testing by Laura, John */
/*    2.61     06-28-00   BEKymer     Changed all MODEL to LEVEL            */
/*    2.62     07-14-00   BEKymer     Changed LEVEL_ea text to "ea"         */
/*    2.63     07-21-00   JLH         Changed GetPowerSupplyFrequency to    */
/*                                     return center frequencies defined    */
/*                                     in psnvram.h.                        */   
/*    2.64     08-24-00   BEKymer     Added MoveToCurrentPreset function    */
/*    2.65     04-30-01   LAM         changed 4400 watt to 4000             */
/*    2.66     08-10-01   BEKymer     Add function RemoveExtraSpaces        */
/*    2.67     08-23-01   BEKymer     Check for trailing space in function  */
/*                                     RemoveExtraSpaces()                  */
/*    2.68     04-03-02   BEKymer     Add Numout function                   */
/*    2.69     04-03-02   BEKymer     Change argument for Numout            */
/*    2.70     04-04-02   BEKymer     Fix bug in Numout                     */
/*    2.71     04-05-02   LAM         Add AtLeastVersion806 function        */
/*    2.72     04-10-02   LAM         Fixed test in AtLeastVersion806       */
/*    2.73     04-24-02   BEKymer     Add ConfigureAed and ConfigureAef     */
/*    2.74     04-25-02   BEKymer     Add 6000 W to P/S functions           */
/*    2.75     03-29-04   BEKymer     Make sure NULL terminator is added    */
/*                                     anywhere actuator serial number is   */
/*                                     copied into ram or BBR.              */
/*    2.76     04-06-04   VSharma     Modified UpdatePressureOffset().      */
/*    2.77     07-14-04   BEKymer     Change all 2500w references to 200w   */
/*    2.78     07-28-04   JOY         Added FREQ60KHZ in GetPowerSupplyFrequency()& */
/*                                     GetPSInfo().                         */
/*    2.79     09-10-05   Aare        Added functions for power supply frequency */
/*                                     offsets and actuator/force gauge combinations. */
/*    2.80     10-24-05   Bwadia      PS wattage changes to the functions   */
/*                                    'GetModelNumber' and 'GetPSInfo'      */
/*    2.81     09-02-08   NHAhmed     CleanUp for multi-language support.   */
/*    2.82     09-04-08   YGupta      CleanUp for LangTest Project.         */
/*    2.83     09-09-08   NHAhmed     CleanUp for multi-language support.   */
/*    2.84     10-20-08   NHAhmed     Replaced stroke length LENGTH_7 by LENGTH_2.  */
/*    2.85     09-10-09   BEkymer     Add new define MICRO where needed     */
/*    2.86     10-21-09   BEKymer     Pass stroke and length to             */
/*                                     ConfigureActuatorBoard function      */
/*    2.87     06-08-10   PDwivedi    Modify GetMaxStrokeLength and         */
/*                                    ConfigureActuatorBoard function for   */
/*                                    Standard MICRO.                        */
/*----------------------------- DESCRIPTION --------------------------------*/

/* This module contains general purpose functions.                          */



/*----------------------------- PSEUDO CODE --------------------------------*/



/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define MAXPARAMCHANGED            10
#define MAX_ACCEPT_PRESS          900 /* outside this pressure range we will reduce */
#define MIN_ACCEPT_PRESS          300 /* signal to PV                               */
#define PRESSURE_POINTS             5 /* Number of 1/4 sec points before considered stable */
#define UPDATE_PRESSURE_TOLERANCE   5 /* Tolerance (in tenths of PSI) before stable */
#define NOT_INITIALIZED        0xffff /* Actuator novram has not been written to */

/*------------------------------ INCLUDES ----------------------------------*/

#include "portable.h"
#include "actnvram.h"
#include "preset.h"
#include "string.h"
#include "param.h"
#include "psnvram.h"
#include "spidd.h"
#include "actnvram.h"
#include "menu7a.h"
#include "state.h"
#include "mansensr.h"
#include "digout.h"
#include "rtclock.h"
#include "battram.h"
#include "snsrcalb.h"
#include "menu6.h"


/*------------------------- FUNCTION PROTOTYPING ---------------------------*/

#include "util.h"


/*----------------------------- GLOBAL DATA --------------------------------*/

SINT16 ForceTableDelta = 0,VelocityTableDelta = 0;
enum  PARAM ParamChanged[MAXPARAMCHANGED];/* Array to hold indexes of param's changed */


static UINT16 PressureArray[PRESSURE_POINTS];
static UINT16 PresIndex = 0;



/*------------  Things to be removed eventually (GLOBALS!!)  ---------------*/


/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

extern const UINT16  CurrentVersion;    /* Current version/revision in binary, no decimal */

extern SETUPS_Ver800 CurrentPreset;
extern SETUPS_Ver800 MaxLimit;
extern CONFIGSETUP CurrentSetup;
extern PSNOVRAMDATA PSNvRamData;
extern SINT32 DistanceOffset;
extern SINT32 Distance1;
extern SINT32 CurrentPressure;

//extern SINT8 SysInfoBuffer2[LANGSIZE][MESSAGESIZE];
extern SINT16 ForceTableCylFactor,VelocityTableCylFactor;

/*-------------------------------- CODE ------------------------------------*/



void strsub(SINT8 string[], SINT8 old, SINT8 new)
/***************************************************************************/
/*                                                                         */
/*  This function will replace all 'old' characters in the passed string   */
/*  with the 'new' passed character.                                       */
/*                                                                         */
/***************************************************************************/
{
   SINT16 len, index = 0;

   len = strlen(string);
   while (index <= len) {
      if (string[index] == old) string[index] = new;
      index++;
   }
}


void RemoveExtraSpaces(UINT8 string[])
/***************************************************************************/
/*                                                                         */
/*  This function will remove extra spaces in a string leaving only one    */
/*  within a group.  For example:                                          */
/*  "  ABC  DEF     GHIJK  +  112 "  would be replaced with                */
/*  "ABC DEF GHIJK +112"                                                   */
/*                                                                         */
/*  Notes:                                                                 */
/*  1) One special exception.  All spaces between a sign (+/-) and any     */
/*     character will be removed.                                          */
/*  2) The remaining part of the string will be null terminated.           */
/*  3) All leading spaces before the first alpha/numeric character will    */
/*     be eliminated.                                                      */
/*  4) All trailing spaces will be eliminated.                             */
/*                                                                         */
/***************************************************************************/
{
   SINT16 len, SrcIndex = 0, DstIndex = 0;
   UINT16 SpaceFound = TRUE;  /* Setting to TRUE eliminates leading spaces */

   len = strlen((SINT8 *)string);
   while (SrcIndex < len) {
      if (string[SrcIndex] == ' ') {
         if (SpaceFound == TRUE) {
            SrcIndex++;
         }
         else {
            SpaceFound = TRUE;
            string[DstIndex++] = ' ';
         }
      }
      else {
         if ((string[SrcIndex] == '+') || (string[SrcIndex] == '-') ){
            SpaceFound = TRUE;
            string[DstIndex++] = string[SrcIndex++];
         }
         else {
            string[DstIndex++] = string[SrcIndex++];
            SpaceFound = FALSE;
         }
      }
   }
   if (string[DstIndex - 1] == ' ')   /* Check for trailing space */
      string[DstIndex - 1] = 0;
   else
      string[DstIndex] = 0;
}

UINT16 GetPowerSupplyFrequency(void)
/****************************************************************************/   
/*                                                                          */
/* This function will get the power supply frequency from the NOVRAM and    */
/* return the value in hertz (i.e. 19950, 39900).                           */
/*                                                                          */
/****************************************************************************/   
{
   UINT16  Frequency;


   switch (CurrentSetup.PSFreq)
   {
      case FREQ15KHZ:
         Frequency = CENTER15KHZ;
         break;
      case FREQ20KHZ:
         Frequency = CENTER20KHZ;
         break;
      case FREQ30KHZ:
         Frequency = CENTER30KHZ;
         break;
      case FREQ60KHZ:
         Frequency = CENTER60KHZ;
         break;   
      case FREQ40KHZ:
      default:
         Frequency = CENTER40KHZ;
         break;
   }
   return(Frequency);
}


UINT16 GetPowerSupplyFrequencyOffset(void)
/****************************************************************************/   
/*                                                                          */
/* This function will get the power supply frequency from the NOVRAM and    */
/* return the offset value in hertz (i.e. 500 for 20KHz etc                 */
/*                                                                          */
/****************************************************************************/   
{
   UINT16  Frequency;


   switch (CurrentSetup.PSFreq)
   {
      case FREQ15KHZ:
         Frequency = FREQ15_OFF;
         break;
      case FREQ20KHZ:
         Frequency = FREQ20_OFF;
         break;
      case FREQ30KHZ:
         Frequency = FREQ30_OFF;
         break;
      case FREQ60KHZ:
         Frequency = FREQ60_OFF;
         break;   
      case FREQ40KHZ:
      default:
         Frequency = FREQ40_OFF;
         break;
   }
   return(Frequency);
}


/*---------------------------------------------------------*/
/* This function takes a  value that is stored  in integer */
/* form representing inches and converts it into a float   */
/* value representing millimeter for display               */
/*---------------------------------------------------------*/
float InchToMm(SINT32 IInches)
{
    float FVal;
    FVal = ((float)IInches * 25.4)/10000;
    return(FVal);
}
/* conversion of a SINT32 lbs-force value in a SINT32 Newton value*/



/*----------------------------------------------------------*/
/* This function takes a  value that is stored  in integer  */
/* form representing lbs-force and converts it into a float */
/* value representing Newton for display.  Input value is   */
/* in tenths of pounds.                                     */
/*----------------------------------------------------------*/
float PoundToNewton(SINT32 ILbs)
{
    float IVal;
    IVal = (float)(((ILbs * 4448) + 5000)/10000);
    return(IVal);
}

void FormatIntToAscii(SINT8 Str[], UINT8 length, UINT16 val)
{
   UINT8 i;
   for (i = 0; i < length - 1; i++)
      Str[i] = FILLCHAR;
   Str[i] = 0x00;
   while(val != 0)        
   {
      Str[--i] = (val%10) + 0x30;
      val /= 10;
   }
}

SINT8 * TrimLeadingBlanks(SINT8 Str_temp[])
/****************************************************************************/
/*Description:-                                                             */
/* Trim the leading spaces in the Input string and returns string pointer   */
/****************************************************************************/
{
   SINT8 *StrPtr= NULL_PTR;
   UINT16 Index;

   for(Index=0; Index < strlen(Str_temp); Index++)
   {
      if(Str_temp[Index]!=' ')
      {
         StrPtr = &Str_temp[Index]; 
         break;
      }
   }

   return(StrPtr); 
}

SINT32 GetMaxStrokeLength(void)
/****************************************************************************/   
/*                                                                          */
/*  This function will return the maximum stroke length (in inches) for the */
/*  value returned by GetStrokeLength().  Returned value is scaled up by    */
/*  10000.                                                                  */
/*                                                                          */
/****************************************************************************/   
{
   UINT16 Stroke;
   SINT32 RetVal;

   Stroke = GetStrokeLength();
   switch (Stroke) {
      case CUSTOMLEN:
         RetVal = 99999;         /* Keep it at 5 digits so it fits */
         break;

      case LENGTH_4:
         RetVal = 40000;
         break;

      case LENGTH_5:
         RetVal = 50000;
         break;

      case LENGTH_6:
         RetVal = 60000;
         break;

      case LENGTH_2:
         RetVal = 20000;
         break;
     
      case LENGTH_8:
         RetVal = 80000;
         break;

      case LENGTH_80:
         RetVal = 31496;
         break;

      case LENGTH_100:
         RetVal = 39370;
         break;

      case LENGTH_125:
         RetVal = 49212;
         break;

     /* case LENGTH_160:
         RetVal = 62992;
         break;*/
      case LENGTH_50:
         RetVal = 19685;
         break;

      default:
         RetVal = 40000;
         break;
   }
   return(RetVal);
}



void ClearPressureArray(void)
/****************************************************************************/   
/*                                                                          */
/*  This function will clear the pressure array, throwing away all old      */
/*  readings.                                                               */
/*                                                                          */
/****************************************************************************/   
{
   UINT16 Index;
   
   for (Index = 0; Index < PRESSURE_POINTS; Index++) {
      PressureArray[Index] = 0;
   }
}



void UpdatePressureOffset(void)
/****************************************************************************/   
/*                                                                          */
/*  This function will read current averaged system pressure at ULS and     */
/*  update velocity and force offset. If the CurrentPressure is greater than*/
/*  the Calibrated SysPressure the TableDelta is positive                   */
/*                                                                          */
/*  Inputs:  CurrentPressure - averaged pressure at home                    */
/*           NVR.CalSysPressure - sensor calibrated pressure                */
/*           VelocityTableCylFactor - updated when cylinder size changed    */
/*           ForceTableCylFactor - updated when cylinder size changed       */
/*                                                                          */
/*  Outputs: VelocityTableDelta - used in SetPV                             */
/*           ForceTableDelta - used in SetPV                                */
/*                                                                          */
/****************************************************************************/   
{
   
   SINT16 PressureDifference;
   SINT32 TempVelDelta,TempForceDelta;
   UINT16 LoopIndex;
   UINT16 HighPressure = LOW_PRESSURE - PRESSURE_TOLLERANCE; /* Set to lowest possible pressure  */
   UINT16 LowPressure = HIGH_PRESSURE + PRESSURE_TOLLERANCE; /* Set to highest possible pressure */
   
   PressureArray[PresIndex++] = CurrentPressure;
   if (PresIndex >= PRESSURE_POINTS) PresIndex = 0;
   for (LoopIndex = 0; LoopIndex < PRESSURE_POINTS; LoopIndex++) {
      if (PressureArray[LoopIndex] > HighPressure) HighPressure = PressureArray[LoopIndex];
      if (PressureArray[LoopIndex] < LowPressure) LowPressure = PressureArray[LoopIndex];
   }
   if ( ((LowPressure + UPDATE_PRESSURE_TOLERANCE) > HighPressure) &&
         (CurrentPressure > (LOW_PRESSURE - PRESSURE_TOLLERANCE)) &&
         (CurrentPressure < (HIGH_PRESSURE + PRESSURE_TOLLERANCE)) &&
         (LowPressure != 0) ) {
      PressureDifference = (SINT16)(CurrentPressure - NVR.CalSysPressure);
      TempVelDelta = PressureDifference * VelocityTableCylFactor;
      VelocityTableDelta = (SINT16)(TempVelDelta >> 8);
      TempForceDelta = PressureDifference * ForceTableCylFactor;
      ForceTableDelta = (SINT16)(TempForceDelta >> 8);
      SetPV((UINT16)CurrentSetup.IdleSpeed, HOLD_TO_HOME);   /* Also update home idle value  */        
      //ToggleUser1();                                         /* TEST CODE, let user know pressure updated */
   }
      
   if ((CurrentPressure < MIN_ACCEPT_PRESS) || (CurrentPressure > MAX_ACCEPT_PRESS)) 
      SetPV( 0, ZERO_PSI );
}



void UpdateDistanceOffset(void)
/****************************************************************************/   
/*                                                                          */
/* This function will update distance offset correction factor which is used*/
/* in the SetPV function based on the part contact distance.  This distance */
/* offset is an estimate which results in aprox. 5.50  to 6.00 lbs/in.      */
/* and approx. three times greater for 15kHz                                */
/* depending on rounding at any given distance.                             */
/*                                                                          */
/* 1280 is added (or subtracted) to aid in rounding.  It's slightly more    */
/* than half the shift value of 2048 (shift 11).                            */
/*                                                                          */
/* This results in a correction of (+ for pos offset, - for neg offset):    */
/*                                                                          */
/*   0.5000"   3 lbs      2.0000"   11 lbs      3.5000"   19 lbs            */
/*   1.0000"   6 lbs      2.5000"   14 lbs      4.0000"   22 lbs            */
/*   1.5000"   8 lbs      3.0000"   17 lbs      4.5000"   25 lbs            */
/*                                                                          */
/*  For 15kHz                                                               */
/* This results in a correction of (+ for pos offset, - for neg offset):    */
/*                                                                          */
/*   0.5000"   7 lbs      2.0000"   29 lbs      3.5000"   51 lbs            */
/*   1.0000"  15 lbs      2.5000"   37 lbs      4.0000"   59 lbs            */
/*   1.5000"  22 lbs      3.0000"   44 lbs      4.5000"   66 lbs            */
/*                                                                          */
/*                                                                          */
/****************************************************************************/   
{
   SINT32 Temp1;
   
   Temp1 = Distance1 - NVR.CalStrokeLen;
   if (CurrentSetup.PSFreq == FREQ15KHZ)
   {
      if (Temp1 > 0) {
         DistanceOffset = ((Temp1 + (Temp1 >>1) + 640) >> 10); /* Offset is positive */
      }
      else {
         DistanceOffset = ((Temp1 - (Temp1 >>1) - 640) >> 10); /* Offset is negative */
      } 
   }   
   else  /* other than 15kHz */
   {
      if (Temp1 > 0) {
         DistanceOffset = ((Temp1 + (Temp1 >>3) + 1280) >> 11); /* Offset is positive */
      }
      else {
         DistanceOffset = ((Temp1 - (Temp1 >>3) - 1280) >> 11); /* Offset is negative */
      }   
   }  
}



BOOLEAN CheckPressure( UINT16 *TestPresFlag, UINT16 PressureValue )
/****************************************************************************/     
/*                                                                          */
/* This function will return true when system pressure is within tolerance  */
/* for either 60 or 80 psi, and sets the flag to false when set pressure    */
/* is 60 and true when is 80                                                */
/*                                                                          */
/****************************************************************************/   
{
   BOOLEAN ReturnValue;
   
   if( ((HIGH_PRESSURE - PRESSURE_TOLLERANCE) < PressureValue) && 
      ((HIGH_PRESSURE + PRESSURE_TOLLERANCE)  > PressureValue) ){
         *TestPresFlag = TRUE;
         ReturnValue = TRUE;
   }
   else if( ((LOW_PRESSURE - PRESSURE_TOLLERANCE) < PressureValue) &&      
      ((LOW_PRESSURE + PRESSURE_TOLLERANCE)  > PressureValue) ){
         *TestPresFlag = FALSE;
         ReturnValue = TRUE;
   }
   else { 
      ReturnValue = FALSE;
   }   
   return (ReturnValue);   
}            



void Numout(UINT32 Value, UINT8 Base, UINT8 LC, STR Ptr[], UINT8 Width)
/*****************************************************************************/
/*                                                                           */
/*  ABSTRACT                                                                 */
/*  --------                                                                 */
/*  This function converts a number from binary form to an ASCII string for  */
/*  display or printing.                                                     */
/*                                                                           */
/*  PARAMETERS                                                               */
/*  ----------                                                               */
/*     Value   The number whose ASCII representation is desired.             */
/*     Base    An integer between 2 and 16, inclusive, specifying in what    */
/*             number base 'Value' is to be interpreted.                     */
/*     LC      (Leading Character): Leading zeroes will be designated by     */
/*             'LC', which should be an ASCII character.                     */
/*     Ptr     The address of the buffer of at least 'Width' bytes, into     */
/*             which the ASCII representation is placed.                     */
/*     Width   The number of character positions desired in the ASCII format.*/
/*                                                                           */
/*  DESCRIPTION                                                              */
/*  -----------                                                              */
/*  If the 'Value' is too large to be represented in 'Width' characters of   */
/*  the chosen 'Base', then only the least significant digits will be        */
/*  represented.                                                             */
/*                                                                           */
/*  There is no error checking.  Input values must conform to the restraints:*/
/*             Base > 1 and Base < 17                                        */
/*             Width > 0                                                     */
/*                                                                           */
/*****************************************************************************/
{
   STR   Digits[] = "0123456789ABCDEF";
   UINT8 i;
   
   for (i = 1; i <= Width; i++) {
      Ptr[Width - i] = Digits[Value % Base];
      Value /= Base;
   }
   i = 0;
   while ((Ptr[i] == '0') && (i < Width-1)) {
      Ptr[i] = LC;
      i++;
   }
}


BOOLEAN AtLeastVersion806(void)
/****************************************************************************/     
/*                                                                          */
/* This function will return true when the current software version is 8.06 */
/* or above.                                                                */
/*                                                                          */
/* Inputs: NVR.PSVersion - Software Version stored in the actuator          */
/*                                                                          */
/****************************************************************************/   
{
BOOLEAN Version806 = TRUE;

   if((NVR.PSVersion < 806) || (NVR.PSVersion >= NOT_INITIALIZED)) 
      Version806 = FALSE;
   return(Version806);
}   



void ConfigureAed(void)
/****************************************************************************/     
/*                                                                          */
/*  This function is called from the main menu as a hidden function.  It    */
/*  will initialize the actuator nvram as an aed, with 3" diameter cylinder */
/*  and 4" stroke.  It will set the actuator serial number to "BUCMMDDYY".  */
/*                                                                          */
/****************************************************************************/     
{
   ConfigureActuatorBoard (NVR_AED, LENGTH_4, SIZE3_0);
}



void ConfigureAef(void)
/****************************************************************************/     
/*                                                                          */
/*  This function is called from the main menu as a hidden function.  It    */
/*  will initialize the actuator nvram as an aef, with 3" diameter cylinder */
/*  and 4" stroke.  It will set the actuator serial number to "BUCMMDDYY".  */
/*                                                                          */
/****************************************************************************/     
{
   ConfigureActuatorBoard (NVR_AEF, LENGTH_4, SIZE3_0);
}



void ConfigureMicro(void)
/****************************************************************************/     
/*                                                                          */
/*  This function is called from the main menu as a hidden function.  It    */
/*  will initialize the actuator nvram as a MICRO with 40 mm diameter       */
/*  cylinder and 2" stroke.  It will set the actuator serial number to      */
/*  "BUCMMDDYY".                                                            */
/*                                                                          */
/****************************************************************************/     
{
   ConfigureActuatorBoard (NVR_MICRO, LENGTH_2, SIZE_40);
}



void ConfigureActuatorBoard(UINT16 ActType, UINT16 Stroke, UINT16 Cylinder)
/****************************************************************************/     
/*                                                                          */
/*  This function does the real work for the three functions above.         */
/*                                                                          */
/*  Parameters: ActType  - NVR_AED, NVR_AEF or NVR_MICRO                    */
/*              Stroke   - LENGTH_2 or LENGTH_4                             */
/*              Cylinder - SIZE3_0 or SIZE_40                               */
/*                                                                          */
/*  On Exit :   Entire contents of actuator novram rewritten                */
/*              Serial number changed to "BUCmmddyy*"                       */
/*                                                                          */
/****************************************************************************/     
{
   CONFIGSETUP *BBRPtr;
   STR         SerialNumber[] = "BUC      ";
   RTC         RTCCal;
   UINT16      i;

   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   TestWriteToNvram();             /* Erase everything currently in Novram */
   TestReadFromNvram();

/* Write the actuator type */
   BBRPtr->Actuator = ActType;
   SetActId(ActType);

/* Now write the stroke length */
   BBRPtr->StrokeLen = Stroke;
   SetStrokeLength(BBRPtr->StrokeLen);  
   SetDefStrokeLength(BBRPtr->StrokeLen);  

/* Now write the cylinder diameter */
   BBRPtr->CylinDiameter = Cylinder;
   SetCylSize(BBRPtr->CylinDiameter);     
   SetDefCylSize(BBRPtr->CylinDiameter);     

/* Now create and then write a default serial number */
   RTCCal = RtcReadDateandTime();     /* Get date when calibration complete */
   Numout((UINT32)RTCCal.Month, 10, '0', &SerialNumber[3], 2);
   Numout((UINT32)RTCCal.Day, 10, '0', &SerialNumber[5], 2);
   Numout((UINT32)RTCCal.Year, 10, '0', &SerialNumber[7], 2);
   SerialNumber[9] = '*';
   SetSerNum(SerialNumber);
   SetDefSerNum((UINT8 *)SerialNumber);

/* Now put new serial number in current setup and BBR */
   for (i=0; i<MAXSERIALNUM; i++) {
      BBRPtr->ActSerialNumber[i] = SerialNumber[i];
      CurrentSetup.ActSerialNumber[i] = SerialNumber[i];
   }
/* Note: The CurrentSetup.ActSerialNumber member is larger than MAXSERIALNUM */
/*       allowing a NULL terminator to be added at location MAXSERIALNUM.    */

   
   if(BBRPtr->Actuator==NVR_MICRO)
   {
      if(BBRPtr->StrokeLen==LENGTH_50)//2000X micro std prod
         SetEncoderType(ENCODER_ENGLISH);
   }

   BBRPtr->ActSerialNumber[i] = NULL;
   CurrentSetup.ActSerialNumber[i] = NULL;
   
   GetSerialNumbers();
   BuildVelocityTable();
   SetDefCalSysPressure((SINT16)LOW_PRESSURE);
   SetDefCalStrokeLength(DEF_CAL_LENGTH);
   SetDefPressure(); 
   SetDefLoadCell();
   SetDefForce();

   NvrCopyDeftoNon();   /* copy actuator def novram settings to working novram settings */
   UpdateNVRSpringRate(); 
   SetPSVersionNVR();
   BuildDefaultSpringRate(); /* update Home Offset must */
}



BOOLEAN IsConfiguredActuatorForceGauge(BOOLEAN AED_LC, BOOLEAN AEF_LC, BOOLEAN AED_SB, BOOLEAN AEF_SB)
{
   BOOLEAN ret;
   if ( (NVR.ActId == NVR_AED) || (NVR.ActId == NVR_MICRO) )
      {
      if (NVR.ForceGauge == SBEAM)
         ret = AED_SB;
      else
         ret = AED_LC;
      }
   else
      {
      if (NVR.ForceGauge == SBEAM)
         ret = AEF_SB;
      else
         ret = AEF_LC;
      }
   return ret;
}
