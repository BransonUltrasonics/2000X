/* $Header:   D:/SWLab/VMdb/2000Series/INC/IPSATYPE.H_V   2.24   Jun 10 2004 09:39:56   BKymer  $ */
#ifndef IPS_ACTION_ID_TYPE_H
#define IPS_ACTION_ID_TYPE_H 1
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
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: ips_action_id_type 

   Filename:  ipsatype.h   


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
        0           03/07/96      Mark L      Initial Version
        1           04/23/96      Mark L      Add WRITE & READ_PRESET
        2           07/13/96      MAL         ADD more parameters
        3           07/22/96      MAL         Add more parameters
        4           3/30/97       LAM         welddata test
        5           4/21/97       LAM         chged start weld data to fun26
        6           04/28/97      LAM         cleanup            
        7           05/20/97      PhilJ       added special Branson Host parameters
        8.2.8       07/14/97      LAM         added error message ids               
        8.2.9       08/20/97      PhilJ       added CHECKSUM_ERROR id               
              2.9                 04.20.98      JBerman     Added 269 & 270 into the structure.  
        2.10        05/11/98      PhilJ       reorganized codes                     
        2.11        06/19/98      PhilJ       added more codes 
        2.12        12/07/98      LAM         split cycle aborts and control limits
        2.14        04/19/99      OFI         changed for DIAB
        2.15        09/27/99      OFI         Add SET_FORCE_RAMPS
        2.16        09/28/99      LAM         corrected SET_FORCE_RAMPS
        2.17        06/09/00      JLH         Changed numbers of several Branson host commands.
        2.19        07/10/00      JLH         RCS updates.
        2.20        07/28/00      JLH         Restored READ_PRESET and RECALL_PRESET command codes.
        2.21        11/09/00      JLH         Exchanged function codes for SET_ACT_MODELNUMBER and
                                               SET_PS_MODELNUMBER.
        2.22        10-02-02      BEKymer     Added ONBOARD_DIAGNOSTICS as a host command for
                                               Quality and manufacturing to test 332 boards.
        2.23        12-27-03      VSharma     Added 4 new Host commands DOWNLOAD_CURRENT_PRESET
                                              (changed from READ_PRESET),RESET_ALARMS,VERIFY_PRESET,
                                              UPLOAD_CURRENT_PRESET for Ver9.00c. 
        2.24        04-05-04      BEKymer     Add REQUEST_GRAPH_DATA
        
                                               
                                               
------------------------------- DESCRIPTION -----------------------------------

 This header contains the definitions of Command Ids when the IPS Type Id indicates
 the IPS is an Action type.  
 ------------------------------ INCLUDE FILES ----------------------------------
*/
     

/*
 --------------------------------- DEFINES -------------------------------------
*/

/* Define ranges for each of the Action commands */

#define FIRST_ASCII_CMD    1                               /* used for ascii diag */
#define LAST_ASCII_CMD     6

#define FIRST_SYNC_CMD    16                                /* These are for the GPS                  */
#define LAST_SYNC_CMD     31

#define FIRST_RSDM_CMD    32                                /* Remote Software Download               */
#define LAST_RSDM_CMD     34

#define FIRST_REDU_CMD    48
#define LAST_REDU_CMD     63

#define FIRST_MAD_CMD     25
#define LAST_MAD_CMD      (MAX_IPS_ACTION_CMD - 1)

/* This is equivilent to PARAMETER_TYPE_UNKNOWN from        */
/* the type PARAMETER_DATA_TYPE_TYPE in paramngr.h */
#define   NO_ACTION_ARG   0u
 
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/ 

