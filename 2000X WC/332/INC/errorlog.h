/* $Header:   K:\APPS\PVCS Pro\332\INC\ERRORLOG.H_V   2.3   Apr 19 1999 15:21:52   ofingere  $ */
#ifndef ERROR_LOG_HANDLER_H 
#define ERROR_LOG_HANDLER_H
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

   Module name:  n/a

   Filename:  errorlog.h


            Written by: Mark Lazarewicz
                  Date: 2/5/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            02/05/96      Mark L      Initial
       1            04/28/97      LAM         cleanup            
	   2.3			04/19/99	  OFI		  Changed for DIAB
 ------------------------------- DESCRIPTION -----------------------------------

 This file contains the function prototype for  error_log.c.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "root.h"     
#include "managerr.h"     
#include "err_data.h"     

/*
 --------------------------------- DEFINES -------------------------------------

 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
 
typedef  enum
   {
   WRITE_ERROR_LOG = 0u,
   READ_ALL_ERRORS_IN_ERROR_LOG,
   READ_ERR_LOG_ENTRIES_1_20,
   READ_ERR_LOG_ENTRIES_21_40,
   READ_ERR_LOG_ENTRIES_41_60,
   READ_ERR_LOG_ENTRIES_61_80,
   CLEAR_ERROR_LOG
   }ERROR_LOG_REQUEST_TYPE;

typedef  enum
   {
   ERROR_LOG_PROCESSING_OK = 0u,
   ERROR_LOG_PROCESSING_NOT_OK
   }ERROR_LOG_STATUS_TYPE;

typedef enum
   {
   GROUP_NUMBER_ONE = 1,  /* THIS HAS TO BE 1 and NOT 0 for equation in copy_error_log_chunk function.*/
   GROUP_NUMBER_TWO = 2,
   GROUP_NUMBER_THREE = 3,
   GROUP_NUMBER_FOUR = 4
   }ERROR_LOG_GROUP_NUMBER_TYPE;

/* ----------------------------- FUNCTION PROTOTYPES ----------------------------- */ 

SYS_STARTUP_STATUS_TYPE ErrorLogHandlerInit(
   void
   );

ERROR_LOG_STATUS_TYPE ErrorLogHandler(
   ERROR_LOG_REQUEST_TYPE        error_log_request,
   ERROR_KIND_TYPE               error_kind,
   ERROR_CODE_TYPE               error_code,
   ERROR_CALLER_TYPE             error_caller,
   ERROR_REQUEST_TYPE            error_request,
   C_LINE_NUMBER_TYPE            line_number,
   ERROR_LOG_DATABASE_TYPE       **error_log_return_data_ptr,
   ERROR_LOG_BYTE_COUNT_TYPE     *error_log_byte_count
   );

UINT16 ErrorLogWriteEntry (
   ERROR_KIND_TYPE               error_kind,
   ERROR_CODE_TYPE               error_code,
   ERROR_CALLER_TYPE             error_caller,
   ERROR_REQUEST_TYPE            error_request,
   C_LINE_NUMBER_TYPE            line_number );

void ErrorLogEmergencySave(
   UINT16                        error_log_index,
   UINT16                        number_of_entries );


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* ERROR_LOG_HANDLER_H */
