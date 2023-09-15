/* $Header:   L:/pvcs/1000/psos332/archives/inc/TIMERS.H_v   2.1   01 Aug 1996 14:51:06   BKYMER  $ */
#ifndef SET_TIMERS_H
#define SET_TIMERS_H
/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Set_Timers

   Filename:  timers.h


            Written by: Mark lazarewicz 
                  Date: 1/25/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

 The "set_timers" routine can be called to start a timer, re-start a timer with
 a new value, or stop a timer in progress.  The procedure for calling this 
 module is as follows:

 1) Set timer_name to the desired timer listed in file "timrname.h".

 2) Set time_remaining to the desired timer length in units of system ticks.
    Use the macros defined in "ticks.h" to convert from time to ticks. 
    Setting time_remaining to "0" will stop a timer in progress.

 3) Specify the message opcode to be sent once the timer expires by setting
    expiration_msg.common.opcode to "OP_TIMER_EXPIRED" and by setting 
    expiration_msg.state to the timer name specified in step 1.

 4) Set queue_id to the queue needing the timer expired message.

 Example:

        timeout_value = SECONDS_TO_TICKS( number of seconds ); 
        timer_expired_msg.common.opcode = OP_TIMER_EXPIRED;
        timer_expired_msg.state         = PTT_TOT_TIMER;
        status = q_ident(NVMM_Q, Q_NODE_0, &NvmmQid); 

        set_timers( BATT_BKUP_TIMER, 
                    timeout_value,
                    timer_expired_msg,
                    NvmmQid );  


 Note:  Timers must be set by code of single-threaded execution, i.e. two
        different tasks should not be starting/stopping a timer of the same 
        name.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "timrname.h"     /* types used by more than two functions     */
#include "timr_msg.h" 

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef SINT32 TIME_REMAINING_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

void SetTimers(  
   TIMER_NAME_TYPE          timer_name,
   TIME_REMAINING_TYPE      time_remaining,
   TIMER_EXPIRED_MSG        expiration_msg,
   UINT32                   queue_id
   );

void InitSetTimers (void);

void ManageTimers (void);  /* interrupt service routine */

/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* end of SET_TIMERS_H */
