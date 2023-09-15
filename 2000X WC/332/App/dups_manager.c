/* $Header:   D:/SWLab/VMdb/2000Series/App/dups_manager.c_v   1.73   12 Sep 2008 19:22:14   NHAHMED  $ */
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
------------------------- MODULE DESCRIPTION -------------------------------
                                          
   Module name:   DUPS manager

   Filename:      dups_manager.c

   Function name: 

            Written by: Ashish Sharma 
                  Date: 06/07/00
              Language:  "C"                              


----------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author   Description
   ==========   ========   ======   ===========
       1.0      06/07/00   AS       Initial Version
       1.1      06/19/00   AS       General clean-up
       1.2      06/29/00   SRP      Modified as per Part II spec.
       1.3      06/30/00   SRP      PSType made commented 
       1.4      07/07/00   SRP      All functions modified after code review.
                                    checked in for complete build.
       1.5      07/13/00   SRP      Upload param set null char added.
       1.6      07/14/00   SRP      Memflag,seekflag logic addded. Temporary stuff addred
                                    for deebugging purpose. 
       1.7      07/18/00   SRP      -> is peplaced by . at DUps_info and horninfo. Fequ and power
                                    made commented in upload and download.
       1.8      07/19/00   SRP      BBRAM2RAM and RAM2BBRAM function added. Paramsetname made commeneted 
       1.9      07/19/00   SRP      ParamSetName string logic updated in upload and download paramset.
       1.10     07/19/00   srp      Compile error removed at stptr
       1.11     07/19/00   SRP      PSnum input param removed from downloadparamset function                                                                                                            
                                    param conversion function added
       1.12     07/20/00   SRP      UpdateHWConfiguration function call added in interfaceinit.
       1.13     07/20/00   SRP      DUPS  value changed to ~DUPS in UpdateHWConfiguration function 
       1.14     07/20/00   SRP      UpdateHWConfiguration made true at dups expected place
       1.15     07/20/00   SRP      UpdateHWConfiguration made same as previous at dups expected place
       1.16     07/22/00   SRP      sptr pointer to string err fixed .
       1.17     07/25/00   SCM      Removed the Dups_Info structure from BBRAM.
       1.18     07/26/00   SRP      Download paramset function commented temporary. Returns only status.
       1.19     07/27/00   SRP      pointer addressing to RspBuf corrected in Upload and Download paramset. Check is added
                                    for a valid cops and Dups preset nos. in initialization. checked in under Ver8.
       1.20     07/28/00   SRP      & removed from Paramsetname[] in upload paramset inserted for testing. ParamSetName
                                    is not uploaded temporary. It is made commented.
       1.21     08/02/00   SRP      DUPs_ParamSetname made two dim array. Hornscan conversion added. Download param set
                                    corrected. Paramconversion removed.
       1.22     08/02/00   SRP      DUPS_PerD2C() and DUPS_PerC2D() fun added. qdelete temoved. Freq conversion added at hornscan fun.
       1.23     08/03/00   SRP      DUPSOkFlag added.
       1.24     08/07/00   SRP      tmwakeafter in initialization reduced. MsgScanabort added. Freq cobersion added for hornscan.
       1.25     08/08/00   SRP      Tmwakeafter at initialization is removed. Beeper control is also removed.
       1.26     08/08/00   SRP      DUPSOkFlag = TRUE added after initialzation is complete. All other place it is removed.
       1.27     08/09/00   SRP      tm_wkafter value is changed in hornscan.
       1.28     08/10/00   SRP      UpdateScanDateandTime func added to update RTC parameters after scan complete.
       1.29     08/10/00   Jhenri   Checked in to unlock file.
       1.30     08/11/00   RBH      Save/Recall Preset corrections 
       1.31     08/11/00   SRP      MAxcurrent and amplitude for hornscan is converted. New func for hornscan data processing called.
       1.32     08/12/00   SCM      Moved the BBRAM functions to dups_api.c.
       1.33     08/14/00   AT       UploadWeldStatus - convert error frequency
       1.34     08/16/00   RBH      Corrections to Save/Recall presets and Parameter Sets 
       1.35     08/17/00   AT       SendFakeKeyPress(UPDATEDISPLAY) at end of horn scan to refresh frequencies
       1.36     08/23/00   SRP      Old scan data cleared. Status returned in step function.
       1.37     08/24/00   AT       DUPS_MsgXXXXParamSet() - hard-coded DipFlag to 1 (Software DIP)
       1.38     08/24/00   LAM      update psnovram with the dups freq and power
       1.39     08/25/00   SCM      Enabled all the keys on Horn Scan completion.
       1.40     08/28/00   SRP      Hornscan Abort stuff added.
       1.41     08/28/00   AT       Added alarm if DUPS expected but not found, ClrReady and SetReady to horn scan
       1.42     08/28/00   AT       Hard-coded DipFlag to 0 (real Software DIP value)
       1.43     08/29/00   AT       DUPS_MsgSelectParamSetNum - don't clear current parameter set, upload instead
                                    DUPS_MsgInitInterface - select parameter set 20 to work on
                                    DUPSMemFlag depends on DUPS_SWDIPSTOREMEMATWLDEND
      1.44      09/07/00   SRP      Cleaning, Touchup, Description added at each functions.
      1.45      09/08/00   SCM      General clean up.
      1.46      09/20/00   AT       DUPS_PerC2D - fixed roundoff error
      1.47      09/20/00   AT       Tried to correct roundoff by putting some of it into DUPS_PerD2C
                                    Still not 100%...
      1.48      09/28/00   AT       Cleanup after code review
      1.49      09/29/00   SCM      Fixed the problems with the Horn Scan graph start and stop frequencies.
      1.50      10/05/00   LAM      Fixed the problems with the Horn Scan abort
                                    ISSUE(3597)
      1.51      10/05/00   AT       DUPS_MsgUploadWeldStatus - added % conversion for ErrorPSV and Current
      1.52      10/09/00   LAM      fix updatekeymask when hornscan complete.
      1.53      10/10/00   AT       Force DUPS_SWDIPAMPLITUDEEXTERN SW DIP switch on in upload/download
      1.54      10/12/00   AT       Copy paramset name to current in upload and from current on download
                                    Changed SINT16 to enum DUPS_RESULTS
                                    Entirely commented out MsgHornScanAbort
                                    Replaced PSOS_MSG_OK with PSOS_OK
      1.55      10/13/00   SCM      Fixed problems with Horn Scan printing.Tracker issue no:3626
      1.56      10/24/00   AT       Fixed DUPS_MsgUploadWeldStatus to update status after unsuccessful transfer
      1.57      05-22-03   BEKymer  In DUPS_MsgUploadSWId accept DUPS software versions 1.x and 2.x
      1.56.2.1  07/02/03   JOY      'ResonanceFreqType' is Cleared when Scan is aborted. 
      1.58      07-24-03   LAM      merger 8.10 with ts01
      1.59      09-08-03   JOY      'RESONANCE_FREQ_TYPE', is moved to 'HORNSCAN_INFO'. 
      1.60      02-02-04   VSharma  'CurrentSetup.DUPS_WorkingPreset' is updated when downloading DUPS parameters.
                                    At the power up DUPS_CurrentParamset is updated from Current DUPS working preset
                                    in DUPS_MsgInitInterface().
      1.61      04-06-04   VSharma  Modified DUPS_MsgHornScanStep() & DUPS_MsgDownloadStartScan() for not to 
                                    display Resonance frequencies for NULL value. 
      1.62      05-17-04   VSharma  Formatted bracket spaces in DUPS_MsgSelectParamSetNum().
      1.63      08-04-04   JOY      Updated 'DUPS_CurrPSStatus' flag in DUPS_MsgSelectParamSetNum().
      1.64      08-05-04   SCM      Fixed the 'warning' that came up during compile.
      1.65      09-10-05   Aare     Added InitSBL(), UpdateSBL() and VerifySBL().
      1.66      11-22-05   Bwadia   InitSBL(), UpdateSBL() modified.
      1.67      12-20-05   Bwadia   DUPS_HostDownloadParamSet() and DUPS_HostUploadParamSet()
                                    added. Modified for Tracker issue 4013
      1.68      01-03-06   Bwadia   Dummy check in
	  1.69      01-12-06   Bwadia   HS_MaxScanInfo and HS_MinScanInfo structure
									start frequency and stop frequency initialized
									at power up. Modified for tracker 3966
      1.70      02-22-06   Bwadia   Modified for tracker issue 4078. Actual frequency 
	                                stored when +/- freq SBL limit condition detected.
	                                Also modified for memory reset implementation
	                                Tracker issue 4077
	  1.71      02-22-06   Bwadia   RunningPreset used instead of CurrentPreset
	                                for VerifySBL()                                      
	  1.72      09-04-08   YGupta   CleanUp for LangTest Project.
	  1.73      09-12-08   NHAhmed  Added a function UpdateDUPS_MaxWeldFreqLimit() to change
                                   maximum limit of WeldFrequency according to PSFrequency.
