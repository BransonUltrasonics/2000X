/* $Header:   L:/pvcs/1000/psos332/archives/inc/nvm_msg.h_v   2.4   30 Mar 1997 19:35:46   lmarkure  $ */
#ifndef NVM_ACCESS_MSG_H
#define NVM_ACCESS_MSG_H 
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
------------------------------ MODULE DESCRIPTION -----------------------------


------------------------------ REVISIONS --------------------------------------
   Revision #      Date          Author      Description
   ==========      ========      ======      ===========
      0             5/05/96      MAL         Initial
      1             6/26/96      LAM         deleted nvm_type.h
      2             3/30/97      LAM         welddata test
----------------------------- DESCRIPTIONS ------------------------------------

   This header file contains the information necessary for use of any of the
   nvm_message.

---------------------------- INCLUDE FILES ------------------------------------
*/

#include "commnmsg.h"  

/*
-------------------------------- DEFINES  -------------------------------------
*/

/*
---------------------------- TYPE DECLARATIONS --------------------------------
*/      

typedef struct
   {
   COMMON_MSG_FIELD_TYPE   common;         /* 32 bits :common to all messages          */
   UINT32                  partition_id;   /* 32 bits : unused                         */
   UINT16                  offset;         /* 16 bits :offset into NVM to start access */
   UINT16                  byte_count;     /* 16 bits :number of bytes to access       */
   void                    *data_pointer;   /* 32 bits :ptr to DRAM (or elsewhere) data */
   }  NVM_ACCESS_MSG;

#endif /* NVM_ACCESS_MSG_H */
