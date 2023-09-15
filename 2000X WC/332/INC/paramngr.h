/* $Header:   L:/pvcs/1000/psos332/archives/inc/paramngr.h_v   2.2   18 Sep 1996 10:17:10   lmarkure  $ */
#ifndef PARAMNGR_H
#define PARAMNGR_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: PARAMETER_MANAGER

   Filename: paramngr.h 


            Written by: Mark Lazarewicz
                  Date: 03/12/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
        0           03/12/96      Mark L      Initial Version
        1           09/09/96      LAM         cleanup warnings

 ------------------------------- DESCRIPTION -----------------------------------

  This header file contains or references all interface typedefs for the 
  parameter_manager interface as well as it's function prototype.
  The library function accepts requests to read and write a specified parameter in 
  in the parameter database.  It will also provide the caller with the text for the
  parameter's name or set a specified parameter to its default value.  Return values
  are the status of the execution, the basic C type and the byte count of the 
  parameter.                    

  Note: In order to safeguard various requests to change critical data areas the
        following "keys" are required with the listed parameter requests:  
        REBUILD_PARAMETER_DATABASE_DEFAULTS keys:
                                 parameter_id = MAX_NUMBER_PARAMETER_IDS
                                 local_variable_size = PARAMETER_SIZE_UNKNOWN.

 ------------------------------ INCLUDE FILES ----------------------------------
*/
                                                                          
#include "root.h"                         /* define SYS_STARTUP_STATUS_TYPE   */
#include "managerr.h"
#include "parametr.h"
#include "pm2ascii.h"
#include "parmdata.h"

  

/*
 --------------------------------- DEFINES -------------------------------------
*/
/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
/* -------------------- */
/*    INTERFACE TYPES   */
/* -------------------- */
/* return value incicating the basic C type of the parameter */

/* requested parameter database action */
typedef enum
   {
   WRITE_PARAMETER =1,
   READ_PARAMETER = 2,
   GET_PARAMETER_NAME_TEXT = 3,
   SET_PARAMETER_TO_DEFAULT = 4,
   REBUILD_PARAMETER_DATABASE_DEFAULTS = 5,
   SET_PARAMETER_MIN_LIMIT = 6,
   SET_PARAMETER_MAX_LIMIT = 7,
   SET_PARAMETER_DEFAULT   = 8,
   WRITE_PARAMETER_NO_NOTIFICATION = 9
   } PARAMETER_ACCESS_TYPE;
                                
/* the processing status of the requested database action */
/* explicit manage error error codes are for sware log purposes */
typedef enum
   {
   PARAMETER_OK = 0, 
   SIZE_DOES_NOT_MATCH_LOCAL_VARIABLE = E_SIZE_DOES_NOT_MATCH_LOCAL_VARIABLE,
   PARAMETER_WRITE_VALUE_OUT_OF_RANGE = E_PARAMETER_WRITE_OUT_OF_RANGE,
   PARAMETER_DATABASE_OUT_OF_RANGE    = E_PARAMETER_DATABASE_OUT_OF_RANGE,
   UNKNOWN_PARAMETER                  = E_PARAMETER_UNKNOWN,
   UNKNOWN_ACCESS_REQUEST             = E_PARAMETER_UNKNOWN_ACCESS_REQUEST,
   PARAMETER_READ_ONLY                = E_PARAMETER_READ_ONLY,
   PARAMETER_MANAGER_ATTRIBUTE_ERROR  = E_PARAMETER_ATTRIBUTE_FAULT,
   ILLEGAL_PARAMETER_WRITE_REQUEST    = E_ILLEGAL_PARAMETER_WRITE,
   } PARAMETER_MANAGER_ERROR_TYPE;                                       

/* return value of the byte size of the parameter */
typedef packed enum
   {
    PARAMETER_SIZE_UNKNOWN      = 0,
    PARAMETER_SIZE_ONE_BYTE     = 1,
    PARAMETER_SIZE_TWO_BYTE     = 2,
    PARAMETER_SIZE_FOUR_BYTE    = 4, 
    PARAMETER_SIZE_EIGHT_BYTE   = 8,                       
    PARAMETER_SIZE_STRING_BYTE  = MAX_PARAMETER_STRING_SIZE
    } PARAMETER_BYTE_COUNT_TYPE;
                                                 
/* all informational return values */
typedef struct
   {
   PARAMETER_MANAGER_ERROR_TYPE  status;
   PARAMETER_DATA_TYPE_TYPE      data_type;
   PARAMETER_BYTE_COUNT_TYPE     byte_count;
   } PARAMETER_MANAGER_STATUS_TYPE;
                                     
typedef char PARAMETER_STRING_TYPE[MAX_PARAMETER_STRING_SIZE];
                         
/*
 ------------------------------- MACRO DEFINTIONS ------------------------------
*/

/* MACRO definitions for easy use of manage_errors */
/* It is assumed that the macros calls are ended with a ';' */

/* the 'else' is to make sure this 'if' doesn't steal another 'ifs' 'else' */

#define PMAN_CHECK_SIZE(parameter_status, error_caller)                        \
   if (parameter_status.status == SIZE_DOES_NOT_MATCH_LOCAL_VARIABLE)          \
      {                                                                        \
      ManageErrorsMain (                                                     \
                         SWARE,                                                \
                         E_SIZE_DOES_NOT_MATCH_LOCAL_VARIABLE,                 \
                         error_caller,                                         \
                         RESET_WELDER,                                        \
                          __LINE__);                                           \
      }                                                                        \
   else if (parameter_status.status != PARAMETER_OK)                           \
      {                                                                        \
      ManageErrorsMain (                                                     \
                         SWARE,                                                \
                         parameter_status.status,                              \
                         error_caller,                                         \
                         LOG_ERROR,                                            \
                          __LINE__);                                           \
      }

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

PARAMETER_MANAGER_STATUS_TYPE  ParameterManager (PARAMETER_ACCESS_TYPE parameter_access_request,
                                     PARAMETER_ID_TYPE     parameter_id,            
                                     PARAMETER_BYTE_COUNT_TYPE local_variable_size,
                                     PARAMETER_VALUE_TYPE  *parameter_value
                                    );


SYS_STARTUP_STATUS_TYPE ParameterManagerInit (void);

PARAMETER_MANAGER_ERROR_TYPE     GetParameterOperator(
   PARAMETER_ID_TYPE         parameter_id,
   PARAMETER_OPERATOR_TYPE   *parameter_operator);


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/        


#endif /* PARAMETER_MANAGER_H */