*/

/*------------------------------ DESCRIPTION -------------------------------*/

/* 
   This file is the DUPS manager. Its a pSOS task waiting for a message from
   one of DUPS API functions.
*/


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"
#include "dups_api.h"
#include "dups.h"
#include <psos.h>
#include "ascii.h"
#include "ready.h"
#include "alarms.h"
#include "preset.h"
#include "psnvram.h"
#include "menu.h"
#include "state.h"
#include "rtclock.h"
#include "keypad.h"
#include "getmsg.h"
#include "fpk_task.h"
#include "digout.h" 
#include <string.h>
#include "util.h"
#include "statedrv.h"

/*---------------------------- EXTERNAL DATA -------------------------------*/
extern CONFIGSETUP CurrentSetup;
extern enum WELD_SEQUENCE_TYPE CurrentSequence;
extern UINT16 *HornScanRawFrequency;
extern SINT16 *HornScanRawCurrent; 
extern SINT16 *HornScanRawPhase; 
extern SINT8 DUPS_ScanStep;
extern BOOLEAN IsRecalledPreset;
extern UINT16 ResonanceFreqEnable[];
extern SETUPS_Ver800      CurrentPreset, RunningPreset;
extern BOOLEAN SBLMinLimitReached;
extern BOOLEAN SBLMaxLimitReached;
extern SINT32 CurrentFreqIn;          /* Value being read by 7890          */
extern UINT16 ShowHSAbort;

/*----------------------------- LOCAL DEFINES ------------------------------*/
#define PSFREQ15     15
#define PSFREQ20     20
#define PSFREQ30     30
#define PSFREQ40     40

/*----------------------- LOCAL TYPE DECLARATIONS --------------------------*/

/*----------------------------- GLOBAL DATA --------------------------------*/

UINT32        DupsQid;          /* Queue id initialized in roots.c */
DUPS_CMDBUF DUPS_CmdBuf;
DUPS_RESPONSEBUF DUPS_RspBuf;
DUPS_RAWWELDSTATUS DUPS_RawWeldStatus;
DUPS_RAWPARAMSET DUPS_RawParamSet;
DUPS_DOWNLOADPARAMCMD DUPS_DownloadParamCmd;
DUPS_UPLOADPARAMRSP DUPS_UploadParamRsp;
HORNSCANPOINT HornScanPoint;
DUPS_CURRENTPARAMSET DUPS_HostParamSet; /* Declare the DUPS Host preset struct */ 
STR DUPS_HostParamSetName[DUPS_PARAMSETNAMELEN + 1]; /*DUPS host preset name*/
SINT32 ActualSBLMinFreq;
SINT32 ActualSBLMaxFreq;

/*------------------------- PRIVATE GLOBAL DATA ----------------------------*/


/*------------------------ EXTERNAL FUNCTIONS ------------------------------*/


/*----------------------- LOCAL FUNCTION PROTOTYPES ------------------------*/
SINT32 DUPS_PerD2C(SINT32 DUPSPer);
SINT32 DUPS_PerC2D(SINT32 COPPer);
void UpdateScanDateandTime(void);
void InitSBL(void);
void UpdateSBL(void);

/*------------------------------ CODE --------------------------------------*/


void DUPS_Manager(void)
/*******************************************************************************/
/*  The function recieves messages from the DUPS API functions and calls the   */ 
/*  corresponding message function to process the message.                     */
/*******************************************************************************/
{ 
   DUPS_MSGBUF InMsg;
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT32      psosStatus;
   while (TRUE)        /* Wait forever for a message */
   {  
      if((psosStatus = q_receive(DupsQid, Q_WAIT, Q_WAIT_FOREVER, &InMsg))
                     == PSOS_OK)
      {
         switch(InMsg.mt)
         {  
            case DUPS_MSGINITINTERFACE:
            {  status = DUPS_MsgInitInterface();
               break;
            }

            case DUPS_MSGUPLOADHWID:
            {  status = DUPS_MsgUploadHWId();
               break;
            }
         
            case DUPS_MSGUPLOADSWID:
            {  status = DUPS_MsgUploadSWId();
               break;
            }
         
            case DUPS_MSGSELECTPARAMSETNUM:
            {  status = DUPS_MsgSelectParamSetNum( (UINT8)InMsg.data1);
               break;
            }
         
            case DUPS_MSGREQUESTPARAMSETNUM:
            {  status = DUPS_MsgReqParamSetNum();
               break;
            }
            
            case DUPS_MSGDOWNLOADPARAMSET:
            {  status = DUPS_MsgDownloadParamSet( (UINT8)InMsg.data1);
               break;
            }
          
            case DUPS_MSGUPLOADPARAMSET:
            {  status = DUPS_MsgUploadParamSet( (UINT8)InMsg.data1);
               break;
            }
            
            case DUPS_MSGDOWNLOADLIBRARYNAME:
            {  status = DUPS_MsgDownloadLibraryName();
               break;
            }
         
            case DUPS_MSGUPLOADLIBRARYNAME:
            {  status = DUPS_MsgUploadLibraryName();
               break;
            }
            
            case DUPS_MSGUPLOADLASTWELDSTATUS:
            {  status = DUPS_MsgUploadWeldStatus((DUPS_WELDSTATUS *) InMsg.data2);
               break;
            }
           
            case DUPS_MSGUPLOADRELEASE:
            {  status = DUPS_MsgUploadReleaseId();
               break;
            }

            case DUPS_MSGDOWNLOADSTARTSCAN:
            {  status = DUPS_MsgDownloadStartScan();
               break;
            }

            case DUPS_MSGHORNSCANSTEP:
            {  status = DUPS_MsgHornScanStep(InMsg.data1);
               break;
            }
         
            case DUPS_MSGHORNSCANABORT:
               status = DUPS_SUCCESS;
               break;
//            {  status = DUPS_MsgHornScanAbort();
//               break;
//            }
         
            case DUPS_MSGUPLOADSCANPOINT:
            {  status = DUPS_MsgUploadScanPt();
               break;
            }

            default:
            {  status = DUPS_OTHER;
               break;
            }
         }  /* End of switch(InMsg.mt) */
      } /* End of if (  q_ receive -- ) */
      else
         status = DUPS_OTHER;
      if (status != DUPS_SUCCESS)
         RecordAlarm(EQ15);
   } /* End of while(TRUE) */
} /* End of void DUPS_Manager(void) */



