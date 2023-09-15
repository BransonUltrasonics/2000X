/* $Header:   D:/SWLab/VMdb/2000Series/INC/WELD_OBJ.H_V   2.64   May 23 2007 16:54:12   nhahmed  $ */
#ifndef WELD_OBJ_H
#define WELD_OBJ_H
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
 ---------------------------- MODULE DESCRIPTION -------------------------------
                                           
   Module name: WELD_OBJ

   Filename: weld_obj.h 

 -------------------------------- REVISIONS ------------------------------------

    Revision#  Date      Author       Description
    =========  ========  ===========  ===========
       1       07/23/96  Lam          deleted unused functions    
       1.01    08/12/96  Lam          added alarms to weld summary
       1.02    09-12-96  BEKymer      Added stuff to WELD_DATA
       1.03    09-26-96  BEKymer      Compress WELD_DATA by making
                                      some entries less then SINT32
       1.04    10-02-96  PhilJ        Changed all alarms to UINT32. Deleted
                                      array type, added third GeneralAlarm.
       1.05    10-14-96  PaulG        Change MAX_WELD_SAMPLE from 300 to 400.       
       2.0     10-15-96  BEKymer      Change VeriftPreset return from UINT16
                                      to UINT32
       2.01    11-11-96  PaulG        WELD_OBJECT struct modified, members of
                                      1MS_DATA inserted into WELD_OBJECT struct.
       2.02    02-21-97  PaulG        WELD_OBJECT struct modified, member MakeCopy added.
       3.00    03-13-97  LAM          WELD_OBJECT struct modified
       3.10    03-20-97  PhilJ        WELD_DATA struct modified Warnings now UINT32.
       3.20    03-31-97  PhilJ        Added Weldmode to WELD_DATA structure.
       4.00    05-03-97  LAM          made weldobject array size of packetmax
       5.00    05-30-97  LAM          decreased packetmax to 50
       6.2.25  06-20-97  LAM          added new alarm structure
       6.2.26  06-25-97  BEKymer      Added SetupErrorAlarms10
       6.2.27  08-12-97  PaulG        Changed PACKET_MAX to MAX_WELD_SAMPLES.
       2.28    08-23-97  LAM          deleted triggerattime                  
       2.29    08-23-97  LAM          deleted sonicsendattime
       2.31    09-19-97  LAM          deleted updatepreset, getpresetdatapointer
       2.32    11-21-97  LAM          deleted sonicsendattime
       2.33    12-04-97  BEKymer      Reorder WELD_DATA structure to ease debugging
       2.34    02-04-98  BEKymer      Move final 'Times' into WELD_OBJECT
                                      from WELD_DATA
       2.35    02-05-98  BEKymer      Make PeakPower a UINT16 instead of UINT8
       2.36    02-18-98  BEKymer      Make ActualAmp..Start/End SINT32 
       2.37    03-18-98  BJB          Terminated comments to satisfy compiler
       2.38    03-19-98  BEKymer      Rename Spare in WELD_DATA to AmpControl
       2.39    03-20-98  BEKymer      Rename AmpControl to AmpControlFlags
       2.40    03-24-98  PaulG        Added TotalPts to weldobject structure.
       2.41    03-26-98  PaulG        Added MANULASCALEFLAG for AutoScaleFlag = OFF.
       2.42    03-27-98  PaulG        Added IncrementPts, CopyPts, NewPreCt to WELD_OBJECT.
       2.43    03-31-98  PaulG        Added BufferWrapFlag to WELD_OBJECT.
       2.44    04-06-98  PaulG        Added NewInc to WELD_OBJECT.
       2.45    04-07-98  PaulG        Changed BufferWrapFlag from UINT16 to BOOLEAN.
       2.46    05-11-98  LAM          temporarily added triggerforce to test part contact
       2.47    05-26-98  PaulG        Changes Dist from UINT32 to SINT32.

       2.46 ?  06-03-98  BEKymer      Change AmpControlFlags to PowerSupply
                                      ControlFlags and add frequency control
       2.47    06-22-98  BEKymer      Rename ActualForceMax to WeldForceMax
                                      Add HoldForceMax for future use
                                      Add WeldPressure
       2.48    08-06-98  PaulG        Added PointsUpTillHold to store points at holdtime.
                                      Also added EndOfSonicCt to store points at weldtime.
       2.49    08-07-98  PaulG        Added DontPrintGraph to WELD_OBJECT struct.
       2.50    08-10-98  BEKymer      Add ActualWeldCollapse to WELD_DATA structure
                                      Rename ActualCollapse to ActualTotalCollapse
       2.51    04-20-99  OFI          Changed for DIAB
       2.52    05-14-99  JZ           Changed WeldForceMax to SetForceB, ActualForceStart to
                                      SetForceA, ActualForceEnd to WeldForceEnd
                                      PowerSupplyControlFlags to PSActControlFlags and added BIT4
       2.53    10-13-99  OFI          Swapped WeldForceEnd and SetForceB to have weld data correctly appear
                                      on one line data (WeldForce)

       2.54    04-14-00  SCM          Added CycleTimeresult and WeldAbsDistance to the WELD_DATA
                                      structure.
       2.55    06-27-00  SCM          Changed the names of the variables ActualWeldAbs
                                      and ActualTotalAbs in the structure WELD_DATA.
       2.56    09-12-00  JLH          Added WELD_DATA structure from version 7.02 as WELD_DATA7_02.
       2.57    02-19-04  VSharma      Added PresetNum and PresetName in WELD_DATA & WELD_DATA7_02 struct.
       2.58    06-14-04  VSharma      Changed size of PresetName in WELD_DATA to append '*'.
       2.59    01-28-05  BEKymer      Restore WELD_DATA7_02 structure to
                                       original format so original Compuweld will
                                       work correctly.
                                       
       2.60    09-10-05  Aare         Merged 10f and 10h. 
       2.61    03-27-07  NHAhmed      Changes made in WELD_DATA7_02 structure for VQSData limit
       2.62    03-29-07  YGupta       Modified WELD_DATA7_02 structure to move TriggerForce before TotalCycleTime.
       2.63    03-30-07  YGupta       Added __packed__ for WELD_DATA7_02.
       2.64    05-23-07  NHAhmed      Added new member (ScrubStartAtTime) in WELD_OBJ
 ------------------------------- DESCRIPTION -----------------------------------


