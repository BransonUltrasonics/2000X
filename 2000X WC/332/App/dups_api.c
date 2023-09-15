/* $Header:   D:/databases/VMdb/2000Series/App/dups_api.c_v   1.54.1.2   Dec 14 2017 12:36:32   RCHAPA  $ */
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
                                          
   Module name:   DUPS API

   Filename:      dups_api.c

   Function name: 

            Written by: Sunil Patil 
                  Date: 6/13/00
              Language:  "C"                              


----------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author  Description
   ==========   ========   ======  ===========
       1.0      06/21/00   SRP     Initial Version
       1.1      06/23/00   SRP     Modifications as per Part-II spec.
       1.2      06/30/00   SRP     Modifications as per Part-II spec.
       1.3      06/30/00   SRP     Modified after code review.
       1.4      07/07/00   SRP     Checked in for complete build.        
       1.5      07/11/00   SRP     Memflag and seekflag logic implemented.
       1.6      07/14/00   SRP     BBRAM 800 declarations updated.
       1.7      07/14/00   SRP     BBRAM800 stuff defined as global and made extern in api.h
       1.8      07/18/00   SCM     Fixed the HORN_SCANMAXIMUMAMPLITUDE parameter.
       1.9      07/18/00   SRP     -> is peplaced by . at DUps_info and horninfo.
       1.10     07/18/00   SRP     Max and min struct define added for paramset and HSlimits 
       1.11     07/18/00   SCM     Fixed some syntax errors associated with the DUPS compile.
       1.12     07/19/00   SCM     Added the DUPS_ParamSetName[] array.
       1.13     07/19/00   SRP     Maxparamset and Minimum values added. Downloadparamset function added.
       1.14     07/21/00   SRP     One more character added in dupsparamsetname string to make it 20.
       1.15     07/22/00   SCM     Deleted the function DUPS_DownloadHornScan().
       1.16     07/25/00   SCM     Changed the prototype definitions of DUPS_ClearDUPSParamSet(),
                                   DUPS_FindCOP4DUPS() and DUPS_FindDUPS4COP() funcs.
       1.17     08/01/00   SRP     Max and Min Parameter value changed.STR *DUPS_PsNamePTR and chkparamlimits fun added.
       1.18     08/02/00   SRP     StartScan fun made void. Fun Selectparamset made as uploadparamset.
       1.19     08/03/00   SRP     SINT32 psNum changed to UINT16 in DUPS_UploadParamSet(UINT16 psNum)
       1.20     08/03/00   SRP     In fun  DUPS_DownloadParamSet( void) = made == in if check for status.
       1.21     08/04/00   SRP     HornScanInfo.FreqStep checked for min value of 10. But again it is made 1.
                                   Hornscanabort fun added.
       1.22     08/11/00   RBH     Save/Recall Preset corrections. 
       1.23     08/11/00   RBH     Added DUPS_Wait4CurrPS().  
       1.24     08/12/00   SCM     Modified DUPS_Wait4CurrPS() and added functions DUPS_BBRAM2RAM() and
                                   DUPS_RAM2BBRAM().
       1.25     08/14/00   AT      Copy DUPS_Lock data to DUPS_LockTemp in DUPS_BBRAM2RAM()
       1.26     08/16/00   RBH     Correct Min/Max Seek Time and Seek Ramp Time to SRS values
       1.27     08/16/00   RBH     Corrections to Save/Recall presets and Parameter Sets 
       1.28     08/17/00   AT      DUPS_StartHornScan - clear resonance frequencies before scan
       1.29     08/28/00   SCM     Added the code to disable all keys except the GoBackKey at the 
                                   start of an HORNSCAN.
       1.31     08/29/00   AT      DUPSMemFlag depends on DUPS_SWDIPSTOREMEMATWLDEND
                                   Changed Max preset frequency limits from 500 to 1000 (40kHz DUPS)
       1.32     08/29/00   AT      Changed FreqStep calculation for horn scan
       1.33     08/29/00   AT      Changed COP2DUPS to MAX_PRESETS + 1, replaced some constants with sizeof
       1.34     09/01/00   SRP     DUPS_CurrPSStatus = DUPS_PENDING added in uploadparam func.
       1.35     09/05/00   LAM     made min ramptime = 10ms.
       1.36     09/07/00   SRP     Cleaning and touch up. Comments , Function description added.
       1.37     09/11/00   SCM     General clean up.
       1.38     09/28/00   AT      Cleanup after code review.
       1.39     10/03/00   LAM     Need to save OL during hornscan Issue(3597)
       1.40     10/04/00   AT      added DUPS_QueuedDownloadPS
       1.41     10/05/00   AT      added enum DUPS_CHANGE DUPS_Change
       1.42     10-05-00   BEKymer Modify DUPS_QueuedDownloadPS to handle DUPS
                                    communication requests during ready.
                                    for a partial fix for issue #3592
       1.43     10-09-00   AT      Added DUPS_QueuedUploadPS 
       1.44     10-10-00   AT      Don't clear DUPSChangePending in Upload (need to download as well)
       1.45     10-11-00   AT      Replaced SINT16 with enum DUPS_RESULTS for status
       1.45.1.1 07-03-03   JOY     Following flags are cleared at the begining of Horn Scan
                                   in 'DUPS_StartHornScan()'.
                                   'DupsOkFlag', 'QVGAHornScanOLD', 'ResonanceFreqType'. 
       1.45.1.2 09-08-03   JOY     'RESONANCE_FREQ_TYPE', is moved to 'HORNSCAN_INFO'. 
       1.46     01-09-01   BEkymer Added argument to all functions that are called from
                                    TEXT or SUBMENU menu structure.
       1.47     12-02-03   BEKymer Merged 1.46 & 1.45.1.2 to create 1.47 for
                                    Ver9.00b build
       1.48     02-02-04   VSharma  Called function ChangeDUPSSubParamList() from the
                                    DUPS_ModifySWDipSetting().                                   
       1.49     04-06-04   VSharma  Modified DUPS_StartHornScan().
       1.50     05-18-04   VSharma  Modified DUPS_DownloadCurrPS().
       1.51     08-04-04   JOY      DUPS_CurrPSStatus = DUPS_PENDING added in DUPS_SelectParamSetNum().
       1.52     07-25-05   Bwadia   Added asian language support for DUPS_ParamSetName
                                    string
       1.53     01-12-06   Bwadia   HS_MaxScanInfo and HS_MinScanInfo made variable
                                    Modified for tracker 3966 
       1.54     02-22-06   Bwadia   Memory reset flag added to SWDipsetting variable
                                    Modified for tracker issue 4077      
       1.55     04-14-08   NHAhmed  Added function DUPS_StartHS 
	   1.54.1.2   	07-21-17   RChapa  Update DUPS Parameters on an External Preset for Ramp Time.
