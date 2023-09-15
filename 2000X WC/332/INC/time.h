/* $Header:   L:/pvcs/1000/psos332/archives/inc/TIME.H_v   2.1   01 Aug 1996 14:52:04   BKYMER  $ */
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
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            12/12/94      Mark Lazarewicz Initial release 


 ------------------------------- DESCRIPTION -----------------------------------

   This file defines prototypes for the real time clock

 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/

#ifndef TIME_H
#define TIME_H


/*********************************************************************/ 
/*  Timer structures                                                 */
/*********************************************************************/ 

struct t_date        {
        UINT16 year;  /* Year, A.D. */
        UINT8 month; /* Month, 1->12 */
        UINT8 day;   /* Day, 1->31 */
};

struct t_time        {
        UINT16 hour;    /* Hour, 0->23 */
        UINT8 minute;  /* Minute, 0->59 */
        UINT8 second;  /* Second, 0->59 */
};

struct time_ds        {
        struct t_date date;    /* Date */
        struct t_time time;    /* Time */
        UINT32 ticks;   /* Current Elapsed Ticks Between Seconds */
};


#endif     /* TIME_H */


