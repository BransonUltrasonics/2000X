/* $Header:   L:/pvcs/1000/psos332/archives/inc/MYPTRMSG.H_v   2.1   01 Aug 1996 14:51:16   BKYMER  $ */
#ifndef GENERIC_PTR_MSG_H
#define GENERIC_PTR_MSG_H
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

   Module name: GENERIC_PTR_MSG

   Filename: genptrms.h 


            Written by: Mark Lazarewicz 
                  Date: 01/04/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

   Revision #      Date          Author           Description
   ==========      ========      ===========      ==============


 ------------------------------- DESCRIPTION -----------------------------------


*/

/*
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
   COMMON_MSG_FIELD_TYPE common;
   UINT32                partition_id; 
   UINT16                spare;
   UINT16                byte_count;
   void                 *msg_pointer;
   } GENERIC_PTR_MSG; 

#endif /* GENERIC_PTR_MSG_H */
