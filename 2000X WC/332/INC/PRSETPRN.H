/* $Header:   D:/SWLab/VMdb/2000Series/INC/PRSETPRN.H_V   1.96   22 Sep 2009 12:09:32   ygupta  $ */
#ifndef _PRSETPRN_H
#define _PRSETPRN_H

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

 /*---------------------------- MODULE DESCRIPTION --------------------------

    Module name: prsetprn

    Filename: prsetprn.h

    Function name:

 --------------------------------- REVISIONS --------------------------------

 Rev#   Date     Author   Description
 ===    ====     ======   ===========
 0               PaulG    Initial Version                   
 1.00   08/23/96 PaulG    Removed "const" form SETUP and CONFIG strings.
 1.01   08/26/96 PaulG    Modified  formal parameters in FormatNumber,
                          FormatString and FormatHeader function prototypes.
 1.02   09/19/96 PaulG    Added printer codes and deactivated test data
 1.03   09/20/96 PaulG    Modified printer code for Cancel print.
 1.04   09/24/96 PaulG    Modified Setup0021 string. 
 1.05   10/10/96 PaulG    Added unit test
 1.06   12/03/96 PaulG    Added Setup0019A - Pretrigger At Distance.
 1.07   01/30/97 PaulG    Modified Config0037 to MPS.
 1.08   02/03/97 PaulG    Added Setup0070 - MaxTimeout.
 1.09   02/06/97 PaulG    Added Setup0071 - CycleAbort.
 1.10   02/26/97 PaulG    Added header.
 1.11   03/11/97 PaulG    Modified text string.
 1.12   03/13/97 PaulG    Modified Energy text string.
 1.13   05/05/97 LAM      Made strings constants       
 1.20   06/13/97 PaulG    Changed Config0003 fron 1000 to 2000
 1.21   07/18/97 PaulG    Added defines
 2.1.24 07/22/97 LAM      moved defines to limarray.h
 2.1.28 07/23/97 PaulG    Modify defines.
 2.1.29 07/24/97 PaulG    Modify defines (contd1).
 2.1.30 07/25/97 PaulG    Modify defines (contd2).
 2.1.31 07/28/97 PaulG    Modify Features from "Advance" to "Advanced".
 2.1.32 07/30/97 PaulG    Removed ESC sequences.
 2.1.33 08/28/97 PaulG    Added prototype ChecktoPrintPageTwo().
 2.1.35 08.29.97 JBerman  Added "WATT"
 2.1.37 09.18.97 JBerman  Added: #define ASTRICK333 "***"
 2.1.38 09.19.97 JBerman  Fixed PAGELEN11 & PAGELEN14
 2.1.39 11-12-97 PaulG    Changed HEADERVAL from 94 to 74
 2.1.39 11-19-97 PaulG    Changed HEADERVAL from 74 to 84
 1.40   11-24-97 LAM      added systempresetreport        
 1.41   11-24-97 LAM      need to remove systempresetreport        
 1.43   12.03.97 JBerman  Changed AE->ae, AED->aed...
 1.44   12.04.97 JBerman  Changed Setup according the spec.:
                          Weld Data, Groung Detect Cutoff Col Dist
 1.45   12.04.97 JBerman  Added "Start Screen", "Main", "Run" 
                          and prototype PrintStartScreen
 1.46   12.11.97 JBerman  Changed LinesPerPage->Welds per Page
 1.47   01.22.98 BJB      Deleted definitions of YESSTR, NOSTR
 1.48   01.22.98 BJB      Changed VALUEHOST to "Computer" from "Host"
 1.49   04.06.98 PaulG    Changed MaxTimeout to Max Timeout.
 1.50   04.17.98 LAM      Changed ground detect cutoff to abort
 1.51   05.14.98 PaulG    Added  PrintConfig0081() for Digital Tune.
 1.52   05.15.98 PaulG    Added  string const CONTROLF.
 1.53   05.22.98 PaulG    Added  string const KPASTR = "kPa".
 1.54   06.17.98 PaulG    Added  Changed text from Dist. to Distance.
 1.55   06.19.98 JBerman  Changed Advanced->All, Normal->Basic.
 1.56   06.25.98 JBerman  Modified MAXLIMITS FROM 16 TO 17.
 1.57   06.26.98 JBerman  Changed Max Force to Weld Force.
 1.58   06-29-98 PaulG    Changed frequence to frequency.
 1.59   08-05-98 PaulG    Moved PSITOKPA, PSISTR and KPASTR to Graphs.h
 1.60   09-03-98 BJB      AE shows as "ae/ao" on printout, AED as "aed/aod",
                          etc.
 1.61   09-17-98 PaulG    Added define FTENVALUE of 10.0 for float calculations. 
 1.62   10-05-98 LAM      deleted duplicate UPDATEPRINTBUFFER define             
 1.63   10-05-98 LAM      deleted duplicate MAXLIMITS & MAXWELDMODES from graphs.h
 1.64   11-02-98 PaulG    Modified text strings aedActVelSetting[] and ActVelSetting[].
 1.65   11-04-98 PaulG    Added text string AEDSetGaugePressure[], also modified AEDGaugeSettings.
 1.66   12-09-98 LAM      Modified output of freq for 15/30KHz support.
 1.66.4.1 08-19-99 JLH    Deleted PrintSetup0069, PrintConfig0074, PrintConfig0075, PrintaefSetting3,
                            PrintaefSetting4, PrintAEDPressure.
                          Added PrintForceRamps, PrintWeldRate, PrintStepRate, PrintHoldRate,
                            PrintSystemPressure, CalStr, and CalDateStr. 
 1.66.4.2 09-08-99 JLH    Changed "R/T Distance" to "RT Distance".  Printer would not print half-line
                            with R/T Distance in it.
 1.66.4.3 09-14-99 JLH    Numerous functions to print text followed by an underline replaced with one
                            function called Fillin.  
 1.68     09-24-99 JLH    Eliminate CalDateStr definition - it is also defined in menu6.c.
 1.69     10-08-99 JLH    Eliminated prototype for unused function removed from prsetprn.c.  Commented
                          out "SETUP" string that is no longer used by prsetprn.c.
 1.70     10-19-99 JLH    Various changes to conform to changes in prsetprn.c.  All SPrintf calls were
                            removed from prsetprn.c, and general cleanup was initiated (much remains
                          to be done).
 1.71     11-01-99 JLH    Added strings to implement printer code review changes.
 1.72     11-05-99 JLH    Changed Velocity variable name to VelocityStr.  Velocity was also declared
                           in sc.c.
 1.72.1.1 12-17-99 JLH    Deleted #defines for PAGE1, PAGE2, etc.  Deleted TWOLINE.  Changed TIMELEN
                           to 10.  Deleted FormatLeftJ.
 1.73     02-23-00 JLH    merged 7.f4CHp to trunk
 1.74     02-28-00 JZ     removed tabs
 1.75     03-23-00 JLH    Removed InitPresetPrinter function prototype.
 1.76     04-11-00 JLH    Merged with Lang branch revision 1.72.6.3.
 1.77     04-24-00 JLH    Moved most remaining strings to pr_text.c.
 1.78     05-26-00 JLH    Added strings PRINTHPPCL and PRINTOKI520 for new printer designations. 
 1.79     06-09-00 JLH    Added 2 lines to length of half-page buffers (now 18 lines).
 1.80     07-12-00 LAM    Corrected for indexing with new control level defines
 1.81     07-14-00 BEKymerAdded defines for CONTROLEA and CONTROLTEST
 1.82     08-07-00 JLH    Removed NEWLINEFILL define.
 1.83     08-30-00 JLH    Added CONTROLDEPOT define.   
 1.84     10-19-00 SCM    Modified the define "PRINTOKI520".
 1.85     04-25-01 BEKymerChanged ACTAE fro 'ae/ao' to 'ae/ao/HH' for handheld
 1.86     06-02-04 VSharma Added function prototypes to print User I/O.
                           Added define CUSTOMACT. 
 1.87     08-26-04 JOY    Added function prototype.
 1.88     09-21-04 JOY    Added function prototype.
 1.89     09-10-05 Bwadia VGA print related additions for Ver10.0h 
 1.90     10-28-05 Bwadia Function prototype added for sequencing item
 1.91     12-07-05 Bwadia Function prototype added for decimal place and distance
                          print items for VFD print welder setup conditions
                          Modified for tracker issue 3996  
 1.92     05-23-07 NHAhmed Redefined PRINT_LINE_HEIGHT to 23. 
 1.93     10-22-07 NHAhmed Changes done for LangTest phase 0
 1.94     06-06-08 NHAhmed Added enum PRESET_REPORT.
 1.95     08-01-08 NHAhmed Added defines for MID_XCOORDINATE, LEFT_SUB_XCOORDINATE and 
                           RIGHT_SUB_XCOORDINATE.
 1.96     09-22-09 YGupta  Added MICRO_SETTINGS_TXT for MICRO Actuator.
 ------------------------------- DESCRIPTION --------------------------------*/


