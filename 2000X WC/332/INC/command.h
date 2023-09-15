/* $Header:   D:/databases/VMdb/2000Series/INC/COMMAND.H_V   2.25.1.8.1.0   08 Mar 2011 02:58:20   PDwivedi  $ */
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
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      command.h


 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date      Author  Description
   ==========      ========  ======  ===========
      0             5/05/96          Initial
      1             9/09/96  LAM     cleanup
      2            04/28/97  LAM     cleanup            
      2.5          09.29.97  JBerman Added ColdStartPlus proto.
      2.7          06-28-04  BEKymer Add prototype for SetBucMenuToFactoryDefault(void)
      2.8          05-23-05  Bwadia  Moved defines from command.c
      2.9          07-25-05  Bwadia   Checked in for Ver10.0e 
      2.10         08-12-05  Bwadia  Added defines for VGA Export weld data command
      2.11         09-10-05  Bwadia  Print related host command defines added
      2.12         10-11-05  Bwadia  defines added for upload and download preset command 
      2.13         10-24-05  Bwadia  Added PMC command defines
      2.14         10-26-05  Bwadia  Added Sequencing command defines 
      2.15         11-22-05  Bwadia  Added error beep command
      2.16         12-07-05  Bwadia  Added command for printer offline alarm.
                                     Modified for tracker issue 3987
      2.17         12-20-05  Bwadia  Added command for USB offline alarm
                                     Modified for tracker issue 4029 and 4013        
      2.18         01-12-06  Bwadia  Defines added for USB and P/S view
                                     preset command. Modified for tracker 4017, 4018, 4049 
      2.19         02-07-06  Bwadia  Added command for screen setup entry. Also increased
                                     VGAAckBuf to 8K. Modified for tracker issue 4083  
      2.20         04-24-06  Bwadia  Horn scan abort command defines added 
      2.21         05-18-06  YGupta  Defines added for Command Size.
      2.22         12-26-06  NHAhmed Changed the #define MENU_PTRS_COMMAND_SIZE to 15.
                                     and added #define SBC_SW_VERSION_LENTGH.
      2.23         01-03-06  NHAhmed Added #define NO_DATA_COMMAND_SIZE.
      2.24         03-12-07  NHAhmed Added SHOW_WELDINGON_MESSAGE.
      2.25         03-27-07  NHAhmed Added SEND_QUALITYLIMITS_DATA & 
                                     QUALITYLIMITS_DATA_COMMAND_SIZE.
      2.26         10-22-07  NHAhmed Changes done for LangTest phase 0
      2.27         01-11-08  NHAhmed Defined new commands and their length for muli-language support.
      2.28         04-14-08  NHAhmed Defined some new commands and their length.Also updated 
                                     enum MAP_ID 
      2.29         06-06-08  NHAhmed Defined some new commands and their corresponding length.
      2.30         08-01-08  NHAhmed Defined two new commands SEND_SETUPPRINT_DATA_COMMAND_SIZE and
                                     USBPRESET_COMMAND and their corresponding length.
                                     Added #define COLSETUP_MSG_SCREEN.
      2.31         09-02-08  NHAhmed CleanUp for multi-language support.
      2.32         09-12-08  NHAhmed Updated enum MAP_ID; Defiened a new command START_RUNCYCLE
                                     and its corresponding length.
      2.33         10-01-08  NHAhmed Modifed #define SEND_STRUCTURE_DATA_SIZE and Updated enum MAP_ID.
      2.34         11-18-08  NHAhmed Added POWER_TEST enum MAP_ID for Test Menu Problem.
      2.35         03-08-11  PDwivedi Added new micro for VGA_USBFULLALARM.
  ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/
