/* $Header:   K:\APPS\PVCS Pro\332new\App\CKPTGBUF.C_V   2.3   Dec 16 1999 16:19:14   lmarkure  $ */
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

   Module name:  Ck_Pt_Getbuf

   Filename:  ckptgbuf.c

   Function name:  CkPtGetbuf

            Written by:  Mark Lazarewicz
                  Date:  03/18/96
              Language:  Microtec "C"

  -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            03/18/96      Mark L      Initial
      2.3          12/16/99      LAM         removed unused error handling code
 
 ------------------------------- DESCRIPTION -----------------------------------
 
   This module:

     - executes the pSOS pt_getbuf command using the partition_id data
       (psos_buffer_ptr) to the requested buffer.
     - It also handles the possible pSOS errors that can occur.
       "Partition Deleted" and "Partition ID Incorrect" errors cause the error
       to be reported and a "Reset Welder" request (ManageErrorsMain will
       reset the welder).  An "Out of Partition Buffers" error causes the
       error to be reported with a "Log Only" request.  The module then waits for
       the prescribed period of time (psos_error_retry_time).  After the wait the
       pt_getbuf is retried.  If any errors occur then the error is reported with
       a "Reset Welder" request (ManageErrorsMain will reset the welder).
     - All error calls to Manage_Errors pass the caler_module_id and the
       caller_line_number values received from the calling routine.  No error
       handling is required to take into account the condition where this module
       is returned to after having requested a "Welder Reset" due to an error in
       the error manager module.

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include <psos.h>                    /* for interface to pt_getbuf            */
#include "ckptgbuf.h"                /* contains function interface           */
#include "ticks.h"

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/
#define ONE_TICK 1
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
                              
/*
 ---------------------------------- CODE ---------------------------------------
*/

void CkPtGetbuf(
   UINT32              partition_id,
   void                **psos_buffer_ptr,
   ERROR_CALLER_TYPE   caller_module_id,
   UINT32              caller_line_number,
   UINT32              psos_error_retry_count 
   ) 
   {
   UINT32    PsosStatus;

   /* Get a buffer from destination's partition */
   PsosStatus = pt_getbuf(partition_id, psos_buffer_ptr);

   if ( PsosStatus != PSOS_NOERROR ) /* Check for any error */
      {
      /* Look for "Out of Partition Buffers" error */
      if ( PsosStatus == ERR_NOBUF )
         {

         /* retry get buf the requested amount of time */
         while ((psos_error_retry_count-- > 0) && (PsosStatus != PSOS_NOERROR))
	    {
            /* wait for requested time */
            tm_wkafter(ONE_TICK); 

            /* Try to get buffer again */
            PsosStatus = pt_getbuf(partition_id, psos_buffer_ptr);
            }

         }
      } /* Check for pSOS error */

   return;
   }

/* For Unit testing of this routine */
#ifdef INCLUDE_UNIT_TEST
#include "ckptgbuf.ut"
#endif
