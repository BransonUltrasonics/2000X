/* $Header:   K:/APPS/PVCS Pro/332new/App/KEYPAD.C_V   2.25   Dec 02 2003 13:58:34   BKymer  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96              */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
-------------------------- MODULE DESCRIPTION -------------------------------

   Module name: 

   Filename:       keypad.c

   Function name : ProcessFpKeypadInterrupt

 
            Written by:  Mark Lazarewicz
                  Date:  1/29/96
              Language:  Microtec "C"

------------------------------ REVISIONS ------------------------------------

   Revision #      Date          Author      Description
  ==========      ========      ======       ===========
      0            1/29/96      Mark L       Initial Version
      1            4/18/96      LAM          deleted debounce routine
      2            6/11/96      LAM          added code for 2c board 
      3            10/09/96     LAM          running 2c board 
      4            05/05/97     LAM          commented out test code
      5.2.15       05-08-97     BEKymer      Made FpkpQid a global so Inports.c
                                             can use it.
      6            06/04/97     J.B          Free runing kb clock
      2.18         09/19/97     LAM          set keymask to enable all keys
      2.19         09/23/97     LAM          set keymask to 32bits
      2.20         10/16/97     kgd          Enabled test horn down and reset in remote terminal
      2.21         12/29/97     BJB          Deleted use of DTEnabled.
      2.22         01/12/98     BJB          Doesn't call error logging routine
                                              from FakeKeyInt().  That routine
                                              has the bad side-effect of raising
                                              calling task priority!
      2.23         12/16/99     LAM          removed all unused error handling code
      2.23.2.0     03/20/03     SCM          Enabled QVGA interrupt(IRQ5) in 
                                             InitProcessFpKeypadInterrupt() 
      2.23.2.1     03/28/03     SCM          Comment change.                                             
      2.25         12-02-03     BEKymer      Moved 2.23.2.1 to tip for Ver9.00b
                                              build.
                                              

----------------------------- DESCRIPTION -----------------------------------

  This ISR handles the front panel keypad. An interrupt is generated whenever
  a key is pressed or released. 
    
---------------------------    NOTES    ------------------------------------

--------------------------- INCLUDE FILES ----------------------------------
*/


#include <psos.h>                  /* defines used as interface to psos  */
#include "bsp.h"
#include <bspfuncs.h>
#include "root.h"
#include "names.h"                    /* defines for queue and task names   */
#include "commnmsg.h"                 /* common msg definition              */
#include "keypad.h"                   /* function prototype                 */
#include "kpresmsg.h"
#include "opcodes.h"
#include "memap.h"
#include "332.h"

extern UINT32 KeyMask;

/*
----------------------------- EXTERNAL DATA ---------------------------------
                                                                 
 none

----------------------------- LOCAL DEFINES ---------------------------------
*/
//#define    DTDEBUG
#define ALLBITSSET 0xffffffff
 /*
------------------------- LOCAL TYPE DECLARATIONS ---------------------------
*/                                      
         
/*************************    Local Variables     **************************/

UINT32                   FpkpQid;          /* queue id (needed in inports.c */
static    UINT32         PsosReturnValue;  /* holds status from PSOS calls  */

static    BYTE             *KeyAddr;
static    BYTE             *KeyData;

/*                                                                         */
/***************************************************************************/

SYS_STARTUP_STATUS_TYPE InitProcessFpKeypadInterrupt(void)

/****************************************************************************/ 
/*                                                                          */    
/* This routine sets up the address of the keyboard controller, sets up the */
/* interrupt vector, and configures the keyboard controller.                */    
/*                                                                          */
/****************************************************************************/ 
{

   SYS_STARTUP_STATUS_TYPE  SysStartupStatus = SYS_STARTUP_PASS;

   /*----------------------------------------------------------------------*/
   /* Get the queue id  of FPKP QUEUE                                      */
   /*----------------------------------------------------------------------*/

   PsosReturnValue = q_ident(FPKP_Q, Q_NODE_0, &FpkpQid);

   /* able to identify queue ? If not log the error */

   KeyMask = ALLBITSSET;
   
   
   /*----------------------------------------------------------------------*/
   /* Install the Vector                                                   */
   /*----------------------------------------------------------------------*/

   SysSetVector(V_KEYINT, KeyInt, NORMAL_WRAPPER);

   KeyAddr = (BYTE *) 0x14300a;
   KeyData = (BYTE *) 0x143008;
/* Configure 8279 */
   *(KeyAddr) = 0;          /* 8-bit encoded scan 2 key lockout */
   *(KeyAddr) = 0x22;       /* 1 Mhz % by 10 = 2a*/
   *(KeyAddr) = 0xc0;       /* clr output */

    /* This command should be in BSP. This sets IRQ's for printer(IRQ1), keypad(IRQ2) and 
       the Quarter VGA display (IRQ5).But for now this will stay here until we can move
       this at a more appropriate time */
   SimMap->Pfpar = 0x26;  
   return (SysStartupStatus) ;
   
}


void KeyInt(void)
{

   KEY_CODE_TYPE key;
 
   FP_KEY_PRESSED_MSG FpkpQueue;

   key = *(KeyData) & 0x1f;

   /* send out the message the fpkp task will then debounce the key */
   FpkpQueue.key = key;                                      
   FpkpQueue.common.opcode = OP_FRONT_PANEL_KEYPRESS;
   PsosReturnValue = q_send(FpkpQid, &FpkpQueue);
}

 void FakeKeyInt(KEY_CODE_TYPE key)
{

   FP_KEY_PRESSED_MSG FpkpQueue;

    FpkpQueue.key = key;
    FpkpQueue.common.opcode = OP_FRONT_PANEL_KEYPRESS;
    q_send(FpkpQid, &FpkpQueue);
}