#define SERIALLENGTH 12                  /* Number bytes in PS Serial Number */ 
#define MAXACKLENGTH 8192               /* SBC task transmit Buffer is 8 kbytes  */
#define SERIAL_MAXACKLENGTH 1024         
#define MAXACTIONFLAGS 10
#define STOPASYNCWELDDATA  0
#define STARTASYNCWELDDATA 1
#define SENDNOWOFF 0
#define SENDNOWON  1
#define PROCESSPASSWORDSCREEN 1
#define VGA_PRINTERON 0x01
#define VGA_SCREENCALIB 0x02
#define VGA_USBFULLALARM 0x04
#define MAX_VERSION_LENGTH 10
#define PMCDATACLEAR 2
#define ADDTOPMCDATA 3
#define SENDPMCDATA 4
#define VIEWPRESETPARTONE 1
#define VIEWPRESETPARTTWO 2

/* DLE,STX,FUN(2 bytes),CNT(2 bytes), CHKSUM,DLE,ETX */
#define SPCSIZE  (sizeof(WELD_DATA7_02) + 9) /* Welder Id (2 bytes) not included */ 

#define UPLOADCOMMAND_SIZE      9 /* DLE,STX,FUN(2 bytes),CNT(2 bytes),CHKSUM,DLE,ETX */
#define DOWNLOADCOMMAND_SIZE    (sizeof(PRESET_COMPRESSED) + 9)
#define DOWNLOADDUPS_SIZE       (sizeof(PRESET_COMPRESSED) + sizeof(DUPS_CURRENTPARAMSET) + DUPS_PARAMSETNAMELEN + 9)
#define RESETALARMS_SIZE        9
#define VERIFYCOMMAND_SIZE      9
#define GRAPHCOMMAND_SIZE      11
#define BYTE1SHIFT             24  /* Highest byte of 4  */
#define BYTE2SHIFT             16  /* 2nd high byte of 4 */
#define BYTE3SHIFT             8   /* 3rd high byte of 4 */
#define VEL_POINTS             3   /* # of points used per velocity calculation */
#define MSPERSEC           10000   /* ms/sec x 10 to increase resolution */

#define LANGUAGE_COUNT  8  /* Maximum number of button on the keypad screen */
#define SEND_MENU_PTRS          1000
#define SEND_BOTTOM_MENU_DATA   1001
#define PROCESS_SUBMENU         1002
#define SET_TIME                1003
#define SET_DATE                1004
#define PROCESS_CHOICE          1005
#define SEND_ALPHA_DATA         1006
#define SET_ALPHA_VALUE         1007
#define SEND_VARIABLE_DATA      1008
#define SET_VARIABLE_VALUE      1009
#define PROCESS_RADIO           1010
#define PROCESS_TOGGLE          1011
#define PROCESS_RADIOMENU       1012
#define PROCESS_RADIOLARGEMENU  1013
#define PROCESS_RADIOLARGE      1014
#define PROCESS_VGABUTTON       1015 
#define POLLING_COMMAND         1016
#define VGA_HOST_COMMAND        1000
#define WELD_GRAPH_COMMAND      1017
#define PROCESS_PASSWORD_SAVE   1018
#define PROCESS_PRESET_COMMAND  1019
#define CHECK_PASSWORD_COMMAND  1020
#define PROCESS_ALARM           1021 
#define SEND_ALARM_MENU         1022
#define SEND_WELDER_STATE       1023
#define SEND_START_WELD_DATA    1024 
#define SEND_PRINT_DATA         1025   
#define WELD_PARAM_NAME         1026
#define SEND_PRINT_PARAM        1027
#define VGAUPLOAD_PRESET        1028
#define VGADOWNLOAD_PRESET      1029
#define VGAPMC_COMMAND          1030 
#define VGASEQUENCING_COMMAND   1031
#define VGA_ERRORBEEP_COMMAND   1032
#define VGA_PRINTERROR_COMMAND  1033
#define VGA_USBPRESET_COMMAND   1034 
#define VGA_PSPRESET_COMMAND    1035 
#define VGA_SCREENSETUP_COMMAND 1036
#define VGA_HSABORT_COMMAND     1037
#define VGA_POLLING_COMMAND     1038

