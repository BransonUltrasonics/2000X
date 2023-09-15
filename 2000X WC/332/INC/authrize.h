/* $Header:   L:/pvcs/1000/psos332/archives/inc/AUTHRIZE.H_v   2.1   01 Aug 1996 14:52:36   BKYMER  $ */
#ifndef USER_AUTHORIZATION_TYPE_H
#define USER_AUTHORIZATION_TYPE_H 1
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

   Module name: user_authorization_type

   Filename: authrize.h


            Written by: Mark Lazarewicz 
                  Date: 03/25/96 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author           Description
   ==========      ========      ===========      ==============
      0            03/25/96      Mark L           Initial

 ------------------------------- DESCRIPTION -----------------------------------

 This parameter controls the need for user authorization.
                      
 ------------------------------ INCLUDE FILES ----------------------------------
*/
/*
 ------------------------------- DEFINES ---------------------------------------
*/ 
/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/  
                                    
/* parameter expected to be UINT8 */
typedef packed enum
   {                                  
   MIN_USER_AUTHORIZATION_TYPE_LIMIT = 0u,
   USER_AUTHORIZATION_NOT_REQUIRED   = 1,
   USER_AUTHORIZATION_REQUIRED       = 2,
   MAX_USER_AUTHORIZATION_TYPE_LIMIT
   } USER_AUTHORIZATION_TYPE;

#endif /* USER_AUTHOIZATION_TYPE_H */
