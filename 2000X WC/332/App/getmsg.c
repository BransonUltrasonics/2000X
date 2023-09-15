/* $Header:   D:/SWLab/VMdb/2000Series/App/GETMSG.C_V   2.47   04 Sep 2008 20:16:22   ygupta  $ */
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

   Module name: Manage Display

   Filename:  getmsg.c was fpsmangr.c

 
            Written by: Mark Lazarewicz 
                  Date: 1/30/96 
              Language: Microtec "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========       ======      ===========
     0            01/30/96       Mark L      Initial Version
     1            03/21/96       Mark L      Add ADIM messages
     2            04/22/96       LAM         moved fpsmanger to getmsg
     3            04/29/96       LAM         get current preset
     4            04/29/96       LAM         added test code for minmax
     5            04/29/96       PJ          Added const to display
                                             message strings.
     6            05/10/96       PJ          Added HERE_IS_WELD_DATA
     7.0          05/15/96       PJ          Corrected warnings
     8.0          06/20/96       PJ          Added OP_HERE_IS_CURRENT_SETUP
                                             to copy CurrentSetup configuration.
     8.1          07/25/96       PJ          Deleted call to SelectTimeMode
                                             in OP_HERE_IS_PRESET
     8.2          07/26/96       PJ          Added code to initialize WeldMode
                                             variables on Powerup.
     8.3          08-06-96       BEKymer     Remove code to default set mode to TIMEMODE
                                             Include menu.h for weld modes
     8.4          08/22/96       PJ          CurrentPreset, MinLimit, MaxLimit
                                             and CurrentSetup now externals.
     8.5          08/23/96       PJ          Deleted OP_HERE_IS_WELD_DATA,
                                             OP_HERE_IS_PRESET.
     8.6          09/19/96       PJ          Deleted include file menu0.h.
     8.7          10/27/96       PJ          Removed initialization of Key
                                             at Power up.
     8.8          11-21-96       BEKymer     Put back initialization of Key
                                             New function to figure out who
                                             called GetMsg
     8.9          11/29/96       LAM         chged q_send         
     9.0          01/29/96       LAM         moved min & max preset to sysmanger
     10           03/30/97       LAM         welddata test
     11           04/02/97       LAM         made queue global
     12           04/08/97       LAM         deleted unused include
     13           04/18/97       PhilJ       Major cleanup.
     14.2.23      06/17/97       LAM         deleted unused queues
     15.2.24      06/24/97       LAM         deleted ident for fpkp
     2.25         09/08/97       LAM         cleanup unit test,deleted warning
     2.26         10/21/97       BJB         Added new function GetMsgNoWait()
     2.27         11/07/97       BJB         Added new function ClearKeypadBuffer()
     2.28         11/08/97       BJB         Added new function KeyAvailable().
                                              This required added HoldingChr
                                              variable to temporarily store chr
                                              read from queue.
                                             Deleted function GetMsgNoWait().
     2.29         01/05/98       BJB         Function ClearKeypadBuffer() tells
                                              terminal code some of its messages
                                              may have been zapped.
     2.30         04/05/98       BJB         Added functions WaitMessage(),
                                              ProcessControlMessage().
     2.31         04/21/98       BJB         WaitMessage() modified to return time
                                              remaining.
     2.32         04/23/98       BJB         Added message logging for debugging.
                                             Saves extra message byte in MsgExtra.
                                             Added function PutMsg() to pass the
                                              extra byte.
     2.33         07/21/98       BJB         Created new 32-bit message system.
                                              GetMsg(), SendFakeKeyPress(),
                                              PutMsg() call routines to convert
                                              old format to new and back so the
                                              new system is transparent to old
                                              code.
                                             New system can limit some msgs to
                                              only one occurrence in queue.
     2.34         08/21/98       LAM         added new case to processcontrolmessage.
                                             this is used when calibration aborted
     2.35         08/28/98       BJB         Moved defintion of new message format
                                              to GETMSG.H.
                                             Made message format conversion
                                              routines public (global).
                                             Simplified control message conversions
                                              because HD mode now uses new format
                                              only.
                                             Use new label names for old keycodes.
     2.36         09/08/98       BJB         Makes sure ClearKeypadBuffer() can't
                                              throw out TestKey.
     2.37         09/08/98       BJB         Added code to print message log.
     2.38         09/10/98       BJB         Modified RcvMsg() to accept GetMsgFlag
                                              value.
     2.39         12/07/98       BJB         Sets MESSAGE_NEW bit in messages.
     2.40         05/04/99       LAM         chged asm for DIAB
     2.41         10/11/99       JZ          removed PutMsg()
     2.42         12/16/99       LAM         removed unused error handling code
     2.42.1.0     08/05/03       JOY         CONTROL_MSG/SPECIAL_MSG are send to the
                                             QVGA queue. 
     2.44         12-02-03       BEKymer     Merged 2.42.1.0 & 2.42 to create 2.44
                                              for Ver9.00b build.  ViewKey changes
                                              in 2.43 are not included.
     2.45         07-25-05       Bwadia      Control messages are sent to RVTS queue  
     2.46         10-22-07       NHAhmed     Changes done for LangTest phase 0
     2.47         09-04-08       YGupta      CleanUp for LangTest Project.

                                              

 ------------------------------ DESCRIPTION -----------------------------------

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include <psos.h>
#include "genrlmsg.h"
#include "kpresmsg.h"
#include "ticks.h"
#include "fpkp_msg.h"
#include "keypad.h"
#include "menu.h"
#include "getmsg.h"
#include "snsrcalb.h"

