/* $Header:   L:/pvcs/1000/psos332/archives/inc/parametr.h_v   2.3   18 Sep 1996 10:11:42   lmarkure  $ */
#ifndef PARMID_TYPE_H
#define PARMID_TYPE_H
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

   Module name: PARAMETER_ID_TYPE

   Filename: parametr.h 


            Written by: Mark Lazarewicz
                  Date: 03/14/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            03/14/96      Mark L      Initial Version
       1            04/02/96      Mark L      Add USER_PASSWORD,RTCLOCK parameters
       2            04/29/96      LAM         Add BATTRAM CHECK parameters
       3            04/03/96      MAL         ADD System Data parameters
       4            07/24/96      MAL         Support Serial port variables

 ------------------------------- DESCRIPTION -----------------------------------
  
 ------------------------------ INCLUDE FILES ----------------------------------
*/
/*
 --------------------------------- DEFINES -------------------------------------
*/
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

#define MAX_PARAMETER_STRING_SIZE 8
#define MAX_PARAMETER_VALUE_SIZE  MAX_PARAMETER_STRING_SIZE


typedef packed enum
   {           
   PARAMETER_ID_START          = 0u,   
   P_USER_AUTHORIZATION        = 1,  
   P_FPSP_BAUD_RATE            = 2,
   P_USER_PASSWORD             = 3,
   P_ACTIVE_APPL_SW_VERSION_ID = 4,

   P_REAL_TIME_CLOCK_YEAR      = 11,
   P_REAL_TIME_CLOCK_MONTH     = 12,
   P_REAL_TIME_CLOCK_DAY       = 13,
   P_REAL_TIME_CLOCK_HOUR      = 14,
   P_REAL_TIME_CLOCK_MINUTE    = 15,
   P_REAL_TIME_CLOCK_SECOND    = 16,
   P_BATTRAM_CHECK             = 17,
   /* -.-..--.-..--.-..--.-..--.-..--.-..--.-..--.-..--.-..--.-..--.-..--.-..- */
   /* ALWAYS INSERT THE HIGHEST NUMBERED ID PRIOR TO MAX_NUM_PARAMETER_IDS */    
   /* -.-..--.-..--.-..--.-..--.-..--.-..--.-..--.-..--.-..--.-..--.-..--.-..- */
   P_ACT_CLR_DISTANCE,    
   P_ADVANCED_COUNTERS,   
   P_AMPLITUDE_CONTROL,     
   P_BEEPER_ALARM,      
   P_BEEPER_TRIGGER,   
   P_CUSTOM_ACT_LOGIC,                      
   P_EXT_SWITCH_LOGIC,                         
   P_FREQUENCY_CONTROL,       
   P_HAND_HELD_SYSTEM,                         
   P_MISSING_OUTPUT,     
   P_POSITION_SWITCH,             
   P_POSITION_SWITCH1,            
   P_POSITION_SWITCH2,            
   P_POSITION_SWITCH3,            
   P_SEQUENCING,
   P_TEST_TIMES1,        
   P_TEST_TIMES2,        
   P_TEST_TIMES3,        
   P_UNITS,             
   P_WELD_TIMES1,        
   P_WELD_TIMES2,        
   P_WELD_TIMES3,        
   P_ACTUATOR,
   P_ADJUST_WHILE_RUN,    
   P_BUAD_4800,          
   P_BAUD_9600,          
   P_BAUD_19200,        
   P_BEEPER_ERROR,  
   P_CYLINDER,
   P_ECHO,              
   P_FEATURES,          
   P_FORM_FEED,          
   P_LANG_A,          
   P_LANG_B,             
   P_LANG_C,           
   P_LINES_PER_PAGE,     
   P_PASSWORD,          
   P_PASSWORD_ID,       
   P_PRINTER_ENABLED,   
   P_PRINTER_PANASONIC,  
   P_PRINTER_EPSON,      
   P_PRINTER_PROPRINTER, 
   P_PS_FREQUENCY,
   P_PS_WATT,
   P_SERIAL_ENABLED,     
   P_SERIAL_P_FLAG,
   P_SCROLL_DISPLAY,
   P_SW_HANDSHAKE,       
   P_TEST_DOWN_SPEED1,       
   P_TEST_DOWN_SPEED2,       
   P_TEST_DOWN_SPEED3,      
   P_VERIFY_SETUP,  
   P_WELD_TIME=70,
   P_WELD_ENERGY=71,
   P_PEAK_POWER=72,
   P_COLLAPSE_DISTANCE=73,
   P_HOLD_TIME=74,
   P_HOLD_FORCE=75,
   P_MAX_TIMEOUT=76,
   P_TRIGGER_FORCE=77,
   P_WELD_FORCE=78,
   P_RESET_REQUIRED=79,
   P_ABSOLUTE_DISTANCE=80,
   P_TIME_MLS=81,
   P_TIME_PLS=82,
   P_ENERGY_MLS=83,
   P_ENERGY_PLS=84,
   P_PRETRIGGER_ULS=85,
   P_ENERGY_MLR=86,
   P_ENERGY_PLR=87,
   P_TIME_MLR=88,
   P_TIME_PLR=89,
   MAX_NUMBER_PARAMETER_IDS    = 90,
   PARAMETER_ID_SIZER          = 65534  /* THIS MUST BE THE LAST ENUMERATION */
   } PARAMETER_ID_TYPE;

#endif /* PARAMETER_ID_TYPE_H */