*/ 

/*------------------------------ DESCRIPTION -------------------------------*/

/* 
   This file has the DUPS API functions. Any data exchange with the DUPS is
   handled by one of these functions.
   
*/


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "dups_api.h"
#include <psos.h>
#include "dups.h"
#include "param.h"
#include "battram.h"
#include "preset.h"
#include "string.h"
#include "fpk_task.h"
#include "state.h"
#include "statedrv.h"
#include "menu7a.h"
/*---------------------------- EXTERNAL DATA -------------------------------*/

extern UINT32      DupsQid;
extern UINT16      DUPS_LockTemp[DUPS_NUMPARAMSET];
extern BOOLEAN HornScanOL;
extern enum  WELDSTATES WeldState;
extern BOOLEAN HSNotStarted;
extern BOOLEAN QVGAHornScanOLD;

/*----------------------------- LOCAL DEFINES ------------------------------*/


/*----------------------- LOCAL TYPE DECLARATIONS --------------------------*/

 void ChangeDUPSSubParamList(void);

/*----------------------------- GLOBAL DATA --------------------------------*/
DUPS_WELDSTATUS DUPS_WeldStatus;           /* Declare the DUPS Weld parameter struct */
DUPS_CURRENTPARAMSET DUPS_CurrentParamSet; /* Declare the DUPS Current parameter struct */ 
SINT16  DUPS_CurrPSStatus;                 /* Set to Pending for upload, DUPS_SUCCESS when complete*/

DUPS_MSGBUF DUPS_MsgBuf; /* Delcare the DUPS message buffer struct */
HS_LIMITS HS_Limits;     /* Delcare the hornscan parameters limits struct */

DUPS_STARTSCANCMD DUPS_StartScanCmd; /* Declare the DUPS horn scan command struct */

DUPS_INFO DUPS_Info;       /* Declare the DUPS information struct*/
HORNSCANINFO HornScanInfo; /* Declare the Hornscan Info struct */

/* These are the maximum value limits for the DUPS Parameters*/
DUPS_CURRENTPARAMSET DUPS_MaxParamSet = 
{      0,            /* Freq */
       0,            /* power*/
       0,            /* Varient */
       1,            /* DUPS_DIPFLAG */   
       0xFC,         /* DUPS_SWDIPSETTING  */
       100,          /* DUPS_SEEKAMPLITUDE*/
       1000,         /* DUPS_SEEKRAMPTIME milliseconds*/
       1000,         /* DUPS_SEEKTIME  milliseconds*/
       1000,          /* DUPS_SEEKFLIMH  hertz  */
       1000,          /* DUPS_SEEKFLIML hertz */
       500,          /* DUPS_SEEKPHLOOPI */
       500,          /* DUPS_SEEKPHLOOPCF */
       500,          /* DUPS_SEEKAMPLOOPC1 */
       500,          /* DUPS_SEEKAMPLOOPC2 */
       100,          /* DUPS_WELDAMPLITUDE*/
       1000,         /* DUPS_WELDRAMPTIME */
       500,          /* DUPS_WELDPHLOOPI */
       500,          /* DUPS_WELDPHLOOPCF  */
       500,          /* DUPS_WELDAMPLOOPC1 */
       500,          /* DUPS_WELDAMPLOOPC2 */
       1000,          /* DUPS_WELDFLIMH  hertz   */
       1000,          /* DUPS_WELDFLIML  hertz   */
       2000,         /* DUPS_WELDPHLIM*/
       2000          /* DUPS_WELDPHLIMTIME  milliseconds*/
}; /* End of DUPS_MaxParamSet struct */

