/* $Header:   K:\APPS\PVCS Pro\332new\INC\ALARMSDB.H_V   2.3   May 05 1999 13:40:40   lmarkure  $ */
#ifndef ALARM_DATABASE_MANAGER_H 
#define ALARM_DATABASE_MANAGER_H
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

   Module name: ALARM_DATABASE_MANAGER

   Filename:  alarmsdb.h


            Written by: Mark Lazarewicz
                  Date: 03/24/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author           Description
   ==========      ========      ===========      ==============
      0            03/24/96      Mark L           Initial
 	  2.2		   04/19/99		 OFI			  Changed to DIAB
	  2.3          05/04/99      LAM              fixed packed for DIAB

 ------------------------------- DESCRIPTION -----------------------------------



 ------------------------------ INCLUDE FILES ----------------------------------
*/
  
#include "managerr.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

   #define ERROR_STRING_SIZE      10           /* Max size of error string name */  
   #define MAX_NUMBER_OF_ALARMS   22           /* Max number of alarms to be sent to the HSC */
   #define VALID_ERROR_CODE       E_SWARE + 1  /* Dummy variable passed for READ_ALL_ACTUAL_ALRM*/
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/  

  typedef UINT8            NUMBER_OF_ALARMS_TYPE;   /* Defines the number of alarms to be reported */
  typedef UINT16           FORWARD_POWER_LEVEL_TYPE;
  typedef UINT16           REFLECTED_POWER_LEVEL_TYPE;
  typedef ERROR_CODE_TYPE  ALL_ACTIVE_ALARMS_TYPE[MAX_NUMBER_OF_ALARMS]; /* array of active alarms*/

   typedef __packed__ struct
   {
   ALL_ACTIVE_ALARMS_TYPE        all_active_alarms;
   NUMBER_OF_ALARMS_TYPE         number_of_alarms;        
   FORWARD_POWER_LEVEL_TYPE      forward_power_level;
   REFLECTED_POWER_LEVEL_TYPE    reflected_power_level;
   }ALL_ALARMS_INFO_TYPE;         

   typedef SINT8 ERROR_STRING_NAME_TYPE[ERROR_STRING_SIZE];  /* String equivalent of error enum */

   /* The following is an union of all possible return data from Alarm_Database_Manager */
   typedef __packed__ union
   {
   ALL_ALARMS_INFO_TYPE    all_alarms_info;
   ACT_INACT_TYPE          major_alarm_status;
   ACT_INACT_TYPE          minor_alarm_status;
   ERROR_STRING_NAME_TYPE  error_string_name;
   ACT_INACT_TYPE          single_alarm_status;
   }ALARM_DATABASE_RETURN_DATA_TYPE;
 

   typedef __packed__  enum  /* classification of the diags requests to alarm database mngr*/ 
   {                       
   SET_USER_AND_SOURCE_STATUS = 0u,       /* source reports  the occurence of an alarm */
   CLEAR_SOURCE,                            /* source reports the going away of an alarm */
   CLEAR_SINGLE_ACTUAL_ALRM,
   CLEAR_ALL_ACTUAL_ALRM,
   READ_SINGLE_ACTUAL_ALRM,
   READ_ALL_ACTUAL_ALRM,
   CLEAR_SINGLE_LATCHED_ALRM,
   CLEAR_ALL_LATCHED_ALRM,
   READ_SINGLE_LATCHED_ALRM,
   READ_ALL_LATCHED_ALRM,
   ANALYZE_WILDCARD_ALARMS,
   READ_MAJOR_ALARM_STATUS,
   READ_MINOR_ALARM_STATUS,
   READ_ERROR_STRING_NAME,
   END_OF_DIAGS_REQUEST_TYPE = 255 
   } DIAGS_REQUEST_TYPE;

   typedef __packed__  enum
   {
   ALARM_DATABASE_STATUS_OK =0u,
   INVALID_ERROR_CODE,
   INVALID_ERROR_KIND,
   INVALID_ERROR_REQUEST,
   INVALID_DIAGS_REQUEST
   }ALARM_DATABASE_STATUS_TYPE;

   /* Number of bytes to access    */
   typedef UINT8  ALL_ALARMS_INFO_BYTE_COUNT_TYPE;
                        
   /* interface types for get_all_alarm_ids  */
   typedef UINT16 NUMBER_OF_ALARM_IDS_TYPE;

   typedef ERROR_CODE_TYPE ALARM_IDS_LIST_TYPE[MAX_NUMBER_OF_ALARMS];

   typedef __packed__ struct
      {                          
      NUMBER_OF_ALARM_IDS_TYPE number;
      ALARM_IDS_LIST_TYPE      alarm_id;
      } ALL_POSSIBLE_ALARMS_TYPE;

typedef __packed__  enum
   {
   ERROR_CODE_TRANSLATION_OK = 0u,
   UNKNOWN_TRANSLATION_ERROR_CODE
   } ERROR_CODE_TRANSLATOR_STATUS_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/
                  
ALARM_DATABASE_STATUS_TYPE AlarmDatabaseManager(
DIAGS_REQUEST_TYPE              diags_request_type,
ERROR_CODE_TYPE                 error_code,
ALARM_DATABASE_RETURN_DATA_TYPE **alarm_database_return_data);


void AlarmDatabaseManagerInit(void);
void AlarmDatabaseManagerReadParams(void);
ALL_POSSIBLE_ALARMS_TYPE GetAllAlarmIds(void);

#endif /* ALARM_DATABASE_MANAGER_H */