/*------------------------------ LOCAL DEFINES ------------------------------*/

#define   TAB                  "\x20\x20\x20\x20"    /* 4 blank space      */
#define   INDENT               "\x20\x20\x20"        /* 3 blank space      */
#define   LINELEN              81                    /* length of buffer   */
#define   MISCLEN              20                    /* length of buffer   */
#define   SIZEOFBUF            36                    /* length of buffer   */
#define   ARRYSIZE             18                    /* length of buffer   */
#define   FFLF                 "\xC\xA"       /* form feed + line feed            */
#define   NEXTLINE             "\xD\xA"       /* line feed + carrige return       */
#define   ACTEP                "aef"
#define   ACTAO                "ao"
#define   ACTAOEN              "aod"
#define   ACTEPO               "aof"
#define   ACTAE                "ae/ao/HH"
#define   ACTAEEN              "aed/aod"
#define   CUSTOMACT            "Custom"
#define   PASSWD               "******"
#define   WELDT1X              "1X"
#define   WELDT2X              "2X"
#define   WELDT3X              "3X"
#define   PRINTEPSON           "Epson(ESC/P)"
#define   PRINTHPPCL           "HP(PCL)"
#define   PRINTOKI520          "OKIDATA 520/320"
#define   CLEARBUFFERLINE      strcpy(buffer,"                                    ")
#define   DRAWLINE             " _______________"
#define   BLANKFILL            "                                    "
#define   PAGELEN11            "11\""
#define   PAGELEN14            "14\""                                                 
#define   PAGELENA4            "A4"
#define   CONTROLT             "t"
#define   CONTROLE             "e"
#define   CONTROLD             "d"
#define   CONTROLA             "a"
#define   CONTROLF             "f"
#define   CONTROLEA            "ea"
#define   CONTROLTEST          "TEST"
#define   CONTROLDEPOT         "DEPOT"

