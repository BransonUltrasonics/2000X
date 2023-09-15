/* $Header:   D:/SWLab/VMdb/2000Series/INC/GRAPHS.H_V   1.118   04 Sep 2008 20:17:34   ygupta  $ */
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

   Filename: GRAPHS.H


            Written by: Gert Reitmayer  
                  Date: 9/14/96  
              Language:  "C"
 
----------------------------- REVISIONS ------------------------------------

   Revision #     Date           Author     Description
   ==========     ========       ======     ===========
      0            09/14/96       GR        Initial Release
      1            09/17/96       PAULG     Added function prototype 
                                            InitPresetPrinter.    
      1.01         09/30/96       PAULG     Added function prototypes
                                            PrintData, PrintFinalData,
                                            DisplayPrintMess, GlobalSwitch1Func,
                                            and GlobalSwitch2Func.
     1.02         11/27/96       PaulG      Added prototype InitPresetData.          
     1.03         12/03/96       PaulG      Added prototype SampleAlarmCheckFunc.          
     1.04         12/12/96       LAM        deleted prototype InitPresetData.          
     1.05         12/19/96       PaulG      Added function prototype Form_Feed_Page.
     1.06         01/07/97       PaulG      Added weld history text.
     1.07         01/10/97       PaulG      Changed PrintFinalData parameter from void 
                                            WELD_DATA.
     1.09         02/14/97       PaulG      Added GetGlobalTime and WeldModePresetChg .
     1.10         02/26/97       PaulG      Added header.
     1.12         03/07/97       PaulG      Added TRS text.
     1.13         03/13/97       PaulG      Added NonGraph Array.
     1.14         03/20/97       PaulG      Modified Recalib function.
     1.15         03/21/97       PaulG      Modified COMPRESS TO 2000.0.
     1.16         03/27/97       PaulG      Added MAXVELIN.
     1.17         04/08/97       PaulG      Added MAXVELMM.
     1.18         04/09/97       PaulG      Added PRSF1, PRSF2, PRGA1 thru PRGA3
                                            PRREJBR and PRSUSBR.
     1.19         04/15/97       PaulG      Added function GenerateValues.
     1.20         04/28/97       PaulG      Removed PMess[] and PAlarmsMess[].
     1.21         05/08/97       LAM        Removed weld_data from prototypes 
     1.22         05/08/97       PaulG      Added ENERGYPOINT. 
     1.23         05/18/97       LAM        Added init1mspts. 
     1.24         05/28/97       PaulG      Added function prototype Form_Feed_Page. 
     1.25         05/30/97       PaulG      Modified function prototype GenerateValues. 
     1.26         06/06/97       LAM        deleted unused prototypes
     1.27         06/11/97       PaulG      Added function prototype PrintMarkerLine.
     1.28         06/24/97       PaulG      Added defines for printer types.
                                            Added function prototypes CalMaxLinesPerPage, SetMaxLinesPerPage.
     1.29         06/27/97       PaulG      Added defines for PageSizes.
     1.30         07/01/97       LAM        deleted extern uilines    
     1.31         07/17/97       PaulG      Changed Form_Feed_Page() to FormFeedPage().
     1.32         07/28/97       PaulG      Added defines for alarms.
     1.33         07/30/97       PaulG      Changed COMPRESS from 2000.0 to 400.0
     1.34         08/08/97       PaulG      Added IBM Proprinter driver
     1.35         08/13/97       PaulG      Added PUCGRAPHPR.
     1.36         08/23/97       PaulG      Cleanup data.
     1.37         08/26/97       LAM        moved init1mspts to statedrv.h
     1.38         08/27/97       PaulG      Modified CMALARM from 92 to 96.
     1.39         08/29/97       PaulG      Added MESS_LINE119-121.
     1.40         09/03/97       LAM        made strings const     
     1.41         09/08/97       PaulG      Removed *const from text string.   
     1.42         09/16/97       PaulG      Cleanup data
     1.43         09/18/97       PaulG      Modified SampleAlarmCheckFunc, added argument.
     1.44         09/24/97       PaulG      Changed MAXPAGE sizes by 7 for header space.
     1.45         10/07/97       PaulG      Added MESS_LINE122.
     1.46         10/15/97       PaulG      Added PAGESIZECHOICE.
     1.47         10/27/97       PaulG      Added PRINTCPIMODE to distinguish mode.
     1.48         11/07/97       PaulG      Added SendPageSizeToPrinter()function prototype.
     1.49         11/11/97       PaulG      Increased ENERGYPOINT from 999 to 9999.
     1.50         11/12/97       PaulG      Added function prototype CheckCurrentPrintStatus();
     1.51         11/17/97       PaulG      General modification to printer mode.
     1.52         12/09/97       PaulG      Added HISTORY_HEADER2.
     1.53         12/15/97       PaulG      Decreased weldsperpage by 2 lines.
     1.54         01/23/98       PaulG      Added new define WELDTIMEMAX.
     1.55         01/29/98       PaulG      Added MESSLINE126 - 138.
     1.56         02/06/98       LAM        chged sethorizpos prototype
     1.57         02/06/98       PaulG      Added MESS_PRESET0 thru MESS_PRESET10.
     1.58         02/18/98       LAM        started to delete setprinter calls     
     1.59         03/18/98       PaulG      Added MESS_LINE124.
     1.60         03/27/98       PaulG      Added new function prototype ClearDataStorage().
     1.61         04/21/98       PaulG      Modified LABELSIZE from 13 to 17 and added MESS_LINE125 &6.
     1.62         04/28/98       PaulG      Added function prototype PrintTest() for debugging;
     1.63         05/06/98       PaulG      Added defines FILTERVEL8 and FILTERVEL4 for use with velocity graph filtering.
     1.64         05/15/98       PaulG      Exchanged position of FORCEMMGRAPH and FORCEINGRAPH in enum.
     1.65         05/21/98       PaulG      Added defines LFCR, LFCR2, and LFCR3.
     1.66         05/22/98       BJB        Added prototype for FormatDataLine().
                                            Moved prototypes to end of file so they can use earlier #defines.
     1.67         05/27/98       PaulG      Added defines VELMAX1000 and PRINTSCR18.
     1.68         06/05/98       PaulG      Added defines MAXFILTERSAMPLE.
     1.69         06/09/98       PaulG      Added NUM8 and NUM22.
     1.70         06/15/98       PaulG      Added defines HORIZTICK and VERTICALTICK.
     1.71         06/19/98       BJB        Added prototype for GetLastWeldData().
     1.72         06/25/98       PaulG      Change the values of MAXFILTERSAMPLE to 6,
                                            MAXFILT16SAMPLE  to 4, and MAXFILT4SAMPLE   2
     1.73         06/25/98       PaulG      Change the values of MAXFILT16SAMPLE from 6 to 14.
     1.74         07/07/98       PaulG      Change the values of PRINTSCRSIZE from 19 to 24.
     1.75         07/24/98       PaulG      Added new define POSITION10, POSITION12, POSITION16 for position
                                            that vertical label should start printing.
     1.76         07/28/98       PaulG      Modified parameter type in function GetMaxMinLabel(), parameter is c_which_graph.
     1.77         08-05-98       PaulG      Added PSITOKPA, PSISTR and KPASTR from prsetprn.h
     1.78         08-17-98       PaulG      Added DIGITALFORCEVALUE define for force graph.
     1.79         08-19-98       PaulG      Modified PSITOKPA, PSISTR. 
     1.80         09-04-98       PaulG      Added defines LABELWIDTH7 and LABELWIDTH8. 
     1.81         09-23-98       PaulG      Rename DigitalFilterForce to DigitalFilterFunction.
     1.82         10-05-98       LAM        deleted duplicate of OFFSET8                        
     1.83         10-14-98       PaulG      Modify MAXVELPOINTUSCS and MAXVELPOINTMETRIC to mark line at top of Velocity graph.
     1.84         11-06-98       PaulG      Modified MESS_NA and MESS_EXT.
     1.85         11-20-98       PaulG      Modified string variable.
     1.85.4.1     08-28-99       JLH        Updates for use of printer in IBM Pro mode.
     1.85.4.2     09-08-99       JLH        Removed declarations for emulation codes array PUCEmulate.
     1.85.4.3     09-16-99       JLH        Removed declarations for PUCGraph, PUCNonGraphics, and PUCCancel, which were
                                            eliminated from pr_var.h.
     1.85.4.4     09-24-99       OFI        Merged revision 1.85.4.3 and 1.86
     1.88         09-28-99       JZ         fixed function Kalib
     1.89         10-01-99       JZ         deleted DisplayPrintMess()
     1.90         10-11-99       JZ         made GetMaxMinLabel(), PrintSheet(), PrintMessText type void
                                            and removed PrintEscSequ(), PPrint()
     1.91         10-11-99       JZ         made i_num in PrintGraphVLabel(), ui_number in GetMaxMinLabel() to type UINT16
     1.91.1.1     12-16-99       JLH        Removed declarations for buffers removed from pr_var.h.
     1.92         02-23-99       JLH        merged 7.f4CHp (1.91.1.1) to trunk
     1.93         02-28-00       JZ         removed tabs
     1.94         03-21-00       JLH        Removed IBM proprinter printer type.
     1.95         03-23-00       JLH        Removed InitPresetPrinter function prototype.
     1.91.6.1     03-06-00       JLH        Merged revision 1.93 into Lang branch.
     1.96         04-06-00       JZ         merged Lang to trunk
     1.97         04-14-00       JLH        Replaced Kalib prototype with PlotSort in preparation for Horn Scan plotting.
     1.98         05-01-00       JLH        Replaced val array with val1 and val2 arrays.  Replaced order array with 
                                             order1 and order2 arrays. Updated RecalibVal and SetupVals prototypes.
                                             Updated DigitalFilterFunction prototype. 
     1.99         05-01-00       JLH        Replaced HORNSCANGRAPH with PHASEGRAPH and CURRENTGRAPH.
     1.100        05-02-00       JLH        Added DupsPresetReport function prototype.
     1.101        05-26-00       JLH        Removed InkJet and LaserJet printer types; added OKI520 and HPPCL types.
     1.102,1.103  06-14-00       JLH        Removed some strings and put them in pr_text.c.
     1.104        07-12-00       BEKymer    Changed SETUPS to SETUPS_Ver800
     1.105        08-30-00       AT         Changed PRINTSCRSIZE to 25 (horn scan graph message)
     1.106        09-14-00       JLH        Added POSITION41 for positioning Frequency (HZ) at
	                                         bottom of horn scan graph. Removed POSITION34.  
     1.107        10-17-00       JLH        Added prototypes for DisablePerforationSkip and EnablePerforationSkip.
     1.108        10-17-00       JLH        Added column position defines POSITION0 and POSITION2 for use by PrintHSGraph
	                                         function in pr_print.c.
     1.109        05-01-03       BEKymer    Update comments to make more accurate so proper messages
                                             can be duplicate without the velocity entry
     1.110        09-02-03       JOY        Extended Arg: list of 'RecalibVal()' &&
                                            'GetMaxMinLabel()'.
     1.111        06-02-04       VSharma    Modified function prototype of SampleAlarmCheckFunc().
     1.112        06-10-05       Aare       Renamed AlarmText to Alarm.                  
     1.113        07-25-05       Bwadia     Changed to accomodate pr_text deletion in Mess strings.
     1.114        05-23-07       NHAhmed    Added #define for TICKSCRUB ("G").
     1.115        10-22-07       NHAhmed    Changes done for LangTest phase 0
     1.116        06-06-08       NHAhmed    Added some new defines in enum WHICHGRAPH.
     1.117        08-01-08       NHAhmed    Added new enum GRAPHID.
	 1.118        09-04-08		 ygupta     Cleanup for Multilanguage project.