/* For qvga support */
#include "qvga_task.h"
#include "opcodes.h"

/*
 ---------------------------- FUNCTIONS PROTOTYPES -------------------------
*/

void ShowEstopMessageOn(void);        /* External functions */
void ShowEstopMessageOff(void);

/*
 ------------------------------- EXTERNAL DATA --------------------------------- 
*/ 


/*
 ------------------------------- LOCAL DEFINES ---------------------------------
*/

struct MessageLogItem         /* Def of a message log item */
{
   UINT32 Message;            /* Message being logged */
   UINT32 Time;               /* Time it was read */
   UINT32 Sender;             /* Address of message sender */
   UINT32 Receiver;           /* Return address from GetMsg() call */
};

struct MenuMessage
{
   UINT32 Msg;
   UINT32 Sender;
   UINT32 Unused1;
   UINT32 Unused2;
};

#define MSG_LOG_SIZE 100      /* Number of messages to save in log */

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

extern BOOLEAN QVGAHornDown;
extern UINT32 FpscQid;
extern UINT32 QvgaQid; 
extern UINT32 RvtsQid; 
extern UINT32 ReadOnlyTimer;

UINT8 MsgExtra;         /* Kludge.  This is global storage for extra byte */
                        /* that comes with 8-bit messages and provides */
                        /* additional information. */

struct MessageLogItem MessageLog[MSG_LOG_SIZE]; /* Saves info last messages */
UINT16 MsgLogInPtr = 0;    /* Pointer into circular log buffer */
BOOLEAN MsgLogWrapped = FALSE;

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

static void LogMenuMessage( UINT32 Message, UINT32 Sender, UINT32 Receiver );
static void PrintMsgLogItem( UINT16 Item, UINT32 TimeZero );
static void FormatHex( UINT32 Value, SINT8 buffer[], UINT16 Length );

/*
 -------------------------------- PRIVATE GLOBAL DATA ----------------------------------
*/
static UINT16        GetMsgFlag;
static struct MenuMessage HoldingMsg;        /* Temporary storage for chr */
                                             /* read from queue but not */
                                             /* used by calling func yet. */
static BOOLEAN       GotHoldingMsg = FALSE;

/* Each flag in the array below is TRUE if its corresponding message is in */
/* the message queue. */

UINT8 MessageUseFlags[NUM_MSG_USE_FLAGS] = { 0, 0, 0, 0, 0, 0, 0, 0,
                                                    0, 0, 0, 0, 0, 0, 0 };

/*
 --------------------------------- CODE ----------------------------------------
*/  

