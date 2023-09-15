/* $Header:   K:\APPS\PVCS Pro\332new\App\SWARELOG.C_V   2.6   Oct 11 1999 11:20:22   jzimny  $ */
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

   Module name:  Sware_Log_Handler

   Filename:     swarelog.c


            Written by: Mark Lazarewicz 
                  Date: 1/31/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            01/31/96      Mark L      Initial Version
      1            11/09/96      LAM         replaced q_send
      2            01/29/97      LAM         made queues global
      3.2.5        06/17/97      LAM         deleted nvmqid
      2.6          10-11-99      JZ          made SwareLogHandler() type void

  ------------------------------- DESCRIPTION -----------------------------------

   This library routine is called by manage_errors and diagnostic_manager to log
   sware errors.

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ LOCAL EQUATES ----------------------------------

 ------------------------------- EXPORT DATA -----------------------------------

 ------------------------------- IMPORT DATA -----------------------------------
   
 ------------------------------ INCLUDE FILES ----------------------------------
*/
                                                                    
#include <psos.h>                  /* psos defines and prototypes, etc..     */
#include "root.h"           
#include "names.h"            /* psos object defines                    */
#include "swarelog.h"
#include "managerr.h"
#include <prepc.h>
#include "opcodes.h"
#include "battram.h"

/* Outgoing messages */
#include "nvm_msg.h"
#include "ticks.h"
#include "ck_qsend.h"           /* contains function interface           */

/*
 ------------------------------ EXTERNAL DATA ----------------------------------

 ------------------------------ LOCAL DEFINES ----------------------------------
*/
 
#define LAST_ERROR_WRITTEN     UNKNOWN_ERROR_KIND  /*Invalid error kind value used for MARKER */
#define TWO_ENTRIES            2
#define NEXT_SWARE_LOG_ENTRY   1     
#define INITIAL_SWARE_LOG_INDEX 0

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------

 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
*/

/* CREATE THE SWARE LOG DATABASE */
static SWARE_LOG_DATABASE_TYPE   SwareLogDatabase;

static SWARE_LOG_DATA_TYPE       SwareLogData; 

static SWARE_LOG_DATABASE_TYPE   *sware_log_seg_addr;  /* pointer assigned to segment */
static UINT8                     LatestSwareLogIndex;      /* sware log index */

