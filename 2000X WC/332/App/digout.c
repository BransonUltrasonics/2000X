/* $Header:   D:/SWLab/VMdb/2000Series/App/DIGOUT.C_V   2.79.1.0   Jul 10 2007 08:56:44   lmarkure  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96,97           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
-------------------------- MODULE DESCRIPTION -------------------------------
  Name: digout.c

------------------------------ REVISIONS ------------------------------------

   Revision #  Date      Author   Description
   ----------  -------   ------   -----------
        0      3/26/95   LAM      Initial
        1      7/03/96   LAM      removed unused SV4 functions    
        2      7/10/96   LAM      added sonicsonflag              
        3      08-07-96  BEKymer  New functions SeekOn & SeekOff
        4      08-08-96  BEKymer  New function PSSeek
        5      08/13/96  LAM      added checkready                
        6      08-27-96  BEKymer  New function - CheckGeneralAlarmFlag
        7      9/09/96   LAM      removed unused SV set & clear functions    
        8      09-16-96  BEKymer  Added test for DryCycleFlag in PSRun, 
                                  PSSeek & PSTest
        9      10-03-96  BEKymer  New functions for Reject/Suspect Off/On
       10      10-28-96  BEKymer  Fix CNTL_PORT for suspect/reject outputs
                                  Add function for SystemFault On/Off
                                  Clear Reject, Suspect, and SystemFault in General Alarm
       11      11-11-96  BEKymer  Check for door open before allowing SV on
       12      11-14-96  BEKymer  Turn on cooling whenever sonics are on
       13      01-20-97  LAM      added function for trigswactive            
       14      01-26-97  LAM      chged system fault functions to PBrelease  
       15      02-06-97  LAM      deleted unused variables                   
       16      03-04-97  PhilJ    Added incrementing of PSLifetime counter in PSRun().
       17      05-13-97  PhilJ    Corrected incrementing of PSLifetime counter
       18.2.25 06-05-97  BEKymer  Only allow PSReset only if overload has
                                  occured or door is open
       19.2.25 07-01-97  JBerman  For future functons: adding MissingPartOn/Off
       20.2.27 07-14-97  BEKymer  Renamed Missing Part functions for Warning
       20.2.28 07-16-97  BEKymer  Added ThermalOLFlag
       20.2.29 08-07-97  BEKymer  Increment ThermalOLFlag instead of TRUE
       21.2.30 08-08-97  LAM      added seek test                        
       21.2.31 08.15.97  JBerman  Replaced Every AccessControlOutputPorts
                                  with the appropriate 8255 control  
       22.2.32 08-21-97  LAM      added sonics on led                    
       2.33    08-29-97  LAM      added seek test                        
       2.34    09-02-97  LAM      removed seek test                        
       2.35    09-04-97  BEKymer  Make WarningOn() & WarningOff() use all 3
                                  user outputs until it can be defined later
       2.36    09.09.97  JBerman  8255 Ports access efficeincy 
       2.37    09.11.97  JBerman  Removed old commented code
       2.38    09.30.97  JBerman  In PSReset, SV3Off was removed.
       2.39    10.01.97  JBerman  In PSReset, The following were removed:
                                                SonicsOnFlag = FALSE;
                                                UpdateLED(ZEROPERCENTLED,OFF);
       2.40    10-02-97  LAM      added seek test                        
       2.41    10.13.97  JBerman  DCS 1968, 1807.
       2.42    10.14.97  JBerman  Eliminated Bit_5 & Bit_6 -> WarningOn/Off
       2.43    10.16.97  LAM      deleted inp.trigger=FALSE in svoff        
       2.44    10.24.97  JBerman  Changed BIT_4 to BIT_6 (WarningOn/Off) DCS2083
       2.45    10.24.97  JBerman  Changed BIT_6 to BIT_5 (WarningOn/Off) DCS2083
       2.46    11.18.97  LAM      deleted unused seek functions             
       2.47    12.01.97  JBerman  Modified: 1) SV3Off with CoolValOff.
                                            2) SV3On with CoolValOn.
       2.48    12-11-97  LAM      removed seek test
       2.49    01-30-98  BJB      Doesn't increment lifetime counter in PSRun(),
                                   moved this to WeldManager() FINALDATASTATE.
       2.50    02-09-98  BJB      Explicitly initializes GeneralAlarmFlag to 0.
       2.51    02.12.98  JBerman  Removed CoolingValveOn from: PSTest, PSSeek
       2.52    05-14-98  BEKymer  Use EXTERNAL_SEEK_ON_VAL in PSSeek()
       2.54    09-08-98  BEKymer  In PSReset() set the amplitude back to 10%
                                  (as is done in PSIdle()), because sometimes
                                  PSReset() is called but PSIdle() is not.  
                                  This means the amplitude is not set back to
                                  10% and spikes are occurring.
       2.55    09-27-99  BEKymer  In SVOff(), SetPV to HOLD_TO_HOME, so PV is
                                  always correct even if cycle aborted.
       2.56    10-26-99  JZ       replaced PV_IDLE_VALUE with CurrentSetup.IdleSpeed
       2.57    10-27-99  JZ       typecasted IdleSpeed in SetPV() call
       2.57    11-30-99  BEKymer  Create SetUser1(), SetUser2(), ClearUser1(), ClearUser2(),
                                  ToggleUser1() and ToggleUser2().
       2.59    07-12-00  BEKymer  Changed SETUPS to SETUPS_Ver800
                                  Changed GeneralAlarmFlag to GeneralAlarmLFlag
       2.60    07-13-00  BEKymer  Don't turn off Cooling Valve in PSIdle()
       2.61    08/28/00  SCM      Added function HSReset() relating to HORNSCAN ABORT.
       2.62    08/29/00  AT       Fixed HSReset, included psos.h, ticks.h
       2.63    10/06/00  LAM      Increase HSReset to 20ms. ISSUE(3597)
       2.63.1  02-14-03  BEKymer  Activate PBRelease whenever SV is turned off
       2.63.2.1 03-05-03 BEKymer  Remove code in PSIdle() and PSReset() so sonics
                                   stay once they are on.   Used for FCC testing
       2.65    04-10-03  BEKymer  Move 8.4S special version onto the tip as 2.65
       2.66    04-11-03  BEKymer  Uncomment PSIdle() and PSReset()
       2.67    04-11-03  BEKymer  Add back closing brace (removed one too many)
       2.68    06-23-03  BEKymer  Condition ActClrOn with lack of EQ2
       2.69    06-25-03  BEKymer  Don't call PBReleaseOn() in SVOff() if in
                                   horn down mode, because it only happens the first
                                   time and is confusing to PLC's.  Issue # 3759
       2.70    12-01-03  BEKymer  Add define to turn code into FFC test                            
       2.71    04-06-04  VSharma  Added functions for User configurable outputs.
                                  Added MemoryReset().
                                  Modified ClearGeneralAlarm() and PSRun(). 
       2.72    04-23-04  VSharma  Modified UserCfgOutputOn() & UserCfgOutputOff().                                    
       2.73    04-27-04  VSharma  Removed WarningOn() & WarningOff().
       2.74    04-30-04  VSharma  Modified 'SetSAS()'.
       2.75    05-17-04  VSharma  Removed function ToggleUser1(),ToggleUser2(),SetUser1(),
                                  SetUser2(),ClearUser1() & ClearUser2().
                                  Merge function SVOutOff() in SVOff().
       2.76    06-15-04  BEKymer  Make user defined outputs active low
       2.77    07-21-04  JOY      Sonics not activated, if sonics disable input is active
                                  in PSSeek().
       2.78    09-14-04  JOY      Output pins made active high, when output needs to be 
                                   disabled, in RefreshOutputStatus().
       2.79    01-09-06  LAM       Added Estop Reset 
       2.79.1.1 07-10-07 LAM      Removed PBReleaseOn from SVOff
       
       

              
----------------------------- DESCRIPTION -----------------------------------
    
                                                                              
       
                                                                              
                                                                              
     
--------------------------- INCLUDE FILES ----------------------------------
*/
#include "portable.h"
#include "preset.h"
#include "outports.h"
#include "led.h"
#include "mansensr.h"
#include "menu.h"
#include "digout.h"
#include "state.h"
#include "ticks.h"
#include "psos.h"
#include "alarms.h"
#include "weld_obj.h"

