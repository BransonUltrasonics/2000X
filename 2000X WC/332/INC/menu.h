/* $Header:   D:/databases/VMdb/2000Series/INC/MENU.H_V   2.108.2.12.1.1   Nov 29 2017 11:47:00   hasanchez  $ */
#ifndef MENU_H
#define MENU_H
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
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:          

   Filename: menu.h

   Function name:

 --------------------------------- REVISIONS --------------------------------

   Revision #  Date      Author   Description
   ==========  ========  ======   ===========
   0                              Initial Version                   
   1           5/22/96   LAM      deleted true/false, and led defines           
   2           5/22/96   LAM      added led defines           
   3           06-12-96  BEKymer  Change SUBMENU member flag from UINT16 to BOOLEAN
   4.00        07-01-96  Phil J   Changed Title size from 15 to 14
   4.01        07-19-96  Phil J   enums Modes now Bit Values
   5.00        08-01-96  Phil J   Added function to RADIOMENU structure.
   6.00        08-19-96  LAM      Added enum for frequency.
   7.60        09/04/96  PhilJ    Type TIMEDATE added to enum Format
   7.70        09/11/96  PhilJ    Added struct type HVARIABLE and enum
                                  RUN_PARAM. Deleted LED defines.
   7.80        09/19/96  PhilJ    Added RPIZZA to enum RUN_PARAM.
   7.90        10/04/96  PhilJ    Added typedef menu14 GENALARM.
   8.00        10/11/96  PhilJ    Changed GENALARM to ALARM.
   9.00        11/01/96  LAM      added pressure format      
   9.10        12/12/96  PhilJ    Changed BitMask in struct VARIABLE from
                                  SINT16 to UINT16.      
  10.00        04/08/97  LAM      added watts format      
  11.00        04/09/97  PhilJ    added enum RADIOMASK.
  12.00        04/24/97  PhilJ    Added items to enum RUN_PARAM.
  12.10        04/28/97  PhilJ    Chngd *Eptr in CHOICE and VARIABLE from 
                                  UINT8 to UINT16.
  12.20        05/13/97  PhilJ    Deleted RUNSEEK from RUN_PARAM.
  12. 2.24     06/17/97  PaulG    Added enum PAGESIZE.
  12. 2.25     06/23/97  PaulG    Modified enum PAGESIZE.
  12. 2.26     07/03/97  PhilJ    Modified enum ACTUATOR.
  13. 2.26     07/16/97  JBerman  Added menu 15
  13. 2.28     10.03.97  JBerman  Expended RADIOLINKSIZE from 10 to 12.
  2.29         10-16-97  BJB      Added elements to ALPHA structure for
                                   screen entry position, show/hide chrs.
                                  Added prototype for WaitKeyPress().
  2.30         11-04-97  BJB      Added prototypes for BuidMenu(),
                                   ShowMenuItems().
  2.31         11-11-97  BJB      Modified prototype for WaitKeyPress(), now
                                   returns key.
  2.32         12-29-97  BJB      Modified BuildMenu() prototype, function
                                   now returns lines, not pages.
                                  ShowMenuItems() changed to
                                   ShowScreenMenuItems(), CurrentPage arg
                                   no longer needed.
                                  Added prototypes for FormatMenuLine(),
                                   FormatTitle().
  2.33          1-5-98   BJB      Added definition of new ShowMenuItems(),
                                   which supports remote terminal.
                                  Modified def of FormatMenuLine().
                                  Added prototypes for up/down key handler
                                   functions.
  2.34         01-12-98  BJB      Added prototypes for ShowEstopMessageOn/Off()
  2.35         01-27-98  BJB      Modified prototype for FormatMenuLine()
  2.36         02-06-98  BJB      Added new type PERCENTX10.
  2.37         04-21-98  BJB      Removed unnecessary parameters from
                                   ShowMenuItems(), ShowScreenMenuItems(),
                                   FormatMenuLine().
  2.38         04-27-98  BEKymer  Make Actuator enum use bit assignments
                                   instead of incrementing values (which
                                   required a particular order when defined).
  2.39         04-27-98  BJB      Made DONTCARE 0xFFFF instead of 0, so there
                                   is always a bit set for each actuator type.
  2.40         04-28-98  BJB      Added title pointer, prompt pointer, ID to
                                   ALPHA structure.
                                  Deleted unused Vptr[] array, ID from
                                   RADIOMENU.
  2.41         05-15-98  BJB      Defined structures for new VARIABLE format
                                   table.
                                  Added prototypes for new functions to
                                   support VARIABLE format table.
  2.42         05-19-98  BJB      Added new INTEGER format.
  2.43         05-26-98  BJB      Added "Metric" parameter to FormatVariable(),
                                   FormatNum(), related functions.
  2.44         06-22-98  BJB      Added prototype for GetCurrentMenu().
  2.45         06-24-98  BJB      Added RSYSPRESS label for system pressure
                                   item on weld results line.
  2.46         06-24-98  BJB      Added aliases BASIC, ALL, BASICONLY to enum
                                   USER, code can now refer to either
                                   NORMAL/BASIC or ADVANCED/ALL.
  2.47         08-19-98  BJB      Added definitions, added/deleted prototypes
                                   due to changes in MENU.C for new screen,
                                   terminal modules.
  2.48         08-28-98  BJB      Added bit definitions for VF & Term devices.
  2.49         09-02-98  BJB      Added prototypes for AlarmOn(), AlarmOff().
  2.50         09-04-98  BJB      Added RWCOLDIST, RTCOLDIST labels for    
                                   collapse items on weld results line.
  2.51         09-09-98  BJB      Added LONGTIME format to format list.
  2.52         10-05-98  LAM      deleted duplicate failed1 & failed2 from state.h
  2.53         10-28-98  LAM      chged frequency enum to freqtype to correct      
                                  duplicate declaration from ccrider, added 
                                  15 and 30 khz
  2.54         04-20-99  OFI      Changed for PVCS
  2.55         05-14-99  JZ       changed RFORCESTART to RFORCEA, RFORCEEND to
                                  RFORCEB, RFORCEMAX to RFORCE
  2.56         05-28-99  LAM      deleted unused EP actuator, added HGUN
  2.57         06-04-99  JZ       Added FORCEDIV10 to the Struct FORMAT
  2.58         06-16-99  JZ       added defines from RATE_SLOWEST to RATE_FASTEST
  2.58.1.1     06-23-99  JZ       added enum STAGE and defines for weld stages
  2.58.1.2     06-30-99  JZ       deleted enum STAGE Stage and void SetPV
  ?
  2.61         10-28-99  JZ       added some new defines
  2.62         11-04-99  OFI      Added two defines FORCE_STEP_AT_EXTERNAL and AMP_STEP_AT_EXTERNAL
  2.63         12-07-99  JZ       changed and added defines for 2in and 3in default settings
  2.64         12-07-99  JZ       corrected MIN_TRIGGER_FORCE_DEFAULT_2IN value
  2.64.6.1     02-07-00  JZ       deleted DVS and added Mask1, Cond1, Mask2, Cond2 to the menus
  2.64.6.2     02-23-00  OFI      removed 'User experience level' from menu prototype strucutures
                                  removed enum User; removed typedef struct menu15; removed ADVFEATURES from enum Level
  2.65         04-07-00  JZ       merged Lang to trunk
  2.66         05-30-00  SCM      Checked in for testing by Laura,John.
  2.67         06-02-00  SCM      Added enum's and structure definitions 
                                  for RADIOLARGE menu.
  2.68         06-05-00  SCM      Checked in for testing by Laura, John.
  2.69         06-09-00  SCM      Added enum's for Mask1 and Mask2.
  2.70         06-14-00  SCM      Defined enum's RADIO_16 thro' RADIO_31.
  2.71         06-27-00  SCM      Changed the names of the values RWABSDIST 
                                  and RTABSDIST in the enum RUN_PARAM.
  2.72         06-28-00  SCM      Commented out enum value RCYCLETIME in
                                  RUN_PARAM.(Ver 9 requirement).
  2.70.1.0     06-29-00  JLH      Added CONTROL_LEVEL enum.
  2.73         06-29-00 BEKymer   Changed all MODEL to LEVEL, assigned binary values to Levels,
                                  also changed all MODEL to CTRL_LEVEL and all model to CtrlLevel.
  2.75         07-13-00  BEKymer  Change enum name from MODEL to CTRL_LEVEL
  2.76         07-18-00  JLH      Added to MASK2 enum.
  2.77         07-22-00  SCM      Modified the RADIOLARGE structure definition.
  2.78         08-02-00   SRP     **Tptr made as single pointer at menu16.
  2.79         08-18-00   AT      RMAXPARAMETERS = 21
  2.80         09-12-00  JLH      Reordered frequencies in enum FREQTYPE; gave them values 1 - 4. 
  2.81         01-08-01  BEKymer  Added argument to function call in TEXT and SUBMENU structure
  2.81         06-11-01  BEKymer  Make LEVEL_TEST a 16-bit value so boards received from Fisher
                                   Rosemont configured with all 'ones' will come up as TEST
  2.80.1.1     08-03-01  BEKymer  Add RS232_MASK for 8.2S special
  2.80.1.2     08-21-01  BEKymer  Detab  
  2.80.1.3     04-24-03  BEKymer  Add VEL as a mask2
  2.80.1.2.1.2 07-12-03  JOY      Added function prototypes for 'QVGAFormatMenuLine()'&
                                  'QVGARemoveNull()'.                                     
  2.80.1.4     07-25-03  LAM      merged 8.10 with TS01
  2.80.1.5     07-31-03  JOY      Added function prototypes for 'IsHWConfigured()'.
  2.80.1.6     09-02-03  JOY      Added Dual Graph Types.
                                  Moved 'CODES' struct from menu.c to menu.h.
  2.83         08-05-03  BEKymer  Merged 2.80.1.3 and 2.82 to create 2.83 for build 9.00A
  2.83.1.0     08-05-03  BEKymer  Fix merging bug
                                  Added HH to MASK2
  2.84         09-04-03  BEKymer  Added Energy braking defaults for time and amp
  2.85         12-08-03  BEKymer  Merged 2.84 & 2.83.1.6 to create 2.85 for Ver9.00b
                                   build
  2.86         02-19-04  VSharma  Changed 'MAXSCROLLMENUS' and added 'RPRESETNUM' 
                                  in 'RUN_PARAM'.
  2.87         05-12-04  VSharma  Added define AMP_DECAY_PERCENT_DEFAULT.
  2.88         06-02-04  VSharma  Added EP_S in enum MASK2.                                 
  2.89         06-15-04  BEKymer  Add RVELOCITY_AED & RVELOCITY_AEF
  2.90         07-12-04  BEKymer  Added PC379 & PC594 to mask1 hardware
                                   Add defines for 60 kHz special for Ahmet
  2.91         08-23-04  LAM      increased number_of_codes by 1 for Fast AD COMM
  2.92         08-30-04  BEKymer  Change energy braking default in BUC menu to
                                   40 ms.                                 
  2.93         09-09-04  BEKymer  Change energy braking default in BUC menu to
                                   1000 ms.                                 
  2.94         09-17-04  BEKymer  Moved function prototypes from menu.c to
                                   here where they belong
  2.95         04-05-05  LAM      Added SBeam/ Loadcell hidden prototypes                                   
  2.96         04-08-05  LAM      Added board config for SBeam prototypes                                   
  2.96         07-25-05  Bwadia   VGA object definition added   
  2.97.1.1     08-25-05  Aare     Added DISTANCE3 format 
  2.97.1.2     08-26-05  Aare     Added 2 new codes to NUMBER_OF_CODES #define.
  2.97.1.3     08-28-05  Aare     Added yet another new code to NUMBER_OF_CODES #define.
  2.99         09-10-05  Aare     Checked in so that 'get' wouldn't overwrite it.
  2.100        09-11-05  Aare     Fixed a typo.
  2.101        10-28-05  Bwadia   MAXSUBMENUS and MAX_MENU_ITEMS changed
  2.102        01-03-06  Bwadia   Param ID added to VGABOTTOMHALF object
                                  Modified for tracker issue 3972
  2.103        01-05-06  LAM      Merged BBRaun Special                                
  2.104        01-09-06  LAM      Updated NUMBER_OF_CODES for encoders                                
  2.105        03-02-06  Bwadia   Updated NUMBER_OF_CODES for Trigger force menu 
  2.106        12-22-06  NHAhmed  Changed #define Value of NUMBER_OF_CODES.
  2.107        01-31-07  NHAhmed  Changes related to Changed Structure variables of CHOICE and TOGGLE.
  2.108        02-07-07  NHAhmed  Moved function prototypes for Secret Codes from menu.c to menu.h.
  2.108.2.0    12-03-07  BEKymer  Add function prototypes 
                                  Change NUMBER_OF_CODES from 29 to 31
  2.109        04-14-08 NHAhmed   Added prototypes for function FormatVariables() and FormatNums().
                                  Added a new menu structure RSPARAMETER
  2.110        09-04-08	ygupta    Cleanup for Multilanguage project.
  2.111        09-09-08	NHAhmed   Cleanup for multi-language support.
  1.108.2.3.1  09-22-09 YGupta    Added support for MICRO Actustor.
  2.108.2.5    09-28-09 BEKymer   Change NUMBER_OF_CODES from 34 to 36 for MICRO
  2.108.2.6    10-05-09 BEKymer   Remove duplicate code changing NUMBER_OF_CODES
                                   from 36 to 35 for MICRO
                                  Add define for Hi & Lo Leaving Home force
  2.108.2.7    10-21-09 BEKymer   Change RestoreFactoryDefaults() prototype to
                                   RestoreDefaults().
                                  Change NUMBER_OF_CODES to 37
                                  Add prototypes for changing control levels
  2.108.2.8    06-08-10 PDwivedi  Modified NUMBER_OF_CODES for standard MICRO Actuator.
  2.108.2.9    08-17-10 BEKymer   Change LEAVINGHOMEFORCEMICROHI from 4 to 10
                                   for testing
  2.108.2.10   08-17-10 BEKymer   Change LEAVINGHOMEFORCEMICROHI from 4 to 15
                                   for testing
  2.108.2.11   11-8-10 BEKymer    Change LEAVINGHOMEFORCEMICROHI from 15 to 7
                                   to reflect testing results.
  2.108.2.12   03-25-11 PDWivedi  Added Secret menu function for Baxter velocity limit.
  2.108.2.12.1.1   11-29-17 HSAN  Changes to commit the codding standard
