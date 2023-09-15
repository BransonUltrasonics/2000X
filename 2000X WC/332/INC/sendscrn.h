/* $Header:   L:/pvcs/1000/psos332/archives/inc/sendscrn.h_v   2.3   30 Mar 1997 19:34:50   lmarkure  $ */
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
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      sendscrn.h


            Written by: Laura Markure 
                  Date: 5/13/96  
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/14/96      LAM         Initial
      2             3/30/97      LAM         welddata test
 
 ------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           
 
/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/

SEND_SCREEN_STATUS SendScreenData(
			BYTE                *screen_data,              /* screen data to be sent */
                        ASCII_DATA_BYTE_COUNT_TYPE  screen_byte_count,         /* screen data byte count */
                        ASCII_DIAGS_INITIATOR_TYPE  ascii_diag_initiator,      /* interface data is send to */
                        TERMINATE_FOLLOW_BUSY_TYPE  terminate_follow_busy_scr, /* terminate follow busy scr */
                        CIB_INFO_TYPE               *cib_info,                 /* cib info for aips interface */
                        UINT32                      comm_shell_qid             /* qid for send_comm_str_with_length */
);


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/