#define NUM_CTRL_PORTS  3    // j.b
#define AMPOFFVAL      10    // Amplitude Off Value; Percent.

extern UINT8 PortRegisterA; // U67   j.b
extern UINT8 PortRegisterB; // U79   j.b
extern UINT8 PortRegisterC; // U67   j.b

extern SETUPS_Ver800 CurrentPreset;
extern CONFIGSETUP CurrentSetup;
extern WELD_DATA WeldingResults;
extern BOOLEAN  HornDownFlag;

BOOLEAN SonicsOnFlag;
static  BOOLEAN GeneralAlarmLFlag = 0;

extern  UINT16 DryCycleFlag;
extern enum  WELDSTATES WeldState;
UINT16  ThermalOLFlag;
extern WELD_DATA FinalResults;
extern BOOLEAN  SVInterlockActive;
extern UINT16 MemoryResetFlag;
extern BOOLEAN ConfirmPresetFlag;

extern BOOLEAN VGA_ScreenMicronCalFlag;
extern SINT32 VGA_ScreenMicronCalAmp;

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/                                                              

// #define DIGOUT_UNIT_TEST 0
//#define  FCC_TEST

BOOLEAN SonicDisabledFlag = FALSE;  
/*
 ----------------------------- LOCAL FUNCTIONS ----------------------------------
*/                                                           