*/
/* ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "psos.h"            /* fundamental data object types       */
#include "preset.h"
#include "state.h"
#include "time.h"


#define MAX_WELD_SAMPLES     400
#define PACKET_MAX           50

#define HOLDALARMMASK        (BIT0)
#define AMPSTEPALARMMASK     (BIT1)
#define FORCESTEPALARMMASK   (BIT2)
#define SEEKALARMMASK        (BIT3)
#define MANUALSCALEFLAG      (BIT4)
#define ALLALARMMASK         (HOLDALARMMASK | AMPSTEPALARMMASK | FORCESTEPALARMMASK | SEEKALARMMASK)

typedef enum {
    WELD_DATA_0  = 0u,
	WELD_DATA_1,
	WELD_DATA_2,
	WELD_DATA_3,
	WELD_DATA_4,
	WELD_DATA_5,
	WELD_DATA_6,
	WELD_DATA_7,
	WELD_DATA_8,
	WELD_DATA_9,
	WELD_DATA_10,
	WELD_DATA_11,
	WELD_DATA_12,
	WELD_DATA_13,
	WELD_DATA_14,
	WELD_DATA_15,
	WELD_DATA_16,
	WELD_DATA_17,
	WELD_DATA_18,
	WELD_DATA_19,
	WELD_DATA_20,
	WELD_DATA_21,
	WELD_DATA_22,
	WELD_DATA_23,
	WELD_DATA_24,
	WELD_DATA_25,
	WELD_DATA_26,
	WELD_DATA_27,
	WELD_DATA_28,
	WELD_DATA_29,
	WELD_DATA_30,
	WELD_DATA_31,
	WELD_DATA_32,
	WELD_DATA_33,
	WELD_DATA_34,
	WELD_DATA_35,
	WELD_DATA_36,
	WELD_DATA_37,
	WELD_DATA_38,
	WELD_DATA_39,
	WELD_DATA_40,
	WELD_DATA_41,
	WELD_DATA_42,
	WELD_DATA_43,
	WELD_DATA_44,
	WELD_DATA_45,
	WELD_DATA_46,
	WELD_DATA_47,
	WELD_DATA_48,
	WELD_DATA_49
} WELD_DATA_NUMBER_TYPE;


