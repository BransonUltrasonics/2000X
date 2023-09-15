/* $Header:   D:/databases/VMdb/2000Series/App/version.c_v   1.12.1.0.1.1.1.6.2.4   Jan 17 2018 09:08:44   RCHAPA  $ */
/* ************************************************************************ */ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/* ************************************************************************ */
/*
---------------------------- MODULE DESCRIPTION ------------------------------

     Module name: 

        Filename: version.c

      Written by:  
            Date: 06/02/2004 
        Language: "C"

--------------------------------- REVISIONS ----------------------------------

 Revision #      Date           Author        Description
 ==========      ========       ======        ===========
 1.0             06/02/04       SCM           Initial Version
 1.1             06/04/04       VSharma       Added CheckForVersionChange() & 
                                              UpdateToVer9().
 1.2             06/22/04       JOY           The Version8.21 Variables are initialized 
                                              in separate function UpdateToVer8_21().
 1.3             08/18/04       JOY           Added default values in UpdateToVer9().                                            
 1.4             05-12-05       BEKymer       Fix Tracker issue # 3915  
 1.5             06-10-05       Aare          Moved CurrentVersion here.   
 1.6             07-25-05       Bwadia        QVGA clean up in Ver10.0e
 1.7             12-16-08       BEKymer       Add ver 10 and 11 to table even
                                              though no known update needed.
 1.8             11-08-10       BEKymer       Changed version to 1120.
 1.9             11-8-10        BEKymer       Moved version string from command.c
                                              Changed version to 11.20H for MH2
 1.10            11-15-10       BEKymer       Include command.h to get SW_VERSION_LENTGH
 1.11            12-28-10       PDwivedi      Changed version String to MICRO_11.20I for 
                                              2000X real time clock Issue.
 1.12            02-28-11       PDwivedi      Added changes for USB Memory Full Alarm.
 1.12.1.0        03-24-11       BEKymer       Change version to 11.20 for final release
 1.12.1.0.1.0    09-12-12       GButron       Change version to 11.30 for final release
 1.12.1.0.1.1    06-26-13       HSanchezZ     Change version to 11.32 for final release
 1.12.1.0.1.2    06-26-13       HSanchezZ     Change version to 11.33E
 1.12.1.0.1.3    06-26-13       HSanchezZ     Change version to 11.33H
 1.12.1.0.1.4    06-26-13       HSanchezZ     Change version to 11.33 
 1.12.1.0.1.6    09-25-14       HSanchezZ     Change version to 11.34
 1.12.1.0.1.1.1.6.2.1	 12-05-17		RChapa		  Change version to 11.35A
 1.12.1.0.1.1.1.6.2.2	 12-27-17		RChapa		  Change version to 11.35C
 1.12.1.0.1.1.1.6.2.3	 01-11-18		RChapa		  Change version to 11.35D 
 1.12.1.0.1.1.1.6.2.4	 01-17-18		RChapa		  Change version to 11.35 
*/

/*
 -------------------------------- DESCRIPTION --------------------------------
*/

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include <psos.h>
#include <string.h>
#include "sysmangr.h"
#include "ascii.h"
#include "serial.h"
#include "menu.h"
#include "dups.h"
#include "menu3.h"
#include "alarms.h"
#include "string.h"
#include "preset.h"
#include "battram.h"
#include "inports.h"
#include "outports.h"
#include "dups_api.h"
#include "version_change.h"
#include "screenmsg_touch.h"
#include "psnvram.h"
#include "command.h"
#include "preset.h"


/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
#define DEFAULT_SEEKTIME   500
#define DEFAULT_RAMPTIME   80
#define DEFAULT_SAMPLEVAL  1
#define VER_800            800

/*
 ------------------------------- GLOBAL DATA ---------------------------------
*/
/*                       (scope is global to ALL files)                     */

const UINT16  CurrentVersion =1136;     /* Current version/revision in binary, no decimal */
SINT8 SWVersionLabel[SW_VERSION_LENTGH+1] = "11.35K";

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/
extern UINT32    PresetAddress[];
extern BUCMENU_800 *BUCMenuBBR;
extern const UINT16  CurrentVersion;
extern SETUPS_Ver800 CurrentPreset;

extern UINT32 WeldDataAddress[];

/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/
/*    struct VER_INFO               VersionNum,  void (*VerUpdateFunc)() */
const struct VER_INFO Ver_Info[] = { {VERMIN,          Nothing         },
                                     {VER8_21,         UpdateToVer8_21 },
                                     {VER8_22,         Nothing         },
                                     {VER8_23,         Nothing         },
                                     {VER9,            UpdateToVer9    },
                                     {VER10,           Nothing		   },
                                     {VER11,           Nothing         },
									 {VER1136,		   UpdateToVer1136 },
									 {VER12,           Nothing         },
                                     {VERMAX,          Nothing      }  };