------------------------ DESCRIPTION ----------------------------------*/

#include <psos.h>                          /* for access to pSOS routines    */
#include "weld_obj.h"
#include "preset.h"

/* DEFINES and function prototypes for the printer functions */

#ifndef GRAPHS_H
#define GRAPHS_H



                                              
/* constants for 1ms_data */          

#define COMPRESS          400.0   /* divisor for 1ms data              */
#define PRETRIGMAXLIM     100     /* max point before trigger          */
#define PRETRIGMINLIM     1       /* min point before trigger          */
#define MAXVELIN          5000    /* max velocity in in/s              */
#define MAXVELMM          127000  /* max velocity in mm/s              */
#define MAXNUMSIZE        50      /* Max number of welds in BBRAM      */
#define MAXALARMS         500     /* Maximum number of alarms possible */
                           
/* Alarms */               
                           
#define SETUPEA1       0       
#define SETUPEA2       32      
#define SETUPEA3       64      
#define SETUPEA4       96      
#define SETUPEA5       128     
#define SETUPEA6       160     
#define SETUPEA7       192     
#define SETUPEA8       224
#define SETUPEA9       256
#define SETUPEA10      288
                      
#define NCALARM        0
#define OLALARM        32
#define EQALARM        64
#define CMALARM        96
#define CAALARM        128
#define WAALARM        160 
#define PRALARM        192
#define PSALARM        224




