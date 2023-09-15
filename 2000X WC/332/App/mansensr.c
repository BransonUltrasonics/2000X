/* $Header:   D:/SWLab/VMdb/2000Series/App/MANSENSR.C_V   2.120   04 Sep 2008 20:16:24   ygupta  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 

/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

 Name: Mansensr.c

 -------------------------------- REVISIONS ------------------------------------

 Rev # Date     Author  Description
 ===== ======== ======= ===========                              
  0    4/18/96  LAM     Initial   
  1    4/19/96  LAM     Chged veltable    
  2    5/05/96  LAM     Added writetovf   
  3    5/06/96  LAM     Added AVEpower    
  4    06-10-96 BEKymer Added code to test Force & Velocity values
                        In ManageSensors use VelocityIndex for velocity test
  5    6/27/96  LAM     fixed AVEpower & freqoffset    
  6    7/10/96  LAM     added sonics active flag      
  7    7/28/96  LAM     added interpolated force table added pvpcalibcontrol
  8    8/05/96  LAM     fixed freqoffset    
  9    8/12/96  BEKymer fixed avepower      
 10    8/16/96  LAM     moved writevf    
 11    9/28/96  LAM     cleanup amp & freq tables
 12    10/11/96 LAM     fixed 100% amp           
 13    10/14/96 LAM     added rampdownspeed      
 14    11/18/96 LAM     fixed PVP stepping       
 15    12/07/96 LAM     fixed force table offset 
 16    12/12/96 LAM     added springrate offset 
 17    12/27/96 PhilJ   added check to ManageSensors. 
 18.00 12-28-96 LAM     fixed ext amp & freq   
 19    01-31-97 PaulG   Updated CheckPrinter every 50ms by reading Port A.
 20    02-15-97 LAM     set frequency offset = 0 when in test 
 21    02-28-97 LAM     fixed digpot
 22    03-02-97 LAM     set freqoffset = 0 if pretrig else =0 before pb and after weld
 23    03-28-97 LAM     enable spe in writepvp
 23.01 04-01-97 LAM     reversed freq offset table
 24.00 04-28-97 LAM     read power every 1ms
 24.10 04-28-97 PhilJ   Chngd AmpControlInternal & FreqControlInternal from
                        UINT8 to UINT16.
 24.20 04-29-97 LAM     testmode doesn't use ext amp or freq
 2.61  06-23-97 LAM     added checkforencoder at powerup     
 2.62  08-11-97 LAM     added monitor inputs                 
 2.63  08-13-97 LAM     added get inputs
 2.64  08-17-97 LAM     eliminate getpower,avepower
 2.65  08-29-97 LAM     chged led update to 48ms      
 2.66  09-04-97 LAM     fixed enableddigpot test
 2.67  09-08-97 LAM     unit test cleanup        
 2.68  09-11-97 LAM     moved digital pot to spidd, fixed ext freq control
 2.69  10-14-97 LAM     fixed testamp when ext   
 2.70  10-27-97 LAM     added 24ms bargraph define
 2.71  01-05-98 LAM     start bargraph conv quicker, moved printer chk,
                        chged ampvalue of 100% to equal 4095, if QSPI
                        conversion not complete, do not update bargraph.
 2.71  01-05-98 LAM     start bargraph conv quicker, moved printer chk,
 2.72  01-28-98 LAM     reorder bargraph case
 2.73  01-29-98 PaulG   Check if CheckPrinter was ever Powered off, if so
                        set my InitOnceOnPowerup to TRUE.                                                                                                                                                                                                              
 2.74  01-29-98 LAM     donot use ext amp for seek amp
 2.75  02-03-98 LAM     initialize spielement = 0      
 2.73  01-29-98 PaulG   Check if CheckPrinter is out of paper.
 2.76  03-06-98 PaulG                  
 2.77  03-20-98 LAM     chged ampcontrol to weldingresults
 2.78  04-17-98 LAM     do not need to check for encoder here
 2.79  05-08-98 LAM     deleted unused calibration variables    
 2.80  05-14-98 LAM     chged calibration tables to NVR struct  
 2.81  06-04-98 LAM     added test code for aef                 
 2.82  06-04-98 BEkymer Use WeldingResults.Power SupplyControlFlags to decide
                        if freq is int or ext.
 2.83  07-30-98 BJB     Deleted act_nvr definition, uses actnvram.h
                        Terminated comments to satisfy compiler.
 2.84  09-17-98 LAM     made freq offset table linear at top, fixed 40kHz          
 2.85  12-03-98 LAM     added 15/30 kHz changes                                    
 2.86  12-30-98 LAM     added test code for aef downspeed                          
 2.87  03-15-99 BEKymer Add code for special f0 test
 2.88  05-14-99 JZ      changed PowerSupplyControlFlags to PSActControlFlags
 2.89  05-27-99 LAM     use velocity table based on 60 or 80 PSI.
 
 2.88.1.1 06-23-99 JZ   added SetPV function, eliminated SetForce, SetVelocity
 2.88.1.2 07-14-99 JZ   changed GetinterpolatedSINT32 to UINT16 and assoc. code
 2.88.1.3 07-29-99 JRJ  changed GetinterpolatedUINT32 to SINT16.
 2.92  08-03-99 LAM     deleted unused functions
 2.93  08-06-99 LAM     added forcetabledelta which compensates for pressure 
                        changes
 2.94  08-06-99 JZ      added InitializePV()  
 2.95  08-11-99 LAM     need to wait for the bargraph queue during power up 
 2.96  08-11-99 JZ      changed  SetPV to incl. Start Ramp   
 2.97  08-11-99 LAM     added offset to GetInterpolatedSINT32 parameters 
 2.98  08-13-99 LAM     fixed initializePV    
 2.99  08-23-99 LAM     need to wait for queue to complete before starting another one                                     
 3.00  08-24-99 JZ      added DistanceOffset correction to SetPV function
 3.01  08-25-99 JZ      chngd adjustment to PV from 1 to Error
 2.102 09-03-99 LAM     added velocitydeltafactor
 2.103 09-20-99 LAM     added home weight offset
 2.104 10-08-99 BEKymer Added step limits which are cylinder diameter dependent
 2.105 10-12-99 BEKymer Made FASTEST step limit max.
 2.106 10-25-99 JZ      Modified SetPV(), added temp1 local variable
 2.107 10-26-99 JZ      replaced PV_IDLE_VALUE with CurrentSetup.IdleSpeed
 2.108 10-27-99 JZ      typecasted IdleSpeed in GetInterpolatedSINT32() call
 2.109 11-02-99 JZ      described InitializePV() 
 2.110 11-04-99 JLH     Added debounce counters for printer out of paper and printer
                          power off.  Status of either must persist for 1/2 second to
                          set the InitPrinterOnceOnPowerup variable to TRUE. 
 2.111 11-05-99 LAM     removed printer test, made sure calibration point does not
                        decrease force on the part.   
 2.112 12-06-99 LAM     moved calibration check to snsrcalb.c 
 2.113 02-08-00 LAM     added case for setting pv d/a to zero
 2.114 04-18-00 JLH     Replaced HornWeightOffset with CurrentSetup.HornWeightOffset.
 2.115 07-07-00 BEKymer/DJL fixed SETUPS
 2.116 10-03-00 LAM     moved DupsBid flag to allow reading of inputs Issue(3597)
 2.117 05-12-04 VSharma Added AmpDecay output On/Off in ManageSensors().
 2.118 07-27-04 JOY     Added 60KHZ Freq Offset in SetCurrentFreqOffset().
 2.119 01-31-07 NHAhmed Changes related to Changed Structure variables of CHOICE and TOGGLE.
 2.120 09-04-08 YGupta  CleanUp for LangTest Project.
----------------------------------------------------------------------------*/
                                                                                                                                                                                                                                                            
  
/*----------------------------- DESCRIPTION --------------------------------*/