*/
/*                                    



 ------------------------------ INCLUDE FILES --------------------------------
*/
#include "portable.h"

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/


#define ENDLIST       -1
#define LINESIZE      20         /* Size of display line in characters     */
#define QVGA_LINESIZE 62         /* mAX: Size of display line in QVGA      */
#define MESSAGESIZE (LINESIZE+1) /* Size of display message include nul    */
#define TITLESIZE     14         /* Max # of chars on top line with page # */
#define MAXSUBMENUS   35         /* Max # of entries under any one menu    */
#define MAX_MENU_ITEMS 40        /* Max # of entries with some fudge space */
#define DISPLAY_LINES  4         /* Number of lines on the display device  */
#define MENULINES      3         /* Number of lines to display menus on    */
#define NUM_SEL_KEYS   3

#define NULL           0          /* Nothing, empty, void(management),Nada */
#define RADIOLINKSIZE  12         /* Max # of sub menus to be linked       */
#define RADIOLINKLARGE 32         /* Max # of sub menus for DUPS Menu      */
#define ROWSIZE 10
#define COLUMNSIZE 5
#define LANGSIZE 5
#define ASIAN_LANGUAGE_START 5

//#define MAXSCROLLMENUS 22
//#define SCROLLBUFFERSIZE ((LINESIZE+1) * MAXSCROLLMENUS +1)
#define SCROLLBUFFERSIZE ((LINESIZE+1) * RMAXPARAMETERS +1)