typedef enum
   {                    
   DOWNLOAD_CURRENT_PRESET          = 1,
   RECALL_PRESET                    = 2,
   SET_CURRENT_PRESET_PARAMETERS    = 3,
   SET_ENERGYMLS                    = 16,
   SET_ENERGYPLS                    = 17,
   SET_ENERGYMLR                    = 18,
   SET_ENERGYPLR                    = 19,
   SET_TIMEMLS                      = 20,
   SET_TIMEPLS                      = 21,
   SET_TIMEMLR                      = 22,
   SET_TIMEPLR                      = 23,
   RESET_ALARMS                     = 24,
   START_WELD_DATA                  = 26,
   UPLOAD_CURRENT_PRESET            = 28,
   SET_ENERGY_COMP                  = 29,
   SET_SCRUB_TIME                   = 30,
   SET_PEAKPOWER_CUTOFF             = 31,
   SET_ABSDIST_CUTOFF               = 32,
   SET_COLLDIST_CUTOFF              = 33,
   SET_GND_DETECT_CUTOFF            = 34,
   SET_AFTERBURST                   = 35,
   SET_TRIGGER_DELAY                = 36,
   SET_FREQ_OFFSET                  = 37,
   SUSPECT_LIMIT_RESET_REQ          = 38,
   REJECT_LIMIT_RESET_REQUIRED      = 39,
   SET_MPOWER_SLIMIT                = 40,
   SET_PPOWER_SLIMIT                = 41,
   SET_MPOWER_RLIMIT                = 42,
   SET_PPOWER_RLIMIT                = 43,
   SET_MCOLLAPSE_SLIMIT             = 44,
   SET_PCOLLAPSE_SLIMIT             = 45,
   SET_MCOLLAPSE_RLIMIT             = 46,
   SET_PCOLLAPSE_RLIMIT             = 47,
   SET_MABSOLUTE_SLIMIT             = 48,
   SET_PABSOLUTE_SLIMIT             = 49,
   SET_MABSOLUTE_RLIMIT             = 50,
   SET_PABSOLUTE_RLIMIT             = 51,
   SET_MTRIGDIST_SLIMIT             = 52,
   SET_PTRIGDIST_SLIMIT             = 53,
   SET_MTRIGDIST_RLIMIT             = 54,
   SET_PTRIGDIST_RLIMIT             = 55,
   SET_MMAXFORCE_SLIMIT             = 56,
   SET_PMAXFORCE_SLIMIT             = 57,
   SET_MMAXFORCE_RLIMIT             = 58,
   SET_PMAXFORCE_RLIMIT             = 59,
   SET_MFREQUENCY_SLIMIT            = 60,
   SET_PFREQUENCY_SLIMIT            = 61,
   SET_MFREQUENCY_RLIMIT            = 62,
   SET_PFREQUENCY_RLIMIT            = 63,
   SET_PREWELD_SEEK                 = 64,
   SET_POSTWELD_SEEK                = 65,
   SET_PRETRIGGER                   = 66,
   SET_MISSING_PART                 = 67,
   SET_ACTUATOR_CLEAR               = 68,
   SET_RAPIDTRAVERSE                = 69,
   SET_DIGITAL_FILTER               = 70,
   SET_TEST_AMPLITUDE               = 71,
   SET_GLOBAL_PRINTING              = 72,
   SET_WELD_HISTORY_PRINTING        = 73,
   SET_WELD_SUMMARY_PRINTING        = 74,
   SET_VELOCITY_GRAPH_PRINTING      = 75,
   SET_POWER_GRAPH_PRINTING         = 76,
   SET_COLLDIST_GRAPH_PRINTING      = 77,
   FORCE_GRAPH_PRINTING             = 78,
   SET_FREQ_GRAPH_PRINTING          = 79,
   SET_AMP_GRAPH_PRINTING           = 80,
   SET_AMPLITUDE                    = 81,
   SET_STROKELENGTH                 = 82,
   SET_XSCALE_GRAPH                 = 83,
   SEND_WELD_HISTORY                = 84,
   SAVE_PRESET                      = 85,
   SET_ADVANCE_COUNTERS             = 86,
   SET_AMP_CONTROL                  = 87,
   SET_BEEPERS                      = 88,
   SET_CUSTOM_ACT_LOGIC             = 89,
   SET_FREQ_CONTROL                 = 90,
   SET_HANDHELD_SYSTEM              = 91,
   SET_BARGRAPH_SCALE               = 92,
   SET_UNITS                        = 93,
   SET_HORNDOWN                     = 94,
   SET_ADJUST_WHILE_RUN             = 95,
   SET_CYLIN_DIAMETER               = 96,
   SET_DUAL_PRESSURE                = 97,
   SET_ENCODER                      = 98,
   SET_FEATURES                     = 99,
   SET_START_SCREEN                 = 100,
   SET_LANGUAGE                     = 101,
   SET_PRINTER                      = 102,
   SET_DIGITAL_POT                  = 103,
   SCROLL_BY_1_OR_3                 = 104,
   SETUP_PRINTING                   = 105,
   SET_CNTRL_LIMITS                 = 106,
   SET_COMPENSATION_MODES           = 107,
   SET_TIME_DATE                    = 108,
   SET_SUS_REJ                      = 109,
   SET_ABS_GRAPH                    = 110,
   SET_CYCLEABORTS                  = 111,
   REQUEST_GRAPH_DATA               = 112,
   VERIFY_PRESET                    = 136,

   RSDM_S_RECORD                    = 170,
   RSDM_SWITCH_BANKS                = 171,
   RSDM_GET_VERSION                 = 172,
   READ_ENTIRE_ERROR_LOG            = 173,
   READ_ERROR_LOG_ENTRIES_1_20      = 174,
   READ_ERROR_LOG_ENTRIES_21_40     = 175,
   READ_ERROR_LOG_ENTRIES_41_60     = 176,
   READ_ERROR_LOG_ENTRIES_61_80     = 177,
   READ_EVENT_LOG_ENTRIES           = 178,
   READ_SWARE_LOG_ENTRIES           = 179,
   CLEAR_ERROR_LOG_ENTRIES          = 180,
   CLEAR_EVENT_LOG_ENTRIES          = 181,
   CLEAR_SWARE_LOG_ENTRIES          = 182, 
   INITIATE_SOFTWARE_DOWNLOAD       = 183,
   INITIATE_WELDER_RESET            = 184,
   XLATE_ALARM_ID_TO_STRING         = 185,
   CLEAR_SINGLE_ACTUAL_ALARM        = 186,
   CLEAR_ALL_ACTUAL_ALARMS          = 187,
   RESET_WELD_ALARMS                = 188,
   STOP_WELD_DATA                   = 189,
   WELD_TIME                        = 190,
   WELD_ENERGY                      = 191,
   PEAK_POWER                       = 192,
   COLLAPSE_DISTANCE                = 193,
   HOLD_TIME                        = 194,
   HOLD_FORCE                       = 195,
   MAX_TIME_OUT                     = 196,
   TRIGGER_FORCE                    = 197,
   WELD_FORCE                       = 198,
   ABSOLUTE_DISTANCE                = 199,
   TIME_MLS                         = 200,
   TIME_PLS                         = 201,
   ENERGY_MLS                       = 202,
   ENERGY_PLS                       = 203,
   PRETRIGGER_ULS                   = 204,
   ENERGY_MLR                       = 205,
   ENERGY_PLR                       = 206,
   TIME_MLR                         = 207,
   TIME_PLR                         = 208,
   READ_ONE_ALARM                   = 209,
   READ_ALL_ALARMS                  = 210,
   CHECKSUM_ERROR                   = 211,

   /* BOARD - TEST IPS COMMANDS START HERE                        */
   /* BOARD - TEST commands ONLY after this point                 */
   BOARD_TEST_CLOCK_CHIP            = 123,
   BOARD_TEST_WATCH_DOG_RESET       = 124,
   BOARD_TEST_SPI                   = 130,
   BOARD_TEST_BATTRAM               = 131,
   BOARD_TEST_SRAM                  = 132,
   ONBOARD_DIAGNOSTICS              = 133,   /* Added 10-02 for Quality Dept */
   TEST_ERROR_LOG                   = 154,
   LIST_ALL_ALARM_IDS               = 161,
 
  
   /* ALL HOST COMMANDS ARE TO EXIST ABOVE THIS POSITION    */
   /* EXCEPT SPECIAL BRANSON COMMANDS WHICH START ABOVE 255 */

   SET_ACT_SERIALNUMBER             = 256,
   SET_ACT_MODELNUMBER              = 260,
   SET_CONTROLLEVEL                 = 258,
   SET_PS_SERIALNUMBER              = 259,
   SET_PS_MODELNUMBER               = 257,
   SET_SOFTWARE_SERIALNUMBER        = 261,
   SET_CYLINDER_DIAMETER            = 262,
   SET_CYLINDER_STROKE              = 263,

   RESET_PSLIFETIMECOUNTER          = 264,
   RESET_OVERLOADCOUNTER            = 265,
   RESET_GENALARMCOUNTER            = 266,
   SETUP_ERROR                      = 267,
   NACK_ERROR                       = 268,
   SET_ACTUATOR_CYLINDERDIAMETER    = 269,
   SET_ACTUATOR_STROKELENGTH        = 270,
   UPLOAD_REMOTE_CONFIG_PARMS       = 280,

   /* The UPS commands for the Digital Power Supply start at
      FUN = 512 */

   UPS_HARDWARE_INFO                = 512,
   UPS_SOFTWARE_INFO                = 513,
   UPS_PRESET_INFO                  = 514,
   REQ_PRESET_NUM                   = 515,
   PARAM_SET_SELECT                 = 516,
   UPLOAD_STATUS                    = 517,
   UPDATE_PRESET_PARAM              = 518,
   OVERLOAD_INFO                    = 519,

   IPS_ACTION_SIZER = 32768u
   } IPS_ACTION_ID_TYPE;

                                                           
/*                                                         
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/                                                         
                                                           
#endif /* IPS_ACTION_ID_TYPE_H */