/* These functions interface to the DACs and ADCs.                          */


/*---------------------------- LOCAL_EQUATES -------------------------------*/

#define CENTER_OFFSET  500 
#define CENTER_FREQ    2048 
#define BARGRATE48MS 12
#define DIVIDEBY2 1
#define DIVIDEBY8 3
#define DIVIDEBY16 4
#define DIVIDEBY32 5
#define FLOAT_TO_INT 10
#define BARGRATE24MS 6
#define MAX_FORCE 1000
#define MAX_VELOCITY_SETTING 1024  /* max downspeed value that can be set from the menus */
#define INIT_PV 20000 /* go to about 1/3 current at power up */

//#define INCLUDE_UNIT_TEST 1



/*------------------------------ INCLUDES ----------------------------------*/


#include "mansensr.h"
#include "332.h"
#include "beep.h"
#include "qsm.h"
#include "sc.h"
#include "preset.h"
#include "spidd.h"
#include "state.h"
#include "statedrv.h"
#include "inports.h"
#include "weld.h"
#include "weld_obj.h"
#include "interpol.h"
#include "menu4.h"
#include "menu7a.h"
#include "menu.h"
#include "actnvram.h"
#include "snsrcalb.h"
#include "outports.h"
#include "digout.h"


/*------------------------------ GLOBAL DATA -------------------------------*/
/*                       (scope is global to ALL files)                     */

