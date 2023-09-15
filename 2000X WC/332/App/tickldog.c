/* $Header:   K:\APPS\PVCS Pro\332new\App\TICKLDOG.C_V   2.3   Dec 17 1999 09:57:54   lmarkure  $ */
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

   Module name:  Watchdog

   Filename:  tickldog.c

   Function name: wd_tickle


            Written by: Mark Lazarewicz 
                  Date: 1/16/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             1/16/96      Lazar       Initial version
      2.2           09/11/97     PaulG       Unit test and data cleanup.       
      2.3           12/16/99     LAM         removed unused error handling code

   ------------------------------- DESCRIPTION -----------------------------------


   The purpose of this task is to keep the 68332 watchdog timer from timing out.
   It does this by writing to the watchdog counter register once per second.  
   This task also has a message queue that will accept commands from other tasks.
   So far the the only command is "reset"  which will stop the task and cause 
   the system to reset.

 ------------------------------- PSEUDO CODE -----------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include <psos.h>                 /* psos defines and prototypes, etc..  */
#include "names.h"                /* psos object defines                 */
#include "tickldog.h"             /* defines for this task               */
#include "ticks.h"                /* contains RTC defines                */
#include "memap.h"                /* Welder Memory Map                   */

/* definition of all generic  message types */
#include "genrlmsg.h"     
     
/* definition of all incoming message types */
#include "resetmsg.h"

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
*/
                    
/* resets the watchdog counter */                             

//#define TICKLE_WATCHDOG  SimMap->Swsr = 0x55;                
//#define PET_THE_WATCHDOG SimMap->Swsr = 0xAA;

/* indicates to suspend this task */
#define THIS_TASK       0

/* changes the reference so RESET occurs right away */
#define FAST_RESET      0x0003   /* Sets reference to 1 and enable to 1 */

/*
 --------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/
  
typedef union 
   {     
   GENERIC_MSG            generic_msg;
   RESET_MSG              reset_msg;
   } WDTI_MSG_QUEUE_TYPE;

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
void wd_tickle(
   void
   )
   {           
   WDTI_MSG_QUEUE_TYPE   WdtiMessage;            /* gets any reset request   */
   UINT32                Status;                 /* pSOS return status       */
   UINT32                WdtiQid;                /* message queue id         */

   /* retrieve queue id for msg queue receive */
   Status = q_ident(WDTK_Q, Q_NODE_0, &WdtiQid);

   while (1)
      {

      /* Play with the junkyard watchdog  */

      /* check queue for a message */  
      Status = q_receive(WdtiQid, Q_WAIT, SECONDS_TO_TICKS(1), &WdtiMessage);

      /* if a message was received */
      if (Status == PSOS_NOERROR) 
         {
         /* check for reset command */
         if (WdtiMessage.generic_msg.common.opcode == OP_RESET)  
            {
#ifdef PRODUCT_CODE
            /* speed up the reset process */

            /* suspend watchdog task (We won't get very far with this, though) */
            status = t_suspend(THIS_TASK);    
#else
            asm(" trap #0");  /* Cause pROBE entry or XRAY breakpoint. */
#endif
            }
         else
            {
            /* log unexpected message */
            }
         }

      else    
         {
         if (Status != ERR_TIMEOUT) 
            {
              /* log any error other than timeout */

            }
         }
      }

   }


