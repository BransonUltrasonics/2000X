/* $Header:   K:\APPS\PVCS Pro\332\App\DIAGNOSE.C_V   2.8   Apr 23 1999 09:47:38   ofingere  $ */
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
/* ---------------------- MODULE DESCRIPTION -------------------------------

   Module name:  Diagnostics_Manager

   Filename:     diagnose.c


            Written by: Mark Lazarewicz 
                  Date: 1/31/96 
              Language:  "C"

 ---------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            01/31/96      Mark L      Initial version
      1            03/28/96      Mark L      SwareLog response sent to RSCH
      2            07/06/96      LAM         cleanup warnings
      3            12/04/96      LAM         cleanup warnings
      4            04/04/97      LAM         cleanup         
      5.2.7        07-07-97      LAM         deleted psos_tbl.h
      2.8          04-23-99      OFI         Changed for DIAB                      
 ------------------------------- DESCRIPTION -------------------------------
    This task processes messages associated with the Diagnostics Manager.

  

 ------------------------------- PSEUDO CODE -------------------------------

 
 ------------------------------ LOCAL EQUATES ------------------------------
*/




/*
 ------------------------------- EXPORT DATA --------------------------------

 ------------------------------- IMPORT DATA ------------------------------
   



 ------------------------------ INCLUDE FILES ------------------------------
*/
                                                                    
#include <psos.h>                      /* psos defines and prototypes, etc..     */
#include "names.h"                     /* psos object defines                    */
#include "opcodes.h"                   /* defines msg opcodes                    */
#include "obj_tabl.h"
#include "managerr.h"
#include "id_type.h"
#include "ipsatype.h"

/* defines for READ_SWARE_LOG_ENTRIES  */
#include "err_data.h"
#include "errorlog.h"

/* expected incoming messages */
#include "genrlmsg.h"
#include "err_msg.h"
#include "read_log.h"
#include "clearmsg.h"

/* expected outgoing messages */
#include "read_msg.h"

/* function prototype 
#include "diagnose.h" */

/* function interfaces */
#include "swarelog.h"         /* defines for the software error log */
#include "ck_qsend.h" 

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/
extern ULONG RschQid;   

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/

/* this union is comprised of the expected messages that will be sent */
/*  to this task */

typedef union
   {
   GENERIC_MSG            generic_msg;
   MANAGE_ERRORS_MSG      manage_errors_msg;
   READ_LOG_MSG           read_log_msg;
   CLEAR_LOG_MSG          clear_log_msg;
  } DIAGNOSTICS_MESSAGE_TYPE;




void ProcessErrorMsg(
   MANAGE_ERRORS_MSG                       *manage_errors_msg_ptr );
   
/*
 ---------------------------- PRIVATE GLOBAL DATA ------------------------------
*/

/*
 ------------------------------- LOCAL DATA ------------------------------------
*/
static UINT32                              ErrorThrottle;
static UINT32                              DiagQid;

