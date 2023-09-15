/* $Header:   D:/SWLab/VMdb/2000Series/INC/Dups_api.h_v   1.54   Jan 31 2007 20:19:08   nhahmed  $ */
#ifndef DUPS_API_H 
#define DUPS_API_H
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
                                          
   Module name:

   Filename:      dups_api.h

            Written by: Sunil R. Patil 
                  Date: 06/09/00
              Language:  "C"                              


----------------------------- REVISIONS ------------------------------------

   Revision #   Date       Author    Description
   ==========   ========   ======    ===========
       1.0      06/09/00   SRP       Initial Version
       1.1      06/23/00   SRP       Modifications as per part-II spec.
       1.2      06/29/00   SRP       Modifications as per part-II spec.
       1.3      06/30/00   SRP       some defines made commented temporary.
       1.4      06/30/00   SRP       function added to send message UPLOADPARAMSET.
       1.5      07/05/00   SRP       Changes made after code review like BBram to array 
       1.6      07/07/00   SRP       function prototypes shifted below all defines.
                                     DUPS_startscancmd struct added.
       1.7      07/07/00   SCM       No changes made. Sunil had already done the changes.
       1.8      07/10/00   SRP       Max and Min struct defined for Currentparamset and Hornsacn
       1.9      07/11/00   SRP       WeldStatusFlag is added in DUPS Info struct.
       1.10     07/12/00   SRP       Null char added in dups info struct paramset name.
       1.11     07/12/00   SRP       no change. Checked out for emulator testing.
       1.12     07/14/00   SRP       BBRAM declarations updated. LOCK status modified.
       1.13     07/14/00   SRP       BBRAM decleared as external and defined in api.c
       1.14     07/17/00   SRP       UINT32 changed to SINT32 in CURRENTPARAMSET.
       1.15     07/17/00   SRP       UINT16 changed to SINT32 for HORNSCANINFO 5 params used by menu  
       1.16     07/18/00   SCM       Changed the defn of pointer to structures and replaced them with
                                     regular structure definitions.  
       1.17     07/19/00   SCM       Removed the array containing the parameter set from the structure 
                                     DUPS_Info and added the array definition ParameterSetName.
       1.18     07/19/00   SRP       MSG DownloadParamset and downloadstartscan function prototype added.
       1.19     07/21/00   SCM       Made ActiveWorkNum in DUPS_Info structure a UINT16.
       1.20     07/20/00   SRP       DIPFlag made SINT32. Freq, power and varient added in currentparamset.
       1.21     07/22/00   SCM       Changed the type definition of DUPSMemFlag and DUPSSeekFlag to UINT6,changed 
                                     DipFlag to UINT16 and cleaned up a few prototype definitions.
       1.22     07/22/00   SRP       Msguploadweld prototype added. 
       1.23     07/25/00   SCM       Changed the prototype definitions of a few functions.
       1.24     07/26/00   SRP       Debugging parameters added in DUPS Info.
       1.25     08/02/00   SRP       STR *DUPS_PsNamePTR added. ChkParamLimit function prototype added.
       1.26     08/02/00   SRP       StartScan function made void. Selectparamset made uploadparamset.
       1.27     08/03/00   SRP       SINT32 psNum changed to UINT16 in DUPS_UploadParamSet(UINT16 psNum) prototype.
                                     Hornscan struct parameters made SINT32.
       1.28     08/07/00   SCM       Changes in function prototypes.
       1.29     08/07/00   SRP       DUPS_HornScanAbort(void) prototype added. UINT16 changed to SINT32 in resonance array.                                     
       1.30     08/10/00   SRP       RTC parameter added for horn scan in scan info struct.
       1.31     08/11/00   RBH       Save/Recall Preset corrections.
       1.32     08/11/00   RBH       Library Name to string
       1.33     08/11/00   RBH       Added DUPS_Wait4CurrPS function
       1.34     08/11/00   RBH       Corrected DUPS_TIMELIMIT
       1.35     08/11/00   RBH       Corrected function prototypes
       1.36     08/12/00   SCM       Added function prototypes for DUPS_BBRAM2RAM() and DUPS_RAM2BBRAM().
       1.37     08/16/00   RBH       Corrections to Save/Recall presets and Parameter Sets 
       1.38     08/23/00   SRP       HS_NUMRAWPHASEPOINTS and numcoff added as global defines.
       1.39     08/29/00   AT        Corrected declarations for DUPS2COP, COP2DUPS...
       1.40     09/07/00   SRP       Cleaning, touch up and comments added.
       1.41     09/28/00   AT        Cleanup after code review    
       1.42     09/29/00   SCM       Added the enum DUPS_PSFREQ.
       1.43     10/04/00   AT        Added DUPS_QueuedDownloadPS function.
       1.44     10/05/00   AT        added enum DUPS_CHANGE
       1.45     10-05-00   BEKymer   Removed underscores from DUPSChangePending
                                      and DUPSChange variables.
       1.46     10-09-00   AT        Added DUPS_QueuedUploadPS and DUPSUploadPSPending
       1.47     10-12-00   AT        Changed SINT16 to enum DUPS_RESULTS
       1.47.1.1 06-28-03   JOY       Added enum 'RESONANCE_FREQ_TYPE'. 
       1.47.1.2 09-08-03   JOY       'RESONANCE_FREQ_TYPE', is moved to 'HORNSCAN_INFO'. 
       1.48     01-09-01   BEKymer   Added arguments to functions that are called
                                      from TEXT or SUBMENU structures
       1.49     12-05-03   BEKymer   Merged 1.48 & 1.47.1.2 to create 1.49 for
                                      Ver9.00b build
       1.50     12-08-03   BEKymer   Add argument to DUPS_StartHornScan(UINT32)
       1.51     07-25-05   Bwadia    Checked in for Ver10.0e
       1.52     01-12-06   Bwadia    externs modified for HS_MaxScanInfo and 
                                     HS_MinScanInfo structure and made variable    
                                     Modified for tracker issue 3966
       1.53      02-22-06  Bwadia    Memory reset flag added in DUPS_INFO structure
                                     Modified for tracker issue 4077
       1.54      01-31-07  NHAhmed   Changes related to Changed Structure variables of CHOICE and TOGGLE.
