/* $Header:   D:/SWLab/VMdb/2000Series/INC/ALARMS.H_V   1.74   Dec 03 2007 11:42:36   bkymer  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*   Copyright (c) Branson Ultrasonics Corporation, 1995,96,97              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/*                                                                          */
/*   Module name:   Alarms                                                  */
/*                                                                          */
/*   Filename:      Alarms.h                                                */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*                                                                          */
/*   Revision #  Date      Author   Description                             */
/*   ==========  ========  ======   ===========                             */
/*      1        10-01-96  BEKymer  Original Release                        */
/*      2        10-03-96  BEKymer  Add alarms for pSos errors (while(1))   */
/*      3        10-14-96  LAM      add SF2 requested pvp value exceeds max */
/*                                  PVP value                               */
/*      4        10-19-96  BEKymer  New alarms for power on failures        */
/*      5        10-24-96  BEKymer  Cleanup of some badly assigned bits     */
/*      6        11-11-96  BEKymer  New alarm G81                           */
/*      7        11-14-96  BEKymer  New alarm G82                           */
/*      8        11-20-96  BEKymer  New alarm G46                           */
/*      9        01-21-97  LAM      updated 61 alarms needed for 1st release*/
/*     10        01-29-97  LAM      added nonresettable alarms              */
/*     11        02-03-97  LAM      chged sysfault masks                    */
/*     12        02-04-97  LAM      added hardware masks                    */
/*     13        02-19-97  LAM      added hardware mask for hornreturn      */
/*     14        04-07-97  BEKymer  Changed PeakPowerCutoff from G40 to W5  */
/*                                  Changed AbsoluteCutoff from G45 to W6 if*/
/*                                  sonics already started.                 */
/*                                  Make G26 generate rej & sus output      */
/*     15        04-29-97  BEKymer  Add Warnings which remove Ready signal  */
/*                                  Add System Faults which remove Ready    */
/*                                  Move Time Extended Alarm to W7 (from G46*/
/*     15.1.18   05-06-97  BEKymer  Update GA1_NORESET & GA3_NORESET        */
/*                                  Add G76 to GA3_NORESET                  */
/*                                  Create ??_CYCLE_ABORTS & ??_SONICS_ABORT*/
/*     15.1.19   05-13-97  BEKymer  Create new defines GA?_SETUP            */
/*     16.00     05-29-97  LAM      added W8                                */
/*     16.1.21   05-30-97  BEKymer  Clean up references to hex numbers!     */
/*     16.1.22   06-23-97  BEKymer  Complete change for new alarm groups    */
/*     16.1.24   07-15-97  BEKymer  Added groups for process reject & suspec*/
/*     16.1.25   07-16-97  BEKymer  Eliminate duplicates SE70,71,260-263    */
/*     16.1.26   07-21-97  BEKymer  Eliminate installation group            */
/*     16.1.27   07-23-97  BEKymer  Add reset required define for overloads */
/*     16.1.28   08-05-97  BEKymer  Add EQ_RESET                            */
/*     16.1.31   08-27-97  BEKymer  Add EQ16 to EQ_NO_RESET                 */
/*                                  Create OVERLOAD_RESET, THERMALOVERLOADS */
/*                                  _RESET, PRINTERBUFFER_RESET and START   */
/*                                  SWITCH_RESET.                           */
/*                                  Add EQ9 to EQ_NOT_REQ_RESET             */
/*     1.32      08-29-97  BEKymer  Create TESTOVERLOAD_RESET, remove OL1   */
/*                                  from OVERLOADS_RESET                    */
/*     1.33      09-08-97  LAM      deleted unused gettotalalarmcount       */
/*     1.34      09-23-97  BEKymer  Added EQ20 to EQ_NO_RESET               */
/*     1.35      09-25-97  BEKymer  Added EQ17 to EQ_NO_RESET               */
/*     1.36      10-03-97  BEKymer  Added EQ8 to EQ_RESET                   */
/*     1.37      11-10-97  PaulG    Added PRINTEROFFLINE_RESET              */
/*     1.38      11-13-97  PaulG    Added EQ20 to EQ_RESET                  */
/*     1.39      11-18-97  BEKymer  Created OL_RESET_NOT/IS_NEEDED          */
/*     1.40      12-16-97  PaulG    Added PRINTER80FULL_RESET               */
/*     1.41      01-20-98  PaulG    Moved EQ20 alarm to SE270               */
/*     1.42      01-22-98  BJB      Added OL_INC_COUNTER                    */
/*     1.43      02-02-98  LAM      added eq14 to EQ_NO_RESET, added WRONG  */
/*                                  ACTUATOR defines                        */
/*     1.44      02-03-98  BEKymer  Change NC5 alarm to CM14, expand Ground */
/*                                  Detect Cutoff to NC12 & CM2, and Ext    */
/*                                  Cycle Abort to NC7 & CM15               */
/*     1.45      02-17-98  BEKymer  Added alarms CM16-CM20                  */
/*     1.46      03-23-98  BEKymer  New define EQ_NO_CYCLEABORT             */
/*     1.47      04-28-98  LAM      added eq14(wrong actuator) to EQ_NOT_READY*/
/*     1.48      05-04-98  BEKymer  Added RESET_CALIBRATION_ALARMS,         */
/*                                  RESET_CALIBRATION_WARNINGS,             */
/*                                  and CA_NO_RESET.                        */
/*     1.49      05-20-98  BEKymer  Move Energy Not Reached alarm from PR15 */
/*                                  to CM21    DCS # 2494                   */
/*     1.50      05-22-98  BEKymer  Add EQ_UPDATE_OFTEN to allow some alarms*/
/*                                  to repeatedly updated on display        */
/*     1.51      06-17-98  BEKymer  Move CA1 to EQ20 to simplify calibration*/
/*     1.52      06-18-98  BEKymer  Finish the job started in 1.51          */
/*     1.53      08-11-98  LAM      added eq_calib_not_allowed              */
/*     1.54      11-23-98  BEKymer  Add CM22 (at the last minute, again)    */
/*     1.54.1.1  07-12-99  JZ       Added defines for ERRORCODEs            */
/*     1.56      08-03-99  JZ       added ERRORCODE for EQ10 alarm          */
/*     1.57      08-06-99  JZ       added enum ERRORCODE_ARG                */
/*     1.58      09-13-99  JZ       added ERRORCODE800_EQ20 and             */
/*                                  ERRORCODE900_EQ20 alarm                 */
/*     1.59      11-02-99  JZ       put comments for ERRORCODEs             */
/*     1.60      03-31-00  BEkymer  Added definition for ERRORCODE400_EQ20  */
/*     1.61      04-17-00  JLH      Added AED Upgrade error code            */
/*     1.62      04-18-00  JLH      Corrected error in adding AED Upgrade   */
/*                                   error code.                            */
/*     1.63      05-09-00  JLH      Changed ErrorCode declaration to extern */
/*                                   enum ERRORCODE_ARG.                    */
/*     1.64      05-09-00  LAM      Removed tabs                            */
/*     1.65      05-09-00  JLH      Removed extern declaration for ErrorCode.  */
/*                                   It was causing strange compiler problems. */  
/*     1.67      07-05-00  BEKymer  Add ALARM_MASKS typedef                 */
/*                                  Add 2 new error code for SE268          */
/*     1.68      08-11-00  SCM      Added new enum value ERRORCODE9_SE268   */
/*     1.69      09-08-00  BEKymer  Added description for ERRORCODE9_SE268  */
/*     1.70      04-24-01  LAM      chged SE46 description                  */
/*     1.71      05-06-02  LAM      added errorcode1100 & 1200              */
/*     1.74      12-03-07  BEKymer  Add EQ25 to reset required group        */
/*                                  Put back on tip as 1.74                 */
/*                                                                          */
/*                                                                          */
/*----------------------------- DESCRIPTION --------------------------------*/




/*---------------------------- INCLUDE FILES -------------------------------*/  



/*------------------------- Function Prototypes ----------------------------*/  

