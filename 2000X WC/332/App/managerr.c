/* $Header:   L:/pvcs/1000/psos332/archives/app/managerr.c_v   2.7   11 Sep 1997 10:13:22   pgarvey  $ */
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

/* ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  Manage_Errors

   Filename:     managerr.c


            Written by: Mark Lazarewicz 
                  Date: 2/1/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            02/01/96      Mark L      Initial
      1            03/18/96      Mark L      Bring upto Coding Standard
      2            06/25/96      Lam         added product code define  
      3            09/17/96      Lam         deleted warnings  
      4            01/06/97      LAM         redefined beep prototype
      2.7          09/11/97      PaulG       Unit test and data cleanup
 
 ------------------------------- DESCRIPTION -----------------------------------

   This library routine is called whenever an application wishes to report an
   error or alarm.  This function formats an error message and sends it to the
   DIAG (Diagnostics Manager) queue. This function also deals with fatal error 
   handling by deleting the queue and suspending the calling task. This function
   also does system resets when requested by an application.

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ LOCAL EQUATES ----------------------------------

 ------------------------------- EXPORT DATA -----------------------------------

 ------------------------------- IMPORT DATA -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/
                                                                    
#include <psos.h>                      /* psos defines and prototypes, etc..     */
#include "managerr.h"                  /* defines/prototype for error manager    */
#include "diagnose.h"                  /* Needed for queue_error() prototype     */
#include "xception.h"
#include "beep.h"


/* define all function interfaces */
#include "swarelog.h"
#include "run_task.h"                  /* Needed for FATAL_ERROR_PRIORITY        */ 

/*
 ------------------------------ EXTERNAL DATA ----------------------------------

 ------------------------------ LOCAL DEFINES ----------------------------------
*/

/* indicates to suspend this task */
#define THIS_TASK       0
#define PRODUCT_CODE       1


/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------

 ---------------------------- PRIVATE GLOBAL DATA ------------------------------

 ------------------------------- LOCAL DATA ------------------------------------

 ---------------------- IMPORT SUBROUTINES REFERENCED --------------------------
                              
 ---------------------------------- CODE ---------------------------------------
*/

void ManageErrorsMain(
   ERROR_KIND_TYPE      error_kind,
   ERROR_CODE_TYPE      error_code,
   ERROR_CALLER_TYPE    error_caller,
   ERROR_REQUEST_TYPE   error_request,
   C_LINE_NUMBER_TYPE   line_number
   )
   {
   UINT32               OldPriority;

   if (error_request == RESET_WELDER)
      {
      /*
       * Set this task priority to just below NVM manager
       */
      t_setpri( THIS_TASK, FATAL_ERROR_PRIORITY, &OldPriority);

 
         /* log SWARE error */
         
         SwareLogHandler(WRITE_SWARE_LOG,
                           error_kind,
                           error_code,
                           error_caller,
                           error_request,
                           line_number,
                           ((SWARE_LOG_DATABASE_TYPE **) NULL),
                           ((SWARE_LOG_BYTE_COUNT_TYPE *) NULL)
                           );
         
         
#ifdef PRODUCT_CODE 
      
      /* call exception_handler */
//      exception_handler ();
        Beep(PSOSBEEP);
      
#else /* Cause pROBE entry or XRAY breakpoint. */

      asm(" trap #0"); 

#endif  /* end PRODUCT_CODE */
      }
   
   else if (error_code < MAX_NUMBER_OF_ERROR_CODES)
      {
      /*
       * Queue the error at the Diagnostic Manager
       */
      QueueError( error_kind,
                   error_code,
                   error_caller,
                   error_request,
                   line_number );

      if  (error_request == UNRECOVERABLE)
         {
#ifndef PRODUCT_CODE 
       
         /* Cause pROBE entry or XRAY breakpoint. */
         asm(" trap #0"); 

#endif  /* end PRODUCT_CODE */
         }
      }

   else  /* log invalid error code in the SWARE LOG */
      {
      LOG_SWARE_ERROR(E_INVALID_ERROR_CODE, MANAGE_ERRORS_MAIN);
      }

   return;

   } /* end of manage_errors routine */


/*FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "managerr.ut"
#endif
/*FOR UNIT TEST ONLY */