enum DUPS_RESULTS DUPS_MsgUploadHWId(void)
/******************************************************************************/
/* This function sends a command to DUPS to Upload HWId and get the power     */ 
/* supply Frequency and power supply Watts.                                   */
/******************************************************************************/
{  
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = sizeof(DUPS_CmdBuf.Count) + sizeof(DUPS_CmdBuf.Cmd);
   DUPS_CmdBuf.Cmd      = DUPS_CMDUPLOADHWID;  /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS)
   { 
      DUPS_Info.PowerSupplyFreq = (DUPS_RspBuf.Rsp_Data[0] * 0x100) + DUPS_RspBuf.Rsp_Data[1];
      switch(DUPS_Info.PowerSupplyFreq)
      {
         case PSFREQ15:
            DUPS_Info.FreqConversion = DUPS_15KHZ;
            CurrentSetup.PSFreq = FREQ15KHZ;
            HornScanInfo. StartFreq        =  DUPS_FreqD2C(DUPS_MIN15AND30);
            HornScanInfo. StopFreq         =  DUPS_FreqD2C(DUPS_MAX15AND30);
            HS_MaxScanInfo. StartFreq      =  DUPS_FreqD2C(DUPS_MAX15AND30);
            HS_MaxScanInfo. StopFreq       =  DUPS_FreqD2C(DUPS_MAX15AND30);
            HS_MinScanInfo. StartFreq      =  DUPS_FreqD2C(DUPS_MIN15AND30);
            HS_MinScanInfo. StopFreq       =  DUPS_FreqD2C(DUPS_MIN15AND30);
            break;

         case PSFREQ20:
            DUPS_Info.FreqConversion = DUPS_20KHZ;
            CurrentSetup.PSFreq = FREQ20KHZ;
            HornScanInfo. StartFreq        =  DUPS_FreqD2C(DUPS_MIN20AND40);
            HornScanInfo. StopFreq         =  DUPS_FreqD2C(DUPS_MAX20AND40);
            HS_MaxScanInfo. StartFreq      =  DUPS_FreqD2C(DUPS_MAX20AND40);
            HS_MaxScanInfo. StopFreq       =  DUPS_FreqD2C(DUPS_MAX20AND40);
            HS_MinScanInfo. StartFreq      =  DUPS_FreqD2C(DUPS_MIN20AND40);
            HS_MinScanInfo. StopFreq       =  DUPS_FreqD2C(DUPS_MIN20AND40);
            break;

         case PSFREQ30:
            DUPS_Info.FreqConversion = DUPS_30KHZ;
            CurrentSetup.PSFreq = FREQ30KHZ;
            HornScanInfo. StartFreq        =  DUPS_FreqD2C(DUPS_MIN15AND30);
            HornScanInfo. StopFreq         =  DUPS_FreqD2C(DUPS_MAX15AND30);
            HS_MaxScanInfo. StartFreq      =  DUPS_FreqD2C(DUPS_MAX15AND30);
            HS_MaxScanInfo. StopFreq       =  DUPS_FreqD2C(DUPS_MAX15AND30);
            HS_MinScanInfo. StartFreq      =  DUPS_FreqD2C(DUPS_MIN15AND30);
            HS_MinScanInfo. StopFreq       =  DUPS_FreqD2C(DUPS_MIN15AND30);
            break;

         case PSFREQ40:
            DUPS_Info.FreqConversion = DUPS_40KHZ;
            CurrentSetup.PSFreq = FREQ40KHZ;
            HornScanInfo. StartFreq        =  DUPS_FreqD2C(DUPS_MIN20AND40);
            HornScanInfo. StopFreq         =  DUPS_FreqD2C(DUPS_MAX20AND40);
            HS_MaxScanInfo. StartFreq      =  DUPS_FreqD2C(DUPS_MAX20AND40);
            HS_MaxScanInfo. StopFreq       =  DUPS_FreqD2C(DUPS_MAX20AND40);
            HS_MinScanInfo. StartFreq      =  DUPS_FreqD2C(DUPS_MIN20AND40);
            HS_MinScanInfo. StopFreq       =  DUPS_FreqD2C(DUPS_MIN20AND40);
            break;

         default:
            break;
      }

      DUPS_Info.PowerSupplyWatts = (DUPS_RspBuf.Rsp_Data[2] * 0x100) + DUPS_RspBuf.Rsp_Data[3];
      CurrentSetup.PSWatt = DUPS_Info.PowerSupplyWatts;
   }
   return status;
} /* End of SINT16 DUPS_MsgUploadHWId(void) */



enum DUPS_RESULTS DUPS_MsgUploadSWId(void)
/******************************************************************************/
/*                                                                            */
/* This function sends a command to DUPS to Upload SWId and get the Program   */ 
/* ID and the Flash Version.  Currently only DUPS version 1.x or 2.x will be  */
/* accepted.  All others will result in Failure of: Ultrasonic P/S and the    */
/* system will revert to an analog power supply.                              */
/*                                                                            */
/******************************************************************************/
{  
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT16 PgID;
   UINT16 FlashVersion;     
   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = 0x0004;
   DUPS_CmdBuf.Cmd      = DUPS_CMDUPLOADSWID;  /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS)
   { 
      PgID    = (DUPS_RspBuf.Rsp_Data[0] * 0x100) + DUPS_RspBuf.Rsp_Data[1];
      FlashVersion = (DUPS_RspBuf.Rsp_Data[2] * 0x100) + DUPS_RspBuf.Rsp_Data[3];
      if ( (PgID/100 == 1 && !FlashVersion ) || (PgID/100 == 2 && !FlashVersion ) )  /* If progrsam version is 1 or 2 */
      {                                                                              /* and Flash version = 0         */
         DUPS_Info.ProgramId    = PgID;
         DUPS_Info.FlashVersion = FlashVersion;
      }
      else
         status = DUPS_OTHER;
   } 
   return status;
} /* End of SINT16 DUPS_MsgUploadSWId(void) */



enum DUPS_RESULTS DUPS_MsgSelectParamSetNum(UINT8 psNum)
/********************************************************************************/
/* This function sends a command to DUPS to select the DUPS parameter set number*/ 
/********************************************************************************/
{  
   enum DUPS_RESULTS status = DUPS_SUCCESS;//DUPS_MsgUploadParamSet(psNum);

   if (status == DUPS_SUCCESS)
   {
      DUPS_CmdBuf.DLE_Byte = DLE;
      DUPS_CmdBuf.STX_Byte = STX;
      DUPS_CmdBuf.Count    = 0x0005;
      DUPS_CmdBuf.Cmd      = DUPS_CMDSELECTPARAMSETNUM;  /* Set up command */
      DUPS_CmdBuf.Cmd_Data[0] = psNum;

      status = DUPS_DataXfer();
      DUPS_CurrPSStatus = status;
      /*Set DUPS working Preset*/
      if(status == DUPS_SUCCESS)
      {
         CurrentSetup.DUPS_WorkingPreset = (UINT16)psNum;
         IsRecalledPreset = TRUE;
      }
   }
   
   return status;
}

enum DUPS_RESULTS DUPS_MsgReqParamSetNum(void)
/********************************************************************************/
/* This function sends a command to DUPS to request a DUPS parameter set number*/ 
/********************************************************************************/

{  
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT8  i;
   UINT8  *ps;

   ps = (UINT8 *)&DUPS_CurrentParamSet;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = 0x0004;
   DUPS_CmdBuf.Cmd      = DUPS_CMDREQUESTPARAMSETNUM;  /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS)
   {
      if (DUPS_Info.ActiveWorkNum != DUPS_RspBuf.Rsp_Data[0])
      {
         DUPS_Info.ActiveWorkNum  = DUPS_RspBuf.Rsp_Data[0];
         for (i=0; i<sizeof(DUPS_CurrentParamSet); i++)  
            ps[i] = 0;                 /*clear current param set */
      }
   }
   else
   {
      DUPS_Info.ActiveWorkNum = DUPS_PARAMSETUNDEF;
      for (i=0; i<sizeof(DUPS_CurrentParamSet); i++)  
         ps[i] = 0;                              /*clear current param set */
   }
   return status;
} /* End of SINT16 DUPS_MsgRequestParamSetNum(void) */