*/

/*------------------------------ DESCRIPTION -------------------------------*/


/* This file contains global DUPS data                                      */


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "battram.h"

/*------------------------------- DEFINES ----------------------------------*/

/* This file contains global data*/


#define DUPS_LIBRARYNAMELEN    20    /* DUPS library name string length */
#define DUPS_PARAMSETNAMELEN   20    /* DUPS Param Set mane string length */
#define DUPS_NUMPARAMSET       20    /* Number of DUPS Presets */
#define DUPS_CURRPARAMSET      (DUPS_NUMPARAMSET -1)   /* reserved slot for current parameter set */
#define DUPS_NUMRESONANCES     6     /* Number of Horn Scan Resonance Freqs detected */ 
#define DUPS_HORNSCANPOINTS    400   /* Number of Horn Scan points printed and stored 
                                        in BBRAM */
#define DUPS_HORNSCANMAXPOINTS 1000  /* Max points queried for analysis */
#define DUPS_TIMELIMIT         100   /* 100 PSOS ticks for timeout = 500 ms */
#define HS_NUMCOEFS           17     /* Coff required for filter to smooth out the scan phase data */
#define HS_NUMRAWPHASEPOINTS  (DUPS_HORNSCANMAXPOINTS+HS_NUMCOEFS)

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           


