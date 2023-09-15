/* $Header:   K:\APPS\PVCS Pro\332\App\ERRORLOG.C_V   2.9   Apr 23 1999 09:58:30   ofingere  $ */
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

   Module name:  Error_Log_Handler

   Filename:     errorlog.c


            Written by: Mark Lazarewicz 
                  Date: 02/14/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            02/14/96      Mark L      Initial Version
      1            4/29/96       LAM         put <> around psos.h    
      2            11/22/96      LAM         chged q_send            
      3            01/29/97      LAM         made queues global      
      4.2.6        06/17/97      LAM         deleted nvmqid
      2.7/2.8      09.15.97      JBerman     Added default into the switch statement
	  2.9          04.23.99      OFI         Changed for DIAB

 ------------------------------- DESCRIPTION -----------------------------------

   This library routine is called by manage_errors and diagnostic_manager to log
   welder errors.

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ LOCAL EQUATES ----------------------------------

 ------------------------------- EXPORT DATA -----------------------------------

 ------------------------------- IMPORT DATA -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/
                                                                    
#include "root.h"           
#include <psos.h>                  /* psos defines and prototypes, etc.      */
#include "names.h"                 /* psos object defines                    */
#include "errorlog.h"
#include "managerr.h"
#include <prepc.h>
#include "opcodes.h"
#include "battram.h"
#include "swarelog.h"              /* defines for the software error log     */
#include "ck_qsend.h"           /* contains function interface           */

/* Outgoing messages */
#include "nvm_msg.h"

/*
 ------------------------------ EXTERNAL DATA ----------------------------------

 ------------------------------ LOCAL DEFINES ----------------------------------
*/
 
#define LAST_ERROR_WRITTEN               UNKNOWN_ERROR_KIND /* Invalid error kind value used for MARKER */
#define ERROR_LOG_GROUP_SIZE             20                 /* 20 entries at a time requested */
#define INITIAL_ERROR_LOG_INDEX          0
#define MAX_ERROR_LOG_INDEX              127                /* The error log index goes from 0 to 127 */
#define MAX_ERROR_COUNT                  0xFFFF


/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------

 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
*/

/* CREATE THE ERROR LOG DATABASE */
static ERROR_LOG_DATABASE_TYPE     ErrorLogDatabase;

static ERROR_LOG_DATABASE_TYPE     *ErrorLogSegAddr;     /* pointer assigned to BEGINNING of segment */
static UINT8                       LatestErrorLogIndex;  /* indicates the latest filled index in the log */
static BOOLEAN                     DatabaseFull;           /* Indicates if the error log database is full */


/*
 ---------------------- PRIVATE SUBROUTINES REFERENCED --------------------------
*/
                              
static ERROR_LOG_STATUS_TYPE CopyErrorLogGroup(
   ERROR_LOG_GROUP_NUMBER_TYPE  error_log_group_number,
   ERROR_LOG_BYTE_COUNT_TYPE    *error_log_byte_count
   );

static void ClearErrorLog(void);

/*
 ---------------------------------- CODE ---------------------------------------
*/