typedef struct weldObject
{
   UINT16  Power[MAX_WELD_SAMPLES];            /* Power (in percent)                              */
   UINT16  Amp[MAX_WELD_SAMPLES];              /* Amplitude (in percent)                          */
   UINT16  Freq[MAX_WELD_SAMPLES];             /* Frequency (Hz) 20K:19450-20450, 40K:38900-40900 */
   UINT16  Force[MAX_WELD_SAMPLES];            /* Force (always lb's)                             */
   SINT32  Dist[MAX_WELD_SAMPLES];             /* Distance (always in's)                          */
   UINT16  count;
   SINT32  HoldEndAtTime;
   SINT32  SeekEndAtTime;
   SINT32  AmpStepAtTime;
   SINT32  ForceStepAtTime;
   SINT32  PeakPowerAtTime;
   SINT32  ScrubStartAtTime;
   UINT16  PrintBottomFlags;
   UINT32  TotalPts;
   DFLOAT  IncrementPts;
   UINT16  CopyPts;
   UINT16  NewPreCt;
   BOOLEAN BufferWrapFlag;    /* 100ms buffer wrapped around         */     
   DFLOAT  NewInc;
   UINT16  PointsUpTillHold;  /* Points collected through hold time  */
   UINT16  EndOfSonicCt;      /* Points collected through hold time  */
   BOOLEAN DontPrintGraph;    /* Can't "Print Now" unless there is a good cycle  */
}  WELD_OBJECT;


typedef struct
{
   SINT32  CycleCount;               /* These are arranged in roughly the  */
   struct  t_time  CycleTime;        /* order that they are printed.  This */
   struct  t_date  CycleDate;        /* allows for easier debugging by     */
   SINT32  ActualWeldTime;           /* using the emulator to print the    */
   SINT32  TotalEnergy;              /* entire structure and find where    */
   SINT32  ActualWeldAbs;            /* you are by looking at the weld     */
   SINT32  ActualTotalAbs;           /* history print out.     BEK 12-04-97*/
   SINT32  ActualWeldCollapse;       
   SINT32  ActualTotalCollapse;
   SINT32  ActualFreqStart;
   SINT32  ActualFreqEnd;
   SINT32  FrequencyChange;
   SINT32  FrequencyMin;
   SINT32  FrequencyMax;
   UINT32  CycleTimeResult;                 /* Added on 04/13/00 SCM */
   SINT32  ActualVelocity;
   SINT32  ActualTriggerDistance;
   UINT32  RejectBitResult;
   UINT32  SuspectBitResult;
   UINT32  NoCycleAlarms;
   UINT32  OverloadAlarms;
   UINT32  EquipmentFailureAlarms;
   UINT32  CycleModifiedAlarms;
   UINT32  CalibrateAlarms;
   UINT32  Warnings;
   SINT32  ActualAmplitudeStart;   /* Amplitude Start in % */
   SINT32  ActualAmplitudeEnd;     /* Amplitude End in % */
   UINT8   Weldmode;
   UINT8   PSActControlFlags;      /* BIT0: 1-Amp internal  0-amp external   */
                                   /* BIT1: 1-Amp stepping on 0-stepping off */
                                   /* BIT2: 1-Freq internal 0-Freq external  */
                                   /* BIT4: 1-Force stepping on 0-off        */
   UINT16  PeakPower;
   UINT16  WeldPressure;
   UINT16  WeldForceEnd;
   UINT16  HoldForceMax;
   UINT16  SetForceA;
   UINT16  SetForceB;
   UINT16  TrigForce;
   UINT16  PresetNum;
   SINT8   PresetName[PRESETLEN+1]; /* One more character added to store '*'. */
   UINT32  TotalCycleTime;

   //SINT32  ActualAmplitudeMicronStart; /* Amplitude Start in Microns */
   //SINT32  ActualAmplitudeMicronEnd;   /* Amplitude End in Microns */
   //UINT16  PeakPowerWatts;             /* Peak Power in Watts */

} WELD_DATA;