#define   DATELEN              12
#define   TIMELEN              10
#define   SPACE                "\x20"
/* format page printing */
#define   PRINTSPACEPAGE       35
#define   DISPLAYCHAR          9
#define   SUSACTIVE            0
#define   REJACTIVE            1
#define   SUSREJDIFF           5
#define   TIMEMLIM             0
#define   ENERGYMLIM           1
#define   PKPOWERMLIM          2
#define   COLMLIM              3
#define   ABSMLIM              4
#define   GRDDETMLIM           5
#define   CONTMLIM             6
#define   CENTERVAL            74
#define   HEADERVAL            84

#define VGAPRINTTEXT 30
#define FONT_PRINT 2
#define FONT_PRINTBOLD 3
#define PRINT_LINE_HEIGHT 23
#define LEFT_XCOORDINATE 100
#define RIGHT_XCOORDINATE 650
#define LEFT_YCOORDINATE 100
#define RIGHT_YCOORDINATE 100
#define VGAMISCLEN 12
#define MID_XCOORDINATE 560
#define LEFT_SUB_XCOORDINATE 140
#define RIGHT_SUB_XCOORDINATE 690

enum PRESET_REPORT{
	   PRETRIG_OFF_TXT,
	   WELDMODE_TXT,
		TIME_TXT,
		ENRGY_TXT,
		PKPOWR_TXT,
		COLLAPSE_TXT,
		ABSOLUTE_TXT,
		GRDDETECT_TXT,
		CONTINOUS_TXT,
		ALLMODE_TXT,
		SCRUBAMP_TXT,
		AMPLITUDE_TXT,
		AMPA_TXT,
		AMPB_TXT,
		STEP_TIME_TXT,
		STEP_ENRGY_TXT,
		STEP_PKPOWEER_TXT,
		STEP_COLDIST_TXT,
		STEP_FORCE_TXT,
		STEP_EXTSIGNAL_TXT,
		STEP_OFF_TXT,
		PRETRIG_TXT,
		PRETRIG_TYPE_TXT,
		PRETRIG_DIST_TXT,
		PRETRIG_DLY_TXT,
		PRETRIG_AMP_TXT,
		MAX_TIMEOUT_TXT,
		EXTTRIG_DLY_TXT,
		HOLDTIME_TXT,
		HOLDTIME_OFF_TXT,
		ABRUST_TXT,
		ABRUST_DLY_TXT,
		ABTIME_TXT,
		ABAMP_TXT,
		ENRGYBRAKING_TXT,
		POSTWELD_TXT,
		FREQ_OFFSET_TXT,
		DIGITALTUNE_TXT,
		TESTAMP_TXT,
		ACTCLEAR_OUT_TXT,
		ACTCLEAR_DIST_TXT,
		CYCLEABORT_TXT,
		GRDDETECT_ABORT_TXT,
		MISSINGPART_TXT,
		MISSINGPART_MINOFF_TXT,
		MISSINGPART_MIN_TXT,
		MISSINGPART_MAXOFF_TXT,
		MISSINGPART_MAX_TXT,
		CTRL_LIMITS_TXT,
		COLCUTOFF_TXT,
		COLCUTOFF_DIST_TXT,
		ABSCUTOFF_TXT,
		ABSCUTOFF_DIST_TXT,
		PKPOWERCUTOFF_TXT,
		PKPOWERCUTOFF_VAL_TXT,
		ENRGYCOMP_TXT,
		MAXENRGY_TXT,
		MINENRGY_TXT,
		AEF_SETTINGS_TXT,
		RAPIDTRAVS_TXT,
		RAPIDTRAVS_DIST_TXT,
		DOWNSPEED_TXT,
		TRIGFORCE_TXT,
		WELDFORCE_OFF_TXT,
		WELDFORCE_TXT,
		WELDFORCEA_TXT,
		WELDFORCEB_TXT,
		HOLDFORCE_TXT,
		GAUGEPRESSURE_TXT,
		FORCERAMPS_TXT,
		WELDFORCERATE_TXT,
		STEPFORCERATE_TXT,
		HOLDFORCERATE_TXT,
		AED_SETTINGS_TXT,
		AEDTRIGFORCE_TXT,
		SYSTEMPRESSURE_TXT,
		/* SYSYTEM REPORT 2*/
		DUPS_TXT,
		DUPS_RAMPTIME_TXT,
		DUPS_MEMRY_TXT,
		WELDSTATUS_TXT,
		SELECTNAME_TXT,
		SEEKTIME_TXT,
		TIMEDSEEK_TXT,
		WRITEINFLD1_TXT,
		WRITEINFLD2_TXT,
		LIMITS_TXT,