/* IT IS VERY IMPORTANT THAT THE FUNCTIONS IN THIS FILE BE CALLED ONLY FROM */
/* ONE TASK.  CALLING FROM MULTIPLE TASKS CAN CAUSE UNPREDICTABLE RESULTS! */

UINT32 RcvMsg( UINT16 Flag )
/****************************************************************************/
/*                                                                          */
/* Retrieves the next message for processing by the menu task.  The         */
/* "Flag" parameter is used to find the return address on the stack, which  */
/* is just before &Flag, as well as for its normal use.                     */
/*                                                                          */
/****************************************************************************/
{
   UINT32 PsosStatus;
   UINT32 MsgUseId;
   struct MenuMessage MenuMsg;   /* Full message */

   GetMsgFlag = Flag;    /* TRUE:called by DisplayMenu,        */
                         /* FALSE:called by DealWithSelectKey  */

   if (GotHoldingMsg)
   {
      MenuMsg = HoldingMsg;
      GotHoldingMsg = FALSE;
   }
   else
   {
      PsosStatus = q_receive(FpscQid, Q_NOWAIT, Q_WAIT_FOREVER, &MenuMsg );
      if (PsosStatus == ERR_NOMSG)  /* If no message, wait for one */
      {
         PsosStatus = q_receive(FpscQid, Q_WAIT, Q_WAIT_FOREVER, &MenuMsg );
         MenuMsg.Msg |= MESSAGE_NEW;   /* Note: Had to wait for this msg */
      }                  
   }

   /* If this message is one that should only appear in the buffer once, */
   /* clear flag now so it can be put in the buffer again. */

   MsgUseId = (MenuMsg.Msg & MESSAGE_USE_ID_FIELD) >> MESSAGE_USE_ID_BITPOS;
   if (MsgUseId)
      MessageUseFlags[MsgUseId-1] = 0;  /* MsgUseId=0 when no flag needed */


   /* Before returning message, log it.  Get address that GetMsg() will     */
   /* return to by finding address of Flag on the stack and backing up to   */
   /* function return address.  This is three words: 1 for top half of Flag */
   /* (it's a UINT16 in 32-bits of space), 2 for return address.            */

   LogMenuMessage( MenuMsg.Msg, MenuMsg.Sender,
    *((UINT32*)(((UINT16*)&Flag) - 3)) );

   return(MenuMsg.Msg);
}

UINT32 WaitMessage( UINT32 TimeWait )
/****************************************************************************/
/*                                                                          */
/* Waits the specified time for a message to be available.  If a messasge   */
/* comes in that is a control message, it will be processed locally and the */
/* routine will continue to wait for other messasges up to the time limit.  */
/* If a message comes in that can't be processed locally, it is stored for  */
/* later retrieval by a RcvMsg() call, and this function exits.             */
/*                                                                          */
/* Function returns the amount of time left to wait, in pSOS tick units.    */
/* This is zero if exit was caused by timeout, nonzero if caused by a       */
/* message that couldn't be processed.                                      */
/*                                                                          */
/* This function should be used in place of tm_wkafter(), which may prevent */
/* the menu system from responding to important messages.                   */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN GotMsg, Quit;
   SINT32 FinalTime, TimeTicks, TimeRemaining;
   UINT32 PsosStatus;
   UINT32 MsgUseId;
   struct MenuMessage MenuMsg;

   /* Compute time at which to stop looking for a message */

   FinalTime = ReadOnlyTimer + TICKS_TO_MS( TimeWait );
   GotMsg = FALSE;
   Quit = FALSE;

   TimeRemaining = FinalTime - ReadOnlyTimer;

   while ((TimeRemaining > 0) && !GotMsg && !Quit)
   {
      if (GotHoldingMsg)
      {
         MenuMsg = HoldingMsg;
         GotHoldingMsg = FALSE;
         GotMsg = TRUE;
      }
      else
      {        /* Compute time left to go, wait this long for a message */

         TimeTicks = MS_TO_TICKS( TimeRemaining );
         PsosStatus = q_receive(FpscQid, Q_WAIT, TimeTicks, &MenuMsg);

         if (PsosStatus != ERR_TIMEOUT)
         {
            GotMsg = TRUE;
         }
         else
         {
            GotMsg = FALSE;
            Quit = TRUE;   /* Timed out, don't even bother to check time */
         }                 /* Quit = TRUE prevents calls to q_receive with */
      }                    /* very short timeouts if psos clock and */
                           /* ReadOnlyTimer are slightly out of sync */

      if (GotMsg)          /* If we got a message, try to process here */
      {
         MsgUseId = (MenuMsg.Msg & MESSAGE_USE_ID_FIELD) >> MESSAGE_USE_ID_BITPOS;
         if (MsgUseId)
            MessageUseFlags[MsgUseId-1] = 0;  /* MsgUseId=0 when no flag needed */

         if (ProcessControlMessage( ConvertNewToOld( MenuMsg.Msg, &MsgExtra )))
         {
            GotMsg = FALSE;    /* Processed, will check for more */
            LogMenuMessage( MenuMsg.Msg, MenuMsg.Sender,
             (UINT32)WaitMessage );              /* Message used here, log */
         }
      }

      TimeRemaining = FinalTime - ReadOnlyTimer;
   }

   if (GotMsg)             /* Save message where it can be retrieved */
   {
      HoldingMsg = MenuMsg;
      GotHoldingMsg = TRUE;
   }

   if (Quit || TimeRemaining < 0)
      TimeRemaining = 0;            /* Result must be unsigned, should be */
                                    /* zero if we timed out */
   return( MS_TO_TICKS( TimeRemaining) );
}