INBITS         Inp;
UINT16         VelocityIndex;
UINT16         BarGCount = 1;
UINT16         FreqValue;
UINT16         ForceRamp = 1; 
BOOLEAN        RTFlag = FALSE;
UINT16         RTStep = 0;
UINT16         AmpTable[2] = {0,10442}; 
UINT16         FreqTable[5] = {0,1044,2088,3133,4176};
UINT16         LastForceValue;
SINT16         NumberOfForceSteps = 0;
UINT32         ForceStepSize = 0;
UINT16         CurrentAmpOut;
SINT32         DistanceOffset;

/*----- New code BEK 07-18-06 -----*/


RAMP  RampPV;



/*----------------------------- PRIVATE GLOBAL DATA ------------------------*/
/*                       (scope is global to THIS file)                     */

static UINT16  SpiElement = 0;

/*--------------------------- LOCAL FUNCTION PROTOTYPES --------------------*/


#if INCLUDE_UNIT_TEST
   void TestBarGraph(void);
#endif                             

void ProcessEstop(void);


/*
 ------------------------------- EXTERNAL DATA ------------------------------------
*/

extern UINT32  CurrentPowerIn;         /* Value being read by 7890          */
extern SETUPS_Ver800  RunningPreset,CurrentPreset;
extern CONFIGSETUP CurrentSetup;
extern UINT16  RawPVPValue;
extern enum    WELD_SEQUENCE_TYPE CurrentSequence;
extern SINT8   CheckPrinter;
extern BOOLEAN SonicsOnFlag;
extern enum  WELDSTATES WeldState;
extern UINT8   NovramEnable;
extern SINT16  LCCountsLb;
extern UINT16  CenterPotFlag;
extern UINT16  InitPrinterOnceOnPowerup;
extern WELD_DATA WeldingResults;
extern UINT16 RapidTraversedReached;
extern SINT16 ForceTableDelta,VelocityTableDelta;
extern UINT16  DupsBid;
extern BUCMENU_800 BUCMenuRAM;
/*-------------------------------- CODE ------------------------------------*/



/*--------------debug code-----------*/
UINT16 PVPIndex = 0;
UINT16 TempPVP[128];
SINT8   CheckPrinter;
SINT8   *ReadPrta; 
#define PVP_MASK  0x7f
/*--------------end debug code-------*/