/* offset indices for MESS_LABEL 
   added to MESS_LABEL to point to corrrect text */

#define LABEL_AMPL     0
#define LABEL_POW      1
#define LABEL_FREQU    2
#define LABEL_DIST_IN  3
#define LABEL_FORCE_LB 4
#define LABEL_VELOC_IN 5
#define LABEL_DIST_MM  6
#define LABEL_FORCE_KG 7
#define LABEL_VELOC_MM 8

/* defines for printer init commands */

#define CHAR_PROP      2   // proportional
#define CHAR_NARROW    4   // condensed or 17 cpi
#define CHAR_FAT       8   // bold printout
#define CHAR_BROAD     32  // broad
#define CHAR_UNDER     128 // underline
#define PORTNUM        0   // 0=lpt1 used with biosprint (borland function) 
#define STATUS         2

/* defines for the graph printing */

#define LINE_LENGTH    400                        // number of pts.
#define FIELD_LENGTH   (LINE_LENGTH+21)           // field length exceeding 400
#define BORDER_LEFT    2                          // start of left border
#define BORDER_RIGHT   (BORDER_LEFT+LINE_LENGTH)  // start of right border
#define FINALLINE      137
#define MISCLINE       24
#define LINELENGTH     135
#define LABELLENGTH    145
#define BOTTOMLENGTH    90
#define BOTTOMTEXT      20




