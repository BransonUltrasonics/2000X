/* $Header:   D:/databases/VMdb/2000Series/App/BATTRAM.C_V   2.77.1.0.1.5   16 Jul 2013 11:37:58   hasanchez  $ */
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
------------------------------ MODULE DESCRIPTION -----------------------------

   Module name: 

   Filename:       battram.c

   Function name:  BattramAccess

 
   Written by:     Mark Lazarewicz
   Date:           12/04/95
   Language:       Microtec "C"

------------------------------ REVISIONS --------------------------------------

   Revision #     Date        Author   Description
   ----------     -------     ------   -----------
    0             12/4/95     Mark L   Initial   
    1             01/26/96    Mark L   Add Crc
    2             01/30/96    Mark L   Add sram_log and support code
    3             03/14/96    Mark L   Added System Data Section
    4             04/08/96    Mark L   Added Weld Data Section
    5             04/11/96    Mark L   Increased Weld Data to 3K
    6             04/17/96    Mark L   Parameter Manager Data Storage
    7             04/29/96    LAM      Added checkbattramdefaults    
    8             05/22/96    LAM      Added Initdigpot    
    9             06/11/96    PhilJ    Added swaredat.h to include
                                       files
    10            06/17/96    LAM      chged battram size & start

                                       added 256bytes for PSOS
                                       deleted battraminit
    11            09/26/96    PhilJ    Moved Weld data definitions
                                       to battram.h.
    12            12/23/96    PhilJ    Saved WeldHistoryPtr to
                                       CurrentSetup.
    13            01/16/97    PhilJ    Battram is now cleared if
                                       not previously initialized.
    14            02/05/97    PaulG    Added flag to powerdown                                                    
    15            02/10/97    PaulG    Added flags SetupDone and PresetDone.                                                    
    16            02/28/97    PhilJ    Modified CheckBattramDefaults.
    17            03/03/97    PhilJ    Added call to StartRTClock in
                                       CheckBattramDefaults.
    18            03/05/97    PhilJ    Added init RTclock to
                                       CheckBattramDefaults.
    19            03/24/97    PhilJ    Initialize WeldHistoryPtr in
                                       CheckBattramDefaults.
    20            03/31/97    PhilJ    Changed InitBattramAddress
    21            04/08/97    PhilJ    Added language,units, and password
                                       defaults to CheckBattramDefaults.
    22.2.21       06/17/97    LAM      deleted unused .h
    22.2.22       06/19/97    PhilJ    Changed Language from to enum.
    22.2.23       07-16-97    BEKymer  Add EQ8 to CheckBattramDefaults
    2.24          08-29-97    LAM      deleted power down check       
    2.25          09-11-97    PaulG    Unit test and data cleanup
    2.26          09-24-97    LAM      moved updated historyptr to sysmanger
    2.27          10-07-97    PaulG    Updated WeldHistoryPtr to point at
                                       end of weld data when cycle complete.
    2.28          01-25-98    LAM      commented out CRC check and managerr 
    2.29          06-03-98    BJB      Sets defaults for digital pot if
                                        BBRAM is corrupted.
    2.30          06-18-98    BJB      Code to initialize BBRAM doesn't need
                                        to center digpot, this now in
                                        SetDefaultValues().
                                       Cleaned out some commented-out code.
    2.31          06.24.98    JBerman  Added: ActRecovery();
    2.32          07/30/98    BJB      Modified CheckBattramDefaults() to
                                        correctly re-init BBRAM.  Also, 
                                        doesn't record alarm because this
                                        facility not available when routine
                                        is called.
    2.33          07/30/98    BJB      Sets up more defaults when restoring
                                       BBRAM.
    2.34          12/16/99    LAM      removed error handling code 
    2.35          01/05/00    LAM      removed unused syslog or error log writes         
    2.36          05/26/00    JLH      Changed LaserJet to HPPCL.  Added OKI520 printer type.  
    2.37          07-05-00    BEKymer  Add test to detect for auto conversion from old
                                       software version to the latest.
                                       took away BBR800_CONFIG  in switch SecID.
                                       Rewrote method to access to BBR
    2.38         08-08-00     SCM      Added temporary structure for DUPS parameters and then moved the structure
                                       to menu3.c.                                                    
    2.39         08-08-00     BEKYmer  Restore dups related stuff from BBR at configuration
                                       Remove commented out code                                                        
    2.40         09-09-00     BEKymer  Added DEPOT_FLAGS structure in BBR
    2.41         08-23-00     BEKymer  Include string.h for memcpy prototype
    2.42         08-28-00     BEKymer  In CheckBattramDefaults move BUC menu stuff
                                        from BBR to working RAM
    2.43         08-29-00     JLH      Implement Depot level stuff.
    2.44         08-29-00     AT       Removed extern DUPS2COP..., added sizeof()
    2.45         08-31-00     BEKymer  In CheckBattramDefaults() if no valid
                                        control level then assume BBR is not
                                        initialized and RTC needs to be started.
    2.46         09-01-00     LAM      added a break after new control levels
    2.47         09-07-00     JLH      Set CurrentSetup.SendWeldData to TRUE.  This will send weld
                                        data to host by default.
    2.48         09-18-00     BEKymer  Fix code so a corrupted BBR is corrected correctly by
                                        adding FixBattRam() function
    2.49         10-04-00     BEKymer  Add include files to eliminate compiler warnings
    2.50         10-04-00     AT       Changed DUPS_DownloadCurrPS to DUPS_QueuedDownloadPS
    2.51         10-18-00     BEKymer  Added second arg to SaveCompressedPreset call
                                        Fix for issue # 3387
    2.52         10-20-00     AT       Commented out Convert600to800 and Convert702to800
    2.53         08-03-01     BEKymer  Initialized CurrentSetup.SerialPort to COMPUWELD
    2.52.1.1     08-21-01     BEKymer  Detab    
    2.25.1.2     09-20-01     LAM      moved setting serialport to COMPUWELD in CheckCBattramDefaults                                              
                                       to FixBattRam
    2.25.1.3     04-25-02     LAM      Copy history pointer directly to the Battram every cycle.
    2.25.1.4     04-25-02     BEKymer  Default extra cooling on when wattage is greater than 3300
    2.55         04-30-03     BEKymer  Move 2.52.1.4 back to tip for 8.10 build
                                       Add VelocityReporting where needed
    2.56         08-06-03     JOY      Touch Screen Calibration points(1,2) are set to the
                                       default value in 'FixBattRam()'. 
    2.57         09-01-03     JOY      Added Weld Param OPtion Deaults in 'CurrentSetup' struct.
    2.58         10-31-03     JOY      Cleared the QVGA image save Flag to save the image fresh.
    2.59         02-23-04     BEKymer  Add AmpDecayPercent in saving BUC menu stuff
    2.60         05-07-04     LAM      merged with 8.22
    2.61         05-12-04     VSharma  Added default values for EnergyBraking and AmpDecay in FixBattRam.
    2.62         05-17-04     VSharma  Added code to save ColdStart Preset in FixBattRam().
    2.63         07-07-04     BEKymer  Add call to DoColdStart in FixBattRam()
    2.64         07-08-04     BEKymer  Removed call to DOColdStart in FixBattRam()
                                        It turns out if FixBattRam is called from
                                        root.c, the psos tasks are not running yet
                                        so DoColdSTart locks up waiting for tasks
                                        to complete.  Besides, we don't remember
                                        why we thought we needed a cold start anyway!
    2.65         09-07-04     BEKymer   Use PSNvRamData.PSWatts instead of
                                         CurrentSetup.PSWatts in FixBattRam.  When
                                         this is called at power up Currentsetup.PSWatt
                                         doesn't have any valid data yet.
    2.66         07-25-05     Bwadia     Modified fixBattRam for Auto Refresh feature on graph
    2.67         08-25-05     Aare       Added initialization for metric decimals, default is 2.                 
    2.68         08-26-05     Aare       Added initialization for encoder reset, default is SS.
    2.69         09-10-05     Aare       Initialize SBL defaults.
    2.70         10-24-05     Bwadia     Dummy Check in  
    2.71         10-28-05     Bwadia     Sequencing related variables initialized in fixbattram
    2.72         11-22-05     Bwadia     VGA HW present flag initialized in FixBattRam()
    2.73         01-03-06     Bwadia     InitSBL() function removed from FixBattRam()
                                         Modified for tracker issue 3980
    2.74         04-13-06     Bwadia     CurrentSetup.USEncoder set to FALSE 
    2.75         01-18-07     NHAhmed    Added VGAHWPresent flag in FixBattRam() after SetDefaultValues().  
    2.76         01-18-07     NHAhmed    Commented out CurrentSetup.VGAHWPresent = FALSE in FixBattRam().
    2.77         04-16-07     NHAhmed    Added CurrentSetup.SBLEnable = TRUE in FixBattRam().
    2.77.1.0     11-19-07     LAM        Merged 9.07 changes                      
    2.77.1.1     01-11-08     NHAhmed    Some functions are replicated to a none argument type, 
                                         keeping all functionality same.
    2.77.1.2     10-01-08     NHAhmed    Merged Ver10.40 changes. 
    2.77.1.0.1.2 09-10-09     BEkymer    Add new define MICRO where needed
    2.77.1.0.1.3 09-28-09     BEkymer    Add MicroHomeForce to BUCMENU_800 structure
    2.77.1.0.1.4 10-20-09     BEkymer    Add encoder selection to FixBattRam()
    2.77.1.0.1.5 06-26-13     HSanchezZ  Updated FixBattRam() to enforce the Update on BBR. 
    

    
     -------------------------- DESCRIPTIONS ------------------------------------

   This function reads 1 or more bytes of data from BATRAM to SRAM and 
           also writes 1 or more bytes of data from SRAM to BATRAM.