void ManageSensors(void)
/****************************************************************************/ 
/*                                                                          */    
/* The function is called from the 1ms interrupt. It povides the interface  */
/* between the logical interfaces and the physical interfaces including     */
/* A/Ds, D/As, Power Supply Novram, Actuator Novram, digital pot and        */
/* Bargraph.  These are serial devices that are configured on the QSPI      */
/*                                                                          */    
/* Inputs: DupsBid - Set when the DUPS is using the QSPI                    */    
/*                                                                          */    
/****************************************************************************/ 
{
   UINT16 Error, Error1, Adjustment;

   if(NovramEnable == FALSE)
   {
      switch(SpiElement++){
         case(0):
            if (!DupsBid){
               while(QsmMap->Spsr.Spif == 0);  /* make sure last conversion done */
               ReadACTADC();
               QsmMap->Spcr1.Spe = 1;            /* Enable Qspi */
            }
            MonitorInputPorts();
            ProcessEstop();
            break;

         case(1):
            GetInputData(&Inp); /*----------  Get input data first  ----------*/
            if((WeldingResults.PSActControlFlags & BIT2) == FALSE){ /* external amp */
               if(CurrentSequence == TESTMODE)
                  FreqValue = CENTER_FREQ; /* set frequency offset to */
               else
                  FreqValue = GetInterpolatedUINT16(FreqTable,(CENTER_OFFSET - ExtFreqOffset));
            }
            if(((WeldingResults.PSActControlFlags & BIT0) == FALSE) && (WeldState != SEEKSTATE)){ /* external amp */
               if(CurrentSequence == TESTMODE)
                  CurrentAmpOut = GetInterpolatedUINT16(AmpTable,CurrentPreset.TestAmp);
               else
                  CurrentAmpOut = GetInterpolatedUINT16(AmpTable,ExtAmp);
            }
            if (!DupsBid){
               while(QsmMap->Spsr.Spif == 0);  /* make sure last conversion done */
               WritePSDAC(FreqValue,CurrentAmpOut);
               QsmMap->Spcr1.Spe = 1;            /* Enable Qspi */
            }
            break;

         case(2):
            MonitorInputPorts();
            CheckPrinter = *(ReadPrta);
            if((CheckPrinter == POWEROFF) ||
              (CheckPrinter == OUTOFPAPER)){
               InitPrinterOnceOnPowerup = TRUE;
            }
         
/*---  Here is the code for dealing with the Proportional Valve   ---*/

            if (RampPV.TargetValue < RampPV.CurrentValue) {
               Error = RampPV.CurrentValue - RampPV.TargetValue;
               Error1 = (Error >> RampPV.ShiftValue);
               if (Error1 < 1) Adjustment = Error;
               else if (Error1 > RampPV.CurrentStepLimit) Adjustment = RampPV.CurrentStepLimit;
               else Adjustment = Error1;
               RampPV.CurrentValue -= Adjustment;

            }
            else {
               Error = RampPV.TargetValue - RampPV.CurrentValue;
               Error1 = (Error >> RampPV.ShiftValue);
               if (Error1 < 1) Adjustment = Error;
               else if (Error1 > RampPV.CurrentStepLimit) Adjustment = RampPV.CurrentStepLimit;
               else Adjustment = Error1;
               RampPV.CurrentValue += Adjustment;
            }
            TempPVP[PVPIndex++ & PVP_MASK] = RampPV.CurrentValue;         // debug code

/*---  End of Proportional Valve code  ---*/
            if (!DupsBid){
               while(QsmMap->Spsr.Spif == 0);  /* make sure last conversion done */
               WritePVP(RampPV.CurrentValue);
            }
            break;
         case(3):
            GetInputData(&Inp);
            if (!DupsBid){
               if(BarGCount++ >= BARGRATE48MS)
                  {             
                  while(QsmMap->Spsr.Spif == 0);  /* make sure last conversion done */
                  WriteBarGraph();
                  QsmMap->Spcr1.Spe = 1;            /* Enable Qspi */
                  CheckBeeper();
                  BarGCount = 1;
                  }
            }
            if ((CurrentAmpIn/10) < BUCMenuRAM.AmpDecayPercent )
               UserCfgOutputOn(OUTPUT_AMPDECAY);/* Enable Amplitude Decay output.*/
            else
               UserCfgOutputOff(OUTPUT_AMPDECAY);/* Disable Amplitude Decay output.*/      
            SpiElement = 0;
            break;
     
         default:
            SpiElement = 0;
            break;
      }
   }
}

void   SetCurrentAmp(SINT32 Amplitude)   /* weldhold, profile  */                            
{
   if (Amplitude < (MAX_AMP_PTS - 1))
      CurrentAmpOut = GetInterpolatedUINT16(AmpTable,(UINT16) Amplitude);
   else
      CurrentAmpOut = 4095;  /* send out max count when amplitude = 100% */
}


void SetCurrentFreqOffset(SINT32 FreqOffset)  
/****************************************************************************/ 
/*                                                                          */
/* This function is called when entering the weld state and exiting the     */
/* weld state. FrequencyCenter is dependent on the Power Supply Frequency.  */
/* This offsets the value to a positive number.                             */
/*                                                                          */
/* Input: FreqOffset - user entered value, 0 = center frequency             */
/*        CurrentSetup.PSFreq - Power Supply frequency                      */
/*        FreqTable - table that converts user value to D/A value           */
/*                                                                          */
/* Output: FreqValue - value outputted to the D/A.                          */
/*                                                                          */
/****************************************************************************/ 
{
   if (CurrentSetup.PSFreq == FREQ60KHZ)
      FreqOffset = (FreqOffset * FLOAT_TO_INT) >> DIVIDEBY32; 
   else if (CurrentSetup.PSFreq == FREQ40KHZ)
      FreqOffset = FreqOffset >> DIVIDEBY2;
   else if (CurrentSetup.PSFreq == FREQ30KHZ)
      FreqOffset = (FreqOffset * FLOAT_TO_INT) >> DIVIDEBY16;
   else if (CurrentSetup.PSFreq == FREQ15KHZ)
      FreqOffset = (FreqOffset * FLOAT_TO_INT) >> DIVIDEBY8;
   if(FreqOffset == 0)
      FreqValue = CENTER_FREQ;
   else
      FreqValue = GetInterpolatedUINT16(FreqTable,(FreqOffset + CENTER_OFFSET));
}