		REJLIMITS_TXT = 86,
		REJRESET_TXT,
		SUSPTLIMITS_TXT,
		SUSPTRESET_TXT,
		PCOL_RLIMT_TXT,
		PCOL_RLIMT_OFF_TXT,
		MCOL_RLIMT_TXT,
		MCOL_RLIMT_OFF_TXT,
		PENRGY_RLIMT_TXT,
		PENRGY_RLIMT_OFF_TXT,
		MENRGY_RLIMT_TXT,
		MENRGY_RLIMT_OFF_TXT,
		PABSOLUTE_RLIMT_TXT,
		PABSOLUTE_RLIMT_OFF_TXT,
		MABSOLUTE_RLIMT_TXT,
		MABSOLUTE_RLIMT_OFF_TXT,
		PPKPOWER_RLIMT_TXT,
		PPKPOWER_RLIMT_OFF_TXT,
		MPKPOWER_RLIMT_TXT,
		MPKPOWER_RLIMT_OFF_TXT,
		PTIME_RLIMT_TXT,
		PTIME_RLIMT_OFF_TXT,
		MTIME_RLIMT_TXT,
		MTIME_RLIMT_OFF_TXT,
		PWELDFORCE_RLIMT_TXT,
		PWELDFORCE_RLIMT_OFF_TXT,
		MWELDFORCE_RLIMT_TXT,
		MWELDFORCE_RLIMT_OFF_TXT,
		PTRIGDIST_RLIMT_TXT,
		PTRIGDIST_RLIMT_OFF_TXT,
		MTRIGDIST_RLIMT_TXT,
		MTRIGDIST_RLIMT_OFF_TXT,
		PPOWERBAND_RLIMT_TXT,
		PPOWERBAND_RLIMT_OFF_TXT,
		MPOWERBAND_RLIMT_TXT,
		MPOWERBAND_RLIMT_OFF_TXT,
		PSBLFREQ_RLIMT_TXT,
		PSBLFREQ_RLIMT_OFF_TXT,
		MSBLFREQ_RLIMT_TXT,
		MSBLFREQ_RLIMT_OFF_TXT,