----------------------------- PSUEDOCODE --------------------------------------

---------------------------- INCLUDE FILES ------------------------------------*/

/* System include files */
#include   "portable.h"

/* Function include files */
#include   "comm_crc.h"
#include   "spidd.h"
#include   "weld_obj.h"
#include   "battram.h"
#include   "rtclock.h"
#include   "menu7a.h"
#include   "ready.h"
#include   "alarms.h"
#include   "actnvram.h"
#include   "psnvram.h"
#include   "dups_api.h"
#include   "string.h"
#include   "menu.h"
#include   "preset.h"
#include   "param.h"
#include   "snsrcalb.h"
#include   "selctkey.h"
#include   "menu7.h"
#include   "menu1.h"
#include   "alsetup.h"
#include   "screenmsg_touch.h"
#include   "sysmangr.h"

/*
---------------------------- LOCAL DEFINES  -----------------------------------
*/   


/* ---------------------LOCAL TYPE DECLARATIONS ------------------------- */


/* ----------------------- PRIVATE GLOBAL DATA -------------------------- */
static UINT16                 *BattramStartAddr;
BUCMENU_800  *BUCMenuBBR;
extern ALARM_MASKS AlarmPtrRam;
extern ALARM_MASKS *AlarmPtrBBR;
extern BUCMENU_800 BUCMenuRAM;
//extern const SCRN_CALIB_CORDINATE ActualCalibPts;

