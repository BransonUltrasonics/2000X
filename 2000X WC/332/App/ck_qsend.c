/* $Header:   K:/APPS/PVCS Pro/332new/App/CK_QSEND.C_V   2.8   Oct 14 2003 08:22:20   BWadia  $ */
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

   Module name:  Ck_Q_Send

   Filename:  ck_qsend.c

   Function name:  CkQSend

            Written by:  Mark Lazarewicz
                  Date:  02/18/96
              Language:  Microtec "C"

  -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            02/18/96      Mark L      Initial Version
      1            03/18/96      Mark L      Coding Standards
      2	           10/29/96      LAM         added errors
      3	           05/02/97      PhilJ       deleted while loop in retry q_send
      4	           05/07/97      LAM         added psosreadyflag               
      5	           05/08/97      LAM         deleted printqueue check            
      6.2.6	       06/18/97      LAM         deleted warnings
      2.7	       12/16/99      LAM         deleted unused error handling code
      2.8          10/14/03      JOY         In case qvga queue send data once to the queue.


  ------------------------------- DESCRIPTION -----------------------------------
 
   This module:

     - executes the pSOS q_send command using the psos_msg_ptr and psos_queue_id data
       passed to it.  Nothing is returned.
     - It also handles the possible pSOS errors that can occur.
       "Queue Deleted" and "Queue ID Incorrect" errors cause the error to be reported
       and a "Reset Welder" request (manage_errors_main will reset the station).
       "Out of System Buffers" and "All System Buffers are Full" errors causes the
       error to be reported with a "Log Only" request.  The module thaen waits for
       the prescribed period of time (psos_error_retry_time).
       After the wait the q_send is retried.  If any errors occur then the error is
       reported with a "Reset Welder" request (manage_errors_main will reset the station).
     - All error calls to Manage_Errors pass the caler_module_id and the
       caller_line_number values received from the calling routine.  No error handling
       is required to take into account the condition where this module is returned
       to after having requested a "Station Reset" due to an error in the error manager
       module.

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include <psos.h>               /* for interface to q_send               */

#include "ck_qsend.h"           /* contains function interface           */
#include "alarms.h"
#include "names.h"
#include "ready.h"
#include "util.h"

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/
extern UINT32 FpscQid;
extern UINT32 QvgaQid;
/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/

/*
 ------------------------------- GLOBAL DATA -----------------------------------
                        (scope is global to ALL files)
*/

/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
                        (scope is global to THIS file)
*/
UINT16 QCount = 0;                              
UINT16 PsosReadyFlag = TRUE;
/*
 ---------------------------------- CODE ---------------------------------------
*/

void CkQSend(
   UINT32              psos_queue_id,
   void               *psos_msg_ptr,
   ERROR_CALLER_TYPE   caller_module_id,
   UINT32              caller_line_number,
   UINT32              psos_error_retry_count){

   UINT32      PsosStatus,LineNumber;
   ERROR_CALLER_TYPE Caller;

   /* Send message to requested queue */
   LineNumber = caller_line_number;
   Caller = caller_module_id;
   PsosStatus = q_send(psos_queue_id, psos_msg_ptr);
   if ( PsosStatus != PSOS_NOERROR ){
      /* Retry on Out of buffers or All buffers are full after wait */
      if(psos_queue_id != FpscQid &&
         psos_queue_id != QvgaQid ){
         /* retry q_send the requested amount of time */
         PsosReadyFlag = FALSE;
         tm_wkafter(psos_error_retry_count + QCount);
         /* Try to send message to requested queue again */
         PsosStatus = q_send(psos_queue_id, psos_msg_ptr);
      }
   } /* Check for pSOS errors */
}

/* For Unit testing of this routine */
#ifdef INCLUDE_UNIT_TEST
#include "ck_qsend.ut"
#endif
