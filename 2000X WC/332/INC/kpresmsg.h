/* $Header:   K:\APPS\PVCS Pro\332new\INC\KPRESMSG.H_V   2.3   May 10 1999 15:02:58   lmarkure  $ */
#ifndef FP_KEY_PRESSED_MSG_H
#define FP_KEY_PRESSED_MSG_H
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

   Module name:   front_panel_user_request_type

   Filename:      kpresmsg.h


            Written by: Mark Lazarewicz 
                  Date: 1/29/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========

   2.2             04/23/98      BJB         Added "extra" to key message format
   2.3             05/10/99      LAM         added packed for DIAB
    
 ------------------------------- DESCRIPTION -----------------------------------


 Intertask message definition for key pressed detection.

 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "commnmsg.h"
#include "keypad.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

typedef __packed__(4,1) struct 
        { 
         COMMON_MSG_FIELD_TYPE common;
         KEY_CODE_TYPE  key;
         UINT8          extra;
         UINT16         spare0;
         UINT32         spare1;
         UINT32         spare2;
        } FP_KEY_PRESSED_MSG;


/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