typedef struct
{
   SINT32  CycleCount;               /* These are arranged in roughly the  */
   struct  t_time  CycleTime;        /* order that they are printed.  This */
   struct  t_date  CycleDate;        /* allows for easier debugging by     */
   SINT32  ActualWeldTime;           /* using the emulator to print the    */
   SINT32  TotalEnergy;              /* entire structure and find where    */
   SINT32  ActualWeldAbs;            /* you are by looking at the weld     */
   SINT32  ActualTotalAbs;           /* history print out.     BEK 12-04-97*/
   SINT32  ActualWeldCollapse;
   SINT32  ActualTotalCollapse;
   SINT32  ActualFreqStart;
   SINT32  ActualFreqEnd;
   SINT32  FrequencyChange;
   SINT32  FrequencyMin;
   SINT32  FrequencyMax;
   UINT32  CycleTimeResult;                 /* Added on 04/13/00 SCM */
   SINT32  ActualVelocity;
   SINT32  ActualTriggerDistance;
   UINT32  RejectBitResult;
   UINT32  SuspectBitResult;
   UINT32  NoCycleAlarms;
   UINT32  OverloadAlarms;
   UINT32  EquipmentFailureAlarms;
   UINT32  CycleModifiedAlarms;
   UINT32  CalibrateAlarms;
   UINT32  Warnings;
   SINT32  ActualAmplitudeStart; /* Amplitude Start in % */
   SINT32  ActualAmplitudeEnd;   /* Amplitude End in % */
   UINT8   Weldmode;
   UINT8   PSActControlFlags;      /* BIT0: 1-Amp internal  0-amp external   */
                                   /* BIT1: 1-Amp stepping on 0-stepping off */
                                   /* BIT2: 1-Freq internal 0-Freq external  */
                                   /* BIT4: 1-Force stepping on 0-off        */
   UINT16  PeakPower;
   UINT16  WeldPressure;
   UINT16  WeldForceEnd;
   UINT16  HoldForceMax;
   UINT16  SetForceA;
   UINT16  SetForceB;
   UINT16  TrigForce;
   UINT16  PresetNum;
   SINT8   PresetName[PRESETLEN+1]; /* One more character added to store '*'. */
   UINT32  TotalCycleTime;

} WELD_DATA_1135;

typedef __packed__ struct
{
   SINT32  CycleCount;               /* These are arranged in roughly the  */
   struct  t_time  CycleTime;        /* order that they are printed.  This */
   struct  t_date  CycleDate;        /* allows for easier debugging by     */
   SINT32  ActualWeldTime;           /* using the emulator to print the    */
   SINT32  TotalEnergy;              /* entire structure and find where    */
   SINT32  ActualDistance;           /* you are by looking at the weld     */
   SINT32  ActualWeldCollapse;       /* history print out.     BEK 12-04-97*/
   SINT32  ActualTotalCollapse;
   SINT32  ActualFreqStart;
   SINT32  ActualFreqEnd;
   SINT32  FrequencyChange;
   SINT32  FrequencyMin;
   SINT32  FrequencyMax;
   SINT32  ActualVelocity;
   SINT32  ActualTriggerDistance;
   UINT32  RejectBitResult;
   UINT32  SuspectBitResult;
   UINT32  NoCycleAlarms;
   UINT32  OverloadAlarms;
   UINT32  EquipmentFailureAlarms;
   UINT32  CycleModifiedAlarms;
   UINT8   PresetNum;
   UINT8   Language;
   UINT8   Unit;
   UINT8   LimitChangedFlag;
   UINT32  Warnings;
   SINT32  ActualAmplitudeStart;
   SINT32  ActualAmplitudeEnd;
   UINT8   Weldmode;
   UINT8   PSActControlFlags;      /* BIT0: 1-Amp internal  0-amp external   */
                                   /* BIT1: 1-Amp stepping on 0-stepping off */
                                   /* BIT2: 1-Freq internal 0-Freq external  */
                                   /* BIT4: 1-Force stepping on 0-off        */
   UINT16  PeakPower;
   UINT16  WeldPressure;
   UINT16  WeldForceEnd;
   UINT16  HoldForceMax;
   UINT32  TotalCycleTime;
   UINT16  TrigForce;

} WELD_DATA7_02;

typedef struct
{
   UINT32  SetupErrorAlarms1;
   UINT32  SetupErrorAlarms2;
   UINT32  SetupErrorAlarms3;
   UINT32  SetupErrorAlarms4;
   UINT32  SetupErrorAlarms5;
   UINT32  SetupErrorAlarms6;
   UINT32  SetupErrorAlarms7;
   UINT32  SetupErrorAlarms8;
   UINT32  SetupErrorAlarms9;
   UINT32  SetupErrorAlarms10;

} SETUP_DATA_ALARMS;

#endif

void   CheckProcessLimits(void);
UINT32 VerifyPreset(void);
WELD_DATA  * GetWeldDataPointer(WELD_DATA  * weldDataPtr);