/*
 ---------------------- IMPORT SUBROUTINES REFERENCED --------------------------
                              
 ---------------------------------- CODE ---------------------------------------
*/
void DiagnosticsManager(
   void
   )
   {
   /*---------------------------------------------------------------*/   
   /*            Define and Initialize Local Variables              */
   /*---------------------------------------------------------------*/

   SWARE_LOG_DATABASE_TYPE                 *SwareLogReturnDataPtr;

   ERROR_KIND_TYPE                         ErrorKind;
   ERROR_CODE_TYPE                         ErrorCode;
   ERROR_CALLER_TYPE                       ErrorCaller;
   ERROR_REQUEST_TYPE                      ErrorRequest;
   C_LINE_NUMBER_TYPE                      LineNumber;

   DIAGNOSTICS_MESSAGE_TYPE                DiagMsg;        /* target for q_receive   */
   UINT32                                  PsosStatus;

   READ_SWARE_LOG_RESPONSE_MSG             ReadSwareLogResponseMsg;


   /*--------------n------------------------------*/
   /*    Request Incoming MSG DIAG queue id      */
   /*--------------------------------------------*/
   PsosStatus = q_ident(DIAG_Q, Q_NODE_0, &DiagQid);

   /* If the queue id is not there then RESET ! */
   if (PsosStatus != PSOS_OK) 
      MANAGE_ERRORS(PSOS, PsosStatus, DIAGNOSTICS_MANAGER, RESET_WELDER);

   /* If the queue id is not there then RESET ! */
   if (PsosStatus != PSOS_OK) 
      MANAGE_ERRORS(PSOS, PsosStatus, DIAGNOSTICS_MANAGER, RESET_WELDER);
 
   /*--------------------------------------------*/
   /* Set the error throttle to 10 ticks. We're  */
   /* using a variable to facilitate tests with  */
   /* XRAY and the emulator                      */
   /*--------------------------------------------*/
   ErrorThrottle = 10;

   /*--------------------------------------------*/
   /*    Process Diagnostics information         */
   /*--------------------------------------------*/

   while (TRUE)
      {
      /* wait on msg queue */ 
      PsosStatus = q_receive(DiagQid, Q_WAIT, Q_WAIT_FOREVER, &DiagMsg);

      /* Log any software errors */
      LOG_PSOS_ERROR(PsosStatus, DIAGNOSTICS_MANAGER);

      if (PsosStatus == PSOS_OK)
         {

         switch( DiagMsg.generic_msg.common.opcode)  
            {
         
            case OP_MANAGE_ERRORS_MSG:         
               ProcessErrorMsg( &DiagMsg.manage_errors_msg );         
               break;
         
         
            case OP_READ_LOG:           /* this is a msg to read one of the error logs */
               switch (DiagMsg.read_log_msg.ips_command_id)
                  {
                  case READ_SWARE_LOG_ENTRIES:
               
                     /* Call the SWARE error log to read SWARE log entries */
                     /* Note that the error_kind, error_code, error_caller,*/ 
                     /* error_request, and line_number will be ignored by the sware log handler*/
                     LineNumber   = 0;
         
                     SwareLogHandler(READ_SWARE_LOG,
                                       UNKNOWN_ERROR_KIND,
                                       E_NO_ERROR,
                                       DIAGNOSTICS_MANAGER,
                                       MAX_NUMBER_OF_ERROR_REQUESTS,
                                       LineNumber,
                                       &SwareLogReturnDataPtr,
                                       &ReadSwareLogResponseMsg.byte_count
                                       );
               
                     /* Form the message, OP_READ_SWARE_LOG_RESPONSE with the */
                     /* sware_log_return_data_ptr and send to MICH queue      */   
               
                     ReadSwareLogResponseMsg.common.opcode       = OP_READ_SWARE_LOG_RESPONSE;
                     ReadSwareLogResponseMsg.common.pointer_flag = DATA_PTR_NO_DEALLOC;
                     ReadSwareLogResponseMsg.common.source_task  = DIAG_SOURCE_TASK;
                     ReadSwareLogResponseMsg.sware_log_info_ptr  = SwareLogReturnDataPtr;
                     ReadSwareLogResponseMsg.ips_command_id      = READ_SWARE_LOG_ENTRIES;
               
                     /* assign cib info */
//                     ReadSwareLogResponseMsg.cib_info = DiagMsg.read_log_msg.cib_info;
               
                     CkQSend(RschQid,                            /* Queue to send message to   */ 
                               &ReadSwareLogResponseMsg,         /* Address of message buffer  */
                               DIAGNOSTICS_MANAGER,              /* Caller Identifier          */
                               __LINE__, 
                               MILLS_TO_TICKS(100));

                     break;

//                    case LIST_ALL_ALARM_IDS:
//                  case READ_ENTIRE_ERROR_LOG:
//                  case READ_ERROR_LOG_ENTRIES_1_20:
//                  case READ_ERROR_LOG_ENTRIES_21_40:
//                  case READ_ERROR_LOG_ENTRIES_41_60:
//                  case READ_ERROR_LOG_ENTRIES_61_80:
//         
//                     switch (DiagMsg.read_log_msg.ips_command_id)
//                        {
//         
//                        case READ_ENTIRE_ERROR_LOG:
//                           ErrorLogHandlerRequest  = READ_ALL_ERRORS_IN_ERROR_LOG;
//         
                           /* Assign the ips_command_id for the response msg.*/
//                           ReadErrorLogResponseMsg.ips_command_id  = READ_ENTIRE_ERROR_LOG;
//                           break;
//         
//                        case READ_ERROR_LOG_ENTRIES_1_20:
//                           ErrorLogHandlerRequest  = READ_ERR_LOG_ENTRIES_1_20;
//         
                           /* Assign the ips_command_id for the response msg.*/
//                           ReadErrorLogResponseMsg.ips_command_id  = READ_ERROR_LOG_ENTRIES_1_20;
//                           break;
//                         
//                        case READ_ERROR_LOG_ENTRIES_21_40:
//                           ErrorLogHandlerRequest  = READ_ERR_LOG_ENTRIES_21_40;
//         
                           /* Assign the ips_command_id for the response msg.*/
//                           ReadErrorLogResponseMsg.ips_command_id  = READ_ERROR_LOG_ENTRIES_21_40;
//                           break;
//                         
//                        case READ_ERROR_LOG_ENTRIES_41_60:
//                           ErrorLogHandlerRequest  = READ_ERR_LOG_ENTRIES_41_60;
//         
                           /* Assign the ips_command_id for the response msg.*/
//                           ReadErrorLogResponseMsg.ips_command_id  = READ_ERROR_LOG_ENTRIES_41_60;
//                           break;
//                         
//                        case READ_ERROR_LOG_ENTRIES_61_80:
//                           ErrorLogHandlerRequest  = READ_ERR_LOG_ENTRIES_61_80;
//         
                           /* Assign the ips_command_id for the response msg.*/
//                           ReadErrorLogResponseMsg.ips_command_id  = READ_ERROR_LOG_ENTRIES_61_80;
//                           break;
//         
//                        default:   
//
                           /* Log any software errors */
//                           LOG_SWARE_ERROR(E_SWITCH_DEFAULT, DIAGNOSTICS_MANAGER); 
//
//                           break;
//                
//                        } /* END SWITCH */
//                           
//                     
                     /* assign cib info */
//                     ReadErrorLogResponseMsg.cib_info = DiagMsg.read_log_msg.cib_info;
//               
                     /* Call the ERROR log to read ERROR log entries */
                     /* Note that the error_kind, error_code, error_caller,*/ 
                     /* error_request, and line_number will be ignored by the sware log handler*/
//                     ErrorLogHandler(ErrorLogHandlerRequest ,
//                                       ErrorKind,
//                                       ErrorCode,
//                                       ErrorCaller,
//                                       ErrorRequest,
//                                       LineNumber,
//                                       &ErrorLogReturnDataPtr,
//                                       &ErrorLogByteCount);
//         
                     /* Form the message, OP_READ_ERROR_LOG_RESPONSE with the */
                     /* error_log_return_data_ptr and error log byte count. Send to MICH queue. */   
//                     ReadErrorLogResponseMsg.common.opcode       = OP_READ_ERROR_LOG_RESPONSE;
//                     ReadErrorLogResponseMsg.common.pointer_flag = DATA_PTR_NO_DEALLOC;
//                     ReadErrorLogResponseMsg.common.source_task  = DIAG_SOURCE_TASK;
//                     ReadErrorLogResponseMsg.error_log_info_ptr  = ErrorLogReturnDataPtr;
//                     ReadErrorLogResponseMsg.byte_count          = ErrorLogByteCount;
//
                     /* ReadErrorLogResponseMsg.ips_command_id has been set above in "case"    */
                     /* statements above                                                           */
//                     CkQSend(RschQid,                            /* Queue to send message to   */ 
//                               &ReadErrorLogResponseMsg,         /* Address of message buffer  */
//                               DIAGNOSTICS_MANAGER,              /* Caller Identifier          */
//                               __LINE__, 
//                               MILLS_TO_TICKS(100));
//                     break;   
//
                  }  /*END SWITCH DiagMsg.read_log_msg.ips_command_id */
            break;

            case OP_CLEAR_LOG:               /* Msg to clear one of the logs */
                  
               /* Deallocate the buffer */
               PsosStatus = pt_retbuf(DiagMsg.clear_log_msg.cib_partition_id,
                                       DiagMsg.clear_log_msg.cib_info);
                                       
               /* Log any software errors */
               LOG_PSOS_ERROR(PsosStatus, DIAGNOSTICS_MANAGER);

               switch (DiagMsg.clear_log_msg.ips_command_id)
                  {
         
                  case CLEAR_SWARE_LOG_ENTRIES:
         
                     /* Call the SWARE error log to CLEAR SWARE log entries. */
                     /* Note that the error_kind,ErrorCode, ErrorCaller, ErrorRequest, */
                     /* LineNumber, and SwareLogReturnDataPtr will be ignored by the */
                     /* sware log handler.*/
                     SwareLogHandler(CLEAR_SWARE_LOG,
                                       ErrorKind,
                                       ErrorCode,
                                       ErrorCaller,
                                       ErrorRequest,
                                       LineNumber,
                                       (SWARE_LOG_DATABASE_TYPE **) NULL,
                                       (SWARE_LOG_BYTE_COUNT_TYPE *) NULL
                                       );
                     break;
         
         
                  default:   

                     /* Log any software errors */
                     LOG_SWARE_ERROR(E_SWITCH_DEFAULT, DIAGNOSTICS_MANAGER); 

                     break;
         
                  } /* END SWITCH DiagMsg.clear_log_msg.ips_command_id */
         
               break;
         
          
           default:   /*Unknown opcode */

              /* Log the error in the Sware error log  */
              LOG_SWARE_ERROR(E_SWITCH_DEFAULT, DIAGNOSTICS_MANAGER); 
         
              break;
           }  /* END SWITCH OPCODES */
        }
     }
 
   } /* end of DiagManager task */