/* length of a line: 2 dots tick, 1 dot line vert, 400 dots values
   1 dot line vert. */

/* In printing the setup parameters switch to metric output */

#define DEF_ADDTEXT    0x80
#define DEF_METRIC     0xC0
#define DEF_DIV        0xA0
#define ENERGYPOINT    9999


/* Max Page sizes */

#define MAXPAGE11      57   /*-- 66  WeldsPerPage: subtract 9 lines for HEADER --*/
#define MAXPAGE14      75   /*-- 84  WeldsPerPage: subtract 9 lines for HEADER --*/
#define MAXPAGEA4      61   /*-- 70  WeldsPerPage: subtract 9 lines for HEADER --*/
#define MAXPAGE17      93   /*-- 102 WeldsPerPage: subtract 9 lines for HEADER --*/
#define MAXPAGECONT    999
#define MINPAGESIZE    10

                      
/* Line Length for 1 line data */

#define LINE70         70
#define LINE80         80
#define LINE110        110
#define LINE135        135


#define SIZEOFHISTBRAM (50 * sizeof(WELD_DATA)


#define NUL                '\x00'
#define STX                '\x02'
#define ETX                '\x03'
#define BS                 '\x08'
#define HT                 '\x09'
#define LF                 '\x0a'
#define VT                 '\x0b'
#define FF                 '\x0c'
#define CR                 '\x0d'
#define SO                 '\x0e'
#define SI                 '\x0f'
#define DLE                '\x10'
#define DC1                '\x11'
#define DC2                '\x12'
#define DC3                '\x13'
#define DC4                '\x14'
#define CAN                '\x18'
#define EM                 '\x19'
#define ESC                '\x1b'
#define FS                 '\x1c'
#define GS                 '\x1d'
#define RS                 '\x1e'
#define SP                 '\x20'