/* These are the minimum value limits for the DUPS Parameters*/
DUPS_CURRENTPARAMSET DUPS_MinParamSet =
{      0,            /* Freq */
       0,            /* power*/
       0,            /* Varient */
       0,            /* DUPS_DIPFLAG */   
       0,            /* DUPS_SWDIPSETTING  */
       1,            /* DUPS_SEEKAMPLITUDE*/
       1,            /* DUPS_SEEKRAMPTIME milliseconds*/
       100,          /* DUPS_SEEKTIME  milliseconds*/
       1,            /* DUPS_SEEKFLIMH  hertz  */
       1,            /* DUPS_SEEKFLIML hertz */
       50,           /* DUPS_SEEKPHLOOPI */
       50,           /* DUPS_SEEKPHLOOPCF */
       100,          /* DUPS_SEEKAMPLOOPC1 */
       100,          /* DUPS_SEEKAMPLOOPC2 */
       1,            /* DUPS_WELDAMPLITUDE*/
       10,           /* DUPS_WELDRAMPTIME */
       50,           /* DUPS_WELDPHLOOPI */
       50,           /* DUPS_WELDPHLOOPCF  */
       100,          /* DUPS_WELDAMPLOOPC1 */
       100,          /* DUPS_WELDAMPLOOPC2 */
       1,            /* DUPS_WELDFLIMH  hertz   */
       1,            /* DUPS_WELDFLIML  hertz   */
       1,            /* DUPS_WELDPHLIM*/
       1             /* DUPS_WELDPHLIMTIME  milliseconds*/
}; /* End of DUPS_MinParamSet struct */

/* This struct defines horn scan parameters maximum values */
HORNSCANINFO HS_MaxScanInfo =  {  204500,    /* StartFreq */
                                  204500,    /* StopFreq */
								  50,        /* FreqStep*/
                                  //100,       /* FreqStep*/
                                  100,       /* TimeDelay */
                                  50,        /* MaximumAmplitude*/
                                  50};       /* MaximumCurrent*/

/* This struct defines horn scan parameters minimum values */
HORNSCANINFO HS_MinScanInfo =  {  194500,    /* StartFreq */
                                  194500,    /* StopFreq */
								  1,         /* FreqStep */
                                  //10,        /* FreqStep*/
                                  10,        /* TimeDelay */
                                  10,        /* MaximumAmplitude*/
                                  10};       /* MaximumCurrent*/

/* These arrays will be used to find DUPS Paramset and COPs Preset assigned, Locked and saved*/
UINT8  DUPS2COP[DUPS_NUMPARAMSET];  /* DUPS_NUMPARAMSET */
UINT8  COP2DUPS[MAX_PRESETS + 1];   /*MAX_PRESETS*/
UINT16 DUPS_Lock[DUPS_NUMPARAMSET]; /*Avail,Locked,Saved*/

/* Location in BBRAM to store Hornscan Current and phase points uploaded from DUPS, Filterd 
and decimated - used for printing graph*/
SINT16 *HornScanCurrent = (SINT16 *)BBR800_HORNGRAPH_START + (2 * DUPS_HORNSCANPOINTS); /*DUPS_HORNSCANPOINTS*/
SINT16 *HornScanPhase = (SINT16 *)BBR800_HORNGRAPH_START;

/* This stores the param set names for DUPS */
STR DUPS_ParamSetName[DUPS_NUMPARAMSET][DUPS_PARAMSETNAMELEN + 1] =  
                           { "ParamSet1Nameabcdefg",
                             "ParamSet2Name       ",
                             "ParamSet3Name       ",
                             "ParamSet4Name       ",
                             "ParamSet5Name       ",
                             "ParamSet6Name       ",
                             "ParamSet7Name       ",
                             "ParamSet8Name       ",
                             "ParamSet9Name       ",
                             "ParamSet10Name      ",
                             "ParamSet11Name      ",
                             "ParamSet12Name      ",
                             "ParamSet13Name      ",
                             "ParamSet14Name      ",
                             "ParamSet15Name      ",
                             "ParamSet16Name      ",
                             "ParamSet17Name      ",
                             "ParamSet18Name      ",
                             "ParamSet19Name      ",
                             "ParamSet20Name      "  };
                             
                            