enum DUPS_RESULTS DUPS_MsgUploadParamSet(UINT8 psNum)
/*************************************************************************************/
/* This function sends a command to DUPS to upload a parameter set and the uploaded  */ 
/* parameter values are stored in the Current Parameter set with the frequency       */ 
/* conversion values.                                                                */
/*************************************************************************************/
{  
   enum DUPS_RESULTS status             = DUPS_SUCCESS;
   UINT8  i = 0;

   DUPS_UPLOADPARAMRSP   *pc = (DUPS_UPLOADPARAMRSP *) &DUPS_RspBuf.Rsp_Data;
   DUPS_CURRENTPARAMSET  *cp = &DUPS_CurrentParamSet; 

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = 0x0005;
   DUPS_CmdBuf.Cmd      = DUPS_CMDUPLOADPARAMSET;   /* Set up command */ 
   DUPS_CmdBuf.Cmd_Data[0] = psNum;

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS)
   {  
      for(i = 0; i < DUPS_PARAMSETNAMELEN; i++)
          DUPS_ParamSetName[psNum][i] = pc -> ParameterSetName[i];
      DUPS_ParamSetName[psNum][i] = '\0';
      strcpy(DUPS_ParamSetName[DUPS_CURRPARAMSET], DUPS_ParamSetName[psNum]);

      cp->Frequency           = DUPS_FreqD2C(pc -> Frequency);
      cp->Power               = pc ->  Power;
      cp->Variant             = pc ->  Variant;
      cp->DipFlag             = 0;  //at: pc ->  Paramset. DipFlag;
   // set both source and destination SW DIPs to be sure
      cp->SWDipSetting        = pc ->  Paramset.  SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN;
      cp->SeekAmplitude       = DUPS_PerD2C(pc ->  Paramset.  SeekAmplitude);
      cp->SeekRampTime        = pc ->  Paramset.  SeekRampTime;
      cp->SeekTime            = pc ->  Paramset.  SeekTime ;
      cp->SeekFreqLimitHigh   = DUPS_FreqD2C(pc ->  Paramset.  SeekFreqLimitHigh);
      cp->SeekFreqLimitLow    = DUPS_FreqD2C(pc ->  Paramset.  SeekFreqLimitLow);
      cp->SeekPhaseLoop       = pc ->  Paramset.  SeekPhaseLoop;
      cp->SeekPhaseLoopCF     = pc ->  Paramset.  SeekPhaseLoopCF;
      cp->SeekAmplitudeLoopC1 = pc ->  Paramset.  SeekAmplitudeLoopC1;
      cp->SeekAmplitudeLoopC2 = pc ->  Paramset.  SeekAmplitudeLoopC2;
      cp->WeldAmplitude       = DUPS_PerD2C(pc ->  Paramset.  WeldAmplitude);
      cp->WeldRampTime        = pc ->  Paramset.  WeldRampTime;
      cp->WeldPhaseLoop       = pc ->  Paramset.  WeldPhaseLoop;
      cp->WeldPhaseLoopCF     = pc ->  Paramset.  WeldPhaseLoopCF;
      cp->WeldAmplitudeLoopC1 = pc ->  Paramset.  WeldAmplitudeLoopC1;
      cp->WeldAmplitudeLoopC2 = pc ->  Paramset.  WeldAmplitudeLoopC2;
      cp->WeldFreqLimitHigh   = DUPS_FreqD2C(pc ->  Paramset.  WeldFreqLimitHigh);
      cp->WeldFreqLimitLow    = DUPS_FreqD2C(pc ->  Paramset.  WeldFreqLimitLow);
      cp->WeldPhaseLimit      = pc ->  Paramset.  WeldPhaseLimit;
      cp->WeldPhaseLimitTime  = pc ->  Paramset.  WeldPhaseLimitTime;

      if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPSTOREMEMATWLDEND) /* Check for bit4 if set flag = True*/
         DUPS_Info. DUPSMemFlag = TRUE;
      else                                /*Update status in DUPS Info*/
         DUPS_Info. DUPSMemFlag = FALSE;

      if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPAUTOSEEK)/* Check for bit6 if set flag = True*/
         DUPS_Info. DUPSSeekFlag = TRUE;
      else              
         DUPS_Info. DUPSSeekFlag = FALSE;  

      if (DUPS_CurrentParamSet.SWDipSetting & DUPS_SWDIPCLEARMEMATRST) /* Check for bit3 if set flag = True*/
         DUPS_Info. DUPSMemRstFlag = TRUE;
      else                                /*Update status in DUPS Info*/
         DUPS_Info. DUPSMemRstFlag = FALSE;

   }  //if (status == DUPS_SUCCESS
   DUPS_CurrPSStatus = status;             /* DUPS manager is now available */
   IsRecalledPreset = FALSE;
   return status;
} /* End of SINT16 DUPS_MsgUploadParamSet(psNum) */

    

enum DUPS_RESULTS DUPS_MsgDownloadParamSet(UINT8 psNum)
/*************************************************************************************/
/* This function sends a command to DUPS to download the current parameter set.      */ 
/* Dependent values are converted back to DUPS units.                                */ 
/*************************************************************************************/
{  
   enum DUPS_RESULTS status            = DUPS_SUCCESS;
   UINT8 i;
   UINT8  *stptr;
   
   DUPS_DOWNLOADPARAMCMD *pc = (DUPS_DOWNLOADPARAMCMD *) &DUPS_CmdBuf.Cmd_Data;
   DUPS_CURRENTPARAMSET  *cp = &DUPS_CurrentParamSet; 

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = sizeof(DUPS_DOWNLOADPARAMCMD) + 0x0004;
   DUPS_CmdBuf.Cmd      = DUPS_CMDDOWNLOADPARAMSET;  /* Set up command */

   pc -> ParameterSetNum = psNum;

   strcpy(DUPS_ParamSetName[psNum], DUPS_ParamSetName[DUPS_CURRPARAMSET]);
   for(i = 0; i < DUPS_PARAMSETNAMELEN; i++)
       pc -> ParameterSetName[i] = DUPS_ParamSetName[psNum][i];
   
   pc->Frequency           = DUPS_FreqC2D(cp -> Frequency);
   pc->Power               = cp -> Power;
   pc->Variant             = cp -> Variant;
   

   pc->Paramset.DipFlag            = 0;  //at: cp->DipFlag;
   // set both source and destination SW DIPs to be sure
   pc->Paramset.SWDipSetting       = cp->SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN;
   pc->Paramset.SeekAmplitude      = DUPS_PerC2D(cp->SeekAmplitude);
   pc->Paramset.SeekRampTime       = cp->SeekRampTime ;
   pc->Paramset.SeekTime           = cp->SeekTime;
   pc->Paramset.SeekFreqLimitHigh  = DUPS_FreqC2D(cp->SeekFreqLimitHigh); 
   pc->Paramset.SeekFreqLimitLow   = DUPS_FreqC2D(cp->SeekFreqLimitLow);
   pc->Paramset.SeekPhaseLoop      = cp->SeekPhaseLoop;
   pc->Paramset.SeekPhaseLoopCF    = cp->SeekPhaseLoopCF;
   pc->Paramset.SeekAmplitudeLoopC1= cp->SeekAmplitudeLoopC1;
   pc->Paramset.SeekAmplitudeLoopC2= cp->SeekAmplitudeLoopC2;
   pc->Paramset.WeldAmplitude      = DUPS_PerC2D(cp->WeldAmplitude);
   pc->Paramset.WeldRampTime       = cp->WeldRampTime;
   pc->Paramset.WeldPhaseLoop      = cp->WeldPhaseLoop;
   pc->Paramset.WeldPhaseLoopCF    = cp->WeldPhaseLoopCF;
   pc->Paramset.WeldAmplitudeLoopC1= cp->WeldAmplitudeLoopC1;
   pc->Paramset.WeldAmplitudeLoopC2= cp->WeldAmplitudeLoopC2;
   pc->Paramset.WeldFreqLimitHigh  = DUPS_FreqC2D(cp->WeldFreqLimitHigh);
   pc->Paramset.WeldFreqLimitLow   = DUPS_FreqC2D(cp->WeldFreqLimitLow);
   pc->Paramset.WeldPhaseLimit     = cp->WeldPhaseLimit;
   pc->Paramset.WeldPhaseLimitTime = cp->WeldPhaseLimitTime;

   status = DUPS_DataXfer();
   DUPS_CurrPSStatus = status;               /* Now dups manager is available */
   /*Set DUPS working Preset*/
   if(status == DUPS_SUCCESS)
   {
      //CurrentSetup.DUPS_WorkingPreset = (UINT16)psNum;
      IsRecalledPreset = FALSE;
   }
   return status;
} /* End of SINT16 DUPS_MsgDownloadParamSet(psNum) */


enum DUPS_RESULTS DUPS_MsgUploadLibraryName(void)
/*************************************************************************************/
/* This function sends a command to DUPS to upload the Library name of the Parameter */ 
/* sets.                                                                             */ 
/*************************************************************************************/

