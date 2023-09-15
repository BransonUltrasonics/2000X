/* $Header:   L:/pvcs/1000/psos332/archives/inc/WRITEFP.H_v   2.2   01 Aug 1996 14:48:20   BKYMER  $ */
#ifndef WRITE_FP_DISPLAY_H
#define WRITE_FP_DISPLAY_H
/*
 ---------------------------- MODULE DESCRIPTION --------------------------

   Module name:  Write_Front_Panel_Display

   Filename:     write_front_panel_display.h


            Written by:  Mark Lazaarewicz 
                  Date:  02/16/96
              Language:  "C"

 -------------------------------- REVISIONS --------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
       1           07/06/96      LAM         cleanup warnings 
 ------------------------------- DESCRIPTION --------------------------------

                                                                     
 Definitions for write front panel display libray and init functions

 ------------------------------ INCLUDE FILES ------------------------------
*/

#include "root.h"                          /* SYS_STARTUP_STATUS_TYPE definition */             
#include "fpdmangr.h"                     /* FP_DISPLAY_REQUEST_TYPE definition */

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/* return codes from write_front_panel_display library function */

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/

/*  
 ----------------------------- FUNCTION PROTOTYPES --------------------------
*/       

WRITE_FP_DISPLAY_STATUS_TYPE WriteFrontPanelDisplay 
                          (FP_DISPLAY_REQUEST_TYPE fp_display_request,
                           BYTE * fp_display_string,
                           FP_BLINK_STATE_TYPE blink_state
                           );
                               
SYS_STARTUP_STATUS_TYPE InitializeFrontPanelDisplay (void) ;


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif 