void   ClearTotalAlarmCount(void);
UINT8  IfAlarmEnabled(UINT32 AlarmCopy, UINT32 BitMask);
void   CountNoCycleAlarms(void);
void   CountOverloadAlarms(void);
void   CountEquipmentFailureAlarms(void);
void   CountCycleModifiedAlarms(void);
void   CountWarnings(void);
void   CountCalibrateAlarms(void);
void   CountSuspectResults(void);
void   CountRejectResults(void);
void   CountAlarms(void);
UINT8  CheckForAlarms(void);
UINT8  CheckForWarnings(void);
void   GetAlarmMask(void);


extern UINT16 ErrorCodeFlag;

/*-------------------------------- DEFINES ---------------------------------*/


/*--------------------------------------------------------------------------*/
/*  The upper 4 bits (BIT28-BIT31) are used to define which type of alarm   */
/*  has been generated.  The following defines show which types are used.   */
/*  As a result, all alarm types will not use alarms 28-31 (ie. there will  */
/*  be no G28, G29, etc).  By reserving 4 bits, and not using case 0000, up */
/*  to 15 types of alarms can be defined.                                   */
/*--------------------------------------------------------------------------*/

#define NONE  0            /* No alarm condition                            */

#define PSG1  0x10000000   /* Process Suspect Alarms - Group 1              */
#define PRG1  0x20000000   /* Process Reject Alarms - Group 1               */
#define OLG1  0x30000000   /* Overload Alarms - Group 1                     */
#define NCG1  0x40000000   /* No Cycle (No Weld) Alarms - Group 1           */
#define EQG1  0x50000000   /* Equipment Failure Alarms - Group 1            */
#define CMG1  0x60000000   /* Cycle Modified Alarms - Group 1               */
#define WAG1  0x70000000   /* Warnings - Griup 1                            */
#define CAG1  0x80000000   /* Calibration Alarms - Group 1                  */


#define SEG1  0x10000000   /* Setup group 1                                 */
#define SEG2  0x20000000   /* Setup group 2                                 */
#define SEG3  0x30000000   /* Setup group 3                                 */
#define SEG4  0x40000000   /* Setup group 4                                 */
#define SEG5  0x50000000   /* Setup group 5                                 */
#define SEG6  0x60000000   /* Setup group 6                                 */
#define SEG7  0x70000000   /* Setup group 7                                 */
#define SEG8  0x80000000   /* Setup group 8                                 */
#define SEG9  0x90000000   /* Setup group 9                                 */
#define SEG10 0xA0000000   /* Setup group 10                                */

#define ALARMTYPEMASK  0xf0000000
#define ALARMCODEMASK  0x0fffffff


#ifndef ERRORCODE_ALREADY_DEFINED
#define ERRORCODE_ALREADY_DEFINED

typedef __packed__(2,1) struct {
    SINT32  SetupGroup1;
    SINT32  SetupGroup2;
    SINT32  SetupGroup3;
    SINT32  SetupGroup4;
    SINT32  SetupGroup5;
    SINT32  SetupGroup6;
    SINT32  SetupGroup7;
    SINT32  SetupGroup8;
    SINT32  SetupGroup9;
    SINT32  SetupGroup10;
    SINT32  Overload;
    SINT32  NoCycle;
    SINT32  EquipmentFailure;
    SINT32  CycleModified;
    SINT32  Reject;
    SINT32  Suspect;
    SINT32  Warning;
    SINT32  Calibrate; } ALARM_MASKS;

enum ERRORCODE_ARG {
 ERRORCODE1_SE268 =  1,        /*  MPS    Future Release                                         */
 ERRORCODE2_SE268 =  2,        /*  Amplitude stepping on Control Level: 1 or 2                   */
 ERRORCODE3_SE268 =  3,        /*  Force stepping on Control Level: 1, 2, 3 or 4                 */
 ERRORCODE4_SE268 =  4,        /*  Using a weld mode not valid for Control Level                 */
 ERRORCODE5_SE268 =  5,        /*  Invalid distance                                              */
 ERRORCODE6_SE268 =  6,        /*  Invalid force                                                 */
 ERRORCODE7_SE268 =  7,        /*  Software version is incorrect                                 */
 ERRORCODE8_SE268 =  8,        /*  Control level or actuator is incorrect                        */
 ERRORCODE9_SE268 =  9,        /*  No associated Parameter set means invalid preset              */
 ERRORCODE10_EQ10 =  10,       /*  Actuator serial number - when any of the characters displayed */
                               /*  (in system info) are not alphanumeric.                        */
 ERRORCODE20_EQ10 =  20,       /*  Cylinder size - when the cylinder diameter is not either 1.5",*/
                               /*  2.0", 2,5", 3.0", 3.25", 40mm, 50mm, 63mm, 80mm or custom     */
 ERRORCODE30_EQ10 =  30,       /*  Stroke length - when the stroke length is not either 4", 5",  */
                               /*  6", 7", 8" , 80mm, 100mm, 125nn, 160mm or custom              */
 ERRORCODE40_EQ10 =  40,       /*  Pressure sensor calibration table - when each successive      */
                               /*  element in the table in not larger than the preceding one.    */
 ERRORCODE50_EQ10 =  50,       /*  Load cell table- when each successive element in the table in */
                               /*  not larger than the preceding one                             */
 ERRORCODE60_EQ10 =  60,       /*  Could not write to the actuator NovRam                        */

 ERRORCODE100_EQ20 =  100,     /*  The actuator serial number is different from the last time    */
                               /*  power was turned on                                           */
 ERRORCODE200_EQ20 =  200,     /*  A collapse of more than 0.2500" and less than 35 lb. of force reached */
 ERRORCODE300_EQ20 =  300,     /*  A change in horn weight of 6-7 lb. for a period of 5 seconds  */
 ERRORCODE400_EQ20 =  400,     /*  A negative collapse of more than 0.2500"                      */
 ERRORCODE500_EQ20 =  500,     /*  The system pressure was changed                               */
 ERRORCODE600_EQ20 =  600,     /*  The actuator type has been changed                            */
 ERRORCODE700_EQ20 =  700,     /*  In horn down a bad trigger has occurred                       */
 ERRORCODE800_EQ20 =  800,     /*  The part contact flag has been lost.                          */
 ERRORCODE900_EQ20 =  900,     /*  The carriage traveled more than 0.2500" and less than 35 lbs. */ 
                               /*  of force was developed after part contact and before trigger. */
 ERRORCODE1000_EQ20 = 1000,    /*  8.05 upgrade error - NVR.LoadCell[0] >100 or NVR.DefLoadCell[0]*/
                               /*  > 100.  Must recalibrate to get rid of 1000 offset.           */
 ERRORCODE1100_EQ20 = 1100,    /*  NVR.LoadCell < 100 at power up */
 ERRORCODE1200_EQ20 = 1200};   /*  NVR.LoadCell < 100 after reset sensor defaults */


#endif


   
/*--------------------------------------------------------------------------*/
/*  This group is the Setup alarms.                                         */
/*--------------------------------------------------------------------------*/

