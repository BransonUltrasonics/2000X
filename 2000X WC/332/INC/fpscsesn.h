/* $Header:   L:/pvcs/1000/psos332/archives/inc/FPSCSESN.H_v   2.1   01 Aug 1996 14:49:52   BKYMER  $ */

#ifndef FPSC_SESSION_STATE_MSG_H
#define FPSC_SESSION_STATE_MSG_H
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:   fpsc_session_state_msg

   Filename:     fpscsesn.h


            Written by: Mark Lazarewicz
                  Date:  03/18/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
       0           03/18/96      Mark L      Initial Version
  
 ------------------------------- DESCRIPTION -----------------------------------


 Message from the Front Panel State Coordinator to Ascii Diagnostics Interface Manager
 indicating the front panel busy status.

 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "commnmsg.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

typedef packed enum
   {
   FRONT_PANEL_BUSY = 0u,
   FRONT_PANEL_NOT_BUSY
   } FPSC_SESSION_STATE_TYPE;



typedef struct 
        { 
         COMMON_MSG_FIELD_TYPE    	 common;        /* 32 bits */
         FPSC_SESSION_STATE_TYPE   session_state; /* 8 bits  */
         UINT8  spare_1;
         UINT16 spare_2;
         UINT32 spare_3;
         UINT32 spare_4;
        } FPSC_SESSION_STATE_MSG;


/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* FPSC_SESSION_STATE_MSG */
