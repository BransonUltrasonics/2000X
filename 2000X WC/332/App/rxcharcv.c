/* $Header:   D:/SWLab/VMdb/2000Series/App/RXCHARCV.C_V   2.39   04 Sep 2008 20:16:36   ygupta  $ */
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

   Module name: Comm_ASCII_Char_Rcvd

      Filename: rxcharcv.c

Function name : CommAsciiCharRcvd

    Written by: Mark Lazarewicz 
          Date: 02/28/96 
      Language: Microtec "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========       ======      ===========
      0            02/28/96      Mark L      Initial Version
      1            03/30/97      LAM         welddata test
      2            04/04/97      LAM         welddata test2
      3            04/04/97      Kevin D     Modified for Dumb Term operation
      4            04/21/97      LAM         1line data version
      5            04/28/97      LAM         cleanup      
      6.2.11       06/17/97      philj       Deleted qsend in void echo()
      6.2.12       06/17/97      LAM         Deleted echo_qid, echo();            
      6.2.13       07/03/97      Philj       fixed bug in memcpy bytecount
      6.2.14       07/07/97      LAM         Deleted COMSHORT.H                   
      6.2.13       07/08/97      Philj       Changed SerialTimer to OneMilTimer
      6.2.16       07/16/97      Philj       Added Sizer to packed enum.
      7.2.17       07/16/97      LAM         Deleted serialrxmessage[]            
      7.2.18       07/18/97      Philj       Deleted OneMilTimer.
      7.2.19       07/22/97      Philj       Receive counter is reset to 0
                                             on invalid DLE or END_OF_MESSAGE.
      7.2.20       07/22/97      Philj       Added check on byte count if < zero.
      7.2.21       07/22/97      Philj       ReceiveBuffer.Count was UINT16
                                             now SINT16.
      7.2.22       08/15/97      Philj       Commented out Echo mode 
      7.2.23       08/15/97      Philj       Chgd END_OF_MESSAGE from ETX to EOT 
      7.2.24       08/20/97      Philj       Checksum code added but not enabled 
      2.25         11/10/97      LAM         Chgd END_OF_MESSAGE from EOT to ETX
      2.26         12/29/97      BJB         Deleted code "if (DTEnabled)".
      2.27         12/31/97      BJB         Deleted unused *Serial from old
                                             terminal code.
                                             CommAsciiCharRcvd() is passed the
                                             new char, doesn't get it from
                                             global.
                                             Passes chrs meant for terminal code
                                             to TerminalInput().
      2.28         08/19/98      BJB         Changed RemoteTermInUse() call to
                                             new name, TermIsEnabled().
      2.29         10/22/98      LAM         moved typedef to include file add
                                             commandstartflag for timeout
      2.30         11/04/98      LAM         added 1 more byte for memcpy                              
      2.31         12/16/99      LAM         removed unused error handling code                        
      2.32         06/09/00      JLH         Rewrote to make it easier to follow.
      2.34         07/10/00      JLH         fixed some bugs.
      2.33.1.0     07-07-00      BEKymer/DJL fixed SETUP
      2.36         10-03-02      BEKymer     Add a call to DiagnosticInput with serial
                                              data received if OnboardDiag flag is TRUE
      2.37         04-15-03      BEKymer     Add ability to enable Diagnostics from remote
                                              terminal at power up by pressing the esc key
      2.38         12-27-03      VSharma     Update the byte_count value of ReadHostMsg
                                              before sending to Rsch task.
      2.39         09-04-08      YGupta      CleanUp for LangTest Project.
                                                                                      
                                              

 ------------------------------- DESCRIPTION -----------------------------------

  This module is called by ASYNC ASCII communication ISRs when a character is
  received. This may be from SCI or PC UART ports.
    
 ------------------------------    NOTES    ------------------------------------


 ------------------------------- PSEUDO CODE -----------------------------------
                 
                                                                              
 ------------------------------ INCLUDE FILES ----------------------------------