/*
  ---------------------------- MODULE DESCRIPTION -------------------------------
   Module name:   Diagnostic Manager

   Function name: ProcessErrorMsg

   -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            01/31/96      Mark L      Initial Version

 ------------------------------- DESCRIPTION ------------------------------------

 This routine processes error messages received from manage_errors. It logs the
 error in the software log (SWARE) 

 We call tm_wkafter() prior to returning. This will throttle the rate that error
 messages are processed.
 
 ---------------------------------- CODE ---------------------------------------
*/

void ProcessErrorMsg(
   MANAGE_ERRORS_MSG                       *manage_errors_msg_ptr )

   {

   switch( manage_errors_msg_ptr->error_kind)  
      {
      case  PSOS:
      case  SWARE:               
      case  NVM:               
      case  OPTION_ERROR:
      case  MISC_ERROR:               
                      
      if ((manage_errors_msg_ptr->error_request ==  LOG_ERROR) ||
          (manage_errors_msg_ptr->error_request == UNRECOVERABLE)) 
         {
         /* Log the PSOS, SWARE, SPI,and NVM problems in the SWARE LOG in detail.*/
                                
         if ((manage_errors_msg_ptr->error_kind ==  PSOS) ||
             (manage_errors_msg_ptr->error_kind ==  SWARE)||
             (manage_errors_msg_ptr->error_kind ==  NVM)) 
            {
            /* Log the error in the Sware error log  */
            SwareLogHandler(WRITE_SWARE_LOG,
                              manage_errors_msg_ptr->error_kind,
                              manage_errors_msg_ptr->error_code,
                              manage_errors_msg_ptr->error_caller,
                              manage_errors_msg_ptr->error_request,
                              manage_errors_msg_ptr->line_number,
                              (SWARE_LOG_DATABASE_TYPE **) NULL,
                              (SWARE_LOG_BYTE_COUNT_TYPE *) NULL);
            }
         }  

      default:   /*This is an unknown error kind - update alarm db table */

         /* Log any software errors */
         LOG_SWARE_ERROR(E_SWITCH_DEFAULT, DIAGNOSTICS_MANAGER); 

      break;
         
      } /*END SWITCH ERROR KIND */

   tm_wkafter( ErrorThrottle );

   return;
   }