BOOLEAN KeyAvailable( UINT16 Flag )
/****************************************************************************/
/*                                                                          */
/* Returns FALSE if no keys available, TRUE if there are keys available.    */
/* Unfortunately, to find out if queue holding keypresses is empty, must    */
/* try to read something.  May then end up with a character we don't know   */
/* what to do with.  In this case, it gets put in HoldingMsg and returned   */
/* by GetMsg() ahead of any other keypresses.                               */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN GotMsg;
   UINT32 PsosStatus;
   struct MenuMessage MenuMsg;

   GetMsgFlag = Flag;    /* TRUE:called by DisplayMenu,        */
                         /* FALSE:called by DealWithSelectKey  */

   if (GotHoldingMsg)   /* Got a chr right here, so certainly available */
      GotMsg = TRUE;
   else
   {
            /* Check keypad queue and return whether keypress or not */
      PsosStatus = q_receive(FpscQid, Q_NOWAIT, Q_WAIT_FOREVER, &MenuMsg);
   
      if (PsosStatus != ERR_NOMSG)    /* If queue empty, just return */
      {
         GotMsg = TRUE;
         HoldingMsg = MenuMsg;
         GotHoldingMsg = TRUE;
      }
      else
         GotMsg = FALSE;

   }
   return( GotMsg );
}

void ClearKeypadBuffer( UINT16 Flag )
/****************************************************************************/
/*                                                                          */
/* This function reads all the keys that are in the key queue and throws    */
/* them away. Exception: If one of these is the Test key, this is NOT       */
/* thrown away, see explanation below.                                      */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN GotKey;
   BOOLEAN TestFlag;
   UINT8 NewKey;
   UINT8 MsgUseIndex;

   TestFlag = FALSE;

   do
   {
      GotKey = KeyAvailable( Flag );
      if (GotKey)
         NewKey = GetMsg( Flag );

      /* TestKey is at present processed initially by WeldManager, which    */
      /* will go ahead and put the system in test mode before the menu task */
      /* knows what's happening. WeldManager then sends a Test keypress to  */
      /* the menu task. It's very important not to throw this out or the    */
      /* system could end up in Test mode with the menus showing weld mode. */
      /* So, if we find a TestKey here, we stuff it back into the queue     */
      /* after clearing the other keypresses. */

      if (NewKey == TestKey)
         TestFlag = TRUE;

   } while (GotKey);

   /* No messages now in buffer, clear all use flags */

   for (MsgUseIndex=0; MsgUseIndex < NUM_MSG_USE_FLAGS; MsgUseIndex++)
      MessageUseFlags[MsgUseIndex] = 0;


   if (TestFlag)
      SendMsg( TEST_KEY );
}