#define SE0   (SEG1 |BIT0 ) /* RESERVED                                     */
#define SE1   (SEG1 |BIT1 ) /* +-Time Limit Crossed                         */
#define SE2   (SEG1 |BIT2 ) /* +-Time Limit Crossed                         */
#define SE3   (SEG1 |BIT3 ) /* +-Eng Limit Crossed                          */
#define SE4   (SEG1 |BIT4 ) /* +-Eng Limit Crossed                          */
#define SE5   (SEG1 |BIT5 ) /* +-Pwr Limit Crossed                          */
#define SE6   (SEG1 |BIT6 ) /* +-Pwr Limit Crossed                          */
#define SE7   (SEG1 |BIT7 ) /* +-Freq Limit Crossed                         */
#define SE8   (SEG1 |BIT8 ) /* +-Freq Limit Crossed                         */
#define SE9   (SEG1 |BIT9 ) /* +-Abs Limit Crossed                          */
#define SE10  (SEG1 |BIT10) /* +-Abs Limit Crossed                          */
#define SE11  (SEG1 |BIT11) /* +-Col Limit Crossed                          */
#define SE12  (SEG1 |BIT12) /* +-Col Limit Crossed                          */
#define SE13  (SEG1 |BIT13) /* +-Frc Limit Crossed                          */
#define SE14  (SEG1 |BIT14) /* +-Frc Limit Crossed                          */
#define SE15  (SEG1 |BIT15) /* Amp Step Conflict                            */
#define SE16  (SEG1 |BIT16) /* Amp Step Conflict                            */
#define SE17  (SEG1 |BIT17) /* Amp Step Conflict                            */
#define SE18  (SEG1 |BIT18) /* Amp Step Conflict                            */
#define SE19  (SEG1 |BIT19) /* Amp Step Conflict                            */
#define SE20  (SEG1 |BIT20) /* Amp Step Conflict                            */
#define SE21  (SEG1 |BIT21) /* Amp Step Conflict                            */
#define SE22  (SEG1 |BIT22) /* Amp Step Conflict                            */
#define SE23  (SEG1 |BIT23) /* Amp Step Conflict                            */
#define SE24  (SEG1 |BIT24) /* Amp Step Conflict                            */
#define SE25  (SEG1 |BIT25) /* Amp Step Conflict                            */
#define SE26  (SEG1 |BIT26) /* Amp Step Conflict                            */
#define SE27  (SEG1 |BIT27) /* Amp Step Conflict                            */
#define SE28  (SEG1 |BIT28) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE29  (SEG1 |BIT29) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE30  (SEG1 |BIT30) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE31  (SEG1 |BIT31) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE32  (SEG2 |BIT0 ) /* RESERVED                                     */
#define SE33  (SEG2 |BIT1 ) /* Amp Step Conflict                            */
#define SE34  (SEG2 |BIT2 ) /* Amp Step Conflict                            */
#define SE35  (SEG2 |BIT3 ) /* Amp Step Conflict                            */
#define SE36  (SEG2 |BIT4 ) /* Amp Step Conflict                            */
#define SE37  (SEG2 |BIT5 ) /* Amp Step Conflict                            */
#define SE38  (SEG2 |BIT6 ) /* Amp Step Conflict                            */
#define SE39  (SEG2 |BIT7 ) /* Amp Step Conflict                            */
#define SE40  (SEG2 |BIT8 ) /* Amp Step Conflict                            */
#define SE41  (SEG2 |BIT9 ) /* Amp Step Conflict                            */
#define SE42  (SEG2 |BIT10) /* Amp Step Conflict                            */
#define SE43  (SEG2 |BIT11) /* Amp Step Conflict                            */
#define SE44  (SEG2 |BIT12) /* +-Trig Limit Crossed                         */
#define SE45  (SEG2 |BIT13) /* +-Trig Limit Crossed                         */
#define SE46  (SEG2 |BIT14) /* Preset Not Available                         */
#define SE47  (SEG2 |BIT15) /* Amp Step Conflict                            */
#define SE48  (SEG2 |BIT16) /* Amp Step Conflict                            */
#define SE49  (SEG2 |BIT17) /* Timeout Conflict                             */
#define SE50  (SEG2 |BIT18) /* Timeout Conflict                             */
#define SE51  (SEG2 |BIT19) /* Timeout Conflict                             */
#define SE52  (SEG2 |BIT20) /* Amp Step on Force                            */
#define SE53  (SEG2 |BIT21) /* Force Step on Amp                            */
#define SE54  (SEG2 |BIT22) /* -S Trg > -S Abs                              */
#define SE55  (SEG2 |BIT23) /* +S Trg > +S Abs                              */
#define SE56  (SEG2 |BIT24) /* -R Trg > -R Abs                              */
#define SE57  (SEG2 |BIT25) /* +R Trg > +R Abs                              */
#define SE58  (SEG2 |BIT26) /* Timeout Conflict                             */
#define SE59  (SEG2 |BIT27) /* Cutoff Conflict                              */
#define SE60  (SEG2 |BIT28) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE61  (SEG2 |BIT29) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE62  (SEG2 |BIT30) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE63  (SEG2 |BIT31) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE64  (SEG3 |BIT0 ) /* RESERVED                                     */
#define SE65  (SEG3 |BIT1 ) /* Cutoff Conflict                              */
#define SE66  (SEG3 |BIT2 ) /* Cutoff Conflict                              */
#define SE67  (SEG3 |BIT3 ) /* Cutoff Conflict                              */
#define SE68  (SEG3 |BIT4 ) /* Cutoff Conflict                              */
#define SE69  (SEG3 |BIT5 ) /* Cutoff Conflict                              */
#define SE70  (SEG3 |BIT6 ) /*                                              */
#define SE71  (SEG3 |BIT7 ) /*                                              */
#define SE72  (SEG3 |BIT8 ) /* Trig Delay & Pretrig                         */
#define SE73  (SEG3 |BIT9 ) /* Trig > Weld Force                            */
#define SE74  (SEG3 |BIT10) /* Time S/R Limit Cross                         */
#define SE75  (SEG3 |BIT11) /* Time S/R Limit Cross                         */
#define SE76  (SEG3 |BIT12) /* Time S/R Limit Cross                         */
#define SE77  (SEG3 |BIT13) /* Time S/R Limit Cross                         */
#define SE78  (SEG3 |BIT14) /* Eng S/R Limit Cross                          */
#define SE79  (SEG3 |BIT15) /* Eng S/R Limit Cross                          */
#define SE80  (SEG3 |BIT16) /* Eng S/R Limit Cross                          */
#define SE81  (SEG3 |BIT17) /* Eng S/R Limit Cross                          */
#define SE82  (SEG3 |BIT18) /* Pwr S/R Limit Cross                          */
#define SE83  (SEG3 |BIT19) /* Pwr S/R Limit Cross                          */
#define SE84  (SEG3 |BIT20) /* Pwr S/R Limit Cross                          */
#define SE85  (SEG3 |BIT21) /* Pwr S/R Limit Cross                          */
#define SE86  (SEG3 |BIT22) /* Abs S/R Limit Cross                          */
#define SE87  (SEG3 |BIT23) /* Abs S/R Limit Cross                          */
#define SE88  (SEG3 |BIT24) /* Abs S/R Limit Cross                          */
#define SE89  (SEG3 |BIT25) /* Abs S/R Limit Cross                          */
#define SE90  (SEG3 |BIT26) /* Col S/R Limit Cross                          */
#define SE91  (SEG3 |BIT27) /* Col S/R Limit Cross                          */
#define SE92  (SEG3 |BIT28) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE93  (SEG3 |BIT29) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE94  (SEG3 |BIT30) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE95  (SEG3 |BIT31) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE96  (SEG4 |BIT0 ) /* RESERVED                                     */
#define SE97  (SEG4 |BIT1 ) /* Col S/R Limit Cross                          */
#define SE98  (SEG4 |BIT2 ) /* Col S/R Limit Cross                          */
#define SE99  (SEG4 |BIT3 ) /* Frc S/R Limit Cross                          */
#define SE100 (SEG4 |BIT4 ) /* Frc S/R Limit Cross                          */
#define SE101 (SEG4 |BIT5 ) /* Frc S/R Limit Cross                          */
#define SE102 (SEG4 |BIT6 ) /* Frc S/R Limit Cross                          */
#define SE103 (SEG4 |BIT7 ) /* Freq S/R Limit Cross                         */
#define SE104 (SEG4 |BIT8 ) /* Freq S/R Limit Cross                         */
#define SE105 (SEG4 |BIT9 ) /* Freq S/R Limit Cross                         */
#define SE106 (SEG4 |BIT10) /* Freq S/R Limit Cross                         */
#define SE107 (SEG4 |BIT11) /* Trig S/R Limit Cross                         */
#define SE108 (SEG4 |BIT12) /* Trig S/R Limit Cross                         */
#define SE109 (SEG4 |BIT13) /* Trig S/R Limit Cross                         */
#define SE110 (SEG4 |BIT14) /* Trig S/R Limit Cross                         */
#define SE111 (SEG4 |BIT15) /* Force Step Cutoff                            */
#define SE112 (SEG4 |BIT16) /* Force Step Cutoff                            */
#define SE113 (SEG4 |BIT17) /* Force Step Cutoff                            */
#define SE114 (SEG4 |BIT18) /* Force Step Cutoff                            */
#define SE115 (SEG4 |BIT19) /* Force Step Cutoff                            */
#define SE116 (SEG4 |BIT20) /* Force Step Cutoff                            */
#define SE117 (SEG4 |BIT21) /* Force Step Cutoff                            */
#define SE118 (SEG4 |BIT22) /* Force Step Cutoff                            */
#define SE119 (SEG4 |BIT23) /* Energy Comp Crossed                          */
#define SE120 (SEG4 |BIT24) /*                                              */
#define SE121 (SEG4 |BIT25) /* Pretrigger Conflict                          */
#define SE122 (SEG4 |BIT26) /* Pretrigger Conflict                          */
#define SE123 (SEG4 |BIT27) /* Pretrigger Conflict                          */
#define SE124 (SEG4 |BIT28) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE125 (SEG4 |BIT29) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE126 (SEG4 |BIT30) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE127 (SEG4 |BIT31) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE128 (SEG5 |BIT0 ) /* RESERVED                                     */
#define SE129 (SEG5 |BIT1 ) /* Pretrigger Conflict                          */
#define SE130 (SEG5 |BIT2 ) /* Pretrigger Conflict                          */
#define SE131 (SEG5 |BIT3 ) /* Pretrigger Conflict                          */
#define SE132 (SEG5 |BIT4 ) /* Pretrigger Conflict                          */
#define SE133 (SEG5 |BIT5 ) /* Pretrigger Conflict                          */
#define SE134 (SEG5 |BIT6 ) /* Pretrigger Conflict                          */
#define SE135 (SEG5 |BIT7 ) /* Pretrigger Conflict                          */
#define SE136 (SEG5 |BIT8 ) /* Pretrigger Conflict                          */
#define SE137 (SEG5 |BIT9 ) /* Pretrigger Conflict                          */
#define SE138 (SEG5 |BIT10) /* Abs Cutoff Conflict                          */
#define SE139 (SEG5 |BIT11) /* Abs Cutoff Conflict                          */
#define SE140 (SEG5 |BIT12) /* Abs Cutoff Conflict                          */
#define SE141 (SEG5 |BIT13) /* Abs Cutoff Conflict                          */
#define SE142 (SEG5 |BIT14) /* Abs Cutoff Conflict                          */
#define SE143 (SEG5 |BIT15) /* Abs Cutoff Conflict                          */
#define SE144 (SEG5 |BIT16) /* Abs Cutoff Conflict                          */
#define SE145 (SEG5 |BIT17) /* Abs Cutoff Conflict                          */
#define SE146 (SEG5 |BIT18) /* Missing Part Conflct                         */
#define SE147 (SEG5 |BIT19) /* Missing Part Conflct                         */
#define SE148 (SEG5 |BIT20) /* Missing Part Conflct                         */
#define SE149 (SEG5 |BIT21) /* Missing Part Conflct                         */
#define SE150 (SEG5 |BIT22) /* Missing Part Conflct                         */
#define SE151 (SEG5 |BIT23) /* Missing Part Conflct                         */
#define SE152 (SEG5 |BIT24) /* Missing Part Conflct                         */
#define SE153 (SEG5 |BIT25) /* Missing Part Conflct                         */
#define SE154 (SEG5 |BIT26) /* Missing Part Conflct                         */
#define SE155 (SEG5 |BIT27) /* Missing Part Conflct                         */
#define SE156 (SEG5 |BIT28) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE157 (SEG5 |BIT29) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE158 (SEG5 |BIT30) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE159 (SEG5 |BIT31) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE160 (SEG6 |BIT0 ) /* RESERVED                                     */
#define SE161 (SEG6 |BIT1 ) /* Missing Part Conflct                         */
#define SE162 (SEG6 |BIT2 ) /* Missing Part Conflct                         */
#define SE163 (SEG6 |BIT3 ) /* Missing Part Conflct                         */
#define SE164 (SEG6 |BIT4 ) /* Missing Part Conflct                         */
#define SE165 (SEG6 |BIT5 ) /* Missing Part Conflct                         */
#define SE166 (SEG6 |BIT6 ) /* Missing Part Conflct                         */
#define SE167 (SEG6 |BIT7 ) /* Missing Part Conflct                         */
#define SE168 (SEG6 |BIT8 ) /* Missing Part Conflct                         */
#define SE169 (SEG6 |BIT9 ) /* Missing Part Conflct                         */
#define SE170 (SEG6 |BIT10) /* Energy Comp Conflict                         */
#define SE171 (SEG6 |BIT11) /* Energy Comp Conflict                         */
#define SE172 (SEG6 |BIT12) /* Energy Comp Conflict                         */
#define SE173 (SEG6 |BIT13) /* Energy Comp Conflict                         */
#define SE174 (SEG6 |BIT14) /* Rapid Trav. Conflict                         */
#define SE175 (SEG6 |BIT15) /* Rapid Trav. Conflict                         */
#define SE176 (SEG6 |BIT16) /* Rapid Trav. Conflict                         */
#define SE177 (SEG6 |BIT17) /* Rapid Trav. Conflict                         */
#define SE178 (SEG6 |BIT18) /* Rapid Trav. Conflict                         */
#define SE179 (SEG6 |BIT19) /* Rapid Trav. Conflict                         */
#define SE180 (SEG6 |BIT20) /* Rapid Trav. Conflict                         */
#define SE181 (SEG6 |BIT21) /* Rapid Trav. Conflict                         */
#define SE182 (SEG6 |BIT22) /* Rapid Trav. Conflict                         */
#define SE183 (SEG6 |BIT23) /* Rapid Trav. Conflict                         */
#define SE184 (SEG6 |BIT24) /* Rapid Trav. Conflict                         */
#define SE185 (SEG6 |BIT25) /* Rapid Trav. Conflict                         */
#define SE186 (SEG6 |BIT26) /* Rapid Trav. Conflict                         */
#define SE187 (SEG6 |BIT27) /* Rapid Trav. Conflict                         */
#define SE188 (SEG6 |BIT28) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE189 (SEG6 |BIT29) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE190 (SEG6 |BIT30) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE191 (SEG6 |BIT31) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE192 (SEG7 |BIT0 ) /* RESERVED                                     */
#define SE193 (SEG7 |BIT1 ) /* Rapid Trav. Conflict                         */
#define SE194 (SEG7 |BIT2 ) /* Rapid Trav. Conflict                         */
#define SE195 (SEG7 |BIT3 ) /* Rapid Trav. Conflict                         */
#define SE196 (SEG7 |BIT4 ) /* Hold Force Conflict                          */
#define SE197 (SEG7 |BIT5 ) /* Hold Force Conflict                          */
#define SE198 (SEG7 |BIT6 ) /* Hold Force Conflict                          */
#define SE199 (SEG7 |BIT7 ) /* Hold Force Conflict                          */
#define SE200 (SEG7 |BIT8 ) /* Force/Lmt Conflict                           */
#define SE201 (SEG7 |BIT9 ) /* Force/Lmt Conflict                           */
#define SE202 (SEG7 |BIT10) /* Force/Lmt Conflict                           */
#define SE203 (SEG7 |BIT11) /* Force/Lmt Conflict                           */
#define SE204 (SEG7 |BIT12) /* Force/Lmt Conflict                           */
#define SE205 (SEG7 |BIT13) /* Force/Lmt Conflict                           */
#define SE206 (SEG7 |BIT14) /* Force/Lmt Conflict                           */
#define SE207 (SEG7 |BIT15) /* Force/Lmt Conflict                           */
#define SE208 (SEG7 |BIT16) /* Force Step Conflict                          */
#define SE209 (SEG7 |BIT17) /* Force Step Conflict                          */
#define SE210 (SEG7 |BIT18) /* Force Step Conflict                          */
#define SE211 (SEG7 |BIT19) /* Force Step Conflict                          */
#define SE212 (SEG7 |BIT20) /* Force Step Conflict                          */
#define SE213 (SEG7 |BIT21) /* Force Step Conflict                          */
#define SE214 (SEG7 |BIT22) /* Force Step Conflict                          */
#define SE215 (SEG7 |BIT23) /* Force Step Conflict                          */
#define SE216 (SEG7 |BIT24) /* Force Step Conflict                          */
#define SE217 (SEG7 |BIT25) /* Force Step Conflict                          */
#define SE218 (SEG7 |BIT26) /* Force Step Conflict                          */
#define SE219 (SEG7 |BIT27) /* Force Step Conflict                          */
#define SE220 (SEG7 |BIT28) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE221 (SEG7 |BIT29) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE222 (SEG7 |BIT30) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE223 (SEG7 |BIT31) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE224 (SEG8 |BIT0 ) /* RESERVED                                     */
#define SE225 (SEG8 |BIT1 ) /* Force Step Conflict                          */
#define SE226 (SEG8 |BIT2 ) /* Force Step Conflict                          */
#define SE227 (SEG8 |BIT3 ) /* Force Step Conflict                          */
#define SE228 (SEG8 |BIT4 ) /* Force Step Conflict                          */
#define SE229 (SEG8 |BIT5 ) /* Force Step Conflict                          */
#define SE230 (SEG8 |BIT6 ) /* Force Step Conflict                          */
#define SE231 (SEG8 |BIT7 ) /* Force Step Conflict                          */
#define SE232 (SEG8 |BIT8 ) /* Force Step Conflict                          */
#define SE233 (SEG8 |BIT9 ) /* Force Step Conflict                          */
#define SE234 (SEG8 |BIT10) /* Force Step Conflict                          */
#define SE235 (SEG8 |BIT11) /* Force Step Conflict                          */
#define SE236 (SEG8 |BIT12) /* Force Step Conflict                          */
#define SE237 (SEG8 |BIT13) /* Force Step Conflict                          */
#define SE238 (SEG8 |BIT14) /* Force Step Conflict                          */
#define SE239 (SEG8 |BIT15) /* Force Step Conflict                          */
#define SE240 (SEG8 |BIT16) /* Force Step Conflict                          */
#define SE241 (SEG8 |BIT17) /* Force Step Conflict                          */
#define SE242 (SEG8 |BIT18) /* Force Step Conflict                          */
#define SE243 (SEG8 |BIT19) /* Force Step Conflict                          */
#define SE244 (SEG8 |BIT20) /* Amp/F Step Conflict                          */
#define SE245 (SEG8 |BIT21) /* Weld Force>Pressure                          */
#define SE246 (SEG8 |BIT22) /* Force B>Pressure                             */
#define SE247 (SEG8 |BIT23) /* Hold Force>Pressure                          */
#define SE248 (SEG8 |BIT24) /* Pressure>Weld Force                          */
#define SE249 (SEG8 |BIT25) /* Pressure>Force B                             */
#define SE250 (SEG8 |BIT26) /* Pressure>Hold Force                          */
#define SE251 (SEG8 |BIT27) /* Trig Force Conflict                          */
#define SE252 (SEG8 |BIT28) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE253 (SEG8 |BIT29) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE254 (SEG8 |BIT30) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE255 (SEG8 |BIT31) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE256 (SEG9 |BIT0 ) /* RESERVED                                     */
#define SE257 (SEG9 |BIT1 ) /* Trig Force Conflict                          */
#define SE258 (SEG9 |BIT2 ) /* Adv Features in Use                          */
#define SE259 (SEG9 |BIT3 ) /* Encoder Required                             */
#define SE260 (SEG9 |BIT4 ) /*                                              */
#define SE261 (SEG9 |BIT5 ) /*                                              */
#define SE262 (SEG9 |BIT6 ) /*                                              */
#define SE263 (SEG9 |BIT7 ) /*                                              */
#define SE264 (SEG9 |BIT8 ) /* Energy Comp Conflict                         */
#define SE265 (SEG9 |BIT9 ) /* Energy Comp Conflict                         */
#define SE266 (SEG9 |BIT10) /* Energy Comp Conflict                         */
#define SE267 (SEG9 |BIT11) /* Energy Comp Conflict                         */
#define SE268 (SEG9 |BIT12) /* Invalid Preset                               */
#define SE269 (SEG9 |BIT13) /* Undefined Preset                             */
#define SE270 (SEG9 |BIT14) /* Printer offline                              */
#define SE271 (SEG9 |BIT15) /*                                              */
#define SE272 (SEG9 |BIT16) /*                                              */
#define SE273 (SEG9 |BIT17) /*                                              */
#define SE274 (SEG9 |BIT18) /*                                              */
#define SE275 (SEG9 |BIT19) /*                                              */
#define SE276 (SEG9 |BIT20) /*                                              */
#define SE277 (SEG9 |BIT21) /*                                              */
#define SE278 (SEG9 |BIT22) /*                                              */         
#define SE279 (SEG9 |BIT23) /*                                              */
#define SE280 (SEG9 |BIT24) /*                                              */
#define SE281 (SEG9 |BIT25) /*                                              */
#define SE282 (SEG9 |BIT26) /*                                              */
#define SE283 (SEG9 |BIT27) /*                                              */
#define SE284 (SEG9 |BIT28) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE285 (SEG9 |BIT29) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE286 (SEG9 |BIT30) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE287 (SEG9 |BIT31) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE288 (SEG10|BIT0 ) /* RESERVED                                     */
#define SE289 (SEG10|BIT1 ) /*                                              */
#define SE290 (SEG10|BIT2 ) /*                                              */
#define SE291 (SEG10|BIT3 ) /*                                              */
#define SE292 (SEG10|BIT4 ) /*                                              */
#define SE293 (SEG10|BIT5 ) /*                                              */
#define SE294 (SEG10|BIT6 ) /*                                              */
#define SE295 (SEG10|BIT7 ) /*                                              */
#define SE296 (SEG10|BIT8 ) /*                                              */
#define SE297 (SEG10|BIT9 ) /*                                              */
#define SE298 (SEG10|BIT10) /*                                              */
#define SE299 (SEG10|BIT11) /*                                              */
#define SE300 (SEG10|BIT12) /*                                              */
#define SE301 (SEG10|BIT13) /*                                              */
#define SE302 (SEG10|BIT14) /*                                              */
#define SE303 (SEG10|BIT15) /*                                              */
#define SE304 (SEG10|BIT16) /*                                              */
#define SE305 (SEG10|BIT17) /*                                              */
#define SE306 (SEG10|BIT18) /*                                              */
#define SE307 (SEG10|BIT19) /*                                              */
#define SE308 (SEG10|BIT20) /*                                              */
#define SE309 (SEG10|BIT21) /*                                              */
#define SE310 (SEG10|BIT22) /*                                              */
#define SE311 (SEG10|BIT23) /*                                              */
#define SE312 (SEG10|BIT24) /*                                              */
#define SE313 (SEG10|BIT25) /*                                              */
#define SE314 (SEG10|BIT26) /*                                              */
#define SE315 (SEG10|BIT27) /*                                              */
#define SE316 (SEG10|BIT28) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE317 (SEG10|BIT29) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE318 (SEG10|BIT30) /* RESERVED FOR USE BY ALARM TYPE.              */
#define SE319 (SEG10|BIT31) /* RESERVED FOR USE BY ALARM TYPE.              */