/*
 --------------------------- EXTERNAL FUNCTION PROTOTYPES --------------------
*/
UINT32 GetCurrentHwCnfg (void);
/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -----------------------
*/

/*
 ---------------------------------- CODE -------------------------------------
*/

void CheckForVersionChange (void)
/***************************************************************************/
/*                                                                         */
/*  This function is called on the powerup and check if the new version    */
/*  software is downloaded then it will update the Newly added variable of */
/*  latest version with the default values. This function will update the  */
/*  last saved data accoring to the latest software version.               */
/*                                                                         */
/***************************************************************************/
{
   PRESET_COMPRESSED* CompressPreset;
   CONFIGSETUP *BBRPtr;
   UINT16 i;
  
   CompressPreset = (PRESET_COMPRESSED*) PRESET_0_START;
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   
   if(CompressPreset->Version >= VER_800 && CompressPreset->Version < CurrentVersion)
   {
      /* Update the last saved data for the latest software.  */
      for(i=0; Ver_Info[i].VersionNum != VERMAX ;i++)
         if(CompressPreset->Version < Ver_Info[i].VersionNum && 
             Ver_Info[i].VerUpdateFunc != NULL )
            Ver_Info[i].VerUpdateFunc();
                   
       /* Update Version of preset. */
       for (i=0; i< ALL_PRESETS; i++) {
          CompressPreset = (PRESET_COMPRESSED*)PresetAddress[i]; 
          CompressPreset->Version = CurrentVersion;
       }
   }   
}

void UpdateToVer8_21(void)
/***************************************************************************/
/*                                                                         */
/*  This function will update the newly added variable in version 8.21     */
/*  with the default values in BBRam.                                      */
/*                                                                         */
/***************************************************************************/
{
   UINT16 x;
   CONFIGSETUP *BBRPtr;
   HORNSCANINFO *HornScanInfoPtr; 
   
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   
   /* Set Default Touch Screen Calib. points */
   /*memcpy((SINT16*)BBR800_QVGASCRNCLAIB_START, (SINT16 *)&ActualCalibPts,
              sizeof(SCRN_CALIB_CORDINATE));*/
   
   /*Update all the current setup and BUCMenu variables */
   BBRPtr->WeldParamOption[0] = RCYCLECOUNT;
   BBRPtr->WeldParamOption[1] = RTIME;
   BBRPtr->WeldParamOption[2] = RPKPWR;
   BBRPtr->WeldParamOption[3] = RENERGY;
   BBRPtr->WeldParamOption[4] = RTCOLDIST;
   BBRPtr->QVGAImgSaved = 0;
   
   /* Update the BUCMenu variables.   */
   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   BUCMenuBBR->VelocityReporting = FALSE;

   /* Clear the HornScanData in BBRam.  */
   HornScanInfoPtr = (HORNSCANINFO *)BBR800_HORNSCAN_START; 
   HornScanInfoPtr-> NumScanPoints = 0;
   for(x=0; x<=DUPS_NUMRESONANCES; x++) {  
      HornScanInfoPtr->ResonanceFreqs[x] = 0;
      HornScanInfoPtr->ResonanceFreqType[x] = FREQ_NONE;
   } 
   HornScanInfoPtr->ScanStatus    = DUPS_NOSCAN;

}


