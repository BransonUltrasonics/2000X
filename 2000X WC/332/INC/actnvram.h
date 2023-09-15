/* $Header:   D:/databases/VMdb/2000Series/INC/ACTNVRAM.H_V   1.37.1.1   Nov 29 2017 11:43:14   hasanchez  $ */
#ifndef ACTNVRAM_H
#define ACTNVRAM_H
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

   Module name:  

   Filename:      actnovram.h


 -------------------------------- REVISIONS ------------------------------------

 Rev # Date     Author Description
 ===== ======== ====== ===========
 1.0   11/22/96 PhilJ  Initial Version.
 1.1   12/23/96 PhilJ  Added ACTNOVRAMID and ACTIDADDR
 1.2   04.24.98 JB     Added prototypes   
 1.3   04.24.98 JB     Changed Strk with Stroke
 1.4   04.24.98 JB     Changed MaxForce to GetMaxForce
 1.5   04.30.98 JB     Added a prototype CheckNvrValid
 1.6   05.06.98 JB     Added prototypes
 1.7   05.11.98 JB     Added proto: NvrCopyDeftoNon
 1.8   05.21.98 JB     Added prototypes.
 1.9   06.11.98 LAM    Made calibpass UINT16 instead of BOOLEAN
 1.10  06.25.98 JB     Added Prototypes
 1.11  07.07.98 JB     Added new defines
 1.12  07.30.98 BJB    Added act_nvr definition
                       Modified, added new prototypes
 1.13  08.03.98 BJB    ActRecover() takes parameter, act type
 1.14  08.31.98 LAM    Added update calibration table prototype 
 1.15  09.28.98 LAM    Deleted unused defines   l
 
                  
 1.16  10.05.98 LAM    Added update def date prototype
 1.17  10.13.98 BJB    Modified prototypes for write functions to match new .C
 1.18  10.26.98 LAM    added defines for array sizes
 1.19  10.28.98 BJB    Updated SetSerNum() prototype.
 1.20  05-25-99 JZ     Changed GetMaxForce to SINT32, added #define NVR_AE, NVR_AED
                       NVR_AEF
 1.21  05-28-99 JZ     made ActRecover(void)
 1.21.2.1 06-25-99 JHenry Added GetDefForce function prototype; deleted prototypes
                           for unused functions GetPressure and GetLoadCell.
 1.23  08-25-99 LAM    added UpdateCylinderFactor prototype
 1.24  09-08-99 LAM    added prototypes for calibrated stroke and system pressure. Added
                       stroke and pressure to NVR structure
 1.25  09-09-99 LAM    changed defsyspressure prototype
 1.26  09-15-99 LAM    added prototypes for calibrated homeoffset and springrateslope. 
                       Added homeoffset and springrateslope to NVR structure
 1.27  10-14-99 BEKymerAdded Prototypes for TestWriteToNvram() and TestReadFromNvram()
 1.28  11-04-99 JZ     added defines for max force at given cylinder size, actuator type and
                       system pressure
 1.29  10-31-00 LAM    added prototypes need to correct (Issue 3661). 
 1.30  11-01-00 LAM    deleted repeat prototype
 1.31  11-28-00 BEKymerAdded AED_MAXFORCE_4_0IN
                       Added AEF_MAXFORCE_3_25IN_80PSI & ..60PSI to test with an AEF
 1.32  04-02-02 LAM    added psversion to NVR structure                       
 1.33  04-04-02 LAM    added NO_LOADCELL_OFFSET                       
 1.34  04-29-04 BEKymerExpand comment on MAXSERIALNUM                      
 1.35  04-05-05 LAM    Added forcegauge type to novram structure 
 1.36  09-22-09 YGupta Added NVR_MICRO for MICRO Actuator.
 1.37  06-08-10 PDwivedi Added EncoderType enum in act_nvr for standard MICRO Actuator. 
1.37.1.1  11-23-17 HSAN   Included new features to new encoder.                  
                       
------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/

#define ACTNOVRAMID         0xAA55
#define NEXTADDRESS         0x0001

// Actuator novram memory map addresses

/* 12 bit Commands */
#define ACTRAMENABLE        0x04c0   /* 010011xxxxxx */
#define ACTRAMDISABLE       0x0400   /* 010000xxxxxx */
#define ACTRAMERASEADDR     0x0700   /* 0111AAAAAAAA */
#define ACTRAMERASEALL      0x0480   /* 01001xxxxxxx */
#define ACTRAMWRITEALL      0x0440   /* 010001xxxxxx */

/* 16 bit Commands */
#define ACTREADRAM          0x0600   /* 00000110AAAAAAAA */
#define ACTWRITERAM         0x0500   /* 00000101AAAAAAAA */

#define ACTIDADDR           0x0000

#define ACTSERNUM1          0x0001
#define ACTSERNUM2          0x0002
#define ACTSERNUM3          0x0003
#define ACTSERNUM4          0x0004
#define ACTSERNUM5          0x0005

