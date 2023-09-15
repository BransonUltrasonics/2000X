/* $Header:   L:/pvcs/1000/psos332/archives/inc/DIAGNOSE.H_v   2.1   01 Aug 1996 14:50:04   BKYMER  $ */
#ifndef DIAGNOSTICS_MANAGER_H 
#define DIAGNOSTICS_MANAGER_H
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

   Module name: DIAGNOSTICS_MANAGER

   Filename: diagnose.h 


            Written by: Mark Lazarewicz 
                  Date: 02/01/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author           Description
   ==========      ========      ===========      ==============
       0           02/01/96      Mark L           initial Version

 ------------------------------- DESCRIPTION -----------------------------------

   This header defines the return value and function prototype for the
   Diagnostics_Manager module.

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "managerr.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/
   
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/
                                       
void DiagnosticsManager(void); 

void QueueError(
   ERROR_KIND_TYPE      error_kind,
   ERROR_CODE_TYPE      error_code,
   ERROR_CALLER_TYPE    error_caller,
   ERROR_REQUEST_TYPE   error_request,
   C_LINE_NUMBER_TYPE   line_number );


#endif /* DIAGNOSTICS_MANAGER_H */