/*--------------------------------------------------------------------------*/
/* This first new group is No Cycle Alarms                                  */
/*--------------------------------------------------------------------------*/

#define NC0   (NCG1|BIT0 ) /* RESERVED                                      */
#define NC1   (NCG1|BIT1 ) /* Upper Limit Timeout                           */
#define NC2   (NCG1|BIT2 ) /*                                               */
#define NC3   (NCG1|BIT3 ) /* Trg before Pretrg                             */
#define NC4   (NCG1|BIT4 ) /* Trigger Timeout                               */
#define NC5   (NCG1|BIT5 ) /*                                               */
#define NC6   (NCG1|BIT6 ) /* LLS abort before TRS                          */
#define NC7   (NCG1|BIT7 ) /* External Cycle Abort (before trigger)         */
#define NC8   (NCG1|BIT8 ) /* Missing Part Abort                            */
#define NC9   (NCG1|BIT9 ) /* Abs before Trg                                */
#define NC10  (NCG1|BIT10) /* Amp Step before Trg                           */
#define NC11  (NCG1|BIT11) /* Frc Step before Trg                           */
#define NC12  (NCG1|BIT12) /* Ground Detect Cutoff (before trigger)         */
#define NC13  (NCG1|BIT13) /*                                               */
#define NC14  (NCG1|BIT14) /*                                               */
#define NC15  (NCG1|BIT15) /*                                               */
#define NC16  (NCG1|BIT16) /*                                               */
#define NC17  (NCG1|BIT17) /*                                               */
#define NC18  (NCG1|BIT18) /*                                               */
#define NC19  (NCG1|BIT19) /*                                               */
#define NC20  (NCG1|BIT20) /*                                               */
#define NC21  (NCG1|BIT21) /*                                               */
#define NC22  (NCG1|BIT22) /*                                               */
#define NC23  (NCG1|BIT23) /*                                               */
#define NC24  (NCG1|BIT24) /*                                               */
#define NC25  (NCG1|BIT25) /*                                               */
#define NC26  (NCG1|BIT26) /*                                               */
#define NC27  (NCG1|BIT27) /*                                               */
#define NC28  (NCG1|BIT28) /* RESERVED FOR USE BY ALARM TYPE.               */
#define NC29  (NCG1|BIT29) /* RESERVED FOR USE BY ALARM TYPE.               */
#define NC30  (NCG1|BIT30) /* RESERVED FOR USE BY ALARM TYPE.               */
#define NC31  (NCG1|BIT31) /* RESERVED FOR USE BY ALARM TYPE.               */


