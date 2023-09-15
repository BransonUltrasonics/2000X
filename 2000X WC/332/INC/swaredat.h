/* $Header:   K:\APPS\PVCS Pro\332\INC\SWAREDAT.H_V   2.2   Apr 20 1999 11:05:58   ofingere  $ */


#ifndef SWARE_LOG_DATA_TYPE_H 
#define SWARE_LOG_DATA_TYPE_H

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

   Module name: sware_log_data_type

   Filename:  swaredat.h


            Written by: Mark Lazarewicz 
                  Date: 2/1/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
       0            02/01/96      Mark L      Initial Version
	   2.2			04/20/99	  OFI		  Changed for DIAB
 ------------------------------- DESCRIPTION -----------------------------------

 This file contains the the typdefs used by sware_log_handler as well as 
 read_sware_log_response_msg 

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "managerr.h"	     
/*
 --------------------------------- DEFINES -------------------------------------
*/

#define MAX_SWARE_LOG_ENTRIES     128

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

 
typedef struct
   {
   ERROR_KIND_TYPE            error_kind;    /* 1 Byte */     
   ERROR_REQUEST_TYPE         error_request; /* 1 Byte */     
   ERROR_CODE_TYPE            error_code;    /* 2 Bytes */    
   ERROR_CALLER_TYPE          error_caller;  /* 2 Bytes */    
   C_LINE_NUMBER_TYPE         line_number;   /* 2 Bytes */    
  }SWARE_LOG_DATA_TYPE;                     
                                            
/***
 *** When the structure "SWARE_LOG_DATA_TYPE" changes size,
 *** the #define " SWARE_LOG_DATA_TYPE_SIZE"  has to change.
 ***/

#define SWARE_LOG_DATA_TYPE_SIZE  8          

/* Create the software log database */
typedef SWARE_LOG_DATA_TYPE   SWARE_LOG_DATABASE_TYPE[MAX_SWARE_LOG_ENTRIES];

/* Number of bytes to access    */
typedef UINT16  SWARE_LOG_BYTE_COUNT_TYPE; 

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* SWARE_LOG_HANDLER_H */