UINT16 old_mode;


UINT32 SendMsg( UINT32 Msg )
/****************************************************************************/
/*                                                                          */
/* Stores the given message in the message queue for the menu task.         */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN DoSend;
   UINT32 MsgUseId;
   UINT32 MsgType;
   UINT32 PsosStatus;
   struct MenuMessage MenuMsg;
   QVGAMENUTASK_MSG  QVGAmenuMsg;

   PsosStatus = 0;

   MenuMsg.Msg = Msg & ~MESSAGE_NEW;
   MenuMsg.Sender = *((&Msg)-1); /* Gets return address in SendMsg() caller */
   MenuMsg.Unused1 = 0;
   MenuMsg.Unused2 = 0;

   MsgUseId = (MenuMsg.Msg & MESSAGE_USE_ID_FIELD) >> MESSAGE_USE_ID_BITPOS;
   MsgType  = (MenuMsg.Msg & MESSAGE_TYPE_FIELD) >> MESSAGE_TYPE_BITPOS;

   /* If this field of message has a nonzero # in it, then this message */
   /* should only be placed in the buffer if it isn't already there.  Check */
   /* appropriate flag to see if it is, don't send in this case.  Test must */
   /* be done with interrupts off in case message is placed in buffer by */
   /* another task after test but flag set TRUE. */

   if (MsgUseId)
   {
      asm( " move.w sr,d0\n ori.w #$700,sr\n move.w d0, _old_mode" );

      if (!MessageUseFlags[MsgUseId-1])
      {
         MessageUseFlags[MsgUseId-1] = TRUE;
         DoSend = TRUE;
      }
      else
         DoSend = FALSE;

      asm( " move.w _old_mode,d0\n move.w d0,sr" );

   }
   else
      DoSend = TRUE;

   if (DoSend)
   {
     if(QVGAHornDown)
     {
        if(MsgType == CONTROL_MSG || MsgType == SPECIAL_MSG)
        {
           QVGAmenuMsg.common.opcode = OP_QVGAMENUTASK_MSG;
           QVGAmenuMsg.message = MenuMsg.Msg;
           PsosStatus = q_send(RvtsQid, &QVGAmenuMsg );
        }
     }
     else
        PsosStatus = q_send( FpscQid, &MenuMsg );

      if ((PsosStatus == ERR_QFULL) && MsgUseId)   /* If queue was full, */
         MessageUseFlags[MsgUseId-1] = 0;         /* msg not really put in. */
   }

   return( PsosStatus );
}

UINT16 Get_GetMsgFlag(void)
{
   return(GetMsgFlag);
}

BOOLEAN ProcessControlMessage( UINT8 Message )
/****************************************************************************/
/*                                                                          */
/* Provides default processing for control messages.  Takes a message code  */
/* as input, returns TRUE if the message was successfully processed.  This  */
/* routine should be called to handle any control messages not processed    */
/* explicitly by a particular menu.                                         */
/*                                                                          */
/****************************************************************************/
{
   BOOLEAN RetVal;

   switch( Message )
   {
      case TERMDATAOUTPUT:
         RetVal = TRUE;
         break;

      case UPDATETERMALARM:
         RetVal = TRUE;
         break;


      case ESTOPMSGON:
         ShowEstopMessageOn();
         RetVal = TRUE;
         break;

      case ESTOPMSGOFF:
         ShowEstopMessageOff();
         RetVal = TRUE;
         break;

      case CALIBRATION_ABORTED:
         ShowCalibrationAbort();
         RetVal = TRUE;
         break;

      default:
         RetVal = FALSE;
   }

   return( RetVal );
}

UINT8 GetMsg( UINT16 Flag )
{
   return( ConvertNewToOld( RcvMsg( Flag ), &MsgExtra ));
}