/*---  No cycle alarms which are NOT affected by Reset Required   ---*/
/*---      (Dont include those which must be cleared first)       ---*/

#define NC_NOT_REQ_RESET    (~(NONE))



/*--------------------------------------------------------------------------*/
/* The second new group is Overload Alarms                                  */
/*--------------------------------------------------------------------------*/

#define OL0   (OLG1|BIT0 ) /* RESERVED                                      */
#define OL1   (OLG1|BIT1 ) /* Test Overload                                 */
#define OL2   (OLG1|BIT2 ) /* Pretrigger Overload                           */
#define OL3   (OLG1|BIT3 ) /* Seek Overload                                 */
#define OL4   (OLG1|BIT4 ) /* Power Supply O/L                              */
#define OL5   (OLG1|BIT5 ) /* Cont Pwr Limit                                */
#define OL6   (OLG1|BIT6 ) /* Afterburst Overload                           */
#define OL7   (OLG1|BIT7 ) /* Pre-Weld Seek O/L                             */
#define OL8   (OLG1|BIT8 ) /* Post Weld Seek O/L                            */
#define OL9   (OLG1|BIT9 ) /*                                               */
#define OL10  (OLG1|BIT10) /*                                               */
#define OL11  (OLG1|BIT11) /*                                               */
#define OL12  (OLG1|BIT12) /*                                               */
#define OL13  (OLG1|BIT13) /*                                               */
#define OL14  (OLG1|BIT14) /*                                               */
#define OL15  (OLG1|BIT15) /*                                               */
#define OL16  (OLG1|BIT16) /*                                               */
#define OL17  (OLG1|BIT17) /*                                               */
#define OL18  (OLG1|BIT18) /*                                               */
#define OL19  (OLG1|BIT19) /*                                               */
#define OL20  (OLG1|BIT20) /*                                               */
#define OL21  (OLG1|BIT21) /*                                               */
#define OL22  (OLG1|BIT22) /*                                               */
#define OL23  (OLG1|BIT23) /*                                               */
#define OL24  (OLG1|BIT24) /*                                               */
#define OL25  (OLG1|BIT25) /*                                               */
#define OL26  (OLG1|BIT26) /*                                               */
#define OL27  (OLG1|BIT27) /*                                               */
#define OL28  (OLG1|BIT28) /* RESERVED FOR USE BY ALARM TYPE.               */
#define OL29  (OLG1|BIT29) /* RESERVED FOR USE BY ALARM TYPE.               */
#define OL30  (OLG1|BIT30) /* RESERVED FOR USE BY ALARM TYPE.               */
#define OL31  (OLG1|BIT31) /* RESERVED FOR USE BY ALARM TYPE.               */


