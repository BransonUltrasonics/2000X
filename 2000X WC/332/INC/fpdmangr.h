/* $Header:   K:\APPS\PVCS Pro\332\INC\FPDMANGR.H_V   2.4   Apr 19 1999 15:25:38   ofingere  $ */
#ifndef FP_DISPLAY_MESSAGE_MSG_H
#define FP_DISPLAY_MESSAGE_MSG_H
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

   Module name:   fp_display_message_msg.h


   Filename: fpdmangr.h     

            Written by: Mark Lazarewicz 
                  Date: 2/7/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0            02/07/96      Mark L      Initial Version 
      1            01/05/96      LAM         deleted prototype
 	  2.4		   04/19/99		 OFI		 Changed for DIAB
 ------------------------------- DESCRIPTION -----------------------------------


 Intertask message with front panel display information

 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "commnmsg.h"

/*
 ------------------------------- DEFINES ---------------------------------------
*/
#define MAX_CONSTRUCTED_MESSAGE_SIZE 20

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

typedef char CONSTRUCTED_MESSAGE_TYPE[MAX_CONSTRUCTED_MESSAGE_SIZE];


typedef enum
   {          
   DISPLAY_FP_MESSAGE_REQUEST,
   CLEAR_FP_DISPLAY_REQUEST,
   BLINK_FP_DISPLAY_REQUEST
   } FP_DISPLAY_REQUEST_TYPE ;


typedef enum
   {          
   BLINK_FP_DISPLAY = 0u,
   SOLID_FP_DISPLAY
   } FP_BLINK_STATE_TYPE ;

typedef enum
   {
   REQUEST_PERFORMED,
   UNABLE_TO_PERFORM_REQUST,   
   STRING_TOO_BIG
   } WRITE_FP_DISPLAY_STATUS_TYPE ;


typedef enum
   {          
   INTENSITY_100_PERCENT = 0u ,
   INTENSITY_80_PERCENT  = 1  ,
   INTENSITY_53_PERCENT  = 2  ,
   INTENSITY_40_PERCENT  = 3  ,
   INTENSITY_27_PERCENT  = 4  ,
   INTENSITY_20_PERCENT  = 5  ,
   INTENSITY_13_PERCENT  = 6  ,
   INTENSITY_0_PERCENT   = 7
   } FP_INTENSITY_STATE_TYPE ;


typedef struct 
        { 
         COMMON_MSG_FIELD_TYPE     common;               /* 32 bits */
         CONSTRUCTED_MESSAGE_TYPE  *constructed_message; /* 32 bits */
         FP_BLINK_STATE_TYPE       blink_state;          /* 8 bits  */
         UINT8                     intensity_state;      /* 8 bits  */
         UINT16 spare_1;
         UINT32 spare2 ;
        } FP_DISPLAY_MESSAGE_MSG;

#endif

/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