UINT32 SendFakeKeyPress(KEY_CODE_TYPE Key)
{
   return( SendMsg( ConvertOldToNew( Key, 0 )));
}

static void LogMenuMessage( UINT32 Message, UINT32 Sender, UINT32 Receiver )
{
   if (Message != UPDATE_TERM_ALARM)      /* Don't log these, too many */
   {
      MessageLog[MsgLogInPtr].Message = Message;
      MessageLog[MsgLogInPtr].Time = ReadOnlyTimer;
      MessageLog[MsgLogInPtr].Sender = Sender;
      MessageLog[MsgLogInPtr++].Receiver = Receiver;

      if (MsgLogInPtr >= MSG_LOG_SIZE)
      {
         MsgLogInPtr = 0;
         MsgLogWrapped = TRUE;
      }
   }
}

UINT32 ConvertOldToNew( KEY_CODE_TYPE Key, UINT8 Extra )
{
   UINT32 Msg;
   UINT32 MsgType;
   UINT32 MsgCode;
   UINT32 MsgData;
   UINT32 MsgUseId;

   MsgData = Extra;
   MsgUseId = 0;

   if (Key > FIRSTCONTROLMESSAGE)
   {
      MsgType = CONTROL_MSG;
      MsgCode = Key - UPDATEDISPLAY + UPDATE_DISPLAY_CODE;

      /* Set use id for messages that should only be in */
      /* buffer once at any given time. */

      if (Key >= UPDATEDISPLAY && Key <= UPDATETERMALARM &&
       Key != TERMDATAOUTPUT)
         MsgUseId = Key - UPDATEDISPLAY + 1;
   }
   else
   {
      MsgType = CHR_RECEIVED_MSG;  /* This usually true from here on */

      if (Key <= KEY_9)
         MsgCode = Key + '0';
      else if (Key >= SetupKey && Key <= RunKey)
      {
         if (Key == GoBackKey)
            MsgCode = 0x1B;  /* ESC */
         else
            MsgCode = Key - SetupKey + SETUP_KEY_CODE;
      }
      else if (Key >= Select1Key && Key <= Select3Key)
      {
         MsgType = SELECT_MSG;
         MsgCode = Key - Select1Key + 1;
      }
      else if (Key >= RightKey && Key <= DownKey)
         MsgCode = Key - RightKey + RIGHT_KEY_CODE;
      else if (Key >= TermUpKey && Key <= TermDownKey)
         MsgCode = Key - TermUpKey + UP_KEY_CODE;
      else if (Key == DPointKey)
         MsgCode = '.';
      else if (Key == IncKey)
         MsgCode = '+';
      else if (Key == DecKey)
         MsgCode = '-';
      else if (Key == ClearKey)
         MsgCode = 8;  /* backspace */
      else if (Key == EnterKey)
         MsgCode = 13; /* carriage return */
      else if (Key == TermDataKey)
         MsgCode = DATA_KEY_CODE;
      else if (Key == TermSelectKey)
      {
         MsgType = SELECT_MSG;
         MsgCode = 0;  /* single select key */
      }
      else
         MsgCode = 0;
   }

   Msg = (MsgType << MESSAGE_TYPE_BITPOS) |
    (MsgCode << MESSAGE_CODE_BITPOS) |
    (MsgData << MESSAGE_DATA_BITPOS) |
    (MsgUseId << MESSAGE_USE_ID_BITPOS);

   return( Msg );
}

