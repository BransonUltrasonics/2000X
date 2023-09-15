/* $Header:   K:\APPS\PVCS Pro\332\INC\ERR_DATA.H_V   2.4   Apr 19 1999 14:30:24   ofingere  $ */
#ifndef ERROR_LOG_DATA_TYPE_H 
#define ERROR_LOG_DATA_TYPE_H
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

   Module name: error_log_data_type

   Filename:  err_data.h


	    Written by: Mark Lazarewicz  
		  Date: 2/6/96 
	      Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            02/06/96      Mark L      Initial Version
       1            07/06/96      LAM         cleanup warnings
	   2.4			04/19/99	  OFI		  Changed for DIAB
 ------------------------------- DESCRIPTION -----------------------------------

 This file contains the the typdefs used by error_log_handler.c as well as 
 read_error_log_response_msg.h.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "managerr.h"        
#include "time.h"            
/*
 --------------------------------- DEFINES -------------------------------------
*/

#define MAX_ERROR_LOG_ENTRIES     128

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef UINT16  ERROR_COUNT_TYPE; 
	 

typedef struct
   {
   ERROR_KIND_TYPE            error_kind;   /* 1 Byte */
   ERROR_REQUEST_TYPE         error_request;/* 1 Byte */
   ERROR_CODE_TYPE            error_code;   /* 2 Bytes */
   ERROR_CALLER_TYPE          error_caller; /* 2 Bytes */
   C_LINE_NUMBER_TYPE         line_number;  /* 2 Bytes */
   ERROR_COUNT_TYPE           error_count;  /* 2 Bytes */
   struct t_date              last_date;    /* 4 Bytes */
   struct t_time              last_time;    /* 4 Bytes */ 
   }ERROR_LOG_DATA_TYPE;

/***
 *** When the structure "ERROR_LOG_DATA_TYPE" changes size,
 *** the #define " ERROR_LOG_DATA_TYPE_SIZE"  has to change.
 ***/

#define  ERROR_LOG_DATA_TYPE_SIZE 18

/* Create the software log database */
typedef ERROR_LOG_DATA_TYPE   ERROR_LOG_DATABASE_TYPE[MAX_ERROR_LOG_ENTRIES];

/* Number of bytes to access    */
typedef UINT16  ERROR_LOG_BYTE_COUNT_TYPE; 


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* ERROR_LOG_DATA_TYPE_H */