#define MAXSERIALNUM        10       /* Total displayable characters.  NULL  */
                                     /* is not stored in NOVRAM, but must be */
                                     /* added when copying into CurrentSetup */
                                     /* or BBR.                              */
                                     
#define ACTLIFETIME1        0x0006
#define ACTLIFETIME2        0x0007

#define ACTSTROKELEN1       0x0008
#define ACTSTROKELEN2       0x0009
#define MESSAGE_DELAY1      1
#define TENMILLS_SLEEP      25
#define PREWRITE            0x0500
#define PREREAD             0x0600
#define ENCODER_ADDR          0xA7

#define EWEN                0x4C0    

#define AENVR   1       /* Make sure this is first in list */
#define AONVR   2
#define AEDNVR  3
#define AODNVR  4
#define AEFNVR  5
#define AOFNVR  6       /* Make sure this is last in list */

#define LOAD_CELL    1  /* standard loadcell */
#define SBEAM        2  /* Sbeam loadcell */

#define CALIBPASSED  1
#define CALIBFAILED  2
#define CALIBDEFAULT 3

#define FORCE_TABLE_SIZE 6

#define NVR_AE                1
#define NVR_AED               3
#define NVR_AEF               5
#define NVR_MICRO             7
#define DEF_CAL_LENGTH            20000   /* 2 inch stroke is default */

#define AED_MAXFORCE_1_5IN        1590    /* means 159.0 lbs  */
#define AED_MAXFORCE_2_0IN        2820    /* max force at given cylinder size */
#define AED_MAXFORCE_2_5IN        4420    /* actuator type and pressure       */
#define AED_MAXFORCE_3_0IN        6360
#define AED_MAXFORCE_3_25IN       7250
#define AED_MAXFORCE_4_0IN       12500

#define AED_MAXFORCE_40MM         1753
#define AED_MAXFORCE_50MM         2739
#define AED_MAXFORCE_63MM         4348
#define AED_MAXFORCE_80MM         7012
#define AED_MAXFORCE_CUSTOM      16000

#define AEF_MAXFORCE_1_5IN_60PSI   760
#define AEF_MAXFORCE_2_0IN_60PSI  1540
#define AEF_MAXFORCE_2_5IN_60PSI  2550
#define AEF_MAXFORCE_3_0IN_60PSI  3780
#define AEF_MAXFORCE_3_25IN_60PSI 4480
#define AEF_MAXFORCE_4_0IN_60PSI  7070
#define AEF_MAXFORCE_CUSTOM_60PSI 3780

#define AEF_MAXFORCE_1_5IN_80PSI  1110
#define AEF_MAXFORCE_2_0IN_80PSI  2170
#define AEF_MAXFORCE_2_5IN_80PSI  3530
#define AEF_MAXFORCE_3_0IN_80PSI  5190
#define AEF_MAXFORCE_3_25IN_80PSI 6140
#define AEF_MAXFORCE_4_0IN_80PSI  9580
#define AEF_MAXFORCE_CUSTOM_80PSI 5190
#define NO_LOADCELL_OFFSET         100

#define MICRO_MAXFORCE_40MM       1350


#define ENCODER_MICROE				1  // EDP 100-143-190   Manufacturer: celera motion MicroE ; vendor part number:195-00710
#define ENCODER_OLD					2  // EDP 100-143-175 manufacturer: GSI & amphenol; vendor part number: 1-LDK-2-8-G117


enum ENCODER {
 ENCODER_ENGLISH =  1,   /* English encoder*/
 ENCODER_METRIC =   2    /* Metric encoder */
}; 
/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