UINT8 ConvertNewToOld( UINT32 Msg, UINT8 *Extra )
{
   UINT8 Key;
   UINT8 MsgType;
   UINT8 MsgCode;

   MsgType = (Msg & MESSAGE_TYPE_FIELD) >> MESSAGE_TYPE_BITPOS;
   MsgCode = (Msg & MESSAGE_CODE_FIELD) >> MESSAGE_CODE_BITPOS;
   *Extra = (Msg & MESSAGE_DATA_FIELD) >> MESSAGE_DATA_BITPOS;

   switch (MsgType)
   {
      case CONTROL_MSG:
         if (!MsgCode)
            Key = NOKEY;
         else
            Key = MsgCode - UPDATE_DISPLAY_CODE + UPDATEDISPLAY;

         break;

      case SELECT_MSG:
         if (!MsgCode)  /* individual select key from terminal */
            Key = TermSelectKey;
         else
            Key = MsgCode + Select1Key - 1;
         break;

      case CHR_RECEIVED_MSG:
         if (MsgCode >= '0' && MsgCode <= '9')
            Key = MsgCode - '0' + KEY_0;
         else if (MsgCode >= SETUP_KEY_CODE && MsgCode <= RUN_KEY_CODE)
         {
            if (MsgCode == DATA_KEY_CODE)
               Key = TermDataKey;
            else
               Key = MsgCode - SETUP_KEY_CODE + SetupKey;
         }
         else if (MsgCode >= RIGHT_KEY_CODE && MsgCode <= PG_DOWN_KEY_CODE)
            Key = MsgCode - RIGHT_KEY_CODE + RightKey;
         else if (MsgCode >= UP_KEY_CODE && MsgCode <= DOWN_KEY_CODE)
            Key = MsgCode - UP_KEY_CODE + TermUpKey;
         else if (MsgCode == '.')
            Key = DPointKey;
         else if (MsgCode == '+')
            Key = IncKey;
         else if (MsgCode == '-')
            Key = DecKey;
         else if (MsgCode == 8) /* backspace */
            Key = ClearKey;
         else if (MsgCode == 13) /* carriage return */
            Key = EnterKey;
         else if (MsgCode == 0x1B)  /* ESC key */
            Key = GoBackKey;
         else
            Key = NOKEY;
         break;

      default:
         Key = NOKEY;
   }
   return( Key );
}

void PrintMessageLog(void)
/****************************************************************************/
/*                                                                          */
/* Prints last MSG_LOG_SIZE messages logged, not including messages which   */
/* cause the ALARM message to blink. Printout shows time that message was   */
/* received (measured from time of first message), message code, and the    */
/* address of the message sender and receiver.                              */
/*                                                                          */
/****************************************************************************/
{
   UINT16 x;
   UINT32 TimeZero;


   if (MsgLogWrapped)
   {
      TimeZero = MessageLog[MsgLogInPtr].Time;

      for (x=MsgLogInPtr; x<MSG_LOG_SIZE; x++)
         PrintMsgLogItem(x, TimeZero);
   }
   else
      TimeZero = MessageLog[0].Time;

   for (x=0; x<MsgLogInPtr; x++)
      PrintMsgLogItem( x, TimeZero );

}

static void PrintMsgLogItem( UINT16 Item, UINT32 TimeZero )
/****************************************************************************/
/*                                                                          */
/* Prints the given item from the message log.                              */
/*                                                                          */
/* Inputs:                                                                  */
/*                                                                          */
/*    Item     - Index of item in message log to print.                     */
/*    TimeZero - Time of first message, from which to measure time of later */
/*               messages.                                                  */
/*                                                                          */
/****************************************************************************/
{
  
}

static void FormatHex( UINT32 Value, SINT8 buffer[], UINT16 Length )
/****************************************************************************/
/*                                                                          */
/* Converts value from binary to hex ASCII, writes to given buffer.         */
/*                                                                          */
/* Inputs:                                                                  */
/*                                                                          */
/*    Value  - Number to display in hex                                     */
/*    buffer - Where to put ASCII text. It will be right-justified, space   */
/*             to the left filled with spaces.                              */
/*    Length - Size of buffer to accept text.                               */
/*                                                                          */
/* Note: String is NOT terminated with a zero.                              */
/*                                                                          */
/****************************************************************************/
{
   UINT16 x, Digit;
   SINT8  *Ptr;

   Ptr = &buffer[Length-1];

   if (Length < 8)
      x = Length;
   else
      x = 8;

   while (x--)
   {
      Digit = Value & 0x0F;
      Digit += '0';
      if (Digit > '9')
         Digit += 7;

      Value /= 16;
      *(Ptr--) = Digit;
   }

   while (Length > 8)
   {
      *(Ptr--) = ' ';
      Length--;
   }
}