/*
  ---------------------------- MODULE DESCRIPTION -------------------------------
   Module name:   Diagnostic Manager

   Function name: QueueError


  -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
       0           01/31/96      Mark L      Initial Version

 ------------------------------- DESCRIPTION ------------------------------------

 This routine constructs a MANAGE_ERRORS_MSG and queues it at the DiagQid.

 If the queue is full or if pSOS is out of buffers then we ignore the message.
 
 ---------------------------------- CODE ---------------------------------------
*/
void QueueError(
   ERROR_KIND_TYPE      error_kind,
   ERROR_CODE_TYPE      error_code,
   ERROR_CALLER_TYPE    error_caller,
   ERROR_REQUEST_TYPE   error_request,
   C_LINE_NUMBER_TYPE   line_number )

   {
//   UINT32               PsosStatus;      
   MANAGE_ERRORS_MSG    ManageErrorsMsg;

   ManageErrorsMsg.error_kind          = error_kind;
   ManageErrorsMsg.error_code          = error_code;
   ManageErrorsMsg.error_caller        = error_caller;
   ManageErrorsMsg.error_request       = error_request;
   ManageErrorsMsg.line_number         = line_number;
   ManageErrorsMsg.common.pointer_flag = NO_DATA_PTR;
   ManageErrorsMsg.common.opcode       = OP_MANAGE_ERRORS_MSG;

   /*
    * Send the message to the DIAG_Q. Note that the DiagQid is global within
    * this file. We don't have to call pSOS to get it
    */
//   PsosStatus = q_send (DiagQid, &ManageErrorsMsg);

   /*
    * If unable to send the message then determine the reason for failure.
    */
//   if ( PsosStatus != E_NO_ERROR )
//      {
      /*
       * If there aren't enough buffers or if the queue is full then just ignore
       * the error. All other errors are fatal.
       */
//      if ( (PsosStatus != E_NOMGB) && (PsosStatus != E_QFULL) )
//         {
//         LOG_PSOS_ERROR(PsosStatus, MANAGE_ERRORS_MAIN);
//         }
//      }
   return;
   }

/* FOR UNIT TEST ONLY */
#ifdef INCLUDE_UNIT_TEST
#include "diagnose.ut"
#endif
/* FOR UNIT TEST ONLY */

/* FOR INTEGRATION TEST ONLY */

 #ifdef INCLUDE_INTEGRATION_TEST
   #include "diagnose.it"
 #endif


/* FOR INTERGRATION TEST ONLY */
