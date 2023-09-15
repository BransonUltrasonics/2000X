/* $Header:   K:/apps/PVCS Pro/PSS68k.222/BSP/src/tick_isr.c_v   1.2   Jan 16 2001 16:19:16   lmarkure  $ */
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
/*   PURPOSE: PSOS+ tick generator for the Motorola 68332                   */
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

 ------------------------------- REVISIONS ------------------------------------

   Rev #      Date          Author      Description
   =====      ========      ======      ===========
   1.0        12/22/95      LAM         Initial release for new psos made from
                                        ver 2.8
   1.1        04/29/99      LAM         fixed m68332.h
   1.2        01-09-01      LAM         added complier switch for throughput analysis

 ------------------------------- DESCRIPTION -----------------------------------

   This routine is the PSOS tick ISR.
    

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "bsp.h"
#include <bspfuncs.h>
#include <psos.h>
#include "board.h"
#include <m68332.h>
#include <configs.h>
#include <drv_intf.h>
#include "rxcharcv.h"           /* Own interface                        */

extern UINT16 CommandStarted;
extern RCV_BUFFER_STATUS_TYPE RcvBufferStatus;
UINT16 SerialTimeout = 0;

#define CLK_FREQ   21
#define TIMEOUT   250     /* 5ms * 250 = 1.250 sec */
#define  TICK_IRQ_LEVEL     5
/* This is only set for testing purposes */
//#define INCLUDE_THROUGHPUTTEST 1

/*---------------------------------------------------------------------*/
/* Declaration of clock tick ISR for forward reference                 */
/*---------------------------------------------------------------------*/
static void PsosTickIsr(void);

/*---------------------------------------------------------------------*/
/* The node anchor address is a pointer to the node configuration      */
/* table, which in turn points to the pSOS+ configuration table.  This */
/* driver will look in the pSOS+ configuration table to see how many   */
/* ticks per second are specified, and thus how many interrupts per    */
/* second to generate.                                                 */
/*---------------------------------------------------------------------*/
extern NODE_CT *anchor;

void PsosTickInit(void)
{
/*---------------------------------------------------------------------*/
/* Pre-set return parameter values                                     */
/*---------------------------------------------------------------------*/

/*---------------------------------------------------------------------*/
/* Install the interrupt vector.                                       */
/*---------------------------------------------------------------------*/
   SysSetVector(V_TICK, PsosTickIsr, NORMAL_WRAPPER);
/*---------------------------------------------------------------------*/
/* Establish the periodic interrupt interval and enable the interrupt. */
/* The value for the PITR is given by the formula:                     */
/*                                                                     */
/*            clock_frequency                                          */
/*    PITR =  ------------------                                       */
/*            4 x tick_frequency                                       */
/*                                                                     */
/* clock_frequency for this board is 32768, and tick_frequency is      */
/* given by the pSOS+ configuration table entry kc_ticks2sec.          */
/*---------------------------------------------------------------------*/
   Periodic_Int_Timing_Reg = 32768 / ( 4 * anchor->psosct->kc_ticks2sec);
   Periodic_Int_Ctrl_Reg = (TICK_IRQ_LEVEL << 8) + V_TICK;
}

/***********************************************************************/
/*     PsosTickIsr: Handle a clock tick interrupt                      */
/*                                                                     */
/***********************************************************************/
static void PsosTickIsr(void)
{
/*---------------------------------------------------------------------*/
/* Announce to pSOS+ that another clock tick has occurred.             */
/*---------------------------------------------------------------------*/

#if INCLUDE_THROUGHPUTTEST          /* toggle digpot output */
   asm(" ori.w #$10,$fffe18");      /* drive pin low */
#endif

   tm_tick();
   if(CommandStarted == TRUE)
   {
      SerialTimeout++;
      if(SerialTimeout > TIMEOUT)
      {
         RcvBufferStatus = WAIT_FOR_START;
         CommandStarted = FALSE;
         SerialTimeout = 0;
      }
   }
   else
      SerialTimeout = 0;

#if INCLUDE_THROUGHPUTTEST          /* toggle digpot output */
   asm(" ori.w #$20,$fffe18");      /* drive pin high */
#endif

}