/* This points the parameter set names for DUPS in each language */
STR * const DUPS_PsNamePTR[DUPS_NUMPARAMSET][LANGUAGE_MAX] =
                         {
                            {  
                               DUPS_ParamSetName[0],
                               DUPS_ParamSetName[0],
                               DUPS_ParamSetName[0],
                               DUPS_ParamSetName[0],
                               DUPS_ParamSetName[0],
                               DUPS_ParamSetName[0],
                               DUPS_ParamSetName[0],
                               DUPS_ParamSetName[0],
                               DUPS_ParamSetName[0]
                            },

                            {  
                               DUPS_ParamSetName[1],
                               DUPS_ParamSetName[1],
                               DUPS_ParamSetName[1],
                               DUPS_ParamSetName[1],
                               DUPS_ParamSetName[1],
                               DUPS_ParamSetName[1],
                               DUPS_ParamSetName[1],
                               DUPS_ParamSetName[1],
                               DUPS_ParamSetName[1]
                            },
                            {  
                               DUPS_ParamSetName[2],
                               DUPS_ParamSetName[2],
                               DUPS_ParamSetName[2],
                               DUPS_ParamSetName[2],
                               DUPS_ParamSetName[2],
                               DUPS_ParamSetName[2],
                               DUPS_ParamSetName[2],
                               DUPS_ParamSetName[2],
                               DUPS_ParamSetName[2]
                            },

                            {  
                               DUPS_ParamSetName[3],
                               DUPS_ParamSetName[3],
                               DUPS_ParamSetName[3],
                               DUPS_ParamSetName[3],
                               DUPS_ParamSetName[3],
                               DUPS_ParamSetName[3],
                               DUPS_ParamSetName[3],
                               DUPS_ParamSetName[3],
                               DUPS_ParamSetName[3]
                            },

                            {  
                               DUPS_ParamSetName[4],
                               DUPS_ParamSetName[4],
                               DUPS_ParamSetName[4],
                               DUPS_ParamSetName[4],
                               DUPS_ParamSetName[4],
                               DUPS_ParamSetName[4],
                               DUPS_ParamSetName[4],
                               DUPS_ParamSetName[4],
                               DUPS_ParamSetName[4]
                            },

                            {  
                               DUPS_ParamSetName[5],
                               DUPS_ParamSetName[5],
                               DUPS_ParamSetName[5],
                               DUPS_ParamSetName[5],
                               DUPS_ParamSetName[5],
                               DUPS_ParamSetName[5],
                               DUPS_ParamSetName[5],
                               DUPS_ParamSetName[5],
                               DUPS_ParamSetName[5]
                            },
                            {  
                               DUPS_ParamSetName[6],
                               DUPS_ParamSetName[6],
                               DUPS_ParamSetName[6],
                               DUPS_ParamSetName[6],
                               DUPS_ParamSetName[6],
                               DUPS_ParamSetName[6],
                               DUPS_ParamSetName[6],
                               DUPS_ParamSetName[6],
                               DUPS_ParamSetName[6]
                            },
                            {  
                               DUPS_ParamSetName[7],
                               DUPS_ParamSetName[7],
                               DUPS_ParamSetName[7],
                               DUPS_ParamSetName[7],
                               DUPS_ParamSetName[7],
                               DUPS_ParamSetName[7],
                               DUPS_ParamSetName[7],
                               DUPS_ParamSetName[7],
                               DUPS_ParamSetName[7]
                            },
                            {  
                               DUPS_ParamSetName[8],
                               DUPS_ParamSetName[8],
                               DUPS_ParamSetName[8],
                               DUPS_ParamSetName[8],
                               DUPS_ParamSetName[8],
                               DUPS_ParamSetName[8],
                               DUPS_ParamSetName[8],
                               DUPS_ParamSetName[8],
                               DUPS_ParamSetName[8]
                            },
                            {  
                               DUPS_ParamSetName[9],
                               DUPS_ParamSetName[9],
                               DUPS_ParamSetName[9],
                               DUPS_ParamSetName[9],
                               DUPS_ParamSetName[9],
                               DUPS_ParamSetName[9],
                               DUPS_ParamSetName[9],
                               DUPS_ParamSetName[9],
                               DUPS_ParamSetName[9]
                            },
                            {  
                               DUPS_ParamSetName[10],
                               DUPS_ParamSetName[10],
                               DUPS_ParamSetName[10],
                               DUPS_ParamSetName[10],
                               DUPS_ParamSetName[10],
                               DUPS_ParamSetName[10],
                               DUPS_ParamSetName[10],
                               DUPS_ParamSetName[10],
                               DUPS_ParamSetName[10]
                            },
                            {  
                               DUPS_ParamSetName[11],
                               DUPS_ParamSetName[11],
                               DUPS_ParamSetName[11],
                               DUPS_ParamSetName[11],
                               DUPS_ParamSetName[11],
                               DUPS_ParamSetName[11],
                               DUPS_ParamSetName[11],
                               DUPS_ParamSetName[11],
                               DUPS_ParamSetName[11]
                            },
                            {  
                               DUPS_ParamSetName[12],
                               DUPS_ParamSetName[12],
                               DUPS_ParamSetName[12],
                               DUPS_ParamSetName[12],
                               DUPS_ParamSetName[12],
                               DUPS_ParamSetName[12],
                               DUPS_ParamSetName[12],
                               DUPS_ParamSetName[12],
                               DUPS_ParamSetName[12]
                            },
                            {  
                               DUPS_ParamSetName[13],
                               DUPS_ParamSetName[13],
                               DUPS_ParamSetName[13],
                               DUPS_ParamSetName[13],
                               DUPS_ParamSetName[13],
                               DUPS_ParamSetName[13],
                               DUPS_ParamSetName[13],
                               DUPS_ParamSetName[13],
                               DUPS_ParamSetName[13]
                            },
                            {  
                               DUPS_ParamSetName[14],
                               DUPS_ParamSetName[14],
                               DUPS_ParamSetName[14],
                               DUPS_ParamSetName[14],
                               DUPS_ParamSetName[14],
                               DUPS_ParamSetName[14],
                               DUPS_ParamSetName[14],
                               DUPS_ParamSetName[14],
                               DUPS_ParamSetName[14]
                            },
                            {  
                               DUPS_ParamSetName[15],
                               DUPS_ParamSetName[15],
                               DUPS_ParamSetName[15],
                               DUPS_ParamSetName[15],
                               DUPS_ParamSetName[15],
                               DUPS_ParamSetName[15],
                               DUPS_ParamSetName[15],
                               DUPS_ParamSetName[15],
                               DUPS_ParamSetName[15]
                            },
                            {  
                               DUPS_ParamSetName[16],
                               DUPS_ParamSetName[16],
                               DUPS_ParamSetName[16],
                               DUPS_ParamSetName[16],
                               DUPS_ParamSetName[16],
                               DUPS_ParamSetName[16],
                               DUPS_ParamSetName[16],
                               DUPS_ParamSetName[16],
                               DUPS_ParamSetName[16]
                            },
                            {  
                               DUPS_ParamSetName[17],
                               DUPS_ParamSetName[17],
                               DUPS_ParamSetName[17],
                               DUPS_ParamSetName[17],
                               DUPS_ParamSetName[17],
                               DUPS_ParamSetName[17],
                               DUPS_ParamSetName[17],
                               DUPS_ParamSetName[17],
                               DUPS_ParamSetName[17]
                            },
                            {  
                               DUPS_ParamSetName[18],
                               DUPS_ParamSetName[18],
                               DUPS_ParamSetName[18],
                               DUPS_ParamSetName[18],
                               DUPS_ParamSetName[18],
                               DUPS_ParamSetName[18],
                               DUPS_ParamSetName[18],
                               DUPS_ParamSetName[18],
                               DUPS_ParamSetName[18]
                            },
                            {  
                               DUPS_ParamSetName[19],
                               DUPS_ParamSetName[19],
                               DUPS_ParamSetName[19],
                               DUPS_ParamSetName[19],
                               DUPS_ParamSetName[19],
                               DUPS_ParamSetName[19],
                               DUPS_ParamSetName[19],
                               DUPS_ParamSetName[19],
                               DUPS_ParamSetName[19]
                            },
                         };  

