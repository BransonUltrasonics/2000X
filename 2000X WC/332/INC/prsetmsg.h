/* $Header:   L:/pvcs/1000/psos332/archives/inc/PRSETMSG.H_v   2.2   01 Aug 1996 14:51:08   BKYMER  $ */
#ifndef PRESET_PTR_MSG_H
#define PRESET_PTR_MSG_H
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

   Filename: prsetmsg.h 


            Written by: Mark Lazarewicz  
                  Date: 1/24/96
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
   UINT16                preset_number;
   UINT16                byte_count;
   void                 *msg_pointer;
   } PRESET_TABLE_MSG; 

#endif /* PRESET_PTR_MSG_H */