ERROR_LOG_STATUS_TYPE ErrorLogHandler(
   ERROR_LOG_REQUEST_TYPE        error_log_request,
   ERROR_KIND_TYPE               error_kind,
   ERROR_CODE_TYPE               error_code,
   ERROR_CALLER_TYPE             error_caller,
   ERROR_REQUEST_TYPE            error_request,
   C_LINE_NUMBER_TYPE            line_number,
   ERROR_LOG_DATABASE_TYPE       **error_log_return_data_ptr,
   ERROR_LOG_BYTE_COUNT_TYPE     *error_log_byte_count
   )
   {
   ERROR_LOG_STATUS_TYPE  ErrorLogStatus =
                          ERROR_LOG_PROCESSING_OK; /* initialize ruturn value */ 

   NVM_ACCESS_MSG   NvmAccessMsg; 
   SINT8                LogIndex;  
   UINT8                ErrorLogIndex;                 
   UINT8                ErrorLogStartIndex;
   UINT8                ErrorLogEndIndex;
   ERROR_LOG_DATA_TYPE  *CurrentSegAddr; 


   switch(error_log_request)
      {
      
      case WRITE_ERROR_LOG:
         /*
          * Write the error into the local copy of the error log database
          */
         ErrorLogIndex = ErrorLogWriteEntry( error_kind,
                                                  error_code,
                                                  error_caller,
                                                  error_request,
                                                  line_number );
         /*
          * Slots in the error log database are consumed in consecutive order. Keep
          * track of the highest entry used.
          */
         if ( LatestErrorLogIndex < (ErrorLogIndex + 1) )
            {
            LatestErrorLogIndex = ErrorLogIndex + 1;
            }

         /* Form and send message to NVM queue to write to SRAM.*/
         NvmAccessMsg.common.opcode       = OP_BATTRAM_WRITE_ERROR_LOG;
         NvmAccessMsg.common.pointer_flag = NO_DATA_PTR;
         NvmAccessMsg.common.source_task  = DIAG_SOURCE_TASK;
         NvmAccessMsg.data_pointer        = (BYTE *)(&ErrorLogDatabase[ErrorLogIndex]);
         NvmAccessMsg.offset              = (sizeof(ERROR_LOG_DATA_TYPE))*(ErrorLogIndex);
         NvmAccessMsg.byte_count          = sizeof(ERROR_LOG_DATA_TYPE);

//         CkQSend (NvmmQid,&NvmAccessMsg,ERROR_LOG_HANDLER,
//                 __LINE__,MILLS_TO_TICKS(50));   /* 50 ms        */
               
         break;

      case READ_ALL_ERRORS_IN_ERROR_LOG:
          
         if (DatabaseFull == TRUE)
            {
            /* Copy the error log entries into the assigned segment in REVERSE order */

            ErrorLogStartIndex = MAX_ERROR_LOG_INDEX;     /* Start copying from index 127 */     
            ErrorLogEndIndex   = INITIAL_ERROR_LOG_INDEX; /* Till index 0 in reverse order */

            for(LogIndex = ErrorLogStartIndex,
                CurrentSegAddr = (ERROR_LOG_DATA_TYPE *)ErrorLogSegAddr;
                LogIndex >= ErrorLogEndIndex;
                LogIndex--, CurrentSegAddr++)
            {
                memcpy (CurrentSegAddr,
                        &ErrorLogDatabase[LogIndex],
                        sizeof(ERROR_LOG_DATA_TYPE));
            }

            /* Set the error_log_byte_count equal to the size of the database */
            *error_log_byte_count = sizeof(ERROR_LOG_DATABASE_TYPE);
            }
         
         else if ( LatestErrorLogIndex == INITIAL_ERROR_LOG_INDEX)  /* When the database is empty , return a bad status */
            {
            ErrorLogStatus = ERROR_LOG_PROCESSING_NOT_OK;
        
            /* Set the byte count to 0 */
            *error_log_byte_count =  0;
            }

         else  /* when the database is partially filled, return only that portion */
            {

            ErrorLogStartIndex = LatestErrorLogIndex - 1;
            ErrorLogEndIndex   = INITIAL_ERROR_LOG_INDEX;

            for(LogIndex = ErrorLogStartIndex,
                CurrentSegAddr = (ERROR_LOG_DATA_TYPE *)ErrorLogSegAddr;
                LogIndex >= ErrorLogEndIndex;
                LogIndex--, CurrentSegAddr++)

               {
                memcpy (CurrentSegAddr,
                        &ErrorLogDatabase[LogIndex],
                        sizeof(ERROR_LOG_DATA_TYPE));
               }

            /* Set the error_log_data_count equal to the size one entry in the database times the number
             * of valid entries.
             */
            *error_log_byte_count = sizeof(ERROR_LOG_DATA_TYPE) * (LatestErrorLogIndex);
            }
            
         /* Set the return data pointer equal to the buffer pointer */
         *error_log_return_data_ptr = ErrorLogSegAddr; 

         break;

     /*
      * THE FOLLOWING NOTE APPLIES TO THE NEXT FOUR CASES:
      *
      * NOTE: - error_log_group_number specifies the particular group of 20 consecutive errors in the log:
      *    GROUP_NUMBER_ONE: latest 20 entries (1-20)
      *    GROUP_NUMBER_TWO: 20 entries past the latest 20 entries (21-40)
      *    GROUP_NUMBER_THREE: 20 entries past the latest 40 entries (41-60) 
      *    GROUP_NUMBER_FOUR: 20 entries past the latest 60 entries (61-80) 
      */

      case READ_ERR_LOG_ENTRIES_1_20:  /* Request for the 20 latest entry */
          
         /* Check to see if the database is empty.  If it is then return a bad status. */
         
         if (LatestErrorLogIndex == INITIAL_ERROR_LOG_INDEX)
            {
            ErrorLogStatus = ERROR_LOG_PROCESSING_NOT_OK;

            /* Set the byte count to 0 */
            *error_log_byte_count =  0;
            }

         else
            {

            /* Call copy_error_log_group with the error_log_group_number and a pointer,
             * error_log_byte_count. 
             *
             * NOTE: This function will pass back: the status of the call,
             *       ErrorLogSegAddr (a pointer to the BEGINNING  of segment containing the return data), 
             *       and the error_log_byte_count.
             */ 
            ErrorLogStatus = CopyErrorLogGroup (GROUP_NUMBER_ONE,
                                                     error_log_byte_count);
        
            /* Set the return data pointer equal to the buffer pointer */
            *error_log_return_data_ptr = ErrorLogSegAddr; 
            }
         break;

      case READ_ERR_LOG_ENTRIES_21_40: 

         /* Request for 20 entries past the latest 20 entries */

         /* Check to see if the database is empty.  If it is then return a bad 
          * status.
          */
         if (LatestErrorLogIndex == INITIAL_ERROR_LOG_INDEX)
            {
            ErrorLogStatus = ERROR_LOG_PROCESSING_NOT_OK;

            /* Set the byte count to 0 */
            *error_log_byte_count =  0;
            }

         else
            {

            /* Call copy_error_log_group with the error_log_group_number and a pointer,
             * error_log_byte_count. 
             *
             * NOTE: This function will pass back: the status of the call,
             *       ErrorLogSegAddr (a pointer to the BEGINNING of segment containing the return data), 
             *       and the error_log_byte_count.
             */ 
            ErrorLogStatus = CopyErrorLogGroup (GROUP_NUMBER_TWO,
                                                     error_log_byte_count);

            /* Set the return data pointer equal to the buffer pointer */
            *error_log_return_data_ptr = ErrorLogSegAddr; 
            }

         break;

      case READ_ERR_LOG_ENTRIES_41_60: 

         /* Request for 20 entries pas the latest 40 entries */

         /* Check to see if the database is empty.  If it is then return a bad
          * status. 
          */

         if (LatestErrorLogIndex == INITIAL_ERROR_LOG_INDEX)
            {
            ErrorLogStatus = ERROR_LOG_PROCESSING_NOT_OK;
   
            /* Set the byte count to 0 */
            *error_log_byte_count =  0;
            }

         else
            {

            /* Call copy_error_log_group with the error_log_group_number and a pointer,
             * error_log_byte_count. 
             *
             * NOTE: This function will pass back: the status of the call,
             *       ErrorLogSegAddr (a pointer to the BEGINNING of segment containing the return data), 
             *       and the error_log_byte_count.
             */ 
            ErrorLogStatus = CopyErrorLogGroup (GROUP_NUMBER_THREE,
                                                     error_log_byte_count);

            /* Set the return data pointer equal to the buffer pointer */
            *error_log_return_data_ptr = ErrorLogSegAddr; 
            }

         break;

      case READ_ERR_LOG_ENTRIES_61_80:
         
         /* Request for 20 entires past the latest 60 entries */

         /* Check to see if the database is empty.  If it is then return a bad
          * status.
          */

         if (LatestErrorLogIndex == INITIAL_ERROR_LOG_INDEX)
            {
            ErrorLogStatus = ERROR_LOG_PROCESSING_NOT_OK;

            /* Set the byte count to 0 */
            *error_log_byte_count =  0;
            }

         else
            {

            /* Call copy_error_log_group with the error_log_group_number and a pointer,
             * error_log_byte_count. 
             *
             * NOTE: This function will pass back: the status of the call,
             *       ErrorLogSegAddr (a pointer to the BEGINNING of segment containing the return data), 
             *       and the error_log_byte_count.
             */ 

            ErrorLogStatus = CopyErrorLogGroup (GROUP_NUMBER_FOUR,
                                                        error_log_byte_count);
            /* Set the return data pointer equal to the buffer pointer */
            *error_log_return_data_ptr = ErrorLogSegAddr; 
            }

         break;

      case CLEAR_ERROR_LOG:
         
         ClearErrorLog();

         NvmAccessMsg.common.opcode       = OP_BATTRAM_WRITE_ERROR_LOG;
         NvmAccessMsg.common.pointer_flag = NO_DATA_PTR;
         NvmAccessMsg.common.source_task =  DIAG_SOURCE_TASK;
         NvmAccessMsg.data_pointer        = (BYTE *)ErrorLogDatabase;
         NvmAccessMsg.offset              = 0;
         NvmAccessMsg.byte_count          = sizeof(ERROR_LOG_DATABASE_TYPE);

         LatestErrorLogIndex = INITIAL_ERROR_LOG_INDEX;
 
//         CkQSend (NvmmQid,&NvmAccessMsg,ERROR_LOG_HANDLER,
//                 __LINE__,MILLS_TO_TICKS(50));   /* 50 ms        */
         break;

      default:
         break;

      } /* END SWITCH */
   
   return(ErrorLogStatus);
   }

/* ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:     Error_Log_Handler    

   Filename:        errorlog.c    

   Function name:   CopyErrorLogGroup


            Written by: Mark Lazarewicz
                  Date: 02/14/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            02/14/96      Mark L      Initial Version
 
 ------------------------------- DESCRIPTION -----------------------------------

 This function copies the error log in fixed sizes of GROUP_SIZE.

 ------------------------------- PSEUDO CODE -----------------------------------
                                                                          

 ---------------------------------- CODE ---------------------------------------
*/  
static ERROR_LOG_STATUS_TYPE CopyErrorLogGroup(
   ERROR_LOG_GROUP_NUMBER_TYPE  error_log_group_number,
   ERROR_LOG_BYTE_COUNT_TYPE    *error_log_byte_count
   )
   {      
   ERROR_LOG_STATUS_TYPE  ErrorLogStatus = ERROR_LOG_PROCESSING_OK;
   SINT8                  ErrorLogIndex;                 
   SINT8                  ErrorLogStartIndex;
   SINT8                  ErrorLogEndIndex;
   ERROR_LOG_DATA_TYPE    *CurrentSegAddr;              /* Pointer to keep track of current location in ErrorLogSegAddr */
 
   /* NOTE: - LatestErrorLogIndex is the latest entry into the error log.
    *       - ERROR_LOG_GROUP_SIZE is 20 entries.
    *       - error_log_group_number specifies the particular group of 20 consecutive errors in the log:
    *
    *   GROUP 1: latest 20 entries (1-20)
    *   GROUP 2: 20 entries past the latest 20 entries (21-40)
    *   GROUP 3: 20 entries past the latest 40 entries (41-60) 
    *   GROUP 4: 20 entries past the latest 60 entries (61-80) 
    */

   /* Calculate the start and the end indices of the group to copy */
   ErrorLogStartIndex = (LatestErrorLogIndex - 1) - ((ERROR_LOG_GROUP_SIZE)*(error_log_group_number - 1));
   ErrorLogEndIndex   = (LatestErrorLogIndex) - ((ERROR_LOG_GROUP_SIZE)*(error_log_group_number));

   /* if both the indices are > 0, copy the error log entries into the assigned segment in REVERSE order */
   if (ErrorLogStartIndex >= 0 && ErrorLogEndIndex >= 0)
      {
      for(ErrorLogIndex = ErrorLogStartIndex,
          CurrentSegAddr = (ERROR_LOG_DATA_TYPE *)ErrorLogSegAddr;
          ErrorLogIndex >= ErrorLogEndIndex; 
          ErrorLogIndex--, CurrentSegAddr++)
         {
         memcpy (CurrentSegAddr, 
                 &ErrorLogDatabase[ErrorLogIndex],
                 sizeof(ERROR_LOG_DATA_TYPE));    
         }

      /* Assign the byte count */
      *error_log_byte_count =  sizeof(ERROR_LOG_DATA_TYPE) * ERROR_LOG_GROUP_SIZE;
      }
  
   else if (ErrorLogStartIndex >= 0 && ErrorLogEndIndex < 0)
      {
      /* Check to see if the database is full */

      if (DatabaseFull == TRUE)
         {

         /* Add MAX_ERROR_LOG_ENTRIES to the ErrorLogEndIndex to loop around the database*/
         ErrorLogEndIndex = MAX_ERROR_LOG_ENTRIES + ErrorLogEndIndex; 
          
         /* Copy the error log entries in 2 groups in REVERSE order. */
         /* First group: copy all entries starting from the start index to 0 REVERSE order. */
         for(ErrorLogIndex = ErrorLogStartIndex,
             CurrentSegAddr = (ERROR_LOG_DATA_TYPE *)ErrorLogSegAddr;
             ErrorLogIndex >= 0; 
             ErrorLogIndex --, CurrentSegAddr++)
            {
            memcpy (CurrentSegAddr, 
                    &ErrorLogDatabase[ErrorLogIndex],
                    sizeof(ERROR_LOG_DATA_TYPE));    
            }
  
         /* Second group: Copy all entries starting from entry 127 to the end index in REVERSE order. */
         for (ErrorLogIndex = MAX_ERROR_LOG_ENTRIES - 1;
              ErrorLogIndex >= ErrorLogEndIndex;
              ErrorLogIndex --, CurrentSegAddr++)
            {
            memcpy (CurrentSegAddr, 
                    &ErrorLogDatabase[ErrorLogIndex],
                    sizeof(ERROR_LOG_DATA_TYPE));    
            }

         /* Assign the byte count */
         *error_log_byte_count =  sizeof(ERROR_LOG_DATA_TYPE) * (ERROR_LOG_GROUP_SIZE);
         }

      else  /* if the database is not full then copy all valid entries - latest entry  to 0 in REVERSE order. */
         {
         for(ErrorLogIndex = ErrorLogStartIndex,
             CurrentSegAddr = (ERROR_LOG_DATA_TYPE *)ErrorLogSegAddr;
             ErrorLogIndex >= 0; 
             ErrorLogIndex --,CurrentSegAddr++)
            {
            memcpy (CurrentSegAddr, 
                    &ErrorLogDatabase[ErrorLogIndex],
                    sizeof(ERROR_LOG_DATA_TYPE));    
            }

         /* Assign the byte count */
         *error_log_byte_count =  sizeof(ERROR_LOG_DATA_TYPE) * (ErrorLogStartIndex + 1);
         }
          
      } /*END else if (ErrorLogStartIndex >= 0 && ErrorLogEndIndex < 0) */

   else if ( ErrorLogStartIndex < 0 && ErrorLogEndIndex < 0)
      {
   
      if (DatabaseFull == TRUE)
         {
         /* Add MAX_ERROR_LOG_ENTRIES to the ErrorLogEndIndex to loop around the database*/
         /* Add MAX_ERROR_LOG_ENTRIES to the ErrorLogStartIndex to loop around the database*/
         ErrorLogEndIndex = MAX_ERROR_LOG_ENTRIES + ErrorLogEndIndex; 
         ErrorLogStartIndex = MAX_ERROR_LOG_ENTRIES + ErrorLogStartIndex; 
          
         /* Copy the error log entries into the assigned segment in REVERSE order. */
         for(ErrorLogIndex = ErrorLogStartIndex,
             CurrentSegAddr = (ERROR_LOG_DATA_TYPE *)ErrorLogSegAddr;
             ErrorLogIndex >= ErrorLogEndIndex; 
             ErrorLogIndex--,CurrentSegAddr++)
            {
            memcpy(CurrentSegAddr, 
                   &ErrorLogDatabase[ErrorLogIndex],
                   sizeof(ERROR_LOG_DATA_TYPE));    
            }

         /* Assign the byte count */
         *error_log_byte_count =  sizeof(ERROR_LOG_DATA_TYPE) * ERROR_LOG_GROUP_SIZE;
         }

      else  /* if the database is NOT full then return a bad status */
         {
         ErrorLogStatus = ERROR_LOG_PROCESSING_NOT_OK;

         /* Set the byte count to 0 */
         *error_log_byte_count =  0;
         }

      } /* END else if ( ErrorLogStartIndex < 0 && ErrorLogEndIndex < 0) */

   else
      {
      /* if none of the above conditions are satisfied, return a bad status */
      ErrorLogStatus = ERROR_LOG_PROCESSING_NOT_OK;

      /* Set the byte count to 0 */
      *error_log_byte_count =  0;
      }
 
   return (ErrorLogStatus);

   } /* END of CopyErrorLogGroup */

/* ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:     Error_Log_Handler    

   Filename:        errorlog.c    

   Function name:   ErrorLogHandlerInit

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            02/14/96      Mark L      Initial Version

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

SYS_STARTUP_STATUS_TYPE ErrorLogHandlerInit(
   void )
   {      
   SYS_STARTUP_STATUS_TYPE  SysStartupStatus = SYS_STARTUP_PASS;

   UINT32                    PsosStatus;
   UINT32                    PsosRegionId;
   BATTRAM_ACCESS_STATUS_TYPE   SramStatus;


   DatabaseFull = FALSE;

   if (PsosStatus != PSOS_OK )
      SysStartupStatus = SYS_STARTUP_FAIL;

   /* Identify REGION 0 */
   PsosStatus = rn_ident(ROOT_REGION_ZERO_NAME, &PsosRegionId);
 
   LOG_PSOS_ERROR(PsosStatus, ERROR_LOG_HANDLER);

   if (PsosStatus != PSOS_OK )
      SysStartupStatus = SYS_STARTUP_FAIL;

   if (SysStartupStatus == SYS_STARTUP_PASS)
      {
      /* Get some memory from REGION 0 */
      PsosStatus = rn_getseg(PsosRegionId,
                              (sizeof (ERROR_LOG_DATABASE_TYPE)),
                              RN_NOWAIT,
                              RN_WAIT_FOREVER,
                              (void *)&ErrorLogSegAddr);

      LOG_PSOS_ERROR(PsosStatus, ERROR_LOG_HANDLER);

      if (PsosStatus != PSOS_OK )
         SysStartupStatus = SYS_STARTUP_FAIL;
      }

   /* ADD INIT ROUTINE TO HANDLE DATABASE COPY OF THE LOG AT STARTUP */
   SramStatus = BattramAccess(BATTRAM_READ_ACCESS,
                             ERROR_LOG_SECTION,
                             (BYTE *)ErrorLogDatabase,
                             0,
                             sizeof(ERROR_LOG_DATABASE_TYPE)
                             );


   if (SramStatus == BATTRAM_ACCESS_STATUS_OK)
      {
      /*
       * SEARCH FOR THE LAST ERROR THAT WAS WRITTEN INTO SRAM (MARKER) BEFORE STATION WENT DOWN
       */
      for(LatestErrorLogIndex = 0; 
          LatestErrorLogIndex < MAX_ERROR_LOG_ENTRIES; 
          LatestErrorLogIndex++)
         {
         if ( ErrorLogDatabase[LatestErrorLogIndex].error_kind == LAST_ERROR_WRITTEN)
            {
            break;
            }
         }

      /*
       * If we use the final entry in the error log database then set a flag indicating that
       * the database is full
       */
      if ( LatestErrorLogIndex == MAX_ERROR_LOG_ENTRIES )
         {
         DatabaseFull = TRUE;
         }
      }
   else  
      
      /* if database is corrupt, initialize the ERROR LOG by filling it with init values */
      {
      ClearErrorLog();

      /* Write initialized ERROR LOG to SRAM */
      BattramAccess(BATTRAM_WRITE_ACCESS,
                  ERROR_LOG_SECTION,
                  (BYTE *)ErrorLogDatabase,
                  0,
                  sizeof(ERROR_LOG_DATABASE_TYPE)
                 );

      /* Log a sware error */
      SwareLogHandler(WRITE_SWARE_LOG,
                        SWARE,
                        E_BATTRAM_READ_FAULT,
                        ERROR_LOG_HANDLER,
                        LOG_ERROR,
                        __LINE__,
                        (SWARE_LOG_DATABASE_TYPE **) NULL,
                        (SWARE_LOG_BYTE_COUNT_TYPE *) NULL
                       );

      } /* END ELSE */

   return(SysStartupStatus);
   }  /* end of ErrorLogHanderInit */


/* ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:     Error_Log_Handler    

   Filename:        errorlog.c    

   Function name:   ClearErrorLog

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
  ------------------------------- DESCRIPTION -----------------------------------
      0            02/15/96      Mark L      Initial Version

 ------------------------------- PSEUDO CODE -----------------------------------
                                                                          
 initialize error log database to startup states/values

 ---------------------------------- CODE ---------------------------------------
*/  

static void ClearErrorLog( void )
   {      
   UINT16                    ErrorLogIndex;

   for(ErrorLogIndex = 0; 
       ErrorLogIndex < MAX_ERROR_LOG_ENTRIES; 
       ErrorLogIndex++)
      {
      ErrorLogDatabase[ErrorLogIndex].error_kind    = LAST_ERROR_WRITTEN;
      ErrorLogDatabase[ErrorLogIndex].error_code    = MAX_NUMBER_OF_ERROR_CODES;
      ErrorLogDatabase[ErrorLogIndex].error_caller  = MAX_NUMBER_OF_ERROR_CALLERS;
      ErrorLogDatabase[ErrorLogIndex].error_request = MAX_NUMBER_OF_ERROR_REQUESTS;
      ErrorLogDatabase[ErrorLogIndex].line_number   = 0;
      ErrorLogDatabase[ErrorLogIndex].error_count   = 0;
      }


   /* Set ErrorLogIndex equal to INITIAL_ERROR_LOG_INDEX */  
   LatestErrorLogIndex = INITIAL_ERROR_LOG_INDEX;

   /* The database is definately NOT full                  */
   DatabaseFull = FALSE;

   return;
   }


/* ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:     Error_Log_Handler    

   Filename:        errorlog.c    

   Function name:   ErrorLogWriteEntry

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------
      0            02/15/96      Mark L      Initial Version

 ------------------------------- PSEUDO CODE -----------------------------------
                                                                          
 Write one entry into the error log database. Note that this function does NOT
 write data into NVRAM... only into the local copy of the database.

 ---------------------------------- CODE ---------------------------------------
*/
UINT16 ErrorLogWriteEntry (
   ERROR_KIND_TYPE               error_kind,
   ERROR_CODE_TYPE               error_code,
   ERROR_CALLER_TYPE             error_caller,
   ERROR_REQUEST_TYPE            error_request,
   C_LINE_NUMBER_TYPE            line_number )

   {
   UINT16                        ErrorLogIndex;
   UINT32                        PsosStatus;
   UINT32                        ticks;                   /* the ticks parameter for tm_get */

   for (ErrorLogIndex = 0;
       (ErrorLogIndex < MAX_ERROR_LOG_ENTRIES); 
        ErrorLogIndex++)
      {     
      /*
       * See if we have come to an empty entry. Since we consume the entries consecutively
       * this will be the next entry to use.
       */
      if ( ErrorLogDatabase[ErrorLogIndex].error_kind == LAST_ERROR_WRITTEN)
         {
         break;
         }

      /* Look for a match */
      if ((ErrorLogDatabase[ErrorLogIndex].error_kind    == error_kind) &&
          (ErrorLogDatabase[ErrorLogIndex].error_code    == error_code) &&
          (ErrorLogDatabase[ErrorLogIndex].error_caller  == error_caller) &&
          (ErrorLogDatabase[ErrorLogIndex].error_request == error_request) &&
          (ErrorLogDatabase[ErrorLogIndex].line_number   == line_number))   
         {
         break;
         }
      }

   /*
    * If we use the final entry in the error log database then set a flag indicating that
    * the database is full
    */
   if ( ErrorLogIndex == MAX_ERROR_LOG_INDEX )
      {
      DatabaseFull = TRUE;
      }

   /*
    * If the error log database is full and this error doesn't match a prior entry
    * (i.e. we went through the entire database a didn't find an empty or a match)
    * then write over the oldest entry
    */
   if ( ErrorLogIndex == MAX_ERROR_LOG_ENTRIES )
      {
      ErrorLogIndex = 0;

      ErrorLogDatabase[ErrorLogIndex].error_count = 0;
      }
      
   /*
    * Don't let the error count roll-over. If we reach the maximum then
    * stop incrementing.
    */
   if (ErrorLogDatabase[ErrorLogIndex].error_count < MAX_ERROR_COUNT)
      {
      ErrorLogDatabase[ErrorLogIndex].error_count++;   
      }

   /* Fill the ErrorLogDatabase with the correct values */ 
   ErrorLogDatabase[ErrorLogIndex].error_kind    = error_kind;
   ErrorLogDatabase[ErrorLogIndex].error_code    = error_code;
   ErrorLogDatabase[ErrorLogIndex].error_caller  = error_caller;
   ErrorLogDatabase[ErrorLogIndex].error_request = error_request;
   ErrorLogDatabase[ErrorLogIndex].line_number   = line_number;

   /* get system date and time */
  /* PsosStatus = tm_get(&ErrorLogDatabase[ErrorLogIndex].last_date,
                        &ErrorLogDatabase[ErrorLogIndex].last_time,
                        &ticks);          /* ignore the ticks */

   LOG_PSOS_ERROR(PsosStatus, ERROR_LOG_HANDLER);


   return ErrorLogIndex;
   }




/* ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:     Error_Log_Handler    

   Filename:        errorlog.c    

   Function name:   ErrorLogEmergencySave

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            02/14/96      Mark L      Initial Version
 
 ------------------------------- DESCRIPTION -----------------------------------

 ------------------------------- PSEUDO CODE -----------------------------------
                                                                          
 Write saves the designated entries from the local copy of the error log database
 into the ERROR_LOG_SECTION of SRAM using a direct call to BattramAccess rather than
 sending a message to the nvm_manager.

 THIS FUNCTION SHOULD ONLY BE USED IN THE CASE OF A SYSTEM FAILURE. THE CALLER MUST
 BE THE HIGHEST PRIORITY TASK TO AVOID POTENTIAL CONFLICT WITH THE NVM_MANAGER.

 ---------------------------------- CODE ---------------------------------------
*/

void ErrorLogEmergencySave(
   UINT16                        ErrorLogIndex,
   UINT16                        number_of_entries )

   {
   /*
    * Write error log entries into SRAM
    */ 
   BattramAccess(BATTRAM_WRITE_ACCESS,
               ERROR_LOG_SECTION,
               (BYTE *)&ErrorLogDatabase[ErrorLogIndex],
               0,
               number_of_entries * sizeof(ERROR_LOG_DATA_TYPE) );
   return;
   }