/*These values are used for the error reason codes in the Weld Status report*/
enum DUPS_ERROR_REASON
{  DUPS_POWEROVERLOAD     = 0x01,
   DUPS_CURRENTOVERLOAD   = 0x02,
   DUPS_VOLTAGEOVERLOAD   = 0x04,
   DUPS_THERMALOVERLOAD   = 0x08,
   DUPS_FREQLIMITSEEKLOW  = 0x10,
   DUPS_FREQLIMITSEEKHIGH = 0x20,
   DUPS_FREQLIMITWELDLOW  = 0x40,
   DUPS_FREQLIMITWELDHIGH = 0x80,
   DUPS_PHASELIMIT        = 0x100,
};


/*These values are used in the Weld Status Report for State and Error State*/
enum DUPS_STATE
{  DUPS_NOERROR = 0,
   DUPS_RESET   = 1,
   DUPS_ERROR   = 2,
   DUPS_READY   = 3,
   DUPS_SEEK    = 4,
   DUPS_WELD    = 5,
};


enum DUPS_FREQCONVERSION   /*The appropriate units are as follows:*/
{   DUPS_15KHZ = 3,   /*  15Khz Units = (3 * 0.0025) 0.075hz/bit*/ 
    DUPS_20KHZ = 4,   /*  20Khz Units = (4 * 0.025 ) 0.100hz/bit*/
    DUPS_30KHZ = 6,   /*  30Khz Units = (6 * 0.025 ) 0.150hz/bit*/
    DUPS_40KHZ = 8    /*  40hz  Units = (8 * 0.025 ) 0.200hz/bit*/
};

enum DUPS_PSFREQ             /* The values of the power supply frequencies for the 15khz,20khz,30khz and 40khz*/
{                            /* welders used to populate HornScanInfo structure during initialization.Values are */
  DUPS_MIN15AND30 = 195000,  /* the same for 15khz and 30khz welders AND */                             
  DUPS_MAX15AND30 = 205000,  /*              20khz and 40khz welders.  */
  DUPS_MIN20AND40 = 194500,
  DUPS_MAX20AND40 = 204500
};

/*Parameter Set Status is maintained for each DUPS parameter Sets*/
enum DUPS_LOCK
{  DUPS_PARAMSETLOCKED = 0x01,
   DUPS_PARAMSETAVAIL= 0x02,
   DUPS_PARAMSETSAVED = 0x04};

#define DUPS_PARAMSETUNDEF 255 /*used in x-ref tables when no associated preset*/

/*These values placed in the Operation Status field of the user provided data area when a
DUPS request is made*/
enum DUPS_RESULTS
{  DUPS_PENDING = -1,   /*Transefer or operation is in progress*/
   DUPS_SUCCESS =  0,   /*successfully completed*/
   DUPS_NACK,           /*DUPS board return an error*/  
   DUPS_TIMEOUT,        /*operation did not complete within alotted time*/
   DUPS_CHECKSUM,       /*DUPS board reported or DUPS interface detected error*/
   DUPS_OTHER};         /*other interface error*/


/*The values for Scan Status are defined in following enum*/
enum DUPS_HORNSCANSTATE
{  DUPS_NOSCAN    = 0,
   DUPS_SCANINPROG,
   DUPS_SCANSCOMPLETE,
   DUPS_SCANDATAAVAIL};

/* Resonance Frequency Types*/
enum RESONANCE_FREQ_TYPE
{   FREQ_NONE,
    FREQ_SERIES,
    FREQ_PARALLEL};   


/*These are PSOS+ messages sent to DUPS Manager*/
enum DUPS_MESSAGES
{   DUPS_MSGUPLOADHWID       = 1,
    DUPS_MSGUPLOADSWID,
    DUPS_MSGSELECTPARAMSETNUM,
    DUPS_MSGREQUESTPARAMSETNUM,
    DUPS_MSGDOWNLOADPARAMSET,
    DUPS_MSGUPLOADPARAMSET,
    DUPS_MSGUPLOADLIBRARYNAME,
    DUPS_MSGDOWNLOADLIBRARYNAME,
    DUPS_MSGUPLOADLASTWELDSTATUS,
    DUPS_MSGUPLOADRELEASE,
    DUPS_MSGDOWNLOADSTARTSCAN,
    DUPS_MSGUPLOADSCANPOINT,
    DUPS_MSGINITINTERFACE,  
    DUPS_MSGHORNSCANSTEP,
    DUPS_MSGHORNSCANABORT,
    DUPS_MSGLASTMESSAGE};

