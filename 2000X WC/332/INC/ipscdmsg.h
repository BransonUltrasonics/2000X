/* $Header:   K:/APPS/PVCS Pro/332new/INC/IPSCDMSG.H_V   2.11   Apr 30 1999 11:11:40   lmarkure  $ */
#ifndef IPS_COMMAND_MSG_H
#define IPS_COMMAND_MSG_H
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
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: ips_command_msg

   Filename:  ipscdmsg.h


            Written by: Mark Lazarewicz
                  Date: 03/18/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
        0           03/18/96      Mark L      Initial
        1           04/22/97      LAM         added host command msg
        2           04/28/97      LAM         cleanup            
        3           05/20/97      LAM         added host command weld msg
      2.9           10/28/98      LAM         added ; after datapointer to fix
                                              cc rider error
      3.0     		04/19/99	  OFI		  changed for DIAB
	  2.11          04/29/99      LAM         fixed l to LONG
 ------------------------------- DESCRIPTION -----------------------------------  

 All the type definitions in this file support the definition of the
 IPS_COMMAND_MSG.  This type consists of CIB communications routing
 information and IPS information. Since IPS information will reside 
 in a pSos allocated buffer, a partition is is provided for deallocation
 responsibilities.

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "weld_obj.h"
#include "commnmsg.h"
#include "cibinfo.h"
#include "ipscmdty.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
typedef struct
   {
   CIB_INFO_TYPE    cib_info;
   IPS_COMMAND_TYPE ips_info;
   } IPS_MESSAGE_TYPE; 
                                   
/* pSos message queue message */
typedef struct
   {
   COMMON_MSG_FIELD_TYPE  common;          /* 32 bits */
   ULONG                  partition_id;    /* 32 bits */
   UINT16                 offset;     
   UINT16                 byte_count;    
   void                   *data_pointer;
   }HOST_COMMAND_MSG;

typedef struct
   {
   COMMON_MSG_FIELD_TYPE  common;          /* 32 bits */
   ULONG                  partition_id;    /* 32 bits */
   UINT16                 offset;     
   UINT16                 byte_count;    
   WELD_DATA              *data_pointer;
   }HOST_CMD_WELD_MSG;

/*----------------------- FUNCTION PROTOTYPES ------------------------------*/

/*----------------------------- EXTERNAL DATA ------------------------------*/

#endif /* IPS_COMMAND_MSG_H */