#define SEND_QUALITYLIMITS_DATA  137
#define SEND_STRUCTURE_DATA     1050   //to be adjusted accordingly.
#define RECEIVE_STRUCTURE_DATA  1051   //to be adjusted accordingly.
#define SEND_MIN_MAX_COMMAND    1052   //to be adjusted accordingly.
#define BOTTOMHALF_COMMAND      1053   //to be adjusted accordingly.
#define SEND_CONDN_VAR          1100   //to be adjusted accordingly.
#define WELD_DATA_COMMAND       1054
#define SEND_WELDER_STATE_CMD   1055
#define PMC_COMMAND             1056
#define PSPRESET_COMMAND        1057 
#define SEND_ALARMBIT_COMMAND   1058
#define PROCESS_ALARM_ITEM      1059 
#define SEND_SETUPPRINT_DATA    1060
#define USBPRESET_COMMAND       1061
#define VGA_RESET_ALARMS        1062
#define START_RUNCYCLE          1063

#define MENU_PTRS_COMMAND_SIZE                15
#define BOTTOM_MENU_COMMAND_SIZE              13
#define PROCESS_SUBMENU_COMMAND_SIZE          13
#define SET_TIME_COMMAND_SIZE                 15 
#define SET_DATE_COMMAND_SIZE                 16 
#define PROCESS_CHOICE_COMMAND_SIZE           14   
#define ALPHA_DATA_COMMAND_SIZE               13
#define SET_ALPHA_COMMAND_SIZE                14  
#define VARIABLE_DATA_COMMAND_SIZE            13 
#define SET_VARIABLE_COMMAND_SIZE             21 
#define PROCESS_RADIO_COMMAND_SIZE            15
#define PROCESS_TOGGLE_COMMAND_SIZE           14 
#define PROCESS_RADIOMENU_COMMAND_SIZE        13
#define PROCESS_RADIOLARGEMENU_COMMAND_SIZE   13
#define PROCESS_RADIOLARGE_COMMAND_SIZE       15
#define UPLOAD_REMOTE_CONFIG_PARMS_SIZE       31
#define ACK_REPLY_SIZE                        11 
#define WELD_GRAPH_COMMAND_SIZE               11
#define WELD_DATA_COMMAND_SIZE                11
#define PROCESS_VGABUTTON_COMMAND_SIZE        13 
#define PROCESS_PRESET_COMMAND_SIZE           14
#define POLLING_COMMAND_SIZE                  10 
#define PROCESS_ALARM_COMMAND_SIZE            13
#define SEND_ALARM_MENU_COMMAND_SIZE          9
#define SEND_WELDER_STATE_COMMAND_SIZE        9 
#define SEND_START_WELD_DATA_COMMAND_SIZE     9
#define SEND_PRINT_DATA_COMMAND_SIZE          10
#define WELD_PARAM_NAME_COMMAND_SIZE          9
#define SEND_PRINT_PARAM_COMMAND_SIZE         9
#define VGAPMC_COMMAND_SIZE                   10
#define VGASEQUENCING_COMMAND_SIZE            10
#define VGA_ERRORBEEP_COMMAND_SIZE            9
#define VGA_PRINTERROR_COMMAND_SIZE           10
#define VGA_PSPRESET_COMMAND_SIZE             11
#define VGA_SCREENSETUP_COMMAND_SIZE          9  
#define VGA_HSABORT_COMMAND_SIZE              9 
#define QUALITYLIMITS_DATA_COMMAND_SIZE       10 
#define SEND_STRUCTURE_DATA_SIZE              12
#define RECEIVE_STRUCTURE_DATA_SIZE           42 //17 + 25 for storing 30 sequencing preset
#define SEND_CONDN_VAR_SIZE                   9
#define SEND_MIN_MAX_COMMAND_SIZE             11
#define BOTTOMHALF_COMMAND_SIZE               11
#define PMC_COMMAND_SIZE                      10
#define SEND_SETUPPRINT_DATA_COMMAND_SIZE     10
#define PSPRESET_COMMAND_SIZE                 11
#define START_RUNCYCLE_COMMAND_SIZE           9