/* Graph label const */                     
#define STARTLABEL    -0.100
#define LABELINT      -100
#define INCLABEL       10
#define LABELWIDTH6    6 
#define LABELWIDTH5    5
#define LABELWIDTH7    7
#define LABELWIDTH8    8
#define VALUEDIV       10000.0
#define VALUEDIV2      1000.0
#define FREQMAX41      41000
#define FREQMIN39      39000
#define LABELNUM       12
#define LABELSIZE      15

#define HISTORYDATA     50
#define GRAPHUPPERLIMIT 172 
#define WELDTIMEMAX     30000

/* Velocity graph const */
#define MAXFILTERSAMPLE  6
#define MAXFILT16SAMPLE  14
#define MAXFILT4SAMPLE   2
#define SQWITHDIGITAL    100 
#define WITHDIGITAL      3
#define WITHOUTDIGITAL   4
#define FILTERVEL16      14
#define FILTERVEL8       6
#define FILTERVEL4       2
#define SHIFTVEL2        2
#define SHIFTVEL3        3
#define SHIFTVEL4        4
#define SHIFTVEL5        5
#define SHIFTVEL6        6

#define MAXVELPOINTUSCS    16000
#define MAXVELPOINTMETRIC  450000

#define PRINTSCR0       0     
#define PRINTSCR1       1     
#define PRINTSCR2       2
#define PRINTSCR3       3
#define PRINTSCR4       4
#define PRINTSCR5       5
#define PRINTSCR6       6
#define PRINTSCR7       7
#define PRINTSCR8       8
#define PRINTSCR9       9
#define PRINTSCR10      10
#define PRINTSCR11      11
#define PRINTSCR12      12
#define PRINTSCR13      13
#define PRINTSCR14      14
#define PRINTSCR15      15
#define PRINTSCR16      16
#define PRINTSCR17      17
#define PRINTSCR18      18
#define PRINTSCR19      19
#define PRINTSCR20      20
#define PRINTSCR21      21
#define PRINTSCR22      22
#define PRINTSCR23      23
#define PRINTSCR24      24
#define PRINTSCR25      25
#define PRINTSCR26      26
#define PRINTSCR27      27
#define PRINTSCRSIZE    25

/* Line Feed and Carriage return counts*/
#define LFCR            1
#define LFCR2           2
#define LFCR3           3
#define LFCR4           4
#define LFCR5           5
#define LFCR6           6

/* General numbers in pr_print */
#define PRINTERHEAD7   7
#define PIXEL7TO0      255
#define PIXEL6TO1      126
#define PIXEL7TO3      248
#define PIXEL76        192
#define PIXEL7         128
#define PIXEL7TO5      224
#define POSITION0      0
#define POSITION2      60
#define POSITION16     480
#define POSITION13     390
#define POSITION10     300
#define POSITION11     330
#define POSITION12     360
#define POSITION27     810
#define POSITION41     1230
#define RESOLUTION     10
#define DATESIZE       9
#define MAX16INT       65534
#define ALARMTOPRINT   9
#define SINTINEL       3
#define BYTESIZE       8
#define ROUNDOFF       5
#define BITMOVE        1
#define OFFSET         1
#define OFFSET2        2
#define OFFSET3        3
#define OFFSET4        4
#define OFFSET8        8
#define OFFSET5        5
#define OFFSET6        6
#define OFFSET7        7
#define OFFSET9        9
#define OFFSET10       10
#define NUM10DOT       10.0
#define VERTICALTICK   5
#define HORIZTICK      8
#define BOXSIZE        22
#define NUM100DOT      100.0
#define NUM100         100
#define NUM330         330
#define NUM254         25.4
#define NUM135         135
#define ENDGRAPH       401
#define NUM200         200
#define TESTSIZE       140
#define CONV254        254
#define TICKTRIG       0
#define TICKAMP        1
#define TICKFORCE      2
#define TICKSONIC      3
#define TICKHOLD       4
#define TICKSEEK       5
#define TICKSCRUB      6