#define FILLCHAR     ' '
#define VISIBLE      0
#define INVISIBLE    1

#define NOCHAR 0              /* Means display no characters in FormatStr */
#define NUM_OUTPUT_DEVICES 2  /* VF screen & terminal */

#define VF_DEVICE          0
#define VF_DEVICE_BIT      1

#define TERM_DEVICE        1
#define TERM_DEVICE_BIT    2

#define BARGRAPH_VFD       0
#define BARGRAPH_QVGA      1
#define RATE_SLOWEST  BIT0
#define RATE_SLOW     BIT1
#define RATE_NORMAL   BIT2
#define RATE_FAST     BIT3
#define RATE_FASTEST  BIT4

#define MIN_TRIGGER_FORCE_DEFAULT_2IN  50
#define MIN_TRIGGER_FORCE_DEFAULT_3IN 100
#define GAIN_FACTOR_DEFAULT       1421
#define VELOCITY_PC_DEFAULT          1
#define FORCE_PC_DEFAULT_2IN        49
#define FORCE_PC_DEFAULT_3IN        99
#define IDLE_SPEED_DEFAULT          30
#define RT_COMP_DEFAULT             50
#define FORCE_STEP_AT_EXTERNAL    0x7d
#define AMP_STEP_AT_EXTERNAL      0x7d
#define ENERGY_BRAKE_TIME_DEFAULT 1000
#define ENERGY_BRAKE_AMP_DEFAULT    10 
#define AMP_DECAY_PERCENT_DEFAULT    3
#define LEAVINGHOMEFORCEMICROLO     3
#define LEAVINGHOMEFORCEMICROHI     7

#define NUMBER_OF_CODES             47 /* # of secret codes in menu.c */



/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

enum LineNums { ClrAll, Clr1, Clr2, Clr3, Clr4, Clr123 };


typedef struct {
   UINT16  Low;
   UINT16  Hi;
} UNION_UINT16;

typedef union {
   BOOLEAN        bool;
   UNION_UINT16   uint16;
} UNION_BOOL_UINT16;