BOOLEAN DUPSChangePending = FALSE;
enum DUPS_CHANGE DUPSChange;
UINT16 DUPSUploadPSPending;
UINT16 ResonanceFreqEnable[DUPS_NUMRESONANCES];
BOOLEAN HSStartFlag =FALSE;
/*------------------------- PRIVATE GLOBAL DATA ----------------------------*/


/*------------------------ EXTERNAL FUNCTIONS ------------------------------*/


/*----------------------- LOCAL FUNCTION PROTOTYPES ------------------------*/


/*------------------------------ CODE --------------------------------------*/

void DUPS_SelectParamSetNum(SINT32 PSNum)
/*********************************************************************************/
/* This function sends the selected parameter set number message to DUPS manager */ 
/*********************************************************************************/
{
   DUPS_MSGBUF OutMsg;
   DUPS_CurrPSStatus = DUPS_PENDING;

   OutMsg.mt    = DUPS_MSGSELECTPARAMSETNUM;
   OutMsg.data1 = (UINT16) PSNum;
   q_send(DupsQid, &OutMsg);
}

void DUPS_DownloadCurrPS(void)
/*********************************************************************************/
/* This function is called from various menus to download the current parameter  */
/* set to the DUPS module.                                                       */ 
/*********************************************************************************/
{
    DUPS_CurrPSStatus = DUPS_PENDING;       /* DUPS Manager is Busy */
    DUPS_DownloadParamSet(DUPS_CURRPARAMSET);
    DUPS_Wait4CurrPS(); 
    DUPS_SelectParamSetNum(DUPS_CURRPARAMSET);
    DUPS_Wait4CurrPS();

}

void DUPS_QueuedUploadPS(UINT16 psNum)
/*********************************************************************************/
/*   This function will only call DUPS_UploadCurrPS if the welder is in          */
/*   the preready state.  If it is in the ready state the ReadyOK flag will be   */
/*   cleared to FALSE to pull the welder out of ready and the communication      */
/*   will be queued.  If welder is any other state the communication will be     */
/*   queued  and the global flag DUPSChangePending will be set so that a         */
/*   call to verify preset or entry into the preready state will cause the call  */
/*   to DUPS_UploadParamSet.                                                     */
/*********************************************************************************/
{
   switch (WeldState) {
      case PREREADYSTATE:
         DUPS_UploadParamSet(psNum);
         break;
      case READYSTATE:
      default:
         DUPSChange = UPLOAD_PENDING;
         DUPSUploadPSPending = psNum;
         DUPSChangePending = TRUE;
         break;
   }
}

