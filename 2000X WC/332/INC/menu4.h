/* $Header:   D:/databases/VMdb/2000Series/INC/MENU4.H_V   1.24   08 Mar 2011 02:58:20   PDwivedi  $ */
#ifndef _MENU4_H
#define _MENU4_H


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
/****************************************************************************/

/**--------------------------- MODULE DESCRIPTION -------------------------**

   Module name:

   
   Filename: menu4.h
   

   Function Names:   
                     
                     
 

**------------------------------ REVISIONS ---------------------------------------**

   Revision #      Date       Author   Description
   ==========     ========    ======   ===========
   0              10/10/96    PaulG    Initial Version                     
   1.00           10/19/96    PaulG    Added new function PrnMgrONOFFFunc
                                       and PrnMgrAbortFunc.
   1.01           11/04/96    PaulG    Added prototype function ResetPrinterChoice.
   1.02           11/15/96    PaulG    Added prototype function SetPrinterFlags.
   1.03           06/23/96    PaulG    Changed Prototypes for printer types.
   1.04           08/28/96    PaulG    Added Prototypes OfflineCheckFunc.
   1.05           09/15/97    PaulG    Added Prototypes SetMaxWeldsPerPage().
   1.06           09/18/97    PaulG    Added Prototypes to initialize sample value.
   1.07           09/22/97    PaulG    Added Printer status variables
   1.08           10/15/97    PaulG    Added function prototype SetPageSizeFunc();
   1.12           10/21/97    PaulG    Added PoweredOffCheckFunc() and MASKPRINT.
   1.13           12/02/97     KGD     Added GetPrinterInfo();
   1.14           03/06/98    PaulG    Added OUTOFPAPER to printer status.
   1.15           05/18/98    PaulG    Added AbsDistanceGraphFunc();
   1.16           08/27/98    PaulG    Added defines for max and min values from x-axis scale.
   1.17           10-01-99    JZ       added arguments to DisplayPrintMess()
   1.19           03-21-00    JLH      Removed EnabledPrinterIBMPro function prototype.
   1.20           05-25-00    JLH      Added EnabledPrinterOKI520 function prototype.
   1.21           01-08-01    BEKymer  Added argument to functions called from TEXT
                                        or SUBMENU structures
   1.22           10-22-07    NHAhmed  Changes done for LangTest phase 0
   1.23           09-04-08	  ygupta   Cleanup for Multilanguage project.
   1.24           03-08-11	  PDwivedi Added new function USBFullCheckFunc.

**---------------------------------------------------------------------------------**/


/* Printer Status */
#define POWEROFF       0x0f
#define PRINTBUSY      0x0d
#define PRINTONLINE    0x05
#define OUTOFPAPER     0x0A
#define MASKPRINT      0X0f

/*-- Max and min values for x-axis scale --*/
#define XSCALEMINVALUE   400
#define XSCALEMAXVALUE   60100

/**--------------------------------- DESCRIPTION ---------------------------**/


/**------------------------------ LOCAL FUNCTIONS -------------------------**/

UINT16 CheckPrintingStatus(void);
void SamplePresetFunc(void);
void AlarmPresetFunc(void);
void SampleHistoryFunc(void);
void AlarmeHistoryFunc(void);
void SampleSummaryFunc(void);
void AlarmSummaryFunc(void);
void SamplePowerFunc(void);
void AlarmPowerFunc(void);
void SampleAmplitudeFunc(void);
void AlarmAmplitudeFunc(void);
void SampleFrequencyFunc(void);
void AlarmFrequencyFunc(void);
void SampleDistanceFunc(void);
void AlarmDistanceFunc(void);
void SampleVelocityFunc(void);
void AlarmVelocityFunc(void);
void SampleForceFunc(void);
void AlarmForceFunc(void);
void DisplayPrintMess(SINT8 *String1, SINT8 *String2);
void GlobalSwitch1Func(void);
void GlobalSwitch2Func(void);
void PrintPresetFunc(UINT32);
void WeldHistoryFunc(UINT32);
void PowerGraphFunc(UINT32);
void AmpGraphFunc(UINT32);
void FreqGraphFunc(UINT32);
void ColDistanceGraphFunc(UINT32);
void AbsDistanceGraphFunc(UINT32);
void VelocityGraphFunc(UINT32);
void ForceGraphFunc(UINT32);
void AbortCurPrintFunc(void);
void GetPrinterChoice(void);
void EnabledPrinterOKI520(void);
void EnabledPrinterEpson(void);
void EnabledPrinterHPPCL(void);
void PrnMgrONOFFFunc(void);
void PrnMgrAbortFunc(void);
void ResetPrinterChoice(void);
void SetPrinterFlags(void);
UINT16 OfflineCheckFunc(void);
UINT16 USBFullCheckFunc(void);
void PrintNowOfflineCheck(void);
void SetMaxWeldsPerPage(void);
void InitSetupPresetValue(void);
void InitWeldHistoryValue(void);
void InitWeldSummaryValue(void);
void InitPowerGraphValue(void);
void InitAmpGraphValue(void);
void InitFreqGraphValue(void);
void InitColDistGraphValue(void);
void InitAbsDistGraphValue(void);
void InitVelGraphValue(void);
void InitForceGraphValue(void);
void GetPageSize(void);
UINT16 PoweredOffCheckFunc(void);


#endif