enum LEVEL {                      /* Security level of user                */
   OPERATOR,                      /* Lowest level of security              */
   SETUP,                         /* Middle level of security              */
   MAINTAINENCE,                  /* Highest level of customer security    */
   BRANSON   };                   /* Level for Branson personnel only      */

enum FORMAT {                     /*  US Format (units)  SI Format (units) */
   PERCENT,                       /*        xxx     %          xxx     %   */
   FORCE,                         /*       xxxx    lb         xxxx     N   */
   FORCEDIV10,                    /*     xxxx.x    lb         xxxx     N   */
   TIME,                          /*     xx.xxx     S       xx.xxx     S   */
   PRESSURE,                      /*        xxx    PSI         xxx   KPA   */
   DISTANCE,                      /*     x.xxxx    in      xxx.xxx    mm   */
   DISTANCE3,                     /*     x.xxxx    in       xx.xxx    mm   */
   FREQUENCY,                     /*      xxxxx    Hz        xxxxx    Hz   */
   FREQOFFSET,                    /*       Sxxx    Hz         Sxxx    Hz   */
   ENERGY,                        /*     xxxxxx     j       xxxxxx     j   */
   COUNTER,                       /*  xxxxxxxxx          xxxxxxxxx         */
   VELOCITY,                      /*      xx.xx  in/s        xxx.x  mm/s   */
   WATTS,                         /*      xxxx   W            xxxx  W      */
   BARGRAPH,                      /* [____|____]        [____|____]        */
   TIMEDATE,                      /* xx:xx xx/xx/xx                        */
   PERCENTX10,
   ENERGYDIV10,
   INTEGER,
   LONGTIME,
   MICRONS,
   POWERWATTS
};

enum FORMAT_AMP_PWR {
	POWER,
	MIC
};
/* The following structures are used to set up the variable format table, */
/* see notes in MENU.C */

struct var_format_def1
{
   SINT8   Units[5];       /* Name of units, up to 4 chrs */
   UINT8   LeftDigits;     /* Max # of digits left of decimal point */
   UINT8   RightDigits;    /* # of digits right of decimal point */
   UINT8   Increment;      /* Change in value with + or - keypress */
   BOOLEAN ShowSign;       /* TRUE to display + or - sign */
   SINT32  ConvMult;       /* Conversion multiplier */
   SINT32  ConvDiv;        /* Conversion divisor */
};

struct var_format_def2
{
   struct var_format_def1 English;
   struct var_format_def1 Metric;
};

struct var_format_AmpPower
{
	struct var_format_def1 Percent;
	struct var_format_def1 Unit;
};

extern struct var_format_def2 VarFormatTable[];
extern struct var_format_AmpPower VarFormatTableAmpPower[];

enum CTRL_LEVEL {                /* Lowest model this feature will be on   */
   LEVEL_DEPOT = 0x001,
   LEVEL_t     = 0x010,          /*                                        */
   LEVEL_e     = 0x020,          /*                                        */
   LEVEL_a     = 0x030,          /*                                        */
   LEVEL_ea    = 0x040,          /*                                        */
   LEVEL_d     = 0x050,          /*                                        */
   LEVEL_f     = 0x060,          /*                                        */
   LEVEL_TEST  = 0x0ffff         /* Make sure 16 bit value so nvram as     */
   };                            /* configured from Fisher Rosemont works  */


/* This enum is required for the automatic conversion process from ver 6.00 or 7.02 to ver 8.00 and above */

enum MODEL_V600 {     
   MODEL1 = 1,     
   MODEL2,           
   MODEL3,           
   MODEL4,           
   MODEL5,           
   MODEL6,           
   MODEL7    }; 
   
   
enum ACTUATOR {                   /* What actuator is required             */
   AE = BIT1,                     /*                                       */
   AO = BIT2,                     /*                                       */
   AED = BIT3,                     /*                                       */
   AOD = BIT4,                     /*                                       */
   AES = BIT5,                     /*                                       */
   MICRO = BIT6,                   /* Replaced AOS with MICRO               */
   AEF = BIT7,                     /*                                       */
   AOF = BIT8,                     /*                                       */
   HGUN = BIT9,
   DONTCARE = 65535u};            /*                                       */

/* Reordered frequency designators and changed values from 1 to 4 per conversation
   with Barry Kymer on 9-8-00 */
enum FREQTYPE {                   /* What PS frequency                     */
   FREQ15KHZ = 1,                 /*                                       */
   FREQ20KHZ,                     /*                                       */
   FREQ30KHZ,
   FREQ40KHZ,
   FREQ50KHZ,                     /* Reserve for future                    */
   FREQ60KHZ};                    /* For Ahmet special                     */             

enum MODES {                      /* All possible welding modes            */
   TIMEMODE = BIT0,               /* TIMEMODE   = 0x0001                   */
   ENERGYMODE = BIT1,             /* ENERGYMODE = 0x0002                   */
   PKPOWERMODE = BIT2,            /* PKPOWERMODE = 0x0004                  */
   COLLAPSEMODE = BIT3,           /* COLLAPSEMODE = 0x0008                 */
   ABSOLUTEMODE = BIT4,           /* ABSOLUTEMODE = 0x0010                 */
   GRDDETECTMODE = BIT5,          /* GRDDETECTMODE = 0x0020                */
   TECMODE = BIT6,                /* TECMODE = 0x0040                      */
   CONTINUOUSMODE = BIT7,         /* CONTINUOUSMODE = 0x0080               */
   ALLMODES = BIT0 | BIT1 | BIT2 | BIT3 | BIT4 | BIT5 | BIT6 | BIT7 };
 

enum PAGESIZE {                   /* All possible PAGE SIZE                */
   PAGESIZE11 = BIT0,             /* PAGESIZE11 = 0x0001                   */
   PAGESIZE14 = BIT1,             /* PAGESIZE17 = 0x0002                   */
   PAGESIZEA4 = BIT2,             /* PAGESIZEA4 = 0x0004                   */
   PAGESIZE17 = BIT4 };           /* PAGESIZE16 = 0x0010                   */