void DUPS_QueuedDownloadPS(void)
/*********************************************************************************/
/*   This function will only call DUPS_DownloadCurrPS if the welder is in        */
/*   the preready state.  If it is in the ready state the ReadyOK flag will be   */
/*   cleared to FALSE to pull the welder out of ready and the communication      */
/*   will be queued.  If welder is any other state the communication will be     */
/*   queued  and the global flag DUPSChangePending will be set so that a         */
/*   call to verify preset or entry into the preready state will cause the call  */
/*   to DUPS_DownloadCurrPS.                                                     */
/*********************************************************************************/
{
   switch (WeldState) {
      case PREREADYSTATE:
         DUPS_DownloadCurrPS();
         DUPSChangePending = FALSE;
         break;
      case READYSTATE:
      default:
         if (DUPSChangePending == FALSE)    /* only if we don't have upload pending */
            {
            DUPSChange = DOWNLOAD_PENDING;
            DUPSChangePending = TRUE;
            }
         break;
   }
}

void DUPS_Wait4CurrPS(void)
/*********************************************************************************/
/* This function waits for the DUPS Manager to complete an download or upload    */
/* set to the DUPS module.                                                       */ 
/* divide limit by 10 and wait 10 times so the waiting could be over faster      */
/*********************************************************************************/
{
   UINT16  Time = 0;

   while ( (Time < DUPS_TIMELIMIT) && (DUPS_CurrPSStatus != DUPS_SUCCESS ))
     {
        tm_wkafter(DUPS_TIMELIMIT / 10);
        Time += (DUPS_TIMELIMIT / 10);
     }
}

void DUPS_DownloadParamSet(UINT16 PSnum)
/***********************************************************************************/
/* This function tells the DUPS manager to download the DUPS parameter set if all  */ 
/* the values are within limits.                                                   */ 
/***********************************************************************************/
{
   DUPS_MSGBUF OutMsg;

   enum DUPS_RESULTS Status = DUPS_ChkParamLimit();  /* Check all parameters are within limit*/

   if (Status == DUPS_SUCCESS)
      {
      OutMsg.mt    = DUPS_MSGDOWNLOADPARAMSET;
      OutMsg.data1 = PSnum;
      q_send(DupsQid, &OutMsg);
      }
}

void DUPS_UploadParamSet(UINT16 PSnum)
/***********************************************************************************/
/* This function sends an Upload parameter set message to the DUPS manager.        */ 
/***********************************************************************************/
{
   DUPS_MSGBUF OutMsg;
   DUPS_CurrPSStatus = DUPS_PENDING;

   OutMsg.mt    = DUPS_MSGUPLOADPARAMSET;
   OutMsg.data1 = PSnum;
   q_send(DupsQid, &OutMsg);
}

void DUPS_HornScanAbort(void)
/***********************************************************************************/
/* This function sends an HornScan abort message to the DUPS manager.              */ 
/***********************************************************************************/
{
   DUPS_MSGBUF OutMsg;

   OutMsg.data1 = HORNSCANABORTED;
   OutMsg.mt = DUPS_MSGHORNSCANSTEP;
   q_send(DupsQid, &OutMsg);
}

void DUPS_ModifySWDipSetting(void)
/***********************************************************************************/
/* Modify Software Dip Setting. Menu manager calls this function when software dip */
/* settings in the DUPS parameter set are modified in the Weld Setup menu          */ 
/***********************************************************************************/
{  
   if (DUPS_Info.DUPSMemFlag)           
      DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPSTOREMEMATWLDEND;
   else       
      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPSTOREMEMATWLDEND;
   
   if (DUPS_Info.DUPSSeekFlag)  
      DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPAUTOSEEK;
   else
      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPAUTOSEEK;

   if (DUPS_Info.DUPSMemRstFlag)           
      DUPS_CurrentParamSet.SWDipSetting |= DUPS_SWDIPCLEARMEMATRST;
   else       
      DUPS_CurrentParamSet.SWDipSetting &= ~DUPS_SWDIPCLEARMEMATRST;
        
   ChangeDUPSSubParamList();
}