*/


#include <psos.h>
#include <prepc.h>
#include "rxcharcv.h"           /* Own interface                        */
#include "ipscdmsg.h"
#include "ipsatype.h"
#include "preset.h"
#include "serial.h"
#include "ckptgbuf.h"
#include "ck_qsend.h"           /* contains function interface           */
#include "iotest332.h"
#include "ascii.h"

/*
 ------------------------------- EXTERNAL DATA ---------------------------------
*/
                                                                 
extern CONFIGSETUP CurrentSetup;
extern UINT32 RschQid;   

extern UINT8  DTEnabled;
extern UINT8  RcvChecksum;

extern BOOLEAN OnboardDiag;
extern BOOLEAN PoweredUp;


/*
 ------------------------------- LOCAL DEFINES ---------------------------------
*/

#define MESSAGECOUNT 1

#define STARTCOUNT 4

#define START_OF_MESSAGE 0x10  /* DLE */
#define DLE              0x10  /* DLE */
#define STX              0x02  /* STX */
#define END_OF_MESSAGE   0x03  /* ETX */
#define ETX              0x03  /* ETX */

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/                                      
struct
   {
   UINT16            Function;    /* Host Command ID      */
   SINT16            Count;       /* Number of chars in receive buffer */
   UINT8             CharPtr[sizeof(SETUPS_Ver800)]; /* Pointer into current buffer   */
   UINT8             CheckSum;    /*  */
   } ReceiveBuffer;

HOST_COMMAND_MSG  ReadHostMsg;
UINT32 HostPtId;      /* Receiver partition ID */
UINT16 CommandStarted = FALSE;

/*
 -------------------------------- GLOBAL DATA ----------------------------------
*/    

RCV_BUFFER_STATUS_TYPE RcvBufferStatus = WAIT_FOR_START;
UINT16 MessageLength;
UINT16 ReceiveCounter = 0;
UINT8 *HostDataPtr;      /* Current destination of data            */

/*
 --------------------------------- CODE ----------------------------------------
*/                