#define RECALL_PRESET_COMMAND_SIZE                 10
#define SET_CURRENT_PRESET_PARAMETERS_COMMAND_SIZE 26
#define START_WELD_DATA_COMMAND_SIZE               11
#define SET_PARAMETER_COMMAND_SIZE                 13
#define CHECKSUM_ERROR_COMMAND_SIZE                 9
#define ONBOARD_DIAGNOSTICS_COMMAND_SIZE            9
#define SET_PS_SERIALNUMBER_COMMAND_SIZE           21
#define SET_PS_MODELNUMBER_COMMAND_SIZE            14
#define SET_CONTROLLEVEL_COMMAND_SIZE              13
#define SET_ACT_SERIALNUMBER_COMMAND_SIZE          19
#define SET_ACT_MODELNUMBER_COMMAND_SIZE           12
#define RESET_PSLIFETIMECOUNTER_COMMAND_SIZE        9
#define RESET_OVERLOADCOUNTER_COMMAND_SIZE          9
#define RESET_GENALARMCOUNTER_COMMAND_SIZE          9
#define SET_ACTUATOR_CYLINDERDIAMETER_COMMAND_SIZE 13
#define SET_ACTUATOR_STROKELENGTH_COMMAND_SIZE     13
#define UPLOAD_REMOTE_CONFIG_PARMS_COMMAND_SIZE     9
#define DEFAULT_COMMAND_SIZE                        9
#define MAX_ALPHA_ITOM_COMMAND_SIZE                25
#define SBC_SW_VERSION_LENTGH                       6
#define SEND_ALARMBIT_COMMAND_SIZE                  9
#define PROCESS_ALARM_ITEM_COMMAND_SIZE            11
#define VGA_RESET_ALARMS_SIZE                       9
#define  SW_VERSION_LENTGH    6

#define ACCESS_NOT_ALLOWED 1
#define SHOW_MAIN_MENU 2
#define REFRESH_MENU 3
#define SHOW_PREV_MENU 4
#define SHOW_PASSWORD_SCREEN 5
#define SHOW_PASSWORD_ENTRY1 6
#define SHOW_PASSWORD_ENTRY2 7
#define DUPS_NOT_UPLOADED 8
#define PS_MISMATCH 9
#define DUPS_NOT_DOWNLOADED 10
#define DUPS_NOT_AVAILABLE  11
#define SHOW_WELDINGON_MESSAGE   11
#define SHOW_MSG_SCREEN          4
#define COLSETUP_MSG_SCREEN   12

#define NO_DATA_COMMAND_SIZE 9
#define ACK 0x06
#define NAK 0x15

/* Error Codes Returned to Controller from Command Parser  */

#define INVALID_SOURCE       0x00002
#define BAD_CHECKSUM         0x00004
#define MAX_ERROR            0x00008+1      /* add 1 for data follows */
#define MIN_ERROR            0x00010+1      /* add 1 for data follows */
#define INVALID_OPCODE       0x00020
#define PARAMETER_ERROR      0x00040
#define UNIMPLEMENTED_OPCODE 0x00080
#define INVALID_SYS_CONFIG   0x00200
#define HARDWARE_FAILURE     0x00800
#define INVALID_AUTH_CODE    0x02000
#define ILLEGAL_COMMAND      0x04000
#define WELDER_PROCESS_ERROR 0x08001


#define REFRESH_MENU_AED   179
#define REFRESH_MENU_AE    181
#define REFRESH_MENU_AEF2  182
#define RESULT_MENU        183
#define RESULT_MENU_AE     184
#define REFRESH_MENU_AEF1  175

#define ThreeRulePorcentageToMicrons(NewValue,SystemValue) ((NewValue * SystemValue) / 100) // New Amplitude * System100%Microns / 100% Amplitude
#define ThreeRuleMicronsToPorcentage(NewValue,SystemValue) ((NewValue * 100) / SystemValue) // New Porcentage * 100% / System100%Microns

