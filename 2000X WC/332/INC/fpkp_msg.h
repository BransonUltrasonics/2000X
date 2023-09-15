/* $Header:   K:\APPS\PVCS Pro\332new\INC\FPKP_MSG.H_V   2.2   May 10 1999 14:58:50   lmarkure  $ */
#ifndef FP_USER_REQUEST_MSG_H
#define FP_USER_REQUEST_MSG_H
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

   Module name:   front_panel_user_request_msg

   Filename:      fpkp_msg.h


            Written by: Mark Lazarewicz 
                  Date: 1/28/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            01/28/96      Mark L      Initial Version
	  2.2          05/10/99      LAM         added packed for DIAB

 ------------------------------- DESCRIPTION -----------------------------------

 This defines the FRONT_PANEL_USER_REQUEST_MSG 

 ------------------------------ INCLUDE FILES ----------------------------------
*/
              
#include "commnmsg.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

typedef __packed__(4,1) struct 
        { 
         COMMON_MSG_FIELD_TYPE common;
         UINT8            user_request;
         UINT8                 spare_1;
         UINT16                spare_2;
         UINT32                spare_3;
         UINT32                spare_4;
        } FRONT_PANEL_USER_REQUEST_MSG;


/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
