/* $Header:   L:/pvcs/1000/psos332/archives/inc/TIMRNAME.H_v   2.1   01 Aug 1996 14:52:10   BKYMER  $ */
#ifndef TIMER_NAME_TYPE_H
#define TIMER_NAME_TYPE_H 1

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name:  TIMER_NAME_TYPE_H

   Filename:  timrname.h


            Written by: Mark Lazarewicz
                  Date: 1/26/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

  Revision #   Date       Author      Description
  ==========   ========   ======      ===========
     0         01/26/96   Mark L      Initial Version
     1         03/21/96   Mark L      Added FP activity timer

 ------------------------------- DESCRIPTION -----------------------------------

   Contains the name of all timers that are managed by manage_timers.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*                                                               
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/


/* list of timer names */
typedef enum
   {  
   ASCII_INACTIVITY_TIMER,
   FPSP_SHELL_INACTIVITY_TIMER,
   FRONT_PANEL_ACTIVITY_TIMER,
   NVM_WRITE_BANK_TIMER,
   NVM_QUEUE_WAIT_TIMER,
   NO_KEYPRESS_KEYPAD_TIMER,
   P_PSTN_INACTIVITY_TIMER,
   SYSTEM_TIMER,
/* ALL timers should be added above this */
/* the next line is number of timers defined by this enum */
   NUM_OF_TMRS, 
   NOTHING_EXPIRED
   } TIMER_NAME_TYPE;                  

#endif /* TIMER_NAME_TYPE_H */