/*
 ---------------------- IMPORT SUBROUTINES REFERENCED --------------------------
                              
 ---------------------------------- CODE ---------------------------------------
*/
void SwareLogHandler(
   SWARE_LOG_REQUEST_TYPE    sware_log_request,
   ERROR_KIND_TYPE           error_kind,
   ERROR_CODE_TYPE           error_code,
   ERROR_CALLER_TYPE         error_caller,
   ERROR_REQUEST_TYPE        error_request,
   C_LINE_NUMBER_TYPE        line_number,
   SWARE_LOG_DATABASE_TYPE   **sware_log_return_data_ptr,
   SWARE_LOG_BYTE_COUNT_TYPE *sware_log_byte_count
   )
   {

   NVM_ACCESS_MSG   NvmAccessMsg; 
   UINT8            SwareLogIndex;      /* sware log index */
   BOOLEAN          match_found = FALSE;

   switch(sware_log_request)
      {
      case WRITE_SWARE_LOG:
          
         for (SwareLogIndex = 0;
             (SwareLogIndex < MAX_SWARE_LOG_ENTRIES) && (match_found == FALSE); 
             SwareLogIndex++)
            {     
      
            /* Look for a match */
            if ((SwareLogDatabase[SwareLogIndex].error_kind == error_kind) &&
               (SwareLogDatabase[SwareLogIndex].error_code == error_code) &&
               (SwareLogDatabase[SwareLogIndex].error_caller == error_caller) &&
               (SwareLogDatabase[SwareLogIndex].error_request == error_request) &&
               (SwareLogDatabase[SwareLogIndex].line_number == line_number))   
               {
               match_found =  TRUE;
               }

            } /* END FOR LOOP */

         if (match_found == FALSE )

             /* No match is found: record the new error. */

            {

            /* Fill the SwareLogDatabase with the correct values */ 
            SwareLogDatabase[LatestSwareLogIndex].error_kind = error_kind;
            SwareLogDatabase[LatestSwareLogIndex].error_code = error_code;
            SwareLogDatabase[LatestSwareLogIndex].error_caller = error_caller;
            SwareLogDatabase[LatestSwareLogIndex].error_request = error_request;
            SwareLogDatabase[LatestSwareLogIndex].line_number = line_number;


             /* Form and send message to NVM queue to write to BATTRAM.
             * Write the last valid entry AND the invalid error entry MARKER to
             * identify the last valid entry if you have NOT reached the last
             * entry of the SWARE LOG
             */

            if (LatestSwareLogIndex < MAX_SWARE_LOG_ENTRIES - 1)
               {

               /* Form and write the next error entry into DRAM with an invalid error
                * kind. This marker is used to determine the last valid entry in the
                * SWARE  LOG.
                */
               SwareLogDatabase[LatestSwareLogIndex + NEXT_SWARE_LOG_ENTRY].error_kind = 
                                                                                  LAST_ERROR_WRITTEN;

               NvmAccessMsg.common.opcode       = OP_BATTRAM_WRITE_SWARE_LOG;
               NvmAccessMsg.common.pointer_flag = NO_DATA_PTR;
               NvmAccessMsg.common.source_task =  DIAG_SOURCE_TASK;
               NvmAccessMsg.data_pointer        = (BYTE *)(&SwareLogDatabase[LatestSwareLogIndex]);
               NvmAccessMsg.offset              = (sizeof(SwareLogData))*(LatestSwareLogIndex);
               NvmAccessMsg.byte_count          = sizeof(SWARE_LOG_DATA_TYPE) * TWO_ENTRIES;
              
               }

             else

               /* Write only the valid error entry (not the MARKER) if you are at
                * the LAST ENTRY since you are at the end of the table and you don't
                *  want to write into unknown memory.
                */

               {
               NvmAccessMsg.common.opcode       = OP_BATTRAM_WRITE_SWARE_LOG;
               NvmAccessMsg.common.pointer_flag = NO_DATA_PTR;
               NvmAccessMsg.common.source_task =  DIAG_SOURCE_TASK;
               NvmAccessMsg.data_pointer        = (BYTE *)(&SwareLogDatabase[LatestSwareLogIndex]);
               NvmAccessMsg.offset              = (sizeof(SWARE_LOG_DATA_TYPE))*(LatestSwareLogIndex);
               NvmAccessMsg.byte_count          = sizeof(SWARE_LOG_DATA_TYPE);
 
               }

//               CkQSend (NvmmQid,&NvmAccessMsg,DIAG_SOURCE_TASK,__LINE__,        /* line number   */
//                                   MILLS_TO_TICKS(10));      /* 10 ms        */
               /* Increment LatestSwareLogIndex to the next sware log entry */
               LatestSwareLogIndex = (LatestSwareLogIndex + 1) % MAX_SWARE_LOG_ENTRIES;

            } /* END  (if match_found == FALSE) */

         break;

      case READ_SWARE_LOG:
         SwareLogIndex = 0;

         while (( SwareLogIndex < MAX_SWARE_LOG_ENTRIES) &&
            (SwareLogDatabase[SwareLogIndex].error_kind != MAX_NUMBER_OF_ERROR_KINDS) &&
            (SwareLogDatabase[SwareLogIndex].error_kind != LAST_ERROR_WRITTEN))
            SwareLogIndex++;

         *sware_log_byte_count = (SwareLogIndex *  sizeof(SWARE_LOG_DATA_TYPE));

         /* Copy SwareLogDatabase into the buffer */
         memcpy (sware_log_seg_addr, 
                 SwareLogDatabase, 
                 *sware_log_byte_count
                 );    

         /* Set the return data pointer equal to the buffer pointer */
         *sware_log_return_data_ptr = sware_log_seg_addr; 
         break;

      case CLEAR_SWARE_LOG:
         /* Initialize SwareLogIndex to 0 */
         SwareLogIndex = 0;

         while ( SwareLogIndex < MAX_SWARE_LOG_ENTRIES)
            {
            SwareLogDatabase[SwareLogIndex].error_kind = MAX_NUMBER_OF_ERROR_KINDS;
            SwareLogDatabase[SwareLogIndex].error_code = MAX_NUMBER_OF_ERROR_CODES;
            SwareLogDatabase[SwareLogIndex].error_caller = MAX_NUMBER_OF_ERROR_CALLERS;
            SwareLogDatabase[SwareLogIndex].error_request = MAX_NUMBER_OF_ERROR_REQUESTS;
            SwareLogDatabase[SwareLogIndex].line_number = 0;

            SwareLogIndex++;
           }

         NvmAccessMsg.common.opcode       = OP_BATTRAM_WRITE_SWARE_LOG;
         NvmAccessMsg.common.pointer_flag = NO_DATA_PTR;
         NvmAccessMsg.common.source_task =  DIAG_SOURCE_TASK;
         NvmAccessMsg.data_pointer        = (BYTE *)SwareLogDatabase;
         NvmAccessMsg.offset              = 0;
         NvmAccessMsg.byte_count          = sizeof(SWARE_LOG_DATABASE_TYPE);

         /* Set the index back to 0 */
         LatestSwareLogIndex = 0;

//         CkQSend (NvmmQid,&NvmAccessMsg,DIAG_SOURCE_TASK,__LINE__,        /* line number   */
//                                   MILLS_TO_TICKS(10));      /* 10 ms        */
         break;

      } /* END SWITCH */

   }

/* ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:     Sware_Log_Handler    

   Filename:        swarelog.c    

   Function name:   SwareLogHandlerInit


            Written by: Mark Lazarewicz
                  Date: 2/1/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             02/01/96     Mark L      Initial Version

 ------------------------------- DESCRIPTION -----------------------------------

 This function initializes all static data associated with its assosiated function.
 This function exists in its assosiated function's source file following the
 function code.  This function assumes that the static data it initializes has 
 previously been defined with "file" visibility.  This function shall be called
 from its associated functions task initialization function.

 ------------------------------- PSEUDO CODE -----------------------------------
                                                                          
 initialize static data to startup states/values

 ---------------------------------- CODE ---------------------------------------
*/  
SYS_STARTUP_STATUS_TYPE SwareLogHandlerInit(
   void
   )
   {      
   SYS_STARTUP_STATUS_TYPE  SysStartupStatus = SYS_STARTUP_PASS;

   UINT32                      PsosStatus;
   UINT32                      PsosRegionId;
   BATTRAM_ACCESS_STATUS_TYPE  SramStatus;
   UINT8                       SwareLogIndex;      /* sware log index */

   /* Identify REGION 0 */
   PsosStatus = rn_ident(ROOT_REGION_ZERO_NAME, &PsosRegionId);
 
   if (PsosStatus != PSOS_NOERROR)
      SysStartupStatus = SYS_STARTUP_FAIL;

   if (SysStartupStatus == SYS_STARTUP_PASS)
      {
      /* Get some memory from REGION 0 */
      PsosStatus = rn_getseg(PsosRegionId,
                              (sizeof (SWARE_LOG_DATABASE_TYPE)),
                              RN_NOWAIT,
                              RN_WAIT_FOREVER,
                              (void *)&sware_log_seg_addr);

      if (PsosStatus != PSOS_NOERROR)
         SysStartupStatus = SYS_STARTUP_FAIL;
      }

   /* ADD INIT ROUTINE TO HANDLE DATABASE COPY OF THE LOG AT STARTUP */
   SramStatus = BattramAccess(BATTRAM_READ_ACCESS,
                             SWARE_LOG_SECTION,
                             (BYTE *)SwareLogDatabase,
                             0,
                             sizeof(SWARE_LOG_DATABASE_TYPE)
                             );

   if (SramStatus == BATTRAM_ACCESS_STATUS_OK)
      {
      SwareLogIndex = 0;
      
      /* SEARCH FOR THE LAST ERROR THAT WAS WRITTEN INTO BATTRAM (MARKER) BEFORE STATION WENT DOWN */
      while ((SwareLogDatabase[SwareLogIndex].error_kind != LAST_ERROR_WRITTEN)
            && (SwareLogIndex < MAX_SWARE_LOG_ENTRIES))
         SwareLogIndex ++;

      if (SwareLogIndex == MAX_SWARE_LOG_ENTRIES)
            
             /* if no match was found then set  LatestSwareLogIndex to INITIAL_SwareLogIndex. */ 
             LatestSwareLogIndex = INITIAL_SWARE_LOG_INDEX;

       else if (SwareLogIndex < MAX_SWARE_LOG_ENTRIES)

         /* a match is found for the invalid entry before the end of the database. */
         LatestSwareLogIndex = SwareLogIndex;

      }

   else  /* Initialize the SWARE LOG - Fill SWARE LOG with init values */
      {
      for (SwareLogIndex = 0; SwareLogIndex < MAX_SWARE_LOG_ENTRIES; SwareLogIndex++)
         {
         SwareLogDatabase[SwareLogIndex].error_kind = MAX_NUMBER_OF_ERROR_KINDS;
         SwareLogDatabase[SwareLogIndex].error_code = MAX_NUMBER_OF_ERROR_CODES;
         SwareLogDatabase[SwareLogIndex].error_caller = MAX_NUMBER_OF_ERROR_CALLERS;
         SwareLogDatabase[SwareLogIndex].error_request = MAX_NUMBER_OF_ERROR_REQUESTS;
         SwareLogDatabase[SwareLogIndex].line_number = 0;
         }
   
      /* Write initialized SWARE LOG to BATTRAM */
      SramStatus = BattramAccess(BATTRAM_WRITE_ACCESS,
                                SWARE_LOG_SECTION,
                                (BYTE *)SwareLogDatabase,
                                0,
                                sizeof(SwareLogDatabase)
                               );
        
      /* Set SwareLogIndex equal to 0 */  
      LatestSwareLogIndex = INITIAL_SWARE_LOG_INDEX;
      }

   return(SysStartupStatus);
   }  /* end of sware_log_hander_init */