{  
   enum DUPS_RESULTS status        = DUPS_SUCCESS;
   UINT8 i;
   
   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = 0x0004;
   DUPS_CmdBuf.Cmd      = DUPS_CMDUPLOADLIBRARYNAME; /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS)
   {
      for(i=0; i<DUPS_LIBRARYNAMELEN; i++)
           DUPS_Info.LibraryName[i] = DUPS_RspBuf.Rsp_Data[i];
      DUPS_Info.LibraryName[i] = '\0';
   }
   return status;
} /* End of SINT16 DUPS_MsgUploadLibraryName(void) */


enum DUPS_RESULTS DUPS_MsgDownloadLibraryName(void)
/***************************************************************************************/
/* This function sends a command to DUPS to download the Library name of the Parameter */ 
/* sets.                                                                               */ 
/***************************************************************************************/

{  
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT8 i;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = (DUPS_LIBRARYNAMELEN + 4);
   DUPS_CmdBuf.Cmd      = DUPS_CMDDOWNLOADLIBRARYNAME;      /* Set up command */
       
   for(i=0; i<DUPS_LIBRARYNAMELEN; i++) 
        DUPS_CmdBuf.Cmd_Data[i] = DUPS_Info.LibraryName[i];

   status = DUPS_DataXfer();
   return status;
} /* End of SINT16 DUPS_MsgDownloadLibraryName(void) */


enum DUPS_RESULTS DUPS_MsgUploadWeldStatus(DUPS_WELDSTATUS *outbuf)
/*************************************************************************************/
/* This function sends a command to DUPS to Upload the last weld parameters values   */ 
/* and stores it in the buffer provided by the API function with frequency dependent */   
/* conversion values.                                                                */ 
/*************************************************************************************/

{  enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT8 i;

   DUPS_RAWWELDSTATUS *inbuf = (DUPS_RAWWELDSTATUS *) &DUPS_RspBuf.Rsp_Data;
                                                 /* caller's storage in from DUPS*/

   outbuf -> OpStatus   = DUPS_PENDING;
   outbuf -> DataStatus = DUPS_PENDING;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = 0x0004;
   DUPS_CmdBuf.Cmd      = DUPS_CMDUPLOADLASTWELDSTATUS;  /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS)
   { 
      for(i = 0; i < DUPS_PARAMSETNAMELEN; i++)
           outbuf ->   ParameterSetName[i] = inbuf ->   ParameterSetName[i];
      
      outbuf -> Frequency = DUPS_Info. PowerSupplyFreq;
      outbuf -> Power     = DUPS_Info. PowerSupplyWatts;
      outbuf -> Variant   = 0;   /* As per comment from IRS */

      outbuf ->   SeekStartFrequency  = DUPS_FreqD2C(inbuf -> SeekStartFrequency);
      outbuf ->   SeekStopFrequency   = DUPS_FreqD2C(inbuf -> SeekStopFrequency);
      outbuf ->   SeekMemoryFrequency = DUPS_FreqD2C(inbuf -> SeekMemoryFrequency);
      outbuf ->   WeldStartFrequency  = DUPS_FreqD2C(inbuf -> WeldStartFrequency);
      outbuf ->   WeldStopFrequency   = DUPS_FreqD2C(inbuf -> WeldStopFrequency);
      outbuf ->   WeldMemoryFrequency = DUPS_FreqD2C(inbuf -> WeldMemoryFrequency);
      outbuf ->   WeldTime            = inbuf -> WeldTime;
      outbuf ->   WeldEnergy          = inbuf -> WeldEnergy;
      outbuf ->   Temperature         = inbuf -> Temperature;
      outbuf ->   State               = inbuf -> State;
      outbuf ->   ErrorState          = inbuf -> ErrorState;
      outbuf ->   ErrorReason         = inbuf -> ErrorReason;
      outbuf ->   ErrorFrequency      = DUPS_FreqD2C(inbuf -> ErrorFrequency);
      outbuf ->   ErrorPower          = inbuf -> ErrorPower;
      outbuf ->   ErrorCurrent        = DUPS_PerD2C(inbuf -> ErrorCurrent);
      outbuf ->   ErrorPSV            = DUPS_PerD2C(inbuf -> ErrorPSV * 8);   // 0..255 convert to 0..2047
                                                                              // might need also sign modification
      outbuf ->   ErrorAmplitude      = inbuf -> ErrorAmplitude;
      outbuf ->   ErrorTime           = inbuf -> ErrorTime;

   }
   outbuf -> OpStatus   = status;
   outbuf -> DataStatus = status;
   return status;
} /* End of SINT16 DUPS_MsgUploadWeldStatus(DUPS_WELDSTATUS *outbuf) */


enum DUPS_RESULTS DUPS_MsgUploadReleaseId(void)
/*************************************************************************************/
/* This function send a command to DUPS to Upload the release ID of DUPS and check   */ 
/* for ID = 0x1111                                                                   */ 
/*************************************************************************************/
{  
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   
   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = 0x0004;
   DUPS_CmdBuf.Cmd      = DUPS_CMDUPLOADRELEASE;  /* Set up command */

   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS)
   { 
      if( DUPS_RspBuf.Rsp_Data[0] == 0x11 && DUPS_RspBuf.Rsp_Data[1] == 0x11)
      {
         DUPS_Info.ProgramId = (DUPS_RspBuf.Rsp_Data[0] * 0x100) + DUPS_RspBuf.Rsp_Data[1];
      }
      else
         status = DUPS_OTHER;
   }  
   return status;
} /* End of SINT16 DUPS_MsgUploadReleaseId(void) */



enum DUPS_RESULTS DUPS_MsgDownloadStartScan(void)
/*****************************************************************************************/
/* This function sends a command to DUPS to start a horn scan. All input scan parameters */ 
/* are converted back to DUPS units before downloading. Also all scan output paramters   */
/* buffers are initialised.                                                              */ 
/*****************************************************************************************/

{  
   enum DUPS_RESULTS status = DUPS_SUCCESS;
   UINT16 i;
   DUPS_MSGBUF       outMsg;

   DUPS_STARTSCANCMD  *sp = (DUPS_STARTSCANCMD *) &DUPS_CmdBuf.Cmd_Data;

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = /*DUPS_CMDHEADER*/ 0x0004 + sizeof(DUPS_STARTSCANCMD);
   DUPS_CmdBuf.Cmd      = DUPS_CMDDOWNLOADSTARTSCAN;  /* Set up command */

  /* transfer the values from hornsacn info to scanparams struct */
   sp->StartFreq        =   DUPS_FreqC2D(HornScanInfo. StartFreq);
   sp->StopFreq         =   DUPS_FreqC2D(HornScanInfo. StopFreq);
   sp->FreqStep         =   DUPS_FreqC2D(HornScanInfo. FreqStep);
   sp->TimeDelay        =   HornScanInfo. TimeDelay;
   sp->MaximumAmplitude =   DUPS_PerC2D(HornScanInfo. MaximumAmplitude);
   sp->MaximumCurrent   =   DUPS_PerC2D(HornScanInfo. MaximumCurrent);
   
   status = DUPS_DataXfer();
   if (status == DUPS_SUCCESS)
   {
      ClearReady();
      for(i=0; i<= DUPS_HORNSCANMAXPOINTS; i++)
          HornScanRawCurrent[i] = 0xFFFF;
      for(i=0; i<= DUPS_HORNSCANMAXPOINTS; i++)  //  initialize temporary work area pointers
          HornScanRawPhase[i] = 0xFFFF;
      
      //  Clear the old scan data in BBram
      HornScanInfo. NumScanPoints = 0;
      for(i=0; i<=DUPS_NUMRESONANCES; i++) {  
          HornScanInfo.ResonanceFreqs[i] = 0;
          HornScanInfo.ResonanceFreqType[i] = FREQ_NONE;
          ResonanceFreqEnable[i] = 0;
      } 
      HornScanInfo. ScanStatus    = DUPS_SCANINPROG;
      UpdateScanDateandTime();

      DUPS_RAM2BBRAM();

      outMsg.data1 = HORNSCANCOLLECTING;
      outMsg.mt = DUPS_MSGHORNSCANSTEP;  /*send message */
      q_send(DupsQid, &outMsg);
   }
   else
      HornScanInfo. ScanStatus    = DUPS_NOSCAN;
   return status;
}