struct act_nvr
{
   UINT16 ActId;                   // 1-6 ae, ao, aed, aod, aef, aof
   UINT32 ActualLifeTime;          // Number of Cycles in 1K (x1000 cycles) 
   UINT16 DefStrokeLength;         // 1-A> 4.0 5.0 6.0 7.0 8.0 80 100 125 160 Custom
   UINT16 StrokeLength;            // 1-A> 4.0 5.0 6.0 7.0 8.0 80 100 125 160 Custom
   UINT16 DefCylSize;              // 1-A> 1.5 2.0 2.5 3.0 3.25 40 50 63 80 Custom
   UINT16 CylSize;                 // 1-A> 1.5 2.0 2.5 3.0 3.25 40 50 63 80 Custom
   UINT16 DefSerNum[MAXSERIALNUM]; // 10 Words Default Serial Number
   UINT16 SerNum[MAXSERIALNUM];    // 10 Words Serial Number
   UINT16 DefCalUseName[10];       // 10 Words Default Calibration User Name
   UINT16 CalUseName[10];          // 10 Words Calibration User Name
   UINT16 DefCalDate[3];           // 3 Words Default Calibration date: 04 13 1967
   UINT16 CalDate[3];              // 3 Words Calibration date: 04 13 1967
   SINT16 DefLoadCell[11];         // 11 Words Default Load Cell Table
   SINT16 LoadCell[11];            // 11 Words Load Cell Table
   SINT16 DefPressure[11];         // 11 Words Default Pressure Table
   SINT16 Pressure[11];            // 11 Words Pressure Table
   SINT32 DefForce[FORCE_TABLE_SIZE];      // 6 of SINT32 Default Force Table
   SINT32 Force[FORCE_TABLE_SIZE];         // 6 of SINT32 Force Table
   UINT16 DefDeflection[11];       // 11 Words Default Deflection Table
   UINT16 Deflection[11];          // 11 Words Deflection Table
   UINT32 DefCalStrokeLen;         // Default Calibrated Stroke Length = 2.00in.
   UINT32 CalStrokeLen;            // Calibrated Stroke Length
   SINT16 DefCalSysPressure;       // Default Calibrated System Pressure = 60PSI.
   SINT16 CalSysPressure;          // Calibrated System Pressure
   UINT16 DefCalHomeOffset;        // Used to offset the force table
   UINT16 CalHomeOffset;           // Used to offset the force table
   UINT16 DefSpringRateSlope;      // Set to 5lbs per inch
   UINT16 SpringRateSlope;         // Set when sensor calibration is run
   UINT16 CalibDefPass;            // TRUE for pass
   UINT16 CalibPass;               // 1-3,True,False,Default
   UINT16 PSVersion;               // Software version ie. 8.06
   UINT16 ForceGauge;              // Loadcell or Sbeam
   enum ENCODER EncoderType;       // Encoder Settings
   UINT16 Dummy;              	   // dummy variable to make space between the encoder Type and the Manufacturer.
   UINT16 Manufacturer;            // Loadcell or Sbeam      
};

/*------------------------------- GLOBAL DATA ------------------------------*/
/*                       (scope is global to ALL files)                     */

extern struct act_nvr NVR;

/*
 --------------------------- FUNCTION PROTOTYPES ---------------------------
*/

void Init1(void);
void Init3(void);
void NVRWriteEWEN(void);
void NVRCommandEWDS(void);
void NVRWriteSetup(void);
void NVRWriteVerify( UINT16 Data, UINT16 Address);
void NVRWriteNovram( UINT16 Data, UINT16 Address);
void SetPressure(void);
void SetDefPressure(void);
void SetActId(UINT16 Data);
void SetActLifeTime(void);
void SetDefStrokeLength(UINT16 Data);
void SetStrokeLength(UINT16 Data);                       
void SetDefCylSize(UINT16 Data);
void SetCylSize(UINT16 Data);
void SetDefSerNum(UINT8 *Ptr); 
void SetSerNum(SINT8 *Ptr);
void SetDefLoadCell(void);                                         
void SetLoadCell(void);                                         
void SetDefDeflection(UINT16 *Ptr);                                         
void SetDeflection(UINT16 *Ptr);                                         
void SetDefForce(void);
void SetForceNVR(void);
void SetPSVersionNVR(void);
void UpdateDefForce(void);                                         
void UpdateDefCalHomeOffset(void);
void ActPowerUp(void); 
void ResetActLifeTime(void);
void NvrCopyDeftoNon(void);
void SetCalibrationDate(UINT16 *Ptr);
void SetDefCalibDate(UINT16 *Ptr);
void SetCalibPass(UINT16 Val);
void UpdateCylinderFactor(void);

void SetManufacturer(UINT16 Data);
void SetDefCalStrokeLength(UINT32 Data);                         
void SetDefCalSysPressure(SINT16 Data);
void SetCalStrokeLength(void);                       
void SetCalSysPressure(void);
void UpdateDefCalStrokeLength(void);
void UpdateDefCalSysPressure(void);

void SetDefSpringRateSlope(UINT16 Data);
UINT16 GetDefSpringRateSlope(void);
void GetDefCalStrokeLen(void);
void GetDefHomeOffset(void);
void SetCalSpringRateSlope(UINT16 Data);
void SetCalHomeOffset(void);
void SetDefCalHomeOffset(void);
void UpdateDefSpringRateSlope(void);

UINT16 GetActId(void);
UINT32 GetActLifeTime(void);
UINT16 ReadNVR(UINT16);
UINT16 ActNovramExists(void);
void TestWriteToNvram(void);
void TestReadFromNvram(void);
SINT32 GetMaxForce(void);
UINT16 GetDefStrokeLength(void);
UINT16 GetStrokeLength(void);
UINT16 GetDefCylSize(void);
UINT16 GetCylSize(void);
UINT16 GetCalibPass(void);

void GetDefPressure(void);
void GetDefLoadCell(void);
void GetDefForce(void);
void GetDefCalSysPressure(void);
void InitSetupFromAct(void);
void ActRecover(void);
void UpdateDefPressure(void);
void UpdateDefLoadCell(void);                    

void SetForceGauge(UINT16 Type);
BOOLEAN CheckNvrValid(void); 
BOOLEAN IsCalibPass(void);
BOOLEAN CheckForActChange(void);
enum ENCODER GetEncoderType (void);
void SetEncoderType (enum ENCODER Data);
#endif