void DUPS_StartHornScan(UINT32 MenuExtra)
/**************************************************************************************/
/* Menu manager calls this function to start a horn scan. The function itself sends a */
/* start scan message                                                                 */ 
/**************************************************************************************/
{
   enum DUPS_RESULTS Status = DUPS_SUCCESS;
   DUPS_MSGBUF  OutMsg;
   UINT16 K;

   /***************************************/
   StopStateMachine();
   DUPSOkFlag = FALSE;  
   HSNotStarted = FALSE;
   QVGAHornScanOLD = FALSE;
   /***************************************/
   for (K = 0; K < DUPS_NUMRESONANCES; K++) {
      HornScanInfo.ResonanceFreqs[K] = 0;
      HornScanInfo.ResonanceFreqType[K] = FREQ_NONE;
      ResonanceFreqEnable[K] = 0; /* Don't display Resonance frequency if 0.*/  
   }   
                          /* check the limits */
   if (HornScanInfo.StartFreq >= HornScanInfo.StopFreq)
      Status = DUPS_OTHER;
   if (Status == DUPS_SUCCESS) 
      {                                /* frequency step calculate. Atleast should be 1*/
      while (HornScanInfo.FreqStep * DUPS_HORNSCANMAXPOINTS < (HornScanInfo.StopFreq - HornScanInfo.StartFreq + 1))
         HornScanInfo.FreqStep++;
      OutMsg.mt = DUPS_MSGDOWNLOADSTARTSCAN;
      UpdateKeyMask(HSMASK);
      HornScanOL = FALSE;
      q_send(DupsQid, &OutMsg);
      HornScanInfo.ScanStatus = DUPS_SCANINPROG;
      }
}
void DUPS_StartHS(void)
/**************************************************************************************/
/* Menu manager calls this function to start a horn scan. The function itself sends a */
/* start scan message                                                                 */ 
/**************************************************************************************/
{
   enum DUPS_RESULTS Status = DUPS_SUCCESS;
   DUPS_MSGBUF  OutMsg;
   UINT16 K;
   HSStartFlag = TRUE;
   /***************************************/
   StopStateMachine();
   DUPSOkFlag = FALSE;  
   HSNotStarted = FALSE;
   QVGAHornScanOLD = FALSE;
   /***************************************/
   for (K = 0; K < DUPS_NUMRESONANCES; K++) {
      HornScanInfo.ResonanceFreqs[K] = 0;
      HornScanInfo.ResonanceFreqType[K] = FREQ_NONE;
      ResonanceFreqEnable[K] = 0; /* Don't display Resonance frequency if 0.*/  
   }   
                          /* check the limits */
   if (HornScanInfo.StartFreq >= HornScanInfo.StopFreq)
      Status = DUPS_OTHER;
   if (Status == DUPS_SUCCESS) 
      {                                /* frequency step calculate. Atleast should be 1*/
      while (HornScanInfo.FreqStep * DUPS_HORNSCANMAXPOINTS < (HornScanInfo.StopFreq - HornScanInfo.StartFreq + 1))
         HornScanInfo.FreqStep++;
      OutMsg.mt = DUPS_MSGDOWNLOADSTARTSCAN;
      UpdateKeyMask(HSMASK);
      HornScanOL = FALSE;
      q_send(DupsQid, &OutMsg);
      HornScanInfo.ScanStatus = DUPS_SCANINPROG;
      }
}

             
UINT16 DUPS_SetDUPSParamSet(UINT16 COPps)
/**************************************************************************************/
/* Function accepts a COP preset no. and associates it with the first available       */
/* DUPS parameter set.                                                                */ 
/**************************************************************************************/
{
   SINT16    Status = DUPS_PARAMSETUNDEF;
   UINT16         i = 0;

   while ((i< DUPS_NUMPARAMSET) && (DUPS_Lock[i] != DUPS_PARAMSETAVAIL))
           i++;                          /* find an available slot */

   if (i < DUPS_NUMPARAMSET)
      {
      Status          = i ;
      DUPS2COP[i]     = COPps;
      COP2DUPS[COPps] = i;
      DUPS_Lock[i]    = DUPS_PARAMSETSAVED;  /*change param set status to saved */
      DUPS_RAM2BBRAM();
      }
   return Status;
}

void DUPS_ClearDUPSParamSet(UINT16 COPps)
/**************************************************************************************/
/* Function accepts a COP preset no. and makes the associated DUPS parameter set      */
/* status 'Avail'.                                                                    */ 
/**************************************************************************************/
{
   UINT16         i = 0;

   if ((i = COP2DUPS[COPps])!= DUPS_PARAMSETUNDEF)
      {
      DUPS_Lock[i]    = DUPS_PARAMSETAVAIL; /* param set status = avail */
      DUPS2COP[i]     = DUPS_PARAMSETUNDEF;
      COP2DUPS[COPps] = DUPS_PARAMSETUNDEF;
      DUPS_RAM2BBRAM();
      }
}

UINT16 DUPS_FindCOP4DUPS(UINT16 DUPSps)
/***************************************************************************************/
/* Function accepts the DUPS parameter set no. as input and returns the associated COP */
/* preset.                                                                             */ 
/***************************************************************************************/

{
   return (UINT16) DUPS2COP[DUPSps];
}

UINT16 DUPS_FindDUPS4COP(UINT16 COPps)
/****************************************************************************************/
/* Function accepts the COPS parameter set no. as input and returns the associated DUPS */
/* preset.                                                                              */ 
/****************************************************************************************/
{
   return (UINT16) COP2DUPS[COPps];
}