void UpdateToVer9(void)
/***************************************************************************/
/*                                                                         */
/*  This function will update the newly added variable in version 9.00     */
/*  with the default values in BBRam.                                      */
/*                                                                         */
/***************************************************************************/
{
   UINT16 x;
   UINT32 CurrentHwCnfg;
   PRESET_COMPRESSED* TempPreset;
   CONFIGSETUP *BBRPtr;
   HORNSCANINFO *HornScanInfoPtr; 
   
   CurrentHwCnfg = GetCurrentHwCnfg(); 
   
   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;
   
   /* Upgrade the alarm mask variables. */
   GetAlarmMask();

   for (x=0; x< ALL_PRESETS; x++) {
      TempPreset = (PRESET_COMPRESSED *)PresetAddress[x];
      /* Update all Preset variables. */
      TempPreset->HwCnfg = CurrentHwCnfg;
      TempPreset->Verified = FALSE;
      TempPreset->SwDip |= DUPS_SWDIPAMPLITUDEEXTERN | DUPS_SWDIPSTOREMEMATWLDEND; /* external amp control */
      TempPreset->SwDip &= ~DUPS_SWDIPAUTOSEEK;
      TempPreset->SeekTime = DEFAULT_SEEKTIME;  /* Seek time and seek flag value hard coded*/
      TempPreset->WeldRampTime = DEFAULT_RAMPTIME;
      TempPreset->ZWriteIn1[0] = NULL;
      TempPreset->ZWriteIn2[0] = NULL;
      TempPreset->Version = CurrentVersion;
   }   
      
   /*Update all the current setup and BUCMenu variables */
   BBRPtr->BeeperRelease = FALSE;
   BBRPtr->CustomAct = FALSE;         /*   */
   BBRPtr->DUPS_WorkingPreset = 0;
   BBRPtr->J3_32In = INPUT_PRESET1;        // Select preset 1
   BBRPtr->J3_33In = INPUT_PRESET2;        // Select Preset 2
   BBRPtr->J3_19In = INPUT_PRESET3;        // Select Preset 3
   BBRPtr->J3_17In = INPUT_PRESET4;        // Select Preset 4
   BBRPtr->J3_31In = INPUT_DISP_LOCK;      // Display Lock.
   BBRPtr->J3_1In = INPUT_EXT_TRIGGER;     // Ext Trigger.
   BBRPtr->J3_36Out = OUTPUT_NO_CYCLEALARM;//  No Cycle Alarm
   BBRPtr->J3_8Out = OUTPUT_CYCLE_OK;      //  Cycle OK
   BBRPtr->J3_22Out = OUTPUT_EXT_BEEPER;   //  Missing Part
   BBRPtr->UserInLogic = FALSE;
   BBRPtr->GndDetLogicCustom = TRUE; /*Custom Menu Defaults.*/
   BBRPtr->ULSLogicCustom = TRUE;
   BBRPtr->ExtGlobalPrintFlag = TRUE;
   BBRPtr->SPExtSampleFlag    = TRUE; /* SampleFlag */
   BBRPtr->WHExtSampleFlag    = TRUE;
   BBRPtr->WSExtSampleFlag    = TRUE;
   BBRPtr->PGExtSampleFlag    = TRUE;
   BBRPtr->AGExtSampleFlag    = TRUE;
   BBRPtr->FreqGExtSampleFlag = TRUE;
   BBRPtr->CDGExtSampleFlag   = TRUE;
   BBRPtr->VGExtSampleFlag    = TRUE;
   BBRPtr->FGExtSampleFlag    = TRUE;
   BBRPtr->SPExtAlarmFlag    = FALSE; /* Alarm Flag */
   BBRPtr->WHExtAlarmFlag    = FALSE;
   BBRPtr->WSExtAlarmFlag    = FALSE;
   BBRPtr->PGExtAlarmFlag    = FALSE;
   BBRPtr->AGExtAlarmFlag    = FALSE;
   BBRPtr->FreqGExtAlarmFlag = FALSE;
   BBRPtr->CDGExtAlarmFlag   = FALSE;
   BBRPtr->VGExtAlarmFlag    = FALSE;
   BBRPtr->FGExtAlarmFlag    = FALSE;
   BBRPtr->SPExtSampleValue = DEFAULT_SAMPLEVAL;  /* SampleValue */
   BBRPtr->WHExtSampleValue = DEFAULT_SAMPLEVAL;
   BBRPtr->WSExtSampleValue = DEFAULT_SAMPLEVAL;
   BBRPtr->PGExtSampleValue = DEFAULT_SAMPLEVAL;
   BBRPtr->AGExtSampleValue = DEFAULT_SAMPLEVAL;
   BBRPtr->FreqGExtSampleValue = DEFAULT_SAMPLEVAL;
   BBRPtr->CDGExtSampleValue = DEFAULT_SAMPLEVAL;
   BBRPtr->VGExtSampleValue = DEFAULT_SAMPLEVAL;
   BBRPtr->FGExtSampleValue = DEFAULT_SAMPLEVAL;
   BBRPtr->BBRInitialized = BBRAM_INIT;
   BBRPtr->WeldHistoryPtr = (BBR800_HISTORY_START);
   
   BBRPtr->WelderAddrFlag = 1;         /* Welder ID On/Off */
   BBRPtr->WelderAddrValue = 100;        /* Welder ID value */   
   BBRPtr->SVDelay = 5000;
   
   /* Update the BUCMenu variables.   */
   BUCMenuBBR = ( BUCMENU_800*) BBR800_BUCMENU_START;
   BUCMenuBBR->EnergyBrakingTime = ENERGY_BRAKE_TIME_DEFAULT;
   BUCMenuBBR->EnergyBrakingAmp = ENERGY_BRAKE_AMP_DEFAULT;
   BUCMenuBBR->AmpDecayPercent = AMP_DECAY_PERCENT_DEFAULT;
   /*  Clear the weld history data. */
   ClearHistoryInBbram();
     
   SaveColdStartValues(); /* Save the ColdStart preset in BattRam. */
}

