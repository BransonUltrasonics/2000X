/* $Header:   L:/pvcs/1000/psos332/archives/inc/TICKS.H_v   2.4   22 Apr 1998 09:33:30   bbarrows  $ */

#ifndef TICKS_H
#define TICKS_H
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
------------------------- MODULE DESCRIPTION -------------------------------

   Filename:  ticks.h


            Written by: Mark Lazarewicz 
                  Date: 1/10/96 
              Language:  "C"

----------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
                                             for MILLS_TO_TICKS
       1           07/01/96      LAM         deleted days_to_ticks,duration_to_ticks
       2.3         04/05/98      BJB         Added MS_PER_TICK, TICKS_TO_MS,
                                              MS_TO_TICKS.
       2.4         04/21/98      BJB         MS_TO_TICKS() returns 0 if passed 0.

---------------------------- DESCRIPTION -----------------------------------

   This header file is for use with the PSOS+ real time kernel. It will be used
   by application programs that will need to pass a 'TICK' count to any specific
   PSOS+ service routine. These defines are structured such that the developer
   can select a length of duration in the typical time units and not need to
   concern oneself with the conversion to 'TICK' count.
  
---------------------------- INCLUDE FILES ----------------------------------
*/


/*
----------------------------- DEFINES ---------------------------------------
*/


      /* NOTE: Somebody goofed and defined MILLS_PER_TICK as 10 when it's  */
      /* really 5.  This macro and the ones defined from it have been used */
      /* all over the code, so it's somewhat risky to correct the mistake. */
      /* Instead, new macros, MS_PER_TICK, MS_TO_TICKS, TICKS_TO_MS have   */
      /* been defined instead.  These should be used in future conversions.*/


                  /* NOTE: MILLS_PER_TICK * TICKS_PER_SECOND = 1000 */
                  /*       If not, then something is amiss.         */

#define CLOCK_SPEED  16666667           /* Clock speed in hertz     */
#define MILLS_PER_TICK 10               /* Must be an integer value */

#define MS_PER_TICK    5         /* This is right, other one is wrong */

#define TICKS_PER_SECOND 100            /* Must be an integer value */

/*
   To determine the watchdog reference value:

        (CLOCK_SPEED/WTD_TIMER_PRESCALER) * "seconds per WTD timeout"
*/

#define WTD_TIMER_PRESCALER 8192        /* Watchdog timer prescaler */

/*
   These defines are for use with the PSOS+ calls that require a count
   of systems TICKS for a duration of time. Conditions are checked that
   insure 32-bit signed integer math does not overflow (i.e., can only
   wait up to 24 days time). If someone wants to foolishly pass in a
   negative parameter, let them.
*/

#define MS_TO_TICKS(ms)    ((!ms) ? (0) : (((ms) / MS_PER_TICK) + 1))    /* +1 prevents 0 unless ms is 0 */
#define TICKS_TO_MS(ticks) ( (ticks) * MS_PER_TICK )

#define MILLS_TO_TICKS(mills) \
         ( ( (mills) / MILLS_PER_TICK) + 1 )

#define SECONDS_TO_TICKS(secs) \
         ( ( (secs) * 1000 / MILLS_PER_TICK) )

#define MINUTES_TO_TICKS(mins) \
         ( ( (mins) * 60000 / MILLS_PER_TICK) )

/*
------------------------- TYPE DECLARATIONS ---------------------------------
*/


/*  
--------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
---------------------------- EXTERNAL DATA ----------------------------------
*/

#endif     /* TICKS_H */