		PCOL_SLIMT_TXT,
		PCOL_SLIMT_OFF_TXT,
		MCOL_SLIMT_TXT,
		MCOL_SLIMT_OFF_TXT,
		PENRGY_SLIMT_TXT,
		PENRGY_SLIMT_OFF_TXT,
		MENRGY_SLIMT_TXT,
		MENRGY_SLIMT_OFF_TXT,
		PABSOLUTE_SLIMT_TXT,
		PABSOLUTE_SLIMT_OFF_TXT,
		MABSOLUTE_SLIMT_TXT,
		MABSOLUTE_SLIMT_OFF_TXT,
		PPKPOWER_SLIMT_TXT,
		PPKPOWER_SLIMT_OFF_TXT,
		MPKPOWER_SLIMT_TXT,
		MPKPOWER_SLIMT_OFF_TXT,
		PTIME_SLIMT_TXT,
		PTIME_SLIMT_OFF_TXT,
		MTIME_SLIMT_TXT,
		MTIME_SLIMT_OFF_TXT,
		PWELDFORCE_SLIMT_TXT,
		PWELDFORCE_SLIMT_OFF_TXT,
		MWELDFORCE_SLIMT_TXT,
		MWELDFORCE_SLIMT_OFF_TXT,
		PTRIGDIST_SLIMT_TXT,
		PTRIGDIST_SLIMT_OFF_TXT,
		MTRIGDIST_SLIMT_TXT,
		MTRIGDIST_SLIMT_OFF_TXT,
      VQS_TXT,

		VQS_WELDTIMEMIN_TXT = 254,
		VQS_WELDTIMEMIN_OFF_TXT,
		VQS_ENRGYMIN_TXT,
		VQS_ENRGYMIN_OFF_TXT,
		VQS_PKPOWERMIN_TXT,
		VQS_PKPOWERMIN_OFF_TXT,
		VQS_WELDCOLMIN_TXT,
		VQS_WELDCOLMIN_OFF_TXT,
		VQS_TOTALCOLMIN_TXT,
		VQS_TOTALCOLMIN_OFF_TXT,
		VQS_TOTALABSMIN_TXT,
		VQS_TOTALABSLMIN_OFF_TXT,
		VQS_WELDFORCEMIN_TXT,
		VQS_WELDFORCEMIN_OFF_TXT,
		VQS_TOTALCYCLETIMEMIN_TXT,
		VQS_TOTALCYCLETIMEMIN_OFF_TXT,

		VQS_WELDTIMEMAX_TXT,
		VQS_WELDTIMEMAX_OFF_TXT,
		VQS_ENRGYMAX_TXT,
		VQS_ENRGYMAX_OFF_TXT,
		VQS_PKPOWERMAX_TXT,
		VQS_PKPOWERMAX_OFF_TXT,
		VQS_WELDCOLMAX_TXT,
		VQS_WELDCOLMAX_OFF_TXT,
		VQS_TOTALCOLMAX_TXT,
		VQS_TOTALCOLMAX_OFF_TXT,
		VQS_TOTALABSMAX_TXT,
		VQS_TOTALABSLMAX_OFF_TXT,
		VQS_WELDFORCEMAX_TXT,
		VQS_WELDFORCEMAX_OFF_TXT,
		VQS_TOTALCYCLETIMEMAX_TXT,
		VQS_TOTALCYCLETIMEMAX_OFF_TXT,
		MICRO_SETTINGS_TXT
};

/*------------------------FUNCTION PROTOTYPES ------------------------------*/
 
void InitMessage(UINT8);

// Function Prototypes
void InitPrinterNow(void);    /* Initialize preset printer */
void GetDateTime(void);
SINT8 * RateText(UINT16);

SINT8* GetSelectedInpStr (UINT16 InputBit);
SINT8* GetSelectedOutStr (UINT16 OutputBit);

#endif /* _PRSETPRN_H */