DEPOT_FLAGS  *DepotFlag = (DEPOT_FLAGS *) BBR800_DEPOT_START;

WELD_DATA* WeldDataAddress[NMBR_OF_WELD_HISTORY] = {
										(WELD_DATA*) WELD_DATA_0_START,
										(WELD_DATA*) WELD_DATA_1_START,
										(WELD_DATA*) WELD_DATA_2_START,
										(WELD_DATA*) WELD_DATA_3_START,
										(WELD_DATA*) WELD_DATA_4_START,
										(WELD_DATA*) WELD_DATA_5_START,
										(WELD_DATA*) WELD_DATA_6_START,
										(WELD_DATA*) WELD_DATA_7_START,
										(WELD_DATA*) WELD_DATA_8_START,
										(WELD_DATA*) WELD_DATA_9_START,
										(WELD_DATA*) WELD_DATA_10_START,
										(WELD_DATA*) WELD_DATA_11_START,
										(WELD_DATA*) WELD_DATA_12_START,
										(WELD_DATA*) WELD_DATA_13_START,
										(WELD_DATA*) WELD_DATA_14_START,
										(WELD_DATA*) WELD_DATA_15_START,
										(WELD_DATA*) WELD_DATA_16_START,
										(WELD_DATA*) WELD_DATA_17_START,
										(WELD_DATA*) WELD_DATA_18_START,
										(WELD_DATA*) WELD_DATA_19_START,
										(WELD_DATA*) WELD_DATA_20_START,
										(WELD_DATA*) WELD_DATA_21_START,
										(WELD_DATA*) WELD_DATA_22_START,
										(WELD_DATA*) WELD_DATA_23_START,
										(WELD_DATA*) WELD_DATA_24_START,
										(WELD_DATA*) WELD_DATA_25_START,
										(WELD_DATA*) WELD_DATA_26_START,
										(WELD_DATA*) WELD_DATA_27_START,
										(WELD_DATA*) WELD_DATA_28_START,
										(WELD_DATA*) WELD_DATA_29_START,
										(WELD_DATA*) WELD_DATA_30_START,
										(WELD_DATA*) WELD_DATA_31_START,
										(WELD_DATA*) WELD_DATA_32_START,
										(WELD_DATA*) WELD_DATA_33_START,
										(WELD_DATA*) WELD_DATA_34_START,
										(WELD_DATA*) WELD_DATA_35_START,
										(WELD_DATA*) WELD_DATA_36_START,
										(WELD_DATA*) WELD_DATA_37_START,
										(WELD_DATA*) WELD_DATA_38_START,
										(WELD_DATA*) WELD_DATA_39_START,
										(WELD_DATA*) WELD_DATA_40_START,
										(WELD_DATA*) WELD_DATA_41_START,
										(WELD_DATA*) WELD_DATA_42_START,
										(WELD_DATA*) WELD_DATA_43_START,
										(WELD_DATA*) WELD_DATA_44_START,
										(WELD_DATA*) WELD_DATA_45_START,
										(WELD_DATA*) WELD_DATA_46_START,
										(WELD_DATA*) WELD_DATA_47_START,
										(WELD_DATA*) WELD_DATA_48_START,
										(WELD_DATA*) WELD_DATA_49_START
									  };