enum  MASK1  {
   DUPS = 0x1L,                   //DUPS - BIT0
   LE = 0x2L,                     //Encoder - BIT1
   CONF = 0x4L,                   //Configured - BIT2         
   QVGA = 0x8L,                   //QVGA H/W- BIT3
   PC379 = BIT4,                  /* TRUE when old system controller (379) */
   PC594 = BIT5,                  /* TRUE when new system controller (594) */
   VGA = 0x0040L                  /* VGA  H/W*/    
   };             

enum  MASK2 {
   EC   = 0x1L,                   /* Error code */
   CUS  = 0x2L,                   /* Custom */ 
   WS   = 0x4L,                   /* Weld Status */
   DEPO = 0x8L,                   /* Depot */ 

   V_OL = 0x10L,                  /* Voltage overload */
   C_OL = 0x20L,                  /* Current overload */
   F_OL = 0x40L,                  /* Frequency overload */
   P_OL = 0x80L,                  /* Phase overload */
   HE   = 0x100L,                 /* Hold enabled */
   ALR  = 0x200L,                 /* Alarms */ 
   VEL  = 0x400L,                 /* velocity reporting */ 
   HH   = BIT11,                  /* Handheld enabled */ 
   EP_E = BIT12,                  /* External preset enabled. */
   HSC  = BIT13,                  /* HSC menu Enabled. */ 
   SBL_EN = BIT14,                /* SBL enabled globally */
   CAL  = BIT15,                  /* Recal code 300 reporting */
   };

enum ADVANCE {                    /* Conditions to advance to next menu    */
   SELECTKEY,                     /*  - when the Select key is pressed     */
   PALMBUTTONS,                   /*  - when palm buttons & trigger exist  */
   TEST,                          /*  - when the Test button is hit        */
   FLAG    };                     /*  - when Flag is set TRUE              */ 

enum NAME_PRESET {
   NAME_MODE = 1,                 /* Auto name using current weld mode     */
   NAME_CURRENT,                  /* Auto name using current preset name   */
   NAME_NEW   };                  /* Auto name using dest. preset name     */

enum PRESET_FUNCTION {
   FUNCTION_CLEAR = 1,            /* Preset function - Clear               */
   FUNCTION_RECALL,               /* Preset function - Recall              */
   FUNCTION_INFO,                 /* Preset function - Information         */
   FUNCTION_VERIFY,               /* Preset function - Verify              */
   FUNCTION_SAVE  };              /* Preset function - Save                */


enum MENUS {
   _TITLE = 1,
   _TEXT,
   _SUBMENU,                      /* Submenus on a new display page        */
   _HSUBMENU,                     /* Submenus scrolled on a horizontal line*/
   _HHMM,
   _DATE,
   _CHOICE,
   _ALPHA,
   _VARIABLE,                     /* Variable of type signed short         */
   _RADIO,
   _RADIOMENU,
   _TOGGLE,                       /* 2 choices, but not ON/OFF, no submenu */
   _HVARIABLE,                    /* Variable scrolled on a horizontal line*/
   _ALARM,
   _RADIOLARGEMENU,               /* Currently used for DUPS only          */
   _RADIOLARGE,                   /* Used in conjunction with RADIOLARGEMENU */
   _GRAPH,
   _MENUEND,
   _VGATEXT,
   _VGATEXTBOX,
   _VGALINE,
   _VGARUNSCREEN,
   _VGABUTTON,
   _VGABOTTOMHALF,
   _VGACHECK,
   _VGAGRAPH,
   _VGALISTBOX,
   _VGAMSGSCREEN,
   _VGAPOINTER,
   _VGATABLE,
   _RSPARAMETER   };

 enum RUN_PARAM {
   WELDRESULTS = 0,
   RCYCLECOUNT,
   RTIME,
   RPKPWR,
   RENERGY,
   RVELOCITY_AED,
   RVELOCITY_AEF,
   RWABSDIST,
   RTABSDIST,
   RWCOLDIST,
   RTCOLDIST,
   RAMPSTART,
   RAMPEND,
   RFORCEA,
   RFORCEB,
   RFORCE,
   RSYSPRESS,
   RFREQMIN,
   RFREQMAX,
   RFREQSTART,
   RFREQEND,
   RFREQCHG,
   RPRESETNUM,
   RCYCLETIME,
   RMAXPARAMETERS,
   RUNPARAMSIZER = 65535 };

enum RADIOMASK {
   RADIO_0 = 0x0001,   
   RADIO_1 = 0x0002,   
   RADIO_2 = 0x0004,   
   RADIO_3 = 0x0008,   
   RADIO_4 = 0x0010,   
   RADIO_5 = 0x0020,   
   RADIO_6 = 0x0040,
   RADIO_7 = 0x0080,
   RADIO_8 = 0x0100,
   RADIO_9 = 0x0200,
   RADIO_10 = 0x0400,
   RADIO_11 = 0x0800,
   RADIO_12 = 0x1000,
   RADIO_13 = 0x2000,
   RADIO_14 = 0x4000,
   RADIO_15 = 0x8000,
   RADIO_16 = 0x10000,
   RADIO_17 = 0x20000,
   RADIO_18 = 0x40000,
   RADIO_19 = 0x80000,
   RADIO_20 = 0x100000,
   RADIO_21 = 0x200000,
   RADIO_22 = 0x400000,
   RADIO_23 = 0x800000,
   RADIO_24 = 0x1000000,
   RADIO_25 = 0x2000000,
   RADIO_26 = 0x4000000,
   RADIO_27 = 0x8000000,
   RADIO_28 = 0x10000000,
   RADIO_29 = 0x20000000,
   RADIO_30 = 0x40000000,
   RADIO_31 = 0x80000000,
   RADIOSIZER = 0xFFFFFFFF }; 

enum RS232_MASK {
   COMPUWELD = RADIO_1,
   TERMINAL = RADIO_2,
   ASCIICOMMA = RADIO_3,
   ASCIITAB = RADIO_4,
   ASCIISPACE = RADIO_5,
   RS232DISABLED = RADIO_6 };

