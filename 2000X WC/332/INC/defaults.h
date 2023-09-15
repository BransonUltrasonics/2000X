/* $Header:   L:/pvcs/1000/psos332/archives/inc/defaults.h_v   2.4   18 Sep 1996 10:20:28   lmarkure  $ */
#ifndef PARAMETER_MANAGER_DEFAULTS_H
#define PARAMETER_MANAGER_DEFAULTS_H  1
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
 
/*
---------------------------- INCLUDE DESCRIPTION ------------------------------
                                                  
  Module name:parameter_manager_defaults

  Filename:  defaults.h


           Written by:  Mark Lazarewicz
                 Date:  03/19/96
             Language:  68000 Microtec "C" Compiler

--------------------------------- REVISIONS -----------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
       0           03/19/96      Mark L      Initial
       1           04/29/96      LAM         added battram check
       2           04/04/96      MAL         Support System Parameters
       3           07/25/96      MAL         Support Serial Variables  
       4           09/05/96      MAL         Support Serial Variables  
--------------------------------- DESCRIPTION -----------------------------------

 minimum limits, maximum limits and default values for parameters

--------------------------------- INCLUDE FILES ---------------------------------
*/
/* minimum limits, maximum limits and default values */
#include "baudtype.h"
#include "authrize.h"
#include "timrname.h"


/*
---------------------------------- DEFINITIONS ----------------------------------
*/
/* default values */