/*DUPS Preset Mapping and Status*/
extern UINT8 DUPS2COP[DUPS_NUMPARAMSET]; /* DUPS_NUMPRESET */
extern UINT8 COP2DUPS[MAX_PRESETS + 1]; /*DUPS_NUMPRESET*/
extern UINT16 DUPS_Lock[DUPS_NUMPARAMSET]; /*Avail,Locked,Saved*/
 
/*DUPS information structure: indicates whether or not a DUPS has been detected*/
typedef struct 
{  UINT16    DUPSFlag;                  /*TRUE if DUPS detected*/
   BOOLEAN    DUPSMemFlag;               /* Memory on off flag */
   BOOLEAN    DUPSMemRstFlag;            /* Memory reset flag */
   BOOLEAN    DUPSSeekFlag;              /* Timed seek on off flag */
   UINT16    WeldStatusFlag;            /* Request weld status on overload*/
   SINT32    ProgramId;                 /* SW ID from command 513 */
   UINT16    FlashVersion;              /* Flash version from command 513 */
   UINT16    ActiveWorkNum;             /* current DUPS Preset */
   UINT16    PowerSupplyFreq;           /* system enum */
   UINT16    FreqConversion;            /* 0.025 Hz / bit */
   UINT16    PowerSupplyWatts;          /* Value in Watts   */
   UINT16    LastFunction;              /* Added for dioganostic purpose*/
   SINT16    LastStatus;                /* Added for dioganostic purpose*/
   UINT8     RspCE1;                    /* Added for dioganostic purpose*/
   UINT8     RspCE2;                    /* Added for dioganostic purpose*/
   UINT8     RspFE1;                    /* Added for dioganostic purpose*/
   UINT8     RspFE2;                    /* Added for dioganostic purpose*/
   UINT8     ACKorNACK;                 /* Added for dioganostic purpose*/
   UINT8     LibraryName[DUPS_LIBRARYNAMELEN +1];/*ASCII characters*/
 } DUPS_INFO;
extern DUPS_INFO DUPS_Info; 


// This string contains the uploaded parameter set names during initialization.

extern STR DUPS_ParamSetName[DUPS_NUMPARAMSET][DUPS_PARAMSETNAMELEN + 1];
extern STR *DUPS_PsNamePTR[DUPS_NUMPARAMSET][9];

/*The weld status report contains a subset of the data received for the last weld*/
typedef struct 
{  UINT8    ParameterSetName[DUPS_PARAMSETNAMELEN];
   SINT16   OpStatus;    /*progress of command to retrive data - Pending, Success, etc*/
   SINT16   DataStatus;          /*validity of data upon completion of command */
   SINT32   Frequency;          /*Same as HW Id Frequency*/
   SINT32   Power;              /*Same as HW Id Power Level */
   SINT32   Variant;            /* apparently Variant = 0 (EQ or Adv?)*/
   SINT32   ReadHWDip;          /* 1 = read HW dip; 0 = SW dip*/
   SINT32   SWDipSetting; /*meaning described  above */
   SINT32   SeekStartFrequency; /* units = Frequency dependent */
   SINT32   SeekStopFrequency;  /* units = Frequency dependent */
   SINT32   SeekMemoryFrequency;/* units = Frequency dependent */
   SINT32   WeldStartFrequency; /* units = Frequency dependent */
   SINT32   WeldStopFrequency;  /* units = Frequency dependent */
   SINT32   WeldMemoryFrequency;/* units = Frequency dependent */
   SINT32   WeldTime;            /* units = 1 millisecond per bit */
   SINT32   WeldEnergy;         /* units = 100/2047 percent per bit */
   SINT32   Temperature;         /* units = degree F*/
   SINT32   State;               /* see DUPS state enumeration*/
   SINT32   ErrorState;          /* see DUPS state enumeration*/
   SINT32   ErrorReason;         /* see Error Reason enumeration*/
   SINT32   ErrorFrequency;      /* units are Hz */
   SINT32   ErrorPower;          /* units are percent */
   SINT32   ErrorCurrent;        /* units are percent */
   SINT32   ErrorPSV;            /* units 100/255 bits*/
   SINT32   ErrorAmplitude;      /* units are percent */
   SINT32   ErrorTime;           /*millisecs - start of sonics to error*/
}  DUPS_WELDSTATUS;