UINT32 WeldDataAddressList[NMBR_OF_WELD_HISTORY] = {
										WELD_DATA_0_START,
										WELD_DATA_1_START,
										WELD_DATA_2_START,
										WELD_DATA_3_START,
										WELD_DATA_4_START,
										WELD_DATA_5_START,
										WELD_DATA_6_START,
										WELD_DATA_7_START,
										WELD_DATA_8_START,
										WELD_DATA_9_START,
										WELD_DATA_10_START,
										WELD_DATA_11_START,
										WELD_DATA_12_START,
										WELD_DATA_13_START,
										WELD_DATA_14_START,
										WELD_DATA_15_START,
										WELD_DATA_16_START,
										WELD_DATA_17_START,
										WELD_DATA_18_START,
										WELD_DATA_19_START,
										WELD_DATA_20_START,
										WELD_DATA_21_START,
										WELD_DATA_22_START,
										WELD_DATA_23_START,
										WELD_DATA_24_START,
										WELD_DATA_25_START,
										WELD_DATA_26_START,
										WELD_DATA_27_START,
										WELD_DATA_28_START,
										WELD_DATA_29_START,
										WELD_DATA_30_START,
										WELD_DATA_31_START,
										WELD_DATA_32_START,
										WELD_DATA_33_START,
										WELD_DATA_34_START,
										WELD_DATA_35_START,
										WELD_DATA_36_START,
										WELD_DATA_37_START,
										WELD_DATA_38_START,
										WELD_DATA_39_START,
										WELD_DATA_40_START,
										WELD_DATA_41_START,
										WELD_DATA_42_START,
										WELD_DATA_43_START,
										WELD_DATA_44_START,
										WELD_DATA_45_START,
										WELD_DATA_46_START,
										WELD_DATA_47_START,
										WELD_DATA_48_START,
										WELD_DATA_49_START
									  };


/*--------------------------- EXTERNAL DATA ----------------------------- */
extern CONFIGSETUP CurrentSetup;
extern SETUPS_Ver800 CurrentPreset;
extern PSNOVRAMDATA PSNvRamData;
extern WELD_DATA WeldingResults;
extern UINT8     AlarmDetectedFlag;
extern UINT16    PresetHasBeenOKed;
extern UINT32    PresetAddress[];
extern UINT16 DisplayRefreshButton;
extern SETUPS_Ver800   MinLimit;
extern SETUPS_Ver800   MaxLimit;


/*------------------------------- CODE -----------------------------------*/

