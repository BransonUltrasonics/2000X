/* $Header:   L:/pvcs/1000/psos332/archives/inc/SNDSCDAT.H_v   2.1   01 Aug 1996 14:46:40   BKYMER  $ */

#ifndef SEND_SCREEN_DATA_H
#define SEND_SCREEN_DATA_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: SEND_SCREEN_DATA

   Filename: send_screen_data.h 


            Written by: 
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

  Revision #   Date       Author   Description
  ==========   ========   ======   ===========

 ------------------------------- DESCRIPTION -----------------------------------
  This file defines the interface to the executable function of the same
  name. 

 ------------------------------ INCLUDE FILES ----------------------------------
*/ 

#include "portable.h"                       /* general hardware defines, etc..   */
#include "adinityp.h"                       /* defines for ASCII_DIAGS_INITIATOR_TYPE   */
#include "ascrnmsg.h"                       /* defines for EXTERNAL_ASCII_DISPLAY_TYPE and   */
                                            /* ASCII_DATA_BYTE_COUNT_TYPE */
#include "ipscdmsg.h"                       /* defines  CIB_INFO_TYPE  */
#include "commlong.h"


/*
 --------------------------------- DEFINES -------------------------------------
*/                                   

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/ 
/* returned processing  status */
typedef packed enum
   {
   SEND_SCREEN_SUCCESS = 0u,
   SEND_SCREEN_FAILURE
   }  SEND_SCREEN_STATUS;
                         

/* Indicates if a terminate response msg is sent to AIPS following a busy screen */
typedef packed enum
   {
   TERMINATE_FOLLOW_BUSY = 0u,
   TERMINATE_NOT_FOLLOW_BUSY
   } TERMINATE_FOLLOW_BUSY_TYPE;
/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/  
SEND_SCREEN_STATUS 
     send_screen_data(char                        *screen_data,
                      ASCII_DATA_BYTE_COUNT_TYPE  screen_byte_count,
                      ASCII_DIAGS_INITIATOR_TYPE  ascii_diag_initiator,
                      TERMINATE_FOLLOW_BUSY_TYPE  terminate_follow_busy_scr,
                      CIB_INFO_TYPE               *cib_info,
                      UINT32                      qid);
               
/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/    

#endif /* SEND_SCREEN_DATA_H */