enum GRAPH_TYPE {
   POWER_GRAPH,
   FREQUENCY_GRAPH,
   AMPLITUDE_GRAPH,
   FORCE_GRAPH,
   VELOCITY_GRAPH,
   COL_DIST_GRAPH,
   POWER_COL_GRAPH,
   POWER_FORCE_GRAPH,
   FORCE_COL_GRAPH   
   };

enum COLOR {
   COLOR_DEFAULT = 0,
   COLOR_BLACK,
   COLOR_BLUE,
   COLOR_RED,
   COLOR_GREEN,
   COLOR_BROWN,
   COLOR_MAGENTA,
   COLOR_CYAN,
   COLOR_LIGHTGREY,
   COLOR_GREY,
   COLOR_YELLOW,
   COLOR_WHITE
   };    

enum FONT {
   FONT_DEFAULT = 0,
   FONT_1,
   FONT_2
   };    
 
typedef struct menu0 {  
   void     *ptr;                  /* Pointer to one of the next structures */
   enum     MENUS type;            /* Which structure is it pointing to     */
   } MENU;


typedef struct menu1 {             /* Text only, top line title             */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16   CenterFlag;            /* TRUE if should center justify field   */
   UINT16   PageFlag;              /* TRUE if page information should show  */
   UINT16   CaseFlag;              /* TRUE if text should be uppercased     */
   } TITLE;


typedef struct menu2 {             /* Text only, lines 2-4, information     */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16   JustifyFlag;           /* TRUE:Right justify  FALSE:Left justify*/
   void     (*func)(UINT32);       /* Pointer to function to execute        */
   UINT32   Arg;                   /* Argument for function call above      */
   } TEXT;

typedef struct menu3 {             /* Text used as a choice for sub menus   */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func1)(UINT32);      /* Function to execute before menu called*/
   UINT32   Arg;                   /* Argument for function call above      */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   enum     ADVANCE next;          /* SELECTKEY/PALMBUTTONS/TEST/FLAG       */
   BOOLEAN  *flag;                 /* Pointer to Flag if FLAG is selected   */
   UINT16   Timeout;               /* Length of time to display menu        */
   UINT16   UpdateTime;            /* Time before display is updated        */
   void     (*func2)(void);        /* Function to execute after menu called */
   } SUBMENU;


typedef struct menu4 {             /* Text used as a choice for sub menus   */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func1)(void);        /* Function to execute before menu called*/
   UINT16   *Vptr;                 /* ?                                     */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   enum     ADVANCE next;          /* SELECTKEY/PALMBUTTONS/TEST/FLAG       */
   BOOLEAN  *flag;                 /* Pointer to Flag if FLAG is selected   */
   void     (*func2)(void);        /* Function to execute before menu call  */
   } HSUBMENU;


typedef struct menu5 {             /* Text with time                        */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   SINT32   *Hour;                 /* Pointer to hour in 24 hour format     */
   SINT32   *Minute;               /* Pointer to minutes                    */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } HHMM;


typedef struct menu6 {             /* Text with date                        */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   SINT32   *Month;                /* Pointer to month  JAN = 1             */
   SINT32   *Date;                 /* Pointer to date                       */
   SINT32   *Year;                 /* Pointer to year   1995=95, 2003=03    */ 
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } DATE;


typedef struct menu7 {             /* Text with 2 choices, submenu with ON  */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   BOOLEAN  *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16   *Rptr;                 /* Pointer to return value (TRUE/FALSE)  */
   STR      **Sptr1;               /* Pointer to choice 1 string (FALSE)    */
   STR      **Sptr2;               /* Pointer to choice 2 string (TRUE)     */
   MENU     *Mptr;                 /* Pointer to sub menus (if choice 2)    */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   SINT16   Timeout;               /* Length of time to display menu        */
   SINT16   UpdateTime;            /* Time before display is updated        */
   void     (*func)(void);         /* Pointer to function to execute        */
   } CHOICE;             


typedef struct menu8 {             /* Text, selecting alpha characters      */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   STR      **TtlPtr;              /* Pointer to string for title in entry  */
   STR      **Pptr;                /* Pointer to string to use as prompt    */
   UINT16   NumChar;               /* Number of characters allowed          */
   UINT16   StartPos;              /* Position on display line for entry    */
   UINT16   Hide;                  /* TRUE if entry should not be displayed */
   SINT8    *Rptr;                 /* Pointer to return string              */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } ALPHA;


typedef struct menu9 {             /* Text with a variable (short) field    */
/****************************************************************************/
/*  Text string to contain ampersands (&&) where the units should be disp.  */
/****************************************************************************/

   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   enum     MODES mode;            /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16   disable;               /* TRUE if variable can be disabled      */
   UINT16   *DisableFlag;          /* Pointer to disable/enable flag        */
   UINT16   BitMask;               /* Bit used for this variable enable     */
   enum     FORMAT format;         /* PERCENT/FORCE/TIME/DISTANCE/FREQUENCY */
   UINT16   digits;                /* Number of digits to display (0=all)   */
   UINT16   Security;              /* TRUE:Security on, supress display (*) */
   SINT32   *Vptr;                 /* Pointer to value                      */
   SINT32   *ptrmin;               /* Pointer to minimum value accepted     */
   SINT32   *ptrmax;               /* Pointer to maximum value accepted     */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } VARIABLE;


typedef struct menu10 {            /* Radio menus linked together           */
/****************************************************************************/
/*  This structure will allow two or more (up to 10) sub menu items to be   */
/*  linked.  This means if any item in the list is turned on all other      */
/*  items in the list will be turned off.  Only one item can be selected.   */
/****************************************************************************/
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   *Vptr;                 /* Pointer to value                      */
   enum     MODES Value;           /* Value                                 */
   enum     RADIOMASK RadioMask;   /* Which index in list is this entry     */
   STR      **Sptr1;               /* Pointer to string (OFF = FALSE)       */
   STR      **Sptr2;               /* Pointer to string (ON = TRUE)         */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } RADIO;                      

                                 