/*---  Overload alarms which will generate reject output  ---*/

#define OL_REJECT       (OL2|OL4|OL5)


/*---  Overload alarms which will abort the cycle  ---*/

#define OL_CYCLE_ABORT  (OL2|OL5|OL7)


/*---  Overload alarms which will increment the overload counter  ---*/

#define OL_INC_COUNTER  (OL2|OL4|OL6|OL7|OL8)


/*---  Overload alarms which must be reset  ---*/

#define OL_RESET       (OL1|OL3|OL5|OL7|OL8)


/*---  Overload alarms which are NOT affected by Reset Required   ---*/
/*---      (Dont include those which must be cleared first)       ---*/

#define OL_NOT_REQ_RESET    (~(NONE))


/*--  These defines are used to actually clear the alarms in ClearAlarm() --*/

#define OL_RESET_NOT_NEEDED ((~(OL2|OL4|OL6)) | ALARMTYPEMASK)/*Reset not required*/
#define OL_RESET_IS_NEEDED  ((~(OL1|OL3|OL5|OL7|OL8)) | ALARMTYPEMASK)/*Reset is required */
#define TESTOVERLOAD_RESET  ((~(OL1)) | ALARMTYPEMASK)


/*--------------------------------------------------------------------------*/
/* The next new group is Equipment Failure Alarms                           */
/*--------------------------------------------------------------------------*/

#define EQ0   (EQG1|BIT0 ) /* RESERVED                                      */
#define EQ1   (EQG1|BIT1 ) /* Encoder Fail                                  */
#define EQ2   (EQG1|BIT2 ) /* Upper Limit Switch                            */
#define EQ3   (EQG1|BIT3 ) /* Upper Limit Switch                            */
#define EQ4   (EQG1|BIT4 ) /* Door Sw Fail                                  */
#define EQ5   (EQG1|BIT5 ) /* Loadcell Fail                                 */
#define EQ6   (EQG1|BIT6 ) /* Solenoid Drive Fail                           */
#define EQ7   (EQG1|BIT7 ) /* Thermal Overload                              */
#define EQ8   (EQG1|BIT8 ) /* Preset Data/BBR                               */
#define EQ9   (EQG1|BIT9 ) /* Horn Return Timeout                           */
#define EQ10  (EQG1|BIT10) /* Actuator NovRam                               */
#define EQ11  (EQG1|BIT11) /* P/S NovRam                                    */
#define EQ12  (EQG1|BIT12) /* Start Sw Time                                 */
#define EQ13  (EQG1|BIT13) /* MPS Switch Failed                             */
#define EQ14  (EQG1|BIT14) /* Wrong Actuator                                */
#define EQ15  (EQG1|BIT15) /* Ultrasonics P/S                               */
#define EQ16  (EQG1|BIT16) /* Printer Buffer Full                           */
#define EQ17  (EQG1|BIT17) /* Start Switch Closed                           */
#define EQ18  (EQG1|BIT18) /* Pretrigger Timeout                            */
#define EQ19  (EQG1|BIT19) /* Actuator Not Found                            */
#define EQ20  (EQG1|BIT20) /* Recalibrate Actuator (was CA1)                */
#define EQ21  (EQG1|BIT21) /* Act Clear Function                            */
#define EQ22  (EQG1|BIT22) /* Stack                                         */
#define EQ23  (EQG1|BIT23) /* Start Switches Lost                           */
#define EQ24  (EQG1|BIT24) /* Actuator Type                                 */
#define EQ25  (EQG1|BIT25) /* Air Pressure Incorrect                        */
#define EQ26  (EQG1|BIT26) /*                                               */
#define EQ27  (EQG1|BIT27) /*                                               */
#define EQ28  (EQG1|BIT28) /* RESERVED FOR USE BY ALARM TYPE.               */
#define EQ29  (EQG1|BIT29) /* RESERVED FOR USE BY ALARM TYPE.               */
#define EQ30  (EQG1|BIT30) /* RESERVED FOR USE BY ALARM TYPE.               */
#define EQ31  (EQG1|BIT31) /* RESERVED FOR USE BY ALARM TYPE.               */


/*---  Equipment failure alarms which will generate reject output  ---*/

#define EQ_REJECT       (EQ1|EQ2|EQ3|EQ4|EQ5|EQ6|EQ7|EQ8|EQ18|EQ20|EQ23|EQ24)


/*---  Equipment failure alarms which will remove the ready output  ---*/