extern DUPS_WELDSTATUS DUPS_WeldStatus;
                                                  

/*DUPS current parameter set contains the values of the parameter set in COP's 
current preset's format*/
typedef struct                  /* ParamIDs */
{  
   SINT32   Frequency;
   SINT32   Power;
   SINT32   Variant;
   UINT16   DipFlag;            /* DUPS_DIPFLAG */
   SINT32   SWDipSetting;       /*DUPS_SWDIPSETTING  */
   SINT32   SeekAmplitude;      /*DUPS_SEEKAMPLITUDE*/
   SINT32   SeekRampTime;       /*DUPS_SEEKRAMPTIME milisecons*/
   SINT32   SeekTime;           /* DUPS_SEEKTIME  miliseconds*/
   SINT32   SeekFreqLimitHigh;  /*DUPS_SEEKFLIMH  hertz*/
   SINT32   SeekFreqLimitLow;   /* DUPS_SEEKFLIML hertz*/
   SINT32   SeekPhaseLoop;      /* DUPS_SEEKPHLOOPI */
   SINT32   SeekPhaseLoopCF;    /* DUPS_SEEKPHLOOPCF */
   SINT32   SeekAmplitudeLoopC1;/* DUPS_SEEKAMPLOOPC1 */
   SINT32   SeekAmplitudeLoopC2;/*DUPS_SEEKAMPLOOPC2 */
   SINT32   WeldAmplitude;      /*DUPS_WELDAMPLITUDE */
   SINT32   WeldRampTime;       /* DUPS_WELDRAMPTIME */
   SINT32   WeldPhaseLoop;      /* DUPS_WELDPHLOOPI */
   SINT32   WeldPhaseLoopCF;    /* DUPS_WELDPHLOOPCF */
   SINT32   WeldAmplitudeLoopC1;/*DUPS_WELDAMPLOOPC1 */
   SINT32   WeldAmplitudeLoopC2;/* DUPS_WELDAMPLOOPC2 */
   SINT32   WeldFreqLimitHigh;  /* DUPS_WELDFLIMH  hertz*/
   SINT32   WeldFreqLimitLow;   /* DUPS_WELDFLIML  hertz*/
   SINT32   WeldPhaseLimit;     /* DUPS_WELDPHLIM */
   SINT32   WeldPhaseLimitTime; /* DUPS_WELDPHLIMTIME  milliseconds*/
}  DUPS_CURRENTPARAMSET;

extern DUPS_CURRENTPARAMSET DUPS_CurrentParamSet;
extern SINT16  DUPS_CurrPSStatus;       /* Set to Pending for upload, DUPS_SUCCESS when complete*/
extern DUPS_CURRENTPARAMSET DUPS_MaxParamSet;
extern DUPS_CURRENTPARAMSET DUPS_MinParamSet;

/*DUPS message buffer is used to send PSOS+ messages to DUPS Manager*/
typedef struct 
{   enum DUPS_MESSAGES mt;    /* message type see DUPS message enumeration */
    UINT16 data1; /* Data value to use in DUPS Manager */
    UINT32 data2; /* Data value to use in DUPS Manager */
    UINT32 data3; /* Data value to use in DUPS Manager */
    UINT32 data4; /* Data value to use in DUPS Manager */
}   DUPS_MSGBUF;