enum DUPS_RESULTS DUPS_MsgHornScanStep(SINT16 scanStep)
/*************************************************************************************/
/* This function processes the Scan data depending on the current state of the scan  */ 
/* i.e, HORNSCANCOLLECTING,HORNSCANCALCULATING etc.                                  */
/*************************************************************************************/

{  
   enum DUPS_RESULTS       status = DUPS_OTHER;
   DUPS_MSGBUF  outMsg;
   UINT16 i;
   switch(scanStep)  
   {
      case HORNSCANCOLLECTING:
          HornScanInfo. ScanStatus = DUPS_SCANINPROG;
          outMsg.mt = DUPS_MSGUPLOADSCANPOINT;
          q_send(DupsQid, &outMsg);
          status = DUPS_SUCCESS;
          break;

      case HORNSCANCALCULATING:
          HornScanInfo. ScanStatus = DUPS_SCANSCOMPLETE;
          ShowHSAbort = FALSE;
          HS_Resonance();
          status = DUPS_SUCCESS;
          break;

      case HORNSCANCOMPLETED:
          HS_Decimate(HornScanRawCurrent,HornScanRawPhase,(HornScanInfo.NumScanPoints - HS_NUMCOEFS),
                       HornScanCurrent,HornScanPhase);
          UpdateKeyMask(HSSUBMENUMASK);
          HornScanInfo. ScanStatus = DUPS_SCANDATAAVAIL;
          UpdateScanDateandTime();                      /* Update RTC parameters after scan*/
          SendFakeKeyPress(UPDATEDISPLAY);
          DUPS_RAM2BBRAM();
          UpdateSBL();
          status = DUPS_SUCCESS;
          break;

      case HORNSCANABORTED:
        for(i=0; i<= DUPS_HORNSCANMAXPOINTS; i++)  //  initialize temporary work area pointers
            HornScanRawCurrent[i] = 0xFFFF;
        for(i=0; i<= DUPS_HORNSCANMAXPOINTS; i++)  
            HornScanRawPhase[i] = 0xFFFF;
        
        HornScanInfo. NumScanPoints = 0;
        for(i=0; i<=DUPS_NUMRESONANCES; i++) {  
            HornScanInfo.ResonanceFreqs[i] = 0;
            HornScanInfo.ResonanceFreqType[i] = FREQ_NONE;
            ResonanceFreqEnable[i] = 0;
        } 
        HornScanInfo. ScanStatus    = DUPS_NOSCAN;
        SendFakeKeyPress(UPDATEDISPLAY);
        status = DUPS_SUCCESS;
        InitSBL();
        break;

      default:
            status = DUPS_OTHER;
            outMsg.mt = DUPS_MSGHORNSCANABORT;
            q_send(DupsQid, &outMsg);
            break;
   } /* End of switch(scanStep) */
   return status;
} /* End of SINT16 DUPS_MsgDownloadStartScan(void) */ 

    

//SINT16 DUPS_MsgHornScanAbort(void)
/**************************************************************************************/
/* This function cleans and initializes the buffers and scan parameters in case of an */ 
/* abort. CURRENTLY NOT USED IN VER8                                                  */
/**************************************************************************************/

//{  
//   UINT16 i;

//   for(i=0; i<= DUPS_HORNSCANMAXPOINTS; i++) //  initialize temporary work area pointers
//      HornScanRawCurrent[i] = 0xFFFF;
//   for(i=0; i<= DUPS_HORNSCANMAXPOINTS; i++)  
//      HornScanRawPhase[i] = 0xFFFF;
  
//   HornScanInfo. NumScanPoints = 0;
//   for(i=0; i<=DUPS_NUMRESONANCES; i++)  
//      HornScanInfo.ResonanceFreqs[i] = 0;
//   HornScanInfo. ScanStatus    = DUPS_NOSCAN;
//   return DUPS_SUCCESS;
//} /* End of DUPS_MsgHornScanAbort(void)*/

enum DUPS_RESULTS DUPS_MsgInitInterface(void)
/************************************************************************************/
/* This function does the initialization of DUPS at power up and gets the required  */ 
/* data for processing and initialises some DUPS data. This function also tells     */
/* whether DUPS is present, expected or not absent at power up.                     */ 
/************************************************************************************/

{
   enum DUPS_RESULTS       status = DUPS_OTHER;
   UINT8        i      = 0;
   UINT8       *ps, *rs;

   DUPSOkFlag = FALSE;  /* DUPS Initialization is in Progress */
   
   DUPS_BBRAM2RAM();  /* initialise data in RAM from BBRAM at power up*/
   
   while( ( i++ < DUPS_INITTRIES) && (status != DUPS_SUCCESS) )
   {
      status = DUPS_MsgUploadReleaseId();
   }
   if (status == DUPS_SUCCESS)
      status = DUPS_MsgUploadSWId();
   if (status == DUPS_SUCCESS)
      status = DUPS_MsgUploadHWId();

//   HornScanInfo. StartFreq        =  DUPS_FreqD2C(HS_MinScanInfo. StartFreq);
//   HornScanInfo. StopFreq         =  DUPS_FreqD2C(HS_MaxScanInfo. StopFreq);
//   HornScanInfo. FreqStep         =  DUPS_FreqD2C(HS_MinScanInfo. FreqStep);
   HornScanInfo.FreqStep          =  HS_MinScanInfo.FreqStep; 
   HornScanInfo. TimeDelay        =  HS_MinScanInfo. TimeDelay;
   HornScanInfo. MaximumAmplitude =  HS_MinScanInfo. MaximumAmplitude;
   HornScanInfo. MaximumCurrent   =  HS_MinScanInfo. MaximumCurrent;

      
   if (status == DUPS_SUCCESS)
      status = DUPS_MsgUploadLibraryName();

   /*
        This section uploads each parameter set to obtain the parameter set name.  The last
        parameter set is reserved, by convention, to be the DUPS Current Parameter Set.
        As long as the convention is followed this will result in the curremt parameter set
        being valid at the end of the loop.  If the convention is changed then you will have
        to reload DUPS_CURRPARAMSET after this loop.
   */
   i=0;
   while(( i < DUPS_NUMPARAMSET) && (status == DUPS_SUCCESS))
   {
      status = DUPS_MsgUploadParamSet(i);
      i++;
   } 
      
   /* First time Battram contains some illegal Values, then set
   working preset to permissible limit */
   if(CurrentSetup.DUPS_WorkingPreset >= DUPS_NUMPARAMSET ||
      CurrentSetup.DUPS_WorkingPreset < 0)
      CurrentSetup.DUPS_WorkingPreset = DUPS_NUMPARAMSET - 1;
      
   if (status == DUPS_SUCCESS)
      status = DUPS_MsgSelectParamSetNum((UINT8)CurrentSetup.DUPS_WorkingPreset);
   
   if (status == DUPS_SUCCESS)
      status = DUPS_MsgUploadParamSet((UINT8)CurrentSetup.DUPS_WorkingPreset);
   /*
       At this point all of the actions for initialization have been tried.  Now we need to
       check for the results.
   */  
   if (status == DUPS_SUCCESS)
   {
        CurrentSetup.PSType = TRUE;           // DUPS is present and working
        DUPS_Info.DUPSFlag  = TRUE;           // DUPS is up
        DUPS_RAM2BBRAM();
        UpdateHWConfiguration(DUPS, TRUE);
        StorePSFrequency();          /* update novram with DUPS frequency setting */
        SetMaxMinValues();           /* Update Min/Max based on new setting */
        StorePSWattage();              /* update novram with DUPS wattage setting */
   }
   else                                     // no DUPS detected
   {
      DUPS_Info.DUPSFlag = FALSE;           // DUPS is not up
      if (CurrentSetup.PSType == TRUE)  // DUPS expected but failed
      {
        UpdateHWConfiguration(DUPS, FALSE);
        RecordAlarm(EQ15);
      }
      else
      {
         status = DUPS_SUCCESS;         // no error if DUPS not expected
         UpdateHWConfiguration(DUPS, FALSE);
      } 
   }
   DUPSOkFlag = TRUE;      /* DUPS Initialization is Completed */
   return status;
}   // end of DUPS_MsgInitInterface(void)