BBR_STATUS_TYPE  BattramAccess( 
                               BBR_ACCESS_TYPE  Request,     
                               BBR_SECTION_TYPE SecID,   
                               UINT8            *DataPointer,
                               UINT32           Offset,     
                               UINT16           ByteCount   )  
{ /* Start of function */

   UINT8            *BBRPointer;         /* points to BATTRAM data location for read or write */
   BBR_STATUS_TYPE   CompletionStatus = BBR_STATUS_OK;
   CONFIGSETUP  *SetupPtr;

   SetupPtr = (CONFIGSETUP *) BBR800_CONFIG_START;

 
   if (ByteCount == 0)               /* Check for zero byte count */
      CompletionStatus = BBR_STATUS_BAD_ARG;
   else {
      switch (SecID) { 
         case SYSTEM_SECTION:
         case PRESET_SECTION:
         case CONFIG_SECTION:
            BBRPointer = (UINT8 *) Offset;
            break;

         case HORN_SECTION:
            BBRPointer = (UINT8 *) (BBR800_HORNGRAPH_START + Offset);
            break;

         case HISTORY_SECTION:
            BBRPointer = (UINT8 *) (BBR800_HISTORY_START + Offset);
            break;

         case NOTASSIGNED_SECTION:
            BBRPointer = (UINT8 *) (BBR800_NOTASSIGNED_START + Offset);
            break;

         default:
            CompletionStatus = BBR_STATUS_BAD_ARG;
      }
   }

   if (CompletionStatus == BBR_STATUS_OK) {
      switch (Request) {
         case BBR_READ:
            while (ByteCount > 0) {
               *DataPointer = *BBRPointer;
               BBRPointer++;
               DataPointer++;
               ByteCount--;
            }
            break;
         case BBR_WRITE:
            while (ByteCount > 0) {
               *BBRPointer = *DataPointer;
               BBRPointer++;
               DataPointer++;
               ByteCount--;
            }
            if (SecID == HISTORY_SECTION){
                CurrentSetup.WeldHistoryPtr = (UINT32) BBRPointer;
                SetupPtr->WeldHistoryPtr = (UINT32) BBRPointer;
            }    
            break;
         default:
             CompletionStatus = BBR_STATUS_BAD_ARG;
      }
   }
   return(CompletionStatus);
}



void ClearOutBattRam(void)
/* -------------------------------- DESCRIPTION ----------------------------------- */
/*                                                                                  */
/*  This function clears out all of battery backed ram starting from BBR800_START_  */
/*  ADDRESS and going for BBR800_SIZE bytes.                                        */
/*                                                                                  */
/*----------------------------------------------------------------------------------*/  
{
   UINT8  *BattramPtr;      /* points to BATTRAM data location for write */
   UINT16 ByteCount;

   BattramPtr = (UINT8 *) BBR800_START_ADDRESS;

   for(ByteCount = 0; ByteCount < BBR800_SIZE; ByteCount++)
      *BattramPtr++ = 0;
}