void SetPV(UINT16 InitVel, enum STAGE Stage)
/****************************************************************************/ 
/*                                                                          */
/* This function will handle changing the proportional valve from one value */
/* to the next. Each change will be ramped. The slope of the ramp will be   */
/* determined by what stage the weld cycle is in. The actual ramp is handled*/
/* by ManageSensors() in this file.                                         */
/*                                                                          */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 temp;
   SINT16 temp1;
   
   switch (Stage) {
      case RT_TO_DWNSPD:
         RampPV.TargetValue = GetInterpolatedSINT32(CurrentSetup.VelocityTable, InitVel, VelocityTableDelta);
         switch (RunningPreset.RTRamp) {
            case RATE_SLOWEST:
                 RampPV.ShiftValue = SHIFT_SLOWEST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_SLOW:
                 RampPV.ShiftValue = SHIFT_SLOW;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_NORMAL:
                 RampPV.ShiftValue = SHIFT_NORMAL;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FAST:
                 RampPV.ShiftValue = SHIFT_FAST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FASTEST:
                 RampPV.ShiftValue = SHIFT_FASTEST;
                 RampPV.CurrentStepLimit = NO_LIMIT;
                 break;
         }
         break;
  
      case TRG_TO_FORCE_A:
         temp1 = (InitVel/10)+DistanceOffset + CurrentSetup.HornWeightOffset;
         if (temp1 < 0)
            temp = 0;
         else
            temp = (UINT16)temp1;
         RampPV.TargetValue = GetInterpolatedSINT32(NVR.Force, temp, ForceTableDelta);
         switch (RunningPreset.WeldFR) {
            case RATE_SLOWEST:
                 RampPV.ShiftValue = SHIFT_SLOWEST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_SLOW:
                 RampPV.ShiftValue = SHIFT_SLOW;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_NORMAL:
                 RampPV.ShiftValue = SHIFT_NORMAL;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FAST:
                 RampPV.ShiftValue = SHIFT_FAST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FASTEST:
                 RampPV.ShiftValue = SHIFT_FASTEST;
                 RampPV.CurrentStepLimit = NO_LIMIT;
                 break;
         }
         break;

      case FORCE_A_TO_FORCE_B:
         temp1 = (InitVel/10)+DistanceOffset + CurrentSetup.HornWeightOffset;
          if (temp1 < 0)
            temp = 0;
         else
            temp = (UINT16)temp1;
         RampPV.TargetValue = GetInterpolatedSINT32(NVR.Force, temp, ForceTableDelta);
         switch (RunningPreset.StepFR) {
            case RATE_SLOWEST:
                 RampPV.ShiftValue = SHIFT_SLOWEST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_SLOW:
                 RampPV.ShiftValue = SHIFT_SLOW;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_NORMAL:
                 RampPV.ShiftValue = SHIFT_NORMAL;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FAST:
                 RampPV.ShiftValue = SHIFT_FAST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FASTEST:
                 RampPV.ShiftValue = SHIFT_FASTEST;
                 RampPV.CurrentStepLimit = NO_LIMIT;
                 break;
         }
         break;

      case FORCE_B_TO_HOLD:
         temp1 = (InitVel/10)+DistanceOffset + CurrentSetup.HornWeightOffset;
          if (temp1 < 0)
            temp = 0;
         else
            temp = (UINT16)temp1;
         RampPV.TargetValue = GetInterpolatedSINT32(NVR.Force, temp, ForceTableDelta);
         switch (RunningPreset.HoldFR) {
            case RATE_SLOWEST:
                 RampPV.ShiftValue = SHIFT_SLOWEST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_SLOW:
                 RampPV.ShiftValue = SHIFT_SLOW;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_NORMAL:
                 RampPV.ShiftValue = SHIFT_NORMAL;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FAST:
                 RampPV.ShiftValue = SHIFT_FAST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FASTEST:
                 RampPV.ShiftValue = SHIFT_FASTEST;
                 RampPV.CurrentStepLimit = NO_LIMIT;
                 break;
         }
         break;

      case HOLD_TO_HOME:
         RampPV.TargetValue = GetInterpolatedSINT32(CurrentSetup.VelocityTable, (UINT16)CurrentSetup.IdleSpeed,VelocityTableDelta);
         switch (RunningPreset.ReturnRamp) {
            case RATE_SLOWEST:
                 RampPV.ShiftValue = SHIFT_SLOWEST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_SLOW:
                 RampPV.ShiftValue = SHIFT_SLOW;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_NORMAL:
                 RampPV.ShiftValue = SHIFT_NORMAL;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FAST:
                 RampPV.ShiftValue = SHIFT_FAST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FASTEST:
                 RampPV.ShiftValue = SHIFT_FASTEST;
                 RampPV.CurrentStepLimit = NO_LIMIT;
                 break;
         }
         break;

      case HOME_TO_RT:
         RampPV.TargetValue = GetInterpolatedSINT32(CurrentSetup.VelocityTable, InitVel,VelocityTableDelta);
         switch (RunningPreset.StartRamp) {
            case RATE_SLOWEST:
                 RampPV.ShiftValue = SHIFT_SLOWEST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_SLOW:
                 RampPV.ShiftValue = SHIFT_SLOW;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_NORMAL:
                 RampPV.ShiftValue = SHIFT_NORMAL;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FAST:
                 RampPV.ShiftValue = SHIFT_FAST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FASTEST:
                 RampPV.ShiftValue = SHIFT_FASTEST;
                 RampPV.CurrentStepLimit = NO_LIMIT;
                 break;
         }
         break;

      case HOME_TO_DWNSPD:
         RampPV.TargetValue = GetInterpolatedSINT32(CurrentSetup.VelocityTable, InitVel,VelocityTableDelta);
         switch (RunningPreset.StartRamp) {                  
            case RATE_SLOWEST:
                 RampPV.ShiftValue = SHIFT_SLOWEST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_SLOW:
                 RampPV.ShiftValue = SHIFT_SLOW;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_NORMAL:
                 RampPV.ShiftValue = SHIFT_NORMAL;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FAST:
                 RampPV.ShiftValue = SHIFT_FAST;
                 RampPV.CurrentStepLimit = RampPV.CylinderStepLimit;
                 break;
            case RATE_FASTEST:
                 RampPV.ShiftValue = SHIFT_FASTEST;
                 RampPV.CurrentStepLimit = NO_LIMIT;
                 break;
         }
         break;

      case FORCE_CALIBRATION:
         RampPV.TargetValue = InitVel;               
         RampPV.ShiftValue = 0;
         break;
      case ZERO_PSI:
         RampPV.TargetValue = 0;               
         RampPV.ShiftValue = 0;
         break;
         
   }
}