typedef struct menu11 {            /* Radio menus linked together           */
/****************************************************************************/
/*  This structure will allow displaying of a choice of radio menus.        */
/*  Selecting the choice will bring up a list menus allowing the choice to  */
/*  be changed.  This structure only deals with displaying the choice.      */
/****************************************************************************/
   STR      *Tptr;                 /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   void     (*func1)(void);        /* Function to execute before menu called*/
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   STR      **Cptr[RADIOLINKSIZE]; /* Pointers to strings of all choices    */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   void     (*func2)(void);        /* Function to execute after menu called */
   } RADIOMENU;                  

                                 
typedef struct menu12 {            /* Text with 2 choices other then ON/OFF */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1 ;                /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   BOOLEAN  *Eptr;                 /* Pointer to flag to see if display line*/
   BOOLEAN  *Rptr;                 /* Pointer to return value (TRUE/FALSE)  */
   STR      **Sptr1;               /* Pointer to choice 1 string (FALSE)    */
   STR      **Sptr2;               /* Pointer to choice 2 string (TRUE)     */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } TOGGLE;                 


typedef struct menu13 {            /* Text with 2 choices other then ON/OFF */
   STR     **Tptr;                 /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   enum     MODES mode;            /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT8    *Eptr;                 /* Pointer to flag to see if display line*/
   UINT16   *DisableFlag;          /* Pointer to disable/enable flag        */
   void     (*func1)(void);        /* Function to execute before menu called*/
   enum     FORMAT format;         /* PERCENT/FORCE/TIME/DISTANCE/FREQUENCY */
   UINT16   Security;              /* TRUE:Security on, supress display (*) */
   SINT32   *Vptr;                 /* Pointer to value                      */
   enum PARAM ID;                  /* Unique identifier for this parameter  */
   enum RUN_PARAM Index;           /* Unique identifier for this parameter  */
   void     (*func2)(void);        /* Pointer to function to execute        */
   } HVARIABLE;


typedef struct menu14 {            /* Text only, lines 2-4, information     */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT32   BitLoc;                /* Bit Mask used for this menu enable    */
   UINT32   *Aptr;                 /* Pointer to General Alarm Variable     */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } ALARM;


typedef struct menu15 {            /* Radio menus linked together           */
/****************************************************************************/
/*  This structure will allow displaying of a choice of radio menus.        */
/*  Selecting the choice will bring up a list menus allowing the choice to  */
/*  be changed.  This structure only deals with displaying the choice.      */
/****************************************************************************/
   STR      *Tptr;                 /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINANCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   EnableFlag;            /* TRUE if it should look at EnableValue */
   void     (*func1)(void);        /* Function to execute before menu called*/
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   STR      **Cptr[RADIOLINKLARGE];/* Pointers to strings of all choices    */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   void     (*func2)(void);        /* Function to execute after menu called */
   } RADIOLARGEMENU;


typedef struct menu16 {            /* Radio(large) menus linked together    */
/****************************************************************************/
/*  This structure will allow two or more (up to 10) sub menu items to be   */
/*  linked.  This means if any item in the list is turned on all other      */
/*  items in the list will be turned off.  Only one item can be selected.   */
/****************************************************************************/
   STR      *Tptr;                 /* Pointer to text string                */
   UINT16   *Lptr;                 /* Pointer to locked array               */
   UINT16   *Vptr;                 /* Pointer to value                      */
   UINT16   Value;                 /* Value                                 */
   STR      **Sptr1;               /* Pointer to string (OFF = FALSE)       */
   STR      **Sptr2;               /* Pointer to string (ON = TRUE)         */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   void     (*func)(void);         /* Pointer to function to execute        */
   } RADIOLARGE;

typedef struct menu17 {
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;
   enum     PARAM ID;              /*Param ID*/
   }GRAPH;

typedef struct menu18 {             /* Text only, lines 2-4, information    */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func)(UINT32);       /* Pointer to function to execute        */
   UINT32   Arg;                   /* Argument for function call above      */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   enum     FONT font;             /* Text Font                             */ 
   enum     COLOR TextColor;       /* Text Color*/
   } VGATEXT;
   
typedef struct menu19 {             /* Text only, lines 2-4, information    */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   void     (*func)(UINT32);       /* Pointer to function to execute        */
   UINT32   Arg;                   /* Argument for function call above      */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   enum     FONT font;             /* Text Font                             */  
   enum     COLOR fillcolor;       /* Text Box fill Color                   */
   enum     COLOR TextColor;       /* Text Color                            */
   } VGATEXTBOX;

typedef struct menu20 {            /* Text only, lines 2-4, information     */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     COLOR Linecolor;       /* Line Color                            */
   } VGALINE;

typedef struct menu21 {            /*                                       */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func)(void);         /* Pointer to function to execute        */
   UINT16   *CycleCount;           /* Pointer to Cycle Count variable       */
   BOOLEAN  *AllColumnFlag;        /* Pointer to send all columns or not    */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     FONT font;             /* Text Font                             */  
   } VGARUNSCREEN;

typedef struct menu22 {             /* Text only, lines 2-4, information    */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func)(UINT32);       /* Pointer to function to execute        */
   UINT32   Arg;                   /* Argument for function call above      */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   enum     FONT font;             /* Text Font                             */  
   enum     COLOR TextColor;       /* Text Color                            */
   } VGABUTTON;

typedef struct menu23 {             /* Text only, lines 2-4, information    */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   void     (*func)(void);         /* Pointer to function to execute        */
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   BOOLEAN  RefreshReq;            /* Flag to see if refresh required       */
   UINT16   RefreshInterval;       /* Refresh Intervalin msec               */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     COLOR fillcolor;       /* Text Box fill Color                   */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   } VGABOTTOMHALF;

typedef struct menu24 {             /* Text only, lines 2-4, information    */
   STR      **Tptr;                /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   void     (*func)(void);         /* Pointer to function to execute        */
   UINT16   XCoordinate;           /* X Co-ordinate                         */
   UINT16   YCoordinate;           /* Y Co-ordinate                         */
   BOOLEAN  *Selected;             /* Whether selected or not               */
   enum     FONT font;             /* Text Font                             */  
   enum     COLOR TextColor;       /* Text Color                            */
   } VGACHECK;