#define EQ_NOT_READY    (EQ1|EQ2|EQ3|EQ4|EQ5|EQ6|EQ7|EQ8|EQ14|EQ19|EQ20|EQ21|EQ24)


/*---  Equipment failure alarms which must be reset  ---*/

#define EQ_RESET    (EQ1|EQ2|EQ3|EQ4|EQ5|EQ7|EQ8|EQ24|EQ25)        


/*---  Equipment failure alarms which cannot be reset unless fixed ---*/

#define EQ_NO_RESET    (EQ2|EQ4|EQ7|EQ14|EQ16|EQ17|EQ20)


/*---  Equipment failure alarms which are NOT affected by Reset Required  --*/
/*---        (Dont include those which must be cleared first)             --*/

#define EQ_NOT_REQ_RESET    (~(EQ9|EQ12|EQ17|EQ23))


/*---  Equipment failure alarms which will NOT set the CycleAbort flag  --*/

#define EQ_NO_CYCLEABORT    (~(EQ16))


/*---  Equipment failure alarms allowed to update display more than once ---*/

#define EQ_UPDATE_OFTEN    (EQ12)


/*---  Equipment failure alarms which will still allow calibration  ---*/

#define EQ_CALIB_ALLOWED   (EQ4|EQ20)
#define EQ_CALIB_NOT_ALLOWED   (EQ10)
#define RESET_CALIBRATION_ALARMS   ((~EQ20) | ALARMTYPEMASK) 



#define DOOR_TRIG_FAIL         (EQ4 & ALARMCODEMASK)    
#define DOOR_TRIG_FAIL_RESET   ((~EQ4) | ALARMTYPEMASK) 
#define ENCODER_FAIL           (EQ1 & ALARMCODEMASK)    
#define ENCODER_FAIL_RESET     ((~EQ1) | ALARMTYPEMASK  
#define ULS_FAIL               (EQ2 & ALARMCODEMASK)    
#define ULS_FAIL_RESET         ((~EQ2) | ALARMTYPEMASK) 
#define WRONG_ACTUATOR_FAIL    (EQ14 & ALARMCODEMASK)    
#define WRONG_ACTUATOR_FAIL_RESET ((~EQ14) | ALARMTYPEMASK) 
#define ULSRETURN_FAIL         (EQ9 & ALARMCODEMASK)   
#define ULSRETURN_FAIL_RESET   ((~EQ9) | ALARMTYPEMASK)
#define PRINTERBUFFER_RESET    ((~EQ16) | ALARMTYPEMASK)
#define THERMALOVERLOADS_RESET ((~EQ7)  | ALARMTYPEMASK)
#define STARTSWITCH_RESET      ((~EQ17) | ALARMTYPEMASK)

                           
/*--------------------------------------------------------------------------*/
/* The next new group is Cycle Modified Alarms                              */
/*--------------------------------------------------------------------------*/

#define CM0   (CMG1|BIT0 ) /* RESERVED                                      */
#define CM1   (CMG1|BIT1 ) /* Trigger Lost in Hold                          */
#define CM2   (CMG1|BIT2 ) /* Ground Detect Cutoff (after trigger)          */
#define CM3   (CMG1|BIT3 ) /* Max Timeout                                   */
#define CM4   (CMG1|BIT4 ) /* No Amplitude Step                             */
#define CM5   (CMG1|BIT5 ) /* No Force Step                                 */
#define CM6   (CMG1|BIT6 ) /* No Amplitude Step                             */
#define CM7   (CMG1|BIT7 ) /* No Force Step                                 */
#define CM8   (CMG1|BIT8 ) /* No Amplitude Step                             */
#define CM9   (CMG1|BIT9 ) /* No Amplitude Step                             */
#define CM10  (CMG1|BIT10) /* No Force Step                                 */
#define CM11  (CMG1|BIT11) /* No Amplitude Step                             */
#define CM12  (CMG1|BIT12) /* No Amplitude Step                             */
#define CM13  (CMG1|BIT13) /*                                               */
#define CM14  (CMG1|BIT14) /* Trigger Lost in Weld                          */
#define CM15  (CMG1|BIT15) /* External Cycle Abort (after trigger)          */
#define CM16  (CMG1|BIT16) /* Amp B Not Reached (too low)                   */
#define CM17  (CMG1|BIT17) /* Amp Not Reached                               */
#define CM18  (CMG1|BIT18) /* Amp A Not Reached                             */
#define CM19  (CMG1|BIT19) /* Amp B Not Reached (too high)                  */
#define CM20  (CMG1|BIT20) /* Amp Exceeded                                  */
#define CM21  (CMG1|BIT21) /* Energy Not Reached                            */
#define CM22  (CMG1|BIT22) /* Trigger > Weld Force                          */
#define CM23  (CMG1|BIT23) /*                                               */
#define CM24  (CMG1|BIT24) /*                                               */
#define CM25  (CMG1|BIT25) /*                                               */
#define CM26  (CMG1|BIT26) /*                                               */
#define CM27  (CMG1|BIT27) /*                                               */
#define CM28  (CMG1|BIT28) /* RESERVED FOR USE BY ALARM TYPE.               */
#define CM29  (CMG1|BIT29) /* RESERVED FOR USE BY ALARM TYPE.               */
#define CM30  (CMG1|BIT30) /* RESERVED FOR USE BY ALARM TYPE.               */
#define CM31  (CMG1|BIT31) /* RESERVED FOR USE BY ALARM TYPE.               */


/*---  Cycle modified alarms which will abort the cycle  ---*/

#define CM_CYCLE_ABORT   (CM1|CM2|CM14|CM15)


/*---  Cycle modified alarms which will abort the sonics  ---*/

#define CM_SONICS_ABORT  (CM3)


/*---  Cycle modified alarms which are NOT affected by Reset Required   ---*/
/*---         (Dont include those which must be cleared first)          ---*/

#define CM_NOT_REQ_RESET    (~(NONE))






/*--------------------------------------------------------------------------*/
/* The next new group is Calibrate Alarms                                   */
/*--------------------------------------------------------------------------*/

#define CA0   (CAG1|BIT0 ) /* RESERVED                                      */
#define CA1   (CAG1|BIT1 ) /*                                               */
#define CA2   (CAG1|BIT2 ) /*                                               */
#define CA3   (CAG1|BIT3 ) /*                                               */
#define CA4   (CAG1|BIT4 ) /*                                               */
#define CA5   (CAG1|BIT5 ) /*                                               */
#define CA6   (CAG1|BIT6 ) /*                                               */
#define CA7   (CAG1|BIT7 ) /*                                               */
#define CA8   (CAG1|BIT8 ) /*                                               */
#define CA9   (CAG1|BIT9 ) /*                                               */
#define CA10  (CAG1|BIT10) /*                                               */
#define CA11  (CAG1|BIT11) /*                                               */
#define CA12  (CAG1|BIT12) /*                                               */
#define CA13  (CAG1|BIT13) /*                                               */
#define CA14  (CAG1|BIT14) /*                                               */
#define CA15  (CAG1|BIT15) /*                                               */
#define CA16  (CAG1|BIT16) /*                                               */
#define CA17  (CAG1|BIT17) /*                                               */
#define CA18  (CAG1|BIT18) /*                                               */
#define CA19  (CAG1|BIT19) /*                                               */
#define CA20  (CAG1|BIT20) /*                                               */
#define CA21  (CAG1|BIT21) /*                                               */
#define CA22  (CAG1|BIT22) /*                                               */
#define CA23  (CAG1|BIT23) /*                                               */
#define CA24  (CAG1|BIT24) /*                                               */
#define CA25  (CAG1|BIT25) /*                                               */
#define CA26  (CAG1|BIT26) /*                                               */
#define CA27  (CAG1|BIT27) /*                                               */
#define CA28  (CAG1|BIT28) /* RESERVED FOR USE BY ALARM TYPE.               */
#define CA29  (CAG1|BIT29) /* RESERVED FOR USE BY ALARM TYPE.               */
#define CA30  (CAG1|BIT30) /* RESERVED FOR USE BY ALARM TYPE.               */
#define CA31  (CAG1|BIT31) /* RESERVED FOR USE BY ALARM TYPE.               */