/*
 ------------------------------- LOCAL DATA ------------------------------------
*/

BOOLEAN ReadyFlag = FALSE;
extern INBITS Inp;
static UINT16 StatusOfUser1 = FALSE;
static UINT16 StatusOfUser2 = FALSE;
#ifdef FCC_TEST
UINT16 FCCTestFlag = FALSE;
#endif

/*
 ---------------------------------- CODE ---------------------------------------
*/

void LockPowerOn(void){
   PortRegisterA = (PortRegisterA | BIT_6_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}


void PowerDownSystem(void){
   PortRegisterA = (PortRegisterA & BIT_6_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}
 

void SetGeneralAlarm(void){
   PortRegisterC = (PortRegisterC | BIT_0_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_2 = PortRegisterC;
   GeneralAlarmLFlag = TRUE;
}


void ClearGeneralAlarm(void){
   PortRegisterC = (PortRegisterC & BIT_0_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_2 = PortRegisterC;

   GeneralAlarmLFlag = FALSE;
   RejectOff();                   /* Also clear the Reject alarm output     */
   SuspectOff();                  /* While we're at it, do Suspect also     */
   //WarningOff();                  /* Might as well do warning output too    */
   UserCfgOutputOff(OUTPUT_NOTE); /* Clear the Warning Alarm output */
   UserCfgOutputOff(OUTPUT_NO_CYCLEALARM); /* Clear the No Cycle Alarm output */
   UserCfgOutputOff(OUTPUT_OLDALARM); /* Clear the Overload Alarm output */
   UserCfgOutputOff(OUTPUT_MDFY_ALARM);/* Clear the Modified Alarm output */
   UserCfgOutputOff(OUTPUT_MISSING_PART);/* Clear the MissingPart output */

}

BOOLEAN CheckGeneralAlarmFlag(void){
   return(GeneralAlarmLFlag);
}

void SetAuxAlarms(void){                                      /* For level 1, do all alarms       */
   PortRegisterA = (PortRegisterA | SET_AUX_ALARMS_PORT0);    // !!!
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void SetReady(void){
   PortRegisterC = (PortRegisterC | BIT_1_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_2 = PortRegisterC;
   ReadyFlag = TRUE;
}

void ClearReady(void){
   PortRegisterC = (PortRegisterC & BIT_1_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_2 = PortRegisterC;
   ReadyFlag = FALSE;
}

BOOLEAN GetReadyStatus(void){
   return(ReadyFlag);
}

void ClearSAS(void){
   PortRegisterC = (PortRegisterC & BIT_2_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_2 = PortRegisterC;
}

void SetSAS(void)
/***************************************************************************/
/* This function will enable the Sonics Active Signal.This signal is not   */
/* activated if 'SonicDisable' input is high.                              */
/***************************************************************************/
{
   if (SonicDisabledFlag == FALSE) {
      PortRegisterC = (PortRegisterC | BIT_2_SET);   
      *(UINT8 *)CONTROL_OUTPUT_PORT_2 = PortRegisterC;
   }
}

void EnableSVOn(void){
UINT8 *PortE;
   PortE = (UINT8 *) 0xFFFA11;        /* enable SV port  */
   *(PortE) = 0x08;
}

void SVOn(void){                               /* Turn on SV1 */
   if (Inp.DoorOpen == FALSE){
      PortRegisterB = (PortRegisterB | BIT_4_SET);   
      *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
   }
}

void SV2On(void){
   PortRegisterB = (PortRegisterB | BIT_5_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
}

void CoolValOn(void){
   PortRegisterB = (PortRegisterB | BIT_6_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
}

void SVOff(void){     /* Turn off SV1 */

   UINT8 *PortE;

   PortRegisterB = (PortRegisterB & BIT_45CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
   PortE = (UINT8 *) 0xFFFA11;        /* Disable SV port  */
   *(PortE) = 0x00;
   SetPV((UINT16)CurrentSetup.IdleSpeed, HOLD_TO_HOME);           
   UserCfgOutputOff(OUTPUT_SV_INTERLOCK);
}

void CoolValOff(void){
   PortRegisterB = (PortRegisterB & BIT_6_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
}

void PSIdle(void){

#ifdef FCC_TEST
   if (FCCTestFlag == FALSE) {
#endif   
   PortRegisterB = (PortRegisterB & (BIT_123CR & BIT_0_CLR));   
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
   SonicsOnFlag = FALSE;
   UpdateLED(ZEROPERCENTLED,OFF);
//   PortRegisterB = (PortRegisterB & BIT_6_CLR);   // Cooling Valve Off 
//   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
   SetCurrentAmp(AMPOFFVAL);       // Initial amplitude           

#ifdef FCC_TEST
   }
#endif
}

/*---  Only allow reset if there really is an OL or door is open  ---*/

void PSReset(void){
   if ( (Inp.OL == TRUE) || (Inp.DoorOpen == TRUE) ){
      PortRegisterB = (PortRegisterB & BIT_13CLR);    // !!!
      PortRegisterB = (PortRegisterB | BIT_2_SET);   
      *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
      ThermalOLFlag++;
      SetCurrentAmp(AMPOFFVAL);       // Initial amplitude           
   }
}


void EStopReset(void){
/***************************************************************************/
/* This function will send a reset signal to the power supply when the     */
/* system is in Estop                                                      */   
/***************************************************************************/
   PortRegisterB = (PortRegisterB & BIT_13CLR);    // !!!
   PortRegisterB = (PortRegisterB | BIT_2_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
   SetCurrentAmp(AMPOFFVAL);       // Initial amplitude           
}



void MemoryReset(void)
/***************************************************************************/
/* This function will send a reset signal to the power supply to center    */
/* the frequency, in ready or pre-ready state.                             */   
/***************************************************************************/
{
   if ( (WeldState == PREREADYSTATE) || (WeldState == READYSTATE) ){
      PortRegisterB = (PortRegisterB & BIT_13CLR);    // !!!
      PortRegisterB = (PortRegisterB | BIT_2_SET);   
      *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
      MemoryResetFlag++;          
   }
}

/* Function to turn the sonics off during an HornScan Abort */
void HSReset(void)
{
   UINT8 oldport = PortRegisterB;
   PortRegisterB = (PortRegisterB & BIT_13CLR);    // !!!
   PortRegisterB = (PortRegisterB | BIT_2_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
   tm_wkafter(MS_TO_TICKS(20));
   PortRegisterB = oldport;
   *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
}

void PSRun(void){
   if (DryCycleFlag == FALSE && SonicDisabledFlag == FALSE) {
      PortRegisterB = (PortRegisterB & BIT_23CLR);        // !!!
      PortRegisterB = (PortRegisterB | BIT_1_SET);   
      *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
      UpdateLED(ZEROPERCENTLED,ON);
      SonicsOnFlag = TRUE;

      // No Reason to turn Cool_Val_On here.
      // PortRegisterB = (PortRegisterB | BIT_6_SET);   
      // *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
   }
}

void PSTest(void){
   if (DryCycleFlag == FALSE) {
	  /* if micron cal set 100% amp else default 50% normal test */
	  if(VGA_ScreenMicronCalFlag == TRUE)
	  {
		  SetCurrentAmp(VGA_ScreenMicronCalAmp);
	  }
	  else
	  {
		  SetCurrentAmp(CurrentPreset.TestAmp);
	  }
      PortRegisterB = (PortRegisterB & BIT_2_CLR);   
      PortRegisterB = (PortRegisterB | BIT_13SET);   // !!!
      *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
      UpdateLED(ZEROPERCENTLED,ON);
      SonicsOnFlag = TRUE;
      ClearReady();                       /* Remove Welder Ready signal       */
      // PortRegisterB = (PortRegisterB | BIT_6_SET);   
      // *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
#ifdef FCC_TEST
      FCCTestFlag = TRUE;
#endif

   }
}

void PSSeek(void){
   if (DryCycleFlag == FALSE && SonicDisabledFlag == FALSE) {
      SetCurrentAmp((SINT32) 5);
      PortRegisterB = (PortRegisterB & BIT_2_CLR);   
//      PortRegisterB = (PortRegisterB | BIT_13SET);   
      PortRegisterB = (PortRegisterB | EXTERNAL_SEEK_ON_VAL);   
      *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
      UpdateLED(ZEROPERCENTLED,ON);
      SonicsOnFlag = TRUE;
      // PortRegisterB = (PortRegisterB | BIT_6_SET);   
      // *(UINT8 *)CONTROL_OUTPUT_PORT_1 = PortRegisterB;
   }
}

//----------------------PORT A-------------------------------------------

void RejectOff(void){
   PortRegisterA = (PortRegisterA & BIT_3_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void RejectOn(void){
   PortRegisterA = (PortRegisterA | BIT_3_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void SuspectOff(void){
   PortRegisterA = (PortRegisterA & BIT_4_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void SuspectOn(void){
   PortRegisterA = (PortRegisterA | BIT_4_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void PBReleaseOff(void){
/*****************************************************************************/
/*                                                                           */
/*  This output will be active when entering Ready                           */
/*  held mode it is when the HHBeep is called.                               */ 
/*                                                                           */
/*****************************************************************************/
   PortRegisterA = (PortRegisterA & BIT_5_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void PBReleaseOn(void){
/*****************************************************************************/
/*                                                                           */
/*  This output will be active when an the trigger switch is made. In hand   */
/*  held mode it is when the HHBeep is called.                               */ 
/*                                                                           */
/*****************************************************************************/
   PortRegisterA = (PortRegisterA | BIT_5_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void ActClrOn(void){
/*****************************************************************************/
/*                                                                           */
/*  This output will not be allowed to be active when an upper limit switch  */
/*  alarm (EQ2) exists.  This is because if this alarm occurs, it is most    */
/*  likely at power up and the carriage is not at home.  Therefore, the      */
/*  position of the carriage is unknown and any values read by the encoder   */
/*  are incorrect.  Furthermore, if the alarm does occur, call ActClrOff     */
/*  to ensure the output isn't left active                                   */
/*                                                                           */
/*  2.68    06-23-03  BEKymer  Condition ActClrOn with lack of EQ2           */
/*                                                                           */
/*****************************************************************************/

   if ((WeldingResults.EquipmentFailureAlarms & EQ2) == 0) {
      PortRegisterA = (PortRegisterA | BIT_0_SET);   
      *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
   }
   else ActClrOff();
}

void ActClrOff(void){
   PortRegisterA = (PortRegisterA & BIT_0_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void TrigSwActv(void){
   PortRegisterA = (PortRegisterA | BIT_1_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void TrigSwInactv(void){
   PortRegisterA = (PortRegisterA & BIT_1_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void TrsEnabled(void){
   PortRegisterA = (PortRegisterA | BIT_7_SET);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}

void TrsDisabled(void){
   PortRegisterA = (PortRegisterA & BIT_7_CLR);   
   *(UINT8 *)CONTROL_OUTPUT_PORT_0 = PortRegisterA;
}



// -------------------PORT C---------------------------------------

//void UserCfgOutputOn (UINT16 OutputConfigured)
void UserCfgOutputOff(UINT16 OutputConfigured)  /* Make active low for now */
/***************************************************************************/
/* This function will make the output enabled if the output is configured  */
/* to any of the port pin.                                                 */
/***************************************************************************/
{
    if(CurrentSetup.J3_36Out == OutputConfigured)
    { /* Make J3_36 High. */
       PortRegisterC = (PortRegisterC | BIT_5_SET);   
       *(UINT8 *) CONTROL_OUTPUT_PORT_2 = PortRegisterC; 
    }
    if (CurrentSetup.J3_8Out == OutputConfigured) 
    { /* Make J3_8 High. */
       PortRegisterC = (PortRegisterC | BIT_6_SET);
       *(UINT8 *) CONTROL_OUTPUT_PORT_2 = PortRegisterC;
    }
    if (CurrentSetup.J3_22Out == OutputConfigured) 
    { /* Make J3_22 High. */
       PortRegisterC = (PortRegisterC | BIT_4_SET);   
       *(UINT8 *) CONTROL_OUTPUT_PORT_2 = PortRegisterC;   
    }
     
} 

//void UserCfgOutputOff (UINT16 OutputConfigured)
void UserCfgOutputOn (UINT16 OutputConfigured)  /* Make active low for now */
/***************************************************************************/
/* This function will make the output disabled if the output is configured */
/* to any of the port pin.                                                 */
/***************************************************************************/
{
    if(CurrentSetup.J3_36Out == OutputConfigured)
    { /* Make J3_36 Low. */
       PortRegisterC = (PortRegisterC & BIT_5_CLR);
       *(UINT8 *) CONTROL_OUTPUT_PORT_2 = PortRegisterC;
    }
    if (CurrentSetup.J3_8Out == OutputConfigured) 
    { /* Make J3_8 Low. */
       PortRegisterC = (PortRegisterC & BIT_6_CLR);   
       *(UINT8 *) CONTROL_OUTPUT_PORT_2 = PortRegisterC;
    }
    if (CurrentSetup.J3_22Out == OutputConfigured) 
    { /* Make J3_22 Low. */
       PortRegisterC = (PortRegisterC & BIT_4_CLR);
       *(UINT8 *) CONTROL_OUTPUT_PORT_2 = PortRegisterC;
    }
}

void RefreshOutputStatus(UINT16 RefreshPin )
/***************************************************************************/
/* This function refresh the output status to disable when the output is   */
/* reselected to the port pin.                                             */
/***************************************************************************/
{
   switch (RefreshPin) {
      case J3PIN36:
      /* Disable J3_36 if output is changed. */
         PortRegisterC = (PortRegisterC | BIT_5_SET);
         break;
         
      case J3PIN8:  
      /* Disable J3_8 if output is changed. */    
         PortRegisterC = (PortRegisterC | BIT_6_SET);
         break;
         
      case J3PIN22:
      /* Disable J3_22 if output is changed. */
         PortRegisterC = (PortRegisterC | BIT_4_SET);
         break;
   }   
   *(UINT8 *) CONTROL_OUTPUT_PORT_2 = PortRegisterC;   
}

void ConfirmPresetOn(void)
/***************************************************************************/
/* This function will make the 'ConfirmPreset'output enabled,if the preset */
/* used to run the cycle is diffrent from preset used to run previous cycle*/
/***************************************************************************/
{
   if(ConfirmPresetFlag == TRUE)
      UserCfgOutputOn(OUTPUT_CFMPRESET);
   ConfirmPresetFlag = FALSE;
}

void ConfirmPresetOff(void)
/***************************************************************************/
/* This function will make the 'ConfirmPreset'output disabled.             */
/***************************************************************************/
{
   UserCfgOutputOff(OUTPUT_CFMPRESET);
}

void SVOutOn(void)
/***************************************************************************/
/* This function will make the 'SVInterlock'output enabled.                */
/***************************************************************************/
{
   if(SVInterlockActive) /* If both SVInterlock input and output are selected. */
      UserCfgOutputOn(OUTPUT_SV_INTERLOCK);
}

/* Include for Unit test */
#ifdef DIGOUT_UNIT_TEST
#include "..\ut\digout.ut"
#endif
/* End of include for unit test */