void InitializePV( void )
/****************************************************************************/ 
/*                                                                          */
/*  Will initialize RampPV struct. TargetValue, ShiftValue, CurrentValue,   */
/*  and CylinderStepLimit                                                   */
/****************************************************************************/ 

{
   RampPV.TargetValue = INIT_PV;
   RampPV.ShiftValue     = SHIFT_NORMAL;
   RampPV.CurrentValue = 0;     /* In D/A counts (0-65535)    */
   switch(NVR.CylSize) {                        /* First determine what the  */
      case SIZE1_5:                             /* steplimit should be based */
      case SIZE_40:                             /* on the cylinder diameter  */
         RampPV.CylinderStepLimit = STEPLIMIT_1_5in;
         break;   
      case SIZE2_0:
      case SIZE_50:
         RampPV.CylinderStepLimit = STEPLIMIT_2_0in;
         break;   
      case SIZE2_5:
      case SIZE_63:
         RampPV.CylinderStepLimit = STEPLIMIT_2_5in;
         break;   
      case SIZE3_0:
         RampPV.CylinderStepLimit = STEPLIMIT_3_0in;
         break;   
      case SIZE3_25:
      case SIZE_80:
         RampPV.CylinderStepLimit = STEPLIMIT_3_25in;
         break;   
      default:              // In case of an Error
         RampPV.CylinderStepLimit = STEPLIMIT_3_0in;
         break;   
    }
}