/*-- Related to Gauge Pressure --*/
#define PSITOKPA       6.89
#define PSISTR          " psi"
#define KPASTR          " kPa"

#define VELMAX1000     1000
#define VELMAX3000     3000
#define VELMAX6000     6000

#define DIGITALFORCEVALUE   16


/**-----------------------------------------------------------------**
 **                    Structure Decalarations                      ** 
 **-----------------------------------------------------------------**/                       

typedef float FLOAT;

enum WHICHGRAPH {       
     AMPLIGRAPH,
     POWGRAPH,
     FREQUGRAPH,
     DISTINGRAPH,
     FORCELBGRAPH,
     VELINGRAPH,
     DISTMMGRAPH,
     FORCENGRAPH,
     VELMMGRAPH,
     ABSINGRAPH,
     ABSMMGRAPH,
     CURRENTGRAPH,
     POW_DISTMMGRAPH,
     POW_DISTINGRAPH,
     POW_FORCENGRAPH,
     POW_FORCELBGRAPH,
     FORCEN_DISTMMGRAPH,
     FORCELB_DISTINGRAPH,
     PHASEGRAPH,
     PMC_GRAPH,
     NO_VALID_GRAPH
};           

enum GRAPHID{
   VGAPOWERGRAPH,
   VGAFREQUENCYGRAPH,
   VGAAMPLITUDEGRAPH,
   VGAFORCEGRAPH,
   VGAVELOCITYGRAPH,
   VGACOLDISTGRAPH,
   VGAHORNSCANGRAPH
};




/* pr_kalib.c for sorting the input values */
struct STRComp{     
    UINT16 higher;
    UINT16 lower;
    };

/* PrintSummary function */
struct SummaryStruct{
        UINT8           b_yes_no        :    1;     // 1 = yes
        UINT8           b_unit          :    1;     // 0 = inch,
                                                    // 1 = metric
        UINT8           b_resolution     :    1;    // 0 = condensed
                                                    // 1 = not condensed
        UINT8           b_number        :    8;     // number of summaries
    };

/* PrintGraph function */
struct GraphicStruct{
        UINT8           b_yes_no        :    1;    // 1 = with graphic print
                                                   // 0 = without graphics
        UINT8           b_unit          :    1;    // 0 = inch, 1 = metric
//    UINT8           b_which_graph   :    4;     which graph to be printed
    };

/* printing the trailer at the bottom of the page */
struct BottomStruct{
    UINT8               b_yes_no        :    1;    // with or without bottom lines
    };

/* printing history values (not yet activated) */
struct HistoryStruct{
    UINT8               b_yes_no        :    1;    // with or without setup
    UINT8               b_every_page    :    1;
    };

/* global information is stored */
struct GeneralStruct{
    UINT8               b_printer_type    :    3;    // several printer types available
                                                                // 0 = Epson LQ
                                                                // 1 = Epson FX
                                                                // 2 = IBM Proprinter
    UINT8               b_language        :    4;    // max 7 languages
                                                                // 0 = english
                                                                // 1 = german
                                                                // 2 = french
    UINT8               b_welds_per_page  :    8;   // lines per page
    };






/* Which graph is being printed */