void SaveColdStartValues (void)
/*****************************************************************************/
/*                                                                           */
/*  This function will restore the normal factory defaults for the cold      */
/*  start values. First this function Make the CurrentPreset struct with     */
/*  default values and then save the preset as ColdStart preset in BattRam.  */
/*                                                                           */
/*****************************************************************************/
{
   SetDefaultValues(); /* Store the default values in CurrentPreset struct. */
   CurrentPreset.SetRTComp = RT_COMP_DEFAULT; 
   CurrentPreset.RTRamp = RATE_SLOW;            
   CurrentPreset.ReturnRamp = RATE_SLOWEST; 
   CurrentPreset.StartRamp = RATE_SLOW;
   CurrentPreset.PresetUpdateComplete = TRUE;
   strcpy(CurrentPreset.PresetID, "COLD START");        /* Name it              */
   SaveCompressedPreset( (PRESET_COMPRESSED *) PRESET_CLDSTRT_START, &CurrentPreset);
}

void UpdateToVer1136(void)
/***************************************************************************/
/*                                                                         */
/*  This function will update the newly added variable in version 9.00     */
/*  with the default values in BBRam.                                      */
/*                                                                         */
/***************************************************************************/
{
	   UINT16 WeldStructSizeCrt;
	   UINT16 CounterCrt;
	   UINT16 SubCounterCrt;
	   PRESET_COMPRESSED* TempPreset;
	   CONFIGSETUP *BBRPtr;

	   /*******************************/
	   UINT8            *BBRPointer;
	   UINT8            *DataPointer;
	   UINT32            Offset;
	   UINT16            ByteCounter;

	   /*****************************************/
	   WELD_DATA_1135 WeldingRead;
	   UINT32 MaxCycleCount,MaxWeldDataAddress;
	   /*****************************************/
	   UINT8 *NotAssingBattramPtr;
	   UINT16 ByteCount;
	   /****************************************/

	   BBRPtr = (CONFIGSETUP *) BBR800_CONFIG_START;

	   BBRPtr->AmpMicronsFlag = FALSE;
	   BBRPtr->AmpMicronsValue = 20;
	   BBRPtr->PeakPowerWattsFlag = FALSE;

	   for (CounterCrt=0; CounterCrt< ALL_PRESETS; CounterCrt++) {
	      TempPreset = (PRESET_COMPRESSED *)PresetAddress[CounterCrt];
	      TempPreset->AmpAMicron = 20;
	      TempPreset->AmpBMicron = 20;
	      TempPreset->Version = CurrentVersion;
	   }

	   /****************************************/
	   NotAssingBattramPtr = (UINT8 *) BBR800_NOTASSIGNED_START;
	   for(ByteCount = 0; ByteCount < BBR800_NOTASSIGNED_SIZE; ByteCount++){
	      *NotAssingBattramPtr++ = 0;
	   }
		MaxCycleCount=0;
		MaxWeldDataAddress=0;
	    for (CounterCrt=0; CounterCrt< NMBR_OF_WELD_HISTORY; CounterCrt++) {

	    	Offset = CounterCrt * sizeof(WELD_DATA_1135);
	    	BBRPointer = (UINT8 *) (BBR800_HISTORY_START_1135 + Offset);
		    ByteCounter = sizeof(WELD_DATA_1135);
		    DataPointer = (UINT8*)&WeldingRead;
            while (ByteCounter > 0) {
               *DataPointer = *BBRPointer;
               BBRPointer++;
               DataPointer++;
               ByteCounter--;
            }

	       Offset = CounterCrt * sizeof(WELD_DATA);
	       BBRPointer = (UINT8 *) (BBR800_HISTORY_START + Offset);
		   ByteCounter = sizeof(WELD_DATA_1135);
		   DataPointer = (UINT8*)&WeldingRead;
           while (ByteCounter > 0) {
              *BBRPointer = *DataPointer;
              BBRPointer++;
              DataPointer++;
              ByteCounter--;
           }

           WeldStructSizeCrt = sizeof(WELD_DATA) - sizeof(WELD_DATA_1135);
           for(SubCounterCrt=0;SubCounterCrt<WeldStructSizeCrt;SubCounterCrt++){
               *BBRPointer = 0;
               BBRPointer++;
           }

	 	   if(WeldingRead.CycleCount>MaxCycleCount){
	 			MaxCycleCount=WeldingRead.CycleCount;
	 			MaxWeldDataAddress=(UINT32)WeldDataAddress[CounterCrt]+sizeof(WELD_DATA); //Add address plus extra weld sizes
	 	   }

	    }
	    /*************************************************/
	    BBRPtr->WeldHistoryPtr = MaxWeldDataAddress;
		CheckHistoryPtrBound();
}
