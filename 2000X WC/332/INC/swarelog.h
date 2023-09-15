/* $Header:   K:\APPS\PVCS Pro\332new\INC\SWARELOG.H_V   2.3   Oct 11 1999 11:38:40   jzimny  $ */

#ifndef SWARE_LOG_HANDLER_H 
#define SWARE_LOG_HANDLER_H
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

   Filename:  sw


            Written by: Mark Lazarewicz
                  Date: 1/31/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            1/31/96       Mark L      Initial Version
	   2.2          4/20/99       OFI         Changed for DIAB
       2.3         10-11-99       JZ          made SwareLogHandler() type void 
 ------------------------------- DESCRIPTION -----------------------------------

 This file contains the function prototype for  sware_log_handler.c.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "root.h"	     
#include "managerr.h"	     
#include "swaredat.h"	     

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

 
typedef enum
   {
   WRITE_SWARE_LOG = 0u,
   READ_SWARE_LOG,
   CLEAR_SWARE_LOG
   }SWARE_LOG_REQUEST_TYPE;

typedef enum
   {
   SWARE_LOG_PROCESSING_OK = 0u,
   SWARE_LOG_PROCESSING_NOT_OK
   }SWARE_LOG_STATUS_TYPE;


/* ----------------------------- FUNCTION PROTOTYPES ----------------------------- */ 

 SYS_STARTUP_STATUS_TYPE SwareLogHandlerInit(void);

 void SwareLogHandler(                   SWARE_LOG_REQUEST_TYPE        sware_log_request,
                                         ERROR_KIND_TYPE               error_kind,
                                         ERROR_CODE_TYPE               error_code,
                                         ERROR_CALLER_TYPE             error_caller,
                                         ERROR_REQUEST_TYPE            error_request,
                                         C_LINE_NUMBER_TYPE            line_number,
                                         SWARE_LOG_DATABASE_TYPE       **sware_log_return_data_ptr,
                                         SWARE_LOG_BYTE_COUNT_TYPE     *sware_log_byte_count
                                        );



/*
 ------------------------------- MACRO DEFINTIONS ------------------------------
*/

/* MACRO definitions for easy use of manage_errors */
/* It is assumed that the macros calls are ended with a ';' */

#define LOG_PSOS_ERROR(psos_status, error_caller)           \
   if (psos_status != PSOS_OK)                              \
      {                                                     \
      SwareLogHandler(WRITE_SWARE_LOG,                    \
                        PSOS,                               \
                        psos_status,                        \
                        error_caller,                       \
                        LOG_ERROR,                          \
                        __LINE__,                           \
                       (SWARE_LOG_DATABASE_TYPE **)(NULL),  \
                       (SWARE_LOG_BYTE_COUNT_TYPE *)(NULL)  \
                       );                                   \
      }                                                     \
   else{}

/* MACRO definitions for easy use of manage_errors */
/* It is assumed that the macros calls are ended with a ';' */

#define LOG_SWARE_ERROR(error_code, error_caller)           \
   SwareLogHandler(WRITE_SWARE_LOG,                       \
                     SWARE,                                 \
                     error_code,                            \
                     error_caller,                          \
                     LOG_ERROR,                             \
                     __LINE__,                              \
                     (SWARE_LOG_DATABASE_TYPE **)(NULL),    \
                     (SWARE_LOG_BYTE_COUNT_TYPE *)(NULL)    \
                     );

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* SWARE_LOG_HANDLER_H */
