/* $Header:   L:/pvcs/1000/psos332/archives/inc/COMXMITS.H_v   2.2   01 Aug 1996 14:48:38   BKYMER  $ */
#ifndef COMM_XMT_STRING_H
#define COMM_XMT_STRING_H
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

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: Comm_XMT_String

   Filename:    comm_xmt_string.h 


 -------------------------------- REVISIONS ------------------------------------

    Revision #      Date          Author      Description
    ==========      ========      ======      ===========
      0            02/08/96      Mark Lazarewicz Initial release 


 ------------------------------- DESCRIPTION -----------------------------------


 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "cibinfo.h"


/*
 --------------------------------- DEFINES -------------------------------------
*/


/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

#endif /* COMM_XMT_STRING_H */

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/

void CommXmtStringInit(void);

void CommXmtString(
   CIB_INTERFACE_TYPE_TYPE           comm_port,                     /* Designates which SCC port         */
   char                              *str_ptr );                    /* Pointer to null terminated string */

void CommQueueString(
   UINT32                            qid,                           /* Queue ID to send to               */
   CIB_INTERFACE_TYPE_TYPE           comm_port,                     /* Comm port designator              */
   char                              *str_ptr );                    /* Pointer to null terminated string */


void CommXmtBuf(
   CIB_INTERFACE_TYPE_TYPE           comm_port,                     /* Designates which SCC port         */
   UINT32                            partition_id,                  /* Partition Id of buffer to send    */
   UINT8                             *buf_ptr,                      /* Pointer to buffer                 */
   UINT16                            buf_length );                   /* Number of bytes to transmit       */

void SendCommStringLong(
    char                                *string_ptr,                /* String to transmit            */
    UINT32                              partition_id,               /* partition id of buffer        */
    UINT32                              qid );                       /* Protocol Manager Queue ID     */

void SendCommStrWithLength(
    char                                *string_ptr,                /* String to transmit            */
    UINT32                              partition_id,               /* partition id of buffer        */
    UINT32                              qid,                        /* Protocol Manager Queue ID     */
    UINT16                              buf_length );                /* NUmber of bytes to transmit   */






