#define ThreeRulePorcentageToWatts(NewValue,SystemValue) ((NewValue * SystemValue) / 1000) // New Paek Power * SystemPower / 1000% move decimal point
#define ThreeRuleWattsToPorcentage(NewValue,SystemValue) ((NewValue * 10) / CurrentSetup.PSWatt) // (PeakPower * 100) / PSWatt;

/* MapIDs list*/

enum MAP_ID{
   UNIT_SET =	0,
   TIME_INFO = 5,
   DATE_INFO = 6,
   PSFREQ_WATTINFO = 17,
   CALIBRATE_INFO=19,

	PSSERIAL_NUMID = 23,
	ACTSERIAL_NUMID,

	PASSWD_ENTRY = 30,
	PASSWD_SAVE =54,

	TIMEDISPLAY =65,        
	PKPWRDISPLAY,
	ENERGYDISPLAY,
	VELOCITYDISPLAYAED,
	VELOCITYDISPLAYAEF,
	FREQMINDISPLAY,
	FREQMAXDISPLAY,
	FREQSTARTDISPLAY,
	FREQENDDISPLAY,
	FREQCHGDISPLAY,
	SETAMPADISPLAY,
	SETAMPBDISPLAY,
	WELDABSDISPLAY,
	ACTPRESSDISPLAY,
	TOTALABSDISPLAY,
	WELDCOLDISPLAY,
	TOTALCOLDISPLAY,
	WELDFORCEDISPLAY,
	SETFORCEADISPLAY,
	SETFORCEBDISPLAY,
	PRESETNUMDISPLAY,
	CYCLETIMEDISPLAY,

   J3_32IN = 88,
   J3_33IN,
   J3_19IN,
   J3_17IN,
   J3_31IN,
   J3_1IN, 
   J3_8OUT,
   J3_36OUT,
   J3_22OUT,

   RESTORE_USERIO = 99,
	WELDMODE_SET = 101,

	AMPLITUDEMODE_SET = 114,
	WELDFORCEMODE_SET = 175,

	AMP_CNTL_SET = 208,
	FREQ_CNTL_SET,

   AUTO_NAME = 216,
   SAME_NAMEAS_OLD,
   SAME_NAMEAS_NEW,
   ASSIGN_NAME,
	PRST_LISTING,

	PRST_RECALL = 223,
	PRST_VERIFY,
	PRST_INFO,

	SEQUENCE_LISTING =235,
	SEQUENCE_LIST_UPDATE,

	XSCALE_SET =258,

   RESTORE_ACTUATOR = 378,
   RESTORE_BBR,
   RESTORE_PRINTING,
   RESTORE_GLOBAL,
   
   DIGITAL_TUNE_CHOICE = 382,
   DIGITAL_FREQ = 384,

   RECALL_MIN_MSG = 390,
   RECALL_MAX_MSG,
   RECALL_COLDSTART_MSG,
   SAVE_MIN_MSG,
   SAVE_MAX_MSG,
   SAVE_COLDSTART_MSG,
   RESTORE_MINMAX_MSG,
   RESTORE_COLDSTART_MSG,
   HORN_SCAN_MENU,
   HS_START,

   HORN_DOWN_MENU = 401,
   RT_DIST = 406,

   MAIN_MENU = 409,
   WELDMODE_MENU,
   GRAPH_MENU,
   RUN_MENU,
	
   UNIQUE_PRST = 416,
   SETUP_ALARM,
   COLDSTART_ALL,

   TEST_AMPLITUDE = 421,
   CALIB_SENSOR = 426,
   CALIB_ACTUATOR = 429,
   PARAMETER_NUM = 455,
   POWER_TEST = 485,
   MENU_SYNC = 519,
   AMPLITUDMICRON_SET = 527
};



/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/


/*
 -----------------------.---- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


void RemoteSerialCommandHandler(void);
void ColdStartPlus(void);  
//void SelectAutoPretrig(void);
//void SelectDistPretrig(void);
void SetBucMenuToFactoryDefault(void);