BOOLEAN CheckBattramDefaults(void)
/* -------------------------------- DESCRIPTION -----------------------------------*/
/*                                                                                 */
/* This function checks to see if the battram contains the default settings.  If   */
/* it does not, then the BBR is cleared and everything is initialized, including   */
/* the real time clock and values not affected by cold start.  Then the min/max    */
/* values are set as well as cold start values.                                    */
/*                                                                                 */
/*---------------------------------------------------------------------------------*/
{
   BOOLEAN  RetVal = TRUE;       /* Returns TRUE if BBRAM is okay */

   /* check to see if the battram has default values and digpot is centered   */
  
/* Here the first thing to do is check for old versions to determine if a conversion is needed */

   switch (PSNvRamData.ControlLevel) {
      case MODEL1:
         PSNvRamData.ControlLevel = LEVEL_t;         /* Old version MODEL 1 found, convert to new version */
         break;
      case MODEL2:
         PSNvRamData.ControlLevel = LEVEL_e;         /* Old version MODEL 2 found, convert to new version */
         break;
      case MODEL3:
         PSNvRamData.ControlLevel = LEVEL_ea;        /* Old version MODEL 3 found, convert to new version */
         break;
      case MODEL4:
         PSNvRamData.ControlLevel = LEVEL_d;         /* Old version MODEL 4 found, convert to new version */
         break;
      case MODEL5:
         PSNvRamData.ControlLevel = LEVEL_f;         /* Old version MODEL 5 found, convert to new version */
         break;
      case LEVEL_t:
      case LEVEL_e:
      case LEVEL_ea:
      case LEVEL_a:
      case LEVEL_d:
      case LEVEL_f:
      case LEVEL_TEST:
         break;
      default:                    /* Assume if no valid control level, BBR is also bad */
         ClearOutBattRam();
         FixBattRam();
         InitRtclock();
         StartRtclock();
         break;
   }
/* Here copy the BUC Menu stuff into working ram structure */
   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   BUCMenuRAM.EnergyBrakingAmp = BUCMenuBBR->EnergyBrakingAmp; 
   BUCMenuRAM.EnergyBrakingTime = BUCMenuBBR->EnergyBrakingTime; 
   BUCMenuRAM.ExtSwLogicBUC = BUCMenuBBR->ExtSwLogicBUC; 
   BUCMenuRAM.ForcePC = BUCMenuBBR->ForcePC; 
   BUCMenuRAM.GndDetLogicBUC = BUCMenuBBR->GndDetLogicBUC; 
   BUCMenuRAM.ULSLogicBUC = BUCMenuBBR->ULSLogicBUC; 
   BUCMenuRAM.VelocityPC = BUCMenuBBR->VelocityPC; 
   BUCMenuRAM.VelocityReporting = BUCMenuBBR->VelocityReporting; 
   BUCMenuRAM.AmpDecayPercent = BUCMenuBBR->AmpDecayPercent;
   BUCMenuRAM.RecalCode300 = BUCMenuBBR->RecalCode300;  
   BUCMenuRAM.MicroHomeForce = BUCMenuBBR->MicroHomeForce;  

/* Here copy BBR BUC menu stuff into working ram structure */
   AlarmPtrBBR = (ALARM_MASKS *)BBR800_ALARM_START;

   AlarmPtrRam.SetupGroup1 = AlarmPtrBBR->SetupGroup1;
   AlarmPtrRam.SetupGroup2 = AlarmPtrBBR->SetupGroup2;
   AlarmPtrRam.SetupGroup3 = AlarmPtrBBR->SetupGroup3;
   AlarmPtrRam.SetupGroup4 = AlarmPtrBBR->SetupGroup4;
   AlarmPtrRam.SetupGroup5 = AlarmPtrBBR->SetupGroup5;
   AlarmPtrRam.SetupGroup6 = AlarmPtrBBR->SetupGroup6;
   AlarmPtrRam.SetupGroup7 = AlarmPtrBBR->SetupGroup7;
   AlarmPtrRam.SetupGroup8 = AlarmPtrBBR->SetupGroup8;
   AlarmPtrRam.SetupGroup9 = AlarmPtrBBR->SetupGroup9;
   AlarmPtrRam.SetupGroup10 = AlarmPtrBBR->SetupGroup10;
   AlarmPtrRam.Overload = AlarmPtrBBR->Overload;
   AlarmPtrRam.NoCycle = AlarmPtrBBR->NoCycle;
   AlarmPtrRam.EquipmentFailure = AlarmPtrBBR->EquipmentFailure;
   AlarmPtrRam.CycleModified = AlarmPtrBBR->CycleModified;
   AlarmPtrRam.Reject = AlarmPtrBBR->Reject;
   AlarmPtrRam.Suspect = AlarmPtrBBR->Suspect;
   AlarmPtrRam.Warning = AlarmPtrBBR->Warning;

/* Now copy the stuff for the DUPS from BBR into working ram */

   memcpy(DUPS2COP, (UINT8*)BBR800_DUPS2COP_START, sizeof(DUPS2COP));
   memcpy(COP2DUPS, (UINT8*)BBR800_COP2DUPS_START, sizeof(COP2DUPS));
   memcpy(DUPS_Lock, (UINT16*)BBR800_DUPSLOCK_START, sizeof(DUPS_Lock));

/* Now check for DEPOT level */

   if(DepotFlag->IsADepot)
   {
      UpdateSWConfiguration(DEPO, TRUE);
      DepotLevel = TRUE;
   }
   else
   {
      UpdateSWConfiguration(DEPO, FALSE);
      DepotLevel = FALSE;
   }

   return( RetVal );
}



