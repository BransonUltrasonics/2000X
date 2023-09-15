/* $Header:   L:/pvcs/1000/psos332/archives/inc/RSSN_MSG.H_v   2.1   01 Aug 1996 14:48:50   BKYMER  $ */
#ifndef RSSN_MODE_MSG_H
#define RSSN_MODE_MSG_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: rssn_mode_msg.h

   Filename:  rssn_msg.h


            Written by: Mark Lazarewicz 
                  Date:  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========

 ------------------------------- DESCRIPTION -----------------------------------

  This file defines the message that changes a port from rssn mode to fips 
  and fips mode to rssn mode.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "commnmsg.h" 

/*
 -------------------------------- DEFINES --------------------------------------
*/

typedef packed enum
   {
   RSSN_RAW_MODE = 0u,
   RSSN_FIPS_MODE
   } RSSN_MODE;

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

typedef struct
   {
   COMMON_MSG_FIELD_TYPE           common;                   /* 32 bits */
   RSSN_MODE		                     rssn_mode;	     	         /* 8 bits  */
   UINT8                           spare_1;                  /* 8 bits */
   UINT16                          spare_2;                  /* 16 bits */
   UINT32                          spare_3;                  /* 32 bits */
   UINT32                          spare_4;                  /* 32 bits */
   } RSSN_MODE_MSG;
   

#endif /* RSSN_MODE_MSG_H */
