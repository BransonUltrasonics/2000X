/* $Header:   L:/pvcs/1000/psos332/archives/inc/FPDMSG.H_v   2.1   01 Aug 1996 14:49:48   BKYMER  $ */
#ifndef FP_DISPLAY_MESSAGE_MSG_H
#define FP_DISPLAY_MESSAGE_MSG_H
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name: fp_display_message_msg 

   Filename: fpdmsg.h


            Written by: Mark Lazarewicz 
                  Date: 1/31/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            01/31/96      Mark L      Initial Version
 
 ------------------------------- DESCRIPTION -----------------------------------


 Intertask message with front panel display information

 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "commnmsg.h"
#include "display_message_constructor.h"
#include "fp_blink_state_type.h"
#include "fp_intensity_state_type.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

typedef struct 
        { 
         COMMON_MSG_FIELD_TYPE     common;               /* 32 bits */
         CONSTRUCTED_MESSAGE_TYPE  *constructed_message; /* 32 bits */
         FP_BLINK_STATE_TYPE       blink_state;          /* 8 bits  */
         FP_INTENSITY_STATE_TYPE   intensity_state;      /* 8 bits  */
         UINT16 spare_1;
         UINT32 spare2 ;
        } FP_DISPLAY_MESSAGE_MSG;


/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