/*---  Calibration alarms which cannot be reset unless fixed ---*/

#define CA_NO_RESET    (NONE)




/*--------------------------------------------------------------------------*/
/* The next new group is Warnings                                           */
/*--------------------------------------------------------------------------*/

#define W0   (WAG1|BIT0 )  /* RESERVED                                      */
#define W1   (WAG1|BIT1 )  /* Actuator Clear not reached                    */
#define W2   (WAG1|BIT2 )  /* Max Energy Reached                            */
#define W3   (WAG1|BIT3 )  /* Printer Buffer 80%                            */
#define W4   (WAG1|BIT4 )  /* Cont Pwr Limit                                */
#define W5   (WAG1|BIT5 )  /* Peak Power Cutoff                             */
#define W6   (WAG1|BIT6 )  /* Absolute Cutoff                               */
#define W7   (WAG1|BIT7 )  /* Time Extended                                 */
#define W8   (WAG1|BIT8 )  /* Actuator Recal Suggested                      */
#define W9   (WAG1|BIT9 )  /* Collapse Cutoff                               */
#define W10  (WAG1|BIT10)  /* Act Clear Not Reached (MPS)                   */
#define W11  (WAG1|BIT11)  /*                                               */
#define W12  (WAG1|BIT12)  /*                                               */
#define W13  (WAG1|BIT13)  /*                                               */
#define W14  (WAG1|BIT14)  /*                                               */
#define W15  (WAG1|BIT15)  /*                                               */
#define W16  (WAG1|BIT16)  /*                                               */
#define W17  (WAG1|BIT17)  /*                                               */
#define W18  (WAG1|BIT18)  /*                                               */
#define W19  (WAG1|BIT19)  /*                                               */
#define W20  (WAG1|BIT20)  /*                                               */
#define W21  (WAG1|BIT21)  /*                                               */
#define W22  (WAG1|BIT22)  /*                                               */
#define W23  (WAG1|BIT23)  /*                                               */
#define W24  (WAG1|BIT24)  /*                                               */
#define W25  (WAG1|BIT25)  /*                                               */
#define W26  (WAG1|BIT26)  /*                                               */
#define W27  (WAG1|BIT27)  /*                                               */
#define W28  (WAG1|BIT28)  /* RESERVED FOR USE BY ALARM TYPE.               */
#define W29  (WAG1|BIT29)  /* RESERVED FOR USE BY ALARM TYPE.               */
#define W30  (WAG1|BIT30)  /* RESERVED FOR USE BY ALARM TYPE.               */
#define W31  (WAG1|BIT31)  /* RESERVED FOR USE BY ALARM TYPE.               */


/*---  Warnings which will abort the sonics  ---*/

#define WA_SONICS_ABORT  (W2|W5|W6|W7|W9)

#define PRINTER80FULL_RESET   ((~W3) | ALARMTYPEMASK)  

#define RESET_CALIBRATION_WARNINGS   ((~W8) | ALARMTYPEMASK) 


/*--------------------------------------------------------------------------*/
/* The next new group is Process Reject Alarms                              */
/*--------------------------------------------------------------------------*/

#define PR0   (PRG1|BIT0 ) /* RESERVED                                      */
#define PR1   (PRG1|BIT1 ) /* -R Energy Limit                               */
#define PR2   (PRG1|BIT2 ) /* +R Energy Limit                               */
#define PR3   (PRG1|BIT3 ) /* -R Pk Power Limit                             */
#define PR4   (PRG1|BIT4 ) /* +R Pk Power Limit                             */
#define PR5   (PRG1|BIT5 ) /* -R Col Dist Limit                             */
#define PR6   (PRG1|BIT6 ) /* +R Col Dist Limit                             */
#define PR7   (PRG1|BIT7 ) /* -R Abs Dist Limit                             */
#define PR8   (PRG1|BIT8 ) /* +R Abs Dist Limit                             */
#define PR9   (PRG1|BIT9 ) /* -R Trig Dist Limit                            */
#define PR10  (PRG1|BIT10) /* +R Trig Dist Limit                            */
#define PR11  (PRG1|BIT11) /* -R Max Force Limit                            */
#define PR12  (PRG1|BIT12) /* +R Max Force Limit                            */
#define PR13  (PRG1|BIT13) /* -R Time Limit                                 */
#define PR14  (PRG1|BIT14) /* +R Time Limit                                 */
#define PR15  (PRG1|BIT15) /*                                               */
#define PR16  (PRG1|BIT16) /*                                               */
#define PR17  (PRG1|BIT17) /*                                               */
#define PR18  (PRG1|BIT18) /* LL Not Reached                                */
#define PR19  (PRG1|BIT19) /* - SBL Freq Limit                              */
#define PR20  (PRG1|BIT20) /* + SBL Freq Limit                              */
#define PR21  (PRG1|BIT21) /*                                               */
#define PR22  (PRG1|BIT22) /*                                               */
#define PR23  (PRG1|BIT23) /*                                               */
#define PR24  (PRG1|BIT24) /*                                               */
#define PR25  (PRG1|BIT25) /*                                               */
#define PR26  (PRG1|BIT26) /*                                               */
#define PR27  (PRG1|BIT27) /*                                               */
#define PR28  (PRG1|BIT28) /* RESERVED FOR USE BY ALARM TYPE.               */
#define PR29  (PRG1|BIT29) /* RESERVED FOR USE BY ALARM TYPE.               */
#define PR30  (PRG1|BIT30) /* RESERVED FOR USE BY ALARM TYPE.               */
#define PR31  (PRG1|BIT31) /* RESERVED FOR USE BY ALARM TYPE.               */




/*--------------------------------------------------------------------------*/
/* The next new group is Process Suspect Alarms                             */
/*--------------------------------------------------------------------------*/

#define PS0   (PSG1|BIT0 ) /* RESERVED                                      */
#define PS1   (PSG1|BIT1 ) /* -S Energy Limit                               */
#define PS2   (PSG1|BIT2 ) /* +S Energy Limit                               */
#define PS3   (PSG1|BIT3 ) /* -S Pk Power Limit                             */
#define PS4   (PSG1|BIT4 ) /* +S Pk Power Limit                             */
#define PS5   (PSG1|BIT5 ) /* -S Col Dist Limit                             */
#define PS6   (PSG1|BIT6 ) /* +S Col Dist Limit                             */
#define PS7   (PSG1|BIT7 ) /* -S Abs Dist Limit                             */
#define PS8   (PSG1|BIT8 ) /* +S Abs Dist Limit                             */
#define PS9   (PSG1|BIT9 ) /* -S Trig Dist Limit                            */
#define PS10  (PSG1|BIT10) /* +S Trig Dist Limit                            */
#define PS11  (PSG1|BIT11) /* -S Max Force Limit                            */
#define PS12  (PSG1|BIT12) /* +S Max Force Limit                            */
#define PS13  (PSG1|BIT13) /* -S Time Limit                                 */
#define PS14  (PSG1|BIT14) /* +S Time Limit                                 */
#define PS15  (PSG1|BIT15) /*                                               */
#define PS16  (PSG1|BIT16) /*                                               */
#define PS17  (PSG1|BIT17) /*                                               */
#define PS18  (PSG1|BIT18) /*                                               */
#define PS19  (PSG1|BIT19) /*                                               */
#define PS20  (PSG1|BIT20) /*                                               */
#define PS21  (PSG1|BIT21) /*                                               */
#define PS22  (PSG1|BIT22) /*                                               */
#define PS23  (PSG1|BIT23) /*                                               */
#define PS24  (PSG1|BIT24) /*                                               */
#define PS25  (PSG1|BIT25) /*                                               */
#define PS26  (PSG1|BIT26) /*                                               */
#define PS27  (PSG1|BIT27) /*                                               */
#define PS28  (PSG1|BIT28) /* RESERVED FOR USE BY ALARM TYPE.               */
#define PS29  (PSG1|BIT29) /* RESERVED FOR USE BY ALARM TYPE.               */
#define PS30  (PSG1|BIT30) /* RESERVED FOR USE BY ALARM TYPE.               */
#define PS31  (PSG1|BIT31) /* RESERVED FOR USE BY ALARM TYPE.               */