extern DUPS_MSGBUF DUPS_MsgBuf;

/*Horn scan information structure contains data about the parameters and status 
of the most recent scan*/
typedef struct 
{  SINT32   StartFreq;        /* hertz */
   SINT32   StopFreq;         /* hertz */
   SINT32   FreqStep;         /* 0.025 / bit */
   SINT32   TimeDelay;        /* miliseconds */
   SINT32   MaximumAmplitude; /* % */ 
   SINT32   MaximumCurrent;   /* % */
   UINT8    ScanStatus;
   UINT16   NumScanPoints;
   SINT32   ResonanceFreqs[DUPS_NUMRESONANCES]; /* hertz */
   enum RESONANCE_FREQ_TYPE ResonanceFreqType[DUPS_NUMRESONANCES];
   SINT32   Year;
   SINT32   Month;
   SINT32   Day;
   SINT32   Hour;
   SINT32   Minute;
}  HORNSCANINFO;

extern HORNSCANINFO HornScanInfo; 
extern HORNSCANINFO HS_MaxScanInfo;
extern HORNSCANINFO HS_MinScanInfo;

typedef struct 
{  SINT32   StartFreq;        /* hertz */
   SINT32   StopFreq;         /* hertz */
   SINT32   FreqStep;         /* 0.025 / bit */
   SINT32   TimeDelay;        /* miliseconds */
   SINT32   MaximumAmplitude; /* % */ 
   SINT32   MaximumCurrent;   /* % */
}  DUPS_STARTSCANCMD;

extern DUPS_STARTSCANCMD DUPS_StartScanCmd;
/*Horn scan information structure contains max and min limits data about 
the parameters */
typedef struct 
{  UINT16   MaxFreq;             /* hertz */
   UINT16   MinFreq;             /* hertz */
   UINT16   MaxTimeDelay;        /* miliseconds */
   UINT16   MinTimeDelay;        /* miliseconds */
   UINT16   MaxAmplitude;        /* % */ 
   UINT16   MaxCurrent;          /* % */
}  HS_LIMITS;

extern HS_LIMITS HS_Limits;

/*DUPS Horn Scan data for Most recent Horn Scan stored in BBRAM*/
extern SINT16  *HornScanCurrent;
extern SINT16  *HornScanPhase;

extern BOOLEAN DUPSChangePending;
enum DUPS_CHANGE { DOWNLOAD_PENDING = 1, UPLOAD_PENDING };
extern enum DUPS_CHANGE DUPSChange;
extern UINT16 DUPSUploadPSPending; /* upload param set number */

/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/
enum DUPS_RESULTS DUPS_MsgUploadWeldStatus(DUPS_WELDSTATUS *);
void   DUPS_StartHornScan(UINT32 MenuExtra);
UINT16 DUPS_SetDUPSParamSet(UINT16 COPps);
void   DUPS_ClearDUPSParamSet(UINT16 COPps);
UINT16 DUPS_FindCOP4DUPS(UINT16 DUPSps);
UINT16 DUPS_FindDUPS4COP(UINT16 COPps);
void   DUPS_ModifySWDipSetting( void );
void   DUPS_SelectParamSetNum(SINT32 psNum);
void   DUPS_UploadParamSet(UINT16 psNum);
void   DUPS_GetLastWeldStatus(DUPS_WELDSTATUS *buf);
void   DUPS_DownloadCurrPS(void);
void   DUPS_QueuedDownloadPS(void);
void   DUPS_QueuedUploadPS(UINT16 psNum);
void   DUPS_Wait4CurrPS(void);
void   DUPS_DownloadParamSet(UINT16 psNum);
enum DUPS_RESULTS DUPS_ChkParamLimit(void);
void   DUPS_HornScanAbort(void);
void   DUPS_BBRAM2RAM(void);
void   DUPS_RAM2BBRAM(void);

#endif  /* DUPS_API_H */