struct GraphicStruct GraphicInfo;
struct BottomStruct  BottomInfo;
struct HistoryStruct HistoryInfo;
struct GeneralStruct GeneralInfo;


/**-----------------------------------------------------------------**
 **                    External Variables Decalarations             ** 
 **-----------------------------------------------------------------**/                       

extern SINT32 val1[];
extern SINT32 val2[];
extern struct STRComp order1[];
extern struct STRComp order2[];

extern UINT32 UIVmaxlabel, UIVminlabel, UIHmaxlabel;
extern UINT32 UIWeldtime;
extern CONFIGSETUP CurrentSetup;
extern SETUPS_Ver800 CurrentPreset;
extern UINT32 UIGraphPoints;


/**-----------------------------------------------------------------**
 **                    Global Variables Decalarations               ** 
 **-----------------------------------------------------------------**/                       



/**-----------------------------------------------------------------**
 ** Function prototypes for functions in printer files:             ** 
 ** pr_print, pr_text, pr_label, 1ms_data, prnweld, prnmangr        **                       
 **-----------------------------------------------------------------**/                       
void SetupVals( enum WHICHGRAPH GraphSelected, SINT32 *Data );
UINT16 PlotSort( SINT32 *Data, struct STRComp *DataOrder, UINT16 NumSamp );
void RecalibVal( SINT32 *Data, UINT16 CurrentGraph, UINT32 VmaxLabel,
                 UINT32 VminLabel );
/*void PrintMessText(SINT32 ii);
UINT8* GetMessText(SINT32 INumber);
void SetHorizPos(UINT16 pos);
void PrintHistory(void);
void PrintSetup(void);
void PrintGraph(void);*/
void GetMaxMinLabel(UINT16 c_which_graph, SINT32 *Data, UINT16 ui_number,
UINT32 *p_maxlabel,UINT32 *p_minlabel);
SINT16 SPrintf(SINT8* pc_buf, const SINT8* pc_format,...);
void PrintSheet(MSG_GRAPH_TYPE);
void InitPrinterFlags(void);
void QVGAPrepTickMarks(void);
void FormatDataLine( UINT8 DataLine[LINELENGTH], WELD_DATA *Results, UINT16 Metric );
void GlobalSwitch1Func(void);
void GlobalSwitch2Func(void);
void GetPtsIncrement(void);
void PostHoldtimeState(void);
void PreTrigState(void);
void DurTrigWeldHoldState(void);
void GroupAllmSObject(void);
void CombineAllData(void);
void Get1msData(void);
void AbortCurPrintFunc(void);
void PrintWeldHistory(void);
UINT16 FuncExpandData(void);
void Form_Feed_Page(void);
void CalMaxLinesPerPage(void);
void SetMaxLinesPerPage(void);
void ControlLevelText(void);
void SetThePrinterType(void);
void EmulateEPSON(void);
void InitEPSON(void);
void InitHP(void);
void InitPrinterType(void);
void Select10CPI(void);
void Select12CPI(void);
void Select17CPI(void);
void Select16LF(void);
void Select872LF(void);
void SelectEmphasized(void);
void SelectNonEmphasized(void);
void Plot8Lines(UINT8 *PixelData, UINT16 NPixelCols);
void EnablePerforationSkip(void);

void SetPrinterToDraw(void);
void PrintSummaryLevel1(void);
void PrintSummaryLevel2(void);
void EscapeCodeString(SINT8 string2[], UINT16 len);
UINT16 CheckCurrentPrintStatus(void);
void GetLastHistoryData(void);
void ClearDataStorage(void);
void GetLastWeldData( WELD_DATA *Results );
void PrintTestFunc(void);
void DigitalFilterFunction(SINT32 *Data, SINT32 ForceDigFilter);
void GetLast1LineData(void);
void GetPresetNameFunc(void);
BOOLEAN CheckForPrintHeader(void);
                                        // these indices points to messages in pr_text.c
#endif /* end of GRAPHS_H */