void FixBattRam(void)
/****************************************************************************/ 
/*                                                                          */
/* This function sets up the factory defaults in the event the battram is   */
/* corrupted or not initialized.  This will be similiar to ColdStartPlus()  */
/* except it will be assumed the novram is okay.  This means calibration    */
/* stuff won't be done.                                                     */
/*                                                                          */
/****************************************************************************/ 
{
   UINT16 x;

   InitSetupFromAct();    /* Make sure CurrentSetup.Actuator is correct for next step */
   switch (CurrentSetup.Actuator) {
      case AED:
      case AEF:
         BuildVelocityTable();
         EnableMetricEncoder();
         break;
      case MICRO:
         BuildVelocityTable();
         EnableUSEncoder();
         break;
      default:
         break;
   }

/* Now setup some systemconfiguration stuff */

   CurrentSetup.SBLEnable       = TRUE;
   CurrentSetup.PageSize        = PAGESIZE11;
   CurrentSetup.PrinterOKI520   = TRUE;     // Printer Type
   CurrentSetup.PrinterEpson    = FALSE;
   CurrentSetup.PrinterHPPCL    = FALSE;
   CurrentSetup.Units           = FALSE;
   CurrentSetup.Metric3Flag     = FALSE;   // default to 2 decimals as before
   CurrentSetup.DistanceULS     = FALSE;   // default reset encoder on start switches
   CurrentSetup.PassWordFlag    = FALSE;
   CurrentSetup.Language        = ENGLISH;
   CurrentSetup.WeldsPerPage    = 59;
   CurrentSetup.WeldHistoryPtr  = BBR800_HISTORY_START;
   CurrentSetup.BaudRate        = BAUD_9600;
   CurrentSetup.ExtPresets      = FALSE;
   CurrentSetup.HandHeld        = FALSE;
   CurrentSetup.GainFactor = GAIN_FACTOR_DEFAULT;
    /*Set Default Weld Param Options for QVGA */
   CurrentSetup.WeldParamOption[0] = RCYCLECOUNT;
   CurrentSetup.WeldParamOption[1] = RTIME;
   CurrentSetup.WeldParamOption[2] = RPKPWR;
   PSNvRamData.ControlLevel = CurrentSetup.ControlLevel;
   if(PSNvRamData.ControlLevel >= LEVEL_ea)
      CurrentSetup.WeldParamOption[3] = RENERGY;
   else
      CurrentSetup.WeldParamOption[3] = RAMPSTART;
   if(PSNvRamData.ControlLevel >= LEVEL_d)
      CurrentSetup.WeldParamOption[4] = RTCOLDIST;
   else
      CurrentSetup.WeldParamOption[4] = RFREQEND;   /*Set Default Weld Param Options for QVGA */
   CurrentSetup.QVGAImgSaved = 0;
   
   if (DUPS_Info.DUPSFlag == FALSE)          /* Let DUPS power up sequence decide if */
      CurrentSetup.PSType = FALSE;           /* system should be configured with or  */
   else                                      /* without a DUPS.                      */
      CurrentSetup.PSType = TRUE;

   CurrentSetup.SerialPort = COMPUWELD;
   CurrentSetup.SequenceEnable = FALSE;      /*Sequencing Disabled */
   CurrentSetup.SequenceCount = 0;           /*Sequenclist count made zero */
   CurrentSetup.SequenceNos = 0;             /*Current Sequence nos made zero */
   CurrentSetup.AutoRefresh = FALSE;
   CurrentSetup.StartScreen     = FALSE;     /*Default to Main Menu           */
   CurrentSetup.Sclk7890Act = SLOWSPEED;     /* Actuator A/D SCK  */
   CurrentSetup.ClockPhase = INVERTCLK;      /* need to invert signal when using slow speed*/
   CurrentSetup.PSLifetime = 0;

   StorePSLifeTimeCount();

   DisplayRefreshButton = TRUE;

//   DoColdStart();
   strcpy(MinLimit.PresetID, "DEFAULT");  /*     it will allow restore the values as a factory*/
   strcpy(MaxLimit.PresetID, "DEFAULT");  /*     it will allow restore the values as a factory*/
   strcpy(CurrentPreset.PresetID, "COLD START");  /*     it will allow restore the values as a factory*/
   SaveCompressedPreset( (PRESET_COMPRESSED *) PRESET_CLDSTRT_START, &CurrentPreset);
   
   SetMaxMinValues();

   SetDefaultValues();
   CurrentSetup.VGAHWPresent = FALSE;
   GetAlarmMask();
   SetAmpControl();
   SetFreqControl();
   if (ClearAlarm(WeldingResults.EquipmentFailureAlarms) == TRUE) {
      ClearFinalResults();
      ClearWeldData();
      AlarmDetectedFlag = FALSE;
      AlarmOff();           // Turn Reset led off 
   }
   ClearSetupAlarms();

   CurrentPreset.SetRTComp = RT_COMP_DEFAULT;           /* in percents */
   CurrentPreset.RTRamp = RATE_SLOW;            
   CurrentPreset.ReturnRamp = RATE_SLOWEST; 
   CurrentPreset.StartRamp = RATE_SLOW;
   UpdateCylDefaults();
   if(PSNvRamData.PSWatts > 3300)
      CurrentSetup.ExtraCooling = TRUE;
   else
      CurrentSetup.ExtraCooling = FALSE;
   BUCMenuRAM.VelocityPC = VELOCITY_PC_DEFAULT;
   BUCMenuBBR->VelocityPC = VELOCITY_PC_DEFAULT;
   BUCMenuRAM.VelocityReporting = FALSE;             /* Default velocity reporting to off */
   BUCMenuBBR->VelocityReporting = FALSE;
   BUCMenuRAM.RecalCode300 = TRUE;                   /* Default recal code 300 reporting to on */
   BUCMenuBBR->RecalCode300 = TRUE;
   /* Default values for EnergyBraking and AmpDecay.*/
   BUCMenuRAM.AmpDecayPercent = AMP_DECAY_PERCENT_DEFAULT;  
   BUCMenuRAM.EnergyBrakingTime = ENERGY_BRAKE_TIME_DEFAULT;
   BUCMenuRAM.EnergyBrakingAmp = ENERGY_BRAKE_AMP_DEFAULT;
   BUCMenuBBR->EnergyBrakingTime = ENERGY_BRAKE_TIME_DEFAULT;
   BUCMenuBBR->EnergyBrakingAmp = ENERGY_BRAKE_AMP_DEFAULT;
   BUCMenuBBR->AmpDecayPercent = AMP_DECAY_PERCENT_DEFAULT;
   BUCMenuBBR->MicroHomeForce = LEAVINGHOMEFORCEMICROLO;
   CurrentSetup.Overload = 0;
   CurrentSetup.GenAlarmCount = 0;
   CurrentSetup.BBRInitialized = BBRAM_INIT;
   UpdateCurrentPreset(SAVEPRESETZERO, 0, 0);   // Updates Running Preset 
   
   CurrentSetup.IdleSpeed = IDLE_SPEED_DEFAULT;
   BackupCurrentSetupChange();
   CurrentPreset.PresetUpdateComplete = TRUE;
   CurrentPreset.PresetID[0] = 0;       /* Ensure the preset names are blank */
   PresetHasBeenOKed = FALSE;           /* Ensure preset stored as not verified.   */ 
                                        /* Otherwise changing actuators will cause */
                                        /* every preset at power up to generate an */
                                        /* Invalid Preset alarm.                   */
   for (x=0; x<=MAX_PRESETS; x++) {
      SaveCompressedPreset( (PRESET_COMPRESSED *) PresetAddress[x], &CurrentPreset);
   }
/* Initialize the DUPS arrays */
   for (x=0; x<DUPS_NUMPARAMSET; x++) {
      DUPS2COP[x] = DUPS_PARAMSETUNDEF;
      DUPS_Lock[x] = DUPS_PARAMSETAVAIL;
   }
   for (x=0; x<=MAX_PRESETS; x++) {
      COP2DUPS[x] = DUPS_PARAMSETUNDEF;
   }
   DUPS_Lock[0] = DUPS_PARAMSETLOCKED;   /* Make Parameter Set 0 Locked all the time  */
   DUPS_Lock[DUPS_CURRPARAMSET] = DUPS_PARAMSETSAVED;   /* by convention this is reserved */
   COP2DUPS[0] = DUPS_CURRPARAMSET;      /* COP Current Preset permanently associated with */
   DUPS2COP[DUPS_CURRPARAMSET] = 0;      /* DUPS Current Parameter Set */
   memcpy((UINT8*)BBR800_DUPS2COP_START, DUPS2COP, sizeof(DUPS2COP));  /* Force all arrays into BBR */
   memcpy((UINT8*)BBR800_COP2DUPS_START, COP2DUPS, sizeof(COP2DUPS));  /* just in case a proper     */
   memcpy((UINT16*)BBR800_DUPSLOCK_START, DUPS_Lock, sizeof(DUPS_Lock));/* power down is never done. */
   /* Set Default Touch Screen Calib. points */
   /*memcpy((SINT16*)BBR800_QVGASCRNCLAIB_START, (SINT16 *)&ActualCalibPts,
              sizeof(SCRN_CALIB_CORDINATE));*/

   DUPS_Info.WeldStatusFlag = TRUE;     /* Initialize weld status flag*/
   if (DUPS_Info.DUPSFlag)               /* if DUPS Communications established */
   {
      DUPS_UploadParamSet(0);            /* Upload factory default parameter set */
      DUPS_Wait4CurrPS();
      DUPS_QueuedDownloadPS();             /* setup default current parameter set */
      DUPS_Wait4CurrPS();
    }
    /* Save the ColdStart Preset. */
    strcpy(CurrentPreset.PresetID, "COLD START");        /* Name it              */
    SaveCompressedPreset( (PRESET_COMPRESSED *) PRESET_CLDSTRT_START, &CurrentPreset);
    CurrentPreset.PresetID[0] = 0;
    //InitSBL();
}



/* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "battram.ut"
#endif  
/* FOR UNIT TEST ONLY */