void DUPS_GetLastWeldStatus(DUPS_WELDSTATUS *Buf)
/****************************************************************************************/
/* This function sends a message to manager to retrieve the weld status report for      */
/* the last weld.                                                                       */ 
/****************************************************************************************/
{  
   DUPS_MSGBUF  OutMsg;
   Buf->OpStatus = DUPS_PENDING;
   Buf->DataStatus = DUPS_PENDING;

   OutMsg.mt = DUPS_MSGUPLOADLASTWELDSTATUS;
   OutMsg.data2 = (UINT32) Buf;
   q_send(DupsQid, &OutMsg);
}

#define IN_RANGE(value)   ((Current->value >= Low->value) && (Current->value <= High->value))

enum DUPS_RESULTS DUPS_ChkParamLimit(void)
/****************************************************************************************/
/* This function checks the maximum and minimum limits of the current parameter set     */
/* values.                                                                              */ 
/****************************************************************************************/
{
   enum DUPS_RESULTS Status;

   DUPS_CURRENTPARAMSET * Current = &DUPS_CurrentParamSet;
   DUPS_CURRENTPARAMSET * High = &DUPS_MaxParamSet;
   DUPS_CURRENTPARAMSET * Low = &DUPS_MinParamSet;

   if (IN_RANGE(SeekAmplitude) && IN_RANGE(SeekRampTime) && IN_RANGE(SeekTime) &&
       IN_RANGE(SeekFreqLimitHigh) && IN_RANGE(SeekFreqLimitLow) &&
       IN_RANGE(SeekPhaseLoop) && IN_RANGE(SeekPhaseLoopCF) &&
       IN_RANGE(SeekAmplitudeLoopC1) && IN_RANGE(SeekAmplitudeLoopC2) &&
       IN_RANGE(WeldAmplitude) && IN_RANGE(WeldRampTime) && IN_RANGE(WeldPhaseLoop) &&
       IN_RANGE(WeldPhaseLoopCF) && IN_RANGE(WeldAmplitudeLoopC1) &&
       IN_RANGE(WeldAmplitudeLoopC2) && IN_RANGE(WeldFreqLimitHigh) &&
       IN_RANGE(WeldFreqLimitLow) && IN_RANGE(WeldPhaseLimit) &&
       IN_RANGE(WeldPhaseLimitTime))

      Status = DUPS_SUCCESS;
   else
      Status = DUPS_OTHER;
   return Status;
}

void DUPS_BBRAM2RAM(void)
/****************************************************************************************/
/*  Function initializes all the data pointers to transfer data from BBRAM to RAM       */
/****************************************************************************************/
{
   UINT8  *HORN_Infoptr = (UINT8 *) BBR800_HORNSCAN_START;
   UINT8  *DUPS2COPptr  = (UINT8 *)BBR800_DUPS2COP_START; /* DUPS_NUMPARAMSET */
   UINT8  *COP2DUPSptr  = (UINT8 *)BBR800_COP2DUPS_START; /*MAX_PRESETS*/
   UINT16 *DUPS_Lockptr = (UINT16 *)BBR800_DUPSLOCK_START; /*Avail,Locked,Saved*/

   memcpy(&HornScanInfo, HORN_Infoptr, sizeof(HORNSCANINFO)); /* copy HORNscanInfo from BBRAM */
   memcpy(&DUPS2COP, DUPS2COPptr, sizeof(DUPS2COP));   /* copy DUPS_info from BBRAM */
   memcpy(&COP2DUPS, COP2DUPSptr, sizeof(COP2DUPS)); /* copy HORNscanInfo from BBRAM */
   memcpy(&DUPS_Lock, DUPS_Lockptr, sizeof(DUPS_Lock));   /* copy DUPS_info from BBRAM */
   memcpy(&DUPS_LockTemp, DUPS_Lockptr, sizeof(DUPS_LockTemp));
}

void DUPS_RAM2BBRAM(void)
/****************************************************************************************/
/* This function is used to store the data in BBRAM                                     */
/****************************************************************************************/
{
   UINT8  *HORN_Infoptr = (UINT8 *) BBR800_HORNSCAN_START;
   UINT8  *DUPS2COPptr  = (UINT8 *)BBR800_DUPS2COP_START; /* DUPS_NUMPARAMSET */
   UINT8  *COP2DUPSptr  = (UINT8 *)BBR800_COP2DUPS_START; /*MAX_PRESETS*/
   UINT16 *DUPS_Lockptr = (UINT16 *)BBR800_DUPSLOCK_START; /*Avail,Locked,Saved*/

   memcpy(HORN_Infoptr, &HornScanInfo,  sizeof(HORNSCANINFO) ); /* copy HORNscanInfo to BBRAM */
   memcpy(DUPS2COPptr, &DUPS2COP, sizeof(DUPS2COP));   /* copy DUPS_info to BBRAM */
   memcpy(COP2DUPSptr, &COP2DUPS, sizeof(COP2DUPS)); /* copy HORNscanInfo to BBRAM */
   memcpy(DUPS_Lockptr, &DUPS_Lock, sizeof(DUPS_Lock));   /* copy DUPS_info to  BBRAM */
}