SINT32 DUPS_FreqC2D(SINT32 COPFreq)
/**********************************************************************************/
/* This function converts the frequency dependent values from COPS to DUPS        */ 
/**********************************************************************************/

{
   return ((COPFreq * 40) / DUPS_Info.FreqConversion);
} // end of DUPS_FreqC2D(SINT32 COPFreq)



SINT32 DUPS_FreqD2C(SINT32 DUPSFreq)
/**********************************************************************************/
/* This function converts the frequency dependent values from DUPS to COPS        */ 
/**********************************************************************************/
{
   return ((DUPSFreq * DUPS_Info.FreqConversion)/ 40 );
} // end of DUPS_FreqD2C(SINT32 DUPSFreq)



SINT32 DUPS_PerD2C(SINT32 DUPSPer)
/**********************************************************************************/
/* This function converts the percentage dependent values from DUPS to COPS        */ 
/**********************************************************************************/

{
   return ((DUPSPer * 100 + 1023)/ 2047 );
} // end of DUPS_PerD2C()



SINT32 DUPS_PerC2D(SINT32 COPPer)
/**********************************************************************************/
/* This function converts the percentage dependent values from COPS to DUPS        */ 
/**********************************************************************************/

{
   return ((COPPer * 2047 + 49)/ 100 );
} // end of DUPS_PerC2D()



void UpdateScanDateandTime(void)
/**********************************************************************************/
/* THis function updates the time, date, year and month after a scan is complete  */ 
/**********************************************************************************/

{
   RTC HS_Time;
   
   HS_Time = RtcReadDateandTime();

   HornScanInfo.Year   = HS_Time.Year;
   HornScanInfo.Month  = HS_Time.Month;
   HornScanInfo.Day    = HS_Time.Day;
   HornScanInfo.Hour   = HS_Time.Hour;
   HornScanInfo.Minute = HS_Time.Minute;
} /* end of func  UpdateScanDateandTime(void)*/


void InitSBL(void)
/**********************************************************************************/
/* Set up initial SBL values (Horn scan will override them).                      */ 
/**********************************************************************************/
{
   UINT16 Offset;
   SINT32 TempPSFreq;

   Offset = GetPowerSupplyFrequencyOffset();
   TempPSFreq = GetPowerSupplyFrequency();
   CurrentPreset.SBLMinFreqLim = TempPSFreq - Offset;
   CurrentPreset.SBLMaxFreqLim = TempPSFreq + Offset;
   CurrentPreset.SBLMinFreq = CurrentPreset.SBLMinFreqLim;
   CurrentPreset.SBLMaxFreq = CurrentPreset.SBLMaxFreqLim;
   CurrentPreset.SBLFreqFlags = 0x03;  //Both + and - SBL flags are off
}

void UpdateSBL(void)
/**********************************************************************************/
/* Update SBL values based on horn scan results                                   */
/**********************************************************************************/
{
   UINT8 i;
   UINT16 ResFreq, MinSerFreq, MaxSerFreq;
   UINT32 Diff;

   ResFreq = 0;
   for (i = 0; i < DUPS_NUMRESONANCES; i++)
      {
      if (HornScanInfo.ResonanceFreqType[i] == FREQ_PARALLEL)
         ResFreq = HornScanInfo.ResonanceFreqs[i];
      }
   // What if we didn't get any parallel frequencies?
   if (ResFreq == 0)
      ResFreq = GetPowerSupplyFrequency();
   // Get minimum series frequency
   MinSerFreq = GetPowerSupplyFrequency() - GetPowerSupplyFrequencyOffset();
   for (i = 0; i < DUPS_NUMRESONANCES; i++)
      {
      if ((HornScanInfo.ResonanceFreqType[i] == FREQ_SERIES) &&
          (HornScanInfo.ResonanceFreqs[i] < ResFreq) &&
          (HornScanInfo.ResonanceFreqs[i] > MinSerFreq))
         MinSerFreq = HornScanInfo.ResonanceFreqs[i];
      }
   // Same for maximum frequency
   MaxSerFreq = GetPowerSupplyFrequency() + GetPowerSupplyFrequencyOffset();
   for (i = 0; i < DUPS_NUMRESONANCES; i++)
      {
      if ((HornScanInfo.ResonanceFreqType[i] == FREQ_SERIES) &&
          (HornScanInfo.ResonanceFreqs[i] > ResFreq) &&
          (HornScanInfo.ResonanceFreqs[i] < MaxSerFreq))
         MaxSerFreq = HornScanInfo.ResonanceFreqs[i];
      }
   // Done, let's store them
   //CurrentPreset.SBLParFreq = ResFreq;
   // Either the min PS freq, or 90% of the way from parallel freq to series
   if (MinSerFreq == GetPowerSupplyFrequency() - GetPowerSupplyFrequencyOffset())
      {
      CurrentPreset.SBLMinFreqLim = MinSerFreq;
      }
   else
      {
      Diff = ResFreq - MinSerFreq;
      Diff *= 90;
      Diff /= 100;
      CurrentPreset.SBLMinFreqLim = ResFreq - Diff;
      }
   // Either the max PS freq, or 90% of the way from parallel freq to series
   if (MaxSerFreq == GetPowerSupplyFrequency() + GetPowerSupplyFrequencyOffset())
      {
      CurrentPreset.SBLMaxFreqLim = MaxSerFreq;
      }
   else
      {
      Diff = MaxSerFreq - ResFreq;
      Diff *= 90;
      Diff /= 100;
      CurrentPreset.SBLMaxFreqLim = ResFreq + Diff;
      }
   CurrentPreset.SBLMinFreq = CurrentPreset.SBLMinFreqLim;
   CurrentPreset.SBLMaxFreq = CurrentPreset.SBLMaxFreqLim;
   CurrentPreset.SBLFreqFlags = 0x00;  //Both + and - SBL are made ON
}

void VerifySBL(void)
{
   if (CurrentSequence == WELD)
   {
      if ((CurrentFreqIn < RunningPreset.SBLMinFreq) && !(SBLMinLimitReached))
	  {
         SBLMinLimitReached = TRUE;
		 ActualSBLMinFreq = CurrentFreqIn;
      }
      if ((CurrentFreqIn > RunningPreset.SBLMaxFreq) && !(SBLMaxLimitReached))
	  {
         SBLMaxLimitReached = TRUE;
		 ActualSBLMaxFreq = CurrentFreqIn;
	  }
   }
}

