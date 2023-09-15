/* $Header:   L:/pvcs/1000/psos332/archives/inc/FPDATMSG.H_v   2.1   01 Aug 1996 14:49:44   BKYMER  $ */
#ifndef FP_USER_DATA_MSG_H
#define FP_USER_DATA_MSG_H
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

   Module name:   front_panel_user_data_msg

   Filename:      fpdatmsg.h


            Written by: Mark Lazarewicz 
                  Date: 04/10/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            04/10/96      Mark L      Initial Version

 ------------------------------- DESCRIPTION -----------------------------------

 This defines the FRONT_PANEL_USER_DATA_MSG 

 ------------------------------ INCLUDE FILES ----------------------------------
*/
              
#include "commnmsg.h"
#include "param.h"


/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

typedef struct 
        { 
         COMMON_MSG_FIELD_TYPE common;
         EDIT_PARAM_TYPE       request;
         SINT32                value;
         UINT16                preset;
         UINT16                spare_4;
        } FRONT_PANEL_USER_DATA_MSG;


/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