#define BATTRAM_WRITE 0x55
/* 
------------  PARAMETER ATTRIBUTES TABLE INITIALIZATION -------------------------
*/    
     
  /* This parameter is not used */
  parameter_attributes[0].data_type = PARAMETER_TYPE_UINT32;
  parameter_attributes[0].operator = DO_NOT_CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[0].min_limit.size_uint32 = 0;
  parameter_attributes[0].max_limit.size_uint32  = 0;
  parameter_attributes[0].default_value.size_uint32 = 0; 
  parameter_attributes[0].notification_task = NO_NOTIFICATION;

 


  /* ******************************************************************** */
  /* ******************************************************************** */
  parameter_attributes[P_USER_AUTHORIZATION].data_type = PARAMETER_TYPE_UINT8;
  parameter_attributes[P_USER_AUTHORIZATION].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_USER_AUTHORIZATION].min_limit.size_uint8 = MIN_USER_AUTHORIZATION_TYPE_LIMIT +1;
  parameter_attributes[P_USER_AUTHORIZATION].max_limit.size_uint8 = MAX_USER_AUTHORIZATION_TYPE_LIMIT -1;
  parameter_attributes[P_USER_AUTHORIZATION].default_value.size_uint8 = USER_AUTHORIZATION_REQUIRED; 
  parameter_attributes[P_USER_AUTHORIZATION].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_USER_PASSWORD].data_type = PARAMETER_TYPE_STRING;
  parameter_attributes[P_USER_PASSWORD].operator = DO_NOT_CHECK_PARAMETER_RANGE + WRITE_NVM;
  /* secret default password - do not tell anyone !!*/ 
  parameter_attributes[P_USER_PASSWORD].default_value.size_string[0] = '6';
  parameter_attributes[P_USER_PASSWORD].default_value.size_string[1] = '0';
  parameter_attributes[P_USER_PASSWORD].default_value.size_string[2] = '0';
  parameter_attributes[P_USER_PASSWORD].default_value.size_string[3] = '0';
  parameter_attributes[P_USER_PASSWORD].default_value.size_string[4] = NULL;
  parameter_attributes[P_USER_PASSWORD].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_FPSP_BAUD_RATE].data_type = PARAMETER_TYPE_UINT8;
  parameter_attributes[P_FPSP_BAUD_RATE].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_FPSP_BAUD_RATE].min_limit.size_uint8 = MIN_BAUD_RATE_TYPE_LIMIT + 1;
  parameter_attributes[P_FPSP_BAUD_RATE].max_limit.size_uint8 = MAX_BAUD_RATE_TYPE_LIMIT - 1;
  parameter_attributes[P_FPSP_BAUD_RATE].notification_task = FPPM_SOURCE_TASK;

  /* ******************************************************************** */
  parameter_attributes[P_PSTN_INACTIVITY_TIMER].data_type = PARAMETER_TYPE_UINT32;
  parameter_attributes[P_PSTN_INACTIVITY_TIMER].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_PSTN_INACTIVITY_TIMER].min_limit.size_uint32 = 60L;
  parameter_attributes[P_PSTN_INACTIVITY_TIMER].max_limit.size_uint32 = 600L;
  parameter_attributes[P_PSTN_INACTIVITY_TIMER].default_value.size_uint32 = 300L; 
  parameter_attributes[P_PSTN_INACTIVITY_TIMER].notification_task = NO_NOTIFICATION;


  /* ******************************************************************** */
  parameter_attributes[P_ACTIVE_APPL_SW_VERSION_ID].data_type =  PARAMETER_TYPE_STRING;
  parameter_attributes[P_ACTIVE_APPL_SW_VERSION_ID].operator = DO_NOT_CHECK_PARAMETER_RANGE;
  parameter_attributes[P_ACTIVE_APPL_SW_VERSION_ID].min_limit.size_string[0] = NULL;
  parameter_attributes[P_ACTIVE_APPL_SW_VERSION_ID].max_limit.size_string[0] = NULL;
  parameter_attributes[P_ACTIVE_APPL_SW_VERSION_ID].default_value.size_string[0] = NULL ;
  parameter_attributes[P_ACTIVE_APPL_SW_VERSION_ID].notification_task = NO_NOTIFICATION;
  
  /********************************************************************** */
  parameter_attributes[P_REAL_TIME_CLOCK_YEAR].data_type = PARAMETER_TYPE_UINT16;
  parameter_attributes[P_REAL_TIME_CLOCK_YEAR].operator = CHECK_PARAMETER_RANGE;
  parameter_attributes[P_REAL_TIME_CLOCK_YEAR].min_limit.size_uint16 = 1995;
  parameter_attributes[P_REAL_TIME_CLOCK_YEAR].max_limit.size_uint16  = 2092;
  parameter_attributes[P_REAL_TIME_CLOCK_YEAR].default_value.size_uint16 = 1995; 
  parameter_attributes[P_REAL_TIME_CLOCK_YEAR].notification_task = NO_NOTIFICATION;

  /********************************************************************** */
  parameter_attributes[P_REAL_TIME_CLOCK_MONTH].data_type = PARAMETER_TYPE_UINT8;
  parameter_attributes[P_REAL_TIME_CLOCK_MONTH].operator = CHECK_PARAMETER_RANGE;
  parameter_attributes[P_REAL_TIME_CLOCK_MONTH].min_limit.size_uint8 = 1;
  parameter_attributes[P_REAL_TIME_CLOCK_MONTH].max_limit.size_uint8  = 12;
  parameter_attributes[P_REAL_TIME_CLOCK_MONTH].default_value.size_uint8 = 4; 
  parameter_attributes[P_REAL_TIME_CLOCK_MONTH].notification_task = NO_NOTIFICATION;

  /********************************************************************** */
  parameter_attributes[P_REAL_TIME_CLOCK_DAY].data_type = PARAMETER_TYPE_UINT8;
  parameter_attributes[P_REAL_TIME_CLOCK_DAY].operator = CHECK_PARAMETER_RANGE;
  parameter_attributes[P_REAL_TIME_CLOCK_DAY].min_limit.size_uint8 = 1;
  parameter_attributes[P_REAL_TIME_CLOCK_DAY].max_limit.size_uint8  = 31;
  parameter_attributes[P_REAL_TIME_CLOCK_DAY].default_value.size_uint8 = 1; 
  parameter_attributes[P_REAL_TIME_CLOCK_DAY].notification_task = NO_NOTIFICATION;

  /********************************************************************** */
  parameter_attributes[P_REAL_TIME_CLOCK_HOUR].data_type = PARAMETER_TYPE_UINT16;
  parameter_attributes[P_REAL_TIME_CLOCK_HOUR].operator = CHECK_PARAMETER_RANGE;
  parameter_attributes[P_REAL_TIME_CLOCK_HOUR].min_limit.size_uint16 = 1;
  parameter_attributes[P_REAL_TIME_CLOCK_HOUR].max_limit.size_uint16  = 24;
  parameter_attributes[P_REAL_TIME_CLOCK_HOUR].default_value.size_uint16 = 12; 
  parameter_attributes[P_REAL_TIME_CLOCK_HOUR].notification_task = NO_NOTIFICATION;

  /********************************************************************** */
  parameter_attributes[P_REAL_TIME_CLOCK_MINUTE].data_type = PARAMETER_TYPE_UINT8;
  parameter_attributes[P_REAL_TIME_CLOCK_MINUTE].operator = CHECK_PARAMETER_RANGE;
  parameter_attributes[P_REAL_TIME_CLOCK_MINUTE].min_limit.size_uint8 = 0;
  parameter_attributes[P_REAL_TIME_CLOCK_MINUTE].max_limit.size_uint8  = 59;
  parameter_attributes[P_REAL_TIME_CLOCK_MINUTE].default_value.size_uint8 = 15; 
  parameter_attributes[P_REAL_TIME_CLOCK_MINUTE].notification_task = NO_NOTIFICATION;

  /********************************************************************** */
  parameter_attributes[P_REAL_TIME_CLOCK_SECOND].data_type = PARAMETER_TYPE_UINT8;
  parameter_attributes[P_REAL_TIME_CLOCK_SECOND].operator = CHECK_PARAMETER_RANGE;
  parameter_attributes[P_REAL_TIME_CLOCK_SECOND].min_limit.size_uint8 = 0;
  parameter_attributes[P_REAL_TIME_CLOCK_SECOND].max_limit.size_uint8  = 59;
  parameter_attributes[P_REAL_TIME_CLOCK_SECOND].default_value.size_uint8 = 30; 
  parameter_attributes[P_REAL_TIME_CLOCK_SECOND].notification_task = NO_NOTIFICATION;


  /* ******************************************************************** */
  parameter_attributes[P_BATTRAM_CHECK].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_BATTRAM_CHECK].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_BATTRAM_CHECK].min_limit.size_uint16 = 0;
  parameter_attributes[P_BATTRAM_CHECK].max_limit.size_uint16  = 0xFFFF;
  parameter_attributes[P_BATTRAM_CHECK].default_value.size_uint16 = BATTRAM_WRITE; 
  parameter_attributes[P_BATTRAM_CHECK].notification_task = NO_NOTIFICATION;


  /* ******************************************************************** */
  parameter_attributes[P_ACT_CLR_DISTANCE].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_ACT_CLR_DISTANCE].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_ACT_CLR_DISTANCE].min_limit.size_uint8 = 0;
  parameter_attributes[P_ACT_CLR_DISTANCE].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_ACT_CLR_DISTANCE].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_ACT_CLR_DISTANCE].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_ADVANCED_COUNTERS].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_ADVANCED_COUNTERS].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_ADVANCED_COUNTERS].min_limit.size_uint8 = 0;
  parameter_attributes[P_ADVANCED_COUNTERS].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_ADVANCED_COUNTERS].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_ADVANCED_COUNTERS].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_AMPLITUDE_CONTROL].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_AMPLITUDE_CONTROL].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_AMPLITUDE_CONTROL].min_limit.size_uint8 = 0;
  parameter_attributes[P_AMPLITUDE_CONTROL].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_AMPLITUDE_CONTROL].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_AMPLITUDE_CONTROL].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_BEEPER_ALARM].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_BEEPER_ALARM].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_BEEPER_ALARM].min_limit.size_uint8 = 0;
  parameter_attributes[P_BEEPER_ALARM].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_BEEPER_ALARM].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_BEEPER_ALARM].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_BEEPER_TRIGGER].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_BEEPER_TRIGGER].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_BEEPER_TRIGGER].min_limit.size_uint8 = 0;
  parameter_attributes[P_BEEPER_TRIGGER].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_BEEPER_TRIGGER].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_BEEPER_TRIGGER].notification_task = NO_NOTIFICATION;


 /* ******************************************************************** */
  parameter_attributes[P_CUSTOM_ACT_LOGIC].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_CUSTOM_ACT_LOGIC].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_CUSTOM_ACT_LOGIC].min_limit.size_uint8 = 0;
  parameter_attributes[P_CUSTOM_ACT_LOGIC].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_CUSTOM_ACT_LOGIC].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_CUSTOM_ACT_LOGIC].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_EXT_SWITCH_LOGIC].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_EXT_SWITCH_LOGIC].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_EXT_SWITCH_LOGIC].min_limit.size_uint8 = 0;
  parameter_attributes[P_EXT_SWITCH_LOGIC].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_EXT_SWITCH_LOGIC].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_EXT_SWITCH_LOGIC].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_FREQUENCY_CONTROL].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_FREQUENCY_CONTROL].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_FREQUENCY_CONTROL].min_limit.size_uint8 = 0;
  parameter_attributes[P_FREQUENCY_CONTROL].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_FREQUENCY_CONTROL].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_FREQUENCY_CONTROL].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_HAND_HELD_SYSTEM].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_HAND_HELD_SYSTEM].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_HAND_HELD_SYSTEM].min_limit.size_uint8 = 0;
  parameter_attributes[P_HAND_HELD_SYSTEM].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_HAND_HELD_SYSTEM].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_HAND_HELD_SYSTEM].notification_task = NO_NOTIFICATION;


  /* ******************************************************************** */
  parameter_attributes[P_MISSING_OUTPUT].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_MISSING_OUTPUT].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_MISSING_OUTPUT].min_limit.size_uint8 = 0;
  parameter_attributes[P_MISSING_OUTPUT].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_MISSING_OUTPUT].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_MISSING_OUTPUT].notification_task = NO_NOTIFICATION;


  /* ******************************************************************** */
  parameter_attributes[P_POSITION_SWITCH].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_POSITION_SWITCH].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_POSITION_SWITCH].min_limit.size_uint8 = 0;
  parameter_attributes[P_POSITION_SWITCH].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_POSITION_SWITCH].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_POSITION_SWITCH].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_POSITION_SWITCH1].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_POSITION_SWITCH1].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_POSITION_SWITCH1].min_limit.size_uint8 = 0;
  parameter_attributes[P_POSITION_SWITCH1].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_POSITION_SWITCH1].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_POSITION_SWITCH1].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_POSITION_SWITCH2].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_POSITION_SWITCH2].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_POSITION_SWITCH2].min_limit.size_uint8 = 0;
  parameter_attributes[P_POSITION_SWITCH2].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_POSITION_SWITCH2].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_POSITION_SWITCH2].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_POSITION_SWITCH3].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_POSITION_SWITCH3].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_POSITION_SWITCH3].min_limit.size_uint8 = 0;
  parameter_attributes[P_POSITION_SWITCH3].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_POSITION_SWITCH3].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_POSITION_SWITCH3].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_SEQUENCING].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_SEQUENCING].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_SEQUENCING].min_limit.size_uint8 = 0;
  parameter_attributes[P_SEQUENCING].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_SEQUENCING].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_SEQUENCING].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_TEST_TIMES1].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_TEST_TIMES1].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_TEST_TIMES1].min_limit.size_uint8 = 0;
  parameter_attributes[P_TEST_TIMES1].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_TEST_TIMES1].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_TEST_TIMES1].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_TEST_TIMES2].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_TEST_TIMES2].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_TEST_TIMES2].min_limit.size_uint8 = 0;
  parameter_attributes[P_TEST_TIMES2].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_TEST_TIMES2].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_TEST_TIMES2].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_TEST_TIMES3].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_TEST_TIMES3].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_TEST_TIMES3].min_limit.size_uint8 = 0;
  parameter_attributes[P_TEST_TIMES3].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_TEST_TIMES3].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_TEST_TIMES3].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_UNITS].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_UNITS].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_UNITS].min_limit.size_uint8 = 0;
  parameter_attributes[P_UNITS].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_UNITS].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_UNITS].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_WELD_TIMES1].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_WELD_TIMES1].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_WELD_TIMES1].min_limit.size_uint8 = 0;
  parameter_attributes[P_WELD_TIMES1].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_WELD_TIMES1].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_WELD_TIMES1].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_WELD_TIMES2].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_WELD_TIMES2].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_WELD_TIMES2].min_limit.size_uint8 = 0;
  parameter_attributes[P_WELD_TIMES2].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_WELD_TIMES2].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_WELD_TIMES2].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_WELD_TIMES3].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_WELD_TIMES3].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_WELD_TIMES3].min_limit.size_uint8 = 0;
  parameter_attributes[P_WELD_TIMES3].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_WELD_TIMES3].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_WELD_TIMES3].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_ACTUATOR].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_ACTUATOR].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_ACTUATOR].min_limit.size_uint8 = 0;
  parameter_attributes[P_ACTUATOR].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_ACTUATOR].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_ACTUATOR].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_ADJUST_WHILE_RUN].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_ADJUST_WHILE_RUN].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_ADJUST_WHILE_RUN].min_limit.size_uint8 = 0;
  parameter_attributes[P_ADJUST_WHILE_RUN].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_ADJUST_WHILE_RUN].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_ADJUST_WHILE_RUN].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_BUAD_4800].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_BUAD_4800].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_BUAD_4800].min_limit.size_uint8 = 0;
  parameter_attributes[P_BUAD_4800].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_BUAD_4800].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_BUAD_4800].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_BAUD_9600].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_BAUD_9600].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_BAUD_9600].min_limit.size_uint8 = 0;
  parameter_attributes[P_BAUD_9600].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_BAUD_9600].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_BAUD_9600].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_BAUD_19200].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_BAUD_19200].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_BAUD_19200].min_limit.size_uint8 = 0;
  parameter_attributes[P_BAUD_19200].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_BAUD_19200].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_BAUD_19200].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_BEEPER_ERROR].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_BEEPER_ERROR].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_BEEPER_ERROR].min_limit.size_uint8 = 0;
  parameter_attributes[P_BEEPER_ERROR].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_BEEPER_ERROR].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_BEEPER_ERROR].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_CYLINDER].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_CYLINDER].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_CYLINDER].min_limit.size_uint8 = 0;
  parameter_attributes[P_CYLINDER].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_CYLINDER].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_CYLINDER].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_ECHO].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_ECHO].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_ECHO].min_limit.size_uint8 = 0;
  parameter_attributes[P_ECHO].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_ECHO].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_ECHO].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_FEATURES].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_FEATURES].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_FEATURES].min_limit.size_uint8 = 0;
  parameter_attributes[P_FEATURES].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_FEATURES].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_FEATURES].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_FORM_FEED].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_FORM_FEED].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_FORM_FEED].min_limit.size_uint8 = 0;
  parameter_attributes[P_FORM_FEED].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_FORM_FEED].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_FORM_FEED].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_LANG_A].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_LANG_A].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_LANG_A].min_limit.size_uint8 = 0;
  parameter_attributes[P_LANG_A].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_LANG_A].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_LANG_A].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_LANG_A].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_LANG_A].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_LANG_A].min_limit.size_uint8 = 0;
  parameter_attributes[P_LANG_A].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_LANG_A].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_LANG_A].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_LANG_B].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_LANG_B].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_LANG_B].min_limit.size_uint8 = 0;
  parameter_attributes[P_LANG_B].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_LANG_B].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_LANG_B].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_LANG_C].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_LANG_C].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_LANG_C].min_limit.size_uint8 = 0;
  parameter_attributes[P_LANG_C].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_LANG_C].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_LANG_C].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_LINES_PER_PAGE].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_LINES_PER_PAGE].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_LINES_PER_PAGE].min_limit.size_uint8 = 0;
  parameter_attributes[P_LINES_PER_PAGE].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_LINES_PER_PAGE].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_LINES_PER_PAGE].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_PASSWORD].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_PASSWORD].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_PASSWORD].min_limit.size_uint8 = 0;
  parameter_attributes[P_PASSWORD].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_PASSWORD].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_PASSWORD].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_PASSWORD_ID].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_PASSWORD_ID].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_PASSWORD_ID].min_limit.size_uint8 = 0;
  parameter_attributes[P_PASSWORD_ID].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_PASSWORD_ID].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_PASSWORD_ID].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_PRINTER_ENABLED].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_PRINTER_ENABLED].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_PRINTER_ENABLED].min_limit.size_uint8 = 0;
  parameter_attributes[P_PRINTER_ENABLED].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_PRINTER_ENABLED].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_PRINTER_ENABLED].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_PRINTER_PANASONIC].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_PRINTER_PANASONIC].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_PRINTER_PANASONIC].min_limit.size_uint8 = 0;
  parameter_attributes[P_PRINTER_PANASONIC].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_PRINTER_PANASONIC].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_PRINTER_PANASONIC].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_PRINTER_EPSON].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_PRINTER_EPSON].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_PRINTER_EPSON].min_limit.size_uint8 = 0;
  parameter_attributes[P_PRINTER_EPSON].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_PRINTER_EPSON].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_PRINTER_EPSON].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_PRINTER_PROPRINTER].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_PRINTER_PROPRINTER].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_PRINTER_PROPRINTER].min_limit.size_uint8 = 0;
  parameter_attributes[P_PRINTER_PROPRINTER].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_PRINTER_PROPRINTER].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_PRINTER_PROPRINTER].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_PS_FREQUENCY].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_PS_FREQUENCY].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_PS_FREQUENCY].min_limit.size_uint8 = 0;
  parameter_attributes[P_PS_FREQUENCY].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_PS_FREQUENCY].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_PS_FREQUENCY].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_PS_WATT].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_PS_WATT].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_PS_WATT].min_limit.size_uint8 = 0;
  parameter_attributes[P_PS_WATT].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_PS_WATT].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_PS_WATT].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_SERIAL_ENABLED].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_SERIAL_ENABLED].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_SERIAL_ENABLED].min_limit.size_uint8 = 0;
  parameter_attributes[P_SERIAL_ENABLED].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_SERIAL_ENABLED].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_SERIAL_ENABLED].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_SERIAL_P_FLAG].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_SERIAL_P_FLAG].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_SERIAL_P_FLAG].min_limit.size_uint8 = 0;
  parameter_attributes[P_SERIAL_P_FLAG].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_SERIAL_P_FLAG].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_SERIAL_P_FLAG].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_SCROLL_DISPLAY].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_SCROLL_DISPLAY].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_SCROLL_DISPLAY].min_limit.size_uint8 = 0;
  parameter_attributes[P_SCROLL_DISPLAY].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_SCROLL_DISPLAY].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_SCROLL_DISPLAY].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_SW_HANDSHAKE].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_SW_HANDSHAKE].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_SW_HANDSHAKE].min_limit.size_uint8 = 0;
  parameter_attributes[P_SW_HANDSHAKE].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_SW_HANDSHAKE].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_SW_HANDSHAKE].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_TEST_DOWN_SPEED1].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_TEST_DOWN_SPEED1].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_TEST_DOWN_SPEED1].min_limit.size_uint8 = 0;
  parameter_attributes[P_TEST_DOWN_SPEED1].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_TEST_DOWN_SPEED1].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_TEST_DOWN_SPEED1].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_TEST_DOWN_SPEED2].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_TEST_DOWN_SPEED2].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_TEST_DOWN_SPEED2].min_limit.size_uint8 = 0;
  parameter_attributes[P_TEST_DOWN_SPEED2].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_TEST_DOWN_SPEED2].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_TEST_DOWN_SPEED2].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_TEST_DOWN_SPEED3].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_TEST_DOWN_SPEED3].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_TEST_DOWN_SPEED3].min_limit.size_uint8 = 0;
  parameter_attributes[P_TEST_DOWN_SPEED3].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_TEST_DOWN_SPEED3].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_TEST_DOWN_SPEED3].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_VERIFY_SETUP].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_VERIFY_SETUP].operator = CHECK_PARAMETER_RANGE + WRITE_NVM;
  parameter_attributes[P_VERIFY_SETUP].min_limit.size_uint8 = 0;
  parameter_attributes[P_VERIFY_SETUP].max_limit.size_uint8  = 0xFF;
  parameter_attributes[P_VERIFY_SETUP].default_value.size_uint8 = BATTRAM_WRITE; 
  parameter_attributes[P_VERIFY_SETUP].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_WELD_TIME].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_WELD_TIME].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_WELD_TIME].min_limit.size_uint16 = 10;
  parameter_attributes[P_WELD_TIME].max_limit.size_uint16  = 0x8000;
  parameter_attributes[P_WELD_TIME].default_value.size_uint16 = 5000; 
  parameter_attributes[P_WELD_TIME].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_WELD_ENERGY].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_WELD_ENERGY].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_WELD_ENERGY].min_limit.size_uint16 = 5;
  parameter_attributes[P_WELD_ENERGY].max_limit.size_uint16  = 0xffff;
  parameter_attributes[P_WELD_ENERGY].default_value.size_uint16 = 5; 
  parameter_attributes[P_WELD_ENERGY].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_PEAK_POWER].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_PEAK_POWER].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_PEAK_POWER].min_limit.size_uint16 = 1;
  parameter_attributes[P_PEAK_POWER].max_limit.size_uint16  = 100;
  parameter_attributes[P_PEAK_POWER].default_value.size_uint16 = 1; 
  parameter_attributes[P_PEAK_POWER].notification_task = NO_NOTIFICATION;

 /* ******************************************************************** */
  parameter_attributes[P_COLLAPSE_DISTANCE].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_COLLAPSE_DISTANCE].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_COLLAPSE_DISTANCE].min_limit.size_uint16 = 1;
  parameter_attributes[P_COLLAPSE_DISTANCE].max_limit.size_uint16  = 10000;
  parameter_attributes[P_COLLAPSE_DISTANCE].default_value.size_uint16 = 1; 
  parameter_attributes[P_COLLAPSE_DISTANCE].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_HOLD_TIME].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_HOLD_TIME].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_HOLD_TIME].min_limit.size_uint16 = 10;
  parameter_attributes[P_HOLD_TIME].max_limit.size_uint16  = 30000;
  parameter_attributes[P_HOLD_TIME].default_value.size_uint16 = 10; 
  parameter_attributes[P_HOLD_TIME].notification_task = NO_NOTIFICATION;

 /* ******************************************************************** */
  parameter_attributes[P_HOLD_FORCE].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_HOLD_FORCE].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_HOLD_FORCE].min_limit.size_uint16 = 5;
  parameter_attributes[P_HOLD_FORCE].max_limit.size_uint16  = 1600;
  parameter_attributes[P_HOLD_FORCE].default_value.size_uint16 = 5; 
  parameter_attributes[P_HOLD_FORCE].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_MAX_TIMEOUT].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_MAX_TIMEOUT].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_MAX_TIMEOUT].min_limit.size_uint16 = 10;
  parameter_attributes[P_MAX_TIMEOUT].max_limit.size_uint16  = 30000;
  parameter_attributes[P_MAX_TIMEOUT].default_value.size_uint16 = 10; 
  parameter_attributes[P_MAX_TIMEOUT].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_TRIGGER_FORCE].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_TRIGGER_FORCE].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_TRIGGER_FORCE].min_limit.size_uint16 = 5;
  parameter_attributes[P_TRIGGER_FORCE].max_limit.size_uint16  = 1600;
  parameter_attributes[P_TRIGGER_FORCE].default_value.size_uint16 = 150; 
  parameter_attributes[P_TRIGGER_FORCE].notification_task = NO_NOTIFICATION;

  /* ******************************************************************** */
  parameter_attributes[P_WELD_FORCE].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_WELD_FORCE].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_WELD_FORCE].min_limit.size_uint16 = 5;
  parameter_attributes[P_WELD_FORCE].max_limit.size_uint16  = 1600;
  parameter_attributes[P_WELD_FORCE].default_value.size_uint16 = 5; 
  parameter_attributes[P_WELD_FORCE].notification_task = NO_NOTIFICATION;
  
  parameter_attributes[P_RESET_REQUIRED].data_type =  PARAMETER_TYPE_UINT8;
  parameter_attributes[P_RESET_REQUIRED].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_RESET_REQUIRED].min_limit.size_uint16 = 0;
  parameter_attributes[P_RESET_REQUIRED].max_limit.size_uint16  = 1;
  parameter_attributes[P_RESET_REQUIRED].default_value.size_uint16 =0; 
  parameter_attributes[P_RESET_REQUIRED].notification_task = NO_NOTIFICATION;
  
  parameter_attributes[P_ABSOLUTE_DISTANCE].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_ABSOLUTE_DISTANCE].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_ABSOLUTE_DISTANCE].min_limit.size_uint16 = 1000;
  parameter_attributes[P_ABSOLUTE_DISTANCE].max_limit.size_uint16  = 1600;
  parameter_attributes[P_ABSOLUTE_DISTANCE].default_value.size_uint16 = 5; 
  parameter_attributes[P_ABSOLUTE_DISTANCE].notification_task = NO_NOTIFICATION;

  parameter_attributes[ P_TIME_MLS].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[ P_TIME_MLS].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[ P_TIME_MLS].min_limit.size_uint16 = 10;
  parameter_attributes[ P_TIME_MLS].max_limit.size_uint16  = 0x30000;
  parameter_attributes[ P_TIME_MLS].default_value.size_uint16 = 10; 
  parameter_attributes[ P_TIME_MLS].notification_task = NO_NOTIFICATION;

  parameter_attributes[ P_TIME_PLS].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[ P_TIME_PLS].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[ P_TIME_PLS].min_limit.size_uint16 = 10;
  parameter_attributes[ P_TIME_PLS].max_limit.size_uint16  = 0x30000;
  parameter_attributes[ P_TIME_PLS].default_value.size_uint16 = 10; 
  parameter_attributes[ P_TIME_PLS].notification_task = NO_NOTIFICATION;

  parameter_attributes[P_ENERGY_MLS].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_ENERGY_MLS].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_ENERGY_MLS].min_limit.size_uint16 = 10;
  parameter_attributes[P_ENERGY_MLS].max_limit.size_uint16  = 0xFFFF;
  parameter_attributes[P_ENERGY_MLS].default_value.size_uint16 = 10; 
  parameter_attributes[P_ENERGY_MLS].notification_task = NO_NOTIFICATION;

  parameter_attributes[P_ENERGY_PLS].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_ENERGY_PLS].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_ENERGY_PLS].min_limit.size_uint16 = 10;
  parameter_attributes[P_ENERGY_PLS].max_limit.size_uint16  = 0xFFFF;
  parameter_attributes[P_ENERGY_PLS].default_value.size_uint16 = 10; 
  parameter_attributes[P_ENERGY_PLS].notification_task = NO_NOTIFICATION;

  parameter_attributes[P_PRETRIGGER_ULS].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_PRETRIGGER_ULS].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_PRETRIGGER_ULS].min_limit.size_uint16 = 5;
  parameter_attributes[P_PRETRIGGER_ULS].max_limit.size_uint16  = 1600;
  parameter_attributes[P_PRETRIGGER_ULS].default_value.size_uint16 = 5; 
  parameter_attributes[P_PRETRIGGER_ULS].notification_task = NO_NOTIFICATION;

  parameter_attributes[P_ENERGY_MLR].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_ENERGY_MLR].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_ENERGY_MLR].min_limit.size_uint16 = 10;
  parameter_attributes[P_ENERGY_MLR].max_limit.size_uint16  = 0xFFFF;
  parameter_attributes[P_ENERGY_MLR].default_value.size_uint16 = 10; 
  parameter_attributes[P_ENERGY_MLR].notification_task = NO_NOTIFICATION;

  parameter_attributes[P_ENERGY_PLR].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[P_ENERGY_PLR].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[P_ENERGY_PLR].min_limit.size_uint16 = 10;
  parameter_attributes[P_ENERGY_PLR].max_limit.size_uint16  = 0xffff;
  parameter_attributes[P_ENERGY_PLR].default_value.size_uint16 = 10; 
  parameter_attributes[P_ENERGY_PLR].notification_task = NO_NOTIFICATION;

  parameter_attributes[ P_TIME_MLR].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[ P_TIME_MLR].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[ P_TIME_MLR].min_limit.size_uint16 = 10;
  parameter_attributes[ P_TIME_MLR].max_limit.size_uint16  = 30000;
  parameter_attributes[ P_TIME_MLR].default_value.size_uint16 = 10; 
  parameter_attributes[ P_TIME_MLR].notification_task = NO_NOTIFICATION;

  parameter_attributes[ P_TIME_PLR].data_type =  PARAMETER_TYPE_UINT16;
  parameter_attributes[ P_TIME_PLR].operator = CHECK_PARAMETER_RANGE + WRITE_NVM + APPL_AND_USER_WRITE_ALLOWED;
  parameter_attributes[ P_TIME_PLR].min_limit.size_uint16 = 10;
  parameter_attributes[ P_TIME_PLR].max_limit.size_uint16  = 30000;
  parameter_attributes[ P_TIME_PLR].default_value.size_uint16 = 10; 
  parameter_attributes[ P_TIME_PLR].notification_task = NO_NOTIFICATION;

#endif /* PARAMETER_MANAGER_DEFAULTS_H */