BOOLEAN DUPS_HostUploadParamSet(UINT8 psNum)
/*************************************************************************************/
/* This function sends a command to DUPS to upload a parameter set and the uploaded  */ 
/* parameter values are stored in the host Parameter set with the frequency          */ 
/* conversion values.                                                                */
/*************************************************************************************/
{  
   enum DUPS_RESULTS status             = DUPS_SUCCESS;
   BOOLEAN Flag = TRUE;
   UINT8  i = 0;
   UINT16 DUPS_paramsetno;

   DUPS_UPLOADPARAMRSP   *pc = (DUPS_UPLOADPARAMRSP *) &DUPS_RspBuf.Rsp_Data;
   DUPS_CURRENTPARAMSET  *cp = &DUPS_HostParamSet; 

   if ((DUPS_paramsetno = DUPS_FindDUPS4COP((UINT16)psNum)) == DUPS_PARAMSETUNDEF)
      Flag = FALSE;
   else
   {   
      DUPS_CmdBuf.DLE_Byte = DLE;
      DUPS_CmdBuf.STX_Byte = STX;
      DUPS_CmdBuf.Count    = 0x0005;
      DUPS_CmdBuf.Cmd      = DUPS_CMDUPLOADPARAMSET;   /* Set up command */ 
      DUPS_CmdBuf.Cmd_Data[0] = (UINT8)DUPS_paramsetno;

      status = DUPS_DataXfer();
      if (status == DUPS_SUCCESS)
      {  
         for(i = 0; i < DUPS_PARAMSETNAMELEN; i++)
             DUPS_HostParamSetName[i] = pc -> ParameterSetName[i];
         DUPS_HostParamSetName[i] = '\0';

         cp->Frequency           = DUPS_FreqD2C(pc -> Frequency);
         cp->Power               = pc ->  Power;
         cp->Variant             = pc ->  Variant;
         cp->DipFlag             = 0;  //at: pc ->  Paramset. DipFlag;
      // set both source and destination SW DIPs to be sure
         cp->SWDipSetting        = pc ->  Paramset.  SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN;
         cp->SeekAmplitude       = DUPS_PerD2C(pc ->  Paramset.  SeekAmplitude);
         cp->SeekRampTime        = pc ->  Paramset.  SeekRampTime;
         cp->SeekTime            = pc ->  Paramset.  SeekTime ;
         cp->SeekFreqLimitHigh   = DUPS_FreqD2C(pc ->  Paramset.  SeekFreqLimitHigh);
         cp->SeekFreqLimitLow    = DUPS_FreqD2C(pc ->  Paramset.  SeekFreqLimitLow);
         cp->SeekPhaseLoop       = pc ->  Paramset.  SeekPhaseLoop;
         cp->SeekPhaseLoopCF     = pc ->  Paramset.  SeekPhaseLoopCF;
         cp->SeekAmplitudeLoopC1 = pc ->  Paramset.  SeekAmplitudeLoopC1;
         cp->SeekAmplitudeLoopC2 = pc ->  Paramset.  SeekAmplitudeLoopC2;
         cp->WeldAmplitude       = DUPS_PerD2C(pc ->  Paramset.  WeldAmplitude);
         cp->WeldRampTime        = pc ->  Paramset.  WeldRampTime;
         cp->WeldPhaseLoop       = pc ->  Paramset.  WeldPhaseLoop;
         cp->WeldPhaseLoopCF     = pc ->  Paramset.  WeldPhaseLoopCF;
         cp->WeldAmplitudeLoopC1 = pc ->  Paramset.  WeldAmplitudeLoopC1;
         cp->WeldAmplitudeLoopC2 = pc ->  Paramset.  WeldAmplitudeLoopC2;
         cp->WeldFreqLimitHigh   = DUPS_FreqD2C(pc ->  Paramset.  WeldFreqLimitHigh);
         cp->WeldFreqLimitLow    = DUPS_FreqD2C(pc ->  Paramset.  WeldFreqLimitLow);
         cp->WeldPhaseLimit      = pc ->  Paramset.  WeldPhaseLimit;
         cp->WeldPhaseLimitTime  = pc ->  Paramset.  WeldPhaseLimitTime;

      }  //if (status == DUPS_SUCCESS
      if (status != DUPS_SUCCESS)
         Flag = FALSE;
   }   
   return Flag;
} /* End of SINT16 DUPS_HostMsgUploadParamSet(psNum) */

BOOLEAN DUPS_HostDownloadParamSet(UINT8 psNum)
/*************************************************************************************/
/* This function sends a command to DUPS to download the host parameter set.         */ 
/* Dependent values are converted back to DUPS units.                                */ 
/*************************************************************************************/
{  
   enum DUPS_RESULTS status            = DUPS_SUCCESS;
   UINT8 i;
   UINT8  *stptr;
   BOOLEAN Flag = TRUE;
   
   DUPS_DOWNLOADPARAMCMD *pc = (DUPS_DOWNLOADPARAMCMD *) &DUPS_CmdBuf.Cmd_Data;
   DUPS_CURRENTPARAMSET  *cp = &DUPS_HostParamSet; 

   DUPS_CmdBuf.DLE_Byte = DLE;
   DUPS_CmdBuf.STX_Byte = STX;
   DUPS_CmdBuf.Count    = sizeof(DUPS_DOWNLOADPARAMCMD) + 0x0004;
   DUPS_CmdBuf.Cmd      = DUPS_CMDDOWNLOADPARAMSET;  /* Set up command */

   pc -> ParameterSetNum = psNum;

   for(i = 0; i < DUPS_PARAMSETNAMELEN; i++)
       pc -> ParameterSetName[i] = DUPS_HostParamSetName[i];
   
   pc->Frequency           = DUPS_FreqC2D(cp -> Frequency);
   pc->Power               = cp -> Power;
   pc->Variant             = cp -> Variant;
   

   pc->Paramset.DipFlag            = 0;  //at: cp->DipFlag;
   // set both source and destination SW DIPs to be sure
   pc->Paramset.SWDipSetting       = cp->SWDipSetting |= DUPS_SWDIPAMPLITUDEEXTERN;
   pc->Paramset.SeekAmplitude      = DUPS_PerC2D(cp->SeekAmplitude);
   pc->Paramset.SeekRampTime       = cp->SeekRampTime ;
   pc->Paramset.SeekTime           = cp->SeekTime;
   pc->Paramset.SeekFreqLimitHigh  = DUPS_FreqC2D(cp->SeekFreqLimitHigh); 
   pc->Paramset.SeekFreqLimitLow   = DUPS_FreqC2D(cp->SeekFreqLimitLow);
   pc->Paramset.SeekPhaseLoop      = cp->SeekPhaseLoop;
   pc->Paramset.SeekPhaseLoopCF    = cp->SeekPhaseLoopCF;
   pc->Paramset.SeekAmplitudeLoopC1= cp->SeekAmplitudeLoopC1;
   pc->Paramset.SeekAmplitudeLoopC2= cp->SeekAmplitudeLoopC2;
   pc->Paramset.WeldAmplitude      = DUPS_PerC2D(cp->WeldAmplitude);
   pc->Paramset.WeldRampTime       = cp->WeldRampTime;
   pc->Paramset.WeldPhaseLoop      = cp->WeldPhaseLoop;
   pc->Paramset.WeldPhaseLoopCF    = cp->WeldPhaseLoopCF;
   pc->Paramset.WeldAmplitudeLoopC1= cp->WeldAmplitudeLoopC1;
   pc->Paramset.WeldAmplitudeLoopC2= cp->WeldAmplitudeLoopC2;
   pc->Paramset.WeldFreqLimitHigh  = DUPS_FreqC2D(cp->WeldFreqLimitHigh);
   pc->Paramset.WeldFreqLimitLow   = DUPS_FreqC2D(cp->WeldFreqLimitLow);
   pc->Paramset.WeldPhaseLimit     = cp->WeldPhaseLimit;
   pc->Paramset.WeldPhaseLimitTime = cp->WeldPhaseLimitTime;

   status = DUPS_DataXfer();
   if(status != DUPS_SUCCESS)
   {
      Flag = FALSE;
   }
   return Flag;
} /* End of SINT16 DUPS_HostDownloadParamSet(psNum) */

void UpdateDUPS_MaxWeldFreqLimit(void)
/*************************************************************************************/
/* This function changes maximum limit of  WeldFreqLimitHigh and WeldFreqLimitLow    */ 
/* of DUPS_CURRENTPARAMSET according to PSfrequency.                                 */ 
/*************************************************************************************/
{
   switch (CurrentSetup.PSFreq)
   {
      case FREQ15KHZ:
         DUPS_MaxParamSet.WeldFreqLimitHigh = 375;
         DUPS_MaxParamSet.WeldFreqLimitLow = 375;
         break;
      case FREQ30KHZ:
         DUPS_MaxParamSet.WeldFreqLimitHigh = 750;
         DUPS_MaxParamSet.WeldFreqLimitLow = 750;
         break;
      case FREQ40KHZ:
         DUPS_MaxParamSet.WeldFreqLimitHigh = 1000;
         DUPS_MaxParamSet.WeldFreqLimitLow = 1000;
         break;   
      case FREQ60KHZ:
         DUPS_MaxParamSet.WeldFreqLimitHigh = 1500;
         DUPS_MaxParamSet.WeldFreqLimitLow = 1500;
         break;   
      case FREQ20KHZ:
      default:
         DUPS_MaxParamSet.WeldFreqLimitHigh = 500;
         DUPS_MaxParamSet.WeldFreqLimitLow = 500;
         break;
   }
}