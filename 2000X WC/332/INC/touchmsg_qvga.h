/* $Header:   K:/apps/PVCS Pro/332new/INC/touchmsg_qvga.h_v   1.2   Jul 10 2003 17:48:14   SMadhugiri  $ */
#ifndef TOUCH_MSG_H
#define TOUCH_MSG_H
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
   Filename:      touchmsg_qvga.h       


            Written by: Shishir Madhugiri 
                  Date: 03/05/03 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author      Description
   ==========      ========      ======      ===========

   1.0             03/05/03      SCM         Initial Version.
   1.1             03/20/03      SCM         Added message definition for QVGA handler.
   1.2             07/10/03      SCM         Added PVCS Header.
    
 ------------------------------- DESCRIPTION -----------------------------------


 Message definition for touch screen message being sent to QVGA task handler.

 ------------------------------ INCLUDE FILES ----------------------------------
*/  

#include "commnmsg.h"       
                           

/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

typedef struct
   {
   COMMON_MSG_FIELD_TYPE  common;             
   UINT16                 xcord;
   UINT16                 ycord;
   UINT16                 keystatus;
   UINT16                 spare1;
   UINT32                 spare2;   
   }TOUCH_HANDLER_MSG;         
    


/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif  