void CommAsciiCharRcvd( UINT8  ByteReceived )
{

    /*
    * Copy the received characters into the partition buffer. Note that we
    * will normally receive only one character at a time but that the
    * PC UART may buffer up to four characters.
    */

   if (OnboardDiag == TRUE)                
      DiagnosticInput(ByteReceived);       /* On board diagnostics enabled */

   
   else        /* Host command */
   {
      switch(RcvBufferStatus)
      {
         case WAIT_FOR_START:
            if(ByteReceived == DLE)
            {
               RcvBufferStatus = WAIT_FOR_STX;
               CommandStarted = TRUE;
            }
            else if ((PoweredUp == FALSE) && (ByteReceived ==  ESC)) 
               OnboardDiag = TRUE;             /* diagnostics through the serial port */
            break;

         case WAIT_FOR_STX:
            if(ByteReceived == STX)
            {
               RcvBufferStatus = GET_MESSAGE_SIZE;
               ReceiveCounter = 0;
               RcvChecksum = 0;
            }
            else
            {
               RcvBufferStatus = WAIT_FOR_START;
               CommandStarted = FALSE;
            }
            break;

         case GET_MESSAGE_SIZE:
            switch(ReceiveCounter)
            {
               case 0:
                  MessageLength = ByteReceived;
                  RcvChecksum ^= ByteReceived;
                  ReceiveCounter++;
                  break;
               case 1:
                  /* Subtract 4 to get number of data bytes. */
                  ReceiveBuffer.Count = MessageLength*256 + ByteReceived - 4;
                  RcvChecksum ^= ByteReceived;
                  RcvBufferStatus = GET_MESSAGE_TYPE;
                  ReceiveCounter = 0;
                  break;
            }
            break;

         case GET_MESSAGE_TYPE:
            switch(ReceiveCounter)
            {
               case 0:
                  MessageLength = ByteReceived;
                  RcvChecksum ^= ByteReceived;
                  ReceiveCounter++;
                  break;
               case 1:
                  ReceiveBuffer.Function = MessageLength*256 + ByteReceived;
                  RcvChecksum ^= ByteReceived;
                  if(ReceiveBuffer.Count)
                     RcvBufferStatus = START_TO_ACCUMULATE;
                  else
                  {
                     RcvBufferStatus = WAIT_FOR_CHECKSUM;
                     /* Send a NULL to command.c if there are no data bytes. */
                     ReadHostMsg.byte_count = 1;
                     ReceiveBuffer.CharPtr[0] = 0;
                  }
                  ReceiveCounter = 0;
                  break;
            }
            break;

         case START_TO_ACCUMULATE:
            ReceiveBuffer.CharPtr[ReceiveCounter++] = ByteReceived;
            RcvChecksum ^= ByteReceived;
            if(ReceiveCounter == ReceiveBuffer.Count)
            {
               /* NULL terminate data sent to command.c */
               ReceiveBuffer.CharPtr[ReceiveCounter++] = NULL;
               ReadHostMsg.byte_count = ReceiveCounter;
               RcvBufferStatus = WAIT_FOR_CHECKSUM;
            }
            break;

         case WAIT_FOR_CHECKSUM:
            ReceiveBuffer.CheckSum = ByteReceived;
            if(ByteReceived != RcvChecksum)
               ReceiveBuffer.Function = CHECKSUM_ERROR;
            RcvBufferStatus = WAIT_FOR_DLE;
            break;

         case WAIT_FOR_DLE:
            if(ByteReceived == DLE)
               RcvBufferStatus = WAIT_FOR_END_MESSAGE;
            else
            {
               RcvBufferStatus = WAIT_FOR_START;
               CommandStarted = FALSE;
            }
            break;           

         case WAIT_FOR_END_MESSAGE:
            if(ByteReceived == ETX)
               RcvBufferStatus = SEND_BUFFER;
            else
            {
               RcvBufferStatus = WAIT_FOR_START;
               CommandStarted = FALSE;
            }
            break;
         
         default:
            RcvBufferStatus = WAIT_FOR_START;
            break;

      }
      /*
       * Send buffer if its complete
       */
      if ( RcvBufferStatus == SEND_BUFFER ){
         RcvBufferStatus = WAIT_FOR_START;
         CommandStarted = FALSE;                                                                        
         ReceiveCounter = 0;
         /*
          * Get a new partition buffer for accumulating received messages
          */
         CkPtGetbuf(HostPtId, (void **)&HostDataPtr,
              SERIAL_INTERRUPT,__LINE__, MILLS_TO_TICKS(100));

         ReadHostMsg.common.opcode        = ReceiveBuffer.Function;
         ReadHostMsg.data_pointer         = HostDataPtr;
         ReadHostMsg.common.pointer_flag  = DATA_PTR_DEALLOC;
         ReadHostMsg.partition_id         = HostPtId;
         memcpy(HostDataPtr,&ReceiveBuffer.CharPtr,ReadHostMsg.byte_count);
         ReadHostMsg.byte_count           = ReceiveBuffer.Count;
         /*
          * Send the message
          */
          CkQSend(RschQid,           /* Queue to send message to   */ 
                  &ReadHostMsg,      /* Address of message buffer  */
                  SERIAL_INTERRUPT,  /* Caller Identifier          */
                  __LINE__, 
                  MILLS_TO_TICKS(100));
      }
   }
}


void InitReceiveBuffer(void)
{
    UINT32      PsosStatus;                   /* Status returned from pSOS         */

   /*
    * Get a buffer from the Receiver Partition. Received strings will
    * be accumulated in this buffer
    */
   PsosStatus = pt_ident (READ_LOG_PARTITION, PT_NODE_0, &HostPtId);


}