typedef struct menu25 {            /*                                       */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func)(void);         /* Pointer to function to execute        */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   enum     FONT font;             /* Text Font                             */  
   enum     COLOR LineColor;       /* Line Color                            */  
   } VGAGRAPH;

typedef struct menu26 {            /*                                       */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   void     (*func)(void);         /* Pointer to function to execute        */
   UINT16   *AddlInfo;             /* Pointer to additional Info            */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   enum     COLOR fillcolor;       /* Fill Color                            */  
   } VGALISTBOX;

typedef struct menu27 {            /*                                       */
   STR      **Tptr1;               /* Pointer to text string                */
   STR      **Tptr2;               /* Pointer to text string                */
   STR      **Tptr3;               /* Pointer to text string                */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   void     (*func)(void);         /* Pointer to function to execute        */
   UINT16   Timer;                 /* Timer in msec 0 means no timeout      */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     FONT font;             /* Text Font                             */  
   enum     COLOR TextColor;       /* Text Color                            */  
   enum     COLOR fillcolor;       /* Fill Color                            */  
   } VGAMSGSCREEN;

typedef struct menu28 {            /*                                       */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   SINT16   EnableFlag;            /* TRUE if should look at EnableValue    */
   UINT16   *Eptr;                 /* Pointer to flag to see if display line*/
   MENU     *Mptr;                 /* Pointer to sub menus                  */
   } VGAPOINTER;

typedef struct menu29 {            
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   SINT16   mode;                  /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   UINT8    NosOfRows;             /*Total number of rows in the table      */
   UINT8    NosOfColumns;          /*Total number of columns in the table   */
   void     (*func)(void);         /* Function to execute before menu called*/
   STR      **Rptr[ROWSIZE];       /* Pointers to strings of all choices    */
   STR      **Cptr[COLUMNSIZE];    /* Pointers to strings of all choices    */
   UINT16   X1Coordinate;          /* X1 Co-ordinate                        */
   UINT16   Y1Coordinate;          /* Y1 Co-ordinate                        */
   UINT16   X2Coordinate;          /* X2 Co-ordinate                        */
   UINT16   Y2Coordinate;          /* Y2 Co-ordinate                        */
   enum     PARAM ID;              /* Unique identifier for this parameter  */
   } VGATABLE;                  

typedef struct menu30 {            /* Text with 2 choices other then ON/OFF */
   enum     CTRL_LEVEL CtrlLevel;  /* Lowest CtrlLevel to display on        */
   enum     ACTUATOR act;          /* What actuator is required             */
   enum     MODES mode;            /* Which welding mode                    */
   enum     LEVEL level;           /* OPERATOR/SETUP/MAINTAINENCE/BRANSON   */ 
   UINT32   Mask1;                 /* what is important to display          */
   UINT32   Cond1;                 /* this menu                             */
   UINT32   Mask2;                 /* what condition are required to        */
   UINT32   Cond2;                 /* display this menu                     */
   enum RUN_PARAM Index;           /* Unique identifier for this parameter  */
   } RSPARAMETER;

typedef struct menuend {     
   SINT8    junk;                  /* Indicate end of list                  */
   } MENUEND;

typedef struct Codes {
   STR    *Password;             /* Pointer to the password string           */
   STR    *Ptr;                  /* Pointer to entered digits, menu will use */
   void   (*func)(void);         /* Pointer to function to execute           */
   UINT16 ID;                    /* Menu ID number if menu is displayed      */
} CODES;
   
/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/



void BUCMenu(void);
void DebugMenu(void);
void VelocityOn(void);
void VelocityOff(void);
void CreateSecretCodes(void);
void RestoreDefaults(void);
void EnableTestingMenu(void);
void EnableSpecialsMenu(void);


void SlowActADComm(void);
void FastActADComm(void);
void SlowerActADComm(void);
void SelectOldBoard(void);
void SelectNewBoard(void);
void ConfigSBeam(void);
void ConfigLoadcell(void);
void DisableCode300(void);
void EnableCode300(void);

void ConfigAEDSbeam(void);
void ConfigAEFSbeam(void);
void ConfigMICROSbeam(void);
void Config50mmMICRO(void);
void MicroEncoder(void);
void OLDEncoder(void);
void ConfigOriginal_MICRO(void);
void ConfigMaxMinValues(void);

void FormatVariables( SINT32 Value, enum FORMAT format, SINT8 String[],
 UINT8 MaxLen, BOOLEAN Metric );

void FormatNums( SINT32 Number, enum FORMAT format, SINT8 String[],
 UINT8 MaxLen, BOOLEAN Metric );

SINT32 ConvertInternalExternal( SINT32 Value, enum FORMAT format, BOOLEAN Metric );

SINT32 ConvertExternalInternal( SINT32 Number, enum FORMAT format,
 BOOLEAN Metric );

UINT8 WaitKeyPress(void);
void ShowEstopMessageOn(void);
void ShowEstopMessageOff(void);

MENU *GetCurrentMenu(void);


void AlarmOn(void);
void AlarmOff(void);
void EnablePLCTiming(void);
void UpdateHWConfiguration(enum MASK1 HWConfig, BOOLEAN Enabled);
void UpdateSWConfiguration(enum MASK2 SWConfig, BOOLEAN Enabled);
BOOLEAN IsHWConfigured(UINT16 HWType);
void EnableDiagnostics(void);
void DistanceSS(void);
void DupsControl(void);
void EnableHSCandSBL(void);
void DisableHSCandSBL(void);
void EnableUSEncoder(void);
void EnableMetricEncoder(void);
void EnableTF(void);
void SetSpringRate3(void);
void SetSpringRate4(void);
void SaveCalibration(void);
void DisplayChecksum(void);
void SetContLevelt(void);
void SetContLevelea(void);
void SetContLeveld(void);
void SetContLevelf(void);
void SetContLeveldepot(void);
void SetContLeveltest(void);

#endif
